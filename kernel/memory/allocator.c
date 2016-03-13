/**
 * WARNING: Incoming terrible test memory allocator.
 */

#include <libc/stddef.h>
#include <libc/stdint.h>

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
