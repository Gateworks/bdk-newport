/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "bdk-qlm-common.h"
#include "bdk-qlm-common-gserp.h"
#include "libbdk-arch/bdk-csrs-gserp.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-tsn.h"

/* Indexed by QLM number and lane */
static uint64_t prbs_errors[8][4];

/**
 * Get the SERDES state
 *
 * @param node   Node to query
 * @param qlm    Index into GSER* group
 * @param lane   Lane in GSER*
 *
 * @return State data
 */
bdk_qlm_state_lane_t __bdk_qlm_gserp_get_state(bdk_node_t node, int qlm, int lane)
{
    bdk_qlm_state_lane_t state;
    state.u = BDK_CSR_READ(node, BDK_GSERPX_SCRATCHX(qlm, lane));
    return state;
}

/**
 * For chips that don't use pin strapping, this function programs
 * the QLM to the specified mode
 *
 * @param node     Node to use in a Numa setup
 * @param qlm      QLM to configure
 * @param lane     Lane inside the QLM
 * @param mode     Desired mode
 * @param baud_mhz Desired speed
 * @param flags    Flags to specify mode specific options
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_gserp_set_mode(bdk_node_t node, int qlm, int lane, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    /* All processing is done on lane 0 */
    if (lane > 0)
        return 0;

    bdk_qlm_state_lane_t state = __bdk_qlm_build_state(mode, baud_mhz, flags);

    /* Loop through all lanes */
    BDK_CSR_INIT(gserpx_const, node, BDK_GSERPX_CONST(qlm));
    for (int l = 0; l < gserpx_const.s.nr_lanes; l++)
        BDK_CSR_WRITE(node, BDK_GSERPX_SCRATCHX(qlm, l), state.u);
    return 0;
}

/**
 * Measure the reference clock of a QLM
 *
 * @param qlm    QLM to measure
 *
 * @return Clock rate in Hz
 */
int __bdk_qlm_gserp_measure_refclock(bdk_node_t node, int qlm)
{
    if (bdk_is_platform(BDK_PLATFORM_ASIM) || bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return REF_100MHZ;

    BDK_CSR_INIT(ctr_start, node, BDK_GSERPX_REFCLK_CTR(qlm));
    uint64_t start = bdk_clock_get_count(BDK_CLOCK_TIME);

    /* Wait for a short time to get a number of counts */
    bdk_wait_usec(50000); /* 50ms */

    BDK_CSR_INIT(ctr_stop, node, BDK_GSERPX_REFCLK_CTR(qlm));
    uint64_t stop = bdk_clock_get_count(BDK_CLOCK_TIME);

    /* Calculate the rate */
    uint64_t count = ctr_stop.u - ctr_start.u;
    count *= bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
    count /= stop - start;
    return count;
}

/**
 * Put a QLM into hardware reset
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_gserp_reset(bdk_node_t node, int qlm)
{
    BDK_TRACE(QLM, "%s: Not implemented\n", __FUNCTION__);
    return -1; /* FIXME */
}

/**
 * Enable PRBS on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 * @param prbs   PRBS mode (31, etc)
 * @param dir    Directions to enable. This is so you can enable TX and later
 *               enable RX after TX has run for a time
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_gserp_enable_prbs(bdk_node_t node, int qlm, int prbs, bdk_qlm_direction_t dir)
{
    int pattern = 1;
    switch (prbs)
    {
        case 7:
            pattern = 1;
            break;
        case 9:
            pattern = 2;
            break;
        case 11:
            pattern = 3;
            break;
        case 15:
            pattern = 4;
            break;
        case 23:
            pattern = 5;
            break;
        case 31:
            pattern = 6;
            break;
    }

    BDK_CSR_INIT(gserpx_const, node, BDK_GSERPX_CONST(qlm));
    for (int lane = 0; lane < gserpx_const.s.nr_lanes; lane++)
    {
        if (dir & BDK_QLM_DIRECTION_TX)
        {
            /* No error injection */
            BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_BER_CTRL0(qlm, lane), 0);
            /* Seed PRBS */
            BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_PRBS_CTRL0(qlm, lane), bdk_rng_get_random8());
            BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_PRBS_CTRL1(qlm, lane), bdk_rng_get_random8());
            BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_PRBS_CTRL2(qlm, lane), bdk_rng_get_random8());
            BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_PRBS_CTRL3(qlm, lane), bdk_rng_get_random8());
            /* Start transmit */
            BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_BIST_TX_CTRL(qlm, lane),
                c.s.pattern_sel = pattern;
                c.s.en = 1);
            /* Mux data from BIST generator */
            BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_LANE_TOP_DPL_TXDP_CTRL1(qlm, lane),
                c.s.tx_dmux2_sel = 1);

        }
        if (dir & BDK_QLM_DIRECTION_RX)
        {
            /* Clear error counter */
            BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_BIST_RX_CTRL(qlm, lane),
                c.s.stop_error_count = 1;
                c.s.clear_ber = 1);
            /* Allow re-lock */
            BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_BIST_RX_LOSS_LOCK_CTRL4(qlm, lane),
                c.s.stop_on_loss_lock = 0);
            /* Start receive */
            BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_BIST_RX_CTRL(qlm, lane),
                c.s.stop_error_count = 0;
                c.s.clear_ber = 0;
                c.s.pattern_sel = pattern;
                c.s.en = 1);
            prbs_errors[qlm][lane] = 0;
        }
    }
    return 0;
}

/**
 * Disable PRBS on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_gserp_disable_prbs(bdk_node_t node, int qlm)
{
    BDK_CSR_INIT(gserpx_const, node, BDK_GSERPX_CONST(qlm));
    for (int lane = 0; lane < gserpx_const.s.nr_lanes; lane++)
    {
        /* Stop receive */
        BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_BIST_RX_CTRL(qlm, lane),
            c.s.stop_error_count = 1;
            c.s.clear_ber = 1;
            c.s.en = 0);
        /* Stop transmit */
        BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_LANE_TOP_DPL_TXDP_CTRL1(qlm, lane),
            c.s.tx_dmux2_sel = 0);
        BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_BIST_TX_CTRL(qlm, lane),
            c.s.pattern_sel = 9;
            c.s.en = 0);
        prbs_errors[qlm][lane] = 0;
    }
    return 0;
}

