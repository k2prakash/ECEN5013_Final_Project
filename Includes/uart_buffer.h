/*
 * uart_buffer.h
 *
 *  Created on: Oct 12, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_UART_BUFFER_H_
#define INCLUDES_UART_BUFFER_H_

#include "MKL25Z4.h"
#include "stdint.h"
#include "cbuffer.h"
#include "uart.h"

void uart_putch_cbuffer(cbuffer* buff, uint16_t len);
void uart_getch_cbuffer(cbuffer* buff, uint16_t len);

#endif /* INCLUDES_UART_BUFFER_H_ */
