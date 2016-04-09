
# Emulator and arguments to pass to it.
EMU = qemu-system-i386
EMU_ARGS  = -kernel ./sysroot/boot/zykernel
# Arguments for storage and memory
EMU_ARGS += -m 1024 -hda $(HD_IMAGE_NAME)
# Arguments for keyboard mouse and language
EMU_ARGS += -k en-us -show-cursor
# Arguments for video
EMU_ARGS += -vga std
# Arguments for network
EMU_ARGS += -net nic,model=rtl8139 -net user
# Arguments for clock
EMU_ARGS += -rtc base=localtime

# Hard disk image generator.
GENEXT2FS = genext2fs
HD_IMAGE_NAME = zylix.img
HD_IMAGE_DIR = sysroot
HD_IMAGE_SIZE = 131072

# Pretty output utilities.
BEG = tools/output/mk-beg
END = tools/output/mk-end
INFO = tools/output/mk-info
ERRORS = 2>>/.build-errors || tools/output/mk-error
ERRORSS = >>/.build-errors || tools/output/mk-error
BEGRM = tools/output/mk-beg-rm
ENDRM = tools/output/mk-end-rm

all: build install

################################################################################
#                                  Build                                       #
################################################################################

build: build-libc build-kernel build-userspace

build-libc:
	@cd libc && $(MAKE) --no-print-directory

build-kernel:
	@cd kernel && $(MAKE) --no-print-directory

build-userspace:
	@cd userspace && $(MAKE) --no-print-directory

################################################################################
#                                  Ctags                                       #
################################################################################

ctags: ctags-libc ctags-kernel ctags-userspace

ctags-libc:
	@cd libc && $(MAKE) ctags --no-print-directory

ctags-kernel:
	@cd kernel && $(MAKE) ctags --no-print-directory

ctags-userspace:
	@cd userspace && $(MAKE) ctags --no-print-directory

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

clean: clean-libc clean-kernel clean-userspace clean-image clean-trace

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

zylix.img: install
	@${BEG} "HDD" "Building emulation hard disk image."
	@$(GENEXT2FS) -d $(HD_IMAGE_DIR) -D tools/devtable -b $(HD_IMAGE_SIZE) -N 4096 $(HD_IMAGE_NAME)
	@${END} "HDD" "Finished building emulation image."
	@${INFO} "--" "Hard disk image for Zylix is available."

run: zylix.img
	@${BEG} "EMU" "Running ${EMU}"
	@$(EMU) $(EMU_ARGS)
	@${END} "EMU" "Emulation ended."
