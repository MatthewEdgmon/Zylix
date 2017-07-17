#include <stdint.h>
#include <stdio.h>

#include <devices/acpi/acpi.h>
#include <devices/acpi/rsdp.h>

void SetupACPI() {
    RSDPLocate();
}
