/**
 * elf.c - ELF process image handling/creation.
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

#include <stdio.h>
#include <stdint.h>

#include <tasking/elf.h>

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

// process_t* ELFLoad(void* elf) {
//
//     if(ELFValidateHeader(elf)) {
//         printf("Tried to load an invalid ELF file.\n");
//         return (process_t*) NULL;
//     }
//
//     /* Retrieve the header. */
//     elf32_ehdr* header = (elf32_ehdr*) elf;
//
//     if(header->e_type != ET_EXEC) {
//         printf("Tried to load a non-executable ELF file.\n");
//         return (process_t*) NULL;
//     }
//
//     process_t* process;
//     process->name = "ELF_PROGRAM";
//
//     return process;
// }
