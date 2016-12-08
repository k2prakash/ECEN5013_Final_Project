/*
 * uart_buffer.c
 *
 *  Created on: Oct 12, 2016
 *      Author: kprakash
 */

#include "uart_buffer.h"

void uart_putch_cbuffer(cbuffer* buff, uint16_t len)
{
    int i;
    uint8_t ch = 0;
    while(len) {
        cbuffer_remove(buff, &ch);
        uart0_putch(ch);
        len--;
    }
    return;
}


void uart_getch_cbuffer(cbuffer* buff, uint16_t len)
{
	uint8_t ch;
	while(len) {
		ch = uart0_getch(ch);
		cbuffer_add(buff, &ch);
		len--;
	}
	return;
}

