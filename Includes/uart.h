/*
 * uart.h
 *
 *  Created on: Oct 7, 2016
 *      Author: kprakash
 */
#include "stdint.h"

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_


#define CLOCKDIV 16
#define CORECLK 24000000
#define MESSAGE_BUFFER_SIZE_50 			50
#define MESSAGE_BUFFER_SIZE_25 			25
#define MESSAGE_BUFFER_SIZE_16 			16
#define MESSAGE_BUFFER_SIZE_8 			8
#define LOG_NEWLINE_LEN					2
#define NEWLINE							"\r\n"



void uart0_init(uint32_t baudrate);

void uart0_putch(char s);

char uart0_getch();

int uart0_getstr(char *str);

void uart0_getstr_n(char *str, uint8_t size);

void set_pins_for_uart();



#endif /* INCLUDES_UART_H_ */
