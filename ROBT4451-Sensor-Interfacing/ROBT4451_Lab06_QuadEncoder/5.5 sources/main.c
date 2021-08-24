/*************************************************************************************************
 * main.c
 * - main C implementation or source file.
 *
 *  Author: Taeyoon Rim
 *  Created on: Mar 22, 2021
 *  Modified: Apr 10, 2021
 **************************************************************************************************/

#include <msp430.h> 
#include <pulseTimingA0.h>
//#include <quadEncDec.h>
#include <usciA1Uart.h>
//#include <usciB1Spi.h>
#include "stdio.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// initialize modules
	usciA1UartInit();
	//quadEncDecInit();
	pulseTimingA0Init();
	//pulseCountingA0Init();

	// enable global interrupt
	__enable_interrupt();

	char str[30];

	while(1)
	{
	    sprintf(str, "\r\nvelocity: %.4f rad/s", getVelocity());
	    usciA1UartTxString(str);
	}

	return 0;
}
