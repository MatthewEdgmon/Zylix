/**
 * vsnprintf.c - Write formatted data from va list to sized buffer.
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

#include <stdarg.h>
#include <stdio.h>

int vsnprintf_help(unsigned c, void **ptr) {
    char *dst;

    dst = *ptr;
    *dst++ = c;
    *ptr = dst;
	return 0;
}

int vsnprintf(char *buffer, const char *fmt, va_list args) {
    int ret_val;
    ret_val = printf_format(fmt, args, vsnprintf_help, (void*) buffer);
    buffer[ret_val] = '\0';
    return ret_val;
}
