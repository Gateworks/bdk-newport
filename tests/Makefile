# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

ifndef BDK_ROOT
    export BDK_ROOT:=$(shell pwd)/..
endif

ifeq ($(shell which qsub),)
    SUBMIT_PREFIX=
    SUFFIX=" > $@.log 2>&1
else
    # "qsub" to run on another node
    # "-N name" to give the job a new name
    # "-o file" to log stdout to file
    # "-j yes" to merge stdout and stderr
    # "-sync yes" to wait for the job
    # "-r no" Don't resubmit on failure
    # "-q build" Use nodes designated for builds (from Jeff Pangborn)
    # "-l h_rt=300" Limit the job to 5 min
    SUBMIT_PREFIX=qsub -N $@ -o $@.log -j yes -sync yes -r no -q build -l h_rt=300 '
    SUFFIX=" ' > /dev/null
endif
SUBMIT=$(SUBMIT_PREFIX) bash -c "export ASIM=$(ASIM); export ASIM_CHIP=$(ASIM_CHIP); export BDK_ROOT=$(BDK_ROOT); cd $(BDK_ROOT)/tests; pwd;

.PHONY: all
all: cn80xx cn81xx cn83xx cn96xxa cn96xxc cnf95xxa cnf95xxb loki cn98xx

.PHONY: cn80xx
cn80xx: ASIM_CHIP=CN80XX:1.0
cn80xx: CN80XX.test-net-dxaui1 CN80XX.test-net-fake CN80XX.test-sata CN80XX.test-stage1 CN80XX.test-stage1-emmc CN80XX.test-stage1-trusted-boot CN80XX.test-stage1-trusted-boot-emmc CN80XX.test-asim-hw-scripts CN80XX.test-asim-hw-scripts-qlm-config-all

.PHONY: cn81xx
cn81xx: ASIM_CHIP=CN81XX:1.0
cn81xx: CN81XX.test-net-dxaui1 CN81XX.test-net-fake CN81XX.test-sata CN81XX.test-stage1 CN81XX.test-stage1-emmc CN81XX.test-stage1-trusted-boot CN81XX.test-stage1-trusted-boot-emmc CN81XX.test-asim-hw-scripts CN81XX.test-asim-hw-scripts-qlm-config-all

.PHONY: cn83xx
cn83xx: ASIM_CHIP=CN83XX:1.0
cn83xx: CN83XX.test-net-dxaui1 CN83XX.test-net-fake CN83XX.test-sata CN83XX.test-stage1 CN83XX.test-stage1-emmc CN83XX.test-stage1-trusted-boot CN83XX.test-stage1-trusted-boot-emmc CN83XX.test-asim-hw-scripts CN83XX.test-asim-hw-scripts-qlm-config-all

.PHONY: cn96xxa
cn96xxa: ASIM_CHIP=CN96XX:A0
cn96xxa: CN96XXa.test-net-dxaui1 CN96XXa.test-net-fake CN96XXa.test-stage1 CN96XXa.test-stage1-emmc CN96XXa.test-stage1-trusted-boot CN96XXa.test-stage1-trusted-boot-emmc CN96XXa.test-asim-hw-scripts CN96XXa.test-asim-hw-scripts-qlm-config-all CN96XXa.test-stage1-spi0cs1 CN96XXa.test-stage1-spi1cs0 CN96XXa.test-stage1-spi1cs1 CN96XXa.test-emulator-test

.PHONY: cn96xxc
cn96xxc: ASIM_CHIP=CN96XX:C0
cn96xxc: CN96XXc.test-net-dxaui1 CN96XXc.test-net-fake CN96XXc.test-stage1 CN96XXc.test-stage1-emmc CN96XXc.test-stage1-trusted-boot CN96XXc.test-stage1-trusted-boot-emmc CN96XXc.test-stage1-spi0cs1 CN96XXc.test-stage1-spi1cs0 CN96XXc.test-stage1-spi1cs1 CN96XXc.test-emulator-test

