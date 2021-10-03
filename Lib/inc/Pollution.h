#ifndef INC_POLLUTION_H_
#define INC_POLLUTION_H_

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

/**
  * @brief  Detection of dust particules using SM-UART-04L
  * @note	Used of the USART1
  * @warn	This function is dependent on USART communication speed limit.
  */
void get_pollution();

/**
  * @brief  This function is used to send the 3 differents particules
  */
void send_pollution ();

#endif /* INC_POLLUTION_H_ */
