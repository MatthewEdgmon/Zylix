Zylix
=====

Build Instructions
------------------

Zylix needs to be built with a GCC cross compiler. See http://wiki.osdev.org/GCC_Cross-Compiler for instructions on how to build one. Then edit the Makefile's options to point to your cross compiler directory. Then invoke the makefile.

Dependencies
------------
To build Zylix, the following must be installed.

```
gcc 5.2.0 (x86_64 to i686-elf cross compiler)
genext2fs
qemu
```

Emulation
---------

Options for emulating Zylix are included in the Makefile for QEMU.
```
make run
```
