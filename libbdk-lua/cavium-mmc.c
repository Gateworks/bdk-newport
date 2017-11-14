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
#include <unistd.h>
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-mio_emm.h"
#include "cavium-mmc.h"
#ifdef BDK_BUILD_HOST
    #include "utils/bdk-lua/octeon-remote.h"
    #define bdk_wait_usec(s) usleep(s)
#endif

/**
 *  Module for the eMMC/MMC/SD interface
 */

#define ULL unsigned long long
static uint64_t block_addressable_device;
static uint64_t card_is_sd = 0;
static uint64_t relative_address = 1;
static int show_debug = 0;


/**
 * print_cmd_status
 */
static void print_cmd_status(void)
{
    bdk_node_t node = bdk_numa_local();
    BDK_CSR_INIT(sts_reg, node, BDK_MIO_EMM_RSP_STS);
    BDK_CSR_INIT(rsp_lo, node, BDK_MIO_EMM_RSP_LO);
    BDK_CSR_INIT(rsp_hi, node, BDK_MIO_EMM_RSP_HI);

    printf("Command index = %d, command type = %d\n", sts_reg.s.cmd_idx, sts_reg.s.cmd_type);
    switch (sts_reg.s.rsp_type)
    {
        case 1:
            printf("Response type 1, card status = 0x%08x\n", (uint32_t) ((rsp_lo.u >>8) & 0xFFFFFFFF));
            break;
        case 2:
            printf("Response type 2, rsp_hi-bits = 0x%016llx, rsp_lo-bits = 0x%016llx\n", (ULL)rsp_hi.u, (ULL)rsp_lo.u);
            break;
        case 3:
            printf("Response type 3, OCR Register = 0x%08x\n", (uint32_t) ((rsp_lo.u >>8) & 0xFFFFFFFF));
            break;
        case 4:
            printf("Response type 4, RCA = 0x%llx, status =0x%llx, reg. addr. = 0x%llx, reg. contents = 0x%llx\n",
                   (ULL)((rsp_lo.u >> 24) & 0xffff), (ULL)((rsp_lo.u >> 23) & 0x1), (ULL)((rsp_lo.u >> 16) & 0x7F), (ULL)((rsp_lo.u >> 8) & 0xFF));
            break;
        case 5:
            printf("Response type 5, RCA = 0x%llx, status =0x%llx, reg. addr. = 0x%llx\n",
                   (ULL)((rsp_lo.u >> 24) & 0xffff), (ULL)((rsp_lo.u >> 23) & 0x1), (ULL)((rsp_lo.u >> 16) & 0x7F));
            break;

        default:
            printf("Unknown response type, rsp_sts. reg. = 0x%llx\n", (ULL)sts_reg.u);
    }
}


/**
 * mmc_cmd
 *
 * @param cmd
 * @param arg
 * @param busid
 * @param dbuf
 * @param rtype_xor
 * @param ctype_xor
 * @param offset
 *
 * @return
 */
