#include "console.h"

void Console::proccessStatement()
{
    if(strcmp(statement, "help", statementLenght))
    {
        GLOBAL_RENDERER->Println("Commands: ");
        GLOBAL_RENDERER->Println("\"say\" -> Print out the sentance you typed after the command bellow.");
        GLOBAL_RENDERER->Println("\"clear\" -> Clear the screen.");
        GLOBAL_RENDERER->Println("\"drawRect\" -> Draw rectangle at the coordinates you specified (eg.: drawRect 10,20,40,90).");
        GLOBAL_RENDERER->Println("\"lolCow\" -> Draw a lol cow.");
        GLOBAL_RENDERER->Println("\"sys\" -> Print out system info.");
        GLOBAL_RENDERER->Print("CMD\\>");
    }
    else if(strcmp(statement, "say", 3))
    {
        char str[252];
        for(uint8_t i = 0; i < 251; i++)
            str[i] = (char)0;
        for(int i = 0; i < statementLenght - 4; i++)
            str[i] = statement[4+i];
        GLOBAL_RENDERER->Println(str);
        GLOBAL_RENDERER->Print("CMD\\>");
    }
    else if(strcmp(statement, "clear", statementLenght))
    {
        GLOBAL_RENDERER->Clear(BLUE);
        GLOBAL_RENDERER->CursorPosition.X = 0;
        GLOBAL_RENDERER->CursorPosition.Y = 0;
        GLOBAL_RENDERER->Print("CMD\\>");
    }
    else if(strcmp(statement, "drawRect", 8))
    {
        int coords[4];
        int i2 = 9, coordNum = 0, strInc = 0;
        char str[40];
        
        for(int i = 0; i < 4; i++)
        {
            strInc = 0;
            strclr(str, 39);
            for(uint8_t i = i2; statement[i] != ',' && i < statementLenght; i++){
                str[strInc] = statement[i];
                i2 = i+1;
                strInc++;
            }
            coords[coordNum] = atoi(str, (uint8_t)strInc);;
            coordNum++;
            i2++;
        }

        GLOBAL_RENDERER->DrawRectange(coords[0], coords[1], coords[2]*3, coords[3], RED);

        GLOBAL_RENDERER->Print("CMD\\>");
    }
    else if(strcmp(statement, "lolCow", statementLenght))
    {
        GLOBAL_RENDERER->Println(" _____ ");
        GLOBAL_RENDERER->Println("< lol >");
        GLOBAL_RENDERER->Println(" ----- ");
        GLOBAL_RENDERER->Println("       \\  ^__^");
        GLOBAL_RENDERER->Println("        \\ (oo)\\_______");
        GLOBAL_RENDERER->Println("          (__)\\       )\\/\\");
        GLOBAL_RENDERER->Println("              ||----w |");
        GLOBAL_RENDERER->Println("              ||     ||");
        GLOBAL_RENDERER->Print("CMD\\>");
    }
    else if(strcmp(statement, "sys", statementLenght))
    {
        GLOBAL_RENDERER->DrawRectange(GLOBAL_RENDERER->CursorPosition.X, GLOBAL_RENDERER->CursorPosition.Y, GLOBAL_RENDERER->CursorPosition.X+32*67, GLOBAL_RENDERER->CursorPosition.Y+16*13, CYAN);
        GLOBAL_RENDERER->Println("+-----------------------------------------------------------------+");
        GLOBAL_RENDERER->Println("|       _______  ________   _______      _______   ________       |");
        GLOBAL_RENDERER->Println("|     //       \\/        \\//       \\    /       \\\\/        \\      |");
        GLOBAL_RENDERER->Println("|    //      __/        _//      __/   /        //        _/      |");
        GLOBAL_RENDERER->Println("|   /        _/-        /        _/   /         /-        /       |");
        GLOBAL_RENDERER->Println("|   \\_______/ \\_______//\\_______/     \\________/\\_______//        |");
        GLOBAL_RENDERER->Println("|                                                                 |");
        GLOBAL_RENDERER->Println("|         Author:                               System:           |");
        GLOBAL_RENDERER->Println("|          Tevz Beskovnik                        FSF OS           |");
        GLOBAL_RENDERER->Println("|                                                                 |");
        GLOBAL_RENDERER->Println("|         Write \"help\" for a list of commands.                    |");
        GLOBAL_RENDERER->Println("|                                                                 |");
        GLOBAL_RENDERER->Println("+-----------------------------------------------------------------+");
        GLOBAL_RENDERER->Print("CMD\\>");
    }
    else
    {
        GLOBAL_RENDERER->Println("Command not recognised, write \"help\" for a list of commands.");
        GLOBAL_RENDERER->Print("CMD\\>");
    }
}

void Console::updateStatement(char* newStatment, uint8_t len)
{
    for(uint8_t i = 0; i < 255; i++)
        statement[i] = 0;
    statementLenght = len;
    strcpy(statement, newStatment, len);
}