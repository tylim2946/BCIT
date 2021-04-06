/*****************************************************************
 * Course: ROBT4451
 *
 * Lab 2. pioInt
 *
 * Purpose:
 *   - to interface modules with MSP430
 *
 * Author: Taeyoon Rim
 * Group: M1
 *
 * Declaration: I, Taeyoon Rim, declare that the following program was written by me.
 *
 * Date Created: Jan 11, 2021
 * Data Modified: Jan 18, 2021
 *****************************************************************/

#include <msp430.h>
#include "pioInt.h"

#define DATA_OUT P3OUT
#define DATA_IN P3IN
#define DATA 0xFF

#define ADDR_OUT P6OUT
#define ADDR (BIT2 + BIT1 + BIT0)

#define R BIT2
#define NE BIT0
#define gIO BIT1
#define BIT_ALL 0xFF;

#define SET_ADDR (ADDR_OUT = addr)
#define SET_R (P1OUT |= R)
#define CLEAR_R (P1OUT &= ~R)
#define SET_DATA P3DIR |= DATA; DATA_OUT = data;
#define FETCH_DATA P3DIR &= ~DATA; *data = DATA_IN;
#define STROBE_NE CLEAR_NE; SET_NE;
#define CLEAR_NE (P2OUT &= ~NE)
#define SET_NE (P2OUT |= NE)

unsigned char write = 0;

// initialize pioInt interface.
void pioIntInit()
{
    // [P6<2:0>]
    P6DIR |= ADDR; // out

    // [P1.2] configure R/~W
    P1DIR |= R;

    // [P2.0] configure ~E
    P2DIR |= NE;

    // [P2.2] configure gIO
    P2DIR &= ~gIO;
    P2REN |= gIO;
    P2OUT &= ~gIO;

    // configure interrupts
    P2IES &= ~gIO;
    P2IFG &= ~BIT_ALL;
    P2IE |= gIO;
    _bis_SR_register(GIE); // enable global interrupt
}

// write data to addr on pioInt adhering to functional timing
char pioIntWrite(unsigned char addr, unsigned char data)
{
    SET_ADDR;
    CLEAR_R;
    SET_DATA;
    STROBE_NE;
    return 0;
}

// read a byte from addr and store it where data points to
// adhering to functional timing
char pioIntRead(unsigned char addr, unsigned char *data)
{
    volatile unsigned char test;
    SET_ADDR;
    SET_R;
    CLEAR_NE;
    FETCH_DATA;
    SET_NE;
    return 0;
}

char pioIntWriteTest(unsigned char iteration, unsigned char pattern)
{
    // variable declaration
    volatile unsigned int i;
    volatile unsigned char j;

    if (pattern == 0x00)
    {
        j = 0x1;
        pioIntWrite2AllAddr(j);

        if (iteration == 0)
        {
            while(1)
            {
                j = j << 1;

                if (j % BIT8 == 0)
                {
                    j = 0x01;
                }

                pioIntWrite2AllAddr(j);
            }
        }
        else
        {
            for (i = 1; i < iteration - 1; i ++)
            {
                j = j << 1;

                if (j % BIT8 == 0)
                {
                    j = 0x01;
                }

                pioIntWrite2AllAddr(j);
            }
        }
    }
    else
    {
        if (iteration == 0)
        {
            while(1)
            {
                pioIntWrite2AllAddr(pattern);
            }
        }
        else
        {
            for (i = 0; i < iteration - 1; i ++)
            {
                pioIntWrite2AllAddr(pattern);
            }
        }
    }
}

char pioIntWrite2AllAddr(unsigned char data)
{
    // variable declaration
    volatile unsigned int i;

    for (i = 0; i < 8; i ++)
    {
        pioIntWrite(i, data);
    }
}

#pragma vector = PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
    if (write)
    {
        pioIntWrite(BIT0 + BIT1, 0xAA);
        write = 0;
    }
    else
    {
        pioIntRead(BIT1 + BIT2, 0x05);
        write = 1;
    }
}
