#ifndef __BDK_CSRS_MDC_H__
#define __BDK_CSRS_MDC_H__
/* This file is auto-generated. Do not edit */

/***********************license start***********************************
* Copyright (C) 2019 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/


/**
 * @file
 *
 * Configuration and status register (CSR) address and type definitions for
 * OcteonTX MDC.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration mdc_bar_e
 *
 * MDC Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_MDC_BAR_E_MDC_PF_BAR0 (0x87e010000000ll)
#define BDK_MDC_BAR_E_MDC_PF_BAR0_SIZE 0x100000ull
#define BDK_MDC_BAR_E_MDC_PF_BAR2 (0x87e008000000ll)
#define BDK_MDC_BAR_E_MDC_PF_BAR2_SIZE 0x1000000ull
#define BDK_MDC_BAR_E_MDC_PF_BAR4 (0x87e010100000ll)
#define BDK_MDC_BAR_E_MDC_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration mdc_int_vec_e
 *
 * MDC Interrupt Source Enumeration
 * Enumerates the different MDC-generated interrupts.
 */
#define BDK_MDC_INT_VEC_E_MDC_ECC_ERR (0)

/**
 * Enumeration mdc_ras_uet_e
 *
 * MDC RAS Uncorrected Error Type Enumeration
 * Enumerates the uncorrected error types in MDC_RAS_ROM(). See also RAS_UET_E of which
 * this enumeration is a superset.
 */
#define BDK_MDC_RAS_UET_E_NOUC (4)
#define BDK_MDC_RAS_UET_E_UC (0)
#define BDK_MDC_RAS_UET_E_UEO (2)
#define BDK_MDC_RAS_UET_E_UER (3)
#define BDK_MDC_RAS_UET_E_UEU (1)

/**
 * Structure mdc_ras_entry_s
 *
 * MDN RAS Entry Structure
 * This structure describes the leaf node data returned from MDC_RAS_ROM().
 */
union bdk_mdc_ras_entry_s
{
    uint64_t u;
    struct bdk_mdc_ras_entry_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ras_id                : 32; /**< [ 63: 32] RAM identifier. Program-determined (non-human-readable hash) unique identifier
                                                                 for this given RAM. Software typically uses this to indicate in an error record
                                                                 which memory is reporting the error. Software may also use this value to
                                                                 initiate special error handing routines, e.g. on a SBE determine the [RAS_ID] is
                                                                 the LLC cache data, and thus initiate a LLC cache scrub.

                                                                 If a memory in a future passes or products have the same function, but a
                                                                 different size, the [RAS_ID] should remain the same.  Memories with the same
                                                                 [RAS_ID] will typically have the same value for all MDC_RAS_ENTRY_S fields. */
        uint64_t ras_serr              : 8;  /**< [ 31: 24] Type of errors, and ARM RAS error record type. Enumerated by
                                                                 RAS_SERR_E. Software, if/when creating a ARM RAS error record, typically should
                                                                 mark the record's error type (SERR) using this value.

                                                                 Typically RAMs use either RAS_SERR_E::SRAM_DATA or RAS_SERR_E::REG_CTL. */
        uint64_t ras_uet               : 3;  /**< [ 23: 21] ARM RAS uncorrected error type. Enumerated by MDC_RAS_UET_E. If a uncorrectable
                                                                 error occurs in this memory, the uncorrected error type. Software, if/when
                                                                 creating a ARM RAS error record, typically should mark the record's uncorrected
                                                                 error field (UE) using this value. */
        uint64_t ras_transient         : 1;  /**< [ 20: 20] Transient. This indicates that software, if/when creating a ARM RAS error record,
                                                                 typically should mark the record's corrected error field (CE) as persistent
                                                                 versus transient.
                                                                 0 = Persistent. If a soft error occurs in this memory, multiple soft errors may
                                                                 be seen until some action is taken, e.g. a software scrub. Typically memories
                                                                 containing configuration data work this way.
                                                                 1 = Transient. If a soft error occurs in this memory, it will generally be seen
                                                                 only once then self-correct. Software never needs to take any action on single
                                                                 bit errors to clean up. e.g. a RAM that has a hardware scrubber or is a FIFO. */
        uint64_t ras_poison            : 2;  /**< [ 19: 18] Poison propagation.
                                                                 0x0 = None. This memory does not support poisoning.
                                                                 0x1 = Deferred. If a DBE occurs in this memory, the block sends out poison to
                                                                 the consumer and does not otherwise consume the data. This indicates software,
                                                                 if/when creating a ARM RAS error record, typically would mark the record's
                                                                 deferred error field (DE) as true.
                                                                 0x2 = Consumed. This memory is reporting it received a poison and is propagating
                                                                 it. This indicates software, if/when creating a ARM RAS error record, typically
                                                                 would mark the record's deferred error field (DE) as true, and the poison (PN)
                                                                 field as true. */
        uint64_t reserved_0_17         : 18;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_17         : 18;
        uint64_t ras_poison            : 2;  /**< [ 19: 18] Poison propagation.
                                                                 0x0 = None. This memory does not support poisoning.
                                                                 0x1 = Deferred. If a DBE occurs in this memory, the block sends out poison to
                                                                 the consumer and does not otherwise consume the data. This indicates software,
                                                                 if/when creating a ARM RAS error record, typically would mark the record's
                                                                 deferred error field (DE) as true.
                                                                 0x2 = Consumed. This memory is reporting it received a poison and is propagating
                                                                 it. This indicates software, if/when creating a ARM RAS error record, typically
                                                                 would mark the record's deferred error field (DE) as true, and the poison (PN)
                                                                 field as true. */
        uint64_t ras_transient         : 1;  /**< [ 20: 20] Transient. This indicates that software, if/when creating a ARM RAS error record,
                                                                 typically should mark the record's corrected error field (CE) as persistent
                                                                 versus transient.
                                                                 0 = Persistent. If a soft error occurs in this memory, multiple soft errors may
                                                                 be seen until some action is taken, e.g. a software scrub. Typically memories
                                                                 containing configuration data work this way.
                                                                 1 = Transient. If a soft error occurs in this memory, it will generally be seen
                                                                 only once then self-correct. Software never needs to take any action on single
                                                                 bit errors to clean up. e.g. a RAM that has a hardware scrubber or is a FIFO. */
        uint64_t ras_uet               : 3;  /**< [ 23: 21] ARM RAS uncorrected error type. Enumerated by MDC_RAS_UET_E. If a uncorrectable
                                                                 error occurs in this memory, the uncorrected error type. Software, if/when
                                                                 creating a ARM RAS error record, typically should mark the record's uncorrected
                                                                 error field (UE) using this value. */
        uint64_t ras_serr              : 8;  /**< [ 31: 24] Type of errors, and ARM RAS error record type. Enumerated by
                                                                 RAS_SERR_E. Software, if/when creating a ARM RAS error record, typically should
                                                                 mark the record's error type (SERR) using this value.

                                                                 Typically RAMs use either RAS_SERR_E::SRAM_DATA or RAS_SERR_E::REG_CTL. */
        uint64_t ras_id                : 32; /**< [ 63: 32] RAM identifier. Program-determined (non-human-readable hash) unique identifier
                                                                 for this given RAM. Software typically uses this to indicate in an error record
                                                                 which memory is reporting the error. Software may also use this value to
                                                                 initiate special error handing routines, e.g. on a SBE determine the [RAS_ID] is
                                                                 the LLC cache data, and thus initiate a LLC cache scrub.

                                                                 If a memory in a future passes or products have the same function, but a
                                                                 different size, the [RAS_ID] should remain the same.  Memories with the same
                                                                 [RAS_ID] will typically have the same value for all MDC_RAS_ENTRY_S fields. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_ras_entry_s_s cn9; */
    /* struct bdk_mdc_ras_entry_s_s cn96xxp1; */
    struct bdk_mdc_ras_entry_s_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ras_id                : 32; /**< [ 63: 32] RAM identifier. Program-determined (non-human-readable hash) unique identifier
                                                                 for this given RAM. Software typically uses this to indicate in an error record
                                                                 which memory is reporting the error. Software may also use this value to
                                                                 initiate special error handing routines, e.g. on a SBE determine the [RAS_ID] is
                                                                 the LLC cache data, and thus initiate a LLC cache scrub.

                                                                 If a memory in a future passes or products have the same function, but a
                                                                 different size, the [RAS_ID] should remain the same.  Memories with the same
                                                                 [RAS_ID] will typically have the same value for all MDC_RAS_ENTRY_S fields. */
        uint64_t ras_serr              : 8;  /**< [ 31: 24] Type of errors, and Arm RAS error record type. Enumerated by
                                                                 RAS_SERR_E. Software, if/when creating a Arm RAS error record, typically should
                                                                 mark the record's error type (SERR) using this value.

                                                                 Typically RAMs use either RAS_SERR_E::SRAM_DATA or RAS_SERR_E::REG_CTL. */
        uint64_t ras_uet               : 3;  /**< [ 23: 21] Arm RAS uncorrected error type. Enumerated by MDC_RAS_UET_E. If a uncorrectable
                                                                 error occurs in this memory, the uncorrected error type. Software, if/when
                                                                 creating a Arm RAS error record, typically should mark the record's uncorrected
                                                                 error field (UE) using this value. */
        uint64_t ras_transient         : 1;  /**< [ 20: 20] Transient. This indicates that software, if/when creating a Arm RAS error record,
                                                                 typically should mark the record's corrected error field (CE) as persistent
                                                                 versus transient.
                                                                 0 = Persistent. If a soft error occurs in this memory, multiple soft errors may
                                                                 be seen until some action is taken, e.g. a software scrub. Typically memories
                                                                 containing configuration data work this way.
                                                                 1 = Transient. If a soft error occurs in this memory, it will generally be seen
                                                                 only once then self-correct. Software never needs to take any action on single
                                                                 bit errors to clean up. e.g. a RAM that has a hardware scrubber or is a FIFO. */
        uint64_t ras_poison            : 2;  /**< [ 19: 18] Poison propagation.
                                                                 0x0 = None. This memory does not support poisoning.
                                                                 0x1 = Deferred. If a DBE occurs in this memory, the block sends out poison to
                                                                 the consumer and does not otherwise consume the data. This indicates software,
                                                                 if/when creating a Arm RAS error record, typically would mark the record's
                                                                 deferred error field (DE) as true.
                                                                 0x2 = Consumed. This memory is reporting it received a poison and is propagating
                                                                 it. This indicates software, if/when creating a Arm RAS error record, typically
                                                                 would mark the record's deferred error field (DE) as true, and the poison (PN)
                                                                 field as true. */
        uint64_t reserved_0_17         : 18;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_17         : 18;
        uint64_t ras_poison            : 2;  /**< [ 19: 18] Poison propagation.
                                                                 0x0 = None. This memory does not support poisoning.
                                                                 0x1 = Deferred. If a DBE occurs in this memory, the block sends out poison to
                                                                 the consumer and does not otherwise consume the data. This indicates software,
                                                                 if/when creating a Arm RAS error record, typically would mark the record's
                                                                 deferred error field (DE) as true.
                                                                 0x2 = Consumed. This memory is reporting it received a poison and is propagating
                                                                 it. This indicates software, if/when creating a Arm RAS error record, typically
                                                                 would mark the record's deferred error field (DE) as true, and the poison (PN)
                                                                 field as true. */
        uint64_t ras_transient         : 1;  /**< [ 20: 20] Transient. This indicates that software, if/when creating a Arm RAS error record,
                                                                 typically should mark the record's corrected error field (CE) as persistent
                                                                 versus transient.
                                                                 0 = Persistent. If a soft error occurs in this memory, multiple soft errors may
                                                                 be seen until some action is taken, e.g. a software scrub. Typically memories
                                                                 containing configuration data work this way.
                                                                 1 = Transient. If a soft error occurs in this memory, it will generally be seen
                                                                 only once then self-correct. Software never needs to take any action on single
                                                                 bit errors to clean up. e.g. a RAM that has a hardware scrubber or is a FIFO. */
        uint64_t ras_uet               : 3;  /**< [ 23: 21] Arm RAS uncorrected error type. Enumerated by MDC_RAS_UET_E. If a uncorrectable
                                                                 error occurs in this memory, the uncorrected error type. Software, if/when
                                                                 creating a Arm RAS error record, typically should mark the record's uncorrected
                                                                 error field (UE) using this value. */
        uint64_t ras_serr              : 8;  /**< [ 31: 24] Type of errors, and Arm RAS error record type. Enumerated by
                                                                 RAS_SERR_E. Software, if/when creating a Arm RAS error record, typically should
                                                                 mark the record's error type (SERR) using this value.

                                                                 Typically RAMs use either RAS_SERR_E::SRAM_DATA or RAS_SERR_E::REG_CTL. */
        uint64_t ras_id                : 32; /**< [ 63: 32] RAM identifier. Program-determined (non-human-readable hash) unique identifier
                                                                 for this given RAM. Software typically uses this to indicate in an error record
                                                                 which memory is reporting the error. Software may also use this value to
                                                                 initiate special error handing routines, e.g. on a SBE determine the [RAS_ID] is
                                                                 the LLC cache data, and thus initiate a LLC cache scrub.

                                                                 If a memory in a future passes or products have the same function, but a
                                                                 different size, the [RAS_ID] should remain the same.  Memories with the same
                                                                 [RAS_ID] will typically have the same value for all MDC_RAS_ENTRY_S fields. */
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mdc_ras_entry_s_cn96xxp3 cn98xx; */
    /* struct bdk_mdc_ras_entry_s_cn96xxp3 cnf95xx; */
    /* struct bdk_mdc_ras_entry_s_cn96xxp3 loki; */
};

