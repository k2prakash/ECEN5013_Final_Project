/*
 * i2c.h
 *
 *  Created on: Nov 28, 2016
 *      Author: kprakash
 */

#ifndef INCLUDES_I2C_H_
#define INCLUDES_I2C_H_
#include "stdint.h"
#include "MKL25Z4.h"

#define MSB_MASK				0x80

#define I2C_WRITE				0x00
#define I2C_READ				0x01
#define I2C_SCL					0x01
#define I2C_SDA					0x00



/*#define I2C_START()           I2C1_C1 |= I2C_C1_MST_MASK;\
								I2C1_C1 |= I2C_C1_TX_MASK;


#define I2C_STOP()             	I2C1_C1 &= ~I2C_C1_MST_MASK;\
								I2C1_C1 |= I2C_C1_TX_MASK;

*/

#define I2C_START()				GPIOE_PSOR |= (1<<I2C_SDA);\
								GPIOE_PSOR |= (1<<I2C_SCL);\
								GPIOE_PCOR |= (1<<I2C_SDA);\
								GPIOE_PCOR |= (1<<I2C_SCL)

#define I2C_STOP()				GPIOE_PCOR |= (1<<I2C_SCL);\
								GPIOE_PCOR |= (1<<I2C_SDA);\
								GPIOE_PSOR |= (1<<I2C_SCL);\
								GPIOE_PSOR |= (1<<I2C_SDA)

#define I2C_ACK()				GPIOE_PCOR |= (1<<I2C_SDA);\
								GPIOE_PSOR |= (1<<I2C_SCL);\
								GPIOE_PCOR |= (1<<I2C_SCL);\
								GPIOE_PSOR |= (1<<I2C_SDA)

#define I2C_NACK()				GPIOE_PSOR |= (1<<I2C_SDA);\
								GPIOE_PSOR |= (1<<I2C_SCL);\
								GPIOE_PCOR |= (1<<I2C_SCL);\
								GPIOE_PSOR |= (1<<I2C_SDA)

#define SET_SDA					GPIOE_PSOR |= (1<<I2C_SDA)
#define CLEAR_SDA				GPIOE_PCOR |= (1<<I2C_SDA)
#define SET_SCL					GPIOE_PSOR |= (1<<I2C_SCL)
#define CLEAR_SCL				GPIOE_PCOR |= (1<<I2C_SCL)

#define GET_SDA                 (GPIOE_PDIR & 0x01)


void i2c_init();
uint8_t i2c_write_byte(uint8_t byte);
uint8_t i2c_read_byte();
uint8_t i2c_ack();
uint8_t i2c_nack();





//#define I2C_WRITE_BYTE(x)      I2C1_D = x
//void i2c_start_sequence (uint8_t slave_id, uint8_t command);
//uint8_t i2c_read_register(uint8_t slave_id, uint8_t addr);
//void i2c_write_register(uint8_t slave_id, uint8_t addr, uint8_t data);
//void i2c_busy_wait();


#endif /* INCLUDES_I2C_H_ */
