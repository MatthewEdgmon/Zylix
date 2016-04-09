#include <stdint.h>
#include <string.h>

#include <devices/acpi.h>

#include <arch/io.h>

uint64_t xsdt_address = 0x0000000000000000;

/**
 * Returns a pointer to the address of the RSDP.
 */
void* FindRSDP() {

    // RSP is either within 1KB of the EBDA, or within 0x000E0000 to 0x000FFFFF
    uint16_t rsdp_signature = "RSD PTR ";
    uint32_t search_address = 0x000E0000;

}

/**
 * Add up every byte in the RSDP and ensure the lowest byte of the result is equal to 0.
 */
void VerifyRSDP() {

}

void SetupACPI() {

}
