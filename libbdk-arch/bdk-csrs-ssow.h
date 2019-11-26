#ifndef __BDK_CSRS_SSOW_H__
#define __BDK_CSRS_SSOW_H__
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
 * OcteonTX SSOW.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration ssow_bar_e
 *
 * SSO Work Slot Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_SSOW_BAR_E_SSOW_PF_BAR0 (0x861000000000ll)
#define BDK_SSOW_BAR_E_SSOW_PF_BAR0_SIZE 0x100000ull
#define BDK_SSOW_BAR_E_SSOW_VFX_BAR0(a) (0x861800000000ll + 0x100000ll * (a))
#define BDK_SSOW_BAR_E_SSOW_VFX_BAR0_SIZE 0x100000ull

/**
 * Enumeration ssow_lf_int_vec_e
 *
 * SSOW MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_SSOW_LF_INT_VEC_E_IOP (0)

/**
 * Structure ssow_clr_nsched_addr_s
 *
 * SSO Clear Noschedule Address Structure
 * This structure determines the address offset for SSOW_VHWS()_OP_CLR_NSCHED.
 */
union bdk_ssow_clr_nsched_addr_s
{
    uint32_t u;
    struct bdk_ssow_clr_nsched_addr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t index                 : 12; /**< [ 15:  4] Index to clear. Bits \<15:14\> are always zero. */
        uint32_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_3          : 4;
        uint32_t index                 : 12; /**< [ 15:  4] Index to clear. Bits \<15:14\> are always zero. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_clr_nsched_addr_s_s cn; */
};

/**
 * Structure ssow_get_work_addr_s
 *
 * SSO Get-Work Address Structure
 * This structure determines the address offset for SSOW_VHWS()_OP_GET_WORK0 and
 * SSOW_VHWS()_OP_GET_WORK1.
 */
union bdk_ssow_get_work_addr_s
{
    uint32_t u;
    struct bdk_ssow_get_work_addr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_19_31        : 13;
        uint32_t indexed               : 1;  /**< [ 18: 18] Indexed get work. If set, indexed get work, specified in [INDEX_GGRP_MASK]. */
        uint32_t grouped               : 1;  /**< [ 17: 17] Get from a specific group number, specified in [INDEX_GGRP_MASK]. */
        uint32_t waitw                 : 1;  /**< [ 16: 16] If set, wait for work; don't return load result until work is available or timeout. Must
                                                                 be zero if [INDEXED] is set. */
        uint32_t index_ggrp_mask       : 12; /**< [ 15:  4] Index or guest-group or masks.

                                                                 * If [INDEXED] and [GROUPED]=0, \<5:4\> indicates how to use the mask sets
                                                                 in SSO_HWS()_S()_GRPMSK() (\<15:6\> are ignored):
                                                                 0x0 = use mask set 0 as high priority, and mask set 1 as lower priority if no groups
                                                                 satisfy mask set 0.
                                                                 0x1 = use mask set 0.
                                                                 0x2 = use mask set 1.
                                                                 0x3 = reserved.

                                                                 * If [INDEXED] = 1, \<15:4\> provides the index to get work from.

                                                                 * If [GROUPED] = 1, \<13:4\> provides the guest-group number.

                                                                  o If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                  o else if SSO_HWS()_GMCTL[GMID] = 0x1, then GGRP is the hardware-group
                                                                    number.

                                                                  o else the GGRP is translated to a hardware-group as described in SSO_PF_MAP().
                                                                    If no match or a multi-match is found SSO_ERR2[WS_UNMAP] or
                                                                    SSO_ERR2[AW_MULTI] is set respectively and no-work is returned. */
        uint32_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_3          : 4;
        uint32_t index_ggrp_mask       : 12; /**< [ 15:  4] Index or guest-group or masks.

                                                                 * If [INDEXED] and [GROUPED]=0, \<5:4\> indicates how to use the mask sets
                                                                 in SSO_HWS()_S()_GRPMSK() (\<15:6\> are ignored):
                                                                 0x0 = use mask set 0 as high priority, and mask set 1 as lower priority if no groups
                                                                 satisfy mask set 0.
                                                                 0x1 = use mask set 0.
                                                                 0x2 = use mask set 1.
                                                                 0x3 = reserved.

                                                                 * If [INDEXED] = 1, \<15:4\> provides the index to get work from.

                                                                 * If [GROUPED] = 1, \<13:4\> provides the guest-group number.

                                                                  o If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                  o else if SSO_HWS()_GMCTL[GMID] = 0x1, then GGRP is the hardware-group
                                                                    number.

                                                                  o else the GGRP is translated to a hardware-group as described in SSO_PF_MAP().
                                                                    If no match or a multi-match is found SSO_ERR2[WS_UNMAP] or
                                                                    SSO_ERR2[AW_MULTI] is set respectively and no-work is returned. */
        uint32_t waitw                 : 1;  /**< [ 16: 16] If set, wait for work; don't return load result until work is available or timeout. Must
                                                                 be zero if [INDEXED] is set. */
        uint32_t grouped               : 1;  /**< [ 17: 17] Get from a specific group number, specified in [INDEX_GGRP_MASK]. */
        uint32_t indexed               : 1;  /**< [ 18: 18] Indexed get work. If set, indexed get work, specified in [INDEX_GGRP_MASK]. */
        uint32_t reserved_19_31        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_get_work_addr_s_s cn; */
};

/**
 * Register (RVU_PF_BAR0) ssow_af_bar2_alias#
 *
 * INTERNAL: SSO Work Slot Admin Function  BAR2 Alias Registers
 *
 * These registers alias to the SSO Workslot BAR2 registers for the PF and
 * function selected by SSOW_AF_BAR2_SEL[PF_FUNC].
 *
 * Internal:
 * Not implemented. Placeholder for bug33464.
 */
union bdk_ssow_af_bar2_aliasx
{
    uint64_t u;
    struct bdk_ssow_af_bar2_aliasx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Aliased register data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Aliased register data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_af_bar2_aliasx_s cn; */
};
typedef union bdk_ssow_af_bar2_aliasx bdk_ssow_af_bar2_aliasx_t;

static inline uint64_t BDK_SSOW_AF_BAR2_ALIASX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_AF_BAR2_ALIASX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=131071))
        return 0x840089100000ll + 8ll * ((a) & 0x1ffff);
    __bdk_csr_fatal("SSOW_AF_BAR2_ALIASX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_AF_BAR2_ALIASX(a) bdk_ssow_af_bar2_aliasx_t
#define bustype_BDK_SSOW_AF_BAR2_ALIASX(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSOW_AF_BAR2_ALIASX(a) "SSOW_AF_BAR2_ALIASX"
#define device_bar_BDK_SSOW_AF_BAR2_ALIASX(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSOW_AF_BAR2_ALIASX(a) (a)
#define arguments_BDK_SSOW_AF_BAR2_ALIASX(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ssow_af_bar2_sel
 *
 * INTERNAL: SSO Work Slot Admin Function BAR2 Select Register
 *
 * This register configures BAR2 accesses from the SSOW_AF_BAR2_ALIAS() registers in BAR0.
 * Internal:
 * Not implemented. Placeholder for bug33464.
 */
union bdk_ssow_af_bar2_sel
{
    uint64_t u;
    struct bdk_ssow_af_bar2_sel_s
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
    /* struct bdk_ssow_af_bar2_sel_s cn; */
};
typedef union bdk_ssow_af_bar2_sel bdk_ssow_af_bar2_sel_t;

#define BDK_SSOW_AF_BAR2_SEL BDK_SSOW_AF_BAR2_SEL_FUNC()
static inline uint64_t BDK_SSOW_AF_BAR2_SEL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_AF_BAR2_SEL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840089000000ll;
    __bdk_csr_fatal("SSOW_AF_BAR2_SEL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_AF_BAR2_SEL bdk_ssow_af_bar2_sel_t
#define bustype_BDK_SSOW_AF_BAR2_SEL BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSOW_AF_BAR2_SEL "SSOW_AF_BAR2_SEL"
#define device_bar_BDK_SSOW_AF_BAR2_SEL 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSOW_AF_BAR2_SEL 0
#define arguments_BDK_SSOW_AF_BAR2_SEL -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ssow_af_lf_hws_rst
 *
 * SSOW AF LF Reset Register
 */
union bdk_ssow_af_lf_hws_rst
{
    uint64_t u;
    struct bdk_ssow_af_lf_hws_rst_s
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
    /* struct bdk_ssow_af_lf_hws_rst_s cn; */
};
typedef union bdk_ssow_af_lf_hws_rst bdk_ssow_af_lf_hws_rst_t;

#define BDK_SSOW_AF_LF_HWS_RST BDK_SSOW_AF_LF_HWS_RST_FUNC()
static inline uint64_t BDK_SSOW_AF_LF_HWS_RST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_AF_LF_HWS_RST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840080000030ll;
    __bdk_csr_fatal("SSOW_AF_LF_HWS_RST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_AF_LF_HWS_RST bdk_ssow_af_lf_hws_rst_t
#define bustype_BDK_SSOW_AF_LF_HWS_RST BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSOW_AF_LF_HWS_RST "SSOW_AF_LF_HWS_RST"
#define device_bar_BDK_SSOW_AF_LF_HWS_RST 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSOW_AF_LF_HWS_RST 0
#define arguments_BDK_SSOW_AF_LF_HWS_RST -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ssow_af_rvu_lf_hws_cfg_debug
 *
 * SSO WS Privileged LF Configuration Debug Registers
 */
union bdk_ssow_af_rvu_lf_hws_cfg_debug
{
    uint64_t u;
    struct bdk_ssow_af_rvu_lf_hws_cfg_debug_s
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
    /* struct bdk_ssow_af_rvu_lf_hws_cfg_debug_s cn; */
};
typedef union bdk_ssow_af_rvu_lf_hws_cfg_debug bdk_ssow_af_rvu_lf_hws_cfg_debug_t;

#define BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG_FUNC()
static inline uint64_t BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840080000010ll;
    __bdk_csr_fatal("SSOW_AF_RVU_LF_HWS_CFG_DEBUG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG bdk_ssow_af_rvu_lf_hws_cfg_debug_t
#define bustype_BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG "SSOW_AF_RVU_LF_HWS_CFG_DEBUG"
#define device_bar_BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG 0
#define arguments_BDK_SSOW_AF_RVU_LF_HWS_CFG_DEBUG -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ssow_af_scratch_aw
 *
 * SSOW Scratch Register
 */
union bdk_ssow_af_scratch_aw
{
    uint64_t u;
    struct bdk_ssow_af_scratch_aw_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) Scratch register for software use; no hardware impact. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) Scratch register for software use; no hardware impact. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_af_scratch_aw_s cn; */
};
typedef union bdk_ssow_af_scratch_aw bdk_ssow_af_scratch_aw_t;

#define BDK_SSOW_AF_SCRATCH_AW BDK_SSOW_AF_SCRATCH_AW_FUNC()
static inline uint64_t BDK_SSOW_AF_SCRATCH_AW_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_AF_SCRATCH_AW_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840080300000ll;
    __bdk_csr_fatal("SSOW_AF_SCRATCH_AW", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_AF_SCRATCH_AW bdk_ssow_af_scratch_aw_t
#define bustype_BDK_SSOW_AF_SCRATCH_AW BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSOW_AF_SCRATCH_AW "SSOW_AF_SCRATCH_AW"
#define device_bar_BDK_SSOW_AF_SCRATCH_AW 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSOW_AF_SCRATCH_AW 0
#define arguments_BDK_SSOW_AF_SCRATCH_AW -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ssow_af_scratch_gw
 *
 * SSOW Scratch Register
 */
union bdk_ssow_af_scratch_gw
{
    uint64_t u;
    struct bdk_ssow_af_scratch_gw_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) Scratch register for software use; no hardware impact. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) Scratch register for software use; no hardware impact. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_af_scratch_gw_s cn; */
};
typedef union bdk_ssow_af_scratch_gw bdk_ssow_af_scratch_gw_t;

#define BDK_SSOW_AF_SCRATCH_GW BDK_SSOW_AF_SCRATCH_GW_FUNC()
static inline uint64_t BDK_SSOW_AF_SCRATCH_GW_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_AF_SCRATCH_GW_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840080200000ll;
    __bdk_csr_fatal("SSOW_AF_SCRATCH_GW", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_AF_SCRATCH_GW bdk_ssow_af_scratch_gw_t
#define bustype_BDK_SSOW_AF_SCRATCH_GW BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSOW_AF_SCRATCH_GW "SSOW_AF_SCRATCH_GW"
#define device_bar_BDK_SSOW_AF_SCRATCH_GW 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSOW_AF_SCRATCH_GW 0
#define arguments_BDK_SSOW_AF_SCRATCH_GW -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ssow_af_scratch_ws
 *
 * SSOW Scratch Register
 */
union bdk_ssow_af_scratch_ws
{
    uint64_t u;
    struct bdk_ssow_af_scratch_ws_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) Scratch register for software use; no hardware impact. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) Scratch register for software use; no hardware impact. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_af_scratch_ws_s cn; */
};
typedef union bdk_ssow_af_scratch_ws bdk_ssow_af_scratch_ws_t;

