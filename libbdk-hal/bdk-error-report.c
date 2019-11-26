/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-fus.h"
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-l2c_cbc.h"
#include "libbdk-arch/bdk-csrs-l2c_tad.h"
#include "libbdk-arch/bdk-csrs-l2c_mci.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-mcc.h"
#include "libbdk-arch/bdk-csrs-mdc.h"
#include "libbdk-dram/bdk-ccs-addr-decode.h"

// These are for DRAM parity errors
extern void clear_parity_error(bdk_node_t node, int lmc);
extern void print_parity_error(bdk_node_t node, int lmc);

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(ERROR_DECODE);

#define CLEAR_CHIP_ERROR(csr, chip, field)  \
if (c.chip.field) {                         \
    typedef_##csr w1c;                      \
    w1c.u = 0;                              \
    w1c.chip.field = c.chip.field;          \
    bdk_csr_write(node, bustype_##csr,      \
        busnum_##csr, sizeof(typedef_##csr),\
        csr, w1c.u);                        \
}

#define CHECK_CHIP_ERROR(csr, chip, field)  \
if (c.chip.field) {                         \
    typedef_##csr w1c;                      \
    w1c.u = 0;                              \
    w1c.chip.field = c.chip.field;          \
    bdk_csr_write(node, bustype_##csr,      \
        busnum_##csr, sizeof(typedef_##csr),\
        csr, w1c.u);                        \
    display_error(node, basename_##csr, arguments_##csr, #field); \
}

static void display_error(bdk_node_t node, const char *csr_name, int arg1, int arg2, int arg3, int arg4, const char *field_name)
{
    if (arg4 != -1)
        bdk_error("N%d %s(%d,%d,%d,%d)[%s]\n", node, csr_name, arg1, arg2, arg3, arg4, field_name);
    else if (arg3 != -1)
        bdk_error("N%d %s(%d,%d,%d)[%s]\n", node, csr_name, arg1, arg2, arg3, field_name);
    else if (arg2 != -1)
        bdk_error("N%d %s(%d,%d)[%s]\n", node, csr_name, arg1, arg2, field_name);
    else if (arg1 != -1)
        bdk_error("N%d %s(%d)[%s]\n", node, csr_name, arg1, field_name);
    else
        bdk_error("N%d %s[%s]\n", node, csr_name, field_name);
}

static void construct_phase_info(char *buffer, int fill_order, int fail_index, int err_bits)
{
    int basic_phase, bitno, bitmask, phase_no, read_no;
    //printf("decode_err(%d, %d, %d)\n", fill_order, fail_index, err_bits);

    if (fill_order != 0) {
        snprintf(buffer, 8, "FO%02d", fill_order);
        return;
    }
    if ((err_bits & 15) == 0) {
        snprintf(buffer, 8, "EBZ!");
        return;
    }

    // fail_index determines the byte of the map associated with the fill_order
    // FIXME: we only try for fill_order == 0 for now...
    // for FO = 0, it is a direct map: fail_index == byte # in the map == byte #
    // and the byte # maps directly to the basic phase #
    read_no = ((fail_index & 7) >> 2) + 1;
    basic_phase = (fail_index & 3) * 2;

    bitno = 0;
    bitmask = err_bits & 15;
    while (!(bitmask & 1)) { bitno++; bitmask >>= 1; } // FIXME: better error detect

    //printf("basic phase = %d or %d\n", basic_phase, basic_phase + 1);
    //printf("bitno phase = %d or %d\n", bitno, bitno + 4);

    phase_no = -1;
    if ((basic_phase == bitno) || (basic_phase == bitno + 4))
        phase_no = basic_phase;
    else if ((basic_phase + 1 == bitno) || (basic_phase + 1 == bitno + 4))
        phase_no = basic_phase + 1;

    if (phase_no < 0) { // better indication of not found/illegality
        snprintf(buffer, 8, "ILL!");
        return;
    }

    snprintf(buffer, 8, "R%dP%d", read_no, phase_no);
    return;
}

// Table to translate ECC single-bit syndrome to "byte.bit" format.
//
// indexed by syndrome, data is [7:4] = byte no. + 1 and [3:0] = bit no.
// hack: make the byte no. bits be non-zero even for byte 0;
// this is so non-explicit data can be 0x00 and will be illegal.
static const unsigned char
ecc_syndrome_to_bytebit[256] = {
    // byte 0, bits 0 to 7
    [0xce] = 0x10, [0xcb] = 0x11, [0xd3] = 0x12, [0xd5] = 0x13,
    [0xd6] = 0x14, [0xd9] = 0x15, [0xda] = 0x16, [0xdc] = 0x17,
    // byte 1, bits 0 to 7
    [0x23] = 0x20, [0x25] = 0x21, [0x26] = 0x22, [0x29] = 0x23,
    [0x2a] = 0x24, [0x2c] = 0x25, [0x31] = 0x26, [0x34] = 0x27,
    // byte 2, bits 0 to 7
    [0x0e] = 0x30, [0x0b] = 0x31, [0x13] = 0x32, [0x15] = 0x33,
    [0x16] = 0x34, [0x19] = 0x35, [0x1a] = 0x36, [0x1c] = 0x37,
    // byte 3, bits 0 to 7
    [0xe3] = 0x40, [0xe5] = 0x41, [0xe6] = 0x42, [0xe9] = 0x43,
    [0xea] = 0x44, [0xec] = 0x45, [0xf1] = 0x46, [0xf4] = 0x47,
    // byte 4, bits 0 to 7
    [0x4f] = 0x50, [0x4a] = 0x51, [0x52] = 0x52, [0x54] = 0x53,
    [0x57] = 0x54, [0x58] = 0x55, [0x5b] = 0x56, [0x5d] = 0x57,
    // byte 5, bits 0 to 7
    [0xa2] = 0x60, [0xa4] = 0x61, [0xa7] = 0x62, [0xa8] = 0x63,
    [0xab] = 0x64, [0xad] = 0x65, [0xb0] = 0x66, [0xb5] = 0x67,
    // byte 6, bits 0 to 7
    [0x8f] = 0x70, [0x8a] = 0x71, [0x92] = 0x72, [0x94] = 0x73,
    [0x97] = 0x74, [0x98] = 0x75, [0x9b] = 0x76, [0x9d] = 0x77,
    // byte 7, bits 0 to 7
    [0x62] = 0x80, [0x64] = 0x81, [0x67] = 0x82, [0x68] = 0x83,
    [0x6b] = 0x84, [0x6d] = 0x85, [0x70] = 0x86, [0x75] = 0x87,
    // byte 8, bits 0 to 7
    [0x01] = 0x90, [0x02] = 0x91, [0x04] = 0x92, [0x08] = 0x93,
    [0x10] = 0x94, [0x20] = 0x95, [0x40] = 0x96, [0x80] = 0x97
};

static void check_cn8xxx_l2c_cbcs(bdk_node_t node, int limit)
{
    for (int index = 0; index < limit; index++) {
        BDK_CSR_INIT(c, node, BDK_L2C_CBCX_INT_W1C(index));
        CHECK_CHIP_ERROR(BDK_L2C_CBCX_INT_W1C(index), s, iowrdisoci);
        CHECK_CHIP_ERROR(BDK_L2C_CBCX_INT_W1C(index), s, iorddisoci);
        CHECK_CHIP_ERROR(BDK_L2C_CBCX_INT_W1C(index), s, mibdbe);
        CHECK_CHIP_ERROR(BDK_L2C_CBCX_INT_W1C(index), s, mibsbe);
        CHECK_CHIP_ERROR(BDK_L2C_CBCX_INT_W1C(index), s, rsddbe);
        CHECK_CHIP_ERROR(BDK_L2C_CBCX_INT_W1C(index), s, rsdsbe);
    }
}

void check_cn8xxx_l2c_mcis(bdk_node_t node, int limit)
{
    for (int index = 0; index < limit; index++) {
        BDK_CSR_INIT(w1c, node, BDK_L2C_MCIX_INT_W1C(index));
        if (w1c.s.vbfdbe || w1c.s.vbfsbe) { // L2C_MCIX ECC errors
            BDK_CSR_INIT(err, node, BDK_L2C_MCIX_ERR(index));
            BDK_CSR_WRITE(node, BDK_L2C_MCIX_INT_W1C(index), w1c.u);
            bdk_error("N%d.L2C_MCIX_INT(%d)[vbf%s]: L2C_MCIX_ERR [0x%016lx]\n",
                      node, index, (w1c.s.vbfdbe) ? "dbe" : "sbe", err.u);
        }
    }
}

static void check_cn8xxx_l2c_tads(bdk_node_t node, int limit)
{
    for (int index = 0; index < limit; index++) {
        BDK_CSR_INIT(c, node, BDK_L2C_TADX_INT_W1C(index));
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, wrdisoci);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, rddisoci);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, lfbto);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, wrdislmc);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, rddislmc);
        //CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, noway); /* Happens when we run with L2 locked */
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, tagdbe);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, tagsbe);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, reserved_6_7);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, fbfdbe);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, fbfsbe);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, sbfdbe);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, sbfsbe);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, l2ddbe);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), s, l2dsbe);
    }
}

