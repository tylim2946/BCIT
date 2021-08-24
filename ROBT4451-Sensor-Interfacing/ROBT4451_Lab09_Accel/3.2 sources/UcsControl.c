/*
 * UcsControl.c
 * - MSP430F5529 UCS API function module impementation
 * -
 *
 *  Created on: Feb 12, 2017
 *      Author: Greg Scutt
 */
#include <math.h>
#include <msp430.h>
#include "UcsControl.h"

/************************************************************************************
 * Function: setVcoreUp
 * - sets internal core voltage using PMM. Required for higher MCLK settings
 * - code provided by TI in 2.2.4 of usermanual
 * argument: level 	- PMM core voltage level needed for MCLK setting
 * 					- valid values 0,1,2,3,4
 * return: void.
 * Author: Texas Instruments
 * Date:
 * Revision:
 ************************************************************************************
*/
void setVcoreUp (unsigned int level)
{
  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}



/* ***********************************************************************************
 * Function: ucsSelSource
 * - selects the divisor for MCLK, SMCLK, extACLK, ACLK
 * - selects the source for MCLK, SMCLK and ACLK. SMCLK, MCLK sourced from DCOCLKDIV by default.
 * argument:	divM - divS, divA, divPA are the divisors for the 4 clocks. valid values 1,2,4,8,16,32
 *
 * return: void
 * Author: Greg Scutt
 * Date: Feb 13, 2017
 * Revision: 1.0
 ************************************************************************************
 */
void ucsSelSource (unsigned int divM, unsigned int divS, unsigned int divA, unsigned int divPA)
{


	// assummes UCSCTL5 starts from 0x0000
	UCSCTL5 = 0;

	switch (divM) {
		case 1:
			UCSCTL5 |= DIVM__1; 		// div1
			break;
		case 2:
			UCSCTL5 |= DIVM__2; 		// div2
			break;
		case 4:
			UCSCTL5 |= DIVM__4; 		// div4
			break;
		case 8:
			UCSCTL5 |= DIVM__8; 		// div8
			break;
		case 16:
			UCSCTL5 |= DIVM__16; 		// div16
			break;
		case 32:
			UCSCTL5 |= DIVM__32; 		// div32
			break;
		default:
			UCSCTL5 |= DIVM__1; 		// div1

		}


	switch (divS) {
		case 1:
			UCSCTL5 |= DIVS__1; 		// div1
			break;
		case 2:
			UCSCTL5 |= DIVS__2; 		// div2
			break;
		case 4:
			UCSCTL5 |= DIVS__4; 		// div4
			break;
		case 8:
			UCSCTL5 |= DIVS__8; 		// div8
			break;
		case 16:
			UCSCTL5 |= DIVS__16; 		// div32
			break;
		case 32:
			UCSCTL5 |= DIVS__32; 		// div32
			break;
		default:
			UCSCTL5 |= DIVS__1; 		// div1

		}


		switch (divA) {
		case 1:
			UCSCTL5 |= DIVA__1; 		// div1
			break;
		case 2:
			UCSCTL5 |= DIVA__2; 		// div2
			break;
		case 4:
			UCSCTL5 |= DIVA__4; 		// div4
			break;
		case 8:
			UCSCTL5 |= DIVA__8; 		// div8
			break;
		case 16:
			UCSCTL5 |= DIVA__16; 		// div16
			break;
		case 32:
			UCSCTL5 |= DIVA__32; 		// div32
			break;
		default:
			UCSCTL5 |= DIVA__1; 		// div1

		}


	switch (divPA) {
		case 1:
			UCSCTL5 |= DIVPA__1; 		// div1
			break;
		case 2:
			UCSCTL5 |= DIVPA__2; 		// div2
			break;
		case 4:
			UCSCTL5 |= DIVPA__4; 		// div4
			break;
		case 8:
			UCSCTL5 |= DIVPA__8; 		// div8
			break;
		case 16:
			UCSCTL5 |= DIVPA__16; 		// div16
			break;
		case 32:
			UCSCTL5 |= DIVPA__32; 		// div32
			break;
		default:
			UCSCTL5 |= DIVPA__1; 		// div1

	}


	// selects the source for ACLK, MCLK and SMCLK
	// ACLK is sourced from REFOCLK
	// MCLK, SMCLK is sourced from DCOCLKDIV
	UCSCTL4 = SELA__REFOCLK | SELS__DCOCLKDIV |SELM__DCOCLKDIV;

}


/************************************************************************************
 * Function: ucsDcoRsel
 * - sets DCO range used for FLL operation
 * - uses very crude method to assign requested DCO freq to a DCO range.
 * - assigns core voltage too with setVcoreUp. A bit of a guess.
 * argument: fDcoClk 	- desired DCO clock frequency. Valid values are .5MHz to 15MHz.
 * 						- not tested > 15MHz
 *						- values > DCO_MAX_FREQ are assigned DCORSEL_5
 * return: DCO range 0 to 5.
 * Author: Greg Scutt
 * Date: Feb 13, 2017
 * Revision: 1.0
 ************************************************************************************
  */
