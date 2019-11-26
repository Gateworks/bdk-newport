# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

from asim_helper import AsimHelper
import os

BDK_ROOT = os.environ["BDK_ROOT"]

# Change the image we're execute to emulator-test
extra_env = {}
extra_env["SYMBOL_IMAGE"] = BDK_ROOT + "/apps/emulator-test/app"

# Change the platform fuses to say emulator
extra_commands = []
# ASIM currently doesn't map DTX
extra_commands.append("device memory n0.dtx0 config 0x10000 0x87e0fe440000")
# Run platform is fuse 118:117, need 1 for emulator, so set fuse 117
# Fuse 117 is in FUS_CACHEX(117/64) = FUS_CACHEX(1)[0x87e003001000+8] bit 53
extra_commands.append("control n0.fus0 set fuse 1 0x0020000000000000")
extra_commands.append("load -n %s/apps/emulator-test/emulator-test.bin 0x120000" % BDK_ROOT)
extra_commands.append("rm0 pc = 0x120000")
extra_commands.append("mm8 0x87e087102000 = 0") # CCS_ASC_REGIONX_START
extra_commands.append("mm8 0x87e087102008 = -1") # CCS_ASC_REGIONX_END
extra_commands.append("mm8 0x87e087102010 = 0") # CCS_ASC_REGIONX_OFFSET
extra_commands.append("mm8 0x87e087102018 = 2") # CCS_ASC_REGIONX_ATTR
extra_commands.append("start 0")
asim = AsimHelper()
asim.start(15 * 60, extra_commands, extra_env, True) # 15 min limit

asim.wait_for("OcteonTX SOC")
asim.wait_for("PASS: CRC32 verification")
asim.wait_for("Transferring to thread scheduler")
asim.wait_for("Platform set to emulator: PASS")
asim.wait_for("Enabling all tracing")
asim.wait_for("Starting cores")
asim.wait_for("Alive cores: 4")
asim.wait_for("Starting power burn on all cores for 10ms")
asim.wait_for("Power burn complete")
asim.wait_for("Starting DRAM test of 1MB")
asim.wait_for("Reported 0 errors: PASS")
if asim.chip.startswith("CN96XX"):
    test_size = 16
elif asim.chip.startswith("CNF95XX"):
    test_size = 5
elif asim.chip.startswith("LOKI"):
    test_size = 5
else:
    assert(False, "Unknown chip")
asim.wait_for("Quick tests complete, starting longer test")
asim.wait_for("Starting DRAM test of %dMB at offset 64MB" % test_size)
asim.wait_for("Reported 0 errors: PASS")
for mb in range(512, 4097, 512):
    asim.wait_for("Starting DRAM test of %dMB at offset %dMB" % (test_size, mb - test_size))
    asim.wait_for("Reported 0 errors: PASS")
asim.wait_for("All tests complete")
asim.stop()

print "***********"
print "Test Passed"
print "***********"

