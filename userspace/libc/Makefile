#
# Makefile for Zylix userspace libc
#

# Point to your local i686 elf cross compiler.
CROSS_DIR = /home/matthew/cross/bin

# Build using our cross compiler.
CC  = $(CROSS_DIR)/i686-elf-gcc
LD  = $(CROSS_DIR)/i686-elf-ld
NM  = $(CROSS_DIR)/i686-elf-nm
CXX = $(CROSS_DIR)/i686-elf-g++
AS  = $(CROSS_DIR)/i686-elf-as

LIBC_VERSION_MAJOR = 0
LIBC_VERSION_MINOR = 0
LIBC_VERSION_PATCH = 0

# C flags used to build libc
LIBC_CFLAGS   =
LIBC_CXXFLAGS =

# libc source files
LIBC_OBJS  = $(patsubst %.c,%.o,$(wildcard ./*/*/*.c))
LIBC_OBJS += $(patsubst %.c,%.o,$(wildcard ./*/*.c))
LIBC_OBJS += $(patsubst %.c,%.o,$(wildcard ./*.c))

# Pretty output utilities.
BEG     = ../../tools/output/mk-beg
END     = ../../tools/output/mk-end
INFO    = ../../tools/output/mk-info
ERRORS  = 2>>../.build-errors || ../../tools/output/mk-error
ERRORSS = >>../.build-errors || ../../tools/output/mk-error
BEGRM   = ../../tools/output/mk-beg-rm
ENDRM   = ../../tools/output/mk-end-rm

# Capture build error to a log.
ERRORS = 2>>../.build-errors

###############################################################################
#                                   libc                                      #
###############################################################################

libc.a: ${LIBC_OBJS}
	@${BEG} "AR" "libc"
	@${AR} rcs $@ ${LIBC_OBJS}
	@${END} "AR" "libc"
	@${INFO} "--" "Finished building libc."

libc/%.o: libc/%.c ${HEADERS}
	@${BEG} "CC" "$<"
	@${CC} ${LIBC_CFLAGS} -g -I./libc/include -c -o $@ $< ${ERRORS}
	@${END} "CC" "$<"

libc/%.o: libc/%.s
	@${BEG} "CC" "$<"
	@${AS} -c $< -o $@ ${ERRORS}
	@${END} "CC" "$<"

###############################################################################
#                                   Clean-Up                                  #
###############################################################################

clean: clean-libc-objects clean-libc clean-build-errors

clean-libc-objects:
	@${BEGRM} "RM" "Cleaning libc objects..."
	@rm -f ${LIBC_OBJS}
	@${ENDRM} "RM" "Cleaned libc objects."

clean-libc:
	@${BEGRM} "RM" "Cleaning libc library..."
	@rm -f libc.a
	@${ENDRM} "RM" "Cleaned libc library."

clean-build-errors:
	@${BEGRM} "RM" "Cleaning build error log..."
	@rm -f .build-errors
	@${ENDRM} "RM" "Cleaned build error log."