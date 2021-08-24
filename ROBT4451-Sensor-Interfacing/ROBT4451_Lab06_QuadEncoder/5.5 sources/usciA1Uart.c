/*************************************************************************************************
 * usciA1Uart.c
 * - C source file for MSP430 USCI UART A1
 *
 *  Author: Greg ScAutt
 *  Created on: March 1, 2017
 *  Modified: February 20th, 2021 by Taeyoon Rim
 **************************************************************************************************/
#include <msp430.h>
#include <stdio.h>
#include <usciA1Uart.h>

#define TXD_A1 BIT4 //Transmit Data on P4.4
#define RXD_A1 BIT5 //Receive Data on P4.5

#define UCBRF (UCBRF2 + UCBRF1) // UCBRF = 6
#define UCBRS (UCBRS0)  // UCBRS = 1
#define UCBR 3  // UCBR = 3

char rxBuffer[BUFF_SIZE];

/************************************************************************************
* Function: usciA1UartInit
* - configures UCA1 UART to use SMCLK, no parity, 8 bit data, LSB first, one stop bit
*  BAUD rate = 19.2Kbps with 16xoversampling.
*  assumes SMCLK = 2^20 Hz.
* Arguments: none, but baud rate would be useful
* Return: none
*
* Author: Greg Scutt
* Date: March 1st, 2017
* Modified: February 20th, 2021 by Taeyoon Rim
************************************************************************************/
void usciA1UartInit()
{
	P4SEL |= TXD_A1 | RXD_A1;

	UCA1CTL1 |= UCSWRST; 			// USCI A1  Software Reset Enabled

	UCA1CTL1 |= UCSSEL_2; 		// select SMCLK. User is responsible for setting this rate.

	UCA1CTL0 = 0; 				// RESET UCA1CTL0 before new configuration
	UCA1CTL0 &=	~UCPEN			// No Parity
			 &	~UCMSB			// LSB First
			 &	~UC7BIT			// 8 bits of data
			 &	~UCSPB			// 1 stop bit
			 &	~UCSYNC;		// UART Mode

	UCA1BR1 = 0; // calculate and confirm with table
	UCA1BR0 = UCBR; // calculate and confirm with table
	UCA1MCTL = UCBRF + UCBRS + (UCOS16); // calculate and confirm with table.

	UCA1CTL1 &= ~UCSWRST; 		//  configured. take state machine out of reset.
}

/************************************************************************************
* Function: usciA1UartTxChar
* - writes a single character to UCA1TXBUF if it is ready
* Arguments: txChar - byte to be transmitted
* Return: none
*
* Author: Greg Scutt
* Date: March 1st, 2017
* Modified: March 1st, 2017
************************************************************************************/
void usciA1UartTxChar(unsigned char txChar)
{
	while (!(UCA1IFG & UCTXIFG));
	UCA1TXBUF = txChar;	 // if TXBUFF ready then transmit a byte by writing to it
}

/************************************************************************************
* Function: usciA1UartTxString
* - writes a C string of characters, one char at a time to UCA1TXBUF by calling
*   usciA1UartTxChar. Stops when it encounters  the NULL character in the string
*   does NOT transmit the NULL character
* Arguments: txChar - pointer to char (string) to be transmitted
* Return: number of characters transmitted
*
* Author: Greg Scutt
* Date: March 1st, 2017
* Modified: February 15th, 2021 by Taeyoon Rim
************************************************************************************/
int usciA1UartTxString(unsigned char * txChar)
{
    unsigned int ptr = 0;

    while (txChar[ptr] != 0) // while not a null character
    {
        usciA1UartTxChar(txChar[ptr++]) ;
    }

    return ptr;
}

/************************************************************************************
* Function: usciA1UartTxBuffer
* - writes bufLen characters from buffer
* Arguments:
*   buffer - pointer to buffer to be transmitted
*   bufLen - number of bytes to transmit
* return: number of bytes transmitted
*
* Author: Taeyoon Rim
* Date: February 15th, 2021
* Modified: February 15th, 2021
************************************************************************************/
int usciA1UartTxBuffer(char * buffer, int bufLen)
{
    unsigned int ptr = 0;
    unsigned char outputStr[BUFF_SIZE] = 0;

    while (!(ptr >= bufLen || buffer[ptr] == 0)) // while not a null character
    {
        sprintf(outputStr, "%s%c", outputStr, buffer[ptr++]);
    }

    // display result to the console
    sprintf(outputStr, "%s\n\r%d characters transmitted\n\r", outputStr, ptr);
    usciA1UartTxString(outputStr);

    return ptr;
}

/************************************************************************************
* Function: usciUartGets
* - receives a string entered from the console and store it into rxBuffer
* Arguments:
*   rxString - pointer to string; is overwritten with string entered from the console
* return: if successful, returns the pointer to rxString. If not, return null
*
* Author: Taeyoon Rim
* Date: February 18th, 2021
* Modified: February 20th, 2021
************************************************************************************/
char * usciA1UartGets(char * rxString)
{
    char * result;
    int index = 0;

    do
    {
        while(!(UCA1IFG & UCRXIFG)); // polling

        if (UCA1RXBUF != '\r')
            rxBuffer[index] = UCA1RXBUF;
        else
            rxBuffer[index] = '\0';

        // clear interrupt flag
        // UCA1IFG &= ~UCRXIFG;
    } while(rxBuffer[index++] != '\0' && index < BUFF_SIZE - 1);

    if (rxBuffer[index - 1] != '\0') // if unsuccessful (received string does not fits into BUFF_SIZE)
    {
        result = NULL;
    }
    else // if successful
    {
        strcpy(rxString, rxBuffer);
        result = rxString;

        // echo rxString back to console
        char outputStr[BUFF_SIZE];
        sprintf(outputStr, "\n\r%s", rxString);
        usciA1UartTxString(outputStr);
    }

    return result;
}
