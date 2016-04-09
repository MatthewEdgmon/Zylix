# Point to your local i686 elf cross compiler.
CROSS_DIR = /home/matth_000/cross/bin

# Build using our cross compiler.
CC  = $(CROSS_DIR)/i686-elf-gcc
LD  = $(CROSS_DIR)/i686-elf-ld
NM  = $(CROSS_DIR)/i686-elf-nm
CXX = $(CROSS_DIR)/i686-elf-g++
AS  = $(CROSS_DIR)/i686-elf-as

# Flags used to build the library.
LIBRARY_CFLAGS  = -O2 -std=c99
LIBRARY_CFLAGS += -finline-functions -ffreestanding
LIBRARY_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
LIBRARY_CFLAGS += -pedantic -fno-omit-frame-pointer
# Choose between userspace and kernel version.
LIBRARY_CFLAGS += -DZYLIX_LIBC_KERNEL
#LIBRARY_CFLAGS += -DZYLIX_LIBC_USERSPACE
LIBRARY_CFLAGS += -DKERNEL_LIBC_USE_ASSEMBLY
LIBRARY_CFLAGS = -shared -Bsymbolic -z defs

# Library headers.
LIBRARY_INCLUDE_DIR = ./include
LIBRARY_HEADERS = $(shell find include/ -type f -name '*.h')

# Library object files.
LIBRARY_OBJS  = $(patsubst %.c,%.o,$(wildcard *.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard ctype/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard stdio/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard stdlib/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard string/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard syscall/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard unistd/*.c))

# Pretty output utilities.
BEG = ../tools/output/mk-beg
END = ../tools/output/mk-end
INFO = ../tools/output/mk-info
ERRORS = 2>>/.build-errors || ../tools/output/mk-error
ERRORSS = >>/.build-errors || ../tools/output/mk-error
BEGRM = ../tools/output/mk-beg-rm
ENDRM = ../tools/output/mk-end-rm

# Capture build error to a log.
ERRORS = 2>>./.build-errors

# Where to put the library headers.
SYSROOT = ../sysroot
INSTALL = $(CROSS_DIR)/../lib/gcc/i686-elf/5.3.0

.PHONY: all libc.a ctags install clean
.SECONDARY:
.SUFFIXES:

all: libc.a

################################################################################
#                                  Build                                       #
################################################################################

libc.a: ${LIBRARY_OBJS}
	@${BEG} "AR" "libc.a"
	@${AR} rcs libc.a ${LIBRARY_OBJS}
	@${END} "AR" "libc.a"
	@${INFO} "--" "Finished building library."

%.o: %.c ${HEADERS}
	@${BEG} "CC" "$<"
	@${CC} ${LIBRARY_CFLAGS} -g -I./include -c -o $@ $< ${ERRORS}
	@${END} "CC" "$<"

%.o: %.s
	@${BEG} "CC" "$<"
	@${AS} -c $< -o $@ ${ERRORS}
	@${END} "CC" "$<"

################################################################################
#                                  Ctags                                       #
################################################################################

ctags:
	@${BEG} "CTAG" "CTags (libc)."
	@ctags -R ./
	@${END} "CTAG" "CTags (libc)."

################################################################################
#                                 Install                                      #
################################################################################

install: install-gcc install-sysroot

install-gcc:
	@${BEG} "CP" "Copying libc to gcc."
	@rm -f $(INSTALL)/libc.a
	@cp libc.a $(INSTALL)/libc.a
	@cp -RT -f ./include $(INSTALL)/include
	@${END} "CP" "Done copying libc to gcc."

install-sysroot:
	@${BEG} "CP" "Copying libc to sysroot."
	@rm -f $(SYSROOT)/usr/lib/libc.a
	@cp libc.a $(SYSROOT)/usr/lib/libc.a
	@cp -RT -f ./include $(SYSROOT)/usr/include/libc/
	@${END} "CP" "Done copying libc to sysroot."

################################################################################
#                                  Clean                                       #
################################################################################

clean: clean-objects clean-library clean-library-gcc clean-library-sysroot clean-tags clean-build-errors
	@${INFO} "--" "Cleaning complete."

clean-objects:
	@${BEGRM} "RM" "Cleaning library objects..."
	@rm -f ${LIBRARY_OBJS}
	@${ENDRM} "RM" "Cleaned library objects."

clean-library:
	@${BEGRM} "RM" "Cleaning library..."
	@rm -f libc.a
	@${ENDRM} "RM" "Cleaned library."

clean-library-gcc:
	@${BEGRM} "RM" "Cleaning library from gcc..."
	@rm -f $(INSTALL)/libc.a
	@${ENDRM} "RM" "Cleaned library from gcc."

clean-library-sysroot:
	@${BEGRM} "RM" "Cleaning library from sysroot..."
	@rm -f $(SYSROOT)/usr/lib/libc.a
	@${ENDRM} "RM" "Cleaned library from sysroot."

clean-tags:
	@${BEGRM} "RM" "Cleaning CTags..."
	@rm -f tags
	@${ENDRM} "RM" "Cleaned CTags."

clean-build-errors:
	@${BEGRM} "RM" "Cleaning build error log..."
	@rm -f .build-errors
	@rm -f trace-*
	@${ENDRM} "RM" "Cleaned build error log."
