#pragma once

#include <stdint.h>
#include "acpi.h"

namespace PCI
{
    void enumeratePCI(ACPI::MCFGHeader* mcfg);
}