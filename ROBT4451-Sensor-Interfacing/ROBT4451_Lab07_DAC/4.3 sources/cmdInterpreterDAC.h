/*************************************************************************************************
 * cmdInterpreterDAC.h
 * - header file for interpreting DAC commands
 *
 *  Author: Taeyoon Rim
 *  Created on: February 20th, 2021
 *  Modified: April 12, 2021
 **************************************************************************************************/

#ifndef CMDINTERPRETERDAC_H_
#define CMDINTERPRETERDAC_H_

#define MAX_ARGS 1
#define MAX_CMDS 1
#define NUM_CMDS 1

typedef struct CMD
{
    const char * name; // command name
    int nArgs; // number of input arguments for a command
    double args[MAX_ARGS]; // arguments
} CMD;

void cmdInterpreterVnh7070Init(CMD * cmdList);
int parseCmd(CMD * cmdList, char * cmdLine);
int validateCmd(CMD * cmdLIist, char * cmdName);
int executeCmd(CMD * cmdList, int cmdIndex);

#endif /* CMDINTERPRETERDAC_H_ */
