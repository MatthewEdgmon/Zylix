/* Adapted from http://www.gnu.org/software/grub/manual/multiboot/html_node/multiboot_002eh.html#multiboot_002eh */

#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__

#define MULTIBOOT_HEADER_MAGIC         0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC     0x2BADB002
#define MULTIBOOT_FLAG_MEM             0x001
#define MULTIBOOT_FLAG_DEVICE          0x002
#define MULTIBOOT_FLAG_CMDLINE         0x004
#define MULTIBOOT_FLAG_MODS            0x008
#define MULTIBOOT_FLAG_AOUT            0x010
#define MULTIBOOT_FLAG_ELF             0x020
#define MULTIBOOT_FLAG_MMAP            0x040
#define MULTIBOOT_FLAG_CONFIG          0x080
#define MULTIBOOT_FLAG_LOADER          0x100
#define MULTIBOOT_FLAG_APM             0x200
#define MULTIBOOT_FLAG_VBE             0x400

#define MULTIBOOT_MEMORY_AVAILABLE     1
#define MULTIBOOT_MEMORY_RESERVED      2

typedef struct multiboot_header {
	uint32_t magic;			/* Must be set to MULTIBOOT_MAGIC. */
	uint32_t flags;			/* Feature flags. */
	uint32_t checksum;		/* The above fields plus this one must equal 0 mod 2^32. */
	/* The following is valid if MULTIBOOT_AOUT_KLUDGE is set. */
	uint32_t header_addr;
	uint32_t load_addr;
	uint32_t load_end_addr;
	uint32_t bss_end_addr;
	uint32_t entry_addr;
	/* The following is valid if MULTIBOOT_VIDEO_MODE is set. */
	uint32_t mode_type;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
} __attribute__ ((packed)) multiboot_header_t;

typedef struct multiboot_aout_symbol_table {
    uint32_t tabsize;
	uint32_t strsize;
	uint32_t addr;
	uint32_t reserved
} __attribute__ ((packed)) multiboot_aout_symbol_table_t;

typedef struct multiboot_elf_section_header_table {
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
} __attribute__ ((packed)) multiboot_elf_section_header_table_t;

typedef struct multiboot_info {
	uintptr_t flags;
	uintptr_t mem_lower;
	uintptr_t mem_upper;
	uintptr_t boot_device;
	uintptr_t cmdline;
	uintptr_t mods_count;
	uintptr_t mods_addr;
	union {
		multiboot_aout_symbol_table_t aout_sym;
		multiboot_elf_section_header_table_t elf_sec;
	} u;
	uintptr_t mmap_length;
	uintptr_t mmap_addr;
	uintptr_t drives_length;
	uintptr_t drives_addr;
	uintptr_t config_table;
	uintptr_t boot_loader_name;
	uintptr_t apm_table;
	uintptr_t vbe_control_info;
	uintptr_t vbe_mode_info;
	uintptr_t vbe_mode;
	uintptr_t vbe_interface_seg;
	uintptr_t vbe_interface_off;
	uintptr_t vbe_interface_len;
} __attribute__ ((packed)) multiboot_info_t;

typedef struct multiboot_vbe_info {
	uint16_t attributes;
	uint8_t  winA, winB;
	uint16_t granularity;
	uint16_t winsize;
	uint16_t segmentA, segmentB;
	uint32_t realFctPtr;
	uint16_t pitch;

	uint16_t Xres, Yres;
	uint8_t  Wchar, Ychar, planes, bpp, banks;
	uint8_t  memory_model, bank_size, image_pages;
	uint8_t  reserved0;

	uint8_t  red_mask, red_position;
	uint8_t  green_mask, green_position;
	uint8_t  blue_mask, blue_position;
	uint8_t  rsv_mask, rsv_position;
	uint8_t  directcolor_attributes;

	uint32_t physbase;
	uint32_t reserved1;
	uint16_t reserved2;
} __attribute__ ((packed)) multiboot_vbe_info_t;

typedef struct multiboot_module {
	uint32_t mod_start;		/* Address of the module. */
	uint32_t mod_end;		/* Memory used goes from bytes 'mod_start' to 'mod_end-1' inclusive. */
	uint32_t cmdline;		/* Module command line. */
	uint32_t reserved;		/* Padding to take it to 16 bytes. */
} __attribute__ ((packed)) multiboot_module_t;

typedef struct multiboot_memory_map {
	uint32_t size;
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
} __attribute__ ((packed)) multiboot_memory_map_t;

extern multiboot_info_t* MultibootCopy(multiboot_info_t* multiboot_info);
extern void MultibootDumpInfo(multiboot_info_t* multiboot_info);
extern char* ramdisk;
extern struct multiboot* mboot_ptr;

#endif /* __MULTIBOOT_H__ */
