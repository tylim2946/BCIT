/*************************************************************************************************
 * pwmTimerA0.h
 * - header file for setting pwm frequency and duty cycle
 *
 *  Author: Taeyoon Rim
 *  Created on: January 25th, 2021
 *  Modified: January 25th, 2021
 **************************************************************************************************/
#ifndef PWMTIMERA0_H_
#define PWMTIMERA0_H_

char timerA0Init(unsigned int pwnFreq);
char timerA0PwmFreqSet(unsigned int pwmFreq);
char timerA0DutyCycleSet(unsigned char dutyCycle);

#endif /* PWMTIMERA0_H_ */
