/* Handdle
 * Communication module
 * 2021
 */

#include "main_msg_gen.h"
#include "../../include/msg_types.h"
#include "../../uid.h"

HAL_StatusTypeDef send_main_msg_temp(double temp,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_temp[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_TEMPERATURE, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	uint16_t temp16 = (uint16_t) temp * 100;
	Tx_msg_temp[12] = temp16 >> 8; // temp takes two bytes because it's a uint16_t value
	Tx_msg_temp[13] = temp16;

	for(int i = 14; i<MSG_SIZE; i++)
		Tx_msg_temp[i] = 0x00;

	Tx_msg_temp[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart, Tx_msg_temp, MSG_SIZE + 1, 200);
}

HAL_StatusTypeDef send_main_msg_hum(uint16_t hum,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_hum[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_HUMIDITY, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_hum[POS_DATA] = hum >> 8; // hum takes two bytes because it's a uint16_t value
	Tx_msg_hum[POS_DATA + 1] = hum;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_hum[i] = 0x00;

	Tx_msg_hum[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_hum,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_temp_hum(double temp,uint16_t hum,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_temp_hum[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_TEMPERATURE_HUMIDITY, // Sub message type
		0x00, 0x04 // Length
	}; // 12 first bytes

	uint16_t temp16 = (uint16_t) temp * 100;
	Tx_msg_temp_hum[POS_DATA] = temp16 >> 8; // temp takes two bytes because it's a uint16_t value
	Tx_msg_temp_hum[POS_DATA + 1] = temp16;
	Tx_msg_temp_hum[POS_DATA + 2] = hum >> 8; // hum takes two bytes because it's a uint16_t value
	Tx_msg_temp_hum[POS_DATA + 3] = hum;

	for(int i = POS_DATA + 4; i< MSG_SIZE; i++)
		Tx_msg_temp_hum[i] = 0x00;

	Tx_msg_temp_hum[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_temp_hum,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_current_EE(double current,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_current[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_CURRENT_EE, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	uint16_t current_uint16 = (uint16_t) current;
	Tx_msg_current[POS_DATA] = current_uint16 >> 8; // current takes two bytes because it's a uint16_t value
	Tx_msg_current[POS_DATA + 1] = current_uint16;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_current[i] = 0x00;

	Tx_msg_current[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_current,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_current_printer(double current,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_current[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_CURRENT_PRINTER, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	uint16_t current_uint16 = (uint16_t) current;
	Tx_msg_current[POS_DATA] = current_uint16 >> 8; // current takes two bytes because it's a uint16_t value
	Tx_msg_current[POS_DATA + 1] = current_uint16;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_current[i] = 0x00;

	Tx_msg_current[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_current,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_door_state(uint8_t door_state,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_state_door[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_STATE_DOOR, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

	Tx_msg_state_door[POS_DATA] = door_state;

	for(int i = POS_DATA + 1; i< MSG_SIZE; i++)
		Tx_msg_state_door[i] = 0x00;

	Tx_msg_state_door[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_state_door,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_latch_state(uint8_t latch_state,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_state_latch[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_STATE_LATCH, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

	Tx_msg_state_latch[POS_DATA] = latch_state;

	for(int i = POS_DATA + 1; i< MSG_SIZE; i++)
		Tx_msg_state_latch[i] = 0x00;

	Tx_msg_state_latch[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_state_latch,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_weight(uint16_t weight,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_weight[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_WEIGHT, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_weight[POS_DATA] = weight >> 8; // weight takes two bytes because it's a uint16_t value
	Tx_msg_weight[POS_DATA + 1] = weight;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_weight[i] = 0x00;

	Tx_msg_weight[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_weight,MSG_SIZE+1,200);
}


HAL_StatusTypeDef send_main_msg_pm1_0(uint16_t pm1_0, UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_pm1_0[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_PM1_0, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_pm1_0[POS_DATA] = pm1_0 >> 8; // weight takes two bytes because it's a uint16_t value
	Tx_msg_pm1_0[POS_DATA + 1] = pm1_0;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_pm1_0[i] = 0x00;

	Tx_msg_pm1_0[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_pm1_0,MSG_SIZE+1,200);
}


HAL_StatusTypeDef send_main_msg_pm2_5(uint16_t pm2_5, UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_pm2_5[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_PM2_5, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_pm2_5[POS_DATA] = pm2_5 >> 8; // weight takes two bytes because it's a uint16_t value
	Tx_msg_pm2_5[POS_DATA + 1] = pm2_5;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_pm2_5[i] = 0x00;

	Tx_msg_pm2_5[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_pm2_5,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_pm10(uint16_t pm10, UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_pm10[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_PM10, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_pm10[POS_DATA] = pm10 >> 8; // weight takes two bytes because it's a uint16_t value
	Tx_msg_pm10[POS_DATA + 1] = pm10;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_pm10[i] = 0x00;

	Tx_msg_pm10[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_pm10,MSG_SIZE+1,200);
}


HAL_StatusTypeDef send_main_msg_sound(uint16_t sound,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_sound[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_SOUND, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_sound[POS_DATA] = sound >> 8; // sound takes two bytes because it's a uint16_t value
	Tx_msg_sound[POS_DATA + 1] = sound;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_sound[i] = 0x00;

	Tx_msg_sound[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_sound,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_led_color(uint16_t led_color,UART_HandleTypeDef * uart){
	uint8_t Tx_msg_led_color[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_LED_COLOR, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_led_color[POS_DATA] = led_color >> 8; // led_color takes two bytes because it's a uint16_t value
	Tx_msg_led_color[POS_DATA + 1] = led_color;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_led_color[i] = 0x00;

	Tx_msg_led_color[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_led_color,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_main_msg_printing_state(uint8_t printing_state,uint8_t status,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_printing_state[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_MAIN, // Message type
		MAIN_MSG_PRINTING_STATE, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_printing_state[POS_DATA] = printing_state;
	Tx_msg_printing_state[POS_DATA + 1] = status;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_printing_state[i] = 0x00;

	Tx_msg_printing_state[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_printing_state,MSG_SIZE+1,200);
}
