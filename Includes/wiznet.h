/*
 * wiznet.h
 *
 *  Created on: Dec 3, 2016
 *      Author: kprakash
 */
#include "stdint.h"
#include "stdlib.h"
#include "MKL25Z4.h"
#include "spi.h"
#include "delay.h"
#include "uart.h"
#include "log.h"
#include "data.h"
#include "memory.h"

#define WIZNET_MAX_DATA_SIZE 	8
#define HIGHER_BYTE_MASK		0xFF00
#define LOWER_BYTE_MASK			0x00FF
#define NOP						0xFF

// Wiznet W5100 Register Addresses
#define MR   					0x0000   // Mode Register
#define GAR  					0x0001   // Gateway Address: 0x0001 to 0x0004
#define SUBR 					0x0005   // Subnet mask Address: 0x0005 to 0x0008
#define SAR  					0x0009   // Source Hardware Address (MAC): 0x0009 to 0x000E
#define SIPR 					0x000F   // Source IP Address: 0x000F to 0x0012
#define RMSR 					0x001A   // RX Memory Size Register
#define TMSR 					0x001B   // TX Memory Size Register

#define MR_VALUE				0x80	// Mode register value

#define WIZNET_CS_PIN			8
#define DISABLE_WIZNET			(GPIOB_PSOR |= (1 << WIZNET_CS_PIN ))
#define ENABLE_WIZNET			(GPIOB_PCOR |= (1 << WIZNET_CS_PIN ))

#define GET_HIGHER_BYTE(x)		((x & HIGHER_BYTE_MASK) >> 8)
#define GET_LOWER_BYTE(x)		(x & LOWER_BYTE_MASK)


typedef enum WIZNET_Cmds_t
{
	 WIZNET_READ = 0x0F,
	 WIZNET_WRITE = 0xF0
} WIZNET_CMDS;


typedef struct WIZNET_Msg_t
{
	 WIZNET_CMDS command;
	 uint8_t length;
	 uint32_t address;
	 uint8_t data [WIZNET_MAX_DATA_SIZE];
 } WIZNET_Msg;

 void addr_write(uint32_t addr,uint8_t data);
 uint8_t addr_read(uint32_t addr);
 void wiznet_init();
 uint8_t SPI_Read(uint32_t addr);
 void print_number(uint8_t* ip_addr, uint8_t * buff);
