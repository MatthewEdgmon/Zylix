#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

uint64_t rdtsc();

void SetupCPU();
void SetupFPU();

#include "../../arch/i686/i686.h"

#endif /* __CPU_H__ */
