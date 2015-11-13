#
# Makefile for Zylix
#

## This makefile is pretty ugly. It currently holds up compilation of both
## the kernel, bootloader and userspace utilities. It will be remade when
## we port GCC to Zylix.

# Point to your local i686 elf cross compiler.
CROSS_DIR = /home/matthew/cross/bin

# Build using our cross compiler.
CC  = $(CROSS_DIR)/i686-elf-gcc
LD  = $(CROSS_DIR)/i686-elf-ld
NM  = $(CROSS_DIR)/i686-elf-nm
CXX = $(CROSS_DIR)/i686-elf-g++
AS  = $(CROSS_DIR)/i686-elf-as

KERNEL_VERSION_MAJOR = 0
KERNEL_VERSION_MINOR = 0
KERNEL_VERSION_PATCH = 0

# Flags used to build the kernel.
KERNEL_CFLAGS  = -O2 -std=c99
KERNEL_CFLAGS += -finline-functions -ffreestanding
KERNEL_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
KERNEL_CFLAGS += -pedantic -fno-omit-frame-pointer
KERNEL_LDFLAGS = -shared -Bsymbolic -z defs
KERNEL_LIBS    = -nostdlib -lgcc

# Kernel headers.
KERNEL_INCLUDE_DIR = ./kernel/include
KERNEL_HEADERS = $(shell find kernel/include/ -type f -name '*.h')

