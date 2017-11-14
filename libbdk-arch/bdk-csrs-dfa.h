#ifndef __BDK_CSRS_DFA_H__
#define __BDK_CSRS_DFA_H__
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
 * Cavium DFA.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration dfa_bar_e
 *
 * HFA Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_DFA_BAR_E_DFA_PF_BAR0 (0x846000000000ll)
#define BDK_DFA_BAR_E_DFA_PF_BAR0_SIZE 0x800000000ull
#define BDK_DFA_BAR_E_DFA_PF_BAR4 (0x846a00000000ll)
#define BDK_DFA_BAR_E_DFA_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration dfa_int_vec_e
 *
 * HFA MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_DFA_INT_VEC_E_DONE (1)
#define BDK_DFA_INT_VEC_E_ERR (0)

/**
 * Structure dfa_cq_s
 *
 * INTERNAL: HFA Completion Queue Structure
 *
 * This structure specifies the HFA completion queue.
 * The CQ contains the RPTRs of the instructions that HFA has completed processing.
 * Software would generally wait for an interrupt caused by
 * DFA_INT_DONE[INST_DONE], then read this buffer and process result buffers
 * which have their RPTR listed in this queue.
 *
 * Internal:
 * Defeatured.
 */
union bdk_dfa_cq_s
{
    uint64_t u;
    struct bdk_dfa_cq_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t rptr                  : 49; /**< [ 48:  0] RPTR IOVA from the completed instruction. */
#else /* Word 0 - Little Endian */
        uint64_t rptr                  : 49; /**< [ 48:  0] RPTR IOVA from the completed instruction. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_cq_s_s cn; */
};

/**
 * Register (NCB) dfa_asc_region#_attr
 *
 * HFA Address Space Control Region Attributes Registers
 */
union bdk_dfa_asc_regionx_attr
{
    uint64_t u;
    struct bdk_dfa_asc_regionx_attr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ns_en                 : 1;  /**< [  0:  0](SR/W) Enables nonsecure access to a region.
                                                                 If a HFA access falls outside all ASC regions, then then the cache line at
                                                                 DFA_ASC_REGION(0)_START[ADDR] will be read.
                                                                 Therefore for proper HFA access to DLC, DFA_ASC_REGION(0)_ATTR[NS_EN] must be
                                                                 enabled along with a corresponding valid DFA_ASC_REGION(0)_START[ADDR] and
                                                                 DFA_ASC_REGION(0)_END[ADDR]. */
#else /* Word 0 - Little Endian */
        uint64_t ns_en                 : 1;  /**< [  0:  0](SR/W) Enables nonsecure access to a region.
                                                                 If a HFA access falls outside all ASC regions, then then the cache line at
                                                                 DFA_ASC_REGION(0)_START[ADDR] will be read.
                                                                 Therefore for proper HFA access to DLC, DFA_ASC_REGION(0)_ATTR[NS_EN] must be
                                                                 enabled along with a corresponding valid DFA_ASC_REGION(0)_START[ADDR] and
                                                                 DFA_ASC_REGION(0)_END[ADDR]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_asc_regionx_attr_s cn; */
};
typedef union bdk_dfa_asc_regionx_attr bdk_dfa_asc_regionx_attr_t;

static inline uint64_t BDK_DFA_ASC_REGIONX_ATTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_ASC_REGIONX_ATTR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8462000001c0ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("DFA_ASC_REGIONX_ATTR", 1, a, 0, 0, 0);
}

#define typedef_BDK_DFA_ASC_REGIONX_ATTR(a) bdk_dfa_asc_regionx_attr_t
#define bustype_BDK_DFA_ASC_REGIONX_ATTR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_ASC_REGIONX_ATTR(a) "DFA_ASC_REGIONX_ATTR"
#define device_bar_BDK_DFA_ASC_REGIONX_ATTR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_ASC_REGIONX_ATTR(a) (a)
#define arguments_BDK_DFA_ASC_REGIONX_ATTR(a) (a),-1,-1,-1

/**
 * Register (NCB) dfa_asc_region#_end
 *
 * HFA Address Space Control Region End Address Registers
 */
union bdk_dfa_asc_regionx_end
{
    uint64_t u;
    struct bdk_dfa_asc_regionx_end_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 29; /**< [ 48: 20](SR/W) Virtual address \<48:20\> marking the inclusive end of the corresponding ASC region.
                                                                 Note that the region includes this address.
                                                                 Software must ensure that regions do not overlap.
                                                                 To specify an empty region, clear [NS_EN] fields of
                                                                 the corresponding DFA_ASC_REGION()_ATTR register. */
        uint64_t reserved_0_19         : 20;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_19         : 20;
        uint64_t addr                  : 29; /**< [ 48: 20](SR/W) Virtual address \<48:20\> marking the inclusive end of the corresponding ASC region.
                                                                 Note that the region includes this address.
                                                                 Software must ensure that regions do not overlap.
                                                                 To specify an empty region, clear [NS_EN] fields of
                                                                 the corresponding DFA_ASC_REGION()_ATTR register. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_asc_regionx_end_s cn; */
};
typedef union bdk_dfa_asc_regionx_end bdk_dfa_asc_regionx_end_t;

