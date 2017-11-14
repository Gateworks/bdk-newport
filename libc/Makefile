# ***********************license start***********************************
# Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
# reserved.
#
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#   * Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#
#   * Neither the name of Cavium Inc. nor the names of
#     its contributors may be used to endorse or promote products
#     derived from this software without specific prior written
#     permission.
#
# This Software, including technical data, may be subject to U.S. export
# control laws, including the U.S. Export Administration Act and its
# associated regulations, and may be subject to export or import
# regulations in other countries.
#
# TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
# AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
# WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
# TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
# REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
# DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
# OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
# PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
# QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
# ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
# **********************license end**************************************

ifdef BDK_CLANG_ROOT
    USE_LLVM=1
endif

CROSS=aarch64-thunderx-elf
ifdef USE_LLVM
    LLVM_TARGET=-target aarch64-cavium-none-elf -march=armv8.1a+crypto
    export CC=$(BDK_CLANG_ROOT)/clang $(LLVM_TARGET) -ccc-gcc-name $(CROSS)-gcc
    export AR=$(BDK_CLANG_ROOT)/llvm-ar
    export AS=$(BDK_CLANG_ROOT)/llvm-as $(LLVM_TARGET)
    export RANLIB=$(BDK_CLANG_ROOT)/llvm-ranlib
else
    export CC=$(CROSS)-gcc
endif

CFLAGS := -D__FILENAME_MAX__=64
CFLAGS += -D__BUFSIZ__=4096
CFLAGS += -DREENTRANT_SYSCALLS_PROVIDED
CFLAGS += -g
CFLAGS += -Os
CFLAGS += -fno-asynchronous-unwind-tables
CFLAGS += -ffunction-sections
CFLAGS += -fshort-wchar
ifeq "$(BE)" "1"
CFLAGS += -mbig-endian
endif
export CFLAGS

NEWLIB_CONFIG := --host=$(CROSS)
NEWLIB_CONFIG += --target=$(CROSS)
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

${CROSS}/lib/libc.a: build/Makefile
	$(MAKE) -C build
	$(MAKE) -j1 -C build install

build/Makefile:
	rm -rf build
	mkdir build
	cd build && ../newlib-2.1.0/newlib/configure $(NEWLIB_CONFIG)

clean:
	rm -rf share build ${CROSS}