.PHONY: cnf95xxa
cnf95xxa: ASIM_CHIP=CNF95XX:A0
cnf95xxa: CNF95XXA.test-net-dxaui1 CNF95XXA.test-net-fake CNF95XXA.test-stage1 CNF95XXA.test-stage1-emmc CNF95XXA.test-stage1-trusted-boot CNF95XXA.test-stage1-trusted-boot-emmc CNF95XXA.test-asim-hw-scripts CNF95XXA.test-asim-hw-scripts-qlm-config-all CNF95XXA.test-stage1-spi0cs1 CNF95XXA.test-stage1-spi1cs0  CNF95XXA.test-stage1-spi1cs1 CNF95XXA.test-emulator-test

.PHONY: cnf95xxb
cnf95xxb: ASIM_CHIP=CNF95XX:B0
cnf95xxb: CNF95XXB.test-net-dxaui1 CNF95XXB.test-net-fake CNF95XXB.test-stage1 CNF95XXB.test-stage1-emmc CNF95XXB.test-stage1-trusted-boot CNF95XXB.test-stage1-trusted-boot-emmc CNF95XXB.test-asim-hw-scripts CNF95XXB.test-stage1-spi0cs1 CNF95XXB.test-stage1-spi1cs0  CNF95XXB.test-stage1-spi1cs1 CNF95XXB.test-emulator-test

.PHONY: loki
loki: ASIM_CHIP=LOKI:A0
loki: loki.test-net-dxaui1 loki.test-net-fake loki.test-stage1 loki.test-stage1-emmc loki.test-stage1-trusted-boot loki.test-stage1-trusted-boot-emmc loki.test-asim-hw-scripts loki.test-stage1-spi0cs1 loki.test-stage1-spi1cs0 loki.test-stage1-spi1cs1 loki.test-emulator-test

.PHONY: cn98xx
cn98xx: ASIM_CHIP=CN98XX:A0
cn98xx: CN98XX.test-net-dxaui1 CN98XX.test-net-fake CN98XX.test-stage1 CN98XX.test-stage1-emmc CN98XX.test-stage1-trusted-boot CN98XX.test-stage1-trusted-boot-emmc CN98XX.test-stage1-spi0cs1 CN98XX.test-stage1-spi1cs0 CN98XX.test-stage1-spi1cs1

.PHONY: %.test-net-dxaui1
%.test-net-dxaui1:
	$(SUBMIT) python2 asim/test-net-dxaui1.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-net-fake
%.test-net-fake:
	$(SUBMIT) python2 asim/test-net-fake.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-sata
%.test-sata:
	$(SUBMIT) python2 asim/test-sata.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-stage1
%.test-stage1:
	$(SUBMIT) python2 asim/test-stage1.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-stage1-emmc
%.test-stage1-emmc:
	$(SUBMIT) python2 asim/test-stage1-emmc.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-stage1-trusted-boot
%.test-stage1-trusted-boot:
	$(SUBMIT) python2 asim/test-stage1-trusted-boot.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-stage1-trusted-boot-emmc
%.test-stage1-trusted-boot-emmc:
	$(SUBMIT) python2 asim/test-stage1-trusted-boot-emmc.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-asim-hw-scripts
%.test-asim-hw-scripts:
	$(SUBMIT) python2 hardware/run-test.py -b asim --bmc asim boot-diags short-dram $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-stage1-spi0cs1
%.test-stage1-spi0cs1:
	$(SUBMIT) python2 asim/test-stage1-spi0cs1.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-stage1-spi1cs0
%.test-stage1-spi1cs0:
	$(SUBMIT) python2 asim/test-stage1-spi1cs0.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-stage1-spi1cs1
%.test-stage1-spi1cs1:
	$(SUBMIT) python2 asim/test-stage1-spi1cs1.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-emulator-test
%.test-emulator-test:
	$(SUBMIT) python2 asim/test-emulator-test.py $(SUFFIX)
	echo "PASS: $@.log"

.PHONY: %.test-asim-hw-scripts-qlm-config-all
%.test-asim-hw-scripts-qlm-config-all:
	$(SUBMIT) python2 hardware/run-test.py -b asim --bmc asim qlm-detect qlm-config-all $(SUFFIX)
	echo "PASS: $@.log"
