#include <msp430.h>
#include <stdlib.h>
#include <usciB1Spi.h>

#define VERSION 3

// 5.2.1
/**********************************************/
#define LED2 BIT7 // LED2 on P4.7
#define CLEAR_LED P4OUT &= LED2
#define TOGGLE_LED P4OUT ^= LED2
#define DELAY_500MS __delay_cycles((unsigned long) 500000);
/**********************************************/

// 5.2.2
/**********************************************/
#define BUFF_SIZE 50
/**********************************************/

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	char rxString[BUFF_SIZE];
	int buffer[BUFF_SIZE];

	usciB1SpiInit(SLV, 16, MODE_DEFAULT, !LOOPBACK);

	UCB1IE |= UCRXIE;
	__enable_interrupt();

	P4DIR |= LED2;
	CLEAR_LED;

	do
	{
	    DELAY_500MS
	    TOGGLE_LED;
	} while (1);

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
* Modified: February 28th, 2021
************************************************************************************/
void numStringToInt(char * rxString, int * buffer)
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
