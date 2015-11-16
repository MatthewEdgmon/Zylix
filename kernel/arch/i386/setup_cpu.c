#include <arch/setup_cpu.h>

#include "i386.h"
#include "interrupts.h"
#include "pic.h"

void SetupCPU() {
	StoreCPUInformation();
	RemapPIC(0x20, 0x28);
	SetupTimer(50); /* 50 Hz */
	SetupInterrupts();
	return;
}