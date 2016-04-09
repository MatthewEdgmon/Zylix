#include <stdio.h>
#include <stdint.h>

#include <process.h>

#include <elf.h>

unsigned char elf_magic_numbers[] = {
    ELFMAG0,
    ELFMAG1,
    ELFMAG2,
    ELFMAG3
};

int ELFValidateHeader(void* data) {
    elf32_ehdr* header = (elf32_ehdr*) data;
    for(int i = 0; i < 4; i++) {
        if(header->e_ident[i] != elf_magic_numbers[i]) {
            /* Invalid ELF header. */
            return 1;
        }
    }
    /* Valid ELF header. */
    return 0;
}

process_t* ELFLoad(void* elf) {
    if(ELFValidateHeader(elf)) {
        printf("Tried to load an invalid ELF file.\n");
        return (process_t*) NULL;
    }

    /* Retrieve the header. */
    elf32_ehdr* header = (elf32_ehdr*) elf;

    if(header->e_type != ET_EXEC) {
        printf("Tried to load a non-executable ELF file.\n");
        return (process_t*) NULL;
    }

    process_t* process;
    process->name = "ELF_PROGRAM";

    return process;
}

void ELFDumpInfo(void* elf) {

}
