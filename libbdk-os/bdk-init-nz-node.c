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
#include "libbdk-arch/bdk-csrs-bgx.h"
#include "libbdk-arch/bdk-csrs-key.h"
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-gser.h"
#include "libbdk-arch/bdk-csrs-gti.h"
#include "libbdk-arch/bdk-csrs-ocx.h"
#include "libbdk-arch/bdk-csrs-uaa.h"

#define DEBUG_STATE                 false/* Show state transitions for each lane */
#define DEBUG_TRAIN_MESSAGES        false/* Show every transition of LD and LP messages */
#define DEBUG_MESSAGE_CHECK         false/* Show counting numbers when we run the message check */
#define DEBUG_TUNING_CHANGES        false/* Show setting when we send tuning to hardware */
#define DEBUG_TIME_RX_EQ            false/* Show how long RX equalization takes */
#define DEBUG_PARAMETERS            false/* Show tuning parameter passing */
#define DEBUG_ONE_LANE_AT_A_TIME    false/* Run one lane at a time instead of all lanes in parallel */

#define CCPI_LANES              24      /* Number of SERDES lanes used for CCPI */
#define CCPI_MIN_LINKS          2       /* Number of logical links that must work for success */
#define CCPI_MAX_LINKS          3       /* Total number of logical links */
#define CCPI_MASTER_TIMEOUT     30      /* Seconds to wait for CCPI links */
#define CCPI_MAX_STEPS          15      /* Maximum number of training steps a lane can take before training ends */
#define REF_CLOCK               50000000/* This is currently defined to be 50Mhz */
#define TRAIN_INIT_TX_MAIN      13      /* Starting swing / amplitude */
#define TRAIN_INIT_TX_PRE       2       /* Starting pre-emphasis */
#define TRAIN_INIT_TX_POST      11      /* Starting post-emphasis */
#define TRAIN_DATA_MASK         0x3f    /* The lower 6 bits of CU and SR are data we can use */
#define RXT_ESM_HOLD            0       /* RX equalization request value hold */
#define RXT_ESM_INC             1       /* RX equalization request value for increment */
#define RXT_ESM_DEC             2       /* RX equalization request value for decrement */

extern void __bdk_reset_thread(int arg1, void *arg2);

/**
 * Enumeration of the possible state of each CCPI lane
 */
typedef enum
{
    STATE_START,                /* Done nothing, initial start state */
    STATE_WAIT_EIE,             /* Waiting for Eletrical Idle Exit */
    STATE_WAIT_CDR,             /* Waiting for CDR lock */
    STATE_WAIT_TRAIN_PRESET,    /* Waiting for special training message signalling start of message check */
    STATE_MESSAGE_CHECK,        /* Sending message to check reliability if training messages */
    STATE_TRAINING_INIT,        /* Start training */
    STATE_TRAINING_IDLE = 0x8,  /* Training, no outstanding CU nor SR */
    STATE_TRAINING_UPDATE = 0x9,/* Training, no CU, SR in progress */
    STATE_TRAINING_REQ = 0xa,   /* Training, CU in progress, no SR */
    STATE_TRAINING_REQ_UPDATE = 0xb, /* Training, CU in progress, SR in progress */
    STATE_WAIT_FOR_READY,       /* Waiting for CCPI to mark lane as ready */
    STATE_READY,                /* Lane is ready for use */
} state_t;

/**
 * State information for each CCPI lane
 */
typedef struct
{
    union bdk_bgx_spu_br_train_cup_s lp_cu; /* Last valid received Coef Update from link partner */
    union bdk_bgx_spu_br_train_rep_s lp_sr; /* Last valid received Status Response from link partner */
    union bdk_bgx_spu_br_train_cup_s ld_cu; /* Current Coef Update for local device */
    union bdk_bgx_spu_br_train_rep_s ld_sr; /* Current Status Response for local device */
    uint8_t merit;          /* RX equalization figure of merit */
    uint8_t chk_done    : 1;/* Set when this lane completes message check */
    uint8_t rx_ready    : 1;/* Set when this lane is done with training */
    uint8_t desired_pre : 2;/* RX equalization recommended PRE change (RXT_ESM_*) */
    uint8_t desired_main: 2;/* RX equalization recommended MAIN change (RXT_ESM_*) */
    uint8_t desired_post: 2;/* RX equalization recommended POST change (RXT_ESM_*) */
    uint8_t init_main;      /* Initial TX MAIN value */
    uint8_t init_pre;       /* Initial TX PRE value */
    uint8_t init_post;      /* Initial TX POST value */
    uint8_t tx_main;        /* Current TX MAIN value */
    uint8_t tx_pre;         /* Current TX PRE value */
    uint8_t tx_post;        /* Current TX POST value */
    uint8_t steps;          /* Number of training steps for the lane */
    state_t lane_state : 8; /* Current state of the lane (enumeration) */
} lane_state_t;

/**
 * The node number may change dynamically while this code is running. This
 * variable contains its value after every update in the CCPI monitor loop
 */
static bdk_node_t node;
static bool do_trace;
static lane_state_t lane_state[CCPI_LANES];

/**
 * Get the current reference clock count. When running on secondary nodes, the
 * normal clock functions don't work when compiled with LLVM. This serves as
 * a simple replacement that should work regardless of the compiler.
 *
 * @return Reference clock count
 */
static uint64_t get_ref_clock(void)
{
    return BDK_CSR_READ(node, BDK_RST_REF_CNTR);
}

/**
 * Delay for the specified microseconds
 *
 * @param usec
 */
static void wait_usec(uint64_t usec)
{
    uint64_t timeout = get_ref_clock() + REF_CLOCK * usec / 1000000;
    while (get_ref_clock() < timeout)
    {
        /* Spin */
    }
}

static void uart_dec1(int v)
{
    bdk_dbg_uart_char('0' + v);
}

static void uart_dec2(int v)
{
    if (v < 0)
    {
        bdk_dbg_uart_char('-');
        v = -v;
    }
    if (v >= 100)
    {
        bdk_dbg_uart_char('0' + v / 100);
        v %= 100;
    }
    bdk_dbg_uart_char('0' + v / 10);
    bdk_dbg_uart_char('0' + v % 10);
}

/**
 * Read OCX setup used to determine which QLMs connect to which links
 *
 * @param node   Node to query
 * @param link   Link to query
 *
 * @return QLM mask of CCPI QLMs being used
 */
static int ccpi_get_qlm_select(int link)
{
    BDK_CSR_INIT(qlmx_cfg2, node, BDK_OCX_QLMX_CFG(2));
    BDK_CSR_INIT(qlmx_cfg3, node, BDK_OCX_QLMX_CFG(3));

    /* Determine which QLMs a link uses */
    int qlm_select = 0;
    /* qlmx_cfg2[ser_local]=1 means QLM2 is to link 1 */
    /* qlmx_cfg3[ser_local]=1 means QLM3 is to link 1 */
    switch (link)
    {
        case 0:
            qlm_select = (qlmx_cfg2.s.ser_local) ? 0x3 : 0x7;
            break;
        case 1:
            qlm_select = (qlmx_cfg2.s.ser_local) ? 0x4 : 0x0;
            qlm_select |= (qlmx_cfg3.s.ser_local) ? 0x8 : 0x0;
            break;
        case 2:
            qlm_select = (qlmx_cfg3.s.ser_local) ? 0x30 : 0x38;
            break;
    }
    return qlm_select;
}

/**
 * CN88XX pass 1.x required CCPI lane reversal to be programmed manually. This
 * function is called on the master node to setup lane reversal based on a
 * configuration parameter.
 */
static void ccpi_set_lane_reversal(void)
{
    int lane_reverse = bdk_config_get_int(BDK_CONFIG_CCPI_LANE_REVERSE);
    if (!lane_reverse)
        return;

    printf("N%d.CCPI: Applying lane reversal\n", node);

    for (int link = 0; link < CCPI_MAX_LINKS; link++)
    {
        /* QLM_SELECT must be zero before changing lane reversal */
        BDK_CSR_MODIFY(c, node, BDK_OCX_LNKX_CFG(link),
            c.s.qlm_select = 0);
        /* Set RX lane reversal */
        BDK_CSR_MODIFY(c, node, BDK_OCX_LNKX_CFG(link),
            c.s.lane_rev = 1);
    }
    /* Set TX lane reversal */
    BDK_CSR_MODIFY(c, node, BDK_OCX_LNE_DBG,
        c.s.tx_lane_rev = 1);
    /* Restore the QLM lane select */
    for (int link = 0; link < CCPI_MAX_LINKS; link++)
    {
        BDK_CSR_MODIFY(c, node, BDK_OCX_LNKX_CFG(link),
            c.s.qlm_select = ccpi_get_qlm_select(link));
    }
}

/**
 * Get the speed of the CCPI lanes
 *
 * @return Speed in Mhz
 */
static int ccpi_get_speed(void)
{
    int qlm = 8;
    /* Use the OCI strapping to find the speed. This will not work if
       the OCI is in SW_MODE */
    BDK_CSR_INIT(gserx_spd, node, BDK_GSERX_SPD(qlm));
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
    {
        /* Pass 1.x used a different encoding than pass 2.x */
        switch (gserx_spd.s.spd)
        {
            case 0x0: return 1250; /* Ref 100Mhz */
            case 0x1: return 2500;
            case 0x2: return 5000;
            case 0x3: return 8000;
            case 0x4: return 1250; /* Ref 125Mhz */
            case 0x5: return 2500;
            case 0x6: return 3125;
            case 0x7: return 5000;
            case 0x8: return 6250;
            case 0x9: return 8000;
            case 0xa: return 2500; /* Ref 156.25Mhz */
            case 0xb: return 3125;
            case 0xc: return 5000;
            case 0xd: return 6250;
            case 0xe: return 10312; /* KR training */
            default: /* Software mode */
                return 0;
        }
    }
    else
    {
        /* This is for pass 2.x (and beyond) */
        switch (gserx_spd.s.spd)
        {
            case 0x0: return 5000; /* Ref 100Mhz, Training short (Rx EQ only) */
            case 0x1: return 2500; /* Ref 100Mhz, No training */
            case 0x2: return 5000; /* Ref 100Mhz, No training */
            case 0x3: return 8000; /* Ref 100Mhz, No training */
            case 0x4: return 8000; /* Ref 100Mhz, Training short (Rx EQ only) */
            case 0x5: return 8000; /* Ref 100Mhz, KR training */
            case 0x6: return 3125; /* Ref 156.25Mhz, No training */
            case 0x7: return 5000; /* Ref 125Mhz, No training */
            case 0x8: return 6250; /* Ref 156.25Mhz, No training */
            case 0x9: return 8000; /* Ref 125Mhz, No training */
            case 0xa: return 10312;/* Ref 156.25Mhz, Training short (Rx EQ only) */
            case 0xb: return 3125; /* Ref 156.25Mhz, No training */
            case 0xc: return 5000; /* Ref 125Mhz, Training short (Rx EQ only) */
            case 0xd: return 6250; /* Ref 156.25Mhz, Training short (Rx EQ only) */
            case 0xe: return 10312;/* Ref 156.25Mhz, KR training */
            default: /* Software mode */
                return 0;
        }
    }
}

