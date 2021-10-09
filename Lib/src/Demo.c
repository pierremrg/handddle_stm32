/*
 * Demo.c
 *
 *  Created on: Oct 6, 2021
 *      Author: Alternance
 */

#include "../Inc/main.h"

#include "../../Lib/inc/Pollution.h"
#include "../../Lib/inc/Lights.h"
#include "../../Lib/inc/ELN_temperature.h"
#include "../../Lib/inc/Microphone.h"

#define HEATER_ON  1
#define HEATER_OFF 0

void process_demo()
{

	/* SENSOR TEST */
		get_heater_temp();
		get_door_state();
		get_pollution();
		get_ELN_temp();
		get_listening();
		get_temp_humi_SHT40();
		get_pression();
		get_listening();
		getElectricCurrentConsumption();
		getElectricCurrentConsumptionTransmit();


		/* CYCLE 1 */


		/* TEST LIGHTS */


		int test_light = GREEN_FREE ;
		set_lights(test_light);

		for(int i = 0 ; i < 2 ; i++)
		{
			send_heater_temp();
			send_temp_humi();
			send_ELN_temp();
			send_humi();
			send_printer_state();
			send_temp();
			send_pollution();
			getElectricCurrentConsumption();
			getElectricCurrentConsumptionTransmit();
			HAL_Delay(5000);
		}





		/*
			CYCLE 2 : Production --- 2 min
		*/


		/* Heater Test + Fan Test */
		test_light = RED_PRINTING;
		set_lights(test_light);

		int test_heater_pwm = 50; // on peut aussi faire à 100%
		set_heater_pwm(&test_heater_pwm);
		int test_heater = HEATER_ON ; // Mise à ON du chauffage
		set_heater(&test_heater);

		for(int i = 0 ; i < 2 ; i++)
		{
			send_heater_temp();
			send_temp_humi();
			send_ELN_temp();
			send_humi();
			send_printer_state();
			send_temp();
			send_pollution();
			getElectricCurrentConsumption();
			getElectricCurrentConsumptionTransmit();
			HAL_Delay(5000);
		}

		test_heater = 0; // Mise à 0 du chauffage
		set_heater(&test_heater);

		for(int i = 0 ; i < 1 ; i++)
		{
			send_heater_temp();
			send_temp_humi();
			send_ELN_temp();
			send_humi();
			send_printer_state();
			send_temp();
			send_pollution();
			getElectricCurrentConsumption();
			getElectricCurrentConsumptionTransmit();
			HAL_Delay(10000);
		}

		test_heater_pwm = 0 ; // On eteind le chauffage et le ventilateur
		set_heater_pwm(&test_heater_pwm);

		for(int i = 0 ; i < 1 ; i++)
		{
			send_heater_temp();
			send_temp_humi();
			send_ELN_temp();
			send_humi();
			send_printer_state();
			send_temp();
			send_pollution();
			getElectricCurrentConsumption();
			getElectricCurrentConsumptionTransmit();
			HAL_Delay(10000);
		}

		/*
			CYCLE 3 : Dépollution --- 2 min
		*/


		test_light = ORANGE_STRAIGHT_DEFAULT;
		set_lights(test_light);

		int test_cooler_pwm = 70;
		set_cooling(&test_cooler_pwm);

		for(int i = 0 ; i < 2 ; i++)
		{
			send_heater_temp();
			send_temp_humi();
			send_ELN_temp();
			send_humi();
			send_printer_state();
			send_temp();
			send_pollution();
			getElectricCurrentConsumption();
			getElectricCurrentConsumptionTransmit();
			HAL_Delay(5000);
		}

		test_cooler_pwm = 0;
		set_cooling(&test_cooler_pwm);

		for(int i = 0 ; i < 1 ; i++)
		{
			send_heater_temp();
			send_temp_humi();
			send_ELN_temp();
			send_humi();
			send_printer_state();
			send_temp();
			send_pollution();
			getElectricCurrentConsumption();
			getElectricCurrentConsumptionTransmit();
			HAL_Delay(10000);
		}





		/*
			CYCLE 4 : Post Prod --- 2 min
		*/
		test_light = WHITE_PT;
		set_lights(test_light);

		test_cooler_pwm = 30;
		set_cooling(&test_cooler_pwm);

		for(int i = 0 ; i < 2 ; i++)
		{
			send_heater_temp();
			send_temp_humi();
			send_ELN_temp();
			send_humi();
			send_printer_state();
			send_temp();
			send_pollution();
			getElectricCurrentConsumption();
			getElectricCurrentConsumptionTransmit();
			HAL_Delay(10000);
		}

		test_cooler_pwm = 0;
		set_cooling(&test_cooler_pwm);

		HAL_Delay(5000);




		/*
			CYCLE 5 : Défaut --- 2 min
		*/



		for(int i = 0 ; i < 1 ; i++)
		{
			test_light = ORANGE_BLINKY_DEFAULT;
			set_lights(test_light);
			/* BUZZER TEST */
			send_heater_temp();
			send_temp_humi();
			send_ELN_temp();
			send_humi();
			send_printer_state();
			send_temp();
			send_pollution();

			if(i == 1 || i == 6 || i== 12) set_buzzer();

			getElectricCurrentConsumption();
			getElectricCurrentConsumptionTransmit();

			HAL_Delay(10000);
		}
}
