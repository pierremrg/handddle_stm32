#ifndef INC_LIGHTS_C_
#define INC_LIGHTS_C_

#define DARK             			0
#define WHITE_PT 					1
#define RED_PRINTING 				2
#define GREEN_FREE 					3
#define ORANGE_STRAIGHT_DEFAULT 	4
#define BLUE_HANDDDLE_MP 			5
#define ORANGE_BLINKY_DEFAULT 		6
#define WHITE_DOOR_OPEN		 		8

/**
  * @brief  This function has been designed for the selection of the lights
  * @param  Color choice
  * @note	To select the color of the lights we have to select 4 different PWM rate according to the HW
  */
void set_lights(int color);

/**
  * @brief  This function has been designed to send the selected light
  */
void send_lights(int light);

#endif /* INC_LIGHTS_C_ */
