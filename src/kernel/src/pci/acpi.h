#pragma once
#include <stdint.h>

namespace ACPI
{
    struct RSDP2
    {
        unsigned char signature[8];
        uint8_t checksum;
        uint8_t OEMId[6];
        uint8_t revision;
        uint32_t RSDTAddress;
        uint32_t length;
        uint64_t XSDTAddress;
        uint8_t extendedChecksum;
        uint8_t reserved[3];
    }__attribute__((packed));

    struct SDTHeader
    {
        unsigned char signature[4];
        uint32_t length;
        uint8_t revision;
        uint8_t checksum;
        uint8_t OEMID[6];
        uint8_t OEMTableID[8];
        uint32_t OEMRevision;
        uint32_t creatorID;
        uint32_t creatorRevision;
    }__attribute__((packed));

    struct MCFGHeader
    {
        SDTHeader header;
        uint64_t reserver;
    }__attribute__((packed));

    struct DeviceConfig
    {
        uint64_t baseAddress;
        uint64_t PCISegGroup;
        uint8_t startBus;
        uint8_t endBus;
        uint32_t reserved;
    }__attribute__((packed));

    void* findTable(SDTHeader* header, char* tableName);
}