#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Multi-threaded build
MAKEFLAGS="-j8 --output-sync"
# Single-threaded build
#MAKEFLAGS=

# BUILD CONFIGURATION OPTIONS
# Toolchain versions, this should match the filname of the tarball minus extension
GCC=gcc-7.1.0
BINUTILS=binutils-2.28
# Toolchain and building options
PREFIX=$DIR/local
TARGET=i686-pc-zylix
# This is relative to the build directories, not the script directory.
SYSROOT=$DIR/../../sysroot

function main() {

    if [ -f $DIR/../../.toolchain-built ]; then
        echo "Toolchain already built, will rebuild in 10 seconds."
        for i in {10..1};do echo -n "$i." && sleep 1; done
        echo
        clean
    fi

    command_check wget
	command_check tar
	command_check find
	command_check patch
	command_check make
    command_check gcc
    command_check genisoimage
    command_check genext2fs

    echo "Building toolchain in $PREFIX targeting $TARGET at sysroot $SYSROOT"

    echo "Preparing system root."
	mkdir -p $DIR/../../sysroot/bin
	mkdir -p $DIR/../../sysroot/boot
	mkdir -p $DIR/../../sysroot/dev
	mkdir -p $DIR/../../sysroot/etc
	mkdir -p $DIR/../../sysroot/home/Zylix
	mkdir -p $DIR/../../sysroot/lib
	mkdir -p $DIR/../../sysroot/media
	mkdir -p $DIR/../../sysroot/mnt
	mkdir -p $DIR/../../sysroot/opt
	mkdir -p $DIR/../../sysroot/proc
	mkdir -p $DIR/../../sysroot/root
	mkdir -p $DIR/../../sysroot/tmp
	mkdir -p $DIR/../../sysroot/usr
	mkdir -p $DIR/../../sysroot/var

	echo "Copying C library headers to sysroot."
	directory_check $DIR/../../sysroot/usr/include
	(cd $DIR/../../libc/include && find . -name '*.h' -print | tar --create --files-from -) | (cd $DIR/../../sysroot/usr/include/ && tar xvfp -)

    directory_check $DIR/download
    pushd $DIR/download > /dev/null
        download_and_extract "ftp://ftp.gnu.org/gnu/gcc/$GCC/" $GCC ".tar.bz2"
        download_and_extract "ftp://ftp.gnu.org/gnu/binutils/" $BINUTILS ".tar.bz2"

        apply_patch $GCC
        apply_patch $BINUTILS
    popd > /dev/null

    directory_check $DIR/local
    directory_check $DIR/build-binutils
    pushd $DIR/build-binutils > /dev/null
        $DIR/download/$BINUTILS/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot=$SYSROOT --disable-werror --disable-nls --disable-libssp
        make $MAKEFLAGS
        make install
    popd > /dev/null

    directory_check $DIR/build-gcc
    pushd $DIR/build-gcc > /dev/null
        $DIR/download/$GCC/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot=$SYSROOT --enable-languages=c,c++ --disable-nls --disable-libssp
        make $MAKEFLAGS all-gcc all-target-libgcc
        make install-gcc install-target-libgcc
    popd > /dev/null

    touch $DIR/../../.toolchain-built
}

function directory_check() {
    if [ ! -d $1 ]; then
        mkdir -p $1
    fi
}

function command_check() {
    command -v $1 >/dev/null 2>&1 || { echo "Command "$1" was not found on your system, ensure the software is installed and run build.sh again."; exit 1; }
}

function download_and_extract() {

    if [ ! -f "$2$3" ]; then
        echo "Downloading $2$3 from $1"
        wget -q "$1$2$3"
    else
        echo "File $2$3 already exists. Skipping download."
    fi

    if [ ! -d "./$2" ]; then
        echo "Extracting $2$3"
        tar -xf $2$3
    else
        echo "Directory $2 already exists. Skipping extraction."
    fi

}

function apply_patch() {
    echo Patching $1
	pushd $1 > /dev/null
    patch -p2 < $DIR/patches/$1.patch > /dev/null
	popd > /dev/null
}

function clean() {
    rm -rf $DIR/local
    rm -rf $DIR/build-gcc
    rm -rf $DIR/build-binutils
    rm -rf $DIR/download/gcc-*
    rm -rf $DIR/download/binutils-*
    rm -f  $DIR/../../.toolchain-built
    rm -rf $SYSROOT/usr/include
}

main "$@"
