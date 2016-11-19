/*
 * uart.c
 *
 *  Created on: Oct 7, 2016
 *      Author: kprakash
 */
#include <stddef.h>
#include "MKL25Z4.h"
#include "uart.h"
#include "stdint.h"


/*
 * This function will initialize all the registers necessary for the UART
 * to operate.
 *
 * PTA1 and PTA2 are rx and tx respectively connected to SDA Debugger(USB)
 * This will help us to interface the serial terminal on pc
 *
 * The function takes a baud rate to calculate the value to be
 * set into the BDL register
 */
void uart0_init(uint32_t baudrate)
{
	uint16_t bdl;
	NVIC_ISER = 1 << UART0_IRQn;        // Enable Interrupts on UART0

	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;  // SETS CLOCK FOR PORT-A
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;  // SETS CLOCK FOR UART-0

	UART0_C2 &= ~(UART0_C2_RE_MASK | UART0_C2_TE_MASK);  // Disable Transmit and Receive on UART before configuring the clock
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);   // Setting clock source as MCGFLLCLK or MCGPLLCK/2
	PORTA_PCR1 |= PORT_PCR_MUX(2);        // Setting Pin 1 of Port A to be UART0_RX
    PORTA_PCR2 |= PORT_PCR_MUX(2);		  // Setting Pin 2 of Port A to be UART0_TX

    bdl = (CORECLK / CLOCKDIV) / baudrate; // to obtain the prescale divisor for UART Baud rate generation
    UART0_C4 = UART0_C4_OSR(CLOCKDIV - 1); // Setting the Over Sampling ratio as 16 - 0b1111. This is the default value.
    UART0_BDL = (bdl - 1);
    UART0_C1 |= UART0_C1_LOOPS(0); // Setting Loop mode to be normal. No Echo where tx output is connected to rx output.
    //UART0_C2 |= UART0_C2_RIE_MASK; // Enable the Receive Interrupt so that Hardware will set the Interrupt flag
    UART0_C2 |= UART0_C2_RE_MASK | UART0_C2_TE_MASK; // Enable Transmitter and Receiver


}

/*
 * This function will put a character into the user's terminal session screen.
 * It takes the character to be printed by the user and transfers it over UART
 */
void uart0_putch(char s)
{
	 // Wait till Transmit Data buffer is empty. 0 -full, 1 - empty
	 while(!(UART0_S1 & UART0_S1_TDRE_MASK));
	 UART0_D = s; // Fill the Transmit buffer data by writing into it.

}

/*
 * This function will obtain a character obtained by the user over UART.
 */
char uart0_getch()
{   // Wait till Receive Data buffer is full. 0 - empty, 1 - full.
	while(!(UART0_S1 & UART0_S1_RDRF_MASK));
    return (UART0_D); //Empty out the Receive Data buffer by reading the data.
}

/*
 * This function will print a string and paste it on the console till a new line is reached.
 */
int uart0_getstr(char *str)
{
    int is_end_of_str = 0;
    uint32_t len = 0;
    char c;
    while(!is_end_of_str)
    {
        c = uart0_getch();
        if (c == '\r')	// New Line encountered
        {
            *str = '\0';	// appending a NULL character at the end to signal the end of string
            is_end_of_str = 1;
            break;
        }

        else
        {
           *str++ = c; // Keeps on appending characters in str until carriage return found
           len++;
        }
    }
    //*st_len = len;
    return len;
}

void uart0_getstr_n(char *str, uint8_t size)
{
    int is_end_of_str = 0;
    char c;
    while( size != 0)
    {
        c = uart0_getch();
        uart0_putch(c);
        if (c == '\r')	// New Line encountered
        {
            *str = '\0';	// appending a NULL character at the end to signal the end of string
            break;
        }

        else
        {
           *str++ = c; // Keeps on appending characters in str until carriage return found
           size--;
        }

    }
}




