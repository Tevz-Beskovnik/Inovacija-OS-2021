#include "keyboard.h"
#include "../cstr.h"

    bool isLeftShiftPressed;
    bool isRightShiftPressed;

    //command from input
    char command[256];
    uint8_t commandCount = 0;

    Console console;

void HandleKeyboard(uint8_t scancode){

    switch (scancode){
        case LeftShift:
            isLeftShiftPressed = true;
            return;
        case LeftShift + 0x80:
            isLeftShiftPressed = false;
            return;
        case RightShift:
            isRightShiftPressed = true;
            return;
        case RightShift + 0x80:
            isRightShiftPressed = false;
            return;
        case Enter:
            GLOBAL_RENDERER->Next();
            console.updateStatement(command, commandCount);
            console.proccessStatement();
            for(uint8_t i = 0; i < commandCount; i++)
                command[i] = 0;
            commandCount = 0;
            return;
        case Spacebar:
            GLOBAL_RENDERER->PutChar(' ');
            command[commandCount] = ' ';
            if(commandCount < 255)
                commandCount++;
            return;
        case BackSpace:
            if(GLOBAL_RENDERER->CursorPosition.X > 5*8)
            {
                commandCount--;
                command[commandCount] = 0;
                GLOBAL_RENDERER->ClearChar(BLUE);
            }
            return;
        default:
            char ascii = QWERTY::translate(scancode, isLeftShiftPressed | isRightShiftPressed);
            if (ascii != 0){
                GLOBAL_RENDERER->PutChar(ascii);
                command[commandCount] = ascii;
                if(commandCount < 255)
                    commandCount++;
            }
            break;
    }

}