/*

 * ftoa_m.c
 *
 *  Created on: Oct 8, 2016
 *      Author: kprakash
 */


#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "data.h"
#include "ftoa.h"


/*
 * This function will convert a float value into its corresponding string representation.
 * The function makes use of a union to represent the float value. The value is stored
 * as a 32 bit value. The function then uses the same memory region to determine the
 * exponent, the mantissa and the sign for the float number. With this information
 * available, it is possible to obtain the floating point value and rounded of to
 * a 3 digit decimal precision.
 */
void my_ftoa(float value, char* buffer) {

	union
	     {
	         float f;
	         struct
	         {
	             uint32_t val : 32;

	         };
	     } helper;


		helper.f = value;
		char sign = 0;
		uint32_t exp = 0;
		uint32_t mantissa = 0;
		uint32_t dec = 0;
		uint32_t frac = 0;
		char *ptr =  buffer;

		// The sign value is obtained by left shifting the value stored in the memory region
		// for 31 bits. If the value is 1 then the number is negative, else positive.

		sign = ( ((((uint32_t)helper.val & SIGN_MASK)>>SIGN_SHIFT_BITS) == 1) ? '-' : '+' );

		// The exponent is obtained by obtaining the bits from index 30 to index 23. The 8 bit value
		// when subtracted with the exponent base value of 127, gives you the number of digits the
		// integer portion before the '.' will be required.

		exp = (  (((uint32_t)helper.val & EXP_MASK)>>EXP_SHIFT_BITS) - EXP_BASE );

        // The bits remaining after the exponent will be used to determine the fraction portion
		// of the floating point number

		mantissa = ((uint32_t)helper.val & MANTISSA_MASK);

		// Add a leading 1 to the mantissa and obtain the decimal portion by shifting the resulting value
		// by 23 - exponent value.This will give us the decimal value before the '.'

		dec = ((uint32_t)mantissa | (MANTISSA_MASK+1))>>(EXP_SHIFT_BITS-exp);

		// Obtain the fraction by obtaining the bits that are right of bit 22 - exp bits. With this value obtained,
		// right shift the value till we get only the bits at 2^(-1), 2^(-2) and 2^(-3). This will give us a precision
		// of 3 bits after the '.'

		frac = (mantissa & ((2 << (EXP_SHIFT_BITS - exp - 1)) - 1)) >> (EXP_SHIFT_BITS - exp - DECIMAL_PRECISION);

		// append the sign of the floating value.
		*buffer=sign;

		// Increment the buffer pointer by 1 to add the integer portion of the fraction value.
		ptr+=1;

		// use the my_itoa function to construct the integer portion of the fraction value.
		my_itoa(ptr,dec, 10);

		// Increment the pointer to the place on the string, where the integer value ends.
		ptr+=(number_of_bytes(dec, 10));

        // Put a '.' on the string right after the integer value ends.
		*ptr= DOT;

		// increment the pointer to the buffer by 1;
		ptr+=1;

		// Append the fraction value that was obtained for a 3 point decimal precision.
		switch(frac){
		case 0: *ptr++='0';
				*ptr='\0';
			break;
		case 1: my_itoa(ptr,FRAC_001H,10);
			break;
		case 2: my_itoa(ptr,FRAC_010H,10);
			break;
		case 3: my_itoa(ptr,FRAC_011H,10);
			break;
		case 4: my_itoa(ptr,FRAC_100H,10);
			break;
		case 5: my_itoa(ptr,FRAC_101H,10);
			break;
		case 6: my_itoa(ptr,FRAC_110H,10);
			break;
		case 7: my_itoa(ptr,FRAC_111H,10);
			break;
		default: *ptr++='0';
				 *ptr='\0';
			break;
		}

}
