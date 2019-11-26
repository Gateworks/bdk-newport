# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
import test_boot

def get_refclk_for_mode(cnx, qlm_mode):
    if qlm_mode.startswith("rc"):
        return "c0" # 100Mhz clock
    elif qlm_mode.startswith("ep"):
        return "ext" # External clock
    elif qlm_mode.startswith("sata"):
        return "c0" # 100Mhz clock
    else: # Should be networking with a 156Mhz clock
        if cnx.chip_model.startswith("CN8"):
            return "c1"
        else:
            return "c2"

#
# Wait for the QLM main menu
#
def wait_for_main_menu(cnx):
    cnx.match("=================================")
    cnx.match("QLM/DLM Menu")
    cnx.match("=================================")
    if cnx.multinode:
        cnx.matchRE("node\\) Select active node \\(Currently [01]\\)")
    if cnx.chip_model.startswith("CN8") or (cnx.chip_model == "CN96XX") or (cnx.chip_model == "CNF95XX"):
        cnx.match("set) Change QLM/DLM configuration")
    num_qlms = 0
    for qlm in range(32):
        try:
            match = cnx.matchRE("qlm%d\\) [QD]LM%d - .+, ref .+ Mhz" % (qlm, qlm))
            if not "Cavium Coherent Processor Interconnect" in match.group(0):
                num_qlms += 1
        except:
            break
    cnx.match("tune) PRBS and SERDES Tuning")
    cnx.match("quit) Main menu")
    cnx.match("(INS)Menu choice []:")
    return num_qlms

#
# Wait for the QLM/DLM set menu
#
def wait_for_main_set_menu(cnx):
    cnx.match("=================================")
    cnx.matchRE("Select a [DQ]LM to Configure")
    cnx.match("=================================")
    for qlm in range(32):
        try:
            cnx.matchRE("qlm%d\\) [QD]LM%d - .+\n" % (qlm, qlm))
        except:
            break
    cnx.match("quit) Exit menu")
    cnx.match("(INS)Menu choice []:")

#
# Configure a QLM/DLM once in the set menu. Pass None
# as qlm_mode to get a list of possible modes. ref_clk
# can be passed as None too.
#
def configure_qlm(cnx, board_info, qlm, ref_clk, qlm_mode):
    cnx.sendEcho("qlm%d" % qlm)
    cnx.match("=================================")
    cnx.matchRE("Select a mode for [DQ]LM%d" % qlm)
    cnx.match("=================================")
    modes = []
    while True:
        match = cnx.matchRE("([a-z0-9-_]+)\\) .+\n")
        modes.append(match.group(1))
        if match.group(1) == "disabled":
            break
    cnx.match("(INS)Menu choice []:")
    if qlm_mode:
        cnx.sendEcho(qlm_mode)
    else:
        cnx.send(chr(3))
        cnx.match("ERROR: interrupted!")
        wait_for_main_set_menu(cnx)
        cnx.match("Selection not valid. Please choose an entry from the list above.")
    wait_for_main_set_menu(cnx)
    return modes

#
# Detect the number of QLMs and all their modes
#
def qlm_detect(cnx, board_info):
    cnx.sendEcho("qlm")
    num_qlms = wait_for_main_menu(cnx)
    qlm_modes = {}
    cnx.sendEcho("set")
    wait_for_main_set_menu(cnx)
    for qlm in range(num_qlms):
        qlm_modes[qlm] = configure_qlm(cnx, board_info, qlm, None, None)
    cnx.sendEcho("quit")
    wait_for_main_menu(cnx)
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)
    return qlm_modes


#
# Run through all QLM configurations making sure the menus
# work. This test doesn't check that the mode was set, just
# that the menus functioned.
#
def qlm_config_all(cnx, board_info):
    qlm_modes = qlm_detect(cnx, board_info)
    cnx.sendEcho("qlm")
    num_qlms = wait_for_main_menu(cnx)
    cnx.sendEcho("set")
    wait_for_main_set_menu(cnx)
    for qlm in range(num_qlms):
        for mode in qlm_modes[qlm]:
            refclk = get_refclk_for_mode(cnx, mode)
            configure_qlm(cnx, board_info, qlm, refclk, mode)
    cnx.sendEcho("quit")
    wait_for_main_menu(cnx)
    cnx.sendEcho("quit")
    test_boot.wait_for_main_menu(cnx)

