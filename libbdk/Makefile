# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

include bdk.mk

ifndef LIBC_DIR
    $(error LIBC_DIR not defined, supposed to be from higher level make)
endif

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
dirs += libbdk-boot
dirs += libfdt
dirs += libbdk-hal/usb
dirs += liblzma
dirs += libuecc
dirs += libcavm-gsern
dirs += libcoremark

usbdir := libbdk-hal/usb
usbsrc := $(foreach d,$(usbdir),$(BDK_ROOT)/$(d)/*.[cS])
usbsrc := $(wildcard $(usbsrc))
usbobjs = $(addsuffix .o, $(basename $(usbsrc)))
usbdeps = $(addsuffix .d, $(basename $(usbsrc)))

$(usbobjs) $(usbdeps): CPPFLAGS += -I $(BDK_ROOT)/$(usbdir)

include $(BDK_ROOT)/libphy/phy.mk

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
# automatically add all these functions to the octeontx.c Lua module, allowing
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
	rm -rf $(X6141_SBUS_MASTER_BIN) $(X6141_SERDES_BIN)
distclean: clean
	rm -f $(deps)

$(BDK_ROOT)/libbdk-hal/if/bdk-if.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libbdk-hal/bdk-nic.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libbdk-hal/bdk-nix-common.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libbdk-hal/bdk-pko.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libbdk-lua/trafficgen.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch

include $(BDK_ROOT)/libphy/marvell-88x6141/mydFwImages.mk

$(BDK_ROOT)/libcoremark/*.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libcoremark/core_list_join.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libcoremark/core_main.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libcoremark/core_matrix.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libcoremark/core_portme.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libcoremark/core_state.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libcoremark/core_util.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
$(BDK_ROOT)/libcoremark/cvt.o: CFLAGS+=$(BDK_OPTIMIZE_CRITICAL) -Wno-invalid-pch
