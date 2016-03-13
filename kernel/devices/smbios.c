#include <arch/io.h>

#include <devices/smbios.h>
#include <terminal.h>

uint32_t* smbios_entry_point;

void SMBIOSLocateEntryPoint() {

    char *mem = (unsigned char *) 0xF0000;
    int length, i;
    uint8_t version_major, version_minor;
    unsigned char checksum;
    while ((unsigned int) mem < 0x100000) {
        if (mem[0] == '_' && mem[1] == 'S' && mem[2] == 'M' && mem[3] == '_') {
            length = mem[5];
            checksum = 0;
            for(i = 0; i < length; i++) {
                checksum += mem[i];
            }
            if(checksum == 0) break;
        }
    mem += 16;
    }

    if((int8_t) mem == 0x100000) {
        TerminalPrintString("Could not find SMBIOS!");
    }

    version_major = mem[6];
    version_minor = mem[7];
    //TerminalPrintString("Found SMBIOS version %i, %i", version_major, version_minor);

    smbios_entry_point = mem;
}

void SMBIOSParseEntryPointTable() {

}

void SetupSMBIOS() {
    SMBIOSLocateEntryPoint();
    SMBIOSParseEntryPointTable();
}
