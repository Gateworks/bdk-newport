# ***********************license start***********************************
# Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
# reserved.
#
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#   * Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#
#   * Neither the name of Cavium Inc. nor the names of
#     its contributors may be used to endorse or promote products
#     derived from this software without specific prior written
#     permission.
#
# This Software, including technical data, may be subject to U.S. export
# control laws, including the U.S. Export Administration Act and its
# associated regulations, and may be subject to export or import
# regulations in other countries.
#
# TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
# AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
# WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
# TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
# REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
# DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
# OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
# PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
# QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
# ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
# **********************license end**************************************
import time
import boards
import connection
import test_boot
import test_dram

TEST_MODES = [
    ["sgmii",   "sgmii"],
    ["sgmii",   "rxaui"],
    ["sgmii",   "xfi"],
    ["sgmii",   "10g"],
    ["sgmii",   "dis"],
    ["qsgmii",  "dis"],
    #["xaui",    None], # Not supported
    #["dxaui",   None], # Not supported
    ["rxaui",   "sgmii"],
    ["rxaui",   "rxaui"],
    ["rxaui",   "xfi"],
    ["rxaui",   "10g"],
    ["rxaui",   "dis"],
    ["xfi",     "sgmii"],
    ["xfi",     "rxaui"],
    ["xfi",     "xfi"],
    ["xfi",     "10g"],
    ["xfi",     "dis"],
    #["xlaui",   None], # FAIL
    ["10g",     "sgmii"],
    ["10g",     "rxaui"],
    ["10g",     "xfi"],
    ["10g",     "10g"],
    ["10g",     "dis"],
    #["40g",     None], # FAIL
    ["dis",     "sgmii"],
    ["dis",     "qsgmii"],
    ["dis",     "rxaui"],
    ["dis",     "xfi"],
    ["dis",     "10g"],
    ["dis",     "dis"]
]

def get_port_list(qlm_test_mode):
    port_list = []
    for bgx in range(2):
        for i,mode in enumerate(qlm_test_mode):
            if mode == "sgmii":
                if qlm_test_mode[0] == "dis":
                    port_list.append("SGMII%d.0" % bgx)
                    port_list.append("SGMII%d.1" % bgx)
                elif qlm_test_mode[0] == "rxaui":
                    port_list.append("SGMII%d.1" % bgx)
                    port_list.append("SGMII%d.2" % bgx)
                else:
                    port_list.append("SGMII%d.%d" % (bgx, i * 2 + 0))
                    port_list.append("SGMII%d.%d" % (bgx, i * 2 + 1))
            elif mode == "qsgmii":
                port_list.append("QSGMII%d.0" % bgx)
                port_list.append("QSGMII%d.1" % bgx)
                port_list.append("QSGMII%d.2" % bgx)
                port_list.append("QSGMII%d.3" % bgx)
            elif mode == "xaui":
                port_list.append("XAUI%d" % bgx)
            elif mode == "dxaui":
                port_list.append("DXAUI%d" % bgx)
            elif mode == "rxaui":
                if qlm_test_mode[0] == "dis":
                    port_list.append("RXAUI%d.0" % bgx)
                elif (qlm_test_mode[0] == "rxaui") and (i != 0):
                    port_list.append("RXAUI%d.1" % bgx)
                else:
                    port_list.append("RXAUI%d.%d" % (bgx, i * 2))
            elif mode == "xfi":
                if qlm_test_mode[0] == "dis":
                    port_list.append("XFI%d.0" % bgx)
                    port_list.append("XFI%d.1" % bgx)
                elif qlm_test_mode[0] == "rxaui":
                    port_list.append("XFI%d.1" % bgx)
                    port_list.append("XFI%d.2" % bgx)
                else:
                    port_list.append("XFI%d.%d" % (bgx, i * 2 + 0))
                    port_list.append("XFI%d.%d" % (bgx, i * 2 + 1))
            elif mode == "xlaui":
                port_list.append("XLAUI%d" % bgx)
            elif mode == "10g":
                if qlm_test_mode[0] == "dis":
                    port_list.append("10GKR%d.0" % bgx)
                    port_list.append("10GKR%d.1" % bgx)
                elif qlm_test_mode[0] == "rxaui":
                    port_list.append("10GKR%d.1" % bgx)
                    port_list.append("10GKR%d.2" % bgx)
                else:
                    port_list.append("10GKR%d.%d" % (bgx, i * 2 + 0))
                    port_list.append("10GKR%d.%d" % (bgx, i * 2 + 1))
            elif mode == "40g":
                port_list.append("40GKR%d" % bgx)
            elif mode == "dis":
                pass
            elif mode == None:
                pass
            else:
                assert False, "Unexpected mode %s" % mode
    for p in range(4):
        port_list.append("FAKE%d" % p)
    for p in range(4):
        port_list.append("LBK0.%d" % p)
    port_list.append("RGMII0.0")
    return port_list

