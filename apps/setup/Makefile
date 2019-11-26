# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

include $(BDK_ROOT)/libbdk/bdk.mk

.PHONY: all
all: setup.bin.lzma.sign

SRC =app.c
SRC+=$(wildcard menu-*.c)
OBJ=$(SRC:.c=.o)
DEPS=$(SRC:.c=.d)
DEPS+=$(BDK_ROOT)/libbdk/bdk.d

setup.bin.lzma: setup.bin
setup.bin: app.bin
	$(BDK_ROOT)/bin/bdk-update-romfs $@ $^
setup.bin.lzma.sign: setup.bin.lzma $(BDK_ROOT)/trust-keys/bdk-sign-public.pem
	$(BDK_ROOT)/bin/bdk-sign bdk-sign-private $@ $<

ifndef USE_LLVM
app: LDFLAGS+=-fno-lto
endif
app: $(OBJ) $(BDK_ROOT)/libbdk/libbdk.a
%.o: %.d
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
-include $(DEPS)
endif
endif

clean:
	rm -f $(OBJ) *.sign *.lzma *.d *.map *.bin app
