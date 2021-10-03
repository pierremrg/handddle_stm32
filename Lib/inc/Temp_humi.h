#ifndef INC_TEMP_HUMI_H_
#define INC_TEMP_HUMI_H_

#define SHT4X_ADDRESS 0x44

/**
  * @brief  This function is used to collect Temperature & Humidity with the HIH1.
  * @note	We are collecting an average from 2 sensors
  */
float get_temp_humi_HIH1();

/**
  * @brief  This function is used to collect Temperature & Humidity with the SHT40.
  * @note	We are collecting an average from 2 sensors
  */
float get_temp_humi_SHT40();

/**
  * @brief  This function is used to send the humidity & the temperature
  */
void send_temp_humi();

/**
  * @brief  This function is used to send the temperature
  */
void send_temp();

/**
  * @brief  This function is used to send the humidity
  */
void send_humi();

#endif /* INC_TEMP_HUMI_H_ */
