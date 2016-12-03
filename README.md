# Zylix
An open-source, hobby/research kernel and operating system.

Before contributing, make sure to check the [coding style](https://github.com/MatthewEdgmon/Zylix/blob/master/STYLE.md) and the source code [license](https://github.com/MatthewEdgmon/Zylix/blob/master/LICENSE.md).

## Build Instructions
Zylix needs to be built with a GCC cross compiler. See [GCC Cross Compiler](http://wiki.osdev.org/GCC_Cross-Compiler) for instructions on how to build one. Then edit the Makefile in kernel and libc directories. The options you need to edit are within ten lines of the beginning. Then invoke the Makefile.

## Dependencies
To build Zylix, the following must be installed.

```
binutils 2.26
gcc 6.1.0
Both must be built from source to target your architecture.
genext2fs 1.4.1
```

## Emulation
QEMU is the emulator of choice for emulating Zylix. It will probably work on Bochs but it's not tested. You can edit the arguments passed to the emulator in the root Makefile. Some sample choices for different machines are listed below.
```
i386:
qemu-system-i386 -kernel ./sysroot/boot/zykernel -m 1024 -k en-us -show-cursor -vga std -net nic,model=rtl8139 -net user -rtc base=localtime

Raspberry Pi (Models 1 to 3):
qemu-system-arm -kernel ./sysroot/boot/zykernel -cpu arm1176 -m 256 -M raspi -serial stdio

```
