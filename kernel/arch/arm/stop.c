#include <arch/stop.h>

void stop_execution() {
    __asm__ __volatile__("cpsie");
    __asm__ __volatile__("cpsid");
    __asm__ __volatile__("wfi");
}
