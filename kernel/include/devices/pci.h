#ifndef __PCI_H__
#define __PCI_H__

#include <arch/io.h>

uint16_t PCIConfigReadWord(uint8_t bus, uint8_t slot, uint8_t function, uint8_t offset);
uint16_t PCICheckVendor(uint8_t bus, uint8_t slot);

#endif /* __PCI_H__ */
