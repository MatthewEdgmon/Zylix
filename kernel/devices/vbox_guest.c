/**
 * vbox_guest.c - Support code for Virtualbox Guest functionality.
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

#include <devices/pci.h>
#include <devices/vbox_guest.h>

#include <memory/liballoc.h>

static uint16_t vbox_guest_io_port;
static uintptr_t vbox_guest_vmmdev;

void VBoxGuestLog(char input) {
    outb(VBOX_GUEST_LOG_PORT, input);
}

int VBoxGuestHandler(cpu_registers_t* registers) {

    //PICSendEOI();

    return 1;
}

void SetupVBoxGuest() {
    /* Find the PCI device. */
    uint32_t vbox_guest_device = PCIFind(VBOX_GUEST_PCI_VENDOR_ID, VBOX_GUEST_PCI_DEVICE_ID);

    /* BAR0 is the IO port. */
    vbox_guest_io_port = PCIReadField(vbox_guest_device, PCI_HEADER_BAR0, 4) & 0xFFFFFFF0;

    /* BAR1 is the memory-mapped "vmmdevmem" area. */
    vbox_guest_vmmdev = PCIReadField(vbox_guest_device, PCI_HEADER_BAR1, 4) & 0xFFFFFFF0;

    /* Fill out the packet. */
    vbox_guest_info_t* guest_info = malloc(sizeof(vbox_guest_info_t));

    guest_info->header.size         = sizeof(vbox_guest_info_t);
    guest_info->header.version      = VBOX_GUEST_REQUEST_HEADER_VERSION;
    guest_info->header.request_type = VBOX_GUEST_REQUEST_GUEST_INFO;
    guest_info->header.return_code  = 0;
    guest_info->header.reserved1    = 0;
    guest_info->header.reserved2    = 0;
    guest_info->version             = VBOX_GUEST_VMMDEV_VERSION;
    guest_info->os_type             = 0;

    /* Send the packet. */
    outl(vbox_guest_io_port, (uintptr_t) guest_info);

    /* Check return result. */
}
