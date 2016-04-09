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
