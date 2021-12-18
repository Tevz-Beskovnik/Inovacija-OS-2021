#include "pci.h"

namespace PCI
{
    void enumirateFunction(uint64_t deviceAddress, uint64_t function)
    {
        uint64_t offset = function << 12; 

        uint64_t functionAddress = deviceAddress + offset;

        GLOBAL_PAGE_MANAGER.MapMemory((void*)functionAddress, (void*)functionAddress); 

        PCIDeviceHeader* pciDeviceHeader = (PCIDeviceHeader*)functionAddress;

        if(pciDeviceHeader->deviceID == 0) return;
        if(pciDeviceHeader->deviceID == 0xFFFF) return;

        GLOBAL_RENDERER->Print(DESC::getVendorInfo(pciDeviceHeader->vendorID));
        GLOBAL_RENDERER->Print(" / ");
        GLOBAL_RENDERER->Print(DESC::getDeviceName(pciDeviceHeader->vendorID, pciDeviceHeader->deviceID));
        GLOBAL_RENDERER->Print(" / ");
        GLOBAL_RENDERER->Print(DESC::deviceClasses[pciDeviceHeader->primClass]);
        GLOBAL_RENDERER->Print(" / ");
        GLOBAL_RENDERER->Print(DESC::getSubclassName(pciDeviceHeader->primClass, pciDeviceHeader->subClass));
        GLOBAL_RENDERER->Print(" / ");
        GLOBAL_RENDERER->Print(DESC::getProgIFName(pciDeviceHeader->primClass, pciDeviceHeader->subClass, pciDeviceHeader->progIF));
        GLOBAL_RENDERER->Next();
    }

    void enumerateDevice(uint64_t busAddress, uint64_t device)
    {
        uint64_t offset = device << 15; 

        uint64_t deviceAddress = busAddress + offset;

        GLOBAL_PAGE_MANAGER.MapMemory((void*)deviceAddress, (void*)deviceAddress); 

        PCIDeviceHeader* pciDeviceHeader = (PCIDeviceHeader*)deviceAddress;

        if(pciDeviceHeader->deviceID == 0) return;
        if(pciDeviceHeader->deviceID == 0xFFFF) return;

        for(uint64_t function = 0; function < 8; function++)
        {
            enumirateFunction(deviceAddress, function);
        }
    }

    void enumerateBus(uint64_t baseAddress, uint64_t bus)
    {
        uint64_t offset = bus << 20; 

        uint64_t busAddress = baseAddress + offset;

        GLOBAL_PAGE_MANAGER.MapMemory((void*)busAddress, (void*)busAddress); 

        PCIDeviceHeader* pciDeviceHeader = (PCIDeviceHeader*)busAddress;

        if(pciDeviceHeader->deviceID == 0) return;
        if(pciDeviceHeader->deviceID == 0xFFFF) return;

        for(uint64_t device = 0; device < 32; device++)
        {
            enumerateDevice(busAddress, device);
        }
    }

    void enumeratePCI(ACPI::MCFGHeader* mcfg)
    {
        int entries = ((mcfg->header.length) - sizeof(ACPI::MCFGHeader)) / sizeof(ACPI::DeviceConfig);
        for(int i = 0; i < entries; i++)
        {
            ACPI::DeviceConfig* newDeviceConf  = (ACPI::DeviceConfig*)((uint64_t)mcfg + sizeof(ACPI::MCFGHeader) + (sizeof(ACPI::DeviceConfig) * i));
            for(uint64_t bus = newDeviceConf->startBus; bus < newDeviceConf->endBus; bus++)
            {
                enumerateBus(newDeviceConf->baseAddress, bus);
            }
        }
    }
}