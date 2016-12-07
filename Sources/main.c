/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "main.h"
#include "string.h"

static int i = 0;
char ch = '0';
uint8_t r = 0;
uint8_t c = 0;
char row_col_buff[ROW_COL_STR_BUFFER_SIZE];
char user_ip_buff[MESSAGE_BUFFER_SIZE_50];
uint8_t sockstat;
uint8_t sockreg;
uint16_t rsize;
int getidx,postidx;
uint8_t buf[MAX_BUF];



/*
 * The ISR for UART0.
 * The Interrupt will be enabled every time a user
 * inputs a character into the serial debugger
 *
 */
/*extern void UART0_IRQHandler (void)
{

	if (UART0_S1 & UART0_S1_RDRF_MASK)
	{
		ch = UART0_D;					// Clear the RDRF flag by reading the contents.
		uart_recieve_cbuffer(&rx_buffer, (uint8_t)ch);

	}
}*/

int main(void)
{
    uint8_t val = 0;
    sockreg=0;
	// __enable_irq();
	uart0_init(BAUDRATE);
	lcd_init();
	i2c_init();
	spi_init();
	wiznet_init();
	eeprom_reset();

    for (;;) {

    	call_to_server();

    }
    return 0;
}

void call_to_server()
{
	sockstat=addr_read(S0_SR);
	    switch(sockstat) {
	     case SOCK_CLOSED:
	        if (socket(sockreg,MR_TCP,TCP_PORT) > 0) {
		  // Listen to Socket 0
		  if (listen(sockreg) <= 0)
		    delay(1);
	#if _DEBUG_MODE
	          log0("Socket Listen!\r\n", MESSAGE_BUFFER_SIZE_16);
	#endif
		}
		break;
	     case SOCK_ESTABLISHED:
		// Get the client request size
	        rsize=recv_size();
		if (rsize > 0) {
		  // Now read the client Request
		  if (recv(sockreg,buf,rsize) <= 0) break;
	#if _DEBUG_MODE
	  	  log0("Content:\r\n",MESSAGE_BUFFER_SIZE_16);
	  	  log0(buf, MAX_BUF);
	#endif
	          // Check the Request Header
		  getidx=strindex((char *)buf,"GET /");
		  postidx=strindex((char *)buf,"POST /");
		  if (getidx >= 0 || postidx >= 0) {
	#if _DEBUG_MODE
		    log0("Recieved an HTTP request!\r\n",MESSAGE_BUFFER_SIZE_50);
	#endif


//	#if _DEBUG_MODE
//		    printf("Req. Send!\n");
//	#endif
		    // Create the HTTP Response	Header
		    strcpy((char *)buf,"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n");
		    strcat((char *)buf,"<html><body><span style=\"color:#0000A0\">\r\n");
		    strcat((char *)buf,"<h1>Embedded Web Server</h1>\r\n");
		    strcat((char *)buf,"<h2>A Project by Kaushik and Ryan</h2>\r\n");
		    strcat((char *)buf,"<h3>Components: KL25Z board, WIZ811MJ NIC and HD44780 LCD</h3>\r\n");
		    strcat((char *)buf,"</span></body></html>\r\n");
	            // Now Send the HTTP Remaining Response
		    if (send(sockreg,buf,strlen((char *)buf)) <= 0) break;

		  }
		  else
		  {
			  lcd_put_str(buf);
		  }

		  // Disconnect the socket
		  disconnect(sockreg);
	        } else
		  delay(1);    // Wait for request
		break;
	      case SOCK_FIN_WAIT:
	      case SOCK_CLOSING:
	      case SOCK_TIME_WAIT:
	      case SOCK_CLOSE_WAIT:
	      case SOCK_LAST_ACK:
	        // Force to close the socket
		close(sockreg);
	#if _DEBUG_MODE
		log0("Socket Close!\r\n",MESSAGE_BUFFER_SIZE_16);
	#endif
		break;
	    }
}

void lcd_print()
{
	log0("Enter the row number: 0 - 3\r\n", MESSAGE_BUFFER_SIZE_50);
	uart0_getstr_n(row_col_buff, ROW_COL_STR_BUFFER_SIZE);
	log0(NEWLINE,LOG_NEWLINE_LEN);
	r = (uint8_t)my_atoi(row_col_buff);
	my_memzero(row_col_buff, ROW_COL_STR_BUFFER_SIZE);

	log0("Enter the col number: 0 - 15\r\n", MESSAGE_BUFFER_SIZE_50);
	uart0_getstr_n(row_col_buff, ROW_COL_STR_BUFFER_SIZE);
	log0(NEWLINE,LOG_NEWLINE_LEN);
	c = (uint8_t)my_atoi(row_col_buff);

	my_memzero(row_col_buff, ROW_COL_STR_BUFFER_SIZE);

	if ((r >= 0) && (r <= 3) && (c >=0) && (c <= 15))
	{
		lcd_goto_xy(r,c);
		log0("Enter the string to display on the LCD\r\n", MESSAGE_BUFFER_SIZE_50);
		uart0_getstr_n(user_ip_buff, MESSAGE_BUFFER_SIZE_50); // replace with circular buffer.
		log0(NEWLINE,LOG_NEWLINE_LEN);
		lcd_put_str(user_ip_buff);
		my_memzero(user_ip_buff, MESSAGE_BUFFER_SIZE_50);

	}
	else
	{
		log0("Wrong combination of row/col entered.\r\n", MESSAGE_BUFFER_SIZE_50);
		return;
	}
}

void eeprom_write()
{
	uint8_t val = 0;
	eeprom_write_byte(EEPROM_I2C_ADDRESS, 0x02, 6);
	val = eeprom_read_byte(EEPROM_I2C_ADDRESS, 0x02);

}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
