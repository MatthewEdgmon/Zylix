/**
 * vesa.h - VESA definitions
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

#ifndef __VESA_H__
#define __VESA_H__

#include <stdint.h>

#define VESA_PMID_SEARCH_START            0x10000
#define VESA_PMID_SEARCH_END              0xFFFFFF

typedef struct vesa_protected_mode_entry_point {
    char     entry_point_string[4];     /* This is "PMID" */
    uint16_t entry_point;               /* Offset of PM entry point within BIOS. */
    uint16_t protected_mode_initialize; /* Offset of PM initialization entry point. */
    uint16_t BIOS_data_selector;        /* Selector to BIOS data area emulation block. */
    uint16_t A0000_selector;            /* Selector to access 0xA0000 physical memory. */
    uint16_t B0000_selector;            /* Selector to access 0xB0000 physical memory. */
    uint16_t B8000_selector;            /* Selector to access 0xB8000 physical memory. */
    uint16_t code_segment_selector;     /* Selector to access code segment as data. */
    uint8_t in_protected_mode;          /* This is set to 1 when in protected mode. */
    uint8_t checksum;                   /* Added to all values of the table to make 0. */
} vesa_protected_mode_entry_point_t;

void VESALocateProtectedModeEntryPoint();
void SetupVESA();

#endif /* __VESA_H__ */
