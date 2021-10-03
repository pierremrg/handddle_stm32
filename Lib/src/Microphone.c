#include "../../Lib/inc/Microphone.h"

#include "../../Core/Inc/main.h"

#define SETTING_VOLTAGE 3.3
#define ADC_12BITS 4096

extern ADC_HandleTypeDef hadc2;
extern DMA_HandleTypeDef hdma_adc2;

uint16_t adc_value_mic[2];
uint16_t RxBuffer[8];
uint16_t TxBuffer[8];


void get_listening()
{
	ADC_Select_CH10();
//	float ADC_1 = adc_value_mic[0];
//	float voltage_ADC_1 = ADC_1  / ADC_12BITS * SETTING_VOLTAGE;

	ADC_Select_CH11();
//	float ADC_2 = adc_value_mic[1];
//	float voltage_ADC_2 = ADC_2  / ADC_12BITS * SETTING_VOLTAGE;
}

void ADC_Select_CH10()
{
	ADC_ChannelConfTypeDef sConfig = {0};

	// Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	sConfig.Channel = ADC_CHANNEL_10;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
	{
	Error_Handler();
	}

	HAL_ADC_Start(&hadc2);
	HAL_ADC_PollForConversion(&hadc2, 1000);
	adc_value_mic[0] = HAL_ADC_GetValue(&hadc2);
	HAL_ADC_Stop(&hadc2);
}


void ADC_Select_CH11()
{
	ADC_ChannelConfTypeDef sConfig = {0};

	// Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	sConfig.Channel = ADC_CHANNEL_11;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_ADC_Start(&hadc2);
	HAL_ADC_PollForConversion(&hadc2, 1000);
	adc_value_mic[1] = HAL_ADC_GetValue(&hadc2);
	HAL_ADC_Stop(&hadc2);
}


