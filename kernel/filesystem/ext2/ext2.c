#include <filesystem/ext2/ext2.h>
#include <filesystem/vfs.h>

struct ext2_superblock* ext2GetSuperBlock(void* address) {
    struct ext2_superblock* superblock = address + EXT2_SUPERBLOCK_OFFSET;

    if(ext2ValidateSuperBlock(superblock)) {
        return NULL;
    }

    return superblock;
}

int ext2ValidateSuperBlock(struct ext2_superblock* superblock) {
	if(superblock->magic == EXT2_MAGIC) {
		return 0;
	} else {
		return 1;
    }
}