static bdk_mio_emm_rsp_sts_t mmc_cmd(uint64_t cmd, uint64_t arg, uint64_t busid, uint64_t dbuf, uint64_t rtype_xor, uint64_t ctype_xor, uint64_t offset)
{
    bdk_node_t node = bdk_numa_local();
    BDK_CSR_DEFINE(cmd_reg, BDK_MIO_EMM_CMD);
    cmd_reg.u = 0;
    cmd_reg.s.bus_id = busid;
    cmd_reg.s.cmd_idx = cmd;
    cmd_reg.s.arg = arg;
    cmd_reg.s.dbuf = dbuf;
    cmd_reg.s.rtype_xor = rtype_xor;
    cmd_reg.s.ctype_xor = ctype_xor;
    cmd_reg.s.offset = offset;
    cmd_reg.s.cmd_val = 1;

    BDK_CSR_WRITE(node, BDK_MIO_EMM_CMD, cmd_reg.u);
    BDK_CSR_INIT(sts_reg, node, BDK_MIO_EMM_RSP_STS);

    /* We use loops ever 1ms here instead of a wall time based timeout so
        code isn't needed to keep track of accurate time on both host and
        target */
    int wait_loops = 1000;
    do
    {
        bdk_wait_usec(1000);
        sts_reg.u = BDK_CSR_READ(node, BDK_MIO_EMM_RSP_STS);
        if (--wait_loops <= 0)
        {
            if (show_debug)
                printf("No response, timeout.\n");
            return sts_reg;
        }
    } while (sts_reg.s.cmd_done != 1);

    if (sts_reg.s.rsp_val || sts_reg.s.stp_val)
    {
        int cmd_error = 0;
        if (sts_reg.s.rsp_bad_sts || sts_reg.s.stp_bad_sts)
        {
            BDK_CSR_INIT(rsp_lo, node, BDK_MIO_EMM_RSP_LO);
            if (show_debug)
                printf("Response bad status, cmd response = 0x%08x\n", (uint32_t) ((rsp_lo.u >>8) & 0xFFFFFFFF));
            cmd_error++;
        }
        if (sts_reg.s.rsp_crc_err || sts_reg.s.stp_crc_err)
        {
            if (show_debug)
                printf("Response CRC error.\n");
            cmd_error++;
        }
        if (sts_reg.s.rsp_timeout || sts_reg.s.stp_timeout)
        {
            if (show_debug)
                printf("Response timeout error.\n");
            cmd_error++;
        }
        if (sts_reg.s.blk_crc_err)
        {
            if (show_debug)
                printf("Read/write block CRC error.\n");
            cmd_error++;
        }
        if (sts_reg.s.blk_timeout)
        {
            if (show_debug)
                printf("Read/write block timeout error.\n");
            cmd_error++;
        }
        if (sts_reg.s.dbuf_err)
        {
            if (show_debug)
                printf("Dbuf error, no free buffer\n");
            cmd_error++;
        }
        if (cmd_error)
        {
            if (show_debug)
                print_cmd_status();
            return sts_reg;
        }
    }
    else
    {
        if ((sts_reg.s.cmd_idx != MMC_CMD_GO_IDLE_STATE) &&
            (sts_reg.s.cmd_idx != MMC_CMD_SET_DSR) &&
            (sts_reg.s.cmd_idx != MMC_CMD_GO_INACTIVE_STATE))
        {
            if (show_debug)
            {
                cmd_reg.u = BDK_CSR_READ(node, BDK_MIO_EMM_CMD);
                sts_reg.u = BDK_CSR_READ(node, BDK_MIO_EMM_RSP_STS);
                BDK_CSR_INIT(rsp_lo, node, BDK_MIO_EMM_RSP_LO);
                BDK_CSR_INIT(rsp_hi, node, BDK_MIO_EMM_RSP_HI);
                printf("No valid response\n");
                printf("mio_emm_cmd     = 0x%016llx\n", (ULL)cmd_reg.u);
                printf("mio_emm_rsp_sts = 0x%016llx\n", (ULL)sts_reg.u);
                printf("mio_emm_rsp_lo  = 0x%016llx\n", (ULL)rsp_lo.u);
                printf("mio_emm_rsp_hi  = 0x%016llx\n", (ULL)rsp_hi.u);
            }
            return sts_reg;
        }
    }

    sts_reg.u = 0;
    return sts_reg;
}


/**
 * print_ocr_reg
 *
 * @param ocr_reg
 */
static void print_ocr_reg(ocr_register_t ocr_reg)
{
    printf("\nOCR Register fields --\n");
    printf("Volts 1.70 - 1.95 0x%04x\n", ocr_reg.s.volts_1_7__1_95);
    printf("Volts 2.0 - 2.6   0x%04x\n", ocr_reg.s.volts_2_0__2_6);
    printf("Volts 2.7 - 3.6   0x%04x\n", ocr_reg.s.volts_2_7__3_6);
    printf("Access Mode       0x%04x\n", ocr_reg.s.access_mode);
}


/**
 * print_csd_reg
 *
 * @param reg_hi
 * @param reg_lo
 */
