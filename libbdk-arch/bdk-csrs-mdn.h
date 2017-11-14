#ifndef __BDK_CSRS_MDN_H__
#define __BDK_CSRS_MDN_H__
/* This file is auto-generated. Do not edit */

/***********************license start***************
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

 *   * Neither the name of Cavium Inc. nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.

 * This Software, including technical data, may be subject to U.S. export  control
 * laws, including the U.S. Export Administration Act and its  associated
 * regulations, and may be subject to export or import  regulations in other
 * countries.

 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM  NETWORKS MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR
 * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/


/**
 * @file
 *
 * Configuration and status register (CSR) address and type definitions for
 * Cavium MDN.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration mdn_bist_status_e
 *
 * MDN BIST Status Enumeration
 * Enumerates MDN_BIST_STATUS[STATUS], which reports the state of the BIST state
 * machine.
 */
#define BDK_MDN_BIST_STATUS_E_ACTIVE (7)
#define BDK_MDN_BIST_STATUS_E_DONE_BIST_TIMEOUT (5)
#define BDK_MDN_BIST_STATUS_E_DONE_BUS_ERROR (4)
#define BDK_MDN_BIST_STATUS_E_DONE_FAIL (2)
#define BDK_MDN_BIST_STATUS_E_DONE_FAIL_NO_FUSES (3)
#define BDK_MDN_BIST_STATUS_E_DONE_PASS_CLEAN (0)
#define BDK_MDN_BIST_STATUS_E_DONE_PASS_REPAIRABLE (1)
#define BDK_MDN_BIST_STATUS_E_HALTED (6)

/**
 * Enumeration mdn_debug_algo_e
 *
 * MDN BIST Debug Algorithm Enumeration
 * Enumerates MDN_BIST_CONFIG[DEBUG_ALGO], which selects how defects are captured
 * for debug purposes.
 */
#define BDK_MDN_DEBUG_ALGO_E_DEFECT_CAPTURE_FIRST (0)
#define BDK_MDN_DEBUG_ALGO_E_DEFECT_CAPTURE_LAST (1)
#define BDK_MDN_DEBUG_ALGO_E_DEFECT_CAPTURE_MAX (2)
#define BDK_MDN_DEBUG_ALGO_E_DEFECT_CAPTURE_MIN (3)

/**
 * Enumeration mdn_debug_kind_e
 *
 * MDN BIST Debug Kind Enumeration
 * Enumerates MDN_BIST_CONFIG[DEBUG_KIND], which selects which defects are captured
 * for debug purposes.
 */
#define BDK_MDN_DEBUG_KIND_E_DEFECT_CAPTURE_COL (1)
#define BDK_MDN_DEBUG_KIND_E_DEFECT_CAPTURE_REP (2)
#define BDK_MDN_DEBUG_KIND_E_DEFECT_CAPTURE_ROW (0)

/**
 * Register (MDSB) mdn_bisr_repair
 *
 * MDN BISR Repair Register
 */
union bdk_mdn_bisr_repair
{
    uint32_t u;
    struct bdk_mdn_bisr_repair_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_17_31        : 15;
        uint32_t valid                 : 1;  /**< [ 16: 16](R/W) Set when [REPAIR] is valid. */
        uint32_t reserved_12_15        : 4;
        uint32_t repair                : 12; /**< [ 11:  0](R/W) BISR repair information. */
#else /* Word 0 - Little Endian */
        uint32_t repair                : 12; /**< [ 11:  0](R/W) BISR repair information. */
        uint32_t reserved_12_15        : 4;
        uint32_t valid                 : 1;  /**< [ 16: 16](R/W) Set when [REPAIR] is valid. */
        uint32_t reserved_17_31        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_bisr_repair_s cn; */
};
typedef union bdk_mdn_bisr_repair bdk_mdn_bisr_repair_t;

