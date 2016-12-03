#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <memory/liballoc.h>

#include <common.h>
#include <multiboot.h>
#include <panic.h>

char* ramdisk = NULL;
multiboot_info_t* multiboot_info_ptr = NULL;

multiboot_info_t* MultibootCopy(multiboot_info_t* multiboot_info) {
    struct multiboot* new_info = (multiboot_info_t*) malloc(sizeof(struct multiboot_info));
    memcpy(new_info, multiboot_info, sizeof(struct multiboot_info));
    return new_info;
}

void MultibootDumpInfo(multiboot_info_t* multiboot_info) {
    printf("Multiboot Information:\n");
    printf("    Flags: 0x%X\n", multiboot_info->flags);
    printf("    Bootloader: %s\n", multiboot_info->boot_loader_name);
    if(BIT_CHECK(multiboot_info->flags, 0)) {
        printf("    Lower memory: %uKB\n", multiboot_info->mem_lower);
        uint32_t mem_upper_mb = multiboot_info->mem_upper / 1024;
        printf("    Upper memory: %uKB (%uMB)\n", multiboot_info->mem_upper, mem_upper_mb);
    }
    if(BIT_CHECK(multiboot_info->flags, 1)) {
        printf("    Boot device: 0x%X\n", multiboot_info->boot_device);
    }
    if(BIT_CHECK(multiboot_info->flags, 2)) {
        printf("    Command line: %s\n", multiboot_info->cmdline);
    }
    if(BIT_CHECK(multiboot_info->flags, 3)) {
        printf("    Module Information:\n");
        printf("        Count: %d\n", multiboot_info->mods_count);
        printf("        Modules start at: 0x%X\n", multiboot_info->mods_addr);
        multiboot_module_t* module = (multiboot_module_t*) multiboot_info->mods_addr;
        for(size_t i = 0; i < multiboot_info->mods_count; i++) {
            printf("        Module #%d, Start: 0x%X, End: 0x%X, Cmdline: %s\n", i, module->mod_start, module->mod_end, module->cmdline);
            module++;
        }
    }
    if(BIT_CHECK(multiboot_info->flags, 4) && BIT_CHECK(multiboot_info->flags, 5)) {
        KernelPanic("Invalid Mutliboot flags! Bits 4 and 5 both set.\n", NULL);
    }
    if(BIT_CHECK(multiboot_info->flags, 4)) {
        multiboot_aout_symbol_table_t* aout_symbol_table = &(multiboot_info->u.aout_sym);
    }
    if(BIT_CHECK(multiboot_info->flags, 5)) {
        multiboot_elf_section_header_table_t* elf_header = &(multiboot_info->u.elf_sec);
    }
    if(BIT_CHECK(multiboot_info->flags, 6)) {
        printf("    Memory Map Information:\n");
        printf("        Map address: 0x%X\n", multiboot_info->mmap_addr);
        printf("        Map length: 0x%X\n", multiboot_info->mmap_length);
        multiboot_memory_map_t* memory_map = (multiboot_memory_map_t*) multiboot_info->mmap_addr;
        for(; memory_map < multiboot_info->mmap_addr + multiboot_info->mmap_length;
              memory_map = (multiboot_memory_map_t*) ((uint32_t) memory_map + memory_map->size + sizeof(memory_map->size))) {
            printf("        Size: 0x%X, Base Address: 0x%X%X, Length: 0x%X%X, Type: 0x%X\n",
                   memory_map->size,
                   memory_map->base_addr >> 32, memory_map->base_addr & 0xFFFFFFFF,
                   memory_map->length >> 32, memory_map->length & 0xFFFFFFFF,
                   memory_map->type);
        }
    }
}
