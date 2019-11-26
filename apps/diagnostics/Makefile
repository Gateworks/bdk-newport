# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

include $(BDK_ROOT)/libbdk/bdk.mk

.PHONY: all
all: diagnostics.bin.lzma.sign

diagnostics.bin.lzma: diagnostics.bin
diagnostics.bin: app.bin lua/*
	$(BDK_ROOT)/bin/bdk-update-romfs $@ $^
diagnostics.bin.lzma.sign: diagnostics.bin.lzma $(BDK_ROOT)/trust-keys/bdk-sign-public.pem
	$(BDK_ROOT)/bin/bdk-sign bdk-sign-private $@ $<

ifndef USE_LLVM
app: LDFLAGS+=-fno-lto
endif
app: app.o $(BDK_ROOT)/libbdk/libbdk.a
%.o: %.d
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
-include app.d
endif
endif

clean:
	rm -f *.sign *.lzma *.o *.d *.map *.bin app
