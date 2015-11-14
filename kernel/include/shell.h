#ifndef __SHELL_H__
#define __SHELL_H__

#define MAX_COMMANDS 100

typedef struct {
    char* name;
    char* description;
    void* function;
} command_table_t;

void AddNewCommand();

#endif /* __SHELL_H__ */