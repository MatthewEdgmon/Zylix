#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <filesystem/vfs.h>
#include <filesystem/dev.h>

#include <memory/heap.h>

uint32_t read_fs(fs_node_t* node, uint32_t offset, uint8_t* buffer) {
    if(node->read_block != NULL) {
        return node->read_block(node, offset, buffer);
    } else {
        return 0;
    }
}

uint32_t write_fs(fs_node_t* node, uint32_t offset, uint8_t* buffer) {
    if(node->write_block != NULL) {
        return node->write_block(node, offset, buffer);
    } else {
        return 0;
    }
}

uint32_t open_fs(fs_node_t* node, uint32_t offset) {
    if(node->open != NULL) {
        return node->open(node, offset);
    } else {
        return 0;
    }
}

void close_fs(fs_node_t* node) {
    if(node->close != NULL) {
        node->close(node);
    }
}

struct dirent* readdir_fs(fs_node_t* node, uint32_t index) {
    if((node->readdir != NULL) && ((node->flags & 7) == FS_DIRECTORY)) {
		return node->readdir(node, index);
    } else {
		return (struct dirent*) NULL;
    }
}

/* Get a file from it's path. */
fs_node_t* FSPath(fs_node_t* node, char* name) {
    if(strcmp(name, "/") == 0) {
        return node;
    }

    /* Copy the string. */
    char* name_copy = (char*) kmalloc(strlen(name) + 2);
    strcpy(name_copy, name);

    /* Format the string for parsing. */
    for(uint8_t i = 0; i < strlen(name); i++) {
        if(name[i] == '/') {
            name[i] = 0;
        }
    }
/*
    do {
        node = node->holds;

        while(node != NULL) {
            if(strcmp(node->name, name) == 0) {
                break;
            }
            node = node->link;
        }

    } while((uint32_t) name < (uint32_t) end);
*/
    kfree(name_copy);
    return node;
}

void VFSListDirectory(char* path) {
    printf("Directory listing of ");
}

char* VFSGetBaseName(char* name) {
    for(int i = strlen(name); i >= 0; i--) {
        if(name[i] == '/') {
            return &name[i + 1];
        }
    }
    return name;
}

fs_node_t* VFSTouch(fs_node_t* node, char* name) {
    fs_node_t* directory = VFSGetDirectory(node, name);

    if(directory == NULL) {
        printf("VFS tried to touch a file in an invalid path.");
        return NULL;
    }

    fs_node_t* file;

    file->link = directory->holds;
    directory->holds = file;

    return file;
}

fs_node_t* VFSGetDirectory(fs_node_t* node, char* name) {
    return NULL;
}

fs_node_t* VFSMakeDirectory(fs_node_t* node, char* name) {
    fs_node_t* directory = VFSGetDirectory(node, name);

    if(directory == NULL) {
        printf("VFS tried to make an invalid path.");
        return NULL;
    }

    fs_node_t* file;

    file->link = directory->holds;
    directory->holds = file;

    return file;
}
