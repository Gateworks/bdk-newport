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
#include "libbdk-arch/bdk-csrs-mio_fus.h"

/**
 * Initialize the CCPI links, but don't bringup the other nodes
 *
 * @return Zero on success, negative on failure
 */
static int bdk_boot_ccpi_link(void)
{
    /* multi_node: 0 = off, 1 = on, 2 = auto detect */
    int multi_node = bdk_config_get_int(BDK_CONFIG_MULTI_NODE);
    if (!multi_node)
        return -1;

    /* Skip CCPI link init in Asim */
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        bdk_config_set_int(0, BDK_CONFIG_MULTI_NODE);
        return -1;
    }

    BDK_CSR_INIT(mio_fus_dat2, bdk_numa_master(), BDK_MIO_FUS_DAT2);
    if (mio_fus_dat2.s.ocx_dis)
    {
        bdk_config_set_int(0, BDK_CONFIG_MULTI_NODE);
        return -1;
    }

    BDK_TRACE(INIT, "Initializing CCPI links\n");
    int status = __bdk_init_ccpi_links(0);
    bdk_watchdog_poke();

    if (status)
    {
        bdk_config_set_int(0, BDK_CONFIG_MULTI_NODE);
        if (1 == multi_node) /* fail case for 'on' setting */
        {
            printf("CCPI: Link timeout\n");
            /* Reset on failure if we're using the watchdog */
            if (bdk_watchdog_is_running())
            {
                bdk_boot_status(BDK_BOOT_STATUS_REQUEST_POWER_CYCLE);
                return -1;
            }
            else
            {
                bdk_warn("\n");
                bdk_warn("********************************************************\n");
                bdk_warn("* CCPI initialization failed with two nodes required.\n");
                bdk_warn("* Boot suspended. A full power cycle is recommended.\n");
                bdk_warn("********************************************************\n");
                bdk_warn("\n");
                bdk_fatal("CCPI failed required initialization\n");
            }
        }
        else /* fail case for 'auto' setting */
        {
            BDK_TRACE(INIT, "Auto configured 1 node.\n");
            return 0;
        }
    }
    else
    {
        if (2 == multi_node) /* success case for 'auto' setting */
            BDK_TRACE(INIT, "Auto configured 2 nodes.\n");
        return 0;
    }
}

/**
 * Bringup the other nodes
 */
static void bdk_boot_ccpi_nodes(void)
{
    int multi_node = bdk_config_get_int(BDK_CONFIG_MULTI_NODE);
    if (!multi_node)
        return;

    BDK_TRACE(INIT, "Initializing CCPI\n");
    __bdk_init_ccpi_multinode();
    /* Reset if CCPI failed */
    if (bdk_numa_is_only_one() && bdk_watchdog_is_running())
        bdk_boot_status(BDK_BOOT_STATUS_REQUEST_POWER_CYCLE);

    bdk_watchdog_poke();
}

/**
 * Initialize the CCPI links and bringup the other nodes
 */
void bdk_boot_ccpi(void)
{
    /* Only CN88XX supports CCPI */
    if (!CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return;
    /* Emulator doesn't support CCPI */
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return;
    if (bdk_boot_ccpi_link() == 0)
        bdk_boot_ccpi_nodes();
}
