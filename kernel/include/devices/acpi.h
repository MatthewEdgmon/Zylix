#ifndef __ACPI_H__
#define __ACPI_H__

#include <libc/stdint.h>

struct rsdp_descriptor {
    char signature[8];
    uint8_t checksum;
    char oemid[6];
    uint8_t revision;
    uint32_t rsdtaddress;
} __attribute__ ((packed));

struct rsdp_descriptor_ext {
    char signature[8];
    uint8_t checksum;
    char oemid[6];
    uint8_t revision;
    uint32_t rsdtaddress;
    uint32_t length;
    uint64_t xsdtaddress;
    uint8_t extended_checksum;
    uint8_t reserved[3];
} __attribute__ ((packed));

void SetupACPI();

#endif /* __ACPI_H__ */
