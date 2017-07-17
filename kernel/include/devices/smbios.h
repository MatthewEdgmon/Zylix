#ifndef __SMBIOS_H__
#define __SMBIOS_H__

#define SMBIOS_SEARCH_START            0xF0000
#define SMBIOS_SEARCH_END              0x100000

#define SMBIOS_HEADER_BIOS             0
#define SMBIOS_HEADER_SYSTEM           1
#define SMBIOS_HEADER_MAINBOARD        2
#define SMBIOS_HEADER_ENCLOSURE        3
#define SMBIOS_HEADER_PROCESSOR        4
#define SMBIOS_HEADER_CACHE            7
#define SMBIOS_HEADER_PORT_CONNECTOR   8
#define SMBIOS_HEADER_SYSTEM_SLOTS     9
#define SMBIOS_HEADER_
#define SMBIOS_HEADER_OEM_STRINGS      11
#define SMBIOS_HEADER_MEMORY_MAPPED_DEVICE_MAPPED_ADDRESS
#define SMBIOS_HEADER_PORTABLE_BATTERY 22
#define SMBIOS_HEADER_VOLTAGE_PROBE    26
#define SMBIOS_HEADER_COOLING_DEVICE   27
#define SMBIOS_HEADER_TEMPERATURE_PROBE 28
#define SMBIOS_HEADER_SYSTEM_BOOT      32
#define SMBIOS_HEADER_INACTIVE         126
#define SMBIOS_HEADER_FINAL            127

typedef struct smbios_entry_point {
    char    entry_point_string[4];      /* This is "_SM_" */
    uint8_t checksum;                   /* This value added to all other values equals 0 via overflow. */
    uint8_t length;                     /* Length of the table, since spec 2.1 it's 0x1F */
    uint8_t major_version;
    uint8_t minor_version;
    uint8_t max_structure_size;
    uint8_t entry_point_revision;
    char    formatted_area[5];
    char    entry_point_string2[5];     /* This is "_DMI_" */
    uint8_t checksum2;
    uint16_t table_length;
    uint32_t table_address;             /* This is the address of the table. */
    uint16_t number_of_structures;
    uint8_t bcd_revision;
} smbios_entry_point_t;

/**
 * 4 byte long header.
 */
typedef struct smbios_header {
    uint8_t type;
    uint8_t length;
    uint16_t handle;
} smbios_header_t;

void SMBIOSLocateEntryPoint();
void SMBIOSParseEntryPointTable();
void SMBIOSParseHeader(smbios_header_t* header);

void SMBIOSDumpInfo();

void SetupSMBIOS();

#endif /* __SMBIOS_H__ */
