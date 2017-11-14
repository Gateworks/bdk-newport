#ifndef __BDK_CSRS_CCS_H__
#define __BDK_CSRS_CCS_H__
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
 * Cavium CCS.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration ccs_at_scmd_e
 *
 * INTERNAL: Command Mesh Atomic Sub-command Enumeration
 *
 * Enumerates the command mesh atomic sub-command encodings.
 */
#define BDK_CCS_AT_SCMD_E_AT_ADD (8)
#define BDK_CCS_AT_SCMD_E_AT_CAS (0)
#define BDK_CCS_AT_SCMD_E_AT_CLR (9)
#define BDK_CCS_AT_SCMD_E_AT_DEC (3)
#define BDK_CCS_AT_SCMD_E_AT_EOR (0xa)
#define BDK_CCS_AT_SCMD_E_AT_INC (2)
#define BDK_CCS_AT_SCMD_E_AT_SET (0xb)
#define BDK_CCS_AT_SCMD_E_AT_SMAX (0xc)
#define BDK_CCS_AT_SCMD_E_AT_SMIN (0xd)
#define BDK_CCS_AT_SCMD_E_AT_STC (4)
#define BDK_CCS_AT_SCMD_E_AT_SWP (1)
#define BDK_CCS_AT_SCMD_E_AT_UMAX (0xe)
#define BDK_CCS_AT_SCMD_E_AT_UMIN (0xf)

/**
 * Enumeration ccs_bar_e
 *
 * CCS Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_CCS_BAR_E_CCS_PF_BAR0 (0x87e087000000ll)
#define BDK_CCS_BAR_E_CCS_PF_BAR0_SIZE 0x200000ull

/**
 * Enumeration ccs_cmd_e
 *
 * INTERNAL: Command Mesh Command Enumeration
 *
 * Enumerates the command mesh command encodings.
 */
#define BDK_CCS_CMD_E_CMD_AT (2)
#define BDK_CCS_CMD_E_CMD_BC (3)
#define BDK_CCS_CMD_E_CMD_DS (1)
#define BDK_CCS_CMD_E_CMD_FV (6)
#define BDK_CCS_CMD_E_CMD_IO (4)
#define BDK_CCS_CMD_E_CMD_IS (5)
#define BDK_CCS_CMD_E_CMD_NOP (0)

/**
 * Enumeration ccs_ds_scmd_e
 *
 * INTERNAL: Command Mesh D-Stream Sub-command Enumeration
 *
 * Enumerates the command mesh d-stream sub-command encodings.
 */
#define BDK_CCS_DS_SCMD_E_DS_INV (4)
#define BDK_CCS_DS_SCMD_E_DS_INVI (0xc)
#define BDK_CCS_DS_SCMD_E_DS_LCK (2)
#define BDK_CCS_DS_SCMD_E_DS_LD (0)
#define BDK_CCS_DS_SCMD_E_DS_LTGI (8)
#define BDK_CCS_DS_SCMD_E_DS_ST (1)
#define BDK_CCS_DS_SCMD_E_DS_WBC (3)
#define BDK_CCS_DS_SCMD_E_DS_WBCI (0xb)
#define BDK_CCS_DS_SCMD_E_DS_WBI (7)
#define BDK_CCS_DS_SCMD_E_DS_WBII (0xf)

/**
 * Enumeration ccs_is_scmd_e
 *
 * INTERNAL: Command Mesh I-Stream Sub-command Enumeration
 *
 * Enumerates the command mesh i-stream sub-command encodings.
 */
#define BDK_CCS_IS_SCMD_E_IS_INV (4)
#define BDK_CCS_IS_SCMD_E_IS_INVI (0xc)
#define BDK_CCS_IS_SCMD_E_IS_LD (0)
#define BDK_CCS_IS_SCMD_E_IS_LTGI (8)

/**
 * Enumeration ccs_lmc_mode_e
 *
 * CCS ASC Region LMC Mode Enumeration
 * Enumerates the allowed access modes used by ASC regions in CCS_ASC_REGION()_ATTR[LMC_MODE].
 */
#define BDK_CCS_LMC_MODE_E_FLAT_1 (0)
#define BDK_CCS_LMC_MODE_E_STRIPE_2 (2)
#define BDK_CCS_LMC_MODE_E_STRIPE_3 (3)

/**
 * Enumeration ccs_rid_e
 *
 * INTERNAL: CCS Mesh Routing ID Enumeration
 *
 * Enumerates the mesh sources and destinations in CCU()_TAD()_NXM_ERR[MS],
 * CCU()_TAD()_DAT_ERR[MS], and CCU()_TAD()_XBF_ERR[MS].
 */
#define BDK_CCS_RID_E_CLU0_PIC (2)
#define BDK_CCS_RID_E_CLU0_TAD0 (0)
#define BDK_CCS_RID_E_CLU0_TAD1 (1)
#define BDK_CCS_RID_E_CLU1_PIC (6)
#define BDK_CCS_RID_E_CLU1_TAD0 (4)
#define BDK_CCS_RID_E_CLU1_TAD1 (5)
#define BDK_CCS_RID_E_CLU2_PIC (0xa)
#define BDK_CCS_RID_E_CLU2_TAD0 (8)
#define BDK_CCS_RID_E_CLU2_TAD1 (9)
#define BDK_CCS_RID_E_CLU3_PIC (0xe)
#define BDK_CCS_RID_E_CLU3_TAD0 (0xc)
#define BDK_CCS_RID_E_CLU3_TAD1 (0xd)
#define BDK_CCS_RID_E_IOB0 (0x24)
#define BDK_CCS_RID_E_IOB1 (0x25)
#define BDK_CCS_RID_E_MCC0_MCI0 (0x28)
#define BDK_CCS_RID_E_MCC0_MCI1 (0x29)
#define BDK_CCS_RID_E_MCC1_MCI0 (0x2c)
#define BDK_CCS_RID_E_MCC1_MCI1 (0x2d)

/**
 * Register (RSL) ccs_adr_ctl
 *
 * CCS Address Control Register
 * This register holds some of the information required for TAD selection and set
 * hashing. See also CCS_ADR_TDS().
 *
 * Internal:
 * The format and reset values of this register must remain constant for all chips that
 * share an AP implementation.
 */
