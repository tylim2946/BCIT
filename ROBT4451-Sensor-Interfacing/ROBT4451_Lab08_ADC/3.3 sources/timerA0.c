/*************************************************************************************************
 * timerA0.c
 * - C implementation or source file to trigger timerA0Ready every interval
 *
 *  Author: Taeyoon Rim
 *  Created on: Apr 26, 2021
 *  Modified: Apr 11, 2021
 **************************************************************************************************/
#include <msp430.h>
#include <timerA0.h>

#define SMCLK 1.048E6

const double ccr0Const = SMCLK / 1000;

unsigned char timerA0Ready; // timer done bit

/************************************************************************************
* Function: timerA0Init
* - writes bufLen characters from buffer
* Arguments:
*   period - trigger interval for timerA0Ready in milliseconds
* return: none
*
* Author: Taeyoon Rim
* Date: Apr 26, 2021
* Modified: Apr 26, 2021
************************************************************************************/
void timerA0Init(int period)
{
    // configure timer A registers
    TA0CTL |= TASSEL_2 + MC_1 + ID_0;       // SMCLK, up to TA0CCR0, input divide by 1
    TA0EX0 |= TAIDEX_0;                     // divide by 1
    TA0CCR0 = ccr0Const * period - 1 + 0.5; // calculate TA0CCR0 for required period

    // configure interrupts
    TA0CTL |= TAIE;     // enable interrupt
    TA0CTL &= ~TAIFG;   // clear interrupt flag
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TimerA0_ISR(void)
{
    switch(__even_in_range(TA0IV, 0x0E))
    {
    case 0x0E: // TA0CTL TAIFG (period elapsed)
        timerA0Ready = 1;
        break;
    }
}
