/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <unistd.h>
#include "libbdk-arch/bdk-csrs-ccs.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-ap.h"
#include "../libdram/libdram.h"

BDK_REQUIRE_DEFINE(DRAM_CONFIG);

/**
 * Given a node and LMC, return a map to where it is located on the chip. Needed
 * for CN9XXX parts to determine which MCC to use.
 *
 * @param node   Node for LMC
 * @param lmc    LMC to lookup
 *
 * @return LMC and MCC information
 */
bdk_dram_lmc_map_t bdk_dram_get_lmc_map(bdk_node_t node, int lmc)
{
    bdk_dram_lmc_map_t result;
    result.node = node;
    result.lmc = lmc;
    if (bdk_is_model(OCTEONTX_CN96XX))
    {
        /* LMC0 connects to MCC 1 LMCOE 0 */
        /* LMC1 connects to MCC 0 LMCOE 0 */
        /* LMC2 connects to MCC 1 LMCOE 1 */
        result.mcc = (lmc == 1) ? 0 : 1;
        result.lmcoe = (lmc == 2) ? 1 : 0;
    }
    else if (bdk_is_model(OCTEONTX_CNF95XX) || bdk_is_model(OCTEONTX_LOKI))
    {
        /* LMC0 connects to MCC 0 LMCOE 0 */
        /* LMC2 connects to MCC 1 LMCOE 1 */
        result.mcc = 0;
        result.lmcoe = (lmc) ? 1 : 0;
    }
    else
        bdk_fatal("Update bdk_dram_get_lmc_map for this chip");
    return result;
}

/**
 * CALL directly from app "init" code
 *
 * Lookup a DRAM configuration by name and initialize DRAM using it
 *
 * @param node   Node to configure
 * @param ddr_clock_override
 *               If non zero, override the DRAM frequency specified
 *               in the config with this value
 *
 * @return Amount of DRAM in MB, or negative on failure
 */
static int __bdk_dram_config(int node, int ddr_clock_override)
{
    int mbytes = 0;
    const dram_config_t *config = libdram_config_load(node);
    if (!config)
    {
        if (bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            /* Asim can't config memory, so just lie about having 1GB
               per LMC */
            int num_lmc = __bdk_dram_get_num_lmc(node);
            for (int lmc = 0; lmc < num_lmc; lmc++)
            {
                if ((bdk_is_model(OCTEONTX_CNF95XX) || bdk_is_model(OCTEONTX_LOKI)) && (lmc == 1))
                {
                    /* CNF95XX and LOKI implement LMC0 and LMC2, skipping LMC1. Avoid
                       accessing LMC1 */
                    continue;
                }
                else if (bdk_is_model(OCTEONTX_CN8XXX))
                    BDK_CSR_MODIFY(c, node, BDK_LMCX_DDR_PLL_CTL(lmc),
                        c.cn83xx.reset_n = 1);
                else
                    BDK_CSR_MODIFY(c, node, BDK_LMCX_DDR_PLL_CTL(lmc),
                        c.cn9.pd = 0);
                printf("N%d.LMC%d.DIMM0: 1024 MB, DDR4 UDIMM 2Rx8 ECC, p/n: ASIM, s/n: ASIM, 1.2V\n", node, lmc);
                printf("N%d.LMC%d Configuration Completed: 1024 MB\n", node, lmc);
                mbytes += 1024;
            }
            if (bdk_is_model(OCTEONTX_CN9XXX))
            {
                BDK_CSR_MODIFY(asc_end, node, BDK_CCS_ASC_REGIONX_END(0),
                    asc_end.s.addr = ((mbytes << 20) - 1) >> 24);
            }
            return mbytes;
        }
        printf("N%d: No DRAM config specified, skipping DRAM init\n", node);
        return 0;
    }

    BDK_TRACE(DRAM, "N%d: Starting DRAM init (config=%p, ddr_clock_override=%d)\n", node, config, ddr_clock_override);
    mbytes = libdram_config(node, config, ddr_clock_override);
    BDK_TRACE(DRAM, "N%d: DRAM init returned %d\n", node, mbytes);

   if (mbytes <= 0)
    {
        printf("ERROR: DDR initialization failed\n");
        return -1;
    }

    return mbytes;
}

