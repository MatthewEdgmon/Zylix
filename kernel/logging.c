/**
 * logging.c
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
#include <stdbool.h>
#include <stdio.h>

#include <logging.h>

#include <terminal.h>

log_level_t logging_level = INFO;

void* logging_file = NULL;

void (*debug_hook)(void *, char *) = NULL;
void (*debug_video_crash)(char **) = NULL;

static char* level_types[] = {
    "",     /* Silent. */
    "INFO",
    "DEBUG",
    "WARNING",
    "ERROR",
    "FATAL",
    "SANITY"
};

static char message_buffer[1024];

void _Log(char* file_name, int line_number, log_level_t level, char* fmt, ...) {
    if(logging_level != SILENT && level >= logging_level) {
        va_list args;
		va_start(args, fmt);
        vsprintf(message_buffer, fmt, args);
        va_end(args);

        TerminalPrintString(message_buffer);

        fprintf(logging_file, "[00:00][%s:%d] (%s) %s", file_name, line_number, level_types[level], message_buffer);
    }
    return;
}
