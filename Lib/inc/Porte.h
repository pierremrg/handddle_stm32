#ifndef INC_PORTE_H_
#define INC_PORTE_H_

#include <stdint.h>

#define PRESENT 	1
#define NOT_PRESENT 0

/**
  * @brief  This function is used for the detection of the doors states & the latches states.
  * @note 	We are using 2 different sensors to lock the door.
  */
int get_door_state();

/**
  * @brief  This function is used to unlock the door
  * @param	Byte reception status reveived from a command
  * @note 	WE HAVE TO CHECK THE BEHAVIOR OF THE LOCKER
  */
void set_unlock(uint8_t ptr_door_state);

/**
  * @brief  This function is used to give the state of the door (Open or Close)
  * @note 	WE HAVE TO CHECK THE BEHAVIOR OF THE LOCKER
  */
void send_door_state();

/**
  * @brief  This function is used to give the state of the latch (PRESENT or NOT_PRESENT)
  * @note
  */
void send_latch_state();

void door_cycle();

/**
  * @brief  This function is used to give the authorization to the app to open the door because we have to check the pollution inside every environment
  */
void send_pollution_ok_door();


#endif /* INC_PORTE_H_ */
