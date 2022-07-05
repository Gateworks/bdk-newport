/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-mio_emm.h"

// Basic definitions for the eMMC interface

#ifndef BDK_MMC_CLOCK_HZ
#define BDK_MMC_CLOCK_HZ 26000000
#endif
#define BDK_MMC_MIN_CLOCK_HZ 400000

/* Some large devices (32GB Samsung EVO) have shown timeouts with a watchdog of
   500ms. The 750ms values is to give a 50% margin */
#define BDK_MMC_WATCHDOG 750 /* In milliseconds */
#define MMC_TIMEOUT_SHORT       20      /* in ms */
#define MMC_TIMEOUT_LONG        1000
#define MMC_TIMEOUT_ERASE       10000

// Basic Commands
#define MMC_CMD_GO_IDLE_STATE		0
#define MMC_CMD_SEND_OP_COND		1
#define MMC_CMD_ALL_SEND_CID		2
#define MMC_CMD_SET_RELATIVE_ADDR	3
#define MMC_CMD_SET_DSR			4
#define MMC_CMD_SLEEP_AWAKE             5
#define MMC_CMD_SWITCH			6
#define MMC_CMD_SELECT_CARD		7 // also DESELECT_CARD
#define MMC_CMD_SEND_EXT_CSD		8
#define MMC_CMD_SEND_CSD		9
#define MMC_CMD_SEND_CID		10
#define MMC_CMD_ERAD_DAT_UNTIL_STOP     11
#define MMC_CMD_STOP_TRANSMISSION	12
#define MMC_CMD_SEND_STATUS		13
#define MMC_CMD_BUSTEST_R               14
#define MMC_CMD_GO_INACTIVE_STATE       15
#define MMC_CMD_BUSTEST_W               19

// Block-oriented Read Commands
#define MMC_CMD_SET_BLOCKLEN		16
#define MMC_CMD_READ_SINGLE_BLOCK	17
#define MMC_CMD_READ_MULTIPLE_BLOCK	18

// Stream Write Commands
#define MMC_CMD_WRITE_ADT_UNTIL_STOP    20

//Block-oriented Write Commands
#define MMC_CMD_SET_BLOCK_COUNT         23
#define MMC_CMD_WRITE_BLOCK             24
#define MMC_CMD_WRITE_MULTIPLE_BLOCK	25
#define MMC_CMD_PROGRAM_CID             26
#define MMC_CMD_PROGRAM_CIS             27

// Block-oriented write protection commands
#define MMC_CMD_SET_WRITE_PROT          28
#define MMC_CMD_CLR_WRITE_PROT          29
#define MMC_CMD_SEND_WRITE_PROT         30
#define MMC_CMD_SEND_WRITE_PROT_TYPE    31

// Erase Commands
#define MMC_CMD_ERASE_GROUP_START       35
#define MMC_CMD_ERASE_GROUP_END         36
#define MMC_CMD_ERASE                   38

//I/O Mode Commands
#define MMC_CMD_FAST_IO                 39
#define MMC_CMD_GO_IRQ_STATE            40
#define MMC_CMD_RES_41                  41

// Lock Card Commands
#define MMC_CMD_LOCK_UNLOCK             42

// Application-specific Commands
#define MMC_CMD_APP_CMD                 55
#define MMC_CMD_GEN_CMD			56


typedef union ocr_register
{
    uint32_t u32;

    struct ocr_register_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN

        uint32_t done_bit        :1 ;
        uint32_t access_mode     :2 ;
        uint32_t reserved_24_28  :5 ;
        uint32_t volts_2_7__3_6  :9 ;
        uint32_t volts_2_0__2_6  :7 ;
        uint32_t volts_1_7__1_95 :1 ;
        uint32_t reserved_0_6    :7 ;
#else
        uint32_t reserved_0_6    :7 ;
        uint32_t volts_1_7__1_95 :1 ;
        uint32_t volts_2_0__2_6  :7 ;
        uint32_t volts_2_7__3_6  :9 ;
        uint32_t reserved_24_28  :5 ;
        uint32_t access_mode     :2 ;
        uint32_t done_bit        :1 ;
#endif
    } s;
} ocr_register_t;

typedef union mmc_csd_register_hi
{
	uint64_t u;

    struct mmc_csd_register_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN

         uint64_t csd_structure      :2 ;
         uint64_t spec_vers          :4 ;
         uint64_t reserved_120_121   :2 ;
         uint64_t taac               :8 ;
         uint64_t nsac               :8 ;
         uint64_t tran_speed         :8 ;
         uint64_t ccc                :12 ;
         uint64_t read_bl_len        :4 ;
         uint64_t read_bl_partial    :1 ;
         uint64_t write_blk_misalign :1 ;
         uint64_t read_blk_misalign  :1 ;
         uint64_t dsr_imp            :1 ;
         uint64_t reserved_74_75     :2 ;
         uint64_t c_size             :10 ;

#else
         uint64_t c_size             :10 ;
         uint64_t reserved_74_75     :2 ;
         uint64_t dsr_imp            :1 ;
         uint64_t read_blk_misalign  :1 ;
         uint64_t write_blk_misalign :1 ;
         uint64_t read_bl_partial    :1 ;
         uint64_t read_bl_len        :4 ;
         uint64_t ccc                :12 ;
         uint64_t tran_speed         :8 ;
         uint64_t nsac               :8 ;
         uint64_t taac               :8 ;
         uint64_t reserved_120_121   :2 ;
         uint64_t spec_vers          :4 ;
         uint64_t csd_structure      :2 ;
#endif
    } s;
} mmc_csd_register_hi_t;


typedef union mmc_csd_register_lo
{
	uint64_t u;

    struct mmc_csd_register_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN

         uint64_t c_size             :2 ;
         uint64_t vdd_r_curr_min     :3 ;
         uint64_t vdd_r_curr_max     :3 ;
         uint64_t vdd_w_curr_min     :3 ;
         uint64_t vdd_w_curr_max     :3 ;
         uint64_t c_size_mult        :3 ;
         uint64_t erase_grp_size     :5 ;
         uint64_t erase_grp_mult     :5 ;
         uint64_t wp_grp_size        :5 ;
         uint64_t wp_grp_enable      :1 ;
         uint64_t default_ecc        :2 ;
         uint64_t r2w_factor         :3 ;
         uint64_t write_bl_len       :4 ;
         uint64_t write_bl_partial   :1 ;
         uint64_t reserved_17_20     :4 ;
         uint64_t content_prot_app   :1 ;
         uint64_t file_format_grp    :1 ;
         uint64_t copy               :1 ;
         uint64_t perm_write_protect :1 ;
         uint64_t tmp_write_protect  :1 ;
         uint64_t file_format        :2 ;
         uint64_t ecc                :2 ;
         uint64_t crc                :7 ;
         uint64_t always_one         :1 ;
#else
         uint64_t always_one         :1 ;
         uint64_t crc                :7 ;
         uint64_t ecc                :2 ;
         uint64_t file_format        :2 ;
         uint64_t tmp_write_protect  :1 ;
         uint64_t perm_write_protect :1 ;
         uint64_t copy               :1 ;
         uint64_t file_format_grp    :1 ;
         uint64_t content_prot_app   :1 ;
         uint64_t reserved_17_20     :4 ;
         uint64_t write_bl_partial   :1 ;
         uint64_t write_bl_len       :4 ;
         uint64_t r2w_factor         :3 ;
         uint64_t default_ecc        :2 ;
         uint64_t wp_grp_enable      :1 ;
         uint64_t wp_grp_size        :5 ;
         uint64_t erase_grp_mult     :5 ;
         uint64_t erase_grp_size     :5 ;
         uint64_t c_size_mult        :3 ;
         uint64_t vdd_w_curr_max     :3 ;
         uint64_t vdd_w_curr_min     :3 ;
         uint64_t vdd_r_curr_max     :3 ;
         uint64_t vdd_r_curr_min     :3 ;
         uint64_t c_size             :2 ;
#endif
    } s;
} mmc_csd_register_lo_t;


