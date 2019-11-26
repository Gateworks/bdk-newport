/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-lmc.h"
#include "libbdk-arch/bdk-csrs-mcc.h"
#include "libdram.h"

#include "bdk-dram-init.h"

/* Parameters from DDR3/DDR4 Specifications */
#define DDR_tREFI         7800000    /* 7.8 us */
#define DDR_ZQCS_Interval 1280000000 /* 128ms/100 */
#define DDR_tCKE          5000       /* 5 ns */
#define DDR_tMPRR         1          /* 1 nCK */
#define DDR_tWLMRD        40         /* 40 nCK */
#define DDR_tWLDQSEN      25         /* 25 nCK */

/* Parameters from DDR4 Specifications */
#define DDR4_tMRD          8          /* 8 nCK */
#define DDR4_tDLLK         768        /* 768 nCK */

#define DEBUG_RC3X_COMPUTE 0
#define rc3x_print(...) \
    do { if (DEBUG_RC3X_COMPUTE) printf(__VA_ARGS__); } while (0)

#define DEFAULT_INTERNAL_VREF_TRAINING_LIMIT 3 // was 5

int
CN8_OR_CN9(int x8, int x9) {
    return (bdk_is_model(OCTEONTX_CN8XXX) ? x8 : x9 );
}

static unsigned int EXTR_ARB(int w, uint64_t u, int x) {
    return (u >> (x * w)) & ((1ULL << w) - 1);
}

unsigned int EXTR_WR(uint64_t u, int x)
{
    unsigned int ret = 0;
    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        ret = (((u >> (x*12+5)) & 0x3UL) | ((u >> (51+x-2)) & 0x4UL));
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        ret = ((u >> (x*13+5)) & 0x7UL);
    }
    return ret;
}

void INSRT_WR(uint64_t *up, int x, int v)
{
    uint64_t u = *up;
    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        u &= ~(((0x3UL) << (x*12+5)) | ((0x1UL) << (51+x)));
        *up = (u | ((v & 0x3UL) << (x*12+5)) | ((v & 0x4UL) << (51+x-2)));
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        u &= ~((0x7UL) << (x*13+5));
        *up = (u | ((v & 0x7UL) << (x*13+5)));
    }
    return;
}

unsigned int EXTR_NOM(uint64_t u, int x)
{
    int step, off;
    step = CN8_OR_CN9(12, 13);
    off  = CN8_OR_CN9( 9, 10);

    return (unsigned int)((u >> (x*step+off)) & 0x7UL);
}

void INSRT_NOM(uint64_t *up, int x, int v)
{
    uint64_t u = *up;
    int step, off;
    step = CN8_OR_CN9(12, 13);
    off  = CN8_OR_CN9( 9, 10);

    u &= ~((0x7UL) << (x*step+off));
    *up = (u | ((v & 0x7UL) << (x*step+off)));
    return;
}

unsigned int EXTR_DIC(uint64_t u, int x)
{
    int step, off;
    step = CN8_OR_CN9(12, 13);
    off  = CN8_OR_CN9( 7,  8);

    return (unsigned int)((u >> (x*step+off)) & 0x3UL);
}

void INSRT_DIC(uint64_t *up, int x, int v)
{
    uint64_t u = *up;
    int step, off;
    step = CN8_OR_CN9(12, 13);
    off  = CN8_OR_CN9( 7,  8);

    u &= ~((0x3UL) << (x*step+off));
    *up = (u | ((v & 0x3UL) << (x*step+off)));
    return;
}

void INSRT_PASR(uint64_t *up, int x, int v)
{
    uint64_t u = *up;

    u &= ~((0x7UL) << (x*12+0));
    *up = (u | ((v & 0x7UL) << (x*12+0)));
    return;
}

void INSRT_ASR(uint64_t *up, int x, int v)
{
    uint64_t u = *up;

    u &= ~((0x1UL) << (x*12+3));
    *up = (u | ((v & 0x1UL) << (x*12+3)));
    return;
}

void INSRT_SRT(uint64_t *up, int x, int v)
{
    uint64_t u = *up;

    u &= ~((0x1UL) << (x*12+4));
    *up = (u | ((v & 0x1UL) << (x*12+4)));
    return;
}

unsigned int EXTR_PARK(uint64_t u, int x)
{
    return (unsigned int)(((u >> (x*10+0)) & 0x7UL));
}

void INSRT_PARK(uint64_t *up, int x, int v)
{
    uint64_t u = *up;
    u &= ~((0x7UL) << (x*10+0));
    *up = (u | ((v & 0x7UL) << (x*10+0)));
    return;
}

int set_rdimm_mode(bdk_node_t node, int ddr_interface_num, int enable)
{
    bdk_lmcx_control_t lmc_control;
    int save_rdimm_mode;

    lmc_control.u = BDK_CSR_READ(node, BDK_LMCX_CONTROL(ddr_interface_num));
    save_rdimm_mode = lmc_control.s.rdimm_ena;
    lmc_control.s.rdimm_ena       = enable;
    VB_PRT(VBL_FAE, "Setting RDIMM_ENA = %x\n", enable);
    DRAM_CSR_WRITE(node, BDK_LMCX_CONTROL(ddr_interface_num), lmc_control.u);

    return (save_rdimm_mode);
}

int set_lrdimm_mode(bdk_node_t node, int ddr_interface_num, int enable)
{
    bdk_lmcx_config_t lmc_config;
    int save_lrdimm_mode;

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));
    save_lrdimm_mode = lmc_config.s.lrdimm_ena;
    lmc_config.s.lrdimm_ena = enable;
    VB_PRT(VBL_FAE, "Setting LRDIMM_ENA = %x\n", enable);
    DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(ddr_interface_num), lmc_config.u);

    return (save_lrdimm_mode);
}

void perform_octeontx_ddr_sequence(bdk_node_t node, int rank_mask,
                                   int ddr_interface_num, int sequence)
{
    /*
     * 3. Without changing any other fields in LMC(0)_CONFIG, write
     *    LMC(0)_CONFIG[RANKMASK] then write both
     *    LMC(0)_SEQ_CTL[SEQ_SEL,INIT_START] = 1 with a single CSR write
     *    operation. LMC(0)_CONFIG[RANKMASK] bits should be set to indicate
     *    the ranks that will participate in the sequence.
     *
     *    The LMC(0)_SEQ_CTL[SEQ_SEL] value should select power-up/init or
     *    selfrefresh exit, depending on whether the DRAM parts are in
     *    self-refresh and whether their contents should be preserved. While
     *    LMC performs these sequences, it will not perform any other DDR3
     *    transactions. When the sequence is complete, hardware sets the
     *    LMC(0)_CONFIG[INIT_STATUS] bits for the ranks that have been
     *    initialized.
     *
     *    If power-up/init is selected immediately following a DRESET
     *    assertion, LMC executes the sequence described in the "Reset and
     *    Initialization Procedure" section of the JEDEC DDR3
     *    specification. This includes activating CKE, writing all four DDR3
     *    mode registers on all selected ranks, and issuing the required ZQCL
     *    command. The LMC(0)_CONFIG[RANKMASK] value should select all ranks
     *    with attached DRAM in this case. If LMC(0)_CONTROL[RDIMM_ENA] = 1,
     *    LMC writes the JEDEC standard SSTE32882 control words selected by
     *    LMC(0)_DIMM_CTL[DIMM*_WMASK] between DDR_CKE* signal assertion and
     *    the first DDR3 mode register write operation.
     *    LMC(0)_DIMM_CTL[DIMM*_WMASK] should be cleared to 0 if the
     *    corresponding DIMM is not present.
     *
     *    If self-refresh exit is selected, LMC executes the required SRX
     *    command followed by a refresh and ZQ calibration. Section 4.5
     *    describes behavior of a REF + ZQCS.  LMC does not write the DDR3
     *    mode registers as part of this sequence, and the mode register
     *    parameters must match at self-refresh entry and exit times.
     *
     * 4. Read LMC(0)_SEQ_CTL and wait for LMC(0)_SEQ_CTL[SEQ_COMPLETE] to be
     *    set.
     *
     * 5. Read LMC(0)_CONFIG[INIT_STATUS] and confirm that all ranks have
     *    been initialized.
     */

    static const char *sequence_str[] = {
	/* 00 */ "Power-up/init",
	/* 01 */ "Read-leveling",
	/* 02 */ "Self-refresh entry",
	/* 03 */ "Self-refresh exit",
	/* 04 */ "Illegal",
	/* 05 */ "Illegal",
	/* 06 */ "Write-leveling",
	/* 07 */ "Init Register Control Words",
	/* 08 */ "Mode Register Write",
	/* 09 */ "MPR Register Access",
	/* 10 */ "LMC Deskew/Internal Vref training",
	/* 11 */ "Offset Training",
	/* 12 */ "Illegal",
	/* 13 */ "POW MPR", // CN9XXX only
	/* 14 */ "RW Training",
	/* 15 */ "Post Package Repair",
	/* 16 */ "MPSM Entry", // CN9XXX only
	/* 17 */ "MPSM Exit", // CN9XXX only
    };

    bdk_lmcx_seq_ctl_t seq_ctl;
    bdk_lmcx_config_t  lmc_config;
    int is_cn8xxx = bdk_is_model(OCTEONTX_CN8XXX);

    lmc_config.u = BDK_CSR_READ(node, BDK_LMCX_CONFIG(ddr_interface_num));
    lmc_config.s.rankmask = rank_mask;
    DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(ddr_interface_num), lmc_config.u);

    seq_ctl.u = 0;

    if (is_cn8xxx) {
        seq_ctl.cn8.seq_sel = sequence;
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        seq_ctl.cn9.seq_sel = sequence;
    }
    seq_ctl.s.init_start  = 1;

    VB_PRT(VBL_SEQ, "N%d.LMC%d: Performing LMC sequence=%x: rank_mask=0x%02x, %s\n",
            node, ddr_interface_num, sequence, rank_mask, sequence_str[sequence]);

    DRAM_CSR_WRITE(node, BDK_LMCX_SEQ_CTL(ddr_interface_num), seq_ctl.u);
    BDK_CSR_READ(node, BDK_LMCX_SEQ_CTL(ddr_interface_num));

    /* Wait 100us minimum before checking for sequence complete */
    bdk_wait_usec(100);

    if (!bdk_is_platform(BDK_PLATFORM_ASIM)) {

	//was: if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_LMCX_SEQ_CTL(ddr_interface_num), seq_complete, ==, 1, 1000000))
        int result = 0;
        uint64_t timeout_usec = 1000000;
        uint64_t done =
            bdk_clock_get_count(BDK_CLOCK_TIME) + (uint64_t)timeout_usec *
            bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;

        while (1) {
            seq_ctl.u = BDK_CSR_READ(node, BDK_LMCX_SEQ_CTL(ddr_interface_num));
            int complete = (is_cn8xxx)
                ? seq_ctl.cn8.seq_complete
                : seq_ctl.cn9.seq_complete;
            if (complete == 1)
                break;
            else if (bdk_clock_get_count(BDK_CLOCK_TIME) > done) {
                result = -1;
                break;
            } else
                bdk_thread_yield();
        } /* while (1) */

        if (result)
        {
            error_print("N%d.LMC%d: Timeout waiting for LMC sequence=%x, rank_mask=0x%02x, ignoring...\n",
                        node, ddr_interface_num, sequence, rank_mask);
            return;
        }
    } /* if (!bdk_is_platform(BDK_PLATFORM_ASIM)) */

    VB_PRT(VBL_SEQ, "N%d.LMC%d: LMC sequence=%x: Completed.\n", node, ddr_interface_num, sequence);
}

void
do_lmc_ddr_reset(bdk_node_t node, int ddr_interface_num, int reset)
{
    /*
     * 4. Deassert DDRn_RESET_L pin by writing LMC(0..3)_RESET_CTL[DDR3RST] = 1
     *    without modifying any other LMC(0..3)_RESET_CTL fields.
     * 5. Read LMC(0..3)_RESET_CTL and wait for the result.
     * 6. Wait a minimum of 500us. This guarantees the necessary T = 500us
     *    delay between DDRn_RESET_L deassertion and DDRn_DIMM*_CKE* assertion.
     */
    // NOTE: CN9XXX RESET_CTL CSR uses same bit for RESET as CN8XXX CSR
    //       that is, for 9XXX RESET_CTL[ddr4rst] == 8XXX RESET_CTL[ddr3rst]
    //
    ddr_print("LMC%d %s DDR_RESET_L\n", ddr_interface_num,
	      (reset == LMC_RESET_DEASSERT) ? "De-asserting" : "Asserting");

    // NOTE: this is OK on both CN8XXX and CN9XXX
    DRAM_CSR_MODIFY(c, node, BDK_LMCX_RESET_CTL(ddr_interface_num),
                    c.cn8.ddr3rst = reset);

    // read to force the write
    BDK_CSR_READ(node, BDK_LMCX_RESET_CTL(ddr_interface_num));

    // wait 200us after ASSERT, or 500us after DEASSERT 
    bdk_wait_usec((reset == LMC_RESET_ASSERT) ? 200 : 500);
}

