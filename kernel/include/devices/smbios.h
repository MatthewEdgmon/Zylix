#ifndef __SMBIOS_H__
#define __SMBIOS_H__

#define SMBIOS_SEARCH_START            0x000F0000
#define SMBIOS_SEARCH_END              0x000FFFFF

#define SMBIOS_HEADER_BIOS             0
#define SMBIOS_HEADER_SYSTEM           1
#define SMBIOS_HEADER_MAINBOARD        2
#define SMBIOS_HEADER_ENCLOSURE        3
#define SMBIOS_HEADER_PROCESSOR        4
#define SMBIOS_HEADER_CACHE            7
#define SMBIOS_HEADER_MEMORY_MAPPED_DEVICE_MAPPED_ADDRESS
#define SMBIOS_HEADER_SYSTEM_BOOT      32
#define SMBIOS_HEADER_FINAL            127

struct SMBIOSEntryPoint {
    int8_t entry_point_string[4];      /* This "_SM_" */
    uint8_t checksum;
    uint8_t length;
    uint8_t major_version;
    uint8_t minor_version;
    uint8_t max_structure_size;
    uint8_t entry_point_revision;
    int8_t formatted_area[5];
    int8_t entry_point_string2[5];     /* This "_DMI_" */
};

struct SMBIOSHeader {
    uint8_t type;
    uint8_t length;
    uint8_t handle;
};

void SetupSMBIOS();

#endif /* __SMBIOS_H__ */
