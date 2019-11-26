/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#ifndef __BDK_QLM_COMMON_CN8XXX_H__
#define __BDK_QLM_COMMON_CN8XXX_H__

/**
 * Setup the PEM to either driver or receive reset from PRST based on RC or EP
 *
 * @param node   Node to use in a Numa setup
 * @param pem    Which PEM to setuo
 * @param is_endpoint
 *               Non zero if PEM is a EP
 */
extern void __bdk_qlm_setup_pem_reset_cn8xxx(bdk_node_t node, int pem, int is_endpoint);

/**
 * Given a valid PEM number, return its speed in Gbaud
 *
 * @param node   Node to use in numa setup
 * @param pem    PEM to get speed of
 *
 * @return Speed in Gbaud. Zero if disabled
 */
extern int __bdk_qlm_get_gbaud_mhz_pem_cn8xxx(bdk_node_t node, int pem);

/**
 * Figure out which lane mode to use for a given reference clock and GBaud
 *
 * @param mode_name String name for error messages
 * @param qlm       QlM being configured
 * @param ref_clk   Reference clock in hertz
 * @param baud_mhz  Baud rate in Mhz
 *
 * @return Lane mode or -1 on failure
 */
extern int __bdk_qlm_get_lane_mode_for_speed_and_ref_clk_cn8xxx(const char *mode_name, int qlm, int ref_clk, int baud_mhz);

/**
 * Measure the reference clock of a QLM
 *
 * @param qlm    QLM to measure
 *
 * @return Clock rate in Hz
 */
extern int __bdk_qlm_measure_refclock_cn8xxx(bdk_node_t node, int qlm);

/**
 * Put a QLM into hardware reset
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_reset_cn8xxx(bdk_node_t node, int qlm);

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
extern int __bdk_qlm_enable_prbs_cn8xxx(bdk_node_t node, int qlm, int prbs, bdk_qlm_direction_t dir);

/**
 * Disable PRBS on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_disable_prbs_cn8xxx(bdk_node_t node, int qlm);

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
extern uint64_t __bdk_qlm_get_prbs_errors_cn8xxx(bdk_node_t node, int qlm, int lane, int clear);

/**
 * Inject an error into PRBS
 *
 * @param node   Node to use in numa setup
 * @param qlm    QLM to use
 * @param lane   Which lane
 */
extern void __bdk_qlm_inject_prbs_error_cn8xxx(bdk_node_t node, int qlm, int lane);

/**
 * Enable shallow loopback on a QLM
 *
 * @param node   Node to use in a numa setup
 * @param qlm    QLM to use
 * @param loop   Type of loopback. Not all QLMs support all modes
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_enable_loop_cn8xxx(bdk_node_t node, int qlm, bdk_qlm_loop_t loop);

/**
 * Initialize the QLM mode table
 *
 * @param node    Node to initialize
 * @param qlm     Which QLM
 * @param ref_clk Reference clock of the QLM in Hz
 */
extern void __bdk_qlm_init_mode_table_cn8xxx(bdk_node_t node, int qlm, int ref_clk);

/**
 * Get the speed of a QLM using its LMODE. This can't be used on PCIe QLMs.
 *
 * @param node   Node to use in numa setup
 * @param qlm    Which QLM
 *
 * @return QLM speed on Gbaud
 */
extern int __bdk_qlm_get_gbaud_mhz_lmode_cn8xxx(bdk_node_t node, int qlm);

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
extern int __bdk_qlm_eye_capture_cn8xxx(bdk_node_t node, int qlm, int lane, int show_data, bdk_qlm_eye_t *eye_data) BDK_WEAK;

/**
 * Disables DFE for the specified QLM lane(s).
 * This function should only be called for low-loss channels.
 *
 * @param node   Node to configure
 * @param qlm    QLM to configure
 * @param lane   Lane to configure, or -1 for all lanes
 */
extern void __bdk_qlm_dfe_disable_cn8xxx(int node, int qlm, int lane);

/**
 * Check if a specific lane is using KR training. This is used by low level GSER
 * code to remember which QLMs and lanes need to support KR training for BGX. The
 * hardware doesn't have a bit set aside to record this, so we repurpose the
 * register GSERX_SCRATCH.
 *
 * @param node   Node to check
 * @param qlm    QLM to check
 * @param lane   Lane to check
 *
 * @return True if this lane uses KR with BGX, false otherwise
 */