int Perform_LMC_RESET_Init(bdk_node_t node, int ddr_interface_num,
                           dram_init_data_t *init_data)
{
    // HRM-CN9XXX Section 7.9.5
    /*
     * 6.9.6 LMC RESET Initialization
     *
     * The purpose of this step is to assert/deassert the RESET# pin at the
     * DDR3/DDR4 parts.
     *
     * This LMC RESET step is done for all enabled LMCs.
     *
     * It may be appropriate to skip this step if the DDR3/DDR4 DRAM parts
     * are in self refresh and are currently preserving their
     * contents. (Software can determine this via
     * LMC(0..3)_RESET_CTL[DDR3PSV] in some circumstances.) The remainder of
     * this section assumes that the DRAM contents need not be preserved.
     *
     * The remainder of this section assumes that the CN8XXX DDRn_RESET_L pin
     * is attached to the RESET# pin of the attached DDR3/DDR4 parts, as will
     * be appropriate in many systems.
     *
     * (In other systems, such as ones that can preserve DDR3/DDR4 part
     * contents while CN8XXX is powered down, it will not be appropriate to
     * directly attach the CN8XXX DDRn_RESET_L pin to DRESET# of the
     * DDR3/DDR4 parts, and this section may not apply.)
     *
     * The remainder of this section describes the sequence for LMCn.
     *
     * Perform the following six substeps for LMC reset initialization:
     *
     * 1. If not done already, assert DDRn_RESET_L pin by writing
     *    LMC(0..3)_RESET_ CTL[DDR3RST] = 0 without modifying any other
     *    LMC(0..3)_RESET_CTL fields.
     * 2. Read LMC(0..3)_RESET_CTL and wait for the result.
     * 3. Wait until RESET# assertion-time requirement from JEDEC DDR3/DDR4
     *    specification is satisfied (200 us during a power-on ramp, 100ns when
     *    power is already stable).
     * 4. Deassert DDRn_RESET_L pin by writing LMC(0..3)_RESET_CTL[DDR3RST] = 1
     *    without modifying any other LMC(0..3)_RESET_CTL fields.
     * 5. Read LMC(0..3)_RESET_CTL and wait for the result.
     * 6. Wait a minimum of 500us. This guarantees the necessary T = 500us
     *    delay between DDRn_RESET_L deassertion and DDRn_DIMM*_CKE* assertion.
     */

    if ( !ddr_memory_preserved(node)) {

        do_lmc_ddr_reset(node, ddr_interface_num, LMC_RESET_ASSERT);
        do_lmc_ddr_reset(node, ddr_interface_num, LMC_RESET_DEASSERT);

        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            /* Toggle Reset Again */
            /* That is, assert, then de-assert, one more time */
            do_lmc_ddr_reset(node, ddr_interface_num, LMC_RESET_ASSERT);
            do_lmc_ddr_reset(node, ddr_interface_num, LMC_RESET_DEASSERT);
        }

    } else { /* if ( !ddr_memory_preserved(node)) */

        // only CN9xxx preserves GP0-2 across core domain resets...
        if (bdk_is_model(OCTEONTX_CN9XXX)) {
            int lmc = ddr_interface_num;

            // move the preserved CSRs contents to globals for later use
            // address mask is different for each LMC
            // NOTE: remember that GP2 only holds 16 bits!!
            global_scramble_cfg2[lmc] = BDK_CSR_READ(node, BDK_LMCX_GENERAL_PURPOSE2(lmc));
            printf("N%d.LMC%d: Memory Preserve: Saving GENERAL_PURPOSE2: 0x%016lx\n",
                   node, lmc, global_scramble_cfg2[lmc]);

            if (lmc < 2) { // LMC2 shares MCC with LMC0, no need to do data masks for LMC2
                // preserving memory, save the GP regs in case we were also SCRAMBLING...
                // assume GENERAL_PURPOSE CSRs hold the previous scramble keys
                global_scramble_cfg0[lmc] = BDK_CSR_READ(node, BDK_LMCX_GENERAL_PURPOSE0(lmc));
                global_scramble_cfg1[lmc] = BDK_CSR_READ(node, BDK_LMCX_GENERAL_PURPOSE1(lmc));

                printf("N%d.LMC%d: Memory Preserve: Saving GENERAL_PURPOSE0: 0x%016lx\n",
                       node, lmc, global_scramble_cfg0[lmc]);
                printf("N%d.LMC%d: Memory Preserve: Saving GENERAL_PURPOSE1: 0x%016lx\n",
                       node, lmc, global_scramble_cfg1[lmc]);
            }
        } /* if (bdk_is_model(OCTEONTX_CN9XXX)) */
    }

    return 0;
}


static int encode_row_lsb(int row_lsb)
{
    /*  Decoding for row_lsb             */
    /*       000: row_lsb = mem_adr[14]  */
    /*       001: row_lsb = mem_adr[15]  */
    /*       010: row_lsb = mem_adr[16]  */
    /*       011: row_lsb = mem_adr[17]  */
    /*       100: row_lsb = mem_adr[18]  */
    /*       101: row_lsb = mem_adr[19]  */
    /*       110: row_lsb = mem_adr[20]  */
    /*       111: RESERVED               */

    return row_lsb - 14;
}

static int encode_pbank_lsb(int pbank_lsb)
{
    /*  Decoding for pbank_lsb                                              */
    /*       0000: DIMM = mem_adr[28]    / rank = mem_adr[27] (if RANK_ENA) */
    /*       0001: DIMM = mem_adr[29]    / rank = mem_adr[28]      "        */
    /*       0010: DIMM = mem_adr[30]    / rank = mem_adr[29]      "        */
    /*       0011: DIMM = mem_adr[31]    / rank = mem_adr[30]      "        */
    /*       0100: DIMM = mem_adr[32]    / rank = mem_adr[31]      "        */
    /*       0101: DIMM = mem_adr[33]    / rank = mem_adr[32]      "        */
    /*       0110: DIMM = mem_adr[34]    / rank = mem_adr[33]      "        */
    /*       0111: DIMM = mem_adr[35]    / rank = mem_adr[34]      "        */
    /*       1000: DIMM = mem_adr[36]    / rank = mem_adr[35]      "        */
    /*       1001: DIMM = mem_adr[37]    / rank = mem_adr[36]      "        */
    /*       1010: DIMM = mem_adr[38]    / rank = mem_adr[37]      "        */
    /*       1011: DIMM = mem_adr[39]    / rank = mem_adr[38]      "        */
    /*       1100: DIMM = mem_adr[40]    / rank = mem_adr[39]      "        */
    /*       1101: DIMM = mem_adr[41]    / rank = mem_adr[40]      "        */
    /*       1110: DIMM = 0              / rank = mem_adr[41]      "        */
    /*       1111: RESERVED                                                 */

    return pbank_lsb - 28;
}

/* Setup ECC error reporting (enable or disable) */
void Setup_ECC_Error_Reporting(bdk_node_t node, int lmc, int enable)
{
    if (enable) {
        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            // enable ECC interrupts to allow ECC error info in LMCX_INT
            DRAM_CSR_WRITE(node, BDK_LMCX_INT_ENA_W1S(lmc), -1ULL);
            BDK_CSR_INIT(lmc_int_ena_w1s, node, BDK_LMCX_INT_ENA_W1S(lmc));
            ddr_print("N%d.LMC%d: %-36s : 0x%08lx\n",
                      node, lmc, "LMC_INT_ENA_W1S", lmc_int_ena_w1s.u);
        } else { //CN9XXX
            bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);

            /* Enable ERR00 through ERR03 for Single and Double bit ECC errors */
            DRAM_CSR_WRITE(node, BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(lmc_map.mcc, lmc_map.lmcoe), 0x0F);
            BDK_CSR_INIT(mcc_lmcoe, node, BDK_MCCX_LMCOEX_RAS_INT_ENA_W1S(lmc_map.mcc, lmc_map.lmcoe));
            ddr_print("N%d.LMC%d: %-36s : 0x%08lx\n",
                      node, lmc, "MCC_LMCOE_RAS_INT_ENA_W1S", mcc_lmcoe.u);

        }
    } else { // disable
        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            // disable ECC interrupts to prevent ECC error info in LMCX_INT
            DRAM_CSR_WRITE(node, BDK_LMCX_INT_ENA_W1C(lmc), -1ULL);
            BDK_CSR_INIT(lmc_int_ena_w1c, node, BDK_LMCX_INT_ENA_W1C(lmc));
            ddr_print("N%d.LMC%d: %-36s : 0x%08lx\n",
                      node, lmc, "LMC_INT_ENA_W1C", lmc_int_ena_w1c.u);
        } else { //CN9XXX
            bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);

            /* Disable ERR00 through ERR03 for Single and Double bit ECC errors */
            DRAM_CSR_WRITE(node, BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(lmc_map.mcc, lmc_map.lmcoe), 0x0F);
            BDK_CSR_INIT(mcc_lmcoe, node, BDK_MCCX_LMCOEX_RAS_INT_ENA_W1C(lmc_map.mcc, lmc_map.lmcoe));
            ddr_print("N%d.LMC%d: %-36s : 0x%08lx\n",
                      node, lmc, "MCC_LMCOE_RAS_INT_ENA_W1C", mcc_lmcoe.u);

        }
    }
}

/* LMC(0)_SCRAMBLE_CFG or LMC(0)_ADR_SCRAMBLE */
static void Clear_LMCX_Scrambling(bdk_node_t node, int ddr_interface_num)
{
    // Make sure scrambling is disabled during init...
    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        bdk_lmcx_control_t lmc_control;

        lmc_control.u = BDK_CSR_READ(node, BDK_LMCX_CONTROL(ddr_interface_num));
        lmc_control.s.scramble_ena = 0;
        DRAM_CSR_WRITE(node, BDK_LMCX_CONTROL(ddr_interface_num), lmc_control.u);

        DRAM_CSR_WRITE(node, BDK_LMCX_SCRAMBLE_CFG0(ddr_interface_num), 0);
        DRAM_CSR_WRITE(node, BDK_LMCX_SCRAMBLE_CFG1(ddr_interface_num), 0);
        DRAM_CSR_WRITE(node, BDK_LMCX_SCRAMBLE_CFG2(ddr_interface_num), 0);

    } else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        DRAM_CSR_WRITE(node, BDK_LMCX_ADR_SCRAMBLE(ddr_interface_num), 0); // address mask per LMC
        if (ddr_interface_num < 2) { // LMC2 shares an MCC with LMC0, does not need doing
            bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, ddr_interface_num);
            DRAM_CSR_MODIFY(c, node, BDK_MCCX_CONFIG(lmc_map.mcc), 
                            c.s.scramble_s_ena  = 0; c.s.scramble_ns_ena = 0);
            DRAM_CSR_WRITE(node, BDK_MCCX_SCRAMBLE_CFG0(lmc_map.mcc), 0);
            DRAM_CSR_WRITE(node, BDK_MCCX_SCRAMBLE_CFG1(lmc_map.mcc), 0);
        }
    }
}


/* LMC(0)_CONFIG */
void Setup_LMCX_CONFIG(bdk_node_t node, int lmc, dram_init_data_t *init_data)
{
    bdk_lmcx_config_t           lmc_config;
    int ddr_interface_64b =     init_data->refs.ddr_interface_64b;
    uint64_t tclk_psecs =       init_data->refs.tclk_psecs;
    int rank_mask =             init_data->refs.rank_mask;
    int dram_width =            init_data->refs.dram_width;
    int row_lsb =               init_data->spd.row_lsb;
    int pbank_lsb =             init_data->spd.pbank_lsb;
    int spd_addr_mirror =       init_data->timing.spd_addr_mirror;
    int spd_lrdimm =            init_data->refs.spd_lrdimm;
    int use_ecc =               init_data->refs.use_ecc;
    const char *s;

    lmc_config.u = 0;

    lmc_config.s.ecc_ena         = use_ecc;

    if (bdk_is_model(OCTEONTX_CN9XXX)) { // CN9XXX do MCC also
        bdk_dram_lmc_map_t lmc_map = bdk_dram_get_lmc_map(node, lmc);
        DRAM_CSR_MODIFY(c, node, BDK_MCCX_LMCOEX_CFG(lmc_map.mcc, lmc_map.lmcoe),
                        c.s.dram_ecc_ena = 0; // FIXME: leave this OFF during init!!!
                        c.s.dram_ecc_adr = use_ecc);
    }

    lmc_config.s.row_lsb         = encode_row_lsb(row_lsb);
    lmc_config.s.pbank_lsb       = encode_pbank_lsb(pbank_lsb);

    lmc_config.s.idlepower       = 0; /* Disabled */
    if ((s = lookup_env_parameter("ddr_idlepower")) != NULL) {
        lmc_config.s.idlepower = strtoul(s, NULL, 0);
    }

    lmc_config.s.forcewrite      = 0; /* Disabled */

    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        lmc_config.s.ecc_adr = 1; /* Include memory reference address in the ECC */
        if ((s = lookup_env_parameter("ddr_ecc_adr")) != NULL) {
            lmc_config.s.ecc_adr = strtoul(s, NULL, 0);
        }

        lmc_config.s.early_dqx = 1; /* Default to enabled */
        if ((s = lookup_env_parameter("ddr_early_dqx")) == NULL)
            s = lookup_env_parameter("ddr%d_early_dqx", lmc);
        if (s != NULL) {
            lmc_config.s.early_dqx = strtoul(s, NULL, 0);
        }
        lmc_config.cn83xx.scrz = 0;
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        lmc_config.cn9.bg_mirror_dis = (dram_width == 16);
    }

    lmc_config.s.reset = 0;

    /*
     *  Program LMC0_CONFIG[24:18], ref_zqcs_int(6:0) to
     *  RND-DN(tREFI/clkPeriod/512) Program LMC0_CONFIG[36:25],
     *  ref_zqcs_int(18:7) to
     *  RND-DN(ZQCS_Interval/clkPeriod/(512*128)). Note that this
     *  value should always be greater than 32, to account for
     *  resistor calibration delays.
     */

    //uint64_t tclk_psecs = hertz_to_psecs(ddr_hertz); /* Clock in psecs */

    lmc_config.s.ref_zqcs_int     = ((DDR_tREFI/tclk_psecs/512) & 0x7f);
#if ALLOW_FORCE_2X_REFRESH
    if (ddr_overrides->force_2x_refresh)
        lmc_config.s.ref_zqcs_int = ((DDR_tREFI/2/tclk_psecs/512) & 0x7f);
#endif
    lmc_config.s.ref_zqcs_int   |= ((max(33ull, (DDR_ZQCS_Interval/(tclk_psecs/100)/(512*128))) & 0xfff) << 7);

    lmc_config.s.sref_with_dll   = 0;

    lmc_config.s.rank_ena        = init_data->refs.bunk_enable;
    lmc_config.s.rankmask        = rank_mask; /* Set later */
    lmc_config.s.mirrmask        = (spd_addr_mirror << 1 | spd_addr_mirror << 3) & rank_mask;
    lmc_config.s.init_status     = rank_mask; /* Set once and don't change it. */
    lmc_config.s.early_unload_d0_r0   = 0;
    lmc_config.s.early_unload_d0_r1   = 0;
    lmc_config.s.early_unload_d1_r0   = 0;
    lmc_config.s.early_unload_d1_r1   = 0;

    // set 32-bit mode for real only when selected AND 81xx...
    if (!ddr_interface_64b && bdk_is_model(OCTEONTX_CN81XX)) {
        lmc_config.s.mode32b = 1;
    }
    VB_PRT(VBL_DEV, "%-45s : %d\n", "MODE32B (init)", lmc_config.s.mode32b);

    lmc_config.s.mode_x4dev        = (dram_width == 4) ? 1 : 0;
    lmc_config.s.bg2_enable	   = (dram_width == 16) ? 0 : 1;

    lmc_config.s.lrdimm_ena	   = spd_lrdimm;

    if ((s = lookup_env_parameter_ull("ddr_config")) != NULL) {
        lmc_config.u = strtoull(s, NULL, 0);
    }
    ddr_print("%-45s : 0x%016lx\n", "LMC_CONFIG", lmc_config.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_CONFIG(lmc), lmc_config.u);
}


