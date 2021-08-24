/*****************************************************************
 * Course: ROBT4451
 *
 * Lab 3. Speed Control of DC Motor
 *
 * Purpose:
 *   - to interface motor driver with MSP430
 *   - to drive and control the speed of the motor
 *
 * Author: Taeyoon Rim (Kevin)
 * Group: M1
 *
 * Declaration: I, Taeyoon Rim, declare that the following program was written by me.
 *
 * Date Created: Jan 25, 2021
 * Data Modified: Apr 11, 2021
 *****************************************************************/

#include <msp430.h>
#include <pwmTimerA1.h>
#include <vnh7070API.h>

#define PWM_MIN 16 // when TA0CCR0 is 65535
#define PWM_MAX 116444 // when TA0CCR0 is 9
#define DC_MIN 0
#define DC_MAX 10

#define SMCLK_CLK 1.048E6

char timerA1Init(unsigned int pwmFreq) // 20kHz PWM Signal
{
    // variable declaration
    unsigned char output;

    // configure timer A registers
    TA1CCTL1 &= ~CAP; // compare mode
    TA1CTL |= TASSEL_2 + MC_1 + ID_0; //up mode, input divider
    TA1EX0 |= TAIDEX_0; // divide by 1
    TA1CCTL1 |= OUTMOD_7; //OUTMOD_7; // out mode
    P2DIR |= BIT0; // P2.0
    P2SEL |= BIT0;
    output = timerA1PwmFreqSet(pwmFreq); // configure PWM frequency
    timerA1DutyCycleSet(0);

    // return the result of timerA0PwmFreqSet
    return output;
}

char timerA1PwmFreqSet(unsigned int pwmFreq)
{
    // variable declaration
    unsigned char output = 0;

    if (pwmFreq >= PWM_MIN && pwmFreq <= PWM_MAX) // if the requested pwmFreq is outside the range, then TACCR0 is not changed and -1 is returned
    {
        TA1CCR0 = 1.0 / pwmFreq * SMCLK_CLK - 1 + 0.5; // compute and set TACCR0 value
    }
    else
    {
        output = -1;
    }

    return output;
}

char timerA1DutyCycleSet(unsigned char dutyCycle)
{
    // variable declaration
    unsigned char output = 0;

    if(dutyCycle >= DC_MIN && dutyCycle <= DC_MAX)// dutyCycle is an integer between 0 to 10
    {
        TA1CCR1 = (1.0 + TA1CCR0) * dutyCycle / 10; // compute and set TA0CCR1
    }
    else
    {
        output = -1;
    }

    return output;
}
