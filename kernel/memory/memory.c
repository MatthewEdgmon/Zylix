#include <stdint.h>

#include <memory/memory.h>

void pokeb(uint16_t* address, uint8_t value) {
    *((uint8_t*) address) = value;
}

void pokew(uint16_t* address, uint16_t value) {
    *((uint16_t*) address) = value;
}

void pokel(uint16_t* address, uint32_t value) {
    *((uint32_t*) address) = value;
}

uint8_t peekb(uint8_t* address) {
    return *((uint8_t*) address);
}

uint16_t peekw(uint16_t* address) {
    return *((uint16_t*) address);
}

uint32_t peekl(uint32_t* address) {
    return *((uint32_t*) address);
}
