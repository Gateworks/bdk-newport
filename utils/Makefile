# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

.PHONY: all
all:
	$(MAKE) -C bdk-lua
	$(MAKE) -C bdk-luac
	$(MAKE) -C fatfs-tool
	$(MAKE) -C bdk-csr

.PHONY: clean
clean:
	$(MAKE) -C bdk-lua clean
	$(MAKE) -C bdk-luac clean
	$(MAKE) -C fatfs-tool clean
	$(MAKE) -C bdk-csr clean
	find scripts -name "*.pyc" | xargs -r rm
