/*************************************************************************************************
 * motionProfile.c
 * - C source file for motion profiling
 *
 *  Author: Taeyoon Rim
 *  Created on: February 1st, 2021
 *  Modified: February 8th, 2021
 **************************************************************************************************/
#include <msp430.h>
#include <motionProfile.h>
#include <pwmTimerA0.h>
#include <vnh7070API.h>

#define FREQ_MIN 16 // when TA1CCR0 is 65535
#define FREQ_MAX 116444 // when TA1CCR0 is 9

#define SMCLK_CLK 1.048E6

#define FREQ 20
#define SPEED 100 // 100 percent per seconds = 10 % per each 0.1 seconds

unsigned int dCycle;
unsigned char dir;
unsigned char brake;

unsigned int dCycleReq;
unsigned char dirReq;

double elapsed;
const double reqElapse = 10.0 / SPEED; // minimum elapse required to change 10% d.c.

/************************************************************************************
* Function: timerA1Init
* - initialize timerA1 for motion profiling
* Arguments: none
* return: none
*
* Author: Taeyoon Rim
* Date: February 1st, 2021
* Modified: February 1st, 2021
************************************************************************************/
void timerA1Init()
{
    // variable declaration
    unsigned char output;

    // configure timer A registers
    TA1CCTL1 &= ~CAP; // compare mode
    TA1CTL |= TASSEL_2 + MC_1 + ID_0; //up mode, input divider
    TA1EX0 |= TAIDEX_0; // divide by 1
    timerA1FreqSet(FREQ);
    TA1CCR1 = 1;

    // configure interrupts
    TA1CCTL1 |= CCIE; // enable interrupt (MOTION_PROF_ON)
    TA1CCTL1 &= ~CCIFG; // clear interrupt flag
    _bis_SR_register(GIE); // enable global interrupt
}

/************************************************************************************
* Function: timerA1FreqSet
* - set timerA1 frequency for motion profiling
* Arguments:
*   freq - desired frequency in integer
* return: If successful, return 0. Otherwise, return -1
*
* Author: Taeyoon Rim
* Date: February 1st, 2021
* Modified: February 1st, 2021
************************************************************************************/
char timerA1FreqSet(unsigned int freq)
{
    // variable declaration
    unsigned char output = 0;

    if (freq >= FREQ_MIN && freq <= FREQ_MAX) // if the requested pwmFreq is outside the range, then TACCR0 is not changed and -1 is returned
    {
        TA1CCR0 = 1.0 / freq * SMCLK_CLK - 1 + 0.5; // compute and set TACCR0 value
    }
    else
    {
        output = -1;
    }

    return output;
}

/************************************************************************************
* Function: loop
* - update the speed and direction of the motor to implement motion profiling
* Arguments: none
* return: none
*
* Author: Taeyoon Rim
* Date: February 1st, 2021
* Modified: February 8th, 2021
************************************************************************************/
void loop() // loop is executed every 1/FREQ seconds
{
    if (dir != dirReq && dCycle != 0) // dCycle -> 0
    {
        elapsed += 1.0 / FREQ;

        if (elapsed >= reqElapse && dCycle > 0)
        {
            elapsed -= reqElapse;
            dCycle --;
            timerA0DutyCycleSet(dCycle);
            brake = 0;
        }
    }


    if (dCycle != dirReq && dCycle == 0 && brake == 0) // brake
    {
        elapsed = 0;

        vnh7070Brake();
        dir = 0;
        brake = 1;
    }

    /*
    if (dCycle != dirReq && dirReq == 0 && brake == 0) // brake
    {
        elapsed = 0;

        vnh7070Brake();
        dir = 0;
        dCycle = 0;
        brake = 1;
    }
     */

    if (dir == 0 && dir != dirReq) // dir: 0 -> 1/-1
    {
        elapsed = 0;

        if (dirReq == 1)
        {
            vnh7070CW(0);
        }
        else
        {
            vnh7070CCW(0);
        }

        dir = dirReq;
    }

    if (dir == dirReq && dCycle != dCycleReq && dir != 0)  // dCycle -> dCycleReq
    {
        elapsed += 1.0 / FREQ;

        if (elapsed >= reqElapse)
        {
            elapsed -= reqElapse;

            if (dCycle > dCycleReq)
            {
                dCycle --;
                timerA0DutyCycleSet(dCycle);
            }
            else if (dCycle < dCycleReq)
            {
                dCycle ++;
                timerA0DutyCycleSet(dCycle);
            }

            brake = 0;
        }
    }
}

/************************************************************************************
* Function: vnhProfileMove
* - Use motion profile to change motor direction and speed
* Arguments:
*   dir - direction; 0 -> CCW, 1 -> CW
*   speed - 10% increments duty cycle; [1:9]
* return: If successful, return 0. Otherwise, return -1
*
* Author: Taeyoon Rim
* Date: February 8th, 2021
* Modified: February 8th, 2021
************************************************************************************/
int vnhProfileMove(int dir, int speed)
{
    int result = -1;

    if (dir >= 0 && dir <= 1 && speed >= 1 && speed <= 10) // validate arguments
    {
        switch(dir)
        {
        case 0: // CCW
            dirReq = -1;
            break;
        case 1: // CW
            dirReq = 1;
            break;
        }

        dCycleReq = speed;
        result = 0;
    }

    return result;
}

/************************************************************************************
* Function: vnhProfileBrake
* - Use dymanic braking and motion profile to brake the motor
* Arguments: none
* return: Return 0 (it will always be successful)
*
* Author: Taeyoon Rim
* Date: February 8th, 2021
* Modified: February 8th, 2021
************************************************************************************/
int vnhProfileBrake()
{
    dirReq = 0;
    return 0;
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void TA1_ISR(void)
{
    loop();
    TA1CCTL1 &= ~CCIFG; // clear interrupt flag
}
