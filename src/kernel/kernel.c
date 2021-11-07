#include "print.h"

void _main(){
    const char* logo[5] = {
        " ______     ______   ______ \n",
        "/\\  ___\\   /\\  ___\\ /\\  ___\\ \n",
        "\\ \\___  \\  \\ \\  __\\ \\ \\___  \\ \n",
        " \\/\\_____\\  \\ \\_\\    \\/\\_____\\ \n",
        "  \\/_____/   \\/_/     \\/_____/ \n"
    };
    for(int i = 0; i < 5; i++)
    {
        print(logo[i]);
    }
    print("\n SFS OS kernel \n");
    return;
}