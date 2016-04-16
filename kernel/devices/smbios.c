#include <stdint.h>
#include <stdio.h>

#include <arch/io.h>

#include <devices/smbios.h>
#include <logging.h>
#include <terminal.h>

smbios_entry_point_t* smbios;

uint8_t* smbios_address;

uint8_t smbios_structures = 0;
uint8_t smbios_version_major = 0;
uint8_t smbios_version_minor = 0;

/**
 * The search starts at memory location 0xF0000, up to 0x100000
 * If there is a series of characters "_SM_", it's possibly a header, skip ahead
 * and check for "_DMI_", at that point, verify the checksum. If all these
 * conditions are met, it's an SMBIOS header.
 */
void SMBIOSLocateEntryPoint() {

    uint8_t* memory = (uint8_t*) SMBIOS_SEARCH_START;//0xF0000;
    uint8_t length;
    uint8_t checksum;
    
    while((uint16_t*) memory < (uint16_t*) SMBIOS_SEARCH_END) {
        if(memory[0] == '_' && memory[1] == 'S' && memory[2] == 'M' && memory[3] == '_') {
            /* Found the identifier string, get the length. */
            length = memory[5];
            checksum = 0;
            /* Add all the elements together. */
            for(size_t i = 0; i < length; i++) {
                checksum += memory[i];
            }
            /* Looks good. */
            if(checksum == 0) {
                break;
            }
        }
        memory += 16;
    }

    if((uint8_t*) memory == (uint16_t*) SMBIOS_SEARCH_END) {
        printf("SMBIOS Not Found.\n");
    }

    smbios_address = memory;

    smbios = (smbios_entry_point_t*) memory;
}

void SMBIOSParseEntryPointTable() {
    smbios_version_major = smbios->major_version;
    smbios_version_minor = smbios->minor_version;

    printf("Found SMBIOS version %d.%d at 0x%X\n", smbios->major_version,
                                                   smbios->minor_version,
                                                   smbios_address);

    printf("Number of headers: %d\n", smbios->number_of_structures);

    smbios_header_t* this_header = (smbios_header_t*) smbios->table_address;

    SMBIOSParseHeader(this_header);

}

void SMBIOSParseHeader(smbios_header_t* header) {

    uint16_t* header_address = (uint16_t*) header;

    switch(header->type) {
        case SMBIOS_HEADER_BIOS:
            printf("BIOS header.\n");
            break;
        case SMBIOS_HEADER_SYSTEM:
            printf("System header.\n");
            break;
        case SMBIOS_HEADER_MAINBOARD:
            printf("Mainboard header.\n");
            break;
        case SMBIOS_HEADER_SYSTEM_BOOT:
            printf("System boot structure.\n");
            break;
        case SMBIOS_HEADER_FINAL:
            printf("Final SMBIOS header.\n");
            break;
        default:
            printf("Non-standard header.\n");
            break;
    }

    printf("Type: %d, Length: %d, Handle %d\n", header->type, header->length, header->handle);

    printf("Type: %d\n", header_address[0]);

}

void SetupSMBIOS() {
    SMBIOSLocateEntryPoint();
    SMBIOSParseEntryPointTable();
}
