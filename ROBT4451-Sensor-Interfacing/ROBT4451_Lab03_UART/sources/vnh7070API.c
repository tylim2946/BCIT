/*************************************************************************************************
 * vnh7070API.c
 * - C source file for interfacing vnh7070 h-bridge motor driver
 *
 *  Author: Taeyoon Rim
 *  Created on: January 24th, 2021
 *  Modified: January 24th, 2021
 **************************************************************************************************/
#include <msp430.h>
#include <pwmTimerA0.h>
#include <vnh7070API.h>

#define CTRL (BIT0 + BIT1 + BIT2)
#define INa BIT0
#define INb BIT1
#define SEL0 BIT2
#define PWM BIT2

unsigned char brake;

/************************************************************************************
* Function: vnh7070Init
* - initialize vnh7070
* Arguments: none
* return: none
*
* Author: Taeyoon Rim
* Date: January 24th, 2021
* Modified: January 24th, 2021
************************************************************************************/
void vnh7070Init()
{
    P3DIR |= CTRL;
    vnh7070CW(0);
}

/************************************************************************************
* Function: vnh7070InputCtrl
* - configure vnh7070 using control bits
* Arguments:
*   ctrl - control bits for INa, INb, SEL0
* return: If successful, return 0. Otherwise, return -1
*
* Author: Taeyoon Rim
* Date: January 24th, 2021
* Modified: January 24th, 2021
************************************************************************************/
char vnh7070InputCtrl(unsigned char ctrl)
{
    unsigned char result = 0;

    if (ctrl >= 0x0 && ctrl <= 0x7 && !(~P3DIR & CTRL)) // ctrl is a char between 0x0 and 0x7, and P3<2:0> is output
    {
        P3OUT = ctrl ;
    }
    else
    {
        result = -1;
    }

    return result;
}

/************************************************************************************
* Function: vnh7070CW
* - configure vnh7070 to drive in clockwise direction
* Arguments:
*   dutyCycle - dutyCycle of pwm
* return: If successful, return 0. Otherwise, return -1
*
* Author: Taeyoon Rim
* Date: January 24th, 2021
* Modified: January 24th, 2021
************************************************************************************/
char vnh7070CW(unsigned char dutyCycle)
{
    unsigned char result = 0;

    if(!timerA0DutyCycleSet(dutyCycle)) // valid duty cycle
    {
        vnh7070InputCtrl(INa + 0 + 0);
    }
    else
    {
        result= -1;
    }

    return result;
}

/************************************************************************************
* Function: vnh7070CCW
* - configure vnh7070 to drive in counter-clockwise direction
* Arguments:
*   dutyCycle - dutyCycle of pwm
* return: If successful, return 0. Otherwise, return -1
*
* Author: Taeyoon Rim
* Date: January 24th, 2021
* Modified: January 24th, 2021
************************************************************************************/
char vnh7070CCW(unsigned char dutyCycle)
{
    unsigned char result = 0;

    if(!timerA0DutyCycleSet(dutyCycle)) // valid duty cycle
    {
        vnh7070InputCtrl(0 + INb + 0);
    }
    else
    {
        result = -1;
    }

    return result;
}

/************************************************************************************
* Function: vnh7070Brake
* - configure vnh7070 for dynamic braking
* Arguments: none
* return: Return 0 (it will always be successful)
*
* Author: Taeyoon Rim
* Date: January 24th, 2021
* Modified: January 24th, 2021
************************************************************************************/
char vnh7070Brake()
{
    unsigned char result = 0;

    vnh7070InputCtrl(0 + 0 + 0);
    timerA0DutyCycleSet(10); // set pwm high

    return result;
}
