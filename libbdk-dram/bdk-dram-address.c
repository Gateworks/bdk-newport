/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-dram/bdk-ccs-addr-decode.h"

/**
 * Given a physical DRAM address, extract information about the node, LMC, DIMM,
 * prank, lrank, bank, row, and column that was accessed.
 *
 * @param address Full LMC Address
 * @param node    Node the address was for
 * @param lmc     LMC controller the address was for
 * @param dimm    DIMM the address was for
 * @param prank   Physical RANK on the DIMM
 * @param lrank   Logical RANK on the DIMM
 * @param bank    BANK on the DIMM
 * @param row     Row on the DIMM
 * @param col     Column on the DIMM
 */
void bdk_dram_address_extract_info(uint64_t address, int *node, int *lmc, int *dimm,
                                    int *prank, int *lrank, int *bank, int *row, int *col)
{
    int bank_lsb, xbits;

    /* LMC and Node are defined within the address for CN8XXX */
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        int bitno = bdk_is_model(OCTEONTX_CN83XX) ? 19 : 20;
        *node = bdk_extract(address, 40, 2); /* Address bits [41:40] */
        /* Determine the LMC controller */
        BDK_CSR_INIT(l2c_ctl, *node, BDK_L2C_CTL);
        /* xbits depends on number of LMCs */
        xbits = __bdk_dram_get_num_lmc(*node) >> 1; // 4->2; 2->1; 1->0
        /* LMC number is probably aliased */
        if (l2c_ctl.s.disidxalias)
            *lmc = bdk_extract(address, 7, xbits);
        else
            *lmc = bdk_extract(address, 7, xbits) ^ bdk_extract(address, bitno, xbits) ^
                    bdk_extract(address, 12, xbits);
    }
    else
    {
        /* Address bits [46:47] - shifted to accomidate LMC in addr*/
        *node = bdk_extract(address, 46, 2);
        /* xbits setup in address conversion to look like 8x */
        xbits = 2;
        *lmc = bdk_extract(address, 7, xbits);
    }

    bank_lsb = 7 + xbits;
    /* Figure out the bank field width */
    BDK_CSR_INIT(lmcx_config, *node, BDK_LMCX_CONFIG(*lmc));
    int bank_width = __bdk_dram_get_num_bank_bits(*node, *lmc);

    /* Extract additional info from the LMC_CONFIG CSR */
    BDK_CSR_INIT(ext_config, *node, BDK_LMCX_EXT_CONFIG(*lmc));
    int dimm_lsb    = 28 + lmcx_config.s.pbank_lsb + xbits;
    int dimm_width  = 40 - dimm_lsb;
    int prank_lsb   = dimm_lsb - lmcx_config.s.rank_ena;
    int prank_width = dimm_lsb - prank_lsb;
    int lrank_lsb   = prank_lsb - ext_config.s.dimm0_cid;
    int lrank_width = prank_lsb - lrank_lsb;
    int row_lsb     = 14 + lmcx_config.s.row_lsb + xbits;
    int row_width   = lrank_lsb - row_lsb;
    int col_hi_lsb  = bank_lsb + bank_width;
    int col_hi_width= row_lsb - col_hi_lsb;

    /* Extract the parts of the address */
    *dimm =  bdk_extract(address, dimm_lsb, dimm_width);
    *prank = bdk_extract(address, prank_lsb, prank_width);
    *lrank = bdk_extract(address, lrank_lsb, lrank_width);
    *row =   bdk_extract(address, row_lsb, row_width);

    /* bank calculation may be aliased... */
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        BDK_CSR_INIT(lmcx_control, *node, BDK_LMCX_CONTROL(*lmc));
        if (lmcx_control.s.xor_bank)
            *bank = bdk_extract(address, bank_lsb, bank_width) ^
                bdk_extract(address, 12 + xbits, bank_width);
        else
            *bank = bdk_extract(address, bank_lsb, bank_width);
    }
    else
    {
        //xor_bank not present on CN9XXX
        *bank = bdk_extract(address, bank_lsb, bank_width);
    }
    /* LMC number already extracted */
    int col_hi = bdk_extract(address, col_hi_lsb, col_hi_width);
    *col = bdk_extract(address, 3, 4) | (col_hi << 4);
    /* Bus byte is address bits [2:0]. Unused here */
}

/**
 * Given a physical DRAM address, extract LMC and rank info only.
 * Only appropriate for CN8xxx chips.
 *
 * @param address Full LMC Address
 * @param rank    Physical RANK on the LMC
 * @param xbits   LMC bits width in address
 *
 * @return LMC controller the address was for
 *
 * NOTE: many assumptions made to speed up processing:
 * 1. LMC number is always aliased
 */