void Setup_LMCX_CONTROL(bdk_node_t node, int ddr_interface_num,
                        dram_init_data_t *init_data,
                        dram_overrides_t *overrides)
/* LMC(0)_CONTROL */
{
    const ddr_custom_config_t *custom_lmc_config =
        &init_data->ddr_configuration->custom_lmc_config;
    bdk_lmcx_control_t      lmc_control;
    int spd_rdimm =         init_data->refs.spd_rdimm;
    int safe_ddr_flag =     overrides->init.safe_ddr_flag;
    int parity_mode =       overrides->init.parity_mode;
    const char *s;

    lmc_control.u = BDK_CSR_READ(node, BDK_LMCX_CONTROL(ddr_interface_num));
    lmc_control.s.rdimm_ena = spd_rdimm;
    lmc_control.s.bwcnt = 0; /* Clear counter later */
    if (spd_rdimm)
        lmc_control.s.ddr2t = (safe_ddr_flag ? 1 : custom_lmc_config->ddr2t_rdimm );
    else
        lmc_control.s.ddr2t = (safe_ddr_flag ? 1 : custom_lmc_config->ddr2t_udimm );

    // force DDR2T = 0 only if we have enabled parity mode on CN8xxx
    // we have to do this in case we want to inject a parity error
    if (parity_mode && bdk_is_model(OCTEONTX_CN8XXX)) {
        ddr_print("N%d.LMC%d: PARITY: LMCX_CONTROL[ddr2t]: must set to 0\n",
                  node, ddr_interface_num);
        lmc_control.s.ddr2t = 0; // must set to 0 because of RTL bug
    }

    lmc_control.s.pocas = 0;

    // turn ON the POCAS field if doing parity on CN9
    if (parity_mode && bdk_is_model(OCTEONTX_CN9XXX)) {
        ddr_print("N%d.LMC%d: PARITY: LMCX_CONTROL[pocas]: set to 1\n",
                  node, ddr_interface_num);
        lmc_control.s.pocas = 1;
    }

    lmc_control.s.fprch2          = (safe_ddr_flag ? 2 : custom_lmc_config->fprch2 );
    lmc_control.s.inorder_rd      = safe_ddr_flag ? 1 : 0;
    lmc_control.s.inorder_wr      = safe_ddr_flag ? 1 : 0;
    lmc_control.s.nxm_write_en    = 0; /* discards writes to
                                        addresses that don't exist
                                        in the DRAM */
    lmc_control.s.max_write_batch = 8;

    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        lmc_control.cn8.elev_prio_dis     = safe_ddr_flag ? 1 : 0;
        lmc_control.s.throttle_rd         = safe_ddr_flag ? 1 : 0;
        lmc_control.s.throttle_wr         = safe_ddr_flag ? 1 : 0;
        lmc_control.s.xor_bank            = 1;
        lmc_control.cn8.auto_dclkdis      = 1;
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        lmc_control.cn9.wrfl_prio_dis = 0;
        lmc_control.cn9.dclk_force    = 0;
    }

    lmc_control.s.int_zqcs_dis    = 0;
    lmc_control.s.ext_zqcs_dis    = 0;
    lmc_control.s.bprch           = 1;
    lmc_control.s.wodt_bprch      = 1;
    lmc_control.s.rodt_bprch      = 1;

    if ((s = lookup_env_parameter("ddr_xor_bank")) != NULL) {
        lmc_control.s.xor_bank = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_2t")) != NULL) {
        lmc_control.s.ddr2t = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_fprch2")) != NULL) {
        lmc_control.s.fprch2 = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_bprch")) != NULL) {
        lmc_control.s.bprch = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_wodt_bprch")) != NULL) {
        lmc_control.s.wodt_bprch = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_rodt_bprch")) != NULL) {
        lmc_control.s.rodt_bprch = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_int_zqcs_dis")) != NULL) {
        lmc_control.s.int_zqcs_dis = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_ext_zqcs_dis")) != NULL) {
        lmc_control.s.ext_zqcs_dis = strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter_ull("ddr_control")) != NULL) {
        lmc_control.u    = strtoull(s, NULL, 0);
    }

    ddr_print("%-45s : 0x%016lx\n", "LMC_CONTROL", lmc_control.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_CONTROL(ddr_interface_num), lmc_control.u);

    overrides->hw_rlevel.ddr_rlevel_2t = lmc_control.s.ddr2t;
}

/* LMC(0)_DLL_CTL3 */
void Setup_LMCX_DLL_CTL3(bdk_node_t node, int ddr_interface_num,
                         dram_init_data_t *init_data)
{
    bdk_lmcx_dll_ctl3_t lmc_dll_ctl3;

    // Just make sure that wr_deskew_ena is OFF...
    lmc_dll_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_DLL_CTL3(ddr_interface_num));
    lmc_dll_ctl3.s.wr_deskew_ena = 0;

    ddr_print("%-45s : 0x%016lx\n", "LMC_DLL_CTL3", lmc_dll_ctl3.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_DLL_CTL3(ddr_interface_num), lmc_dll_ctl3.u);
}

/* LMC(0)_TIMING_PARAMS0 */
void Setup_LMCX_TIMING_PARAMS0(bdk_node_t node,
                        int ddr_interface_num,
                        dram_init_data_t *init_data)
{
    unsigned trp_value;
    bdk_lmcx_timing_params0_t   lmc_timing_params0;
    uint64_t tclk_psecs =       init_data->refs.tclk_psecs;
    int spd_lrdimm =            init_data->refs.spd_lrdimm;
    int trfc =                  init_data->timing.trfc;
    int trp =                   init_data->timing.trp;
    const char *s;

    lmc_timing_params0.u = BDK_CSR_READ(node, BDK_LMCX_TIMING_PARAMS0(ddr_interface_num));

    trp_value = divide_roundup(trp, tclk_psecs) - 1;

    // only for LRDIMMs, modify TBCW field
    int tbcw = 16;
    if (spd_lrdimm) {
        if ((s = lookup_env_parameter_ull("ddr_lrdimm_tbcw")) != NULL)
            tbcw = strtoull(s, NULL, 0);
        else
            tbcw = 35;
        ddr_print("LRDIMM: TIMING_PARAMS0[tbcw]:  0x%x (%d)\n",  tbcw, tbcw);
    }

    int txpr     = divide_roundup(max(5*tclk_psecs, trfc+10000ull), 16*tclk_psecs);
    int tcksre   = divide_roundup(max(5*tclk_psecs, 10000ull), tclk_psecs) - 1;

    int tzqinit, tzqcs, tcke, tmrd, tmod, tdllk;

    int tdllk_cks = (tclk_psecs < 1071) ? ((tclk_psecs < 833) ? 1024 : 768) : 597;

    tzqinit = 4; // Default to 4, for all DDR4 speed bins
    tzqcs   = divide_roundup(128*tclk_psecs, (16*tclk_psecs)); /* Always 8. */
    tcke    = divide_roundup(max(3*tclk_psecs, (uint64_t) DDR_tCKE), tclk_psecs) - 1;
    tmrd    = divide_roundup((DDR4_tMRD*tclk_psecs), tclk_psecs) - 1;
    tmod    = 25; /* 25 is the max allowed */

    tdllk   = divide_roundup(tdllk_cks, 256);
    int tdllk_old = divide_roundup(DDR4_tDLLK, 256);
    if (tdllk != tdllk_old) {
        VB_PRT(VBL_DEV, "N%d.LMC%d: TIMING_PARAMS0[tdllk] set to %d (was %d)\n",
               node, ddr_interface_num, tdllk, tdllk_old);
    }

    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        lmc_timing_params0.cn8.tbcw     = tbcw;
        lmc_timing_params0.cn8.txpr     = txpr;
        lmc_timing_params0.cn8.trp      = trp_value & 0x1f;
        lmc_timing_params0.cn8.tcksre   = tcksre;
        lmc_timing_params0.cn8.tzqinit  = tzqinit;
        lmc_timing_params0.cn8.tzqcs    = tzqcs;
        lmc_timing_params0.cn8.tcke     = tcke;
        lmc_timing_params0.cn8.tmrd     = tmrd;
        lmc_timing_params0.cn8.tmod     = tmod;
        lmc_timing_params0.cn8.tdllk    = tdllk;
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        lmc_timing_params0.cn9.tbcw     = tbcw;
        lmc_timing_params0.cn9.txpr     = txpr;
        lmc_timing_params0.cn9.trp      = trp_value & 0x3f;
        lmc_timing_params0.cn9.tcksre   = tcksre;
        lmc_timing_params0.cn9.tzqinit  = tzqinit;
        lmc_timing_params0.cn9.tzqcs    = tzqcs;
        lmc_timing_params0.cn9.tcke     = tcke;
        lmc_timing_params0.cn9.tmrd     = tmrd;
        lmc_timing_params0.cn9.tmod     = tmod;
        lmc_timing_params0.cn9.tdllk    = tdllk;
    }

    if ((s = lookup_env_parameter_ull("ddr_timing_params0")) != NULL) {
        lmc_timing_params0.u    = strtoull(s, NULL, 0);
    }
    ddr_print("%-45s : 0x%016lx\n", "TIMING_PARAMS0", lmc_timing_params0.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_TIMING_PARAMS0(ddr_interface_num), lmc_timing_params0.u);

}

/* LMC(0)_TIMING_PARAMS1 */
void Setup_LMCX_TIMING_PARAMS1(bdk_node_t node, int ddr_interface_num,
                               dram_init_data_t *init_data,
                               dram_overrides_t *overrides)
{
    int txp, trcd, trfc_dlr, tras, twtr, trfc, trrd, tfaw, twlmrd, twldqsen, txpdll, temp, tpdm;
    bdk_lmcx_timing_params1_t lmc_timing_params1;
    uint64_t tclk_psecs =  init_data->refs.tclk_psecs;
    int dram_width =       init_data->refs.dram_width;
    int tras_in =          init_data->timing.tras;
    int twtr_in =          init_data->timing.twtr;
    int trfc_in =          init_data->timing.trfc;
    int trrd_in =          init_data->timing.trrd;
    int tfaw_in =          init_data->timing.tfaw;
    int trcd_in =          init_data->timing.trcd;
    int is_3ds_dimm =      init_data->spd.is_3ds_dimm;
    int spd_lrdimm =       init_data->refs.spd_lrdimm;
    int die_capacity =     init_data->spd.die_capacity;
    int parity_mode =      overrides->init.parity_mode;
    const char *s;

    lmc_timing_params1.u = BDK_CSR_READ(node, BDK_LMCX_TIMING_PARAMS1(ddr_interface_num));

    lmc_timing_params1.s.tmprr    = divide_roundup(DDR_tMPRR*tclk_psecs, tclk_psecs) - 1;

    tras     = divide_roundup(tras_in, tclk_psecs) - 1;
    trcd     = divide_roundup(trcd_in, tclk_psecs);
    twtr     = divide_roundup(twtr_in, tclk_psecs) - 1;
    trfc     = divide_roundup(trfc_in, 8*tclk_psecs);
    {
        int trrd_old = divide_roundup(trrd_in, tclk_psecs) - 2;
        int ps = (dram_width < 16) ? (4 * tclk_psecs) : ((tclk_psecs < 1250) ? 5300 : 6000);
        trrd = divide_roundup(max((4 * (int)tclk_psecs), ps), tclk_psecs) - 2;
        if (trrd != trrd_old) {
            // FIXME: verbosity?
            VB_PRT(VBL_DEV, "N%d.LMC%d: TIMING_PARAMS1[trrd] set to %d (was %d)\n",
                   node, ddr_interface_num, trrd, trrd_old);
        }
    }

    temp = (tclk_psecs < 1875) ? 6000 : 7500;
    // NOTE: this is reworked for pass 2.x
    txp = divide_roundup(max(3*tclk_psecs, (unsigned)temp), tclk_psecs) - 1;

    // modify TXP if parity mode is ON
    if (parity_mode) {
        // when parity mode is wanted, bump TXP by ?...
        int new_txp = txp + 5;
        ddr_print("N%d.LMC%d: PARITY: TIMING_PARAMS1[txp] bumped by +%d to %d for parity mode\n",
                  node, ddr_interface_num, new_txp - txp, new_txp);
        txp = new_txp;
    }

    twlmrd   = divide_roundup(DDR_tWLMRD*tclk_psecs, 4*tclk_psecs);
    twldqsen = divide_roundup(DDR_tWLDQSEN*tclk_psecs, 4*tclk_psecs);
    tfaw     = divide_roundup(tfaw_in, 4*tclk_psecs);
    txpdll   = divide_roundup(max(10*tclk_psecs, 24000ull), tclk_psecs) - 1;

    trfc_dlr = 0;
    if (is_3ds_dimm) {
        int trfc_dlr_ns;
        /*
          4 Gb: tRFC_DLR = 90 ns
          8 Gb: tRFC_DLR = 120 ns
          16 Gb: tRFC_DLR = 190 ns FIXME?
         */
        // RNDUP[tRFC_DLR(ns) / (8 * TCYC(ns))]
        if (die_capacity == 0x1000) // 4 Gbit
            trfc_dlr_ns = 90;
        else if (die_capacity == 0x2000) // 8 Gbit
            trfc_dlr_ns = 120;
        else if (die_capacity == 0x4000) // 16 Gbit
            trfc_dlr_ns = 190;
        else
            trfc_dlr_ns = 0;

#if ALLOW_FORCE_2X_REFRESH
        if (ddr_overrides->force_2x_refresh) {
            if (die_capacity == 0x1000) // 4 Gbit
                trfc_dlr_ns = 55;
            else if (die_capacity == 0x2000) // 8 Gbit
                trfc_dlr_ns = 90;
            else if (die_capacity == 0x4000) // 16 Gbit
                trfc_dlr_ns = 120; // FIXME! bogus
        }
#endif

        if (trfc_dlr_ns == 0) {
            ddr_print("N%d.LMC%d: ERROR: tRFC_DLR: die_capacity %u Mbit is illegal\n",
                      node, ddr_interface_num, die_capacity);
        } else {
            trfc_dlr = divide_roundup(trfc_dlr_ns * 1000UL, 8*tclk_psecs);
            ddr_print("N%d.LMC%d: 3DS: TIMING_PARAMS1[trfc_dlr] set to %u (%d)\n",
                      node, ddr_interface_num, trfc_dlr, trfc_dlr_ns);
        }
    } /* if (is_3ds_dimm) */

    tpdm = 1;
    if (spd_lrdimm) {
        tpdm = 0;
        ddr_print("N%d.LMC%d: LRDIMM: TIMING_PARAMS1[tpdm_full_cycle_ena] set to %d\n",
                  node, ddr_interface_num, tpdm);
    }

    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        lmc_timing_params1.cn8.tras     = tras;
        lmc_timing_params1.cn8.trcd     = trcd & 0x0f;
        lmc_timing_params1.cn8.trcd_ext = (trcd >> 4) & 1;
        lmc_timing_params1.cn8.twtr     = twtr;
        lmc_timing_params1.cn8.trfc     = trfc;
        lmc_timing_params1.cn8.trrd     = trrd;
        lmc_timing_params1.cn8.txp      = txp & 7;
        lmc_timing_params1.cn8.txp_ext  = (txp >> 3) & 1;
        lmc_timing_params1.cn8.twlmrd   = twlmrd;
        lmc_timing_params1.cn8.twldqsen = twldqsen;
        lmc_timing_params1.cn8.tfaw     = tfaw;
        lmc_timing_params1.cn8.txpdll   = txpdll;
        lmc_timing_params1.cn8.tpdm_full_cycle_ena = tpdm;
        if (trfc_dlr > 0)
            lmc_timing_params1.cn8.trfc_dlr = trfc_dlr;
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        lmc_timing_params1.cn9.tras     = tras;
        lmc_timing_params1.cn9.trcd     = trcd & 0x3F;
        lmc_timing_params1.cn9.twtr     = twtr;
        lmc_timing_params1.cn9.trfc     = trfc;
        lmc_timing_params1.cn9.trrd     = trrd;
        lmc_timing_params1.cn9.txp      = txp & 0x0F;
        lmc_timing_params1.cn9.twlmrd   = twlmrd;
        lmc_timing_params1.cn9.twldqsen = twldqsen;
        lmc_timing_params1.cn9.tfaw     = tfaw;
        lmc_timing_params1.cn9.txpdll   = txpdll;
        lmc_timing_params1.cn9.tpdm_full_cycle_ena = tpdm;
        if (trfc_dlr > 0)
            lmc_timing_params1.cn9.trfc_dlr = trfc_dlr;
    }

    if ((s = lookup_env_parameter_ull("ddr_timing_params1")) != NULL) {
        lmc_timing_params1.u = strtoull(s, NULL, 0);
    }

    ddr_print("%-45s : 0x%016lx\n", "TIMING_PARAMS1", lmc_timing_params1.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_TIMING_PARAMS1(ddr_interface_num), lmc_timing_params1.u);
}

