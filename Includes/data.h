/*
 * data.h
 *
 *  Created on: Oct 8, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_DATA_H_
#define INCLUDES_DATA_H_

uint32_t number_of_bytes(uint32_t data, int32_t base);

uint8_t * my_itoa(uint8_t * str, int32_t data, int32_t base);

uint32_t my_hextoi(uint8_t * str);

int32_t my_atoi(uint8_t * str);

void dump_memory(uint8_t * start, uint32_t length);

int32_t big_to_little(int32_t data);

int32_t little_to_big(int32_t data);

#endif /* INCLUDES_DATA_H_ */
