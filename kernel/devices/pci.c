#include <stdint.h>
#include <stdio.h>

#include <devices/pci.h>
#include <devices/pci_database.h>

#include <arch/io.h>

uint16_t PCIConfigReadWord(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {

    uint16_t return_value = 0;

    uint32_t address = ((bus << 16) | (slot << 11) | (function << 8) | (offset & PCI_CONFIG_DATA) | ((uint32_t)0x80000000));

    outw(PCI_CONFIG_ADDRESS, address);

    return_value = inw(PCI_CONFIG_DATA) >> ((offset & 2)) & 0xFFFF;

    return return_value;
}

const char* PCIGetVendorStringForID(uint16_t vendor_id) {
    for(uint16_t i = 0; i < PCI_VENTABLE_LEN; i++) {
        if(PciVenTable[i].VenId == vendor_id) {
            return PciVenTable[i].VenFull;
        }
    }

    return "";
}

const char* PCIGetVendorShortStringForID(uint16_t vendor_id) {
    for(uint16_t i = 0; i < PCI_VENTABLE_LEN; i++) {
        if(PciVenTable[i].VenId == vendor_id) {
            return PciVenTable[i].VenShort;
        }
    }

    return "";
}

const char* PCIGetDeviceStringForID(uint16_t vendor_id, uint16_t device_id) {
    for(uint16_t i = 0; i < PCI_DEVTABLE_LEN; i++) {
		if(PciDevTable[i].VenId == vendor_id && PciDevTable[i].DevId == device_id) {
			return PciDevTable[i].Chip;
		}
	}

	return "";
}

const char* PCIGetDeviceDescriptionStringForID(uint16_t vendor_id, uint16_t device_id) {
    for(uint16_t i = 0; i < PCI_DEVTABLE_LEN; i++) {
		if(PciDevTable[i].VenId == vendor_id && PciDevTable[i].DevId == device_id) {
			return PciDevTable[i].ChipDesc;
		}
	}

	return "";
}

void SetupPCI() {
    /* Option #1: Computer doesn't support PCI (too old or far future). */
    /* Option #2: Computer supports config space address mechanism 2. */
    /* Option #3: Computer supports config space address mechanism 1 but not memory mapped access. */
    /* Option #4: Computer supports config space address mechanism 1 and memory mapped access. */
}