#define BDK_SSOW_AF_SCRATCH_WS BDK_SSOW_AF_SCRATCH_WS_FUNC()
static inline uint64_t BDK_SSOW_AF_SCRATCH_WS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_AF_SCRATCH_WS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840080100000ll;
    __bdk_csr_fatal("SSOW_AF_SCRATCH_WS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_AF_SCRATCH_WS bdk_ssow_af_scratch_ws_t
#define bustype_BDK_SSOW_AF_SCRATCH_WS BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSOW_AF_SCRATCH_WS "SSOW_AF_SCRATCH_WS"
#define device_bar_BDK_SSOW_AF_SCRATCH_WS 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSOW_AF_SCRATCH_WS 0
#define arguments_BDK_SSOW_AF_SCRATCH_WS -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_grpmsk_chg
 *
 * SSO Workslot LF Group-Mask Change Registers
 * This register changes which group or groups a GWS belongs to.  It
 * can change membership for up to four groups.
 */
union bdk_ssow_lf_gws_grpmsk_chg
{
    uint64_t u;
    struct bdk_ssow_lf_gws_grpmsk_chg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t set3                  : 2;  /**< [ 63: 62](WO) Set/clear membership.
                                                                 0x0 = Disable this GWS's membership in the guest group [GGRP3].
                                                                 0x1 = Enable this GWS's membership in the guest group [GGRP3].
                                                                 0x2 = Do not set or clear any bits for [GGRP3].
                                                                 0x3 = Reserved.

                                                                 See [SET0] for more details. */
        uint64_t reserved_61           : 1;
        uint64_t mskset3               : 1;  /**< [ 60: 60](WO) Set number to enable/disable membership in for [GGRP3]. */
        uint64_t reserved_58_59        : 2;
        uint64_t ggrp3                 : 10; /**< [ 57: 48](WO) Second guest group number to enable/disable membership in.
                                                                 See [GGRP0]. */
        uint64_t set2                  : 2;  /**< [ 47: 46](WO) Set/clear membership.
                                                                 0x0 = Disable this GWS's membership in the guest group [GGRP2].
                                                                 0x1 = Enable this GWS's membership in the guest group [GGRP2].
                                                                 0x2 = Do not set or clear any bits for [GGRP2].
                                                                 0x3 = Reserved.

                                                                 See [SET0] for more details. */
        uint64_t reserved_45           : 1;
        uint64_t mskset2               : 1;  /**< [ 44: 44](WO) Set number to enable/disable membership in for [GGRP2]. */
        uint64_t reserved_42_43        : 2;
        uint64_t ggrp2                 : 10; /**< [ 41: 32](WO) Second guest group number to enable/disable membership in.
                                                                 See [GGRP0]. */
        uint64_t set1                  : 2;  /**< [ 31: 30](WO) Set/clear membership.
                                                                 0x0 = Disable this GWS's membership in the guest group [GGRP1].
                                                                 0x1 = Enable this GWS's membership in the guest group [GGRP1].
                                                                 0x2 = Do not set or clear any bits for [GGRP1].
                                                                 0x3 = Reserved.

                                                                 See [SET0] for more details. */
        uint64_t reserved_29           : 1;
        uint64_t mskset1               : 1;  /**< [ 28: 28](WO) Set number to enable/disable membership in for [GGRP1]. */
        uint64_t reserved_26_27        : 2;
        uint64_t ggrp1                 : 10; /**< [ 25: 16](WO) Second guest group number to enable/disable membership in.
                                                                 See [GGRP0]. */
        uint64_t set0                  : 2;  /**< [ 15: 14](WO) Set/clear membership.

                                                                 0x0 = Disable this GWS's membership in the guest group [GGRP0].  This
                                                                 clears the corresponding bit in
                                                                 SSO_AF_HWS(\<hws\>)_S(\<s\>)_GRPMSK(\<hwgrp\>), where \<hws\> is translated
                                                                 from PF,Func,Slot in the register address, \<s\> is from [MSKSET0], and
                                                                 \<hwgrp\> is a translated [GGRP0] (see [GGRP0] below).

                                                                 0x1 = Enable this GWS's membership in the guest group [GGRP0].  This sets
                                                                 the corresponding bit in SSO_AF_HWS(\<hws\>)_S(\<s\>)_GRPMSK(\<hwgrp\>).

                                                                 0x2 = Do not set or clear any bits for [GGRP0].

                                                                 0x3 = Reserved. */
        uint64_t reserved_13           : 1;
        uint64_t mskset0               : 1;  /**< [ 12: 12](WO) Set number to enable/diable membership in for [GGRP0]. */
        uint64_t reserved_10_11        : 2;
        uint64_t ggrp0                 : 10; /**< [  9:  0](WO) Guest group number 0 to enable/disable membership in.

                                                                 [GGRP0] is in the context of the PF_FUNC determined by this register's
                                                                 address and translated to a HWGRP based on SSO_PRIV_LF()_HWGRP_CFG. Each
                                                                 write to this register can require up to 4 translations.  Any translation
                                                                 that fails will set SSO_AF_ERR2[WS_GRP_UNMAP] or
                                                                 SSO_AF_ERR2[WS_GRP_MULTI] if the SETn field is 0x0 or 0x1 and will not
                                                                 modify any bits in SSO_AF_HWS()_S()_GRPMSK().  An error in one of the
                                                                 4 groups does not affect the others. */
#else /* Word 0 - Little Endian */
        uint64_t ggrp0                 : 10; /**< [  9:  0](WO) Guest group number 0 to enable/disable membership in.

                                                                 [GGRP0] is in the context of the PF_FUNC determined by this register's
                                                                 address and translated to a HWGRP based on SSO_PRIV_LF()_HWGRP_CFG. Each
                                                                 write to this register can require up to 4 translations.  Any translation
                                                                 that fails will set SSO_AF_ERR2[WS_GRP_UNMAP] or
                                                                 SSO_AF_ERR2[WS_GRP_MULTI] if the SETn field is 0x0 or 0x1 and will not
                                                                 modify any bits in SSO_AF_HWS()_S()_GRPMSK().  An error in one of the
                                                                 4 groups does not affect the others. */
        uint64_t reserved_10_11        : 2;
        uint64_t mskset0               : 1;  /**< [ 12: 12](WO) Set number to enable/diable membership in for [GGRP0]. */
        uint64_t reserved_13           : 1;
        uint64_t set0                  : 2;  /**< [ 15: 14](WO) Set/clear membership.

                                                                 0x0 = Disable this GWS's membership in the guest group [GGRP0].  This
                                                                 clears the corresponding bit in
                                                                 SSO_AF_HWS(\<hws\>)_S(\<s\>)_GRPMSK(\<hwgrp\>), where \<hws\> is translated
                                                                 from PF,Func,Slot in the register address, \<s\> is from [MSKSET0], and
                                                                 \<hwgrp\> is a translated [GGRP0] (see [GGRP0] below).

                                                                 0x1 = Enable this GWS's membership in the guest group [GGRP0].  This sets
                                                                 the corresponding bit in SSO_AF_HWS(\<hws\>)_S(\<s\>)_GRPMSK(\<hwgrp\>).

                                                                 0x2 = Do not set or clear any bits for [GGRP0].

                                                                 0x3 = Reserved. */
        uint64_t ggrp1                 : 10; /**< [ 25: 16](WO) Second guest group number to enable/disable membership in.
                                                                 See [GGRP0]. */
        uint64_t reserved_26_27        : 2;
        uint64_t mskset1               : 1;  /**< [ 28: 28](WO) Set number to enable/disable membership in for [GGRP1]. */
        uint64_t reserved_29           : 1;
        uint64_t set1                  : 2;  /**< [ 31: 30](WO) Set/clear membership.
                                                                 0x0 = Disable this GWS's membership in the guest group [GGRP1].
                                                                 0x1 = Enable this GWS's membership in the guest group [GGRP1].
                                                                 0x2 = Do not set or clear any bits for [GGRP1].
                                                                 0x3 = Reserved.

                                                                 See [SET0] for more details. */
        uint64_t ggrp2                 : 10; /**< [ 41: 32](WO) Second guest group number to enable/disable membership in.
                                                                 See [GGRP0]. */
        uint64_t reserved_42_43        : 2;
        uint64_t mskset2               : 1;  /**< [ 44: 44](WO) Set number to enable/disable membership in for [GGRP2]. */
        uint64_t reserved_45           : 1;
        uint64_t set2                  : 2;  /**< [ 47: 46](WO) Set/clear membership.
                                                                 0x0 = Disable this GWS's membership in the guest group [GGRP2].
                                                                 0x1 = Enable this GWS's membership in the guest group [GGRP2].
                                                                 0x2 = Do not set or clear any bits for [GGRP2].
                                                                 0x3 = Reserved.

                                                                 See [SET0] for more details. */
        uint64_t ggrp3                 : 10; /**< [ 57: 48](WO) Second guest group number to enable/disable membership in.
                                                                 See [GGRP0]. */
        uint64_t reserved_58_59        : 2;
        uint64_t mskset3               : 1;  /**< [ 60: 60](WO) Set number to enable/disable membership in for [GGRP3]. */
        uint64_t reserved_61           : 1;
        uint64_t set3                  : 2;  /**< [ 63: 62](WO) Set/clear membership.
                                                                 0x0 = Disable this GWS's membership in the guest group [GGRP3].
                                                                 0x1 = Enable this GWS's membership in the guest group [GGRP3].
                                                                 0x2 = Do not set or clear any bits for [GGRP3].
                                                                 0x3 = Reserved.

                                                                 See [SET0] for more details. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_grpmsk_chg_s cn; */
};
typedef union bdk_ssow_lf_gws_grpmsk_chg bdk_ssow_lf_gws_grpmsk_chg_t;

#define BDK_SSOW_LF_GWS_GRPMSK_CHG BDK_SSOW_LF_GWS_GRPMSK_CHG_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_GRPMSK_CHG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_GRPMSK_CHG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800080ll;
    __bdk_csr_fatal("SSOW_LF_GWS_GRPMSK_CHG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_GRPMSK_CHG bdk_ssow_lf_gws_grpmsk_chg_t
#define bustype_BDK_SSOW_LF_GWS_GRPMSK_CHG BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_GRPMSK_CHG "SSOW_LF_GWS_GRPMSK_CHG"
#define device_bar_BDK_SSOW_LF_GWS_GRPMSK_CHG 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_GRPMSK_CHG 0
#define arguments_BDK_SSOW_LF_GWS_GRPMSK_CHG -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_int
 *
 * SSO Workslot LF Interrupt Register
 * Contains the per guest group interrupts and is used to clear these
 * interrupts.
 */
union bdk_ssow_lf_gws_int
{
    uint64_t u;
    struct bdk_ssow_lf_gws_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t swtag_dis             : 1;  /**< [ 11: 11](R/W1C/H) Received UPD_WQP_GRP/SWTAG_FULL/SWTAG_DESCHED when SSO_AF_HWGRP()_AW_CFG[SWTAG_DIS] was set. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1C/H) Received illegal load for workslot op. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1C/H) Received illegal store for workslot op. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1C/H) Received UPD_WQP_GRP referencing a different tag space than currently held by workslot. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1C/H) Received UPD_WQP_GRP/SWTAG_FULL/CLR_NSCHED with WQP=0. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with CLR_NSCHED
                                                                 pending. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1C/H) Received CLR_NSCHED or indexed GET_WORK from workslot with SWTAG_DESCHED/DESCH pending. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with ALLOC_WE pending. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with GET_WORK pending. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1C/H) Received SWTAG_NORM/SWTAG_FULL/SWTAG_DESCHED with tag specified as EMPTY. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/GET_WORK/ALLOC_WE/CLR_NSCHED
                                                                 from workslot with pending tag switch to ORDERED or ATOMIC. */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL/SWTAG_FLUSH/SWTAG_DESCHED/DESCH/UPD_WQP_GRP from work
                                                                 slot in EMPTY state. */
#else /* Word 0 - Little Endian */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL/SWTAG_FLUSH/SWTAG_DESCHED/DESCH/UPD_WQP_GRP from work
                                                                 slot in EMPTY state. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/GET_WORK/ALLOC_WE/CLR_NSCHED
                                                                 from workslot with pending tag switch to ORDERED or ATOMIC. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1C/H) Received SWTAG_NORM/SWTAG_FULL/SWTAG_DESCHED with tag specified as EMPTY. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with GET_WORK pending. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with ALLOC_WE pending. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1C/H) Received CLR_NSCHED or indexed GET_WORK from workslot with SWTAG_DESCHED/DESCH pending. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with CLR_NSCHED
                                                                 pending. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1C/H) Received UPD_WQP_GRP/SWTAG_FULL/CLR_NSCHED with WQP=0. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1C/H) Received UPD_WQP_GRP referencing a different tag space than currently held by workslot. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1C/H) Received illegal store for workslot op. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1C/H) Received illegal load for workslot op. */
        uint64_t swtag_dis             : 1;  /**< [ 11: 11](R/W1C/H) Received UPD_WQP_GRP/SWTAG_FULL/SWTAG_DESCHED when SSO_AF_HWGRP()_AW_CFG[SWTAG_DIS] was set. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_int_s cn9; */
    struct bdk_ssow_lf_gws_int_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1C/H) Received illegal load for workslot op. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1C/H) Received illegal store for workslot op. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1C/H) Received UPD_WQP_GRP referencing a different tag space than currently held by workslot. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1C/H) Received UPD_WQP_GRP/SWTAG_FULL/CLR_NSCHED with WQP=0. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with CLR_NSCHED
                                                                 pending. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1C/H) Received CLR_NSCHED or indexed GET_WORK from workslot with SWTAG_DESCHED/DESCH pending. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with ALLOC_WE pending. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with GET_WORK pending. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1C/H) Received SWTAG_NORM/SWTAG_FULL/SWTAG_DESCHED with tag specified as EMPTY. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/GET_WORK/ALLOC_WE/CLR_NSCHED
                                                                 from workslot with pending tag switch to ORDERED or ATOMIC. */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL/SWTAG_FLUSH/SWTAG_DESCHED/DESCH/UPD_WQP_GRP from work
                                                                 slot in EMPTY state. */
#else /* Word 0 - Little Endian */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL/SWTAG_FLUSH/SWTAG_DESCHED/DESCH/UPD_WQP_GRP from work
                                                                 slot in EMPTY state. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/GET_WORK/ALLOC_WE/CLR_NSCHED
                                                                 from workslot with pending tag switch to ORDERED or ATOMIC. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1C/H) Received SWTAG_NORM/SWTAG_FULL/SWTAG_DESCHED with tag specified as EMPTY. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with GET_WORK pending. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with ALLOC_WE pending. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1C/H) Received CLR_NSCHED or indexed GET_WORK from workslot with SWTAG_DESCHED/DESCH pending. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1C/H) Received SWTAG_NORM/SWTAG_UNTAG/SWTAG_FULL /SWTAG_FLUSH/SWTAG_DESCHED/DESCH
                                                                 /UPD_WQP_GRP/GET_WORK/ALLOC_WE/CLR_NSCHED from workslot with CLR_NSCHED
                                                                 pending. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1C/H) Received UPD_WQP_GRP/SWTAG_FULL/CLR_NSCHED with WQP=0. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1C/H) Received UPD_WQP_GRP referencing a different tag space than currently held by workslot. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1C/H) Received illegal store for workslot op. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1C/H) Received illegal load for workslot op. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn96xxp1;
    /* struct bdk_ssow_lf_gws_int_s cn96xxp3; */
    /* struct bdk_ssow_lf_gws_int_s cn98xx; */
    /* struct bdk_ssow_lf_gws_int_cn96xxp1 cnf95xx; */
    /* struct bdk_ssow_lf_gws_int_cn96xxp1 loki; */
};
typedef union bdk_ssow_lf_gws_int bdk_ssow_lf_gws_int_t;

#define BDK_SSOW_LF_GWS_INT BDK_SSOW_LF_GWS_INT_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800100ll;
    __bdk_csr_fatal("SSOW_LF_GWS_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_INT bdk_ssow_lf_gws_int_t
#define bustype_BDK_SSOW_LF_GWS_INT BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_INT "SSOW_LF_GWS_INT"
#define device_bar_BDK_SSOW_LF_GWS_INT 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_INT 0
#define arguments_BDK_SSOW_LF_GWS_INT -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_int_ena_w1c
 *
 * SSO Workslot LF Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_ssow_lf_gws_int_ena_w1c
{
    uint64_t u;
    struct bdk_ssow_lf_gws_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t swtag_dis             : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SWTAG_DIS]. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[WQP0]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[EMPTY_WS]. */
#else /* Word 0 - Little Endian */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[EMPTY_WS]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[WQP0]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t swtag_dis             : 1;  /**< [ 11: 11](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SWTAG_DIS]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_int_ena_w1c_s cn9; */
    struct bdk_ssow_lf_gws_int_ena_w1c_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[WQP0]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[EMPTY_WS]. */
#else /* Word 0 - Little Endian */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[EMPTY_WS]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[WQP0]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1C/H) Reads or clears enable for SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn96xxp1;
    /* struct bdk_ssow_lf_gws_int_ena_w1c_s cn96xxp3; */
    /* struct bdk_ssow_lf_gws_int_ena_w1c_s cn98xx; */
    /* struct bdk_ssow_lf_gws_int_ena_w1c_cn96xxp1 cnf95xx; */
    /* struct bdk_ssow_lf_gws_int_ena_w1c_cn96xxp1 loki; */
};
typedef union bdk_ssow_lf_gws_int_ena_w1c bdk_ssow_lf_gws_int_ena_w1c_t;

#define BDK_SSOW_LF_GWS_INT_ENA_W1C BDK_SSOW_LF_GWS_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800118ll;
    __bdk_csr_fatal("SSOW_LF_GWS_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_INT_ENA_W1C bdk_ssow_lf_gws_int_ena_w1c_t
#define bustype_BDK_SSOW_LF_GWS_INT_ENA_W1C BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_INT_ENA_W1C "SSOW_LF_GWS_INT_ENA_W1C"
#define device_bar_BDK_SSOW_LF_GWS_INT_ENA_W1C 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_INT_ENA_W1C 0
#define arguments_BDK_SSOW_LF_GWS_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_int_ena_w1s
 *
 * SSO Workslot LF Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_ssow_lf_gws_int_ena_w1s
{
    uint64_t u;
    struct bdk_ssow_lf_gws_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t swtag_dis             : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SWTAG_DIS]. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[WQP0]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[EMPTY_WS]. */
#else /* Word 0 - Little Endian */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[EMPTY_WS]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[WQP0]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t swtag_dis             : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SWTAG_DIS]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_int_ena_w1s_s cn9; */
    struct bdk_ssow_lf_gws_int_ena_w1s_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[WQP0]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[EMPTY_WS]. */
#else /* Word 0 - Little Endian */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[EMPTY_WS]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[WQP0]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets enable for SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn96xxp1;
    /* struct bdk_ssow_lf_gws_int_ena_w1s_s cn96xxp3; */
    /* struct bdk_ssow_lf_gws_int_ena_w1s_s cn98xx; */
    /* struct bdk_ssow_lf_gws_int_ena_w1s_cn96xxp1 cnf95xx; */
    /* struct bdk_ssow_lf_gws_int_ena_w1s_cn96xxp1 loki; */
};
typedef union bdk_ssow_lf_gws_int_ena_w1s bdk_ssow_lf_gws_int_ena_w1s_t;

