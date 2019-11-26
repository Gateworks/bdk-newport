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
extra_commands.append("control n0.mpi0 connect 0 /dev/zero")
extra_commands.append("control n0.mpi0 connect 1 " + BDK_ROOT + "/target-bin/bdk.bin")
asim.start(10 * 60, extra_commands) # 10 min limit
asim_tests.do_diags_boot(asim)
asim.stop()

print "***********"
print "Test Passed"
print "***********"