typedef union sd_csd_register_hi
{
	uint64_t u;

    struct sd_csd_register_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN

         uint64_t csd_structure      :2 ;
         uint64_t reserved_120_125   :6 ;
         uint64_t taac               :8 ;
         uint64_t nsac               :8 ;
         uint64_t tran_speed         :8 ;
         uint64_t ccc                :12 ;
         uint64_t read_bl_len        :4 ;
         uint64_t read_bl_partial    :1 ;
         uint64_t write_blk_misalign :1 ;
         uint64_t read_blk_misalign  :1 ;
         uint64_t dsr_imp            :1 ;
         uint64_t reserved_74_75     :2 ;
         uint64_t c_size             :10 ;

#else
         uint64_t c_size             :10 ;
         uint64_t reserved_74_75     :2 ;
         uint64_t dsr_imp            :1 ;
         uint64_t read_blk_misalign  :1 ;
         uint64_t write_blk_misalign :1 ;
         uint64_t read_bl_partial    :1 ;
         uint64_t read_bl_len        :4 ;
         uint64_t ccc                :12 ;
         uint64_t tran_speed         :8 ;
         uint64_t nsac               :8 ;
         uint64_t taac               :8 ;
         uint64_t reserved_120_125   :6 ;
         uint64_t csd_structure      :2 ;
#endif
    } s;
} sd_csd_register_hi_t;


typedef union sd_csd_register_lo
{
	uint64_t u;

    struct sd_csd_register_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN

         uint64_t c_size             :2 ;
         uint64_t vdd_r_curr_min     :3 ;
         uint64_t vdd_r_curr_max     :3 ;
         uint64_t vdd_w_curr_min     :3 ;
         uint64_t vdd_w_curr_max     :3 ;
         uint64_t c_size_mult        :3 ;
         uint64_t erase_blk_en       :1 ;
         uint64_t sector_size        :7 ;
         uint64_t wp_grp_size        :7 ;
         uint64_t wp_grp_enable      :1 ;
         uint64_t reserved_29_30     :2 ;
         uint64_t r2w_factor         :3 ;
         uint64_t write_bl_len       :4 ;
         uint64_t write_bl_partial   :1 ;
         uint64_t reserved_16_20     :5 ;
         uint64_t file_format_grp    :1 ;
         uint64_t copy               :1 ;
         uint64_t perm_write_protect :1 ;
         uint64_t tmp_write_protect  :1 ;
         uint64_t file_format        :2 ;
         uint64_t reserved_8_9       :2 ;
         uint64_t crc                :7 ;
         uint64_t always_one         :1 ;
#else
         uint64_t always_one         :1 ;
         uint64_t crc                :7 ;
         uint64_t reserved_8_9       :2 ;
         uint64_t file_format        :2 ;
         uint64_t tmp_write_protect  :1 ;
         uint64_t perm_write_protect :1 ;
         uint64_t copy               :1 ;
         uint64_t file_format_grp    :1 ;
         uint64_t reserved_16_20     :5 ;
         uint64_t write_bl_partial   :1 ;
         uint64_t write_bl_len       :4 ;
         uint64_t r2w_factor         :3 ;
         uint64_t reserved_29_30     :2 ;
         uint64_t wp_grp_enable      :1 ;
         uint64_t wp_grp_size        :7 ;
         uint64_t sector_size        :7 ;
         uint64_t erase_blk_en       :1 ;
         uint64_t c_size_mult        :3 ;
         uint64_t vdd_w_curr_max     :3 ;
         uint64_t vdd_w_curr_min     :3 ;
         uint64_t vdd_r_curr_max     :3 ;
         uint64_t vdd_r_curr_min     :3 ;
         uint64_t c_size             :2 ;
#endif
    } s;
} sd_csd_register_lo_t;


// SCR reg. is SD only

typedef union scr_register
{
    uint64_t u;

    struct scr_register_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN

        uint64_t scr_structure   :4 ;
        uint64_t sd_spec         :4 ;
        uint64_t data_stat_after_erase  :1 ;
        uint64_t sd_security     :3 ;
        uint64_t sd_bus_widths   :4 ;
        uint64_t sd_spec3        :1 ;
        uint64_t ex_security     :4 ;
        uint64_t reserved_46_43  :9 ;
        uint64_t cmd_support     :2 ;
        uint64_t reserved_31_0   :32 ;
#else
        uint64_t reserved_31_0   :32 ;
        uint64_t cmd_support     :2 ;
        uint64_t reserved_46_43  :9 ;
        uint64_t ex_security     :4 ;
        uint64_t sd_spec3        :1 ;
        uint64_t sd_bus_widths   :4 ;
        uint64_t sd_security     :3 ;
        uint64_t data_stat_after_erase  :1 ;
        uint64_t sd_spec         :4 ;
        uint64_t scr_structure   :4 ;
#endif
    } s;
} scr_register_t;

typedef struct
{
    uint64_t block_addressable_device;
    uint64_t card_is_sd;
    uint64_t relative_address;
    int64_t init_status;
    bdk_mio_emm_switch_t mio_emm_switch;
} mmc_card_state_t;

#define ULL unsigned long long
static mmc_card_state_t card_state[4];
static int last_chipsel;
static int init;

/**
 * Setup the eMMC controller watchdog to BDK_MMC_WATCHDOG(ms)
 */
static void set_wdog(bdk_node_t node, uint64_t timeout, int chip_sel)
{
    BDK_CSR_INIT(mode_reg, node, BDK_MIO_EMM_MODEX(chip_sel));
    uint64_t sclk = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
    uint64_t wdog_value = sclk * timeout / 1000;
    wdog_value /= mode_reg.s.clk_hi + mode_reg.s.clk_lo;
    BDK_CSR_WRITE(node, BDK_MIO_EMM_WDOG, wdog_value);
}

