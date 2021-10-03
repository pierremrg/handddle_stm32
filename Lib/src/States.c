#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"

#define DELTA 1.0 // desired_temperature Delta -- X-1 < X < X+1
#define REACHED_COUNTER_BUZZER 6 // Eq à 10 sec -- 60 pour 10 min
#define FINISH 2
#define IN_PROGRESS 1
#define BEGINNING 0

int counter_sensor = 0;
int cpt_send_preheat_over = 0;
int dutycycle_heater = 0;
int dutycycle_cooling = 0;
uint8_t response_req_door_opening = 0;
uint8_t lock = 0;
int advancement_state = 0;
int delay = 1000;
int heater_actif = 0;

/* Extern variables */
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart2;

/* State variable */
extern int state;
extern int preheat_over;

/* Pollution variables */
extern uint16_t pm10[1];
extern uint16_t pm25[1];
extern uint16_t pm100[1];
extern uint16_t pm10_th_limit;
extern uint16_t pm25_th_limit;
extern uint16_t pm100_th_limit;

/* Manual mode variables */
extern uint8_t manual_mode_filtration;
extern int manual_mode_temperature;
extern float desired_temperature_manual;
extern int dutycycle_cooling_manual;

/* Temperature variable */
extern float desired_temperature; // As to be a parameter linked to the Jetson Nano

/* Door variables */
extern int req_opening_door;
extern uint8_t cmd_door_state;
extern int req_opening_door;
extern int status;

/* Buzzer variables */
extern int buzzer_wait;
extern int cpt_buzzer_counter ;
extern uint16_t state_buzzer;

/* Light variable */
extern int light ;

/* Night mode variables */
extern int night_mode;

/* Delay Counter variable */
extern volatile int delay_counter;

