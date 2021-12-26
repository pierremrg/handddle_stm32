/* Handdle
 * Communication module
 * 2021
 */

#include "../../include/transport.h"

/** @def CMD_ACK
 *  @brief Message ID for the ack when it's a command message
 */
#define CMD_ACK 0x00

/** @def CMD_ON_OFF
 *  @brief Command ID for the ON/OFF command message
 */
#define CMD_ON_OFF 0x01

/** @def CMD_DOOR
 *  @brief Command ID for the Door command message
 */
#define CMD_DOOR 0x02

/** @def CMD_FORCING_DOOR
 *  @brief Command ID for the forcing Door command message
 */
#define CMD_FORCING_DOOR 0x03

/** @def CMD_TEMP
 *  @brief Command ID for the temperature command message
 */
#define CMD_TEMP 0x04

/** @def CMD_LED_COLOR
 *  @brief Command ID for the led color command message
 */
#define CMD_LED_COLOR 0x05

/** @def CMD_PRINTING_STATE
 *  @brief Command ID for the printing state command message
 */
#define CMD_PRINTING_STATE 0x06

/** @def CMD_AIR_EXTRACT
 *  @brief Command ID for the air extraction command message
 */
#define CMD_AIR_EXTRACT 0x07

/** @def CMD_RELAY
 *  @brief Command ID for the relay command message
 */
#define CMD_RELAY 0x08

/** @def CMD_TARE
 *  @brief Command ID for the tare command message
 */
#define CMD_TARE 0x09

/** @def CMD_GET_WEIGHT
 *  @brief Command ID for the weight command message
 */
#define CMD_GET_WEIGHT 0x0A

/** @def CMD_UPDATE_WATCHDOG
 *  @brief Command ID for the watchdog
 */
#define CMD_UPDATE_WATCHDOG 0x0B

/** @def CMD_UPDATE_WATCHDOG
 *  @brief Command ID to force reset
 */
#define CMD_FORCE_RESET 0x0C

/** @def CMD_BUZZER
 *  @brief active or not buzzer
 */
#define CMD_BUZZER 0x0D


void parser_cmd_on_off(uint8_t * rx_buff,UART_HandleTypeDef * uart);


/** @fn void parser_cmd_door(uint8_t *rx_buff, UART_HandleTypeDef * uart)
 * @brief Parser function for the open/close door command message without forcing
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_door(uint8_t *rx_buff, UART_HandleTypeDef * uart);

/** @fn void parser_cmd_door(uint8_t *rx_buff, UART_HandleTypeDef * uart)
 * @brief Parser function for the forcing open/close door command message
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_forcing_door(uint8_t *rx_buff, UART_HandleTypeDef * uart);

/** @fn void parser_cmd_temp(uint8_t *rx_buff,UART_HandleTypeDef * uart)
 * @brief Parser function for the temperature command message
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_temp(uint8_t *rx_buff,UART_HandleTypeDef * uart);

/** @fn void parser_cmd_led_color(uint8_t *rx_buff,UART_HandleTypeDef * uart)
 * @brief Parser function for the led color command message
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_led_color(uint8_t *rx_buff,UART_HandleTypeDef * uart);

/** @fn void parser_cmd_printing_state(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 * @brief Parser function for the printing state command message
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_printing_state(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/** @fn void parser_cmd_relay(uint8_t * rx_buff,UART_HandleTypeDef * uart)
 * @brief Parser function for the relay state command message
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_cmd_relay(uint8_t * rx_buff,UART_HandleTypeDef * uart);


/** @fn void parser_cmd(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 * @brief General parser function used to dispatch every command message to the correct parser
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */

void parser_cmd_tare(uint8_t * rx_buff,UART_HandleTypeDef * uart);


/** @fn void parser_cmd(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 * @brief General parser function used to dispatch every command message to the correct parser
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */

void parser_cmd_buzzer(uint8_t * rx_buff, UART_HandleTypeDef * uart);

void parser_cmd_getWeight(uint8_t * rx_buff,UART_HandleTypeDef * uart);


void parser_cmd_update_watchdog(uint8_t * rx_buff,UART_HandleTypeDef * uart);

void parser_cmd_force_reset(uint8_t * rx_buff,UART_HandleTypeDef * uart);


void parser_cmd(uint8_t * rx_buff, UART_HandleTypeDef * uart);

/** @fn void build_ack_msg_cmd(uint8_t ack)
 * @brief Function used for the ack message, for command messages.
 * @param ack Value for the ack message. 1 -> OK 0 -> NOK
 */
void build_ack_msg_cmd(uint8_t ack);

void send_cmd_ack(UART_HandleTypeDef * uart);

void send_cmd_ack_with_value(UART_HandleTypeDef * uart, uint8_t value);

void send_cmd_nok(UART_HandleTypeDef * uart);
