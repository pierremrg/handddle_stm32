#ifndef INC_CURRENT_H_
#define INC_CURRENT_H_

/**
  * @brief  This function is used to collect the ADC value from the Channel 5 to get the current.
  * @note	This Channel is linked to PA5. This Channel is used to get the Power Consumption from the
  * printers (TO VERIFY)
  */
void ADC_Select_CH5();

/**
  * @brief  This function is used to collect the ADC value from the Channel 4 to get the current.
  * @note	This Channel is linked to PA4. This Channel is used to get the Power Consumption from the
  * EE (TO VERIFY)
  */
void ADC_Select_CH4();

/**
  * @brief  This function is used to collect the ADC values each 6 ms and store it into an array
  */
void getElectricCurrentConsumption();

/**
  * @brief  This function is used to select the maximum value from the ADC during the 50Hz cycle.
  * @note	We are trying to get the maximum value to convert it into a power consumption. Because we are
  * working with an AC current, we have to collect a period from the 50 Hz to be efficient. We execute this command
  * each 204 ms.
  */
void getElectricCurrentConsumptionTransmit();


#endif /* INC_CURRENT_H_ */
