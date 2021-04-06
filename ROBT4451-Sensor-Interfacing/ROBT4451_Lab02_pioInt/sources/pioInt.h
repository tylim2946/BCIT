/*
 * pioint.h
 *
 * Created on: Jan 11, 2021
 * Author: Taeyoon Rim
 */

#ifndef PIOINT_H_
#define PIOINT_H_

#define DATA_OUT P3OUT
#define DATA_IN P3IN

void pioIntInit();
char pioIntWrite(unsigned char addr, unsigned char data);
char pioIntRead(unsigned char addr, unsigned char *data);
char pioIntWriteTest(unsigned char iteration, unsigned char pattern);

#endif /* PIOINT_H_ */
