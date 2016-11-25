/*
 * ftoa.h
 *
 *  Created on: Oct 8, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_FTOA_H_
#define INCLUDES_FTOA_H_

#define EXP_BASE 127
#define SIGN_MASK 0x80000000
#define SIGN_SHIFT_BITS 31
#define EXP_MASK 0x7F800000
#define EXP_SHIFT_BITS 23
#define MANTISSA_MASK 0x007FFFFF
#define DECIMAL_PRECISION 3
#define DOT '.'


#define FRAC_000H 0
#define FRAC_001H 125
#define FRAC_010H 250
#define FRAC_011H 375
#define FRAC_100H 500
#define FRAC_101H 625
#define FRAC_110H 750
#define FRAC_111H 875

void my_ftoa(float value, char* str);




#endif /* INCLUDES_FTOA_H_ */