# Kernel object files.
KERNEL_OBJS  = $(patsubst %.c,%.o,$(wildcard kernel/devices/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard kernel/*.c))

# Change TARGET_ARCH to match the platform you're targeting.
TARGET_ARCH  = i386
ARCH_DIR     = kernel/arch/$(TARGET_ARCH)

# Kernel architecture specific files
include		   $(ARCH_DIR)/make.config
CRTI_OBJ     = $(ARCH_DIR)/crti.o
CRTN_OBJ     = $(ARCH_DIR)/crtn.o
CRTBEGIN_OBJ = $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ   = $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)

# Add flags supplied by our arch.
KERNEL_CFLAGS  += $(KERNEL_ARCH_CFLAGS)
KERNEL_LDFLAGS += $(KERNEL_ARCH_LDFLAGS)

# Order in which objects are linked.
KERNEL_OBJ_LINK_LIST = ${CRTI_OBJ} \
					   ${CRTBEGIN_OBJ} \
					   ${KERNEL_ARCH_OBJS} \
					   ${KERNEL_OBJS} \
					   ${CRTEND_OBJ} \
					   ${CRTN_OBJ}

# C flags used to build libc
LIBC_CFLAGS   =
LIBC_CXXFLAGS =

# libc source files
LIBC_OBJS    += $(patsubst %.c,%.o,$(wildcard libc/*/*.c))
LIBC_OBJS	 += $(patsubst %.c,%.o,$(wildcard libc/*.c))

# C flags used to build userspace programs.
USER_CFLAGS   =
USER_CXXFLAGS =

# Userspace source files.
USER_OBJS    = $(patsubst %.c,%.o,$(wildcard userspace/*/*/*/*.c))
USER_OBJS   += $(patsubst %.c,%.o,$(wildcard userspace/*/*/*.c))
USER_OBJS   += $(patsubst %.c,%.o,$(wildcard userspace/*/*.c))
USER_OBJS   += $(patsubst %.c,%.o,$(wildcard userspace/*.c))

# Emulator and arguments to pass to it.
EMU = qemu-system-i386
#EMU_ARGS  = -sdl -kernel zykernel -m 1024
EMU_ARGS  = -kernel zykernel -m 1024
EMU_ARGS += -hda $(HD_IMAGE_NAME) #-no-frame
EMU_ARGS += -rtc base=localtime -net nic,model=rtl8139 -net user

# Hard disk image generator.
GENEXT2FS = genext2fs
HD_IMAGE_NAME = zylix.img
HD_IMAGE_DIR = sysroot
HD_IMAGE_SIZE = 131072

# CD image generator.
CD_IMAGE_NAME = zylix-cd.iso
CD_IMAGE_DIR = sysroot
CD_IMAGE_SIZE = 131072

# Pretty output utilities.
BEG = tools/output/mk-beg
END = tools/output/mk-end
INFO = tools/output/mk-info
ERRORS = 2>>/.build-errors || tools/output/mk-error
ERRORSS = >>/.build-errors || tools/output/mk-error
BEGRM = tools/output/mk-beg-rm
ENDRM = tools/output/mk-end-rm

# Capture build error to a log.
ERRORS = 2>>./.build-errors

.PHONY: all system zykernel ctags userspace
.SECONDARY:
.SUFFIXES: 

all: system ctags install
system: zykernel libc.a userspace

###############################################################################
#                                   Kernel                                    #
###############################################################################

zykernel: ${CRTI_OBJ} ${CRTN_OBJ} ${KERNEL_ARCH_OBJS} ${KERNEL_OBJS}
	@${BEG} "LD" "zykernel"
	@${CC} -T $(ARCH_DIR)/linker.ld -o $@ ${KERNEL_CFLAGS} ${KERNEL_OBJ_LINK_LIST} ${KERNEL_LDFLAGS} ${KERNEL_LIBS} ${ERRORS}
	@${END} "LD" "zykernel"
	@${INFO} "--" "Finished building kernel."

kernel/%.o: kernel/%.c ${HEADERS}
	@${BEG} "CC" "$<"
	@${CC} ${KERNEL_CFLAGS} -g -I./kernel/include -c -o $@ $< ${ERRORS}
	@${END} "CC" "$<"

kernel/%.o: kernel/%.s
	@${BEG} "CC" "$<"
	@${AS} -c $< -o $@ ${ERRORS}
	@${END} "CC" "$<"

install-kernel:

install-kernel-headers:

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

libc/%.o: kernel/%.s
	@${BEG} "CC" "$<"
	@${AS} -c $< -o $@ ${ERRORS}
	@${END} "CC" "$<"

install-libc:

install-libc-headers:

###############################################################################
#                                  Userspace                                  #
###############################################################################

userspace: 
	@${BEG} "USER" "Building userspace binaries."
	@${END} "USER" "Userspace binaries built."
	@${INFO} "--" "Finished building userspace."

install-userspace:

install-userspace-headers:

###############################################################################
#                                  Toolchain                                  #
###############################################################################

toolchain:
	@${BEG} "TOOL" "Generating Zylix toolchain."
	@touch .toolchain-built
	@${END} "TOOL"

###############################################################################
#                                  Emulation                                  #
###############################################################################

run: zykernel zylix.img
	@${BEG} "EMU" "Running ${EMU}"
	@$(EMU) $(EMU_ARGS)
	@${END} "EMU" "Emulation ended."

###############################################################################
#                                  Disk Image                                 #
###############################################################################

zylix.img:
	@${BEG} "HDD" "Building emulation hard disk image."
	@$(GENEXT2FS) -d $(HD_IMAGE_DIR) -D tools/devtable -b $(HD_IMAGE_SIZE) -N 4096 $(HD_IMAGE_NAME)
	@${END} "HDD" "Finished building emulation image."

###############################################################################
#                                    CTags                                    #
###############################################################################

ctags:
	@${BEG} "CTAG" "Generating CTags..."
	@ctags -R zykernel
	@${END} "CTAG" "Done generating CTags."

###############################################################################
#                                    Install                                  #
###############################################################################

install: install-kernel install-kernel-headers install-libc install-libc-headers

###############################################################################
#                                   Clean-Up                                  #
###############################################################################

clean: clean-kernel clean-libc clean-tags clean-image clean-objects clean-arch-objects clean-build-errors

clean-kernel:
	@${BEGRM} "RM" "Cleaning kernel binary..."
	@rm -f zykernel
	@${ENDRM} "RM" "Cleaned kernel binary."

clean-libc:
	@${BEGRM} "RM" "Cleaning libc library..."
	@rm -f libc.a
	@${ENDRM} "RM" "Cleaned libc library."

clean-tags:
	@${BEGRM} "RM" "Cleaning CTags..."
	@rm -f tags
	@${ENDRM} "RM" "Cleaned CTags."

clean-image:
	@${BEGRM} "RM" "Cleaning emulation hard disk image..."
	@rm -f zylix.img
	@${ENDRM} "RM" "Cleaned emulation hard disk image."

clean-objects:
	@${BEGRM} "RM" "Cleaning kernel objects..."
	@rm -f ${KERNEL_OBJS}
	@${ENDRM} "RM" "Cleaned kernel objects."

clean-arch-objects:
	@${BEGRM} "RM" "Cleaning kernel arch-specific objects..."
	@rm -f ${KERNEL_ARCH_OBJS} ${CRTI_OBJ} ${CRTN_OBJ}
	@${ENDRM} "RM" "Cleaned kernel arch-specific objects."

clean-build-errors:
	@${BEGRM} "RM" "Cleaning build error log..."
	@rm -f .build-errors
	@${ENDRM} "RM" "Cleaned build error log."
