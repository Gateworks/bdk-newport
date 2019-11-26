# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

ifdef FUSES
    VERBOSE="--verbose"
else
    VERBOSE=
endif
# Value to use for the Fused Non-Volatile counter
NV_COUNT?=0
# Optional SSK encryption
ifdef SSK
    SSK_ARG=--ssk $(SSK)
else
    SSK_ARG=
endif
# Optional HUK encryption
ifdef HUK
    HUK_ARG=--huk $(HUK)
else
    HUK_ARG=
endif

include $(BDK_ROOT)/libbdk/bdk.mk

#
# Create a list of the device tree DTB files we need
#
DTS_FILES=generic.dts
ifneq ($(findstring t81, $(PLAT)),)
DTS_FILES+=asim-cn81xx.dts ebb8004.dts ebb8104.dts nas8104.dts sff8104.dts \
	   rbd8030.dts router8030.dts sierra838.dts xpliant-cn81xx.dts \
	   vcpe8031.dts n838.dts emul-cn81xx.dts
else ifneq ($(findstring t83, $(PLAT)),)
DTS_FILES+=asim-cn83xx.dts ebb8304.dts sff8304.dts xpliant-cn83xx.dts \
	   emul-cn83xx.dts cn8370-crb.dts
else ifneq ($(findstring t96, $(PLAT)),)
DTS_FILES+=asim-cn96xx-a0.dts ebb9604.dts cn96xx-fio.dts cn3380_250sv.dts \
           ebb9304.dts cn96xx-crb.dts cn96xx-crb-r2.dts emul-cn96xx.dts \
           cn3380_250sv_v3.dts
FIRMWARE_INPUT=$(wildcard $(BDK_ROOT)/target-bin/gser?-cn96xx.frm)
else ifneq ($(findstring f95, $(PLAT)),)
DTS_FILES+=asim-cnf95xx-a0.dts emul-cnf95xx.dts ebb9504.dts
FIRMWARE_INPUT=$(wildcard $(BDK_ROOT)/target-bin/gser?-cnf95xx.frm)
else ifneq ($(findstring loki, $(PLAT)),)
DTS_FILES+=asim-loki.dts
FIRMWARE_INPUT=$(wildcard $(BDK_ROOT)/target-bin/gser?-loki.frm)
else ifneq ($(findstring t98, $(PLAT)),)
DTS_FILES+=asim-cn98xx.dts
FIRMWARE_INPUT=$(wildcard $(BDK_ROOT)/target-bin/gser?-cn98xx.frm)
endif
# This is needed for buildroot as it copies SDK linux devicetree files to
# boards directory inside BDK, will not have impact of SDK build
DTS_FILES+=$(wildcard *-linux.dts*)

DTB_FILES=$(DTS_FILES:%.dts=%.dtb)
DTB_SIGNATURES=$(DTS_FILES:%.dts=%.dtb.sign)
FIRMWARE_FILES=$(FIRMWARE_INPUT:%.frm=%.frm.lzma)
FIRMWARE_SIGS=$(FIRMWARE_INPUT:%.frm=%.frm.lzma.sign)
EXTRA_FILES=
EXTRA_CLEAN=
ifneq ("$(wildcard $(BDK_ROOT)/target-bin/bl1.bin)","")
    EXTRA_FILES+=$(BDK_ROOT)/target-bin/bl1.bin.lzma
    EXTRA_FILES+=$(BDK_ROOT)/target-bin/bl1.bin.lzma.sign
    EXTRA_CLEAN+=$(BDK_ROOT)/target-bin/bl1.bin.lzma
    EXTRA_CLEAN+=$(BDK_ROOT)/target-bin/bl1.bin.lzma.sign
endif

