#ifndef BUZZER_BUZZER_H_
#define BUZZER_BUZZER_H_

/**
  * @brief  Simple Control of the buzzer -- Must USE PWM PIN
  * @note	Timed (Delay) activation of the buzzer
  */
void set_buzzer();

/**
  * @brief  This function is used to send the the stae of the buzzer
  */
void send_buzzer_state();

#endif /* BUZZER_BUZZER_H_ */
