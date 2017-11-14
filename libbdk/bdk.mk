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

ifndef BDK_ROOT
    $(error Define BDK_ROOT in the environment)
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
LIBC_DIR=aarch64-thunderx-elf
ifdef USE_LLVM
    LLVM_TARGET=-target aarch64-cavium-none-elf -march=armv8.1a+crypto
    CC=$(BDK_CLANG_ROOT)/clang $(LLVM_TARGET) -ccc-gcc-name $(LIBC_DIR)-gcc
    AR=$(BDK_CLANG_ROOT)/llvm-ar
    AS=$(BDK_CLANG_ROOT)/llvm-as $(LLVM_TARGET)
    RANLIB=$(BDK_CLANG_ROOT)/llvm-ranlib
    OBJCOPY=$(LIBC_DIR)-objcopy
else
    CC=$(LIBC_DIR)-gcc
    AR=$(LIBC_DIR)-ar
    AS=$(LIBC_DIR)-as
    RANLIB=$(LIBC_DIR)-ranlib
    OBJCOPY=$(LIBC_DIR)-objcopy
endif

#
# Setup the compile flags
#
CPPFLAGS  = -Wundef $(BDK_EXTRA_CPPFLAGS)
CPPFLAGS += -I $(BDK_ROOT)/libbdk
CPPFLAGS += -I $(BDK_ROOT)/liblua
CPPFLAGS += -I $(BDK_ROOT)/libc/${LIBC_DIR}/include
CPPFLAGS += -I $(BDK_ROOT)/libfdt
CPPFLAGS += -I $(BDK_ROOT)

CFLAGS  = -Wall
CFLAGS += -Wextra
CFLAGS += -Wno-unused-parameter
CFLAGS += -Winline
CFLAGS += -Winvalid-pch
ifndef USE_LLVM
    CFLAGS += -mcpu=thunderx+lse
    CFLAGS += -flto -ffat-lto-objects # Link time optimization for smaller size
endif
CFLAGS += -Os -g
CFLAGS += -std=gnu11
CFLAGS += -fno-asynchronous-unwind-tables
CFLAGS += -ffunction-sections
CFLAGS += -fshort-wchar
CFLAGS += -MP -MD

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
IMAGE_END=`$(LIBC_DIR)-objdump -t $^ | grep " _end$$" | sed "s/^00000[0-9]\([0-9a-f]*\).*/print 0x\1/g" | python`

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
	$(BDK_ROOT)/bin/bdk-aes-pad $@



