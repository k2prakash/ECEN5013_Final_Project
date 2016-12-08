/*
 * cbuffer.h
 *
 *  Created on: Oct 12, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_CBUFFER_H_
#define INCLUDES_CBUFFER_H_

typedef struct cbuffer
{
    uint8_t* start;
    uint8_t* end;
    uint8_t* head;
    uint8_t* tail;
	uint16_t size;
    uint16_t count;
} cbuffer;


/*initializes a circular buffer of size sz on the heap*/
void cbuffer_init(cbuffer* buff, uint16_t size);


/*free a circular buffer from memory*/
void cbuffer_free(cbuffer* buff);


/*adds one element to the buffer*/
void cbuffer_add(cbuffer* buff, uint8_t* elem);

void cbuffer_copy_to_str(cbuffer* buff, uint8_t* str);


/*removes one element from the buffer*/
void cbuffer_remove(cbuffer* buff, uint8_t* elem);


#endif /* INCLUDES_CBUFFER_H_ */
