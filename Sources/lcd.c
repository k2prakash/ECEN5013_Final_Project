/*
 * gpio.c
 * Used the LCD initialization sequence from the following source:
 * http://web.alfredstate.edu/weimandn/lcd/lcd_initialization/lcd_initialization_index.html
 *
 * The Pins used in the LCD operation are as follows:
 *
 *
 * Port D Pin 0 <-> D0
 * Port D Pin 1 <-> D1
 * Port D Pin 2 <-> D2
 * Port D Pin 3 <-> D3
 * Port D Pin 4 <-> D4
 * Port D Pin 5 <-> D5
 * Port D Pin 6 <-> D6
 * Port D Pin 7 <-> D7
 *
 *  Created on: Oct 7, 2016
 *      Author: kprakash
 */


#include "lcd.h"
uint8_t curr_addr = LCD_ROW1_ADDRESS;


/*
 * This function will initialize all the registers required for the LCD to
 * work.
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
	LCD_DISABLE; // Disable the LCD at the start of the initialization sequence
	delay(100);  // Provide a delay of 100 ms.

	lcd_write_command(); 	// set LCD to issue a command write
	LCD_ENABLE;				// Enable the LCD
	SP_FUNCTION_SET; 		// Issue the special function set command 0x30
	LCD_DISABLE;
	delay(5);

	lcd_write_command(); 	// set LCD to issue a command write
	LCD_ENABLE;				// Enable the LCD
	SP_FUNCTION_SET;		// Issue the special function set command 0x30
	LCD_DISABLE;
	delay(1);

	lcd_write_command();	// set LCD to issue a command write
	LCD_ENABLE;				// Enable the LCD
	SP_FUNCTION_SET;		// Issue the special function set command 0x30
	LCD_DISABLE;
	delay(1);

	lcd_write_command();	// set LCD to issue a command write
	LCD_ENABLE;				// Enable the LCD
	FUNCTION_SET;			// Issue the function set command to set 1 line display and
							// 5x8 dot character font
	LCD_DISABLE;
	//lcd_busy_wait();
	delay(1);

	//Step 6
	lcd_write_command();	// set LCD to issue a command write
	LCD_ENABLE;				// Enable the LCD
	LCD_DISPLAY_OFF;		// Turn the LCD display off
	LCD_DISABLE;
	//lcd_busy_wait();
	delay(1);

	lcd_write_command();	// set LCD to issue a command write
	LCD_ENABLE;				// Enable the LCD
	LCD_CLEAR_DISPLAY;		// Clear the LCD display
	LCD_DISABLE;
	delay(3);
	//lcd_busy_wait();

	lcd_write_command();	// set LCD to issue a command write
	LCD_ENABLE;				// Enable the LCD
	LCD_ENTRY_MODE; 		// Set the Cursor to increment left to right and
							// Set the display to not shift
	LCD_DISABLE;
	delay(1);
	//lcd_busy_wait();

	//Step 7

	lcd_write_command();	// set LCD to issue a command write
	LCD_ENABLE;				// Enable the LCD
	LCD_DISPLAY_ON; 		// Turn the the LCD display on
	LCD_DISABLE;
	delay(1);

	delay(100);

}

/*
 * Set the LCD to accept a command, by setting RS to 0
 * Set the RW bit to 0 to indicate a Write
 */
void lcd_write_command()
{
	LCD_SET_CMD;
	LCD_WRITE;
}

/*
 * Set the LCD to accept a command, by setting RS to 0
 * Set the RW bit to 1 to indicate a Read
 */
void lcd_read_command()
{
	LCD_SET_CMD;
	LCD_READ;
}

/*
 * Set the LCD to accept a data, by setting RS to 1
 * Set the RW bit to 0 to indicate a Write
 */
void lcd_write_data()
{
	LCD_SET_DATA;
	LCD_WRITE;
}

/*
 * Wait till the LCD has finished processing
 * Currently not working as expected, as so
 * I  am using a time delay instead.
 */
void lcd_busy_wait()
{
	lcd_read_command();
	GPIOD_PDDR &= DATA_IN;
	while(BUSY_CON & GPIOD_PDIR)
	{
	}
	GPIOD_PDDR |= DATA_OUT;
	return;
}

/*
* This function will make the cursor on the LED to go to a
* particular location on the LCD, as specified by the user
* The user must give an input that is an integer type row
* and integer type column. The rows can only be from 1 through
* 4 as there are only 4 rows available. Similarly, a user can
* give only 16 values from 1 through 16 as there are only 16
* columns available.

* The function will internally call the lcd_goto_addr function
* after calculating the address bases on predefined address
* offsets
*/


void lcd_goto_xy(uint8_t row, uint8_t column) {
    uint8_t first_byte = 0;

    if ((column >= 0) && (column <16)) {
        if (row == 0)
        {
            first_byte = LCD_ROW1_ADDRESS;
        } else if (row == 2)
        {
            first_byte = LCD_ROW3_ADDRESS;
        } else if (row == 1)
        {
            first_byte = LCD_ROW2_ADDRESS;
        } else if (row == 3)
        	{
            first_byte = LCD_ROW4_ADDRESS;
        } else {
            return;
        }
        curr_addr = (first_byte | (column));
        lcd_goto_addr(curr_addr);
    }else {
        return;
    }
}


/*
* This function will put the cursor
* to the specified address. This function requires
* that RW and RS be set to 0
*/

void lcd_goto_addr(uint8_t addr) {
	lcd_write_command();
	LCD_ENABLE;
	LCD_SET_ADDR(addr);
	LCD_DISABLE;
	//lcd_busy_wait();
	delay(1);
	return;
}


/*
* This function will display the input character into the LCD
* In order to do this, the Register Set has to be enabled.
* Since we are also writing a character into the LCD, the RW
* value will be 0.
*/

void lcd_put_ch(uint8_t c) {
    if (c == '\0' || c == '\r') {
        return;
    }

    lcd_write_data();

    if(curr_addr == 0xDF){
    	lcd_print_ch(c);
    	lcd_goto_xy(0,0);
    } else if (curr_addr == 0x8F) {
    	lcd_print_ch(c);
    	lcd_goto_xy(1,0);
    } else if (curr_addr == 0xCF) {
    	lcd_print_ch(c);
    	lcd_goto_xy(2,0);
    } else if (curr_addr == 0x9F) {
    	lcd_print_ch(c);
    	lcd_goto_xy(3,0);
    } else {
    	lcd_print_ch(c);
        curr_addr++;
    }
}

/*
 * This function will print the character on the LCD
 * The function takes a character as its input.
 */
void lcd_print_ch(uint8_t c) {
	LCD_ENABLE;
	LCD_PUT_CH(c);
	LCD_DISABLE;
	delay(1);
    //lcd_busy_wait();
    return;
}

/*
 * This function will input a string onto the LCD
 * The fuction takes a string array as its input.
 * The plan is to use circular buffer later on.
 */
void lcd_put_str(char * str)

{
	uint8_t is_end_of_str = 0;
	char c;
	while(!is_end_of_str)
	{
		c = *str++;
		if (!c)	// New Line encountered
		{
			is_end_of_str = 1;
		}

		else
		{
		   lcd_put_ch((uint8_t)c);

		}
	}
	return;
}









