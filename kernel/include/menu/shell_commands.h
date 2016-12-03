#ifndef __SHELL_COMMANDS_H__
#define __SHELL_COMMANDS_H__

#include <arch/interrupts.h>
#include <arch/registers.h>

int ComamndInputHandler(registers_t* registers);

void CommandEcho();
void CommandClear();
void CommandPing();
void CommandLogo();
void CommandLaunchCode();
void CommandClock();
void CommandMonitor();
void CommandPanic();
void CommandExplode();
void CommandBrowser();
void CommandFizzBuzz();

#endif /* __SHELL_COMMANDS_H__ */
