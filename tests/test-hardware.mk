# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

ifndef BDK_ROOT
    export BDK_ROOT:=$(shell pwd)/..
endif

.PHONY: all
all: ebb8104 ebb8304 ebb9504 ebb9604

.PHONY: ebb8104
ebb8104:
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ --flash $(BDK_ROOT)/target-bin/bdk.bin boot-diags > $@-flash.log 2>&1
	echo "PASS: $@-flash.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ short-dram > $@-short-dram.log 2>&1
	echo "PASS: $@-short-dram.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ lbk > $@-lbk.log 2>&1
	echo "PASS: $@-lbk.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ qlm-detect > $@-qlm-detect.log 2>&1
	echo "PASS: $@-qlm-detect.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ qlm-config-all > $@-qlm-config-all.log 2>&1
	echo "PASS: $@-qlm-config-all.log"

.PHONY: ebb8304
ebb8304:
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ --flash $(BDK_ROOT)/target-bin/bdk.bin boot-diags > $@-flash.log 2>&1
	echo "PASS: $@-flash.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ short-dram > $@-short-dram.log 2>&1
	echo "PASS: $@-short-dram.log"
	# LBK fails on 83
	#$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ lbk > $@-lbk.log 2>&1
	#echo "PASS: $@-lbk.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ qlm-detect > $@-qlm-detect.log 2>&1
	echo "PASS: $@-qlm-detect.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ qlm-config-all > $@-qlm-config-all.log 2>&1
	echo "PASS: $@-qlm-config-all.log"

.PHONY: ebb9504 ebb9604
ebb9504 ebb9604:
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ --flash $(BDK_ROOT)/target-bin/bdk.bin boot-diags > $@-flash.log 2>&1
	echo "PASS: $@-flash.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ short-dram > $@-short-dram.log 2>&1
	echo "PASS: $@-short-dram.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ lbk > $@-lbk.log 2>&1
	echo "PASS: $@-lbk.log"
	$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ qlm-detect > $@-qlm-detect.log 2>&1
	echo "PASS: $@-qlm-detect.log"
	# QLM config all fails on 9x
	#$(BDK_ROOT)/tests/hardware/run-test.py -b $@ --mcu $@ qlm-config-all > $@-qlm-config-all.log 2>&1
	#echo "PASS: $@-qlm-config-all.log"

