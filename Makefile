# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

#
# Check for the BDK_ROOT environment variable. If it isn't set,
# assume the root is the current dir. This allos use of the BDK
# from its top dir without any variables.
#
ifndef BDK_ROOT
    export BDK_ROOT:=$(shell pwd)
    $(info BDK_ROOT not set, assuming $(BDK_ROOT))
endif

#
# We can build with either LLVM or GCC. Look for the variable BDK_CLANG_ROOT
# saying we should build with LLVM. GCC is assumed to already be in the PATH.
#
ifdef BDK_CLANG_ROOT
    $(info BDK_CLANG_ROOT set, using LLVM tools)
else
    #$(info BDK_CLANG_ROOT not set, using GNU tools)
endif

# Prevent python from cluttering the source with PYC files
export PYTHONDONTWRITEBYTECODE=1

#
# Releases don't completely recreate the version on every build. Use the
# existence of bdk-release.txt to determine a release
#
ifeq ($(shell test -e libbdk-arch/bdk-release.txt;echo $$?),0)
    BDK_RELEASE:=true
endif

include $(BDK_ROOT)/version.mk
include $(BDK_ROOT)/libbdk/bdk.mk

TFTPBOOT?=/tftpboot/

#
# Default target to build the BDK
#
.PHONY: all
all: version
	$(MAKE) -C trust-keys
	$(MAKE) -C libc
	$(MAKE) -C libbdk
	$(MAKE) -C utils
	$(MAKE) -C apps
	$(MAKE) -C boards

#
# Split docs out from all to allow build to reach tftp when docs fails.
#
.PHONY: docs
docs:
	$(MAKE) -C docs

#
# Note that the clean target doesn't touch the C library. The C library
# changes rarely, so we only clean it with distclean.
#
.PHONY: clean
clean:
	$(MAKE) -C libbdk clean
	$(MAKE) -C utils clean
	$(MAKE) -C apps clean
	$(MAKE) -C boards clean
	$(MAKE) -C docs clean
	$(MAKE) -C trust-keys clean
	rm -f target-bin/bdk.bin *.hex thunder-emmc-ascii.img signing-key.asim
ifndef BDK_RELEASE
	rm -f libbdk-arch/bdk-version.[cd]
endif

#
# Clean everything, normally not needed
#
.PHONY: distclean
distclean: clean
	$(MAKE) -C libc clean
	$(MAKE) -C libbdk distclean
	$(MAKE) -C trust-keys distclean

#
# Copy the firmware binary to a TFTP directory after building. Use for
# quick downloads to boards.
#
.PHONY: tftp
tftp: all
	cp target-bin/bdk.bin $(TFTPBOOT)

#
# The release target creates a tar of the source. It only works if a tag
# exactly matches the current branch head
#
.PHONY: release
release: all docs
	cp target-bin/bdk.bin $(BUILD_REV).bin
	md5sum $(BUILD_REV).bin > $(BUILD_REV).bin.md5
	git archive --format=tar --prefix=$(BUILD_REV)/ $(BUILD_REV) | tar -x
	cp -a docs/api-docs docs/lua-modules docs/*.pdf $(BUILD_REV)/docs/
	cp $(BUILD_REV).bin $(BUILD_REV).bin.md5 $(BUILD_REV)/
	cp libbdk-arch/bdk-version.c $(BUILD_REV)/libbdk-arch/
	cp libbdk-arch/bdk-version.c $(BUILD_REV)/libbdk-arch/bdk-release.txt
	tar -zcf $(BUILD_REV)-source.tgz $(BUILD_REV)
	md5sum $(BUILD_REV)-source.tgz > $(BUILD_REV)-source.tgz.md5

#
# User targets to run Asim. Control which chip is simulated with
# the ASIM_CHIP environment variable. Examples:
#
# ASIM_CHIP=CN81XX:1.0 make -s run
# ASIM_CHIP=CN83XX:1.0 make -s run
# ASIM_CHIP=CN96XX:A0 make -s run
# ASIM_CHIP=CNF95XX:A0 make -s run
#
.PHONY: run
run:
ifndef ASIM
	echo ERROR: Define ASIM in the environment, the directory of asim && false
endif
	echo $(ASIM_CMD)
	$(ASIM_CMD)

#
# Defines controlling the command line for Asim
#
ASIM_CHIP ?= CN96XX:A0
ASIM_IMAGE = $(BDK_ROOT)/target-bin/bdk.bin
ASIM_ELF = $(BDK_ROOT)/apps/diagnostics/app
ASIM_ENV = ASIM_CHIP=$(ASIM_CHIP)
ASIM_ENV += UART0PORT=2000
ASIM_ENV += UART1PORT=2001
ASIM_ENV += UART2PORT=2002
ASIM_ENV += BIN_IMAGE=$(ASIM_IMAGE)
ASIM_ENV += SYMBOL_IMAGE=$(ASIM_ELF)
ASIM_SCRIPT = $(firstword $(subst :, ,$(ASIM_CHIP))).asim
ASIM_CMD = $(ASIM_ENV) $(ASIM)/bin/asim -e $(ASIM_SCRIPT)
export ASIM_PCI_EA_CAP=1

#
# Determine the BDK version based on the last change in the version
# control system. This supports "git". It will need  changes for
# any other version control.
#
# BUILD_REV is a string representing the revision in version control
# BUILD_BRANCH is a string representing the branch in version control
#
ifeq ($(shell test -d .git;echo $$?),0)
    # Using git
    BUILD_REV := $(SUBVERSION)-$(shell git describe --always --dirty)
    BUILD_BRANCH := $(shell git branch | grep \* | sed "s/^\\*[ ]*//g")
else
    # Don't know the version control system
    BUILD_REV=$(SUBVERSION)
    BUILD_BRANCH=$(shell pwd)
endif
SOURCE_DATE_EPOCH?=$(shell date -u +%s)
BUILD_DATE=$(shell date -u -R -d @${SOURCE_DATE_EPOCH})
# Build the full BDK version string
#DISPLAY_VERSION=$(BUILD_REV), Branch: $(BUILD_BRANCH), Built: $(BUILD_DATE)
DISPLAY_VERSION = "Gateworks Newport SPL \($(BUILD_REV) $(shell date -u)\)"

.PHONY: version
version:
ifndef BDK_RELEASE
	echo "const char bdk_version_str[] = \"$(DISPLAY_VERSION)\";" > libbdk-arch/bdk-version.c
else
	sed -i "s/Built:[ A-Za-z0-9:]*\"/Built: $(BUILD_DATE)\"/g" libbdk-arch/bdk-version.c
endif

#
# Run the BDK test suite using Asim
#
.PHONY: test
test:
ifndef ASIM
	echo ERROR: Define ASIM in the environment, the directory of asim && false
endif
	$(MAKE) -C tests

#
# Run the BDK test suite on hardware
#
.PHONY: test-hw
test-hw:
	$(MAKE) -C tests -f test-hardware.mk

#
# Internal use target for creating files used by the hardware emulator
#
.PHONY: emu
emu:
	od -Ax -vtx1 -w1 target-bin/bdk.bin | cut -d " " -f 2 -s > thunder-emmc-ascii.img
	python2 utils/scripts/bdk-create-emulator-mem-image.py bdk-boot.hex apps/boot/boot.bin
	python2 utils/scripts/bdk-create-emulator-mem-image.py emulator-test.hex apps/emulator-test/emulator-test.bin
	echo Copy bdk-boot.hex, emulator-test.hex, and thunder-emmc-ascii.img
	echo to verif/emulator/emulator_fc/bdk/.

