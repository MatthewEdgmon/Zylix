#include <stdio.h>

#include <filesystem/vfs.h>
#include <filesystem/dev.h>

void RegisterDevice(char* name, read_block_t read, write_block_t write) {
    fs_node_t* node;
    //fs_node_t* node = VFSTouch(df_root, path);

    if(node == NULL){
		printf("ERROR! Couldn't resolve path for device: %s\n", name);
		return;
	}

    node->read_block = read;
    node->write_block = write;

    node->dev->read = read;
    node->dev->write = write;
    node->dev->block_size = 512;
}

uint32_t dev_read(fs_node_t* dev, uint32_t offset, char* buffer) {
    if(dev->read_block == NULL){
		printf("ERROR! Can't read device: %s\n", dev->name);
		return 1;
	}
    return dev->read_block(dev, offset, buffer);
}

uint32_t dev_write(fs_node_t* dev, uint32_t offset, char* buffer) {
    if(dev->write_block == NULL){
		printf("ERROR! Can't write device: %s\n", dev->name);
		return 1;
	}
    return dev->write_block(dev, offset, buffer);
}
