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
#include "ucsiSpi.h"
#include "ucsControl.h"
#include "mcp4921Dac.h"
#include "stdio.h"

#define dcoFreq 20                          //MHz.
#define sclkDiv 2                           //SPI sclk divide. SCLK MAX to the DAC is 20MHz.
                                            // sclkDiv will slow down transfer rate to DAC

int main(void)
{
    unsigned char oscFail = 1;

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	/*********Set clock frequency*********************************************/
	//unsigned char testPass = 1;
	ucsSelSource(1,1,1,1);
	oscFail = ucsDcoFreqSet (dcoFreq, 2, 1);            //set sclk to dcoFreq
	if (oscFail)
	    return 1;
	/***End***Set clock frequency*********************************************/

	// initialize modules
	adc12Cfg(REF_2V5, MODE_PULSESAMPLE, TRIG_TIMER, ADC12INCH_0);
	usciA1UartInit();
	ucsiA0SpiInit(sclkDiv);

	// set-up I/O ports
	P3SEL |= BIT3;                          // SPI A0SIMO P3.3
	P2SEL |= BIT7;                          // SPI A0CLK P2.7
	P4DIR |= CS + LDAC;                     // CS 4.0 and LDAC 4.2

    // de-assert serial control signals
    LDAC_B_DEASSERT;
    CS_B_DEASSERT;

    // clear past RXIFG and enable RXIFG interrupt
    UCA0IFG &= ~UCRXIFG;                    // clear  RXIFG interrupt flag
    UCA0IE |= (UCRXIE);                     // enable RXIFG interrupt

    // enable global interrupt
    __enable_interrupt();
    //__bis_SR_register(GIE); // enable global interrupt

	while(1)
	{
	    if (usciA1UartIsRxd())
	    {
	        adc12SetFreq(usciA1RxBuff);
	    }

	    if (adc12IsRxd())
	    {
	        dacWriteWord(adc12Result, DAC_CTRL_SET_DEFAULT);
	    }
	}

	__disable_interrupt();                  // disable global interrupts
	return 0;
}
