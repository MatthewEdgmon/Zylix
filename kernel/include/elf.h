/**
 * Information for decoding and processing ELF header files.
 */
#ifndef __ELF_LOADER_H__
#define __ELF_LOADER_H__

#include <libc/stdint.h>

/**
 * The definitions here are source from the
 * ELF specification version 1.2. Variable names
 * and methods are kept the same for cross reference.
 */

/**
 * ELF Datatypes.
 */
typedef uint32_t Elf32_Word;           /* 4 bytes, 4 aligned, unsigned large integer. */
typedef uint32_t Elf32_Addr;           /* 4 bytes, 4 aligned, unsigned program address. */
typedef uint32_t Elf32_Off;            /* 4 bytes, 4 aligned, unsigned file offset. */
typedef uint32_t Elf32_Sword;          /* 4 bytes, 4 aligned, signed large integer. */
typedef uint16_t Elf32_Half;           /* 2 bytes, 2 aligned, unsigned medium integer. */

#define EI_NIDENT   16

/**
 * ELF Header
 */
typedef struct {
    unsigned char e_ident[EI_NIDENT];  /* Identify this as an ELF file. */
    Elf32_Half    e_type;              /* Object file type. */
    Elf32_Half    e_machine;           /* Architecture the file runs on. */
    Elf32_Word    e_version;           /* Object file version. */
    Elf32_Addr    e_entry;             /* Address where control is transfered to. 0 if not executable. */
    Elf32_Off     e_phoff;             /* Program Header Table's file offset in bytes. 0 if none. */
    Elf32_Off     e_shoff;             /* Section Header Table's file offset in bytes. 0 if none. */
    Elf32_Word    e_flags;             /* Processor specific flags. */
    Elf32_Half    e_ehsize;            /* ELF header size in bytes. */
    Elf32_Half    e_phentsize;         /* Size in bytes of one entry in the file's program header table, all are same size. */
    Elf32_Half    e_phnum;             /* Number of entries in the program header table. */
    Elf32_Half    e_shentsize;         /* Size in bytes of one entry in the file's section header table, all are same size. */
    Elf32_Half    e_shnum;             /* Number of entries in the section header table. */
    Elf32_Half    e_shstrndx;          /* Section Header Table index of the entry associated with the section name string table. */
} Elf32_Ehdr;

/**
 * e_ident index.
 */
#define EI_MAG0      0                 /* File identification. */
#define EI_MAG1      1                 /* File identification. */
#define EI_MAG2      2                 /* File identification. */
#define EI_MAG3      3                 /* File identification. */
#define EI_CLASS     4                 /* File class. */
#define EI_DATA      5                 /* Data encoding. */
#define EI_VERSION   6                 /* File version. */
#define EI_PAD       7                 /* Start of padding bytes. */
#define EI_NIDENT    16                /* Size of e_ident[] */

/**
 * e_ident values.
 */
#define ELFMAG0      0x7F              /* Identification magic value. */
#define ELFMAG1      'E'               /* Identification magic value. */
#define ELFMAG2      'L'               /* Identification magic value. */
#define ELFMAG3      'F'               /* Identification magic value. */
#define ELFCLASSNONE 0                 /* Invalid class. */   
#define ELFCLASS32   1                 /* 32-bit object file. */      
#define ELFCLASS64   2                 /* 64-bit object file. */
#define ELFDATANONE  0                 /* Invalid encoding. */
#define ELFDATA2LSB  1                 /* Least significant bit encoding. I.e. 0x01020304 = 04 03 02 01 */
#define ELFDATA2MSB  2                 /* Most significant bit encoding. I.e. 0x01020304 = 01 02 03 04 */

/**
 * e_type values.
 */
#define ET_NONE     0                  /* No file type */
#define ET_REL      1                  /* Relocatable file */
#define ET_EXEC     2                  /* Executable file */
#define ET_DYN      3                  /* Shared object file */
#define ET_CORE     4                  /* Core file */
#define ET_LOPROC   0xff0              /* [Processor Specific] */
#define ET_HIPROC   0xfff              /* [Processor Specific] */

/**
 * e_machine values.
 */
