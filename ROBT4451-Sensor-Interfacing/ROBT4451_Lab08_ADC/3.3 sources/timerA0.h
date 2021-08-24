/*************************************************************************************************
 * timerA0.h
 * - header file to trigger timerA0Ready every interval
 *
 *  Author: Taeyoon Rim
 *  Created on: Apr 26, 2021
 *  Modified: Apr 26, 2021
 **************************************************************************************************/

#ifndef TIMERA0_H_
#define TIMERA0_H_

void timerA0Init(int period);

extern unsigned char timerA0Ready;

#endif /* TIMERA0_H_ */