union bdk_ccs_adr_ctl
{
    uint64_t u;
    struct bdk_ccs_adr_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t md_lr_en              : 36; /**< [ 42:  7](R/W) Enable for each bit that is to participate (1 means participate, 0 means does
                                                                 not participate) in the XOR that determines whether a memory-space physical
                                                                 address is sent to the left or right TADs. */
        uint64_t reserved_4_6          : 3;
        uint64_t md_lr_bit             : 3;  /**< [  3:  1](R/W) Specifies which bit is removed from a memory-space physical address when
                                                                 calculating the LMC line address and TAD set. Legal values 0..7 represent
                                                                 physical address bits 7..14. */
        uint64_t dissetalias           : 1;  /**< [  0:  0](R/W) Disables TAD set hashing, which distributes addresses within a TAD across
                                                                 different sets. */
#else /* Word 0 - Little Endian */
        uint64_t dissetalias           : 1;  /**< [  0:  0](R/W) Disables TAD set hashing, which distributes addresses within a TAD across
                                                                 different sets. */
        uint64_t md_lr_bit             : 3;  /**< [  3:  1](R/W) Specifies which bit is removed from a memory-space physical address when
                                                                 calculating the LMC line address and TAD set. Legal values 0..7 represent
                                                                 physical address bits 7..14. */
        uint64_t reserved_4_6          : 3;
        uint64_t md_lr_en              : 36; /**< [ 42:  7](R/W) Enable for each bit that is to participate (1 means participate, 0 means does
                                                                 not participate) in the XOR that determines whether a memory-space physical
                                                                 address is sent to the left or right TADs. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_adr_ctl_s cn; */
};
typedef union bdk_ccs_adr_ctl bdk_ccs_adr_ctl_t;

#define BDK_CCS_ADR_CTL BDK_CCS_ADR_CTL_FUNC()
static inline uint64_t BDK_CCS_ADR_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_ADR_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100000ll;
    __bdk_csr_fatal("CCS_ADR_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_ADR_CTL bdk_ccs_adr_ctl_t
#define bustype_BDK_CCS_ADR_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_ADR_CTL "CCS_ADR_CTL"
#define device_bar_BDK_CCS_ADR_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_ADR_CTL 0
#define arguments_BDK_CCS_ADR_CTL -1,-1,-1,-1

/**
 * Register (RSL) ccs_adr_mcs#
 *
 * CCS Address Memory Controller Select Registers
 * These registers hold information for memory controller selection.
 * Internal:
 * The reset values are different for each register, parameters can be found in the RTL
 * at ccu_defs::CCS_ADR_MCS_REG_RST[n]. Their values are:
 * * CCS_ADR_MCS(0)[EN] : 0x481249.
 * * CCS_ADR_MCS(1)[EN] : 0x2.
 * * CCS_ADR_MCS(2)[EN] : 0x4.
 * * CCS_ADR_MCS(3)[EN] : 0x8.
 */
union bdk_ccs_adr_mcsx
{
    uint64_t u;
    struct bdk_ccs_adr_mcsx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t en                    : 35; /**< [ 42:  8](R/W) Enable for each bit that is to participate (1 means participate, 0 means does
                                                                 not participate) in the XORs that determine to which memory controller a
                                                                 memory-space physical address is sent. */
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t en                    : 35; /**< [ 42:  8](R/W) Enable for each bit that is to participate (1 means participate, 0 means does
                                                                 not participate) in the XORs that determine to which memory controller a
                                                                 memory-space physical address is sent. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_adr_mcsx_s cn; */
};
typedef union bdk_ccs_adr_mcsx bdk_ccs_adr_mcsx_t;

static inline uint64_t BDK_CCS_ADR_MCSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_ADR_MCSX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=3))
        return 0x87e087104800ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("CCS_ADR_MCSX", 1, a, 0, 0, 0);
}

#define typedef_BDK_CCS_ADR_MCSX(a) bdk_ccs_adr_mcsx_t
#define bustype_BDK_CCS_ADR_MCSX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_ADR_MCSX(a) "CCS_ADR_MCSX"
#define device_bar_BDK_CCS_ADR_MCSX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_ADR_MCSX(a) (a)
#define arguments_BDK_CCS_ADR_MCSX(a) (a),-1,-1,-1

/**
 * Register (RSL) ccs_adr_tds#
 *
 * CCS Address TAD Select Registers
 * These registers hold information for TAD selection.
 * Internal:
 * The format and number of this register must remain constant for all chips that share
 * an AP implementation.
 * The reset values are different for each register, parameters can be found in the RTL
 * at ccu_defs::CCS_ADR_TDS_REG_RST[n]. Their values are:
 * * CCS_ADR_TDS(0)[EN] : 0x1601f725.
 * * CCS_ADR_TDS(1)[EN] : 0x3a03196e.
 */
union bdk_ccs_adr_tdsx
{
    uint64_t u;
    struct bdk_ccs_adr_tdsx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t en                    : 35; /**< [ 42:  8](R/W) Enable for each bit that is to participate (1 means participate, 0 means does
                                                                 not participate) in the XORs for one of the bits that determines to which TAD a
                                                                 memory-space physical address is sent. */
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t en                    : 35; /**< [ 42:  8](R/W) Enable for each bit that is to participate (1 means participate, 0 means does
                                                                 not participate) in the XORs for one of the bits that determines to which TAD a
                                                                 memory-space physical address is sent. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_adr_tdsx_s cn; */
};
typedef union bdk_ccs_adr_tdsx bdk_ccs_adr_tdsx_t;

static inline uint64_t BDK_CCS_ADR_TDSX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_ADR_TDSX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e087104000ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("CCS_ADR_TDSX", 1, a, 0, 0, 0);
}

#define typedef_BDK_CCS_ADR_TDSX(a) bdk_ccs_adr_tdsx_t
#define bustype_BDK_CCS_ADR_TDSX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_ADR_TDSX(a) "CCS_ADR_TDSX"
#define device_bar_BDK_CCS_ADR_TDSX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_ADR_TDSX(a) (a)
#define arguments_BDK_CCS_ADR_TDSX(a) (a),-1,-1,-1

/**
 * Register (RSL) ccs_asc_region#_attr
 *
 * CCS Address Space Control Region Attributes Registers
 */
union bdk_ccs_asc_regionx_attr
{
    uint64_t u;
    struct bdk_ccs_asc_regionx_attr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t write_through         : 1;  /**< [  8:  8](R/W) When set addresses in the region are treated as write-through. All modifications
                                                                 of a cache line will be sent to DRAM immediately. */
        uint64_t lmc_mode              : 3;  /**< [  7:  5](R/W) Specifies how the LMCs in [LMC_MASK] are accessed for this region. Enumerated by
                                                                 CCS_LMC_MODE_E. */
        uint64_t lmc_mask              : 3;  /**< [  4:  2](R/W) Specifies which LMCs are used by this region. If [LMC_MODE] is
                                                                 CCS_LMC_MODE_E::FLAT_1, exactly one bit must be set, if CCS_LMC_MODE_E::STRIPE_2
                                                                 exactly two bits must be set, and if CCS_LMC_MODE_E::STRIPE_3 all 3 bits must be
                                                                 set. */
        uint64_t s_en                  : 1;  /**< [  1:  1](R/W) Enables secure access to region.
                                                                 Undefined if both [S_EN] and [NS_EN] are set for the same region. */
        uint64_t ns_en                 : 1;  /**< [  0:  0](R/W) Enables nonsecure access to region.
                                                                 Undefined if both [S_EN] and [NS_EN] are set for the same region. */
#else /* Word 0 - Little Endian */
        uint64_t ns_en                 : 1;  /**< [  0:  0](R/W) Enables nonsecure access to region.
                                                                 Undefined if both [S_EN] and [NS_EN] are set for the same region. */
        uint64_t s_en                  : 1;  /**< [  1:  1](R/W) Enables secure access to region.
                                                                 Undefined if both [S_EN] and [NS_EN] are set for the same region. */
        uint64_t lmc_mask              : 3;  /**< [  4:  2](R/W) Specifies which LMCs are used by this region. If [LMC_MODE] is
                                                                 CCS_LMC_MODE_E::FLAT_1, exactly one bit must be set, if CCS_LMC_MODE_E::STRIPE_2
                                                                 exactly two bits must be set, and if CCS_LMC_MODE_E::STRIPE_3 all 3 bits must be
                                                                 set. */
        uint64_t lmc_mode              : 3;  /**< [  7:  5](R/W) Specifies how the LMCs in [LMC_MASK] are accessed for this region. Enumerated by
                                                                 CCS_LMC_MODE_E. */
        uint64_t write_through         : 1;  /**< [  8:  8](R/W) When set addresses in the region are treated as write-through. All modifications
                                                                 of a cache line will be sent to DRAM immediately. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_asc_regionx_attr_s cn; */
};
typedef union bdk_ccs_asc_regionx_attr bdk_ccs_asc_regionx_attr_t;

