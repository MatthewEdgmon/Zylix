/**
 * acpi.c - Advanced Configuration and Power Interface
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

#include <stdint.h>
#include <stdio.h>

#include <devices/acpi/acpi.h>

/* RSDP Can be anywhere from 0x000E0000 to 0x000FFFFF in memory, on 16 byte boundary. */
uint32_t* FindRSDP() {

    for(uint32_t i = 0xE0000; i < 0xFFFFF; i += 0x10) {

    }

    printf("RSDP not found. ACPI not enabled.");
    return 0xE0000;
}

void SetupACPI() {
    printf("Starting ACPI sub-system...\n");
    FindRSDP();
}
