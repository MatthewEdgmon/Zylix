/**
 * ELF Loader.
 */
#include <execute.h>

#include <common.h>
#include <libc/stdint.h>

#include <terminal.h>

/* Executable types. */
#include <elf.h>

/**
 * Execute an elf binary.
 */
int ExecuteELF() {
    Elf32_Ehdr *hdr;

    /* Read the file from memory. */
    /* Process the header. */

    /* Determine if it's a valid ELF, else return. */
    if(hdr->e_ident[EI_MAG0] != ELFMAG0) {
        return -1;
    }
    if(hdr->e_ident[EI_MAG1] != ELFMAG1) {
        return -1;
    }
    if(hdr->e_ident[EI_MAG2] != ELFMAG2) {
        return -1;
    }
    if(hdr->e_ident[EI_MAG3] != ELFMAG3) {
        return -1;
    }

    if(hdr->e_ident[EI_CLASS] != ELFCLASS32) {
        return -1;
    }
    if(hdr->e_ident[EI_DATA] != ELFDATA2LSB) {
        return -1;
    }

    /* Allocate memory for the program. */
    /* Place it's code at the entry point. */
    /* Close the file. */
    /* Fork to new PID. */
    /* Get the return code and return that to Execute() */
    return 0;
}

/**
 * Execute a script shebang.
 */
int ExecuteShebang() {
    /* Get the return code and return that to Execute() */
    return 0;
}

/**
 * Execute something.
 */
int Execute() {
    /* Determine file type. */
    /* Execute it. */
    return 0;
}