/**
 * Update the per lane state with the current LP messages
 *
 * @param ccpi_lane Lane to update
 */
static void ccpi_update_lp_messages(int ccpi_lane)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    BDK_CSR_INIT(trn_lp, node, BDK_OCX_LNEX_TRN_LP(ccpi_lane));
    if (trn_lp.s.lp_cu_val)
    {
        if (DEBUG_TRAIN_MESSAGES && do_trace && (lstate->lp_cu.u != trn_lp.s.lp_cu_dat))
        {
            bdk_dbg_uart_str("Lane ");
            uart_dec2(ccpi_lane);
            bdk_dbg_uart_str(": LP CU ");
            bdk_dbg_uart_hex(lstate->lp_cu.u);
            bdk_dbg_uart_str(" -> ");
            bdk_dbg_uart_hex(trn_lp.s.lp_cu_dat);
            bdk_dbg_uart_str("\r\n");
        }
        lstate->lp_cu.u = trn_lp.s.lp_cu_dat;
    }
    if (trn_lp.s.lp_sr_val)
    {
        if (DEBUG_TRAIN_MESSAGES && do_trace && (lstate->lp_sr.u != trn_lp.s.lp_sr_dat))
        {
            bdk_dbg_uart_str("Lane ");
            uart_dec2(ccpi_lane);
            bdk_dbg_uart_str(": LP SR ");
            bdk_dbg_uart_hex(lstate->lp_sr.u);
            bdk_dbg_uart_str(" -> ");
            bdk_dbg_uart_hex(trn_lp.s.lp_sr_dat);
            bdk_dbg_uart_str("\r\n");
        }
        lstate->lp_sr.u = trn_lp.s.lp_sr_dat;
    }
}

/**
 * Perform an RX equalization request on all CCPI lanes and record the results
 * in the per lane global state
 */
static void ccpi_update_rx_equalization()
{
    for (int qlm = 8; qlm < 14; qlm++)
    {
        for (int lane = 0; lane < 4; lane++)
        {
            int ccpi_lane = (qlm - 8) * 4 + lane;
            lane_state_t *lstate = &lane_state[ccpi_lane];
            /* Only do RX equalization on lanes in training */
            if ((lstate->lane_state >= STATE_WAIT_TRAIN_PRESET) &&
                (lstate->lane_state < STATE_WAIT_FOR_READY))
            {
                /* Software control of RX equalization */
                BDK_CSR_MODIFY(c, node, BDK_GSERX_BR_RXX_CTL(qlm, lane),
                    c.s.rxt_swm = 1);
                /* Clear the completion flag and initiate a new request */
                BDK_CSR_MODIFY(c, node, BDK_GSERX_BR_RXX_EER(qlm, lane),
                    c.s.rxt_esv = 0;
                    c.s.rxt_eer = 1);
            }
        }
    }

    uint64_t start_time = get_ref_clock();
    uint64_t finish_time = start_time;
    uint64_t timeout = start_time + REF_CLOCK * 100ull / 1000; /* 100ms */

    for (int qlm = 8; qlm < 14; qlm++)
    {
        for (int lane = 0; lane < 4; lane++)
        {
            int ccpi_lane = (qlm - 8) * 4 + lane;
            lane_state_t *lstate = &lane_state[ccpi_lane];
            /* Only do RX equalization on lanes in training */
            if ((lstate->lane_state >= STATE_WAIT_TRAIN_PRESET) &&
                (lstate->lane_state < STATE_WAIT_FOR_READY))
            {
                BDK_CSR_INIT(gserx_br_rxx_eer, node, BDK_GSERX_BR_RXX_EER(qlm, lane));
                while (!gserx_br_rxx_eer.s.rxt_esv)
                {
                    finish_time = get_ref_clock();
                    if (finish_time >= timeout)
                        break;
                    gserx_br_rxx_eer.u = BDK_CSR_READ(node, BDK_GSERX_BR_RXX_EER(qlm, lane));
                    /* Update Link Partner message state */
                    ccpi_update_lp_messages(ccpi_lane);
                }

                /* Disable software control of RX equalization */
                BDK_CSR_MODIFY(c, node, BDK_GSERX_BR_RXX_CTL(qlm, lane),
                    c.s.rxt_swm = 0);

                if (gserx_br_rxx_eer.s.rxt_esv)
                {
                    lstate->merit = bdk_extract(gserx_br_rxx_eer.s.rxt_esm, 6, 8);
                    lstate->desired_pre = bdk_extract(gserx_br_rxx_eer.s.rxt_esm, 0, 2);
                    lstate->desired_main = bdk_extract(gserx_br_rxx_eer.s.rxt_esm, 2, 2);
                    lstate->desired_post = bdk_extract(gserx_br_rxx_eer.s.rxt_esm, 4, 2);
                    /* Change a hold of 3 to 0 so software only has to deal
                       with one value */
                    if (lstate->desired_pre == 3)
                        lstate->desired_pre = RXT_ESM_HOLD;
                    if (lstate->desired_main == 3)
                        lstate->desired_main = RXT_ESM_HOLD;
                    if (lstate->desired_post == 3)
                        lstate->desired_post = RXT_ESM_HOLD;
                }
                else
                {
                    lstate->merit = 0;
                    lstate->desired_pre = RXT_ESM_HOLD;
                    lstate->desired_main = RXT_ESM_HOLD;
                    lstate->desired_post = RXT_ESM_HOLD;
                }
            }
        }
    }

    if (DEBUG_TIME_RX_EQ && do_trace && (finish_time != start_time))
    {
        bdk_dbg_uart_str("RX Equalization: ");
        uart_dec2((finish_time - start_time) / (REF_CLOCK / 1000));
        bdk_dbg_uart_str(" ms\r\n");
    }
}

/**
 * Check if the supplied tuning values are valid and could be applied to a SERDES
 * lane. This function doesn't apply the setting, just range checks.
 *
 * @param tx_swing Desired swing value
 * @param tx_pre   Desired pre-emphasis
 * @param tx_post  Desired post-emphasis
 *
 * @return True if the settings are valid, false otherwise
 */
static bool is_tuning_valid(int tx_swing, int tx_pre, int tx_post)
{
    /* SERDES range limits */
    /* 1) (pre + post) - main <= 2 */
    /* 2) pre + post + main <= 35 */
    /* 3) 0 <= pre <= 10 (0=Max, 10=Min) */
    /* 4) 0 <= main <= 25 (0=Max, 25=Min) */
    /* 5) 0 <= post <= 15 (0=Max, 15=Min) */
    if (tx_pre + tx_post - tx_swing > 2)
        return false;
    if (tx_pre + tx_post + tx_swing > 35)
        return false;
    if ((tx_pre < 0) || (tx_pre > 10))
        return false;
    if ((tx_swing < 0) || (tx_swing > 25))
        return false;
    if ((tx_post < 0) || (tx_post > 15))
        return false;
    return true;
}

/**
 * Apply SERDES tuning parameters to a specific CCPI lane
 *
 * @param ccpi_lane Lane to apply settings to
 * @param tx_swing  New swing / amplitude
 * @param tx_pre    New pre-emphasis
 * @param tx_post   New post-emphasis
 */
static void ccpi_tx_tune(int ccpi_lane, int tx_swing, int tx_pre, int tx_post)
{
    int qlm = ccpi_lane / 4 + 8;
    int lane = ccpi_lane & 3;

    /* Manual Tx Swing and Tx Equalization Programming Steps */

    /* 1) Enable Tx swing and Tx emphasis overrides */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_TX_CFG_1(qlm, lane),
        c.s.tx_swing_ovrrd_en = 1;
        c.s.tx_premptap_ovrrd_val = 1);
    /* 2) Program the Tx swing and Tx emphasis Pre-cursor and Post-cursor values */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_TX_CFG_0(qlm, lane),
        c.s.cfg_tx_swing = tx_swing);
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_TX_PRE_EMPHASIS(qlm, lane),
        c.s.cfg_tx_premptap = (tx_post << 4) | tx_pre);
    /* 3) Program override for the Tx coefficient request */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_0(qlm, lane),
        c.s.cfg_tx_coeff_req_ovrrd_val = 1);
    /* 4) Enable the Tx coefficient request override enable */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
        c.s.cfg_tx_coeff_req_ovrrd_en = 1);
    /* 5) Issue a Control Interface Configuration Override request to start
        the Tx equalizer Optimization cycle which applies the new Tx swing
        and equalization settings */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
        c.s.ctlifc_ovrrd_req = 1);
    /* 6) To perform a subsequent Tx swing and Tx equalization adjustment:
        a) Disable the Tx coefficient request override enable */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
        c.s.cfg_tx_coeff_req_ovrrd_en = 0);
    /* b) Issue a Control Interface Configuration Override request */
    BDK_CSR_MODIFY(c, node, BDK_GSERX_LANEX_PCS_CTLIFC_2(qlm, lane),
        c.s.ctlifc_ovrrd_req = 1);
}

