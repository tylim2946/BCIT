/*************************************************************************************************
 * cmdInterpreterVnh7070.h
 * - header file for interfacing vnh7070 h-bridge motor driver
 *
 *  Author: Taeyoon Rim
 *  Created on: January 24th, 2021
 *  Modified: January 24th, 2021
 **************************************************************************************************/
#ifndef VNH7070API_H_
#define VNH7070API_H_

void vnh7070Init(void);
char vnh7070InputCtrl(unsigned char ctrl);
char vnh7070CW(unsigned char dutyCycle);
char vnh7070CCW(unsigned char dutyCycle);
char vnh7070Brake(void);

#endif /* VNH7070API_H_ */
