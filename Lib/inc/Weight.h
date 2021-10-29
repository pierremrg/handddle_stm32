#ifndef INC_WEIGHT_H_
#define INC_WEIGHT_H_

#include "../../Core/Inc/main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

/**
  * @brief  Measuring the weight
  * @note	Used of the PSCK and DATA Pin
  */
float get_weight();

/**
  * @brief  This function is used to send weight
  */
void send_weight();

/**
  * @brief  This function is used to calibrate the weight sensor
  */
void Calibration();

#endif /* INC_WEIGHT_H_ */