#define BDK_SSOW_LF_GWS_INT_ENA_W1S BDK_SSOW_LF_GWS_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800110ll;
    __bdk_csr_fatal("SSOW_LF_GWS_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_INT_ENA_W1S bdk_ssow_lf_gws_int_ena_w1s_t
#define bustype_BDK_SSOW_LF_GWS_INT_ENA_W1S BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_INT_ENA_W1S "SSOW_LF_GWS_INT_ENA_W1S"
#define device_bar_BDK_SSOW_LF_GWS_INT_ENA_W1S 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_INT_ENA_W1S 0
#define arguments_BDK_SSOW_LF_GWS_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_int_w1s
 *
 * SSO Workslot LF Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_ssow_lf_gws_int_w1s
{
    uint64_t u;
    struct bdk_ssow_lf_gws_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t swtag_dis             : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SWTAG_DIS]. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[WQP0]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[EMPTY_WS]. */
#else /* Word 0 - Little Endian */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[EMPTY_WS]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[WQP0]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t swtag_dis             : 1;  /**< [ 11: 11](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SWTAG_DIS]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_int_w1s_s cn9; */
    struct bdk_ssow_lf_gws_int_w1s_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[WQP0]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[EMPTY_WS]. */
#else /* Word 0 - Little Endian */
        uint64_t empty_ws              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[EMPTY_WS]. */
        uint64_t sw_pend               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SW_PEND]. */
        uint64_t sw_empty              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[SW_EMPTY]. */
        uint64_t gw_pend               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[GW_PEND]. */
        uint64_t alloc_pend            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ALLOC_PEND]. */
        uint64_t desched_pend          : 1;  /**< [  5:  5](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[DESCHED_PEND]. */
        uint64_t clr_nsched_pend       : 1;  /**< [  6:  6](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[CLR_NSCHED_PEND]. */
        uint64_t wqp0                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[WQP0]. */
        uint64_t wqp_space             : 1;  /**< [  8:  8](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[WQP_SPACE]. */
        uint64_t illegal_st            : 1;  /**< [  9:  9](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ILLEGAL_ST]. */
        uint64_t illegal_ld            : 1;  /**< [ 10: 10](R/W1S/H) Reads or sets SSOW_LF_GWS_INT[ILLEGAL_LD]. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn96xxp1;
    /* struct bdk_ssow_lf_gws_int_w1s_s cn96xxp3; */
    /* struct bdk_ssow_lf_gws_int_w1s_s cn98xx; */
    /* struct bdk_ssow_lf_gws_int_w1s_cn96xxp1 cnf95xx; */
    /* struct bdk_ssow_lf_gws_int_w1s_cn96xxp1 loki; */
};
typedef union bdk_ssow_lf_gws_int_w1s bdk_ssow_lf_gws_int_w1s_t;

#define BDK_SSOW_LF_GWS_INT_W1S BDK_SSOW_LF_GWS_INT_W1S_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800108ll;
    __bdk_csr_fatal("SSOW_LF_GWS_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_INT_W1S bdk_ssow_lf_gws_int_w1s_t
#define bustype_BDK_SSOW_LF_GWS_INT_W1S BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_INT_W1S "SSOW_LF_GWS_INT_W1S"
#define device_bar_BDK_SSOW_LF_GWS_INT_W1S 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_INT_W1S 0
#define arguments_BDK_SSOW_LF_GWS_INT_W1S -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_links
 *
 * SSO Workslot LF Links Status Registers
 * Returns status of each HWS.
 */
union bdk_ssow_lf_gws_links
{
    uint64_t u;
    struct bdk_ssow_lf_gws_links_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t tailc                 : 1;  /**< [ 63: 63](RO/H) Set when this SSO entry is the tail of the conflicted tail chain, and so there are no
                                                                 additional conflicts on this tag chain. */
        uint64_t reserved_62           : 1;
        uint64_t index                 : 14; /**< [ 61: 48](RO/H) The SSO entry attached to the GWS. */
        uint64_t reserved_43_47        : 5;
        uint64_t ggrp_err              : 1;  /**< [ 42: 42](RO/H) Indicates a guest group translation error. SSOW_LF_GWS_LINKS[GGRP] is invalid and will return 0. */
        uint64_t ggrp                  : 10; /**< [ 41: 32](RO/H) The guest group attached to the GWS (updated when new tag list entered on SWTAG_FULL).
                                                                 Translation is as described in SSOW_LF_GWS_TAG[GGRP]. */
        uint64_t head                  : 1;  /**< [ 31: 31](RO/H) Set when this SSO entry is at the head of its tag list or when in the UNTAGGED state. */
        uint64_t tail                  : 1;  /**< [ 30: 30](RO/H) Set when this SSO entry is at the tail of its tag list or when in the UNTAGGED state. */
        uint64_t reserved_0_29         : 30;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_29         : 30;
        uint64_t tail                  : 1;  /**< [ 30: 30](RO/H) Set when this SSO entry is at the tail of its tag list or when in the UNTAGGED state. */
        uint64_t head                  : 1;  /**< [ 31: 31](RO/H) Set when this SSO entry is at the head of its tag list or when in the UNTAGGED state. */
        uint64_t ggrp                  : 10; /**< [ 41: 32](RO/H) The guest group attached to the GWS (updated when new tag list entered on SWTAG_FULL).
                                                                 Translation is as described in SSOW_LF_GWS_TAG[GGRP]. */
        uint64_t ggrp_err              : 1;  /**< [ 42: 42](RO/H) Indicates a guest group translation error. SSOW_LF_GWS_LINKS[GGRP] is invalid and will return 0. */
        uint64_t reserved_43_47        : 5;
        uint64_t index                 : 14; /**< [ 61: 48](RO/H) The SSO entry attached to the GWS. */
        uint64_t reserved_62           : 1;
        uint64_t tailc                 : 1;  /**< [ 63: 63](RO/H) Set when this SSO entry is the tail of the conflicted tail chain, and so there are no
                                                                 additional conflicts on this tag chain. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_links_s cn; */
};
typedef union bdk_ssow_lf_gws_links bdk_ssow_lf_gws_links_t;

#define BDK_SSOW_LF_GWS_LINKS BDK_SSOW_LF_GWS_LINKS_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_LINKS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_LINKS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800010ll;
    __bdk_csr_fatal("SSOW_LF_GWS_LINKS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_LINKS bdk_ssow_lf_gws_links_t
#define bustype_BDK_SSOW_LF_GWS_LINKS BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_LINKS "SSOW_LF_GWS_LINKS"
#define device_bar_BDK_SSOW_LF_GWS_LINKS 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_LINKS 0
#define arguments_BDK_SSOW_LF_GWS_LINKS -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_nw_tim
 *
 * SSOW LF New-Work Timer Period Register
 * Sets the minimum period for a new-work-request timeout. The period is specified in n-1
 * notation, with the increment value of 1us. A value of 0x0 in this register sets the
 * min period to 1us, 0x1 to 2us, 0x2 to 3us, etc.
 */
union bdk_ssow_lf_gws_nw_tim
{
    uint64_t u;
    struct bdk_ssow_lf_gws_nw_tim_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t nw_tim                : 10; /**< [  9:  0](R/W) New-work-timer period.
                                                                 0x0 \>= 1us.
                                                                 0x1 \>= 2us.
                                                                 0x2 \>= 3us.
                                                                 _ ... etc. */
#else /* Word 0 - Little Endian */
        uint64_t nw_tim                : 10; /**< [  9:  0](R/W) New-work-timer period.
                                                                 0x0 \>= 1us.
                                                                 0x1 \>= 2us.
                                                                 0x2 \>= 3us.
                                                                 _ ... etc. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_nw_tim_s cn; */
};
typedef union bdk_ssow_lf_gws_nw_tim bdk_ssow_lf_gws_nw_tim_t;

#define BDK_SSOW_LF_GWS_NW_TIM BDK_SSOW_LF_GWS_NW_TIM_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_NW_TIM_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_NW_TIM_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800070ll;
    __bdk_csr_fatal("SSOW_LF_GWS_NW_TIM", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_NW_TIM bdk_ssow_lf_gws_nw_tim_t
#define bustype_BDK_SSOW_LF_GWS_NW_TIM BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_NW_TIM "SSOW_LF_GWS_NW_TIM"
#define device_bar_BDK_SSOW_LF_GWS_NW_TIM 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_NW_TIM 0
#define arguments_BDK_SSOW_LF_GWS_NW_TIM -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_alloc_we
 *
 * SSO Workslot LF Allocate Work Entry Operation Register
 * A read to this register allocates a work entry.
 */
union bdk_ssow_lf_gws_op_alloc_we
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_alloc_we_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t state                 : 2;  /**< [  1:  0](RO/H) See SSO_TT_E enumeration; returns EMPTY on failure. */
#else /* Word 0 - Little Endian */
        uint64_t state                 : 2;  /**< [  1:  0](RO/H) See SSO_TT_E enumeration; returns EMPTY on failure. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_alloc_we_s cn; */
};
typedef union bdk_ssow_lf_gws_op_alloc_we bdk_ssow_lf_gws_op_alloc_we_t;

#define BDK_SSOW_LF_GWS_OP_ALLOC_WE BDK_SSOW_LF_GWS_OP_ALLOC_WE_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_ALLOC_WE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_ALLOC_WE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800400ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_ALLOC_WE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_ALLOC_WE bdk_ssow_lf_gws_op_alloc_we_t
#define bustype_BDK_SSOW_LF_GWS_OP_ALLOC_WE BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_ALLOC_WE "SSOW_LF_GWS_OP_ALLOC_WE"
#define device_bar_BDK_SSOW_LF_GWS_OP_ALLOC_WE 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_ALLOC_WE 0
#define arguments_BDK_SSOW_LF_GWS_OP_ALLOC_WE -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_clr_nsched0
 *
 * SSO Workslot LF Clear Noschedule Operation Register
 * A write to this register performs a CLR_NSCHED.
 *
 * A 128-bit store (STP) must be used to SSOW_LF_GWS_OP_CLR_NSCHED0 and
 * SSOW_LF_GWS_OP_CLR_NSCHED1 to perform the CLR_NSCHED.
 *
 * 64-bit stores to either SSOW_LF_GWS_OP_CLR_NSCHED0 or
 * SSOW_LF_GWS_OP_CLR_NSCHED1 register are errors.
 */
union bdk_ssow_lf_gws_op_clr_nsched0
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_clr_nsched0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to CLR_NSCHED on.
                                                                 Bits \<63:53\> and \<2:0\> are ignored.

                                                                 Must match the WQP of the work-queue entry specified by
                                                                 SSOW_LF_GWS_OP_CLR_NSCHED1[INDEX], otherwise the operation is dropped. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to CLR_NSCHED on.
                                                                 Bits \<63:53\> and \<2:0\> are ignored.

                                                                 Must match the WQP of the work-queue entry specified by
                                                                 SSOW_LF_GWS_OP_CLR_NSCHED1[INDEX], otherwise the operation is dropped. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_clr_nsched0_s cn; */
};
typedef union bdk_ssow_lf_gws_op_clr_nsched0 bdk_ssow_lf_gws_op_clr_nsched0_t;

#define BDK_SSOW_LF_GWS_OP_CLR_NSCHED0 BDK_SSOW_LF_GWS_OP_CLR_NSCHED0_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_CLR_NSCHED0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_CLR_NSCHED0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800a00ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_CLR_NSCHED0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_CLR_NSCHED0 bdk_ssow_lf_gws_op_clr_nsched0_t
#define bustype_BDK_SSOW_LF_GWS_OP_CLR_NSCHED0 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_CLR_NSCHED0 "SSOW_LF_GWS_OP_CLR_NSCHED0"
#define device_bar_BDK_SSOW_LF_GWS_OP_CLR_NSCHED0 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_CLR_NSCHED0 0
#define arguments_BDK_SSOW_LF_GWS_OP_CLR_NSCHED0 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_clr_nsched1
 *
 * SSO Workslot LF Clear Noschedule Operation Register
 * See SSOW_LF_GWS_OP_CLR_NSCHED0.
 */
union bdk_ssow_lf_gws_op_clr_nsched1
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_clr_nsched1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t index                 : 14; /**< [ 13:  0](WO) Index to clear. */
#else /* Word 0 - Little Endian */
        uint64_t index                 : 14; /**< [ 13:  0](WO) Index to clear. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_clr_nsched1_s cn; */
};
typedef union bdk_ssow_lf_gws_op_clr_nsched1 bdk_ssow_lf_gws_op_clr_nsched1_t;

#define BDK_SSOW_LF_GWS_OP_CLR_NSCHED1 BDK_SSOW_LF_GWS_OP_CLR_NSCHED1_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_CLR_NSCHED1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_CLR_NSCHED1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800a08ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_CLR_NSCHED1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_CLR_NSCHED1 bdk_ssow_lf_gws_op_clr_nsched1_t
#define bustype_BDK_SSOW_LF_GWS_OP_CLR_NSCHED1 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_CLR_NSCHED1 "SSOW_LF_GWS_OP_CLR_NSCHED1"
#define device_bar_BDK_SSOW_LF_GWS_OP_CLR_NSCHED1 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_CLR_NSCHED1 0
#define arguments_BDK_SSOW_LF_GWS_OP_CLR_NSCHED1 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_desched
 *
 * SSO Workslot LF Deschedule Operation Register
 * A write to this register performs a deschedule operation.
 */
union bdk_ssow_lf_gws_op_desched
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_desched_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_desched_s cn; */
};
typedef union bdk_ssow_lf_gws_op_desched bdk_ssow_lf_gws_op_desched_t;

#define BDK_SSOW_LF_GWS_OP_DESCHED BDK_SSOW_LF_GWS_OP_DESCHED_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_DESCHED_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_DESCHED_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800880ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_DESCHED", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_DESCHED bdk_ssow_lf_gws_op_desched_t
#define bustype_BDK_SSOW_LF_GWS_OP_DESCHED BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_DESCHED "SSOW_LF_GWS_OP_DESCHED"
#define device_bar_BDK_SSOW_LF_GWS_OP_DESCHED 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_DESCHED 0
#define arguments_BDK_SSOW_LF_GWS_OP_DESCHED -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_desched_nosch
 *
 * SSO Workslot LF Deschedule Noschedule Operation Register
 * A write to this register performs a deschedule nosched operation.
 */
union bdk_ssow_lf_gws_op_desched_nosch
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_desched_nosch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_desched_nosch_s cn; */
};
typedef union bdk_ssow_lf_gws_op_desched_nosch bdk_ssow_lf_gws_op_desched_nosch_t;

#define BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8402008008c0ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_DESCHED_NOSCH", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH bdk_ssow_lf_gws_op_desched_nosch_t
#define bustype_BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH "SSOW_LF_GWS_OP_DESCHED_NOSCH"
#define device_bar_BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH 0
#define arguments_BDK_SSOW_LF_GWS_OP_DESCHED_NOSCH -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_get_work
 *
 * SSO Workslot LF Get-Work Operation Register 0
 * A write to this register initiates a GET_WORK operation.
 *
 * SSOW_LF_GWS_TAG[PEND_GET_WORK] will be set to one when the GET_WORK
 * operation is initiated, and it will be cleared when the GET_WORK
 * completes. The resulting work can be determined by reading the
 * SSOW_LF_GWS_TAG and SSOW_LF_GWS_WQP registers.
 *
 * When no work is available, SSOW_LF_GWS_TAG[TT]=SSO_TT_E::EMPTY, and
 * SSOW_LF_GWS_WQP[WQP] = 0x0.
 */
union bdk_ssow_lf_gws_op_get_work
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_get_work_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_19_63        : 45;
        uint64_t grouped               : 1;  /**< [ 18: 18](WO) Get from a specific group number, specified in [INDEX_GGRP_MASK]. */
        uint64_t indexed               : 1;  /**< [ 17: 17](WO) Indexed get work. If set, indexed get work, specified in [INDEX_GGRP_MASK]. */
        uint64_t waitw                 : 1;  /**< [ 16: 16](WO) If set, wait for work; don't complete GET_WORK until work is available
                                                                 or timeout. Must be zero if [INDEXED] is set. */
        uint64_t reserved_14_15        : 2;
        uint64_t index_ggrp_mask       : 14; /**< [ 13:  0](WO) Index or guest group or masks.

                                                                 * If [INDEXED] and [GROUPED]=0, \<1:0\> indicates how to use the mask sets
                                                                 in SSO_AF_HWS()_S()_GRPMSK() (\<13:2\> are ignored):
                                                                 0x0 = use mask set 0 as high priority, and mask set 1 as lower priority if no groups
                                                                 satisfy mask set 0.
                                                                 0x1 = use mask set 0.
                                                                 0x2 = use mask set 1.
                                                                 0x3 = reserved, behaves as 0x0.

                                                                 * If [INDEXED] = 1, \<13:0\> provides the index to get work from.

                                                                 * If [GROUPED] = 1, \<9:0\> provides the guest group number.

                                                                  o GGRP is translated to a hardware group as described in SSOW_LF_GWS_GRPMSK_CHG.
                                                                    If no match or a multi-match is found SSO_AF_ERR2[WS_UNMAP] or
                                                                    SSO_AF_ERR2[WS_MULTI] is set respectively and no-work is returned. */
