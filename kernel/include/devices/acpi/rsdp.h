#ifndef __RSDP_H__
#define __RSDP_H__

#include <stdbool.h>
#include <stdint.h>

#define ACPI_RSDP_SEARCH_START 0xE0000
#define ACPI_RSDP_SEARCH_END   0x100000
#define ACPI_RSDP_SIGNATURE    0x2052545020445352 /* 'RSD PTR ' */
#define ACPI_RSDP_ALIGNMENT    16

typedef struct rsdp {
    char signature[8];
    uint8_t checksum;
    char oemid[6];
    uint8_t revision;
    uint32_t rsdtaddress;

    /* Following fields are present only if revision >= 2 */
    uint32_t length;
    uint64_t xsdtaddress;
    uint8_t extended_checksum;
    uint8_t reserved[3];
} rsdp_t;

rsdp_t* RSDPLocate();
rsdp_t* RSDPLocateInRange(uintptr_t start, uintptr_t end);

bool RSDPValidate(rsdp_t* rsdp);

#endif /* __RSDP_H__ */
