/*
 * keypad.h
 *
 *  Created on: Jan. 7, 2021
 *      Author: Taeyoon Rim
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

typedef struct KEYPAD_4X4
{
    unsigned char currentKeyCoord; // the row, column coordinate of the pressed key
    unsigned char keyPressCnt; // tracks the number of key pressed
    unsigned char keyBuffer[KEY_BUFF_SZ]; // history of key presses
    unsigned char currentKey; // decoded currentKeyboard that maps to the real keypad. i.e. '0', '1', '2', '3', ..., '9', 'A', 'B', 'C', 'D', '#', '*'.
} KEYPAD_4X4;

#define KEY_BUFF_SZ 20

#define KEYCODE_1 (BIT4 + BIT0) // ROW, COL = 1, 1
#define KEYCODE_2 (BIT4 + BIT1) // ROW, COL = 1, 2
#define KEYCODE_3 (BIT4 + BIT2) // ROW, COL = 1, 3

#define KEYCODE_4 (BIT5 + BIT0) // ROW, COL = 2, 1
#define KEYCODE_5 (BIT5 + BIT1) // ROW, COL = 2, 2
#define KEYCODE_6 (BIT5 + BIT2) // ROW, COL = 2, 3

#define KEYCODE_7 (BIT6 + BIT0) // ROW, COL = 3, 1
#define KEYCODE_8 (BIT6 + BIT1) // ROW, COL = 3, 2
#define KEYCODE_9 (BIT6 + BIT2) // ROW, COL = 3, 3

#define KEYCODE_ASTERISK (BIT7 + BIT0) // ROW, COL = 4, 1
#define KEYCODE_0 (BIT7 + BIT1) // ROW, COL = 4, 2
#define KEYCODE_POUND (BIT7 + BIT2) // ROW, COL = 4, 3

void keypadInit(KEYPAD_4X4 * keypad);
unsigned char getKeypress(KEYPAD_4X4 * keypad);
unsigned char decodeKeyCoord(KEYPAD_4X4 * keypad);

#endif /* KEYPAD_H_ */