#else /* Word 0 - Little Endian */
        uint64_t index_ggrp_mask       : 14; /**< [ 13:  0](WO) Index or guest group or masks.

                                                                 * If [INDEXED] and [GROUPED]=0, \<1:0\> indicates how to use the mask sets
                                                                 in SSO_AF_HWS()_S()_GRPMSK() (\<13:2\> are ignored):
                                                                 0x0 = use mask set 0 as high priority, and mask set 1 as lower priority if no groups
                                                                 satisfy mask set 0.
                                                                 0x1 = use mask set 0.
                                                                 0x2 = use mask set 1.
                                                                 0x3 = reserved, behaves as 0x0.

                                                                 * If [INDEXED] = 1, \<13:0\> provides the index to get work from.

                                                                 * If [GROUPED] = 1, \<9:0\> provides the guest group number.

                                                                  o GGRP is translated to a hardware group as described in SSOW_LF_GWS_GRPMSK_CHG.
                                                                    If no match or a multi-match is found SSO_AF_ERR2[WS_UNMAP] or
                                                                    SSO_AF_ERR2[WS_MULTI] is set respectively and no-work is returned. */
        uint64_t reserved_14_15        : 2;
        uint64_t waitw                 : 1;  /**< [ 16: 16](WO) If set, wait for work; don't complete GET_WORK until work is available
                                                                 or timeout. Must be zero if [INDEXED] is set. */
        uint64_t indexed               : 1;  /**< [ 17: 17](WO) Indexed get work. If set, indexed get work, specified in [INDEX_GGRP_MASK]. */
        uint64_t grouped               : 1;  /**< [ 18: 18](WO) Get from a specific group number, specified in [INDEX_GGRP_MASK]. */
        uint64_t reserved_19_63        : 45;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_get_work_s cn; */
};
typedef union bdk_ssow_lf_gws_op_get_work bdk_ssow_lf_gws_op_get_work_t;

#define BDK_SSOW_LF_GWS_OP_GET_WORK BDK_SSOW_LF_GWS_OP_GET_WORK_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_GET_WORK_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_GET_WORK_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800600ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_GET_WORK", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_GET_WORK bdk_ssow_lf_gws_op_get_work_t
#define bustype_BDK_SSOW_LF_GWS_OP_GET_WORK BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_GET_WORK "SSOW_LF_GWS_OP_GET_WORK"
#define device_bar_BDK_SSOW_LF_GWS_OP_GET_WORK 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_GET_WORK 0
#define arguments_BDK_SSOW_LF_GWS_OP_GET_WORK -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_gwc_inval
 *
 * SSO Workslot LF GW Cache Invalidate Operation Register
 * A write to this register invalidates all SSO register state cached inside
 * the local core. The invalidate only affects the core that executes the
 * write. The write data is ignored.
 */
union bdk_ssow_lf_gws_op_gwc_inval
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_gwc_inval_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_gwc_inval_s cn; */
};
typedef union bdk_ssow_lf_gws_op_gwc_inval bdk_ssow_lf_gws_op_gwc_inval_t;

#define BDK_SSOW_LF_GWS_OP_GWC_INVAL BDK_SSOW_LF_GWS_OP_GWC_INVAL_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_GWC_INVAL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_GWC_INVAL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800e00ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_GWC_INVAL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_GWC_INVAL bdk_ssow_lf_gws_op_gwc_inval_t
#define bustype_BDK_SSOW_LF_GWS_OP_GWC_INVAL BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_GWC_INVAL "SSOW_LF_GWS_OP_GWC_INVAL"
#define device_bar_BDK_SSOW_LF_GWS_OP_GWC_INVAL 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_GWC_INVAL 0
#define arguments_BDK_SSOW_LF_GWS_OP_GWC_INVAL -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_swtag_desched
 *
 * SSO Workslot LF Switch Tag Deschedule Operation Register
 * A write to this register performs a switch tag and a deschedule operation.
 */
union bdk_ssow_lf_gws_op_swtag_desched
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_swtag_desched_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_LF_GWS_GRPMSK_CHG[GGRP0]. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_LF_GWS_GRPMSK_CHG[GGRP0]. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_swtag_desched_s cn; */
};
typedef union bdk_ssow_lf_gws_op_swtag_desched bdk_ssow_lf_gws_op_swtag_desched_t;

#define BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800980ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_SWTAG_DESCHED", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED bdk_ssow_lf_gws_op_swtag_desched_t
#define bustype_BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED "SSOW_LF_GWS_OP_SWTAG_DESCHED"
#define device_bar_BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED 0
#define arguments_BDK_SSOW_LF_GWS_OP_SWTAG_DESCHED -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_swtag_flush
 *
 * SSO Workslot LF Switch Tag Flush Register
 * A write to this register performs a switch tag to EMPTY.
 */
union bdk_ssow_lf_gws_op_swtag_flush
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_swtag_flush_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_swtag_flush_s cn; */
};
typedef union bdk_ssow_lf_gws_op_swtag_flush bdk_ssow_lf_gws_op_swtag_flush_t;

#define BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800800ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_SWTAG_FLUSH", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH bdk_ssow_lf_gws_op_swtag_flush_t
#define bustype_BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH "SSOW_LF_GWS_OP_SWTAG_FLUSH"
#define device_bar_BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH 0
#define arguments_BDK_SSOW_LF_GWS_OP_SWTAG_FLUSH -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_swtag_full0
 *
 * SSO Workslot LF Switch Tag Full Operation Register 0
 * A write to this register performs a switch tag.
 *
 * A 128-bit store (STP) must be used to SSOW_LF_GWS_OP_SWTAG_FULL0 and
 * SSOW_LF_GWS_OP_SWTAG_FULL1.
 */
union bdk_ssow_lf_gws_op_swtag_full0
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_swtag_full0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_LF_GWS_GRPMSK_CHG[GGRP0]. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_LF_GWS_GRPMSK_CHG[GGRP0]. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_swtag_full0_s cn; */
};
typedef union bdk_ssow_lf_gws_op_swtag_full0 bdk_ssow_lf_gws_op_swtag_full0_t;

#define BDK_SSOW_LF_GWS_OP_SWTAG_FULL0 BDK_SSOW_LF_GWS_OP_SWTAG_FULL0_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_FULL0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_FULL0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800c20ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_SWTAG_FULL0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_SWTAG_FULL0 bdk_ssow_lf_gws_op_swtag_full0_t
#define bustype_BDK_SSOW_LF_GWS_OP_SWTAG_FULL0 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_SWTAG_FULL0 "SSOW_LF_GWS_OP_SWTAG_FULL0"
#define device_bar_BDK_SSOW_LF_GWS_OP_SWTAG_FULL0 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_SWTAG_FULL0 0
#define arguments_BDK_SSOW_LF_GWS_OP_SWTAG_FULL0 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_swtag_full1
 *
 * SSO Workslot LF Switch Tag Full Operation Register 1
 * A write to this register performs a switch tag.
 *
 * A 128-bit store (STP) must be used to SSOW_LF_GWS_OP_SWTAG_FULL0 and
 * SSOW_LF_GWS_OP_SWTAG_FULL1.
 */
union bdk_ssow_lf_gws_op_swtag_full1
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_swtag_full1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to switch to.
                                                                 Bits \<63:53\> and \<2:0\> are ignored. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to switch to.
                                                                 Bits \<63:53\> and \<2:0\> are ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_swtag_full1_s cn; */
};
typedef union bdk_ssow_lf_gws_op_swtag_full1 bdk_ssow_lf_gws_op_swtag_full1_t;

#define BDK_SSOW_LF_GWS_OP_SWTAG_FULL1 BDK_SSOW_LF_GWS_OP_SWTAG_FULL1_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_FULL1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_FULL1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800c28ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_SWTAG_FULL1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_SWTAG_FULL1 bdk_ssow_lf_gws_op_swtag_full1_t
#define bustype_BDK_SSOW_LF_GWS_OP_SWTAG_FULL1 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_SWTAG_FULL1 "SSOW_LF_GWS_OP_SWTAG_FULL1"
#define device_bar_BDK_SSOW_LF_GWS_OP_SWTAG_FULL1 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_SWTAG_FULL1 0
#define arguments_BDK_SSOW_LF_GWS_OP_SWTAG_FULL1 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_swtag_norm
 *
 * SSO Workslot LF Switch Tag Normal Operation Register
 * A write to this register performs a switch tag.
 */
union bdk_ssow_lf_gws_op_swtag_norm
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_swtag_norm_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_swtag_norm_s cn; */
};
typedef union bdk_ssow_lf_gws_op_swtag_norm bdk_ssow_lf_gws_op_swtag_norm_t;

#define BDK_SSOW_LF_GWS_OP_SWTAG_NORM BDK_SSOW_LF_GWS_OP_SWTAG_NORM_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_NORM_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_NORM_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800c10ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_SWTAG_NORM", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_SWTAG_NORM bdk_ssow_lf_gws_op_swtag_norm_t
#define bustype_BDK_SSOW_LF_GWS_OP_SWTAG_NORM BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_SWTAG_NORM "SSOW_LF_GWS_OP_SWTAG_NORM"
#define device_bar_BDK_SSOW_LF_GWS_OP_SWTAG_NORM 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_SWTAG_NORM 0
#define arguments_BDK_SSOW_LF_GWS_OP_SWTAG_NORM -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_swtag_nosched
 *
 * SSO Workslot LF Switch Tag Nosched Operation Register
 * A write to this register performs a switch tag and a deschedule operation
 * and sets the NOSCHED bit so that this WQE will not be rescheduled.
 */
union bdk_ssow_lf_gws_op_swtag_nosched
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_swtag_nosched_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_LF_GWS_GRPMSK_CHG[GGRP0]. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_LF_GWS_GRPMSK_CHG[GGRP0]. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_swtag_nosched_s cn; */
};
typedef union bdk_ssow_lf_gws_op_swtag_nosched bdk_ssow_lf_gws_op_swtag_nosched_t;

#define BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8402008009c0ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_SWTAG_NOSCHED", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED bdk_ssow_lf_gws_op_swtag_nosched_t
#define bustype_BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED "SSOW_LF_GWS_OP_SWTAG_NOSCHED"
#define device_bar_BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED 0
#define arguments_BDK_SSOW_LF_GWS_OP_SWTAG_NOSCHED -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_swtag_untag
 *
 * SSO Workslot LF Switch Tag Untagged Operation Register
 * A write to this register performs a switch tag to UNTAGGED.
 */
union bdk_ssow_lf_gws_op_swtag_untag
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_swtag_untag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_swtag_untag_s cn; */
};
typedef union bdk_ssow_lf_gws_op_swtag_untag bdk_ssow_lf_gws_op_swtag_untag_t;

#define BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800810ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_SWTAG_UNTAG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG bdk_ssow_lf_gws_op_swtag_untag_t
#define bustype_BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG "SSOW_LF_GWS_OP_SWTAG_UNTAG"
#define device_bar_BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG 0
#define arguments_BDK_SSOW_LF_GWS_OP_SWTAG_UNTAG -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_swtp_clr
 *
 * SSO Workslot LF Clear Switch Tag Operation Register
 * A write to this register clears the switch-tag pending bit cached in the cores. The
 * workslot's SSOW_LF_GWS_PENDTAG[PEND_SWITCH] bit is unaffected. The write data is
 * ignored.
 */
union bdk_ssow_lf_gws_op_swtp_clr
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_swtp_clr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_swtp_clr_s cn; */
};
typedef union bdk_ssow_lf_gws_op_swtp_clr bdk_ssow_lf_gws_op_swtp_clr_t;

#define BDK_SSOW_LF_GWS_OP_SWTP_CLR BDK_SSOW_LF_GWS_OP_SWTP_CLR_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTP_CLR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTP_CLR_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800820ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_SWTP_CLR", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_SWTP_CLR bdk_ssow_lf_gws_op_swtp_clr_t
#define bustype_BDK_SSOW_LF_GWS_OP_SWTP_CLR BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_SWTP_CLR "SSOW_LF_GWS_OP_SWTP_CLR"
#define device_bar_BDK_SSOW_LF_GWS_OP_SWTP_CLR 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_SWTP_CLR 0
#define arguments_BDK_SSOW_LF_GWS_OP_SWTP_CLR -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_swtp_set
 *
 * SSO Workslot LF Set Switch Tag Operation Register
 * A write to this register sets the switch-tag pending bit cached in the cores. The
 * workslot's SSOW_LF_GWS_PENDTAG[PEND_SWITCH] bit is unaffected. The write data is
 * ignored.
 */
union bdk_ssow_lf_gws_op_swtp_set
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_swtp_set_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_swtp_set_s cn; */
};
typedef union bdk_ssow_lf_gws_op_swtp_set bdk_ssow_lf_gws_op_swtp_set_t;

#define BDK_SSOW_LF_GWS_OP_SWTP_SET BDK_SSOW_LF_GWS_OP_SWTP_SET_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTP_SET_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_SWTP_SET_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800c00ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_SWTP_SET", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_SWTP_SET bdk_ssow_lf_gws_op_swtp_set_t
#define bustype_BDK_SSOW_LF_GWS_OP_SWTP_SET BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_SWTP_SET "SSOW_LF_GWS_OP_SWTP_SET"
#define device_bar_BDK_SSOW_LF_GWS_OP_SWTP_SET 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_SWTP_SET 0
#define arguments_BDK_SSOW_LF_GWS_OP_SWTP_SET -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_upd_wqp_grp0
 *
 * SSO Workslot LF Update WQP/Group Operation Register 0
 * A 64-bit write to this register updates the group.
 *
 * A 128-bit store (STP) to SSOW_LF_GWS_OP_UPD_WQP_GRP0 and
 * SSOW_LF_GWS_OP_UPD_WQP_GRP1 may be used to update both the WQP and group.
 */
union bdk_ssow_lf_gws_op_upd_wqp_grp0
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_upd_wqp_grp0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_LF_GWS_GRPMSK_CHG[GGRP0]. */
        uint64_t reserved_0_33         : 34;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_33         : 34;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_LF_GWS_GRPMSK_CHG[GGRP0]. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_upd_wqp_grp0_s cn; */
};
typedef union bdk_ssow_lf_gws_op_upd_wqp_grp0 bdk_ssow_lf_gws_op_upd_wqp_grp0_t;

#define BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0 BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800830ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_UPD_WQP_GRP0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0 bdk_ssow_lf_gws_op_upd_wqp_grp0_t
#define bustype_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0 "SSOW_LF_GWS_OP_UPD_WQP_GRP0"
#define device_bar_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0 0
#define arguments_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP0 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_op_upd_wqp_grp1
 *
 * SSO Workslot LF Update WQP/Group Operation Register 1
 * A 64-bit write to this register updates the WQP.
 *
 * A 128-bit store (STP) to SSOW_LF_GWS_OP_UPD_WQP_GRP0 and
 * SSOW_LF_GWS_OP_UPD_WQP_GRP1 may be used to update both the WQP and group.
 */
union bdk_ssow_lf_gws_op_upd_wqp_grp1
{
    uint64_t u;
    struct bdk_ssow_lf_gws_op_upd_wqp_grp1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to switch to.
                                                                 Bits \<63:53\> and \<2:0\> are ignored. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to switch to.
                                                                 Bits \<63:53\> and \<2:0\> are ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_op_upd_wqp_grp1_s cn; */
};
typedef union bdk_ssow_lf_gws_op_upd_wqp_grp1 bdk_ssow_lf_gws_op_upd_wqp_grp1_t;

