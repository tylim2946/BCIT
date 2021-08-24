/*************************************************************************************************
 * main.c
 * - main source file for Activity 3.4 - Sampling a sinusoid
 *
 *  Author: Taeyoon Rim
 *  Created on: Apr 26, 2021
 *  Modified on: Apr 26, 2021
 **************************************************************************************************/

#include <msp430.h>
#include <adc12.h>
#include "stdio.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// initialize modules
	adc12Cfg(REF_3V3, MODE_PULSESAMPLE, TRIG_TIMER, ADC12INCH_0);

	// enable global interrupt
	__enable_interrupt();

	// sample voltage continuously and display voltage measurements
	const int numSample = 2 * 100;
	int buffer[numSample];
	char idx = 0;

	while(idx < numSample - 1) // 2 periods
	{
	    if (adc12Ready)
	    {
	        buffer[idx++] = adc12Result;
	        adc12Ready = 0; // clear timerA0Ready
	    }
	}

	return 0;
}
