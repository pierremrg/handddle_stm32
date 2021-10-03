#ifndef INC_SECURITY_H_
#define INC_SECURITY_H_

/**
  * @brief  This function is used when to stop the system and to alert because we reached a default state
  * note 	The default can either be the temperature or the current which is too high
  */
void set_shutdown_breakdown();

/**
  * @brief  This function is used when to disable an environment
  * @warn	THe lights are off
  */
void set_shutdown_all();

#endif /* INC_SECURITY_H_ */
