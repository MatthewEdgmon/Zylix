# Point to your local i686 elf cross compiler.
#CROSS_DIR = /usr/cross/bin
CROSS_DIR = /cygdrive/F/Development/OS/toolchain-testing/output/bin

# Build using our cross compiler.
CC  = $(CROSS_DIR)/i686-pc-zylix-gcc
LD  = $(CROSS_DIR)/i686-pc-zylix-ld
NM  = $(CROSS_DIR)/i686-pc-zylix-nm
CXX = $(CROSS_DIR)/i686-pc-zylix-g++
AS  = $(CROSS_DIR)/i686-pc-zylix-as

# Flags used to build the library.
CFLAGS  = -O2 -std=c99
CFLAGS += -finline-functions
CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter
CFLAGS += -pedantic -fno-omit-frame-pointer
CFLAGS += -DZYLIX_LIBC_USERSPACE
LDFLAGS = -z defs
LIBS    = -lc -lgcc

OBJECTS += hello.o

all: hello

hello: hello.c
	@${CC} -T ../link.ld -o $@

clean:
	rm -rf hello.o hello
