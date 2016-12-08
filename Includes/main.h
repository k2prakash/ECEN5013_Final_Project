/*
 * main.h
 *
 *  Created on: Nov 19, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_MAIN_H_
#define INCLUDES_MAIN_H_

#include "uart.h"
#include "lcd.h"
#include "delay.h"
#include "MKL25Z4.h"
#include "memory.h"
#include "data.h"
#include "log.h"
#include "i2c.h"
#include "eeprom.h"
#include "spi.h"
#include "wiznet.h"
#include "socket.h"
#include "cbuffer.h"
#include "uart_buffer.h"
#include "gpio.h"


#define BAUDRATE 						115200
#define ROW_COL_STR_BUFFER_SIZE 		2
#define _DEBUG_MODE      				1
#define GET_STR							"GET /"
#define POST_STR						"POST /"

void call_to_server();
void lcd_print();
void eeprom_write();
#endif /* INCLUDES_MAIN_H_ */
