#include <stdint.h>

/**
 * Read the current value of the CPU's time-stamp counter and store into EDX:EAX.
 * The time-stamp counter contains the amount of clock ticks that have elapsed since the last CPU reset.
 * The value is stored in a 64-bit MSR and is incremented after each clock cycle.
 */
uint64_t rdtsc() {
    uint64_t ret;
    __asm__ __volatile__ ( "rdtsc" : "=A"(ret) );
    return ret;
}