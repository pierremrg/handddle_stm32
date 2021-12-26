#ifndef INC_COOLING_H_
#define INC_COOLING_H_

/**
  * @brief  Control of the Extraction Fan - This function is used for cooling
  * @note	PWM controlled Fan
  */
void set_cooling(int dutycycle);

void get_tachy_cooling();

void cooling_stop();

#endif /* INC_COOLING_H_ */
