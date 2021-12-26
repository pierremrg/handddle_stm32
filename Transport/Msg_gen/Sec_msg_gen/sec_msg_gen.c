/* Handdle
 * Communication module
 * 2021
 */

#include "sec_msg_gen.h"
#include "../../include/msg_types.h"
#include "../../uid.h"

HAL_StatusTypeDef send_sec_msg_tachy_extract(uint16_t tachy_extract,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_tachy_extract[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4,  // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_TACHY_EXTRACT, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_tachy_extract[POS_DATA] = tachy_extract >> 8; // tachy_extract takes two bytes because it's a uint16_t value
	Tx_msg_tachy_extract[POS_DATA + 1] = tachy_extract;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_tachy_extract[i] = 0x00;

	Tx_msg_tachy_extract[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_tachy_extract,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_sec_msg_tachy_heating(uint16_t tachy_heating,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_tachy_heating[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4,  // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_TACHY_HEATING, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_tachy_heating[POS_DATA] = tachy_heating >> 8; // tachy_heating takes two bytes because it's a uint16_t value
	Tx_msg_tachy_heating[POS_DATA + 1] = tachy_heating;

	for(int i = POS_DATA + 2; i< MSG_SIZE; i++)
		Tx_msg_tachy_heating[i] = 0x00;

	Tx_msg_tachy_heating[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_tachy_heating,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_sec_msg_temp_rack(uint16_t temp_rack,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_temp_rack[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4,  // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_TEMP_RACK, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_temp_rack[POS_DATA] = temp_rack >> 8; // temp_rack takes two bytes because it's a uint16_t value
	Tx_msg_temp_rack[POS_DATA + 1] = temp_rack;

	for(int i = POS_DATA + 2; i< MSG_SIZE;i++)
		Tx_msg_temp_rack[i] = 0x00;

	Tx_msg_temp_rack[MSG_SIZE] = '\n';

	return HAL_UART_Transmit(uart,Tx_msg_temp_rack,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_sec_msg_temp_heating_resistor(uint16_t temp_heating_resistor,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_temp_heating_resistor[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4,  // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_TEMP_HEATING_RESISTOR, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_temp_heating_resistor[POS_DATA] = temp_heating_resistor >> 8; // temp_heating_resistor takes two bytes because it's a uint16_t value
	Tx_msg_temp_heating_resistor[POS_DATA + 1] = temp_heating_resistor;

	for(int i = POS_DATA + 2; i< MSG_SIZE;i++)
		Tx_msg_temp_heating_resistor[i] = 0x00;

	Tx_msg_temp_heating_resistor[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_temp_heating_resistor,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_sec_msg_pressure(int pressure,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_pressure[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4,  // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_PRESSURE, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	uint16_t pressure16 = (uint16_t) pressure + 50;
	Tx_msg_pressure[POS_DATA] = pressure16 >> 8; // pressure takes two bytes because it's a uint16_t value
	Tx_msg_pressure[POS_DATA + 1] = pressure16;

	for(int i = POS_DATA + 2; i< MSG_SIZE;i++)
		Tx_msg_pressure[i] = 0x00;

	Tx_msg_pressure[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_pressure,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_sec_msg_relay_state(uint16_t relay_state,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_relay_state[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4,  // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_RELAY_STATE, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_relay_state[POS_DATA] = relay_state >> 8; // relay_state takes two bytes because it's a uint16_t value
	Tx_msg_relay_state[POS_DATA + 1] = relay_state;

	for(int i = POS_DATA + 2; i< MSG_SIZE;i++)
		Tx_msg_relay_state[i] = 0x00;

	Tx_msg_relay_state[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_relay_state,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_sec_msg_buzzer_state(uint16_t buzzer_state,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_buzzer_state[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4,  // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_BUZZER_STATE, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_buzzer_state[POS_DATA] = buzzer_state >> 8; // buzzer_state takes two bytes because it's a uint16_t value
	Tx_msg_buzzer_state[POS_DATA + 1] = buzzer_state;

	for(int i = POS_DATA + 2; i< MSG_SIZE;i++)
		Tx_msg_buzzer_state[i] = 0x00;

	Tx_msg_buzzer_state[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_buzzer_state,MSG_SIZE+1,200);
}

HAL_StatusTypeDef send_sec_msg_preheat_over(uint16_t preheat_over,UART_HandleTypeDef * uart ){
	uint8_t Tx_msg_buzzer_state[MSG_SIZE + 1] = {
		MSG_HEADER_IDENTIFIER_1, MSG_HEADER_IDENTIFIER_2, MSG_HEADER_SIZE_1, MSG_HEADER_SIZE_2, // Global information
		MSG_HEADER_UID_1, MSG_HEADER_UID_2, MSG_HEADER_UID_3, MSG_HEADER_UID_4, // UID of the STM32
		MSG_TYPE_SECONDARY, // Message type
		SEC_MSG_PREHEAT_OVER, // Sub message type
		0x00, 0x02 // Length
	}; // 12 first bytes

	Tx_msg_buzzer_state[POS_DATA] = preheat_over >> 8; // buzzer_state takes two bytes because it's a uint16_t value
	Tx_msg_buzzer_state[POS_DATA + 1] = preheat_over;

	for(int i = POS_DATA + 2; i< MSG_SIZE;i++)
		Tx_msg_buzzer_state[i] = 0x00;

	Tx_msg_buzzer_state[MSG_SIZE] = '\n';
	return HAL_UART_Transmit(uart,Tx_msg_buzzer_state,MSG_SIZE+1,200);
}
