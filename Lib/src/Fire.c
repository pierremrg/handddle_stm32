/*
 * Fire.c
 *
 *  Created on: Nov 26, 2021
 *      Author: Fawaz
 */


#include "../../Lib/inc/Fire.h"
#include "../../Lib/inc/Cooling.h"
#include "../../Lib/inc/Buzzer.h"
#include "../../Core/Inc/main.h"
#include "../../Transport/Msg_gen/Main_msg_gen/main_msg_gen.h"
#include <stdbool.h>

#define PWM_STOP			0
#define PWM_COOLING 		60
#define PWM_COOLING_DANGER	100

UART_HandleTypeDef huart2;
I2C_HandleTypeDef hi2c3;

uint8_t command[7] = {0};    /* Buffer for data read/written on the i2c bus */
uint8_t recBuf[6]={0};

//Sensor data
uint16_t co2;
uint16_t tvoc;
uint8_t CO2_Warning;
uint8_t TVOC_Warning;

int dutycycle_cooling;




#include "../../Lib/inc/Fire.h"

uint8_t sgp30_send_cmd(sgp30_cmd_t cmd)
{
	uint8_t cmd_buffer[2];
	cmd_buffer[0] = cmd >> 8;
	cmd_buffer[1] = cmd;
	return HAL_I2C_Master_Transmit(&hi2c3, SGP30_ADDR_WRITE, (uint8_t*) cmd_buffer, 2, 0xFFFF);
}


int sgp30_soft_reset(void)
{
    uint8_t cmd = 0x06;
    return HAL_I2C_Master_Transmit(&hi2c3, 0x00, &cmd, 1, 0xFFFF);
}


int sgp30_init(void)
{
    int status;

    status = sgp30_soft_reset();
    if (status != HAL_OK) {
        return -1;
    }

    HAL_Delay(100);

    status = sgp30_send_cmd(INIT_AIR_QUALITY);

    HAL_Delay(100);

    return status == 0 ? 0 : -1;
}


uint8_t CheckCrc8(uint8_t* const message, uint8_t initial_value)
{
    uint8_t  remainder;	    //remainder
    uint8_t  i = 0, j = 0;  //Loop variable

    /* Initialization */
    remainder = initial_value;

    for(j = 0; j < 2;j++)
    {
        remainder ^= message[j];

        /* Calculate sequentially from the highest bit */
        for (i = 0; i < 8; i++)
        {
            if (remainder & 0x80)
            {
                remainder = (remainder << 1)^CRC8_POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }

    /* Return the calculated CRC code */
    return remainder;
}


int sgp30_start(void)
{
    return sgp30_send_cmd(MEASURE_AIR_QUALITY);
}


int spg30_read(void)
{
    int status;
    uint8_t recv_buffer[6]={0};

    /* Start measurement */
    status = sgp30_start();
    if (status != 0) {
        // Start fail
        return -1;
    }

    HAL_Delay(100);

    /* Read measurement data */
    status = HAL_I2C_Master_Receive(&hi2c3, SGP30_ADDR_READ, (uint8_t*)recv_buffer, 6, 0xFFFF);
    if (status != HAL_OK) {
        //I2C Master Receive fail
        return -1;
    }

    /* Verify the received measurement data */
    if (CheckCrc8(&recv_buffer[0], 0xFF) != recv_buffer[2]) {
        // co2 recv data crc check fail
        return -1;
    }
    if (CheckCrc8(&recv_buffer[3], 0xFF) != recv_buffer[5]) {
        // tvoc recv data crc check fail
        return -1;
    }


    /* Convert measurement data */
    co2  = (recv_buffer[0] << 8) + (recv_buffer[1]);
    tvoc = (recv_buffer[3] << 8) + (recv_buffer[4]);

    return 1;
}

void send_co2(){
	send_main_msg_incendie_co2(co2, &huart2);
}


void send_tvoc(){
	send_main_msg_incendie_tvoc(tvoc, &huart2);
}

void TVOC_treatment(){
	if(tvoc > 250 && tvoc < 2000) {
//		if(dutycycle_cooling == 0) set_cooling(PWM_COOLING);
		TVOC_Warning = 1; // dans cette zone de ppb, il faut commencer a aerer mais ce n'est pas 'dangereux'
	}
	else if(tvoc > 2000){
//		if(dutycycle_cooling == 0) set_cooling(PWM_COOLING_DANGER);
		TVOC_Warning = 1;
		// implémenter une alarme et non un buzzer
	}
	else {
		if(dutycycle_cooling == 0) set_cooling(PWM_STOP);
		TVOC_Warning = 0;
	}
}

void CO2_treatment(){
	if(co2 > 1100 && co2 < 5000) {
//		if(dutycycle_cooling == 0) set_cooling(PWM_COOLING);
		CO2_Warning = 0; // car entre 1100 et 5000ppm, on est à la limite maximum pour 8h d'exposition en moyenne
	}
	else if(co2 > 5000) {
//		if(dutycycle_cooling == 0) set_cooling(PWM_COOLING_DANGER);
		CO2_Warning = 1;
		// implémenter une alarme et non un buzzer
	}
	else {
//		if(dutycycle_cooling == 0) set_cooling(PWM_STOP);
		CO2_Warning = 0;
	}
}

void send_TVOC_CO2_treatments(){
	send_main_msg_co2_warning(CO2_Warning, &huart2);
	send_main_msg_tvoc_warning(TVOC_Warning, &huart2);
}
