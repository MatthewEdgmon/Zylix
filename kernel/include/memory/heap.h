#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdint.h>

typedef struct _KHEAPBLOCKBM {
    struct _KHEAPBLOCKBM    *next;
    uint32_t                size;
    uint32_t                used;
    uint32_t                bsize;
    uint32_t                lfb;
} KHEAPBLOCKBM;

typedef struct _KHEAPBM {
    KHEAPBLOCKBM            *fblock;
} KHEAPBM;

void k_heapBMInit(KHEAPBM *heap);
int k_heapBMAddBlock(KHEAPBM *heap, uintptr_t addr, uint32_t size, uint32_t bsize);
static uint8_t k_heapBMGetNID(uint8_t a, uint8_t b);
void *k_heapBMAlloc(KHEAPBM *heap, uint32_t size);
void k_heapBMFree(KHEAPBM *heap, void *ptr);

void* kmalloc(uint32_t size);
void kfree(void *ptr);

void SetupKernelHeap();

#endif /* __HEAP_H__ */
