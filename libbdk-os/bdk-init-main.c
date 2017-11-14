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
#include <stdio.h>
#include "libbdk-arch/bdk-csrs-ap.h"
#include "libbdk-arch/bdk-csrs-dap.h"
#include "libbdk-arch/bdk-csrs-iobn.h"
#include "libbdk-arch/bdk-csrs-lbk.h"
#include "libbdk-arch/bdk-csrs-ccs.h"
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-gic.h"

#ifndef MFG_SYSTEM_LEVEL_TEST
#define MFG_SYSTEM_LEVEL_TEST 0
#endif



/**
 * Do per core initialization of system registers
 */
static void __bdk_init_sysreg(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
    {
        bdk_ap_cvmctl_el1_t cvmctl_el1;
        BDK_MRS(s3_0_c11_c0_0, cvmctl_el1.u);

        /* Errara (AP-22934) CIM module has incorrect conditional clock */
        if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_0))
            cvmctl_el1.s.force_issue_clock = 1;

        /* Errata (AP-22500) GlobalSync request during a multi-cycle ATOMIC
           stalls forever */
        /* Disable compare and swap on CN88XX pass 1.x */
        cvmctl_el1.s.disable_casp = 1;
        cvmctl_el1.s.disable_cas = 1;

        /* (AP-26147) Event register may not be set */
        cvmctl_el1.s.disable_wfe = 1;

        BDK_MSR(s3_0_c11_c0_0, cvmctl_el1.u);
    }

    /* Bug #27499 - ISB not flushing the pipeline after a TLBI */
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
    {
        bdk_ap_cvmctl_el1_t cvmctl_el1;
        BDK_MRS(s3_0_c11_c0_0, cvmctl_el1.u);
        cvmctl_el1.s.isb_flush = 1;
        BDK_MSR(s3_0_c11_c0_0, cvmctl_el1.u);
    }

    /* The defaults for write buffer timeouts are poor */
    bdk_ap_cvmmemctl0_el1_t cvmmemctl0_el1;
    BDK_MRS(s3_0_c11_c0_4, cvmmemctl0_el1.u);
    cvmmemctl0_el1.s.wbftonshena = 1; /* NSH has 2^18 timeout. All BDK mem is NSH */
    cvmmemctl0_el1.s.wbftomrgclrena = 1; /* Reset timer on merge. Hardware default is brain dead */
    /* Errata (AP-27388) Flavors of DMB not stalling on subsequent LD */
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X))
        cvmmemctl0_el1.s.dmbstallforce = 1;
    BDK_MSR(s3_0_c11_c0_4, cvmmemctl0_el1.u);

    /* Enable LMTST and IOATOMIC on CN83XX */
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) || CAVIUM_IS_MODEL(CAVIUM_CN93XX))
    {
        bdk_ap_cvmmemctl1_el1_t cvmmemctl1_el1;
        BDK_MRS(s3_0_c11_c0_5, cvmmemctl1_el1.u);
        cvmmemctl1_el1.s.lmtstena = 1;
        cvmmemctl1_el1.s.ioatomicena = 1; // pko _OP_OPEN/CLOSE/QUERY needs that
        BDK_MSR(s3_0_c11_c0_5, cvmmemctl1_el1.u);
    }
}

/**
 * Run on each node as a thread to perform error reporting
 *
 * @param arg
 * @param arg1
 */
static void __bdk_error_poll(int arg, void *arg1)
{
    while (bdk_error_check)
    {
        bdk_vrm_poll(bdk_numa_local());
        bdk_error_check(bdk_numa_local());
        bdk_wait_usec(100000);
    }
}

/**
 * Perform one time initialization for a node. Called for each
 * node from the master node.
 */