/**
 * The definition of a short or long channel is whether the channel loss
 * is less than or equal to 10dB. This function does the range
 * check so it is only in one spot in the CCPI code.
 *
 * @param channel_loss
 *               Channel loss in dB
 *
 * @return True for short channel, false otherwise
 */
static bool is_short_channel(int channel_loss)
{
    /* A value of -1, unknown channel loss, will be treated as short channel.
       Short channel is the most common CCPI setup */
    return (channel_loss <= 10);
}

/**
 * Configure the channel for short or long. This function shouldn't be used
 * directly, instead ccpi_channel_loss should be called with the
 * proper channel loss. Due to limited space in training
 * messages, the secondary node uses this function directly.
 *
 * @param ccpi_lane Lane to configure
 * @param short_channel
 *                  True if the channel is short, False if long
 */
static void ccpi_channel_length(int ccpi_lane, bool short_channel)
{
    int qlm = ccpi_lane / 4 + 8;
    int lane = ccpi_lane & 3;
    /* The gain setting can only be set for an entire QLM instead of
       per lane. Only set it for lane 0 and ignore lanes 1-3 */
    if (lane == 0)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERX_LANE_VMA_FINE_CTRL_2(qlm),
            c.s.rx_prectle_gain_min_fine = short_channel ? 0x0 : 0x6);
    }
}

/**
 * Given a channel loss in dB, configure the ccpi lane
 *
 * @param ccpi_lane Lane to configure
 * @param channel_loss
 *                  Channel loss in dB
 */
static void ccpi_channel_loss(int ccpi_lane, int channel_loss)
{
    ccpi_channel_length(ccpi_lane, is_short_channel(channel_loss));
}

/**
 * Display detailed tuning state for a single CCPI lane
 *
 * @param ccpi_lane Lane to display
 */
static void display_tuning_state(int ccpi_lane)
{
    const char dir_label[4][5] = {"Hold", "Inc", "Dec", "Hold"};
    int qlm = 8 + ccpi_lane / 4;
    int lane = ccpi_lane & 3;

    uint64_t rx_aeq_out_0 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_AEQ_OUT_0(qlm, lane));
    uint64_t rx_aeq_out_1 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_AEQ_OUT_1(qlm, lane));
    uint64_t rx_aeq_out_2 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_AEQ_OUT_2(qlm, lane));
    uint64_t rx_vma_status_0 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_VMA_STATUS_0(qlm, lane));
    uint64_t rx_vma_status_1 = BDK_CSR_READ(node, BDK_GSERX_LANEX_RX_VMA_STATUS_1(qlm, lane));
    uint64_t sds_pin_mon_1 = BDK_CSR_READ(node, BDK_GSERX_LANEX_SDS_PIN_MON_1(qlm, lane));
    uint64_t sds_pin_mon_2 = BDK_CSR_READ(node, BDK_GSERX_LANEX_SDS_PIN_MON_2(qlm, lane));
    uint64_t br_rxx_eer = BDK_CSR_READ(node, BDK_GSERX_BR_RXX_EER(qlm, lane));
    BDK_CSR_INIT(qlmx_cfg, node, BDK_OCX_QLMX_CFG(qlm - 8));

    bdk_dbg_uart_str("Lane ");
    uart_dec2(ccpi_lane);
    bdk_dbg_uart_str(":\r\n");

    bdk_dbg_uart_str("    DFE Tap 1: ");
    uart_dec2(bdk_extract(rx_aeq_out_1, 0, 5));
    bdk_dbg_uart_str(", Tap 2: ");
    uart_dec2(bdk_extract_smag(rx_aeq_out_1, 5, 9));
    bdk_dbg_uart_str(", Tap 3: ");
    uart_dec2(bdk_extract_smag(rx_aeq_out_1, 10, 14));
    bdk_dbg_uart_str(", Tap 4: ");
    uart_dec2(bdk_extract_smag(rx_aeq_out_0, 0, 4));
    bdk_dbg_uart_str(", Tap 5: ");
    uart_dec2(bdk_extract_smag(rx_aeq_out_0, 5, 9));
    bdk_dbg_uart_str("\r\n");

    bdk_dbg_uart_str("    Pre-CTLE Gain: ");
    uart_dec2(bdk_extract(rx_aeq_out_2, 4, 4));
    bdk_dbg_uart_str(", Post-CTLE Gain: ");
    uart_dec2(bdk_extract(rx_aeq_out_2, 0, 4));
    bdk_dbg_uart_str(", CTLE Peak: ");
    uart_dec2(bdk_extract(rx_vma_status_0, 2, 4));
    bdk_dbg_uart_str(", CTLE Pole: ");
    uart_dec2(bdk_extract(rx_vma_status_0, 0, 2));
    bdk_dbg_uart_str("\r\n");

    bdk_dbg_uart_str("    TX Swing: ");
    uart_dec2(bdk_extract(sds_pin_mon_1, 1, 5));
    bdk_dbg_uart_str(", Pre-emphasis Pre-cursor: ");
    uart_dec2(bdk_extract(sds_pin_mon_2, 0, 4));
    bdk_dbg_uart_str(", Post-cursor: ");
    uart_dec2(bdk_extract(sds_pin_mon_2, 4, 5));
    bdk_dbg_uart_str("\r\n");

    bdk_dbg_uart_str("    TX Boost Enable: ");
    uart_dec2(bdk_extract(sds_pin_mon_2, 10, 1));
    bdk_dbg_uart_str(", TX Turbo Mode: ");
    uart_dec2(bdk_extract(sds_pin_mon_2, 9, 1));
    bdk_dbg_uart_str("\r\n");

    bdk_dbg_uart_str("    RX Equalization Tx Directions Hints TXPRE: ");
    bdk_dbg_uart_str(dir_label[bdk_extract(br_rxx_eer, 0, 2)]);
    bdk_dbg_uart_str(", TXMAIN: ");
    bdk_dbg_uart_str(dir_label[bdk_extract(br_rxx_eer, 2, 2)]);
    bdk_dbg_uart_str(", TXPOST: ");
    bdk_dbg_uart_str(dir_label[bdk_extract(br_rxx_eer, 4, 2)]);
    bdk_dbg_uart_str(", Figure of Merit: ");
    uart_dec2(bdk_extract(br_rxx_eer, 6, 8));
    bdk_dbg_uart_str("\r\n");

    bdk_dbg_uart_str("    Training-done: ");
    uart_dec1(bdk_extract(rx_vma_status_1, 7, 1));
    bdk_dbg_uart_str(", Ready: ");
    uart_dec1(qlmx_cfg.s.ser_lane_ready & (1 << lane) ? 1 : 0);
    bdk_dbg_uart_str(", Bad: ");
    uart_dec1(qlmx_cfg.s.ser_lane_bad & (1 << lane) ? 1 : 0);
    bdk_dbg_uart_str("\r\n");
}

/**
 * Display detailed tuning state for every CCPI lane
 */
static void display_tuning_state_all(void)
{
    for (int ccpi_lane = 0; ccpi_lane < CCPI_LANES; ccpi_lane++)
        display_tuning_state(ccpi_lane);
}

/**
 * Display the state of all lanes on a single output line
 */
static void display_state(void)
{
    static int count = 0;
    if ((count & 0xf) == 0)
    {
        for (int ccpi_lane = 0; ccpi_lane < CCPI_LANES; ccpi_lane++)
        {
            bdk_dbg_uart_char(' ');
            bdk_dbg_uart_char('[');
            uart_dec2(ccpi_lane);
            bdk_dbg_uart_char(']');
        }
        bdk_dbg_uart_str("\r\n");
    }
    count++;

    for (int ccpi_lane = 0; ccpi_lane < CCPI_LANES; ccpi_lane++)
    {
        switch (lane_state[ccpi_lane].lane_state)
        {
            case STATE_START:
                bdk_dbg_uart_str(" Strt");
                break;
            case STATE_WAIT_EIE:
                bdk_dbg_uart_str(" Weie");
                break;
            case STATE_WAIT_CDR:
                bdk_dbg_uart_str(" Wcdr");
                break;
            case STATE_WAIT_TRAIN_PRESET:
                bdk_dbg_uart_str(" W1st");
                break;
            case STATE_MESSAGE_CHECK:
            {
                int request = lane_state[ccpi_lane].ld_cu.u & TRAIN_DATA_MASK;
                bdk_dbg_uart_str(" Ck");
                uart_dec2(request);
                break;
            }
            case STATE_TRAINING_INIT:
                bdk_dbg_uart_str(" Init");
                break;
            case STATE_TRAINING_IDLE:
                bdk_dbg_uart_str(" Idle");
                break;
            case STATE_TRAINING_UPDATE:
                bdk_dbg_uart_str(" Upd ");
                break;
            case STATE_TRAINING_REQ:
                bdk_dbg_uart_str(" Req ");
                break;
            case STATE_TRAINING_REQ_UPDATE:
                bdk_dbg_uart_str(" R+U ");
                break;
            case STATE_WAIT_FOR_READY:
                bdk_dbg_uart_str(" Wrdy");
                break;
            case STATE_READY:
                bdk_dbg_uart_str(" Rdy ");
                break;
        }
    }
    bdk_dbg_uart_str("\r\n");
}

/**
 * Change a lane's current state. This is a function to make it easy to log the
 * various state changes.
 *
 * @param ccpi_lane CCPI lane to change state
 * @param state     New state
 */
