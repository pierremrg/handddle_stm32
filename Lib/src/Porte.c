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
	int DOOR = get_door_state();

	// CYCLE
	if (LATCH == NOT_PRESENT || DOOR == OPEN) 		// If door is open
		set_unlock(CLOSED); 	//Lock
}


void send_door_state()
{
	send_main_msg_door_state(door_state,&huart2);
}

void send_latch_state()
{
	send_main_msg_latch_state(latch_state, &huart2);
}

//void send_pollution_ok_door()
//{
//	req_opening_door = 1;
//}
