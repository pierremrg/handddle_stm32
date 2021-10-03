/* Handdle
 * Communication module
 * 2021
 */

#include "../../include/transport.h"

/** @def ERROR_MSG_TACHY_EXTRACT
 *  @brief Error ID for the tachy extraction error message
 */
#define ERROR_MSG_TACHY_EXTRACT 0x01

/** @def ERROR_MSG_HEATER
 *  @brief Error ID for the heater error message
 */
#define ERROR_MSG_HEATER 0x02

/** @def ERROR_MSG_TEMP_ENV
 *  @brief Error ID for the environment temperature error message
 */
#define ERROR_MSG_TEMP_ENV 0x03

/** @def ERROR_MSG_HUM_ENV
 *  @brief Error ID for the environment humidity error message
 */
#define ERROR_MSG_HUM_ENV 0x04

/** @def ERROR_MSG_HEATER_WARNING
 *  @brief Error ID for the heater warning message
 */
#define ERROR_MSG_HEATER_WARNING 0x05

/** @def ERROR_MSG_RACK_WARNING
 *  @brief Error ID for the rack warning message
 */
#define ERROR_MSG_RACK_WARNING 0x06

/** @fn int send_error_msg_tachy_extract(UART_HandleTypeDef * uart )
 * @brief Function used to send the tachy extraction error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_tachy_extract(UART_HandleTypeDef * uart );

/** @fn int send_error_msg_heater(UART_HandleTypeDef * uart )
 * @brief Function used to send the heater error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_heater(UART_HandleTypeDef * uart );

/** @fn int send_error_msg_temp_env(UART_HandleTypeDef * uart )
 * @brief Function used to send the environment temperature error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_temp_env(UART_HandleTypeDef * uart );

/** @fn int send_error_msg_hum_env(UART_HandleTypeDef * uart )
 * @brief Function used to send the environment humidity error message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_hum_env(UART_HandleTypeDef * uart );

/** @fn int send_error_msg_heater_warning(UART_HandleTypeDef * uart )
 * @brief Function used to send the heater warning message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_heater_warning(UART_HandleTypeDef * uart );

/** @fn int send_error_msg_rack_warning(UART_HandleTypeDef * uart )
 * @brief Function used to send the Rack warning message
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_error_msg_rack_warning(UART_HandleTypeDef * uart );
