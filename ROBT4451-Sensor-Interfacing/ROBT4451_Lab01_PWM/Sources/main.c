#include <msp430.h>
#include <pwmTest.h>
#include <keypad.h>

struct KEYPAD_4X4 myKeypad;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	timerA0Init();
	keypadInit(&myKeypad);

	while(1)
	{
	    if (!getKeypress(&myKeypad))
	    {
	        decodeKeyCoord(&myKeypad);
	        onClick(&myKeypad);
	    }
	}
}

void onClick(KEYPAD_4X4 * keypad)
{
    switch(keypad->currentKeyCoord)
    {
    case KEYCODE_1:
        TA0CCR1 = 1;
        break;
    case KEYCODE_2:
        TA0CCR1 = 2;
        break;
    case KEYCODE_3:
        TA0CCR1 = 3;
        break;
    case KEYCODE_4:
        TA0CCR1 = 4;
        break;
    case KEYCODE_5:
        TA0CCR1 = 5;
        break;
    case KEYCODE_6:
        TA0CCR1 = 6;
        break;
    case KEYCODE_7:
        TA0CCR1 = 7;
        break;
    case KEYCODE_8:
        TA0CCR1 = 8;
        break;
    case KEYCODE_9:
        TA0CCR1 = 9;
        break;
    case KEYCODE_0:
        TA0CCR1 = 0;
        break;
    case KEYCODE_POUND:
        TA0CCR1 = 10;
        break;
    default:
    }
}
