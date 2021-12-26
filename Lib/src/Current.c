// The current sensor use in this project is the current transductor HO-P/SP33
// The value of the Ipn can be : 6, 10 or 25 A
// We use external Vref on 1.65V (we divide on 2 the 3V3 power supply)
//
// At 1.65V we have 0A read
// The sensor range is -25A to 25A
// On arduino : 0V --> 0 [ADC]  | 165V -- > 338 [ADC]  |  3.3V -- > 676 [ADC}  | 5V --> 1023 [ADC]

#include "../../Lib/inc/Current.h"

#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"
#include <math.h>
#include <string.h>

#define SETTIING_CURRENT_CALIBRATION 3
#define SETTING_VOLTAGE 3.3
#define THEORY_FORMULA 4600 // Step for our calibration are 46 mV for 1A
#define ALIM_VOLTAGE 230
#define ADC_12BITS 4096
#define VREF_CURRENT_2 1.646 // Volt
#define VREF_CURRENT_1 1.655 // Volt
#define GAIN 76.67 // mV/A


uint16_t adc_value_current_1[50];
uint16_t buf;
uint16_t buf2;
uint16_t adc_current_1_max[1];

uint16_t adc_value_current_2[50];
uint16_t adc_current_2_max[1];

float Printer_Consumption;
float Printer_Current;

float Printer_Consumption2;
float Printer_Current2;
float p_Volt=0;

extern int index_adc_current;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart2;

int i_current=0;
int i_timer5;
extern int current_breakdown;

int tab_ConsumptionValues[1000];
int Incorrect_Values=0;

extern float tabEXEMPLE[1500];
extern float tabEXEMPLE2[1500];
extern float MAX;
extern float MIN;




void getElectricCurrentConsumption()
{
	ADC_Select_CH4();

	if (i_current < 1000) // size of array
	{
		tab_ConsumptionValues[i_current] = Printer_Consumption;
		i_current+=1;
	}
	else {
		MIN = tab_ConsumptionValues[0]; MAX = tab_ConsumptionValues[0];

		for(int i=0; i<1000; i += 1)
			if(MIN > tab_ConsumptionValues[i]) MIN = tab_ConsumptionValues[i];
		for(int i=0; i<1000; i += 1)
			if(tab_ConsumptionValues[i] > MAX) MAX = tab_ConsumptionValues[i];

		i_current = 0;
		Incorrect_Values = 0;
	}

	getElectricCurrentConsumptionTransmit();

	if(Printer_Consumption > 100) //100W we estimated no active printer for conso < 100watts
		Incorrect_Values+=1;
}

void getElectricCurrentConsumptionTransmit()
{
	float Voltage_Printer = (buf * SETTING_VOLTAGE) / ADC_12BITS;

	float Diff_Potentiel = fabs((Voltage_Printer - VREF_CURRENT_2) * 1000); // *1000 -> mV

	Printer_Current = Diff_Potentiel / (3*GAIN); // 3*Gain -> 3 tours
	Printer_Consumption = Printer_Current * ALIM_VOLTAGE; // Attention for power voltage (220V-240V)

	//send_main_msg_current_printer(Printer_Consumption,&huart2);
}



void ADC_Select_CH4() // Consumption printer plug = Current 2
{
	/*ADC_Current_2*/
	/* Current1 Env */
	ADC_ChannelConfTypeDef sConfig = {0};
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = 1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);
	buf = HAL_ADC_GetValue(&hadc1);
//	HAL_ADC_Stop(&hadc1);

}

void ADC_Select_CH5() // Consumption ee = Current 1
{
	/*ADC_Current_1*/
	/* Current1 Env */
	ADC_ChannelConfTypeDef sConfig = {0};
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_5;
	sConfig.Rank = 2;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1000);
	buf2 = HAL_ADC_GetValue(&hadc1);
//	HAL_ADC_Stop(&hadc1);
}

void get(){
	float Voltage_Printer2 = (buf2 * SETTING_VOLTAGE) / ADC_12BITS;

	//	float Voltage_Printer_Eff = Voltage_Printer / sqrt(2);

	float Diff_Potentiel2 = fabs((Voltage_Printer2 - VREF_CURRENT_2) * 1000); // *1000 -> mV

	Printer_Current2 = Diff_Potentiel2 / (3*GAIN); // 3*Gain -> 3 tours
	Printer_Consumption2 = Printer_Current2 * ALIM_VOLTAGE; // Attention for power voltage (220V-240V)

	if(Voltage_Printer2 != 0) tabEXEMPLE[i_timer5] = Voltage_Printer2;
}
