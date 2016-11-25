/*
 * memory.c
 *
 *  Created on: Oct 8, 2016
 *      Author: kprakash
 */

#include <stdio.h>
#include "stdint.h"
#include "memory.h"

#ifdef FRDM
#define printf(...)
#endif

/*This function moves length byte(s) from the source address to the desitination address.*/
int8_t my_memmove(uint8_t* src , uint8_t* dst , uint32_t length)
{
    if ( !src || !dst )
    {
        fprintf( stderr , "Null pointer. Exit code: %d\n" , NULL_PTR_ERROR );
        return NULL_PTR_ERROR;
    }

    if( src < dst && dst < src + length )
    {
        for ( src += length , dst += length ; 0 < length ; --length )
        {
            *--dst = *--src;
        }
    }
    else
    {
        for ( ; 0 < length ; --length )
        {
            *dst++ = *src++;
        }
    }

    return SUCCESS;
}


/*This function zeros the address space defined by length and the starting src pointer.*/
int8_t my_memzero(uint8_t* src, uint32_t length)
{
    if ( !src )
    {
        fprintf( stderr , "Null pointer. Exit code: %d\n" , NULL_PTR_ERROR );
        return NULL_PTR_ERROR;
    }

    for ( uint8_t* tmp = src ; 0 < length ; ++tmp, --length )
    {
        *tmp = 0;
    }

    return SUCCESS;
}


/*This function reverses the byte order of length bytes starting at the src pointer address*/
int8_t my_reverse(uint8_t* src, uint32_t length)
{
    if ( !src )
    {
        fprintf( stderr , "Null pointer. Exit code: %d\n" , NULL_PTR_ERROR );
        return NULL_PTR_ERROR;
    }

    uint8_t tmp;
    for ( uint8_t* end = src + length ; 0 < length/2 ; --length )
    {
        tmp = *--end;
        *end = *src;
        *src++ = tmp;
    }

    return SUCCESS;
}


