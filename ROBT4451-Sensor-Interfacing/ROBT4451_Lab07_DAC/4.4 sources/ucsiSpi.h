/*
 * ucsiSpi.h
 *
 *  Created on: Feb 19, 2017
 *      Author: Greg Scutt
 */

#ifndef UCSISPI_H_
#define UCSISPI_H_


// extern allows the ucsiSpi.c to be compiled on its own.
// Let's linker know that there is a global variable rxFlag "defined" externally in the .c file.
extern unsigned char rxFlag;

void ucsiA0SpiInit(unsigned int sclkDiv);
void ucsiA0SpiClkDiv(unsigned int sclkDiv);
void ucsiB1SpiInit(unsigned int sclkDiv);
void ucsiB1SpiClkDiv(unsigned int sclkDiv);

#endif /* UCSISPI_H_ */
