/*
 * i2c.c
 *
 *  Created on: Nov 28, 2016
 *      Author: kprakash
 */
#include "i2c.h"
#include "delay.h"
uint8_t mode = 0;

void i2c_init()
{
	/*
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; 	// Turn on clock to Port E for the I2C pins
    SIM_SCGC4 |= SIM_SCGC4_I2C1_MASK; 	// Turn on clock to I2C_1` module

    PORTC_PCR10 = PORT_PCR_MUX(2);		// Set Port E Pin 0 as the SDA pin
    PORTC_PCR11 = PORT_PCR_MUX(2);		// Set Port E Pin 1 as the SCL pin

    I2C1_F  = 0x14;       				// set MULT and ICR
    I2C1_C1 |= I2C_C1_IICEN_MASK;       // enable IIC
     */

	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK; 	// Turn on clock to Port E for the I2C pins
	PORTE_PCR0 = PORT_PCR_MUX(1);		// Set Port E Pin 0 as the GPIO SDA pin
	PORTE_PCR1 = PORT_PCR_MUX(1);		// Set Port E Pin 1 as the GPIO SCL pin
	GPIOE_PDDR |= 0x03;



}

/*
* This function will send a character of a byte serially into the slave device
* It is done by iterating over the byte word and making a transition of the  SCL from low to high
* The byte is then left shifted and the last bit is again obtained and the sequence continues. This will
* generate an ack.
*/
uint8_t i2c_write_byte(uint8_t byte) {

	uint8_t i = 0;
	uint8_t ack = 0;

	 for (i=0; i<8; i++)
	 { //iterate over all the bits in the Byte word
		if ((0x80 & byte) == 0)
		{
			CLEAR_SDA;
		} else {
			SET_SDA;
		} // data to be sent is ready during clock transition
		SET_SCL;
		CLEAR_SCL; //transition the clock back to 0
		byte<<=1; // left shift data by 1
	 }

     ack = i2c_ack();
	 return ack;
}

/*
* This function will read a character of a byte serially into the code
* It is done by polling the SDA line 8 times everytime SCL transitions from
* high to low. Everytime a bit is received by means of SDA, we add it to the byte
* word and left shift it till the entire byte word is filled. the function then returns the
* byte back to the program
*/

uint8_t i2c_read_byte() {
	uint8_t i = 0;
	uint8_t byte = 0;
	// clear the SDA pin - bit 0 to 0 to function as Input pin.
	GPIOE_PDDR &= ~I2C_SDA_MASK;
	CLEAR_SDA;
	for (i = 0; i < 8; i++)
	{
		SET_SCL;
		if( GET_SDA )
		{
			byte |=1;
		}
		for(int j=0;j<5;j++);
		CLEAR_SCL;
		if(i<7)
		{
			byte<<=1;
		}

	}
	// set the SDA pin - bit 0 to 1 to function as Output pin
	 GPIOE_PDDR |= I2C_SDA_MASK;


	return byte;
}

/*
uint8_t i2c_read_byte(uint8_t ack) {
	uint8_t i,j,k = 0;
	uint8_t byte = 0;
	SET_SDA;
	// clear the SDA pin - bit 0 to 0 to function as Input pin.
	GPIOE_PDDR &= ~I2C_SDA_MASK;
	for (i = 0; i < 8; i++)
	{
		byte<<=1;
		SET_SCL;
		k = GET_SDA;
		if(k)
		{
			//for(j=0;j<1;j++);
			byte |=1;
		}
		CLEAR_SCL;
	}
	// set the SDA pin - bit 0 to 1 to function as Output pin
	GPIOE_PDDR |= I2C_SDA_MASK;
	if (ack)
	{
		CLEAR_SDA;
	}else
	{
		SET_SDA;
	}
	i2c_nack();
	return byte;
}
*/



/*
* This function will return an Acknowledgement. It works by making the SDA low, making SCL transition
* from high to low and then raising SDA back to high.
*/
uint8_t i2c_ack()
{
	I2C_ACK();
	return GET_SDA;

}

/*
* This function will return an negative Acknowledgement. It works by making the SDA high, making SCL transition
* from high to low and then raising SDA back to high.
*/
uint8_t i2c_nack()
{
	I2C_NACK();
	return GET_SDA;
}



/*
void i2c_start_sequence (uint8_t slave_id, uint8_t command)
{

	if(command == I2C_WRITE)
	{
		slave_id |= I2C_WRITE; 	// set transmission mode as write
	}
	else
	{
		slave_id |= I2C_READ;	// set transmission mode as read
	}

	I2C_START();
	I2C_WRITE_BYTE(slave_id);

}


uint8_t i2c_read_register(uint8_t slave_id, uint8_t addr)
{
  uint8_t value;

  // Send Slave Address
  i2c_start_sequence(slave_id, I2C_READ);
  i2c_busy_wait();

  // Write Register Address
  I2C_WRITE_BYTE(addr);
  i2c_busy_wait();

  // Do a repeated start
  I2C1_C1 |= I2C_C1_RSTA_MASK;

  // Send Slave Address
  I2C_WRITE_BYTE(slave_id | I2C_READ); //read address
  i2c_busy_wait();

  // Put in Rx Mode
  I2C1_C1 &= (~I2C_C1_TX_MASK);

  // Turn off ACK since this is second to last byte being read
  I2C1_C1 |= I2C_C1_TXAK_MASK;

  // Dummy read
  value = I2C1_D ;
  i2c_busy_wait();

  // Send stop since about to read last byte
  I2C_STOP();

  // Read byte
  value = I2C1_D ;

  return value;
}



void i2c_write_register(uint8_t slave_id, uint8_t addr, uint8_t data)
{
	// send data to slave
	i2c_start_sequence(slave_id, I2C_WRITE);
	i2c_busy_wait();

	// Write Register Address
	I2C_WRITE_BYTE(addr);
	i2c_busy_wait();

	I2C_WRITE_BYTE(data);
	i2c_busy_wait();

	I2C_STOP();

	delay(1);
}

void i2c_busy_wait()
{
	while((I2C1_S & I2C_S_TCF_MASK)==0)
	{

	}
    I2C1_S |= I2C_S_TCF_MASK;
}
*/

