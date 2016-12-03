#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <arch/interrupts.h>

#include <tasking/process.h>
#include <tasking/test_process.h>

uint8_t run_flag = 0;

void TestProcess() {
    if(run_flag == 0) {
        printf("Hello World!\n");
        run_flag = 1;
    }
    return;
}

void TestProcessCreate() {

}
