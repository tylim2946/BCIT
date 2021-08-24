/*************************************************************************************************
 * main.c
 * - main source file for Activity 3.5 - Signal Sampling and Reconstruction
 *
 *  Author: Taeyoon Rim
 *  Created on: Apr 26, 2021
 *  Modified on: May 1, 2021
 **************************************************************************************************/

#include <msp430.h>
#include <adc12.h>
#include <usciA1Uart.h>
#include <incSensor.h>
#include "stdio.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// initialize modules
	adc12Cfg(REF_2V5, MODE_PULSESAMPLE, TRIG_TIMER, ADC12INCH_0);
	usciA1UartInit();

    // enable global interrupt
    __enable_interrupt();

    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

	while(1)
	{
	    if (adc12IsRxd())
	    {
	        usciA1UartTxString("\r\n");
	        sprintf(str1, "\r\nAng: %0.4f degrees", dout2Ang(adc12Results));
	        sprintf(str2, "\r\nAng Ave: %0.4f g", dout2AngAve());
	        usciA1UartTxString(str1);
	        usciA1UartTxString(str2);
	    }
	}

	__disable_interrupt(); // disable global interrupts
	return 0;
}
