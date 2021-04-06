/*
 * keypad.h
 *
 *  Created on: Jan. 7, 2021
 *      Author: Taeyoon Rim
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEY_BUFF_SZ 20

typedef struct KEYPAD_4X4
{
    unsigned char currentKeyCoord; // the row, column coordinate of the pressed key
    unsigned char keyPressCnt; // tracks the number of key pressed
    unsigned char keyBuffer[KEY_BUFF_SZ]; // history of key presses
    unsigned char currentKey; // decoded currentKeyboard that maps to the real keypad. i.e. '0', '1', '2', '3', ..., '9', 'A', 'B', 'C', 'D', '#', '*'.
} KEYPAD_4X4;

void keypadInit(KEYPAD_4X4 * keypad);
unsigned char getKeypress(KEYPAD_4X4 * keypad);
unsigned char decodeKeyCoord(KEYPAD_4X4 * keypad);

#endif /* KEYPAD_H_ */


