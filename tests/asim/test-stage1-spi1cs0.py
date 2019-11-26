# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

from asim_helper import AsimHelper
from asim_helper import BDK_ROOT
import asim_tests

asim = AsimHelper()

extra_commands = []
# Change strapping to SPI1_CS0,SPI1_CS1 boot
extra_commands.append("control n0.gpio0 set strap 0x200c")
extra_commands.append("control n0.mpi0 connect 0 /dev/zero")
extra_commands.append("control n0.mpi1 connect 0 " + BDK_ROOT + "/target-bin/bdk.bin")
asim.start(10 * 60, extra_commands) # 10 min limit
asim_tests.do_diags_boot(asim, use_spi1=True)
asim.stop()

print "***********"
print "Test Passed"
print "***********"

