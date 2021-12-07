#include "pageTableManager.h"

PageTableManager::PageTableManager(PageTable* PML4Address)
    :PML4(PML4Address)
{
    ;
}

void PageTableManager::MapMemory(void* virtualMemory, void* physicalMemory)
{
    PageMapIndexer indexer((u64)virtualMemory);
    PageDirectoryEntry PDE;

    // če 4 slojni paging tabela ne obstaja se ustvari
    // najprej se ustvari page directory pointer
    PDE = PML4->entries[indexer.PDP_i];
    PageTable* PDP;
    if(!PDE.present) // če ni prisotno v spominu treba spravit v spomin 
    {
        PDP = (PageTable*)GLOBAL_ALLOCATOR.RequestPage();
        memset(PDP, 0, 0x1000);
        PDE.address = (u64)PDP >> 12;
        PDE.present = true;
        PDE.readWrite = true;
        PML4->entries[indexer.PDP_i] = PDE;
    }
    else
    {
        PDP = (PageTable*)((u64)PDE.address << 12);
    }

    // ustvari se Page Directory
    PDE = PDP->entries[indexer.PD_i];
    PageTable* PD;
    if(!PDE.present) // če ni prisotno v spominu treba spravit v spomin 
    {
        PD = (PageTable*)GLOBAL_ALLOCATOR.RequestPage();
        memset(PD, 0, 0x1000);
        PDE.address = (u64)PD >> 12;
        PDE.present = true;
        PDE.readWrite = true;
        PDP->entries[indexer.PD_i] = PDE;
    }
    else
    {
        PD = (PageTable*)((u64)PDE.address << 12);
    }

    // ustvari se page table
    PDE = PD->entries[indexer.PT_i];
    PageTable* PT;
    if(!PDE.present) // če ni prisotno v spominu treba spravit v spomin 
    {
        PT = (PageTable*)GLOBAL_ALLOCATOR.RequestPage();
        memset(PT, 0, 0x1000);
        PDE.address = (u64)PT >> 12;
        PDE.present = true;
        PDE.readWrite = true;
        PD->entries[indexer.PT_i] = PDE;
    }
    else
    {
        PT = (PageTable*)((u64)PDE.address << 12);
    }

    // ustvari se page
    PDE = PT->entries[indexer.P_i];
    PDE.address = (u64)physicalMemory >> 12;
    PDE.present = true;
    PDE.readWrite = true;
    PT->entries[indexer.P_i] = PDE;
}