#define BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1 BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800838ll;
    __bdk_csr_fatal("SSOW_LF_GWS_OP_UPD_WQP_GRP1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1 bdk_ssow_lf_gws_op_upd_wqp_grp1_t
#define bustype_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1 BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1 "SSOW_LF_GWS_OP_UPD_WQP_GRP1"
#define device_bar_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1 0
#define arguments_BDK_SSOW_LF_GWS_OP_UPD_WQP_GRP1 -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_pendstate
 *
 * SSO Workslot LF Pending Status Registers
 * Returns status of each GWS.
 *
 * IMPORTANT: Unlike SSOW_LF_GWS_PENDTAG, the state of this register is never
 * cached inside a core.
 */
union bdk_ssow_lf_gws_pendstate
{
    uint64_t u;
    struct bdk_ssow_lf_gws_pendstate_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend_get_work         : 1;  /**< [ 63: 63](RO/H) Set when there is a pending GET_WORK. */
        uint64_t pend_switch           : 1;  /**< [ 62: 62](RO/H) Set when there is a pending SWTAG, SWTAG_DESCHED, or SWTAG_FULL. If the register
                                                                 read was issued after an indexed GET_WORK, the DESCHED portion of a
                                                                 SWTAG_DESCHED cannot still be pending. */
        uint64_t pend_get_work_wait    : 1;  /**< [ 61: 61](RO/H) When [PEND_GET_WORK] is set, indicates that the WAITW bit was set. */
        uint64_t pend_nosched          : 1;  /**< [ 60: 60](RO/H) Set when nosched is desired and [PEND_DESCHED] is set. */
        uint64_t pend_nosched_clr      : 1;  /**< [ 59: 59](RO/H) Set when there is a pending CLR_NSCHED. */
        uint64_t pend_desched          : 1;  /**< [ 58: 58](RO/H) Set when there is a pending DESCHED or SWTAG_DESCHED. */
        uint64_t pend_alloc_we         : 1;  /**< [ 57: 57](RO/H) Set when there is a pending ALLOC_WE. */
        uint64_t pend_flush            : 1;  /**< [ 56: 56](RO/H) Set when there is a pending SWTAG_FLUSH. */
        uint64_t pend_gw_insert        : 1;  /**< [ 55: 55](RAZ) Reserved. Obsolete. */
        uint64_t pend_swunt            : 1;  /**< [ 54: 54](RO/H) Set when there is a pending SWTAG_UNTAG or SWTAG_NORM/SWTAG_FULL with TT of UNTAGGED. */
        uint64_t pend_index            : 14; /**< [ 53: 40](RO/H) The index when [PEND_NOSCHED_CLR] is set. */
        uint64_t reserved_34_39        : 6;
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The tag type when [PEND_SWITCH] is set and [PEND_GET_WORK] is clear. */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The tag when [PEND_SWITCH] is set and [PEND_GET_WORK] is clear. */
#else /* Word 0 - Little Endian */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The tag when [PEND_SWITCH] is set and [PEND_GET_WORK] is clear. */
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The tag type when [PEND_SWITCH] is set and [PEND_GET_WORK] is clear. */
        uint64_t reserved_34_39        : 6;
        uint64_t pend_index            : 14; /**< [ 53: 40](RO/H) The index when [PEND_NOSCHED_CLR] is set. */
        uint64_t pend_swunt            : 1;  /**< [ 54: 54](RO/H) Set when there is a pending SWTAG_UNTAG or SWTAG_NORM/SWTAG_FULL with TT of UNTAGGED. */
        uint64_t pend_gw_insert        : 1;  /**< [ 55: 55](RAZ) Reserved. Obsolete. */
        uint64_t pend_flush            : 1;  /**< [ 56: 56](RO/H) Set when there is a pending SWTAG_FLUSH. */
        uint64_t pend_alloc_we         : 1;  /**< [ 57: 57](RO/H) Set when there is a pending ALLOC_WE. */
        uint64_t pend_desched          : 1;  /**< [ 58: 58](RO/H) Set when there is a pending DESCHED or SWTAG_DESCHED. */
        uint64_t pend_nosched_clr      : 1;  /**< [ 59: 59](RO/H) Set when there is a pending CLR_NSCHED. */
        uint64_t pend_nosched          : 1;  /**< [ 60: 60](RO/H) Set when nosched is desired and [PEND_DESCHED] is set. */
        uint64_t pend_get_work_wait    : 1;  /**< [ 61: 61](RO/H) When [PEND_GET_WORK] is set, indicates that the WAITW bit was set. */
        uint64_t pend_switch           : 1;  /**< [ 62: 62](RO/H) Set when there is a pending SWTAG, SWTAG_DESCHED, or SWTAG_FULL. If the register
                                                                 read was issued after an indexed GET_WORK, the DESCHED portion of a
                                                                 SWTAG_DESCHED cannot still be pending. */
        uint64_t pend_get_work         : 1;  /**< [ 63: 63](RO/H) Set when there is a pending GET_WORK. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_pendstate_s cn9; */
    struct bdk_ssow_lf_gws_pendstate_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend_get_work         : 1;  /**< [ 63: 63](RO/H) Set when there is a pending GET_WORK. */
        uint64_t pend_switch           : 1;  /**< [ 62: 62](RO/H) Set when there is a pending SWTAG, SWTAG_DESCHED, or SWTAG_FULL. If the register
                                                                 read was issued after an indexed GET_WORK, the DESCHED portion of a
                                                                 SWTAG_DESCHED cannot still be pending. */
        uint64_t pend_get_work_wait    : 1;  /**< [ 61: 61](RO/H) When [PEND_GET_WORK] is set, indicates that the WAITW bit was set. */
        uint64_t pend_nosched          : 1;  /**< [ 60: 60](RO/H) Set when nosched is desired and [PEND_DESCHED] is set. */
        uint64_t pend_nosched_clr      : 1;  /**< [ 59: 59](RO/H) Set when there is a pending CLR_NSCHED. */
        uint64_t pend_desched          : 1;  /**< [ 58: 58](RO/H) Set when there is a pending DESCHED or SWTAG_DESCHED. */
        uint64_t pend_alloc_we         : 1;  /**< [ 57: 57](RO/H) Set when there is a pending ALLOC_WE. */
        uint64_t pend_flush            : 1;  /**< [ 56: 56](RO/H) Set when there is a pending SWTAG_FLUSH. */
        uint64_t pend_gw_insert        : 1;  /**< [ 55: 55](RAZ) Reserved. Obsolete. */
        uint64_t reserved_54           : 1;
        uint64_t pend_index            : 14; /**< [ 53: 40](RO/H) The index when [PEND_NOSCHED_CLR] is set. */
        uint64_t reserved_34_39        : 6;
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The tag type when [PEND_SWITCH] is set and [PEND_GET_WORK] is clear. */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The tag when [PEND_SWITCH] is set and [PEND_GET_WORK] is clear. */
#else /* Word 0 - Little Endian */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The tag when [PEND_SWITCH] is set and [PEND_GET_WORK] is clear. */
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The tag type when [PEND_SWITCH] is set and [PEND_GET_WORK] is clear. */
        uint64_t reserved_34_39        : 6;
        uint64_t pend_index            : 14; /**< [ 53: 40](RO/H) The index when [PEND_NOSCHED_CLR] is set. */
        uint64_t reserved_54           : 1;
        uint64_t pend_gw_insert        : 1;  /**< [ 55: 55](RAZ) Reserved. Obsolete. */
        uint64_t pend_flush            : 1;  /**< [ 56: 56](RO/H) Set when there is a pending SWTAG_FLUSH. */
        uint64_t pend_alloc_we         : 1;  /**< [ 57: 57](RO/H) Set when there is a pending ALLOC_WE. */
        uint64_t pend_desched          : 1;  /**< [ 58: 58](RO/H) Set when there is a pending DESCHED or SWTAG_DESCHED. */
        uint64_t pend_nosched_clr      : 1;  /**< [ 59: 59](RO/H) Set when there is a pending CLR_NSCHED. */
        uint64_t pend_nosched          : 1;  /**< [ 60: 60](RO/H) Set when nosched is desired and [PEND_DESCHED] is set. */
        uint64_t pend_get_work_wait    : 1;  /**< [ 61: 61](RO/H) When [PEND_GET_WORK] is set, indicates that the WAITW bit was set. */
        uint64_t pend_switch           : 1;  /**< [ 62: 62](RO/H) Set when there is a pending SWTAG, SWTAG_DESCHED, or SWTAG_FULL. If the register
                                                                 read was issued after an indexed GET_WORK, the DESCHED portion of a
                                                                 SWTAG_DESCHED cannot still be pending. */
        uint64_t pend_get_work         : 1;  /**< [ 63: 63](RO/H) Set when there is a pending GET_WORK. */
#endif /* Word 0 - End */
    } cn96xxp1;
    /* struct bdk_ssow_lf_gws_pendstate_s cn96xxp3; */
    /* struct bdk_ssow_lf_gws_pendstate_s cn98xx; */
    /* struct bdk_ssow_lf_gws_pendstate_cn96xxp1 cnf95xx; */
    /* struct bdk_ssow_lf_gws_pendstate_cn96xxp1 loki; */
};
typedef union bdk_ssow_lf_gws_pendstate bdk_ssow_lf_gws_pendstate_t;

#define BDK_SSOW_LF_GWS_PENDSTATE BDK_SSOW_LF_GWS_PENDSTATE_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_PENDSTATE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_PENDSTATE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800050ll;
    __bdk_csr_fatal("SSOW_LF_GWS_PENDSTATE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_PENDSTATE bdk_ssow_lf_gws_pendstate_t
#define bustype_BDK_SSOW_LF_GWS_PENDSTATE BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_PENDSTATE "SSOW_LF_GWS_PENDSTATE"
#define device_bar_BDK_SSOW_LF_GWS_PENDSTATE 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_PENDSTATE 0
#define arguments_BDK_SSOW_LF_GWS_PENDSTATE -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_pendtag
 *
 * SSO Workslot LF Pending Tag Status Registers
 * Returns status of each GWS.
 *
 * IMPORTANT: Although this register is located in SSO I/O address space, the state of
 * this register is cached inside the cores, and so loads to this register can
 * typically be returned with L1Dcache-like timing.
 */
union bdk_ssow_lf_gws_pendtag
{
    uint64_t u;
    struct bdk_ssow_lf_gws_pendtag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend_get_work         : 1;  /**< [ 63: 63](RO/H) Set when there is a pending GET_WORK. */
        uint64_t pend_switch           : 1;  /**< [ 62: 62](RO/H) Set when there is a pending SWTAG, SWTAG_DESCHED, or SWTAG_FULL. If the register
                                                                 read was issued after an indexed GET_WORK, the DESCHED portion of a
                                                                 SWTAG_DESCHED cannot still be pending. */
        uint64_t reserved_34_61        : 28;
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The tag type when [PEND_SWITCH] is set. */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The tag when [PEND_SWITCH] is set. */
#else /* Word 0 - Little Endian */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The tag when [PEND_SWITCH] is set. */
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The tag type when [PEND_SWITCH] is set. */
        uint64_t reserved_34_61        : 28;
        uint64_t pend_switch           : 1;  /**< [ 62: 62](RO/H) Set when there is a pending SWTAG, SWTAG_DESCHED, or SWTAG_FULL. If the register
                                                                 read was issued after an indexed GET_WORK, the DESCHED portion of a
                                                                 SWTAG_DESCHED cannot still be pending. */
        uint64_t pend_get_work         : 1;  /**< [ 63: 63](RO/H) Set when there is a pending GET_WORK. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_pendtag_s cn; */
};
typedef union bdk_ssow_lf_gws_pendtag bdk_ssow_lf_gws_pendtag_t;

#define BDK_SSOW_LF_GWS_PENDTAG BDK_SSOW_LF_GWS_PENDTAG_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_PENDTAG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_PENDTAG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800230ll;
    __bdk_csr_fatal("SSOW_LF_GWS_PENDTAG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_PENDTAG bdk_ssow_lf_gws_pendtag_t
#define bustype_BDK_SSOW_LF_GWS_PENDTAG BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_PENDTAG "SSOW_LF_GWS_PENDTAG"
#define device_bar_BDK_SSOW_LF_GWS_PENDTAG 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_PENDTAG 0
#define arguments_BDK_SSOW_LF_GWS_PENDTAG -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_pendwqp
 *
 * SSO Workslot LF Pending WQP Status Registers
 * Returns status of each HWS.
 */
union bdk_ssow_lf_gws_pendwqp
{
    uint64_t u;
    struct bdk_ssow_lf_gws_pendwqp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend_wqp              : 64; /**< [ 63:  0](RO/H) The WQP when SSOW_LF_GWS_PENDSTATE[PEND_NOSCHED_CLR] is set.
                                                                 Bits \<63:53\> are a sign extension of \<52\>.  Bits \<2:0\> are 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t pend_wqp              : 64; /**< [ 63:  0](RO/H) The WQP when SSOW_LF_GWS_PENDSTATE[PEND_NOSCHED_CLR] is set.
                                                                 Bits \<63:53\> are a sign extension of \<52\>.  Bits \<2:0\> are 0x0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_pendwqp_s cn; */
};
typedef union bdk_ssow_lf_gws_pendwqp bdk_ssow_lf_gws_pendwqp_t;

#define BDK_SSOW_LF_GWS_PENDWQP BDK_SSOW_LF_GWS_PENDWQP_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_PENDWQP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_PENDWQP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800040ll;
    __bdk_csr_fatal("SSOW_LF_GWS_PENDWQP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_PENDWQP bdk_ssow_lf_gws_pendwqp_t
#define bustype_BDK_SSOW_LF_GWS_PENDWQP BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_PENDWQP "SSOW_LF_GWS_PENDWQP"
#define device_bar_BDK_SSOW_LF_GWS_PENDWQP 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_PENDWQP 0
#define arguments_BDK_SSOW_LF_GWS_PENDWQP -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_swtp
 *
 * SSO Workslot LF Switch Tag Pending Register
 * This register returns the state of the switch-tag pending bit.
 *
 * IMPORTANT: Although this register is located in SSO I/O address space, the state of
 * this register is cached inside the cores, and so loads to this register can
 * typically be returned with L1Dcache-like timing.
 *
 * Internal:
 * The address of this register is decoded by AP MEM.
 */
union bdk_ssow_lf_gws_swtp
{
    uint64_t u;
    struct bdk_ssow_lf_gws_swtp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t pendsw                : 1;  /**< [  0:  0](RO/H) Switch-tag pending. */
#else /* Word 0 - Little Endian */
        uint64_t pendsw                : 1;  /**< [  0:  0](RO/H) Switch-tag pending. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_swtp_s cn; */
};
typedef union bdk_ssow_lf_gws_swtp bdk_ssow_lf_gws_swtp_t;

#define BDK_SSOW_LF_GWS_SWTP BDK_SSOW_LF_GWS_SWTP_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_SWTP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_SWTP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800220ll;
    __bdk_csr_fatal("SSOW_LF_GWS_SWTP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_SWTP bdk_ssow_lf_gws_swtp_t
#define bustype_BDK_SSOW_LF_GWS_SWTP BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_SWTP "SSOW_LF_GWS_SWTP"
#define device_bar_BDK_SSOW_LF_GWS_SWTP 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_SWTP 0
#define arguments_BDK_SSOW_LF_GWS_SWTP -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_tag
 *
 * SSO Workslot LF Tag Status Registers
 * Returns status of each GWS.
 *
 * IMPORTANT: Although this register is located in SSO I/O address space, the state of
 * this register is cached inside the cores, and so loads to this register can
 * typically be returned with L1Dcache-like timing.
 */
union bdk_ssow_lf_gws_tag
{
    uint64_t u;
    struct bdk_ssow_lf_gws_tag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend_get_work         : 1;  /**< [ 63: 63](RO/H) Set when there is a pending GET_WORK. */
        uint64_t pend_switch           : 1;  /**< [ 62: 62](RO/H) Set when there is a pending SWTAG operation. */
        uint64_t reserved_46_61        : 16;
        uint64_t ggrp                  : 10; /**< [ 45: 36](RO/H) The guest group attached to the GWS (updated when new tag list entered on SWTAG_FULL). */
        uint64_t head                  : 1;  /**< [ 35: 35](RO/H) Set when this SSO entry is at the head of its tag list or when in the UNTAGGED state. */
        uint64_t reserved_34           : 1;
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type attached to the GWS (updated when new tag list entered on SWTAG, SWTAG_FULL,
                                                                 or SWTAG_DESCHED.) Enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag attached to the GWS (updated when new tag list entered on SWTAG, SWTAG_FULL, or
                                                                 SWTAG_DESCHED.) */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag attached to the GWS (updated when new tag list entered on SWTAG, SWTAG_FULL, or
                                                                 SWTAG_DESCHED.) */
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type attached to the GWS (updated when new tag list entered on SWTAG, SWTAG_FULL,
                                                                 or SWTAG_DESCHED.) Enumerated by SSO_TT_E. */
        uint64_t reserved_34           : 1;
        uint64_t head                  : 1;  /**< [ 35: 35](RO/H) Set when this SSO entry is at the head of its tag list or when in the UNTAGGED state. */
        uint64_t ggrp                  : 10; /**< [ 45: 36](RO/H) The guest group attached to the GWS (updated when new tag list entered on SWTAG_FULL). */
        uint64_t reserved_46_61        : 16;
        uint64_t pend_switch           : 1;  /**< [ 62: 62](RO/H) Set when there is a pending SWTAG operation. */
        uint64_t pend_get_work         : 1;  /**< [ 63: 63](RO/H) Set when there is a pending GET_WORK. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_tag_s cn; */
};
typedef union bdk_ssow_lf_gws_tag bdk_ssow_lf_gws_tag_t;

#define BDK_SSOW_LF_GWS_TAG BDK_SSOW_LF_GWS_TAG_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_TAG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_TAG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800200ll;
    __bdk_csr_fatal("SSOW_LF_GWS_TAG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_TAG bdk_ssow_lf_gws_tag_t
#define bustype_BDK_SSOW_LF_GWS_TAG BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_TAG "SSOW_LF_GWS_TAG"
#define device_bar_BDK_SSOW_LF_GWS_TAG 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_TAG 0
#define arguments_BDK_SSOW_LF_GWS_TAG -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ssow_lf_gws_wqp
 *
 * SSO Workslot LF WQP Status Registers
 * Returns the WQP attached to the GWS.
 *
 * IMPORTANT: Although this register is located in SSO I/O address space, the state of
 * this register is cached inside the cores, and so loads to this register can
 * typically be returned with L1Dcache-like timing.
 */
union bdk_ssow_lf_gws_wqp
{
    uint64_t u;
    struct bdk_ssow_lf_gws_wqp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) The WQP attached to the GWS (updated when new tag list entered on SWTAG_FULL.)
                                                                 Bits \<63:53\> are a sign extension of \<52\>.  Bits \<2:0\> are 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) The WQP attached to the GWS (updated when new tag list entered on SWTAG_FULL.)
                                                                 Bits \<63:53\> are a sign extension of \<52\>.  Bits \<2:0\> are 0x0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_lf_gws_wqp_s cn; */
};
typedef union bdk_ssow_lf_gws_wqp bdk_ssow_lf_gws_wqp_t;

#define BDK_SSOW_LF_GWS_WQP BDK_SSOW_LF_GWS_WQP_FUNC()
static inline uint64_t BDK_SSOW_LF_GWS_WQP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_LF_GWS_WQP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200800210ll;
    __bdk_csr_fatal("SSOW_LF_GWS_WQP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_LF_GWS_WQP bdk_ssow_lf_gws_wqp_t
#define bustype_BDK_SSOW_LF_GWS_WQP BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_SSOW_LF_GWS_WQP "SSOW_LF_GWS_WQP"
#define device_bar_BDK_SSOW_LF_GWS_WQP 0x2 /* RVU_BAR2 */
#define busnum_BDK_SSOW_LF_GWS_WQP 0
#define arguments_BDK_SSOW_LF_GWS_WQP -1,-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ssow_priv_lf#_hws_cfg
 *
 * SSO WS Privileged Local Function Configuration Registers
 */
union bdk_ssow_priv_lfx_hws_cfg
{
    uint64_t u;
    struct bdk_ssow_priv_lfx_hws_cfg_s
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
    /* struct bdk_ssow_priv_lfx_hws_cfg_s cn; */
};
typedef union bdk_ssow_priv_lfx_hws_cfg bdk_ssow_priv_lfx_hws_cfg_t;

static inline uint64_t BDK_SSOW_PRIV_LFX_HWS_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_PRIV_LFX_HWS_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=51))
        return 0x840080001000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=75))
        return 0x840080001000ll + 8ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=51))
        return 0x840080001000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=51))
        return 0x840080001000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSOW_PRIV_LFX_HWS_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_PRIV_LFX_HWS_CFG(a) bdk_ssow_priv_lfx_hws_cfg_t
