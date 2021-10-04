/* Handdle
 * Communication module
 * 2021
 */

#include "error_msg_gen.h"
#include "../../include/msg_types.h"
#include "../../uid.h"

HAL_StatusTypeDef send_error_msg_tachy_extract(UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_error_tachy_extract[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_ERROR, // Message type
		ERROR_MSG_TACHY_EXTRACT, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

	for(int i = POS_DATA; i< MSG_SIZE; i++)
		Tx_msg_error_tachy_extract[i] = 0x00;

	Tx_msg_error_tachy_extract[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_error_tachy_extract,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_error_msg_heater(UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_error_heater[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_ERROR, // Message type
		ERROR_MSG_HEATER, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

	for(int i = POS_DATA; i< MSG_SIZE; i++)
		Tx_msg_error_heater[i] = 0x00;

	Tx_msg_error_heater[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_error_heater,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_error_msg_temp_env(UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_error_temp_env[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_ERROR, // Message type
		ERROR_MSG_TEMP_ENV, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

	for(int i = POS_DATA; i< MSG_SIZE; i++)
		Tx_msg_error_temp_env[i] = 0x00;

	Tx_msg_error_temp_env[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_error_temp_env,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_error_msg_hum_env(UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_error_hum_env[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_ERROR, // Message type
		ERROR_MSG_HUM_ENV, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

	for(int i = POS_DATA; i< MSG_SIZE; i++)
		Tx_msg_error_hum_env[i] = 0x00;

	Tx_msg_error_hum_env[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_error_hum_env,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_error_msg_heater_warning(UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_error_heater_warning[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_ERROR, // Message type
		ERROR_MSG_HEATER_WARNING, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

	for(int i = POS_DATA; i< MSG_SIZE; i++)
		Tx_msg_error_heater_warning[i] = 0x00;

	Tx_msg_error_heater_warning[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_error_heater_warning,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_error_msg_rack_warning(UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_error_rack_warning[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_ERROR, // Message type
		ERROR_MSG_RACK_WARNING, // Sub message type
		0x00, 0x01 // Length
	}; // 12 first bytes

	for(int i = POS_DATA; i< MSG_SIZE; i++)
		Tx_msg_error_rack_warning[i] = 0x00;

	Tx_msg_error_rack_warning[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_error_rack_warning,MSG_SIZE+1,200);
}