/**
 * Return the number of PRBS errors since PRBS started running
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 * @param clear  Clear counter after return the current value
 *
 * @return Number of errors
 */
uint64_t __bdk_qlm_gserp_get_prbs_errors(bdk_node_t node, int qlm, int lane, int clear)
{
    BDK_CSR_INIT(status, node, BDK_GSERPX_LNX_BIST_RX_STATUS(qlm, lane));
    switch (status.s.state)
    {
        case 3: /* Lock acquired */
            /* Continue below getting counters */
            break;
        case 0: /* Off */
        case 1: /* Searching for pattern */
        case 2: /* Waiting for lock */
        case 4: /* Lock loss */
        default:
            if (clear)
                prbs_errors[qlm][lane] = 0;
            return -1; /* No lock */
    }

    /* Stop the counter so we coherent results */
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_BIST_RX_CTRL(qlm, lane),
        c.s.stop_error_count = 1);

    /* Read the 24 bit counter */
    BDK_CSR_INIT(status0, node, BDK_GSERPX_LNX_BIST_RX_BER_STATUS0(qlm, lane));
    BDK_CSR_INIT(status1, node, BDK_GSERPX_LNX_BIST_RX_BER_STATUS1(qlm, lane));
    BDK_CSR_INIT(status2, node, BDK_GSERPX_LNX_BIST_RX_BER_STATUS2(qlm, lane));

    /* Clear the counter */
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_BIST_RX_CTRL(qlm, lane),
        c.s.clear_ber = 1);
    /* Restart the counter */
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_BIST_RX_CTRL(qlm, lane),
        c.s.stop_error_count = 0;
        c.s.clear_ber = 0);

    /* Add up the errors */
    uint64_t errors = status0.s.bit_error_count_7_0;
    errors += status1.s.bit_error_count_15_8 << 8;
    errors += status2.s.bit_error_count_23_16 << 16;
    errors += prbs_errors[qlm][lane];

    prbs_errors[qlm][lane] = (clear) ? 0 : errors;

    return errors;
}

/**
 * Inject an error into PRBS
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 */
void __bdk_qlm_gserp_inject_prbs_error(bdk_node_t node, int qlm, int lane)
{
    BDK_CSR_DEFINE(ctrl0, BDK_GSERPX_LNX_BIST_TX_BER_CTRL0(0, 0));
    BDK_CSR_DEFINE(ctrl1, BDK_GSERPX_LNX_BIST_TX_BER_CTRL1(0, 0));
    BDK_CSR_DEFINE(ctrl2, BDK_GSERPX_LNX_BIST_TX_BER_CTRL2(0, 0));
    BDK_CSR_DEFINE(ctrl3, BDK_GSERPX_LNX_BIST_TX_BER_CTRL3(0, 0));
    BDK_CSR_DEFINE(ctrl4, BDK_GSERPX_LNX_BIST_TX_BER_CTRL4(0, 0));
    BDK_CSR_DEFINE(ctrl5, BDK_GSERPX_LNX_BIST_TX_BER_CTRL5(0, 0));
    BDK_CSR_DEFINE(ctrl6, BDK_GSERPX_LNX_BIST_TX_BER_CTRL6(0, 0));

    ctrl0.u = 0; /* Control */
    ctrl1.u = 0; /* Timer bits 7:0 */
    ctrl2.u = 0; /* Timer bits 15:8 */
    ctrl3.u = 0; /* Error bits 7:0 */
    ctrl4.u = 0; /* Error bits 15:8 */
    ctrl5.u = 0; /* Error bits 23:16 */
    ctrl6.u = 0; /* Error bits 31:24 */

    /* LSB bit is where we inject the error */
    ctrl3.s.bit_error_field_7_0 = 1;

    /* Inject single error without the timer */
    ctrl0.s.mode = 1;

    /* Write ctrl0 last as it starts injection */
    BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_BER_CTRL6(qlm, lane), ctrl6.u);
    BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_BER_CTRL5(qlm, lane), ctrl5.u);
    BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_BER_CTRL4(qlm, lane), ctrl4.u);
    BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_BER_CTRL3(qlm, lane), ctrl3.u);
    BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_BER_CTRL2(qlm, lane), ctrl2.u);
    BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_BER_CTRL1(qlm, lane), ctrl1.u);
    BDK_CSR_WRITE(node, BDK_GSERPX_LNX_BIST_TX_BER_CTRL0(qlm, lane), ctrl0.u);
}

/**
 * Enable shallow loopback on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 * @param loop   Type of loopback. Not all QLMs support all modes
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_gserp_enable_loop(bdk_node_t node, int qlm, bdk_qlm_loop_t loop)
{
    int near_end_analog = 0;
    int far_end_analog = 0;
    int near_end_digital = 0;

    switch (loop)
    {
        case BDK_QLM_LOOP_DISABLED:  /* No loopback */
            break;
        case BDK_QLM_LOOP_SHALLOW: /* Loop external data RX->TX (Not supported on CN8XXX) */
            far_end_analog = 1;
            break;
        case BDK_QLM_LOOP_NEAR_END: /* Loop internal data TX->RX in analog domain (Not supported on CN8XXX) */
            near_end_analog = 1;
            break;
        case BDK_QLM_LOOP_CORE: /* Loop internal data TX->RX in digital domain */
            near_end_digital = 1;
            break;
    }

    BDK_CSR_INIT(gserpx_const, node, BDK_GSERPX_CONST(qlm));
    for (int lane = 0; lane < gserpx_const.s.nr_lanes; lane++)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_LANE_TOP_AFE_LOOPBACK_CTRL(qlm, lane),
            c.s.loopback_nea_en = near_end_analog;
            c.s.loopback_fea_en = far_end_analog);
        BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_LANE_TOP_DPL_RXDP_CTRL1(qlm, lane),
            c.s.rx_dmux_sel = near_end_digital);
    }
    return 0;
}

