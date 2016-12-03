# Point to your cross compiler.
CROSS_DIR = /home/matth_000/cross/bin

# Change TARGET_ARCH to match the platform you're targeting.
TARGET_ARCH  = i686
ARCH_DIR     = arch/$(TARGET_ARCH)
include        $(ARCH_DIR)/make.config

# Build using our cross compiler.
CC  = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-gcc
LD  = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-ld
NM  = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-nm
CXX = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-g++
AS  = $(CROSS_DIR)/$(KERNEL_ARCH_GCC_NAME)-as

# Flags used to build the kernel.
KERNEL_CFLAGS  = -O2 -std=c99
KERNEL_CFLAGS += -finline-functions -ffreestanding
KERNEL_CFLAGS += -fstack-protector-strong
KERNEL_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
KERNEL_CFLAGS += -pedantic -fno-omit-frame-pointer
# Choose between userspace and kernel version.
KERNEL_CFLAGS += -DZYLIX_LIBC_KERNEL
#LIBRARY_CFLAGS += -DZYLIX_LIBC_USERSPACE
KERNEL_LDFLAGS = -shared -Bsymbolic -z defs
KERNEL_LIBS    = -nostdlib -lc -lgcc

# Kernel headers.
KERNEL_INCLUDE_DIR = ./include
KERNEL_HEADERS = $(shell find include/ -type f -name '*.h')

# Kernel object files.
KERNEL_OBJS  = $(patsubst %.c,%.o,$(wildcard devices/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard filesystem/*/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard filesystem/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard memory/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard shell/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard structures/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard tasking/*.c))
KERNEL_OBJS += $(patsubst %.c,%.o,$(wildcard *.c))

# Kernel architecture specific files
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

# Where to put the finished kernel and headers.
SYSROOT = ../sysroot

.PHONY: all zykernel ctags install clean
.SECONDARY:
.SUFFIXES:

all: zykernel

################################################################################
#                                  Build                                       #
################################################################################

zykernel: ${CRTI_OBJ} ${CRTN_OBJ} ${KERNEL_ARCH_OBJS} ${KERNEL_OBJS}
	@${BEG} "LD" "zykernel"
	@${CC} -T $(ARCH_DIR)/linker.ld -o $@ ${KERNEL_CFLAGS} ${KERNEL_OBJ_LINK_LIST} ${KERNEL_LDFLAGS} ${KERNEL_LIBS} ${ERRORS}
	@${END} "LD" "zykernel"
	@${INFO} "--" "Finished building kernel."

%.o: %.c ${HEADERS}
	@${BEG} "CC" "$<"
	@${CC} ${KERNEL_CFLAGS} -g -I./include -c -o $@ $< ${ERRORS}
	@${END} "CC" "$<"

%.o: %.s
	@${BEG} "CC" "$<"
	@${AS} -c $< -o $@ ${ERRORS}
	@${END} "CC" "$<"

################################################################################
#                                 Install                                      #
################################################################################

install: install-kernel install-kernel-headers

install-kernel: zykernel
	@${BEG} "CP" "Copying kernel to sysroot."
	@rm -f $(SYSROOT)/boot/zykernel
	@cp zykernel $(SYSROOT)/boot
	@${END} "CP" "Copied kernel to sysroot."

install-kernel-headers: zykernel
	@${BEG} "CP" "Copying kernel headers to sysroot."
	@rm -r -f $(SYSROOT)/usr/include/zykernel
	@cp -RT ./include $(SYSROOT)/usr/include/zykernel
	@${END} "CP" "Copied kernel headers to sysroot."

################################################################################
#                                  Clean                                       #
################################################################################

clean: clean-arch-objects clean-objects clean-kernel clean-build-errors
	@${INFO} "--" "Cleaning complete."

clean-arch-objects:
	@${BEGRM} "RM" "Cleaning kernel arch-specific objects..."
	@rm -f ${KERNEL_ARCH_OBJS} ${CRTI_OBJ} ${CRTN_OBJ}
	@${ENDRM} "RM" "Cleaned kernel arch-specific objects."

clean-objects:
	@${BEGRM} "RM" "Cleaning kernel objects..."
	@rm -f ${KERNEL_OBJS}
	@${ENDRM} "RM" "Cleaned kernel objects."

clean-kernel:
	@${BEGRM} "RM" "Cleaning kernel binary..."
	@rm -f zykernel
	@${ENDRM} "RM" "Cleaned kernel binary."

clean-build-errors:
	@${BEGRM} "RM" "Cleaning build error log..."
	@rm -f .build-errors
	@rm -f trace-*
	@${ENDRM} "RM" "Cleaned build error log."
