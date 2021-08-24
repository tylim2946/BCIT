/*
 * vnh7070API.c
 *
 *  Created on: Jan. 24, 2021
 *      Author: Kevin Rim
 */

#include <msp430.h>
#include <pwmTimerA1.h>
#include <vnh7070API.h>

#define CTRL (BIT0 + BIT1 + BIT2)
#define INa BIT0
#define INb BIT1
#define SEL0 BIT2

#define PWM BIT2

unsigned char brake;

void vnh7070Init()
{
    P3DIR |= CTRL;
    vnh7070CW(0);
}

char vnh7070InputCtrl(unsigned char ctrl)
{
    // variable declaration
    unsigned char output = 0;

    if (ctrl >= 0x0 && ctrl <= 0x7 && !(~P3DIR & CTRL)) // ctrl is a char between 0x0 and 0x7, and P3<2:0> is output
    {
        P3OUT = ctrl ;
    }
    else
    {
        output = -1;
    }

    return output;
}

char vnh7070CW(unsigned char dutyCycle)
{
    // variable declaration
    unsigned char output = 0;

    if(!timerA1DutyCycleSet(dutyCycle)) // valid duty cycle
    {
        vnh7070InputCtrl(INa + 0 + 0);
    }
    else
    {
        output= -1;
    }

    return output;
}

char vnh7070CCW(unsigned char dutyCycle)
{
    // variable declaration
    unsigned char output = 0;

    if(!timerA1DutyCycleSet(dutyCycle)) // valid duty cycle
    {
        vnh7070InputCtrl(0 + INb + 0);
    }
    else
    {
        output = -1;
    }

    return output;
}

char vnh7070Brake()
{
    // variable declaration
    unsigned char output = 0;

    vnh7070InputCtrl(0 + 0 + 0);
    timerA1DutyCycleSet(10); // set pwm high

    return output;
}
