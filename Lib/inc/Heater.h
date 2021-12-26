#ifndef HEATER_HEATER_H_
#define HEATER_HEATER_H_

/**
  * @brief  This function is used to control the heater and the fan linked to the heater
  * @param  ptr_dutycycle : PWM rate to control the fan rate
  */
void set_heater_pwm(int dutycycle);

/**
  * @brief  This function is used to control the heater and the fan linked to the heater
  * @param  ON_off_heater : Activation of the heater
  */
void set_heater(int ON_off_heater);

/**
  * @brief  This function is used to collect the ADC value from the Channel 9 to get the temperature near the heater.
  */
void ADC_Select_CH9();

/**
  * @brief  Calculation of the RPM from the Heater Fan
  * @note	Used of an external interruption
  */
void get_tachy();

/**
  * @brief  This function is used to reach the temperature requested by the user.
  */
void asservissement(int desired_temperature);

/**
  * @brief  This function is used to translate the ADC value collected from the Channel 19 into a Temperature.
  * @note	This Channel is linked to PB1. Those lines below are linked to the HW configuration (CTN choice)
  */
int get_heater_temp();

/**
  * @brief  This function is used to send the temperature near the Heater
  */
void send_heater_temp();

void heater_stop();

#endif /* HEATER_HEATER_H_ */
