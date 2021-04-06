/*************************************************************************************************
 * usciB1Spi.h
 * - header file for MSP430 UCSI SPI B1
 *
 *  Author: Taeyoon Rim
 *  Created on: February 26th, 2021
 *  Modified: February 26th, 2021
 **************************************************************************************************/
#ifndef UCSIB1SPI_H_
#define UCSIB1SPI_H_

#define MST 1   // configure usciB1 as master
#define SLV 0   // configure usciB1 as slave

#define MODE_DEFAULT BIT1   //  capture data on rising edge, clock inactive low

#define LOOPBACK BIT0   // UCLISTEN

void usciB1SpiInit(unsigned char spiMST, unsigned int sclkDiv, unsigned char sclkMode, unsigned char spiLoopBack);
void usciB1SpiClkDiv(unsigned int sclkDiv);
void usciB1SpiPutChar(unsigned char txByte);
void usciB1SpiTxBuffer(const unsigned char * buffer, int buffLen);

#endif /* UCSIB1SPI_H_ */