#define bustype_BDK_SSOW_PRIV_LFX_HWS_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSOW_PRIV_LFX_HWS_CFG(a) "SSOW_PRIV_LFX_HWS_CFG"
#define device_bar_BDK_SSOW_PRIV_LFX_HWS_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSOW_PRIV_LFX_HWS_CFG(a) (a)
#define arguments_BDK_SSOW_PRIV_LFX_HWS_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ssow_priv_lf#_hws_int_cfg
 *
 * SSO WS Privileged Local Function Interrupt Configuration Registers
 */
union bdk_ssow_priv_lfx_hws_int_cfg
{
    uint64_t u;
    struct bdk_ssow_priv_lfx_hws_int_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by SSOW_LF_INT_VEC_E. */
        uint64_t reserved_11           : 1;
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of LF interrupt vectors enumerated by the block's
                                                                 SSOW_LF_INT_VEC_E in the MSI-X table of the corresponding RVU VF/PF (see
                                                                 SSOW_PRIV_LF()_HWS_CFG[PF_FUNC]). This offset is added to each enumerated value
                                                                 to obtain the corresponding MSI-X vector index. The highest enumerated
                                                                 value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF()_MSIX_CFG[PF_MSIXT_SIZEM1,VF_MSIXT_SIZEM1]. */
#else /* Word 0 - Little Endian */
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of LF interrupt vectors enumerated by the block's
                                                                 SSOW_LF_INT_VEC_E in the MSI-X table of the corresponding RVU VF/PF (see
                                                                 SSOW_PRIV_LF()_HWS_CFG[PF_FUNC]). This offset is added to each enumerated value
                                                                 to obtain the corresponding MSI-X vector index. The highest enumerated
                                                                 value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF()_MSIX_CFG[PF_MSIXT_SIZEM1,VF_MSIXT_SIZEM1]. */
        uint64_t reserved_11           : 1;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by SSOW_LF_INT_VEC_E. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_priv_lfx_hws_int_cfg_s cn; */
};
typedef union bdk_ssow_priv_lfx_hws_int_cfg bdk_ssow_priv_lfx_hws_int_cfg_t;

static inline uint64_t BDK_SSOW_PRIV_LFX_HWS_INT_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_PRIV_LFX_HWS_INT_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=51))
        return 0x840080002000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=75))
        return 0x840080002000ll + 8ll * ((a) & 0x7f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=51))
        return 0x840080002000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=51))
        return 0x840080002000ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("SSOW_PRIV_LFX_HWS_INT_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_PRIV_LFX_HWS_INT_CFG(a) bdk_ssow_priv_lfx_hws_int_cfg_t
#define bustype_BDK_SSOW_PRIV_LFX_HWS_INT_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_SSOW_PRIV_LFX_HWS_INT_CFG(a) "SSOW_PRIV_LFX_HWS_INT_CFG"
#define device_bar_BDK_SSOW_PRIV_LFX_HWS_INT_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_SSOW_PRIV_LFX_HWS_INT_CFG(a) (a)
#define arguments_BDK_SSOW_PRIV_LFX_HWS_INT_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_grpmsk_chg#
 *
 * SSO Work Slot VF Tag Status Registers
 * These registers change which group or groups a HWS belongs to. Multiple registers are
 * provided so 2 bits may be changed using a multi-word store instruction (STP, ST1), or
 * 4 bits with LMTST.
 */
union bdk_ssow_vhwsx_grpmsk_chgx
{
    uint64_t u;
    struct bdk_ssow_vhwsx_grpmsk_chgx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_25_63        : 39;
        uint64_t set                   : 1;  /**< [ 24: 24](WO) Set/clear membership.

                                                                 0 = Disable this HWS's membership in the guest-group [GGRP].  This clears the
                                                                 corresponding bit in SSO_HWS(\<hws\>)_S(\<s\>)_GRPMSK()\<vhg\>, where \<hws\> is
                                                                 determined from this register address, \<s\> is from [MSKSET], and \<vhg\> is
                                                                 a translated [GGRP] (see [GGRP] below).

                                                                 1 = Enable this HWS's membership in the guest-group [GRP].  This sets the
                                                                 corresponding bit in SSO_HWS(\<hws\>)_S(\<s\>)_GRPMSK()\<vhg\>, where \<hws\> is
                                                                 determined from this register address, \<s\> is from [MSKSET], and \<vhg\> is
                                                                 a translated [GGRP] (see [GGRP] below). */
        uint64_t reserved_17_23        : 7;
        uint64_t mskset                : 1;  /**< [ 16: 16](WO) Set number to enable/disable membership in. */
        uint64_t reserved_10_15        : 6;
        uint64_t ggrp                  : 10; /**< [  9:  0](WO) Guest-group number to enable/disable membership in.

                                                                 * If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                 * else if SSO_HWS()_GMCTL[GMID] = 0x1, then [GGRP] is the hardware-group number.

                                                                 * else the [GGRP] is in the context of SSO_HWS()_GMCTL[GMID], and is translated
                                                                   to a hardware-group as described in SSO_PF_MAP(). If no match or a multi-match
                                                                   is found SSO_ERR2[WS_UNMAP] or SSO_ERR2[AW_MULTI] is set respectively and this
                                                                   operation is otherwise ignored (no SSO_HWS()_S()_GRPMSK() bit is set nor
                                                                   cleared). */
#else /* Word 0 - Little Endian */
        uint64_t ggrp                  : 10; /**< [  9:  0](WO) Guest-group number to enable/disable membership in.

                                                                 * If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                 * else if SSO_HWS()_GMCTL[GMID] = 0x1, then [GGRP] is the hardware-group number.

                                                                 * else the [GGRP] is in the context of SSO_HWS()_GMCTL[GMID], and is translated
                                                                   to a hardware-group as described in SSO_PF_MAP(). If no match or a multi-match
                                                                   is found SSO_ERR2[WS_UNMAP] or SSO_ERR2[AW_MULTI] is set respectively and this
                                                                   operation is otherwise ignored (no SSO_HWS()_S()_GRPMSK() bit is set nor
                                                                   cleared). */
        uint64_t reserved_10_15        : 6;
        uint64_t mskset                : 1;  /**< [ 16: 16](WO) Set number to enable/disable membership in. */
        uint64_t reserved_17_23        : 7;
        uint64_t set                   : 1;  /**< [ 24: 24](WO) Set/clear membership.

                                                                 0 = Disable this HWS's membership in the guest-group [GGRP].  This clears the
                                                                 corresponding bit in SSO_HWS(\<hws\>)_S(\<s\>)_GRPMSK()\<vhg\>, where \<hws\> is
                                                                 determined from this register address, \<s\> is from [MSKSET], and \<vhg\> is
                                                                 a translated [GGRP] (see [GGRP] below).

                                                                 1 = Enable this HWS's membership in the guest-group [GRP].  This sets the
                                                                 corresponding bit in SSO_HWS(\<hws\>)_S(\<s\>)_GRPMSK()\<vhg\>, where \<hws\> is
                                                                 determined from this register address, \<s\> is from [MSKSET], and \<vhg\> is
                                                                 a translated [GGRP] (see [GGRP] below). */
        uint64_t reserved_25_63        : 39;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_grpmsk_chgx_s cn; */
};
typedef union bdk_ssow_vhwsx_grpmsk_chgx bdk_ssow_vhwsx_grpmsk_chgx_t;

static inline uint64_t BDK_SSOW_VHWSX_GRPMSK_CHGX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_GRPMSK_CHGX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=31) && (b<=3)))
        return 0x861800000080ll + 0x100000ll * ((a) & 0x1f) + 8ll * ((b) & 0x3);
    __bdk_csr_fatal("SSOW_VHWSX_GRPMSK_CHGX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_GRPMSK_CHGX(a,b) bdk_ssow_vhwsx_grpmsk_chgx_t
#define bustype_BDK_SSOW_VHWSX_GRPMSK_CHGX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_GRPMSK_CHGX(a,b) "SSOW_VHWSX_GRPMSK_CHGX"
#define device_bar_BDK_SSOW_VHWSX_GRPMSK_CHGX(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_GRPMSK_CHGX(a,b) (a)
#define arguments_BDK_SSOW_VHWSX_GRPMSK_CHGX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ssow_vhws#_links
 *
 * SSO Work Slot VF Links Status Registers
 * Returns status of each HWS.
 */
union bdk_ssow_vhwsx_links
{
    uint64_t u;
    struct bdk_ssow_vhwsx_links_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t tailc                 : 1;  /**< [ 63: 63](RO/H) Set when this SSO entry is the tail of the conflicted tail chain, and so there are no
                                                                 additional conflicts on this tag chain. */
        uint64_t reserved_58_62        : 5;
        uint64_t index                 : 10; /**< [ 57: 48](RO/H) The SSO entry attached to the HWS. */
        uint64_t reserved_38_47        : 10;
        uint64_t ggrp                  : 10; /**< [ 37: 28](RO/H) The guest-group attached to the HWS (updated when new tag list entered on SWTAG_FULL).
                                                                 Translation is as described in SSOW_VHWS()_TAG[GGRP]. */
        uint64_t head                  : 1;  /**< [ 27: 27](RO/H) Set when this SSO entry is at the head of its tag list, or when in the UNTAGGED or EMPTY state. */
        uint64_t tail                  : 1;  /**< [ 26: 26](RO/H) Set when this SSO entry is at the tail of its tag list, or when in the UNTAGGED or EMPTY state. */
        uint64_t reserved_21_25        : 5;
        uint64_t revlink_index         : 10; /**< [ 20: 11](RO/H) Prior SSO entry in the tag list when [HEAD]=0 and [TT] is not UNTAGGED nor
                                                                 EMPTY, otherwise unpredictable. */
        uint64_t link_index_vld        : 1;  /**< [ 10: 10](RO/H) Indicates [LINK_INDEX] is valid. [LINK_INDEX_VLD] is itself valid when [TAIL]=1
                                                                 and [TT]=ATOMIC, otherwise unpredictable. */
        uint64_t link_index            : 10; /**< [  9:  0](RO/H) Next SSO entry in the tag list when [LINK_INDEX_VLD]=1, [TAILC]=0 and
                                                                 [TT]=ATOMIC, otherwise unpredictable. */
#else /* Word 0 - Little Endian */
        uint64_t link_index            : 10; /**< [  9:  0](RO/H) Next SSO entry in the tag list when [LINK_INDEX_VLD]=1, [TAILC]=0 and
                                                                 [TT]=ATOMIC, otherwise unpredictable. */
        uint64_t link_index_vld        : 1;  /**< [ 10: 10](RO/H) Indicates [LINK_INDEX] is valid. [LINK_INDEX_VLD] is itself valid when [TAIL]=1
                                                                 and [TT]=ATOMIC, otherwise unpredictable. */
        uint64_t revlink_index         : 10; /**< [ 20: 11](RO/H) Prior SSO entry in the tag list when [HEAD]=0 and [TT] is not UNTAGGED nor
                                                                 EMPTY, otherwise unpredictable. */
        uint64_t reserved_21_25        : 5;
        uint64_t tail                  : 1;  /**< [ 26: 26](RO/H) Set when this SSO entry is at the tail of its tag list, or when in the UNTAGGED or EMPTY state. */
        uint64_t head                  : 1;  /**< [ 27: 27](RO/H) Set when this SSO entry is at the head of its tag list, or when in the UNTAGGED or EMPTY state. */
        uint64_t ggrp                  : 10; /**< [ 37: 28](RO/H) The guest-group attached to the HWS (updated when new tag list entered on SWTAG_FULL).
                                                                 Translation is as described in SSOW_VHWS()_TAG[GGRP]. */
        uint64_t reserved_38_47        : 10;
        uint64_t index                 : 10; /**< [ 57: 48](RO/H) The SSO entry attached to the HWS. */
        uint64_t reserved_58_62        : 5;
        uint64_t tailc                 : 1;  /**< [ 63: 63](RO/H) Set when this SSO entry is the tail of the conflicted tail chain, and so there are no
                                                                 additional conflicts on this tag chain. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_links_s cn; */
};
typedef union bdk_ssow_vhwsx_links bdk_ssow_vhwsx_links_t;

static inline uint64_t BDK_SSOW_VHWSX_LINKS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_LINKS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000310ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_LINKS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_LINKS(a) bdk_ssow_vhwsx_links_t
#define bustype_BDK_SSOW_VHWSX_LINKS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_LINKS(a) "SSOW_VHWSX_LINKS"
#define device_bar_BDK_SSOW_VHWSX_LINKS(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_LINKS(a) (a)
#define arguments_BDK_SSOW_VHWSX_LINKS(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_alloc_we
 *
 * SSO Work Slot VF Allocate Work Entry Operation Register
 * A read to this register allocates a work entry.
 */
union bdk_ssow_vhwsx_op_alloc_we
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_alloc_we_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t state                 : 2;  /**< [  1:  0](RO/H) See SSO_TT_E enumeration; returns EMPTY on failure. */
#else /* Word 0 - Little Endian */
        uint64_t state                 : 2;  /**< [  1:  0](RO/H) See SSO_TT_E enumeration; returns EMPTY on failure. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_alloc_we_s cn; */
};
typedef union bdk_ssow_vhwsx_op_alloc_we bdk_ssow_vhwsx_op_alloc_we_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_ALLOC_WE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_ALLOC_WE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000410ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_ALLOC_WE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_ALLOC_WE(a) bdk_ssow_vhwsx_op_alloc_we_t
#define bustype_BDK_SSOW_VHWSX_OP_ALLOC_WE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_ALLOC_WE(a) "SSOW_VHWSX_OP_ALLOC_WE"
#define device_bar_BDK_SSOW_VHWSX_OP_ALLOC_WE(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_ALLOC_WE(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_ALLOC_WE(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_clr_nsched
 *
 * SSO Work Slot VF Clear Noschedule Operation Register
 * A write to this register performs a CLR_NSCHED.
 *
 * The address offset is calculated using SSOW_CLR_NSCHED_ADDR_S.
 */