/**
 * Configure the TX tuning parameters for a QLM lane
 *
 * @param node      Node to configure
 * @param qlm       QLM to configure
 * @param lane      Lane to configure
 * @param tx_cmain  Transmitter Main (C0) equalizer tap coefficient value.
 *                  Programs the SerDes transmitter Main tap. Valid range is
 *                  0x30 to 0x18.
 * @param tx_cpre   Transmitter Pre (C-1) equalizer tap coefficient value.
 *                  Programs the transmitter Pre tap. Valid range is 0 to 0x10.
 * @param tx_cpost  Transmitter Post (C+1) equalizer tap coefficient value.
 *                  Programs the transmitter Post tap. Valid range is 0 to
 *                  0x10.
 * @param tx_bs     TX bias/swing selection. This setting only takes effect if
 *                  [TX_CSPD] is deasserted; with [TX_CSPD] asserted the
 *                  bias/swing control setting seen in the analog bias generator
 *                  is zero.
 *                  Typical override values would be:
 *                  42 = Nominal 1.0V p-p transmit amplitude.
 *                  52 = Nominal 1.2V p-p transmit amplitude.
 *                  The maximum usable value without transmitted waveform
 *                  distortion depends primarily on voltage, secondarily on
 *                  process corner and temperature, but is at least 52. There is
 *                  no minimum setting based on transmitter distortion, only
 *                  that set by the receiver.
 * @param tx_unused Currently unused
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_gserp_tune_lane_tx(bdk_node_t node, int qlm, int lane, int tx_cmain, int tx_cpre, int tx_cpost, int tx_unused1, int tx_unused2)
{
    BDK_CSR_INIT(ctrl0, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_CTRL0(qlm, lane));
    BDK_CSR_INIT(status0, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_STATUS0(qlm, lane));
    if (ctrl0.s.req || status0.s.ack)
    {
        bdk_error("GSERP%d.%d: TXEQ coefficient request in progress\n", qlm, lane);
        return -1;
    }
    int orig_tx_cmain = -1;
    int orig_tx_cpre = -1;
    int orig_tx_cpost = -1;
    if (__bdk_qlm_gserp_get_tune_lane_tx(node, qlm, lane, &orig_tx_cmain, &orig_tx_cpre, &orig_tx_cpost, &tx_unused1, &tx_unused2))
    {
        bdk_error("GSERP%d.%d: Failed to read previous settings\n", qlm, lane);
        return -1;
    }

    if (tx_cmain == -1)
        tx_cmain = orig_tx_cmain;
    if (tx_cpre == -1)
        tx_cpre = orig_tx_cpre;
    if (tx_cpost == -1)
        tx_cpost = orig_tx_cpost;

    /* Load the new value */
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_CTRL1(qlm, lane),
        c.s.txeq_c1 = tx_cpost);
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_CTRL3(qlm, lane),
        c.s.txeq_cm1 = tx_cpre);
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_CTRL5(qlm, lane),
        c.s.drv_swing = tx_cmain);
    /* Request an update */
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_CTRL0(qlm, lane),
        c.s.req = 1);
    /* Wait for ACK */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_STATUS0(qlm, lane), ack, ==, 1, 10000))
    {
        bdk_error("GSERP%d.%d: TXEQ coefficient request timeout\n", qlm, lane);
        return -1;
    }
    /* Clear update request */
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_CTRL0(qlm, lane),
        c.s.req = 0);

    return 0;
}

/**
 * Get the TX tuning parameters for a QLM lane
 *
 * @param node      Node to configure
 * @param qlm       QLM to configure
 * @param lane      Lane to configure
 * @param tx_cmain  Transmitter Main (C0) equalizer tap coefficient value.
 *                  Programs the SerDes transmitter Main tap. Valid range is
 *                  0x30 to 0x18.
 * @param tx_cpre   Transmitter Pre (C-1) equalizer tap coefficient value.
 *                  Programs the transmitter Pre tap. Valid range is 0 to 0x10.
 * @param tx_cpost  Transmitter Post (C+1) equalizer tap coefficient value.
 *                  Programs the transmitter Post tap. Valid range is 0 to
 *                  0x10.
 * @param tx_bs     TX bias/swing selection. This setting only takes effect if
 *                  [TX_CSPD] is deasserted; with [TX_CSPD] asserted the
 *                  bias/swing control setting seen in the analog bias generator
 *                  is zero.
 *                  Typical override values would be:
 *                  42 = Nominal 1.0V p-p transmit amplitude.
 *                  52 = Nominal 1.2V p-p transmit amplitude.
 *                  The maximum usable value without transmitted waveform
 *                  distortion depends primarily on voltage, secondarily on
 *                  process corner and temperature, but is at least 52. There is
 *                  no minimum setting based on transmitter distortion, only
 *                  that set by the receiver.
 * @param tx_unused Currently unused
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_gserp_get_tune_lane_tx(bdk_node_t node, int qlm, int lane, int *tx_cmain, int *tx_cpre, int *tx_cpost, int *tx_bs, int *tx_unused)
{
    BDK_CSR_INIT(status1, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_STATUS1(qlm, lane));
    BDK_CSR_INIT(status2, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_STATUS2(qlm, lane));
    BDK_CSR_INIT(status3, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_STATUS3(qlm, lane));
    *tx_cmain = status3.s.txeq_c0;
    *tx_cpre = status2.s.txeq_cm1;
    *tx_cpost = status1.s.txeq_c1;
    *tx_bs = -1;
    *tx_unused = -1;
    return 0;
}

/**
 * Display the current settings of a QLM lane
 *
 * @param node     Node the QLM is on
 * @param qlm      QLM to display
 * @param qlm_lane Lane to use
 * @param show_tx  Display TX parameters
 * @param show_rx  Display RX parameters
 */
