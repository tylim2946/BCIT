/*
 * ucsiSpi.c
 *
 *  Created on: Feb 15, 2017
 *      Author: Greg Scutt
 */

#include <msp430.h>
#include "ucsiSpi.h"


// these functions could be made more generic with the driver lib functions
// need a function header
void ucsiA0SpiInit(unsigned int sclkDiv){

	UCA0CTL1 |= UCSWRST;                      	// **Put state machine in USCI reset to intitialize it**

	UCA0CTL0 |= UCMST+UCSYNC+UCMSB+UCCKPH;    	// 3-pin, 8-bit SPI master
												// Clock polarity high, MSB
												//modified to add ckph so that the phase would match (rising edge)? +UCCKPL+UCCKPH
	UCA0CTL1 |= UCSSEL_2;                     	// SMCLK is source
	UCA0BR0 = (sclkDiv&0xFF);                   // divide SMCLK by sclkDiv
	UCA0BR1 = (sclkDiv>>8);                     //

	UCA0CTL1 &= ~UCSWRST;                     	// **Initialize USCI state machine**
}


// these functions could be made more generic with the driver lib functions
// need a function header
void ucsiA0SpiClkDiv(unsigned int sclkDiv){

	UCA0CTL1 |= UCSWRST;			// you always need to put state machine into reset when configuring UCSC

	UCA0BR0 = (sclkDiv&0xFF);                   // 2
	UCA0BR1 = (sclkDiv>>8);                     //


	UCA0CTL1 &= ~UCSWRST;                     	// **Initialize USCI state machine**
}

// these functions could be made more generic with the driver lib functions
void ucsiB1SpiInit(unsigned int sclkDiv){

	UCB1CTL1 |= UCSWRST;                      	// **Put state machine in USCI reset to intitialize it**

	UCB1CTL0 |= UCMST+UCSYNC+UCMSB+UCCKPH;    	// 3-pin, 8-bit SPI master
												// Clock polarity high, MSB
												//modified to add ckph so that the phase would match (rising edge)? +UCCKPL+UCCKPH
	UCB1CTL1 |= UCSSEL_2;                     	// SMCLK is source
	UCB1BR0 = (sclkDiv&0xFF);                   // divide SMCLK by sclkDiv
	UCB1BR1 = (sclkDiv>>8);                     //


	UCB1CTL1 &= ~UCSWRST;                     	// **Initialize USCI state machine**
}



void ucsiB1SpiClkDiv(unsigned int sclkDiv){

	UCB1CTL1 |= UCSWRST;			// you always need to put state machine into reset when configuring UCSC

	UCB1BR0 = (sclkDiv&0xFF);                   // 2
	UCB1BR1 = (sclkDiv>>8);                     //


	UCB1CTL1 &= ~UCSWRST;                     	// **Initialize USCI state machine**
}


#pragma vector=USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void) {
	
  switch(__even_in_range(UCB1IV,4)) // this will clear the current highest priority flag. TXIFG or RXIFG.
  {
  	  case 0: break;                          	// Vector 0 - no interrupt
  	  case 2:                                 	// Vector 2 - RXIFG. Highest priority
  		  rxFlag++;								// count the bytes SENT ...
  		  break;
  	  case 4:
  		 break;
  	  default: break;
  }
}



#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) {

  switch(__even_in_range(UCA0IV,4)) // this will clear the current highest priority flag. TXIFG or RXIFG.
  {
  	  case 0: break;                          	// Vector 0 - no interrupt
  	  case 2:                                 	// Vector 2 - RXIFG. Highest priority
  		  rxFlag++;								// count the bytes SENT ...
  		  break;
  	  case 4:
  		 break;
  	  default: break;
  }
}
