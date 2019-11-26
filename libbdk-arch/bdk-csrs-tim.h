#ifndef __BDK_CSRS_TIM_H__
#define __BDK_CSRS_TIM_H__
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
 * OcteonTX TIM.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration tim_af_int_vec_e
 *
 * TIM AF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_TIM_AF_INT_VEC_E_BKT_SKIP_INTX(a) (0 + (a))
#define BDK_TIM_AF_INT_VEC_E_RVU_INT (4)

/**
 * Enumeration tim_bar_e
 *
 * TIM Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_TIM_BAR_E_TIM_PF_BAR0 (0x858000000000ll)
#define BDK_TIM_BAR_E_TIM_PF_BAR0_SIZE 0x100000ull
#define BDK_TIM_BAR_E_TIM_PF_BAR4 (0x858000f00000ll)
#define BDK_TIM_BAR_E_TIM_PF_BAR4_SIZE 0x100000ull
#define BDK_TIM_BAR_E_TIM_VFX_BAR0(a) (0x858010000000ll + 0x100000ll * (a))
#define BDK_TIM_BAR_E_TIM_VFX_BAR0_SIZE 0x100000ull
#define BDK_TIM_BAR_E_TIM_VFX_BAR4(a) (0x858020000000ll + 0x100000ll * (a))
#define BDK_TIM_BAR_E_TIM_VFX_BAR4_SIZE 0x100000ull

/**
 * Enumeration tim_clk_srcs_e
 *
 * TIM Clock Sources Enumeration
 * Enumerates TIM_AF_RING()_CTL1[CLK_SRC].
 */
#define BDK_TIM_CLK_SRCS_E_GPIO (1)
#define BDK_TIM_CLK_SRCS_E_GTI (2)
#define BDK_TIM_CLK_SRCS_E_PTP (3)
#define BDK_TIM_CLK_SRCS_E_SCLK (0)
#define BDK_TIM_CLK_SRCS_E_TENNS (0)

/**
 * Enumeration tim_lf_int_vec_e
 *
 * TIM LF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_TIM_LF_INT_VEC_E_NRSPERR_INT (0)
#define BDK_TIM_LF_INT_VEC_E_RAS_INT (1)

/**
 * Enumeration tim_pf_int_vec_e
 *
 * TIM PF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_TIM_PF_INT_VEC_E_BKT_SKIP_INT (1)
#define BDK_TIM_PF_INT_VEC_E_ECCERR (0)

/**
 * Enumeration tim_vf_int_vec_e
 *
 * TIM VF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_TIM_VF_INT_VEC_E_NRSPERR (0)

/**
 * Structure tim_mem_bucket_s
 *
 * TIM Memory Bucket Structure
 */
union bdk_tim_mem_bucket_s
{
    uint64_t u[4];
    struct bdk_tim_mem_bucket_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t first_chunk           : 64; /**< [ 63:  0] Pointer to first chunk's FPA buffer. \<63:49,2:0\> must be zero. Updated by
                                                                 software when a first chunk is added. Read by timer hardware. */
#else /* Word 0 - Little Endian */
        uint64_t first_chunk           : 64; /**< [ 63:  0] Pointer to first chunk's FPA buffer. \<63:49,2:0\> must be zero. Updated by
                                                                 software when a first chunk is added. Read by timer hardware. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t chunk_remainder       : 16; /**< [127:112] Number of remaining entries for software to enter in the list. This number
                                                                 should always be smaller than chunk size. Software decrements this field
                                                                 whenever software adds an entry, and increments it by the number of entries in a
                                                                 chunk when a new FPA chunk is appended. If [NUM_ENTRIES] is nonzero, and
                                                                 TIM_RING()_CTL1[ENA_PRD] is clear, written to zeros by hardware when hardware
                                                                 begins processing a bucket.

                                                                 Internal:
                                                                 Field must include bit w1\<63\> as it may underflow negative. */
        uint64_t lock                  : 8;  /**< [111:104] Count of how many outstanding software threads are working on the bucket.
                                                                 The field must be atomically incremented and decremented by software.
                                                                 Note that this allows up to 255 threads doing parallel operations.

                                                                 Hardware never writes this byte.

                                                                 Internal:
                                                                 Cannot overflow/underflow. MSB msut be on 8/16/32/64-bit boundary. */
        uint64_t reserved_99_103       : 5;
        uint64_t bsk                   : 1;  /**< [ 98: 98] Bucket skip indicator. Set by hardware to indicate to software that hardware has
                                                                 skipped processing the bucket because it was unable to gain the bucket lock.

                                                                 Cleared by the entity that traverses the bucket (either software or hardware). */
        uint64_t hbt                   : 1;  /**< [ 97: 97] Hardware bucket traversal indicator.
                                                                 Indicates that hardware is currently attempting to traverse the bucket. */
        uint64_t sbt                   : 1;  /**< [ 96: 96] Software bucket traversal indicator.
                                                                 Indicates that software is currently attempting to traverse the bucket. */
        uint64_t num_entries           : 32; /**< [ 95: 64] Number of entries that software added to the list. Software increments whenever
                                                                 software adds an entry. When TIM_RING()_CTL1[ENA_PRD] is clear, written to zeros
                                                                 by hardware when hardware begins processing this bucket. (As it is zeroed when
                                                                 the list processing begins, software cannot take this zeroing as an indication
                                                                 the list has finished processing.) */
#else /* Word 1 - Little Endian */
        uint64_t num_entries           : 32; /**< [ 95: 64] Number of entries that software added to the list. Software increments whenever
                                                                 software adds an entry. When TIM_RING()_CTL1[ENA_PRD] is clear, written to zeros
                                                                 by hardware when hardware begins processing this bucket. (As it is zeroed when
                                                                 the list processing begins, software cannot take this zeroing as an indication
                                                                 the list has finished processing.) */
        uint64_t sbt                   : 1;  /**< [ 96: 96] Software bucket traversal indicator.
                                                                 Indicates that software is currently attempting to traverse the bucket. */
        uint64_t hbt                   : 1;  /**< [ 97: 97] Hardware bucket traversal indicator.
                                                                 Indicates that hardware is currently attempting to traverse the bucket. */
        uint64_t bsk                   : 1;  /**< [ 98: 98] Bucket skip indicator. Set by hardware to indicate to software that hardware has
                                                                 skipped processing the bucket because it was unable to gain the bucket lock.

                                                                 Cleared by the entity that traverses the bucket (either software or hardware). */
        uint64_t reserved_99_103       : 5;
        uint64_t lock                  : 8;  /**< [111:104] Count of how many outstanding software threads are working on the bucket.
                                                                 The field must be atomically incremented and decremented by software.
                                                                 Note that this allows up to 255 threads doing parallel operations.

                                                                 Hardware never writes this byte.

                                                                 Internal:
                                                                 Cannot overflow/underflow. MSB msut be on 8/16/32/64-bit boundary. */
        uint64_t chunk_remainder       : 16; /**< [127:112] Number of remaining entries for software to enter in the list. This number
                                                                 should always be smaller than chunk size. Software decrements this field
                                                                 whenever software adds an entry, and increments it by the number of entries in a
                                                                 chunk when a new FPA chunk is appended. If [NUM_ENTRIES] is nonzero, and
                                                                 TIM_RING()_CTL1[ENA_PRD] is clear, written to zeros by hardware when hardware
                                                                 begins processing a bucket.

                                                                 Internal:
                                                                 Field must include bit w1\<63\> as it may underflow negative. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t current_chunk         : 64; /**< [191:128] Not used by timer hardware. Points to the last chunk in the list and is updated by
                                                                 software whenever chunk is added to the list. */
#else /* Word 2 - Little Endian */
        uint64_t current_chunk         : 64; /**< [191:128] Not used by timer hardware. Points to the last chunk in the list and is updated by
                                                                 software whenever chunk is added to the list. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t pad                   : 64; /**< [255:192] Padding, not used by hardware. */
#else /* Word 3 - Little Endian */
        uint64_t pad                   : 64; /**< [255:192] Padding, not used by hardware. */
#endif /* Word 3 - End */
    } s;
    /* struct bdk_tim_mem_bucket_s_s cn8; */
    struct bdk_tim_mem_bucket_s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t first_chunk           : 64; /**< [ 63:  0] Pointer to first chunk memory. \<63:49,2:0\> must be zero. Updated by software when a first
                                                                 chunk is added. Read by timer hardware. */
#else /* Word 0 - Little Endian */
        uint64_t first_chunk           : 64; /**< [ 63:  0] Pointer to first chunk memory. \<63:49,2:0\> must be zero. Updated by software when a first
                                                                 chunk is added. Read by timer hardware. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t chunk_remainder       : 16; /**< [127:112] Number of remaining entries for software to enter in the list. This number should always
                                                                 be smaller than chunk size. This field is decremented by software whenever software adds
                                                                 an entry. If [NUM_ENTRIES] is nonzero, written to zeros by hardware when hardware
                                                                 processes the entry unless TIM_AF_RING()_CTL1[ENA_PRD] is set.

                                                                 Internal:
                                                                 Field must include bit w1\<63\> as it may underflow negative. */
        uint64_t lock                  : 8;  /**< [111:104] Count of how many outstanding software threads are working on the bucket.
                                                                 The field must be atomically incremented and decremented by software.
                                                                 Note that this allows up to 256 threads doing parallel operations.

                                                                 Hardware never writes this byte.

                                                                 Internal:
                                                                 Cannot overflow/underflow. MSB msut be on 8/16/32/64-bit boundary. */
        uint64_t reserved_99_103       : 5;
        uint64_t bsk                   : 1;  /**< [ 98: 98] Bucket skip indicator. Set by hardware to indicate to software that hardware has
                                                                 skipped processing the bucket because it was unable to gain the bucket lock.

                                                                 Cleared by the entity that traverses the bucket (either software or hardware). */
        uint64_t hbt                   : 1;  /**< [ 97: 97] Hardware bucket traversal indicator.
                                                                 Indicates that hardware is currently attempting to traverse the bucket. */
        uint64_t sbt                   : 1;  /**< [ 96: 96] Software bucket traversal indicator.
                                                                 Indicates that software is currently attempting to traverse the bucket. */
        uint64_t num_entries           : 32; /**< [ 95: 64] Number of entries that software added to the list. Incremented whenever software adds an
                                                                 entry. Written to zeros by hardware when hardware processes the list unless
                                                                 TIM_AF_RING()_CTL1[ENA_PRD] is set. */
#else /* Word 1 - Little Endian */
        uint64_t num_entries           : 32; /**< [ 95: 64] Number of entries that software added to the list. Incremented whenever software adds an
                                                                 entry. Written to zeros by hardware when hardware processes the list unless
                                                                 TIM_AF_RING()_CTL1[ENA_PRD] is set. */
        uint64_t sbt                   : 1;  /**< [ 96: 96] Software bucket traversal indicator.
                                                                 Indicates that software is currently attempting to traverse the bucket. */
        uint64_t hbt                   : 1;  /**< [ 97: 97] Hardware bucket traversal indicator.
                                                                 Indicates that hardware is currently attempting to traverse the bucket. */
        uint64_t bsk                   : 1;  /**< [ 98: 98] Bucket skip indicator. Set by hardware to indicate to software that hardware has
                                                                 skipped processing the bucket because it was unable to gain the bucket lock.

                                                                 Cleared by the entity that traverses the bucket (either software or hardware). */
        uint64_t reserved_99_103       : 5;
        uint64_t lock                  : 8;  /**< [111:104] Count of how many outstanding software threads are working on the bucket.
                                                                 The field must be atomically incremented and decremented by software.
                                                                 Note that this allows up to 256 threads doing parallel operations.

                                                                 Hardware never writes this byte.

                                                                 Internal:
                                                                 Cannot overflow/underflow. MSB msut be on 8/16/32/64-bit boundary. */
        uint64_t chunk_remainder       : 16; /**< [127:112] Number of remaining entries for software to enter in the list. This number should always
                                                                 be smaller than chunk size. This field is decremented by software whenever software adds
                                                                 an entry. If [NUM_ENTRIES] is nonzero, written to zeros by hardware when hardware
                                                                 processes the entry unless TIM_AF_RING()_CTL1[ENA_PRD] is set.

                                                                 Internal:
                                                                 Field must include bit w1\<63\> as it may underflow negative. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t current_chunk         : 64; /**< [191:128] Not used by timer hardware. Points to the last chunk in the list and is updated by
                                                                 software whenever chunk is added to the list. */
#else /* Word 2 - Little Endian */
        uint64_t current_chunk         : 64; /**< [191:128] Not used by timer hardware. Points to the last chunk in the list and is updated by
                                                                 software whenever chunk is added to the list. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t pad                   : 64; /**< [255:192] Padding, not used by hardware. */
#else /* Word 3 - Little Endian */
        uint64_t pad                   : 64; /**< [255:192] Padding, not used by hardware. */
#endif /* Word 3 - End */
    } cn9;
};

/**
 * Structure tim_mem_entry_s
 *
 * TIM Memory Entry Structure
 */
union bdk_tim_mem_entry_s
{
    uint64_t u[2];
    struct bdk_tim_mem_entry_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t grp                   : 10; /**< [ 43: 34] SSO guest-group.
                                                                 For the SSO to not discard the add-work request, SSO_PF_MAP() must map
                                                                 [GRP] and TIM_VRING()_GMCTL[GMID] as valid. */
        uint64_t tt                    : 2;  /**< [ 33: 32] SSO tag type.  Enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0] SSO tag. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0] SSO tag. */
        uint64_t tt                    : 2;  /**< [ 33: 32] SSO tag type.  Enumerated by SSO_TT_E. */
        uint64_t grp                   : 10; /**< [ 43: 34] SSO guest-group.
                                                                 For the SSO to not discard the add-work request, SSO_PF_MAP() must map
                                                                 [GRP] and TIM_VRING()_GMCTL[GMID] as valid. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t wqp                   : 64; /**< [127: 64] Pointer to a work-queue entry. An all-zero [WQP] is not sent to the SSO and may
                                                                 be used as a NOP, e.g. to indicate a deleted entry. \<2:0\> must be zero.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:49\> are ignored by hardware; software should
                                                                 store a sign-extended [WQP]\<48\> for forward compatibility. */
#else /* Word 1 - Little Endian */
        uint64_t wqp                   : 64; /**< [127: 64] Pointer to a work-queue entry. An all-zero [WQP] is not sent to the SSO and may
                                                                 be used as a NOP, e.g. to indicate a deleted entry. \<2:0\> must be zero.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:49\> are ignored by hardware; software should
                                                                 store a sign-extended [WQP]\<48\> for forward compatibility. */
#endif /* Word 1 - End */
    } s;
    /* struct bdk_tim_mem_entry_s_s cn8; */
    struct bdk_tim_mem_entry_s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t grp                   : 10; /**< [ 43: 34] SSO guest group.
                                                                 For the SSO to not discard the add-work request, TIM_AF_RING()_GMCTL[SSO_PF_FUNC] must be legal. */
        uint64_t tt                    : 2;  /**< [ 33: 32] SSO tag type.  Enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0] SSO tag. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0] SSO tag. */
        uint64_t tt                    : 2;  /**< [ 33: 32] SSO tag type.  Enumerated by SSO_TT_E. */
        uint64_t grp                   : 10; /**< [ 43: 34] SSO guest group.
                                                                 For the SSO to not discard the add-work request, TIM_AF_RING()_GMCTL[SSO_PF_FUNC] must be legal. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t wqp                   : 64; /**< [127: 64] Pointer to a work-queue entry. An all-zero [WQP] is not sent to the SSO and may
                                                                 be used as a NOP, e.g. to indicate a deleted entry. \<2:0\> must be zero.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:53\> are ignored by hardware; software should
                                                                 store a sign-extended [WQP]\<52\> for forward compatibility. */
#else /* Word 1 - Little Endian */
        uint64_t wqp                   : 64; /**< [127: 64] Pointer to a work-queue entry. An all-zero [WQP] is not sent to the SSO and may
                                                                 be used as a NOP, e.g. to indicate a deleted entry. \<2:0\> must be zero.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:53\> are ignored by hardware; software should
                                                                 store a sign-extended [WQP]\<52\> for forward compatibility. */
#endif /* Word 1 - End */
    } cn9;
};

/**
 * Register (RVU_PF_BAR0) tim_af_active_pc
 *
 * TIM AF Active Cycles Register
 */
union bdk_tim_af_active_pc
{
    uint64_t u;
    struct bdk_tim_af_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the conditional clocks are active. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](R/W/H) Counts every coprocessor-clock cycle that the conditional clocks are active. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_active_pc_s cn; */
};
typedef union bdk_tim_af_active_pc bdk_tim_af_active_pc_t;

