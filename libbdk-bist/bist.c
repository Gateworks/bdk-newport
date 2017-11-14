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
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <bdk.h>

#include "efuse-read.h"
#include "libbdk-arch/bdk-csrs-ap.h"
#include "libbdk-arch/bdk-csrs-bgx.h"
#include "libbdk-arch/bdk-csrs-dfa.h"
#include "libbdk-arch/bdk-csrs-gic.h"
#include "libbdk-arch/bdk-csrs-gti.h"
#include "libbdk-arch/bdk-csrs-iobn.h"
#include "libbdk-arch/bdk-csrs-key.h"
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-l2c_cbc.h"
#include "libbdk-arch/bdk-csrs-l2c_tad.h"
#include "libbdk-arch/bdk-csrs-mio_boot.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-nic.h"
#include "libbdk-arch/bdk-csrs-ocla.h"
#include "libbdk-arch/bdk-csrs-ocx.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-rad.h"
#include "libbdk-arch/bdk-csrs-rnm.h"
#include "libbdk-arch/bdk-csrs-sli.h"
#include "libbdk-arch/bdk-csrs-smmu.h"
#include "libbdk-arch/bdk-csrs-tns.h"
#include "libbdk-arch/bdk-csrs-zip.h"

// DEFINE to track things to fix
#define T88XX_HACK  1

/* Set VERBOSE to 0 for more human readable summary.  VERBOSE
 * should be 1 for script use.
 */
#define VERBOSE 1

