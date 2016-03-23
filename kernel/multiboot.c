#include <libc/stdint.h>
#include <libc/stdio.h>
#include <libc/string.h>

#include <multiboot.h>

char* ramdisk = NULL;
struct multiboot* multiboot_ptr = NULL;

/**
 * Copies the multiboot header for safe keeping.
 */
//struct multiboot* CopyMultiboot(struct multiboot*multiboot_ptr) {
//
//}

void DumpMultiboot(struct multiboot* multiboot_ptr) {
    printf("Multiboot Header located at: 0x%x", multiboot_ptr);

}
