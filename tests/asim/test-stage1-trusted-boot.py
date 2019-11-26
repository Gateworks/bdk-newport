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
    extra_commands.append("control n0.gpio0 set strap 0x140a")

asim.start(10 * 60, extra_commands) # 10 min limit
asim_tests.do_diags_boot(asim, use_trust=True)
asim.stop()

print "***********"
print "Test Passed"
print "***********"

