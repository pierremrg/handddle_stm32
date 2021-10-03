#ifndef INC_ELN_TEMPERATURE_H_
#define INC_ELN_TEMPERATURE_H_

/**
  * @brief  This function is used to collect the temperature inside the rack
  * @note	Parameter from this function are linked to the HW configuration (CTN choice)
  */
void get_ELN_temp();

/**
  * @brief  This function is used to collect the ADC value from the Channel 13 to get the temperature inside the rack.
  * @note	This Channel is linked to PC3.
  */
void ADC_Select_CH13();


/**
  * @brief  This function is used to send the temperature inside the rack.
  */
void send_ELN_temp();

#endif /* INC_ELN_TEMPERATURE_H_ */