void __bdk_qlm_gserp_display_settings(bdk_node_t node, int qlm, int qlm_lane, bool show_tx, bool show_rx)
{
    printf("N%d.GSERP%d Lane %d:\n", node, qlm, qlm_lane);
    if (show_tx)
    {
        BDK_CSR_INIT(status1, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_STATUS1(qlm, qlm_lane));
        BDK_CSR_INIT(status2, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_STATUS2(qlm, qlm_lane));
        BDK_CSR_INIT(status3, node, BDK_GSERPX_LNX_DRV_REFCLK_TXEQ_STATUS3(qlm, qlm_lane));
        printf("  Transmitter Status:\n");
        printf("    PRE=%d, MAIN=%d, POST=%d\n", status2.s.txeq_cm1, status3.s.txeq_c0, status1.s.txeq_c1);
    }
    if (show_rx)
    {
        /* Read LEQ */
        int att = -1;
        int apg = -1;
        int lfg = -1;
        int hfg = -1;
        int mbf = -1;
        int mbg = -1;
        switch (qlm_lane)
        {
            case 0:
                att = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_PLE_ATT_O_READ_VAL_2_0(qlm));
                apg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_GN_APG_O_READ_VAL_2_0(qlm));
                lfg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_EQ_LFG_O_READ_VAL_4_0(qlm));
                hfg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_EQ_HFG_O_READ_VAL_4_0(qlm));
                mbf = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_EQ_MBF_O_READ_VAL_3_0(qlm));
                mbg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_EQ_MBG_O_READ_VAL_3_0(qlm));
                break;
            case 1:
                att = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_PLE_ATT_O_READ_VAL_2_0(qlm));
                apg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_GN_APG_O_READ_VAL_2_0(qlm));
                lfg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_EQ_LFG_O_READ_VAL_4_0(qlm));
                hfg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_EQ_HFG_O_READ_VAL_4_0(qlm));
                mbf = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_EQ_MBF_O_READ_VAL_3_0(qlm));
                mbg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_EQ_MBG_O_READ_VAL_3_0(qlm));
                break;
            case 2:
                att = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_PLE_ATT_O_READ_VAL_2_0(qlm));
                apg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_GN_APG_O_READ_VAL_2_0(qlm));
                lfg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_EQ_LFG_O_READ_VAL_4_0(qlm));
                hfg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_EQ_HFG_O_READ_VAL_4_0(qlm));
                mbf = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_EQ_MBF_O_READ_VAL_3_0(qlm));
                mbg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_EQ_MBG_O_READ_VAL_3_0(qlm));
                break;
            case 3:
                att = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_PLE_ATT_O_READ_VAL_2_0(qlm));
                apg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_GN_APG_O_READ_VAL_2_0(qlm));
                lfg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_EQ_LFG_O_READ_VAL_4_0(qlm));
                hfg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_EQ_HFG_O_READ_VAL_4_0(qlm));
                mbf = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_EQ_MBF_O_READ_VAL_3_0(qlm));
                mbg = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_EQ_MBG_O_READ_VAL_3_0(qlm));
                break;
        }
        printf("  Receiver Status:\n");
        printf("    ATT=%d, APG=%d, LFG=%d, HFG=%d, MBF=%d, MBG=%d\n",
            att, apg, lfg, hfg, mbf, mbg);

        /* Read DFE taps */
        bool use_even = 1;
        int tap1_val = -1;
        int tap2_val = -1;
        int tap3_val = -1;
        int tap4_val = -1;
        int tap5_val = -1;
        int tap6_val = -1;
        int tap7_val = -1;
        int tap8_val = -1;
        switch (qlm_lane)
        {
            case 0:
                if (use_even == 1)
                    tap1_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXDFE_EVEN_TAP1_O_READ_VAL_6_0(qlm));
                else
                    tap1_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXDFE_ODD_TAP1_O_READ_VAL_6_0(qlm));
                tap2_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP2_O_READ_VAL_5_0(qlm));
                tap3_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP3_O_READ_VAL_4_0(qlm));
                tap4_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP4_O_READ_VAL_3_0(qlm));
                tap5_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP5_O_READ_VAL_3_0(qlm));
                tap6_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP6_O_READ_VAL_3_0(qlm));
                tap7_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP7_O_READ_VAL_2_0(qlm));
                tap8_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP8_O_READ_VAL_2_0(qlm));
                break;
            case 1:
                if (use_even == 1)
                    tap1_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXDFE_EVEN_TAP1_O_READ_VAL_6_0(qlm));
                else
                    tap1_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXDFE_ODD_TAP1_O_READ_VAL_6_0(qlm));
                tap2_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP2_O_READ_VAL_5_0(qlm));
                tap3_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP3_O_READ_VAL_4_0(qlm));
                tap4_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP4_O_READ_VAL_3_0(qlm));
                tap5_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP5_O_READ_VAL_3_0(qlm));
                tap6_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP6_O_READ_VAL_3_0(qlm));
                tap7_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP7_O_READ_VAL_2_0(qlm));
                tap8_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP8_O_READ_VAL_2_0(qlm));
                break;
            case 2:
                if (use_even == 1)
                    tap1_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXDFE_EVEN_TAP1_O_READ_VAL_6_0(qlm));
                else
                    tap1_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXDFE_ODD_TAP1_O_READ_VAL_6_0(qlm));
                tap2_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP2_O_READ_VAL_5_0(qlm));
                tap3_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP3_O_READ_VAL_4_0(qlm));
                tap4_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP4_O_READ_VAL_3_0(qlm));
                tap5_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP5_O_READ_VAL_3_0(qlm));
                tap6_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP6_O_READ_VAL_3_0(qlm));
                tap7_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP7_O_READ_VAL_2_0(qlm));
                tap8_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP8_O_READ_VAL_2_0(qlm));
                break;
            case 3:
                if (use_even == 1)
                    tap1_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXDFE_EVEN_TAP1_O_READ_VAL_6_0(qlm));
                else
                    tap1_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXDFE_ODD_TAP1_O_READ_VAL_6_0(qlm));
                tap2_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP2_O_READ_VAL_5_0(qlm));
                tap3_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP3_O_READ_VAL_4_0(qlm));
                tap4_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP4_O_READ_VAL_3_0(qlm));
                tap5_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP5_O_READ_VAL_3_0(qlm));
                tap6_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP6_O_READ_VAL_3_0(qlm));
                tap7_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP7_O_READ_VAL_2_0(qlm));
                tap8_val = BDK_CSR_READ(node, BDK_GSERPX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP8_O_READ_VAL_2_0(qlm));
                break;
        }
        printf("    TAP1=%d, TAP2=%d, TAP3=%d, TAP4=%d, TAP5=%d, TAP6=%d, TAP7=%d, TAP8=%d\n",
            tap1_val, tap2_val, tap3_val, tap4_val, tap5_val, tap6_val, tap7_val, tap8_val);
    }
}

/**
 * Issue a mailbox command to the serdes firmware
 *
 * @param node   Node to access
 * @param qlm    QLM to access
 * @param cmd    Command to issue
 * @param args   Arguments to command. LSB = arg0, MSB = arg7
 *
 * @return Command status, or -1 on failure
 */
