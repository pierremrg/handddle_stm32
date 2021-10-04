#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"
#include "../inc/Lights.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart2;
extern int light;


void set_lights(int color)
{
	switch(color)
	{
		//Color : White - Porte Ouverte
	    case WHITE_DOOR_OPEN :
	    	//RED -- TIMER 2 CH1
	    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	    	htim2.Instance->CCR1 = 0; //Modulation
	    	//BLUE -- TIMER 4 CH3
	    	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	    	htim4.Instance->CCR3 = 0; //Modulation
	    	//GREEN TIMER 2 CH2
	    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	    	htim2.Instance->CCR2 = 0; //Modulation
	    	//WHITE -- TIMER 3 - CH3
	    	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	    	htim3.Instance->CCR3 = 100; //Modulation
	    	break;

	    //Color : White - Post Traitement
	    case WHITE_PT:
	    	//RED -- TIMER 2 CH1
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			htim2.Instance->CCR1 = 0; //Modulation
			//BLUE -- TIMER 4 CH3
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			htim4.Instance->CCR3 = 0; //Modulation
			//GREEN TIMER 2 CH2
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
			htim2.Instance->CCR2 = 0; //Modulation
			//WHITE -- TIMER 3 - CH3
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
			htim3.Instance->CCR3 = 60; //Modulation
			break;

	    //Color : RED - Print en cours
	    case RED_PRINTING:
	    	//RED -- TIMER 2 CH1
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			htim2.Instance->CCR1 = 100; //Modulation
			//BLUE -- TIMER 4 CH3
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			htim4.Instance->CCR3 = 0; //Modulation
			//GREEN TIMER 2 CH2
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
			htim2.Instance->CCR2 = 0; //Modulation
			//WHITE -- TIMER 3 - CH3
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
			htim3.Instance->CCR3 = 0; //Modulation
			break;

		//Color : Vert - Disponible
	    case GREEN_FREE:
	    	//RED -- TIMER 2 CH1
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			htim2.Instance->CCR1 = 0; //Modulation
			//BLUE -- TIMER 4 CH3
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			htim4.Instance->CCR3 = 0; //Modulation
			//GREEN TIMER 2 CH2
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
			htim2.Instance->CCR2 = 100; //Modulation
			//WHITE -- TIMER 3 - CH3
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
			htim3.Instance->CCR3 = 0; //Modulation
			break;

	    //Color : Orange - Default
	    case ORANGE_STRAIGHT_DEFAULT :
	    	//RED -- TIMER 2 CH1
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			htim2.Instance->CCR1 = 100; //Modulation
			//BLUE -- TIMER 4 CH3
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			htim4.Instance->CCR3 = 2; //Modulation
			//GREEN TIMER 2 CH2
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
			htim2.Instance->CCR2 = 58; //Modulation
			//WHITE -- TIMER 3 - CH3
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
			htim3.Instance->CCR3 = 0; //Modulation
			break;

		// Color : Bleu Handddle - Matière Première -- Validé
		case BLUE_HANDDDLE_MP:
			//RED -- TIMER 2 CH1
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			htim2.Instance->CCR1 = 14; //Modulation
			//BLUE -- TIMER 4 CH3
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			htim4.Instance->CCR3 = 45; //Modulation //75
			//GREEN TIMER 2 CH2
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
			htim2.Instance->CCR2 = 100; //Modulation //58 base
			//WHITE -- TIMER 3 - CH3
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
			htim3.Instance->CCR3 = 0; //Modulation

			break;

		// Color : Orange : Mouving
		 case ORANGE_BLINKY_DEFAULT :
			 // Clignotement ON
			//RED -- TIMER 2 CH1
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			htim2.Instance->CCR1 = 100; //Modulation
			//BLUE -- TIMER 4 CH3
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			htim4.Instance->CCR3 = 2; //Modulation
			//GREEN TIMER 2 CH2
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
			htim2.Instance->CCR2 = 58; //Modulation
			//WHITE -- TIMER 3 - CH3
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
			htim3.Instance->CCR3 = 0; //Modulation
			HAL_Delay(500);
			// Clignotement OFF
			//RED -- TIMER 2 CH1
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			htim2.Instance->CCR1 = 0; //Modulation
			//BLUE -- TIMER 4 CH3
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			htim4.Instance->CCR3 = 0; //Modulation
			//GREEN TIMER 2 CH2
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
			htim2.Instance->CCR2 = 0; //Modulation
			//WHITE -- TIMER 3 - CH3
			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
			htim3.Instance->CCR3 = 0; //Modulation
			HAL_Delay(500);
			break;

		 case WHITE_NIGHT_PT :
	    	//RED -- TIMER 2 CH1
	    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	    	htim2.Instance->CCR1 = 0; //Modulation
	    	//BLUE -- TIMER 4 CH3
	    	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	    	htim4.Instance->CCR3 = 0; //Modulation
	    	//GREEN TIMER 2 CH2
	    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	    	htim2.Instance->CCR2 = 0; //Modulation
	    	//WHITE -- TIMER 3 - CH3
	    	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	    	htim3.Instance->CCR3 = 30; //Modulation
	    	break;

		 case DARK :
	    	//RED -- TIMER 2 CH1
	    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	    	htim2.Instance->CCR1 = 0; //Modulation
	    	//BLUE -- TIMER 4 CH3
	    	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	    	htim4.Instance->CCR3 = 0; //Modulation
	    	//GREEN TIMER 2 CH2
	    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	    	htim2.Instance->CCR2 = 0; //Modulation
	    	//WHITE -- TIMER 3 - CH3
	    	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	    	htim3.Instance->CCR3 = 0; //Modulation
	    	break;

	    //Color : 30 % WHITE
	    default :
	    	//RED -- TIMER 2 CH1
	    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	    	htim2.Instance->CCR1 = 0; //Modulation
	    	//BLUE -- TIMER 4 CH3
	    	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	    	htim4.Instance->CCR3 = 0; //Modulation
	    	//GREEN TIMER 2 CH2
	    	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	    	htim2.Instance->CCR2 = 0; //Modulation
	    	//WHITE -- TIMER 3 - CH3
	    	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	    	htim3.Instance->CCR3 = 30; //Modulation
	    	break;
	}
}

void send_lights(int light)
{
	send_main_msg_led_color((uint16_t) light, &huart2);
}
