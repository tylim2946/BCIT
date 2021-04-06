/*************************************************************************************************
 * motionProfile.h
 * - header file for motion profiling
 *
 *  Author: Taeyoon Rim
 *  Created on: February 1st, 2021
 *  Modified: February 8th, 2021
 **************************************************************************************************/
#ifndef MOTIONPROFILE_H_
#define MOTIONPROFILE_H_

#define MOTION_PROF_ON (TA1CCTL1 |= CCIE)
#define MOTION_PROF_OFF (TA1CCTL1 &= ~CCIE)

extern unsigned int dCycle;
extern unsigned char dir;
extern unsigned char brake;

void timerA1Init(void);
char timerA1FreqSet(unsigned int freq);
int vnhProfileMove(int dir, int speed);
int vnhProfileBrake();

#endif /* MOTIONPROFILE_H_ */
