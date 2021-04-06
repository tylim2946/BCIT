/*****************************************************************
 * Course: ROBT4451
 *
 * Lab 1. PWM
 *
 * Purpose:
 *   - to set up a timer and PWM with specified period and duty cycle
 *
 * Author: Taeyoon Rim
 * Group: M1
 *
 * Declaration: I, Taeyoon Rim, declare that the following program was written by me.
 *
 * Date Created: Jan 4, 2021
 * Data Modified: Jan 7, 2021
 *
 * Used pins:
 *   - (P1.2) PWM output
 *****************************************************************/

#include <msp430.h>
#include <pwmTest.h>

void timerA0Init() // 20kHz PWM Signal
{
    // configure timer A registers
    TA0CCTL1 &= ~CAP; // compare mode
    TA0CTL |= TASSEL_2 + MC_1 + ID_0; //up mode, input divider
    TA0EX0 |= TAIDEX_4; // divide by 5
    TA0CCTL1 |= OUTMOD_7; //OUTMOD_7; // out mode
    P1DIR |= BIT2;
    P1SEL |= BIT2;
    TA0CCR0 = 9; // configure PWM frequency
    TA0CCR1 = 0; // configure duty cycle (10% increments)
}
