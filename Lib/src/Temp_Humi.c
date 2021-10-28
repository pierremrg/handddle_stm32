#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"
#include "../../Lib/inc/Temp_humi.h"
#include <string.h>

extern I2C_HandleTypeDef hi2c2;
extern I2C_HandleTypeDef hi2c3;

extern UART_HandleTypeDef huart2;

static const uint8_t REG_TEMP = 0x00;

extern float moy_temperature;
extern float moy_humidity;

float get_temp_humi_HIH1()
{
//	uint16_t  address = 0x27;             /* Address of Honeywell sensor shifted right 1 bit */
//	address = address << 1;
	float reading_hum1;
	float reading_hum2;
	float reading_temp1;
	float reading_temp2;
	float humidity1;
	float humidity2;
	float temperature1;
	float temperature2;

	//1nd sensor
	uint8_t buf1[7] = {0};                 /* Buffer for data read/written on the i2c bus */
	buf1[0] = REG_TEMP;
	HAL_StatusTypeDef ret1;
	// Tell HIH that we want to read from the temperature register
	/* SmartPower */

	    ret1 = HAL_I2C_Master_Transmit(&hi2c2, 0x4F , buf1, 1, HAL_MAX_DELAY);
	    HAL_Delay(50);
	    if ( ret1 != HAL_OK )
	    {
	      strcpy((char*)buf1, "Tx 1\r\n");
	    }
	    else
	    {
	      // Read 2 bytes from the temperature register
	      ret1 = HAL_I2C_Master_Receive(&hi2c2, 0x4E, buf1, 4, HAL_MAX_DELAY);
	      HAL_Delay(50);
	      if ( ret1 != HAL_OK )
	      {
	        strcpy((char*)buf1, "Rx 1\r\n");
	      }
	      else
	      {
	    	/* Humidity is located in first two bytes */
			reading_hum1 = (buf1[0] << 8) + buf1[1];
			humidity1 = reading_hum1 / 16382.0 * 100.0;

			/* Temperature is located in next two bytes, padded by two trailing bits */
			reading_temp1 = (buf1[2] << 6) + (buf1[3] >> 2);
			temperature1 = reading_temp1 / 16382.0 * 165.0 - 40;
	      }
	    }
	    //2nd sensor
		uint8_t buf2[36] ={0};                 /* Buffer for data read/written on the i2c bus */
		buf2[0] = REG_TEMP;
		HAL_StatusTypeDef ret2;
		// Tell HIH that we want to read from the temperature register
		/* SmartSensor */
		ret2 = HAL_I2C_Master_Transmit(&hi2c3, 0x4F, buf2, 1, HAL_MAX_DELAY);
		HAL_Delay(50);
		if ( ret2 != HAL_OK )
		{
		  strcpy((char*)buf2, "Tx 2\r\n");
		}
		else
		{
		  // Read 2 bytes from the temperature register
		  ret2 = HAL_I2C_Master_Receive(&hi2c3, 0x4E, buf2, 4, HAL_MAX_DELAY);
		  HAL_Delay(50);
		  if ( ret2 != HAL_OK )
		  {
			strcpy((char*)buf2, "Rx 2\r\n");
		  }
		  else
		  {
			/* Humidity is located in first two bytes */
			reading_hum2 = (buf2[0] << 8) + buf2[1];
			humidity2 = reading_hum2 / 16382.0 * 100.0;

			/* Temperature is located in next two bytes, padded by two trailing bits */
			reading_temp2 = (buf2[2] << 6) + (buf2[3] >> 2);
			temperature2 = reading_temp2 / 16382.0 * 165.0 - 40;
		  }
		}

		//For the both sensor at the same time
		moy_temperature = (temperature1 + temperature2) / 2;
		moy_humidity = (humidity1 + humidity2) / 2;

		return moy_temperature;

}

