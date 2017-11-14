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

include bdk.mk

#
# These are the directories where source files are found
#
dirs  = libbdk-arch
dirs += libbdk-hal
dirs += libbdk-hal/if
dirs += libbdk-hal/qlm
dirs += libbdk-hal/device
dirs += libbdk-os
dirs += libbdk-dram
dirs += libbdk-driver
dirs += libbdk-trust
dirs += liblua
dirs += libbdk-lua
dirs += libdram
dirs += libdram/configs
dirs += libfatfs
dirs += libbdk-bist
dirs += libbdk-boot
dirs += libfdt
dirs += libbdk-hal/usb
dirs += liblzma
dirs += libuecc
# aquantia support and interface to it
dirs += libbdk-hal/aq_api
dirs += libbdk-hal/aq_api/src

usbdir := libbdk-hal/usb
usbsrc := $(foreach d,$(usbdir),$(BDK_ROOT)/$(d)/*.[cS])
usbsrc := $(wildcard $(usbsrc))
usbobjs = $(addsuffix .o, $(basename $(usbsrc)))
usbdeps = $(addsuffix .d, $(basename $(usbsrc)))

$(usbobjs) $(usbdeps): CPPFLAGS += -I $(BDK_ROOT)/$(usbdir)

#
# extra rules for aquantia support subtree, it needs more include files
#
aqrifdir := libbdk-hal/aq_api
aqrdir := libbdk-hal/aq_api/src
aqrinc := libbdk-hal/aq_api/include
aqrinc1 := libbdk-hal/aq_api/include/registerMap
aqrinc2 := libbdk-hal/aq_api/include/registerMap/APPIA
aqrinc3 := libbdk-hal/aq_api/include/registerMap/HHD
aqrinc4 := libbdk-hal/aq_api/include/registerMap/EUR
aqrsrc := $(foreach d,$(aqrdir),$(BDK_ROOT)/$(d)/*.[cS]) $(foreach d,$(aqrifdir),$(BDK_ROOT)/$(d)/*.[cS])
aqrsrc := $(wildcard $(aqrsrc))
aqrobjs = $(addsuffix .o, $(basename $(aqrsrc)))
aqrdeps = $(addsuffix .d, $(basename $(aqrsrc)))

$(aqrobjs) $(aqrdeps): CPPFLAGS += -I $(BDK_ROOT)/$(aqrdir) -I $(BDK_ROOT)/$(aqrinc) -I $(BDK_ROOT)/$(aqrinc1) -I $(BDK_ROOT)/$(aqrinc2) -I $(BDK_ROOT)/$(aqrinc3) -I $(BDK_ROOT)/$(aqrinc4)

#
# Create a list of all source files
#
src := $(foreach d,$(dirs),$(BDK_ROOT)/$(d)/*.[cS])
src := $(wildcard $(src))

ifeq (,$(findstring bdk-microcode-cn8xxx,$(src)))
    # The wildcard will find it if the link is already there, otherwise
    # we must add it
    src += $(BDK_ROOT)/libbdk-hal/if/bdk-microcode-cn8xxx.c
endif

#
# Create a list of all objects and depends files
#
objs = $(addsuffix .o, $(basename $(src)))
deps = $(addsuffix .d, $(basename $(src)))

#
# The library depends on the precompiled header and all the object files
#
.DEFAULT: $(BDK_ROOT)/libbdk/libbdk.a
$(BDK_ROOT)/libbdk/libbdk.a: $(objs) bdk-functions.o $(BDK_ROOT)/libc/${LIBC_DIR}/lib/libc.a
	rm -f $@
	$(AR) qc $@ $(objs) bdk-functions.o
	rm -rf tmp
	mkdir tmp
	cd tmp && $(AR) x $(BDK_ROOT)/libc/${LIBC_DIR}/lib/libc.a
	cd tmp && $(AR) x $(BDK_ROOT)/libc/${LIBC_DIR}/lib/libg.a
	cd tmp && $(AR) x $(BDK_ROOT)/libc/${LIBC_DIR}/lib/libm.a
	$(AR) r $@ tmp/*
	rm -rf tmp

#
# bdk-functions.c is a generated file that contains a mapping of function name
# to function pointer for all functions starting with bdk_. This is used to
# automatically add all these functions to the cavium.c Lua module, allowing
# direct function calling.
#
bdk-functions.c: ./create_function_table.py $(objs)
	./create_function_table.py $@ $(objs)

#
# PKI needs microcode to function. The file bdk-microcode-cn8xxx.c is generated
# from an ELF file maintained by the hardware team that contains this microcode.
#
$(BDK_ROOT)/libbdk-hal/if/bdk-microcode-cn8xxx.c: $(BDK_ROOT)/target-bin/ipemainc.elf
	$(BDK_ROOT)/bin/bdk-convert-pki-elf $^ $@

ifndef USE_LLVM
#
# These are needed to make bdk.h.gch
# The -M creates the dependencies to stdout
# The -MP creates fake target for .h files so make won't complain on include changes
# The -MT changes the target to match our object file name
#
deps += $(BDK_ROOT)/libbdk/bdk.d
$(BDK_ROOT)/libbdk/bdk.h.gch: $(BDK_ROOT)/libbdk/bdk.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(BDK_ROOT)/libbdk/bdk.h
$(BDK_ROOT)/libbdk/bdk.d: $(BDK_ROOT)/libbdk/bdk.h
	$(CC) $(CFLAGS) -I $(BDK_ROOT) -M -MP -MT $(basename $@).h.gch $< > $@
$(objs): $(BDK_ROOT)/libbdk/bdk.h.gch
endif

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)

#
# Include all the depends files
#
-include $(deps)

endif
endif
#
# Clean targets
#
clean:
	rm -rf $(BDK_ROOT)/libbdk/libbdk.a $(objs) tmp bdk-functions.[cdo] bdk.h.d bdk.h.gch $(BDK_ROOT)/libbdk-hal/if/bdk-microcode-cn8xxx.c
distclean: clean
	rm -f $(deps)

$(BDK_ROOT)/libbdk-hal/if/bdk-if.o: CFLAGS+=-O3 -Wno-invalid-pch
$(BDK_ROOT)/libbdk-lua/trafficgen.o: CFLAGS+=-O3 -Wno-invalid-pch
