#ifndef __ELF_LOADER_H__
#define __ELF_LOADER_H__

#include <types.h>

/**
 * The definitions here are source from the
 * ELF specification version 1.2.
 */

/**
 * ELF magic number, always first 4 bytes (0-3).
 */
#define ELF_MAGIC1  0x7F
#define ELF_MAGIC2  'E'
#define ELF_MAGIC3  'L'
#define ELF_MAGIC4  'F'
#define EI_NIDENT   16

/**
 * ELF Datatypes.
 */
typedef uint32_t elf32_word;
typedef uint32_t elf32_address;
typedef uint32_t elf32_offset;
typedef uint32_t elf32_shword;
typedef uint16_t elf32_half;

typedef struct {
    unsigned char   e_ident[EI_NIDENT];
    elf32_half      e_type;
    elf32_half      e_machine;
    elf32_word      e_version;
    elf32_address   e_entry;
    elf32_offset    e_phoff;
    elf32_offset    e_shoff;
    elf32_word      e_flags;
    elf32_half      e_ehsize;
    elf32_half      e_phentsize;
    elf32_half      e_phnum;
    elf32_half      e_shentsize;
    elf32_half      e_shnum;
    elf32_half      e_shstrndx;
} elf32_header;

/**
 * elf32_type
 */
#define ET_NONE     0     /* No file type */
#define ET_REL      1     /* Relocatable file */
#define ET_EXEC     2     /* Executable file */
#define ET_DYN      3     /* Shared object file */
#define ET_CORE     4     /* Core file */
#define ET_LOPROC   0xff0 /* [Processor Specific] */
#define ET_HIPROC   0xfff /* [Processor Specific] */

/**
 * elf32_machine
 */
#define EM_NONE     0       /* No machine. */
#define EM_M32      1       /* AT&T WE 32100 */
#define EM_SPARC    2       /* SPARC */
#define EM_386      3       /* Intel Architecture */
#define EM_68K      4       /* Motorola 68000 */
#define EM_88K      5       /* Motorola 88000 */
#define EM_860      7       /* Intel 80860 */
#define EM_MIPS     8       /* MIPS RS3000 Big-Endian */
#define EM_RESERVED 11
#define EM_RESERVED 12
#define EM_RESERVED 13
#define EM_RESERVED 14
#define EM_RESERVED 15
#define EM_RESERVED 16

/**
 * elf32_version
 */
#define EV_NONE     0       /* Invalid version. */
#define EV_CURRENT  1       /* Curent version. */

typedef struct {

} elf64_header;

#endif /* __ELF_LOADER_H__ */
