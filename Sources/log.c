/*
 * log.c

 *
 *  Created on: Oct 9, 2016
 *      Author: kprakash
 */
#include <stddef.h>
#include "uart.h"
#include "stdint.h"
#include "data.h"
#include "main.h"
#include "log.h"
#include "ftoa.h"

#define VERBOSE

#ifdef VERBOSE

/*
 * This function will print the contents of a string, based on the length specified
 * by the user. The function terminates upon the first occurance of a null character
 */
void log0(char *str, uint32_t len)
{

	while (len != 0)
	{
		if(!*str) {
			break;
		}
		uart0_putch(*(str));
		len-=1;
		str++;
	}
}

/*
 * This function will print the contents of a string, based on the parameter specified
 * by the user. The params are integer type and float type.
 */
void log1(char * str, uint32_t len, void * param, uint32_t data_type_size, char typ)
{
    char param_str[BUFFER_SIZE];
    uint32_t c = 0;

    if (typ == INTEGER_TYPE) {
    	    log0(str, len);	// print the message string
			if (data_type_size == ONE_BYTE)
			{
				uint32_t val = c + *(int8_t *)param;
				my_itoa ((uint8_t *)param_str, val, BASE_10); //convert the integer into to string
				log0(param_str, number_of_bytes(val, BASE_10));	// print the integer as a string

			}

			else if (data_type_size == TWO_BYTES)
			{
				uint32_t val =  c + *(int16_t *)param;
				my_itoa ((uint8_t *)param_str, val, BASE_10); //convert the integer into to string
				log0(param_str, number_of_bytes(val, BASE_10));	// print the integer as a string

			}

			else if (data_type_size == FOUR_BYTES)
			{
				uint32_t val =  c + *(int32_t *)param;
				my_itoa ((uint8_t *)param_str, val, BASE_10); //convert the integer into to string
				log0(param_str, number_of_bytes(val, BASE_10));	// print the integer as a string

			}
			log0(NEWLINE, LOG_NEWLINE_LEN);
    }
	else if (typ == FLOAT_TYPE)
	{
		float val = *(float *)param;
		my_ftoa(val, param_str);			// convert the float value into a string
		log0(str, len); // print the message string
		log0(param_str, BUFFER_SIZE);				// print the floating point number as a string
		log0(NEWLINE, LOG_NEWLINE_LEN);
	}

}
#endif



