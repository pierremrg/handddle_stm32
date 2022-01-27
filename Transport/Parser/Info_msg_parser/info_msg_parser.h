/* Handdle
 * Communication module
 * 2021
 */

#include "../../include/transport.h"

/** @def INFO_ACK
 *  @brief Info ID for the ack when it's a information message
 */
#define INFO_ACK 0x00

/** @def INFO_MODE
 *  @brief Info ID day/night mode, information message
 */
#define INFO_NIGHT_MODE 0x01 //For the day or night mode

/** @def INFO_MANUAL_MODE_TEMPERATURE
 *  @brief Info ID for the manual or automatic mode, iformation message
 */
#define INFO_MANUAL_MODE_TEMPERATURE 0x02

/** @def INFO_MANUAL_MODE_FILTRATION
 *  @brief Info ID for the manual or automatic mode, iformation message
 */
#define INFO_MANUAL_MODE_FILTRATION 0x03

/** @def INFO_DOOR_STATE
 *  @brief Info ID for the manual or automatic mode, iformation message
 */
#define INFO_DOOR_STATE 0x05

/** @fn void parser_info_night_mode(uint8_t * rx_buff,UART_HandleTypeDef * uart )
 * @brief Parser for day/night mode information message.
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_info_night_mode(uint8_t * rx_buff,UART_HandleTypeDef * uart );

/** @fn void parser_info_manual_mode_temperature(uint8_t * rx_buff,UART_HandleTypeDef * uart )
 * @brief Parser for manual/automatic mode information message
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_info_manual_mode_temperature(uint8_t * rx_buff,UART_HandleTypeDef * uart );

/** @fn void parser_info_manual_mode_filtration(uint8_t * rx_buff,UART_HandleTypeDef * uart )
 * @brief Parser for manual/automatic mode information message
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_info_manual_mode_filtration(uint8_t * rx_buff,UART_HandleTypeDef * uart );

/** @fn void parser_info_pollution_threshold(uint8_t * rx_buff,UART_HandleTypeDef * uart )
 * @brief Parser for manual/automatic mode information message
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_info_pollution_threshold(uint8_t * rx_buff,UART_HandleTypeDef * uart );

/** @fn void parser_info_door_state(uint8_t * rx_buff,UART_HandleTypeDef * uart )
 * @brief Parser for manual/automatic mode information message
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_info_door_state(uint8_t * rx_buff,UART_HandleTypeDef * uart);

/** @fn void parser_info_mode(uint8_t * rx_buff,UART_HandleTypeDef * uart )
 * @brief General parser for information messages. This parser is called by the general parser for every information messages
 * @param rx_buff Pointer to the array tab containing the message received
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 */
void parser_info(uint8_t * rx_buff, UART_HandleTypeDef * uart);

/** @fn void build_ack_msg(uint8_t ack)
 * @brief Function used for the ack message, for the info type messages. If the message is not recognized, a NON ack is sent
 * @param ack Value for the ack message. 1 -> OK 0 -> NOK
 */
void build_ack_msg_info(uint8_t ack);