static int mailbox_command(bdk_node_t node, int qlm, uint8_t cmd, uint64_t args)
{
    BDK_CSR_INIT(flag, node, BDK_GSERPX_PHY0_MB_CMD_FLAG(qlm));
    if (flag.s.cmd_flag)
    {
        bdk_error("GSERP%d: Mailbox already has a command\n", qlm);
        return -1;
    }

    BDK_CSR_INIT(rsp_flag, node, BDK_GSERPX_PHY0_MB_RSP_FLAG(qlm));
    if (rsp_flag.s.rsp_flag)
    {
        bdk_error("GSERP%d: Mailbox already has a response\n", qlm);
        return -1;
    }

    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_CMD_DATA0(qlm), bdk_extract(args, 0, 8));
    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_CMD_DATA1(qlm), bdk_extract(args, 8, 8));
    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_CMD_DATA2(qlm), bdk_extract(args, 16, 8));
    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_CMD_DATA3(qlm), bdk_extract(args, 24, 8));
    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_CMD_DATA4(qlm), bdk_extract(args, 32, 8));
    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_CMD_DATA5(qlm), bdk_extract(args, 40, 8));
    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_CMD_DATA6(qlm), bdk_extract(args, 48, 8));
    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_CMD_DATA7(qlm), bdk_extract(args, 56, 8));
    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_CMD(qlm), cmd);

    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERPX_PHY0_MB_CMD_FLAG(qlm), cmd_flag, ==, 0, 10000))
    {
        bdk_error("GSERP%d: Mailbox stuck on command\n", qlm);
        return -1;
    }
    return 0;
}

/**
 * Read a mailbox response from the serdes firmware
 *
 * @param node   Node to access
 * @param qlm    QLM to access
 * @param arg0   First 8 arguments of the response. LSB = data0, MSB = data7
 * @param arg1   Second 8 arguments of the response. LSB = data8, MSB = data15
 *
 * @return Response status, or -1 on failure
 */
static int mailbox_response(bdk_node_t node, int qlm, uint64_t *arg0, uint64_t *arg1)
{
    /* Wait for a response */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERPX_PHY0_MB_RSP_FLAG(qlm), rsp_flag, ==, 1, 10000))
    {
        bdk_error("GSERP%d: Mailbox has no response\n", qlm);
        return -1;
    }

    /* Read the response */
    BDK_CSR_INIT(rsp, node, BDK_GSERPX_PHY0_MB_RSP(qlm));
    BDK_CSR_INIT(data0, node, BDK_GSERPX_PHY0_MB_RSP_DATA0(qlm));
    BDK_CSR_INIT(data1, node, BDK_GSERPX_PHY0_MB_RSP_DATA1(qlm));
    BDK_CSR_INIT(data2, node, BDK_GSERPX_PHY0_MB_RSP_DATA2(qlm));
    BDK_CSR_INIT(data3, node, BDK_GSERPX_PHY0_MB_RSP_DATA3(qlm));
    BDK_CSR_INIT(data4, node, BDK_GSERPX_PHY0_MB_RSP_DATA4(qlm));
    BDK_CSR_INIT(data5, node, BDK_GSERPX_PHY0_MB_RSP_DATA5(qlm));
    BDK_CSR_INIT(data6, node, BDK_GSERPX_PHY0_MB_RSP_DATA6(qlm));
    BDK_CSR_INIT(data7, node, BDK_GSERPX_PHY0_MB_RSP_DATA7(qlm));
    BDK_CSR_INIT(data8, node, BDK_GSERPX_PHY0_MB_RSP_DATA8(qlm));
    BDK_CSR_INIT(data9, node, BDK_GSERPX_PHY0_MB_RSP_DATA9(qlm));
    BDK_CSR_INIT(data10, node, BDK_GSERPX_PHY0_MB_RSP_DATA10(qlm));
    BDK_CSR_INIT(data11, node, BDK_GSERPX_PHY0_MB_RSP_DATA11(qlm));
    BDK_CSR_INIT(data12, node, BDK_GSERPX_PHY0_MB_RSP_DATA12(qlm));
    BDK_CSR_INIT(data13, node, BDK_GSERPX_PHY0_MB_RSP_DATA13(qlm));
    BDK_CSR_INIT(data14, node, BDK_GSERPX_PHY0_MB_RSP_DATA14(qlm));
    BDK_CSR_INIT(data15, node, BDK_GSERPX_PHY0_MB_RSP_DATA15(qlm));

    /* Tell firmware we read the response */
    BDK_CSR_WRITE(node, BDK_GSERPX_PHY0_MB_RSP_FLAG(qlm), 1);

    /* Package and return the response */
    *arg0 = (uint64_t)data0.s.rsp_data0;
    *arg0 |= (uint64_t)data1.s.rsp_data1 << 8;
    *arg0 |= (uint64_t)data2.s.rsp_data2 << 16;
    *arg0 |= (uint64_t)data3.s.rsp_data3 << 24;
    *arg0 |= (uint64_t)data4.s.rsp_data4 << 32;
    *arg0 |= (uint64_t)data5.s.rsp_data5 << 40;
    *arg0 |= (uint64_t)data6.s.rsp_data6 << 48;
    *arg0 |= (uint64_t)data7.s.rsp_data7 << 56;
    *arg1 = (uint64_t)data8.s.rsp_data8;
    *arg1 |= (uint64_t)data9.s.rsp_data9 << 8;
    *arg1 |= (uint64_t)data10.s.rsp_data10 << 16;
    *arg1 |= (uint64_t)data11.s.rsp_data11 << 24;
    *arg1 |= (uint64_t)data12.s.rsp_data12 << 32;
    *arg1 |= (uint64_t)data13.s.rsp_data13 << 40;
    *arg1 |= (uint64_t)data14.s.rsp_data14 << 48;
    *arg1 |= (uint64_t)data15.s.rsp_data15 << 56;
    return rsp.s.rsp;
}

/**
 * Perform RX equalization on a QLM
 *
 * @param node     Node the QLM is on
 * @param qlm      QLM to perform RX equalization on
 * @param qlm_lane Lane to use, or -1 for all lanes
 *
 * @return Zero on success, negative if any lane failed RX equalization
 */
