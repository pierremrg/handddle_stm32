/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "../../Lib/inc/Buzzer.h"
#include "../../Lib/inc/Temp_humi.h"
#include "../../Lib/inc/Cooling.h"
#include "../../Lib/inc/Current.h"
#include "../../Lib/inc/Heater.h"
#include "../../Lib/inc/Lights.h"
#include "../../Lib/inc/Pollution.h"
#include "../../Lib/inc/Porte.h"
#include "../../Lib/inc/Pression.h"
#include "../../Lib/inc/States.h"
#include "../../Lib/inc/Heater.h"
#include "../../Lib/inc/Relay.h"
#include "../../Lib/inc/Test.h"
#include "../../Lib/inc/security.h"
#include "../../Transport/include/transport.h"
#include "../../Transport/uid.h"


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


/* Private defines -----------------------------------------------------------*/

/* Various constants */
#define false 0
#define true 1

#define SYSTEM_INACTIVE 0
#define SYSTEM_ACTIVE 1

#define NIGHT_MODE_INACTIVE 0
#define NIGHT_MODE_ACTIVE 1

#define MODE_AUTO 0
#define MODE_MANUAL 1

#define CLOSED 0
#define OPEN 1


/* Pins */
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC

#define SON_100K_Pin GPIO_PIN_0
#define SON_100K_GPIO_Port GPIOC
#define SON_50K_Pin GPIO_PIN_1
#define SON_50K_GPIO_Port GPIOC

#define PRESSION_Pin GPIO_PIN_2
#define PRESSION_GPIO_Port GPIOC

#define ELN_TEMP_Pin GPIO_PIN_3
#define ELN_TEMP_GPIO_Port GPIOC

#define RED_COLOR_Pin GPIO_PIN_0
#define RED_COLOR_GPIO_Port GPIOA
#define GREEN_COLOR_Pin GPIO_PIN_1
#define GREEN_COLOR_GPIO_Port GPIOA
#define BLUE_COLOR_Pin GPIO_PIN_8
#define BLUE_COLOR_GPIO_Port GPIOB
#define WHITE_COLOR_Pin GPIO_PIN_0
#define WHITE_COLOR_GPIO_Port GPIOB

#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA

#define CURRENT1_Pin GPIO_PIN_4
#define CURRENT1_GPIO_Port GPIOA
#define CURRENT2_Pin GPIO_PIN_5
#define CURRENT2_GPIO_Port GPIOA

#define LATCH_STATUS1_Pin GPIO_PIN_5
#define LATCH_STATUS1_GPIO_Port GPIOC
#define LATCH_STATUS2_Pin GPIO_PIN_6
#define LATCH_STATUS2_GPIO_Port GPIOA

#define DOOR_STATUS2_Pin GPIO_PIN_7
#define DOOR_STATUS2_GPIO_Port GPIOA
#define DOOR_STATUS1_Pin GPIO_PIN_4
#define DOOR_STATUS1_GPIO_Port GPIOC

#define TEST_COMMAND_PORTE_Pin GPIO_PIN_2
#define TEST_COMMAND_PORTE_GPIO_Port GPIOB

#define SHTC3_SCL1_Pin GPIO_PIN_8
#define SHTC3_SCL1_GPIO_Port GPIOA
#define SHTC3_SCL2_Pin GPIO_PIN_10
#define SHTC3_SCL2_GPIO_Port GPIOB

#define HEATER_TEMPERATURE_Pin GPIO_PIN_8
#define HEATER_TEMPERATURE_GPIO_Port GPIOB

#define HEATER_TACHY_Pin GPIO_PIN_6
#define HEATER_TACHY_GPIO_Port GPIOC

#define HEATER_Pin GPIO_PIN_9
#define HEATER_GPIO_Port GPIOB

#define HEATER_PWM_Pin GPIO_PIN_1
#define HEATER_PWM_GPIO_Port GPIOC

#define RELAY_Pin GPIO_PIN_9
#define RELAY_GPIO_Port GPIOC

#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA

#define FILTRATION_TACHY_Pin GPIO_PIN_10
#define FILTRATION_TACHY_GPIO_Port GPIOC

#define CMD_PORTE_Pin GPIO_PIN_11
#define CMD_PORTE_GPIO_Port GPIOC

#define ELN_FAN_Pin GPIO_PIN_12
#define ELN_FAN_GPIO_Port GPIOC

#define SHTC3_SDA2_Pin GPIO_PIN_3
#define SHTC3_SDA2_GPIO_Port GPIOB
#define SHTC3_SDA1_Pin GPIO_PIN_4
#define SHTC3_SDA1_GPIO_Port GPIOB

#define BUZZER_Pin GPIO_PIN_6
#define BUZZER_GPIO_Port GPIOB

#define FILTRATION_FAN_Pin GPIO_PIN_7
#define FILTRATION_FAN_GPIO_Port GPIOB


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