/* LMC(0)_TIMING_PARAMS2 */
void Setup_LMCX_TIMING_PARAMS2(bdk_node_t node, int ddr_interface_num,
                               dram_init_data_t *init_data)
{
    uint64_t tclk_psecs =   init_data->refs.tclk_psecs;
    int spd_lrdimm =        init_data->refs.spd_lrdimm;
    int ddr4_tRRD_Lmin =    init_data->timing.ddr4_tRRD_Lmin;
    int spd_rdimm =         init_data->refs.spd_rdimm;
    int dram_width =        init_data->refs.dram_width;
    int twr_in =            init_data->timing.twr;
    int trrd_l, twtr_l, t_rw_op_max, trtp, twr = 0, tstab = 0, ps;
    bdk_lmcx_timing_params2_t lmc_timing_params2;
    const char *s;

    lmc_timing_params2.u = BDK_CSR_READ(node, BDK_LMCX_TIMING_PARAMS2(ddr_interface_num));

    int trrd_l_old = divide_roundup(ddr4_tRRD_Lmin, tclk_psecs) - 2;
    if (dram_width < 16) 
        ps = (tclk_psecs < 1250) ? ((tclk_psecs < 938) ? 4900 : 5300) : 6000;
    else
        ps = (tclk_psecs < 1250) ? 6400 : 7500;
    trrd_l = divide_roundup(max((4 * (int)tclk_psecs), ps), tclk_psecs) - 2;
    if (trrd_l != trrd_l_old) {
        // FIXME: verbosity?
        VB_PRT(VBL_DEV, "N%d.LMC%d: TIMING_PARAMS2[trrd_l] set to %d (was %d)\n",
               node, ddr_interface_num, trrd_l, trrd_l_old);
    }

    int twtr_l_old = divide_nint(max(4*tclk_psecs, 7500ull), tclk_psecs) - 1; // correct for 1600-3200
    twtr_l = divide_roundup(max(4*tclk_psecs, 7500ull), tclk_psecs) - 1; // correct for 1600-3200
    if (twtr_l != twtr_l_old) {
        // FIXME: verbosity?
        VB_PRT(VBL_DEV, "N%d.LMC%d: TIMING_PARAMS2[twtr_l] set to %d (was %d)\n",
               node, ddr_interface_num, twtr_l, twtr_l_old);
    }

    t_rw_op_max = (spd_lrdimm) ? 15 : 7; // FIXME?
    trtp = divide_roundup(max(4*tclk_psecs, 7500ull), tclk_psecs) - 1;

    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        twr = divide_roundup(twr_in, tclk_psecs);
        if (twr != lmc_timing_params2.cn9.twr) {
            // FIXME: verbosity?
            VB_PRT(VBL_DEV, "N%d.LMC%d: TIMING_PARAMS2[twr] set to %d (was %d)\n",
                   node, ddr_interface_num, twr, lmc_timing_params2.cn9.twr);
        }
        tstab = divide_roundup(5000000, 512*tclk_psecs); // 5us across the board
        if (tstab != lmc_timing_params2.cn9.tstab) {
            VB_PRT(VBL_DEV, "N%d.LMC%d: TIMING_PARAMS2[tstab] set to %d (was %d)\n",
                   node, ddr_interface_num, tstab, lmc_timing_params2.cn9.tstab);
        }
    }

    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        lmc_timing_params2.cn8.trrd_l      = trrd_l & 7;
        lmc_timing_params2.cn8.trrd_l_ext  = (trrd_l >> 3) & 1;
        lmc_timing_params2.cn8.twtr_l      = twtr_l;
        lmc_timing_params2.cn8.t_rw_op_max = t_rw_op_max;
        lmc_timing_params2.cn8.trtp        = trtp;

        /* Workaround Errata 25823 - LMC: Possible DDR4 tWTR_L not met
           for Write-to-Read operations to the same Bank Group */

        bdk_lmcx_timing_params1_t lmc_timing_params1;
        lmc_timing_params1.u = BDK_CSR_READ(node, BDK_LMCX_TIMING_PARAMS1(ddr_interface_num));

        if (lmc_timing_params1.cn8.twtr < (lmc_timing_params2.cn8.twtr_l - 4)) {
            lmc_timing_params1.cn8.twtr = lmc_timing_params2.cn8.twtr_l - 4;
            VB_PRT(VBL_FAE, "ERRATA 25823: NEW: TWTR: %d, TWTR_L: %d\n",
                   lmc_timing_params1.cn8.twtr, lmc_timing_params2.cn8.twtr_l);
            ddr_print("%-45s : 0x%016lx\n", "TIMING_PARAMS1", lmc_timing_params1.u);
            DRAM_CSR_WRITE(node, BDK_LMCX_TIMING_PARAMS1(ddr_interface_num), lmc_timing_params1.u);
        }
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        lmc_timing_params2.cn9.trrd_l      = trrd_l & 0x0F;
        lmc_timing_params2.cn9.twtr_l      = twtr_l;
        lmc_timing_params2.cn9.t_rw_op_max = t_rw_op_max;
        lmc_timing_params2.cn9.trtp        = trtp;
        lmc_timing_params2.cn9.twr         = twr;
        if (spd_rdimm)
            lmc_timing_params2.cn9.tstab   = tstab;
     }

    if ((s = lookup_env_parameter_ull("ddr_timing_params2")) != NULL) {
        lmc_timing_params2.u = strtoull(s, NULL, 0);
    }

    ddr_print("%-45s : 0x%016lx\n", "TIMING_PARAMS2", lmc_timing_params2.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_TIMING_PARAMS2(ddr_interface_num), lmc_timing_params2.u);
}

void
Setup_LMCX_TIMING_PARAMS_Registers(bdk_node_t node, int ddr_interface_num,
                                   dram_init_data_t *init_data,
                                   dram_overrides_t *overrides)
{
    Setup_LMCX_TIMING_PARAMS0(node, ddr_interface_num, init_data);
    Setup_LMCX_TIMING_PARAMS1(node, ddr_interface_num, init_data, overrides);
    Setup_LMCX_TIMING_PARAMS2(node, ddr_interface_num, init_data);
}


/* LMC(0)_MODEREG_PARAMS0 */
void Setup_LMCX_MODEREG_PARAMS0(bdk_node_t node, int ddr_interface_num,
                                dram_init_data_t *init_data,
                                dram_overrides_t *overrides)
{
    bdk_lmcx_modereg_params0_t lmc_modereg_params0;
    uint64_t tclk_psecs =   init_data->refs.tclk_psecs;
    uint32_t CL_in =        init_data->refs.CL;
    int twr =               init_data->timing.twr;
    //int tCKmin =            init_data->timing.tCKmin;
    int parity_mode =       overrides->init.parity_mode;
    int param;
    const char *s;
    int cwl, cl, wrp;

    lmc_modereg_params0.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num));

    //
    // The settings are from "Table 7 - CWL" in the JEDEC DDR4 spec.
    // Assume: 1 tCK write preamble and 1st "set" from  the table.
    // If we need to use the 2nd "set", just add 2 to CWL.
    //
    cwl = 0; /* 1600 (1250ps) */
    if (tclk_psecs < 750)       cwl = 5; /* 3200 (625ps) and 2933 (638ps) */
    else if (tclk_psecs < 833)  cwl = 4; /* 2666 (750ps) */
    else if (tclk_psecs < 938)  cwl = 3; /* 2400 (833ps) */
    else if (tclk_psecs < 1071) cwl = 2; /* 2133 (938ps) */
    else if (tclk_psecs < 1250) cwl = 1; /* 1866 (1072ps) */

    if ((s = lookup_env_parameter("ddr_cwl")) != NULL) {
        cwl = strtoul(s, NULL, 0);
    }

    ddr_print("%-45s : %d, [0x%x]\n", "CAS Write Latency CWL, [CSR]",
              cwl + 9 + ((cwl > 3) ? (cwl - 3) : 0), cwl);

    if ((s = lookup_env_parameter("ddr_cl")) != NULL) {
        CL_in = strtoul(s, NULL, 0);
        ddr_print("%-45s : %6d\n", "CAS Latency", CL_in);
        init_data->refs.CL = CL_in; // update if it changed...
    }

    cl = 0x0;
    if (CL_in > 24)      cl  = 0xB;
    else if (CL_in > 20) cl  = 0xA;
    else if (CL_in > 18) cl  = 0x9;
    else if (CL_in > 16) cl  = 0x8;
    else if (CL_in > 15) cl  = 0x7;
    else if (CL_in > 14) cl  = 0x6;
    else if (CL_in > 13) cl  = 0x5;
    else if (CL_in > 12) cl  = 0x4;
    else if (CL_in > 11) cl  = 0x3;
    else if (CL_in > 10) cl  = 0x2;
    else if (CL_in > 9)  cl  = 0x1;

#if 1
    // try a different way to calculate
    //                                9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
    static uint8_t xlate_cl_in[23] = {0, 1, 2, 3, 4, 5, 6, 7,13, 8,14, 9,15,10,13,11,16,17,18,19,20,21,22};
    int new_cl = 0;
    if (CL_in > 31)
        new_cl = 23;
    else if (CL_in >= 9)
        new_cl = xlate_cl_in[CL_in - 9];
    VB_PRT(VBL_DEV, "N%d.LMC%d: MODEREG_PARAMS0[cl] set to %d (was %d)\n",
           node, ddr_interface_num, new_cl, cl);
    cl = new_cl;
#endif

    param = divide_roundup(twr, tclk_psecs);

    wrp = 1;
    if (param > 24)      wrp = 7;         /* RESERVED in DDR4 spec */
    else if (param > 20) wrp = 6;
    else if (param > 18) wrp = 5;
    else if (param > 16) wrp = 4;
    else if (param > 14) wrp = 3;
    else if (param > 12) wrp = 2;

#if 1
    // try a different way to calculate
    int new_wrp = (param / 2) - 5;
    if (new_wrp == 7)      new_wrp = 6; // swap 6(24) and 7(22)
    else if (new_wrp == 6) new_wrp = 7; // swap 6(24) and 7(22)
    VB_PRT(VBL_DEV, "N%d.LMC%d: MODEREG_PARAMS0[wrp] set to %d (was %d)\n",
           node, ddr_interface_num, new_wrp, wrp);
    wrp = new_wrp;
