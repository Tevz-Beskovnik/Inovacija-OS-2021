#include "pci.h"

namespace PCI
{
    void enumirateFunction(uint64_t deviceAddress, uint64_t function)
    {
        
    }

    void enumerateDevice(uint64_t busAddress, uint64_t device)
    {
        
    }

    void enumerateBus(uint64_t baseAddress, uint64_t bus)
    {
        uint64_t offset = bus << 20; 

        uint64_t busAddress = baseAddress + offset;

         
    }

    void enumeratePCI(ACPI::MCFGHeader* mcfg)
    {
        int entries = ((mcfg->header.length)-sizeof(ACPI::MCFGHeader)) / sizeof(ACPI::DeviceConfig);

        for(int i = 0; i < entries; i++)
        {
            ACPI::DeviceConfig* newDeviceConf  = (ACPI::DeviceConfig*)((uint64_t)mcfg + sizeof(ACPI::MCFGHeader) + sizeof(ACPI::DeviceConfig) * i);
            for(uint64_t bus = newDeviceConf->startBus; bus < newDeviceConf->endBus; bus++)
            {
                enumerateBus(newDeviceConf->baseAddress, bus);
            }
        }
    }
}