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
uint16_t adc_current_1_max[1];

uint16_t adc_value_current_2[50];
uint16_t adc_current_2_max[1];

float Printer_Consumption;
float Printer_Current;

int tab_ADC[100];

extern int index_adc_current;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart2;

int i_current=0;
extern int current_breakdown;

int tab_ConsumptionValues[1000];
int Incorrect_Values=0;

void getElectricCurrentConsumption()
{
	/*Sensor 1 */
//	ADC_Select_CH4();
//
//	/* Sensor2 */
//	ADC_Select_CH5();
//
//	index_adc_current++;

	ADC_Select_CH5();

	if (i_current < 1000) // size of array
	{
		tab_ConsumptionValues[i_current] = Printer_Consumption;
		i_current+=1;
	}
	else {
		i_current = 0;
		Incorrect_Values = 0;
	}

	getElectricCurrentConsumptionTransmit();

	if(Printer_Consumption > 100) //100W we estimated no active printer for conso < 100watts
		Incorrect_Values+=1;

	//hh
}

void getElectricCurrentConsumptionTransmit()
{
//	for (int i = 0; i<index_adc_current; i++)
//	{
//		if (adc_value_current_1[i] > adc_current_1_max[0])
//			adc_current_1_max[0] = adc_value_current_1[i];
//		if (adc_value_current_2[i] > adc_current_2_max[0])
//			adc_current_2_max[0] = adc_value_current_2[i];
//	}
//
//	double ADC_1 = adc_current_1_max[0];
//	double ADC_1_offsetless = ADC_1 - 2048;
//	double electricCurrentVoltageReadSensor1 =  (ADC_1_offsetless * SETTING_VOLTAGE /  ADC_12BITS );
//	// 0A we have 1.65V
//	double electricCurrentValueSensor1 = electricCurrentVoltageReadSensor1 * 1 / 0.23 ;
//	double electricCurrentValueSensor1_Eff = electricCurrentValueSensor1 / sqrt(2) ;
//	//Calculation of power consumption in [W]
//	double getPowerConsumptionSensor1 =  (electricCurrentValueSensor1_Eff * ALIM_VOLTAGE);
//
//	if(getPowerConsumptionSensor1 > 500) current_breakdown = 1;
//	else current_breakdown = 0;
//
//	send_main_msg_current_EE(getPowerConsumptionSensor1,&huart2);
//
//	double ADC_2 = adc_current_2_max[0];
//	double ADC_2_offsetless = ADC_2 - 2048;
//	double electricCurrentVoltageReadSensor2 =  (ADC_2_offsetless * SETTING_VOLTAGE /  ADC_12BITS );
//	// 0A we have 1.65V
//	double electricCurrentValueSensor2 = electricCurrentVoltageReadSensor2 * 1 / 0.23 ; //0.23 = 3 tours : 0.076*3
//	double electricCurrentValueSensor2_Eff = electricCurrentValueSensor2 / sqrt(2) ;
//	//Calculation of power consumption in [W]
//	double getPowerConsumptionSensor2 =  (electricCurrentValueSensor2_Eff * ALIM_VOLTAGE);

//	if(getPowerConsumptionSensor2 > 500) current_breakdown = 1;
//	else current_breakdown = 0;

//	send_main_msg_current_printer(getPowerConsumptionSensor2,&huart2);

//	adc_current_1_max[0] = 0;
//	adc_current_2_max[0] = 0;
//	memset(adc_value_current_1, 0, sizeof(adc_value_current_1));
//	memset(adc_value_current_2, 0, sizeof(adc_value_current_2));


	float Voltage_Printer = (buf * SETTING_VOLTAGE) / ADC_12BITS;

//	float Voltage_Printer_Eff = Voltage_Printer / sqrt(2);

	float Diff_Potentiel = fabs((Voltage_Printer - VREF_CURRENT_2) * 1000); // *1000 -> mV

	Printer_Current = Diff_Potentiel / (3*GAIN); // 3*Gain -> 3 tours
	Printer_Consumption = Printer_Current * ALIM_VOLTAGE; // Attention for power voltage (220V-240V)

	//send_main_msg_current_printer(Printer_Consumption,&huart2);

}



void ADC_Select_CH5() // Consumption printer plug = Current 2
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
	HAL_ADC_PollForConversion(&hadc1, 1000);
	buf = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

}


//void ADC_Select_CH4() // Consumption EE = Current 1
//{
//	/*ADC_Current_2*/
//	/* Current1 Env */
//	ADC_ChannelConfTypeDef sConfig = {0};
//	  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//	  */
//	  sConfig.Channel = ADC_CHANNEL_4;
//	  sConfig.Rank = 1;
//	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//	  {
//	    Error_Handler();
//	  }
//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, 1000);
//	  buf[0] = HAL_ADC_GetValue(&hadc1);
//	  if(index_adc_current > 0)
//	  {
//			if (buf[0] + 2000 > adc_value_current_1[index_adc_current-1] && buf[0] - 2000 < adc_value_current_1[index_adc_current-1])
//			{
//				adc_value_current_1[index_adc_current] = buf[0];
//			}
//			else
//			{
//				adc_value_current_1[index_adc_current] = adc_value_current_1[index_adc_current-1];
//			}
//	  }
//	  else
//	  {
//		  adc_value_current_1[index_adc_current] = buf[0];
//	  }
//	  HAL_ADC_Stop(&hadc1);
//}


//void ADC_Select_CH5() // Consumption printer plug = Current 2
//{
//	ADC_ChannelConfTypeDef sConfig = {0};
//	/*ADC_Current_1*/
//	/* Current1 SE */
//	  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//	  */
//	  sConfig.Channel = ADC_CHANNEL_5;
//	  sConfig.Rank = 1;
//	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//	  {
//	    Error_Handler();
//	  }
//	  HAL_ADC_Start(&hadc1);
//	  HAL_ADC_PollForConversion(&hadc1, 1000);
//	  buf[0] = HAL_ADC_GetValue(&hadc1);
//	  if(index_adc_current > 0)
//	  {
//		  	if (buf[0] + 2000 > adc_value_current_2[index_adc_current-1] && buf[0] - 2000 < adc_value_current_2[index_adc_current-1])
//			{
//				adc_value_current_2[index_adc_current] = buf[0];
//			}
//			else
//			{
//				adc_value_current_2[index_adc_current] = adc_value_current_2[index_adc_current-1];
//			}
//	  }
//	  else
//	  {
//		  adc_value_current_2[index_adc_current] = buf[0];
//	  }
//	  HAL_ADC_Stop(&hadc1);
//
//}
