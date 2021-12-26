/*
 * Typology.c
 *
 *  Created on: 20 déc. 2021
 *      Author: handddle
 */
#include "../../Lib/inc/Temp_humi.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"
#include "../../Transport/uid.h"

extern UART_HandleTypeDef huart2;

void send_typology(){
	send_main_msg_typology(MSG_HEADER_UID_1, &huart2);
}
