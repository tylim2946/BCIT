/*
 * pwmTimerA0.h
 *
 *  Created on: Jan. 7, 2021
 *  Author: Taeyoon Rim
 */

#ifndef PWMTIMERA0_H_
#define PWMTIMERA0_H_

char timerA0Init(unsigned int pwnFreq);
char timerA0PwmFreqSet(unsigned int pwmFreq);
char timerA0DutyCycleSet(unsigned char dutyCycle);

#endif /* PWMTIMERA0_H_ */
