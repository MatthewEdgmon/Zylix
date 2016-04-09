#ifndef __FILE_H__
#define __FILE_H__

#include <stdint.h>

FILE kernel_fopen(char* path, uint32_t offset);
void kernel_fclose(FILE file);
uint32_t kernel_fwrite(FILE file, uint32_t size, char* buffer);
uint32_t kernel_fread(FILE file, uint32_t size, char* buffer);

#endif /* __FILE_H__ */