union bdk_ssow_vhwsx_op_clr_nsched
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_clr_nsched_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to CLR_NSCHED on.
                                                                 Bits \<63:49\> and \<2:0\> are ignored. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to CLR_NSCHED on.
                                                                 Bits \<63:49\> and \<2:0\> are ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_clr_nsched_s cn; */
};
typedef union bdk_ssow_vhwsx_op_clr_nsched bdk_ssow_vhwsx_op_clr_nsched_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_CLR_NSCHED(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_CLR_NSCHED(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800010000ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_CLR_NSCHED", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_CLR_NSCHED(a) bdk_ssow_vhwsx_op_clr_nsched_t
#define bustype_BDK_SSOW_VHWSX_OP_CLR_NSCHED(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_CLR_NSCHED(a) "SSOW_VHWSX_OP_CLR_NSCHED"
#define device_bar_BDK_SSOW_VHWSX_OP_CLR_NSCHED(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_CLR_NSCHED(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_CLR_NSCHED(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_desched
 *
 * SSO Work Slot VF Deschedule Operation Register
 * A write to this register performs a deschedule operation.
 */
union bdk_ssow_vhwsx_op_desched
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_desched_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_desched_s cn; */
};
typedef union bdk_ssow_vhwsx_op_desched bdk_ssow_vhwsx_op_desched_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_DESCHED(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_DESCHED(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000860ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_DESCHED", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_DESCHED(a) bdk_ssow_vhwsx_op_desched_t
#define bustype_BDK_SSOW_VHWSX_OP_DESCHED(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_DESCHED(a) "SSOW_VHWSX_OP_DESCHED"
#define device_bar_BDK_SSOW_VHWSX_OP_DESCHED(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_DESCHED(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_DESCHED(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_desched_nosch
 *
 * SSO Work Slot VF Deschedule Noschedule Operation Register
 * A write to this register performs a deschedule nosched operation.
 */
union bdk_ssow_vhwsx_op_desched_nosch
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_desched_nosch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_desched_nosch_s cn; */
};
typedef union bdk_ssow_vhwsx_op_desched_nosch bdk_ssow_vhwsx_op_desched_nosch_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_DESCHED_NOSCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_DESCHED_NOSCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000870ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_DESCHED_NOSCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_DESCHED_NOSCH(a) bdk_ssow_vhwsx_op_desched_nosch_t
#define bustype_BDK_SSOW_VHWSX_OP_DESCHED_NOSCH(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_DESCHED_NOSCH(a) "SSOW_VHWSX_OP_DESCHED_NOSCH"
#define device_bar_BDK_SSOW_VHWSX_OP_DESCHED_NOSCH(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_DESCHED_NOSCH(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_DESCHED_NOSCH(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_get_work0
 *
 * SSO Work Slot VF Get-Work Operation Register 0
 * See SSOW_VHWS()_OP_GET_WORK1.
 */
union bdk_ssow_vhwsx_op_get_work0
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_get_work0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_58_63        : 6;
        uint64_t index                 : 10; /**< [ 57: 48](RO/H) Index for the work-queue entry. Unpredictable when SSOW_VHWS()_OP_GET_WORK1[WQP] = 0x0 (no work). */
        uint64_t pend_switch           : 1;  /**< [ 47: 47](RO/H) Pending switch. Set in the result of an indexed GET_WORK when there is a pending SWTAG,
                                                                 SWTAG_FULL, or SWTAG_DESCHED to ORDERED or ATOMIC. Always clear otherwise. (The DESCHED
                                                                 portion of a SWTAG_DESCHED cannot still be pending.) */
        uint64_t reserved_44_46        : 3;
        uint64_t ggrp                  : 10; /**< [ 43: 34](RO/H) Guest-group of the returned work. Unpredictable if SSOW_VHWS()_OP_GET_WORK1[WQP] = 0x0 (no
                                                                 work).

                                                                 * If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                 * else if SSO_HWS()_GMCTL[GMID] = 0x1, then [GGRP] is the hardware-group number.

                                                                 * else the [GGRP] is in the context of SSO_HWS()_GMCTL[GMID].  The return value
                                                                   is translated into a guest-group as described in SSO_PF_MAP(). */
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) Tag type of returned work, enumerated by SSO_TT_E. If
                                                                 SSOW_VHWS()_OP_GET_WORK1[WQP] = 0x0 (no work), returns EMPTY if the work slot was
                                                                 previously empty, else UNTAGGED. */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) Tag of the work-queue entry. Unpredictable when SSOW_VHWS()_OP_GET_WORK1[WQP] = 0x0 (no work). */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) Tag of the work-queue entry. Unpredictable when SSOW_VHWS()_OP_GET_WORK1[WQP] = 0x0 (no work). */
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) Tag type of returned work, enumerated by SSO_TT_E. If
                                                                 SSOW_VHWS()_OP_GET_WORK1[WQP] = 0x0 (no work), returns EMPTY if the work slot was
                                                                 previously empty, else UNTAGGED. */
        uint64_t ggrp                  : 10; /**< [ 43: 34](RO/H) Guest-group of the returned work. Unpredictable if SSOW_VHWS()_OP_GET_WORK1[WQP] = 0x0 (no
                                                                 work).

                                                                 * If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                 * else if SSO_HWS()_GMCTL[GMID] = 0x1, then [GGRP] is the hardware-group number.

                                                                 * else the [GGRP] is in the context of SSO_HWS()_GMCTL[GMID].  The return value
                                                                   is translated into a guest-group as described in SSO_PF_MAP(). */
        uint64_t reserved_44_46        : 3;
        uint64_t pend_switch           : 1;  /**< [ 47: 47](RO/H) Pending switch. Set in the result of an indexed GET_WORK when there is a pending SWTAG,
                                                                 SWTAG_FULL, or SWTAG_DESCHED to ORDERED or ATOMIC. Always clear otherwise. (The DESCHED
                                                                 portion of a SWTAG_DESCHED cannot still be pending.) */
        uint64_t index                 : 10; /**< [ 57: 48](RO/H) Index for the work-queue entry. Unpredictable when SSOW_VHWS()_OP_GET_WORK1[WQP] = 0x0 (no work). */
        uint64_t reserved_58_63        : 6;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_get_work0_s cn; */
};
typedef union bdk_ssow_vhwsx_op_get_work0 bdk_ssow_vhwsx_op_get_work0_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_GET_WORK0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_GET_WORK0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800080000ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_GET_WORK0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_GET_WORK0(a) bdk_ssow_vhwsx_op_get_work0_t
#define bustype_BDK_SSOW_VHWSX_OP_GET_WORK0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_GET_WORK0(a) "SSOW_VHWSX_OP_GET_WORK0"
#define device_bar_BDK_SSOW_VHWSX_OP_GET_WORK0(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_GET_WORK0(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_GET_WORK0(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_get_work1
 *
 * SSO Work Slot VF Get-Work Operation Register 1
 * This register is used along with SSOW_VHWS()_OP_GET_WORK0.
 * A read to this register performs a get work. Either:
 *   * A single-transaction 128-bit load (LDP) is used to GET_WORK0 and GET_WORK1 to
 *   perform a single get-work, returning both information about the work
 *   (index/GRP/TT/TAG) and the work pointer.
 *   * Or, a single 64-bit load is used to GET_WORK1 to return a work pointer.
 *   * Reading GET_WORK0 without a simultaneous read to GET_WORK1
 *   as described above will return 0x0.
 *   * Writing GET_WORK0 or GET_WORK1 is ignored.
 *
 * The address offset is calculated using SSOW_GET_WORK_ADDR_S.
 */
union bdk_ssow_vhwsx_op_get_work1
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_get_work1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) IOVA of the work-queue entry. 0x0 indicates no work.
                                                                 Bits \<2:0\> are always zero; bits \<63:49\> are always a sign extension of bit \<48\>. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) IOVA of the work-queue entry. 0x0 indicates no work.
                                                                 Bits \<2:0\> are always zero; bits \<63:49\> are always a sign extension of bit \<48\>. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_get_work1_s cn; */
};
typedef union bdk_ssow_vhwsx_op_get_work1 bdk_ssow_vhwsx_op_get_work1_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_GET_WORK1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_GET_WORK1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800080008ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_GET_WORK1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_GET_WORK1(a) bdk_ssow_vhwsx_op_get_work1_t
#define bustype_BDK_SSOW_VHWSX_OP_GET_WORK1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_GET_WORK1(a) "SSOW_VHWSX_OP_GET_WORK1"
#define device_bar_BDK_SSOW_VHWSX_OP_GET_WORK1(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_GET_WORK1(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_GET_WORK1(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_swtag_desched
 *
 * SSO Work Slot VF Switch Tag Deschedule Operation Register
 * A write to this register performs a switch tag.
 */
union bdk_ssow_vhwsx_op_swtag_desched
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_swtag_desched_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest-group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_VHWS()_OP_SWTAG_FULL0[GGRP]. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest-group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_VHWS()_OP_SWTAG_FULL0[GGRP]. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_swtag_desched_s cn; */
};
typedef union bdk_ssow_vhwsx_op_swtag_desched bdk_ssow_vhwsx_op_swtag_desched_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_DESCHED(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_DESCHED(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x8618000008c0ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_SWTAG_DESCHED", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_SWTAG_DESCHED(a) bdk_ssow_vhwsx_op_swtag_desched_t
#define bustype_BDK_SSOW_VHWSX_OP_SWTAG_DESCHED(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_SWTAG_DESCHED(a) "SSOW_VHWSX_OP_SWTAG_DESCHED"
#define device_bar_BDK_SSOW_VHWSX_OP_SWTAG_DESCHED(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_SWTAG_DESCHED(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_SWTAG_DESCHED(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_swtag_full0
 *
 * SSO Work Slot VF Switch Tag Full Operation Register 0
 * A write to this register performs a switch tag.
 *
 * A 128-bit store (STP) must be used to SSOW_VHWS()_OP_SWTAG_FULL0 and
 * SSOW_VHWS()_OP_SWTAG_FULL1.
 */
union bdk_ssow_vhwsx_op_swtag_full0
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_swtag_full0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest-group that the work-queue entry will switch to.

                                                                 * If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                 * else if SSO_HWS()_GMCTL[GMID] = 0x1, then [GGRP] is the hardware-group number.

                                                                 * else the [GGRP] is in the context of SSO_HWS()_GMCTL[GMID], and is translated
                                                                   into a hardware-group as described in SSO_PF_MAP().  If no match or a
                                                                   multi-match is found SSO_ERR2[WS_UNMAP] or SSO_ERR2[AW_MULTI] is set
                                                                   respectively and the switch operation is dropped. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest-group that the work-queue entry will switch to.

                                                                 * If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                 * else if SSO_HWS()_GMCTL[GMID] = 0x1, then [GGRP] is the hardware-group number.

                                                                 * else the [GGRP] is in the context of SSO_HWS()_GMCTL[GMID], and is translated
                                                                   into a hardware-group as described in SSO_PF_MAP().  If no match or a
                                                                   multi-match is found SSO_ERR2[WS_UNMAP] or SSO_ERR2[AW_MULTI] is set
                                                                   respectively and the switch operation is dropped. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_swtag_full0_s cn; */
};
typedef union bdk_ssow_vhwsx_op_swtag_full0 bdk_ssow_vhwsx_op_swtag_full0_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_FULL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_FULL0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000ca0ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_SWTAG_FULL0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_SWTAG_FULL0(a) bdk_ssow_vhwsx_op_swtag_full0_t
#define bustype_BDK_SSOW_VHWSX_OP_SWTAG_FULL0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_SWTAG_FULL0(a) "SSOW_VHWSX_OP_SWTAG_FULL0"
#define device_bar_BDK_SSOW_VHWSX_OP_SWTAG_FULL0(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_SWTAG_FULL0(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_SWTAG_FULL0(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_swtag_full1
 *
 * SSO Work Slot VF Switch Tag Full Operation Register 1
 * A write to this register performs a switch tag.
 *
 * A 128-bit store (STP) must be used to SSOW_VHWS()_OP_SWTAG_FULL0 and
 * SSOW_VHWS()_OP_SWTAG_FULL1.
 */
union bdk_ssow_vhwsx_op_swtag_full1
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_swtag_full1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to switch to.
                                                                 Bits \<63:49\> and \<2:0\> are ignored. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to switch to.
                                                                 Bits \<63:49\> and \<2:0\> are ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_swtag_full1_s cn; */
};
typedef union bdk_ssow_vhwsx_op_swtag_full1 bdk_ssow_vhwsx_op_swtag_full1_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_FULL1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_FULL1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000ca8ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_SWTAG_FULL1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_SWTAG_FULL1(a) bdk_ssow_vhwsx_op_swtag_full1_t
#define bustype_BDK_SSOW_VHWSX_OP_SWTAG_FULL1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_SWTAG_FULL1(a) "SSOW_VHWSX_OP_SWTAG_FULL1"
#define device_bar_BDK_SSOW_VHWSX_OP_SWTAG_FULL1(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_SWTAG_FULL1(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_SWTAG_FULL1(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_swtag_norm
 *
 * SSO Work Slot VF Switch Tag Normal Operation Register
 * A write to this register performs a switch tag.
 */
union bdk_ssow_vhwsx_op_swtag_norm
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_swtag_norm_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. [TT] must be ORDERED or ATOMIC. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. [TT] must be ORDERED or ATOMIC. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_swtag_norm_s cn; */
};
typedef union bdk_ssow_vhwsx_op_swtag_norm bdk_ssow_vhwsx_op_swtag_norm_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_NORM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_NORM(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000c80ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_SWTAG_NORM", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_SWTAG_NORM(a) bdk_ssow_vhwsx_op_swtag_norm_t
#define bustype_BDK_SSOW_VHWSX_OP_SWTAG_NORM(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_SWTAG_NORM(a) "SSOW_VHWSX_OP_SWTAG_NORM"
#define device_bar_BDK_SSOW_VHWSX_OP_SWTAG_NORM(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_SWTAG_NORM(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_SWTAG_NORM(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_swtag_nosched
 *
 * SSO Work Slot VF Switch Tag Nosched Operation Register
 * A write to this register performs a switch tag.
 */
union bdk_ssow_vhwsx_op_swtag_nosched
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_swtag_nosched_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest-group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_VHWS()_OP_SWTAG_FULL0[GGRP]. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](WO) Tag to switch to. */
        uint64_t tt                    : 2;  /**< [ 33: 32](WO) The type of the tag, enumerated by SSO_TT_E. */
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest-group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_VHWS()_OP_SWTAG_FULL0[GGRP]. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_swtag_nosched_s cn; */
};
typedef union bdk_ssow_vhwsx_op_swtag_nosched bdk_ssow_vhwsx_op_swtag_nosched_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_NOSCHED(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_NOSCHED(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x8618000008d0ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_SWTAG_NOSCHED", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_SWTAG_NOSCHED(a) bdk_ssow_vhwsx_op_swtag_nosched_t
#define bustype_BDK_SSOW_VHWSX_OP_SWTAG_NOSCHED(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_SWTAG_NOSCHED(a) "SSOW_VHWSX_OP_SWTAG_NOSCHED"
#define device_bar_BDK_SSOW_VHWSX_OP_SWTAG_NOSCHED(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_SWTAG_NOSCHED(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_SWTAG_NOSCHED(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_swtag_untag
 *
 * SSO Work Slot VF Switch Tag Untagged Operation Register
 * A write to this register performs a switch tag to UNTAGGED.
 */
union bdk_ssow_vhwsx_op_swtag_untag
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_swtag_untag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_swtag_untag_s cn; */
};
typedef union bdk_ssow_vhwsx_op_swtag_untag bdk_ssow_vhwsx_op_swtag_untag_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_UNTAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_SWTAG_UNTAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000490ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_SWTAG_UNTAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_SWTAG_UNTAG(a) bdk_ssow_vhwsx_op_swtag_untag_t
#define bustype_BDK_SSOW_VHWSX_OP_SWTAG_UNTAG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_SWTAG_UNTAG(a) "SSOW_VHWSX_OP_SWTAG_UNTAG"
#define device_bar_BDK_SSOW_VHWSX_OP_SWTAG_UNTAG(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_SWTAG_UNTAG(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_SWTAG_UNTAG(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_swtp_clr
 *
 * SSO Work Slot VF Clear Switch Tag Operation Register
 * A write to this register clears the switch-tag pending bit cached in the cores. The
 * work-slot's SSOW_VHWS()_PENDTAG[PEND_SWITCH] bit is unaffected. The write data is
 * ignored.
 */
union bdk_ssow_vhwsx_op_swtp_clr
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_swtp_clr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_swtp_clr_s cn; */
};
typedef union bdk_ssow_vhwsx_op_swtp_clr bdk_ssow_vhwsx_op_swtp_clr_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_SWTP_CLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_SWTP_CLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000820ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_SWTP_CLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_SWTP_CLR(a) bdk_ssow_vhwsx_op_swtp_clr_t
#define bustype_BDK_SSOW_VHWSX_OP_SWTP_CLR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_SWTP_CLR(a) "SSOW_VHWSX_OP_SWTP_CLR"
#define device_bar_BDK_SSOW_VHWSX_OP_SWTP_CLR(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_SWTP_CLR(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_SWTP_CLR(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_swtp_set
 *
 * SSO Work Slot VF Set Switch Tag Operation Register
 * A write to this register sets the switch-tag pending bit cached in the cores. The
 * work-slot's SSOW_VHWS()_PENDTAG[PEND_SWITCH] bit is unaffected. The write data is
 * ignored.
 */
