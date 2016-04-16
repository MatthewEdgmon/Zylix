#ifndef __PANIC_H__
#define __PANIC_H__

#include <arch/registers.h>

void _KernelPanic(char* message, const char* file, int line, registers_t* registers);
void _AssertFailure(const char* statement, const char* file, int line);

#define KernelPanic(message, registers) _KernelPanic(message, __FILE__, __LINE__, registers)
#define Assert(statement) ((statement) ? (void) 0 : _AssertFailure(#statement, __FILE__, __LINE__))

#endif /* __PANIC_H__ */
