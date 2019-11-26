/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "bdk-qlm-common.h"
#include "bdk-qlm-common-gserp.h"
#include "bdk-qlm-common-gserr.h"
#include "bdk-qlm-common-gserc.h"
#include "libbdk-arch/bdk-csrs-pem.h"

#define GSERP_MIN 0 /* QLM0 => GSERP */
#define GSERP_MAX 0 /* QLM0 => GSERP */
#define GSERR_MIN 1 /* QLM1 => GSERR */
#define GSERR_MAX 1 /* QLM1 => GSERR */
#define GSERC_MIN 2 /* DLM2 => GSERC */
#define GSERC_MAX 6 /* DLM6 => GSERC */

/**
 * Return the number of QLMs supported for the chip
 *
 * @return Number of QLMs
 */
static int qlm_get_num(bdk_node_t node)
{
    return 7; /* 1 QLM (GSERP), 1 QLM (GSERR), 5 DLM (GSERC) */
}

/**
 * Return the number of lanes in a QLM. QLMs normally contain
 * 4 lanes, except for chips which only have half of a QLM.
 *
 * @param qlm    QLM to get lanes number for
 *
 * @return Number of lanes on the QLM
 */
static int qlm_get_lanes(bdk_node_t node, int qlm)
{
    return (qlm < 2) ? 4 : 2;
}

/**
 * Lookup the hardware QLM number for a given interface type and index. This
 * function will fail with a fatal error if called on invalid interfaces for
 * a chip. It returns the QLM number for an interface without checking to
 * see if the QLM is in the correct mode.
 *
 * @param iftype    Interface type
 * @param interface Interface index number
 *
 * @return QLM number. Dies on a fatal error on failure.
 */
static int qlm_get_qlm_num(bdk_node_t node, bdk_if_t iftype, int interface, int index)
{
    switch (iftype)
    {
        case BDK_IF_CGX:
        {
            switch (interface)
            {
                case 0:
                {
                    bdk_qlm_state_lane_t state = __bdk_qlm_gserr_get_state(node, 0, 0);
                    if (state.s.cgx)
                        return GSERR_MIN;
                    break;
                }
                case 1 ... 3:
                {
                    int dlm = GSERC_MIN + (interface - 1) * 2;
                    /* All DLMs */
                    bdk_qlm_state_lane_t state = __bdk_qlm_gserc_get_state(node, dlm - GSERC_MIN, 0);
                    int lane = index;
                    if ((state.s.mode == BDK_QLM_MODE_QSGMII) || (state.s.mode == BDK_QLM_MODE_USXGMII_4X1))
                        lane = 0;
                    if (lane >= 2)
                    {
                        lane -= 2;
                        dlm++;
                        if (dlm > GSERC_MAX)
                            return -1;
                    }
                    state = __bdk_qlm_gserc_get_state(node, dlm - GSERC_MIN, lane);
                    if (state.s.cgx)
                        return dlm;
                    break;
                }
            }
            return -1;
        }
        case BDK_IF_PCIE: /* PCIe */
        {
            if (interface == 0)
            {
                bdk_qlm_state_lane_t state = __bdk_qlm_gserp_get_state(node, 0, 0);
                if (state.s.pcie)
                    return 0;
            }
            return -1;
        }
        default: /* Not supported by CNF95XX */
            return -1;
    }
}

/**
 * Get the mode of a QLM as a human readable string
 *
 * @param node   Node to use in a Numa setup
 * @param qlm    QLM to examine
 * @param lane   Lane inside the QLM
 *
 * @return String mode
 */
