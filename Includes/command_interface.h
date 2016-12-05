/*
 * command_interface.h
 *
 *  Created on: Nov 3, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_COMMAND_INTERFACE_H_
#define INCLUDES_COMMAND_INTERFACE_H_

#include <stdlib.h>
#include "stdint.h"
#include "log.h"
#define MAX_DATA_SIZE 32

#define CHECKSUM_VALID 0
#define CHECKSUM_INVALID -1

typedef enum Cmds_t {

	 GET_TEMP = 0x01,
	 SET_TEMP = 0x02,
	 SET_SPEED = 0x03,
	 GET_SPEED = 0x04,
	 LED_CONFIG = 0x05,
	 SET_LPM = 0x06,
	 GET_LPM = 0x07
 } Cmds;

 typedef struct CI_Msg_t {
	 Cmds command;
	 uint8_t length;
	 uint8_t data [MAX_DATA_SIZE];
	 uint16_t checksum;
 } CI_Msg;


 int8_t validate_checksum(CI_Msg * msg);

 void configure_led(uint8_t led_value);

 void decode_CI_Message(CI_Msg * msg);

#endif /* INCLUDES_COMMAND_INTERFACE_H_ */