static void print_csd_reg(uint64_t reg_hi, uint64_t reg_lo)
{
    if (card_is_sd)
    {
        sd_csd_register_hi_t  sd_csd_reg_hi;
        sd_csd_register_lo_t  sd_csd_reg_lo;
        sd_csd_reg_hi.u = reg_hi;
        sd_csd_reg_lo.u = reg_lo;
        printf("\nCSD Register fields --\n");
        printf("csd_structure       = 0x%x\n", sd_csd_reg_hi.s.csd_structure);
        printf("reserved_120_125    = 0x%x\n", sd_csd_reg_hi.s.reserved_120_125);
        printf("taac                = 0x%x\n", sd_csd_reg_hi.s.taac);
        printf("nsac                = 0x%x\n", sd_csd_reg_hi.s.nsac);
        printf("tran_speed          = 0x%x\n", sd_csd_reg_hi.s.tran_speed);
        printf("ccc                 = 0x%x\n", sd_csd_reg_hi.s.ccc);
        printf("read_bl_len         = 0x%x\n", sd_csd_reg_hi.s.read_bl_len);
        printf("read_bl_partial     = 0x%x\n", sd_csd_reg_hi.s.read_bl_partial);
        printf("write_blk_misalign  = 0x%x\n", sd_csd_reg_hi.s.write_blk_misalign);
        printf("read_blk_misalign   = 0x%x\n", sd_csd_reg_hi.s.read_blk_misalign);
        printf("dsr_imp             = 0x%x\n", sd_csd_reg_hi.s.dsr_imp);
        printf("reserved_74_75      = 0x%x\n", sd_csd_reg_hi.s.reserved_74_75);
        printf("c_size              = 0x%x\n", (sd_csd_reg_hi.s.c_size << 2) + sd_csd_reg_lo.s.c_size);
        printf("vdd_r_curr_min      = 0x%x\n", sd_csd_reg_lo.s.vdd_r_curr_min);
        printf("vdd_r_curr_max      = 0x%x\n", sd_csd_reg_lo.s.vdd_r_curr_max);
        printf("vdd_w_curr_min      = 0x%x\n", sd_csd_reg_lo.s.vdd_w_curr_min);
        printf("vdd_w_curr_max      = 0x%x\n", sd_csd_reg_lo.s.vdd_w_curr_max);
        printf("c_size_mult         = 0x%x\n", sd_csd_reg_lo.s.c_size_mult);
        printf("erase_blk_en        = 0x%x\n", sd_csd_reg_lo.s.erase_blk_en);
        printf("wp_grp_size         = 0x%x\n", sd_csd_reg_lo.s.wp_grp_size);
        printf("wp_grp_enable       = 0x%x\n", sd_csd_reg_lo.s.wp_grp_enable);
        printf("reserved_29_30      = 0x%x\n", sd_csd_reg_lo.s.reserved_29_30);
        printf("r2w_factor          = 0x%x\n", sd_csd_reg_lo.s.r2w_factor);
        printf("write_bl_len        = 0x%x\n", sd_csd_reg_lo.s.write_bl_len);
        printf("write_bl_partial    = 0x%x\n", sd_csd_reg_lo.s.write_bl_partial);
        printf("reserved_16_20      = 0x%x\n", sd_csd_reg_lo.s.reserved_16_20);
        printf("file_format_grp     = 0x%x\n", sd_csd_reg_lo.s.file_format_grp);
        printf("copy                = 0x%x\n", sd_csd_reg_lo.s.copy);
        printf("perm_write_protect  = 0x%x\n", sd_csd_reg_lo.s.perm_write_protect);
        printf("tmp_write_protect   = 0x%x\n", sd_csd_reg_lo.s.tmp_write_protect);
        printf("file_format         = 0x%x\n", sd_csd_reg_lo.s.file_format);
        printf("reserved_8_9        = 0x%x\n", sd_csd_reg_lo.s.reserved_8_9);
        printf("crc                 = 0x%x\n", sd_csd_reg_lo.s.crc);
        printf("always_one          = 0x%x\n", sd_csd_reg_lo.s.always_one);
    }
    else
    {
        mmc_csd_register_hi_t mmc_csd_reg_hi;
        mmc_csd_register_lo_t mmc_csd_reg_lo;
        mmc_csd_reg_hi.u = reg_hi;
        mmc_csd_reg_lo.u = reg_lo;
        printf("\nCSD Register fields --\n");
        printf("csd_structure       = 0x%x\n", mmc_csd_reg_hi.s.csd_structure);
        printf("spec_vers           = 0x%x\n", mmc_csd_reg_hi.s.spec_vers);
        printf("reserved_120_121    = 0x%x\n", mmc_csd_reg_hi.s.reserved_120_121);
        printf("taac                = 0x%x\n", mmc_csd_reg_hi.s.taac);
        printf("nsac                = 0x%x\n", mmc_csd_reg_hi.s.nsac);
        printf("tran_speed          = 0x%x\n", mmc_csd_reg_hi.s.tran_speed);
        printf("ccc                 = 0x%x\n", mmc_csd_reg_hi.s.ccc);
        printf("read_bl_len         = 0x%x\n", mmc_csd_reg_hi.s.read_bl_len);
        printf("read_bl_partial     = 0x%x\n", mmc_csd_reg_hi.s.read_bl_partial);
        printf("write_blk_misalign  = 0x%x\n", mmc_csd_reg_hi.s.write_blk_misalign);
        printf("read_blk_misalign   = 0x%x\n", mmc_csd_reg_hi.s.read_blk_misalign);
        printf("dsr_imp             = 0x%x\n", mmc_csd_reg_hi.s.dsr_imp);
        printf("reserved_74_75      = 0x%x\n", mmc_csd_reg_hi.s.reserved_74_75);
        printf("c_size              = 0x%x\n", (mmc_csd_reg_hi.s.c_size << 2) + mmc_csd_reg_lo.s.c_size);
        printf("vdd_r_curr_min      = 0x%x\n", mmc_csd_reg_lo.s.vdd_r_curr_min);
        printf("vdd_r_curr_max      = 0x%x\n", mmc_csd_reg_lo.s.vdd_r_curr_max);
        printf("vdd_w_curr_min      = 0x%x\n", mmc_csd_reg_lo.s.vdd_w_curr_min);
        printf("vdd_w_curr_max      = 0x%x\n", mmc_csd_reg_lo.s.vdd_w_curr_max);
        printf("c_size_mult         = 0x%x\n", mmc_csd_reg_lo.s.c_size_mult);
        printf("erase_grp_size      = 0x%x\n", mmc_csd_reg_lo.s.erase_grp_size);
        printf("erase_grp_mult      = 0x%x\n", mmc_csd_reg_lo.s.erase_grp_mult);
        printf("wp_grp_size         = 0x%x\n", mmc_csd_reg_lo.s.wp_grp_size);
        printf("wp_grp_enable       = 0x%x\n", mmc_csd_reg_lo.s.wp_grp_enable);
        printf("default_ecc         = 0x%x\n", mmc_csd_reg_lo.s.default_ecc);
        printf("r2w_factor          = 0x%x\n", mmc_csd_reg_lo.s.r2w_factor);
        printf("write_bl_len        = 0x%x\n", mmc_csd_reg_lo.s.write_bl_len);
        printf("write_bl_partial    = 0x%x\n", mmc_csd_reg_lo.s.write_bl_partial);
        printf("reserved_17_20      = 0x%x\n", mmc_csd_reg_lo.s.reserved_17_20);
        printf("content_prot_app    = 0x%x\n", mmc_csd_reg_lo.s.content_prot_app);
        printf("file_format_grp     = 0x%x\n", mmc_csd_reg_lo.s.file_format_grp);
        printf("copy                = 0x%x\n", mmc_csd_reg_lo.s.copy);
        printf("perm_write_protect  = 0x%x\n", mmc_csd_reg_lo.s.perm_write_protect);
        printf("tmp_write_protect   = 0x%x\n", mmc_csd_reg_lo.s.tmp_write_protect);
        printf("file_format         = 0x%x\n", mmc_csd_reg_lo.s.file_format);
        printf("crc                 = 0x%x\n", mmc_csd_reg_lo.s.crc);
        printf("always_one          = 0x%x\n", mmc_csd_reg_lo.s.always_one);
    }
}


