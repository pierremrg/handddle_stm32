/*
 * Weight.c
 *
 *      Author: Handddle
 */

#include "../../Lib/inc/Weight_HX711Config.h"
#include "../../Core/Inc/main.h"

#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"
#include "../inc/Weight_HX711.h"

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;

// HX711 : weight sensor
hx711_t loadcell;

float weight, weight_raw = 0;
int tare;
int tab_weight;
int average=0;
float y_tendance;


void Calibration()
{
	hx711_init(&loadcell, PSCK_Weight_GPIO_Port, PSCK_Weight_Pin, DATA_Weight_GPIO_Port, DATA_Weight_Pin);

	for(int i=0; i<10; i++)
	{
		tab_weight=hx711_weight(&loadcell, 1);
		average+=tab_weight;
	}

	average=average/10;
	hx711_calibration(&loadcell, average, average+221, 1); // iPhone 12 = 221g
	//hx711_calibration(&loadcell, average, average+1745, 1);

	//Tare
	hx711_tare(&loadcell, 1);
}

float get_weight()
{
	if(tare == 1)
	{
		weight_raw = hx711_weight(&loadcell, 1);
		tare = 0;
	}

	weight = hx711_weight(&loadcell, 1) - weight_raw;
	//y_tendance = 8.3091*weight-0.9388;
	//y_tendance = -9*pow(10,-6)*(weight*weight)+ 8.3141*weight - 1,1818;
	return weight;

}
void send_weight()
{
	send_main_msg_weight((uint16_t)weight*1.08064283066791 ,&huart2);
}
