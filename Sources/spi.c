/*
 * spi.c
 *  Used a part of the init sequence command from //https://community.nxp.com/thread/311824
 *  Created on: Nov 5, 2016
 *      Author: kprakash
 */
#include "spi.h"
#include "MKL25Z4.h"

size_t spi_read_n()
{

	return 0;
}

void spi_write_n(size_t data)
{

}

//https://community.nxp.com/thread/311824

void spi_init(void)
{
  SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      //SETS CLOCK FOR PORT-C
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;      // SETS CLOCK FOR PORT-B
  SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;       //Enable SPI0 clock

  PORTC_PCR4 = PORT_PCR_MUX(0x2);    //Set PTD0 to mux 2 [SPI0_PCS0] slave select I/O. Asserted when the pin is 0.
  PORTC_PCR5 = PORT_PCR_MUX(0x2);    //Set PTD1 to mux 2 [SPI0_SCK] output
  PORTC_PCR6 = PORT_PCR_MUX(0x2);    //Set PTD2 to mux 2 [SPI0_MOSI] output
  PORTC_PCR7 = PORT_PCR_MUX(0x2);    //Set PTD3 to mux 2 [SPIO_MISO] input
  PORTB_PCR8 = PORT_PCR_MUX(0x1);	 //Slave enable


  SPI0_C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK; // | SPI_C1_CPHA_MASK;   //Set SPI0 to Master & SS pin to auto SS
  SPI0_C2 = 0x00;   //Master SS pin acts as slave select output
  SPI0_C1 |= SPI_C1_SPE_MASK;    //Enable SPI0
  SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x08));     //Set baud rate prescale divisor to 3 & set baud rate divisor to 512 for baud rate of 15625 hz

  GPIOB_PDDR |= 1<<8;
  GPIOB_PSOR |= 1<<8; //toggle CS
}

// Read size number of characters into buffer p from register at address
uint8_t spi_read() {
	char data;
	while (!(SPI0_S & SPI_S_SPRF_MASK))
	{
		__asm__("nop");  //While buffer is not empty do nothing
	}
	return SPI0_D;

}

uint8_t spi_write(uint8_t data)
{
  SPI0_D = data;
  while(!(SPI_S_SPTEF_MASK & SPI0_S))
  {
    __asm__("nop");  //While buffer is not empty do nothing
  }

    //Write char to SPI - initially here
  return SPI0_D;

}

void spi_flush() //empty the spi buffer
{
	SPI0_C1&=0xBF;
	spi_init();
}

