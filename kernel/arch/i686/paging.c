/**
 * paging.c - i686 Paging
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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cpu_info_i686.h"
#include "paging.h"

page_directory_t* page_directory;
page_table_t* page_table;

extern void PagingEnable(page_directory_t*);
extern void PagingActivatePSE(void);
extern void PagingActivatePAE(void);

bool using_pae = false;
bool using_pse = false;

/**
 * Returns a physical address for a mapped virtual address.
 */
uintptr_t PagingGetPhysical(uintptr_t virtual) {

    uint32_t page_directory_index = (uint32_t) virtual >> 22;
    uint32_t page_table_index = (uint32_t) virtual >> 12 & 0x03FF;

    return NULL;
}

/**
 * Maps a physical address to a virtual address.
 * NOTE: Both address must be page aligned.
 */
void PagingMapPage(uintptr_t physical, uintptr_t virtual, uint16_t flags) {
    /* Ensure both addresses are page aligned. */

    uint32_t page_directory_index = (uint32_t) virtual >> 22;
    uint32_t page_table_index = (uint32_t) virtual >> 12 & 0x03FF;

    /* Flush TLB. */
}

void PagingDebugPrintDirectory(page_directory_t* directory) {

}

void SetupPaging() {

    if(cpu_info->features_PAE) {
        PagingActivatePAE();
        using_pae = true;
    }

    if(cpu_info->features_PSE) {
        PagingActivatePSE();
        using_pse = true;
    }

    /* Determine total memory size. */

    //PagingEnable(page_directory);
}

// CR3 GETS LOADED SUCCESSFULLY, ACTUALYL SETTING THE PROTECTION BITS CRASHES SYSTEM.
