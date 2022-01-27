#include "../../Lib/inc/Relay.h"

#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Sec_msg_gen/sec_msg_gen.h"

extern UART_HandleTypeDef huart2;

extern uint16_t relay_state;

void set_shutdown_printer(int ON_off)
{
	if( ON_off == 1)
	{
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
		relay_state = 1;
	}
	else
	{
		HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
		relay_state = 0;
	}
}

void send_printer_state()
{
	send_sec_msg_relay_state(relay_state,&huart2);
}
