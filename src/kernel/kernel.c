#include "print.h"
#include "idt.h"
#include "keyboard.h"
#include "math.h"

extern const char Test[];

void _main(){
    initIDT();
    setKeyboardHandler(keyboardHandler);
    //print(intToChar(-123456789), BACKGROUND_BLACK | FOREGROUND_WHITE);
    //print("\n", BACKGROUND_BLACK | FOREGROUND_WHITE);
    double a = 15.5;
    doubleToChar(a);
    doubleToChar(a);
    //print(doubleToChar(a), BACKGROUND_BLACK | FOREGROUND_WHITE);
    const char* logo[5] = {
        " ______     ______   ______ \n\r",
        "/\\  ___\\   /\\  ___\\ /\\  ___\\ \n\r",
        "\\ \\___  \\  \\ \\  __\\ \\ \\___  \\ \n\r",
        " \\/\\_____\\  \\ \\_\\    \\/\\_____\\ \n\r",
        "  \\/_____/   \\/_/     \\/_____/ \n\r"
    };
    for(int i = 0; i < 5; i++)
    {
        print(logo[i], FOREGROUND_YELLOW | BACKGROUND_BLACK);
    }

    print("\n\rSFS OS kernel\n\r", FOREGROUND_WHITE | BACKGROUND_BLACK);
    setProtectedCurosrPos(0, 7);
    return; 
}