#include <stdint.h>

#include <memory/paging.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t page_table1[1024] __attribute__((aligned(4096)));

extern void PagingLoadDirectory(uint32_t*);
extern void PagingEnable();

void SetupPaging() {
    /* Set each entry to not present. */
    for(int i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002;
    }
}
