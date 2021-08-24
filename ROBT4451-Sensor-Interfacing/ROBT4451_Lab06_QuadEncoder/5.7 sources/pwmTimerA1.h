/*
 * pwmTimerA1.h
 *
 *  Created on: Jan. 7, 2021
 *      Author: Kevin Rim
 */

#ifndef PWMTIMERA1_H_
#define PWMTIMERA1_H_

char timerA1Init(unsigned int pwnFreq);
char timerA1PwmFreqSet(unsigned int pwmFreq);
char timerA1DutyCycleSet(unsigned char dutyCycle);
void timerA1VoltageSet(double voltage);

#endif /* PWMTIMERA1_H_ */
