# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

import os
import time

def do_diags_boot(asim, use_emmc=False, use_trust=False, use_spi1=False):
    asim.wait_for("OcteonTX SOC")
    asim.wait_for("PASS: CRC32 verification")
    asim.wait_for("==================")
    asim.wait_for("OcteonTX Boot Stub")
    asim.wait_for("==================")
    asim.wait_for("Version:")
    if asim.chip.startswith("CN88XX"):
        asim.wait_for("Node:  0")
    if asim.chip.startswith("CN8"):
        asim.wait_for("Chip:  0xa")
        asim.wait_for("SKU:   CN8")
        asim.wait_for("L2:")
        if use_emmc:
            asim.wait_for("Boot:  EMMC_SS")
        else:
            asim.wait_for("Boot:  SPI24")
        asim.wait_for("VRM:   Enabled")
        if use_trust:
            asim.wait_for("Trust: Enabled, Secure Boot")
        else:
            asim.wait_for("Trust: Disabled, Non-secure Boot")
    else:
        asim.wait_for("Chip:  0xb")
        if asim.chip.startswith("CNF"):
            asim.wait_for("SKU:   CNF9")
        elif asim.chip.startswith("LOKI"):
            asim.wait_for("SKU:   LOK")
        else:
            asim.wait_for("SKU:   CN9")
        asim.wait_for("L2:")
        if use_emmc:
            asim.wait_for("Boot:  EMMC_CS0,EMMC_CS1, using EMMC_CS0")
        elif use_spi1:
            asim.wait_for("Boot:  SPI1_CS0,SPI1_CS1, using SPI1_CS")
        else:
            asim.wait_for("Boot:  SPI0_CS0,SPI0_CS1, using SPI0_CS")
        asim.wait_for("AVS:   Enabled")
        if use_trust:
            asim.wait_for("Trust: Enabled, Secure Boot")
        else:
            asim.wait_for("Trust: Disabled")
    asim.wait_for("Press 'B' within 10 seconds for boot menu")
    asim.send("b")

    asim.wait_for("============")
    asim.wait_for("Boot Options")
    asim.wait_for("============")
    asim.wait_for("N) Boot Normally")
    asim.wait_for("S) Enter Setup")
    asim.wait_for("D) Enter Diagnostics")
    if not (asim.chip.startswith("CN81XX") or asim.chip.startswith("CN80XX")):
        asim.wait_for("E) Enter Diagnostics, skipping Setup")
    asim.wait_for("W) Burn boot flash using Xmodem")
    asim.wait_for("U) Change baud rate and flow control")
    asim.wait_for("R) Reboot")
    asim.wait_for("Choice:")

    asim.send("d")
    asim.wait_for("Loading image file '/fatfs/diagnostics.bin.lzma'")
    asim.wait_for("---")
    asim.wait_for("OcteonTX SOC")
    asim.wait_for("PASS: CRC32 verification")
    asim.wait_for("Lua 5.2.0  Copyright (C) 1994-2011 Lua.org, PUC-Rio")

    asim.wait_for("OcteonTX Diagnostic")
    asim.wait_for("Copyright (C) 2018 Marvell International Ltd.")
    asim.wait_for("Version")

    asim.wait_for("=================================")
    asim.wait_for("Main Menu")
    asim.wait_for("=================================")
    asim.wait_for("(INS)Menu choice []:")

