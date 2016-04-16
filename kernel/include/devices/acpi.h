#ifndef __ACPI_H__
#define __ACPI_H__

#include <stdint.h>

#define ACPI_RSDP_SEARCH_START  0xE0000
#define ACPI_RSDP_SEARCH_END 0x100000

typedef struct rsdp_descriptor {
    char signature[8];
    uint8_t checksum;
    char oemid[6];
    uint8_t revision;
    uint32_t rsdtaddress;
} rsdp_descriptor_t;

typedef struct rsdp_descriptor_ext {
    char signature[8];
    uint8_t checksum;
    char oemid[6];
    uint8_t revision;
    uint32_t rsdtaddress;
    uint32_t length;
    uint64_t xsdtaddress;
    uint8_t extended_checksum;
    uint8_t reserved[3];
} rsdp_descriptor_ext_t;

void ACPILocateRSDP();
void ACPIParseRSDPDescriptor();

void SetupACPI();

#endif /* __ACPI_H__ */