int bdk_dram_address_extract_lmc_rank_cn8xxx(uint64_t address, int xbits, int *rank)
{
    int bitno = bdk_is_model(OCTEONTX_CN83XX) ? 19 : 20;
    int lmc = bdk_extract(address, 7, xbits) ^ bdk_extract(address, bitno, xbits) ^
              bdk_extract(address, 12, xbits);

    /* Extract additional info from the LMC_CSRs */
    BDK_CSR_INIT(lmcx_config, bdk_numa_local(), BDK_LMCX_CONFIG(lmc));
    int dimm_lsb    = 28 + lmcx_config.s.pbank_lsb + xbits;
    int dimm_width  = 40 - dimm_lsb;
    int prank_lsb   = dimm_lsb - lmcx_config.s.rank_ena;
    int prank_width = dimm_lsb - prank_lsb;

    /* Extract the dimm/rank parts of the address */
    int dimm = bdk_extract(address, dimm_lsb, dimm_width);
    *rank = bdk_extract(address, prank_lsb, prank_width) + (2 * dimm);

    return (lmc);
}

/**
 * Construct a physical address given the node, LMC, DIMM, prank, lrank, bank, row, and column.
 *
 * @param node    Node the address was for
 * @param lmc     LMC controller the address was for
 * @param dimm    DIMM the address was for
 * @param prank   Physical RANK on the DIMM
 * @param lrank   Logical RANK on the DIMM
 * @param bank    BANK on the DIMM
 * @param row     Row on the DIMM
 * @param col     Column on the DIMM
 */
uint64_t bdk_dram_address_construct_info(bdk_node_t node, int lmc, int dimm,
                                        int prank, int lrank, int bank, int row, int col)
{
    uint64_t address = 0;
    int bitno = bdk_is_model(OCTEONTX_CN83XX) ? 19 : 20;

    // insert node bits
    address = bdk_insert(address, node, 40, 2); /* Address bits [41:40] */

    /* xbits depends on number of LMCs */
    int xbits = __bdk_dram_get_num_lmc(node) >> 1; // 4->2; 2->1; 1->0
    int bank_lsb = 7 + xbits;

    /* Figure out the bank field width */
    int bank_width = __bdk_dram_get_num_bank_bits(node, lmc);

    /* Extract additional info from the LMC_CONFIG CSR */
    BDK_CSR_INIT(lmcx_config, node, BDK_LMCX_CONFIG(lmc));
    BDK_CSR_INIT(ext_config, node, BDK_LMCX_EXT_CONFIG(lmc));
    int dimm_lsb     = 28 + lmcx_config.s.pbank_lsb + xbits;
    int dimm_width   = 40 - dimm_lsb;
    int prank_lsb    = dimm_lsb - lmcx_config.s.rank_ena;
    int prank_width  = dimm_lsb - prank_lsb;
    int lrank_lsb    = prank_lsb - ext_config.s.dimm0_cid;
    int lrank_width  = prank_lsb - lrank_lsb;
    int row_lsb      = 14 + lmcx_config.s.row_lsb + xbits;
    int row_width    = lrank_lsb - row_lsb;
    int col_hi_lsb   = bank_lsb + bank_width;
    int col_hi_width = row_lsb - col_hi_lsb;

    /* Insert some other parts of the address */
    address = bdk_insert(address, dimm, dimm_lsb, dimm_width);
    address = bdk_insert(address, prank, prank_lsb, prank_width);
    address = bdk_insert(address, lrank, lrank_lsb, lrank_width);
    address = bdk_insert(address, row,  row_lsb,  row_width);
    address = bdk_insert(address, col >> 4, col_hi_lsb, col_hi_width);
    address = bdk_insert(address, col, 3, 4);

    /* bank calculation may be aliased... */
    BDK_CSR_INIT(lmcx_control, node, BDK_LMCX_CONTROL(lmc));
    int new_bank = bank;
    if (lmcx_control.s.xor_bank)
        new_bank ^= bdk_extract(address, 12 + xbits, bank_width);
    address = bdk_insert(address, new_bank, bank_lsb, bank_width);

    /* Determine the actual C bits from the input LMC controller arg */
    /* The input LMC number was probably aliased with other fields */
    BDK_CSR_INIT(l2c_ctl, node, BDK_L2C_CTL);
    int new_lmc = lmc;
    if (!l2c_ctl.s.disidxalias)
        new_lmc ^= bdk_extract(address, bitno, xbits) ^ bdk_extract(address, 12, xbits);
    address = bdk_insert(address, new_lmc, 7, xbits);

    return address;
}