/**
 * Register (RSL) mdc_active_pc
 *
 * MDC Active Cycles Register
 */
union bdk_mdc_active_pc
{
    uint64_t u;
    struct bdk_mdc_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the conditional clocks are active. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the conditional clocks are active. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_active_pc_s cn; */
};
typedef union bdk_mdc_active_pc bdk_mdc_active_pc_t;

#define BDK_MDC_ACTIVE_PC BDK_MDC_ACTIVE_PC_FUNC()
static inline uint64_t BDK_MDC_ACTIVE_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_ACTIVE_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e0100000e8ll;
    __bdk_csr_fatal("MDC_ACTIVE_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_ACTIVE_PC bdk_mdc_active_pc_t
#define bustype_BDK_MDC_ACTIVE_PC BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_ACTIVE_PC "MDC_ACTIVE_PC"
#define device_bar_BDK_MDC_ACTIVE_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_ACTIVE_PC 0
#define arguments_BDK_MDC_ACTIVE_PC -1,-1,-1,-1

/**
 * Register (RSL) mdc_bist_config
 *
 * MDC Configuration Register
 */
union bdk_mdc_bist_config
{
    uint64_t u;
    struct bdk_mdc_bist_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_27_63        : 37;
        uint64_t clock_gating_enable   : 1;  /**< [ 26: 26](R/W) When clear, force conditional clocks on. Clear for diagnostic use only.
                                                                 Internal:
                                                                 clock_forcer attribute not used as state is inverted versus other blocks. */
        uint64_t mdc_broadcast         : 1;  /**< [ 25: 25](R/W) This field is used in conjunction with [MDH_START_RATIO], [MDN_START_RATIO],
                                                                 and [STAGGER_PERIOD] to control BIST start staggering. The field
                                                                 specifies whether or not a given BIST start command is transmitted to
                                                                 all serial chains simultaneously or not.
                                                                   0 = BIST start commands sent to one chain at a time.
                                                                   1 = BIST start commands sent to all chains simultaneously. */
        uint64_t mdh_start_ratio       : 3;  /**< [ 24: 22](R/W) This field is used in conjunction with [MDC_BROADCAST], [MDN_START_RATIO],
                                                                 and [STAGGER_PERIOD] to control BIST start staggering.  The field effectively
                                                                 specifies how many MDHs participates in a given BIST start command. Valid
                                                                 values are 0 through 7.  The MDC programs MDN_BIST_ADDR_MASK[MDH_START_RATIO]
                                                                 of all MDN's with this value prior to starting BIST.
                                                                   0x0 = All MDHs participate - 1 hub loop.
                                                                   0x1 = Every 2nd MDH participates - 2 hub loops.
                                                                   0x2 = Every 4th MDH participates - 4 hub loops.
                                                                   ...
                                                                   0x7 = Every 128th MDH participates - 128 hub loops. */
        uint64_t mdn_start_ratio       : 4;  /**< [ 21: 18](R/W) This field is used in conjuction with [MDC_BROADCAST], [MDH_START_RATIO],
                                                                 and [STAGGER_PERIOD] to control BIST start staggering.  The field effectively
                                                                 specifies how many MDNs participate in a given BIST start command.  The
                                                                 value is formatted as the reciprocal of a base two exponent
                                                                 (1/2^[MDN_START_RATIO]).  Valid values are 0 through 10.  The MDC programs
                                                                 MDN_BIST_ADDR_MASK[MDN_START_RATIO] of all MDN's with this value prior
                                                                 to starting BIST.
                                                                   0x0 = All MDNs participate - 1 node loop.
                                                                   0x1 = Every 2nd MDN participates - 2 node loops.
                                                                   0x2 = Every 4th MDN participates - 4 node loops.
                                                                   ...
                                                                   0xA = Every 1024th MDN participates - 1024 node loops. */
        uint64_t bisr_soft_disable_xor : 1;  /**< [ 17: 17](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 This value is XORed with the FUS_FUSE_NUM_E::BISR_FUSED_ONLY fuse bit to
                                                                 override its setting. When the FUS_FUSE_NUM_E::BISR_FUSED_ONLY fuse is blown,
                                                                 only repairs that are blown into fuses are used and soft repairs are
                                                                 disallowed. Overriding the fuse allows soft repairs to be used again. */
        uint64_t stagger_disable       : 1;  /**< [ 16: 16](R/W) BIST stagger disable. Disables the BIST stagger period and starts BIST
                                                                 via a broadcast write to all BIST state machines. For diagnostic use only. */
        uint64_t stagger_period        : 16; /**< [ 15:  0](R/W) When BIST start staggering is enabled, a BIST start command is
                                                                 periodically transmitted down 1 or more MDC serial chains through 1 or
                                                                 more MDHs (hubs) to start BIST on 1 or more MDNs (nodes).  The total
                                                                 number of start commands transmitted and the number of MDNs that start
                                                                 BIST upon each command is a controlled by the settings of [MDC_BROADCAST],
                                                                 [MDH_START_RATIO] and [MDN_START_RATIO].  At one extreme only a single BIST
                                                                 start command is sent to start all MDNs simultaneously.  At the other
                                                                 extreme a BIST start command is sent to each MDN individually to start
                                                                 BIST sequentially.  The MDC root state machine loops upon chain (outer),
                                                                 hub (middle) and node (inner) IDs when send the BIST start commands.

                                                                 This field specifies the number of clocks between BIST start commands.
                                                                 Increasing the value reduces the number of memories executing BIST
                                                                 simultaneously thus reducing peak power consumption at the expense of
                                                                 lengthening the overall time it takes to run BIST.  Decreasing the value
                                                                 has the opposite effect of reducing the overall BIST run time while
                                                                 increasing power consumption. */
#else /* Word 0 - Little Endian */
        uint64_t stagger_period        : 16; /**< [ 15:  0](R/W) When BIST start staggering is enabled, a BIST start command is
                                                                 periodically transmitted down 1 or more MDC serial chains through 1 or
                                                                 more MDHs (hubs) to start BIST on 1 or more MDNs (nodes).  The total
                                                                 number of start commands transmitted and the number of MDNs that start
                                                                 BIST upon each command is a controlled by the settings of [MDC_BROADCAST],
                                                                 [MDH_START_RATIO] and [MDN_START_RATIO].  At one extreme only a single BIST
                                                                 start command is sent to start all MDNs simultaneously.  At the other
                                                                 extreme a BIST start command is sent to each MDN individually to start
                                                                 BIST sequentially.  The MDC root state machine loops upon chain (outer),
                                                                 hub (middle) and node (inner) IDs when send the BIST start commands.

                                                                 This field specifies the number of clocks between BIST start commands.
                                                                 Increasing the value reduces the number of memories executing BIST
                                                                 simultaneously thus reducing peak power consumption at the expense of
                                                                 lengthening the overall time it takes to run BIST.  Decreasing the value
                                                                 has the opposite effect of reducing the overall BIST run time while
                                                                 increasing power consumption. */
        uint64_t stagger_disable       : 1;  /**< [ 16: 16](R/W) BIST stagger disable. Disables the BIST stagger period and starts BIST
                                                                 via a broadcast write to all BIST state machines. For diagnostic use only. */
        uint64_t bisr_soft_disable_xor : 1;  /**< [ 17: 17](R/W) For diagnostic use only.
                                                                 Internal:
                                                                 This value is XORed with the FUS_FUSE_NUM_E::BISR_FUSED_ONLY fuse bit to
                                                                 override its setting. When the FUS_FUSE_NUM_E::BISR_FUSED_ONLY fuse is blown,
                                                                 only repairs that are blown into fuses are used and soft repairs are
                                                                 disallowed. Overriding the fuse allows soft repairs to be used again. */
        uint64_t mdn_start_ratio       : 4;  /**< [ 21: 18](R/W) This field is used in conjuction with [MDC_BROADCAST], [MDH_START_RATIO],
                                                                 and [STAGGER_PERIOD] to control BIST start staggering.  The field effectively
                                                                 specifies how many MDNs participate in a given BIST start command.  The
                                                                 value is formatted as the reciprocal of a base two exponent
                                                                 (1/2^[MDN_START_RATIO]).  Valid values are 0 through 10.  The MDC programs
                                                                 MDN_BIST_ADDR_MASK[MDN_START_RATIO] of all MDN's with this value prior
                                                                 to starting BIST.
                                                                   0x0 = All MDNs participate - 1 node loop.
                                                                   0x1 = Every 2nd MDN participates - 2 node loops.
                                                                   0x2 = Every 4th MDN participates - 4 node loops.
                                                                   ...
                                                                   0xA = Every 1024th MDN participates - 1024 node loops. */
        uint64_t mdh_start_ratio       : 3;  /**< [ 24: 22](R/W) This field is used in conjunction with [MDC_BROADCAST], [MDN_START_RATIO],
                                                                 and [STAGGER_PERIOD] to control BIST start staggering.  The field effectively
                                                                 specifies how many MDHs participates in a given BIST start command. Valid
                                                                 values are 0 through 7.  The MDC programs MDN_BIST_ADDR_MASK[MDH_START_RATIO]
                                                                 of all MDN's with this value prior to starting BIST.
                                                                   0x0 = All MDHs participate - 1 hub loop.
                                                                   0x1 = Every 2nd MDH participates - 2 hub loops.
                                                                   0x2 = Every 4th MDH participates - 4 hub loops.
                                                                   ...
                                                                   0x7 = Every 128th MDH participates - 128 hub loops. */
        uint64_t mdc_broadcast         : 1;  /**< [ 25: 25](R/W) This field is used in conjunction with [MDH_START_RATIO], [MDN_START_RATIO],
                                                                 and [STAGGER_PERIOD] to control BIST start staggering. The field
                                                                 specifies whether or not a given BIST start command is transmitted to
                                                                 all serial chains simultaneously or not.
                                                                   0 = BIST start commands sent to one chain at a time.
                                                                   1 = BIST start commands sent to all chains simultaneously. */
        uint64_t clock_gating_enable   : 1;  /**< [ 26: 26](R/W) When clear, force conditional clocks on. Clear for diagnostic use only.
                                                                 Internal:
                                                                 clock_forcer attribute not used as state is inverted versus other blocks. */
        uint64_t reserved_27_63        : 37;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_bist_config_s cn; */
};
typedef union bdk_mdc_bist_config bdk_mdc_bist_config_t;

#define BDK_MDC_BIST_CONFIG BDK_MDC_BIST_CONFIG_FUNC()
static inline uint64_t BDK_MDC_BIST_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_BIST_CONFIG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000008ll;
    __bdk_csr_fatal("MDC_BIST_CONFIG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_BIST_CONFIG bdk_mdc_bist_config_t
#define bustype_BDK_MDC_BIST_CONFIG BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_BIST_CONFIG "MDC_BIST_CONFIG"
#define device_bar_BDK_MDC_BIST_CONFIG 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_BIST_CONFIG 0
#define arguments_BDK_MDC_BIST_CONFIG -1,-1,-1,-1

/**
 * Register (RSL) mdc_bist_control
 *
 * MDC Global BIST Control Register
 */
union bdk_mdc_bist_control
{
    uint64_t u;
    struct bdk_mdc_bist_control_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t reset                 : 1;  /**< [  2:  2](WO) Resets all BIST state machines. */
        uint64_t clear                 : 1;  /**< [  1:  1](WO) Assert this control with [START] to run clear BIST operation. */
        uint64_t start                 : 1;  /**< [  0:  0](WO) Run Normal BIST operation. No other command ([RESET], [CLEAR] nor [START]) from
                                                                 this CSR will be recognized until the BIST operation has completed or timed out
                                                                 (i.e. until MDC_BIST_STATUS[STATUS] != MDN_BIST_STATUS_E::ACTIVE). */
#else /* Word 0 - Little Endian */
        uint64_t start                 : 1;  /**< [  0:  0](WO) Run Normal BIST operation. No other command ([RESET], [CLEAR] nor [START]) from
                                                                 this CSR will be recognized until the BIST operation has completed or timed out
                                                                 (i.e. until MDC_BIST_STATUS[STATUS] != MDN_BIST_STATUS_E::ACTIVE). */
        uint64_t clear                 : 1;  /**< [  1:  1](WO) Assert this control with [START] to run clear BIST operation. */
        uint64_t reset                 : 1;  /**< [  2:  2](WO) Resets all BIST state machines. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_bist_control_s cn; */
};
typedef union bdk_mdc_bist_control bdk_mdc_bist_control_t;

#define BDK_MDC_BIST_CONTROL BDK_MDC_BIST_CONTROL_FUNC()
static inline uint64_t BDK_MDC_BIST_CONTROL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_BIST_CONTROL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000028ll;
    __bdk_csr_fatal("MDC_BIST_CONTROL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_BIST_CONTROL bdk_mdc_bist_control_t
#define bustype_BDK_MDC_BIST_CONTROL BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_BIST_CONTROL "MDC_BIST_CONTROL"
#define device_bar_BDK_MDC_BIST_CONTROL 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_BIST_CONTROL 0
#define arguments_BDK_MDC_BIST_CONTROL -1,-1,-1,-1

/**
 * Register (RSL) mdc_bist_debug_mode
 *
 * MDC Configuration Register
 */
union bdk_mdc_bist_debug_mode
{
    uint64_t u;
    struct bdk_mdc_bist_debug_mode_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t enable                : 1;  /**< [  0:  0](R/W/H) Sticky enable bit for debug mode that is reset by cold reset only.  Debug
                                                                 mode enables BIST control via RSL and/or JTAG CSR access after the reset
                                                                 block has requested BIST to run.  For diagnostic use only.
                                                                   0 = Debug mode disabled.
                                                                   1 = Debug mode enabled. */
#else /* Word 0 - Little Endian */
        uint64_t enable                : 1;  /**< [  0:  0](R/W/H) Sticky enable bit for debug mode that is reset by cold reset only.  Debug
                                                                 mode enables BIST control via RSL and/or JTAG CSR access after the reset
                                                                 block has requested BIST to run.  For diagnostic use only.
                                                                   0 = Debug mode disabled.
                                                                   1 = Debug mode enabled. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_bist_debug_mode_s cn; */
};
typedef union bdk_mdc_bist_debug_mode bdk_mdc_bist_debug_mode_t;

#define BDK_MDC_BIST_DEBUG_MODE BDK_MDC_BIST_DEBUG_MODE_FUNC()
static inline uint64_t BDK_MDC_BIST_DEBUG_MODE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_BIST_DEBUG_MODE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000000ll;
    __bdk_csr_fatal("MDC_BIST_DEBUG_MODE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_BIST_DEBUG_MODE bdk_mdc_bist_debug_mode_t
#define bustype_BDK_MDC_BIST_DEBUG_MODE BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_BIST_DEBUG_MODE "MDC_BIST_DEBUG_MODE"
#define device_bar_BDK_MDC_BIST_DEBUG_MODE 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_BIST_DEBUG_MODE 0
#define arguments_BDK_MDC_BIST_DEBUG_MODE -1,-1,-1,-1

/**
 * Register (RSL) mdc_bist_fail#
 *
 * MDC BIST Failures Register
 * This register array holds information about the first 32 BIST failures.
 */
union bdk_mdc_bist_failx
{
    uint64_t u;
    struct bdk_mdc_bist_failx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t chain_id              : 3;  /**< [ 31: 29](RO/H) Chain number. */
        uint64_t hub_id                : 7;  /**< [ 28: 22](RO/H) MDH identifier. */
        uint64_t node_id               : 10; /**< [ 21: 12](RO/H) MDN identifier. */
        uint64_t info                  : 12; /**< [ 11:  0](RO/H) Generic failure information vector.  The value is the first defect
                                                                 location in the RAM. */
#else /* Word 0 - Little Endian */
        uint64_t info                  : 12; /**< [ 11:  0](RO/H) Generic failure information vector.  The value is the first defect
                                                                 location in the RAM. */
        uint64_t node_id               : 10; /**< [ 21: 12](RO/H) MDN identifier. */
        uint64_t hub_id                : 7;  /**< [ 28: 22](RO/H) MDH identifier. */
        uint64_t chain_id              : 3;  /**< [ 31: 29](RO/H) Chain number. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_bist_failx_s cn9; */
    /* struct bdk_mdc_bist_failx_s cn96xxp1; */
    struct bdk_mdc_bist_failx_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t chain_id              : 3;  /**< [ 31: 29](RO/H) Chain number. */
        uint64_t hub_id                : 7;  /**< [ 28: 22](RO/H) MDH identifier. */
        uint64_t node_id               : 10; /**< [ 21: 12](RO/H) MDN identifier. */
        uint64_t info                  : 12; /**< [ 11:  0](RO/H) Contains MDN_BISR_REPAIR[REPAIR]. For repairable memories, this value is the
                                                                 defect location in the RAM. */
#else /* Word 0 - Little Endian */
        uint64_t info                  : 12; /**< [ 11:  0](RO/H) Contains MDN_BISR_REPAIR[REPAIR]. For repairable memories, this value is the
                                                                 defect location in the RAM. */
        uint64_t node_id               : 10; /**< [ 21: 12](RO/H) MDN identifier. */
        uint64_t hub_id                : 7;  /**< [ 28: 22](RO/H) MDH identifier. */
        uint64_t chain_id              : 3;  /**< [ 31: 29](RO/H) Chain number. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mdc_bist_failx_cn96xxp3 cn98xx; */
    /* struct bdk_mdc_bist_failx_s cnf95xxp1; */
    /* struct bdk_mdc_bist_failx_cn96xxp3 cnf95xxp2; */
    /* struct bdk_mdc_bist_failx_cn96xxp3 loki; */
};
typedef union bdk_mdc_bist_failx bdk_mdc_bist_failx_t;

static inline uint64_t BDK_MDC_BIST_FAILX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_BIST_FAILX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=31))
        return 0x87e010000100ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("MDC_BIST_FAILX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_BIST_FAILX(a) bdk_mdc_bist_failx_t
#define bustype_BDK_MDC_BIST_FAILX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_BIST_FAILX(a) "MDC_BIST_FAILX"
#define device_bar_BDK_MDC_BIST_FAILX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_BIST_FAILX(a) (a)
#define arguments_BDK_MDC_BIST_FAILX(a) (a),-1,-1,-1

/**
 * Register (RSL) mdc_bist_status
 *
 * MDC Global BIST Status Register
 */
union bdk_mdc_bist_status
{
    uint64_t u;
    struct bdk_mdc_bist_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_38_63        : 26;
        uint64_t sm_state              : 6;  /**< [ 37: 32](RO/H) BIST state machine state. For diagnostic use only. */
        uint64_t fail_count            : 16; /**< [ 31: 16](RO/H) Count of the number of failing RAMs/CAMs.  The valid range for this
                                                                 field is 0 to 33.  0 indicates no failures.  1 through 32 indicates
                                                                 1 to 32 failures.  33 indicates 33 or more failures.  Information
                                                                 for the first 32 failures can be found in MDC_BIST_FAIL(0..31). */
        uint64_t reserved_4_15         : 12;
        uint64_t rst_bist_req          : 1;  /**< [  3:  3](RO/H) Reset BIST request.  Asserted when the RESET block has requested BIST
                                                                 to run.  When debug mode is enabled, via MDC_BIST_DEBUG_MODE[ENABLE] = 1,
                                                                 MDC will still not allow BIST control via CSR until the reset block has
                                                                 requested BIST to run. */
        uint64_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine according to the
                                                                 MDN_BIST_STATUS_E enumeration. */
#else /* Word 0 - Little Endian */
        uint64_t status                : 3;  /**< [  2:  0](RO/H) Reports the state of the BIST state machine according to the
                                                                 MDN_BIST_STATUS_E enumeration. */
        uint64_t rst_bist_req          : 1;  /**< [  3:  3](RO/H) Reset BIST request.  Asserted when the RESET block has requested BIST
                                                                 to run.  When debug mode is enabled, via MDC_BIST_DEBUG_MODE[ENABLE] = 1,
                                                                 MDC will still not allow BIST control via CSR until the reset block has
                                                                 requested BIST to run. */
        uint64_t reserved_4_15         : 12;
        uint64_t fail_count            : 16; /**< [ 31: 16](RO/H) Count of the number of failing RAMs/CAMs.  The valid range for this
                                                                 field is 0 to 33.  0 indicates no failures.  1 through 32 indicates
                                                                 1 to 32 failures.  33 indicates 33 or more failures.  Information
                                                                 for the first 32 failures can be found in MDC_BIST_FAIL(0..31). */
        uint64_t sm_state              : 6;  /**< [ 37: 32](RO/H) BIST state machine state. For diagnostic use only. */
        uint64_t reserved_38_63        : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_bist_status_s cn; */
};
typedef union bdk_mdc_bist_status bdk_mdc_bist_status_t;

#define BDK_MDC_BIST_STATUS BDK_MDC_BIST_STATUS_FUNC()
static inline uint64_t BDK_MDC_BIST_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_BIST_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000030ll;
    __bdk_csr_fatal("MDC_BIST_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_BIST_STATUS bdk_mdc_bist_status_t
#define bustype_BDK_MDC_BIST_STATUS BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_BIST_STATUS "MDC_BIST_STATUS"
#define device_bar_BDK_MDC_BIST_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_BIST_STATUS 0
#define arguments_BDK_MDC_BIST_STATUS -1,-1,-1,-1

/**
 * Register (RSL) mdc_const
 *
 * MDC Constants Register
 */
union bdk_mdc_const
{
    uint64_t u;
    struct bdk_mdc_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_39_63        : 25;
        uint64_t max_chain_id          : 5;  /**< [ 38: 34](RO/H) Maximum allowed value for MDC_WIN_CMD[CHAIN_ID]. */
        uint64_t max_hub_id            : 8;  /**< [ 33: 26](RO/H) Maximum allowed value for MDC_WIN_CMD[HUB_ID]. */
        uint64_t max_node_id           : 10; /**< [ 25: 16](RO/H) Maximum allowed value for MDC_WIN_CMD[NODE_ID]. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t max_node_id           : 10; /**< [ 25: 16](RO/H) Maximum allowed value for MDC_WIN_CMD[NODE_ID]. */
        uint64_t max_hub_id            : 8;  /**< [ 33: 26](RO/H) Maximum allowed value for MDC_WIN_CMD[HUB_ID]. */
        uint64_t max_chain_id          : 5;  /**< [ 38: 34](RO/H) Maximum allowed value for MDC_WIN_CMD[CHAIN_ID]. */
        uint64_t reserved_39_63        : 25;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_const_s cn; */
};
typedef union bdk_mdc_const bdk_mdc_const_t;

#define BDK_MDC_CONST BDK_MDC_CONST_FUNC()
static inline uint64_t BDK_MDC_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_CONST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000068ll;
    __bdk_csr_fatal("MDC_CONST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_CONST bdk_mdc_const_t
#define bustype_BDK_MDC_CONST BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_CONST "MDC_CONST"
#define device_bar_BDK_MDC_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_CONST 0
#define arguments_BDK_MDC_CONST -1,-1,-1,-1

/**
 * Register (RSL) mdc_ecc_config
 *
 * MDC ECC Configuration Register
 */
union bdk_mdc_ecc_config
{
    uint64_t u;
    struct bdk_mdc_ecc_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t polling_period        : 32; /**< [ 31:  0](R/W) Specifies the length of the ECC polling period in 100 MHz clock cycles.
                                                                 The minimum period is determined by the length of the MDC serial chains.
                                                                 A value of 0 guarantees the minimum ECC polling period.  Longer values
                                                                 should be used to reduce power consumption as each ECC poll wakes up
                                                                 sleeping module along the MDC serial bus. */
#else /* Word 0 - Little Endian */
        uint64_t polling_period        : 32; /**< [ 31:  0](R/W) Specifies the length of the ECC polling period in 100 MHz clock cycles.
                                                                 The minimum period is determined by the length of the MDC serial chains.
                                                                 A value of 0 guarantees the minimum ECC polling period.  Longer values
                                                                 should be used to reduce power consumption as each ECC poll wakes up
                                                                 sleeping module along the MDC serial bus. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_ecc_config_s cn; */
};
typedef union bdk_mdc_ecc_config bdk_mdc_ecc_config_t;

#define BDK_MDC_ECC_CONFIG BDK_MDC_ECC_CONFIG_FUNC()
static inline uint64_t BDK_MDC_ECC_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_ECC_CONFIG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000038ll;
    __bdk_csr_fatal("MDC_ECC_CONFIG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_ECC_CONFIG bdk_mdc_ecc_config_t
#define bustype_BDK_MDC_ECC_CONFIG BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_ECC_CONFIG "MDC_ECC_CONFIG"
#define device_bar_BDK_MDC_ECC_CONFIG 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_ECC_CONFIG 0
#define arguments_BDK_MDC_ECC_CONFIG -1,-1,-1,-1

/**
 * Register (RSL) mdc_ecc_status
 *
 * MDC Interrupt Status Register
 */
union bdk_mdc_ecc_status
{
    uint64_t u;
    struct bdk_mdc_ecc_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t row                   : 14; /**< [ 61: 48](RO/H) SRAM row address of the most recent double-bit/uncorrectable error (DBE) if
                                                                 [DBE] is asserted or the SRAM row address of the most recent
                                                                 single bit/correctable error (SBE) is [DBE] is deasserted and [SBE] is
                                                                 asserted. */
        uint64_t reserved_36_47        : 12;
        uint64_t chain_id              : 3;  /**< [ 35: 33](RO/H) Chain identifier. */
        uint64_t hub_id                : 7;  /**< [ 32: 26](RO/H) Hub identifier. */
        uint64_t node_id               : 10; /**< [ 25: 16](RO/H) Node identifier. */
        uint64_t reserved_4_15         : 12;
        uint64_t dbe_plus              : 1;  /**< [  3:  3](RO/H) Asserted when ECC detects another double-bit or single-bit error
                                                                 before the first error was processed by the interrupt handler. */
        uint64_t sbe_plus              : 1;  /**< [  2:  2](RO/H) Asserted when another double-bit/uncorrectable or single-bit/correctable error
                                                                 before the first error was processed by the interrupt handler. */
        uint64_t dbe                   : 1;  /**< [  1:  1](RO/H) Asserted when a single-bit/correctable error is detected. */
        uint64_t sbe                   : 1;  /**< [  0:  0](RO/H) Asserted when a double-bit/uncorrectable error is detected. */
#else /* Word 0 - Little Endian */
        uint64_t sbe                   : 1;  /**< [  0:  0](RO/H) Asserted when a double-bit/uncorrectable error is detected. */
        uint64_t dbe                   : 1;  /**< [  1:  1](RO/H) Asserted when a single-bit/correctable error is detected. */
        uint64_t sbe_plus              : 1;  /**< [  2:  2](RO/H) Asserted when another double-bit/uncorrectable or single-bit/correctable error
                                                                 before the first error was processed by the interrupt handler. */
        uint64_t dbe_plus              : 1;  /**< [  3:  3](RO/H) Asserted when ECC detects another double-bit or single-bit error
                                                                 before the first error was processed by the interrupt handler. */
        uint64_t reserved_4_15         : 12;
        uint64_t node_id               : 10; /**< [ 25: 16](RO/H) Node identifier. */
        uint64_t hub_id                : 7;  /**< [ 32: 26](RO/H) Hub identifier. */
        uint64_t chain_id              : 3;  /**< [ 35: 33](RO/H) Chain identifier. */
        uint64_t reserved_36_47        : 12;
        uint64_t row                   : 14; /**< [ 61: 48](RO/H) SRAM row address of the most recent double-bit/uncorrectable error (DBE) if
                                                                 [DBE] is asserted or the SRAM row address of the most recent
                                                                 single bit/correctable error (SBE) is [DBE] is deasserted and [SBE] is
                                                                 asserted. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_ecc_status_s cn; */
};
typedef union bdk_mdc_ecc_status bdk_mdc_ecc_status_t;

#define BDK_MDC_ECC_STATUS BDK_MDC_ECC_STATUS_FUNC()
static inline uint64_t BDK_MDC_ECC_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_ECC_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000040ll;
    __bdk_csr_fatal("MDC_ECC_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_ECC_STATUS bdk_mdc_ecc_status_t
#define bustype_BDK_MDC_ECC_STATUS BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_ECC_STATUS "MDC_ECC_STATUS"
#define device_bar_BDK_MDC_ECC_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_ECC_STATUS 0
#define arguments_BDK_MDC_ECC_STATUS -1,-1,-1,-1

/**
 * Register (RSL) mdc_eco
 *
 * INTERNAL: MDC ECO Register
 */
union bdk_mdc_eco
{
    uint64_t u;
    struct bdk_mdc_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_eco_s cn; */
};
typedef union bdk_mdc_eco bdk_mdc_eco_t;

#define BDK_MDC_ECO BDK_MDC_ECO_FUNC()
static inline uint64_t BDK_MDC_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e0100000f8ll;
    __bdk_csr_fatal("MDC_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_ECO bdk_mdc_eco_t
#define bustype_BDK_MDC_ECO BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_ECO "MDC_ECO"
#define device_bar_BDK_MDC_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_ECO 0
#define arguments_BDK_MDC_ECO -1,-1,-1,-1

/**
 * Register (RSL) mdc_int_ena_w1c
 *
 * MDC Interrupt Enable Write-1-Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_mdc_int_ena_w1c
{
    uint64_t u;
    struct bdk_mdc_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ecc_error             : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MDC_INT_W1C[ECC_ERROR]. */
#else /* Word 0 - Little Endian */
        uint64_t ecc_error             : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MDC_INT_W1C[ECC_ERROR]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_int_ena_w1c_s cn; */
};
typedef union bdk_mdc_int_ena_w1c bdk_mdc_int_ena_w1c_t;

#define BDK_MDC_INT_ENA_W1C BDK_MDC_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_MDC_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000058ll;
    __bdk_csr_fatal("MDC_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_INT_ENA_W1C bdk_mdc_int_ena_w1c_t
#define bustype_BDK_MDC_INT_ENA_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_INT_ENA_W1C "MDC_INT_ENA_W1C"
#define device_bar_BDK_MDC_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_INT_ENA_W1C 0
#define arguments_BDK_MDC_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RSL) mdc_int_ena_w1s
 *
 * MDC Interrupt Enable Write-1-Set Register
 * This register sets interrupt enable bits.
 */
union bdk_mdc_int_ena_w1s
{
    uint64_t u;
    struct bdk_mdc_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ecc_error             : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MDC_INT_W1C[ECC_ERROR]. */
#else /* Word 0 - Little Endian */
        uint64_t ecc_error             : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MDC_INT_W1C[ECC_ERROR]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_int_ena_w1s_s cn; */
};
typedef union bdk_mdc_int_ena_w1s bdk_mdc_int_ena_w1s_t;

#define BDK_MDC_INT_ENA_W1S BDK_MDC_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_MDC_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000060ll;
    __bdk_csr_fatal("MDC_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_INT_ENA_W1S bdk_mdc_int_ena_w1s_t
#define bustype_BDK_MDC_INT_ENA_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_INT_ENA_W1S "MDC_INT_ENA_W1S"
#define device_bar_BDK_MDC_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_INT_ENA_W1S 0
#define arguments_BDK_MDC_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RSL) mdc_int_w1c
 *
 * MDC Interrupt Control Register
 */
union bdk_mdc_int_w1c
{
    uint64_t u;
    struct bdk_mdc_int_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ecc_error             : 1;  /**< [  0:  0](R/W1C/H) Set when an ECC error is detected.  MDC_ECC_STATUS contains the error information. */
#else /* Word 0 - Little Endian */
        uint64_t ecc_error             : 1;  /**< [  0:  0](R/W1C/H) Set when an ECC error is detected.  MDC_ECC_STATUS contains the error information. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_int_w1c_s cn; */
};
typedef union bdk_mdc_int_w1c bdk_mdc_int_w1c_t;

#define BDK_MDC_INT_W1C BDK_MDC_INT_W1C_FUNC()
static inline uint64_t BDK_MDC_INT_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_INT_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000048ll;
    __bdk_csr_fatal("MDC_INT_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_INT_W1C bdk_mdc_int_w1c_t
#define bustype_BDK_MDC_INT_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_INT_W1C "MDC_INT_W1C"
#define device_bar_BDK_MDC_INT_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_INT_W1C 0
#define arguments_BDK_MDC_INT_W1C -1,-1,-1,-1

/**
 * Register (RSL) mdc_int_w1s
 *
 * MDC Interrupt Control Register
 * This register sets interrupt bits.
 */
union bdk_mdc_int_w1s
{
    uint64_t u;
    struct bdk_mdc_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ecc_error             : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MDC_INT_W1C[ECC_ERROR]. */
#else /* Word 0 - Little Endian */
        uint64_t ecc_error             : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MDC_INT_W1C[ECC_ERROR]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_int_w1s_s cn; */
};
typedef union bdk_mdc_int_w1s bdk_mdc_int_w1s_t;

#define BDK_MDC_INT_W1S BDK_MDC_INT_W1S_FUNC()
static inline uint64_t BDK_MDC_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000050ll;
    __bdk_csr_fatal("MDC_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_INT_W1S bdk_mdc_int_w1s_t
#define bustype_BDK_MDC_INT_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_INT_W1S "MDC_INT_W1S"
#define device_bar_BDK_MDC_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_INT_W1S 0
#define arguments_BDK_MDC_INT_W1S -1,-1,-1,-1

/**
 * Register (RSL) mdc_pf_msix_pba#
 *
 * MDC MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the MDC_INT_VEC_E
 * enumeration.
 */
union bdk_mdc_pf_msix_pbax
{
    uint64_t u;
    struct bdk_mdc_pf_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MDC_PF_MSIX_VEC()_CTL, enumerated by
                                                                 MDC_INT_VEC_E. Bits that have no associated MDC_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MDC_PF_MSIX_VEC()_CTL, enumerated by
                                                                 MDC_INT_VEC_E. Bits that have no associated MDC_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_pf_msix_pbax_s cn; */
};
typedef union bdk_mdc_pf_msix_pbax bdk_mdc_pf_msix_pbax_t;

static inline uint64_t BDK_MDC_PF_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_PF_MSIX_PBAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a==0))
        return 0x87e0101f0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("MDC_PF_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_PF_MSIX_PBAX(a) bdk_mdc_pf_msix_pbax_t
#define bustype_BDK_MDC_PF_MSIX_PBAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_PF_MSIX_PBAX(a) "MDC_PF_MSIX_PBAX"
#define device_bar_BDK_MDC_PF_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MDC_PF_MSIX_PBAX(a) (a)
#define arguments_BDK_MDC_PF_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (RSL) mdc_pf_msix_vec#_addr
 *
 * MDC MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the MDC_INT_VEC_E enumeration.
 */
union bdk_mdc_pf_msix_vecx_addr
{
    uint64_t u;
    struct bdk_mdc_pf_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MDC_PF_MSIX_VEC()_ADDR, MDC_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MDC_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MDC_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MDC_PF_MSIX_VEC()_ADDR, MDC_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MDC_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MDC_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_pf_msix_vecx_addr_s cn9; */
    /* struct bdk_mdc_pf_msix_vecx_addr_s cn96xxp1; */
    struct bdk_mdc_pf_msix_vecx_addr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's MDC_PF_MSIX_VEC()_ADDR, MDC_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MDC_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_MDC_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set.

                                                                 Also note the following:
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_EN]=1, all secure vectors (including secure
                                                                 VF vectors) will act as if PCCPF/PCCVF_XXX_MSIX_CAP_HDR[MSIXEN]=1,
                                                                 PCCPF/PCCVF_XXX_MSIX_CAP_HDR[FUNM]=0 and PCCPF/PCCVF_XXX_CMD[ME]=1.
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1, all secure vectors (including
                                                                 secure VF vectors) are considered physical, regardless of
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's MDC_PF_MSIX_VEC()_ADDR, MDC_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MDC_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_MDC_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set.

                                                                 Also note the following:
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_EN]=1, all secure vectors (including secure
                                                                 VF vectors) will act as if PCCPF/PCCVF_XXX_MSIX_CAP_HDR[MSIXEN]=1,
                                                                 PCCPF/PCCVF_XXX_MSIX_CAP_HDR[FUNM]=0 and PCCPF/PCCVF_XXX_CMD[ME]=1.
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1, all secure vectors (including
                                                                 secure VF vectors) are considered physical, regardless of
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mdc_pf_msix_vecx_addr_cn96xxp3 cn98xx; */
    /* struct bdk_mdc_pf_msix_vecx_addr_cn96xxp3 cnf95xx; */
    /* struct bdk_mdc_pf_msix_vecx_addr_cn96xxp3 loki; */
};
typedef union bdk_mdc_pf_msix_vecx_addr bdk_mdc_pf_msix_vecx_addr_t;

static inline uint64_t BDK_MDC_PF_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_PF_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a==0))
        return 0x87e010100000ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("MDC_PF_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_PF_MSIX_VECX_ADDR(a) bdk_mdc_pf_msix_vecx_addr_t
#define bustype_BDK_MDC_PF_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_PF_MSIX_VECX_ADDR(a) "MDC_PF_MSIX_VECX_ADDR"
#define device_bar_BDK_MDC_PF_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MDC_PF_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_MDC_PF_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) mdc_pf_msix_vec#_ctl
 *
 * MDC MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the MDC_INT_VEC_E enumeration.
 */
union bdk_mdc_pf_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_mdc_pf_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_pf_msix_vecx_ctl_s cn; */
};
typedef union bdk_mdc_pf_msix_vecx_ctl bdk_mdc_pf_msix_vecx_ctl_t;

static inline uint64_t BDK_MDC_PF_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_PF_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a==0))
        return 0x87e010100008ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("MDC_PF_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_PF_MSIX_VECX_CTL(a) bdk_mdc_pf_msix_vecx_ctl_t
#define bustype_BDK_MDC_PF_MSIX_VECX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_PF_MSIX_VECX_CTL(a) "MDC_PF_MSIX_VECX_CTL"
#define device_bar_BDK_MDC_PF_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MDC_PF_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_MDC_PF_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) mdc_ras_rom#
 *
 * MDC RAM ROM Access Register
 */
union bdk_mdc_ras_romx
{
    uint64_t u;
    struct bdk_mdc_ras_romx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) ROM data representing the RAS information for each MDC memory. See the MDC
                                                                 chapter body text for the format of the ROM.

                                                                 Index 0 indicates the version of the ROM table. A 0x0 at this location indicates
                                                                 this product does not have a ROM.

                                                                 For additional constant data, see each node's MDN_CONST.

                                                                 Internal:
                                                                 When the user wants to access the RAS INFO for cain ID = CID, hub ID = HID and
                                                                 node ID = NID he need to access the ROM 3 times:
                                                                 1) Read the ROM address at (CID+1), to determine CID_base.
                                                                 2) Read the ROM address at (CID_base + HIB) to determine HID_base.
                                                                 3) Read the ROM address at (HID_base + NID) to determine RAS_data.

                                                                 For P1 or other chips without the ROM, this must return 0x0 at index 0. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) ROM data representing the RAS information for each MDC memory. See the MDC
                                                                 chapter body text for the format of the ROM.

                                                                 Index 0 indicates the version of the ROM table. A 0x0 at this location indicates
                                                                 this product does not have a ROM.

                                                                 For additional constant data, see each node's MDN_CONST.

                                                                 Internal:
                                                                 When the user wants to access the RAS INFO for cain ID = CID, hub ID = HID and
                                                                 node ID = NID he need to access the ROM 3 times:
                                                                 1) Read the ROM address at (CID+1), to determine CID_base.
                                                                 2) Read the ROM address at (CID_base + HIB) to determine HID_base.
                                                                 3) Read the ROM address at (HID_base + NID) to determine RAS_data.

                                                                 For P1 or other chips without the ROM, this must return 0x0 at index 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_ras_romx_s cn; */
};
typedef union bdk_mdc_ras_romx bdk_mdc_ras_romx_t;

