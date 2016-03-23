#include <libc/stdbool.h>
#include <libc/stdarg.h>
#include <libc/stddef.h>
#include <libc/stdio.h>
#include <libc/stdlib.h>
#include <libc/string.h>

#include <terminal.h>

/* Flags for formatting text. */
#define FORMAT_LJ  0x01      /* Justify text to the left. */
#define FORMAT_CA  0x02      /* Use capital letters instead of lower in hex. */
#define FORMAT_SG  0x04      /* Signed numeric conversion. */
#define FORMAT_32  0x08      /* Long (32-bit) numeric conversion */
#define	FORMAT_16  0x10      /* Short (16-bit) numeric conversion */
#define FORMAT_WS  0x20      /* PR_SG set and num was < 0 */
#define FORMAT_LZ  0x40      /* Pad left with zeros instead of ' '. */
#define FORMAT_FP  0x80      /* Pointers are far. */

/* Largest number handled is 2^32-1, lowest radix handled is 8.
 2^32-1 in base 8 has 11 digits (add 5 for trailing NUL and for slop). */
#define FORMAT_BUFLEN 16

/**
 * The base printf fucntion that does the heavy lifting of formatting text.
 * It takes 4 arguments:
 * fmt = A string of text to be formatted.
 * va_args = Variable argument list.
 * printf_func_ptr = A pointer to the printf function to use (vasprintf, sprintf, etc).
 *
 */
