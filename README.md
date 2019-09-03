# Zylix
An open-source, hobby/research kernel and operating system.

Before contributing, make sure to check the [coding style](https://github.com/MatthewEdgmon/Zylix/blob/master/STYLE.md) and the source code [license](https://github.com/MatthewEdgmon/Zylix/blob/master/LICENSE.md).

## Build Instructions
Zylix provides a script known to work under Cygwin and Arch Linux to download and compile a toolchain. Run ```tools/toolchain/build.sh```. Required programs, and steps to follow it the script breaks on your system are there. The compiler is set in the Makefile for an 8 core machine, make sure to set it accordingly to your system.

## Dependencies
To build Zylix and the toolchain the following software packages must be present in your system.

```
binutils (2.28 confirmed working)
gcc (7.1.0 confirmed working)
genext2fs (1.4.1 confirmed working) for hard disk image creation.
genisoimage (1.1.11 confirmed working) for live CD image creation.
patch
```

## Emulation
You can edit the arguments passed to the emulator in the top level Makefile. Some sample choices for different machines are listed below.
```
i386:
qemu-system-i386 -kernel ./sysroot/boot/zykernel -m 1024 -k en-us -show-cursor -vga std -net nic,model=rtl8139 -net user -rtc base=localtime

Raspberry Pi (Models 1 to 3):
qemu-system-arm -kernel ./sysroot/boot/zykernel -cpu arm1176 -m 256 -M raspi -serial stdio

```

## Licensing
See the file LICENSE.md for licensing information.