extern bool __bdk_qlm_is_lane_kr_cn8xxx(bdk_node_t node, int qlm, int lane);

/**
 * Set if a specific lane is using KR training. This is used by low level GSER
 * code to remember which QLMs and lanes need to support KR training for BGX. The
 * hardware doesn't have a bit set aside to record this, so we repurpose the
 * register GSERX_SCRATCH.
 *
 * @param node   Node to set
 * @param qlm    QLM to set
 * @param lane   Lane to set
 * @param is_kr  KR (true) or XFI/XLAUI (false)
 */
extern void __bdk_qlm_set_lane_kr_cn8xxx(bdk_node_t node, int qlm, int lane, bool is_kr);

/**
 * Initialize a DLM/QLM for use with SATA controllers
 *
 * @param node       Node to initialize
 * @param qlm        Which DLM/QLM to init
 * @param baud_mhz   QLM speed in Gbaud
 * @param sata_first First SATA controller connected to this DLM/QLM
 * @param sata_last  Last SATA controller connected to this DLM/QLM (inclusive)
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_set_sata_cn8xxx(bdk_node_t node, int qlm, int baud_mhz, int sata_first, int sata_last);

/**
 * Perform RX equalization on a QLM
 *
 * @param node     Node the QLM is on
 * @param qlm      QLM to perform RX equalization on
 * @param qlm_lane Lane to use, or -1 for all lanes
 *
 * @return Zero on success, negative if any lane failed RX equalization
 */
extern int __bdk_qlm_rx_equalization_cn8xxx(bdk_node_t node, int qlm, int qlm_lane);

/**
 * Configure the TX tuning parameters for a QLM lane
 *
 * @param node      Node to configure
 * @param qlm       QLM to configure
 * @param lane      Lane to configure
 * @param tx_swing  Transmit swing (coef 0) Range 0-31
 * @param tx_pre    Pre cursor emphasis (Coef -1). Range 0-15
 * @param tx_post   Post cursor emphasis (Coef +1). Range 0-31
 * @param tx_gain   Transmit gain. Range 0-7
 * @param tx_vboost Transmit voltage boost. Range 0-1
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_tune_lane_tx_cn8xxx(bdk_node_t node, int qlm, int lane, int tx_swing, int tx_pre, int tx_post, int tx_gain, int tx_vboost);

/**
 * Get the TX tuning parameters for a QLM lane
 *
 * @param node     Node to configure
 * @param qlm      QLM to configure
 * @param lane     Lane to configure
 * @param tx_swing Transmit swing, also called cMain (coef 0)
 * @param tx_pre   Pre cursor emphasis (Coef -1)
 * @param tx_post  Post cursor emphasis (Coef +1)
 * @param tx_gain_bias
 *                 For CN8XXX, this is transmit gain. For CN9XXX, this is transmit bias
 * @param tx_vboost_unused
 *                 For CN8XXX, this is transmit voltage boost. For CN9XXX, this is unused
 *
 * @return Zero on success, negative on failure
 */
extern int __bdk_qlm_get_tune_lane_tx_cn8xxx(bdk_node_t node, int qlm, int lane, int *tx_swing, int *tx_pre, int *tx_post, int *tx_gain_bias, int *tx_vboost_unused);

/**
 * Some QLM speeds need to override the default tuning parameters
 *
 * @param node     Node to use in a Numa setup
 * @param qlm      QLM to configure
 * @param mode     Desired mode
 * @param baud_mhz Desired speed
 */
extern void __bdk_qlm_tune_cn8xxx(bdk_node_t node, int qlm, bdk_qlm_modes_t mode, int baud_mhz);

/**
 * Display the current settings of a QLM lane
 *
 * @param node     Node the QLM is on
 * @param qlm      QLM to display
 * @param qlm_lane Lane to use
 * @param show_tx  Display TX parameters
 * @param show_rx  Display RX parameters
 */
extern void __bdk_qlm_display_settings_cn8xxx(bdk_node_t node, int qlm, int qlm_lane, bool show_tx, bool show_rx);

#endif /* __BDK_QLM_COMMON_CN8XXX_H__ */
