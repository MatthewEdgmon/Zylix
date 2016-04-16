# Zylix
An open-source, hobby/research kernel and operating system.

Before contributing, make sure to check the [coding style](https://github.com/MatthewEdgmon/Zylix/blob/master/STYLE.md) and the source code [license](https://github.com/MatthewEdgmon/Zylix/blob/master/LICENSE.md).

## Build Instructions
Zylix needs to be built with a GCC cross compiler. See [GCC Cross Compiler](http://wiki.osdev.org/GCC_Cross-Compiler) for instructions on how to build one. Then edit the Makefile's options to point to your cross compiler directory. Then invoke the makefile.

## Dependencies
To build Zylix, the following must be installed.

```
binutils 2.26 (x86_64 to i686-elf cross compiler)
gcc 5.3.0 (x86_64 to i686-elf cross compiler)
genext2fs
```

## Emulation
Options for emulating Zylix are included in the Makefile for QEMU.
```
make run
```
