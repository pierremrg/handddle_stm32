#include "../../Lib/inc/Heater.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Sec_msg_gen/sec_msg_gen.h"
#include <math.h>

#define SECOND 60
#define HALL_SENSORS 3 // Number of Hall captors in the Fan
#define FULL_PERIOD 2
#define R22k 22000
#define VOLTAGE_SUPPLY 3.3
#define MAX_TEMPERATURE 200.0

extern TIM_HandleTypeDef htim8;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;


uint16_t adc_value_HEATER_TEMP[1];
float temperature_C_heater;


void set_heater_pwm (int dutycycle)
{
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	htim8.Instance->CCR3 = dutycycle; // PWM Rate might change
}

void set_heater(int ON_off_heater)
{
	get_heater_temp(); //Récupération de adc_value - Need to check if it's not working go on int for the heater_temp
	if(temperature_C_heater < MAX_TEMPERATURE)
	{
		if(ON_off_heater == 1 )
			HAL_GPIO_WritePin(GPIOB, HEATER_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(GPIOB, HEATER_Pin, GPIO_PIN_RESET);
	}
	else
		HAL_GPIO_WritePin(GPIOB, HEATER_Pin, GPIO_PIN_RESET);
}

void ADC_Select_CH9()
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_9;
	  sConfig.Rank = 1;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  adc_value_HEATER_TEMP[0] = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);
}


void get_tachy()
{
	//Tachy
	 /* Measure the duration of the (half) period */
	//Read to check the rising edge start timer check falling stop timer
	//unsigned long periode = pulseIn(HEATER_TACHY_PIN, LOW, 1000000) * FULL_PERIOD;

	  /* Displays the measurement result in RPM */

	 // Serial.println(1000000 / periode * SECOND);
}


int get_heater_temp()
{
	ADC_Select_CH9();
	//Steinhart-Hart coefficients
	float A = 0.0006318979274;
	float B = 0.000226285692;
	float C = 0.0000000766104297845452;
	float ADC_1 = adc_value_HEATER_TEMP[0];
	float sensorVoltage = ADC_1 * VOLTAGE_SUPPLY / 4096;
	float R_CTN_Heater = (R22k * (sensorVoltage/VOLTAGE_SUPPLY)/ (1 - (sensorVoltage/VOLTAGE_SUPPLY)));
	float temperature_K = (1 / (A + B * log(R_CTN_Heater) + C * pow(log(R_CTN_Heater), 3)));
	temperature_C_heater = temperature_K - 273.15;

	return temperature_C_heater;
}

void send_heater_temp()
{
	send_sec_msg_temp_heating_resistor((uint16_t) temperature_C_heater, &huart2);
}
