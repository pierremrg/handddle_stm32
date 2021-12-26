/*
 * Fire.h
 *
 *  Created on: Nov 26, 2021
 *      Author: Fawaz
 */

#include "../../Core/Inc/main.h"

#ifndef INC_FIRE_H_
#define INC_FIRE_H_

#define SGP30_ADDR          0x58
#define	SGP30_ADDR_WRITE	SGP30_ADDR<<1       //0xb0
#define	SGP30_ADDR_READ		(SGP30_ADDR<<1)+1   //0xb1
#define CRC8_POLYNOMIAL 0x31

//Enumerate the list of SHT30 commands
typedef enum sgp30_cmd_en {
    /* Initialize air quality measurement */
    INIT_AIR_QUALITY = 0x2003,

    /* Start air quality measurement */
    MEASURE_AIR_QUALITY = 0x2008

} sgp30_cmd_t;

//Send command function
/**
   * @brief sends a command (16bit) to SGP30
   * @param cmd SGP30 command
   * @retval returns HAL_OK successfully
*/
uint8_t sgp30_send_cmd(sgp30_cmd_t cmd);


//Reset function
/**
   * @brief soft reset SGP30
 * @param	none
   * @retval returns HAL_OK successfully
*/
int sgp30_soft_reset(void);

//SGP30 initialization function
/**
 * @brief initialize SGP30 air quality measurement mode
 * @param	none
   * @retval returns 0 on success, -1 on failure
*/
int sgp30_init(void);


//Send a measurement start command
/**
   * @brief initialize SGP30 air quality measurement mode
 * @param	none
   * @retval returns HAL_OK successfully
*/
int sgp30_start(void);


uint8_t CheckCrc8(uint8_t* const message, uint8_t initial_value);

/**
   * @brief read air quality data once
 * @param	none
   * @retval returns 0 on success, -1 on failure
*/
int spg30_read(void);


void send_co2();

void send_tvoc();

void TVOC_treatment();
void CO2_treatment();

void send_TVOC_CO2_treatments();






#endif /* INC_FIRE_H_ */
