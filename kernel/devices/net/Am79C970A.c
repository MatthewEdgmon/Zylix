/**
 * AM79C970A.c - AMD PCnet-PCI II Network Driver
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

#include <devices/net/Am79C970A.h>

#include <devices/pci.h>

int SetupAm79C970A() {

    uint32_t device = PCIFind(AM79C970A_PCI_VENDOR_ID, AM79C970A_PCI_DEVICE_ID);

    if(device == 0xFFFF) {
        device = PCIFind(AM79C970A_PCI_VENDOR_ID, AM79C970A_PCI_DEVICE_ID_ALT);
        if(device == 0xFFFF) {
            printf("Did not find AMD PCnet-PCI II\n");
            return 1;
        }
    } else {
        printf("Found AMD PCnet-PCI II\n");
    }

    return 0;
}
