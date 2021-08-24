/*************************************************************************************************
 * pulseCountingA0.c
 * - C implementation or source file for pulse counting method.
 *
 *  Author: Taeyoon Rim
 *  Created on: Apr 11, 2021
 *  Modified: Apr 11, 2021
 **************************************************************************************************/

// quadrature encoder pin connectivity --> to MSP-EXP430F5529LP EVM.
// 5V          -->     3.3 V
// GND         -->     GND
// A-A         -->     MS430EVM  P1.2 (TA0CCI1A)
// B-B         -->     N/A
// I-Index     -->     N/A

#include <msp430.h>
#include <pulseCountingA0.h>

#define A   BIT2        // P1.2

#define SMCLK 1.048E6
#define REV_COUNT 1150
#define PI 3.14159265359
#define DIVISOR 2
#define SAMP_TIME 100 // sampling time in ms

double velocity; // motor angular speed in rad/s
int pulseCount; // CCI1A pulse count

const double constant = PI * 2 / REV_COUNT / SAMP_TIME * 1000;

void pulseCountingA0Init()
{
    // configure ports
    P1DIR &= ~A;
    P1SEL |= A;

    // configure timer A registers
    TA0CTL |= TASSEL_2 + MC_1 + ID_1;           // SMCLK, up to TA0CCR0, input divide by 2
    TA0CCR0 = SMCLK * SAMP_TIME / 1000 / DIVISOR - 1 + 0.5;   // sampling time: 100 ms
    TA0EX0 |= TAIDEX_0;                         // divide by 1
    TA0CCTL1 |= CAP + SCS + CCIS_0 + CM_1;            // capture mode, synchronize, CCIxA, capture rising edge

    // configure interrupts
    TA0CTL |= TAIE;     // enable interrupt
    TA0CTL &= ~TAIFG;   // clear interrupt flag
    TA0CCTL1 |= CCIE;   // enable interrupt
    TA0CCTL1 &= ~CCIFG; // clear interrupt flag
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TimerA0_ISR(void)
{
    switch(__even_in_range(TA0IV, 0x0E))
    {
    case 0x02: // TA0CCR1 CCIFG
        pulseCount ++;
        break;
    case 0x0E: // TA0CTL TAIFG (sampling time elapsed)
        velocity = constant * pulseCount;
        pulseCount = 0;
        break;
    }
}
