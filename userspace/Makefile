##
# Userspace programs Makefile.
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
CC  = $(CROSS_DIR)/$(USERSPACE_ARCH_GCC_NAME)-gcc
LD  = $(CROSS_DIR)/$(USERSPACE_ARCH_GCC_NAME)-ld
NM  = $(CROSS_DIR)/$(USERSPACE_ARCH_GCC_NAME)-nm
CXX = $(CROSS_DIR)/$(USERSPACE_ARCH_GCC_NAME)-g++
AS  = $(CROSS_DIR)/$(USERSPACE_ARCH_GCC_NAME)-as

# Flags used to build the library.
USER_CFLAGS  = -O2 -std=c99
USER_CFLAGS += -finline-functions
USER_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
USER_CFLAGS += -pedantic -fno-omit-frame-pointer
USER_CFLAGS += -DZYLIX_LIBC_USERSPACE
USER_LDFLAGS = -shared -Bsymbolic -z defs
USER_LIBS    = -lgcc

# Capture build error to a log.
ERRORS = 2>>./.build-errors

FOLDERS = $(wildcard /*)

# Where to put the finished userspace binaries.
SYSROOT = ../sysroot

.PHONY: all .userspace-built ctags install clean
.SECONDARY:
.SUFFIXES:

all: .userspace-built

.userspace-built:
	@touch .userspace-built

################################################################################
#                                  Build                                       #
################################################################################

%.o: %.s
	@printf "Compiling ${COLOR_LIGHT_BLUE}$< ${COLOR_OFF}..."
	@${AS} -c $< -o $@ ${ERRORS}
	@printf "${STATUS_OK}"

################################################################################
#                                  Ctags                                       #
################################################################################

ctags:
	@echo "CTags (userspace)."
	@ctags -R .
	@echo "CTags (userspace)."

################################################################################
#                                 Install                                      #
################################################################################

install:
	@echo "Installing userspace binaries."

################################################################################
#                                  Clean                                       #
################################################################################

clean: clean-userspace
	@echo "Cleaning complete."

clean-userspace:
	@echo "Cleaning userspace binaries..."
	@rm -f .userspace-built
	@echo "Cleaning userspace binaries..."
