/*
 * gpio.c
 *
 *  Created on: Oct 7, 2016
 *      Author: kprakash
 */

#include "MKL25Z4.h"
#include "lcd.h"
#include "delay.h"

/*
 * This function will initialize all the registers required for GPIO
 *
 */
void lcd_init()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;  // SETS CLOCK FOR PORT-C
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;  // SETS CLOCK FOR PORT-C

	PORTB_PCR0 =  PORT_PCR_MUX(1);        // Setting Pin 1 of Port A to be used as GPIO
	PORTB_PCR1 =  PORT_PCR_MUX(1);		  // Setting Pin 2 of Port A to be used as GPIO
	PORTB_PCR2 =  PORT_PCR_MUX(1);		  // Setting Pin 4 of Port D to be used as GPIO

	PORTD_PCR0 =  PORT_PCR_MUX(1);        // Setting Pin 1 of Port A to be used as GPIO
	PORTD_PCR1 =  PORT_PCR_MUX(1);		  // Setting Pin 2 of Port A to be used as GPIO
	PORTD_PCR2 =  PORT_PCR_MUX(1);		  // Setting Pin 4 of Port D to be used as GPIO
	PORTD_PCR3 =  PORT_PCR_MUX(1);		  // Setting Pin 12 of Port A to be used as GPIO
	PORTD_PCR4 =  PORT_PCR_MUX(1);        // Setting Pin 1 of Port A to be used as GPIO
	PORTD_PCR5 =  PORT_PCR_MUX(1);		  // Setting Pin 2 of Port A to be used as GPIO
	PORTD_PCR6 =  PORT_PCR_MUX(1);		  // Setting Pin 4 of Port D to be used as GPIO
	PORTD_PCR7 =  PORT_PCR_MUX(1);		  // Setting Pin 12 of Port A to be used as GPIO


	/* Set the pins direction to output */
	GPIOB_PDDR |= 0x07;
	GPIOB_PDOR = 0x00;



	/* Set the pins direction to output */
	GPIOD_PDDR |= DATA_OUT;
	/* Set the initial output state to high */
    //GPIOD_PSOR |= DATA_OUT;

	lcd_init_sequence();

}

void lcd_init_sequence()
{
	LCD_DISABLE;
	delay(100);

	LCD_WRITE_CMD;
	LCD_ENABLE;
	GPIOD_PDOR = FUNCTION_SET;
	LCD_DISABLE;
	delay(5);

	LCD_WRITE_CMD;
	LCD_ENABLE;
	GPIOD_PDOR = FUNCTION_SET;
	LCD_DISABLE;
	delay(1);

	LCD_WRITE_CMD;
	LCD_ENABLE;
	GPIOD_PDOR = FUNCTION_SET;
	LCD_DISABLE;
	delay(1);

	LCD_WRITE_CMD;
	LCD_ENABLE;
	GPIOD_PDOR = SP_FUNCTION_SET;
	LCD_DISABLE;
	delay(1);

	//Step 6
	LCD_WRITE_CMD;
	LCD_ENABLE;
	GPIOD_PDOR = LCD_DISPLAY_OFF;
	LCD_DISABLE;
	delay(1);
	//lcdbusywait();

	LCD_WRITE_CMD;
	LCD_ENABLE;
	GPIOD_PDOR = LCD_CLEAR;
	LCD_DISABLE;
	delay(3);

	LCD_WRITE_CMD;
	LCD_ENABLE;
	GPIOD_PDOR = LCD_ENTRY_MODE; // send the code 0x06 to the lcd pointer. This will set the cursor and the blink type
	LCD_DISABLE;
	delay(1);

	//Step 7
	LCD_WRITE_CMD;
	LCD_ENABLE;
	GPIOD_PDOR = LCD_DISPLAY_ON; // send the code 0x0f to the lcd pointer. This will turn the display on
	LCD_DISABLE;
	delay(1);


}

void lcd_busy_wait()
{
	LCD_READ_CMD;
	while(BUSY_CON & GPIOD_PDIR)
	{
	}
	 return;
}




