# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

.PHONY: all
all: boot diagnostics init setup emulator-test

.PHONY: boot
boot:
	${MAKE} -C boot

.PHONY: diagnostics
diagnostics:
	${MAKE} -C diagnostics

.PHONY: init
init:
	${MAKE} -C init

.PHONY: setup
setup:
	${MAKE} -C setup

.PHONY: emulator-test
emulator-test:
	${MAKE} -C emulator-test

.PHONY: clean
clean:
	${MAKE} -C boot clean
	${MAKE} -C diagnostics clean
	${MAKE} -C init clean
	${MAKE} -C setup clean
	${MAKE} -C emulator-test clean

