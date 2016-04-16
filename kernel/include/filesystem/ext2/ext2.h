#ifndef __EXT2_H__
#define __EXT2_H__

#include <stdint.h>

#define EXT2_MAGIC      0xEF53

#define EXT2_SUPERBLOCK_OFFSET 1024

#define EXT2_INODE_ROOT 2
#define EXT2_INODE_BLOCK_TOTAL 12

#define EXT2_STATE_CLEAN 1
#define EXT2_STATE_ERROR 2

#define EXT2_ERROR_IGNORE 1
#define EXT2_ERROR_REMOUNT 2
#define EXT2_ERROR_PANIC 3

enum EXT2_FILE_TYPE {
    EXT2_FILE_UNKNOWN = 0,
    EXT2_FILE_REG_FILE = 1,
    EXT2_FILE_DIR = 2,
    EXT2_FILE_CHRDEV = 3,
    EXT2_FILE_BLKDEV = 4,
    EXT2_FILE_FIFO = 5,
    EXT2_FILE_SOCK = 6,
    EXT2_FILE_SYMLINK = 7
};

struct ext2_superblock {
	uint32_t inode_total;
	uint32_t block_total;
	uint32_t block_rev_total;
	uint32_t block_free_total;
	uint32_t inode_free_total;
	uint32_t block_superblock_index;
	uint32_t block_size_log;
	uint32_t frag_size_log;
	uint32_t block_per_group;
	uint32_t frag_per_group;
	uint32_t inode_per_group;
	uint32_t mount_time; //Last time in POSIX time
	uint32_t write_time; //Last time in POSIX time
	uint16_t mount_total;
	uint16_t mount_max_total;
	uint16_t magic;
	uint16_t state;
	uint16_t error;
	uint16_t ver_minor;
	uint32_t con_time;
	uint32_t con_interval;
	uint32_t osid;
	uint32_t ver_major;
	uint16_t uid;
	uint16_t gid;

	//Extended Superblock - byte 84 & >
	uint32_t inode_first;
	uint16_t inode_size;
	uint16_t block_group;
	uint32_t feature_optional;
	uint32_t feature_required;
	uint32_t feature_nosupport;
	uint8_t uuid[16];
	uint8_t vol_name[16];
	uint8_t mount_last_path[16];
	uint32_t compression;
	uint8_t block_prealloc_file;
	uint8_t block_prealloc_dir;
	uint16_t unused;
	uint8_t journal_id[16];
	uint32_t journal_inode;
	uint32_t journal_dev;
	uint32_t orphan_inode;

	uint32_t hash_seed[4];
	uint8_t hash_ver;
	uint16_t unused2;
	uint8_t unused3;

	uint32_t mount_opt;
	uint32_t meta;
	uint8_t unused4[760];
};// __attribute__ ((packed));

struct ext2_inode {
    uint16_t type;
    uint16_t uid;
    uint32_t size;
    uint32_t atime;     /* Access time. */
    uint32_t ctime;     /* Creation time. */
    uint32_t dtime;
    uint16_t gid;
};// ___attribute__ ((packed));

struct ext2_superblock* ext2GetSuperBlock(void* address);


#endif /* __EXT2_H__ */
