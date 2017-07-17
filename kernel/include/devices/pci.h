/**
 * pci.h PCI (Peripheral Component Interface) bus support code.
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

#ifndef __PCI_H__
#define __PCI_H__

#include <stdint.h>

#define PCI_PORT_CONFIG_ADDRESS        0xCF8
#define PCI_PORT_CONFIG_DATA           0xCFC

#define PCI_HEADER_VENDOR_ID           0x00 /* 2 bytes */
#define PCI_HEADER_DEVICE_ID           0x02 /* 2 bytes */
#define PCI_HEADER_COMMAND             0x04 /* 2 bytes */
#define PCI_HEADER_STATUS              0x06 /* 2 bytes */
#define PCI_HEADER_REVISION_ID         0x08 /* 1 byte */
#define PCI_HEADER_PROG_IF             0x09 /* 1 byte */
#define PCI_HEADER_SUBCLASS            0x0A /* 1 byte */
#define PCI_HEADER_CLASS               0x0B /* 1 byte */
#define PCI_HEADER_CACHE_LINE_SIZE     0x0C /* 1 byte */
#define PCI_HEADER_LATENCY_TIMER       0x0D /* 1 byte */
#define PCI_HEADER_HEADER_TYPE         0x0E /* 1 byte */
#define PCI_HEADER_BIST                0x0F /* 1 byte */
#define PCI_HEADER_BAR0                0x10 /* 4 bytes */
#define PCI_HEADER_BAR1                0x14 /* 4 bytes */
#define PCI_HEADER_BAR2                0x18 /* 4 bytes */
#define PCI_HEADER_BAR3                0x1C /* 4 bytes */
#define PCI_HEADER_BAR4                0x20 /* 4 bytes */
#define PCI_HEADER_BAR5                0x24 /* 4 bytes */

#define PCI_HEADER_INTERRUPT_LINE      0x3C /* 1 byte */

#define PCI_HEADER_SECONDARY_BUS       0x19 /* 1 byte */

#define PCI_HEADER_TYPE_DEVICE         0
#define PCI_HEADER_TYPE_BRIDGE         1
#define PCI_HEADER_TYPE_CARDBUS        2

#define PCI_NO_DEVICE                  0xFFFF

const char* PCILookupVendorString(uint16_t vendor_id);
const char* PCILookupVendorShortString(uint16_t vendor_id);
const char* PCILookupDeviceString(uint16_t vendor_id, uint16_t device_id);
const char* PCILookupDeviceDescriptionString(uint16_t vendor_id, uint16_t device_id);
const char* PCILookupClassString(uint8_t class_code, uint8_t subclass_code, uint8_t interface_code) ;
const char* PCILookupSubClassString(uint8_t class_code, uint8_t subclass_code, uint8_t interface_code) ;
const char* PCILookupInterfaceString(uint8_t class_code, uint8_t subclass_code, uint8_t interface_code) ;

uint32_t PCIGetAddress(uint32_t device, uint8_t field);
uint32_t PCIGetDevice(uint8_t bus, uint8_t slot, uint8_t func);
uint8_t  PCIGetDeviceBus(uint32_t device);
uint8_t  PCIGetDeviceSlot(uint32_t device);
uint8_t  PCIGetDeviceFunc(uint32_t device);

uint32_t PCIFind(uint16_t vendor_id, uint16_t device_id);

uint32_t PCIReadField(uint32_t device, uint8_t field, uint8_t size);
void     PCIWriteField(uint32_t device, uint8_t field, uint32_t value);

void PCIDetectAll();
void PCIDetectBus(uint8_t bus);
void PCIDetectDevice(uint8_t bus, uint8_t slot);
void PCIDetectFunction(uint32_t device);

void PCIDebugDumpDeviceInfo(uint32_t device);
void PCIDebugDumpDeviceInfoGrid(uint32_t device);

void SetupPCI();

#endif /* __PCI_H__ */
