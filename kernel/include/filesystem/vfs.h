#ifndef __VFS_H__
#define __VFS_H__

#include <stdint.h>

#include <filesystem/dev.h>

#define FS_FILE         1
#define FS_DIRECTORY	2
#define FS_CHARDEVICE	3
#define FS_BLOCKDEVICE	4
#define FS_PIPE		    5
#define FS_SYMLINK	    6
#define FS_MOUNTPOINT	8

struct fs_node;

typedef uint32_t (*read_type_t)    (struct fs_node*, uint32_t, uint32_t, char*);
typedef uint32_t (*write_type_t)   (struct fs_node*, uint32_t, uint32_t, char*);
typedef uint32_t (*open_type_t)    (struct fs_node*, uint32_t);
typedef void     (*close_type_t)   (struct fs_node*);

typedef struct dirent*  (*readdir_type_t) (struct fs_node*, uint32_t);
typedef struct fs_node* (*finddir_type_t) (struct fs_node*, uint8_t* name);

typedef struct fs_node {
    char name[128];
    uint8_t permissions;

    uint8_t uid;
    uint8_t gid;
    uint8_t flags;

    char dos_name[16];

    uint8_t inode;
    uint8_t length;

    dev_t* dev;

    open_type_t open;
    close_type_t close;

    read_block_t read_block;
    write_block_t write_block;

    readdir_type_t readdir;
    finddir_type_t finddir;

    struct fs_node* holds;
    struct fs_node* link;
} fs_node_t;

struct dirent {
    char name[128];
    uint8_t ino;
};

struct stat {
	uint32_t st_dev;
	uint32_t st_ino;
	uint32_t st_mode;
	uint32_t st_nlink;
	uint32_t st_uid;
	uint32_t st_gid;
	uint32_t st_rdev;
	uint32_t st_size;
	uint32_t st_atime;
	uint32_t st_mtime;
	uint32_t st_ctime;
	uint32_t st_blksize;
	uint32_t st_blocks;
};

uint32_t read_fs(fs_node_t* node, uint32_t offset, uint8_t* buffer);
uint32_t write_fs(fs_node_t* node, uint32_t offset, uint8_t* buffer);

uint32_t open_fs(fs_node_t* node, uint32_t offset);
void     close_fs(fs_node_t* node);

fs_node_t* VFSTouch(fs_node_t* node, char* name);
fs_node_t* VFSGetDirectory(fs_node_t* node, char* name);
fs_node_t* VFSMakeDirectory(fs_node_t* node, char* name);

#endif /* __VFS_H__ */
