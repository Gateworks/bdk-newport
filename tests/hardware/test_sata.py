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
    cnx.match("SATA Menu")
    cnx.match("=================================")
    if cnx.multinode:
        cnx.matchRE("node\\) Select active node \\(Currently [01]\\)")
    cnx.matchRE("port\\) Select SATA port \\(Currently [0-9]+\\)")
    cnx.match("id) Perform an identify disk")
    cnx.match("sw-retimed) Enter Local-end Retimed Loopback")
    cnx.match("sw-tx4) Enter Local-end Transmit Only, Simultaneous switching outputs pattern (SSOP)")
    cnx.match("sw-tx5) Enter Local-end Transmit Only, High transition density pattern (HTDP)")
    cnx.match("sw-tx6) Enter Local-end Transmit Only, Low transition density pattern (LTDP)")
    cnx.match("sw-tx7) Enter Local-end Transmit Only, Low frequency spectral component pattern (LFSCP)")
    cnx.match("sw-tx8) Enter Local-end Transmit Only, Composite pattern (COMP)")
    cnx.match("sw-tx9) Enter Local-end Transmit Only, Lone bit pattern (LBP)")
    cnx.match("sw-tx10) Enter Local-end Transmit Only, Mid frequency test pattern (MFTP)")
    cnx.match("sw-tx11) Enter Local-end Transmit Only, High frequency test pattern (HFTP)")
    cnx.match("sw-tx12) Enter Local-end Transmit Only, Low frequency test pattern (LFTP)")
    cnx.match("reset) Reset the controller")
    cnx.match("hex) Hex display")
    cnx.match("w0) Write pattern 0x00")
    cnx.match("r0) Read  pattern 0x00")
    cnx.match("w255) Write pattern 0xff")
    cnx.match("r255) Read  pattern 0xff")
    cnx.match("w85) Write pattern 0x55")
    cnx.match("r85) Read  pattern 0x55")
    cnx.match("w170) Write pattern 0xaa")
    cnx.match("r170) Read  pattern 0xaa")
    cnx.match("auto) Run automated pattern test")
    cnx.match("margin) Run margining tool")
    cnx.match("quit) Main menu")

#
# Perform a disk ID
#
def sata_id_detect(cnx):
    cnx.sendEcho("id")
    cnx.matchRE("N[01].SATA[0-9]+: Model=\"[^\"]+\", Firmware=\"[^\"]+\", Serial=\"[^\"]+\", Sectors=[0-9]+, Link=Gen[1-3]")

#
# Run all DRAM tests over 64MB of memory
#
def sata_detect(cnx, board_info):
    for sata in board_info["sata"]:
        cnx.sendEcho("sata")
        wait_for_main_menu(cnx)
        cnx.sendEcho("port")
        cnx.matchRE("\\(INS\\)SATA port to use \\(0 - [0-9]+\\) \\[0\\]:")
        cnx.sendEcho("%d" % sata)
        wait_for_main_menu(cnx)
        sata_id_detect(cnx)
        wait_for_main_menu(cnx)
        cnx.sendEcho("quit")
        test_boot.wait_for_main_menu(cnx)

