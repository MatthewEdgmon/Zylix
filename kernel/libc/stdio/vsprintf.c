#include <libc/stdio.h>
#include <libc/stdarg.h>
#include <libc/string.h>

int vsprintf_help(unsigned c, void **ptr) {
	char *dst;

	dst = *ptr;
	*dst++ = c;
	*ptr = dst;
	return 0 ;
}

int vsprintf(char *buffer, const char *fmt, va_list args) {
	int ret_val;
	ret_val = do_printf(fmt, args, vsprintf_help, (void *)buffer);
	buffer[ret_val] = '\0';
	return ret_val;
}
