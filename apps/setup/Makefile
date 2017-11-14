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
setup.bin.lzma.sign: setup.bin.lzma $(BDK_ROOT)/trust-keys/bdk-sign-private.pem
	openssl dgst -sha256 -binary -sign $(BDK_ROOT)/trust-keys/bdk-sign-private.pem -out $@ $<
	$(BDK_ROOT)/bin/bdk-aes-pad $@

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
