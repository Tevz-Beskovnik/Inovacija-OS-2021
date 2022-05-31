#pragma once

#include <stdint.h>
#include "../cstr.h"
#include "../print.h"
#include "../rgb.h"

class Console
{
    public:
        char statement[256];
        uint8_t statementLenght = 0;

        void proccessStatement();

        void updateStatement(char* newStatment, uint8_t len);
};