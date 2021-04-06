#include <msp430.h>
#include <stdlib.h>
#include <usciA1Uart.h>
#include <usciB1Spi.h>

#define VERSION 3

// 5.2.1
/**********************************************/
#define LED2 BIT7 // LED2 on P4.7
#define CLEAR_LED P4OUT &= LED2
#define TOGGLE_LED P4OUT ^= LED2
#define DELAY_500MS __delay_cycles((unsigned long) 500000)
/**********************************************/

// 5.2.2
/**********************************************/
#define BUFF_SIZE 50
/**********************************************/

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	if (VERSION == 1)
	{
	    // 5.2.1
	    /**********************************************/
	    usciA1UartInit();
	    usciB1SpiInit(MST, 16, MODE_DEFAULT, !LOOPBACK);

	    UCA1IE |= UCRXIE;
	    __enable_interrupt();

	    P4DIR |= LED2;
	    CLEAR_LED;

	    do
	    {
	        // flashLed every one second
	        DELAY_500MS;
	        TOGGLE_LED;
	        usciB1SpiPutChar('A');
	    } while (1);
	    /**********************************************/
	}
	else if (VERSION == 2)
	{
	    // 5.2.3
	    /**********************************************/
	    char rxString[BUFF_SIZE];
	    char buffer[BUFF_SIZE];

	    usciA1UartInit();
	    usciB1SpiInit(MST, 1, MODE_DEFAULT, !LOOPBACK);

	    __enable_interrupt();

	    do
	    {
	        usciA1UartGets(rxString); // wait for a string
	        int buffLen = strlen(rxString);
	        numStringToInt(rxString, buffer);
	        usciB1SpiTxBuffer(buffer, buffLen); // transmit buffer of integers
	    } while (1);
	    /**********************************************/
	}
	else if (VERSION == 3)
	{
	    // 5.2.4
	    /**********************************************/
	    char rxString[BUFF_SIZE];
	    char buffer[BUFF_SIZE];

	    usciA1UartInit();
	    usciB1SpiInit(MST, 16, MODE_DEFAULT, LOOPBACK);

	    UCB1IE |= UCRXIE;
	    __enable_interrupt();

	    do
	    {
	        usciA1UartGets(rxString); // wait for a string
	        int buffLen = strlen(rxString);
	        numStringToInt(rxString, buffer);
	        usciB1SpiTxBuffer(buffer, buffLen); // transmit buffer of integers
	    } while (1);
	    /**********************************************/
	}

	return 0;
}

/************************************************************************************
* Function: numStringToInt
* - atoi each byte in rxString and store in buffer
* Arguments:
*   rxString - pointer to string
*   buffer - pointer to integer array
* return: none
*
* Author: Taeyoon Rim
* Date: February 27th, 2021
* Modified: March 7th, 2021
************************************************************************************/
void numStringToInt(char * rxString, char * buffer)
{
    unsigned int idx = 0;
    char c[2] = "\0\0"; // atoi() needs to see the null character at the end

    // convert char to int
    while(rxString[idx] != '\0')
    {
        c[0] = rxString[idx];
        buffer[idx++] = atoi(c);
    }
}
