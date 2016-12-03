#ifndef __SHELL_COMMANDS_H__
#define __SHELL_COMMANDS_H__

#include <arch/interrupts.h>
#include <arch/registers.h>

int ComamndInputHandler(registers_t* registers);

void CommandEcho();
void CommandClear();
void CommandLogo();
void CommandClock();
void CommandPanic();
void CommandExplode();
void CommandBrowser();
void CommandStartVideo();

#endif /* __SHELL_COMMANDS_H__ */
