/*
 * command_interface.c
 *
 *  Created on: Nov 3, 2016
 *      Author: kprakash
 */

#include "main.h"
#include "command_interface.h"


int8_t validate_checksum(CI_Msg * msg)
{
	uint16_t add_chksum = 0;
	add_chksum+= msg->command;
	add_chksum+= msg->length + (2*sizeof(uint8_t) + sizeof(uint16_t));
	for (int i=0;i<msg->length;i++)
	{
		add_chksum+=msg->data[i];
	}

    if (add_chksum ==  msg->checksum)
    {
    	return CHECKSUM_VALID;
    }
    else
    {
    	return CHECKSUM_INVALID;
    }
}


void decode_CI_Message(CI_Msg * msg)
{
	switch (msg->command)
	{
		case SET_TEMP:	break;

		case GET_TEMP:	break;

		case SET_SPEED:	break;

		case GET_SPEED:	break;

		case LED_CONFIG:
						configure_led(msg->data[0]);
						break;

		case SET_LPM:	break;

		case GET_LPM:	break;


	}
}

void configure_led(uint8_t led_value) {
	if (led_value >=0 && led_value <=3)
		display_color(led_value);
}


