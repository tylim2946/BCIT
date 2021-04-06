/*************************************************************************************************
 * main.c
 * - top level source file for UART lab4
 *
 *  Author: Taeyoon Rim
 *  Created on: February 15th, 2021
 *  Modified: February 20th, 2021
 **************************************************************************************************/
#include <cmdInterpreterVnh7070.h>
#include <msp430.h> 
#include <stdio.h>
#include <ucsiA1Uart.h>

CMD vnh7070Cmds[MAX_CMDS];
char mCmdLine[100];

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // initialize
    timerA0Init(20);
    vnh7070Init();
    timerA1Init(); // motionProfile
    ucsiA1UartInit();
    cmdInterpreterVnh7070Init(vnh7070Cmds);

    // interrupts
    __enable_interrupt();

    while (1)
    {
        ucsiA1UartGets(mCmdLine);

        if (mCmdLine != NULL)
        {
            int mIndex = parseCmd(vnh7070Cmds, mCmdLine);

            if (mIndex != -1)
                executeCmd(vnh7070Cmds, mIndex);
        }
    }

	return 0;
}
