/*************************************************************************************************
 * nok5110LCD.c
 * - C implementation or source file for NOKIA 5110 LCD.
 *
 *  Author: Greg Scutt
 *  Created on: Feb 20th, 2017
 *  Modified: Mar 7th, 2021 by Taeyoon Rim
 **************************************************************************************************/

// nok5110LCD pin connectivity --> to MSP-EXP430F5529LP EVM.
//  8-LIGHT  	-->  	no connection necessary
//  7-SCLK  	-->  	MS430EVM  P4.3 or UCB1CLK
//  6-DN(MOSI)  -->  	MS430EVM  P4.1 or UCB1SIMO
//  5-D/C'  	-->  	MS430EVM  P4.2. 	Kept as I/O pin !!
//  4-RST'  	-->  	MS430EVM  I/O pin of your choice. See 8.1, 8.2, 12.2 in Nokia Datasheet.
//  3-SCE'  	-->  	MS430EVM  P4.0.  	Kept as I/O pin !!
//  2-GND  		-->  	MS430EVM or supply VSS
//  1-VDD  		-->  	MS430EVM or supply 3V3. Consider controlling it with an I/O pin

#include <msp430.h>
#include <usciB1Spi.h>
#include <nok5110LCD.h> // remove _lab from file names
#include "math.h"
#include "stdlib.h"

#define APPLY_PWR P2OUT |= VCC
#define PULSE_RST P2OUT |= RST; P2OUT &= ~RST; P2OUT |= RST // reset strobe (if it only requires the rising edge, it does not need P2OUT |= RST; in the beginning)
#define WAIT_FOR_RXIFG while(!(UCB1IFG & UCRXIFG)); char temp = UCB1RXBUF // clear RXIFG by reading RXBUF
#define ASSERT P4OUT &= ~SCE
#define DEASSERT P4OUT |= SCE

#define PI 3.14159265359

// 2-D 84x6 array that stores the current pixelated state of the display.
// remember a byte (8 bits) sets 8 vertical pixels in a column allowing 8x6=48 rows
// note that this array is GLOBAL to this file only. In that way it is protected from access from other functions in files.
// said another way - it is a private global array with local scope to the file in which the defining declaration exists.
// we don't want other functions messing with the shadow RAM. This is the reason for static and for its dec/defn in this .c file
// static here means that it does not have inter-file scope, it is local to this file only. This is a best practice when you want to
// protect data structures from unwanted access by other functions in other files.
static unsigned char currentPixelDisplay[LCD_MAX_COL][LCD_MAX_ROW / LCD_ROW_IN_BANK];

/************************************************************************************
* Function: nokLcdInit
* - initializes nokia 5110 lcd (includes power on reset sequence). Requires an SPI init with
*   ucsiB1SpiInit from ucsiSpi.h before this function call!!
* argument:
*   none
* return: none
* Author: Greg Scutt
* Date: Feb 20th, 2017
* Modified: Mar 7th, 2021 by Taeyoon Rim
************************************************************************************/
void nokLcdInit(void)
{
    // configure ports
    P4DIR |= SCE | DAT_CMD;
    P2DIR |= VCC | RST;

    // add power-on RST sequence here.  The display is not powered until this sequence occurs.
    APPLY_PWR;
    PULSE_RST;

    // send initialization sequence to LCD module
    nokLcdWrite(LCD_EXT_INSTR, DC_CMD);
    nokLcdWrite(LCD_SET_OPVOLT, DC_CMD);
    nokLcdWrite(LCD_SET_TEMPCTRL, DC_CMD);
    nokLcdWrite(LCD_SET_SYSBIAS, DC_CMD);
    nokLcdWrite(LCD_BASIC_INSTR, DC_CMD);
    nokLcdWrite(LCD_NORMAL_DISP, DC_CMD);

    nokLcdClear(); // clear the pixel memory and hence the display.
    /* Sometimes necessary since the pixel ram is not defined after a PWR on and RST. The best practice would be to
     always clear it so no residual pixels are set. You will sometimes see random pixels set and I think it is from not clearing the memory
     which must be done manually. Try removing this function to see what happens.*/
}

