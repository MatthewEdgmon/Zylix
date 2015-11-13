#include <arch/cpu_setup.h>

#include "arm.h"

void setup_cpu() {
	store_cpu_information();
	return;
}