// "check_intf_en" arg: 0 = no check INTF_EN, 1 = check INTF_EN
/*static*/ void check_cn8xxx_lmc(bdk_node_t node, int index, int check_intf_en)
{
    BDK_CSR_INIT(lmcx_dll_ctl2, node, BDK_LMCX_DLL_CTL2(index));

    // always make sure it is out of DRESET first...
    if (lmcx_dll_ctl2.s.dreset)
        return;

    // then, if check_intf_en == 1, must have INTF_EN == 1
    if ((check_intf_en != 0) && (lmcx_dll_ctl2.s.intf_en == 0))
        return;

    BDK_CSR_INIT(c, node, BDK_LMCX_INT(index));
    CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, macram_ded_err);
    CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, macram_sec_err);
    //CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, ddr_err);
    CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, dlcram_ded_err);
    CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, dlcram_sec_err);
    //CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, ded_err);
    //CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, sec_err);
    //CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, nxm_wr_err);

    if (c.s.ddr_err) {
        bdk_error("N%d.LMC%d: DDR_ERR \n", node, index);
        print_parity_error(node, index);
        clear_parity_error(node, index); // FIXME: must do this first?
        CLEAR_CHIP_ERROR(BDK_LMCX_INT(index), s, ddr_err);
    }

    if (c.cn8.nxm_wr_err) {
        BDK_CSR_INIT(nxm_fadr, node, BDK_LMCX_NXM_FADR(index));
        bdk_error("N%d.LMC%d: NXM_WR_ERR: %s at [0x%016lx]\n",
                  node, index, (nxm_fadr.s.nxm_type) ? "Write" : "Read",
                  (nxm_fadr.s.nxm_faddr | ((nxm_fadr.u >> 2) & (1UL << 37))));
        CLEAR_CHIP_ERROR(BDK_LMCX_INT(index), cn8, nxm_wr_err);
    }

    /* A double bit error overwrites single info, so only
       report/count single bit errors if there hasn't been a
       double bit error */
    if (c.cn8.ded_err || c.cn8.sec_err) {
        char *err_type;
        char synstr[20];
        char phasestr[8];
        int err_bits;
        BDK_CSR_INIT(fadr, node, BDK_LMCX_FADR(index));
        BDK_CSR_INIT(ecc_synd, node, BDK_LMCX_ECC_SYND(index));
        uint64_t syndrome = ecc_synd.u;
        CLEAR_CHIP_ERROR(BDK_LMCX_INT(index), cn8, ded_err);
        CLEAR_CHIP_ERROR(BDK_LMCX_INT(index), cn8, sec_err);
        if (c.s.ded_err) { // if DED, count it and do not count SEC
            bdk_atomic_add64_nosync(&__bdk_dram_ecc_double_bit_errors[index], 1);
            err_type = "double";
            err_bits = c.cn8.ded_err;
            snprintf(synstr, sizeof(synstr), "DED=0x%x", err_bits);
        } else { // must be just SEC, also extract the syndrome byte
            bdk_atomic_add64_nosync(&__bdk_dram_ecc_single_bit_errors[index], 1);
            err_type = "single";
            err_bits = c.cn8.sec_err;
            int i = err_bits;
            while ((i & 1) == 0) {syndrome >>= 8; i >>= 1; }
            syndrome &= 0xff;
            int bytebit = ecc_syndrome_to_bytebit[syndrome];
            if (bytebit != 0x00) {
                snprintf(synstr, sizeof(synstr), "BYTE %d.%d/0x%x",
                         ((bytebit >> 4) & 0x0f) - 1, bytebit & 0x0f, err_bits);
            } else {
                snprintf(synstr, sizeof(synstr), "SYND 0x%02lx/0x%x", syndrome, err_bits);
            }
        }
        uint32_t frow = fadr.s.frow & __bdk_dram_get_row_mask(node, index);
        uint32_t fcol = fadr.s.fcol & __bdk_dram_get_col_mask(node, index);
        uint64_t where = bdk_dram_address_construct_info(node, index, fadr.s.fdimm, fadr.s.fbunk,
                                                         fadr.s.fcid, fadr.s.fbank, frow, fcol);
        construct_phase_info(phasestr, fadr.s.fill_order, bdk_extract(fadr.s.fcol, 1, 3), err_bits);

        bdk_error("N%d.LMC%d: ECC %s (DIMM%d,Rank%d/%d,Bank%02d,Row 0x%05x,Col 0x%04x,%s,%s)[0x%011lx]\n",
                  node, index, err_type, fadr.s.fdimm, fadr.s.fbunk, fadr.s.fcid,
                  fadr.s.fbank, frow, fcol, phasestr, synstr, where);
    } /* if (c.s.ded_err || c.s.sec_err) */
}

