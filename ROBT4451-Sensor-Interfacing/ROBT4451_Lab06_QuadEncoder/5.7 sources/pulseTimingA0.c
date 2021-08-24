/*************************************************************************************************
 * pulseTimingA0.c
 * - C implementation or source file for pulse timing method.
 *
 *  Author: Taeyoon Rim
 *  Created on: Mar 29, 2021
 *  Modified: Apr 10, 2021
 **************************************************************************************************/

// quadrature encoder pin connectivity --> to MSP-EXP430F5529LP EVM.
// 5V          -->     3.3 V
// GND         -->     GND
// A-A         -->     MS430EVM  P1.2 (TA0CCI1A)
// B-B         -->     N/A
// I-Index     -->     N/A

#include <msp430.h>
#include <pulseTimingA0.h>

#define A   BIT2        // P1.2

#define SMCLK 1.048E6
#define REV_COUNT 1150
#define PI 3.14159265359

unsigned int pulseCount = 0;    // SMCLK pulse count
int error = 1; // no error: 1, error: 0

const double angResPulse = PI * 2 / REV_COUNT * SMCLK;

void pulseTimingA0Init()
{
    // configure ports
    P1DIR &= ~A;
    P1SEL |= A;

    // configure timer A registers
    TA0CTL |= TASSEL_2 + MC_2 + ID_0;   // SMCLK, continuous up, input divide by 1
    TA0EX0 |= TAIDEX_0;                 // divide by 1
    TA0CCTL1 |= CAP + SCS + CCIS_0 + CM_1;    // capture mode, synchronize, CCIxA, capture on rising edge

    // configure interrupts
    TA0CTL |= TAIE;     // enable interrupt
    TA0CTL &= ~TAIFG;   // clear interrupt flag
    TA0CCTL1 |= CCIE;   // enable interrupt
    TA0CCTL1 &= ~CCIFG; // clear interrupt flag
}

double getVelocity()
{
    return error * angResPulse / TA0CCR1;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TimerA0_ISR(void)
{
    switch(__even_in_range(TA0IV, 0x0E))
    {
    case 0x02: // TA0CCR1 CCIFG
        TA0CTL |= TACLR; // reset TA0R
        error = 1;
        break;
    case 0x0E: // TA0CTL TAIFG (Timer overflow)
        error = 0; // error (too slow)
        break;
    }
}
