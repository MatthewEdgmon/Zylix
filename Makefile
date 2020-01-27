# Emulation image generators
GENEXT2FS = genext2fs
GENISOIMAGE = genisoimage
HD_IMAGE_NAME = zylix-hard-drive.img
HD_IMAGE_DIR = sysroot
HD_IMAGE_SIZE = 131072
ISO_IMAGE_NAME = zylix-el-torito.iso
ISO_IMAGE_DIR = sysroot
ISO_IMAGE_LABEL = ZylixAlpha

# Set your default emulator here.
EMU = $(VBOX)
EMU_ARGS = $(VBOX_ARGS)

# For multi-threaded compilation.
MAKE_ARGS = -j8 --output-sync
# For single-threaded compilation.
#MAKE_ARGS = -j1

QEMU = qemu-system-i386
QEMU_ARGS  = -kernel ./sysroot/boot/zykernel
# Arguments for storage and memory
QEMU_ARGS += -m 1024 -hda $(HD_IMAGE_NAME)
# Arguments for keyboard mouse and language
QEMU_ARGS += -k en-us -show-cursor
# Arguments for video
QEMU_ARGS += -vga std
# Arguments for network
QEMU_ARGS += -net nic,model=rtl8139 -net user
# Arguments for clock
QEMU_ARGS += -rtc base=localtime
# QEMU quick shutdown
QEMU_ARGS += -device isa-debug-exit,iobase=0xf4,iosize=0x04

VBOX = vboxmanage startvm "Zylix"
VBOX_ARGS =

BOCHS = bochs
BOCHS_ARGS = -q -f bochsrc.bxrc

# Text output colors.
include tools/pretty-print.inc

all: .toolchain-built build install ctags

.toolchain-built:
	@echo "It appears you have not built the Zylix toolchain yet. Please examine ./tools/toolchain/build.sh, and run it when you are ready to generate the toolchain."
	@exit

################################################################################
#                                  Build                                       #
################################################################################

build: build-libc build-kernel build-userspace

build-libc:
	@cd libc && $(MAKE) $(MAKE_ARGS) --no-print-directory

build-kernel: install-libc
	@cd kernel && $(MAKE) $(MAKE_ARGS) --no-print-directory

build-userspace:
	@cd userspace && $(MAKE) $(MAKE_ARGS) --no-print-directory

################################################################################
#                                  Ctags                                       #
################################################################################

ctags:
	@echo "Generating ctags..."
	@ctags --exclude=boot --exclude=libc --exclude=sysroot --exclude=tools --exclude=userspace --fields=+KSn -R .

################################################################################
#                                 Install                                      #
################################################################################

install: install-libc install-kernel install-userspace

install-libc: build-libc
	@cd libc && $(MAKE) $(MAKE_ARGS) install --no-print-directory

install-kernel: build-kernel
	@cd kernel && $(MAKE) $(MAKE_ARGS) install --no-print-directory

install-userspace: build-userspace
	@cd userspace && $(MAKE) $(MAKE_ARGS) install --no-print-directory

################################################################################
#                                  Clean                                       #
################################################################################

clean: clean-libc clean-kernel clean-userspace clean-image clean-ctags clean-trace

clean-libc:
	@cd libc && $(MAKE) --no-print-directory clean

clean-kernel:
	@cd kernel && $(MAKE) --no-print-directory clean

clean-userspace:
	@cd userspace && $(MAKE) --no-print-directory clean

clean-image:
	@echo "Cleaning emulation hard disk image..."
	@rm -f zylix-el-torito.iso
	@rm -f zylix-hard-drive.img
	@rm -f $(HD_IMAGE_DIR)/boot/zykernel
	@rm -r -f $(HD_IMAGE_DIR)/usr/lib/libc
	@rm -r -f $(HD_IMAGE_DIR)/usr/include/libc
	@rm -r -f $(HD_IMAGE_DIR)/usr/include/zykernel

clean-ctags:
	@echo "Cleaning ctags file..."
	@rm -f tags

clean-trace:
	@echo "Cleaning trace files..."
	@rm -f trace-*

################################################################################
#                                 Errors                                       #
################################################################################

errors: errors-libc errors-kernel errors-userspace

errors-libc:
	@cd libc && cat .build-log

errors-kernel:
	@cd kernel && cat .build-log

errors-userspace:
	@cd userspace && cat .build-log

################################################################################
#                                Emulation                                     #
################################################################################

zylix-hard-drive.img: install
	@echo "Building emulation hard disk image."
	@$(GENEXT2FS) -d $(HD_IMAGE_DIR) -D tools/devtable -b $(HD_IMAGE_SIZE) -N 4096 $(HD_IMAGE_NAME)

zylix-el-torito.iso: install
	@echo "Building an El Torito CD image."
	@$(GENISOIMAGE) -input-charset utf8 -quiet -V $(ISO_IMAGE_NAME) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $(ISO_IMAGE_NAME) $(ISO_IMAGE_DIR)

run: $(HD_IMAGE_NAME) $(ISO_IMAGE_NAME)
	@echo "Running ${EMU}"
	@$(EMU) $(EMU_ARGS)

qemu: $(HD_IMAGE_NAME) $(ISO_IMAGE_NAME)
	@echo "Running ${QEMU}"
	@$(QEMU) $(QEMU_ARGS)

bochs: $(HD_IMAGE_NAME) $(ISO_IMAGE_NAME)
	@echo "Running ${BOCHS}"
	@$(BOCHS) $(BOCHS_ARGS)

vbox: $(HD_IMAGE_NAME) $(ISO_IMAGE_NAME)
	@echo "Running ${VBOX}"
	@$(VBOX) $(VBOX_ARGS)
