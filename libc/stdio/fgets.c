/**
 * fgets.c - Get string from file.
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