static inline uint64_t BDK_DFA_ASC_REGIONX_END(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_ASC_REGIONX_END(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8462000001a0ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("DFA_ASC_REGIONX_END", 1, a, 0, 0, 0);
}

#define typedef_BDK_DFA_ASC_REGIONX_END(a) bdk_dfa_asc_regionx_end_t
#define bustype_BDK_DFA_ASC_REGIONX_END(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_ASC_REGIONX_END(a) "DFA_ASC_REGIONX_END"
#define device_bar_BDK_DFA_ASC_REGIONX_END(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_ASC_REGIONX_END(a) (a)
#define arguments_BDK_DFA_ASC_REGIONX_END(a) (a),-1,-1,-1

/**
 * Register (NCB) dfa_asc_region#_offset
 *
 * HFA Address Space Control Region Offset Registers
 */
union bdk_dfa_asc_regionx_offset
{
    uint64_t u;
    struct bdk_dfa_asc_regionx_offset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t offset                : 29; /**< [ 48: 20](SR/W) Offset \<48:20\> added to the HFA virtual address which matches the corresponding
                                                                 DFA_ASC_REGION()_START[ADDR] and DFA_ASC_REGION()_END[ADDR] to convert it into
                                                                 into an LMC address.

                                                                 This offset should include any offset needed to convert a guest intermediate
                                                                 physical address to a physical address that would normally be computed by the
                                                                 SMMU (which is being bypassed for these HFA accesses).

                                                                 This offset should not include a nonsecure offset, as LMC()_NS_CTL[ADR_OFFSET]
                                                                 is applied to these transactions by LMC. */
        uint64_t reserved_0_19         : 20;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_19         : 20;
        uint64_t offset                : 29; /**< [ 48: 20](SR/W) Offset \<48:20\> added to the HFA virtual address which matches the corresponding
                                                                 DFA_ASC_REGION()_START[ADDR] and DFA_ASC_REGION()_END[ADDR] to convert it into
                                                                 into an LMC address.

                                                                 This offset should include any offset needed to convert a guest intermediate
                                                                 physical address to a physical address that would normally be computed by the
                                                                 SMMU (which is being bypassed for these HFA accesses).

                                                                 This offset should not include a nonsecure offset, as LMC()_NS_CTL[ADR_OFFSET]
                                                                 is applied to these transactions by LMC. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_asc_regionx_offset_s cn; */
};
typedef union bdk_dfa_asc_regionx_offset bdk_dfa_asc_regionx_offset_t;

static inline uint64_t BDK_DFA_ASC_REGIONX_OFFSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_ASC_REGIONX_OFFSET(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8462000001e0ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("DFA_ASC_REGIONX_OFFSET", 1, a, 0, 0, 0);
}

#define typedef_BDK_DFA_ASC_REGIONX_OFFSET(a) bdk_dfa_asc_regionx_offset_t
#define bustype_BDK_DFA_ASC_REGIONX_OFFSET(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_ASC_REGIONX_OFFSET(a) "DFA_ASC_REGIONX_OFFSET"
#define device_bar_BDK_DFA_ASC_REGIONX_OFFSET(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_ASC_REGIONX_OFFSET(a) (a)
#define arguments_BDK_DFA_ASC_REGIONX_OFFSET(a) (a),-1,-1,-1

/**
 * Register (NCB) dfa_asc_region#_start
 *
 * HFA Address Space Control Region Start Address Registers
 */
union bdk_dfa_asc_regionx_start
{
    uint64_t u;
    struct bdk_dfa_asc_regionx_start_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 29; /**< [ 48: 20](SR/W) Virtual address \<48:20\> marking the start of the corresponding ASC region.
                                                                 Software must ensure that regions do not overlap. */
        uint64_t reserved_0_19         : 20;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_19         : 20;
        uint64_t addr                  : 29; /**< [ 48: 20](SR/W) Virtual address \<48:20\> marking the start of the corresponding ASC region.
                                                                 Software must ensure that regions do not overlap. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_asc_regionx_start_s cn; */
};
typedef union bdk_dfa_asc_regionx_start bdk_dfa_asc_regionx_start_t;

static inline uint64_t BDK_DFA_ASC_REGIONX_START(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_ASC_REGIONX_START(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x846200000180ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("DFA_ASC_REGIONX_START", 1, a, 0, 0, 0);
}

#define typedef_BDK_DFA_ASC_REGIONX_START(a) bdk_dfa_asc_regionx_start_t
#define bustype_BDK_DFA_ASC_REGIONX_START(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_ASC_REGIONX_START(a) "DFA_ASC_REGIONX_START"
#define device_bar_BDK_DFA_ASC_REGIONX_START(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_ASC_REGIONX_START(a) (a)
#define arguments_BDK_DFA_ASC_REGIONX_START(a) (a),-1,-1,-1

/**
 * Register (NCB) dfa_bist0
 *
 * HFA BIST Status (per-DTC) Register
 * This register shows the result of the BIST run on the HFA (per-DTC).
 * 1 = BIST error, 0 = BIST passed, is in progress, or never ran.
 */
union bdk_dfa_bist0
{
    uint64_t u;
    struct bdk_dfa_bist0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t mrp                   : 2;  /**< [ 29: 28](RO/H) BIST results for MRP RAM(s) (per-DLC). */
        uint64_t gfb                   : 4;  /**< [ 27: 24](RO/H) BIST results for GFB RAMs (per cluster). */
        uint64_t stx3                  : 2;  /**< [ 23: 22](RO/H) BIST Results for STX3 RAM(s). */
        uint64_t stx2                  : 2;  /**< [ 21: 20](RO/H) BIST results for STX2 RAMs. */
        uint64_t stx1                  : 2;  /**< [ 19: 18](RO/H) BIST results for STX1 RAMs. */
        uint64_t stx                   : 2;  /**< [ 17: 16](RO/H) BIST results for STX0 RAMs. */
        uint64_t dtx3                  : 2;  /**< [ 15: 14](RO/H) BIST Results for DTX3 RAM(s). */
        uint64_t dtx2                  : 2;  /**< [ 13: 12](RO/H) BIST results for DTX2 RAMs. */
        uint64_t dtx1                  : 2;  /**< [ 11: 10](RO/H) BIST results for DTX1 RAMs. */
        uint64_t dtx                   : 2;  /**< [  9:  8](RO/H) BIST results for DTX0 RAMs. */
        uint64_t rdf                   : 4;  /**< [  7:  4](RO/H) BIST results for RWB RAMs (per cluster). */
        uint64_t pdb                   : 4;  /**< [  3:  0](RO/H) BIST results for PDB RAMs (per cluster). */
#else /* Word 0 - Little Endian */
        uint64_t pdb                   : 4;  /**< [  3:  0](RO/H) BIST results for PDB RAMs (per cluster). */
        uint64_t rdf                   : 4;  /**< [  7:  4](RO/H) BIST results for RWB RAMs (per cluster). */
        uint64_t dtx                   : 2;  /**< [  9:  8](RO/H) BIST results for DTX0 RAMs. */
        uint64_t dtx1                  : 2;  /**< [ 11: 10](RO/H) BIST results for DTX1 RAMs. */
        uint64_t dtx2                  : 2;  /**< [ 13: 12](RO/H) BIST results for DTX2 RAMs. */
        uint64_t dtx3                  : 2;  /**< [ 15: 14](RO/H) BIST Results for DTX3 RAM(s). */
        uint64_t stx                   : 2;  /**< [ 17: 16](RO/H) BIST results for STX0 RAMs. */
        uint64_t stx1                  : 2;  /**< [ 19: 18](RO/H) BIST results for STX1 RAMs. */
        uint64_t stx2                  : 2;  /**< [ 21: 20](RO/H) BIST results for STX2 RAMs. */
        uint64_t stx3                  : 2;  /**< [ 23: 22](RO/H) BIST Results for STX3 RAM(s). */
        uint64_t gfb                   : 4;  /**< [ 27: 24](RO/H) BIST results for GFB RAMs (per cluster). */
        uint64_t mrp                   : 2;  /**< [ 29: 28](RO/H) BIST results for MRP RAM(s) (per-DLC). */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    struct bdk_dfa_bist0_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t reserved_30_31        : 2;
        uint64_t mrp                   : 2;  /**< [ 29: 28](RO/H) BIST results for MRP RAM(s) (per-DLC). */
        uint64_t gfb                   : 4;  /**< [ 27: 24](RO/H) BIST results for GFB RAMs (per cluster). */
        uint64_t stx3                  : 2;  /**< [ 23: 22](RO/H) BIST Results for STX3 RAM(s). */
        uint64_t stx2                  : 2;  /**< [ 21: 20](RO/H) BIST results for STX2 RAMs. */
        uint64_t stx1                  : 2;  /**< [ 19: 18](RO/H) BIST results for STX1 RAMs. */
        uint64_t stx                   : 2;  /**< [ 17: 16](RO/H) BIST results for STX0 RAMs. */
        uint64_t dtx3                  : 2;  /**< [ 15: 14](RO/H) BIST Results for DTX3 RAM(s). */
        uint64_t dtx2                  : 2;  /**< [ 13: 12](RO/H) BIST results for DTX2 RAMs. */
        uint64_t dtx1                  : 2;  /**< [ 11: 10](RO/H) BIST results for DTX1 RAMs. */
        uint64_t dtx                   : 2;  /**< [  9:  8](RO/H) BIST results for DTX0 RAMs. */
        uint64_t rdf                   : 4;  /**< [  7:  4](RO/H) BIST results for RWB RAMs (per cluster). */
        uint64_t pdb                   : 4;  /**< [  3:  0](RO/H) BIST results for PDB RAMs (per cluster). */
#else /* Word 0 - Little Endian */
        uint64_t pdb                   : 4;  /**< [  3:  0](RO/H) BIST results for PDB RAMs (per cluster). */
        uint64_t rdf                   : 4;  /**< [  7:  4](RO/H) BIST results for RWB RAMs (per cluster). */
        uint64_t dtx                   : 2;  /**< [  9:  8](RO/H) BIST results for DTX0 RAMs. */
        uint64_t dtx1                  : 2;  /**< [ 11: 10](RO/H) BIST results for DTX1 RAMs. */
        uint64_t dtx2                  : 2;  /**< [ 13: 12](RO/H) BIST results for DTX2 RAMs. */
        uint64_t dtx3                  : 2;  /**< [ 15: 14](RO/H) BIST Results for DTX3 RAM(s). */
        uint64_t stx                   : 2;  /**< [ 17: 16](RO/H) BIST results for STX0 RAMs. */
        uint64_t stx1                  : 2;  /**< [ 19: 18](RO/H) BIST results for STX1 RAMs. */
        uint64_t stx2                  : 2;  /**< [ 21: 20](RO/H) BIST results for STX2 RAMs. */
        uint64_t stx3                  : 2;  /**< [ 23: 22](RO/H) BIST Results for STX3 RAM(s). */
        uint64_t gfb                   : 4;  /**< [ 27: 24](RO/H) BIST results for GFB RAMs (per cluster). */
        uint64_t mrp                   : 2;  /**< [ 29: 28](RO/H) BIST results for MRP RAM(s) (per-DLC). */
        uint64_t reserved_30_31        : 2;
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn;
};
typedef union bdk_dfa_bist0 bdk_dfa_bist0_t;

#define BDK_DFA_BIST0 BDK_DFA_BIST0_FUNC()
static inline uint64_t BDK_DFA_BIST0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_BIST0_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000007f0ll;
    __bdk_csr_fatal("DFA_BIST0", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_BIST0 bdk_dfa_bist0_t
#define bustype_BDK_DFA_BIST0 BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_BIST0 "DFA_BIST0"
#define device_bar_BDK_DFA_BIST0 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_BIST0 0
#define arguments_BDK_DFA_BIST0 -1,-1,-1,-1

/**
 * Register (NCB) dfa_bist1
 *
 * HFA Bist Status (Globals) Register
 * This register shows the result of the BIST run on the HFA (globals).
 * 1 = BIST error, 0 = BIST passed, is in progress, or never ran.
 */
union bdk_dfa_bist1
{
    uint64_t u;
    struct bdk_dfa_bist1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t dc3ram3               : 1;  /**< [ 23: 23](RO/H) Cluster 3 BIST results for RAM3 RAM. */
        uint64_t dc3ram2               : 1;  /**< [ 22: 22](RO/H) Cluster 3 BIST results for RAM2 RAM. */
        uint64_t dc3ram1               : 1;  /**< [ 21: 21](RO/H) Cluster 3 BIST results for RAM1 RAM. */
        uint64_t dlc1ram               : 1;  /**< [ 20: 20](RO/H) DLC1 BIST results. */
        uint64_t dlc0ram               : 1;  /**< [ 19: 19](RO/H) DLC0 BIST results. */
        uint64_t dc2ram3               : 1;  /**< [ 18: 18](RO/H) Cluster 2 BIST results for RAM3 RAM. */
        uint64_t dc2ram2               : 1;  /**< [ 17: 17](RO/H) Cluster 2 BIST results for RAM2 RAM. */
        uint64_t dc2ram1               : 1;  /**< [ 16: 16](RO/H) Cluster 2 BIST results for RAM1 RAM. */
        uint64_t dc1ram3               : 1;  /**< [ 15: 15](RO/H) Cluster 1 BIST results for RAM3 RAM. */
        uint64_t dc1ram2               : 1;  /**< [ 14: 14](RO/H) Cluster 1 BIST results for RAM2 RAM. */
        uint64_t dc1ram1               : 1;  /**< [ 13: 13](RO/H) Cluster 1 BIST results for RAM1 RAM. */
        uint64_t ram3                  : 1;  /**< [ 12: 12](RO/H) Cluster 0 BIST results for RAM3 RAM. */
        uint64_t ram2                  : 1;  /**< [ 11: 11](RO/H) Cluster 0 BIST results for RAM2 RAM. */
        uint64_t ram1                  : 1;  /**< [ 10: 10](RO/H) Cluster 0 BIST results for RAM1 RAM. */
        uint64_t crq                   : 1;  /**< [  9:  9](RO/H) BIST results for CRQ RAM. */
        uint64_t gutv                  : 1;  /**< [  8:  8](RO/H) BIST results for GUTV RAM. */
        uint64_t gutp                  : 4;  /**< [  7:  4](RO/H) BIST results for GUTP RAMs (per-cluster). */
        uint64_t ncd                   : 1;  /**< [  3:  3](RO/H) BIST results for NCD RAM. */
        uint64_t gif                   : 1;  /**< [  2:  2](RO/H) BIST results for GIF RAM. */
        uint64_t gib                   : 1;  /**< [  1:  1](RO/H) BIST results for GIB RAM. */
        uint64_t gfu                   : 1;  /**< [  0:  0](RO/H) BIST results for GFU RAM. */
#else /* Word 0 - Little Endian */
        uint64_t gfu                   : 1;  /**< [  0:  0](RO/H) BIST results for GFU RAM. */
        uint64_t gib                   : 1;  /**< [  1:  1](RO/H) BIST results for GIB RAM. */
        uint64_t gif                   : 1;  /**< [  2:  2](RO/H) BIST results for GIF RAM. */
        uint64_t ncd                   : 1;  /**< [  3:  3](RO/H) BIST results for NCD RAM. */
        uint64_t gutp                  : 4;  /**< [  7:  4](RO/H) BIST results for GUTP RAMs (per-cluster). */
        uint64_t gutv                  : 1;  /**< [  8:  8](RO/H) BIST results for GUTV RAM. */
        uint64_t crq                   : 1;  /**< [  9:  9](RO/H) BIST results for CRQ RAM. */
        uint64_t ram1                  : 1;  /**< [ 10: 10](RO/H) Cluster 0 BIST results for RAM1 RAM. */
        uint64_t ram2                  : 1;  /**< [ 11: 11](RO/H) Cluster 0 BIST results for RAM2 RAM. */
        uint64_t ram3                  : 1;  /**< [ 12: 12](RO/H) Cluster 0 BIST results for RAM3 RAM. */
        uint64_t dc1ram1               : 1;  /**< [ 13: 13](RO/H) Cluster 1 BIST results for RAM1 RAM. */
        uint64_t dc1ram2               : 1;  /**< [ 14: 14](RO/H) Cluster 1 BIST results for RAM2 RAM. */
        uint64_t dc1ram3               : 1;  /**< [ 15: 15](RO/H) Cluster 1 BIST results for RAM3 RAM. */
        uint64_t dc2ram1               : 1;  /**< [ 16: 16](RO/H) Cluster 2 BIST results for RAM1 RAM. */
        uint64_t dc2ram2               : 1;  /**< [ 17: 17](RO/H) Cluster 2 BIST results for RAM2 RAM. */
        uint64_t dc2ram3               : 1;  /**< [ 18: 18](RO/H) Cluster 2 BIST results for RAM3 RAM. */
        uint64_t dlc0ram               : 1;  /**< [ 19: 19](RO/H) DLC0 BIST results. */
        uint64_t dlc1ram               : 1;  /**< [ 20: 20](RO/H) DLC1 BIST results. */
        uint64_t dc3ram1               : 1;  /**< [ 21: 21](RO/H) Cluster 3 BIST results for RAM1 RAM. */
        uint64_t dc3ram2               : 1;  /**< [ 22: 22](RO/H) Cluster 3 BIST results for RAM2 RAM. */
        uint64_t dc3ram3               : 1;  /**< [ 23: 23](RO/H) Cluster 3 BIST results for RAM3 RAM. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_bist1_s cn; */
};
typedef union bdk_dfa_bist1 bdk_dfa_bist1_t;

#define BDK_DFA_BIST1 BDK_DFA_BIST1_FUNC()
static inline uint64_t BDK_DFA_BIST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_BIST1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000007f8ll;
    __bdk_csr_fatal("DFA_BIST1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_BIST1 bdk_dfa_bist1_t
#define bustype_BDK_DFA_BIST1 BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_BIST1 "DFA_BIST1"
#define device_bar_BDK_DFA_BIST1 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_BIST1 0
#define arguments_BDK_DFA_BIST1 -1,-1,-1,-1

/**
 * Register (NCB) dfa_config
 *
 * HFA Configuration Register
 */
union bdk_dfa_config
{
    uint64_t u;
    struct bdk_dfa_config_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t dlcclear_bist         : 1;  /**< [ 10: 10](R/W) When [DLCSTART_BIST] is written 0-\>1, if [DLCCLEAR_BIST]=1, all previous DLC BIST state is
                                                                 cleared. Note the following:

                                                                 * [DLCCLEAR_BIST] must be written to 1 before [DLCSTART_BIST] is written to 1
                                                                 using a separate CSR write operation.

                                                                 * [DLCCLEAR_BIST] must not be changed after writing [DLCSTART_BIST] 0-\>1 until
                                                                 the BIST operation completes. */
        uint64_t dlcstart_bist         : 1;  /**< [  9:  9](R/W) When software writes [DLCSTART_BIST]=0-\>1, a BIST is executed for the DLC sub-block RAMs
                                                                 which contains DCLK domain asynchronous RAMs. Note the following:
                                                                 This bit should only be written after DCLK has been enabled by software and is stable.
                                                                 (See LMC initialization routine for details on how to enable the DDR3/4 memory
                                                                 (DCLK)--which requires LMC PLL init, clock divider, and proper DLL initialization
                                                                 sequence.) */
        uint64_t repl_ena              : 1;  /**< [  8:  8](R/W) Replication mode enable.
                                                                 This is used by the memory controller to support graph data in multiple ports (or port
                                                                 sets), so that the least full port can be selected to minimize latency effects.
                                                                 Software Note: Using this mode requires the HFA software compiler and HFA driver to be
                                                                 aware of the address replication changes. This involves changes to the MLOAD/GWALK HFA
                                                                 instruction format (See IWORD2.SREPL), as well as changes to node arc and metadata
                                                                 definitions which support an additional REPL field. When clear, replication mode is
                                                                 disabled, and HFA interprets HFA instructions and node-arc formats which do not have
                                                                 address replication information. */
        uint64_t reserved_6_7          : 2;
        uint64_t clmskcrip             : 2;  /**< [  5:  4](R/W/H) Cluster cripple mask. A 1 in each bit of the mask represents which HTE cluster to cripple.
                                                                 CN88XX has two clusters (therefore CLMSKCRIP\<1:0\> are used.)
                                                                 The MIO_FUS_DFA_CLMASK_CRIPPLE[1:0] fuse bits are forced into this register at reset. Any
                                                                 fuse bits that contain 1 are disallowed during a write and are always read as 1. */
        uint64_t cldtecrip             : 3;  /**< [  3:  1](R/W/H) Encoding that represents the number of HTEs to cripple for each cluster. Typically
                                                                 DTE_CLCRIP = 0, which enables all HTEs within each cluster. However, when the HFA
                                                                 performance counters are used, software may want to limit the number of HTEs per cluster
                                                                 available, as there are only four parallel performance counters.

                                                                 0 = HTE[15:0]:ON.
                                                                 1 = 1/2 = HTE[15:8]:OFF  /HTE[7:0]:ON.
                                                                 2 = 1/4 = HTE[15:12]:OFF /HTE[11:0]:ON.
                                                                 3 = 3/4 = HTE[15:4]:OFF  /HTE[3:0]:ON.
                                                                 4 = 1/8 = HTE[15:14]:OFF /HTE[13:0]:ON.
                                                                 5 = 5/8 = HTE[15:6]:OFF  /HTE[5:0]:ON.
                                                                 6 = 3/8 = HTE[15:10]:OFF /HTE[9:0]:ON.
                                                                 7 = 7/8 = HTE[15:2]:OFF  /HTE[1:0]:ON.

                                                                 Higher numbered HTEs are crippled first. For instance, on CN78XX (with 16 HTEs/cluster),
                                                                 if DTE_CLCRIP = 1 (1/2), then [15:8] within the cluster are crippled and only HTE numbers
                                                                 [7:0] are available.

                                                                 The MIO_FUS_DFA_NUMDTE_CRIPPLE[3:0] fuse bits are forced into this register at reset. Any
                                                                 fuse bits that contain 1 are disallowed during a write operation and are always read as 1. */
        uint64_t dteclkdis             : 1;  /**< [  0:  0](R/W) HFA clock disable source. When set, the HFA clocks for HTE (thread engine) operations are
                                                                 disabled to conserve overall chip clocking power when the HFA function is not used.
                                                                 When set, software must never issue NCB-direct CSR operations to the HFA (will result in
                                                                 NCB timeout errors).

                                                                 This should only be written to a different value during power-on software initialization.
                                                                 The MIO_FUS_DFA_DTE_DISABLE fuse bit is forced into this register at reset. If the fuse
                                                                 bit contains 1, write operations to DTECLKDIS are disallowed and are always read as 1. */
#else /* Word 0 - Little Endian */
        uint64_t dteclkdis             : 1;  /**< [  0:  0](R/W) HFA clock disable source. When set, the HFA clocks for HTE (thread engine) operations are
                                                                 disabled to conserve overall chip clocking power when the HFA function is not used.
                                                                 When set, software must never issue NCB-direct CSR operations to the HFA (will result in
                                                                 NCB timeout errors).

                                                                 This should only be written to a different value during power-on software initialization.
                                                                 The MIO_FUS_DFA_DTE_DISABLE fuse bit is forced into this register at reset. If the fuse
                                                                 bit contains 1, write operations to DTECLKDIS are disallowed and are always read as 1. */
        uint64_t cldtecrip             : 3;  /**< [  3:  1](R/W/H) Encoding that represents the number of HTEs to cripple for each cluster. Typically
                                                                 DTE_CLCRIP = 0, which enables all HTEs within each cluster. However, when the HFA
                                                                 performance counters are used, software may want to limit the number of HTEs per cluster
                                                                 available, as there are only four parallel performance counters.

                                                                 0 = HTE[15:0]:ON.
                                                                 1 = 1/2 = HTE[15:8]:OFF  /HTE[7:0]:ON.
                                                                 2 = 1/4 = HTE[15:12]:OFF /HTE[11:0]:ON.
                                                                 3 = 3/4 = HTE[15:4]:OFF  /HTE[3:0]:ON.
                                                                 4 = 1/8 = HTE[15:14]:OFF /HTE[13:0]:ON.
                                                                 5 = 5/8 = HTE[15:6]:OFF  /HTE[5:0]:ON.
                                                                 6 = 3/8 = HTE[15:10]:OFF /HTE[9:0]:ON.
                                                                 7 = 7/8 = HTE[15:2]:OFF  /HTE[1:0]:ON.

                                                                 Higher numbered HTEs are crippled first. For instance, on CN78XX (with 16 HTEs/cluster),
                                                                 if DTE_CLCRIP = 1 (1/2), then [15:8] within the cluster are crippled and only HTE numbers
                                                                 [7:0] are available.

                                                                 The MIO_FUS_DFA_NUMDTE_CRIPPLE[3:0] fuse bits are forced into this register at reset. Any
                                                                 fuse bits that contain 1 are disallowed during a write operation and are always read as 1. */
        uint64_t clmskcrip             : 2;  /**< [  5:  4](R/W/H) Cluster cripple mask. A 1 in each bit of the mask represents which HTE cluster to cripple.
                                                                 CN88XX has two clusters (therefore CLMSKCRIP\<1:0\> are used.)
                                                                 The MIO_FUS_DFA_CLMASK_CRIPPLE[1:0] fuse bits are forced into this register at reset. Any
                                                                 fuse bits that contain 1 are disallowed during a write and are always read as 1. */
        uint64_t reserved_6_7          : 2;
        uint64_t repl_ena              : 1;  /**< [  8:  8](R/W) Replication mode enable.
                                                                 This is used by the memory controller to support graph data in multiple ports (or port
                                                                 sets), so that the least full port can be selected to minimize latency effects.
                                                                 Software Note: Using this mode requires the HFA software compiler and HFA driver to be
                                                                 aware of the address replication changes. This involves changes to the MLOAD/GWALK HFA
                                                                 instruction format (See IWORD2.SREPL), as well as changes to node arc and metadata
                                                                 definitions which support an additional REPL field. When clear, replication mode is
                                                                 disabled, and HFA interprets HFA instructions and node-arc formats which do not have
                                                                 address replication information. */
        uint64_t dlcstart_bist         : 1;  /**< [  9:  9](R/W) When software writes [DLCSTART_BIST]=0-\>1, a BIST is executed for the DLC sub-block RAMs
                                                                 which contains DCLK domain asynchronous RAMs. Note the following:
                                                                 This bit should only be written after DCLK has been enabled by software and is stable.
                                                                 (See LMC initialization routine for details on how to enable the DDR3/4 memory
                                                                 (DCLK)--which requires LMC PLL init, clock divider, and proper DLL initialization
                                                                 sequence.) */
        uint64_t dlcclear_bist         : 1;  /**< [ 10: 10](R/W) When [DLCSTART_BIST] is written 0-\>1, if [DLCCLEAR_BIST]=1, all previous DLC BIST state is
                                                                 cleared. Note the following:

                                                                 * [DLCCLEAR_BIST] must be written to 1 before [DLCSTART_BIST] is written to 1
                                                                 using a separate CSR write operation.

                                                                 * [DLCCLEAR_BIST] must not be changed after writing [DLCSTART_BIST] 0-\>1 until
                                                                 the BIST operation completes. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_config_s cn; */
};
typedef union bdk_dfa_config bdk_dfa_config_t;

#define BDK_DFA_CONFIG BDK_DFA_CONFIG_FUNC()
static inline uint64_t BDK_DFA_CONFIG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_CONFIG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000000ll;
    __bdk_csr_fatal("DFA_CONFIG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_CONFIG bdk_dfa_config_t
#define bustype_BDK_DFA_CONFIG BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_CONFIG "DFA_CONFIG"
#define device_bar_BDK_DFA_CONFIG 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_CONFIG 0
#define arguments_BDK_DFA_CONFIG -1,-1,-1,-1

/**
 * Register (NCB) dfa_control
 *
 * HFA Control Register
 */
union bdk_dfa_control
{
    uint64_t u;
    struct bdk_dfa_control_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t sbdnum                : 5;  /**< [ 10:  6](R/W) Reserved.
                                                                 Internal:
                                                                 DFA Scoreboard debug control. Selects which DFA scoreboard
                                                                 entry is latched into the DFA_SBD_DBG[0-3] registers. */
        uint64_t sbdlck                : 1;  /**< [  5:  5](R/W) Reserved.
                                                                 Internal:
                                                                 DFA Scoreboard LOCK stribe. When written with a '1', the DFA
                                                                 Scoreboard Debug registers (DFA_SBD_DBG[0-3]) are all locked down. This allows software to
                                                                 lock down the contents of the entire SBD for a single instant in time. All subsequent
                                                                 read operations of the DFA scoreboard registers will return the data from that instant in
                                                                 time. */
        uint64_t reserved_3_4          : 2;
        uint64_t pmode                 : 1;  /**< [  2:  2](R/W) Reserved.
                                                                 Internal:
                                                                 NCB-NRP Arbiter Mode.
                                                                 (0=Fixed Priority {LP=WQF,DFF,HP=RGF}/1=RR.
                                                                 NOTE: This should only be written to a different value during power-on software
                                                                 initialization. */
        uint64_t qmode                 : 1;  /**< [  1:  1](R/W) Reserved.
                                                                 Internal:
                                                                 NCB-NRQ Arbiter Mode.
                                                                 (0=Fixed Priority {LP=IRF,RWF,PRF,HP=GRF}/1=RR.
                                                                 NOTE: This should only be written to a different value during power-on software
                                                                 initialization. */
        uint64_t imode                 : 1;  /**< [  0:  0](R/W) Reserved.
                                                                 Internal:
                                                                 NCB-Inbound Arbiter.
                                                                 (0=FP {LP=NRQ,HP=NRP}, 1=RR).
                                                                 NOTE: This should only be written to a different value during power-on software
                                                                 initialization. */
#else /* Word 0 - Little Endian */
        uint64_t imode                 : 1;  /**< [  0:  0](R/W) Reserved.
                                                                 Internal:
                                                                 NCB-Inbound Arbiter.
                                                                 (0=FP {LP=NRQ,HP=NRP}, 1=RR).
                                                                 NOTE: This should only be written to a different value during power-on software
                                                                 initialization. */
        uint64_t qmode                 : 1;  /**< [  1:  1](R/W) Reserved.
                                                                 Internal:
                                                                 NCB-NRQ Arbiter Mode.
                                                                 (0=Fixed Priority {LP=IRF,RWF,PRF,HP=GRF}/1=RR.
                                                                 NOTE: This should only be written to a different value during power-on software
                                                                 initialization. */
        uint64_t pmode                 : 1;  /**< [  2:  2](R/W) Reserved.
                                                                 Internal:
                                                                 NCB-NRP Arbiter Mode.
                                                                 (0=Fixed Priority {LP=WQF,DFF,HP=RGF}/1=RR.
                                                                 NOTE: This should only be written to a different value during power-on software
                                                                 initialization. */
        uint64_t reserved_3_4          : 2;
        uint64_t sbdlck                : 1;  /**< [  5:  5](R/W) Reserved.
                                                                 Internal:
                                                                 DFA Scoreboard LOCK stribe. When written with a '1', the DFA
                                                                 Scoreboard Debug registers (DFA_SBD_DBG[0-3]) are all locked down. This allows software to
                                                                 lock down the contents of the entire SBD for a single instant in time. All subsequent
                                                                 read operations of the DFA scoreboard registers will return the data from that instant in
                                                                 time. */
        uint64_t sbdnum                : 5;  /**< [ 10:  6](R/W) Reserved.
                                                                 Internal:
                                                                 DFA Scoreboard debug control. Selects which DFA scoreboard
                                                                 entry is latched into the DFA_SBD_DBG[0-3] registers. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_control_s cn; */
};
typedef union bdk_dfa_control bdk_dfa_control_t;

#define BDK_DFA_CONTROL BDK_DFA_CONTROL_FUNC()
static inline uint64_t BDK_DFA_CONTROL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_CONTROL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000020ll;
    __bdk_csr_fatal("DFA_CONTROL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_CONTROL bdk_dfa_control_t
#define bustype_BDK_DFA_CONTROL BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_CONTROL "DFA_CONTROL"
#define device_bar_BDK_DFA_CONTROL 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_CONTROL 0
#define arguments_BDK_DFA_CONTROL -1,-1,-1,-1

/**
 * Register (NCB) dfa_cq_cfg
 *
 * INTERNAL: HFA Completion Queue Configuration Register
 *
 * Defeatured.
 */
union bdk_dfa_cq_cfg
{
    uint64_t u;
    struct bdk_dfa_cq_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cq_ena                : 1;  /**< [ 63: 63](R/W) Reserved.
                                                                 Internal:
                                                                 Deprecated. Enables the completion queue. */
        uint64_t reserved_60_62        : 3;
        uint64_t cq_size               : 4;  /**< [ 59: 56](R/W) Internal:
                                                                 Deprecated.
                                                                 Specifies completion queue buffer size in entries:
                                                                 0x0 = 256 entries.
                                                                 0x1 = 512 entries.
                                                                 0x2 = 1K entries.
                                                                 0x3 = 2K entries.
                                                                 0x4 = 4K entries.
                                                                 0x5 = 8K entries.
                                                                 0x6 = 16K entries.
                                                                 0x7 = 32K entries.
                                                                 0x8 = 64K entries.
                                                                 0x9 = 128K entries.
                                                                 0xA = 256K entries.
                                                                 0xB = 512K entries.
                                                                 0xC = 1M entries.
                                                                 0xD = Reserved.
                                                                 0xE = Reserved.
                                                                 0xF = Reserved.

                                                                 As completion queue is a circular buffer HW will rollover to DFA_CQ_CFG[CQ_BASE_PTR] after
                                                                 writing the address that represents (DFA_CQ_CFG[CQ_BASE_PTR] + (DFA_CQ_CFG[CQ_SIZE]).
                                                                 S/W maintains tail (read) pointer while H/W maintains head (write) pointer.
                                                                 S/W guarantees that HW will not overwrites an entry that was never processed by S/W.
                                                                 Number of entries currently outstanding for SW to process defined by
                                                                 DFA_INT_STATUS[DONE_CNT]. */
        uint64_t reserved_39_55        : 17;
        uint64_t cq_base_ptr           : 39; /**< [ 38:  0](R/W) Internal:
                                                                 Deprecated.
                                                                 Global completion queue base address, divided by 1KB. Address is 1KB aligned. */
#else /* Word 0 - Little Endian */
        uint64_t cq_base_ptr           : 39; /**< [ 38:  0](R/W) Internal:
                                                                 Deprecated.
                                                                 Global completion queue base address, divided by 1KB. Address is 1KB aligned. */
        uint64_t reserved_39_55        : 17;
        uint64_t cq_size               : 4;  /**< [ 59: 56](R/W) Internal:
                                                                 Deprecated.
                                                                 Specifies completion queue buffer size in entries:
                                                                 0x0 = 256 entries.
                                                                 0x1 = 512 entries.
                                                                 0x2 = 1K entries.
                                                                 0x3 = 2K entries.
                                                                 0x4 = 4K entries.
                                                                 0x5 = 8K entries.
                                                                 0x6 = 16K entries.
                                                                 0x7 = 32K entries.
                                                                 0x8 = 64K entries.
                                                                 0x9 = 128K entries.
                                                                 0xA = 256K entries.
                                                                 0xB = 512K entries.
                                                                 0xC = 1M entries.
                                                                 0xD = Reserved.
                                                                 0xE = Reserved.
                                                                 0xF = Reserved.

                                                                 As completion queue is a circular buffer HW will rollover to DFA_CQ_CFG[CQ_BASE_PTR] after
                                                                 writing the address that represents (DFA_CQ_CFG[CQ_BASE_PTR] + (DFA_CQ_CFG[CQ_SIZE]).
                                                                 S/W maintains tail (read) pointer while H/W maintains head (write) pointer.
                                                                 S/W guarantees that HW will not overwrites an entry that was never processed by S/W.
                                                                 Number of entries currently outstanding for SW to process defined by
                                                                 DFA_INT_STATUS[DONE_CNT]. */
        uint64_t reserved_60_62        : 3;
        uint64_t cq_ena                : 1;  /**< [ 63: 63](R/W) Reserved.
                                                                 Internal:
                                                                 Deprecated. Enables the completion queue. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_cq_cfg_s cn; */
};
typedef union bdk_dfa_cq_cfg bdk_dfa_cq_cfg_t;

#define BDK_DFA_CQ_CFG BDK_DFA_CQ_CFG_FUNC()
static inline uint64_t BDK_DFA_CQ_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_CQ_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000210ll;
    __bdk_csr_fatal("DFA_CQ_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_CQ_CFG bdk_dfa_cq_cfg_t
#define bustype_BDK_DFA_CQ_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_CQ_CFG "DFA_CQ_CFG"
#define device_bar_BDK_DFA_CQ_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_CQ_CFG 0
#define arguments_BDK_DFA_CQ_CFG -1,-1,-1,-1

/**
 * Register (NCB) dfa_dbell
 *
 * HFA Doorbell Register
 * If DFA_CONFIG[DTECLKDIS] = 1 (i.e. HFA-HTE clocks are disabled) or if the HFA HTE
 * disable fuse is blown, read/write operations to DFA_DBELL do not take effect.
 */
union bdk_dfa_dbell
{
    uint64_t u;
    struct bdk_dfa_dbell_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t dbell                 : 20; /**< [ 19:  0](R/W/H) Represents the cumulative total of pending HFA instructions that software has previously
                                                                 written into the HFA instruction FIFO (DIF) in main memory. Each HFA instruction contains
                                                                 a fixed size 64-byte instruction word which is executed by the HFA hardware.
                                                                 The DBL register can hold up to 1M-1 (2^20-1) pending HFA instruction requests. During a
                                                                 read (by software), the 'most recent' contents of the DFA_DBELL register are returned at
                                                                 the time the NCB-inbound bus is driven.

                                                                 Since HFA hardware updates this register, its contents are unpredictable in software. */
#else /* Word 0 - Little Endian */
        uint64_t dbell                 : 20; /**< [ 19:  0](R/W/H) Represents the cumulative total of pending HFA instructions that software has previously
                                                                 written into the HFA instruction FIFO (DIF) in main memory. Each HFA instruction contains
                                                                 a fixed size 64-byte instruction word which is executed by the HFA hardware.
                                                                 The DBL register can hold up to 1M-1 (2^20-1) pending HFA instruction requests. During a
                                                                 read (by software), the 'most recent' contents of the DFA_DBELL register are returned at
                                                                 the time the NCB-inbound bus is driven.

                                                                 Since HFA hardware updates this register, its contents are unpredictable in software. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_dbell_s cn; */
};
typedef union bdk_dfa_dbell bdk_dfa_dbell_t;

#define BDK_DFA_DBELL BDK_DFA_DBELL_FUNC()
static inline uint64_t BDK_DFA_DBELL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_DBELL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846000000000ll;
    __bdk_csr_fatal("DFA_DBELL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_DBELL bdk_dfa_dbell_t
#define bustype_BDK_DFA_DBELL BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_DBELL "DFA_DBELL"
#define device_bar_BDK_DFA_DBELL 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_DBELL 0
#define arguments_BDK_DFA_DBELL -1,-1,-1,-1

/**
 * Register (NCB) dfa_debug0
 *
 * INTERNAL: HFA Scoreboard Debug 0 Register
 *
 * When the DFA_CONTROL[SBDLCK] bit is written '1', the contents of this register are locked
 * down. Otherwise, the contents of this register are the 'active' contents of the DFA Scoreboard
 * at the time of the CSR read operation.
 * VERIFICATION NOTE: Read data is unsafe. X's (undefined data) can propagate (in the behavioral
 * model) on the read operations unless the DTE Engine specified by DFA_CONTROL[SBDNUM] has
 * previously been assigned an instruction.
 */
union bdk_dfa_debug0
{
    uint64_t u;
    struct bdk_dfa_debug0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sbd0                  : 64; /**< [ 63:  0](RO/H) DFA ScoreBoard 0 Data (DFA Scoreboard Debug).
                                                                 Internal:
                                                                 [63:38]   (26) rptr[28:3]: Result Base Pointer (QW-aligned).
                                                                 [37:22]   (16) Cumulative Result Write Counter (for HDR write operation).
                                                                 [21]       (1) Waiting for GRdRsp EOT.
                                                                 [20]       (1) Waiting for GRdReq Issue (to NRQ).
                                                                 [19]       (1) GLPTR/GLCNT Valid.
                                                                 [18]       (1) Completion Mark Detected.
                                                                 [17:15]    (3) Completion Code [0=PDGONE/1=PERR/2=RFULL/3=TERM].
                                                                 [14]       (1) Completion Detected.
                                                                 [13]       (1) Waiting for HDR RWrCmtRsp.
                                                                 [12]       (1) Waiting for LAST RESULT RWrCmtRsp.
                                                                 [11]       (1) Waiting for HDR RWrReq.
                                                                 [10]        (1) Waiting for RWrReq.
                                                                 [9]        (1) Waiting for WQWrReq issue.
                                                                 [8]        (1) Waiting for PRdRsp EOT.
                                                                 [7]        (1) Waiting for PRdReq Issue (to NRQ).
                                                                 [6]        (1) Packet Data Valid.
                                                                 [5]        (1) WQVLD.
                                                                 [4]        (1) WQ Done Point (either WQWrReq issued (for WQPTR\<\>0) OR HDR RWrCmtRsp).
                                                                 [3]        (1) Resultant write STF/P Mode.
                                                                 [2]        (1) Packet Data LDT mode.
                                                                 [1]        (1) Gather Mode.
                                                                 [0]        (1) Valid. */
#else /* Word 0 - Little Endian */
        uint64_t sbd0                  : 64; /**< [ 63:  0](RO/H) DFA ScoreBoard 0 Data (DFA Scoreboard Debug).
                                                                 Internal:
                                                                 [63:38]   (26) rptr[28:3]: Result Base Pointer (QW-aligned).
                                                                 [37:22]   (16) Cumulative Result Write Counter (for HDR write operation).
                                                                 [21]       (1) Waiting for GRdRsp EOT.
                                                                 [20]       (1) Waiting for GRdReq Issue (to NRQ).
                                                                 [19]       (1) GLPTR/GLCNT Valid.
                                                                 [18]       (1) Completion Mark Detected.
                                                                 [17:15]    (3) Completion Code [0=PDGONE/1=PERR/2=RFULL/3=TERM].
                                                                 [14]       (1) Completion Detected.
                                                                 [13]       (1) Waiting for HDR RWrCmtRsp.
                                                                 [12]       (1) Waiting for LAST RESULT RWrCmtRsp.
                                                                 [11]       (1) Waiting for HDR RWrReq.
                                                                 [10]        (1) Waiting for RWrReq.
                                                                 [9]        (1) Waiting for WQWrReq issue.
                                                                 [8]        (1) Waiting for PRdRsp EOT.
                                                                 [7]        (1) Waiting for PRdReq Issue (to NRQ).
                                                                 [6]        (1) Packet Data Valid.
                                                                 [5]        (1) WQVLD.
                                                                 [4]        (1) WQ Done Point (either WQWrReq issued (for WQPTR\<\>0) OR HDR RWrCmtRsp).
                                                                 [3]        (1) Resultant write STF/P Mode.
                                                                 [2]        (1) Packet Data LDT mode.
                                                                 [1]        (1) Gather Mode.
                                                                 [0]        (1) Valid. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_debug0_s cn; */
};
typedef union bdk_dfa_debug0 bdk_dfa_debug0_t;

#define BDK_DFA_DEBUG0 BDK_DFA_DEBUG0_FUNC()
static inline uint64_t BDK_DFA_DEBUG0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_DEBUG0_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000040ll;
    __bdk_csr_fatal("DFA_DEBUG0", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_DEBUG0 bdk_dfa_debug0_t
#define bustype_BDK_DFA_DEBUG0 BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_DEBUG0 "DFA_DEBUG0"
#define device_bar_BDK_DFA_DEBUG0 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_DEBUG0 0
#define arguments_BDK_DFA_DEBUG0 -1,-1,-1,-1

/**
 * Register (NCB) dfa_debug1
 *
 * INTERNAL: HFA Scoreboard Debug 1 Register
 *
 * When the DFA_CONTROL[SBDLCK] bit is written '1', the contents of this register are locked
 * down. Otherwise, the contents of this register are the 'active' contents of the DFA Scoreboard
 * at the time of the CSR read operation.
 * VERIFICATION NOTE: Read data is unsafe. X's(undefined data) can propagate (in the behavioral
 * model) on the read operations unless the DTE Engine specified by DFA_CONTROL[SBDNUM] has
 * previously been assigned an instruction.
 */
union bdk_dfa_debug1
{
    uint64_t u;
    struct bdk_dfa_debug1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t sbd1                  : 64; /**< [ 63:  0](RO/H) Scoreboard 1 debug data.
                                                                 [63:56] = Reserved.
                                                                 [55:16] = Packet data pointer.
                                                                 [15:0] = Packet data counter. */
#else /* Word 0 - Little Endian */
        uint64_t sbd1                  : 64; /**< [ 63:  0](RO/H) Scoreboard 1 debug data.
                                                                 [63:56] = Reserved.
                                                                 [55:16] = Packet data pointer.
                                                                 [15:0] = Packet data counter. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_debug1_s cn; */
};
typedef union bdk_dfa_debug1 bdk_dfa_debug1_t;

#define BDK_DFA_DEBUG1 BDK_DFA_DEBUG1_FUNC()
static inline uint64_t BDK_DFA_DEBUG1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_DEBUG1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000048ll;
    __bdk_csr_fatal("DFA_DEBUG1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_DEBUG1 bdk_dfa_debug1_t
#define bustype_BDK_DFA_DEBUG1 BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_DEBUG1 "DFA_DEBUG1"
#define device_bar_BDK_DFA_DEBUG1 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_DEBUG1 0
#define arguments_BDK_DFA_DEBUG1 -1,-1,-1,-1

/**
 * Register (NCB) dfa_difctl
 *
 * HFA Instruction FIFO (DIF) Control Register
 * To write to DFA_DIFCTL, a device issues an IOBST request directed at the HFA with addr[34:32]
 * = 0x6. To read DFA_DIFCTL, a device issues an IOBLD64 request directed at the HFA with
 * addr[34:32] = 0x6. This register is intended to only be written once (at power-up). Any future
 * write operations could cause the HFA and FPA hardware to become unpredictable.
 *
 * If DFA_CONFIG[DTECLKDIS] = 1 (i.e. HFA-HTE clocks are disabled) or if FUSE[90] = 'HFA HTE
 * disable' is blown, read/write operations to DFA_DIFCTL do not take effect.
 */
union bdk_dfa_difctl
{
    uint64_t u;
    struct bdk_dfa_difctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_26_63        : 38;
        uint64_t msegbase              : 6;  /**< [ 25: 20](R/W) Reserved. */
        uint64_t reserved_13_19        : 7;
        uint64_t ldwb                  : 1;  /**< [ 12: 12](R/W) Load don't write back.

                                                                 0 = The hardware issues NCB regular load towards the cache, which will cause the
                                                                 line to be written back before being replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Partial cache line reads always use LDI. */
        uint64_t reserved_9_11         : 3;
        uint64_t size                  : 9;  /**< [  8:  0](R/W) Represents the number of 64-byte instructions contained within each HFA instruction chunk.
                                                                 At power-on, software seeds the SIZE register with a fixed chunk-size (must be at least
                                                                 0x3). HFA hardware uses this field to determine the size of each HFA instruction chunk, in
                                                                 order to:

                                                                 a) determine when to read the next HFA instruction chunk pointer which is written by
                                                                 software at the end of the current HFA instruction chunk (see HFA description of next
                                                                 chunk buffer Ptr for format).

                                                                 b) determine when a HFA instruction chunk can be returned to the free page list maintained
                                                                 by the FPA hardware. */
#else /* Word 0 - Little Endian */
        uint64_t size                  : 9;  /**< [  8:  0](R/W) Represents the number of 64-byte instructions contained within each HFA instruction chunk.
                                                                 At power-on, software seeds the SIZE register with a fixed chunk-size (must be at least
                                                                 0x3). HFA hardware uses this field to determine the size of each HFA instruction chunk, in
                                                                 order to:

                                                                 a) determine when to read the next HFA instruction chunk pointer which is written by
                                                                 software at the end of the current HFA instruction chunk (see HFA description of next
                                                                 chunk buffer Ptr for format).

                                                                 b) determine when a HFA instruction chunk can be returned to the free page list maintained
                                                                 by the FPA hardware. */
        uint64_t reserved_9_11         : 3;
        uint64_t ldwb                  : 1;  /**< [ 12: 12](R/W) Load don't write back.

                                                                 0 = The hardware issues NCB regular load towards the cache, which will cause the
                                                                 line to be written back before being replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Partial cache line reads always use LDI. */
        uint64_t reserved_13_19        : 7;
        uint64_t msegbase              : 6;  /**< [ 25: 20](R/W) Reserved. */
        uint64_t reserved_26_63        : 38;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_difctl_s cn; */
};
typedef union bdk_dfa_difctl bdk_dfa_difctl_t;

#define BDK_DFA_DIFCTL BDK_DFA_DIFCTL_FUNC()
static inline uint64_t BDK_DFA_DIFCTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_DIFCTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846600000000ll;
    __bdk_csr_fatal("DFA_DIFCTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_DIFCTL bdk_dfa_difctl_t
#define bustype_BDK_DFA_DIFCTL BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_DIFCTL "DFA_DIFCTL"
#define device_bar_BDK_DFA_DIFCTL 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_DIFCTL 0
#define arguments_BDK_DFA_DIFCTL -1,-1,-1,-1

/**
 * Register (NCB) dfa_difrdptr
 *
 * HFA Instruction FIFO (DIF) RDPTR Register
 * To write to DFA_DIFRDPTR, a device issues an IOBST request directed at the HFA with
 * addr[34:33] = 0x1. To read DFA_DIFRDPTR, a device issues an IOBLD64 request directed at the
 * HFA with addr[34:33] = 0x1.
 *
 * If DFA_CONFIG[DTECLKDIS] = 1 (i.e. HFA-HTE clocks are disabled) or if FUSE[90] = 'HFA HTE
 * disable' is blown, read/write operations to DFA_DIFRDPTR do not take effect.
 */
union bdk_dfa_difrdptr
{
    uint64_t u;
    struct bdk_dfa_difrdptr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t rdptr                 : 43; /**< [ 48:  6](R/W/H) Represents the 64-byte-aligned IOVA of the current instruction in the HFA instruction
                                                                 FIFO in main memory. The RDPTR must be seeded by software at boot time, and is then
                                                                 maintained thereafter by HFA hardware. During the seed write operation (by software),
                                                                 [RDPTR]\<6:5\> = 0, since HFA instruction chunks must be 128-byte-aligned. During a read
                                                                 operation (by software), the most-recent contents of the [RDPTR] register are returned at
                                                                 the time the NCB-inbound bus is driven.

                                                                 Since HFA hardware updates this register, its contents are unpredictable in software
                                                                 (unless it is guaranteed that no new doorbell register write operations have occurred and
                                                                 the doorbell register is read as zero). */
        uint64_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_5          : 6;
        uint64_t rdptr                 : 43; /**< [ 48:  6](R/W/H) Represents the 64-byte-aligned IOVA of the current instruction in the HFA instruction
                                                                 FIFO in main memory. The RDPTR must be seeded by software at boot time, and is then
                                                                 maintained thereafter by HFA hardware. During the seed write operation (by software),
                                                                 [RDPTR]\<6:5\> = 0, since HFA instruction chunks must be 128-byte-aligned. During a read
                                                                 operation (by software), the most-recent contents of the [RDPTR] register are returned at
                                                                 the time the NCB-inbound bus is driven.

                                                                 Since HFA hardware updates this register, its contents are unpredictable in software
                                                                 (unless it is guaranteed that no new doorbell register write operations have occurred and
                                                                 the doorbell register is read as zero). */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_difrdptr_s cn; */
};
typedef union bdk_dfa_difrdptr bdk_dfa_difrdptr_t;

#define BDK_DFA_DIFRDPTR BDK_DFA_DIFRDPTR_FUNC()
static inline uint64_t BDK_DFA_DIFRDPTR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_DIFRDPTR_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846100000000ll;
    __bdk_csr_fatal("DFA_DIFRDPTR", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_DIFRDPTR bdk_dfa_difrdptr_t
#define bustype_BDK_DFA_DIFRDPTR BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_DIFRDPTR "DFA_DIFRDPTR"
#define device_bar_BDK_DFA_DIFRDPTR 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_DIFRDPTR 0
#define arguments_BDK_DFA_DIFRDPTR -1,-1,-1,-1

/**
 * Register (NCB) dfa_done_ack
 *
 * HFA Done Count Ack Registers
 * This register is written by software to acknowledge interrupts.
 */
union bdk_dfa_done_ack
{
    uint64_t u;
    struct bdk_dfa_done_ack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to DFA_INT_STATUS[DONE_CNT]. Reads
                                                                 DFA_INT_STATUS[DONE_CNT].

                                                                 Written by software to acknowledge interrupts.  If DFA_INT_STATUS[DONE_CNT] is
                                                                 still nonzero the interrupt will be re-sent if the conditions described in
                                                                 DFA_INT_STATUS[DONE_CNT] are satified. */
#else /* Word 0 - Little Endian */
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to DFA_INT_STATUS[DONE_CNT]. Reads
                                                                 DFA_INT_STATUS[DONE_CNT].

                                                                 Written by software to acknowledge interrupts.  If DFA_INT_STATUS[DONE_CNT] is
                                                                 still nonzero the interrupt will be re-sent if the conditions described in
                                                                 DFA_INT_STATUS[DONE_CNT] are satified. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_done_ack_s cn; */
};
typedef union bdk_dfa_done_ack bdk_dfa_done_ack_t;

#define BDK_DFA_DONE_ACK BDK_DFA_DONE_ACK_FUNC()
static inline uint64_t BDK_DFA_DONE_ACK_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_DONE_ACK_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000000d8ll;
    __bdk_csr_fatal("DFA_DONE_ACK", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_DONE_ACK bdk_dfa_done_ack_t
#define bustype_BDK_DFA_DONE_ACK BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_DONE_ACK "DFA_DONE_ACK"
#define device_bar_BDK_DFA_DONE_ACK 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_DONE_ACK 0
#define arguments_BDK_DFA_DONE_ACK -1,-1,-1,-1

/**
 * Register (NCB) dfa_done_wait
 *
 * HFA Done Interrupt Coalescing Wait Registers
 * Specifies the interrupt coalescing settings.
 */
union bdk_dfa_done_wait
{
    uint64_t u;
    struct bdk_dfa_done_wait_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t time_wait             : 20; /**< [ 51: 32](R/W) Represents time to hold off setting DFA_INT_DONE[INST_DONE].
                                                                 When the HW timer reaches [TIME_WAIT]*1024 then interrupt coalescing ends.
                                                                 Typical value MUST be \>=1. */
        uint64_t reserved_20_31        : 12;
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of completion messages to hold-off setting DFA_INT_DONE[INST_DONE].
                                                                 When DFA_INT_STATUS[DONE_CNT] \> DFA_DONE_WAIT[NUM_WAIT] then interrupt coalescing ends. */
#else /* Word 0 - Little Endian */
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of completion messages to hold-off setting DFA_INT_DONE[INST_DONE].
                                                                 When DFA_INT_STATUS[DONE_CNT] \> DFA_DONE_WAIT[NUM_WAIT] then interrupt coalescing ends. */
        uint64_t reserved_20_31        : 12;
        uint64_t time_wait             : 20; /**< [ 51: 32](R/W) Represents time to hold off setting DFA_INT_DONE[INST_DONE].
                                                                 When the HW timer reaches [TIME_WAIT]*1024 then interrupt coalescing ends.
                                                                 Typical value MUST be \>=1. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_done_wait_s cn; */
};
typedef union bdk_dfa_done_wait bdk_dfa_done_wait_t;

#define BDK_DFA_DONE_WAIT BDK_DFA_DONE_WAIT_FUNC()
static inline uint64_t BDK_DFA_DONE_WAIT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_DONE_WAIT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000000e0ll;
    __bdk_csr_fatal("DFA_DONE_WAIT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_DONE_WAIT bdk_dfa_done_wait_t
#define bustype_BDK_DFA_DONE_WAIT BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_DONE_WAIT "DFA_DONE_WAIT"
#define device_bar_BDK_DFA_DONE_WAIT 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_DONE_WAIT 0
#define arguments_BDK_DFA_DONE_WAIT -1,-1,-1,-1

/**
 * Register (NCB) dfa_dtcfadr
 *
 * HFA DTC Failing Address Register
 * This register contains HFA graph-cache failing address/control error capture information. It
 * contains useful information to help in isolating a graph-cache RAM failure.
 */
union bdk_dfa_dtcfadr
{
    uint64_t u;
    struct bdk_dfa_dtcfadr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t ram3fadr              : 12; /**< [ 43: 32](RO/H) HFA RAM3 failing address. If DFA_ERROR[DC0PERR\<2\>] = 1, this field indicates the failing
                                                                 RAM3 address. The failing address is locked down until the DC0PERR\<2\> W1C occurs.
                                                                 If multiple DC0PERR\<0\>=1 errors are detected, the LSB cluster error information is
                                                                 captured. */
        uint64_t reserved_25_31        : 7;
        uint64_t ram2fadr              : 9;  /**< [ 24: 16](RO/H) HFA RAM2 failing address. If DFA_ERROR[DC0PERR\<1\>] = 1, this field indicates the failing
                                                                 RAM2 address. The failing address is locked down until the DC0PERR\<1\> W1C occurs.
                                                                 If multiple DC0PERR\<0\>=1 errors are detected, the LSB cluster error information is
                                                                 captured. */
        uint64_t reserved_14_15        : 2;
        uint64_t ram1fadr              : 14; /**< [ 13:  0](RO/H) HFA RAM1 failing address. If DFA_ERROR[DC0PERR\<0\>] = 1, this field indicates the failing
                                                                 RAM1 address. The failing address is locked down until the DC0PERR\<0\> W1C occurs.
                                                                 If multiple DC0PERR\<0\>=1 errors are detected, the LSB cluster error information is
                                                                 captured. */
#else /* Word 0 - Little Endian */
        uint64_t ram1fadr              : 14; /**< [ 13:  0](RO/H) HFA RAM1 failing address. If DFA_ERROR[DC0PERR\<0\>] = 1, this field indicates the failing
                                                                 RAM1 address. The failing address is locked down until the DC0PERR\<0\> W1C occurs.
                                                                 If multiple DC0PERR\<0\>=1 errors are detected, the LSB cluster error information is
                                                                 captured. */
        uint64_t reserved_14_15        : 2;
        uint64_t ram2fadr              : 9;  /**< [ 24: 16](RO/H) HFA RAM2 failing address. If DFA_ERROR[DC0PERR\<1\>] = 1, this field indicates the failing
                                                                 RAM2 address. The failing address is locked down until the DC0PERR\<1\> W1C occurs.
                                                                 If multiple DC0PERR\<0\>=1 errors are detected, the LSB cluster error information is
                                                                 captured. */
        uint64_t reserved_25_31        : 7;
        uint64_t ram3fadr              : 12; /**< [ 43: 32](RO/H) HFA RAM3 failing address. If DFA_ERROR[DC0PERR\<2\>] = 1, this field indicates the failing
                                                                 RAM3 address. The failing address is locked down until the DC0PERR\<2\> W1C occurs.
                                                                 If multiple DC0PERR\<0\>=1 errors are detected, the LSB cluster error information is
                                                                 captured. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_dtcfadr_s cn; */
};
typedef union bdk_dfa_dtcfadr bdk_dfa_dtcfadr_t;

#define BDK_DFA_DTCFADR BDK_DFA_DTCFADR_FUNC()
static inline uint64_t BDK_DFA_DTCFADR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_DTCFADR_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000060ll;
    __bdk_csr_fatal("DFA_DTCFADR", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_DTCFADR bdk_dfa_dtcfadr_t
#define bustype_BDK_DFA_DTCFADR BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_DTCFADR "DFA_DTCFADR"
#define device_bar_BDK_DFA_DTCFADR 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_DTCFADR 0
#define arguments_BDK_DFA_DTCFADR -1,-1,-1,-1

/**
 * Register (NCB) dfa_int
 *
 * HFA Interrupt Register
 */
union bdk_dfa_int
{
    uint64_t u;
    struct bdk_dfa_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t cb_rsp_err            : 1;  /**< [ 21: 21](R/W1C/H) NCB CB response error. */
        uint64_t stdn_err              : 1;  /**< [ 20: 20](R/W1C/H) Store commit error. */
        uint64_t osmerr                : 1;  /**< [ 19: 19](R/W1C/H) Incorrect access to OSM, who doesn't exist. Non recoverable SW error. */
        uint64_t replerr               : 1;  /**< [ 18: 18](R/W1C/H) HFA illegal replication factor error. HFA only supports 1*, 2*, and 4* port replication.
                                                                 Legal configurations for memory are to support 2 port or 4 port configurations.
                                                                 The REPLERR interrupt is set in the following illegal configuration cases:

                                                                 An 8* replication factor is detected for any memory reference.

                                                                 A 4* replication factor is detected for any memory reference when only 2 memory ports are
                                                                 enabled.

                                                                 If REPLERR is set during a HFA graph walk operation, the walk prematurely terminates with
                                                                 RWORD0[REA]=ERR. If REPLERR is set during a NCB-direct CSR read access to HFA memory
                                                                 region, the CSR read response data is unpredictable. */
        uint64_t reserved_17           : 1;
        uint64_t asc_rg_err            : 1;  /**< [ 16: 16](R/W1C/H) ASC regions error. HTEs (or backdoor CSR HFA memory region reads) has tried
                                                                 to access DRAM secure region address space while nonsecure access is not enabled or
                                                                 accessed address is not defined by any of the DFA's ASC regions.
                                                                 See DFA_ASC_REGION(0..3)_START/END/ATTR/OFFSET. */
        uint64_t reserved_15           : 1;
        uint64_t dlc1_ovferr           : 1;  /**< [ 14: 14](R/W1C/H) DLC1 FIFO overflow error detected. This condition should never architecturally occur, and
                                                                 is here in case hardware credit/debit scheme is not working. */
        uint64_t dlc0_ovferr           : 1;  /**< [ 13: 13](R/W1C/H) DLC0 FIFO overflow error detected. This condition should never architecturally occur, and
                                                                 is here in case hardware credit/debit scheme is not working. */
        uint64_t reserved_7_12         : 6;
        uint64_t dc1perr               : 3;  /**< [  6:  4](R/W1C/H) Cluster 1 RAM[3:1] parity error detected. See also DFA_DTCFADR, which contains the failing
                                                                 addresses for the internal node cache RAMs. */
        uint64_t dc0perr               : 3;  /**< [  3:  1](R/W1C/H) Cluster 0 RAM[3:1] parity error detected. See also DFA_DTCFADR register, which contains
                                                                 the failing addresses for the graph-cache RAMs. */
        uint64_t dblovf                : 1;  /**< [  0:  0](R/W1C/H) Doorbell overflow detected - status bit. When set, DFA_DBELL[DBELL]
                                                                 had overflowed (software wrote too many doorbell requests). If the DBLINA had previously
                                                                 been enabled (set), an interrupt will be posted. Software can clear the interrupt by
                                                                 writing a 1 to this register bit.
                                                                 Detection of a doorbell register overflow is a catastrophic error that may leave the HFA
                                                                 hardware in an unrecoverable state. */
#else /* Word 0 - Little Endian */
        uint64_t dblovf                : 1;  /**< [  0:  0](R/W1C/H) Doorbell overflow detected - status bit. When set, DFA_DBELL[DBELL]
                                                                 had overflowed (software wrote too many doorbell requests). If the DBLINA had previously
                                                                 been enabled (set), an interrupt will be posted. Software can clear the interrupt by
                                                                 writing a 1 to this register bit.
                                                                 Detection of a doorbell register overflow is a catastrophic error that may leave the HFA
                                                                 hardware in an unrecoverable state. */
        uint64_t dc0perr               : 3;  /**< [  3:  1](R/W1C/H) Cluster 0 RAM[3:1] parity error detected. See also DFA_DTCFADR register, which contains
                                                                 the failing addresses for the graph-cache RAMs. */
        uint64_t dc1perr               : 3;  /**< [  6:  4](R/W1C/H) Cluster 1 RAM[3:1] parity error detected. See also DFA_DTCFADR, which contains the failing
                                                                 addresses for the internal node cache RAMs. */
        uint64_t reserved_7_12         : 6;
        uint64_t dlc0_ovferr           : 1;  /**< [ 13: 13](R/W1C/H) DLC0 FIFO overflow error detected. This condition should never architecturally occur, and
                                                                 is here in case hardware credit/debit scheme is not working. */
        uint64_t dlc1_ovferr           : 1;  /**< [ 14: 14](R/W1C/H) DLC1 FIFO overflow error detected. This condition should never architecturally occur, and
                                                                 is here in case hardware credit/debit scheme is not working. */
        uint64_t reserved_15           : 1;
        uint64_t asc_rg_err            : 1;  /**< [ 16: 16](R/W1C/H) ASC regions error. HTEs (or backdoor CSR HFA memory region reads) has tried
                                                                 to access DRAM secure region address space while nonsecure access is not enabled or
                                                                 accessed address is not defined by any of the DFA's ASC regions.
                                                                 See DFA_ASC_REGION(0..3)_START/END/ATTR/OFFSET. */
        uint64_t reserved_17           : 1;
        uint64_t replerr               : 1;  /**< [ 18: 18](R/W1C/H) HFA illegal replication factor error. HFA only supports 1*, 2*, and 4* port replication.
                                                                 Legal configurations for memory are to support 2 port or 4 port configurations.
                                                                 The REPLERR interrupt is set in the following illegal configuration cases:

                                                                 An 8* replication factor is detected for any memory reference.

                                                                 A 4* replication factor is detected for any memory reference when only 2 memory ports are
                                                                 enabled.

                                                                 If REPLERR is set during a HFA graph walk operation, the walk prematurely terminates with
                                                                 RWORD0[REA]=ERR. If REPLERR is set during a NCB-direct CSR read access to HFA memory
                                                                 region, the CSR read response data is unpredictable. */
        uint64_t osmerr                : 1;  /**< [ 19: 19](R/W1C/H) Incorrect access to OSM, who doesn't exist. Non recoverable SW error. */
        uint64_t stdn_err              : 1;  /**< [ 20: 20](R/W1C/H) Store commit error. */
        uint64_t cb_rsp_err            : 1;  /**< [ 21: 21](R/W1C/H) NCB CB response error. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_int_s cn; */
};
typedef union bdk_dfa_int bdk_dfa_int_t;

#define BDK_DFA_INT BDK_DFA_INT_FUNC()
static inline uint64_t BDK_DFA_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_INT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000028ll;
    __bdk_csr_fatal("DFA_INT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_INT bdk_dfa_int_t
#define bustype_BDK_DFA_INT BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_INT "DFA_INT"
#define device_bar_BDK_DFA_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_INT 0
#define arguments_BDK_DFA_INT -1,-1,-1,-1

/**
 * Register (NCB) dfa_int_done
 *
 * HFA Interrupt Register
 */
union bdk_dfa_int_done
{
    uint64_t u;
    struct bdk_dfa_int_done_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t inst_done             : 1;  /**< [  0:  0](RO/H) Instruction completion interrupt.
                                                                 Set when:
                                                                 1. DFA_INT_STATUS[DONE_CNT] becomes greater than DFA_DONE_WAIT[NUM_WAIT].
                                                                 2. SW writes DFA_DONE_ACK[DONE_ACK] with value that meets the next equation:
                                                                    DFA_DONE_ACK[DONE_ACK] \< ( DFA_INT_STATUS[DONE_CNT] - DFA_DONE_WAIT[NUM_WAIT] )

                                                                 Clears when SW writes DFA_DONE_ACK[DONE_ACK] with value that meets the next equation:
                                                                    DFA_DONE_ACK[DONE_ACK] \> ( DFA_INT_STATUS[DONE_CNT] - DFA_DONE_WAIT[NUM_WAIT] ) */
#else /* Word 0 - Little Endian */
        uint64_t inst_done             : 1;  /**< [  0:  0](RO/H) Instruction completion interrupt.
                                                                 Set when:
                                                                 1. DFA_INT_STATUS[DONE_CNT] becomes greater than DFA_DONE_WAIT[NUM_WAIT].
                                                                 2. SW writes DFA_DONE_ACK[DONE_ACK] with value that meets the next equation:
                                                                    DFA_DONE_ACK[DONE_ACK] \< ( DFA_INT_STATUS[DONE_CNT] - DFA_DONE_WAIT[NUM_WAIT] )

                                                                 Clears when SW writes DFA_DONE_ACK[DONE_ACK] with value that meets the next equation:
                                                                    DFA_DONE_ACK[DONE_ACK] \> ( DFA_INT_STATUS[DONE_CNT] - DFA_DONE_WAIT[NUM_WAIT] ) */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_int_done_s cn; */
};
typedef union bdk_dfa_int_done bdk_dfa_int_done_t;

#define BDK_DFA_INT_DONE BDK_DFA_INT_DONE_FUNC()
static inline uint64_t BDK_DFA_INT_DONE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_INT_DONE_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000000e8ll;
    __bdk_csr_fatal("DFA_INT_DONE", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_INT_DONE bdk_dfa_int_done_t
#define bustype_BDK_DFA_INT_DONE BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_INT_DONE "DFA_INT_DONE"
#define device_bar_BDK_DFA_INT_DONE 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_INT_DONE 0
#define arguments_BDK_DFA_INT_DONE -1,-1,-1,-1

/**
 * Register (NCB) dfa_int_done_ena_w1c
 *
 * HFA Interrupt Register
 */
union bdk_dfa_int_done_ena_w1c
{
    uint64_t u;
    struct bdk_dfa_int_done_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t inst_done             : 1;  /**< [  0:  0](R/W1C/H) Reads or clears DFA_INT_DONE_ENA_W1S[INST_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t inst_done             : 1;  /**< [  0:  0](R/W1C/H) Reads or clears DFA_INT_DONE_ENA_W1S[INST_DONE]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_int_done_ena_w1c_s cn; */
};
typedef union bdk_dfa_int_done_ena_w1c bdk_dfa_int_done_ena_w1c_t;

#define BDK_DFA_INT_DONE_ENA_W1C BDK_DFA_INT_DONE_ENA_W1C_FUNC()
static inline uint64_t BDK_DFA_INT_DONE_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_INT_DONE_ENA_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000100ll;
    __bdk_csr_fatal("DFA_INT_DONE_ENA_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_INT_DONE_ENA_W1C bdk_dfa_int_done_ena_w1c_t
#define bustype_BDK_DFA_INT_DONE_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_INT_DONE_ENA_W1C "DFA_INT_DONE_ENA_W1C"
#define device_bar_BDK_DFA_INT_DONE_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_INT_DONE_ENA_W1C 0
#define arguments_BDK_DFA_INT_DONE_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) dfa_int_done_ena_w1s
 *
 * HFA Interrupt Register
 */
union bdk_dfa_int_done_ena_w1s
{
    uint64_t u;
    struct bdk_dfa_int_done_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t inst_done             : 1;  /**< [  0:  0](R/W1S/H) Enables reporting of DFA_INT_DONE[INST_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t inst_done             : 1;  /**< [  0:  0](R/W1S/H) Enables reporting of DFA_INT_DONE[INST_DONE]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_int_done_ena_w1s_s cn; */
};
typedef union bdk_dfa_int_done_ena_w1s bdk_dfa_int_done_ena_w1s_t;

#define BDK_DFA_INT_DONE_ENA_W1S BDK_DFA_INT_DONE_ENA_W1S_FUNC()
static inline uint64_t BDK_DFA_INT_DONE_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_INT_DONE_ENA_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000000f8ll;
    __bdk_csr_fatal("DFA_INT_DONE_ENA_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_INT_DONE_ENA_W1S bdk_dfa_int_done_ena_w1s_t
#define bustype_BDK_DFA_INT_DONE_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_INT_DONE_ENA_W1S "DFA_INT_DONE_ENA_W1S"
#define device_bar_BDK_DFA_INT_DONE_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_INT_DONE_ENA_W1S 0
#define arguments_BDK_DFA_INT_DONE_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) dfa_int_ena_w1c
 *
 * HFA Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_dfa_int_ena_w1c
{
    uint64_t u;
    struct bdk_dfa_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t cb_rsp_err            : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for DFA_INT[CB_RSP_ERR]. */
        uint64_t stdn_err              : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for DFA_INT[STDN_ERR]. */
        uint64_t osmerr                : 1;  /**< [ 19: 19](R/W1C/H) Reads or clears enable for DFA_INT[OSMERR]. */
        uint64_t replerr               : 1;  /**< [ 18: 18](R/W1C/H) Reads or clears enable for DFA_INT[REPLERR]. */
        uint64_t reserved_17           : 1;
        uint64_t asc_rg_err            : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for DFA_INT[ASC_RG_ERR]. */
        uint64_t reserved_15           : 1;
        uint64_t dlc1_ovferr           : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for DFA_INT[DLC1_OVFERR]. */
        uint64_t dlc0_ovferr           : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for DFA_INT[DLC0_OVFERR]. */
        uint64_t reserved_7_12         : 6;
        uint64_t dc1perr               : 3;  /**< [  6:  4](R/W1C/H) Reads or clears enable for DFA_INT[DC1PERR]. */
        uint64_t dc0perr               : 3;  /**< [  3:  1](R/W1C/H) Reads or clears enable for DFA_INT[DC0PERR]. */
        uint64_t dblovf                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for DFA_INT[DBLOVF]. */
#else /* Word 0 - Little Endian */
        uint64_t dblovf                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for DFA_INT[DBLOVF]. */
        uint64_t dc0perr               : 3;  /**< [  3:  1](R/W1C/H) Reads or clears enable for DFA_INT[DC0PERR]. */
        uint64_t dc1perr               : 3;  /**< [  6:  4](R/W1C/H) Reads or clears enable for DFA_INT[DC1PERR]. */
        uint64_t reserved_7_12         : 6;
        uint64_t dlc0_ovferr           : 1;  /**< [ 13: 13](R/W1C/H) Reads or clears enable for DFA_INT[DLC0_OVFERR]. */
        uint64_t dlc1_ovferr           : 1;  /**< [ 14: 14](R/W1C/H) Reads or clears enable for DFA_INT[DLC1_OVFERR]. */
        uint64_t reserved_15           : 1;
        uint64_t asc_rg_err            : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for DFA_INT[ASC_RG_ERR]. */
        uint64_t reserved_17           : 1;
        uint64_t replerr               : 1;  /**< [ 18: 18](R/W1C/H) Reads or clears enable for DFA_INT[REPLERR]. */
        uint64_t osmerr                : 1;  /**< [ 19: 19](R/W1C/H) Reads or clears enable for DFA_INT[OSMERR]. */
        uint64_t stdn_err              : 1;  /**< [ 20: 20](R/W1C/H) Reads or clears enable for DFA_INT[STDN_ERR]. */
        uint64_t cb_rsp_err            : 1;  /**< [ 21: 21](R/W1C/H) Reads or clears enable for DFA_INT[CB_RSP_ERR]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_int_ena_w1c_s cn; */
};
typedef union bdk_dfa_int_ena_w1c bdk_dfa_int_ena_w1c_t;

#define BDK_DFA_INT_ENA_W1C BDK_DFA_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_DFA_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_INT_ENA_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000078ll;
    __bdk_csr_fatal("DFA_INT_ENA_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_INT_ENA_W1C bdk_dfa_int_ena_w1c_t
#define bustype_BDK_DFA_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_INT_ENA_W1C "DFA_INT_ENA_W1C"
#define device_bar_BDK_DFA_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_INT_ENA_W1C 0
#define arguments_BDK_DFA_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) dfa_int_ena_w1s
 *
 * HFA Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_dfa_int_ena_w1s
{
    uint64_t u;
    struct bdk_dfa_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t cb_rsp_err            : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for DFA_INT[CB_RSP_ERR]. */
        uint64_t stdn_err              : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for DFA_INT[STDN_ERR]. */
        uint64_t osmerr                : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets enable for DFA_INT[OSMERR]. */
        uint64_t replerr               : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets enable for DFA_INT[REPLERR]. */
        uint64_t reserved_17           : 1;
        uint64_t asc_rg_err            : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for DFA_INT[ASC_RG_ERR]. */
        uint64_t reserved_15           : 1;
        uint64_t dlc1_ovferr           : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for DFA_INT[DLC1_OVFERR]. */
        uint64_t dlc0_ovferr           : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for DFA_INT[DLC0_OVFERR]. */
        uint64_t reserved_7_12         : 6;
        uint64_t dc1perr               : 3;  /**< [  6:  4](R/W1S/H) Reads or sets enable for DFA_INT[DC1PERR]. */
        uint64_t dc0perr               : 3;  /**< [  3:  1](R/W1S/H) Reads or sets enable for DFA_INT[DC0PERR]. */
        uint64_t dblovf                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for DFA_INT[DBLOVF]. */
#else /* Word 0 - Little Endian */
        uint64_t dblovf                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for DFA_INT[DBLOVF]. */
        uint64_t dc0perr               : 3;  /**< [  3:  1](R/W1S/H) Reads or sets enable for DFA_INT[DC0PERR]. */
        uint64_t dc1perr               : 3;  /**< [  6:  4](R/W1S/H) Reads or sets enable for DFA_INT[DC1PERR]. */
        uint64_t reserved_7_12         : 6;
        uint64_t dlc0_ovferr           : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets enable for DFA_INT[DLC0_OVFERR]. */
        uint64_t dlc1_ovferr           : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets enable for DFA_INT[DLC1_OVFERR]. */
        uint64_t reserved_15           : 1;
        uint64_t asc_rg_err            : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for DFA_INT[ASC_RG_ERR]. */
        uint64_t reserved_17           : 1;
        uint64_t replerr               : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets enable for DFA_INT[REPLERR]. */
        uint64_t osmerr                : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets enable for DFA_INT[OSMERR]. */
        uint64_t stdn_err              : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets enable for DFA_INT[STDN_ERR]. */
        uint64_t cb_rsp_err            : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets enable for DFA_INT[CB_RSP_ERR]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_int_ena_w1s_s cn; */
};
typedef union bdk_dfa_int_ena_w1s bdk_dfa_int_ena_w1s_t;

#define BDK_DFA_INT_ENA_W1S BDK_DFA_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_DFA_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_INT_ENA_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000070ll;
    __bdk_csr_fatal("DFA_INT_ENA_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_INT_ENA_W1S bdk_dfa_int_ena_w1s_t
#define bustype_BDK_DFA_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_INT_ENA_W1S "DFA_INT_ENA_W1S"
#define device_bar_BDK_DFA_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_INT_ENA_W1S 0
#define arguments_BDK_DFA_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) dfa_int_status
 *
 * HFA Interrupt Status Register
 */
union bdk_dfa_int_status
{
    uint64_t u;
    struct bdk_dfa_int_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t cndrd                 : 1;  /**< [ 32: 32](RO/H) If any of the clusters detected a parity error on RAM1, this additional bit further
                                                                 specifies that the RAM1 parity error was detected during a CND-RD (cache node metadata
                                                                 read).
                                                                 This bit is set if ANY node cluster's RAM1 accesses detect a CNDRD error.

                                                                 Internal:
                                                                 For CNDRD Parity Error, the previous CNA arc fetch information is written to
                                                                 RWORD1+ as follows:
                                                                 RWORD1+[NTYPE]=MNODE
                                                                 RWORD1+[NDNID]=cna.ndnid
                                                                 RWORD1+[NHMSK]=cna.hmsk
                                                                 RWORD1+[NNPTR]=cna.nnptr[13:0] */
        uint64_t reserved_20_31        : 12;
        uint64_t done_cnt              : 20; /**< [ 19:  0](R/W/H) Done count. When an instruction completes, DFA_INT_STATUS[DONE_CNT] is
                                                                 incremented. Write to this field are for diagnostic use only; instead
                                                                 software writes DFA_DONE_ACK[DONE] with the number of decrements for this field.

                                                                 Interrupts are sent as follows:

                                                                 * When DFA_INT_STATUS[DONE_CNT] = 0, then no results are pending, the interrupt
                                                                 coalescing timer is held to zero, and an interrupt is not sent.

                                                                 * When DFA_INT_STATUS[DONE_CNT] != 0, then the interrupt coalescing timer
                                                                 counts. If the counter is \>= DFA_DONE_WAIT[TIME_WAIT]*1024, or
                                                                 DFA_INT_STATUS[DONE_CNT] \>= DFA_DONE_WAIT[NUM_WAIT], i.e. enough time has passed
                                                                 or enough results have arrived, then the interrupt is sent.  Otherwise, it is
                                                                 not sent due to coalescing.

                                                                 * When DFA_DONE_ACK is written, the interrupt coalescing timer restarts.  Note
                                                                 after decrementing this interrupt equation is recomputed, for example if
                                                                 DFA_INT_STATUS[DONE_CNT] \>= DFA_DONE_WAIT[NUM_WAIT] and because the timer is
                                                                 zero, the interrupt will be resent immediately.  (This covers the race case
                                                                 between software acknowledging an interrupt and a result returning.)

                                                                 * When DFA_INT_DONE_ENA_W1S[DONE_ENA] = 0, interrupts are not sent, but the counting
                                                                 described above still occurs.

                                                                 Since DFA instructions can complete out-of-order, if software is using
                                                                 completion interrupts the suggested scheme is to request a DONEINT on each
                                                                 request, and when an interrupt arrives perform a "greedy" scan for completions;
                                                                 even if a later command is acknowledged first this will not result in missing a
                                                                 completion. */
#else /* Word 0 - Little Endian */
        uint64_t done_cnt              : 20; /**< [ 19:  0](R/W/H) Done count. When an instruction completes, DFA_INT_STATUS[DONE_CNT] is
                                                                 incremented. Write to this field are for diagnostic use only; instead
                                                                 software writes DFA_DONE_ACK[DONE] with the number of decrements for this field.

                                                                 Interrupts are sent as follows:

                                                                 * When DFA_INT_STATUS[DONE_CNT] = 0, then no results are pending, the interrupt
                                                                 coalescing timer is held to zero, and an interrupt is not sent.

                                                                 * When DFA_INT_STATUS[DONE_CNT] != 0, then the interrupt coalescing timer
                                                                 counts. If the counter is \>= DFA_DONE_WAIT[TIME_WAIT]*1024, or
                                                                 DFA_INT_STATUS[DONE_CNT] \>= DFA_DONE_WAIT[NUM_WAIT], i.e. enough time has passed
                                                                 or enough results have arrived, then the interrupt is sent.  Otherwise, it is
                                                                 not sent due to coalescing.

                                                                 * When DFA_DONE_ACK is written, the interrupt coalescing timer restarts.  Note
                                                                 after decrementing this interrupt equation is recomputed, for example if
                                                                 DFA_INT_STATUS[DONE_CNT] \>= DFA_DONE_WAIT[NUM_WAIT] and because the timer is
                                                                 zero, the interrupt will be resent immediately.  (This covers the race case
                                                                 between software acknowledging an interrupt and a result returning.)

                                                                 * When DFA_INT_DONE_ENA_W1S[DONE_ENA] = 0, interrupts are not sent, but the counting
                                                                 described above still occurs.

                                                                 Since DFA instructions can complete out-of-order, if software is using
                                                                 completion interrupts the suggested scheme is to request a DONEINT on each
                                                                 request, and when an interrupt arrives perform a "greedy" scan for completions;
                                                                 even if a later command is acknowledged first this will not result in missing a
                                                                 completion. */
        uint64_t reserved_20_31        : 12;
        uint64_t cndrd                 : 1;  /**< [ 32: 32](RO/H) If any of the clusters detected a parity error on RAM1, this additional bit further
                                                                 specifies that the RAM1 parity error was detected during a CND-RD (cache node metadata
                                                                 read).
                                                                 This bit is set if ANY node cluster's RAM1 accesses detect a CNDRD error.

                                                                 Internal:
                                                                 For CNDRD Parity Error, the previous CNA arc fetch information is written to
                                                                 RWORD1+ as follows:
                                                                 RWORD1+[NTYPE]=MNODE
                                                                 RWORD1+[NDNID]=cna.ndnid
                                                                 RWORD1+[NHMSK]=cna.hmsk
                                                                 RWORD1+[NNPTR]=cna.nnptr[13:0] */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_int_status_s cn; */
};
typedef union bdk_dfa_int_status bdk_dfa_int_status_t;

#define BDK_DFA_INT_STATUS BDK_DFA_INT_STATUS_FUNC()
static inline uint64_t BDK_DFA_INT_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_INT_STATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000030ll;
    __bdk_csr_fatal("DFA_INT_STATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_INT_STATUS bdk_dfa_int_status_t
#define bustype_BDK_DFA_INT_STATUS BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_INT_STATUS "DFA_INT_STATUS"
#define device_bar_BDK_DFA_INT_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_INT_STATUS 0
#define arguments_BDK_DFA_INT_STATUS -1,-1,-1,-1

/**
 * Register (NCB) dfa_int_w1s
 *
 * HFA Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_dfa_int_w1s
{
    uint64_t u;
    struct bdk_dfa_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t cb_rsp_err            : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets DFA_INT[CB_RSP_ERR]. */
        uint64_t stdn_err              : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets DFA_INT[STDN_ERR]. */
        uint64_t osmerr                : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets DFA_INT[OSMERR]. */
        uint64_t replerr               : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets DFA_INT[REPLERR]. */
        uint64_t reserved_17           : 1;
        uint64_t asc_rg_err            : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets DFA_INT[ASC_RG_ERR]. */
        uint64_t reserved_15           : 1;
        uint64_t dlc1_ovferr           : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets DFA_INT[DLC1_OVFERR]. */
        uint64_t dlc0_ovferr           : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets DFA_INT[DLC0_OVFERR]. */
        uint64_t reserved_7_12         : 6;
        uint64_t dc1perr               : 3;  /**< [  6:  4](R/W1S/H) Reads or sets DFA_INT[DC1PERR]. */
        uint64_t dc0perr               : 3;  /**< [  3:  1](R/W1S/H) Reads or sets DFA_INT[DC0PERR]. */
        uint64_t dblovf                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets DFA_INT[DBLOVF]. */
#else /* Word 0 - Little Endian */
        uint64_t dblovf                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets DFA_INT[DBLOVF]. */
        uint64_t dc0perr               : 3;  /**< [  3:  1](R/W1S/H) Reads or sets DFA_INT[DC0PERR]. */
        uint64_t dc1perr               : 3;  /**< [  6:  4](R/W1S/H) Reads or sets DFA_INT[DC1PERR]. */
        uint64_t reserved_7_12         : 6;
        uint64_t dlc0_ovferr           : 1;  /**< [ 13: 13](R/W1S/H) Reads or sets DFA_INT[DLC0_OVFERR]. */
        uint64_t dlc1_ovferr           : 1;  /**< [ 14: 14](R/W1S/H) Reads or sets DFA_INT[DLC1_OVFERR]. */
        uint64_t reserved_15           : 1;
        uint64_t asc_rg_err            : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets DFA_INT[ASC_RG_ERR]. */
        uint64_t reserved_17           : 1;
        uint64_t replerr               : 1;  /**< [ 18: 18](R/W1S/H) Reads or sets DFA_INT[REPLERR]. */
        uint64_t osmerr                : 1;  /**< [ 19: 19](R/W1S/H) Reads or sets DFA_INT[OSMERR]. */
        uint64_t stdn_err              : 1;  /**< [ 20: 20](R/W1S/H) Reads or sets DFA_INT[STDN_ERR]. */
        uint64_t cb_rsp_err            : 1;  /**< [ 21: 21](R/W1S/H) Reads or sets DFA_INT[CB_RSP_ERR]. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_int_w1s_s cn; */
};
typedef union bdk_dfa_int_w1s bdk_dfa_int_w1s_t;

#define BDK_DFA_INT_W1S BDK_DFA_INT_W1S_FUNC()
static inline uint64_t BDK_DFA_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_INT_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000068ll;
    __bdk_csr_fatal("DFA_INT_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_INT_W1S bdk_dfa_int_w1s_t
#define bustype_BDK_DFA_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_INT_W1S "DFA_INT_W1S"
#define device_bar_BDK_DFA_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_INT_W1S 0
#define arguments_BDK_DFA_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) dfa_memhidat
 *
 * HFA NCB-Direct Memory Space Register
 */
union bdk_dfa_memhidat
{
    uint64_t u;
    struct bdk_dfa_memhidat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hidat                 : 64; /**< [ 63:  0](R/W) This register is unused and can be treated as spare bits. */
#else /* Word 0 - Little Endian */
        uint64_t hidat                 : 64; /**< [ 63:  0](R/W) This register is unused and can be treated as spare bits. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_memhidat_s cn; */
};
typedef union bdk_dfa_memhidat bdk_dfa_memhidat_t;

#define BDK_DFA_MEMHIDAT BDK_DFA_MEMHIDAT_FUNC()
static inline uint64_t BDK_DFA_MEMHIDAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_MEMHIDAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846700000000ll;
    __bdk_csr_fatal("DFA_MEMHIDAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_MEMHIDAT bdk_dfa_memhidat_t
#define bustype_BDK_DFA_MEMHIDAT BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_MEMHIDAT "DFA_MEMHIDAT"
#define device_bar_BDK_DFA_MEMHIDAT 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_MEMHIDAT 0
#define arguments_BDK_DFA_MEMHIDAT -1,-1,-1,-1

/**
 * Register (NCB) dfa_msix_pba#
 *
 * HFA MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the DFA_INT_VEC_E enumeration.
 */
union bdk_dfa_msix_pbax
{
    uint64_t u;
    struct bdk_dfa_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated DFA_MSIX_VEC()_CTL, enumerated by DFA_INT_VEC_E. Bits
                                                                 that have no associated DFA_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated DFA_MSIX_VEC()_CTL, enumerated by DFA_INT_VEC_E. Bits
                                                                 that have no associated DFA_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_msix_pbax_s cn; */
};
typedef union bdk_dfa_msix_pbax bdk_dfa_msix_pbax_t;

static inline uint64_t BDK_DFA_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_MSIX_PBAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a==0))
        return 0x846a000f0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("DFA_MSIX_PBAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_DFA_MSIX_PBAX(a) bdk_dfa_msix_pbax_t
#define bustype_BDK_DFA_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_MSIX_PBAX(a) "DFA_MSIX_PBAX"
#define device_bar_BDK_DFA_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_DFA_MSIX_PBAX(a) (a)
#define arguments_BDK_DFA_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) dfa_msix_vec#_addr
 *
 * HFA MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the DFA_INT_VEC_E enumeration.
 */
union bdk_dfa_msix_vecx_addr
{
    uint64_t u;
    struct bdk_dfa_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's DFA_MSIX_VEC()_ADDR, DFA_MSIX_VEC()_CTL, and corresponding
                                                                 bit of DFA_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_DFA_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's DFA_MSIX_VEC()_ADDR, DFA_MSIX_VEC()_CTL, and corresponding
                                                                 bit of DFA_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_DFA_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_msix_vecx_addr_s cn; */
};
typedef union bdk_dfa_msix_vecx_addr bdk_dfa_msix_vecx_addr_t;

static inline uint64_t BDK_DFA_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_MSIX_VECX_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x846a00000000ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("DFA_MSIX_VECX_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_DFA_MSIX_VECX_ADDR(a) bdk_dfa_msix_vecx_addr_t
#define bustype_BDK_DFA_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_MSIX_VECX_ADDR(a) "DFA_MSIX_VECX_ADDR"
#define device_bar_BDK_DFA_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_DFA_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_DFA_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) dfa_msix_vec#_ctl
 *
 * HFA MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the DFA_INT_VEC_E enumeration.
 */
union bdk_dfa_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_dfa_msix_vecx_ctl_s
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
    /* struct bdk_dfa_msix_vecx_ctl_s cn; */
};
typedef union bdk_dfa_msix_vecx_ctl bdk_dfa_msix_vecx_ctl_t;

static inline uint64_t BDK_DFA_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_MSIX_VECX_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x846a00000008ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("DFA_MSIX_VECX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_DFA_MSIX_VECX_CTL(a) bdk_dfa_msix_vecx_ctl_t
#define bustype_BDK_DFA_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_MSIX_VECX_CTL(a) "DFA_MSIX_VECX_CTL"
#define device_bar_BDK_DFA_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_DFA_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_DFA_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) dfa_pfc0_cnt
 *
 * INTERNAL: HFA Performance Counter 0 Register
 */
union bdk_dfa_pfc0_cnt
{
    uint64_t u;
    struct bdk_dfa_pfc0_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pfcnt0                : 64; /**< [ 63:  0](R/W/H) Performance counter 0. When DFA_PFC_GCTL[CNT0ENA] = 1, the event selected by
                                                                 DFA_PFC0_CTL[EVSEL] is counted. See also DFA_PFC_GCTL[CNT0WCLR] and DFA_PFC_GCTL[CNT0RCLR]
                                                                 for special clear count cases available for software data collection. */
#else /* Word 0 - Little Endian */
        uint64_t pfcnt0                : 64; /**< [ 63:  0](R/W/H) Performance counter 0. When DFA_PFC_GCTL[CNT0ENA] = 1, the event selected by
                                                                 DFA_PFC0_CTL[EVSEL] is counted. See also DFA_PFC_GCTL[CNT0WCLR] and DFA_PFC_GCTL[CNT0RCLR]
                                                                 for special clear count cases available for software data collection. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_pfc0_cnt_s cn; */
};
typedef union bdk_dfa_pfc0_cnt bdk_dfa_pfc0_cnt_t;

#define BDK_DFA_PFC0_CNT BDK_DFA_PFC0_CNT_FUNC()
static inline uint64_t BDK_DFA_PFC0_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_PFC0_CNT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000090ll;
    __bdk_csr_fatal("DFA_PFC0_CNT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_PFC0_CNT bdk_dfa_pfc0_cnt_t
#define bustype_BDK_DFA_PFC0_CNT BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_PFC0_CNT "DFA_PFC0_CNT"
#define device_bar_BDK_DFA_PFC0_CNT 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_PFC0_CNT 0
#define arguments_BDK_DFA_PFC0_CNT -1,-1,-1,-1

/**
 * Register (NCB) dfa_pfc0_ctl
 *
 * INTERNAL: HFA Performance Counter 0 Control Register
 */
union bdk_dfa_pfc0_ctl
{
    uint64_t u;
    struct bdk_dfa_pfc0_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t evsel                 : 6;  /**< [ 13:  8](R/W) "Performance counter 0 event selector.
                                                                 // Events [0-31] are based on PMODE(0:per cluster-DTE 1:per graph)
                                                                 0:  #Total Cycles.
                                                                 1:  #LDNODE visits.
                                                                 2:  #SDNODE visits.
                                                                 3:  #DNODE visits (LD/SD).
                                                                 4:  #LCNODE visits.
                                                                 5:  #SCNODE visits.
                                                                 6:  #CNODE visits (LC/SC).
                                                                 7:  #LMNODE visits.
                                                                 8:  #SMNODE visits.
                                                                 9:  #MNODE visits (LM/SM).
                                                                 10: #MONODE visits.
                                                                 11: #CACHE visits (DNODE,CNODE) exc: CNDRD,MPHIDX.
                                                                 12: #CACHE visits (DNODE,CNODE)+(CNDRD,MPHIDX).
                                                                 13: #MEMORY visits (MNODE+MONODE).
                                                                 14: #CNDRDs detected (occur for SCNODE-\>*MNODE transitions).
                                                                 15: #MPHIDX detected (occur for -\>LMNODE transitions).
                                                                 16: #RESCANs detected (occur when HASH collision is detected).
                                                                 17: #GWALK iterations -  stalled--packet data/result buffer.
                                                                 18: #GWALK iterations - nonstalled.
                                                                 19: #CLOAD iterations.
                                                                 20: #MLOAD iterations [NOTE: If PMODE=1 (per-graph) the MLOAD IWORD0.VGID is used to
                                                                 discern graph number].
                                                                 21: #RWORD1+ write operations.
                                                                 22: #cycles cluster is busy.
                                                                 23: #GWALK instructions.
                                                                 24: #CLOAD instructions.
                                                                 25: #MLOAD instructions [NOTE: If PMODE = 1 (per-graph) the MLOAD IWORD0.VGID is used to
                                                                 discern graph number].
                                                                 26: #GFREE instructions.
                                                                 27-30: Reserved.
                                                                 31: # node transitions detected (see DFA_PFC_GCTL[SNODE,ENODE, EDNODE] registers
                                                                 Events [32-63] are used only for PMODE = 0 (per-cluster HTE mode).
                                                                 32: #cycles a specific cluster-HTE remains active (valid state).
                                                                 33: #cycles a specific cluster-HTE waits for memory response data.
                                                                 34: #cycles a specific cluster-HTE waits in resource stall state (waiting for packet data
                                                                 or result buffer space).
                                                                 35: #cycles a specific cluster-HTE waits in resource pending state.
                                                                 36-63: Reserved." */
        uint64_t reserved_6_7          : 2;
        uint64_t cldte                 : 4;  /**< [  5:  2](R/W) Performance counter 0 cluster HTE selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster
                                                                 HTE), this field is used to select/monitor the cluster's HTE number for all events
                                                                 associated with performance counter 0. */
        uint64_t clnum                 : 2;  /**< [  1:  0](R/W) Performance counter 0 cluster selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster HTE),
                                                                 this field is used to select/monitor the cluster number for all events associated with
                                                                 performance counter 0. */
#else /* Word 0 - Little Endian */
        uint64_t clnum                 : 2;  /**< [  1:  0](R/W) Performance counter 0 cluster selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster HTE),
                                                                 this field is used to select/monitor the cluster number for all events associated with
                                                                 performance counter 0. */
        uint64_t cldte                 : 4;  /**< [  5:  2](R/W) Performance counter 0 cluster HTE selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster
                                                                 HTE), this field is used to select/monitor the cluster's HTE number for all events
                                                                 associated with performance counter 0. */
        uint64_t reserved_6_7          : 2;
        uint64_t evsel                 : 6;  /**< [ 13:  8](R/W) "Performance counter 0 event selector.
                                                                 // Events [0-31] are based on PMODE(0:per cluster-DTE 1:per graph)
                                                                 0:  #Total Cycles.
                                                                 1:  #LDNODE visits.
                                                                 2:  #SDNODE visits.
                                                                 3:  #DNODE visits (LD/SD).
                                                                 4:  #LCNODE visits.
                                                                 5:  #SCNODE visits.
                                                                 6:  #CNODE visits (LC/SC).
                                                                 7:  #LMNODE visits.
                                                                 8:  #SMNODE visits.
                                                                 9:  #MNODE visits (LM/SM).
                                                                 10: #MONODE visits.
                                                                 11: #CACHE visits (DNODE,CNODE) exc: CNDRD,MPHIDX.
                                                                 12: #CACHE visits (DNODE,CNODE)+(CNDRD,MPHIDX).
                                                                 13: #MEMORY visits (MNODE+MONODE).
                                                                 14: #CNDRDs detected (occur for SCNODE-\>*MNODE transitions).
                                                                 15: #MPHIDX detected (occur for -\>LMNODE transitions).
                                                                 16: #RESCANs detected (occur when HASH collision is detected).
                                                                 17: #GWALK iterations -  stalled--packet data/result buffer.
                                                                 18: #GWALK iterations - nonstalled.
                                                                 19: #CLOAD iterations.
                                                                 20: #MLOAD iterations [NOTE: If PMODE=1 (per-graph) the MLOAD IWORD0.VGID is used to
                                                                 discern graph number].
                                                                 21: #RWORD1+ write operations.
                                                                 22: #cycles cluster is busy.
                                                                 23: #GWALK instructions.
                                                                 24: #CLOAD instructions.
                                                                 25: #MLOAD instructions [NOTE: If PMODE = 1 (per-graph) the MLOAD IWORD0.VGID is used to
                                                                 discern graph number].
                                                                 26: #GFREE instructions.
                                                                 27-30: Reserved.
                                                                 31: # node transitions detected (see DFA_PFC_GCTL[SNODE,ENODE, EDNODE] registers
                                                                 Events [32-63] are used only for PMODE = 0 (per-cluster HTE mode).
                                                                 32: #cycles a specific cluster-HTE remains active (valid state).
                                                                 33: #cycles a specific cluster-HTE waits for memory response data.
                                                                 34: #cycles a specific cluster-HTE waits in resource stall state (waiting for packet data
                                                                 or result buffer space).
                                                                 35: #cycles a specific cluster-HTE waits in resource pending state.
                                                                 36-63: Reserved." */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_pfc0_ctl_s cn; */
};
typedef union bdk_dfa_pfc0_ctl bdk_dfa_pfc0_ctl_t;

#define BDK_DFA_PFC0_CTL BDK_DFA_PFC0_CTL_FUNC()
static inline uint64_t BDK_DFA_PFC0_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_PFC0_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000088ll;
    __bdk_csr_fatal("DFA_PFC0_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_PFC0_CTL bdk_dfa_pfc0_ctl_t
#define bustype_BDK_DFA_PFC0_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_PFC0_CTL "DFA_PFC0_CTL"
#define device_bar_BDK_DFA_PFC0_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_PFC0_CTL 0
#define arguments_BDK_DFA_PFC0_CTL -1,-1,-1,-1

/**
 * Register (NCB) dfa_pfc1_cnt
 *
 * INTERNAL: HFA Performance Counter 1 Register
 */
union bdk_dfa_pfc1_cnt
{
    uint64_t u;
    struct bdk_dfa_pfc1_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pfcnt1                : 64; /**< [ 63:  0](R/W/H) Performance counter 1. When DFA_PFC_GCTL[CNT1ENA] = 1, the event selected by
                                                                 DFA_PFC1_CTL[EVSEL] is counted. See also DFA_PFC_GCTL[CNT1WCLR] and DFA_PFC_GCTL[CNT1RCLR]
                                                                 for special clear count cases available for software data collection. */
#else /* Word 0 - Little Endian */
        uint64_t pfcnt1                : 64; /**< [ 63:  0](R/W/H) Performance counter 1. When DFA_PFC_GCTL[CNT1ENA] = 1, the event selected by
                                                                 DFA_PFC1_CTL[EVSEL] is counted. See also DFA_PFC_GCTL[CNT1WCLR] and DFA_PFC_GCTL[CNT1RCLR]
                                                                 for special clear count cases available for software data collection. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_pfc1_cnt_s cn; */
};
typedef union bdk_dfa_pfc1_cnt bdk_dfa_pfc1_cnt_t;

#define BDK_DFA_PFC1_CNT BDK_DFA_PFC1_CNT_FUNC()
static inline uint64_t BDK_DFA_PFC1_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_PFC1_CNT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000000a0ll;
    __bdk_csr_fatal("DFA_PFC1_CNT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_PFC1_CNT bdk_dfa_pfc1_cnt_t
#define bustype_BDK_DFA_PFC1_CNT BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_PFC1_CNT "DFA_PFC1_CNT"
#define device_bar_BDK_DFA_PFC1_CNT 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_PFC1_CNT 0
#define arguments_BDK_DFA_PFC1_CNT -1,-1,-1,-1

/**
 * Register (NCB) dfa_pfc1_ctl
 *
 * INTERNAL: HFA Performance Counter 1 Control Register
 */
union bdk_dfa_pfc1_ctl
{
    uint64_t u;
    struct bdk_dfa_pfc1_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t evsel                 : 6;  /**< [ 13:  8](R/W) Performance counter 1 event selector.  See events enumerated by DFA_PFC0_CTL[EVSEL]. */
        uint64_t reserved_6_7          : 2;
        uint64_t cldte                 : 4;  /**< [  5:  2](R/W) Performance counter 1 cluster HTE selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster
                                                                 HTE), this field is used to select/monitor the cluster's DTE number for all events
                                                                 associated with performance counter 1. */
        uint64_t clnum                 : 2;  /**< [  1:  0](R/W) Performance counter 1 cluster selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster HTE),
                                                                 this field is used to select/monitor the cluster number for all events associated with
                                                                 performance counter 1. */
#else /* Word 0 - Little Endian */
        uint64_t clnum                 : 2;  /**< [  1:  0](R/W) Performance counter 1 cluster selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster HTE),
                                                                 this field is used to select/monitor the cluster number for all events associated with
                                                                 performance counter 1. */
        uint64_t cldte                 : 4;  /**< [  5:  2](R/W) Performance counter 1 cluster HTE selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster
                                                                 HTE), this field is used to select/monitor the cluster's DTE number for all events
                                                                 associated with performance counter 1. */
        uint64_t reserved_6_7          : 2;
        uint64_t evsel                 : 6;  /**< [ 13:  8](R/W) Performance counter 1 event selector.  See events enumerated by DFA_PFC0_CTL[EVSEL]. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_pfc1_ctl_s cn; */
};
typedef union bdk_dfa_pfc1_ctl bdk_dfa_pfc1_ctl_t;

#define BDK_DFA_PFC1_CTL BDK_DFA_PFC1_CTL_FUNC()
static inline uint64_t BDK_DFA_PFC1_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_PFC1_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000098ll;
    __bdk_csr_fatal("DFA_PFC1_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_PFC1_CTL bdk_dfa_pfc1_ctl_t
#define bustype_BDK_DFA_PFC1_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_PFC1_CTL "DFA_PFC1_CTL"
#define device_bar_BDK_DFA_PFC1_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_PFC1_CTL 0
#define arguments_BDK_DFA_PFC1_CTL -1,-1,-1,-1

/**
 * Register (NCB) dfa_pfc2_cnt
 *
 * INTERNAL: HFA Performance Counter 2 Register
 */
union bdk_dfa_pfc2_cnt
{
    uint64_t u;
    struct bdk_dfa_pfc2_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pfcnt2                : 64; /**< [ 63:  0](R/W/H) Performance counter 2. When DFA_PFC_GCTL[CNT2ENA] = 1, the event selected by
                                                                 DFA_PFC2_CTL[EVSEL] is counted. See also DFA_PFC_GCTL[CNT2WCLR] and DFA_PFC_GCTL[CNT2RCLR]
                                                                 for special clear count cases available for software data collection. */
#else /* Word 0 - Little Endian */
        uint64_t pfcnt2                : 64; /**< [ 63:  0](R/W/H) Performance counter 2. When DFA_PFC_GCTL[CNT2ENA] = 1, the event selected by
                                                                 DFA_PFC2_CTL[EVSEL] is counted. See also DFA_PFC_GCTL[CNT2WCLR] and DFA_PFC_GCTL[CNT2RCLR]
                                                                 for special clear count cases available for software data collection. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_pfc2_cnt_s cn; */
};
typedef union bdk_dfa_pfc2_cnt bdk_dfa_pfc2_cnt_t;

#define BDK_DFA_PFC2_CNT BDK_DFA_PFC2_CNT_FUNC()
static inline uint64_t BDK_DFA_PFC2_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_PFC2_CNT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000000b0ll;
    __bdk_csr_fatal("DFA_PFC2_CNT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_PFC2_CNT bdk_dfa_pfc2_cnt_t
#define bustype_BDK_DFA_PFC2_CNT BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_PFC2_CNT "DFA_PFC2_CNT"
#define device_bar_BDK_DFA_PFC2_CNT 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_PFC2_CNT 0
#define arguments_BDK_DFA_PFC2_CNT -1,-1,-1,-1

/**
 * Register (NCB) dfa_pfc2_ctl
 *
 * INTERNAL: HFA Performance Counter 2 Control Register
 */
union bdk_dfa_pfc2_ctl
{
    uint64_t u;
    struct bdk_dfa_pfc2_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t evsel                 : 6;  /**< [ 13:  8](R/W) Performance counter 2 event selector.  See events enumerated by DFA_PFC0_CTL[EVSEL]. */
        uint64_t reserved_6_7          : 2;
        uint64_t cldte                 : 4;  /**< [  5:  2](R/W) Performance counter 2 cluster HTE selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster
                                                                 HTE), this field is used to select/monitor the cluster's HTE number for all events
                                                                 associated with performance counter 2. */
        uint64_t clnum                 : 2;  /**< [  1:  0](R/W) Performance counter 2 cluster selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster HTE),
                                                                 this field is used to select/monitor the cluster number for all events associated with
                                                                 performance counter 2. */
#else /* Word 0 - Little Endian */
        uint64_t clnum                 : 2;  /**< [  1:  0](R/W) Performance counter 2 cluster selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster HTE),
                                                                 this field is used to select/monitor the cluster number for all events associated with
                                                                 performance counter 2. */
        uint64_t cldte                 : 4;  /**< [  5:  2](R/W) Performance counter 2 cluster HTE selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster
                                                                 HTE), this field is used to select/monitor the cluster's HTE number for all events
                                                                 associated with performance counter 2. */
        uint64_t reserved_6_7          : 2;
        uint64_t evsel                 : 6;  /**< [ 13:  8](R/W) Performance counter 2 event selector.  See events enumerated by DFA_PFC0_CTL[EVSEL]. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_pfc2_ctl_s cn; */
};
typedef union bdk_dfa_pfc2_ctl bdk_dfa_pfc2_ctl_t;

#define BDK_DFA_PFC2_CTL BDK_DFA_PFC2_CTL_FUNC()
static inline uint64_t BDK_DFA_PFC2_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_PFC2_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000000a8ll;
    __bdk_csr_fatal("DFA_PFC2_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_PFC2_CTL bdk_dfa_pfc2_ctl_t
#define bustype_BDK_DFA_PFC2_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_PFC2_CTL "DFA_PFC2_CTL"
#define device_bar_BDK_DFA_PFC2_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_PFC2_CTL 0
#define arguments_BDK_DFA_PFC2_CTL -1,-1,-1,-1

/**
 * Register (NCB) dfa_pfc3_cnt
 *
 * INTERNAL: HFA Performance Counter 3 Register
 */
union bdk_dfa_pfc3_cnt
{
    uint64_t u;
    struct bdk_dfa_pfc3_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pfcnt3                : 64; /**< [ 63:  0](R/W/H) Performance counter 3. When DFA_PFC_GCTL[CNT3ENA] = 1, the event selected by
                                                                 DFA_PFC3_CTL[EVSEL] is counted. See also DFA_PFC_GCTL[CNT3WCLR] and DFA_PFC_GCTL[CNT3RCLR]
                                                                 for special clear count cases available for software data collection. */
#else /* Word 0 - Little Endian */
        uint64_t pfcnt3                : 64; /**< [ 63:  0](R/W/H) Performance counter 3. When DFA_PFC_GCTL[CNT3ENA] = 1, the event selected by
                                                                 DFA_PFC3_CTL[EVSEL] is counted. See also DFA_PFC_GCTL[CNT3WCLR] and DFA_PFC_GCTL[CNT3RCLR]
                                                                 for special clear count cases available for software data collection. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_pfc3_cnt_s cn; */
};
typedef union bdk_dfa_pfc3_cnt bdk_dfa_pfc3_cnt_t;

#define BDK_DFA_PFC3_CNT BDK_DFA_PFC3_CNT_FUNC()
static inline uint64_t BDK_DFA_PFC3_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_PFC3_CNT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000000c0ll;
    __bdk_csr_fatal("DFA_PFC3_CNT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_PFC3_CNT bdk_dfa_pfc3_cnt_t
#define bustype_BDK_DFA_PFC3_CNT BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_PFC3_CNT "DFA_PFC3_CNT"
#define device_bar_BDK_DFA_PFC3_CNT 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_PFC3_CNT 0
#define arguments_BDK_DFA_PFC3_CNT -1,-1,-1,-1

/**
 * Register (NCB) dfa_pfc3_ctl
 *
 * INTERNAL: HFA Performance Counter 3 Control Register
 */
union bdk_dfa_pfc3_ctl
{
    uint64_t u;
    struct bdk_dfa_pfc3_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t evsel                 : 6;  /**< [ 13:  8](R/W) Performance counter 3 event selector.  See events enumerated by DFA_PFC0_CTL[EVSEL]. */
        uint64_t reserved_6_7          : 2;
        uint64_t cldte                 : 4;  /**< [  5:  2](R/W) Performance counter 3 cluster HTE selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster
                                                                 HTE), this field is used to select/monitor the cluster's HTE number for all events
                                                                 associated with performance counter 3. */
        uint64_t clnum                 : 2;  /**< [  1:  0](R/W) Performance counter 3 cluster selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster HTE),
                                                                 this field is used to select/monitor the cluster number for all events associated with
                                                                 performance counter 3. */
#else /* Word 0 - Little Endian */
        uint64_t clnum                 : 2;  /**< [  1:  0](R/W) Performance counter 3 cluster selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster HTE),
                                                                 this field is used to select/monitor the cluster number for all events associated with
                                                                 performance counter 3. */
        uint64_t cldte                 : 4;  /**< [  5:  2](R/W) Performance counter 3 cluster HTE selector. When DFA_PFC_GCTL[PMODE] = 0 (per-cluster
                                                                 HTE), this field is used to select/monitor the cluster's HTE number for all events
                                                                 associated with performance counter 3. */
        uint64_t reserved_6_7          : 2;
        uint64_t evsel                 : 6;  /**< [ 13:  8](R/W) Performance counter 3 event selector.  See events enumerated by DFA_PFC0_CTL[EVSEL]. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_pfc3_ctl_s cn; */
};
typedef union bdk_dfa_pfc3_ctl bdk_dfa_pfc3_ctl_t;

#define BDK_DFA_PFC3_CTL BDK_DFA_PFC3_CTL_FUNC()
static inline uint64_t BDK_DFA_PFC3_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_PFC3_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x8462000000b8ll;
    __bdk_csr_fatal("DFA_PFC3_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_PFC3_CTL bdk_dfa_pfc3_ctl_t
#define bustype_BDK_DFA_PFC3_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_PFC3_CTL "DFA_PFC3_CTL"
#define device_bar_BDK_DFA_PFC3_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_PFC3_CTL 0
#define arguments_BDK_DFA_PFC3_CTL -1,-1,-1,-1

/**
 * Register (NCB) dfa_pfc_gctl
 *
 * INTERNAL: HFA Performance Counter Global Control Register
 */
union bdk_dfa_pfc_gctl
{
    uint64_t u;
    struct bdk_dfa_pfc_gctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_31_63        : 33;
        uint64_t vgid                  : 8;  /**< [ 30: 23](R/W) Virtual graph ID. When PMODE = 1 (per-graph selector), this field is used to
                                                                 select/monitor only those events which are associated with this selected VGID (virtual
                                                                 graph ID). This field is used globally across all four performance counters. */
        uint64_t pmode                 : 1;  /**< [ 22: 22](R/W) Select mode.
                                                                 0 = Events are selected on a per-cluster HTE number (CLNUM/CLDTE).
                                                                 DFA_PFCx_CTL[CLNUM,CLDTE] specifies the cluster-HTE for each 1 (of 4) performance
                                                                 counters.

                                                                 1 = Events are selected on a per-graph basis (VGID = virtual graph ID).
                                                                 Only EVSEL = [0...31] can be used in conjunction with
                                                                 [PMODE] = 1. DFA_PFC_GCTL[VGID] specifies the virtual graph ID used across all four
                                                                 performance counters. */
        uint64_t ednode                : 2;  /**< [ 21: 20](R/W) Ending DNODE Selector.
                                                                 When [ENODE]=0/1(*DNODE), this field is used to further specify the ending DNODE
                                                                 transition  sub-type:
                                                                 0x0 = ALL DNODE sub-types.
                                                                 0x1 = -\>D2e (explicit DNODE transition node-arc alone transitions to DNODE).
                                                                 0x2 = -\>D2i (implicit DNODE transition:arc-present triggers transition).
                                                                 0x3 = -\>D1r (rescan DNODE transition). */
        uint64_t enode                 : 4;  /**< [ 19: 16](R/W) Ending node selector.
                                                                 When DFA_PFCx_CTL[EVSEL]=Node Transition(31), [ENODE] is used to select ending
                                                                 node, and the SNODE field is used to select the starting node.
                                                                 0x0 = LDNODE.
                                                                 0x1 = SDNODE.
                                                                 0x2 = LCNODE.
                                                                 0x3 = SCNODE.
                                                                 0x4 = LMNODE.
                                                                 0x5 = SMNODE.
                                                                 0x6 = MONODE.
                                                                 0x7 = Reserved.
                                                                 0x8 = LONODE.
                                                                 0x9 = SONODE. */
        uint64_t snode                 : 4;  /**< [ 15: 12](R/W) Starting node selector.
                                                                 When DFA_PFCx_CTL[EVSEL]=Node Transition(31), [SNODE] is used to select starting
                                                                 node, and the ENODE field is used to select the ending node.
                                                                 0x0 = LDNODE.
                                                                 0x1 = SDNODE.
                                                                 0x2 = LCNODE.
                                                                 0x3 = SCNODE.
                                                                 0x4 = LMNODE.
                                                                 0x5 = SMNODE.
                                                                 0x6 = MONODE.
                                                                 0x7 = Reserved.
                                                                 0x8 = LONODE.
                                                                 0x9 = SONODE. */
        uint64_t cnt3rclr              : 1;  /**< [ 11: 11](R/W) Performance counter 3 read clear. If this bit is set, CSR read operations to DFA_PFC3_CNT
                                                                 clear the count value. This allows software to maintain 'cumulative' counters to avoid
                                                                 hardware wraparound. */
        uint64_t cnt2rclr              : 1;  /**< [ 10: 10](R/W) Performance counter 2 read clear. If this bit is set, CSR read operations to DFA_PFC2_CNT
                                                                 clear the count value. This allows software to maintain 'cumulative' counters to avoid
                                                                 hardware wraparound. */
        uint64_t cnt1rclr              : 1;  /**< [  9:  9](R/W) Performance counter 1 read clear. If this bit is set, CSR read operations to DFA_PFC1_CNT
                                                                 clear the count value. This allows software to maintain 'cumulative' counters to avoid
                                                                 hardware wraparound. */
        uint64_t cnt0rclr              : 1;  /**< [  8:  8](R/W) Performance counter 0 read clear. If this bit is set, CSR read operations to DFA_PFC0_CNT
                                                                 clear the count value. This allows software to maintain 'cumulative' counters to avoid
                                                                 hardware wraparound. */
        uint64_t cnt3wclr              : 1;  /**< [  7:  7](R/W) Performance counter 3 write clear. If this bit is set, CSR write operations to
                                                                 DFA_PFC3_CNT clear the count value. If this bit is clear, CSR write operations to
                                                                 DFA_PFC3_CNT continue the count from the written value. */
        uint64_t cnt2wclr              : 1;  /**< [  6:  6](R/W) Performance counter 2 write clear. If this bit is set, CSR write operations to
                                                                 DFA_PFC2_CNT clear the count value. If this bit is clear, CSR write operations to
                                                                 DFA_PFC2_CNT continue the count from the written value. */
        uint64_t cnt1wclr              : 1;  /**< [  5:  5](R/W) Performance counter 1 write clear. If this bit is set, CSR write operations to
                                                                 DFA_PFC1_CNT clear the count value. If this bit is clear, CSR write operations to
                                                                 DFA_PFC1_CNT continue the count from the written value. */
        uint64_t cnt0wclr              : 1;  /**< [  4:  4](R/W) Performance counter 0 write clear. If this bit is set, CSR write operations to
                                                                 DFA_PFC0_CNT clear the count value. If this bit is clear, CSR write operations to
                                                                 DFA_PFC0_CNT continue the count from the written value. */
        uint64_t cnt3ena               : 1;  /**< [  3:  3](R/W) Performance counter 3 enable. When this bit is set, the performance counter 3 is enabled. */
        uint64_t cnt2ena               : 1;  /**< [  2:  2](R/W) Performance counter 2 enable. When this bit is set, the performance counter 2 is enabled. */
        uint64_t cnt1ena               : 1;  /**< [  1:  1](R/W) Performance counter 1 enable. When this bit is set, the performance counter 1 is enabled. */
        uint64_t cnt0ena               : 1;  /**< [  0:  0](R/W) Performance counter 0 enable. When this bit is set, the performance counter 0 is enabled. */
#else /* Word 0 - Little Endian */
        uint64_t cnt0ena               : 1;  /**< [  0:  0](R/W) Performance counter 0 enable. When this bit is set, the performance counter 0 is enabled. */
        uint64_t cnt1ena               : 1;  /**< [  1:  1](R/W) Performance counter 1 enable. When this bit is set, the performance counter 1 is enabled. */
        uint64_t cnt2ena               : 1;  /**< [  2:  2](R/W) Performance counter 2 enable. When this bit is set, the performance counter 2 is enabled. */
        uint64_t cnt3ena               : 1;  /**< [  3:  3](R/W) Performance counter 3 enable. When this bit is set, the performance counter 3 is enabled. */
        uint64_t cnt0wclr              : 1;  /**< [  4:  4](R/W) Performance counter 0 write clear. If this bit is set, CSR write operations to
                                                                 DFA_PFC0_CNT clear the count value. If this bit is clear, CSR write operations to
                                                                 DFA_PFC0_CNT continue the count from the written value. */
        uint64_t cnt1wclr              : 1;  /**< [  5:  5](R/W) Performance counter 1 write clear. If this bit is set, CSR write operations to
                                                                 DFA_PFC1_CNT clear the count value. If this bit is clear, CSR write operations to
                                                                 DFA_PFC1_CNT continue the count from the written value. */
        uint64_t cnt2wclr              : 1;  /**< [  6:  6](R/W) Performance counter 2 write clear. If this bit is set, CSR write operations to
                                                                 DFA_PFC2_CNT clear the count value. If this bit is clear, CSR write operations to
                                                                 DFA_PFC2_CNT continue the count from the written value. */
        uint64_t cnt3wclr              : 1;  /**< [  7:  7](R/W) Performance counter 3 write clear. If this bit is set, CSR write operations to
                                                                 DFA_PFC3_CNT clear the count value. If this bit is clear, CSR write operations to
                                                                 DFA_PFC3_CNT continue the count from the written value. */
        uint64_t cnt0rclr              : 1;  /**< [  8:  8](R/W) Performance counter 0 read clear. If this bit is set, CSR read operations to DFA_PFC0_CNT
                                                                 clear the count value. This allows software to maintain 'cumulative' counters to avoid
                                                                 hardware wraparound. */
        uint64_t cnt1rclr              : 1;  /**< [  9:  9](R/W) Performance counter 1 read clear. If this bit is set, CSR read operations to DFA_PFC1_CNT
                                                                 clear the count value. This allows software to maintain 'cumulative' counters to avoid
                                                                 hardware wraparound. */
        uint64_t cnt2rclr              : 1;  /**< [ 10: 10](R/W) Performance counter 2 read clear. If this bit is set, CSR read operations to DFA_PFC2_CNT
                                                                 clear the count value. This allows software to maintain 'cumulative' counters to avoid
                                                                 hardware wraparound. */
        uint64_t cnt3rclr              : 1;  /**< [ 11: 11](R/W) Performance counter 3 read clear. If this bit is set, CSR read operations to DFA_PFC3_CNT
                                                                 clear the count value. This allows software to maintain 'cumulative' counters to avoid
                                                                 hardware wraparound. */
        uint64_t snode                 : 4;  /**< [ 15: 12](R/W) Starting node selector.
                                                                 When DFA_PFCx_CTL[EVSEL]=Node Transition(31), [SNODE] is used to select starting
                                                                 node, and the ENODE field is used to select the ending node.
                                                                 0x0 = LDNODE.
                                                                 0x1 = SDNODE.
                                                                 0x2 = LCNODE.
                                                                 0x3 = SCNODE.
                                                                 0x4 = LMNODE.
                                                                 0x5 = SMNODE.
                                                                 0x6 = MONODE.
                                                                 0x7 = Reserved.
                                                                 0x8 = LONODE.
                                                                 0x9 = SONODE. */
        uint64_t enode                 : 4;  /**< [ 19: 16](R/W) Ending node selector.
                                                                 When DFA_PFCx_CTL[EVSEL]=Node Transition(31), [ENODE] is used to select ending
                                                                 node, and the SNODE field is used to select the starting node.
                                                                 0x0 = LDNODE.
                                                                 0x1 = SDNODE.
                                                                 0x2 = LCNODE.
                                                                 0x3 = SCNODE.
                                                                 0x4 = LMNODE.
                                                                 0x5 = SMNODE.
                                                                 0x6 = MONODE.
                                                                 0x7 = Reserved.
                                                                 0x8 = LONODE.
                                                                 0x9 = SONODE. */
        uint64_t ednode                : 2;  /**< [ 21: 20](R/W) Ending DNODE Selector.
                                                                 When [ENODE]=0/1(*DNODE), this field is used to further specify the ending DNODE
                                                                 transition  sub-type:
                                                                 0x0 = ALL DNODE sub-types.
                                                                 0x1 = -\>D2e (explicit DNODE transition node-arc alone transitions to DNODE).
                                                                 0x2 = -\>D2i (implicit DNODE transition:arc-present triggers transition).
                                                                 0x3 = -\>D1r (rescan DNODE transition). */
        uint64_t pmode                 : 1;  /**< [ 22: 22](R/W) Select mode.
                                                                 0 = Events are selected on a per-cluster HTE number (CLNUM/CLDTE).
                                                                 DFA_PFCx_CTL[CLNUM,CLDTE] specifies the cluster-HTE for each 1 (of 4) performance
                                                                 counters.

                                                                 1 = Events are selected on a per-graph basis (VGID = virtual graph ID).
                                                                 Only EVSEL = [0...31] can be used in conjunction with
                                                                 [PMODE] = 1. DFA_PFC_GCTL[VGID] specifies the virtual graph ID used across all four
                                                                 performance counters. */
        uint64_t vgid                  : 8;  /**< [ 30: 23](R/W) Virtual graph ID. When PMODE = 1 (per-graph selector), this field is used to
                                                                 select/monitor only those events which are associated with this selected VGID (virtual
                                                                 graph ID). This field is used globally across all four performance counters. */
        uint64_t reserved_31_63        : 33;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dfa_pfc_gctl_s cn; */
};
typedef union bdk_dfa_pfc_gctl bdk_dfa_pfc_gctl_t;

#define BDK_DFA_PFC_GCTL BDK_DFA_PFC_GCTL_FUNC()
static inline uint64_t BDK_DFA_PFC_GCTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DFA_PFC_GCTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX))
        return 0x846200000080ll;
    __bdk_csr_fatal("DFA_PFC_GCTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_DFA_PFC_GCTL bdk_dfa_pfc_gctl_t
#define bustype_BDK_DFA_PFC_GCTL BDK_CSR_TYPE_NCB
#define basename_BDK_DFA_PFC_GCTL "DFA_PFC_GCTL"
#define device_bar_BDK_DFA_PFC_GCTL 0x0 /* PF_BAR0 */
#define busnum_BDK_DFA_PFC_GCTL 0
#define arguments_BDK_DFA_PFC_GCTL -1,-1,-1,-1

#endif /* __BDK_CSRS_DFA_H__ */
