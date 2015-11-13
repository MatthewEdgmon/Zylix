#include <arch/SetupCPU.h>

#include "i386.h"

void SetupCPU() {
	StoreCPUInformation();
	RemapPIC(0x20, 0x28);
	SetupTimer(50); /* 50 Hz */
	SetupIRQ();
	SetupGDT();
	SetupIDT();
	SetupISR();
	return;
}