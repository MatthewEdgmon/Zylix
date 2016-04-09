#include <unistd.h>
#include <stdio.h>

int fgetchar(FILE* file) {
	char input_char;
	int status = read((int) file, &input_char, 1);

	if(status) {
		return status;
    }

	return input_char;
}
