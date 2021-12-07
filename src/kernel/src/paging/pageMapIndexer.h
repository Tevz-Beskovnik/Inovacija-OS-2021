#pragma once

#include "../typedef.h"

class PageMapIndexer
{
    public:
        u64 PDP_i;
        u64 PD_i;
        u64 PT_i;
        u64 P_i;

        PageMapIndexer(u64 virtualAddress);
};