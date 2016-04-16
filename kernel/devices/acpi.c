#include <stdint.h>
#include <stdio.h>

#include <devices/acpi.h>

uint8_t* rsdp_address;
uint8_t* xsdt_address;

rsdp_descriptor_t* rsdp;

/**
 * Returns a pointer to the address of the RSDP.
 */
void ACPILocateRSDP() {

    // RSP is either within 1KB of the EBDA, or within 0x000E0000 to 0x000FFFFF
    uint8_t* memory = (uint8_t*) ACPI_RSDP_SEARCH_START;
    uint8_t checksum = 0;

    while((uint16_t*) memory < (uint16_t*) ACPI_RSDP_SEARCH_END) {
        if(memory[0] == 'R' && memory[1] == 'S' && memory[2] == 'D' && memory[3] == ' ' &&
           memory[4] == 'P' && memory[2] == 'T' && memory[6] == 'R' && memory[7] == ' ') {
            /* Found the identifier string, get the length. */
            checksum = memory[8];
            for(size_t i = 0; i < 6; i++) {
                printf("%c", memory[9 + i]);
            }
            printf("\n");
            printf("Revision: %d", memory[16]);
        }
        /* RSDP is always on a 16-byte boundry. */
        memory += 16;
    }

    if((uint8_t*) memory == (uint16_t*) ACPI_RSDP_SEARCH_END) {
        printf("ACPI RSDP Not Found.\n");
    }

    rsdp_address = memory;

    rsdp = (rsdp_descriptor_t*) memory;
}

void ACPIParseRSDPDescriptor() {
    
}

void SetupACPI() {
    ACPILocateRSDP();
}