#
# Variables used to append proper .dtb with signature nodes
# using mkimage utility. Used only when FIT_DIR is specified.
#
ifdef FIT_DIR
    PLAT_NO=$(shell echo $(PLAT) | grep -o -E '[0-9]+')
    BOARD_PLAT_FILES := $(shell ls $(BDK_ROOT)/boards/ -I "*.dtsi" -I "*.dtb" | grep -e "-linux.dts" | grep $(PLAT_NO))
    ITS_DUMMY_DIR=$(OCTEONTX_ROOT)/fit/dummy
    MKIMAGE=$(OCTEONTX_ROOT)/bootloader/u-boot/tools/mkimage
    KEY_NAME=$(basename $(notdir $(wildcard $(FIT_DIR)/keys/*.key)))
endif

#
# The all target calls CREATE_COMMAND for each board in BOARDS
# init.bin is not compressed as CN80XX runs out of space in its 1MB L2
#
.PHONY: all
all:  $(DTB_FILES) $(DTB_SIGNATURES) $(FIRMWARE_FILES) $(FIRMWARE_SIGS) $(EXTRA_FILES) $(BDK_ROOT)/trust-keys/hw-rot-public.pem
	$(BDK_ROOT)/bin/bdk-create-fatfs-image create \
	    $(VERBOSE) \
	    --out "$(BDK_ROOT)/target-bin/bdk.bin" \
	    --ap_bl1 "$(BDK_ROOT)/apps/boot/boot.bin" \
	    --scp_bl1 "$(BDK_ROOT)/target-bin/scp_bl1.exe" \
	    --mcp_bl1 "$(BDK_ROOT)/target-bin/mcp_bl1.exe" \
	    --key "$(BDK_ROOT)/trust-keys/hw-rot-public.pem" \
	    --nv $(NV_COUNT) $(SSK_ARG) $(HUK_ARG) \
	    "$(BDK_ROOT)/apps/init/init.bin.lzma" \
	    "$(BDK_ROOT)/apps/init/init.bin.lzma.sign" \
	    "$(BDK_ROOT)/apps/diagnostics/diagnostics.bin.lzma" \
	    "$(BDK_ROOT)/apps/diagnostics/diagnostics.bin.lzma.sign" \
	    "$(BDK_ROOT)/apps/setup/setup.bin.lzma" \
	    "$(BDK_ROOT)/apps/setup/setup.bin.lzma.sign" \
	    "$(BDK_ROOT)/trust-keys/bdk-sign.pub" \
	    "$(BDK_ROOT)/trust-keys/bdk-sign.pub.sign" \
	    $(EXTRA_FILES)
ifneq ($(FIRMWARE_FILES),)
	$(BDK_ROOT)/bin/fatfs-tool -q -i "$(BDK_ROOT)/target-bin/bdk.bin" mkdir serdes
	$(BDK_ROOT)/bin/fatfs-tool -q -i "$(BDK_ROOT)/target-bin/bdk.bin" cp \
	    $(FIRMWARE_FILES) $(FIRMWARE_SIGS) serdes
endif
	$(BDK_ROOT)/bin/fatfs-tool -q -i "$(BDK_ROOT)/target-bin/bdk.bin" mkdir dtb
	$(BDK_ROOT)/bin/fatfs-tool -q -i "$(BDK_ROOT)/target-bin/bdk.bin" cp \
	    $(DTB_FILES) $(DTB_SIGNATURES) dtb

#
# This assumes that all binaries in target-bin that match our naming
# pattern should be deleted.
#
clean:
	rm -f $(BDK_ROOT)/target-bin/bdk.bin $(DTB_FILES) $(DTB_SIGNATURES) $(EXTRA_CLEAN) *.d *.o

%.dtb: %.dts *.dtsi
ifneq ($(FIT_DIR),)
	if [[ "$(BOARD_PLAT_FILES)" =~ (^|[[:space:]])"$<"($$|[[:space:]]) ]] ; then \
		dtc -p 2048 -I dts -O dtb -o $@ $< ; \
		echo "Setting dummy key name hint to $(KEY_NAME)"; \
		sed "s/key-name-hint = \"dummy\"/key-name-hint = \"$(KEY_NAME)\"/g" \
			$(ITS_DUMMY_DIR)/default.its > $(ITS_DUMMY_DIR)/dummy.its ; \
		$(MKIMAGE) -r -k $(FIT_DIR)/keys -K $(BDK_ROOT)/boards/$@ \
			-f $(ITS_DUMMY_DIR)/dummy.its $(ITS_DUMMY_DIR)/dummy.itb ; \
		rm $(ITS_DUMMY_DIR)/dummy.its $(ITS_DUMMY_DIR)/dummy.itb; \
	else \
		dtc -I dts -O dtb -o $@ $< ; \
	fi
else
	dtc -I dts -O dtb -o $@ $<
endif

%.sign: % $(BDK_ROOT)/trust-keys/bdk-sign-public.pem
	$(BDK_ROOT)/bin/bdk-sign bdk-sign-private $@ $<