#endif

    if ((s = lookup_env_parameter("ddr_wrp")) != NULL) {
        wrp = strtoul(s, NULL, 0);
    }

    // these are common bitfields
    lmc_modereg_params0.s.cwl     = cwl;
    lmc_modereg_params0.s.mprloc  = 0;
    lmc_modereg_params0.s.mpr     = 0;
    lmc_modereg_params0.s.dll     = 1; /* enable(1) for DDR4 */

    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        lmc_modereg_params0.cn8.al      = 0;
        lmc_modereg_params0.cn8.wlev    = 0; /* Read Only */
        lmc_modereg_params0.cn8.tdqs    = 0; /* disable(0) for DDR4 */
        lmc_modereg_params0.cn8.qoff    = 0;
        //lmc_modereg_params0.cn8.bl      = 0; /* Don't touch block dirty logic */
        lmc_modereg_params0.cn8.cl      = cl;
        lmc_modereg_params0.cn8.rbt     = 0; /* Read Only. */
        lmc_modereg_params0.cn8.tm      = 0;
        lmc_modereg_params0.cn8.dllr    = 0;
        lmc_modereg_params0.cn8.wrp     = wrp;
        lmc_modereg_params0.cn8.ppd     = 0;
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        lmc_modereg_params0.cn9.al = 0;
        if (parity_mode) {
            lmc_modereg_params0.cn9.al = 1;
            ddr_print("N%d.LMC%d: PARITY: LMCX_MODEREG_PARAMS0[al]: set to %d\n",
                      node, ddr_interface_num, lmc_modereg_params0.cn9.al);
        }
        lmc_modereg_params0.cn9.wlev    = 0; /* Read Only */
        lmc_modereg_params0.cn9.tdqs    = 0; /* disable(0) for DDR4 */
        lmc_modereg_params0.cn9.qoff    = 0;
        //lmc_modereg_params0.cn9.bl      = 0; /* Don't touch block dirty logic */
        lmc_modereg_params0.cn9.cl      = cl;
        lmc_modereg_params0.cn9.rbt     = 0; /* Read Only. */
        lmc_modereg_params0.cn9.tm      = 0;
        lmc_modereg_params0.cn9.dllr    = 0;
        lmc_modereg_params0.cn9.wrp     = wrp;
        lmc_modereg_params0.cn9.ppd     = 0;
    }

    ddr_print("%-45s : %d, [0x%x]\n", "Write recovery for auto precharge WRP, [CSR]",
              param, wrp);

    if ((s = lookup_env_parameter_ull("ddr_modereg_params0")) != NULL) {
        lmc_modereg_params0.u    = strtoull(s, NULL, 0);
    }

    ddr_print("%-45s : 0x%016lx\n", "MODEREG_PARAMS0", lmc_modereg_params0.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num), lmc_modereg_params0.u);
}


/* LMC(0)_MODEREG_PARAMS1 */
void Setup_LMCX_MODEREG_PARAMS1(bdk_node_t node, int ddr_interface_num,
                                dram_init_data_t *init_data)
{
    bdk_lmcx_modereg_params1_t lmc_modereg_params1;
    int spd_lrdimm =                        init_data->refs.spd_lrdimm;
    const dimm_odt_config_t *odt_config =   init_data->terms.odt_config;
    int dyn_rtt_nom_mask =                  init_data->terms.dyn_rtt_nom_mask;
    uint8_t *rtt_nom =                      init_data->terms.default_rtt_nom;
    int ddr_rtt_nom_auto =                  init_data->terms.ddr_rtt_nom_auto;
    int odt_idx =                           init_data->terms.odt_idx;
    impedence_values_t *imp_values =        init_data->imp_values;
    const char *s;
    int i;
    int rtt_wr[4], rtt_dic[4];

    lmc_modereg_params1.u = odt_config[odt_idx].modereg_params1.u;

    // LRDIMM setup_modereg_params1 pre-processing must be performed here,
    //  to filter in ODT settings from the SPD LRDIMM annex
    if (spd_lrdimm) {
        lrdimm_setup_modereg_params1(node, ddr_interface_num, 
                                     init_data, &lmc_modereg_params1.u);
    }

    /* Save the original rtt_nom settings before sweeping through settings. */
    for (i = 0; i < 4; i++) {
        rtt_nom[i] = EXTR_NOM(lmc_modereg_params1.u, i);
        rtt_wr[i]  = EXTR_WR(lmc_modereg_params1.u, i);
        rtt_dic[i] = EXTR_DIC(lmc_modereg_params1.u, i);
    }

    if ((s = lookup_env_parameter("ddr_rtt_nom_mask")) != NULL) {
        dyn_rtt_nom_mask    = strtoul(s, NULL, 0);
    }

    for (i = 0; i < 4; ++i) {
        uint64_t value;
        if ((s = lookup_env_parameter("ddr_rtt_nom_%1d%1d", !!(i&2), !!(i&1))) == NULL)
            s = lookup_env_parameter("ddr%d_rtt_nom_%1d%1d", ddr_interface_num, !!(i&2), !!(i&1));
        if (s != NULL) {
            value = strtoul(s, NULL, 0);
            INSRT_NOM(&lmc_modereg_params1.u, i, value);
            rtt_nom[i] = value;
            ddr_rtt_nom_auto = 0;
        }
    }

    if ((s = lookup_env_parameter("ddr_rtt_nom")) == NULL)
        s = lookup_env_parameter("ddr%d_rtt_nom", ddr_interface_num);
    if (s != NULL) {
        uint64_t value;
        value = strtoul(s, NULL, 0);
        for (i = 0; i < 4; i++) {
            if (dyn_rtt_nom_mask & (1 << i)) {
                INSRT_NOM(&lmc_modereg_params1.u, i, value);
                rtt_nom[i] = value;
            }
        }
        ddr_rtt_nom_auto = 0;
    }

    if ((s = lookup_env_parameter("ddr_rtt_wr")) != NULL) {
        uint64_t value = strtoul(s, NULL, 0);
        for (i = 0; i < 4; ++i) {
            INSRT_WR(&lmc_modereg_params1.u, i, value);
            rtt_wr[i] = value;
        }
    }

    for (i = 0; i < 4; ++i) {
        uint64_t value;
        if ((s = lookup_env_parameter("ddr_rtt_wr_%1d%1d", !!(i&2), !!(i&1))) == NULL)
            s = lookup_env_parameter("ddr%d_rtt_wr_%1d%1d", ddr_interface_num, !!(i&2), !!(i&1));
        if (s != NULL) {
            value = strtoul(s, NULL, 0);
            INSRT_WR(&lmc_modereg_params1.u, i, value);
            rtt_wr[i] = value;
        }
    }

    if ((s = lookup_env_parameter("ddr_dic")) != NULL) {
        uint64_t value = strtoul(s, NULL, 0);
        for (i = 0; i < 4; ++i) {
            INSRT_DIC(&lmc_modereg_params1.u, i, value);
            rtt_dic[i] = value;
        }
    }

    for (i = 0; i < 4; ++i) {
        uint64_t value;
        if ((s = lookup_env_parameter("ddr_dic_%1d%1d", !!(i&2), !!(i&1))) != NULL) {
            value = strtoul(s, NULL, 0);
            INSRT_DIC(&lmc_modereg_params1.u, i, value);
            rtt_dic[i] = value;
        }
    }

    if ((s = lookup_env_parameter_ull("ddr_modereg_params1")) != NULL) {
        lmc_modereg_params1.u    = strtoull(s, NULL, 0);
    }

    ddr_print("RTT_NOM     %3d, %3d, %3d, %3d ohms           :  %x,%x,%x,%x\n",
              imp_values->rtt_nom_ohms[rtt_nom[3]],
              imp_values->rtt_nom_ohms[rtt_nom[2]],
              imp_values->rtt_nom_ohms[rtt_nom[1]],
              imp_values->rtt_nom_ohms[rtt_nom[0]],
              rtt_nom[3], rtt_nom[2], rtt_nom[1], rtt_nom[0]);

    ddr_print("RTT_WR      %3d, %3d, %3d, %3d ohms           :  %x,%x,%x,%x\n",
              imp_values->rtt_wr_ohms[rtt_wr[3]],
              imp_values->rtt_wr_ohms[rtt_wr[2]],
              imp_values->rtt_wr_ohms[rtt_wr[1]],
              imp_values->rtt_wr_ohms[rtt_wr[0]],
              rtt_wr[3], rtt_wr[2], rtt_wr[1], rtt_wr[0]);

    ddr_print("DIC         %3d, %3d, %3d, %3d ohms           :  %x,%x,%x,%x\n",
              imp_values->dic_ohms[rtt_dic[3]],
              imp_values->dic_ohms[rtt_dic[2]],
              imp_values->dic_ohms[rtt_dic[1]],
              imp_values->dic_ohms[rtt_dic[0]],
              rtt_dic[3], rtt_dic[2], rtt_dic[1], rtt_dic[0]);

    ddr_print("%-45s : 0x%016lx\n", "MODEREG_PARAMS1", lmc_modereg_params1.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS1(ddr_interface_num), lmc_modereg_params1.u);

    init_data->terms.ddr_rtt_nom_auto =     ddr_rtt_nom_auto;
    init_data->terms.dyn_rtt_nom_mask =     dyn_rtt_nom_mask;
}

/* LMC(0)_MODEREG_PARAMS2 */
void Setup_LMCX_MODEREG_PARAMS2(bdk_node_t node, int ddr_interface_num,
                                dram_init_data_t *init_data)
{
    int spd_lrdimm =                        init_data->refs.spd_lrdimm;
    const dimm_odt_config_t *odt_config =   init_data->terms.odt_config;
    int odt_idx =                           init_data->terms.odt_idx;
    impedence_values_t *imp_values =        init_data->imp_values;
    bdk_lmcx_modereg_params2_t lmc_modereg_params2;
    int i;
    const char *s;
    int rtt_park[4];

    lmc_modereg_params2.u = odt_config[odt_idx].modereg_params2.u;

    // LRDIMM setup_modereg_params2 pre-processing must be performed here,
    //  to filter in ODT settings from the SPD LRDIMM annex
    if (spd_lrdimm) {
        lrdimm_setup_modereg_params2(node, ddr_interface_num,
                                     init_data, &lmc_modereg_params2.u);
    }

    // wait until here to unpack the CSR, since the LRDIMM code may make changes
    for (i = 0; i < 4; i++)
        rtt_park[i] = EXTR_PARK(lmc_modereg_params2.u, i);

    for (i = 0; i < 4; ++i) {
        uint64_t value;
        if ((s = lookup_env_parameter("ddr_rtt_park_%1d%1d", !!(i&2), !!(i&1))) != NULL) {
            value = strtoul(s, NULL, 0);
            INSRT_PARK(&lmc_modereg_params2.u, i, value);
            rtt_park[i] = value;
        }
    }

    if ((s = lookup_env_parameter("ddr_rtt_park")) != NULL) {
        uint64_t value = strtoul(s, NULL, 0);
        for (i = 0; i < 4; ++i) {
            INSRT_PARK(&lmc_modereg_params2.u, i, value);
            rtt_park[i] = value;
        }
    }

    if ((s = lookup_env_parameter_ull("ddr_modereg_params2")) != NULL) {
        lmc_modereg_params2.u    = strtoull(s, NULL, 0);
    }

    ddr_print("RTT_PARK    %3d, %3d, %3d, %3d ohms           :  %x,%x,%x,%x\n",
              imp_values->rtt_nom_ohms[rtt_park[3]],
              imp_values->rtt_nom_ohms[rtt_park[2]],
              imp_values->rtt_nom_ohms[rtt_park[1]],
              imp_values->rtt_nom_ohms[rtt_park[0]],
              rtt_park[3], rtt_park[2], rtt_park[1], rtt_park[0]);

    ddr_print("%-45s :  0x%x,0x%x,0x%x,0x%x\n", "VREF_RANGE",
              lmc_modereg_params2.s.vref_range_11,
              lmc_modereg_params2.s.vref_range_10,
              lmc_modereg_params2.s.vref_range_01,
              lmc_modereg_params2.s.vref_range_00);

    ddr_print("%-45s :  0x%x,0x%x,0x%x,0x%x\n", "VREF_VALUE",
              lmc_modereg_params2.s.vref_value_11,
              lmc_modereg_params2.s.vref_value_10,
              lmc_modereg_params2.s.vref_value_01,
              lmc_modereg_params2.s.vref_value_00);

    ddr_print("%-45s : 0x%016lx\n", "MODEREG_PARAMS2", lmc_modereg_params2.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS2(ddr_interface_num), lmc_modereg_params2.u);
}


/* LMC(0)_MODEREG_PARAMS3 */
void Setup_LMCX_MODEREG_PARAMS3(bdk_node_t node, int ddr_interface_num,
                                dram_init_data_t *init_data)
{
    bdk_lmcx_modereg_params3_t lmc_modereg_params3;
    uint64_t tclk_psecs =       init_data->refs.tclk_psecs;
    uint64_t ddr_hertz =        init_data->refs.ddr_hertz;
    int ddr4_tCCD_Lmin =        init_data->timing.ddr4_tCCD_Lmin;
    int lranks_per_prank =      init_data->spd.lranks_per_prank;
    const char *s;

    lmc_modereg_params3.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS3(ddr_interface_num));

    lmc_modereg_params3.s.tccd_l = max(divide_roundup(ddr4_tCCD_Lmin, tclk_psecs), 5ull) - 4;

#if ALLOW_FORCE_2X_REFRESH
    lmc_modereg_params3.s.fgrm = force_2x_refresh;
#endif

    if ((s = lookup_env_parameter_ull("ddr_rd_preamble")) != NULL) {
        lmc_modereg_params3.s.rd_preamble = !!strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter_ull("ddr_wr_preamble")) != NULL) {
        lmc_modereg_params3.s.wr_preamble = !!strtoul(s, NULL, 0);
    }

    int delay = 0;
    if ((lranks_per_prank == 4) && (ddr_hertz >= 1000000000))
        delay = 1;
    lmc_modereg_params3.s.xrank_add_tccd_l = delay;
    lmc_modereg_params3.s.xrank_add_tccd_s = delay;

    ddr_print("%-45s : 0x%016lx\n", "MODEREG_PARAMS3", lmc_modereg_params3.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS3(ddr_interface_num), lmc_modereg_params3.u);
}

void Setup_LMCX_MODEREG_PARAMS_Registers(bdk_node_t node,
                                         int ddr_interface_num,
                                         dram_init_data_t *init_data,
                                         dram_overrides_t *overrides)
{
    Setup_LMCX_MODEREG_PARAMS0(node, ddr_interface_num, init_data, overrides);
    Setup_LMCX_MODEREG_PARAMS1(node, ddr_interface_num, init_data);
    Setup_LMCX_MODEREG_PARAMS2(node, ddr_interface_num, init_data);
    Setup_LMCX_MODEREG_PARAMS3(node, ddr_interface_num, init_data);
}

