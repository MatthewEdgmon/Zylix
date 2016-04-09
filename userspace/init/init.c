#include <stdio.h>
#include <unistd.h>

int main(char* argv[], int argc) {
    printf("Hello from userspace!\n");
    printf("Init is loading...\n");
    if(fork() == 0) {
        exec("bin/msh");
    }
    return 0;
}
