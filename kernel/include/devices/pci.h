#ifndef __PCI_H__
#define __PCI_H__

#include <stdint.h>

/* Ports associated with PCI. */
#define PCI_CONFIG_ADDRESS             0xCF8
#define PCI_CONFIG_DATA                0xCFC

const char* PCIGetVendorStringForID(uint16_t vendor_id);
const char* PCIGetVendorShortStringForID(uint16_t vendor_id);
const char* PCIGetDeviceStringForID(uint16_t vendor_id, uint16_t device_id);
const char* PCIGetDeviceDescriptionStringForID(uint16_t vendor_id, uint16_t device_id);

void SetupPCI();

#endif /* __PCI_H__ */
