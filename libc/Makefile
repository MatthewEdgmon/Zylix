# Point to your cross compiler.
CROSS_DIR = /home/matth_000/cross/bin
# Put the three digit number version of your cross compiler.
CROSS_VER = 6.1.0

# Change TARGET_ARCH to match the platform you're targeting.
TARGET_ARCH  = i686
ARCH_DIR     = arch/$(TARGET_ARCH)
include        $(ARCH_DIR)/make.config

# Build using our cross compiler.
CC  = $(CROSS_DIR)/$(LIBRARY_ARCH_GCC_NAME)-gcc
LD  = $(CROSS_DIR)/$(LIBRARY_ARCH_GCC_NAME)-ld
NM  = $(CROSS_DIR)/$(LIBRARY_ARCH_GCC_NAME)-nm
CXX = $(CROSS_DIR)/$(LIBRARY_ARCH_GCC_NAME)-g++
AS  = $(CROSS_DIR)/$(LIBRARY_ARCH_GCC_NAME)-as

# Flags used to build the library.
LIBRARY_CFLAGS  = -O2 -std=c99
LIBRARY_CFLAGS += -finline-functions -ffreestanding
LIBRARY_CFLAGS += -fstack-protector-strong
LIBRARY_CFLAGS += -fno-builtin
LIBRARY_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
LIBRARY_CFLAGS += -pedantic -fno-omit-frame-pointer
# Choose between userspace and kernel version.
LIBRARY_CFLAGS += -DZYLIX_LIBC_KERNEL
#LIBRARY_CFLAGS += -DZYLIX_LIBC_USERSPACE
LIBRARY_CFLAGS += -DKERNEL_LIBC_USE_ASSEMBLY
LIBRARY_LDFLAGS = -shared -Bsymbolic -z defs

# Library headers.
LIBRARY_INCLUDE_DIR = ./include
LIBRARY_HEADERS = $(shell find include/ -type f -name '*.h')

# Library object files.
LIBRARY_OBJS  = $(patsubst %.c,%.o,$(wildcard *.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard ctype/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard math/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard stat/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard stdio/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard stdlib/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard string/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard time/*.c))
LIBRARY_OBJS += $(patsubst %.c,%.o,$(wildcard unistd/*.c))

# Add flags supplied by our arch.
LIBRARY_CFLAGS  += $(LIBRARY_ARCH_CFLAGS)
LIBRARY_LDFLAGS += $(LIBRARY_ARCH_LDFLAGS)

# Order in which objects are linked.
LIBRARY_OBJ_LINK_LIST = ${LIBRARY_ARCH_OBJS} \
                        ${LIBRARY_OBJS}

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
INSTALL = $(CROSS_DIR)/../lib/gcc/$(LIBRARY_ARCH_GCC_NAME)/$(CROSS_VER)

.PHONY: all libc.a ctags install clean
.SECONDARY:
.SUFFIXES:

all: libc.a

################################################################################
#                                  Build                                       #
################################################################################

libc.a: ${LIBRARY_ARCH_OBJS} ${LIBRARY_OBJS}
	@${BEG} "AR" "libc.a"
	@${AR} rcs libc.a ${LIBRARY_OBJ_LINK_LIST}
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
	@mkdir -p $(SYSROOT)/usr/lib
	@rm -f $(SYSROOT)/usr/lib/libc.a
	@cp libc.a $(SYSROOT)/usr/lib/libc.a
	@cp -RT -f ./include $(SYSROOT)/usr/include/libc/
	@${END} "CP" "Done copying libc to sysroot."

################################################################################
#                                  Clean                                       #
################################################################################

clean: clean-arch-objects clean-objects clean-library clean-library-gcc clean-library-sysroot clean-build-errors
	@${INFO} "--" "Cleaning complete."

clean-arch-objects:
	@${BEGRM} "RM" "Cleaning library arch-specific objects..."
	@rm -f ${LIBRARY_ARCH_OBJS}
	@${ENDRM} "RM" "Cleaned library arch-specific objects."

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

clean-build-errors:
	@${BEGRM} "RM" "Cleaning build error log..."
	@rm -f .build-errors
	@rm -f trace-*
	@${ENDRM} "RM" "Cleaned build error log."
