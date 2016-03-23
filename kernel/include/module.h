#ifndef __MODULE_H__
#define __MODULE_H__

#include <libc/stdint.h>

void (* symbol_find(const char * name))(void);

#endif /* __MODULE_H__ */
