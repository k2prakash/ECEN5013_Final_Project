/*
 * eeprom.c
 *
 *  Created on: Nov 29, 2016
 *      Author: kprakash
 */
#include "eeprom.h"

void eeprom_write_byte (uint8_t slave_addr, uint8_t word_addr, uint8_t data)
{
	uint8_t b = 0;
	uint8_t count = 0;

	I2C_START(); // Signal a start in the I2C bus by having the SCL high and the SDA signal going from High to low
	i2c_write_byte(slave_addr); //send the slave address of the EEPROM in the bus and wait for SDA line to get pulled low by the eeprom
	i2c_write_byte(word_addr); //send the word address in the bus and wait for SDA line to get pulled low by the eeprom
	i2c_write_byte(data); // send the byte to be written into the eeprom and wait for SDA line to get pulled low by the eeprom
	I2C_STOP(); // send a stop signal by making the SCL high and the SDA line transition from low to High
	do
	{ // Poll for the acknowledgement from the EEPROM
		I2C_START(); // Signal a start in the I2C bus by having the SCL high and the SDA signal going from High to low
		b = i2c_write_byte(word_addr); //send the word address in the bus and wait for SDA line to get pulled low by the eeprom
	} while (b != 1); // loop till an acknowledgement is received

}

void eeprom_page_write (uint8_t slave_addr, uint8_t word_addr, uint8_t * buff)
{
	uint8_t b = 0;
	uint8_t count = 0;
	I2C_START(); // Signal a start in the I2C bus by having the SCL high and the SDA signal going from High to low
	i2c_write_byte(slave_addr); //send the slave address of the EEPROM in the bus and wait for SDA line to get pulled low by the eeprom
	i2c_write_byte(word_addr); //send the word address in the bus and wait for SDA line to get pulled low by the eeprom
	for (count = 0; count < 16; count++)
	{
		i2c_write_byte(*buff++); // Perform a page write by sending the same hex byte 16 times to write 16 bytes into the page.
	}
	I2C_STOP();// send a stop signal by making the SCL high and the SDA line transition from low to High
	do
	{
		I2C_START(); // Signal a start in the I2C bus by having the SCL high and the SDA signal going from High to low
		b = i2c_write_byte(word_addr); //send the word address in the bus and wait for SDA line to get pulled low by the eeprom. This will return an Acknowledgement
	} while (b != 1);   // loop till an acknowledgement is received

}

/*
* This function return a byte from the specified slave address and the word address.
*/
uint8_t eeprom_read_byte(uint8_t slave_addr, uint8_t word_addr)
{
    uint8_t ch = '\0';
    I2C_START(); // Signal a start in the I2C bus by having the SCL high and the SDA signal going from High to low
    i2c_write_byte(slave_addr); //send the slave address of the EEPROM in the bus and wait for SDA line to get pulled low by the eeprom
    i2c_write_byte(word_addr); //send the word address in the bus and wait for SDA line to get pulled low by the eeprom
    I2C_START(); // Signal a start in the I2C bus by having the SCL high and the SDA signal going from High to low
    i2c_write_byte((slave_addr + 1)); //send the slave address of the EEPROM in the bus and wait for SDA line to get pulled low by the eeprom. Notice that we add a 1, to indicate that the last bit is set to perform a read operation
    ch = i2c_read_byte(); // obtain the character from the eeprom
    i2c_nack(); // send a NACK to the EEPROM
    I2C_STOP(); // send a stop signal by making the SCL high and the SDA line transition from low to High
    return ch; // return the character
}

/*
* This function will reset the EEPROM. It works by sending nine 1s to the  EEPROM. The ninth 1 suppresses the ack
* and then a start and stop will perform the reset.
*
*/
void eeprom_reset()
{
    uint8_t i=0;
    uint8_t byte = RESET_BYTE;
    I2C_START();

    for (i=0; i<8; i++)
    { //iterate over all the bits in the 	Byte word
		if ((MSB_MASK & byte) == 0)
		{
			CLEAR_SDA;
		}
		else
		{
			SET_SDA;
		} // now we have the data to be sent
		SET_SCL;
		CLEAR_SCL; //transition the clock back to 0
		byte<<=1; // left shift data by 1
	}
    SET_SDA;
    SET_SCL;
    CLEAR_SCL;
    I2C_START();
    I2C_STOP();
}

uint8_t eeprom_get_slave_address(uint8_t page)
{
	return (EEPROM_I2C_ADDRESS + (page<<1));
}
