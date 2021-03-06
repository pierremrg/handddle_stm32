#ifndef INC_POLLUTION_H_
#define INC_POLLUTION_H_

#include "../../Core/Inc/main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

/**
  * @brief  Detection of dust particules using SM-UART-04L
  * @note	Used of the USART1
  * @warn	This function is dependent on USART communication speed limit.
  */
void get_pollution();

/**
  * @brief  This function is used to send the pm 1.0
  */
void send_pollution_pm1_0();

/**
  * @brief  This function is used to send the pm 2.5
  */
void send_pollution_pm2_5();

/**
  * @brief  This function is used to send the pm 10
  */
void send_pollution_pm10();

#endif /* INC_POLLUTION_H_ */
