 /*************************************************************************************************
 * mcp4921Dac.c
 * - top level file for Lab 7
 * Demonstrates use of mcp4921Dac.c. A 12 bit DAC with SPI digital interface to uC
 * Assumes MSP430 is interfaced to mcp4921 through SPI with UCSIA0.
 * dcoFreq and sclkDiv can be set by user
 *
 *
 *  Author: Greg Scutt
 *  Created: April 8th, 2017 . modified function write to function dacWriteWord
 *  removed unneeded __delay_cycles, created serial interface definitons.
 **************************************************************************************************/


#include <msp430.h>
#include "mcp4921Dac.h"



/**************************************************************
 * dacWriteWord
 * Purpose: write values to the SPI DAC MCP4921,
 * 			controls LDAC, CS pins
 *
 * 			As per the datasheet, LDAC can be held low, it would
 * 			no longer be a double buffered DAC
 *
 * Input:	dacWord - 12 bit DAC data
 *			dacCtrl - 4 bit control nibble
 * Returns:	nothing
 *
 * Function:1. asserts CS_B pin
 * 			2. clears rxFlag
 * 			3.  (dacCtrl + dacWord[15:8]) --> SPI TXBUFF --> DAC
 * 				bit15 - 0 means write, 1 means ignore
 *				bit14 - 1 means buffer vref, 0 means don't buffer vref
 *				bit13 - 1 means 1x gain, 0 means 2x gain
 *				bit12 - 1 means active Voutput, 0 means shutoff voutput
 *			4. send the LSB to TXBuf
 *			5. waits for both RX interrupts to occur
 *			6. resets rxflag (ensures that both bytes have sent) to 0
 *			7. reset CS pin
 *			8. strobe LDAC (it's a double buffered chip)
 *
 * NB!!!	the ISR for the RXIFG needs to increment rxflag to count
 * 			the number of bytes that are sent.
 *
 * Author:	Chris Baitz
 * Date:	March 2017
 * Modified: Greg Scutt April 8th, 2017. revisions: remove delays, add dacCtrl input argument
 *************************************************************/
void dacWriteWord(unsigned int dacWord, unsigned int dacCtrl)
{
	char * dacBytePtr = (char *)&dacWord;	// set-up a pointer to dacWord, so access to LSB and MSB is possible
											// needed for 8 bit SPI TXBUFF.


	CS_B_ASSERT; 							//	 CS_B LOW

	dacWord |= dacCtrl;						// add dacCtrl to MSNibble of dacWord

	// must *WAIT* 40ns after CS_B asserts before first SCLK cycle. ALWAYS satisfied.

	UCA0TXBUF = *(dacBytePtr+1);			// MSByte --> TXBUFF
	while(!(UCA0IFG&UCTXIFG));				// wait for the TXBUFF ready. not efficient if SCLK << MCLK
	UCA0TXBUF = *dacBytePtr;				// LSByte --> TXBUFF

	while(rxFlag<2);						// waiting until both bytes are sent over SPI to DAC. Effecively polling..
	rxFlag = 0;								// clear rxFlag for next write

	// must *WAIT* 40 ns minimum before ldac is strobed. ALWAYS satisfied.

	CS_B_DEASSERT;							// CS_B HIGH

	// LDAC may be tied low for single buffered mode.

	// load the DAC register with LDAC strobe.   H->L->H
	LDAC_B_ASSERT;							// assert   LDAC
	// must *WAIT* minimum of 100ns. ALWAYS satisfied.
	LDAC_B_DEASSERT;						// de-assert LDAC

}

/************************************************************************************
* Function: DACSet
* - set the output of the DAC
* Arguments:
*   voltage - desired output voltage
* return: none
*
* Author: Taeyoon Rim
* Date: April 12, 2021
* Modified: April 12, 2021
************************************************************************************/
void dacSet(double voltage)
{
    unsigned int dacCtrl = (~DAC_CFG_WR & ~DAC_CFG_BUF & (DAC_CFG_GA + DAC_CFG_SHDN)) & 0xF000;
    unsigned int dacWord = 0; // convert voltage into respective binary digits

    dacWriteWord(dacCtrl, dacWord);
}
