/**
 * bga.c - Bochs graphics adapter driver.
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
#include <string.h>

#include <arch/io.h>
#include <arch/interrupts.h>
#include <arch/registers.h>

#include <devices/video/bga.h>

#include <devices/pci.h>

#include <common.h>

/* TODO A lot of stuff is hardcoded, with no bounds checking or error checking. */

uint8_t bga_enabled = 0;

uint32_t bga_pci_device;

uint32_t* lfb_address;
uint32_t lfb_width = 1024;
uint32_t lfb_height = 768;

uint32_t* BGAGetLFBAddress() {
    return lfb_address;
}

uint32_t BGAGetLFBWidth() {
    return lfb_width;
}

uint32_t BGAGetLFBHeight() {
    return lfb_height;
}

uint8_t BGAIsEnabled() {
    return bga_enabled;
}

void BGAWriteRegister(uint16_t bga_register, uint16_t value) {
    outw(VBE_DISPI_IOPORT_INDEX, bga_register);
    outw(VBE_DISPI_IOPORT_DATA, value);
}

uint16_t BGAReadRegister(uint16_t bga_register) {
    outw(VBE_DISPI_IOPORT_INDEX, bga_register);
    return inw(VBE_DISPI_IOPORT_DATA);
}

uint16_t BGAOffsetToBank(uint32_t offset) {
    return offset / 64000;
}

void BGASetBank(uint16_t bank_number) {
    BGAWriteRegister(VBE_DISPI_INDEX_BANK, bank_number);
}

void BGASetVideoMode(uint16_t width, uint16_t height, uint16_t bpp, uint8_t use_lfb, uint8_t clear_vram) {
    if(bga_enabled == 0) {
        return;
    }

    BGAWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
    BGAWriteRegister(VBE_DISPI_INDEX_XRES, width);
    BGAWriteRegister(VBE_DISPI_INDEX_YRES, height);
    BGAWriteRegister(VBE_DISPI_INDEX_BPP, bpp);
    BGAWriteRegister(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED |
                                            VBE_DISPI_8BIT_DAC |
                         (use_lfb ? VBE_DISPI_LFB_ENABLED : 0) |
                        (clear_vram ? 0 : VBE_DISPI_NOCLEARMEM));

    lfb_width = width;
    lfb_height = height;

    if(use_lfb) {
        lfb_address = (uint32_t*) PCIReadField(bga_pci_device, PCI_HEADER_BAR0, 4);
    }
}

int SetupBGA() {

    bga_pci_device = PCIFind(BGA_PCI_VENDOR_1, BGA_PCI_DEVICE_1);

    if(bga_pci_device == PCI_NO_DEVICE) {
        bga_pci_device = PCIFind(BGA_PCI_VENDOR_2, BGA_PCI_DEVICE_2);
    }

    if(bga_pci_device == PCI_NO_DEVICE) {
        /* No device. */
        return 1;
    }

    uint32_t bga_version = BGAReadRegister(VBE_DISPI_INDEX_ID);

    switch(bga_version) {
        case 0xB0C0:
            printf("Bochs Graphics Adapter is version 1 (0xB0C0).\n");
            break;
        case 0xB0C1:
            printf("Bochs Graphics Adapter is version 2 (0xB0C1).\n");
            break;
        case 0xB0C2:
            printf("Bochs Graphics Adapter is version 3 (0xB0C2).\n");
            break;
        case 0xB0C3:
            printf("Bochs Graphics Adapter is version 4 (0xB0C3).\n");
            break;
        case 0xB0C4:
            printf("Bochs Graphics Adapter is version 5 (0xB0C4).\n");
            break;
        case 0xB0C5:
            printf("Bochs Graphics Adapter is version 6 (0xB0C5).\n");
            break;
        default:
            printf("Bochs Graphics Adapter unknown version (0x%X), aborting.\n", bga_version);
            return 1;
            break;
    }

    lfb_address = (uint32_t*) PCIReadField(bga_pci_device, PCI_HEADER_BAR0, 4);

    bga_enabled = 1;

    return 0;
}