/************************************************************************************
* Function: nokLcdWrite
* - performs write sequence to send data or command to nokLCD. Calls spiPutChar to transmit serially to nokLCD
* arguments: lcdByte - the 8 bit char (data or command) that is written to nokLCD.
* 			 cmdType - 0: lcdByte is a cmd, 1: lcdByte is data.
* return: none
* Author: Greg Scutt
* Date: Feb 20th, 2017
* Modified: Mar 8th, 2021 by Taeyoon Rim
************************************************************************************/
void nokLcdWrite(char lcdByte, char cmdType)
{
	// check cmdType and output correct DAT_CMD signal to PORT4 based on it. Use definitions in .h file
    if ((P4OUT & DAT_CMD) != (cmdType << 2))
    {
        P4OUT ^= DAT_CMD;
    }

	// activate the SCE  chip select
    ASSERT;

	// transmit lcdByte with spiPutChar from Lab 3.  That function must stay in the spi C module.
    usciB1SpiPutChar(lcdByte);

	// wait for SPI transmission to complete. You need to poll an SPI interrupt flag. Which one RXIFG or TXIFG? Understand why.
    WAIT_FOR_RXIFG;

    // when transmission is complete deactivate the SCE */
    DEASSERT;
}

/************************************************************************************
* Function: nokLcdSetPixel
* -
* argument:
*	xPos - The horizontal pixel location in the domain (0 to 83)
*	yPos - The vertical pixel location in the domain (0 to 47)
*
* return: 0 - pixel was valid and written.  1 - pixel not valid
* Author: Greg Scutt
* Date: Feb 20th, 2017
* Modified: <date of any mods> usually taken care of by rev control
************************************************************************************/
unsigned char  nokLcdSetPixel(unsigned char xPos, unsigned char yPos)
{
	unsigned char bank; // a bank is a group of 8 rows, selected by 8 bits in a byte

	// verify pixel position is valid
	if ((xPos < LCD_MAX_COL) && (yPos < LCD_MAX_ROW))
	{
		// if-else statement avoids costly division
		if (yPos<8) bank = 0;
		else if (yPos<16) bank = 1;
		else if (yPos<24) bank = 2;
		else if (yPos<32) bank = 3;
		else if (yPos<40) bank = 4;
		else if (yPos<48) bank = 5;

		// set the x and y RAM address  corresponding to the desired (x,bank) location. this is a command DC_CMD
		nokLcdWrite(LCD_SET_XRAM | xPos, DC_CMD);
		nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD);

		// update the pixel being set in currentPixelDisplay array
		currentPixelDisplay[xPos][bank] |= BIT0 << (yPos % LCD_ROW_IN_BANK); // i.e if yPos = 7 then BIT0 is left shifted 7 positions to be 0x80. nice mod.
		nokLcdWrite(currentPixelDisplay[xPos][bank], DC_DAT); // write the byte defining a single pixel
		return 0;
	}
	return 1;
}

/************************************************************************************
* Function: nokLcdClear
* - clears all pixels on LCD diplay. results in blank display.
* argument:
*   none
* return: none
* Author: Greg Scutt
* Date: Feb 20th, 2017
* Modified: <date of any mods> usually taken care of by rev control
************************************************************************************/
void nokLcdClear(void)
{
    unsigned char bank; // bank (group of 8 rows) on which pixel falls
    unsigned char x;    // x coordinate to track columns

    // sweep banks (or group of 8 rows)
    for (bank = 0; bank < 6; bank++) {

        // start in first column of the bank (0, bank)
        nokLcdWrite(LCD_SET_XRAM | 0, DC_CMD);
        // start in current bank
        nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD);

        // sweep columns. X address is auto-incremented by one since V = 0.
        for (x = 0; x < LCD_MAX_COL; x++) {
            currentPixelDisplay[x][bank] = 0;       // update pixel display array to keep pixel state current
            nokLcdWrite(0, DC_DAT);                 // clear all 8 pixels at (x,bank)
        }
    }
}