void __bdk_init_node(bdk_node_t node)
{
    /* Enable the timer. Do this first as many things depend on the clock */
    bdk_clock_setup(node);

    BDK_TRACE(INIT, "N%d: Performing node initialization\n", node);

    /* Allow CAP access from cores so we can read system registers through
       memory mapped addresses. See bdk_sysreg_read() */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
        BDK_CSR_MODIFY(c, node, BDK_DAP_IMP_DAR, c.s.caben = 1);

    /* Shut off cores in reset to save power. It is optional, but probably
        good practice */
    BDK_TRACE(INIT, "N%d: Enable power gating on cores\n", node);
    if ((!MFG_SYSTEM_LEVEL_TEST) && (!bdk_is_platform(BDK_PLATFORM_EMULATOR)))
    {
        uint64_t in_reset = BDK_CSR_READ(node, BDK_RST_PP_RESET);
        BDK_CSR_WRITE(node, BDK_RST_PP_POWER, in_reset);
    }

    BDK_TRACE(INIT, "N%d: Initialize L2\n", node);
    bdk_l2c_initialize(node);

    BDK_TRACE(INIT, "N%d: Initialize VRM\n", node);
    bdk_vrm_initialize(node);

    BDK_TRACE(INIT, "N%d: Initialize IOBN\n", node);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) || CAVIUM_IS_MODEL(CAVIUM_CN81XX))
    {
        BDK_CSR_MODIFY(c, node, BDK_IOBNX_NCB0_HP(0),
            c.s.hp = 1);
        if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
            BDK_CSR_MODIFY(c, node, BDK_IOBNX_NCB0_HP(1),
                c.s.hp = 0);
    }

    BDK_TRACE(INIT, "N%d: Initialize LBK clocking\n", node);
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) || CAVIUM_IS_MODEL(CAVIUM_CN83XX))
    {
        int num_lbk = CAVIUM_IS_MODEL(CAVIUM_CN83XX) ? 4 : 1;
        for (int lbk = 0; lbk < num_lbk; lbk++)
            BDK_CSR_MODIFY(c, node, BDK_LBKX_CLK_GATE_CTL(lbk),
                c.s.dis = 0);
    }

    if (BDK_IS_REQUIRED(ECAM))
    {
        BDK_TRACE(INIT, "N%d: Performing global ECAM initialization\n", node);
        bdk_ecam_scan_all(node);
    }
    if (BDK_IS_REQUIRED(QLM))
    {
        BDK_TRACE(INIT, "N%d: Performing global QLM initialization\n", node);
        bdk_qlm_init(node);
    }
    if (BDK_IS_REQUIRED(TWSI))
    {
        BDK_TRACE(INIT, "N%d: Initialize TWSI\n", node);
        bdk_twsix_initialize(node);
    }

    if (BDK_IS_REQUIRED(TNS))
    {
        BDK_TRACE(INIT, "N%d: Initialize TNS\n", node);
        bdk_tns_initialize(node);
    }

    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX_PASS1_X))
    {
        /* Errata (GIC-28835)  2016-10-18  CIM load balancers need tuning */
        BDK_TRACE(INIT, "N%d: Initialize GIC-28835\n", node);
        BDK_CSR_MODIFY(c, node, BDK_GIC_CFG_CTLR,
            c.s.dis_cpu_if_load_balancer = 1);
    }

    if (BDK_IS_REQUIRED(ERROR_DECODE) && !bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        BDK_TRACE(INIT, "N%d: Enabling error reporting\n", node);
        bdk_error_enable(node);
        if (bdk_error_check)
        {
            if (node != bdk_numa_local())
                bdk_init_cores(node, 1);
            if (bdk_thread_create(node, 0, __bdk_error_poll, 0, NULL, 0))
                bdk_fatal("Create of error poll thread failed\n");
        }
    }
}

/**
 * This function is the first function run on all cores once the
 * threading system takes over.
 *
 * @param arg
 * @param arg1
 */
void __bdk_init_main(int argc, void *argv)
{
    const bdk_node_t node = bdk_numa_local();
    /* All cores start running threads here. Only the setup required to get
        threading up is done. More init is needed. This code will be locked to
        a single core with threads being spawned for each core */

    /* Unlock the global stack now that we aren't using it anymore */
    extern volatile uint64_t __bdk_initial_stack_start;
    BDK_WMB;
    __bdk_initial_stack_start = 0;
    BDK_WMB;

    /* Init any system registers that need to be done on every core */
    BDK_TRACE(INIT, "N%d: Initialize system registers on Core %d\n", node, bdk_get_core_num());
    __bdk_init_sysreg();

    /* Perform one time init that must be done on the master node. This
       will not be run on the other nodes */
    if (bdk_is_boot_core())
    {
        if (BDK_IS_REQUIRED(DRIVER))
        {
            BDK_TRACE(INIT, "N%d: Registering drivers\n", node);
            __bdk_driver_register_all();
        }

        BDK_TRACE(INIT, "N%d: Performing common initialization\n", node);

        /* Load all file systems */
        __bdk_fs_init_late();
        /* Some config setting are dynamically updated */
        __bdk_config_init();

        if (!bdk_is_platform(BDK_PLATFORM_EMULATOR))
        {
            BDK_TRACE(INIT, "N%d: Checking if CCPI is already up and has other nodes\n", node);
            int enaoci;
            if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
            {
                BDK_CSR_INIT(l2c_oci_ctl, node, BDK_L2C_OCI_CTL);
                enaoci = l2c_oci_ctl.s.enaoci;
            }
            else
            {
                BDK_CSR_INIT(ccs_ccpi_ctl, node, BDK_CCS_CCPI_CTL);
                enaoci = ccs_ccpi_ctl.s.enaoci;
            }
            for (bdk_node_t n = 0; n < BDK_NUMA_MAX_NODES; n++)
            {
                if (enaoci & (1 << n))
                {
                    BDK_TRACE(INIT, "N%d:     Found node %d\n", node, n);
                    bdk_numa_set_exists(n);
                }
            }
        }

        for (bdk_node_t n = 0; n < BDK_NUMA_MAX_NODES; n++)
        {
            if (bdk_numa_exists(n))
                __bdk_init_node(n);
        }

        /* Core 0 start main as another thread. We create a new thread so that
            the coremask will allow all cores in case the application
            goes multicore later */
        extern int main(int argc, const char **argv);
        BDK_TRACE(INIT, "Switching to main\n");
        if (bdk_thread_create(node, 0, (bdk_thread_func_t)main, argc, argv, BDK_THREAD_MAIN_STACK_SIZE))
            bdk_fatal("Create of main thread failed\n");

        /* The following code doesn't do anything useful. It forces a link
            dependency on bdk_require_depends(), which forces link dependency
            on needed components using BDK_REQUIRE() */
        __bdk_require_depends();
    }
}

