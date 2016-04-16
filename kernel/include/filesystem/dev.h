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
