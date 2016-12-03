#include <arch/stop.h>

void stop_execution() {
    __asm__ __volatile__("cli");
    __asm__ __volatile__("hlt");
}