static void lane_change_state(int ccpi_lane, state_t state)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    if (DEBUG_STATE && do_trace)
    {
        bdk_dbg_uart_str("Lane ");
        uart_dec2(ccpi_lane);
        bdk_dbg_uart_str(": (Merit ");
        uart_dec2(lstate->merit);
        bdk_dbg_uart_str(" Main=");
        switch (lstate->desired_main)
        {
            case RXT_ESM_INC:
                bdk_dbg_uart_str("Incr");
                break;
            case RXT_ESM_DEC:
                bdk_dbg_uart_str("Decr");
                break;
            default:
                bdk_dbg_uart_str("Hold");
                break;
        }
        bdk_dbg_uart_str(" Post=");
        switch (lstate->desired_post)
        {
            case RXT_ESM_INC:
                bdk_dbg_uart_str("Incr");
                break;
            case RXT_ESM_DEC:
                bdk_dbg_uart_str("Decr");
                break;
            default:
                bdk_dbg_uart_str("Hold");
                break;
        }
        bdk_dbg_uart_str(" Pre=");
        switch (lstate->desired_pre)
        {
            case RXT_ESM_INC:
                bdk_dbg_uart_str("Incr");
                break;
            case RXT_ESM_DEC:
                bdk_dbg_uart_str("Decr");
                break;
            default:
                bdk_dbg_uart_str("Hold");
                break;
        }

        int qlm = 8 + ccpi_lane / 4;
        int lane = ccpi_lane & 3;
        BDK_CSR_INIT(pin1, node, BDK_GSERX_LANEX_SDS_PIN_MON_1(qlm, lane));
        BDK_CSR_INIT(pin2, node, BDK_GSERX_LANEX_SDS_PIN_MON_2(qlm, lane));

        bdk_dbg_uart_str(" Tuning Main=");
        uart_dec2(pin1.s.pcs_sds_tx_swing);
        bdk_dbg_uart_str(" Post=");
        uart_dec2(pin2.s.pcs_sds_premptap >> 4);
        bdk_dbg_uart_str(" Pre=");
        uart_dec2(pin2.s.pcs_sds_premptap & 0xf);
        bdk_dbg_uart_str(" Step=");
        uart_dec2(lstate->steps);
#if 0
        bdk_dbg_uart_str(" LD[");
        bdk_dbg_uart_hex(lstate->ld_cu.u);
        bdk_dbg_uart_char(',');
        bdk_dbg_uart_hex(lstate->ld_sr.u);
        bdk_dbg_uart_str("] LP]");
        bdk_dbg_uart_hex(lstate->lp_cu.u);
        bdk_dbg_uart_char(',');
        bdk_dbg_uart_hex(lstate->lp_sr.u);
        bdk_dbg_uart_char(']');
#endif
        bdk_dbg_uart_str(") ");
        switch (state)
        {
            case STATE_START:
                bdk_dbg_uart_str("Starting");
                break;
            case STATE_WAIT_EIE:
                bdk_dbg_uart_str("Waitng for EIE");
                break;
            case STATE_WAIT_CDR:
                bdk_dbg_uart_str("Waiting for CDR");
                break;
            case STATE_WAIT_TRAIN_PRESET:
                bdk_dbg_uart_str("Waiting for first message");
                break;
            case STATE_MESSAGE_CHECK:
                bdk_dbg_uart_str("Running message check");
                break;
            case STATE_TRAINING_INIT:
                bdk_dbg_uart_str("Training - Starting");
                break;
            case STATE_TRAINING_IDLE:
                bdk_dbg_uart_str("Training - Idle");
                break;
            case STATE_TRAINING_UPDATE:
                bdk_dbg_uart_str("Training - Updated");
                break;
            case STATE_TRAINING_REQ:
                bdk_dbg_uart_str("Training - Request");
                break;
            case STATE_TRAINING_REQ_UPDATE:
                bdk_dbg_uart_str("Training - Request, Updated");
                break;
            case STATE_WAIT_FOR_READY:
                bdk_dbg_uart_str("Waiting for ready");
                break;
            case STATE_READY:
                bdk_dbg_uart_str("Lane ready");
                break;
        }
        bdk_dbg_uart_str("\r\n");
    }
    lstate->lane_state = state;
    /* Force RX ready = 0 in states before training */
    if (lstate->lane_state <= STATE_TRAINING_INIT)
        lstate->rx_ready = 0;
    /* Force RX ready = 1 in states after training */
    if (lstate->lane_state >= STATE_WAIT_FOR_READY)
        lstate->rx_ready = 1;

    /* Force message check done bit clear before its state */
    if (lstate->lane_state < STATE_MESSAGE_CHECK)
        lstate->chk_done = 0;
    /* Force message check done bit set after its state */
    if (lstate->lane_state > STATE_MESSAGE_CHECK)
        lstate->chk_done = 1;
}

/**
 * Check if a lane as performed Electrical Idle Exit. Lanes are not allowed to
 * proceed until EIE.
 *
 * @param ccpi_lane Lane to check
 */
static void lane_check_eie(int ccpi_lane)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    int qlm = 8 + ccpi_lane / 4;
    BDK_CSR_INIT(ocx_lnex_trn_ctl, node, BDK_OCX_LNEX_TRN_CTL(ccpi_lane));
    if (ocx_lnex_trn_ctl.s.eie_detect)
    {
        /* If we're waiting for EIE move to the next state */
        if (lstate->lane_state == STATE_WAIT_EIE)
            lane_change_state(ccpi_lane, STATE_WAIT_CDR);
    }
    else
    {
        /* Return to the waiting for EIE state */
        if (lstate->lane_state != STATE_WAIT_EIE)
            lane_change_state(ccpi_lane, STATE_WAIT_EIE);
    }
    BDK_CSR_INIT(srst, node, BDK_GSERX_LANE_SRST(qlm));
    if (srst.s.lsrst)
        BDK_CSR_WRITE(node, BDK_GSERX_LANE_SRST(qlm), 0);
}

/**
 * Check that CDR has occurred for a lane. Lanes are not allowed to continue
 * training until CDR.
 *
 * @param ccpi_lane Lane to check
 */
static void lane_check_cdr(int ccpi_lane)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    int qlm = 8 + ccpi_lane / 4;
    int lane = ccpi_lane & 3;

    if (lstate->lane_state < STATE_WAIT_CDR)
        return;

    BDK_CSR_INIT(eie_detsts, node, BDK_GSERX_RX_EIE_DETSTS(qlm));
    if ((1 << lane) & eie_detsts.s.cdrlock)
    {
        /* If we're waiting for CDR move to the next state */
        if (lstate->lane_state == STATE_WAIT_CDR)
        {
            BDK_CSR_INIT(ocx_qlmx_cfg, node, BDK_OCX_QLMX_CFG(qlm - 8));
            if (ocx_qlmx_cfg.s.trn_ena && ocx_qlmx_cfg.s.trn_rxeq_only)
            {
                /* RX equalization only */
                lstate->steps = 0;
                lane_change_state(ccpi_lane, STATE_WAIT_TRAIN_PRESET);
            }
            else if (ocx_qlmx_cfg.s.trn_ena)
            {
                /* KR Training */
                lane_change_state(ccpi_lane, STATE_WAIT_TRAIN_PRESET);
            }
            else
            {
                /* No Training, jump directly to wait for lane ready */
                lstate->steps = 0;
                lane_change_state(ccpi_lane, STATE_WAIT_FOR_READY);
            }
        }
    }
    else
    {
        /* Return to the waiting for CDR state */
        if (lstate->lane_state != STATE_WAIT_CDR)
            lane_change_state(ccpi_lane, STATE_WAIT_CDR);
    }
}

/**
 * Check that training message correctly deliver payload
 *
 * Before starting training, we check that the message protocol is working
 * by sending a sequence of incrementing numbers and verifying we get the same
 * number back. This is unrelated to the actual training, but proves training
 * message can send/receive without error.
 *
 * @param ccpi_lane Lane to check
 * @param is_master True if this node is the master
 */
static void lane_check_messaging(int ccpi_lane, bool is_master)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    int qlm = 8 + ccpi_lane / 4;
    if (lstate->lane_state <= STATE_WAIT_TRAIN_PRESET)
    {
        lstate->ld_cu.u = 0x3f;
        lstate->ld_cu.s.preset = 1;
        lstate->ld_sr.u = 0;
    }
    if (lstate->lane_state == STATE_WAIT_TRAIN_PRESET)
    {
        BDK_CSR_INIT(trn_ctl, node, BDK_OCX_LNEX_TRN_CTL(ccpi_lane));
        /* CN88XX pass 1.0 can't restart training */
        if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_0))
        {
            /* If training already completed, jump to STATE_WAIT_FOR_READY */
            if (trn_ctl.s.done)
            {
                if (do_trace)
                {
                    bdk_dbg_uart_str("Lane ");
                    uart_dec2(ccpi_lane);
                    bdk_dbg_uart_str(": Training complete too early on pass 1.0, skipping to STATE_WAIT_FOR_READY\r\n");
                }
                lstate->steps = 0;
                lane_change_state(ccpi_lane, STATE_WAIT_FOR_READY);
            }
        }
        else
        {
            /* Restart training */
            if (trn_ctl.s.done)
            {
                BDK_CSR_WRITE(node, BDK_OCX_LNEX_STATUS(ccpi_lane), 0);
                BDK_CSR_MODIFY(c, node, BDK_OCX_LNEX_TRN_CTL(ccpi_lane),
                    c.s.done = 0);
            }
        }
        if (lstate->lp_cu.s.preset)
            lane_change_state(ccpi_lane, STATE_MESSAGE_CHECK);
    }
    if (lstate->lane_state == STATE_MESSAGE_CHECK)
    {
        /* Respond to the current request */
        lstate->ld_sr.u = lstate->lp_cu.u & TRAIN_DATA_MASK;

        /* Check the response we got */
        int request = lstate->ld_cu.u & TRAIN_DATA_MASK;
        int response = lstate->lp_sr.u & TRAIN_DATA_MASK;
        if (response == request)
        {
            if (DEBUG_MESSAGE_CHECK && do_trace)
            {
                if (DEBUG_TRAIN_MESSAGES)
                {
                    bdk_dbg_uart_str("Lane ");
                    uart_dec2(ccpi_lane);
                    bdk_dbg_uart_str(": Message ");
                    uart_dec2(request);
                    bdk_dbg_uart_str(" was ACKed\r\n");
                }
                else
                {
                    bdk_dbg_uart_char(' ');
                    uart_dec2(request);
                    if ((request & 0x1f) == 0)
                        bdk_dbg_uart_str("\r\n");
                }
            }
            if (request == 0)
            {
                lstate->chk_done = 1;
                int finished = 1;
                for (int l = 0; l < CCPI_LANES; l++)
                    finished &= lane_state[l].chk_done;
                if (finished)
                    lane_change_state(ccpi_lane, STATE_TRAINING_INIT);
            }
            else
                lstate->ld_cu.u -= 3;
        }
        else if (response - 3 == request)
        {
            /* Partner is one behind, assume we just haven't gotten the update
               yet. Continue in current state */
            lstate->chk_done = 0;
        }
        else
        {
            /* Wrong message, start over */
            lstate->ld_cu.u = 0x3f;
            lstate->ld_cu.s.preset = 1;
            lstate->chk_done = 0;
            if ((request == 63) && !CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_0))
            {
                /* Check if most other lanes are past this step. If so, this lane
                   is stuck waiting for something that won't happen */
                int finished = 0;
                for (int l = 0; l < CCPI_LANES; l++)
                    finished += lane_state[l].chk_done;
                /* CN88XX pass 1.0 can't restart training */
                if (finished >= 21)
                {
                    if (do_trace)
                    {
                        bdk_dbg_uart_str("Lane ");
                        uart_dec2(ccpi_lane);
                        bdk_dbg_uart_str(": Training stuck, reseting QLM\r\n");
                    }
                    BDK_CSR_WRITE(node, BDK_GSERX_LANE_SRST(qlm), 1);
                    wait_usec(1000);
                }
            }
        }
    }
}

