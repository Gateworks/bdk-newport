# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import sys
import time
import boards
import connection
import test_boot
import test_dram
import test_trafficgen

DO_FAKE_TESTS = False
DO_LBK_TESTS = False

TOTAL_QLMS = 4

TEST_MODES_QLM1 = [
    "sgmii-1250",
    "1g_x-1250",
    "qsgmii-5000",
    "xaui-3125",
    "xaui-6250",
    "rxaui-6250",
    "xfi-10312",
    "sfi-10312",
    "xlaui-10312",
    "xlaui_c2m-10312",
    "10g_kr-10312",
    "40g_cr4-10312",
    "40g_kr4-10312",
    "20gaui_c2c-20625",
    "25gaui_c2c-25781",
    "25gaui_c2m-25781",
    "25g_cr-25781",
    "25g_kr-25781",
    "40gaui_2_c2c-20625",
    "50gaui_2_c2c-25781",
    "50gaui_2_c2m-25781",
    "50g_cr2-25781",
    "50g_kr2-25781",
    "80gaui_4_c2c-20625",
    "caui_4_c2c-25781",
    "caui_4_c2m-25781",
    "100g_cr4-25781",
    "100g_kr4-25781",
]

TEST_MODES = {
    1: TEST_MODES_QLM1,
}

TEST_QLMS = TEST_MODES.keys()
TEST_QLMS.sort()

#TEST_GSERN_LOOP = ["near", "core", "none"]
TEST_GSERN_LOOP = ["none"]

def set_fec(cnx):
    cnx.sendEcho("ilua")
    cnx.match("ILUA: Lua 5.2.0  Copyright (C) 1994-2007 Lua.org, PUC-Rio")
    cnx.match("\"quit\" to end")
    cnx.match("(INS)> ")
    for cgx in range(3):
        for p in range(4):
            cmd = "octeontx.c.bdk_config_set_int(3, octeontx.CONFIG_NETWORK_FLAGS, 0, %d, %d)" % (cgx, p)
            cnx.write(cmd + "\r")
            cnx.match(cmd)
            cnx.match("0")
            cnx.match("(INS)> ")
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)

