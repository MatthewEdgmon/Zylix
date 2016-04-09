#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

char input_buffer[256];

void error(char* message) {
    printf("msh error: %s\n", message);
}

int main(char* argv[], int argc) {
    while(true) {
        error("Hello from Matt's Shell!");
    }
    return 0;
}
