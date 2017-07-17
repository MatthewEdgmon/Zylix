#include <stdint.h>
#include <stdio.h>

#include <memory/manager.h>

int liballoc_lock() {
    //lock();
    return 0;
}

int liballoc_unlock() {
    //unlock();
    return 0;
}

void* liballoc_alloc(int pages) {
    return ManagerPageAllocate(pages);
}

int liballoc_free(void* ptr, int pages) {
    return ManagerPageFree(ptr, pages);
}
