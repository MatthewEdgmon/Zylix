#include <stdio.h>
#include <stdint.h>

#include <filesystem/vfs.h>
#include <filesystem/dev.h>

/*
void VFSRegisterDevice(char* name, read_block_t read, write_block_t write) {
	if(fs_path(df_root, "/dev") == NULL){
		printf("Can't make device, no path for /dev\n");
		return;
	}

	char* path = (char*) kmalloc(strlen(name) + strlen("/dev/") + 2);
	strmov(path, "/dev/");
	strmov(&path[strlen("/dev/")], name);

	fs_node_t* node = vfs_touch(df_root, path);

	if(node == NULL){
		printf("couldn't resolve path\n");
		return;
	}

	node->read_blk = read;
	node->write_blk = write;

	node->dev = (dev_t*) kmalloc(sizeof(dev_t));
	node->dev->read = read;
	node->dev->write = write;
	node->dev->block_size = 512;
}

uint32_t VFSDeviceRead(fs_node_t* device, uint32_t offset, char* buffer){
	if(device->read_blk == NULL){
		printf("can't read from device\n");
		return 1;
	}

	return dev->read_blk(dev, offset, buffer);
}


uint32_t VFSDeviceWrite(fs_node_t* device, uint32_t offset, char* buffer){
	if(device->write_blk == NULL){
		printf("can't write to device\n");
		return 1;
	}

	return device->write_blk(dev, offset, buffer);
}
*/
