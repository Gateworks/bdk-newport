# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import time
import boards
import connection
import test_boot
import test_dram

# This script assumes a QLM cable is connected between the two connectors.
# MCU module configs are all disabled
# This test runs 100 packets at 60 bytes each across the interface and expects
# no errors.

TEST_MODES = [
    ["sgmii-1250",      "sgmii-1250"],
    ["sgmii-1250",      "1g_x-1250"],
    ["sgmii-1250",      "rxaui-6250"],
    ["sgmii-1250",      "xfi-10312"],
    ["sgmii-1250",      "10g_kr-10312"],
    ["sgmii-1250",      "disabled"],
    ["1g_x-1250",       "sgmii-1250"],
    ["1g_x-1250",       "1g_x-1250"],
    ["1g_x-1250",       "rxaui-6250"],
    ["1g_x-1250",       "xfi-10312"],
    ["1g_x-1250",       "10g_kr-10312"],
    ["1g_x-1250",       "disabled"],
    #["qsgmii-5000",    "disabled"],    # FIXME: Not working
    ["rxaui-6250",      "sgmii-1250"],
    ["rxaui-6250",      "1g_x-1250"],
    ["rxaui-6250",      "rxaui-6250"],
    ["rxaui-6250",      "xfi-10312"],
    ["rxaui-6250",      "10g_kr-10312"],
    ["rxaui-6250",      "disabled"],
    ["xfi-10312",       "sgmii-1250"],
    ["xfi-10312",       "1g_x-1250"],
    ["xfi-10312",       "rxaui-6250"],
    ["xfi-10312",       "xfi-10312"],
    ["xfi-10312",       "10g_kr-10312"],
    ["xfi-10312",       "disabled"],
    ["10g_kr-10312",    "sgmii-1250"],
    ["10g_kr-10312",    "1g_x-1250"],
    ["10g_kr-10312",    "rxaui-6250"],
    ["10g_kr-10312",    "xfi-10312"],
    ["10g_kr-10312",    "10g_kr-10312"],
    ["10g_kr-10312",    "disabled"],
    ["disabled",        "sgmii-1250"],
    ["disabled",        "1g_x-1250"],
    #["disabled",       "qsgmii-5000"], # FIXME: Not working
    ["disabled",        "rxaui-6250"],
    ["disabled",        "xfi-10312"],
    ["disabled",        "10g_kr-10312"],
    ["disabled",        "disabled"]
]

def get_port_list(qlm_test_mode):
    port_list = []
    for bgx in range(2):
        for i,mode in enumerate(qlm_test_mode):
            if mode == "sgmii-1250":
                if qlm_test_mode[0] == "disabled":
                    port_list.append("SGMII%d.0" % bgx)
                    port_list.append("SGMII%d.1" % bgx)
                elif qlm_test_mode[0] == "rxaui-6250":
                    port_list.append("SGMII%d.1" % bgx)
                    port_list.append("SGMII%d.2" % bgx)
                else:
                    port_list.append("SGMII%d.%d" % (bgx, i * 2 + 0))
                    port_list.append("SGMII%d.%d" % (bgx, i * 2 + 1))
            elif mode == "1g_x-1250":
                if qlm_test_mode[0] == "disabled":
                    port_list.append("1GX%d.0" % bgx)
                    port_list.append("1GX%d.1" % bgx)
                elif qlm_test_mode[0] == "rxaui-6250":
                    port_list.append("1GX%d.1" % bgx)
                    port_list.append("1GX%d.2" % bgx)
                else:
                    port_list.append("1GX%d.%d" % (bgx, i * 2 + 0))
                    port_list.append("1GX%d.%d" % (bgx, i * 2 + 1))
            elif mode == "qsgmii-5000":
                port_list.append("QSGMII%d.0" % bgx)
                port_list.append("QSGMII%d.1" % bgx)
                port_list.append("QSGMII%d.2" % bgx)
                port_list.append("QSGMII%d.3" % bgx)
            elif mode == "xaui-3125":
                port_list.append("XAUI%d" % bgx)
            elif mode == "xaui-6250":
                port_list.append("DXAUI%d" % bgx)
            elif mode == "rxaui-6250":
                if qlm_test_mode[0] == "disabled":
                    port_list.append("RXAUI%d.0" % bgx)
                elif (qlm_test_mode[0] == "rxaui-6250") and (i != 0):
                    port_list.append("RXAUI%d.1" % bgx)
                else:
                    port_list.append("RXAUI%d.%d" % (bgx, i * 2))
            elif mode == "xfi-10312":
                if qlm_test_mode[0] == "disabled":
                    port_list.append("XFI%d.0" % bgx)
                    port_list.append("XFI%d.1" % bgx)
                elif qlm_test_mode[0] == "rxaui-6250":
                    port_list.append("XFI%d.1" % bgx)
                    port_list.append("XFI%d.2" % bgx)
                else:
                    port_list.append("XFI%d.%d" % (bgx, i * 2 + 0))
                    port_list.append("XFI%d.%d" % (bgx, i * 2 + 1))
            elif mode == "xlaui-10312":
                port_list.append("XLAUI%d" % bgx)
            elif mode == "10g_kr-10312":
                if qlm_test_mode[0] == "disabled":
                    port_list.append("10GKR%d.0" % bgx)
                    port_list.append("10GKR%d.1" % bgx)
                elif qlm_test_mode[0] == "rxaui-6250":
                    port_list.append("10GKR%d.1" % bgx)
                    port_list.append("10GKR%d.2" % bgx)
                else:
                    port_list.append("10GKR%d.%d" % (bgx, i * 2 + 0))
                    port_list.append("10GKR%d.%d" % (bgx, i * 2 + 1))
            elif mode == "40g_kr4-10312":
                port_list.append("40GKR%d" % bgx)
            elif mode == "disabled":
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
    cnx.match("Select a QLM to Configure")
    cnx.match("=================================")
    cnx.match("qlm0) DLM0 - Disabled")
    cnx.match("qlm1) DLM1 - Disabled")
    cnx.match("qlm2) DLM2 - Disabled")
    cnx.match("qlm3) DLM3 - Disabled")
    cnx.match("quit) Exit menu")
    cnx.match("(INS)Menu choice []: ")
    for qlm in [0,2]:
        for i,dlm in enumerate([qlm,qlm+1]):
            if qlm_test_mode[i] == None:
                continue
            cnx.sendEcho("qlm%d" % dlm)
            cnx.match("=================================")
            cnx.match("Select a mode for DLM%d" % dlm)
            cnx.match("=================================")
            cnx.waitfor("disabled) Disabled")
            cnx.match("(INS)Menu choice []: ")
            cnx.sendEcho(qlm_test_mode[i])
            cnx.match("=================================")
            cnx.match("Select a QLM to Configure")
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
    cnx.waitfor("(INS)Command>")
    cnx.sendEcho("loopback rgmii0.0 internal")
    cnx.waitfor("(INS)Command>")
    cnx.sendEcho("wait_links")
    cnx.waitfor("(INS)Command> ")
    cnx.write("\r")
    cnx.match("(INS)Command> ")
    time.sleep(1)
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
                cmd = "octeontx.c.bdk_config_set_int(0x1000, octeontx.CONFIG_PHY_ADDRESS, 0, %d, %d)" % (bgx, p)
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
    args = Args("ebb8104")
    cnx = boards.Board_EVB(args, log)
    run_test(cnx)
    cnx.close()

main("ebb8104-network-modes.log")