#define EM_NONE     0                  /* No machine. */
#define EM_M32      1                  /* AT&T WE 32100 */
#define EM_SPARC    2                  /* SPARC */
#define EM_386      3                  /* Intel Architecture */
#define EM_68K      4                  /* Motorola 68000 */
#define EM_88K      5                  /* Motorola 88000 */
#define EM_860      7                  /* Intel 80860 */
#define EM_MIPS     8                  /* MIPS RS3000 Big-Endian */

/**
 * e_version values.
 */
#define EV_NONE     0                  /* Invalid version. */
#define EV_CURRENT  1                  /* Curent version. */

/**
 * Special Section Indexes
 */
#define SHN_UNDEF     0                /* Marks an undefined, missing or meaningless section reference. */
#define SHN_LORESERVE 0xff00           /* This value specifies the lower bound of the range of reserved indexes. */
#define SHN_LOPROC    0xff00           /* Values between this and SHN_HIPROC are reserved for processor-specific semantics. */
#define SHN_HIPROC    0xff1f           /* Values between this and SHN_LOPROC are reserved for processor-specific semantics. */
#define SHN_ABS       0xfff1           /* This value specifies absolute values for the corresponding reference. */
#define SHN_COMMON    0xfff2           /* Sections defined relative to this section are common symbols. I.e. FORTRAN COMMON or C external. */
#define SHN_HIRESERVE 0xffff           /* This value specifies the upper bound of the range of reserved indexes. */

/**
 * ELF Section Header
 */
typedef struct {
    Elf32_Word    sh_name;
    Elf32_Word    sh_type;             /* Categorizes the section's contents and semantics. */
    Elf32_Word    sh_flags;
    Elf32_Addr    sh_addr;             /* If the section will appear in memory, this is the address the first byte resides. */
    Elf32_Off     sh_offset;
    Elf32_Word    sh_size;
    Elf32_Word    sh_link;
    Elf32_Word    sh_info;
    Elf32_Word    sh_addralign;
    Elf32_Word    sh_entsize;          /* If this section has a table of fixed size entries, size of bytes in each entry. 0 if none. */
} Elf32_Shdr;

/**
 * sh_type values.
 */
#define SHT_NULL      0                /* Marks the section header as inactive. Other members are undefined. */
#define SHT_PROGBITS  1                /* Section holding information defined by the program, for the program. */
#define SHT_SYMTAB    2                /* This section holds a symbol table. */
#define SHT_STRTAB    3                /* This section holds a string table. */
#define SHT_RELA      4                /* This section holds relocation entires with excplicit addends. */
#define SHT_HASH      5                /* This section holds a symbol hash table. */
#define SHT_DYNAMIC   6                /* This section holds information for dynamic linking. */
#define SHT_NOTE      7                /* This section marks the file in some way. */
#define SHT_NOBITS    8                /* This section occupies no space in the file, but resembles SHT_PROGBITS. */
#define SHT_REL       9                /* This section holds relaction entries without explicit addends. */
#define SHT_SHLIB     10               /* This section type is reserved but has unspecified semantics. */
#define SHT_DYNSYM    11               /* This section holds a symbol table. */
#define SHT_LOPROC    0x70000000       /* Values between this and SHT_HIPROC are reserved for processor-specific semantics. */
#define SHT_HIPROC    0x7fffffff       /* Values between this and SHT_LOPROC are reserved for processor-specific semantics. */
#define SHT_LOUSER    0x80000000       /* The lower bound of range of indexes reserved for application programs. */
#define SHT_HIUSER    0xffffffff       /* The upper bound of range of indexes reserved for application programs. */

/**
 * Symbol Table
 */
typedef struct {
    Elf32_Word st_name;                /* This member holds and index into the object file's symbol string table. */
    Elf32_Addr st_value;               /* This member gives the value of the associated symbol. May be an address, absolute value, etc. */
    Elf32_Word st_size;                /* Size in bytes of different associated tpyes. May be 0 for none or unknown. */
    unsigned char st_info;             /* This member specifies the symbol's type and binding attributes. */
    unsigned char st_other;            /* This member currently holds 0 and has no defined meaning. */
    Elf32_Half st_shndx;               /* Every symbol table is defined in relation to some section. This holds the relevent section header table index. Some have special meanings. */
} Elf32_Sym;

/**
 * Symbol Table binding and type manipulation and definitions.
 */

