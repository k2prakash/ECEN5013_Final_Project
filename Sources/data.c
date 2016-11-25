/*
 * data.c
 *
 *  Created on: Oct 8, 2016
 *      Author: kprakash
 */

#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "data.h"
#include "memory.h"


#ifdef FRDM
#define printf(...)
#endif

/*This function will return the number of characters needed to form the ascii string*/
uint32_t number_of_bytes(uint32_t data, int32_t base) {
    uint32_t  count = 1;
    while((data/base) > 0) {
	data = data/base;
        count++;
    }
    return count;
}


/*
* This function takes an integer value and converts it into an ascii equivalent value.
* When the number is negative the function will be converted to its 2's complement or
* the uint32_t equivalent, which will be a very large number. If the number is positive
* the value remains unchanged. The value is then fed to a function that determines the
* number of ascii characters required to build the string.Next the conversion from
* integer to ascii takes place by means of repeated division and obtaining the remainder
*/
uint8_t * my_itoa(uint8_t * str, int32_t data, int32_t base){
    uint32_t num = 0; // variable to store the number of ascii characters
    uint32_t val = 0; // value to store the converted int32_t value to a uint32_t value
    val+=data; // conversion of int32_t to uint32_t
    num = number_of_bytes(val,base);

    *(str + num) = '\0'; // populate the last character in the string as a null character
    while (val != 0) { //  Perform repeated division of value with the base, till value becomes 0
	*(str+(num-1)) = ( (base == 16) && ((val % base) > 9) ) ?  //  if the base is 16 or HEX,  and the
		 (((val % base) -10) + 'A') : ((val % base) + '0'); // remainder is greater than 9, use A-F.
			// store the value in the index pointed out by str+ (num -1). This way we are building
			// the value backwards.
        num--; // keep decrementing num.
        val = val/base; // divide value with the base
    }
    return str;
}


/*
* This funtion takes an ascii string and converts it into an equivalent 32bit integer value.
* This fucntion will strip of any leading occurances of blank space, till the first occurance
* of a valid character: -,+ 0-9 is encountered. Any other character will be stop the atoi conversion
* at that point and will provide an integer output of the string.
*/
int32_t my_atoi(uint8_t * str){
    int32_t value = 0;
    char is_start = 0;
    char sign = 1;
    //char  space = '';
    while(*str != '\0') { // iterate till a Null character is encountered.
	if (*str == 32 && !is_start) { // If there are leading blank spaces, iterate till the very first character is encountered.
	    str+=1;
	} else { // a character other than a blank has been encountered or there is blank in the middle of the string
            if( !((*str == '-') || (*str == '+') || ((*str >= '0' && *str <= '9')))) { // The character is not a number, '-' or '+'.
	        break;
	    } else { //The character is a number, '-' or '+'.
                if ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f')) { // a number has been encountered.
                	is_start = 1; // a start of the number sequence is met
                	/*if (*str >= 'a' && *str <= 'f'){
                		value = (value * 10) + ((*str - 'a')+10);
                	}else{*/
                		value = (value * 10) + (*str - '0');
                	//}
                    str+=1;
		} else { // must be the sign '-' or '+'
		    if(!is_start) {// the first time the symbol '-' or '+' was encountered at the very beginning of the string
		        is_start = 1;
			if(*str == '-') { //if the sign is -, then the number mustbe multiplied by -1;
			    sign = -1;
			}
			str+=1;
		    } else { // the symbol '-' or '+' has occured again. Time to break from the loop and return the value.
			break;
		    }
		}
            }
        }
    }
    return (value * sign);
}

uint32_t my_hextoi(uint8_t * str){
    int32_t value = 0;
    char is_start = 0;
    char sign = 1;
    //char  space = '';
    while(*str != '\0') { // iterate till a Null character is encountered.
	if (*str == 32 && !is_start) { // If there are leading blank spaces, iterate till the very first character is encountered.
	    str+=1;
	} else { // a character other than a blank has been encountered or there is blank in the middle of the string
            if( !((*str == '-') || (*str == '+') || ((*str >= '0' && *str <= '9')) || ((*str >= 'a' && *str <= 'f')))) { // The character is not a number, '-' or '+'.
	        break;
	    } else { //The character is a number, '-' or '+'.
                if ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f')) { // a number has been encountered.
                	is_start = 1; // a start of the number sequence is met
                	if (*str >= 'a' && *str <= 'f'){
                		value = (value * 16) + ((*str - 'a')+10);
                	}else{
                		value = (value * 16) + (*str - '0');
                	}
                    str+=1;
		} else { // must be the sign '-' or '+'
		    if(!is_start) {// the first time the symbol '-' or '+' was encountered at the very beginning of the string
		        is_start = 1;
			if(*str == '-') { //if the sign is -, then the number mustbe multiplied by -1;
			    sign = -1;
			}
			str+=1;
		    } else { // the symbol '-' or '+' has occured again. Time to break from the loop and return the value.
			break;
		    }
		}
            }
        }
    }
    return (value * sign);
}


/*This function will output a Hex dump of the contents of contiguous address space for a user specified length.*/
void dump_memory(uint8_t * start, uint32_t length){

    uint32_t count = 0;
    uint32_t pr = 0;
    if ((length >> 31) == 1) {
	printf("Warning: A negative number or a value of large length passed.\n");
    }
    // Build the row format, where each addresses from the left most value are addresses at increments of 1 from left to right.
    printf("ADDRESS:\t  00\t  01\t  02\t  03\t  04\t  05\t 06\t  07\t  08\t  09\t  10\t  11\t  12\t  13\t  14\t  15\n");

    while (count < length) {
        if ((pr % 16) == 0 ) {   // if the count is a factor of 16, then go to the next line.
            printf("\n");
            printf("%p", start); // print the address of the current pointer
            printf("\t 0x%x", *start); // print the value at the pointer
        }
        else {
           printf("\t 0x%x", *start); // print the value at the pointer.
        }

        start++; // Keep incrementing the pointer till the end of length
        pr++; // increment the column counter
        count++; // increment the count used to track if value of length is reached.
    }
    printf("\n");
    return;
}


/*This function swaps the byte order of a big endian stored value, making it a little endian stored value*/
int32_t big_to_little( int32_t data )
{
    uint8_t* src = ( uint8_t* ) &data;
    uint32_t length = sizeof( int32_t );
    my_reverse( src , length);
    /*int32_t val = *( ptr + 3 ) + ( *( ptr + 2 ) << 8 ) + ( *( ptr + 1 ) << 16 ) + ( *( ptr ) << 24 );*/
    return data;
}


/*This function swaps the byte order of a little endian stored value, , making it a big endian stored value*/
int32_t little_to_big(int32_t data)
{
    uint8_t* src = ( uint8_t* ) &data;
    uint32_t length = sizeof( int32_t );
    my_reverse( src , length);
    /*val =  (*(ptr)<<24) + (*(ptr+1)<<16) + (*(ptr+2)<<8) + *(ptr+3);*/
    return data;
}


