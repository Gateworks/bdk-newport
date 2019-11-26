/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"

/**
 * Return the number of LMC controllers in use
 *
 * @param node   Node to probe
 *
 * @return 2 or 4 depending on the mode
 */
int __bdk_dram_get_num_lmc(bdk_node_t node)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
    {
        BDK_CSR_INIT(lmcx_dll_ctl1, node, BDK_LMCX_DLL_CTL2(1)); // sample LMC1
        return (lmcx_dll_ctl1.s.intf_en) ? 2 : 1;
    }
    else if (bdk_is_model(OCTEONTX_CN81XX))
    {
        return 1;
    }
    else if (bdk_is_model(OCTEONTX_CN96XX))
    {
        BDK_CSR_INIT(lmcx_dll_ctl1, node, BDK_LMCX_DLL_CTL2(2));
        if (lmcx_dll_ctl1.s.intf_en)
            return 3;
        lmcx_dll_ctl1.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL2(1));
        return (lmcx_dll_ctl1.s.intf_en) ? 2 : 1;
    }
    else if (bdk_is_model(OCTEONTX_CNF95XX))
    {
        /* CN95XX implements LMC0 and LMC2, skipping LMC1. We return
           3 LMCx when LMC2 is enabled so loops work. Note that LMC1
           will always return 1 for __bdk_dram_is_lmc_in_dreset().
           This is to allow code to seamlessly skip the non-existent
           LMC */
        BDK_CSR_INIT(lmcx_dll_ctl1, node, BDK_LMCX_DLL_CTL2(2));
        return (lmcx_dll_ctl1.s.intf_en) ? 3 : 1;
    }
    else if (bdk_is_model(OCTEONTX_LOKI))
    {
        /* LOKI implements LMC0 and LMC2, skipping LMC1. We return
           3 LMCx when LMC2 is enabled so loops work. Note that LMC1
           will always return 1 for __bdk_dram_is_lmc_in_dreset().
           This is to allow code to seamlessly skip the non-existent
           LMC */
        BDK_CSR_INIT(lmcx_dll_ctl1, node, BDK_LMCX_DLL_CTL2(2));
        return (lmcx_dll_ctl1.s.intf_en) ? 3 : 1;
    }
    else if (bdk_is_model(OCTEONTX_CN98XX))
    {
        for (int lmc = 5; lmc >= 0; lmc--)
        {
            BDK_CSR_INIT(lmcx_dll_ctl1, node, BDK_LMCX_DLL_CTL2(lmc));
            if (lmcx_dll_ctl1.s.intf_en)
                return lmc + 1;
        }
        return 1;
    }
    bdk_error("__bdk_dram_get_num_lmc() needs update for this chip\n");
    return 1;
}

/**
 * Return the mask of LMC controllers in use
 *
 * @param node   Node to probe
 *
 * @return       Bits set appropriately
 */
int __bdk_dram_get_lmc_mask(bdk_node_t node)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
    {
        BDK_CSR_INIT(ctl2_1, node, BDK_LMCX_DLL_CTL2(1)); // sample LMC1
        return (ctl2_1.s.intf_en << 1) | 1;
    }
    else if (bdk_is_model(OCTEONTX_CN81XX))
    {
        return 1;
    }
    else if (bdk_is_model(OCTEONTX_CN96XX))
    {
        BDK_CSR_INIT(ctl2_1, node, BDK_LMCX_DLL_CTL2(1));
        BDK_CSR_INIT(ctl2_2, node, BDK_LMCX_DLL_CTL2(2));
        return (ctl2_2.s.intf_en << 2) | (ctl2_1.s.intf_en << 1) | 1;
    }
    else if (bdk_is_model(OCTEONTX_CNF95XX))
    {
        /* CN95XX implements LMC0 and LMC2, skipping LMC1. */
        BDK_CSR_INIT(ctl2_2, node, BDK_LMCX_DLL_CTL2(2));
        return (ctl2_2.s.intf_en << 2) | 1;
    }
    bdk_error("__bdk_dram_get_num_lmc() needs update for this chip\n");
    return 1;
}

/**
 * Return whether the node/LMC is in DRESET
 *
 * @param node   Node to probe
 * @param node   LMC to probe
 *
 * @return 1 or 0
 */