static inline uint64_t BDK_CCS_ASC_REGIONX_ATTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_ASC_REGIONX_ATTR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=15))
        return 0x87e087102018ll + 0x20ll * ((a) & 0xf);
    __bdk_csr_fatal("CCS_ASC_REGIONX_ATTR", 1, a, 0, 0, 0);
}

#define typedef_BDK_CCS_ASC_REGIONX_ATTR(a) bdk_ccs_asc_regionx_attr_t
#define bustype_BDK_CCS_ASC_REGIONX_ATTR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_ASC_REGIONX_ATTR(a) "CCS_ASC_REGIONX_ATTR"
#define device_bar_BDK_CCS_ASC_REGIONX_ATTR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_ASC_REGIONX_ATTR(a) (a)
#define arguments_BDK_CCS_ASC_REGIONX_ATTR(a) (a),-1,-1,-1

/**
 * Register (RSL) ccs_asc_region#_end
 *
 * CCS Address Space Control Region End Address Registers
 */
union bdk_ccs_asc_regionx_end
{
    uint64_t u;
    struct bdk_ccs_asc_regionx_end_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t addr                  : 19; /**< [ 42: 24](R/W) Node-local physical address \<42:24\> marking the inclusive end of the
                                                                 corresponding ASC region. Note that the region includes this address. Software
                                                                 must ensure that regions do not overlap. To indicate an invalidate region, clear
                                                                 both the corresponding CCS_ASC_REGION()_ATTR[S_EN] and CCS_ASC_REGION()_ATTR[NS_EN]. */
        uint64_t reserved_0_23         : 24;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_23         : 24;
        uint64_t addr                  : 19; /**< [ 42: 24](R/W) Node-local physical address \<42:24\> marking the inclusive end of the
                                                                 corresponding ASC region. Note that the region includes this address. Software
                                                                 must ensure that regions do not overlap. To indicate an invalidate region, clear
                                                                 both the corresponding CCS_ASC_REGION()_ATTR[S_EN] and CCS_ASC_REGION()_ATTR[NS_EN]. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_asc_regionx_end_s cn; */
};
typedef union bdk_ccs_asc_regionx_end bdk_ccs_asc_regionx_end_t;

static inline uint64_t BDK_CCS_ASC_REGIONX_END(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_ASC_REGIONX_END(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=15))
        return 0x87e087102008ll + 0x20ll * ((a) & 0xf);
    __bdk_csr_fatal("CCS_ASC_REGIONX_END", 1, a, 0, 0, 0);
}

#define typedef_BDK_CCS_ASC_REGIONX_END(a) bdk_ccs_asc_regionx_end_t
#define bustype_BDK_CCS_ASC_REGIONX_END(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_ASC_REGIONX_END(a) "CCS_ASC_REGIONX_END"
#define device_bar_BDK_CCS_ASC_REGIONX_END(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_ASC_REGIONX_END(a) (a)
#define arguments_BDK_CCS_ASC_REGIONX_END(a) (a),-1,-1,-1

/**
 * Register (RSL) ccs_asc_region#_offset
 *
 * CCS Address Space Control Region Offset Address Registers
 */
union bdk_ccs_asc_regionx_offset
{
    uint64_t u;
    struct bdk_ccs_asc_regionx_offset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_35_63        : 29;
        uint64_t offset                : 18; /**< [ 34: 17](R/W) For each region, the offset to add to the DRAM line address to get the final MCC
                                                                 address. As this is an DRAM offset, the units of {OFFSET] depends on
                                                                 CCS_ASC_REGION()_ATTR[LMC_MODE]; see CCS_LMC_MODE_E. */
        uint64_t reserved_0_16         : 17;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_16         : 17;
        uint64_t offset                : 18; /**< [ 34: 17](R/W) For each region, the offset to add to the DRAM line address to get the final MCC
                                                                 address. As this is an DRAM offset, the units of {OFFSET] depends on
                                                                 CCS_ASC_REGION()_ATTR[LMC_MODE]; see CCS_LMC_MODE_E. */
        uint64_t reserved_35_63        : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_asc_regionx_offset_s cn; */
};
typedef union bdk_ccs_asc_regionx_offset bdk_ccs_asc_regionx_offset_t;

static inline uint64_t BDK_CCS_ASC_REGIONX_OFFSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_ASC_REGIONX_OFFSET(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=15))
        return 0x87e087102010ll + 0x20ll * ((a) & 0xf);
    __bdk_csr_fatal("CCS_ASC_REGIONX_OFFSET", 1, a, 0, 0, 0);
}

#define typedef_BDK_CCS_ASC_REGIONX_OFFSET(a) bdk_ccs_asc_regionx_offset_t
#define bustype_BDK_CCS_ASC_REGIONX_OFFSET(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_ASC_REGIONX_OFFSET(a) "CCS_ASC_REGIONX_OFFSET"
#define device_bar_BDK_CCS_ASC_REGIONX_OFFSET(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_ASC_REGIONX_OFFSET(a) (a)
#define arguments_BDK_CCS_ASC_REGIONX_OFFSET(a) (a),-1,-1,-1

/**
 * Register (RSL) ccs_asc_region#_start
 *
 * CCS Address Space Control Region Start Address Registers
 */
union bdk_ccs_asc_regionx_start
{
    uint64_t u;
    struct bdk_ccs_asc_regionx_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t addr                  : 19; /**< [ 42: 24](R/W) Node-local physical address \<42:24\> marking the start of the corresponding ASC region.
                                                                 Software must ensure that regions do not overlap. */
        uint64_t reserved_0_23         : 24;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_23         : 24;
        uint64_t addr                  : 19; /**< [ 42: 24](R/W) Node-local physical address \<42:24\> marking the start of the corresponding ASC region.
                                                                 Software must ensure that regions do not overlap. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_asc_regionx_start_s cn; */
};
typedef union bdk_ccs_asc_regionx_start bdk_ccs_asc_regionx_start_t;

