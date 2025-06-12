#ifndef USER_INPUT_H_
#define USER_INPUT_H_

#include <stdbool.h>
#include "stm32g4_uart.h"
#include "stm32g4_gpio.h"

void init_user_input(void);
bool char_received(uart_id_t uart_id);
void process_keyboard_input(void);
void write_LED(bool state);

#endif /* USER_INPUT_H_ */