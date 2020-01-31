/**
 * acpi.h - Advanced Configuration and Power Interface
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

#ifndef __ACPI_ZYLIX_H__
#define __ACPI_ZYLIX_H__

#include <stdint.h>

typedef struct rsdp_descriptor {
    char signature[8];
    uint8_t checksum;
    char oem_id[6];
    uint8_t revision;
    uint32_t rsdt_address;
} rsdp_descriptor_t __attribute__((packed));

typedef struct rsdp_descriptor2 {
    rsdp_descriptor_t original_descriptor;

    uint32_t length;
    uint64_t xsdt_address;
    uint8_t extended_checksum;
    uint8_t reserved[3];
} rsdp_descriptor2_t __attribute__((packed));

void SetupACPI();

#endif /* __ACPI_ZYLIX_H__ */