//////////////
// 83XX chip

static void enable_cn83xx(bdk_node_t node)
{
    /* Do nothing for now */
}

static void check_cn83xx(bdk_node_t node)
{
    check_cn8xxx_l2c_cbcs(node, 2);
    check_cn8xxx_l2c_mcis(node, 3);
    check_cn8xxx_l2c_tads(node, 4);

    check_cn8xxx_lmc(node, 0, 0); // LMC0 without INTF_EN
    check_cn8xxx_lmc(node, 1, 1); // LMC1 maybe not, so check INTF_EN
}

//////////////
// 81XX chip

static void enable_cn81xx(bdk_node_t node)
{
    /* Do nothing for now */
}

static void check_cn81xx(bdk_node_t node)
{
    check_cn8xxx_l2c_cbcs(node, 1);
    check_cn8xxx_l2c_mcis(node, 1);
    check_cn8xxx_l2c_tads(node, 1);

    check_cn8xxx_lmc(node, 0, 0); // LMC0 without INTF_EN
}

//////////////
// 9XXX chip

#define PRINT_EXTRA_ECC_ERRORS_CN9XXX 0 // set to 1 for extensive info

static void enable_cn9xxx(bdk_node_t node)
{
    /* Check results of BIST in MDC */
    BDK_CSR_INIT(mdc_bist_status, node, BDK_MDC_BIST_STATUS);
    if (mdc_bist_status.s.fail_count)
    {
        int count = mdc_bist_status.s.fail_count;
        if (count > 32)
            count = 32;
        for (int i = 0; i < count; i++)
        {
            BDK_CSR_INIT(mdc_bist_failx, node, BDK_MDC_BIST_FAILX(i));
            bdk_error("BIST failure %d, Chain %d, Hub %d, Node %d, Info 0x%x\n",
                i, mdc_bist_failx.s.chain_id, mdc_bist_failx.s.hub_id,
                mdc_bist_failx.s.node_id, mdc_bist_failx.s.info);
        }
        if (mdc_bist_status.s.fail_count > 32)
            bdk_error("More BIST failures without fail info\n");
    }
    else
        BDK_TRACE(INIT, "MDC: No BIST errors detected\n");

    /* Report soft repairs during BIST. Screened parts will not report these */
    BDK_CSR_INIT(soft_repair, node, BDK_FUS_SOFT_REPAIR);
    if (soft_repair.s.numdefects)
        bdk_error("BIST reports %d detected defects\n", soft_repair.s.numdefects);
    else
        BDK_TRACE(INIT, "MDC: No BIST defects detected\n");


    /* Enable MDC ECC error reporting */
    BDK_CSR_MODIFY(c, node, BDK_MDC_INT_W1S,
        c.s.ecc_error = 1);

    /* Enable LMC ECC error reporting */

    /* Enable Memory Poisoning so All DBEs are reported as ERR02 */
    BDK_CSR_MODIFY(c, node, BDK_MCCX_CONFIG(0),
                   //c.s.early_rsp_val_ena = 0;  /* Disable Early Error Response */
                   //c.s.retry_scrub_ena = 0;    /* Disable Error Retry */
                   c.s.dis_tadpsn = 0;           /* Enable Memory Poisoning */
                   c.s.dis_tadecc = 0);          /* Enable ECC */
    if (!bdk_is_model(OCTEONTX_CNF95XX) && !bdk_is_model(OCTEONTX_LOKI))
    {
        BDK_CSR_MODIFY(c, node, BDK_MCCX_CONFIG(1),
                       //c.s.early_rsp_val_ena = 0;  /* Disable Early Error Response */
                       //c.s.retry_scrub_ena = 0;    /* Disable Error Retry */
                       c.s.dis_tadpsn = 0;           /* Enable Memory Poisoning */
                       c.s.dis_tadecc = 0);          /* Enable ECC */
    }

    // we have not initialized any LMCs by this time, so try them all
    for (int lmc = 0; lmc < 3; lmc++)
    {
        // this mapping will only allow access to legal MCCs for the LMCs on the chip
        bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);

        /* Enable Both Correctable and Uncorrectable ECC Interrupts */
        BDK_CSR_MODIFY(c, node, BDK_MCCX_LMCOEX_RAS_ERR00CTLR(lmc_map.mcc, lmc_map.lmcoe),
                       c.s.cfi = 1;
                       c.s.fi = 1);

        /* Enable Read and Write NXM interrupts */
        BDK_CSR_WRITE(node, BDK_MCCX_LMCOEX_INT_ENA_W1S(lmc_map.mcc, lmc_map.lmcoe), 3);

        /* Enable ERR00 through ERR03 MCC errors for all Correctable and Uncorrectable errors */
        BDK_CSR_WRITE(node, BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(lmc_map.mcc, lmc_map.lmcoe), 0x0F);

        /* Enable only ERR00 LMC Errors all other reserved */
        // This is only good for CRC/parity errors!!!
        // FIXME: this is done elsewhere later when configuration options are available
        //BDK_CSR_WRITE(node, BDK_LMCX_RAS_INT_ENA_W1S(lmc), 0x1);
        //BDK_CSR_MODIFY(c, node, BDK_LMCX_RAS_ERR00CTLR(lmc),
        //               c.s.cfi = 1;
        //               c.s.fi = 1);

        /* Ensure Background Scrubbing Is Disabled */
        BDK_CSR_MODIFY(c, node, BDK_MCCX_LMCOEX_BSCRUB_CFG(lmc_map.mcc, lmc_map.lmcoe),
                       c.s.enable = 0);
    }
}

