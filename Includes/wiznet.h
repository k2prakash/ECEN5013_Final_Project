/*
 * wiznet.h
 *
 *  Created on: Dec 3, 2016
 *      Author: kprakash
 */
#ifndef INCLUDES_WIZNET_H_
#define INCLUDES_WIZNET_H_
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

#define S0_MR	   0x0400      // Socket 0: Mode Register Address
#define S0_CR	   0x0401      // Socket 0: Command Register Address
#define S0_IR	   0x0402      // Socket 0: Interrupt Register Address
#define S0_SR	   0x0403      // Socket 0: Status Register Address
#define S0_PORT    0x0404      // Socket 0: Source Port: 0x0404 to 0x0405
#define SO_TX_FSR  0x0420      // Socket 0: Tx Free Size Register: 0x0420 to 0x0421
#define S0_TX_RD   0x0422      // Socket 0: Tx Read Pointer Register: 0x0422 to 0x0423
#define S0_TX_WR   0x0424      // Socket 0: Tx Write Pointer Register: 0x0424 to 0x0425
#define S0_RX_RSR  0x0426      // Socket 0: Rx Received Size Pointer Register: 0x0425 to 0x0427
#define S0_RX_RD   0x0428      // Socket 0: Rx Read Pointer: 0x0428 to 0x0429
#define TXBUFADDR  0x4000      // W5100 Send Buffer Base Address
#define RXBUFADDR  0x6000      // W5100 Read Buffer Base Address
// S0_MR values
#define MR_CLOSE	  0x00    // Unused socket
#define MR_TCP		  0x01    // TCP
#define MR_UDP		  0x02    // UDP
#define MR_IPRAW	  0x03	  // IP LAYER RAW SOCK
#define MR_MACRAW	  0x04	  // MAC LAYER RAW SOCK
#define MR_PPPOE	  0x05	  // PPPoE
#define MR_ND		  0x20	  // No Delayed Ack(TCP) flag
#define MR_MULTI	  0x80	  // support multicasting
// S0_CR values
#define CR_OPEN          0x01	  // Initialize or open socket
#define CR_LISTEN        0x02	  // Wait connection request in tcp mode(Server mode)
#define CR_CONNECT       0x04	  // Send connection request in tcp mode(Client mode)
#define CR_DISCON        0x08	  // Send closing reqeuset in tcp mode
#define CR_CLOSE         0x10	  // Close socket
#define CR_SEND          0x20	  // Update Tx memory pointer and send data
#define CR_SEND_MAC      0x21	  // Send data with MAC address, so without ARP process
#define CR_SEND_KEEP     0x22	  // Send keep alive message
#define CR_RECV          0x40	  // Update Rx memory buffer pointer and receive data
// S0_SR values
#define SOCK_CLOSED      0x00     // Closed
#define SOCK_INIT        0x13	  // Init state
#define SOCK_LISTEN      0x14	  // Listen state
#define SOCK_SYNSENT     0x15	  // Connection state
#define SOCK_SYNRECV     0x16	  // Connection state
#define SOCK_ESTABLISHED 0x17	  // Success to connect
#define SOCK_FIN_WAIT    0x18	  // Closing state
#define SOCK_CLOSING     0x1A	  // Closing state
#define SOCK_TIME_WAIT	 0x1B	  // Closing state
#define SOCK_CLOSE_WAIT  0x1C	  // Closing state
#define SOCK_LAST_ACK    0x1D	  // Closing state
#define SOCK_UDP         0x22	  // UDP socket
#define SOCK_IPRAW       0x32	  // IP raw mode socket
#define SOCK_MACRAW      0x42	  // MAC raw mode socket
#define SOCK_PPPOE       0x5F	  // PPPOE socket
#define TX_BUF_MASK      0x07FF   // Tx 2K Buffer Mask:
#define RX_BUF_MASK      0x07FF   // Rx 2K Buffer Mask:
#define NET_MEMALLOC     0x05     // Use 2K of Tx/Rx Buffer
#define TCP_PORT         80       // TCP/IP Port




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

#endif /* INCLUDES_WIZNET_H_ */
