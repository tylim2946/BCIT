/*
 * vnh7070API.h
 *
 *  Created on: Jan. 24, 2021
 *      Author: Kevin Rim
 */

#ifndef VNH7070API_H_
#define VNH7070API_H_

void vnh7070Init(void);
char vnh7070InputCtrl(unsigned char ctrl);
char vnh7070CW(unsigned char dutyCycle);
char vnh7070CCW(unsigned char dutyCycle);
char vnh7070Brake(void);

#endif /* VNH7070API_H_ */
