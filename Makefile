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

# Pretty output utilities.
BEG = tools/output/mk-beg
END = tools/output/mk-end
INFO = tools/output/mk-info
ERRORS = 2>>/.build-errors || tools/output/mk-error
ERRORSS = >>/.build-errors || tools/output/mk-error
BEGRM = tools/output/mk-beg-rm
ENDRM = tools/output/mk-end-rm

all: .toolchain-built build install ctags

################################################################################
#                                  Build                                       #
################################################################################

build: build-libc build-kernel build-userspace

build-libc:
	@cd libc && $(MAKE) --no-print-directory

build-kernel: install-libc
	@cd kernel && $(MAKE) --no-print-directory

build-userspace:
	@cd userspace && $(MAKE) --no-print-directory

################################################################################
#                                  Ctags                                       #
################################################################################

ctags:
	@${BEG} "CTAG" "Generating ctags..."
	@ctags --exclude=boot --exclude=libc --exclude=sysroot --exclude=tools --exclude=userspace --fields=+KSn -R .
	@${END} "CTAG" "Generated ctags."

################################################################################
#                                 Install                                      #
################################################################################

install: install-libc install-kernel install-userspace

install-libc: build-libc
	@cd libc && $(MAKE) install --no-print-directory

install-kernel: build-kernel
	@cd kernel && $(MAKE) install --no-print-directory

install-userspace: build-userspace
	@cd userspace && $(MAKE) install --no-print-directory

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
	@${BEGRM} "RM" "Cleaning emulation hard disk image..."
	@rm -f zylix.img
	@rm -f $(HD_IMAGE_DIR)/boot/zykernel
	@rm -r -f $(HD_IMAGE_DIR)/usr/lib/libc
	@rm -r -f $(HD_IMAGE_DIR)/usr/include/libc
	@rm -r -f $(HD_IMAGE_DIR)/usr/include/zykernel
	@${ENDRM} "RM" "Cleaned emulation hard disk image."

clean-ctags:
	@${BEGRM} "RM" "Cleaning ctags file..."
	@rm -f tags
	@${ENDRM} "RM" "Cleaned ctags file"

clean-trace:
	@${BEGRM} "RM" "Cleaning trace files..."
	@rm -f trace-*
	@${ENDRM} "RM" "Cleaned trace files."

################################################################################
#                                 Errors                                       #
################################################################################

errors: errors-libc errors-kernel errors-userspace

errors-libc:
	@cd libc && cat .build-errors

errors-kernel:
	@cd kernel && cat .build-errors

errors-userspace:
	@cd userspace && cat .build-errors

################################################################################
#                                Emulation                                     #
################################################################################

zylix-hard-drive.img: install
	@${BEG} "HDD" "Building emulation hard disk image."
	@$(GENEXT2FS) -d $(HD_IMAGE_DIR) -D tools/devtable -b $(HD_IMAGE_SIZE) -N 4096 $(HD_IMAGE_NAME)
	@${END} "HDD" "Finished building emulation image."
	@${INFO} "--" "Hard disk image for Zylix is available."

zylix-el-torito.iso: install
	@${BEG} "ISO" "Building an El Torito CD image."
	@$(GENISOIMAGE) -input-charset utf8 -quiet -V $(ISO_IMAGE_NAME) -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $(ISO_IMAGE_NAME) $(ISO_IMAGE_DIR)
	@${END} "ISO" "Finished building El Torito CD image."
	@${INFO} "--" "ISO image for Zylix is available."

run: $(HD_IMAGE_NAME) $(ISO_IMAGE_NAME)
	@${BEG} "EMU" "Running ${EMU}"
	@$(EMU) $(EMU_ARGS)
	@${END} "EMU" "Emulation ended."

qemu: $(HD_IMAGE_NAME) $(ISO_IMAGE_NAME)
	@${BEG} "EMU" "Running ${QEMU}"
	@$(QEMU) $(QEMU_ARGS)
	@${END} "EMU" "Emulation ended."

bochs: $(HD_IMAGE_NAME) $(ISO_IMAGE_NAME)
	@${BEG} "EMU" "Running ${BOCHS}"
	@$(BOCHS) $(BOCHS_ARGS)
	@${END} "EMU" "Emulation ended."

vbox: $(HD_IMAGE_NAME) $(ISO_IMAGE_NAME)
	@${BEG} "EMU" "Running ${VBOX}"
	@$(VBOX) $(VBOX_ARGS)
	@${END} "EMU" "Emulation ended."
