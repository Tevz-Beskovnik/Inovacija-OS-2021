#include "kernelUtil.h"
#include "cstr.h"
#include "rgb.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    const char* logo[13] = {
        "+-----------------------------------------------------------------+",
        "|       _______  ________   _______      _______   ________       |",
        "|     //       \\/        \\//       \\    /       \\\\/        \\      |",
        "|    //      __/        _//      __/   /        //        _/      |",
        "|   /        _/-        /        _/   /         /-        /       |",
        "|   \\_______/ \\_______//\\_______/     \\________/\\_______//        |",
        "|                                                                 |",
        "|         Author:                               System:           |",
        "|          Tevz Beskovnik                        FSF OS           |",
        "|                                                                 |",
        "|         Write \"help\" for a list of commands.                    |",
        "|                                                                 |",
        "+-----------------------------------------------------------------+"
        };

    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Clear(BLUE);
    GLOBAL_RENDERER->DrawRectange(0, 32, 32*67, 16*15, CYAN);
    GLOBAL_RENDERER->Print(logo[0]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[1]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[2]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[3]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[4]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[5]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[6]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[7]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[8]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[9]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[10]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[11]);
    GLOBAL_RENDERER->Next();
    GLOBAL_RENDERER->Print(logo[12]);
    GLOBAL_RENDERER->Next();

    GLOBAL_RENDERER->Print("CMD\\>");

    while(true)
    {
        asm("hlt");    
    }
}