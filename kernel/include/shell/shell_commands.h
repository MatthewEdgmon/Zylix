/**
 * shell_commands.h - Built-in shell commands.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SHELL_COMMANDS_H__
#define __SHELL_COMMANDS_H__

#include <arch/interrupts.h>
#include <arch/registers.h>

int ComamndInputHandler(cpu_registers_t* registers);

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
void CommandATASetupPIO();
void CommandATAResetPIO();
void CommandATATestPIO();
void CommandATASetupDMA();
void CommandATAResetDMA();
void CommandATATestDMA();
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
