# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

include $(BDK_ROOT)/libbdk/bdk.mk

emulator-test.bin: app.bin
	$(BDK_ROOT)/bin/bdk-update-romfs $@ $^

app: app.o $(BDK_ROOT)/libbdk/libbdk.a
%.o: %.d
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
-include app.d
endif
endif

clean:
	rm -f *.o *.d *.map *.bin app
