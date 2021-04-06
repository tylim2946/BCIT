/*************************************************************************************************
 * nok5110LCD.h
 * - C interface file for NOKIA 5110 LCD.
 *
 *  Author: Greg Scutt
 *  Created on: Feb 20th, 2017
 **************************************************************************************************/

// nok5110LCD pin connectivity --> to MSP-EXP430F5529LP EVM.
// Assumes UCB1SI  is used.
//  8-LIGHT  	-->  	no connection necassary unless you want it on
//  7-SCLK  	-->  	MS430EVM  P4.3 or UCB1CLK
//  6-DN(MOSI)  -->  	MS430EVM  P4.1 or UCB1SIMO
//  5-D/C'  	-->  	MS430EVM  P4.2. 	Kept as I/O pin !!
//  4-RST'  	-->  	MS430EVM or supply VSS.  Can tie to I/O pin if user wants. data sheet says RESET is necassary .. but?
//  3-SCE'  	-->  	MS430EVM  P4.0. chip select 	Kept as I/O pin !!
//  2-GND  		-->  	MS430EVM or supply VSS
//  1-VCC  		-->  	MS430EVM or supply 3V3

#ifndef nok5110LCD_H_
#define nok5110LCD_H_

// nok5110 pin --> msp430 PORT4 bit position
#define SCLK  	BIT3
#define DAT_CMD BIT2
#define SIMO 	BIT1
#define	SCE   	BIT0

// nok5110 pin (VCC and RST) --> msp430 PORT2 bit position
#define VCC     BIT3
#define RST     BIT4

// constants for cmdType argument passed to the nokLcdWrite function
#define DC_CMD  0	// command control
#define DC_DAT  1	// data control

// NOKIA 5110 LCD row,col MAX
#define LCD_MAX_COL 84  	// 	max # of columns.  84 pixels in x direction
#define LCD_MAX_ROW 48     	// 	max # of row.  48 pixels in y direction

// NOKIA 5110 LCD controller instructions for initialization
#define LCD_NORMAL_DISP      	0x0C // normal display control
#define LCD_EXT_INSTR 			0x21 // enable extended instruction set
#define LCD_BASIC_INSTR      	0x20 // enable basic instruction set
#define LCD_SET_SYSBIAS       	0x13 // set system bias mode
#define LCD_SET_OPVOLT     		0xBC // set operation voltage for contrast ctrl
#define LCD_SET_TEMPCTRL       	0x04 // set coeff 2
#define LCD_SET_YRAM          	0x40 // set Y address of RAM
#define LCD_SET_XRAM          	0x80 // set X address of RAM

#define LCD_ROW_IN_BANK 8 	    // 8 rows in a bank. 6 banks, so  8x6 = 48 rows of pixels. y coordinate

#define H 0
#define V 1

void nokLcdInit(void);
unsigned char nokLcdSetPixel(unsigned char xPix, unsigned char yPix);
void nokLcdWrite(char lcdByte, char cmdType);
void nokLcdClear(void);
char nokLcdDrawScrnLine(char pos, char rot);

#endif /* nok5110LCD_H_ */
