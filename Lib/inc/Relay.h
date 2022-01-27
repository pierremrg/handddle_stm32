#ifndef INC_RELAY_H_
#define INC_RELAY_H_

/**
  * @brief  This function is used to power the printer.
  * @param	Binary to set or shutdown the printer
  */
void set_shutdown_printer(int ON_off);

/**
  * @brief  This function is used to send the state of the relay
  */
void send_printer_state();

#endif /* INC_RELAY_H_ */
