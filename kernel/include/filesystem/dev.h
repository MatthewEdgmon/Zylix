/**
 * dev.h -
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

#ifndef __DEV_H__
#define __DEV_H__

#include <stdint.h>
#include <stddef.h>

struct dev;
typedef struct fs_node fs_node_t;

typedef uint32_t (*read_block_t)     (fs_node_t*, uint32_t, uint8_t*);
typedef uint32_t (*write_block_t)    (fs_node_t*, uint32_t, uint8_t*);

typedef struct dev {
    uint8_t   name[128];
    size_t    block_size;
    read_block_t read;
    write_block_t write;
    uint8_t   bus;
    uint8_t   drive;
} dev_t;

void VFSRegisterDevice(char* name, read_block_t read, write_block_t write);

uint32_t VFSDeviceRead(fs_node_t* dev, uint32_t offset, char* buffer);
uint32_t VFSDeviceWrite(fs_node_t* dev, uint32_t offset, char* buffer);

#endif /* __DEV_H__ */