static inline uint64_t BDK_CCS_ASC_REGIONX_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_ASC_REGIONX_START(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=15))
        return 0x87e087102000ll + 0x20ll * ((a) & 0xf);
    __bdk_csr_fatal("CCS_ASC_REGIONX_START", 1, a, 0, 0, 0);
}

#define typedef_BDK_CCS_ASC_REGIONX_START(a) bdk_ccs_asc_regionx_start_t
#define bustype_BDK_CCS_ASC_REGIONX_START(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_ASC_REGIONX_START(a) "CCS_ASC_REGIONX_START"
#define device_bar_BDK_CCS_ASC_REGIONX_START(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_ASC_REGIONX_START(a) (a)
#define arguments_BDK_CCS_ASC_REGIONX_START(a) (a),-1,-1,-1

/**
 * Register (RSL) ccs_bcst_rsp
 *
 * CCS CCU Broadcast Response Register
 */
union bdk_ccs_bcst_rsp
{
    uint64_t u;
    struct bdk_ccs_bcst_rsp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t ena_clu               : 4;  /**< [  3:  0](R/W) Indicates which CCU cluster instance responds to CCU broadcast read/write
                                                                 operations. For diagnostic use only.

                                                                 Internal:
                                                                 FIXME Change both reset and typical to farthest cluster once ROC floorplan finished. */
#else /* Word 0 - Little Endian */
        uint64_t ena_clu               : 4;  /**< [  3:  0](R/W) Indicates which CCU cluster instance responds to CCU broadcast read/write
                                                                 operations. For diagnostic use only.

                                                                 Internal:
                                                                 FIXME Change both reset and typical to farthest cluster once ROC floorplan finished. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_bcst_rsp_s cn; */
};
typedef union bdk_ccs_bcst_rsp bdk_ccs_bcst_rsp_t;

