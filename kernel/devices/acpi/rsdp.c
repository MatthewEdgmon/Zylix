#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <devices/acpi/acpi.h>
#include <devices/acpi/rsdp.h>

/**
 * Returns a pointer to the address of the RSDP.
 */
rsdp_t* RSDPLocate() {

    rsdp_t* rsdp;

    /* Start search in first kilobyte of EBDA. */
    uintptr_t ebda = (uint32_t*) 0x40E;
    uint64_t value_of_ebda = &ebda;
    uint64_t value_of_ebda2 = value_of_ebda << 4;
    printf("EBDA Address is 0x%X\n", value_of_ebda2);
    rsdp = RSDPLocateInRange(value_of_ebda2, value_of_ebda2 + 1024);

    /* If not in EBDA, search 0xE0000 to 0xFFFFF. */
    rsdp = RSDPLocateInRange(0xE0000, 0x100000);

    if(rsdp) {
        return rsdp;
    } else {
        return NULL;
    }
}

rsdp_t* RSDPLocateInRange(uintptr_t start, uintptr_t end) {
    for(uintptr_t ptr = start; ptr < end; ptr += ACPI_RSDP_ALIGNMENT) {
        rsdp_t* rsdp = (rsdp_t*) ptr;
        if(RSDPValidate(rsdp)) {
            printf("Found RSDP at 0x%X\n", ptr);
            return rsdp;
        }
    }

    return NULL;
}

/**
 * Validates the RSDP, returns zero if failure.
 */
bool RSDPValidate(rsdp_t* rsdp) {
    if(rsdp->signature != ACPI_RSDP_SIGNATURE) {
        return false;
    }

    return true;
}