/* LMC(0)_NXM */
void Setup_LMCX_NXM(bdk_node_t node,
                    int ddr_interface_num,
                    dram_init_data_t *init_data)
{
    bdk_lmcx_nxm_t lmc_nxm;
    int rank_mask =     init_data->refs.rank_mask;
    int row_lsb =       init_data->spd.row_lsb;
    int row_bits =      init_data->spd.row_bits;
    int lranks_bits =   init_data->spd.lranks_bits;
    const char *s;

    int num_bits = row_lsb + row_bits + lranks_bits - 26;
    lmc_nxm.u = BDK_CSR_READ(node, BDK_LMCX_NXM(ddr_interface_num));

    if (rank_mask & 0x1)
        lmc_nxm.s.mem_msb_d0_r0 = num_bits;
    if (rank_mask & 0x2)
        lmc_nxm.s.mem_msb_d0_r1 = num_bits;
    if (rank_mask & 0x4)
        lmc_nxm.s.mem_msb_d1_r0 = num_bits;
    if (rank_mask & 0x8)
        lmc_nxm.s.mem_msb_d1_r1 = num_bits;

    lmc_nxm.s.cs_mask = ~rank_mask & 0xff; /* Set the mask for non-existant ranks. */

    if ((s = lookup_env_parameter_ull("ddr_nxm")) != NULL) {
        lmc_nxm.u    = strtoull(s, NULL, 0);
    }
    ddr_print("%-45s : 0x%016lx\n", "LMC_NXM", lmc_nxm.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_NXM(ddr_interface_num), lmc_nxm.u);
}

/* LMC(0)_WODT_MASK */
void Setup_LMCX_WODT_MASK(bdk_node_t node, int ddr_interface_num,
                          dram_init_data_t *init_data)
{
    bdk_lmcx_wodt_mask_t lmc_wodt_mask;
    int odt_idx =       init_data->terms.odt_idx;
    lmc_wodt_mask.u =   init_data->terms.odt_config[odt_idx].wodt_mask;
    const char *s;

    if ((s = lookup_env_parameter_ull("ddr_wodt_mask")) != NULL) {
        lmc_wodt_mask.u    = strtoull(s, NULL, 0);
    }

    ddr_print("%-45s : 0x%016lx\n", "WODT_MASK", lmc_wodt_mask.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_WODT_MASK(ddr_interface_num), lmc_wodt_mask.u);
}

/* LMC(0)_RODT_MASK */
void Setup_LMCX_RODT_MASK(bdk_node_t node, int ddr_interface_num,
                          dram_init_data_t *init_data)
{
    bdk_lmcx_rodt_mask_t lmc_rodt_mask;
    int odt_idx =       init_data->terms.odt_idx;
    lmc_rodt_mask.u =   init_data->terms.odt_config[odt_idx].rodt_mask;
    int rank_mask =     init_data->refs.rank_mask;
    int num_ranks =     init_data->refs.num_ranks;
    int rankx;
    const char *s;

    if ((s = lookup_env_parameter_ull("ddr_rodt_mask")) != NULL) {
        lmc_rodt_mask.u    = strtoull(s, NULL, 0);
    }

    ddr_print("%-45s : 0x%016lx\n", "RODT_MASK", lmc_rodt_mask.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_RODT_MASK(ddr_interface_num), lmc_rodt_mask.u);

    int dyn_rtt_nom_mask = 0;
    for (rankx = 0; rankx < 4;rankx++) {
        if (!(rank_mask & (1 << rankx)))
            continue;
        dyn_rtt_nom_mask |= ((lmc_rodt_mask.u >> (8*rankx)) & 0xff);
    }
    if (num_ranks == 4) {
        /* Normally ODT1 is wired to rank 1. For quad-ranked DIMMs
           ODT1 is wired to the third rank (rank 2).  The mask,
           dyn_rtt_nom_mask, is used to indicate for which ranks
           to sweep RTT_NOM during read-leveling. Shift the bit
           from the ODT1 position over to the "ODT2" position so
           that the read-leveling analysis comes out right. */
        int odt1_bit = dyn_rtt_nom_mask & 2;
        dyn_rtt_nom_mask &= ~2;
        dyn_rtt_nom_mask |= odt1_bit<<1;
    }

    ddr_print("%-45s : 0x%02x\n", "DYN_RTT_NOM_MASK", dyn_rtt_nom_mask);

    init_data->terms.dyn_rtt_nom_mask = dyn_rtt_nom_mask;
}

/* LMC(0)_COMP_CTL2 */
void Setup_LMCX_COMP_CTL2(bdk_node_t node, int ddr_interface_num,
                          dram_init_data_t *init_data)
{
    bdk_lmcx_comp_ctl2_t comp_ctl2;
    const ddr_custom_config_t *custom_lmc_config = &init_data->ddr_configuration->custom_lmc_config;
    const dimm_odt_config_t *odt_config =   init_data->terms.odt_config;
    int odt_idx =                           init_data->terms.odt_idx;
    int ddr_rodt_ctl_auto =                 init_data->terms.ddr_rodt_ctl_auto;
    impedence_values_t *imp_values =        init_data->imp_values;
    uint64_t ddr_hertz =                    init_data->refs.ddr_hertz;
    int dimm_count =                        init_data->refs.dimm_count;
    int spd_dimm_type =                     init_data->refs.spd_dimm_type;
    const char *s;

    comp_ctl2.u = BDK_CSR_READ(node, BDK_LMCX_COMP_CTL2(ddr_interface_num));

    comp_ctl2.s.dqx_ctl	= odt_config[odt_idx].dqx_ctl;
    if ((s = lookup_env_parameter("ddr_dqx_ctl")) != NULL) { // allow override
        comp_ctl2.s.dqx_ctl  = strtoul(s, NULL, 0);
    }

    // NOTE: these are now done earlier, in Step 6.9.3
    // comp_ctl2.s.ntune_offset    = 0;
    // comp_ctl2.s.ptune_offset    = 0;
    //
    // comp_ctl2.s.ck_ctl = driver_default; /* Default 34 or 30 ohm */
    // comp_ctl2.s.cmd_ctl = driver_default; /* Default 34 or 30 ohm */
    // comp_ctl2.s.control_ctl = driver_default; /* Default 34 or 30 ohm */
    //
    //  and any board configuration overrides of the above 3 fields

    ddr_rodt_ctl_auto = custom_lmc_config->ddr_rodt_ctl_auto;
    if ((s = lookup_env_parameter("ddr_rodt_ctl_auto")) != NULL) {
        ddr_rodt_ctl_auto = !!strtoul(s, NULL, 0);
    }

    int default_rodt_ctl = odt_config[odt_idx].rodt_ctl;

    // allow rodt_ctl to be overridden...
    if ((s = lookup_env_parameter("ddr_rodt_ctl")) == NULL)
        s = lookup_env_parameter("ddr%d_rodt_ctl", ddr_interface_num);
    if (s != NULL) {
        default_rodt_ctl    = strtoul(s, NULL, 0);
        ddr_rodt_ctl_auto = 0;
    }

    comp_ctl2.s.rodt_ctl = default_rodt_ctl;

    // pick the closest to 26 ohms if we need to modify for speed
    int driver_26_ohm = CN8_OR_CN9(ddr4_driver_26_ohm, ddr4_driver_27_ohm_cn9);

    // if DDR4, force CK_CTL to 26 ohms if it is currently the default, and DCLK speed is 1 GHz or more...
        // but allow no override if the custom setting is not the default.
    if ((ddr_hertz >= 1000000000) &&
        (custom_lmc_config->ck_ctl == 0))
    {
        comp_ctl2.s.ck_ctl = driver_26_ohm;
        ddr_print("Forcing DDR4 COMP_CTL2[CK_CTL] to %d, %d ohms\n",
                  driver_26_ohm, imp_values->drive_strength[driver_26_ohm]);
    }

    // if DDR4, 2DPC, UDIMM, force CONTROL_CTL and CMD_CTL to 26 ohms,
    // when DCLK speed is 1 GHz or more...
    // but allow no override if the custom setting is not the default.
    if ((dimm_count == 2) &&
        ((spd_dimm_type == 2) || (spd_dimm_type == 6)) &&
        (ddr_hertz >= 1000000000))
    {
        if (custom_lmc_config->ctl_ctl == 0) { // allow override if default
            comp_ctl2.s.control_ctl = driver_26_ohm;
            ddr_print("N%d.LMC%d: Forcing DDR4 COMP_CTL2[CONTROL_CTL] to %d, %d ohms\n",
                      node, ddr_interface_num, driver_26_ohm,
                      imp_values->drive_strength[driver_26_ohm]);
        }
        if (custom_lmc_config->cmd_ctl == 0) { // allow override if default
            comp_ctl2.s.cmd_ctl = driver_26_ohm;
            ddr_print("N%d.LMC%d: Forcing DDR4 COMP_CTL2[CMD_CTL] to %d, %d ohms\n",
                      node, ddr_interface_num, driver_26_ohm,
                      imp_values->drive_strength[driver_26_ohm]);
        }
    }

    ddr_print("%-45s : %d, %d ohms\n", "DQX_CTL           ", comp_ctl2.s.dqx_ctl,
      imp_values->dqx_strength  [comp_ctl2.s.dqx_ctl    ]);
    ddr_print("%-45s : %d, %d ohms\n", "CK_CTL            ", comp_ctl2.s.ck_ctl,
      imp_values->drive_strength[comp_ctl2.s.ck_ctl     ]);
    ddr_print("%-45s : %d, %d ohms\n", "CMD_CTL           ", comp_ctl2.s.cmd_ctl,
      imp_values->drive_strength[comp_ctl2.s.cmd_ctl    ]);
    ddr_print("%-45s : %d, %d ohms\n", "CONTROL_CTL       ", comp_ctl2.s.control_ctl,
      imp_values->drive_strength[comp_ctl2.s.control_ctl]);
    ddr_print("%-45s : 0x%x (%d ohms)\n", "Read ODT_CTL",
              comp_ctl2.s.rodt_ctl, imp_values->rodt_ohms[comp_ctl2.s.rodt_ctl]);

    DRAM_CSR_WRITE(node, BDK_LMCX_COMP_CTL2(ddr_interface_num), comp_ctl2.u);

    init_data->terms.ddr_rodt_ctl_auto =    ddr_rodt_ctl_auto;
    init_data->terms.default_rodt_ctl =     default_rodt_ctl;
}

/* LMC(0)_PHY_CTL */
void Setup_LMCX_PHY_CTL(bdk_node_t node, int ddr_interface_num,
                        dram_init_data_t *init_data,
                        dram_overrides_t *overrides)
{
    bdk_lmcx_phy_ctl_t lmc_phy_ctl;
    int num_ranks        = init_data->refs.num_ranks;
    int dimm_count       = init_data->refs.dimm_count;
    int is_stacked_die   = init_data->spd.is_stacked_die;
    int lranks_per_prank = init_data->spd.lranks_per_prank;

    lmc_phy_ctl.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL(ddr_interface_num));
    lmc_phy_ctl.s.ts_stagger           = 0;
    lmc_phy_ctl.s.phy_dsk_lock_en      = 1;
    lmc_phy_ctl.s.dsk_dbg_overwrt_ena  = 0; // FIXME: are there others TBD?

    if (bdk_is_model(OCTEONTX_CN8XXX) && (lranks_per_prank > 1)) {
        lmc_phy_ctl.cn83xx.c0_sel = lmc_phy_ctl.cn83xx.c1_sel = 2; // C0 is TEN, C1 is A17
        ddr_print("N%d.LMC%d: 3DS: setting PHY_CTL[cx_csel] = %d\n",
                  node, ddr_interface_num, lmc_phy_ctl.cn8.c1_sel);
    }

    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        if (is_stacked_die && (dimm_count == 1) && (num_ranks == 4)) {
            // set both C0_CS2 and C1_CS3 switches
            lmc_phy_ctl.cn9.c0_cs2_switch = lmc_phy_ctl.cn9.c1_cs3_switch = 1;
            ddr_print("N%d.LMC%d: 4RANK: setting PHY_CTL[cX_csY] = %d\n",
                      node, ddr_interface_num, lmc_phy_ctl.cn9.c0_cs2_switch);
        }
        lmc_phy_ctl.cn9.double_vref_training = overrides->init.double_vref_training;
    }

    ddr_print("%-45s : 0x%016lx\n", "PHY_CTL", lmc_phy_ctl.u);
    DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL(ddr_interface_num), lmc_phy_ctl.u);
}

/* LMC(0)_EXT_CONFIG */

void Setup_LMCX_EXT_CONFIG(bdk_node_t node, int ddr_interface_num,
                           dram_init_data_t *init_data,
                           dram_overrides_t *overrides)
{
    bdk_lmcx_ext_config_t   ext_config;
    int lranks_bits =       init_data->spd.lranks_bits;
    int lranks_per_prank =  init_data->spd.lranks_per_prank;
    int data_invert =       overrides->init.data_invert;
    int use_scramble =      overrides->init.use_scramble;
    const char *s;

    ext_config.u = BDK_CSR_READ(node, BDK_LMCX_EXT_CONFIG(ddr_interface_num));
    ext_config.s.vrefint_seq_deskew = 0;
    ext_config.s.read_ena_bprch = 1;
    ext_config.s.read_ena_fprch = 1;
    ext_config.s.drive_ena_fprch = 1;
    ext_config.s.drive_ena_bprch = 1;

    // On CN8XXX, we cannot do both data invert and scrambling, so we choose scrambling
    if (bdk_is_model(OCTEONTX_CN8XXX) && data_invert && (use_scramble != 0)) {
        ddr_print("N%d.LMC%d: DATA_INVERT: Cannot combine with scrambling on CN8XXX; ignoring.\n",
                  node, ddr_interface_num);
        data_invert = 0;
    }

    // only print when we are NOT using the chip default...
    ext_config.s.invert_data = data_invert;
    if ((data_invert && bdk_is_model(OCTEONTX_CN8XXX)) || // default is 0 for CN8
        (!data_invert && bdk_is_model(OCTEONTX_CN9XXX)))  // default is 1 for CN9
    {
        ddr_print("N%d.LMC%d: DATA_INVERT: Setting EXT_CONFIG[invert_data] = %d.\n",
                  node, ddr_interface_num, data_invert);
    }

    if ((s = lookup_env_parameter("ddr_read_fprch")) != NULL) {
        ext_config.s.read_ena_fprch = !!strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_read_bprch")) != NULL) {
        ext_config.s.read_ena_bprch = !!strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_drive_fprch")) != NULL) {
        ext_config.s.drive_ena_fprch = !!strtoul(s, NULL, 0);
    }
    if ((s = lookup_env_parameter("ddr_drive_bprch")) != NULL) {
        ext_config.s.drive_ena_bprch = !!strtoul(s, NULL, 0);
    }

    if (lranks_per_prank > 1) {
        ext_config.s.dimm0_cid = ext_config.s.dimm1_cid = lranks_bits;
        ddr_print("N%d.LMC%d: 3DS: setting EXT_CONFIG[dimmx_cid] = %d\n",
                  node, ddr_interface_num, ext_config.s.dimm0_cid);
    }

    Setup_EXT_CONFIG_for_parity_mode(node, ddr_interface_num, init_data, overrides, &ext_config);

    DRAM_CSR_WRITE(node, BDK_LMCX_EXT_CONFIG(ddr_interface_num), ext_config.u);
    ddr_print("%-45s : 0x%016lx\n", "EXT_CONFIG", ext_config.u);
}