/**
 * Read through MCC RAS ROM for each LMC and each error type and
 * extract the error information before printing it to the console.
 *
 * @param node      Node the address was for
 */

#if PRINT_EXTRA_ECC_ERRORS_CN9XXX

// extra debug output for MCC ECC errors
static void
bdk_print_extra_ecc_errors_cn9xxx_lmc(bdk_node_t node, int lmc,
                                      bdk_mccx_lmcoex_ras_err00addr_t erraddr,
                                      bdk_mccx_lmcoex_ras_err00status_t status)
{
    bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);

    // do status specially
    printf("ERROR: N%d.LMC%d: EXTRA ECC: STATUS=0x%08lX[",
              node, lmc, status.u);
    if (status.s.av) printf("AV,");
    if (status.s.v) printf("V,");
    if (status.s.ue) printf("UE,");
    if (status.s.er) printf("ER,");
    if (status.s.of) printf("OF,");
    if (status.s.mv) printf("MV,");
    if (status.s.ce) printf("CE%d,", status.s.ce);
    if (status.s.de) printf("DE,");
    if (status.s.pn) printf("PN,");
    if (status.s.uet) printf("UET%d,", status.s.uet);
    if (status.s.ierr) printf("IERR%02x,", status.s.ierr);
    if (status.s.serr) printf("SERR%02x", status.s.serr);

    printf("]\n");

    // ERRxxADDR decode
    uint64_t paddr = (uint64_t)erraddr.s.paddr;
    bdk_error("N%d.LMC%d: EXTRA ECC: NSEC=%d, SI=%d, AI=%d, PADDR=0x%lX\n",
              node, lmc, erraddr.s.nsec, erraddr.s.si, erraddr.s.ai, paddr);
    bdk_error("N%d.LMC%d: EXTRA ECC: FLRBIT=%1d, FAREM=0x%1X, FREGION=0x%1X, FO=%1d, FOFFSET=0x%06lX, FIDX=%d\n",
              node, lmc,
              (int)bdk_extract(paddr, 47, 1),
              (int)bdk_extract(paddr, 43, 4),
              (int)bdk_extract(paddr, 39, 4),
              (int)bdk_extract(paddr, 38, 1),
              (uint64_t)bdk_extract(paddr, 3, 35),
              (int)bdk_extract(erraddr.u, 0, 3));

    // ERRxxFR and ERRxxCTLR
    bdk_mccx_lmcoex_ras_err00fr_t fr;
    bdk_mccx_lmcoex_ras_err00ctlr_t ctlr;
    fr.u      = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR00FR(lmc_map.mcc, lmc_map.lmcoe));
    ctlr.u    = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR00CTLR(lmc_map.mcc, lmc_map.lmcoe));
    bdk_error("N%d.LMC%d: EXTRA ECC: FR=0x%05lX, CTLR=0x%03lX\n",
              node, lmc, fr.u, ctlr.u);
}
#endif /* PRINT_EXTRA_ECC_ERRORS_CN9XXX */