static bdk_qlm_modes_t qlm_get_mode(bdk_node_t node, int qlm, int lane)
{
    bdk_qlm_state_lane_t qlm_state;
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            qlm_state = __bdk_qlm_gserp_get_state(node, qlm - GSERP_MIN, lane);
            break;
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            qlm_state = __bdk_qlm_gserr_get_state(node, qlm - GSERR_MIN, lane);
            break;
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            qlm_state = __bdk_qlm_gserc_get_state(node, qlm - GSERC_MIN, lane);
            break;
        default:
            return BDK_QLM_MODE_DISABLED;
    }
    return qlm_state.s.mode;
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
static int qlm_set_mode(bdk_node_t node, int qlm, int lane, bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
        {
            if (__bdk_qlm_gserp_set_mode(node, qlm - GSERP_MIN, lane, mode, baud_mhz, flags))
                return -1;
            if ((mode >= BDK_QLM_MODE_PCIE_X1) && (mode <= BDK_QLM_MODE_PCIE_X16))
            {
                bool is_rc = !(flags & BDK_QLM_MODE_FLAG_ENDPOINT);
                /* LANES= 0= 2 lanes, 1= 4 lanes, 2 = 8 lanes, 3= 16 lanes */
                BDK_CSR_MODIFY(c, node, BDK_PEMX_CFG(0),
                    c.cn9.hostmd = is_rc;
                    c.cn9.lanes = 1); /* The width has to be the width of the QLM */
            }
            return 0;
        }
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_set_mode(node, qlm - GSERR_MIN, lane, mode, baud_mhz, flags);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_set_mode(node, qlm - GSERC_MIN, lane, mode, baud_mhz, flags);
        default:
            return -1;
    }
}

/**
 * Get the speed (Gbaud) of the QLM in Mhz.
 *
 * @param node   Node to query
 * @param qlm    QLM to examine
 * @param lane   Lane inside the QLM
 *
 * @return Speed in Mhz
 */
static int qlm_get_gbaud_mhz(bdk_node_t node, int qlm, int lane)
{
    bdk_qlm_state_lane_t qlm_state;
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            qlm_state = __bdk_qlm_gserp_get_state(node, qlm - GSERP_MIN, lane);
            break;
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            qlm_state = __bdk_qlm_gserr_get_state(node, qlm - GSERR_MIN, lane);
            break;
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            qlm_state = __bdk_qlm_gserc_get_state(node, qlm - GSERC_MIN, lane);
            break;
        default:
            return 0;
    }
    return qlm_state.s.baud_mhz;
}

/**
 * Measure the reference clock of a QLM
 *
 * @param qlm    QLM to measure
 *
 * @return Clock rate in Hz
 */
static int qlm_measure_refclock(bdk_node_t node, int qlm)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm_gserp_measure_refclock(node, qlm - GSERP_MIN);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_measure_refclock(node, qlm - GSERR_MIN);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_measure_refclock(node, qlm - GSERC_MIN);
        default:
            return 0;
    }
}