static void mmc_delay_msec(uint64_t msec)
{
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        bdk_wait_usec(msec); /* Speed up 1000x */
    else
        bdk_wait_usec(msec * 1000);
}

/**
 * print_cmd_status
 */
static void print_cmd_status(bdk_node_t node)
{
    BDK_CSR_INIT(sts_reg, node, BDK_MIO_EMM_RSP_STS);
    BDK_CSR_INIT(rsp_lo, node, BDK_MIO_EMM_RSP_LO);
    BDK_CSR_INIT(rsp_hi, node, BDK_MIO_EMM_RSP_HI);

    BDK_TRACE(EMMC, "Command index = %d, command type = %d\n", sts_reg.s.cmd_idx, sts_reg.s.cmd_type);
    switch (sts_reg.s.rsp_type)
    {
        case 1:
            BDK_TRACE(EMMC, "Response type 1, card status = 0x%08x\n", (uint32_t) ((rsp_lo.u >>8) & 0xFFFFFFFF));
            break;
        case 2:
            BDK_TRACE(EMMC, "Response type 2, rsp_hi-bits = 0x%016llx, rsp_lo-bits = 0x%016llx\n", (ULL)rsp_hi.u, (ULL)rsp_lo.u);
            break;
        case 3:
            BDK_TRACE(EMMC, "Response type 3, OCR Register = 0x%08x\n", (uint32_t) ((rsp_lo.u >>8) & 0xFFFFFFFF));
            break;
        case 4:
            BDK_TRACE(EMMC, "Response type 4, RCA = 0x%llx, status =0x%llx, reg. addr. = 0x%llx, reg. contents = 0x%llx\n",
                   (ULL)((rsp_lo.u >> 24) & 0xffff), (ULL)((rsp_lo.u >> 23) & 0x1), (ULL)((rsp_lo.u >> 16) & 0x7F), (ULL)((rsp_lo.u >> 8) & 0xFF));
            break;
        case 5:
            BDK_TRACE(EMMC, "Response type 5, RCA = 0x%llx, status =0x%llx, reg. addr. = 0x%llx\n",
                   (ULL)((rsp_lo.u >> 24) & 0xffff), (ULL)((rsp_lo.u >> 23) & 0x1), (ULL)((rsp_lo.u >> 16) & 0x7F));
            break;

        default:
            BDK_TRACE(EMMC, "Unknown response type, rsp_sts. reg. = 0x%llx\n", (ULL)sts_reg.u);
    }
}


void bdk_mmc_do_switch(bdk_node_t node, bdk_mio_emm_switch_t mio_emm_switch)
{
	int chip_sel = mio_emm_switch.s.bus_id;

	if (chip_sel != 0) {
		mio_emm_switch.s.bus_id = 0;
		BDK_CSR_WRITE(node, BDK_MIO_EMM_SWITCH, mio_emm_switch.u);
		bdk_wait_usec(100);
		mio_emm_switch.s.bus_id = chip_sel;
	}

	BDK_CSR_WRITE(node, BDK_MIO_EMM_SWITCH, mio_emm_switch.u);

	if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_MIO_EMM_RSP_STS, switch_val, ==, 0, 10 * 1000 )) {
		printf("Timeout waiting for switch command to complete\n");
	}
	card_state[chip_sel].mio_emm_switch = mio_emm_switch;
}

