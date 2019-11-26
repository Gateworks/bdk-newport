# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

import time
from asim_helper import AsimHelper
import asim_tests

asim = AsimHelper()
asim.start(10 * 60, []) # 10 min limit
asim_tests.do_diags_boot(asim)

asim.send("tg")
asim.wait_for("BDK Traffic Generator")
asim.wait_for("Type \"help\" for a list of commands")
asim.wait_for("(INS)Command>")
asim.send("loopback all internal")
asim.wait_for("(INS)Command>")
asim.send("wait_links")
asim.wait_for("(INS)Command>")
asim.send("default all")
asim.wait_for("(INS)Command>")

if asim.chip.startswith("CN80XX"):
    ports = ["XFI0.0", "SGMII1.0", "SGMII1.1",
             "LBK0.0", "LBK0.1", "LBK0.2", "LBK0.3"]
elif asim.chip.startswith("CN81XX"):
    ports = ["XFI0.0", "XFI0.1", "RXAUI0.2", "SGMII1.0", "SGMII1.1",
             "LBK0.0", "LBK0.1", "LBK0.2", "LBK0.3"]
elif asim.chip.startswith("CN83XX"):
    ports = ["XFI0.0", "XFI0.1", "XFI0.2", "XFI0.3", "DXAUI1", "XLAUI2",
             "LBK0.0", "LBK0.1", "LBK0.2", "LBK0.3",
             "LBK1.0", "LBK1.1", "LBK1.2", "LBK1.3",
             "LBK2.0", "LBK2.1", "LBK2.2", "LBK2.3",
             "LBK3.0", "LBK3.1", "LBK3.2", "LBK3.3"]
elif asim.chip.startswith("CN88XX"):
    ports = ["XFI0.0", "XFI0.1", "XFI0.2", "XFI0.3", "DXAUI1"]
elif asim.chip.startswith("CN96XX"):
    ports = ["LBK0.0", "LBK0.1", "LBK0.2", "LBK0.3",
             "25G0.0", "25G0.1", "25G0.2", "25G0.3",
             "50G1.2",
             "USX2.0", "USX2.1", "USX2.2", "USX2.3"]
elif asim.chip.startswith("CNF95XX"):
    ports = ["LBK0.0", "LBK0.1", "LBK0.2", "LBK0.3",
             "10G0.0", "10G0.1", "10G0.2", "10G0.3"]
elif asim.chip.startswith("LOKI"):
    ports = ["LBK0.0", "LBK0.1", "LBK0.2", "LBK0.3",
             "10G0.0", "10G0.1", "10G0.2", "10G0.3"]
elif asim.chip.startswith("CN98XX"):
    ports = ["LBK0.0", "LBK0.1", "LBK0.2", "LBK0.3",
             #"LBK1.0", "LBK1.1", "LBK1.2", "LBK1.3", # FIXME
             #"LBK2.0", "LBK2.1", "LBK2.2", "LBK2.3",
             #"LBK3.0", "LBK3.1", "LBK3.2", "LBK3.3",
             "10G0.0", "10G0.1", "10G0.2", "10G0.3",
             "40G1",
             "25G2.0", "25G2.1", "25G2.2", "25G2.3",
             "50G3.0", "50G3.2",
             "100G4"]
else:
    assert False, "test-net-dxaui.py doesn't know this chip"

for port in ports:
    asim.send("default %s" % port)
    asim.wait_for("(INS)Command>")
    asim.send("count 100")
    asim.wait_for("(INS)Command>")
    asim.send("start")
    asim.wait_for("(INS)Command>")
    time.sleep(2)
    asim.send("tx_packets_total")
    asim.wait_for("Port %s: tx_packets_total = 100" % port)
    asim.wait_for("(INS)Command>")
    asim.send("tx_octets_total")
    if "LBK" in port:
        asim.wait_for("Port %s: tx_octets_total = 6000" % port)
    else:
        asim.wait_for("Port %s: tx_octets_total = 6400" % port)
    asim.wait_for("(INS)Command>")
    asim.send("rx_packets_total")
    asim.wait_for("Port %s: rx_packets_total = 100" % port)
    asim.wait_for("(INS)Command>")
    asim.send("rx_octets_total")
    if "LBK" in port:
        asim.wait_for("Port %s: rx_octets_total = 6000" % port)
    else:
        asim.wait_for("Port %s: rx_octets_total = 6400" % port)
    asim.wait_for("(INS)Command>")
    asim.send("rx_errors")
    asim.wait_for("Port %s: rx_errors = 0" % port)
    asim.wait_for("(INS)Command>")
    asim.send("rx_validation_errors")
    asim.wait_for("Port %s: rx_validation_errors = 0" % port)
    asim.wait_for("(INS)Command>")
    asim.send("scan_sizes 10 60 9212 1111")
    for size in range(60, 9212, 1111):
        asim.wait_for("Size %d" % size)
    asim.wait_for("(INS)Command>")
asim.send("quit")

asim.wait_for("=================================")
asim.wait_for("Main Menu")
asim.wait_for("=================================")
asim.wait_for("(INS)Menu choice []:")

asim.stop()

print "***********"
print "Test Passed"
print "***********"

