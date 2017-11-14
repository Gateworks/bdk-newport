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
#include "libbdk-arch/bdk-csrs-l2c_cbc.h"
#include "libbdk-arch/bdk-csrs-l2c_tad.h"
#include "libbdk-arch/bdk-csrs-l2c_mci.h"
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-ocx.h"

/* It is questionable whether we want to report CCPI errors that are
   automatically fixed by the hardware. This controls if these are
   reported for CN88XX pass 2 and newr chips */
static int report_ccpi_recoverable_errors = 1;

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

#define EXTRACT(v, lsb, width) (((v) >> (lsb)) & ((1ull << (width)) - 1))

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

static void check_cn8xxx_l2c_mcis(bdk_node_t node, int limit)
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
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), cn88xxp1, rtgdbe);
        CHECK_CHIP_ERROR(BDK_L2C_TADX_INT_W1C(index), cn88xxp1, rtgsbe);
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
static void check_cn8xxx_lmc(bdk_node_t node, int index, int check_intf_en)
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
    CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, ddr_err);
    CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, dlcram_ded_err);
    CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, dlcram_sec_err);
    //CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, ded_err);
    //CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, sec_err);
    //CHECK_CHIP_ERROR(BDK_LMCX_INT(index), s, nxm_wr_err);

    if (c.s.nxm_wr_err) {
        BDK_CSR_INIT(nxm_fadr, node, BDK_LMCX_NXM_FADR(index));
        bdk_error("N%d.LMC%d: NXM_WR_ERR: %s at [0x%016lx]\n",
                  node, index, (nxm_fadr.cn8.nxm_type) ? "Write" : "Read",
                  (nxm_fadr.cn8.nxm_faddr | ((nxm_fadr.u >> 2) & (1UL << 37))));
        CLEAR_CHIP_ERROR(BDK_LMCX_INT(index), s, nxm_wr_err);
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
            snprintf(synstr, sizeof(synstr), "DED=%X", err_bits);
        } else { // must be just SEC, also extract the syndrome byte
            bdk_atomic_add64_nosync(&__bdk_dram_ecc_single_bit_errors[index], 1);
            err_type = "single";
            err_bits = c.cn8.sec_err;
            int i = err_bits;
            while ((i & 1) == 0) {syndrome >>= 8; i >>= 1; }
            syndrome &= 0xff;
            int bytebit = ecc_syndrome_to_bytebit[syndrome];
            if (bytebit != 0x00) {
                snprintf(synstr, sizeof(synstr), "BYTE %d.%d/%X",
                         ((bytebit >> 4) & 0x0f) - 1, bytebit & 0x0f, err_bits);
            } else {
                snprintf(synstr, sizeof(synstr), "SYND 0x%02lx/%X", syndrome, err_bits);
            }
        }
        uint32_t frow = fadr.s.frow & __bdk_dram_get_row_mask(node, index);
        uint32_t fcol = fadr.s.fcol & __bdk_dram_get_col_mask(node, index);
        uint64_t where = bdk_dram_address_construct_info(node, index, fadr.s.fdimm, fadr.s.fbunk,
                                                         fadr.s.fcid, fadr.s.fbank, frow, fcol);
        construct_phase_info(phasestr, fadr.s.fill_order, EXTRACT(fadr.s.fcol, 1, 3), err_bits);

        bdk_error("N%d.LMC%d: ECC %s (DIMM%d,Rank%d/%d,Bank%02d,Row 0x%05x,Col 0x%04x,%s,%s)[0x%011lx]\n",
                  node, index, err_type, fadr.s.fdimm, fadr.s.fbunk, fadr.s.fcid,
                  fadr.s.fbank, frow, fcol, phasestr, synstr, where);
    } /* if (c.s.ded_err || c.s.sec_err) */
}

