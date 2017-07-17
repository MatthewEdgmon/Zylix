/**
 * string.h - C string and memory manipulation.
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

#ifndef __STRING_H__
#define __STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Define size_t if it's undefined. */
#ifndef LIBC_SIZE_T_DEFINED
#define LIBC_SIZE_T_DEFINED
typedef unsigned long size_t;
#endif /* LIBC_SIZE_T_DEFINED */

/* Define NULL if it's undefined. */
#ifndef LIBC_NULL_DEFINED
#define LIBC_NULL_DEFINED
#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif /* __cplusplus */
#endif /* LIBC_NULL_DEFINED */

#include <stddef.h>

int memcmp(const void *vl, const void *vr, size_t n);
void* memcpy(void* dest, const void* src, size_t);
void* memset(void* buffer_pointer, int value, size_t size);

char* stpcpy(char * restrict d, const char * restrict s);
int strcmp(const char * l, const char * r);
char* strcpy(char * restrict dest, const char * restrict src);
size_t strlen(const char* string);

// TODO: Add in preprocessor macros for handling C extensions, like POSIX strdup
char* strdup(const char* s1);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STRING_H__ */
