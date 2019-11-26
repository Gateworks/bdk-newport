# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import test_boot

#
# Wait for the DRAM main menu
#
def wait_for_main_menu(cnx):
    cnx.match("=================================")
    cnx.match("DRAM Menu")
    cnx.match("=================================")
    if cnx.multinode:
        cnx.match("node) Select active node (Currently 0)")
    cnx.match("verbose) Change verbosity level (Currently 0)")
    cnx.match("setenv) Set environment variable")
    cnx.match("getenv) Get environment variable")
    cnx.match("showenv) Show environment variables")
    cnx.match("tune) DDR Read Tuning")
    cnx.match("margin) DDR Margining Tool")
    cnx.match("test) Memory Testing Menu")
    cnx.match("quit) Main menu")
    cnx.match("(INS)Menu choice []:")
#
# Wait for the DRAM test menu
#
def wait_for_test_menu(cnx, ccpi=False):
    cnx.match("=================================")
    cnx.matchRE("DRAM Test Menu - [ ]*[0-9]+ MB, [0-9]+ MT/s, DDR[34] [UR]DIMM")
    cnx.match("=================================")
    cnx.matchRE("cores\\) Bringup Cores for multi-core testing \\([0-9]+\\)")
    cnx.match("repeat) Number of times to repeat the test (1)")
    cnx.matchRE("start\\) Starting address \\(0x[0-9a-fA-F]*\\)")
    cnx.matchRE("length\\) Length of the range to check \\([^)]*\\)")
    cnx.match("64MB) Set test range from 64MB to 128MB")
    cnx.match("all) Run all DRAM tests")
    cnx.match("test0) Data Bus")
    cnx.match("test1) Address Bus")
    cnx.match("test2) Marching Rows")
    cnx.match("test3) Random Data")
    cnx.match("test4) Random XOR (32 Burst)")
    cnx.match("test5) Self Address")
    cnx.match("test6) March C- Solid Bits")
    cnx.match("test7) March C- Checkerboard")
    cnx.match("test8) Walking Ones Left")
    cnx.match("test9) Walking Ones Right")
    cnx.match("test10) Walking Zeros Left")
    cnx.match("test11) Walking Zeros Right")
    cnx.match("test12) Random XOR (224 Burst)")
    cnx.match("test13) Fast Scan")
    cnx.match("spec) Run special DRAM tests")
    cnx.match("abort) Abort on Errors (Currently ON)")
    cnx.match("batch) Batch mode (Currently OFF)")
    if cnx.multinode:
        if ccpi:
            cnx.match("ccpi) Use CCPI cross node (Currently ON)")
        else:
            cnx.match("ccpi) Use CCPI cross node (Currently OFF)")
    cnx.match("inject_s) Inject a single bit memory error")
    cnx.match("inject_d) Inject a double bit memory error")
    cnx.match("inject_p) Inject a DRAM parity error")
    cnx.match("inject_r) Test Memory Preservation")
    cnx.match("quit) Main menu")
    cnx.match("(INS)Menu choice []:")

#
# Wait for a single DRAM test
#
def wait_for_dram_test(cnx, test_name):
    cnx.match("Starting Test \"%s\" for" % test_name)
    cnx.matchRE("\\[0x[0-9a-fA-F]+:0x[0-9a-fA-F]+\\] using [0-9]* core\\(s\\)")
    timeout = 600; # Default to 10 min
    while True:
        try:
            cnx.matchRE("[0-9]+\\.[0-9]% complete, testing \\[0x[0-9a-fA-F]+:0x[0-9a-fA-F]+\\]", timeout=timeout)
        except:
            break
    if cnx.board == "asim":
        return
    cnx.matchRE("Node 0, LMC0: ops [0-9]*, cycles [0-9]*, used [0-9]*\\.[0-9]\\%", timeout=timeout)
    try:
        # These messages vary by chip config
        for i in range(7):
            cnx.matchRE("Node [0-1], LMC[0-3]: ops [0-9]*, cycles [0-9]*, used [0-9]*\\.[0-9]\\%", timeout=1)
        for i in range(8):
            cnx.matchRE("Node [0-1], CCPI[0-2]: busy [0-9]*, total [0-9]*, used [0-9]*\\.[0-9]\\%", timeout=1)
    except:
        pass

#
# Wait for all DRAM tests
#
def wait_for_all_dram_test(cnx):
    tests = []
    tests.append("Data Bus")
    tests.append("Address Bus")
    tests.append("Marching Rows")
    tests.append("Random Data")
    tests.append("Random XOR (32 Burst)")
    tests.append("Self Address")
    tests.append("March C- Solid Bits")
    tests.append("March C- Checkerboard")
    tests.append("Walking Ones Left")
    tests.append("Walking Ones Right")
    tests.append("Walking Zeros Left")
    tests.append("Walking Zeros Right")
    tests.append("Random XOR (224 Burst)")
    tests.append("Fast Scan")
    for t in tests:
        wait_for_dram_test(cnx, t)

#
# Run all DRAM tests over all of memory
#
def dram_all(cnx, board_info):
    cnx.sendEcho("ddr")
    wait_for_main_menu(cnx)
    cnx.sendEcho("test")
    wait_for_test_menu(cnx)
    cnx.sendEcho("cores")
    wait_for_test_menu(cnx)
    cnx.sendEcho("all")
    cnx.match("Pass 1 of 1")
    wait_for_all_dram_test(cnx)
    cnx.matchRE("All tests passed \\(time [0-9]+:[0-9]+:[0-9]+\\)")
    cnx.matchRE("Total time [0-9]+:[0-9][0-9]:[0-9][0-9]")
    wait_for_test_menu(cnx)
    cnx.sendEcho("quit")
    wait_for_main_menu(cnx)
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)

#
# Run all DRAM tests over 64MB of memory
#
def dram_short(cnx, board_info, ccpi=False):
    cnx.sendEcho("ddr")
    wait_for_main_menu(cnx)
    cnx.sendEcho("test")
    wait_for_test_menu(cnx)
    cnx.sendEcho("cores")
    wait_for_test_menu(cnx)
    if cnx.board == "asim":
        cnx.sendEcho("start")
        cnx.matchRE("\\(INS\\)Physical byte address to start memory test at \\[0\\]:")
        cnx.sendEcho("0x4000000")
        wait_for_test_menu(cnx)
        cnx.sendEcho("length")
        cnx.matchRE("\\(INS\\)Length of region in bytes, or -1 for all of memory \\[-1\\]:")
        cnx.sendEcho("0x100000")
        wait_for_test_menu(cnx)
    else:
        cnx.sendEcho("64MB")
        wait_for_test_menu(cnx)
    if ccpi:
        cnx.sendEcho("ccpi")
        wait_for_test_menu(cnx, ccpi)
    cnx.sendEcho("all")
    cnx.match("Pass 1 of 1")
    wait_for_all_dram_test(cnx)
    cnx.matchRE("All tests passed \\(time [0-9]+:[0-9]+:[0-9]+\\)")
    cnx.matchRE("Total time [0-9]+:[0-9][0-9]:[0-9][0-9]")
    wait_for_test_menu(cnx, ccpi)
    cnx.sendEcho("quit")
    wait_for_main_menu(cnx)
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)

#
# Run all DRAM tests over 64MB of memory
#
def dram_ccpi(cnx, board_info):
    dram_short(cnx, board_info, ccpi=True)