def set_mode(cnx, qlm_test_mode):
    cnx.sendEcho("qlm")
    cnx.match("=================================")
    cnx.match("QLM/DLM Menu")
    cnx.match("=================================")
    cnx.match("set) Change QLM/DLM configuration")
    cnx.matchRE("qlm0\\) .+\n")
    cnx.matchRE("qlm1\\) .+\n")
    cnx.matchRE("qlm2\\) .+\n")
    cnx.matchRE("qlm3\\) .+\n")
    cnx.match("tune) PRBS and SERDES Tuning")
    cnx.match("quit) Main menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("set")
    cnx.match("=================================")
    cnx.match("Select a DLM to Configure")
    cnx.match("=================================")
    cnx.match("qlm0) DLM 0 - Disabled")
    cnx.match("qlm1) DLM 1 - Disabled")
    cnx.match("qlm2) DLM 2 - Disabled")
    cnx.match("qlm3) DLM 3 - Disabled")
    cnx.match("quit) Exit menu")
    cnx.match("(INS)Menu choice []: ")
    for qlm in [0,2]:
        for i,dlm in enumerate([qlm,qlm+1]):
            if qlm_test_mode[i] == None:
                continue
            cnx.sendEcho("qlm%d" % dlm)
            cnx.match("=================================")
            cnx.match("Select a reference clock for DLM%d" % dlm)
            cnx.match("=================================")
            cnx.match("ext) External reference (DLM%d_REF_CLK)" % dlm)
            cnx.match("c0) Common clock 0 (DLMC_REF_CLK0)")
            cnx.match("c1) Common clock 1 (DLMC_REF_CLK1)")
            cnx.match("(INS)Menu choice []: ")
            cnx.sendEcho("c1")
            cnx.match("=================================")
            cnx.match("Select a mode for DLM%d" % dlm)
            cnx.match("=================================")
            cnx.waitfor("dis) Disabled")
            cnx.match("(INS)Menu choice []: ")
            cnx.sendEcho(qlm_test_mode[i])
            cnx.match("=================================")
            cnx.match("Select a DLM to Configure")
            cnx.match("=================================")
            cnx.matchRE("qlm0\\) .+\n")
            cnx.matchRE("qlm1\\) .+\n")
            cnx.matchRE("qlm2\\) .+\n")
            cnx.matchRE("qlm3\\) .+\n")
            cnx.match("quit) Exit menu")
            cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("quit")
    cnx.match("=================================")
    cnx.match("QLM/DLM Menu")
    cnx.match("=================================")
    cnx.match("set) Change QLM/DLM configuration")
    cnx.matchRE("qlm0\\) .+\n")
    cnx.matchRE("qlm1\\) .+\n")
    cnx.matchRE("qlm2\\) .+\n")
    cnx.matchRE("qlm3\\) .+\n")
    cnx.match("tune) PRBS and SERDES Tuning")
    cnx.match("quit) Main menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)

def run_traffic_gen(cnx, qlm_test_mode):
    cnx.sendEcho("tg")
    cnx.waitfor("BDK Traffic Generator")
    cnx.match("Type \"help\" for a list of commands")
    cnx.match("(INS)Command> ")
    cnx.sendEcho("loopback rgmii0.0 internal")
    cnx.waitfor("(INS)Command>")
    time.sleep(5)
    cnx.write("\r")
    cnx.waitfor("(INS)Command> ")
    cnx.write("\r")
    cnx.match("(INS)Command> ")
    cnx.sendEcho("default all")
    cnx.match("Default ports: ")
    ports = get_port_list(qlm_test_mode)
    print ports
    for p in ports:
        cnx.match(p)
    cnx.match("(INS)Command> ")
    cnx.sendEcho("link_speed")
    for p in ports:
        cnx.matchRE("Port %s: link_speed = [14].+\n" % p)
    cnx.match("(INS)Command> ")
    cnx.sendEcho("count 100")
    cnx.match("(INS)Command> ")
    cnx.sendEcho("start")
    cnx.match("(INS)Command> ")
    time.sleep(1)
    cnx.sendEcho("tx_packets_total")
    for p in ports:
        cnx.match("Port %s: tx_packets_total = 100\n" % p)
    cnx.match("(INS)Command> ")
    cnx.sendEcho("tx_octets_total")
    for p in ports:
        if p.startswith("FAKE") or p.startswith("LBK"):
            cnx.match("Port %s: tx_octets_total = 6000\n" % p)
        else:
            cnx.match("Port %s: tx_octets_total = 6400\n" % p)
    cnx.match("(INS)Command> ")
    cnx.sendEcho("rx_packets_total")
    for p in ports:
        cnx.match("Port %s: rx_packets_total = 100\n" % p)
    cnx.match("(INS)Command> ")
    cnx.sendEcho("rx_octets_total")
    for p in ports:
        if p.startswith("FAKE") or p.startswith("LBK"):
            cnx.match("Port %s: rx_octets_total = 6000\n" % p)
        else:
            cnx.match("Port %s: rx_octets_total = 6400\n" % p)
    cnx.match("(INS)Command> ")
    cnx.sendEcho("rx_errors")
    for p in ports:
        cnx.match("Port %s: rx_errors = 0\n" % p)
    cnx.match("(INS)Command> ")
    cnx.sendEcho("rx_validation_errors")
    for p in ports:
        cnx.match("Port %s: rx_validation_errors = 0\n" % p)
    cnx.match("(INS)Command> ")
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)

def run_test(cnx):
    for qlm_test_mode in TEST_MODES:
        test_boot.boot_normal(cnx)
        cnx.sendEcho("ilua")
        cnx.match("ILUA: Lua 5.2.0  Copyright (C) 1994-2007 Lua.org, PUC-Rio")
        cnx.match("\"quit\" to end")
        cnx.match("(INS)> ")
        for bgx in [0,1]:
            for p in range(4):
                cmd = "cavium.c.bdk_config_set_int(0x1000, cavium.CONFIG_PHY_ADDRESS, 0, %d, %d)" % (bgx, p)
                cnx.write(cmd + "\r")
                cnx.match(cmd)
                cnx.match("0")
                cnx.match("(INS)> ")
        cnx.sendEcho("quit")
        test_boot.wait_for_main_menu(cnx)
        set_mode(cnx, qlm_test_mode)
        run_traffic_gen(cnx, qlm_test_mode)

class Args:
    def __init__(self, mcu):
        self.mcu = "%s:9760" % mcu
        self.mcu2 = None
        self.bmc = None
        self.board = "ebb8104"
        self.console = "%s:9761" % mcu

def main(logName):
    log = connection.Log(logName)
    args = Args("b11-0036")
    cnx = boards.Board_EVB(args, log)
    run_test(cnx)
    cnx.close()

main("ebb8104-network-modes.log")
