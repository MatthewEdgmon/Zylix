#ifndef __SHELL_COMMANDS_H__
#define __SHELL_COMMANDS_H__

#include <arch/interrupts.h>
#include <arch/registers.h>

int ComamndInputHandler(registers_t* registers);

void CommandEcho();
void CommandClear();
void CommandLogo();
void CommandClock();
void CommandCPUInfo();
void CommandSMBIOSInfo();
void CommandPanic();
void CommandExplode();
void CommandBrowser();
void CommandShutdown();
void CommandBGAStart();
void CommandVGADump();
void CommandVGAText40x25();
void CommandVGAText40x50();
void CommandVGAText80x25();
void CommandVGAText80x50();
void CommandVGAText90x30();
void CommandVGAText90x60();
void CommandVGAGraphics640x480x16();

#endif /* __SHELL_COMMANDS_H__ */
