/*************************************************************************************************
 * usciB1Spi.c
 * - C source file for MSP430 UCSI SPI B1
 *
 *  Author: Taeyoon Rim
 *  Created on: February 26th, 2021
 *  Modified: February 27th, 2021
 **************************************************************************************************/
#include <msp430.h>
#include <usciB1Spi.h>

#define MOSI_B1 BIT1 // MOSI on P4.1
#define MISO_B1 BIT2 // MISO on P4.2
#define CLK_B1  BIT3 // SCLK on P4.3

#define bSS BIT0     // bSS on P6.0

#define BUFF_SIZE 50

int i = 0;
char spiRxBuffer[50];

/************************************************************************************
* Function: usciB1SpiInit
* - configures UCB1 SPI to use SMCLK, 8 bit data, 3 pin mode, MSP first
* Arguments:
*   spiMst - 1 bit code for UCMST
*   sclkDiv - 16 bit SMCLK divisor
*   sclkMode - 2 bit codes for UCCKPH and UCCKPL respectively
*   spiLoopBack - 1 bit code for UCLISTEN
* Return: none
*
* Author: Taeyoon Rim
* Created on: February 26th, 2021
* Modified: February 27th, 2021
************************************************************************************/
void usciB1SpiInit(unsigned char spiMST, unsigned int sclkDiv, unsigned char sclkMode, unsigned char spiLoopBack)
{
	UCB1CTL1 |= UCSWRST;    // put state machine in USCI reset while you initialize it

	UCB1CTL1 |= UCSSEL_2;   // select SMCLK. User is responsible for setting this rate.
	
	// configure the control registers using the input arguments
	UCB1CTL0 = 0;                       // reset UCB1CTL0
	UCB1CTL0 &= ~UC7BIT                 // 8 bit data
	         &  ~UCMODE0 & ~UCMODE1;    // 3-pin SPI
	UCB1CTL0 |= ((UCCKPH | UCCKPL) & (sclkMode << 6))   // configure clock phase and polarity
             |  (UCMST & (spiMST << 3))                 // set master/slave
	         |  UCMSB                                   // MSB first
	         |  UCSYNC;                                 // synchronous (SPI)

	UCB1STAT |= (UCLISTEN & (spiLoopBack << 7));   // select loopback mode
	
	usciB1SpiClkDiv(sclkDiv); // set clock divisor

	// configure the SPI B1 pins with PxSEL register
	P4DIR |= (MOSI_B1 | MISO_B1 | CLK_B1);
	P4SEL |= MOSI_B1 | MISO_B1 | CLK_B1;

	UCB1CTL1 &= ~UCSWRST;   // take USCI state machine out of reset
}

/************************************************************************************
* Function: usciB1SpiClkDiv
* - configure SMCLK clock divisor
* Arguments: sclkDiv - 16 bit SMCLK divisor
* Return: none
*
* Author: Greg Scutt
* Created on: March 1st, 2017
* Modified: March 1st, 2017
************************************************************************************/
void usciB1SpiClkDiv(unsigned int sclkDiv)
{
    UCB1CTL1 |= UCSWRST;                        // you always need to put state machine into reset when configuring USC module

    UCB1BR0 = (sclkDiv&0xFF);                   // 2
    UCB1BR1 = (sclkDiv>>8);                     //

    UCB1CTL1 &= ~UCSWRST;                       // **Initialize USCI state machine**
}

/************************************************************************************
* Function: usciB1SpiPutChar
* - writes a single character to UCB1TXBUF if it is ready
* Arguments: txByte - byte to be transmitted
* Return: none
*
* Author: Taeyoon Rim
* Created on: February 27th, 2021
* Modified: February 27th, 2021
************************************************************************************/
void usciB1SpiPutChar(unsigned char txByte)
{
    while (!(UCB1IFG & UCTXIFG));
        UCB1TXBUF = txByte;  // if TXBUFF ready then transmit a byte by writing to it
}

/************************************************************************************
* Function: usciB1SpiTxBuffer
* -
* Arguments:
*   buffer -
*   buffLen -
* Return: none
*
* Author: Taeyoon Rim
* Created on: February 27th, 2021
* Modified: February 27th, 2021
************************************************************************************/
void usciB1SpiTxBuffer(const unsigned char * buffer, int buffLen)
{
    unsigned int ptr = 0;

    // convert char to int
    for(ptr = buffLen; ptr > 0; ptr --)
    {
        P6OUT &= ~bSS; // assert bSS

        usciB1SpiPutChar(buffer[ptr]);

        while (!(UCB1IFG & UCRXIFG));
        char temp = UCB1RXBUF; // clear RXIFG by reading RXBUF

        P6OUT |= bSS; // deassert bSS
    }
}


#pragma vector=USCI_B1_VECTOR
__interrupt void usciB1SpiIsr(void)
{
  // UCB1IV interrupt handler. __even_in_range will optimize the C code so efficient jumps are implemented.
  switch(__even_in_range(UCB1IV,4)) // this will clear the current highest priority flag. TXIFG or RXIFG.
  {
  	  case 0: break;    // Vector 0 - no interrupt
  	  case 2:           // Vector 2 - RXIFG. Highest priority
  		  spiRxBuffer[i++] = UCB1RXBUF;
  		  break;
  	  case 4: break;	// Vector 4 - TXIFG
  	  default:
  }
}
