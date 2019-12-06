# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
include $(BDK_ROOT)/libbdk/bdk.mk

.PHONY: all
all: init.bin.lzma.sign init.bin.sign

init.bin.lzma: init.bin
init.bin: app.bin
	$(BDK_ROOT)/bin/bdk-update-romfs $@ $^
init.bin.sign: init.bin $(BDK_ROOT)/trust-keys/bdk-sign-public.pem
	$(BDK_ROOT)/bin/bdk-sign bdk-sign-private $@ $<
init.bin.lzma.sign: init.bin.lzma $(BDK_ROOT)/trust-keys/bdk-sign-public.pem
	$(BDK_ROOT)/bin/bdk-sign bdk-sign-private $@ $<

#boardsrc := $(wildcard $(BDK_ROOT)/boards/*.c)
boardobjs = $(addsuffix .o, $(basename $(boardsrc)))
boarddeps = $(addsuffix .d, $(basename $(boardsrc)))

app: app.o devtree.o $(boardobjs) $(BDK_ROOT)/libbdk/libbdk.a
%.o: %.d
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
-include app.d devtree.d
endif
endif

clean:
	rm -f *.sign *.lzma *.o *.d *.map *.bin app