float get_temp_humi_SHT40()
{
	float reading_hum1;
	float reading_hum2;
	float reading_temp1;
	float reading_temp2;
	float humidity1; //SmartPower Sensor
	float humidity2; //SmartBoard Sensor
	float temperature1; //SmartPower Sensor
	float temperature2; //SmartBoard Sensor

	//1nd sensor
	uint8_t buf1[7] = {0};                 /* Buffer for data read/written on the i2c bus */
	buf1[0] = 0xFD;                      // Command for measuring Temp and Hum with HIGH Precision
	HAL_StatusTypeDef ret1;              // Struct to Use with i2C communication

	// Tell HIH that we want to read from the temperature register
	/* SmartPower */
	ret1 = HAL_I2C_Master_Transmit(&hi2c2, (SHT4X_ADDRESS << 1), buf1, 1, 200); // Decalage de 1 bit car adresse sur 7 bits
	HAL_Delay(20);
	if ( ret1 != HAL_OK )
	{
//		send_error_msg_temp_env(&huart2); //SPAM si error à corriger
//		send_error_msg_hum_env(&huart2);
		temperature1 = 0;
		humidity2 = 0;
	}
	else
	{
	  // Read 2 bytes from the temperature register
	  ret1 = HAL_I2C_Master_Receive(&hi2c2, (SHT4X_ADDRESS << 1) , buf1, 6, 200);
	  HAL_Delay(20);
	  if ( ret1 != HAL_OK )
	  {
		strcpy((char*)buf1, "Rx 1\r\n");
	  }
	  else
	  {
		/* Temperature is located in next two bytes, padded by two trailing bits */
		reading_temp1 = (buf1[0] << 8) + (buf1[1]);
		temperature1 = 175 * reading_temp1 / 65535 - 45;     // from datasheet

		/* Humidity is located in the 4th and 5th bytes */
		reading_hum1 = (buf1[3] << 8) + buf1[4];
		humidity1 = 125 * reading_hum1 / 65535 - 6 ;        // from datasheet

		if(humidity1 > 100)
		{
			humidity1 = 100;
		}
		else if (humidity1 < 0)
		{
			humidity1 = 0;
		}
	  }
	}
	//2nd sensor
	uint8_t buf2[7] ={0};                 /* Buffer for data read/written on the i2c bus */
	buf2[0] = 0xFD;
	HAL_StatusTypeDef ret2;
	// Tell HIH that we want to read from the temperature register
	/* SmartSensor */
	ret2 = HAL_I2C_Master_Transmit(&hi2c3, (SHT4X_ADDRESS << 1), buf2, 1, HAL_MAX_DELAY);
	HAL_Delay(20);
	if ( ret2 != HAL_OK )
	{
//		send_error_msg_temp_env(&huart2);
//		send_error_msg_hum_env(&huart2);
		temperature2 = 0;
		humidity2 = 0;
	}
	else
	{
	  // Read 2 bytes from the temperature register
	  ret2 = HAL_I2C_Master_Receive(&hi2c3, (SHT4X_ADDRESS << 1), buf2, 5, HAL_MAX_DELAY);
	  HAL_Delay(1);
	  if ( ret2 != HAL_OK )
	  {
		strcpy((char*)buf1, "Rx 2\r\n");
	  }
	  else
	  {
		/* Temperature is located in next two bytes, padded by two trailing bits */
		reading_temp2 = (buf2[0] << 8) + (buf2[1]);
		temperature2 = 175 * reading_temp2 / 65535 - 45;

		/* Humidity is located in the 4th and 5th bytes */
		reading_hum2 = (buf2[3] << 8) + buf2[4];
		humidity2 = 125 * reading_hum2 / 65535 - 6 ;

		if(humidity2 > 100)
		{
			humidity2 = 100;
		}
		else if (humidity2 < 0)
		{
			humidity2 = 0;
		}
	  }
	}

	//For the both sensor at the same time
	if (temperature1 == 0)
	{
		moy_temperature = temperature2;
		moy_humidity = humidity2;
	}
	else if(temperature2 == 0)
	{
		moy_temperature = temperature1;
		moy_humidity = humidity1;
	}
	else
	{
		moy_temperature = (temperature1 + temperature2) / 2;
		moy_humidity = (humidity1 + humidity2) / 2;
	}

	return moy_temperature;

}
void send_temp_humi()
{
	send_main_msg_temp_hum(moy_temperature,(uint16_t)moy_humidity,&huart2);
}

void send_temp()
{
	send_main_msg_temp(moy_temperature,&huart2);
}

void send_humi()
{
	send_main_msg_hum((uint16_t)moy_humidity,&huart2);
}
