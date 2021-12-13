#include "acpi.h"

namespace ACPI
{
    void* findTable(SDTHeader* header, char* tableName)
    {
        int entries = (header->length - sizeof(ACPI::SDTHeader)) / 8;
        for(int i = 0; i < entries; i++)
        {
            ACPI::SDTHeader* nextHeader = (SDTHeader*)*(uint64_t*)((uint64_t)header + sizeof(SDTHeader) + (i * 8));
            for(int j = 0; j < 4; j++)
            {
                if(tableName[j] != nextHeader->signature[j])
                    break;
                if(j == 3)
                    return (void*)nextHeader;
            }
        }
        return 0;
    }
}