/**
 * Setup the eMMC controller watchdog to 100ms
 */
static void wdog_default()
{
    bdk_node_t node = bdk_numa_local();
    BDK_CSR_INIT(rst_boot, node, BDK_RST_BOOT);
    BDK_CSR_INIT(mode_reg, node, BDK_MIO_EMM_MODEX(0));
    uint64_t sclk = 50000000ull * rst_boot.s.pnr_mul;
    uint64_t wdog_value = sclk / 10 / (mode_reg.s.clk_hi + mode_reg.s.clk_lo);
    BDK_CSR_WRITE(node, BDK_MIO_EMM_WDOG, wdog_value);
}


/**
 * Macro to make it easier to submit a command and fail on bad status
 */
#define MMC_CMD_OR_ERROR(L, cmd, arg, busid, dbuf, rtype_xor, ctype_xor, offset)    \
do {                                                                                \
    bdk_mio_emm_rsp_sts_t status = mmc_cmd(cmd, arg, busid, dbuf, rtype_xor, ctype_xor, offset); \
    if(status.u)                                                                  \
        return luaL_error(L, "eMMC: Command " #cmd " failed");                            \
} while (0)


/**
 * Initialize a eMMC/MMC/SD for use
 *
 * @param L
 *
 * @return
 */
static int mmc_init(lua_State *L)
{
    bdk_node_t node = bdk_numa_local();
    show_debug = lua_toboolean(L, 1);
    bdk_mio_emm_rsp_sts_t status;
    ocr_register_t ocr_reg;

    // Disable bus 1, causes the clocking to reset to the default
    BDK_CSR_WRITE(node, BDK_MIO_EMM_CFG, 0x0);
    bdk_wait_usec(200000);

    // Disable buses and reset device using GPIO8
    BDK_CSR_WRITE(node, BDK_MIO_EMM_CFG, 0x0);
    BDK_CSR_MODIFY(c, node, BDK_GPIO_BIT_CFGX(8),
                   c.s.tx_oe = 1);
    bdk_wait_usec(1000);

    BDK_CSR_WRITE(node, BDK_GPIO_TX_CLR, 1<<8);

    bdk_wait_usec(200000);

    BDK_CSR_WRITE(node, BDK_GPIO_TX_SET, 1<<8);

    bdk_wait_usec(2000);

    // Enable bus 1
    BDK_CSR_WRITE(node, BDK_MIO_EMM_CFG, 0x1);

    // Assume card is eMMC
    card_is_sd = 0;

    // Reset the status mask reg., boot will change it
    BDK_CSR_WRITE(node, BDK_MIO_EMM_STS_MASK, 0xE4390080);

    bdk_wait_usec(2000);

    // Setup watchdog timer
    wdog_default();

    //Reset the device
    MMC_CMD_OR_ERROR(L, MMC_CMD_GO_IDLE_STATE, 0, 0, 0, 0, 0, 0);

    // Do a CMD SEND_EXT_CSD (8)
    status = mmc_cmd(MMC_CMD_SEND_EXT_CSD, 0x000001AA, 0, 0, 2, 1, 0);
    if (status.u == 0x0)
    {
        // We may have an SD card, as it should respond
        BDK_CSR_INIT(rsp_lo, node, BDK_MIO_EMM_RSP_LO);
        if (((rsp_lo.u >>8) & 0xFFFFFFFFFF) != 0x08000001AA)
            return luaL_error(L, "eMMC: Unexpected response from MMC_CMD_SEND_EXT_CSD");
        // Send a ACMD 41
        do
        {
            status = mmc_cmd(MMC_CMD_APP_CMD, 0, 0, 0, 0, 0, 0);
            if (status.u == 0x0)
            {
                status = mmc_cmd(41, 0x40ff8000, 0, 0, 3, 0, 0);
                if (status.u)
                    return luaL_error(L, "eMMC: Failed to recognize card");
                card_is_sd = 1;
            }
            else
            {
                // Failed, not sure whats out there
                return luaL_error(L, "eMMC: Failed to recognize card");
            }

            ocr_reg.u32 = (uint32_t) ((BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO) >>8) &0xFFFFFFFF);
        } while (ocr_reg.s.done_bit == 0x0);
        // Success, we have an SD card version 2.0 or above, fall through
    }
    else
    {
        // Card could be an SD version less than 2.0 or an MMC card
        // Send a ACMD 41
        do
        {
            status = mmc_cmd(MMC_CMD_APP_CMD, 0, 0, 0, 0, 0, 0);
            if (status.u == 0x0)
            {
                status = mmc_cmd(41, 0x40ff8000, 0, 0, 3, 0, 0);
                if (status.u)
                {
                    // Have an SD card, version less than 2.0
                    // fall through, exit the loop
                    card_is_sd = 1;
                    break;
                }
            }
            else
            {
                // APP_CMD command failed
                break;
            }
            ocr_reg.u32 = (uint32_t) ((BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO) >>8) &0xFFFFFFFF);
        } while (ocr_reg.s.done_bit == 0x0);

        if (status.u == 0x0)
        {
            // Success, we have an SD card version 2.0 or less
            card_is_sd = 1;
        }
        else
        {
            //Have an MMC card, do a command 1
            //Select the initial operating conditions
            do
            {
                MMC_CMD_OR_ERROR(L, MMC_CMD_SEND_OP_COND, 0x40ff8000, 0, 0, 0, 0, 0);
                ocr_reg.u32 = (uint32_t) ((BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO) >>8) &0xFFFFFFFF);
            } while (ocr_reg.s.done_bit == 0x0);
        }
    }
    // Global to determine if the card is block or byte addressable.
    block_addressable_device = ocr_reg.s.access_mode;
    if (show_debug)
        print_ocr_reg(ocr_reg);

    // Get card identification
    MMC_CMD_OR_ERROR(L, MMC_CMD_ALL_SEND_CID, 0, 0, 0, 0, 0, 0);

    if (card_is_sd)
    {
        // For SD, read the relative address from the card
        // CMD3 response for SD cards is R6 format, similar to R1, but different
        // Need to chane the mio_EMM_STS_MASK register so we don't get a response status error
        BDK_CSR_INIT(sts_mask, node, BDK_MIO_EMM_STS_MASK);
        BDK_CSR_WRITE(node, BDK_MIO_EMM_STS_MASK, 0xE000);
        status = mmc_cmd(MMC_CMD_SET_RELATIVE_ADDR, 0, 0, 0, 0, 0, 0);
        BDK_CSR_WRITE(node, BDK_MIO_EMM_STS_MASK, sts_mask.u);
        if (status.u)
            return luaL_error(L, "eMMC: Command MMC_CMD_SET_RELATIVE_ADDR failed");
        relative_address = ((BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO) >>24) &0xFFFF);
    }
    else
    {
        // For MMC, set card relative address
        relative_address = 1; //Default for MMC cards
        MMC_CMD_OR_ERROR(L, MMC_CMD_SET_RELATIVE_ADDR, relative_address << 16, 0, 0, 0, 0, 0);
    }

    BDK_CSR_WRITE(node, BDK_MIO_EMM_RCA, relative_address);

    // Get CSD Register
    MMC_CMD_OR_ERROR(L, MMC_CMD_SEND_CSD, relative_address << 16, 0, 0, 0, 0, 0);
    mmc_csd_register_lo_t csd_reg_lo;
    csd_reg_lo.u = (BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO));
    mmc_csd_register_hi_t csd_reg_hi;
    csd_reg_hi.u = (BDK_CSR_READ(node, BDK_MIO_EMM_RSP_HI));
    uint64_t mmc_capacity;
    if (card_is_sd)
    {
        sd_csd_register_hi_t  sd_csd_reg_hi;
        sd_csd_register_lo_t  sd_csd_reg_lo;
        sd_csd_reg_hi.u = csd_reg_hi.u;
        sd_csd_reg_lo.u = csd_reg_lo.u;
        mmc_capacity = (sd_csd_reg_hi.s.c_size << 2) + sd_csd_reg_lo.s.c_size;
        mmc_capacity = (mmc_capacity + 1) << (sd_csd_reg_lo.s.c_size_mult + 2);
        mmc_capacity *= 1<<sd_csd_reg_hi.s.read_bl_len;
    }
    else
    {
        mmc_csd_register_hi_t mmc_csd_reg_hi;
        mmc_csd_register_lo_t mmc_csd_reg_lo;
        mmc_csd_reg_hi.u = csd_reg_hi.u;
        mmc_csd_reg_lo.u = csd_reg_lo.u;
        mmc_capacity = (mmc_csd_reg_hi.s.c_size << 2) + mmc_csd_reg_lo.s.c_size;
        mmc_capacity = (mmc_capacity + 1) << (mmc_csd_reg_lo.s.c_size_mult + 2);
        mmc_capacity *= 1<<mmc_csd_reg_hi.s.read_bl_len;
    }

    if (show_debug)
        print_csd_reg(csd_reg_hi.u, csd_reg_lo.u);

    // Select Card
    MMC_CMD_OR_ERROR(L, MMC_CMD_SELECT_CARD, relative_address << 16 , 0, 0, 0, 0, 0);
    // Send Card Status
    MMC_CMD_OR_ERROR(L, MMC_CMD_SEND_STATUS, relative_address << 16 , 0, 0, 0, 0, 0);

    // Return the card size in bytes
    lua_pushnumber(L, mmc_capacity);
    return 1;
}


