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
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-ocx.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"

BDK_REQUIRE_DEFINE(DRIVER_CCPI);

static int probe(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.CCPI%d", device->node, device->instance);
    return 0;
}

/**
 * CCPI init() function
 *
 * @param device CCPI to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    /* Nothing to do here */
    return 0;
}

static int ccpi_dram_test(bdk_node_t node_id)
{
    bdk_dram_test_flags_t flags = BDK_DRAM_TEST_NO_STOP_ERROR |
        BDK_DRAM_TEST_NO_PROGRESS | BDK_DRAM_TEST_NO_STATS |
        BDK_DRAM_TEST_NO_BANNERS;
    flags |= 1 << node_id;
    if (node_id != bdk_numa_master())
        flags |= BDK_DRAM_TEST_USE_CCPI;

    int test = 0;
    int errors = 0;
    while (bdk_dram_get_test_name(test))
    {
        errors += bdk_dram_test(test, 64 << 20, 64 << 20, flags);
        test++;
    }
    return errors;
}

int bdk_ccpi_test_loopback(void)
{
    const bdk_node_t node_master = bdk_numa_master();
    const bdk_node_t node_loop = node_master ^ 1;
    const bdk_node_t node_invalid = 3;
    int result_code = 0;

    /* Make sure DRAM is setup */
    if (!__bdk_is_dram_enabled(node_master))
    {
        bdk_error("CCPI Loopback: Memory must be setup before this test\n");
        return -1;
    }
    uint64_t mbytes = bdk_dram_get_size_mbytes(node_master);
    if (mbytes < 128)
    {
        bdk_error("CCPI Loopback: Expected at least 128MB of memory (%luMB)\n", mbytes);
        return -1;
    }

    /* Make sure CCPI is not setup */
    BDK_CSR_INIT(l2c_oci_ctl, node_master, BDK_L2C_OCI_CTL);
    if (l2c_oci_ctl.s.enaoci)
    {
        bdk_error("CCPI Loopback: CCPI is already running\n");
        return -1;
    }

    /* Bringup all cores for DRAM testing */
    bdk_init_cores(node_master, 0);

    /* Only use one link for communications */
    BDK_CSR_MODIFY(c, node_master, BDK_OCX_COM_DUAL_SORT,
        c.s.sort = 0);

    /* Disable all links */
    for (int link = 0; link < 3; link++)
    {
        BDK_CSR_MODIFY(c, node_master, BDK_OCX_COM_LINKX_CTL(link),
            c.s.loopback = 0;
            c.s.reinit = 0;
            c.s.auto_clr = 0;
            c.s.drop = 1;
            c.s.id = node_invalid);
        BDK_CSR_MODIFY(c, node_master, BDK_OCX_LNKX_CFG(link),
            c.s.qlm_select = 0);
    }

    /* Perform a memory test on the DRAM range we are going to use */
    uint64_t errors = ccpi_dram_test(node_master);
    if (errors)
    {
        printf("Local access: FAIL\n");
        result_code = -1;
    }
    else
        printf("Local access: PASS\n");

    /* Flush L2 */
    bdk_l2c_flush(node_master);

    /* Enable CCPI transactions */
    BDK_CSR_MODIFY(c, node_master, BDK_L2C_OCI_CTL,
        c.s.enaoci = (1 << node_master) | (1 << node_loop));

    /* For each CCPI link */
    for (int link = 0; link < 3; link++)
    {
        /* Setup CCPI loopback on this link */
        BDK_CSR_MODIFY(c, node_master, BDK_OCX_COM_LINKX_CTL(link),
            c.s.loopback = 1;
            c.s.reinit = 0;
            c.s.auto_clr = 0;
            c.s.drop = 0;
            c.s.id = node_loop);
        bdk_wait_usec(500000);
        /* Disable loopback on previous link */
        if (link)
        {
            BDK_CSR_MODIFY(c, node_master, BDK_OCX_COM_LINKX_CTL(link-1),
                c.s.loopback = 0;
                c.s.reinit = 0;
                c.s.auto_clr = 0;
                c.s.drop = 1;
                c.s.id = node_invalid);
        }
        /* Perform a DRAM test on this link */
        errors = ccpi_dram_test(node_loop);
        /* Flush L2 */
        bdk_l2c_flush(node_master);
        bdk_wait_usec(500000);
        /* Report status */
        if (errors)
        {
            printf("Loop Link %d: FAIL\n", link);
            result_code = -1;
        }
        else
            printf("Loop Link %d: PASS\n", link);
    }

    /* Setup CCPI loopback on links 0 and 2. This represents the production
       CCPI setup where two links are used. Link 2 is still setup from above  */
    BDK_CSR_MODIFY(c, node_master, BDK_OCX_COM_LINKX_CTL(0),
        c.s.loopback = 1;
        c.s.reinit = 0;
        c.s.auto_clr = 1;
        c.s.drop = 0;
        c.s.id = node_loop);
    BDK_CSR_MODIFY(c, node_master, BDK_OCX_COM_DUAL_SORT,
        c.s.sort = 2);
    bdk_wait_usec(500000);
    /* Perform a DRAM test on these link */
    errors = ccpi_dram_test(node_loop);
    /* Flush L2 twice so we know the first one is finished before we disable
       the links */
    bdk_l2c_flush(node_master);
    bdk_l2c_flush(node_master);
    bdk_wait_usec(500000);
    /* Disable loopback on these link */
    BDK_CSR_MODIFY(c, node_master, BDK_OCX_COM_LINKX_CTL(0),
        c.s.loopback = 0;
        c.s.reinit = 0;
        c.s.auto_clr = 0;
        c.s.drop = 1;
        c.s.id = node_invalid);
    BDK_CSR_MODIFY(c, node_master, BDK_OCX_COM_LINKX_CTL(2),
        c.s.loopback = 0;
        c.s.reinit = 0;
        c.s.auto_clr = 0;
        c.s.drop = 1;
        c.s.id = node_invalid);
    BDK_CSR_MODIFY(c, node_master, BDK_OCX_COM_DUAL_SORT,
        c.s.sort = 0);
    /* Report status */
    if (errors)
    {
        printf("Loop Dual Link: FAIL\n");
        result_code = -1;
    }
    else
        printf("Loop Dual Link: PASS\n");

    /* Disable CCPI transactions */
    BDK_CSR_MODIFY(c, node_master, BDK_L2C_OCI_CTL,
        c.s.enaoci = 0);

    return result_code;
}

bdk_driver_t __bdk_driver_ccpi = {
    .id = (BDK_PCC_PROD_E_GEN << 24) | BDK_PCC_VENDOR_E_CAVIUM | (BDK_PCC_DEV_IDL_E_OCX << 16),
    .probe = probe,
    .init = init,
};