int __bdk_qlm__gserp_rx_equalization(bdk_node_t node, int qlm, int qlm_lane)
{
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return 0;

    int result = 0;
    BDK_CSR_INIT(gserpx_const, node, BDK_GSERPX_CONST(qlm));
    for (int lane = 0; lane < gserpx_const.s.nr_lanes; lane++)
    {
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;

        BDK_TRACE(QLM, "N%d.GSERP%d.%d: Lane TXDP Clock Phase Calibration starting\n", node, qlm, lane);
        if (mailbox_command(node, qlm, 0x81, qlm_lane))
        {
            bdk_error("N%d.GSERP%d.%d: Lane TXDP Clock Phase Calibration failed to issue\n", node, qlm, lane);
            result = -1;
            continue;
        }
        uint64_t arg0 = 0;
        uint64_t arg1 = 0;
        int status = mailbox_response(node, qlm, &arg0, &arg1);
        switch (status)
        {
            case 0x00: /* Calibration OK */
                BDK_TRACE(QLM, "N%d.GSERP%d.%d: Lane TXDP Clock Phase Calibration: %lu\n", node, qlm, lane, arg0 & 0xff);
                break;
            case 0x01: /* Calibration Railed Low */
                bdk_error("N%d.GSERP%d.%d: Lane TXDP Clock Phase Calibration Railed Low\n", node, qlm, lane);
                result = -1;
                break;
            case 0x02: /* Calibration Railed High */
                bdk_error("N%d.GSERP%d.%d: Lane TXDP Clock Phase Calibration Railed High\n", node, qlm, lane);
                result = -1;
                break;
            default:
                bdk_error("N%d.GSERP%d.%d: Lane TXDP Clock Phase Calibration illegal response %d\n", node, qlm, lane, status);
                result = -1;
                break;
        }
    }
    return result;
}

/**
 * Capture an eye diagram for the given QLM lane. The output data is written
 * to "eye".
 *
 * @param node      Node to use in numa setup
 * @param qlm       QLM to use
 * @param qlm_lane  Which lane
 * @param show_data Set to non-zero to have the eye capture dump the raw eye data as
 *                  it is captured
 * @param eye       Output eye data
 *
 * @return Zero on success, negative on failure
 */
int __bdk_qlm_gserp_eye_capture(bdk_node_t node, int qlm, int lane, int show_data, bdk_qlm_eye_t *eye_data)
{
    int x_min = 0;
    int x_max = 127;
    int x_step = 1;
    int y_min = -255;
    int y_max = 255;
    int y_step = 8;
    int ber = 16; /* Base 2, not base 10. Must be 8, 16, or 32 */
    uint64_t resp0;
    uint64_t resp1;

    eye_data->width = 0;
    eye_data->height = 0;

    int y_points = (y_max - y_min + 1) / y_step;
    int x_points = (x_max - x_min + 1) / x_step;
    if (y_points > 64) /* Limit from static struct */
    {
        bdk_error("GSERP%d: Eye too high\n", qlm);
        return -1;
    }
    if (x_points > 128) /* Limit from static struct */
    {
        bdk_error("GSERP%d: Eye too high\n", qlm);
        return -1;
    }

    if (show_data)
    {
        printf("# Extensive 1D Rx Eye on GSERP%d Lane %d\n", qlm, lane);
        printf("# Cycle Bits: %lu\n", 1ul << ber);
        printf("# Start Time Offset: %d; End Time Offset: %d; Time Step: %d\n", x_min, x_max, x_step);
        printf("# Start Voltage Offset: %d; End Voltage Offset: %d; Voltage Step: %d\n", y_min, y_max, y_step);
        printf("%5s %5s %s\n", "V", "T", "Errors");
    }
    else
        printf("Capturing eye...\n");

    uint64_t cmd_arg = (uint64_t)lane; /* data 0 */
    cmd_arg |= (uint64_t)x_min << 8; /* data 1 */
    cmd_arg |= (uint64_t)x_max << 16; /* data 2 */
    cmd_arg |= (uint64_t)x_step << 24; /* data 3 */
    cmd_arg |= (uint64_t)-y_min << 32; /* data 4 */
    cmd_arg |= (uint64_t)y_max << 40; /* data 5 */
    int signs = ((y_min < 0) ? 1 : 0) | ((y_max < 0) ? 2 : 0);
    cmd_arg |= (uint64_t)signs << 48; /* data 6 */
    cmd_arg |= (uint64_t)y_step << 56; /* data 7 */

    if (mailbox_command(node, qlm, 0x83, cmd_arg) != 0)
        return -1;
    if (mailbox_response(node, qlm, &resp0, &resp1) != 0)
    {
        bdk_error("GSERP%d: Eye setup 1 failed\n", qlm);
        return -1;
    }

    cmd_arg = lane; /* data 0 */
    uint64_t ber_limit = bdk_build_mask(ber);
    cmd_arg |= bdk_extract(ber_limit, 32, 8) << 8; /* data 1 */
    cmd_arg |= bdk_extract(ber_limit, 24, 8) << 16; /* data 2 */
    cmd_arg |= bdk_extract(ber_limit, 16, 8) << 24; /* data 3 */
    cmd_arg |= bdk_extract(ber_limit, 8, 8) << 32; /* data 4 */
    cmd_arg |= bdk_extract(ber_limit, 0, 8) << 40; /* data 5 */

    if (mailbox_command(node, qlm, 0x84, cmd_arg))
        return -1;
    if (mailbox_response(node, qlm, &resp0, &resp1) != 0)
    {
        bdk_error("GSERP%d: Eye setup 2 failed\n", qlm);
        return -1;
    }

    cmd_arg = lane; /* data 0 */
    cmd_arg = 0 << 16; /* data 2, sweep mode */

    if (mailbox_command(node, qlm, 0x82, cmd_arg))
        return -1;

    int x = 0;
    int y = 0;
    int rsp = 0;
    while (rsp != 1)
    {
        /* read 128 bits of response */
        rsp = mailbox_response(node, qlm, &resp0, &resp1);
        /* 0 = more data, 1 = done, others are errors */
        if ((rsp != 0) || (rsp != 1))
        {
            bdk_error("GSERP%d: Eye failed (%d)\n", qlm, rsp);
            return -1;
        }
        /* Make a 128 bit number from response for easy processing */
        __uint128_t r = resp0;
        r |= (__uint128_t)resp1 << 64;
        /* Loop through all response bits. This assumes 128 divides evenly by BER */
        for (int bits = 0; bits < 128; bits += ber)
        {
            /* Extract this sample. It is encoded BE */
            uint64_t sample = r & bdk_build_mask(ber);
            /* Move to the next BER bits */
            r >>= ber;
            /* Convert and store the sample */
            sample = bdk_be16_to_cpu(sample);
            eye_data->data[y][x] = sample;
            if (show_data)
                printf("%5d %5d %lu\n", y * y_step + y_min, x * x_step + x_min, sample);
            /* Move to next */
            y++;
            if (y >= y_points)
            {
                y = 0;
                x++;
                if (x >= x_points)
                {
                    if (rsp != 1)
                    {
                        bdk_error("GSERP%d: Too many response\n", qlm);
                        return -1;
                    }
                    break; /* Bit loop */
                }
            }
        }
    }
    eye_data->width = x_points;
    eye_data->height = y_points;
    return 0;
}

