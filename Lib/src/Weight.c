/*
 * Weight.c
 *
 *  Created on: Aug 13, 2021
 *      Author: marti
 */


#include "../../Lib/inc/Weight_HX711Config.h"
#include "../../Core/Inc/main.h"

#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"
#include "../inc/Weight_HX711.h"

#define DELTA 3

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;

//uint8_t moy_weight = 0;

// HX711 : weight sensor
hx711_t loadcell;

float weight, weight_raw;
int tare;
int tab_weight;


void Calibration()
{
	hx711_init(&loadcell, PSCK_Weight_GPIO_Port, PSCK_Weight_Pin, DATA_Weight_GPIO_Port, DATA_Weight_Pin);

	int average=0;
	for(int i=0; i<10; i++)
	{
		tab_weight=hx711_weight(&loadcell, 1);
		average+=tab_weight;
	}

	average=average/10;
	hx711_calibration(&loadcell, average, average+221, 1); // iPhone 12 = 221g

	//Tare
	hx711_tare(&loadcell, 10);
}

float get_weight()
{
	weight_raw = 0;

	if(tare == 1)
	{
		weight_raw = hx711_weight(&loadcell, 1);
		tare = 0;
	}

	weight = hx711_weight(&loadcell, 1) - weight_raw;
	return weight;

}
void send_weight()
{
	send_main_msg_weight((uint16_t)weight + DELTA,&huart2);
}

