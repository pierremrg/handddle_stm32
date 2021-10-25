/* Handdle
 * Communication module
 * 2021
 */

#include "../../include/transport.h"

/** @def MAIN_MSG_TEMPERATURE
 *  @brief Main message ID for the temperature main message
 */
#define MAIN_MSG_TEMPERATURE 0x01

/** @def MAIN_MSG_HUMIDITY
 *  @brief Main message ID for the humidity main message
 */
#define MAIN_MSG_HUMIDITY 0x02

/** @def MAIN_MSG_TEMPERATURE_HUMIDITY
 *  @brief Main message ID for the message containing temperature and humity values
 */
#define MAIN_MSG_TEMPERATURE_HUMIDITY 0x03

/** @def MAIN_MSG_CURRENT_EE
 *  @brief Main message ID for the current main message
 */
#define MAIN_MSG_CURRENT_EE 0x04

/** @def MAIN_MSG_CURRENT_PRINTER
 *  @brief Main message ID for the current main message
 */
#define MAIN_MSG_CURRENT_PRINTER 0x05

/** @def MAIN_MSG_STATE_DOOR
 *  @brief Main message ID for the door state main message
 */
#define MAIN_MSG_STATE_DOOR 0x06

/** @def MAIN_MSG_POLLUTION
 *  @brief Main message ID for the pollution main message
 */
#define MAIN_MSG_POLLUTION 0x07

/** @def MAIN_MSG_SOUND
 *  @brief Main message ID for the sound main message
 */
#define MAIN_MSG_SOUND 0x08

/** @def MAIN_MSG_LED_COLOR
 *  @brief Main message ID for the led color main message
 */
#define MAIN_MSG_LED_COLOR 0x09

/** @def MAIN_MSG_PRINTING_STATE
 *  @brief Main message ID for the printing state main message
 */
#define MAIN_MSG_PRINTING_STATE 0x0A

/** @def MAIN_MSG_STATE_LATCH
 *  @brief Main message ID for the latch state main message
 */
#define MAIN_MSG_STATE_LATCH 0x0B



/** @fn int send_main_msg_temp(double temp,UART_HandleTypeDef * uart )
 * @brief Function used to send the temperature message
 * @param temp Temperature value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_temp(double temp, UART_HandleTypeDef * uart);

/** @fn int send_main_msg_hum(uint16_t hum,UART_HandleTypeDef * uart )
 * @brief Function used to send the humidity message
 * @param hum Humidity value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_hum(uint16_t hum,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_temp_hum(double temp,uint16_t hum,UART_HandleTypeDef * uart )
 * @brief Function used to send the Temperature and Humidity messages
 * @param temp Temperature value to be sent
 * @param hum Humidity value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_temp_hum(double temp,uint16_t hum,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_current_EE(double current,UART_HandleTypeDef * uart )
 * @brief Function used to send the current message
 * @param current Current value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_current_EE(double current,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_current_printer(double current,UART_HandleTypeDef * uart )
 * @brief Function used to send the current message
 * @param current Current value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_current_printer(double current,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_door_state(uint8_t door_state,UART_HandleTypeDef * uart )
 * @brief Function used to send the door state message
 * @param state_door Door state value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_door_state(uint8_t door_state,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_latch_state(uint8_t latch_state,UART_HandleTypeDef * uart )
 * @brief Function used to send the latch state message
 * @param latch state value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_latch_state(uint8_t latch_state,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_pollution(uint16_t pm10, uint16_t pm25,uint16_t pm100,UART_HandleTypeDef * uart )
 * @brief Function used to send the Pollution message
 * @param pm10 PM10 value to be sent
 * @param pm25 PM25 value to be sent
 * @param pm100 PM100 value to be sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_pollution(uint16_t pm10, uint16_t pm25,uint16_t pm100,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_sound(uint16_t sound,UART_HandleTypeDef * uart )
 * @brief Function used to send the Sound message
 * @param sound Sound value to sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_sound(uint16_t sound,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_led_color(uint16_t led_color,UART_HandleTypeDef * uart )
 * @brief Function used to send the Led color message
 * @param led_color Led color value to sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_led_color(uint16_t led_color,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_printing_state(uint8_t printig_state,uint8_t status,UART_HandleTypeDef * uart )
 * @brief Function used to send the Printing state message
 * @param printig_state Printing state value to sent
 * @param status Current status for the the given printig status: Begining, In progress and finished (Values to be determined)
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_printing_state(uint8_t printig_state,uint8_t status,UART_HandleTypeDef * uart );
