#ifndef __MEMORY_H__
#define __MEMORY_H__

void pokeb(uint16_t* address, uint8_t value);
void pokew(uint16_t* address, uint16_t value);
void pokel(uint16_t* address, uint32_t value);
uint8_t peekb(uint8_t* address);
uint16_t peekw(uint16_t* address);
uint32_t peekl(uint32_t* address);

#endif /* __MEMORY_H__ */
