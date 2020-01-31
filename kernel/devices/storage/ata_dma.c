/**
 * ata_dma.c - Generic ATA DMA mode driver.
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

#include <arch/io.h>
#include <arch/interrupts.h>
#include <arch/registers.h>

#include <devices/storage/ata.h>
#include <devices/storage/ata_dma.h>
#include <devices/pci.h>

#include <common.h>

void ATA_DMA_ReadDMA28() {
    // Send 0xC8
}

void ATA_DMA_WriteDMA28() {
    // Send 0x25
}

void ATA_DMA_ReadDMA48() {
    // Send 0xCA
}

void ATA_DMA_WriteDMA48() {
    // Send 0x35
}

void ATA_DMA_SoftwareReset() {
    printf("Yes\n");
}

void ATA_DMA_TestRead() {
    printf("No\n");
}

int SetupATA_DMA() {

    uint32_t disk_controller_device = PCIFind(0x8086, 0x2829);

    if(disk_controller_device == 0xFFFF) {
        printf("[ATA_DMA]: No DMA capable ATA disk controller found.\n");
        return;
    } else {
        printf("[ATA_DMA]: Found DMA capable ATA disk controller: %04X\n", disk_controller_device);
    }

    uint32_t disk_controller_bar0 = PCIReadField(disk_controller_device, PCI_HEADER_BAR0, 4);
    uint32_t disk_controller_bar1 = PCIReadField(disk_controller_device, PCI_HEADER_BAR1, 4);
    uint32_t disk_controller_bar2 = PCIReadField(disk_controller_device, PCI_HEADER_BAR2, 4);
    uint32_t disk_controller_bar3 = PCIReadField(disk_controller_device, PCI_HEADER_BAR3, 4);
    uint32_t disk_controller_bar4 = PCIReadField(disk_controller_device, PCI_HEADER_BAR4, 4);
    uint32_t disk_controller_bar5 = PCIReadField(disk_controller_device, PCI_HEADER_BAR5, 4);

    printf("[ATA_DMA]: BAR0 Primary Command Task File Base Address Register: %04X\n", disk_controller_bar0);
    printf("[ATA_DMA]: BAR1 Primary Control Task File Base Address Register: %04X\n", disk_controller_bar1);
    printf("[ATA_DMA]: BAR2: %04X\n", disk_controller_bar2);
    printf("[ATA_DMA]: BAR3: %04X\n", disk_controller_bar3);
    printf("[ATA_DMA]: BAR4 Bus Master Register port offset is: %04X\n", disk_controller_bar4);
    printf("[ATA_DMA]: BAR5: %04X\n", disk_controller_bar5);

    /* Prepare a PRDT in memory. */
    /* Send the PHYSICAL PRDT address to the Bus Master PRDT Register. */
    /* Set the direction of the data transfer by setting the Read/Write bit in the Bus Master Command Register */
    /* Read the controller and drive status to determine if the transfer completed successfully. */
    /* Find Bus Master Register in BAR4 in PCI Configuration Space of the disk controller. */

    /*
    (Primary ATA bus)
    0x0			Command (byte)
    0x2			Status (byte)
    0x4-0x7		PRDT Address (uint32_t)

    (Secondary ATA bus)
    0x8			Command (byte)
    0xA			Status (byte)
    0xC-0xF		PRDT Address (uint32_t)
    */

    return 0;
}
