/**
 * WARNING: Incoming terrible test memory allocator.
 */

#include <stdint.h>

#include <types.h>

#define MALLOC_MAGIC	0xDEADD00D

/**
 * General use malloc
 */
void* malloc(size_t size) {

	if(size == 0) {
		return NULL;
	}

	return NULL;
}

