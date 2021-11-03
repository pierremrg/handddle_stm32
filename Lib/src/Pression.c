#include "../../Lib/inc/Pression.h"

#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Sec_msg_gen/sec_msg_gen.h"

#define VOLTAGE_SUPPLY 3.3
#define THRESHOLD 50000

uint16_t adc_value_pressure[1] = {0};
int16_t pressure;

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

int get_pression()
{
	ADC_Select_CH12();

	// according to the sensor datasheet for the 500PA, DifferentialPressure = (750 * AOut / Vdd) - 150
	float Value_ADC = adc_value_pressure[0];
	float sensorVoltage = Value_ADC/4096*VOLTAGE_SUPPLY;
	float DP = (750*sensorVoltage/VOLTAGE_SUPPLY)-150;
	pressure = (int16_t) DP;

	return pressure;
}


void ADC_Select_CH12()
{
	ADC_ChannelConfTypeDef sConfig = {0};
	  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	  */
	  sConfig.Channel = ADC_CHANNEL_12;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  adc_value_pressure[0] = HAL_ADC_GetValue(&hadc1);
	  HAL_ADC_Stop(&hadc1);
}

void send_pression()
{
	send_sec_msg_pressure(pressure,&huart2);
}
