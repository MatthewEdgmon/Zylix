/**
 * stdlib.h - Common C utilities.
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

#ifndef __STDLIB_H__
#define __STDLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX (0x7FFFFFFF)

static unsigned long int rand_seed = 1;

typedef unsigned long size_t;

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int atoi(const char*);
long atol(const char*);
long long atoll(const char*);
double atof(const char*);

float strtof(const char*, char**);
long strtol(char*, char*, int);

int rand(void);
void srand(unsigned);

void* malloc(size_t);
void* calloc(size_t);
void* realloc(void*, size_t);
void  free(void*);

void abort(void);

int atexit(void(*) (void));

char* getenv(const char *);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STDLIB_H__ */
