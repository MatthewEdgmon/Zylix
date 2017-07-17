/**
 * crt0.c - i686 C runtime support.
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

#include <syscall.h>
#include <stdio.h>

/* This crt0 is used by userspace programs only. */

FILE* stdin   = NULL;
FILE* stdout  = NULL;
FILE* stderr  = NULL;

#ifdef ZYLIX_LIBC_USERSPACE

extern int main(char** argc, int argv);
extern void _exit(int);

void _start() {
    stdin = (FILE*) syscall_0arg(SYSCALL_GETSTDIN);
	stdout = (FILE*) syscall_0arg(SYSCALL_GETSTDOUT);
	stderr = (FILE*) syscall_0arg(SYSCALL_GETSTDERR);
	_exit(main(NULL, NULL));
}

#endif /* ZYLIX_LIBC_USERSPACE */
