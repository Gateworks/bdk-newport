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
node = ""
asim.send("default %sFAKE0-%sFAKE3" % (node, node))
asim.wait_for("(INS)Command>")
asim.send("count 100")
asim.wait_for("(INS)Command>")
asim.send("start")
asim.wait_for("(INS)Command>")
time.sleep(2)
asim.send("tx_packets_total")
asim.wait_for("Port %sFAKE0: tx_packets_total = 100" % node)
asim.wait_for("Port %sFAKE1: tx_packets_total = 100" % node)
asim.wait_for("Port %sFAKE2: tx_packets_total = 100" % node)
asim.wait_for("Port %sFAKE3: tx_packets_total = 100" % node)
asim.wait_for("(INS)Command>")
asim.send("tx_octets_total")
asim.wait_for("Port %sFAKE0: tx_octets_total = 6000" % node)
asim.wait_for("Port %sFAKE1: tx_octets_total = 6000" % node)
asim.wait_for("Port %sFAKE2: tx_octets_total = 6000" % node)
asim.wait_for("Port %sFAKE3: tx_octets_total = 6000" % node)
asim.wait_for("(INS)Command>")
asim.send("rx_packets_total")
asim.wait_for("Port %sFAKE0: rx_packets_total = 100" % node)
asim.wait_for("Port %sFAKE1: rx_packets_total = 100" % node)
asim.wait_for("Port %sFAKE2: rx_packets_total = 100" % node)
asim.wait_for("Port %sFAKE3: rx_packets_total = 100" % node)
asim.wait_for("(INS)Command>")
asim.send("rx_octets_total")
asim.wait_for("Port %sFAKE0: rx_octets_total = 6000" % node)
asim.wait_for("Port %sFAKE1: rx_octets_total = 6000" % node)
asim.wait_for("Port %sFAKE2: rx_octets_total = 6000" % node)
asim.wait_for("Port %sFAKE3: rx_octets_total = 6000" % node)
asim.wait_for("(INS)Command>")
asim.send("rx_errors")
asim.wait_for("Port %sFAKE0: rx_errors = 0" % node)
asim.wait_for("Port %sFAKE1: rx_errors = 0" % node)
asim.wait_for("Port %sFAKE2: rx_errors = 0" % node)
asim.wait_for("Port %sFAKE3: rx_errors = 0" % node)
asim.wait_for("(INS)Command>")
asim.send("rx_validation_errors")
asim.wait_for("Port %sFAKE0: rx_validation_errors = 0" % node)
asim.wait_for("Port %sFAKE1: rx_validation_errors = 0" % node)
asim.wait_for("Port %sFAKE2: rx_validation_errors = 0" % node)
asim.wait_for("Port %sFAKE3: rx_validation_errors = 0" % node)
asim.wait_for("(INS)Command>")
asim.send("scan_sizes 100 60 9212 1111")
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

