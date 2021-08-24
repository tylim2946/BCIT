/*
 * UcsControl.h
 *
 * - MSP430F5529 UCS API function module interface
 * -
 *
 *  Created on: Feb 12, 2017
 *      Author: Greg Scutt
 */

#include <msp430.h>


#ifndef UCSCONTROL_H_
#define UCSCONTROL_H_

#define DEBUG 0

#define DCO_MAX_FREQ 16 // .  Max DCO Frequency permissible

#define REFOCLK_FREQ 32768	// frequency of internal oscillator
#define XT1_FREQ REFOCLK_FREQ // frequency of external watch crystal oscillator
#define XT2_FREQ 4e6           // frequency of external high freq  oscillator

#define DCO_RSEL5_MAX DCO_MAX_FREQ
#define DCO_RSEL5_MIN 6

#define DCO_RSEL4_MAX 12
#define DCO_RSEL4_MIN 3

#define DCO_RSEL3_MAX 6
#define DCO_RSEL3_MIN 1.5

#define DCO_RSEL2_MAX 3
#define DCO_RSEL2_MIN .75

#define DCO_RSEL1_MAX 1.5
#define DCO_RSEL1_MIN 0.4

#define DCO_RSEL0_MAX .7
#define DCO_RSEL0_MIN 0.2

// UcsControl function protoType Definition
void setVcoreUp (unsigned int level);
unsigned int ucsDcoRsel (double fDcoClk);
unsigned int ucsDcoFreqSet (double fDcoClk, unsigned char fllRefClk, unsigned char fllRefDiv);
void ucsSelSource (unsigned int divM, unsigned int divS, unsigned int divA, unsigned int divPA);


#endif /* UCSCONTROL_H_ */
