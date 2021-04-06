/*************************************************************************************************
 * cmdInterpreterVNH7070.c
 * - C implementation or source file for interpreting vnh7070 commands
 *
 *  Author: Taeyoon Rim
 *  Created on: February 20th, 2021
 *  Modified: February 20th, 2021
 **************************************************************************************************/

#include <msp430.h>
#include "cmdInterpreterVNH7070.h"
#include "pwmTimerA0.h"
#include "motionProfile.h"
#include <stdio.h>
#include <ucsiA1Uart.h>

#define CMD0 "pwmFreqSet"
#define CMD0_NARGS 1
#define CMD1 "vnhMove"
#define CMD1_NARGS 2
#define CMD2 "vnhBrake"
#define CMD2_NARGS 0

#define CMDLIST_ARGS cmdList[cmdIndex].args

void cmdInterpreterVnh7070Init(CMD * cmdList)
{
    cmdList[0].name = CMD0;
    cmdList[0].nArgs = CMD0_NARGS;
    cmdList[1].name = CMD1;
    cmdList[1].nArgs = CMD1_NARGS;
    cmdList[2].name = CMD2;
    cmdList[2].nArgs = CMD2_NARGS;
}

/************************************************************************************
* Function: parseCmd
* - verify and parse vnh7070 command line
* Arguments:
*   cmdList - initialized array of commands
*   cmdLine - command line entered by user
* return: If validation was successful, return cmdIndex. Otherwise, return -1
*
* Author: Taeyoon Rim
* Date: February 20th, 2021
* Modified: February 20th, 2021
************************************************************************************/
int parseCmd(CMD * cmdList, char * cmdLine)
{
    char * cmdToken;
    char * con;
    int cmdIndex;

    int numArgs = 0;
    int result = -1;

    // validate command name
    cmdToken = strtok(cmdLine, " ", &con);
    cmdIndex = validateCmd(cmdList, cmdToken);

    // separate arguments from command line
    if (cmdList[cmdIndex].nArgs > 0)
    {
        volatile int i;

        for (i = 0; i < cmdList[cmdIndex].nArgs; i++)
        {
            cmdToken = strtok(NULL, " ", &con);

            if (cmdToken)
            {
                numArgs ++;
                cmdList[cmdIndex].args[i] = atoi(cmdToken);
            }
        }
    }

    // check for extra arguments
    if (cmdIndex >= 0 && strtok(NULL, " ,", &con))
    {
        numArgs ++;
    }

    // validate nArgs
    if (numArgs == cmdList[cmdIndex].nArgs)
    {
        result = cmdIndex;
    }

    // if cmd is invalid, display an error message
    if (result == -1)
    {
        ucsiA1UartTxString("\n\rError!");
    }

    return result;
}

/************************************************************************************
* Function: validateCmd
* - validate vnh7070 command name
* Arguments:
*   cmdList - initialized array of commands
*   cmdName - command name
* return: If validation was successful, return the index. Otherwise, return -1
*
* Author: Greg Scutt
* Date: March 1st, 2017
* Modified: March 1st, 2017
************************************************************************************/
int validateCmd(CMD * cmdList, char * cmdName)
{
    int i = 0;
    int idx = -1;
    int invalidCmd = 1;

    while (invalidCmd && i < NUM_CMDS)
    {
        invalidCmd = strcmp(cmdName, cmdList[i++].name);
    }

    if (!invalidCmd)
        idx = i - 1;

    return idx;
}

/************************************************************************************
* Function: executeCMD
* - execute vnh7070 command
* Arguments:
*   cmdList - initialized array of commands
*   cmdIndex - command index
* return: if execution was successful, return 0. Otherwise, return -1
*
* Author: Taeyoon Rim
* Date: February 20th, 2021
* Modified: February 20th, 2021
************************************************************************************/
int executeCmd(CMD * cmdList, int cmdIndex)
{
    int result = -1;

    switch(cmdIndex)
    {
    case 0: // pwmSetFreq
        result = timerA0PwmFreqSet(CMDLIST_ARGS[0]);
        break;
    case 1: // vnhMove
        result = vnhProfileMove(CMDLIST_ARGS[0], CMDLIST_ARGS[1]);
        break;
    case 2: // vnhBrake
        result = vnhProfileBrake();
        break;
    }

    // if cmd is invalid, display an error message
    if (result)
    {
        ucsiA1UartTxString("\n\rError!");
    }

    return result;
}
