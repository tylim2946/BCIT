/*************************************************************************************************
 * pwmTimerA0.c
 * - C source file for setting pwm frequency and duty cycle
 *
 *  Author: Taeyoon Rim
 *  Created on: January 25th, 2021
 *  Modified: January 25th, 2021
 **************************************************************************************************/
#include <msp430.h>
#include <pwmTimerA0.h>
#include <motionProfile.h>

#define PWM_MIN 16 // when TA0CCR0 is 65535
#define PWM_MAX 116444 // when TA0CCR0 is 9
#define DC_MIN 0
#define DC_MAX 10

#define SMCLK_CLK 1.048E6

/************************************************************************************
* Function: timerA0Init
* - initialize timerA0 pwm with given frequency
* Arguments:
*   pwmFreq - desired frequency in integer
* return: none
*
* Author: Taeyoon Rim
* Date: January 25th, 2021
* Modified: January 25th, 2021
************************************************************************************/
char timerA0Init(unsigned int pwmFreq) // 20kHz PWM Signal
{
    // variable declaration
    unsigned char output;

    // configure timer A registers
    TA0CCTL1 &= ~CAP; // compare mode
    TA0CTL |= TASSEL_2 + MC_1 + ID_0; //up mode, input divider
    TA0EX0 |= TAIDEX_0; // divide by 1
    TA0CCTL1 |= OUTMOD_7; //OUTMOD_7; // out mode
    P1DIR |= BIT2;
    P1SEL |= BIT2;
    output = timerA0PwmFreqSet(pwmFreq); // configure PWM frequency
    timerA0DutyCycleSet(0);

    // return the result of timerA0PwmFreqSet
    return output;
}

/************************************************************************************
* Function: timerA0PwmFreqSet
* - set timerA0 frequency for pwm
* Arguments:
*   pwmFreq - desired frequency in integer
* return: If successful, return 0. Otherwise, return -1
*
* Author: Taeyoon Rim
* Date: January 25th, 2021
* Modified: January 25th, 2021
************************************************************************************/
char timerA0PwmFreqSet(unsigned int pwmFreq)
{
    // variable declaration
    unsigned char output = 0;

    if (pwmFreq >= PWM_MIN && pwmFreq <= PWM_MAX) // if the requested pwmFreq is outside the range, then TACCR0 is not changed and -1 is returned
    {
        TA0CCR0 = 1.0 / pwmFreq * SMCLK_CLK - 1 + 0.5; // compute and set TACCR0 value
        timerA0DutyCycleSet(dCycle);
    }
    else
    {
        output = -1;
    }

    return output;
}

/************************************************************************************
* Function: timerA0DutyCycleSet
* - set timerA0 duty cycle for pwm
* Arguments:
*   dutyCycle - desired duty cycle; [0:10]
* return: If successful, return 0. Otherwise, return -1
*
* Author: Taeyoon Rim
* Date: January 25th, 2021
* Modified: January 25th, 2021
************************************************************************************/
char timerA0DutyCycleSet(unsigned char dutyCycle)
{
    // variable declaration
    unsigned char output = 0;

    if(dutyCycle >= DC_MIN && dutyCycle <= DC_MAX)// dutyCycle is an integer between 0 to 10
    {
        TA0CCR1 = (1.0 + TA0CCR0) * dutyCycle / 10; // compute and set TA0CCR1
    }
    else
    {
        output = -1;
    }

    return output;
}
