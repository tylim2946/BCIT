#include <msp430.h> 
#include <pioInt.h>

/*****************************************************************
 * Course: ROBT4451
 *
 * Lab 2. pioInt
 *
 * Purpose:
 *   - to interface modules with MSP430
 *
 * Author: Taeyoon Rim
 * Group: M1
 *
 * Declaration: I, Taeyoon Rim, declare that the following program was written by me.
 *
 * Date Created: Jan 11, 2021
 * Data Modified: Jan 18, 2021
 *****************************************************************/

#define LED 0x7
#define SW 0x5

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	unsigned char mData;

	pioIntInit();
	pioIntWrite(LED, 0xAA);
	pioIntRead(LED, &mData);
	pioIntRead(SW, &mData);
	pioIntWrite(LED, mData);
}

