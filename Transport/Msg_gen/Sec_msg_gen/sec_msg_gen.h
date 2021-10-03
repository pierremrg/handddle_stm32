/* Handdle
 * Communication module
 * 2021
 */

#include "../../include/transport.h"

/** @def SEC_MSG_TACHY_EXTRACT
 *  @brief Message ID for the tachy extraction secondary message
 */
#define SEC_MSG_TACHY_EXTRACT 0x01

/** @def SEC_MSG_TACHY_HEATING
 *  @brief Secondary message ID for the tachy heating secondary message
 */
#define SEC_MSG_TACHY_HEATING 0x02

/** @def SEC_MSG_TEMP_RACK
 *  @brief Secondary message ID for the rack temperature secondary message
 */
#define SEC_MSG_TEMP_RACK 0x03

/** @def SEC_MSG_TEMP_HEATING_RESISTOR
 *  @brief Secondary message ID for the heating resistor temperature secondary message
 */
#define SEC_MSG_TEMP_HEATING_RESISTOR 0x04

/** @def SEC_MSG_PRESSURE
 *  @brief Secondary message ID for the pressure secondary message
 */
#define SEC_MSG_PRESSURE 0x05

/** @def SEC_MSG_RELAY_STATE
 *  @brief Secondary message ID for the relay state secondary message
 */
#define SEC_MSG_RELAY_STATE 0x06

/** @def SEC_MSG_BUZZER_STATE
 *  @brief Secondary message ID for the buzzer state secondary message
 */
#define SEC_MSG_BUZZER_STATE 0x07

/** @def SEC_MSG_PREHEAT_OVER
 *  @brief Secondary message ID for the preheat state secondary message
 */
#define SEC_MSG_PREHEAT_OVER 0x08

/** @fn int send_sec_msg_tachy_extract(uint16_t tachy_extract,UART_HandleTypeDef * uart )
 * @brief Function used to send the Tachy Extraction message
 * @param tachy_extract Tachy extraction value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_sec_msg_tachy_extract(uint16_t tachy_extract,UART_HandleTypeDef * uart );

/** @fn int send_sec_msg_tachy_heating(uint16_t tachy_heating,UART_HandleTypeDef * uart )
 * @brief Function used to send the Tachy Heating message
 * @param tachy_heating Tachy heating value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_sec_msg_tachy_heating(uint16_t tachy_heating,UART_HandleTypeDef * uart );

/** @fn int send_sec_msg_temp_rack(uint16_t temp_rack,UART_HandleTypeDef * uart )
 * @brief Function used to send the rack temperature
 * @param temp_rack Rack temperature value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_sec_msg_temp_rack(uint16_t temp_rack,UART_HandleTypeDef * uart );

/** @fn int send_sec_msg_temp_heating_resistor(uint16_t temp_heating_resistor,UART_HandleTypeDef * uart )
 * @brief Function used to send the temperature on the heating resistor
 * @param temp_heating_resistor Heating resistor temperature value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_sec_msg_temp_heating_resistor(uint16_t temp_heating_resistor,UART_HandleTypeDef * uart );

/** @fn int send_sec_msg_pressure(int pressure,UART_HandleTypeDef * uart )
 * @brief Function used to send the rack temperature
 * @param pressure Pressure value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_sec_msg_pressure(int pressure,UART_HandleTypeDef * uart );

/** @fn int send_sec_msg_relay_state(uint16_t relay_state,UART_HandleTypeDef * uart )
 * @brief Function used to send the relay position
 * @param relay_state Relay position to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_sec_msg_relay_state(uint16_t relay_state,UART_HandleTypeDef * uart );

/** @fn int send_sec_msg_buzzer_state(uint16_t buzzer_state,UART_HandleTypeDef * uart )
 * @brief Function used to send the buzzer state
 * @param buzzer_state Buzzer state to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_sec_msg_buzzer_state(uint16_t buzzer_state,UART_HandleTypeDef * uart );

/** @fn int send_sec_msg_preheat_over(uint16_t preheat_over,UART_HandleTypeDef * uart )
 * @brief Function used to send the buzzer state
 * @param buzzer_state Buzzer state to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_sec_msg_preheat_over(uint16_t preheat_over,UART_HandleTypeDef * uart );