/**
 * CALL directly from LUA DDR Menu item
 *
 * Lookup a DRAM configuration by name and initialize DRAM using it
 *
 * @param node   Node to configure
 * @param ddr_clock_override
 *               If non zero, override the DRAM frequency specified
 *               in the config with this value
 *
 * @return Amount of DRAM in MB, or negative on failure
 */
int bdk_dram_config(bdk_node_t node, int ddr_clock_override)
{
    int mbytes;

    // call the basic code above to do DRAM config
    mbytes = __bdk_dram_config(node, ddr_clock_override);
    if (mbytes <= 0)
        return mbytes;

    /*  On 9xxx Re-enable OOO after DRAM is up and running  */
    if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        BDK_TRACE(INIT, "Enable OOO operation after DRAM init\n");
        extern void __bdk_init_sysreg(void);
        __bdk_init_sysreg();
    }

    /* Unlock L2 now that DRAM works */
    if (node == bdk_numa_master())
    {
        BDK_TRACE(INIT, "Unlocking and flushing L2/LLC\n");
        bdk_l2c_flush(node);
    }

    return mbytes;
}

/**
 * Do DRAM configuration tuning
 *
 * @param node   Node to tune
 *
 * @return Success or Fail
 */
int bdk_dram_tune(int node)
{
    int ret;
    BDK_TRACE(DRAM, "N%d: Starting DRAM tuning\n", node);
    ret = libdram_tune(node);
    BDK_TRACE(DRAM, "N%d: DRAM tuning returned %d\n", node, ret);
    return ret;
}

/**
 * Do all the DRAM Margin tests 
 *
 * @param node   Node to test
 *
 * @return Success or Fail
 */
void bdk_dram_margin(int node)
{
    BDK_TRACE(DRAM, "N%d: Starting DRAM margining\n", node);
    libdram_margin(node);
    BDK_TRACE(DRAM, "N%d: Finished DRAM margining.\n", node);
    return;
}

/**
 * Test memory preservation across core domain reset 
 *
 * @param node   Node to test
 *
 * @return Success or Fail
 */
void bdk_dram_test_memory_preserve(int node)
{
    BDK_TRACE(DRAM, "N%d: Test DRAM memory preserve\n", node);
    libdram_test_memory_preserve(node);
    return;
}

/**
 * Return the string of the DRAM configuration info at the specified node.
 * If the node is not configured, NULL is returned.
 *
 * @param node   node to retrieve
 *
 * @return string or NULL
 */
const char* bdk_dram_get_info_string(int node)
{
    #define INFO_STRING_LEN 40
    static char info_string[INFO_STRING_LEN];
    static const char *info_ptr = info_string;

    snprintf(info_string, INFO_STRING_LEN,
             " %ld MB, %ld MT/s, DDR4 %s",
             bdk_dram_get_size_mbytes(node),
             bdk_config_get_int(BDK_CONFIG_DDR_SPEED, node),
             (__bdk_dram_is_rdimm(node, 0)) ? "RDIMM" : "UDIMM");

    return info_ptr;
}


/**
 * Return the highest address currently used by the BDK. This address will
 * be about 4MB above the top of the BDK to make sure small growths between the
 * call and its use don't cause corruption. Any call to memory allocation can
 * change this value.
 *
 * @return Size of the BDK in bytes
 */
uint64_t bdk_dram_get_top_of_bdk(void)
{
    /* Make sure the start address is higher that the BDK's active range.
     *
     * As sbrk() returns a node address, mask off the node portion of
     * the address to make it a physical offset. Doing this simplifies the
     * address checks and calculations which only work with physical offsets.
     */
    uint64_t top_of_bdk = (bdk_ptr_to_phys(sbrk(0)) & bdk_build_mask(40));
    uint64_t top_of_cache = bdk_dram_get_top_of_cache();
    if (top_of_bdk < top_of_cache)
    {
        /* Early BDK code takes care of the first top_of_cache sized area of memory */
        top_of_bdk = top_of_cache;
    }
    else
    {
        /* Give 4MB of extra so the BDK has room to grow */
        top_of_bdk += 4 << 20;
        /* Align it on a 64KB boundary */
        top_of_bdk >>= 16;
        top_of_bdk <<= 16;
    }
    return top_of_bdk;
}
