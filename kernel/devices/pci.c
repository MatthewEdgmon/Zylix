/**
 * pci.c PCI (Peripheral Component Interface) bus support code.
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

#include <devices/pci.h>
#include <devices/pci_database.h>

uint64_t pci_device_count = 0; /* How many slots are populated with devices. */
uint64_t pci_bus_count = 0; /* How many buses the system has. */

uint32_t pci_devices[1024];

/**
 * Takes a vendor ID and returns the vendor name.
 */
const char* PCILookupVendorString(uint16_t vendor_id) {
    for(size_t i = 0; i < PCI_VENDOR_TABLE_LENGTH; i++) {
        if(pci_vendor_table[i].vendor_id == vendor_id) {
            return pci_vendor_table[i].vendor_string_full;
        }
    }

    return "";
}

/**
 * Takes a vendor ID and returns the full vendor name string.
 */
const char* PCILookupVendorShortString(uint16_t vendor_id) {
    for(size_t i = 0; i < PCI_VENDOR_TABLE_LENGTH; i++) {
        if(pci_vendor_table[i].vendor_id == vendor_id) {
            return pci_vendor_table[i].vendor_string_short;
        }
    }

    return "";
}

/**
 * Takes a vendor ID and device ID and returns a description of that device.
 */
const char* PCILookupDeviceString(uint16_t vendor_id, uint16_t device_id) {
    for(size_t i = 0; i < PCI_DEVICE_TABLE_LENGTH; i++) {
		if(pci_device_table[i].vendor_id == vendor_id && pci_device_table[i].device_id == device_id) {
			return pci_device_table[i].chip;
		}
	}

	return "";
}

/**
 * Takes a vendor ID and device ID and returns a full description of that device.
 */
const char* PCILookupDeviceDescriptionString(uint16_t vendor_id, uint16_t device_id) {
    for(size_t i = 0; i < PCI_DEVICE_TABLE_LENGTH; i++) {
		if(pci_device_table[i].vendor_id == vendor_id && pci_device_table[i].device_id == device_id) {
			return pci_device_table[i].chip_description;
		}
	}

	return "";
}

const char* PCILookupClassString(uint8_t class_code, uint8_t subclass_code, uint8_t interface_code) {
    for(size_t i = 0; i < PCI_CLASS_CODE_TABLE_LENGTH; i++) {
		if(pci_class_code_table[i].base_class == class_code &&
           pci_class_code_table[i].sub_class == subclass_code &&
           pci_class_code_table[i].prog_interface == interface_code) {
			return pci_class_code_table[i].base_description;
		}
	}

	return "";
}

const char* PCILookupSubClassString(uint8_t class_code, uint8_t subclass_code, uint8_t interface_code)  {
    for(size_t i = 0; i < PCI_CLASS_CODE_TABLE_LENGTH; i++) {
        if(pci_class_code_table[i].base_class == class_code &&
           pci_class_code_table[i].sub_class == subclass_code &&
           pci_class_code_table[i].prog_interface == interface_code) {
			return pci_class_code_table[i].sub_description;
		}
	}

	return "";
}

const char* PCILookupInterfaceString(uint8_t class_code, uint8_t subclass_code, uint8_t interface_code)  {
    for(size_t i = 0; i < PCI_CLASS_CODE_TABLE_LENGTH; i++) {
        if(pci_class_code_table[i].base_class == class_code &&
           pci_class_code_table[i].sub_class == subclass_code &&
           pci_class_code_table[i].prog_interface == interface_code) {
			return pci_class_code_table[i].prog_description;
		}
	}

	return "n/a";
}

/**
 * This function will create the 32 bit integer to send to PCI_CONFIG_ADDRESS to
 * to select the associated configuration space.
 */
uint32_t PCIGetAddress(uint32_t device, uint8_t field) {
    return 0x80000000 | (PCIGetDeviceBus(device) << 16)
                      | (PCIGetDeviceSlot(device) << 11)
                      | (PCIGetDeviceFunc(device) << 8)
                      | ((field) & 0xFC);
}

