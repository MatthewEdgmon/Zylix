/**
 * shell.h - Built-in kernel shell.
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

#ifndef __SHELL_H__
#define __SHELL_H__

typedef void (*func_pointer_t)();

void CommandEmpty();
void CommandHelp();

void AddShellCommand(char* name, char* description, func_pointer_t function);
int FindShellCommand(char* name);
void Shell(char* input);
char* ShellHistoryUp();
char* ShellHistoryDown();
void SetupShell();

#endif /* __SHELL_H__ */
