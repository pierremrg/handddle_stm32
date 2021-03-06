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

/** @def MAIN_MSG_WEIGHT
 *  @brief Main message ID for the weight
 */
#define MAIN_MSG_WEIGHT 0x0C

/** @def MAIN_MSG_PM1_0
 *  @brief Main message ID for the pollution rate
 */
#define MAIN_MSG_PM1_0 0x0D

/** @def MAIN_MSG_PM2_5
 *  @brief Main message ID for the pollution rate
 */
#define MAIN_MSG_PM2_5 0x0E

/** @def MAIN_MSG_PM10
 *  @brief Main message ID for the pollution rate
 */
#define MAIN_MSG_PM10 0x0F

/** @def MAIN_MSG_INCENDIE_CO2
 *  @brief Main message ID for the weight
 */
#define MAIN_MSG_INCENDIE_CO2 0x10

/** @def MAIN_MSG_INCENDIE_TVOC
 *  @brief Main message ID for the weight
 */
#define MAIN_MSG_INCENDIE_TVOC 0x11

/** @def MAIN_MSG_TVOC_WARNING
 *  @brief Main message ID for the weight
 */
#define MAIN_MSG_TVOC_WARNING 0x12

/** @def MAIN_MSG_CO2_WARNING
 *  @brief Main message ID for the weight
 */
#define MAIN_MSG_CO2_WARNING 0x13

/** @def MAIN_MSG_TYPOLOGY
 *  @brief Main message ID for the weight
 */
#define MAIN_MSG_TYPOLOGY 0x14



/** @fn int send_main_msg_temp(double temp,UART_HandleTypeDef * uart )
 * @brief Function used to send the temperature message
 * @param temp Temperature value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_temp(double temp, UART_HandleTypeDef * uart);

/** @fn int send_main_msg_hum(uint16_t hum,UART_HandleTypeDef * uart )
 * @brief Function used to send the humidity message
 * @param hum Humidity value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_hum(uint16_t hum,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_temp_hum(double temp,uint16_t hum,UART_HandleTypeDef * uart )
 * @brief Function used to send the Temperature and Humidity messages
 * @param temp Temperature value to be sent
 * @param hum Humidity value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_temp_hum(double temp,uint16_t hum,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_current_EE(double current,UART_HandleTypeDef * uart )
 * @brief Function used to send the current message
 * @param current Current value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_current_EE(double current,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_current_printer(double current,UART_HandleTypeDef * uart )
 * @brief Function used to send the current message
 * @param current Current value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_current_printer(double current,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_door_state(uint8_t door_state,UART_HandleTypeDef * uart )
 * @brief Function used to send the door state message
 * @param state_door Door state value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_door_state(uint8_t door_state,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_latch_state(uint8_t latch_state,UART_HandleTypeDef * uart )
 * @brief Function used to send the latch state message
 * @param latch state value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_latch_state(uint8_t latch_state,UART_HandleTypeDef * uart );

/** @fn send_main_msg_weight(uint16_t weight,UART_HandleTypeDef * uart )
 * @brief Function used to send the weight message
 * @param weight value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_weight(uint16_t weight,UART_HandleTypeDef * uart );


/** @fn send_main_msg_pm1_0(uint16_t pm1_0,UART_HandleTypeDef * uart )
 * @brief Function used to send the pm1_0 pollution message
 * @param pm1.0 value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_pm1_0(uint16_t pm1_0,UART_HandleTypeDef * uart );


/** @fn send_main_msg_pm2_5(uint16_t pm2_5,UART_HandleTypeDef * uart )
 * @brief Function used to send the pm2_5 pollution message
 * @param pm2.5 value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_pm2_5(uint16_t pm2_5,UART_HandleTypeDef * uart );


/** @fn send_main_msg_pm10(uint16_t pm10,UART_HandleTypeDef * uart )
 * @brief Function used to send the pm10 pollution message
 * @param pm10 value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_pm10(uint16_t pm10,UART_HandleTypeDef * uart );


/** @fn send_main_msg_incendie_co2(uint16_t co2,UART_HandleTypeDef * uart )
 * @brief Function used to send the co2 rate
 * @param co2 value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_incendie_co2(uint16_t co2,UART_HandleTypeDef * uart );


/** @fn send_main_msg_incendie_tvoc(uint16_t tvoc,UART_HandleTypeDef * uart )
 * @brief Function used to send the tvoc rate
 * @param tvoc value to be sent
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_incendie_tvoc(uint16_t tvoc,UART_HandleTypeDef * uart );


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

/** @fn int send_main_msg_co2_warning(uint8_t co2_warning,UART_HandleTypeDef * uart )
 * @brief Function used to send the co2_warning state message
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_co2_warning(uint8_t co2_warning,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_tvoc_warning(uint8_t tvoc_warning,UART_HandleTypeDef * uart )
 * @brief Function used to send the tvoc_warning state message
 * @param uart Uart structure used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_tvoc_warning(uint8_t tvoc_warning,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_printing_state(uint8_t printig_state,uint8_t status,UART_HandleTypeDef * uart )
 * @brief Function used to send the Printing state message
 * @param printig_state Printing state value to sent
 * @param status Current status for the the given printig status: Begining, In progress and finished (Values to be determined)
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_printing_state(uint8_t printig_state,uint8_t status,UART_HandleTypeDef * uart );

/** @fn int send_main_msg_typology(uint8_t typo, uint8_t status,UART_HandleTypeDef * uart )
 * @brief Function used to send the stm32 typology
 * @param typo is value to sent
 * @param uart Uart strcture used to the communication with the Jetson Nano. If the cable used is the ST-Link, huart2
 * @return -1 if something went wrong; 0 if every went well
 */
HAL_StatusTypeDef send_main_msg_typology(uint8_t typo, UART_HandleTypeDef * uart );
