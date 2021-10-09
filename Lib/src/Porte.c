#include "../../Lib/inc/Porte.h"

#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"

#define ERROR_CPT_1 2
#define ERROR_CPT_2 3

extern int status;
extern int maximum_pollution;  // Is this needed to have max_pol for pm10 & pm25 & pm100 or just for one
extern UART_HandleTypeDef huart2;
extern uint16_t pm10[1];
extern uint16_t pm25[1];
extern uint16_t pm100[1];
extern int req_opening_door;


int get_door_state()
{
		int door1 = 0, door2 = 0, latch1 = 0, latch2 = 0;
//	int latch2 = 0;

	// Door State 1 -- Not Working because of the HW sensor
//		if(HAL_GPIO_ReadPin(GPIOC, DOOR_STATUS1_Pin))
//		{
//			door1 = 1;
//		}

	 //Latch state 1
		if(HAL_GPIO_ReadPin(GPIOC, LATCH_STATUS1_Pin))
		{
			latch1 = 1;
		}

	// Door State 2 -- Not Working because of the HW sensor
//		if(HAL_GPIO_ReadPin(GPIOA, DOOR_STATUS2_Pin))
//		{
//			door2 = 1;
//		}
	// Latch State 2
	if(HAL_GPIO_ReadPin(GPIOA, LATCH_STATUS2_Pin))
	{
		latch2 = 1;
	}


//	if (latch1 == 0  && latch2 == 0)
//			status = OPEN; //Open
//
//	if (latch1 == 0) // && latch2 == 1)
//		status = ERROR_CPT_1; //Error cpt Door1
//
//	if (latch1 == 1) // && latch2 == 0)
//		status = ERROR_CPT_2; //Error cpt Door2
//
//	if(latch1 == 1 && latch2 == 1)
//		status = CLOSED; //Close


	if ((latch2 == 0) || latch2 == 0)
		status = OPEN; //Open

	if ((latch2 == 1) || latch2 == 1)
		status = CLOSED; //Close

	return status;
}


void set_unlock(uint8_t desired_door_state)
{
	if(desired_door_state == OPEN)
		HAL_GPIO_WritePin(GPIOC, CMD_PORTE_Pin, GPIO_PIN_SET); // Door is unlocked
	else
		HAL_GPIO_WritePin(GPIOC, CMD_PORTE_Pin, GPIO_PIN_RESET); // Door is locked
}

void send_door_state()
{
	send_main_msg_state_door(status,&huart2);
}

//void send_pollution_ok_door()
//{
//	req_opening_door = 1;
//}
