/*
 * eeprom.h
 *
 *  Created on: Nov 29, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_EEPROM_H_
#define INCLUDES_EEPROM_H_
#include "i2c.h"

#define EEPROM_I2C_ADDRESS      0xA0
#define RESET_BYTE				0xFF

void eeprom_write_byte (uint8_t slave_addr, uint8_t word_addr, uint8_t data);
void eeprom_page_write (uint8_t slave_addr, uint8_t word_addr, uint8_t * buff);
uint8_t eeprom_read_byte(uint8_t slave_addr, uint8_t word_addr);
void eeprom_reset();
uint8_t eeprom_get_slave_address(uint8_t page);


#endif /* INCLUDES_EEPROM_H_ */
