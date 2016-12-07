/*
 * server.c
 *
 *  Created on: Dec 6, 2016
 *      Author: kprakash
 */
#include "socket.h"

void close(uint8_t sock)
{
   if (sock != 0) return;

   // Send Close Command
   addr_write(S0_CR,CR_CLOSE);

   // Waiting until the S0_CR is clear
   while(addr_read(S0_CR));
}

void disconnect(uint8_t sock)
{
   if (sock != 0) return;

   // Send Disconnect Command
   addr_write(S0_CR,CR_DISCON);

   // Wait for Disconecting Process
   while(addr_read(S0_CR));
}

uint8_t socket(uint8_t sock,uint8_t eth_protocol,uint16_t tcp_port)
{
    uint8_t retval=0;
    if (sock != 0) return retval;

    // Make sure we close the socket first
    if (addr_read(S0_SR) == SOCK_CLOSED) {
      close(sock);
    }
    // Assigned Socket 0 Mode Register
    addr_write(S0_MR,eth_protocol);

    // Now open the Socket 0
    addr_write(S0_PORT,GET_HIGHER_BYTE(tcp_port));
    addr_write(S0_PORT + 1,(GET_LOWER_BYTE(tcp_port)));
    addr_write(S0_CR,CR_OPEN);                   // Open Socket

    // Wait for Opening Process
    while(addr_read(S0_CR));
    // Check for Init Status
    if (addr_read(S0_SR) == SOCK_INIT)
      retval=1;
    else
      close(sock);

    return retval;
}

uint8_t listen(uint8_t sock)
{
   uint8_t retval = 0;
   if (sock != 0) return retval;

   if (addr_read(S0_SR) == SOCK_INIT) {
     // Send the LISTEN Command
	   addr_write(S0_CR,CR_LISTEN);

     // Wait for Listening Process
     while(addr_read(S0_CR));
     // Check for Listen Status
     if (addr_read(S0_SR) == SOCK_LISTEN)
       retval=1;
     else
       close(sock);
    }
    return retval;
}


uint16_t send(uint8_t sock,const uint8_t *buf,uint16_t buflen)
{
    uint16_t ptr,offaddr,realaddr,txsize,timeout;

    if (buflen <= 0 || sock != 0) return 0;
#if _DEBUG_MODE
    printf("Send Size: %d\n",buflen);
#endif
    // Make sure the TX Free Size Register is available
    txsize=addr_read(SO_TX_FSR);
    txsize=(((txsize & 0x00FF) << 8 ) + addr_read(SO_TX_FSR + 1));
#if _DEBUG_MODE
    printf("TX Free Size: %d\n",txsize);
#endif
    timeout=0;
    while (txsize < buflen) {
      delay(1);
     txsize=addr_read(SO_TX_FSR);
     txsize=(((txsize & 0x00FF) << 8 ) + addr_read(SO_TX_FSR + 1));
     // Timeout for approx 1000 ms
     if (timeout++ > 1000) {
#if _DEBUG_MODE
       printf("TX Free Size Error!\n");
#endif
       // Disconnect the connection
       disconnect(sock);
       return 0;
     }
   }

   // Read the Tx Write Pointer
   ptr = addr_read(S0_TX_WR);
   offaddr = (((ptr & 0x00FF) << 8 ) + addr_read(S0_TX_WR + 1));
#if _DEBUG_MODE
    printf("TX Buffer: %x\n",offaddr);
#endif

    while(buflen) {
      buflen--;
      // Calculate the real W5100 physical Tx Buffer Address
      realaddr = TXBUFADDR + (offaddr & TX_BUF_MASK);
      // Copy the application data to the W5100 Tx Buffer
      addr_write(realaddr,*buf);
      offaddr++;
      buf++;
    }

    // Increase the S0_TX_WR value, so it point to the next transmit
    addr_write(S0_TX_WR,(offaddr & 0xFF00) >> 8 );
    addr_write(S0_TX_WR + 1,(offaddr & 0x00FF));

    // Now Send the SEND command
    addr_write(S0_CR,CR_SEND);

    // Wait for Sending Process
    while(addr_read(S0_CR));

    return 1;
}

uint16_t recv(uint8_t sock,uint8_t *buf,uint16_t buflen)
{
    uint16_t ptr,offaddr,realaddr;

    if (buflen <= 0 || sock != 0) return 1;

    // If the request size > MAX_BUF,just truncate it
    if (buflen > MAX_BUF)
      buflen=MAX_BUF - 2;
    // Read the Rx Read Pointer
    ptr = addr_read(S0_RX_RD);
    offaddr = (((ptr & 0x00FF) << 8 ) + addr_read(S0_RX_RD + 1));
#if _DEBUG_MODE
    printf("RX Buffer: %x\n",offaddr);
#endif

    while(buflen) {
      buflen--;
      realaddr=RXBUFADDR + (offaddr & RX_BUF_MASK);
      *buf = addr_read(realaddr);
      offaddr++;
      buf++;
    }
    *buf='\0';        // String terminated character

    // Increase the S0_RX_RD value, so it point to the next receive
    addr_write(S0_RX_RD,(offaddr & 0xFF00) >> 8 );
    addr_write(S0_RX_RD + 1,(offaddr & 0x00FF));

    // Now Send the RECV command
    addr_write(S0_CR,CR_RECV);
    delay(1);    // Wait for Receive Process

    return 1;
}


uint16_t recv_size(void)
{
  return ((addr_read(S0_RX_RSR) & 0x00FF) << 8 ) + addr_read(S0_RX_RSR + 1);
}


int strindex(char *s,char *t)
{
  uint16_t i,n;

  n=strlen(t);
  for(i=0;*(s+i); i++) {
    if (strncmp(s+i,t,n) == 0)
      return i;
  }
  return -1;
}