/**
 * Handle a training request from the link partner
 *
 * This function is called periodically to update lane tuning based on training
 * requests from the partner. It applies the settings and responds to the link
 * partner using the SR message.
 *
 * @param ccpi_lane Lane to handle
 */
static void lane_handle_training_request(int ccpi_lane)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    const union bdk_bgx_spu_br_train_cup_s lp_cu = lstate->lp_cu;
    union bdk_bgx_spu_br_train_rep_s ld_sr = lstate->ld_sr;
    state_t new_state = lstate->lane_state;

    bool have_request = (lp_cu.u != 0); /* True if we have a request from the partner */

    if ((lstate->lane_state == STATE_TRAINING_UPDATE) ||
        (lstate->lane_state == STATE_TRAINING_REQ_UPDATE))
    {
        /* We did a coef update and responded to the link partner. Wait until
           the link partner acks getting our response before clearing it.
           Response should have hold(0) for update stats (last 6 bits) */
        if (!have_request)
        {
            /* Clear SR now that the LP has seen it */
            ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_NOT_UPDATED;
            ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_NOT_UPDATED;
            ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_NOT_UPDATED;
            /* Back to training state as update is complete */
            new_state &= STATE_TRAINING_REQ;
        }
    }
    else if (have_request) /* We got a new request */
    {
        if (lp_cu.s.init && !(lp_cu.u & TRAIN_DATA_MASK))
        {
            lstate->tx_pre = lstate->init_pre;
            lstate->tx_main = lstate->init_main;
            lstate->tx_post = lstate->init_post;
            ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
            ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
            ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
            if (DEBUG_PARAMETERS)
                bdk_dbg_uart_str("Received INIT\r\n");
        }

        if (lp_cu.s.preset)
        {
            bdk_dbg_uart_str("Received PRESET, restarting training\r\n");
            lane_change_state(ccpi_lane, STATE_WAIT_TRAIN_PRESET);
        }

        /* INIT set and direction hints is illegal in normal training. We
           use it as a special message to set the init values from the
           remote node. 1-31=tx_swing, 32-47=tx_post, 48-58=tx_pre,
           59-63=reserved */
        if (lp_cu.s.init && (lp_cu.u & TRAIN_DATA_MASK))
        {
            int v = lp_cu.u & TRAIN_DATA_MASK;
            if (v < 32) /* Request to set init swing */
            {
                lstate->init_main = v - 1;
                ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                if (DEBUG_PARAMETERS)
                {
                    bdk_dbg_uart_str("Received param tx_swing=");
                    uart_dec2(lstate->init_main);
                    bdk_dbg_uart_str("\r\n");
                }
            }
            else if (v < 48) /* Request to set init post */
            {
                lstate->init_post = v - 32;
                ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                if (DEBUG_PARAMETERS)
                {
                    bdk_dbg_uart_str("Received param tx_post=");
                    uart_dec2(lstate->init_post);
                    bdk_dbg_uart_str("\r\n");
                }
            }
            else if (v < 59) /* Request to set init pre */
            {
                lstate->init_pre = v - 48;
                ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                if (DEBUG_PARAMETERS)
                {
                    bdk_dbg_uart_str("Received param tx_pre=");
                    uart_dec2(lstate->init_pre);
                    bdk_dbg_uart_str("\r\n");
                }
            }
            else if (v == 59) /* Request to set long channel */
            {
                ccpi_channel_length(ccpi_lane, false);
                ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                if (DEBUG_PARAMETERS)
                    bdk_dbg_uart_str("Received param channel=long\r\n");
            }
            else if (v == 60) /* Request to set short channel */
            {
                ccpi_channel_length(ccpi_lane, true);
                ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                if (DEBUG_PARAMETERS)
                    bdk_dbg_uart_str("Received param channel=short\r\n");
            }
        }

        if (lp_cu.s.main_cup && !lp_cu.s.init)
        {
            /* 0=max amplitude, 25=min amplitude */
            if (lp_cu.s.main_cup == BDK_BGX_SPU_BR_TRAIN_CUP_E_INCREMENT)
            {
                if (is_tuning_valid(lstate->tx_main - 1, lstate->tx_pre, lstate->tx_post))
                {
                    lstate->tx_main--;
                    ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                }
                else
                {
                    ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_MAXIMUM;
                }
            }
            else if (lp_cu.s.main_cup == BDK_BGX_SPU_BR_TRAIN_CUP_E_DECREMENT)
            {
                if (is_tuning_valid(lstate->tx_main + 1, lstate->tx_pre, lstate->tx_post))
                {
                    lstate->tx_main++;
                    ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                }
                else
                {
                    ld_sr.s.main_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_MINIMUM;
                }
            }
        }

        if (lp_cu.s.post_cup && !lp_cu.s.init)
        {
            /* 0=max post emphasis, 15=min post emphasis */
            if (lp_cu.s.post_cup == BDK_BGX_SPU_BR_TRAIN_CUP_E_INCREMENT)
            {
                if (is_tuning_valid(lstate->tx_main, lstate->tx_pre, lstate->tx_post - 1))
                {
                    lstate->tx_post--;
                    ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                }
                else
                {
                    ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_MAXIMUM;
                }
            }
            else if (lp_cu.s.post_cup == BDK_BGX_SPU_BR_TRAIN_CUP_E_DECREMENT)
            {
                if (is_tuning_valid(lstate->tx_main, lstate->tx_pre, lstate->tx_post + 1))
                {
                    lstate->tx_post++;
                    ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                }
                else
                {
                    ld_sr.s.post_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_MINIMUM;
                }
            }
        }

        if (lp_cu.s.pre_cup && !lp_cu.s.init)
        {
            /* 0=max pre emphasis, 10=min pre emphasis */
            if (lp_cu.s.pre_cup == BDK_BGX_SPU_BR_TRAIN_CUP_E_INCREMENT)
            {
                if (is_tuning_valid(lstate->tx_main, lstate->tx_pre - 1, lstate->tx_post))
                {
                    lstate->tx_pre--;
                    ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                }
                else
                {
                    ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_MAXIMUM;
                }
            }
            else if (lp_cu.s.pre_cup == BDK_BGX_SPU_BR_TRAIN_CUP_E_DECREMENT)
            {
                if (is_tuning_valid(lstate->tx_main, lstate->tx_pre + 1, lstate->tx_post))
                {
                    lstate->tx_pre++;
                    ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_UPDATED;
                }
                else
                {
                    ld_sr.s.pre_cst = BDK_BGX_SPU_BR_TRAIN_CST_E_MINIMUM;
                }
            }
        }

        if (DEBUG_TUNING_CHANGES && do_trace)
        {
            bdk_dbg_uart_str("Lane ");
            uart_dec2(ccpi_lane);
            bdk_dbg_uart_str(": Set Main=");
            uart_dec2(lstate->tx_main);
            bdk_dbg_uart_str(", Post=");
            uart_dec2(lstate->tx_post);
            bdk_dbg_uart_str(", Pre=");
            uart_dec2(lstate->tx_pre);
            bdk_dbg_uart_str("\r\n");
        }
        ccpi_tx_tune(ccpi_lane, lstate->tx_main, lstate->tx_pre, lstate->tx_post);
        new_state |= STATE_TRAINING_UPDATE;
    }

    /* Lane is considered stable when RX equalization is requesting all holds
       and we don't have a pending request */
    bool lane_stable = (lstate->desired_main == RXT_ESM_HOLD);
    lane_stable &= (lstate->desired_post == RXT_ESM_HOLD);
    lane_stable &= (lstate->desired_pre == RXT_ESM_HOLD);
    if (lstate->steps >= CCPI_MAX_STEPS)
        lane_stable = true;
    lane_stable &= ((lstate->ld_cu.u & TRAIN_DATA_MASK) == 0);
    lane_stable &= (lstate->steps >= 4);
    lstate->rx_ready = lane_stable;
    if (DEBUG_ONE_LANE_AT_A_TIME)
    {
        ld_sr.s.rx_ready |= lstate->rx_ready;
    }
    else
    {
        int finished = 1;
        for (int l = 0; l < CCPI_LANES; l++)
            finished &= lane_state[l].rx_ready;
        ld_sr.s.rx_ready |= finished;
    }

    lstate->ld_sr = ld_sr;

    if (lstate->lane_state != new_state)
        lane_change_state(ccpi_lane, new_state);
}