void bdk_mmc_switch_to(bdk_node_t node, int chip_sel)
{
	bdk_mio_emm_switch_t mio_emm_switch = card_state[chip_sel].mio_emm_switch;
	bdk_mio_emm_rca_t mio_emm_rca;

	if (chip_sel == last_chipsel)
		return;

	if (card_state[chip_sel].relative_address)
		BDK_CSR_WRITE(node, BDK_MIO_EMM_RCA, card_state[chip_sel].relative_address);

	bdk_mmc_do_switch(node, mio_emm_switch);

	mio_emm_rca.u = 0;
	mio_emm_rca.s.card_rca = card_state[chip_sel].relative_address;
	BDK_CSR_WRITE(node, BDK_MIO_EMM_RCA, mio_emm_rca.u);
	mmc_delay_msec(100);

	set_wdog(node, MMC_TIMEOUT_LONG, chip_sel);

	BDK_CSR_WRITE(node, BDK_MIO_EMM_STS_MASK, (1 << 7 | 1 << 22 | 1 << 23 | 1 << 19));

	last_chipsel = chip_sel;
	mmc_delay_msec(10);
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
static bdk_mio_emm_rsp_sts_t mmc_cmd(bdk_node_t node, uint64_t cmd, uint64_t arg, uint64_t busid, uint64_t dbuf, uint64_t rtype_xor, uint64_t ctype_xor, uint64_t offset)
{
    static const uint64_t timeout_short = 0xFFFFFFA4FCF9FFDFull;
    uint64_t timeout;

    if (timeout_short & (1ull << cmd))
        timeout = MMC_TIMEOUT_SHORT;
    else if (cmd == MMC_CMD_SWITCH && card_state[busid].card_is_sd)
        timeout = 2560;
    else if (cmd == MMC_CMD_ERASE)
        timeout = MMC_TIMEOUT_ERASE;
    else
        timeout = MMC_TIMEOUT_LONG;
    set_wdog(node, timeout, busid);
    timeout = (timeout + 1) * 1000;

    bdk_mmc_switch_to(node, busid);

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
    /* Make sure command made it all the way to the block */
    BDK_CSR_READ(node, BDK_MIO_EMM_CMD);

    BDK_TRACE(EMMC, "Waiting for command completion\n");
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_MIO_EMM_RSP_STS, cmd_done, ==, 1, timeout ))
    {
        BDK_TRACE(EMMC, "No response, timeout.\n");
        BDK_CSR_INIT(sts_reg, node, BDK_MIO_EMM_RSP_STS);
        return sts_reg;
    }

    BDK_CSR_INIT(sts_reg, node, BDK_MIO_EMM_RSP_STS);
    if (sts_reg.s.rsp_val || sts_reg.s.stp_val)
    {
        int cmd_error = 0;
        if (sts_reg.s.rsp_bad_sts || sts_reg.s.stp_bad_sts)
        {
            BDK_CSR_INIT(rsp_lo, node, BDK_MIO_EMM_RSP_LO);
            BDK_TRACE(EMMC, "Response bad status, cmd response = 0x%08x\n", (uint32_t) ((rsp_lo.u >>8) & 0xFFFFFFFF));
            cmd_error++;
        }
        if (sts_reg.s.rsp_crc_err || sts_reg.s.stp_crc_err)
        {
            BDK_TRACE(EMMC, "Response CRC error.\n");
            cmd_error++;
        }
        if (sts_reg.s.rsp_timeout || sts_reg.s.stp_timeout)
        {
            BDK_TRACE(EMMC, "Response timeout error.\n");
            cmd_error++;
        }
        if (sts_reg.s.blk_crc_err)
        {
            BDK_TRACE(EMMC, "Read/write block CRC error.\n");
            cmd_error++;
        }
        if (sts_reg.s.blk_timeout)
        {
            BDK_TRACE(EMMC, "Read/write block timeout error.\n");
            cmd_error++;
        }
        if (sts_reg.s.dbuf_err)
        {
            BDK_TRACE(EMMC, "Dbuf error, no free buffer\n");
            cmd_error++;
        }
        if (cmd_error)
        {
            if (BDK_TRACE_ENABLE_EMMC)
                print_cmd_status(node);
            return sts_reg;
        }
    }
    else
    {
        if ((sts_reg.s.cmd_idx != MMC_CMD_GO_IDLE_STATE) &&
            (sts_reg.s.cmd_idx != MMC_CMD_SET_DSR) &&
            (sts_reg.s.cmd_idx != MMC_CMD_GO_INACTIVE_STATE))
        {
            if (BDK_TRACE_ENABLE_EMMC)
            {
                cmd_reg.u = BDK_CSR_READ(node, BDK_MIO_EMM_CMD);
                sts_reg.u = BDK_CSR_READ(node, BDK_MIO_EMM_RSP_STS);
                BDK_CSR_INIT(rsp_lo, node, BDK_MIO_EMM_RSP_LO);
                BDK_CSR_INIT(rsp_hi, node, BDK_MIO_EMM_RSP_HI);
                BDK_TRACE(EMMC, "No valid response\n");
                BDK_TRACE(EMMC, "mio_emm_cmd     = 0x%016llx\n", (ULL)cmd_reg.u);
                BDK_TRACE(EMMC, "mio_emm_rsp_sts = 0x%016llx\n", (ULL)sts_reg.u);
                BDK_TRACE(EMMC, "mio_emm_rsp_lo  = 0x%016llx\n", (ULL)rsp_lo.u);
                BDK_TRACE(EMMC, "mio_emm_rsp_hi  = 0x%016llx\n", (ULL)rsp_hi.u);
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
    BDK_TRACE(EMMC, "\nOCR Register fields --\n");
    BDK_TRACE(EMMC, "Volts 1.70 - 1.95 0x%04x\n", ocr_reg.s.volts_1_7__1_95);
    BDK_TRACE(EMMC, "Volts 2.0 - 2.6   0x%04x\n", ocr_reg.s.volts_2_0__2_6);
    BDK_TRACE(EMMC, "Volts 2.7 - 3.6   0x%04x\n", ocr_reg.s.volts_2_7__3_6);
    BDK_TRACE(EMMC, "Access Mode       0x%04x\n", ocr_reg.s.access_mode);
}


/**
 * print_csd_reg
 *
 * @param reg_hi
 * @param reg_lo
 */
static void print_csd_reg(int chip_sel, uint64_t reg_hi, uint64_t reg_lo)
{
    if (card_state[chip_sel].card_is_sd)
    {
        sd_csd_register_hi_t  sd_csd_reg_hi;
        sd_csd_register_lo_t  sd_csd_reg_lo;
        sd_csd_reg_hi.u = reg_hi;
        sd_csd_reg_lo.u = reg_lo;
        BDK_TRACE(EMMC, "\nCSD Register fields --\n");
        BDK_TRACE(EMMC, "csd_structure       = 0x%x\n", sd_csd_reg_hi.s.csd_structure);
        BDK_TRACE(EMMC, "reserved_120_125    = 0x%x\n", sd_csd_reg_hi.s.reserved_120_125);
        BDK_TRACE(EMMC, "taac                = 0x%x\n", sd_csd_reg_hi.s.taac);
        BDK_TRACE(EMMC, "nsac                = 0x%x\n", sd_csd_reg_hi.s.nsac);
        BDK_TRACE(EMMC, "tran_speed          = 0x%x\n", sd_csd_reg_hi.s.tran_speed);
        BDK_TRACE(EMMC, "ccc                 = 0x%x\n", sd_csd_reg_hi.s.ccc);
        BDK_TRACE(EMMC, "read_bl_len         = 0x%x\n", sd_csd_reg_hi.s.read_bl_len);
        BDK_TRACE(EMMC, "read_bl_partial     = 0x%x\n", sd_csd_reg_hi.s.read_bl_partial);
        BDK_TRACE(EMMC, "write_blk_misalign  = 0x%x\n", sd_csd_reg_hi.s.write_blk_misalign);
        BDK_TRACE(EMMC, "read_blk_misalign   = 0x%x\n", sd_csd_reg_hi.s.read_blk_misalign);
        BDK_TRACE(EMMC, "dsr_imp             = 0x%x\n", sd_csd_reg_hi.s.dsr_imp);
        BDK_TRACE(EMMC, "reserved_74_75      = 0x%x\n", sd_csd_reg_hi.s.reserved_74_75);
        BDK_TRACE(EMMC, "c_size              = 0x%x\n", (sd_csd_reg_hi.s.c_size << 2) + sd_csd_reg_lo.s.c_size);
        BDK_TRACE(EMMC, "vdd_r_curr_min      = 0x%x\n", sd_csd_reg_lo.s.vdd_r_curr_min);
        BDK_TRACE(EMMC, "vdd_r_curr_max      = 0x%x\n", sd_csd_reg_lo.s.vdd_r_curr_max);
        BDK_TRACE(EMMC, "vdd_w_curr_min      = 0x%x\n", sd_csd_reg_lo.s.vdd_w_curr_min);
        BDK_TRACE(EMMC, "vdd_w_curr_max      = 0x%x\n", sd_csd_reg_lo.s.vdd_w_curr_max);
        BDK_TRACE(EMMC, "c_size_mult         = 0x%x\n", sd_csd_reg_lo.s.c_size_mult);
        BDK_TRACE(EMMC, "erase_blk_en        = 0x%x\n", sd_csd_reg_lo.s.erase_blk_en);
        BDK_TRACE(EMMC, "wp_grp_size         = 0x%x\n", sd_csd_reg_lo.s.wp_grp_size);
        BDK_TRACE(EMMC, "wp_grp_enable       = 0x%x\n", sd_csd_reg_lo.s.wp_grp_enable);
        BDK_TRACE(EMMC, "reserved_29_30      = 0x%x\n", sd_csd_reg_lo.s.reserved_29_30);
        BDK_TRACE(EMMC, "r2w_factor          = 0x%x\n", sd_csd_reg_lo.s.r2w_factor);
        BDK_TRACE(EMMC, "write_bl_len        = 0x%x\n", sd_csd_reg_lo.s.write_bl_len);
        BDK_TRACE(EMMC, "write_bl_partial    = 0x%x\n", sd_csd_reg_lo.s.write_bl_partial);
        BDK_TRACE(EMMC, "reserved_16_20      = 0x%x\n", sd_csd_reg_lo.s.reserved_16_20);
        BDK_TRACE(EMMC, "file_format_grp     = 0x%x\n", sd_csd_reg_lo.s.file_format_grp);
        BDK_TRACE(EMMC, "copy                = 0x%x\n", sd_csd_reg_lo.s.copy);
        BDK_TRACE(EMMC, "perm_write_protect  = 0x%x\n", sd_csd_reg_lo.s.perm_write_protect);
        BDK_TRACE(EMMC, "tmp_write_protect   = 0x%x\n", sd_csd_reg_lo.s.tmp_write_protect);
        BDK_TRACE(EMMC, "file_format         = 0x%x\n", sd_csd_reg_lo.s.file_format);
        BDK_TRACE(EMMC, "reserved_8_9        = 0x%x\n", sd_csd_reg_lo.s.reserved_8_9);
        BDK_TRACE(EMMC, "crc                 = 0x%x\n", sd_csd_reg_lo.s.crc);
        BDK_TRACE(EMMC, "always_one          = 0x%x\n", sd_csd_reg_lo.s.always_one);
    }
    else
    {
        mmc_csd_register_hi_t mmc_csd_reg_hi;
        mmc_csd_register_lo_t mmc_csd_reg_lo;
        mmc_csd_reg_hi.u = reg_hi;
        mmc_csd_reg_lo.u = reg_lo;
        BDK_TRACE(EMMC, "\nCSD Register fields --\n");
        BDK_TRACE(EMMC, "csd_structure       = 0x%x\n", mmc_csd_reg_hi.s.csd_structure);
        BDK_TRACE(EMMC, "spec_vers           = 0x%x\n", mmc_csd_reg_hi.s.spec_vers);
        BDK_TRACE(EMMC, "reserved_120_121    = 0x%x\n", mmc_csd_reg_hi.s.reserved_120_121);
        BDK_TRACE(EMMC, "taac                = 0x%x\n", mmc_csd_reg_hi.s.taac);
        BDK_TRACE(EMMC, "nsac                = 0x%x\n", mmc_csd_reg_hi.s.nsac);
        BDK_TRACE(EMMC, "tran_speed          = 0x%x\n", mmc_csd_reg_hi.s.tran_speed);
        BDK_TRACE(EMMC, "ccc                 = 0x%x\n", mmc_csd_reg_hi.s.ccc);
        BDK_TRACE(EMMC, "read_bl_len         = 0x%x\n", mmc_csd_reg_hi.s.read_bl_len);
        BDK_TRACE(EMMC, "read_bl_partial     = 0x%x\n", mmc_csd_reg_hi.s.read_bl_partial);
        BDK_TRACE(EMMC, "write_blk_misalign  = 0x%x\n", mmc_csd_reg_hi.s.write_blk_misalign);
        BDK_TRACE(EMMC, "read_blk_misalign   = 0x%x\n", mmc_csd_reg_hi.s.read_blk_misalign);
        BDK_TRACE(EMMC, "dsr_imp             = 0x%x\n", mmc_csd_reg_hi.s.dsr_imp);
        BDK_TRACE(EMMC, "reserved_74_75      = 0x%x\n", mmc_csd_reg_hi.s.reserved_74_75);
        BDK_TRACE(EMMC, "c_size              = 0x%x\n", (mmc_csd_reg_hi.s.c_size << 2) + mmc_csd_reg_lo.s.c_size);
        BDK_TRACE(EMMC, "vdd_r_curr_min      = 0x%x\n", mmc_csd_reg_lo.s.vdd_r_curr_min);
        BDK_TRACE(EMMC, "vdd_r_curr_max      = 0x%x\n", mmc_csd_reg_lo.s.vdd_r_curr_max);
        BDK_TRACE(EMMC, "vdd_w_curr_min      = 0x%x\n", mmc_csd_reg_lo.s.vdd_w_curr_min);
        BDK_TRACE(EMMC, "vdd_w_curr_max      = 0x%x\n", mmc_csd_reg_lo.s.vdd_w_curr_max);
        BDK_TRACE(EMMC, "c_size_mult         = 0x%x\n", mmc_csd_reg_lo.s.c_size_mult);
        BDK_TRACE(EMMC, "erase_grp_size      = 0x%x\n", mmc_csd_reg_lo.s.erase_grp_size);
        BDK_TRACE(EMMC, "erase_grp_mult      = 0x%x\n", mmc_csd_reg_lo.s.erase_grp_mult);
        BDK_TRACE(EMMC, "wp_grp_size         = 0x%x\n", mmc_csd_reg_lo.s.wp_grp_size);
        BDK_TRACE(EMMC, "wp_grp_enable       = 0x%x\n", mmc_csd_reg_lo.s.wp_grp_enable);
        BDK_TRACE(EMMC, "default_ecc         = 0x%x\n", mmc_csd_reg_lo.s.default_ecc);
        BDK_TRACE(EMMC, "r2w_factor          = 0x%x\n", mmc_csd_reg_lo.s.r2w_factor);
        BDK_TRACE(EMMC, "write_bl_len        = 0x%x\n", mmc_csd_reg_lo.s.write_bl_len);
        BDK_TRACE(EMMC, "write_bl_partial    = 0x%x\n", mmc_csd_reg_lo.s.write_bl_partial);
        BDK_TRACE(EMMC, "reserved_17_20      = 0x%x\n", mmc_csd_reg_lo.s.reserved_17_20);
        BDK_TRACE(EMMC, "content_prot_app    = 0x%x\n", mmc_csd_reg_lo.s.content_prot_app);
        BDK_TRACE(EMMC, "file_format_grp     = 0x%x\n", mmc_csd_reg_lo.s.file_format_grp);
        BDK_TRACE(EMMC, "copy                = 0x%x\n", mmc_csd_reg_lo.s.copy);
        BDK_TRACE(EMMC, "perm_write_protect  = 0x%x\n", mmc_csd_reg_lo.s.perm_write_protect);
        BDK_TRACE(EMMC, "tmp_write_protect   = 0x%x\n", mmc_csd_reg_lo.s.tmp_write_protect);
        BDK_TRACE(EMMC, "file_format         = 0x%x\n", mmc_csd_reg_lo.s.file_format);
        BDK_TRACE(EMMC, "crc                 = 0x%x\n", mmc_csd_reg_lo.s.crc);
        BDK_TRACE(EMMC, "always_one          = 0x%x\n", mmc_csd_reg_lo.s.always_one);
    }
}


/**
 * Macro to make it easier to submit a command and fail on bad status
 */
#if 0 // NEWPORT
#define MMC_CMD_OR_ERROR(node, cmd, arg, busid, dbuf, rtype_xor, ctype_xor, offset)   \
do {                                                                            \
    bdk_mio_emm_rsp_sts_t status = mmc_cmd(node, cmd, arg, busid, dbuf, rtype_xor, ctype_xor, offset); \
    if(status.u) {                                                            \
        bdk_error("MMC: Command " #cmd " failed\n");                            \
        return 0 ;                                                              \
    }                                                                           \
} while (0)
#else
#define MMC_CMD_OR_ERROR(node, cmd, arg, busid, dbuf, rtype_xor, ctype_xor, offset)   \
do {                                                                            \
    bdk_mio_emm_rsp_sts_t status = mmc_cmd(node, cmd, arg, busid, dbuf, rtype_xor, ctype_xor, offset); \
    if(status.u) {                                                            \
        return 0 ;                                                              \
    }                                                                           \
} while (0)
#endif

uint64_t get_clock_rate(bdk_node_t node, int chip_sel)
{
    BDK_CSR_INIT(emm_mode, node, BDK_MIO_EMM_MODEX(chip_sel));
    emm_mode.u = BDK_CSR_READ(node, BDK_MIO_EMM_MODEX(chip_sel));
    uint64_t sclk = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
    return (sclk / (emm_mode.s.clk_lo + emm_mode.s.clk_hi));
}

void bdk_mmc_host_probe(bdk_node_t node)
{
    if (!init) {
	// Inspired from u-boot host_probe function
	// Reset the entire bus
        BDK_CSR_WRITE(node, BDK_MIO_EMM_CFG, 0x0);
        BDK_TRACE(EMMC, "Delay 1ms\n");
        mmc_delay_msec(1);

	// Reset Interrupt flags
	BDK_CSR_DEFINE(emm_int, BDK_MIO_EMM_INT);
	emm_int.u = BDK_CSR_READ(node, BDK_MIO_EMM_INT);
	BDK_CSR_WRITE(node, BDK_MIO_EMM_INT, emm_int.u);

	init = 1;
	last_chipsel = -1;
    }
}

void bdk_mmc_chipsel_probe(bdk_node_t node, int chip_sel)
{
	bdk_mio_emm_cfg_t mio_emm_cfg;
	bdk_mio_emm_switch_t mio_emm_switch;
	uint64_t sclk = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);

	// This code is inspired from u-bbot mmc_init_lowlevel
	// Disable the bus
	mio_emm_cfg.u = BDK_CSR_READ(node, BDK_MIO_EMM_CFG);
	mio_emm_cfg.u &= ~(1<<chip_sel);
	BDK_CSR_WRITE(node, BDK_MIO_EMM_CFG, mio_emm_cfg.u);
	mmc_delay_msec(1);

	// Enable the bus
	mio_emm_cfg.u |= (1<<chip_sel);
	BDK_CSR_WRITE(node, BDK_MIO_EMM_CFG, mio_emm_cfg.u);
	mmc_delay_msec(1);

	// Set the clock to the minimum clock frequency of 400Khz
	// Change the clock
	int CLOCK_HZ = BDK_MMC_MIN_CLOCK_HZ;
	sclk /= CLOCK_HZ;
	sclk /= 2; /* Half is time hi/lo */
	mio_emm_switch.u = 0;
	mio_emm_switch.s.bus_id = chip_sel;
	mio_emm_switch.s.power_class = 10;
	mio_emm_switch.s.clk_hi = sclk;
	mio_emm_switch.s.clk_lo = sclk;

	bdk_mmc_do_switch(node, mio_emm_switch);

	set_wdog(node, MMC_TIMEOUT_LONG, chip_sel);

	// Reset the status mask reg., boot will change it
	BDK_CSR_WRITE(node, BDK_MIO_EMM_STS_MASK, 0xE4390080);

	// Set the RCA as it could have been changed from a previous cmd7 call
	BDK_CSR_WRITE(node, BDK_MIO_EMM_RCA, 0x1);

	BDK_TRACE(EMMC, "Delay 10ms\n");
	mmc_delay_msec(10);

	// Assume there is no card
	card_state[chip_sel].init_status = -1;

	// Assume card is eMMC
	card_state[chip_sel].card_is_sd = 0;

	// Save off mio_emm_switch register
	card_state[chip_sel].mio_emm_switch = mio_emm_switch;
}

/**
 * Initialize a MMC for read/write
 *
 * @author creese (10/14/2013)
 * @param node     Node to access
 * @param chip_sel Chip select to use
 *
 * @return Size of the SD card, zero on failure
 */
int64_t bdk_mmc_initialize(bdk_node_t node, int chip_sel)
{
	uint64_t CLOCK_HZ;
	uint64_t sclk = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
	bdk_mio_emm_switch_t mio_emm_switch;
	bdk_mio_emm_rsp_sts_t status;
	ocr_register_t ocr_reg;

	if (card_state[chip_sel].init_status) {
		if (card_state[chip_sel].init_status == -1)
			return 0;
		return card_state[chip_sel].init_status;
	}

	// Make sure we have setup the host side
	bdk_mmc_host_probe(node);

	// Setup a spefic chip select
	bdk_mmc_chipsel_probe(node, chip_sel);

	// Now switch to that chip select
	bdk_mmc_switch_to(node, chip_sel);

	//Reset the device
	MMC_CMD_OR_ERROR(node, MMC_CMD_GO_IDLE_STATE, 0, chip_sel, 0, 0, 0, 0);

	// Do a CMD SEND_EXT_CSD (8)
	if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
		status.u = -1; /* This always fails on the emulator so save boot time */
	else
		status = mmc_cmd(node, MMC_CMD_SEND_EXT_CSD, 0x000001AA, chip_sel, 0, 2, 1, 0);
	if (status.u == 0x0) {
		// We may have an SD card, as it should respond
		BDK_CSR_INIT(rsp_lo, node, BDK_MIO_EMM_RSP_LO);
		if (((rsp_lo.u >> 8) & 0xFFFFFFFFFF) != 0x08000001AA) {
			bdk_error("MMC: Unexpected response from MMC_CMD_SEND_EXT_CSD\n");
			return 0;
		}
		// Send a ACMD 41
		do {
			status = mmc_cmd(node, MMC_CMD_APP_CMD, 0, chip_sel, 0, 0, 0, 0);
			if (status.u == 0x0) {
				status = mmc_cmd(node, 41, 0x40ff8000, chip_sel, 0, 3, 0, 0);
				if (status.u) {
					bdk_error("MMC: Failed to recognize card\n");
					return 0;
				}
				card_state[chip_sel].card_is_sd = 1;
			} else {
				// Failed, not sure what's out there
				bdk_error("MMC: Failed to recognize card\n");
				return 0;
			}

			ocr_reg.u32 = (uint32_t) ((BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO) >>8) &0xFFFFFFFF);
		} while (ocr_reg.s.done_bit == 0x0);
		// Success, we have an SD card version 2.0 or above, fall through
	} else {
		// Card could be an SD version less than 2.0 or an MMC card
		// Send a ACMD 41
		do {
			if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
				status.u = -1; /* This always fails on the emulator so save boot time */
			else
				status = mmc_cmd(node, MMC_CMD_APP_CMD, 0, chip_sel, 0, 0, 0, 0);

			if (status.u == 0x0) {
				status = mmc_cmd(node, 41, 0x40ff8000, chip_sel, 0, 3, 0, 0);
				if (status.u) {
					// Have an SD card, version less than 2.0
					// fall through, exit the loop
					card_state[chip_sel].card_is_sd = 1;
					break;
				}
			} else {
				// APP_CMD command failed
				break;
			}
			ocr_reg.u32 = (uint32_t) ((BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO) >>8) &0xFFFFFFFF);
		} while (ocr_reg.s.done_bit == 0x0);

		if (status.u == 0x0) {
			// Success, we have an SD card version 2.0 or less
			card_state[chip_sel].card_is_sd = 1;
		} else {
			//Have an MMC card, do a command 1
			//Select the initial operating conditions
			do {
				MMC_CMD_OR_ERROR(node, MMC_CMD_SEND_OP_COND, 0x40ff8000, chip_sel, 0, 0, 0, 0);
				ocr_reg.u32 = (uint32_t) ((BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO) >>8) &0xFFFFFFFF);
			} while (ocr_reg.s.done_bit == 0x0);
		}
	}

	// Global to determine if the card is block or byte addressable.
	card_state[chip_sel].block_addressable_device = ocr_reg.s.access_mode;
	if (BDK_TRACE_ENABLE_EMMC)
		print_ocr_reg(ocr_reg);

	// Get card identification
	MMC_CMD_OR_ERROR(node, MMC_CMD_ALL_SEND_CID, 0, chip_sel, 0, 0, 0, 0);

	if (card_state[chip_sel].card_is_sd) {
		// For SD, read the relative address from the card
		// CMD3 response for SD cards is R6 format, similar to R1, but different
		// Need to chane the mio_EMM_STS_MASK register so we don't get a response status error
		BDK_CSR_INIT(sts_mask, node, BDK_MIO_EMM_STS_MASK);
		BDK_CSR_WRITE(node, BDK_MIO_EMM_STS_MASK, 0xE000);
		status = mmc_cmd(node, MMC_CMD_SET_RELATIVE_ADDR, 0, chip_sel, 0, 0, 0, 0);
		BDK_CSR_WRITE(node, BDK_MIO_EMM_STS_MASK, sts_mask.u);
		if (status.u) {
			bdk_error("MMC: Command MMC_CMD_SET_RELATIVE_ADDR failed\n");
			return 0;
		}
		card_state[chip_sel].relative_address = ((BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO) >>24) &0xFFFF);
	} else {
		// For MMC, set card relative address
		card_state[chip_sel].relative_address = 1; //Default for MMC cards
		MMC_CMD_OR_ERROR(node, MMC_CMD_SET_RELATIVE_ADDR, card_state[chip_sel].relative_address << 16, chip_sel, 0, 0, 0, 0);
	}

	BDK_CSR_WRITE(node, BDK_MIO_EMM_RCA, card_state[chip_sel].relative_address);

	// Get CSD Register
	MMC_CMD_OR_ERROR(node, MMC_CMD_SEND_CSD, card_state[chip_sel].relative_address << 16, chip_sel, 0, 0, 0, 0);
	mmc_csd_register_lo_t csd_reg_lo;
	csd_reg_lo.u = (BDK_CSR_READ(node, BDK_MIO_EMM_RSP_LO));
	mmc_csd_register_hi_t csd_reg_hi;
	csd_reg_hi.u = (BDK_CSR_READ(node, BDK_MIO_EMM_RSP_HI));
	uint64_t mmc_capacity;
	if (card_state[chip_sel].card_is_sd) {
		sd_csd_register_hi_t  sd_csd_reg_hi;
		sd_csd_register_lo_t  sd_csd_reg_lo;
		sd_csd_reg_hi.u = csd_reg_hi.u;
		sd_csd_reg_lo.u = csd_reg_lo.u;
		mmc_capacity = (sd_csd_reg_hi.s.c_size << 2) + sd_csd_reg_lo.s.c_size;
		mmc_capacity = (mmc_capacity + 1) << (sd_csd_reg_lo.s.c_size_mult + 2);
		mmc_capacity *= 1<<sd_csd_reg_hi.s.read_bl_len;
	} else {
		mmc_csd_register_hi_t mmc_csd_reg_hi;
		mmc_csd_register_lo_t mmc_csd_reg_lo;
		mmc_csd_reg_hi.u = csd_reg_hi.u;
		mmc_csd_reg_lo.u = csd_reg_lo.u;
		mmc_capacity = (mmc_csd_reg_hi.s.c_size << 2) + mmc_csd_reg_lo.s.c_size;
		mmc_capacity = (mmc_capacity + 1) << (mmc_csd_reg_lo.s.c_size_mult + 2);
		mmc_capacity *= 1<<mmc_csd_reg_hi.s.read_bl_len;
	}

	if (BDK_TRACE_ENABLE_EMMC)
		print_csd_reg(chip_sel, csd_reg_hi.u, csd_reg_lo.u);

	// Select Card
	MMC_CMD_OR_ERROR(node, MMC_CMD_SELECT_CARD, card_state[chip_sel].relative_address << 16 , chip_sel, 0, 0, 0, 0);
	// Send Card Status
	MMC_CMD_OR_ERROR(node, MMC_CMD_SEND_STATUS, card_state[chip_sel].relative_address << 16 , chip_sel, 0, 0, 0, 0);

	// Set the clock to a default clock frequency of 26Mhz
	// Change the clock
	CLOCK_HZ = BDK_MMC_CLOCK_HZ;
	sclk /= CLOCK_HZ;
	sclk /= 2; /* Half is time hi/lo */
	mio_emm_switch.u = 0;
	mio_emm_switch.s.bus_id = chip_sel;
	mio_emm_switch.s.power_class = 10;
	mio_emm_switch.s.clk_hi = sclk;
	mio_emm_switch.s.clk_lo = sclk;

	bdk_mmc_do_switch(node, mio_emm_switch);

	// If we are a mmc card, we can additionally change the bus width
	if (!card_state[chip_sel].card_is_sd) {
		mio_emm_switch.s.switch_exe = 1;
		mio_emm_switch.s.bus_width = 6; /* 8 bit double data rate */

		BDK_CSR_WRITE(node, BDK_MIO_EMM_SWITCH, mio_emm_switch.u);

		if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_MIO_EMM_RSP_STS, switch_val, ==, 0, 10 * 1000 )) {
			printf("Timeout waiting for switch command to complete\n");
		}
		card_state[chip_sel].mio_emm_switch = mio_emm_switch;
	}

	// Reset watchdog timer for the new bus speed
	set_wdog(node, BDK_MMC_WATCHDOG, chip_sel);

	// Return the card size in bytes
	BDK_TRACE(EMMC, "MMC init done\n");
	card_state[chip_sel].init_status = mmc_capacity;
	return mmc_capacity;
}