/* LMC(0)_EXT_CONFIG2 */
void Setup_LMCX_EXT_CONFIG2(bdk_node_t node, int ddr_interface_num,
                            dram_init_data_t *init_data)
{
    int spd_lrdimm =        init_data->refs.spd_lrdimm;
    int spd_rdimm =         init_data->refs.spd_rdimm;
    uint64_t ddr_hertz =    init_data->refs.ddr_hertz;
    const char *s;
    bdk_lmcx_ext_config2_t ext_config2;
    int value = 1; // default unloads to 1

    ext_config2.u = BDK_CSR_READ(node, BDK_LMCX_EXT_CONFIG2(ddr_interface_num));

    if ((s = lookup_env_parameter("ddr_ext2_delay_unload")) != NULL) {
        value = !!strtoul(s, NULL, 0);
    }

    if (bdk_is_model(OCTEONTX_CN8XXX)) {
        int early_dqx2 = 0;

        if (spd_lrdimm) {
            early_dqx2 = 1; // FIXME: allow override?
            ddr_print("N%d.LMC%d: LRDIMM: setting EXT_CONFIG2[early_dqx2] = %d\n",
                      node, ddr_interface_num, early_dqx2);
        }

        ext_config2.cn8.delay_unload_r0 = value;
        ext_config2.cn8.delay_unload_r1 = value;
        ext_config2.cn8.delay_unload_r2 = value;
        ext_config2.cn8.delay_unload_r3 = value;
        ext_config2.cn8.early_dqx2 = early_dqx2;
    }
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
        // follow CN8 setting for early_dqx, unless RDIMM and speed is >= 2933 MT/s
        int early_dqx = (spd_rdimm && ddr_hertz >= 1466000000UL) ? 0 : 1;

        if (early_dqx == 0) { // we modified the default
            ddr_print("N%d.LMC%d: RDIMM at high speed: setting EXT_CONFIG2[early_dqx] = %d\n",
                      node, ddr_interface_num, early_dqx);
        }

        if (spd_lrdimm)
            early_dqx += 1; // add 1 if an LRDIMM

        // allow override
        if ((s = lookup_env_parameter("ddr_early_dqx")) == NULL)
            s = lookup_env_parameter("ddr%d_early_dqx", ddr_interface_num);
        if (s != NULL) {
            early_dqx = strtoul(s, NULL, 0);
        }

        if (spd_lrdimm) {
            ddr_print("N%d.LMC%d: LRDIMM: setting EXT_CONFIG2[early_dqx] = %d\n",
                      node, ddr_interface_num, early_dqx);
        }

        // FIXME: for now, same settings on the delay_unloads as CN8XXX
        ext_config2.cn9.delay_unload_r0 = value;
        ext_config2.cn9.delay_unload_r1 = value;
        ext_config2.cn9.delay_unload_r2 = value;
        ext_config2.cn9.delay_unload_r3 = value;
        ext_config2.cn9.early_dqx = early_dqx;
    }

    DRAM_CSR_WRITE(node, BDK_LMCX_EXT_CONFIG2(ddr_interface_num), ext_config2.u);
    ddr_print("%-45s : 0x%016lx\n", "EXT_CONFIG2", ext_config2.u);
}

void Setup_LMCX_EXT_CONFIGX_Bank_Hash(bdk_node_t node,
                                      int ddr_interface_num,
                                      dram_init_data_t *init_data)
{
    // for CN9 and x16 DRAM devices, must do special configuration
    DRAM_CSR_MODIFY(c, node, BDK_LMCX_EXT_CONFIG2(ddr_interface_num),
                    c.cn9.ba0_hash_sel = (c.cn9.ba0_hash_sel & ~0x0F) | 0x02);
    DRAM_CSR_MODIFY(c, node, BDK_LMCX_EXT_CONFIG3(ddr_interface_num),
                    c.s.ba1_hash_sel = (c.s.ba1_hash_sel & ~0x0F) | 0x04);

    // Currently disabled, as these are the same as RESET values or are do not care...
    /*
    DRAM_CSR_MODIFY(c, node, BDK_LMCX_EXT_CONFIG4(ddr_interface_num),
                    c.s.bg0_hash_sel = (c.s.bg0_hash_sel & ~0x0F) | 0x01);
    DRAM_CSR_MODIFY(c, node, BDK_LMCX_EXT_CONFIG5(ddr_interface_num),
                    c.s.bg1_hash_sel = (c.s.bg1_hash_sel & ~0x0F) | 0x02);
    */

    ddr_print("N%d.LMC%d: Adjusted bank hash selections for x16 DRAM\n",
              node, ddr_interface_num);
}

void Setup_LMCX_EXT_CONFIG_Registers(bdk_node_t node,
                                     int ddr_interface_num,
                                     dram_init_data_t *init_data,
                                     dram_overrides_t *overrides)
{
    int dram_width =            init_data->refs.dram_width;

    Setup_LMCX_EXT_CONFIG(node, ddr_interface_num, init_data, overrides);
    Setup_LMCX_EXT_CONFIG2(node, ddr_interface_num, init_data);

    if (bdk_is_model(OCTEONTX_CN9XXX) && (dram_width == 16)) {
        Setup_LMCX_EXT_CONFIGX_Bank_Hash(node, ddr_interface_num, init_data);
    }
}

/* LMC(0)_PHY_CTL3 */
void Setup_LMCX_PHY_CTL3(bdk_node_t node, int ddr_interface_num,
                         dram_init_data_t *init_data)
{
    // only for CN9XXX
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        bdk_lmcx_phy_ctl3_t phy_ctl3;
        int rank_mask  = init_data->refs.rank_mask;
        int spd_rdimm  = init_data->refs.spd_rdimm;
        int dimm_count = init_data->refs.dimm_count;

        phy_ctl3.u = BDK_CSR_READ(node, BDK_LMCX_PHY_CTL3(ddr_interface_num));

        // assumption is that all the DIMMx_CKy are NOT set after cold RESET

        // HRM-CN9XXX Section 7.9.6.7
        /* When interfacing with RDIMM or NVDIMM systems in a two DIMMs per
           channel application, be sure to turn off CK pairs 1 and 3 by writing
           the following CSRs:
           LMC(0..2)_PHY_CTL3[DDR_DIMM0_CK1_EN_CLEAR]
           LMC(0..2)_PHY_CTL3[DDR_DIMM1_CK1_EN_CLEAR]
           Furthermore, in a one DIMM per channel application, also turn off:
           LMC(0..2)_PHY_CTL3[DDR_DIMM1_CK1_EN_CLEAR]
        */
        if (rank_mask & 1) phy_ctl3.s.ddr_dimm0_ck0_en_set = 1;
        if ((rank_mask & 2) && !spd_rdimm)  phy_ctl3.s.ddr_dimm0_ck1_en_set = 1;
        if ((rank_mask & 4) && !(dimm_count == 1)) phy_ctl3.s.ddr_dimm1_ck0_en_set = 1;
        if ((rank_mask & 8) && !spd_rdimm)  phy_ctl3.s.ddr_dimm1_ck1_en_set = 1;

        DRAM_CSR_WRITE(node, BDK_LMCX_PHY_CTL3(ddr_interface_num), phy_ctl3.u);
    }
}

static int compute_rc3x (int64_t tclk_psecs)
{
    long speed;
    long tclk_psecs_min, tclk_psecs_max;
    long data_rate_mhz, data_rate_mhz_min, data_rate_mhz_max;
    int rc3x;

#define ENCODING_BASE 1240

    data_rate_mhz = psecs_to_mts(tclk_psecs);

    /* 2400 MT/s is a special case. Using integer arithmetic it rounds
       from 833 psecs to 2401 MT/s. Force it to 2400 to pick the
       proper setting from the table. */
    if (tclk_psecs == 833)
        data_rate_mhz = 2400;

    for (speed = ENCODING_BASE; speed < 3200; speed += 20) {
        int error = 0;

        tclk_psecs_min = hertz_to_psecs(mts_to_hertz(speed + 00)); /* Clock in psecs */
        tclk_psecs_max = hertz_to_psecs(mts_to_hertz(speed + 18)); /* Clock in psecs */

        data_rate_mhz_min = psecs_to_mts(tclk_psecs_min);
        data_rate_mhz_max = psecs_to_mts(tclk_psecs_max);

        /* Force alingment to multiple to avound rounding errors. */
        data_rate_mhz_min = ((data_rate_mhz_min + 18) / 20) * 20;
        data_rate_mhz_max = ((data_rate_mhz_max + 18) / 20) * 20;

        error += (speed + 00 != data_rate_mhz_min);
        error += (speed + 20 != data_rate_mhz_max);

        rc3x = (speed - ENCODING_BASE) / 20;

        rc3x_print("rc3x: %02x speed: %4ld MT/s < f <= %4ld MT/s, psec: %3ld:%3ld %4ld:%4ld %s\n",
                   rc3x, speed, speed + 20, tclk_psecs_min, tclk_psecs_max,
                   data_rate_mhz_min, data_rate_mhz_max, error ? "****" : "");

        if (data_rate_mhz <= (speed + 20)) {
            rc3x_print("rc3x: %4ld MT/s <= %4ld MT/s\n", data_rate_mhz, speed + 20);
            break;
        }
    }
    return rc3x;
}