static union bdk_bgx_spu_br_train_cup_s lane_do_param_request(int ccpi_lane)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    int qlm = 8 + ccpi_lane / 4;
    int lane = ccpi_lane & 3;
    union bdk_bgx_spu_br_train_cup_s ld_cu = {.u = 0};

    if (lstate->steps == 0) /* Send TX Swing */
    {
        ld_cu.u = lstate->init_main;
        int tx_swing = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_SWING, node+1, qlm, lane);
        if (tx_swing != -1)
            ld_cu.u = tx_swing;
        if (DEBUG_PARAMETERS)
        {
            bdk_dbg_uart_str("Sent param tx_swing=");
            uart_dec2(ld_cu.u);
            bdk_dbg_uart_str("\r\n");
        }
        ld_cu.u += 1; /* Encode as 1-31 */
        ld_cu.s.init = 1;
    }
    else if (lstate->steps == 1) /* Send TX Post */
    {
        ld_cu.u = lstate->init_post;
        int tx_premptap = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_PREMPTAP, node+1, qlm, lane);
        if (tx_premptap != -1)
            ld_cu.u = tx_premptap >> 4;
        if (DEBUG_PARAMETERS)
        {
            bdk_dbg_uart_str("Sent param tx_post=");
            uart_dec2(ld_cu.u);
            bdk_dbg_uart_str("\r\n");
        }
        ld_cu.u += 32; /* Encode as 32-47 */
        ld_cu.s.init = 1;
    }
    else if (lstate->steps == 2) /* Send TX Pre */
    {
        ld_cu.u = lstate->init_pre;
        int tx_premptap = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_PREMPTAP, node+1, qlm, lane);
        if (tx_premptap != -1)
            ld_cu.u = tx_premptap & 0xf;
        if (DEBUG_PARAMETERS)
        {
            bdk_dbg_uart_str("Sent param tx_pre=");
            uart_dec2(ld_cu.u);
            bdk_dbg_uart_str("\r\n");
        }
        ld_cu.u += 48; /* Encode as 48-58 */
        ld_cu.s.init = 1;
    }
    else if (lstate->steps == 3) /* Send Channel length */
    {
        int channel_loss = bdk_config_get_int(BDK_CONFIG_QLM_CHANNEL_LOSS, node+1, qlm);
        bool short_channel = is_short_channel(channel_loss);
        if (short_channel)
            ld_cu.u = 60; /* Short channel */
        else
            ld_cu.u = 59; /* Long channel */
        if (DEBUG_PARAMETERS)
        {
            bdk_dbg_uart_str("Sent channel=");
            bdk_dbg_uart_str(short_channel ? "short" : "long");
            bdk_dbg_uart_str("\r\n");
        }
        ld_cu.s.init = 1;
    }
    else if (lstate->steps == 4) /* Send INIT */
    {
        ld_cu.u = 0;
        ld_cu.s.init = 1;
        if (DEBUG_PARAMETERS)
            bdk_dbg_uart_str("Sent INIT\r\n");
    }
    return ld_cu;
}

/**
 * Perform link training for the local device
 *
 * This function looks at the RX equalization results and sends training
 * requests to the link partner. It doesn't update the local SERDES, just
 * asks the link partner to make updates
 *
 * @param ccpi_lane Lane running training
 * @param is_master True if this node is the master
 */
static void lane_do_training(int ccpi_lane, bool is_master)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    const union bdk_bgx_spu_br_train_rep_s lp_sr = lstate->lp_sr;
    union bdk_bgx_spu_br_train_cup_s ld_cu = lstate->ld_cu;

    bool have_request = (ld_cu.u != 0); /* True if we have a request to the partner that isn't ACKed */
    bool have_response = (lp_sr.u & TRAIN_DATA_MASK) != 0; /* True if the partner sent a response (ACK) */

    if (have_response)
    {
        if (have_request)
        {
            ld_cu.s.init = 0;
            ld_cu.s.preset = 0;
            ld_cu.s.main_cup = BDK_BGX_SPU_BR_TRAIN_CUP_E_HOLD;
            ld_cu.s.post_cup = BDK_BGX_SPU_BR_TRAIN_CUP_E_HOLD;
            ld_cu.s.pre_cup = BDK_BGX_SPU_BR_TRAIN_CUP_E_HOLD;
            lstate->ld_cu = ld_cu;
            lane_change_state(ccpi_lane, lstate->lane_state & STATE_TRAINING_UPDATE);
        }
        return;
    }

    if (have_request || (lstate->steps >= CCPI_MAX_STEPS))
        return;

    if ((lstate->steps < 5) && is_master)
        ld_cu = lane_do_param_request(ccpi_lane);
    else if (lstate->ld_sr.s.rx_ready)
        ld_cu.u = 0; /* Don't allow any more requests if we already said we're ready */
    else if (lstate->desired_main == RXT_ESM_INC)
        ld_cu.s.main_cup = BDK_BGX_SPU_BR_TRAIN_CUP_E_INCREMENT;
    else if (lstate->desired_main == RXT_ESM_DEC)
        ld_cu.s.main_cup = BDK_BGX_SPU_BR_TRAIN_CUP_E_DECREMENT;
    else if (lstate->desired_post == RXT_ESM_INC)
        ld_cu.s.post_cup = BDK_BGX_SPU_BR_TRAIN_CUP_E_INCREMENT;
    else if (lstate->desired_post == RXT_ESM_DEC)
        ld_cu.s.post_cup = BDK_BGX_SPU_BR_TRAIN_CUP_E_DECREMENT;
    else if (lstate->desired_pre == RXT_ESM_INC)
        ld_cu.s.pre_cup = BDK_BGX_SPU_BR_TRAIN_CUP_E_INCREMENT;
    else if (lstate->desired_pre == RXT_ESM_DEC)
        ld_cu.s.pre_cup = BDK_BGX_SPU_BR_TRAIN_CUP_E_DECREMENT;

    lstate->ld_cu = ld_cu;
    lstate->steps++; /* Increment number of request steps */
    if (ld_cu.u)
    {
        lane_change_state(ccpi_lane, lstate->lane_state | STATE_TRAINING_REQ);
    }
}

/**
 * Handles the state machine for KR training
 *
 * @param ccpi_lane Lane to train
 * @param is_master True if this node is the master
 */
static void lane_check_training(int ccpi_lane, bool is_master)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];

    if (lstate->lane_state == STATE_TRAINING_INIT)
    {
        /* Show link partner we are in INIT */
        lstate->ld_cu.u = 0;
        lstate->ld_cu.s.init = 1;
        lane_change_state(ccpi_lane, STATE_TRAINING_REQ);
        return;
    }

    if ((lstate->lane_state < STATE_TRAINING_IDLE) ||
        (lstate->lane_state > STATE_TRAINING_REQ_UPDATE))
        return;

    if (lstate->lp_cu.s.preset)
    {
        /* Respond to the current request, other guy is still in STATE_MESSAGE_CHECK */
        lstate->ld_sr.u = lstate->lp_cu.u & TRAIN_DATA_MASK;
    }
    else
    {
        /* Handle link partner request */
        lane_handle_training_request(ccpi_lane);

        /* Make request to link partner for better tuning */
        lane_do_training(ccpi_lane, is_master);

        BDK_CSR_INIT(trn_ctl, node, BDK_OCX_LNEX_TRN_CTL(ccpi_lane));
        if (trn_ctl.s.done)
        {
            lstate->steps = 0;
            lane_change_state(ccpi_lane, STATE_WAIT_FOR_READY);
        }
    }
}

/**
 * Checks if lane is ready for use
 *
 * After a lane finishes training, we wait for CCPI to make the lane good and
 * ready for use. If it is marked bad, we clear the flag and resart the lane.
 *
 * @param ccpi_lane Lane to check
 */
static void lane_check_ready(int ccpi_lane)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    int ccpi_qlm = ccpi_lane / 4;
    int lane = ccpi_lane & 3;

    /* Don't check for ready until all other training is complete */
    if (lstate->lane_state < STATE_WAIT_FOR_READY)
        return;

    /* Lane is ready if SER_LANE_READY is set and SER_LANE_BAD is clear */
    BDK_CSR_INIT(qlmx_cfg, node, BDK_OCX_QLMX_CFG(ccpi_qlm));
    bool is_ready = ((qlmx_cfg.s.ser_lane_ready & (1 << lane)) &&
                     !(qlmx_cfg.s.ser_lane_bad & (1 << lane)));

    if (is_ready)
    {
        /* Count how many times we are ready in row. Limit to 5 */
        if (lstate->steps < 5)
            lstate->steps++;
        /* Transition to ready if we've been ready 10 loops in a row */
        if ((lstate->steps >= 5) && (lstate->lane_state != STATE_READY))
            lane_change_state(ccpi_lane, STATE_READY);
    }
    else
    {
        /* Not ready, retry. In rare cases it seems necessary to toggle
           SER_LANE_BAD to restart a lane, which is why there is a
           write/read/write sequence below */
        qlmx_cfg.s.ser_lane_ready = 0xf;
        qlmx_cfg.s.ser_lane_bad |= 1 << lane;
        BDK_CSR_WRITE(node, BDK_OCX_QLMX_CFG(ccpi_qlm), qlmx_cfg.u);
        BDK_CSR_READ(node, BDK_OCX_QLMX_CFG(ccpi_qlm));
        wait_usec(10000); /* 1ms proved to be too short in rare conditions */
        qlmx_cfg.s.ser_lane_bad = 0;
        BDK_CSR_WRITE(node, BDK_OCX_QLMX_CFG(ccpi_qlm), qlmx_cfg.u);
        wait_usec(10000); /* 1ms proved to be too short in rare conditions */
        /* Set count to zero */
        lstate->steps = 0;
        /* Change our state if needed */
        if (lstate->lane_state > STATE_WAIT_FOR_READY)
            lane_change_state(ccpi_lane, STATE_WAIT_FOR_READY);
    }
}

/**
 * Step the lane state machine
 *
 * @param ccpi_lane Lane to update
 * @param is_master True if this node is the master
 */
