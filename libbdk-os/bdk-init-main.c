/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include "libbdk-arch/bdk-csrs-ap.h"
#include "libbdk-arch/bdk-csrs-ccs.h"
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
void __bdk_init_sysreg(void)
{
    /* The defaults for write buffer timeouts are poor */
    bdk_ap_cvmmemctl0_el1_t cvmmemctl0_el1;
    BDK_MRS(s3_0_c11_c0_4, cvmmemctl0_el1.u);
    cvmmemctl0_el1.s.wbftonshena = 1; /* NSH has 2^18 timeout. All BDK mem is NSH */
    cvmmemctl0_el1.s.wbftomrgclrena = 1; /* Reset timer on merge. Hardware default is brain dead */
    BDK_MSR(s3_0_c11_c0_4, cvmmemctl0_el1.u);

    /* Enable LMTST and IOATOMIC on CN83XX */
    if (bdk_is_model(OCTEONTX_CN83XX) || bdk_is_model(OCTEONTX_CN9XXX))
    {
        bdk_ap_cvmmemctl1_el1_t cvmmemctl1_el1;
        BDK_MRS(s3_0_c11_c0_5, cvmmemctl1_el1.u);
        cvmmemctl1_el1.s.lmtstena = 1;
        cvmmemctl1_el1.s.ioatomicena = 1; // pko _OP_OPEN/CLOSE/QUERY needs that
        cvmmemctl1_el1.s.switchtagena = 1; /* Enable switch cache per core */
        if (bdk_is_model(OCTEONTX_CN83XX_PASS1_0))
        {
            /* (AP-30350)   2018-09-11  SSO Switch Tag Cache predictor
              can corrupt loads */
            cvmmemctl1_el1.s.switchtagena = 0;
        }
        BDK_MSR(s3_0_c11_c0_5, cvmmemctl1_el1.u);
    }

    /* Errata AP-36579: MSR->MRS/ERET hazard violated with certain code layouts */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0) || bdk_is_model(OCTEONTX_CNF95XX_PASS1_X))
    {
        bdk_ap_cvmctl2_el1_t cvmctl2_el1;
        BDK_MRS(s3_0_c11_c0_1, cvmctl2_el1.u);
        cvmctl2_el1.s.reduce_map_bandwidth = 3;
        BDK_MSR(s3_0_c11_c0_1, cvmctl2_el1.u);
    }

    /* Errata AP-36933: Corruption of SSO/NPA/PSM STP transactions */
    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        bdk_ap_cvmctl_el1_t cvmctl_el1;
        BDK_MRS(s3_0_c11_c0_0, cvmctl_el1.u);
        cvmctl_el1.s.disable_ldp_stp_fiss = 1;
        BDK_MSR(s3_0_c11_c0_0, cvmctl_el1.u);
    }

    /* OOO fetures and prefetching can only be enabled if DRAM is enabled */
    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        int is_dram = (0 != BDK_CSR_READ(bdk_numa_local(), BDK_CCS_ASC_REGIONX_END(0)));
        bdk_ap_cvmctl_el1_t ap_cvmctl_el1;
        BDK_MRS(s3_0_c11_c0_0, ap_cvmctl_el1.u);
        ap_cvmctl_el1.cn9.ldil1swprefdis = !is_dram; /* Enable LDI L1 software prefetch instructions (PRFM) */
        ap_cvmctl_el1.cn9.ldil1specdis = !is_dram; /* Enable all LDI L1 speculative fill requests */
        ap_cvmctl_el1.cn9.ldil1hwprefdis = !is_dram; /* Enable Istream LDI L1 hardware prefetcher */
        ap_cvmctl_el1.cn9.disable_ooo = !is_dram; /* Allow OOO instructions */
        ap_cvmctl_el1.cn9.disable_mem_ooo = !is_dram; /* Allow OOO memory */
        ap_cvmctl_el1.cn9.force_strong_ordering = !is_dram; /* Don't force strong ordering */

        /* Enable the prefetcher */
        if (bdk_is_model(OCTEONTX_CN96XX_PASS1_0))
        {
            /* FIXME: CN96XX:A0 prefetcher */
        }
        else
        {
            ap_cvmctl_el1.cnf95xxp1.dpref_delta = is_dram; /* Enable delta stream hardware data prefetcher */
            ap_cvmctl_el1.cnf95xxp1.dpref_next_line = is_dram; /* Enable next line hardware data prefetcher */
            ap_cvmctl_el1.cnf95xxp1.dpref_lookahead = is_dram; /* When set, hardware data prefetcher uses a lookahead of 2. When clear, lookahead of 1 */
            ap_cvmctl_el1.cnf95xxp1.dpref_bp_dis = is_dram; /* When set, hardware data prefetcher ignores memory system backpressure for next line prefetcher */
        }

        BDK_MSR(s3_0_c11_c0_0, ap_cvmctl_el1.u);
    }

    /* v8.5 store barrier was added to 96A1 and future chips. 96A0 does not
       have this feature. Disable v8.5 for better performance */
    if (bdk_is_model(OCTEONTX_CN9XXX) && !bdk_is_model(OCTEONTX_CN96XX_PASS1_0))
    {
        bdk_ap_cvmctl_el1_t cvmctl_el1;
        BDK_MRS(s3_0_c11_c0_0, cvmctl_el1.u);
        cvmctl_el1.s.disable_store_barrier_func = 1;
        BDK_MSR(s3_0_c11_c0_0, cvmctl_el1.u);
    }

    /* Trap all non-zero node accesses on chips that don't support
       multi-node. This should be set by default, but it doesn't hurt
       to set it again */
    bdk_ap_cvmmemctl1_el1_t cvmmemctl1_el1;
    BDK_MRS(s3_0_c11_c0_5, cvmmemctl1_el1.u);
    cvmmemctl1_el1.s.node1trapena = 1;
    BDK_MSR(s3_0_c11_c0_5, cvmmemctl1_el1.u);

    uint64_t ap_cvmctl_el1;
    uint64_t ap_cvmctl2_el1;
    uint64_t ap_cvmmemctl0_el1;
    uint64_t ap_cvmmemctl1_el1;
    uint64_t ap_cvmmemctl2_el1;
    uint64_t ap_cvmmemctl3_el1;

    BDK_MRS(s3_0_c11_c0_0, ap_cvmctl_el1);
    BDK_MRS(s3_0_c11_c0_4, ap_cvmmemctl0_el1);
    BDK_MRS(s3_0_c11_c0_5, ap_cvmmemctl1_el1);
    BDK_TRACE(INIT, "Core%d: AP_CVMCTL_EL1 = 0x%lx\n", bdk_get_core_num(), ap_cvmctl_el1);
    BDK_TRACE(INIT, "Core%d: AP_CVMMEMCTL0_EL1 = 0x%lx\n", bdk_get_core_num(), ap_cvmmemctl0_el1);
    BDK_TRACE(INIT, "Core%d: AP_CVMMEMCTL1_EL1 = 0x%lx\n", bdk_get_core_num(), ap_cvmmemctl1_el1);
    if (!bdk_is_model(OCTEONTX_CN8XXX))
    {
        BDK_MRS(s3_0_c11_c0_1, ap_cvmctl2_el1);
        BDK_MRS(s3_0_c11_c0_6, ap_cvmmemctl2_el1);
        BDK_MRS(s3_0_c11_c0_7, ap_cvmmemctl3_el1);
        BDK_TRACE(INIT, "Core%d: AP_CVMCTL2_EL1 = 0x%lx\n", bdk_get_core_num(), ap_cvmctl2_el1);
        BDK_TRACE(INIT, "Core%d: AP_CVMMEMCTL2_EL1 = 0x%lx\n", bdk_get_core_num(), ap_cvmmemctl2_el1);
        BDK_TRACE(INIT, "Core%d: AP_CVMMEMCTL3_EL1 = 0x%lx\n", bdk_get_core_num(), ap_cvmmemctl3_el1);
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
        if (bdk_is_model(OCTEONTX_CN8XXX))
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

    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        BDK_TRACE(INIT, "N%d: Initialize VRM\n", node);
        bdk_vrm_initialize(node);
    }

    BDK_TRACE(INIT, "N%d: Initialize IOBN\n", node);
    if (bdk_is_model(OCTEONTX_CN81XX))
    {
        BDK_CSR_MODIFY(c, node, BDK_IOBNX_NCB0_HP(0),
            c.s.hp = 1);
    }

    /* Errata (IOB-36522) IOBN()_ARBID()_CTL resets incorrectly */
    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        int max_iob = bdk_is_model(OCTEONTX_CN96XX_PASS1_X) ? 2 : 1;
        for (int iob = 0; iob < max_iob; iob++)
        {
            for (int arb = 0; arb < 16; arb++)
                BDK_CSR_WRITE(node, BDK_IOBNX_ARBIDX_CTL(iob, arb),
                    BDK_CSR_READ(node, BDK_IOBNX_ARBIDX_CTL(iob, arb)));
        }
    }

    if (bdk_is_model(OCTEONTX_CN81XX) || bdk_is_model(OCTEONTX_CN83XX))
    {
        BDK_TRACE(INIT, "N%d: Initialize LBK clocking\n", node);
        int num_lbk = bdk_is_model(OCTEONTX_CN83XX) ? 4 : 1;
        for (int lbk = 0; lbk < num_lbk; lbk++)
            BDK_CSR_MODIFY(c, node, BDK_LBKX_CLK_GATE_CTL(lbk),
                c.s.dis = 0);
    }

    if (BDK_IS_REQUIRED(QLM))
    {
        BDK_TRACE(INIT, "N%d: Performing global QLM initialization\n", node);
        bdk_qlm_init(node);
    }
    if (BDK_IS_REQUIRED(ECAM))
    {
        BDK_TRACE(INIT, "N%d: Performing global ECAM initialization\n", node);
        bdk_ecam_scan_all(node);
    }

    if (bdk_is_model(OCTEONTX_CN83XX_PASS1_X))
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
            if (bdk_is_model(OCTEONTX_CN8XXX))
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

