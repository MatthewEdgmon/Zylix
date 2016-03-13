#include <devices/pci.h>

#include <arch/io.h>

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC

uint16_t PCIConfigReadWord(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset) {

    uint32_t configuration_address;
    uint32_t bus_long = (uint32_t) bus;
    uint32_t slot_long = (uint32_t) slot;
    uint32_t function_long = (uint32_t) function;
    uint16_t data;

    /* Build the configuration address to read. */
    configuration_address = (uint32_t)((bus_long << 16) | (slot_long << 11) | (function_long << 8) | (offset & 0xFC) | ((uint32_t) 0x80000000));

    /* Write the address. */
    outl(0xCF8, configuration_address);

    /* Read the data. */
    /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register. */
    data = (uint16_t) ((inl(PCI_CONFIG_DATA) >> ((offset & 2) * 8)) & 0xFFFF);

    return data;
}

uint16_t PCICheckVendor(uint8_t bus, uint8_t slot) {
    uint16_t vendor, device;

    /* If the vendor field reads as 0xFFFF, it indicates no device. */
    if((vendor = PCIConfigReadWord(bus, slot, 0, 0) != 0xFFFF)) {
        device = PCIConfigReadWord(bus, slot, 0, 2);
    }

    return vendor;
}
