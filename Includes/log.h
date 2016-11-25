/*
 * log.h
 *
 *  Created on: Oct 9, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_LOG_H_
#define INCLUDES_LOG_H_

#define BASE_10 10
#define VERBOSE
#define INTEGER_TYPE 'i'
#define FLOAT_TYPE 'f'

#define ONE_BYTE 1
#define TWO_BYTES 2
#define FOUR_BYTES 4
#define BUFFER_SIZE 16


void log0(char *str, uint32_t len);
void log1(char *str, uint32_t len, void * param, uint32_t data_type_size, char typ);

#endif /* INCLUDES_LOG_H_ */
