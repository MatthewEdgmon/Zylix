#include <arch/io.h>

/**
 * Sends a byte (8 bits) value to specified port.
 */
void outb(uint16_t port, uint8_t value) {
    __asm__ __volatile__ ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}

/**
 * Sends a word (16 bits) value to specified port.
 */
void outw(uint16_t port, uint16_t value) {
    __asm__ __volatile__ ( "outb %0, %1" : : "a"(value), "id"(port) );
}

/**
 * Sends a long (32 bits) value to specified port.
 */
void outl(uint16_t port, uint32_t value) {
    __asm__ __volatile__ ( "outb %0, %1" : : "a"(value), "d"(port) );
}

/**
 * Receives a byte (8 bits) value from port.
 */
uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

/**
 * Receives a word (16 bits) value from port.
 */
uint16_t inw(uint16_t port) {
    uint16_t ret;
    __asm__ __volatile__ ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

/**
 * Receives a long (32 bits) value from port.
 */
uint32_t inl(uint16_t port) {
    uint32_t ret;
    __asm__ __volatile__ ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

/**
 * Wait for an IO operation to finish using an IO operation.
 * If it's safe enough for Linux, it's safe enough for me.
 */
void io_wait() {
    __asm__ __volatile__ ( "outb %%al, $0x80" : : "a"(0) );
}