# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

ifndef LIBC_DIR
    $(error LIBC_DIR not defined, supposed to be from higher level make)
endif

ifdef BDK_CLANG_ROOT
    USE_LLVM=1
endif

ifdef USE_LLVM
    LLVM_TARGET=-target aarch64-cavium-none-elf -march=armv8.1a+crypto
    export CC=$(BDK_CLANG_ROOT)/clang $(LLVM_TARGET) -ccc-gcc-name $(BDK_GCC_PREFIX)-gcc
    export AR=$(BDK_CLANG_ROOT)/llvm-ar
    export AS=$(BDK_CLANG_ROOT)/llvm-as $(LLVM_TARGET)
    export RANLIB=$(BDK_CLANG_ROOT)/llvm-ranlib
else
    export CC=$(BDK_GCC_PREFIX)-gcc
endif

CFLAGS := -D__FILENAME_MAX__=64
CFLAGS += -D__BUFSIZ__=4096
CFLAGS += -DREENTRANT_SYSCALLS_PROVIDED
CFLAGS += -g
CFLAGS += $(BDK_OPTIMIZE)
CFLAGS += -fno-asynchronous-unwind-tables
CFLAGS += -ffunction-sections
CFLAGS += -fshort-wchar
CFLAGS += -ffreestanding
ifeq "$(BE)" "1"
CFLAGS += -mbig-endian
endif
export CFLAGS

NEWLIB_CONFIG := --host=$(LIBC_DIR)
NEWLIB_CONFIG += --target=$(LIBC_DIR)
NEWLIB_CONFIG += --silent
NEWLIB_CONFIG += --prefix=$(BDK_ROOT)/libc
NEWLIB_CONFIG += --disable-newlib-io-pos-args
NEWLIB_CONFIG += --disable-newlib-mb
NEWLIB_CONFIG += --disable-newlib-io-c99-formats
NEWLIB_CONFIG += --disable-newlib-register-fini
NEWLIB_CONFIG += --enable-newlib-io-long-long
NEWLIB_CONFIG += --disable-newlib-reent-small
NEWLIB_CONFIG += --disable-newlib-fseek-optimization
NEWLIB_CONFIG += --disable-newlib-wide-orient
NEWLIB_CONFIG += --disable-newlib-nano-malloc # Enabling causes stack alignment issues
NEWLIB_CONFIG += --enable-target-optspace
NEWLIB_CONFIG += --enable-newlib-multithread
NEWLIB_CONFIG += --disable-newlib-iconv
NEWLIB_CONFIG += --disable-multilib
NEWLIB_CONFIG += --disable-newlib-io-float
NEWLIB_CONFIG += --disable-malloc-debugging

${LIBC_DIR}/lib/libc.a: build/Makefile
	$(MAKE) -C build
	$(MAKE) -j1 -C build install

build/Makefile:
	rm -rf build
	mkdir build
	cd build && ../newlib-2.1.0/newlib/configure $(NEWLIB_CONFIG)

clean:
	rm -rf share build ${LIBC_DIR}

