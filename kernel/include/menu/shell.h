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
