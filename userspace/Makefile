# Point to your local i686 elf cross compiler.
CROSS_DIR = /home/matth_000/cross/bin

# Build using our cross compiler.
CC  = $(CROSS_DIR)/i686-elf-gcc
LD  = $(CROSS_DIR)/i686-elf-ld
NM  = $(CROSS_DIR)/i686-elf-nm
CXX = $(CROSS_DIR)/i686-elf-g++
AS  = $(CROSS_DIR)/i686-elf-as

# Flags used to build the library.
USER_CFLAGS  = -O2 -std=c99
USER_CFLAGS += -finline-functions -ffreestanding
USER_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
USER_CFLAGS += -pedantic -fno-omit-frame-pointer
USER_CFLAGS += -DZYLIX_LIBC_USERSPACE
USER_LDFLAGS = -shared -Bsymbolic -z defs
USER_LIBS    = -nostdlib -lgcc

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

.PHONY: all .userspace-done ctags install clean
.SECONDARY:
.SUFFIXES:

all: .userspace-done

.userspace-done:
	@${BEG} "USER" "Building userspace binaries."
	@${END} "USER" "Userspace binaries built."
	@${INFO} "--" "Finished building userspace."
	@touch .userspace-done

################################################################################
#                                  Ctags                                       #
################################################################################

ctags:
	@${BEG} "CTAG" "CTags (userspace)."
	@ctags -R .
	@${END} "CTAG" "CTags (userspace)."

install:
	@${INFO} "--" "Installing userspace binaries."

clean:
	@${INFO} "--" "Cleaning complete."