uint32_t PCIGetDevice(uint8_t bus, uint8_t slot, uint8_t func) {
    return (uint32_t)((bus << 16) | (slot << 8) | func);
}

uint8_t PCIGetDeviceBus(uint32_t device){
    return (uint8_t)((device >> 16));
}

uint8_t PCIGetDeviceSlot(uint32_t device){
    return (uint8_t)((device >> 8));
}

uint8_t PCIGetDeviceFunc(uint32_t device){
    return (uint8_t)(device);
}

/**
 * This returns a 32 bit integer representing the device, if found.
 */
uint32_t PCIFind(uint16_t vendor_id, uint16_t device_id) {
    for(size_t i = 0; i < pci_device_count; i++) {
        if(PCIReadField(pci_devices[i], PCI_HEADER_VENDOR_ID, 2) == vendor_id &&
           PCIReadField(pci_devices[i], PCI_HEADER_DEVICE_ID, 2) == device_id) {
               return pci_devices[i];
        }
    }
    return 0xFFFF;
}

uint32_t PCIReadField(uint32_t device, uint8_t field, uint8_t size) {

    /* Select device at address. */
    outl(PCI_PORT_CONFIG_ADDRESS, PCIGetAddress(device, field));

    if(size == 4) {
        uint32_t value = inl(PCI_PORT_CONFIG_DATA);
        return value;
    } else if(size == 2) {
        uint32_t value = inw(PCI_PORT_CONFIG_DATA + (field & 2));
        return value;
    } else if(size == 1) {
        uint8_t value = inb(PCI_PORT_CONFIG_DATA + (field & 3));
        return value;
    }

    return 0xFFFF;
}

void PCIWriteField(uint32_t device, uint8_t field, uint32_t value) {
    outl(PCI_PORT_CONFIG_ADDRESS, PCIGetAddress(device, field));
    outl(PCI_PORT_CONFIG_DATA, value);
}

/**
 * This function starts a 4 layer recursive search for all PCI devices and buses.
 */
void PCIDetectAll() {
    uint32_t device;
    uint8_t bus = 0;
    uint8_t slot = 0;
    uint8_t function = 0;

    device = PCIGetDevice(bus, slot, function);

    if((PCIReadField(device, PCI_HEADER_HEADER_TYPE, 1) & 0x80) == 0) {
        /* Single PCI host controller with one bus. */
        pci_bus_count++;
        PCIDetectBus(0);
    } else {
        /* Multiple PCI host controllers. */
        for(function = 0; function < 8; function++) {
            device = PCIGetDevice(0, 0, function);
            if(PCIReadField(device, PCI_HEADER_VENDOR_ID, 2) == PCI_NO_DEVICE) {
                break;
            }
            bus = function;
            pci_bus_count++;
            PCIDetectBus(bus);
        }
    }
}

void PCIDetectBus(uint8_t bus) {
    uint8_t slot;

    for(slot = 0; slot < 32; slot++) {
        PCIDetectDevice(bus, slot);
    }
}

void PCIDetectDevice(uint8_t bus, uint8_t slot) {
    uint32_t device;
    uint8_t function = 0;

    device = PCIGetDevice(bus, slot, function);

    if(PCIReadField(device, PCI_HEADER_VENDOR_ID, 2) == PCI_NO_DEVICE) {
        /* No device detected. */
        return;
    }

    /* Check function 0. */
    PCIDetectFunction(device);

    /* Ensure there is only 1 function. */
    if((PCIReadField(device, PCI_HEADER_HEADER_TYPE, 1) & 0x80) != 0) {
        /* Multi-Function device, check each function. */
        for(function = 1; function < 8; function++) {
            device = PCIGetDevice(bus, slot, function);
            if(PCIReadField(device, PCI_HEADER_VENDOR_ID, 2) != PCI_NO_DEVICE) {
                PCIDetectFunction(device);
                pci_devices[pci_device_count] = device;
                pci_device_count++;
            }
        }
    }

    pci_devices[pci_device_count] = device;
    pci_device_count++;
}