/**
 * Put a QLM into hardware reset
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
static int qlm_reset(bdk_node_t node, int qlm)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm_gserp_reset(node, qlm - GSERP_MIN);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_reset(node, qlm - GSERR_MIN);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_reset(node, qlm - GSERC_MIN);
        default:
            return -1;
    }
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
static int qlm_enable_prbs(bdk_node_t node, int qlm, int prbs, bdk_qlm_direction_t dir)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm_gserp_enable_prbs(node, qlm - GSERP_MIN, prbs, dir);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_enable_prbs(node, qlm - GSERR_MIN, prbs, dir);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_enable_prbs(node, qlm - GSERC_MIN, prbs, dir);
        default:
            return -1;
    }
}

/**
 * Disable PRBS on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
static int qlm_disable_prbs(bdk_node_t node, int qlm)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm_gserp_disable_prbs(node, qlm - GSERP_MIN);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_disable_prbs(node, qlm - GSERR_MIN);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_disable_prbs(node, qlm - GSERC_MIN);
        default:
            return -1;
    }
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
static uint64_t qlm_get_prbs_errors(bdk_node_t node, int qlm, int lane, int clear)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm_gserp_get_prbs_errors(node, qlm - GSERP_MIN, lane, clear);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_get_prbs_errors(node, qlm - GSERR_MIN, lane, clear);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_get_prbs_errors(node, qlm - GSERC_MIN, lane, clear);
        default:
            return -1;
    }
}

/**
 * Inject an error into PRBS
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 */
static void qlm_inject_prbs_error(bdk_node_t node, int qlm, int lane)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            __bdk_qlm_gserp_inject_prbs_error(node, qlm - GSERP_MIN, lane);
            break;
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            __bdk_qlm_gserr_inject_prbs_error(node, qlm - GSERR_MIN, lane);
            break;
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            __bdk_qlm_gserc_inject_prbs_error(node, qlm - GSERC_MIN, lane);
            break;
    }
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
static int qlm_enable_loop(bdk_node_t node, int qlm, bdk_qlm_loop_t loop)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm_gserp_enable_loop(node, qlm - GSERP_MIN, loop);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_enable_loop(node, qlm - GSERR_MIN, loop);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_enable_loop(node, qlm - GSERC_MIN, loop);
        default:
            return -1;
    }
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
static int qlm_tune_lane_tx(bdk_node_t node, int qlm, int lane, int tx_cmain, int tx_cpre, int tx_cpost, int tx_bs, int tx_unused)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm_gserp_tune_lane_tx(node, qlm - GSERP_MIN, lane, tx_cmain, tx_cpre, tx_cpost, tx_bs, tx_unused);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_tune_lane_tx(node, qlm - GSERR_MIN, lane, tx_cmain, tx_cpre, tx_cpost, tx_bs, tx_unused);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_tune_lane_tx(node, qlm - GSERC_MIN, lane, tx_cmain, tx_cpre, tx_cpost, tx_bs, tx_unused);
        default:
            return -1;
    }
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
static int qlm_get_tune_lane_tx(bdk_node_t node, int qlm, int lane, int *tx_cmain, int *tx_cpre, int *tx_cpost, int *tx_bs, int *tx_unused)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm_gserp_get_tune_lane_tx(node, qlm - GSERP_MIN, lane, tx_cmain, tx_cpre, tx_cpost, tx_bs, tx_unused);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_get_tune_lane_tx(node, qlm - GSERR_MIN, lane, tx_cmain, tx_cpre, tx_cpost, tx_bs, tx_unused);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_get_tune_lane_tx(node, qlm - GSERC_MIN, lane, tx_cmain, tx_cpre, tx_cpost, tx_bs, tx_unused);
        default:
            return -1;
    }
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
static int qlm_rx_equalization(bdk_node_t node, int qlm, int qlm_lane)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm__gserp_rx_equalization(node, qlm - GSERP_MIN, qlm_lane);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm__gserr_rx_equalization(node, qlm - GSERR_MIN, qlm_lane);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm__gserc_rx_equalization(node, qlm - GSERC_MIN, qlm_lane);
        default:
            return -1;
    }
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
static void qlm_display_settings(bdk_node_t node, int qlm, int qlm_lane, bool show_tx, bool show_rx)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            __bdk_qlm_gserp_display_settings(node, qlm - GSERP_MIN, qlm_lane, show_tx, show_rx);
            break;
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            __bdk_qlm_gserr_display_settings(node, qlm - GSERR_MIN, qlm_lane, show_tx, show_rx);
            break;
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            __bdk_qlm_gserc_display_settings(node, qlm - GSERC_MIN, qlm_lane, show_tx, show_rx);
            break;
    }
}

static const bdk_qlm_mode_desc_t qlm0[] = {
    /* PEM0 */
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 2500},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 5000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 8000},
    {BDK_QLM_MODE_PCIE_X4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_1, 16000},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t qlm1[] = {
    /* CGX0 */
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 5000},
    {BDK_QLM_MODE_XAUI,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 3125},
    {BDK_QLM_MODE_XAUI,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_SFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_XLAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_XLAUI_C2M,    BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_40G_CR4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_40G_KR4,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_20GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_25GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_CR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_80GAUI_4_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_CAUI_4_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_CAUI_4_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_100G_CR4,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_100G_KR4,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_USXGMII_4X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_USXGMII_2X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_USXGMII_1X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};
static const bdk_qlm_mode_desc_t dlms[] = {
    /* CGX1-3 */
    {BDK_QLM_MODE_SGMII,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_1G_X,         BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 1250},
    {BDK_QLM_MODE_QSGMII,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 5000},
    {BDK_QLM_MODE_RXAUI,        BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 6250},
    {BDK_QLM_MODE_XFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_SFI,          BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_10G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_20GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_25GAUI_C2C,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25GAUI_C2M,   BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_CR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_25G_KR,       BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_40GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_50GAUI_2_C2C, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50GAUI_2_C2M, BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_CR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_50G_KR2,      BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 25781},
    {BDK_QLM_MODE_USXGMII_4X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_USXGMII_2X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 20625},
    {BDK_QLM_MODE_USXGMII_1X1,  BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_2, 10312},
    {BDK_QLM_MODE_DISABLED,     BDK_QLM_MODE_FLAG_NONE, BDK_QLM_CLK_COMMON_0, 0}
};

