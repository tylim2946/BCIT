/*
 * motionProfile.h
 *
 *  Created on: Feb 1, 2021
 *  Author: Taeyoon Rim
 */

#ifndef MOTIONPROFILE_H_
#define MOTIONPROFILE_H_

#define MOTION_PROF_ON (TA1CCTL1 |= CCIE)
#define MOTOIN_PROF_OFF (TA1CCTL1 &= ~CCIE)

extern unsigned int dCycle;
extern unsigned char dir;
extern unsigned char brake;

extern unsigned int dCycleReq;
extern unsigned char dirReq;

extern double elapsed;
extern const double reqElapse;

void timerA1Init(void);
char timerA1FreqSet(unsigned int freq);

#endif /* MOTIONPROFILE_H_ */
