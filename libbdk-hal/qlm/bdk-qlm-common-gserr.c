/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "bdk-qlm-common.h"
#include "bdk-qlm-common-gserr.h"
#include "libbdk-arch/bdk-csrs-gserr.h"

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
bdk_qlm_state_lane_t __bdk_qlm_gserr_get_state(bdk_node_t node, int qlm, int lane)
{
    bdk_qlm_state_lane_t state = {.u = BDK_CSR_READ(node, BDK_GSERRX_SCRATCHX(qlm, lane))};
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
int __bdk_qlm_gserr_set_mode(bdk_node_t node, int qlm, int lane, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    bdk_qlm_state_lane_t state = __bdk_qlm_build_state(mode, baud_mhz, flags);
    BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(qlm));

    int start_lane = (lane == -1) ? 0 : lane;
    int end_lane = (lane == -1) ? gserrx_const.s.nr_lanes - 1 : lane;

    /* Loop through all lanes */
    for (int l = start_lane; l <= end_lane; l++)
        BDK_CSR_WRITE(node, BDK_GSERRX_SCRATCHX(qlm, l), state.u);
    return 0;
}

/**
 * Measure the reference clock of a QLM
 *
 * @param qlm    QLM to measure
 *
 * @return Clock rate in Hz
 */
int __bdk_qlm_gserr_measure_refclock(bdk_node_t node, int qlm)
{
    if (bdk_is_platform(BDK_PLATFORM_ASIM) || bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return REF_156MHZ;

    BDK_CSR_INIT(ctr_start, node, BDK_GSERRX_REFCLK_CTR(qlm));
    uint64_t start = bdk_clock_get_count(BDK_CLOCK_TIME);

    /* Wait for a short time to get a number of counts */
    bdk_wait_usec(50000); /* 50ms */

    BDK_CSR_INIT(ctr_stop, node, BDK_GSERRX_REFCLK_CTR(qlm));
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
int __bdk_qlm_gserr_reset(bdk_node_t node, int qlm)
{
    BDK_CSR_INIT(gsercx_const, node, BDK_GSERRX_CONST(qlm));
    for (int lane = 0; lane < gsercx_const.s.nr_lanes; lane++)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERRX_LANEX_CONTROL_BCFG(qlm, lane),
            c.s.ln_rst = 1);
    }
    bdk_wait_usec(1000); /* Stay in reset of 1ms */
    for (int lane = 0; lane < gsercx_const.s.nr_lanes; lane++)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERRX_LANEX_CONTROL_BCFG(qlm, lane),
            c.s.ln_rst = 0);
    }
    return 0;
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
int __bdk_qlm_gserr_enable_prbs(bdk_node_t node, int qlm, int prbs, bdk_qlm_direction_t dir)
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

    BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(qlm));
    for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
    {
        if (dir & BDK_QLM_DIRECTION_TX)
        {
            /* No error injection */
            BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_BER_CTRL0(qlm, lane), 0);
            /* Seed PRBS */
            BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_PRBS_CTRL0(qlm, lane), bdk_rng_get_random8());
            BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_PRBS_CTRL1(qlm, lane), bdk_rng_get_random8());
            BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_PRBS_CTRL2(qlm, lane), bdk_rng_get_random8());
            BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_PRBS_CTRL3(qlm, lane), bdk_rng_get_random8());
            /* Start transmit */
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_BIST_TX_CTRL(qlm, lane),
                c.s.pattern_sel = pattern;
                c.s.en = 1);
            /* Mux data from BIST generator */
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_TOP_DPL_TXDP_CTRL1(qlm, lane),
                c.s.tx_dmux2_sel = 1);

        }
        if (dir & BDK_QLM_DIRECTION_RX)
        {
            /* Clear error counter */
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_BIST_RX_CTRL(qlm, lane),
                c.s.stop_error_count = 1;
                c.s.clear_ber = 1);
            /* Allow re-lock */
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_BIST_RX_LOSS_LOCK_CTRL4(qlm, lane),
                c.s.stop_on_loss_lock = 0);
            /* Start receive */
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_BIST_RX_CTRL(qlm, lane),
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
int __bdk_qlm_gserr_disable_prbs(bdk_node_t node, int qlm)
{
    BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(qlm));
    for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
    {
        /* Stop receive */
        BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_BIST_RX_CTRL(qlm, lane),
            c.s.stop_error_count = 1;
            c.s.clear_ber = 1;
            c.s.en = 0);
        /* Stop transmit */
        BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_TOP_DPL_TXDP_CTRL1(qlm, lane),
            c.s.tx_dmux2_sel = 0);
        BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_BIST_TX_CTRL(qlm, lane),
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
uint64_t __bdk_qlm_gserr_get_prbs_errors(bdk_node_t node, int qlm, int lane, int clear)
{
    BDK_CSR_INIT(status, node, BDK_GSERRX_LNX_BIST_RX_STATUS(qlm, lane));
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
    BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_BIST_RX_CTRL(qlm, lane),
        c.s.stop_error_count = 1);

    /* Read the 24 bit counter */
    BDK_CSR_INIT(status0, node, BDK_GSERRX_LNX_BIST_RX_BER_STATUS0(qlm, lane));
    BDK_CSR_INIT(status1, node, BDK_GSERRX_LNX_BIST_RX_BER_STATUS1(qlm, lane));
    BDK_CSR_INIT(status2, node, BDK_GSERRX_LNX_BIST_RX_BER_STATUS2(qlm, lane));

    /* Clear the counter */
    BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_BIST_RX_CTRL(qlm, lane),
        c.s.clear_ber = 1);
    /* Restart the counter */
    BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_BIST_RX_CTRL(qlm, lane),
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
void __bdk_qlm_gserr_inject_prbs_error(bdk_node_t node, int qlm, int lane)
{
    BDK_CSR_DEFINE(ctrl0, BDK_GSERRX_LNX_BIST_TX_BER_CTRL0(0, 0));
    BDK_CSR_DEFINE(ctrl1, BDK_GSERRX_LNX_BIST_TX_BER_CTRL1(0, 0));
    BDK_CSR_DEFINE(ctrl2, BDK_GSERRX_LNX_BIST_TX_BER_CTRL2(0, 0));
    BDK_CSR_DEFINE(ctrl3, BDK_GSERRX_LNX_BIST_TX_BER_CTRL3(0, 0));
    BDK_CSR_DEFINE(ctrl4, BDK_GSERRX_LNX_BIST_TX_BER_CTRL4(0, 0));
    BDK_CSR_DEFINE(ctrl5, BDK_GSERRX_LNX_BIST_TX_BER_CTRL5(0, 0));
    BDK_CSR_DEFINE(ctrl6, BDK_GSERRX_LNX_BIST_TX_BER_CTRL6(0, 0));

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
    BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_BER_CTRL6(qlm, lane), ctrl6.u);
    BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_BER_CTRL5(qlm, lane), ctrl5.u);
    BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_BER_CTRL4(qlm, lane), ctrl4.u);
    BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_BER_CTRL3(qlm, lane), ctrl3.u);
    BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_BER_CTRL2(qlm, lane), ctrl2.u);
    BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_BER_CTRL1(qlm, lane), ctrl1.u);
    BDK_CSR_WRITE(node, BDK_GSERRX_LNX_BIST_TX_BER_CTRL0(qlm, lane), ctrl0.u);
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
int __bdk_qlm_gserr_enable_loop(bdk_node_t node, int qlm, bdk_qlm_loop_t loop)
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

    BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(qlm));
    for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_TOP_AFE_LOOPBACK_CTRL(qlm, lane),
            c.s.loopback_nea_en = near_end_analog;
            c.s.loopback_fea_en = far_end_analog);
        BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_TOP_DPL_RXDP_CTRL1(qlm, lane),
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
int __bdk_qlm_gserr_tune_lane_tx(bdk_node_t node, int qlm, int lane, int tx_cmain, int tx_cpre, int tx_cpost, int tx_unused1, int tx_unused2)
{
    BDK_CSR_INIT(ctrl0, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_CTRL0(qlm, lane));
    BDK_CSR_INIT(status0, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_STATUS0(qlm, lane));
    if (ctrl0.s.req || status0.s.ack)
    {
        bdk_error("GSERR%d.%d: TXEQ coefficient request in progress\n", qlm, lane);
        return -1;
    }
    int orig_tx_cmain = -1;
    int orig_tx_cpre = -1;
    int orig_tx_cpost = -1;
    if (__bdk_qlm_gserr_get_tune_lane_tx(node, qlm, lane, &orig_tx_cmain, &orig_tx_cpre, &orig_tx_cpost, &tx_unused1, &tx_unused2))
    {
        bdk_error("GSERR%d.%d: Failed to read previous settings\n", qlm, lane);
        return -1;
    }

    if (tx_cmain == -1)
        tx_cmain = orig_tx_cmain;
    if (tx_cpre == -1)
        tx_cpre = orig_tx_cpre;
    if (tx_cpost == -1)
        tx_cpost = orig_tx_cpost;

    /* Load the new value */
    BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_CTRL1(qlm, lane),
        c.s.txeq_c1 = tx_cpost);
    BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_CTRL3(qlm, lane),
        c.s.txeq_cm1 = tx_cpre);
    BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_CTRL5(qlm, lane),
        c.s.drv_swing = tx_cmain);
    /* Request an update */
    BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_CTRL0(qlm, lane),
        c.s.req = 1);
    /* Wait for ACK */
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_STATUS0(qlm, lane), ack, ==, 1, 10000))
    {
        bdk_error("GSERR%d.%d: TXEQ coefficient request timeout\n", qlm, lane);
        return -1;
    }
    /* Clear update request */
    BDK_CSR_MODIFY(c, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_CTRL0(qlm, lane),
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
int __bdk_qlm_gserr_get_tune_lane_tx(bdk_node_t node, int qlm, int lane, int *tx_cmain, int *tx_cpre, int *tx_cpost, int *tx_bs, int *tx_unused)
{
    BDK_CSR_INIT(status1, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_STATUS1(qlm, lane));
    BDK_CSR_INIT(status2, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_STATUS2(qlm, lane));
    BDK_CSR_INIT(status3, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_STATUS3(qlm, lane));
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
void __bdk_qlm_gserr_display_settings(bdk_node_t node, int qlm, int qlm_lane, bool show_tx, bool show_rx)
{
    printf("N%d.GSERR%d Lane %d:\n", node, qlm, qlm_lane);
    if (show_tx)
    {
        BDK_CSR_INIT(status1, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_STATUS1(qlm, qlm_lane));
        BDK_CSR_INIT(status2, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_STATUS2(qlm, qlm_lane));
        BDK_CSR_INIT(status3, node, BDK_GSERRX_LNX_DRV_REFCLK_TXEQ_STATUS3(qlm, qlm_lane));
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
                att = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_PLE_ATT_O_READ_VAL_2_0_RSVD(qlm));
                apg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_GN_APG_O_READ_VAL_2_0_RSVD(qlm));
                lfg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_EQ_LFG_O_READ_VAL_4_0_RSVD(qlm));
                hfg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_EQ_HFG_O_READ_VAL_4_0_RSVD(qlm));
                mbf = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_EQ_MBF_O_READ_VAL_3_0_RSVD(qlm));
                mbg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXLEQ_EQ_MBG_O_READ_VAL_3_0_RSVD(qlm));
                break;
            case 1:
                att = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_PLE_ATT_O_READ_VAL_2_0_RSVD(qlm));
                apg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_GN_APG_O_READ_VAL_2_0_RSVD(qlm));
                lfg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_EQ_LFG_O_READ_VAL_4_0_RSVD(qlm));
                hfg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_EQ_HFG_O_READ_VAL_4_0_RSVD(qlm));
                mbf = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_EQ_MBF_O_READ_VAL_3_0_RSVD(qlm));
                mbg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXLEQ_EQ_MBG_O_READ_VAL_3_0_RSVD(qlm));
                break;
            case 2:
                att = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_PLE_ATT_O_READ_VAL_2_0_RSVD(qlm));
                apg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_GN_APG_O_READ_VAL_2_0_RSVD(qlm));
                lfg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_EQ_LFG_O_READ_VAL_4_0_RSVD(qlm));
                hfg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_EQ_HFG_O_READ_VAL_4_0_RSVD(qlm));
                mbf = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_EQ_MBF_O_READ_VAL_3_0_RSVD(qlm));
                mbg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXLEQ_EQ_MBG_O_READ_VAL_3_0_RSVD(qlm));
                break;
            case 3:
                att = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_PLE_ATT_O_READ_VAL_2_0_RSVD(qlm));
                apg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_GN_APG_O_READ_VAL_2_0_RSVD(qlm));
                lfg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_EQ_LFG_O_READ_VAL_4_0_RSVD(qlm));
                hfg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_EQ_HFG_O_READ_VAL_4_0_RSVD(qlm));
                mbf = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_EQ_MBF_O_READ_VAL_3_0_RSVD(qlm));
                mbg = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXLEQ_EQ_MBG_O_READ_VAL_3_0_RSVD(qlm));
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
                    tap1_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXDFE_EVEN_TAP1_O_READ_VAL_6_0_RSVD(qlm));
                else
                    tap1_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXDFE_ODD_TAP1_O_READ_VAL_6_0_RSVD(qlm));
                tap2_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP2_O_READ_VAL_5_0_RSVD(qlm));
                tap3_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP3_O_READ_VAL_4_0_RSVD(qlm));
                tap4_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP4_O_READ_VAL_3_0_RSVD(qlm));
                tap5_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP5_O_READ_VAL_3_0_RSVD(qlm));
                tap6_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP6_O_READ_VAL_3_0_RSVD(qlm));
                tap7_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP7_O_READ_VAL_2_0_RSVD(qlm));
                tap8_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN0_RXDFE_TAP8_O_READ_VAL_2_0_RSVD(qlm));
                break;
            case 1:
                if (use_even == 1)
                    tap1_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXDFE_EVEN_TAP1_O_READ_VAL_6_0_RSVD(qlm));
                else
                    tap1_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXDFE_ODD_TAP1_O_READ_VAL_6_0_RSVD(qlm));
                tap2_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP2_O_READ_VAL_5_0_RSVD(qlm));
                tap3_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP3_O_READ_VAL_4_0_RSVD(qlm));
                tap4_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP4_O_READ_VAL_3_0_RSVD(qlm));
                tap5_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP5_O_READ_VAL_3_0_RSVD(qlm));
                tap6_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP6_O_READ_VAL_3_0_RSVD(qlm));
                tap7_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP7_O_READ_VAL_2_0_RSVD(qlm));
                tap8_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN1_RXDFE_TAP8_O_READ_VAL_2_0_RSVD(qlm));
                break;
            case 2:
                if (use_even == 1)
                    tap1_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXDFE_EVEN_TAP1_O_READ_VAL_6_0_RSVD(qlm));
                else
                    tap1_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXDFE_ODD_TAP1_O_READ_VAL_6_0_RSVD(qlm));
                tap2_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP2_O_READ_VAL_5_0_RSVD(qlm));
                tap3_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP3_O_READ_VAL_4_0_RSVD(qlm));
                tap4_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP4_O_READ_VAL_3_0_RSVD(qlm));
                tap5_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP5_O_READ_VAL_3_0_RSVD(qlm));
                tap6_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP6_O_READ_VAL_3_0_RSVD(qlm));
                tap7_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP7_O_READ_VAL_2_0_RSVD(qlm));
                tap8_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN2_RXDFE_TAP8_O_READ_VAL_2_0_RSVD(qlm));
                break;
            case 3:
                if (use_even == 1)
                    tap1_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXDFE_EVEN_TAP1_O_READ_VAL_6_0_RSVD(qlm));
                else
                    tap1_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXDFE_ODD_TAP1_O_READ_VAL_6_0_RSVD(qlm));
                tap2_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP2_O_READ_VAL_5_0_RSVD(qlm));
                tap3_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP3_O_READ_VAL_4_0_RSVD(qlm));
                tap4_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP4_O_READ_VAL_3_0_RSVD(qlm));
                tap5_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP5_O_READ_VAL_3_0_RSVD(qlm));
                tap6_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP6_O_READ_VAL_3_0_RSVD(qlm));
                tap7_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP7_O_READ_VAL_2_0_RSVD(qlm));
                tap8_val = BDK_CSR_READ(node, BDK_GSERRX_PHY0_AFE_OVR_AFE_LN3_RXDFE_TAP8_O_READ_VAL_2_0_RSVD(qlm));
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
    BDK_CSR_INIT(flag, node, BDK_GSERRX_PHY0_MB_CMD_FLAG(qlm));
    if (flag.s.data)
    {
        bdk_error("GSERR%d: Mailbox already has a command\n", qlm);
        return -1;
    }

    BDK_CSR_INIT(rsp_flag, node, BDK_GSERRX_PHY0_MB_RSP_FLAG(qlm));
    if (rsp_flag.s.data)
    {
        bdk_error("GSERR%d: Mailbox already has a response\n", qlm);
        return -1;
    }

    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_CMD_DATA0(qlm), bdk_extract(args, 0, 8));
    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_CMD_DATA1(qlm), bdk_extract(args, 8, 8));
    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_CMD_DATA2(qlm), bdk_extract(args, 16, 8));
    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_CMD_DATA3(qlm), bdk_extract(args, 24, 8));
    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_CMD_DATA4(qlm), bdk_extract(args, 32, 8));
    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_CMD_DATA5(qlm), bdk_extract(args, 40, 8));
    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_CMD_DATA6(qlm), bdk_extract(args, 48, 8));
    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_CMD_DATA7(qlm), bdk_extract(args, 56, 8));
    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_CMD(qlm), cmd);

    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_PHY0_MB_CMD_FLAG(qlm), data, ==, 0, 10000))
    {
        bdk_error("GSERR%d: Mailbox stuck on command\n", qlm);
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
    if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_PHY0_MB_RSP_FLAG(qlm), data, ==, 1, 10000))
    {
        bdk_error("GSERR%d: Mailbox has no response\n", qlm);
        return -1;
    }

    /* Read the response */
    BDK_CSR_INIT(rsp, node, BDK_GSERRX_PHY0_MB_RSP(qlm));
    BDK_CSR_INIT(data0, node, BDK_GSERRX_PHY0_MB_RSP_DATA0(qlm));
    BDK_CSR_INIT(data1, node, BDK_GSERRX_PHY0_MB_RSP_DATA1(qlm));
    BDK_CSR_INIT(data2, node, BDK_GSERRX_PHY0_MB_RSP_DATA2(qlm));
    BDK_CSR_INIT(data3, node, BDK_GSERRX_PHY0_MB_RSP_DATA3(qlm));
    BDK_CSR_INIT(data4, node, BDK_GSERRX_PHY0_MB_RSP_DATA4(qlm));
    BDK_CSR_INIT(data5, node, BDK_GSERRX_PHY0_MB_RSP_DATA5(qlm));
    BDK_CSR_INIT(data6, node, BDK_GSERRX_PHY0_MB_RSP_DATA6(qlm));
    BDK_CSR_INIT(data7, node, BDK_GSERRX_PHY0_MB_RSP_DATA7(qlm));
    BDK_CSR_INIT(data8, node, BDK_GSERRX_PHY0_MB_RSP_DATA8(qlm));
    BDK_CSR_INIT(data9, node, BDK_GSERRX_PHY0_MB_RSP_DATA9(qlm));
    BDK_CSR_INIT(data10, node, BDK_GSERRX_PHY0_MB_RSP_DATA10(qlm));
    BDK_CSR_INIT(data11, node, BDK_GSERRX_PHY0_MB_RSP_DATA11(qlm));
    BDK_CSR_INIT(data12, node, BDK_GSERRX_PHY0_MB_RSP_DATA12(qlm));
    BDK_CSR_INIT(data13, node, BDK_GSERRX_PHY0_MB_RSP_DATA13(qlm));
    BDK_CSR_INIT(data14, node, BDK_GSERRX_PHY0_MB_RSP_DATA14(qlm));
    BDK_CSR_INIT(data15, node, BDK_GSERRX_PHY0_MB_RSP_DATA15(qlm));

    /* Tell firmware we read the response */
    BDK_CSR_WRITE(node, BDK_GSERRX_PHY0_MB_RSP_FLAG(qlm), 1);

    /* Package and return the response */
    *arg0 = (uint64_t)data0.s.data;
    *arg0 |= (uint64_t)data1.s.data << 8;
    *arg0 |= (uint64_t)data2.s.data << 16;
    *arg0 |= (uint64_t)data3.s.data << 24;
    *arg0 |= (uint64_t)data4.s.data << 32;
    *arg0 |= (uint64_t)data5.s.data << 40;
    *arg0 |= (uint64_t)data6.s.data << 48;
    *arg0 |= (uint64_t)data7.s.data << 56;
    *arg1 = (uint64_t)data8.s.data;
    *arg1 |= (uint64_t)data9.s.data << 8;
    *arg1 |= (uint64_t)data10.s.data << 16;
    *arg1 |= (uint64_t)data11.s.data << 24;
    *arg1 |= (uint64_t)data12.s.data << 32;
    *arg1 |= (uint64_t)data13.s.data << 40;
    *arg1 |= (uint64_t)data14.s.data << 48;
    *arg1 |= (uint64_t)data15.s.data << 56;
    return rsp.s.data;
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
int __bdk_qlm__gserr_rx_equalization(bdk_node_t node, int qlm, int qlm_lane)
{
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return 0;

    int result = 0;
    BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(qlm));
    for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
    {
        if ((qlm_lane != -1) && (qlm_lane != lane))
            continue;

        BDK_TRACE(QLM, "N%d.GSERR%d.%d: Lane TXDP Clock Phase Calibration starting\n", node, qlm, lane);
        if (mailbox_command(node, qlm, 0x81, qlm_lane))
        {
            bdk_error("N%d.GSERR%d.%d: Lane TXDP Clock Phase Calibration failed to issue\n", node, qlm, lane);
            result = -1;
            continue;
        }
        uint64_t arg0 = 0;
        uint64_t arg1 = 0;
        int status = mailbox_response(node, qlm, &arg0, &arg1);
        switch (status)
        {
            case 0x00: /* Calibration OK */
                BDK_TRACE(QLM, "N%d.GSERR%d.%d: Lane TXDP Clock Phase Calibration: %lu\n", node, qlm, lane, arg0 & 0xff);
                break;
            case 0x01: /* Calibration Railed Low */
                bdk_error("N%d.GSERR%d.%d: Lane TXDP Clock Phase Calibration Railed Low\n", node, qlm, lane);
                result = -1;
                break;
            case 0x02: /* Calibration Railed High */
                bdk_error("N%d.GSERR%d.%d: Lane TXDP Clock Phase Calibration Railed High\n", node, qlm, lane);
                result = -1;
                break;
            default:
                bdk_error("N%d.GSERR%d.%d: Lane TXDP Clock Phase Calibration illegal response %d\n", node, qlm, lane, status);
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
int __bdk_qlm_gserr_eye_capture(bdk_node_t node, int qlm, int lane, int show_data, bdk_qlm_eye_t *eye_data)
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
        bdk_error("GSERR%d: Eye too high\n", qlm);
        return -1;
    }
    if (x_points > 128) /* Limit from static struct */
    {
        bdk_error("GSERR%d: Eye too high\n", qlm);
        return -1;
    }

    if (show_data)
    {
        printf("# Extensive 1D Rx Eye on GSERR%d Lane %d\n", qlm, lane);
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
        bdk_error("GSERR%d: Eye setup 1 failed\n", qlm);
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
        bdk_error("GSERR%d: Eye setup 2 failed\n", qlm);
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
            bdk_error("GSERR%d: Eye failed (%d)\n", qlm, rsp);
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
                        bdk_error("GSERR%d: Too many response\n", qlm);
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
void __bdk_qlm_gserr_init(bdk_node_t node)
{
    const char *firmware_file = NULL;
    int num_gserr = -1;

    /* Figure out which firmware file to use */
    if (bdk_is_model(OCTEONTX_CN96XX))
    {
        firmware_file = "/fatfs/serdes/gserr-cn96xx.frm.lzma";
        num_gserr = 3;
    }
    else if (bdk_is_model(OCTEONTX_CNF95XX))
    {
        firmware_file = "/fatfs/serdes/gserr-cnf95xx.frm.lzma";
        num_gserr = 3;
    }
    else if (bdk_is_model(OCTEONTX_LOKI))
    {
        firmware_file = "/fatfs/serdes/gserr-loki.frm.lzma";
        num_gserr = 1;
    }
    else if (bdk_is_model(OCTEONTX_CN98XX))
    {
        firmware_file = "/fatfs/serdes/gserr-cn98xx.frm.lzma";
        num_gserr = 5;
    }
    else
    {
        bdk_error("GSERR: Unrecognized chip\n");
        return;
    }

    BDK_CSR_INIT(gserrx_init_ctl, node, BDK_GSERRX_COMMON_PHY_CTRL_BCFG(0));
    if (!gserrx_init_ctl.s.cpu_reset)
    {
        BDK_TRACE(QLM, "GSERR: Firmware already loaded\n");
        return;
    }

    /* Open the firmware file */
    BDK_TRACE(QLM, "GSERR: Loading firmware %s\n", firmware_file);
    uint64_t filesize = 0;
    uint64_t *firmware = bdk_signed_load(firmware_file, 0,BDK_SIGNED_IMAGE, BDK_SIGNED_FLAG_NOT_ENCRYPTED, &filesize);
    if (!firmware)
    {
        bdk_error("GSERR: Failed to load firmware %s\n", firmware_file);
        return;
    }

    /* 1) Load the PHY Firmware - While not EOF read the FW file and write the
       FW image to the Program Memory (96KB, 12288*8Bytes) */
    /* Load the firmware */
    for (int index = 0; index < (int)filesize / 8; index++)
    {
        for (int gserr = 0; gserr < num_gserr; gserr++)
            BDK_CSR_WRITE(node, BDK_GSERRX_PMEMX(gserr, index), firmware[index]);
    }
    free(firmware);
    BDK_TRACE(QLM, "GSERR: Loading firmware of %lu bytes\n", filesize);

    /* 2. For each “Active” QLM Program the Lane Rate and Width parameters for
       each lane.
        Write GSERR()_LANE()_CONTROL_BCFG
            LN_CTRL_TX_RATE=3’h0 //PHY Rate 1 used here, but other PHY rates available
            LN_CTRL_RX_RATE=3’h0 //PHY Rate 1 used here, but other PHY rates available
            LN_CTRL_TX_WIDTH=3’h4 //32-bit Tx data width @25G & 20.625G, or 3’h2 for 16-bit width at 10G and lower data rates
            LN_CTRL_RX_WIDTH=3’h5 //40-bit Rx data width @25G & 20.625G, or 3’h3 for 20-bit width at 10G and lower data rates
            TX_CLK_MUX_SEL=5’h0 //Select cm0_clk_rate1_o as the transmitter clock source, or appropriate clock source for other PHY rates
            CGX_QUAD=0 //Set the CGX_QUAD=1 in all lanes which are part of a x4 link (Lanes 0,1,2,3).
            CGX_DUAL=0 //Set the CGX_DUAL=1 in all lanes which are part of a x2 link (Lane 0&1, or Lanes 2&3) */
    for (int gserr = 0; gserr < num_gserr; gserr++)
    {
        /* Find if 10G is rate 1 because 5G or 6G is needed */
        bool need_6g = false;
        bool need_5g = false;
        BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(gserr));
        for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
        {
            bdk_qlm_state_lane_t state = __bdk_qlm_gserr_get_state(node, gserr, lane);
            need_6g |= (state.s.baud_mhz == 6250) || (state.s.baud_mhz == 3125);
            need_5g |= (state.s.baud_mhz == 5000);
        }
        for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
        {
            bdk_qlm_state_lane_t state = __bdk_qlm_gserr_get_state(node, gserr, lane);
            int ln_ctrl_rate = 0;
            int tx_clk_mux_sel = 0;
            int ln_ctrl_tx_width = 0x4;
            int ln_ctrl_rx_width = 0x5;
            switch (state.s.baud_mhz)
            {
                case 1250:
                    ln_ctrl_rate = 2; /* PHY rate 3 */
                    tx_clk_mux_sel = 0x6; /* PHY rate 3 */
                    ln_ctrl_tx_width = 0x2; /* 16 bit */
                    ln_ctrl_rx_width = 0x3; /* 20 bit */
                    break;
                case 3125:
                    ln_ctrl_rate = 0x5; /* PHY rate 2 divide by 2 */
                    tx_clk_mux_sel = 0x4; /* PHY rate 2 divide by 2 */
                    ln_ctrl_tx_width = 0x2; /* 16 bit */
                    ln_ctrl_rx_width = 0x3; /* 20 bit */
                    break;
                case 5000:
                case 6250:
                    ln_ctrl_rate = 0x1; /* PHY rate 2 */
                    tx_clk_mux_sel = 0x1; /* PHY rate 2 */
                    ln_ctrl_tx_width = 0x2; /* 16 bit */
                    ln_ctrl_rx_width = 0x3; /* 20 bit */
                    break;
                case 10312:
                    if (need_6g || need_5g)
                    {
                        ln_ctrl_rate = 0x0; /* PHY rate 1 */
                        tx_clk_mux_sel = 0x0; /* PHY rate 1 */
                    }
                    else
                    {
                        ln_ctrl_rate = 0x1; /* PHY rate 2 */
                        tx_clk_mux_sel = 0x1; /* PHY rate 2 */
                    }
                    ln_ctrl_tx_width = 0x2; /* 16 bit */
                    ln_ctrl_rx_width = 0x3; /* 20 bit */
                    break;
                case 20625:
                case 25781:
                default:
                    ln_ctrl_rate = 0x0; /* PHY rate 1 */
                    tx_clk_mux_sel = 0x0; /* PHY rate 1 */
                    ln_ctrl_tx_width = 0x4; /* 32 bit */
                    ln_ctrl_rx_width = 0x5; /* 40 bit */
                    break;
            }
            bool is_dual = false;
            bool is_quad = false;
            switch (state.s.mode)
            {
                case BDK_QLM_MODE_RXAUI:
                case BDK_QLM_MODE_25GAUI_2_C2C:
                case BDK_QLM_MODE_40GAUI_2_C2C:
                case BDK_QLM_MODE_50GAUI_2_C2C:
                case BDK_QLM_MODE_50GAUI_2_C2M:
                case BDK_QLM_MODE_50G_CR2:
                case BDK_QLM_MODE_50G_KR2:
                    is_dual = true;
                    break;
                case BDK_QLM_MODE_XAUI:
                case BDK_QLM_MODE_XLAUI:
                case BDK_QLM_MODE_XLAUI_C2M:
                case BDK_QLM_MODE_40G_CR4:
                case BDK_QLM_MODE_40G_KR4:
                case BDK_QLM_MODE_50GAUI_4_C2C:
                case BDK_QLM_MODE_80GAUI_4_C2C:
                case BDK_QLM_MODE_CAUI_4_C2C:
                case BDK_QLM_MODE_CAUI_4_C2M:
                case BDK_QLM_MODE_100G_CR4:
                case BDK_QLM_MODE_100G_KR4:
                    is_quad = true;
                    break;
                default:
                    break;
            }
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_LANEX_CONTROL_BCFG(gserr, lane),
                c.s.ln_ctrl_tx_rate = ln_ctrl_rate;
                c.s.ln_ctrl_rx_rate = ln_ctrl_rate;
                c.s.ln_ctrl_tx_width = ln_ctrl_tx_width;
                c.s.ln_ctrl_rx_width = ln_ctrl_rx_width;
                c.s.tx_clk_mux_sel = tx_clk_mux_sel;
                c.s.cgx_quad = is_quad;
                c.s.cgx_dual = is_dual);
        }
    }

    /* 3) For each QLM, Active and not Active Program the PHY Rate 1 and Rate 2
        settings, also enable the reference clock buffer to the next downstream QLM
        Write GSERR()_COMMON_PHY_CTRL_BCFG //Repeat for Slave QLMs
            REFCLK_A_OE_R = 1’h1 //Enable reference clock A right side clock buffer to pass “clk_ref_a_r_o” to adjacent QLM
            REFCLK_INPUT_SEL = 3’h0 if refclk from the “refclkp/m” pads, else 3’h2 if refclk is from the “clk_ref_a_r_i” inputs from adjacent QLM
            PHY_CTRL_RATE1 = 6’h03 //Set PHY Rate 1 25.78125Gbps
            PHY_CTRL_RATE2 = 6’h23 //Set PHY Rate 2 10.3125Gbps */
    for (int gserr = 0; gserr < num_gserr; gserr++)
    {
        /* Find all needed clocks */
        bool need_25g = false;
        bool need_20g = false;
        bool need_10g = false;
        bool need_6g = false;
        bool need_5g = false;
        bool need_1g = false;
        BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(gserr));
        for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
        {
            bdk_qlm_state_lane_t state = __bdk_qlm_gserr_get_state(node, gserr, lane);
            need_25g |= (state.s.baud_mhz == 25781);
            need_20g |= (state.s.baud_mhz == 20625);
            need_10g |= (state.s.baud_mhz == 10312);
            need_6g |= (state.s.baud_mhz == 6250) || (state.s.baud_mhz == 3125);
            need_5g |= (state.s.baud_mhz == 5000);
            need_1g |= (state.s.baud_mhz == 1250);
        }
        /* This enum represents the clock modes we support. The names are PHY Rate
           1, Rate 2, and Rate 3. Rate 3 only exists on the first clock mode */
        enum
        {
            CLOCK_25G_10G_1G,   /* Ethernet */
            CLOCK_25G_6G,       /* 25G ethernet and RXAUI/XAUI */
            CLOCK_10G_6G,       /* 10G ethernet and RXAUI/XAUI */
            CLOCK_25G_5G,       /* 25G ethernet and QSGMII */
            CLOCK_10G_5G,       /* 10G ethernet and QSGMII */
            CLOCK_20G_10G,      /* 20G and 10G ethernet */
            CLOCK_20G_6G,       /* 20G ethernet and RXAUI/XAUI */
            CLOCK_20G_5G        /* 20G ethernet and QSGMII */
        } clock_mode;

        if (need_20g)
            clock_mode = (need_10g) ? CLOCK_20G_10G : (need_6g) ? CLOCK_20G_6G : CLOCK_20G_5G;
        else if (need_25g)
            clock_mode = (need_10g) ? CLOCK_25G_10G_1G : (need_6g) ? CLOCK_25G_6G : CLOCK_25G_5G;
        else
            clock_mode = (need_6g) ? CLOCK_10G_6G : (need_5g) ? CLOCK_10G_5G : CLOCK_25G_10G_1G;

        int phy_ctrl_rate1 = 3;
        int phy_ctrl_rate2 = 0x23;

        switch (clock_mode)
        {
            case CLOCK_25G_10G_1G:   /* Ethernet */
                phy_ctrl_rate1 = 0x03; /* 25G */
                phy_ctrl_rate2 = 0x23; /* 10G */
                /* rate 3 is auto enabled at 1G */
                break;
            case CLOCK_25G_6G:       /* 25G ethernet and RXAUI/XAUI */
                phy_ctrl_rate1 = 0x03; /* 25G */
                phy_ctrl_rate2 = 0x28; /* 6G */
                break;
            case CLOCK_10G_6G:       /* 10G ethernet and RXAUI/XAUI */
                phy_ctrl_rate1 = 0x23; /* 10G */
                phy_ctrl_rate2 = 0x28; /* 6G */
                break;
            case CLOCK_25G_5G:       /* 25G ethernet and QSGMII */
                phy_ctrl_rate1 = 0x03; /* 25G */
                phy_ctrl_rate2 = 0x2a; /* 5G */
                break;
            case CLOCK_10G_5G:       /* 10G ethernet and QSGMII */
                phy_ctrl_rate1 = 0x23; /* 10G */
                phy_ctrl_rate2 = 0x2a; /* 5G */
                break;
            case CLOCK_20G_10G:      /* 20G and 10G ethernet */
                phy_ctrl_rate1 = 0x05; /* 20G */
                phy_ctrl_rate2 = 0x23; /* 10G */
                break;
            case CLOCK_20G_6G:       /* 20G ethernet and RXAUI/XAUI */
                phy_ctrl_rate1 = 0x05; /* 20G */
                phy_ctrl_rate2 = 0x28; /* 6G */
                break;
            case CLOCK_20G_5G:       /* 20G ethernet and QSGMII */
                phy_ctrl_rate1 = 0x05; /* 20G */
                phy_ctrl_rate2 = 0x2a; /* 5G */
                break;
        }

        BDK_CSR_MODIFY(c, node, BDK_GSERRX_COMMON_PHY_CTRL_BCFG(gserr),
            c.s.refclk_a_oe_r = 1;
            c.s.refclk_input_sel = 0;
            c.s.phy_ctrl_rate1 = phy_ctrl_rate1;
            c.s.phy_ctrl_rate2 = phy_ctrl_rate2);
    }

    /* 4) Take the PHY out of reset and release the APB reset
        Write GSERR()_COMMON_PHY_CTRL_BCFG
        POR = 1’h0 //Release PHY Power-on Reset (POR)
        APB_RESET = 1’h0 //Release APB reset */
    for (int gserr = 0; gserr < num_gserr; gserr++)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERRX_COMMON_PHY_CTRL_BCFG(gserr),
            c.s.por = 0;
            c.s.apb_reset = 0);
    }

    /* 5) Take the CPU out of reset so it will boot and run the PHY firmware
        Write GSERR()_COMMON_PHY_CTRL_BCFG
        CPU_RESET = 1’h0 //Release CPU reset */
    for (int gserr = 0; gserr < num_gserr; gserr++)
    {
        BDK_CSR_MODIFY(c, node, BDK_GSERRX_COMMON_PHY_CTRL_BCFG(gserr),
            c.s.cpu_reset = 0);
    }

    /* 6) Poll for “CM0_STATE_CHNG_RDY=1” This signal indicates that the CMU
        has transitioned to the RESET state
        // transition into the RESET power state.
        Poll GSERR()_COMMON_PHY_STATUS_BSTS
            CM0_STATE_CHNG_RDY = 1'b1
            PHY_ERROR = 1'b1 //PHY_ERROR (signal err_o) should always be 1'b0 unless there is a startup problem with the PHY
                            // If PHY_ERROR=1'b1 then throw an Error Message else continue to poll for CM0_STATE_CHNG_RDY=1. */
    // FIXME
    /* 7) Poll for “CM0_STATE_CHNG_RDY=0” These signals indicate that the CMU
        is transitioning between states
        // transition into the RESET power state.
        Poll GSERR()_COMMON_PHY_STATUS_BSTS
            CM0_STATE_CHNG_RDY = 1’b0
            PHY_ERROR = 1’b0 //PHY_ERROR (signal err_o) should always be 1'b0 unless there is a startup problem with the PHY
                            // If PHY_ERROR=1'b1 then throw an Error Message, else continue to poll for CM0_STATE_CHNG_RDY=0. */
    // FIXME
    /* 8) Poll for “CM0_STATE_CHNG_RDY=1” and “CM0_OK=1” These signals indicate
        that the CMU is in the ACTIVE state
        // transition into the RESET power state.
        Poll GSERR()_COMMON_PHY_STATUS_BSTS
            CM0_STATE_CHNG_RDY = 1’b1
            CM0_OK = 1’b1
            PHY_ERROR = 1’b0 //PHY_ERROR (signal err_o) should always be 1'b0 unless there is a startup problem with the PHY
                            // If PHY_ERROR=1'b1 then throw an Error Message, else continue to poll for CM0_STATE_CHNG_RDY=1. */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        for (int gserr = 0; gserr < num_gserr; gserr++)
        {
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_COMMON_PHY_STATUS_BSTS(gserr), cm0_ok, ==, 1, 10000))
                bdk_error("GSERR%d: Timeout waiting for GSERRX_COMMON_PHY_STATUS_BSTS[cm0_ok]=1\n", gserr);
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_COMMON_PHY_STATUS_BSTS(gserr), cm0_state_chng_rdy, ==, 1, 10000))
                bdk_error("GSERR%d: Timeout waiting for GSERRX_COMMON_PHY_STATUS_BSTS[cm0_state_chng_rdy]=1\n", gserr);
            if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_COMMON_PHY_STATUS_BSTS(gserr), phy_error, ==, 0, 10000))
                bdk_error("GSERR%d: Timeout waiting for GSERRX_COMMON_PHY_STATUS_BSTS[phy_error]=0\n", gserr);
        }
    }
    /* 9) Poll for all lanes “Ready” to indicate the LANE is in the “RESET” state
        For i=0 to 3, i++
            Poll GSERR()_LANE(i)_STATUS_BSTS
                LN_STATE_CHNG_RDY = 1'b1 //Lane is in RESET power state
        next i;
        // Use a watchdog timer on “LN_STATE_CHNG_RDY” in case this signal never goes ready. */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        for (int gserr = 0; gserr < num_gserr; gserr++)
        {
            BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(gserr));
            for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
            {
                if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_LANEX_STATUS_BSTS(gserr, lane), ln_state_chng_rdy, ==, 1, 10000))
                    bdk_error("GSERR%d: Timeout waiting for GSERRX_LANEX_STATUS_BSTS[ln_state_chng_rdy]=1\n", gserr);
            }
            /* Enable the BIST/PRBS clocks before starting each lane */
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_PHY0_TOP_CLOCK_LN0_CG_CTRL(gserr),
                c.s.bist_rx = 1;
                c.s.bist_tx = 1);
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_PHY0_TOP_CLOCK_LN1_CG_CTRL(gserr),
                c.s.bist_rx = 1;
                c.s.bist_tx = 1);
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_PHY0_TOP_CLOCK_LN2_CG_CTRL(gserr),
                c.s.bist_rx = 1;
                c.s.bist_tx = 1);
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_PHY0_TOP_CLOCK_LN3_CG_CTRL(gserr),
                c.s.bist_rx = 1;
                c.s.bist_tx = 1);
        }
    }
    /* 10) Take the lanes out of reset
        For i=0 to 3, i++
            Write GSERR()_LANE(i)_CONTROL_BCFG
                LN_RST_N = 1'b1
        next i */
    for (int gserr = 0; gserr < num_gserr; gserr++)
    {
        BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(gserr));
        for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_LANEX_CONTROL_BCFG(gserr, lane),
                c.s.ln_rst = 0);
        }
    }
    /* 11) Poll for “LN_STATE_CHNG_RDY = 1” & “LN_TX_RDY=1” & “LN_RX_RDY=1” to
        indicate the Lane is in the “Active” power state
        For i=0 to 3, i++
            Poll GSERR()_LANE(i)_STATUS_BSTS
                LN_TX_RDY=1’b1 //Lane Tx is up
                LN_RX_RDY=1’b1 //Lane Rx is up
                LN_STATE_CHNG_RDY = 1'b1 //Lane is in RESET power state
        next i */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        for (int gserr = 0; gserr < num_gserr; gserr++)
        {
            BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(gserr));
            for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
            {
                if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_LANEX_STATUS_BSTS(gserr, lane), ln_tx_rdy, ==, 1, 10000))
                    bdk_error("GSERR%d: Timeout waiting for GSERRX_LANEX_STATUS_BSTS[ln_tx_rdy]=1\n", gserr);
                if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_LANEX_STATUS_BSTS(gserr, lane), ln_rx_rdy, ==, 1, 10000))
                    bdk_error("GSERR%d: Timeout waiting for GSERRX_LANEX_STATUS_BSTS[ln_rx_rdy]=1\n", gserr);
                if (BDK_CSR_WAIT_FOR_FIELD(node, BDK_GSERRX_LANEX_STATUS_BSTS(gserr, lane), ln_state_chng_rdy, ==, 1, 10000))
                    bdk_error("GSERR%d: Timeout waiting for GSERRX_LANEX_STATUS_BSTS[ln_state_chng_rdy]=1\n", gserr);
            }
        }
    }
    /* 12) Once Lane is Tx and Rx is Ready set the CFG_CGX=1 to enable the Tx/Rx
        FIFOs between CGX and PHY.
        Write in reverse order, Lane 3 down to Lane 0
        For i=3 to 0, i--
            Write GSERR()_LANE(i)_CONTROL_BCFG
                CFG_CGX = 1 //Enable Tx and Rx FIFOs to CGX
        next i */
    for (int gserr = num_gserr - 1; gserr >= 0; gserr--)
    {
        BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(gserr));
        for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_LANEX_CONTROL_BCFG(gserr, lane),
                c.s.cfg_cgx = 1);
        }
    }
    /* 13) The CGX MAC transmitter can be started at this point */
    /* 14) Once CGX starts transmitting set the SerDes Transmitter Enable on
        each lane that is enabled
        For i=0 to 3, i++
            Write GSERR()_LANE(i)_CONTROL_BCFG
                LN_CTRL_TX_EN = 1’b1 //Enable the Lane SerDes transmitter driver
        next i */
    for (int gserr = 0; gserr < num_gserr; gserr++)
    {
        BDK_CSR_INIT(gserrx_const, node, BDK_GSERRX_CONST(gserr));
        for (int lane = 0; lane < gserrx_const.s.nr_lanes; lane++)
        {
            BDK_CSR_MODIFY(c, node, BDK_GSERRX_LANEX_CONTROL_BCFG(gserr, lane),
                c.s.ln_ctrl_tx_en = 1);
        }
    }
    /* 15) Poll the receiver looking for a valid receive signal and the indication
        that the PHY Lane Rx CDR is locked
        For i=0 to 3, i++
            Poll GSERR()_LANE(i)_STATUS_BSTS
                LN_STAT_LOS=1'b0 //Rx signal carrier detected (Loss-of-signal is negated)
                LN_STAT_RXVALID=1'b1 //Rx CDR has locked and Rx data is valid
        next i */
    /* 16) Now bring up the CGX receiver */
}
