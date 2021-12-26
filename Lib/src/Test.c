#include "../../Core/Inc/main.h"
#include "../../Lib/inc/Heater.h"
#include "../../Lib/inc/Cooling.h"
#include "../../Lib/inc/ELN_temperature.h"
#include "../../Lib/inc/Microphone.h"
#include "../../Lib/inc/Weight.h"
#include "../../Lib/inc/Fire.h"


void process_test()
{

	get_pollution();

//	ADC_Select_CH5();

	  /* SENSOR TEST */
//	get_heater_temp();
//	get_door_state();
//	get_pollution();
//	get_ELN_temp();
//	get_listening();
//	get_temp_humi_SHT40();
//	get_pression();
//	get_listening();




	/* Door TEST */
//	int test_unlock = 1;
//	set_unlock(&test_unlock);
//	test_unlock = 0;
//	set_unlock(&test_unlock);

//	int ab, lighty;
//	ab=get_door_state();
//
//
//	if(ab==0){
//		set_buzzer();
//		lighty = WHITE_DOOR_OPEN;
//		set_lights(lighty);}
//	else{
//		lighty = DARK;
//		set_lights(lighty);}


//	// Reset heater
//	int test_heater, test_heater_pwm;
//
//	test_heater = 1;
//	set_heater(&test_heater);

//	test_heater_pwm = 50;
//	set_heater_pwm(&test_heater_pwm);

	/* Cooling Test */
//	int test_cooler_pwm = 50;
//	set_cooling(&test_cooler_pwm);
//


//	set_buzzer();

//	HAL_Delay(2000);
//
//	test_cooler_pwm = 100;
//	set_cooling(&test_cooler_pwm);
//
//	HAL_Delay(5000);
//
//	test_cooler_pwm = 0;
//	set_cooling(&test_cooler_pwm);
//
//	HAL_Delay(5000);
//
//	/* RELAY TEST */
//	int activation_relay = 1 ;
//	set_shutdown_printer(&activation_relay);
//	HAL_Delay(5000);
//	activation_relay = 0 ;
//	set_shutdown_printer(&activation_relay);
//
//	/* BUZZER TEST */
//	set_buzzer();
//
//	/* LIGHTS TEST */
//	int test_light = 0;
//	set_lights(test_light);
//
//	HAL_Delay(1000);
//
//	test_light +=1 ; //1
//	set_lights(test_light);
//
//	HAL_Delay(1000);
//
//	test_light +=1 ; //2
//	set_lights(test_light);
//
//	HAL_Delay(1000);
//
//	test_light +=1 ; //3
//	set_lights(test_light);
//
//	HAL_Delay(1000);
//
//	test_light +=1 ; //4
//	set_lights(test_light);
//
//	HAL_Delay(1000);
//
//	test_light +=1 ; //5
//	set_lights(test_light);
//
//	HAL_Delay(1000);
}
