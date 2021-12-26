#include "../../Lib/inc/Pollution.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"
#include "../../Transport/Msg_gen/Sec_msg_gen/sec_msg_gen.h"
#include <string.h>

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

uint8_t getReading[7] =    {0x42, 0x4D, 0xE2, 0x00, 0x00, 0x01, 0x71};
uint8_t askAnswerMode[8] = {0x42, 0x4D, 0x00, 0x04, 0xE1, 0x00, 0x01, 0x74};
uint8_t DirectMode[8] =    {0x42, 0x4D, 0x00, 0x04, 0xE1, 0x01, 0x01, 0x75};
uint8_t standbyMode[8] =   {0x42,0x4D, 0x00, 0x04, 0xE4, 0x00, 0x01, 0x77};
uint8_t workingMode[8] =   {0x42,0x4D, 0x00, 0x04, 0xE4, 0x01, 0x01, 0x78};

uint8_t data2[32];

uint8_t a = 0x20;


void get_pollution()
{
//	HAL_UART_Transmit(&huart1, a, sizeof(a), HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart1, b, sizeof(b), HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart1, c, sizeof(c), HAL_MAX_DELAY);

//	HAL_UART_Transmit(&huart1, workingMode, 1, 100);
//	HAL_Delay(50);
//	HAL_UART_Transmit(&huart1, askAnswerMode, 1, 100);
//	HAL_Delay(50);
//	HAL_UART_Transmit(&huart1, getReading, sizeof(getReading), 100);
//	HAL_Delay(50);
//	HAL_UART_Receive(&huart1, data2, sizeof(data2), 100);
}
//
//void send_pollution_pm1_0()
//{
//	send_main_msg_pm1_0(pm1_0, &huart2);
//}
//
//void send_pollution_pm2_5()
//{
//	send_main_msg_pm2_5(pm2_5, &huart2);
//}
//
//void send_pollution_pm10()
//{
//	send_main_msg_pm10(pm10, &huart2);
//}
