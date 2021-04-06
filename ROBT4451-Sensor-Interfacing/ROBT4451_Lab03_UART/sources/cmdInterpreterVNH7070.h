/*************************************************************************************************
 * cmdInterpreterVNH7070.h
 * - header file for interpreting vnh7070 commands
 *
 *  Author: Taeyoon Rim
 *  Created on: February 20th, 2021
 *  Modified: February 20th, 2021
 **************************************************************************************************/

#ifndef CMDINTERPRETERVNH7070_H_
#define CMDINTERPRETERVNH7070_H_

#define MAX_ARGS 2
#define MAX_CMDS 3
#define NUM_CMDS 3

typedef struct CMD
{
    const char * name; // command name
    int nArgs; // number of input arguments for a command
    int args[MAX_ARGS]; // arguments
} CMD;

void cmdInterpreterVnh7070Init(CMD * cmdList);
int parseCmd(CMD * cmdList, char * cmdLine);
int validateCmd(CMD * cmdLIist, char * cmdName);
int executeCmd(CMD * cmdList, int cmdIndex);

#endif /* CMDINTERPRETERVNH7070_H_ */