void bdk_check_ecc_errors_cn9xxx_lmc(bdk_node_t node, int lmc)
{
    // this mapping will only allow access to legal MCCs for the LMCs on the chip
    bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);
    bdk_mccx_lmcoex_ras_int_t ras_int;

    // use ERRGSR0 which is a direct map of the VALID bits from the status CSRs;
    // this is useful at all times, unlike RAS_INT which may have counter-controlled bits
    ras_int.u = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERRGSR0(lmc_map.mcc, lmc_map.lmcoe));

    if (ras_int.u)
    {
        char *err_type = "";
        char synstr[24];
        int node_num = (int)node;
        int lmc_num = 0;
        int dimm = 0;
        int prank = 0;
        int lrank = 0;
        int bank = 0;
        int row = 0;
        int col = 0;
        int beat = 0;
        int fidx = 0;
        uint64_t syns_left = 0;
        uint64_t address = 0;
        uint64_t physaddr = 0;
        uint64_t lmcaddr = 0;
        bdk_mccx_lmcoex_ras_err00status_t status;
        bdk_mccx_lmcoex_ras_err00addr_t erraddr;
        bdk_mccx_lmcoex_ras_err00misc0_t misc0;
        int report_err;

        status.u  = 0;
        erraddr.u = 0;
        misc0.u   = 0;

        // use the RAS_INT_ENA bits to say whether we actually had enabled the interrupts;
        // that is, the ERR0xSTATUS[V] bits are always current, but we may not desire reporting them
        BDK_CSR_INIT(ras_int_ena, node, BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(lmc_map.mcc, lmc_map.lmcoe));

        // no report but do clear if ERR00-ERR03 bits are not enabled
        report_err = ((ras_int.u & ras_int_ena.u & 0x0F) != 0);

        // check for double bit errors only in MCC
        if ((ras_int.s.err03) || (ras_int.s.err02)) {
            if (ras_int.s.err02) {
                status.u  = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR02STATUS(lmc_map.mcc, lmc_map.lmcoe));
                erraddr.u = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR02ADDR(lmc_map.mcc, lmc_map.lmcoe));
                syns_left = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR02MISC1(lmc_map.mcc, lmc_map.lmcoe));

                // Clear Error Interrupts by writing BDK_MCCX_LMCOEX_RAS_ERR02STATUS[V]
                BDK_CSR_WRITE(node, BDK_MCCX_LMCOEX_RAS_ERR02STATUS(lmc_map.mcc, lmc_map.lmcoe), status.u);
                //err_type = "double ERR02";
            }
            // more double bit errors from MCC
            else if (ras_int.s.err03) {
                status.u  = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR03STATUS(lmc_map.mcc, lmc_map.lmcoe));
                erraddr.u = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR03ADDR(lmc_map.mcc, lmc_map.lmcoe));
                syns_left = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR03MISC1(lmc_map.mcc, lmc_map.lmcoe));

                // Clear Error Interrupts by writing BDK_MCCX_LMCOEX_RAS_ERR03STATUS[V]
                BDK_CSR_WRITE(node, BDK_MCCX_LMCOEX_RAS_ERR03STATUS(lmc_map.mcc, lmc_map.lmcoe), status.u);
                //err_type = "double ERR03";
            }
            err_type = "double";
            bdk_atomic_add64_nosync(&__bdk_dram_ecc_double_bit_errors[lmc], 1);
        }
        // check for single bit errors
        else if ((ras_int.s.err01) || (ras_int.s.err00)) { // else check only when no double bit errs
            // single bit errors from MCC
            if (ras_int.s.err00) {
                status.u  = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR00STATUS(lmc_map.mcc, lmc_map.lmcoe));
                erraddr.u = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR00ADDR(lmc_map.mcc, lmc_map.lmcoe));
                misc0.u   = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR00MISC0(lmc_map.mcc, lmc_map.lmcoe));
                syns_left = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR00MISC1(lmc_map.mcc, lmc_map.lmcoe));

                // Clear Error Interrupts by writing BDK_MCCX_LMCOEX_RAS_ERR00STATUS[V]
                BDK_CSR_WRITE(node, BDK_MCCX_LMCOEX_RAS_ERR00STATUS(lmc_map.mcc, lmc_map.lmcoe), status.u);
                BDK_CSR_WRITE(node, BDK_MCCX_LMCOEX_RAS_ERR00MISC0(lmc_map.mcc, lmc_map.lmcoe), 0UL);
                //err_type = "single ERR00";
            }
            // more single bit errors from MCC
            else if (ras_int.s.err01) {
                status.u  = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR01STATUS(lmc_map.mcc, lmc_map.lmcoe));
                erraddr.u = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR01ADDR(lmc_map.mcc, lmc_map.lmcoe));
                misc0.u   = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR01MISC0(lmc_map.mcc, lmc_map.lmcoe));
                syns_left = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RAS_ERR01MISC1(lmc_map.mcc, lmc_map.lmcoe));

                // Clear Error Interrupts by writing BDK_MCCX_LMCOEX_RAS_ERR01STATUS[V]
                BDK_CSR_WRITE(node, BDK_MCCX_LMCOEX_RAS_ERR01STATUS(lmc_map.mcc, lmc_map.lmcoe), status.u);
                BDK_CSR_WRITE(node, BDK_MCCX_LMCOEX_RAS_ERR01MISC0(lmc_map.mcc, lmc_map.lmcoe), 0UL);
                //err_type = "single ERR01";
            }
            err_type = "single";
            bdk_atomic_add64_nosync(&__bdk_dram_ecc_single_bit_errors[lmc], 1);
        }

        address = bdk_extract(erraddr.u, 3, 35) * BDK_CACHE_LINE_SIZE;

        // Display failing cache line index instead of phase string on CN9XXX
        fidx = bdk_extract(erraddr.u, 0, 3);

        if (!report_err) { // FIXME? use TRACE to control output or not
            BDK_TRACE(DRAM, "N%d.LMC%d: EXTRA ECC: %s @ 0x%016lX (I%02lX/E%02lx)\n",
                      node, lmc, err_type, address,
                      ras_int.u & 0x0FUL, ras_int_ena.u & 0x0FUL);

#if PRINT_EXTRA_ECC_ERRORS_CN9XXX
            // for debugging, enable this to always print all the info for the "extra" errors
            bdk_error("N%d.LMC%d: EXTRA ECC: %s @ 0x%016lX (I%02lX/E%02lx)\n",
                      node, lmc, err_type, address,
                      ras_int.u & 0x0FUL, ras_int_ena.u & 0x0FUL);
            bdk_print_extra_ecc_errors_cn9xxx_lmc(node, lmc, erraddr, status);
#endif /* PRINT_EXTRA_ECC_ERRORS_CN9XXX */

            return; // we bypass reporting on this LMC
        }

        // Convert LMC address into Physical address
        // FIXME: Note that when address scrambling is enabled on this LMC,
        // FIXME: we would still like the rank and DIMM to be correct in ECC reports;
        // FIXME: that means we will need to ensure that the DIMM and rank bits of
        // FIXME: the LMC address will not be scrambled, by placing 0's appropriately.
        // FIXME: BDK_CSR_INIT(lmc_adr_scramble, node, BDK_LMCX_ADR_SCRAMBLE(lmc));
        lmcaddr = __bdk_ccs_get_lmc_addr(node, address, lmc);
        physaddr = bdk_ccs_convert_lmc_to_pa(node, lmcaddr);
        if (physaddr == (uint64_t)-1) {
            bdk_error("N%d.LMC%d: ECC: LMC to Phys conversion failed: ADDR: 0x%lx, LMC: 0x%lx\n",
                      node, lmc, address, lmcaddr);
            return;
        }

        synstr[0] = 0; // just in case...
        while (syns_left) {
            // Check each byte of the syndrome for error data
            // each byte represents the syndrome data for one of 8 beats in a transaction
            // The syndrome can hold error data for multiple errors
            // but if the byte is 0 there's no error
            if (syns_left & 0xFF) {
                int bytebit = ecc_syndrome_to_bytebit[syns_left & 0xFF];
                if (bytebit != 0x00) {
                    if ((ras_int.s.err03) || (ras_int.s.err02)) {
                        snprintf(synstr, sizeof(synstr), "DED=0x%02x", (0x1 << beat));
                    } else {
                        snprintf(synstr, sizeof(synstr), "BYTE %d.%d/0x%02x [%x/%04x]",
                                 ((bytebit >> 4) & 0x0f) - 1, bytebit & 0x0f, (0x1 << beat),
                                 misc0.s.of, misc0.s.cec);
                    }
                } else { // syndrome led to bytebit == 0x00
                    snprintf(synstr, sizeof(synstr), "SYN=0x%02lx", syns_left & 0xFF);
                }
                break;
            }
            syns_left >>= 8;
            beat++;
        }

        bdk_dram_address_extract_info(lmcaddr, &node_num, &lmc_num, &dimm, &prank,
                                      &lrank, &bank, &row, &col);
        bdk_error("N%d.LMC%d: ECC %s (DIMM%d,Rank%d/%d,Bank%02d,Row 0x%05x,Col 0x%04x,FIDX=%d,%s)[0x%012lx]\n",
                  node, lmc, err_type, dimm, prank, lrank, bank, row, col, fidx, synstr, physaddr);

