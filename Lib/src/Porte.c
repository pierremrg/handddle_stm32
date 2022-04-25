#include "../../Lib/inc/Porte.h"

#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"

#define ERROR_CPT_1 2
#define ERROR_CPT_2 3

int latch_state;
int door_state;

int door1 = 0, latch1 = 0;
int door2 = 0, latch2 = 0;

extern int maximum_pollution;  // Is this needed to have max_pol for pm10 & pm25 & pm100 or just for one
extern UART_HandleTypeDef huart2;
extern uint16_t pm10[1];
extern uint16_t pm25[1];
extern uint16_t pm100[1];
extern int req_opening_door;
extern int DOOR_Previous_State;

extern TIM_HandleTypeDef htim1;
extern int i_timer1;
extern int compteur_buzzer, compteur_porte;
extern int CPT_CoolingDoorClosed;
extern int fermeture_porte;
extern int buzzer_state;

int light;
const int stop = 0, cooling = 100, cooling_40 = 40;

//TYPO : MACHINE
int prevDesiredTemp, prevHeaterActif, dutycycle_cooling, light;
int desired_temperature, heater_actif, prevDutyCCooling, prevLight = WHITE_PT;

uint8_t i_porte=1;


int get_door_state()
{
	// Door State 1
	if(HAL_GPIO_ReadPin(DOOR_STATUS1_GPIO_Port, DOOR_STATUS1_Pin))
		door1 = CLOSED; //value=1
	else
		door1 = OPEN; //value=0

	// Door State 2
	if(HAL_GPIO_ReadPin(DOOR_STATUS2_GPIO_Port, DOOR_STATUS2_Pin))
		door2 = CLOSED; //value=1
	else
		door2 = OPEN; //value=0

	// Return door satus
	if(door1 == CLOSED || door2 == CLOSED)
		door_state = CLOSED;
	else if(door1 == OPEN || door2 == OPEN)
		door_state = OPEN;

	return door_state;
}

int get_latch_state()
{
	// Latch state 1
	if(HAL_GPIO_ReadPin(LATCH_STATUS1_GPIO_Port, LATCH_STATUS1_Pin))
		latch1 = PRESENT;
	else latch1 = NOT_PRESENT;

	// Latch State 2
	if(HAL_GPIO_ReadPin(LATCH_STATUS2_GPIO_Port, LATCH_STATUS2_Pin))
		latch2 = PRESENT;
	else latch2 = NOT_PRESENT;

	// Return Latch State
	if(latch1 == PRESENT || latch2 == PRESENT)
		latch_state = PRESENT; //value=1
	else if(latch1 == NOT_PRESENT || latch2 == NOT_PRESENT)
		latch_state = NOT_PRESENT; //value=0

	return latch_state;
}


void set_unlock(uint8_t desired_door_state)
{
	if(desired_door_state == OPEN)
		HAL_GPIO_WritePin(CMD_PORTE_GPIO_Port, CMD_PORTE_Pin, GPIO_PIN_SET); // Door is unlocked
	else
		HAL_GPIO_WritePin(CMD_PORTE_GPIO_Port, CMD_PORTE_Pin, GPIO_PIN_RESET); // Door is locked
}

void door_cycle()
{
	int LATCH = get_latch_state();

	// CYCLE
	if (LATCH == NOT_PRESENT) 		// If door is open, on prend en compte que les latch
	{
		HAL_Delay(50);
		prevLight = light;
		set_lights(WHITE_DOOR_OPEN);
		if(buzzer_state){
			// Start Timer
			HAL_TIM_Base_Start_IT(&htim1);
		}
		set_unlock(CLOSED); //Lock
		CPT_CoolingDoorClosed = COOLING_T_DOOR_CLOSED; // Val COOLING_T_DOOR_CLOSED

		HAL_Delay(50);
		if(MSG_HEADER_UID_1 == TYPE_MACHINE_TOIT || MSG_HEADER_UID_1 == TYPE_MACHINE_RACK || MSG_HEADER_UID_1 == TYPE_POST_TREATMENT)
		{
			//STOP
			prevDesiredTemp = desired_temperature;
			prevDutyCCooling = dutycycle_cooling;

			if (i_porte == 1)
			{
				i_porte = 0;
				prevHeaterActif = heater_actif;
			}

			heater_actif = 0;
			set_cooling(0); //Force l'arret A CHANGE ! PT = 100 sinon 0
		} else{
			set_cooling(cooling);
		}
	}
	else if(LATCH == PRESENT){// If door is closed, On prend en compte que les latch
		// Stop Timer & buzzer
		i_porte = 1;
		stop_buzzer();
		if(compteur_porte != 0) // variable incrémentée quand la porte est ouverte => detecte la fermeture
		{
			compteur_buzzer=0; // reinit si la porte est fermée
			if(MSG_HEADER_UID_1 == TYPE_POST_TREATMENT)
			{
				if(CPT_CoolingDoorClosed > 0) // var qui va etre decrementée jusqua 0
				{
					set_lights(WHITE_PT);
					HAL_Delay(50); //Pour ne pas créer de bug
					set_cooling(cooling_40);
					fermeture_porte=1; // si = 1, CPT_CoolingDoorClosed va se decrementee de 1 toutes les secondes
				} else if(CPT_CoolingDoorClosed == 0) //, donc on a attendu X secondes apres fermeture de la porte
				{ // on reinit toutes les variables
					HAL_Delay(50); // pour ne pas créer de bug
					if (fermeture_porte == 1){
						set_cooling(cooling_40);
						compteur_porte = 0;
					}
					fermeture_porte=0; // si = 0, CPT_CoolingDoorClosed ne decremente pas

					if (prevLight != 0)
					{
						light = prevLight;
						set_lights(light);
						prevLight = 0;
					}
				}
			} else {
				compteur_porte = 0;
				HAL_TIM_Base_Stop_IT(&htim1);
				compteur_buzzer = 0; //en secondes
				if (prevLight != 0)
				{
					light = prevLight;
					set_lights(light);
					prevLight = 0;
				}
				HAL_Delay(100); //Pour ne pas créer de bug
				set_cooling(0); //A CHANGE ! PT = 100 sinon 0
			}
		} else
		{
			if((prevDesiredTemp != 0) && (prevHeaterActif == 1)) //22°C => definit comme temp amb dans main.c
			{
				heater_actif = 1;
				desired_temperature = prevDesiredTemp;
				asservissement(desired_temperature);
				prevDesiredTemp = 0;
			} else if ((prevDutyCCooling != 0) && (prevHeaterActif == 0))
			{
				dutycycle_cooling = prevDutyCCooling;
				set_cooling(dutycycle_cooling);
				prevDutyCCooling = 0;
			}
		}
	}
}


void send_door_state()
{
	get_door_state();

	if(door_state != DOOR_Previous_State)
	{
		DOOR_Previous_State = door_state;
		send_main_msg_door_state(door_state,&huart2);
	}
}

void send_latch_state()
{
	send_main_msg_latch_state(latch_state, &huart2);
}

//void send_pollution_ok_door()
//{
//	req_opening_door = 1;
//}