/* LMC(0)_DIMM0/1_PARAMS */
void Setup_LMCX_DIMMX_PARAMS(bdk_node_t node, int ddr_interface_num,
                             dram_init_data_t *init_data)
{
    const dimm_config_t *dimm_config_table = init_data->ddr_configuration->dimm_config_table;
    const ddr_custom_config_t *custom_lmc_config = &init_data->ddr_configuration->custom_lmc_config;
    int dimm_count =            init_data->refs.dimm_count;
    uint64_t tclk_psecs =       init_data->refs.tclk_psecs;
    int num_ranks =             init_data->refs.num_ranks;
    int rank_mask =             init_data->refs.rank_mask;
    int spd_rdimm =             init_data->refs.spd_rdimm;
    int spd_lrdimm =            init_data->refs.spd_lrdimm;
    int spd_addr_mirror =       init_data->timing.spd_addr_mirror;
    //int spd_rdimm_registers =   init_data->spd.spd_rdimm_registers;
    unsigned didx;
    int i;
    const char *s;

    if (spd_rdimm) {
        bdk_lmcx_dimm_ctl_t lmc_dimm_ctl;

        for (didx = 0; didx < (unsigned)dimm_count; ++didx) {
            bdk_lmcx_dimmx_params_t lmc_dimmx_params;
            int dimm = didx;
            int rc;

            lmc_dimmx_params.u = 0;

            bdk_lmcx_dimmx_ddr4_params0_t lmc_dimmx_ddr4_params0;
            bdk_lmcx_dimmx_ddr4_params1_t lmc_dimmx_ddr4_params1;
            bdk_lmcx_ddr4_dimm_ctl_t lmc_ddr4_dimm_ctl;

            //lmc_dimmx_params.s.rc0  = 0;
            //lmc_dimmx_params.s.rc1  = 0;
            //lmc_dimmx_params.s.rc2  = 0;

            rc = read_spd(node, &dimm_config_table[didx], DDR4_SPD_RDIMM_REGISTER_DRIVE_STRENGTH_CTL);
            lmc_dimmx_params.s.rc3  = (rc >> 4) & 0xf;
            lmc_dimmx_params.s.rc4  = ((rc >> 0) & 0x3) << 2;
            lmc_dimmx_params.s.rc4 |= ((rc >> 2) & 0x3) << 0;

            rc = read_spd(node, &dimm_config_table[didx], DDR4_SPD_RDIMM_REGISTER_DRIVE_STRENGTH_CK);
            lmc_dimmx_params.s.rc5  = ((rc >> 0) & 0x3) << 2;
            lmc_dimmx_params.s.rc5 |= ((rc >> 2) & 0x3) << 0;

            //lmc_dimmx_params.s.rc6  = 0;
            //lmc_dimmx_params.s.rc7  = 0;
            //lmc_dimmx_params.s.rc8  = 0;
            //lmc_dimmx_params.s.rc9  = 0;

            /*
            ** rc10               DDR4 RDIMM Operating Speed
            v                ** ====   =========================================================
            **  0                 tclk_psecs >= 1250 psec DDR4-1600 (1250 ps)
            **  1     1250 psec > tclk_psecs >= 1071 psec DDR4-1866 (1071 ps)
            **  2     1071 psec > tclk_psecs >=  938 psec DDR4-2133 ( 938 ps)
            **  3      938 psec > tclk_psecs >=  833 psec DDR4-2400 ( 833 ps)
            **  4      833 psec > tclk_psecs >=  750 psec DDR4-2666 ( 750 ps)
            **  5      750 psec > tclk_psecs >=  625 psec DDR4-3200 ( 625 ps)
            */
            lmc_dimmx_params.s.rc10        = 0;
            if (1250 > tclk_psecs)
                lmc_dimmx_params.s.rc10    = 1;
            if (1071 > tclk_psecs)
                lmc_dimmx_params.s.rc10    = 2;
            if (938 > tclk_psecs)
                lmc_dimmx_params.s.rc10    = 3;
            if (833 > tclk_psecs)
                lmc_dimmx_params.s.rc10    = 4;
            if (750 > tclk_psecs)
                lmc_dimmx_params.s.rc10    = 5;

            //lmc_dimmx_params.s.rc11 = 0;
            //lmc_dimmx_params.s.rc12 = 0;

            // RC0D: bits0,1 direct CS mode
            lmc_dimmx_params.s.rc13  = ((num_ranks == 4) && (dimm_count == 1)) ? /*quad*/1 : /*dual*/0;
            lmc_dimmx_params.s.rc13 |= (spd_lrdimm) ? 0 : 4; // bit 2 is 0=LRDIMM, 1=RDIMM
            lmc_dimmx_params.s.rc13 |= ((spd_addr_mirror & 1) << 3); // bit 3
            if (spd_lrdimm || ((num_ranks == 4) && (dimm_count == 1))) { // FIXME: verbosity
                ddr_print("DIMMX_PARAMS: RC0D: 0x%02x\n", lmc_dimmx_params.s.rc13);
            }

            //lmc_dimmx_params.s.rc14 = 0;
            //lmc_dimmx_params.s.rc15 = 4; /* 0 nCK latency adder */
            //lmc_dimmx_params.s.rc15 = 0; /* 1 nCK latency adder */

            lmc_dimmx_ddr4_params0.u = 0;

            //lmc_dimmx_ddr4_params0.s.rc8x = 0;
            //lmc_dimmx_ddr4_params0.s.rc7x = 0;
            //lmc_dimmx_ddr4_params0.s.rc6x = 0;
            //lmc_dimmx_ddr4_params0.s.rc5x = 0;
            //lmc_dimmx_ddr4_params0.s.rc4x = 0;

            lmc_dimmx_ddr4_params0.s.rc3x = compute_rc3x(tclk_psecs);

            //lmc_dimmx_ddr4_params0.s.rc2x = 0;
            //lmc_dimmx_ddr4_params0.s.rc1x = 0;

            lmc_dimmx_ddr4_params1.u = 0;

            //lmc_dimmx_ddr4_params1.s.rcbx = 0;
            //lmc_dimmx_ddr4_params1.s.rcax = 0;
            //lmc_dimmx_ddr4_params1.s.rc9x = 0;

            lmc_ddr4_dimm_ctl.u = 0;
            lmc_ddr4_dimm_ctl.s.ddr4_dimm0_wmask = 0x004;
            lmc_ddr4_dimm_ctl.s.ddr4_dimm1_wmask = (dimm_count > 1) ? 0x004 : 0x0000;

            /*
             * Handle any DDR4 overrides via envvars here...
             */
            if ((s = lookup_env_parameter("ddr_ddr4_params0")) != NULL) {
                lmc_dimmx_ddr4_params0.u = strtoul(s, NULL, 0);
            }
            if ((s = lookup_env_parameter("ddr_ddr4_params1")) != NULL) {
                lmc_dimmx_ddr4_params1.u = strtoul(s, NULL, 0);
            }
            if ((s = lookup_env_parameter("ddr_ddr4_dimm_ctl")) != NULL) {
                lmc_ddr4_dimm_ctl.u = strtoul(s, NULL, 0);
            }
            for (i = 0; i < 11; ++i) {
                uint64_t value;
                if ((s = lookup_env_parameter("ddr_ddr4_rc%1xx", i+1)) != NULL) {
                    value = strtoul(s, NULL, 0);
                    if (i < 8) {
                        lmc_dimmx_ddr4_params0.u &= ~((uint64_t)0xff << (i*8));
                        lmc_dimmx_ddr4_params0.u |=           (value << (i*8));
                    }
                    else {
                        lmc_dimmx_ddr4_params1.u &= ~((uint64_t)0xff << ((i-8)*8));
                        lmc_dimmx_ddr4_params1.u |=           (value << ((i-8)*8));
                    }
                }
            }

            /*
             * write the final CSR values
             */
            DRAM_CSR_WRITE(node, BDK_LMCX_DIMMX_DDR4_PARAMS0(ddr_interface_num, dimm), lmc_dimmx_ddr4_params0.u);

            DRAM_CSR_WRITE(node, BDK_LMCX_DDR4_DIMM_CTL(ddr_interface_num), lmc_ddr4_dimm_ctl.u);

            DRAM_CSR_WRITE(node, BDK_LMCX_DIMMX_DDR4_PARAMS1(ddr_interface_num, dimm), lmc_dimmx_ddr4_params1.u);

            ddr_print("N%d.LMC%d: DIMM%d DDR4 Register Control Words   RCBx:RC1x :",
                      node, ddr_interface_num, dimm);
            for (rc = 2; rc >= 0; --rc) ddr_print(" %x", EXTR_ARB(8,lmc_dimmx_ddr4_params1.u, rc));
            for (rc = 7; rc >= 0; --rc) ddr_print(" %x", EXTR_ARB(8,lmc_dimmx_ddr4_params0.u, rc));
            ddr_print("\n");

            // allow full DIMMX_PARAMSfinal override
            if ((s = lookup_env_parameter("ddr_dimmx_params")) != NULL) {
                lmc_dimmx_params.u = strtoul(s, NULL, 0);
            }

            // allow DIMMX_PARAMS RC[0:15] overrides here...
            for (i = 0; i < 16; ++i) {
                uint64_t value;
                if ((s = lookup_env_parameter("ddr_rc%d", i)) != NULL) {
                    value = strtoul(s, NULL, 0);
                    lmc_dimmx_params.u &= ~((uint64_t)0xf << (i*4));
                    lmc_dimmx_params.u |=           (  value << (i*4));
                }
            }

            DRAM_CSR_WRITE(node, BDK_LMCX_DIMMX_PARAMS(ddr_interface_num, dimm), lmc_dimmx_params.u);

            ddr_print("N%d.LMC%d: DIMM%d Register Control Words RC15:RC0 :",
                      node, ddr_interface_num, dimm);
            for (rc = 15; rc >= 0; --rc) ddr_print(" %x", EXTR_ARB(4,lmc_dimmx_params.u, rc));
            ddr_print("\n");

        } /* for didx */

        /* LMC0_DIMM_CTL */
        lmc_dimm_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(ddr_interface_num));
        lmc_dimm_ctl.s.dimm0_wmask = 0xdf3f;
        lmc_dimm_ctl.s.dimm1_wmask = (dimm_count > 1) ? 0xdf3f : 0x0000;

        if ((s = lookup_env_parameter("ddr_dimm0_wmask")) != NULL) {
            lmc_dimm_ctl.s.dimm0_wmask    = strtoul(s, NULL, 0);
        }
        if ((s = lookup_env_parameter("ddr_dimm1_wmask")) != NULL) {
            lmc_dimm_ctl.s.dimm1_wmask    = strtoul(s, NULL, 0);
        }

        if (bdk_is_model(OCTEONTX_CN8XXX)) {
            lmc_dimm_ctl.cn83xx.parity = custom_lmc_config->parity;
            if ((s = lookup_env_parameter("ddr_dimm_ctl_parity")) != NULL) {
                lmc_dimm_ctl.cn83xx.parity = strtoul(s, NULL, 0);
            }
        }
        else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */ {
            lmc_dimm_ctl.cn9.cke_assert = 1; // FIXME?
        }

        lmc_dimm_ctl.s.tcws = 0x4e0;
        if ((s = lookup_env_parameter("ddr_dimm_ctl_tcws")) != NULL) {
            lmc_dimm_ctl.s.tcws = strtoul(s, NULL, 0);
        }

        ddr_print("%-45s : 0x%016lx\n", "LMC DIMM_CTL", lmc_dimm_ctl.u);
        DRAM_CSR_WRITE(node, BDK_LMCX_DIMM_CTL(ddr_interface_num), lmc_dimm_ctl.u);

        perform_octeontx_ddr_sequence(node, rank_mask,
                                      ddr_interface_num, 0x7 ); /* Init RCW */

        /* Write RC0D last */
        lmc_dimm_ctl.s.dimm0_wmask = 0x2000;
        lmc_dimm_ctl.s.dimm1_wmask = (dimm_count > 1) ? 0x2000 : 0x0000;
        ddr_print("%-45s : 0x%016lx\n", "LMC DIMM_CTL", lmc_dimm_ctl.u);
        DRAM_CSR_WRITE(node, BDK_LMCX_DIMM_CTL(ddr_interface_num), lmc_dimm_ctl.u);

        /* Don't write any extended registers the second time */
        DRAM_CSR_WRITE(node, BDK_LMCX_DDR4_DIMM_CTL(ddr_interface_num), 0);

        perform_octeontx_ddr_sequence(node, rank_mask,
                                      ddr_interface_num, 0x7 ); /* Init RCW */
    }
    else { /* if (spd_rdimm) */

        /* Disable register control writes for unbuffered */
        bdk_lmcx_dimm_ctl_t lmc_dimm_ctl;
        lmc_dimm_ctl.u = BDK_CSR_READ(node, BDK_LMCX_DIMM_CTL(ddr_interface_num));
        lmc_dimm_ctl.s.dimm0_wmask         = 0;
        lmc_dimm_ctl.s.dimm1_wmask         = 0;
        DRAM_CSR_WRITE(node, BDK_LMCX_DIMM_CTL(ddr_interface_num), lmc_dimm_ctl.u);

    } /* if (spd_rdimm) */
}

void
Perform_Early_LMC_Init(bdk_node_t node, int ddr_interface_num,
                       dram_init_data_t *init_data,
                       dram_overrides_t *overrides)
{
    /*
     * 6.9.7 Early LMC Initialization
     *
     * All of DDR PLL, LMC CK, and LMC DRESET initializations must be
     * completed prior to starting this LMC initialization sequence.
     *
     * Perform the following five substeps for early LMC initialization:
     *
     * 1. Software must ensure there are no pending DRAM transactions.
     *
     * 2. Write LMC(0)_CONFIG, LMC(0)_CONTROL, LMC(0)_TIMING_PARAMS0,
     *    LMC(0)_TIMING_PARAMS1, LMC(0)_MODEREG_PARAMS0,
     *    LMC(0)_MODEREG_PARAMS1, LMC(0)_DUAL_MEMCFG, LMC(0)_NXM,
     *    LMC(0)_WODT_MASK, LMC(0)_RODT_MASK, LMC(0)_COMP_CTL2,
     *    LMC(0)_PHY_CTL, LMC(0)_DIMM0/1_PARAMS, and LMC(0)_DIMM_CTL with
     *    appropriate values. All sections in this chapter can be used to
     *    derive proper register settings.
     */

    // turn OFF ECC error reporting until we are done with init
    Setup_ECC_Error_Reporting(node, ddr_interface_num, 0/*disable*/);

    // HRM-CN9XXX Section 7.9.6.1-2

    Clear_LMCX_Scrambling(node, ddr_interface_num); // disable scrambling

    Setup_LMCX_CONFIG(node, ddr_interface_num, init_data);

    Setup_LMCX_CONTROL(node, ddr_interface_num, init_data, overrides);

    Setup_LMCX_DLL_CTL3(node, ddr_interface_num, init_data);

    Setup_LMCX_TIMING_PARAMS_Registers(node, ddr_interface_num, init_data, overrides);

    Setup_LMCX_MODEREG_PARAMS_Registers(node, ddr_interface_num, init_data, overrides);

    //Setup_LMCX_DUAL_MEMCFG(node, ddr_interface_num, init_data);

    Setup_LMCX_NXM(node, ddr_interface_num, init_data);

    //Setup_LMCX_MR_MPR_CTL(node, ddr_interface_num, init_data);

    Setup_LMCX_WODT_MASK(node, ddr_interface_num, init_data);

    Setup_LMCX_RODT_MASK(node, ddr_interface_num, init_data);

    Setup_LMCX_COMP_CTL2(node, ddr_interface_num, init_data);

    Setup_LMCX_PHY_CTL(node, ddr_interface_num, init_data, overrides);

    Setup_LMCX_EXT_CONFIG_Registers(node, ddr_interface_num, init_data, overrides);

    //Setup_LMCX_REF_CONFIG(node, ddr_interface_num, init_data);

    Setup_LMCX_PHY_CTL3(node, ddr_interface_num, init_data);
}

//Bring the DRAM out of self refresh mode
void
Bring_Up_DRAM_for_Training(bdk_node_t node, int ddr_interface_num,
                           int rank_mask, dram_init_data_t *init_data)
{
    bdk_lmcx_modereg_params0_t lmc_modereg_params0;

    // HRM-CN8XXX Section 6.9.7.4
    // HRM-CN9XXX Section 7.9.6.4-6

    if (ddr_memory_preserved(node)) {
        /* Contents are being preserved. Take DRAM out of
           self-refresh first. Then init steps can proceed
           normally
        */
        /* SEQ: self-refresh exit */
        perform_octeontx_ddr_sequence(node, rank_mask, ddr_interface_num, 3);
    }

    lmc_modereg_params0.u = BDK_CSR_READ(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num));

    if (bdk_is_model(OCTEONTX_CN8XXX))
        lmc_modereg_params0.cn8.dllr = 1; /* Set during first init sequence */
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */
        lmc_modereg_params0.cn9.dllr = 1; /* Set during first init sequence */
    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num), lmc_modereg_params0.u);

    // issue the powerup/init sequence
    perform_ddr_init_sequence(node, rank_mask, ddr_interface_num);

    if (bdk_is_model(OCTEONTX_CN8XXX))
        lmc_modereg_params0.cn8.dllr = 0; /* Clear after first init sequence */
    else /* if (bdk_is_model(OCTEONTX_CN9XXX)) */
        lmc_modereg_params0.cn9.dllr = 0; /* Clear after first init sequence */
    DRAM_CSR_WRITE(node, BDK_LMCX_MODEREG_PARAMS0(ddr_interface_num), lmc_modereg_params0.u);

    // FIXME: do this in early LMC init on PHY_CTL3 setup...
    // HRM-CN9XXX Section 7.9.6.7
}

void
Finish_Early_LMC_Init(bdk_node_t node, int ddr_interface_num,
                       dram_init_data_t *init_data,
                       dram_overrides_t *overrides)
{
    // HRM-CN9XXX Section 7.9.6.3-7

    /* Variables Needed to Setup LMC CSRs */
    int spd_lrdimm = init_data->refs.spd_lrdimm;

    // LRDIMM DB Reset must be performed here,
    //  just before the normal RCW write.
    if (spd_lrdimm) {
        lrdimm_db_reset(node, ddr_interface_num, init_data);
    }

    // HRM-CN9XXX Section 7.9.6.3
    // performs RCW sequence, does DIMM_CTL also
    Setup_LMCX_DIMMX_PARAMS(node, ddr_interface_num, init_data);

    // LRDIMM DB Setup pre-processing must be performed here,
    //  just before the powerup/init sequence.
    if (spd_lrdimm) {
        lrdimm_db_setup(node, ddr_interface_num, init_data, overrides);
    }

    // HRM-CN9XXX Section 7.9.6.4-7
    // Bring DRAM out of self refresh, do powerup/init
    // NOTE: these steps are done later (in Perform_Training_on_Rank_Mask_Part1) for CN8xxx,
    //       because of complications when doing BY-RANK init on that chip...
    if (bdk_is_model(OCTEONTX_CN9XXX)) {
        int rank_mask =             init_data->refs.rank_mask;
        Bring_Up_DRAM_for_Training(node, ddr_interface_num, rank_mask, init_data);
    }

}