def set_mode(cnx, qlm, qlm_test_mode, gsern_loop):
    cnx.sendEcho("qlm")
    cnx.match("=================================")
    cnx.match("QLM/DLM Menu")
    cnx.match("=================================")
    cnx.match("set) Change QLM/DLM configuration")
    for q in range(TOTAL_QLMS):
        cnx.matchRE("qlm%d\\) .+\n" % q)
    cnx.match("tune) PRBS and SERDES Tuning")
    cnx.match("quit) Main menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("set")
    cnx.match("=================================")
    cnx.match("Select a QLM to Configure")
    cnx.match("=================================")
    for q in range(TOTAL_QLMS):
        cnx.matchRE("qlm%d[)] [DQ]LM%d - Disabled" % (q,q))
    cnx.match("quit) Exit menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("qlm%d" % qlm)
    cnx.match("=================================")
    cnx.matchRE("Select a mode for [DQ]LM%d" % qlm)
    cnx.match("=================================")
    cnx.waitfor("disabled) Disabled")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho(qlm_test_mode)
    cnx.match("=================================")
    cnx.match("Select a QLM to Configure")
    cnx.match("=================================")
    for q in range(TOTAL_QLMS):
        cnx.matchRE("qlm%d\\) .+\n" % q)
    cnx.match("quit) Exit menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("quit")
    cnx.match("=================================")
    cnx.match("QLM/DLM Menu")
    cnx.match("=================================")
    cnx.match("set) Change QLM/DLM configuration")
    for q in range(TOTAL_QLMS):
        cnx.matchRE("qlm%d\\) .+\n" % q)
    cnx.match("tune) PRBS and SERDES Tuning")
    cnx.match("quit) Main menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("tune")
    cnx.match("=================================")
    cnx.match("PRBS and SERDES Tuning Menu")
    cnx.match("=================================")
    cnx.matchRE("qlm[)] Select active QLM/DLM [(]Currently [DQ]LM[0-9][)]")
    cnx.waitfor("quit) Main menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("qlm")
    cnx.match("(INS)QLM/DLM (0 - %d) [0]: " % (TOTAL_QLMS-1))
    cnx.sendEcho("%d" % qlm)
    cnx.match("=================================")
    cnx.match("PRBS and SERDES Tuning Menu")
    cnx.match("=================================")
    cnx.matchRE("qlm[)] Select active QLM/DLM [(]Currently [DQ]LM[0-9][)]")
    cnx.waitfor("quit) Main menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("loop")
    cnx.match("=================================")
    cnx.match("Loopback Type")
    cnx.match("=================================")
    cnx.match("none) No loopback")
    cnx.match("core) Core loopback, TX to RX in digital domain")
    cnx.match("near) Near end, TX to RX in analog domain")
    cnx.match("sh) Shallow loopback, line side RX to TX")
    cnx.match("quit) No change")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho(gsern_loop)
    cnx.match("=================================")
    cnx.match("PRBS and SERDES Tuning Menu")
    cnx.match("=================================")
    cnx.matchRE("qlm[)] Select active QLM/DLM [(]Currently [DQ]LM[0-9][)]")
    cnx.waitfor("quit) Main menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("quit")
    cnx.match("=================================")
    cnx.match("QLM/DLM Menu")
    cnx.match("=================================")
    cnx.match("set) Change QLM/DLM configuration")
    for q in range(TOTAL_QLMS):
        cnx.matchRE("qlm%d\\) .+\n" % q)
    cnx.match("tune) PRBS and SERDES Tuning")
    cnx.match("quit) Main menu")
    cnx.match("(INS)Menu choice []: ")
    cnx.sendEcho("quit")

def run_traffic_gen(cnx):
    test_boot.wait_for_main_menu(cnx)
    test_trafficgen.start_trafficgen(cnx)
    port_list = test_trafficgen.get_port_list(cnx)
    try:
        link_speeds = test_trafficgen.check_links_up(cnx, port_list)
    except:
        return "FAIL-LINK"
    if DO_FAKE_TESTS:
        try:
            test_trafficgen.run_scan_size(cnx, ["FAKE0","FAKE1","FAKE2","FAKE3"])
            test_trafficgen.run_perf_test(cnx, ["FAKE0","FAKE1","FAKE2","FAKE3"])
        except:
            return "FAIL-FAKE"
    if DO_LBK_TESTS:
        try:
            test_trafficgen.run_scan_size(cnx, ["LBK0.0","LBK0.1","LBK0.2","LBK0.3"])
            test_trafficgen.run_perf_test(cnx, ["LBK0.0","LBK0.1","LBK0.2","LBK0.3"])
        except:
            return "FAIL-LBK"
    result = "TBD"
    for port in port_list:
        if "FAKE" in port:
            continue
        if "LBK" in port:
            continue
        try:
            test_trafficgen.run_scan_size(cnx, [port])
        except:
            return "FAIL-SCAN"
        try:
            perf_results = test_trafficgen.run_perf_test(cnx, [port], use_validation=False)
            max_speed = link_speeds[port]
            min_speed = max_speed * 99 / 100
            sizes = perf_results.keys()
            sizes.sort()
            sizes.reverse()
            for size in sizes:
                if size < 512: # Don't care about small packet performance
                    continue
                tx = perf_results[size][0]
                rx = perf_results[size][1]
                if tx < min_speed:
                    result = "TX-SLOW(%d-%d)" % (size, tx)
                elif rx < min_speed:
                    result = "RX-SLOW(%d-%d)" % (size, rx)
                elif rx > max_speed:
                    result = "RX-FAST(%d-%d)" % (size, rx)
                elif tx > max_speed:
                    result = "TX-FAST(%d-%d)" % (size, tx)
                else:
                    result = "Pass(%d)" % max_speed
        except:
            return "FAIL-PERF"
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)
    return result

def run_test(cnx):
    gsern_loop_results = {}
    sort_order = []
    for gsern_loop in TEST_GSERN_LOOP:
        gsern_loop_results[gsern_loop] = {}
        results = gsern_loop_results[gsern_loop]
        for qlm in TEST_QLMS:
            for qlm_test_mode in TEST_MODES[qlm]:
                if not qlm_test_mode in sort_order:
                    sort_order.append(qlm_test_mode)
                if not qlm_test_mode in results:
                    results[qlm_test_mode] = {}
                if not qlm in results[qlm_test_mode]:
                    results[qlm_test_mode][qlm] = {}
                if cnx == None:
                    results[qlm_test_mode][qlm] = "TBD%d(###)" % qlm + gsern_loop
                    continue
                test_boot.boot_normal(cnx, False, True)
                set_fec(cnx)
                set_mode(cnx, qlm, qlm_test_mode, gsern_loop)
                try:
                    results[qlm_test_mode][qlm] = run_traffic_gen(cnx)
                    cnx.log("Result for QLM%d, mode %s, %s" % (qlm, qlm_test_mode, results[qlm_test_mode][qlm]))
                except:
                    results[qlm_test_mode][qlm] = "FAIL"
                    cnx.log("Fail for QLM%d, mode %s" % (qlm, qlm_test_mode))
    print
    print "---"
    print "EBB9504 with QLM loopbacks on QLM1"
    print "---"
    output = "%-20s" % "GSERN loop mode"
    for gsern_loop in TEST_GSERN_LOOP:
        for qlm in TEST_QLMS:
            output += " %13s" % gsern_loop
    print output
    output = "%-20s" % "Mode"
    for gsern_loop in TEST_GSERN_LOOP:
        for qlm in TEST_QLMS:
            output += " %13s" % ("QLM%d" % qlm)
    print output
    for mode in sort_order:
        output = "%-20s" % mode
        for gsern_loop in TEST_GSERN_LOOP:
            results = gsern_loop_results[gsern_loop]
            for qlm in TEST_QLMS:
                if qlm in results[mode]:
                    status = results[mode][qlm]
                else:
                    status = "-"
                output += " %13s" % status
        print output
    print "---"

class Args:
    def __init__(self, mcu):
        self.mcu = "%s:9760" % mcu
        self.mcu2 = None
        self.bmc = None
        self.board = "ebb9504"
        self.console = "%s:9761" % mcu

def main(logName):
    log = connection.Log(logName)
    args = Args(sys.argv[1])
    cnx = boards.Board_EVB(args, log)
    run_test(cnx)
    cnx.close()

main("ebb9504-network-test-qlm-loopback.log")
