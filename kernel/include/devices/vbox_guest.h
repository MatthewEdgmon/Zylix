/**
 * vbox_guest.h - Support code for Virtualbox Guest functionality.
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

#ifndef __VBOX_GUEST_H__
#define __VBOX_GUEST_H__

#include <stdint.h>

#include <arch/interrupts.h>

#define VBOX_GUEST_LOG_PORT      0x504

#define VBOX_GUEST_PCI_VENDOR_ID  0x80EE
#define VBOX_GUEST_PCI_DEVICE_ID  0xCAFE
#define VBOX_GUEST_VMMDEV_VERSION 0x00010002
#define VBOX_GUEST_REQUEST_HEADER_VERSION 0x10001

#define VBOX_GUEST_REQUEST_GUEST_INFO 50

typedef struct {
    uint32_t size;          /* Size of the packet, including header. */
    uint32_t version;       /* Version */
    uint32_t request_type;  /* Request code. */
    int32_t return_code;    /* Will be filled with the return code from the request. */
    uint32_t reserved1;
    uint32_t reserved2;
} vbox_guest_header_t;

typedef struct {
    vbox_guest_header_t header;
    uint32_t version;
    uint32_t os_type;
} vbox_guest_info_t;

int VBoxGuestHandler(registers_t* registers);

void SetupVBoxGuest();

#endif /* __VBOX_GUEST_H__ */
