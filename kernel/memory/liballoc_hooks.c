#include <stdint.h>
#include <stdio.h>

#define PAGE_SIZE 0x1000
#define PAGE_START 0x100000
#define PAGE_MAX 0x3200000

void* current_page = PAGE_START;

int liballoc_lock() {
    //lock();
    return 0;
}

int liballoc_unlock() {
    //unlock();
    return 0;
}

void* liballoc_alloc(int pages) {
    if(current_page >= PAGE_MAX);
    unsigned int size = pages * PAGE_SIZE;
    current_page = current_page + size;
    return current_page;
}

int liballoc_free(void* ptr, int pages) {
    unsigned int size = pages * PAGE_SIZE;
    memset(ptr, NULL, size);
    return 0;
}
