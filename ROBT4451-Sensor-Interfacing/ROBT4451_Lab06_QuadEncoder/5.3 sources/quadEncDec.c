/*************************************************************************************************
 * quadEncDec.c
 * - C implementation or source file for quadrature encoder.
 *
 *  Author: Taeyoon Rim
 *  Created on: Mar 22, 2021
 *  Modified: Mar 22, 2021
 **************************************************************************************************/

// quadrature encoder pin connectivity --> to MSP-EXP430F5529LP EVM.
// 5V          -->     3.3 V
// GND         -->     GND
// A-A         -->     MS430EVM  P1.2
// B-B         -->     MS430EVM  P1.3
// I-Index     -->     N/A

#include <msp430.h>
#include <quadEncDec.h>

// PORT1 -> highest priority
#define RES BIT1        // P1.1
#define A   BIT2        // P1.2
#define B   BIT3        // P1.3

#define UPDATE_STATE prevState = currState; currState = P1IN & (A + B)
#define UPDATE_EDGESELECT P1IES &= ~(A + B); P1IES |= currState         // clear IES for A and B then update based on currState
#define UPDATE_DIR dir = (prevState & A) ^ (currState & B)
#define UPDATE_POS posCount += dir ? 1 : posCount -1

unsigned int posCount = 0;
unsigned char dir = 0;      // 1 = CW; 0 = CCW
unsigned char prevState, currState;

void quadEncDecInit()
{
    // configure ports
    P1DIR &= ~(A + B + RES);
    P1OUT |= RES;               // pull-up resistor
    P1REN |= RES;               // pull-up resistor

    // configure interrupt
    P1IE |= A + B + RES;
    P1IFG &= ~(A + B + RES);
    P1IES &= ~RES;              // detect rising edge

    // initialize the decoder
    UPDATE_STATE;
    UPDATE_EDGESELECT;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
    switch(__even_in_range(P1IV, 0x08))
    {
    case 0x04: // reset pushbutton
        posCount = 0;
        break;
    case 0x06: // A
        UPDATE_STATE;
        UPDATE_EDGESELECT;
        UPDATE_DIR;
        UPDATE_POS;
        break;
    case 0x08: // B
        UPDATE_STATE;
        UPDATE_EDGESELECT;
        UPDATE_DIR;
        UPDATE_POS;
        break;
    }
}