#define BDK_CCS_BCST_RSP BDK_CCS_BCST_RSP_FUNC()
static inline uint64_t BDK_CCS_BCST_RSP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_BCST_RSP_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100050ll;
    __bdk_csr_fatal("CCS_BCST_RSP", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_BCST_RSP bdk_ccs_bcst_rsp_t
#define bustype_BDK_CCS_BCST_RSP BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_BCST_RSP "CCS_BCST_RSP"
#define device_bar_BDK_CCS_BCST_RSP 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_BCST_RSP 0
#define arguments_BDK_CCS_BCST_RSP -1,-1,-1,-1

/**
 * Register (RSL) ccs_ccpi_ctl
 *
 * CCS CCPI Control Register
 */
union bdk_ccs_ccpi_ctl
{
    uint64_t u;
    struct bdk_ccs_ccpi_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t inv_mode              : 2;  /**< [  7:  6](RAZ) Reserved.
                                                                 Internal:
                                                                 Describes how aggressive to be when waiting for local invalidates before sending
                                                                 CCPI responses which act like commits at the remote. 0x0 = Conservative mode,
                                                                 waits until all local invalidates have been sent and their IAKs received. 0x1 =
                                                                 Moderate mode, waits until all local invalidates have been sent, but not for
                                                                 their IAKs. 0x2 = Aggressive mode, does not wait for local invalidates to begin
                                                                 their processing. */
        uint64_t cas_fdx               : 1;  /**< [  5:  5](RAZ) Reserved.
                                                                 Internal:
                                                                 When set, STC/CAS operations performed at the home will immediately bring the
                                                                 block exclusive into the home. Default operation is to first request the block
                                                                 shared and only invalidate the remote if the compare succeeds. */
        uint64_t rldd_psha             : 1;  /**< [  4:  4](RAZ) Reserved.
                                                                 Internal:
                                                                 When set, RLDD is assumed to return a shared response (PRXS). Default operation
                                                                 assumes an exclusive response (PRXE). Note that an incorrect assumption only
                                                                 causes an extra tag write to be done upon receiving the response. */
        uint64_t enaoci                : 4;  /**< [  3:  0](RAZ) Reserved.
                                                                 Internal:
                                                                 Enable CCPI processing (one bit per node_id). When [ENAOCI]=0x0, no CCPI
                                                                 processing is expected. */
#else /* Word 0 - Little Endian */
        uint64_t enaoci                : 4;  /**< [  3:  0](RAZ) Reserved.
                                                                 Internal:
                                                                 Enable CCPI processing (one bit per node_id). When [ENAOCI]=0x0, no CCPI
                                                                 processing is expected. */
        uint64_t rldd_psha             : 1;  /**< [  4:  4](RAZ) Reserved.
                                                                 Internal:
                                                                 When set, RLDD is assumed to return a shared response (PRXS). Default operation
                                                                 assumes an exclusive response (PRXE). Note that an incorrect assumption only
                                                                 causes an extra tag write to be done upon receiving the response. */
        uint64_t cas_fdx               : 1;  /**< [  5:  5](RAZ) Reserved.
                                                                 Internal:
                                                                 When set, STC/CAS operations performed at the home will immediately bring the
                                                                 block exclusive into the home. Default operation is to first request the block
                                                                 shared and only invalidate the remote if the compare succeeds. */
        uint64_t inv_mode              : 2;  /**< [  7:  6](RAZ) Reserved.
                                                                 Internal:
                                                                 Describes how aggressive to be when waiting for local invalidates before sending
                                                                 CCPI responses which act like commits at the remote. 0x0 = Conservative mode,
                                                                 waits until all local invalidates have been sent and their IAKs received. 0x1 =
                                                                 Moderate mode, waits until all local invalidates have been sent, but not for
                                                                 their IAKs. 0x2 = Aggressive mode, does not wait for local invalidates to begin
                                                                 their processing. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_ccpi_ctl_s cn; */
};
typedef union bdk_ccs_ccpi_ctl bdk_ccs_ccpi_ctl_t;

#define BDK_CCS_CCPI_CTL BDK_CCS_CCPI_CTL_FUNC()
static inline uint64_t BDK_CCS_CCPI_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_CCPI_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100048ll;
    __bdk_csr_fatal("CCS_CCPI_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_CCPI_CTL bdk_ccs_ccpi_ctl_t
#define bustype_BDK_CCS_CCPI_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_CCPI_CTL "CCS_CCPI_CTL"
#define device_bar_BDK_CCS_CCPI_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_CCPI_CTL 0
#define arguments_BDK_CCS_CCPI_CTL -1,-1,-1,-1

/**
 * Register (RSL) ccs_const
 *
 * CCS Constants Register
 * This register contains CCU constants for software discovery.
 */
union bdk_ccs_const
{
    uint64_t u;
    struct bdk_ccs_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t asc                   : 8;  /**< [ 31: 24](RO) Number of ASC regions. */
        uint64_t mpar                  : 12; /**< [ 23: 12](RO) Specifies the number of MPAR IDs. */
        uint64_t tadclu                : 4;  /**< [ 11:  8](RO) Specifies the number of TADs/cluster. */
        uint64_t apclu                 : 4;  /**< [  7:  4](RO) Specifies the number of APs/cluster. */
        uint64_t clu                   : 4;  /**< [  3:  0](RO) Specifies the number of clusters. */
#else /* Word 0 - Little Endian */
        uint64_t clu                   : 4;  /**< [  3:  0](RO) Specifies the number of clusters. */
        uint64_t apclu                 : 4;  /**< [  7:  4](RO) Specifies the number of APs/cluster. */
        uint64_t tadclu                : 4;  /**< [ 11:  8](RO) Specifies the number of TADs/cluster. */
        uint64_t mpar                  : 12; /**< [ 23: 12](RO) Specifies the number of MPAR IDs. */
        uint64_t asc                   : 8;  /**< [ 31: 24](RO) Number of ASC regions. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_const_s cn; */
};
typedef union bdk_ccs_const bdk_ccs_const_t;

#define BDK_CCS_CONST BDK_CCS_CONST_FUNC()
static inline uint64_t BDK_CCS_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_CONST_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100060ll;
    __bdk_csr_fatal("CCS_CONST", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_CONST bdk_ccs_const_t
#define bustype_BDK_CCS_CONST BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_CONST "CCS_CONST"
#define device_bar_BDK_CCS_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_CONST 0
#define arguments_BDK_CCS_CONST -1,-1,-1,-1

/**
 * Register (RSL) ccs_ctl
 *
 * CCS Control Register
 * This register controls common CCU behavior.
 */
union bdk_ccs_ctl
{
    uint64_t u;
    struct bdk_ccs_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t dispsn                : 1;  /**< [  0:  0](R/W) Disable poison code creation and detection in the mesh ECC checkers/generators. */
#else /* Word 0 - Little Endian */
        uint64_t dispsn                : 1;  /**< [  0:  0](R/W) Disable poison code creation and detection in the mesh ECC checkers/generators. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_ctl_s cn; */
};
typedef union bdk_ccs_ctl bdk_ccs_ctl_t;

#define BDK_CCS_CTL BDK_CCS_CTL_FUNC()
static inline uint64_t BDK_CCS_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100078ll;
    __bdk_csr_fatal("CCS_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_CTL bdk_ccs_ctl_t
#define bustype_BDK_CCS_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_CTL "CCS_CTL"
#define device_bar_BDK_CCS_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_CTL 0
#define arguments_BDK_CCS_CTL -1,-1,-1,-1

/**
 * Register (RSL) ccs_mlc_const
 *
 * CCS IMLC Constants Register
 * This register contains I-MLC constants for software discovery.
 */
union bdk_ccs_mlc_const
{
    uint64_t u;
    struct bdk_ccs_mlc_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t ways                  : 8;  /**< [ 19: 12](RO) Specifies the number of ways in I-MLC. */
        uint64_t sets                  : 12; /**< [ 11:  0](RO) Specifies the number of sets in I-MLC. */
#else /* Word 0 - Little Endian */
        uint64_t sets                  : 12; /**< [ 11:  0](RO) Specifies the number of sets in I-MLC. */
        uint64_t ways                  : 8;  /**< [ 19: 12](RO) Specifies the number of ways in I-MLC. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_mlc_const_s cn; */
};
typedef union bdk_ccs_mlc_const bdk_ccs_mlc_const_t;

#define BDK_CCS_MLC_CONST BDK_CCS_MLC_CONST_FUNC()
static inline uint64_t BDK_CCS_MLC_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_MLC_CONST_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100068ll;
    __bdk_csr_fatal("CCS_MLC_CONST", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_MLC_CONST bdk_ccs_mlc_const_t
#define bustype_BDK_CCS_MLC_CONST BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_MLC_CONST "CCS_MLC_CONST"
#define device_bar_BDK_CCS_MLC_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_MLC_CONST 0
#define arguments_BDK_CCS_MLC_CONST -1,-1,-1,-1

/**
 * Register (RSL) ccs_mpar#_mask
 *
 * CCS Memory Paritioning Mask Registers
 * The corresponding CCU()_TAD()_MPAR()_ACNT and CCU()_TAD()_MPAR()_HCNT registers are
 * cleared whenever this register is written.
 */
union bdk_ccs_mparx_mask
{
    uint64_t u;
    struct bdk_ccs_mparx_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_34_63        : 30;
        uint64_t dtg                   : 20; /**< [ 33: 14](R/W) Each bit set to one prevents the use of the corresponding DTG way by sources that
                                                                 are using this MPARID. It is illegal to prevent all DTG ways from being used. */
        uint64_t ltg                   : 14; /**< [ 13:  0](R/W) Each bit set to one prevents the use of the corresponding LTG way by sources
                                                                 that are using this MPARID. */
#else /* Word 0 - Little Endian */
        uint64_t ltg                   : 14; /**< [ 13:  0](R/W) Each bit set to one prevents the use of the corresponding LTG way by sources
                                                                 that are using this MPARID. */
        uint64_t dtg                   : 20; /**< [ 33: 14](R/W) Each bit set to one prevents the use of the corresponding DTG way by sources that
                                                                 are using this MPARID. It is illegal to prevent all DTG ways from being used. */
        uint64_t reserved_34_63        : 30;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_mparx_mask_s cn; */
};
typedef union bdk_ccs_mparx_mask bdk_ccs_mparx_mask_t;

static inline uint64_t BDK_CCS_MPARX_MASK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_MPARX_MASK(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=255))
        return 0x87e087101000ll + 8ll * ((a) & 0xff);
    __bdk_csr_fatal("CCS_MPARX_MASK", 1, a, 0, 0, 0);
}

#define typedef_BDK_CCS_MPARX_MASK(a) bdk_ccs_mparx_mask_t
#define bustype_BDK_CCS_MPARX_MASK(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_MPARX_MASK(a) "CCS_MPARX_MASK"
#define device_bar_BDK_CCS_MPARX_MASK(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_MPARX_MASK(a) (a)
#define arguments_BDK_CCS_MPARX_MASK(a) (a),-1,-1,-1

/**
 * Register (RSL) ccs_pic_ctl
 *
 * CCS PIC Control Register
 * This register controls PIC behavior.
 */
union bdk_ccs_pic_ctl
{
    uint64_t u;
    struct bdk_ccs_pic_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t excmdrqh              : 6;  /**< [ 55: 50](R/W) Extra mesh VC credits to reserve for CMD mesh RQH (high priority) memory requests. */
        uint64_t excmdreq              : 6;  /**< [ 49: 44](R/W) Extra mesh VC credits to reserve for CMD mesh REQ (normal priority) memory requests. */
        uint64_t exdatrqh              : 6;  /**< [ 43: 38](R/W) Extra mesh VC credits to reserve for DAT mesh RQH (high priority) memory requests. */
        uint64_t exdatreq              : 6;  /**< [ 37: 32](R/W) Extra mesh VC credits to reserve for DAT mesh REQ (normal priority) memory requests. */
        uint64_t reserved_3_31         : 29;
        uint64_t error_inject          : 2;  /**< [  2:  1](R/W) This 2-bit field provides diagnostic ECC error injection by flipping
                                                                 the least significant two bits of the PIC's DAT mesh ECC generator.
                                                                 This bit flipping is done for all DAT mesh transactions while the
                                                                 field is asserted. Asserting a single bit causes a single bit ECC
                                                                 error and asserting both bits causes a double-bit ECC error. */
        uint64_t cclk_dis              : 1;  /**< [  0:  0](R/W) Disable power saving PIC conditional clocking. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t cclk_dis              : 1;  /**< [  0:  0](R/W) Disable power saving PIC conditional clocking. For diagnostic use only. */
        uint64_t error_inject          : 2;  /**< [  2:  1](R/W) This 2-bit field provides diagnostic ECC error injection by flipping
                                                                 the least significant two bits of the PIC's DAT mesh ECC generator.
                                                                 This bit flipping is done for all DAT mesh transactions while the
                                                                 field is asserted. Asserting a single bit causes a single bit ECC
                                                                 error and asserting both bits causes a double-bit ECC error. */
        uint64_t reserved_3_31         : 29;
        uint64_t exdatreq              : 6;  /**< [ 37: 32](R/W) Extra mesh VC credits to reserve for DAT mesh REQ (normal priority) memory requests. */
        uint64_t exdatrqh              : 6;  /**< [ 43: 38](R/W) Extra mesh VC credits to reserve for DAT mesh RQH (high priority) memory requests. */
        uint64_t excmdreq              : 6;  /**< [ 49: 44](R/W) Extra mesh VC credits to reserve for CMD mesh REQ (normal priority) memory requests. */
        uint64_t excmdrqh              : 6;  /**< [ 55: 50](R/W) Extra mesh VC credits to reserve for CMD mesh RQH (high priority) memory requests. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_pic_ctl_s cn; */
};
typedef union bdk_ccs_pic_ctl bdk_ccs_pic_ctl_t;

#define BDK_CCS_PIC_CTL BDK_CCS_PIC_CTL_FUNC()
static inline uint64_t BDK_CCS_PIC_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_PIC_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100058ll;
    __bdk_csr_fatal("CCS_PIC_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_PIC_CTL bdk_ccs_pic_ctl_t
#define bustype_BDK_CCS_PIC_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_PIC_CTL "CCS_PIC_CTL"
#define device_bar_BDK_CCS_PIC_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_PIC_CTL 0
#define arguments_BDK_CCS_PIC_CTL -1,-1,-1,-1

/**
 * Register (RSL) ccs_quick_did#
 *
 * CCS Quick-Done Device ID Control Register
 */
union bdk_ccs_quick_didx
{
    uint64_t u;
    struct bdk_ccs_quick_didx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t quick                 : 64; /**< [ 63:  0](R/W) Enable quick-done.

                                                                 Each bit controls the quick-done setting for the corresponding NCB DID when
                                                                 PA\<51:47\> = 0x1. E.g. CCS_QUICK_DID(0) bit 0 of controls NCB DID 0 (which
                                                                 corresponds to PA\<43:36\> = 0x0), and CCS_QUICK_DID(3) bit 63 controls NCB DID
                                                                 255. */
#else /* Word 0 - Little Endian */
        uint64_t quick                 : 64; /**< [ 63:  0](R/W) Enable quick-done.

                                                                 Each bit controls the quick-done setting for the corresponding NCB DID when
                                                                 PA\<51:47\> = 0x1. E.g. CCS_QUICK_DID(0) bit 0 of controls NCB DID 0 (which
                                                                 corresponds to PA\<43:36\> = 0x0), and CCS_QUICK_DID(3) bit 63 controls NCB DID
                                                                 255. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_quick_didx_s cn; */
};
typedef union bdk_ccs_quick_didx bdk_ccs_quick_didx_t;

static inline uint64_t BDK_CCS_QUICK_DIDX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_QUICK_DIDX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=3))
        return 0x87e087100020ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("CCS_QUICK_DIDX", 1, a, 0, 0, 0);
}

#define typedef_BDK_CCS_QUICK_DIDX(a) bdk_ccs_quick_didx_t
#define bustype_BDK_CCS_QUICK_DIDX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_QUICK_DIDX(a) "CCS_QUICK_DIDX"
#define device_bar_BDK_CCS_QUICK_DIDX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_QUICK_DIDX(a) (a)
#define arguments_BDK_CCS_QUICK_DIDX(a) (a),-1,-1,-1

/**
 * Register (RSL) ccs_quick_huge
 *
 * CCS Quick-Done Huge Segment Control Register
 * This register controls the bitmask of which address regions are quick-done when
 * PA\<51:50\> != 0x0.
 */
union bdk_ccs_quick_huge
{
    uint64_t u;
    struct bdk_ccs_quick_huge_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t quick                 : 48; /**< [ 47:  0](R/W) Enable quick-done.

                                                                 Each bit in \<47:32\> controls the quick-done setting corresponding to PA\<47:44\>
                                                                 when PA\<51:50\> = 0x3. E.g. bit\<32\> controls PA\<47:44\> = 0x0 and bit\<47\> controls
                                                                 PA\<47:44\> = 0xF.

                                                                 Each bit in \<31:16\> controls the quick-done setting corresponding to PA\<47:44\>
                                                                 when PA\<51:50\> = 0x2. E.g. bit\<16\> controls PA\<47:44\> = 0x0 and bit\<31\> controls
                                                                 PA\<47:44\> = 0xF.

                                                                 Each bit in \<15:0\> controls the quick-done setting corresponding to PA\<47:44\>
                                                                 when PA\<51:50\> = 0x1. E.g. bit\<0\> controls PA\<47:44\> = 0x0 and bit 15 controls
                                                                 PA\<47:44\> = 0xF. */
#else /* Word 0 - Little Endian */
        uint64_t quick                 : 48; /**< [ 47:  0](R/W) Enable quick-done.

                                                                 Each bit in \<47:32\> controls the quick-done setting corresponding to PA\<47:44\>
                                                                 when PA\<51:50\> = 0x3. E.g. bit\<32\> controls PA\<47:44\> = 0x0 and bit\<47\> controls
                                                                 PA\<47:44\> = 0xF.

                                                                 Each bit in \<31:16\> controls the quick-done setting corresponding to PA\<47:44\>
                                                                 when PA\<51:50\> = 0x2. E.g. bit\<16\> controls PA\<47:44\> = 0x0 and bit\<31\> controls
                                                                 PA\<47:44\> = 0xF.

                                                                 Each bit in \<15:0\> controls the quick-done setting corresponding to PA\<47:44\>
                                                                 when PA\<51:50\> = 0x1. E.g. bit\<0\> controls PA\<47:44\> = 0x0 and bit 15 controls
                                                                 PA\<47:44\> = 0xF. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_quick_huge_s cn; */
};
typedef union bdk_ccs_quick_huge bdk_ccs_quick_huge_t;

#define BDK_CCS_QUICK_HUGE BDK_CCS_QUICK_HUGE_FUNC()
static inline uint64_t BDK_CCS_QUICK_HUGE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_QUICK_HUGE_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100040ll;
    __bdk_csr_fatal("CCS_QUICK_HUGE", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_QUICK_HUGE bdk_ccs_quick_huge_t
#define bustype_BDK_CCS_QUICK_HUGE BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_QUICK_HUGE "CCS_QUICK_HUGE"
#define device_bar_BDK_CCS_QUICK_HUGE 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_QUICK_HUGE 0
#define arguments_BDK_CCS_QUICK_HUGE -1,-1,-1,-1

/**
 * Register (RSL) ccs_scratch
 *
 * INTERNAL: CCS General Purpose Scratch Register
 *
 * These registers are only reset by hardware during chip cold reset. The values of the CSR
 * fields in these registers do not change during chip warm or soft resets.
 */
union bdk_ccs_scratch
{
    uint64_t u;
    struct bdk_ccs_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 8;  /**< [  7:  0](R/W) General purpose scratch register. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_scratch_s cn; */
};
typedef union bdk_ccs_scratch bdk_ccs_scratch_t;

#define BDK_CCS_SCRATCH BDK_CCS_SCRATCH_FUNC()
static inline uint64_t BDK_CCS_SCRATCH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_SCRATCH_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100008ll;
    __bdk_csr_fatal("CCS_SCRATCH", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_SCRATCH bdk_ccs_scratch_t
#define bustype_BDK_CCS_SCRATCH BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_SCRATCH "CCS_SCRATCH"
#define device_bar_BDK_CCS_SCRATCH 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_SCRATCH 0
#define arguments_BDK_CCS_SCRATCH -1,-1,-1,-1

/**
 * Register (RSL) ccs_tad_const
 *
 * CCS TAD Constants Register
 * This register contains TAD constants for software discovery.
 */
union bdk_ccs_tad_const
{
    uint64_t u;
    struct bdk_ccs_tad_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t dtgways               : 8;  /**< [ 27: 20](RO) Specifies the number of DTG ways in a TAD. */
        uint64_t ltgways               : 8;  /**< [ 19: 12](RO) Specifies the number of LTG ways in a TAD. */
        uint64_t sets                  : 12; /**< [ 11:  0](RO) Specifies the number of sets in a TAD. */
#else /* Word 0 - Little Endian */
        uint64_t sets                  : 12; /**< [ 11:  0](RO) Specifies the number of sets in a TAD. */
        uint64_t ltgways               : 8;  /**< [ 19: 12](RO) Specifies the number of LTG ways in a TAD. */
        uint64_t dtgways               : 8;  /**< [ 27: 20](RO) Specifies the number of DTG ways in a TAD. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_tad_const_s cn; */
};
typedef union bdk_ccs_tad_const bdk_ccs_tad_const_t;

#define BDK_CCS_TAD_CONST BDK_CCS_TAD_CONST_FUNC()
static inline uint64_t BDK_CCS_TAD_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_TAD_CONST_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100070ll;
    __bdk_csr_fatal("CCS_TAD_CONST", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_TAD_CONST bdk_ccs_tad_const_t
#define bustype_BDK_CCS_TAD_CONST BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_TAD_CONST "CCS_TAD_CONST"
#define device_bar_BDK_CCS_TAD_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_TAD_CONST 0
#define arguments_BDK_CCS_TAD_CONST -1,-1,-1,-1

/**
 * Register (RSL) ccs_tad_ctl
 *
 * CCS TAD Control Register
 * Controls TAD behavior.
 */
union bdk_ccs_tad_ctl
{
    uint64_t u;
    struct bdk_ccs_tad_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t persist_wbfl          : 3;  /**< [ 59: 57](R/W) Specifies how long until a write to MCC with persist waiting in the TAD will
                                                                 force a request to make MCC writes higher priority. 0,6,7 - disabled, 1-5 -
                                                                 between 2^([PERSIST_WBFL]+8) and 2^([PERSIST_WBFL]+9) core-clock cycles (with an
                                                                 average of 1.5*2^([PERSIST_WBFL]+8) core-clock cycles). */
        uint64_t disadrwbfl            : 1;  /**< [ 56: 56](R/W) Disable the request to make MCC writes higher priority in MCC/LMC based on
                                                                 address conflicts. See also CCS_TAD_CTL[MCCWR_THRESH] for threshold based
                                                                 priority increases. */
        uint64_t disdfill              : 1;  /**< [ 55: 55](R/W) Disable the ability for MCC to fill directly to requesting IOB/PIC in addition
                                                                 to returning the fill to the TAD. */
        uint64_t disrqhprio            : 1;  /**< [ 54: 54](R/W) Disable the ability for RQH commands arriving from IOB/AP to jump in front of
                                                                 already arrived, but pending REQ commands. */
        uint64_t sameidx_thresh        : 6;  /**< [ 53: 48](R/W) Prevents MSW from sending new commands into the TAD when the number of same
                                                                 index, different address LFBs exceeds this threshold. Should never be programmed
                                                                 above 14 or a DTG way may not be available for allocation (a fatal condition). A
                                                                 value of 9 can be used to guarantee that a LTG way is always available for
                                                                 allocation (assuming no way locking or memory paritioning is in use). */
        uint64_t disdwb                : 1;  /**< [ 47: 47](R/W) Disable the ability to "don't write back" (throw away) dirty data. When one,
                                                                 converts LFNW/LPNW commands to LFNN/LPNN commands and turns INVI commands into
                                                                 NOPs. */
        uint64_t cclk_dis              : 1;  /**< [ 46: 46](R/W) Disable power saving TAD conditional clocking. For diagnostic use only. */
        uint64_t frcnalc               : 1;  /**< [ 45: 45](R/W) When set, all cache accesses are forced to not allocate in the CCS TAD
                                                                 LTG. */
        uint64_t reserved_40_44        : 5;
        uint64_t exrq1                 : 5;  /**< [ 39: 35](R/W) Extra LFBs to reserve for locally generated, priority one requests. None are
                                                                 reserved for functional correctness. This is the priority used by the AP for
                                                                 I-stream requests to the TAD. */
        uint64_t exrq2                 : 5;  /**< [ 34: 30](R/W) Extra LFBs to reserve for locally generated, priority two requests. None are
                                                                 reserved for functional correctness. This is the priority used by the IOB for
                                                                 high-priority requests to the TAD. */
        uint64_t exrrq                 : 5;  /**< [ 29: 25](RAZ) Reserved.
                                                                 Internal:
                                                                 For CCPI enabled chips only. Extra LFBs to reserve for remote CCPI requests
                                                                 beyond the one required for CCPI protocol functional correctness. Ignored if
                                                                 CCS_CCPI_CTL[ENAOCI] = 0. */
        uint64_t exfwd                 : 5;  /**< [ 24: 20](RAZ) Reserved.
                                                                 Internal:
                                                                 For CCPI enabled chips only. Extra LFBs to reserve for Fxxx CCPI commands beyond
                                                                 the one required for CCPI protocol functional correctness. Ignored if
                                                                 CCS_CCPI_CTL[ENAOCI] = 0. */
        uint64_t exvic                 : 5;  /**< [ 19: 15](RAZ) Reserved.
                                                                 Internal:
                                                                 For CCPI enabled chips only. Extra LFBs to reserve for VICx CCPI commands beyond
                                                                 the one required for CCPI protocol functional correctness. Ignored if
                                                                 CCS_CCPI_CTL[ENAOCI] = 0. */
        uint64_t exlvc                 : 5;  /**< [ 14: 10](R/W) Extra LFBs to reserve for VICx IOB commands beyond the one required for functional
                                                                 correctness. */
        uint64_t mccwr_thresh          : 5;  /**< [  9:  5](R/W) MCC write threshold. When the number of LFBs with MCC writes waiting for
                                                                 responses from the MCC exceeds this number, the CCU TAD requests an increase in
                                                                 the priority of all its write operations in the MCC/LMC (0-23 as expected, 24-31
                                                                 effectively disables priority increase based on threshold). See also
                                                                 CCS_TAD_CTL[DISADRWBFL] for address based MCC write priority increase. */
        uint64_t maxlfb                : 5;  /**< [  4:  0](R/W) Maximum VABs/LFBs in use at once (0, 25-31 interpreted as 24, 1-24 as
                                                                 expected). Must be \>= (2 + CCS_TAD_CTL[EXRQ1/2,EXLVC]). */
#else /* Word 0 - Little Endian */
        uint64_t maxlfb                : 5;  /**< [  4:  0](R/W) Maximum VABs/LFBs in use at once (0, 25-31 interpreted as 24, 1-24 as
                                                                 expected). Must be \>= (2 + CCS_TAD_CTL[EXRQ1/2,EXLVC]). */
        uint64_t mccwr_thresh          : 5;  /**< [  9:  5](R/W) MCC write threshold. When the number of LFBs with MCC writes waiting for
                                                                 responses from the MCC exceeds this number, the CCU TAD requests an increase in
                                                                 the priority of all its write operations in the MCC/LMC (0-23 as expected, 24-31
                                                                 effectively disables priority increase based on threshold). See also
                                                                 CCS_TAD_CTL[DISADRWBFL] for address based MCC write priority increase. */
        uint64_t exlvc                 : 5;  /**< [ 14: 10](R/W) Extra LFBs to reserve for VICx IOB commands beyond the one required for functional
                                                                 correctness. */
        uint64_t exvic                 : 5;  /**< [ 19: 15](RAZ) Reserved.
                                                                 Internal:
                                                                 For CCPI enabled chips only. Extra LFBs to reserve for VICx CCPI commands beyond
                                                                 the one required for CCPI protocol functional correctness. Ignored if
                                                                 CCS_CCPI_CTL[ENAOCI] = 0. */
        uint64_t exfwd                 : 5;  /**< [ 24: 20](RAZ) Reserved.
                                                                 Internal:
                                                                 For CCPI enabled chips only. Extra LFBs to reserve for Fxxx CCPI commands beyond
                                                                 the one required for CCPI protocol functional correctness. Ignored if
                                                                 CCS_CCPI_CTL[ENAOCI] = 0. */
        uint64_t exrrq                 : 5;  /**< [ 29: 25](RAZ) Reserved.
                                                                 Internal:
                                                                 For CCPI enabled chips only. Extra LFBs to reserve for remote CCPI requests
                                                                 beyond the one required for CCPI protocol functional correctness. Ignored if
                                                                 CCS_CCPI_CTL[ENAOCI] = 0. */
        uint64_t exrq2                 : 5;  /**< [ 34: 30](R/W) Extra LFBs to reserve for locally generated, priority two requests. None are
                                                                 reserved for functional correctness. This is the priority used by the IOB for
                                                                 high-priority requests to the TAD. */
        uint64_t exrq1                 : 5;  /**< [ 39: 35](R/W) Extra LFBs to reserve for locally generated, priority one requests. None are
                                                                 reserved for functional correctness. This is the priority used by the AP for
                                                                 I-stream requests to the TAD. */
        uint64_t reserved_40_44        : 5;
        uint64_t frcnalc               : 1;  /**< [ 45: 45](R/W) When set, all cache accesses are forced to not allocate in the CCS TAD
                                                                 LTG. */
        uint64_t cclk_dis              : 1;  /**< [ 46: 46](R/W) Disable power saving TAD conditional clocking. For diagnostic use only. */
        uint64_t disdwb                : 1;  /**< [ 47: 47](R/W) Disable the ability to "don't write back" (throw away) dirty data. When one,
                                                                 converts LFNW/LPNW commands to LFNN/LPNN commands and turns INVI commands into
                                                                 NOPs. */
        uint64_t sameidx_thresh        : 6;  /**< [ 53: 48](R/W) Prevents MSW from sending new commands into the TAD when the number of same
                                                                 index, different address LFBs exceeds this threshold. Should never be programmed
                                                                 above 14 or a DTG way may not be available for allocation (a fatal condition). A
                                                                 value of 9 can be used to guarantee that a LTG way is always available for
                                                                 allocation (assuming no way locking or memory paritioning is in use). */
        uint64_t disrqhprio            : 1;  /**< [ 54: 54](R/W) Disable the ability for RQH commands arriving from IOB/AP to jump in front of
                                                                 already arrived, but pending REQ commands. */
        uint64_t disdfill              : 1;  /**< [ 55: 55](R/W) Disable the ability for MCC to fill directly to requesting IOB/PIC in addition
                                                                 to returning the fill to the TAD. */
        uint64_t disadrwbfl            : 1;  /**< [ 56: 56](R/W) Disable the request to make MCC writes higher priority in MCC/LMC based on
                                                                 address conflicts. See also CCS_TAD_CTL[MCCWR_THRESH] for threshold based
                                                                 priority increases. */
        uint64_t persist_wbfl          : 3;  /**< [ 59: 57](R/W) Specifies how long until a write to MCC with persist waiting in the TAD will
                                                                 force a request to make MCC writes higher priority. 0,6,7 - disabled, 1-5 -
                                                                 between 2^([PERSIST_WBFL]+8) and 2^([PERSIST_WBFL]+9) core-clock cycles (with an
                                                                 average of 1.5*2^([PERSIST_WBFL]+8) core-clock cycles). */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ccs_tad_ctl_s cn; */
};
typedef union bdk_ccs_tad_ctl bdk_ccs_tad_ctl_t;

#define BDK_CCS_TAD_CTL BDK_CCS_TAD_CTL_FUNC()
static inline uint64_t BDK_CCS_TAD_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CCS_TAD_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e087100018ll;
    __bdk_csr_fatal("CCS_TAD_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CCS_TAD_CTL bdk_ccs_tad_ctl_t
#define bustype_BDK_CCS_TAD_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_CCS_TAD_CTL "CCS_TAD_CTL"
#define device_bar_BDK_CCS_TAD_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_CCS_TAD_CTL 0
#define arguments_BDK_CCS_TAD_CTL -1,-1,-1,-1

#endif /* __BDK_CSRS_CCS_H__ */
