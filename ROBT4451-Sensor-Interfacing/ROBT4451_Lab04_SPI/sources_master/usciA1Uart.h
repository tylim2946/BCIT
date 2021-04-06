/*************************************************************************************************
 * usciA1Uart.h
 * - header file for MSP430 UCSI UART A1
 *
 *  Author: Taeyoon Rim
 *  Created on: February 20th, 2021
 *  Modified: February 20th, 2021
 **************************************************************************************************/
#ifndef USCIA1UART_H_
#define USCIA1UART_H_

#define BUFF_SIZE 100

void usciA1UartInit();
void usciA1UartTxChar(unsigned char txChar);
int usciA1UartTxString(unsigned char * txChar);
int usciA1UartTxBuffer(char * buffer, int bufLen);
char * usciA1UartGets(char * rxString);

#endif /* USCIA1UART_H_ */