/* Macros. */
#define ELF32_ST_BIND(i)    ((i) >> 4)
#define ELF32_ST_TYPE(i)    ((i) &  0xf)
#define ELF32_ST_INFO(b, t) ((b) << 4) + ((t) & 0xf)

/* Symbol bindings. */
#define STB_LOCAL     0                /* Local symbols are not visible outside the object file containing their definition. */
#define STB_GLOBAL    1                /* Glocal symbols are visible to all object files being combined. */
#define STB_WEAK      2                /* Weak symbols resemble global symbols, but their definitions have lower precedence. */
#define STB_LOPROC    13               /* Values between this and STB_HIPROC are reserved for processor-specific semantics. */
#define STB_HIPROC    15               /* Values between this and STB_LOPROC are reserved for processor-specific semantics. */

/* Symbol types. */
#define STT_NOTYPE    0                /* The symbol's type is not specified. */
#define STT_OBJECT    1                /* The symbol is associated with a data object, such as a variable, an array, etc. */
#define STT_FUNC      2                /* The symbol is associated with a function or other executable code. */
#define STT_SECTION   3                /* The symbol is associated with a section. Primarily used for relocation and have an STB_LOCAL binding. */
#define STT_FILE      4                /* A file symbol has an STB_LOCAL binding, it's section index is SHN_ABS and ir precedes all other STB_LOCAL symbols. */
#define STT_LOPROC    13               /* Values between this and STT_HIPROC are reserved for processor-specific semantics. */
#define STT_HIPROC    15               /* Values between this and STT_LOPROC are reserved for processor-specific semantics. */

/**
 * Relocation Table.
 */
typedef struct {
    Elf32_Addr  r_offset;              /* This member gives the location at which to apply the relocation action. */
    Elf32_Word  r_info;                /* This member gives both the relocation type and symbol table index to be relocated. */
} Elf32_Rel;

/**
 * Relocation Table with addends.
 */
typedef struct {
    Elf32_Addr  r_offset;              /* This member gives the location at which to apply the relocation action. */
    Elf32_Word  r_info;                /* This member gives both the relocation type and symbol table index to be relocated. */
    Elf32_Sword r_addend;              /* This member specifies a constant addend used to compute the value to be stored in the relocatable field. */
} Elf32_Rela;

#define ELF32_R_SYM(i)     ((i) >> 8)
#define ELF32_R_TYE(i)     ((unsigned char)(i)) 
#define ELF32_R_INFO(s, t) (((s) << 8) + (unsigned char)(t))

/**
 * ELF Program Header.
 */
typedef struct {
    Elf32_Word    p_type;              /* How to interpret the array element's information. */
    Elf32_Off     p_offset;            /* The offset from the beginning of the file where the first byte of the segment resides. */
    Elf32_Addr    p_vaddr;             /* The virtual address at which the first byte of the segment resides. */
    Elf32_Addr    p_paddr;             /* The segment's physical address. */
    Elf32_Word    p_filesz;            /* Number of bytes in the file image of the segment. May be zero. */
    Elf32_Word    p_memsz;             /* Number of bytes in the memory image of the segment. May be zero. */
    Elf32_Word    p_flags;             /* Flags relevent to the segment. */
    Elf32_Word    p_align;             /* The value to which the segments are aligned in memory and file. 0 or 1 mean none. */
} Elf32_Phdr;

/**
 * p_type values.
 */
#define PT_NULL       0                /* The array element is unused. Other values are undefined. */
#define PT_LOAD       1                /* The array element specifies a loadable segment. */
#define PT_DYNAMIC    2                /* The array element specifies dynamic linking information. */
#define PT_INTERP     3                /* The array element specifies the location and size of null terminated path to an interpreter. */
#define PT_NOTE       4                /* The array element specifies the location and size of auxiliary information. */
#define PT_SHLIB      5                /* This segment type is reserved but has unspecified semantics. */
#define PT_PHDR       6                /* The array element specifies the location and size of the program header table. */
#define PT_LOPROC     0x70000000       /* Values between this and PT_HIPROC are reserved for processor-specific semantics. */
#define PT_HIPROC     0x7fffffff       /* Values between this and PT_LOPROC are reserved for processor-specific semantics. */

#endif /* __ELF_LOADER_H__ */
