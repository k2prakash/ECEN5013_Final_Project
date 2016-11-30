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


#define BAUDRATE 						115200
#define MESSAGE_BUFFER_SIZE_50 			50
#define MESSAGE_BUFFER_SIZE_25 			25
#define MESSAGE_BUFFER_SIZE_16 			16
#define ROW_COL_STR_BUFFER_SIZE 		2
#define LOG_NEWLINE_LEN					2

#define NEWLINE							"\r\n"

#endif /* INCLUDES_MAIN_H_ */
