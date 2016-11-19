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

void uart0_init(uint32_t baudrate);

void uart0_putch(char s);

char uart0_getch();

int uart0_getstr(char *str);

void uart0_getstr_n(char *str, uint8_t size);




#endif /* INCLUDES_UART_H_ */