void cycle(int *state)
{
	switch (*state)
	{

	/* CASE 0  - SETUP DATA*/

	/* Needs of maximum_pollution and a desired_temperature to go to the next step */
	/* This state can be skip thanks to the app */
	case 0 :
		light = RED_PRINTING;
		set_lights(light);
		if(desired_temperature != 0)
		{
			*state = 1;
			if(delay_counter == 0) send_main_msg_printing_state(*state,FINISH,&huart2);
			else if(delay_counter >= 10 )delay_counter = 0;
		}
		else
		{
			if(delay_counter == 0) send_main_msg_printing_state(*state,IN_PROGRESS,&huart2);
			else if(delay_counter >= 10 )delay_counter = 0;
		}
		if(status == 1)
		{
			 lock = 0 ;
			 set_unlock(lock);
		}
		break;

	/* ------------------------------------------------------------------------------------------------------------------*/
	/* ------------------------------------------------------------------------------------------------------------------*/

	/* CASE 1  - HEATING*/

	case 1 :
		if (status == 0) // CLOSE
		{
			buzzer_wait = 0 ;
			state_buzzer = 0;
			cpt_buzzer_counter = 0 ;
			light = 2 ;
			set_lights(light);
			float environment_temperature = get_temp_humi_SHT40();
			if(manual_mode_filtration == 1 && manual_mode_temperature != 1 )
			{
				//HEAT
				if (environment_temperature < (desired_temperature - DELTA))
				{
					heater_actif = 1;
					set_heater(&heater_actif);
					dutycycle_heater = 30;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = dutycycle_cooling_manual;
					set_cooling(&dutycycle_cooling);
				}
				//COOLING
				else if (environment_temperature > (desired_temperature + DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 0;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = dutycycle_cooling_manual;
					set_cooling(&dutycycle_cooling);
				}
				//REACHED_POINT
				else if (environment_temperature < (desired_temperature + DELTA) && environment_temperature > (desired_temperature - DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 30;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = dutycycle_cooling_manual;
					set_cooling(&dutycycle_cooling);
					/* Change of state */
					*state = 2 ;
				}
			 }
			 else if(manual_mode_temperature == 1 && manual_mode_filtration != 1 )
			 {
				//HEAT
				if (environment_temperature < (desired_temperature_manual - DELTA))
				{
					heater_actif = 1;
					set_heater(&heater_actif);
					dutycycle_heater = 30;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = 0;
					set_heater_pwm(&dutycycle_cooling);
				}
				//FAST-COOLING
				else if (environment_temperature > (desired_temperature_manual + 2*DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 0;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = 100;
					set_cooling(&dutycycle_cooling);

				}
				//COOLING
				else if (environment_temperature > (desired_temperature + DELTA) && environment_temperature < (desired_temperature + 2*DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 0;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = 50;
					set_cooling(&dutycycle_cooling);
				}
				//REACHED_POINT
				else if (environment_temperature < (desired_temperature_manual + DELTA) && environment_temperature > (desired_temperature_manual - DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 30;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = 50;
					set_cooling(&dutycycle_cooling);
					/* Change of state */
					*state = 2 ;
				}
			}
			else if (manual_mode_temperature == 1 && manual_mode_filtration == 1 )
			{
				//HEAT
				if (environment_temperature < (desired_temperature_manual - DELTA))
				{
					heater_actif = 1;
					set_heater(&heater_actif);
					dutycycle_heater = 30;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = dutycycle_cooling_manual;
					set_cooling(&dutycycle_cooling);
				}
				//COOLING
				else if (environment_temperature > (desired_temperature_manual + DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 0;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = dutycycle_cooling_manual;
					set_cooling(&dutycycle_cooling);
				}
				//REACHED_POINT
				else if (environment_temperature < (desired_temperature_manual + DELTA) && environment_temperature > (desired_temperature_manual - DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 30;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = dutycycle_cooling_manual;
					set_cooling(&dutycycle_cooling);
					/* Change of state */
					*state = 2 ;
				}
			}
			//Automatic Mode
			if(manual_mode_filtration == 0 && manual_mode_temperature == 0)
			{
				//Heat
				if (environment_temperature < (desired_temperature - DELTA))
				{
					heater_actif = 1;
					set_heater(&heater_actif);
					dutycycle_heater = 100;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = 0;
					set_cooling(&dutycycle_cooling);
				}
				//Fast-Cooling
				else if (environment_temperature > (desired_temperature + 2*DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 0;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = 100;
					set_cooling(&dutycycle_cooling);
				}
				//Cooling
				else if (environment_temperature > (desired_temperature + DELTA) && environment_temperature < (desired_temperature + 2*DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 0;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = 50;
					set_cooling(&dutycycle_cooling);
				}
				//Reached point
				else if (environment_temperature < (desired_temperature + DELTA) && environment_temperature > (desired_temperature - DELTA))
				{
					heater_actif = 0;
					set_heater(&heater_actif);
					dutycycle_heater = 20;
					set_heater_pwm(&dutycycle_heater);
					dutycycle_cooling = 0;
					set_cooling(&dutycycle_cooling);
					/* Change of state */
					*state = 2 ;
				}
			}
		}
		else if (status == 1) //OPEN
		{
			buzzer_wait = 1 ;
			if(cpt_buzzer_counter >= REACHED_COUNTER_BUZZER) // 10 sec * 60 = 10min
			{
				light = 6 ; // Blinky Orange
				set_lights(light);
				set_buzzer();
				state_buzzer = 1;
			}
			else
			{
				light = 0 ; // White
				set_lights(light);
			}
			lock = 0 ;
			set_unlock(lock);
		}
		break;

	/* ------------------------------------------------------------------------------------------------------------------*/
	/* ------------------------------------------------------------------------------------------------------------------*/

	/* CASE 2  - PRINTING*/
	case 2 :
		if (status == 0) // CLOSE
		{
			light = 2 ;
			set_lights(light);
			buzzer_wait = 0 ;
			state_buzzer = 0;
			preheat_over = 0;
			cpt_buzzer_counter = 0 ;
			if(req_opening_door == 0 ) //Req Opening -- NO -- HAVE TO WAIT FOR JOAO -- NOT NEEDED
			{
				float environment_temperature = get_temp_humi_SHT40();
				if(manual_mode_filtration == 1 && manual_mode_temperature != 1)
				{
					//HEAT
					if (environment_temperature < (desired_temperature - DELTA))
					{
						heater_actif = 1;
						set_heater(&heater_actif);
						dutycycle_heater = 30;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = dutycycle_cooling_manual;
						set_cooling(&dutycycle_cooling);
					}
					//COOLING
					else if (environment_temperature > (desired_temperature + DELTA))
					{
						heater_actif = 0;
						set_heater(&heater_actif);
						dutycycle_heater = 0;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = dutycycle_cooling_manual;
						set_cooling(&dutycycle_cooling);
					}
					//REACHED_POINT
					else if (environment_temperature < (desired_temperature + DELTA) && environment_temperature > (desired_temperature - DELTA))
					{
						heater_actif = 0;
						set_heater(&heater_actif);
						dutycycle_heater = 30;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = dutycycle_cooling_manual;
						set_cooling(&dutycycle_cooling);
					}
				 }
				 else if(manual_mode_temperature == 1 && manual_mode_filtration != 1 )
				  {
					//HEAT
					if (environment_temperature < (desired_temperature_manual - DELTA))
					{
						heater_actif = 1;
						set_heater(&heater_actif);
						dutycycle_heater = 50;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = 0;
						set_cooling(&dutycycle_cooling);
					}
					//COOLING
					else if (environment_temperature > (desired_temperature_manual + DELTA))
					{
						heater_actif = 0;
						set_heater(&heater_actif);
						dutycycle_heater = 0;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = 50;
						set_cooling(&dutycycle_cooling);
					}
					//REACHED_POINT
					else if (environment_temperature < (desired_temperature_manual + DELTA) && environment_temperature > (desired_temperature_manual - DELTA))
					{
						heater_actif = 0;
						set_heater(&heater_actif);
						dutycycle_heater = 30;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = 50;
						set_cooling(&dutycycle_cooling);
					}
				}
				else if (manual_mode_temperature == 1 && manual_mode_filtration == 1 )
				{
					//HEAT
					if (environment_temperature < (desired_temperature_manual - DELTA))
					{
						heater_actif = 1;
						set_heater(&heater_actif);
						dutycycle_heater = 30;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = dutycycle_cooling_manual;
						set_cooling(&dutycycle_cooling);
					}
					//COOLING
					else if (environment_temperature > (desired_temperature_manual + DELTA))
					{
						heater_actif = 0;
						set_heater(&heater_actif);
						dutycycle_heater = 0;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = dutycycle_cooling_manual;
						set_cooling(&dutycycle_cooling);
					}
					//REACHED_POINT
					else if (environment_temperature < (desired_temperature_manual + DELTA) && environment_temperature > (desired_temperature_manual - DELTA))
					{
						heater_actif = 0;
						set_heater(&heater_actif);
						dutycycle_heater = 30;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = dutycycle_cooling_manual;
						set_cooling(&dutycycle_cooling);
					}
				}
				//Automatic Mode
				if(manual_mode_filtration == 0 && manual_mode_temperature == 0)
				{
					if (environment_temperature < (desired_temperature - DELTA))
					{
						heater_actif = 1;
						set_heater(&heater_actif);
						dutycycle_heater = 30;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = 0;
						set_cooling(&dutycycle_cooling);
					}
					else if (environment_temperature > (desired_temperature + DELTA))
					{
						heater_actif = 0;
						set_heater(&heater_actif);
						dutycycle_heater = 0;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = 50;
						set_cooling(&dutycycle_cooling);
					}
					else if (environment_temperature < (desired_temperature + DELTA) && environment_temperature > (desired_temperature - DELTA))
					{
						heater_actif = 0;
						set_heater(&heater_actif);
						dutycycle_heater = 30;
						set_heater_pwm(&dutycycle_heater);
						dutycycle_cooling = 30;
						set_cooling(&dutycycle_cooling);
					}
				}
			}
			else //Req Opening -- YES -- HAVE TO WAIT FOR JOAO
			{
				get_pollution();
				if (pm10[0] < pm10_th_limit && pm25[0] < pm25_th_limit && pm100[0]< pm100_th_limit)
				{
					set_unlock(response_req_door_opening);
				}
				else
				{
					dutycycle_cooling = 50;
					set_cooling(&dutycycle_cooling);
				}
			}
		}
		else if (status == 1) //OPEN
		{
			buzzer_wait = 1 ;
			req_opening_door = 0;
			if(cpt_buzzer_counter >= REACHED_COUNTER_BUZZER) // 10 sec * 60 = 10min
			{
				light = 6 ; // Blinky Orange
				set_lights(light);
				set_buzzer();
				state_buzzer = 1;
			}
			else
			{
				light = 0 ; // White
				set_lights(light);
			}
			dutycycle_cooling = 50;
			set_cooling(&dutycycle_cooling);
			lock = 0 ;
			set_unlock(lock);

		}
		break;

	/* ------------------------------------------------------------------------------------------------------------------*/
	/* ------------------------------------------------------------------------------------------------------------------*/

	/* CASE 3  - POST TREATMENT */
	case 3 :
		if (night_mode == 0)
		{
			light = 1 ; // WHITE PT
			set_lights(light);
			if(status == 0) //CLOSE
			{
				dutycycle_cooling = 100;
				set_cooling(&dutycycle_cooling);
				get_pollution();
				if(pm10[1] > pm10_th_limit && pm25[1] > pm25_th_limit && pm100[1] > pm100_th_limit)
				{
					set_buzzer();
					state_buzzer = 1;
				}
				else state_buzzer = 0;
			}
			else
			{
				dutycycle_cooling = 30;
				set_cooling(&dutycycle_cooling);
				lock = 0;
				set_unlock(lock);
			}
		}
		else
		{
			light = 7 ; // WHITE NIGHT PT
			set_lights(light);
			dutycycle_cooling = 20;
			set_cooling(&dutycycle_cooling);
			lock = 0 ;
			set_unlock(lock);
		}
		break;

	//Wait state
	default :

		/* Stop actuators */
		heater_actif = 0 ;
		set_heater(&heater_actif);
		light = 3 ;
		set_lights(light);
		dutycycle_heater = 0;
		set_cooling(&dutycycle_heater);
		dutycycle_cooling = 0;
		set_cooling(&dutycycle_cooling);

		/*Re Initialization of the variables of the Setup-Up State */
		desired_temperature = 0;
		pm10_th_limit = 1000;
		pm25_th_limit = 1000;
		pm100_th_limit = 1000;

	}
}
//
//void send_cycle()
//{
//	send_main_msg_printing_state(state, advancement_state, &huart2);
//}