/************************************************************************************
* Function: nokLcdDrawScrnLine
* - draws a straight line at pos. Its orientation is determined by rot
* argument:
*   pos - x/y position of the line
*   rot - 0: horizontal, 1: vertical
* return: 0 if it was successful, -1 if it was not
* Author: Taeyoon Rim
* Date: Mar 8th, 2021
************************************************************************************/
char nokLcdDrawScrnLine(char pos, char rot)
{
    char bank, xPos;
    char result = -1;

    if (rot == H && pos < LCD_MAX_ROW)
    {
        if (pos<8) bank = 0;
        else if (pos<16) bank = 1;
        else if (pos<24) bank = 2;
        else if (pos<32) bank = 3;
        else if (pos<40) bank = 4;
        else if (pos<48) bank = 5;

        nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD);

        for (xPos = 0; xPos < LCD_MAX_COL; xPos ++)
        {
            // set the x and y RAM address
            nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD); // XRAM will automatically increment

            // update the pixel being set in currentPixelDisplay array
            currentPixelDisplay[xPos][bank] |= BIT0 << (pos % LCD_ROW_IN_BANK); // i.e if yPos = 7 then BIT0 is left shifted 7 positions to be 0x80. nice mod.
            nokLcdWrite(currentPixelDisplay[xPos][bank], DC_DAT); // write the byte defining a single pixel
        }
    }
    else if (rot == V && pos < LCD_MAX_COL)
    {
        xPos = pos;

        for (bank = 0; bank < 6; bank ++)
        {
            // set the x and y RAM address
            nokLcdWrite(LCD_SET_XRAM | xPos, DC_CMD);
            nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD);

            // update the pixel being set in currentPixelDisplay array
            currentPixelDisplay[xPos][bank] |= 0xFF;
            nokLcdWrite(currentPixelDisplay[xPos][bank], DC_DAT); // write the byte defining a single pixel
        }
        result = 0;
    }

    return result;
}

/************************************************************************************
* Function: nokLcdDrawLine
* - draws a line between the two coordinates
* argument:
*   x1, y1 - coordinate 1
*   x2, y2 - coordinate 2
* return: 0 if it was successful, -1 if it was not
* Author: Taeyoon Rim
* Date: Mar 8th, 2021
************************************************************************************/
char nokLcdDrawLine(char x1, char y1, char x2, char y2)
{
    unsigned char i;
    unsigned char bank;
    unsigned char yStartPos[LCD_MAX_COL];
    unsigned char yEndPos[LCD_MAX_COL];
    unsigned char yCurrent, yNext;

    char result = -1;

    if ((x1 < LCD_MAX_COL) && (x2 < LCD_MAX_COL) && (y1 < LCD_MAX_ROW) &&  (y2 < LCD_MAX_ROW))
    {
        calcLine(yStartPos, yEndPos, x1, y1, x2, y2);

        // draw lines
        for (i = x1; i <= x2; i ++) // note: x1 (and x2) is being modified somewhere => use subroutine (it will save the register values in stack)
        {
            yCurrent = yStartPos[i];

            // draw for each bank in i (from yPos[i] to yNext)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ word it better
            do
            {
                yNext = findNextY(yCurrent, yEndPos[i]);
                bank = bankAt(yCurrent);

                if (yCurrent >= 0 && yCurrent < LCD_MAX_ROW)
                {
                    // draw up to a bank or yNext
                    // set the x and y RAM address  corresponding to the desired (x,bank) location. this is a command DC_CMD
                    nokLcdWrite(LCD_SET_XRAM | i, DC_CMD);
                    nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD);

                    // draw pixel
                    currentPixelDisplay[i][bank] |= pos2Row(yCurrent, yNext); // update currentPixelDisplay
                    nokLcdWrite(currentPixelDisplay[i][bank], DC_DAT);
                }

                yCurrent = yNext;
            } while(yCurrent != yEndPos[i]);
        }

        result = 0;
    }

    return result;
}
/*
char nokLcdDrawLine(char x1, char y1, char x2, char y2)
{
    unsigned char i;
    unsigned char bank;
    unsigned char yPos[LCD_MAX_COL + 1];
    unsigned char yCurrent, yNext;

    char result = -1;

    if (x1 < LCD_MAX_COL && x2 < LCD_MAX_COL && y1 < LCD_MAX_ROW &&  y2 < LCD_MAX_ROW)
    {
        calcLine(yPos, x1, y1, x2, y2);

        // draw lines
        for (i = x1; i <= x2; i ++) // note: x1 (and x2) is being modified somewhere => use subroutine (it will save the register values in stack)
        //i = x1;
        //do
        {
            yCurrent = yPos[i];

            // draw for each bank in i (from yPos[i] to yNext)@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ word it better
            do
            {
                yNext = findNextY(yCurrent, yPos[i + 1]);
                bank = bankAt(yCurrent);

                if (yCurrent >= 0 && yCurrent < LCD_MAX_ROW)
                {
                    // draw up to a bank or yNext
                    // set the x and y RAM address  corresponding to the desired (x,bank) location. this is a command DC_CMD
                    nokLcdWrite(LCD_SET_XRAM | i, DC_CMD);
                    nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD);

                    // draw pixel
                    currentPixelDisplay[i][bank] |= pos2Row(yCurrent, yNext); // update currentPixelDisplay
                    nokLcdWrite(currentPixelDisplay[i][bank], DC_DAT);
                }

                yCurrent = yNext + 1; // not compatible with negative slope@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
            } while(yCurrent < yPos[i + 1]); // not compatible with negative slope@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

            //i ++;
        } //while(i < x2);

        result = 0;
    }

    return result;
}
*/

