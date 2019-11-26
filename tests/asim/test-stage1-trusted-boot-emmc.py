# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

import os
from asim_helper import AsimHelper
import asim_tests

BDK_ROOT = os.environ["BDK_ROOT"]

asim = AsimHelper()

extra_commands = []
extra_commands.append("@%s/signing-key.asim" % BDK_ROOT)
if asim.chip.startswith("CN9") or asim.chip.startswith("CNF95XX") or asim.chip.startswith("LOKI"):
    # eMMC0 then eMMC1, trusted mode
    # GPIO[3-0] = BOOT[3-0]
    # GPIO[4] = MCP debug
    # GPIO[5] = NCSI_ON_GPIO
    # GPIO[8-6] Unused
    # GPIO[9] = AVS Disable
    # GPIO[10] = TRUSTED_MODE
    # GPIO[11] = CCPI_NODE_ID, must be 0
    # GPIO[13-12] = BOOT[5-4]
    # GPIO[15-14] Unused
    # GPIO[17-16] = GSER_CLK0_TERM_SEL
    # GPIO[23-18] Unused
    # GPIO[24] = PCIE0_EP_MODE
    # GPIO[25] = PCIE1_EP_MODE
    extra_commands.append("control n0.gpio0 set strap 0x408")
else:
    # Change strapping to EMMC_SS, trusted boot
    extra_commands.append("control n0.gpio0 set strap 0x402")
asim.start(10 * 60, extra_commands) # 10 min limit
asim_tests.do_diags_boot(asim, use_emmc=True, use_trust=True)
asim.stop()

print "***********"
print "Test Passed"
print "***********"
