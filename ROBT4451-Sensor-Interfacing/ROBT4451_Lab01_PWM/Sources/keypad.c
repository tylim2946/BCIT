/*****************************************************************
 * Course: ROBT3356
 *
 * Lab 8. Interfacing a 4x4 Keypad
 *
 * Purpose:
 *   - to interface a 4x4 matrix keypad to MSP430F5529 EVM.
 *   - to develop a program to detect and record key presses.
 *
 * Author(s): Taeyoon Rim
 * Set: ROBT 3B
 * Group: T2
 *
 * Declaration: I, Taeyoon Rim, declare that the following program was written by me.
 *
 * Date Created: Nov 5, 2020
 * Data Modified: Nov 25, 2020
 *
 * Used pins:
 *   - (P6.<6:4>) keypad columns
 *   - (P2.<3:0>) keypad rows
 *****************************************************************/
#include <msp430.h>
#include <keypad.h>

#define COL P6OUT
#define ROW P2IN

#define ROW_MEMBER (BIT4 + BIT5 + BIT6 + BIT7)
#define COL_MEMBER (BIT0 + BIT1 + BIT2)

#define BIT_ALL 0xFF

#define ROW1 0
#define ROW2 1
#define ROW3 2
#define ROW4 3

#define DEBOUNCE_DELAY _delay_cycles(5000)
#define DELAY_250MS _delay_cycles((long int) 250000)

unsigned char pbState[4];

/*****************************************************************
 * Function: keypadInit
 *
 * Purpose:
 *   - set up I/O ports that are connected to keypad and LED array. You must refer to ROW, COL and LED_ARRAY only.
 *   - initialize keypad structure members.
 *
 * Arguments:
 *   - keypad (KEYPAD_4X4): keypad ADT
 *****************************************************************/
void keypadInit(KEYPAD_4X4 *keypad)
{
    // variable declaration
    volatile unsigned int i;

    // configure interrupts
    P2IES &= ~ROW_MEMBER;
    P2IFG &= ~BIT_ALL;
    P2IE |= ROW_MEMBER;
    _bis_SR_register(GIE); // enable global interrupt

    // configure rows
    P2DIR &= ~ROW_MEMBER;
    P2REN |= ROW_MEMBER;
    P2OUT &= ~ROW_MEMBER;

    // configure columns
    P6DIR |= COL_MEMBER;
    COL |= COL_MEMBER;

    // initialize keypad structure members
    keypad->currentKeyCoord = 0;
    keypad->keyPressCnt = 0;
    keypad->currentKey = '\0';

    for (i = 0; i < KEY_BUFF_SZ; i++)
    {
        keypad->keyBuffer[i] = '\0';
    }
}

/*****************************************************************
 * Function: getKeypress
 *
 * Purpose:
 *   - detect a key press and updates keypad ADT (currentKeyCoord, keyPressCnt, keyBuffer).
 *
 * Arguments:
 *   - keypad (KEYPAD_4X4): keypad ADT
 *
 * Returns:
 *   - returns 0 if a key was pressed and -1 if not.
 *****************************************************************/
unsigned char getKeypress(KEYPAD_4X4 *keypad)
{
    // variable declaration
    volatile unsigned int i, j, k;
    volatile signed char result = -1;

    for (i = 0; i < 4; i ++)
    {
        if (pbState[i])
        {
            COL |= BIT0;

            // shifts a single bit through COL to test for a pressed key
            for (j = 0; j < 3; j ++)
            {
                COL &= COL_MEMBER;

                if (ROW & ROW_MEMBER)
                {
                    DEBOUNCE_DELAY;

                    // update keypad
                    keypad->currentKeyCoord = ((ROW & ROW_MEMBER) | COL);
                    keypad->keyPressCnt ++;

                    for (k = KEY_BUFF_SZ - 1; k > 0 ; k --)
                    {
                        keypad->keyBuffer[k] = keypad->keyBuffer[k - 1];
                    }

                    keypad->keyBuffer[0] = keypad->currentKeyCoord;

                    result = 0;

                    // key release
                    while((keypad->currentKeyCoord & ROW_MEMBER) & (ROW & ROW_MEMBER)) {}
                    DEBOUNCE_DELAY;

                    // re-enable interrupts
                    P2IFG &= ~ROW_MEMBER;
                    P2IE |= ROW_MEMBER;

                    j = 3; // exit loop
                }

                COL <<= 1; // shift COL
            }
        }
    }
    return result;
}

/*****************************************************************
 * Function: decodeKeypress
 *
 * Purpose:
 *   - decodes currentKeyCoord to currentKey and updates keypad ADT.
 *
 * Arguments:
 *   - keypad (KEYPAD_4X4): keypad ADT
 *
 * Returns:
 *   - returns 0 if decoding was successful (valid currentKeyCoord) and -1 if not.
 *****************************************************************/
unsigned char decodeKeyCoord(KEYPAD_4X4 *keypad)
{
    // variable declaration
    volatile signed char result = 0;

    // decode currentKeyCoord
    switch (keypad->currentKeyCoord)
    {
    case KEYCODE_1:
        keypad->currentKey = 1;
        break;
    case KEYCODE_2:
        keypad->currentKey = 2;
        break;
    case KEYCODE_3:
        keypad->currentKey = 3;
        break;
    case KEYCODE_4:
        keypad->currentKey = 4;
        break;
    case KEYCODE_5:
        keypad->currentKey = 5;
        break;
    case KEYCODE_6:
        keypad->currentKey = 6;
        break;
    case KEYCODE_7:
        keypad->currentKey = 7;
        break;
    case KEYCODE_8:
        keypad->currentKey = 8;
        break;
    case KEYCODE_9:
        keypad->currentKey = 9;
        break;
    case KEYCODE_ASTERISK:
        keypad->currentKey = '*';
        break;
    case KEYCODE_0:
        keypad->currentKey = 0;
        break;
    case KEYCODE_POUND:
        keypad->currentKey = '#';
        break;
    default:
        result = -1;
    }

    return result;
}

#pragma vector = PORT2_VECTOR
__interrupt void Port2_ISR(void)
{
    switch(_even_in_range(P2IV, 16))
    {
    case 0xA: // p2.4
        pbState[ROW1] ++;
        break;
    case 0xC: //p2.5
        pbState[ROW2] ++;
        break;
    case 0xE: //p2.6
        pbState[ROW3] ++;
        break;
    case 0x10: //p2.7
        pbState[ROW4] ++;
        break;
    }

    P2IE &= ~COL_MEMBER;
}
