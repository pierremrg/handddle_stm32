/* Handdle
 * Communication module
 * 2021
 */

#include "stm32f4xx_hal.h"
#include "../uid.h"
#include "../include/transport.h"

/** @fn void parser(uint8_t * rx_buff, UART_HandleTypeDef * uart)
 * @brief General parser function used to dispatch every message to the correct parser depending on the message type
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser(uint8_t * rx_buff, UART_HandleTypeDef * uart);

/** @fn void build_ack_msg(uint8_t ack)
 * @brief General function used for the ack message. If the message is not recognized, a NON ack is sent
 * @param ack Value for the ack message. 1 -> OK 0 -> NOK
 */
void build_ack_msg(uint8_t ack);


