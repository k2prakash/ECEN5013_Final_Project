/*
 * memory.h
 *
 *  Created on: Oct 8, 2016
 *      Author: kprakash
 */

#ifndef SOURCES_MEMORY_H_
#define SOURCES_MEMORY_H_

#ifndef _MEMORY_H
#define _MEMORY_H

static const uint8_t SUCCESS = 0;
static const int8_t NULL_PTR_ERROR = -1;
static const int8_t INVAL_LEN_ERROR = -2;
static const int8_t ADDR_OVERLAP_ERROR = -3;
/*
This fucntion will move byte(s) of data starting from the source address location to the desitination address location.
*/
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length);

/*
This function will zeroize all the the data for the given length of addresses starting from the source address location.
*/

int8_t my_memzero(uint8_t * src, uint32_t length);

/*
This fucntion will takes a pointer to a memory location and a length in bytes and reverse the order of all of the bytes.
*/

int8_t my_reverse(uint8_t* src, uint32_t length);

uint32_t srclen(uint8_t *src);
#endif



#endif /* SOURCES_MEMORY_H_ */
