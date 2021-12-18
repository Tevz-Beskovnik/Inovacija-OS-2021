#pragma once
#include <stdint.h>
#include "../cstr.h"

namespace DESC
{
    extern const char* deviceClasses[];

    const char* getVendorInfo(uint16_t vendorId);

    const char* getDeviceName(uint16_t vendorId, uint16_t deviceId);

    const char* massStorageControllerSubclassName(uint8_t subclassCode);

    const char* serialBusControllerSubclassName(uint8_t subclassCode);

    const char* bridgeDeviceSubclassName(uint8_t subclassCode);

    const char* getSubclassName(uint8_t classCode, uint8_t subclassCode);

    const char* getProgIFName(uint8_t classCode, uint8_t subclassCode, uint8_t progIF);
}