/*
char nokLcdDrawLine(char x1, char y1, char x2, char y2)
{
    unsigned char i;
    unsigned char bank, xPos;
    unsigned char yPos[LCD_MAX_COL + 1];
    signed char yCurrent;
    signed char polarity;

    char result = -1;

    if (x1 < LCD_MAX_COL && x2 < LCD_MAX_COL && y1 < LCD_MAX_ROW &&  y2 < LCD_MAX_ROW)
    {
        calcLine(yPos, x1, y1, x2, y2);

        // set polarity
        polarity = (y2 >= y1) ? 1 : -1;

        // draw lines
        for (i = x1; i < x2; i ++) // note: x1 (and x2) is being modified somewhere => use subroutine (it will save the register values in stack)
        {
            // draw for each bank in i (from yPos[i] to yNext)
            for (yCurrent = yPos[i]; polarity * yCurrent < polarity * yPos[i + 1]; yCurrent = (bank + polarity) * LCD_ROW_IN_BANK) // note: bank is not initialized
            {
                // if-else statement avoids costly division
                if (yCurrent<8) bank = 0;
                else if (yCurrent<16) bank = 1;
                else if (yCurrent<24) bank = 2;
                else if (yCurrent<32) bank = 3;
                else if (yCurrent<40) bank = 4;
                else if (yCurrent<48) bank = 5;

                if (yCurrent >= 0 && yCurrent < LCD_MAX_ROW)
                {
                    // draw up to a bank or yNext
                    // set the x and y RAM address  corresponding to the desired (x,bank) location. this is a command DC_CMD
                    nokLcdWrite(LCD_SET_XRAM | i, DC_CMD);
                    nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD);

                    // draw pixel
                    currentPixelDisplay[i][bank] |= pos2Row(yCurrent, min((bank + polarity) * LCD_ROW_IN_BANK - 1, yPos[i + 1] - 1)); // update currentPixelDisplay
                    nokLcdWrite(currentPixelDisplay[i][bank], DC_DAT);
                }
            }
        }

        result = 0;
    }

    return result;
}
*/