static void lane_state_update(int ccpi_lane, bool is_master)
{
    lane_state_t *lstate = &lane_state[ccpi_lane];
    /* Unconditionally move from the start state to EIE detect */
    if (lstate->lane_state == STATE_START)
        lane_change_state(ccpi_lane, STATE_WAIT_EIE);

    /* Update Link Partner message state */
    ccpi_update_lp_messages(ccpi_lane);

    lane_check_eie(ccpi_lane);
    lane_check_cdr(ccpi_lane);
    lane_check_messaging(ccpi_lane, is_master);
    lane_check_training(ccpi_lane, is_master);
    lane_check_ready(ccpi_lane);

    /* Update local device message state */
    BDK_CSR_MODIFY(c, node, BDK_OCX_LNEX_TRN_LD(ccpi_lane),
        if (DEBUG_TRAIN_MESSAGES && do_trace && (c.s.ld_cu_dat != lstate->ld_cu.u))
        {
            bdk_dbg_uart_str("Lane ");
            uart_dec2(ccpi_lane);
            bdk_dbg_uart_str(": LD CU ");
            bdk_dbg_uart_hex(c.s.ld_cu_dat);
            bdk_dbg_uart_str(" -> ");
            bdk_dbg_uart_hex(lstate->ld_cu.u);
            bdk_dbg_uart_str("\r\n");
        }
        if (DEBUG_TRAIN_MESSAGES && do_trace && (c.s.ld_sr_dat != lstate->ld_sr.u))
        {
            bdk_dbg_uart_str("Lane ");
            uart_dec2(ccpi_lane);
            bdk_dbg_uart_str(": LD SR ");
            bdk_dbg_uart_hex(c.s.ld_sr_dat);
            bdk_dbg_uart_str(" -> ");
            bdk_dbg_uart_hex(lstate->ld_sr.u);
            bdk_dbg_uart_str("\r\n");
        }
        c.s.ld_cu_dat = lstate->ld_cu.u;
        c.s.ld_sr_dat = lstate->ld_sr.u);
}

/**
 * Called very early in during init of both the master and slave. It performs one
 * time init of CCPI QLM and link parameters. It must only be called once per
 * boot.
 *
 * @param is_master Non-zero if the caller is the master node
 */
void __bdk_init_ccpi_early(int is_master)
{
    /* Bail early if CCPI is disabled */
    BDK_CSR_INIT(gserx_phy_ctl, node, BDK_GSERX_PHY_CTL(8));
    if (gserx_phy_ctl.s.phy_reset)
        return;

    /* Make sure the link layer is down by disabling lane alignment */
    for (int link = 0; link < CCPI_MAX_LINKS; link++)
        BDK_CSR_MODIFY(c, node, BDK_OCX_LNKX_CFG(link),
            c.s.lane_align_dis = 1);

    BDK_CSR_INIT(ocx_qlmx_cfg, node, BDK_OCX_QLMX_CFG(0));
    if (ocx_qlmx_cfg.s.trn_ena)
    {
        /* Force training to stop while we make changes. CN88XX pass 1.0
           can't restart training, so this code doesn't run on that chip */
        if (!CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_0))
        {
            for (int ccpi_lane = 0; ccpi_lane < CCPI_LANES; ccpi_lane++)
            {
                BDK_CSR_DEFINE(trn_ctl, BDK_OCX_LNEX_TRN_CTL(ccpi_lane));
                trn_ctl.u = 0;
                trn_ctl.s.done = 1;
                BDK_CSR_WRITE(node, BDK_OCX_LNEX_TRN_CTL(ccpi_lane), trn_ctl.u);
            }
            wait_usec(100000);
        }

        /* Force training into manual mode so we can control it */
        for (int ccpi_lane = 0; ccpi_lane < CCPI_LANES; ccpi_lane++)
        {
            BDK_CSR_DEFINE(trn_ld, BDK_OCX_LNEX_TRN_LD(ccpi_lane));
            trn_ld.u = 0;
            trn_ld.s.lp_manual = 1;
            BDK_CSR_WRITE(node, BDK_OCX_LNEX_TRN_LD(ccpi_lane), trn_ld.u);
        }

        for (int ccpi_qlm = 0; ccpi_qlm < 6; ccpi_qlm++)
        {
            /* Disable Each GSER Lane KR Training Time-out timer (330msec) */
            for (int lane = 0; lane < 4; lane++)
            {
                BDK_CSR_MODIFY(c, node, BDK_GSERX_BR_RXX_CTL(ccpi_qlm + 8, lane),
                    c.s.rxt_adtmout_disable = 1; /* Disable timer */
                    c.s.rxt_swm = 1); /* Software control of RX equalization */
            }
            int baud_mhz = ccpi_get_speed();
            /* Errata (GSER-25992) RX EQ Default Settings Update */
            __bdk_qlm_errata_gser_25992(node, ccpi_qlm + 8, baud_mhz);
            /* Errata (GSER-26150) 10G PHY PLL Temperature Failure */
            __bdk_qlm_errata_gser_26150(node, ccpi_qlm + 8, baud_mhz);
            /* Errata (GSER-26636) 10G-KR/40G-KR - Inverted Tx Coefficient Direction Change */
            __bdk_qlm_errata_gser_26636(node, ccpi_qlm + 8, baud_mhz);
            /* Errata (GSER-27140) SERDES temperature drift sensitivity in receiver */
            __bdk_qlm_errata_gser_27140(node, ccpi_qlm + 8, baud_mhz, -1);
            /* Errata (GSER-27882) GSER 10GBASE-KR Transmit Equalizer */
            /* Doesn't apply since we are training is software */
        }
    }

    /* We use L2C_OCI_CTL[iofrcl] to remember if this code has been run
       when we pass through multiple images */
    BDK_CSR_MODIFY(c, node, BDK_L2C_OCI_CTL,
        c.s.iofrcl = 0);

    /* Disable the bad lane timer and clear all bad bits */
    for (int ccpi_qlm = 0; ccpi_qlm < 6; ccpi_qlm++)
    {
        BDK_CSR_MODIFY(c, node, BDK_OCX_QLMX_CFG(ccpi_qlm),
            c.s.timer_dis = 1;
            c.s.ser_lane_bad = 0);
    }
}

/**
 * Brings the CCPI lanes and links into an operational state without perofrming
 * node discovery and enumeration. After this function succeeds, CCPI lanes and
 * links are ready for traffic, but node routing has not been setup.
 *
 * Note this function runs on the slave node with the BDK code not at its link
 * address. Many normal BDK functions do not work properly. Be careful.
 *
 * @param is_master  Non-zero when run on the master node. Zero when run on the slave
 * @param gbaud      Baud rate to run links at. This is only used if the QLMs are in software init
 *                   mode. If they are strapped for hardware init, the strapping speed is used.
 * @param ccpi_trace Non-zero to enable CCPI tracing. Note that tracing doesn't use the standard
 *                   bdk-trace functions. This code runs on the secondary node before we are
 *                   multi-node, and the C library doesn't work right.
 *
 * @return Zero on success, negative on failure. Zero means CCPI lanes and links are
 *         functional.
 */
