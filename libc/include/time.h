/**
 * time.h - Date and time.
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

#ifndef __TIME_H__
#define __TIME_H__

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

struct tm {
	int tm_sec;   /* 0 - 60 */
	int tm_min;   /* 0 - 59 */
	int tm_hour;  /* 0 - 23 */
	int tm_mday;  /* 1 - 31 */
	int tm_mon;   /* 0 - 11 */
	int tm_year;  /* years since 1900 */
	int tm_wday;  /* 0 - 6 */
	int tm_yday;  /* 0 - 365 */
	int tm_isdst; /* >0 DST, 0 No DST, <0 undefined behaviour. */
};

#ifdef __cplusplus
}
#endif

#endif /* __TIME_H__ */