unsigned int ucsDcoRsel (double fDcoClk)
{

	__bis_SR_register(SCG0);               		// disable the FLL before adjusting range
	UCSCTL0 = 0x0000;

	// select range/ see Table 5.19 in MSP430F5529 Data Sheet.
	// this is only one crude way to do it whereby DCRSEL is chosen
	// such that the fDcoClk will use the upper taps.
	// there are other more robust ways to choose these taps
	// the taps are there to adjust the FLL integrator
	if (fDcoClk > DCO_MAX_FREQ) {
		UCSCTL1 = DCORSEL_6;
		setVcoreUp (0x03);
		}
	else if (fDcoClk >= (DCO_RSEL4_MAX - 2)) {
		UCSCTL1 = DCORSEL_5; 	// Select DCO range 24MHz operation
		setVcoreUp (0x02);
	}
	else if (fDcoClk >= (DCO_RSEL3_MAX - 1)) {
		UCSCTL1 = DCORSEL_4;                  	// Select DCO range 12MHz operation
		setVcoreUp (0x01);
	}
	else if (fDcoClk >= (DCO_RSEL2_MAX - 0.5)){
		UCSCTL1 = DCORSEL_3;                  	// Select DCO range 6MHz operation
		setVcoreUp (0x01);
		}
	else if (fDcoClk >= (DCO_RSEL1_MAX - 0.5))
		UCSCTL1 = DCORSEL_2;                  	// Select DCO range 3MHz operation
	else if (fDcoClk >= (DCO_RSEL0_MAX - 0.2))
		UCSCTL1 = DCORSEL_1;              		// Select DCO range 1.5MHz operation
	else
		UCSCTL1 = DCORSEL_0;


	return ((UCSCTL1&0x70)>>4); // return the range selection
}


/* ***********************************************************************************
 * Function: ucsDcoFreqSet
 * - sets up the FLL to be used for setting fDcoClk
 * - sets dco range
 * - selects FLL source fllRefClk, divisor fllRefDiv and assigns frequency fDcoClk
 * - calculatates fllN for required fDcoClk
 * argument:	fDcoClk 	- desired DCO clock frequency. Valid values are .5MHz to 15MHz.
 * 				fllRefClk	- reference source for FLL.
 * 							- 1 for XT1, 2 for REFOCLK, 3 for XT2.  Any other values defaults to REFOCLK
 * 				fllRefDiv	- FLL source clock divisor. 1,2,4,8,12,16. Default is 1
 * return: fllN. 9 bit value used to set fDcoClk.
 * Author: Greg Scutt
 * Date: Feb 13, 2017
 * Revision: 1.0
 ************************************************************************************
*/
unsigned int ucsDcoFreqSet (double fDcoClk, unsigned char fllRefClk, unsigned char fllRefDiv)
{
	unsigned long int fllRefFreq = 0;
	double fllN = 0;
	//unsigned long int settleTime = 400000;

	__bis_SR_register(SCG0);               		// disable the FLL before adjusting DCO with FLL


	ucsDcoRsel (fDcoClk);	// set dcoRange

	// select FLL source clock and frequency
	switch (fllRefClk) {
		case 1:
			UCSCTL3 |= SELREF__XT1CLK; // XT1CLK, external oscillator
			fllRefFreq = XT1_FREQ;
			break;

		case 2:
			UCSCTL3 |= SELREF__REFOCLK; // REFOCLK, internal oscillator
			fllRefFreq = REFOCLK_FREQ;
			break;

		case 3:
			UCSCTL3 |= SELREF__XT2CLK; // XT1CLK, internal oscillator
			fllRefFreq = XT2_FREQ;
			break;

		default:
			UCSCTL3 |= SELREF__REFOCLK; // REFOCLK, internal oscillator
			fllRefFreq = REFOCLK_FREQ;
		}


		// divide source clock
	switch (fllRefDiv) {
		case 1:
			UCSCTL3 |= FLLREFDIV__1; // div1
			break;
		case 2:
			UCSCTL3 |= FLLREFDIV__2; // div2
			break;
		case 4:
			UCSCTL3 |= FLLREFDIV__4; // div4
			break;
		case 8:
			UCSCTL3 |= FLLREFDIV__8; // div8
			break;
		case 12:
			UCSCTL3 |= FLLREFDIV__12; // div12
			break;
		case 16:
			UCSCTL3 |= FLLREFDIV__16; // div16
			break;

		default:
			UCSCTL3 |= FLLREFDIV_0; // div1 is default

	}

	// calculate N
	// fDcoClk = D(N+1)*(fllRefClk/fllRefDiv)
	// fDcoClkDiv = (N+1)*(fllRefClk/fllRefDiv)
	fllN = ceil((fDcoClk*1e6/fllRefFreq - 1)); 	// (fllN + 1) * FLLRef/fllRefDiv = fDcoClk

// ***********************
	if (DEBUG) {
		UCSCTL1 = DCORSEL_4;  // set dco range manually
		fllN = 187; // set N manually.
	}
// ***********************

	UCSCTL2 = FLLD_1 + (int)fllN;        	//  D*(fllN + 1) * FLLRef/fllRefDiv = fDcoClkDiv. FLLD_1 so Div by 2.

	__bic_SR_register(SCG0);                  // Enable the FLL control loop

	 // Worst-case settling time for the DCO when the DCO range bits have been
	 // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
	 // UG for optimization.
	 // 32 x 32 x 12 MHz / 32,768 Hz = 375000 = MCLK cycles for DCO to settle
	 //settleTime = (long int)(fllRefDiv*32*32*fDcoClk*1e6/fllRefFreq);
	 // can't be a variable since it needs to insert assembler at compile time
	__delay_cycles(700000);

	int i = 0;
	do
	{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG;                      	// Clear fault flags
		i++;
	} while ((SFRIFG1&OFIFG) && i<3);              // Test oscillator fault flag

	return (SFRIFG1&OFIFG);
	//return fllN;
}



