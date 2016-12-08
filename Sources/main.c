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
cbuffer rx_cbuffer;
uint8_t led_status = 0;


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
    cbuffer_init(&rx_cbuffer,MAX_BUF);
    uart0_init(BAUDRATE);
	lcd_init();
	i2c_init();
	spi_init();
	wiznet_init();
	gpio_init();
	eeprom_reset();


    for (;;) {

    	call_to_server();

    }
    return 0;
}

void call_to_server()
{
	char radiostat0[10];
	char radiostat1[10];

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
		  if (recv(sockreg,&rx_cbuffer,rsize) <= 0) break;
		  cbuffer_copy_to_str(&rx_cbuffer, buf);
	      // Check the Request Header
		  getidx=strindex((char *)buf,GET_STR);
		  postidx=strindex((char *)buf,POST_STR);
		  if (getidx >= 0 || postidx >= 0) {

			  // Now check the Radio Button for POST request
				if (postidx >= 0)
				{
				  if (strindex((char *)buf,"radio=0") > 0)
		//#if _DEBUG_MODE
			//
		//#endif
				  {
					log0("LED OFF\r\n",MESSAGE_BUFFER_SIZE_16);
					LED_OFF;
				  	led_status = 0;
				  }
				  if (strindex((char *)buf,"radio=1") > 0)
		//#if _DEBUG_MODE
		//
		//#endif
				  {
					  log0("LED ON\r\n",MESSAGE_BUFFER_SIZE_16);
					  LED_ON;
				  	  led_status = 1;
				  }
				}
				log0("Received an HTTP request!\r\n",MESSAGE_BUFFER_SIZE_50);
				log0("Content:\r\n",MESSAGE_BUFFER_SIZE_16);
				uart_putch_cbuffer(&rx_cbuffer, (rsize+1));
				log0("\r\n",2);
				// Create the HTTP Response	Header
				strcpy((char *)buf,"HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n");
				strcat((char *)buf,"<html><body><span style=\"color:#0000A0\">\r\n");
				strcat((char *)buf,"<h1>Embedded Web Server</h1>\r\n");
				strcat((char *)buf,"<h2>A Project by Kaushik and Ryan</h2>\r\n");
				strcat((char *)buf,"<h3>Components: KL25Z board, WIZ811MJ NIC and HD44780 LCD</h3>\r\n");
				strcat((char *)buf,"<p><form method=\"POST\">\r\n");
				if (send(sockreg,buf,strlen((char *)buf)) <= 0) break;

				if (led_status == 1) {
				  strcpy(radiostat0,"");
				  strcpy(radiostat1,"checked");
				} else {
				  strcpy(radiostat0,"checked");
				  strcpy(radiostat1,"");
				}

				// Create the HTTP Radio Button 0 Response
				strcpy((char *)buf,"<p><input type=\"radio\" name=\"radio\" value=\"0\" ");
				strcat((char *)buf,radiostat0);
				strcat((char *)buf,">LED OFF\r\n");
				strcat((char *)buf,"<br><input type=\"radio\" name=\"radio\" value=\"1\" ");
				strcat((char *)buf,radiostat1);
				strcat((char *)buf,">LED ON\r\n");
				strcat((char *)buf,"<p>\r\n");
				strcat((char *)buf,"<input type=\"submit\">\r\n");
				strcat((char *)buf,"</form></span></body></html>\r\n");

				// Now Send the HTTP Remaining Response
				if (send(sockreg,buf,strlen((char *)buf)) <= 0) break;

		  }
		  else
		  {
			  lcd_print_cbuff(&rx_cbuffer);
			  uart_putch_cbuffer(&rx_cbuffer, (rsize+1));
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
