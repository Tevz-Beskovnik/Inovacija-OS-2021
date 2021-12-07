#include "paging/pageFrameAllocator.h"
#include "paging/pageTableManager.h"
#include "paging/pageMapIndexer.h"
#include "type_conversion.h"
#include "paging/paging.h"
#include "typedef.h"
#include "memory.h"
#include "math.h"
#include "print.h"
#include "bitmap.h"
#include "font.h"
#include "boot.h"
#include "rgb.h"

extern u64 _KernStart; // start of kernel
extern u64 _KernEnd; // end of kernel

struct KernelInfo
{
    PageTableManager* pageTableManager;
};  

KernelInfo InitializeInfo(BootInfo* bootInfo);