static void check_cn88xx(bdk_node_t node)
{
    check_cn8xxx_l2c_cbcs(node, 4);
    check_cn8xxx_l2c_mcis(node, 4);
    check_cn8xxx_l2c_tads(node, 8);

    for (int index = 0; index < 4; index++) {
        /*
         * LMC0 and LMC1 are always enabled, but we cannot set their INTF_EN bits.
         * LMC2 and LMC3 may be disabled, so check their INTF_EN bits.
         */
        check_cn8xxx_lmc(node, index, (index >= 2));
    }

    BDK_CSR_INIT(l2c_oci_ctl, node, BDK_L2C_OCI_CTL);
    extern int __bdk_disable_ccpi_error_report;
    if ((l2c_oci_ctl.s.enaoci > 1) && !__bdk_disable_ccpi_error_report)
    {
        int loopback = 0;
        for (int link = 0; link < 3; link++)
        {
            BDK_CSR_INIT(com_linkx_ctl, node, BDK_OCX_COM_LINKX_CTL(link));
            loopback |= com_linkx_ctl.s.loopback;
        }

        /* Check CCPI errors */
        BDK_CSR_INIT(c, node, BDK_OCX_COM_INT);
        CHECK_CHIP_ERROR(BDK_OCX_COM_INT, s, io_badid);
        CHECK_CHIP_ERROR(BDK_OCX_COM_INT, s, mem_badid);
        CHECK_CHIP_ERROR(BDK_OCX_COM_INT, s, copr_badid);
        CHECK_CHIP_ERROR(BDK_OCX_COM_INT, s, win_req_badid);
        CHECK_CHIP_ERROR(BDK_OCX_COM_INT, s, win_req_tout);
        if (c.s.rx_lane && !loopback)
        {
            /* Check CCPI link errors */
            CLEAR_CHIP_ERROR(BDK_OCX_COM_INT, s, rx_lane);
            for (int lane=0; lane<24; lane++)
            {
                BDK_CSR_INIT(c, node, BDK_OCX_LNEX_INT(lane));
                if (report_ccpi_recoverable_errors)
                {
                    CLEAR_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, disp_err); /* Harmless and fires during init */
                    CHECK_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, bad_64b67b);
                    CHECK_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, crc32_err);
                }
                else
                {
                    CLEAR_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, disp_err);
                    CLEAR_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, bad_64b67b);
                    CLEAR_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, crc32_err);
                }
                CLEAR_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, stat_cnt_ovfl);
                CHECK_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, stat_msg);
                CHECK_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, dskew_fifo_ovfl);
                CHECK_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, scrm_sync_loss);
                CHECK_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, ukwn_cntl_word);
                CHECK_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, bdry_sync_loss);
                CHECK_CHIP_ERROR(BDK_OCX_LNEX_INT(lane), s, serdes_lock_loss);
            }
        }
        /* Check high level link errors */
        for (int link=0; link<3; link++)
        {
            BDK_CSR_INIT(c, node, BDK_OCX_COM_LINKX_INT(link));
            if (!loopback)
            {
                if (report_ccpi_recoverable_errors)
                {
                    CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, bad_word);
                }
                else
                {
                    CLEAR_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, bad_word);
                }
                CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, align_fail);
                CLEAR_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, align_done);
                CLEAR_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, up);
                CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, stop);
                if (c.s.blk_err)
                {
                    BDK_CSR_MODIFY(c, node, BDK_OCX_RLKX_BLK_ERR(link), c.s.count = 0);
                    //CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, blk_err);
                }
                CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, reinit);
            }
            CLEAR_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, lnk_data);
            CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, rxfifo_dbe);
            CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, rxfifo_sbe);
            CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, txfifo_dbe);
            CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, txfifo_sbe);
            CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, replay_dbe);
            CHECK_CHIP_ERROR(BDK_OCX_COM_LINKX_INT(link), s, replay_sbe);
        }
    }
}

static void enable_cn88xx(bdk_node_t node)
{
    /* Do nothing for now */
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

// Generic Error Enable
void (*bdk_error_check)(bdk_node_t node) = NULL;
void bdk_error_enable(bdk_node_t node)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
    {
        /* Require reporting of all CCPI errors on pass 1 as automatic
           recovery doesn't work */
        if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
            report_ccpi_recoverable_errors = 1;
        enable_cn88xx(node);
        check_cn88xx(node);
        bdk_error_check = check_cn88xx;
    }
    else if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
    {
        enable_cn83xx(node);
        check_cn83xx(node);
        bdk_error_check = check_cn83xx;
    }
    else if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
    {
        enable_cn81xx(node);
        check_cn81xx(node);
        bdk_error_check = check_cn81xx;
    }
    else
        bdk_error("Error reporting not implemented for this chip\n");
}
