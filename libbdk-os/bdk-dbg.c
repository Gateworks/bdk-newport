/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-ap.h"
#include "libbdk-arch/bdk-csrs-uaa.h"

/**
 * The routine in this file are called when some unknown bad thing has happened.
 * They bypass the normal output mechanism and push characters directly to the
 * uart. Hopefully this will allow them to work when everything else has died.
 *
 * @param c      Character to print
 */
void bdk_dbg_uart_char(char c)
{
    const int id = 0;
    const bdk_node_t node = bdk_numa_master();

    BDK_CSR_INIT(fr, node, BDK_UAAX_FR(id));
    while (fr.s.txff) /* Spin while full */
        fr.u = BDK_CSR_READ(node, BDK_UAAX_FR(id));
    BDK_CSR_WRITE(node, BDK_UAAX_DR(id), c);
}

/**
 * Write a low level string
 *
 * @param s      String to write
 */
void bdk_dbg_uart_str(const char *s)
{
    while (*s)
    {
        bdk_dbg_uart_char(*s);
        s++;
    }
}

/**
 * Write a low level 64bit number in hex
 *
 * @param value  Value to write
 */
void bdk_dbg_uart_hex(uint64_t value)
{
    bdk_dbg_uart_char('0');
    bdk_dbg_uart_char('x');
    for (int i=15; i>=0; i--)
    {
        char c = (value >> (i*4)) & 0xf;
        if (c >= 10)
            c += 'a' - 10;
        else
            c += '0';
        bdk_dbg_uart_char(c);
    }
}

/**
 * Dump multiple samples of all cores out of reset on the given node
 *
 * @param node   Node to dump core PCs for
 */
void bdk_dbg_dump_pc(bdk_node_t node)
{
    uint64_t pp_reset = BDK_CSR_READ(node, BDK_RST_PP_RESET);
    int num_cores = bdk_get_num_cores(node);
    int my_core = bdk_get_core_num();

    bdk_dbg_uart_str("\r\n\r\n\r\nNode ");
    bdk_dbg_uart_char(node + '0');
    bdk_dbg_uart_str(": Dumping PCs (4 samples):\r\n");

    for (int core=0; core<num_cores; core++)
    {
        if (pp_reset & (1ull << core))
            continue;
        bdk_dbg_uart_str("Core ");
        bdk_dbg_uart_char(core / 10 + '0');
        bdk_dbg_uart_char(core % 10 + '0');
        for (int sample=0; sample < 4; sample++)
        {
            uint64_t pc = bdk_sysreg_read(node, core, BDK_AP_CVM_DEBUG3_EL3);
            bdk_dbg_uart_char(' ');
            bdk_dbg_uart_hex(pc);
        }
        if ((node == bdk_numa_local()) && (my_core == core))
            bdk_dbg_uart_str(" (doing dump)");
        bdk_dbg_uart_str("\r\n");
    }
    bdk_dbg_uart_str("\r\n");
}

/**
 * Check to see if someone sent a break signal to uart 0. This is treated
 * as a magic dump key to get info out of the BDK if it is locked up. Using
 * minicom, this is sent with Control-A,F.
 */
void bdk_dbg_check_magic(void)
{
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return;

    /* Dump PCs if we receive a break signal */
    BDK_CSR_INIT(uaax_ris, bdk_numa_master(), BDK_UAAX_RIS(0));
    if (bdk_likely(!uaax_ris.s.beris))
        return;

    static bdk_spinlock_t lock;
    bdk_spinlock_lock(&lock);

    uaax_ris.u = BDK_CSR_READ(bdk_numa_master(), BDK_UAAX_RIS(0));
    if (uaax_ris.s.beris)
    {
        BDK_CSR_DEFINE(uaax_icr, BDK_UAAX_ICR(0));
        uaax_icr.u = 0;
        uaax_icr.s.beic = 1;
        BDK_CSR_WRITE(bdk_numa_master(), BDK_UAAX_ICR(0), uaax_icr.u);
        bdk_dbg_dump_pc(bdk_numa_master());
    }
    bdk_spinlock_unlock(&lock);
}

