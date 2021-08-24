/*************************************************************************************************
 * main.c
 * - main source file for Activity 3.3 - A DC Voltmeter
 *
 *  Author: Taeyoon Rim
 *  Created on: Apr 26, 2021
 *  Modified on: Apr 26, 2021
 **************************************************************************************************/

#include <msp430.h>
#include <timerA0.h>
#include <adc12.h>
#include <usciA1Uart.h>
#include "stdio.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// initialize modules
	usciA1UartInit();
	timerA0Init(40); // 25Hz
	adc12Cfg(REF_3V3, MODE_EXTENDED, TRIG_SW, ADC12INCH_0);

	// enable global interrupt
	__enable_interrupt();

	// sample voltage continuously and display voltage measurements
	char str[30];

	while(1)
	{
	    if (timerA0Ready)
	    {
	        adc12SampSWConv();
	        double voltage = CONV_D2V * adc12Result;
	        sprintf(str, "\r\nvoltage: %.6f V", voltage);
	        usciA1UartTxString(str);
	        timerA0Ready = 0; // clear timerA0Ready
	    }
	}

	return 0;
}
