/* Handdle
 * Communication module
 * 2021
 */

#include "info_msg_parser.h"
#include "../../include/msg_types.h"

extern uint8_t manual_mode_filtration;
extern int manual_mode_temperature;
extern int night_mode;
extern uint16_t pm10_th_limit;
extern uint16_t pm25_th_limit;
extern uint16_t pm100_th_limit;
extern int status;

uint8_t msg_ack_info[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_INTERNAL, // Message type
		INFO_ACK, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

void build_ack_msg_info(uint8_t ack){
	// Ack value
	msg_ack_info[12] = ack;
	// Padding with zeros
	for (int i=13; i<MSG_SIZE;i++)
		msg_ack_info[i] = 0x00;
}

void parser_info_night_mode(uint8_t * rx_buff,UART_HandleTypeDef * uart){
	if((rx_buff[POS_MSG_TYPE] == MSG_TYPE_INFORMATION) && (rx_buff[POS_MSG_SUBTYPE] == INFO_NIGHT_MODE)){
		build_ack_msg_info(0x01);
		HAL_UART_Transmit(uart,msg_ack_info,MSG_SIZE,200);

		night_mode = rx_buff[POS_DATA];

		// Calling the function that will use the payload for the door command
		//info_mode_night_received(rx_buff[4]);
	}
}

//manual_mode_temperature
void parser_info_manual_mode_temperature(uint8_t * rx_buff,UART_HandleTypeDef * uart){
	if((rx_buff[POS_MSG_TYPE] == MSG_TYPE_INFORMATION) && (rx_buff[POS_MSG_SUBTYPE] == INFO_MANUAL_MODE_TEMPERATURE)){
		build_ack_msg_info(0x01);
		HAL_UART_Transmit(uart,msg_ack_info,MSG_SIZE,200);

		manual_mode_temperature = rx_buff[POS_DATA];

		// Calling the function that will use the payload for the door command
		//info_mode_manual_received(rx_buff[4]);
	}
}


 //manual_mode_filtration
void parser_info_manual_mode_filtration(uint8_t * rx_buff,UART_HandleTypeDef * uart){
	if((rx_buff[POS_MSG_TYPE] == MSG_TYPE_INFORMATION) && (rx_buff[POS_MSG_SUBTYPE] == INFO_MANUAL_MODE_FILTRATION)){
		build_ack_msg_info(0x01);
		HAL_UART_Transmit(uart,msg_ack_info,MSG_SIZE,200);

		manual_mode_filtration = rx_buff[POS_DATA];
		// Calling the function that will use the payload for the door command
		//info_mode_manual_received(rx_buff[4]);
	}
}

void parser_info_pollution_threshold(uint8_t * rx_buff,UART_HandleTypeDef * uart ){
	uint16_t pm10_th, pm25_th, pm100_th;

	if((rx_buff[POS_MSG_TYPE] == MSG_TYPE_INFORMATION) && (rx_buff[POS_MSG_SUBTYPE] == INFO_POLLUTION_THRESHOLD)){
		build_ack_msg_info(0x01);
		HAL_UART_Transmit(uart,msg_ack_info,MSG_SIZE,200);

		// For PM10 threshold
		if(rx_buff[POS_DATA] != AUTO_VALUE || rx_buff[POS_DATA + 1] != AUTO_VALUE){
			pm10_th = rx_buff[4];
			pm10_th = pm10_th << 8;
			pm10_th = pm10_th | rx_buff[5];

			// Call function for PM10 threshold here
			pm10_th_limit = pm10_th;
		}

		// For PM25 threshold
		if(rx_buff[POS_DATA + 2] != AUTO_VALUE || rx_buff[POS_DATA + 3] != AUTO_VALUE){
			pm25_th = rx_buff[6];
			pm25_th = pm25_th << 8;
			pm25_th = pm25_th | rx_buff[7];

			// Call function for PM25 threshold here
			pm25_th_limit = pm25_th;
		}

		// For PM100 threshold
		if(rx_buff[POS_DATA + 5] != AUTO_VALUE || rx_buff[POS_DATA + 6] != AUTO_VALUE){
			pm100_th = rx_buff[8];
			pm100_th = pm100_th << 8;
			pm100_th = pm100_th | rx_buff[9];

			// Call function for PM100 threshold here
			pm100_th_limit = pm100_th;
		}
	}
}

void parser_info_door_state(uint8_t * rx_buff,UART_HandleTypeDef * uart){
	if((rx_buff[POS_MSG_TYPE] == MSG_TYPE_INFORMATION) && (rx_buff[POS_MSG_SUBTYPE] == INFO_DOOR_STATE)){
		build_ack_msg_info(0x01);
		HAL_UART_Transmit(uart,msg_ack_info,MSG_SIZE,200);

		status = rx_buff[POS_DATA];
		// Calling the function that will use the payload for the door command
		// info_mode_manual_received(rx_buff[4]);
	}
}

void parser_info(uint8_t * rx_buff, UART_HandleTypeDef * uart){
	uint8_t info_type = rx_buff[1]; // No need to check the first byte.
	switch(info_type){
	case (INFO_NIGHT_MODE):
				parser_info_night_mode(&rx_buff[0],uart);
	break;
	case (INFO_MANUAL_MODE_TEMPERATURE):
				parser_info_manual_mode_temperature(&rx_buff[0],uart);
	break;
	case (INFO_MANUAL_MODE_FILTRATION):
				parser_info_manual_mode_filtration(&rx_buff[0],uart);
	break;
	case (INFO_POLLUTION_THRESHOLD):
			parser_info_pollution_threshold(&rx_buff[0],uart);
	break;
	case (INFO_DOOR_STATE):
			parser_info_door_state(&rx_buff[0],uart);
	break;
	default:
		//Info not known  -> Sending ack :NOK
		build_ack_msg_info(0x00);
		HAL_UART_Transmit(uart,msg_ack_info,MSG_SIZE,200);
	}
}