#define BDK_TIM_AF_ACTIVE_PC BDK_TIM_AF_ACTIVE_PC_FUNC()
static inline uint64_t BDK_TIM_AF_ACTIVE_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_ACTIVE_PC_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090030070ll;
    __bdk_csr_fatal("TIM_AF_ACTIVE_PC", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_ACTIVE_PC bdk_tim_af_active_pc_t
#define bustype_BDK_TIM_AF_ACTIVE_PC BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_ACTIVE_PC "TIM_AF_ACTIVE_PC"
#define device_bar_BDK_TIM_AF_ACTIVE_PC 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_ACTIVE_PC 0
#define arguments_BDK_TIM_AF_ACTIVE_PC -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_bar2_alias#
 *
 * INTERNAL: TIM Admin Function  BAR2 Alias Registers
 *
 * These registers alias to the TIM BAR2 registers for the PF and function
 * selected by TIM_AF_BAR2_SEL[PF_FUNC].
 *
 * Internal:
 * Not implemented. Placeholder for bug33464.
 */
union bdk_tim_af_bar2_aliasx
{
    uint64_t u;
    struct bdk_tim_af_bar2_aliasx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Aliased register data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Aliased register data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_bar2_aliasx_s cn; */
};
typedef union bdk_tim_af_bar2_aliasx bdk_tim_af_bar2_aliasx_t;

static inline uint64_t BDK_TIM_AF_BAR2_ALIASX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_BAR2_ALIASX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=131071))
        return 0x840099100000ll + 8ll * ((a) & 0x1ffff);
    __bdk_csr_fatal("TIM_AF_BAR2_ALIASX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_BAR2_ALIASX(a) bdk_tim_af_bar2_aliasx_t
#define bustype_BDK_TIM_AF_BAR2_ALIASX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_BAR2_ALIASX(a) "TIM_AF_BAR2_ALIASX"
#define device_bar_BDK_TIM_AF_BAR2_ALIASX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_BAR2_ALIASX(a) (a)
#define arguments_BDK_TIM_AF_BAR2_ALIASX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_bar2_sel
 *
 * INTERNAL: TIM Admin Function BAR2 Select Register
 *
 * This register configures BAR2 accesses from the TIM_AF_BAR2_ALIAS() registers in BAR0.
 * Internal:
 * Not implemented. Placeholder for bug33464.
 */
union bdk_tim_af_bar2_sel
{
    uint64_t u;
    struct bdk_tim_af_bar2_sel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t alias_ena             : 1;  /**< [ 16: 16](R/W) Enable BAR2 register accesses from the AF BAR2 alias registers in BAR0. */
        uint64_t alias_pf_func         : 16; /**< [ 15:  0](R/W) PF and function whose BAR2 registers may be accessed from the AF BAR2 alias
                                                                 registers. Format specified by RVU_PF_FUNC_S. */
#else /* Word 0 - Little Endian */
        uint64_t alias_pf_func         : 16; /**< [ 15:  0](R/W) PF and function whose BAR2 registers may be accessed from the AF BAR2 alias
                                                                 registers. Format specified by RVU_PF_FUNC_S. */
        uint64_t alias_ena             : 1;  /**< [ 16: 16](R/W) Enable BAR2 register accesses from the AF BAR2 alias registers in BAR0. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_bar2_sel_s cn; */
};
typedef union bdk_tim_af_bar2_sel bdk_tim_af_bar2_sel_t;

#define BDK_TIM_AF_BAR2_SEL BDK_TIM_AF_BAR2_SEL_FUNC()
static inline uint64_t BDK_TIM_AF_BAR2_SEL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_BAR2_SEL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840099000000ll;
    __bdk_csr_fatal("TIM_AF_BAR2_SEL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_BAR2_SEL bdk_tim_af_bar2_sel_t
#define bustype_BDK_TIM_AF_BAR2_SEL BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_BAR2_SEL "TIM_AF_BAR2_SEL"
#define device_bar_BDK_TIM_AF_BAR2_SEL 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_BAR2_SEL 0
#define arguments_BDK_TIM_AF_BAR2_SEL -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_bkt_skip#_int_status
 *
 * TIM BKT_SKIP_INT Ring Status Register
 */
union bdk_tim_af_bkt_skipx_int_status
{
    uint64_t u;
    struct bdk_tim_af_bkt_skipx_int_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t bkt_skip_id           : 20; /**< [ 19:  0](RO/H) When TIM_AF_BKT_SKIP_INT() gets set, this field reflects the bucket that was skipped
                                                                 for the corresponding ring. For diagnostic use only, as only one ring's status is kept. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip_id           : 20; /**< [ 19:  0](RO/H) When TIM_AF_BKT_SKIP_INT() gets set, this field reflects the bucket that was skipped
                                                                 for the corresponding ring. For diagnostic use only, as only one ring's status is kept. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_bkt_skipx_int_status_s cn; */
};
typedef union bdk_tim_af_bkt_skipx_int_status bdk_tim_af_bkt_skipx_int_status_t;

static inline uint64_t BDK_TIM_AF_BKT_SKIPX_INT_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_BKT_SKIPX_INT_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840090044000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("TIM_AF_BKT_SKIPX_INT_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_BKT_SKIPX_INT_STATUS(a) bdk_tim_af_bkt_skipx_int_status_t
#define bustype_BDK_TIM_AF_BKT_SKIPX_INT_STATUS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_BKT_SKIPX_INT_STATUS(a) "TIM_AF_BKT_SKIPX_INT_STATUS"
#define device_bar_BDK_TIM_AF_BKT_SKIPX_INT_STATUS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_BKT_SKIPX_INT_STATUS(a) (a)
#define arguments_BDK_TIM_AF_BKT_SKIPX_INT_STATUS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_bkt_skip_int#
 *
 * TIM AF Bucket Skip Interrupt Register
 */
union bdk_tim_af_bkt_skip_intx
{
    uint64_t u;
    struct bdk_tim_af_bkt_skip_intx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1C/H) Interrupt bit per ring. Each bit corresponds to rings 255:0 respectively.
                                                                 If set, at least one bucket was skipped by hardware, when a ring has expired.
                                                                 Hardware sets this when TIM attempted traversal but the bucket's
                                                                 TIM_MEM_BUCKET_S[SBT] was set or TIM_MEM_BUCKET_S[LOCK] was nonzero. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1C/H) Interrupt bit per ring. Each bit corresponds to rings 255:0 respectively.
                                                                 If set, at least one bucket was skipped by hardware, when a ring has expired.
                                                                 Hardware sets this when TIM attempted traversal but the bucket's
                                                                 TIM_MEM_BUCKET_S[SBT] was set or TIM_MEM_BUCKET_S[LOCK] was nonzero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_bkt_skip_intx_s cn; */
};
typedef union bdk_tim_af_bkt_skip_intx bdk_tim_af_bkt_skip_intx_t;

static inline uint64_t BDK_TIM_AF_BKT_SKIP_INTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_BKT_SKIP_INTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840090010000ll + 0x20ll * ((a) & 0x3);
    __bdk_csr_fatal("TIM_AF_BKT_SKIP_INTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_BKT_SKIP_INTX(a) bdk_tim_af_bkt_skip_intx_t
#define bustype_BDK_TIM_AF_BKT_SKIP_INTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_BKT_SKIP_INTX(a) "TIM_AF_BKT_SKIP_INTX"
#define device_bar_BDK_TIM_AF_BKT_SKIP_INTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_BKT_SKIP_INTX(a) (a)
#define arguments_BDK_TIM_AF_BKT_SKIP_INTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_bkt_skip_int_ena_w1c#
 *
 * TIM AF Bucket Skip Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_tim_af_bkt_skip_int_ena_w1cx
{
    uint64_t u;
    struct bdk_tim_af_bkt_skip_int_ena_w1cx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for TIM_AF_BKT_SKIP_INT(0..3)[BKT_SKIP]. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for TIM_AF_BKT_SKIP_INT(0..3)[BKT_SKIP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_bkt_skip_int_ena_w1cx_s cn; */
};
typedef union bdk_tim_af_bkt_skip_int_ena_w1cx bdk_tim_af_bkt_skip_int_ena_w1cx_t;

static inline uint64_t BDK_TIM_AF_BKT_SKIP_INT_ENA_W1CX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_BKT_SKIP_INT_ENA_W1CX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840090010018ll + 0x20ll * ((a) & 0x3);
    __bdk_csr_fatal("TIM_AF_BKT_SKIP_INT_ENA_W1CX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1CX(a) bdk_tim_af_bkt_skip_int_ena_w1cx_t
#define bustype_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1CX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1CX(a) "TIM_AF_BKT_SKIP_INT_ENA_W1CX"
#define device_bar_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1CX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1CX(a) (a)
#define arguments_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1CX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_bkt_skip_int_ena_w1s#
 *
 * TIM AF Bucket Skip Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_tim_af_bkt_skip_int_ena_w1sx
{
    uint64_t u;
    struct bdk_tim_af_bkt_skip_int_ena_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for TIM_AF_BKT_SKIP_INT(0..3)[BKT_SKIP]. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for TIM_AF_BKT_SKIP_INT(0..3)[BKT_SKIP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_bkt_skip_int_ena_w1sx_s cn; */
};
typedef union bdk_tim_af_bkt_skip_int_ena_w1sx bdk_tim_af_bkt_skip_int_ena_w1sx_t;

static inline uint64_t BDK_TIM_AF_BKT_SKIP_INT_ENA_W1SX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_BKT_SKIP_INT_ENA_W1SX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840090010010ll + 0x20ll * ((a) & 0x3);
    __bdk_csr_fatal("TIM_AF_BKT_SKIP_INT_ENA_W1SX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1SX(a) bdk_tim_af_bkt_skip_int_ena_w1sx_t
#define bustype_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1SX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1SX(a) "TIM_AF_BKT_SKIP_INT_ENA_W1SX"
#define device_bar_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1SX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1SX(a) (a)
#define arguments_BDK_TIM_AF_BKT_SKIP_INT_ENA_W1SX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_bkt_skip_int_w1s#
 *
 * TIM AF Bucket Skip Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_tim_af_bkt_skip_int_w1sx
{
    uint64_t u;
    struct bdk_tim_af_bkt_skip_int_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1S/H) Reads or sets TIM_AF_BKT_SKIP_INT(0..3)[BKT_SKIP]. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1S/H) Reads or sets TIM_AF_BKT_SKIP_INT(0..3)[BKT_SKIP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_bkt_skip_int_w1sx_s cn; */
};
typedef union bdk_tim_af_bkt_skip_int_w1sx bdk_tim_af_bkt_skip_int_w1sx_t;

static inline uint64_t BDK_TIM_AF_BKT_SKIP_INT_W1SX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_BKT_SKIP_INT_W1SX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840090010008ll + 0x20ll * ((a) & 0x3);
    __bdk_csr_fatal("TIM_AF_BKT_SKIP_INT_W1SX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_BKT_SKIP_INT_W1SX(a) bdk_tim_af_bkt_skip_int_w1sx_t
#define bustype_BDK_TIM_AF_BKT_SKIP_INT_W1SX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_BKT_SKIP_INT_W1SX(a) "TIM_AF_BKT_SKIP_INT_W1SX"
#define device_bar_BDK_TIM_AF_BKT_SKIP_INT_W1SX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_BKT_SKIP_INT_W1SX(a) (a)
#define arguments_BDK_TIM_AF_BKT_SKIP_INT_W1SX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_blk_rst
 *
 * TIM AF Block Reset Registers
 */
union bdk_tim_af_blk_rst
{
    uint64_t u;
    struct bdk_tim_af_blk_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When one, the block is busy completing reset. No access except the reading of
                                                                 this bit should occur to the block until this is clear. */
        uint64_t reserved_1_62         : 62;
        uint64_t rst                   : 1;  /**< [  0:  0](WO/H) Write one to reset the block, except for privileged AF registers in PF BAR0
                                                                 (block_PRIV_*). Software must ensure that all block activity is quiesced before
                                                                 writing 1. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 1;  /**< [  0:  0](WO/H) Write one to reset the block, except for privileged AF registers in PF BAR0
                                                                 (block_PRIV_*). Software must ensure that all block activity is quiesced before
                                                                 writing 1. */
        uint64_t reserved_1_62         : 62;
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) When one, the block is busy completing reset. No access except the reading of
                                                                 this bit should occur to the block until this is clear. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_blk_rst_s cn; */
};
typedef union bdk_tim_af_blk_rst bdk_tim_af_blk_rst_t;

#define BDK_TIM_AF_BLK_RST BDK_TIM_AF_BLK_RST_FUNC()
static inline uint64_t BDK_TIM_AF_BLK_RST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_BLK_RST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000010ll;
    __bdk_csr_fatal("TIM_AF_BLK_RST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_BLK_RST bdk_tim_af_blk_rst_t
#define bustype_BDK_TIM_AF_BLK_RST BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_BLK_RST "TIM_AF_BLK_RST"
#define device_bar_BDK_TIM_AF_BLK_RST 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_BLK_RST 0
#define arguments_BDK_TIM_AF_BLK_RST -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_bp_test#
 *
 * INTERNAL: TIM AF Backpressure Test Register
 */
union bdk_tim_af_bp_testx
{
    uint64_t u;
    struct bdk_tim_af_bp_testx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 BP_TEST(0).\<63\> = Reserved.
                                                                 BP_TEST(0).\<62\> = NCBI CR path to NCBO request interface.
                                                                 BP_TEST(0).\<61\> = NPA FIFO.
                                                                 BP_TEST(0).\<60\> = WQE FIFO.
                                                                 BP_TEST(1..8).\<63\> = Reserved.
                                                                 BP_TEST(1..8).\<62\> = Reserved.
                                                                 BP_TEST(1..8).\<61\> = NCBI P path to STA interface(0..7).
                                                                 BP_TEST(1..8).\<60\> = NCBI NP path to STA interface(0..7). */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 BP_TEST(0).\<63\> = Reserved.
                                                                 BP_TEST(0).\<62\> = NCBI CR path to NCBO request interface.
                                                                 BP_TEST(0).\<61\> = NPA FIFO.
                                                                 BP_TEST(0).\<60\> = WQE FIFO.
                                                                 BP_TEST(1..8).\<63\> = Reserved.
                                                                 BP_TEST(1..8).\<62\> = Reserved.
                                                                 BP_TEST(1..8).\<61\> = NCBI P path to STA interface(0..7).
                                                                 BP_TEST(1..8).\<60\> = NCBI NP path to STA interface(0..7). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_bp_testx_s cn; */
};
typedef union bdk_tim_af_bp_testx bdk_tim_af_bp_testx_t;

static inline uint64_t BDK_TIM_AF_BP_TESTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_BP_TESTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=8))
        return 0x840090034000ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("TIM_AF_BP_TESTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_BP_TESTX(a) bdk_tim_af_bp_testx_t
#define bustype_BDK_TIM_AF_BP_TESTX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_BP_TESTX(a) "TIM_AF_BP_TESTX"
#define device_bar_BDK_TIM_AF_BP_TESTX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_BP_TESTX(a) (a)
#define arguments_BDK_TIM_AF_BP_TESTX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_const
 *
 * TIM Const Register
 */
union bdk_tim_af_const
{
    uint64_t u;
    struct bdk_tim_af_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t sta_n                 : 8;  /**< [ 23: 16](RO) Number of traverse engines. */
        uint64_t ring_n                : 16; /**< [ 15:  0](RO) Number of rings. */
#else /* Word 0 - Little Endian */
        uint64_t ring_n                : 16; /**< [ 15:  0](RO) Number of rings. */
        uint64_t sta_n                 : 8;  /**< [ 23: 16](RO) Number of traverse engines. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_const_s cn; */
};
typedef union bdk_tim_af_const bdk_tim_af_const_t;

#define BDK_TIM_AF_CONST BDK_TIM_AF_CONST_FUNC()
static inline uint64_t BDK_TIM_AF_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_CONST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000090ll;
    __bdk_csr_fatal("TIM_AF_CONST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_CONST bdk_tim_af_const_t
#define bustype_BDK_TIM_AF_CONST BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_CONST "TIM_AF_CONST"
#define device_bar_BDK_TIM_AF_CONST 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_CONST 0
#define arguments_BDK_TIM_AF_CONST -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_dbg
 *
 * TIM AF Debug Register
 */
union bdk_tim_af_dbg
{
    uint64_t u;
    struct bdk_tim_af_dbg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqe_fifo_alloc_level  : 10; /**< [ 63: 54](RO/H) SSO WQE FIFO allocation level. */
        uint64_t reserved_47_53        : 7;
        uint64_t npa_fifo_level        : 5;  /**< [ 46: 42](RO/H) NPA FIFO level. */
        uint64_t reserved_30_41        : 12;
        uint64_t wqe_fifo_level        : 10; /**< [ 29: 20](RO/H) SSO WQE FIFO level. */
        uint64_t reserved_0_19         : 20;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_19         : 20;
        uint64_t wqe_fifo_level        : 10; /**< [ 29: 20](RO/H) SSO WQE FIFO level. */
        uint64_t reserved_30_41        : 12;
        uint64_t npa_fifo_level        : 5;  /**< [ 46: 42](RO/H) NPA FIFO level. */
        uint64_t reserved_47_53        : 7;
        uint64_t wqe_fifo_alloc_level  : 10; /**< [ 63: 54](RO/H) SSO WQE FIFO allocation level. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_dbg_s cn; */
};
typedef union bdk_tim_af_dbg bdk_tim_af_dbg_t;

#define BDK_TIM_AF_DBG BDK_TIM_AF_DBG_FUNC()
static inline uint64_t BDK_TIM_AF_DBG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_DBG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090030010ll;
    __bdk_csr_fatal("TIM_AF_DBG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_DBG bdk_tim_af_dbg_t
#define bustype_BDK_TIM_AF_DBG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_DBG "TIM_AF_DBG"
#define device_bar_BDK_TIM_AF_DBG 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_DBG 0
#define arguments_BDK_TIM_AF_DBG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_eco
 *
 * INTERNAL: TIM AF ECO Register
 */
union bdk_tim_af_eco
{
    uint64_t u;
    struct bdk_tim_af_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_eco_s cn; */
};
typedef union bdk_tim_af_eco bdk_tim_af_eco_t;

#define BDK_TIM_AF_ECO BDK_TIM_AF_ECO_FUNC()
static inline uint64_t BDK_TIM_AF_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000000ll;
    __bdk_csr_fatal("TIM_AF_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_ECO bdk_tim_af_eco_t
#define bustype_BDK_TIM_AF_ECO BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_ECO "TIM_AF_ECO"
#define device_bar_BDK_TIM_AF_ECO 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_ECO 0
#define arguments_BDK_TIM_AF_ECO -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_eng#_active
 *
 * TIM AF Engine Active Registers
 */
union bdk_tim_af_engx_active
{
    uint64_t u;
    struct bdk_tim_af_engx_active_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act                   : 1;  /**< [ 63: 63](RO/H) Engine active. For diagnostic use. */
        uint64_t reserved_45_62        : 18;
        uint64_t state                 : 5;  /**< [ 44: 40](RO/H) Engine state. For diagnostic use. */
        uint64_t bucket_id             : 20; /**< [ 39: 20](RO/H) Current bucket ID. For diagnostic use. */
        uint64_t reserved_8_19         : 12;
        uint64_t ring_id               : 8;  /**< [  7:  0](RO/H) Current ring ID. For diagnostic use. */
#else /* Word 0 - Little Endian */
        uint64_t ring_id               : 8;  /**< [  7:  0](RO/H) Current ring ID. For diagnostic use. */
        uint64_t reserved_8_19         : 12;
        uint64_t bucket_id             : 20; /**< [ 39: 20](RO/H) Current bucket ID. For diagnostic use. */
        uint64_t state                 : 5;  /**< [ 44: 40](RO/H) Engine state. For diagnostic use. */
        uint64_t reserved_45_62        : 18;
        uint64_t act                   : 1;  /**< [ 63: 63](RO/H) Engine active. For diagnostic use. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_engx_active_s cn; */
};
typedef union bdk_tim_af_engx_active bdk_tim_af_engx_active_t;

static inline uint64_t BDK_TIM_AF_ENGX_ACTIVE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_ENGX_ACTIVE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=15))
        return 0x840090038000ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("TIM_AF_ENGX_ACTIVE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_ENGX_ACTIVE(a) bdk_tim_af_engx_active_t
#define bustype_BDK_TIM_AF_ENGX_ACTIVE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_ENGX_ACTIVE(a) "TIM_AF_ENGX_ACTIVE"
#define device_bar_BDK_TIM_AF_ENGX_ACTIVE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_ENGX_ACTIVE(a) (a)
#define arguments_BDK_TIM_AF_ENGX_ACTIVE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_fr_rn_cycles
 *
 * TIM AF Free Running Cycle Count Register
 */
union bdk_tim_af_fr_rn_cycles
{
    uint64_t u;
    struct bdk_tim_af_fr_rn_cycles_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of system coprocessor-clock cycles. This register is only writable when
                                                                 TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of system coprocessor-clock cycles. This register is only writable when
                                                                 TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_fr_rn_cycles_s cn; */
};
typedef union bdk_tim_af_fr_rn_cycles bdk_tim_af_fr_rn_cycles_t;

#define BDK_TIM_AF_FR_RN_CYCLES BDK_TIM_AF_FR_RN_CYCLES_FUNC()
static inline uint64_t BDK_TIM_AF_FR_RN_CYCLES_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_FR_RN_CYCLES_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000030ll;
    __bdk_csr_fatal("TIM_AF_FR_RN_CYCLES", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_FR_RN_CYCLES bdk_tim_af_fr_rn_cycles_t
#define bustype_BDK_TIM_AF_FR_RN_CYCLES BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_FR_RN_CYCLES "TIM_AF_FR_RN_CYCLES"
#define device_bar_BDK_TIM_AF_FR_RN_CYCLES 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_FR_RN_CYCLES 0
#define arguments_BDK_TIM_AF_FR_RN_CYCLES -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_fr_rn_gpios
 *
 * TIM AF Free Running GPIO Clock Count Register
 */
union bdk_tim_af_fr_rn_gpios
{
    uint64_t u;
    struct bdk_tim_af_fr_rn_gpios_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of GPIO cycles. This register is only writable when TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of GPIO cycles. This register is only writable when TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_fr_rn_gpios_s cn; */
};
typedef union bdk_tim_af_fr_rn_gpios bdk_tim_af_fr_rn_gpios_t;

#define BDK_TIM_AF_FR_RN_GPIOS BDK_TIM_AF_FR_RN_GPIOS_FUNC()
static inline uint64_t BDK_TIM_AF_FR_RN_GPIOS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_FR_RN_GPIOS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000040ll;
    __bdk_csr_fatal("TIM_AF_FR_RN_GPIOS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_FR_RN_GPIOS bdk_tim_af_fr_rn_gpios_t
#define bustype_BDK_TIM_AF_FR_RN_GPIOS BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_FR_RN_GPIOS "TIM_AF_FR_RN_GPIOS"
#define device_bar_BDK_TIM_AF_FR_RN_GPIOS 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_FR_RN_GPIOS 0
#define arguments_BDK_TIM_AF_FR_RN_GPIOS -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_fr_rn_gti
 *
 * TIM AF Free Running GTI Clock Count Register
 */
union bdk_tim_af_fr_rn_gti
{
    uint64_t u;
    struct bdk_tim_af_fr_rn_gti_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of GTI system timer cycles. This register is only writable when
                                                                 TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of GTI system timer cycles. This register is only writable when
                                                                 TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_fr_rn_gti_s cn; */
};
typedef union bdk_tim_af_fr_rn_gti bdk_tim_af_fr_rn_gti_t;

#define BDK_TIM_AF_FR_RN_GTI BDK_TIM_AF_FR_RN_GTI_FUNC()
static inline uint64_t BDK_TIM_AF_FR_RN_GTI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_FR_RN_GTI_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000050ll;
    __bdk_csr_fatal("TIM_AF_FR_RN_GTI", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_FR_RN_GTI bdk_tim_af_fr_rn_gti_t
#define bustype_BDK_TIM_AF_FR_RN_GTI BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_FR_RN_GTI "TIM_AF_FR_RN_GTI"
#define device_bar_BDK_TIM_AF_FR_RN_GTI 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_FR_RN_GTI 0
#define arguments_BDK_TIM_AF_FR_RN_GTI -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_fr_rn_ptp
 *
 * TIM Free Running PTP Count Register
 */
union bdk_tim_af_fr_rn_ptp
{
    uint64_t u;
    struct bdk_tim_af_fr_rn_ptp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of PTP cycles. This register is only writable when TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of PTP cycles. This register is only writable when TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_fr_rn_ptp_s cn; */
};
typedef union bdk_tim_af_fr_rn_ptp bdk_tim_af_fr_rn_ptp_t;

#define BDK_TIM_AF_FR_RN_PTP BDK_TIM_AF_FR_RN_PTP_FUNC()
static inline uint64_t BDK_TIM_AF_FR_RN_PTP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_FR_RN_PTP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000060ll;
    __bdk_csr_fatal("TIM_AF_FR_RN_PTP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_FR_RN_PTP bdk_tim_af_fr_rn_ptp_t
#define bustype_BDK_TIM_AF_FR_RN_PTP BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_FR_RN_PTP "TIM_AF_FR_RN_PTP"
#define device_bar_BDK_TIM_AF_FR_RN_PTP 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_FR_RN_PTP 0
#define arguments_BDK_TIM_AF_FR_RN_PTP -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_fr_rn_tenns
 *
 * TIM AF Free Running 10ns Clock Count Register
 */
union bdk_tim_af_fr_rn_tenns
{
    uint64_t u;
    struct bdk_tim_af_fr_rn_tenns_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of 10ns clock cycles. This register is only writable when
                                                                 TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of 10ns clock cycles. This register is only writable when
                                                                 TIM_AF_REG_FLAGS[ENA_TIM] = 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_fr_rn_tenns_s cn; */
};
typedef union bdk_tim_af_fr_rn_tenns bdk_tim_af_fr_rn_tenns_t;

#define BDK_TIM_AF_FR_RN_TENNS BDK_TIM_AF_FR_RN_TENNS_FUNC()
static inline uint64_t BDK_TIM_AF_FR_RN_TENNS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_FR_RN_TENNS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000070ll;
    __bdk_csr_fatal("TIM_AF_FR_RN_TENNS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_FR_RN_TENNS bdk_tim_af_fr_rn_tenns_t
#define bustype_BDK_TIM_AF_FR_RN_TENNS BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_FR_RN_TENNS "TIM_AF_FR_RN_TENNS"
#define device_bar_BDK_TIM_AF_FR_RN_TENNS 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_FR_RN_TENNS 0
#define arguments_BDK_TIM_AF_FR_RN_TENNS -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_lf_rst
 *
 * TIM AF LF Reset Register
 * This register initiates LF resets.
 */
union bdk_tim_af_lf_rst
{
    uint64_t u;
    struct bdk_tim_af_lf_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t exec                  : 1;  /**< [ 12: 12](R/W1S/H) Execute LF software-initiated reset. When software writes a one to set this bit, hardware
                                                                 resets the local function selected by [LF]. Hardware clears this bit when
                                                                 done.

                                                                 Internal:
                                                                 This comment applies to all blocks that refer to this register:

                                                                 This should preferrably reset all registers/state associated with the LF, including
                                                                 any BLK_LF_* and BLK_AF_LF()_* registers. It would also be nice to reset any per-LF
                                                                 bits in other registers but its OK to have exceptions as long as the AF software has
                                                                 another way to reset them, e.g. by writing to the bits. Such additional steps
                                                                 expected from software should be documented in the HRM, e.g. in section 19.11.5
                                                                 "VF Function Level Reset". */
        uint64_t reserved_8_11         : 4;
        uint64_t lf                    : 8;  /**< [  7:  0](R/W) Local function that is reset when [EXEC] is set. */
#else /* Word 0 - Little Endian */
        uint64_t lf                    : 8;  /**< [  7:  0](R/W) Local function that is reset when [EXEC] is set. */
        uint64_t reserved_8_11         : 4;
        uint64_t exec                  : 1;  /**< [ 12: 12](R/W1S/H) Execute LF software-initiated reset. When software writes a one to set this bit, hardware
                                                                 resets the local function selected by [LF]. Hardware clears this bit when
                                                                 done.

                                                                 Internal:
                                                                 This comment applies to all blocks that refer to this register:

                                                                 This should preferrably reset all registers/state associated with the LF, including
                                                                 any BLK_LF_* and BLK_AF_LF()_* registers. It would also be nice to reset any per-LF
                                                                 bits in other registers but its OK to have exceptions as long as the AF software has
                                                                 another way to reset them, e.g. by writing to the bits. Such additional steps
                                                                 expected from software should be documented in the HRM, e.g. in section 19.11.5
                                                                 "VF Function Level Reset". */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_lf_rst_s cn; */
};
typedef union bdk_tim_af_lf_rst bdk_tim_af_lf_rst_t;

#define BDK_TIM_AF_LF_RST BDK_TIM_AF_LF_RST_FUNC()
static inline uint64_t BDK_TIM_AF_LF_RST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_LF_RST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000020ll;
    __bdk_csr_fatal("TIM_AF_LF_RST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_LF_RST bdk_tim_af_lf_rst_t
#define bustype_BDK_TIM_AF_LF_RST BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_LF_RST "TIM_AF_LF_RST"
#define device_bar_BDK_TIM_AF_LF_RST 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_LF_RST 0
#define arguments_BDK_TIM_AF_LF_RST -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_nxt_min_gpios_expire
 *
 * INTERNAL: TIM AF Next Minimum GPIOS Expiration Time Registers
 */
union bdk_tim_af_nxt_min_gpios_expire
{
    uint64_t u;
    struct bdk_tim_af_nxt_min_gpios_expire_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_AF_FR_RN_GPIOS must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_AF_FR_RN_GPIOS must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_nxt_min_gpios_expire_s cn; */
};
typedef union bdk_tim_af_nxt_min_gpios_expire bdk_tim_af_nxt_min_gpios_expire_t;

#define BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE_FUNC()
static inline uint64_t BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090030030ll;
    __bdk_csr_fatal("TIM_AF_NXT_MIN_GPIOS_EXPIRE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE bdk_tim_af_nxt_min_gpios_expire_t
#define bustype_BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE "TIM_AF_NXT_MIN_GPIOS_EXPIRE"
#define device_bar_BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE 0
#define arguments_BDK_TIM_AF_NXT_MIN_GPIOS_EXPIRE -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_nxt_min_gti_expire
 *
 * INTERNAL: TIM AF Next Minimum GTI Expire Time Registers
 */
union bdk_tim_af_nxt_min_gti_expire
{
    uint64_t u;
    struct bdk_tim_af_nxt_min_gti_expire_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_AF_FR_RN_GTI must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_AF_FR_RN_GTI must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_nxt_min_gti_expire_s cn; */
};
typedef union bdk_tim_af_nxt_min_gti_expire bdk_tim_af_nxt_min_gti_expire_t;

#define BDK_TIM_AF_NXT_MIN_GTI_EXPIRE BDK_TIM_AF_NXT_MIN_GTI_EXPIRE_FUNC()
static inline uint64_t BDK_TIM_AF_NXT_MIN_GTI_EXPIRE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_NXT_MIN_GTI_EXPIRE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090030040ll;
    __bdk_csr_fatal("TIM_AF_NXT_MIN_GTI_EXPIRE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_NXT_MIN_GTI_EXPIRE bdk_tim_af_nxt_min_gti_expire_t
#define bustype_BDK_TIM_AF_NXT_MIN_GTI_EXPIRE BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_NXT_MIN_GTI_EXPIRE "TIM_AF_NXT_MIN_GTI_EXPIRE"
#define device_bar_BDK_TIM_AF_NXT_MIN_GTI_EXPIRE 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_NXT_MIN_GTI_EXPIRE 0
#define arguments_BDK_TIM_AF_NXT_MIN_GTI_EXPIRE -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_nxt_min_ptp_expire
 *
 * INTERNAL: TIM AF Next Minimum PTP Expire Time Registers
 */
union bdk_tim_af_nxt_min_ptp_expire
{
    uint64_t u;
    struct bdk_tim_af_nxt_min_ptp_expire_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_AF_FR_RN_PTP must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_AF_FR_RN_PTP must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_nxt_min_ptp_expire_s cn; */
};
typedef union bdk_tim_af_nxt_min_ptp_expire bdk_tim_af_nxt_min_ptp_expire_t;

#define BDK_TIM_AF_NXT_MIN_PTP_EXPIRE BDK_TIM_AF_NXT_MIN_PTP_EXPIRE_FUNC()
static inline uint64_t BDK_TIM_AF_NXT_MIN_PTP_EXPIRE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_NXT_MIN_PTP_EXPIRE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090030050ll;
    __bdk_csr_fatal("TIM_AF_NXT_MIN_PTP_EXPIRE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_NXT_MIN_PTP_EXPIRE bdk_tim_af_nxt_min_ptp_expire_t
#define bustype_BDK_TIM_AF_NXT_MIN_PTP_EXPIRE BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_NXT_MIN_PTP_EXPIRE "TIM_AF_NXT_MIN_PTP_EXPIRE"
#define device_bar_BDK_TIM_AF_NXT_MIN_PTP_EXPIRE 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_NXT_MIN_PTP_EXPIRE 0
#define arguments_BDK_TIM_AF_NXT_MIN_PTP_EXPIRE -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_nxt_min_tenns_expire
 *
 * INTERNAL: TIM AF Next Minimum 10ns Clock Expiration Time Register
 */
union bdk_tim_af_nxt_min_tenns_expire
{
    uint64_t u;
    struct bdk_tim_af_nxt_min_tenns_expire_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_AF_FR_RN_TENNS must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_AF_FR_RN_TENNS must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_nxt_min_tenns_expire_s cn; */
};
typedef union bdk_tim_af_nxt_min_tenns_expire bdk_tim_af_nxt_min_tenns_expire_t;

#define BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE_FUNC()
static inline uint64_t BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090030020ll;
    __bdk_csr_fatal("TIM_AF_NXT_MIN_TENNS_EXPIRE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE bdk_tim_af_nxt_min_tenns_expire_t
#define bustype_BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE "TIM_AF_NXT_MIN_TENNS_EXPIRE"
#define device_bar_BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE 0
#define arguments_BDK_TIM_AF_NXT_MIN_TENNS_EXPIRE -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_reg_flags
 *
 * TIM AF Flags Register
 * This register provides flags for TIM.
 */
union bdk_tim_af_reg_flags
{
    uint64_t u;
    struct bdk_tim_af_reg_flags_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t gpio_edge             : 2;  /**< [  6:  5](R/W) Edge used for GPIO timing.
                                                                 0x0 = no edges and the timer tick is not generated.
                                                                 0x1 = TIM counts low-to-high transitions.
                                                                 0x2 = TIM counts high-to-low transitions.
                                                                 0x3 = TIM counts both low-to-high and high-to-low transitions. */
        uint64_t force_extbus_ena      : 1;  /**< [  4:  4](R/W) When set, the extbus clock enable is always on. For diagnostic use only. */
        uint64_t rd_psn_ign            : 1;  /**< [  3:  3](WO/H) When set, poisoned data is treated as normal nonpoisoned data. Otherwise, react
                                                                 as if a faulted data is received. Regardless of how this bit is configured,
                                                                 poison errors are logged in TIM_LF_RAS_INT always. */
        uint64_t reset                 : 1;  /**< [  2:  2](WO/H) Reset. One-shot pulse for clearing free-running timers TIM_AF_FR_RN_*. */
        uint64_t force_csclk_ena       : 1;  /**< [  1:  1](R/W) When set, conditional clock is always on. For diagnostic use only. */
        uint64_t ena_tim               : 1;  /**< [  0:  0](R/W) When set, TIM is in normal operation. When clear, time is effectively stopped for all
                                                                 rings in TIM.

                                                                 When [ENA_TIM] transitions 1-\>0, TIM stops all free-running timers and disables all rings.
                                                                 No new buckets will be traversed, and the buckets that are being traversed at the
                                                                 moment will be completed. */
#else /* Word 0 - Little Endian */
        uint64_t ena_tim               : 1;  /**< [  0:  0](R/W) When set, TIM is in normal operation. When clear, time is effectively stopped for all
                                                                 rings in TIM.

                                                                 When [ENA_TIM] transitions 1-\>0, TIM stops all free-running timers and disables all rings.
                                                                 No new buckets will be traversed, and the buckets that are being traversed at the
                                                                 moment will be completed. */
        uint64_t force_csclk_ena       : 1;  /**< [  1:  1](R/W) When set, conditional clock is always on. For diagnostic use only. */
        uint64_t reset                 : 1;  /**< [  2:  2](WO/H) Reset. One-shot pulse for clearing free-running timers TIM_AF_FR_RN_*. */
        uint64_t rd_psn_ign            : 1;  /**< [  3:  3](WO/H) When set, poisoned data is treated as normal nonpoisoned data. Otherwise, react
                                                                 as if a faulted data is received. Regardless of how this bit is configured,
                                                                 poison errors are logged in TIM_LF_RAS_INT always. */
        uint64_t force_extbus_ena      : 1;  /**< [  4:  4](R/W) When set, the extbus clock enable is always on. For diagnostic use only. */
        uint64_t gpio_edge             : 2;  /**< [  6:  5](R/W) Edge used for GPIO timing.
                                                                 0x0 = no edges and the timer tick is not generated.
                                                                 0x1 = TIM counts low-to-high transitions.
                                                                 0x2 = TIM counts high-to-low transitions.
                                                                 0x3 = TIM counts both low-to-high and high-to-low transitions. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_reg_flags_s cn; */
};
typedef union bdk_tim_af_reg_flags bdk_tim_af_reg_flags_t;

#define BDK_TIM_AF_REG_FLAGS BDK_TIM_AF_REG_FLAGS_FUNC()
static inline uint64_t BDK_TIM_AF_REG_FLAGS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_REG_FLAGS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090000080ll;
    __bdk_csr_fatal("TIM_AF_REG_FLAGS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_REG_FLAGS bdk_tim_af_reg_flags_t
#define bustype_BDK_TIM_AF_REG_FLAGS BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_REG_FLAGS "TIM_AF_REG_FLAGS"
#define device_bar_BDK_TIM_AF_REG_FLAGS 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_REG_FLAGS 0
#define arguments_BDK_TIM_AF_REG_FLAGS -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_ring#_ctl0
 *
 * TIM AF Ring Control 0 Registers
 */
union bdk_tim_af_ringx_ctl0
{
    uint64_t u;
    struct bdk_tim_af_ringx_ctl0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t expire_offset         : 32; /**< [ 63: 32](R/W/H) Time at which the next bucket will be serviced, or offset. See also TIM_LF_RING_REL
                                                                 for the position relative to current time.

                                                                 If TIM_AF_RING()_CTL1[ENA] = 0, then contains an offset. When ENA transitions from a
                                                                 zero to a one, this offset will be added to the current time and INTERVAL, and loaded back into
                                                                 [EXPIRE_OFFSET]. Thus the offset sets the delta time between ENA transitioning to one and
                                                                 the very first time the ring will be serviced. Software should program different offsets
                                                                 on each ring to reduce congestion to prevent many rings from otherwise expiring
                                                                 concurrently.

                                                                 If TIM_AF_RING()_CTL1[ENA] = 1, then [EXPIRE_OFFSET] contains the time in the future the next
                                                                 bucket will be serviced.

                                                                 When [EXPIRE_OFFSET] reaches the current time (TIM_AF_FR_RN_TENNS,
                                                                 TIM_AF_FR_RN_GPIOS, TIM_AF_FR_RN_PTP or TIM_AF_FR_RN_GTI),
                                                                 [EXPIRE_OFFSET] is set to the next expiration time (current time plus
                                                                 TIM_AF_RING()_CTL0[INTERVAL]).

                                                                 [EXPIRE_OFFSET] is unpredictable after TIM_AF_RING()_CTL1[CLK_SRC] changes or
                                                                 TIM_AF_RING()_CTL1[ENA] transitions from one to zero, and must be reprogrammed before
                                                                 setting or resetting TIM_AF_RING()_CTL1[ENA]. */
        uint64_t interval              : 32; /**< [ 31:  0](R/W) Timer interval, measured in TENNS, GTI or PTP clocks, or GPIO transitions.
                                                                 Minimum value is 256 for TENNS, 256 for GPIO, 300 for GTI and PTP rings. */
#else /* Word 0 - Little Endian */
        uint64_t interval              : 32; /**< [ 31:  0](R/W) Timer interval, measured in TENNS, GTI or PTP clocks, or GPIO transitions.
                                                                 Minimum value is 256 for TENNS, 256 for GPIO, 300 for GTI and PTP rings. */
        uint64_t expire_offset         : 32; /**< [ 63: 32](R/W/H) Time at which the next bucket will be serviced, or offset. See also TIM_LF_RING_REL
                                                                 for the position relative to current time.

                                                                 If TIM_AF_RING()_CTL1[ENA] = 0, then contains an offset. When ENA transitions from a
                                                                 zero to a one, this offset will be added to the current time and INTERVAL, and loaded back into
                                                                 [EXPIRE_OFFSET]. Thus the offset sets the delta time between ENA transitioning to one and
                                                                 the very first time the ring will be serviced. Software should program different offsets
                                                                 on each ring to reduce congestion to prevent many rings from otherwise expiring
                                                                 concurrently.

                                                                 If TIM_AF_RING()_CTL1[ENA] = 1, then [EXPIRE_OFFSET] contains the time in the future the next
                                                                 bucket will be serviced.

                                                                 When [EXPIRE_OFFSET] reaches the current time (TIM_AF_FR_RN_TENNS,
                                                                 TIM_AF_FR_RN_GPIOS, TIM_AF_FR_RN_PTP or TIM_AF_FR_RN_GTI),
                                                                 [EXPIRE_OFFSET] is set to the next expiration time (current time plus
                                                                 TIM_AF_RING()_CTL0[INTERVAL]).

                                                                 [EXPIRE_OFFSET] is unpredictable after TIM_AF_RING()_CTL1[CLK_SRC] changes or
                                                                 TIM_AF_RING()_CTL1[ENA] transitions from one to zero, and must be reprogrammed before
                                                                 setting or resetting TIM_AF_RING()_CTL1[ENA]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_ringx_ctl0_s cn; */
};
typedef union bdk_tim_af_ringx_ctl0 bdk_tim_af_ringx_ctl0_t;

static inline uint64_t BDK_TIM_AF_RINGX_CTL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RINGX_CTL0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840090004000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("TIM_AF_RINGX_CTL0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RINGX_CTL0(a) bdk_tim_af_ringx_ctl0_t
#define bustype_BDK_TIM_AF_RINGX_CTL0(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RINGX_CTL0(a) "TIM_AF_RINGX_CTL0"
#define device_bar_BDK_TIM_AF_RINGX_CTL0(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RINGX_CTL0(a) (a)
#define arguments_BDK_TIM_AF_RINGX_CTL0(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_ring#_ctl1
 *
 * TIM AF Ring Control 1 Registers
 */
union bdk_tim_af_ringx_ctl1
{
    uint64_t u;
    struct bdk_tim_af_ringx_ctl1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_54_63        : 10;
        uint64_t be                    : 1;  /**< [ 53: 53](R/W) Ring big-endian. If set, TIM_MEM_BUCKET_S and other in-memory structures are big endian. */
        uint64_t clk_src               : 2;  /**< [ 52: 51](R/W) Source of ring's timer tick. Enumerated by TIM_CLK_SRCS_E. To change [CLK_SRC]:

                                                                 1. TIM_AF_RING()_CTL1[ENA] is cleared.

                                                                 2. [CLK_SRC] is changed.

                                                                 3. TIM_AF_RING()_CTL0[EXPIRE_OFFSET] is reprogrammed appropriately.

                                                                 4. TIM_AF_RING()_CTL1[ENA] is set. */
        uint64_t rcf_busy              : 1;  /**< [ 50: 50](RO/H) Ring reconfiguration busy. When [ENA] is cleared, this bit will be set, if an
                                                                 engine is currently processing, a ring/bucket. It will remain set until
                                                                 hardware completes traversing that bucket. [ENA] must not be re-enabled until clear. */
        uint64_t reserved_49           : 1;
        uint64_t lock_en               : 1;  /**< [ 48: 48](R/W) Enables bucket locking mechanism between hardware and software.
                                                                   0 = Hardware will always service the bucket when it expires.
                                                                   1 = Hardware skips buckets when it can't get the bucket's lock. */
        uint64_t ena                   : 1;  /**< [ 47: 47](R/W/H) Ring timer enable. When clearing, software must delay until
                                                                 [RCF_BUSY] = 0 to ensure the completion of the traversal before reprogramming
                                                                 the ring. Hardware will clear this bit when any TIM_LF_NRSPERR_INT[*] bit
                                                                 is set by hardware. */
        uint64_t reserved_46           : 1;
        uint64_t ena_prd               : 1;  /**< [ 45: 45](R/W) Enable periodic mode, which disables the memory write of zeros to
                                                                 TIM_MEM_BUCKET_S[NUM_ENTRIES] and TIM_MEM_BUCKET_S[CHUNK_REMAINDER] when a
                                                                 bucket is traversed. In periodic mode, [ENA_LDWB] must be cleared.
                                                                 Also, in periodic mode, [ENA_DFB] should be one, and zero otherwise. */
        uint64_t ena_ldwb              : 1;  /**< [ 44: 44](R/W) When set, enables the use of load and don't-write-back when reading timer entry cache lines.
                                                                 Must be clear when [ENA_PRD] is set. */
        uint64_t ena_dfb               : 1;  /**< [ 43: 43](R/W) Enable don't free buffer. When set, chunk buffer is not released by the TIM back to NPA.
                                                                 Must be set when [ENA_PRD] is set. */
        uint64_t reserved_40_42        : 3;
        uint64_t bucket                : 20; /**< [ 39: 20](R/W/H) Current bucket. Should be set to 0x0 by software at enable time. Incremented once per
                                                                 bucket traversal. */
        uint64_t bsize                 : 20; /**< [ 19:  0](R/W) Number of buckets minus one. [BSIZE] needs to be \> 0x0 and \< 0xFFFFF, i.e., there are at least two
                                                                 buckets in each nonempty ring. */
#else /* Word 0 - Little Endian */
        uint64_t bsize                 : 20; /**< [ 19:  0](R/W) Number of buckets minus one. [BSIZE] needs to be \> 0x0 and \< 0xFFFFF, i.e., there are at least two
                                                                 buckets in each nonempty ring. */
        uint64_t bucket                : 20; /**< [ 39: 20](R/W/H) Current bucket. Should be set to 0x0 by software at enable time. Incremented once per
                                                                 bucket traversal. */
        uint64_t reserved_40_42        : 3;
        uint64_t ena_dfb               : 1;  /**< [ 43: 43](R/W) Enable don't free buffer. When set, chunk buffer is not released by the TIM back to NPA.
                                                                 Must be set when [ENA_PRD] is set. */
        uint64_t ena_ldwb              : 1;  /**< [ 44: 44](R/W) When set, enables the use of load and don't-write-back when reading timer entry cache lines.
                                                                 Must be clear when [ENA_PRD] is set. */
        uint64_t ena_prd               : 1;  /**< [ 45: 45](R/W) Enable periodic mode, which disables the memory write of zeros to
                                                                 TIM_MEM_BUCKET_S[NUM_ENTRIES] and TIM_MEM_BUCKET_S[CHUNK_REMAINDER] when a
                                                                 bucket is traversed. In periodic mode, [ENA_LDWB] must be cleared.
                                                                 Also, in periodic mode, [ENA_DFB] should be one, and zero otherwise. */
        uint64_t reserved_46           : 1;
        uint64_t ena                   : 1;  /**< [ 47: 47](R/W/H) Ring timer enable. When clearing, software must delay until
                                                                 [RCF_BUSY] = 0 to ensure the completion of the traversal before reprogramming
                                                                 the ring. Hardware will clear this bit when any TIM_LF_NRSPERR_INT[*] bit
                                                                 is set by hardware. */
        uint64_t lock_en               : 1;  /**< [ 48: 48](R/W) Enables bucket locking mechanism between hardware and software.
                                                                   0 = Hardware will always service the bucket when it expires.
                                                                   1 = Hardware skips buckets when it can't get the bucket's lock. */
        uint64_t reserved_49           : 1;
        uint64_t rcf_busy              : 1;  /**< [ 50: 50](RO/H) Ring reconfiguration busy. When [ENA] is cleared, this bit will be set, if an
                                                                 engine is currently processing, a ring/bucket. It will remain set until
                                                                 hardware completes traversing that bucket. [ENA] must not be re-enabled until clear. */
        uint64_t clk_src               : 2;  /**< [ 52: 51](R/W) Source of ring's timer tick. Enumerated by TIM_CLK_SRCS_E. To change [CLK_SRC]:

                                                                 1. TIM_AF_RING()_CTL1[ENA] is cleared.

                                                                 2. [CLK_SRC] is changed.

                                                                 3. TIM_AF_RING()_CTL0[EXPIRE_OFFSET] is reprogrammed appropriately.

                                                                 4. TIM_AF_RING()_CTL1[ENA] is set. */
        uint64_t be                    : 1;  /**< [ 53: 53](R/W) Ring big-endian. If set, TIM_MEM_BUCKET_S and other in-memory structures are big endian. */
        uint64_t reserved_54_63        : 10;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_ringx_ctl1_s cn; */
};
typedef union bdk_tim_af_ringx_ctl1 bdk_tim_af_ringx_ctl1_t;

static inline uint64_t BDK_TIM_AF_RINGX_CTL1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RINGX_CTL1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840090006000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("TIM_AF_RINGX_CTL1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RINGX_CTL1(a) bdk_tim_af_ringx_ctl1_t
#define bustype_BDK_TIM_AF_RINGX_CTL1(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RINGX_CTL1(a) "TIM_AF_RINGX_CTL1"
#define device_bar_BDK_TIM_AF_RINGX_CTL1(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RINGX_CTL1(a) (a)
#define arguments_BDK_TIM_AF_RINGX_CTL1(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_ring#_ctl2
 *
 * TIM AF Ring Control 2 Registers
 */
union bdk_tim_af_ringx_ctl2
{
    uint64_t u;
    struct bdk_tim_af_ringx_ctl2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t csize                 : 13; /**< [ 52: 40](R/W) Number of sixteen-byte words per chunk, i.e. one for the next pointer plus one
                                                                 times the number of TIM_MEM_ENTRY_S. [CSIZE] mod(8) must be zero. */
        uint64_t reserved_0_39         : 40;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_39         : 40;
        uint64_t csize                 : 13; /**< [ 52: 40](R/W) Number of sixteen-byte words per chunk, i.e. one for the next pointer plus one
                                                                 times the number of TIM_MEM_ENTRY_S. [CSIZE] mod(8) must be zero. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_ringx_ctl2_s cn; */
};
typedef union bdk_tim_af_ringx_ctl2 bdk_tim_af_ringx_ctl2_t;

static inline uint64_t BDK_TIM_AF_RINGX_CTL2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RINGX_CTL2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840090008000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("TIM_AF_RINGX_CTL2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RINGX_CTL2(a) bdk_tim_af_ringx_ctl2_t
#define bustype_BDK_TIM_AF_RINGX_CTL2(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RINGX_CTL2(a) "TIM_AF_RINGX_CTL2"
#define device_bar_BDK_TIM_AF_RINGX_CTL2(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RINGX_CTL2(a) (a)
#define arguments_BDK_TIM_AF_RINGX_CTL2(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_ring#_gmctl
 *
 * TIM Ring Guest Machine Control Register
 */
union bdk_tim_af_ringx_gmctl
{
    uint64_t u;
    struct bdk_tim_af_ringx_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t npa_pf_func           : 16; /**< [ 31: 16](R/W) NPA RVU physical and virtual function. Indicates the RVU PF and VF to which
                                                                 this ring's NPA free buffer requests are sent. */
        uint64_t sso_pf_func           : 16; /**< [ 15:  0](R/W) SSO RVU physical and virtual function. Indicates the RVU PF and VF to which
                                                                 this ring's SSO add works are sent. */
#else /* Word 0 - Little Endian */
        uint64_t sso_pf_func           : 16; /**< [ 15:  0](R/W) SSO RVU physical and virtual function. Indicates the RVU PF and VF to which
                                                                 this ring's SSO add works are sent. */
        uint64_t npa_pf_func           : 16; /**< [ 31: 16](R/W) NPA RVU physical and virtual function. Indicates the RVU PF and VF to which
                                                                 this ring's NPA free buffer requests are sent. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_ringx_gmctl_s cn; */
};
typedef union bdk_tim_af_ringx_gmctl bdk_tim_af_ringx_gmctl_t;

static inline uint64_t BDK_TIM_AF_RINGX_GMCTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RINGX_GMCTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840090002000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("TIM_AF_RINGX_GMCTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RINGX_GMCTL(a) bdk_tim_af_ringx_gmctl_t
#define bustype_BDK_TIM_AF_RINGX_GMCTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RINGX_GMCTL(a) "TIM_AF_RINGX_GMCTL"
#define device_bar_BDK_TIM_AF_RINGX_GMCTL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RINGX_GMCTL(a) (a)
#define arguments_BDK_TIM_AF_RINGX_GMCTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_ring#_late
 *
 * TIM Ring Late Register
 */
union bdk_tim_af_ringx_late
{
    uint64_t u;
    struct bdk_tim_af_ringx_late_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t count                 : 20; /**< [ 19:  0](RO/H) Indicates how many buckets are late ([COUNT] \> 1) to be processed in this ring.
                                                                 When the associated ring is late, TIM will make a best effort to catch up and
                                                                 processes all buckets that are late, back-to-back. Incremented by TIM for every
                                                                 ring expiration and decremented when a ring's bucket is serviced.
                                                                 When (TIM_AF_RING()_LATE[COUNT] \>= (TIM_AF_RING()_CTL1[BSIZE]+1))
                                                                 hardware will set TIM_AF_RING()_LATE[COUNT] = 1.
                                                                 Hardware will set TIM_AF_RING()_LATE[COUNT] = 0 when TIM_AF_RING()_CTL1[ENA]
                                                                 transitions from 1-\>0. Since maximum of TIM_AF_RING()_CTL1[BSIZE] is 0xFFFFE,
                                                                 maximum of TIM_AF_RING()_LATE[COUNT] is 0xFFFFF. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 20; /**< [ 19:  0](RO/H) Indicates how many buckets are late ([COUNT] \> 1) to be processed in this ring.
                                                                 When the associated ring is late, TIM will make a best effort to catch up and
                                                                 processes all buckets that are late, back-to-back. Incremented by TIM for every
                                                                 ring expiration and decremented when a ring's bucket is serviced.
                                                                 When (TIM_AF_RING()_LATE[COUNT] \>= (TIM_AF_RING()_CTL1[BSIZE]+1))
                                                                 hardware will set TIM_AF_RING()_LATE[COUNT] = 1.
                                                                 Hardware will set TIM_AF_RING()_LATE[COUNT] = 0 when TIM_AF_RING()_CTL1[ENA]
                                                                 transitions from 1-\>0. Since maximum of TIM_AF_RING()_CTL1[BSIZE] is 0xFFFFE,
                                                                 maximum of TIM_AF_RING()_LATE[COUNT] is 0xFFFFF. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_ringx_late_s cn; */
};
typedef union bdk_tim_af_ringx_late bdk_tim_af_ringx_late_t;

static inline uint64_t BDK_TIM_AF_RINGX_LATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RINGX_LATE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840090046000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("TIM_AF_RINGX_LATE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RINGX_LATE(a) bdk_tim_af_ringx_late_t
#define bustype_BDK_TIM_AF_RINGX_LATE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RINGX_LATE(a) "TIM_AF_RINGX_LATE"
#define device_bar_BDK_TIM_AF_RINGX_LATE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RINGX_LATE(a) (a)
#define arguments_BDK_TIM_AF_RINGX_LATE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_ring_active_vec#
 *
 * TIM AF Ring Active Register
 */
union bdk_tim_af_ring_active_vecx
{
    uint64_t u;
    struct bdk_tim_af_ring_active_vecx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ring_active_vec       : 64; /**< [ 63:  0](RO/H) Active rings vector. Indicates which rings in TIM are active, reconfigured with updated
                                                                 TIM_AF_RING()_CTL0[EXPIRE_OFFSET], and are ready to be searched/expired. */
#else /* Word 0 - Little Endian */
        uint64_t ring_active_vec       : 64; /**< [ 63:  0](RO/H) Active rings vector. Indicates which rings in TIM are active, reconfigured with updated
                                                                 TIM_AF_RING()_CTL0[EXPIRE_OFFSET], and are ready to be searched/expired. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_ring_active_vecx_s cn; */
};
typedef union bdk_tim_af_ring_active_vecx bdk_tim_af_ring_active_vecx_t;

static inline uint64_t BDK_TIM_AF_RING_ACTIVE_VECX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RING_ACTIVE_VECX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840090040000ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("TIM_AF_RING_ACTIVE_VECX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RING_ACTIVE_VECX(a) bdk_tim_af_ring_active_vecx_t
#define bustype_BDK_TIM_AF_RING_ACTIVE_VECX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RING_ACTIVE_VECX(a) "TIM_AF_RING_ACTIVE_VECX"
#define device_bar_BDK_TIM_AF_RING_ACTIVE_VECX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RING_ACTIVE_VECX(a) (a)
#define arguments_BDK_TIM_AF_RING_ACTIVE_VECX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_ring_pending_vec#
 *
 * TIM AF Ring Pending Register
 */
union bdk_tim_af_ring_pending_vecx
{
    uint64_t u;
    struct bdk_tim_af_ring_pending_vecx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ring_pending_vec      : 64; /**< [ 63:  0](RO/H) Pending rings vector. Indicates which rings in TIM are pending traversal. Bit 0
                                                                 of TIM_AF_RING_PENDING_VEC(0) represents ring 0, while bit 63 of
                                                                 TIM_AF_RING_PENDING_VEC(3) represents ring 255. */
#else /* Word 0 - Little Endian */
        uint64_t ring_pending_vec      : 64; /**< [ 63:  0](RO/H) Pending rings vector. Indicates which rings in TIM are pending traversal. Bit 0
                                                                 of TIM_AF_RING_PENDING_VEC(0) represents ring 0, while bit 63 of
                                                                 TIM_AF_RING_PENDING_VEC(3) represents ring 255. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_ring_pending_vecx_s cn; */
};
typedef union bdk_tim_af_ring_pending_vecx bdk_tim_af_ring_pending_vecx_t;

static inline uint64_t BDK_TIM_AF_RING_PENDING_VECX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RING_PENDING_VECX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=3))
        return 0x840090042000ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("TIM_AF_RING_PENDING_VECX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RING_PENDING_VECX(a) bdk_tim_af_ring_pending_vecx_t
#define bustype_BDK_TIM_AF_RING_PENDING_VECX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RING_PENDING_VECX(a) "TIM_AF_RING_PENDING_VECX"
#define device_bar_BDK_TIM_AF_RING_PENDING_VECX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RING_PENDING_VECX(a) (a)
#define arguments_BDK_TIM_AF_RING_PENDING_VECX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_rvu_int
 *
 * TIM AF RVU Interrupt Register
 * This register contains RVU error interrupt summary bits.
 */
union bdk_tim_af_rvu_int
{
    uint64_t u;
    struct bdk_tim_af_rvu_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Unmapped slot. Received an I/O request to a VF/PF slot in BAR2 that is not
                                                                 reverse mapped to an LF. See TIM_PRIV_LF()_CFG and TIM_AF_RVU_LF_CFG_DEBUG. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Unmapped slot. Received an I/O request to a VF/PF slot in BAR2 that is not
                                                                 reverse mapped to an LF. See TIM_PRIV_LF()_CFG and TIM_AF_RVU_LF_CFG_DEBUG. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_rvu_int_s cn9; */
    /* struct bdk_tim_af_rvu_int_s cn96xxp1; */
    struct bdk_tim_af_rvu_int_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Unmapped slot. Received an I/O request to a VF/PF slot in BAR2 that is not
                                                                 reverse mapped to an LF. See TIM_PRIV_LF()_CFG.

                                                                 Internal:
                                                                 A reverse lookup using TIM_AF_RVU_LF_CFG_DEBUG will never set this bit. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Unmapped slot. Received an I/O request to a VF/PF slot in BAR2 that is not
                                                                 reverse mapped to an LF. See TIM_PRIV_LF()_CFG.

                                                                 Internal:
                                                                 A reverse lookup using TIM_AF_RVU_LF_CFG_DEBUG will never set this bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_tim_af_rvu_int_cn96xxp3 cn98xx; */
    /* struct bdk_tim_af_rvu_int_cn96xxp3 cnf95xx; */
    /* struct bdk_tim_af_rvu_int_cn96xxp3 loki; */
};
typedef union bdk_tim_af_rvu_int bdk_tim_af_rvu_int_t;

#define BDK_TIM_AF_RVU_INT BDK_TIM_AF_RVU_INT_FUNC()
static inline uint64_t BDK_TIM_AF_RVU_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RVU_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090010200ll;
    __bdk_csr_fatal("TIM_AF_RVU_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RVU_INT bdk_tim_af_rvu_int_t
#define bustype_BDK_TIM_AF_RVU_INT BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RVU_INT "TIM_AF_RVU_INT"
#define device_bar_BDK_TIM_AF_RVU_INT 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RVU_INT 0
#define arguments_BDK_TIM_AF_RVU_INT -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_rvu_int_ena_w1c
 *
 * TIM AF RVU Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_tim_af_rvu_int_ena_w1c
{
    uint64_t u;
    struct bdk_tim_af_rvu_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_AF_RVU_INT[UNMAPPED_SLOT]. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_AF_RVU_INT[UNMAPPED_SLOT]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_rvu_int_ena_w1c_s cn9; */
    /* struct bdk_tim_af_rvu_int_ena_w1c_s cn96xxp1; */
    struct bdk_tim_af_rvu_int_ena_w1c_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using TIM_AF_RVU_LF_CFG_DEBUG will never set this bit. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using TIM_AF_RVU_LF_CFG_DEBUG will never set this bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_tim_af_rvu_int_ena_w1c_cn96xxp3 cn98xx; */
    /* struct bdk_tim_af_rvu_int_ena_w1c_cn96xxp3 cnf95xx; */
    /* struct bdk_tim_af_rvu_int_ena_w1c_cn96xxp3 loki; */
};
typedef union bdk_tim_af_rvu_int_ena_w1c bdk_tim_af_rvu_int_ena_w1c_t;

#define BDK_TIM_AF_RVU_INT_ENA_W1C BDK_TIM_AF_RVU_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_TIM_AF_RVU_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RVU_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090010218ll;
    __bdk_csr_fatal("TIM_AF_RVU_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RVU_INT_ENA_W1C bdk_tim_af_rvu_int_ena_w1c_t
#define bustype_BDK_TIM_AF_RVU_INT_ENA_W1C BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RVU_INT_ENA_W1C "TIM_AF_RVU_INT_ENA_W1C"
#define device_bar_BDK_TIM_AF_RVU_INT_ENA_W1C 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RVU_INT_ENA_W1C 0
#define arguments_BDK_TIM_AF_RVU_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_rvu_int_ena_w1s
 *
 * TIM AF RVU Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_tim_af_rvu_int_ena_w1s
{
    uint64_t u;
    struct bdk_tim_af_rvu_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_AF_RVU_INT[UNMAPPED_SLOT]. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_AF_RVU_INT[UNMAPPED_SLOT]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_rvu_int_ena_w1s_s cn9; */
    /* struct bdk_tim_af_rvu_int_ena_w1s_s cn96xxp1; */
    struct bdk_tim_af_rvu_int_ena_w1s_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using TIM_AF_RVU_LF_CFG_DEBUG will never set this bit. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using TIM_AF_RVU_LF_CFG_DEBUG will never set this bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_tim_af_rvu_int_ena_w1s_cn96xxp3 cn98xx; */
    /* struct bdk_tim_af_rvu_int_ena_w1s_cn96xxp3 cnf95xx; */
    /* struct bdk_tim_af_rvu_int_ena_w1s_cn96xxp3 loki; */
};
typedef union bdk_tim_af_rvu_int_ena_w1s bdk_tim_af_rvu_int_ena_w1s_t;

#define BDK_TIM_AF_RVU_INT_ENA_W1S BDK_TIM_AF_RVU_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_TIM_AF_RVU_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RVU_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090010210ll;
    __bdk_csr_fatal("TIM_AF_RVU_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RVU_INT_ENA_W1S bdk_tim_af_rvu_int_ena_w1s_t
#define bustype_BDK_TIM_AF_RVU_INT_ENA_W1S BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RVU_INT_ENA_W1S "TIM_AF_RVU_INT_ENA_W1S"
#define device_bar_BDK_TIM_AF_RVU_INT_ENA_W1S 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RVU_INT_ENA_W1S 0
#define arguments_BDK_TIM_AF_RVU_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_rvu_int_w1s
 *
 * TIM AF RVU Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_tim_af_rvu_int_w1s
{
    uint64_t u;
    struct bdk_tim_af_rvu_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_AF_RVU_INT[UNMAPPED_SLOT]. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_AF_RVU_INT[UNMAPPED_SLOT]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_rvu_int_w1s_s cn9; */
    /* struct bdk_tim_af_rvu_int_w1s_s cn96xxp1; */
    struct bdk_tim_af_rvu_int_w1s_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using TIM_AF_RVU_LF_CFG_DEBUG will never set this bit. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using TIM_AF_RVU_LF_CFG_DEBUG will never set this bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_tim_af_rvu_int_w1s_cn96xxp3 cn98xx; */
    /* struct bdk_tim_af_rvu_int_w1s_cn96xxp3 cnf95xx; */
    /* struct bdk_tim_af_rvu_int_w1s_cn96xxp3 loki; */
};
typedef union bdk_tim_af_rvu_int_w1s bdk_tim_af_rvu_int_w1s_t;

#define BDK_TIM_AF_RVU_INT_W1S BDK_TIM_AF_RVU_INT_W1S_FUNC()
static inline uint64_t BDK_TIM_AF_RVU_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RVU_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090010208ll;
    __bdk_csr_fatal("TIM_AF_RVU_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RVU_INT_W1S bdk_tim_af_rvu_int_w1s_t
#define bustype_BDK_TIM_AF_RVU_INT_W1S BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RVU_INT_W1S "TIM_AF_RVU_INT_W1S"
#define device_bar_BDK_TIM_AF_RVU_INT_W1S 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RVU_INT_W1S 0
#define arguments_BDK_TIM_AF_RVU_INT_W1S -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_af_rvu_lf_cfg_debug
 *
 * TIM Privileged LF Configuration Debug Registers
 * This debug register allows software to lookup the reverse mapping from VF/PF
 * slot to LF. The forward mapping is programmed with TIM_PRIV_LF()_CFG.
 */
union bdk_tim_af_rvu_lf_cfg_debug
{
    uint64_t u;
    struct bdk_tim_af_rvu_lf_cfg_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t pf_func               : 16; /**< [ 39: 24](R/W) RVU VF/PF for reverse lookup. Format defined by RVU_PF_FUNC_S. */
        uint64_t slot                  : 8;  /**< [ 23: 16](R/W) Slot within the VF/PF selected by [PF_FUNC] for reverse lookup. Must be
                                                                 zero for NIX and NPA. */
        uint64_t reserved_14_15        : 2;
        uint64_t exec                  : 1;  /**< [ 13: 13](R/W1S/H) Execute lookup. Writing a one to this bit initiates the reverse lookup
                                                                 from {[PF_FUNC], [SLOT]}. Hardware writes the lookup result to {[LF_VALID],
                                                                 [LF]} and clears this bit when done. */
        uint64_t lf_valid              : 1;  /**< [ 12: 12](RO/H) When set, indicates local function [LF] is provisioned to the VF/PF slot
                                                                 indexed by this register. When clear, a local function is not provisioned
                                                                 to the VF/PF slot. */
        uint64_t lf                    : 12; /**< [ 11:  0](RO/H) When [LF_VALID] is set, local function provisioned to the VF/PF slot. */
#else /* Word 0 - Little Endian */
        uint64_t lf                    : 12; /**< [ 11:  0](RO/H) When [LF_VALID] is set, local function provisioned to the VF/PF slot. */
        uint64_t lf_valid              : 1;  /**< [ 12: 12](RO/H) When set, indicates local function [LF] is provisioned to the VF/PF slot
                                                                 indexed by this register. When clear, a local function is not provisioned
                                                                 to the VF/PF slot. */
        uint64_t exec                  : 1;  /**< [ 13: 13](R/W1S/H) Execute lookup. Writing a one to this bit initiates the reverse lookup
                                                                 from {[PF_FUNC], [SLOT]}. Hardware writes the lookup result to {[LF_VALID],
                                                                 [LF]} and clears this bit when done. */
        uint64_t reserved_14_15        : 2;
        uint64_t slot                  : 8;  /**< [ 23: 16](R/W) Slot within the VF/PF selected by [PF_FUNC] for reverse lookup. Must be
                                                                 zero for NIX and NPA. */
        uint64_t pf_func               : 16; /**< [ 39: 24](R/W) RVU VF/PF for reverse lookup. Format defined by RVU_PF_FUNC_S. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_af_rvu_lf_cfg_debug_s cn; */
};
typedef union bdk_tim_af_rvu_lf_cfg_debug bdk_tim_af_rvu_lf_cfg_debug_t;

#define BDK_TIM_AF_RVU_LF_CFG_DEBUG BDK_TIM_AF_RVU_LF_CFG_DEBUG_FUNC()
static inline uint64_t BDK_TIM_AF_RVU_LF_CFG_DEBUG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_AF_RVU_LF_CFG_DEBUG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090030000ll;
    __bdk_csr_fatal("TIM_AF_RVU_LF_CFG_DEBUG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_AF_RVU_LF_CFG_DEBUG bdk_tim_af_rvu_lf_cfg_debug_t
#define bustype_BDK_TIM_AF_RVU_LF_CFG_DEBUG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_AF_RVU_LF_CFG_DEBUG "TIM_AF_RVU_LF_CFG_DEBUG"
#define device_bar_BDK_TIM_AF_RVU_LF_CFG_DEBUG 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_AF_RVU_LF_CFG_DEBUG 0
#define arguments_BDK_TIM_AF_RVU_LF_CFG_DEBUG -1,-1,-1,-1

/**
 * Register (NCB) tim_bist_result
 *
 * TIM BIST Result Register
 * This register provides access to the internal timer BIST results. Each bit is the BIST result
 * of an individual memory (per bit, 0 = pass and 1 = fail).
 */
union bdk_tim_bist_result
{
    uint64_t u;
    struct bdk_tim_bist_result_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t bsk_mem               : 1;  /**< [  9:  9](RO/H) BIST result of the BSK memory. */
        uint64_t pf_msix_mem           : 1;  /**< [  8:  8](RO/H) BIST result of the PF_MSIX memory. */
        uint64_t vf_msix_mem           : 1;  /**< [  7:  7](RO/H) BIST result of the VF_MSIX memory. */
        uint64_t wqe_fifo              : 1;  /**< [  6:  6](RO/H) BIST result of the NCB WQE FIFO. */
        uint64_t csrf_fifo             : 1;  /**< [  5:  5](RO/H) Not used for this memory. Held at 0. */
        uint64_t lslr_fifo             : 1;  /**< [  4:  4](RO/H) BIST result of the NCB LSLR FIFO. */
        uint64_t ctl2                  : 1;  /**< [  3:  3](RO/H) BIST result of the CTL2 memory. */
        uint64_t ctl1                  : 1;  /**< [  2:  2](RO/H) BIST result of the CTL1 memory. */
        uint64_t base                  : 1;  /**< [  1:  1](RO/H) BIST result of the BASE memory. */
        uint64_t ctl0_mem              : 1;  /**< [  0:  0](RO/H) BIST result of the CTL0 memory. */
#else /* Word 0 - Little Endian */
        uint64_t ctl0_mem              : 1;  /**< [  0:  0](RO/H) BIST result of the CTL0 memory. */
        uint64_t base                  : 1;  /**< [  1:  1](RO/H) BIST result of the BASE memory. */
        uint64_t ctl1                  : 1;  /**< [  2:  2](RO/H) BIST result of the CTL1 memory. */
        uint64_t ctl2                  : 1;  /**< [  3:  3](RO/H) BIST result of the CTL2 memory. */
        uint64_t lslr_fifo             : 1;  /**< [  4:  4](RO/H) BIST result of the NCB LSLR FIFO. */
        uint64_t csrf_fifo             : 1;  /**< [  5:  5](RO/H) Not used for this memory. Held at 0. */
        uint64_t wqe_fifo              : 1;  /**< [  6:  6](RO/H) BIST result of the NCB WQE FIFO. */
        uint64_t vf_msix_mem           : 1;  /**< [  7:  7](RO/H) BIST result of the VF_MSIX memory. */
        uint64_t pf_msix_mem           : 1;  /**< [  8:  8](RO/H) BIST result of the PF_MSIX memory. */
        uint64_t bsk_mem               : 1;  /**< [  9:  9](RO/H) BIST result of the BSK memory. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_bist_result_s cn; */
};
typedef union bdk_tim_bist_result bdk_tim_bist_result_t;

#define BDK_TIM_BIST_RESULT BDK_TIM_BIST_RESULT_FUNC()
static inline uint64_t BDK_TIM_BIST_RESULT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_BIST_RESULT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000020ll;
    __bdk_csr_fatal("TIM_BIST_RESULT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_BIST_RESULT bdk_tim_bist_result_t
#define bustype_BDK_TIM_BIST_RESULT BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_BIST_RESULT "TIM_BIST_RESULT"
#define device_bar_BDK_TIM_BIST_RESULT 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_BIST_RESULT 0
#define arguments_BDK_TIM_BIST_RESULT -1,-1,-1,-1

/**
 * Register (NCB) tim_bkt_skip_ena_w1c
 *
 * TIM Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_tim_bkt_skip_ena_w1c
{
    uint64_t u;
    struct bdk_tim_bkt_skip_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for TIM_BKT_SKIP_INT[BKT_SKIP]. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for TIM_BKT_SKIP_INT[BKT_SKIP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_bkt_skip_ena_w1c_s cn; */
};
typedef union bdk_tim_bkt_skip_ena_w1c bdk_tim_bkt_skip_ena_w1c_t;

#define BDK_TIM_BKT_SKIP_ENA_W1C BDK_TIM_BKT_SKIP_ENA_W1C_FUNC()
static inline uint64_t BDK_TIM_BKT_SKIP_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_BKT_SKIP_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000100ll;
    __bdk_csr_fatal("TIM_BKT_SKIP_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_BKT_SKIP_ENA_W1C bdk_tim_bkt_skip_ena_w1c_t
#define bustype_BDK_TIM_BKT_SKIP_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_BKT_SKIP_ENA_W1C "TIM_BKT_SKIP_ENA_W1C"
#define device_bar_BDK_TIM_BKT_SKIP_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_BKT_SKIP_ENA_W1C 0
#define arguments_BDK_TIM_BKT_SKIP_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) tim_bkt_skip_ena_w1s
 *
 * TIM Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_tim_bkt_skip_ena_w1s
{
    uint64_t u;
    struct bdk_tim_bkt_skip_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for TIM_BKT_SKIP_INT[BKT_SKIP]. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for TIM_BKT_SKIP_INT[BKT_SKIP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_bkt_skip_ena_w1s_s cn; */
};
typedef union bdk_tim_bkt_skip_ena_w1s bdk_tim_bkt_skip_ena_w1s_t;

#define BDK_TIM_BKT_SKIP_ENA_W1S BDK_TIM_BKT_SKIP_ENA_W1S_FUNC()
static inline uint64_t BDK_TIM_BKT_SKIP_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_BKT_SKIP_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000108ll;
    __bdk_csr_fatal("TIM_BKT_SKIP_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_BKT_SKIP_ENA_W1S bdk_tim_bkt_skip_ena_w1s_t
#define bustype_BDK_TIM_BKT_SKIP_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_BKT_SKIP_ENA_W1S "TIM_BKT_SKIP_ENA_W1S"
#define device_bar_BDK_TIM_BKT_SKIP_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_BKT_SKIP_ENA_W1S 0
#define arguments_BDK_TIM_BKT_SKIP_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) tim_bkt_skip_int
 *
 * TIM BKT_SKIP_INT Interrupt Register
 */
union bdk_tim_bkt_skip_int
{
    uint64_t u;
    struct bdk_tim_bkt_skip_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1C/H) Interrupt bit per ring. Each bit corresponds to rings 63:0 respectively.
                                                                 If set, at least one bucket was skipped by hardware, when a ring has expired.
                                                                 Hardware sets this when TIM attempted traversal but the bucket's
                                                                 TIM_MEM_BUCKET_S[SBT] was set or TIM_MEM_BUCKET_S[LOCK] was non-zero. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1C/H) Interrupt bit per ring. Each bit corresponds to rings 63:0 respectively.
                                                                 If set, at least one bucket was skipped by hardware, when a ring has expired.
                                                                 Hardware sets this when TIM attempted traversal but the bucket's
                                                                 TIM_MEM_BUCKET_S[SBT] was set or TIM_MEM_BUCKET_S[LOCK] was non-zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_bkt_skip_int_s cn; */
};
typedef union bdk_tim_bkt_skip_int bdk_tim_bkt_skip_int_t;

#define BDK_TIM_BKT_SKIP_INT BDK_TIM_BKT_SKIP_INT_FUNC()
static inline uint64_t BDK_TIM_BKT_SKIP_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_BKT_SKIP_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000030ll;
    __bdk_csr_fatal("TIM_BKT_SKIP_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_BKT_SKIP_INT bdk_tim_bkt_skip_int_t
#define bustype_BDK_TIM_BKT_SKIP_INT BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_BKT_SKIP_INT "TIM_BKT_SKIP_INT"
#define device_bar_BDK_TIM_BKT_SKIP_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_BKT_SKIP_INT 0
#define arguments_BDK_TIM_BKT_SKIP_INT -1,-1,-1,-1

/**
 * Register (NCB) tim_bkt_skip_int_status#
 *
 * TIM BKT_SKIP_INT Ring Status Register
 */
union bdk_tim_bkt_skip_int_statusx
{
    uint64_t u;
    struct bdk_tim_bkt_skip_int_statusx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t bkt_skip_id           : 20; /**< [ 19:  0](RO/H) When TIM_BKT_SKIP_INT\<{a}\> gets set, this field reflects the bucket that was skipped
                                                                 for ring {a}. For diagnostic use only, as only one ring's status is kept. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip_id           : 20; /**< [ 19:  0](RO/H) When TIM_BKT_SKIP_INT\<{a}\> gets set, this field reflects the bucket that was skipped
                                                                 for ring {a}. For diagnostic use only, as only one ring's status is kept. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_bkt_skip_int_statusx_s cn; */
};
typedef union bdk_tim_bkt_skip_int_statusx bdk_tim_bkt_skip_int_statusx_t;

static inline uint64_t BDK_TIM_BKT_SKIP_INT_STATUSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_BKT_SKIP_INT_STATUSX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858000002c00ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_BKT_SKIP_INT_STATUSX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_BKT_SKIP_INT_STATUSX(a) bdk_tim_bkt_skip_int_statusx_t
#define bustype_BDK_TIM_BKT_SKIP_INT_STATUSX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_BKT_SKIP_INT_STATUSX(a) "TIM_BKT_SKIP_INT_STATUSX"
#define device_bar_BDK_TIM_BKT_SKIP_INT_STATUSX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_BKT_SKIP_INT_STATUSX(a) (a)
#define arguments_BDK_TIM_BKT_SKIP_INT_STATUSX(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_bkt_skip_int_w1s
 *
 * TIM Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_tim_bkt_skip_int_w1s
{
    uint64_t u;
    struct bdk_tim_bkt_skip_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1S/H) Reads or sets TIM_BKT_SKIP_INT[BKT_SKIP]. */
#else /* Word 0 - Little Endian */
        uint64_t bkt_skip              : 64; /**< [ 63:  0](R/W1S/H) Reads or sets TIM_BKT_SKIP_INT[BKT_SKIP]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_bkt_skip_int_w1s_s cn; */
};
typedef union bdk_tim_bkt_skip_int_w1s bdk_tim_bkt_skip_int_w1s_t;

#define BDK_TIM_BKT_SKIP_INT_W1S BDK_TIM_BKT_SKIP_INT_W1S_FUNC()
static inline uint64_t BDK_TIM_BKT_SKIP_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_BKT_SKIP_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000040ll;
    __bdk_csr_fatal("TIM_BKT_SKIP_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_BKT_SKIP_INT_W1S bdk_tim_bkt_skip_int_w1s_t
#define bustype_BDK_TIM_BKT_SKIP_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_BKT_SKIP_INT_W1S "TIM_BKT_SKIP_INT_W1S"
#define device_bar_BDK_TIM_BKT_SKIP_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_BKT_SKIP_INT_W1S 0
#define arguments_BDK_TIM_BKT_SKIP_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) tim_bp_test
 *
 * INTERNAL: TIM Backpressure Test Register
 */
union bdk_tim_bp_test
{
    uint64_t u;
    struct bdk_tim_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t ncb_wqe_bp            : 1;  /**< [ 11: 11](R/W) NCB WQE CSR FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_wqe FIFO valid
                                                                 (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill. */
        uint64_t ncbmux_dstmem_bp      : 1;  /**< [ 10: 10](R/W) NCBMUX DSTMEM FIFO backpressure.
                                                                 When asserted, the tim.tim_csr.tim_csr_ncbmux.ncb_dstmem FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill.
                                                                 Only the RSL path can be used when this bit is set. */
        uint64_t ncbmux_ctlmem_bp      : 1;  /**< [  9:  9](R/W) NCBMUX CTLMEM FIFO backpressure.
                                                                 When asserted, the tim.tim_csr.tim_csr_ncbmux.ncb_ctlmem FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill.
                                                                 Only the RSL path can be used when this bit is set. */
        uint64_t ncb_fpa_bp            : 1;  /**< [  8:  8](R/W) NCB CSR FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.ncbi_csrf FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill. */
        uint64_t ncb_sta_bp            : 4;  /**< [  7:  4](R/W) NCB STA backpressure.
                                                                 When asserted, this blocks specific STAs (3-0) from sending
                                                                 requests. This combines the tim.tim_ncb.tim_ncb_tag.sfsta[3:0]_fifo
                                                                 and tim.tim_ncb.tim_ncb_tag.nwfsta[3:0]_fifo backpressuring. */
        uint64_t ncb_csrf_bp           : 1;  /**< [  3:  3](R/W) NCB CSR FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.ncbi_csrf FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, beyond what was already arbitrated
                                                                 for the NCBI bus, allowing it to fill.
                                                                 Only the RSL path can be used for access when this bit is
                                                                 set. All NCB-based CSR accesses will not respond, and NCB
                                                                 credits will not be returned, once the downstream FIFOs
                                                                 fill up. */
        uint64_t ncb_lslr_bp           : 1;  /**< [  2:  2](R/W) NCB LSLR FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.lslr_mem FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, beyond what was already arbitrated
                                                                 for the NCBI bus, allowing it to fill.
                                                                 This will stop requests from the STA engines, when the
                                                                 FIFO reaches full. */
        uint64_t ncbi_rsp_gnt_bp       : 1;  /**< [  1:  1](R/W) NCBI response grant FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.ncbi_cgntf FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill.
                                                                 Only the RSL path can be used for access when this bit is
                                                                 set. All NCB-based CSR accesses will not respond, and NCB
                                                                 credits will not be returned, once the downstream FIFOs
                                                                 fill up. */
        uint64_t ncbi_req_gnt_bp       : 1;  /**< [  0:  0](R/W) NCBI request grant FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.ncbi_lgntf FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill.
                                                                 This will stop requests from the STA engines, when both
                                                                 this FIFO, and the LSLR FIFO reaches full. */
#else /* Word 0 - Little Endian */
        uint64_t ncbi_req_gnt_bp       : 1;  /**< [  0:  0](R/W) NCBI request grant FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.ncbi_lgntf FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill.
                                                                 This will stop requests from the STA engines, when both
                                                                 this FIFO, and the LSLR FIFO reaches full. */
        uint64_t ncbi_rsp_gnt_bp       : 1;  /**< [  1:  1](R/W) NCBI response grant FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.ncbi_cgntf FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill.
                                                                 Only the RSL path can be used for access when this bit is
                                                                 set. All NCB-based CSR accesses will not respond, and NCB
                                                                 credits will not be returned, once the downstream FIFOs
                                                                 fill up. */
        uint64_t ncb_lslr_bp           : 1;  /**< [  2:  2](R/W) NCB LSLR FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.lslr_mem FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, beyond what was already arbitrated
                                                                 for the NCBI bus, allowing it to fill.
                                                                 This will stop requests from the STA engines, when the
                                                                 FIFO reaches full. */
        uint64_t ncb_csrf_bp           : 1;  /**< [  3:  3](R/W) NCB CSR FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.ncbi_csrf FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, beyond what was already arbitrated
                                                                 for the NCBI bus, allowing it to fill.
                                                                 Only the RSL path can be used for access when this bit is
                                                                 set. All NCB-based CSR accesses will not respond, and NCB
                                                                 credits will not be returned, once the downstream FIFOs
                                                                 fill up. */
        uint64_t ncb_sta_bp            : 4;  /**< [  7:  4](R/W) NCB STA backpressure.
                                                                 When asserted, this blocks specific STAs (3-0) from sending
                                                                 requests. This combines the tim.tim_ncb.tim_ncb_tag.sfsta[3:0]_fifo
                                                                 and tim.tim_ncb.tim_ncb_tag.nwfsta[3:0]_fifo backpressuring. */
        uint64_t ncb_fpa_bp            : 1;  /**< [  8:  8](R/W) NCB CSR FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_ncb_arb.ncbi_csrf FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill. */
        uint64_t ncbmux_ctlmem_bp      : 1;  /**< [  9:  9](R/W) NCBMUX CTLMEM FIFO backpressure.
                                                                 When asserted, the tim.tim_csr.tim_csr_ncbmux.ncb_ctlmem FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill.
                                                                 Only the RSL path can be used when this bit is set. */
        uint64_t ncbmux_dstmem_bp      : 1;  /**< [ 10: 10](R/W) NCBMUX DSTMEM FIFO backpressure.
                                                                 When asserted, the tim.tim_csr.tim_csr_ncbmux.ncb_dstmem FIFO
                                                                 valid (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill.
                                                                 Only the RSL path can be used when this bit is set. */
        uint64_t ncb_wqe_bp            : 1;  /**< [ 11: 11](R/W) NCB WQE CSR FIFO backpressure.
                                                                 When asserted, the tim.tim_ncb.tim_wqe FIFO valid
                                                                 (an entry is in the FIFO) is blocked. This creates
                                                                 no popping of the FIFO, allowing it to fill. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_bp_test_s cn; */
};
typedef union bdk_tim_bp_test bdk_tim_bp_test_t;

#define BDK_TIM_BP_TEST BDK_TIM_BP_TEST_FUNC()
static inline uint64_t BDK_TIM_BP_TEST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_BP_TEST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000150ll;
    __bdk_csr_fatal("TIM_BP_TEST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_BP_TEST bdk_tim_bp_test_t
#define bustype_BDK_TIM_BP_TEST BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_BP_TEST "TIM_BP_TEST"
#define device_bar_BDK_TIM_BP_TEST 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_BP_TEST 0
#define arguments_BDK_TIM_BP_TEST -1,-1,-1,-1

/**
 * Register (NCB) tim_dbg2
 *
 * TIM Debug 2 Register
 */
union bdk_tim_dbg2
{
    uint64_t u;
    struct bdk_tim_dbg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mem_alloc_reg         : 8;  /**< [ 63: 56](RO/H) NCBI load memory allocation status. */
        uint64_t reserved_54_55        : 2;
        uint64_t cgnt_fifo_level       : 4;  /**< [ 53: 50](RO/H) NCBI grant for response FIFO level. */
        uint64_t lgnt_fifo_level       : 4;  /**< [ 49: 46](RO/H) NCBI grant for request FIFO level. */
        uint64_t reserved_45           : 1;
        uint64_t fpa_fifo_level        : 3;  /**< [ 44: 42](RO/H) FPA FIFO level. */
        uint64_t lslr_fifo_level       : 6;  /**< [ 41: 36](RO/H) NCBI requests FIFO level. */
        uint64_t csrf_fifo_level       : 4;  /**< [ 35: 32](RO/H) NCBI requests FIFO level. */
        uint64_t reserved_28_31        : 4;
        uint64_t wqe_fifo_level        : 8;  /**< [ 27: 20](RO/H) NCBI WQE LD FIFO level. */
        uint64_t fsm3_state            : 5;  /**< [ 19: 15](RO/H) FSM 3 current state. */
        uint64_t fsm2_state            : 5;  /**< [ 14: 10](RO/H) FSM 2 current state. */
        uint64_t fsm1_state            : 5;  /**< [  9:  5](RO/H) FSM 1 current state. */
        uint64_t fsm0_state            : 5;  /**< [  4:  0](RO/H) FSM 0 current state. */
#else /* Word 0 - Little Endian */
        uint64_t fsm0_state            : 5;  /**< [  4:  0](RO/H) FSM 0 current state. */
        uint64_t fsm1_state            : 5;  /**< [  9:  5](RO/H) FSM 1 current state. */
        uint64_t fsm2_state            : 5;  /**< [ 14: 10](RO/H) FSM 2 current state. */
        uint64_t fsm3_state            : 5;  /**< [ 19: 15](RO/H) FSM 3 current state. */
        uint64_t wqe_fifo_level        : 8;  /**< [ 27: 20](RO/H) NCBI WQE LD FIFO level. */
        uint64_t reserved_28_31        : 4;
        uint64_t csrf_fifo_level       : 4;  /**< [ 35: 32](RO/H) NCBI requests FIFO level. */
        uint64_t lslr_fifo_level       : 6;  /**< [ 41: 36](RO/H) NCBI requests FIFO level. */
        uint64_t fpa_fifo_level        : 3;  /**< [ 44: 42](RO/H) FPA FIFO level. */
        uint64_t reserved_45           : 1;
        uint64_t lgnt_fifo_level       : 4;  /**< [ 49: 46](RO/H) NCBI grant for request FIFO level. */
        uint64_t cgnt_fifo_level       : 4;  /**< [ 53: 50](RO/H) NCBI grant for response FIFO level. */
        uint64_t reserved_54_55        : 2;
        uint64_t mem_alloc_reg         : 8;  /**< [ 63: 56](RO/H) NCBI load memory allocation status. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_dbg2_s cn; */
};
typedef union bdk_tim_dbg2 bdk_tim_dbg2_t;

#define BDK_TIM_DBG2 BDK_TIM_DBG2_FUNC()
static inline uint64_t BDK_TIM_DBG2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_DBG2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8580000000a0ll;
    __bdk_csr_fatal("TIM_DBG2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_DBG2 bdk_tim_dbg2_t
#define bustype_BDK_TIM_DBG2 BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_DBG2 "TIM_DBG2"
#define device_bar_BDK_TIM_DBG2 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_DBG2 0
#define arguments_BDK_TIM_DBG2 -1,-1,-1,-1

/**
 * Register (NCB) tim_dbg3
 *
 * TIM Debug 3 Register
 */
union bdk_tim_dbg3
{
    uint64_t u;
    struct bdk_tim_dbg3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t rings_pending_vec     : 64; /**< [ 63:  0](RO/H) Pending rings vector. Indicates which rings in TIM are pending traversal. Bit 0
                                                                 represents ring 0 while bit 63 represents ring 63. */
#else /* Word 0 - Little Endian */
        uint64_t rings_pending_vec     : 64; /**< [ 63:  0](RO/H) Pending rings vector. Indicates which rings in TIM are pending traversal. Bit 0
                                                                 represents ring 0 while bit 63 represents ring 63. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_dbg3_s cn; */
};
typedef union bdk_tim_dbg3 bdk_tim_dbg3_t;

#define BDK_TIM_DBG3 BDK_TIM_DBG3_FUNC()
static inline uint64_t BDK_TIM_DBG3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_DBG3_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8580000000a8ll;
    __bdk_csr_fatal("TIM_DBG3", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_DBG3 bdk_tim_dbg3_t
#define bustype_BDK_TIM_DBG3 BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_DBG3 "TIM_DBG3"
#define device_bar_BDK_TIM_DBG3 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_DBG3 0
#define arguments_BDK_TIM_DBG3 -1,-1,-1,-1

/**
 * Register (NCB) tim_ecc_cfg
 *
 * TIM ECC Configuration Register
 */
union bdk_tim_ecc_cfg
{
    uint64_t u;
    struct bdk_tim_ecc_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t auto_corr             : 1;  /**< [  3:  3](R/W) Reserved.
                                                                 Internal:
                                                                 Must be 0.
                                                                 Enable ECC auto-correction of CTL0-2 and BASE RAM single-bit errors.
                                                                 The internal logic will write back the corrected
                                                                 data to the location reporting a single-bit error. */
        uint64_t ecc_flp_syn           : 2;  /**< [  2:  1](R/W) ECC flip syndrome. Flip the ECC's syndrome for testing purposes, to test SBE and DBE ECC
                                                                 interrupts. */
        uint64_t ecc_en                : 1;  /**< [  0:  0](R/W) Enable ECC correction of the ring data structure memory.
                                                                 Refer to TIM_ECCERR_INT for a list of ECC-protected memories. */
#else /* Word 0 - Little Endian */
        uint64_t ecc_en                : 1;  /**< [  0:  0](R/W) Enable ECC correction of the ring data structure memory.
                                                                 Refer to TIM_ECCERR_INT for a list of ECC-protected memories. */
        uint64_t ecc_flp_syn           : 2;  /**< [  2:  1](R/W) ECC flip syndrome. Flip the ECC's syndrome for testing purposes, to test SBE and DBE ECC
                                                                 interrupts. */
        uint64_t auto_corr             : 1;  /**< [  3:  3](R/W) Reserved.
                                                                 Internal:
                                                                 Must be 0.
                                                                 Enable ECC auto-correction of CTL0-2 and BASE RAM single-bit errors.
                                                                 The internal logic will write back the corrected
                                                                 data to the location reporting a single-bit error. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_ecc_cfg_s cn; */
};
typedef union bdk_tim_ecc_cfg bdk_tim_ecc_cfg_t;

#define BDK_TIM_ECC_CFG BDK_TIM_ECC_CFG_FUNC()
static inline uint64_t BDK_TIM_ECC_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_ECC_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000018ll;
    __bdk_csr_fatal("TIM_ECC_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_ECC_CFG bdk_tim_ecc_cfg_t
#define bustype_BDK_TIM_ECC_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_ECC_CFG "TIM_ECC_CFG"
#define device_bar_BDK_TIM_ECC_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_ECC_CFG 0
#define arguments_BDK_TIM_ECC_CFG -1,-1,-1,-1

/**
 * Register (NCB) tim_eccerr_ena_w1c
 *
 * TIM ECC Error Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_tim_eccerr_ena_w1c
{
    uint64_t u;
    struct bdk_tim_eccerr_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t msix_pmem_dbe         : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[MSIX_PMEM_DBE]. */
        uint64_t msix_pmem_sbe         : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[MSIX_PMEM_SBE]. */
        uint64_t msix_vmem_dbe         : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[MSIX_VMEM_DBE]. */
        uint64_t msix_vmem_sbe         : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[MSIX_VMEM_SBE]. */
        uint64_t ctl0_dbe              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL0_DBE]. */
        uint64_t ctl0_sbe              : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL0_SBE]. */
        uint64_t ctl1_dbe              : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL1_DBE]. */
        uint64_t ctl1_sbe              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL1_SBE]. */
        uint64_t ctl2_dbe              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL2_DBE]. */
        uint64_t ctl2_sbe              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL2_SBE]. */
        uint64_t base_dbe              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[BASE_DBE]. */
        uint64_t base_sbe              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[BASE_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t base_sbe              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[BASE_SBE]. */
        uint64_t base_dbe              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[BASE_DBE]. */
        uint64_t ctl2_sbe              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL2_SBE]. */
        uint64_t ctl2_dbe              : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL2_DBE]. */
        uint64_t ctl1_sbe              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL1_SBE]. */
        uint64_t ctl1_dbe              : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL1_DBE]. */
        uint64_t ctl0_sbe              : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL0_SBE]. */
        uint64_t ctl0_dbe              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[CTL0_DBE]. */
        uint64_t msix_vmem_sbe         : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[MSIX_VMEM_SBE]. */
        uint64_t msix_vmem_dbe         : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[MSIX_VMEM_DBE]. */
        uint64_t msix_pmem_sbe         : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[MSIX_PMEM_SBE]. */
        uint64_t msix_pmem_dbe         : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for TIM_ECCERR_INT[MSIX_PMEM_DBE]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_eccerr_ena_w1c_s cn; */
};
typedef union bdk_tim_eccerr_ena_w1c bdk_tim_eccerr_ena_w1c_t;

#define BDK_TIM_ECCERR_ENA_W1C BDK_TIM_ECCERR_ENA_W1C_FUNC()
static inline uint64_t BDK_TIM_ECCERR_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_ECCERR_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000110ll;
    __bdk_csr_fatal("TIM_ECCERR_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_ECCERR_ENA_W1C bdk_tim_eccerr_ena_w1c_t
#define bustype_BDK_TIM_ECCERR_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_ECCERR_ENA_W1C "TIM_ECCERR_ENA_W1C"
#define device_bar_BDK_TIM_ECCERR_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_ECCERR_ENA_W1C 0
#define arguments_BDK_TIM_ECCERR_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) tim_eccerr_ena_w1s
 *
 * TIM ECC Error Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_tim_eccerr_ena_w1s
{
    uint64_t u;
    struct bdk_tim_eccerr_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t msix_pmem_dbe         : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[MSIX_PMEM_DBE]. */
        uint64_t msix_pmem_sbe         : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[MSIX_PMEM_SBE]. */
        uint64_t msix_vmem_dbe         : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[MSIX_VMEM_DBE]. */
        uint64_t msix_vmem_sbe         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[MSIX_VMEM_SBE]. */
        uint64_t ctl0_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL0_DBE]. */
        uint64_t ctl0_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL0_SBE]. */
        uint64_t ctl1_dbe              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL1_DBE]. */
        uint64_t ctl1_sbe              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL1_SBE]. */
        uint64_t ctl2_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL2_DBE]. */
        uint64_t ctl2_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL2_SBE]. */
        uint64_t base_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[BASE_DBE]. */
        uint64_t base_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[BASE_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t base_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[BASE_SBE]. */
        uint64_t base_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[BASE_DBE]. */
        uint64_t ctl2_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL2_SBE]. */
        uint64_t ctl2_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL2_DBE]. */
        uint64_t ctl1_sbe              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL1_SBE]. */
        uint64_t ctl1_dbe              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL1_DBE]. */
        uint64_t ctl0_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL0_SBE]. */
        uint64_t ctl0_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[CTL0_DBE]. */
        uint64_t msix_vmem_sbe         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[MSIX_VMEM_SBE]. */
        uint64_t msix_vmem_dbe         : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[MSIX_VMEM_DBE]. */
        uint64_t msix_pmem_sbe         : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[MSIX_PMEM_SBE]. */
        uint64_t msix_pmem_dbe         : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for TIM_ECCERR_INT[MSIX_PMEM_DBE]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_eccerr_ena_w1s_s cn; */
};
typedef union bdk_tim_eccerr_ena_w1s bdk_tim_eccerr_ena_w1s_t;

#define BDK_TIM_ECCERR_ENA_W1S BDK_TIM_ECCERR_ENA_W1S_FUNC()
static inline uint64_t BDK_TIM_ECCERR_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_ECCERR_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000118ll;
    __bdk_csr_fatal("TIM_ECCERR_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_ECCERR_ENA_W1S bdk_tim_eccerr_ena_w1s_t
#define bustype_BDK_TIM_ECCERR_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_ECCERR_ENA_W1S "TIM_ECCERR_ENA_W1S"
#define device_bar_BDK_TIM_ECCERR_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_ECCERR_ENA_W1S 0
#define arguments_BDK_TIM_ECCERR_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) tim_eccerr_int
 *
 * TIM ECC Error Interrupt Register
 */
union bdk_tim_eccerr_int
{
    uint64_t u;
    struct bdk_tim_eccerr_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t msix_pmem_dbe         : 1;  /**< [ 11: 11](R/W1C/H) MSIX PMEM memory had a double-bit error. */
        uint64_t msix_pmem_sbe         : 1;  /**< [ 10: 10](R/W1C/H) MSIX PMEM memory had a single-bit error. */
        uint64_t msix_vmem_dbe         : 1;  /**< [  9:  9](R/W1C/H) MSIX VMEM memory had a double-bit error. */
        uint64_t msix_vmem_sbe         : 1;  /**< [  8:  8](R/W1C/H) MSIX VMEM memory had a single-bit error. */
        uint64_t ctl0_dbe              : 1;  /**< [  7:  7](R/W1C/H) TIM CTL0 memory had a double-bit error. */
        uint64_t ctl0_sbe              : 1;  /**< [  6:  6](R/W1C/H) TIM CTL0 memory had a single-bit error. */
        uint64_t ctl1_dbe              : 1;  /**< [  5:  5](R/W1C/H) TIM CTL1 memory had a double-bit error. */
        uint64_t ctl1_sbe              : 1;  /**< [  4:  4](R/W1C/H) TIM CTL1 memory had a single-bit error. */
        uint64_t ctl2_dbe              : 1;  /**< [  3:  3](R/W1C/H) TIM CTL2 memory had a double-bit error. */
        uint64_t ctl2_sbe              : 1;  /**< [  2:  2](R/W1C/H) TIM CTL2 memory had a single-bit error. */
        uint64_t base_dbe              : 1;  /**< [  1:  1](R/W1C/H) TIM BASE memory had a double-bit error. */
        uint64_t base_sbe              : 1;  /**< [  0:  0](R/W1C/H) TIM BASE memory had a single-bit error. */
#else /* Word 0 - Little Endian */
        uint64_t base_sbe              : 1;  /**< [  0:  0](R/W1C/H) TIM BASE memory had a single-bit error. */
        uint64_t base_dbe              : 1;  /**< [  1:  1](R/W1C/H) TIM BASE memory had a double-bit error. */
        uint64_t ctl2_sbe              : 1;  /**< [  2:  2](R/W1C/H) TIM CTL2 memory had a single-bit error. */
        uint64_t ctl2_dbe              : 1;  /**< [  3:  3](R/W1C/H) TIM CTL2 memory had a double-bit error. */
        uint64_t ctl1_sbe              : 1;  /**< [  4:  4](R/W1C/H) TIM CTL1 memory had a single-bit error. */
        uint64_t ctl1_dbe              : 1;  /**< [  5:  5](R/W1C/H) TIM CTL1 memory had a double-bit error. */
        uint64_t ctl0_sbe              : 1;  /**< [  6:  6](R/W1C/H) TIM CTL0 memory had a single-bit error. */
        uint64_t ctl0_dbe              : 1;  /**< [  7:  7](R/W1C/H) TIM CTL0 memory had a double-bit error. */
        uint64_t msix_vmem_sbe         : 1;  /**< [  8:  8](R/W1C/H) MSIX VMEM memory had a single-bit error. */
        uint64_t msix_vmem_dbe         : 1;  /**< [  9:  9](R/W1C/H) MSIX VMEM memory had a double-bit error. */
        uint64_t msix_pmem_sbe         : 1;  /**< [ 10: 10](R/W1C/H) MSIX PMEM memory had a single-bit error. */
        uint64_t msix_pmem_dbe         : 1;  /**< [ 11: 11](R/W1C/H) MSIX PMEM memory had a double-bit error. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_eccerr_int_s cn; */
};
typedef union bdk_tim_eccerr_int bdk_tim_eccerr_int_t;

#define BDK_TIM_ECCERR_INT BDK_TIM_ECCERR_INT_FUNC()
static inline uint64_t BDK_TIM_ECCERR_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_ECCERR_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000060ll;
    __bdk_csr_fatal("TIM_ECCERR_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_ECCERR_INT bdk_tim_eccerr_int_t
#define bustype_BDK_TIM_ECCERR_INT BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_ECCERR_INT "TIM_ECCERR_INT"
#define device_bar_BDK_TIM_ECCERR_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_ECCERR_INT 0
#define arguments_BDK_TIM_ECCERR_INT -1,-1,-1,-1

/**
 * Register (NCB) tim_eccerr_int_w1s
 *
 * TIM ECC Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_tim_eccerr_int_w1s
{
    uint64_t u;
    struct bdk_tim_eccerr_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t msix_pmem_dbe         : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets TIM_ECCERR_INT[MSIX_PMEM_DBE]. */
        uint64_t msix_pmem_sbe         : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets TIM_ECCERR_INT[MSIX_PMEM_SBE]. */
        uint64_t msix_vmem_dbe         : 1;  /**< [  9:  9](R/W1S/H) Reads or sets TIM_ECCERR_INT[MSIX_VMEM_DBE]. */
        uint64_t msix_vmem_sbe         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets TIM_ECCERR_INT[MSIX_VMEM_SBE]. */
        uint64_t ctl0_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL0_DBE]. */
        uint64_t ctl0_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL0_SBE]. */
        uint64_t ctl1_dbe              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL1_DBE]. */
        uint64_t ctl1_sbe              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL1_SBE]. */
        uint64_t ctl2_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL2_DBE]. */
        uint64_t ctl2_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL2_SBE]. */
        uint64_t base_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets TIM_ECCERR_INT[BASE_DBE]. */
        uint64_t base_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_ECCERR_INT[BASE_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t base_sbe              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_ECCERR_INT[BASE_SBE]. */
        uint64_t base_dbe              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets TIM_ECCERR_INT[BASE_DBE]. */
        uint64_t ctl2_sbe              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL2_SBE]. */
        uint64_t ctl2_dbe              : 1;  /**< [  3:  3](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL2_DBE]. */
        uint64_t ctl1_sbe              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL1_SBE]. */
        uint64_t ctl1_dbe              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL1_DBE]. */
        uint64_t ctl0_sbe              : 1;  /**< [  6:  6](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL0_SBE]. */
        uint64_t ctl0_dbe              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets TIM_ECCERR_INT[CTL0_DBE]. */
        uint64_t msix_vmem_sbe         : 1;  /**< [  8:  8](R/W1S/H) Reads or sets TIM_ECCERR_INT[MSIX_VMEM_SBE]. */
        uint64_t msix_vmem_dbe         : 1;  /**< [  9:  9](R/W1S/H) Reads or sets TIM_ECCERR_INT[MSIX_VMEM_DBE]. */
        uint64_t msix_pmem_sbe         : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets TIM_ECCERR_INT[MSIX_PMEM_SBE]. */
        uint64_t msix_pmem_dbe         : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets TIM_ECCERR_INT[MSIX_PMEM_DBE]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_eccerr_int_w1s_s cn; */
};
typedef union bdk_tim_eccerr_int_w1s bdk_tim_eccerr_int_w1s_t;

#define BDK_TIM_ECCERR_INT_W1S BDK_TIM_ECCERR_INT_W1S_FUNC()
static inline uint64_t BDK_TIM_ECCERR_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_ECCERR_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000068ll;
    __bdk_csr_fatal("TIM_ECCERR_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_ECCERR_INT_W1S bdk_tim_eccerr_int_w1s_t
#define bustype_BDK_TIM_ECCERR_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_ECCERR_INT_W1S "TIM_ECCERR_INT_W1S"
#define device_bar_BDK_TIM_ECCERR_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_ECCERR_INT_W1S 0
#define arguments_BDK_TIM_ECCERR_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) tim_eco
 *
 * INTERNAL: TIM ECO Register
 */
union bdk_tim_eco
{
    uint64_t u;
    struct bdk_tim_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_eco_s cn; */
};
typedef union bdk_tim_eco bdk_tim_eco_t;

#define BDK_TIM_ECO BDK_TIM_ECO_FUNC()
static inline uint64_t BDK_TIM_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000140ll;
    __bdk_csr_fatal("TIM_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_ECO bdk_tim_eco_t
#define bustype_BDK_TIM_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_ECO "TIM_ECO"
#define device_bar_BDK_TIM_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_ECO 0
#define arguments_BDK_TIM_ECO -1,-1,-1,-1

/**
 * Register (NCB) tim_eng#_active
 *
 * TIM Engine Active Registers
 */
union bdk_tim_engx_active
{
    uint64_t u;
    struct bdk_tim_engx_active_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t act                   : 1;  /**< [  8:  8](RO/H) Engine active. For diagnostic use. */
        uint64_t reserved_6_7          : 2;
        uint64_t ring_id               : 6;  /**< [  5:  0](RO/H) Current ring ID. For diagnostic use. */
#else /* Word 0 - Little Endian */
        uint64_t ring_id               : 6;  /**< [  5:  0](RO/H) Current ring ID. For diagnostic use. */
        uint64_t reserved_6_7          : 2;
        uint64_t act                   : 1;  /**< [  8:  8](RO/H) Engine active. For diagnostic use. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_engx_active_s cn; */
};
typedef union bdk_tim_engx_active bdk_tim_engx_active_t;

static inline uint64_t BDK_TIM_ENGX_ACTIVE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_ENGX_ACTIVE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x858000001000ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("TIM_ENGX_ACTIVE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_ENGX_ACTIVE(a) bdk_tim_engx_active_t
#define bustype_BDK_TIM_ENGX_ACTIVE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_ENGX_ACTIVE(a) "TIM_ENGX_ACTIVE"
#define device_bar_BDK_TIM_ENGX_ACTIVE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_ENGX_ACTIVE(a) (a)
#define arguments_BDK_TIM_ENGX_ACTIVE(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_fr_rn_cycles
 *
 * TIM Free Running Cycle Count Register
 */
union bdk_tim_fr_rn_cycles
{
    uint64_t u;
    struct bdk_tim_fr_rn_cycles_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of system coprocessor-clock cycles. This register is only writable when
                                                                 TIM_REG_FLAGS[ENA_TIM] = 0. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of system coprocessor-clock cycles. This register is only writable when
                                                                 TIM_REG_FLAGS[ENA_TIM] = 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_fr_rn_cycles_s cn; */
};
typedef union bdk_tim_fr_rn_cycles bdk_tim_fr_rn_cycles_t;

#define BDK_TIM_FR_RN_CYCLES BDK_TIM_FR_RN_CYCLES_FUNC()
static inline uint64_t BDK_TIM_FR_RN_CYCLES_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_FR_RN_CYCLES_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8580000000c0ll;
    __bdk_csr_fatal("TIM_FR_RN_CYCLES", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_FR_RN_CYCLES bdk_tim_fr_rn_cycles_t
#define bustype_BDK_TIM_FR_RN_CYCLES BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_FR_RN_CYCLES "TIM_FR_RN_CYCLES"
#define device_bar_BDK_TIM_FR_RN_CYCLES 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_FR_RN_CYCLES 0
#define arguments_BDK_TIM_FR_RN_CYCLES -1,-1,-1,-1

/**
 * Register (NCB) tim_fr_rn_gpios
 *
 * TIM Free Running GPIO Count Register
 */
union bdk_tim_fr_rn_gpios
{
    uint64_t u;
    struct bdk_tim_fr_rn_gpios_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of GPIO cycles. This register is only writable when TIM_REG_FLAGS[ENA_TIM] = 0. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of GPIO cycles. This register is only writable when TIM_REG_FLAGS[ENA_TIM] = 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_fr_rn_gpios_s cn; */
};
typedef union bdk_tim_fr_rn_gpios bdk_tim_fr_rn_gpios_t;

#define BDK_TIM_FR_RN_GPIOS BDK_TIM_FR_RN_GPIOS_FUNC()
static inline uint64_t BDK_TIM_FR_RN_GPIOS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_FR_RN_GPIOS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8580000000c8ll;
    __bdk_csr_fatal("TIM_FR_RN_GPIOS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_FR_RN_GPIOS bdk_tim_fr_rn_gpios_t
#define bustype_BDK_TIM_FR_RN_GPIOS BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_FR_RN_GPIOS "TIM_FR_RN_GPIOS"
#define device_bar_BDK_TIM_FR_RN_GPIOS 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_FR_RN_GPIOS 0
#define arguments_BDK_TIM_FR_RN_GPIOS -1,-1,-1,-1

/**
 * Register (NCB) tim_fr_rn_gti
 *
 * TIM Free Running System Clock Count Register
 */
union bdk_tim_fr_rn_gti
{
    uint64_t u;
    struct bdk_tim_fr_rn_gti_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of GTI system timer cycles. This register is only writable when TIM_REG_FLAGS[ENA_TIM] = 0. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of GTI system timer cycles. This register is only writable when TIM_REG_FLAGS[ENA_TIM] = 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_fr_rn_gti_s cn; */
};
typedef union bdk_tim_fr_rn_gti bdk_tim_fr_rn_gti_t;

#define BDK_TIM_FR_RN_GTI BDK_TIM_FR_RN_GTI_FUNC()
static inline uint64_t BDK_TIM_FR_RN_GTI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_FR_RN_GTI_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8580000000d0ll;
    __bdk_csr_fatal("TIM_FR_RN_GTI", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_FR_RN_GTI bdk_tim_fr_rn_gti_t
#define bustype_BDK_TIM_FR_RN_GTI BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_FR_RN_GTI "TIM_FR_RN_GTI"
#define device_bar_BDK_TIM_FR_RN_GTI 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_FR_RN_GTI 0
#define arguments_BDK_TIM_FR_RN_GTI -1,-1,-1,-1

/**
 * Register (NCB) tim_fr_rn_ptp
 *
 * TIM Free Running PTP Count Register
 */
union bdk_tim_fr_rn_ptp
{
    uint64_t u;
    struct bdk_tim_fr_rn_ptp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of PTP cycles. This register is only writable when TIM_REG_FLAGS[ENA_TIM] = 0. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of PTP cycles. This register is only writable when TIM_REG_FLAGS[ENA_TIM] = 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_fr_rn_ptp_s cn; */
};
typedef union bdk_tim_fr_rn_ptp bdk_tim_fr_rn_ptp_t;

#define BDK_TIM_FR_RN_PTP BDK_TIM_FR_RN_PTP_FUNC()
static inline uint64_t BDK_TIM_FR_RN_PTP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_FR_RN_PTP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x8580000000d8ll;
    __bdk_csr_fatal("TIM_FR_RN_PTP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_FR_RN_PTP bdk_tim_fr_rn_ptp_t
#define bustype_BDK_TIM_FR_RN_PTP BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_FR_RN_PTP "TIM_FR_RN_PTP"
#define device_bar_BDK_TIM_FR_RN_PTP 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_FR_RN_PTP 0
#define arguments_BDK_TIM_FR_RN_PTP -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_fr_rn_cycles
 *
 * TIM Ring Free Running Cycle Count Register
 * This register is a read-only copy of TIM_AF_FR_RN_CYCLES.
 */
union bdk_tim_lf_fr_rn_cycles
{
    uint64_t u;
    struct bdk_tim_lf_fr_rn_cycles_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_CYCLES[COUNT]. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_CYCLES[COUNT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_fr_rn_cycles_s cn; */
};
typedef union bdk_tim_lf_fr_rn_cycles bdk_tim_lf_fr_rn_cycles_t;

#define BDK_TIM_LF_FR_RN_CYCLES BDK_TIM_LF_FR_RN_CYCLES_FUNC()
static inline uint64_t BDK_TIM_LF_FR_RN_CYCLES_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_FR_RN_CYCLES_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900010ll;
    __bdk_csr_fatal("TIM_LF_FR_RN_CYCLES", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_FR_RN_CYCLES bdk_tim_lf_fr_rn_cycles_t
#define bustype_BDK_TIM_LF_FR_RN_CYCLES BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_FR_RN_CYCLES "TIM_LF_FR_RN_CYCLES"
#define device_bar_BDK_TIM_LF_FR_RN_CYCLES 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_FR_RN_CYCLES 0
#define arguments_BDK_TIM_LF_FR_RN_CYCLES -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_fr_rn_gpios
 *
 * TIM Ring Free Running GPIO Count Register
 * This register is a read-only copy of TIM_AF_FR_RN_GPIOS.
 */
union bdk_tim_lf_fr_rn_gpios
{
    uint64_t u;
    struct bdk_tim_lf_fr_rn_gpios_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_GPIOS[COUNT]. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_GPIOS[COUNT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_fr_rn_gpios_s cn; */
};
typedef union bdk_tim_lf_fr_rn_gpios bdk_tim_lf_fr_rn_gpios_t;

#define BDK_TIM_LF_FR_RN_GPIOS BDK_TIM_LF_FR_RN_GPIOS_FUNC()
static inline uint64_t BDK_TIM_LF_FR_RN_GPIOS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_FR_RN_GPIOS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900020ll;
    __bdk_csr_fatal("TIM_LF_FR_RN_GPIOS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_FR_RN_GPIOS bdk_tim_lf_fr_rn_gpios_t
#define bustype_BDK_TIM_LF_FR_RN_GPIOS BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_FR_RN_GPIOS "TIM_LF_FR_RN_GPIOS"
#define device_bar_BDK_TIM_LF_FR_RN_GPIOS 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_FR_RN_GPIOS 0
#define arguments_BDK_TIM_LF_FR_RN_GPIOS -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_fr_rn_gti
 *
 * TIM Ring Free Running System Clock Count Register
 * This register is a read-only copy of TIM_AF_FR_RN_GTI.
 */
union bdk_tim_lf_fr_rn_gti
{
    uint64_t u;
    struct bdk_tim_lf_fr_rn_gti_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_GTI[COUNT]. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_GTI[COUNT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_fr_rn_gti_s cn; */
};
typedef union bdk_tim_lf_fr_rn_gti bdk_tim_lf_fr_rn_gti_t;

#define BDK_TIM_LF_FR_RN_GTI BDK_TIM_LF_FR_RN_GTI_FUNC()
static inline uint64_t BDK_TIM_LF_FR_RN_GTI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_FR_RN_GTI_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900030ll;
    __bdk_csr_fatal("TIM_LF_FR_RN_GTI", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_FR_RN_GTI bdk_tim_lf_fr_rn_gti_t
#define bustype_BDK_TIM_LF_FR_RN_GTI BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_FR_RN_GTI "TIM_LF_FR_RN_GTI"
#define device_bar_BDK_TIM_LF_FR_RN_GTI 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_FR_RN_GTI 0
#define arguments_BDK_TIM_LF_FR_RN_GTI -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_fr_rn_ptp
 *
 * TIM Ring Free Running PTP Count Register
 * This register is a read-only copy of TIM_AF_FR_RN_PTP.
 */
union bdk_tim_lf_fr_rn_ptp
{
    uint64_t u;
    struct bdk_tim_lf_fr_rn_ptp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_PTP[COUNT]. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_PTP[COUNT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_fr_rn_ptp_s cn; */
};
typedef union bdk_tim_lf_fr_rn_ptp bdk_tim_lf_fr_rn_ptp_t;

#define BDK_TIM_LF_FR_RN_PTP BDK_TIM_LF_FR_RN_PTP_FUNC()
static inline uint64_t BDK_TIM_LF_FR_RN_PTP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_FR_RN_PTP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900040ll;
    __bdk_csr_fatal("TIM_LF_FR_RN_PTP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_FR_RN_PTP bdk_tim_lf_fr_rn_ptp_t
#define bustype_BDK_TIM_LF_FR_RN_PTP BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_FR_RN_PTP "TIM_LF_FR_RN_PTP"
#define device_bar_BDK_TIM_LF_FR_RN_PTP 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_FR_RN_PTP 0
#define arguments_BDK_TIM_LF_FR_RN_PTP -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_fr_rn_tenns
 *
 * TIM Ring Free Running 10ns Clock Count Register
 * This register is a read-only copy of TIM_AF_FR_RN_TENNS.
 */
union bdk_tim_lf_fr_rn_tenns
{
    uint64_t u;
    struct bdk_tim_lf_fr_rn_tenns_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_TENNS[COUNT]. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_AF_FR_RN_TENNS[COUNT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_fr_rn_tenns_s cn; */
};
typedef union bdk_tim_lf_fr_rn_tenns bdk_tim_lf_fr_rn_tenns_t;

#define BDK_TIM_LF_FR_RN_TENNS BDK_TIM_LF_FR_RN_TENNS_FUNC()
static inline uint64_t BDK_TIM_LF_FR_RN_TENNS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_FR_RN_TENNS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900050ll;
    __bdk_csr_fatal("TIM_LF_FR_RN_TENNS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_FR_RN_TENNS bdk_tim_lf_fr_rn_tenns_t
#define bustype_BDK_TIM_LF_FR_RN_TENNS BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_FR_RN_TENNS "TIM_LF_FR_RN_TENNS"
#define device_bar_BDK_TIM_LF_FR_RN_TENNS 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_FR_RN_TENNS 0
#define arguments_BDK_TIM_LF_FR_RN_TENNS -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_nrsperr_int
 *
 * TIM LF NCB Response Error Interrupt Register
 */
union bdk_tim_lf_nrsperr_int
{
    uint64_t u;
    struct bdk_tim_lf_nrsperr_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t wqe_psn               : 1;  /**< [  4:  4](R/W1C/H) WQE poison flag. Set when a poisoned WQE response or next chunk pointer was detected. */
        uint64_t la_psn                : 1;  /**< [  3:  3](R/W1C/H) Load and atomic poison flag. Set when a poisoned non-WQE load or atomic response was detected. */
        uint64_t wqe_flt               : 1;  /**< [  2:  2](R/W1C/H) WQE fault flag. Set when a faulted WQE response or next chunk pointer was detected. */
        uint64_t la_flt                : 1;  /**< [  1:  1](R/W1C/H) Load and atomic fault flag. Set when a faulted non-WQE load or
                                                                 atomic response was detected, e.g. a SMMU page fault to a
                                                                 bad IOVA request by this ring. */
        uint64_t stdn_flt              : 1;  /**< [  0:  0](R/W1C/H) Store fault flag. Set when a faulted store was detected, e.g. a SMMU
                                                                 page fault to a bad IOVA request by this ring. */
#else /* Word 0 - Little Endian */
        uint64_t stdn_flt              : 1;  /**< [  0:  0](R/W1C/H) Store fault flag. Set when a faulted store was detected, e.g. a SMMU
                                                                 page fault to a bad IOVA request by this ring. */
        uint64_t la_flt                : 1;  /**< [  1:  1](R/W1C/H) Load and atomic fault flag. Set when a faulted non-WQE load or
                                                                 atomic response was detected, e.g. a SMMU page fault to a
                                                                 bad IOVA request by this ring. */
        uint64_t wqe_flt               : 1;  /**< [  2:  2](R/W1C/H) WQE fault flag. Set when a faulted WQE response or next chunk pointer was detected. */
        uint64_t la_psn                : 1;  /**< [  3:  3](R/W1C/H) Load and atomic poison flag. Set when a poisoned non-WQE load or atomic response was detected. */
        uint64_t wqe_psn               : 1;  /**< [  4:  4](R/W1C/H) WQE poison flag. Set when a poisoned WQE response or next chunk pointer was detected. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_nrsperr_int_s cn; */
};
typedef union bdk_tim_lf_nrsperr_int bdk_tim_lf_nrsperr_int_t;

#define BDK_TIM_LF_NRSPERR_INT BDK_TIM_LF_NRSPERR_INT_FUNC()
static inline uint64_t BDK_TIM_LF_NRSPERR_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_NRSPERR_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900200ll;
    __bdk_csr_fatal("TIM_LF_NRSPERR_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_NRSPERR_INT bdk_tim_lf_nrsperr_int_t
#define bustype_BDK_TIM_LF_NRSPERR_INT BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_NRSPERR_INT "TIM_LF_NRSPERR_INT"
#define device_bar_BDK_TIM_LF_NRSPERR_INT 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_NRSPERR_INT 0
#define arguments_BDK_TIM_LF_NRSPERR_INT -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_nrsperr_int_ena_w1c
 *
 * TIM LF NCB Response Error Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_tim_lf_nrsperr_int_ena_w1c
{
    uint64_t u;
    struct bdk_tim_lf_nrsperr_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t wqe_psn               : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[WQE_PSN]. */
        uint64_t la_psn                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[LA_PSN]. */
        uint64_t wqe_flt               : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[WQE_FLT]. */
        uint64_t la_flt                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[LA_FLT]. */
        uint64_t stdn_flt              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[STDN_FLT]. */
#else /* Word 0 - Little Endian */
        uint64_t stdn_flt              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[STDN_FLT]. */
        uint64_t la_flt                : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[LA_FLT]. */
        uint64_t wqe_flt               : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[WQE_FLT]. */
        uint64_t la_psn                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[LA_PSN]. */
        uint64_t wqe_psn               : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for TIM_LF_NRSPERR_INT[WQE_PSN]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_nrsperr_int_ena_w1c_s cn; */
};
typedef union bdk_tim_lf_nrsperr_int_ena_w1c bdk_tim_lf_nrsperr_int_ena_w1c_t;

#define BDK_TIM_LF_NRSPERR_INT_ENA_W1C BDK_TIM_LF_NRSPERR_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_TIM_LF_NRSPERR_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_NRSPERR_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900218ll;
    __bdk_csr_fatal("TIM_LF_NRSPERR_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_NRSPERR_INT_ENA_W1C bdk_tim_lf_nrsperr_int_ena_w1c_t
#define bustype_BDK_TIM_LF_NRSPERR_INT_ENA_W1C BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_NRSPERR_INT_ENA_W1C "TIM_LF_NRSPERR_INT_ENA_W1C"
#define device_bar_BDK_TIM_LF_NRSPERR_INT_ENA_W1C 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_NRSPERR_INT_ENA_W1C 0
#define arguments_BDK_TIM_LF_NRSPERR_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_nrsperr_int_ena_w1s
 *
 * TIM NCB Response Error Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_tim_lf_nrsperr_int_ena_w1s
{
    uint64_t u;
    struct bdk_tim_lf_nrsperr_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t wqe_psn               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[WQE_PSN]. */
        uint64_t la_psn                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[LA_PSN]. */
        uint64_t wqe_flt               : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[WQE_FLT]. */
        uint64_t la_flt                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[LA_FLT]. */
        uint64_t stdn_flt              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[STDN_FLT]. */
#else /* Word 0 - Little Endian */
        uint64_t stdn_flt              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[STDN_FLT]. */
        uint64_t la_flt                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[LA_FLT]. */
        uint64_t wqe_flt               : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[WQE_FLT]. */
        uint64_t la_psn                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[LA_PSN]. */
        uint64_t wqe_psn               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for TIM_LF_NRSPERR_INT[WQE_PSN]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_nrsperr_int_ena_w1s_s cn; */
};
typedef union bdk_tim_lf_nrsperr_int_ena_w1s bdk_tim_lf_nrsperr_int_ena_w1s_t;

#define BDK_TIM_LF_NRSPERR_INT_ENA_W1S BDK_TIM_LF_NRSPERR_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_TIM_LF_NRSPERR_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_NRSPERR_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900210ll;
    __bdk_csr_fatal("TIM_LF_NRSPERR_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_NRSPERR_INT_ENA_W1S bdk_tim_lf_nrsperr_int_ena_w1s_t
#define bustype_BDK_TIM_LF_NRSPERR_INT_ENA_W1S BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_NRSPERR_INT_ENA_W1S "TIM_LF_NRSPERR_INT_ENA_W1S"
#define device_bar_BDK_TIM_LF_NRSPERR_INT_ENA_W1S 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_NRSPERR_INT_ENA_W1S 0
#define arguments_BDK_TIM_LF_NRSPERR_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_nrsperr_int_w1s
 *
 * TIM LF NCB Response Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_tim_lf_nrsperr_int_w1s
{
    uint64_t u;
    struct bdk_tim_lf_nrsperr_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t wqe_psn               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[WQE_PSN]. */
        uint64_t la_psn                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[LA_PSN]. */
        uint64_t wqe_flt               : 1;  /**< [  2:  2](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[WQE_FLT]. */
        uint64_t la_flt                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[LA_FLT]. */
        uint64_t stdn_flt              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[STDN_FLT]. */
#else /* Word 0 - Little Endian */
        uint64_t stdn_flt              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[STDN_FLT]. */
        uint64_t la_flt                : 1;  /**< [  1:  1](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[LA_FLT]. */
        uint64_t wqe_flt               : 1;  /**< [  2:  2](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[WQE_FLT]. */
        uint64_t la_psn                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[LA_PSN]. */
        uint64_t wqe_psn               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets TIM_LF_NRSPERR_INT[WQE_PSN]. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_nrsperr_int_w1s_s cn; */
};
typedef union bdk_tim_lf_nrsperr_int_w1s bdk_tim_lf_nrsperr_int_w1s_t;

#define BDK_TIM_LF_NRSPERR_INT_W1S BDK_TIM_LF_NRSPERR_INT_W1S_FUNC()
static inline uint64_t BDK_TIM_LF_NRSPERR_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_NRSPERR_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900208ll;
    __bdk_csr_fatal("TIM_LF_NRSPERR_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_NRSPERR_INT_W1S bdk_tim_lf_nrsperr_int_w1s_t
#define bustype_BDK_TIM_LF_NRSPERR_INT_W1S BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_NRSPERR_INT_W1S "TIM_LF_NRSPERR_INT_W1S"
#define device_bar_BDK_TIM_LF_NRSPERR_INT_W1S 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_NRSPERR_INT_W1S 0
#define arguments_BDK_TIM_LF_NRSPERR_INT_W1S -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ras_int
 *
 * TIM LF NCB Response Poison Interrupt Register
 */
union bdk_tim_lf_ras_int
{
    uint64_t u;
    struct bdk_tim_lf_ras_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wqe_psn               : 1;  /**< [  1:  1](R/W1C/H) WQE poison flag. Set when a poisoned WQE response was detected. */
        uint64_t la_psn                : 1;  /**< [  0:  0](R/W1C/H) Load and atomic poison flag. Set when a poisoned non-WQE load or atomic response was detected. */
#else /* Word 0 - Little Endian */
        uint64_t la_psn                : 1;  /**< [  0:  0](R/W1C/H) Load and atomic poison flag. Set when a poisoned non-WQE load or atomic response was detected. */
        uint64_t wqe_psn               : 1;  /**< [  1:  1](R/W1C/H) WQE poison flag. Set when a poisoned WQE response was detected. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ras_int_s cn; */
};
typedef union bdk_tim_lf_ras_int bdk_tim_lf_ras_int_t;

#define BDK_TIM_LF_RAS_INT BDK_TIM_LF_RAS_INT_FUNC()
static inline uint64_t BDK_TIM_LF_RAS_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RAS_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900300ll;
    __bdk_csr_fatal("TIM_LF_RAS_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RAS_INT bdk_tim_lf_ras_int_t
#define bustype_BDK_TIM_LF_RAS_INT BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RAS_INT "TIM_LF_RAS_INT"
#define device_bar_BDK_TIM_LF_RAS_INT 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RAS_INT 0
#define arguments_BDK_TIM_LF_RAS_INT -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ras_int_ena_w1c
 *
 * TIM LF NCB Response Poison Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_tim_lf_ras_int_ena_w1c
{
    uint64_t u;
    struct bdk_tim_lf_ras_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wqe_psn               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for TIM_LF_RAS_INT[WQE_PSN]. */
        uint64_t la_psn                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_LF_RAS_INT[LA_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t la_psn                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_LF_RAS_INT[LA_PSN]. */
        uint64_t wqe_psn               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for TIM_LF_RAS_INT[WQE_PSN]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ras_int_ena_w1c_s cn; */
};
typedef union bdk_tim_lf_ras_int_ena_w1c bdk_tim_lf_ras_int_ena_w1c_t;

#define BDK_TIM_LF_RAS_INT_ENA_W1C BDK_TIM_LF_RAS_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_TIM_LF_RAS_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RAS_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900318ll;
    __bdk_csr_fatal("TIM_LF_RAS_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RAS_INT_ENA_W1C bdk_tim_lf_ras_int_ena_w1c_t
#define bustype_BDK_TIM_LF_RAS_INT_ENA_W1C BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RAS_INT_ENA_W1C "TIM_LF_RAS_INT_ENA_W1C"
#define device_bar_BDK_TIM_LF_RAS_INT_ENA_W1C 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RAS_INT_ENA_W1C 0
#define arguments_BDK_TIM_LF_RAS_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ras_int_ena_w1s
 *
 * TIM NCB Response Poison Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_tim_lf_ras_int_ena_w1s
{
    uint64_t u;
    struct bdk_tim_lf_ras_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wqe_psn               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for TIM_LF_RAS_INT[WQE_PSN]. */
        uint64_t la_psn                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_LF_RAS_INT[LA_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t la_psn                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_LF_RAS_INT[LA_PSN]. */
        uint64_t wqe_psn               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for TIM_LF_RAS_INT[WQE_PSN]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ras_int_ena_w1s_s cn; */
};
typedef union bdk_tim_lf_ras_int_ena_w1s bdk_tim_lf_ras_int_ena_w1s_t;

#define BDK_TIM_LF_RAS_INT_ENA_W1S BDK_TIM_LF_RAS_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_TIM_LF_RAS_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RAS_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900310ll;
    __bdk_csr_fatal("TIM_LF_RAS_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RAS_INT_ENA_W1S bdk_tim_lf_ras_int_ena_w1s_t
#define bustype_BDK_TIM_LF_RAS_INT_ENA_W1S BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RAS_INT_ENA_W1S "TIM_LF_RAS_INT_ENA_W1S"
#define device_bar_BDK_TIM_LF_RAS_INT_ENA_W1S 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RAS_INT_ENA_W1S 0
#define arguments_BDK_TIM_LF_RAS_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ras_int_w1s
 *
 * TIM LF NCB Response Poison Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_tim_lf_ras_int_w1s
{
    uint64_t u;
    struct bdk_tim_lf_ras_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t wqe_psn               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets TIM_LF_RAS_INT[WQE_PSN]. */
        uint64_t la_psn                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_LF_RAS_INT[LA_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t la_psn                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_LF_RAS_INT[LA_PSN]. */
        uint64_t wqe_psn               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets TIM_LF_RAS_INT[WQE_PSN]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ras_int_w1s_s cn; */
};
typedef union bdk_tim_lf_ras_int_w1s bdk_tim_lf_ras_int_w1s_t;

#define BDK_TIM_LF_RAS_INT_W1S BDK_TIM_LF_RAS_INT_W1S_FUNC()
static inline uint64_t BDK_TIM_LF_RAS_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RAS_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900308ll;
    __bdk_csr_fatal("TIM_LF_RAS_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RAS_INT_W1S bdk_tim_lf_ras_int_w1s_t
#define bustype_BDK_TIM_LF_RAS_INT_W1S BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RAS_INT_W1S "TIM_LF_RAS_INT_W1S"
#define device_bar_BDK_TIM_LF_RAS_INT_W1S 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RAS_INT_W1S 0
#define arguments_BDK_TIM_LF_RAS_INT_W1S -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ring_aura
 *
 * TIM Ring Aura Registers
 */
union bdk_tim_lf_ring_aura
{
    uint64_t u;
    struct bdk_tim_lf_ring_aura_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t aura                  : 20; /**< [ 19:  0](R/W) Guest-aura number used to free and return chunks to. Bits \<15:12\> must be zero. */
#else /* Word 0 - Little Endian */
        uint64_t aura                  : 20; /**< [ 19:  0](R/W) Guest-aura number used to free and return chunks to. Bits \<15:12\> must be zero. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ring_aura_s cn; */
};
typedef union bdk_tim_lf_ring_aura bdk_tim_lf_ring_aura_t;

#define BDK_TIM_LF_RING_AURA BDK_TIM_LF_RING_AURA_FUNC()
static inline uint64_t BDK_TIM_LF_RING_AURA_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RING_AURA_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900000ll;
    __bdk_csr_fatal("TIM_LF_RING_AURA", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RING_AURA bdk_tim_lf_ring_aura_t
#define bustype_BDK_TIM_LF_RING_AURA BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RING_AURA "TIM_LF_RING_AURA"
#define device_bar_BDK_TIM_LF_RING_AURA 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RING_AURA 0
#define arguments_BDK_TIM_LF_RING_AURA -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ring_base
 *
 * TIM Ring Base Registers
 */
union bdk_tim_lf_ring_base
{
    uint64_t u;
    struct bdk_tim_lf_ring_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t base                  : 48; /**< [ 52:  5](R/W) IOVA pointer to bucket 0. */
        uint64_t reserved_0_4          : 5;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_4          : 5;
        uint64_t base                  : 48; /**< [ 52:  5](R/W) IOVA pointer to bucket 0. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ring_base_s cn; */
};
typedef union bdk_tim_lf_ring_base bdk_tim_lf_ring_base_t;

#define BDK_TIM_LF_RING_BASE BDK_TIM_LF_RING_BASE_FUNC()
static inline uint64_t BDK_TIM_LF_RING_BASE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RING_BASE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900130ll;
    __bdk_csr_fatal("TIM_LF_RING_BASE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RING_BASE bdk_tim_lf_ring_base_t
#define bustype_BDK_TIM_LF_RING_BASE BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RING_BASE "TIM_LF_RING_BASE"
#define device_bar_BDK_TIM_LF_RING_BASE 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RING_BASE 0
#define arguments_BDK_TIM_LF_RING_BASE -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ring_ctl0
 *
 * TIM Ring Control 0 Registers
 * This register is a read-only copy of TIM_AF_RING()_CTL0.
 */
union bdk_tim_lf_ring_ctl0
{
    uint64_t u;
    struct bdk_tim_lf_ring_ctl0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t expire_offset         : 32; /**< [ 63: 32](RO/H) Read-only TIM_AF_RING(0..255)_CTL0[EXPIRE_OFFSET]. */
        uint64_t interval              : 32; /**< [ 31:  0](RO) Read-only TIM_AF_RING(0..255)_CTL0[INTERVAL]. */
#else /* Word 0 - Little Endian */
        uint64_t interval              : 32; /**< [ 31:  0](RO) Read-only TIM_AF_RING(0..255)_CTL0[INTERVAL]. */
        uint64_t expire_offset         : 32; /**< [ 63: 32](RO/H) Read-only TIM_AF_RING(0..255)_CTL0[EXPIRE_OFFSET]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ring_ctl0_s cn; */
};
typedef union bdk_tim_lf_ring_ctl0 bdk_tim_lf_ring_ctl0_t;

#define BDK_TIM_LF_RING_CTL0 BDK_TIM_LF_RING_CTL0_FUNC()
static inline uint64_t BDK_TIM_LF_RING_CTL0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RING_CTL0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900100ll;
    __bdk_csr_fatal("TIM_LF_RING_CTL0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RING_CTL0 bdk_tim_lf_ring_ctl0_t
#define bustype_BDK_TIM_LF_RING_CTL0 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RING_CTL0 "TIM_LF_RING_CTL0"
#define device_bar_BDK_TIM_LF_RING_CTL0 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RING_CTL0 0
#define arguments_BDK_TIM_LF_RING_CTL0 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ring_ctl1
 *
 * TIM Ring Control 1 Registers
 * This register is a read-only copy of TIM_AF_RING()_CTL1.
 */
union bdk_tim_lf_ring_ctl1
{
    uint64_t u;
    struct bdk_tim_lf_ring_ctl1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_54_63        : 10;
        uint64_t be                    : 1;  /**< [ 53: 53](RO) Read-only TIM_AF_RING(0..255)_CTL1[BE]. */
        uint64_t clk_src               : 2;  /**< [ 52: 51](RO) Read-only TIM_AF_RING(0..255)_CTL1[CLK_SRC]. */
        uint64_t rcf_busy              : 1;  /**< [ 50: 50](RO/H) Read-only TIM_AF_RING(0..255)_CTL1[RCF_BUSY]. */
        uint64_t reserved_49           : 1;
        uint64_t lock_en               : 1;  /**< [ 48: 48](RO) Read-only TIM_AF_RING(0..255)_CTL1[LOCK_EN]. */
        uint64_t ena                   : 1;  /**< [ 47: 47](RO/H) Read-only TIM_AF_RING(0..255)_CTL1[ENA]. */
        uint64_t reserved_46           : 1;
        uint64_t ena_prd               : 1;  /**< [ 45: 45](RO) Read-only TIM_AF_RING(0..255)_CTL1[ENA_PRD]. */
        uint64_t ena_ldwb              : 1;  /**< [ 44: 44](RO) Read-only TIM_AF_RING(0..255)_CTL1[ENA_LDWB]. */
        uint64_t ena_dfb               : 1;  /**< [ 43: 43](RO) Read-only TIM_AF_RING(0..255)_CTL1[ENA_DFB]. */
        uint64_t reserved_40_42        : 3;
        uint64_t bucket                : 20; /**< [ 39: 20](RO/H) Read-only TIM_AF_RING(0..255)_CTL1[BUCKET]. */
        uint64_t bsize                 : 20; /**< [ 19:  0](RO) Read-only TIM_AF_RING(0..255)_CTL1[BSIZE]. */
#else /* Word 0 - Little Endian */
        uint64_t bsize                 : 20; /**< [ 19:  0](RO) Read-only TIM_AF_RING(0..255)_CTL1[BSIZE]. */
        uint64_t bucket                : 20; /**< [ 39: 20](RO/H) Read-only TIM_AF_RING(0..255)_CTL1[BUCKET]. */
        uint64_t reserved_40_42        : 3;
        uint64_t ena_dfb               : 1;  /**< [ 43: 43](RO) Read-only TIM_AF_RING(0..255)_CTL1[ENA_DFB]. */
        uint64_t ena_ldwb              : 1;  /**< [ 44: 44](RO) Read-only TIM_AF_RING(0..255)_CTL1[ENA_LDWB]. */
        uint64_t ena_prd               : 1;  /**< [ 45: 45](RO) Read-only TIM_AF_RING(0..255)_CTL1[ENA_PRD]. */
        uint64_t reserved_46           : 1;
        uint64_t ena                   : 1;  /**< [ 47: 47](RO/H) Read-only TIM_AF_RING(0..255)_CTL1[ENA]. */
        uint64_t lock_en               : 1;  /**< [ 48: 48](RO) Read-only TIM_AF_RING(0..255)_CTL1[LOCK_EN]. */
        uint64_t reserved_49           : 1;
        uint64_t rcf_busy              : 1;  /**< [ 50: 50](RO/H) Read-only TIM_AF_RING(0..255)_CTL1[RCF_BUSY]. */
        uint64_t clk_src               : 2;  /**< [ 52: 51](RO) Read-only TIM_AF_RING(0..255)_CTL1[CLK_SRC]. */
        uint64_t be                    : 1;  /**< [ 53: 53](RO) Read-only TIM_AF_RING(0..255)_CTL1[BE]. */
        uint64_t reserved_54_63        : 10;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ring_ctl1_s cn; */
};
typedef union bdk_tim_lf_ring_ctl1 bdk_tim_lf_ring_ctl1_t;

#define BDK_TIM_LF_RING_CTL1 BDK_TIM_LF_RING_CTL1_FUNC()
static inline uint64_t BDK_TIM_LF_RING_CTL1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RING_CTL1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900110ll;
    __bdk_csr_fatal("TIM_LF_RING_CTL1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RING_CTL1 bdk_tim_lf_ring_ctl1_t
#define bustype_BDK_TIM_LF_RING_CTL1 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RING_CTL1 "TIM_LF_RING_CTL1"
#define device_bar_BDK_TIM_LF_RING_CTL1 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RING_CTL1 0
#define arguments_BDK_TIM_LF_RING_CTL1 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ring_ctl2
 *
 * TIM Ring Control 2 Registers
 * This register is a read-only copy of TIM_AF_RING()_CTL2.
 */
union bdk_tim_lf_ring_ctl2
{
    uint64_t u;
    struct bdk_tim_lf_ring_ctl2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t csize                 : 13; /**< [ 52: 40](RO) Read-only TIM_AF_RING(0..255)_CTL2[CSIZE]. */
        uint64_t reserved_0_39         : 40;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_39         : 40;
        uint64_t csize                 : 13; /**< [ 52: 40](RO) Read-only TIM_AF_RING(0..255)_CTL2[CSIZE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ring_ctl2_s cn; */
};
typedef union bdk_tim_lf_ring_ctl2 bdk_tim_lf_ring_ctl2_t;

#define BDK_TIM_LF_RING_CTL2 BDK_TIM_LF_RING_CTL2_FUNC()
static inline uint64_t BDK_TIM_LF_RING_CTL2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RING_CTL2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900120ll;
    __bdk_csr_fatal("TIM_LF_RING_CTL2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RING_CTL2 bdk_tim_lf_ring_ctl2_t
#define bustype_BDK_TIM_LF_RING_CTL2 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RING_CTL2 "TIM_LF_RING_CTL2"
#define device_bar_BDK_TIM_LF_RING_CTL2 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RING_CTL2 0
#define arguments_BDK_TIM_LF_RING_CTL2 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) tim_lf_ring_rel
 *
 * TIM Ring Relative Position Register
 * Current positions and status of the TIM walker in both time and ring position,
 * for easy synchronization with software.
 *
 * Internal:
 * For VM-safety this register contains only read-only fields.
 */
union bdk_tim_lf_ring_rel
{
    uint64_t u;
    struct bdk_tim_lf_ring_rel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cur_bucket            : 20; /**< [ 63: 44](RO/H) Current bucket. Indicates the ring's current bucket. See TIM_AF_RING()_CTL1[BUCKET]. */
        uint64_t late_count_msbs       : 1;  /**< [ 43: 43](RO/H) Set when TIM_AF_RING()_LATE[COUNT]\<19:11\> != 0x0. Software should read
                                                                 TIM_AF_RING()_LATE[COUNT] to find how many buckets a ring is late. */
        uint64_t late_count            : 11; /**< [ 42: 32](RO/H) Identical to TIM_AF_RING()_LATE[COUNT]\<10:0\>. If [LATE_COUNT_MSBS] is zero,
                                                                 it indicates how many bucket are late to be scheduled per ring. See the HRM body
                                                                 text with regards to how software should consider TIM_AF_RING()_LATE[COUNT] when
                                                                 inserting an entry. */
        uint64_t timercount            : 32; /**< [ 31:  0](RO/H) Timer count indicates how many timer ticks are left until the interval
                                                                 expiration, calculated as TIM_AF_RING()_CTL0[EXPIRE_OFFSET] minus current time
                                                                 (TIM_FR_RN_TENNS, TIM_FR_RN_GPIOS, TIM_FR_RN_GTI, or TIM_FR_RN_PTP).

                                                                 Once TIM_AF_RING()_CTL1[ENA] = 1, [TIMERCOUNT] will be observed to count down timer
                                                                 ticks. When [TIMERCOUNT] reaches 0x0, the ring's interval expired and the
                                                                 hardware forces a bucket traversal (and increments [LATE_COUNT]).

                                                                 Typical initialization value should be interval/constant; Cavium recommends that
                                                                 the constant be unique per ring. This creates an offset between the rings.
                                                                 [TIMERCOUNT] becomes and remains unpredictable whenever TIM_AF_RING()_CTL1[ENA] = 0
                                                                 or TIM_AF_RING()_CTL1[CLK_SRC] changes, until TIM_AF_RING()_CTL0 is updated. */
#else /* Word 0 - Little Endian */
        uint64_t timercount            : 32; /**< [ 31:  0](RO/H) Timer count indicates how many timer ticks are left until the interval
                                                                 expiration, calculated as TIM_AF_RING()_CTL0[EXPIRE_OFFSET] minus current time
                                                                 (TIM_FR_RN_TENNS, TIM_FR_RN_GPIOS, TIM_FR_RN_GTI, or TIM_FR_RN_PTP).

                                                                 Once TIM_AF_RING()_CTL1[ENA] = 1, [TIMERCOUNT] will be observed to count down timer
                                                                 ticks. When [TIMERCOUNT] reaches 0x0, the ring's interval expired and the
                                                                 hardware forces a bucket traversal (and increments [LATE_COUNT]).

                                                                 Typical initialization value should be interval/constant; Cavium recommends that
                                                                 the constant be unique per ring. This creates an offset between the rings.
                                                                 [TIMERCOUNT] becomes and remains unpredictable whenever TIM_AF_RING()_CTL1[ENA] = 0
                                                                 or TIM_AF_RING()_CTL1[CLK_SRC] changes, until TIM_AF_RING()_CTL0 is updated. */
        uint64_t late_count            : 11; /**< [ 42: 32](RO/H) Identical to TIM_AF_RING()_LATE[COUNT]\<10:0\>. If [LATE_COUNT_MSBS] is zero,
                                                                 it indicates how many bucket are late to be scheduled per ring. See the HRM body
                                                                 text with regards to how software should consider TIM_AF_RING()_LATE[COUNT] when
                                                                 inserting an entry. */
        uint64_t late_count_msbs       : 1;  /**< [ 43: 43](RO/H) Set when TIM_AF_RING()_LATE[COUNT]\<19:11\> != 0x0. Software should read
                                                                 TIM_AF_RING()_LATE[COUNT] to find how many buckets a ring is late. */
        uint64_t cur_bucket            : 20; /**< [ 63: 44](RO/H) Current bucket. Indicates the ring's current bucket. See TIM_AF_RING()_CTL1[BUCKET]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_lf_ring_rel_s cn9; */
    /* struct bdk_tim_lf_ring_rel_s cn96xxp1; */
    struct bdk_tim_lf_ring_rel_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cur_bucket            : 20; /**< [ 63: 44](RO/H) Current bucket. Indicates the ring's current bucket. See TIM_AF_RING()_CTL1[BUCKET]. */
        uint64_t late_count_msbs       : 1;  /**< [ 43: 43](RO/H) Set when TIM_AF_RING()_LATE[COUNT]\<19:11\> != 0x0. Software should read
                                                                 TIM_AF_RING()_LATE[COUNT] to find how many buckets a ring is late. */
        uint64_t late_count            : 11; /**< [ 42: 32](RO/H) Identical to TIM_AF_RING()_LATE[COUNT]\<10:0\>. If [LATE_COUNT_MSBS] is zero,
                                                                 it indicates how many bucket are late to be scheduled per ring. See the HRM body
                                                                 text with regards to how software should consider TIM_AF_RING()_LATE[COUNT] when
                                                                 inserting an entry. */
        uint64_t timercount            : 32; /**< [ 31:  0](RO/H) Timer count indicates how many timer ticks are left until the interval
                                                                 expiration, calculated as TIM_AF_RING()_CTL0[EXPIRE_OFFSET] minus current time
                                                                 (TIM_FR_RN_TENNS, TIM_FR_RN_GPIOS, TIM_FR_RN_GTI, or TIM_FR_RN_PTP).

                                                                 Once TIM_AF_RING()_CTL1[ENA] = 1, [TIMERCOUNT] will be observed to count down timer
                                                                 ticks. When [TIMERCOUNT] reaches 0x0, the ring's interval expired and the
                                                                 hardware forces a bucket traversal (and increments [LATE_COUNT]).

                                                                 Typical initialization value should be interval/constant; Marvell recommends that
                                                                 the constant be unique per ring. This creates an offset between the rings.
                                                                 [TIMERCOUNT] becomes and remains unpredictable whenever TIM_AF_RING()_CTL1[ENA] = 0
                                                                 or TIM_AF_RING()_CTL1[CLK_SRC] changes, until TIM_AF_RING()_CTL0 is updated. */
#else /* Word 0 - Little Endian */
        uint64_t timercount            : 32; /**< [ 31:  0](RO/H) Timer count indicates how many timer ticks are left until the interval
                                                                 expiration, calculated as TIM_AF_RING()_CTL0[EXPIRE_OFFSET] minus current time
                                                                 (TIM_FR_RN_TENNS, TIM_FR_RN_GPIOS, TIM_FR_RN_GTI, or TIM_FR_RN_PTP).

                                                                 Once TIM_AF_RING()_CTL1[ENA] = 1, [TIMERCOUNT] will be observed to count down timer
                                                                 ticks. When [TIMERCOUNT] reaches 0x0, the ring's interval expired and the
                                                                 hardware forces a bucket traversal (and increments [LATE_COUNT]).

                                                                 Typical initialization value should be interval/constant; Marvell recommends that
                                                                 the constant be unique per ring. This creates an offset between the rings.
                                                                 [TIMERCOUNT] becomes and remains unpredictable whenever TIM_AF_RING()_CTL1[ENA] = 0
                                                                 or TIM_AF_RING()_CTL1[CLK_SRC] changes, until TIM_AF_RING()_CTL0 is updated. */
        uint64_t late_count            : 11; /**< [ 42: 32](RO/H) Identical to TIM_AF_RING()_LATE[COUNT]\<10:0\>. If [LATE_COUNT_MSBS] is zero,
                                                                 it indicates how many bucket are late to be scheduled per ring. See the HRM body
                                                                 text with regards to how software should consider TIM_AF_RING()_LATE[COUNT] when
                                                                 inserting an entry. */
        uint64_t late_count_msbs       : 1;  /**< [ 43: 43](RO/H) Set when TIM_AF_RING()_LATE[COUNT]\<19:11\> != 0x0. Software should read
                                                                 TIM_AF_RING()_LATE[COUNT] to find how many buckets a ring is late. */
        uint64_t cur_bucket            : 20; /**< [ 63: 44](RO/H) Current bucket. Indicates the ring's current bucket. See TIM_AF_RING()_CTL1[BUCKET]. */
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_tim_lf_ring_rel_cn96xxp3 cn98xx; */
    /* struct bdk_tim_lf_ring_rel_cn96xxp3 cnf95xx; */
    /* struct bdk_tim_lf_ring_rel_cn96xxp3 loki; */
};
typedef union bdk_tim_lf_ring_rel bdk_tim_lf_ring_rel_t;

#define BDK_TIM_LF_RING_REL BDK_TIM_LF_RING_REL_FUNC()
static inline uint64_t BDK_TIM_LF_RING_REL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_LF_RING_REL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200900400ll;
    __bdk_csr_fatal("TIM_LF_RING_REL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_LF_RING_REL bdk_tim_lf_ring_rel_t
#define bustype_BDK_TIM_LF_RING_REL BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_TIM_LF_RING_REL "TIM_LF_RING_REL"
#define device_bar_BDK_TIM_LF_RING_REL 0x2 /* RVU_BAR2 */
#define busnum_BDK_TIM_LF_RING_REL 0
#define arguments_BDK_TIM_LF_RING_REL -1,-1,-1,-1

/**
 * Register (NCB) tim_nxt_min_cycles_expire
 *
 * INTERNAL: TIM Next Minimum Cycles Expiration Time Register
 */
union bdk_tim_nxt_min_cycles_expire
{
    uint64_t u;
    struct bdk_tim_nxt_min_cycles_expire_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_FR_RN_CYCLES must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_FR_RN_CYCLES must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_nxt_min_cycles_expire_s cn; */
};
typedef union bdk_tim_nxt_min_cycles_expire bdk_tim_nxt_min_cycles_expire_t;

#define BDK_TIM_NXT_MIN_CYCLES_EXPIRE BDK_TIM_NXT_MIN_CYCLES_EXPIRE_FUNC()
static inline uint64_t BDK_TIM_NXT_MIN_CYCLES_EXPIRE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_NXT_MIN_CYCLES_EXPIRE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000001100ll;
    __bdk_csr_fatal("TIM_NXT_MIN_CYCLES_EXPIRE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_NXT_MIN_CYCLES_EXPIRE bdk_tim_nxt_min_cycles_expire_t
#define bustype_BDK_TIM_NXT_MIN_CYCLES_EXPIRE BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_NXT_MIN_CYCLES_EXPIRE "TIM_NXT_MIN_CYCLES_EXPIRE"
#define device_bar_BDK_TIM_NXT_MIN_CYCLES_EXPIRE 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_NXT_MIN_CYCLES_EXPIRE 0
#define arguments_BDK_TIM_NXT_MIN_CYCLES_EXPIRE -1,-1,-1,-1

/**
 * Register (NCB) tim_nxt_min_gpios_expire
 *
 * INTERNAL: TIM Next Minimum GPIOS Expiration Time Registers
 */
union bdk_tim_nxt_min_gpios_expire
{
    uint64_t u;
    struct bdk_tim_nxt_min_gpios_expire_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_FR_RN_GPIOS must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) Indicates the value TIM_FR_RN_GPIOS must reach before the next possible
                                                                 servicing of rings/buckets. For diagnostic use only. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_nxt_min_gpios_expire_s cn; */
};
typedef union bdk_tim_nxt_min_gpios_expire bdk_tim_nxt_min_gpios_expire_t;

#define BDK_TIM_NXT_MIN_GPIOS_EXPIRE BDK_TIM_NXT_MIN_GPIOS_EXPIRE_FUNC()
static inline uint64_t BDK_TIM_NXT_MIN_GPIOS_EXPIRE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_NXT_MIN_GPIOS_EXPIRE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000001108ll;
    __bdk_csr_fatal("TIM_NXT_MIN_GPIOS_EXPIRE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_NXT_MIN_GPIOS_EXPIRE bdk_tim_nxt_min_gpios_expire_t
#define bustype_BDK_TIM_NXT_MIN_GPIOS_EXPIRE BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_NXT_MIN_GPIOS_EXPIRE "TIM_NXT_MIN_GPIOS_EXPIRE"
#define device_bar_BDK_TIM_NXT_MIN_GPIOS_EXPIRE 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_NXT_MIN_GPIOS_EXPIRE 0
#define arguments_BDK_TIM_NXT_MIN_GPIOS_EXPIRE -1,-1,-1,-1

/**
 * Register (NCB) tim_nxt_min_gti_expire
 *
 * INTERNAL: TIM Next Minimum GTI Expire Time Registers
 */
union bdk_tim_nxt_min_gti_expire
{
    uint64_t u;
    struct bdk_tim_nxt_min_gti_expire_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) This field indicates the value TIM_FR_RN_GTI must reach
                                                                 before the next possible servicing of rings/buckets.
                                                                 For diagnostic use. */
#else /* Word 0 - Little Endian */
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) This field indicates the value TIM_FR_RN_GTI must reach
                                                                 before the next possible servicing of rings/buckets.
                                                                 For diagnostic use. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_nxt_min_gti_expire_s cn; */
};
typedef union bdk_tim_nxt_min_gti_expire bdk_tim_nxt_min_gti_expire_t;

#define BDK_TIM_NXT_MIN_GTI_EXPIRE BDK_TIM_NXT_MIN_GTI_EXPIRE_FUNC()
static inline uint64_t BDK_TIM_NXT_MIN_GTI_EXPIRE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_NXT_MIN_GTI_EXPIRE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000001110ll;
    __bdk_csr_fatal("TIM_NXT_MIN_GTI_EXPIRE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_NXT_MIN_GTI_EXPIRE bdk_tim_nxt_min_gti_expire_t
#define bustype_BDK_TIM_NXT_MIN_GTI_EXPIRE BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_NXT_MIN_GTI_EXPIRE "TIM_NXT_MIN_GTI_EXPIRE"
#define device_bar_BDK_TIM_NXT_MIN_GTI_EXPIRE 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_NXT_MIN_GTI_EXPIRE 0
#define arguments_BDK_TIM_NXT_MIN_GTI_EXPIRE -1,-1,-1,-1

/**
 * Register (NCB) tim_nxt_min_ptp_expire
 *
 * INTERNAL: TIM Next Minimum PTP Expire Time Registers
 */
union bdk_tim_nxt_min_ptp_expire
{
    uint64_t u;
    struct bdk_tim_nxt_min_ptp_expire_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) This field indicates the value TIM_FR_RN_PTP must reach
                                                                 before the next possible servicing of rings/buckets.
                                                                 For diagnostic use. */
#else /* Word 0 - Little Endian */
        uint64_t min_exp_time          : 33; /**< [ 32:  0](RO/H) This field indicates the value TIM_FR_RN_PTP must reach
                                                                 before the next possible servicing of rings/buckets.
                                                                 For diagnostic use. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_nxt_min_ptp_expire_s cn; */
};
typedef union bdk_tim_nxt_min_ptp_expire bdk_tim_nxt_min_ptp_expire_t;

#define BDK_TIM_NXT_MIN_PTP_EXPIRE BDK_TIM_NXT_MIN_PTP_EXPIRE_FUNC()
static inline uint64_t BDK_TIM_NXT_MIN_PTP_EXPIRE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_NXT_MIN_PTP_EXPIRE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000001118ll;
    __bdk_csr_fatal("TIM_NXT_MIN_PTP_EXPIRE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_NXT_MIN_PTP_EXPIRE bdk_tim_nxt_min_ptp_expire_t
#define bustype_BDK_TIM_NXT_MIN_PTP_EXPIRE BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_NXT_MIN_PTP_EXPIRE "TIM_NXT_MIN_PTP_EXPIRE"
#define device_bar_BDK_TIM_NXT_MIN_PTP_EXPIRE 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_NXT_MIN_PTP_EXPIRE 0
#define arguments_BDK_TIM_NXT_MIN_PTP_EXPIRE -1,-1,-1,-1

/**
 * Register (NCB) tim_pf_msix_pba#
 *
 * TIM PF MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the TIM_PF_INT_VEC_E
 * enumeration.
 */
union bdk_tim_pf_msix_pbax
{
    uint64_t u;
    struct bdk_tim_pf_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated TIM_PF_MSIX_VEC()_CTL, enumerated by
                                                                 TIM_PF_INT_VEC_E. Bits that have no associated TIM_PF_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated TIM_PF_MSIX_VEC()_CTL, enumerated by
                                                                 TIM_PF_INT_VEC_E. Bits that have no associated TIM_PF_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_pf_msix_pbax_s cn; */
};
typedef union bdk_tim_pf_msix_pbax bdk_tim_pf_msix_pbax_t;

static inline uint64_t BDK_TIM_PF_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_PF_MSIX_PBAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x858000ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("TIM_PF_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_PF_MSIX_PBAX(a) bdk_tim_pf_msix_pbax_t
#define bustype_BDK_TIM_PF_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_PF_MSIX_PBAX(a) "TIM_PF_MSIX_PBAX"
#define device_bar_BDK_TIM_PF_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_TIM_PF_MSIX_PBAX(a) (a)
#define arguments_BDK_TIM_PF_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_pf_msix_vec#_addr
 *
 * TIM PF MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the TIM_PF_INT_VEC_E enumeration.
 */
union bdk_tim_pf_msix_vecx_addr
{
    uint64_t u;
    struct bdk_tim_pf_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's TIM_PF_MSIX_VEC()_ADDR, TIM_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of TIM_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_TIM_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's TIM_PF_MSIX_VEC()_ADDR, TIM_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of TIM_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_TIM_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_pf_msix_vecx_addr_s cn; */
};
typedef union bdk_tim_pf_msix_vecx_addr bdk_tim_pf_msix_vecx_addr_t;

static inline uint64_t BDK_TIM_PF_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_PF_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x858000f00000ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("TIM_PF_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_PF_MSIX_VECX_ADDR(a) bdk_tim_pf_msix_vecx_addr_t
#define bustype_BDK_TIM_PF_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_PF_MSIX_VECX_ADDR(a) "TIM_PF_MSIX_VECX_ADDR"
#define device_bar_BDK_TIM_PF_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_TIM_PF_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_TIM_PF_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_pf_msix_vec#_ctl
 *
 * TIM PF MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the TIM_PF_INT_VEC_E enumeration.
 */
union bdk_tim_pf_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_tim_pf_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_pf_msix_vecx_ctl_s cn; */
};
typedef union bdk_tim_pf_msix_vecx_ctl bdk_tim_pf_msix_vecx_ctl_t;

static inline uint64_t BDK_TIM_PF_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_PF_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=1))
        return 0x858000f00008ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("TIM_PF_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_PF_MSIX_VECX_CTL(a) bdk_tim_pf_msix_vecx_ctl_t
#define bustype_BDK_TIM_PF_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_PF_MSIX_VECX_CTL(a) "TIM_PF_MSIX_VECX_CTL"
#define device_bar_BDK_TIM_PF_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_TIM_PF_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_TIM_PF_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_priv_af_int_cfg
 *
 * TIM Privileged AF Interrupt Configuration Registers
 */
union bdk_tim_priv_af_int_cfg
{
    uint64_t u;
    struct bdk_tim_priv_af_int_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by TIM_AF_INT_VEC_E. */
        uint64_t reserved_11           : 1;
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of AF interrupt vectors enumerated by
                                                                 TIM_AF_INT_VEC_E in RVU PF(0)'s MSI-X table. This offset is added to each
                                                                 enumerated value to obtain the corresponding MSI-X vector index. The
                                                                 highest enumerated value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF(0)_MSIX_CFG[PF_MSIXT_SIZEM1]. */
#else /* Word 0 - Little Endian */
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of AF interrupt vectors enumerated by
                                                                 TIM_AF_INT_VEC_E in RVU PF(0)'s MSI-X table. This offset is added to each
                                                                 enumerated value to obtain the corresponding MSI-X vector index. The
                                                                 highest enumerated value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF(0)_MSIX_CFG[PF_MSIXT_SIZEM1]. */
        uint64_t reserved_11           : 1;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by TIM_AF_INT_VEC_E. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_priv_af_int_cfg_s cn; */
};
typedef union bdk_tim_priv_af_int_cfg bdk_tim_priv_af_int_cfg_t;

#define BDK_TIM_PRIV_AF_INT_CFG BDK_TIM_PRIV_AF_INT_CFG_FUNC()
static inline uint64_t BDK_TIM_PRIV_AF_INT_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_PRIV_AF_INT_CFG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840090022000ll;
    __bdk_csr_fatal("TIM_PRIV_AF_INT_CFG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_PRIV_AF_INT_CFG bdk_tim_priv_af_int_cfg_t
#define bustype_BDK_TIM_PRIV_AF_INT_CFG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_PRIV_AF_INT_CFG "TIM_PRIV_AF_INT_CFG"
#define device_bar_BDK_TIM_PRIV_AF_INT_CFG 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_PRIV_AF_INT_CFG 0
#define arguments_BDK_TIM_PRIV_AF_INT_CFG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_priv_lf#_cfg
 *
 * TIM Privileged LF Configuration Registers
 * These registers allow each TIM local function (LF) to be provisioned to a VF/PF
 * slot for RVU. See also TIM_AF_RVU_LF_CFG_DEBUG.
 */
union bdk_tim_priv_lfx_cfg
{
    uint64_t u;
    struct bdk_tim_priv_lfx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enable. When set, the LF is enabled and provisioned to the VF/PF slot
                                                                 selected by [PF_FUNC] and [SLOT]. When clear, the LF is not provisioned.

                                                                 LF to slot mapping must be 1-to-1. Thus, each enabled LF must be provisioned
                                                                 to a unique {[PF_FUNC], [SLOT]} combination. */
        uint64_t reserved_24_62        : 39;
        uint64_t pf_func               : 16; /**< [ 23:  8](R/W) RVU VF/PF to which the LF is provisioned. Format defined by RVU_PF_FUNC_S.
                                                                 Interrupts from the LF are delivered to the selected PF/VF. */
        uint64_t slot                  : 8;  /**< [  7:  0](R/W) Slot within the VF/PF selected by [PF_FUNC] to which the LF is
                                                                 provisioned. */
#else /* Word 0 - Little Endian */
        uint64_t slot                  : 8;  /**< [  7:  0](R/W) Slot within the VF/PF selected by [PF_FUNC] to which the LF is
                                                                 provisioned. */
        uint64_t pf_func               : 16; /**< [ 23:  8](R/W) RVU VF/PF to which the LF is provisioned. Format defined by RVU_PF_FUNC_S.
                                                                 Interrupts from the LF are delivered to the selected PF/VF. */
        uint64_t reserved_24_62        : 39;
        uint64_t ena                   : 1;  /**< [ 63: 63](R/W) Enable. When set, the LF is enabled and provisioned to the VF/PF slot
                                                                 selected by [PF_FUNC] and [SLOT]. When clear, the LF is not provisioned.

                                                                 LF to slot mapping must be 1-to-1. Thus, each enabled LF must be provisioned
                                                                 to a unique {[PF_FUNC], [SLOT]} combination. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_priv_lfx_cfg_s cn; */
};
typedef union bdk_tim_priv_lfx_cfg bdk_tim_priv_lfx_cfg_t;

static inline uint64_t BDK_TIM_PRIV_LFX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_PRIV_LFX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840090020000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("TIM_PRIV_LFX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_PRIV_LFX_CFG(a) bdk_tim_priv_lfx_cfg_t
#define bustype_BDK_TIM_PRIV_LFX_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_PRIV_LFX_CFG(a) "TIM_PRIV_LFX_CFG"
#define device_bar_BDK_TIM_PRIV_LFX_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_PRIV_LFX_CFG(a) (a)
#define arguments_BDK_TIM_PRIV_LFX_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) tim_priv_lf#_int_cfg
 *
 * TIM Privileged LF Interrupt Configuration Registers
 */
union bdk_tim_priv_lfx_int_cfg
{
    uint64_t u;
    struct bdk_tim_priv_lfx_int_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by TIM_LF_INT_VEC_E. */
        uint64_t reserved_11           : 1;
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of LF interrupt vectors enumerated by the block's
                                                                 TIM_LF_INT_VEC_E in the MSI-X table of the corresponding RVU VF/PF (see
                                                                 TIM_PRIV_LF()_CFG[PF_FUNC]). This offset is added to each enumerated value
                                                                 to obtain the corresponding MSI-X vector index. The highest enumerated
                                                                 value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF()_MSIX_CFG[PF_MSIXT_SIZEM1,VF_MSIXT_SIZEM1]. */
#else /* Word 0 - Little Endian */
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of LF interrupt vectors enumerated by the block's
                                                                 TIM_LF_INT_VEC_E in the MSI-X table of the corresponding RVU VF/PF (see
                                                                 TIM_PRIV_LF()_CFG[PF_FUNC]). This offset is added to each enumerated value
                                                                 to obtain the corresponding MSI-X vector index. The highest enumerated
                                                                 value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF()_MSIX_CFG[PF_MSIXT_SIZEM1,VF_MSIXT_SIZEM1]. */
        uint64_t reserved_11           : 1;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by TIM_LF_INT_VEC_E. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_priv_lfx_int_cfg_s cn; */
};
typedef union bdk_tim_priv_lfx_int_cfg bdk_tim_priv_lfx_int_cfg_t;

static inline uint64_t BDK_TIM_PRIV_LFX_INT_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_PRIV_LFX_INT_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=255))
        return 0x840090024000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("TIM_PRIV_LFX_INT_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_PRIV_LFX_INT_CFG(a) bdk_tim_priv_lfx_int_cfg_t
#define bustype_BDK_TIM_PRIV_LFX_INT_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_TIM_PRIV_LFX_INT_CFG(a) "TIM_PRIV_LFX_INT_CFG"
#define device_bar_BDK_TIM_PRIV_LFX_INT_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_TIM_PRIV_LFX_INT_CFG(a) (a)
#define arguments_BDK_TIM_PRIV_LFX_INT_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_reg_flags
 *
 * TIM Flags Register
 * This register provides flags for TIM.
 */
union bdk_tim_reg_flags
{
    uint64_t u;
    struct bdk_tim_reg_flags_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t gpio_edge             : 2;  /**< [  6:  5](R/W) Edge used for GPIO timing.
                                                                 0x0 = no edges and the timer tick is not generated.
                                                                 0x1 = TIM counts low to high transitions.
                                                                 0x2 = TIM counts high to low transitions.
                                                                 0x3 = TIM counts both low to high and high to low transitions. */
        uint64_t reserved_3_4          : 2;
        uint64_t reset                 : 1;  /**< [  2:  2](WO/H) Reset. One-shot pulse for free-running timers TIM_FR_RN_\<CLOCK\>. */
        uint64_t reserved_1            : 1;
        uint64_t ena_tim               : 1;  /**< [  0:  0](R/W) When set, TIM is in normal operation. When clear, time is effectively stopped for all
                                                                 rings in TIM.

                                                                 TIM has a counter (see TIM_FR_RN_CYCLES) that causes a periodic tick. This
                                                                 counter is shared by all rings. Each timer tick causes the hardware to decrement
                                                                 the time count for all enabled rings.

                                                                 When [ENA_TIM] = 0, the hardware stops the shared periodic counter,
                                                                 TIM_FR_RN_CYCLES, so there are no more timer ticks, and there are no more new
                                                                 bucket traversals.

                                                                 If [ENA_TIM] transitions 1-\>0, TIM longer creates new bucket traversals, but
                                                                 does traverse any rings that previously expired and are pending hardware
                                                                 traversal. */
#else /* Word 0 - Little Endian */
        uint64_t ena_tim               : 1;  /**< [  0:  0](R/W) When set, TIM is in normal operation. When clear, time is effectively stopped for all
                                                                 rings in TIM.

                                                                 TIM has a counter (see TIM_FR_RN_CYCLES) that causes a periodic tick. This
                                                                 counter is shared by all rings. Each timer tick causes the hardware to decrement
                                                                 the time count for all enabled rings.

                                                                 When [ENA_TIM] = 0, the hardware stops the shared periodic counter,
                                                                 TIM_FR_RN_CYCLES, so there are no more timer ticks, and there are no more new
                                                                 bucket traversals.

                                                                 If [ENA_TIM] transitions 1-\>0, TIM longer creates new bucket traversals, but
                                                                 does traverse any rings that previously expired and are pending hardware
                                                                 traversal. */
        uint64_t reserved_1            : 1;
        uint64_t reset                 : 1;  /**< [  2:  2](WO/H) Reset. One-shot pulse for free-running timers TIM_FR_RN_\<CLOCK\>. */
        uint64_t reserved_3_4          : 2;
        uint64_t gpio_edge             : 2;  /**< [  6:  5](R/W) Edge used for GPIO timing.
                                                                 0x0 = no edges and the timer tick is not generated.
                                                                 0x1 = TIM counts low to high transitions.
                                                                 0x2 = TIM counts high to low transitions.
                                                                 0x3 = TIM counts both low to high and high to low transitions. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_reg_flags_s cn; */
};
typedef union bdk_tim_reg_flags bdk_tim_reg_flags_t;

#define BDK_TIM_REG_FLAGS BDK_TIM_REG_FLAGS_FUNC()
static inline uint64_t BDK_TIM_REG_FLAGS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_REG_FLAGS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x858000000000ll;
    __bdk_csr_fatal("TIM_REG_FLAGS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_REG_FLAGS bdk_tim_reg_flags_t
#define bustype_BDK_TIM_REG_FLAGS BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_REG_FLAGS "TIM_REG_FLAGS"
#define device_bar_BDK_TIM_REG_FLAGS 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_REG_FLAGS 0
#define arguments_BDK_TIM_REG_FLAGS -1,-1,-1,-1

/**
 * Register (NCB) tim_ring#_ctl0
 *
 * TIM Ring Control 0 Registers
 */
union bdk_tim_ringx_ctl0
{
    uint64_t u;
    struct bdk_tim_ringx_ctl0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t expire_offset         : 32; /**< [ 63: 32](R/W/H) Time at which the next bucket will be serviced, or offset. See also
                                                                 TIM_VRING()_REL[TIMERCOUNT] for the timer ticks until the interval experation.

                                                                 If TIM_RING()_CTL1[ENA] = 0, then contains an offset. When ENA transitions from a
                                                                 zero to a one this offset will be added to the current time and loaded back into
                                                                 [EXPIRE_OFFSET]. Thus the offset sets the delta time between ENA transitioning to one and
                                                                 the very first time the ring will be serviced. Software should program different offsets
                                                                 on each ring to reduce congestion to prevent many rings from otherwise expiring
                                                                 concurrently.

                                                                 If TIM_RING()_CTL1[ENA] = 1, then contains the time in the future the next
                                                                 bucket will be serviced.

                                                                 When [EXPIRE_OFFSET] reaches the current time (TIM_FR_RN_CYCLES or TIM_FR_RN_GPIOS),
                                                                 [EXPIRE_OFFSET] is set to the next expiration time (current time plus
                                                                 TIM_RING()_CTL0[INTERVAL]).

                                                                 [EXPIRE_OFFSET] is unpredictable after TIM_RING()_CTL1[CLK_SRC] changes or
                                                                 TIM_RING()_CTL1[ENA] transitions from one to zero, and must be reprogrammed before
                                                                 (re-) setting TIM_RING()_CTL1[ENA]. */
        uint64_t interval              : 32; /**< [ 31:  0](R/W) Timer interval, measured in timer ticks (GTI or PTP clocks, or GPIO transitions).
                                                                 Minimum value is 256 for GPIO rings, 300 for GTI and PTP rings, and 512 for
                                                                 SCLK rings. Minimum time which this interval is recommended to represent is
                                                                 1 usec, or 1 usec for every 64 entries in the bucket, whichever is greater. */
#else /* Word 0 - Little Endian */
        uint64_t interval              : 32; /**< [ 31:  0](R/W) Timer interval, measured in timer ticks (GTI or PTP clocks, or GPIO transitions).
                                                                 Minimum value is 256 for GPIO rings, 300 for GTI and PTP rings, and 512 for
                                                                 SCLK rings. Minimum time which this interval is recommended to represent is
                                                                 1 usec, or 1 usec for every 64 entries in the bucket, whichever is greater. */
        uint64_t expire_offset         : 32; /**< [ 63: 32](R/W/H) Time at which the next bucket will be serviced, or offset. See also
                                                                 TIM_VRING()_REL[TIMERCOUNT] for the timer ticks until the interval experation.

                                                                 If TIM_RING()_CTL1[ENA] = 0, then contains an offset. When ENA transitions from a
                                                                 zero to a one this offset will be added to the current time and loaded back into
                                                                 [EXPIRE_OFFSET]. Thus the offset sets the delta time between ENA transitioning to one and
                                                                 the very first time the ring will be serviced. Software should program different offsets
                                                                 on each ring to reduce congestion to prevent many rings from otherwise expiring
                                                                 concurrently.

                                                                 If TIM_RING()_CTL1[ENA] = 1, then contains the time in the future the next
                                                                 bucket will be serviced.

                                                                 When [EXPIRE_OFFSET] reaches the current time (TIM_FR_RN_CYCLES or TIM_FR_RN_GPIOS),
                                                                 [EXPIRE_OFFSET] is set to the next expiration time (current time plus
                                                                 TIM_RING()_CTL0[INTERVAL]).

                                                                 [EXPIRE_OFFSET] is unpredictable after TIM_RING()_CTL1[CLK_SRC] changes or
                                                                 TIM_RING()_CTL1[ENA] transitions from one to zero, and must be reprogrammed before
                                                                 (re-) setting TIM_RING()_CTL1[ENA]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_ringx_ctl0_s cn; */
};
typedef union bdk_tim_ringx_ctl0 bdk_tim_ringx_ctl0_t;

static inline uint64_t BDK_TIM_RINGX_CTL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_RINGX_CTL0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858000002000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_RINGX_CTL0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_RINGX_CTL0(a) bdk_tim_ringx_ctl0_t
#define bustype_BDK_TIM_RINGX_CTL0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_RINGX_CTL0(a) "TIM_RINGX_CTL0"
#define device_bar_BDK_TIM_RINGX_CTL0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_RINGX_CTL0(a) (a)
#define arguments_BDK_TIM_RINGX_CTL0(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_ring#_ctl1
 *
 * TIM Ring Control 1 Registers
 */
union bdk_tim_ringx_ctl1
{
    uint64_t u;
    struct bdk_tim_ringx_ctl1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_55_63        : 9;
        uint64_t be                    : 1;  /**< [ 54: 54](R/W) Ring big-endian. If set, TIM_MEM_BUCKET_S and other in-memory structures are big endian. */
        uint64_t clk_src               : 3;  /**< [ 53: 51](R/W) Source of ring's timer tick. Enumerated by TIM_CLK_SRCS_E. To change [CLK_SRC]:

                                                                 1. TIM_RING()_CTL1[ENA] is cleared.

                                                                 2. [CLK_SRC] is changed.

                                                                 3. TIM_RING()_CTL0[EXPIRE_OFFSET] is reprogrammed appropriately.

                                                                 4. TIM_RING()_CTL1[ENA] is set. */
        uint64_t rcf_busy              : 1;  /**< [ 50: 50](RO/H) Ring reconfiguration busy. When [ENA] is cleared, this bit will be set, if an
                                                                 engine is currently scheduled to, or is processing, a ring. It will remain set until
                                                                 hardware completes the idling of the ring. [ENA] must not be re-enabled until clear. */
        uint64_t reserved_49           : 1;
        uint64_t lock_en               : 1;  /**< [ 48: 48](R/W) Enables bucket locking mechanism between hardware and software.
                                                                   0 = Hardware will always service the bucket when it expires.
                                                                   1 = Hardware skips buckets when it can't get the bucket's lock. */
        uint64_t ena                   : 1;  /**< [ 47: 47](R/W/H) Ring timer enable. After a one to zero transition on ENA, the hardware still
                                                                 completes a bucket traversal for the ring if it were pending or active
                                                                 prior to the transition. When clearing, software must delay until
                                                                 [RCF_BUSY] = 0 to ensure the completion of the traversal before reprogramming
                                                                 the ring. Hardware will clear this bit when any TIM_VF()_NRSPERR_INT[*] bit
                                                                 is set by hardware. */
        uint64_t reserved_46           : 1;
        uint64_t ena_prd               : 1;  /**< [ 45: 45](R/W) Enable periodic mode, which disables the memory write of zeros to
                                                                 TIM_MEM_BUCKET_S[NUM_ENTRIES] and TIM_MEM_BUCKET_S[CHUNK_REMAINDER] when a
                                                                 bucket is traversed. In periodic mode, [ENA_LDWB] must be cleared.
                                                                 Also, in periodic mode, [ENA_DFB] should be one, and zero otherwise. */
        uint64_t ena_ldwb              : 1;  /**< [ 44: 44](R/W) When set, enables the use of load and don't-write-back when reading timer entry cache lines.
                                                                 Must be clear when [ENA_PRD] is set. */
        uint64_t ena_dfb               : 1;  /**< [ 43: 43](R/W) Enable don't free buffer. When set, chunk buffer is not released by the TIM back to FPA.
                                                                 Must be set when [ENA_PRD] is set. */
        uint64_t reserved_40_42        : 3;
        uint64_t bucket                : 20; /**< [ 39: 20](R/W/H) Current bucket. Should be set to 0x0 by software at enable time. Incremented once per
                                                                 bucket traversal. */
        uint64_t bsize                 : 20; /**< [ 19:  0](R/W) Number of buckets minus one. If [BSIZE] = 0x0, there is only one bucket in each
                                                                 non-empty ring. */
#else /* Word 0 - Little Endian */
        uint64_t bsize                 : 20; /**< [ 19:  0](R/W) Number of buckets minus one. If [BSIZE] = 0x0, there is only one bucket in each
                                                                 non-empty ring. */
        uint64_t bucket                : 20; /**< [ 39: 20](R/W/H) Current bucket. Should be set to 0x0 by software at enable time. Incremented once per
                                                                 bucket traversal. */
        uint64_t reserved_40_42        : 3;
        uint64_t ena_dfb               : 1;  /**< [ 43: 43](R/W) Enable don't free buffer. When set, chunk buffer is not released by the TIM back to FPA.
                                                                 Must be set when [ENA_PRD] is set. */
        uint64_t ena_ldwb              : 1;  /**< [ 44: 44](R/W) When set, enables the use of load and don't-write-back when reading timer entry cache lines.
                                                                 Must be clear when [ENA_PRD] is set. */
        uint64_t ena_prd               : 1;  /**< [ 45: 45](R/W) Enable periodic mode, which disables the memory write of zeros to
                                                                 TIM_MEM_BUCKET_S[NUM_ENTRIES] and TIM_MEM_BUCKET_S[CHUNK_REMAINDER] when a
                                                                 bucket is traversed. In periodic mode, [ENA_LDWB] must be cleared.
                                                                 Also, in periodic mode, [ENA_DFB] should be one, and zero otherwise. */
        uint64_t reserved_46           : 1;
        uint64_t ena                   : 1;  /**< [ 47: 47](R/W/H) Ring timer enable. After a one to zero transition on ENA, the hardware still
                                                                 completes a bucket traversal for the ring if it were pending or active
                                                                 prior to the transition. When clearing, software must delay until
                                                                 [RCF_BUSY] = 0 to ensure the completion of the traversal before reprogramming
                                                                 the ring. Hardware will clear this bit when any TIM_VF()_NRSPERR_INT[*] bit
                                                                 is set by hardware. */
        uint64_t lock_en               : 1;  /**< [ 48: 48](R/W) Enables bucket locking mechanism between hardware and software.
                                                                   0 = Hardware will always service the bucket when it expires.
                                                                   1 = Hardware skips buckets when it can't get the bucket's lock. */
        uint64_t reserved_49           : 1;
        uint64_t rcf_busy              : 1;  /**< [ 50: 50](RO/H) Ring reconfiguration busy. When [ENA] is cleared, this bit will be set, if an
                                                                 engine is currently scheduled to, or is processing, a ring. It will remain set until
                                                                 hardware completes the idling of the ring. [ENA] must not be re-enabled until clear. */
        uint64_t clk_src               : 3;  /**< [ 53: 51](R/W) Source of ring's timer tick. Enumerated by TIM_CLK_SRCS_E. To change [CLK_SRC]:

                                                                 1. TIM_RING()_CTL1[ENA] is cleared.

                                                                 2. [CLK_SRC] is changed.

                                                                 3. TIM_RING()_CTL0[EXPIRE_OFFSET] is reprogrammed appropriately.

                                                                 4. TIM_RING()_CTL1[ENA] is set. */
        uint64_t be                    : 1;  /**< [ 54: 54](R/W) Ring big-endian. If set, TIM_MEM_BUCKET_S and other in-memory structures are big endian. */
        uint64_t reserved_55_63        : 9;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_ringx_ctl1_s cn; */
};
typedef union bdk_tim_ringx_ctl1 bdk_tim_ringx_ctl1_t;

static inline uint64_t BDK_TIM_RINGX_CTL1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_RINGX_CTL1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858000002400ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_RINGX_CTL1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_RINGX_CTL1(a) bdk_tim_ringx_ctl1_t
#define bustype_BDK_TIM_RINGX_CTL1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_RINGX_CTL1(a) "TIM_RINGX_CTL1"
#define device_bar_BDK_TIM_RINGX_CTL1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_RINGX_CTL1(a) (a)
#define arguments_BDK_TIM_RINGX_CTL1(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_ring#_ctl2
 *
 * TIM Ring Control 2 Registers
 */
union bdk_tim_ringx_ctl2
{
    uint64_t u;
    struct bdk_tim_ringx_ctl2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t csize                 : 13; /**< [ 52: 40](R/W) Number of sixteen-byte words per chunk, i.e. one for the next pointer plus one
                                                                 times the number of TIM_MEM_ENTRY_S. [CSIZE] mod(8) must be zero. */
        uint64_t reserved_0_39         : 40;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_39         : 40;
        uint64_t csize                 : 13; /**< [ 52: 40](R/W) Number of sixteen-byte words per chunk, i.e. one for the next pointer plus one
                                                                 times the number of TIM_MEM_ENTRY_S. [CSIZE] mod(8) must be zero. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_ringx_ctl2_s cn; */
};
typedef union bdk_tim_ringx_ctl2 bdk_tim_ringx_ctl2_t;

static inline uint64_t BDK_TIM_RINGX_CTL2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_RINGX_CTL2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858000002800ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_RINGX_CTL2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_RINGX_CTL2(a) bdk_tim_ringx_ctl2_t
#define bustype_BDK_TIM_RINGX_CTL2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_RINGX_CTL2(a) "TIM_RINGX_CTL2"
#define device_bar_BDK_TIM_RINGX_CTL2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_RINGX_CTL2(a) (a)
#define arguments_BDK_TIM_RINGX_CTL2(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_ring#_gmctl
 *
 * TIM Ring Guest Machine Control Register
 */
union bdk_tim_ringx_gmctl
{
    uint64_t u;
    struct bdk_tim_ringx_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Low eight bits of the SMMU stream identifier to use when issuing requests.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc. */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all buffer free, or to SSO
                                                                 for all submit work operations initiated by this ring.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all buffer free, or to SSO
                                                                 for all submit work operations initiated by this ring.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Low eight bits of the SMMU stream identifier to use when issuing requests.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_ringx_gmctl_s cn; */
};
typedef union bdk_tim_ringx_gmctl bdk_tim_ringx_gmctl_t;

static inline uint64_t BDK_TIM_RINGX_GMCTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_RINGX_GMCTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858000002a00ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_RINGX_GMCTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_RINGX_GMCTL(a) bdk_tim_ringx_gmctl_t
#define bustype_BDK_TIM_RINGX_GMCTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_RINGX_GMCTL(a) "TIM_RINGX_GMCTL"
#define device_bar_BDK_TIM_RINGX_GMCTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_RINGX_GMCTL(a) (a)
#define arguments_BDK_TIM_RINGX_GMCTL(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vf#_msix_pba#
 *
 * TIM VF MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the TIM_VF_INT_VEC_E
 * enumeration.
 */
union bdk_tim_vfx_msix_pbax
{
    uint64_t u;
    struct bdk_tim_vfx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated TIM_PF_MSIX_VEC()_CTL, enumerated by
                                                                 TIM_PF_INT_VEC_E. Bits that have no associated TIM_PF_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated TIM_PF_MSIX_VEC()_CTL, enumerated by
                                                                 TIM_PF_INT_VEC_E. Bits that have no associated TIM_PF_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vfx_msix_pbax_s cn; */
};
typedef union bdk_tim_vfx_msix_pbax bdk_tim_vfx_msix_pbax_t;

static inline uint64_t BDK_TIM_VFX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VFX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=63) && (b==0)))
        return 0x8580200f0000ll + 0x100000ll * ((a) & 0x3f) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("TIM_VFX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VFX_MSIX_PBAX(a,b) bdk_tim_vfx_msix_pbax_t
#define bustype_BDK_TIM_VFX_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VFX_MSIX_PBAX(a,b) "TIM_VFX_MSIX_PBAX"
#define device_bar_BDK_TIM_VFX_MSIX_PBAX(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_TIM_VFX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_TIM_VFX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) tim_vf#_msix_vec#_addr
 *
 * TIM VF MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the TIM_PF_INT_VEC_E enumeration.
 */
union bdk_tim_vfx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_tim_vfx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_TIM_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_TIM_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vfx_msix_vecx_addr_s cn; */
};
typedef union bdk_tim_vfx_msix_vecx_addr bdk_tim_vfx_msix_vecx_addr_t;

static inline uint64_t BDK_TIM_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=63) && (b==0)))
        return 0x858020000000ll + 0x100000ll * ((a) & 0x3f) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("TIM_VFX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VFX_MSIX_VECX_ADDR(a,b) bdk_tim_vfx_msix_vecx_addr_t
#define bustype_BDK_TIM_VFX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VFX_MSIX_VECX_ADDR(a,b) "TIM_VFX_MSIX_VECX_ADDR"
#define device_bar_BDK_TIM_VFX_MSIX_VECX_ADDR(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_TIM_VFX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_TIM_VFX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) tim_vf#_msix_vec#_ctl
 *
 * TIM VF MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the TIM_VF_INT_VEC_E enumeration.
 */
union bdk_tim_vfx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_tim_vfx_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vfx_msix_vecx_ctl_s cn; */
};
typedef union bdk_tim_vfx_msix_vecx_ctl bdk_tim_vfx_msix_vecx_ctl_t;

static inline uint64_t BDK_TIM_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=63) && (b==0)))
        return 0x858020000008ll + 0x100000ll * ((a) & 0x3f) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("TIM_VFX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VFX_MSIX_VECX_CTL(a,b) bdk_tim_vfx_msix_vecx_ctl_t
#define bustype_BDK_TIM_VFX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VFX_MSIX_VECX_CTL(a,b) "TIM_VFX_MSIX_VECX_CTL"
#define device_bar_BDK_TIM_VFX_MSIX_VECX_CTL(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_TIM_VFX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_TIM_VFX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) tim_vf#_nrsperr_ena_w1c
 *
 * TIM NCB Response Error Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_tim_vfx_nrsperr_ena_w1c
{
    uint64_t u;
    struct bdk_tim_vfx_nrsperr_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t atomic_err            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for TIM_VF(0..63)_NRSPERR_INT[ATOMIC_ERR]. */
        uint64_t load_err              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for TIM_VF(0..63)_NRSPERR_INT[LOAD_ERR]. */
        uint64_t stdn_err              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_VF(0..63)_NRSPERR_INT[STDN_ERR]. */
#else /* Word 0 - Little Endian */
        uint64_t stdn_err              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for TIM_VF(0..63)_NRSPERR_INT[STDN_ERR]. */
        uint64_t load_err              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for TIM_VF(0..63)_NRSPERR_INT[LOAD_ERR]. */
        uint64_t atomic_err            : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for TIM_VF(0..63)_NRSPERR_INT[ATOMIC_ERR]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vfx_nrsperr_ena_w1c_s cn; */
};
typedef union bdk_tim_vfx_nrsperr_ena_w1c bdk_tim_vfx_nrsperr_ena_w1c_t;

static inline uint64_t BDK_TIM_VFX_NRSPERR_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VFX_NRSPERR_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000010ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VFX_NRSPERR_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VFX_NRSPERR_ENA_W1C(a) bdk_tim_vfx_nrsperr_ena_w1c_t
#define bustype_BDK_TIM_VFX_NRSPERR_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VFX_NRSPERR_ENA_W1C(a) "TIM_VFX_NRSPERR_ENA_W1C"
#define device_bar_BDK_TIM_VFX_NRSPERR_ENA_W1C(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VFX_NRSPERR_ENA_W1C(a) (a)
#define arguments_BDK_TIM_VFX_NRSPERR_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vf#_nrsperr_ena_w1s
 *
 * TIM NCB Response Error Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_tim_vfx_nrsperr_ena_w1s
{
    uint64_t u;
    struct bdk_tim_vfx_nrsperr_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t atomic_err            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for TIM_VF(0..63)_NRSPERR_INT[ATOMIC_ERR]. */
        uint64_t load_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for TIM_VF(0..63)_NRSPERR_INT[LOAD_ERR]. */
        uint64_t stdn_err              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_VF(0..63)_NRSPERR_INT[STDN_ERR]. */
#else /* Word 0 - Little Endian */
        uint64_t stdn_err              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for TIM_VF(0..63)_NRSPERR_INT[STDN_ERR]. */
        uint64_t load_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for TIM_VF(0..63)_NRSPERR_INT[LOAD_ERR]. */
        uint64_t atomic_err            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for TIM_VF(0..63)_NRSPERR_INT[ATOMIC_ERR]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vfx_nrsperr_ena_w1s_s cn; */
};
typedef union bdk_tim_vfx_nrsperr_ena_w1s bdk_tim_vfx_nrsperr_ena_w1s_t;

static inline uint64_t BDK_TIM_VFX_NRSPERR_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VFX_NRSPERR_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000018ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VFX_NRSPERR_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VFX_NRSPERR_ENA_W1S(a) bdk_tim_vfx_nrsperr_ena_w1s_t
#define bustype_BDK_TIM_VFX_NRSPERR_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VFX_NRSPERR_ENA_W1S(a) "TIM_VFX_NRSPERR_ENA_W1S"
#define device_bar_BDK_TIM_VFX_NRSPERR_ENA_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VFX_NRSPERR_ENA_W1S(a) (a)
#define arguments_BDK_TIM_VFX_NRSPERR_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vf#_nrsperr_int
 *
 * TIM NCB Response Error Interrupt Register
 */
union bdk_tim_vfx_nrsperr_int
{
    uint64_t u;
    struct bdk_tim_vfx_nrsperr_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t atomic_err            : 1;  /**< [  2:  2](R/W1C/H) Atomic error flag. Each VF bit corresponds to rings [63:0] respectively.
                                                                 This register reflects any atomic set/clear errors received for specific
                                                                 ring NCB atomic (SET64/CLR64) operations. */
        uint64_t load_err              : 1;  /**< [  1:  1](R/W1C/H) Load error flag. Set when a load fault was detected, e.g. a SMMU page fault to a
                                                                 bad IOVA request by this ring. */
        uint64_t stdn_err              : 1;  /**< [  0:  0](R/W1C/H) Store error flag. Set when a store fault was detected, e.g. a SMMU page fault to
                                                                 a bad IOVA request by this ring. */
#else /* Word 0 - Little Endian */
        uint64_t stdn_err              : 1;  /**< [  0:  0](R/W1C/H) Store error flag. Set when a store fault was detected, e.g. a SMMU page fault to
                                                                 a bad IOVA request by this ring. */
        uint64_t load_err              : 1;  /**< [  1:  1](R/W1C/H) Load error flag. Set when a load fault was detected, e.g. a SMMU page fault to a
                                                                 bad IOVA request by this ring. */
        uint64_t atomic_err            : 1;  /**< [  2:  2](R/W1C/H) Atomic error flag. Each VF bit corresponds to rings [63:0] respectively.
                                                                 This register reflects any atomic set/clear errors received for specific
                                                                 ring NCB atomic (SET64/CLR64) operations. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vfx_nrsperr_int_s cn; */
};
typedef union bdk_tim_vfx_nrsperr_int bdk_tim_vfx_nrsperr_int_t;

static inline uint64_t BDK_TIM_VFX_NRSPERR_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VFX_NRSPERR_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000000ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VFX_NRSPERR_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VFX_NRSPERR_INT(a) bdk_tim_vfx_nrsperr_int_t
#define bustype_BDK_TIM_VFX_NRSPERR_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VFX_NRSPERR_INT(a) "TIM_VFX_NRSPERR_INT"
#define device_bar_BDK_TIM_VFX_NRSPERR_INT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VFX_NRSPERR_INT(a) (a)
#define arguments_BDK_TIM_VFX_NRSPERR_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vf#_nrsperr_int_w1s
 *
 * TIM NCB Response Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_tim_vfx_nrsperr_int_w1s
{
    uint64_t u;
    struct bdk_tim_vfx_nrsperr_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t atomic_err            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets TIM_VF(0..63)_NRSPERR_INT[ATOMIC_ERR]. */
        uint64_t load_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets TIM_VF(0..63)_NRSPERR_INT[LOAD_ERR]. */
        uint64_t stdn_err              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_VF(0..63)_NRSPERR_INT[STDN_ERR]. */
#else /* Word 0 - Little Endian */
        uint64_t stdn_err              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets TIM_VF(0..63)_NRSPERR_INT[STDN_ERR]. */
        uint64_t load_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets TIM_VF(0..63)_NRSPERR_INT[LOAD_ERR]. */
        uint64_t atomic_err            : 1;  /**< [  2:  2](R/W1S/H) Reads or sets TIM_VF(0..63)_NRSPERR_INT[ATOMIC_ERR]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vfx_nrsperr_int_w1s_s cn; */
};
typedef union bdk_tim_vfx_nrsperr_int_w1s bdk_tim_vfx_nrsperr_int_w1s_t;

static inline uint64_t BDK_TIM_VFX_NRSPERR_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VFX_NRSPERR_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000008ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VFX_NRSPERR_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VFX_NRSPERR_INT_W1S(a) bdk_tim_vfx_nrsperr_int_w1s_t
#define bustype_BDK_TIM_VFX_NRSPERR_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VFX_NRSPERR_INT_W1S(a) "TIM_VFX_NRSPERR_INT_W1S"
#define device_bar_BDK_TIM_VFX_NRSPERR_INT_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VFX_NRSPERR_INT_W1S(a) (a)
#define arguments_BDK_TIM_VFX_NRSPERR_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_aura
 *
 * TIM Ring Aura Registers
 */
union bdk_tim_vringx_aura
{
    uint64_t u;
    struct bdk_tim_vringx_aura_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t aura                  : 16; /**< [ 15:  0](R/W) Guest-aura number used to free and return chunks to. Bits \<15:12\> must be zero.
                                                                 Ignored if TIM_RING()_CTL1[ENA_DFB] is set.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and TIM_VRING()_GMCTL[GMID] as valid. */
#else /* Word 0 - Little Endian */
        uint64_t aura                  : 16; /**< [ 15:  0](R/W) Guest-aura number used to free and return chunks to. Bits \<15:12\> must be zero.
                                                                 Ignored if TIM_RING()_CTL1[ENA_DFB] is set.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and TIM_VRING()_GMCTL[GMID] as valid. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_aura_s cn; */
};
typedef union bdk_tim_vringx_aura bdk_tim_vringx_aura_t;

static inline uint64_t BDK_TIM_VRINGX_AURA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_AURA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000108ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_AURA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_AURA(a) bdk_tim_vringx_aura_t
#define bustype_BDK_TIM_VRINGX_AURA(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_AURA(a) "TIM_VRINGX_AURA"
#define device_bar_BDK_TIM_VRINGX_AURA(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_AURA(a) (a)
#define arguments_BDK_TIM_VRINGX_AURA(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_base
 *
 * TIM Ring Base Registers
 */
union bdk_tim_vringx_base
{
    uint64_t u;
    struct bdk_tim_vringx_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t base                  : 44; /**< [ 48:  5](R/W) IOVA pointer to bucket 0. Naturally aligned to the 32-byte size of
                                                                 TIM_MEM_BUCKET_S. */
        uint64_t reserved_0_4          : 5;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_4          : 5;
        uint64_t base                  : 44; /**< [ 48:  5](R/W) IOVA pointer to bucket 0. Naturally aligned to the 32-byte size of
                                                                 TIM_MEM_BUCKET_S. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_base_s cn; */
};
typedef union bdk_tim_vringx_base bdk_tim_vringx_base_t;

static inline uint64_t BDK_TIM_VRINGX_BASE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_BASE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000100ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_BASE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_BASE(a) bdk_tim_vringx_base_t
#define bustype_BDK_TIM_VRINGX_BASE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_BASE(a) "TIM_VRINGX_BASE"
#define device_bar_BDK_TIM_VRINGX_BASE(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_BASE(a) (a)
#define arguments_BDK_TIM_VRINGX_BASE(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_ctl0
 *
 * TIM Ring Control 0 Registers
 * This register is a read-only copy of TIM_RING()_CTL0.
 */
union bdk_tim_vringx_ctl0
{
    uint64_t u;
    struct bdk_tim_vringx_ctl0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t expire_offset         : 32; /**< [ 63: 32](RO/H) Read-only TIM_RING(0..63)_CTL0[EXPIRE_OFFSET]. */
        uint64_t interval              : 32; /**< [ 31:  0](RO) Read-only TIM_RING(0..63)_CTL0[INTERVAL]. */
#else /* Word 0 - Little Endian */
        uint64_t interval              : 32; /**< [ 31:  0](RO) Read-only TIM_RING(0..63)_CTL0[INTERVAL]. */
        uint64_t expire_offset         : 32; /**< [ 63: 32](RO/H) Read-only TIM_RING(0..63)_CTL0[EXPIRE_OFFSET]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_ctl0_s cn; */
};
typedef union bdk_tim_vringx_ctl0 bdk_tim_vringx_ctl0_t;

static inline uint64_t BDK_TIM_VRINGX_CTL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_CTL0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000040ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_CTL0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_CTL0(a) bdk_tim_vringx_ctl0_t
#define bustype_BDK_TIM_VRINGX_CTL0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_CTL0(a) "TIM_VRINGX_CTL0"
#define device_bar_BDK_TIM_VRINGX_CTL0(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_CTL0(a) (a)
#define arguments_BDK_TIM_VRINGX_CTL0(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_ctl1
 *
 * TIM Ring Control 1 Registers
 * This register is a read-only copy of TIM_RING()_CTL1.
 */
union bdk_tim_vringx_ctl1
{
    uint64_t u;
    struct bdk_tim_vringx_ctl1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_55_63        : 9;
        uint64_t be                    : 1;  /**< [ 54: 54](RO) Read-only TIM_RING(0..63)_CTL1[BE]. */
        uint64_t clk_src               : 3;  /**< [ 53: 51](RO) Read-only TIM_RING(0..63)_CTL1[CLK_SRC]. */
        uint64_t rcf_busy              : 1;  /**< [ 50: 50](RO/H) Read-only TIM_RING(0..63)_CTL1[RCF_BUSY]. */
        uint64_t reserved_49           : 1;
        uint64_t lock_en               : 1;  /**< [ 48: 48](RO) Read-only TIM_RING(0..63)_CTL1[LOCK_EN]. */
        uint64_t ena                   : 1;  /**< [ 47: 47](RO/H) Read-only TIM_RING(0..63)_CTL1[ENA]. */
        uint64_t reserved_46           : 1;
        uint64_t ena_prd               : 1;  /**< [ 45: 45](RO) Read-only TIM_RING(0..63)_CTL1[ENA_PRD]. */
        uint64_t ena_ldwb              : 1;  /**< [ 44: 44](RO) Read-only TIM_RING(0..63)_CTL1[ENA_LDWB]. */
        uint64_t ena_dfb               : 1;  /**< [ 43: 43](RO) Read-only TIM_RING(0..63)_CTL1[ENA_DFB]. */
        uint64_t reserved_40_42        : 3;
        uint64_t bucket                : 20; /**< [ 39: 20](RO/H) Read-only TIM_RING(0..63)_CTL1[BUCKET]. */
        uint64_t bsize                 : 20; /**< [ 19:  0](RO) Read-only TIM_RING(0..63)_CTL1[BSIZE]. */
#else /* Word 0 - Little Endian */
        uint64_t bsize                 : 20; /**< [ 19:  0](RO) Read-only TIM_RING(0..63)_CTL1[BSIZE]. */
        uint64_t bucket                : 20; /**< [ 39: 20](RO/H) Read-only TIM_RING(0..63)_CTL1[BUCKET]. */
        uint64_t reserved_40_42        : 3;
        uint64_t ena_dfb               : 1;  /**< [ 43: 43](RO) Read-only TIM_RING(0..63)_CTL1[ENA_DFB]. */
        uint64_t ena_ldwb              : 1;  /**< [ 44: 44](RO) Read-only TIM_RING(0..63)_CTL1[ENA_LDWB]. */
        uint64_t ena_prd               : 1;  /**< [ 45: 45](RO) Read-only TIM_RING(0..63)_CTL1[ENA_PRD]. */
        uint64_t reserved_46           : 1;
        uint64_t ena                   : 1;  /**< [ 47: 47](RO/H) Read-only TIM_RING(0..63)_CTL1[ENA]. */
        uint64_t lock_en               : 1;  /**< [ 48: 48](RO) Read-only TIM_RING(0..63)_CTL1[LOCK_EN]. */
        uint64_t reserved_49           : 1;
        uint64_t rcf_busy              : 1;  /**< [ 50: 50](RO/H) Read-only TIM_RING(0..63)_CTL1[RCF_BUSY]. */
        uint64_t clk_src               : 3;  /**< [ 53: 51](RO) Read-only TIM_RING(0..63)_CTL1[CLK_SRC]. */
        uint64_t be                    : 1;  /**< [ 54: 54](RO) Read-only TIM_RING(0..63)_CTL1[BE]. */
        uint64_t reserved_55_63        : 9;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_ctl1_s cn; */
};
typedef union bdk_tim_vringx_ctl1 bdk_tim_vringx_ctl1_t;

static inline uint64_t BDK_TIM_VRINGX_CTL1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_CTL1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000050ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_CTL1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_CTL1(a) bdk_tim_vringx_ctl1_t
#define bustype_BDK_TIM_VRINGX_CTL1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_CTL1(a) "TIM_VRINGX_CTL1"
#define device_bar_BDK_TIM_VRINGX_CTL1(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_CTL1(a) (a)
#define arguments_BDK_TIM_VRINGX_CTL1(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_ctl2
 *
 * TIM Ring Control 2 Registers
 * This register is a read-only copy of TIM_RING()_CTL2.
 */
union bdk_tim_vringx_ctl2
{
    uint64_t u;
    struct bdk_tim_vringx_ctl2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t csize                 : 13; /**< [ 52: 40](RO) Read-only TIM_RING(0..63)_CTL2[CSIZE]. */
        uint64_t reserved_0_39         : 40;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_39         : 40;
        uint64_t csize                 : 13; /**< [ 52: 40](RO) Read-only TIM_RING(0..63)_CTL2[CSIZE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_ctl2_s cn; */
};
typedef union bdk_tim_vringx_ctl2 bdk_tim_vringx_ctl2_t;

static inline uint64_t BDK_TIM_VRINGX_CTL2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_CTL2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000060ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_CTL2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_CTL2(a) bdk_tim_vringx_ctl2_t
#define bustype_BDK_TIM_VRINGX_CTL2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_CTL2(a) "TIM_VRINGX_CTL2"
#define device_bar_BDK_TIM_VRINGX_CTL2(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_CTL2(a) (a)
#define arguments_BDK_TIM_VRINGX_CTL2(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_fr_rn_cycles
 *
 * TIM Ring Free Running Cycle Count Register
 * This register is a read-only copy of TIM_FR_RN_CYCLES.
 */
union bdk_tim_vringx_fr_rn_cycles
{
    uint64_t u;
    struct bdk_tim_vringx_fr_rn_cycles_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_FR_RN_CYCLES[COUNT]. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_FR_RN_CYCLES[COUNT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_fr_rn_cycles_s cn; */
};
typedef union bdk_tim_vringx_fr_rn_cycles bdk_tim_vringx_fr_rn_cycles_t;

static inline uint64_t BDK_TIM_VRINGX_FR_RN_CYCLES(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_FR_RN_CYCLES(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000020ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_FR_RN_CYCLES", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_FR_RN_CYCLES(a) bdk_tim_vringx_fr_rn_cycles_t
#define bustype_BDK_TIM_VRINGX_FR_RN_CYCLES(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_FR_RN_CYCLES(a) "TIM_VRINGX_FR_RN_CYCLES"
#define device_bar_BDK_TIM_VRINGX_FR_RN_CYCLES(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_FR_RN_CYCLES(a) (a)
#define arguments_BDK_TIM_VRINGX_FR_RN_CYCLES(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_fr_rn_gpios
 *
 * TIM Ring Free Running GPIO Count Register
 * This register is a read-only copy of TIM_FR_RN_GPIOS.
 */
union bdk_tim_vringx_fr_rn_gpios
{
    uint64_t u;
    struct bdk_tim_vringx_fr_rn_gpios_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_FR_RN_GPIOS[COUNT]. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_FR_RN_GPIOS[COUNT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_fr_rn_gpios_s cn; */
};
typedef union bdk_tim_vringx_fr_rn_gpios bdk_tim_vringx_fr_rn_gpios_t;

static inline uint64_t BDK_TIM_VRINGX_FR_RN_GPIOS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_FR_RN_GPIOS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000028ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_FR_RN_GPIOS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_FR_RN_GPIOS(a) bdk_tim_vringx_fr_rn_gpios_t
#define bustype_BDK_TIM_VRINGX_FR_RN_GPIOS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_FR_RN_GPIOS(a) "TIM_VRINGX_FR_RN_GPIOS"
#define device_bar_BDK_TIM_VRINGX_FR_RN_GPIOS(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_FR_RN_GPIOS(a) (a)
#define arguments_BDK_TIM_VRINGX_FR_RN_GPIOS(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_fr_rn_gti
 *
 * TIM Ring Free Running System Clock Count Register
 * This register is a read-only copy of TIM_FR_RN_GTI.
 */
union bdk_tim_vringx_fr_rn_gti
{
    uint64_t u;
    struct bdk_tim_vringx_fr_rn_gti_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_FR_RN_GTI[COUNT]. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_FR_RN_GTI[COUNT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_fr_rn_gti_s cn; */
};
typedef union bdk_tim_vringx_fr_rn_gti bdk_tim_vringx_fr_rn_gti_t;

static inline uint64_t BDK_TIM_VRINGX_FR_RN_GTI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_FR_RN_GTI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000030ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_FR_RN_GTI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_FR_RN_GTI(a) bdk_tim_vringx_fr_rn_gti_t
#define bustype_BDK_TIM_VRINGX_FR_RN_GTI(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_FR_RN_GTI(a) "TIM_VRINGX_FR_RN_GTI"
#define device_bar_BDK_TIM_VRINGX_FR_RN_GTI(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_FR_RN_GTI(a) (a)
#define arguments_BDK_TIM_VRINGX_FR_RN_GTI(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_fr_rn_ptp
 *
 * TIM Ring Free Running PTP Count Register
 * This register is a read-only copy of TIM_FR_RN_PTP.
 */
union bdk_tim_vringx_fr_rn_ptp
{
    uint64_t u;
    struct bdk_tim_vringx_fr_rn_ptp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_FR_RN_PTP[COUNT]. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Read-only TIM_FR_RN_PTP[COUNT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_fr_rn_ptp_s cn; */
};
typedef union bdk_tim_vringx_fr_rn_ptp bdk_tim_vringx_fr_rn_ptp_t;

static inline uint64_t BDK_TIM_VRINGX_FR_RN_PTP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_FR_RN_PTP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000038ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_FR_RN_PTP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_FR_RN_PTP(a) bdk_tim_vringx_fr_rn_ptp_t
#define bustype_BDK_TIM_VRINGX_FR_RN_PTP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_FR_RN_PTP(a) "TIM_VRINGX_FR_RN_PTP"
#define device_bar_BDK_TIM_VRINGX_FR_RN_PTP(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_FR_RN_PTP(a) (a)
#define arguments_BDK_TIM_VRINGX_FR_RN_PTP(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_late
 *
 * TIM Ring Late Register
 */
union bdk_tim_vringx_late
{
    uint64_t u;
    struct bdk_tim_vringx_late_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t count                 : 20; /**< [ 19:  0](RO/H) Indicates how many buckets are late ([COUNT] \> 1) to be processed in this ring.
                                                                 When the associated ring is late, TIM will make a best effort to catch up and
                                                                 processes all buckets that are late, back-to-back. Incremented by TIM for every
                                                                 ring expiration and decremented when a ring's bucket is serviced.
                                                                 When (TIM_VRING()_LATE[COUNT] \>= TIM_RING()_CTL1[BSIZE+1]), or
                                                                 (TIM_VRING()_LATE[COUNT] 0xFFFFF, and to be incremented),
                                                                 hardware will set TIM_VRING()_LATE[COUNT] = 1.
                                                                 Hardware will set TIM_VRING()_LATE[COUNT] = 0 when TIM_RING()_CTL1[ENA]
                                                                 transitions from zero to one or from one to zero. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 20; /**< [ 19:  0](RO/H) Indicates how many buckets are late ([COUNT] \> 1) to be processed in this ring.
                                                                 When the associated ring is late, TIM will make a best effort to catch up and
                                                                 processes all buckets that are late, back-to-back. Incremented by TIM for every
                                                                 ring expiration and decremented when a ring's bucket is serviced.
                                                                 When (TIM_VRING()_LATE[COUNT] \>= TIM_RING()_CTL1[BSIZE+1]), or
                                                                 (TIM_VRING()_LATE[COUNT] 0xFFFFF, and to be incremented),
                                                                 hardware will set TIM_VRING()_LATE[COUNT] = 1.
                                                                 Hardware will set TIM_VRING()_LATE[COUNT] = 0 when TIM_RING()_CTL1[ENA]
                                                                 transitions from zero to one or from one to zero. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_late_s cn; */
};
typedef union bdk_tim_vringx_late bdk_tim_vringx_late_t;

static inline uint64_t BDK_TIM_VRINGX_LATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_LATE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858000002e00ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_LATE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_LATE(a) bdk_tim_vringx_late_t
#define bustype_BDK_TIM_VRINGX_LATE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_LATE(a) "TIM_VRINGX_LATE"
#define device_bar_BDK_TIM_VRINGX_LATE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_TIM_VRINGX_LATE(a) (a)
#define arguments_BDK_TIM_VRINGX_LATE(a) (a),-1,-1,-1

/**
 * Register (NCB) tim_vring#_rel
 *
 * TIM Ring Relative Position Register
 * Current positions and status of the TIM walker in both time and ring position,
 * for easy synchronization with software.
 *
 * Internal:
 * For VM-safety this register contains only read-only fields.
 */
union bdk_tim_vringx_rel
{
    uint64_t u;
    struct bdk_tim_vringx_rel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cur_bucket            : 20; /**< [ 63: 44](RO/H) Current bucket. Indicates the ring's current bucket. See TIM_RING()_CTL1[BUCKET]. */
        uint64_t late_count_msbs       : 1;  /**< [ 43: 43](RO/H) Set when TIM_VRING()_LATE[COUNT]\<19:11\> != 0x0.
                                                                 Software should read TIM_VRING()_LATE[COUNT] to find how many buckets a ring is late. */
        uint64_t late_count            : 11; /**< [ 42: 32](RO/H) Identical to TIM_VRING(0..63)_LATE[COUNT]\<10:0\>. If [LATE_COUNT_MSBS] is zero,
                                                                 it indicates how many bucket are late to be scheduled per ring. See the HRM body
                                                                 text with regards to how software should consider TIM_VRING()_LATE[COUNT] when
                                                                 inserting an entry. */
        uint64_t timercount            : 32; /**< [ 31:  0](RO/H) Timer count indicates how many timer ticks are left until the interval
                                                                 expiration, calculated as TIM_RING()_CTL0[EXPIRE_OFFSET] minus current time
                                                                 (TIM_FR_RN_CYCLES, TIM_FR_RN_GPIOS, TIM_FR_RN_GTI, or TIM_FR_RN_PTP).

                                                                 Once TIM_RING()_CTL1[ENA] = 1, [TIMERCOUNT] will be observed to count down timer
                                                                 ticks. When [TIMERCOUNT] reaches 0x0, the ring's interval expired and the
                                                                 hardware forces a bucket traversal (and increments [LATE_COUNT] MSBs).

                                                                 Typical initialization value should be interval/constant; Cavium recommends that
                                                                 the constant be unique per ring. This creates an offset between the rings.
                                                                 [TIMERCOUNT] becomes and remains unpredictable whenever TIM_RING()_CTL1[ENA] = 0
                                                                 or TIM_RING()_CTL1[CLK_SRC] changes. It is software's responsibility to set
                                                                 [TIMERCOUNT] before TIM_RING()_CTL1[ENA] transitions from zero to one. */
#else /* Word 0 - Little Endian */
        uint64_t timercount            : 32; /**< [ 31:  0](RO/H) Timer count indicates how many timer ticks are left until the interval
                                                                 expiration, calculated as TIM_RING()_CTL0[EXPIRE_OFFSET] minus current time
                                                                 (TIM_FR_RN_CYCLES, TIM_FR_RN_GPIOS, TIM_FR_RN_GTI, or TIM_FR_RN_PTP).

                                                                 Once TIM_RING()_CTL1[ENA] = 1, [TIMERCOUNT] will be observed to count down timer
                                                                 ticks. When [TIMERCOUNT] reaches 0x0, the ring's interval expired and the
                                                                 hardware forces a bucket traversal (and increments [LATE_COUNT] MSBs).

                                                                 Typical initialization value should be interval/constant; Cavium recommends that
                                                                 the constant be unique per ring. This creates an offset between the rings.
                                                                 [TIMERCOUNT] becomes and remains unpredictable whenever TIM_RING()_CTL1[ENA] = 0
                                                                 or TIM_RING()_CTL1[CLK_SRC] changes. It is software's responsibility to set
                                                                 [TIMERCOUNT] before TIM_RING()_CTL1[ENA] transitions from zero to one. */
        uint64_t late_count            : 11; /**< [ 42: 32](RO/H) Identical to TIM_VRING(0..63)_LATE[COUNT]\<10:0\>. If [LATE_COUNT_MSBS] is zero,
                                                                 it indicates how many bucket are late to be scheduled per ring. See the HRM body
                                                                 text with regards to how software should consider TIM_VRING()_LATE[COUNT] when
                                                                 inserting an entry. */
        uint64_t late_count_msbs       : 1;  /**< [ 43: 43](RO/H) Set when TIM_VRING()_LATE[COUNT]\<19:11\> != 0x0.
                                                                 Software should read TIM_VRING()_LATE[COUNT] to find how many buckets a ring is late. */
        uint64_t cur_bucket            : 20; /**< [ 63: 44](RO/H) Current bucket. Indicates the ring's current bucket. See TIM_RING()_CTL1[BUCKET]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_tim_vringx_rel_s cn; */
};
typedef union bdk_tim_vringx_rel bdk_tim_vringx_rel_t;

static inline uint64_t BDK_TIM_VRINGX_REL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_TIM_VRINGX_REL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=63))
        return 0x858010000110ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("TIM_VRINGX_REL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_TIM_VRINGX_REL(a) bdk_tim_vringx_rel_t
#define bustype_BDK_TIM_VRINGX_REL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_TIM_VRINGX_REL(a) "TIM_VRINGX_REL"
#define device_bar_BDK_TIM_VRINGX_REL(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_TIM_VRINGX_REL(a) (a)
#define arguments_BDK_TIM_VRINGX_REL(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_TIM_H__ */
