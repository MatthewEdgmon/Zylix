##
# C library Makefile.
#
# This file is part of Zylix.
#
# Zylix is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Zylix is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Zylix.  If not, see <http://www.gnu.org/licenses/>.

CROSS_DIR = ../tools/toolchain/local/bin
CROSS_VER = 7.1.0

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
LIBRARY_CFLAGS += -finline-functions
#LIBRARY_CFLAGS += -fstack-protector-strong
LIBRARY_CFLAGS += -fno-builtin
LIBRARY_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
LIBRARY_CFLAGS += -pedantic -fno-omit-frame-pointer
LIBRARY_LDFLAGS = -shared -fPIC -pie -Bsymbolic -z defs

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

# C library startup code.
CRTI_OBJ     = $(ARCH_DIR)/crti.o
CRTN_OBJ     = $(ARCH_DIR)/crtn.o
CRTBEGIN_OBJ = $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ   = $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)

# Add flags supplied by our arch.
LIBRARY_CFLAGS  += $(LIBRARY_ARCH_CFLAGS)
LIBRARY_LDFLAGS += $(LIBRARY_ARCH_LDFLAGS)

# Order in which objects are linked.
#LIBRARY_OBJ_LINK_LIST = ${CRTI_OBJ} \
#                        ${CRTBEGIN_OBJ} \
#                        ${LIBRARY_ARCH_OBJS} \
#                        ${LIBRARY_OBJS} \
#                        ${CRTEND_OBJ} \
#                        ${CRTN_OBJ}

# Order in which objects are linked.
LIBRARY_OBJ_LINK_LIST = ${LIBRARY_ARCH_OBJS} \
                        ${LIBRARY_OBJS}

# Capture build events to a log.
ERRORS = &>>./.build-log

# Where to put the library headers.
SYSROOT = ../sysroot
INSTALL = $(CROSS_DIR)/../lib/gcc/$(LIBRARY_ARCH_GCC_NAME)/$(CROSS_VER)

# Text output colors.
include ../tools/pretty-print.inc

.PHONY: all libc.a ctags install clean
.SECONDARY:
.SUFFIXES:

all: libc.a

################################################################################
#                                  Build                                       #
################################################################################

libc.a: ${CRTI_OBJ} ${CRTN_OBJ} ${LIBRARY_ARCH_OBJS} ${LIBRARY_OBJS}
	@${AR} rcs libc.a ${LIBRARY_OBJ_LINK_LIST}
	@echo "Finished building libc."

%.o: %.c ${HEADERS}
	@printf "Compiling ${COLOR_LIGHT_BLUE}$< ${COLOR_OFF}..."
	@${CC} ${LIBRARY_CFLAGS} -g -I./include -c -o $@ $< ${ERRORS}
	@printf "${STATUS_OK}"

%.o: %.s
	@printf "Compiling ${COLOR_LIGHT_BLUE}$< ${COLOR_OFF}..."
	@${AS} -c $< -o $@ ${ERRORS}
	@printf "${STATUS_OK}"

################################################################################
#                                 Install                                      #
################################################################################

install: install-gcc install-sysroot

# NOTE: Copying crt objects might not be a good idea here....
install-gcc:
	@echo "Copying libc to compiler directories..."
	@rm -f $(INSTALL)/libc.a
	@cp libc.a $(INSTALL)/libc.a
	@cp -RT -f ./include $(INSTALL)/include
	@cp $(ARCH_DIR)/crt0.o $(INSTALL)/crt0.o
	@cp $(ARCH_DIR)/crti.o $(INSTALL)/crti.o
	@cp $(ARCH_DIR)/crtn.o $(INSTALL)/crtn.o

install-sysroot:
	@echo "Copying libc to sysroot..."
	@mkdir -p $(SYSROOT)/usr/{lib,include/libc}
	@rm -f $(SYSROOT)/usr/lib/libc.a
	@cp libc.a $(SYSROOT)/usr/lib/libc.a
	@cp -RT -f ./include $(SYSROOT)/usr/include/libc/

################################################################################
#                                  Clean                                       #
################################################################################

clean: clean-arch-objects clean-objects clean-library clean-library-gcc clean-library-sysroot clean-build-errors
	@echo "Cleaning libc complete."

clean-arch-objects:
	@echo "Cleaning libc arch-specific objects..."
	@rm -f ${LIBRARY_ARCH_OBJS}

clean-objects:
	@echo "Cleaning libc objects..."
	@rm -f ${LIBRARY_OBJS}

clean-library:
	@echo "Cleaning libc..."
	@rm -f libc.a

clean-library-gcc:
	@echo "Cleaning libc from gcc..."
	@rm -f $(INSTALL)/crt0.o
	@rm -f $(INSTALL)/libc.a

clean-library-sysroot:
	@echo "Cleaning libc from sysroot..."
	@rm -f $(SYSROOT)/usr/lib/libc.a

clean-build-errors:
	@echo "Cleaning libc build error log..."
	@rm -f .build-log
	@rm -f trace-*
