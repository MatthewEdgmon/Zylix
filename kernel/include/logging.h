/**
 * logging.h
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

#ifndef __LOGGING_H__
#define __LOGGING_H__

typedef enum {
    SILENT = 0,    /* All logging is disabled. */
    INFO = 1,      /* If we want to see maximum ouput of everything happening. */
    DEBUG = 2,     /* This level logs major events, such as a subystem starting. */
    WARNING = 3,   /* Reserved for handled exceptions, like a configuration value being at default. */
    ERROR = 4,     /* A minor error has occured, execution can continue. */
    FATAL = 5,     /* A major error has occured that halts the execution. */
    SANITY = 6     /* A basic sanity check has failed. 1 = 0. */
} log_level_t;

extern log_level_t logging_level;
extern void* debug_file;
extern void _Log(char * title, int line_no, log_level_t level, char *fmt, ...);
extern void (*debug_hook)(void *, char *);
extern void (*debug_video_crash)(char **);

#ifndef SILENCE_LOGGING
#define KernelLog(level, ...) _Log(__FILE__, __LINE__, level, __VA_ARGS__)
#else
#define KernelLog(level, ...)
#endif

#endif /* __LOGGING_H__ */