/*
char nokLcdDrawLine(char x1, char y1, char x2, char y2)
{
    unsigned char i, j;
    unsigned char bank, yPos;
    unsigned char xPos[LCD_MAX_ROW];
    unsigned char yNext;

    char result = -1;

    if (abs(x1) < LCD_MAX_COL && abs(x2) < LCD_MAX_COL && abs(y1) < LCD_MAX_ROW &&  abs(y2) < LCD_MAX_ROW)
    {
        for (i = y1; i < y2; i ++)
        {
            // calculate y(x)
            xPos[i] = round(((double)(x2 - x1)/(y2 - y1)) * (i - y1) + x1);
        }

        for (i = y1; i < y2; i ++)
        {
            // if-else statement avoids costly division
            if (yPos[i]<8) bank = 0;
            else if (yPos[i]<16) bank = 1;
            else if (yPos[i]<24) bank = 2;
            else if (yPos[i]<32) bank = 3;
            else if (yPos[i]<40) bank = 4;
            else if (yPos[i]<48) bank = 5;

            // connect dots if they are apart from each other
            // I have to know the next value
            if (i > 0 && abs(yPos[i] - yPos[i - 1]) > 1)
            {
                // from bottom to top
                for (j = yPos[i - 1] + 1; j < yPos[i]; j ++)
                {
                    nokLcdSetPixel(i - 1, j);
                }

                // from top to bottom
                for (j = yPos[i - 1] + 1; j > yPos[i]; j --)
                {
                    nokLcdSetPixel(i - 1, j);
                }
            }

            // draw point
            if (abs(yPos[i]) < LCD_MAX_ROW)
            {
                // set the x and y RAM address  corresponding to the desired (x,bank) location. this is a command DC_CMD
                nokLcdWrite(LCD_SET_XRAM | i, DC_CMD);
                nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD);

                // draw pixel
                currentPixelDisplay[i][bank] |= 0xFF >>> (yNext % LCD_ROW_IN_BANK); // update currentPixelDisplay
                nokLcdWrite(currentPixelDisplay[i][bank], DC_DAT);
            }

        }

        result = 0;
    }

    return result;
}
*/
/*
char nokLcdDrawLine(char x1, char y1, char x2, char y2)
{
    unsigned char i, j;
    unsigned char bank, xPos;
    unsigned char yPos[LCD_MAX_COL];

    char result = -1;

    if (abs(x1) < LCD_MAX_COL && abs(x2) < LCD_MAX_COL && abs(y1) < LCD_MAX_ROW &&  abs(y2) < LCD_MAX_ROW)
    {
        for (i = x1; i < x2; i ++)
        {
            // calculate y(x)
            yPos[i] = round(((double)(y2 - y1)/(x2 - x1)) * (i - x1) + y1);

            // if-else statement avoids costly division
            if (yPos[i]<8) bank = 0;
            else if (yPos[i]<16) bank = 1;
            else if (yPos[i]<24) bank = 2;
            else if (yPos[i]<32) bank = 3;
            else if (yPos[i]<40) bank = 4;
            else if (yPos[i]<48) bank = 5;

            // connect dots if they are apart from each other
            // I have to know the next value
            if (i > 0 && abs(yPos[i] - yPos[i - 1]) > 1)
            {
                // from bottom to top
                for (j = yPos[i - 1] + 1; j < yPos[i]; j ++)
                {
                    nokLcdSetPixel(i - 1, j);
                }

                // from top to bottom
                for (j = yPos[i - 1] + 1; j > yPos[i]; j --)
                {
                    nokLcdSetPixel(i - 1, j);
                }
            }

            // draw point
            if (abs(yPos[i]) < LCD_MAX_ROW)
            {
                // set the x and y RAM address  corresponding to the desired (x,bank) location. this is a command DC_CMD
                nokLcdWrite(LCD_SET_XRAM | i, DC_CMD);
                nokLcdWrite(LCD_SET_YRAM | bank, DC_CMD);

                // draw pixel
                currentPixelDisplay[i][bank] |= BIT0 << (yPos[i] % LCD_ROW_IN_BANK); // update currentPixelDisplay
                nokLcdWrite(currentPixelDisplay[i][bank], DC_DAT);
            }

        }

        result = 0;
    }

    return result;
}
*/
void nokLcdDrawPolar(int mag, double ang)
{
    double angRad, dxHalf, dyHalf;
    int x1, x2, y1, y2;
    int x, y, i;

    // take care of extreme angle (90*, -90*, 0*)

    // deg to rad conversion
    angRad = ang * PI / 180;

    // calculate half the span
    dxHalf = mag * acos(angRad);
    dyHalf = mag * asin(angRad);

    // calculate the points
    x1 = -dxHalf + (LCD_MAX_COL / 2);
    x2 = dxHalf + (LCD_MAX_COL / 2);
    y1 = -dyHalf + (LCD_MAX_ROW / 2);
    y2 = dyHalf + (LCD_MAX_ROW / 2);

    nokLcdSetPixel(x1, y1);
    nokLcdSetPixel(x2, y2);

    /*
    // calculate points along the line
    if (abs(x2 - x1) > abs(y2 - y1))
    {
        if (x1 > x2)
        {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }

        for (i = x1; x < x2; i ++)
        {
            y = round(((double)(y2 - y1)/(x2 - x1)) * i + y1);
            nokLcdSetPixel(x, y);
        }
    }
    else
    {
        if (y1 > y2)
        {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }

        for (i = y1; y < y2; i ++)
        {
            x = round(((double)(x2 - x1)/(y2 - y1)) * (i) + x1);
            nokLcdSetPixel(x, y);
        }
    }
    */

}

