#pragma once

#include <stdint.h>
#include "acpi.h"
#include "vendorLookupTable.h"
#include "../cstr.h"
#include "../print.h"
#include "../paging/pageTableManager.h"

namespace PCI
{
      struct PCIDeviceHeader{
        uint16_t vendorID;
        uint16_t deviceID;
        uint16_t command;
        uint16_t status;
        uint8_t revisionID;
        uint8_t progIF;
        uint8_t subClass;
        uint8_t primClass;
        uint8_t cacheLineSize;
        uint8_t latencyTimer;
        uint8_t headerType;
        uint8_t BIST;
    };

    void enumeratePCI(ACPI::MCFGHeader* mcfg);
}