/**
 * Initialize the QLM layer
 */
void __bdk_qlm_gserp_init(bdk_node_t node)
{
    const char *firmware_file = NULL;
    int broadcast = -1;

    /* Figure out which firmware file to use and the broadcast index */
    if (bdk_is_model(OCTEONTX_CN96XX))
    {
        firmware_file = "/fatfs/serdes/gserp-cn96xx.frm.lzma";
        broadcast = 5;
    }
    else if (bdk_is_model(OCTEONTX_CN98XX))
    {
        firmware_file = "/fatfs/serdes/gserp-cn98xx.frm.lzma";
        broadcast = 9;
    }
    else if (bdk_is_model(OCTEONTX_LOKI))
    {
        firmware_file = "/fatfs/serdes/gserp-loki.frm.lzma";
        broadcast = 1;
    }
    else
    {
        bdk_error("GSERP: Unrecognized chip\n");
        return;
    }

    BDK_CSR_INIT(gserpx_init_ctl, node, BDK_GSERPX_INIT_CTL(broadcast));
    if (!gserpx_init_ctl.s.cpu_reset)
    {
        BDK_TRACE(QLM, "GSERP: Firmware already loaded\n");
        return;
    }

    /* Open the firmware file */
    BDK_TRACE(QLM, "GSERP: Loading firmware %s\n", firmware_file);
    uint64_t filesize = 0;
    uint64_t *firmware = bdk_signed_load(firmware_file, 0,BDK_SIGNED_IMAGE, BDK_SIGNED_FLAG_NOT_ENCRYPTED, &filesize);
    if (!firmware)
    {
        bdk_error("GSERP: Failed to load firmware %s\n", firmware_file);
        return;
    }

    /* 1) GSERP will exit cold reset with GSERP()_INIT_CTL fields set as
       follows:
        [SPLIT_FW_RDY] = 0
        [APB_RESET] = 1 (APB bus for this GSERP instance is in reset)
        [CPU_RESET] = 1 (CPU for this GSERP instance is in reset)
        [POR_RESET] = 1 (GSERP(1) value controls gserp_16lane PCS POR and all
            PMA POR inputs, GSERP(4) controls gserp_4lane) */

    /* 2) Initialize the temperature sensor nearest GSERP
        TSN(0)_TS_TEMP_NOFF_MC[MC] = 'd3000
        TSN(0)_TS_TEMP_NOFF_MC[NOFF] = 'd1064
        TSN(0)_FUSE_BYPASS[TS_FUSE_BYPASS] = 1 */
    int sensor = 0; // FIXME: for t93, what about other chips?
    BDK_CSR_MODIFY(c, node, BDK_TSNX_TS_TEMP_NOFF_MC(sensor),
        c.s.mc = 3000;
        c.s.noff = 1064);
    BDK_CSR_MODIFY(c, node, BDK_TSNX_FUSE_BYPASS(sensor),
        c.s.ts_fuse_bypass = 1);

    /* 3) Using SCP script (for EP) or BDK (for RC), load first 48KB of firmware
        from SPI ROM into all GSERP instances using 64B broadcast writes. */
    /* Load the firmware. We load all the firwmare here, not just the first 48KB */
    for (int index = 0; index < (int)filesize / 8; index++)
        BDK_CSR_WRITE(node, BDK_GSERPX_PMEMX(broadcast, index), firmware[index]);
    free(firmware);
    BDK_TRACE(QLM, "GSERP: Loading firmware of %lu bytes\n", filesize);

    /* 4) Configure GSERP(1)_FURCATION_MODE and GSERP(4)_FURCATION_MODE
        (do not use broadcast writes for this). */
    if (bdk_is_model(OCTEONTX_CN96XX))
    {
        bdk_qlm_modes_t qlm0_mode = bdk_qlm_get_mode(node, 0, 0);
        bdk_qlm_modes_t qlm1_mode = bdk_qlm_get_mode(node, 1, 0);
        bdk_qlm_modes_t qlm2_mode = bdk_qlm_get_mode(node, 2, 0);
        bool qlm0_is_pcie8 = (qlm0_mode == BDK_QLM_MODE_PCIE_X8);
        bool qlm0_is_pcie16 = (qlm0_mode == BDK_QLM_MODE_PCIE_X16);
        bool qlm1_is_pcie4 = (qlm1_mode == BDK_QLM_MODE_PCIE_X4);
        bool qlm2_is_pcie8 = (qlm2_mode == BDK_QLM_MODE_PCIE_X8);
        int mode;
        if (qlm0_is_pcie8)
            mode = qlm2_is_pcie8 ? 1 : 2;
        else if (qlm0_is_pcie16)
            mode = 0;
        else
            mode = qlm2_is_pcie8 ? 3 : 4;
        for (int i = 0; i < broadcast; i++)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERPX_FURCATION_MODE(i),
                c.s.mux_cfg1 = qlm2_is_pcie8 ? 0 : 1;
                c.s.mux_cfg0 = qlm1_is_pcie4 ? 1 : 0;
                c.s.mode = mode);
        }
    }
    else if (bdk_is_model(OCTEONTX_LOKI))
    {
        for (int i = 0; i < broadcast; i++)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERPX_FURCATION_MODE(i),
                c.s.mux_cfg1 = 0;
                c.s.mux_cfg0 = 0;
                c.s.mode = 0);
        }
    }
    else if (bdk_is_model(OCTEONTX_CN98XX))
    {
        bdk_qlm_modes_t qlm0_mode = bdk_qlm_get_mode(node, 0, 0);
        bdk_qlm_modes_t qlm1_mode = bdk_qlm_get_mode(node, 1, 0);
        bdk_qlm_modes_t qlm2_mode = bdk_qlm_get_mode(node, 2, 0);
        bdk_qlm_modes_t qlm4_mode = bdk_qlm_get_mode(node, 4, 0);
        bdk_qlm_modes_t qlm5_mode = bdk_qlm_get_mode(node, 1, 0);
        bdk_qlm_modes_t qlm6_mode = bdk_qlm_get_mode(node, 6, 0);
        bool qlm0_is_pcie8 = (qlm0_mode == BDK_QLM_MODE_PCIE_X8);
        bool qlm0_is_pcie16 = (qlm0_mode == BDK_QLM_MODE_PCIE_X16);
        bool qlm1_is_pcie4 = (qlm1_mode == BDK_QLM_MODE_PCIE_X4);
        bool qlm2_is_pcie8 = (qlm2_mode == BDK_QLM_MODE_PCIE_X8);
        bool qlm4_is_pcie8 = (qlm4_mode == BDK_QLM_MODE_PCIE_X8);
        bool qlm4_is_pcie16 = (qlm4_mode == BDK_QLM_MODE_PCIE_X16);
        bool qlm5_is_pcie4 = (qlm5_mode == BDK_QLM_MODE_PCIE_X4);
        bool qlm6_is_pcie8 = (qlm6_mode == BDK_QLM_MODE_PCIE_X8);
        int mode;
        if (qlm0_is_pcie8)
            mode = qlm2_is_pcie8 ? 1 : 2;
        else if (qlm0_is_pcie16)
            mode = 0;
        else
            mode = qlm2_is_pcie8 ? 3 : 4;
        for (int i = 0; i < 4; i++)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERPX_FURCATION_MODE(i),
                c.s.mux_cfg1 = qlm2_is_pcie8 ? 0 : 1;
                c.s.mux_cfg0 = qlm1_is_pcie4 ? 1 : 0;
                c.s.mode = mode);
        }
        if (qlm4_is_pcie8)
            mode = qlm6_is_pcie8 ? 1 : 2;
        else if (qlm4_is_pcie16)
            mode = 0;
        else
            mode = qlm6_is_pcie8 ? 3 : 4;
        for (int i = 4; i < 8; i++)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERPX_FURCATION_MODE(i),
                c.s.mux_cfg1 = qlm6_is_pcie8 ? 0 : 1;
                c.s.mux_cfg0 = qlm5_is_pcie4 ? 1 : 0;
                c.s.mode = mode);
        }
    }
    else
    {
        bdk_error("GSERP: Unrecognized chip (GSERPX_FURCATION_MODE)\n");
        return;
    }
    /* 5) Write GSERP(*)_INIT_CTL
        [POR_RESET] = 0
        [APB_RESET] = 0
        [CPU_RESET] = 1 (keep CPU in reset)
        [SPLIT_FW_RDY] = 0 */
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_INIT_CTL(broadcast),
        c.s.por_reset = 0;
        c.s.apb_reset = 0;
        c.s.cpu_reset = 1;
        c.s.split_fw_rdy = 0);
    /* 6) It takes about 3 ms before the temperature is valid. Read temperature
       sensor and update PHY temperature registers. Do not use broadcast feature
       for this.
            1) For SCP, use romscript command SCR_WRITE_TEMP_S to do the
                appropriate conversion. Otherwise it is necessary to convert
                the 12-bit temperature sensor format to an 8-bit format for
                GSERP.
            2) To enable firmware based extension of temperature range, set
                the feature register bit GSERP(0..4)_CM0_CMU_FEATURE_PLL_CAL_EN_CFG1[VCO_DOSC_TEMP_SKEW].
            3) Write GSERP(0..4)_PHY0_TOP_DOSC_TEMP_DURING_CAL[TEMP_VALUE] */
    // FIXME
    //BDK_CSR_MODIFY(c, node, BDK_GSERPX_CM0_CMU_FEATURE_PLL_CAL_EN_CFG1(gserp),
    //    c.s.vco_dosc_temp_skew = 1);
    //BDK_CSR_MODIFY(c, node, BDK_GSERPX_PHY0_TOP_DOSC_TEMP_DURING_CAL(gserp),
    //    c.s.temp_value = 1);
    /* 7) Write GSERP(*)_INIT_CTL[CPU_RESET] = 0 */
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_INIT_CTL(broadcast),
        c.s.cpu_reset = 0);
    /* 8) Using SCP script (for EP) or BDK (for RC), load second 48KB of
       firmware from SPI ROM into all GSERP instances using 64B broadcast
       writes. */
    /* Already done earlier */
    /* 9) Write GSERP(*)_INIT_CTL[SPLIT_FW_RDY] = 1 */
    BDK_CSR_MODIFY(c, node, BDK_GSERPX_INIT_CTL(broadcast),
        c.s.split_fw_rdy = 1);

    /* PEM setup is done later */
}