bool bdk_mmc_card_is_sd(bdk_node_t node, int chip_sel)
{
	return (card_state[chip_sel].card_is_sd);
}

/**
 * Read blocks from a MMC card
 *
 * @author creese (10/14/2013)
 * @param node     Node to access
 * @param chip_sel Chip select to use
 * @param address  Offset into the card in bytes. Must be a multiple of 512
 * @param buffer   Buffer to read into
 * @param length   Length to read in bytes. Must be a multiple of 512
 *
 * @return Zero on success, negative on failure
 */
int bdk_mmc_read(bdk_node_t node, int chip_sel, uint64_t address, void *buffer, int length)
{
    int block_cnt = card_state[chip_sel].block_addressable_device ? length / 512: length;
    int card_addr = card_state[chip_sel].block_addressable_device ? address / 512: address;

    if (address > (1ull << 40))
    {
        bdk_error("MMC read address too large\n");
        return -1;
    }
    if (address & 511)
    {
        bdk_error("MMC read address must be a multiple of 512\n");
        return -1;
    }
    if (length > (1ll << 30))
    {
        bdk_error("MMC read length too large\n");
        return -1;
    }
    if (length & 511)
    {
        bdk_error("MMC read length must be a multiple of 512\n");
        return -1;
    }
	bdk_mmc_switch_to(node, chip_sel);
	if (__bdk_is_dram_enabled(node)) {
		BDK_CSR_DEFINE(emm_dma_int, BDK_MIO_EMM_DMA_INT);
		emm_dma_int.u = BDK_CSR_READ(node, BDK_MIO_EMM_DMA_INT);
		BDK_CSR_WRITE(node, BDK_MIO_EMM_DMA_INT, emm_dma_int.u);

		BDK_CSR_DEFINE(emm_dma_addr, BDK_MIO_EMM_DMA_ADR);
		BDK_CSR_DEFINE(emm_dma_cfg, BDK_MIO_EMM_DMA_CFG);
		emm_dma_cfg.u = 0;
		emm_dma_cfg.s.en = 1;
		emm_dma_cfg.s.rw = 0;
		emm_dma_cfg.s.clr = 0;
		emm_dma_cfg.s.size = (length / 8) - 1;
	#if __BYTE_ORDER != __BIG_ENDIAN
		emm_dma_cfg.s.endian = 1;
	#endif
		emm_dma_addr.u = 0;
		emm_dma_addr.s.adr = bdk_ptr_to_phys(buffer);
		BDK_CSR_WRITE(node, BDK_MIO_EMM_DMA_ADR, emm_dma_addr.u);
		BDK_CSR_WRITE(node, BDK_MIO_EMM_DMA_CFG, emm_dma_cfg.u);


		BDK_CSR_DEFINE(emm_dma, BDK_MIO_EMM_DMA);
		emm_dma.u = 0;
		emm_dma.s.bus_id = chip_sel;
		emm_dma.s.dma_val = 1;
		emm_dma.s.sector = card_state[chip_sel].block_addressable_device;
		if (block_cnt > 1)
			emm_dma.s.multi = 1;
		emm_dma.s.block_cnt = block_cnt;
		emm_dma.s.card_addr = card_addr;

		set_wdog(node, 1000 + (block_cnt * 20), chip_sel);

		BDK_CSR_WRITE(node, BDK_MIO_EMM_DMA, emm_dma.u);
		BDK_CSR_DEFINE(emm_rsp_sts, BDK_MIO_EMM_RSP_STS);
		do {
			emm_rsp_sts.u = BDK_CSR_READ(node, BDK_MIO_EMM_RSP_STS);
			emm_dma_int.u = BDK_CSR_READ(node, BDK_MIO_EMM_DMA_INT);
		} while (emm_rsp_sts.s.dma_val || !emm_dma_int.s.done);

		return 0;
	} else {
	    /* Read until we've read all data */
	    while (length > 0)
	    {
	        BDK_TRACE(EMMC, "Read 0x%lx\n", address);
	        /* Send the read command */
	        BDK_CSR_DEFINE(status, BDK_MIO_EMM_RSP_STS);
	        status = mmc_cmd(node, MMC_CMD_READ_SINGLE_BLOCK, (card_state[chip_sel].block_addressable_device) ? address/512 : address, chip_sel, 0, 0, 0, 0);
	        if (status.u)
	        {
	            bdk_error("MMC: Read single block failed\n");
	            return -1;
	        }

	        /* Set our location in the internal buffer */
	        BDK_CSR_DEFINE(buf_idx, BDK_MIO_EMM_BUF_IDX);
	        buf_idx.u = 0;
	        buf_idx.s.inc = 1;
	        buf_idx.s.buf_num = 0;
	        buf_idx.s.offset = 0;
	        BDK_CSR_WRITE(node, BDK_MIO_EMM_BUF_IDX, buf_idx.u);

	        BDK_TRACE(EMMC, "Copy data\n");
	        /* Read out the data block and add it to the output buffer */
	        for (int i=0; i<512/8; i++)
	        {
	            uint64_t data = bdk_be64_to_cpu(BDK_CSR_READ(node, BDK_MIO_EMM_BUF_DAT));
	            *(uint64_t*)buffer = data;
	            buffer += 8;
	        }
	        /* Increment to the next position and adjust the size left */
	        address += 512;
	        length -= 512;
	        BDK_TRACE(EMMC, "Read done\n");
	        if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
	        {
	            static int block_count = 0;
	            block_count++;
	            putchar('.');
	            if ((block_count & 63) == 0)
	                putchar('\n');
	        }
	    }
	}
    return 0;
}

