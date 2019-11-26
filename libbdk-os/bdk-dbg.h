/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Utility functions for low level debug
 *
 * @defgroup debug Low level debug
 * @{
 */

/**
 * Set to enable checking for a uart break signal to cause a core register dump
 */
#define BDK_DBG_MAGIC_ENABLE 0

/**
 * The routine in this file are called when some unknown bad thing has happened.
 * They bypass the normal output mechanism and push characters directly to the
 * uart. Hopefully this will allow them to work when everything else has died.
 *
 * @param c      Character to print
 */
extern void bdk_dbg_uart_char(char c);

/**
 * Write a low level string
 *
 * @param s      String to write
 */
extern void bdk_dbg_uart_str(const char *s);

/**
 * Write a low level 64bit number in hex
 *
 * @param value  Value to write
 */
extern void bdk_dbg_uart_hex(uint64_t value);

/**
 * Dump multiple samples of all cores out of reset on the given node
 *
 * @param node   Node to dump core PCs for
 */
extern void bdk_dbg_dump_pc(bdk_node_t node);

/**
 * Check to see if someone sent a break signal to uart 0. This is treated
 * as a magic dump key to get info out of the BDK if it is locked up. Using
 * minicom, this is sent with Control-A,F.
 */
extern void bdk_dbg_check_magic(void);

/** @} */