/**
 * Read data from the eMMC/MMC/SD
 *
 * @param L
 *
 * @return
 */
static int mmc_read(lua_State *L)
{
    bdk_node_t node = bdk_numa_local();
    /* Check the first parameter, the address to read from */
    uint64_t address = luaL_checklong(L, 1);
    if (address > (1ull<<40))
        return luaL_error(L, "Illegal read address");
    if (address & 511)
        return luaL_error(L, "Read address must be a multiple of 512");

    /* Check the second parameter, the number of bytes to read */
    uint64_t size = luaL_checklong(L, 2);
    if ((size <= 0) || (size > (1ull<<30)))
        return luaL_error(L, "Illegal read size");
    if (size & 511)
        return luaL_error(L, "Read size must be a multiple of 512");

    /* Allocate an output buffer for the response */
    luaL_Buffer output;
    luaL_buffinit(L, &output);

    /* Read until we've read all data */
    while (size > 0)
    {
        /* Send the read command */
        BDK_CSR_DEFINE(status, BDK_MIO_EMM_RSP_STS);
        status = mmc_cmd(MMC_CMD_READ_SINGLE_BLOCK, (block_addressable_device) ? address/512 : address, 0, 0, 0, 0, 0);
        if (status.u)
            return luaL_error(L, "eMMC: Read single block failed");

        /* Set our location in the internal buffer */
        BDK_CSR_DEFINE(buf_idx, BDK_MIO_EMM_BUF_IDX);
        buf_idx.u = 0;
        buf_idx.s.inc = 1;
        buf_idx.s.buf_num = 0;
        buf_idx.s.offset = 0;
        BDK_CSR_WRITE(node, BDK_MIO_EMM_BUF_IDX, buf_idx.u);

        /* Read out the data block and add it to the output buffer */
        for (int i=0; i<512/8; i++)
        {
            uint64_t data = bdk_be64_to_cpu(BDK_CSR_READ(node, BDK_MIO_EMM_BUF_DAT));
            luaL_addlstring(&output, (const char*)&data, 8);
        }
        /* Increment to the next position and adjust the size left */
        address += 512;
        size -= 512;
    }
    /* Return the result as a Lua string */
    luaL_pushresult(&output);
    return 1;
}