#if PRINT_EXTRA_ECC_ERRORS_CN9XXX
        // print extra info for "normal" errors if enabled
        bdk_print_extra_ecc_errors_cn9xxx_lmc(node, lmc, erraddr, status);
#endif /* PRINT_EXTRA_ECC_ERRORS_CN9XXX */

    } /* if (ras_int.u) */
}

void bdk_check_ecc_errors_cn9xxx(bdk_node_t node)
{
    // check for DRAM errors on all present LMCs
    bdk_check_ecc_errors_cn9xxx_lmc(node, 0);
    if (!bdk_is_model(OCTEONTX_CNF95XX) && !bdk_is_model(OCTEONTX_LOKI))
        bdk_check_ecc_errors_cn9xxx_lmc(node, 1);
    bdk_check_ecc_errors_cn9xxx_lmc(node, 2);
}

static void bdk_check_nxm_errors_cn9xxx_lmc(bdk_node_t node, int lmc)
{
    bdk_mccx_lmcoex_rdnxm_fadr_t fadr;
    static const char *nxm_str[4] = { "NONE","RD","WR","BOTH" };

    // this mapping will only allow access to legal MCCs for the LMCs on the chip
    bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);

    BDK_CSR_INIT(mcc_lmcoe_int, node, BDK_MCCX_LMCOEX_INT(lmc_map.mcc, lmc_map.lmcoe));

    if ((mcc_lmcoe_int.u & 3) != 0) {
        uint64_t address, lmcaddr, physaddr;
        int node_num, lmc_num, dimm, prank, lrank, bank, row, col;

        if (mcc_lmcoe_int.s.rd_nxm)
            fadr.u = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_RDNXM_FADR(lmc_map.mcc, lmc_map.lmcoe));
        else
            fadr.u = BDK_CSR_READ(node, BDK_MCCX_LMCOEX_WRNXM_FADR(lmc_map.mcc, lmc_map.lmcoe));
                
        // try to construct a meaningful physical address for the NXM
        address = (uint64_t)fadr.s.fadr * BDK_CACHE_LINE_SIZE;
        lmcaddr = __bdk_ccs_get_lmc_addr(node, address, lmc);
        physaddr = bdk_ccs_convert_lmc_to_pa(node, lmcaddr);
        if (physaddr == (uint64_t)-1) {
            printf("N%d.LMC%d: ERROR: LMC to Phys conversion failed: ADDR: 0x%lx, LMC: 0x%lx\n",
                   node, lmc, address, lmcaddr);
        }
            
        bdk_dram_address_extract_info(lmcaddr, &node_num, &lmc_num, &dimm,
                                      &prank, &lrank, &bank, &row, &col);
        node_num = (int) node;
        lmc_num = lmc;
        bdk_error("N%d.LMC%d: %s_NXM (DIMM%d,Rank%d/%d,Bank%02d,Row 0x%05x,Col 0x%04x)[0x%012lx]\n",
                  node, lmc, nxm_str[mcc_lmcoe_int.u & 3], dimm, prank, lrank,
                  bank, row, col, physaddr);
