#include <types.h>

#include <arch/cpu_info.h>

#include "i386.h"

typedef struct {

    /* Information */
    char* vendor;
    char* brand;

} cpu_info_t;