int __bdk_dram_is_lmc_in_dreset(bdk_node_t node, int lmc)
{
    /* CNF95XX and LOKI implements LMC0 and LMC2, skipping LMC1. Avoid
       accessing LMC1 by always saying it is in reset */
    if ((bdk_is_model(OCTEONTX_CNF95XX) || bdk_is_model(OCTEONTX_LOKI)) && (lmc == 1))
        return 1;
    BDK_CSR_INIT(lmcx_dll_ctl2, node, BDK_LMCX_DLL_CTL2(lmc)); // can always read this
    return (lmcx_dll_ctl2.s.dreset != 0) ? 1 : 0;
}

/**
 * Return a mask of the number of row bits in use
 *
 * @param node   Node to probe
 *
 */ 
uint32_t __bdk_dram_get_row_mask(bdk_node_t node, int lmc)
{
    // PROTECT!!!
    if (__bdk_dram_is_lmc_in_dreset(node, lmc)) // check LMCn
        return 0;
    BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(lmc)); // sample LMCn
    int numbits = 14 + lmcx_config.s.pbank_lsb - lmcx_config.s.row_lsb - lmcx_config.s.rank_ena;
    return ((1ul << numbits) - 1);
}

/**
 * Return a mask of the number of column bits in use
 *
 * @param node   Node to probe
 *
 */ 
uint32_t __bdk_dram_get_col_mask(bdk_node_t node, int lmc)
{
    // PROTECT!!!
    if (__bdk_dram_is_lmc_in_dreset(node, lmc)) // check LMCn
        return 0;
    BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(lmc)); // sample LMCn
    int numbits = 11 + lmcx_config.s.row_lsb - __bdk_dram_get_num_bank_bits(node, lmc);
    return ((1ul << numbits) - 1);
}

/**
 * Return the number of bank bits in use
 *
 * @param node   Node to probe
 *
 */ 
// DDR4 x16 today uses only 3 bank bits; DDR4 x4 and x8 always have 4 bank bits
// NOTE: this will change in the future, when DDR4 x16 devices can come with 16 banks!! FIXME!!
int __bdk_dram_get_num_bank_bits(bdk_node_t node, int lmc)
{
    // PROTECT!!!
    if (__bdk_dram_is_lmc_in_dreset(node, lmc)) // check LMCn
        return 0;
    BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(lmc)); // sample LMCn
    int bank_width = (lmcx_config.s.bg2_enable) ? 4 : 3; 
    return bank_width;
}

/**
 * Return whether the node has Registered DIMMs or Unbuffered DIMMs
 *
 * @param node   Node to probe
 *
 * @return 0 (Unbuffered) or 1 (Registered)
 */
int __bdk_dram_is_rdimm(bdk_node_t node, int lmc)
{
    // PROTECT!!!
    if (__bdk_dram_is_lmc_in_dreset(node, lmc)) // check LMCn
        return 0;
    BDK_CSR_INIT(lmcx_control, node, BDK_LMCX_CONTROL(lmc)); // sample LMCn
    return (lmcx_control.s.rdimm_ena != 0);
}

/**
 * Get the amount of DRAM configured for a node. This is read from the LMC
 * controller after DRAM is setup.
 *
 * @param node   Node to query
 *
 * @return Size in megabytes
 */
uint64_t bdk_dram_get_size_mbytes(int node)
{
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return 32 << 10; /* t9x emulators support 32GB, as of 8/8/2019 */
    /* Return zero if dram isn't enabled */
    if (!__bdk_is_dram_enabled(node))
        return 0;

    uint64_t memsize = 0;
    const int num_dram_controllers = __bdk_dram_get_num_lmc(node);
    for (int lmc = 0; lmc < num_dram_controllers; lmc++)
    {
        if (bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            /* Asim doesn't simulate the rank detection, fake 1GB per
               controller */
            memsize += 1ull << 30;
        }
        else
        {
            // PROTECT!!!
	    if (!__bdk_dram_is_lmc_in_dreset(node, lmc)) { // check LMCn
                BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(lmc));
                int num_ranks = bdk_pop(lmcx_config.s.init_status);
                uint64_t rank_size = 1ull << (28 + lmcx_config.s.pbank_lsb - lmcx_config.s.rank_ena);
                memsize += rank_size * num_ranks;
            }
        }
    }
    return memsize >> 20;
}