#if 0
        bdk_error("N%d.LMC%d: %s_NXM: FLRBIT=%d, FAREM=%X, FREGION=%X, FADR=0x%010lX\n",
                  node, lmc, nxm_str[mcc_lmcoe_int.u & 3], fadr.s.flrbit,
                  fadr.s.farem, fadr.s.fregion, (uint64_t)fadr.s.fadr);
#endif
        // clear it
        BDK_CSR_WRITE(node, BDK_MCCX_LMCOEX_INT(lmc_map.mcc, lmc_map.lmcoe), mcc_lmcoe_int.u);
    }
}

static void bdk_check_nxm_errors_cn9xxx(bdk_node_t node)
{
    // check for NXM errors on all present LMCs
    bdk_check_nxm_errors_cn9xxx_lmc(node, 0);
    if (!bdk_is_model(OCTEONTX_CNF95XX) && !bdk_is_model(OCTEONTX_LOKI))
        bdk_check_nxm_errors_cn9xxx_lmc(node, 1);
    bdk_check_nxm_errors_cn9xxx_lmc(node, 2);
}

void bdk_check_parity_errors_cn9xxx_lmc(bdk_node_t node, int lmc)
{
    // check for DRAM parity error on a channel
    BDK_CSR_INIT(status, node, BDK_LMCX_RAS_ERR00STATUS(lmc));
    if (status.s.v)
    {
        int node_num = (int)node;
        int lmc_num = 0;
        int dimm = 0;
        int prank = 0;
        int lrank = 0;
        int bank = 0;
        int row = 0;
        int col = 0;
        uint64_t physaddr;
        uint64_t lmcaddr;
        uint64_t address;
            
        bdk_error("N%d.LMC%d: PARITY ERROR detected...\n", node, lmc);

        BDK_CSR_INIT(erraddr, node, BDK_LMCX_RAS_ERR00ADDR(lmc));
        
        // clear parity error on DIMM
        clear_parity_error(node, lmc);

        // MUST reset counter CSR to overflow on next or it is not reported
        BDK_CSR_INIT(misc0, node, BDK_LMCX_RAS_ERR00MISC0(lmc));
        misc0.s.cec = 0x7FFF; // set Corrected_Error_Counter FULL
        misc0.s.of = 0; // set OverFlow clear
        BDK_CSR_WRITE(node, BDK_LMCX_RAS_ERR00MISC0(lmc), misc0.u);

        // Clear Error Interrupts by (re-)writing RAS_ERR00STATUS[V]
        BDK_CSR_WRITE(node, BDK_LMCX_RAS_ERR00STATUS(lmc), status.u);
            
        address = bdk_extract(erraddr.u, 3, 35) * BDK_CACHE_LINE_SIZE;
        lmcaddr = __bdk_ccs_get_lmc_addr(node, address, lmc);
        physaddr = bdk_ccs_convert_lmc_to_pa(node, lmcaddr);
        if (physaddr == (uint64_t)-1) {
            bdk_error("N%d.LMC%d: PARITY: LMC to Phys conversion failed: ADDR: 0x%lx, LMC: 0x%lx\n",
                      node, lmc, address, lmcaddr);
            return;
        }

        bdk_dram_address_extract_info(lmcaddr, &node_num, &lmc_num, &dimm, &prank,
                                      &lrank, &bank, &row, &col);
            
        bdk_error("N%d.LMC%d: PARITY ERR (DIMM%d,Rank%d/%d,Bank%02d,Row 0x%05x,Col 0x%04x),LMC[0x%011lx],PA[0x%011lx]\n",
                  node, lmc, dimm, prank, lrank, bank, row, col, address, physaddr);
    }
}

