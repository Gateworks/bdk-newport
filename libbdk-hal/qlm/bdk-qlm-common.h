/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#ifndef __BDK_QLM_COMMON_H__
#define __BDK_QLM_COMMON_H__

/* These constants represent the possible QLM reference clock speeds in Hz */
#define REF_100MHZ 100000000
#define REF_125MHZ 125000000
#define REF_156MHZ 156250000

/**
 * This structure is stored in GSER* scratch registers to remember the mode of a
 * single lane.
 */
typedef union
{
    uint64_t u;
    struct
    {
        uint16_t                baud_mhz;       /**< Baudrate of the lane in MHz */
        bdk_qlm_modes_t         mode : 8;       /**< Mode of the lane, enumerated by bdk_qlm_modes_t */
        bdk_qlm_mode_flags_t    flags : 8;      /**< Mode flags */
        uint32_t                pcie : 1;       /**< Mode is PCIE RC or endpoint, see flags */
        uint32_t                sata : 1;       /**< Mode is SATA */
        uint32_t                cgx : 1;        /**< Mode is supported by CGX, see mode for details */
        uint32_t                reserved : 29;  /**< Reserved for future use */
    } s;
} bdk_qlm_state_lane_t;

/**
 * Converts a measured reference clock to a likely ideal value. Rounds
 * clock speed to the nearest REF_*Mhz define.
 *
 * @param node   Node to use in numa setup
 * @param qlm    Which QLM
 * @param measured_hz
 *               Measured value
 *
 * @return Value exactly matching a define
 */
extern int __bdk_qlm_round_refclock(bdk_node_t node, int qlm, int measured_hz);

/**
 * For EVB and EBB board, query the MCU to determine the QLM setup.
 * Applying any configuration found.
 *
 * @param node   Node to configure
 *
 * @return Zero on success, negative on failure
 */
extern int bdk_qlm_mcu_auto_config(bdk_node_t node);

/**
 * Build a structure representing the state of a GSER*. This is normally stored in
 * a scratch register inside GSER*.
 *
 * @param mode     Desired mode
 * @param baud_mhz Rate in MHz
 * @param flags    Optional flags
 *
 * @return State to store in scratch
 */
extern bdk_qlm_state_lane_t __bdk_qlm_build_state(bdk_qlm_modes_t mode, int baud_mhz, bdk_qlm_mode_flags_t flags);

#endif /* __BDK_QLM_COMMON_H__ */