/**
 * Return an array describing the modes allowed for q QLM/DLM
 *
 * @param node   Node to query
 * @param qlm    QLM/DLM to describe
 *
 * @return Mode description
 */
static const bdk_qlm_mode_desc_t* qlm_get_mode_desc(bdk_node_t node, int qlm)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: return qlm0;
        case GSERR_MIN ... GSERR_MAX: return qlm1;
        case GSERC_MIN ... GSERC_MAX: return dlms;
        default: return NULL;
    }
}

/**
 * Return the BGX/CGX interface number that corresponds to the supplied DLM/QLM.
 * This function returns the same result regardless of board configuration. If a
 * single BGX/CGX can be used by multiple DLM/QLM, all of those DLM/QLM will
 * return the same interface. The current active configuration is ignored.
 *
 * @param node     Node to lookup
 * @param qlm      DLM/QLM to lookup
 * @param is_split Set to true if the BGX/CGX is split across two DLMs
 * @param is_upper Set to true if the requested DLM is the upper half of a BGX/CGX
 *
 * @return BGX/CGX number, or -1 if the DLM/QLM can't be used with networking
 */
static int qlm_to_network(bdk_node_t node, int qlm, bool *is_split, bool *is_upper)
{
    /* Which CGX maps to a specific QLM/DLM
       CGX0: QLM1
       CGX1: DLM2-3
       CGX2: DLM4-5
       CGX3: DLM6 */
    const int8_t qlm_to_cgx[7] = {-1, 0, 1, 1, 2, 2, 3};
    *is_split = (qlm >= 2);
    *is_upper = (qlm == 3) || (qlm == 5);
    return qlm_to_cgx[qlm];
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
static int qlm_eye_capture(bdk_node_t node, int qlm, int lane, int show_data, bdk_qlm_eye_t *eye_data)
{
    switch (qlm)
    {
        case GSERP_MIN ... GSERP_MAX: /* GSERP */
            return __bdk_qlm_gserp_eye_capture(node, qlm - GSERP_MIN, lane, show_data, eye_data);
        case GSERR_MIN ... GSERR_MAX: /* GSERR */
            return __bdk_qlm_gserr_eye_capture(node, qlm - GSERR_MIN, lane, show_data, eye_data);
        case GSERC_MIN ... GSERC_MAX: /* GSERC */
            return __bdk_qlm_gserc_eye_capture(node, qlm - GSERC_MIN, lane, show_data, eye_data);
    }
    return -1;
}

/**
 * Initialize the QLM layer
 */
static void qlm_init(bdk_node_t node)
{
}

/* Each chip has its own QLM operation table */
const bdk_qlm_ops_t bdk_qlm_ops_loki = {
    .chip_model = OCTEONTX_LOKI,
    .init = qlm_init,
    .get_num = qlm_get_num,
    .get_lanes = qlm_get_lanes,
    .get_mode = qlm_get_mode,
    .set_mode = qlm_set_mode,
    .get_gbaud_mhz = qlm_get_gbaud_mhz,
    .measure_refclock = qlm_measure_refclock,
    .get_qlm_num = qlm_get_qlm_num,
    .reset = qlm_reset,
    .enable_prbs = qlm_enable_prbs,
    .disable_prbs = qlm_disable_prbs,
    .get_prbs_errors = qlm_get_prbs_errors,
    .inject_prbs_error = qlm_inject_prbs_error,
    .enable_loop = qlm_enable_loop,
    .auto_config = bdk_qlm_mcu_auto_config,
    .tune_lane_tx = qlm_tune_lane_tx,
    .get_tune_lane_tx = qlm_get_tune_lane_tx,
    .rx_equalization = qlm_rx_equalization,
    .eye_capture = qlm_eye_capture,
    .display_settings = qlm_display_settings,
    .get_mode_desc = qlm_get_mode_desc,
    .qlm_to_network = qlm_to_network,
};

