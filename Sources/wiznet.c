/*
 * wiznet.c
 *
 *  Created on: Dec 3, 2016
 *      Author: kprakash
 */

#include "wiznet.h"

void wiznet_init()
{
	uint8_t rc_dt = 0;
	uint8_t k = 0;
	uint8_t mac_addr[] = {0x00,0x16,0x36,0xDE,0x58,0xF6};
	uint8_t ip_addr[] = {192,168,0,10};
	uint8_t sub_mask[] = {255,255,255,0};
	uint8_t gtw_addr[] = {192,168,0,1};

	// Setting the Wiznet W5100 Mode Register: 0x0000
	DISABLE_WIZNET;
	addr_write(MR,MR_VALUE);            // MR = 0b10000000;
	delay(1);
	//log0("Reading MR: \r\n", MESSAGE_BUFFER_SIZE_16);
	rc_dt = addr_read(MR);
	delay(1);
	uart0_putch(rc_dt);
	log0(NEWLINE,LOG_NEWLINE_LEN);

	// Setting the Wiznet W5100 Gateway Address (GAR): 0x0001 to 0x0004
	log0("Setting the gateway 192.168.0.1\r\n", MESSAGE_BUFFER_SIZE_50);
	addr_write(GAR + 0,gtw_addr[0]);
	addr_write(GAR + 1,gtw_addr[1]);
	addr_write(GAR + 2,gtw_addr[2]);
	addr_write(GAR + 3,gtw_addr[3]);
	delay(1);
	log0("Reading GA Register: \r\n", MESSAGE_BUFFER_SIZE_25);
	log0(NEWLINE,LOG_NEWLINE_LEN);
	for(k = 0; k <4; k++)
	{
		rc_dt = addr_read(GAR + k);
		log0(".", 1);
	}
	log0(NEWLINE,LOG_NEWLINE_LEN);


	// Setting the Wiznet W5100 Source Address Register (SAR): 0x0009 to 0x000E
	log0("Setting SAR \r\n", MESSAGE_BUFFER_SIZE_16);
	addr_write(SAR + 0,mac_addr[0]);
	addr_write(SAR + 1,mac_addr[1]);
	addr_write(SAR + 2,mac_addr[2]);
	addr_write(SAR + 3,mac_addr[3]);
	addr_write(SAR + 4,mac_addr[4]);
	addr_write(SAR + 5,mac_addr[5]);
	delay(1);

	log0("Reading SAR \r\n", MESSAGE_BUFFER_SIZE_16);
	//for(k = 0; k < 6; k++)
	//{
	//	addr_read(SAR + k);
	//	log0(":", 1);
	//}
	delay(1);
	log0(NEWLINE,LOG_NEWLINE_LEN);

	// Setting the Wiznet W5100 Sub Mask Address (SUBR): 0x0005 to 0x0008
	log0("Setting Sub Mask Address 255.255.255.0 \r\n",MESSAGE_BUFFER_SIZE_50);
	addr_write(SUBR + 0,sub_mask[0]);
	addr_write(SUBR + 1,sub_mask[1]);
	addr_write(SUBR + 2,sub_mask[2]);
	addr_write(SUBR + 3,sub_mask[3]);
	delay(1);

	log0("Reading SUBR: \r\n",MESSAGE_BUFFER_SIZE_16);
	//for(k = 0; k < 4; k++)
	//{
	//	addr_read(SUBR + k);
	//	log0(".", 1);
	//}
	delay(1);
	log0(NEWLINE,LOG_NEWLINE_LEN);


	log0("Setting IP Address 192.168.0.10 \r\n",MESSAGE_BUFFER_SIZE_50);
	addr_write(SIPR + 0,ip_addr[0]);
	addr_write(SIPR + 1,ip_addr[1]);
	addr_write(SIPR + 2,ip_addr[2]);
	addr_write(SIPR + 3,ip_addr[3]);
	delay(1);
	log0("Reading IP Address \r\n",MESSAGE_BUFFER_SIZE_25);
	//for(k = 0; k < 4; k++)
	//{
	//	addr_read(SIPR + k);
	//	log0(".", 1);
	//}

	// Setting the Wiznet W5100 RX and TX Memory Size, we use 2KB for Rx/Tx 4 channels
	log0("Setting Wiznet RMSR and TMSR\r\n", MESSAGE_BUFFER_SIZE_50);
	addr_write(RMSR,0x55);
	addr_write(TMSR,0x55);
	log0("Done Wiznet W5100 Initialized!\r\n", MESSAGE_BUFFER_SIZE_50);

}


void addr_write(uint32_t addr,uint8_t data)
{
	// Activate the CS pin
	ENABLE_WIZNET;

	// Send the address write opcode
	spi_write(WIZNET_WRITE);

	// Start Wiznet W5100 Address High Bytes transmission
    spi_write(GET_HIGHER_BYTE(addr));

    // Start Wiznet W5100 Address Low Bytes transmission
   	spi_write(GET_LOWER_BYTE(addr));

   	//Start the data transmission
   	spi_write(data);

   	// Give a delay of 1 ms
   	delay(2);

   	// Activate the CS pin
   	DISABLE_WIZNET;
}

uint8_t addr_read(uint32_t addr)
{
	uint8_t miso = 0;

	// Activate the CS pin
	ENABLE_WIZNET;

	// Start Wiznet W5100 Read OpCode transmission
	spi_write(WIZNET_READ);

	// Start Wiznet W5100 Address High Bytes transmission
    spi_write(GET_HIGHER_BYTE(addr));

    // Start Wiznet W5100 Address Low Bytes transmission
   	spi_write(GET_LOWER_BYTE(addr));

   	// Send Dummy transmission for reading the data

   	spi_write(NOP);

   	miso = spi_read();
   	for(int l=0;l<650;l++);
   	delay(1);

   	//Deactivate the CS pin
   	DISABLE_WIZNET;

  return(miso);
}
