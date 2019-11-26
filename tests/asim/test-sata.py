# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

import os
from asim_helper import AsimHelper
import asim_tests

asim = AsimHelper()
asim.start(1 * 60 * 60, []) # 1 hour limit
asim_tests.do_diags_boot(asim)

asim.send("sata")
asim.wait_for("=================================")
asim.wait_for("SATA Menu")
asim.wait_for("=================================")
asim.wait_for(" 1) Select SATA port (Currently 0)")
asim.wait_for(" 2) Perform an identify disk")
asim.wait_for(" 3) Enter Local-end Retimed Loopback")
asim.wait_for(" 4) Enter Local-end Transmit Only, Simultaneous switching outputs pattern (SSOP)")
asim.wait_for(" 5) Enter Local-end Transmit Only, High transition density pattern (HTDP)")
asim.wait_for(" 6) Enter Local-end Transmit Only, Low transition density pattern (LTDP)")
asim.wait_for(" 7) Enter Local-end Transmit Only, Low frequency spectral component pattern (LFSCP)")
asim.wait_for(" 8) Enter Local-end Transmit Only, Composite pattern (COMP)")
asim.wait_for(" 9) Enter Local-end Transmit Only, Lone bit pattern (LBP)")
asim.wait_for("10) Enter Local-end Transmit Only, Mid frequency test pattern (MFTP)")
asim.wait_for("11) Enter Local-end Transmit Only, High frequency test pattern (HFTP)")
asim.wait_for("12) Enter Local-end Transmit Only, Low frequency test pattern (LFTP)")
asim.wait_for("13) Reset the controller")
asim.wait_for("14) Hex display")
asim.wait_for("15) Write pattern 0x00")
asim.wait_for("16) Read  pattern 0x00")
asim.wait_for("17) Write pattern 0xff")
asim.wait_for("18) Read  pattern 0xff")
asim.wait_for("19) Write pattern 0x55")
asim.wait_for("20) Read  pattern 0x55")
asim.wait_for("21) Write pattern 0xaa")
asim.wait_for("22) Read  pattern 0xaa")
asim.wait_for("23) Run automated pattern test")
asim.wait_for("24) Run margining tool")
asim.wait_for("25) Main menu")
asim.wait_for("(INS)Menu choice []:")
serial = 1
sata_port = [0,1]
if asim.chip.startswith("CN88XX"):
    sata_port = [8,15]
if asim.chip.startswith("CN96XX"):
    sata_port = [0,1]
for sata in sata_port:
    sata_file = "test_disk-%d.tmp" % os.getpid()
    assert(os.system("dd if=/dev/zero of=%s bs=1M count=1" % sata_file) == 0)
    asim.command("control n0.ahci%d connect ide 0 %s" % (sata, sata_file))
    asim.send("port %d" % sata)
    asim.wait_for("=================================")
    asim.wait_for("SATA Menu")
    asim.wait_for("=================================")
    asim.wait_for(" 1) Select SATA port (Currently %d)" % sata)
    asim.wait_for("(INS)Menu choice []:")
    asim.send("id")
    asim.wait_for("SATA%d: Model=\"HARDDISK\", Firmware=\"ASIM\", Serial=\"QM0000%d\", Sectors=2016, Link=Gen3" % (sata, serial))
    serial += 1
    asim.wait_for("=================================")
    asim.wait_for("SATA Menu")
    asim.wait_for("=================================")
    asim.wait_for("(INS)Menu choice []:")
    asim.send("auto")
    asim.wait_for("(INS)Repeat count (-1 for infinite) [1]:")
    asim.send("1")
    for sectors in range(1,129):
        asim.wait_for("Testing %d block accesses" % sectors)
    asim.wait_for("=================================")
    asim.wait_for("SATA Menu")
    asim.wait_for("=================================")
    asim.wait_for("(INS)Menu choice []:")
    asim.command("control n0.ahci%d disconnect 0" % sata)
    assert(os.system("rm %s" % sata_file) == 0)

asim.stop()

print "***********"
print "Test Passed"
print "***********"