/**
 * Write data to the eMMC/MMC/SD
 *
 * @param L
 *
 * @return
 */
static int mmc_write(lua_State *L)
{
    bdk_node_t node = bdk_numa_local();
    /* Check the first parameter, the address to write to */
    uint64_t address = luaL_checklong(L, 1);
    if (address > (1ull<<40))
        return luaL_error(L, "Illegal write address");
    if (address & 511)
        return luaL_error(L, "Write address must be a multiple of 512");

    /* Check the second parameter, the data to write */
    size_t data_len = 0;
    const char *data = luaL_checklstring(L, 2, &data_len);
    if (data_len > (1ull<<30))
        return luaL_error(L, "Illegal write size");
    if (data_len & 511)
        return luaL_error(L, "Write size must be a multiple of 512");

    /* Write until no more data */
    while (data_len > 0)
    {
        /* Set our location in the internal buffer */
        BDK_CSR_DEFINE(buf_idx, BDK_MIO_EMM_BUF_IDX);
        buf_idx.u = 0;
        buf_idx.s.inc = 1;
        buf_idx.s.buf_num = 0;
        buf_idx.s.offset = 0;
        BDK_CSR_WRITE(node, BDK_MIO_EMM_BUF_IDX, buf_idx.u);

        /* Fill the internal buffer */
        for (int i=0; i<512/8; i++)
        {
            BDK_CSR_WRITE(node, BDK_MIO_EMM_BUF_DAT, bdk_cpu_to_be64(*(uint64_t*)data));
            data += 8;
        }

        /* Write single block */
        BDK_CSR_DEFINE(status, BDK_MIO_EMM_RSP_STS);
        status = mmc_cmd(MMC_CMD_WRITE_BLOCK, (block_addressable_device) ? address/512 : address, 0, 0, 0, 0, 0);
        if (status.u)
            return luaL_error(L, "eMMC: Write single block failed");
        data_len -= 512;
    }
    return 0;
}


/**
 * Register the eMMC/MMC/SD functions into a table on the Lua
 * stack under the module name "mmc".
 *
 * @param L
 */
void register_cavium_mmc(lua_State *L)
{
    lua_newtable(L);
    lua_pushcfunction(L, mmc_init);
    lua_setfield(L, -2, "init");
    lua_pushcfunction(L, mmc_read);
    lua_setfield(L, -2, "read");
    lua_pushcfunction(L, mmc_write);
    lua_setfield(L, -2, "write");
    lua_setfield(L, -2, "mmc");
}