int do_printf(const char* fmt, va_list va_args, printf_func_ptr func, void* ptr) {

    /* Use a state machine to step through the format list. */
    unsigned int state = 0;

    /* What needs to be done to the text. See the flags above. */
    unsigned int flags = 0;

    /* How many characters were "printed" as per the C standard. */
    unsigned int count = 0;

    /* What base should the character be converted to. Default is 10. */
    unsigned int base = 10;

    unsigned int given_width = 0;
    unsigned int actual_width = 0;

    /* Where we're operating on the buffer. */
    char* where;

    char buffer[FORMAT_BUFLEN];

    /* This is the actual data we are currently formatting. */
    long data = 0;

    /* Scan through each format list. */
    for(; *fmt; fmt++) {
        /* Use a state machine to go through each specifier. */
        switch(state) {
            /* Finding '%' */
            case 0:
                if(*fmt != '%') {
                    /* Not a '%', pass it. */
                    func(*fmt, &ptr);
                    count++;
                    break;
                }
                /* Found a '%', advance state to check if it's a flag. */
                state++;
                fmt++;
            /* Finding the flags (%-0). */
            case 1:
                if(*fmt == '%') {
                    /* Simply print '%'. */
                    func(*fmt, &ptr);
    				count++;
    				state = flags = given_width = 0;
    				break;
                }
                if(*fmt == '-') {
                    /* %-- is illegal */
    				if(flags & FORMAT_LJ) {
    					state = flags = given_width = 0;
                    } else {
    					flags |= FORMAT_LJ;
                    }
    				break;
    			}
                /* Not a flag character. Continue. */
    			state++;
                /* Check now for %0 */
    			if(*fmt == '0') {
    				flags |= FORMAT_LZ;
    				fmt++;
    			}
            /* Finding numeric field width. */
            case 2:
                if(*fmt >= '0' && *fmt <= '9') {
                    given_width = 10 * given_width + (*fmt - '0');
                    break;
                }
                /* Not numeric field width. Keep going. */
                state++;
            /* Finding modifier characters (FNlh). */
            case 3:
                if(*fmt == 'F') {
                    /* Apply the far pointers flag. */
                    flags |= FORMAT_FP;
                    break;
                }
                if(*fmt == 'N') {
                    break;
                }
                if(*fmt == 'l') {
                    /* Apply the long numeric conversion flag. */
                    flags |= FORMAT_32;
                    break;
                }
                if(*fmt == 'h') {
                    /* Apply the shot numeric conversion flag. */
                    flags |= FORMAT_16;
                    break;
                }
                /* Continue. */
                state++;
            /* Finding conversion characters (Xxpndiuocs). */
            case 4:
                /* Null terminate the buffer. */
                where = buffer + FORMAT_BUFLEN - 1;
                *where = '\0';
                switch(*fmt) {
                    /* Uppercase hexadecimal. */
                    case 'X':
                        /* Apply the uppercase hex flag. */
                        flags |= FORMAT_CA;
                        /* Continue. */
                    /* Lowercase hexadecimal. */
                    case 'x':
                    /* Pointer address. */
                    case 'p':
                    /* Nothing printed. */
                    case 'n':
                        base = 16;
                        goto load_number;
                    /* Signed decimal integer. */
                    case 'd':
                    /* Signed decimal integer. */
                    case 'i':
                        /* Apply the signed conversion flag. */
                        flags |= FORMAT_SG;
                    /* Unsigned decimal integer */
                    case 'u':
                        base = 10;
                        goto load_number;
                    /* Unsigned octal. */
                    case 'o':
                        base = 8;

/* Load the value to be printed. */
load_number:
                        /* Check numeric conversion. */
                        if(flags & FORMAT_32) {
                            /* l - long - 32 bit.*/
                            data = va_arg(va_args, unsigned long);
                        } else if (flags & FORMAT_16) {
                            /* h - short - 16 bit. Checl the signage. */
                            if(flags & FORMAT_SG) {
        						data = (short)va_arg(va_args, int);
                            } else {
        						data = (unsigned short)va_arg(va_args, int);
                            }
                        } else {
                            /* No h or l, signed or unsigned sizeof(int). */
                            if(flags & FORMAT_SG) {
        						data = va_arg(va_args, int);
                            } else {
        						data = va_arg(va_args, unsigned int);
                            }
                        }

                        /* Handle the signage. */
                        if(flags & FORMAT_SG) {
                            if(data < 0) {
                                flags |= FORMAT_WS;
                                data = -data;
                            }
                        }

                        /* Convert binary to hex/octal/decimal. */
                        do {
                            unsigned long temp = (unsigned long)data % base;

        					where--;
        					if(temp < 10) {
        						*where = temp + '0';
        					} else if(flags & FORMAT_CA) {
        						*where = temp - 10 + 'A';
        					} else {
        						*where = temp - 10 + 'a';
                            }
        					data = (unsigned long)data / base;
                        } while(data != 0);

                        /* Done with numeric conversion. Push it out. */
                        goto emit;

                    /* Character. */
                    case 'c':
                        /* Pad-left with zeros is not allowed. */
                        flags &= ~FORMAT_LZ;
                        where--;
                        *where = (char)va_arg(va_args, int);
                        actual_width = 1;
                        goto emit2;
                    /* String of characters. */
                    case 's':
                        /* Pad-left with zeros is not allowed. */
                        flags &= ~FORMAT_LZ;
                        where = va_arg(va_args, char*);

emit:
                        actual_width = strlen(where);
                        if(flags & FORMAT_WS) {
        					actual_width++;
                        }

                        /* If we pad left with zeroes, do the sign now. */
                        if((flags & (FORMAT_WS | FORMAT_LZ)) == (FORMAT_WS | FORMAT_LZ)) {
        					func('-', &ptr);
        					count++;
        				}

emit2:
                        /* Pad on left with spaces or zeroes (for right justify). */
                        if((flags & FORMAT_LJ) == 0) {
                            while(given_width > actual_width) {
        						func(flags & FORMAT_LJ ? '0' : ' ', &ptr);
        						count++;
        						given_width--;
        					}
                        }

                        /* If padding left with spaces, do the sign now. */
                        if((flags & (FORMAT_WS | FORMAT_LZ)) == FORMAT_WS) {
        					func('-', &ptr);
        					count++;
        				}

                        /* Emit string/char/converted number. */
                        while(*where != '\0') {
                            func(*where++, &ptr);
        					count++;
                        }

                        /* Pad on right with spaces (for left justify). */
                        if(given_width < actual_width) {
        					given_width = 0;
                        } else {
                            given_width -= actual_width;
                        }
        				for(; given_width; given_width--) {
        					func(' ', &ptr);
        					count++;
        				}

                        /* Done. */
                        break;

                    /* Not a conversion character. */
                    default:
                        break;
                }

            default:
                state = flags = given_width = 0;
                break;
        }

    }

    /* Return number of characters printed. */
    return count;
}

int vprintf_help(unsigned c, void **ptr) {
	return putc(c);
}

int vprintf(const char *fmt, va_list va_args) {
	return do_printf(fmt, va_args, vprintf_help, NULL);
}

int printf(const char* fmt, ...) {

    va_list va_args;
    int return_value = 0;

    va_start(va_args, fmt);
    return_value = vprintf(fmt, va_args);
    va_end(va_args);

    return return_value;
}
