/*************************************************************************************************
 * main.c
 * - main C implementation or source file.
 *
 *  Author: Taeyoon Rim
 *  Created on: Mar 22, 2021
 *  Modified: Apr 9, 2021
 **************************************************************************************************/

#include <msp430.h> 
#include <quadEncDec.h>
#include <usciA1Uart.h>
#include <usciB1Spi.h>
#include "stdio.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// initialize modules
	usciA1UartInit();
	usciB1SpiInit(MST, 1, MODE_DEFAULT, !LOOPBACK);
	quadEncDecInit();

	// enable global interrupt
	__enable_interrupt();

	char str[30];

	while(1)
	{
	    sprintf(str, "\r\nposCount: %d\tdir: %s", posCount, dir?"CW":"CCW");

	    usciA1UartTxString(str);
	    usciB1SpiTxString(str);
	}

	return 0;
}