void PCIDetectFunction(uint32_t device) {
    uint8_t bridged_bus;

    /* Check if the device is a PCI to PCI bridge, if so handle the second bus. */
    if(PCIReadField(device, PCI_HEADER_CLASS, 1) == 0x06 && (PCIReadField(device, PCI_HEADER_SUBCLASS, 1) == 0x04)) {
        bridged_bus = PCIReadField(device, PCI_HEADER_SECONDARY_BUS, 1);
        pci_bus_count++;
        PCIDetectBus(bridged_bus);
    }
}

void PCIDebugDumpDeviceInfo(uint32_t device) {
    uint8_t bus = PCIGetDeviceBus(device);
    uint8_t slot = PCIGetDeviceSlot(device);
    uint16_t vendor_id = PCIReadField(device, PCI_HEADER_VENDOR_ID, 2);
    uint16_t device_id = PCIReadField(device, PCI_HEADER_DEVICE_ID, 2);
    uint8_t revision_id = PCIReadField(device, PCI_HEADER_REVISION_ID, 1);
    uint8_t class = PCIReadField(device, PCI_HEADER_CLASS, 1);
    uint8_t subclass = PCIReadField(device, PCI_HEADER_SUBCLASS, 1);
    uint8_t interface = PCIReadField(device, PCI_HEADER_PROG_IF, 1);

    char* vendor_string = PCILookupVendorString(vendor_id);
    char* device_string = PCILookupDeviceString(vendor_id, device_id);
    char* device_string_long = PCILookupDeviceDescriptionString(vendor_id, device_id);
    char* class_string = PCILookupClassString(class, subclass, interface);
    char* subclass_string = PCILookupSubClassString(class, subclass, interface);
    char* interface_string = PCILookupInterfaceString(class, subclass, interface);

    printf("PCI BUS%d/SLOT%d Information:\n", bus, slot);
    printf("    [Vendor 0x%X] %s\n", vendor_id, vendor_string);
    printf("    [Device 0x%X] %s\n", device_id, device_string);
    printf("    [Description]   %s\n", device_string_long);
    printf("    [Revision]      %X\n", revision_id);
    printf("    [Class]         %s\n", class_string);
    printf("    [Subclass]      %s\n", subclass_string);
    printf("    [Interface]     %s\n", interface_string);
}

void PCIDebugDumpDeviceInfoGrid(uint32_t device) {
    uint8_t bus = PCIGetDeviceBus(device);
    uint8_t slot = PCIGetDeviceSlot(device);
    uint16_t vendor_id = PCIReadField(device, PCI_HEADER_VENDOR_ID, 2);
    uint16_t device_id = PCIReadField(device, PCI_HEADER_DEVICE_ID, 2);
    uint8_t revision_id = PCIReadField(device, PCI_HEADER_REVISION_ID, 1);
    uint8_t class = PCIReadField(device, PCI_HEADER_CLASS, 1);
    uint8_t subclass = PCIReadField(device, PCI_HEADER_SUBCLASS, 1);
    uint8_t interface = PCIReadField(device, PCI_HEADER_PROG_IF, 1);

    char* vendor_string = PCILookupVendorString(vendor_id);
    char* device_string = PCILookupDeviceString(vendor_id, device_id);
    char* class_string = PCILookupClassString(class, subclass, interface);
    char* subclass_string = PCILookupSubClassString(class, subclass, interface);
    char* interface_string = PCILookupInterfaceString(class, subclass, interface);

    printf("PCI BUS%d/SLOT%d Vend: 0x%X Device: 0x%X\n", bus, slot, vendor_id, device_id);
}

void SetupPCI() {
    /* Option #1: Computer doesn't support PCI (too old or far future). */
    /* Option #2: Computer supports config space address mechanism 2. */
    /* Option #3: Computer supports config space address mechanism 1 but not memory mapped access. */
    /* Option #4: Computer supports config space address mechanism 1 and memory mapped access. */

    // TODO: Currently we only use PCI Config Space Mechanism 1

    PCIDetectAll();

    printf("There are %d PCI devices on %d bus(es).\n", pci_device_count, pci_bus_count);

}
