#include <stdio.h>

char* fgets(char* buffer, int size, FILE* file) {

    /* lock file */

    for(int i = 0; i < size; i++) {
        int status = fgetc(file);
        if(status < 0) {
            return NULL;
        }
        buffer[i] = (unsigned char) status;
        if((unsigned char) status == '\n') {
            return buffer;
        }
    }

    /* unlock file */

    return buffer;
}
