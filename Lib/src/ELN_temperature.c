#include "../../Lib/inc/ELN_temperature.h"

#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Sec_msg_gen/sec_msg_gen.h"
#include <math.h>

#define V_SUPPLY 		3.3
#define T0 				298.15 			// 25 + 273.15 -> Datasheet : Temperature de référence
#define RT0 			100000.0		// Reference resistor
#define Beta 				3977.0			// Beta
#define R0 				22000			// Resistor on voltage divider
#define R10k 10000.0

uint16_t adc_value_ELN_TEMP;
//float Temperature_C;
float Temperature_C;

extern ADC_HandleTypeDef	hadc1;
extern UART_HandleTypeDef 	huart2;


void get_ELN_temp()
{
	ADC_Select_CH13();
	float A = 0.0009072951475;
	float B = 0.0002557611399;
	float C = 0.0000001165649589;

	float Temperature_ADC = adc_value_ELN_TEMP;
	float sensorVoltage = Temperature_ADC*V_SUPPLY/4096;
	float R_CTN_ELN_temperature = (R10k * (sensorVoltage/V_SUPPLY)/ (1 - (sensorVoltage/V_SUPPLY)));
	float temp_K = (1 / (A + B * log(R_CTN_ELN_temperature) + C * pow(log(R_CTN_ELN_temperature),3))); //Log not ok
	float temp_C = temp_K - 273.15;
	Temperature_C = temp_C;



  //Temperature_C = 1 / ((1/T0) + (1/B) * log( (R0/RT0) * (( 4096.0 / adc_value_ELN_TEMP ) - 1) )) - 273.15;

}


void ADC_Select_CH13()
{
	ADC_ChannelConfTypeDef sConfig = {0};

	// Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time
	sConfig.Channel = ADC_CHANNEL_13;
	sConfig.Rank = 1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	adc_value_ELN_TEMP = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
}

void send_ELN_temp()
{
	send_sec_msg_temp_rack(Temperature_C, &huart2);
}