int __bdk_init_ccpi_connection(int is_master, uint64_t gbaud, int ccpi_trace)
{
    do_trace = ccpi_trace;
    /* Bail early if CCPI is disabled */
    BDK_CSR_INIT(gserx_phy_ctl, node, BDK_GSERX_PHY_CTL(8));
    if (gserx_phy_ctl.s.phy_reset)
        return -1;
    int baud_mhz = ccpi_get_speed();

    memset(lane_state, 0, sizeof(lane_state));
    for (int ccpi_lane = 0; ccpi_lane < CCPI_LANES; ccpi_lane++)
    {
        lane_state_t *lstate = &lane_state[ccpi_lane];
        lstate->init_main = TRAIN_INIT_TX_MAIN;
        lstate->init_post = TRAIN_INIT_TX_POST;
        lstate->init_pre = TRAIN_INIT_TX_PRE;
    }

    if (is_master)
    {
        BDK_CSR_INIT(eie_detsts, node, BDK_GSERX_RX_EIE_DETSTS(8));
        if (eie_detsts.s.cdrlock == 0)
        {
            if (do_trace)
                bdk_dbg_uart_str("No CDR lock on QLM8, assuming multi-node not available\r\n");
            return -1;
        }
        for (int ccpi_lane = 0; ccpi_lane < CCPI_LANES; ccpi_lane++)
        {
            lane_state_t *lstate = &lane_state[ccpi_lane];
            int qlm = 8 + ccpi_lane / 4;
            int lane = ccpi_lane & 3;

            /* Master has access to config data, read defaults */
            int tx_swing = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_SWING, node, qlm, lane);
            if (tx_swing != -1)
                lstate->init_main = tx_swing;

            int tx_premptap = bdk_config_get_int(BDK_CONFIG_QLM_TUNING_TX_PREMPTAP, node, qlm, lane);
            if (tx_premptap != -1)
            {
                lstate->init_post = tx_premptap >> 4;
                lstate->init_pre = tx_premptap & 0xf;
            }
            int channel_loss = bdk_config_get_int(BDK_CONFIG_QLM_CHANNEL_LOSS, node, qlm);
            ccpi_channel_loss(ccpi_lane, channel_loss);
        }
        ccpi_set_lane_reversal();
    }

    /* Configure the starting tuning settings */
    for (int ccpi_lane = 0; ccpi_lane < CCPI_LANES; ccpi_lane++)
    {
        lane_state_t *lstate = &lane_state[ccpi_lane];
        lstate->tx_main = lstate->init_main;
        lstate->tx_post = lstate->init_post;
        lstate->tx_pre = lstate->init_pre;
        ccpi_tx_tune(ccpi_lane, lstate->tx_main, lstate->tx_pre, lstate->tx_post);
    }

    /* Wait 100ms after making changes before continuing */
    wait_usec(100000);

    const uint64_t one_second = REF_CLOCK;
    const uint64_t start_time = get_ref_clock();
    const uint64_t master_timeout = start_time + one_second * CCPI_MASTER_TIMEOUT;

    if (do_trace || node)
    {
        BDK_CSR_INIT(mio_fus_dat2, node, BDK_MIO_FUS_DAT2);
        int major_pass = ((mio_fus_dat2.s.chip_id >> 3) & 7) + 1;
        int minor_pass = mio_fus_dat2.s.chip_id & 7;
        bdk_dbg_uart_str("\r\n\r\n");
        bdk_dbg_uart_str(bdk_version_string());
        bdk_dbg_uart_str("\r\n");
        bdk_dbg_uart_str("Node ");
        uart_dec1(node);
        if (BDK_DISPLAY_PASS)
        {
            bdk_dbg_uart_str(" Pass ");
            uart_dec1(major_pass);
            bdk_dbg_uart_char('.');
            uart_dec1(minor_pass);
        }
        bdk_dbg_uart_str(", CCPI Speed ");
        uart_dec2(baud_mhz / 100);
        uart_dec2(baud_mhz % 100);

        BDK_CSR_INIT(ocx_qlmx_cfg, node, BDK_OCX_QLMX_CFG(0));
        if (ocx_qlmx_cfg.s.trn_ena && ocx_qlmx_cfg.s.trn_rxeq_only)
            bdk_dbg_uart_str(", RX equalization only\r\n");
        else if (ocx_qlmx_cfg.s.trn_ena)
            bdk_dbg_uart_str(", KR Training\r\n");
        else
            bdk_dbg_uart_str(", No Training\r\n");
        bdk_dbg_uart_str("\r\n");
    }

    /* Loop forever trying to get CCPI links up */
    while (1)
    {
        BDK_CSR_WRITE(node, BDK_GTI_CWD_POKEX(bdk_get_core_num()), 0);
        uint64_t wall_time = get_ref_clock();

        if (is_master && (wall_time >= master_timeout))
        {
            if (do_trace)
            {
                display_tuning_state_all();
                bdk_dbg_uart_str("CCPI timeout, multi-node not available\r\n");
            }
            return -1;
        }

        /* The node ID may change while we're running */
        int mpidr_el1;
        BDK_MRS(MPIDR_EL1, mpidr_el1);
        node = bdk_extract(mpidr_el1, 16, 8);

        /* Perform RX equalization on all lanes, updating the training
           direction hints */
        ccpi_update_rx_equalization();
        if (do_trace)
            display_state();

        /* Loop updating the state of each lane. Count how many lanes
           are up and running */
        int good_lanes = 0;
        for (int ccpi_lane = 0; ccpi_lane < CCPI_LANES; ccpi_lane++)
        {
            lane_state_update(ccpi_lane, is_master);
            /* For debug, we only do one lane at a time so it is easy to
               follow. We don't check a lane until all lanes before it are
               done with training. Note that lanes bounce in and out of ready
               while lanes next to them come up. Too slow for production */
            if (DEBUG_ONE_LANE_AT_A_TIME &&
                (lane_state[ccpi_lane].lane_state < STATE_WAIT_FOR_READY))
                break;
            if (lane_state[ccpi_lane].lane_state == STATE_READY)
                good_lanes++;
        }

        /* Don't check links until all lanes are up */
        if (good_lanes < CCPI_LANES)
        {
            BDK_CSR_INIT(ocx_lnkx_cfg, node, BDK_OCX_LNKX_CFG(0));
            if (ocx_lnkx_cfg.s.lane_align_dis == 0)
            {
                if (do_trace)
                    bdk_dbg_uart_str("Lanes not ready, disabling lane alignment\n");
                /* Make sure the link layer is down using lane alignment */
                for (int link = 0; link < CCPI_MAX_LINKS; link++)
                    BDK_CSR_MODIFY(c, node, BDK_OCX_LNKX_CFG(link),
                        c.s.lane_align_dis = 1);
            }
            /* Skip the rest of the loop body until lanes are all good */
            continue;
        }

        int valid_links = 0;
        /* Check that the three CCPI links are operating */
        for (int link = 0; link < CCPI_MAX_LINKS; link++)
        {
            BDK_CSR_INIT(ocx_lnkx_cfg, node, BDK_OCX_LNKX_CFG(link));
            BDK_CSR_INIT(ocx_com_linkx_ctl, node, BDK_OCX_COM_LINKX_CTL(link));

            /* If lane alignment is disabled, enable it */
            if (ocx_lnkx_cfg.s.lane_align_dis)
            {
                ocx_lnkx_cfg.s.lane_align_dis = 0;
                BDK_CSR_WRITE(node, BDK_OCX_LNKX_CFG(link), ocx_lnkx_cfg.u);
                if (do_trace)
                {
                    bdk_dbg_uart_str("Link ");
                    uart_dec1(link);
                    bdk_dbg_uart_str(": All lanes ready, enabling lane alignment\r\n");
                }
            }
            /* Clear bits that can get set by hardware/software on error */
            else if (ocx_com_linkx_ctl.s.auto_clr || ocx_com_linkx_ctl.s.drop ||
                ocx_com_linkx_ctl.s.reinit)
            {
                ocx_com_linkx_ctl.s.auto_clr = 0;
                ocx_com_linkx_ctl.s.drop = 0;
                ocx_com_linkx_ctl.s.reinit = 0;
                BDK_CSR_WRITE(node, BDK_OCX_COM_LINKX_CTL(link), ocx_com_linkx_ctl.u);
                /* Give link 10ms to update */
                wait_usec(10000);
            }
            /* If the link is up and valid, check the credits */
            else if (ocx_com_linkx_ctl.s.up && ocx_com_linkx_ctl.s.valid)
            {
                BDK_CSR_INIT(ocx_tlkx_lnk_vcx_cnt, node, BDK_OCX_TLKX_LNK_VCX_CNT(link, 0));
                if (ocx_tlkx_lnk_vcx_cnt.s.count == 0)
                {
                    /* No credits, perform a reinit */
                    ocx_com_linkx_ctl.s.reinit = 1;
                    BDK_CSR_WRITE(node, BDK_OCX_COM_LINKX_CTL(link), ocx_com_linkx_ctl.u);
                    /* Give link 10ms to update */
                    wait_usec(10000);
                    /* Reinit will be cleared the next time through the loop */
                    if (do_trace)
                    {
                        bdk_dbg_uart_str("Link ");
                        uart_dec1(link);
                        bdk_dbg_uart_str(": Re-init\r\n");
                    }
                }
                else
                    valid_links |= 1 << link;
            }
        }

        /* Require the links to be valid before marking everything good */
        if (bdk_pop(valid_links) >= CCPI_MIN_LINKS)
        {
            /* Reset if we loose a link */
            BDK_CSR_WRITE(node, BDK_RST_OCX, valid_links);
            BDK_CSR_READ(node, BDK_RST_OCX);
            if (do_trace)
                display_tuning_state_all();
            if (do_trace || node)
            {
                uart_dec1(bdk_pop(valid_links));
                bdk_dbg_uart_str(" CCPI links up\r\n");
            }
            return 0;
        }
    }
}

/**
 * This function is called if we boot on a node that isn't the
 * one we were linked for
 */
void __bdk_init_incorrect_node(void)
{
    /* We're booting from a non-zero node. We can't call many C functions as
       we're running at an address other than our link address */
    int uart = 0;
    node = bdk_numa_local();

    /* Don't reset if a link change state */
    BDK_CSR_WRITE(node, BDK_RST_OCX, 0);
    __bdk_init_ccpi_early(0);

    /* Temporarily change the master node global to this node so some
       functions will work properly when called */
    extern int __bdk_numa_master_node;
    __bdk_numa_master_node = node;

    /* Power gate other cores */
    BDK_CSR_WRITE(node, BDK_RST_PP_POWER, -1);

    /* Setup the uart using only inline C functons */
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart),
        c.s.uaa_rst = 1;
        c.s.uctl_rst = 1);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart),
        c.s.h_clkdiv_sel = 3; /* Run at SCLK / 6, matches emulator */
        c.s.h_clk_byp_sel = 0;
        c.s.h_clk_en = 1);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart),
        c.s.h_clkdiv_rst = 0);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart), c.s.uctl_rst = 0);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart), c.s.uaa_rst = 0);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_UCTL_CTL(uart), c.s.csclk_en = 1);
    BDK_CSR_INIT(rst_boot, node, BDK_RST_BOOT);

    uint64_t divisor_x_64 = 50000000ull * rst_boot.s.pnr_mul / (BDK_UART_BAUDRATE * 16 * 6 / 64);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_IBRD(uart),
        c.s.baud_divint = divisor_x_64 >> 6);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_FBRD(uart),
        c.s.baud_divfrac = divisor_x_64 & 0x3f);
    BDK_CSR_MODIFY(c, node, BDK_UAAX_LCR_H(uart),
        c.s.sps = 0; /* No parity */
        c.s.wlen = 3; /* 8 bits */
        c.s.fen = 1; /* FIFOs enabled */
        c.s.stp2 = 0; /* Use one stop bit, not two */
        c.s.eps = 0; /* No parity */
        c.s.pen = 0; /* No parity */
        c.s.brk = 0); /* Don't send a break */
    BDK_CSR_MODIFY(c, node, BDK_UAAX_CR(uart),
        c.s.ctsen = 0;
        c.s.rtsen = 0;
        c.s.out1 = 1; /* Drive data carrier detect */
        c.s.rts = 0; /* Don't override RTS */
        c.s.dtr = 0; /* Don't override DTR */
        c.s.rxe = 1; /* Enable receive */
        c.s.txe = 1; /* Enable transmit */
        c.s.lbe = 0; /* Disable loopback */
        c.s.uarten = 1); /* Enable uart */
    BDK_CSR_READ(node, BDK_UAAX_CR(uart));

    /* Pass 2 report bad model on some resets */
    uint64_t model;
    asm ("mrs %[rd],MIDR_EL1" : [rd] "=r" (model));
    if (model == 0x430f0a17)
    {
        bdk_dbg_uart_str("Soft reset to fix MIDR_EL1\r\n");
        wait_usec(500000);
        BDK_CSR_READ(node, BDK_RST_SOFT_RST);
        BDK_CSR_WRITE(node, BDK_RST_SOFT_RST, 1);
    }

    strcpy(bdk_phys_to_ptr(bdk_numa_get_address(node, BDK_KEY_MEMX(0))), bdk_version_string());

    __bdk_init_ccpi_connection(false, 0, false);
    bdk_dbg_uart_str("Putting core in reset\r\n");
    __bdk_reset_thread(0, NULL);
}