void calcLine(char * yStartPos, char * yEndPos, char x1, char y1, char x2, char y2)
{
    unsigned char i;

    if (x1 == x2) // x1 == x2; vertical
    {
        yStartPos[x1] = y1;
        yEndPos[x1] = y2;
    }
    else
    {
        if (y1 > y2) // negative slope
        {
            for (i = x1; i < x2; i ++)
            {
                yStartPos[i] = round(((double)(y2 - y1)/(x2 - x1)) * (i + 1 - x1) + y1 + 1);
                yEndPos[i] = round(((double)(y2 - y1)/(x2 - x1)) * (i - x1) + y1);
            }
        }
        else if (y1 < y2) // positive slope
        {
            for (i = x1; i < x2; i ++)
            {
                yStartPos[i] = round(((double)(y2 - y1)/(x2 - x1)) * (i - x1) + y1);
                yEndPos[i] = round(((double)(y2 - y1)/(x2 - x1)) * (i + 1 - x1) + y1) - 1;
            }
        }
        else // y1 == y2; horizontal
        {
            for (i = x1; i < x2; i ++)
            {
                yStartPos[i] = y1;
                yEndPos[i] = y1;
            }
        }
    }
}

/*
void calcLine(char * yPos, char x1, char y1, char x2, char y2)
{
    unsigned char i;

    if (x2 == x1)
    {
        for (i = x1; i <= x2; i ++)
        {
            yPos[i] = y1;
        }

        yPos[i] = y2 + 1;
    }
    else
    {
        for (i = x1; i <= x2 + 1; i ++)
        {
            yPos[i] = round(((double)(y2 - y1)/(x2 - x1)) * (i - x1) + y1);
        }
    }
}
*/

char findNextY(char currY, char nextY) // change name to yUp2?
{
    char result = -1;

    if (bankAt(currY) == bankAt(nextY))
    {
        if (currY == nextY)
        {
            result = nextY;
        }
        else
        {
            result = nextY - 1;
        }

    }
    else
    {
        if (currY < nextY) // result = start of the current bank; 7, 15, 23, 31, 39, 47
        {
            result = (bankAt(currY) + 1) * LCD_ROW_IN_BANK - 1;
        }
        else // result = end of the current bank; 0, 8, 16, 24, 32, 40
        {
            result = bankAt(currY) * LCD_ROW_IN_BANK;
        }
    }

    return result;
}

char bankAt(char y)
{
    char result = -1;

    if (y<8) result = 0;
    else if (y<16) result = 1;
    else if (y<24) result = 2;
    else if (y<32) result = 3;
    else if (y<40) result = 4;
    else if (y<48) result = 5;

    return result;
}

/*
temp = pos2Row(0, 0); // 00000001b
temp = pos2Row(1, 3); // 00001110b
temp = pos2Row(1, 1); // 00000010b
temp = pos2Row(0, 7); // 11111111b
temp = pos2Row(4, 6); // 00111000b => 00100000b
*/
// requirement: yStart <= yEnd
char pos2Row(int yStart, int yEnd)
{
    if (yStart > yEnd)
    {
        int temp = yStart;
        yStart = yEnd;
        yEnd = temp;
    }

    return (0xFF >> (LCD_ROW_IN_BANK - (yEnd % LCD_ROW_IN_BANK) - 1)) & (0xFF << ((yStart % LCD_ROW_IN_BANK)));
}

char min(char c1, char c2)
{
    return (c1 < c2) ? c1 : c2;
}

char max(char c1, char c2)
{
    return (c1 > c2) ? c1 : c2;
}