static int bist_failures = 0;
static int bist_warnings = 0;
static int done = 0;
static int check_bist_reg(const char *reg_name, uint64_t bist_val, uint64_t expected, uint64_t mask, int verbose)
{
    uint64_t masked_val;
    int failed = 0;

    /* Log complete value for reference.... */
    if (verbose)
        printf("REG %-25s: 0x%016llx\n", reg_name, (unsigned long long)bist_val);
    masked_val = (bist_val & mask) ^ expected;
    if (masked_val)
    {
        bist_failures++;
        failed = 1;
        //BDK_SYNCW;
        printf("BIST FAILURE: %s, error bits ((register & mask) ^ expected): 0x%016llx\n", reg_name, (unsigned long long)masked_val);
    }
    return failed;
}
#define BIST_CHECK_REG(name, exp, mask) \
    do {\
        check_bist_reg(#name, BDK_CSR_READ(node, BDK_##name), exp, mask, VERBOSE);\
    } while (0)

#define BIST_CHECK_REG0(name) \
    do {\
        check_bist_reg(#name, BDK_CSR_READ(node, BDK_##name), 0, ~0ULL, VERBOSE);\
    } while (0)


static void bist_t88xx_core(int verbose, void *unused1)
{
    int failures = 0;
    int core = bdk_get_core_num();
    if (verbose)
        printf("Starting core BIST on core %d\n", bdk_get_core_num());

    bdk_ap_cvm_bist0_el1_t bist0;
    BDK_MRS(s3_0_c11_c1_0, bist0.u);
    failures += check_bist_reg("BIST0_EL1", bist0.u, 0, ~(3ULL << 32), verbose);

    bdk_ap_cvm_bist1_el1_t bist1;
    BDK_MRS(s3_0_c11_c1_1, bist1.u);
    failures += check_bist_reg("BIST1_EL1", bist1.u, 0xffffffffffff, 0xffffffffffff, verbose);

    bdk_ap_cvm_bist2_el1_t bist2;
    BDK_MRS(s3_0_c11_c1_4, bist2.u);
    failures += check_bist_reg("BIST2_EL1", bist2.u, 0, ~0ULL, verbose);

    bdk_ap_cvm_bist3_el1_t bist3;
    BDK_MRS(s3_0_c11_c1_5, bist3.u);
    failures += check_bist_reg("BIST3_EL1", bist3.u, 0xffffffffffff, 0xffffffffffff, verbose);

    if (failures)
        printf("core %d BIST FAILED\n", core);
    else if (VERBOSE)
        printf("core %d BIST PASSED\n", core);

    fflush(NULL);
    done = 1;
    //BDK_SYNCW;
}

static void dfa_bist(bdk_node_t node)
{
    printf("Checking non-cleared DFA_BIST\n");
    {
        BDK_CSR_INIT(dfa_config, node, BDK_DFA_CONFIG);
        dfa_config.s.dlcclear_bist = 0;
        dfa_config.s.dlcstart_bist = 0;
        BDK_CSR_WRITE(node, BDK_DFA_CONFIG, dfa_config.u);
    }
    {
        BDK_CSR_INIT(dfa_config, node, BDK_DFA_CONFIG);
        dfa_config.s.dlcstart_bist = 1;
        BDK_CSR_WRITE(node, BDK_DFA_CONFIG, dfa_config.u);
    }
    bdk_wait_usec(10000); //10ms
    BIST_CHECK_REG0(DFA_BIST0);
    BIST_CHECK_REG0(DFA_BIST1);

    printf("Checking clear DFA_BIST\n");
    {
        BDK_CSR_INIT(dfa_config, node, BDK_DFA_CONFIG);
        dfa_config.s.dlcclear_bist = 1;
        dfa_config.s.dlcstart_bist = 0;
        BDK_CSR_WRITE(node, BDK_DFA_CONFIG, dfa_config.u);
    }
    {
        BDK_CSR_INIT(dfa_config, node, BDK_DFA_CONFIG);
        dfa_config.s.dlcstart_bist = 1;
        BDK_CSR_WRITE(node, BDK_DFA_CONFIG, dfa_config.u);
    }
    bdk_wait_usec(10000); //10ms
    BIST_CHECK_REG0(DFA_BIST0);
    BIST_CHECK_REG0(DFA_BIST1);
}

static void bist_t88xx_global(void)
{
    bdk_node_t node = bdk_numa_local();

    BDK_CSR_INIT(fus_dat3, node, BDK_MIO_FUS_DAT3);
    printf("Starting global BIST\n");

    //L2C BIST
    BIST_CHECK_REG0(BGXX_CMR_BIST_STATUS(0));
    BIST_CHECK_REG0(BGXX_CMR_BIST_STATUS(1));

    BIST_CHECK_REG0(BGXX_SPU_BIST_STATUS(0));
    BIST_CHECK_REG0(BGXX_SPU_BIST_STATUS(1));

    dfa_bist(node);

    BIST_CHECK_REG0(GIC_BIST_STATUSR);
    BIST_CHECK_REG0(GTI_ERR_BIST_STATUS);

    for(int cnt=0;cnt<2;cnt++)
        BIST_CHECK_REG0(IOBNX_BISTR_REG(cnt));

    for(int cnt=0;cnt<2;cnt++)
        BIST_CHECK_REG0(IOBNX_BISTS_REG(cnt));

    BIST_CHECK_REG0(KEY_BIST_REG);

    for(int cnt=0;cnt<4;cnt++)
        BIST_CHECK_REG0(L2C_CBCX_BIST_STATUS(cnt));

    for(int cnt=0;cnt<4;cnt++)
        BIST_CHECK_REG0(L2C_MCIX_BIST_STATUS(cnt));


    for(int cnt=0;cnt<8;cnt++)
        BIST_CHECK_REG0(L2C_TADX_TBF_BIST_STATUS(cnt));

    for(int cnt=0;cnt<8;cnt++)
        BIST_CHECK_REG0(L2C_TADX_TDT_BIST_STATUS(cnt));

    for(int cnt=0;cnt<8;cnt++)
        BIST_CHECK_REG0(L2C_TADX_TTG_BIST_STATUS(cnt));

    {
        BDK_CSR_DEFINE(lmcx_dll_ctl2, BDK_LMCX_DLL_CTL2(0));
        lmcx_dll_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL2(0));

        if (lmcx_dll_ctl2.s.intf_en)
        {
            BIST_CHECK_REG0(LMCX_BIST_CTL(0));
            BIST_CHECK_REG0(LMCX_BIST_CTL(1));
            lmcx_dll_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL2(2));
            if (lmcx_dll_ctl2.s.intf_en)
            {
                BIST_CHECK_REG0(LMCX_BIST_CTL(2));
                BIST_CHECK_REG0(LMCX_BIST_CTL(3));
            }
            else
            {
                printf("Warning: LMC 2/3 disabled, not checking\n");
                bist_warnings++;
            }
        }
        else
        {
            printf("Warning: LMC disabled, not checking\n");
            bist_warnings++;
        }
    }

    BIST_CHECK_REG0(MIO_BOOT_BIST_STAT);

    BIST_CHECK_REG0(NIC_PF_BIST0_STATUS);
    BIST_CHECK_REG0(NIC_PF_BIST1_STATUS);
    BIST_CHECK_REG0(NIC_PF_BIST2_STATUS);
    BIST_CHECK_REG0(NIC_PF_BIST3_STATUS);

    for(int cnt=0;cnt<5;cnt++)
        BIST_CHECK_REG0(OCLAX_BIST_RESULT(cnt));

    BIST_CHECK_REG0(OCX_COM_BIST_STATUS);

    for(int cnt=0;cnt<3;cnt++)
        BIST_CHECK_REG0(OCX_TLKX_BIST_STATUS(cnt));

    for(int cnt=0;cnt<5;cnt++)
        BIST_CHECK_REG0(PEMX_BIST_STATUS(cnt));

    BIST_CHECK_REG0(RAD_REG_BIST_RESULT);

    BIST_CHECK_REG0(RNM_BIST_STATUS);

    BIST_CHECK_REG(RST_BIST_TIMER, 0, 1ULL << 28);

    for(int cnt=0;cnt<2;cnt++)
        BIST_CHECK_REG0(SLIX_BIST_STATUS(cnt));
    
    if (!CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
    {
        // T88XX HACK: errata for SMMU BIST, so ignore...
        for(int cnt=0;cnt<4;cnt++)
            BIST_CHECK_REG0(SMMUX_BIST_STATUS(cnt));
    }

    if (fus_dat3.s.tns_cripple)
    {
        printf("INFO: TNS is disabled. Skipping TNS_BIST checks\n");
    }
    else
    {

        BIST_CHECK_REG0(TNS_BIST_STATUS);
        BIST_CHECK_REG0(TNS_BIST_STATUS1);
        BIST_CHECK_REG0(TNS_BIST_STATUS2);
        BIST_CHECK_REG0(TNS_BIST_STATUS3);
        BIST_CHECK_REG0(TNS_BIST_STATUS4);
        BIST_CHECK_REG0(TNS_BIST_STATUS5);
        BIST_CHECK_REG0(TNS_BIST_STATUS6);
        BIST_CHECK_REG0(TNS_BIST_STATUS7);
        BIST_CHECK_REG0(TNS_BIST_STATUS8);
        BIST_CHECK_REG0(TNS_BIST_STATUS9);
        BIST_CHECK_REG0(TNS_BIST_STATUS10);
        BIST_CHECK_REG0(TNS_BIST_STATUS11);
    }

    if (!fus_dat3.s.nozip) 
    {
        for(int cnt=0;cnt<2;cnt++)
            BIST_CHECK_REG0(ZIP_COREX_BIST_STATUS(cnt));
        BIST_CHECK_REG0(ZIP_CTL_BIST_STATUS);
    }
    else
    {
        printf("INFO: ZIP is disabled. Skipping ZIP_BIST checks\n");
    }



    BDK_CSR_INIT(rst_boot, node, BDK_RST_BOOT);
    if (rst_boot.s.lboot == 1)
    {
        int core;
        BDK_CSR_INIT(iob_even_core_bist, node, BDK_IOBNX_CORE_BIST_STATUS(0));
        BDK_CSR_INIT(iob_odd_core_bist, node, BDK_IOBNX_CORE_BIST_STATUS(1));

        if (iob_even_core_bist.u || iob_odd_core_bist.u)
        {
            printf("Cores failed BIST: ");
            for (core = 0; core < 48; core++)
            {
                if (core & 1)
                {
                    if (iob_odd_core_bist.u & (1ull << (core - 1)/2))
                        printf("%d, ", core);
                }
                else
                {
                    if (iob_even_core_bist.u & (1ull << core/2))
                        printf("%d, ", core);
                }
            }
            printf("\n");
        }
        else
            printf("All cores passed BIST (IOBNX_CORE_BIST_STATUS)\n");
    }
    else
    {
        bist_warnings++;
        printf("Warning: Skipping IOBNX_CORE_BIST_STATUS due to non-cold boot\n");
    }

    if (bist_failures) {
        printf("global BIST FAILED\n");
        printf("%d BIST failures reported\n", bist_failures);
    }
    else
        printf("global BIST PASSED\n");
    printf("global BIST complete, %d warnings\n", bist_warnings);
    fflush(NULL);
}

void bdk_bist_check()
{
    uint64_t coremask = 0;
    char global_bist = 1;
    const char *input;

    input = bdk_readline("Do you want to do BIST check (y/n)? ", NULL, 0);
    if ((*input) == 'n')
    {
        printf("Skipping BIST check altogether\n");
        return;
    }

    input = bdk_readline("BIST Coremask (in decimal, enter 0 for all available cores): ", NULL, 0);
    coremask = strtoull(input, NULL, 16);
    printf("User supplied coremask is %llx\n", (unsigned long long)coremask);

    input = bdk_readline("Global BIST(y/n): ", NULL, 0);
    if ((*input) == 'y')
    {
        global_bist = 1;
    }
    else
    {
        global_bist = 0;
    }

    bdk_node_t node = bdk_numa_local();
    printf("BDK version: %s\n", bdk_version_string());
    bdk_init_cores(node, coremask);
    coremask = bdk_get_running_coremask(node);
    int num_cores = bdk_get_num_cores(node);
    printf("Starting all(%d) cores. Coremask %llx\n", num_cores, (unsigned long long)coremask);


    BDK_CSR_INIT(mio_rst_boot, node, BDK_RST_BOOT);
    int rclk =  50 * mio_rst_boot.s.c_mul;
    int sclk = 50 * mio_rst_boot.s.pnr_mul;

    printf("CPU clock: %d MHz, IO clock: %d MHz\n", rclk, sclk);

    if (global_bist)
    {
        bist_t88xx_global();
    }
    else
    {
        printf("Skipping Global BIST check\n");
    }
    fflush(NULL);
    for (int core=0; core<num_cores; core++)
    {
        done = 0;
        int timeout_ms = 50;
        if (!((1ULL<<core) & coremask))
        {
            continue;
        }
        //BDK_SYNCW;
        if (bdk_thread_create(node, 1ull<<core, bist_t88xx_core, VERBOSE, NULL, 0))
        {
            bdk_error("Failed to create thread for core %d\n", core);
        }
        while (!done && timeout_ms-- > 0)
        {
            bdk_thread_yield();
            bdk_wait_usec(1000);
        }
        if (!done)
        {
            bdk_error("BIST FAILED to complete on core %d\n", core);
        }
    }

    if (global_bist)
        dump_fuses();
    else
        printf("Skipping fuse dump.\n");


    printf("BIST test Complete, %d warnings, %d errors\n", bist_warnings, bist_failures);
    fflush(NULL);
}