static void bdk_check_parity_errors_cn9xxx(bdk_node_t node)
{
    // check for DRAM parity errors on all present LMCs
    bdk_check_parity_errors_cn9xxx_lmc(node, 0);
    if (!bdk_is_model(OCTEONTX_CNF95XX) && !bdk_is_model(OCTEONTX_LOKI))
        bdk_check_parity_errors_cn9xxx_lmc(node, 1);
    bdk_check_parity_errors_cn9xxx_lmc(node, 2);
}

static void check_cn9xxx(bdk_node_t node)
{
    // Look for MDC ECC errors
    BDK_CSR_INIT(mdc_int_w1s, node, BDK_MDC_INT_W1S);
    if (mdc_int_w1s.s.ecc_error)
    {
        BDK_CSR_INIT(mdc_ecc_status, node, BDK_MDC_ECC_STATUS);
        if (mdc_ecc_status.s.dbe)
        {
            bdk_error("ECC double bit failure, Row 0x%x, Chain %d, Hub %d, Node %d\n",
                mdc_ecc_status.s.row, mdc_ecc_status.s.chain_id,
                mdc_ecc_status.s.hub_id, mdc_ecc_status.s.node_id);
        }
        if (mdc_ecc_status.s.dbe_plus)
            bdk_error("ECC other double bit failures occurred\n");
        if (mdc_ecc_status.s.sbe)
        {
            bdk_error("ECC single bit correction, Row 0x%x, Chain %d, Hub %d, Node %d\n",
                mdc_ecc_status.s.row, mdc_ecc_status.s.chain_id,
                mdc_ecc_status.s.hub_id, mdc_ecc_status.s.node_id);
        }
        if (mdc_ecc_status.s.sbe_plus)
            bdk_error("ECC other single bit corrections occurred\n");
        BDK_CSR_WRITE(node, BDK_MDC_INT_W1C, mdc_int_w1s.u);
    }

    // Check Read and Write NXM interrupts
    bdk_check_nxm_errors_cn9xxx(node);

    // DRAM ECC errors are separate from MDC ECC errors
    bdk_check_ecc_errors_cn9xxx(node);

    // Look for any DRAM parity errors
    bdk_check_parity_errors_cn9xxx(node);
}

// Generic Error Enable
void (*bdk_error_check)(bdk_node_t node) = NULL;
void bdk_error_enable(bdk_node_t node)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
    {
        enable_cn83xx(node);
        check_cn83xx(node);
        bdk_error_check = check_cn83xx;
    }
    else if (bdk_is_model(OCTEONTX_CN81XX))
    {
        enable_cn81xx(node);
        check_cn81xx(node);
        bdk_error_check = check_cn81xx;
    }
    else if (bdk_is_model(OCTEONTX_CN9XXX) && !bdk_is_platform(BDK_PLATFORM_EMULATOR))
    {
        enable_cn9xxx(node);
        check_cn9xxx(node);
        bdk_error_check = check_cn9xxx;
    }
    else
        bdk_error("Error reporting not implemented for this chip\n");
}
