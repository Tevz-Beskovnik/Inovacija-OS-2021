#include "boot.h"

const char* EFI_MEMORY_TYPE_STRINGS[] { // memory spaces
    "EfiReservedMemoryType", 
    "EfiLoaderCode",
    "EfiLoaderData",
    "EfiBootServicesCode",
    "EfiBootServicesData",
    "EFIRuntimeServicesCode",
    "EFIRuntimeServicesData",
    "EfiConventionalMemory", // memory EFI has not used (that is what can be used in kernel)
    "EfiUnusableMemory", // unusable memory
    "EfiACPIReclaimMemory", // memory that can be used after getting data from ACPI tables (about 90% of possible memory ussualy)
    "EfiACPMemoryNVS",
    "EfiMemoryMappedIO",
    "EfiMemoryMappedIOPortSpace",
    "EfiPalCode"
};