static inline uint64_t BDK_MDC_RAS_ROMX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_RAS_ROMX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=8191))
        return 0x87e010010000ll + 8ll * ((a) & 0x1fff);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=16383))
        return 0x87e010010000ll + 8ll * ((a) & 0x3fff);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=8191))
        return 0x87e010010000ll + 8ll * ((a) & 0x1fff);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=8191))
        return 0x87e010010000ll + 8ll * ((a) & 0x1fff);
    __bdk_csr_fatal("MDC_RAS_ROMX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_RAS_ROMX(a) bdk_mdc_ras_romx_t
#define bustype_BDK_MDC_RAS_ROMX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_RAS_ROMX(a) "MDC_RAS_ROMX"
#define device_bar_BDK_MDC_RAS_ROMX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_RAS_ROMX(a) (a)
#define arguments_BDK_MDC_RAS_ROMX(a) (a),-1,-1,-1

/**
 * Register (RSL) mdc_scratch
 *
 * INTERNAL: MDC Scratch Register
 */
union bdk_mdc_scratch
{
    uint64_t u;
    struct bdk_mdc_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t scratch               : 64; /**< [ 63:  0](R/W) Scratch register. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 64; /**< [ 63:  0](R/W) Scratch register. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_scratch_s cn; */
};
typedef union bdk_mdc_scratch bdk_mdc_scratch_t;

#define BDK_MDC_SCRATCH BDK_MDC_SCRATCH_FUNC()
static inline uint64_t BDK_MDC_SCRATCH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_SCRATCH_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e0100000f0ll;
    __bdk_csr_fatal("MDC_SCRATCH", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_SCRATCH bdk_mdc_scratch_t
#define bustype_BDK_MDC_SCRATCH BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_SCRATCH "MDC_SCRATCH"
#define device_bar_BDK_MDC_SCRATCH 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_SCRATCH 0
#define arguments_BDK_MDC_SCRATCH -1,-1,-1,-1

/**
 * Register (RSL) mdc_timeouts
 *
 * MDC Protocol Timeout Register
 */
union bdk_mdc_timeouts
{
    uint64_t u;
    struct bdk_mdc_timeouts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t bus_response          : 16; /**< [ 47: 32](R/W) Maximum clock cycles allowed for MDC serial bus transaction.
                                                                 A value of 0x0 disables the timeout. For diagnostic use only. */
        uint64_t reserved_28_31        : 4;
        uint64_t bist_completion       : 28; /**< [ 27:  0](R/W) Maximum clock cycles allowed for BIST to run. A value of 0
                                                                 disables the timeout.  For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t bist_completion       : 28; /**< [ 27:  0](R/W) Maximum clock cycles allowed for BIST to run. A value of 0
                                                                 disables the timeout.  For diagnostic use only. */
        uint64_t reserved_28_31        : 4;
        uint64_t bus_response          : 16; /**< [ 47: 32](R/W) Maximum clock cycles allowed for MDC serial bus transaction.
                                                                 A value of 0x0 disables the timeout. For diagnostic use only. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_timeouts_s cn; */
};
typedef union bdk_mdc_timeouts bdk_mdc_timeouts_t;

#define BDK_MDC_TIMEOUTS BDK_MDC_TIMEOUTS_FUNC()
static inline uint64_t BDK_MDC_TIMEOUTS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_TIMEOUTS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000070ll;
    __bdk_csr_fatal("MDC_TIMEOUTS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_TIMEOUTS bdk_mdc_timeouts_t
#define bustype_BDK_MDC_TIMEOUTS BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_TIMEOUTS "MDC_TIMEOUTS"
#define device_bar_BDK_MDC_TIMEOUTS 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_TIMEOUTS 0
#define arguments_BDK_MDC_TIMEOUTS -1,-1,-1,-1

/**
 * Register (RSL) mdc_win_cmd
 *
 * MDC Windowed Access Command Register
 * Writing to this register initiates a MDC serial bus read or write request
 * according to the [WE] field.  MDC_WIN_DAT handles associated read
 * or write data and it contains a status field MDC_WIN_DAT[PENDING] that
 * indicates whether or not a request is in progress.  Writes
 * to MDC_WIN_CMD are ignored while MDC_WIN_DAT[PENDING] is asserted.
 */
union bdk_mdc_win_cmd
{
    uint64_t u;
    struct bdk_mdc_win_cmd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t chain_id              : 3;  /**< [ 35: 33](R/W) Chain number to send request to.  The transaction will be sent on
                                                                 chain 0 if a [CHAIN_ID] greater than MDC_CONST[MAX_CHAIN_ID] is specified. */
        uint64_t hub_id                : 7;  /**< [ 32: 26](R/W) MDH identifier within MDC_WIN_CMD[CHAIN_ID] to send the request to. */
        uint64_t node_id               : 10; /**< [ 25: 16](R/W) MDN identifier to send request to, within the hub selected with
                                                                 [HUB_ID]. (Attached to a generated or custom SRAM or CAM.) */
        uint64_t reserved_11_15        : 5;
        uint64_t bc_chains             : 1;  /**< [ 10: 10](R/W) Chain broadcast access.
                                                                 0 = Send request to single chain.
                                                                 1 = Send request to all chains. */
        uint64_t bc_nodes              : 1;  /**< [  9:  9](R/W) Node broadcast access,
                                                                 0 = Send request to a single node in the chain(s).
                                                                 1 = Send request to all nodes in the chain(s). */
        uint64_t we                    : 1;  /**< [  8:  8](R/W) Write enable.
                                                                 0 = Read request.
                                                                 1 = Write request. */
        uint64_t csr_id                : 8;  /**< [  7:  0](R/W) CSR identifier. Selects which CSR in the node selected via MDC_WIN_CMD[NODE_ID]. */
#else /* Word 0 - Little Endian */
        uint64_t csr_id                : 8;  /**< [  7:  0](R/W) CSR identifier. Selects which CSR in the node selected via MDC_WIN_CMD[NODE_ID]. */
        uint64_t we                    : 1;  /**< [  8:  8](R/W) Write enable.
                                                                 0 = Read request.
                                                                 1 = Write request. */
        uint64_t bc_nodes              : 1;  /**< [  9:  9](R/W) Node broadcast access,
                                                                 0 = Send request to a single node in the chain(s).
                                                                 1 = Send request to all nodes in the chain(s). */
        uint64_t bc_chains             : 1;  /**< [ 10: 10](R/W) Chain broadcast access.
                                                                 0 = Send request to single chain.
                                                                 1 = Send request to all chains. */
        uint64_t reserved_11_15        : 5;
        uint64_t node_id               : 10; /**< [ 25: 16](R/W) MDN identifier to send request to, within the hub selected with
                                                                 [HUB_ID]. (Attached to a generated or custom SRAM or CAM.) */
        uint64_t hub_id                : 7;  /**< [ 32: 26](R/W) MDH identifier within MDC_WIN_CMD[CHAIN_ID] to send the request to. */
        uint64_t chain_id              : 3;  /**< [ 35: 33](R/W) Chain number to send request to.  The transaction will be sent on
                                                                 chain 0 if a [CHAIN_ID] greater than MDC_CONST[MAX_CHAIN_ID] is specified. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_win_cmd_s cn; */
};
typedef union bdk_mdc_win_cmd bdk_mdc_win_cmd_t;

#define BDK_MDC_WIN_CMD BDK_MDC_WIN_CMD_FUNC()
static inline uint64_t BDK_MDC_WIN_CMD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_WIN_CMD_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000010ll;
    __bdk_csr_fatal("MDC_WIN_CMD", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_WIN_CMD bdk_mdc_win_cmd_t
#define bustype_BDK_MDC_WIN_CMD BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_WIN_CMD "MDC_WIN_CMD"
#define device_bar_BDK_MDC_WIN_CMD 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_WIN_CMD 0
#define arguments_BDK_MDC_WIN_CMD -1,-1,-1,-1

/**
 * Register (RSL) mdc_win_dat
 *
 * MDC Windowed Access Read Data Register
 */
union bdk_mdc_win_dat
{
    uint64_t u;
    struct bdk_mdc_win_dat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t timeout               : 1;  /**< [ 34: 34](RO/H) Request timed out.  Both read and write requests receive a completion
                                                                 (i.e. response) in the MDC serial protocol.  [TIMEOUT] is asserted if a
                                                                 request does not receive a completion within 64,000 clock cycles. */
        uint64_t pending               : 1;  /**< [ 33: 33](RO/H) Response pending.  A request has been transmitted into the MDC
                                                                 serial chain and a completion is expected.  Software should poll this
                                                                 field to determine when a request has been serviced. */
        uint64_t read_valid            : 1;  /**< [ 32: 32](RO/H) Read data valid. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W/H) CSR read or write data. When used for write data the value must be set
                                                                 before the write command is given in MDC_WIN_CMD.  When used for read
                                                                 data the value is valid when [PENDING] is cleared and
                                                                 [READ_VALID] is set. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W/H) CSR read or write data. When used for write data the value must be set
                                                                 before the write command is given in MDC_WIN_CMD.  When used for read
                                                                 data the value is valid when [PENDING] is cleared and
                                                                 [READ_VALID] is set. */
        uint64_t read_valid            : 1;  /**< [ 32: 32](RO/H) Read data valid. */
        uint64_t pending               : 1;  /**< [ 33: 33](RO/H) Response pending.  A request has been transmitted into the MDC
                                                                 serial chain and a completion is expected.  Software should poll this
                                                                 field to determine when a request has been serviced. */
        uint64_t timeout               : 1;  /**< [ 34: 34](RO/H) Request timed out.  Both read and write requests receive a completion
                                                                 (i.e. response) in the MDC serial protocol.  [TIMEOUT] is asserted if a
                                                                 request does not receive a completion within 64,000 clock cycles. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mdc_win_dat_s cn; */
};
typedef union bdk_mdc_win_dat bdk_mdc_win_dat_t;

#define BDK_MDC_WIN_DAT BDK_MDC_WIN_DAT_FUNC()
static inline uint64_t BDK_MDC_WIN_DAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MDC_WIN_DAT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e010000018ll;
    __bdk_csr_fatal("MDC_WIN_DAT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MDC_WIN_DAT bdk_mdc_win_dat_t
#define bustype_BDK_MDC_WIN_DAT BDK_CSR_TYPE_RSL
#define basename_BDK_MDC_WIN_DAT "MDC_WIN_DAT"
#define device_bar_BDK_MDC_WIN_DAT 0x0 /* PF_BAR0 */
#define busnum_BDK_MDC_WIN_DAT 0
#define arguments_BDK_MDC_WIN_DAT -1,-1,-1,-1

#endif /* __BDK_CSRS_MDC_H__ */
