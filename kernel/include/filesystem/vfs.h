/**
 * vfs.h -
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

#ifndef __VFS_H__
#define __VFS_H__

#include <stdint.h>
#include <stdio.h>

#include <filesystem/dev.h>

typedef struct fs_node {
    char name[256];         /* Filename. */
    char name_dos[16];      /* Short name to support DOS names. */

    uint32_t uid;           /* The owning user. */
    uint32_t gid;           /* The owning group. */
    uint32_t mask;          /* Permissions mask. */
    uint32_t size;          /* Size of the file, in bytes. */

    uint32_t access_time;   /* When was the file last accessed. */
    uint32_t modify_time;   /* When was the file last modified. */
    uint32_t create_time;   /* When was the file created. */

} fs_node_t;

extern fs_node_t* root_node;

FILE kernel_fopen(char* path, uint32_t offset);
void kernel_fclose(FILE file);
uint32_t kernel_fwrite(FILE file, uint32_t size, char* buffer);
uint32_t kernel_fread(FILE file, uint32_t size, char* buffer);

uint32_t read_fs(fs_node_t* node, uint32_t offset, uint8_t* buffer);
uint32_t write_fs(fs_node_t* node, uint32_t offset, uint8_t* buffer);

uint32_t open_fs(fs_node_t* node, uint32_t offset);
void     close_fs(fs_node_t* node);

uint8_t FSCreateFile(char* name, uint16_t permissions);

fs_node_t* VFSTouch(fs_node_t* node, char* name);
fs_node_t* VFSGetDirectory(fs_node_t* node, char* name);
fs_node_t* VFSMakeDirectory(fs_node_t* node, char* name);

void SetupVFS();

#endif /* __VFS_H__ */
