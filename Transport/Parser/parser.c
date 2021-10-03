/* Handdle
 * Communication module
 * 2021
 */

#include "parser.h"
#include "Cmd_msg_parser/cmd_msg_parser.h"
#include "Info_msg_parser/info_msg_parser.h"
#include "../include/msg_types.h"


// Message ACK header
uint8_t msg_ack[MSG_SIZE + 1] = {
	MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
	MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
	MSG_TYPE_INFORMATION, // Message type
	0x00, // Sub message type
	0x00, 0x01 // Length
}; // 12 first bytes

// Function used to check the identifier of the messages
int check_msg_identifier(uint8_t * rx_buff){
	return rx_buff[POS_IDENTIFIER_1] == MSG_HEADER_IDENTIFIER_1 && rx_buff[POS_IDENTIFIER_2] == MSG_HEADER_IDENTIFIER_2;
}

// Function used to check the UID in the messages. If not the same as the one defined for the STM32, the message is not for us.
int check_msg_UID(uint8_t * rx_buff){
	return rx_buff[POS_UID_1] == MSG_HEADER_UID_1 && rx_buff[POS_UID_2] == MSG_HEADER_UID_2
			&& rx_buff[POS_UID_3] == MSG_HEADER_UID_3 && rx_buff[POS_UID_4] == MSG_HEADER_UID_4;
}

// The message has to be check because if it is not correct it might suggest that the code version are not the same between the STM32 and Jetson boards.
int check_msg_size(uint8_t * rx_buff){
	// TODO hard coded variables. It has to be changed using the MSG_SIZE constant!
	return rx_buff[POS_LENGTH_1] == 0x00 && rx_buff[POS_LENGTH_2] == 0x10;
}

// For every messages received, a ACK message is sent. If it is a OK ACK, it will have the cmd or info type.
void build_ack_msg(uint8_t ack){
	// Ack value
	msg_ack[POS_DATA] = ack;
	// Padding with zeros
	for (int i=POS_DATA + 1; i<MSG_SIZE; i++){
		msg_ack[i] = 0x00;
	}
}

// For every message received by the SMT32, there is a type defined
// Depending on the type defined, there are special parsers used to parse the message
void parser(uint8_t * rx_buff, UART_HandleTypeDef * uart){

	if(check_msg_identifier(rx_buff)){

		// This message is from the Jetson Nano
		if(check_msg_size(rx_buff)){

			// This message has the correct size
			if(check_msg_UID(rx_buff)){

				// This messages is for this STM32
				uint8_t msg_type = rx_buff[POS_MSG_TYPE];

				switch(msg_type){
				case MSG_TYPE_COMMAND:
					parser_cmd(rx_buff, uart);
					break;
				case MSG_TYPE_INFORMATION:
					parser_info(rx_buff, uart);
					break;
				default:
					// Unknown message --> Sending ACK NOK
					build_ack_msg(0x00);
					HAL_UART_Transmit(uart, msg_ack, MSG_SIZE, 200);
					break;
				}
			}
		}
	}
}
