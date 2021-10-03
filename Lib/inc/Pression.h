#ifndef INC_PRESSION_H_
#define INC_PRESSION_H_


/**
  * @brief  This function is used to collect the wear condition from our filters.
  * @note	We are getting the differential pressure between the entry and the output of the filters to get the state of wear.
  */
void get_pression();

/**
  * @brief  This function is used to collect the ADC value from the Channel 12 which is linked to our filters condition.
  * @note	This Channel is liked to PC2
  */
void ADC_Select_CH12();

/**
  * @brief  This function is used to send the pressure
  */
void send_pression();

#endif /* INC_PRESSION_H_ */
