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
#include <usciA1Uart.h>
#include "stdio.h"

// PORT1 -> highest priority
#define RES BIT1        // P1.1
#define A   BIT2        // P1.2
#define B   BIT3        // P1.3

#define UPDATE_STATE prevState = currState; currState = P1IN & (A + B)
#define UPDATE_EDGESELECT if (P1IN & A) { P1IN |= A; } else { P1IN &= ~A; } if (P1IN & B) { P1IN |= B; } else { P1IN &= ~B; }
#define UPDATE_DIR dir = (prevState & A) ^ ((currState & B) >> 1)
#define UPDATE_POS posCount += dir ? 1 : -1

unsigned int posCount = 0;
unsigned char dir = 0;                  // 0 = CW; 1 = CCW
unsigned char prevState = 0, currState = 0;

char str[30];

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
        switch(currState & (A + B))
        {
        case 0:
            // CW
            dir = 1;
            posCount -= 1;
            break;
        case A:
            // CCW
            dir = 0;
            posCount += 1;
            break;
        case B:
            // CCW
            dir = 0;
            posCount += 1;
            break;
        case A + B:
            // CW
            dir = 1;
            posCount -= 1;
            break;
        }

        currState = P1IN & (A + B);
        P1IFG &= ~A;
        break;
    case 0x08: // B
        switch(currState & (A + B))
        {
        case 0:
            // CCW
            dir = 0;
            posCount += 1;
            break;
        case A:
            // CW
            dir = 1;
            posCount -= 1;
            break;
        case B:
            // CW
            dir = 1;
            posCount -= 1;
            break;
        case A + B:
            // CCW
            dir = 0;
            posCount += 1;
            break;
        }

        currState = P1IN & (A + B);
        P1IFG &= ~B;
        break;
    }
}
