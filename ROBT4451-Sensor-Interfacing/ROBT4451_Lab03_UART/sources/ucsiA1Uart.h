/*************************************************************************************************
 * ucsiA1Uart.h
 * - header file for MSP430 UCSI UART A1
 *
 *  Author: Taeyoon Rim
 *  Created on: February 20th, 2021
 *  Modified: February 20th, 2021
 **************************************************************************************************/
#ifndef UCSIA1UART_H_
#define UCSIA1UART_H_

#define BUFF_SIZE 100

void ucsiA1UartInit();
void ucsiA1UartTxChar(unsigned char txChar);
int ucsiA1UartTxString(unsigned char * txChar);
int ucsiA1UartTxBuffer(char * buffer, int bufLen);
char * ucsiA1UartGets(char * rxString);

#endif /* UCSIA1UART_H_ */
