#include <stdint.h>
#include <stdio.h>

#include <filesystem/ext2/ext2.h>
#include <filesystem/vfs.h>

ext2_superblock_t* ext2GetSuperBlock(uintptr_t address) {
    ext2_superblock_t* superblock = address + EXT2_SUPERBLOCK_OFFSET;

    if(ext2ValidateSuperBlock(superblock)) {
        return NULL;
    }

    return superblock;
}

int ext2ValidateSuperBlock(ext2_superblock_t* superblock) {
	if(superblock->magic == EXT2_MAGIC) {
		return 0;
	} else {
		return 1;
    }
}
