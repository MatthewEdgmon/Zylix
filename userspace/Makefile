# Point to your local i686 elf cross compiler.
#CROSS_DIR = /usr/cross/bin
CROSS_DIR = /cygdrive/F/Development/OS/toolchain-testing/output/bin

# Build using our cross compiler.
CC  = $(CROSS_DIR)/i686-pc-zylix-gcc
LD  = $(CROSS_DIR)/i686-pc-zylix-ld
NM  = $(CROSS_DIR)/i686-pc-zylix-nm
CXX = $(CROSS_DIR)/i686-pc-zylix-g++
AS  = $(CROSS_DIR)/i686-pc-zylix-as

# Flags used to build the library.
USER_CFLAGS  = -O2 -std=c99
USER_CFLAGS += -finline-functions
USER_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
USER_CFLAGS += -pedantic -fno-omit-frame-pointer
USER_CFLAGS += -DZYLIX_LIBC_USERSPACE
USER_LDFLAGS = -shared -Bsymbolic -z defs
USER_LIBS    = -lgcc

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

FOLDERS = $(wildcard /*)

# Where to put the finished userspace binaries.
SYSROOT = ../sysroot

.PHONY: all .userspace-built ctags install clean
.SECONDARY:
.SUFFIXES:

all: .userspace-built

.userspace-built:
	@${BEG} "USER" "Building userspace binaries."
	@${END} "USER" "Userspace binaries built."
	@${INFO} "--" "Finished building userspace."
	@touch .userspace-built

################################################################################
#                                  Build                                       #
################################################################################

%.o: %.s
	@${BEG} "CC" "$<"
	@${AS} -c $< -o $@ ${ERRORS}
	@${END} "CC" "$<"

################################################################################
#                                  Ctags                                       #
################################################################################

ctags:
	@${BEG} "CTAG" "CTags (userspace)."
	@ctags -R .
	@${END} "CTAG" "CTags (userspace)."

################################################################################
#                                 Install                                      #
################################################################################

install:
	@${INFO} "--" "Installing userspace binaries."

################################################################################
#                                  Clean                                       #
################################################################################

clean: clean-userspace
	@${INFO} "--" "Cleaning complete."

clean-userspace:
	@${BEGRM} "RM" "Cleaning userspace binaries..."
	@rm -f .userspace-built
	@${ENDRM} "RM" "Cleaning userspace binaries..."
