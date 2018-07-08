/**
 * ext2.c - EXT2 filesystem support.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdio.h>

#include <filesystem/ext2.h>
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
