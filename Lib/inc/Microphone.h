#ifndef INC_MICROPHONE_H_
#define INC_MICROPHONE_H_

/**
  * @brief  This function is used to get the sound in the printing environment.
  * @note	This function will evolve
  */
void get_listening();

/**
  * @brief  This function is used to collect the ADC value from the Channel 10 to get the sound.
  * @note	This Channel is linked to PC0. This Channel is used by default to get the ADC value. The HW gain for this Channel is equal to 100.
  */
void ADC_Select_CH10();

/**
  * @brief  This function is used to collect the ADC value from the Channel 11 to get the sound.
  * @note	This Channel is linked to PC1. This Channel is used when the ADC value from the Channel 10 is too high. The HW configuration is a gain equals to 50.
  */
void ADC_Select_CH11();

#endif /* INC_MICROPHONE_H_ */
