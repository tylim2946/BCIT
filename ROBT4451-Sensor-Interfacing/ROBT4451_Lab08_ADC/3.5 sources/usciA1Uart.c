/*************************************************************************************************
 * usciA1Uart.c
 * - C source file for MSP430 USCI UART A1
 *
 *  Author: Greg Scutt
 *  Created on: March 1, 2017
 *  Modified: May 1, 2021 by Taeyoon Rim
 **************************************************************************************************/
#include <msp430.h>
#include <stdio.h>
#include <usciA1Uart.h>

#define TXD_A1 BIT4 //Transmit Data on P4.4
#define RXD_A1 BIT5 //Receive Data on P4.5

// from Table 36-5. Commonly Used Baud Rates, Settings, and Errors, UCOS16= 1
#define UCBR 65
#define UCBRS 0
#define UCBRF 2

// usciA1UartGets
char rxGetsBuffer[BUFF_SIZE];

// USCIA1_ISR
char usciA1Ready = 0;
int rxIdx = 0;
char usciA1RxBuff[BUFF_SIZE];

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
* Modified: May 1, 2021 by Taeyoon Rim
************************************************************************************/
void usciA1UartInit()
{
	P4SEL |= TXD_A1 | RXD_A1;

	UCA1CTL1 |= UCSWRST; 			// USCI A1  Software Reset Enabled

	UCA1CTL1 |= UCSSEL_2; 		// select SMCLK. User is responsible for setting this rate.
	                            // divide CLK by 20

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

	// clear past RXIFG and enable RXIFG interrupt
	UCA1IFG &= ~UCRXIFG;                    // clear  RXIFG interrupt flag
	UCA1IE |= UCRXIE;                       // enable RXIFG interrupt
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
            rxGetsBuffer[index] = UCA1RXBUF;
        else
            rxGetsBuffer[index] = '\0';

        // clear interrupt flag
        // UCA1IFG &= ~UCRXIFG;
    } while(rxGetsBuffer[index++] != '\0' && index < BUFF_SIZE - 1);

    if (rxGetsBuffer[index - 1] != '\0') // if unsuccessful (received string does not fits into BUFF_SIZE)
    {
        result = NULL;
    }
    else // if successful
    {
        strcpy(rxString, rxGetsBuffer);
        result = rxString;

        // echo rxString back to console
        char outputStr[BUFF_SIZE];
        sprintf(outputStr, "\n\r%s", rxString);
        usciA1UartTxString(outputStr);
    }

    return result;
}

char usciA1UartIsRxd(void)
{
    char result = 1;

    if (!usciA1Ready)
        result = 0;

    usciA1Ready = 0; // reset ready bit

    return result;
}

// write an ISR to receive byte and store it in a buffer & set ready flag
#pragma vector = USCI_A1_VECTOR
__interrupt void USCIA1_ISR(void)
{
    switch(__even_in_range(UCA1IV, 0x02))
    {
    case 0x02: // data received
        if (UCA1RXBUF != '\r')
        {
            usciA1RxBuff[rxIdx++] = UCA1RXBUF;
        }
        else
        {
            usciA1RxBuff[rxIdx] = '\0';
            rxIdx = 0;
            usciA1Ready = 1;
        }
        break;
    }
}
