#include <stdio.h>
#include <unistd.h>

int fclose(FILE* file) {
	return close((int) file);
}
