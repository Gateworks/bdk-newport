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
DTS_FILES=$(wildcard *.dts)
DTB_FILES=$(DTS_FILES:%.dts=%.dtb)
DTB_SIGNATURES=$(DTS_FILES:%.dts=%.dtb.sign)
EXTRA_FILES=$(BDK_ROOT)/apps/cortina/cortina-app.bin.lzma
EXTRA_FILES+=$(BDK_ROOT)/apps/cortina/cortina-app.bin.lzma.sign
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
    ITS_DUMMY_DIR=$(THUNDER_ROOT)/fit/dummy
    MKIMAGE=$(THUNDER_ROOT)/bootloader/u-boot/tools/mkimage
    KEY_NAME=$(basename $(notdir $(wildcard $(FIT_DIR)/keys/*.key)))
endif

#
# The all target calls CREATE_COMMAND for each board in BOARDS
# init.bin is not compressed as CN80XX runs out of space in its 1MB L2
#
.PHONY: all
all:  $(DTB_FILES) $(DTB_SIGNATURES) $(EXTRA_FILES) $(BDK_ROOT)/trust-keys/hw-rot-private.pem
	$(BDK_ROOT)/bin/bdk-create-fatfs-image create \
	    $(VERBOSE) \
	    --out "$(BDK_ROOT)/target-bin/bdk.bin" \
	    --ap_bl1 "$(BDK_ROOT)/apps/boot/boot.bin" \
	    --scp_bl1 "$(BDK_ROOT)/target-bin/scp_bl1.exe" \
	    --mcp_bl1 "$(BDK_ROOT)/target-bin/mcp_bl1.exe" \
	    --key "$(BDK_ROOT)/trust-keys/hw-rot-private.pem" \
	    --nv $(NV_COUNT) $(SSK_ARG) $(HUK_ARG) \
	    "$(BDK_ROOT)/apps/init/init.bin" \
	    "$(BDK_ROOT)/apps/init/init.bin.sign" \
	    "$(BDK_ROOT)/apps/diagnostics/diagnostics.bin.lzma" \
	    "$(BDK_ROOT)/apps/diagnostics/diagnostics.bin.lzma.sign" \
	    "$(BDK_ROOT)/apps/setup/setup.bin.lzma" \
	    "$(BDK_ROOT)/apps/setup/setup.bin.lzma.sign" \
	    "$(BDK_ROOT)/trust-keys/bdk-sign.pub" \
	    "$(BDK_ROOT)/trust-keys/bdk-sign.pub.sign" \
	    $(EXTRA_FILES) \
	    $(DTB_FILES) \
	    $(DTB_SIGNATURES)

#
# This assumes that all binaries in target-bin that match our naming
# pattern should be deleted.
#
clean:
	rm -f $(BDK_ROOT)/target-bin/bdk.bin $(DTB_FILES) $(DTB_SIGNATURES) $(EXTRA_CLEAN)

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
	$(BDK_ROOT)/bin/bdk-aes-pad $@

%.dtb.sign: %.dtb $(BDK_ROOT)/trust-keys/bdk-sign-private.pem
	openssl dgst -sha256 -binary -sign $(BDK_ROOT)/trust-keys/bdk-sign-private.pem -out $@ $<
	$(BDK_ROOT)/bin/bdk-aes-pad $@

$(BDK_ROOT)/target-bin/bl1.bin.lzma.sign: $(BDK_ROOT)/target-bin/bl1.bin.lzma $(BDK_ROOT)/trust-keys/bdk-sign-private.pem
	openssl dgst -sha256 -binary -sign $(BDK_ROOT)/trust-keys/bdk-sign-private.pem -out $@ $<
	$(BDK_ROOT)/bin/bdk-aes-pad $@
