# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

from asim_helper import AsimHelper
import asim_tests

asim = AsimHelper()

extra_commands = []
if asim.chip.startswith("CN9") or asim.chip.startswith("CNF95XX") or asim.chip.startswith("LOKI"):
    # Change strapping to EMMC_CS0,EMMC_CS1 boot
    extra_commands.append("control n0.gpio0 set strap 0x008")
else:
    # Change strapping to EMMC_SS boot
    extra_commands.append("control n0.gpio0 set strap 0x2")
asim.start(10 * 60, extra_commands) # 10 min limit
asim_tests.do_diags_boot(asim, use_emmc=True)
asim.stop()

print "***********"
print "Test Passed"
print "***********"

