#include "keyboard.h"

bool capsLock = false;
bool shift = false;
bool alt = false;
bool ctrl = false;

void keyboardHandler(u8 scanCode, u8 chr){
    switch (scanCode)
    {
        case CAPS_KEY_PRESS:
            capsLock = !capsLock;
            break;

        case SHIFT_LEFT_KEY_PRESS:
            shift = true;
            break;

        case SHIFT_RIGHT_KEY_PRESS:
            shift = true;
            break;

        case SHIFT_LEFT_KEY_RELEASE:
            shift = false;
            break;

        case SHIFT_RIGHT_KEY_REALSE:
            shift = false;
            break;

        case ALT_KEY_PRESS:
            alt = true;
            break;

        case ALT_KEY_RELEASE:
            alt = false;
            break;

        case TAB_KEY:
            print("   ", BACKGROUND_BLACK | FOREGROUND_WHITE);
            break;

        case CONTROL_KEY_PRESS:
            ctrl = true;
            break;

        case CONTROL_KEY_RELEASE:
            ctrl = false;
            break;

        case ENTER_KEY_PRESS:
            print("\n", BACKGROUND_BLACK | FOREGROUND_WHITE);
            break;

        case BACKSPACE_KEY_PRESS:
            if(getCursorPos() != 0)
            {
                setCursorPosSingle(getCursorPos() - 1);
                printChar(' ', BACKGROUND_BLACK | FOREGROUND_WHITE);
                setCursorPosSingle(getCursorPos() - 1);
            }
            break;

        default:
            char convertedChar = scanCodeLookupTabelSet1[chr];
            if(chr < 0x5A)
                printChar(convertedChar < 133 && convertedChar > 90 ? convertedChar - (u8)(capsLock | shift)*32 : convertedChar, BACKGROUND_BLACK | FOREGROUND_WHITE);
            break;
    }
}