#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <filesystem/vfs.h>
#include <filesystem/dev.h>

#include <memory/liballoc.h>

#include <structures/list.h>
#include <structures/tree.h>

tree_t*     fs_tree = NULL; /* Mountpoint tree. */
fs_node_t*  fs_root = NULL; /* Pointer to the root of the filesystem. */

FILE kernel_fopen(char* path, uint32_t offset) {
	return NULL;
}

uint32_t kernel_fwrite(FILE file, uint32_t size, char* buffer) {
	return NULL;
}

uint32_t kernel_fread(FILE file, uint32_t size, char* buffer) {
	return NULL;
}

uint32_t kernel_freadch(FILE file, char* c) {
	return NULL;
}

void kernel_fflush(FILE file) {

}

uint32_t FSRead(fs_node_t* node, uint32_t offset, uint32_t size, uint8_t* buffer) {
	return NULL;
}

/**
 * Open a file system node.
 */
void FSOpen(fs_node_t* node, uint32_t flags) {

}

/**
 * Close a file system node.
 */
void FSClose(fs_node_t* node) {

}

/**
 * Finds a file with name and returns a fs_node_t to it.
 */
fs_node_t* FSFindInDirectory(fs_node_t* directory_node, char* name) {
	if(directory_node == NULL) {
		printf("Tried to find in a non-existant directory.\n");
		return NULL;
	}

	return NULL;
}

uint8_t FSCreateFile(char* name, uint16_t permissions) {

}

fs_node_t* VFSTouch(fs_node_t* node, char* name) {
	return NULL;
}

fs_node_t* VFSListDirectory(char* path) {
	return NULL;
}

fs_node_t* VFSGetDirectory(fs_node_t* node, char* name) {
	return NULL;
}

fs_node_t* VFSMakeDirectory(fs_node_t* node, char* name) {
	return NULL;
}

void SetupVFS() {
	fs_tree = TreeCreate();
}