union bdk_ssow_vhwsx_op_swtp_set
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_swtp_set_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_swtp_set_s cn; */
};
typedef union bdk_ssow_vhwsx_op_swtp_set bdk_ssow_vhwsx_op_swtp_set_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_SWTP_SET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_SWTP_SET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000c20ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_SWTP_SET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_SWTP_SET(a) bdk_ssow_vhwsx_op_swtp_set_t
#define bustype_BDK_SSOW_VHWSX_OP_SWTP_SET(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_SWTP_SET(a) "SSOW_VHWSX_OP_SWTP_SET"
#define device_bar_BDK_SSOW_VHWSX_OP_SWTP_SET(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_SWTP_SET(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_SWTP_SET(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_upd_wqp_grp0
 *
 * SSO Work Slot VF Update WQP/Group Operation Register 0
 * A write to this register updates the WQP or group.
 *
 * A 128-bit store (STP) must be used to SSOW_VHWS()_OP_UPD_WQP_GRP0 and
 * SSOW_VHWS()_OP_UPD_WQP_GRP1.
 */
union bdk_ssow_vhwsx_op_upd_wqp_grp0
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_upd_wqp_grp0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest-group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_VHWS()_OP_SWTAG_FULL0[GGRP]. */
        uint64_t reserved_0_33         : 34;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_33         : 34;
        uint64_t ggrp                  : 10; /**< [ 43: 34](WO) Guest-group that the work-queue entry will switch to. Translated as described
                                                                 in SSOW_VHWS()_OP_SWTAG_FULL0[GGRP]. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_upd_wqp_grp0_s cn; */
};
typedef union bdk_ssow_vhwsx_op_upd_wqp_grp0 bdk_ssow_vhwsx_op_upd_wqp_grp0_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_UPD_WQP_GRP0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_UPD_WQP_GRP0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000440ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_UPD_WQP_GRP0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP0(a) bdk_ssow_vhwsx_op_upd_wqp_grp0_t
#define bustype_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP0(a) "SSOW_VHWSX_OP_UPD_WQP_GRP0"
#define device_bar_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP0(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP0(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP0(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_op_upd_wqp_grp1
 *
 * SSO Work Slot VF Switch Tag Full Operation Register 1
 * A write to this register updates the WQP or group.
 *
 * A 128-bit store (STP) must be used to SSOW_VHWS()_OP_UPD_WQP_GRP0 and
 * SSOW_VHWS()_OP_UPD_WQP_GRP1.
 */
union bdk_ssow_vhwsx_op_upd_wqp_grp1
{
    uint64_t u;
    struct bdk_ssow_vhwsx_op_upd_wqp_grp1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to switch to.
                                                                 Bits \<63:49\> and \<2:0\> are ignored. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](WO) IOVA of the work-queue entry to switch to.
                                                                 Bits \<63:49\> and \<2:0\> are ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_op_upd_wqp_grp1_s cn; */
};
typedef union bdk_ssow_vhwsx_op_upd_wqp_grp1 bdk_ssow_vhwsx_op_upd_wqp_grp1_t;

static inline uint64_t BDK_SSOW_VHWSX_OP_UPD_WQP_GRP1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_OP_UPD_WQP_GRP1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000448ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_OP_UPD_WQP_GRP1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP1(a) bdk_ssow_vhwsx_op_upd_wqp_grp1_t
#define bustype_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP1(a) "SSOW_VHWSX_OP_UPD_WQP_GRP1"
#define device_bar_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP1(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP1(a) (a)
#define arguments_BDK_SSOW_VHWSX_OP_UPD_WQP_GRP1(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_pendtag
 *
 * SSO Work Slot VF Pending Tag Status Registers
 * Returns status of each HWS.
 */
union bdk_ssow_vhwsx_pendtag
{
    uint64_t u;
    struct bdk_ssow_vhwsx_pendtag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend_switch           : 1;  /**< [ 63: 63](RO/H) Set when there is a pending SWTAG, SWTAG_DESCHED, or SWTAG_FULL to ORDERED or ATOMIC. If
                                                                 the register read was issued after an indexed GET_WORK, the DESCHED portion of a
                                                                 SWTAG_DESCHED cannot still be pending. */
        uint64_t pend_get_work         : 1;  /**< [ 62: 62](RO/H) Set when there is a pending GET_WORK. */
        uint64_t pend_get_work_wait    : 1;  /**< [ 61: 61](RO/H) When [PEND_GET_WORK] is set, indicates that the WAITW bit was set. */
        uint64_t pend_nosched          : 1;  /**< [ 60: 60](RO/H) Set when nosched is desired and [PEND_DESCHED] is set. */
        uint64_t pend_nosched_clr      : 1;  /**< [ 59: 59](RO/H) Set when there is a pending CLR_NSCHED. */
        uint64_t pend_desched          : 1;  /**< [ 58: 58](RO/H) Set when there is a pending DESCHED or SWTAG_DESCHED. */
        uint64_t pend_alloc_we         : 1;  /**< [ 57: 57](RO/H) Set when there is a pending ALLOC_WE. */
        uint64_t pend_gw_insert        : 1;  /**< [ 56: 56](RO/H) Set when there is a pending GET_WORK insertion. */
        uint64_t reserved_54_55        : 2;
        uint64_t pend_index            : 10; /**< [ 53: 44](RO/H) The index when [PEND_NOSCHED_CLR] is set. */
        uint64_t reserved_34_43        : 10;
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The tag type when [PEND_SWITCH] is set. */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The tag when [PEND_SWITCH] is set. */
#else /* Word 0 - Little Endian */
        uint64_t pend_tag              : 32; /**< [ 31:  0](RO/H) The tag when [PEND_SWITCH] is set. */
        uint64_t pend_tt               : 2;  /**< [ 33: 32](RO/H) The tag type when [PEND_SWITCH] is set. */
        uint64_t reserved_34_43        : 10;
        uint64_t pend_index            : 10; /**< [ 53: 44](RO/H) The index when [PEND_NOSCHED_CLR] is set. */
        uint64_t reserved_54_55        : 2;
        uint64_t pend_gw_insert        : 1;  /**< [ 56: 56](RO/H) Set when there is a pending GET_WORK insertion. */
        uint64_t pend_alloc_we         : 1;  /**< [ 57: 57](RO/H) Set when there is a pending ALLOC_WE. */
        uint64_t pend_desched          : 1;  /**< [ 58: 58](RO/H) Set when there is a pending DESCHED or SWTAG_DESCHED. */
        uint64_t pend_nosched_clr      : 1;  /**< [ 59: 59](RO/H) Set when there is a pending CLR_NSCHED. */
        uint64_t pend_nosched          : 1;  /**< [ 60: 60](RO/H) Set when nosched is desired and [PEND_DESCHED] is set. */
        uint64_t pend_get_work_wait    : 1;  /**< [ 61: 61](RO/H) When [PEND_GET_WORK] is set, indicates that the WAITW bit was set. */
        uint64_t pend_get_work         : 1;  /**< [ 62: 62](RO/H) Set when there is a pending GET_WORK. */
        uint64_t pend_switch           : 1;  /**< [ 63: 63](RO/H) Set when there is a pending SWTAG, SWTAG_DESCHED, or SWTAG_FULL to ORDERED or ATOMIC. If
                                                                 the register read was issued after an indexed GET_WORK, the DESCHED portion of a
                                                                 SWTAG_DESCHED cannot still be pending. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_pendtag_s cn; */
};
typedef union bdk_ssow_vhwsx_pendtag bdk_ssow_vhwsx_pendtag_t;

static inline uint64_t BDK_SSOW_VHWSX_PENDTAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_PENDTAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000340ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_PENDTAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_PENDTAG(a) bdk_ssow_vhwsx_pendtag_t
#define bustype_BDK_SSOW_VHWSX_PENDTAG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_PENDTAG(a) "SSOW_VHWSX_PENDTAG"
#define device_bar_BDK_SSOW_VHWSX_PENDTAG(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_PENDTAG(a) (a)
#define arguments_BDK_SSOW_VHWSX_PENDTAG(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_pendwqp
 *
 * SSO Work Slot VF Pending WQP Status Registers
 * Returns status of each HWS.
 */
union bdk_ssow_vhwsx_pendwqp
{
    uint64_t u;
    struct bdk_ssow_vhwsx_pendwqp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend_wqp              : 64; /**< [ 63:  0](RO/H) The WQP when SSOW_VHWS()_PENDTAG[PEND_NOSCHED_CLR] is set.
                                                                 Bits \<63:49\> are a sign extension of \<48\>.  Bits \<2:0\> are 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t pend_wqp              : 64; /**< [ 63:  0](RO/H) The WQP when SSOW_VHWS()_PENDTAG[PEND_NOSCHED_CLR] is set.
                                                                 Bits \<63:49\> are a sign extension of \<48\>.  Bits \<2:0\> are 0x0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_pendwqp_s cn; */
};
typedef union bdk_ssow_vhwsx_pendwqp bdk_ssow_vhwsx_pendwqp_t;

static inline uint64_t BDK_SSOW_VHWSX_PENDWQP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_PENDWQP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000348ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_PENDWQP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_PENDWQP(a) bdk_ssow_vhwsx_pendwqp_t
#define bustype_BDK_SSOW_VHWSX_PENDWQP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_PENDWQP(a) "SSOW_VHWSX_PENDWQP"
#define device_bar_BDK_SSOW_VHWSX_PENDWQP(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_PENDWQP(a) (a)
#define arguments_BDK_SSOW_VHWSX_PENDWQP(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_swtp
 *
 * SSO Work Slot VF Switch Tag Pending Register
 * This register returns the state of the switch-tag pending bit.
 *
 * IMPORTANT: Although this register is located in SSO I/O address space, the state of
 * this register is cached inside the cores, and so loads to this register can
 * typically be returned with L1Dcache-like timing.
 *
 * Internal:
 * The address of this register is decoded by AP MEM.
 */
union bdk_ssow_vhwsx_swtp
{
    uint64_t u;
    struct bdk_ssow_vhwsx_swtp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t pendsw                : 1;  /**< [  0:  0](RO/H) Switch-tag pending. */
#else /* Word 0 - Little Endian */
        uint64_t pendsw                : 1;  /**< [  0:  0](RO/H) Switch-tag pending. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_swtp_s cn; */
};
typedef union bdk_ssow_vhwsx_swtp bdk_ssow_vhwsx_swtp_t;

static inline uint64_t BDK_SSOW_VHWSX_SWTP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_SWTP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000400ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_SWTP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_SWTP(a) bdk_ssow_vhwsx_swtp_t
#define bustype_BDK_SSOW_VHWSX_SWTP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_SWTP(a) "SSOW_VHWSX_SWTP"
#define device_bar_BDK_SSOW_VHWSX_SWTP(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_SWTP(a) (a)
#define arguments_BDK_SSOW_VHWSX_SWTP(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_tag
 *
 * SSO Work Slot VF Tag Status Registers
 * Returns status of each HWS.
 */
union bdk_ssow_vhwsx_tag
{
    uint64_t u;
    struct bdk_ssow_vhwsx_tag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t tailc                 : 1;  /**< [ 63: 63](RO/H) Set when this SSO entry is the tail of the conflicted tail chain, and so there are no
                                                                 additional conflicts on this tag chain. */
        uint64_t reserved_58_62        : 5;
        uint64_t index                 : 10; /**< [ 57: 48](RO/H) The SSO entry attached to the HWS. */
        uint64_t reserved_46_47        : 2;
        uint64_t ggrp                  : 10; /**< [ 45: 36](RO/H) The guest-group attached to the HWS (updated when new tag list entered on SWTAG_FULL).

                                                                 * If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                 * else if SSO_HWS()_GMCTL[GMID] = 0x1, then [GGRP] is the hardware-group number.

                                                                 * else the [GGRP] is in the context of SSO_HWS()_GMCTL[GMID].  The return value
                                                                   is translated into a guest-group as described in SSO_PF_MAP(). */
        uint64_t head                  : 1;  /**< [ 35: 35](RO/H) Set when this SSO entry is at the head of its tag list, or when in the UNTAGGED or EMPTY state. */
        uint64_t tail                  : 1;  /**< [ 34: 34](RO/H) Set when this SSO entry is at the tail of its tag list, or when in the UNTAGGED or EMPTY state. */
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type attached to the HWS (updated when new tag list entered on SWTAG, SWTAG_FULL,
                                                                 or SWTAG_DESCHED.) */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag attached to the HWS (updated when new tag list entered on SWTAG, SWTAG_FULL, or
                                                                 SWTAG_DESCHED.) */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0](RO/H) The tag attached to the HWS (updated when new tag list entered on SWTAG, SWTAG_FULL, or
                                                                 SWTAG_DESCHED.) */
        uint64_t tt                    : 2;  /**< [ 33: 32](RO/H) The tag type attached to the HWS (updated when new tag list entered on SWTAG, SWTAG_FULL,
                                                                 or SWTAG_DESCHED.) */
        uint64_t tail                  : 1;  /**< [ 34: 34](RO/H) Set when this SSO entry is at the tail of its tag list, or when in the UNTAGGED or EMPTY state. */
        uint64_t head                  : 1;  /**< [ 35: 35](RO/H) Set when this SSO entry is at the head of its tag list, or when in the UNTAGGED or EMPTY state. */
        uint64_t ggrp                  : 10; /**< [ 45: 36](RO/H) The guest-group attached to the HWS (updated when new tag list entered on SWTAG_FULL).

                                                                 * If SSO_HWS()_GMCTL[GMID] = 0x0, behavior is unpredictable.

                                                                 * else if SSO_HWS()_GMCTL[GMID] = 0x1, then [GGRP] is the hardware-group number.

                                                                 * else the [GGRP] is in the context of SSO_HWS()_GMCTL[GMID].  The return value
                                                                   is translated into a guest-group as described in SSO_PF_MAP(). */
        uint64_t reserved_46_47        : 2;
        uint64_t index                 : 10; /**< [ 57: 48](RO/H) The SSO entry attached to the HWS. */
        uint64_t reserved_58_62        : 5;
        uint64_t tailc                 : 1;  /**< [ 63: 63](RO/H) Set when this SSO entry is the tail of the conflicted tail chain, and so there are no
                                                                 additional conflicts on this tag chain. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_tag_s cn; */
};
typedef union bdk_ssow_vhwsx_tag bdk_ssow_vhwsx_tag_t;

static inline uint64_t BDK_SSOW_VHWSX_TAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_TAG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000300ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_TAG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_TAG(a) bdk_ssow_vhwsx_tag_t
#define bustype_BDK_SSOW_VHWSX_TAG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_TAG(a) "SSOW_VHWSX_TAG"
#define device_bar_BDK_SSOW_VHWSX_TAG(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_TAG(a) (a)
#define arguments_BDK_SSOW_VHWSX_TAG(a) (a),-1,-1,-1

/**
 * Register (NCB) ssow_vhws#_wqp
 *
 * SSO Work Slot VF WQP Status Registers
 * Returns status of each HWS.
 */
union bdk_ssow_vhwsx_wqp
{
    uint64_t u;
    struct bdk_ssow_vhwsx_wqp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) The WQP attached to the HWS (updated when new tag list entered on SWTAG_FULL.)
                                                                 Bits \<63:49\> are a sign extension of \<48\>.  Bits \<2:0\> are 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t wqp                   : 64; /**< [ 63:  0](RO/H) The WQP attached to the HWS (updated when new tag list entered on SWTAG_FULL.)
                                                                 Bits \<63:49\> are a sign extension of \<48\>.  Bits \<2:0\> are 0x0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ssow_vhwsx_wqp_s cn; */
};
typedef union bdk_ssow_vhwsx_wqp bdk_ssow_vhwsx_wqp_t;

static inline uint64_t BDK_SSOW_VHWSX_WQP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SSOW_VHWSX_WQP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=31))
        return 0x861800000308ll + 0x100000ll * ((a) & 0x1f);
    __bdk_csr_fatal("SSOW_VHWSX_WQP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_SSOW_VHWSX_WQP(a) bdk_ssow_vhwsx_wqp_t
#define bustype_BDK_SSOW_VHWSX_WQP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SSOW_VHWSX_WQP(a) "SSOW_VHWSX_WQP"
#define device_bar_BDK_SSOW_VHWSX_WQP(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_SSOW_VHWSX_WQP(a) (a)
#define arguments_BDK_SSOW_VHWSX_WQP(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_SSOW_H__ */
