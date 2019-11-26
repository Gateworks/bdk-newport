# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

from asim_helper import AsimHelper
import asim_tests

asim = AsimHelper()
asim.start(10 * 60, []) # 10 min limit
asim_tests.do_diags_boot(asim)
asim.stop()

print "***********"
print "Test Passed"
print "***********"

