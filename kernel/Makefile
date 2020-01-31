##
# Zylix kernel makefile
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
# TARGET_ARCH  = i686
TARGET_ARCH  = x86_64
ARCH_DIR     = arch/$(TARGET_ARCH)
include        $(ARCH_DIR)/make.config

# Build using our cross compiler.
AR  = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-ar
AS  = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-as
CC  = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-gcc
LD  = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-ld
NM  = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-nm
CXX = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-g++

# Flags used to build the kernel.
KERNEL_CFLAGS  = -O2 -std=c99
KERNEL_CFLAGS += -finline-functions -ffreestanding
KERNEL_CFLAGS += -DARCH_$(TARGET_ARCH)
# TODO: Build support for libssp in gcc
#KERNEL_CFLAGS += -fstack-protector-strong
KERNEL_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
KERNEL_CFLAGS += -pedantic -fno-omit-frame-pointer
KERNEL_LDFLAGS = -z defs -z max-page-size=0x1000
KERNEL_LIBS    = -lc -lgcc

# Kernel headers.
KERNEL_INCLUDE_DIR = ./include
KERNEL_HEADERS = $(shell find include/ -type f -name '*.h')

# Kernel object files.
KERNEL_OBJS  = $(patsubst %.c,%.o,$(wildcard devices/*/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard devices/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard filesystem/*/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard filesystem/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard memory/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard shell/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard structures/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard tasking/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard *.c))

# Add flags supplied by our arch.
KERNEL_CFLAGS  += $(KERNEL_ARCH_CFLAGS)
KERNEL_LDFLAGS += $(KERNEL_ARCH_LDFLAGS)

# Order in which objects are linked.
KERNEL_OBJ_LINK_LIST = ${KERNEL_ARCH_OBJS} \
                       ${KERNEL_OBJS} \

# Capture build events to a log.
ERRORS = 2>>./.build-log

# Where to put the finished kernel and headers.
SYSROOT = ../sysroot

# Text output colors.
include ../tools/pretty-print.inc

.PHONY: all zykernel ctags install clean
.SECONDARY:
.SUFFIXES:

all: zykernel

################################################################################
#                                  Build                                       #
################################################################################

zykernel: ${KERNEL_ARCH_OBJS} ${KERNEL_OBJS}
	@${CC} -T $(ARCH_DIR)/linker.ld -o $@ ${KERNEL_CFLAGS} ${KERNEL_OBJ_LINK_LIST} ${KERNEL_LDFLAGS} ${KERNEL_LIBS}
	@echo "Finished building kernel."

%.o: %.c ${HEADERS}
	@printf "Compiling ${COLOR_LIGHT_BLUE}$< ${COLOR_OFF}..."
	@${CC} ${KERNEL_CFLAGS} -g -I./include -c -o $@ $< ${ERRORS}
	@printf "${STATUS_OK}"

%.o: %.s
	@printf "Compiling ${COLOR_LIGHT_BLUE}$< ${COLOR_OFF}..."
	@${AS} -c $< -o $@ # ${ERRORS}
	@printf "${STATUS_OK}"

################################################################################
#                                 Install                                      #
################################################################################

install: install-kernel install-kernel-headers

install-kernel: zykernel
	@echo "Copying kernel to sysroot."
	@rm -f $(SYSROOT)/boot/zykernel
	@cp zykernel $(SYSROOT)/boot

install-kernel-headers: zykernel
	@echo "Copying kernel headers to sysroot."
	@rm -r -f $(SYSROOT)/usr/include/zykernel
	@cp -RT ./include $(SYSROOT)/usr/include/zykernel

################################################################################
#                                  Clean                                       #
################################################################################

clean: clean-arch-objects clean-objects clean-kernel clean-build-errors
	@echo "Cleaning kernel complete."

clean-arch-objects:
	@echo "Cleaning kernel arch-specific objects..."
	@rm -f ${KERNEL_ARCH_OBJS}

clean-objects:
	@echo "Cleaning kernel objects..."
	@rm -f ${KERNEL_OBJS}

clean-kernel:
	@echo "Cleaning kernel binary..."
	@rm -f zykernel

clean-build-errors:
	@echo "Cleaning kernel build error log..."
	@rm -f .build-log
	@rm -f trace-*
