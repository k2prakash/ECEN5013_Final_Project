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
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;  // SETS CLOCK FOR PORT-B
	//SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;  // SETS CLOCK FOR PORT-D

	PORTB_PCR18 = PORT_PCR_MUX(1);        // Setting Pin 18 of Port B to be used as GPIO
	PORTB_PCR19 = PORT_PCR_MUX(1);		  // Setting Pin 19 of Port B to be used as GPIO
	PORTB_PCR8 = PORT_PCR_MUX(1);		  // Setting Pin 1 of Port D to be used as GPIO

	/* Set the initial output state to high */
	GPIOB_PSOR |= RED_SHIFT;

	/* Set the pins direction to output */
	GPIOB_PDDR |= RED_SHIFT;

	/* Set the initial output state to high */
	GPIOB_PSOR |= GREEN_SHIFT;

	/* Set the pins direction to output */
	GPIOB_PDDR |= GREEN_SHIFT;

	/* Set the PTD1 pin multiplexer to GPIO mode */


	/* Set the initial output state to high */
	//GPIOD_PSOR = BLUE_SHIFT;

	/* Set the pins direction to output */
	//GPIOD_PDDR |= BLUE_SHIFT;

}

/*
 * This function will set the RGB combination for the LED
 * The function takes a color code with values ranging from 0-7
 */
void display_color(uint8_t color_code) {
	switch (color_code) {

	// Black
	case 0:
		    BLUE_OFF;
			RED_OFF;
			GREEN_OFF;
			break;

	// Green
	case 1:
			BLUE_OFF;
			RED_OFF;
			GREEN_ON;
			break;

    // Red
	case 2: BLUE_OFF;
			RED_ON;
		    GREEN_OFF;
		    break;

    // Yellow/ Orange
	case 3: BLUE_OFF;
		    RED_ON;
		    GREEN_ON;
		    break;

    // BLUE
	case 4: BLUE_ON;
		    RED_OFF;
		    GREEN_OFF;
		    break;

   //AQua
	case 5: BLUE_ON;
		    RED_OFF;
		    GREEN_ON;
		    break;

    // Violet
	case 6: BLUE_ON;
		    RED_ON;
		    GREEN_OFF;
		    break;

    // White
	case 7: RED_ON;
		    BLUE_ON;
		    GREEN_ON;
		    break;

	}

}

/*
 * This function will reset the TPM Muxed pins and
 * configure the pins as RGB High out pins
 */
void set_pins_for_color()
{
	PORTB_PCR18 &= ~PORT_PCR_MUX(3);
    PORTB_PCR19 &= ~PORT_PCR_MUX(3);
	//PORTD_PCR1 &= ~PORT_PCR_MUX(4);
	PORTB_PCR18 = PORT_PCR_MUX(1);
	PORTB_PCR19 = PORT_PCR_MUX(1);
	//PORTD_PCR1 = PORT_PCR_MUX(1);
}



