#ifndef __KMALLOC_H__
#define __KMALLOC_H__

#include <stdint.h>
#include <stddef.h>

void* __attribute__ ((malloc)) kmalloc(size_t size);
void  kfree(void* address);

#endif /* __KMALLOC_H__ */
