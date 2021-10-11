/* Header
 * write stuff here
 * write stuff here
 */

#include "cmd_msg_parser.h"
#include "../../include/msg_types.h"
#include "../../uid.h"


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern uint8_t cmd_door_state;
extern int state;
extern float desired_temperature;
extern float desired_temperature_manual;
extern int dutycycle_cooling_manual;
extern int system_is_active;
extern int req_opening_door;
extern int manual_mode_filtration;
extern int manual_mode_temperature;
extern int CMD_Relay;


// Message ACK header
uint8_t msg_ack_cmd[MSG_SIZE + 1] = {
	MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
	MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
	MSG_TYPE_INFORMATION, // Message type
	CMD_ACK, // Sub message type
	0x00, 0x01 // Length
}; // 12 first bytes

void build_ack_msg_cmd(uint8_t ack){
	// Ack value
	msg_ack_cmd[POS_DATA] = ack;
	// Padding with zeros
	for (int i=POS_DATA + 1; i<MSG_SIZE; i++)
		msg_ack_cmd[i] = 0x00;

	msg_ack_cmd[MSG_SIZE] = '\n';
}

void send_cmd_ack(UART_HandleTypeDef * uart){
	build_ack_msg_cmd(0x01);
	HAL_UART_Transmit(uart, msg_ack_cmd, MSG_SIZE + 1, 200);
}

void send_cmd_nok(UART_HandleTypeDef * uart){
	build_ack_msg_cmd(0x00);
	HAL_UART_Transmit(uart, msg_ack_cmd, MSG_SIZE + 1, 200);
}

void parser_cmd_on_off(uint8_t * rx_buff,UART_HandleTypeDef * uart){
	system_is_active = rx_buff[POS_DATA];



	// Calling the function that will use the payload for the door command
	// power_on_off_cmd_received(rx_buff[4]);
}

void parser_cmd_door(uint8_t *rx_buff, UART_HandleTypeDef * uart){
	req_opening_door = rx_buff[POS_DATA];
	set_unlock(req_opening_door);
}

void parser_cmd_forcing_door(uint8_t *rx_buff, UART_HandleTypeDef * uart){
	cmd_door_state = rx_buff[POS_DATA];
	set_unlock(cmd_door_state);
}

void parser_cmd_temp(uint8_t *rx_buff,UART_HandleTypeDef * uart){
	// Compute the temperature value
//	if (manual_mode_temperature)
//	{
//		 desired_temperature_manual = rx_buff[POS_DATA]; // Attention uint8_t to float
//	}
//	else
//	{
//		if(rx_buff[POS_DATA] == AUTO_VALUE)
//		{
//			desired_temperature = get_temp_humi_SHT40();
//		}
//		else
//		{
//			desired_temperature = rx_buff[POS_DATA];
//		}
//	}

	desired_temperature = rx_buff[POS_DATA];
	set_heater_pwm(desired_temperature);
}

void parser_cmd_led_color(uint8_t *rx_buff,UART_HandleTypeDef * uart){
	set_lights(rx_buff[POS_DATA]);

	// Calling the function that will use the payload for the door command
	//led_color_cmd_received(led_color);
}

void parser_cmd_printing_state(uint8_t * rx_buff,UART_HandleTypeDef * uart){
	// Calling the function that will use the payload for the door command
	state = rx_buff[POS_DATA];
}

void parser_cmd_air_extract(uint8_t * rx_buff,UART_HandleTypeDef * uart){
	// Calling the function that will use the payload for the door command
	dutycycle_cooling_manual = rx_buff[POS_DATA];
	set_cooling(dutycycle_cooling_manual);
}

void parser_cmd_relay(uint8_t * rx_buff,UART_HandleTypeDef * uart){
	// Calling the function that will use the payload for the door command
	CMD_Relay = rx_buff[POS_DATA];
}


void parser_cmd(uint8_t * rx_buff, UART_HandleTypeDef * uart){
	uint8_t cmd_type = rx_buff[POS_MSG_SUBTYPE]; // The first byte has already been checked. We want the second one with the cmd type

	switch(cmd_type){
		case CMD_ON_OFF:
			parser_cmd_on_off(rx_buff, uart);
			send_cmd_ack(uart);
			break;
		case CMD_DOOR:
			parser_cmd_door(rx_buff, uart);
			send_cmd_ack(uart);
			break;
		case CMD_FORCING_DOOR:
			parser_cmd_forcing_door(rx_buff, uart);
			send_cmd_ack(uart);
			break;
		case CMD_TEMP:
			parser_cmd_temp(rx_buff, uart);
			send_cmd_ack(uart);
			break;
		case CMD_LED_COLOR:
			parser_cmd_led_color(rx_buff, uart);
			send_cmd_ack(uart);
			break;
		case CMD_PRINTING_STATE:
			parser_cmd_printing_state(rx_buff, uart);
			send_cmd_ack(uart);
			break;
		case CMD_AIR_EXTRACT:
			parser_cmd_air_extract(rx_buff, uart);
			send_cmd_ack(uart);
			break;
		case CMD_RELAY:
			parser_cmd_relay(rx_buff, uart);
			send_cmd_ack(uart);
			break;
		default:
			// Unknown command type -> Sending ACK NOK
			send_cmd_nok(uart);
	}

}



