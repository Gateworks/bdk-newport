# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

LIBC_DIR?=aarch64-marvell-elf
export LIBC_DIR

# Optimization level to use for the BDK and C library
BDK_OPTIMIZE?=-Os
export BDK_OPTIMIZE
# Optimization level to use speed critical parts of the BDK
BDK_OPTIMIZE_CRITICAL?=-O3
export BDK_OPTIMIZE_CRITICAL

ifndef BDK_ROOT
    $(error Define BDK_ROOT in the environment)
endif
ifndef BDK_GCC_ROOT
    GCC=$(shell which $(LIBC_DIR)-gcc)
    ifeq "$(GCC)" ""
        $(error BDK_GCC_ROOT not set and $(LIBC_DIR)-gcc not found)
    endif
    BDK_GCC_ROOT=$(abspath $(dir $(GCC))/..)
    export BDK_GCC_ROOT
    $(info BDK_GCC_ROOT not set, assuming $(BDK_GCC_ROOT))
endif
ifdef BDK_CLANG_ROOT
    USE_LLVM=1
endif


BDK_LINK_ADDRESS?=0x0 # Node 0
#BDK_LINK_ADDRESS?=0x10000000000 # Node 1

SHELL=/bin/bash

#
# Optional compile time flags for the BDK
#
#override BDK_EXTRA_CPPFLAGS += -DBDK_SHOW_BOOT_BANNERS=0

#
# Setup the compiler for the BDK libraries
#
BDK_GCC_PREFIX=$(BDK_GCC_ROOT)/bin/$(LIBC_DIR)
export BDK_GCC_PREFIX
PATH:=$(PATH):$(BDK_GCC_ROOT)/bin
export PATH
ifdef USE_LLVM
    LLVM_TARGET=-target aarch64-cavium-none-elf -march=armv8.1a+crypto
    CC=$(BDK_CLANG_ROOT)/clang $(LLVM_TARGET) -ccc-gcc-name $(LIBC_DIR)-gcc
    AR=$(BDK_CLANG_ROOT)/llvm-ar
    AS=$(BDK_CLANG_ROOT)/llvm-as $(LLVM_TARGET)
    RANLIB=$(BDK_CLANG_ROOT)/llvm-ranlib
    OBJCOPY=$(BDK_GCC_PREFIX)-objcopy
    OBJDUMP=$(BDK_CLANG_ROOT)/llvm-objdump
else
    CC=$(BDK_GCC_PREFIX)-gcc
    AR=$(BDK_GCC_PREFIX)-ar
    AS=$(BDK_GCC_PREFIX)-as
    RANLIB=$(BDK_GCC_PREFIX)-ranlib
    OBJCOPY=$(BDK_GCC_PREFIX)-objcopy
    OBJDUMP=$(BDK_GCC_PREFIX)-objdump
endif

#
# Setup the compile flags
#
CPPFLAGS  = -Wundef $(BDK_EXTRA_CPPFLAGS)
CPPFLAGS += -I $(BDK_ROOT)/libbdk
CPPFLAGS += -I $(BDK_ROOT)/liblua
CPPFLAGS += -I $(BDK_ROOT)/libc/${LIBC_DIR}/include
CPPFLAGS += -I $(BDK_ROOT)/libfdt
CPPFLAGS += -I $(BDK_ROOT)/libcoremark
CPPFLAGS += -I $(BDK_ROOT)

CFLAGS  = -Wall
CFLAGS += -Wextra
CFLAGS += -Wno-unused-parameter
CFLAGS += -Winline
CFLAGS += -Winvalid-pch
ifndef USE_LLVM
    CFLAGS += -mcpu=thunderx+lse
    CFLAGS += -flto -ffat-lto-objects # Link time optimization for smaller size
    # GCC7 creates a whole bunch of flase warnings with -Wformat-truncation
    GCCVERSIONGTEQ7 := $(shell expr $(shell $(CC) -dumpversion | cut -f1 -d.) \>= 7)
    ifeq "$(GCCVERSIONGTEQ7)" "1"
        CFLAGS += -Wno-format-truncation
    endif
endif
CFLAGS += $(BDK_OPTIMIZE) -g
CFLAGS += -std=gnu11
CFLAGS += -ffreestanding
CFLAGS += -fno-asynchronous-unwind-tables
CFLAGS += -ffunction-sections
CFLAGS += -fshort-wchar
CFLAGS += -MP -MD

# Allow changing where ATF non-secure is loaded from
ifdef ATF_NONSECURE_FLASH_ADDRESS
    # Export so python utilities can resize the FatFS as needed. Used by
    # utils/scripts/bdk-create-fatfs-image.py
    export ATF_NONSECURE_FLASH_ADDRESS
    # Make available in C code as a define. Used by apps/init/app.c
    CFLAGS += -DATF_NONSECURE_FLASH_ADDRESS=$(ATF_NONSECURE_FLASH_ADDRESS)
endif

ASFLAGS = $(CFLAGS)

LDFLAGS  = -nostdlib
LDFLAGS += -nostartfiles
LDFLAGS += -Wl,-T
LDFLAGS += -Wl,bdk.ld
LDFLAGS += -Wl,-Map
LDFLAGS += -Wl,$@.map
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--defsym=BDK_LINK_ADDRESS=$(BDK_LINK_ADDRESS)
LDFLAGS += -L $(BDK_ROOT)/libbdk
LDFLAGS += $(BDK_ROOT)/libbdk-os/bdk-start.o

LDLIBS  = -lbdk
ifndef USE_LLVM
    LDLIBS += -lgcc
    LDFLAGS += -mcpu=thunderx+lse
endif

ifeq "$(BE)" "1"
CFLAGS += -mbig-endian
LDFLAGS += -mbig-endian
endif

# This leaves off the bits [63:40] as these contain the node ID, which we don't want
IMAGE_END=`$(OBJDUMP) -t $^ | grep " _end$$" | sed "s/^00000[0-9]\([0-9a-f]*\).*/print 0x\1/g" | python2`

#
# Convert an ELF file into a binary
#
%.bin: %
	$(OBJCOPY) $^ -O binary $@
	truncate -s $(IMAGE_END) $@
	$(BDK_ROOT)/bin/bdk-update-romfs $@ $@

#
# Compress an image. Use "-1" for small dictionary as normal "-7"
# can use many megabytes. "-1" seems to use 64KB
#
%.lzma: %
	$(BDK_ROOT)/bin/lzma e $^ $@



