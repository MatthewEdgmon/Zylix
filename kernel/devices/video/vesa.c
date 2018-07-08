/**
 * vesa.c
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdint.h>

#include <devices/video/vesa.h>

uint8_t* pmid_address;
uint8_t* bios_emulation_area;

/**
 * Start searching the BIOS area for the 'PMID signature.'
 */
void VESALocateProtectedModeEntryPoint() {

    uint8_t* memory = (uint8_t*) VESA_PMID_SEARCH_START;
    uint8_t checksum;

    /* Unlike the SMBIOS header, the VBE PMID table is not 16 byte aligned, so
     * we have to go through the BIOS copy byte by byte. Grrrr. */
    while((uint16_t*) memory < (uint16_t*) VESA_PMID_SEARCH_END) {
        if(memory[0] == 'P' && memory[1] == 'M' && memory[2] == 'I' && memory[3] == 'D') {
            printf("Found possible match\n");
        }
        if(memory[0] == 'P' && memory[1] == 'M' && memory[2] == 'I' && memory[3] == 'D') {
            /* Get the checksum from the table. */
            checksum = memory[20];
            /* Add all the elements together. */
            for(size_t i = 0; i < 19; i++) {
                checksum += memory[i];
            }
            /* Looks good. */
            if(checksum == 0) {
                break;
            }
        }
        memory += 1;
    }

    if((uint8_t*) memory == (uint16_t*) VESA_PMID_SEARCH_END) {
        printf("VBE protected mode entry point not found.\n");
        return;
    }

    printf("Found VBE PMID at 0x%X\n", pmid_address);
    pmid_address = memory;
}

void SetupVESA() {
    printf("Starting VESA video...\n");
    printf("Allocating 32kb buffer.\n");
    printf("Copying BIOS to 32kb buffer.\n");
    VESALocateProtectedModeEntryPoint();
}
