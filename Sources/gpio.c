/*
 * gpio.c
 *
 *  Created on: Oct 7, 2016
 *      Author: kprakash
 */

#include "MKL25Z4.h"
#include "gpio.h"

/*
 * This function will initialize all the registers required for GPIO
 *
 */
void gpio_init()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;  // SETS CLOCK FOR PORT-B
	//SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;  // SETS CLOCK FOR PORT-D

	PORTC_PCR9 = PORT_PCR_MUX(1);        // Setting Pin 18 of Port B to be used as GPIO
	GPIOC_PDDR |= (1 << 9);
	/* Set the initial output state to low */
	GPIOC_PCOR |= (1 << 9);
}
