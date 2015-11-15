#ifndef __SHELL_H__
#define __SHELL_H__

#define MAX_COMMANDS 100
#define MAX_HISTORY  20

typedef struct {
    char* name;
    char* description;
    void* function;
} command_table_t;

/* Two base commands. */
void CommandEmpty();
void CommandHelp();

void AddShellCommand(char* name, char* description, void* function);
int FindShellCommand(char* name);
void Shell();
void SetupShell();

#endif /* __SHELL_H__ */