#define BDK_MDN_BISR_REPAIR BDK_MDN_BISR_REPAIR_FUNC()
static inline uint64_t BDK_MDN_BISR_REPAIR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_BISR_REPAIR_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x28;
    __bdk_csr_fatal("MDN_BISR_REPAIR", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_BISR_REPAIR bdk_mdn_bisr_repair_t
#define bustype_BDK_MDN_BISR_REPAIR BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_BISR_REPAIR "MDN_BISR_REPAIR"
#define busnum_BDK_MDN_BISR_REPAIR 0
#define arguments_BDK_MDN_BISR_REPAIR -1,-1,-1,-1

/**
 * Register (MDSB) mdn_bist_active
 *
 * INTERNAL: MDN BIST Active Status Register
 *
 * This register is a duplicate of MDN_BIST_STATUS that only responds to broadcast
 * reads when [ACTIVE] is asserted. This register should only be accessed by the MDC
 * root state machine.
 */
union bdk_mdn_bist_active
{
    uint32_t u;
    struct bdk_mdn_bist_active_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t hub_id                : 7;  /**< [ 31: 25](RO/H) Hub identifier. */
        uint32_t node_id               : 10; /**< [ 24: 15](RO/H) MDN identifier. */
        uint32_t repair                : 12; /**< [ 14:  3](RO/H) Asserted when BIST state machine detects a defective column. */
        uint32_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine. Enumerated by MDN_BIST_STATUS_E. */
#else /* Word 0 - Little Endian */
        uint32_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine. Enumerated by MDN_BIST_STATUS_E. */
        uint32_t repair                : 12; /**< [ 14:  3](RO/H) Asserted when BIST state machine detects a defective column. */
        uint32_t node_id               : 10; /**< [ 24: 15](RO/H) MDN identifier. */
        uint32_t hub_id                : 7;  /**< [ 31: 25](RO/H) Hub identifier. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_bist_active_s cn; */
};
typedef union bdk_mdn_bist_active bdk_mdn_bist_active_t;

#define BDK_MDN_BIST_ACTIVE BDK_MDN_BIST_ACTIVE_FUNC()
static inline uint64_t BDK_MDN_BIST_ACTIVE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_BIST_ACTIVE_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0xc;
    __bdk_csr_fatal("MDN_BIST_ACTIVE", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_BIST_ACTIVE bdk_mdn_bist_active_t
#define bustype_BDK_MDN_BIST_ACTIVE BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_BIST_ACTIVE "MDN_BIST_ACTIVE"
#define busnum_BDK_MDN_BIST_ACTIVE 0
#define arguments_BDK_MDN_BIST_ACTIVE -1,-1,-1,-1

/**
 * Register (MDSB) mdn_bist_addr_mask
 *
 * MDN BIST Start Mask Register
 */
union bdk_mdn_bist_addr_mask
{
    uint32_t u;
    struct bdk_mdn_bist_addr_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_7_31         : 25;
        uint32_t mdh_start_ratio       : 3;  /**< [  6:  4](R/W) Controls the number of MDNs that respond to a given start BIST command
                                                                 by controlling which of the command's hub_id address bits are used for the
                                                                 node's address decode.  For a node to respond to the start command the
                                                                 command's hub_id ANDed with the compare mask must match the node's hub_id
                                                                 ANDed with the compare mask.  Valid values are 0 through 7.  The MDC typcially
                                                                 programs this field with the contents of MDC_BIST_CONFIG[MDH_START_RATIO] prior to
                                                                 starting BIST.
                                                                   0x0 = Compare-mask is 0b000_0000; every MDH_ID matches (all bits are wild-cards).
                                                                   0x1 = Compare-mask is 0b000_0001; every 2nd MDH_ID matches (upper 6 bits are wild-cards).
                                                                   0x2 = Compare-mask is 0b000_0011; every 4th MDH_ID matches (upper 5 bits wild-cards).
                                                                   ...
                                                                   0x7 = Compare-mask is 0b111_1111; exact match (no bits are wild-cards). */
        uint32_t mdn_start_ratio       : 4;  /**< [  3:  0](R/W) Controls the number of MDNs that respond to a given start BIST command
                                                                 by controlling which of the command's node_id address bits are used for the
                                                                 node's address decode.  For a node to respond to the start command the
                                                                 command's node_id ANDed with the compare mask must match the node's node_id
                                                                 ANDed with the compare mask.  Valid values are 0 through 10.  The MDC typcially
                                                                 programs this field with the contents of MDC_BIST_CONFIG[MDN_START_RATIO] prior to
                                                                 starting BIST.
                                                                   0x0 = Compare mask is 0b00_000_0000; every MDH_ID matches (all bits are wild-cards).
                                                                   0x1 = Compare mask is 0b00_000_0001; every 2nd MDH_ID matches (upper 9 bits are wild-cards).
                                                                   0x2 = Compare mask is 0b00_000_0011; every 4th MDH_ID matches (upper 8 bits are wild-cards).
                                                                   ...
                                                                   0xA = Compare mask is 0b11_1111_1111; exact match (no bits are wild-cards). */
#else /* Word 0 - Little Endian */
        uint32_t mdn_start_ratio       : 4;  /**< [  3:  0](R/W) Controls the number of MDNs that respond to a given start BIST command
                                                                 by controlling which of the command's node_id address bits are used for the
                                                                 node's address decode.  For a node to respond to the start command the
                                                                 command's node_id ANDed with the compare mask must match the node's node_id
                                                                 ANDed with the compare mask.  Valid values are 0 through 10.  The MDC typcially
                                                                 programs this field with the contents of MDC_BIST_CONFIG[MDN_START_RATIO] prior to
                                                                 starting BIST.
                                                                   0x0 = Compare mask is 0b00_000_0000; every MDH_ID matches (all bits are wild-cards).
                                                                   0x1 = Compare mask is 0b00_000_0001; every 2nd MDH_ID matches (upper 9 bits are wild-cards).
                                                                   0x2 = Compare mask is 0b00_000_0011; every 4th MDH_ID matches (upper 8 bits are wild-cards).
                                                                   ...
                                                                   0xA = Compare mask is 0b11_1111_1111; exact match (no bits are wild-cards). */
        uint32_t mdh_start_ratio       : 3;  /**< [  6:  4](R/W) Controls the number of MDNs that respond to a given start BIST command
                                                                 by controlling which of the command's hub_id address bits are used for the
                                                                 node's address decode.  For a node to respond to the start command the
                                                                 command's hub_id ANDed with the compare mask must match the node's hub_id
                                                                 ANDed with the compare mask.  Valid values are 0 through 7.  The MDC typcially
                                                                 programs this field with the contents of MDC_BIST_CONFIG[MDH_START_RATIO] prior to
                                                                 starting BIST.
                                                                   0x0 = Compare-mask is 0b000_0000; every MDH_ID matches (all bits are wild-cards).
                                                                   0x1 = Compare-mask is 0b000_0001; every 2nd MDH_ID matches (upper 6 bits are wild-cards).
                                                                   0x2 = Compare-mask is 0b000_0011; every 4th MDH_ID matches (upper 5 bits wild-cards).
                                                                   ...
                                                                   0x7 = Compare-mask is 0b111_1111; exact match (no bits are wild-cards). */
        uint32_t reserved_7_31         : 25;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_bist_addr_mask_s cn; */
};
typedef union bdk_mdn_bist_addr_mask bdk_mdn_bist_addr_mask_t;

#define BDK_MDN_BIST_ADDR_MASK BDK_MDN_BIST_ADDR_MASK_FUNC()
static inline uint64_t BDK_MDN_BIST_ADDR_MASK_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_BIST_ADDR_MASK_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x4c;
    __bdk_csr_fatal("MDN_BIST_ADDR_MASK", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_BIST_ADDR_MASK bdk_mdn_bist_addr_mask_t
#define bustype_BDK_MDN_BIST_ADDR_MASK BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_BIST_ADDR_MASK "MDN_BIST_ADDR_MASK"
#define busnum_BDK_MDN_BIST_ADDR_MASK 0
#define arguments_BDK_MDN_BIST_ADDR_MASK -1,-1,-1,-1

/**
 * Register (MDSB) mdn_bist_config
 *
 * MDN Configuration Register
 */
union bdk_mdn_bist_config
{
    uint32_t u;
    struct bdk_mdn_bist_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_15_31        : 17;
        uint32_t debug_kind            : 2;  /**< [ 14: 13](R/W) Selects row or column defect capture for debug according to the
                                                                 MDN_DEBUG_KIND_E enumeration. */
        uint32_t debug_algo            : 2;  /**< [ 12: 11](R/W) Selects the algorithm used to capture defects for debug according to the
                                                                 MDN_DEBUG_ALGO_E enumeration. */
        uint32_t continuous_enable     : 1;  /**< [ 10: 10](R/W) Run BIST continuously until turned off.  Use extreme caution when
                                                                 running in this mode as BIST can draw a lot of power. */
        uint32_t halt_enable           : 1;  /**< [  9:  9](R/W) BIST halt mode enable. When set, the BIST state machine will run until a defect
                                                                 is detected; then it will halt. If no defect is detected, the BIST state machine
                                                                 will run until it has finished and remove MDN_BIST_STATUS[STATUS] being
                                                                 MDN_BIST_STATUS_E::ACTIVE if a defect is detected, it will assert set
                                                                 MDN_BIST_STATUS[STATUS] to MDN_BIST_STATUS_E::HALTED and stop executing
                                                                 BIST. The BIST state machine can be restarted at the next location in its march
                                                                 by writing one to MDN_BIST_CONTROL[START]. */
        uint32_t broadcast_disable     : 1;  /**< [  8:  8](R/W) Broadcast start BIST disable.  When set, disables the BIST state
                                                                 machine performing BIST upon a broadcast write of one to
                                                                 MDN_BIST_CONTROL[START].
                                                                 Arbitrary sets of memories can be specified to run BIST by setting
                                                                 or clearing this bit in all memories. */
        uint32_t march_disable         : 8;  /**< [  7:  0](R/W) BIST march disable.  BIST can execute up to eight march patterns.  This
                                                                 8-bit vector controls which marches are disabled.  When a bit in the
                                                                 vector is cleared to zero, the associated march is enabled.  When a bit
                                                                 in the vector is set to one the associated march is disabled.  Marches
                                                                 7 through 4 are the retention patterns and are disabled by default.
                                                                 The marches execute from 7 down to 0.  The marches include:
                                                                   7: Checkerboard write.
                                                                   6: Checkerboard read and compare.
                                                                   5: Inverse checkerboard write.
                                                                   4: Inverse checkerboard read and compare.
                                                                   3: Checkerboard.
                                                                   2: MD2.
                                                                   1: Read-hammer, binary-CAM or ternary-CAM.
                                                                   0: Clear. */
#else /* Word 0 - Little Endian */
        uint32_t march_disable         : 8;  /**< [  7:  0](R/W) BIST march disable.  BIST can execute up to eight march patterns.  This
                                                                 8-bit vector controls which marches are disabled.  When a bit in the
                                                                 vector is cleared to zero, the associated march is enabled.  When a bit
                                                                 in the vector is set to one the associated march is disabled.  Marches
                                                                 7 through 4 are the retention patterns and are disabled by default.
                                                                 The marches execute from 7 down to 0.  The marches include:
                                                                   7: Checkerboard write.
                                                                   6: Checkerboard read and compare.
                                                                   5: Inverse checkerboard write.
                                                                   4: Inverse checkerboard read and compare.
                                                                   3: Checkerboard.
                                                                   2: MD2.
                                                                   1: Read-hammer, binary-CAM or ternary-CAM.
                                                                   0: Clear. */
        uint32_t broadcast_disable     : 1;  /**< [  8:  8](R/W) Broadcast start BIST disable.  When set, disables the BIST state
                                                                 machine performing BIST upon a broadcast write of one to
                                                                 MDN_BIST_CONTROL[START].
                                                                 Arbitrary sets of memories can be specified to run BIST by setting
                                                                 or clearing this bit in all memories. */
        uint32_t halt_enable           : 1;  /**< [  9:  9](R/W) BIST halt mode enable. When set, the BIST state machine will run until a defect
                                                                 is detected; then it will halt. If no defect is detected, the BIST state machine
                                                                 will run until it has finished and remove MDN_BIST_STATUS[STATUS] being
                                                                 MDN_BIST_STATUS_E::ACTIVE if a defect is detected, it will assert set
                                                                 MDN_BIST_STATUS[STATUS] to MDN_BIST_STATUS_E::HALTED and stop executing
                                                                 BIST. The BIST state machine can be restarted at the next location in its march
                                                                 by writing one to MDN_BIST_CONTROL[START]. */
        uint32_t continuous_enable     : 1;  /**< [ 10: 10](R/W) Run BIST continuously until turned off.  Use extreme caution when
                                                                 running in this mode as BIST can draw a lot of power. */
        uint32_t debug_algo            : 2;  /**< [ 12: 11](R/W) Selects the algorithm used to capture defects for debug according to the
                                                                 MDN_DEBUG_ALGO_E enumeration. */
        uint32_t debug_kind            : 2;  /**< [ 14: 13](R/W) Selects row or column defect capture for debug according to the
                                                                 MDN_DEBUG_KIND_E enumeration. */
        uint32_t reserved_15_31        : 17;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_bist_config_s cn; */
};
typedef union bdk_mdn_bist_config bdk_mdn_bist_config_t;

#define BDK_MDN_BIST_CONFIG BDK_MDN_BIST_CONFIG_FUNC()
static inline uint64_t BDK_MDN_BIST_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_BIST_CONFIG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0;
    __bdk_csr_fatal("MDN_BIST_CONFIG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_BIST_CONFIG bdk_mdn_bist_config_t
#define bustype_BDK_MDN_BIST_CONFIG BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_BIST_CONFIG "MDN_BIST_CONFIG"
#define busnum_BDK_MDN_BIST_CONFIG 0
#define arguments_BDK_MDN_BIST_CONFIG -1,-1,-1,-1

/**
 * Register (MDSB) mdn_bist_control
 *
 * MDN Configuration Register
 */
union bdk_mdn_bist_control
{
    uint32_t u;
    struct bdk_mdn_bist_control_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t start                 : 1;  /**< [ 31: 31](R/W1) Starts or restarts the BIST state machine.  If the BIST state machine
                                                                 is idle, writing one will start it executing the first enabled march
                                                                 according to the MDN_BIST_CONFIG[MARCH_DISABLE] vector.  If the BIST
                                                                 state machine is halted due to detecting a defect while
                                                                 MDN_BIST_CONFIG[HALT_ENABLE] is asserted, then writing one will
                                                                 restart it executing at the next enabled march element. */
        uint32_t clear                 : 1;  /**< [ 30: 30](R/W1) When asserted with [START], the BIST SM will execute the clear BIST operation. */
        uint32_t read                  : 1;  /**< [ 29: 29](R/W1) The BIST SM will perform a debug read using the specified REP and ADDRESS
                                                                 when START and READ are asserted simultaneously.  Asserting READ without
                                                                 START has no effect.  The BIST status will change to ACTIVE while the
                                                                 read occurs and then change to DONE_* when the read data is available
                                                                 via MDN_DEBUG_DATA().  Note that the BIST status may be any flavor of
                                                                 DONE_\<FAIL,REPAIRABLE,PASS\> but it simply means that the debug read
                                                                 has completed. */
        uint32_t reset                 : 1;  /**< [ 28: 28](R/W1) Resets the BIST state machine and sets MDN_BIST_STATUS[STATUS] back to
                                                                 MDN_BIST_STATUS_E::DONE_PASS_CLEAN. */
        uint32_t reserved_23_27        : 5;
        uint32_t one_rep               : 1;  /**< [ 22: 22](R/W1) When set to one, the BIST state machine performs BIST only upon the REP
                                                                 specified below.  When cleared to zero, the BIST state machine performs
                                                                 BIST starting at the [REP] specified which may include multiple REPs. */
        uint32_t rep                   : 8;  /**< [ 21: 14](R/W1) When the READ field aboe is asserted this specifies the repetition
                                                                 used for a debug read.  When the [START] field is asserted this
                                                                 specifies repetition that BIST will start with.  Note that any value
                                                                 of REP can be used while halted; however, it must be set back to the
                                                                 value of MDN_DEBUG_MARCH[MARCH_REP] before restarting to continue the
                                                                 march. */
        uint32_t address               : 14; /**< [ 13:  0](R/W1) The address used for a debug read when [READ] is asserted.  This
                                                                 field must be written as zeros when starting or re-starting BIST. */
#else /* Word 0 - Little Endian */
        uint32_t address               : 14; /**< [ 13:  0](R/W1) The address used for a debug read when [READ] is asserted.  This
                                                                 field must be written as zeros when starting or re-starting BIST. */
        uint32_t rep                   : 8;  /**< [ 21: 14](R/W1) When the READ field aboe is asserted this specifies the repetition
                                                                 used for a debug read.  When the [START] field is asserted this
                                                                 specifies repetition that BIST will start with.  Note that any value
                                                                 of REP can be used while halted; however, it must be set back to the
                                                                 value of MDN_DEBUG_MARCH[MARCH_REP] before restarting to continue the
                                                                 march. */
        uint32_t one_rep               : 1;  /**< [ 22: 22](R/W1) When set to one, the BIST state machine performs BIST only upon the REP
                                                                 specified below.  When cleared to zero, the BIST state machine performs
                                                                 BIST starting at the [REP] specified which may include multiple REPs. */
        uint32_t reserved_23_27        : 5;
        uint32_t reset                 : 1;  /**< [ 28: 28](R/W1) Resets the BIST state machine and sets MDN_BIST_STATUS[STATUS] back to
                                                                 MDN_BIST_STATUS_E::DONE_PASS_CLEAN. */
        uint32_t read                  : 1;  /**< [ 29: 29](R/W1) The BIST SM will perform a debug read using the specified REP and ADDRESS
                                                                 when START and READ are asserted simultaneously.  Asserting READ without
                                                                 START has no effect.  The BIST status will change to ACTIVE while the
                                                                 read occurs and then change to DONE_* when the read data is available
                                                                 via MDN_DEBUG_DATA().  Note that the BIST status may be any flavor of
                                                                 DONE_\<FAIL,REPAIRABLE,PASS\> but it simply means that the debug read
                                                                 has completed. */
        uint32_t clear                 : 1;  /**< [ 30: 30](R/W1) When asserted with [START], the BIST SM will execute the clear BIST operation. */
        uint32_t start                 : 1;  /**< [ 31: 31](R/W1) Starts or restarts the BIST state machine.  If the BIST state machine
                                                                 is idle, writing one will start it executing the first enabled march
                                                                 according to the MDN_BIST_CONFIG[MARCH_DISABLE] vector.  If the BIST
                                                                 state machine is halted due to detecting a defect while
                                                                 MDN_BIST_CONFIG[HALT_ENABLE] is asserted, then writing one will
                                                                 restart it executing at the next enabled march element. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_bist_control_s cn; */
};
typedef union bdk_mdn_bist_control bdk_mdn_bist_control_t;

#define BDK_MDN_BIST_CONTROL BDK_MDN_BIST_CONTROL_FUNC()
static inline uint64_t BDK_MDN_BIST_CONTROL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_BIST_CONTROL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 4;
    __bdk_csr_fatal("MDN_BIST_CONTROL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_BIST_CONTROL bdk_mdn_bist_control_t
#define bustype_BDK_MDN_BIST_CONTROL BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_BIST_CONTROL "MDN_BIST_CONTROL"
#define busnum_BDK_MDN_BIST_CONTROL 0
#define arguments_BDK_MDN_BIST_CONTROL -1,-1,-1,-1

/**
 * Register (MDSB) mdn_bist_fail
 *
 * INTERNAL: MDN BIST Fail Status Register
 *
 * This register is a duplicate of MDN_BIST_STATUS that only responds to broadcast
 * reads when [FAIL] is asserted. This register should only be accessed by the MDC root
 * state machine.
 */
union bdk_mdn_bist_fail
{
    uint32_t u;
    struct bdk_mdn_bist_fail_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t hub_id                : 7;  /**< [ 31: 25](RO/H) Hub identifier. */
        uint32_t node_id               : 10; /**< [ 24: 15](RO/H) MDN identifier. */
        uint32_t repair                : 12; /**< [ 14:  3](RO/H) Asserted when BIST state machine detects a defective column. */
        uint32_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine. Enumerated by MDN_BIST_STATUS_E. */
#else /* Word 0 - Little Endian */
        uint32_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine. Enumerated by MDN_BIST_STATUS_E. */
        uint32_t repair                : 12; /**< [ 14:  3](RO/H) Asserted when BIST state machine detects a defective column. */
        uint32_t node_id               : 10; /**< [ 24: 15](RO/H) MDN identifier. */
        uint32_t hub_id                : 7;  /**< [ 31: 25](RO/H) Hub identifier. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_bist_fail_s cn; */
};
typedef union bdk_mdn_bist_fail bdk_mdn_bist_fail_t;

#define BDK_MDN_BIST_FAIL BDK_MDN_BIST_FAIL_FUNC()
static inline uint64_t BDK_MDN_BIST_FAIL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_BIST_FAIL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x10;
    __bdk_csr_fatal("MDN_BIST_FAIL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_BIST_FAIL bdk_mdn_bist_fail_t
#define bustype_BDK_MDN_BIST_FAIL BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_BIST_FAIL "MDN_BIST_FAIL"
#define busnum_BDK_MDN_BIST_FAIL 0
#define arguments_BDK_MDN_BIST_FAIL -1,-1,-1,-1

/**
 * Register (MDSB) mdn_bist_repairable
 *
 * INTERNAL: MDN BIST Repairable Status Register
 *
 * This register is a duplicate of MDN_BIST_STATUS that only responds to broadcast
 * reads when [REPAIRABLE] is asserted. This register should only be accessed by the
 * MDC root state machine.
 */
union bdk_mdn_bist_repairable
{
    uint32_t u;
    struct bdk_mdn_bist_repairable_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t hub_id                : 7;  /**< [ 31: 25](RO/H) Hub identifier. */
        uint32_t node_id               : 10; /**< [ 24: 15](RO/H) MDN identifier. */
        uint32_t repair                : 12; /**< [ 14:  3](RO/H) Asserted when BIST state machine detects a defective column. */
        uint32_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine. Enumerated by MDN_BIST_STATUS_E. */
#else /* Word 0 - Little Endian */
        uint32_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine. Enumerated by MDN_BIST_STATUS_E. */
        uint32_t repair                : 12; /**< [ 14:  3](RO/H) Asserted when BIST state machine detects a defective column. */
        uint32_t node_id               : 10; /**< [ 24: 15](RO/H) MDN identifier. */
        uint32_t hub_id                : 7;  /**< [ 31: 25](RO/H) Hub identifier. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_bist_repairable_s cn; */
};
typedef union bdk_mdn_bist_repairable bdk_mdn_bist_repairable_t;

#define BDK_MDN_BIST_REPAIRABLE BDK_MDN_BIST_REPAIRABLE_FUNC()
static inline uint64_t BDK_MDN_BIST_REPAIRABLE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_BIST_REPAIRABLE_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x14;
    __bdk_csr_fatal("MDN_BIST_REPAIRABLE", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_BIST_REPAIRABLE bdk_mdn_bist_repairable_t
#define bustype_BDK_MDN_BIST_REPAIRABLE BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_BIST_REPAIRABLE "MDN_BIST_REPAIRABLE"
#define busnum_BDK_MDN_BIST_REPAIRABLE 0
#define arguments_BDK_MDN_BIST_REPAIRABLE -1,-1,-1,-1

/**
 * Register (MDSB) mdn_bist_status
 *
 * MDN BIST Status Register
 */
union bdk_mdn_bist_status
{
    uint32_t u;
    struct bdk_mdn_bist_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t hub_id                : 7;  /**< [ 31: 25](RO/H) Hub identifier. */
        uint32_t node_id               : 10; /**< [ 24: 15](RO/H) MDN identifier. */
        uint32_t repair                : 12; /**< [ 14:  3](RO/H) Asserted when BIST state machine detects a defective column. */
        uint32_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine. Enumerated by MDN_BIST_STATUS_E. */
#else /* Word 0 - Little Endian */
        uint32_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine. Enumerated by MDN_BIST_STATUS_E. */
        uint32_t repair                : 12; /**< [ 14:  3](RO/H) Asserted when BIST state machine detects a defective column. */
        uint32_t node_id               : 10; /**< [ 24: 15](RO/H) MDN identifier. */
        uint32_t hub_id                : 7;  /**< [ 31: 25](RO/H) Hub identifier. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_bist_status_s cn; */
};
typedef union bdk_mdn_bist_status bdk_mdn_bist_status_t;

#define BDK_MDN_BIST_STATUS BDK_MDN_BIST_STATUS_FUNC()
static inline uint64_t BDK_MDN_BIST_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_BIST_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 8;
    __bdk_csr_fatal("MDN_BIST_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_BIST_STATUS bdk_mdn_bist_status_t
#define bustype_BDK_MDN_BIST_STATUS BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_BIST_STATUS "MDN_BIST_STATUS"
#define busnum_BDK_MDN_BIST_STATUS 0
#define arguments_BDK_MDN_BIST_STATUS -1,-1,-1,-1

/**
 * Register (MDSB) mdn_const
 *
 * MDN Constants Register
 * This register has constants pertaining to this node for software discovery.
 * See also MDC_RAS_ROM().
 */
union bdk_mdn_const
{
    uint32_t u;
    struct bdk_mdn_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_30_31        : 2;
        uint32_t virt                  : 1;  /**< [ 29: 29](RO) Asserted when this MDN is virtual. */
        uint32_t debug_read            : 1;  /**< [ 28: 28](RO) Asserted when this MDN has debug read capability via MDN_BIST_CONTROL and MDN_DEBUG_DATA(). */
        uint32_t ecc                   : 1;  /**< [ 27: 27](RO) Asserted when this MDH is capable or reporting ECC or parity error events. */
        uint32_t bisr                  : 1;  /**< [ 26: 26](RO) Asserted when BISR capable. */
        uint32_t bist                  : 1;  /**< [ 25: 25](RO) Asserted when BIST capable. */
        uint32_t rows                  : 14; /**< [ 24: 11](RO) Number of rows minus 1 in the SRAM or CAM (16K max). */
        uint32_t cols                  : 11; /**< [ 10:  0](RO) Number of columns minus 1 (data BIST) in the SRAM or CAM (2K max).
                                                                 The value includes any redundant bits for repair.  For multi-port RAMs
                                                                 the value is the sum of all data bits across all ports minus 1.  Thus
                                                                 a 20-bit 2RW RAM with BISR will have a value of (2 x (20 + 1)) - 1 = 41
                                                                 for 2 ports of 21 bits (including repair) minus 1. */
#else /* Word 0 - Little Endian */
        uint32_t cols                  : 11; /**< [ 10:  0](RO) Number of columns minus 1 (data BIST) in the SRAM or CAM (2K max).
                                                                 The value includes any redundant bits for repair.  For multi-port RAMs
                                                                 the value is the sum of all data bits across all ports minus 1.  Thus
                                                                 a 20-bit 2RW RAM with BISR will have a value of (2 x (20 + 1)) - 1 = 41
                                                                 for 2 ports of 21 bits (including repair) minus 1. */
        uint32_t rows                  : 14; /**< [ 24: 11](RO) Number of rows minus 1 in the SRAM or CAM (16K max). */
        uint32_t bist                  : 1;  /**< [ 25: 25](RO) Asserted when BIST capable. */
        uint32_t bisr                  : 1;  /**< [ 26: 26](RO) Asserted when BISR capable. */
        uint32_t ecc                   : 1;  /**< [ 27: 27](RO) Asserted when this MDH is capable or reporting ECC or parity error events. */
        uint32_t debug_read            : 1;  /**< [ 28: 28](RO) Asserted when this MDN has debug read capability via MDN_BIST_CONTROL and MDN_DEBUG_DATA(). */
        uint32_t virt                  : 1;  /**< [ 29: 29](RO) Asserted when this MDN is virtual. */
        uint32_t reserved_30_31        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_const_s cn; */
};
typedef union bdk_mdn_const bdk_mdn_const_t;

#define BDK_MDN_CONST BDK_MDN_CONST_FUNC()
static inline uint64_t BDK_MDN_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_CONST_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x40;
    __bdk_csr_fatal("MDN_CONST", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_CONST bdk_mdn_const_t
#define bustype_BDK_MDN_CONST BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_CONST "MDN_CONST"
#define busnum_BDK_MDN_CONST 0
#define arguments_BDK_MDN_CONST -1,-1,-1,-1

/**
 * Register (MDSB) mdn_debug_data#
 *
 * MDN Debug Data Register
 */
union bdk_mdn_debug_datax
{
    uint32_t u;
    struct bdk_mdn_debug_datax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO/H) Read data according associated with a debug read issued via
                                                                 MDN_BIST_CONTROL[READ, REP and ADDRESS]. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO/H) Read data according associated with a debug read issued via
                                                                 MDN_BIST_CONTROL[READ, REP and ADDRESS]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_debug_datax_s cn; */
};
typedef union bdk_mdn_debug_datax bdk_mdn_debug_datax_t;

static inline uint64_t BDK_MDN_DEBUG_DATAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_DEBUG_DATAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=31))
        return 0x80 + 4 * ((a) & 0x1f);
    __bdk_csr_fatal("MDN_DEBUG_DATAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_MDN_DEBUG_DATAX(a) bdk_mdn_debug_datax_t
#define bustype_BDK_MDN_DEBUG_DATAX(a) BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_DEBUG_DATAX(a) "MDN_DEBUG_DATAX"
#define busnum_BDK_MDN_DEBUG_DATAX(a) (a)
#define arguments_BDK_MDN_DEBUG_DATAX(a) (a),-1,-1,-1

/**
 * Register (MDSB) mdn_debug_defect
 *
 * MDN BIST Debug Register
 * This register contains information about the most recently detected defect.
 * When MDN_BIST_CONFIG[HALT_ENABLE] is asserted this register will maintain
 * its value when the BIST state machine halts; otherwise, the value of this
 * register may change multiple times during a given BIST run.
 */
union bdk_mdn_debug_defect
{
    uint32_t u;
    struct bdk_mdn_debug_defect_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sm_latency            : 8;  /**< [ 31: 24](RO) Read latency in clock cycles.  This reports the depth of the MDN_DEBUG_SKID[SKID]
                                                                 buffer and the clock differential in MDN_DEBUG_MARCH. */
        uint32_t reserved_21_23        : 3;
        uint32_t other                 : 1;  /**< [ 20: 20](RO/H) Asserted for special-case defects.  For NPC TCAM this is asserted when more than
                                                                 one "way" has a defect. */
        uint32_t cam_valid_bit_fail    : 1;  /**< [ 19: 19](RO/H) Asserted if BIST detects an error with CAM entry valid bit.  A CAM
                                                                 entry valid bit is read/writeable and determines whether or not the
                                                                 entry participate in CAM operations.  CAM entry valid bits are not
                                                                 repairable. */
        uint32_t cam_hit_index_fail    : 1;  /**< [ 18: 18](RO/H) Asserted if BIST detects a CAM hit index error.  For certain CAM
                                                                 operations the CAM hit index must match the index of the single
                                                                 matching CAM entry. */
        uint32_t cam_multi_hit_fail    : 1;  /**< [ 17: 17](RO/H) Asserted if BIST detects a CAM multi-hit error.  A multi-hit
                                                                 indication is supposed to fire if multiple entries match
                                                                 during a CAM operation. */
        uint32_t cam_hit_fail          : 1;  /**< [ 16: 16](RO/H) Asserted if BIST detects a CAM hit index error.  The CAM signals
                                                                 a hit if an entry in the CAM matches during a CAM operation. */
        uint32_t multi_col_fail        : 1;  /**< [ 15: 15](RO/H) Asserted if BIST detects multiple failing columns in the same row
                                                                 of a CAM or RAM. */
        uint32_t valid                 : 1;  /**< [ 14: 14](RO/H) The [DEFECT] field is valid. */
        uint32_t defect                : 14; /**< [ 13:  0](RO/H) The maximum, minimum, first or last defect row or column is captured here
                                                                 according to the setting of MDN_BIST_CONFIG[DEBUG_KIND] and MDN_BIST_CONFIG[DEBUG_ALGO]. */
#else /* Word 0 - Little Endian */
        uint32_t defect                : 14; /**< [ 13:  0](RO/H) The maximum, minimum, first or last defect row or column is captured here
                                                                 according to the setting of MDN_BIST_CONFIG[DEBUG_KIND] and MDN_BIST_CONFIG[DEBUG_ALGO]. */
        uint32_t valid                 : 1;  /**< [ 14: 14](RO/H) The [DEFECT] field is valid. */
        uint32_t multi_col_fail        : 1;  /**< [ 15: 15](RO/H) Asserted if BIST detects multiple failing columns in the same row
                                                                 of a CAM or RAM. */
        uint32_t cam_hit_fail          : 1;  /**< [ 16: 16](RO/H) Asserted if BIST detects a CAM hit index error.  The CAM signals
                                                                 a hit if an entry in the CAM matches during a CAM operation. */
        uint32_t cam_multi_hit_fail    : 1;  /**< [ 17: 17](RO/H) Asserted if BIST detects a CAM multi-hit error.  A multi-hit
                                                                 indication is supposed to fire if multiple entries match
                                                                 during a CAM operation. */
        uint32_t cam_hit_index_fail    : 1;  /**< [ 18: 18](RO/H) Asserted if BIST detects a CAM hit index error.  For certain CAM
                                                                 operations the CAM hit index must match the index of the single
                                                                 matching CAM entry. */
        uint32_t cam_valid_bit_fail    : 1;  /**< [ 19: 19](RO/H) Asserted if BIST detects an error with CAM entry valid bit.  A CAM
                                                                 entry valid bit is read/writeable and determines whether or not the
                                                                 entry participate in CAM operations.  CAM entry valid bits are not
                                                                 repairable. */
        uint32_t other                 : 1;  /**< [ 20: 20](RO/H) Asserted for special-case defects.  For NPC TCAM this is asserted when more than
                                                                 one "way" has a defect. */
        uint32_t reserved_21_23        : 3;
        uint32_t sm_latency            : 8;  /**< [ 31: 24](RO) Read latency in clock cycles.  This reports the depth of the MDN_DEBUG_SKID[SKID]
                                                                 buffer and the clock differential in MDN_DEBUG_MARCH. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_debug_defect_s cn; */
};
typedef union bdk_mdn_debug_defect bdk_mdn_debug_defect_t;

#define BDK_MDN_DEBUG_DEFECT BDK_MDN_DEBUG_DEFECT_FUNC()
static inline uint64_t BDK_MDN_DEBUG_DEFECT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_DEBUG_DEFECT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x1c;
    __bdk_csr_fatal("MDN_DEBUG_DEFECT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_DEBUG_DEFECT bdk_mdn_debug_defect_t
#define bustype_BDK_MDN_DEBUG_DEFECT BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_DEBUG_DEFECT "MDN_DEBUG_DEFECT"
#define busnum_BDK_MDN_DEBUG_DEFECT 0
#define arguments_BDK_MDN_DEBUG_DEFECT -1,-1,-1,-1

/**
 * Register (MDSB) mdn_debug_march
 *
 * MDN BIST Debug March Register
 * When MDN_BIST_CONFIG[HALT_ENABLE] is asserted this register contains
 * information about the most recently detected defect. All the fields in
 * this CSR get their values from state variables in the BIST state machine.
 * Due to the state machine's pipelining these values will be ahead of those
 * corresponding to the actual defect according to the number of clock cycles
 * of the RAM/CAM's read latency.
 */
union bdk_mdn_debug_march
{
    uint32_t u;
    struct bdk_mdn_debug_march_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data_index            : 12; /**< [ 31: 20](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports the
                                                                 value of the data bit index used when the BIST state machine halted.
                                                                 The data bit index is used to walk zeros or ones for testing CAM operation. */
        uint32_t march_rep             : 8;  /**< [ 19: 12](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports what
                                                                 BIST state machine repetition was halted upon.  The BIST state machine
                                                                 performs multiple repetitions for certain RAMs.  A typical usage of
                                                                 repetitions is to test the ports of a multi-port RAM. */
        uint32_t march_sel             : 4;  /**< [ 11:  8](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports
                                                                 the march that BIST state machine halted in.  This field has the
                                                                 same format as the MDN_BIST_CONFIG[MARCH_DISABLE] vector. */
        uint32_t march_row             : 3;  /**< [  7:  5](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports
                                                                 the row in the march array that the BIST state machine halted upon. */
        uint32_t march_col             : 5;  /**< [  4:  0](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports
                                                                 the column in the march array that the BIST state machine halted upon. */
#else /* Word 0 - Little Endian */
        uint32_t march_col             : 5;  /**< [  4:  0](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports
                                                                 the column in the march array that the BIST state machine halted upon. */
        uint32_t march_row             : 3;  /**< [  7:  5](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports
                                                                 the row in the march array that the BIST state machine halted upon. */
        uint32_t march_sel             : 4;  /**< [ 11:  8](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports
                                                                 the march that BIST state machine halted in.  This field has the
                                                                 same format as the MDN_BIST_CONFIG[MARCH_DISABLE] vector. */
        uint32_t march_rep             : 8;  /**< [ 19: 12](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports what
                                                                 BIST state machine repetition was halted upon.  The BIST state machine
                                                                 performs multiple repetitions for certain RAMs.  A typical usage of
                                                                 repetitions is to test the ports of a multi-port RAM. */
        uint32_t data_index            : 12; /**< [ 31: 20](RO/H) When MDN_BIST_CONFIG[HALT_ENABLE] is asserted, this field reports the
                                                                 value of the data bit index used when the BIST state machine halted.
                                                                 The data bit index is used to walk zeros or ones for testing CAM operation. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_debug_march_s cn; */
};
typedef union bdk_mdn_debug_march bdk_mdn_debug_march_t;

#define BDK_MDN_DEBUG_MARCH BDK_MDN_DEBUG_MARCH_FUNC()
static inline uint64_t BDK_MDN_DEBUG_MARCH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_DEBUG_MARCH_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x20;
    __bdk_csr_fatal("MDN_DEBUG_MARCH", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_DEBUG_MARCH bdk_mdn_debug_march_t
#define bustype_BDK_MDN_DEBUG_MARCH BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_DEBUG_MARCH "MDN_DEBUG_MARCH"
#define busnum_BDK_MDN_DEBUG_MARCH 0
#define arguments_BDK_MDN_DEBUG_MARCH -1,-1,-1,-1

/**
 * Register (MDSB) mdn_debug_skid
 *
 * MDN BIST Debug Skid Register
 * When MDN_BIST_CONFIG[HALT_ENABLE] is asserted this register contains
 * information about the most recently detected defects.  Since the BIST SM
 * is a pipelined design, when a defect is detected, and the BIST SM halted,
 * there will be some number of BIST operations still in flight.  For example,
 * in some of the custom BIST implementations in the AP core, there can be 16
 * or more operations in flight when a defect is detected.  The SKID field
 * records whether or not any additional defects were found in those in-flight
 * operations.
 */
union bdk_mdn_debug_skid
{
    uint32_t u;
    struct bdk_mdn_debug_skid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t skid                  : 32; /**< [ 31:  0](RO/H) Skid FIFO for defect detection.  0:no defect, 1:defect
                                                                 Each bit corresponds to a clock-cycle pipeline delay from the time
                                                                 BIST SM was halted due to a defect detection.  Bit 0 corresponds to
                                                                 the clock-cycle of the halt plus 1, bit 1 = halt + 2 cycles, etc. */
#else /* Word 0 - Little Endian */
        uint32_t skid                  : 32; /**< [ 31:  0](RO/H) Skid FIFO for defect detection.  0:no defect, 1:defect
                                                                 Each bit corresponds to a clock-cycle pipeline delay from the time
                                                                 BIST SM was halted due to a defect detection.  Bit 0 corresponds to
                                                                 the clock-cycle of the halt plus 1, bit 1 = halt + 2 cycles, etc. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_debug_skid_s cn; */
};
typedef union bdk_mdn_debug_skid bdk_mdn_debug_skid_t;

#define BDK_MDN_DEBUG_SKID BDK_MDN_DEBUG_SKID_FUNC()
static inline uint64_t BDK_MDN_DEBUG_SKID_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_DEBUG_SKID_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x24;
    __bdk_csr_fatal("MDN_DEBUG_SKID", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_DEBUG_SKID bdk_mdn_debug_skid_t
#define bustype_BDK_MDN_DEBUG_SKID BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_DEBUG_SKID "MDN_DEBUG_SKID"
#define busnum_BDK_MDN_DEBUG_SKID 0
#define arguments_BDK_MDN_DEBUG_SKID -1,-1,-1,-1

/**
 * Register (MDSB) mdn_ecc_config
 *
 * MDN Configuration Register
 */
union bdk_mdn_ecc_config
{
    uint32_t u;
    struct bdk_mdn_ecc_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_5_31         : 27;
        uint32_t disable_dbe           : 1;  /**< [  4:  4](R/W) Disables this node from responding to broadcast reads of
                                                                 MDN_ECC_STATUS due to double-bit/uncorrectable error reporting.
                                                                 Overriden when [CORRECTION_DISABLE] is asserted. */
        uint32_t disable_sbe           : 1;  /**< [  3:  3](R/W) Disables this node from responding to broadcast reads of
                                                                 MDN_ECC_STATUS due to single-bit/correctable error reporting.
                                                                 Overriden when [CORRECTION_DISABLE] is asserted. */
        uint32_t error_inject          : 2;  /**< [  2:  1](R/W) This 2-bit field provides diagnostic ECC error injection by flipping
                                                                 the least significant two bits of the write path's ECC code.  This bit
                                                                 flipping is done for all writes while the field is asserted.
                                                                 Asserting a single bit causes a single bit ECC error and asserting
                                                                 both bits causes a double-bit ECC error. Typically this diagnostic
                                                                 mode is used in combination with MDN_ECC_CONFIG[CORRECTION_DISABLE].
                                                                 In this manner ECC errors are injected, triggering upstream events
                                                                 like ECC error interrupts and status capture, without corrupting the
                                                                 data.

                                                                 Internal:
                                                                 Prior to mg2 this was implemented via the csr_flip_synd port. */
        uint32_t correction_disable    : 1;  /**< [  0:  0](R/W) This field disables ECC error correction by ignoring the ECC code
                                                                 associated with the data.  Typically it is used in conjunction with
                                                                 MDN_ECC_CONFIG[ERROR_INJECT] above.  This also disables the reporting
                                                                 of single and double-bit ECC errors and overrides the [DISABLE_SBE] and
                                                                 [DISABLE_DBE] controls.

                                                                 Internal:
                                                                 Prior to mg2 this was implemented via the csr_cor_dis port. */
#else /* Word 0 - Little Endian */
        uint32_t correction_disable    : 1;  /**< [  0:  0](R/W) This field disables ECC error correction by ignoring the ECC code
                                                                 associated with the data.  Typically it is used in conjunction with
                                                                 MDN_ECC_CONFIG[ERROR_INJECT] above.  This also disables the reporting
                                                                 of single and double-bit ECC errors and overrides the [DISABLE_SBE] and
                                                                 [DISABLE_DBE] controls.

                                                                 Internal:
                                                                 Prior to mg2 this was implemented via the csr_cor_dis port. */
        uint32_t error_inject          : 2;  /**< [  2:  1](R/W) This 2-bit field provides diagnostic ECC error injection by flipping
                                                                 the least significant two bits of the write path's ECC code.  This bit
                                                                 flipping is done for all writes while the field is asserted.
                                                                 Asserting a single bit causes a single bit ECC error and asserting
                                                                 both bits causes a double-bit ECC error. Typically this diagnostic
                                                                 mode is used in combination with MDN_ECC_CONFIG[CORRECTION_DISABLE].
                                                                 In this manner ECC errors are injected, triggering upstream events
                                                                 like ECC error interrupts and status capture, without corrupting the
                                                                 data.

                                                                 Internal:
                                                                 Prior to mg2 this was implemented via the csr_flip_synd port. */
        uint32_t disable_sbe           : 1;  /**< [  3:  3](R/W) Disables this node from responding to broadcast reads of
                                                                 MDN_ECC_STATUS due to single-bit/correctable error reporting.
                                                                 Overriden when [CORRECTION_DISABLE] is asserted. */
        uint32_t disable_dbe           : 1;  /**< [  4:  4](R/W) Disables this node from responding to broadcast reads of
                                                                 MDN_ECC_STATUS due to double-bit/uncorrectable error reporting.
                                                                 Overriden when [CORRECTION_DISABLE] is asserted. */
        uint32_t reserved_5_31         : 27;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_ecc_config_s cn; */
};
typedef union bdk_mdn_ecc_config bdk_mdn_ecc_config_t;

#define BDK_MDN_ECC_CONFIG BDK_MDN_ECC_CONFIG_FUNC()
static inline uint64_t BDK_MDN_ECC_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_ECC_CONFIG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x2c;
    __bdk_csr_fatal("MDN_ECC_CONFIG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_ECC_CONFIG bdk_mdn_ecc_config_t
#define bustype_BDK_MDN_ECC_CONFIG BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_ECC_CONFIG "MDN_ECC_CONFIG"
#define busnum_BDK_MDN_ECC_CONFIG 0
#define arguments_BDK_MDN_ECC_CONFIG -1,-1,-1,-1

/**
 * Register (MDSB) mdn_ecc_irq
 *
 * MDN ECC Interrupt Request Register
 * This register responds to broadcast reads when MDN_ECC_STATUS[DBE or SBE] fields are asserted.
 */
union bdk_mdn_ecc_irq
{
    uint32_t u;
    struct bdk_mdn_ecc_irq_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t hub_id                : 7;  /**< [ 30: 24](RO/H) ECC hub identifier. */
        uint32_t node_id               : 10; /**< [ 23: 14](RO/H) ECC node identifier. */
        uint32_t reserved_0_13         : 14;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_13         : 14;
        uint32_t node_id               : 10; /**< [ 23: 14](RO/H) ECC node identifier. */
        uint32_t hub_id                : 7;  /**< [ 30: 24](RO/H) ECC hub identifier. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_ecc_irq_s cn; */
};
typedef union bdk_mdn_ecc_irq bdk_mdn_ecc_irq_t;

#define BDK_MDN_ECC_IRQ BDK_MDN_ECC_IRQ_FUNC()
static inline uint64_t BDK_MDN_ECC_IRQ_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_ECC_IRQ_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x30;
    __bdk_csr_fatal("MDN_ECC_IRQ", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_ECC_IRQ bdk_mdn_ecc_irq_t
#define bustype_BDK_MDN_ECC_IRQ BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_ECC_IRQ "MDN_ECC_IRQ"
#define busnum_BDK_MDN_ECC_IRQ 0
#define arguments_BDK_MDN_ECC_IRQ -1,-1,-1,-1

/**
 * Register (MDSB) mdn_ecc_status
 *
 * MDN ECC Error Status Register
 */
union bdk_mdn_ecc_status
{
    uint32_t u;
    struct bdk_mdn_ecc_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_30_31        : 2;
        uint32_t row                   : 14; /**< [ 29: 16](RO/H) SRAM row address of the most recent double-bit/uncorrectable error (DBE) if
                                                                 [DBE] is asserted or the SRAM row address of the most recent
                                                                 single-bit/correctable error (SBE) is [DBE] is deasserted and [SBE] is
                                                                 asserted. */
        uint32_t reserved_4_15         : 12;
        uint32_t dbe_plus              : 1;  /**< [  3:  3](RO/H) Asserted when ECC detects another double-bit or single-bit error before the
                                                                 first error was processed by the interrupt handler. Note that the error
                                                                 reporting prioritizes DBEs over SBEs. Thus prior to being read, a DBE will
                                                                 overwrite MDN_ECC_IRQ[HUB_ID] and MDN_ECC_IRQ[NODE_ID] of a previous SBE. If
                                                                 [SBE] is set then PLUS indicates that additional SBEs have occurred beyond that
                                                                 first captures. If [DBE] is set then [DBE_PLUS] indicates that there was either
                                                                 a previous SBE or subsequent SBE or subsequent DBE. */
        uint32_t sbe_plus              : 1;  /**< [  2:  2](RO/H) Asserted when ECC detects another double-bit or single-bit error before the
                                                                 first error was processed by the interrupt handler. Note that the error
                                                                 reporting prioritizes DBEs over SBEs. Thus prior to being read, a DBE will
                                                                 overwrite MDN_ECC_IRQ[HUB_ID] and MDN_ECC_IRQ[NODE_ID] of a previous SBE. If
                                                                 [SBE] is set then PLUS indicates that additional SBEs have occurred beyond that
                                                                 first captures. If [DBE] is set then [SBE_PLUS] indicates that there was either
                                                                 a previous SBE or subsequent SBE or subsequent DBE. */
        uint32_t dbe                   : 1;  /**< [  1:  1](RO/H) Asserted when a double-bit/uncorrectable error is detected. */
        uint32_t sbe                   : 1;  /**< [  0:  0](RO/H) Asserted when a single-bit/correctable error is detected. */
#else /* Word 0 - Little Endian */
        uint32_t sbe                   : 1;  /**< [  0:  0](RO/H) Asserted when a single-bit/correctable error is detected. */
        uint32_t dbe                   : 1;  /**< [  1:  1](RO/H) Asserted when a double-bit/uncorrectable error is detected. */
        uint32_t sbe_plus              : 1;  /**< [  2:  2](RO/H) Asserted when ECC detects another double-bit or single-bit error before the
                                                                 first error was processed by the interrupt handler. Note that the error
                                                                 reporting prioritizes DBEs over SBEs. Thus prior to being read, a DBE will
                                                                 overwrite MDN_ECC_IRQ[HUB_ID] and MDN_ECC_IRQ[NODE_ID] of a previous SBE. If
                                                                 [SBE] is set then PLUS indicates that additional SBEs have occurred beyond that
                                                                 first captures. If [DBE] is set then [SBE_PLUS] indicates that there was either
                                                                 a previous SBE or subsequent SBE or subsequent DBE. */
        uint32_t dbe_plus              : 1;  /**< [  3:  3](RO/H) Asserted when ECC detects another double-bit or single-bit error before the
                                                                 first error was processed by the interrupt handler. Note that the error
                                                                 reporting prioritizes DBEs over SBEs. Thus prior to being read, a DBE will
                                                                 overwrite MDN_ECC_IRQ[HUB_ID] and MDN_ECC_IRQ[NODE_ID] of a previous SBE. If
                                                                 [SBE] is set then PLUS indicates that additional SBEs have occurred beyond that
                                                                 first captures. If [DBE] is set then [DBE_PLUS] indicates that there was either
                                                                 a previous SBE or subsequent SBE or subsequent DBE. */
        uint32_t reserved_4_15         : 12;
        uint32_t row                   : 14; /**< [ 29: 16](RO/H) SRAM row address of the most recent double-bit/uncorrectable error (DBE) if
                                                                 [DBE] is asserted or the SRAM row address of the most recent
                                                                 single-bit/correctable error (SBE) is [DBE] is deasserted and [SBE] is
                                                                 asserted. */
        uint32_t reserved_30_31        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_ecc_status_s cn; */
};
typedef union bdk_mdn_ecc_status bdk_mdn_ecc_status_t;

#define BDK_MDN_ECC_STATUS BDK_MDN_ECC_STATUS_FUNC()
static inline uint64_t BDK_MDN_ECC_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_ECC_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x34;
    __bdk_csr_fatal("MDN_ECC_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_ECC_STATUS bdk_mdn_ecc_status_t
#define bustype_BDK_MDN_ECC_STATUS BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_ECC_STATUS "MDN_ECC_STATUS"
#define busnum_BDK_MDN_ECC_STATUS 0
#define arguments_BDK_MDN_ECC_STATUS -1,-1,-1,-1

/**
 * Register (MDSB) mdn_ecc_status_rc
 *
 * INTERNAL: MDN ECC Error Status with Read Clear Register
 *
 * This register is a duplicate of MDC_NODE_ECC_STATUS that clears status
 * when read.  It is intended to only be read by the mdc_root_sm state
 * machine.
 */
union bdk_mdn_ecc_status_rc
{
    uint32_t u;
    struct bdk_mdn_ecc_status_rc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_30_31        : 2;
        uint32_t row                   : 14; /**< [ 29: 16](RO/H) SRAM row address of the most recent double-bit/uncorrectable error (DBE) if
                                                                 [DBE] is asserted or the SRAM row address of the most recent
                                                                 single-bit/correctable error (SBE) is [DBE] is deasserted and [SBE] is
                                                                 asserted. */
        uint32_t reserved_4_15         : 12;
        uint32_t dbe_plus              : 1;  /**< [  3:  3](RO/H) Asserted when ECC detects another double-bit or single-bit error before the
                                                                 first error was processed by the interrupt handler. Note that the error
                                                                 reporting prioritizes DBEs over SBEs. Thus prior to being read, a DBE will
                                                                 overwrite MDN_ECC_IRQ[HUB_ID] and MDN_ECC_IRQ[NODE_ID] of a previous SBE. If
                                                                 [SBE] is set then PLUS indicates that additional SBEs have occurred beyond that
                                                                 first captures. If [DBE] is set then [DBE_PLUS] indicates that there was either
                                                                 a previous SBE or subsequent SBE or subsequent DBE. */
        uint32_t sbe_plus              : 1;  /**< [  2:  2](RO/H) Asserted when ECC detects another double-bit or single-bit error before the
                                                                 first error was processed by the interrupt handler. Note that the error
                                                                 reporting prioritizes DBEs over SBEs. Thus prior to being read, a DBE will
                                                                 overwrite MDN_ECC_IRQ[HUB_ID] and MDN_ECC_IRQ[NODE_ID] of a previous SBE. If
                                                                 [SBE] is set then PLUS indicates that additional SBEs have occurred beyond that
                                                                 first captures. If [DBE] is set then [SBE_PLUS] indicates that there was either
                                                                 a previous SBE or subsequent SBE or subsequent DBE. */
        uint32_t dbe                   : 1;  /**< [  1:  1](RO/H) Asserted when a double-bit/uncorrectable error is detected. */
        uint32_t sbe                   : 1;  /**< [  0:  0](RO/H) Asserted when a single-bit/correctable error is detected. */
#else /* Word 0 - Little Endian */
        uint32_t sbe                   : 1;  /**< [  0:  0](RO/H) Asserted when a single-bit/correctable error is detected. */
        uint32_t dbe                   : 1;  /**< [  1:  1](RO/H) Asserted when a double-bit/uncorrectable error is detected. */
        uint32_t sbe_plus              : 1;  /**< [  2:  2](RO/H) Asserted when ECC detects another double-bit or single-bit error before the
                                                                 first error was processed by the interrupt handler. Note that the error
                                                                 reporting prioritizes DBEs over SBEs. Thus prior to being read, a DBE will
                                                                 overwrite MDN_ECC_IRQ[HUB_ID] and MDN_ECC_IRQ[NODE_ID] of a previous SBE. If
                                                                 [SBE] is set then PLUS indicates that additional SBEs have occurred beyond that
                                                                 first captures. If [DBE] is set then [SBE_PLUS] indicates that there was either
                                                                 a previous SBE or subsequent SBE or subsequent DBE. */
        uint32_t dbe_plus              : 1;  /**< [  3:  3](RO/H) Asserted when ECC detects another double-bit or single-bit error before the
                                                                 first error was processed by the interrupt handler. Note that the error
                                                                 reporting prioritizes DBEs over SBEs. Thus prior to being read, a DBE will
                                                                 overwrite MDN_ECC_IRQ[HUB_ID] and MDN_ECC_IRQ[NODE_ID] of a previous SBE. If
                                                                 [SBE] is set then PLUS indicates that additional SBEs have occurred beyond that
                                                                 first captures. If [DBE] is set then [DBE_PLUS] indicates that there was either
                                                                 a previous SBE or subsequent SBE or subsequent DBE. */
        uint32_t reserved_4_15         : 12;
        uint32_t row                   : 14; /**< [ 29: 16](RO/H) SRAM row address of the most recent double-bit/uncorrectable error (DBE) if
                                                                 [DBE] is asserted or the SRAM row address of the most recent
                                                                 single-bit/correctable error (SBE) is [DBE] is deasserted and [SBE] is
                                                                 asserted. */
        uint32_t reserved_30_31        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_ecc_status_rc_s cn; */
};
typedef union bdk_mdn_ecc_status_rc bdk_mdn_ecc_status_rc_t;

#define BDK_MDN_ECC_STATUS_RC BDK_MDN_ECC_STATUS_RC_FUNC()
static inline uint64_t BDK_MDN_ECC_STATUS_RC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_ECC_STATUS_RC_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x38;
    __bdk_csr_fatal("MDN_ECC_STATUS_RC", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_ECC_STATUS_RC bdk_mdn_ecc_status_rc_t
#define bustype_BDK_MDN_ECC_STATUS_RC BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_ECC_STATUS_RC "MDN_ECC_STATUS_RC"
#define busnum_BDK_MDN_ECC_STATUS_RC 0
#define arguments_BDK_MDN_ECC_STATUS_RC -1,-1,-1,-1

/**
 * Register (MDSB) mdn_enum
 *
 * INTERNAL: MDN Enumeration Register
 *
 * This is used to enumerate a serial chain using broadcast writes.
 */
union bdk_mdn_enum
{
    uint32_t u;
    struct bdk_mdn_enum_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t hub_id                : 7;  /**< [ 30: 24](RO/H) Hub identifier. */
        uint32_t node_id               : 10; /**< [ 23: 14](RO/H) Node identifier. */
        uint32_t reserved_3_13         : 11;
        uint32_t chain_id              : 3;  /**< [  2:  0](RO/H) Chain identifier. */
#else /* Word 0 - Little Endian */
        uint32_t chain_id              : 3;  /**< [  2:  0](RO/H) Chain identifier. */
        uint32_t reserved_3_13         : 11;
        uint32_t node_id               : 10; /**< [ 23: 14](RO/H) Node identifier. */
        uint32_t hub_id                : 7;  /**< [ 30: 24](RO/H) Hub identifier. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_enum_s cn; */
};
typedef union bdk_mdn_enum bdk_mdn_enum_t;

#define BDK_MDN_ENUM BDK_MDN_ENUM_FUNC()
static inline uint64_t BDK_MDN_ENUM_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_ENUM_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x44;
    __bdk_csr_fatal("MDN_ENUM", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_ENUM bdk_mdn_enum_t
#define bustype_BDK_MDN_ENUM BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_ENUM "MDN_ENUM"
#define busnum_BDK_MDN_ENUM 0
#define arguments_BDK_MDN_ENUM -1,-1,-1,-1

/**
 * Register (MDSB) mdn_scratch
 *
 * INTERNAL: MDN Scratch Register
 *
 * Not implemented in hardware.
 */
union bdk_mdn_scratch
{
    uint32_t u;
    struct bdk_mdn_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t scratch               : 32; /**< [ 31:  0](R/W) Scratch register. */
#else /* Word 0 - Little Endian */
        uint32_t scratch               : 32; /**< [ 31:  0](R/W) Scratch register. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdn_scratch_s cn; */
};
typedef union bdk_mdn_scratch bdk_mdn_scratch_t;

#define BDK_MDN_SCRATCH BDK_MDN_SCRATCH_FUNC()
static inline uint64_t BDK_MDN_SCRATCH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDN_SCRATCH_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x3c;
    __bdk_csr_fatal("MDN_SCRATCH", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDN_SCRATCH bdk_mdn_scratch_t
#define bustype_BDK_MDN_SCRATCH BDK_CSR_TYPE_MDSB
#define basename_BDK_MDN_SCRATCH "MDN_SCRATCH"
#define busnum_BDK_MDN_SCRATCH 0
#define arguments_BDK_MDN_SCRATCH -1,-1,-1,-1

#endif /* __BDK_CSRS_MDN_H__ */