/**
 * Setup the PEM to either driver or receive reset from PRST based on RC or EP
 *
 * @param node   Node to use in a Numa setup
 * @param pem    Which PEM to setuo
 * @param is_endpoint
 *               Non zero if PEM is a EP
 */
void __bdk_qlm_setup_pem_reset_gserp(bdk_node_t node, int pem, int is_endpoint)
{
    /* Make sure is_endpoint is either 0 or 1 */
    is_endpoint = (is_endpoint != 0);
    BDK_CSR_MODIFY(c, node, BDK_PEMX_S_RST_CTL(pem),
        c.s.reset_type = 0; /* Chip reset */
        c.s.rst_pfflr = !is_endpoint; /* FLR resets */
        c.s.rst_lnkdwn = is_endpoint; /* Link down automatically assert soft reset for EP */
        c.s.prst_lnkdwn = 0; /* PEM reset on link */
        c.s.rst_perst = 0; /* Link down doesn't automatically assert PERST */
        c.s.en_perst_drv = !is_endpoint; /* PERST is output for RC, input for EP */
        c.s.en_perst_rcv = is_endpoint); /* Only read PERST in EP mode */

    if (is_endpoint)
    {
        /* If we're configuring an endpoint manually the PEM will not
           be turned on by default by the hardware. Turn it on now */
        BDK_CSR_INIT(pemx_on, node, BDK_PEMX_ON(pem));
        if (!pemx_on.s.pemon)
        {
            BDK_CSR_MODIFY(c, node, BDK_PEMX_ON(pem),
                c.s.pemon = 1);
        }
    }
}

