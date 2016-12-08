/*
 * cbuffer.c
 *
 *  Created on: Oct 12, 2016
 *      Author: kprakash
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "cbuffer.h"


void cbuffer_init(cbuffer* buff, uint16_t buff_size)
{
    if(buff_size == 0)
    {
    	buff_size = 1;
    }
    buff->start = (uint8_t*)(malloc(buff_size));
    buff->end = buff->start + buff_size - 1;
    buff->head = buff->start;
    buff->tail = buff->start;
    buff->size = buff_size;
    buff->count = 0;
    return;
}


void cbuffer_free(cbuffer* buff)
{
    free(buff->start);
    return;
}


void cbuffer_add(cbuffer* buff, uint8_t* elem)
{
    if(buff->count == buff->size)
        return;
    if(buff->head == buff->end)
    {
        memcpy(buff->head, elem, sizeof(uint8_t));
        buff->head = buff->start;
    }
    else
    {
        memcpy(buff->head++, elem, sizeof(uint8_t));
    }
    buff->count++;
    return;
}


void cbuffer_remove(cbuffer* buff, uint8_t* elem)
{
    if(buff->count == 0)
    	return;
    if(buff->tail == buff-> end)
    {
        memcpy(elem, buff->tail, sizeof(uint8_t));
        buff->tail = buff->start;
    }
    else
    {
        memcpy(elem, buff->tail++, sizeof(uint8_t));
    }
    buff->count--;
    return;
}

void cbuffer_copy_to_str(cbuffer* buff, uint8_t* str)
{
	uint8_t* head = buff->head;
	uint8_t* tail = buff->tail;
	if(buff->count == 0)
    	return;

    while(tail != head)
    {
    	if(tail == buff-> end)
		{
			*str = *(tail);
			str++;
			tail = buff->start;
		}
		else
		{
			*str++ = *tail++;
		}

    }
    return;
}


