/*
 * quadEncDec.h
 *
 *  Created on: Mar 22, 2021
 *      Author: a01160214
 */

#ifndef QUADENCDEC_H_
#define QUADENCDEC_H_

#define REV_COUNT 2300 // 1150 * 2
#define PI 3.14159265359

extern unsigned int posCount;
extern unsigned char dir;       // 1 = CW; 0 = CCW

void quadEncDecInit(void);

#endif /* QUADENCDEC_H_ */
