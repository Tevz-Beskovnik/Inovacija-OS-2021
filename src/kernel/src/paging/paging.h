#pragma once

#include "../typedef.h" 

struct PageDirectoryEntry 
{
    // this is the struct from the notes.md 9 bits attributes 3 bits for dev use and 52 bit address
    bool present : true;
    bool readWrite : true;
    bool UserSupre : true;
    bool writeTrough : true;
    bool cacheDisabled : true;
    bool accessed : true;
    bool ignore0 : true;
    bool largerPages : true;
    bool ignore1: true;
    u8 available : 3;
    
};