/**
 * Write blocks to a MMC card
 *
 * @author creese (10/14/2013)
 * @param node     Node to access
 * @param chip_sel Chip select to use
 * @param address  Offset into the card in bytes. Must be a multiple of 512
 * @param buffer   Buffer to write
 * @param length   Length to write in bytes. Must be a multiple of 512
 *
 * @return Zero on success, negative on failure
 */
int bdk_mmc_write(bdk_node_t node, int chip_sel, uint64_t address, const void *buffer, int length)
{
    if (address > (1ull << 40))
    {
        bdk_error("MMC write address too large\n");
        return -1;
    }
    if (address & 511)
    {
        bdk_error("MMC write address must be a multiple of 512\n");
        return -1;
    }
    if (length > (1ll << 30))
    {
        bdk_error("MMC write length too large\n");
        return -1;
    }
    if (length & 511)
    {
        bdk_error("MMC write length must be a multiple of 512\n");
        return -1;
    }

    bdk_mmc_switch_to(node, chip_sel);
    /* Write until no more data */
    while (length > 0)
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
            BDK_CSR_WRITE(node, BDK_MIO_EMM_BUF_DAT, bdk_cpu_to_be64(*(uint64_t*)buffer));
            buffer += 8;
        }

        /* Write single block */
        BDK_CSR_DEFINE(status, BDK_MIO_EMM_RSP_STS);
        status = mmc_cmd(node, MMC_CMD_WRITE_BLOCK, (card_state[chip_sel].block_addressable_device) ? address/512 : address, chip_sel, 0, 0, 0, 0);
        if (status.u)
        {
            bdk_error("MMC: Write single block failed\n");
            return -1;
        }
        address += 512;
        length -= 512;
    }
    return 0;
}

