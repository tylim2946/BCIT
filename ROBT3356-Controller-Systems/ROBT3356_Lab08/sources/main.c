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
 * Data Modified: Nov 5, 2020
 *****************************************************************/
#include <msp430.h> 

#define ROW P2IN
#define COL P6OUT
#define LED_ARRAY P3OUT

#define ROW_MEMBER (BIT7 + BIT6 + BIT5 + BIT4)
#define COL_MEMBER (BIT3 + BIT2 + BIT1 + BIT0)
#define ARRAY_MEMBER 0xFF

#define KEY_BUFF_SZ 20

#define KEYCODE_1 0x11 // ROW, COL = 1, 1
#define KEYCODE_2 0x12 // ROW, COL = 1, 2
#define KEYCODE_3 0x13 // ROW, COL = 1, 3

#define KEYCODE_4 0x21 // ROW, COL = 2, 1
#define KEYCODE_5 0x22 // ROW, COL = 2, 2
#define KEYCODE_6 0x23 // ROW, COL = 2, 3

#define KEYCODE_7 0x31 // ROW, COL = 3, 1
#define KEYCODE_8 0x32 // ROW, COL = 3, 2
#define KEYCODE_9 0x33 // ROW, COL = 3, 3

#define KEYCODE_ASTERISK 0x41 // ROW, COL = 4, 1
#define KEYCODE_0 0x42 // ROW, COL = 4, 2
#define KEYCODE_POUND 0x43 // ROW, COL = 4, 3

typedef struct KEYPAD_4X4
{
    unsigned char currentKeyCoord; // the row, column coordinate of the pressed key
    unsigned char keyPressCnt; // tracks the number of key pressed
    unsigned char keyBuffer[KEY_BUFF_SZ]; // history of key presses
    unsigned char currentKey; // decoded currentKeyboard that maps to the real keypad. i.e. '0', '1', '2', '3', ..., '9', 'A', 'B', 'C', 'D', '#', '*'.
} KEYPAD_4X4;

void keypadInit(KEYPAD_4X4 * keypad);
signed char getKeypress(KEYPAD_4X4 * keypad);
signed char decodeKeyCoord(KEYPAD_4X4 * keypad);
void updateLedArray(KEYPAD_4X4 * keypad);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    struct KEYPAD_4X4 * myKeypad;

    keypadInit(&myKeypad);

    while (1)
    {
        if (!getKeypress(&myKeypad))
        {
            decodeKeyCoord(&myKeypad);
            updateLedArray(&myKeypad);
        }
    }

    return 0;
}

/*****************************************************************
 * Function: keypadInit
 *
 * Purpose:
 *   - set up I/O ports that are connected to keypad and LED array. You must refer to ROW, COL and LED_ARRAY only.
 *   - initialize keypad structure members.
 *
 * Arguments:
 *   - keypad (KEYPAD_4X4): keypad ADT
 *
 *****************************************************************/
void keypadInit(KEYPAD_4X4 *keypad)
{
    // variable declaration
    volatile unsigned int i;

    // configure ROW
    P2DIR &= ~ROW_MEMBER;
    P2REN |= ROW_MEMBER;
    P2OUT &= ~ROW_MEMBER; // pull-down resistor

    // configure and initialize COL
    P6DIR |= COL_MEMBER;
    COL &= ~COL_MEMBER;

    // configure and initialize LED_ARRAY
    P3DIR |= ARRAY_MEMBER;
    LED_ARRAY &= ~ARRAY_MEMBER;

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
 *
 *****************************************************************/
signed char getKeypress(KEYPAD_4X4 *keypad)
{
    // variable declaration
    volatile signed char result = -1;

    // shifts a single bit through COL to test for a pressed key)
        // get COL from currentKeyCoord
        // shift COL
        // assign shifted COL to currentKeyCoord



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
 *
 *****************************************************************/
signed char decodeKeyCoord(KEYPAD_4X4 *keypad)
{
    // variable declaration
    volatile signed char result = 0;

    // decode currentKeyCoord
    switch (keypad->currentKeyCoord)
    {
    case KEYCODE_1:
        keypad->currentKey = '1';
        break;
    case KEYCODE_2:
        keypad->currentKey = '2';
        break;
    case KEYCODE_3:
        keypad->currentKey = '3';
        break;
    case KEYCODE_4:
        keypad->currentKey = '4';
        break;
    case KEYCODE_5:
        keypad->currentKey = '5';
        break;
    case KEYCODE_6:
        keypad->currentKey = '6';
        break;
    case KEYCODE_7:
        keypad->currentKey = '7';
        break;
    case KEYCODE_8:
        keypad->currentKey = '8';
        break;
    case KEYCODE_9:
        keypad->currentKey = '9';
        break;
    case KEYCODE_ASTERISK:
        keypad->currentKey = '*';
        break;
    case KEYCODE_0:
        keypad->currentKey = '0';
        break;
    case KEYCODE_POUND:
        keypad->currentKey = '#';
        break;
    default:
        result = -1;
    }

    return result;
}

/*****************************************************************
 * Function: updateLedArray
 *
 * Purpose:
 *   - displays currentKeyCoord to led array.
 *
 * Arguments:
 *   - keypad (KEYPAD_4X4): keypad ADT
 *
 *****************************************************************/
void updateLedArray(KEYPAD_4X4 * keypad)
{
    LED_ARRAY = keypad->currentKeyCoord;
}
