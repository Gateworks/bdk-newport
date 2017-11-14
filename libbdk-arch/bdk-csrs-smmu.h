#ifndef __BDK_CSRS_SMMU_H__
#define __BDK_CSRS_SMMU_H__
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
 * Cavium SMMU.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration smmu_bar_e
 *
 * SMMU Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_SMMU_BAR_E_SMMUX_PF_BAR0_CN8(a) (0x830000000000ll + 0x1000000000ll * (a))
#define BDK_SMMU_BAR_E_SMMUX_PF_BAR0_CN8_SIZE 0x8000000ull
#define BDK_SMMU_BAR_E_SMMUX_PF_BAR0_CN9(a) (0x830000000000ll + 0x1000000000ll * (a))
#define BDK_SMMU_BAR_E_SMMUX_PF_BAR0_CN9_SIZE 0x200000ull
#define BDK_SMMU_BAR_E_SMMUX_PF_BAR4(a) (0x83000f000000ll + 0x1000000000ll * (a))
#define BDK_SMMU_BAR_E_SMMUX_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration smmu_cerror_e
 *
 * SMMU Command Queue Error Enumeration
 */
#define BDK_SMMU_CERROR_E_ABT (2)
#define BDK_SMMU_CERROR_E_ILL (1)
#define BDK_SMMU_CERROR_E_NONE (0)

/**
 * Enumeration smmu_cmd_e
 *
 * SMMU Command Queue Codes Enumeration
 */
#define BDK_SMMU_CMD_E_ATC_INV (0x40)
#define BDK_SMMU_CMD_E_CFGI_CD (5)
#define BDK_SMMU_CMD_E_CFGI_CD_ALL (6)
#define BDK_SMMU_CMD_E_CFGI_STE (3)
#define BDK_SMMU_CMD_E_CFGI_STE_RANGE (4)
#define BDK_SMMU_CMD_E_PREFETCH_ADDR (2)
#define BDK_SMMU_CMD_E_PREFETCH_CONFIG (1)
#define BDK_SMMU_CMD_E_PRI_RESP (0x41)
#define BDK_SMMU_CMD_E_RESUME (0x44)
#define BDK_SMMU_CMD_E_STALL_TERM (0x45)
#define BDK_SMMU_CMD_E_SYNC (0x46)
#define BDK_SMMU_CMD_E_TLBI_EL2_ALL (0x20)
#define BDK_SMMU_CMD_E_TLBI_EL2_ASID (0x21)
#define BDK_SMMU_CMD_E_TLBI_EL2_VA (0x22)
#define BDK_SMMU_CMD_E_TLBI_EL2_VAA (0x23)
#define BDK_SMMU_CMD_E_TLBI_EL3_ALL (0x18)
#define BDK_SMMU_CMD_E_TLBI_EL3_VA (0x1a)
#define BDK_SMMU_CMD_E_TLBI_NH_ALL (0x10)
#define BDK_SMMU_CMD_E_TLBI_NH_ASID (0x11)
#define BDK_SMMU_CMD_E_TLBI_NH_VA (0x12)
#define BDK_SMMU_CMD_E_TLBI_NH_VAA (0x13)
#define BDK_SMMU_CMD_E_TLBI_NSNH_ALL (0x30)
#define BDK_SMMU_CMD_E_TLBI_S12_VMALL (0x28)
#define BDK_SMMU_CMD_E_TLBI_S2_IPA (0x2a)

/**
 * Enumeration smmu_ctype_e
 *
 * SMMU Context Bank Type Enumeration
 * Enumerates the values of SMMU()_CBAR()[CTYPE].
 */
#define BDK_SMMU_CTYPE_E_STAGE1_BYP2 (1)
#define BDK_SMMU_CTYPE_E_STAGE1_FAULT2 (2)
#define BDK_SMMU_CTYPE_E_STAGE1_STAGE2 (3)
#define BDK_SMMU_CTYPE_E_STAGE2 (0)

/**
 * Enumeration smmu_event_e
 *
 * SMMU Event Record Codes Enumeration
 * Enumerates event record types.
 */
#define BDK_SMMU_EVENT_E_C_BAD_CD (0xa)
#define BDK_SMMU_EVENT_E_C_BAD_STE (4)
#define BDK_SMMU_EVENT_E_C_BAD_STREAMID (2)
#define BDK_SMMU_EVENT_E_C_BAD_SUBSTREAMID (8)
#define BDK_SMMU_EVENT_E_E_PAGE_REQUEST (0x24)
#define BDK_SMMU_EVENT_E_F_ACCESS (0x12)
#define BDK_SMMU_EVENT_E_F_ADDR_SIZE (0x11)
#define BDK_SMMU_EVENT_E_F_BAD_ATS_TREQ (5)
#define BDK_SMMU_EVENT_E_F_CD_FETCH (9)
#define BDK_SMMU_EVENT_E_F_CFG_CONFLICT (0x21)
#define BDK_SMMU_EVENT_E_F_PERMISSION (0x13)
#define BDK_SMMU_EVENT_E_F_STE_FETCH (3)
#define BDK_SMMU_EVENT_E_F_STREAM_DISABLED (6)
#define BDK_SMMU_EVENT_E_F_TLB_CONFLICT (0x20)
#define BDK_SMMU_EVENT_E_F_TRANSLATION (0x10)
#define BDK_SMMU_EVENT_E_F_TRANSL_FORBIDDEN (7)
#define BDK_SMMU_EVENT_E_F_UUT (1)
#define BDK_SMMU_EVENT_E_F_WALK_EABT (0xb)
#define BDK_SMMU_EVENT_E_INTERNAL_ERR (0xfd)
#define BDK_SMMU_EVENT_E_INV_REQ (0xff)
#define BDK_SMMU_EVENT_E_INV_STAGE (0xfe)

/**
 * Enumeration smmu_int_vec_e
 *
 * SMMU MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_SMMU_INT_VEC_E_CBX_FSR(a) (0 + 2 * (a))
#define BDK_SMMU_INT_VEC_E_CBX_FSR_CLEAR(a) (1 + 2 * (a))
#define BDK_SMMU_INT_VEC_E_ERRFLG_CN81XX (0x84)
#define BDK_SMMU_INT_VEC_E_ERRFLG_CN88XX (0x104)
#define BDK_SMMU_INT_VEC_E_ERRFLG_CN83XX (0x104)
#define BDK_SMMU_INT_VEC_E_ERR_CLEAR_CN81XX (0x85)
#define BDK_SMMU_INT_VEC_E_ERR_CLEAR_CN88XX (0x105)
#define BDK_SMMU_INT_VEC_E_ERR_CLEAR_CN83XX (0x105)
#define BDK_SMMU_INT_VEC_E_NSGFSR_CN81XX (0x80)
#define BDK_SMMU_INT_VEC_E_NSGFSR_CN88XX (0x100)
#define BDK_SMMU_INT_VEC_E_NSGFSR_CN83XX (0x100)
#define BDK_SMMU_INT_VEC_E_NSGFSR_CLEAR_CN81XX (0x81)
#define BDK_SMMU_INT_VEC_E_NSGFSR_CLEAR_CN88XX (0x101)
#define BDK_SMMU_INT_VEC_E_NSGFSR_CLEAR_CN83XX (0x101)
#define BDK_SMMU_INT_VEC_E_SGFSR_CN81XX (0x82)
#define BDK_SMMU_INT_VEC_E_SGFSR_CN88XX (0x102)
#define BDK_SMMU_INT_VEC_E_SGFSR_CN83XX (0x102)
#define BDK_SMMU_INT_VEC_E_SGFSR_CLEAR_CN81XX (0x83)
#define BDK_SMMU_INT_VEC_E_SGFSR_CLEAR_CN88XX (0x103)
#define BDK_SMMU_INT_VEC_E_SGFSR_CLEAR_CN83XX (0x103)

/**
 * Enumeration smmu_pmcg_e
 *
 * SMMU PMCG Events Enumeration
 * Enumerates counter types.
 */
#define BDK_SMMU_PMCG_E_ACTIVE_CLOCKS (0x80)
#define BDK_SMMU_PMCG_E_ARCH_EVENT6 (6)
#define BDK_SMMU_PMCG_E_ARCH_EVENT7 (7)
#define BDK_SMMU_PMCG_E_CFG_L2C_READ (5)
#define BDK_SMMU_PMCG_E_CLOCKS (0)
#define BDK_SMMU_PMCG_E_CTX_CAM_MISS (3)
#define BDK_SMMU_PMCG_E_TRANSACTION (1)
#define BDK_SMMU_PMCG_E_TRANSACTION_WALKS (2)
#define BDK_SMMU_PMCG_E_TRAN_L2C_READ (4)
#define BDK_SMMU_PMCG_E_WCU_HIT (0x81)
#define BDK_SMMU_PMCG_E_WCU_LVL0_MISS (0x82)
#define BDK_SMMU_PMCG_E_WCU_LVL1_MISS (0x83)
#define BDK_SMMU_PMCG_E_WCU_LVL2_MISS (0x84)

/**
 * Register (NCB) smmu#_active_pc
 *
 * SMMU Active Cycles Register
 * This register counts every core-clock cycle that the SMMU clocks are active.
 */
union bdk_smmux_active_pc
{
    uint64_t u;
    struct bdk_smmux_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](RO/H) Counts the number of active core-clock cycles in the conditional clock domain.
                                                                 Internal:
                                                                 Values are duplicated across each SMMU that shares an IOB. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](RO/H) Counts the number of active core-clock cycles in the conditional clock domain.
                                                                 Internal:
                                                                 Values are duplicated across each SMMU that shares an IOB. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_active_pc_s cn; */
};
typedef union bdk_smmux_active_pc bdk_smmux_active_pc_t;

static inline uint64_t BDK_SMMUX_ACTIVE_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_ACTIVE_PC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000021000ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000021000ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000021000ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_ACTIVE_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_ACTIVE_PC(a) bdk_smmux_active_pc_t
#define bustype_BDK_SMMUX_ACTIVE_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_ACTIVE_PC(a) "SMMUX_ACTIVE_PC"
#define device_bar_BDK_SMMUX_ACTIVE_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_ACTIVE_PC(a) (a)
#define arguments_BDK_SMMUX_ACTIVE_PC(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_agbpa
 *
 * SMMU Alternate Global Bypass Attribute Register
 * This register is intended to allow an implementation to apply an additional non-
 * architected attributes or tag to bypassing transactions, for example a traffic
 * routing identifier.
 *
 * If this field is unsupported by an implementation, it is RES0.  It is not
 * intended for this register to be used to further modify existing architected
 * bypass attributes which are controlled using GPBA.
 */
union bdk_smmux_agbpa
{
    uint32_t u;
    struct bdk_smmux_agbpa_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_17_31        : 15;
        uint32_t qos                   : 1;  /**< [ 16: 16](R/W) SMMU(0)_S_AGBPA[QOS] */
        uint32_t reserved_8_15         : 8;
        uint32_t cpid                  : 8;  /**< [  7:  0](R/W) SMMU(0)_S_AGBPA[CPID] */
#else /* Word 0 - Little Endian */
        uint32_t cpid                  : 8;  /**< [  7:  0](R/W) SMMU(0)_S_AGBPA[CPID] */
        uint32_t reserved_8_15         : 8;
        uint32_t qos                   : 1;  /**< [ 16: 16](R/W) SMMU(0)_S_AGBPA[QOS] */
        uint32_t reserved_17_31        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_agbpa_s cn; */
};
typedef union bdk_smmux_agbpa bdk_smmux_agbpa_t;

static inline uint64_t BDK_SMMUX_AGBPA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_AGBPA(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000048ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_AGBPA", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_AGBPA(a) bdk_smmux_agbpa_t
#define bustype_BDK_SMMUX_AGBPA(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_AGBPA(a) "SMMUX_AGBPA"
#define device_bar_BDK_SMMUX_AGBPA(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_AGBPA(a) (a)
#define arguments_BDK_SMMUX_AGBPA(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_aidr
 *
 * SMMU Auxiliary Identification Register
 * This register identifies the SMMU architecture version to which the implementation conforms.
 */
union bdk_smmux_aidr
{
    uint32_t u;
    struct bdk_smmux_aidr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t archmajorrev          : 4;  /**< [  7:  4](RO) Indicates SMMUv3.1. */
        uint32_t archminorrev          : 4;  /**< [  3:  0](RO) Indicates SMMUv3.1. */
#else /* Word 0 - Little Endian */
        uint32_t archminorrev          : 4;  /**< [  3:  0](RO) Indicates SMMUv3.1. */
        uint32_t archmajorrev          : 4;  /**< [  7:  4](RO) Indicates SMMUv3.1. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_aidr_s cn; */
};
typedef union bdk_smmux_aidr bdk_smmux_aidr_t;

static inline uint64_t BDK_SMMUX_AIDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_AIDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x83000000001cll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_AIDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_AIDR(a) bdk_smmux_aidr_t
#define bustype_BDK_SMMUX_AIDR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_AIDR(a) "SMMUX_AIDR"
#define device_bar_BDK_SMMUX_AIDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_AIDR(a) (a)
#define arguments_BDK_SMMUX_AIDR(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_bist_status
 *
 * SMMU BIST Status Register
 * Contains the BIST status for the memories.
 */
union bdk_smmux_bist_status
{
    uint64_t u;
    struct bdk_smmux_bist_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bist                  : 64; /**< [ 63:  0](RO) Memory BIST status. 0 = pass, 1 = fail.
                                                                 Internal:
                                                                 Values are duplicated across each SMMU
                                                                 that shares an IOB.
                                                                 \<23\> = CSR_VMID_CAM.
                                                                 \<22\> = CSR_ASID_CAM.
                                                                 \<21\> = SIL_CAM.
                                                                 \<20\> = MSIX.
                                                                 \<19\> = WCTL.
                                                                 \<18\> = XL_MFIFO.
                                                                 \<17\> = TCTL.
                                                                 \<16\> = CONTEXT_IDR.
                                                                 \<15\> = CB_FRSYNRA.
                                                                 \<14\> = CB_IPAFAR.
                                                                 \<13\> = CB_FSYNR0.
                                                                 \<12\> = CB_FAR.
                                                                 \<11\> = S2CR.
                                                                 \<10\> = CB_ACTLR.
                                                                 \<9\> = CB_TCR2.
                                                                 \<8\> = SSDR.
                                                                 \<7\> = SCTLR.
                                                                 \<6\> = CB_TTBR0.
                                                                 \<5\> = CB_TTBR1.
                                                                 \<4\> = CB_TCR.
                                                                 \<3\> = CBA2R.
                                                                 \<2\> = CBAR.
                                                                 \<1\> = CB_MAIR0.
                                                                 \<0\> = CB_MAIR1. */
#else /* Word 0 - Little Endian */
        uint64_t bist                  : 64; /**< [ 63:  0](RO) Memory BIST status. 0 = pass, 1 = fail.
                                                                 Internal:
                                                                 Values are duplicated across each SMMU
                                                                 that shares an IOB.
                                                                 \<23\> = CSR_VMID_CAM.
                                                                 \<22\> = CSR_ASID_CAM.
                                                                 \<21\> = SIL_CAM.
                                                                 \<20\> = MSIX.
                                                                 \<19\> = WCTL.
                                                                 \<18\> = XL_MFIFO.
                                                                 \<17\> = TCTL.
                                                                 \<16\> = CONTEXT_IDR.
                                                                 \<15\> = CB_FRSYNRA.
                                                                 \<14\> = CB_IPAFAR.
                                                                 \<13\> = CB_FSYNR0.
                                                                 \<12\> = CB_FAR.
                                                                 \<11\> = S2CR.
                                                                 \<10\> = CB_ACTLR.
                                                                 \<9\> = CB_TCR2.
                                                                 \<8\> = SSDR.
                                                                 \<7\> = SCTLR.
                                                                 \<6\> = CB_TTBR0.
                                                                 \<5\> = CB_TTBR1.
                                                                 \<4\> = CB_TCR.
                                                                 \<3\> = CBA2R.
                                                                 \<2\> = CBAR.
                                                                 \<1\> = CB_MAIR0.
                                                                 \<0\> = CB_MAIR1. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_bist_status_s cn; */
};
typedef union bdk_smmux_bist_status bdk_smmux_bist_status_t;

static inline uint64_t BDK_SMMUX_BIST_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_BIST_STATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000020010ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000020010ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000020010ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_BIST_STATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_BIST_STATUS(a) bdk_smmux_bist_status_t
#define bustype_BDK_SMMUX_BIST_STATUS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_BIST_STATUS(a) "SMMUX_BIST_STATUS"
#define device_bar_BDK_SMMUX_BIST_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_BIST_STATUS(a) (a)
#define arguments_BDK_SMMUX_BIST_STATUS(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cb#_actlr
 *
 * SMMU Context Auxiliary Control Register
 * This register contains implementation specific context fields.
 */
union bdk_smmux_cbx_actlr
{
    uint32_t u;
    struct bdk_smmux_cbx_actlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qos                   : 4;  /**< [ 31: 28](R/W) L2C quality-of-service value to use for transactions to this context. */
        uint32_t reserved_16_27        : 12;
        uint32_t dis_bnk               : 16; /**< [ 15:  0](R/W) Bitmask of sections of TLB to disable for fills caused by transactions to this
                                                                 context. May be used to partition the TLB to achieve QoS; note the WCU is not likewise
                                                                 partitioned. If a context is marked secure but accessed insecurely, than this register is
                                                                 RAZ/WI. For nested translations, the primary context's [DIS_BNK] is used. */
#else /* Word 0 - Little Endian */
        uint32_t dis_bnk               : 16; /**< [ 15:  0](R/W) Bitmask of sections of TLB to disable for fills caused by transactions to this
                                                                 context. May be used to partition the TLB to achieve QoS; note the WCU is not likewise
                                                                 partitioned. If a context is marked secure but accessed insecurely, than this register is
                                                                 RAZ/WI. For nested translations, the primary context's [DIS_BNK] is used. */
        uint32_t reserved_16_27        : 12;
        uint32_t qos                   : 4;  /**< [ 31: 28](R/W) L2C quality-of-service value to use for transactions to this context. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_actlr_s cn; */
};
typedef union bdk_smmux_cbx_actlr bdk_smmux_cbx_actlr_t;

static inline uint64_t BDK_SMMUX_CBX_ACTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_ACTLR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000004ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000004ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000004ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_ACTLR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_ACTLR(a,b) bdk_smmux_cbx_actlr_t
#define bustype_BDK_SMMUX_CBX_ACTLR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_ACTLR(a,b) "SMMUX_CBX_ACTLR"
#define device_bar_BDK_SMMUX_CBX_ACTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_ACTLR(a,b) (a)
#define arguments_BDK_SMMUX_CBX_ACTLR(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_contextidr
 *
 * SMMU Context Identification Register
 * Identifies the current process identifier. Used only by software.
 * This register is used by stage 1 context banks.
 */
union bdk_smmux_cbx_contextidr
{
    uint32_t u;
    struct bdk_smmux_cbx_contextidr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t procid                : 32; /**< [ 31:  0](R/W) Process identifier. Used only by software. */
#else /* Word 0 - Little Endian */
        uint32_t procid                : 32; /**< [ 31:  0](R/W) Process identifier. Used only by software. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_contextidr_s cn; */
};
typedef union bdk_smmux_cbx_contextidr bdk_smmux_cbx_contextidr_t;

static inline uint64_t BDK_SMMUX_CBX_CONTEXTIDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_CONTEXTIDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000034ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000034ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000034ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_CONTEXTIDR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_CONTEXTIDR(a,b) bdk_smmux_cbx_contextidr_t
#define bustype_BDK_SMMUX_CBX_CONTEXTIDR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_CONTEXTIDR(a,b) "SMMUX_CBX_CONTEXTIDR"
#define device_bar_BDK_SMMUX_CBX_CONTEXTIDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_CONTEXTIDR(a,b) (a)
#define arguments_BDK_SMMUX_CBX_CONTEXTIDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_far
 *
 * SMMU Context Fault Address Register
 * This register is used by both stage 1 and stage 2 context banks. This register might be
 * updated as the result of:
 *
 * 1. A stage 2 only context fault for an upstream client device. The IPA supplied by the
 * upstream client device is recorded.
 *
 * 2. A nested stage 1 + stage 2 fault. The VA supplied by the upstream client device to the
 * stage 1 context is recorded. Note: the IPA is not recorded but the fault is tagged as nested
 * and the index of the stage 1 context is recorded in SMMU()_CB()_FSYNR0.
 *
 * 3. An ATOS operation at stage 1 in a nested context that faults at stage 2. The VA supplied by
 * to the global or stage 1 address translation operation is recorded. The IPA is recorded in
 * SMMU()_CB()_IPAFAR below and the fault is tagged as nested. The index of the stage 1
 * context is recorded in SMMU()_CB()_FSYNR0.
 */
union bdk_smmux_cbx_far
{
    uint64_t u;
    struct bdk_smmux_cbx_far_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t faddr                 : 37; /**< [ 48: 12](R/W/H) Fault address, the input IOVA of the faulting access. This register might be updated as
                                                                 the result of a translation fault for an upstream client device. For CNXXXX \<11:0\> are
                                                                 always zero. */
        uint64_t reserved_0_11         : 12;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_11         : 12;
        uint64_t faddr                 : 37; /**< [ 48: 12](R/W/H) Fault address, the input IOVA of the faulting access. This register might be updated as
                                                                 the result of a translation fault for an upstream client device. For CNXXXX \<11:0\> are
                                                                 always zero. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_far_s cn; */
};
typedef union bdk_smmux_cbx_far bdk_smmux_cbx_far_t;

static inline uint64_t BDK_SMMUX_CBX_FAR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_FAR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000060ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000060ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000060ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_FAR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_FAR(a,b) bdk_smmux_cbx_far_t
#define bustype_BDK_SMMUX_CBX_FAR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_FAR(a,b) "SMMUX_CBX_FAR"
#define device_bar_BDK_SMMUX_CBX_FAR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_FAR(a,b) (a)
#define arguments_BDK_SMMUX_CBX_FAR(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_fsr
 *
 * SMMU Context Translation Fault Status Register
 * Provides memory system fault status information. This register is used by both stage 1 and
 * stage 2 context banks.
 */
union bdk_smmux_cbx_fsr
{
    uint32_t u;
    struct bdk_smmux_cbx_fsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t multi                 : 1;  /**< [ 31: 31](R/W1C/H) Multiple error conditions.
                                                                 0 = No multiple error condition was encountered.
                                                                 1 = An error occurred while the value in SMMU()_(S)GFSR was nonzero. */
        uint32_t ss                    : 1;  /**< [ 30: 30](RO) Stalled status.
                                                                 0 = SMMU not stalled due to a fault in this bank.
                                                                 1 = SMMU stalled due to a fault in this bank.

                                                                 For CNXXXX always zero, no stalls. */
        uint32_t reserved_11_29        : 19;
        uint32_t fmt                   : 2;  /**< [ 10:  9](RO) Translation scheme.
                                                                 0x0 = AArch32 short-descriptor translation scheme.
                                                                 0x1 = AArch32 long-descriptor translation scheme.
                                                                 0x2 = AArch64 translation scheme.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX always AArch64. */
        uint32_t uut                   : 1;  /**< [  8:  8](RAZ) Unsupported upstream transaction fault. */
        uint32_t asf                   : 1;  /**< [  7:  7](R/W1C/H) Incorrect address size fault. */
        uint32_t tlblkf                : 1;  /**< [  6:  6](RAZ) TLB lock fault. For CNXXXX always zero, no TLB locks. */
        uint32_t tlbmcf                : 1;  /**< [  5:  5](R/W1C/H) TLB match conflict fault. */
        uint32_t ef                    : 1;  /**< [  4:  4](R/W1C/H) External fault. */
        uint32_t pf                    : 1;  /**< [  3:  3](R/W1C/H) Permission fault.
                                                                 0 = No permission fault.
                                                                 1 = Fault caused by insufficient permission to complete a memory access has occurred. */
        uint32_t aff                   : 1;  /**< [  2:  2](R/W1C/H) Access flag fault.
                                                                 0 = No access flag fault.
                                                                 1 = Fault caused by the access flag being set for the address being accessed has occurred. */
        uint32_t tf                    : 1;  /**< [  1:  1](R/W1C/H) Translation fault.
                                                                 0 = No translation fault.
                                                                 1 = Translation fault has occurred. The mapping for the address being accessed is invalid. */
        uint32_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0            : 1;
        uint32_t tf                    : 1;  /**< [  1:  1](R/W1C/H) Translation fault.
                                                                 0 = No translation fault.
                                                                 1 = Translation fault has occurred. The mapping for the address being accessed is invalid. */
        uint32_t aff                   : 1;  /**< [  2:  2](R/W1C/H) Access flag fault.
                                                                 0 = No access flag fault.
                                                                 1 = Fault caused by the access flag being set for the address being accessed has occurred. */
        uint32_t pf                    : 1;  /**< [  3:  3](R/W1C/H) Permission fault.
                                                                 0 = No permission fault.
                                                                 1 = Fault caused by insufficient permission to complete a memory access has occurred. */
        uint32_t ef                    : 1;  /**< [  4:  4](R/W1C/H) External fault. */
        uint32_t tlbmcf                : 1;  /**< [  5:  5](R/W1C/H) TLB match conflict fault. */
        uint32_t tlblkf                : 1;  /**< [  6:  6](RAZ) TLB lock fault. For CNXXXX always zero, no TLB locks. */
        uint32_t asf                   : 1;  /**< [  7:  7](R/W1C/H) Incorrect address size fault. */
        uint32_t uut                   : 1;  /**< [  8:  8](RAZ) Unsupported upstream transaction fault. */
        uint32_t fmt                   : 2;  /**< [ 10:  9](RO) Translation scheme.
                                                                 0x0 = AArch32 short-descriptor translation scheme.
                                                                 0x1 = AArch32 long-descriptor translation scheme.
                                                                 0x2 = AArch64 translation scheme.
                                                                 0x3 = Reserved.

                                                                 For CNXXXX always AArch64. */
        uint32_t reserved_11_29        : 19;
        uint32_t ss                    : 1;  /**< [ 30: 30](RO) Stalled status.
                                                                 0 = SMMU not stalled due to a fault in this bank.
                                                                 1 = SMMU stalled due to a fault in this bank.

                                                                 For CNXXXX always zero, no stalls. */
        uint32_t multi                 : 1;  /**< [ 31: 31](R/W1C/H) Multiple error conditions.
                                                                 0 = No multiple error condition was encountered.
                                                                 1 = An error occurred while the value in SMMU()_(S)GFSR was nonzero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_fsr_s cn; */
};
typedef union bdk_smmux_cbx_fsr bdk_smmux_cbx_fsr_t;

static inline uint64_t BDK_SMMUX_CBX_FSR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_FSR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000058ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000058ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000058ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_FSR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_FSR(a,b) bdk_smmux_cbx_fsr_t
#define bustype_BDK_SMMUX_CBX_FSR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_FSR(a,b) "SMMUX_CBX_FSR"
#define device_bar_BDK_SMMUX_CBX_FSR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_FSR(a,b) (a)
#define arguments_BDK_SMMUX_CBX_FSR(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_fsrrestore
 *
 * SMMU Context Translation Fault Restore Register
 * Restores the SMMU()_CB()_FSR register after reset. This register is used by both
 * stage 1 and stage 2 context banks.
 */
union bdk_smmux_cbx_fsrrestore
{
    uint32_t u;
    struct bdk_smmux_cbx_fsrrestore_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t restore               : 32; /**< [ 31:  0](WO) Writes bits in corresponding SMMU()_CB()_FSR. */
#else /* Word 0 - Little Endian */
        uint32_t restore               : 32; /**< [ 31:  0](WO) Writes bits in corresponding SMMU()_CB()_FSR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_fsrrestore_s cn; */
};
typedef union bdk_smmux_cbx_fsrrestore bdk_smmux_cbx_fsrrestore_t;

static inline uint64_t BDK_SMMUX_CBX_FSRRESTORE(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_FSRRESTORE(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x83000100005cll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x83000100005cll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x83000100005cll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_FSRRESTORE", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_FSRRESTORE(a,b) bdk_smmux_cbx_fsrrestore_t
#define bustype_BDK_SMMUX_CBX_FSRRESTORE(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_FSRRESTORE(a,b) "SMMUX_CBX_FSRRESTORE"
#define device_bar_BDK_SMMUX_CBX_FSRRESTORE(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_FSRRESTORE(a,b) (a)
#define arguments_BDK_SMMUX_CBX_FSRRESTORE(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_fsynr0
 *
 * SMMU Context Fault Syndrome Register 0
 */
union bdk_smmux_cbx_fsynr0
{
    uint32_t u;
    struct bdk_smmux_cbx_fsynr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t s1cbndx               : 8;  /**< [ 23: 16](R/W/H) Stage 1 context bank index associated with the transaction that caused the fault. For
                                                                 nested translation, this field contains the stage 1 translation context bank index for
                                                                 processing the transaction. For stage 2 only translation, this field is UNKNOWN.
                                                                 This field is only present in a stage 2 format translation context bank. In a stage 1
                                                                 format translation context bank, it is UNKNOWN. */
        uint32_t reserved_12_15        : 4;
        uint32_t afr                   : 1;  /**< [ 11: 11](R/W/H) Asynchronous fault recorded.
                                                                 0 = A fault was recorded synchronously.
                                                                 1 = A fault was recorded asynchronously. */
        uint32_t ptwf                  : 1;  /**< [ 10: 10](R/W/H) A walk fault on a translation table access.
                                                                 0 = A walk fault did not occur.
                                                                 1 = A walk fault occurred during processing of a translation table walk. */
        uint32_t atof                  : 1;  /**< [  9:  9](RO) Stage 2 address translation operation fault. ATOs not supported. */
        uint32_t nsattr                : 1;  /**< [  8:  8](R/W/H) Nonsecure attribute.
                                                                 0 = The input transaction after SMMU()_S2CR()[NSCFG] had secure attribute.
                                                                 1 = The input transaction after SMMU()_S2CR()[NSCFG] had nonsecure attribute. */
        uint32_t nsstate               : 1;  /**< [  7:  7](RO) Stage 2 nonsecure state:
                                                                 0 = The transaction is associated with a secure client.
                                                                 1 = The transaction is associated with a nonsecure client. */
        uint32_t ind                   : 1;  /**< [  6:  6](R/W/H) Instruction, not data.
                                                                 0 = Data.
                                                                 1 = Instruction. */
        uint32_t pnu                   : 1;  /**< [  5:  5](R/W/H) Privileged, not unprivileged.
                                                                 0 = Unprivileged.
                                                                 1 = Privileged. */
        uint32_t wnr                   : 1;  /**< [  4:  4](R/W/H) Write, not read. */
        uint32_t s1ptwf                : 1;  /**< [  3:  3](R/W/H) Stage 2 walk fault during stage 2 translation of a stage 1 translation table walk. */
        uint32_t nested                : 1;  /**< [  2:  2](R/W/H) Indicates whether the fault is due to a nested stage 1 translation.
                                                                 0 = The fault is related to a stage 2 only translation.
                                                                 1 = The fault is related to a nested stage1 and stage 2 translation.

                                                                 When NESTED is set to zero:
                                                                 * SMMU()_CB()_FAR records the IPA that faulted at stage 2
                                                                 * SMMU()_CB()_FSYNR0[S1CBNDX] is UNKNOWN.
                                                                 * SMMU()_CB()_IPAFAR also records the IPA that faulted at stage 2

                                                                 When NESTED is set to one:
                                                                 * SMMU()_CB()_FAR records the virtual address of the requested translation.
                                                                 * SMMU()_CB()_FSYNR0[S1CBNDX] indicates the stage 1 context bank that caused the
                                                                 translation.
                                                                 * SMMU()_CB()_IPAFAR records the IPA that faulted at stage 2.
                                                                 This bit is RAZ/WI if SMMU()_IDR0[NTS] == 0. */
        uint32_t plvl                  : 2;  /**< [  1:  0](R/W/H) Translation table level for fault.
                                                                 0x0 = Reserved.
                                                                 0x1 = Level 1.
                                                                 0x2 = Level 2.
                                                                 0x3 = Level 3. */
#else /* Word 0 - Little Endian */
        uint32_t plvl                  : 2;  /**< [  1:  0](R/W/H) Translation table level for fault.
                                                                 0x0 = Reserved.
                                                                 0x1 = Level 1.
                                                                 0x2 = Level 2.
                                                                 0x3 = Level 3. */
        uint32_t nested                : 1;  /**< [  2:  2](R/W/H) Indicates whether the fault is due to a nested stage 1 translation.
                                                                 0 = The fault is related to a stage 2 only translation.
                                                                 1 = The fault is related to a nested stage1 and stage 2 translation.

                                                                 When NESTED is set to zero:
                                                                 * SMMU()_CB()_FAR records the IPA that faulted at stage 2
                                                                 * SMMU()_CB()_FSYNR0[S1CBNDX] is UNKNOWN.
                                                                 * SMMU()_CB()_IPAFAR also records the IPA that faulted at stage 2

                                                                 When NESTED is set to one:
                                                                 * SMMU()_CB()_FAR records the virtual address of the requested translation.
                                                                 * SMMU()_CB()_FSYNR0[S1CBNDX] indicates the stage 1 context bank that caused the
                                                                 translation.
                                                                 * SMMU()_CB()_IPAFAR records the IPA that faulted at stage 2.
                                                                 This bit is RAZ/WI if SMMU()_IDR0[NTS] == 0. */
        uint32_t s1ptwf                : 1;  /**< [  3:  3](R/W/H) Stage 2 walk fault during stage 2 translation of a stage 1 translation table walk. */
        uint32_t wnr                   : 1;  /**< [  4:  4](R/W/H) Write, not read. */
        uint32_t pnu                   : 1;  /**< [  5:  5](R/W/H) Privileged, not unprivileged.
                                                                 0 = Unprivileged.
                                                                 1 = Privileged. */
        uint32_t ind                   : 1;  /**< [  6:  6](R/W/H) Instruction, not data.
                                                                 0 = Data.
                                                                 1 = Instruction. */
        uint32_t nsstate               : 1;  /**< [  7:  7](RO) Stage 2 nonsecure state:
                                                                 0 = The transaction is associated with a secure client.
                                                                 1 = The transaction is associated with a nonsecure client. */
        uint32_t nsattr                : 1;  /**< [  8:  8](R/W/H) Nonsecure attribute.
                                                                 0 = The input transaction after SMMU()_S2CR()[NSCFG] had secure attribute.
                                                                 1 = The input transaction after SMMU()_S2CR()[NSCFG] had nonsecure attribute. */
        uint32_t atof                  : 1;  /**< [  9:  9](RO) Stage 2 address translation operation fault. ATOs not supported. */
        uint32_t ptwf                  : 1;  /**< [ 10: 10](R/W/H) A walk fault on a translation table access.
                                                                 0 = A walk fault did not occur.
                                                                 1 = A walk fault occurred during processing of a translation table walk. */
        uint32_t afr                   : 1;  /**< [ 11: 11](R/W/H) Asynchronous fault recorded.
                                                                 0 = A fault was recorded synchronously.
                                                                 1 = A fault was recorded asynchronously. */
        uint32_t reserved_12_15        : 4;
        uint32_t s1cbndx               : 8;  /**< [ 23: 16](R/W/H) Stage 1 context bank index associated with the transaction that caused the fault. For
                                                                 nested translation, this field contains the stage 1 translation context bank index for
                                                                 processing the transaction. For stage 2 only translation, this field is UNKNOWN.
                                                                 This field is only present in a stage 2 format translation context bank. In a stage 1
                                                                 format translation context bank, it is UNKNOWN. */
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_fsynr0_s cn; */
};
typedef union bdk_smmux_cbx_fsynr0 bdk_smmux_cbx_fsynr0_t;

static inline uint64_t BDK_SMMUX_CBX_FSYNR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_FSYNR0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000068ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000068ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000068ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_FSYNR0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_FSYNR0(a,b) bdk_smmux_cbx_fsynr0_t
#define bustype_BDK_SMMUX_CBX_FSYNR0(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_FSYNR0(a,b) "SMMUX_CBX_FSYNR0"
#define device_bar_BDK_SMMUX_CBX_FSYNR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_FSYNR0(a,b) (a)
#define arguments_BDK_SMMUX_CBX_FSYNR0(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_fsynr1
 *
 * SMMU Context Fault Syndrome Register 1
 * Not implemented in CNXXXX.
 */
union bdk_smmux_cbx_fsynr1
{
    uint32_t u;
    struct bdk_smmux_cbx_fsynr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_fsynr1_s cn; */
};
typedef union bdk_smmux_cbx_fsynr1 bdk_smmux_cbx_fsynr1_t;

static inline uint64_t BDK_SMMUX_CBX_FSYNR1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_FSYNR1(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x83000100006cll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x83000100006cll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x83000100006cll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_FSYNR1", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_FSYNR1(a,b) bdk_smmux_cbx_fsynr1_t
#define bustype_BDK_SMMUX_CBX_FSYNR1(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_FSYNR1(a,b) "SMMUX_CBX_FSYNR1"
#define device_bar_BDK_SMMUX_CBX_FSYNR1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_FSYNR1(a,b) (a)
#define arguments_BDK_SMMUX_CBX_FSYNR1(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_ipafar
 *
 * SMMU Context IPA Fault Address Register
 * IPA for a nested translation that faults in stage 2 (analogous to HPFAR in the processor).
 *
 * Unlike SMMU()_CB()_FAR this register will zero extend 32-bit writes to the upper 32-bits.
 */
union bdk_smmux_cbx_ipafar
{
    uint64_t u;
    struct bdk_smmux_cbx_ipafar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t faddr                 : 37; /**< [ 48: 12](R/W/H) Fault address, the input IOVA of the faulting access. This register might be updated as
                                                                 the result of a translation fault for an upstream client device. The least significant 12
                                                                 bits of this register are shared with SMMU()_CB()_FAR. */
        uint64_t reserved_0_11         : 12;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_11         : 12;
        uint64_t faddr                 : 37; /**< [ 48: 12](R/W/H) Fault address, the input IOVA of the faulting access. This register might be updated as
                                                                 the result of a translation fault for an upstream client device. The least significant 12
                                                                 bits of this register are shared with SMMU()_CB()_FAR. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_ipafar_s cn; */
};
typedef union bdk_smmux_cbx_ipafar bdk_smmux_cbx_ipafar_t;

static inline uint64_t BDK_SMMUX_CBX_IPAFAR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_IPAFAR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000070ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000070ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000070ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_IPAFAR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_IPAFAR(a,b) bdk_smmux_cbx_ipafar_t
#define bustype_BDK_SMMUX_CBX_IPAFAR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_IPAFAR(a,b) "SMMUX_CBX_IPAFAR"
#define device_bar_BDK_SMMUX_CBX_IPAFAR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_IPAFAR(a,b) (a)
#define arguments_BDK_SMMUX_CBX_IPAFAR(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_mair0
 *
 * SMMU Context Memory Attribute Indirection Register 0
 * Provides a revised version of the TEX-Remap system to redirect the selection of memory
 * attributes from the translation table entries.
 * This register is used by stage 1 context banks.
 */
union bdk_smmux_cbx_mair0
{
    uint32_t u;
    struct bdk_smmux_cbx_mair0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t attr3                 : 8;  /**< [ 31: 24](R/W) Memory attributes. */
        uint32_t attr2                 : 8;  /**< [ 23: 16](R/W) Memory attributes. */
        uint32_t attr1                 : 8;  /**< [ 15:  8](R/W) Memory attributes. */
        uint32_t attr0                 : 8;  /**< [  7:  0](R/W) Memory attributes. */
#else /* Word 0 - Little Endian */
        uint32_t attr0                 : 8;  /**< [  7:  0](R/W) Memory attributes. */
        uint32_t attr1                 : 8;  /**< [ 15:  8](R/W) Memory attributes. */
        uint32_t attr2                 : 8;  /**< [ 23: 16](R/W) Memory attributes. */
        uint32_t attr3                 : 8;  /**< [ 31: 24](R/W) Memory attributes. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_mair0_s cn; */
};
typedef union bdk_smmux_cbx_mair0 bdk_smmux_cbx_mair0_t;

static inline uint64_t BDK_SMMUX_CBX_MAIR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_MAIR0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000038ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000038ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000038ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_MAIR0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_MAIR0(a,b) bdk_smmux_cbx_mair0_t
#define bustype_BDK_SMMUX_CBX_MAIR0(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_MAIR0(a,b) "SMMUX_CBX_MAIR0"
#define device_bar_BDK_SMMUX_CBX_MAIR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_MAIR0(a,b) (a)
#define arguments_BDK_SMMUX_CBX_MAIR0(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_mair1
 *
 * SMMU Context Memory Attribute Indirection Register 1
 * Provides a revised version of the TEX-Remap system to redirect the selection of memory
 * attributes from the translation table entries.
 * This register is used by stage 1 context banks.
 */
union bdk_smmux_cbx_mair1
{
    uint32_t u;
    struct bdk_smmux_cbx_mair1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t attr7                 : 8;  /**< [ 31: 24](R/W) Memory attributes. */
        uint32_t attr6                 : 8;  /**< [ 23: 16](R/W) Memory attributes. */
        uint32_t attr5                 : 8;  /**< [ 15:  8](R/W) Memory attributes. */
        uint32_t attr4                 : 8;  /**< [  7:  0](R/W) Memory attributes. */
#else /* Word 0 - Little Endian */
        uint32_t attr4                 : 8;  /**< [  7:  0](R/W) Memory attributes. */
        uint32_t attr5                 : 8;  /**< [ 15:  8](R/W) Memory attributes. */
        uint32_t attr6                 : 8;  /**< [ 23: 16](R/W) Memory attributes. */
        uint32_t attr7                 : 8;  /**< [ 31: 24](R/W) Memory attributes. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_mair1_s cn; */
};
typedef union bdk_smmux_cbx_mair1 bdk_smmux_cbx_mair1_t;

static inline uint64_t BDK_SMMUX_CBX_MAIR1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_MAIR1(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x83000100003cll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x83000100003cll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x83000100003cll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_MAIR1", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_MAIR1(a,b) bdk_smmux_cbx_mair1_t
#define bustype_BDK_SMMUX_CBX_MAIR1(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_MAIR1(a,b) "SMMUX_CBX_MAIR1"
#define device_bar_BDK_SMMUX_CBX_MAIR1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_MAIR1(a,b) (a)
#define arguments_BDK_SMMUX_CBX_MAIR1(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_resume
 *
 * SMMU Context Resume Register 1
 * Not implemented in CNXXXX.
 */
union bdk_smmux_cbx_resume
{
    uint32_t u;
    struct bdk_smmux_cbx_resume_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_resume_s cn; */
};
typedef union bdk_smmux_cbx_resume bdk_smmux_cbx_resume_t;

static inline uint64_t BDK_SMMUX_CBX_RESUME(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_RESUME(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000008ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000008ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000008ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_RESUME", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_RESUME(a,b) bdk_smmux_cbx_resume_t
#define bustype_BDK_SMMUX_CBX_RESUME(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_RESUME(a,b) "SMMUX_CBX_RESUME"
#define device_bar_BDK_SMMUX_CBX_RESUME(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_RESUME(a,b) (a)
#define arguments_BDK_SMMUX_CBX_RESUME(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_sctlr
 *
 * SMMU Context System Control Register
 * Provides top-level control of the translation system for the related translation context bank.
 * This register is used by both stage 1 and stage 2 context banks.
 */
union bdk_smmux_cbx_sctlr
{
    uint32_t u;
    struct bdk_smmux_cbx_sctlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t uci                   : 1;  /**< [ 30: 30](R/W) For stage 1, user cache maintenance operation enable.
                                                                 0 = User level cache maintenance operations are disabled.
                                                                 1 = User level cache maintenance operations are enabled.

                                                                 This field is ignored when SMMU()_CBA2R()[VA64] is zero.

                                                                 For stage 2, reserved. */
        uint32_t nscfg                 : 2;  /**< [ 29: 28](R/W) For stage 1, nonsecure configuration. Controls the nonsecure attribute for any
                                                                 transaction where the translation context bank translation is disabled. That is, where
                                                                 SMMU()_CB()_SCTLR[M]==0. [NSCFG] only exists in a translation context bank
                                                                 reserved by secure software. In a nonsecure translation context bank, this field is
                                                                 UNK/SBZP.
                                                                 0x0 = Use default NS attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Secure.
                                                                 0x3 = Nonsecure.

                                                                 For stage 2, reserved. */
        uint32_t wacfg                 : 2;  /**< [ 27: 26](RO) Write-allocate configuration. Controls the allocation hint for write accesses where the
                                                                 translation context bank translation is disabled. That is, where
                                                                 SMMU()_CB()_SCTLR[M]==0.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Write-allocate.
                                                                 0x3 = No write-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t racfg                 : 2;  /**< [ 25: 24](RO) Read-allocate configuration. Controls the allocation hint for read accesses where the
                                                                 translation context bank translation is disabled. That is, where
                                                                 SMMU()_CB()_SCTLR[M]==0.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Read-allocate.
                                                                 0x3 = No read-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t shcfg                 : 2;  /**< [ 23: 22](RO) Shared configuration. Controls the sharable attribute of a transaction where the
                                                                 translation context bank is disabled.
                                                                 0x0 = Default shareable attributes.
                                                                 0x1 = Outer sharable.
                                                                 0x2 = Inner sharable.
                                                                 0x3 = Non-sharable.

                                                                 Ignored in CNXXXX. */
        uint32_t fb                    : 1;  /**< [ 21: 21](RAZ) For stage 1, force broadcast. Forces the broadcast of TLB maintenance operations. Ignored
                                                                 in CNXXXX, as NCB clients do not initiate invalidates.

                                                                 For stage 2, reserved. */
        uint32_t mtcfg                 : 1;  /**< [ 20: 20](R/W) For stage 1, memory type configuration. Applies to transactions when the translation
                                                                 context bank is disabled.
                                                                 0 = Use the default memory attributes.
                                                                 1 = Use the MEMATTR field for memory attributes.

                                                                 For stage 2, reserved. */
        uint32_t memattr               : 4;  /**< [ 19: 16](R/W) Memory attributes for bypass transactions if MTCFG == 1. */
        uint32_t transcfg_bsu          : 2;  /**< [ 15: 14](RO) For stage 1, transient allocate configuration. Not implemented in CNXXXX.

                                                                 For stage 2, barrier sharability upgrade. Not implemented in CNXXXX. */
        uint32_t ptw                   : 1;  /**< [ 13: 13](R/W) For stage 1, reserved.

                                                                 For stage 2, protected translation walk for stage 1 followed by stage 2 translations:
                                                                 0 = This behavior is not enabled.
                                                                 1 = Raise a stage 2 permission fault if a stage 1 translation walk is to an area of memory
                                                                 that has the device or strongly-ordered memory attribute in the stage 2 translation
                                                                 tables. */
        uint32_t asidpne               : 1;  /**< [ 12: 12](RO) For stage 1, address space identifier private namespace enable hint.
                                                                 0 = SMMU ASID values for this translation context bank are coordinated with wider
                                                                 system.
                                                                 1 = SMMU ASID values for this translation context bank are a private namespace not
                                                                 coordinated with the wider system.

                                                                 Hint ignored in CNXXXX, always system wide.

                                                                 For stage 2, reserved. */
        uint32_t reserved_11           : 1;
        uint32_t uwxn                  : 1;  /**< [ 10: 10](RO) For stage 1, unprivileged writable execute never.
                                                                 0 = This behavior is not enabled.
                                                                 1 = Raise a stage 1 permission fault if an instruction fetch occurs from a memory location
                                                                 that permits writes for unprivileged access.

                                                                 For stage 2, reserved.

                                                                 CNXXXX not implemented, no instruction stream. */
        uint32_t wxn                   : 1;  /**< [  9:  9](RO) For stage 1, writable execute never.
                                                                 0 = This behavior is not enabled.
                                                                 1 = Raise a stage 1 permission fault if an instruction fetch occurs from a memory location
                                                                 that permits writes.

                                                                 For stage 2, reserved.

                                                                 CNXXXX not implemented, no instruction stream. */
        uint32_t hupcf                 : 1;  /**< [  8:  8](RO) Hit under previous context fault.
                                                                 0 = Stall or terminate subsequent transactions in the presence of an outstanding context
                                                                 fault.
                                                                 1 = Process all subsequent transactions independently of any outstanding context fault.

                                                                 CNXXXX ignores, always processes. */
        uint32_t cfcfg                 : 1;  /**< [  7:  7](RO) Context fault configuration.
                                                                 0 = Terminate.
                                                                 1 = Stall.

                                                                 CNXXXX ignores, always terminates. */
        uint32_t cfie                  : 1;  /**< [  6:  6](R/W) Context fault interrupt enable.
                                                                 0 = Do not raise an interrupt when a context fault occurs.
                                                                 1 = Raise an interrupt when a context fault occurs. */
        uint32_t cfre                  : 1;  /**< [  5:  5](R/W) Context fault report enable.
                                                                 0 = Do not return an abort when a context fault occurs.
                                                                 1 = Return an abort when a context fault occurs. */
        uint32_t ebig                  : 1;  /**< [  4:  4](R/W) Endianness, indicates the endian format of translation tables.
                                                                 0 = Little endian.
                                                                 1 = Big endian. */
        uint32_t affd                  : 1;  /**< [  3:  3](R/W) Access flag fault disable.
                                                                 0 = Access flag faults are enabled.
                                                                 1 = Access flag faults are disabled.

                                                                 It is expected that software will issue TLB maintenance operations if this bit is
                                                                 modified. If page tables are shared with the processor, then any descriptor with AF zero
                                                                 will not be held in a processor TLB entry. However, such descriptors might be held in SMMU
                                                                 TLBs. This means that page table maintenance software that changes descriptors must be
                                                                 aware that the old descriptor might be cached in the SMMU. */
        uint32_t afe                   : 1;  /**< [  2:  2](RO) Access flag enable. In ARMv8 this bit has no effect and the SMMU behaves as if the
                                                                 bit were set. Software should treat this bit as UNK/SBOP. */
        uint32_t tre                   : 1;  /**< [  1:  1](RO) TEX remap enable. In ARMv8 this bit has no effect. */
        uint32_t m                     : 1;  /**< [  0:  0](R/W) MMU enable.
                                                                 0 = MMU behavior for this translation context bank is disabled.
                                                                 1 = MMU behavior for this translation context bank is enabled. */
#else /* Word 0 - Little Endian */
        uint32_t m                     : 1;  /**< [  0:  0](R/W) MMU enable.
                                                                 0 = MMU behavior for this translation context bank is disabled.
                                                                 1 = MMU behavior for this translation context bank is enabled. */
        uint32_t tre                   : 1;  /**< [  1:  1](RO) TEX remap enable. In ARMv8 this bit has no effect. */
        uint32_t afe                   : 1;  /**< [  2:  2](RO) Access flag enable. In ARMv8 this bit has no effect and the SMMU behaves as if the
                                                                 bit were set. Software should treat this bit as UNK/SBOP. */
        uint32_t affd                  : 1;  /**< [  3:  3](R/W) Access flag fault disable.
                                                                 0 = Access flag faults are enabled.
                                                                 1 = Access flag faults are disabled.

                                                                 It is expected that software will issue TLB maintenance operations if this bit is
                                                                 modified. If page tables are shared with the processor, then any descriptor with AF zero
                                                                 will not be held in a processor TLB entry. However, such descriptors might be held in SMMU
                                                                 TLBs. This means that page table maintenance software that changes descriptors must be
                                                                 aware that the old descriptor might be cached in the SMMU. */
        uint32_t ebig                  : 1;  /**< [  4:  4](R/W) Endianness, indicates the endian format of translation tables.
                                                                 0 = Little endian.
                                                                 1 = Big endian. */
        uint32_t cfre                  : 1;  /**< [  5:  5](R/W) Context fault report enable.
                                                                 0 = Do not return an abort when a context fault occurs.
                                                                 1 = Return an abort when a context fault occurs. */
        uint32_t cfie                  : 1;  /**< [  6:  6](R/W) Context fault interrupt enable.
                                                                 0 = Do not raise an interrupt when a context fault occurs.
                                                                 1 = Raise an interrupt when a context fault occurs. */
        uint32_t cfcfg                 : 1;  /**< [  7:  7](RO) Context fault configuration.
                                                                 0 = Terminate.
                                                                 1 = Stall.

                                                                 CNXXXX ignores, always terminates. */
        uint32_t hupcf                 : 1;  /**< [  8:  8](RO) Hit under previous context fault.
                                                                 0 = Stall or terminate subsequent transactions in the presence of an outstanding context
                                                                 fault.
                                                                 1 = Process all subsequent transactions independently of any outstanding context fault.

                                                                 CNXXXX ignores, always processes. */
        uint32_t wxn                   : 1;  /**< [  9:  9](RO) For stage 1, writable execute never.
                                                                 0 = This behavior is not enabled.
                                                                 1 = Raise a stage 1 permission fault if an instruction fetch occurs from a memory location
                                                                 that permits writes.

                                                                 For stage 2, reserved.

                                                                 CNXXXX not implemented, no instruction stream. */
        uint32_t uwxn                  : 1;  /**< [ 10: 10](RO) For stage 1, unprivileged writable execute never.
                                                                 0 = This behavior is not enabled.
                                                                 1 = Raise a stage 1 permission fault if an instruction fetch occurs from a memory location
                                                                 that permits writes for unprivileged access.

                                                                 For stage 2, reserved.

                                                                 CNXXXX not implemented, no instruction stream. */
        uint32_t reserved_11           : 1;
        uint32_t asidpne               : 1;  /**< [ 12: 12](RO) For stage 1, address space identifier private namespace enable hint.
                                                                 0 = SMMU ASID values for this translation context bank are coordinated with wider
                                                                 system.
                                                                 1 = SMMU ASID values for this translation context bank are a private namespace not
                                                                 coordinated with the wider system.

                                                                 Hint ignored in CNXXXX, always system wide.

                                                                 For stage 2, reserved. */
        uint32_t ptw                   : 1;  /**< [ 13: 13](R/W) For stage 1, reserved.

                                                                 For stage 2, protected translation walk for stage 1 followed by stage 2 translations:
                                                                 0 = This behavior is not enabled.
                                                                 1 = Raise a stage 2 permission fault if a stage 1 translation walk is to an area of memory
                                                                 that has the device or strongly-ordered memory attribute in the stage 2 translation
                                                                 tables. */
        uint32_t transcfg_bsu          : 2;  /**< [ 15: 14](RO) For stage 1, transient allocate configuration. Not implemented in CNXXXX.

                                                                 For stage 2, barrier sharability upgrade. Not implemented in CNXXXX. */
        uint32_t memattr               : 4;  /**< [ 19: 16](R/W) Memory attributes for bypass transactions if MTCFG == 1. */
        uint32_t mtcfg                 : 1;  /**< [ 20: 20](R/W) For stage 1, memory type configuration. Applies to transactions when the translation
                                                                 context bank is disabled.
                                                                 0 = Use the default memory attributes.
                                                                 1 = Use the MEMATTR field for memory attributes.

                                                                 For stage 2, reserved. */
        uint32_t fb                    : 1;  /**< [ 21: 21](RAZ) For stage 1, force broadcast. Forces the broadcast of TLB maintenance operations. Ignored
                                                                 in CNXXXX, as NCB clients do not initiate invalidates.

                                                                 For stage 2, reserved. */
        uint32_t shcfg                 : 2;  /**< [ 23: 22](RO) Shared configuration. Controls the sharable attribute of a transaction where the
                                                                 translation context bank is disabled.
                                                                 0x0 = Default shareable attributes.
                                                                 0x1 = Outer sharable.
                                                                 0x2 = Inner sharable.
                                                                 0x3 = Non-sharable.

                                                                 Ignored in CNXXXX. */
        uint32_t racfg                 : 2;  /**< [ 25: 24](RO) Read-allocate configuration. Controls the allocation hint for read accesses where the
                                                                 translation context bank translation is disabled. That is, where
                                                                 SMMU()_CB()_SCTLR[M]==0.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Read-allocate.
                                                                 0x3 = No read-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t wacfg                 : 2;  /**< [ 27: 26](RO) Write-allocate configuration. Controls the allocation hint for write accesses where the
                                                                 translation context bank translation is disabled. That is, where
                                                                 SMMU()_CB()_SCTLR[M]==0.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Write-allocate.
                                                                 0x3 = No write-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t nscfg                 : 2;  /**< [ 29: 28](R/W) For stage 1, nonsecure configuration. Controls the nonsecure attribute for any
                                                                 transaction where the translation context bank translation is disabled. That is, where
                                                                 SMMU()_CB()_SCTLR[M]==0. [NSCFG] only exists in a translation context bank
                                                                 reserved by secure software. In a nonsecure translation context bank, this field is
                                                                 UNK/SBZP.
                                                                 0x0 = Use default NS attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Secure.
                                                                 0x3 = Nonsecure.

                                                                 For stage 2, reserved. */
        uint32_t uci                   : 1;  /**< [ 30: 30](R/W) For stage 1, user cache maintenance operation enable.
                                                                 0 = User level cache maintenance operations are disabled.
                                                                 1 = User level cache maintenance operations are enabled.

                                                                 This field is ignored when SMMU()_CBA2R()[VA64] is zero.

                                                                 For stage 2, reserved. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_sctlr_s cn; */
};
typedef union bdk_smmux_cbx_sctlr bdk_smmux_cbx_sctlr_t;

static inline uint64_t BDK_SMMUX_CBX_SCTLR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_SCTLR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000000ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000000ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000000ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_SCTLR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_SCTLR(a,b) bdk_smmux_cbx_sctlr_t
#define bustype_BDK_SMMUX_CBX_SCTLR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_SCTLR(a,b) "SMMUX_CBX_SCTLR"
#define device_bar_BDK_SMMUX_CBX_SCTLR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_SCTLR(a,b) (a)
#define arguments_BDK_SMMUX_CBX_SCTLR(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_tcr
 *
 * SMMU Context Translation Control Register
 */
union bdk_smmux_cbx_tcr
{
    uint32_t u;
    struct bdk_smmux_cbx_tcr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t tg1                   : 2;  /**< [ 31: 30](R/W) For stage 1, page size granule for TTBR1.
                                                                 0x0 = Reserved.
                                                                 0x1 = 16 KB page granule.
                                                                 0x2 = 4 KB page granule.
                                                                 0x3 = 64 KB page granule.

                                                                 Note the encoding is different from the [TG0] encoding.
                                                                 For stage 2, reserved. */
        uint32_t sh1                   : 2;  /**< [ 29: 28](R/W) For stage 1, sharability attributes for the memory associated with the translation table
                                                                 walks using TTBR1.

                                                                 For stage 2, reserved. */
        uint32_t orgn1                 : 2;  /**< [ 27: 26](R/W) For stage 1, outer cachability attributes for TTBR1 table walks.

                                                                 For stage 2, reserved. */
        uint32_t irgn1                 : 2;  /**< [ 25: 24](R/W) For stage 1, inner cachability attributes for TTBR1 table walks.

                                                                 For stage 2, reserved. */
        uint32_t epd1                  : 1;  /**< [ 23: 23](R/W) For stage 1, translation walk disable for TTBR1 region. This bit controls whether a
                                                                 translation table walk is performed on a TLB miss when SMMU()_CB()_TTBR1 is
                                                                 used:
                                                                 0 = If a TLB miss occurs when TTBR1 is used a translation table walk is performed.
                                                                 1 = If a TLB miss occurs when TTBR1 is used no translation table walk is performed and a
                                                                 L1 Translation fault is returned.

                                                                 For stage 2, reserved. */
        uint32_t a1                    : 1;  /**< [ 22: 22](R/W) For stage 1, select ASID from TTBRn register.
                                                                 0 = Select ASID from SMMU()_CB()_TTBR0.
                                                                 1 = Select ASID from SMMU()_CB()_TTBR1.

                                                                 For stage 2, reserved. */
        uint32_t t1sz_pasize           : 6;  /**< [ 21: 16](R/W) For stage 1, \<21:16\> is size offset of the SMMU()_CB()_TCR addressed region,
                                                                 encoded as a six-bit unsigned number, giving the size of the region as 2^(64-T1SZ).

                                                                 For stage 2, \<21:19\> is reserved, \<18:16\> is PASize, the size of the physical address
                                                                 (i.e. the output address):
                                                                 0x0 = 32 bits (4 GBytes).
                                                                 0x1 = 36 bits (64 GBytes).
                                                                 0x2 = 40 bits (1 TByte).
                                                                 0x3 = 42 bits (4 TByte).
                                                                 0x4 = 44 bits (16 TByte).
                                                                 0x5 = 48 bits (256 TByte).
                                                                 0x6-0x7 = Reserved. Treat as 48 bits. */
        uint32_t tg0                   : 2;  /**< [ 15: 14](R/W) Page size granule for TTBR0.
                                                                 0x0 = 4 KB page granule.
                                                                 0x1 = 64 KB page granule.
                                                                 0x2 = 16 KB page granule.
                                                                 0x3 = Reserved.

                                                                 Note the encoding is different from the [TG1] encoding. */
        uint32_t sh0                   : 2;  /**< [ 13: 12](R/W) Sharability attributes for the memory associated with the translation table walks using TTBR0. */
        uint32_t orgn0                 : 2;  /**< [ 11: 10](RO) Outer cachability attributes for TTBR0 table walks.
                                                                 Ignored in CNXXXX. */
        uint32_t irgn0                 : 2;  /**< [  9:  8](RO) Inner cachability attributes for TTBR0 table walks.
                                                                 Ignored in CNXXXX. */
        uint32_t epd0_sl0              : 2;  /**< [  7:  6](R/W) For stage 1, \<6\> is reserved. \<7\> is EPD0, translation walk disable for TTBR0 region. This
                                                                 bit is RES0 for hypervisor and monitor contexts. This bit controls whether a translation
                                                                 table walk is performed on a TLB miss when TTBR0 is used:
                                                                 0x0 = If aTLB miss occurs when TTBR0 is used a translation table walk is performed.
                                                                 0x1 = If a TLB miss occurs when TTBR0 is used no translation table walk is performed and a
                                                                 L1 Translation fault is returned.

                                                                 For stage 2, \<7:6\> is SL0, starting level of the addressed regions. For 4kB page granule
                                                                 size (TG0 == 0):
                                                                 0x0 = Level 2.
                                                                 0x1 = Level 1.
                                                                 0x2 = Level 0.
                                                                 0x3 = Reserved.

                                                                 For 64kB page granule size (TG0 == 1):
                                                                 0x0 = Level 3.
                                                                 0x1 = Level 2.
                                                                 0x2 = Level 1.
                                                                 0x3 = Reserved. */
        uint32_t t0sz                  : 6;  /**< [  5:  0](R/W) Size offset of the TTBR0 addressed region, encoded as a six-bit unsigned number giving the
                                                                 size of the region as 2^(64-T0SZ). */
#else /* Word 0 - Little Endian */
        uint32_t t0sz                  : 6;  /**< [  5:  0](R/W) Size offset of the TTBR0 addressed region, encoded as a six-bit unsigned number giving the
                                                                 size of the region as 2^(64-T0SZ). */
        uint32_t epd0_sl0              : 2;  /**< [  7:  6](R/W) For stage 1, \<6\> is reserved. \<7\> is EPD0, translation walk disable for TTBR0 region. This
                                                                 bit is RES0 for hypervisor and monitor contexts. This bit controls whether a translation
                                                                 table walk is performed on a TLB miss when TTBR0 is used:
                                                                 0x0 = If aTLB miss occurs when TTBR0 is used a translation table walk is performed.
                                                                 0x1 = If a TLB miss occurs when TTBR0 is used no translation table walk is performed and a
                                                                 L1 Translation fault is returned.

                                                                 For stage 2, \<7:6\> is SL0, starting level of the addressed regions. For 4kB page granule
                                                                 size (TG0 == 0):
                                                                 0x0 = Level 2.
                                                                 0x1 = Level 1.
                                                                 0x2 = Level 0.
                                                                 0x3 = Reserved.

                                                                 For 64kB page granule size (TG0 == 1):
                                                                 0x0 = Level 3.
                                                                 0x1 = Level 2.
                                                                 0x2 = Level 1.
                                                                 0x3 = Reserved. */
        uint32_t irgn0                 : 2;  /**< [  9:  8](RO) Inner cachability attributes for TTBR0 table walks.
                                                                 Ignored in CNXXXX. */
        uint32_t orgn0                 : 2;  /**< [ 11: 10](RO) Outer cachability attributes for TTBR0 table walks.
                                                                 Ignored in CNXXXX. */
        uint32_t sh0                   : 2;  /**< [ 13: 12](R/W) Sharability attributes for the memory associated with the translation table walks using TTBR0. */
        uint32_t tg0                   : 2;  /**< [ 15: 14](R/W) Page size granule for TTBR0.
                                                                 0x0 = 4 KB page granule.
                                                                 0x1 = 64 KB page granule.
                                                                 0x2 = 16 KB page granule.
                                                                 0x3 = Reserved.

                                                                 Note the encoding is different from the [TG1] encoding. */
        uint32_t t1sz_pasize           : 6;  /**< [ 21: 16](R/W) For stage 1, \<21:16\> is size offset of the SMMU()_CB()_TCR addressed region,
                                                                 encoded as a six-bit unsigned number, giving the size of the region as 2^(64-T1SZ).

                                                                 For stage 2, \<21:19\> is reserved, \<18:16\> is PASize, the size of the physical address
                                                                 (i.e. the output address):
                                                                 0x0 = 32 bits (4 GBytes).
                                                                 0x1 = 36 bits (64 GBytes).
                                                                 0x2 = 40 bits (1 TByte).
                                                                 0x3 = 42 bits (4 TByte).
                                                                 0x4 = 44 bits (16 TByte).
                                                                 0x5 = 48 bits (256 TByte).
                                                                 0x6-0x7 = Reserved. Treat as 48 bits. */
        uint32_t a1                    : 1;  /**< [ 22: 22](R/W) For stage 1, select ASID from TTBRn register.
                                                                 0 = Select ASID from SMMU()_CB()_TTBR0.
                                                                 1 = Select ASID from SMMU()_CB()_TTBR1.

                                                                 For stage 2, reserved. */
        uint32_t epd1                  : 1;  /**< [ 23: 23](R/W) For stage 1, translation walk disable for TTBR1 region. This bit controls whether a
                                                                 translation table walk is performed on a TLB miss when SMMU()_CB()_TTBR1 is
                                                                 used:
                                                                 0 = If a TLB miss occurs when TTBR1 is used a translation table walk is performed.
                                                                 1 = If a TLB miss occurs when TTBR1 is used no translation table walk is performed and a
                                                                 L1 Translation fault is returned.

                                                                 For stage 2, reserved. */
        uint32_t irgn1                 : 2;  /**< [ 25: 24](R/W) For stage 1, inner cachability attributes for TTBR1 table walks.

                                                                 For stage 2, reserved. */
        uint32_t orgn1                 : 2;  /**< [ 27: 26](R/W) For stage 1, outer cachability attributes for TTBR1 table walks.

                                                                 For stage 2, reserved. */
        uint32_t sh1                   : 2;  /**< [ 29: 28](R/W) For stage 1, sharability attributes for the memory associated with the translation table
                                                                 walks using TTBR1.

                                                                 For stage 2, reserved. */
        uint32_t tg1                   : 2;  /**< [ 31: 30](R/W) For stage 1, page size granule for TTBR1.
                                                                 0x0 = Reserved.
                                                                 0x1 = 16 KB page granule.
                                                                 0x2 = 4 KB page granule.
                                                                 0x3 = 64 KB page granule.

                                                                 Note the encoding is different from the [TG0] encoding.
                                                                 For stage 2, reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tcr_s cn; */
};
typedef union bdk_smmux_cbx_tcr bdk_smmux_cbx_tcr_t;

static inline uint64_t BDK_SMMUX_CBX_TCR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TCR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000030ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000030ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000030ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TCR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TCR(a,b) bdk_smmux_cbx_tcr_t
#define bustype_BDK_SMMUX_CBX_TCR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_TCR(a,b) "SMMUX_CBX_TCR"
#define device_bar_BDK_SMMUX_CBX_TCR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TCR(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TCR(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_tcr2
 *
 * SMMU Context Translation Control 2 Register
 */
union bdk_smmux_cbx_tcr2
{
    uint32_t u;
    struct bdk_smmux_cbx_tcr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t nscfg1                : 1;  /**< [ 30: 30](R/W) Nonsecure attribute for the memory associated with translation table walks using
                                                                 SMMU()_CB()_TTBR1. This field only applies for secure owned context banks,
                                                                 otherwise this field is ignored. */
        uint32_t reserved_18_29        : 12;
        uint32_t sep                   : 3;  /**< [ 17: 15](R/W) Sign extension position. The bit position from which to sign-extend the stage 1 input
                                                                 address when required.
                                                                 0x0 = Bit [31].
                                                                 0x1 = Bit [35].
                                                                 0x2 = Bit [39].
                                                                 0x3 = Bit [41].
                                                                 0x4 = Bit [43].
                                                                 0x5 = Bit [47].
                                                                 0x6 = Reserved. This must be treated as 0x7.
                                                                 0x7 = Explicit sign bit provided by device (as bit [48]). If bit[48] is not provided it is
                                                                 treated as zero.

                                                                 If SEP specifies a bit above that implemented on the upstream input address bus, addresses
                                                                 will be zero-extended. Sign-extension does not apply to address translation operations.
                                                                 For hypervisor and monitor contexts this field is ignored.

                                                                 If the value of SEP is changed, then software must invalidate any affected TLB entries. */
        uint32_t nscfg0                : 1;  /**< [ 14: 14](R/W) Nonsecure attribute for the memory associated with translation table walks using
                                                                 SMMU()_CB()_TTBR0. This field only applies for secure owned context banks,
                                                                 otherwise this field is ignored. */
        uint32_t reserved_12_13        : 2;
        uint32_t hd                    : 1;  /**< [ 11: 11](RO) Hardware management of dirty bit.
                                                                 In CNXXXX, not implemented. */
        uint32_t ha                    : 1;  /**< [ 10: 10](RO) Hardware management of access flag.
                                                                 In CNXXXX, not implemented. */
        uint32_t had1                  : 1;  /**< [  9:  9](R/W) Hierarchical attribute disable 1 for the TTBR1 region. Similar to [HAD0]. */
        uint32_t had0                  : 1;  /**< [  8:  8](R/W) For stage 1, hierarchical attribute disable 0 for the TTBR0 region.
                                                                 This field is ignored as not supported when SMMU()_IDR2[HADS] is zero.
                                                                 This field is ignored when SMMU()_CBA2R()[VA64] is zero.
                                                                 0 = Hierarchical attributes are enabled.
                                                                 1 = Hierarchical attributes are disabled.

                                                                 For stage 2, reserved. */
        uint32_t reserved_7            : 1;
        uint32_t tbi1                  : 1;  /**< [  6:  6](R/W) Top byte ignored. Indicates whether the top byte of the input address should be used for
                                                                 address match for the TTBR1 region. */
        uint32_t tbi0                  : 1;  /**< [  5:  5](R/W) Top byte ignored. Indicates whether the top byte of the input address should be used for
                                                                 address match for the TTBR0 region. */
        uint32_t as                    : 1;  /**< [  4:  4](R/W) ASID Size.
                                                                 0 = 8 bit. Note: 8 bit ASIDs are zero extended to 16 bits for all TLB matching purposes.
                                                                 1 = 16 bit. */
        uint32_t reserved_3            : 1;
        uint32_t pasize                : 3;  /**< [  2:  0](R/W) The size of the physical address:
                                                                 0x0 = 32 bits (4 GBytes).
                                                                 0x1 = 36 bits (64 GBytes).
                                                                 0x2 = 40 bits (1 TByte).
                                                                 0x3 = 42 bits (4 TByte).
                                                                 0x4 = 44 bits (16 TByte).
                                                                 0x5 = 48 bits (256 TByte).
                                                                 0x6-0x7. Reserved. Treat as 48 bits. */
#else /* Word 0 - Little Endian */
        uint32_t pasize                : 3;  /**< [  2:  0](R/W) The size of the physical address:
                                                                 0x0 = 32 bits (4 GBytes).
                                                                 0x1 = 36 bits (64 GBytes).
                                                                 0x2 = 40 bits (1 TByte).
                                                                 0x3 = 42 bits (4 TByte).
                                                                 0x4 = 44 bits (16 TByte).
                                                                 0x5 = 48 bits (256 TByte).
                                                                 0x6-0x7. Reserved. Treat as 48 bits. */
        uint32_t reserved_3            : 1;
        uint32_t as                    : 1;  /**< [  4:  4](R/W) ASID Size.
                                                                 0 = 8 bit. Note: 8 bit ASIDs are zero extended to 16 bits for all TLB matching purposes.
                                                                 1 = 16 bit. */
        uint32_t tbi0                  : 1;  /**< [  5:  5](R/W) Top byte ignored. Indicates whether the top byte of the input address should be used for
                                                                 address match for the TTBR0 region. */
        uint32_t tbi1                  : 1;  /**< [  6:  6](R/W) Top byte ignored. Indicates whether the top byte of the input address should be used for
                                                                 address match for the TTBR1 region. */
        uint32_t reserved_7            : 1;
        uint32_t had0                  : 1;  /**< [  8:  8](R/W) For stage 1, hierarchical attribute disable 0 for the TTBR0 region.
                                                                 This field is ignored as not supported when SMMU()_IDR2[HADS] is zero.
                                                                 This field is ignored when SMMU()_CBA2R()[VA64] is zero.
                                                                 0 = Hierarchical attributes are enabled.
                                                                 1 = Hierarchical attributes are disabled.

                                                                 For stage 2, reserved. */
        uint32_t had1                  : 1;  /**< [  9:  9](R/W) Hierarchical attribute disable 1 for the TTBR1 region. Similar to [HAD0]. */
        uint32_t ha                    : 1;  /**< [ 10: 10](RO) Hardware management of access flag.
                                                                 In CNXXXX, not implemented. */
        uint32_t hd                    : 1;  /**< [ 11: 11](RO) Hardware management of dirty bit.
                                                                 In CNXXXX, not implemented. */
        uint32_t reserved_12_13        : 2;
        uint32_t nscfg0                : 1;  /**< [ 14: 14](R/W) Nonsecure attribute for the memory associated with translation table walks using
                                                                 SMMU()_CB()_TTBR0. This field only applies for secure owned context banks,
                                                                 otherwise this field is ignored. */
        uint32_t sep                   : 3;  /**< [ 17: 15](R/W) Sign extension position. The bit position from which to sign-extend the stage 1 input
                                                                 address when required.
                                                                 0x0 = Bit [31].
                                                                 0x1 = Bit [35].
                                                                 0x2 = Bit [39].
                                                                 0x3 = Bit [41].
                                                                 0x4 = Bit [43].
                                                                 0x5 = Bit [47].
                                                                 0x6 = Reserved. This must be treated as 0x7.
                                                                 0x7 = Explicit sign bit provided by device (as bit [48]). If bit[48] is not provided it is
                                                                 treated as zero.

                                                                 If SEP specifies a bit above that implemented on the upstream input address bus, addresses
                                                                 will be zero-extended. Sign-extension does not apply to address translation operations.
                                                                 For hypervisor and monitor contexts this field is ignored.

                                                                 If the value of SEP is changed, then software must invalidate any affected TLB entries. */
        uint32_t reserved_18_29        : 12;
        uint32_t nscfg1                : 1;  /**< [ 30: 30](R/W) Nonsecure attribute for the memory associated with translation table walks using
                                                                 SMMU()_CB()_TTBR1. This field only applies for secure owned context banks,
                                                                 otherwise this field is ignored. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tcr2_s cn; */
};
typedef union bdk_smmux_cbx_tcr2 bdk_smmux_cbx_tcr2_t;

static inline uint64_t BDK_SMMUX_CBX_TCR2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TCR2(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000010ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000010ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000010ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TCR2", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TCR2(a,b) bdk_smmux_cbx_tcr2_t
#define bustype_BDK_SMMUX_CBX_TCR2(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_TCR2(a,b) "SMMUX_CBX_TCR2"
#define device_bar_BDK_SMMUX_CBX_TCR2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TCR2(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TCR2(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_tlbiall
 *
 * SMMU Context Invalidate Entire TLB Register
 * Invalidates all of the TLB entries, and only has to apply to TLB entries associated with the
 * VMID used for the stage 1 translation context bank. If SMMU()_CBAR()[HYPC] has the
 * value 1, this operation only has to apply to TLB entries associated with hypervisor contexts.
 * if SMMU()_CBAR()[MONC] has the value 1, this operation only has to apply to TLB
 * entries associated with monitor contexts. The VMID is therefore irrelevant to the operation.
 * This operation only has to apply to TLB entries associated with the security domain that the
 * Stage 1 translation context bank is a member of.
 * Register fields are identical to those in SMMU()_TLBIALLH.
 */
union bdk_smmux_cbx_tlbiall
{
    uint32_t u;
    struct bdk_smmux_cbx_tlbiall_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#else /* Word 0 - Little Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbiall_s cn; */
};
typedef union bdk_smmux_cbx_tlbiall bdk_smmux_cbx_tlbiall_t;

static inline uint64_t BDK_SMMUX_CBX_TLBIALL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBIALL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000618ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000618ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000618ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBIALL", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBIALL(a,b) bdk_smmux_cbx_tlbiall_t
#define bustype_BDK_SMMUX_CBX_TLBIALL(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_TLBIALL(a,b) "SMMUX_CBX_TLBIALL"
#define device_bar_BDK_SMMUX_CBX_TLBIALL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBIALL(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBIALL(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_tlbiasid
 *
 * SMMU Context Invalid TLB by ASID Register
 * Invalidates all of the TLB entries that match the ASID provided as an argument. This operation
 * only has to apply to non-global TLB entries that match the VMID used for the stage 1
 * translation context bank. For MONC and HYPC contexts, this operation has no effect and
 * is ignored.
 * This operation only has to apply to TLB entries associated with the security domain that the
 * Stage 1 translation context bank is a member of.
 */
union bdk_smmux_cbx_tlbiasid
{
    uint32_t u;
    struct bdk_smmux_cbx_tlbiasid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t asid                  : 16; /**< [ 15:  0](WO) ASID to invalidate. */
#else /* Word 0 - Little Endian */
        uint32_t asid                  : 16; /**< [ 15:  0](WO) ASID to invalidate. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbiasid_s cn; */
};
typedef union bdk_smmux_cbx_tlbiasid bdk_smmux_cbx_tlbiasid_t;

static inline uint64_t BDK_SMMUX_CBX_TLBIASID(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBIASID(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000610ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000610ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000610ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBIASID", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBIASID(a,b) bdk_smmux_cbx_tlbiasid_t
#define bustype_BDK_SMMUX_CBX_TLBIASID(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_TLBIASID(a,b) "SMMUX_CBX_TLBIASID"
#define device_bar_BDK_SMMUX_CBX_TLBIASID(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBIASID(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBIASID(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_tlbiipas2
 *
 * SMMU Context Invalidate TLB by IPA Register
 * Invalidates all TLB entries that  match the specified IPA. this operation does not need to
 * apply to caching structures that combines both stage 1 and stage 2 translation table entries,
 * but must apply to caching structures that contain information only from stage 2 translation
 * table entries. For those implementations that choose to store the IPA in a combined stage 1
 * and stage 2 TLB entry, this operation is only required to match those entries that have the
 * same VMID as specified by the stage 2 bank.
 * An incoming transaction directed at an S2 context might result in S2-only TLB entries which
 * will be affected by this operation.
 * However, an incoming transaction directed to a S1 + S2 nested context might result in S1+S2
 * TLB entries. Such entries might not be affected by this operation. Thus in order to change a
 * Stage 2 page table entry then software must invalidate all stage 1 contexts (using an
 * SMMU()_TLBIVMIDS1 operation).
 */
union bdk_smmux_cbx_tlbiipas2
{
    uint64_t u;
    struct bdk_smmux_cbx_tlbiipas2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t address               : 36; /**< [ 35:  0](WO) IPA\<47:12\> to be invalidated. Note this matches the format of the address supplied to
                                                                 ARMv8 processor TLB invalidation instructions. If the page size for stage 2 is 64kB then
                                                                 bits corresponding to address\<15:12\> are ignored. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 36; /**< [ 35:  0](WO) IPA\<47:12\> to be invalidated. Note this matches the format of the address supplied to
                                                                 ARMv8 processor TLB invalidation instructions. If the page size for stage 2 is 64kB then
                                                                 bits corresponding to address\<15:12\> are ignored. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbiipas2_s cn; */
};
typedef union bdk_smmux_cbx_tlbiipas2 bdk_smmux_cbx_tlbiipas2_t;

static inline uint64_t BDK_SMMUX_CBX_TLBIIPAS2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBIIPAS2(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000630ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000630ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000630ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBIIPAS2", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBIIPAS2(a,b) bdk_smmux_cbx_tlbiipas2_t
#define bustype_BDK_SMMUX_CBX_TLBIIPAS2(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_TLBIIPAS2(a,b) "SMMUX_CBX_TLBIIPAS2"
#define device_bar_BDK_SMMUX_CBX_TLBIIPAS2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBIIPAS2(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBIIPAS2(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_tlbiipas2l
 *
 * SMMU Invalidate TLB by IPA Last Level Register
 * Operates exactly as SMMU()_CB()_TLBIIPAS2, but only invalidating those that
 * correspond to the last level of the translation table walk.
 */
union bdk_smmux_cbx_tlbiipas2l
{
    uint64_t u;
    struct bdk_smmux_cbx_tlbiipas2l_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t address               : 36; /**< [ 35:  0](WO) IPA\<47:12\> to be invalidated. Note this matches the format of the address supplied to
                                                                 ARMv8 processor TLB invalidation instructions. If the page size for stage 2 is 64kB then
                                                                 bits corresponding to address\<15:12\> are ignored. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 36; /**< [ 35:  0](WO) IPA\<47:12\> to be invalidated. Note this matches the format of the address supplied to
                                                                 ARMv8 processor TLB invalidation instructions. If the page size for stage 2 is 64kB then
                                                                 bits corresponding to address\<15:12\> are ignored. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbiipas2l_s cn; */
};
typedef union bdk_smmux_cbx_tlbiipas2l bdk_smmux_cbx_tlbiipas2l_t;

static inline uint64_t BDK_SMMUX_CBX_TLBIIPAS2L(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBIIPAS2L(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000638ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000638ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000638ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBIIPAS2L", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBIIPAS2L(a,b) bdk_smmux_cbx_tlbiipas2l_t
#define bustype_BDK_SMMUX_CBX_TLBIIPAS2L(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_TLBIIPAS2L(a,b) "SMMUX_CBX_TLBIIPAS2L"
#define device_bar_BDK_SMMUX_CBX_TLBIIPAS2L(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBIIPAS2L(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBIIPAS2L(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_tlbiva
 *
 * SMMU Context Invalidate TLB by VA Register
 * Invalidates all of the TLB entries that match the VA and ASID provided as arguments. This
 * operation only applies to TLB entries associated with the VMID used for a stage 1 translation
 * context bank. The ASID is not checked for global entries in the TLB. If
 * SMMU()_CBAR()[HYPC] is set, this operation only applies to TLB entries associated
 * with hypervisor contexts. The VMID and ASID are therefore irrelevant to the operation. This
 * operation only applies to TLB entries associated with the security domain that the stage 1
 * translation context bank is a member of.
 */
union bdk_smmux_cbx_tlbiva
{
    uint64_t u;
    struct bdk_smmux_cbx_tlbiva_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t asid                  : 16; /**< [ 63: 48](WO) ASID for which the TLB invalidation should be performed. */
        uint64_t reserved_44_47        : 4;
        uint64_t address               : 44; /**< [ 43:  0](WO) Address\<55:12\> to be invalidated. Note this matches the format of the address supplied to
                                                                 the ARMv8 processor TLBI invalidation instructions. If the page size is 64kB then the bits
                                                                 corresponding to address\<15:12\> are ignored. The address will be extended to bit \<63\> by
                                                                 copying bit \<55\>. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 44; /**< [ 43:  0](WO) Address\<55:12\> to be invalidated. Note this matches the format of the address supplied to
                                                                 the ARMv8 processor TLBI invalidation instructions. If the page size is 64kB then the bits
                                                                 corresponding to address\<15:12\> are ignored. The address will be extended to bit \<63\> by
                                                                 copying bit \<55\>. */
        uint64_t reserved_44_47        : 4;
        uint64_t asid                  : 16; /**< [ 63: 48](WO) ASID for which the TLB invalidation should be performed. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbiva_s cn; */
};
typedef union bdk_smmux_cbx_tlbiva bdk_smmux_cbx_tlbiva_t;

static inline uint64_t BDK_SMMUX_CBX_TLBIVA(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBIVA(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000600ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000600ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000600ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBIVA", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBIVA(a,b) bdk_smmux_cbx_tlbiva_t
#define bustype_BDK_SMMUX_CBX_TLBIVA(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_TLBIVA(a,b) "SMMUX_CBX_TLBIVA"
#define device_bar_BDK_SMMUX_CBX_TLBIVA(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBIVA(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBIVA(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_tlbivaa
 *
 * SMMU Context Invalidate TLB by VA All ASID Register
 * Invalidates all of the TLB entries that match the VA provided as an argument, regardless of
 * the ASID. This operation only has to apply to TLB entries associated with the VMID used for a
 * Stage 1 translation context bank. If SMMU()_CBAR()[HYPC] is set, this operation is
 * unpredictable. This operation only has to apply to TLB entries associated with the security
 * domain that the stage 1 translation context bank is a member of.
 * Register fields are identical to those in SMMU()_TLBIVAH64.
 */
union bdk_smmux_cbx_tlbivaa
{
    uint64_t u;
    struct bdk_smmux_cbx_tlbivaa_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t address               : 44; /**< [ 43:  0](WO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 44; /**< [ 43:  0](WO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbivaa_s cn; */
};
typedef union bdk_smmux_cbx_tlbivaa bdk_smmux_cbx_tlbivaa_t;

static inline uint64_t BDK_SMMUX_CBX_TLBIVAA(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBIVAA(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000608ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000608ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000608ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBIVAA", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBIVAA(a,b) bdk_smmux_cbx_tlbivaa_t
#define bustype_BDK_SMMUX_CBX_TLBIVAA(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_TLBIVAA(a,b) "SMMUX_CBX_TLBIVAA"
#define device_bar_BDK_SMMUX_CBX_TLBIVAA(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBIVAA(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBIVAA(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_tlbivaal
 *
 * SMMU Context Invalidate TLB by VA all ASID Last Level Register
 * Operates exactly as SMMU()_CB()_TLBIVAA, but only invalidating those that correspond
 * to the last level of the translation table walk.
 */
union bdk_smmux_cbx_tlbivaal
{
    uint64_t u;
    struct bdk_smmux_cbx_tlbivaal_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t address               : 44; /**< [ 43:  0](WO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 44; /**< [ 43:  0](WO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbivaal_s cn; */
};
typedef union bdk_smmux_cbx_tlbivaal bdk_smmux_cbx_tlbivaal_t;

static inline uint64_t BDK_SMMUX_CBX_TLBIVAAL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBIVAAL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000628ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000628ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000628ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBIVAAL", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBIVAAL(a,b) bdk_smmux_cbx_tlbivaal_t
#define bustype_BDK_SMMUX_CBX_TLBIVAAL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_TLBIVAAL(a,b) "SMMUX_CBX_TLBIVAAL"
#define device_bar_BDK_SMMUX_CBX_TLBIVAAL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBIVAAL(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBIVAAL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_tlbival
 *
 * SMMU Context Invalidate TLB by VA Last Level Register
 * Operates exactly as SMMU()_CB()_TLBIVA, but only invalidating those that correspond
 * to the last level of the translation table walk.
 */
union bdk_smmux_cbx_tlbival
{
    uint64_t u;
    struct bdk_smmux_cbx_tlbival_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t asid                  : 16; /**< [ 63: 48](WO) ASID for which the TLB invalidation should be performed. */
        uint64_t reserved_44_47        : 4;
        uint64_t address               : 44; /**< [ 43:  0](WO) Address\<55:12\> to be invalidated. Note this matches the format of the address supplied to
                                                                 the ARMv8 processor TLBI invalidation instructions. If the page size is 64kB then the bits
                                                                 corresponding to address\<15:12\> are ignored. The address will be extended to bit \<63\> by
                                                                 copying bit \<55\>. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 44; /**< [ 43:  0](WO) Address\<55:12\> to be invalidated. Note this matches the format of the address supplied to
                                                                 the ARMv8 processor TLBI invalidation instructions. If the page size is 64kB then the bits
                                                                 corresponding to address\<15:12\> are ignored. The address will be extended to bit \<63\> by
                                                                 copying bit \<55\>. */
        uint64_t reserved_44_47        : 4;
        uint64_t asid                  : 16; /**< [ 63: 48](WO) ASID for which the TLB invalidation should be performed. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbival_s cn; */
};
typedef union bdk_smmux_cbx_tlbival bdk_smmux_cbx_tlbival_t;

static inline uint64_t BDK_SMMUX_CBX_TLBIVAL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBIVAL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000620ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000620ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000620ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBIVAL", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBIVAL(a,b) bdk_smmux_cbx_tlbival_t
#define bustype_BDK_SMMUX_CBX_TLBIVAL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_TLBIVAL(a,b) "SMMUX_CBX_TLBIVAL"
#define device_bar_BDK_SMMUX_CBX_TLBIVAL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBIVAL(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBIVAL(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_tlbstatus
 *
 * SMMU Context TLB Synchronize Status Register
 * Gives the status of a TLB maintenance operation. Register fields are identical to those in
 * SMMU()_(S)TLBGSTATUS.
 */
union bdk_smmux_cbx_tlbstatus
{
    uint32_t u;
    struct bdk_smmux_cbx_tlbstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t gsactive              : 1;  /**< [  0:  0](RO/H) Global synchronize TLB invalidate active:
                                                                 0 = No global TLB synchronization operation is active.
                                                                 1 = A global TLB synchronization operation is active. */
#else /* Word 0 - Little Endian */
        uint32_t gsactive              : 1;  /**< [  0:  0](RO/H) Global synchronize TLB invalidate active:
                                                                 0 = No global TLB synchronization operation is active.
                                                                 1 = A global TLB synchronization operation is active. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbstatus_s cn; */
};
typedef union bdk_smmux_cbx_tlbstatus bdk_smmux_cbx_tlbstatus_t;

static inline uint64_t BDK_SMMUX_CBX_TLBSTATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBSTATUS(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x8300010007f4ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x8300010007f4ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x8300010007f4ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBSTATUS", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBSTATUS(a,b) bdk_smmux_cbx_tlbstatus_t
#define bustype_BDK_SMMUX_CBX_TLBSTATUS(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_TLBSTATUS(a,b) "SMMUX_CBX_TLBSTATUS"
#define device_bar_BDK_SMMUX_CBX_TLBSTATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBSTATUS(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBSTATUS(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cb#_tlbsync
 *
 * SMMU Context TLB Synchronize Invalidate Register
 * Starts a context synchronization operation that ensures the completion of any previously
 * accepted TLB Invalidate operation. Register fields are identical to those in
 * SMMU()_(S)TLBGSYNC.
 */
union bdk_smmux_cbx_tlbsync
{
    uint32_t u;
    struct bdk_smmux_cbx_tlbsync_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#else /* Word 0 - Little Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_tlbsync_s cn; */
};
typedef union bdk_smmux_cbx_tlbsync bdk_smmux_cbx_tlbsync_t;

static inline uint64_t BDK_SMMUX_CBX_TLBSYNC(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TLBSYNC(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x8300010007f0ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x8300010007f0ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x8300010007f0ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TLBSYNC", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TLBSYNC(a,b) bdk_smmux_cbx_tlbsync_t
#define bustype_BDK_SMMUX_CBX_TLBSYNC(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBX_TLBSYNC(a,b) "SMMUX_CBX_TLBSYNC"
#define device_bar_BDK_SMMUX_CBX_TLBSYNC(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TLBSYNC(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TLBSYNC(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_ttbr0
 *
 * SMMU Context Translation Table Base Register 0
 * Holds the base address of translation tables. This register is used by both stage 1 and stage
 * 2 context banks.
 */
union bdk_smmux_cbx_ttbr0
{
    uint64_t u;
    struct bdk_smmux_cbx_ttbr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t asid                  : 16; /**< [ 63: 48](R/W) Address space ID associated with this base address. The selection between
                                                                 SMMU()_CB()_TTBR0[ASID] and SMMU()_CB()_TTBR1[ASID] is determined by
                                                                 SMMU()_CB()_TCR[A1]. Bits [15:8] are only valid if
                                                                 SMMU()_CB()_TCR2[AS] ==1 and RES0 otherwise. */
        uint64_t addr                  : 44; /**< [ 47:  4](R/W) Translation table base address. */
        uint64_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_3          : 4;
        uint64_t addr                  : 44; /**< [ 47:  4](R/W) Translation table base address. */
        uint64_t asid                  : 16; /**< [ 63: 48](R/W) Address space ID associated with this base address. The selection between
                                                                 SMMU()_CB()_TTBR0[ASID] and SMMU()_CB()_TTBR1[ASID] is determined by
                                                                 SMMU()_CB()_TCR[A1]. Bits [15:8] are only valid if
                                                                 SMMU()_CB()_TCR2[AS] ==1 and RES0 otherwise. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_ttbr0_s cn; */
};
typedef union bdk_smmux_cbx_ttbr0 bdk_smmux_cbx_ttbr0_t;

static inline uint64_t BDK_SMMUX_CBX_TTBR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TTBR0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000020ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000020ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000020ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TTBR0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TTBR0(a,b) bdk_smmux_cbx_ttbr0_t
#define bustype_BDK_SMMUX_CBX_TTBR0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_TTBR0(a,b) "SMMUX_CBX_TTBR0"
#define device_bar_BDK_SMMUX_CBX_TTBR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TTBR0(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TTBR0(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_cb#_ttbr1
 *
 * SMMU Context Translation Table Base Register 1
 * Holds the base address of translation tables. This register is used by stage 1 context banks.
 * Register fields are identical to those in SMMU()_CB()_TTBR0.
 */
union bdk_smmux_cbx_ttbr1
{
    uint64_t u;
    struct bdk_smmux_cbx_ttbr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t asid                  : 16; /**< [ 63: 48](R/W) Address space ID associated with this base address. The selection between
                                                                 SMMU()_CB()_TTBR0[ASID] and SMMU()_CB()_TTBR1[ASID] is determined by
                                                                 SMMU()_CB()_TCR[A1]. Bits [15:8] are only valid if
                                                                 SMMU()_CB()_TCR2[AS] ==1 and RES0 otherwise. */
        uint64_t addr                  : 44; /**< [ 47:  4](R/W) Translation table base address. */
        uint64_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_3          : 4;
        uint64_t addr                  : 44; /**< [ 47:  4](R/W) Translation table base address. */
        uint64_t asid                  : 16; /**< [ 63: 48](R/W) Address space ID associated with this base address. The selection between
                                                                 SMMU()_CB()_TTBR0[ASID] and SMMU()_CB()_TTBR1[ASID] is determined by
                                                                 SMMU()_CB()_TCR[A1]. Bits [15:8] are only valid if
                                                                 SMMU()_CB()_TCR2[AS] ==1 and RES0 otherwise. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbx_ttbr1_s cn; */
};
typedef union bdk_smmux_cbx_ttbr1 bdk_smmux_cbx_ttbr1_t;

static inline uint64_t BDK_SMMUX_CBX_TTBR1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBX_TTBR1(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830001000028ll + 0x1000000000ll * ((a) & 0x0) + 0x10000ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830001000028ll + 0x1000000000ll * ((a) & 0x1) + 0x10000ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830001000028ll + 0x1000000000ll * ((a) & 0x3) + 0x10000ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBX_TTBR1", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBX_TTBR1(a,b) bdk_smmux_cbx_ttbr1_t
#define bustype_BDK_SMMUX_CBX_TTBR1(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CBX_TTBR1(a,b) "SMMUX_CBX_TTBR1"
#define device_bar_BDK_SMMUX_CBX_TTBR1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBX_TTBR1(a,b) (a)
#define arguments_BDK_SMMUX_CBX_TTBR1(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cba2r#
 *
 * SMMU Context Bank Attribute 2 Register
 * Extended attributes for context bank n.
 */
union bdk_smmux_cba2rx
{
    uint32_t u;
    struct bdk_smmux_cba2rx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t vmid16                : 16; /**< [ 31: 16](R/W/H) Virtual machine identifier.

                                                                 This field is 0x0 when SMMU()_(S)CR0[VMID16EN] is clear, or when
                                                                 SMMU()_IDR2[VMID16S] is clear.

                                                                 Internal:
                                                                 In 88xx pass 1, writes to SMMU()_CBAR()[VMID] also update this field
                                                                 by zeroing the upper 8 bits. */
        uint32_t reserved_3_15         : 13;
        uint32_t e2hc                  : 1;  /**< [  2:  2](R/W) Reserved. */
        uint32_t monc                  : 1;  /**< [  1:  1](R/W) Designates a secure monitor context bank (EL3):
                                                                   0 = Non-monitor context. Use VMID or ASID for TLB tagging.
                                                                   1 = Monitor context. Do not use VMID or ASID for TLB tagging.

                                                                 Ignored if the bank is nonsecure, or SMMU()_CBAR()[CTYPE] != 0x1. */
        uint32_t va64                  : 1;  /**< [  0:  0](RO) Descriptor format. If set, only AArch64 translations are permitted.
                                                                 For CNXXXX always set; ARM defines this as R/W to allow for 32-bit V7 format. */
#else /* Word 0 - Little Endian */
        uint32_t va64                  : 1;  /**< [  0:  0](RO) Descriptor format. If set, only AArch64 translations are permitted.
                                                                 For CNXXXX always set; ARM defines this as R/W to allow for 32-bit V7 format. */
        uint32_t monc                  : 1;  /**< [  1:  1](R/W) Designates a secure monitor context bank (EL3):
                                                                   0 = Non-monitor context. Use VMID or ASID for TLB tagging.
                                                                   1 = Monitor context. Do not use VMID or ASID for TLB tagging.

                                                                 Ignored if the bank is nonsecure, or SMMU()_CBAR()[CTYPE] != 0x1. */
        uint32_t e2hc                  : 1;  /**< [  2:  2](R/W) Reserved. */
        uint32_t reserved_3_15         : 13;
        uint32_t vmid16                : 16; /**< [ 31: 16](R/W/H) Virtual machine identifier.

                                                                 This field is 0x0 when SMMU()_(S)CR0[VMID16EN] is clear, or when
                                                                 SMMU()_IDR2[VMID16S] is clear.

                                                                 Internal:
                                                                 In 88xx pass 1, writes to SMMU()_CBAR()[VMID] also update this field
                                                                 by zeroing the upper 8 bits. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cba2rx_s cn88xxp1; */
    struct bdk_smmux_cba2rx_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t vmid16                : 16; /**< [ 31: 16](R/W/H) Virtual machine identifier.

                                                                 This field is 0x0 when SMMU()_(S)CR0[VMID16EN] is clear, or when
                                                                 SMMU()_IDR2[VMID16S] is clear.

                                                                 Internal:
                                                                 In 88xx pass 1, writes to SMMU()_CBAR()[VMID] also update this field
                                                                 by zeroing the upper 8 bits. */
        uint32_t reserved_3_15         : 13;
        uint32_t reserved_2            : 1;
        uint32_t monc                  : 1;  /**< [  1:  1](R/W) Designates a secure monitor context bank (EL3):
                                                                   0 = Non-monitor context. Use VMID or ASID for TLB tagging.
                                                                   1 = Monitor context. Do not use VMID or ASID for TLB tagging.

                                                                 Ignored if the bank is nonsecure, or SMMU()_CBAR()[CTYPE] != 0x1. */
        uint32_t va64                  : 1;  /**< [  0:  0](RO) Descriptor format. If set, only AArch64 translations are permitted.
                                                                 For CNXXXX always set; ARM defines this as R/W to allow for 32-bit V7 format. */
#else /* Word 0 - Little Endian */
        uint32_t va64                  : 1;  /**< [  0:  0](RO) Descriptor format. If set, only AArch64 translations are permitted.
                                                                 For CNXXXX always set; ARM defines this as R/W to allow for 32-bit V7 format. */
        uint32_t monc                  : 1;  /**< [  1:  1](R/W) Designates a secure monitor context bank (EL3):
                                                                   0 = Non-monitor context. Use VMID or ASID for TLB tagging.
                                                                   1 = Monitor context. Do not use VMID or ASID for TLB tagging.

                                                                 Ignored if the bank is nonsecure, or SMMU()_CBAR()[CTYPE] != 0x1. */
        uint32_t reserved_2            : 1;
        uint32_t reserved_3_15         : 13;
        uint32_t vmid16                : 16; /**< [ 31: 16](R/W/H) Virtual machine identifier.

                                                                 This field is 0x0 when SMMU()_(S)CR0[VMID16EN] is clear, or when
                                                                 SMMU()_IDR2[VMID16S] is clear.

                                                                 Internal:
                                                                 In 88xx pass 1, writes to SMMU()_CBAR()[VMID] also update this field
                                                                 by zeroing the upper 8 bits. */
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_smmux_cba2rx_cn81xx cn83xx; */
    /* struct bdk_smmux_cba2rx_cn81xx cn88xxp2; */
};
typedef union bdk_smmux_cba2rx bdk_smmux_cba2rx_t;

static inline uint64_t BDK_SMMUX_CBA2RX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBA2RX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830000010800ll + 0x1000000000ll * ((a) & 0x0) + 4ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830000010800ll + 0x1000000000ll * ((a) & 0x1) + 4ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830000010800ll + 0x1000000000ll * ((a) & 0x3) + 4ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBA2RX", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBA2RX(a,b) bdk_smmux_cba2rx_t
#define bustype_BDK_SMMUX_CBA2RX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBA2RX(a,b) "SMMUX_CBA2RX"
#define device_bar_BDK_SMMUX_CBA2RX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBA2RX(a,b) (a)
#define arguments_BDK_SMMUX_CBA2RX(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cbar#
 *
 * SMMU Context Bank Attribute Register
 * Specifies configuration attributes for translation context bank n. This field has different
 * layouts based on the CTYPE field value.
 */
union bdk_smmux_cbarx
{
    uint32_t u;
    struct bdk_smmux_cbarx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t wacfg                 : 2;  /**< [ 23: 22](RO) If CTYPE=1 or 3, write allocate configuration hint.

                                                                 If CTYPE=0/2, reserved.

                                                                 CNXXXX ignores the hint.

                                                                 Internal:
                                                                 Requested filed with ARM to make RO. */
        uint32_t racfg                 : 2;  /**< [ 21: 20](RO) If CTYPE=1 or 3, read allocate configuration hint.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 CNXXXX ignores the hint.

                                                                 Internal:
                                                                 Requested filed with ARM to make RO. */
        uint32_t bsu                   : 2;  /**< [ 19: 18](RO) Barrier sharability upgrade. Not implemented in CNXXXX. */
        uint32_t ctype                 : 2;  /**< [ 17: 16](R/W) Register type.   Indicates the context format. Enumerated by SMMU_CTYPE_E. */
        uint32_t memattr_cbndx4        : 4;  /**< [ 15: 12](R/W) Memory attributes, or context bank index \<7:4\>.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 If CTYPE=1, combined with the shared attributes of the previous translation stage.

                                                                 If CTYPE=3, context bank index \<7:4\>, see [BPSHCFG_CBNDX0]. */
        uint32_t fb_cbndx3             : 1;  /**< [ 11: 11](R/W) Force broadcast of TLB and cache maintenance operations or context bank index\<3\>.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 If CTYPE=1, force broadcast mode. Ignored in CNXXXX, as NCB clients do not initiate
                                                                 invalidates.

                                                                 If CTYPE=3, context bank index \<3\>, see [BPSHCFG_CBNDX0]. */
        uint32_t hypc_cbndx2           : 1;  /**< [ 10: 10](R/W) Hypervisor context or E2HC context or context bank index \<2\>.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 If CTYPE=1, and SMMU()_(S)CR0[HYPMODE]=0, hypervisor context.
                                                                 0 = Non-hypervisor context. Use VMID and ASID for TLB tagging.
                                                                 1 = Hypervisor context. Do not use VMID and ASID for TLB tagging.

                                                                 If CTYPE=1, and SMMU()_(S)CR0[HYPMODE]=1, E2HC context.  In CNXXXX, E2HC or
                                                                 non-E2HC must be set identically across all SMMUs.
                                                                 0 = Non-E2HC context.
                                                                 1 = E2HC context.

                                                                 In an interaction with the security extensions, the following restrictions apply to secure
                                                                 software: If SMMU()_SCR1[GASRAE]=0, Secure software must not set HYPC to 1 for any
                                                                 secure translation context bank. If SMMU()_SCR1[GASRAE]=1, Secure software must not
                                                                 set HYPC to 1 for any nonsecure translation context bank. Otherwise, UNPREDICTABLE
                                                                 behavior might occur.

                                                                 If CTYPE=3, context bank index \<2\>, see [BPSHCFG_CBNDX0]. */
        uint32_t bpshcfg_cbndx0        : 2;  /**< [  9:  8](R/W) Bypass shared configuration or context bank index \<1:0\>.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 If CTYPE=1, bypass shared configuration mode. CNXXXX ignores the value, R/W for software
                                                                 only.

                                                                 If CTYPE=3, context bank index \<1:0\>. The translation context bank index used for the
                                                                 stage 2 translation context bank in a nested translation. The full 8-bit context bank
                                                                 index is shared between the [MEMATTR_CBNDX4], [FB_CBNDX3], [HYPC_CBNDX2] and
                                                                 [BPSHCFG_CBNDX0] fields. Behavior is UNPREDICTABLE if the SMMU()_CBAR() register
                                                                 associated with the translation context specified by SMMU()_CBAR()[CBNDX] has
                                                                 any value other than 0x0 to specify a stage 2 translation context bank.) */
        uint32_t vmid                  : 8;  /**< [  7:  0](R/W/H) Virtual machine identifier associated with context bank.
                                                                 Writes to this field are zero extended to form a 16-bit internal VMID.
                                                                 See also SMMU()_CBA2R()[VMID16].

                                                                 This field is 0x0 when SMMU()_(S)CR0[VMID16EN] is set. */
#else /* Word 0 - Little Endian */
        uint32_t vmid                  : 8;  /**< [  7:  0](R/W/H) Virtual machine identifier associated with context bank.
                                                                 Writes to this field are zero extended to form a 16-bit internal VMID.
                                                                 See also SMMU()_CBA2R()[VMID16].

                                                                 This field is 0x0 when SMMU()_(S)CR0[VMID16EN] is set. */
        uint32_t bpshcfg_cbndx0        : 2;  /**< [  9:  8](R/W) Bypass shared configuration or context bank index \<1:0\>.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 If CTYPE=1, bypass shared configuration mode. CNXXXX ignores the value, R/W for software
                                                                 only.

                                                                 If CTYPE=3, context bank index \<1:0\>. The translation context bank index used for the
                                                                 stage 2 translation context bank in a nested translation. The full 8-bit context bank
                                                                 index is shared between the [MEMATTR_CBNDX4], [FB_CBNDX3], [HYPC_CBNDX2] and
                                                                 [BPSHCFG_CBNDX0] fields. Behavior is UNPREDICTABLE if the SMMU()_CBAR() register
                                                                 associated with the translation context specified by SMMU()_CBAR()[CBNDX] has
                                                                 any value other than 0x0 to specify a stage 2 translation context bank.) */
        uint32_t hypc_cbndx2           : 1;  /**< [ 10: 10](R/W) Hypervisor context or E2HC context or context bank index \<2\>.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 If CTYPE=1, and SMMU()_(S)CR0[HYPMODE]=0, hypervisor context.
                                                                 0 = Non-hypervisor context. Use VMID and ASID for TLB tagging.
                                                                 1 = Hypervisor context. Do not use VMID and ASID for TLB tagging.

                                                                 If CTYPE=1, and SMMU()_(S)CR0[HYPMODE]=1, E2HC context.  In CNXXXX, E2HC or
                                                                 non-E2HC must be set identically across all SMMUs.
                                                                 0 = Non-E2HC context.
                                                                 1 = E2HC context.

                                                                 In an interaction with the security extensions, the following restrictions apply to secure
                                                                 software: If SMMU()_SCR1[GASRAE]=0, Secure software must not set HYPC to 1 for any
                                                                 secure translation context bank. If SMMU()_SCR1[GASRAE]=1, Secure software must not
                                                                 set HYPC to 1 for any nonsecure translation context bank. Otherwise, UNPREDICTABLE
                                                                 behavior might occur.

                                                                 If CTYPE=3, context bank index \<2\>, see [BPSHCFG_CBNDX0]. */
        uint32_t fb_cbndx3             : 1;  /**< [ 11: 11](R/W) Force broadcast of TLB and cache maintenance operations or context bank index\<3\>.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 If CTYPE=1, force broadcast mode. Ignored in CNXXXX, as NCB clients do not initiate
                                                                 invalidates.

                                                                 If CTYPE=3, context bank index \<3\>, see [BPSHCFG_CBNDX0]. */
        uint32_t memattr_cbndx4        : 4;  /**< [ 15: 12](R/W) Memory attributes, or context bank index \<7:4\>.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 If CTYPE=1, combined with the shared attributes of the previous translation stage.

                                                                 If CTYPE=3, context bank index \<7:4\>, see [BPSHCFG_CBNDX0]. */
        uint32_t ctype                 : 2;  /**< [ 17: 16](R/W) Register type.   Indicates the context format. Enumerated by SMMU_CTYPE_E. */
        uint32_t bsu                   : 2;  /**< [ 19: 18](RO) Barrier sharability upgrade. Not implemented in CNXXXX. */
        uint32_t racfg                 : 2;  /**< [ 21: 20](RO) If CTYPE=1 or 3, read allocate configuration hint.

                                                                 If CTYPE=0 or 2, reserved.

                                                                 CNXXXX ignores the hint.

                                                                 Internal:
                                                                 Requested filed with ARM to make RO. */
        uint32_t wacfg                 : 2;  /**< [ 23: 22](RO) If CTYPE=1 or 3, write allocate configuration hint.

                                                                 If CTYPE=0/2, reserved.

                                                                 CNXXXX ignores the hint.

                                                                 Internal:
                                                                 Requested filed with ARM to make RO. */
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbarx_s cn; */
};
typedef union bdk_smmux_cbarx bdk_smmux_cbarx_t;

static inline uint64_t BDK_SMMUX_CBARX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBARX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830000010000ll + 0x1000000000ll * ((a) & 0x0) + 4ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830000010000ll + 0x1000000000ll * ((a) & 0x1) + 4ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830000010000ll + 0x1000000000ll * ((a) & 0x3) + 4ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBARX", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBARX(a,b) bdk_smmux_cbarx_t
#define bustype_BDK_SMMUX_CBARX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBARX(a,b) "SMMUX_CBARX"
#define device_bar_BDK_SMMUX_CBARX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBARX(a,b) (a)
#define arguments_BDK_SMMUX_CBARX(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cbfrsynra#
 *
 * SMMU Context Bank Fault Restricted Syndrome A Register
 * Gives fault syndrome information about the access that caused an exception in the associated
 * translation.
 */
union bdk_smmux_cbfrsynrax
{
    uint32_t u;
    struct bdk_smmux_cbfrsynrax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ssd_index             : 16; /**< [ 31: 16](SRO/H) SSD index of the transaction that caused the fault. Only accessible to configuration
                                                                 accesses by secure software, else RAZ/WI. For CNXXXX, set on a fault to always match
                                                                 STREAMID.

                                                                 Internal:
                                                                 Requested ARM extend this into \<31\>. */
        uint32_t streamid              : 16; /**< [ 15:  0](R/W/H) Stream ID of the transaction that caused the fault. */
#else /* Word 0 - Little Endian */
        uint32_t streamid              : 16; /**< [ 15:  0](R/W/H) Stream ID of the transaction that caused the fault. */
        uint32_t ssd_index             : 16; /**< [ 31: 16](SRO/H) SSD index of the transaction that caused the fault. Only accessible to configuration
                                                                 accesses by secure software, else RAZ/WI. For CNXXXX, set on a fault to always match
                                                                 STREAMID.

                                                                 Internal:
                                                                 Requested ARM extend this into \<31\>. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cbfrsynrax_s cn; */
};
typedef union bdk_smmux_cbfrsynrax bdk_smmux_cbfrsynrax_t;

static inline uint64_t BDK_SMMUX_CBFRSYNRAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CBFRSYNRAX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=63)))
        return 0x830000010400ll + 0x1000000000ll * ((a) & 0x0) + 4ll * ((b) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830000010400ll + 0x1000000000ll * ((a) & 0x1) + 4ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830000010400ll + 0x1000000000ll * ((a) & 0x3) + 4ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_CBFRSYNRAX", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_CBFRSYNRAX(a,b) bdk_smmux_cbfrsynrax_t
#define bustype_BDK_SMMUX_CBFRSYNRAX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CBFRSYNRAX(a,b) "SMMUX_CBFRSYNRAX"
#define device_bar_BDK_SMMUX_CBFRSYNRAX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CBFRSYNRAX(a,b) (a)
#define arguments_BDK_SMMUX_CBFRSYNRAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_cidr0
 *
 * SMMU Component Identification Register 0
 */
union bdk_smmux_cidr0
{
    uint32_t u;
    struct bdk_smmux_cidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t preamble              : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t preamble              : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cidr0_s cn; */
};
typedef union bdk_smmux_cidr0 bdk_smmux_cidr0_t;

static inline uint64_t BDK_SMMUX_CIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CIDR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000ff0ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000ff0ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000ff0ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000ff0ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CIDR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CIDR0(a) bdk_smmux_cidr0_t
#define bustype_BDK_SMMUX_CIDR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CIDR0(a) "SMMUX_CIDR0"
#define device_bar_BDK_SMMUX_CIDR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CIDR0(a) (a)
#define arguments_BDK_SMMUX_CIDR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cidr1
 *
 * SMMU Component Identification Register 1
 */
union bdk_smmux_cidr1
{
    uint32_t u;
    struct bdk_smmux_cidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t preamble              : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t preamble              : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cidr1_s cn; */
};
typedef union bdk_smmux_cidr1 bdk_smmux_cidr1_t;

static inline uint64_t BDK_SMMUX_CIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CIDR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000ff4ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000ff4ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000ff4ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000ff4ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CIDR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CIDR1(a) bdk_smmux_cidr1_t
#define bustype_BDK_SMMUX_CIDR1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CIDR1(a) "SMMUX_CIDR1"
#define device_bar_BDK_SMMUX_CIDR1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CIDR1(a) (a)
#define arguments_BDK_SMMUX_CIDR1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cidr2
 *
 * SMMU Component Identification Register 2
 */
union bdk_smmux_cidr2
{
    uint32_t u;
    struct bdk_smmux_cidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t preamble              : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t preamble              : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cidr2_s cn; */
};
typedef union bdk_smmux_cidr2 bdk_smmux_cidr2_t;

static inline uint64_t BDK_SMMUX_CIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CIDR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000ff8ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000ff8ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000ff8ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000ff8ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CIDR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CIDR2(a) bdk_smmux_cidr2_t
#define bustype_BDK_SMMUX_CIDR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CIDR2(a) "SMMUX_CIDR2"
#define device_bar_BDK_SMMUX_CIDR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CIDR2(a) (a)
#define arguments_BDK_SMMUX_CIDR2(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cidr3
 *
 * SMMU Component Identification Register 3
 */
union bdk_smmux_cidr3
{
    uint32_t u;
    struct bdk_smmux_cidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t preamble              : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t preamble              : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cidr3_s cn; */
};
typedef union bdk_smmux_cidr3 bdk_smmux_cidr3_t;

static inline uint64_t BDK_SMMUX_CIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CIDR3(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000ffcll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000ffcll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000ffcll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000ffcll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CIDR3", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CIDR3(a) bdk_smmux_cidr3_t
#define bustype_BDK_SMMUX_CIDR3(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CIDR3(a) "SMMUX_CIDR3"
#define device_bar_BDK_SMMUX_CIDR3(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CIDR3(a) (a)
#define arguments_BDK_SMMUX_CIDR3(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_cmdq_base
 *
 * SMMU Command Queue Base Register
 */
union bdk_smmux_cmdq_base
{
    uint64_t u;
    struct bdk_smmux_cmdq_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t ra                    : 1;  /**< [ 62: 62](R/W) SMMU(0)_S_CMDQ_BASE[RA] */
        uint64_t reserved_52_61        : 10;
        uint64_t addr                  : 47; /**< [ 51:  5](R/W) SMMU(0)_S_CMDQ_BASE[ADDR] */
        uint64_t log2size              : 5;  /**< [  4:  0](R/W) SMMU(0)_S_CMDQ_BASE[LOG2SIZE] */
#else /* Word 0 - Little Endian */
        uint64_t log2size              : 5;  /**< [  4:  0](R/W) SMMU(0)_S_CMDQ_BASE[LOG2SIZE] */
        uint64_t addr                  : 47; /**< [ 51:  5](R/W) SMMU(0)_S_CMDQ_BASE[ADDR] */
        uint64_t reserved_52_61        : 10;
        uint64_t ra                    : 1;  /**< [ 62: 62](R/W) SMMU(0)_S_CMDQ_BASE[RA] */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cmdq_base_s cn; */
};
typedef union bdk_smmux_cmdq_base bdk_smmux_cmdq_base_t;

static inline uint64_t BDK_SMMUX_CMDQ_BASE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CMDQ_BASE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000090ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CMDQ_BASE", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CMDQ_BASE(a) bdk_smmux_cmdq_base_t
#define bustype_BDK_SMMUX_CMDQ_BASE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_CMDQ_BASE(a) "SMMUX_CMDQ_BASE"
#define device_bar_BDK_SMMUX_CMDQ_BASE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CMDQ_BASE(a) (a)
#define arguments_BDK_SMMUX_CMDQ_BASE(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cmdq_cons
 *
 * SMMU Command Queue Consumer Register
 */
union bdk_smmux_cmdq_cons
{
    uint32_t u;
    struct bdk_smmux_cmdq_cons_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t errx                  : 7;  /**< [ 30: 24](RO/H) SMMU(0)_S_CMDQ_CONS[ERRX] */
        uint32_t reserved_20_23        : 4;
        uint32_t rd                    : 20; /**< [ 19:  0](R/W/H) SMMU(0)_S_CMDQ_CONS[RD] */
#else /* Word 0 - Little Endian */
        uint32_t rd                    : 20; /**< [ 19:  0](R/W/H) SMMU(0)_S_CMDQ_CONS[RD] */
        uint32_t reserved_20_23        : 4;
        uint32_t errx                  : 7;  /**< [ 30: 24](RO/H) SMMU(0)_S_CMDQ_CONS[ERRX] */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cmdq_cons_s cn; */
};
typedef union bdk_smmux_cmdq_cons bdk_smmux_cmdq_cons_t;

static inline uint64_t BDK_SMMUX_CMDQ_CONS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CMDQ_CONS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x83000000009cll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CMDQ_CONS", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CMDQ_CONS(a) bdk_smmux_cmdq_cons_t
#define bustype_BDK_SMMUX_CMDQ_CONS(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CMDQ_CONS(a) "SMMUX_CMDQ_CONS"
#define device_bar_BDK_SMMUX_CMDQ_CONS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CMDQ_CONS(a) (a)
#define arguments_BDK_SMMUX_CMDQ_CONS(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cmdq_prod
 *
 * SMMU Command Queue Producer Register
 */
union bdk_smmux_cmdq_prod
{
    uint32_t u;
    struct bdk_smmux_cmdq_prod_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t wr                    : 20; /**< [ 19:  0](R/W) SMMU(0)_S_CMDQ_PROD[WR] */
#else /* Word 0 - Little Endian */
        uint32_t wr                    : 20; /**< [ 19:  0](R/W) SMMU(0)_S_CMDQ_PROD[WR] */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cmdq_prod_s cn; */
};
typedef union bdk_smmux_cmdq_prod bdk_smmux_cmdq_prod_t;

static inline uint64_t BDK_SMMUX_CMDQ_PROD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CMDQ_PROD(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000098ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CMDQ_PROD", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CMDQ_PROD(a) bdk_smmux_cmdq_prod_t
#define bustype_BDK_SMMUX_CMDQ_PROD(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CMDQ_PROD(a) "SMMUX_CMDQ_PROD"
#define device_bar_BDK_SMMUX_CMDQ_PROD(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CMDQ_PROD(a) (a)
#define arguments_BDK_SMMUX_CMDQ_PROD(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cr0
 *
 * SMMU Control 0 Register
 * Each field in this register has a corresponding field in SMMU()_CR0ACK. An
 * individual field is said to be "updated" after the value of the field observed in
 * SMMU()_CR0ACK matches the value that was written to the field in
 * SMMU()_CR0. Reserved fields in SMMU()_CR0 are not reflected in SMMU()_CR0ACK. To
 * ensure a field change has taken effect, software must poll the equivalent field in
 * SMMU()_CR0ACK after writing the field in this register.
 *
 * Each field in this register is independent and unaffected by ongoing update
 * procedures of adjacent fields.
 *
 * Update of a field must complete in reasonable time, but is not required to occur
 * immediately.  The update process may have side effects which are guaranteed to be
 * complete by the time update completes. See below for details of any side effects.
 *
 * A field that has been written is considered to be in a transitional state until
 * update has completed. Anything depending on its value observes the old value until
 * the new value takes effect at an unpredictable point before update completes
 * whereupon the new value is guaranteed to be used, therefore:
 *
 * A written field cannot be assumed to have taken the new value until update completes.
 *
 * A written field cannot be assumed not to have taken the new value after the write is
 * observed by the SMMU.
 *
 * Anywhere behavior depending on a field value (for example, a rule of the form "REG
 * must only be changed if SMMUEN=0"), it is the post-update value that is referred
 * to. In this example, the rule would be broken were REG to be changed after the point
 * that SMMU()_(S_)SMMUEN has been written to one even if update has not
 * completed. Similarly, a field that has been written and is still in a transitional
 * state (pre-update completion) must be considered to still have the old value for the
 * purposes of constraints the old value places upon software. For example,
 * SMMU()_CMDQ_CONS must not be written when CMDQEN=1, or during an as -yet incomplete
 * transition to 0 (as [CMDQEN] must still be considered to be one).
 *
 * After altering a field value, software must not alter the field's value again before
 * the initial alteration's update is complete. Behavior on doing so is constrained
 * unpredictable and one of the following occurs: The new value is stored and the
 * update completes with any of the values written.
 *
 * The effective field value in use might not match that read back from this register.
 * The new value is ignored and update completes using the first value (reflected in
 * SMMU()_CR0ACK).  Cease update if the new value is the same as the original value
 * before the first write.  This means no update side effects would occur.
 *
 * A write with the same value (i.e. not altered) is permitted; this might occur when
 * altering an unrelated field in the same register whilst an earlier field update is
 * in process.
 */
union bdk_smmux_cr0
{
    uint32_t u;
    struct bdk_smmux_cr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t vmw                   : 3;  /**< [  8:  6](RAZ) VMID wildcard.
                                                                  000 = TLB invalidations (broadcast or command) match VMID tags exactly.

                                                                 For CNXXXX, other values not supported.

                                                                 Internal:
                                                                 001 = TLB invalidations match VMID\<N:1\>.
                                                                 010 = TLB invalidations match VMID\<N:2\>.
                                                                 011 = TLB invalidations match VMID\<N:3\>.
                                                                 100 = TLB invalidations match VMID\<N:4\>.
                                                                 1xx = Reserved (behaves as 000).

                                                                 N = upper bit of VMID as determined by SMMU()_IDR0[VMID16].

                                                                 This field may be used to associate VMIDs into groups of 1, 2, 4, 8 or 16 VMIDs
                                                                 that are considered equivalent for the purposes of invalidation (whether due to
                                                                 broadcast TLB invalidation operations, or SMMU TLB invalidation commands). This
                                                                 allows all TLB entries created from a set of differing stage 2 address spaces to
                                                                 be maintained with broadcast invalidation targeting one specific VMID in the
                                                                 group.

                                                                 This field has no effect on VMID matching on translation lookup.

                                                                 If SMMU()_IDR0[VMW]=0, this field is Reserved. */
        uint32_t reserved_5            : 1;
        uint32_t atschk                : 1;  /**< [  4:  4](RAZ) ATS behavior.

                                                                 In CNXXXX, reserved.

                                                                 Internal:
                                                                 0 = Fast mode; all ATS translated traffic passes through the SMMU without
                                                                 stream table/TLB lookup.

                                                                 1 = Safe mode; all ATS translated traffic is checked against the corresponding
                                                                 SMMU_STE_S[EATS] to determine whether the StreamID is allowed to produce
                                                                 translated transactions.

                                                                 If SMMU()_IDR0[ATS]=0, this field is reserved. */
        uint32_t cmdqen                : 1;  /**< [  3:  3](R/W) Enable command queue processing. */
        uint32_t eventqen              : 1;  /**< [  2:  2](R/W) Enable event queue writes. */
        uint32_t priqen                : 1;  /**< [  1:  1](RAZ) Enable pri queue writes.
                                                                 In CNXXXX, reserved.

                                                                 Internal:
                                                                 If SMMU()_IDR0[PRI]=0, this field is reserved. */
        uint32_t smmuen                : 1;  /**< [  0:  0](R/W) SMMU NS enable.
                                                                 0 = All non-secure traffic bypasses SMMU with attributes
                                                                 determined from SMMU()_GBPA.

                                                                 1 = All non-secure transactions are checked against configuration structures and
                                                                 may (if the relevant STE enables it) undergo translation.  SMMU()_S_CR0 has
                                                                 separate enable for secure interface and traffic. */
#else /* Word 0 - Little Endian */
        uint32_t smmuen                : 1;  /**< [  0:  0](R/W) SMMU NS enable.
                                                                 0 = All non-secure traffic bypasses SMMU with attributes
                                                                 determined from SMMU()_GBPA.

                                                                 1 = All non-secure transactions are checked against configuration structures and
                                                                 may (if the relevant STE enables it) undergo translation.  SMMU()_S_CR0 has
                                                                 separate enable for secure interface and traffic. */
        uint32_t priqen                : 1;  /**< [  1:  1](RAZ) Enable pri queue writes.
                                                                 In CNXXXX, reserved.

                                                                 Internal:
                                                                 If SMMU()_IDR0[PRI]=0, this field is reserved. */
        uint32_t eventqen              : 1;  /**< [  2:  2](R/W) Enable event queue writes. */
        uint32_t cmdqen                : 1;  /**< [  3:  3](R/W) Enable command queue processing. */
        uint32_t atschk                : 1;  /**< [  4:  4](RAZ) ATS behavior.

                                                                 In CNXXXX, reserved.

                                                                 Internal:
                                                                 0 = Fast mode; all ATS translated traffic passes through the SMMU without
                                                                 stream table/TLB lookup.

                                                                 1 = Safe mode; all ATS translated traffic is checked against the corresponding
                                                                 SMMU_STE_S[EATS] to determine whether the StreamID is allowed to produce
                                                                 translated transactions.

                                                                 If SMMU()_IDR0[ATS]=0, this field is reserved. */
        uint32_t reserved_5            : 1;
        uint32_t vmw                   : 3;  /**< [  8:  6](RAZ) VMID wildcard.
                                                                  000 = TLB invalidations (broadcast or command) match VMID tags exactly.

                                                                 For CNXXXX, other values not supported.

                                                                 Internal:
                                                                 001 = TLB invalidations match VMID\<N:1\>.
                                                                 010 = TLB invalidations match VMID\<N:2\>.
                                                                 011 = TLB invalidations match VMID\<N:3\>.
                                                                 100 = TLB invalidations match VMID\<N:4\>.
                                                                 1xx = Reserved (behaves as 000).

                                                                 N = upper bit of VMID as determined by SMMU()_IDR0[VMID16].

                                                                 This field may be used to associate VMIDs into groups of 1, 2, 4, 8 or 16 VMIDs
                                                                 that are considered equivalent for the purposes of invalidation (whether due to
                                                                 broadcast TLB invalidation operations, or SMMU TLB invalidation commands). This
                                                                 allows all TLB entries created from a set of differing stage 2 address spaces to
                                                                 be maintained with broadcast invalidation targeting one specific VMID in the
                                                                 group.

                                                                 This field has no effect on VMID matching on translation lookup.

                                                                 If SMMU()_IDR0[VMW]=0, this field is Reserved. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cr0_s cn; */
};
typedef union bdk_smmux_cr0 bdk_smmux_cr0_t;

static inline uint64_t BDK_SMMUX_CR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000020ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CR0(a) bdk_smmux_cr0_t
#define bustype_BDK_SMMUX_CR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CR0(a) "SMMUX_CR0"
#define device_bar_BDK_SMMUX_CR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CR0(a) (a)
#define arguments_BDK_SMMUX_CR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cr0ack
 *
 * SMMU Control 0 Acknowledgement Register
 * This register is a read-only copy of SMMU()_CR0.
 */
union bdk_smmux_cr0ack
{
    uint32_t u;
    struct bdk_smmux_cr0ack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t vmw                   : 3;  /**< [  8:  6](RAZ) Read-only hardware-modified SMMU(0)_CR0[VMW].
                                                                 Internal:
                                                                 001 = TLB invalidations match VMID\<N:1\>.
                                                                 010 = TLB invalidations match VMID\<N:2\>.
                                                                 011 = TLB invalidations match VMID\<N:3\>.
                                                                 100 = TLB invalidations match VMID\<N:4\>.
                                                                 1xx = Reserved (behaves as 000).

                                                                 N = upper bit of VMID as determined by SMMU()_IDR0[VMID16].

                                                                 This field may be used to associate VMIDs into groups of 1, 2, 4, 8 or 16 VMIDs
                                                                 that are considered equivalent for the purposes of invalidation (whether due to
                                                                 broadcast TLB invalidation operations, or SMMU TLB invalidation commands). This
                                                                 allows all TLB entries created from a set of differing stage 2 address spaces to
                                                                 be maintained with broadcast invalidation targeting one specific VMID in the
                                                                 group.

                                                                 This field has no effect on VMID matching on translation lookup.

                                                                 If SMMU()_IDR0[VMW]=0, this field is Reserved. */
        uint32_t reserved_5            : 1;
        uint32_t atschk                : 1;  /**< [  4:  4](RAZ) Read-only hardware-modified SMMU(0)_CR0[ATSCHK].
                                                                 Internal:
                                                                 0 = Fast mode; all ATS translated traffic passes through the SMMU without
                                                                 stream table/TLB lookup.

                                                                 1 = Safe mode; all ATS translated traffic is checked against the corresponding
                                                                 SMMU_STE_S[EATS] to determine whether the StreamID is allowed to produce
                                                                 translated transactions.

                                                                 If SMMU()_IDR0[ATS]=0, this field is reserved. */
        uint32_t cmdqen                : 1;  /**< [  3:  3](RO/H) Read-only hardware-modified SMMU(0)_CR0[CMDQEN]. */
        uint32_t eventqen              : 1;  /**< [  2:  2](RO/H) Read-only hardware-modified SMMU(0)_CR0[EVENTQEN]. */
        uint32_t priqen                : 1;  /**< [  1:  1](RAZ) Read-only hardware-modified SMMU(0)_CR0[PRIQEN].
                                                                 Internal:
                                                                 If SMMU()_IDR0[PRI]=0, this field is reserved. */
        uint32_t smmuen                : 1;  /**< [  0:  0](RO/H) Read-only hardware-modified SMMU(0)_CR0[SMMUEN]. */
#else /* Word 0 - Little Endian */
        uint32_t smmuen                : 1;  /**< [  0:  0](RO/H) Read-only hardware-modified SMMU(0)_CR0[SMMUEN]. */
        uint32_t priqen                : 1;  /**< [  1:  1](RAZ) Read-only hardware-modified SMMU(0)_CR0[PRIQEN].
                                                                 Internal:
                                                                 If SMMU()_IDR0[PRI]=0, this field is reserved. */
        uint32_t eventqen              : 1;  /**< [  2:  2](RO/H) Read-only hardware-modified SMMU(0)_CR0[EVENTQEN]. */
        uint32_t cmdqen                : 1;  /**< [  3:  3](RO/H) Read-only hardware-modified SMMU(0)_CR0[CMDQEN]. */
        uint32_t atschk                : 1;  /**< [  4:  4](RAZ) Read-only hardware-modified SMMU(0)_CR0[ATSCHK].
                                                                 Internal:
                                                                 0 = Fast mode; all ATS translated traffic passes through the SMMU without
                                                                 stream table/TLB lookup.

                                                                 1 = Safe mode; all ATS translated traffic is checked against the corresponding
                                                                 SMMU_STE_S[EATS] to determine whether the StreamID is allowed to produce
                                                                 translated transactions.

                                                                 If SMMU()_IDR0[ATS]=0, this field is reserved. */
        uint32_t reserved_5            : 1;
        uint32_t vmw                   : 3;  /**< [  8:  6](RAZ) Read-only hardware-modified SMMU(0)_CR0[VMW].
                                                                 Internal:
                                                                 001 = TLB invalidations match VMID\<N:1\>.
                                                                 010 = TLB invalidations match VMID\<N:2\>.
                                                                 011 = TLB invalidations match VMID\<N:3\>.
                                                                 100 = TLB invalidations match VMID\<N:4\>.
                                                                 1xx = Reserved (behaves as 000).

                                                                 N = upper bit of VMID as determined by SMMU()_IDR0[VMID16].

                                                                 This field may be used to associate VMIDs into groups of 1, 2, 4, 8 or 16 VMIDs
                                                                 that are considered equivalent for the purposes of invalidation (whether due to
                                                                 broadcast TLB invalidation operations, or SMMU TLB invalidation commands). This
                                                                 allows all TLB entries created from a set of differing stage 2 address spaces to
                                                                 be maintained with broadcast invalidation targeting one specific VMID in the
                                                                 group.

                                                                 This field has no effect on VMID matching on translation lookup.

                                                                 If SMMU()_IDR0[VMW]=0, this field is Reserved. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cr0ack_s cn; */
};
typedef union bdk_smmux_cr0ack bdk_smmux_cr0ack_t;

static inline uint64_t BDK_SMMUX_CR0ACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CR0ACK(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000024ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CR0ACK", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CR0ACK(a) bdk_smmux_cr0ack_t
#define bustype_BDK_SMMUX_CR0ACK(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CR0ACK(a) "SMMUX_CR0ACK"
#define device_bar_BDK_SMMUX_CR0ACK(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CR0ACK(a) (a)
#define arguments_BDK_SMMUX_CR0ACK(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cr1
 *
 * SMMU Control 1 Register
 */
union bdk_smmux_cr1
{
    uint32_t u;
    struct bdk_smmux_cr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_12_31        : 20;
        uint32_t table_sh              : 2;  /**< [ 11: 10](R/W) SMMU(0)_S_CR1[TABLE_SH] */
        uint32_t table_oc              : 2;  /**< [  9:  8](R/W) SMMU(0)_S_CR1[TABLE_OC] */
        uint32_t table_ic              : 2;  /**< [  7:  6](R/W) SMMU(0)_S_CR1[TABLE_IC] */
        uint32_t queue_sh              : 2;  /**< [  5:  4](R/W) SMMU(0)_S_CR1[QUEUE_SH] */
        uint32_t queue_oc              : 2;  /**< [  3:  2](R/W) SMMU(0)_S_CR1[QUEUE_OC] */
        uint32_t queue_ic              : 2;  /**< [  1:  0](R/W) SMMU(0)_S_CR1[QUEUE_IC] */
#else /* Word 0 - Little Endian */
        uint32_t queue_ic              : 2;  /**< [  1:  0](R/W) SMMU(0)_S_CR1[QUEUE_IC] */
        uint32_t queue_oc              : 2;  /**< [  3:  2](R/W) SMMU(0)_S_CR1[QUEUE_OC] */
        uint32_t queue_sh              : 2;  /**< [  5:  4](R/W) SMMU(0)_S_CR1[QUEUE_SH] */
        uint32_t table_ic              : 2;  /**< [  7:  6](R/W) SMMU(0)_S_CR1[TABLE_IC] */
        uint32_t table_oc              : 2;  /**< [  9:  8](R/W) SMMU(0)_S_CR1[TABLE_OC] */
        uint32_t table_sh              : 2;  /**< [ 11: 10](R/W) SMMU(0)_S_CR1[TABLE_SH] */
        uint32_t reserved_12_31        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cr1_s cn; */
};
typedef union bdk_smmux_cr1 bdk_smmux_cr1_t;

static inline uint64_t BDK_SMMUX_CR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000028ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CR1(a) bdk_smmux_cr1_t
#define bustype_BDK_SMMUX_CR1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CR1(a) "SMMUX_CR1"
#define device_bar_BDK_SMMUX_CR1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CR1(a) (a)
#define arguments_BDK_SMMUX_CR1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_cr2
 *
 * SMMU Control 2 Register
 */
union bdk_smmux_cr2
{
    uint32_t u;
    struct bdk_smmux_cr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t ptm                   : 1;  /**< [  2:  2](R/W) Private TLB maintenance.

                                                                 When set, the SMMU is not expected to invalidate any local TLB entries on receipt of
                                                                 broadcast TLB maintenance operations for NS-EL1, EL2, or EL2-E2H translation regimes.

                                                                 Broadcast invalidation for S-EL1 or EL3 translation regimes are not affected by
                                                                 this flag; see SMMU()_S_CR2[PTM].

                                                                 Internal:
                                                                 When SMMU()_IDR0[BTM]=0, this field is reserved. */
        uint32_t recinvsid             : 1;  /**< [  1:  1](R/W) Record event SMMU_C_BAD_STREAMID_S from invalid input StreamIDs. When the SMMU
                                                                 is enabled, all traffic should be associated with a valid, reachable STE. Any
                                                                 transaction with a StreamID out of the range of a linear stream table, reaching
                                                                 an invalid pointer in a two-level stream table or out of the range of a second level
                                                                 array will be aborted. This bit determines whether SMMU_C_BAD_STREAMID_S events
                                                                 are recorded when this happens. */
        uint32_t e2h                   : 1;  /**< [  0:  0](R/W) Enable EL2-E2H translation regime for EL2 stream worlds.
                                                                   0 = EL2 translation regime, without ASIDs or VMIDs.
                                                                   1 = EL2-E2H translation regime used, with ASID.

                                                                 This field affects the SMMU_STE_S[STRW] encoding 0x2, which selects a hypervisor
                                                                 translation regime for the resulting translations; the translations are tagged
                                                                 without ASID in EL2 mode, or with ASID in EL2-E2H mode.

                                                                 This field should match the HCR_EL2[E2H] field in host CPUs.

                                                                 This bit is permitted to be cached in configuration caches and TLBs. Changes to
                                                                 this bit must be accompanied by invalidation of configuration and translations
                                                                 pertinent to streams configured with SMMU_STE_S[STRW]=EL2/EL2-E2H.

                                                                 When SMMU()_IDR0[HYP]=0, this field is reserved. */
#else /* Word 0 - Little Endian */
        uint32_t e2h                   : 1;  /**< [  0:  0](R/W) Enable EL2-E2H translation regime for EL2 stream worlds.
                                                                   0 = EL2 translation regime, without ASIDs or VMIDs.
                                                                   1 = EL2-E2H translation regime used, with ASID.

                                                                 This field affects the SMMU_STE_S[STRW] encoding 0x2, which selects a hypervisor
                                                                 translation regime for the resulting translations; the translations are tagged
                                                                 without ASID in EL2 mode, or with ASID in EL2-E2H mode.

                                                                 This field should match the HCR_EL2[E2H] field in host CPUs.

                                                                 This bit is permitted to be cached in configuration caches and TLBs. Changes to
                                                                 this bit must be accompanied by invalidation of configuration and translations
                                                                 pertinent to streams configured with SMMU_STE_S[STRW]=EL2/EL2-E2H.

                                                                 When SMMU()_IDR0[HYP]=0, this field is reserved. */
        uint32_t recinvsid             : 1;  /**< [  1:  1](R/W) Record event SMMU_C_BAD_STREAMID_S from invalid input StreamIDs. When the SMMU
                                                                 is enabled, all traffic should be associated with a valid, reachable STE. Any
                                                                 transaction with a StreamID out of the range of a linear stream table, reaching
                                                                 an invalid pointer in a two-level stream table or out of the range of a second level
                                                                 array will be aborted. This bit determines whether SMMU_C_BAD_STREAMID_S events
                                                                 are recorded when this happens. */
        uint32_t ptm                   : 1;  /**< [  2:  2](R/W) Private TLB maintenance.

                                                                 When set, the SMMU is not expected to invalidate any local TLB entries on receipt of
                                                                 broadcast TLB maintenance operations for NS-EL1, EL2, or EL2-E2H translation regimes.

                                                                 Broadcast invalidation for S-EL1 or EL3 translation regimes are not affected by
                                                                 this flag; see SMMU()_S_CR2[PTM].

                                                                 Internal:
                                                                 When SMMU()_IDR0[BTM]=0, this field is reserved. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_cr2_s cn; */
};
typedef union bdk_smmux_cr2 bdk_smmux_cr2_t;

static inline uint64_t BDK_SMMUX_CR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_CR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x83000000002cll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_CR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_CR2(a) bdk_smmux_cr2_t
#define bustype_BDK_SMMUX_CR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_CR2(a) "SMMUX_CR2"
#define device_bar_BDK_SMMUX_CR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_CR2(a) (a)
#define arguments_BDK_SMMUX_CR2(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_debug
 *
 * SMMU Debug Registers
 * This register contains debug information.
 */
union bdk_smmux_debug
{
    uint64_t u;
    struct bdk_smmux_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_30_63        : 34;
        uint64_t inflight              : 9;  /**< [ 29: 21](RO/H) Valid entries in inflight queue. */
        uint64_t walker                : 5;  /**< [ 20: 16](RO/H) Walkers active. */
        uint64_t translation_ch1       : 8;  /**< [ 15:  8](RO/H) Channel 1 translations in progress. */
        uint64_t translation_ch0       : 8;  /**< [  7:  0](RO/H) Channel 0 translations in progress. */
#else /* Word 0 - Little Endian */
        uint64_t translation_ch0       : 8;  /**< [  7:  0](RO/H) Channel 0 translations in progress. */
        uint64_t translation_ch1       : 8;  /**< [ 15:  8](RO/H) Channel 1 translations in progress. */
        uint64_t walker                : 5;  /**< [ 20: 16](RO/H) Walkers active. */
        uint64_t inflight              : 9;  /**< [ 29: 21](RO/H) Valid entries in inflight queue. */
        uint64_t reserved_30_63        : 34;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_debug_s cn; */
};
typedef union bdk_smmux_debug bdk_smmux_debug_t;

static inline uint64_t BDK_SMMUX_DEBUG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_DEBUG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000021070ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000021070ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=3))
        return 0x830000021070ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_DEBUG", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_DEBUG(a) bdk_smmux_debug_t
#define bustype_BDK_SMMUX_DEBUG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_DEBUG(a) "SMMUX_DEBUG"
#define device_bar_BDK_SMMUX_DEBUG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_DEBUG(a) (a)
#define arguments_BDK_SMMUX_DEBUG(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_diag_ctl
 *
 * SMMU Secure Diagnostic Control Register
 */
union bdk_smmux_diag_ctl
{
    uint64_t u;
    struct bdk_smmux_diag_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t pg_cmb                : 2;  /**< [ 16: 15](SRO) Reserved. */
        uint64_t force_clks_active     : 1;  /**< [ 14: 14](SR/W) Forces the conditional clocks to be always on. For diagnostic use only. */
        uint64_t walkers               : 6;  /**< [ 13:  8](SR/W) Number of walkers. The number of page table walkers that may
                                                                 simultaneously be executing, minus one.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's.
                                                                 For diagnostic use only. */
        uint64_t reserved_7            : 1;
        uint64_t throttle              : 1;  /**< [  6:  6](SR/W) Throttle throughput. For diagnostic use only. If set, limit translations to one every four
                                                                 cycles, to insure OCLA debug FIFOs will not overrun.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's. */
        uint64_t dis_bcstr             : 1;  /**< [  5:  5](SR/W) Reserved. */
        uint64_t dis_wcs1              : 2;  /**< [  4:  3](SR/W) Disables hitting in the walk cache for stage 1 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint64_t dis_wcs2              : 2;  /**< [  2:  1](SR/W) Disables hitting in the walk cache for stage 2 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint64_t dis_tlb               : 1;  /**< [  0:  0](SR/W) Disables hitting in the TLB. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dis_tlb               : 1;  /**< [  0:  0](SR/W) Disables hitting in the TLB. For diagnostic use only. */
        uint64_t dis_wcs2              : 2;  /**< [  2:  1](SR/W) Disables hitting in the walk cache for stage 2 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint64_t dis_wcs1              : 2;  /**< [  4:  3](SR/W) Disables hitting in the walk cache for stage 1 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint64_t dis_bcstr             : 1;  /**< [  5:  5](SR/W) Reserved. */
        uint64_t throttle              : 1;  /**< [  6:  6](SR/W) Throttle throughput. For diagnostic use only. If set, limit translations to one every four
                                                                 cycles, to insure OCLA debug FIFOs will not overrun.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's. */
        uint64_t reserved_7            : 1;
        uint64_t walkers               : 6;  /**< [ 13:  8](SR/W) Number of walkers. The number of page table walkers that may
                                                                 simultaneously be executing, minus one.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's.
                                                                 For diagnostic use only. */
        uint64_t force_clks_active     : 1;  /**< [ 14: 14](SR/W) Forces the conditional clocks to be always on. For diagnostic use only. */
        uint64_t pg_cmb                : 2;  /**< [ 16: 15](SRO) Reserved. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_diag_ctl_s cn88xxp1; */
    struct bdk_smmux_diag_ctl_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t pg_cmb                : 2;  /**< [ 16: 15](SR/W) Page combining.
                                                                 0x0 = Transactions into the TLB that miss that are to the same 4 KB page as an
                                                                 already outstanding miss are combined into a single page table walk.
                                                                 0x1 = Transactions into the TLB that miss that are to the same 64 KB page as an
                                                                 already outstanding miss are combined into a single page table walk.  This will
                                                                 improve performance, but must only be used when 64 KB is the smallest granule
                                                                 size used across all contexts in the SMMU (all SMMU()_CB()_TCR[TG0,TG1] = 0x3).
                                                                 0x2 = Every transaction into the TLB that misses will require a page table
                                                                 walk. For diagnostic use only.
                                                                 0x3 = Reserved. */
        uint64_t force_clks_active     : 1;  /**< [ 14: 14](SR/W) Forces the conditional clocks to be always on. For diagnostic use only. */
        uint64_t walkers               : 6;  /**< [ 13:  8](SR/W) Number of walkers. The number of page table walkers that may
                                                                 simultaneously be executing, minus one.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's.
                                                                 For diagnostic use only. */
        uint64_t reserved_7            : 1;
        uint64_t throttle              : 1;  /**< [  6:  6](SR/W) Throttle throughput. For diagnostic use only. If set, limit translations to one every four
                                                                 cycles, to insure OCLA debug FIFOs will not overrun.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's. */
        uint64_t dis_bcstr             : 1;  /**< [  5:  5](SR/W) Reserved. */
        uint64_t dis_wcs1              : 2;  /**< [  4:  3](SR/W) Disables hitting in the walk cache for stage 1 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint64_t dis_wcs2              : 2;  /**< [  2:  1](SR/W) Disables hitting in the walk cache for stage 2 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint64_t dis_tlb               : 1;  /**< [  0:  0](SR/W) Disables hitting in the TLB. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dis_tlb               : 1;  /**< [  0:  0](SR/W) Disables hitting in the TLB. For diagnostic use only. */
        uint64_t dis_wcs2              : 2;  /**< [  2:  1](SR/W) Disables hitting in the walk cache for stage 2 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint64_t dis_wcs1              : 2;  /**< [  4:  3](SR/W) Disables hitting in the walk cache for stage 1 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint64_t dis_bcstr             : 1;  /**< [  5:  5](SR/W) Reserved. */
        uint64_t throttle              : 1;  /**< [  6:  6](SR/W) Throttle throughput. For diagnostic use only. If set, limit translations to one every four
                                                                 cycles, to insure OCLA debug FIFOs will not overrun.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's. */
        uint64_t reserved_7            : 1;
        uint64_t walkers               : 6;  /**< [ 13:  8](SR/W) Number of walkers. The number of page table walkers that may
                                                                 simultaneously be executing, minus one.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's.
                                                                 For diagnostic use only. */
        uint64_t force_clks_active     : 1;  /**< [ 14: 14](SR/W) Forces the conditional clocks to be always on. For diagnostic use only. */
        uint64_t pg_cmb                : 2;  /**< [ 16: 15](SR/W) Page combining.
                                                                 0x0 = Transactions into the TLB that miss that are to the same 4 KB page as an
                                                                 already outstanding miss are combined into a single page table walk.
                                                                 0x1 = Transactions into the TLB that miss that are to the same 64 KB page as an
                                                                 already outstanding miss are combined into a single page table walk.  This will
                                                                 improve performance, but must only be used when 64 KB is the smallest granule
                                                                 size used across all contexts in the SMMU (all SMMU()_CB()_TCR[TG0,TG1] = 0x3).
                                                                 0x2 = Every transaction into the TLB that misses will require a page table
                                                                 walk. For diagnostic use only.
                                                                 0x3 = Reserved. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_smmux_diag_ctl_cn81xx cn83xx; */
    /* struct bdk_smmux_diag_ctl_cn81xx cn88xxp2; */
};
typedef union bdk_smmux_diag_ctl bdk_smmux_diag_ctl_t;

static inline uint64_t BDK_SMMUX_DIAG_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_DIAG_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000020030ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000020030ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000020030ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_DIAG_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_DIAG_CTL(a) bdk_smmux_diag_ctl_t
#define bustype_BDK_SMMUX_DIAG_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_DIAG_CTL(a) "SMMUX_DIAG_CTL"
#define device_bar_BDK_SMMUX_DIAG_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_DIAG_CTL(a) (a)
#define arguments_BDK_SMMUX_DIAG_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_ecc_ctl_0
 *
 * SMMU Secure ECC Control Register
 */
union bdk_smmux_ecc_ctl_0
{
    uint64_t u;
    struct bdk_smmux_ecc_ctl_0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_21_63        : 43;
        uint64_t ram_cdis              : 21; /**< [ 20:  0](SR/W) RAM ECC correction disable. Each bit corresponds to a different RAM.
                                                                 Internal:
                                                                 Bits
                                                                 do not match SMMU()_ERR_INT[RAM_SBE].
                                                                 \<20\> = WCTL.
                                                                 \<19\> = TCTL.
                                                                 \<18\> = XL_MFIFO.
                                                                 \<17\> = MSIX.
                                                                 \<16\> = CONTEXT_IDR.
                                                                 \<15\> = CB_FRSYNRA.
                                                                 \<14\> = CB_IPAFAR.
                                                                 \<13\> = CB_FSYNR0.
                                                                 \<12\> = CB_FAR.
                                                                 \<11\> = S2CR.
                                                                 \<10\> = CB_ACTLR.
                                                                 \<9\>  = CB_TCR2.
                                                                 \<8\>  = SSDR.
                                                                 \<7\>  = SCTLR.
                                                                 \<6\>  = CB_MAIR0.
                                                                 \<5\>  = CB_MAIR1.
                                                                 \<4\>  = CBAR.
                                                                 \<3\>  = CBA2R.
                                                                 \<2\>  = CB_TTBR0.
                                                                 \<1\>  = CB_TTBR1.
                                                                 \<0\>  = CB_TCR. */
#else /* Word 0 - Little Endian */
        uint64_t ram_cdis              : 21; /**< [ 20:  0](SR/W) RAM ECC correction disable. Each bit corresponds to a different RAM.
                                                                 Internal:
                                                                 Bits
                                                                 do not match SMMU()_ERR_INT[RAM_SBE].
                                                                 \<20\> = WCTL.
                                                                 \<19\> = TCTL.
                                                                 \<18\> = XL_MFIFO.
                                                                 \<17\> = MSIX.
                                                                 \<16\> = CONTEXT_IDR.
                                                                 \<15\> = CB_FRSYNRA.
                                                                 \<14\> = CB_IPAFAR.
                                                                 \<13\> = CB_FSYNR0.
                                                                 \<12\> = CB_FAR.
                                                                 \<11\> = S2CR.
                                                                 \<10\> = CB_ACTLR.
                                                                 \<9\>  = CB_TCR2.
                                                                 \<8\>  = SSDR.
                                                                 \<7\>  = SCTLR.
                                                                 \<6\>  = CB_MAIR0.
                                                                 \<5\>  = CB_MAIR1.
                                                                 \<4\>  = CBAR.
                                                                 \<3\>  = CBA2R.
                                                                 \<2\>  = CB_TTBR0.
                                                                 \<1\>  = CB_TTBR1.
                                                                 \<0\>  = CB_TCR. */
        uint64_t reserved_21_63        : 43;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_ecc_ctl_0_s cn; */
};
typedef union bdk_smmux_ecc_ctl_0 bdk_smmux_ecc_ctl_0_t;

static inline uint64_t BDK_SMMUX_ECC_CTL_0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_ECC_CTL_0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000200f0ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000200f0ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000200f0ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_ECC_CTL_0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_ECC_CTL_0(a) bdk_smmux_ecc_ctl_0_t
#define bustype_BDK_SMMUX_ECC_CTL_0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_ECC_CTL_0(a) "SMMUX_ECC_CTL_0"
#define device_bar_BDK_SMMUX_ECC_CTL_0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_ECC_CTL_0(a) (a)
#define arguments_BDK_SMMUX_ECC_CTL_0(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_ecc_ctl_1
 *
 * SMMU Secure ECC Control Register
 */
union bdk_smmux_ecc_ctl_1
{
    uint64_t u;
    struct bdk_smmux_ecc_ctl_1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_flip1             : 21; /**< [ 52: 32](SR/W) Flip syndrome bits on write. Flip syndrome bit \<1\> on writes to the corresponding ram to
                                                                 test single-bit or double-bit error handling.

                                                                 Internal:
                                                                 Bits enumerated by
                                                                 SMMU()_ECC_CTL_0[RAM_CDIS]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_flip0             : 21; /**< [ 20:  0](SR/W) Flip syndrome bits on write. Flip syndrome bit \<0\> on writes to the corresponding ram to
                                                                 test single-bit or double-bit error handling.

                                                                 Internal:
                                                                 Bits enumerated by
                                                                 SMMU()_ECC_CTL_0[RAM_CDIS]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_flip0             : 21; /**< [ 20:  0](SR/W) Flip syndrome bits on write. Flip syndrome bit \<0\> on writes to the corresponding ram to
                                                                 test single-bit or double-bit error handling.

                                                                 Internal:
                                                                 Bits enumerated by
                                                                 SMMU()_ECC_CTL_0[RAM_CDIS]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_flip1             : 21; /**< [ 52: 32](SR/W) Flip syndrome bits on write. Flip syndrome bit \<1\> on writes to the corresponding ram to
                                                                 test single-bit or double-bit error handling.

                                                                 Internal:
                                                                 Bits enumerated by
                                                                 SMMU()_ECC_CTL_0[RAM_CDIS]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_ecc_ctl_1_s cn; */
};
typedef union bdk_smmux_ecc_ctl_1 bdk_smmux_ecc_ctl_1_t;

static inline uint64_t BDK_SMMUX_ECC_CTL_1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_ECC_CTL_1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000200f8ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000200f8ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000200f8ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_ECC_CTL_1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_ECC_CTL_1(a) bdk_smmux_ecc_ctl_1_t
#define bustype_BDK_SMMUX_ECC_CTL_1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_ECC_CTL_1(a) "SMMUX_ECC_CTL_1"
#define device_bar_BDK_SMMUX_ECC_CTL_1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_ECC_CTL_1(a) (a)
#define arguments_BDK_SMMUX_ECC_CTL_1(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_err_ena_w1c
 *
 * SMMU ECC Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_smmux_err_ena_w1c
{
    uint64_t u;
    struct bdk_smmux_err_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Reads or clears enable for SMMU(0..3)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Reads or clears enable for SMMU(0..3)_ERR_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Reads or clears enable for SMMU(0..3)_ERR_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Reads or clears enable for SMMU(0..3)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_smmux_err_ena_w1c_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Reads or clears enable for SMMU(0)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Reads or clears enable for SMMU(0)_ERR_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Reads or clears enable for SMMU(0)_ERR_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Reads or clears enable for SMMU(0)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_smmux_err_ena_w1c_s cn88xx; */
    struct bdk_smmux_err_ena_w1c_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Reads or clears enable for SMMU(0..1)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Reads or clears enable for SMMU(0..1)_ERR_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Reads or clears enable for SMMU(0..1)_ERR_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Reads or clears enable for SMMU(0..1)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_smmux_err_ena_w1c bdk_smmux_err_ena_w1c_t;

static inline uint64_t BDK_SMMUX_ERR_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_ERR_ENA_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000200a0ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000200a0ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000200a0ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_ERR_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_ERR_ENA_W1C(a) bdk_smmux_err_ena_w1c_t
#define bustype_BDK_SMMUX_ERR_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_ERR_ENA_W1C(a) "SMMUX_ERR_ENA_W1C"
#define device_bar_BDK_SMMUX_ERR_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_ERR_ENA_W1C(a) (a)
#define arguments_BDK_SMMUX_ERR_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_err_ena_w1s
 *
 * SMMU ECC Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_smmux_err_ena_w1s
{
    uint64_t u;
    struct bdk_smmux_err_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets enable for SMMU(0..3)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets enable for SMMU(0..3)_ERR_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets enable for SMMU(0..3)_ERR_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets enable for SMMU(0..3)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_smmux_err_ena_w1s_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets enable for SMMU(0)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets enable for SMMU(0)_ERR_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets enable for SMMU(0)_ERR_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets enable for SMMU(0)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_smmux_err_ena_w1s_s cn88xx; */
    struct bdk_smmux_err_ena_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets enable for SMMU(0..1)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets enable for SMMU(0..1)_ERR_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets enable for SMMU(0..1)_ERR_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets enable for SMMU(0..1)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_smmux_err_ena_w1s bdk_smmux_err_ena_w1s_t;

static inline uint64_t BDK_SMMUX_ERR_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_ERR_ENA_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000200b0ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000200b0ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000200b0ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_ERR_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_ERR_ENA_W1S(a) bdk_smmux_err_ena_w1s_t
#define bustype_BDK_SMMUX_ERR_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_ERR_ENA_W1S(a) "SMMUX_ERR_ENA_W1S"
#define device_bar_BDK_SMMUX_ERR_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_ERR_ENA_W1S(a) (a)
#define arguments_BDK_SMMUX_ERR_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_err_int
 *
 * SMMU Error Interrupt Register
 * Internal:
 * This register contains ECC and other miscellaneous error bits.  INTERNAL: Errors are only
 * reported in the lowest number SMMU in each SMMU that shares an IOB.
 */
union bdk_smmux_err_int
{
    uint64_t u;
    struct bdk_smmux_err_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Double-bit error detected in internal RAM.
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Single-bit error detected in internal RAM.
                                                                 \<20\> = TCTL.
                                                                 \<19\> = WCTL.
                                                                 \<18\> = XL_MFIFO.
                                                                 \<17\> = MSIX.
                                                                 \<16\> = CONTEXT_IDR.
                                                                 \<15\> = CB_FRSYNRA.
                                                                 \<14\> = CB_IPAFAR.
                                                                 \<13\> = CB_FSYNR0.
                                                                 \<12\> = CB_FAR.
                                                                 \<11\> = S2CR.
                                                                 \<10\> = CB_ACTLR.
                                                                 \<9\>  = CB_TCR2.
                                                                 \<8\>  = SSDR.
                                                                 \<7\>  = SCTLR.
                                                                 \<6\>  = CB_MAIR0.
                                                                 \<5\>  = CB_MAIR1.
                                                                 \<4\>  = CBAR.
                                                                 \<3\>  = CBA2R.
                                                                 \<2\>  = CB_TTBR0.
                                                                 \<1\>  = CB_TTBR1.
                                                                 \<0\>  = CB_TCR. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1C/H) Single-bit error detected in internal RAM.
                                                                 \<20\> = TCTL.
                                                                 \<19\> = WCTL.
                                                                 \<18\> = XL_MFIFO.
                                                                 \<17\> = MSIX.
                                                                 \<16\> = CONTEXT_IDR.
                                                                 \<15\> = CB_FRSYNRA.
                                                                 \<14\> = CB_IPAFAR.
                                                                 \<13\> = CB_FSYNR0.
                                                                 \<12\> = CB_FAR.
                                                                 \<11\> = S2CR.
                                                                 \<10\> = CB_ACTLR.
                                                                 \<9\>  = CB_TCR2.
                                                                 \<8\>  = SSDR.
                                                                 \<7\>  = SCTLR.
                                                                 \<6\>  = CB_MAIR0.
                                                                 \<5\>  = CB_MAIR1.
                                                                 \<4\>  = CBAR.
                                                                 \<3\>  = CBA2R.
                                                                 \<2\>  = CB_TTBR0.
                                                                 \<1\>  = CB_TTBR1.
                                                                 \<0\>  = CB_TCR. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1C/H) Double-bit error detected in internal RAM.
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_err_int_s cn; */
};
typedef union bdk_smmux_err_int bdk_smmux_err_int_t;

static inline uint64_t BDK_SMMUX_ERR_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_ERR_INT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000020080ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000020080ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000020080ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_ERR_INT", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_ERR_INT(a) bdk_smmux_err_int_t
#define bustype_BDK_SMMUX_ERR_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_ERR_INT(a) "SMMUX_ERR_INT"
#define device_bar_BDK_SMMUX_ERR_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_ERR_INT(a) (a)
#define arguments_BDK_SMMUX_ERR_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_err_int_w1s
 *
 * SMMU ECC Interrupt Set Register
 * This register sets interrupt bits.
 * Internal:
 * INTERNAL: Errors are only reported in the lowest number SMMU in each SMMU that shares an IOB.
 */
union bdk_smmux_err_int_w1s
{
    uint64_t u;
    struct bdk_smmux_err_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets SMMU(0..3)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets SMMU(0..3)_ERR_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets SMMU(0..3)_ERR_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets SMMU(0..3)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_smmux_err_int_w1s_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets SMMU(0)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets SMMU(0)_ERR_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets SMMU(0)_ERR_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets SMMU(0)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_smmux_err_int_w1s_s cn88xx; */
    struct bdk_smmux_err_int_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets SMMU(0..1)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets SMMU(0..1)_ERR_INT[RAM_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t ram_sbe               : 21; /**< [ 20:  0](R/W1S/H) Reads or sets SMMU(0..1)_ERR_INT[RAM_SBE]. */
        uint64_t reserved_21_31        : 11;
        uint64_t ram_dbe               : 21; /**< [ 52: 32](R/W1S/H) Reads or sets SMMU(0..1)_ERR_INT[RAM_DBE].
                                                                 Internal:
                                                                 Bits enumerated by [RAM_SBE]. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_smmux_err_int_w1s bdk_smmux_err_int_w1s_t;

static inline uint64_t BDK_SMMUX_ERR_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_ERR_INT_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000020090ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000020090ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000020090ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_ERR_INT_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_ERR_INT_W1S(a) bdk_smmux_err_int_w1s_t
#define bustype_BDK_SMMUX_ERR_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_ERR_INT_W1S(a) "SMMUX_ERR_INT_W1S"
#define device_bar_BDK_SMMUX_ERR_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_ERR_INT_W1S(a) (a)
#define arguments_BDK_SMMUX_ERR_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_eventq_base
 *
 * SMMU Event Queue Base Register
 */
union bdk_smmux_eventq_base
{
    uint64_t u;
    struct bdk_smmux_eventq_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t wa                    : 1;  /**< [ 62: 62](R/W) SMMU(0)_S_EVENTQ_BASE[WA] */
        uint64_t reserved_52_61        : 10;
        uint64_t addr                  : 47; /**< [ 51:  5](R/W) SMMU(0)_S_EVENTQ_BASE[ADDR] */
        uint64_t log2size              : 5;  /**< [  4:  0](R/W) SMMU(0)_S_EVENTQ_BASE[LOG2SIZE] */
#else /* Word 0 - Little Endian */
        uint64_t log2size              : 5;  /**< [  4:  0](R/W) SMMU(0)_S_EVENTQ_BASE[LOG2SIZE] */
        uint64_t addr                  : 47; /**< [ 51:  5](R/W) SMMU(0)_S_EVENTQ_BASE[ADDR] */
        uint64_t reserved_52_61        : 10;
        uint64_t wa                    : 1;  /**< [ 62: 62](R/W) SMMU(0)_S_EVENTQ_BASE[WA] */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_eventq_base_s cn; */
};
typedef union bdk_smmux_eventq_base bdk_smmux_eventq_base_t;

static inline uint64_t BDK_SMMUX_EVENTQ_BASE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_EVENTQ_BASE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000000a0ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_EVENTQ_BASE", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_EVENTQ_BASE(a) bdk_smmux_eventq_base_t
#define bustype_BDK_SMMUX_EVENTQ_BASE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_EVENTQ_BASE(a) "SMMUX_EVENTQ_BASE"
#define device_bar_BDK_SMMUX_EVENTQ_BASE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_EVENTQ_BASE(a) (a)
#define arguments_BDK_SMMUX_EVENTQ_BASE(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_eventq_cons
 *
 * SMMU Event Queue Consumer Register
 */
union bdk_smmux_eventq_cons
{
    uint32_t u;
    struct bdk_smmux_eventq_cons_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ovackflg              : 1;  /**< [ 31: 31](R/W) SMMU(0)_S_EVENTQ_CONS[OVACKFLG] */
        uint32_t reserved_20_30        : 11;
        uint32_t rd                    : 20; /**< [ 19:  0](R/W) SMMU(0)_S_EVENTQ_CONS[RD] */
#else /* Word 0 - Little Endian */
        uint32_t rd                    : 20; /**< [ 19:  0](R/W) SMMU(0)_S_EVENTQ_CONS[RD] */
        uint32_t reserved_20_30        : 11;
        uint32_t ovackflg              : 1;  /**< [ 31: 31](R/W) SMMU(0)_S_EVENTQ_CONS[OVACKFLG] */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_eventq_cons_s cn; */
};
typedef union bdk_smmux_eventq_cons bdk_smmux_eventq_cons_t;

static inline uint64_t BDK_SMMUX_EVENTQ_CONS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_EVENTQ_CONS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000100acll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_EVENTQ_CONS", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_EVENTQ_CONS(a) bdk_smmux_eventq_cons_t
#define bustype_BDK_SMMUX_EVENTQ_CONS(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_EVENTQ_CONS(a) "SMMUX_EVENTQ_CONS"
#define device_bar_BDK_SMMUX_EVENTQ_CONS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_EVENTQ_CONS(a) (a)
#define arguments_BDK_SMMUX_EVENTQ_CONS(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_eventq_irq_cfg0
 *
 * SMMU Event Queue Interrupt Configuration 0 Register
 */
union bdk_smmux_eventq_irq_cfg0
{
    uint64_t u;
    struct bdk_smmux_eventq_irq_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t addr                  : 50; /**< [ 51:  2](R/W) SMMU(0)_S_GERROR_IRQ_CFG0[ADDR]
                                                                 Internal:
                                                                 High-order bits of the [ADDR] above the system physical address size (see
                                                                 SMMU()_IDR5[OAS]) are 0.

                                                                 If [ADDR]=0x0, allows a wired IRQ, if implemented, to be used (when
                                                                 SMMU()_(S_)IRQ_CTRL[GERROR_IRQEN]=1) instead of an MSI. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 50; /**< [ 51:  2](R/W) SMMU(0)_S_GERROR_IRQ_CFG0[ADDR]
                                                                 Internal:
                                                                 High-order bits of the [ADDR] above the system physical address size (see
                                                                 SMMU()_IDR5[OAS]) are 0.

                                                                 If [ADDR]=0x0, allows a wired IRQ, if implemented, to be used (when
                                                                 SMMU()_(S_)IRQ_CTRL[GERROR_IRQEN]=1) instead of an MSI. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_eventq_irq_cfg0_s cn; */
};
typedef union bdk_smmux_eventq_irq_cfg0 bdk_smmux_eventq_irq_cfg0_t;

static inline uint64_t BDK_SMMUX_EVENTQ_IRQ_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_EVENTQ_IRQ_CFG0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000000b0ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_EVENTQ_IRQ_CFG0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_EVENTQ_IRQ_CFG0(a) bdk_smmux_eventq_irq_cfg0_t
#define bustype_BDK_SMMUX_EVENTQ_IRQ_CFG0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_EVENTQ_IRQ_CFG0(a) "SMMUX_EVENTQ_IRQ_CFG0"
#define device_bar_BDK_SMMUX_EVENTQ_IRQ_CFG0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_EVENTQ_IRQ_CFG0(a) (a)
#define arguments_BDK_SMMUX_EVENTQ_IRQ_CFG0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_eventq_irq_cfg1
 *
 * SMMU Event Queue Interrupt Configuration 1 Register
 */
union bdk_smmux_eventq_irq_cfg1
{
    uint32_t u;
    struct bdk_smmux_eventq_irq_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) SMMU(0)_S_GERROR_IRQ_CFG1[DATA] */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) SMMU(0)_S_GERROR_IRQ_CFG1[DATA] */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_eventq_irq_cfg1_s cn; */
};
typedef union bdk_smmux_eventq_irq_cfg1 bdk_smmux_eventq_irq_cfg1_t;

static inline uint64_t BDK_SMMUX_EVENTQ_IRQ_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_EVENTQ_IRQ_CFG1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000000b8ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_EVENTQ_IRQ_CFG1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_EVENTQ_IRQ_CFG1(a) bdk_smmux_eventq_irq_cfg1_t
#define bustype_BDK_SMMUX_EVENTQ_IRQ_CFG1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_EVENTQ_IRQ_CFG1(a) "SMMUX_EVENTQ_IRQ_CFG1"
#define device_bar_BDK_SMMUX_EVENTQ_IRQ_CFG1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_EVENTQ_IRQ_CFG1(a) (a)
#define arguments_BDK_SMMUX_EVENTQ_IRQ_CFG1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_eventq_irq_cfg2
 *
 * SMMU Event Queue Interrupt Configuration 2 Register
 */
union bdk_smmux_eventq_irq_cfg2
{
    uint32_t u;
    struct bdk_smmux_eventq_irq_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t sh                    : 2;  /**< [  5:  4](R/W) SMMU(0)_S_GERROR_IRQ_CFG2[SH] */
        uint32_t memattr               : 4;  /**< [  3:  0](R/W) SMMU(0)_S_GERROR_IRQ_CFG2[MEMATTR] */
#else /* Word 0 - Little Endian */
        uint32_t memattr               : 4;  /**< [  3:  0](R/W) SMMU(0)_S_GERROR_IRQ_CFG2[MEMATTR] */
        uint32_t sh                    : 2;  /**< [  5:  4](R/W) SMMU(0)_S_GERROR_IRQ_CFG2[SH] */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_eventq_irq_cfg2_s cn; */
};
typedef union bdk_smmux_eventq_irq_cfg2 bdk_smmux_eventq_irq_cfg2_t;

static inline uint64_t BDK_SMMUX_EVENTQ_IRQ_CFG2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_EVENTQ_IRQ_CFG2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000000bcll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_EVENTQ_IRQ_CFG2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_EVENTQ_IRQ_CFG2(a) bdk_smmux_eventq_irq_cfg2_t
#define bustype_BDK_SMMUX_EVENTQ_IRQ_CFG2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_EVENTQ_IRQ_CFG2(a) "SMMUX_EVENTQ_IRQ_CFG2"
#define device_bar_BDK_SMMUX_EVENTQ_IRQ_CFG2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_EVENTQ_IRQ_CFG2(a) (a)
#define arguments_BDK_SMMUX_EVENTQ_IRQ_CFG2(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_eventq_prod
 *
 * SMMU Event Queue Producer Register
 */
union bdk_smmux_eventq_prod
{
    uint32_t u;
    struct bdk_smmux_eventq_prod_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ovflg                 : 1;  /**< [ 31: 31](R/W/H) SMMU(0)_S_EVENTQ_PROD[OVFLG] */
        uint32_t reserved_20_30        : 11;
        uint32_t wr                    : 20; /**< [ 19:  0](R/W/H) SMMU(0)_S_EVENTQ_PROD[WR] */
#else /* Word 0 - Little Endian */
        uint32_t wr                    : 20; /**< [ 19:  0](R/W/H) SMMU(0)_S_EVENTQ_PROD[WR] */
        uint32_t reserved_20_30        : 11;
        uint32_t ovflg                 : 1;  /**< [ 31: 31](R/W/H) SMMU(0)_S_EVENTQ_PROD[OVFLG] */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_eventq_prod_s cn; */
};
typedef union bdk_smmux_eventq_prod bdk_smmux_eventq_prod_t;

static inline uint64_t BDK_SMMUX_EVENTQ_PROD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_EVENTQ_PROD(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000100a8ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_EVENTQ_PROD", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_EVENTQ_PROD(a) bdk_smmux_eventq_prod_t
#define bustype_BDK_SMMUX_EVENTQ_PROD(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_EVENTQ_PROD(a) "SMMUX_EVENTQ_PROD"
#define device_bar_BDK_SMMUX_EVENTQ_PROD(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_EVENTQ_PROD(a) (a)
#define arguments_BDK_SMMUX_EVENTQ_PROD(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_gatos_addr
 *
 * SMMU GATOS Address Register
 */
union bdk_smmux_gatos_addr
{
    uint64_t u;
    struct bdk_smmux_gatos_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 52; /**< [ 63: 12](R/W) SMMU(0)_S_GATOS_ADDR[ADDR] */
        uint64_t rtype                 : 2;  /**< [ 11: 10](R/W) SMMU(0)_S_GATOS_ADDR[RTYPE] */
        uint64_t pnu                   : 1;  /**< [  9:  9](R/W) SMMU(0)_S_GATOS_ADDR[PNU] */
        uint64_t rnw                   : 1;  /**< [  8:  8](R/W) SMMU(0)_S_GATOS_ADDR[RNW] */
        uint64_t ind                   : 1;  /**< [  7:  7](R/W) SMMU(0)_S_GATOS_ADDR[IND] */
        uint64_t httui                 : 1;  /**< [  6:  6](R/W) SMMU(0)_S_GATOS_ADDR[HTTUI] */
        uint64_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_5          : 6;
        uint64_t httui                 : 1;  /**< [  6:  6](R/W) SMMU(0)_S_GATOS_ADDR[HTTUI] */
        uint64_t ind                   : 1;  /**< [  7:  7](R/W) SMMU(0)_S_GATOS_ADDR[IND] */
        uint64_t rnw                   : 1;  /**< [  8:  8](R/W) SMMU(0)_S_GATOS_ADDR[RNW] */
        uint64_t pnu                   : 1;  /**< [  9:  9](R/W) SMMU(0)_S_GATOS_ADDR[PNU] */
        uint64_t rtype                 : 2;  /**< [ 11: 10](R/W) SMMU(0)_S_GATOS_ADDR[RTYPE] */
        uint64_t addr                  : 52; /**< [ 63: 12](R/W) SMMU(0)_S_GATOS_ADDR[ADDR] */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gatos_addr_s cn; */
};
typedef union bdk_smmux_gatos_addr bdk_smmux_gatos_addr_t;

static inline uint64_t BDK_SMMUX_GATOS_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GATOS_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000110ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GATOS_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GATOS_ADDR(a) bdk_smmux_gatos_addr_t
#define bustype_BDK_SMMUX_GATOS_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_GATOS_ADDR(a) "SMMUX_GATOS_ADDR"
#define device_bar_BDK_SMMUX_GATOS_ADDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GATOS_ADDR(a) (a)
#define arguments_BDK_SMMUX_GATOS_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_gatos_ctrl
 *
 * SMMU GATOS Control Register
 */
union bdk_smmux_gatos_ctrl
{
    uint32_t u;
    struct bdk_smmux_gatos_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t run                   : 1;  /**< [  0:  0](R/W1S/H) SMMU(0)_S_GATOS_CTRL[RUN] */
#else /* Word 0 - Little Endian */
        uint32_t run                   : 1;  /**< [  0:  0](R/W1S/H) SMMU(0)_S_GATOS_CTRL[RUN] */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gatos_ctrl_s cn; */
};
typedef union bdk_smmux_gatos_ctrl bdk_smmux_gatos_ctrl_t;

static inline uint64_t BDK_SMMUX_GATOS_CTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GATOS_CTRL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000100ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GATOS_CTRL", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GATOS_CTRL(a) bdk_smmux_gatos_ctrl_t
#define bustype_BDK_SMMUX_GATOS_CTRL(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_GATOS_CTRL(a) "SMMUX_GATOS_CTRL"
#define device_bar_BDK_SMMUX_GATOS_CTRL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GATOS_CTRL(a) (a)
#define arguments_BDK_SMMUX_GATOS_CTRL(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_gatos_par
 *
 * SMMU GATOS Address Register
 */
union bdk_smmux_gatos_par
{
    uint64_t u;
    struct bdk_smmux_gatos_par_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t par                   : 64; /**< [ 63:  0](RO/H) SMMU(0)_S_GATOS_PAR[PAR] */
#else /* Word 0 - Little Endian */
        uint64_t par                   : 64; /**< [ 63:  0](RO/H) SMMU(0)_S_GATOS_PAR[PAR] */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gatos_par_s cn; */
};
typedef union bdk_smmux_gatos_par bdk_smmux_gatos_par_t;

static inline uint64_t BDK_SMMUX_GATOS_PAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GATOS_PAR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000118ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GATOS_PAR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GATOS_PAR(a) bdk_smmux_gatos_par_t
#define bustype_BDK_SMMUX_GATOS_PAR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_GATOS_PAR(a) "SMMUX_GATOS_PAR"
#define device_bar_BDK_SMMUX_GATOS_PAR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GATOS_PAR(a) (a)
#define arguments_BDK_SMMUX_GATOS_PAR(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_gatos_sid
 *
 * SMMU GATOS SID Register
 */
union bdk_smmux_gatos_sid
{
    uint64_t u;
    struct bdk_smmux_gatos_sid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ssid_valid            : 1;  /**< [ 52: 52](R/W) SubstreamID valid.
                                                                 Internal:
                                                                 If SMMU()_IDR1[SSIDSIZE]=0, this field is RES0. */
        uint64_t substreamid           : 20; /**< [ 51: 32](R/W) SubstreamID of request.
                                                                 If SMMU()_IDR1[SSIDSIZE]\<20, bits \<51:32+SMMU()_IDR1[SSIDSIZE]\> are RES0. */
        uint64_t reserved_24_31        : 8;
        uint64_t streamid              : 24; /**< [ 23:  0](R/W) StreamID of request.
                                                                 This is written with the StreamID (used to locate translations/CDs) of the request
                                                                 later submitted
                                                                 to SMMU()_GATOS_ADDR.
                                                                 If SMMU()_IDR1[SIDSIZE]\<32, bits \<31:SMMU()_IDR1[SIDSIZE]\> are RES0. */
#else /* Word 0 - Little Endian */
        uint64_t streamid              : 24; /**< [ 23:  0](R/W) StreamID of request.
                                                                 This is written with the StreamID (used to locate translations/CDs) of the request
                                                                 later submitted
                                                                 to SMMU()_GATOS_ADDR.
                                                                 If SMMU()_IDR1[SIDSIZE]\<32, bits \<31:SMMU()_IDR1[SIDSIZE]\> are RES0. */
        uint64_t reserved_24_31        : 8;
        uint64_t substreamid           : 20; /**< [ 51: 32](R/W) SubstreamID of request.
                                                                 If SMMU()_IDR1[SSIDSIZE]\<20, bits \<51:32+SMMU()_IDR1[SSIDSIZE]\> are RES0. */
        uint64_t ssid_valid            : 1;  /**< [ 52: 52](R/W) SubstreamID valid.
                                                                 Internal:
                                                                 If SMMU()_IDR1[SSIDSIZE]=0, this field is RES0. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gatos_sid_s cn; */
};
typedef union bdk_smmux_gatos_sid bdk_smmux_gatos_sid_t;

static inline uint64_t BDK_SMMUX_GATOS_SID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GATOS_SID(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000108ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GATOS_SID", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GATOS_SID(a) bdk_smmux_gatos_sid_t
#define bustype_BDK_SMMUX_GATOS_SID(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_GATOS_SID(a) "SMMUX_GATOS_SID"
#define device_bar_BDK_SMMUX_GATOS_SID(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GATOS_SID(a) (a)
#define arguments_BDK_SMMUX_GATOS_SID(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_gbpa
 *
 * SMMU Global Bypass Attribute Register
 */
union bdk_smmux_gbpa
{
    uint32_t u;
    struct bdk_smmux_gbpa_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t update                : 1;  /**< [ 31: 31](RAZ) Update/completion flag. */
        uint32_t reserved_21_30        : 10;
        uint32_t abrt                  : 1;  /**< [ 20: 20](R/W) Abort all incoming transactions.
                                                                 0 = Do not abort; transactions bypass the SMMU with attributes given by other
                                                                 fields in this register.
                                                                 1 = Abort all incoming transactions.

                                                                 The SMMU makes no record of transactions aborted using this flag. */
        uint32_t instcfg               : 2;  /**< [ 19: 18](R/W) Instruction/data override. Only affects reads; writes are always output as data.
                                                                 0x0 = Use incoming.
                                                                 0x1 = Reserved (behaves as 0x0).
                                                                 0x2 = Data.
                                                                 0x3 = Instruction. */
        uint32_t privcfg               : 2;  /**< [ 17: 16](R/W) User/privileged override.
                                                                 0x0 = Use incoming.
                                                                 0x1 = Reserved (behaves as 0x0).
                                                                 0x2 = Unprivileged.
                                                                 0x3 = Privileged. */
        uint32_t reserved_14_15        : 2;
        uint32_t shcfg                 : 2;  /**< [ 13: 12](R/W) Shareability override.
                                                                 0x0 = NSH.
                                                                 0x1 = Use incoming.
                                                                 0x2 = OSH.
                                                                 0x3 = ISH. */
        uint32_t alloccfg              : 4;  /**< [ 11:  8](R/W) 0xxx = Use incoming RA/WA/TR allocation/transient hints.
                                                                 1RWT = Hints are overridden to given values:
                                                                 * Read allocate = R.
                                                                 * Write allocate = W.
                                                                 * Transient = T.

                                                                 When overridden by this field, for each of RA/WA and TR, both inner- and outer-
                                                                 hints are set to the same value. Since it is not architecturally possible to
                                                                 express hints for types that are device or normal-noncacheable, this field has
                                                                 no effect on memory types that are not normal-WB or normal-WT, whether such
                                                                 types are provided with an upstream transaction or overridden using
                                                                 MTCFG/MemAttr. */
        uint32_t reserved_5_7          : 3;
        uint32_t mtcfg                 : 1;  /**< [  4:  4](R/W) Memory type override.
                                                                 0 = Use incoming memory type.
                                                                 1 = Override incoming memory type using MemAttr field. */
        uint32_t memattr               : 4;  /**< [  3:  0](R/W) Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
#else /* Word 0 - Little Endian */
        uint32_t memattr               : 4;  /**< [  3:  0](R/W) Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
        uint32_t mtcfg                 : 1;  /**< [  4:  4](R/W) Memory type override.
                                                                 0 = Use incoming memory type.
                                                                 1 = Override incoming memory type using MemAttr field. */
        uint32_t reserved_5_7          : 3;
        uint32_t alloccfg              : 4;  /**< [ 11:  8](R/W) 0xxx = Use incoming RA/WA/TR allocation/transient hints.
                                                                 1RWT = Hints are overridden to given values:
                                                                 * Read allocate = R.
                                                                 * Write allocate = W.
                                                                 * Transient = T.

                                                                 When overridden by this field, for each of RA/WA and TR, both inner- and outer-
                                                                 hints are set to the same value. Since it is not architecturally possible to
                                                                 express hints for types that are device or normal-noncacheable, this field has
                                                                 no effect on memory types that are not normal-WB or normal-WT, whether such
                                                                 types are provided with an upstream transaction or overridden using
                                                                 MTCFG/MemAttr. */
        uint32_t shcfg                 : 2;  /**< [ 13: 12](R/W) Shareability override.
                                                                 0x0 = NSH.
                                                                 0x1 = Use incoming.
                                                                 0x2 = OSH.
                                                                 0x3 = ISH. */
        uint32_t reserved_14_15        : 2;
        uint32_t privcfg               : 2;  /**< [ 17: 16](R/W) User/privileged override.
                                                                 0x0 = Use incoming.
                                                                 0x1 = Reserved (behaves as 0x0).
                                                                 0x2 = Unprivileged.
                                                                 0x3 = Privileged. */
        uint32_t instcfg               : 2;  /**< [ 19: 18](R/W) Instruction/data override. Only affects reads; writes are always output as data.
                                                                 0x0 = Use incoming.
                                                                 0x1 = Reserved (behaves as 0x0).
                                                                 0x2 = Data.
                                                                 0x3 = Instruction. */
        uint32_t abrt                  : 1;  /**< [ 20: 20](R/W) Abort all incoming transactions.
                                                                 0 = Do not abort; transactions bypass the SMMU with attributes given by other
                                                                 fields in this register.
                                                                 1 = Abort all incoming transactions.

                                                                 The SMMU makes no record of transactions aborted using this flag. */
        uint32_t reserved_21_30        : 10;
        uint32_t update                : 1;  /**< [ 31: 31](RAZ) Update/completion flag. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gbpa_s cn; */
};
typedef union bdk_smmux_gbpa bdk_smmux_gbpa_t;

static inline uint64_t BDK_SMMUX_GBPA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GBPA(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000044ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GBPA", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GBPA(a) bdk_smmux_gbpa_t
#define bustype_BDK_SMMUX_GBPA(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_GBPA(a) "SMMUX_GBPA"
#define device_bar_BDK_SMMUX_GBPA(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GBPA(a) (a)
#define arguments_BDK_SMMUX_GBPA(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_gerror
 *
 * SMMU Global Error Register
 * This register, in conjunction with SMMU()_(S_)GERRORN, indicates whether global error
 * conditions exist.
 *
 * The SMMU toggles SMMU()_(S_)GERROR[x] when an error becomes active. Software is
 * expected to toggle SMMU()_(S_)GERRORN[x] in response, to acknowledge the error.
 *
 * The SMMU does not toggle a bit when an error is already active. An error is only
 * activated if it is in an inactive state (i.e. a prior error has been
 * acknowledged/de-activated).
 *
 * Software is not intended to trigger interrupts by arranging for SMMU()_GERRORN\<x\> to differ
 * from SMMU()_GERROR\<x\>.
 */
union bdk_smmux_gerror
{
    uint32_t u;
    struct bdk_smmux_gerror_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t sfm_err               : 1;  /**< [  8:  8](RAZ) The SMMU has entered service failure mode.

                                                                 * Traffic through the SMMU might be affected. Depending on the origin of the
                                                                 error, the SMMU might stop processing commands and recording events. The RAS
                                                                 registers describe the error.

                                                                 * Acknowledgement of this error via GERRORN does not clear this error, which is
                                                                 cleared in an implementation defined way.

                                                                 * SFM triggers both SMMU()_GERROR[SFM_ERR] and SMMU()_S_GERROR[SFM_ERR]. */
        uint32_t msi_gerror_abt_err    : 1;  /**< [  7:  7](RAZ) A GERROR MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t msi_priq_abt_err      : 1;  /**< [  6:  6](RAZ) A PRIQ MSI was terminated with abort. Activation of this error does not affect future
                                                                 MSIs.
                                                                 If SMMU()_IDR0[PRI]=0 or SMMU()_IDR0[MSI]=0, this field is RES0.

                                                                 Not implemented in CNXXXX. */
        uint32_t msi_eventq_abt_err    : 1;  /**< [  5:  5](RAZ) An EVENTQ MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs.
                                                                 If SMMU()_IDR0[MSI]=0, this field is RES0. */
        uint32_t msi_cmdq_abt_err      : 1;  /**< [  4:  4](RAZ) A CMD_SYNC MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs.
                                                                 If SMMU()_IDR0[MSI]=0, this field is RES0. */
        uint32_t priq_abt_err          : 1;  /**< [  3:  3](RAZ) A write to the PRI queue was terminated with abort and page request records might have
                                                                 been lost.
                                                                 If SMMU()_IDR0[PRI]=0, this field is RES0.

                                                                 Not implemented in CNXXXX. */
        uint32_t eventq_abt_err        : 1;  /**< [  2:  2](RO/H) A write to the event queue was terminated with abort and event records might have been lost. */
        uint32_t reserved_1            : 1;
        uint32_t cmdq_err              : 1;  /**< [  0:  0](RO/H) A command has been encountered that cannot be processed. SMMU()_CMDQ_CONS[ERRX] has
                                                                 been updated with a reason code and command processing has stopped.
                                                                 Commands are not processed while this error is active. */
#else /* Word 0 - Little Endian */
        uint32_t cmdq_err              : 1;  /**< [  0:  0](RO/H) A command has been encountered that cannot be processed. SMMU()_CMDQ_CONS[ERRX] has
                                                                 been updated with a reason code and command processing has stopped.
                                                                 Commands are not processed while this error is active. */
        uint32_t reserved_1            : 1;
        uint32_t eventq_abt_err        : 1;  /**< [  2:  2](RO/H) A write to the event queue was terminated with abort and event records might have been lost. */
        uint32_t priq_abt_err          : 1;  /**< [  3:  3](RAZ) A write to the PRI queue was terminated with abort and page request records might have
                                                                 been lost.
                                                                 If SMMU()_IDR0[PRI]=0, this field is RES0.

                                                                 Not implemented in CNXXXX. */
        uint32_t msi_cmdq_abt_err      : 1;  /**< [  4:  4](RAZ) A CMD_SYNC MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs.
                                                                 If SMMU()_IDR0[MSI]=0, this field is RES0. */
        uint32_t msi_eventq_abt_err    : 1;  /**< [  5:  5](RAZ) An EVENTQ MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs.
                                                                 If SMMU()_IDR0[MSI]=0, this field is RES0. */
        uint32_t msi_priq_abt_err      : 1;  /**< [  6:  6](RAZ) A PRIQ MSI was terminated with abort. Activation of this error does not affect future
                                                                 MSIs.
                                                                 If SMMU()_IDR0[PRI]=0 or SMMU()_IDR0[MSI]=0, this field is RES0.

                                                                 Not implemented in CNXXXX. */
        uint32_t msi_gerror_abt_err    : 1;  /**< [  7:  7](RAZ) A GERROR MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t sfm_err               : 1;  /**< [  8:  8](RAZ) The SMMU has entered service failure mode.

                                                                 * Traffic through the SMMU might be affected. Depending on the origin of the
                                                                 error, the SMMU might stop processing commands and recording events. The RAS
                                                                 registers describe the error.

                                                                 * Acknowledgement of this error via GERRORN does not clear this error, which is
                                                                 cleared in an implementation defined way.

                                                                 * SFM triggers both SMMU()_GERROR[SFM_ERR] and SMMU()_S_GERROR[SFM_ERR]. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gerror_s cn; */
};
typedef union bdk_smmux_gerror bdk_smmux_gerror_t;

static inline uint64_t BDK_SMMUX_GERROR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GERROR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000060ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GERROR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GERROR(a) bdk_smmux_gerror_t
#define bustype_BDK_SMMUX_GERROR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_GERROR(a) "SMMUX_GERROR"
#define device_bar_BDK_SMMUX_GERROR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GERROR(a) (a)
#define arguments_BDK_SMMUX_GERROR(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_gerror_irq_cfg0
 *
 * SMMU Global Error IRQ Configuration 0 Register
 * Registers SMMU()_S_GERROR_IRQ_CFG0/1/2 are guarded by the respective
 * SMMU()_S_IRQ_CTRL[GERROR_IRQEN] and must only be modified when
 * SMMU()_S_IRQ_CTRL[GERROR_IRQEN]=0.
 */
union bdk_smmux_gerror_irq_cfg0
{
    uint64_t u;
    struct bdk_smmux_gerror_irq_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t addr                  : 50; /**< [ 51:  2](R/W) SMMU(0)_S_GERROR_IRQ_CFG0[ADDR]
                                                                 Internal:
                                                                 High-order bits of the [ADDR] above the system physical address size (see
                                                                 SMMU()_IDR5[OAS]) are 0.

                                                                 If [ADDR]=0x0, allows a wired IRQ, if implemented, to be used (when
                                                                 SMMU()_(S_)IRQ_CTRL[GERROR_IRQEN]=1) instead of an MSI. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 50; /**< [ 51:  2](R/W) SMMU(0)_S_GERROR_IRQ_CFG0[ADDR]
                                                                 Internal:
                                                                 High-order bits of the [ADDR] above the system physical address size (see
                                                                 SMMU()_IDR5[OAS]) are 0.

                                                                 If [ADDR]=0x0, allows a wired IRQ, if implemented, to be used (when
                                                                 SMMU()_(S_)IRQ_CTRL[GERROR_IRQEN]=1) instead of an MSI. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gerror_irq_cfg0_s cn; */
};
typedef union bdk_smmux_gerror_irq_cfg0 bdk_smmux_gerror_irq_cfg0_t;

static inline uint64_t BDK_SMMUX_GERROR_IRQ_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GERROR_IRQ_CFG0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000068ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GERROR_IRQ_CFG0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GERROR_IRQ_CFG0(a) bdk_smmux_gerror_irq_cfg0_t
#define bustype_BDK_SMMUX_GERROR_IRQ_CFG0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_GERROR_IRQ_CFG0(a) "SMMUX_GERROR_IRQ_CFG0"
#define device_bar_BDK_SMMUX_GERROR_IRQ_CFG0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GERROR_IRQ_CFG0(a) (a)
#define arguments_BDK_SMMUX_GERROR_IRQ_CFG0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_gerror_irq_cfg1
 *
 * SMMU Global Error IRQ Configuration 1 Register
 */
union bdk_smmux_gerror_irq_cfg1
{
    uint32_t u;
    struct bdk_smmux_gerror_irq_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) SMMU(0)_S_GERROR_IRQ_CFG1[DATA] */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) SMMU(0)_S_GERROR_IRQ_CFG1[DATA] */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gerror_irq_cfg1_s cn; */
};
typedef union bdk_smmux_gerror_irq_cfg1 bdk_smmux_gerror_irq_cfg1_t;

static inline uint64_t BDK_SMMUX_GERROR_IRQ_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GERROR_IRQ_CFG1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000070ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GERROR_IRQ_CFG1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GERROR_IRQ_CFG1(a) bdk_smmux_gerror_irq_cfg1_t
#define bustype_BDK_SMMUX_GERROR_IRQ_CFG1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_GERROR_IRQ_CFG1(a) "SMMUX_GERROR_IRQ_CFG1"
#define device_bar_BDK_SMMUX_GERROR_IRQ_CFG1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GERROR_IRQ_CFG1(a) (a)
#define arguments_BDK_SMMUX_GERROR_IRQ_CFG1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_gerror_irq_cfg2
 *
 * SMMU Global Error IRQ Configuration 2 Register
 */
union bdk_smmux_gerror_irq_cfg2
{
    uint32_t u;
    struct bdk_smmux_gerror_irq_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t sh                    : 2;  /**< [  5:  4](R/W) SMMU(0)_S_GERROR_IRQ_CFG2[SH] */
        uint32_t memattr               : 4;  /**< [  3:  0](R/W) SMMU(0)_S_GERROR_IRQ_CFG2[MEMATTR] */
#else /* Word 0 - Little Endian */
        uint32_t memattr               : 4;  /**< [  3:  0](R/W) SMMU(0)_S_GERROR_IRQ_CFG2[MEMATTR] */
        uint32_t sh                    : 2;  /**< [  5:  4](R/W) SMMU(0)_S_GERROR_IRQ_CFG2[SH] */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gerror_irq_cfg2_s cn; */
};
typedef union bdk_smmux_gerror_irq_cfg2 bdk_smmux_gerror_irq_cfg2_t;

static inline uint64_t BDK_SMMUX_GERROR_IRQ_CFG2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GERROR_IRQ_CFG2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000074ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GERROR_IRQ_CFG2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GERROR_IRQ_CFG2(a) bdk_smmux_gerror_irq_cfg2_t
#define bustype_BDK_SMMUX_GERROR_IRQ_CFG2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_GERROR_IRQ_CFG2(a) "SMMUX_GERROR_IRQ_CFG2"
#define device_bar_BDK_SMMUX_GERROR_IRQ_CFG2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GERROR_IRQ_CFG2(a) (a)
#define arguments_BDK_SMMUX_GERROR_IRQ_CFG2(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_gerrorn
 *
 * SMMU Global Error Acknowledge Register
 * Same fields as SMMU()_GERROR.
 *
 * Software must not toggle fields in this register that correspond to errors that are
 * inactive.  It is constrained unpredictable whether or not an SMMU activates errors
 * if this is done.
 *
 * The SMMU does not alter fields in this register.
 *
 * Software might maintain an internal copy of the last value written to this register,
 * for comparison against values read from SMMU()_GERROR when probing for errors.
 */
union bdk_smmux_gerrorn
{
    uint32_t u;
    struct bdk_smmux_gerrorn_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t sfm_err               : 1;  /**< [  8:  8](R/W) The SMMU has entered service failure mode.
                                                                 * Traffic through the SMMU might be affected. Depending on the origin of the
                                                                 error, the SMMU might stop processing commands and recording events. The RAS
                                                                 registers describe the error.

                                                                 *  Acknowledgement of this error via GERRORN does not clear this error, which is cleared
                                                                 in an implementation defined way.

                                                                 *  SFM triggers both SMMU()_GERROR[SFM_ERR] and SMMU()_S_GERROR[SFM_ERR]. */
        uint32_t msi_gerror_abt_err    : 1;  /**< [  7:  7](R/W) A GERROR MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t msi_priq_abt_err      : 1;  /**< [  6:  6](RAZ) A PRIQ MSI was terminated with abort. Activation of this error does not affect future
                                                                 MSIs.
                                                                 If SMMU()_IDR0[PRI]=0 or SMMU()_IDR0[MSI]=0, this field is RES0.

                                                                 Not implemented in CNXXXX. */
        uint32_t msi_eventq_abt_err    : 1;  /**< [  5:  5](R/W) An EVENTQ MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs.
                                                                 If SMMU()_IDR0[MSI]=0, this field is RES0. */
        uint32_t msi_cmdq_abt_err      : 1;  /**< [  4:  4](R/W) A CMD_SYNC MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs.
                                                                 If SMMU()_IDR0[MSI]=0, this field is RES0. */
        uint32_t priq_abt_err          : 1;  /**< [  3:  3](RAZ) A write to the PRI queue was terminated with abort and page request records might have
                                                                 been lost.
                                                                 If SMMU()_IDR0[PRI]=0, this field is RES0.

                                                                 Not implemented in CNXXXX. */
        uint32_t eventq_abt_err        : 1;  /**< [  2:  2](R/W) A write to the event queue was terminated with abort and event records might have been lost. */
        uint32_t reserved_1            : 1;
        uint32_t cmdq_err              : 1;  /**< [  0:  0](R/W) A command has been encountered that cannot be processed. SMMU()_CMDQ_CONS[ERRX] has
                                                                 been updated with a reason code and command processing has stopped.
                                                                 Commands are not processed while this error is active. */
#else /* Word 0 - Little Endian */
        uint32_t cmdq_err              : 1;  /**< [  0:  0](R/W) A command has been encountered that cannot be processed. SMMU()_CMDQ_CONS[ERRX] has
                                                                 been updated with a reason code and command processing has stopped.
                                                                 Commands are not processed while this error is active. */
        uint32_t reserved_1            : 1;
        uint32_t eventq_abt_err        : 1;  /**< [  2:  2](R/W) A write to the event queue was terminated with abort and event records might have been lost. */
        uint32_t priq_abt_err          : 1;  /**< [  3:  3](RAZ) A write to the PRI queue was terminated with abort and page request records might have
                                                                 been lost.
                                                                 If SMMU()_IDR0[PRI]=0, this field is RES0.

                                                                 Not implemented in CNXXXX. */
        uint32_t msi_cmdq_abt_err      : 1;  /**< [  4:  4](R/W) A CMD_SYNC MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs.
                                                                 If SMMU()_IDR0[MSI]=0, this field is RES0. */
        uint32_t msi_eventq_abt_err    : 1;  /**< [  5:  5](R/W) An EVENTQ MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs.
                                                                 If SMMU()_IDR0[MSI]=0, this field is RES0. */
        uint32_t msi_priq_abt_err      : 1;  /**< [  6:  6](RAZ) A PRIQ MSI was terminated with abort. Activation of this error does not affect future
                                                                 MSIs.
                                                                 If SMMU()_IDR0[PRI]=0 or SMMU()_IDR0[MSI]=0, this field is RES0.

                                                                 Not implemented in CNXXXX. */
        uint32_t msi_gerror_abt_err    : 1;  /**< [  7:  7](R/W) A GERROR MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t sfm_err               : 1;  /**< [  8:  8](R/W) The SMMU has entered service failure mode.
                                                                 * Traffic through the SMMU might be affected. Depending on the origin of the
                                                                 error, the SMMU might stop processing commands and recording events. The RAS
                                                                 registers describe the error.

                                                                 *  Acknowledgement of this error via GERRORN does not clear this error, which is cleared
                                                                 in an implementation defined way.

                                                                 *  SFM triggers both SMMU()_GERROR[SFM_ERR] and SMMU()_S_GERROR[SFM_ERR]. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_gerrorn_s cn; */
};
typedef union bdk_smmux_gerrorn bdk_smmux_gerrorn_t;

static inline uint64_t BDK_SMMUX_GERRORN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_GERRORN(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000064ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_GERRORN", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_GERRORN(a) bdk_smmux_gerrorn_t
#define bustype_BDK_SMMUX_GERRORN(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_GERRORN(a) "SMMUX_GERRORN"
#define device_bar_BDK_SMMUX_GERRORN(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_GERRORN(a) (a)
#define arguments_BDK_SMMUX_GERRORN(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_idr0
 *
 * SMMU Identification 0 Register
 */
union bdk_smmux_idr0
{
    uint32_t u;
    struct bdk_smmux_idr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ses                   : 1;  /**< [ 31: 31](SRO) Security extensions support. */
        uint32_t s1ts                  : 1;  /**< [ 30: 30](RO) Stage 1 translation support. */
        uint32_t s2ts                  : 1;  /**< [ 29: 29](RO) Stage 2 translation support.
                                                                 0 = Stage 2 translations are not supported.
                                                                 1 = Stage 2 translations are supported.

                                                                 As stage 2 translation is not supported for secure client accesses, the value returned in
                                                                 this field relates to SMMU capabilities for nonsecure client accesses. */
        uint32_t reserved_0_28         : 29;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_28         : 29;
        uint32_t s2ts                  : 1;  /**< [ 29: 29](RO) Stage 2 translation support.
                                                                 0 = Stage 2 translations are not supported.
                                                                 1 = Stage 2 translations are supported.

                                                                 As stage 2 translation is not supported for secure client accesses, the value returned in
                                                                 this field relates to SMMU capabilities for nonsecure client accesses. */
        uint32_t s1ts                  : 1;  /**< [ 30: 30](RO) Stage 1 translation support. */
        uint32_t ses                   : 1;  /**< [ 31: 31](SRO) Security extensions support. */
#endif /* Word 0 - End */
    } s;
    struct bdk_smmux_idr0_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ses                   : 1;  /**< [ 31: 31](SRO) Security extensions support. */
        uint32_t s1ts                  : 1;  /**< [ 30: 30](RO) Stage 1 translation support. */
        uint32_t s2ts                  : 1;  /**< [ 29: 29](RO) Stage 2 translation support.
                                                                 0 = Stage 2 translations are not supported.
                                                                 1 = Stage 2 translations are supported.

                                                                 As stage 2 translation is not supported for secure client accesses, the value returned in
                                                                 this field relates to SMMU capabilities for nonsecure client accesses. */
        uint32_t nts                   : 1;  /**< [ 28: 28](RO) Nested translation support.
                                                                 As stage 2 (and therefore nested) translation is not supported for secure client accesses,
                                                                 the value returned in this field relates to SMMU capabilities for nonsecure client
                                                                 accesses. */
        uint32_t sms                   : 1;  /**< [ 27: 27](RO) Stream match support. */
        uint32_t atosns                : 1;  /**< [ 26: 26](RO) Address translations operation not supported.

                                                                 Address translation operations are deprecated in SMMUv2 and in CNXXXX not
                                                                 supported. */
        uint32_t ptfs                  : 2;  /**< [ 25: 24](RO) Page table format supported.
                                                                 0x0 = V7L and V7S supported.
                                                                 0x1 = V7L format supported.
                                                                 0x2 = Only the V8 format is supported.
                                                                 0x3 = Reserved.

                                                                 In CNXXXX V8 only. */
        uint32_t numirpt               : 8;  /**< [ 23: 16](RO) Number of implemented context fault interrupts. Always 0x1 in ARMv8. */
        uint32_t exsmrgs               : 1;  /**< [ 15: 15](RAZ) Extended stream matching extension supported. */
        uint32_t cttw                  : 1;  /**< [ 14: 14](RO) Coherent translation table walk supported. */
        uint32_t btm                   : 1;  /**< [ 13: 13](RO) Broadcast TLB maintenance supported. */
        uint32_t numsidb               : 4;  /**< [ 12:  9](RO) Number of supported stream ID bits. */
        uint32_t exids                 : 1;  /**< [  8:  8](RO) Extended stream IDs are supported. */
        uint32_t numsmrg               : 8;  /**< [  7:  0](RO/H) Number of supported stream mapping registers groups. Access to this field by nonsecure
                                                                 software gives the value configured in SMMU()_SCR1[NSNUMSMRGO]. */
#else /* Word 0 - Little Endian */
        uint32_t numsmrg               : 8;  /**< [  7:  0](RO/H) Number of supported stream mapping registers groups. Access to this field by nonsecure
                                                                 software gives the value configured in SMMU()_SCR1[NSNUMSMRGO]. */
        uint32_t exids                 : 1;  /**< [  8:  8](RO) Extended stream IDs are supported. */
        uint32_t numsidb               : 4;  /**< [ 12:  9](RO) Number of supported stream ID bits. */
        uint32_t btm                   : 1;  /**< [ 13: 13](RO) Broadcast TLB maintenance supported. */
        uint32_t cttw                  : 1;  /**< [ 14: 14](RO) Coherent translation table walk supported. */
        uint32_t exsmrgs               : 1;  /**< [ 15: 15](RAZ) Extended stream matching extension supported. */
        uint32_t numirpt               : 8;  /**< [ 23: 16](RO) Number of implemented context fault interrupts. Always 0x1 in ARMv8. */
        uint32_t ptfs                  : 2;  /**< [ 25: 24](RO) Page table format supported.
                                                                 0x0 = V7L and V7S supported.
                                                                 0x1 = V7L format supported.
                                                                 0x2 = Only the V8 format is supported.
                                                                 0x3 = Reserved.

                                                                 In CNXXXX V8 only. */
        uint32_t atosns                : 1;  /**< [ 26: 26](RO) Address translations operation not supported.

                                                                 Address translation operations are deprecated in SMMUv2 and in CNXXXX not
                                                                 supported. */
        uint32_t sms                   : 1;  /**< [ 27: 27](RO) Stream match support. */
        uint32_t nts                   : 1;  /**< [ 28: 28](RO) Nested translation support.
                                                                 As stage 2 (and therefore nested) translation is not supported for secure client accesses,
                                                                 the value returned in this field relates to SMMU capabilities for nonsecure client
                                                                 accesses. */
        uint32_t s2ts                  : 1;  /**< [ 29: 29](RO) Stage 2 translation support.
                                                                 0 = Stage 2 translations are not supported.
                                                                 1 = Stage 2 translations are supported.

                                                                 As stage 2 translation is not supported for secure client accesses, the value returned in
                                                                 this field relates to SMMU capabilities for nonsecure client accesses. */
        uint32_t s1ts                  : 1;  /**< [ 30: 30](RO) Stage 1 translation support. */
        uint32_t ses                   : 1;  /**< [ 31: 31](SRO) Security extensions support. */
#endif /* Word 0 - End */
    } cn8;
    struct bdk_smmux_idr0_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t st_level              : 2;  /**< [ 28: 27](RO) Multilevel stream table support.
                                                                 0x0 = Linear stream table supported.
                                                                 0x1 = Two-level stream table supported in addition to linear stream table.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved. */
        uint32_t term_model            : 1;  /**< [ 26: 26](RO) Termination model behavior.

                                                                 0 = SMMU_CD_S[A] determines Abort or RAZ/WI behavior of a terminated transaction. The
                                                                 act of terminating a transaction may be configured using SMMU_CD_S[A] to successfully
                                                                 complete the transaction (RAZ/WI) or abort the transaction/return error.

                                                                 1 = Terminating a transaction with RAZ/WI behavior is not supported,
                                                                 SMMU_CD_S[A] must be one. This means that a terminated transaction will always be
                                                                 aborted/error returned. */
        uint32_t stall_model           : 2;  /**< [ 25: 24](RO) Stalling fault model support.
                                                                     0x0 = Stall and terminate models supported.
                                                                     0x1 = Stall is not supported (all faults terminate transaction); SMMU_STE_S[S2S]/CD[S]
                                                                     must be zero CMD_RESUME and CMD_STALL_TERM are not available.
                                                                     0x2 = Stall is forced (all faults eligible to stall cause stall);
                                                                 SMMU_STE_S[S2S]/CD[S]
                                                                     must be one.
                                                                     0x3 = Reserved.

                                                                     SMMU_STE_S[S2S] must be in the states above only if stage 2 translation was
                                                                     enabled (as it is otherwise ignored).

                                                                     This field is related to SMMU()_S_IDR0[STALL_MODEL] and might be modified by
                                                                     SMMU()_S_CR0[NSSTALLD].

                                                                     An SMMU associated with a PCI system must not have [STALL_MODEL]=0x2. */
        uint32_t reserved_23           : 1;
        uint32_t ttendian              : 2;  /**< [ 22: 21](RO) Endianness support for translation table walks.
                                                                 0x0 = Mixed-endian: SMMU_CD_S[ENDI] and SMMU_STE_S[S2ENDI] may select either endian.
                                                                 0x1 = Reserved.
                                                                 0x2 = Little-endian: SMMU_CD_S[ENDI] and SMMU_STE_S[S2ENDI] must select little-endian.
                                                                 0x3 = Big-endian: SMMU_CD_S[ENDI] and SMMU_STE_S[S2ENDI] must select big-endian.

                                                                 Internal:
                                                                 It is strongly recommended that a general-purpose SMMU implementation supports mixed-
                                                                 endian translation table walks. */
        uint32_t vatos                 : 1;  /**< [ 20: 20](RO) Virtual ATOS page interface supported.
                                                                 ATOS must also be supported.
                                                                 If this is set, both stage 1 and stage 2 translation must also be supported: S1P and
                                                                 S2P must be set. */
        uint32_t cd2l                  : 1;  /**< [ 19: 19](RO) Two-level context descriptor table supported. */
        uint32_t vmid16                : 1;  /**< [ 18: 18](RO) 16-bit VMID supported.
                                                                 When 16-bit VMIDs are not supported, VMID\<15:8\> is RES0 in command parameters and must be
                                                                 zero in SMMU_STE_S[S2VMID].
                                                                 The value of this field is irrelevant to software unless SMMU()_IDR0[S2P] is set. */
        uint32_t vmw                   : 1;  /**< [ 17: 17](RO) VMID wildcard-matching supported for TLB invalidates.
                                                                 Must be zero when SMMU()_IDR0[S2P]=0 (VMID tagging is not supported unless stage 2 is
                                                                 implemented). */
        uint32_t pri                   : 1;  /**< [ 16: 16](RO) Page request interface supported.
                                                                 For CNXXXX, must be zero as no ATS supported.

                                                                 Internal:
                                                                 Must be zero when SMMU()_IDR0[ATS]=0.
                                                                 When zero, all SMMU()_PRI_* registers are reserved. */
        uint32_t atos                  : 1;  /**< [ 15: 15](RO) Address translation operations supported.
                                                                 When zero, VATOS=0 and all SMMU()_(S_)GATOS_* registers are reserved. */
        uint32_t sev                   : 1;  /**< [ 14: 14](RO) SMMU, and system, support generation of events to CPU.
                                                                 When set, WFE may be used on the CPU to wait for CMD_SYNC completion.
                                                                 This bit must reflect the ability of the system, and SMMU implementation, to convey
                                                                 events to all CPUs that are expected to run SMMU maintenance software. */
        uint32_t msi                   : 1;  /**< [ 13: 13](RO) Message signaled interrupts are supported.
                                                                 Internal:
                                                                 When 0, the implementation supports wired interrupt notifications only; MSI fields in
                                                                 SMMU()_EVENTQ_IRQ_CFG0/1/2, SMMU()_PRIQ_IRQ_CFG0/1/2 and SMMU()_GERROR_IRQ_CFG0/1/2 are RES0. */
        uint32_t asid16                : 1;  /**< [ 12: 12](RO) 16-bit ASID supported.
                                                                 When 16-bit ASIDs are not supported, ASID\<15:8\> is RES0 in command parameters and must be
                                                                 zero in SMMU_CD_S[ASID].

                                                                 Internal:
                                                                 The value of this field is irrelevant to software unless SMMU()_IDR0[S1P]=1. */
        uint32_t ns1ats                : 1;  /**< [ 11: 11](RO) stage 1-only ATS not supported.
                                                                 Must be zero when SMMU()_IDR0[ATS]=0 or SMMU()_IDR0[S1P]=0 or SMMU()_IDR0[S2P]=0.

                                                                 The value of this field is only relevant to software when ATS and both stages of
                                                                 translation are supported.

                                                                 When one, stage 1-only ATS set by SMMU_STE_S[EATS]=0x2 is not supported. See
                                                                 SMMU_STE_S[EATS]. */
        uint32_t ats                   : 1;  /**< [ 10: 10](RO) PCIe RC ATS supported by SMMU. An implementation's support for ATS and PRI
                                                                 influences interpretation of SMMU_STE_S[EATS], ATS/PRI-related commands and
                                                                 SMMU()_PRIQ_* registers. It does not guarantee that client devices and
                                                                 intermediate components (e.g. Root Complexes) also support ATS and this must be
                                                                 determined separately. */
        uint32_t hyp                   : 1;  /**< [  9:  9](RO) Hypervisor stage 1 contexts supported.
                                                                 This flag indicates whether TLB entries may be tagged as EL2/EL2-E2H  see
                                                                 SMMU_STE_S[STRW].
                                                                 Must be zero if [S1P]=0, i.e. if no general stage 1 support.
                                                                 Must be zero if [S2P]=0, i.e. if no general stage 2 support.

                                                                 Internal:
                                                                 Note: A stage 1-only implementation with Hyp would imply a set of devices only usable
                                                                 within the hypervisor and without direct assignment.
                                                                 Hyp/EL2 support is recommended if S1P=1 && S2P=1 (both stages are supported). */
        uint32_t dormhint              : 1;  /**< [  8:  8](RO) Dormant hint supported. When one, SMMU()_STATUSR[DORMANT] might read as one;
                                                                 otherwise when zero, DORMANT always reads as zero. */
        uint32_t httu                  : 2;  /**< [  7:  6](RO) Hardware translation table dirty/accessed flag updates supported.
                                                                 0x0 = No flag updates supported.
                                                                 0x1 = Access flag update supported.
                                                                 0x2 = Access and Dirty flag update supported.
                                                                 0x3 = Reserved.

                                                                 Internal:
                                                                 This field must reflect the ability of the system, and SMMU implementation, to
                                                                 support hardware update.

                                                                 HTTU is a feature of an SMMU implementation but the system design also bears
                                                                 upon whether HTTU can be supported; for instance, HTTU requires coherent atomic
                                                                 updates to translation table data which need to be supported by an external
                                                                 interconnect. An SMMU that internally supports HTTU but does not have requisite
                                                                 system support must mark HTTU as '0x0' in this field. */
        uint32_t btm                   : 1;  /**< [  5:  5](RO) Broadcast TLB maintenance. When one, SMMU and system support broadcast TLB
                                                                 maintenance. Software can rely on TLBIxxxIS instructions invalidating matching
                                                                 TLB entries on this SMMU.

                                                                 Internal:
                                                                 This bit must reflect the ability of the system, and SMMU implementation, to
                                                                 support broadcast maintenance. If either the SMMU or system/interconnect cannot
                                                                 fully support broadcast TLB maintenance, this bit must read as zero. */
        uint32_t cohacc                : 1;  /**< [  4:  4](RO) Coherent access supported to translations, structures and queues.
                                                                 When one, I/O-coherent access is supported for translation table walks, L1STE/STE/L1CD/CD
                                                                 fetches and command/event/PRI queue access and GERROR/CMD_SYNC/EVENTQ/PRIQ MSIs (if
                                                                 supported).

                                                                 Whether a specific access is performed in a cacheable shareable manner
                                                                 is dependent on the access type configured for access to structures, queues and
                                                                 translation table walks.

                                                                 Internal:
                                                                 This bit must reflect the ability of the system, and SMMU implementation, to
                                                                 support I/O-coherent access to memory shared coherently with the CPU. If either
                                                                 the SMMU or system/interconnect cannot fully support IO-coherent access to SMMU
                                                                 structures/queues/translations, this bit must read as zero.

                                                                 This bit only pertains to accesses made directly by the SMMU in response to internal
                                                                 operations. It does not indicate that transactions from client devices are also IO-
                                                                 coherent; this capability must be determined in a system-specific manner, e.g. using
                                                                 firmware descriptions.

                                                                 Note: For embedded implementations using preset tables or queues, this bit only
                                                                 pertains to accesses made outside of the preset structures. For example, if
                                                                 COHACC=1 and SMMU()_IDR1[TABLES_PRESET]=1 and SMMU()_IDR1[QUEUES_PRESET]=1, SMMU
                                                                 access to preset configuration tables and queues occurs in a non-IO-coherent
                                                                 manner but other accesses (translation table walk) are coherent with CPU caches. */
        uint32_t ttf                   : 2;  /**< [  3:  2](RO) Translation table formats supported at both stage 1 & 2:
                                                                  0x0 = Reserved.
                                                                  0x1 = AArch32 (LPAE).
                                                                  0x2 = AArch64.
                                                                  0x3 = AArch32 and AArch64. */
        uint32_t s1p                   : 1;  /**< [  1:  1](RO) Stage 1 translation supported (CtxTable etc.). */
        uint32_t s2p                   : 1;  /**< [  0:  0](RO) Stage 2 translation supported. */
#else /* Word 0 - Little Endian */
        uint32_t s2p                   : 1;  /**< [  0:  0](RO) Stage 2 translation supported. */
        uint32_t s1p                   : 1;  /**< [  1:  1](RO) Stage 1 translation supported (CtxTable etc.). */
        uint32_t ttf                   : 2;  /**< [  3:  2](RO) Translation table formats supported at both stage 1 & 2:
                                                                  0x0 = Reserved.
                                                                  0x1 = AArch32 (LPAE).
                                                                  0x2 = AArch64.
                                                                  0x3 = AArch32 and AArch64. */
        uint32_t cohacc                : 1;  /**< [  4:  4](RO) Coherent access supported to translations, structures and queues.
                                                                 When one, I/O-coherent access is supported for translation table walks, L1STE/STE/L1CD/CD
                                                                 fetches and command/event/PRI queue access and GERROR/CMD_SYNC/EVENTQ/PRIQ MSIs (if
                                                                 supported).

                                                                 Whether a specific access is performed in a cacheable shareable manner
                                                                 is dependent on the access type configured for access to structures, queues and
                                                                 translation table walks.

                                                                 Internal:
                                                                 This bit must reflect the ability of the system, and SMMU implementation, to
                                                                 support I/O-coherent access to memory shared coherently with the CPU. If either
                                                                 the SMMU or system/interconnect cannot fully support IO-coherent access to SMMU
                                                                 structures/queues/translations, this bit must read as zero.

                                                                 This bit only pertains to accesses made directly by the SMMU in response to internal
                                                                 operations. It does not indicate that transactions from client devices are also IO-
                                                                 coherent; this capability must be determined in a system-specific manner, e.g. using
                                                                 firmware descriptions.

                                                                 Note: For embedded implementations using preset tables or queues, this bit only
                                                                 pertains to accesses made outside of the preset structures. For example, if
                                                                 COHACC=1 and SMMU()_IDR1[TABLES_PRESET]=1 and SMMU()_IDR1[QUEUES_PRESET]=1, SMMU
                                                                 access to preset configuration tables and queues occurs in a non-IO-coherent
                                                                 manner but other accesses (translation table walk) are coherent with CPU caches. */
        uint32_t btm                   : 1;  /**< [  5:  5](RO) Broadcast TLB maintenance. When one, SMMU and system support broadcast TLB
                                                                 maintenance. Software can rely on TLBIxxxIS instructions invalidating matching
                                                                 TLB entries on this SMMU.

                                                                 Internal:
                                                                 This bit must reflect the ability of the system, and SMMU implementation, to
                                                                 support broadcast maintenance. If either the SMMU or system/interconnect cannot
                                                                 fully support broadcast TLB maintenance, this bit must read as zero. */
        uint32_t httu                  : 2;  /**< [  7:  6](RO) Hardware translation table dirty/accessed flag updates supported.
                                                                 0x0 = No flag updates supported.
                                                                 0x1 = Access flag update supported.
                                                                 0x2 = Access and Dirty flag update supported.
                                                                 0x3 = Reserved.

                                                                 Internal:
                                                                 This field must reflect the ability of the system, and SMMU implementation, to
                                                                 support hardware update.

                                                                 HTTU is a feature of an SMMU implementation but the system design also bears
                                                                 upon whether HTTU can be supported; for instance, HTTU requires coherent atomic
                                                                 updates to translation table data which need to be supported by an external
                                                                 interconnect. An SMMU that internally supports HTTU but does not have requisite
                                                                 system support must mark HTTU as '0x0' in this field. */
        uint32_t dormhint              : 1;  /**< [  8:  8](RO) Dormant hint supported. When one, SMMU()_STATUSR[DORMANT] might read as one;
                                                                 otherwise when zero, DORMANT always reads as zero. */
        uint32_t hyp                   : 1;  /**< [  9:  9](RO) Hypervisor stage 1 contexts supported.
                                                                 This flag indicates whether TLB entries may be tagged as EL2/EL2-E2H  see
                                                                 SMMU_STE_S[STRW].
                                                                 Must be zero if [S1P]=0, i.e. if no general stage 1 support.
                                                                 Must be zero if [S2P]=0, i.e. if no general stage 2 support.

                                                                 Internal:
                                                                 Note: A stage 1-only implementation with Hyp would imply a set of devices only usable
                                                                 within the hypervisor and without direct assignment.
                                                                 Hyp/EL2 support is recommended if S1P=1 && S2P=1 (both stages are supported). */
        uint32_t ats                   : 1;  /**< [ 10: 10](RO) PCIe RC ATS supported by SMMU. An implementation's support for ATS and PRI
                                                                 influences interpretation of SMMU_STE_S[EATS], ATS/PRI-related commands and
                                                                 SMMU()_PRIQ_* registers. It does not guarantee that client devices and
                                                                 intermediate components (e.g. Root Complexes) also support ATS and this must be
                                                                 determined separately. */
        uint32_t ns1ats                : 1;  /**< [ 11: 11](RO) stage 1-only ATS not supported.
                                                                 Must be zero when SMMU()_IDR0[ATS]=0 or SMMU()_IDR0[S1P]=0 or SMMU()_IDR0[S2P]=0.

                                                                 The value of this field is only relevant to software when ATS and both stages of
                                                                 translation are supported.

                                                                 When one, stage 1-only ATS set by SMMU_STE_S[EATS]=0x2 is not supported. See
                                                                 SMMU_STE_S[EATS]. */
        uint32_t asid16                : 1;  /**< [ 12: 12](RO) 16-bit ASID supported.
                                                                 When 16-bit ASIDs are not supported, ASID\<15:8\> is RES0 in command parameters and must be
                                                                 zero in SMMU_CD_S[ASID].

                                                                 Internal:
                                                                 The value of this field is irrelevant to software unless SMMU()_IDR0[S1P]=1. */
        uint32_t msi                   : 1;  /**< [ 13: 13](RO) Message signaled interrupts are supported.
                                                                 Internal:
                                                                 When 0, the implementation supports wired interrupt notifications only; MSI fields in
                                                                 SMMU()_EVENTQ_IRQ_CFG0/1/2, SMMU()_PRIQ_IRQ_CFG0/1/2 and SMMU()_GERROR_IRQ_CFG0/1/2 are RES0. */
        uint32_t sev                   : 1;  /**< [ 14: 14](RO) SMMU, and system, support generation of events to CPU.
                                                                 When set, WFE may be used on the CPU to wait for CMD_SYNC completion.
                                                                 This bit must reflect the ability of the system, and SMMU implementation, to convey
                                                                 events to all CPUs that are expected to run SMMU maintenance software. */
        uint32_t atos                  : 1;  /**< [ 15: 15](RO) Address translation operations supported.
                                                                 When zero, VATOS=0 and all SMMU()_(S_)GATOS_* registers are reserved. */
        uint32_t pri                   : 1;  /**< [ 16: 16](RO) Page request interface supported.
                                                                 For CNXXXX, must be zero as no ATS supported.

                                                                 Internal:
                                                                 Must be zero when SMMU()_IDR0[ATS]=0.
                                                                 When zero, all SMMU()_PRI_* registers are reserved. */
        uint32_t vmw                   : 1;  /**< [ 17: 17](RO) VMID wildcard-matching supported for TLB invalidates.
                                                                 Must be zero when SMMU()_IDR0[S2P]=0 (VMID tagging is not supported unless stage 2 is
                                                                 implemented). */
        uint32_t vmid16                : 1;  /**< [ 18: 18](RO) 16-bit VMID supported.
                                                                 When 16-bit VMIDs are not supported, VMID\<15:8\> is RES0 in command parameters and must be
                                                                 zero in SMMU_STE_S[S2VMID].
                                                                 The value of this field is irrelevant to software unless SMMU()_IDR0[S2P] is set. */
        uint32_t cd2l                  : 1;  /**< [ 19: 19](RO) Two-level context descriptor table supported. */
        uint32_t vatos                 : 1;  /**< [ 20: 20](RO) Virtual ATOS page interface supported.
                                                                 ATOS must also be supported.
                                                                 If this is set, both stage 1 and stage 2 translation must also be supported: S1P and
                                                                 S2P must be set. */
        uint32_t ttendian              : 2;  /**< [ 22: 21](RO) Endianness support for translation table walks.
                                                                 0x0 = Mixed-endian: SMMU_CD_S[ENDI] and SMMU_STE_S[S2ENDI] may select either endian.
                                                                 0x1 = Reserved.
                                                                 0x2 = Little-endian: SMMU_CD_S[ENDI] and SMMU_STE_S[S2ENDI] must select little-endian.
                                                                 0x3 = Big-endian: SMMU_CD_S[ENDI] and SMMU_STE_S[S2ENDI] must select big-endian.

                                                                 Internal:
                                                                 It is strongly recommended that a general-purpose SMMU implementation supports mixed-
                                                                 endian translation table walks. */
        uint32_t reserved_23           : 1;
        uint32_t stall_model           : 2;  /**< [ 25: 24](RO) Stalling fault model support.
                                                                     0x0 = Stall and terminate models supported.
                                                                     0x1 = Stall is not supported (all faults terminate transaction); SMMU_STE_S[S2S]/CD[S]
                                                                     must be zero CMD_RESUME and CMD_STALL_TERM are not available.
                                                                     0x2 = Stall is forced (all faults eligible to stall cause stall);
                                                                 SMMU_STE_S[S2S]/CD[S]
                                                                     must be one.
                                                                     0x3 = Reserved.

                                                                     SMMU_STE_S[S2S] must be in the states above only if stage 2 translation was
                                                                     enabled (as it is otherwise ignored).

                                                                     This field is related to SMMU()_S_IDR0[STALL_MODEL] and might be modified by
                                                                     SMMU()_S_CR0[NSSTALLD].

                                                                     An SMMU associated with a PCI system must not have [STALL_MODEL]=0x2. */
        uint32_t term_model            : 1;  /**< [ 26: 26](RO) Termination model behavior.

                                                                 0 = SMMU_CD_S[A] determines Abort or RAZ/WI behavior of a terminated transaction. The
                                                                 act of terminating a transaction may be configured using SMMU_CD_S[A] to successfully
                                                                 complete the transaction (RAZ/WI) or abort the transaction/return error.

                                                                 1 = Terminating a transaction with RAZ/WI behavior is not supported,
                                                                 SMMU_CD_S[A] must be one. This means that a terminated transaction will always be
                                                                 aborted/error returned. */
        uint32_t st_level              : 2;  /**< [ 28: 27](RO) Multilevel stream table support.
                                                                 0x0 = Linear stream table supported.
                                                                 0x1 = Two-level stream table supported in addition to linear stream table.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved. */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_smmux_idr0 bdk_smmux_idr0_t;

static inline uint64_t BDK_SMMUX_IDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IDR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000020ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000020ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000020ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000000ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IDR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IDR0(a) bdk_smmux_idr0_t
#define bustype_BDK_SMMUX_IDR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IDR0(a) "SMMUX_IDR0"
#define device_bar_BDK_SMMUX_IDR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IDR0(a) (a)
#define arguments_BDK_SMMUX_IDR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_idr1
 *
 * SMMU Identification 1 Register
 */
union bdk_smmux_idr1
{
    uint32_t u;
    struct bdk_smmux_idr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t pagesize              : 1;  /**< [ 31: 31](RO) Indicates the size of each page in the SMMU register map.
                                                                 0 = Each page consumes 4 Kbytes.
                                                                 1 = Each page consumes 64 Kbytes. */
        uint32_t reserved_28_30        : 3;
        uint32_t attr_types_ovr        : 1;  /**< [ 27: 27](RO) Incoming MemType, shareability, allocation/transient hints override.

                                                                 0 = Incoming attributes cannot be overridden before translation or by global
                                                                 bypass; effectively, STE and SMMU()_(S_)GBPA MTCFG/SHCFG/ALLOCCFG fields are fixed
                                                                 as use incoming.

                                                                 1 = Incoming attributes can be overridden. */
        uint32_t attr_perms_ovr        : 1;  /**< [ 26: 26](RO) Incoming Data/Inst, User/Privileged, NS override.

                                                                 0 = Incoming attributes cannot be overridden before translation or by global
                                                                 bypass; effectively, INSTCFG/PRIVCFG/NSCFG are fixed as use incoming.

                                                                 1 = Incoming attributes can be overridden. */
        uint32_t reserved_0_25         : 26;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_25         : 26;
        uint32_t attr_perms_ovr        : 1;  /**< [ 26: 26](RO) Incoming Data/Inst, User/Privileged, NS override.

                                                                 0 = Incoming attributes cannot be overridden before translation or by global
                                                                 bypass; effectively, INSTCFG/PRIVCFG/NSCFG are fixed as use incoming.

                                                                 1 = Incoming attributes can be overridden. */
        uint32_t attr_types_ovr        : 1;  /**< [ 27: 27](RO) Incoming MemType, shareability, allocation/transient hints override.

                                                                 0 = Incoming attributes cannot be overridden before translation or by global
                                                                 bypass; effectively, STE and SMMU()_(S_)GBPA MTCFG/SHCFG/ALLOCCFG fields are fixed
                                                                 as use incoming.

                                                                 1 = Incoming attributes can be overridden. */
        uint32_t reserved_28_30        : 3;
        uint32_t pagesize              : 1;  /**< [ 31: 31](RO) Indicates the size of each page in the SMMU register map.
                                                                 0 = Each page consumes 4 Kbytes.
                                                                 1 = Each page consumes 64 Kbytes. */
#endif /* Word 0 - End */
    } s;
    struct bdk_smmux_idr1_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t pagesize              : 1;  /**< [ 31: 31](RO) Indicates the size of each page in the SMMU register map.
                                                                 0 = Each page consumes 4 Kbytes.
                                                                 1 = Each page consumes 64 Kbytes. */
        uint32_t numpagendxb           : 3;  /**< [ 30: 28](RO) Indicates how many pagesize pages occupy the global address space or the translation
                                                                 context address space where the number of pages is equal to 2^(NUMPAGENDXB + 1). */
        uint32_t reserved_26_27        : 2;
        uint32_t hafdbs                : 2;  /**< [ 25: 24](RO) Hardware access flag and dirty bit management supported.
                                                                 0x0 = No support for hardware update of either Access flag or Dirty bit information.
                                                                 0x1 = Support for hardware update of Access flag, but no support for hardware update of
                                                                 Dirty bit information.
                                                                 0x2 = Reserved.
                                                                 0x3 = Support for hardware update of both Access flag and Dirty bit information.

                                                                 CNXXXX does not support hardware access and dirty management. */
        uint32_t nums2cb               : 8;  /**< [ 23: 16](RO) Number of stage 2 context banks. Indicates the number of translation context banks that
                                                                 only support the stage 2 translation format. */
        uint32_t smcd                  : 1;  /**< [ 15: 15](RO) Stream match conflict detection.
                                                                 0 = The detection of all stream match conflicts is not guaranteed.
                                                                 1 = The detection of all stream match conflicts is guaranteed.

                                                                 CNXXXX detects stream match conflicts. */
        uint32_t reserved_14           : 1;
        uint32_t ssdtp                 : 2;  /**< [ 13: 12](SRO) Security state determination table present.
                                                                 0x0 = The security state determination address space is UNK/WI.
                                                                 0x1 = The security state determination address space is populated for up to 15-bit
                                                                 streams.
                                                                 0x2 = Reserved.
                                                                 0x3 = The security state determination address space is populated for up to 16-bit
                                                                 streams.

                                                                 CNXXXX implements a 16-bit security state determination table. */
        uint32_t numssdndxb            : 4;  /**< [ 11:  8](SRO) Indicates the number of SSD index bits for indexing the security state determination table. */
        uint32_t numcb                 : 8;  /**< [  7:  0](RO/H) Indicates the total number of implemented translation context banks in the range 0-128.
                                                                 The value reported in [NUMCB] includes translation context banks that only support stage 2
                                                                 format. The number of translation context banks that support the stage 1 format is given
                                                                 by [NUMCB] - [NUMS2CB]. A read of this field by nonsecure software gives the value
                                                                 configured in SMMU()_SCR1[NSNUMCBO]. */
#else /* Word 0 - Little Endian */
        uint32_t numcb                 : 8;  /**< [  7:  0](RO/H) Indicates the total number of implemented translation context banks in the range 0-128.
                                                                 The value reported in [NUMCB] includes translation context banks that only support stage 2
                                                                 format. The number of translation context banks that support the stage 1 format is given
                                                                 by [NUMCB] - [NUMS2CB]. A read of this field by nonsecure software gives the value
                                                                 configured in SMMU()_SCR1[NSNUMCBO]. */
        uint32_t numssdndxb            : 4;  /**< [ 11:  8](SRO) Indicates the number of SSD index bits for indexing the security state determination table. */
        uint32_t ssdtp                 : 2;  /**< [ 13: 12](SRO) Security state determination table present.
                                                                 0x0 = The security state determination address space is UNK/WI.
                                                                 0x1 = The security state determination address space is populated for up to 15-bit
                                                                 streams.
                                                                 0x2 = Reserved.
                                                                 0x3 = The security state determination address space is populated for up to 16-bit
                                                                 streams.

                                                                 CNXXXX implements a 16-bit security state determination table. */
        uint32_t reserved_14           : 1;
        uint32_t smcd                  : 1;  /**< [ 15: 15](RO) Stream match conflict detection.
                                                                 0 = The detection of all stream match conflicts is not guaranteed.
                                                                 1 = The detection of all stream match conflicts is guaranteed.

                                                                 CNXXXX detects stream match conflicts. */
        uint32_t nums2cb               : 8;  /**< [ 23: 16](RO) Number of stage 2 context banks. Indicates the number of translation context banks that
                                                                 only support the stage 2 translation format. */
        uint32_t hafdbs                : 2;  /**< [ 25: 24](RO) Hardware access flag and dirty bit management supported.
                                                                 0x0 = No support for hardware update of either Access flag or Dirty bit information.
                                                                 0x1 = Support for hardware update of Access flag, but no support for hardware update of
                                                                 Dirty bit information.
                                                                 0x2 = Reserved.
                                                                 0x3 = Support for hardware update of both Access flag and Dirty bit information.

                                                                 CNXXXX does not support hardware access and dirty management. */
        uint32_t reserved_26_27        : 2;
        uint32_t numpagendxb           : 3;  /**< [ 30: 28](RO) Indicates how many pagesize pages occupy the global address space or the translation
                                                                 context address space where the number of pages is equal to 2^(NUMPAGENDXB + 1). */
        uint32_t pagesize              : 1;  /**< [ 31: 31](RO) Indicates the size of each page in the SMMU register map.
                                                                 0 = Each page consumes 4 Kbytes.
                                                                 1 = Each page consumes 64 Kbytes. */
#endif /* Word 0 - End */
    } cn8;
    struct bdk_smmux_idr1_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t tables_preset         : 1;  /**< [ 30: 30](RO) Table base addresses fixed.

                                                                 When set, the contents of the registers SMMU()_(S_)STRTAB_BASE and
                                                                 SMMU()_(S_)STRTAB_BASE_CFG are fixed and pre-set at initialization
                                                                 time. Software must use the addresses in these registers in order to access the
                                                                 tables, rather than allocating system memory and providing a pointer to the
                                                                 SMMU. Software must use an appropriate memory type for access to these
                                                                 addresses; the SMMU will not guarantee cache coherency, so software must use
                                                                 either non-cached access or cached access with software cache maintenance. See
                                                                 [REL]. */
        uint32_t queues_preset         : 1;  /**< [ 29: 29](RO) Queue base addresses fixed. As with [TABLES_PRESET]: when set, the contents of
                                                                 SMMU()_CMDQ_BASE, SMMU()_EVENTQ_BASE are fixed and pre-set at initialization time.

                                                                 Internal:
                                                                 (and optionally SMMU()_PRIQ_BASE, if present) */
        uint32_t rel                   : 1;  /**< [ 28: 28](RO) Relative base pointers. For embedded implementations, this flag indicates that a
                                                                 base register affected by [TABLES_PRESET] or [QUEUES_PRESET] being set to 1
                                                                 contains a preset address relative to the SMMU base address (register offset
                                                                 0). Otherwise, all addresses in SMMU registers are absolute physical
                                                                 addresses. Relative addresses are calculated using an addition of the unsigned
                                                                 ADDR field onto the SMMU base address. When [TABLES_PRESET]=0 &&
                                                                 [QUEUES_PRESET]=0, the REL value is zero; if base addresses are not fixed, they
                                                                 are always absolute addresses. */
        uint32_t attr_types_ovr        : 1;  /**< [ 27: 27](RO) Incoming MemType, shareability, allocation/transient hints override.

                                                                 0 = Incoming attributes cannot be overridden before translation or by global
                                                                 bypass; effectively, STE and SMMU()_(S_)GBPA MTCFG/SHCFG/ALLOCCFG fields are fixed
                                                                 as use incoming.

                                                                 1 = Incoming attributes can be overridden. */
        uint32_t attr_perms_ovr        : 1;  /**< [ 26: 26](RO) Incoming Data/Inst, User/Privileged, NS override.

                                                                 0 = Incoming attributes cannot be overridden before translation or by global
                                                                 bypass; effectively, INSTCFG/PRIVCFG/NSCFG are fixed as use incoming.

                                                                 1 = Incoming attributes can be overridden. */
        uint32_t cmdqs                 : 5;  /**< [ 25: 21](RO) Command queue maximum number of entries as log2(entries), max 19. The index
                                                                 register values include an extra bit for wrap, so a queue with 2 entries has
                                                                 indices of N bits but an index register containing (N+1) bits. */
        uint32_t eventqs               : 5;  /**< [ 20: 16](RO) Event queue maximum number of entries as log2(entries), max 19. */
        uint32_t priqs                 : 5;  /**< [ 15: 11](RO) PRIQ maximum number of entries as log2(entries), max 19. */
        uint32_t ssidsize              : 5;  /**< [ 10:  6](RO) Max bits of SubstreamID. Valid range 0 to 20 inclusive, 0 meaning no Substreams
                                                                 are supported. */
        uint32_t sidsize               : 6;  /**< [  5:  0](RO) Max bits of StreamID. This value is between 0 and 32 inclusive. This reflects
                                                                 the physical StreamID size, i.e. an SMMU cannot represent (or be presented with)
                                                                 StreamIDs greater than SIDSIZE.

                                                                 Internal:
                                                                 0x0 is a legal value; in this case, the SMMU supports one stream. */
#else /* Word 0 - Little Endian */
        uint32_t sidsize               : 6;  /**< [  5:  0](RO) Max bits of StreamID. This value is between 0 and 32 inclusive. This reflects
                                                                 the physical StreamID size, i.e. an SMMU cannot represent (or be presented with)
                                                                 StreamIDs greater than SIDSIZE.

                                                                 Internal:
                                                                 0x0 is a legal value; in this case, the SMMU supports one stream. */
        uint32_t ssidsize              : 5;  /**< [ 10:  6](RO) Max bits of SubstreamID. Valid range 0 to 20 inclusive, 0 meaning no Substreams
                                                                 are supported. */
        uint32_t priqs                 : 5;  /**< [ 15: 11](RO) PRIQ maximum number of entries as log2(entries), max 19. */
        uint32_t eventqs               : 5;  /**< [ 20: 16](RO) Event queue maximum number of entries as log2(entries), max 19. */
        uint32_t cmdqs                 : 5;  /**< [ 25: 21](RO) Command queue maximum number of entries as log2(entries), max 19. The index
                                                                 register values include an extra bit for wrap, so a queue with 2 entries has
                                                                 indices of N bits but an index register containing (N+1) bits. */
        uint32_t attr_perms_ovr        : 1;  /**< [ 26: 26](RO) Incoming Data/Inst, User/Privileged, NS override.

                                                                 0 = Incoming attributes cannot be overridden before translation or by global
                                                                 bypass; effectively, INSTCFG/PRIVCFG/NSCFG are fixed as use incoming.

                                                                 1 = Incoming attributes can be overridden. */
        uint32_t attr_types_ovr        : 1;  /**< [ 27: 27](RO) Incoming MemType, shareability, allocation/transient hints override.

                                                                 0 = Incoming attributes cannot be overridden before translation or by global
                                                                 bypass; effectively, STE and SMMU()_(S_)GBPA MTCFG/SHCFG/ALLOCCFG fields are fixed
                                                                 as use incoming.

                                                                 1 = Incoming attributes can be overridden. */
        uint32_t rel                   : 1;  /**< [ 28: 28](RO) Relative base pointers. For embedded implementations, this flag indicates that a
                                                                 base register affected by [TABLES_PRESET] or [QUEUES_PRESET] being set to 1
                                                                 contains a preset address relative to the SMMU base address (register offset
                                                                 0). Otherwise, all addresses in SMMU registers are absolute physical
                                                                 addresses. Relative addresses are calculated using an addition of the unsigned
                                                                 ADDR field onto the SMMU base address. When [TABLES_PRESET]=0 &&
                                                                 [QUEUES_PRESET]=0, the REL value is zero; if base addresses are not fixed, they
                                                                 are always absolute addresses. */
        uint32_t queues_preset         : 1;  /**< [ 29: 29](RO) Queue base addresses fixed. As with [TABLES_PRESET]: when set, the contents of
                                                                 SMMU()_CMDQ_BASE, SMMU()_EVENTQ_BASE are fixed and pre-set at initialization time.

                                                                 Internal:
                                                                 (and optionally SMMU()_PRIQ_BASE, if present) */
        uint32_t tables_preset         : 1;  /**< [ 30: 30](RO) Table base addresses fixed.

                                                                 When set, the contents of the registers SMMU()_(S_)STRTAB_BASE and
                                                                 SMMU()_(S_)STRTAB_BASE_CFG are fixed and pre-set at initialization
                                                                 time. Software must use the addresses in these registers in order to access the
                                                                 tables, rather than allocating system memory and providing a pointer to the
                                                                 SMMU. Software must use an appropriate memory type for access to these
                                                                 addresses; the SMMU will not guarantee cache coherency, so software must use
                                                                 either non-cached access or cached access with software cache maintenance. See
                                                                 [REL]. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_smmux_idr1 bdk_smmux_idr1_t;

static inline uint64_t BDK_SMMUX_IDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IDR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000024ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000024ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000024ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000004ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IDR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IDR1(a) bdk_smmux_idr1_t
#define bustype_BDK_SMMUX_IDR1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IDR1(a) "SMMUX_IDR1"
#define device_bar_BDK_SMMUX_IDR1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IDR1(a) (a)
#define arguments_BDK_SMMUX_IDR1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_idr2
 *
 * SMMU Identification 2 Register
 */
union bdk_smmux_idr2
{
    uint32_t u;
    struct bdk_smmux_idr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t dipans                : 1;  /**< [ 30: 30](RO) Privileged access never support.
                                                                 When set, indicates supports ARM v8.1 privileged access never.
                                                                 See SMMU()_S2CR()[PRIVCFG].

                                                                 Note unlike the processor architecture, DIPAN applies to both instruction and data
                                                                 transactions; thus to distinguish the two features then the SMMU feature is called DIPAN
                                                                 whilst the processor architecture version is called PAN. */
        uint32_t compindexs            : 1;  /**< [ 29: 29](RO) StreamID compressed indexing support. */
        uint32_t hads                  : 1;  /**< [ 28: 28](RO) Hierarchical attribute disable support.
                                                                 When set, indicates supports ARM v8.1 hierarchical attribute disables.
                                                                 See SMMU()_CB()_TCR2[HAD0]. */
        uint32_t e2hs                  : 1;  /**< [ 27: 27](RO) E2H context (E2HC) supported.
                                                                 When set, indicates supports ARM v8.1 virtual host extension contexts.
                                                                 See SMMU()_CBA2R()[E2HC]. */
        uint32_t exnumsmrg             : 11; /**< [ 26: 16](RO) For extended stream match extension, the number of extended stream match
                                                                 register groups supported.

                                                                 For CNXXXX, 0x0 as extended stream match extension is not supported. */
        uint32_t vmid16s               : 1;  /**< [ 15: 15](RO) When set, indicates that 16-bit VMIDs are supported (ARMv8 large system extensions). */
        uint32_t ptfsv8_64kb           : 1;  /**< [ 14: 14](RO) When set, indicates that ARMv8 page tables using 64kb page granule are supported. */
        uint32_t ptfsv8_16kb           : 1;  /**< [ 13: 13](RO) When set, indicates that ARMv8 page tables using 16kb page granule are supported. */
        uint32_t ptfsv8_4kb            : 1;  /**< [ 12: 12](RO) When set, indicates that ARMv8 page tables using 4kb page granule are supported. */
        uint32_t reserved_0_11         : 12;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_11         : 12;
        uint32_t ptfsv8_4kb            : 1;  /**< [ 12: 12](RO) When set, indicates that ARMv8 page tables using 4kb page granule are supported. */
        uint32_t ptfsv8_16kb           : 1;  /**< [ 13: 13](RO) When set, indicates that ARMv8 page tables using 16kb page granule are supported. */
        uint32_t ptfsv8_64kb           : 1;  /**< [ 14: 14](RO) When set, indicates that ARMv8 page tables using 64kb page granule are supported. */
        uint32_t vmid16s               : 1;  /**< [ 15: 15](RO) When set, indicates that 16-bit VMIDs are supported (ARMv8 large system extensions). */
        uint32_t exnumsmrg             : 11; /**< [ 26: 16](RO) For extended stream match extension, the number of extended stream match
                                                                 register groups supported.

                                                                 For CNXXXX, 0x0 as extended stream match extension is not supported. */
        uint32_t e2hs                  : 1;  /**< [ 27: 27](RO) E2H context (E2HC) supported.
                                                                 When set, indicates supports ARM v8.1 virtual host extension contexts.
                                                                 See SMMU()_CBA2R()[E2HC]. */
        uint32_t hads                  : 1;  /**< [ 28: 28](RO) Hierarchical attribute disable support.
                                                                 When set, indicates supports ARM v8.1 hierarchical attribute disables.
                                                                 See SMMU()_CB()_TCR2[HAD0]. */
        uint32_t compindexs            : 1;  /**< [ 29: 29](RO) StreamID compressed indexing support. */
        uint32_t dipans                : 1;  /**< [ 30: 30](RO) Privileged access never support.
                                                                 When set, indicates supports ARM v8.1 privileged access never.
                                                                 See SMMU()_S2CR()[PRIVCFG].

                                                                 Note unlike the processor architecture, DIPAN applies to both instruction and data
                                                                 transactions; thus to distinguish the two features then the SMMU feature is called DIPAN
                                                                 whilst the processor architecture version is called PAN. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    struct bdk_smmux_idr2_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t dipans                : 1;  /**< [ 30: 30](RO) Privileged access never support.
                                                                 When set, indicates supports ARM v8.1 privileged access never.
                                                                 See SMMU()_S2CR()[PRIVCFG].

                                                                 Note unlike the processor architecture, DIPAN applies to both instruction and data
                                                                 transactions; thus to distinguish the two features then the SMMU feature is called DIPAN
                                                                 whilst the processor architecture version is called PAN. */
        uint32_t compindexs            : 1;  /**< [ 29: 29](RO) StreamID compressed indexing support. */
        uint32_t hads                  : 1;  /**< [ 28: 28](RO) Hierarchical attribute disable support.
                                                                 When set, indicates supports ARM v8.1 hierarchical attribute disables.
                                                                 See SMMU()_CB()_TCR2[HAD0]. */
        uint32_t e2hs                  : 1;  /**< [ 27: 27](RO) E2H context (E2HC) supported.
                                                                 When set, indicates supports ARM v8.1 virtual host extension contexts.
                                                                 See SMMU()_CBA2R()[E2HC]. */
        uint32_t exnumsmrg             : 11; /**< [ 26: 16](RO) For extended stream match extension, the number of extended stream match
                                                                 register groups supported.

                                                                 For CNXXXX, 0x0 as extended stream match extension is not supported. */
        uint32_t vmid16s               : 1;  /**< [ 15: 15](RO) When set, indicates that 16-bit VMIDs are supported (ARMv8 large system extensions). */
        uint32_t ptfsv8_64kb           : 1;  /**< [ 14: 14](RO) When set, indicates that ARMv8 page tables using 64kb page granule are supported. */
        uint32_t ptfsv8_16kb           : 1;  /**< [ 13: 13](RO) When set, indicates that ARMv8 page tables using 16kb page granule are supported. */
        uint32_t ptfsv8_4kb            : 1;  /**< [ 12: 12](RO) When set, indicates that ARMv8 page tables using 4kb page granule are supported. */
        uint32_t ubs                   : 4;  /**< [ 11:  8](RO) Upstream bus size.  This field specifies the maximum width of any upstream address port
                                                                 used by client devices to perform address translations.
                                                                 0x5 = 48-bit + 1 sign bit. */
        uint32_t oas                   : 4;  /**< [  7:  4](RO) Output address size. The maximum PA size supported.
                                                                 0x5 = 48-bit. */
        uint32_t ias                   : 4;  /**< [  3:  0](RO) Intermediate address size. The maximum IPA size supported.
                                                                 0x5 = 48-bit. */
#else /* Word 0 - Little Endian */
        uint32_t ias                   : 4;  /**< [  3:  0](RO) Intermediate address size. The maximum IPA size supported.
                                                                 0x5 = 48-bit. */
        uint32_t oas                   : 4;  /**< [  7:  4](RO) Output address size. The maximum PA size supported.
                                                                 0x5 = 48-bit. */
        uint32_t ubs                   : 4;  /**< [ 11:  8](RO) Upstream bus size.  This field specifies the maximum width of any upstream address port
                                                                 used by client devices to perform address translations.
                                                                 0x5 = 48-bit + 1 sign bit. */
        uint32_t ptfsv8_4kb            : 1;  /**< [ 12: 12](RO) When set, indicates that ARMv8 page tables using 4kb page granule are supported. */
        uint32_t ptfsv8_16kb           : 1;  /**< [ 13: 13](RO) When set, indicates that ARMv8 page tables using 16kb page granule are supported. */
        uint32_t ptfsv8_64kb           : 1;  /**< [ 14: 14](RO) When set, indicates that ARMv8 page tables using 64kb page granule are supported. */
        uint32_t vmid16s               : 1;  /**< [ 15: 15](RO) When set, indicates that 16-bit VMIDs are supported (ARMv8 large system extensions). */
        uint32_t exnumsmrg             : 11; /**< [ 26: 16](RO) For extended stream match extension, the number of extended stream match
                                                                 register groups supported.

                                                                 For CNXXXX, 0x0 as extended stream match extension is not supported. */
        uint32_t e2hs                  : 1;  /**< [ 27: 27](RO) E2H context (E2HC) supported.
                                                                 When set, indicates supports ARM v8.1 virtual host extension contexts.
                                                                 See SMMU()_CBA2R()[E2HC]. */
        uint32_t hads                  : 1;  /**< [ 28: 28](RO) Hierarchical attribute disable support.
                                                                 When set, indicates supports ARM v8.1 hierarchical attribute disables.
                                                                 See SMMU()_CB()_TCR2[HAD0]. */
        uint32_t compindexs            : 1;  /**< [ 29: 29](RO) StreamID compressed indexing support. */
        uint32_t dipans                : 1;  /**< [ 30: 30](RO) Privileged access never support.
                                                                 When set, indicates supports ARM v8.1 privileged access never.
                                                                 See SMMU()_S2CR()[PRIVCFG].

                                                                 Note unlike the processor architecture, DIPAN applies to both instruction and data
                                                                 transactions; thus to distinguish the two features then the SMMU feature is called DIPAN
                                                                 whilst the processor architecture version is called PAN. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_smmux_idr2_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t ba_vatos              : 10; /**< [  9:  0](RO) VATOS page base address offset. If SMMU()_IDR0[VATOS]=0, no VATOS page is
                                                                 present and this value is zero. */
#else /* Word 0 - Little Endian */
        uint32_t ba_vatos              : 10; /**< [  9:  0](RO) VATOS page base address offset. If SMMU()_IDR0[VATOS]=0, no VATOS page is
                                                                 present and this value is zero. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_smmux_idr2 bdk_smmux_idr2_t;

static inline uint64_t BDK_SMMUX_IDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IDR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000028ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000028ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000028ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000008ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IDR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IDR2(a) bdk_smmux_idr2_t
#define bustype_BDK_SMMUX_IDR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IDR2(a) "SMMUX_IDR2"
#define device_bar_BDK_SMMUX_IDR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IDR2(a) (a)
#define arguments_BDK_SMMUX_IDR2(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_idr3
 *
 * SMMU Identification 3 Register
 */
union bdk_smmux_idr3
{
    uint32_t u;
    struct bdk_smmux_idr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_5_31         : 27;
        uint32_t xnx                   : 1;  /**< [  4:  4](RO) 0 = EL0/EL1 execute control distinction at stage 2 not supported.
                                                                 1 = EL0/EL1 execute control distinction at stage 2 supported for both AArch64 and
                                                                     AArch32 stage 2 translation tables. */
        uint32_t pbha                  : 1;  /**< [  3:  3](RO) 0 = Page-Based Hardware Attributes not supported.
                                                                   SMMU()_IDR3[HAD] determines whether Hierarchical Attribute Disables
                                                                   supported.
                                                                 1 = Page-Based Hardware Attributes are supported.
                                                                   SMMU()_IDR3[HAD] must be 1. */
        uint32_t had                   : 1;  /**< [  2:  2](RO) Hierarchical attribute disable presence.
                                                                 0 = No hierarchical attribute disable support; SMMU_CD_S[HAD0,HAD1] are ignored.
                                                                 1 = SMMU_CD_S[HAD0,HAD1] control hierarchical attribute disable. */
        uint32_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_1          : 2;
        uint32_t had                   : 1;  /**< [  2:  2](RO) Hierarchical attribute disable presence.
                                                                 0 = No hierarchical attribute disable support; SMMU_CD_S[HAD0,HAD1] are ignored.
                                                                 1 = SMMU_CD_S[HAD0,HAD1] control hierarchical attribute disable. */
        uint32_t pbha                  : 1;  /**< [  3:  3](RO) 0 = Page-Based Hardware Attributes not supported.
                                                                   SMMU()_IDR3[HAD] determines whether Hierarchical Attribute Disables
                                                                   supported.
                                                                 1 = Page-Based Hardware Attributes are supported.
                                                                   SMMU()_IDR3[HAD] must be 1. */
        uint32_t xnx                   : 1;  /**< [  4:  4](RO) 0 = EL0/EL1 execute control distinction at stage 2 not supported.
                                                                 1 = EL0/EL1 execute control distinction at stage 2 supported for both AArch64 and
                                                                     AArch32 stage 2 translation tables. */
        uint32_t reserved_5_31         : 27;
#endif /* Word 0 - End */
    } s;
    struct bdk_smmux_idr3_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_smmux_idr3_s cn9; */
};
typedef union bdk_smmux_idr3 bdk_smmux_idr3_t;

static inline uint64_t BDK_SMMUX_IDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IDR3(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x83000000002cll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x83000000002cll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x83000000002cll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x83000000000cll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IDR3", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IDR3(a) bdk_smmux_idr3_t
#define bustype_BDK_SMMUX_IDR3(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IDR3(a) "SMMUX_IDR3"
#define device_bar_BDK_SMMUX_IDR3(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IDR3(a) (a)
#define arguments_BDK_SMMUX_IDR3(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_idr4
 *
 * SMMU Identification 4 Register
 * The contents of this register are implementation-defined and can be used to identify
 * the presence of other implementation-defined register regions elsewhere in the
 * memory map.
 */
union bdk_smmux_idr4
{
    uint32_t u;
    struct bdk_smmux_idr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_idr4_s cn; */
};
typedef union bdk_smmux_idr4 bdk_smmux_idr4_t;

static inline uint64_t BDK_SMMUX_IDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IDR4(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000030ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000030ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000030ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000010ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IDR4", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IDR4(a) bdk_smmux_idr4_t
#define bustype_BDK_SMMUX_IDR4(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IDR4(a) "SMMUX_IDR4"
#define device_bar_BDK_SMMUX_IDR4(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IDR4(a) (a)
#define arguments_BDK_SMMUX_IDR4(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_idr5
 *
 * SMMU Identification 5 Register
 */
union bdk_smmux_idr5
{
    uint32_t u;
    struct bdk_smmux_idr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t stall_max             : 16; /**< [ 31: 16](RO) Maximum number of outstanding stalled transactions supported by SMMU/system.
                                                                 Internal:
                                                                 The SMMU guarantees that the total number of stall fault records that will be
                                                                 recorded in any event queue, without any having been the subject of a
                                                                 resume/terminate command, will not exceed this number. This field is 0 if
                                                                 SMMU()_IDR0[STALL_MODEL]=0x1 (Stalling faults not supported). Note: Hypervisor
                                                                 software could use this value to allocate a static buffer for stall fault
                                                                 records, so that they can be immediately consumed from the event queue upon
                                                                 delivery without being dependent on delivery into guest VM event queues. This
                                                                 decouples the rates of consumption. */
        uint32_t reserved_12_15        : 4;
        uint32_t vax                   : 2;  /**< [ 11: 10](RO) Virtual address extend.
                                                                 0x0 = Virtual addresses of 48 bits per SMMU_CD_S[TTBx] supported.
                                                                 0x1 = Virtual addresses of 52 bits per SMMU_CD_S[TTBx] supported.
                                                                 0x2, 0x3 = Reserved. */
        uint32_t reserved_7_9          : 3;
        uint32_t gran64k               : 1;  /**< [  6:  6](RO) 64 KB translation granule supported. */
        uint32_t gran16k               : 1;  /**< [  5:  5](RO) 16 KB translation granule supported. */
        uint32_t gran4k                : 1;  /**< [  4:  4](RO) 4 KB translation granule supported. */
        uint32_t reserved_3            : 1;
        uint32_t oas                   : 3;  /**< [  2:  0](RO) Output address size (size of physical address output from SMMU).
                                                                  0x0 = 32 bits.
                                                                  0x1 = 36 bits.
                                                                  0x2 = 40 bits.
                                                                  0x3 = 42 bits.
                                                                  0x4 = 44 bits.
                                                                  0x5 = 48 bits.
                                                                  0x6 = 52 bits.
                                                                  _ Other values reserved.

                                                                 Where reference is made to OAS, it is the size value (32, 36, 40, etc.) that is
                                                                 referenced, not the literal value of this field. For example, MAX(OAS, 40) is
                                                                 intended to evaluate against a size like 36, not the field encoding 0x1. */
#else /* Word 0 - Little Endian */
        uint32_t oas                   : 3;  /**< [  2:  0](RO) Output address size (size of physical address output from SMMU).
                                                                  0x0 = 32 bits.
                                                                  0x1 = 36 bits.
                                                                  0x2 = 40 bits.
                                                                  0x3 = 42 bits.
                                                                  0x4 = 44 bits.
                                                                  0x5 = 48 bits.
                                                                  0x6 = 52 bits.
                                                                  _ Other values reserved.

                                                                 Where reference is made to OAS, it is the size value (32, 36, 40, etc.) that is
                                                                 referenced, not the literal value of this field. For example, MAX(OAS, 40) is
                                                                 intended to evaluate against a size like 36, not the field encoding 0x1. */
        uint32_t reserved_3            : 1;
        uint32_t gran4k                : 1;  /**< [  4:  4](RO) 4 KB translation granule supported. */
        uint32_t gran16k               : 1;  /**< [  5:  5](RO) 16 KB translation granule supported. */
        uint32_t gran64k               : 1;  /**< [  6:  6](RO) 64 KB translation granule supported. */
        uint32_t reserved_7_9          : 3;
        uint32_t vax                   : 2;  /**< [ 11: 10](RO) Virtual address extend.
                                                                 0x0 = Virtual addresses of 48 bits per SMMU_CD_S[TTBx] supported.
                                                                 0x1 = Virtual addresses of 52 bits per SMMU_CD_S[TTBx] supported.
                                                                 0x2, 0x3 = Reserved. */
        uint32_t reserved_12_15        : 4;
        uint32_t stall_max             : 16; /**< [ 31: 16](RO) Maximum number of outstanding stalled transactions supported by SMMU/system.
                                                                 Internal:
                                                                 The SMMU guarantees that the total number of stall fault records that will be
                                                                 recorded in any event queue, without any having been the subject of a
                                                                 resume/terminate command, will not exceed this number. This field is 0 if
                                                                 SMMU()_IDR0[STALL_MODEL]=0x1 (Stalling faults not supported). Note: Hypervisor
                                                                 software could use this value to allocate a static buffer for stall fault
                                                                 records, so that they can be immediately consumed from the event queue upon
                                                                 delivery without being dependent on delivery into guest VM event queues. This
                                                                 decouples the rates of consumption. */
#endif /* Word 0 - End */
    } s;
    struct bdk_smmux_idr5_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_smmux_idr5_s cn9; */
};
typedef union bdk_smmux_idr5 bdk_smmux_idr5_t;

static inline uint64_t BDK_SMMUX_IDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IDR5(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000034ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000034ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000034ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000014ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IDR5", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IDR5(a) bdk_smmux_idr5_t
#define bustype_BDK_SMMUX_IDR5(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IDR5(a) "SMMUX_IDR5"
#define device_bar_BDK_SMMUX_IDR5(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IDR5(a) (a)
#define arguments_BDK_SMMUX_IDR5(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_idr6
 *
 * SMMU Identification Register 6
 * Not implemented in CNXXXX.
 */
union bdk_smmux_idr6
{
    uint32_t u;
    struct bdk_smmux_idr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_idr6_s cn; */
};
typedef union bdk_smmux_idr6 bdk_smmux_idr6_t;

static inline uint64_t BDK_SMMUX_IDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IDR6(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000038ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000038ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000038ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_IDR6", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IDR6(a) bdk_smmux_idr6_t
#define bustype_BDK_SMMUX_IDR6(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IDR6(a) "SMMUX_IDR6"
#define device_bar_BDK_SMMUX_IDR6(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IDR6(a) (a)
#define arguments_BDK_SMMUX_IDR6(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_idr7
 *
 * SMMU Identification Register 7
 */
union bdk_smmux_idr7
{
    uint32_t u;
    struct bdk_smmux_idr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t major                 : 4;  /**< [  7:  4](RO) The major part of the implementation version number.
                                                                 On CNXXXX the major revision. See MIO_FUS_DAT2[CHIP_ID]. */
        uint32_t minor                 : 4;  /**< [  3:  0](RO) The minor part of the implementation version number.
                                                                 On CNXXXX the minor revision. See MIO_FUS_DAT2[CHIP_ID]. */
#else /* Word 0 - Little Endian */
        uint32_t minor                 : 4;  /**< [  3:  0](RO) The minor part of the implementation version number.
                                                                 On CNXXXX the minor revision. See MIO_FUS_DAT2[CHIP_ID]. */
        uint32_t major                 : 4;  /**< [  7:  4](RO) The major part of the implementation version number.
                                                                 On CNXXXX the major revision. See MIO_FUS_DAT2[CHIP_ID]. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_idr7_s cn; */
};
typedef union bdk_smmux_idr7 bdk_smmux_idr7_t;

static inline uint64_t BDK_SMMUX_IDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IDR7(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x83000000003cll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x83000000003cll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x83000000003cll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_IDR7", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IDR7(a) bdk_smmux_idr7_t
#define bustype_BDK_SMMUX_IDR7(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IDR7(a) "SMMUX_IDR7"
#define device_bar_BDK_SMMUX_IDR7(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IDR7(a) (a)
#define arguments_BDK_SMMUX_IDR7(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_iidr
 *
 * SMMU Implementation Identification Register
 * Provides information about the implementation/implementer of the SMMU and
 * architecture version supported.
 */
union bdk_smmux_iidr
{
    uint32_t u;
    struct bdk_smmux_iidr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t productid             : 12; /**< [ 31: 20](RO) An implementation defined product number for the device.
                                                                 In CNXXXX, enumerated by PCC_PROD_E.

                                                                 Internal:
                                                                 RTL: This comes from the fuse chain.  {`PCC_PIDR_PARTNUM1_E__COMP_M, gbl_fus__capt.chip_type} */
        uint32_t variant               : 4;  /**< [ 19: 16](RO) Indicates the major revision or variant of the product.
                                                                 On CNXXXX, this is the major revision. See FUS_FUSE_NUM_E::CHIP_ID().

                                                                 Internal:
                                                                 RTL: This comes from the fuse chain. gbl_fus__capt.chip_id[7:4] */
        uint32_t revision              : 4;  /**< [ 15: 12](RO) Indicates the minor revision or variant of the product.
                                                                 On CNXXXX, this is the minor revision. See FUS_FUSE_NUM_E::CHIP_ID().

                                                                 Internal:
                                                                 RTL: This comes from the fuse chain. gbl_fus__capt.chip_id[3:0] */
        uint32_t implementer           : 12; /**< [ 11:  0](RO) Contains the JEP106 code of the company that implemented the SMMU:
                                                                    0x34C = Cavium.

                                                                 Matches the SMMU()_PIDR1/2/4[DES_{0,1,2}] fields. */
#else /* Word 0 - Little Endian */
        uint32_t implementer           : 12; /**< [ 11:  0](RO) Contains the JEP106 code of the company that implemented the SMMU:
                                                                    0x34C = Cavium.

                                                                 Matches the SMMU()_PIDR1/2/4[DES_{0,1,2}] fields. */
        uint32_t revision              : 4;  /**< [ 15: 12](RO) Indicates the minor revision or variant of the product.
                                                                 On CNXXXX, this is the minor revision. See FUS_FUSE_NUM_E::CHIP_ID().

                                                                 Internal:
                                                                 RTL: This comes from the fuse chain. gbl_fus__capt.chip_id[3:0] */
        uint32_t variant               : 4;  /**< [ 19: 16](RO) Indicates the major revision or variant of the product.
                                                                 On CNXXXX, this is the major revision. See FUS_FUSE_NUM_E::CHIP_ID().

                                                                 Internal:
                                                                 RTL: This comes from the fuse chain. gbl_fus__capt.chip_id[7:4] */
        uint32_t productid             : 12; /**< [ 31: 20](RO) An implementation defined product number for the device.
                                                                 In CNXXXX, enumerated by PCC_PROD_E.

                                                                 Internal:
                                                                 RTL: This comes from the fuse chain.  {`PCC_PIDR_PARTNUM1_E__COMP_M, gbl_fus__capt.chip_type} */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_iidr_s cn; */
};
typedef union bdk_smmux_iidr bdk_smmux_iidr_t;

static inline uint64_t BDK_SMMUX_IIDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IIDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000018ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IIDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IIDR(a) bdk_smmux_iidr_t
#define bustype_BDK_SMMUX_IIDR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IIDR(a) "SMMUX_IIDR"
#define device_bar_BDK_SMMUX_IIDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IIDR(a) (a)
#define arguments_BDK_SMMUX_IIDR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_imp_actlr
 *
 * SMMU Auxiliary Control Register
 */
union bdk_smmux_imp_actlr
{
    uint32_t u;
    struct bdk_smmux_imp_actlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_17_31        : 15;
        uint32_t qos                   : 1;  /**< [ 16: 16](R/W) SMMU(0)_S_IMP_ACTLR[QOS] */
        uint32_t reserved_8_15         : 8;
        uint32_t cpid                  : 8;  /**< [  7:  0](R/W) SMMU(0)_S_IMP_ACTLR[CPID] */
#else /* Word 0 - Little Endian */
        uint32_t cpid                  : 8;  /**< [  7:  0](R/W) SMMU(0)_S_IMP_ACTLR[CPID] */
        uint32_t reserved_8_15         : 8;
        uint32_t qos                   : 1;  /**< [ 16: 16](R/W) SMMU(0)_S_IMP_ACTLR[QOS] */
        uint32_t reserved_17_31        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_imp_actlr_s cn; */
};
typedef union bdk_smmux_imp_actlr bdk_smmux_imp_actlr_t;

static inline uint64_t BDK_SMMUX_IMP_ACTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IMP_ACTLR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000e10ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IMP_ACTLR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IMP_ACTLR(a) bdk_smmux_imp_actlr_t
#define bustype_BDK_SMMUX_IMP_ACTLR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IMP_ACTLR(a) "SMMUX_IMP_ACTLR"
#define device_bar_BDK_SMMUX_IMP_ACTLR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IMP_ACTLR(a) (a)
#define arguments_BDK_SMMUX_IMP_ACTLR(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_imp_const0
 *
 * SMMU Constant Register
 */
union bdk_smmux_imp_const0
{
    uint64_t u;
    struct bdk_smmux_imp_const0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cxtc                  : 16; /**< [ 63: 48](RO) Number of CXTC entries. */
        uint64_t rstr                  : 16; /**< [ 47: 32](RO) Number of RSTR entries. */
        uint64_t wcu                   : 16; /**< [ 31: 16](RO) Number of walker cache (WCU) entries. */
        uint64_t tlb                   : 16; /**< [ 15:  0](RO) Number of IO-TLB entries. */
#else /* Word 0 - Little Endian */
        uint64_t tlb                   : 16; /**< [ 15:  0](RO) Number of IO-TLB entries. */
        uint64_t wcu                   : 16; /**< [ 31: 16](RO) Number of walker cache (WCU) entries. */
        uint64_t rstr                  : 16; /**< [ 47: 32](RO) Number of RSTR entries. */
        uint64_t cxtc                  : 16; /**< [ 63: 48](RO) Number of CXTC entries. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_imp_const0_s cn; */
};
typedef union bdk_smmux_imp_const0 bdk_smmux_imp_const0_t;

static inline uint64_t BDK_SMMUX_IMP_CONST0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IMP_CONST0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000e08ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IMP_CONST0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IMP_CONST0(a) bdk_smmux_imp_const0_t
#define bustype_BDK_SMMUX_IMP_CONST0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_IMP_CONST0(a) "SMMUX_IMP_CONST0"
#define device_bar_BDK_SMMUX_IMP_CONST0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IMP_CONST0(a) (a)
#define arguments_BDK_SMMUX_IMP_CONST0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_imp_debug
 *
 * SMMU Debug Registers
 * This register contains debug information.
 */
union bdk_smmux_imp_debug
{
    uint32_t u;
    struct bdk_smmux_imp_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_21_31        : 11;
        uint32_t walker                : 5;  /**< [ 20: 16](RO/H) Walkers active. */
        uint32_t inflight              : 16; /**< [ 15:  0](RO/H) Valid entries in inflight queue. */
#else /* Word 0 - Little Endian */
        uint32_t inflight              : 16; /**< [ 15:  0](RO/H) Valid entries in inflight queue. */
        uint32_t walker                : 5;  /**< [ 20: 16](RO/H) Walkers active. */
        uint32_t reserved_21_31        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_imp_debug_s cn; */
};
typedef union bdk_smmux_imp_debug bdk_smmux_imp_debug_t;

static inline uint64_t BDK_SMMUX_IMP_DEBUG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IMP_DEBUG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000e18ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IMP_DEBUG", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IMP_DEBUG(a) bdk_smmux_imp_debug_t
#define bustype_BDK_SMMUX_IMP_DEBUG(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IMP_DEBUG(a) "SMMUX_IMP_DEBUG"
#define device_bar_BDK_SMMUX_IMP_DEBUG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IMP_DEBUG(a) (a)
#define arguments_BDK_SMMUX_IMP_DEBUG(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_imp_eco
 *
 * INTERNAL: SMMU ECO Register
 */
union bdk_smmux_imp_eco
{
    uint32_t u;
    struct bdk_smmux_imp_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint32_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_imp_eco_s cn; */
};
typedef union bdk_smmux_imp_eco bdk_smmux_imp_eco_t;

static inline uint64_t BDK_SMMUX_IMP_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IMP_ECO(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000e00ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IMP_ECO", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IMP_ECO(a) bdk_smmux_imp_eco_t
#define bustype_BDK_SMMUX_IMP_ECO(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IMP_ECO(a) "SMMUX_IMP_ECO"
#define device_bar_BDK_SMMUX_IMP_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IMP_ECO(a) (a)
#define arguments_BDK_SMMUX_IMP_ECO(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_irq_ctrl
 *
 * SMMU Interrupt Request Control Register
 * Each field in this register has a corresponding field in SMMU()_IRQ_CTRLACK, with
 * the same "update" semantic as fields in SMMU()_CR0 versus SMMU()_CR0ACK.
 *
 * This register contains IRQ enable flags for GERROR/PRIQ/EVENTQ interrupt
 * sources. These enables allow/inhibit both edge-triggered wired outputs (if
 * implemented) and MSI writes (if implemented).
 *
 * IRQ enable flags guard the MSI address/payload registers, which must only be changed
 * when their respective enable flag is zero. See SMMU()_GERROR_IRQ_CFG0 for details.
 *
 * Completion of an update of x_IRQEN from zero to one guarantees that the MSI configuration
 * in SMMU()_x_IRQ_CFG{0,1,2} will be used for all future MSIs generated from source `x'.
 * An update of x_IRQEN from one to zero completes when all prior MSIs have become visible
 * to their shareability domain (have completed). Completion of this update guarantees
 * that no new MSI writes or wired edge events will later become visible from source
 * `x'.
 */
union bdk_smmux_irq_ctrl
{
    uint32_t u;
    struct bdk_smmux_irq_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t eventq_irqen          : 1;  /**< [  2:  2](R/W) Nonsecure event queue interrupt enable. */
        uint32_t priq_irqen            : 1;  /**< [  1:  1](RAZ) Reserved as SMMU()_IDR0[PRI]=0.
                                                                 Internal:
                                                                 Not implemented in CNXXXX. */
        uint32_t gerror_irqen          : 1;  /**< [  0:  0](R/W) Nonsecure GERROR interrupt enable. */
#else /* Word 0 - Little Endian */
        uint32_t gerror_irqen          : 1;  /**< [  0:  0](R/W) Nonsecure GERROR interrupt enable. */
        uint32_t priq_irqen            : 1;  /**< [  1:  1](RAZ) Reserved as SMMU()_IDR0[PRI]=0.
                                                                 Internal:
                                                                 Not implemented in CNXXXX. */
        uint32_t eventq_irqen          : 1;  /**< [  2:  2](R/W) Nonsecure event queue interrupt enable. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_irq_ctrl_s cn; */
};
typedef union bdk_smmux_irq_ctrl bdk_smmux_irq_ctrl_t;

static inline uint64_t BDK_SMMUX_IRQ_CTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IRQ_CTRL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000050ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IRQ_CTRL", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IRQ_CTRL(a) bdk_smmux_irq_ctrl_t
#define bustype_BDK_SMMUX_IRQ_CTRL(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IRQ_CTRL(a) "SMMUX_IRQ_CTRL"
#define device_bar_BDK_SMMUX_IRQ_CTRL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IRQ_CTRL(a) (a)
#define arguments_BDK_SMMUX_IRQ_CTRL(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_irq_ctrlack
 *
 * SMMU Interrupt Control Acknowledgement Register
 * This register is a read-only copy of SMMU()_IRQ_CTRL.
 */
union bdk_smmux_irq_ctrlack
{
    uint32_t u;
    struct bdk_smmux_irq_ctrlack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t eventq_irqen          : 1;  /**< [  2:  2](RO/H) Read-only hardware-modified SMMU(0)_IRQ_CTRL[EVENTQ_IRQEN]. */
        uint32_t priq_irqen            : 1;  /**< [  1:  1](RAZ) Read-only hardware-modified SMMU(0)_IRQ_CTRL[PRIQ_IRQEN].
                                                                 Internal:
                                                                 Not implemented in CNXXXX. */
        uint32_t gerror_irqen          : 1;  /**< [  0:  0](RO/H) Read-only hardware-modified SMMU(0)_IRQ_CTRL[GERROR_IRQEN]. */
#else /* Word 0 - Little Endian */
        uint32_t gerror_irqen          : 1;  /**< [  0:  0](RO/H) Read-only hardware-modified SMMU(0)_IRQ_CTRL[GERROR_IRQEN]. */
        uint32_t priq_irqen            : 1;  /**< [  1:  1](RAZ) Read-only hardware-modified SMMU(0)_IRQ_CTRL[PRIQ_IRQEN].
                                                                 Internal:
                                                                 Not implemented in CNXXXX. */
        uint32_t eventq_irqen          : 1;  /**< [  2:  2](RO/H) Read-only hardware-modified SMMU(0)_IRQ_CTRL[EVENTQ_IRQEN]. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_irq_ctrlack_s cn; */
};
typedef union bdk_smmux_irq_ctrlack bdk_smmux_irq_ctrlack_t;

static inline uint64_t BDK_SMMUX_IRQ_CTRLACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_IRQ_CTRLACK(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000054ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_IRQ_CTRLACK", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_IRQ_CTRLACK(a) bdk_smmux_irq_ctrlack_t
#define bustype_BDK_SMMUX_IRQ_CTRLACK(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_IRQ_CTRLACK(a) "SMMUX_IRQ_CTRLACK"
#define device_bar_BDK_SMMUX_IRQ_CTRLACK(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_IRQ_CTRLACK(a) (a)
#define arguments_BDK_SMMUX_IRQ_CTRLACK(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_look_par
 *
 * SMMU Secure Diagnostic Lookup Result Register
 * Receives the physical address from a SMMU()_LOOK_REQ operation. For diagnostic use only.
 */
union bdk_smmux_look_par
{
    uint64_t u;
    struct bdk_smmux_look_par_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t pa                    : 36; /**< [ 47: 12](SRO/H) If [FAULT]=0, physical address of the completed lookup. */
        uint64_t reserved_3_11         : 9;
        uint64_t nsec                  : 1;  /**< [  2:  2](SRO/H) If [FAULT]=0, nonsecure. The final resolved secure state for the translation, matching
                                                                 the nonsecure bit passed to the L2 cache. */
        uint64_t active                : 1;  /**< [  1:  1](SRO/H) Translation in progress. Set on write to SMMU()_LOOK_REQ[GO], cleared when translation
                                                                 has completed. */
        uint64_t fault                 : 1;  /**< [  0:  0](SRO/H) Fault. If 0 indicates completed successfully. If 1, the fault will not be recorded in the
                                                                 error registers. */
#else /* Word 0 - Little Endian */
        uint64_t fault                 : 1;  /**< [  0:  0](SRO/H) Fault. If 0 indicates completed successfully. If 1, the fault will not be recorded in the
                                                                 error registers. */
        uint64_t active                : 1;  /**< [  1:  1](SRO/H) Translation in progress. Set on write to SMMU()_LOOK_REQ[GO], cleared when translation
                                                                 has completed. */
        uint64_t nsec                  : 1;  /**< [  2:  2](SRO/H) If [FAULT]=0, nonsecure. The final resolved secure state for the translation, matching
                                                                 the nonsecure bit passed to the L2 cache. */
        uint64_t reserved_3_11         : 9;
        uint64_t pa                    : 36; /**< [ 47: 12](SRO/H) If [FAULT]=0, physical address of the completed lookup. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_look_par_s cn; */
};
typedef union bdk_smmux_look_par bdk_smmux_look_par_t;

static inline uint64_t BDK_SMMUX_LOOK_PAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_LOOK_PAR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000020120ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000020120ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000020120ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_LOOK_PAR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_LOOK_PAR(a) bdk_smmux_look_par_t
#define bustype_BDK_SMMUX_LOOK_PAR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_LOOK_PAR(a) "SMMUX_LOOK_PAR"
#define device_bar_BDK_SMMUX_LOOK_PAR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_LOOK_PAR(a) (a)
#define arguments_BDK_SMMUX_LOOK_PAR(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_look_req
 *
 * SMMU Secure Diagnostic Lookup Request Register
 * For diagnostic use only.
 */
union bdk_smmux_look_req
{
    uint64_t u;
    struct bdk_smmux_look_req_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t va                    : 37; /**< [ 48: 12](SR/W) Virtual address to lookup. */
        uint64_t reserved_3_11         : 9;
        uint64_t rd                    : 1;  /**< [  2:  2](SR/W) Read operation lookup; page must allow reads. Either a read or write operation must be asserted. */
        uint64_t wr                    : 1;  /**< [  1:  1](SR/W) Write operation lookup; page must allow writes. Either a read or write operation must be asserted. */
        uint64_t go                    : 1;  /**< [  0:  0](SWO) Write a one to request translation begin. Read SMMU()_LOOK_PAR[ACTIVE] to determine
                                                                 when the translation completes. */
#else /* Word 0 - Little Endian */
        uint64_t go                    : 1;  /**< [  0:  0](SWO) Write a one to request translation begin. Read SMMU()_LOOK_PAR[ACTIVE] to determine
                                                                 when the translation completes. */
        uint64_t wr                    : 1;  /**< [  1:  1](SR/W) Write operation lookup; page must allow writes. Either a read or write operation must be asserted. */
        uint64_t rd                    : 1;  /**< [  2:  2](SR/W) Read operation lookup; page must allow reads. Either a read or write operation must be asserted. */
        uint64_t reserved_3_11         : 9;
        uint64_t va                    : 37; /**< [ 48: 12](SR/W) Virtual address to lookup. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_look_req_s cn; */
};
typedef union bdk_smmux_look_req bdk_smmux_look_req_t;

static inline uint64_t BDK_SMMUX_LOOK_REQ(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_LOOK_REQ(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000020100ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000020100ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000020100ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_LOOK_REQ", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_LOOK_REQ(a) bdk_smmux_look_req_t
#define bustype_BDK_SMMUX_LOOK_REQ(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_LOOK_REQ(a) "SMMUX_LOOK_REQ"
#define device_bar_BDK_SMMUX_LOOK_REQ(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_LOOK_REQ(a) (a)
#define arguments_BDK_SMMUX_LOOK_REQ(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_look_strm
 *
 * SMMU Secure Diagnostic Lookup Stream Register
 * Specifies additional lookup values for the next SMMU()_LOOK_REQ
 * operation. For diagnostic use only.
 */
union bdk_smmux_look_strm
{
    uint64_t u;
    struct bdk_smmux_look_strm_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t stream                : 16; /**< [ 15:  0](SR/W) Stream ID. */
#else /* Word 0 - Little Endian */
        uint64_t stream                : 16; /**< [ 15:  0](SR/W) Stream ID. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_look_strm_s cn; */
};
typedef union bdk_smmux_look_strm bdk_smmux_look_strm_t;

static inline uint64_t BDK_SMMUX_LOOK_STRM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_LOOK_STRM(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000020110ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000020110ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000020110ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_LOOK_STRM", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_LOOK_STRM(a) bdk_smmux_look_strm_t
#define bustype_BDK_SMMUX_LOOK_STRM(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_LOOK_STRM(a) "SMMUX_LOOK_STRM"
#define device_bar_BDK_SMMUX_LOOK_STRM(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_LOOK_STRM(a) (a)
#define arguments_BDK_SMMUX_LOOK_STRM(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_msix_pba#
 *
 * SMMU MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the SMMU_INT_VEC_E enumeration.
 */
union bdk_smmux_msix_pbax
{
    uint64_t u;
    struct bdk_smmux_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for each interrupt, enumerated by SMMU_INT_VEC_E. Bits that have no
                                                                 associated SMMU_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for each interrupt, enumerated by SMMU_INT_VEC_E. Bits that have no
                                                                 associated SMMU_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_msix_pbax_s cn; */
};
typedef union bdk_smmux_msix_pbax bdk_smmux_msix_pbax_t;

static inline uint64_t BDK_SMMUX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=2)))
        return 0x83000f0f0000ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=4)))
        return 0x83000f0f0000ll + 0x1000000000ll * ((a) & 0x1) + 8ll * ((b) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=4)))
        return 0x83000f0f0000ll + 0x1000000000ll * ((a) & 0x3) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("SMMUX_MSIX_PBAX", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_MSIX_PBAX(a,b) bdk_smmux_msix_pbax_t
#define bustype_BDK_SMMUX_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_MSIX_PBAX(a,b) "SMMUX_MSIX_PBAX"
#define device_bar_BDK_SMMUX_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_SMMUX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_SMMUX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_msix_vec#_addr
 *
 * SMMU MSI-X Vector Table Address Registers
 * This register is the MSI-X vector table, indexed by the SMMU_INT_VEC_E enumeration.
 */
union bdk_smmux_msix_vecx_addr
{
    uint64_t u;
    struct bdk_smmux_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's SMMU()_MSIX_VEC()_ADDR, SMMU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of SMMU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_SMMU(0..3)_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if [SECVEC]
                                                                 was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's SMMU()_MSIX_VEC()_ADDR, SMMU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of SMMU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_SMMU(0..3)_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if [SECVEC]
                                                                 was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    struct bdk_smmux_msix_vecx_addr_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's SMMU()_MSIX_VEC()_ADDR, SMMU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of SMMU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_SMMU(0)_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if [SECVEC]
                                                                 was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's SMMU()_MSIX_VEC()_ADDR, SMMU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of SMMU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_SMMU(0)_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if [SECVEC]
                                                                 was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_smmux_msix_vecx_addr_s cn88xx; */
    struct bdk_smmux_msix_vecx_addr_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's SMMU()_MSIX_VEC()_ADDR, SMMU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of SMMU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_SMMU(0..1)_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if [SECVEC]
                                                                 was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's SMMU()_MSIX_VEC()_ADDR, SMMU()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of SMMU()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_SMMU(0..1)_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if [SECVEC]
                                                                 was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_smmux_msix_vecx_addr bdk_smmux_msix_vecx_addr_t;

static inline uint64_t BDK_SMMUX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=133)))
        return 0x83000f000000ll + 0x1000000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0xff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=261)))
        return 0x83000f000000ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x1ff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=261)))
        return 0x83000f000000ll + 0x1000000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x1ff);
    __bdk_csr_fatal("SMMUX_MSIX_VECX_ADDR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_MSIX_VECX_ADDR(a,b) bdk_smmux_msix_vecx_addr_t
#define bustype_BDK_SMMUX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_MSIX_VECX_ADDR(a,b) "SMMUX_MSIX_VECX_ADDR"
#define device_bar_BDK_SMMUX_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_SMMUX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_SMMUX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_msix_vec#_ctl
 *
 * SMMU MSI-X Vector Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the SMMU_INT_VEC_E enumeration.
 */
union bdk_smmux_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_smmux_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_msix_vecx_ctl_s cn; */
};
typedef union bdk_smmux_msix_vecx_ctl bdk_smmux_msix_vecx_ctl_t;

static inline uint64_t BDK_SMMUX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=133)))
        return 0x83000f000008ll + 0x1000000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0xff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=261)))
        return 0x83000f000008ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x1ff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=261)))
        return 0x83000f000008ll + 0x1000000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x1ff);
    __bdk_csr_fatal("SMMUX_MSIX_VECX_CTL", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_MSIX_VECX_CTL(a,b) bdk_smmux_msix_vecx_ctl_t
#define bustype_BDK_SMMUX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_MSIX_VECX_CTL(a,b) "SMMUX_MSIX_VECX_CTL"
#define device_bar_BDK_SMMUX_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_SMMUX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_SMMUX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_ns_hit_perf
 *
 * SMMU Nonsecure Hits Performance Counter Register
 */
union bdk_smmux_ns_hit_perf
{
    uint64_t u;
    struct bdk_smmux_ns_hit_perf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Counts the number of hits in nonsecure mode. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Counts the number of hits in nonsecure mode. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_ns_hit_perf_s cn; */
};
typedef union bdk_smmux_ns_hit_perf bdk_smmux_ns_hit_perf_t;

static inline uint64_t BDK_SMMUX_NS_HIT_PERF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NS_HIT_PERF(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000021010ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000021010ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000021010ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NS_HIT_PERF", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NS_HIT_PERF(a) bdk_smmux_ns_hit_perf_t
#define bustype_BDK_SMMUX_NS_HIT_PERF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_NS_HIT_PERF(a) "SMMUX_NS_HIT_PERF"
#define device_bar_BDK_SMMUX_NS_HIT_PERF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NS_HIT_PERF(a) (a)
#define arguments_BDK_SMMUX_NS_HIT_PERF(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nsacr
 *
 * SMMU Secure Alias to Nonsecure Auxiliary Configuration Register
 * Provides secure alias for nonsecure register SMMU()_(S)ACR.
 */
union bdk_smmux_nsacr
{
    uint32_t u;
    struct bdk_smmux_nsacr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qos                   : 4;  /**< [ 31: 28](R/W) L2C quality-of-service value to use for standard transactions that are not by a specific
                                                                 context, and so SMMU()_CB()_ACTLR[QOS] is not applicable. */
        uint32_t qos_walk              : 4;  /**< [ 27: 24](R/W) L2C quality-of-service value to use for page table walks. For optimal performance, this
                                                                 typically would be set to the most preferential QoS value of zero. */
        uint32_t reserved_0_23         : 24;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_23         : 24;
        uint32_t qos_walk              : 4;  /**< [ 27: 24](R/W) L2C quality-of-service value to use for page table walks. For optimal performance, this
                                                                 typically would be set to the most preferential QoS value of zero. */
        uint32_t qos                   : 4;  /**< [ 31: 28](R/W) L2C quality-of-service value to use for standard transactions that are not by a specific
                                                                 context, and so SMMU()_CB()_ACTLR[QOS] is not applicable. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nsacr_s cn; */
};
typedef union bdk_smmux_nsacr bdk_smmux_nsacr_t;

static inline uint64_t BDK_SMMUX_NSACR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSACR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000410ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000410ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000410ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSACR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSACR(a) bdk_smmux_nsacr_t
#define bustype_BDK_SMMUX_NSACR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSACR(a) "SMMUX_NSACR"
#define device_bar_BDK_SMMUX_NSACR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSACR(a) (a)
#define arguments_BDK_SMMUX_NSACR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nscr0
 *
 * SMMU Secure Alias to Nonsecure Configuration Register 0
 * Provides secure alias for nonsecure register SMMU()_(S)CR0.
 */
union bdk_smmux_nscr0
{
    uint32_t u;
    struct bdk_smmux_nscr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t vmid16en              : 1;  /**< [ 31: 31](R/W) Handling of 16-bit VMID extension:
                                                                 0 = 8-bit VMIDs are in use.
                                                                 The VMID is held in SMMU()_CBAR()[VMID].
                                                                 The SMMU()_CBA2R()[VMID16] field is 0.

                                                                 1 = 16-bit VMIDs are in use.
                                                                 The VMID is held in SMMU()_CBA2R()[VMID16].
                                                                 The SMMU()_CBAR()[VMID] field is 0.

                                                                 Only exists in the nonsecure copy of this register.

                                                                 In pass 1, this field must be 0. */
        uint32_t hypmode               : 1;  /**< [ 30: 30](R/W) Hypervisor mode. Selects which hypervisor context is used:
                                                                   0 = When SMMU()_CBAR()[CTYPE] = 0x1, SMMU()_CBAR()\<10\> represents HYPC.
                                                                   1 = When SMMU()_CBAR()[CTYPE] = 0x1, SMMU()_CBAR()\<10\> represents E2HC.

                                                                 If this bit is changed, TLB maintenance is required.

                                                                 Only exists in the non secure copy of this register. */
        uint32_t nscfg                 : 2;  /**< [ 29: 28](SR/W) Nonsecure configuration. Only exist in secure copy of register, RES0 in nonsecure copy.
                                                                 This field only applies to secure transactions bypassing the SMMU stream mapping
                                                                 process.
                                                                 0x0 = Use default NS attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Secure.
                                                                 0x3 = Nonsecure. */
        uint32_t wacfg                 : 2;  /**< [ 27: 26](RO) Write-allocate configuration, controls the allocation hint for write accesses. This field
                                                                 applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Write-allocate.
                                                                 0x3 = No write-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t racfg                 : 2;  /**< [ 25: 24](RO) Read-allocate configuration, controls the allocation hint for read accesses. This field
                                                                 applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Read-allocate.
                                                                 0x3 = No read-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t shcfg                 : 2;  /**< [ 23: 22](RO) Shared configuration. Applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default shareable attributes.
                                                                 0x1 = Outer sharable.
                                                                 0x2 = Inner sharable.
                                                                 0x3 = Non-sharable.

                                                                 Ignored in CNXXXX. */
        uint32_t smcfcfg               : 1;  /**< [ 21: 21](RO) Stream match conflict fault configuration. Controls transactions with multiple matches in
                                                                 the stream mapping table.
                                                                 0 = Permit the transaction to bypass the SMMU.
                                                                 1 = Raise a stream match conflict fault.

                                                                 CNXXXX detects all stream match conflicts and always faults. */
        uint32_t mtcfg                 : 1;  /**< [ 20: 20](R/W) Memory type configuration, applies to transactions that bypass the stream mapping table.
                                                                 0 = Use the default memory attributes.
                                                                 1 = Use the MEMATTR field for memory attributes. */
        uint32_t memattr               : 4;  /**< [ 19: 16](R/W) Memory attributes for bypass transactions if MTCFG == 1. */
        uint32_t bsu                   : 2;  /**< [ 15: 14](RO) Barrier sharability upgrade. Upgrades the sharability of barriers issued by client devices
                                                                 that are not mapped to a translation context bank by setting the minimum sharability
                                                                 domain applied to any barrier.  Applies to transactions bypassing the stream mapping
                                                                 table.
                                                                 0x0 = No effect.
                                                                 0x1 = Inner sharable.
                                                                 0x2 = Outer sharable.
                                                                 0x3 = Full system.

                                                                 Ignored in CNXXXX. */
        uint32_t fb                    : 1;  /**< [ 13: 13](R/W) Force broadcast of TLB and instruction cache maintenance operations. Applies to
                                                                 transactions bypassing the stream mapping table. Affects client TLB maintenance, BPIALL
                                                                 and ICIALLU operations. If FB=1, any affected operation is modified to the equivalent
                                                                 broadcast variant in the inner shareable domain.
                                                                 0 = Process affected operations as presented.
                                                                 1 = Upgrade affected operations to be broadcast within the inner sharable domain.

                                                                 Ignored in CNXXXX, as NCB clients do not initiate invalidates. */
        uint32_t ptm                   : 1;  /**< [ 12: 12](R/W) Private TLB maintenance hint.
                                                                 0 = Process affected operations as presented.
                                                                 1 = SMMU TLBs are privately managed and are not require to respond to broadcast TLB
                                                                 maintenance operations from the wider system.

                                                                 CNXXXX honors this hint, but both the secure and nonsecure version must be set for
                                                                 private management.

                                                                 Internal:
                                                                 Note when set SMMU always still sends a response for the
                                                                 invalidates, it just does not perform the invalidation action against the TLB/WCU. */
        uint32_t vmidpne               : 1;  /**< [ 11: 11](RO) Reserved. */
        uint32_t usfcfg                : 1;  /**< [ 10: 10](R/W) Unidentified stream fault configuration.
                                                                 0 = Permit any transaction that does not match any entries in the stream matching table to
                                                                 pass through.
                                                                 1 = Raise an unidentified stream fault on any transaction that does not match any stream
                                                                 matching table entry. */
        uint32_t gse                   : 1;  /**< [  9:  9](RO) Global stall enable.
                                                                 0 = Do not enforce global stalling across contexts.
                                                                 1 = Enforce global stalling across contexts.

                                                                 In CNXXXX always 0, no stalling. */
        uint32_t stalld                : 1;  /**< [  8:  8](RO) Stall disable.
                                                                 0 = Permit per-context stalling on context faults.
                                                                 1 = Disable per-context stalling on context faults, or not programmable.

                                                                 In CNXXXX always 1, no stalling. */
        uint32_t transientcfg          : 2;  /**< [  7:  6](RO) Transient configuration controls the transient allocation hint.
                                                                 0x0 = Default transient allocation attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Non-transient.
                                                                 0x3 = Transient.

                                                                 Not implemented in CNXXXX. */
        uint32_t gcfgfie               : 1;  /**< [  5:  5](RO) Global configuration fault interrupt enable.
                                                                 0 = Do not raise an interrupt on a global configuration fault.
                                                                 1 = Raise an interrupt on a global configuration fault.

                                                                 In CNXXXX always zero, as does not support configuration faults. */
        uint32_t gcfgfre               : 1;  /**< [  4:  4](RO) Global configuration fault report enable.
                                                                 0 = Do not return an abort on a global configuration fault
                                                                 1 = Return an abort on a global configuration fault.

                                                                 In CNXXXX always zero, as does not support configuration faults. */
        uint32_t exidenable            : 1;  /**< [  3:  3](R/W) Extended stream ID enable.
                                                                 0 = For this SSD, SMMU()_SMR() has the format with the VALID bit in the
                                                                 SMMU()_SMR(). The SMMU()_S2CR()[EXIDVALID] is ignored.
                                                                 1 = For this SSD, SMMU()_SMR() has the extended id format and the valid bit is
                                                                 held in the corresponding SMMU()_S2CR()[EXIDVALID].

                                                                 Software should only change [EXIDENABLE] when all SMMU()_S2CR()[EXIDVALID] == 0
                                                                 and SMMU()_SMR()[EXMASK[15]/VALID] == 0 for the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized before use. */
        uint32_t gfie                  : 1;  /**< [  2:  2](R/W) Global fault interrupt enable.
                                                                 0 = Do not raise an interrupt on a global fault.
                                                                 1 = Raise an interrupt on a global fault. */
        uint32_t gfre                  : 1;  /**< [  1:  1](R/W) Global fault report enable.
                                                                 0 = Do not return an abort on a global fault.
                                                                 1 = Return an abort on a global fault. */
        uint32_t clientpd              : 1;  /**< [  0:  0](R/W) Client port disable.
                                                                 0 = Each SMMU client access is subject to translation, access control and attribute
                                                                 generation.
                                                                 1 = Each SMMU client access bypasses translation, access control and attribute generation. */
#else /* Word 0 - Little Endian */
        uint32_t clientpd              : 1;  /**< [  0:  0](R/W) Client port disable.
                                                                 0 = Each SMMU client access is subject to translation, access control and attribute
                                                                 generation.
                                                                 1 = Each SMMU client access bypasses translation, access control and attribute generation. */
        uint32_t gfre                  : 1;  /**< [  1:  1](R/W) Global fault report enable.
                                                                 0 = Do not return an abort on a global fault.
                                                                 1 = Return an abort on a global fault. */
        uint32_t gfie                  : 1;  /**< [  2:  2](R/W) Global fault interrupt enable.
                                                                 0 = Do not raise an interrupt on a global fault.
                                                                 1 = Raise an interrupt on a global fault. */
        uint32_t exidenable            : 1;  /**< [  3:  3](R/W) Extended stream ID enable.
                                                                 0 = For this SSD, SMMU()_SMR() has the format with the VALID bit in the
                                                                 SMMU()_SMR(). The SMMU()_S2CR()[EXIDVALID] is ignored.
                                                                 1 = For this SSD, SMMU()_SMR() has the extended id format and the valid bit is
                                                                 held in the corresponding SMMU()_S2CR()[EXIDVALID].

                                                                 Software should only change [EXIDENABLE] when all SMMU()_S2CR()[EXIDVALID] == 0
                                                                 and SMMU()_SMR()[EXMASK[15]/VALID] == 0 for the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized before use. */
        uint32_t gcfgfre               : 1;  /**< [  4:  4](RO) Global configuration fault report enable.
                                                                 0 = Do not return an abort on a global configuration fault
                                                                 1 = Return an abort on a global configuration fault.

                                                                 In CNXXXX always zero, as does not support configuration faults. */
        uint32_t gcfgfie               : 1;  /**< [  5:  5](RO) Global configuration fault interrupt enable.
                                                                 0 = Do not raise an interrupt on a global configuration fault.
                                                                 1 = Raise an interrupt on a global configuration fault.

                                                                 In CNXXXX always zero, as does not support configuration faults. */
        uint32_t transientcfg          : 2;  /**< [  7:  6](RO) Transient configuration controls the transient allocation hint.
                                                                 0x0 = Default transient allocation attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Non-transient.
                                                                 0x3 = Transient.

                                                                 Not implemented in CNXXXX. */
        uint32_t stalld                : 1;  /**< [  8:  8](RO) Stall disable.
                                                                 0 = Permit per-context stalling on context faults.
                                                                 1 = Disable per-context stalling on context faults, or not programmable.

                                                                 In CNXXXX always 1, no stalling. */
        uint32_t gse                   : 1;  /**< [  9:  9](RO) Global stall enable.
                                                                 0 = Do not enforce global stalling across contexts.
                                                                 1 = Enforce global stalling across contexts.

                                                                 In CNXXXX always 0, no stalling. */
        uint32_t usfcfg                : 1;  /**< [ 10: 10](R/W) Unidentified stream fault configuration.
                                                                 0 = Permit any transaction that does not match any entries in the stream matching table to
                                                                 pass through.
                                                                 1 = Raise an unidentified stream fault on any transaction that does not match any stream
                                                                 matching table entry. */
        uint32_t vmidpne               : 1;  /**< [ 11: 11](RO) Reserved. */
        uint32_t ptm                   : 1;  /**< [ 12: 12](R/W) Private TLB maintenance hint.
                                                                 0 = Process affected operations as presented.
                                                                 1 = SMMU TLBs are privately managed and are not require to respond to broadcast TLB
                                                                 maintenance operations from the wider system.

                                                                 CNXXXX honors this hint, but both the secure and nonsecure version must be set for
                                                                 private management.

                                                                 Internal:
                                                                 Note when set SMMU always still sends a response for the
                                                                 invalidates, it just does not perform the invalidation action against the TLB/WCU. */
        uint32_t fb                    : 1;  /**< [ 13: 13](R/W) Force broadcast of TLB and instruction cache maintenance operations. Applies to
                                                                 transactions bypassing the stream mapping table. Affects client TLB maintenance, BPIALL
                                                                 and ICIALLU operations. If FB=1, any affected operation is modified to the equivalent
                                                                 broadcast variant in the inner shareable domain.
                                                                 0 = Process affected operations as presented.
                                                                 1 = Upgrade affected operations to be broadcast within the inner sharable domain.

                                                                 Ignored in CNXXXX, as NCB clients do not initiate invalidates. */
        uint32_t bsu                   : 2;  /**< [ 15: 14](RO) Barrier sharability upgrade. Upgrades the sharability of barriers issued by client devices
                                                                 that are not mapped to a translation context bank by setting the minimum sharability
                                                                 domain applied to any barrier.  Applies to transactions bypassing the stream mapping
                                                                 table.
                                                                 0x0 = No effect.
                                                                 0x1 = Inner sharable.
                                                                 0x2 = Outer sharable.
                                                                 0x3 = Full system.

                                                                 Ignored in CNXXXX. */
        uint32_t memattr               : 4;  /**< [ 19: 16](R/W) Memory attributes for bypass transactions if MTCFG == 1. */
        uint32_t mtcfg                 : 1;  /**< [ 20: 20](R/W) Memory type configuration, applies to transactions that bypass the stream mapping table.
                                                                 0 = Use the default memory attributes.
                                                                 1 = Use the MEMATTR field for memory attributes. */
        uint32_t smcfcfg               : 1;  /**< [ 21: 21](RO) Stream match conflict fault configuration. Controls transactions with multiple matches in
                                                                 the stream mapping table.
                                                                 0 = Permit the transaction to bypass the SMMU.
                                                                 1 = Raise a stream match conflict fault.

                                                                 CNXXXX detects all stream match conflicts and always faults. */
        uint32_t shcfg                 : 2;  /**< [ 23: 22](RO) Shared configuration. Applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default shareable attributes.
                                                                 0x1 = Outer sharable.
                                                                 0x2 = Inner sharable.
                                                                 0x3 = Non-sharable.

                                                                 Ignored in CNXXXX. */
        uint32_t racfg                 : 2;  /**< [ 25: 24](RO) Read-allocate configuration, controls the allocation hint for read accesses. This field
                                                                 applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Read-allocate.
                                                                 0x3 = No read-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t wacfg                 : 2;  /**< [ 27: 26](RO) Write-allocate configuration, controls the allocation hint for write accesses. This field
                                                                 applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Write-allocate.
                                                                 0x3 = No write-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t nscfg                 : 2;  /**< [ 29: 28](SR/W) Nonsecure configuration. Only exist in secure copy of register, RES0 in nonsecure copy.
                                                                 This field only applies to secure transactions bypassing the SMMU stream mapping
                                                                 process.
                                                                 0x0 = Use default NS attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Secure.
                                                                 0x3 = Nonsecure. */
        uint32_t hypmode               : 1;  /**< [ 30: 30](R/W) Hypervisor mode. Selects which hypervisor context is used:
                                                                   0 = When SMMU()_CBAR()[CTYPE] = 0x1, SMMU()_CBAR()\<10\> represents HYPC.
                                                                   1 = When SMMU()_CBAR()[CTYPE] = 0x1, SMMU()_CBAR()\<10\> represents E2HC.

                                                                 If this bit is changed, TLB maintenance is required.

                                                                 Only exists in the non secure copy of this register. */
        uint32_t vmid16en              : 1;  /**< [ 31: 31](R/W) Handling of 16-bit VMID extension:
                                                                 0 = 8-bit VMIDs are in use.
                                                                 The VMID is held in SMMU()_CBAR()[VMID].
                                                                 The SMMU()_CBA2R()[VMID16] field is 0.

                                                                 1 = 16-bit VMIDs are in use.
                                                                 The VMID is held in SMMU()_CBA2R()[VMID16].
                                                                 The SMMU()_CBAR()[VMID] field is 0.

                                                                 Only exists in the nonsecure copy of this register.

                                                                 In pass 1, this field must be 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nscr0_s cn; */
};
typedef union bdk_smmux_nscr0 bdk_smmux_nscr0_t;

static inline uint64_t BDK_SMMUX_NSCR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSCR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000400ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000400ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000400ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSCR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSCR0(a) bdk_smmux_nscr0_t
#define bustype_BDK_SMMUX_NSCR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSCR0(a) "SMMUX_NSCR0"
#define device_bar_BDK_SMMUX_NSCR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSCR0(a) (a)
#define arguments_BDK_SMMUX_NSCR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nscr2
 *
 * SMMU Secure Alias to Nonsecure Configuration Register 2
 * Provides secure alias for nonsecure register SMMU()_(S)CR2.
 */
union bdk_smmux_nscr2
{
    uint32_t u;
    struct bdk_smmux_nscr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t exsmrgenable          : 1;  /**< [ 31: 31](RO) Enables extended stream matching extension.
                                                                 In CNXXXX, extended stream matching is not implemented. */
        uint32_t exnssmrgdisable       : 1;  /**< [ 30: 30](SRO) Disables use of extended stream match register groups by nonsecure software.
                                                                 Only exists in the secure copy of this register.

                                                                 In CNXXXX, extended stream matching is not implemented. */
        uint32_t compindexenable       : 1;  /**< [ 29: 29](RO) StreamID compressed index match enable.

                                                                 In CNXXXX, StreamID compressed indexing is not implemented. */
        uint32_t reserved_16_28        : 13;
        uint32_t bpvmid                : 16; /**< [ 15:  0](RAZ) Bypass VMID. VMID field applied to client transactions that bypass the SMMU. In CNXXXX,
                                                                 not supported.

                                                                 Internal:
                                                                 If L2C adds support for QoS on a per VMID basis the L2C will also
                                                                 have a `secure' QoS setting, so this field should remain not required. */
#else /* Word 0 - Little Endian */
        uint32_t bpvmid                : 16; /**< [ 15:  0](RAZ) Bypass VMID. VMID field applied to client transactions that bypass the SMMU. In CNXXXX,
                                                                 not supported.

                                                                 Internal:
                                                                 If L2C adds support for QoS on a per VMID basis the L2C will also
                                                                 have a `secure' QoS setting, so this field should remain not required. */
        uint32_t reserved_16_28        : 13;
        uint32_t compindexenable       : 1;  /**< [ 29: 29](RO) StreamID compressed index match enable.

                                                                 In CNXXXX, StreamID compressed indexing is not implemented. */
        uint32_t exnssmrgdisable       : 1;  /**< [ 30: 30](SRO) Disables use of extended stream match register groups by nonsecure software.
                                                                 Only exists in the secure copy of this register.

                                                                 In CNXXXX, extended stream matching is not implemented. */
        uint32_t exsmrgenable          : 1;  /**< [ 31: 31](RO) Enables extended stream matching extension.
                                                                 In CNXXXX, extended stream matching is not implemented. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nscr2_s cn; */
};
typedef union bdk_smmux_nscr2 bdk_smmux_nscr2_t;

static inline uint64_t BDK_SMMUX_NSCR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSCR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000408ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000408ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000408ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSCR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSCR2(a) bdk_smmux_nscr2_t
#define bustype_BDK_SMMUX_NSCR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSCR2(a) "SMMUX_NSCR2"
#define device_bar_BDK_SMMUX_NSCR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSCR2(a) (a)
#define arguments_BDK_SMMUX_NSCR2(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_nsgfar
 *
 * SMMU Secure Alias to Nonsecure Global Fault Address Register
 * Provides secure alias for nonsecure register SMMU()_(S)GFAR.
 */
union bdk_smmux_nsgfar
{
    uint64_t u;
    struct bdk_smmux_nsgfar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t faddr                 : 49; /**< [ 48:  0](R/W/H) Fault address, the input IOVA of the faulty access. For configuration access faults,
                                                                 this is the physical address resulting in the fault. For other fault classes it is the
                                                                 input address of the faulting access, which the system can interpret in a number of ways.
                                                                 This register is updated before a valid context has been determined. Hence, no sign
                                                                 extension can have been performed.

                                                                 For CNXXXX \<11:0\> are always zero. */
#else /* Word 0 - Little Endian */
        uint64_t faddr                 : 49; /**< [ 48:  0](R/W/H) Fault address, the input IOVA of the faulty access. For configuration access faults,
                                                                 this is the physical address resulting in the fault. For other fault classes it is the
                                                                 input address of the faulting access, which the system can interpret in a number of ways.
                                                                 This register is updated before a valid context has been determined. Hence, no sign
                                                                 extension can have been performed.

                                                                 For CNXXXX \<11:0\> are always zero. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nsgfar_s cn; */
};
typedef union bdk_smmux_nsgfar bdk_smmux_nsgfar_t;

static inline uint64_t BDK_SMMUX_NSGFAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSGFAR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000440ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000440ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000440ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSGFAR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSGFAR(a) bdk_smmux_nsgfar_t
#define bustype_BDK_SMMUX_NSGFAR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_NSGFAR(a) "SMMUX_NSGFAR"
#define device_bar_BDK_SMMUX_NSGFAR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSGFAR(a) (a)
#define arguments_BDK_SMMUX_NSGFAR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nsgfsr
 *
 * SMMU Secure Alias to Nonsecure Global Fault Status Register
 * Provides secure alias for nonsecure register SMMU()_(S)GFSR.
 */
union bdk_smmux_nsgfsr
{
    uint32_t u;
    struct bdk_smmux_nsgfsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t multi                 : 1;  /**< [ 31: 31](R/W1C/H) Multiple error conditions.
                                                                 0 = No multiple error condition was encountered.
                                                                 1 = An error occurred while the value in this register was nonzero. */
        uint32_t reserved_9_30         : 22;
        uint32_t uut                   : 1;  /**< [  8:  8](R/W1C/H) Unsupported upstream transaction.
                                                                 0 = No unsupported upstream transaction fault.
                                                                 1 = Unsupported upstream transaction fault caused by receipt of an unsupported client
                                                                 transaction from an upstream device. */
        uint32_t pf                    : 1;  /**< [  7:  7](R/W1C/H) Permission fault. In SMMU_GFSR, this field is reserved. In SMMU_SGFSR, this field records
                                                                 global SMMU()_SCR1[SIF] faults.
                                                                 Note if a transaction is associated with a particular translation context bank, faults are
                                                                 recorded in SMMU()_CB()_FSR instead of SMMU_SGFSR. */
        uint32_t ef                    : 1;  /**< [  6:  6](R/W1C/H) External fault. */
        uint32_t caf                   : 1;  /**< [  5:  5](RO) Configuration access fault.
                                                                 For CNXXXX always zero, no configuration faults. */
        uint32_t ucif                  : 1;  /**< [  4:  4](R/W1C/H) Unimplemented context interrupt fault. */
        uint32_t ucbf                  : 1;  /**< [  3:  3](R/W1C/H) Unimplemented context bank fault. */
        uint32_t smcf                  : 1;  /**< [  2:  2](R/W1C/H) Stream match conflict fault. */
        uint32_t usf                   : 1;  /**< [  1:  1](R/W1C/H) Unidentified stream fault. */
        uint32_t icf                   : 1;  /**< [  0:  0](R/W1C/H) Invalid context fault. */
#else /* Word 0 - Little Endian */
        uint32_t icf                   : 1;  /**< [  0:  0](R/W1C/H) Invalid context fault. */
        uint32_t usf                   : 1;  /**< [  1:  1](R/W1C/H) Unidentified stream fault. */
        uint32_t smcf                  : 1;  /**< [  2:  2](R/W1C/H) Stream match conflict fault. */
        uint32_t ucbf                  : 1;  /**< [  3:  3](R/W1C/H) Unimplemented context bank fault. */
        uint32_t ucif                  : 1;  /**< [  4:  4](R/W1C/H) Unimplemented context interrupt fault. */
        uint32_t caf                   : 1;  /**< [  5:  5](RO) Configuration access fault.
                                                                 For CNXXXX always zero, no configuration faults. */
        uint32_t ef                    : 1;  /**< [  6:  6](R/W1C/H) External fault. */
        uint32_t pf                    : 1;  /**< [  7:  7](R/W1C/H) Permission fault. In SMMU_GFSR, this field is reserved. In SMMU_SGFSR, this field records
                                                                 global SMMU()_SCR1[SIF] faults.
                                                                 Note if a transaction is associated with a particular translation context bank, faults are
                                                                 recorded in SMMU()_CB()_FSR instead of SMMU_SGFSR. */
        uint32_t uut                   : 1;  /**< [  8:  8](R/W1C/H) Unsupported upstream transaction.
                                                                 0 = No unsupported upstream transaction fault.
                                                                 1 = Unsupported upstream transaction fault caused by receipt of an unsupported client
                                                                 transaction from an upstream device. */
        uint32_t reserved_9_30         : 22;
        uint32_t multi                 : 1;  /**< [ 31: 31](R/W1C/H) Multiple error conditions.
                                                                 0 = No multiple error condition was encountered.
                                                                 1 = An error occurred while the value in this register was nonzero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nsgfsr_s cn; */
};
typedef union bdk_smmux_nsgfsr bdk_smmux_nsgfsr_t;

static inline uint64_t BDK_SMMUX_NSGFSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSGFSR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000448ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000448ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000448ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSGFSR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSGFSR(a) bdk_smmux_nsgfsr_t
#define bustype_BDK_SMMUX_NSGFSR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSGFSR(a) "SMMUX_NSGFSR"
#define device_bar_BDK_SMMUX_NSGFSR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSGFSR(a) (a)
#define arguments_BDK_SMMUX_NSGFSR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nsgfsrrestore
 *
 * SMMU Secure Alias to Nonsecure Global Fault Status Restore Register
 * Provides secure alias for nonsecure register SMMU()_(S)GFSRRESTORE.
 */
union bdk_smmux_nsgfsrrestore
{
    uint32_t u;
    struct bdk_smmux_nsgfsrrestore_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t restore               : 32; /**< [ 31:  0](WO) Writes bits in corresponding SMMU()_(S)GFSR. */
#else /* Word 0 - Little Endian */
        uint32_t restore               : 32; /**< [ 31:  0](WO) Writes bits in corresponding SMMU()_(S)GFSR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nsgfsrrestore_s cn; */
};
typedef union bdk_smmux_nsgfsrrestore bdk_smmux_nsgfsrrestore_t;

static inline uint64_t BDK_SMMUX_NSGFSRRESTORE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSGFSRRESTORE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x83000000044cll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x83000000044cll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x83000000044cll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSGFSRRESTORE", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSGFSRRESTORE(a) bdk_smmux_nsgfsrrestore_t
#define bustype_BDK_SMMUX_NSGFSRRESTORE(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSGFSRRESTORE(a) "SMMUX_NSGFSRRESTORE"
#define device_bar_BDK_SMMUX_NSGFSRRESTORE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSGFSRRESTORE(a) (a)
#define arguments_BDK_SMMUX_NSGFSRRESTORE(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nsgfsynr0
 *
 * SMMU Secure Alias to Nonsecure Global Fault Syndrome Register 0
 * Provides secure alias for nonsecure register SMMU()_(S)GFSYNR0.
 */
union bdk_smmux_nsgfsynr0
{
    uint32_t u;
    struct bdk_smmux_nsgfsynr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t imp                   : 8;  /**< [ 15:  8](RO) Reserved for implementation. */
        uint32_t reserved_7            : 1;
        uint32_t ats                   : 1;  /**< [  6:  6](RO) Address translation operation fault. For CNXXXX zero, SMMU()_IDR0[ATOSNS] not supported. */
        uint32_t nsattr                : 1;  /**< [  5:  5](R/W/H) Nonsecure attribute.
                                                                 0 = The faulty transaction has the secure attribute.
                                                                 1 = The faulty transaction has the nonsecure attribute. */
        uint32_t nsstate               : 1;  /**< [  4:  4](SR/W/H) Nonsecure state.
                                                                 0 = The faulty transaction is associated with a secure device.
                                                                 1 = The faulty transaction is associated with a nonsecure device.

                                                                 This field is only valid for the secure state.

                                                                 This field may read 1 in the event that a fault is encountered in relation to a
                                                                 nonsecure client device and where SMMU()_SCR1[GEFRO]=1. */
        uint32_t ind                   : 1;  /**< [  3:  3](R/W/H) Instruction not data.
                                                                 0 = The faulty transaction has the data access attribute.
                                                                 1 = The faulty transaction has the instruction access attribute. */
        uint32_t pnu                   : 1;  /**< [  2:  2](R/W/H) Privileged not unprivileged.
                                                                 0 = The faulty transaction has the unprivileged attribute.
                                                                 1 = The faulty transaction has the privileged attribute. */
        uint32_t wnr                   : 1;  /**< [  1:  1](R/W/H) Write not read.
                                                                 0 = The faulty transaction is a read.
                                                                 1 = The faulty transaction is a write. */
        uint32_t nested                : 1;  /**< [  0:  0](R/W/H) Nested fault.
                                                                 0 = The fault occurred in the initial stream context.
                                                                 1 = The fault occurred in a nested context.

                                                                 This bit is reserved in SMMU_SGFSYNR0. */
#else /* Word 0 - Little Endian */
        uint32_t nested                : 1;  /**< [  0:  0](R/W/H) Nested fault.
                                                                 0 = The fault occurred in the initial stream context.
                                                                 1 = The fault occurred in a nested context.

                                                                 This bit is reserved in SMMU_SGFSYNR0. */
        uint32_t wnr                   : 1;  /**< [  1:  1](R/W/H) Write not read.
                                                                 0 = The faulty transaction is a read.
                                                                 1 = The faulty transaction is a write. */
        uint32_t pnu                   : 1;  /**< [  2:  2](R/W/H) Privileged not unprivileged.
                                                                 0 = The faulty transaction has the unprivileged attribute.
                                                                 1 = The faulty transaction has the privileged attribute. */
        uint32_t ind                   : 1;  /**< [  3:  3](R/W/H) Instruction not data.
                                                                 0 = The faulty transaction has the data access attribute.
                                                                 1 = The faulty transaction has the instruction access attribute. */
        uint32_t nsstate               : 1;  /**< [  4:  4](SR/W/H) Nonsecure state.
                                                                 0 = The faulty transaction is associated with a secure device.
                                                                 1 = The faulty transaction is associated with a nonsecure device.

                                                                 This field is only valid for the secure state.

                                                                 This field may read 1 in the event that a fault is encountered in relation to a
                                                                 nonsecure client device and where SMMU()_SCR1[GEFRO]=1. */
        uint32_t nsattr                : 1;  /**< [  5:  5](R/W/H) Nonsecure attribute.
                                                                 0 = The faulty transaction has the secure attribute.
                                                                 1 = The faulty transaction has the nonsecure attribute. */
        uint32_t ats                   : 1;  /**< [  6:  6](RO) Address translation operation fault. For CNXXXX zero, SMMU()_IDR0[ATOSNS] not supported. */
        uint32_t reserved_7            : 1;
        uint32_t imp                   : 8;  /**< [ 15:  8](RO) Reserved for implementation. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nsgfsynr0_s cn; */
};
typedef union bdk_smmux_nsgfsynr0 bdk_smmux_nsgfsynr0_t;

static inline uint64_t BDK_SMMUX_NSGFSYNR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSGFSYNR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000450ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000450ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000450ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSGFSYNR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSGFSYNR0(a) bdk_smmux_nsgfsynr0_t
#define bustype_BDK_SMMUX_NSGFSYNR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSGFSYNR0(a) "SMMUX_NSGFSYNR0"
#define device_bar_BDK_SMMUX_NSGFSYNR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSGFSYNR0(a) (a)
#define arguments_BDK_SMMUX_NSGFSYNR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nsgfsynr1
 *
 * SMMU Secure Alias to Nonsecure Global Fault Syndrome Register 1
 * Provides secure alias for nonsecure register SMMU()_(S)GFSYNR1.
 */
union bdk_smmux_nsgfsynr1
{
    uint32_t u;
    struct bdk_smmux_nsgfsynr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ssd_index             : 16; /**< [ 31: 16](SRO/H) The SSD index of the transaction that caused the fault. [SSD_INDEX] is only
                                                                 accessible to configuration accesses by secure software. Nonsecure configuration
                                                                 accesses treat this field as RAZ/WI.

                                                                 For CNXXXX, [SSD_INDEX] is always the same as [STREAMID]. */
        uint32_t streamid              : 16; /**< [ 15:  0](R/W/H) The stream ID of the transaction that caused the fault. */
#else /* Word 0 - Little Endian */
        uint32_t streamid              : 16; /**< [ 15:  0](R/W/H) The stream ID of the transaction that caused the fault. */
        uint32_t ssd_index             : 16; /**< [ 31: 16](SRO/H) The SSD index of the transaction that caused the fault. [SSD_INDEX] is only
                                                                 accessible to configuration accesses by secure software. Nonsecure configuration
                                                                 accesses treat this field as RAZ/WI.

                                                                 For CNXXXX, [SSD_INDEX] is always the same as [STREAMID]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nsgfsynr1_s cn; */
};
typedef union bdk_smmux_nsgfsynr1 bdk_smmux_nsgfsynr1_t;

static inline uint64_t BDK_SMMUX_NSGFSYNR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSGFSYNR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000454ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000454ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000454ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSGFSYNR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSGFSYNR1(a) bdk_smmux_nsgfsynr1_t
#define bustype_BDK_SMMUX_NSGFSYNR1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSGFSYNR1(a) "SMMUX_NSGFSYNR1"
#define device_bar_BDK_SMMUX_NSGFSYNR1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSGFSYNR1(a) (a)
#define arguments_BDK_SMMUX_NSGFSYNR1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nsgfsynr2
 *
 * SMMU Secure Alias to Nonsecure Global Fault Syndrome Register 2
 * Provides secure alias for nonsecure register SMMU()_(S)GFSYNR2.
 */
union bdk_smmux_nsgfsynr2
{
    uint32_t u;
    struct bdk_smmux_nsgfsynr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nsgfsynr2_s cn; */
};
typedef union bdk_smmux_nsgfsynr2 bdk_smmux_nsgfsynr2_t;

static inline uint64_t BDK_SMMUX_NSGFSYNR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSGFSYNR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000458ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000458ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000458ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSGFSYNR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSGFSYNR2(a) bdk_smmux_nsgfsynr2_t
#define bustype_BDK_SMMUX_NSGFSYNR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSGFSYNR2(a) "SMMUX_NSGFSYNR2"
#define device_bar_BDK_SMMUX_NSGFSYNR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSGFSYNR2(a) (a)
#define arguments_BDK_SMMUX_NSGFSYNR2(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_nsmiss_perf
 *
 * SMMU Nonsecure Misses Performance Counter Register
 */
union bdk_smmux_nsmiss_perf
{
    uint64_t u;
    struct bdk_smmux_nsmiss_perf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Counts the number of lookup requests in nonsecure mode which missed the IOTLB.
                                                                 Also includes sign-extension position translation faults. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Counts the number of lookup requests in nonsecure mode which missed the IOTLB.
                                                                 Also includes sign-extension position translation faults. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nsmiss_perf_s cn; */
};
typedef union bdk_smmux_nsmiss_perf bdk_smmux_nsmiss_perf_t;

static inline uint64_t BDK_SMMUX_NSMISS_PERF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSMISS_PERF(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000021030ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000021030ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000021030ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSMISS_PERF", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSMISS_PERF(a) bdk_smmux_nsmiss_perf_t
#define bustype_BDK_SMMUX_NSMISS_PERF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_NSMISS_PERF(a) "SMMUX_NSMISS_PERF"
#define device_bar_BDK_SMMUX_NSMISS_PERF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSMISS_PERF(a) (a)
#define arguments_BDK_SMMUX_NSMISS_PERF(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_nsptread_perf
 *
 * SMMU Nonsecure Page Table Reads Performance Counter Register
 */
union bdk_smmux_nsptread_perf
{
    uint64_t u;
    struct bdk_smmux_nsptread_perf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Counts the number of page table reads issued to nonsecure memory. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Counts the number of page table reads issued to nonsecure memory. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nsptread_perf_s cn; */
};
typedef union bdk_smmux_nsptread_perf bdk_smmux_nsptread_perf_t;

static inline uint64_t BDK_SMMUX_NSPTREAD_PERF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSPTREAD_PERF(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000021050ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000021050ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000021050ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSPTREAD_PERF", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSPTREAD_PERF(a) bdk_smmux_nsptread_perf_t
#define bustype_BDK_SMMUX_NSPTREAD_PERF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_NSPTREAD_PERF(a) "SMMUX_NSPTREAD_PERF"
#define device_bar_BDK_SMMUX_NSPTREAD_PERF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSPTREAD_PERF(a) (a)
#define arguments_BDK_SMMUX_NSPTREAD_PERF(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nstlbgstatus
 *
 * SMMU Secure Alias to Nonsecure Global Synchronize TLB Status Register
 * Gives the status of a TLB maintenance operation.
 */
union bdk_smmux_nstlbgstatus
{
    uint32_t u;
    struct bdk_smmux_nstlbgstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t gsactive              : 1;  /**< [  0:  0](RO/H) Global synchronize TLB invalidate active:
                                                                 0 = No global TLB synchronization operation is active.
                                                                 1 = A global TLB synchronization operation is active. */
#else /* Word 0 - Little Endian */
        uint32_t gsactive              : 1;  /**< [  0:  0](RO/H) Global synchronize TLB invalidate active:
                                                                 0 = No global TLB synchronization operation is active.
                                                                 1 = A global TLB synchronization operation is active. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nstlbgstatus_s cn; */
};
typedef union bdk_smmux_nstlbgstatus bdk_smmux_nstlbgstatus_t;

static inline uint64_t BDK_SMMUX_NSTLBGSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSTLBGSTATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000474ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000474ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000474ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSTLBGSTATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSTLBGSTATUS(a) bdk_smmux_nstlbgstatus_t
#define bustype_BDK_SMMUX_NSTLBGSTATUS(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSTLBGSTATUS(a) "SMMUX_NSTLBGSTATUS"
#define device_bar_BDK_SMMUX_NSTLBGSTATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSTLBGSTATUS(a) (a)
#define arguments_BDK_SMMUX_NSTLBGSTATUS(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_nstlbgsync
 *
 * SMMU Secure Alias to Nonsecure Global Synchronize TLB Invalidate Register
 * Starts a global synchronization operation that ensures the completion of any previously
 * accepted TLB invalidate operation.
 */
union bdk_smmux_nstlbgsync
{
    uint32_t u;
    struct bdk_smmux_nstlbgsync_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#else /* Word 0 - Little Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_nstlbgsync_s cn; */
};
typedef union bdk_smmux_nstlbgsync bdk_smmux_nstlbgsync_t;

static inline uint64_t BDK_SMMUX_NSTLBGSYNC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_NSTLBGSYNC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000470ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000470ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000470ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_NSTLBGSYNC", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_NSTLBGSYNC(a) bdk_smmux_nstlbgsync_t
#define bustype_BDK_SMMUX_NSTLBGSYNC(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_NSTLBGSYNC(a) "SMMUX_NSTLBGSYNC"
#define device_bar_BDK_SMMUX_NSTLBGSYNC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_NSTLBGSYNC(a) (a)
#define arguments_BDK_SMMUX_NSTLBGSYNC(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_pidr0
 *
 * SMMU Peripheral Identification Register 0
 */
union bdk_smmux_pidr0
{
    uint32_t u;
    struct bdk_smmux_pidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t partnum0              : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::SMMU. */
#else /* Word 0 - Little Endian */
        uint32_t partnum0              : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::SMMU. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pidr0_s cn8; */
    struct bdk_smmux_pidr0_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t partnum0              : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::SMMU3. */
#else /* Word 0 - Little Endian */
        uint32_t partnum0              : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::SMMU3. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_smmux_pidr0 bdk_smmux_pidr0_t;

static inline uint64_t BDK_SMMUX_PIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PIDR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000fe0ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000fe0ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000fe0ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000fe0ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_PIDR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_PIDR0(a) bdk_smmux_pidr0_t
#define bustype_BDK_SMMUX_PIDR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PIDR0(a) "SMMUX_PIDR0"
#define device_bar_BDK_SMMUX_PIDR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PIDR0(a) (a)
#define arguments_BDK_SMMUX_PIDR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_pidr1
 *
 * SMMU Peripheral Identification Register 1
 */
union bdk_smmux_pidr1
{
    uint32_t u;
    struct bdk_smmux_pidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t idcode                : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Cavium code is 0x4C. */
        uint32_t partnum1              : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
#else /* Word 0 - Little Endian */
        uint32_t partnum1              : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
        uint32_t idcode                : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Cavium code is 0x4C. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pidr1_s cn; */
};
typedef union bdk_smmux_pidr1 bdk_smmux_pidr1_t;

static inline uint64_t BDK_SMMUX_PIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PIDR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000fe4ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000fe4ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000fe4ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000fe4ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_PIDR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_PIDR1(a) bdk_smmux_pidr1_t
#define bustype_BDK_SMMUX_PIDR1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PIDR1(a) "SMMUX_PIDR1"
#define device_bar_BDK_SMMUX_PIDR1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PIDR1(a) (a)
#define arguments_BDK_SMMUX_PIDR1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_pidr2
 *
 * SMMU Peripheral Identification Register 2
 */
union bdk_smmux_pidr2
{
    uint32_t u;
    struct bdk_smmux_pidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) SMMU Revision.
                                                                 0x0 = SMMUv1.
                                                                 0x1 = SMMUv2. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t idcode                : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t idcode                : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) SMMU Revision.
                                                                 0x0 = SMMUv1.
                                                                 0x1 = SMMUv2. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pidr2_s cn8; */
    struct bdk_smmux_pidr2_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) SMMU Revision.
                                                                 0x0 = SMMUv1.
                                                                 0x1 = SMMUv2.
                                                                 0x2 = SMMUv3. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t idcode                : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t idcode                : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) SMMU Revision.
                                                                 0x0 = SMMUv1.
                                                                 0x1 = SMMUv2.
                                                                 0x2 = SMMUv3. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_smmux_pidr2 bdk_smmux_pidr2_t;

static inline uint64_t BDK_SMMUX_PIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PIDR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000fe8ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000fe8ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000fe8ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000fe8ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_PIDR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_PIDR2(a) bdk_smmux_pidr2_t
#define bustype_BDK_SMMUX_PIDR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PIDR2(a) "SMMUX_PIDR2"
#define device_bar_BDK_SMMUX_PIDR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PIDR2(a) (a)
#define arguments_BDK_SMMUX_PIDR2(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_pidr3
 *
 * SMMU Peripheral Identification Register 3
 */
union bdk_smmux_pidr3
{
    uint32_t u;
    struct bdk_smmux_pidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t cust                  : 4;  /**< [  3:  0](RO) Customer modified. 1 = Overall product information should be consulted for
                                                                 product, major and minor pass numbers. */
#else /* Word 0 - Little Endian */
        uint32_t cust                  : 4;  /**< [  3:  0](RO) Customer modified. 1 = Overall product information should be consulted for
                                                                 product, major and minor pass numbers. */
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pidr3_s cn; */
};
typedef union bdk_smmux_pidr3 bdk_smmux_pidr3_t;

static inline uint64_t BDK_SMMUX_PIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PIDR3(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000fecll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000fecll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000fecll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000fecll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_PIDR3", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_PIDR3(a) bdk_smmux_pidr3_t
#define bustype_BDK_SMMUX_PIDR3(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PIDR3(a) "SMMUX_PIDR3"
#define device_bar_BDK_SMMUX_PIDR3(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PIDR3(a) (a)
#define arguments_BDK_SMMUX_PIDR3(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_pidr4
 *
 * SMMU Peripheral Identification Register 4
 */
union bdk_smmux_pidr4
{
    uint32_t u;
    struct bdk_smmux_pidr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t pagecnt               : 4;  /**< [  7:  4](RO) Number of log-2 4 KB blocks occupied. */
        uint32_t jepcont               : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
#else /* Word 0 - Little Endian */
        uint32_t jepcont               : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
        uint32_t pagecnt               : 4;  /**< [  7:  4](RO) Number of log-2 4 KB blocks occupied. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pidr4_s cn; */
};
typedef union bdk_smmux_pidr4 bdk_smmux_pidr4_t;

static inline uint64_t BDK_SMMUX_PIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PIDR4(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000fd0ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000fd0ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000fd0ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000fd0ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_PIDR4", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_PIDR4(a) bdk_smmux_pidr4_t
#define bustype_BDK_SMMUX_PIDR4(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PIDR4(a) "SMMUX_PIDR4"
#define device_bar_BDK_SMMUX_PIDR4(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PIDR4(a) (a)
#define arguments_BDK_SMMUX_PIDR4(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_pidr5
 *
 * SMMU Peripheral Identification Register 5
 */
union bdk_smmux_pidr5
{
    uint32_t u;
    struct bdk_smmux_pidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pidr5_s cn; */
};
typedef union bdk_smmux_pidr5 bdk_smmux_pidr5_t;

static inline uint64_t BDK_SMMUX_PIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PIDR5(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000fd4ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000fd4ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000fd4ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000fd4ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_PIDR5", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_PIDR5(a) bdk_smmux_pidr5_t
#define bustype_BDK_SMMUX_PIDR5(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PIDR5(a) "SMMUX_PIDR5"
#define device_bar_BDK_SMMUX_PIDR5(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PIDR5(a) (a)
#define arguments_BDK_SMMUX_PIDR5(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_pidr6
 *
 * SMMU Peripheral Identification Register 6
 */
union bdk_smmux_pidr6
{
    uint32_t u;
    struct bdk_smmux_pidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pidr6_s cn; */
};
typedef union bdk_smmux_pidr6 bdk_smmux_pidr6_t;

static inline uint64_t BDK_SMMUX_PIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PIDR6(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000fd8ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000fd8ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000fd8ll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000fd8ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_PIDR6", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_PIDR6(a) bdk_smmux_pidr6_t
#define bustype_BDK_SMMUX_PIDR6(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PIDR6(a) "SMMUX_PIDR6"
#define device_bar_BDK_SMMUX_PIDR6(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PIDR6(a) (a)
#define arguments_BDK_SMMUX_PIDR6(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_pidr7
 *
 * SMMU Peripheral Identification Register 7
 */
union bdk_smmux_pidr7
{
    uint32_t u;
    struct bdk_smmux_pidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pidr7_s cn; */
};
typedef union bdk_smmux_pidr7 bdk_smmux_pidr7_t;

static inline uint64_t BDK_SMMUX_PIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PIDR7(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000fdcll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000fdcll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000fdcll + 0x1000000000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000fdcll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_PIDR7", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_PIDR7(a) bdk_smmux_pidr7_t
#define bustype_BDK_SMMUX_PIDR7(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PIDR7(a) "SMMUX_PIDR7"
#define device_bar_BDK_SMMUX_PIDR7(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PIDR7(a) (a)
#define arguments_BDK_SMMUX_PIDR7(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_aidr
 *
 * SMMU PMCG Architecture Identification Register
 */
union bdk_smmux_pmcgx_aidr
{
    uint32_t u;
    struct bdk_smmux_pmcgx_aidr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t archmajorrev          : 4;  /**< [  7:  4](RO) Architecture major revision. */
        uint32_t archminorrev          : 4;  /**< [  3:  0](RO) Architecture minor revision. */
#else /* Word 0 - Little Endian */
        uint32_t archminorrev          : 4;  /**< [  3:  0](RO) Architecture minor revision. */
        uint32_t archmajorrev          : 4;  /**< [  7:  4](RO) Architecture major revision. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_aidr_s cn; */
};
typedef union bdk_smmux_pmcgx_aidr bdk_smmux_pmcgx_aidr_t;

static inline uint64_t BDK_SMMUX_PMCGX_AIDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_AIDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e70ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_AIDR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_AIDR(a,b) bdk_smmux_pmcgx_aidr_t
#define bustype_BDK_SMMUX_PMCGX_AIDR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_AIDR(a,b) "SMMUX_PMCGX_AIDR"
#define device_bar_BDK_SMMUX_PMCGX_AIDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_AIDR(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_AIDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_pmcg#_ceid0
 *
 * SMMU PMCG Common Event ID bitmap, Lower Register
 */
union bdk_smmux_pmcgx_ceid0
{
    uint64_t u;
    struct bdk_smmux_pmcgx_ceid0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bitmap                : 64; /**< [ 63:  0](RO) 128-bit bitmap comprised of two consecutive 64-bit registers. Bit (N & 63) of the 64-bit
                                                                 word at offset 8*(N/64)
                                                                 relates to event number N. For each bit:
                                                                 0 = Event N cannot be counted by counters in this group.
                                                                 1 = Event N can be counted by counters in this group. */
#else /* Word 0 - Little Endian */
        uint64_t bitmap                : 64; /**< [ 63:  0](RO) 128-bit bitmap comprised of two consecutive 64-bit registers. Bit (N & 63) of the 64-bit
                                                                 word at offset 8*(N/64)
                                                                 relates to event number N. For each bit:
                                                                 0 = Event N cannot be counted by counters in this group.
                                                                 1 = Event N can be counted by counters in this group. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_ceid0_s cn; */
};
typedef union bdk_smmux_pmcgx_ceid0 bdk_smmux_pmcgx_ceid0_t;

static inline uint64_t BDK_SMMUX_PMCGX_CEID0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_CEID0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e20ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_CEID0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_CEID0(a,b) bdk_smmux_pmcgx_ceid0_t
#define bustype_BDK_SMMUX_PMCGX_CEID0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_CEID0(a,b) "SMMUX_PMCGX_CEID0"
#define device_bar_BDK_SMMUX_PMCGX_CEID0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_CEID0(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_CEID0(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_pmcg#_ceid1
 *
 * SMMU PMCG Common Event ID bitmap, Upper Register
 */
union bdk_smmux_pmcgx_ceid1
{
    uint64_t u;
    struct bdk_smmux_pmcgx_ceid1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bitmap                : 64; /**< [ 63:  0](RO) 128-bit bitmap comprised of two consecutive 64-bit registers. Bit (N & 63) of the 64-bit
                                                                 word at offset 8*(N/64)
                                                                 relates to event number N. For each bit,
                                                                 0 = Event N cannot be counted by counters in this group.
                                                                 1 = Event N can be counted by counters in this group. */
#else /* Word 0 - Little Endian */
        uint64_t bitmap                : 64; /**< [ 63:  0](RO) 128-bit bitmap comprised of two consecutive 64-bit registers. Bit (N & 63) of the 64-bit
                                                                 word at offset 8*(N/64)
                                                                 relates to event number N. For each bit,
                                                                 0 = Event N cannot be counted by counters in this group.
                                                                 1 = Event N can be counted by counters in this group. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_ceid1_s cn; */
};
typedef union bdk_smmux_pmcgx_ceid1 bdk_smmux_pmcgx_ceid1_t;

static inline uint64_t BDK_SMMUX_PMCGX_CEID1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_CEID1(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e28ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_CEID1", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_CEID1(a,b) bdk_smmux_pmcgx_ceid1_t
#define bustype_BDK_SMMUX_PMCGX_CEID1(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_CEID1(a,b) "SMMUX_PMCGX_CEID1"
#define device_bar_BDK_SMMUX_PMCGX_CEID1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_CEID1(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_CEID1(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_cfgr
 *
 * SMMU PMCG Configuration Register
 */
union bdk_smmux_pmcgx_cfgr
{
    uint32_t u;
    struct bdk_smmux_pmcgx_cfgr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t sid_filter_type       : 1;  /**< [ 23: 23](RO) 0 = Separate StreamID filtering is supported for each counter in the PMCG.
                                                                 1 = The StreamID filter configured by SMMU()_PMCG()_SMR(0) and
                                                                 SMMU()_PMCG()_EVTYPER(0)[FILTER_SID_SPAN] applies to all counter in the PMCG. */
        uint32_t capture               : 1;  /**< [ 22: 22](RAZ) Capture of counter values.
                                                                 0 = Capture of counter values into SVRn registers not supported (SMMU()_PMCG()_SVR() and
                                                                 SMMU()_PMCG()_CAPR are reserved.)
                                                                 1 = Capture of counter values supported. */
        uint32_t msi                   : 1;  /**< [ 21: 21](RO) Counter group supports message signaled interrupts.
                                                                 0 = Group does not support MSI.
                                                                 1 = Group can send MSI. */
        uint32_t reloc_ctrs            : 1;  /**< [ 20: 20](RO) If set, page 1 is present and the following registers are relocated to the equivalent
                                                                 offset
                                                                 on page 1 (their page 0 locations become reserved):
                                                                   * SMMU()_PMCG()_EVCNTR().
                                                                   * SMMU()_PMCG()_SVR().
                                                                   * SMMU()_PMCG()_OVSCLR0.
                                                                   * SMMU()_PMCG()_OVSSET0.
                                                                   * SMMU()_PMCG()_CAPR. */
        uint32_t reserved_14_19        : 6;
        uint32_t size                  : 6;  /**< [ 13:  8](RO) Size of PMCG counters in bits, minus one. Valid values are:
                                                                    31 = 32-bit counters.
                                                                    39 = 40-bit counters.
                                                                    43 = 44-bit counters.
                                                                    47 = 48-bit counters.
                                                                    63 = 64-bit counters.

                                                                 Other values are reserved. */
        uint32_t reserved_6_7          : 2;
        uint32_t nctr                  : 6;  /**< [  5:  0](RO) Number of counters in group minus 1. */
#else /* Word 0 - Little Endian */
        uint32_t nctr                  : 6;  /**< [  5:  0](RO) Number of counters in group minus 1. */
        uint32_t reserved_6_7          : 2;
        uint32_t size                  : 6;  /**< [ 13:  8](RO) Size of PMCG counters in bits, minus one. Valid values are:
                                                                    31 = 32-bit counters.
                                                                    39 = 40-bit counters.
                                                                    43 = 44-bit counters.
                                                                    47 = 48-bit counters.
                                                                    63 = 64-bit counters.

                                                                 Other values are reserved. */
        uint32_t reserved_14_19        : 6;
        uint32_t reloc_ctrs            : 1;  /**< [ 20: 20](RO) If set, page 1 is present and the following registers are relocated to the equivalent
                                                                 offset
                                                                 on page 1 (their page 0 locations become reserved):
                                                                   * SMMU()_PMCG()_EVCNTR().
                                                                   * SMMU()_PMCG()_SVR().
                                                                   * SMMU()_PMCG()_OVSCLR0.
                                                                   * SMMU()_PMCG()_OVSSET0.
                                                                   * SMMU()_PMCG()_CAPR. */
        uint32_t msi                   : 1;  /**< [ 21: 21](RO) Counter group supports message signaled interrupts.
                                                                 0 = Group does not support MSI.
                                                                 1 = Group can send MSI. */
        uint32_t capture               : 1;  /**< [ 22: 22](RAZ) Capture of counter values.
                                                                 0 = Capture of counter values into SVRn registers not supported (SMMU()_PMCG()_SVR() and
                                                                 SMMU()_PMCG()_CAPR are reserved.)
                                                                 1 = Capture of counter values supported. */
        uint32_t sid_filter_type       : 1;  /**< [ 23: 23](RO) 0 = Separate StreamID filtering is supported for each counter in the PMCG.
                                                                 1 = The StreamID filter configured by SMMU()_PMCG()_SMR(0) and
                                                                 SMMU()_PMCG()_EVTYPER(0)[FILTER_SID_SPAN] applies to all counter in the PMCG. */
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_cfgr_s cn; */
};
typedef union bdk_smmux_pmcgx_cfgr bdk_smmux_pmcgx_cfgr_t;

static inline uint64_t BDK_SMMUX_PMCGX_CFGR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_CFGR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e00ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_CFGR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_CFGR(a,b) bdk_smmux_pmcgx_cfgr_t
#define bustype_BDK_SMMUX_PMCGX_CFGR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_CFGR(a,b) "SMMUX_PMCGX_CFGR"
#define device_bar_BDK_SMMUX_PMCGX_CFGR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_CFGR(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_CFGR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_pmcg#_cntenclr0
 *
 * SMMU PMCG Counter Enable Clear Register
 */
union bdk_smmux_pmcgx_cntenclr0
{
    uint64_t u;
    struct bdk_smmux_pmcgx_cntenclr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t cnten                 : 4;  /**< [  3:  0](R/W1C) Counter enable. */
#else /* Word 0 - Little Endian */
        uint64_t cnten                 : 4;  /**< [  3:  0](R/W1C) Counter enable. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_cntenclr0_s cn; */
};
typedef union bdk_smmux_pmcgx_cntenclr0 bdk_smmux_pmcgx_cntenclr0_t;

static inline uint64_t BDK_SMMUX_PMCGX_CNTENCLR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_CNTENCLR0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100c20ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_CNTENCLR0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_CNTENCLR0(a,b) bdk_smmux_pmcgx_cntenclr0_t
#define bustype_BDK_SMMUX_PMCGX_CNTENCLR0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_CNTENCLR0(a,b) "SMMUX_PMCGX_CNTENCLR0"
#define device_bar_BDK_SMMUX_PMCGX_CNTENCLR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_CNTENCLR0(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_CNTENCLR0(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_pmcg#_cntenset0
 *
 * SMMU PMCG Counter Enable Set Register
 */
union bdk_smmux_pmcgx_cntenset0
{
    uint64_t u;
    struct bdk_smmux_pmcgx_cntenset0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t cnten                 : 4;  /**< [  3:  0](R/W1S) Counter enable. */
#else /* Word 0 - Little Endian */
        uint64_t cnten                 : 4;  /**< [  3:  0](R/W1S) Counter enable. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_cntenset0_s cn; */
};
typedef union bdk_smmux_pmcgx_cntenset0 bdk_smmux_pmcgx_cntenset0_t;

static inline uint64_t BDK_SMMUX_PMCGX_CNTENSET0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_CNTENSET0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100c00ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_CNTENSET0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_CNTENSET0(a,b) bdk_smmux_pmcgx_cntenset0_t
#define bustype_BDK_SMMUX_PMCGX_CNTENSET0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_CNTENSET0(a,b) "SMMUX_PMCGX_CNTENSET0"
#define device_bar_BDK_SMMUX_PMCGX_CNTENSET0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_CNTENSET0(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_CNTENSET0(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_cr
 *
 * SMMU PMCG Global Counter Enable Register
 */
union bdk_smmux_pmcgx_cr
{
    uint32_t u;
    struct bdk_smmux_pmcgx_cr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t enable                : 1;  /**< [  0:  0](R/W) Global counter enable. When clear, no events are counted and values in
                                                                 SMMU()_PMCG()_EVCNTR() do not change. This bit takes precedence over the
                                                                 SMMU()_PMCG()_CNTENSET0[CNTEN] bits. */
#else /* Word 0 - Little Endian */
        uint32_t enable                : 1;  /**< [  0:  0](R/W) Global counter enable. When clear, no events are counted and values in
                                                                 SMMU()_PMCG()_EVCNTR() do not change. This bit takes precedence over the
                                                                 SMMU()_PMCG()_CNTENSET0[CNTEN] bits. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_cr_s cn; */
};
typedef union bdk_smmux_pmcgx_cr bdk_smmux_pmcgx_cr_t;

static inline uint64_t BDK_SMMUX_PMCGX_CR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_CR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e04ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_CR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_CR(a,b) bdk_smmux_pmcgx_cr_t
#define bustype_BDK_SMMUX_PMCGX_CR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_CR(a,b) "SMMUX_PMCGX_CR"
#define device_bar_BDK_SMMUX_PMCGX_CR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_CR(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_CR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_pmcg#_evcntr#
 *
 * SMMU PMCG Event Counter Register
 */
union bdk_smmux_pmcgx_evcntrx
{
    uint64_t u;
    struct bdk_smmux_pmcgx_evcntrx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Counter value. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Counter value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_evcntrx_s cn; */
};
typedef union bdk_smmux_pmcgx_evcntrx bdk_smmux_pmcgx_evcntrx_t;

static inline uint64_t BDK_SMMUX_PMCGX_EVCNTRX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_EVCNTRX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3) && (c<=3)))
        return 0x830000110000ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_EVCNTRX", 3, a, b, c, 0);
}

#define typedef_BDK_SMMUX_PMCGX_EVCNTRX(a,b,c) bdk_smmux_pmcgx_evcntrx_t
#define bustype_BDK_SMMUX_PMCGX_EVCNTRX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_EVCNTRX(a,b,c) "SMMUX_PMCGX_EVCNTRX"
#define device_bar_BDK_SMMUX_PMCGX_EVCNTRX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_EVCNTRX(a,b,c) (a)
#define arguments_BDK_SMMUX_PMCGX_EVCNTRX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB32b) smmu#_pmcg#_evtyper#
 *
 * SMMU PMCG Event Type Configuration Register
 */
union bdk_smmux_pmcgx_evtyperx
{
    uint32_t u;
    struct bdk_smmux_pmcgx_evtyperx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t filter_sec_sid        : 1;  /**< [ 30: 30](R/W) 0 = Count events originating from non-secure StreamIDs.
                                                                 1 = Count events originating from secure StreamIDs.

                                                                 This bit is RES0 if the PMCG does not implement security support. Otherwise,
                                                                 this bit is effectively 0 if security support is implemented but secure
                                                                 observation is disabled (SMMU()_PMCG()_SCR[SO]=0).

                                                                 For event types that can be filtered on StreamID, this bit causes the StreamID
                                                                 match determined by [FILTER_SID_SPAN] and SMMU()_PMCG()_SMR()[STREAMID] to match
                                                                 secure or non-secure StreamIDs (as determined by SMMU SSD).

                                                                 Where the StreamID match span encodes `ALL', this bit selects counting of events
                                                                 associated with all non-secure StreamIDs or all secure StreamIDs. */
        uint32_t filter_sid_span       : 1;  /**< [ 29: 29](R/W) 0 = SMMU()_PMCG()_SMR()[STREAMID] filters event on an exact StreamID match (if the
                                                                     event type can be filtered on StreamID).

                                                                 1 = SMMU()_PMCG()_SMR()[STREAMID] encodes a `match span' of StreamID values.

                                                                 The span can encode `ALL', equivalent to disabling filtering on StreamID. */
        uint32_t reserved_16_28        : 13;
        uint32_t evnt                  : 16; /**< [ 15:  0](R/W) Event type that causes this counter to increment.
                                                                 Internal:
                                                                 An IMPDEF number of low-order bits of this register are implemented
                                                                 (covering the implemented event number range); unimplemented upper bits are RES0. */
#else /* Word 0 - Little Endian */
        uint32_t evnt                  : 16; /**< [ 15:  0](R/W) Event type that causes this counter to increment.
                                                                 Internal:
                                                                 An IMPDEF number of low-order bits of this register are implemented
                                                                 (covering the implemented event number range); unimplemented upper bits are RES0. */
        uint32_t reserved_16_28        : 13;
        uint32_t filter_sid_span       : 1;  /**< [ 29: 29](R/W) 0 = SMMU()_PMCG()_SMR()[STREAMID] filters event on an exact StreamID match (if the
                                                                     event type can be filtered on StreamID).

                                                                 1 = SMMU()_PMCG()_SMR()[STREAMID] encodes a `match span' of StreamID values.

                                                                 The span can encode `ALL', equivalent to disabling filtering on StreamID. */
        uint32_t filter_sec_sid        : 1;  /**< [ 30: 30](R/W) 0 = Count events originating from non-secure StreamIDs.
                                                                 1 = Count events originating from secure StreamIDs.

                                                                 This bit is RES0 if the PMCG does not implement security support. Otherwise,
                                                                 this bit is effectively 0 if security support is implemented but secure
                                                                 observation is disabled (SMMU()_PMCG()_SCR[SO]=0).

                                                                 For event types that can be filtered on StreamID, this bit causes the StreamID
                                                                 match determined by [FILTER_SID_SPAN] and SMMU()_PMCG()_SMR()[STREAMID] to match
                                                                 secure or non-secure StreamIDs (as determined by SMMU SSD).

                                                                 Where the StreamID match span encodes `ALL', this bit selects counting of events
                                                                 associated with all non-secure StreamIDs or all secure StreamIDs. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_evtyperx_s cn; */
};
typedef union bdk_smmux_pmcgx_evtyperx bdk_smmux_pmcgx_evtyperx_t;

static inline uint64_t BDK_SMMUX_PMCGX_EVTYPERX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_EVTYPERX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3) && (c<=3)))
        return 0x830000100400ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3) + 4ll * ((c) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_EVTYPERX", 3, a, b, c, 0);
}

#define typedef_BDK_SMMUX_PMCGX_EVTYPERX(a,b,c) bdk_smmux_pmcgx_evtyperx_t
#define bustype_BDK_SMMUX_PMCGX_EVTYPERX(a,b,c) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_EVTYPERX(a,b,c) "SMMUX_PMCGX_EVTYPERX"
#define device_bar_BDK_SMMUX_PMCGX_EVTYPERX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_EVTYPERX(a,b,c) (a)
#define arguments_BDK_SMMUX_PMCGX_EVTYPERX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) smmu#_pmcg#_intenclr0
 *
 * SMMU PMCG Interrupt Enable Clear Register
 */
union bdk_smmux_pmcgx_intenclr0
{
    uint64_t u;
    struct bdk_smmux_pmcgx_intenclr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t inten                 : 4;  /**< [  3:  0](R/W1C) Overflow status. */
#else /* Word 0 - Little Endian */
        uint64_t inten                 : 4;  /**< [  3:  0](R/W1C) Overflow status. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_intenclr0_s cn; */
};
typedef union bdk_smmux_pmcgx_intenclr0 bdk_smmux_pmcgx_intenclr0_t;

static inline uint64_t BDK_SMMUX_PMCGX_INTENCLR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_INTENCLR0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100c60ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_INTENCLR0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_INTENCLR0(a,b) bdk_smmux_pmcgx_intenclr0_t
#define bustype_BDK_SMMUX_PMCGX_INTENCLR0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_INTENCLR0(a,b) "SMMUX_PMCGX_INTENCLR0"
#define device_bar_BDK_SMMUX_PMCGX_INTENCLR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_INTENCLR0(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_INTENCLR0(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_pmcg#_intenset0
 *
 * SMMU PMCG Interrupt Enable Set Register
 */
union bdk_smmux_pmcgx_intenset0
{
    uint64_t u;
    struct bdk_smmux_pmcgx_intenset0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t inten                 : 4;  /**< [  3:  0](R/W1S) Counter enable. */
#else /* Word 0 - Little Endian */
        uint64_t inten                 : 4;  /**< [  3:  0](R/W1S) Counter enable. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_intenset0_s cn; */
};
typedef union bdk_smmux_pmcgx_intenset0 bdk_smmux_pmcgx_intenset0_t;

static inline uint64_t BDK_SMMUX_PMCGX_INTENSET0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_INTENSET0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100c40ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_INTENSET0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_INTENSET0(a,b) bdk_smmux_pmcgx_intenset0_t
#define bustype_BDK_SMMUX_PMCGX_INTENSET0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_INTENSET0(a,b) "SMMUX_PMCGX_INTENSET0"
#define device_bar_BDK_SMMUX_PMCGX_INTENSET0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_INTENSET0(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_INTENSET0(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_pmcg#_irq_cfg0
 *
 * SMMU PMCG MSI Configuration Register
 */
union bdk_smmux_pmcgx_irq_cfg0
{
    uint64_t u;
    struct bdk_smmux_pmcgx_irq_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t addr                  : 50; /**< [ 51:  2](R/W) IOVA of MSI target address.
                                                                 If [ADDR]=0x0, no MSI is sent. This allows a wired IRQ, if implemented, to be used instead
                                                                 of an MSI.  Address bits above and below this field are implied as zero. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 50; /**< [ 51:  2](R/W) IOVA of MSI target address.
                                                                 If [ADDR]=0x0, no MSI is sent. This allows a wired IRQ, if implemented, to be used instead
                                                                 of an MSI.  Address bits above and below this field are implied as zero. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_irq_cfg0_s cn; */
};
typedef union bdk_smmux_pmcgx_irq_cfg0 bdk_smmux_pmcgx_irq_cfg0_t;

static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CFG0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CFG0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e58ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_IRQ_CFG0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_IRQ_CFG0(a,b) bdk_smmux_pmcgx_irq_cfg0_t
#define bustype_BDK_SMMUX_PMCGX_IRQ_CFG0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_IRQ_CFG0(a,b) "SMMUX_PMCGX_IRQ_CFG0"
#define device_bar_BDK_SMMUX_PMCGX_IRQ_CFG0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_IRQ_CFG0(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_IRQ_CFG0(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_irq_cfg1
 *
 * SMMU PMCG MSI Configuration Register
 */
union bdk_smmux_pmcgx_irq_cfg1
{
    uint32_t u;
    struct bdk_smmux_pmcgx_irq_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) MSIX data payload. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) MSIX data payload. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_irq_cfg1_s cn; */
};
typedef union bdk_smmux_pmcgx_irq_cfg1 bdk_smmux_pmcgx_irq_cfg1_t;

static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CFG1(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CFG1(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e60ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_IRQ_CFG1", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_IRQ_CFG1(a,b) bdk_smmux_pmcgx_irq_cfg1_t
#define bustype_BDK_SMMUX_PMCGX_IRQ_CFG1(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_IRQ_CFG1(a,b) "SMMUX_PMCGX_IRQ_CFG1"
#define device_bar_BDK_SMMUX_PMCGX_IRQ_CFG1(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_IRQ_CFG1(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_IRQ_CFG1(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_irq_cfg2
 *
 * SMMU PMCG MSI Configuration Register
 */
union bdk_smmux_pmcgx_irq_cfg2
{
    uint32_t u;
    struct bdk_smmux_pmcgx_irq_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t sh                    : 2;  /**< [  5:  4](R/W) Shareability.
                                                                 0x0 = NSH.
                                                                 0x1 = Reserved (behaves as 0x0).
                                                                 0x2 = OSH.
                                                                 0x3 = ISH.

                                                                 When [MEMATTR] encodes a device memory type, the value of this field is ignored
                                                                 and the shareability is effectively OSH. */
        uint32_t reserved_2_3          : 2;
        uint32_t memattr               : 2;  /**< [  1:  0](R/W) MemAttr. Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
#else /* Word 0 - Little Endian */
        uint32_t memattr               : 2;  /**< [  1:  0](R/W) MemAttr. Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
        uint32_t reserved_2_3          : 2;
        uint32_t sh                    : 2;  /**< [  5:  4](R/W) Shareability.
                                                                 0x0 = NSH.
                                                                 0x1 = Reserved (behaves as 0x0).
                                                                 0x2 = OSH.
                                                                 0x3 = ISH.

                                                                 When [MEMATTR] encodes a device memory type, the value of this field is ignored
                                                                 and the shareability is effectively OSH. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_irq_cfg2_s cn; */
};
typedef union bdk_smmux_pmcgx_irq_cfg2 bdk_smmux_pmcgx_irq_cfg2_t;

static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CFG2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CFG2(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e64ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_IRQ_CFG2", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_IRQ_CFG2(a,b) bdk_smmux_pmcgx_irq_cfg2_t
#define bustype_BDK_SMMUX_PMCGX_IRQ_CFG2(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_IRQ_CFG2(a,b) "SMMUX_PMCGX_IRQ_CFG2"
#define device_bar_BDK_SMMUX_PMCGX_IRQ_CFG2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_IRQ_CFG2(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_IRQ_CFG2(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_irq_ctrl
 *
 * SMMU PMCG IRQ Enable Register
 */
union bdk_smmux_pmcgx_irq_ctrl
{
    uint32_t u;
    struct bdk_smmux_pmcgx_irq_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t irqen                 : 1;  /**< [  0:  0](R/W) Main IRQ enable for a per-counter group interrupt source. This enable
                                                                 allows/inhibits both edge-triggered wired outputs (if implemented) and MSI
                                                                 writes (if supported by the counter group). When [IRQEN] is clear, no interrupt
                                                                 is triggered regardless of individual per-counter overflow INTEN flags
                                                                 (i.e. they are overridden). [IRQEN] also controls overall interrupt
                                                                 completion/MSI configuration changes as described below. */
#else /* Word 0 - Little Endian */
        uint32_t irqen                 : 1;  /**< [  0:  0](R/W) Main IRQ enable for a per-counter group interrupt source. This enable
                                                                 allows/inhibits both edge-triggered wired outputs (if implemented) and MSI
                                                                 writes (if supported by the counter group). When [IRQEN] is clear, no interrupt
                                                                 is triggered regardless of individual per-counter overflow INTEN flags
                                                                 (i.e. they are overridden). [IRQEN] also controls overall interrupt
                                                                 completion/MSI configuration changes as described below. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_irq_ctrl_s cn; */
};
typedef union bdk_smmux_pmcgx_irq_ctrl bdk_smmux_pmcgx_irq_ctrl_t;

static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CTRL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CTRL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e50ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_IRQ_CTRL", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_IRQ_CTRL(a,b) bdk_smmux_pmcgx_irq_ctrl_t
#define bustype_BDK_SMMUX_PMCGX_IRQ_CTRL(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_IRQ_CTRL(a,b) "SMMUX_PMCGX_IRQ_CTRL"
#define device_bar_BDK_SMMUX_PMCGX_IRQ_CTRL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_IRQ_CTRL(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_IRQ_CTRL(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_irq_ctrlack
 *
 * SMMU PMCG IRQ Enable Ack Register
 * This register is a read-only copy of SMMU()_PMCG()_IRQ_CTRL.
 */
union bdk_smmux_pmcgx_irq_ctrlack
{
    uint32_t u;
    struct bdk_smmux_pmcgx_irq_ctrlack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t irqen                 : 1;  /**< [  0:  0](RO/H) Read-only hardware-modified SMMU(0)_PMCG(0..3)_IRQ_CTRL[IRQEN]. */
#else /* Word 0 - Little Endian */
        uint32_t irqen                 : 1;  /**< [  0:  0](RO/H) Read-only hardware-modified SMMU(0)_PMCG(0..3)_IRQ_CTRL[IRQEN]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_irq_ctrlack_s cn; */
};
typedef union bdk_smmux_pmcgx_irq_ctrlack bdk_smmux_pmcgx_irq_ctrlack_t;

static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CTRLACK(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_IRQ_CTRLACK(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e54ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_IRQ_CTRLACK", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_IRQ_CTRLACK(a,b) bdk_smmux_pmcgx_irq_ctrlack_t
#define bustype_BDK_SMMUX_PMCGX_IRQ_CTRLACK(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_IRQ_CTRLACK(a,b) "SMMUX_PMCGX_IRQ_CTRLACK"
#define device_bar_BDK_SMMUX_PMCGX_IRQ_CTRLACK(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_IRQ_CTRLACK(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_IRQ_CTRLACK(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_irq_status
 *
 * SMMU PMCG MSI Status Register
 */
union bdk_smmux_pmcgx_irq_status
{
    uint32_t u;
    struct bdk_smmux_pmcgx_irq_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t irq_abt               : 1;  /**< [  0:  0](RO) The SMMU sets this bit to one if it detects that an MSI has terminated with an abort.
                                                                 This bit is RES0 when SMMU()_PMCG()_CFGR[MSI]=0.
                                                                 It is implementation defined whether an implementation can detect this condition.
                                                                 This bit is cleared when SMMU()_PMCG()_IRQ_CTRL[IRQEN] is updated from zero to one.
                                                                        Note: An IRQEN transition from one to zero does not clear this bit, as this
                                                                 transition also
                                                                           ensures visibility of outstanding MSI writes and clearing [IRQ_ABT] at this point
                                                                 might
                                                                           mask possible abort completions of those MSI writes. */
#else /* Word 0 - Little Endian */
        uint32_t irq_abt               : 1;  /**< [  0:  0](RO) The SMMU sets this bit to one if it detects that an MSI has terminated with an abort.
                                                                 This bit is RES0 when SMMU()_PMCG()_CFGR[MSI]=0.
                                                                 It is implementation defined whether an implementation can detect this condition.
                                                                 This bit is cleared when SMMU()_PMCG()_IRQ_CTRL[IRQEN] is updated from zero to one.
                                                                        Note: An IRQEN transition from one to zero does not clear this bit, as this
                                                                 transition also
                                                                           ensures visibility of outstanding MSI writes and clearing [IRQ_ABT] at this point
                                                                 might
                                                                           mask possible abort completions of those MSI writes. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_irq_status_s cn; */
};
typedef union bdk_smmux_pmcgx_irq_status bdk_smmux_pmcgx_irq_status_t;

static inline uint64_t BDK_SMMUX_PMCGX_IRQ_STATUS(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_IRQ_STATUS(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100e68ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_IRQ_STATUS", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_IRQ_STATUS(a,b) bdk_smmux_pmcgx_irq_status_t
#define bustype_BDK_SMMUX_PMCGX_IRQ_STATUS(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_IRQ_STATUS(a,b) "SMMUX_PMCGX_IRQ_STATUS"
#define device_bar_BDK_SMMUX_PMCGX_IRQ_STATUS(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_IRQ_STATUS(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_IRQ_STATUS(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_pmcg#_ovsclr0
 *
 * SMMU PMCG Overflow Status Clear Register
 */
union bdk_smmux_pmcgx_ovsclr0
{
    uint64_t u;
    struct bdk_smmux_pmcgx_ovsclr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t ovs                   : 4;  /**< [  3:  0](R/W1C/H)  */
#else /* Word 0 - Little Endian */
        uint64_t ovs                   : 4;  /**< [  3:  0](R/W1C/H)  */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_ovsclr0_s cn; */
};
typedef union bdk_smmux_pmcgx_ovsclr0 bdk_smmux_pmcgx_ovsclr0_t;

static inline uint64_t BDK_SMMUX_PMCGX_OVSCLR0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_OVSCLR0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000110c80ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_OVSCLR0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_OVSCLR0(a,b) bdk_smmux_pmcgx_ovsclr0_t
#define bustype_BDK_SMMUX_PMCGX_OVSCLR0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_OVSCLR0(a,b) "SMMUX_PMCGX_OVSCLR0"
#define device_bar_BDK_SMMUX_PMCGX_OVSCLR0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_OVSCLR0(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_OVSCLR0(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_pmcg#_ovsset0
 *
 * SMMU PMCG Overflow Status Set Register
 */
union bdk_smmux_pmcgx_ovsset0
{
    uint64_t u;
    struct bdk_smmux_pmcgx_ovsset0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t ovs                   : 4;  /**< [  3:  0](R/W1S/H)  */
#else /* Word 0 - Little Endian */
        uint64_t ovs                   : 4;  /**< [  3:  0](R/W1S/H)  */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_ovsset0_s cn; */
};
typedef union bdk_smmux_pmcgx_ovsset0 bdk_smmux_pmcgx_ovsset0_t;

static inline uint64_t BDK_SMMUX_PMCGX_OVSSET0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_OVSSET0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000110cc0ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_OVSSET0", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_OVSSET0(a,b) bdk_smmux_pmcgx_ovsset0_t
#define bustype_BDK_SMMUX_PMCGX_OVSSET0(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_PMCGX_OVSSET0(a,b) "SMMUX_PMCGX_OVSSET0"
#define device_bar_BDK_SMMUX_PMCGX_OVSSET0(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_OVSSET0(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_OVSSET0(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_scr
 *
 * SMMU PMCG Secure Control Register
 */
union bdk_smmux_pmcgx_scr
{
    uint32_t u;
    struct bdk_smmux_pmcgx_scr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t valid                 : 1;  /**< [ 31: 31](SRO) Reads as one.
                                                                 Secure software can use this bit to discover security support in the PMCG. */
        uint32_t reserved_3_30         : 28;
        uint32_t nsmsi                 : 1;  /**< [  2:  2](SR/W) Non-secure MSI-X.
                                                                    0 = Generated MSIs have an NS=0 attribute.
                                                                    1 = Generated MSIs have an NS=1 attribute. */
        uint32_t nsra                  : 1;  /**< [  1:  1](SR/W) Non-secure register access.
                                                                 0 = Non-secure register access is disabled.
                                                                     Non-secure access to any PMCG register is RAZ/WI.
                                                                 1 = Non-secure register access is enabled.
                                                                     If the PMCG supports MSIs, generated MSIs have an NS=1 attribute. */
        uint32_t so                    : 1;  /**< [  0:  0](SR/W) Secure observation.
                                                                 0 = Secure observation is disabled.
                                                                     SMMU()_PMCG()_EVTYPER()[FILTER_SEC_SID] is effectively 0.
                                                                 1 = Secure observation is enabled. */
#else /* Word 0 - Little Endian */
        uint32_t so                    : 1;  /**< [  0:  0](SR/W) Secure observation.
                                                                 0 = Secure observation is disabled.
                                                                     SMMU()_PMCG()_EVTYPER()[FILTER_SEC_SID] is effectively 0.
                                                                 1 = Secure observation is enabled. */
        uint32_t nsra                  : 1;  /**< [  1:  1](SR/W) Non-secure register access.
                                                                 0 = Non-secure register access is disabled.
                                                                     Non-secure access to any PMCG register is RAZ/WI.
                                                                 1 = Non-secure register access is enabled.
                                                                     If the PMCG supports MSIs, generated MSIs have an NS=1 attribute. */
        uint32_t nsmsi                 : 1;  /**< [  2:  2](SR/W) Non-secure MSI-X.
                                                                    0 = Generated MSIs have an NS=0 attribute.
                                                                    1 = Generated MSIs have an NS=1 attribute. */
        uint32_t reserved_3_30         : 28;
        uint32_t valid                 : 1;  /**< [ 31: 31](SRO) Reads as one.
                                                                 Secure software can use this bit to discover security support in the PMCG. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_scr_s cn; */
};
typedef union bdk_smmux_pmcgx_scr bdk_smmux_pmcgx_scr_t;

static inline uint64_t BDK_SMMUX_PMCGX_SCR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_SCR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3)))
        return 0x830000100df8ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3);
    __bdk_csr_fatal("SMMUX_PMCGX_SCR", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_PMCGX_SCR(a,b) bdk_smmux_pmcgx_scr_t
#define bustype_BDK_SMMUX_PMCGX_SCR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_SCR(a,b) "SMMUX_PMCGX_SCR"
#define device_bar_BDK_SMMUX_PMCGX_SCR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_SCR(a,b) (a)
#define arguments_BDK_SMMUX_PMCGX_SCR(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_pmcg#_smr#
 *
 * SMMU PMCG Counter Stream Match Filter Register
 */
union bdk_smmux_pmcgx_smrx
{
    uint32_t u;
    struct bdk_smmux_pmcgx_smrx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t streamid              : 32; /**< [ 31:  0](R/W) When the corresponding SMMU()_PMCG()_EVTYPER()[EVNT] indicates an event that cannot be
                                                                 filtered on StreamID, the value in this register is ignored. Otherwise:

                                                                 When the corresponding SMMU()_PMCG()_EVTYPER()[FILTER_SID_SPAN]=0, counter `n' only
                                                                 counts events associated with a StreamID matching this field exactly.

                                                                 When SMMU()_PMCG()_EVTYPER()[FILTER_SID_SPAN]=1, this field is encoded such that the
                                                                 least-significant zero bit indicates the uppermost of a contiguous span of
                                                                 least-significant StreamID bits that are ignored for the purposes of filtering
                                                                 on a StreamID match. Bits above this position match the corresponding bits in an
                                                                 event's StreamID for the event to be counted and bits below this position down
                                                                 to bit 0 are 1. When all implemented bits are 1, any StreamID is
                                                                 matched. See Section 12.4.  When secure observation is enabled,
                                                                 SMMU()_PMCG()_EVTYPER()[FILTER_SEC_SID] determines whether the StreamID is matched
                                                                 from secure or non-secure StreamID spaces (as defined by SMMU SSD).

                                                                 This field implements an implementation defined number of contiguous bits (from
                                                                 0 upwards) corresponding to the PMCG StreamID size. Bits outside this range read
                                                                 as zero, writes ignored (RAZ/WI). */
#else /* Word 0 - Little Endian */
        uint32_t streamid              : 32; /**< [ 31:  0](R/W) When the corresponding SMMU()_PMCG()_EVTYPER()[EVNT] indicates an event that cannot be
                                                                 filtered on StreamID, the value in this register is ignored. Otherwise:

                                                                 When the corresponding SMMU()_PMCG()_EVTYPER()[FILTER_SID_SPAN]=0, counter `n' only
                                                                 counts events associated with a StreamID matching this field exactly.

                                                                 When SMMU()_PMCG()_EVTYPER()[FILTER_SID_SPAN]=1, this field is encoded such that the
                                                                 least-significant zero bit indicates the uppermost of a contiguous span of
                                                                 least-significant StreamID bits that are ignored for the purposes of filtering
                                                                 on a StreamID match. Bits above this position match the corresponding bits in an
                                                                 event's StreamID for the event to be counted and bits below this position down
                                                                 to bit 0 are 1. When all implemented bits are 1, any StreamID is
                                                                 matched. See Section 12.4.  When secure observation is enabled,
                                                                 SMMU()_PMCG()_EVTYPER()[FILTER_SEC_SID] determines whether the StreamID is matched
                                                                 from secure or non-secure StreamID spaces (as defined by SMMU SSD).

                                                                 This field implements an implementation defined number of contiguous bits (from
                                                                 0 upwards) corresponding to the PMCG StreamID size. Bits outside this range read
                                                                 as zero, writes ignored (RAZ/WI). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_pmcgx_smrx_s cn; */
};
typedef union bdk_smmux_pmcgx_smrx bdk_smmux_pmcgx_smrx_t;

static inline uint64_t BDK_SMMUX_PMCGX_SMRX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_PMCGX_SMRX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=3) && (c==0)))
        return 0x830000100a00ll + 0x1000000000ll * ((a) & 0x0) + 0x20000ll * ((b) & 0x3) + 4ll * ((c) & 0x0);
    __bdk_csr_fatal("SMMUX_PMCGX_SMRX", 3, a, b, c, 0);
}

#define typedef_BDK_SMMUX_PMCGX_SMRX(a,b,c) bdk_smmux_pmcgx_smrx_t
#define bustype_BDK_SMMUX_PMCGX_SMRX(a,b,c) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_PMCGX_SMRX(a,b,c) "SMMUX_PMCGX_SMRX"
#define device_bar_BDK_SMMUX_PMCGX_SMRX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_PMCGX_SMRX(a,b,c) (a)
#define arguments_BDK_SMMUX_PMCGX_SMRX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB32b) smmu#_s2cr#
 *
 * SMMU Stream to Context Register
 * Specifies the translation context for processing a transaction where the transaction matches
 * the stream mapping group to which this register belongs.
 * An SMMU()_S2CR() register reserved by secure software using
 * SMMU()_SCR1[NSNUMSMRGO] must only specify a translation context bank that is reserved by
 * secure software. An SMMU()_S2CR() register that is accessible from the nonsecure
 * state must only specify a translation context bank that is not reserved by secure software
 */
union bdk_smmux_s2crx
{
    uint32_t u;
    struct bdk_smmux_s2crx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t imp                   : 2;  /**< [ 31: 30](RAZ) Reserved. */
        uint32_t transientcfg          : 2;  /**< [ 29: 28](RO) For CTYPE=0 or 1, transient allocate configuration.

                                                                 0x0 = Use the default transient allocation attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Non-transient.
                                                                 0x3 = Transient.

                                                                 For CTYPE=2, reserved.

                                                                 In CNXXXX this field is not implemented. */
        uint32_t instcfg_fb            : 2;  /**< [ 27: 26](RAZ) For CTYPE=0, \<27:26\> is INSTCFG, instruction fetch attribute configuration. This
                                                                 field does not apply to writes.
                                                                   0x0 = Default instruction fetch attribute.
                                                                   0x1 = Reserved.
                                                                   0x2 = Data.
                                                                   0x3 = Instruction.

                                                                 For CTYPE=1, \<27\> reserved, \<26\> is FB, force broadcast. Force broadcast of TLB and
                                                                 instruction cache maintenance operations. Ignored in CNXXXX, as NCB clients do not
                                                                 initiate invalidates.

                                                                 For CTYPE=2, reserved. */
        uint32_t privcfg_bsu           : 2;  /**< [ 25: 24](R/W) For CTYPE=0, PRIVCFG, privileged attribute configuration.

                                                                 0x0 = Default privilege attribute.

                                                                 0x1 = Privledged access never.  This encoding is reserved if SMMU()_IDR2[DIPANS] is
                                                                     clear.
                                                                     When a context bank is configured to use this encoding, then any transaction from
                                                                     the upstream device is considered to be marked as privileged and any attempt to access
                                                                     a user-accessible page will result in a permission fault.  Thus a device that is
                                                                     expected to operate only on privileged data will fault if it is misprogrammed and
                                                                     tries to access user data accessible through the corresponding context bank.
                                                                     For SMMU()_S2CR() that are configured as bypass, then there is no associated
                                                                     context bank and no permission checks.
                                                                     Thus the only effect of this bit is to mark the downstream transaction as privileged;
                                                                     it behaves identically to encoding 0x3, "Privileged".
                                                                     For E2HC banks then there are two levels of privilege and this encoding behaves as
                                                                     normal.

                                                                 0x2 = Unprivileged.

                                                                 0x3 = Privileged.

                                                                 For CTYPE=1, BSU, barrier shareability upgrade. Ignored in CNXXXX.

                                                                 For CTYPE=2, reserved. */
        uint32_t wacfg                 : 2;  /**< [ 23: 22](RO) For CTYPE=0 or 1, write allocate configuration.

                                                                 0x0 = Default allocation attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Write-allocate.
                                                                 0x3 = No write-allocate.

                                                                 For CTYPE=2, reserved.

                                                                 For CNXXXX not implemented. */
        uint32_t racfg                 : 2;  /**< [ 21: 20](RO) For CTYPE=0 or 1, read allocate configuration.

                                                                 0x0 = Default allocation attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Read-allocate.
                                                                 0x3 = No read-allocate.

                                                                 For CTYPE=2, reserved.

                                                                 For CNXXXX not implemented. */
        uint32_t nscfg                 : 2;  /**< [ 19: 18](SR/W) For CTYPE=0 or 1, Nonsecure configuration.

                                                                 0x0 = Default security attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Secure configuration.
                                                                 0x3 = Non secure configuration.

                                                                 For CTYPE=2, reserved.

                                                                 This field exists only for secure stream mapping register groups. */
        uint32_t ctype                 : 2;  /**< [ 17: 16](R/W) Context register type. Indicates the meaning of the remaining fields in this register:
                                                                 0x0 = Translation context bank index.
                                                                 0x1 = Bypass mode.
                                                                 0x2 = Fault, no index.
                                                                 0x3 = Reserved. */
        uint32_t memattr               : 4;  /**< [ 15: 12](R/W) For CTYPE=0 or 1, memory attributes.

                                                                 For CTYPE=2, reserved. */
        uint32_t mtcfg                 : 1;  /**< [ 11: 11](R/W) For CTYPE=0 or 1, memory type configuration.

                                                                 0 = Default memory attributes.
                                                                 1 = [MEMATTR] field attributes.

                                                                 For CTYPE=2, reserved. */
        uint32_t exidvalid             : 1;  /**< [ 10: 10](R/W) Extended ID valid.
                                                                 0 = The stream match register group is valid if SMMU()_SMR()[VALID] is set and
                                                                 SMMU()_(S)CR0[EXIDENABLE] is clear, for backward compatibility.
                                                                 1 = The stream match register group is valid and SMMU()_SMR()[VALID] is used as
                                                                 an extra mask bit. CNXXXX recommends this setting. */
        uint32_t shcfg                 : 2;  /**< [  9:  8](RO) For CTYPE=0 or 1, Sharability configuration.
                                                                 0x0 = Default sharability attribute.
                                                                 0x1 = Outer sharable.
                                                                 0x2 = Inner sharable.
                                                                 0x3 = Non-sharable.

                                                                 For CTYPE=2, reserved.

                                                                 For CNXXXX not implemented. */
        uint32_t cbndx                 : 8;  /**< [  7:  0](R/W) For CTYPE=0, Context bank index.

                                                                 For CTYPE=1, VMID, not implemented in CNXXXX.

                                                                 For CTYPE=2, reserved.

                                                                 A secure SMMU()_S2CR() register configured to specify a translation context bank
                                                                 is only permitted to specify a CBNDX corresponding to a translation context bank that is
                                                                 also reserved by secure software, or specify a translation context bank configured for the
                                                                 Stage 1 context with stage 2 bypass format. */
#else /* Word 0 - Little Endian */
        uint32_t cbndx                 : 8;  /**< [  7:  0](R/W) For CTYPE=0, Context bank index.

                                                                 For CTYPE=1, VMID, not implemented in CNXXXX.

                                                                 For CTYPE=2, reserved.

                                                                 A secure SMMU()_S2CR() register configured to specify a translation context bank
                                                                 is only permitted to specify a CBNDX corresponding to a translation context bank that is
                                                                 also reserved by secure software, or specify a translation context bank configured for the
                                                                 Stage 1 context with stage 2 bypass format. */
        uint32_t shcfg                 : 2;  /**< [  9:  8](RO) For CTYPE=0 or 1, Sharability configuration.
                                                                 0x0 = Default sharability attribute.
                                                                 0x1 = Outer sharable.
                                                                 0x2 = Inner sharable.
                                                                 0x3 = Non-sharable.

                                                                 For CTYPE=2, reserved.

                                                                 For CNXXXX not implemented. */
        uint32_t exidvalid             : 1;  /**< [ 10: 10](R/W) Extended ID valid.
                                                                 0 = The stream match register group is valid if SMMU()_SMR()[VALID] is set and
                                                                 SMMU()_(S)CR0[EXIDENABLE] is clear, for backward compatibility.
                                                                 1 = The stream match register group is valid and SMMU()_SMR()[VALID] is used as
                                                                 an extra mask bit. CNXXXX recommends this setting. */
        uint32_t mtcfg                 : 1;  /**< [ 11: 11](R/W) For CTYPE=0 or 1, memory type configuration.

                                                                 0 = Default memory attributes.
                                                                 1 = [MEMATTR] field attributes.

                                                                 For CTYPE=2, reserved. */
        uint32_t memattr               : 4;  /**< [ 15: 12](R/W) For CTYPE=0 or 1, memory attributes.

                                                                 For CTYPE=2, reserved. */
        uint32_t ctype                 : 2;  /**< [ 17: 16](R/W) Context register type. Indicates the meaning of the remaining fields in this register:
                                                                 0x0 = Translation context bank index.
                                                                 0x1 = Bypass mode.
                                                                 0x2 = Fault, no index.
                                                                 0x3 = Reserved. */
        uint32_t nscfg                 : 2;  /**< [ 19: 18](SR/W) For CTYPE=0 or 1, Nonsecure configuration.

                                                                 0x0 = Default security attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Secure configuration.
                                                                 0x3 = Non secure configuration.

                                                                 For CTYPE=2, reserved.

                                                                 This field exists only for secure stream mapping register groups. */
        uint32_t racfg                 : 2;  /**< [ 21: 20](RO) For CTYPE=0 or 1, read allocate configuration.

                                                                 0x0 = Default allocation attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Read-allocate.
                                                                 0x3 = No read-allocate.

                                                                 For CTYPE=2, reserved.

                                                                 For CNXXXX not implemented. */
        uint32_t wacfg                 : 2;  /**< [ 23: 22](RO) For CTYPE=0 or 1, write allocate configuration.

                                                                 0x0 = Default allocation attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Write-allocate.
                                                                 0x3 = No write-allocate.

                                                                 For CTYPE=2, reserved.

                                                                 For CNXXXX not implemented. */
        uint32_t privcfg_bsu           : 2;  /**< [ 25: 24](R/W) For CTYPE=0, PRIVCFG, privileged attribute configuration.

                                                                 0x0 = Default privilege attribute.

                                                                 0x1 = Privledged access never.  This encoding is reserved if SMMU()_IDR2[DIPANS] is
                                                                     clear.
                                                                     When a context bank is configured to use this encoding, then any transaction from
                                                                     the upstream device is considered to be marked as privileged and any attempt to access
                                                                     a user-accessible page will result in a permission fault.  Thus a device that is
                                                                     expected to operate only on privileged data will fault if it is misprogrammed and
                                                                     tries to access user data accessible through the corresponding context bank.
                                                                     For SMMU()_S2CR() that are configured as bypass, then there is no associated
                                                                     context bank and no permission checks.
                                                                     Thus the only effect of this bit is to mark the downstream transaction as privileged;
                                                                     it behaves identically to encoding 0x3, "Privileged".
                                                                     For E2HC banks then there are two levels of privilege and this encoding behaves as
                                                                     normal.

                                                                 0x2 = Unprivileged.

                                                                 0x3 = Privileged.

                                                                 For CTYPE=1, BSU, barrier shareability upgrade. Ignored in CNXXXX.

                                                                 For CTYPE=2, reserved. */
        uint32_t instcfg_fb            : 2;  /**< [ 27: 26](RAZ) For CTYPE=0, \<27:26\> is INSTCFG, instruction fetch attribute configuration. This
                                                                 field does not apply to writes.
                                                                   0x0 = Default instruction fetch attribute.
                                                                   0x1 = Reserved.
                                                                   0x2 = Data.
                                                                   0x3 = Instruction.

                                                                 For CTYPE=1, \<27\> reserved, \<26\> is FB, force broadcast. Force broadcast of TLB and
                                                                 instruction cache maintenance operations. Ignored in CNXXXX, as NCB clients do not
                                                                 initiate invalidates.

                                                                 For CTYPE=2, reserved. */
        uint32_t transientcfg          : 2;  /**< [ 29: 28](RO) For CTYPE=0 or 1, transient allocate configuration.

                                                                 0x0 = Use the default transient allocation attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Non-transient.
                                                                 0x3 = Transient.

                                                                 For CTYPE=2, reserved.

                                                                 In CNXXXX this field is not implemented. */
        uint32_t imp                   : 2;  /**< [ 31: 30](RAZ) Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s2crx_s cn; */
};
typedef union bdk_smmux_s2crx bdk_smmux_s2crx_t;

static inline uint64_t BDK_SMMUX_S2CRX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S2CRX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=127)))
        return 0x830000000c00ll + 0x1000000000ll * ((a) & 0x0) + 4ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830000000c00ll + 0x1000000000ll * ((a) & 0x1) + 4ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830000000c00ll + 0x1000000000ll * ((a) & 0x3) + 4ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_S2CRX", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_S2CRX(a,b) bdk_smmux_s2crx_t
#define bustype_BDK_SMMUX_S2CRX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S2CRX(a,b) "SMMUX_S2CRX"
#define device_bar_BDK_SMMUX_S2CRX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S2CRX(a,b) (a)
#define arguments_BDK_SMMUX_S2CRX(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_s_agbpa
 *
 * SMMU Secure Alternate Global Bypass Attribute Register
 * This register is intended to allow an implementation to apply an additional non-
 * architected attributes or tag to bypassing transactions, for example a traffic
 * routing identifier.
 *
 * If this field is unsupported by an implementation, it is RES0.  It is not
 * intended for this register to be used to further modify existing architected
 * bypass attributes which are controlled using GPBA.
 */
union bdk_smmux_s_agbpa
{
    uint32_t u;
    struct bdk_smmux_s_agbpa_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_17_31        : 15;
        uint32_t qos                   : 1;  /**< [ 16: 16](SR/W) Quality-of-service for bypassed transactions. */
        uint32_t reserved_8_15         : 8;
        uint32_t cpid                  : 8;  /**< [  7:  0](SR/W) Cache partition ID for bypassed transactions. */
#else /* Word 0 - Little Endian */
        uint32_t cpid                  : 8;  /**< [  7:  0](SR/W) Cache partition ID for bypassed transactions. */
        uint32_t reserved_8_15         : 8;
        uint32_t qos                   : 1;  /**< [ 16: 16](SR/W) Quality-of-service for bypassed transactions. */
        uint32_t reserved_17_31        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_agbpa_s cn; */
};
typedef union bdk_smmux_s_agbpa bdk_smmux_s_agbpa_t;

static inline uint64_t BDK_SMMUX_S_AGBPA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_AGBPA(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008048ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_AGBPA", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_AGBPA(a) bdk_smmux_s_agbpa_t
#define bustype_BDK_SMMUX_S_AGBPA(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_AGBPA(a) "SMMUX_S_AGBPA"
#define device_bar_BDK_SMMUX_S_AGBPA(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_AGBPA(a) (a)
#define arguments_BDK_SMMUX_S_AGBPA(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_cmdq_base
 *
 * SMMU Secure Command Queue Base Register
 */
union bdk_smmux_s_cmdq_base
{
    uint64_t u;
    struct bdk_smmux_s_cmdq_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t ra                    : 1;  /**< [ 62: 62](SR/W) Read allocate hint.
                                                                 0 = No read-allocate.
                                                                 1 = Read-allocate. */
        uint64_t reserved_52_61        : 10;
        uint64_t addr                  : 47; /**< [ 51:  5](SR/W) PA of queue base.
                                                                 The effective address has \<63:52\> = 0x0 and \<4:0\> = 0x0. */
        uint64_t log2size              : 5;  /**< [  4:  0](SR/W) Queue size as log2(entries).
                                                                 Except for the purposes of readback of this register, any use of this field's
                                                                 value is capped at the maximum, SMMU()_IDR1[CMDQS].
                                                                 The minimum size is zero for one entry, but this must be aligned to a 32-byte (2
                                                                 entry) boundary as above. */
#else /* Word 0 - Little Endian */
        uint64_t log2size              : 5;  /**< [  4:  0](SR/W) Queue size as log2(entries).
                                                                 Except for the purposes of readback of this register, any use of this field's
                                                                 value is capped at the maximum, SMMU()_IDR1[CMDQS].
                                                                 The minimum size is zero for one entry, but this must be aligned to a 32-byte (2
                                                                 entry) boundary as above. */
        uint64_t addr                  : 47; /**< [ 51:  5](SR/W) PA of queue base.
                                                                 The effective address has \<63:52\> = 0x0 and \<4:0\> = 0x0. */
        uint64_t reserved_52_61        : 10;
        uint64_t ra                    : 1;  /**< [ 62: 62](SR/W) Read allocate hint.
                                                                 0 = No read-allocate.
                                                                 1 = Read-allocate. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_cmdq_base_s cn; */
};
typedef union bdk_smmux_s_cmdq_base bdk_smmux_s_cmdq_base_t;

static inline uint64_t BDK_SMMUX_S_CMDQ_BASE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_CMDQ_BASE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008090ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_CMDQ_BASE", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_CMDQ_BASE(a) bdk_smmux_s_cmdq_base_t
#define bustype_BDK_SMMUX_S_CMDQ_BASE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_CMDQ_BASE(a) "SMMUX_S_CMDQ_BASE"
#define device_bar_BDK_SMMUX_S_CMDQ_BASE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_CMDQ_BASE(a) (a)
#define arguments_BDK_SMMUX_S_CMDQ_BASE(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_cmdq_cons
 *
 * SMMU Secure Command Queue Consumer Register
 */
union bdk_smmux_s_cmdq_cons
{
    uint32_t u;
    struct bdk_smmux_s_cmdq_cons_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t errx                  : 7;  /**< [ 30: 24](SRO/H) Error reason code.
                                                                 When a command execution error is detected, set to a reason code and then the
                                                                 SMMU()_S_GERROR[CMDQ_ERR] global error becomes active (is toggled by the SMMU).
                                                                 The value in this field becomes unknown when the SMMU()_S_GERROR[CMDQ_ERR]
                                                                 global error is deactivated.
                                                                 Software should ignore this field unless the error is active. */
        uint32_t reserved_20_23        : 4;
        uint32_t rd                    : 20; /**< [ 19:  0](SR/W/H) Queue read index + wrap flag. Updated by the SMMU (consumer) indicating which
                                                                 command entry has just been executed. */
#else /* Word 0 - Little Endian */
        uint32_t rd                    : 20; /**< [ 19:  0](SR/W/H) Queue read index + wrap flag. Updated by the SMMU (consumer) indicating which
                                                                 command entry has just been executed. */
        uint32_t reserved_20_23        : 4;
        uint32_t errx                  : 7;  /**< [ 30: 24](SRO/H) Error reason code.
                                                                 When a command execution error is detected, set to a reason code and then the
                                                                 SMMU()_S_GERROR[CMDQ_ERR] global error becomes active (is toggled by the SMMU).
                                                                 The value in this field becomes unknown when the SMMU()_S_GERROR[CMDQ_ERR]
                                                                 global error is deactivated.
                                                                 Software should ignore this field unless the error is active. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_cmdq_cons_s cn; */
};
typedef union bdk_smmux_s_cmdq_cons bdk_smmux_s_cmdq_cons_t;

static inline uint64_t BDK_SMMUX_S_CMDQ_CONS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_CMDQ_CONS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x83000000809cll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_CMDQ_CONS", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_CMDQ_CONS(a) bdk_smmux_s_cmdq_cons_t
#define bustype_BDK_SMMUX_S_CMDQ_CONS(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_CMDQ_CONS(a) "SMMUX_S_CMDQ_CONS"
#define device_bar_BDK_SMMUX_S_CMDQ_CONS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_CMDQ_CONS(a) (a)
#define arguments_BDK_SMMUX_S_CMDQ_CONS(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_cmdq_prod
 *
 * SMMU Secure Command Queue Producer Register
 */
union bdk_smmux_s_cmdq_prod
{
    uint32_t u;
    struct bdk_smmux_s_cmdq_prod_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t wr                    : 20; /**< [ 19:  0](SR/W) Queue write index + wrap flag. Updated by the CPU (producer) indicating the next
                                                                 empty space in the queue after new data. */
#else /* Word 0 - Little Endian */
        uint32_t wr                    : 20; /**< [ 19:  0](SR/W) Queue write index + wrap flag. Updated by the CPU (producer) indicating the next
                                                                 empty space in the queue after new data. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_cmdq_prod_s cn; */
};
typedef union bdk_smmux_s_cmdq_prod bdk_smmux_s_cmdq_prod_t;

static inline uint64_t BDK_SMMUX_S_CMDQ_PROD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_CMDQ_PROD(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008098ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_CMDQ_PROD", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_CMDQ_PROD(a) bdk_smmux_s_cmdq_prod_t
#define bustype_BDK_SMMUX_S_CMDQ_PROD(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_CMDQ_PROD(a) "SMMUX_S_CMDQ_PROD"
#define device_bar_BDK_SMMUX_S_CMDQ_PROD(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_CMDQ_PROD(a) (a)
#define arguments_BDK_SMMUX_S_CMDQ_PROD(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_cr0
 *
 * SMMU Secure Control 0 Register
 * An update to a field in SMMU()_S_CR0 is not considered complete, along with any
 * side effects, until the respective field in SMMU()_S_CR0ACK is observed to take the
 * new value.
 */
union bdk_smmux_s_cr0
{
    uint32_t u;
    struct bdk_smmux_s_cr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t nsstalld              : 1;  /**< [  9:  9](SRO) Non-secure stall disable.
                                                                 0 = Nonsecure programming interface may use stalling fault model, if
                                                                 implemented.

                                                                 1 = Nonsecure programming interface prohibited from using stalling fault
                                                                 model, if implemented.

                                                                 For CNXXXX, always stall, so zero.

                                                                 Internal:
                                                                 When SMMU()_S_IDR0[STALL_MODEL]=0x0 (both stall and terminate models available),
                                                                 setting this bit modifies the non-secure behavior such that only the terminate
                                                                 model is available for non-secure streams and SMMU()_IDR0[STALL_MODEL] reads as
                                                                 0x1 (terminate-only).

                                                                 When SMMU()_S_IDR0[STALL_MODEL]!=0x0, this bit is RES0.

                                                                 A reserved SMMU()_S_CR0 bit is not reflected into SMMU()_S_CR0ACK. */
        uint32_t reserved_6_8          : 3;
        uint32_t sif                   : 1;  /**< [  5:  5](SR/W) Secure instruction fetch.
                                                                 0 = Secure transactions may exit the SMMU as a non-secure instruction fetch.
                                                                 1 = Secure transactions determined to be non-secure instruction fetch are
                                                                 terminated with abort.

                                                                 This field causes transactions from a secure stream (as determined by SSD) that
                                                                 are determined to be an instruction fetch (after INSTCFG fields are applied) to
                                                                 experience a permission fault if their effective output NS attribute is
                                                                 non-secure (NS=1).

                                                                 When translation is disabled due to SMMUEN=0, the transaction is terminated with
                                                                 abort and no SMMU_F_PERMISSION_S event is recorded.

                                                                 When SMMUEN is set and the event queue is writable, a SMMU_F_PERMISSION_S event is
                                                                 recorded, and:

                                                                 * If stream translation is disabled (SMMU_STE_S[CONFIG] selects bypass), the
                                                                 faulting transaction is terminated with abort.

                                                                 * If stream translation is enabled (SMMU_STE_S[CONFIG] enables stage 1),
                                                                 CD.{A,R,S} govern stall/terminate behavior.

                                                                 The fault event is a stage 1 permission fault as, by definition, a secure
                                                                 transaction has only stage 1 configuration (that is, has no option to have stage 2
                                                                 translation).

                                                                 This bit is permitted to be cached in a TLB or configuration cache; an update of
                                                                 this bit requires invalidation of all secure TLB entries and configuration caches. */
        uint32_t reserved_4            : 1;
        uint32_t cmdqen                : 1;  /**< [  3:  3](SR/W) Enable secure command queue processing. */
        uint32_t eventqen              : 1;  /**< [  2:  2](SR/W) Enable secure EventQ writes. */
        uint32_t reserved_1            : 1;
        uint32_t smmuen                : 1;  /**< [  0:  0](SR/W) Secure SMMU enable. Enables the secure SMMU interface and allows secure traffic
                                                                 to enter the SMMU. When disabled, secure traffic bypasses the SMMU. Note the
                                                                 independent non-secure interface might remain active. */
#else /* Word 0 - Little Endian */
        uint32_t smmuen                : 1;  /**< [  0:  0](SR/W) Secure SMMU enable. Enables the secure SMMU interface and allows secure traffic
                                                                 to enter the SMMU. When disabled, secure traffic bypasses the SMMU. Note the
                                                                 independent non-secure interface might remain active. */
        uint32_t reserved_1            : 1;
        uint32_t eventqen              : 1;  /**< [  2:  2](SR/W) Enable secure EventQ writes. */
        uint32_t cmdqen                : 1;  /**< [  3:  3](SR/W) Enable secure command queue processing. */
        uint32_t reserved_4            : 1;
        uint32_t sif                   : 1;  /**< [  5:  5](SR/W) Secure instruction fetch.
                                                                 0 = Secure transactions may exit the SMMU as a non-secure instruction fetch.
                                                                 1 = Secure transactions determined to be non-secure instruction fetch are
                                                                 terminated with abort.

                                                                 This field causes transactions from a secure stream (as determined by SSD) that
                                                                 are determined to be an instruction fetch (after INSTCFG fields are applied) to
                                                                 experience a permission fault if their effective output NS attribute is
                                                                 non-secure (NS=1).

                                                                 When translation is disabled due to SMMUEN=0, the transaction is terminated with
                                                                 abort and no SMMU_F_PERMISSION_S event is recorded.

                                                                 When SMMUEN is set and the event queue is writable, a SMMU_F_PERMISSION_S event is
                                                                 recorded, and:

                                                                 * If stream translation is disabled (SMMU_STE_S[CONFIG] selects bypass), the
                                                                 faulting transaction is terminated with abort.

                                                                 * If stream translation is enabled (SMMU_STE_S[CONFIG] enables stage 1),
                                                                 CD.{A,R,S} govern stall/terminate behavior.

                                                                 The fault event is a stage 1 permission fault as, by definition, a secure
                                                                 transaction has only stage 1 configuration (that is, has no option to have stage 2
                                                                 translation).

                                                                 This bit is permitted to be cached in a TLB or configuration cache; an update of
                                                                 this bit requires invalidation of all secure TLB entries and configuration caches. */
        uint32_t reserved_6_8          : 3;
        uint32_t nsstalld              : 1;  /**< [  9:  9](SRO) Non-secure stall disable.
                                                                 0 = Nonsecure programming interface may use stalling fault model, if
                                                                 implemented.

                                                                 1 = Nonsecure programming interface prohibited from using stalling fault
                                                                 model, if implemented.

                                                                 For CNXXXX, always stall, so zero.

                                                                 Internal:
                                                                 When SMMU()_S_IDR0[STALL_MODEL]=0x0 (both stall and terminate models available),
                                                                 setting this bit modifies the non-secure behavior such that only the terminate
                                                                 model is available for non-secure streams and SMMU()_IDR0[STALL_MODEL] reads as
                                                                 0x1 (terminate-only).

                                                                 When SMMU()_S_IDR0[STALL_MODEL]!=0x0, this bit is RES0.

                                                                 A reserved SMMU()_S_CR0 bit is not reflected into SMMU()_S_CR0ACK. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_cr0_s cn; */
};
typedef union bdk_smmux_s_cr0 bdk_smmux_s_cr0_t;

static inline uint64_t BDK_SMMUX_S_CR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_CR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008020ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_CR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_CR0(a) bdk_smmux_s_cr0_t
#define bustype_BDK_SMMUX_S_CR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_CR0(a) "SMMUX_S_CR0"
#define device_bar_BDK_SMMUX_S_CR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_CR0(a) (a)
#define arguments_BDK_SMMUX_S_CR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_cr0ack
 *
 * SMMU Secure Control 0 Acknowledgement Register
 * This register is a read-only copy of SMMU()_S_CR0.
 */
union bdk_smmux_s_cr0ack
{
    uint32_t u;
    struct bdk_smmux_s_cr0ack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t nsstalld              : 1;  /**< [  9:  9](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[NSSTALLD].
                                                                 Internal:
                                                                 When SMMU()_S_IDR0[STALL_MODEL]=0x0 (both stall and terminate models available),
                                                                 setting this bit modifies the non-secure behavior such that only the terminate
                                                                 model is available for non-secure streams and SMMU()_IDR0[STALL_MODEL] reads as
                                                                 0x1 (terminate-only).

                                                                 When SMMU()_S_IDR0[STALL_MODEL]!=0x0, this bit is RES0.

                                                                 A reserved SMMU()_S_CR0 bit is not reflected into SMMU()_S_CR0ACK. */
        uint32_t reserved_6_8          : 3;
        uint32_t sif                   : 1;  /**< [  5:  5](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[SIF]. */
        uint32_t reserved_4            : 1;
        uint32_t cmdqen                : 1;  /**< [  3:  3](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[CMDQEN]. */
        uint32_t eventqen              : 1;  /**< [  2:  2](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[EVENTQEN]. */
        uint32_t reserved_1            : 1;
        uint32_t smmuen                : 1;  /**< [  0:  0](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[SMMUEN]. */
#else /* Word 0 - Little Endian */
        uint32_t smmuen                : 1;  /**< [  0:  0](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[SMMUEN]. */
        uint32_t reserved_1            : 1;
        uint32_t eventqen              : 1;  /**< [  2:  2](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[EVENTQEN]. */
        uint32_t cmdqen                : 1;  /**< [  3:  3](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[CMDQEN]. */
        uint32_t reserved_4            : 1;
        uint32_t sif                   : 1;  /**< [  5:  5](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[SIF]. */
        uint32_t reserved_6_8          : 3;
        uint32_t nsstalld              : 1;  /**< [  9:  9](SRO/H) Read-only hardware-modified SMMU(0)_S_CR0[NSSTALLD].
                                                                 Internal:
                                                                 When SMMU()_S_IDR0[STALL_MODEL]=0x0 (both stall and terminate models available),
                                                                 setting this bit modifies the non-secure behavior such that only the terminate
                                                                 model is available for non-secure streams and SMMU()_IDR0[STALL_MODEL] reads as
                                                                 0x1 (terminate-only).

                                                                 When SMMU()_S_IDR0[STALL_MODEL]!=0x0, this bit is RES0.

                                                                 A reserved SMMU()_S_CR0 bit is not reflected into SMMU()_S_CR0ACK. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_cr0ack_s cn; */
};
typedef union bdk_smmux_s_cr0ack bdk_smmux_s_cr0ack_t;

static inline uint64_t BDK_SMMUX_S_CR0ACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_CR0ACK(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008024ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_CR0ACK", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_CR0ACK(a) bdk_smmux_s_cr0ack_t
#define bustype_BDK_SMMUX_S_CR0ACK(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_CR0ACK(a) "SMMUX_S_CR0ACK"
#define device_bar_BDK_SMMUX_S_CR0ACK(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_CR0ACK(a) (a)
#define arguments_BDK_SMMUX_S_CR0ACK(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_cr1
 *
 * SMMU Secure Control 1 Register
 */
union bdk_smmux_s_cr1
{
    uint32_t u;
    struct bdk_smmux_s_cr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_12_31        : 20;
        uint32_t table_sh              : 2;  /**< [ 11: 10](SR/W) Table access shareability.
                                                                    0x0 = NSH.
                                                                    0x1 = Reserved (treated as 0x0).
                                                                    0x2 = OSH.
                                                                    0x3 = ISH.

                                                                 If [TABLE_OC]=0x0 and [TABLE_IC]=0x0, this field is ignored and OSH shareability
                                                                 is assumed. */
        uint32_t table_oc              : 2;  /**< [  9:  8](SR/W) Table access outer cacheability.
                                                                    0x0 = Noncacheable.
                                                                    0x1 = Write-back cacheable.
                                                                    0x2 = Write-through cacheable.
                                                                    0x3 = Reserved (treated as 0x0). */
        uint32_t table_ic              : 2;  /**< [  7:  6](SR/W) Table access inner cacheability.
                                                                    0x0 = Noncacheable.
                                                                    0x1 = Write-back cacheable.
                                                                    0x2 = Write-through cacheable.
                                                                    0x3 = Reserved (treated as 0x0). */
        uint32_t queue_sh              : 2;  /**< [  5:  4](SR/W) Queue access shareability.
                                                                    0x0 = NSH.
                                                                    0x1 = Reserved (treated as 0x0).
                                                                    0x2 = OSH.
                                                                    0x3 = ISH.

                                                                 If [QUEUE_OC]=0x0 and [QUEUE_IC]=0x0, this field is ignored and OSH
                                                                 shareability is assumed. */
        uint32_t queue_oc              : 2;  /**< [  3:  2](SR/W) Queue access outer cacheability.
                                                                    0x0 = Noncacheable.
                                                                    0x1 = Write-back cacheable.
                                                                    0x2 = Write-through cacheable.
                                                                    0x3 = Reserved (treated as 0x0). */
        uint32_t queue_ic              : 2;  /**< [  1:  0](SR/W) Queue access inner cacheability.
                                                                    0x0 = Noncacheable.
                                                                    0x1 = Write-back cacheable.
                                                                    0x2 = Write-through cacheable.
                                                                    0x3 = Reserved (treated as 0x0). */
#else /* Word 0 - Little Endian */
        uint32_t queue_ic              : 2;  /**< [  1:  0](SR/W) Queue access inner cacheability.
                                                                    0x0 = Noncacheable.
                                                                    0x1 = Write-back cacheable.
                                                                    0x2 = Write-through cacheable.
                                                                    0x3 = Reserved (treated as 0x0). */
        uint32_t queue_oc              : 2;  /**< [  3:  2](SR/W) Queue access outer cacheability.
                                                                    0x0 = Noncacheable.
                                                                    0x1 = Write-back cacheable.
                                                                    0x2 = Write-through cacheable.
                                                                    0x3 = Reserved (treated as 0x0). */
        uint32_t queue_sh              : 2;  /**< [  5:  4](SR/W) Queue access shareability.
                                                                    0x0 = NSH.
                                                                    0x1 = Reserved (treated as 0x0).
                                                                    0x2 = OSH.
                                                                    0x3 = ISH.

                                                                 If [QUEUE_OC]=0x0 and [QUEUE_IC]=0x0, this field is ignored and OSH
                                                                 shareability is assumed. */
        uint32_t table_ic              : 2;  /**< [  7:  6](SR/W) Table access inner cacheability.
                                                                    0x0 = Noncacheable.
                                                                    0x1 = Write-back cacheable.
                                                                    0x2 = Write-through cacheable.
                                                                    0x3 = Reserved (treated as 0x0). */
        uint32_t table_oc              : 2;  /**< [  9:  8](SR/W) Table access outer cacheability.
                                                                    0x0 = Noncacheable.
                                                                    0x1 = Write-back cacheable.
                                                                    0x2 = Write-through cacheable.
                                                                    0x3 = Reserved (treated as 0x0). */
        uint32_t table_sh              : 2;  /**< [ 11: 10](SR/W) Table access shareability.
                                                                    0x0 = NSH.
                                                                    0x1 = Reserved (treated as 0x0).
                                                                    0x2 = OSH.
                                                                    0x3 = ISH.

                                                                 If [TABLE_OC]=0x0 and [TABLE_IC]=0x0, this field is ignored and OSH shareability
                                                                 is assumed. */
        uint32_t reserved_12_31        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_cr1_s cn; */
};
typedef union bdk_smmux_s_cr1 bdk_smmux_s_cr1_t;

static inline uint64_t BDK_SMMUX_S_CR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_CR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008028ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_CR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_CR1(a) bdk_smmux_s_cr1_t
#define bustype_BDK_SMMUX_S_CR1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_CR1(a) "SMMUX_S_CR1"
#define device_bar_BDK_SMMUX_S_CR1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_CR1(a) (a)
#define arguments_BDK_SMMUX_S_CR1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_cr2
 *
 * SMMU Secure Control 2 Register
 */
union bdk_smmux_s_cr2
{
    uint32_t u;
    struct bdk_smmux_s_cr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t ptm                   : 1;  /**< [  2:  2](SR/W) Private TLB maintenance. When set, the SMMU is not expected to invalidate any
                                                                 local TLB entries on receipt of broadcast TLB maintenance operations for S-EL1
                                                                 or EL3 translation regimes.

                                                                 Broadcast invalidation for NS-EL1, EL2 or EL2-E2H translation regimes are not
                                                                 affected by this flag; see SMMU()_CR2[PTM].

                                                                 Internal:
                                                                 When SMMU()_IDR0[BTM]=0, this field is reserved. */
        uint32_t recinvsid             : 1;  /**< [  1:  1](SR/W) Record event SMMU_C_BAD_STREAMID_S from invalid input StreamIDs. When the SMMU is
                                                                 enabled, all traffic must be associated with a valid, reachable STE. Any
                                                                 transaction with a StreamID out of the range of a linear stream table, reaching
                                                                 an invalid pointer in a two-level stream table or out of the range of a second-level
                                                                 array will be aborted. This bit determines whether such events are also
                                                                 recorded. */
        uint32_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0            : 1;
        uint32_t recinvsid             : 1;  /**< [  1:  1](SR/W) Record event SMMU_C_BAD_STREAMID_S from invalid input StreamIDs. When the SMMU is
                                                                 enabled, all traffic must be associated with a valid, reachable STE. Any
                                                                 transaction with a StreamID out of the range of a linear stream table, reaching
                                                                 an invalid pointer in a two-level stream table or out of the range of a second-level
                                                                 array will be aborted. This bit determines whether such events are also
                                                                 recorded. */
        uint32_t ptm                   : 1;  /**< [  2:  2](SR/W) Private TLB maintenance. When set, the SMMU is not expected to invalidate any
                                                                 local TLB entries on receipt of broadcast TLB maintenance operations for S-EL1
                                                                 or EL3 translation regimes.

                                                                 Broadcast invalidation for NS-EL1, EL2 or EL2-E2H translation regimes are not
                                                                 affected by this flag; see SMMU()_CR2[PTM].

                                                                 Internal:
                                                                 When SMMU()_IDR0[BTM]=0, this field is reserved. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_cr2_s cn; */
};
typedef union bdk_smmux_s_cr2 bdk_smmux_s_cr2_t;

static inline uint64_t BDK_SMMUX_S_CR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_CR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x83000000802cll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_CR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_CR2(a) bdk_smmux_s_cr2_t
#define bustype_BDK_SMMUX_S_CR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_CR2(a) "SMMUX_S_CR2"
#define device_bar_BDK_SMMUX_S_CR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_CR2(a) (a)
#define arguments_BDK_SMMUX_S_CR2(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_eventq_base
 *
 * SMMU Secure Event Queue Base Register
 */
union bdk_smmux_s_eventq_base
{
    uint64_t u;
    struct bdk_smmux_s_eventq_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t wa                    : 1;  /**< [ 62: 62](SR/W) Write allocate hint.
                                                                 0 = No write-allocate.
                                                                 1 = Write-allocate. */
        uint64_t reserved_52_61        : 10;
        uint64_t addr                  : 47; /**< [ 51:  5](SR/W) Physical address of queue base.
                                                                 The effective base address has \<63:52\> = 0x0 and [ADDR]\<4:0\> =
                                                                 0x0. The effective base address is aligned to the queue size (in bytes), ignoring
                                                                 the least-significant bits of \<47:5\> as required to do so. */
        uint64_t log2size              : 5;  /**< [  4:  0](SR/W) Queue size as log2(entries). Except for the purposes of readback of this
                                                                 register, any use of this field's value is capped at the maximum,
                                                                 SMMU()_IDR1[EVENTQS]. */
#else /* Word 0 - Little Endian */
        uint64_t log2size              : 5;  /**< [  4:  0](SR/W) Queue size as log2(entries). Except for the purposes of readback of this
                                                                 register, any use of this field's value is capped at the maximum,
                                                                 SMMU()_IDR1[EVENTQS]. */
        uint64_t addr                  : 47; /**< [ 51:  5](SR/W) Physical address of queue base.
                                                                 The effective base address has \<63:52\> = 0x0 and [ADDR]\<4:0\> =
                                                                 0x0. The effective base address is aligned to the queue size (in bytes), ignoring
                                                                 the least-significant bits of \<47:5\> as required to do so. */
        uint64_t reserved_52_61        : 10;
        uint64_t wa                    : 1;  /**< [ 62: 62](SR/W) Write allocate hint.
                                                                 0 = No write-allocate.
                                                                 1 = Write-allocate. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_eventq_base_s cn; */
};
typedef union bdk_smmux_s_eventq_base bdk_smmux_s_eventq_base_t;

static inline uint64_t BDK_SMMUX_S_EVENTQ_BASE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_EVENTQ_BASE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000080a0ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_EVENTQ_BASE", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_EVENTQ_BASE(a) bdk_smmux_s_eventq_base_t
#define bustype_BDK_SMMUX_S_EVENTQ_BASE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_EVENTQ_BASE(a) "SMMUX_S_EVENTQ_BASE"
#define device_bar_BDK_SMMUX_S_EVENTQ_BASE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_EVENTQ_BASE(a) (a)
#define arguments_BDK_SMMUX_S_EVENTQ_BASE(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_eventq_cons
 *
 * SMMU Secure Event Queue Consumer Register
 */
union bdk_smmux_s_eventq_cons
{
    uint32_t u;
    struct bdk_smmux_s_eventq_cons_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ovackflg              : 1;  /**< [ 31: 31](SR/W) Overflow acknowledge flag. Software should set this flag to the value of
                                                                 SMMU()_EVENTQ_PROD[OVFLG] when it is safe for the SMMU to report a future event
                                                                 queue overflow; this should be done on initialization and after a previous event
                                                                 queue overflow is handled by software. */
        uint32_t reserved_20_30        : 11;
        uint32_t rd                    : 20; /**< [ 19:  0](SR/W) Queue read index + wrap flag.
                                                                 Entry last read by CPU (first empty queue location). */
#else /* Word 0 - Little Endian */
        uint32_t rd                    : 20; /**< [ 19:  0](SR/W) Queue read index + wrap flag.
                                                                 Entry last read by CPU (first empty queue location). */
        uint32_t reserved_20_30        : 11;
        uint32_t ovackflg              : 1;  /**< [ 31: 31](SR/W) Overflow acknowledge flag. Software should set this flag to the value of
                                                                 SMMU()_EVENTQ_PROD[OVFLG] when it is safe for the SMMU to report a future event
                                                                 queue overflow; this should be done on initialization and after a previous event
                                                                 queue overflow is handled by software. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_eventq_cons_s cn; */
};
typedef union bdk_smmux_s_eventq_cons bdk_smmux_s_eventq_cons_t;

static inline uint64_t BDK_SMMUX_S_EVENTQ_CONS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_EVENTQ_CONS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000080acll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_EVENTQ_CONS", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_EVENTQ_CONS(a) bdk_smmux_s_eventq_cons_t
#define bustype_BDK_SMMUX_S_EVENTQ_CONS(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_EVENTQ_CONS(a) "SMMUX_S_EVENTQ_CONS"
#define device_bar_BDK_SMMUX_S_EVENTQ_CONS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_EVENTQ_CONS(a) (a)
#define arguments_BDK_SMMUX_S_EVENTQ_CONS(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_eventq_irq_cfg0
 *
 * SMMU Secure Event Queue IRQ Configuration 0 Register
 */
union bdk_smmux_s_eventq_irq_cfg0
{
    uint64_t u;
    struct bdk_smmux_s_eventq_irq_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t addr                  : 50; /**< [ 51:  2](SR/W) Physical address of MSI target register.
                                                                 The effective address has ADDR\<63:52\> = 0x0 and [ADDR]\<1:0\> = 0x0.

                                                                 Note unlike most CNXXXX MSI-X address registers, this is a physical address, not
                                                                 a virtual address.

                                                                 If [ADDR]=0x0, no MSI is sent.

                                                                 Internal:
                                                                 High-order bits of the [ADDR] above the system physical address size (see
                                                                 SMMU()_IDR5[OAS]) are 0.

                                                                 If [ADDR]=0x0, allows a wired IRQ, if implemented, to be used (when
                                                                 SMMU()_(S_)IRQ_CTRL[GERROR_IRQEN]=1) instead of an MSI. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 50; /**< [ 51:  2](SR/W) Physical address of MSI target register.
                                                                 The effective address has ADDR\<63:52\> = 0x0 and [ADDR]\<1:0\> = 0x0.

                                                                 Note unlike most CNXXXX MSI-X address registers, this is a physical address, not
                                                                 a virtual address.

                                                                 If [ADDR]=0x0, no MSI is sent.

                                                                 Internal:
                                                                 High-order bits of the [ADDR] above the system physical address size (see
                                                                 SMMU()_IDR5[OAS]) are 0.

                                                                 If [ADDR]=0x0, allows a wired IRQ, if implemented, to be used (when
                                                                 SMMU()_(S_)IRQ_CTRL[GERROR_IRQEN]=1) instead of an MSI. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_eventq_irq_cfg0_s cn; */
};
typedef union bdk_smmux_s_eventq_irq_cfg0 bdk_smmux_s_eventq_irq_cfg0_t;

static inline uint64_t BDK_SMMUX_S_EVENTQ_IRQ_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_EVENTQ_IRQ_CFG0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000080b0ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_EVENTQ_IRQ_CFG0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_EVENTQ_IRQ_CFG0(a) bdk_smmux_s_eventq_irq_cfg0_t
#define bustype_BDK_SMMUX_S_EVENTQ_IRQ_CFG0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_EVENTQ_IRQ_CFG0(a) "SMMUX_S_EVENTQ_IRQ_CFG0"
#define device_bar_BDK_SMMUX_S_EVENTQ_IRQ_CFG0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_EVENTQ_IRQ_CFG0(a) (a)
#define arguments_BDK_SMMUX_S_EVENTQ_IRQ_CFG0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_eventq_irq_cfg1
 *
 * SMMU Secure Event Queue IRQ Configuration 1 Register
 */
union bdk_smmux_s_eventq_irq_cfg1
{
    uint32_t u;
    struct bdk_smmux_s_eventq_irq_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](SR/W) MSI data payload. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](SR/W) MSI data payload. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_eventq_irq_cfg1_s cn; */
};
typedef union bdk_smmux_s_eventq_irq_cfg1 bdk_smmux_s_eventq_irq_cfg1_t;

static inline uint64_t BDK_SMMUX_S_EVENTQ_IRQ_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_EVENTQ_IRQ_CFG1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000080b8ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_EVENTQ_IRQ_CFG1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_EVENTQ_IRQ_CFG1(a) bdk_smmux_s_eventq_irq_cfg1_t
#define bustype_BDK_SMMUX_S_EVENTQ_IRQ_CFG1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_EVENTQ_IRQ_CFG1(a) "SMMUX_S_EVENTQ_IRQ_CFG1"
#define device_bar_BDK_SMMUX_S_EVENTQ_IRQ_CFG1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_EVENTQ_IRQ_CFG1(a) (a)
#define arguments_BDK_SMMUX_S_EVENTQ_IRQ_CFG1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_eventq_irq_cfg2
 *
 * SMMU Secure Event Queue IRQ Configuration 2 Register
 */
union bdk_smmux_s_eventq_irq_cfg2
{
    uint32_t u;
    struct bdk_smmux_s_eventq_irq_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t sh                    : 2;  /**< [  5:  4](SR/W) Shareability.
                                                                 0x0 = NSH.
                                                                 0x1 = Reserved (treated as 0x0).
                                                                 0x2 = OSH.
                                                                 0x3 = ISH.

                                                                 When [MEMATTR] specifies a device memory type, the contents of this field are
                                                                 ignored and the shareability is effectively OSH. */
        uint32_t memattr               : 4;  /**< [  3:  0](SR/W) Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
#else /* Word 0 - Little Endian */
        uint32_t memattr               : 4;  /**< [  3:  0](SR/W) Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
        uint32_t sh                    : 2;  /**< [  5:  4](SR/W) Shareability.
                                                                 0x0 = NSH.
                                                                 0x1 = Reserved (treated as 0x0).
                                                                 0x2 = OSH.
                                                                 0x3 = ISH.

                                                                 When [MEMATTR] specifies a device memory type, the contents of this field are
                                                                 ignored and the shareability is effectively OSH. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_eventq_irq_cfg2_s cn; */
};
typedef union bdk_smmux_s_eventq_irq_cfg2 bdk_smmux_s_eventq_irq_cfg2_t;

static inline uint64_t BDK_SMMUX_S_EVENTQ_IRQ_CFG2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_EVENTQ_IRQ_CFG2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000080bcll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_EVENTQ_IRQ_CFG2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_EVENTQ_IRQ_CFG2(a) bdk_smmux_s_eventq_irq_cfg2_t
#define bustype_BDK_SMMUX_S_EVENTQ_IRQ_CFG2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_EVENTQ_IRQ_CFG2(a) "SMMUX_S_EVENTQ_IRQ_CFG2"
#define device_bar_BDK_SMMUX_S_EVENTQ_IRQ_CFG2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_EVENTQ_IRQ_CFG2(a) (a)
#define arguments_BDK_SMMUX_S_EVENTQ_IRQ_CFG2(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_eventq_prod
 *
 * SMMU Secure Event Queue Producer Register
 */
union bdk_smmux_s_eventq_prod
{
    uint32_t u;
    struct bdk_smmux_s_eventq_prod_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ovflg                 : 1;  /**< [ 31: 31](SR/W/H) Queue overflowed, one or more events have been lost. An event queue overflow is
                                                                 indicated using this flag. This flag is toggled by the SMMU when a queue
                                                                 overflow is detected, if OVFLG=SMMU()_S_EVENTQ_CONS[OVACKFLG] (i.e. no
                                                                 outstanding overflow condition exists).

                                                                 This flag will not be updated until a prior overflow is acknowledged by setting
                                                                 SMMU()_S_EVENTQ_CONS[OVACKFLG] equal to OVFLG. */
        uint32_t reserved_20_30        : 11;
        uint32_t wr                    : 20; /**< [ 19:  0](SR/W/H) Queue write index + wrap flag.
                                                                 Next space to be written by SMMU. */
#else /* Word 0 - Little Endian */
        uint32_t wr                    : 20; /**< [ 19:  0](SR/W/H) Queue write index + wrap flag.
                                                                 Next space to be written by SMMU. */
        uint32_t reserved_20_30        : 11;
        uint32_t ovflg                 : 1;  /**< [ 31: 31](SR/W/H) Queue overflowed, one or more events have been lost. An event queue overflow is
                                                                 indicated using this flag. This flag is toggled by the SMMU when a queue
                                                                 overflow is detected, if OVFLG=SMMU()_S_EVENTQ_CONS[OVACKFLG] (i.e. no
                                                                 outstanding overflow condition exists).

                                                                 This flag will not be updated until a prior overflow is acknowledged by setting
                                                                 SMMU()_S_EVENTQ_CONS[OVACKFLG] equal to OVFLG. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_eventq_prod_s cn; */
};
typedef union bdk_smmux_s_eventq_prod bdk_smmux_s_eventq_prod_t;

static inline uint64_t BDK_SMMUX_S_EVENTQ_PROD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_EVENTQ_PROD(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x8300000080a8ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_EVENTQ_PROD", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_EVENTQ_PROD(a) bdk_smmux_s_eventq_prod_t
#define bustype_BDK_SMMUX_S_EVENTQ_PROD(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_EVENTQ_PROD(a) "SMMUX_S_EVENTQ_PROD"
#define device_bar_BDK_SMMUX_S_EVENTQ_PROD(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_EVENTQ_PROD(a) (a)
#define arguments_BDK_SMMUX_S_EVENTQ_PROD(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_gatos_addr
 *
 * SMMU GATOS Address Register
 */
union bdk_smmux_s_gatos_addr
{
    uint64_t u;
    struct bdk_smmux_s_gatos_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 52; /**< [ 63: 12](SR/W) Requested input address. */
        uint64_t rtype                 : 2;  /**< [ 11: 10](SR/W) Request type.
                                                                 0x0 = Reserved.
                                                                 0x1 = Stage 1 (VAaIPA).
                                                                 0x2 = Stage 2 (IPAaPA).
                                                                 0x3 = Stage 1 + stage 2 (VAaPA). */
        uint64_t pnu                   : 1;  /**< [  9:  9](SR/W) Privileged/User access.
                                                                   0 = User/unprivileged.
                                                                   1 = Privileged. */
        uint64_t rnw                   : 1;  /**< [  8:  8](SR/W) Read/write access.
                                                                   0 = Write.
                                                                   1 = Read. */
        uint64_t ind                   : 1;  /**< [  7:  7](SR/W) Instruction/data access.
                                                                   0 = Data.
                                                                   1 = Instruction.

                                                                 This bit is ignored if [RNW]=0, and the effective [IND] for writes is "data". */
        uint64_t httui                 : 1;  /**< [  6:  6](SR/W) Inhibit hardware TTD flag update.
                                                                 0 = Flag update (HTTU) may occur, where supported by the SMMU, according to
                                                                 HA/HD configuration fields at stage 1/stage 2.
                                                                 1 = HTTU is inhibited, regardless of HA/HD configuration.
                                                                 The ATOS operation causes no state change and is "passive". */
        uint64_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_5          : 6;
        uint64_t httui                 : 1;  /**< [  6:  6](SR/W) Inhibit hardware TTD flag update.
                                                                 0 = Flag update (HTTU) may occur, where supported by the SMMU, according to
                                                                 HA/HD configuration fields at stage 1/stage 2.
                                                                 1 = HTTU is inhibited, regardless of HA/HD configuration.
                                                                 The ATOS operation causes no state change and is "passive". */
        uint64_t ind                   : 1;  /**< [  7:  7](SR/W) Instruction/data access.
                                                                   0 = Data.
                                                                   1 = Instruction.

                                                                 This bit is ignored if [RNW]=0, and the effective [IND] for writes is "data". */
        uint64_t rnw                   : 1;  /**< [  8:  8](SR/W) Read/write access.
                                                                   0 = Write.
                                                                   1 = Read. */
        uint64_t pnu                   : 1;  /**< [  9:  9](SR/W) Privileged/User access.
                                                                   0 = User/unprivileged.
                                                                   1 = Privileged. */
        uint64_t rtype                 : 2;  /**< [ 11: 10](SR/W) Request type.
                                                                 0x0 = Reserved.
                                                                 0x1 = Stage 1 (VAaIPA).
                                                                 0x2 = Stage 2 (IPAaPA).
                                                                 0x3 = Stage 1 + stage 2 (VAaPA). */
        uint64_t addr                  : 52; /**< [ 63: 12](SR/W) Requested input address. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gatos_addr_s cn; */
};
typedef union bdk_smmux_s_gatos_addr bdk_smmux_s_gatos_addr_t;

static inline uint64_t BDK_SMMUX_S_GATOS_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GATOS_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008110ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GATOS_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GATOS_ADDR(a) bdk_smmux_s_gatos_addr_t
#define bustype_BDK_SMMUX_S_GATOS_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_GATOS_ADDR(a) "SMMUX_S_GATOS_ADDR"
#define device_bar_BDK_SMMUX_S_GATOS_ADDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GATOS_ADDR(a) (a)
#define arguments_BDK_SMMUX_S_GATOS_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_gatos_ctrl
 *
 * SMMU Secure GATOS Control Register
 */
union bdk_smmux_s_gatos_ctrl
{
    uint32_t u;
    struct bdk_smmux_s_gatos_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t run                   : 1;  /**< [  0:  0](SR/W1S/H) Run ATOS translation. Software should write this bit to one to initiate the
                                                                 translation operation, after initializing the SMMU()_S_GATOS_SID and
                                                                 SMMU()_S_GATOS_ADDR registers. The SMMU clears [RUN] after the translation
                                                                 completes and its result is visible in SMMU()_S_GATOS_PAR. A write of zero to
                                                                 this flag might change the value of the flag but has no other effect. Software
                                                                 must only write zero to this flag when the flag is zero. */
#else /* Word 0 - Little Endian */
        uint32_t run                   : 1;  /**< [  0:  0](SR/W1S/H) Run ATOS translation. Software should write this bit to one to initiate the
                                                                 translation operation, after initializing the SMMU()_S_GATOS_SID and
                                                                 SMMU()_S_GATOS_ADDR registers. The SMMU clears [RUN] after the translation
                                                                 completes and its result is visible in SMMU()_S_GATOS_PAR. A write of zero to
                                                                 this flag might change the value of the flag but has no other effect. Software
                                                                 must only write zero to this flag when the flag is zero. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gatos_ctrl_s cn; */
};
typedef union bdk_smmux_s_gatos_ctrl bdk_smmux_s_gatos_ctrl_t;

static inline uint64_t BDK_SMMUX_S_GATOS_CTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GATOS_CTRL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008100ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GATOS_CTRL", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GATOS_CTRL(a) bdk_smmux_s_gatos_ctrl_t
#define bustype_BDK_SMMUX_S_GATOS_CTRL(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_GATOS_CTRL(a) "SMMUX_S_GATOS_CTRL"
#define device_bar_BDK_SMMUX_S_GATOS_CTRL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GATOS_CTRL(a) (a)
#define arguments_BDK_SMMUX_S_GATOS_CTRL(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_gatos_par
 *
 * SMMU GATOS Address Register
 */
union bdk_smmux_s_gatos_par
{
    uint64_t u;
    struct bdk_smmux_s_gatos_par_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t par                   : 64; /**< [ 63:  0](SRO/H) Bit zero determines the format of the register.
                                                                 Fault/error status:
                                                                   0 = No fault.
                                                                   1 = Fault/translation error.

                                                                 See SMMUv3 spec for the encodings. */
#else /* Word 0 - Little Endian */
        uint64_t par                   : 64; /**< [ 63:  0](SRO/H) Bit zero determines the format of the register.
                                                                 Fault/error status:
                                                                   0 = No fault.
                                                                   1 = Fault/translation error.

                                                                 See SMMUv3 spec for the encodings. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gatos_par_s cn; */
};
typedef union bdk_smmux_s_gatos_par bdk_smmux_s_gatos_par_t;

static inline uint64_t BDK_SMMUX_S_GATOS_PAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GATOS_PAR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008118ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GATOS_PAR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GATOS_PAR(a) bdk_smmux_s_gatos_par_t
#define bustype_BDK_SMMUX_S_GATOS_PAR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_GATOS_PAR(a) "SMMUX_S_GATOS_PAR"
#define device_bar_BDK_SMMUX_S_GATOS_PAR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GATOS_PAR(a) (a)
#define arguments_BDK_SMMUX_S_GATOS_PAR(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_gatos_sid
 *
 * SMMU GATOS SID Register
 */
union bdk_smmux_s_gatos_sid
{
    uint64_t u;
    struct bdk_smmux_s_gatos_sid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_54_63        : 10;
        uint64_t ssec                  : 1;  /**< [ 53: 53](SR/W) Secure stream lookup.
                                                                 0 = Non-secure stream lookup. [STREAMID] is a non-secure StreamID.
                                                                 1 = Secure stream lookup. [STREAMID] is a secure StreamID. */
        uint64_t ssid_valid            : 1;  /**< [ 52: 52](SR/W) SubstreamID valid.
                                                                 Internal:
                                                                 If SMMU()_IDR1[SSIDSIZE]=0, this field is RES0. */
        uint64_t substreamid           : 20; /**< [ 51: 32](SR/W) SubstreamID of request.
                                                                 If SMMU()_IDR1[SSIDSIZE]\<20, bits \<51:32+SMMU()_IDR1[SSIDSIZE]\> are RES0. */
        uint64_t reserved_24_31        : 8;
        uint64_t streamid              : 24; /**< [ 23:  0](SR/W) StreamID of request.
                                                                 This is written with the StreamID (used to locate translations/CDs) of the request
                                                                 later submitted
                                                                 to SMMU()_GATOS_ADDR.
                                                                 If SMMU()_IDR1[SIDSIZE]\<32, bits \<31:SMMU()_IDR1[SIDSIZE]\> are RES0. */
#else /* Word 0 - Little Endian */
        uint64_t streamid              : 24; /**< [ 23:  0](SR/W) StreamID of request.
                                                                 This is written with the StreamID (used to locate translations/CDs) of the request
                                                                 later submitted
                                                                 to SMMU()_GATOS_ADDR.
                                                                 If SMMU()_IDR1[SIDSIZE]\<32, bits \<31:SMMU()_IDR1[SIDSIZE]\> are RES0. */
        uint64_t reserved_24_31        : 8;
        uint64_t substreamid           : 20; /**< [ 51: 32](SR/W) SubstreamID of request.
                                                                 If SMMU()_IDR1[SSIDSIZE]\<20, bits \<51:32+SMMU()_IDR1[SSIDSIZE]\> are RES0. */
        uint64_t ssid_valid            : 1;  /**< [ 52: 52](SR/W) SubstreamID valid.
                                                                 Internal:
                                                                 If SMMU()_IDR1[SSIDSIZE]=0, this field is RES0. */
        uint64_t ssec                  : 1;  /**< [ 53: 53](SR/W) Secure stream lookup.
                                                                 0 = Non-secure stream lookup. [STREAMID] is a non-secure StreamID.
                                                                 1 = Secure stream lookup. [STREAMID] is a secure StreamID. */
        uint64_t reserved_54_63        : 10;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gatos_sid_s cn; */
};
typedef union bdk_smmux_s_gatos_sid bdk_smmux_s_gatos_sid_t;

static inline uint64_t BDK_SMMUX_S_GATOS_SID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GATOS_SID(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008108ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GATOS_SID", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GATOS_SID(a) bdk_smmux_s_gatos_sid_t
#define bustype_BDK_SMMUX_S_GATOS_SID(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_GATOS_SID(a) "SMMUX_S_GATOS_SID"
#define device_bar_BDK_SMMUX_S_GATOS_SID(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GATOS_SID(a) (a)
#define arguments_BDK_SMMUX_S_GATOS_SID(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_gbpa
 *
 * SMMU Secure Global Bypass Attribute Register
 */
union bdk_smmux_s_gbpa
{
    uint32_t u;
    struct bdk_smmux_s_gbpa_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t update                : 1;  /**< [ 31: 31](SRO) Update/completion flag. */
        uint32_t reserved_21_30        : 10;
        uint32_t abrt                  : 1;  /**< [ 20: 20](SR/W) Abort all incoming transactions.
                                                                 0 = Do not abort; transactions bypass the SMMU with attributes given by other
                                                                 fields in this register.
                                                                 1 = Abort all incoming transactions.

                                                                 The SMMU makes no record of transactions aborted using this flag.

                                                                 Internal:
                                                                 An implementation can reset this field to 1, in order to implement a default
                                                                 deny policy on reset. */
        uint32_t instcfg               : 2;  /**< [ 19: 18](SR/W) Instruction/data override.
                                                                      0x0 = Use incoming.
                                                                      0x1 = Reserved (behaves as 0x0).
                                                                      0x2 = Data.
                                                                      0x3 = Instruction.

                                                                 Only affects reads; writes are always output as data. */
        uint32_t privcfg               : 2;  /**< [ 17: 16](SR/W) User/privileged override.
                                                                      0x0 = Use incoming.
                                                                      0x1 = Reserved (behaves as 0x0).
                                                                      0x2 = Unprivileged.
                                                                      0x3 = Privileged. */
        uint32_t nscfg                 : 2;  /**< [ 15: 14](SR/W) NS override.
                                                                    0x0 = Use incoming.
                                                                    0x1 = Reserved (behaves as 0x0).
                                                                    0x2 = Secure.
                                                                    0x3 = Non-secure. */
        uint32_t shcfg                 : 2;  /**< [ 13: 12](SR/W) Shareability override.
                                                                    0x0 = NSH.
                                                                    0x1 = Use incoming.
                                                                    0x2 = OSH.
                                                                    0x3 = ISH. */
        uint32_t alloccfg              : 4;  /**< [ 11:  8](SR/W) 0xxx:    Use incoming RA/WA/TR allocation/transient hints.
                                                                 1RWT: Hints are overridden to given values:
                                                                   * Read allocate = R.
                                                                   * Write allocate = W.
                                                                   * Transient = T.

                                                                   When overridden by this field, for each of RA/WA and TR, both inner- and
                                                                 outer-hints are set to the same value. Since it is not architecturally possible
                                                                 to express hints for types that are device or normal-nonCacheable, this field
                                                                 has no effect on memory types that are not normal- WB or normal-WT, whether such
                                                                 types are provided with an upstream transaction or overridden using
                                                                 MTCFG/MemAttr. */
        uint32_t reserved_5_7          : 3;
        uint32_t mtcfg                 : 1;  /**< [  4:  4](SR/W) Memory type override.
                                                                 0 = Use incoming memory type.
                                                                 1 = Override incoming memory type using MemAttr field. */
        uint32_t memattr               : 4;  /**< [  3:  0](SR/W) Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
#else /* Word 0 - Little Endian */
        uint32_t memattr               : 4;  /**< [  3:  0](SR/W) Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
        uint32_t mtcfg                 : 1;  /**< [  4:  4](SR/W) Memory type override.
                                                                 0 = Use incoming memory type.
                                                                 1 = Override incoming memory type using MemAttr field. */
        uint32_t reserved_5_7          : 3;
        uint32_t alloccfg              : 4;  /**< [ 11:  8](SR/W) 0xxx:    Use incoming RA/WA/TR allocation/transient hints.
                                                                 1RWT: Hints are overridden to given values:
                                                                   * Read allocate = R.
                                                                   * Write allocate = W.
                                                                   * Transient = T.

                                                                   When overridden by this field, for each of RA/WA and TR, both inner- and
                                                                 outer-hints are set to the same value. Since it is not architecturally possible
                                                                 to express hints for types that are device or normal-nonCacheable, this field
                                                                 has no effect on memory types that are not normal- WB or normal-WT, whether such
                                                                 types are provided with an upstream transaction or overridden using
                                                                 MTCFG/MemAttr. */
        uint32_t shcfg                 : 2;  /**< [ 13: 12](SR/W) Shareability override.
                                                                    0x0 = NSH.
                                                                    0x1 = Use incoming.
                                                                    0x2 = OSH.
                                                                    0x3 = ISH. */
        uint32_t nscfg                 : 2;  /**< [ 15: 14](SR/W) NS override.
                                                                    0x0 = Use incoming.
                                                                    0x1 = Reserved (behaves as 0x0).
                                                                    0x2 = Secure.
                                                                    0x3 = Non-secure. */
        uint32_t privcfg               : 2;  /**< [ 17: 16](SR/W) User/privileged override.
                                                                      0x0 = Use incoming.
                                                                      0x1 = Reserved (behaves as 0x0).
                                                                      0x2 = Unprivileged.
                                                                      0x3 = Privileged. */
        uint32_t instcfg               : 2;  /**< [ 19: 18](SR/W) Instruction/data override.
                                                                      0x0 = Use incoming.
                                                                      0x1 = Reserved (behaves as 0x0).
                                                                      0x2 = Data.
                                                                      0x3 = Instruction.

                                                                 Only affects reads; writes are always output as data. */
        uint32_t abrt                  : 1;  /**< [ 20: 20](SR/W) Abort all incoming transactions.
                                                                 0 = Do not abort; transactions bypass the SMMU with attributes given by other
                                                                 fields in this register.
                                                                 1 = Abort all incoming transactions.

                                                                 The SMMU makes no record of transactions aborted using this flag.

                                                                 Internal:
                                                                 An implementation can reset this field to 1, in order to implement a default
                                                                 deny policy on reset. */
        uint32_t reserved_21_30        : 10;
        uint32_t update                : 1;  /**< [ 31: 31](SRO) Update/completion flag. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gbpa_s cn; */
};
typedef union bdk_smmux_s_gbpa bdk_smmux_s_gbpa_t;

static inline uint64_t BDK_SMMUX_S_GBPA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GBPA(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008044ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GBPA", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GBPA(a) bdk_smmux_s_gbpa_t
#define bustype_BDK_SMMUX_S_GBPA(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_GBPA(a) "SMMUX_S_GBPA"
#define device_bar_BDK_SMMUX_S_GBPA(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GBPA(a) (a)
#define arguments_BDK_SMMUX_S_GBPA(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_gerror
 *
 * SMMU Secure GERROR Register
 */
union bdk_smmux_s_gerror
{
    uint32_t u;
    struct bdk_smmux_s_gerror_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t sfm_err               : 1;  /**< [  8:  8](SRO) The SMMU has entered service failure mode. Traffic through the SMMU might be
                                                                 affected. Depending on the origin of the error, the SMMU might stop processing
                                                                 commands and recording events. The RAS registers describe the
                                                                 error. Acknowledgement of this error via GERRORN does not clear this error,
                                                                 which is cleared in an implementation defined way. SFM triggers both
                                                                 SMMU()_GERROR[SFM_ERR] and SMMU()_S_GERROR[SFM_ERR]. */
        uint32_t msi_gerror_abt_err    : 1;  /**< [  7:  7](SRO) A GERROR MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t reserved_6            : 1;
        uint32_t msi_eventq_abt_err    : 1;  /**< [  5:  5](SRO) An event queue MSI was terminated with abort. Activation of this error does not
                                                                 affect future MSIs. */
        uint32_t msi_cmdq_abt_err      : 1;  /**< [  4:  4](SRO) A CMD_SYNC MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t reserved_3            : 1;
        uint32_t eventq_abt_err        : 1;  /**< [  2:  2](SRO/H) A write to the event queue was terminated with abort and event records might have been lost. */
        uint32_t reserved_1            : 1;
        uint32_t cmdq_err              : 1;  /**< [  0:  0](SRO/H) A command has been encountered that cannot be processed. SMMU()_CMDQ_CONS[ERRX] has
                                                                 been updated with a reason code and command processing has stopped.
                                                                 Commands are not processed while this error is active. */
#else /* Word 0 - Little Endian */
        uint32_t cmdq_err              : 1;  /**< [  0:  0](SRO/H) A command has been encountered that cannot be processed. SMMU()_CMDQ_CONS[ERRX] has
                                                                 been updated with a reason code and command processing has stopped.
                                                                 Commands are not processed while this error is active. */
        uint32_t reserved_1            : 1;
        uint32_t eventq_abt_err        : 1;  /**< [  2:  2](SRO/H) A write to the event queue was terminated with abort and event records might have been lost. */
        uint32_t reserved_3            : 1;
        uint32_t msi_cmdq_abt_err      : 1;  /**< [  4:  4](SRO) A CMD_SYNC MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t msi_eventq_abt_err    : 1;  /**< [  5:  5](SRO) An event queue MSI was terminated with abort. Activation of this error does not
                                                                 affect future MSIs. */
        uint32_t reserved_6            : 1;
        uint32_t msi_gerror_abt_err    : 1;  /**< [  7:  7](SRO) A GERROR MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t sfm_err               : 1;  /**< [  8:  8](SRO) The SMMU has entered service failure mode. Traffic through the SMMU might be
                                                                 affected. Depending on the origin of the error, the SMMU might stop processing
                                                                 commands and recording events. The RAS registers describe the
                                                                 error. Acknowledgement of this error via GERRORN does not clear this error,
                                                                 which is cleared in an implementation defined way. SFM triggers both
                                                                 SMMU()_GERROR[SFM_ERR] and SMMU()_S_GERROR[SFM_ERR]. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gerror_s cn; */
};
typedef union bdk_smmux_s_gerror bdk_smmux_s_gerror_t;

static inline uint64_t BDK_SMMUX_S_GERROR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GERROR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008060ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GERROR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GERROR(a) bdk_smmux_s_gerror_t
#define bustype_BDK_SMMUX_S_GERROR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_GERROR(a) "SMMUX_S_GERROR"
#define device_bar_BDK_SMMUX_S_GERROR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GERROR(a) (a)
#define arguments_BDK_SMMUX_S_GERROR(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_gerror_irq_cfg0
 *
 * SMMU Secure GERROR IRQ Configuration 0 Register
 * Registers SMMU()_S_GERROR_IRQ_CFG0/1/2 are guarded by the respective
 * SMMU()_S_IRQ_CTRL[GERROR_IRQEN] and must only be modified when
 * SMMU()_S_IRQ_CTRL[GERROR_IRQEN]=0.
 */
union bdk_smmux_s_gerror_irq_cfg0
{
    uint64_t u;
    struct bdk_smmux_s_gerror_irq_cfg0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t addr                  : 50; /**< [ 51:  2](SR/W) Physical address of MSI target register.
                                                                 The effective address has ADDR\<63:52\> = 0x0 and [ADDR]\<1:0\> = 0x0.

                                                                 Note unlike most CNXXXX MSI-X address registers, this is a physical address, not
                                                                 a virtual address.

                                                                 If [ADDR]=0x0, no MSI is sent.

                                                                 Internal:
                                                                 High-order bits of the [ADDR] above the system physical address size (see
                                                                 SMMU()_IDR5[OAS]) are 0.

                                                                 If [ADDR]=0x0, allows a wired IRQ, if implemented, to be used (when
                                                                 SMMU()_(S_)IRQ_CTRL[GERROR_IRQEN]=1) instead of an MSI. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 50; /**< [ 51:  2](SR/W) Physical address of MSI target register.
                                                                 The effective address has ADDR\<63:52\> = 0x0 and [ADDR]\<1:0\> = 0x0.

                                                                 Note unlike most CNXXXX MSI-X address registers, this is a physical address, not
                                                                 a virtual address.

                                                                 If [ADDR]=0x0, no MSI is sent.

                                                                 Internal:
                                                                 High-order bits of the [ADDR] above the system physical address size (see
                                                                 SMMU()_IDR5[OAS]) are 0.

                                                                 If [ADDR]=0x0, allows a wired IRQ, if implemented, to be used (when
                                                                 SMMU()_(S_)IRQ_CTRL[GERROR_IRQEN]=1) instead of an MSI. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gerror_irq_cfg0_s cn; */
};
typedef union bdk_smmux_s_gerror_irq_cfg0 bdk_smmux_s_gerror_irq_cfg0_t;

static inline uint64_t BDK_SMMUX_S_GERROR_IRQ_CFG0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GERROR_IRQ_CFG0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008068ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GERROR_IRQ_CFG0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GERROR_IRQ_CFG0(a) bdk_smmux_s_gerror_irq_cfg0_t
#define bustype_BDK_SMMUX_S_GERROR_IRQ_CFG0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_GERROR_IRQ_CFG0(a) "SMMUX_S_GERROR_IRQ_CFG0"
#define device_bar_BDK_SMMUX_S_GERROR_IRQ_CFG0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GERROR_IRQ_CFG0(a) (a)
#define arguments_BDK_SMMUX_S_GERROR_IRQ_CFG0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_gerror_irq_cfg1
 *
 * SMMU Secure GERROR IRQ Configuration 1 Register
 */
union bdk_smmux_s_gerror_irq_cfg1
{
    uint32_t u;
    struct bdk_smmux_s_gerror_irq_cfg1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](SR/W) MSI data payload. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](SR/W) MSI data payload. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gerror_irq_cfg1_s cn; */
};
typedef union bdk_smmux_s_gerror_irq_cfg1 bdk_smmux_s_gerror_irq_cfg1_t;

static inline uint64_t BDK_SMMUX_S_GERROR_IRQ_CFG1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GERROR_IRQ_CFG1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008070ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GERROR_IRQ_CFG1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GERROR_IRQ_CFG1(a) bdk_smmux_s_gerror_irq_cfg1_t
#define bustype_BDK_SMMUX_S_GERROR_IRQ_CFG1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_GERROR_IRQ_CFG1(a) "SMMUX_S_GERROR_IRQ_CFG1"
#define device_bar_BDK_SMMUX_S_GERROR_IRQ_CFG1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GERROR_IRQ_CFG1(a) (a)
#define arguments_BDK_SMMUX_S_GERROR_IRQ_CFG1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_gerror_irq_cfg2
 *
 * SMMU Secure GERROR IRQ Configuration 2 Register
 */
union bdk_smmux_s_gerror_irq_cfg2
{
    uint32_t u;
    struct bdk_smmux_s_gerror_irq_cfg2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t sh                    : 2;  /**< [  5:  4](SR/W) Shareability.
                                                                 0x0 = NSH.
                                                                 0x1 = Reserved (treated as 0x0).
                                                                 0x2 = OSH.
                                                                 0x3 = ISH.

                                                                 When [MEMATTR] specifies a device memory type, the contents of this field are
                                                                 ignored and the shareability is effectively OSH. */
        uint32_t memattr               : 4;  /**< [  3:  0](SR/W) Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
#else /* Word 0 - Little Endian */
        uint32_t memattr               : 4;  /**< [  3:  0](SR/W) Memory type, encoded the same as SMMU_STE_S[MEMATTR]. */
        uint32_t sh                    : 2;  /**< [  5:  4](SR/W) Shareability.
                                                                 0x0 = NSH.
                                                                 0x1 = Reserved (treated as 0x0).
                                                                 0x2 = OSH.
                                                                 0x3 = ISH.

                                                                 When [MEMATTR] specifies a device memory type, the contents of this field are
                                                                 ignored and the shareability is effectively OSH. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gerror_irq_cfg2_s cn; */
};
typedef union bdk_smmux_s_gerror_irq_cfg2 bdk_smmux_s_gerror_irq_cfg2_t;

static inline uint64_t BDK_SMMUX_S_GERROR_IRQ_CFG2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GERROR_IRQ_CFG2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008074ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GERROR_IRQ_CFG2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GERROR_IRQ_CFG2(a) bdk_smmux_s_gerror_irq_cfg2_t
#define bustype_BDK_SMMUX_S_GERROR_IRQ_CFG2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_GERROR_IRQ_CFG2(a) "SMMUX_S_GERROR_IRQ_CFG2"
#define device_bar_BDK_SMMUX_S_GERROR_IRQ_CFG2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GERROR_IRQ_CFG2(a) (a)
#define arguments_BDK_SMMUX_S_GERROR_IRQ_CFG2(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_gerrorn
 *
 * SMMU Secure GERRORN Register
 */
union bdk_smmux_s_gerrorn
{
    uint32_t u;
    struct bdk_smmux_s_gerrorn_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t sfm_err               : 1;  /**< [  8:  8](SR/W) The SMMU has entered service failure mode. Traffic through the SMMU might be
                                                                 affected. Depending on the origin of the error, the SMMU might stop processing
                                                                 commands and recording events. The RAS registers describe the
                                                                 error. Acknowledgement of this error via GERRORN does not clear this error,
                                                                 which is cleared in an implementation defined way. SFM triggers both
                                                                 SMMU()_GERROR[SFM_ERR] and SMMU()_S_GERROR[SFM_ERR]. */
        uint32_t msi_gerror_abt_err    : 1;  /**< [  7:  7](SR/W) A GERROR MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t reserved_6            : 1;
        uint32_t msi_eventq_abt_err    : 1;  /**< [  5:  5](SR/W) An event queue MSI was terminated with abort. Activation of this error does not
                                                                 affect future MSIs. */
        uint32_t msi_cmdq_abt_err      : 1;  /**< [  4:  4](SR/W) A CMD_SYNC MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t reserved_3            : 1;
        uint32_t eventq_abt_err        : 1;  /**< [  2:  2](SR/W) A write to the event queue was terminated with abort and event records might have been lost. */
        uint32_t reserved_1            : 1;
        uint32_t cmdq_err              : 1;  /**< [  0:  0](SR/W) A command has been encountered that cannot be processed. SMMU()_CMDQ_CONS[ERRX] has
                                                                 been updated with a reason code and command processing has stopped.
                                                                 Commands are not processed while this error is active. */
#else /* Word 0 - Little Endian */
        uint32_t cmdq_err              : 1;  /**< [  0:  0](SR/W) A command has been encountered that cannot be processed. SMMU()_CMDQ_CONS[ERRX] has
                                                                 been updated with a reason code and command processing has stopped.
                                                                 Commands are not processed while this error is active. */
        uint32_t reserved_1            : 1;
        uint32_t eventq_abt_err        : 1;  /**< [  2:  2](SR/W) A write to the event queue was terminated with abort and event records might have been lost. */
        uint32_t reserved_3            : 1;
        uint32_t msi_cmdq_abt_err      : 1;  /**< [  4:  4](SR/W) A CMD_SYNC MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t msi_eventq_abt_err    : 1;  /**< [  5:  5](SR/W) An event queue MSI was terminated with abort. Activation of this error does not
                                                                 affect future MSIs. */
        uint32_t reserved_6            : 1;
        uint32_t msi_gerror_abt_err    : 1;  /**< [  7:  7](SR/W) A GERROR MSI was terminated with abort. Activation of this error does not affect
                                                                 future MSIs. */
        uint32_t sfm_err               : 1;  /**< [  8:  8](SR/W) The SMMU has entered service failure mode. Traffic through the SMMU might be
                                                                 affected. Depending on the origin of the error, the SMMU might stop processing
                                                                 commands and recording events. The RAS registers describe the
                                                                 error. Acknowledgement of this error via GERRORN does not clear this error,
                                                                 which is cleared in an implementation defined way. SFM triggers both
                                                                 SMMU()_GERROR[SFM_ERR] and SMMU()_S_GERROR[SFM_ERR]. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_gerrorn_s cn; */
};
typedef union bdk_smmux_s_gerrorn bdk_smmux_s_gerrorn_t;

static inline uint64_t BDK_SMMUX_S_GERRORN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_GERRORN(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008064ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_GERRORN", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_GERRORN(a) bdk_smmux_s_gerrorn_t
#define bustype_BDK_SMMUX_S_GERRORN(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_GERRORN(a) "SMMUX_S_GERRORN"
#define device_bar_BDK_SMMUX_S_GERRORN(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_GERRORN(a) (a)
#define arguments_BDK_SMMUX_S_GERRORN(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_hit_perf
 *
 * SMMU Secure Hits Performance Counter Register
 */
union bdk_smmux_s_hit_perf
{
    uint64_t u;
    struct bdk_smmux_s_hit_perf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](SR/W/H) Counts the number of hits in secure mode. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](SR/W/H) Counts the number of hits in secure mode. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_hit_perf_s cn; */
};
typedef union bdk_smmux_s_hit_perf bdk_smmux_s_hit_perf_t;

static inline uint64_t BDK_SMMUX_S_HIT_PERF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_HIT_PERF(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000021020ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000021020ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000021020ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_S_HIT_PERF", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_HIT_PERF(a) bdk_smmux_s_hit_perf_t
#define bustype_BDK_SMMUX_S_HIT_PERF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_HIT_PERF(a) "SMMUX_S_HIT_PERF"
#define device_bar_BDK_SMMUX_S_HIT_PERF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_HIT_PERF(a) (a)
#define arguments_BDK_SMMUX_S_HIT_PERF(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_idr0
 *
 * SMMU Secure IDR0 Register
 */
union bdk_smmux_s_idr0
{
    uint32_t u;
    struct bdk_smmux_s_idr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_26_31        : 6;
        uint32_t stall_model           : 2;  /**< [ 25: 24](SRO) Stalling fault model support. Encoded identically to SMMU()_IDR0[STALL_MODEL],
                                                                 this field indicates the implementation's support for stall/terminate fault
                                                                 models.

                                                                 For CNXXXX, no stalling. */
        uint32_t reserved_14_23        : 10;
        uint32_t msi                   : 1;  /**< [ 13: 13](SRO) Secure message signaled interrupts are supported. */
        uint32_t reserved_0_12         : 13;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_12         : 13;
        uint32_t msi                   : 1;  /**< [ 13: 13](SRO) Secure message signaled interrupts are supported. */
        uint32_t reserved_14_23        : 10;
        uint32_t stall_model           : 2;  /**< [ 25: 24](SRO) Stalling fault model support. Encoded identically to SMMU()_IDR0[STALL_MODEL],
                                                                 this field indicates the implementation's support for stall/terminate fault
                                                                 models.

                                                                 For CNXXXX, no stalling. */
        uint32_t reserved_26_31        : 6;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_idr0_s cn; */
};
typedef union bdk_smmux_s_idr0 bdk_smmux_s_idr0_t;

static inline uint64_t BDK_SMMUX_S_IDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IDR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008000ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IDR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IDR0(a) bdk_smmux_s_idr0_t
#define bustype_BDK_SMMUX_S_IDR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IDR0(a) "SMMUX_S_IDR0"
#define device_bar_BDK_SMMUX_S_IDR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IDR0(a) (a)
#define arguments_BDK_SMMUX_S_IDR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_idr1
 *
 * SMMU Secure IDR1 Register
 */
union bdk_smmux_s_idr1
{
    uint32_t u;
    struct bdk_smmux_s_idr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t secure_impl           : 1;  /**< [ 31: 31](SRO) Security implemented.
                                                                 For CNXXXX, reads as one when security is implemented in the SMMU. */
        uint32_t reserved_6_30         : 25;
        uint32_t s_sidsize             : 6;  /**< [  5:  0](SRO) Secure StreamID size. Equivalent to SMMU()_IDR1[SIDSIZE] (and encoded the same),
                                                                 this field determines the maximum secure StreamID value and therefore the
                                                                 maximum size of the secure stream table. */
#else /* Word 0 - Little Endian */
        uint32_t s_sidsize             : 6;  /**< [  5:  0](SRO) Secure StreamID size. Equivalent to SMMU()_IDR1[SIDSIZE] (and encoded the same),
                                                                 this field determines the maximum secure StreamID value and therefore the
                                                                 maximum size of the secure stream table. */
        uint32_t reserved_6_30         : 25;
        uint32_t secure_impl           : 1;  /**< [ 31: 31](SRO) Security implemented.
                                                                 For CNXXXX, reads as one when security is implemented in the SMMU. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_idr1_s cn; */
};
typedef union bdk_smmux_s_idr1 bdk_smmux_s_idr1_t;

static inline uint64_t BDK_SMMUX_S_IDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IDR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008004ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IDR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IDR1(a) bdk_smmux_s_idr1_t
#define bustype_BDK_SMMUX_S_IDR1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IDR1(a) "SMMUX_S_IDR1"
#define device_bar_BDK_SMMUX_S_IDR1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IDR1(a) (a)
#define arguments_BDK_SMMUX_S_IDR1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_idr2
 *
 * SMMU Secure IDR2 Register
 */
union bdk_smmux_s_idr2
{
    uint32_t u;
    struct bdk_smmux_s_idr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_idr2_s cn; */
};
typedef union bdk_smmux_s_idr2 bdk_smmux_s_idr2_t;

static inline uint64_t BDK_SMMUX_S_IDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IDR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008008ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IDR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IDR2(a) bdk_smmux_s_idr2_t
#define bustype_BDK_SMMUX_S_IDR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IDR2(a) "SMMUX_S_IDR2"
#define device_bar_BDK_SMMUX_S_IDR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IDR2(a) (a)
#define arguments_BDK_SMMUX_S_IDR2(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_idr3
 *
 * SMMU Secure IDR3 Register
 */
union bdk_smmux_s_idr3
{
    uint32_t u;
    struct bdk_smmux_s_idr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_idr3_s cn; */
};
typedef union bdk_smmux_s_idr3 bdk_smmux_s_idr3_t;

static inline uint64_t BDK_SMMUX_S_IDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IDR3(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x83000000800cll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IDR3", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IDR3(a) bdk_smmux_s_idr3_t
#define bustype_BDK_SMMUX_S_IDR3(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IDR3(a) "SMMUX_S_IDR3"
#define device_bar_BDK_SMMUX_S_IDR3(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IDR3(a) (a)
#define arguments_BDK_SMMUX_S_IDR3(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_idr4
 *
 * SMMU Secure IDR4 Register
 */
union bdk_smmux_s_idr4
{
    uint32_t u;
    struct bdk_smmux_s_idr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_idr4_s cn; */
};
typedef union bdk_smmux_s_idr4 bdk_smmux_s_idr4_t;

static inline uint64_t BDK_SMMUX_S_IDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IDR4(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008010ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IDR4", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IDR4(a) bdk_smmux_s_idr4_t
#define bustype_BDK_SMMUX_S_IDR4(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IDR4(a) "SMMUX_S_IDR4"
#define device_bar_BDK_SMMUX_S_IDR4(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IDR4(a) (a)
#define arguments_BDK_SMMUX_S_IDR4(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_imp_actlr
 *
 * SMMU Auxiliary Control Register
 */
union bdk_smmux_s_imp_actlr
{
    uint32_t u;
    struct bdk_smmux_s_imp_actlr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_17_31        : 15;
        uint32_t qos                   : 1;  /**< [ 16: 16](SR/W) Quality-of-service for the memory accesses performed during the translation process. */
        uint32_t reserved_8_15         : 8;
        uint32_t cpid                  : 8;  /**< [  7:  0](SR/W) Cache partition ID for the memory accesses performed during the translation process. */
#else /* Word 0 - Little Endian */
        uint32_t cpid                  : 8;  /**< [  7:  0](SR/W) Cache partition ID for the memory accesses performed during the translation process. */
        uint32_t reserved_8_15         : 8;
        uint32_t qos                   : 1;  /**< [ 16: 16](SR/W) Quality-of-service for the memory accesses performed during the translation process. */
        uint32_t reserved_17_31        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_actlr_s cn; */
};
typedef union bdk_smmux_s_imp_actlr bdk_smmux_s_imp_actlr_t;

static inline uint64_t BDK_SMMUX_S_IMP_ACTLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_ACTLR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008e10ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IMP_ACTLR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IMP_ACTLR(a) bdk_smmux_s_imp_actlr_t
#define bustype_BDK_SMMUX_S_IMP_ACTLR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IMP_ACTLR(a) "SMMUX_S_IMP_ACTLR"
#define device_bar_BDK_SMMUX_S_IMP_ACTLR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_ACTLR(a) (a)
#define arguments_BDK_SMMUX_S_IMP_ACTLR(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_imp_bp_test0
 *
 * INTERNAL: SMMU backpressure Register
 */
union bdk_smmux_s_imp_bp_test0
{
    uint64_t u;
    struct bdk_smmux_s_imp_bp_test0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t enable                : 12; /**< [ 59: 48](SR/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<59\> = Unused
                                                                 \<58\> = Unused
                                                                 \<57\> = Limit the CCUI ACK rate
                                                                 \<56\> = Limit the CCUI CMD rate
                                                                 \<55\> = Limit the CCUI DAT rate
                                                                 \<54\> = Limit the CCUI RSP rate
                                                                 \<53\> = Limit the GIB rate
                                                                 \<52\> = Limit the WCU rate
                                                                 \<51\> = Limit the TLB rate
                                                                 \<50\> = Limit the FE-\>XL inv rate.
                                                                 \<49\> = Limit the FE-\>XL tran rate.
                                                                 \<48\> = Limit the FE input rate. */
        uint64_t reserved_40_47        : 8;
        uint64_t bp_cfg                : 24; /**< [ 39: 16](SR/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<39:38\> = Config 11.
                                                                   ..
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](SR/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](SR/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 24; /**< [ 39: 16](SR/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<39:38\> = Config 11.
                                                                   ..
                                                                   \<17:16\> = Config 0. */
        uint64_t reserved_40_47        : 8;
        uint64_t enable                : 12; /**< [ 59: 48](SR/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<59\> = Unused
                                                                 \<58\> = Unused
                                                                 \<57\> = Limit the CCUI ACK rate
                                                                 \<56\> = Limit the CCUI CMD rate
                                                                 \<55\> = Limit the CCUI DAT rate
                                                                 \<54\> = Limit the CCUI RSP rate
                                                                 \<53\> = Limit the GIB rate
                                                                 \<52\> = Limit the WCU rate
                                                                 \<51\> = Limit the TLB rate
                                                                 \<50\> = Limit the FE-\>XL inv rate.
                                                                 \<49\> = Limit the FE-\>XL tran rate.
                                                                 \<48\> = Limit the FE input rate. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_bp_test0_s cn; */
};
typedef union bdk_smmux_s_imp_bp_test0 bdk_smmux_s_imp_bp_test0_t;

static inline uint64_t BDK_SMMUX_S_IMP_BP_TEST0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_BP_TEST0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008e00ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IMP_BP_TEST0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IMP_BP_TEST0(a) bdk_smmux_s_imp_bp_test0_t
#define bustype_BDK_SMMUX_S_IMP_BP_TEST0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_IMP_BP_TEST0(a) "SMMUX_S_IMP_BP_TEST0"
#define device_bar_BDK_SMMUX_S_IMP_BP_TEST0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_BP_TEST0(a) (a)
#define arguments_BDK_SMMUX_S_IMP_BP_TEST0(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_imp_ctxc#_dat#
 *
 * SMMU Secure Context Cache Diagnostic Data Register
 */
union bdk_smmux_s_imp_ctxcx_datx
{
    uint64_t u;
    struct bdk_smmux_s_imp_ctxcx_datx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal context cache state, for diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal context cache state, for diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_ctxcx_datx_s cn; */
};
typedef union bdk_smmux_s_imp_ctxcx_datx bdk_smmux_s_imp_ctxcx_datx_t;

static inline uint64_t BDK_SMMUX_S_IMP_CTXCX_DATX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_CTXCX_DATX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=255) && (c<=7)))
        return 0x830000050000ll + 0x1000000000ll * ((a) & 0x0) + 0x40ll * ((b) & 0xff) + 8ll * ((c) & 0x7);
    __bdk_csr_fatal("SMMUX_S_IMP_CTXCX_DATX", 3, a, b, c, 0);
}

#define typedef_BDK_SMMUX_S_IMP_CTXCX_DATX(a,b,c) bdk_smmux_s_imp_ctxcx_datx_t
#define bustype_BDK_SMMUX_S_IMP_CTXCX_DATX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_IMP_CTXCX_DATX(a,b,c) "SMMUX_S_IMP_CTXCX_DATX"
#define device_bar_BDK_SMMUX_S_IMP_CTXCX_DATX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_CTXCX_DATX(a,b,c) (a)
#define arguments_BDK_SMMUX_S_IMP_CTXCX_DATX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB32b) smmu#_s_imp_diag_ctl
 *
 * SMMU Secure Diagnostic Control Register
 */
union bdk_smmux_s_imp_diag_ctl
{
    uint32_t u;
    struct bdk_smmux_s_imp_diag_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t crsp_id               : 2;  /**< [ 13: 12](SR/W) Which SMMU slave responds to CSR request. Values greater than the number of slaves are
                                                                 reserved and are treated as zero.  For diagnostic use only. */
        uint32_t shrink_config_cache_size : 1;/**< [ 11: 11](SR/W) Shrinks the configuration cache size to 32 entry's. For diagnostic use only. */
        uint32_t force_clks_active     : 1;  /**< [ 10: 10](SR/W) Forces the conditional clocks to be always on. Only affects clocks in the slave.  For
                                                                 diagnostic use only. */
        uint32_t dis_ctx               : 1;  /**< [  9:  9](SR/W) Disables hitting in the CTXC. For diagnostic use only. */
        uint32_t dis_tlb               : 1;  /**< [  8:  8](SR/W) Disables hitting in the TLB. For diagnostic use only. */
        uint32_t dis_wcs1              : 2;  /**< [  7:  6](SR/W) Disables hitting in the walk cache for stage 1 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint32_t dis_wcs2              : 2;  /**< [  5:  4](SR/W) Disables hitting in the walk cache for stage 2 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint32_t walkers               : 4;  /**< [  3:  0](SR/W) Number of walkers. The number of page table walkers that may
                                                                 simultaneously be executing, minus one.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's.
                                                                 For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint32_t walkers               : 4;  /**< [  3:  0](SR/W) Number of walkers. The number of page table walkers that may
                                                                 simultaneously be executing, minus one.
                                                                 SMMU1 uses SMMU0's register value; SMMU3 uses SMMU2's.
                                                                 For diagnostic use only. */
        uint32_t dis_wcs2              : 2;  /**< [  5:  4](SR/W) Disables hitting in the walk cache for stage 2 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint32_t dis_wcs1              : 2;  /**< [  7:  6](SR/W) Disables hitting in the walk cache for stage 1 translations. For diagnostic use only.
                                                                 0x0 = Normal operation. Allow hits at all levels.
                                                                 0x1 = Never hit.
                                                                 0x2 = Allow hits on table levels 0 and 1.
                                                                 0x3 = Reserved. */
        uint32_t dis_tlb               : 1;  /**< [  8:  8](SR/W) Disables hitting in the TLB. For diagnostic use only. */
        uint32_t dis_ctx               : 1;  /**< [  9:  9](SR/W) Disables hitting in the CTXC. For diagnostic use only. */
        uint32_t force_clks_active     : 1;  /**< [ 10: 10](SR/W) Forces the conditional clocks to be always on. Only affects clocks in the slave.  For
                                                                 diagnostic use only. */
        uint32_t shrink_config_cache_size : 1;/**< [ 11: 11](SR/W) Shrinks the configuration cache size to 32 entry's. For diagnostic use only. */
        uint32_t crsp_id               : 2;  /**< [ 13: 12](SR/W) Which SMMU slave responds to CSR request. Values greater than the number of slaves are
                                                                 reserved and are treated as zero.  For diagnostic use only. */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_diag_ctl_s cn; */
};
typedef union bdk_smmux_s_imp_diag_ctl bdk_smmux_s_imp_diag_ctl_t;

static inline uint64_t BDK_SMMUX_S_IMP_DIAG_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_DIAG_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008e14ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IMP_DIAG_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IMP_DIAG_CTL(a) bdk_smmux_s_imp_diag_ctl_t
#define bustype_BDK_SMMUX_S_IMP_DIAG_CTL(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IMP_DIAG_CTL(a) "SMMUX_S_IMP_DIAG_CTL"
#define device_bar_BDK_SMMUX_S_IMP_DIAG_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_DIAG_CTL(a) (a)
#define arguments_BDK_SMMUX_S_IMP_DIAG_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_imp_eva_acam#_dat
 *
 * SMMU Secure EVA_ACAM Data Register
 */
union bdk_smmux_s_imp_eva_acamx_dat
{
    uint64_t u;
    struct bdk_smmux_s_imp_eva_acamx_dat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal eva cam, for diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal eva cam, for diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_eva_acamx_dat_s cn; */
};
typedef union bdk_smmux_s_imp_eva_acamx_dat bdk_smmux_s_imp_eva_acamx_dat_t;

static inline uint64_t BDK_SMMUX_S_IMP_EVA_ACAMX_DAT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_EVA_ACAMX_DAT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=255)))
        return 0x83000005c000ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0xff);
    __bdk_csr_fatal("SMMUX_S_IMP_EVA_ACAMX_DAT", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_S_IMP_EVA_ACAMX_DAT(a,b) bdk_smmux_s_imp_eva_acamx_dat_t
#define bustype_BDK_SMMUX_S_IMP_EVA_ACAMX_DAT(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_IMP_EVA_ACAMX_DAT(a,b) "SMMUX_S_IMP_EVA_ACAMX_DAT"
#define device_bar_BDK_SMMUX_S_IMP_EVA_ACAMX_DAT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_EVA_ACAMX_DAT(a,b) (a)
#define arguments_BDK_SMMUX_S_IMP_EVA_ACAMX_DAT(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_s_imp_eva_vcam#_dat
 *
 * SMMU Secure EVA_VCAM Data Register
 */
union bdk_smmux_s_imp_eva_vcamx_dat
{
    uint64_t u;
    struct bdk_smmux_s_imp_eva_vcamx_dat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal eva cam, for diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal eva cam, for diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_eva_vcamx_dat_s cn; */
};
typedef union bdk_smmux_s_imp_eva_vcamx_dat bdk_smmux_s_imp_eva_vcamx_dat_t;

static inline uint64_t BDK_SMMUX_S_IMP_EVA_VCAMX_DAT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_EVA_VCAMX_DAT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=255)))
        return 0x83000005d000ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0xff);
    __bdk_csr_fatal("SMMUX_S_IMP_EVA_VCAMX_DAT", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_S_IMP_EVA_VCAMX_DAT(a,b) bdk_smmux_s_imp_eva_vcamx_dat_t
#define bustype_BDK_SMMUX_S_IMP_EVA_VCAMX_DAT(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_IMP_EVA_VCAMX_DAT(a,b) "SMMUX_S_IMP_EVA_VCAMX_DAT"
#define device_bar_BDK_SMMUX_S_IMP_EVA_VCAMX_DAT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_EVA_VCAMX_DAT(a,b) (a)
#define arguments_BDK_SMMUX_S_IMP_EVA_VCAMX_DAT(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_s_imp_raz0
 *
 * INTERNAL: SMMU Read-As-Zero 0 Register
 */
union bdk_smmux_s_imp_raz0
{
    uint32_t u;
    struct bdk_smmux_s_imp_raz0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_raz0_s cn; */
};
typedef union bdk_smmux_s_imp_raz0 bdk_smmux_s_imp_raz0_t;

static inline uint64_t BDK_SMMUX_S_IMP_RAZ0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_RAZ0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008038ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IMP_RAZ0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IMP_RAZ0(a) bdk_smmux_s_imp_raz0_t
#define bustype_BDK_SMMUX_S_IMP_RAZ0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IMP_RAZ0(a) "SMMUX_S_IMP_RAZ0"
#define device_bar_BDK_SMMUX_S_IMP_RAZ0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_RAZ0(a) (a)
#define arguments_BDK_SMMUX_S_IMP_RAZ0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_imp_raz1
 *
 * INTERNAL: SMMU Read-As-Zero 1 Register
 */
union bdk_smmux_s_imp_raz1
{
    uint32_t u;
    struct bdk_smmux_s_imp_raz1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_raz1_s cn; */
};
typedef union bdk_smmux_s_imp_raz1 bdk_smmux_s_imp_raz1_t;

static inline uint64_t BDK_SMMUX_S_IMP_RAZ1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_RAZ1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008040ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IMP_RAZ1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IMP_RAZ1(a) bdk_smmux_s_imp_raz1_t
#define bustype_BDK_SMMUX_S_IMP_RAZ1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IMP_RAZ1(a) "SMMUX_S_IMP_RAZ1"
#define device_bar_BDK_SMMUX_S_IMP_RAZ1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_RAZ1(a) (a)
#define arguments_BDK_SMMUX_S_IMP_RAZ1(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_imp_rstr#_dat#
 *
 * SMMU Secure Restore Buffer Diagnostic Data Register
 */
union bdk_smmux_s_imp_rstrx_datx
{
    uint64_t u;
    struct bdk_smmux_s_imp_rstrx_datx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal restore buffer state, for diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal restore buffer state, for diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_rstrx_datx_s cn; */
};
typedef union bdk_smmux_s_imp_rstrx_datx bdk_smmux_s_imp_rstrx_datx_t;

static inline uint64_t BDK_SMMUX_S_IMP_RSTRX_DATX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_RSTRX_DATX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=511) && (c<=1)))
        return 0x830000058000ll + 0x1000000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x1ff) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("SMMUX_S_IMP_RSTRX_DATX", 3, a, b, c, 0);
}

#define typedef_BDK_SMMUX_S_IMP_RSTRX_DATX(a,b,c) bdk_smmux_s_imp_rstrx_datx_t
#define bustype_BDK_SMMUX_S_IMP_RSTRX_DATX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_IMP_RSTRX_DATX(a,b,c) "SMMUX_S_IMP_RSTRX_DATX"
#define device_bar_BDK_SMMUX_S_IMP_RSTRX_DATX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_RSTRX_DATX(a,b,c) (a)
#define arguments_BDK_SMMUX_S_IMP_RSTRX_DATX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) smmu#_s_imp_tlb#_dat#
 *
 * SMMU Secure TLB Diagnostic Data Register
 */
union bdk_smmux_s_imp_tlbx_datx
{
    uint64_t u;
    struct bdk_smmux_s_imp_tlbx_datx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal TLB state, for diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal TLB state, for diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_tlbx_datx_s cn; */
};
typedef union bdk_smmux_s_imp_tlbx_datx bdk_smmux_s_imp_tlbx_datx_t;

static inline uint64_t BDK_SMMUX_S_IMP_TLBX_DATX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_TLBX_DATX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=2047) && (c<=3)))
        return 0x830000020000ll + 0x1000000000ll * ((a) & 0x0) + 0x20ll * ((b) & 0x7ff) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("SMMUX_S_IMP_TLBX_DATX", 3, a, b, c, 0);
}

#define typedef_BDK_SMMUX_S_IMP_TLBX_DATX(a,b,c) bdk_smmux_s_imp_tlbx_datx_t
#define bustype_BDK_SMMUX_S_IMP_TLBX_DATX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_IMP_TLBX_DATX(a,b,c) "SMMUX_S_IMP_TLBX_DATX"
#define device_bar_BDK_SMMUX_S_IMP_TLBX_DATX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_TLBX_DATX(a,b,c) (a)
#define arguments_BDK_SMMUX_S_IMP_TLBX_DATX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) smmu#_s_imp_wcu#_dat#
 *
 * SMMU Secure Walker Cache Diagnostic Data Register
 */
union bdk_smmux_s_imp_wcux_datx
{
    uint64_t u;
    struct bdk_smmux_s_imp_wcux_datx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal walker cache state, for diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal walker cache state, for diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_imp_wcux_datx_s cn; */
};
typedef union bdk_smmux_s_imp_wcux_datx bdk_smmux_s_imp_wcux_datx_t;

static inline uint64_t BDK_SMMUX_S_IMP_WCUX_DATX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IMP_WCUX_DATX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a==0) && (b<=1023) && (c<=3)))
        return 0x830000040000ll + 0x1000000000ll * ((a) & 0x0) + 0x20ll * ((b) & 0x3ff) + 8ll * ((c) & 0x3);
    __bdk_csr_fatal("SMMUX_S_IMP_WCUX_DATX", 3, a, b, c, 0);
}

#define typedef_BDK_SMMUX_S_IMP_WCUX_DATX(a,b,c) bdk_smmux_s_imp_wcux_datx_t
#define bustype_BDK_SMMUX_S_IMP_WCUX_DATX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_IMP_WCUX_DATX(a,b,c) "SMMUX_S_IMP_WCUX_DATX"
#define device_bar_BDK_SMMUX_S_IMP_WCUX_DATX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IMP_WCUX_DATX(a,b,c) (a)
#define arguments_BDK_SMMUX_S_IMP_WCUX_DATX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB32b) smmu#_s_init
 *
 * SMMU Secure INIT Register
 */
union bdk_smmux_s_init
{
    uint32_t u;
    struct bdk_smmux_s_init_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t inv_all               : 1;  /**< [  0:  0](SR/W/H) Invalidate all cache and TLB contents. When written to one, an SMMU-global
                                                                 invalidation is performed for all configuration and translation caches for all
                                                                 translation regimes and security worlds. This field is reset to zero by the SMMU
                                                                 when the invalidation is complete.

                                                                 This field can be used to simplify secure software that otherwise makes no use
                                                                 of the SMMU yet must safely initialize the SMMU for use by non-secure software. */
#else /* Word 0 - Little Endian */
        uint32_t inv_all               : 1;  /**< [  0:  0](SR/W/H) Invalidate all cache and TLB contents. When written to one, an SMMU-global
                                                                 invalidation is performed for all configuration and translation caches for all
                                                                 translation regimes and security worlds. This field is reset to zero by the SMMU
                                                                 when the invalidation is complete.

                                                                 This field can be used to simplify secure software that otherwise makes no use
                                                                 of the SMMU yet must safely initialize the SMMU for use by non-secure software. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_init_s cn; */
};
typedef union bdk_smmux_s_init bdk_smmux_s_init_t;

static inline uint64_t BDK_SMMUX_S_INIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_INIT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x83000000803cll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_INIT", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_INIT(a) bdk_smmux_s_init_t
#define bustype_BDK_SMMUX_S_INIT(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_INIT(a) "SMMUX_S_INIT"
#define device_bar_BDK_SMMUX_S_INIT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_INIT(a) (a)
#define arguments_BDK_SMMUX_S_INIT(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_irq_ctrl
 *
 * SMMU Secure IRQ Control Register
 * An update to a field in SMMU()_S_IRQ_CTRL is not considered complete, along with any
 * side-effects, until the respective field in SMMU()_S_IRQ_CTRLACK is observed to take
 * the new value.
 */
union bdk_smmux_s_irq_ctrl
{
    uint32_t u;
    struct bdk_smmux_s_irq_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t eventq_irqen          : 1;  /**< [  2:  2](SR/W) Secure event queue interrupt enable. */
        uint32_t reserved_1            : 1;
        uint32_t gerror_irqen          : 1;  /**< [  0:  0](SR/W) Secure GERROR interrupt enable. */
#else /* Word 0 - Little Endian */
        uint32_t gerror_irqen          : 1;  /**< [  0:  0](SR/W) Secure GERROR interrupt enable. */
        uint32_t reserved_1            : 1;
        uint32_t eventq_irqen          : 1;  /**< [  2:  2](SR/W) Secure event queue interrupt enable. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_irq_ctrl_s cn; */
};
typedef union bdk_smmux_s_irq_ctrl bdk_smmux_s_irq_ctrl_t;

static inline uint64_t BDK_SMMUX_S_IRQ_CTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IRQ_CTRL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008050ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IRQ_CTRL", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IRQ_CTRL(a) bdk_smmux_s_irq_ctrl_t
#define bustype_BDK_SMMUX_S_IRQ_CTRL(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IRQ_CTRL(a) "SMMUX_S_IRQ_CTRL"
#define device_bar_BDK_SMMUX_S_IRQ_CTRL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IRQ_CTRL(a) (a)
#define arguments_BDK_SMMUX_S_IRQ_CTRL(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_irq_ctrlack
 *
 * SMMU Secure IRQ Control Acknowledgement Register
 * This register is a read-only copy of SMMU()_S_IRQ_CTRL.
 */
union bdk_smmux_s_irq_ctrlack
{
    uint32_t u;
    struct bdk_smmux_s_irq_ctrlack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t eventq_irqen          : 1;  /**< [  2:  2](SRO/H) Read-only hardware-modified SMMU(0)_S_IRQ_CTRL[EVENTQ_IRQEN]. */
        uint32_t reserved_1            : 1;
        uint32_t gerror_irqen          : 1;  /**< [  0:  0](SRO/H) Read-only hardware-modified SMMU(0)_S_IRQ_CTRL[GERROR_IRQEN]. */
#else /* Word 0 - Little Endian */
        uint32_t gerror_irqen          : 1;  /**< [  0:  0](SRO/H) Read-only hardware-modified SMMU(0)_S_IRQ_CTRL[GERROR_IRQEN]. */
        uint32_t reserved_1            : 1;
        uint32_t eventq_irqen          : 1;  /**< [  2:  2](SRO/H) Read-only hardware-modified SMMU(0)_S_IRQ_CTRL[EVENTQ_IRQEN]. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_irq_ctrlack_s cn; */
};
typedef union bdk_smmux_s_irq_ctrlack bdk_smmux_s_irq_ctrlack_t;

static inline uint64_t BDK_SMMUX_S_IRQ_CTRLACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_IRQ_CTRLACK(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008054ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_IRQ_CTRLACK", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_IRQ_CTRLACK(a) bdk_smmux_s_irq_ctrlack_t
#define bustype_BDK_SMMUX_S_IRQ_CTRLACK(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_IRQ_CTRLACK(a) "SMMUX_S_IRQ_CTRLACK"
#define device_bar_BDK_SMMUX_S_IRQ_CTRLACK(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_IRQ_CTRLACK(a) (a)
#define arguments_BDK_SMMUX_S_IRQ_CTRLACK(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_s_strtab_base
 *
 * SMMU Secure STRTAB Base Register
 */
union bdk_smmux_s_strtab_base
{
    uint64_t u;
    struct bdk_smmux_s_strtab_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t ra                    : 1;  /**< [ 62: 62](SR/W) Read allocate hint.
                                                                 0 = No read-allocate.
                                                                 1 = Read-allocate. */
        uint64_t reserved_52_61        : 10;
        uint64_t addr                  : 46; /**< [ 51:  6](SR/W) PA of stream table base.
                                                                 The effective base address has [ADDR]\<63:52\> = 0x0 and [ADDR]\<5:0\> = 0x0.

                                                                 When a linear stream table is used (SMMU()_S_STRTAB_BASE_CFG[FMT]=0x0), the
                                                                 effective base address is aligned to the table size, ignoring the
                                                                 least-significant bits in the [ADDR]\<47:6\> range as required to do so; i.e.,
                                                                 ADDR\<LOG2SIZE+5:0\> = 0.

                                                                 When a two-stage stream table is used (SMMU()_S_STRTAB_BASE_CFG[FMT]=0x1), the
                                                                 effective base address is aligned to the larger of 64 bytes or the first-level
                                                                 table size.  I.e., ADDR\<MAX(5, (LOG2SIZE-SPLIT-1+3)):0\> = 0.

                                                                 The alignment of [ADDR] is affected by the literal value of the respective
                                                                 SMMU()_S_STRTAB_BASE_CFG[LOG2SIZE] field and is not limited by SMMU()_S_IDR1[S_SIDSIZE].
                                                                 This means that configuring a table that is larger than required by the incoming
                                                                 StreamID span results in some entries being unreachable, but the table must be
                                                                 aligned to the configured size. */
        uint64_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_5          : 6;
        uint64_t addr                  : 46; /**< [ 51:  6](SR/W) PA of stream table base.
                                                                 The effective base address has [ADDR]\<63:52\> = 0x0 and [ADDR]\<5:0\> = 0x0.

                                                                 When a linear stream table is used (SMMU()_S_STRTAB_BASE_CFG[FMT]=0x0), the
                                                                 effective base address is aligned to the table size, ignoring the
                                                                 least-significant bits in the [ADDR]\<47:6\> range as required to do so; i.e.,
                                                                 ADDR\<LOG2SIZE+5:0\> = 0.

                                                                 When a two-stage stream table is used (SMMU()_S_STRTAB_BASE_CFG[FMT]=0x1), the
                                                                 effective base address is aligned to the larger of 64 bytes or the first-level
                                                                 table size.  I.e., ADDR\<MAX(5, (LOG2SIZE-SPLIT-1+3)):0\> = 0.

                                                                 The alignment of [ADDR] is affected by the literal value of the respective
                                                                 SMMU()_S_STRTAB_BASE_CFG[LOG2SIZE] field and is not limited by SMMU()_S_IDR1[S_SIDSIZE].
                                                                 This means that configuring a table that is larger than required by the incoming
                                                                 StreamID span results in some entries being unreachable, but the table must be
                                                                 aligned to the configured size. */
        uint64_t reserved_52_61        : 10;
        uint64_t ra                    : 1;  /**< [ 62: 62](SR/W) Read allocate hint.
                                                                 0 = No read-allocate.
                                                                 1 = Read-allocate. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_strtab_base_s cn; */
};
typedef union bdk_smmux_s_strtab_base bdk_smmux_s_strtab_base_t;

static inline uint64_t BDK_SMMUX_S_STRTAB_BASE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_STRTAB_BASE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008080ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_STRTAB_BASE", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_STRTAB_BASE(a) bdk_smmux_s_strtab_base_t
#define bustype_BDK_SMMUX_S_STRTAB_BASE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_S_STRTAB_BASE(a) "SMMUX_S_STRTAB_BASE"
#define device_bar_BDK_SMMUX_S_STRTAB_BASE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_STRTAB_BASE(a) (a)
#define arguments_BDK_SMMUX_S_STRTAB_BASE(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_s_strtab_base_cfg
 *
 * SMMU Secure Command Queue Base Register
 * SMMU()_S_STRTAB_BASE_CFG is guarded by the respective SMMU()_S_CR0[SMMUEN] and
 * must only be modified when SMMU()_S_CR0[SMMUEN]=0. A write whilst
 * SMMU()_S_CR0[SMMUEN]=1 is constrained unpredictable and has one of the following
 * behaviors:
 *
 * * The register takes on any value, which might cause STEs to be fetched from an unpredictable
 *   address.
 *
 * * The write is ignored.
 *
 * * In CNXXXX, TBD which.
 *
 * A read following such a write will return an unknown value.
 *
 * Use of any reserved value or unsupported value combination in this register (for
 * example, selection of a two-level table when unsupported where
 * SMMU()_IDR0[ST_LEVEL]=0x0) causes the stream table to become inaccessible; a
 * transaction causing a lookup of an STE is terminated with abort and a SMMU_C_BAD_STREAMID_S
 * event recorded.
 */
union bdk_smmux_s_strtab_base_cfg
{
    uint32_t u;
    struct bdk_smmux_s_strtab_base_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t fmt                   : 2;  /**< [ 17: 16](SR/W) Format of stream table.
                                                                 0x0 = Linear. ADDR points to an array of STEs.
                                                                 0x1 = 2-level. ADDR points to an array of level 1 stream table descriptors.

                                                                 Other values are reserved, behaving as 0x0.

                                                                 Internal:
                                                                 When SMMU()_IDR0[ST_LEVEL]=0x0 (2-level unsupported), this field is RES0: its
                                                                 effective value is 0x0 regardless of any other value written. */
        uint32_t reserved_11_15        : 5;
        uint32_t split                 : 5;  /**< [ 10:  6](SR/W) StreamID split point for multi-level table.
                                                                 Determines the split point of a two-level stream table, selected by the
                                                                 number of bits at the bottom level.

                                                                   0x6 = 4KB leaf tables.
                                                                   0x8 = 16KB leaf tables.
                                                                   0xA = 64KB leaf tables.
                                                                   _ Other values are reserved, behaving as 0x6.

                                                                 For example, selecting [SPLIT]=6 causes StreamID\<5:0\> to be used to index the
                                                                 lowest level stream table and StreamID\<LOG2SIZE-1:6\> to index the upper level
                                                                 table.

                                                                 The effective value of [SPLIT] is capped at [LOG2SIZE]; a value greater or equal
                                                                 to [LOG2SIZE] results in a single upper-level descriptor indicating one
                                                                 bottom-level stream table of [LOG2SIZE].  This combination is not recommended; a
                                                                 more efficient linear ([FMT]=0x0) table should instead be used.

                                                                 Internal:
                                                                 This field is ignored if FMT=0x0 and this field is RES0 when
                                                                 SMMU()_IDR0[ST_LEVEL]=0x0 (2-level unsupported). */
        uint32_t log2size              : 6;  /**< [  5:  0](SR/W) Table size as log2(entries). The maximum index into the stream table is limited
                                                                 by SMMU()_IDR1[SIDSIZE]. For indexing purposes, [LOG2SIZE] \>
                                                                 SMMU()_IDR1[SIDSIZE] and setting a value greater than SMMU()_IDR1[SIDSIZE] causes a table
                                                                 to be indexed based on that maximum size.

                                                                 In the SMMU()_S_STRTAB_BASE_CFG variant, the maximum effective index of secure
                                                                 stream table [LOG2SIZE] \> SMMU()_S_IDR1[S_SIDSIZE] instead. */
#else /* Word 0 - Little Endian */
        uint32_t log2size              : 6;  /**< [  5:  0](SR/W) Table size as log2(entries). The maximum index into the stream table is limited
                                                                 by SMMU()_IDR1[SIDSIZE]. For indexing purposes, [LOG2SIZE] \>
                                                                 SMMU()_IDR1[SIDSIZE] and setting a value greater than SMMU()_IDR1[SIDSIZE] causes a table
                                                                 to be indexed based on that maximum size.

                                                                 In the SMMU()_S_STRTAB_BASE_CFG variant, the maximum effective index of secure
                                                                 stream table [LOG2SIZE] \> SMMU()_S_IDR1[S_SIDSIZE] instead. */
        uint32_t split                 : 5;  /**< [ 10:  6](SR/W) StreamID split point for multi-level table.
                                                                 Determines the split point of a two-level stream table, selected by the
                                                                 number of bits at the bottom level.

                                                                   0x6 = 4KB leaf tables.
                                                                   0x8 = 16KB leaf tables.
                                                                   0xA = 64KB leaf tables.
                                                                   _ Other values are reserved, behaving as 0x6.

                                                                 For example, selecting [SPLIT]=6 causes StreamID\<5:0\> to be used to index the
                                                                 lowest level stream table and StreamID\<LOG2SIZE-1:6\> to index the upper level
                                                                 table.

                                                                 The effective value of [SPLIT] is capped at [LOG2SIZE]; a value greater or equal
                                                                 to [LOG2SIZE] results in a single upper-level descriptor indicating one
                                                                 bottom-level stream table of [LOG2SIZE].  This combination is not recommended; a
                                                                 more efficient linear ([FMT]=0x0) table should instead be used.

                                                                 Internal:
                                                                 This field is ignored if FMT=0x0 and this field is RES0 when
                                                                 SMMU()_IDR0[ST_LEVEL]=0x0 (2-level unsupported). */
        uint32_t reserved_11_15        : 5;
        uint32_t fmt                   : 2;  /**< [ 17: 16](SR/W) Format of stream table.
                                                                 0x0 = Linear. ADDR points to an array of STEs.
                                                                 0x1 = 2-level. ADDR points to an array of level 1 stream table descriptors.

                                                                 Other values are reserved, behaving as 0x0.

                                                                 Internal:
                                                                 When SMMU()_IDR0[ST_LEVEL]=0x0 (2-level unsupported), this field is RES0: its
                                                                 effective value is 0x0 regardless of any other value written. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_s_strtab_base_cfg_s cn; */
};
typedef union bdk_smmux_s_strtab_base_cfg bdk_smmux_s_strtab_base_cfg_t;

static inline uint64_t BDK_SMMUX_S_STRTAB_BASE_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_S_STRTAB_BASE_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000008088ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_S_STRTAB_BASE_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_S_STRTAB_BASE_CFG(a) bdk_smmux_s_strtab_base_cfg_t
#define bustype_BDK_SMMUX_S_STRTAB_BASE_CFG(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_S_STRTAB_BASE_CFG(a) "SMMUX_S_STRTAB_BASE_CFG"
#define device_bar_BDK_SMMUX_S_STRTAB_BASE_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_S_STRTAB_BASE_CFG(a) (a)
#define arguments_BDK_SMMUX_S_STRTAB_BASE_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_sacr
 *
 * SMMU (Secure) Auxiliary Control Register
 * This register contains implementation specific context fields.
 */
union bdk_smmux_sacr
{
    uint32_t u;
    struct bdk_smmux_sacr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t qos                   : 4;  /**< [ 31: 28](R/W) L2C quality-of-service value to use for standard transactions that are not by a specific
                                                                 context, and so SMMU()_CB()_ACTLR[QOS] is not applicable. */
        uint32_t qos_walk              : 4;  /**< [ 27: 24](R/W) L2C quality-of-service value to use for page table walks. For optimal performance, this
                                                                 typically would be set to the most preferential QoS value of zero. */
        uint32_t reserved_0_23         : 24;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_23         : 24;
        uint32_t qos_walk              : 4;  /**< [ 27: 24](R/W) L2C quality-of-service value to use for page table walks. For optimal performance, this
                                                                 typically would be set to the most preferential QoS value of zero. */
        uint32_t qos                   : 4;  /**< [ 31: 28](R/W) L2C quality-of-service value to use for standard transactions that are not by a specific
                                                                 context, and so SMMU()_CB()_ACTLR[QOS] is not applicable. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_sacr_s cn; */
};
typedef union bdk_smmux_sacr bdk_smmux_sacr_t;

static inline uint64_t BDK_SMMUX_SACR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SACR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000010ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000010ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000010ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SACR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SACR(a) bdk_smmux_sacr_t
#define bustype_BDK_SMMUX_SACR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SACR(a) "SMMUX_SACR"
#define device_bar_BDK_SMMUX_SACR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SACR(a) (a)
#define arguments_BDK_SMMUX_SACR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_scr0
 *
 * SMMU (Secure) Configuration Register 0
 * The nonsecure version of this register does not provide full top-level control of the SMMU.
 * Some fields only apply to secure or nonsecure transactions.
 */
union bdk_smmux_scr0
{
    uint32_t u;
    struct bdk_smmux_scr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t vmid16en              : 1;  /**< [ 31: 31](R/W) Handling of 16-bit VMID extension:
                                                                 0 = 8-bit VMIDs are in use.
                                                                 The VMID is held in SMMU()_CBAR()[VMID].
                                                                 The SMMU()_CBA2R()[VMID16] field is 0.

                                                                 1 = 16-bit VMIDs are in use.
                                                                 The VMID is held in SMMU()_CBA2R()[VMID16].
                                                                 The SMMU()_CBAR()[VMID] field is 0.

                                                                 Only exists in the nonsecure copy of this register.

                                                                 In pass 1, this field must be 0. */
        uint32_t hypmode               : 1;  /**< [ 30: 30](R/W) Hypervisor mode. Selects which hypervisor context is used:
                                                                   0 = When SMMU()_CBAR()[CTYPE] = 0x1, SMMU()_CBAR()\<10\> represents HYPC.
                                                                   1 = When SMMU()_CBAR()[CTYPE] = 0x1, SMMU()_CBAR()\<10\> represents E2HC.

                                                                 If this bit is changed, TLB maintenance is required.

                                                                 Only exists in the non secure copy of this register. */
        uint32_t nscfg                 : 2;  /**< [ 29: 28](SR/W) Nonsecure configuration. Only exist in secure copy of register, RES0 in nonsecure copy.
                                                                 This field only applies to secure transactions bypassing the SMMU stream mapping
                                                                 process.
                                                                 0x0 = Use default NS attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Secure.
                                                                 0x3 = Nonsecure. */
        uint32_t wacfg                 : 2;  /**< [ 27: 26](RO) Write-allocate configuration, controls the allocation hint for write accesses. This field
                                                                 applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Write-allocate.
                                                                 0x3 = No write-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t racfg                 : 2;  /**< [ 25: 24](RO) Read-allocate configuration, controls the allocation hint for read accesses. This field
                                                                 applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Read-allocate.
                                                                 0x3 = No read-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t shcfg                 : 2;  /**< [ 23: 22](RO) Shared configuration. Applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default shareable attributes.
                                                                 0x1 = Outer sharable.
                                                                 0x2 = Inner sharable.
                                                                 0x3 = Non-sharable.

                                                                 Ignored in CNXXXX. */
        uint32_t smcfcfg               : 1;  /**< [ 21: 21](RO) Stream match conflict fault configuration. Controls transactions with multiple matches in
                                                                 the stream mapping table.
                                                                 0 = Permit the transaction to bypass the SMMU.
                                                                 1 = Raise a stream match conflict fault.

                                                                 CNXXXX detects all stream match conflicts and always faults. */
        uint32_t mtcfg                 : 1;  /**< [ 20: 20](R/W) Memory type configuration, applies to transactions that bypass the stream mapping table.
                                                                 0 = Use the default memory attributes.
                                                                 1 = Use the MEMATTR field for memory attributes. */
        uint32_t memattr               : 4;  /**< [ 19: 16](R/W) Memory attributes for bypass transactions if MTCFG == 1. */
        uint32_t bsu                   : 2;  /**< [ 15: 14](RO) Barrier sharability upgrade. Upgrades the sharability of barriers issued by client devices
                                                                 that are not mapped to a translation context bank by setting the minimum sharability
                                                                 domain applied to any barrier.  Applies to transactions bypassing the stream mapping
                                                                 table.
                                                                 0x0 = No effect.
                                                                 0x1 = Inner sharable.
                                                                 0x2 = Outer sharable.
                                                                 0x3 = Full system.

                                                                 Ignored in CNXXXX. */
        uint32_t fb                    : 1;  /**< [ 13: 13](R/W) Force broadcast of TLB and instruction cache maintenance operations. Applies to
                                                                 transactions bypassing the stream mapping table. Affects client TLB maintenance, BPIALL
                                                                 and ICIALLU operations. If FB=1, any affected operation is modified to the equivalent
                                                                 broadcast variant in the inner shareable domain.
                                                                 0 = Process affected operations as presented.
                                                                 1 = Upgrade affected operations to be broadcast within the inner sharable domain.

                                                                 Ignored in CNXXXX, as NCB clients do not initiate invalidates. */
        uint32_t ptm                   : 1;  /**< [ 12: 12](R/W) Private TLB maintenance hint.
                                                                 0 = Process affected operations as presented.
                                                                 1 = SMMU TLBs are privately managed and are not require to respond to broadcast TLB
                                                                 maintenance operations from the wider system.

                                                                 CNXXXX honors this hint, but both the secure and nonsecure version must be set for
                                                                 private management.

                                                                 Internal:
                                                                 Note when set SMMU always still sends a response for the
                                                                 invalidates, it just does not perform the invalidation action against the TLB/WCU. */
        uint32_t vmidpne               : 1;  /**< [ 11: 11](RO) Reserved. */
        uint32_t usfcfg                : 1;  /**< [ 10: 10](R/W) Unidentified stream fault configuration.
                                                                 0 = Permit any transaction that does not match any entries in the stream matching table to
                                                                 pass through.
                                                                 1 = Raise an unidentified stream fault on any transaction that does not match any stream
                                                                 matching table entry. */
        uint32_t gse                   : 1;  /**< [  9:  9](RO) Global stall enable.
                                                                 0 = Do not enforce global stalling across contexts.
                                                                 1 = Enforce global stalling across contexts.

                                                                 In CNXXXX always 0, no stalling. */
        uint32_t stalld                : 1;  /**< [  8:  8](RO) Stall disable.
                                                                 0 = Permit per-context stalling on context faults.
                                                                 1 = Disable per-context stalling on context faults, or not programmable.

                                                                 In CNXXXX always 1, no stalling. */
        uint32_t transientcfg          : 2;  /**< [  7:  6](RO) Transient configuration controls the transient allocation hint.
                                                                 0x0 = Default transient allocation attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Non-transient.
                                                                 0x3 = Transient.

                                                                 Not implemented in CNXXXX. */
        uint32_t gcfgfie               : 1;  /**< [  5:  5](RO) Global configuration fault interrupt enable.
                                                                 0 = Do not raise an interrupt on a global configuration fault.
                                                                 1 = Raise an interrupt on a global configuration fault.

                                                                 In CNXXXX always zero, as does not support configuration faults. */
        uint32_t gcfgfre               : 1;  /**< [  4:  4](RO) Global configuration fault report enable.
                                                                 0 = Do not return an abort on a global configuration fault
                                                                 1 = Return an abort on a global configuration fault.

                                                                 In CNXXXX always zero, as does not support configuration faults. */
        uint32_t exidenable            : 1;  /**< [  3:  3](R/W) Extended stream ID enable.
                                                                 0 = For this SSD, SMMU()_SMR() has the format with the VALID bit in the
                                                                 SMMU()_SMR(). The SMMU()_S2CR()[EXIDVALID] is ignored.
                                                                 1 = For this SSD, SMMU()_SMR() has the extended id format and the valid bit is
                                                                 held in the corresponding SMMU()_S2CR()[EXIDVALID].

                                                                 Software should only change [EXIDENABLE] when all SMMU()_S2CR()[EXIDVALID] == 0
                                                                 and SMMU()_SMR()[EXMASK[15]/VALID] == 0 for the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized before use. */
        uint32_t gfie                  : 1;  /**< [  2:  2](R/W) Global fault interrupt enable.
                                                                 0 = Do not raise an interrupt on a global fault.
                                                                 1 = Raise an interrupt on a global fault. */
        uint32_t gfre                  : 1;  /**< [  1:  1](R/W) Global fault report enable.
                                                                 0 = Do not return an abort on a global fault.
                                                                 1 = Return an abort on a global fault. */
        uint32_t clientpd              : 1;  /**< [  0:  0](R/W) Client port disable.
                                                                 0 = Each SMMU client access is subject to translation, access control and attribute
                                                                 generation.
                                                                 1 = Each SMMU client access bypasses translation, access control and attribute generation. */
#else /* Word 0 - Little Endian */
        uint32_t clientpd              : 1;  /**< [  0:  0](R/W) Client port disable.
                                                                 0 = Each SMMU client access is subject to translation, access control and attribute
                                                                 generation.
                                                                 1 = Each SMMU client access bypasses translation, access control and attribute generation. */
        uint32_t gfre                  : 1;  /**< [  1:  1](R/W) Global fault report enable.
                                                                 0 = Do not return an abort on a global fault.
                                                                 1 = Return an abort on a global fault. */
        uint32_t gfie                  : 1;  /**< [  2:  2](R/W) Global fault interrupt enable.
                                                                 0 = Do not raise an interrupt on a global fault.
                                                                 1 = Raise an interrupt on a global fault. */
        uint32_t exidenable            : 1;  /**< [  3:  3](R/W) Extended stream ID enable.
                                                                 0 = For this SSD, SMMU()_SMR() has the format with the VALID bit in the
                                                                 SMMU()_SMR(). The SMMU()_S2CR()[EXIDVALID] is ignored.
                                                                 1 = For this SSD, SMMU()_SMR() has the extended id format and the valid bit is
                                                                 held in the corresponding SMMU()_S2CR()[EXIDVALID].

                                                                 Software should only change [EXIDENABLE] when all SMMU()_S2CR()[EXIDVALID] == 0
                                                                 and SMMU()_SMR()[EXMASK[15]/VALID] == 0 for the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized before use. */
        uint32_t gcfgfre               : 1;  /**< [  4:  4](RO) Global configuration fault report enable.
                                                                 0 = Do not return an abort on a global configuration fault
                                                                 1 = Return an abort on a global configuration fault.

                                                                 In CNXXXX always zero, as does not support configuration faults. */
        uint32_t gcfgfie               : 1;  /**< [  5:  5](RO) Global configuration fault interrupt enable.
                                                                 0 = Do not raise an interrupt on a global configuration fault.
                                                                 1 = Raise an interrupt on a global configuration fault.

                                                                 In CNXXXX always zero, as does not support configuration faults. */
        uint32_t transientcfg          : 2;  /**< [  7:  6](RO) Transient configuration controls the transient allocation hint.
                                                                 0x0 = Default transient allocation attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Non-transient.
                                                                 0x3 = Transient.

                                                                 Not implemented in CNXXXX. */
        uint32_t stalld                : 1;  /**< [  8:  8](RO) Stall disable.
                                                                 0 = Permit per-context stalling on context faults.
                                                                 1 = Disable per-context stalling on context faults, or not programmable.

                                                                 In CNXXXX always 1, no stalling. */
        uint32_t gse                   : 1;  /**< [  9:  9](RO) Global stall enable.
                                                                 0 = Do not enforce global stalling across contexts.
                                                                 1 = Enforce global stalling across contexts.

                                                                 In CNXXXX always 0, no stalling. */
        uint32_t usfcfg                : 1;  /**< [ 10: 10](R/W) Unidentified stream fault configuration.
                                                                 0 = Permit any transaction that does not match any entries in the stream matching table to
                                                                 pass through.
                                                                 1 = Raise an unidentified stream fault on any transaction that does not match any stream
                                                                 matching table entry. */
        uint32_t vmidpne               : 1;  /**< [ 11: 11](RO) Reserved. */
        uint32_t ptm                   : 1;  /**< [ 12: 12](R/W) Private TLB maintenance hint.
                                                                 0 = Process affected operations as presented.
                                                                 1 = SMMU TLBs are privately managed and are not require to respond to broadcast TLB
                                                                 maintenance operations from the wider system.

                                                                 CNXXXX honors this hint, but both the secure and nonsecure version must be set for
                                                                 private management.

                                                                 Internal:
                                                                 Note when set SMMU always still sends a response for the
                                                                 invalidates, it just does not perform the invalidation action against the TLB/WCU. */
        uint32_t fb                    : 1;  /**< [ 13: 13](R/W) Force broadcast of TLB and instruction cache maintenance operations. Applies to
                                                                 transactions bypassing the stream mapping table. Affects client TLB maintenance, BPIALL
                                                                 and ICIALLU operations. If FB=1, any affected operation is modified to the equivalent
                                                                 broadcast variant in the inner shareable domain.
                                                                 0 = Process affected operations as presented.
                                                                 1 = Upgrade affected operations to be broadcast within the inner sharable domain.

                                                                 Ignored in CNXXXX, as NCB clients do not initiate invalidates. */
        uint32_t bsu                   : 2;  /**< [ 15: 14](RO) Barrier sharability upgrade. Upgrades the sharability of barriers issued by client devices
                                                                 that are not mapped to a translation context bank by setting the minimum sharability
                                                                 domain applied to any barrier.  Applies to transactions bypassing the stream mapping
                                                                 table.
                                                                 0x0 = No effect.
                                                                 0x1 = Inner sharable.
                                                                 0x2 = Outer sharable.
                                                                 0x3 = Full system.

                                                                 Ignored in CNXXXX. */
        uint32_t memattr               : 4;  /**< [ 19: 16](R/W) Memory attributes for bypass transactions if MTCFG == 1. */
        uint32_t mtcfg                 : 1;  /**< [ 20: 20](R/W) Memory type configuration, applies to transactions that bypass the stream mapping table.
                                                                 0 = Use the default memory attributes.
                                                                 1 = Use the MEMATTR field for memory attributes. */
        uint32_t smcfcfg               : 1;  /**< [ 21: 21](RO) Stream match conflict fault configuration. Controls transactions with multiple matches in
                                                                 the stream mapping table.
                                                                 0 = Permit the transaction to bypass the SMMU.
                                                                 1 = Raise a stream match conflict fault.

                                                                 CNXXXX detects all stream match conflicts and always faults. */
        uint32_t shcfg                 : 2;  /**< [ 23: 22](RO) Shared configuration. Applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default shareable attributes.
                                                                 0x1 = Outer sharable.
                                                                 0x2 = Inner sharable.
                                                                 0x3 = Non-sharable.

                                                                 Ignored in CNXXXX. */
        uint32_t racfg                 : 2;  /**< [ 25: 24](RO) Read-allocate configuration, controls the allocation hint for read accesses. This field
                                                                 applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Read-allocate.
                                                                 0x3 = No read-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t wacfg                 : 2;  /**< [ 27: 26](RO) Write-allocate configuration, controls the allocation hint for write accesses. This field
                                                                 applies to transactions that bypass the stream mapping table.
                                                                 0x0 = Default attributes.
                                                                 0x1 = Reserved.
                                                                 0x2 = Write-allocate.
                                                                 0x3 = No write-allocate.

                                                                 Ignored in CNXXXX. */
        uint32_t nscfg                 : 2;  /**< [ 29: 28](SR/W) Nonsecure configuration. Only exist in secure copy of register, RES0 in nonsecure copy.
                                                                 This field only applies to secure transactions bypassing the SMMU stream mapping
                                                                 process.
                                                                 0x0 = Use default NS attribute.
                                                                 0x1 = Reserved.
                                                                 0x2 = Secure.
                                                                 0x3 = Nonsecure. */
        uint32_t hypmode               : 1;  /**< [ 30: 30](R/W) Hypervisor mode. Selects which hypervisor context is used:
                                                                   0 = When SMMU()_CBAR()[CTYPE] = 0x1, SMMU()_CBAR()\<10\> represents HYPC.
                                                                   1 = When SMMU()_CBAR()[CTYPE] = 0x1, SMMU()_CBAR()\<10\> represents E2HC.

                                                                 If this bit is changed, TLB maintenance is required.

                                                                 Only exists in the non secure copy of this register. */
        uint32_t vmid16en              : 1;  /**< [ 31: 31](R/W) Handling of 16-bit VMID extension:
                                                                 0 = 8-bit VMIDs are in use.
                                                                 The VMID is held in SMMU()_CBAR()[VMID].
                                                                 The SMMU()_CBA2R()[VMID16] field is 0.

                                                                 1 = 16-bit VMIDs are in use.
                                                                 The VMID is held in SMMU()_CBA2R()[VMID16].
                                                                 The SMMU()_CBAR()[VMID] field is 0.

                                                                 Only exists in the nonsecure copy of this register.

                                                                 In pass 1, this field must be 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_scr0_s cn; */
};
typedef union bdk_smmux_scr0 bdk_smmux_scr0_t;

static inline uint64_t BDK_SMMUX_SCR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SCR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000000ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000000ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000000ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SCR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SCR0(a) bdk_smmux_scr0_t
#define bustype_BDK_SMMUX_SCR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SCR0(a) "SMMUX_SCR0"
#define device_bar_BDK_SMMUX_SCR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SCR0(a) (a)
#define arguments_BDK_SMMUX_SCR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_scr1
 *
 * SMMU Secure Configuration Register 1
 * Provides top-level secure control of the SMMU.
 */
union bdk_smmux_scr1
{
    uint32_t u;
    struct bdk_smmux_scr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t nshypmodedisable      : 1;  /**< [ 30: 30](SR/W) Reserved. */
        uint32_t nscompindexdisable    : 1;  /**< [ 29: 29](SRO) Nonsecure compressed index disable.
                                                                 In CNXXXX stream compressed indexing is not implemented. */
        uint32_t nscafro               : 1;  /**< [ 28: 28](SRO) Nonsecure configuration access fault report override.
                                                                 0 = Permit SMMU_SGFSR to report configuration access faults caused by nonsecure accesses
                                                                 to secure-only registers.
                                                                 1 = SMMU_GFSR reports all such faults.

                                                                 In CNXXXX always zero, as does not support generation of configuration faults. */
        uint32_t spmen                 : 1;  /**< [ 27: 27](SR/W) Secure performance monitor enable.
                                                                 0 = Any event caused by secure transaction processing does not contribute towards
                                                                 performance monitor counting.
                                                                 1 = Any event caused by secure transaction processing is permitted to contribute towards
                                                                 performance monitor counting.

                                                                 Ignored in CNXXXX, no ARM architected performance monitoring, counters are separate
                                                                 between secure and nonsecure. */
        uint32_t sif                   : 1;  /**< [ 26: 26](SR/W) Secure instruction fetch.
                                                                 0 = Secure instruction fetches are permitted to nonsecure memory locations.
                                                                 1 = Raise a permission fault if a secure domain instruction fetch accesses a nonsecure
                                                                 memory location.

                                                                 Ignored in CNXXXX, no instruction fetches from IO devices. */
        uint32_t gefro                 : 1;  /**< [ 25: 25](SR/W) Global external fault report override.

                                                                 0 = Permit SMMU_GFSR to report external faults.
                                                                 1 = SMMU_SGFSR reports all external faults.

                                                                 If SMMU()_SCR1[GEFRO]==1, all external aborts that would have been recorded in
                                                                 SMMU_GFSR are instead recorded in SMMU_SGFSR. */
        uint32_t gasrae                : 1;  /**< [ 24: 24](SR/W) Global address space restricted access enable.
                                                                 0 = Global address space is accessible using either secure or nonsecure configuration
                                                                 memory accesses.
                                                                 1 = Global address space is only accessible by secure configuration memory accesses. Stage
                                                                 2 format context banks (as determined by SMMU()_CBAR()[CTYPE]) are only
                                                                 accessible by secure configuration accesses.

                                                                 The following additional constraints apply:

                                                                 If 0, secure software must avoid setting SMMU()_CBAR()[HYPC] to 1 when
                                                                 configuring a secure stage 1 translation context bank.

                                                                 If 1, secure software must avoid setting SMMU()_CBAR()[HYPC] to 1 when
                                                                 configuring a nonsecure stage 1 translation context bank.

                                                                 In CNXXXX, implementation defined register accesses are also controlled by this bit. */
        uint32_t nsnumirpto            : 8;  /**< [ 23: 16](SRO) Nonsecure number of interrupts override. Always 1 in ARMv8. */
        uint32_t nsnumsmrgo            : 8;  /**< [ 15:  8](SR/W) Adjusts the number of stream mapping register groups visible to nonsecure accesses. The
                                                                 number of stream mapping register groups reported in SMMU()_IDR0 is reduced to the
                                                                 number indicated by NSNUMSMRGO.

                                                                 In CNXXXX if the value in NSNUMSMRGO exceeds the number of implemented stream match
                                                                 register groups then nonsecure software might attempt to access an unimplemented stream
                                                                 match register group and such access are ignored.

                                                                 In CNXXXX, software should only change [NSNUMSMRGO]/[NSNUMCBO] when
                                                                 SMMU()_S2CR()[EXIDVALID] == 0 and SMMU()_SMR()[EXMASK[15]/VALID] == 0
                                                                 for at minimum any contexts being moved into/out of the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized before use.

                                                                 These bits reset to the implemented number of stream mapping register groups. */
        uint32_t nsnumcbo              : 8;  /**< [  7:  0](SR/W) Nonsecure number of context banks override. adjusts the number of translation context
                                                                 banks visible to nonsecure accesses. The number of translation context banks reported in
                                                                 SMMU()_IDR1[NUMCB] is reduced to the number indicated by SMMU()_SCR1[NSNUMCBO].

                                                                 In CNXXXX, software should only change [NSNUMSMRGO]/[NSNUMCBO] when
                                                                 SMMU()_S2CR()[EXIDVALID] == 0 and SMMU()_SMR()[EXMASK[15]/VALID] == 0
                                                                 for at minimum any contexts being moved into/out of the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized first. */
#else /* Word 0 - Little Endian */
        uint32_t nsnumcbo              : 8;  /**< [  7:  0](SR/W) Nonsecure number of context banks override. adjusts the number of translation context
                                                                 banks visible to nonsecure accesses. The number of translation context banks reported in
                                                                 SMMU()_IDR1[NUMCB] is reduced to the number indicated by SMMU()_SCR1[NSNUMCBO].

                                                                 In CNXXXX, software should only change [NSNUMSMRGO]/[NSNUMCBO] when
                                                                 SMMU()_S2CR()[EXIDVALID] == 0 and SMMU()_SMR()[EXMASK[15]/VALID] == 0
                                                                 for at minimum any contexts being moved into/out of the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized first. */
        uint32_t nsnumsmrgo            : 8;  /**< [ 15:  8](SR/W) Adjusts the number of stream mapping register groups visible to nonsecure accesses. The
                                                                 number of stream mapping register groups reported in SMMU()_IDR0 is reduced to the
                                                                 number indicated by NSNUMSMRGO.

                                                                 In CNXXXX if the value in NSNUMSMRGO exceeds the number of implemented stream match
                                                                 register groups then nonsecure software might attempt to access an unimplemented stream
                                                                 match register group and such access are ignored.

                                                                 In CNXXXX, software should only change [NSNUMSMRGO]/[NSNUMCBO] when
                                                                 SMMU()_S2CR()[EXIDVALID] == 0 and SMMU()_SMR()[EXMASK[15]/VALID] == 0
                                                                 for at minimum any contexts being moved into/out of the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized before use.

                                                                 These bits reset to the implemented number of stream mapping register groups. */
        uint32_t nsnumirpto            : 8;  /**< [ 23: 16](SRO) Nonsecure number of interrupts override. Always 1 in ARMv8. */
        uint32_t gasrae                : 1;  /**< [ 24: 24](SR/W) Global address space restricted access enable.
                                                                 0 = Global address space is accessible using either secure or nonsecure configuration
                                                                 memory accesses.
                                                                 1 = Global address space is only accessible by secure configuration memory accesses. Stage
                                                                 2 format context banks (as determined by SMMU()_CBAR()[CTYPE]) are only
                                                                 accessible by secure configuration accesses.

                                                                 The following additional constraints apply:

                                                                 If 0, secure software must avoid setting SMMU()_CBAR()[HYPC] to 1 when
                                                                 configuring a secure stage 1 translation context bank.

                                                                 If 1, secure software must avoid setting SMMU()_CBAR()[HYPC] to 1 when
                                                                 configuring a nonsecure stage 1 translation context bank.

                                                                 In CNXXXX, implementation defined register accesses are also controlled by this bit. */
        uint32_t gefro                 : 1;  /**< [ 25: 25](SR/W) Global external fault report override.

                                                                 0 = Permit SMMU_GFSR to report external faults.
                                                                 1 = SMMU_SGFSR reports all external faults.

                                                                 If SMMU()_SCR1[GEFRO]==1, all external aborts that would have been recorded in
                                                                 SMMU_GFSR are instead recorded in SMMU_SGFSR. */
        uint32_t sif                   : 1;  /**< [ 26: 26](SR/W) Secure instruction fetch.
                                                                 0 = Secure instruction fetches are permitted to nonsecure memory locations.
                                                                 1 = Raise a permission fault if a secure domain instruction fetch accesses a nonsecure
                                                                 memory location.

                                                                 Ignored in CNXXXX, no instruction fetches from IO devices. */
        uint32_t spmen                 : 1;  /**< [ 27: 27](SR/W) Secure performance monitor enable.
                                                                 0 = Any event caused by secure transaction processing does not contribute towards
                                                                 performance monitor counting.
                                                                 1 = Any event caused by secure transaction processing is permitted to contribute towards
                                                                 performance monitor counting.

                                                                 Ignored in CNXXXX, no ARM architected performance monitoring, counters are separate
                                                                 between secure and nonsecure. */
        uint32_t nscafro               : 1;  /**< [ 28: 28](SRO) Nonsecure configuration access fault report override.
                                                                 0 = Permit SMMU_SGFSR to report configuration access faults caused by nonsecure accesses
                                                                 to secure-only registers.
                                                                 1 = SMMU_GFSR reports all such faults.

                                                                 In CNXXXX always zero, as does not support generation of configuration faults. */
        uint32_t nscompindexdisable    : 1;  /**< [ 29: 29](SRO) Nonsecure compressed index disable.
                                                                 In CNXXXX stream compressed indexing is not implemented. */
        uint32_t nshypmodedisable      : 1;  /**< [ 30: 30](SR/W) Reserved. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_scr1_s cn88xxp1; */
    struct bdk_smmux_scr1_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t reserved_30           : 1;
        uint32_t nscompindexdisable    : 1;  /**< [ 29: 29](SRO) Nonsecure compressed index disable.
                                                                 In CNXXXX stream compressed indexing is not implemented. */
        uint32_t nscafro               : 1;  /**< [ 28: 28](SRO) Nonsecure configuration access fault report override.
                                                                 0 = Permit SMMU_SGFSR to report configuration access faults caused by nonsecure accesses
                                                                 to secure-only registers.
                                                                 1 = SMMU_GFSR reports all such faults.

                                                                 In CNXXXX always zero, as does not support generation of configuration faults. */
        uint32_t spmen                 : 1;  /**< [ 27: 27](SR/W) Secure performance monitor enable.
                                                                 0 = Any event caused by secure transaction processing does not contribute towards
                                                                 performance monitor counting.
                                                                 1 = Any event caused by secure transaction processing is permitted to contribute towards
                                                                 performance monitor counting.

                                                                 Ignored in CNXXXX, no ARM architected performance monitoring, counters are separate
                                                                 between secure and nonsecure. */
        uint32_t sif                   : 1;  /**< [ 26: 26](SR/W) Secure instruction fetch.
                                                                 0 = Secure instruction fetches are permitted to nonsecure memory locations.
                                                                 1 = Raise a permission fault if a secure domain instruction fetch accesses a nonsecure
                                                                 memory location.

                                                                 Ignored in CNXXXX, no instruction fetches from IO devices. */
        uint32_t gefro                 : 1;  /**< [ 25: 25](SR/W) Global external fault report override.

                                                                 0 = Permit SMMU_GFSR to report external faults.
                                                                 1 = SMMU_SGFSR reports all external faults.

                                                                 If SMMU()_SCR1[GEFRO]==1, all external aborts that would have been recorded in
                                                                 SMMU_GFSR are instead recorded in SMMU_SGFSR. */
        uint32_t gasrae                : 1;  /**< [ 24: 24](SR/W) Global address space restricted access enable.
                                                                 0 = Global address space is accessible using either secure or nonsecure configuration
                                                                 memory accesses.
                                                                 1 = Global address space is only accessible by secure configuration memory accesses. Stage
                                                                 2 format context banks (as determined by SMMU()_CBAR()[CTYPE]) are only
                                                                 accessible by secure configuration accesses.

                                                                 The following additional constraints apply:

                                                                 If 0, secure software must avoid setting SMMU()_CBAR()[HYPC] to 1 when
                                                                 configuring a secure stage 1 translation context bank.

                                                                 If 1, secure software must avoid setting SMMU()_CBAR()[HYPC] to 1 when
                                                                 configuring a nonsecure stage 1 translation context bank.

                                                                 In CNXXXX, implementation defined register accesses are also controlled by this bit. */
        uint32_t nsnumirpto            : 8;  /**< [ 23: 16](SRO) Nonsecure number of interrupts override. Always 1 in ARMv8. */
        uint32_t nsnumsmrgo            : 8;  /**< [ 15:  8](SR/W) Adjusts the number of stream mapping register groups visible to nonsecure accesses. The
                                                                 number of stream mapping register groups reported in SMMU()_IDR0 is reduced to the
                                                                 number indicated by NSNUMSMRGO.

                                                                 In CNXXXX if the value in NSNUMSMRGO exceeds the number of implemented stream match
                                                                 register groups then nonsecure software might attempt to access an unimplemented stream
                                                                 match register group and such access are ignored.

                                                                 In CNXXXX, software should only change [NSNUMSMRGO]/[NSNUMCBO] when
                                                                 SMMU()_S2CR()[EXIDVALID] == 0 and SMMU()_SMR()[EXMASK[15]/VALID] == 0
                                                                 for at minimum any contexts being moved into/out of the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized before use.

                                                                 These bits reset to the implemented number of stream mapping register groups. */
        uint32_t nsnumcbo              : 8;  /**< [  7:  0](SR/W) Nonsecure number of context banks override. adjusts the number of translation context
                                                                 banks visible to nonsecure accesses. The number of translation context banks reported in
                                                                 SMMU()_IDR1[NUMCB] is reduced to the number indicated by SMMU()_SCR1[NSNUMCBO].

                                                                 In CNXXXX, software should only change [NSNUMSMRGO]/[NSNUMCBO] when
                                                                 SMMU()_S2CR()[EXIDVALID] == 0 and SMMU()_SMR()[EXMASK[15]/VALID] == 0
                                                                 for at minimum any contexts being moved into/out of the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized first. */
#else /* Word 0 - Little Endian */
        uint32_t nsnumcbo              : 8;  /**< [  7:  0](SR/W) Nonsecure number of context banks override. adjusts the number of translation context
                                                                 banks visible to nonsecure accesses. The number of translation context banks reported in
                                                                 SMMU()_IDR1[NUMCB] is reduced to the number indicated by SMMU()_SCR1[NSNUMCBO].

                                                                 In CNXXXX, software should only change [NSNUMSMRGO]/[NSNUMCBO] when
                                                                 SMMU()_S2CR()[EXIDVALID] == 0 and SMMU()_SMR()[EXMASK[15]/VALID] == 0
                                                                 for at minimum any contexts being moved into/out of the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized first. */
        uint32_t nsnumsmrgo            : 8;  /**< [ 15:  8](SR/W) Adjusts the number of stream mapping register groups visible to nonsecure accesses. The
                                                                 number of stream mapping register groups reported in SMMU()_IDR0 is reduced to the
                                                                 number indicated by NSNUMSMRGO.

                                                                 In CNXXXX if the value in NSNUMSMRGO exceeds the number of implemented stream match
                                                                 register groups then nonsecure software might attempt to access an unimplemented stream
                                                                 match register group and such access are ignored.

                                                                 In CNXXXX, software should only change [NSNUMSMRGO]/[NSNUMCBO] when
                                                                 SMMU()_S2CR()[EXIDVALID] == 0 and SMMU()_SMR()[EXMASK[15]/VALID] == 0
                                                                 for at minimum any contexts being moved into/out of the appropriate security world,
                                                                 otherwise the effect is unpredictable. In particular, note that the reset values of
                                                                 SMMU()_S2CR() and SMMU()_SMR() are unknown and so need to be
                                                                 initialized before use.

                                                                 These bits reset to the implemented number of stream mapping register groups. */
        uint32_t nsnumirpto            : 8;  /**< [ 23: 16](SRO) Nonsecure number of interrupts override. Always 1 in ARMv8. */
        uint32_t gasrae                : 1;  /**< [ 24: 24](SR/W) Global address space restricted access enable.
                                                                 0 = Global address space is accessible using either secure or nonsecure configuration
                                                                 memory accesses.
                                                                 1 = Global address space is only accessible by secure configuration memory accesses. Stage
                                                                 2 format context banks (as determined by SMMU()_CBAR()[CTYPE]) are only
                                                                 accessible by secure configuration accesses.

                                                                 The following additional constraints apply:

                                                                 If 0, secure software must avoid setting SMMU()_CBAR()[HYPC] to 1 when
                                                                 configuring a secure stage 1 translation context bank.

                                                                 If 1, secure software must avoid setting SMMU()_CBAR()[HYPC] to 1 when
                                                                 configuring a nonsecure stage 1 translation context bank.

                                                                 In CNXXXX, implementation defined register accesses are also controlled by this bit. */
        uint32_t gefro                 : 1;  /**< [ 25: 25](SR/W) Global external fault report override.

                                                                 0 = Permit SMMU_GFSR to report external faults.
                                                                 1 = SMMU_SGFSR reports all external faults.

                                                                 If SMMU()_SCR1[GEFRO]==1, all external aborts that would have been recorded in
                                                                 SMMU_GFSR are instead recorded in SMMU_SGFSR. */
        uint32_t sif                   : 1;  /**< [ 26: 26](SR/W) Secure instruction fetch.
                                                                 0 = Secure instruction fetches are permitted to nonsecure memory locations.
                                                                 1 = Raise a permission fault if a secure domain instruction fetch accesses a nonsecure
                                                                 memory location.

                                                                 Ignored in CNXXXX, no instruction fetches from IO devices. */
        uint32_t spmen                 : 1;  /**< [ 27: 27](SR/W) Secure performance monitor enable.
                                                                 0 = Any event caused by secure transaction processing does not contribute towards
                                                                 performance monitor counting.
                                                                 1 = Any event caused by secure transaction processing is permitted to contribute towards
                                                                 performance monitor counting.

                                                                 Ignored in CNXXXX, no ARM architected performance monitoring, counters are separate
                                                                 between secure and nonsecure. */
        uint32_t nscafro               : 1;  /**< [ 28: 28](SRO) Nonsecure configuration access fault report override.
                                                                 0 = Permit SMMU_SGFSR to report configuration access faults caused by nonsecure accesses
                                                                 to secure-only registers.
                                                                 1 = SMMU_GFSR reports all such faults.

                                                                 In CNXXXX always zero, as does not support generation of configuration faults. */
        uint32_t nscompindexdisable    : 1;  /**< [ 29: 29](SRO) Nonsecure compressed index disable.
                                                                 In CNXXXX stream compressed indexing is not implemented. */
        uint32_t reserved_30           : 1;
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_smmux_scr1_cn81xx cn83xx; */
    /* struct bdk_smmux_scr1_cn81xx cn88xxp2; */
};
typedef union bdk_smmux_scr1 bdk_smmux_scr1_t;

static inline uint64_t BDK_SMMUX_SCR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SCR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000004ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000004ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000004ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SCR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SCR1(a) bdk_smmux_scr1_t
#define bustype_BDK_SMMUX_SCR1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SCR1(a) "SMMUX_SCR1"
#define device_bar_BDK_SMMUX_SCR1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SCR1(a) (a)
#define arguments_BDK_SMMUX_SCR1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_scr2
 *
 * SMMU (Secure) Control Register 2
 * Not implemented in CNXXXX.
 */
union bdk_smmux_scr2
{
    uint32_t u;
    struct bdk_smmux_scr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t exsmrgenable          : 1;  /**< [ 31: 31](RO) Enables extended stream matching extension.
                                                                 In CNXXXX, extended stream matching is not implemented. */
        uint32_t exnssmrgdisable       : 1;  /**< [ 30: 30](SRO) Disables use of extended stream match register groups by nonsecure software.
                                                                 Only exists in the secure copy of this register.

                                                                 In CNXXXX, extended stream matching is not implemented. */
        uint32_t compindexenable       : 1;  /**< [ 29: 29](RO) StreamID compressed index match enable.

                                                                 In CNXXXX, StreamID compressed indexing is not implemented. */
        uint32_t reserved_16_28        : 13;
        uint32_t bpvmid                : 16; /**< [ 15:  0](RAZ) Bypass VMID. VMID field applied to client transactions that bypass the SMMU. In CNXXXX,
                                                                 not supported.

                                                                 Internal:
                                                                 If L2C adds support for QoS on a per VMID basis the L2C will also
                                                                 have a `secure' QoS setting, so this field should remain not required. */
#else /* Word 0 - Little Endian */
        uint32_t bpvmid                : 16; /**< [ 15:  0](RAZ) Bypass VMID. VMID field applied to client transactions that bypass the SMMU. In CNXXXX,
                                                                 not supported.

                                                                 Internal:
                                                                 If L2C adds support for QoS on a per VMID basis the L2C will also
                                                                 have a `secure' QoS setting, so this field should remain not required. */
        uint32_t reserved_16_28        : 13;
        uint32_t compindexenable       : 1;  /**< [ 29: 29](RO) StreamID compressed index match enable.

                                                                 In CNXXXX, StreamID compressed indexing is not implemented. */
        uint32_t exnssmrgdisable       : 1;  /**< [ 30: 30](SRO) Disables use of extended stream match register groups by nonsecure software.
                                                                 Only exists in the secure copy of this register.

                                                                 In CNXXXX, extended stream matching is not implemented. */
        uint32_t exsmrgenable          : 1;  /**< [ 31: 31](RO) Enables extended stream matching extension.
                                                                 In CNXXXX, extended stream matching is not implemented. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_scr2_s cn; */
};
typedef union bdk_smmux_scr2 bdk_smmux_scr2_t;

static inline uint64_t BDK_SMMUX_SCR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SCR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000008ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000008ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000008ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SCR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SCR2(a) bdk_smmux_scr2_t
#define bustype_BDK_SMMUX_SCR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SCR2(a) "SMMUX_SCR2"
#define device_bar_BDK_SMMUX_SCR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SCR2(a) (a)
#define arguments_BDK_SMMUX_SCR2(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_sgfar
 *
 * SMMU (Secure) Global Fault Address Register
 * Contains the input address of an erroneous request reported by SMMU()_(S)GFSR.
 */
union bdk_smmux_sgfar
{
    uint64_t u;
    struct bdk_smmux_sgfar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t faddr                 : 49; /**< [ 48:  0](R/W/H) Fault address, the input IOVA of the faulty access. For configuration access faults,
                                                                 this is the physical address resulting in the fault. For other fault classes it is the
                                                                 input address of the faulting access, which the system can interpret in a number of ways.
                                                                 This register is updated before a valid context has been determined. Hence, no sign
                                                                 extension can have been performed.

                                                                 For CNXXXX \<11:0\> are always zero. */
#else /* Word 0 - Little Endian */
        uint64_t faddr                 : 49; /**< [ 48:  0](R/W/H) Fault address, the input IOVA of the faulty access. For configuration access faults,
                                                                 this is the physical address resulting in the fault. For other fault classes it is the
                                                                 input address of the faulting access, which the system can interpret in a number of ways.
                                                                 This register is updated before a valid context has been determined. Hence, no sign
                                                                 extension can have been performed.

                                                                 For CNXXXX \<11:0\> are always zero. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_sgfar_s cn; */
};
typedef union bdk_smmux_sgfar bdk_smmux_sgfar_t;

static inline uint64_t BDK_SMMUX_SGFAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SGFAR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000040ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000040ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000040ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SGFAR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SGFAR(a) bdk_smmux_sgfar_t
#define bustype_BDK_SMMUX_SGFAR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_SGFAR(a) "SMMUX_SGFAR"
#define device_bar_BDK_SMMUX_SGFAR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SGFAR(a) (a)
#define arguments_BDK_SMMUX_SGFAR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_sgfsr
 *
 * SMMU (Secure) Global Fault Status Register
 */
union bdk_smmux_sgfsr
{
    uint32_t u;
    struct bdk_smmux_sgfsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t multi                 : 1;  /**< [ 31: 31](R/W1C/H) Multiple error conditions.
                                                                 0 = No multiple error condition was encountered.
                                                                 1 = An error occurred while the value in this register was nonzero. */
        uint32_t reserved_9_30         : 22;
        uint32_t uut                   : 1;  /**< [  8:  8](R/W1C/H) Unsupported upstream transaction.
                                                                 0 = No unsupported upstream transaction fault.
                                                                 1 = Unsupported upstream transaction fault caused by receipt of an unsupported client
                                                                 transaction from an upstream device. */
        uint32_t pf                    : 1;  /**< [  7:  7](R/W1C/H) Permission fault. In SMMU_GFSR, this field is reserved. In SMMU_SGFSR, this field records
                                                                 global SMMU()_SCR1[SIF] faults.
                                                                 Note if a transaction is associated with a particular translation context bank, faults are
                                                                 recorded in SMMU()_CB()_FSR instead of SMMU_SGFSR. */
        uint32_t ef                    : 1;  /**< [  6:  6](R/W1C/H) External fault. */
        uint32_t caf                   : 1;  /**< [  5:  5](RO) Configuration access fault.
                                                                 For CNXXXX always zero, no configuration faults. */
        uint32_t ucif                  : 1;  /**< [  4:  4](R/W1C/H) Unimplemented context interrupt fault. */
        uint32_t ucbf                  : 1;  /**< [  3:  3](R/W1C/H) Unimplemented context bank fault. */
        uint32_t smcf                  : 1;  /**< [  2:  2](R/W1C/H) Stream match conflict fault. */
        uint32_t usf                   : 1;  /**< [  1:  1](R/W1C/H) Unidentified stream fault. */
        uint32_t icf                   : 1;  /**< [  0:  0](R/W1C/H) Invalid context fault. */
#else /* Word 0 - Little Endian */
        uint32_t icf                   : 1;  /**< [  0:  0](R/W1C/H) Invalid context fault. */
        uint32_t usf                   : 1;  /**< [  1:  1](R/W1C/H) Unidentified stream fault. */
        uint32_t smcf                  : 1;  /**< [  2:  2](R/W1C/H) Stream match conflict fault. */
        uint32_t ucbf                  : 1;  /**< [  3:  3](R/W1C/H) Unimplemented context bank fault. */
        uint32_t ucif                  : 1;  /**< [  4:  4](R/W1C/H) Unimplemented context interrupt fault. */
        uint32_t caf                   : 1;  /**< [  5:  5](RO) Configuration access fault.
                                                                 For CNXXXX always zero, no configuration faults. */
        uint32_t ef                    : 1;  /**< [  6:  6](R/W1C/H) External fault. */
        uint32_t pf                    : 1;  /**< [  7:  7](R/W1C/H) Permission fault. In SMMU_GFSR, this field is reserved. In SMMU_SGFSR, this field records
                                                                 global SMMU()_SCR1[SIF] faults.
                                                                 Note if a transaction is associated with a particular translation context bank, faults are
                                                                 recorded in SMMU()_CB()_FSR instead of SMMU_SGFSR. */
        uint32_t uut                   : 1;  /**< [  8:  8](R/W1C/H) Unsupported upstream transaction.
                                                                 0 = No unsupported upstream transaction fault.
                                                                 1 = Unsupported upstream transaction fault caused by receipt of an unsupported client
                                                                 transaction from an upstream device. */
        uint32_t reserved_9_30         : 22;
        uint32_t multi                 : 1;  /**< [ 31: 31](R/W1C/H) Multiple error conditions.
                                                                 0 = No multiple error condition was encountered.
                                                                 1 = An error occurred while the value in this register was nonzero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_sgfsr_s cn; */
};
typedef union bdk_smmux_sgfsr bdk_smmux_sgfsr_t;

static inline uint64_t BDK_SMMUX_SGFSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SGFSR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000048ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000048ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000048ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SGFSR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SGFSR(a) bdk_smmux_sgfsr_t
#define bustype_BDK_SMMUX_SGFSR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SGFSR(a) "SMMUX_SGFSR"
#define device_bar_BDK_SMMUX_SGFSR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SGFSR(a) (a)
#define arguments_BDK_SMMUX_SGFSR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_sgfsrrestore
 *
 * SMMU (Secure) Global Fault Status Restore Register
 * Restores the SMMU()_(S)GFSR register after reset.
 */
union bdk_smmux_sgfsrrestore
{
    uint32_t u;
    struct bdk_smmux_sgfsrrestore_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t restore               : 32; /**< [ 31:  0](WO) Writes bits in corresponding SMMU()_(S)GFSR. */
#else /* Word 0 - Little Endian */
        uint32_t restore               : 32; /**< [ 31:  0](WO) Writes bits in corresponding SMMU()_(S)GFSR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_sgfsrrestore_s cn; */
};
typedef union bdk_smmux_sgfsrrestore bdk_smmux_sgfsrrestore_t;

static inline uint64_t BDK_SMMUX_SGFSRRESTORE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SGFSRRESTORE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x83000000004cll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x83000000004cll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x83000000004cll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SGFSRRESTORE", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SGFSRRESTORE(a) bdk_smmux_sgfsrrestore_t
#define bustype_BDK_SMMUX_SGFSRRESTORE(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SGFSRRESTORE(a) "SMMUX_SGFSRRESTORE"
#define device_bar_BDK_SMMUX_SGFSRRESTORE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SGFSRRESTORE(a) (a)
#define arguments_BDK_SMMUX_SGFSRRESTORE(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_sgfsynr0
 *
 * SMMU (Secure) Global Fault Syndrome Register 0
 * Contains fault syndrome information relating to SMMU()_(S)GFSR.
 */
union bdk_smmux_sgfsynr0
{
    uint32_t u;
    struct bdk_smmux_sgfsynr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t imp                   : 8;  /**< [ 15:  8](RO) Reserved for implementation. */
        uint32_t reserved_7            : 1;
        uint32_t ats                   : 1;  /**< [  6:  6](RO) Address translation operation fault. For CNXXXX zero, SMMU()_IDR0[ATOSNS] not supported. */
        uint32_t nsattr                : 1;  /**< [  5:  5](R/W/H) Nonsecure attribute.
                                                                 0 = The faulty transaction has the secure attribute.
                                                                 1 = The faulty transaction has the nonsecure attribute. */
        uint32_t nsstate               : 1;  /**< [  4:  4](SR/W/H) Nonsecure state.
                                                                 0 = The faulty transaction is associated with a secure device.
                                                                 1 = The faulty transaction is associated with a nonsecure device.

                                                                 This field is only valid for the secure state.

                                                                 This field may read 1 in the event that a fault is encountered in relation to a
                                                                 nonsecure client device and where SMMU()_SCR1[GEFRO]=1. */
        uint32_t ind                   : 1;  /**< [  3:  3](R/W/H) Instruction not data.
                                                                 0 = The faulty transaction has the data access attribute.
                                                                 1 = The faulty transaction has the instruction access attribute. */
        uint32_t pnu                   : 1;  /**< [  2:  2](R/W/H) Privileged not unprivileged.
                                                                 0 = The faulty transaction has the unprivileged attribute.
                                                                 1 = The faulty transaction has the privileged attribute. */
        uint32_t wnr                   : 1;  /**< [  1:  1](R/W/H) Write not read.
                                                                 0 = The faulty transaction is a read.
                                                                 1 = The faulty transaction is a write. */
        uint32_t nested                : 1;  /**< [  0:  0](R/W/H) Nested fault.
                                                                 0 = The fault occurred in the initial stream context.
                                                                 1 = The fault occurred in a nested context.

                                                                 This bit is reserved in SMMU_SGFSYNR0. */
#else /* Word 0 - Little Endian */
        uint32_t nested                : 1;  /**< [  0:  0](R/W/H) Nested fault.
                                                                 0 = The fault occurred in the initial stream context.
                                                                 1 = The fault occurred in a nested context.

                                                                 This bit is reserved in SMMU_SGFSYNR0. */
        uint32_t wnr                   : 1;  /**< [  1:  1](R/W/H) Write not read.
                                                                 0 = The faulty transaction is a read.
                                                                 1 = The faulty transaction is a write. */
        uint32_t pnu                   : 1;  /**< [  2:  2](R/W/H) Privileged not unprivileged.
                                                                 0 = The faulty transaction has the unprivileged attribute.
                                                                 1 = The faulty transaction has the privileged attribute. */
        uint32_t ind                   : 1;  /**< [  3:  3](R/W/H) Instruction not data.
                                                                 0 = The faulty transaction has the data access attribute.
                                                                 1 = The faulty transaction has the instruction access attribute. */
        uint32_t nsstate               : 1;  /**< [  4:  4](SR/W/H) Nonsecure state.
                                                                 0 = The faulty transaction is associated with a secure device.
                                                                 1 = The faulty transaction is associated with a nonsecure device.

                                                                 This field is only valid for the secure state.

                                                                 This field may read 1 in the event that a fault is encountered in relation to a
                                                                 nonsecure client device and where SMMU()_SCR1[GEFRO]=1. */
        uint32_t nsattr                : 1;  /**< [  5:  5](R/W/H) Nonsecure attribute.
                                                                 0 = The faulty transaction has the secure attribute.
                                                                 1 = The faulty transaction has the nonsecure attribute. */
        uint32_t ats                   : 1;  /**< [  6:  6](RO) Address translation operation fault. For CNXXXX zero, SMMU()_IDR0[ATOSNS] not supported. */
        uint32_t reserved_7            : 1;
        uint32_t imp                   : 8;  /**< [ 15:  8](RO) Reserved for implementation. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_sgfsynr0_s cn; */
};
typedef union bdk_smmux_sgfsynr0 bdk_smmux_sgfsynr0_t;

static inline uint64_t BDK_SMMUX_SGFSYNR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SGFSYNR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000050ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000050ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000050ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SGFSYNR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SGFSYNR0(a) bdk_smmux_sgfsynr0_t
#define bustype_BDK_SMMUX_SGFSYNR0(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SGFSYNR0(a) "SMMUX_SGFSYNR0"
#define device_bar_BDK_SMMUX_SGFSYNR0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SGFSYNR0(a) (a)
#define arguments_BDK_SMMUX_SGFSYNR0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_sgfsynr1
 *
 * SMMU (Secure) Global Fault Syndrome Register 1
 * Contains fault syndrome information relating to SMMU()_(S)GFSR.
 */
union bdk_smmux_sgfsynr1
{
    uint32_t u;
    struct bdk_smmux_sgfsynr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ssd_index             : 16; /**< [ 31: 16](SRO/H) The SSD index of the transaction that caused the fault. [SSD_INDEX] is only
                                                                 accessible to configuration accesses by secure software. Nonsecure configuration
                                                                 accesses treat this field as RAZ/WI.

                                                                 For CNXXXX, [SSD_INDEX] is always the same as [STREAMID]. */
        uint32_t streamid              : 16; /**< [ 15:  0](R/W/H) The stream ID of the transaction that caused the fault. */
#else /* Word 0 - Little Endian */
        uint32_t streamid              : 16; /**< [ 15:  0](R/W/H) The stream ID of the transaction that caused the fault. */
        uint32_t ssd_index             : 16; /**< [ 31: 16](SRO/H) The SSD index of the transaction that caused the fault. [SSD_INDEX] is only
                                                                 accessible to configuration accesses by secure software. Nonsecure configuration
                                                                 accesses treat this field as RAZ/WI.

                                                                 For CNXXXX, [SSD_INDEX] is always the same as [STREAMID]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_sgfsynr1_s cn; */
};
typedef union bdk_smmux_sgfsynr1 bdk_smmux_sgfsynr1_t;

static inline uint64_t BDK_SMMUX_SGFSYNR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SGFSYNR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000054ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000054ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000054ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SGFSYNR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SGFSYNR1(a) bdk_smmux_sgfsynr1_t
#define bustype_BDK_SMMUX_SGFSYNR1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SGFSYNR1(a) "SMMUX_SGFSYNR1"
#define device_bar_BDK_SMMUX_SGFSYNR1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SGFSYNR1(a) (a)
#define arguments_BDK_SMMUX_SGFSYNR1(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_sgfsynr2
 *
 * SMMU (Secure) Global Fault Syndrome Register 2
 * Not implemented in CNXXXX.
 */
union bdk_smmux_sgfsynr2
{
    uint32_t u;
    struct bdk_smmux_sgfsynr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_sgfsynr2_s cn; */
};
typedef union bdk_smmux_sgfsynr2 bdk_smmux_sgfsynr2_t;

static inline uint64_t BDK_SMMUX_SGFSYNR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SGFSYNR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000058ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000058ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000058ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SGFSYNR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SGFSYNR2(a) bdk_smmux_sgfsynr2_t
#define bustype_BDK_SMMUX_SGFSYNR2(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SGFSYNR2(a) "SMMUX_SGFSYNR2"
#define device_bar_BDK_SMMUX_SGFSYNR2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SGFSYNR2(a) (a)
#define arguments_BDK_SMMUX_SGFSYNR2(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_smiss_perf
 *
 * SMMU Secure Misses Performance Counter Register
 */
union bdk_smmux_smiss_perf
{
    uint64_t u;
    struct bdk_smmux_smiss_perf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](SR/W/H) Counts the number of lookup requests in secure mode which missed the IOTLB.
                                                                 Also includes sign-extension position translation faults. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](SR/W/H) Counts the number of lookup requests in secure mode which missed the IOTLB.
                                                                 Also includes sign-extension position translation faults. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_smiss_perf_s cn; */
};
typedef union bdk_smmux_smiss_perf bdk_smmux_smiss_perf_t;

static inline uint64_t BDK_SMMUX_SMISS_PERF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SMISS_PERF(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000021040ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000021040ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000021040ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SMISS_PERF", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SMISS_PERF(a) bdk_smmux_smiss_perf_t
#define bustype_BDK_SMMUX_SMISS_PERF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_SMISS_PERF(a) "SMMUX_SMISS_PERF"
#define device_bar_BDK_SMMUX_SMISS_PERF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SMISS_PERF(a) (a)
#define arguments_BDK_SMMUX_SMISS_PERF(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_smr#
 *
 * SMMU Stream Match Register
 * Match a transaction with a particular stream mapping register group. The stream match register
 * table can have multiple entries matching the same stream id value during configuration,
 * providing software has the necessary precautions before configuration takes effect. For
 * example: 1. disable the stream source and ensure that no outstanding transactions from that
 * source are in progress disable one or more of the SMMU()_SMR() table entries using
 * the corresponding SMMU()_SMR()[VALID] bit, 2. disable the SMMU completely with
 * SMMU()_CB()_SCTLR[M].
 */
union bdk_smmux_smrx
{
    uint32_t u;
    struct bdk_smmux_smrx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t exmask_valid          : 16; /**< [ 31: 16](R/W) Masking of stream id bits irrelevent to the matching process.

                                                                 If MASK\<i\>==1, ID\<i\> is ignored.

                                                                 If MASK\<i\>==0, ID\<i\> is relevant for matching.

                                                                 Note \<31\> indicates VALID if SMMU()_(S)CR0[EXIDENABLE] is zero. */
        uint32_t exid                  : 16; /**< [ 15:  0](R/W/H) Stream identifier to match after masking. In CNXXXX, if a bit is ignored (MASK\<i\>==1), the
                                                                 respective EXID\<i\> bit will be cleared by hardware. */
#else /* Word 0 - Little Endian */
        uint32_t exid                  : 16; /**< [ 15:  0](R/W/H) Stream identifier to match after masking. In CNXXXX, if a bit is ignored (MASK\<i\>==1), the
                                                                 respective EXID\<i\> bit will be cleared by hardware. */
        uint32_t exmask_valid          : 16; /**< [ 31: 16](R/W) Masking of stream id bits irrelevent to the matching process.

                                                                 If MASK\<i\>==1, ID\<i\> is ignored.

                                                                 If MASK\<i\>==0, ID\<i\> is relevant for matching.

                                                                 Note \<31\> indicates VALID if SMMU()_(S)CR0[EXIDENABLE] is zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_smrx_s cn; */
};
typedef union bdk_smmux_smrx bdk_smmux_smrx_t;

static inline uint64_t BDK_SMMUX_SMRX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SMRX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=127)))
        return 0x830000000800ll + 0x1000000000ll * ((a) & 0x0) + 4ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=127)))
        return 0x830000000800ll + 0x1000000000ll * ((a) & 0x1) + 4ll * ((b) & 0x7f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=127)))
        return 0x830000000800ll + 0x1000000000ll * ((a) & 0x3) + 4ll * ((b) & 0x7f);
    __bdk_csr_fatal("SMMUX_SMRX", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_SMRX(a,b) bdk_smmux_smrx_t
#define bustype_BDK_SMMUX_SMRX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SMRX(a,b) "SMMUX_SMRX"
#define device_bar_BDK_SMMUX_SMRX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SMRX(a,b) (a)
#define arguments_BDK_SMMUX_SMRX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) smmu#_sptread_perf
 *
 * SMMU Secure Page Table Reads Performance Counter Register
 */
union bdk_smmux_sptread_perf
{
    uint64_t u;
    struct bdk_smmux_sptread_perf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](SR/W/H) Counts the number of page table reads issued to secure memory. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](SR/W/H) Counts the number of page table reads issued to secure memory. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_sptread_perf_s cn; */
};
typedef union bdk_smmux_sptread_perf bdk_smmux_sptread_perf_t;

static inline uint64_t BDK_SMMUX_SPTREAD_PERF(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SPTREAD_PERF(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000021060ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000021060ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000021060ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_SPTREAD_PERF", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_SPTREAD_PERF(a) bdk_smmux_sptread_perf_t
#define bustype_BDK_SMMUX_SPTREAD_PERF(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_SPTREAD_PERF(a) "SMMUX_SPTREAD_PERF"
#define device_bar_BDK_SMMUX_SPTREAD_PERF(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SPTREAD_PERF(a) (a)
#define arguments_BDK_SMMUX_SPTREAD_PERF(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_ssdr#
 *
 * SMMU Security State Definition Register
 * Internal:
 * INTERNAL: Address offset from SMM_GSSD_BASE.
 */
union bdk_smmux_ssdrx
{
    uint32_t u;
    struct bdk_smmux_ssdrx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ssd                   : 32; /**< [ 31:  0](SR/W) Security state definition, where each bit corresponds to a SSD index:
                                                                 0x0 = Corresponding SSD index is acting for the secure domain.
                                                                 0x1 = Nonsecure domain.

                                                                 Only accessible to secure software, else RAZ/WI. CNXXXX indexes this table by stream
                                                                 identifier, and uses the result of this table to also promote interrupts to secure
                                                                 interrupts. */
#else /* Word 0 - Little Endian */
        uint32_t ssd                   : 32; /**< [ 31:  0](SR/W) Security state definition, where each bit corresponds to a SSD index:
                                                                 0x0 = Corresponding SSD index is acting for the secure domain.
                                                                 0x1 = Nonsecure domain.

                                                                 Only accessible to secure software, else RAZ/WI. CNXXXX indexes this table by stream
                                                                 identifier, and uses the result of this table to also promote interrupts to secure
                                                                 interrupts. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_ssdrx_s cn; */
};
typedef union bdk_smmux_ssdrx bdk_smmux_ssdrx_t;

static inline uint64_t BDK_SMMUX_SSDRX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_SSDRX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=2047)))
        return 0x830000040000ll + 0x1000000000ll * ((a) & 0x0) + 4ll * ((b) & 0x7ff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=2047)))
        return 0x830000040000ll + 0x1000000000ll * ((a) & 0x1) + 4ll * ((b) & 0x7ff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=2047)))
        return 0x830000040000ll + 0x1000000000ll * ((a) & 0x3) + 4ll * ((b) & 0x7ff);
    __bdk_csr_fatal("SMMUX_SSDRX", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_SSDRX(a,b) bdk_smmux_ssdrx_t
#define bustype_BDK_SMMUX_SSDRX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_SSDRX(a,b) "SMMUX_SSDRX"
#define device_bar_BDK_SMMUX_SSDRX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_SSDRX(a,b) (a)
#define arguments_BDK_SMMUX_SSDRX(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_statusr
 *
 * SMMU Status Register
 */
union bdk_smmux_statusr
{
    uint32_t u;
    struct bdk_smmux_statusr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t dormant               : 1;  /**< [  0:  0](RAZ) Dormant hint.

                                                                   0x0 = The SMMU may have cached translation or configuration structure data, or
                                                                 be in the process of doing so.

                                                                   0x1 = The SMMU guarantees that no translation or configuration structure data
                                                                 is cached (and that no prefetches are in-flight).

                                                                 Software may avoid issuing configuration invalidation or TLB invalidation
                                                                 commands for changes to structures made visible to the SMMU before reading this
                                                                 hint as one.

                                                                 This bit might read as one if SMMU()_IDR0[DORMHINT]=1. If SMMU()_IDR0[DORMHINT]=0,
                                                                 the implementation does not support this hint and this bit reads as zero. */
#else /* Word 0 - Little Endian */
        uint32_t dormant               : 1;  /**< [  0:  0](RAZ) Dormant hint.

                                                                   0x0 = The SMMU may have cached translation or configuration structure data, or
                                                                 be in the process of doing so.

                                                                   0x1 = The SMMU guarantees that no translation or configuration structure data
                                                                 is cached (and that no prefetches are in-flight).

                                                                 Software may avoid issuing configuration invalidation or TLB invalidation
                                                                 commands for changes to structures made visible to the SMMU before reading this
                                                                 hint as one.

                                                                 This bit might read as one if SMMU()_IDR0[DORMHINT]=1. If SMMU()_IDR0[DORMHINT]=0,
                                                                 the implementation does not support this hint and this bit reads as zero. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_statusr_s cn; */
};
typedef union bdk_smmux_statusr bdk_smmux_statusr_t;

static inline uint64_t BDK_SMMUX_STATUSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_STATUSR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000040ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_STATUSR", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_STATUSR(a) bdk_smmux_statusr_t
#define bustype_BDK_SMMUX_STATUSR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_STATUSR(a) "SMMUX_STATUSR"
#define device_bar_BDK_SMMUX_STATUSR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_STATUSR(a) (a)
#define arguments_BDK_SMMUX_STATUSR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_stlbgstatus
 *
 * SMMU (Secure) Global Synchronize TLB Status Register
 * Gives the status of a TLB maintenance operation. Register fields are identical to those in
 * SMMU()_(S)TLBGSTATUS.
 */
union bdk_smmux_stlbgstatus
{
    uint32_t u;
    struct bdk_smmux_stlbgstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t gsactive              : 1;  /**< [  0:  0](RO/H) Global synchronize TLB invalidate active:
                                                                 0 = No global TLB synchronization operation is active.
                                                                 1 = A global TLB synchronization operation is active. */
#else /* Word 0 - Little Endian */
        uint32_t gsactive              : 1;  /**< [  0:  0](RO/H) Global synchronize TLB invalidate active:
                                                                 0 = No global TLB synchronization operation is active.
                                                                 1 = A global TLB synchronization operation is active. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_stlbgstatus_s cn; */
};
typedef union bdk_smmux_stlbgstatus bdk_smmux_stlbgstatus_t;

static inline uint64_t BDK_SMMUX_STLBGSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_STLBGSTATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000074ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000074ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000074ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_STLBGSTATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_STLBGSTATUS(a) bdk_smmux_stlbgstatus_t
#define bustype_BDK_SMMUX_STLBGSTATUS(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_STLBGSTATUS(a) "SMMUX_STLBGSTATUS"
#define device_bar_BDK_SMMUX_STLBGSTATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_STLBGSTATUS(a) (a)
#define arguments_BDK_SMMUX_STLBGSTATUS(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_stlbgsync
 *
 * SMMU (Secure) Global Synchronize TLB Invalidate Register
 * Starts a global synchronization operation that ensures the completion of any previously
 * accepted TLB invalidate operation. Register fields are identical to those in
 * SMMU()_(S)TLBGSYNC.
 */
union bdk_smmux_stlbgsync
{
    uint32_t u;
    struct bdk_smmux_stlbgsync_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#else /* Word 0 - Little Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_stlbgsync_s cn; */
};
typedef union bdk_smmux_stlbgsync bdk_smmux_stlbgsync_t;

static inline uint64_t BDK_SMMUX_STLBGSYNC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_STLBGSYNC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000070ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000070ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000070ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_STLBGSYNC", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_STLBGSYNC(a) bdk_smmux_stlbgsync_t
#define bustype_BDK_SMMUX_STLBGSYNC(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_STLBGSYNC(a) "SMMUX_STLBGSYNC"
#define device_bar_BDK_SMMUX_STLBGSYNC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_STLBGSYNC(a) (a)
#define arguments_BDK_SMMUX_STLBGSYNC(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_stlbiall
 *
 * SMMU Secure TLB Invalidate All Register
 * Invalidates all unlocked secure entries in the TLB. Register fields are identical to those in
 * SMMU()_TLBIALLH.
 */
union bdk_smmux_stlbiall
{
    uint32_t u;
    struct bdk_smmux_stlbiall_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t command               : 32; /**< [ 31:  0](SWO) Any write to this register will perform the synchronization. */
#else /* Word 0 - Little Endian */
        uint32_t command               : 32; /**< [ 31:  0](SWO) Any write to this register will perform the synchronization. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_stlbiall_s cn; */
};
typedef union bdk_smmux_stlbiall bdk_smmux_stlbiall_t;

static inline uint64_t BDK_SMMUX_STLBIALL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_STLBIALL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000060ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000060ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000060ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_STLBIALL", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_STLBIALL(a) bdk_smmux_stlbiall_t
#define bustype_BDK_SMMUX_STLBIALL(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_STLBIALL(a) "SMMUX_STLBIALL"
#define device_bar_BDK_SMMUX_STLBIALL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_STLBIALL(a) (a)
#define arguments_BDK_SMMUX_STLBIALL(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_stlbiallm
 *
 * SMMU Secure TLB Invalidate All Monitor Register
 * Invalidate all unlocked secure monitor entries in the TLB. Register fields are identical to
 * those in SMMU()_TLBIALLH.
 */
union bdk_smmux_stlbiallm
{
    uint32_t u;
    struct bdk_smmux_stlbiallm_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t command               : 32; /**< [ 31:  0](SWO) Any write to this register will perform the synchronization. */
#else /* Word 0 - Little Endian */
        uint32_t command               : 32; /**< [ 31:  0](SWO) Any write to this register will perform the synchronization. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_stlbiallm_s cn; */
};
typedef union bdk_smmux_stlbiallm bdk_smmux_stlbiallm_t;

static inline uint64_t BDK_SMMUX_STLBIALLM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_STLBIALLM(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000000bcll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000000bcll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000000bcll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_STLBIALLM", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_STLBIALLM(a) bdk_smmux_stlbiallm_t
#define bustype_BDK_SMMUX_STLBIALLM(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_STLBIALLM(a) "SMMUX_STLBIALLM"
#define device_bar_BDK_SMMUX_STLBIALLM(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_STLBIALLM(a) (a)
#define arguments_BDK_SMMUX_STLBIALLM(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_stlbivalm
 *
 * SMMU Secure Invalidate Monitor TLB by VA Last Register
 * This secure 64-bit register operates exactly as SMMU()_STLBIVAM, except the invalidation
 * need only apply to the caching of entries returned from the last level of translation table
 * walk. This 64-bit register supports the ARMv8 TLB invalidation operation address format.
 */
union bdk_smmux_stlbivalm
{
    uint64_t u;
    struct bdk_smmux_stlbivalm_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t address               : 44; /**< [ 43:  0](SWO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 44; /**< [ 43:  0](SWO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_stlbivalm_s cn; */
};
typedef union bdk_smmux_stlbivalm bdk_smmux_stlbivalm_t;

static inline uint64_t BDK_SMMUX_STLBIVALM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_STLBIVALM(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000000a0ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000000a0ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000000a0ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_STLBIVALM", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_STLBIVALM(a) bdk_smmux_stlbivalm_t
#define bustype_BDK_SMMUX_STLBIVALM(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_STLBIVALM(a) "SMMUX_STLBIVALM"
#define device_bar_BDK_SMMUX_STLBIVALM(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_STLBIVALM(a) (a)
#define arguments_BDK_SMMUX_STLBIVALM(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_stlbivam
 *
 * SMMU Secure Invalidate Monitor TLB by VA Register
 * This secure 64-bit register invalidates all monitor TLB entries that associated with the
 * specified virtual address and applies to all unlocked entries within the TLB. This 64-bit
 * register supports the ARMv8 TLB invalidation operation address format. Register fields are
 * identical to those in SMMU()_TLBIVAH64.
 */
union bdk_smmux_stlbivam
{
    uint64_t u;
    struct bdk_smmux_stlbivam_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t address               : 44; /**< [ 43:  0](SWO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 44; /**< [ 43:  0](SWO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_stlbivam_s cn; */
};
typedef union bdk_smmux_stlbivam bdk_smmux_stlbivam_t;

static inline uint64_t BDK_SMMUX_STLBIVAM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_STLBIVAM(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000000a8ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000000a8ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000000a8ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_STLBIVAM", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_STLBIVAM(a) bdk_smmux_stlbivam_t
#define bustype_BDK_SMMUX_STLBIVAM(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_STLBIVAM(a) "SMMUX_STLBIVAM"
#define device_bar_BDK_SMMUX_STLBIVAM(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_STLBIVAM(a) (a)
#define arguments_BDK_SMMUX_STLBIVAM(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_strtab_base
 *
 * SMMU Stream Table Base Register
 */
union bdk_smmux_strtab_base
{
    uint64_t u;
    struct bdk_smmux_strtab_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t ra                    : 1;  /**< [ 62: 62](R/W) SMMU(0)_S_STRTAB_BASE[RA] */
        uint64_t reserved_52_61        : 10;
        uint64_t addr                  : 46; /**< [ 51:  6](R/W) SMMU(0)_S_STRTAB_BASE[ADDR] */
        uint64_t reserved_0_5          : 6;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_5          : 6;
        uint64_t addr                  : 46; /**< [ 51:  6](R/W) SMMU(0)_S_STRTAB_BASE[ADDR] */
        uint64_t reserved_52_61        : 10;
        uint64_t ra                    : 1;  /**< [ 62: 62](R/W) SMMU(0)_S_STRTAB_BASE[RA] */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_strtab_base_s cn; */
};
typedef union bdk_smmux_strtab_base bdk_smmux_strtab_base_t;

static inline uint64_t BDK_SMMUX_STRTAB_BASE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_STRTAB_BASE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000080ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_STRTAB_BASE", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_STRTAB_BASE(a) bdk_smmux_strtab_base_t
#define bustype_BDK_SMMUX_STRTAB_BASE(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_STRTAB_BASE(a) "SMMUX_STRTAB_BASE"
#define device_bar_BDK_SMMUX_STRTAB_BASE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_STRTAB_BASE(a) (a)
#define arguments_BDK_SMMUX_STRTAB_BASE(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_strtab_base_cfg
 *
 * SMMU Stream Table Base Configuration Register
 * SMMU()_S_STRTAB_BASE_CFG is guarded by the respective SMMU()_S_CR0[SMMUEN] and
 * must only be modified when SMMU()_S_CR0[SMMUEN]=0. A write whilst
 * SMMU()_S_CR0[SMMUEN]=1 is constrained unpredictable and has one of the following
 * behaviors:
 *
 * * The register takes on any value, which might cause STEs to be fetched from an unpredictable
 *   address.
 *
 * * The write is ignored.
 *
 * * In CNXXXX, TBD which.
 *
 * A read following such a write will return an unknown value.
 *
 * Use of any reserved value or unsupported value combination in this register (for
 * example, selection of a two-level table when unsupported where
 * SMMU()_IDR0[ST_LEVEL]=0x0) causes the stream table to become inaccessible; a
 * transaction causing a lookup of an STE is terminated with abort and a SMMU_C_BAD_STREAMID_S
 * event recorded.
 */
union bdk_smmux_strtab_base_cfg
{
    uint32_t u;
    struct bdk_smmux_strtab_base_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t fmt                   : 2;  /**< [ 17: 16](R/W) SMMU(0)_S_STRTAB_BASE_CFG[FMT]
                                                                 Internal:
                                                                 When SMMU()_IDR0[ST_LEVEL]=0x0 (2-level unsupported), this field is RES0: its
                                                                 effective value is 0x0 regardless of any other value written. */
        uint32_t reserved_11_15        : 5;
        uint32_t split                 : 5;  /**< [ 10:  6](R/W) SMMU(0)_S_STRTAB_BASE_CFG[SPLIT]
                                                                 Internal:
                                                                 This field is ignored if FMT=0x0 and this field is RES0 when
                                                                 SMMU()_IDR0[ST_LEVEL]=0x0 (2-level unsupported). */
        uint32_t log2size              : 6;  /**< [  5:  0](R/W) SMMU(0)_S_STRTAB_BASE_CFG[LOG2SIZE] */
#else /* Word 0 - Little Endian */
        uint32_t log2size              : 6;  /**< [  5:  0](R/W) SMMU(0)_S_STRTAB_BASE_CFG[LOG2SIZE] */
        uint32_t split                 : 5;  /**< [ 10:  6](R/W) SMMU(0)_S_STRTAB_BASE_CFG[SPLIT]
                                                                 Internal:
                                                                 This field is ignored if FMT=0x0 and this field is RES0 when
                                                                 SMMU()_IDR0[ST_LEVEL]=0x0 (2-level unsupported). */
        uint32_t reserved_11_15        : 5;
        uint32_t fmt                   : 2;  /**< [ 17: 16](R/W) SMMU(0)_S_STRTAB_BASE_CFG[FMT]
                                                                 Internal:
                                                                 When SMMU()_IDR0[ST_LEVEL]=0x0 (2-level unsupported), this field is RES0: its
                                                                 effective value is 0x0 regardless of any other value written. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_strtab_base_cfg_s cn; */
};
typedef union bdk_smmux_strtab_base_cfg bdk_smmux_strtab_base_cfg_t;

static inline uint64_t BDK_SMMUX_STRTAB_BASE_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_STRTAB_BASE_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x830000000088ll + 0x1000000000ll * ((a) & 0x0);
    __bdk_csr_fatal("SMMUX_STRTAB_BASE_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_STRTAB_BASE_CFG(a) bdk_smmux_strtab_base_cfg_t
#define bustype_BDK_SMMUX_STRTAB_BASE_CFG(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_STRTAB_BASE_CFG(a) "SMMUX_STRTAB_BASE_CFG"
#define device_bar_BDK_SMMUX_STRTAB_BASE_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_STRTAB_BASE_CFG(a) (a)
#define arguments_BDK_SMMUX_STRTAB_BASE_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_tlb#_dat
 *
 * SMMU Secure TLB Diagnostic Data Register
 */
union bdk_smmux_tlbx_dat
{
    uint64_t u;
    struct bdk_smmux_tlbx_dat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal TLB state, for diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal TLB state, for diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_tlbx_dat_s cn; */
};
typedef union bdk_smmux_tlbx_dat bdk_smmux_tlbx_dat_t;

static inline uint64_t BDK_SMMUX_TLBX_DAT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_TLBX_DAT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=2047)))
        return 0x830000028000ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0x7ff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=4095)))
        return 0x830000028000ll + 0x1000000000ll * ((a) & 0x1) + 8ll * ((b) & 0xfff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=4095)))
        return 0x830000028000ll + 0x1000000000ll * ((a) & 0x3) + 8ll * ((b) & 0xfff);
    __bdk_csr_fatal("SMMUX_TLBX_DAT", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_TLBX_DAT(a,b) bdk_smmux_tlbx_dat_t
#define bustype_BDK_SMMUX_TLBX_DAT(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_TLBX_DAT(a,b) "SMMUX_TLBX_DAT"
#define device_bar_BDK_SMMUX_TLBX_DAT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_TLBX_DAT(a,b) (a)
#define arguments_BDK_SMMUX_TLBX_DAT(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) smmu#_tlbiallh
 *
 * SMMU TLB Invalidate Hypervisor Register
 * Invalidate all hypervisor tagged entries in the TLB, regardless of the security state of each
 * entry. It can optionally apply to all unlocked entries.
 */
union bdk_smmux_tlbiallh
{
    uint32_t u;
    struct bdk_smmux_tlbiallh_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#else /* Word 0 - Little Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_tlbiallh_s cn; */
};
typedef union bdk_smmux_tlbiallh bdk_smmux_tlbiallh_t;

static inline uint64_t BDK_SMMUX_TLBIALLH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_TLBIALLH(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x83000000006cll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x83000000006cll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x83000000006cll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_TLBIALLH", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_TLBIALLH(a) bdk_smmux_tlbiallh_t
#define bustype_BDK_SMMUX_TLBIALLH(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_TLBIALLH(a) "SMMUX_TLBIALLH"
#define device_bar_BDK_SMMUX_TLBIALLH(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_TLBIALLH(a) (a)
#define arguments_BDK_SMMUX_TLBIALLH(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_tlbiallnsnh
 *
 * SMMU TLB Invalidate Non-Secure Non-Hypervisor Register
 * Invalidate all nonsecure, non-hypervisor tagged entries in the TLB. Register fields are
 * identical to those in SMMU()_TLBIALLH. It can optionally apply to all unlocked entries.
 */
union bdk_smmux_tlbiallnsnh
{
    uint32_t u;
    struct bdk_smmux_tlbiallnsnh_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#else /* Word 0 - Little Endian */
        uint32_t command               : 32; /**< [ 31:  0](WO) Any write to this register will perform the synchronization. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_tlbiallnsnh_s cn; */
};
typedef union bdk_smmux_tlbiallnsnh bdk_smmux_tlbiallnsnh_t;

static inline uint64_t BDK_SMMUX_TLBIALLNSNH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_TLBIALLNSNH(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000068ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000068ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000068ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_TLBIALLNSNH", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_TLBIALLNSNH(a) bdk_smmux_tlbiallnsnh_t
#define bustype_BDK_SMMUX_TLBIALLNSNH(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_TLBIALLNSNH(a) "SMMUX_TLBIALLNSNH"
#define device_bar_BDK_SMMUX_TLBIALLNSNH(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_TLBIALLNSNH(a) (a)
#define arguments_BDK_SMMUX_TLBIALLNSNH(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_tlbivah
 *
 * SMMU TLB Invalidate Hypervisor Legacy Register
 * Backward compatible version of SMMU()_TLBIVAH64.
 */
union bdk_smmux_tlbivah
{
    uint32_t u;
    struct bdk_smmux_tlbivah_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_tlbivah_s cn; */
};
typedef union bdk_smmux_tlbivah bdk_smmux_tlbivah_t;

static inline uint64_t BDK_SMMUX_TLBIVAH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_TLBIVAH(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000078ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000078ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000078ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_TLBIVAH", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_TLBIVAH(a) bdk_smmux_tlbivah_t
#define bustype_BDK_SMMUX_TLBIVAH(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_TLBIVAH(a) "SMMUX_TLBIVAH"
#define device_bar_BDK_SMMUX_TLBIVAH(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_TLBIVAH(a) (a)
#define arguments_BDK_SMMUX_TLBIVAH(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_tlbivah64
 *
 * SMMU Invalidate Hypervisor TLB by VA Register
 * Invalidate all hypervisor tagged entries in the TLB, regardless of the security tagging
 * associated with the entry. It can optionally apply to all unlocked entries.
 */
union bdk_smmux_tlbivah64
{
    uint64_t u;
    struct bdk_smmux_tlbivah64_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t address               : 44; /**< [ 43:  0](WO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 44; /**< [ 43:  0](WO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_tlbivah64_s cn; */
};
typedef union bdk_smmux_tlbivah64 bdk_smmux_tlbivah64_t;

static inline uint64_t BDK_SMMUX_TLBIVAH64(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_TLBIVAH64(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000000c0ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000000c0ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000000c0ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_TLBIVAH64", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_TLBIVAH64(a) bdk_smmux_tlbivah64_t
#define bustype_BDK_SMMUX_TLBIVAH64(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_TLBIVAH64(a) "SMMUX_TLBIVAH64"
#define device_bar_BDK_SMMUX_TLBIVAH64(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_TLBIVAH64(a) (a)
#define arguments_BDK_SMMUX_TLBIVAH64(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_tlbivalh64
 *
 * SMMU Invalidate Hypervisor TLB by VA Last Register
 * This 64-bit register operates exactly as SMMU()_TLBIVAH64, except the
 * invalidation need only apply to the caching of entries returned from the last level of
 * translation table walk. This 64-bit register supports the ARMv8 TLB invalidation operation
 * address format.
 */
union bdk_smmux_tlbivalh64
{
    uint64_t u;
    struct bdk_smmux_tlbivalh64_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_44_63        : 20;
        uint64_t address               : 44; /**< [ 43:  0](WO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 44; /**< [ 43:  0](WO) Virtual address \<55:12\> to be invalidated. Note: this matches the format of the
                                                                 addresses supplied to ARMv8 processor TLBI invalidation instructions. If the
                                                                 page size is 64kB then bits corresponding to [ADDRESS]\<15:12\> are ignored. The
                                                                 address will be extended to bit \<63\> by copying bit \<55\>. */
        uint64_t reserved_44_63        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_tlbivalh64_s cn; */
};
typedef union bdk_smmux_tlbivalh64 bdk_smmux_tlbivalh64_t;

static inline uint64_t BDK_SMMUX_TLBIVALH64(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_TLBIVALH64(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000000b0ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000000b0ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000000b0ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_TLBIVALH64", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_TLBIVALH64(a) bdk_smmux_tlbivalh64_t
#define bustype_BDK_SMMUX_TLBIVALH64(a) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_TLBIVALH64(a) "SMMUX_TLBIVALH64"
#define device_bar_BDK_SMMUX_TLBIVALH64(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_TLBIVALH64(a) (a)
#define arguments_BDK_SMMUX_TLBIVALH64(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_tlbivmid
 *
 * SMMU TLB Invalidate VMID Register
 * Invalidate all nonsecure, non-hypervisor TLB entries having the specified VMID. It can
 * optionally apply to all entries.
 */
union bdk_smmux_tlbivmid
{
    uint32_t u;
    struct bdk_smmux_tlbivmid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t vmid                  : 16; /**< [ 15:  0](WO) The virtual machine identifier to use in the invalidate operation.
                                                                 Internal:
                                                                 Bits 15:8
                                                                 defined by the large system extensions. */
#else /* Word 0 - Little Endian */
        uint32_t vmid                  : 16; /**< [ 15:  0](WO) The virtual machine identifier to use in the invalidate operation.
                                                                 Internal:
                                                                 Bits 15:8
                                                                 defined by the large system extensions. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_tlbivmid_s cn; */
};
typedef union bdk_smmux_tlbivmid bdk_smmux_tlbivmid_t;

static inline uint64_t BDK_SMMUX_TLBIVMID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_TLBIVMID(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x830000000064ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x830000000064ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x830000000064ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_TLBIVMID", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_TLBIVMID(a) bdk_smmux_tlbivmid_t
#define bustype_BDK_SMMUX_TLBIVMID(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_TLBIVMID(a) "SMMUX_TLBIVMID"
#define device_bar_BDK_SMMUX_TLBIVMID(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_TLBIVMID(a) (a)
#define arguments_BDK_SMMUX_TLBIVMID(a) (a),-1,-1,-1

/**
 * Register (NCB32b) smmu#_tlbivmids1
 *
 * SMMU TLB Invalidate by VMID Register
 * Invalidate all nonsecure, non-hypervisor TLB entries having the specified VMID. In an
 * implementation using combined S1 + S2 TLB entries, this operation must invalidate any entries
 * tagged with a valid matching VMID. It operates exactly as SMMU()_TLBIVMID, except it only
 * applies to caching of entries containing information from the first stage of translation.
 */
union bdk_smmux_tlbivmids1
{
    uint32_t u;
    struct bdk_smmux_tlbivmids1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t vmid                  : 16; /**< [ 15:  0](WO) The virtual machine identifier to use in the invalidate operation.
                                                                 Internal:
                                                                 Bits 15:8
                                                                 defined by the large system extensions. */
#else /* Word 0 - Little Endian */
        uint32_t vmid                  : 16; /**< [ 15:  0](WO) The virtual machine identifier to use in the invalidate operation.
                                                                 Internal:
                                                                 Bits 15:8
                                                                 defined by the large system extensions. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_tlbivmids1_s cn; */
};
typedef union bdk_smmux_tlbivmids1 bdk_smmux_tlbivmids1_t;

static inline uint64_t BDK_SMMUX_TLBIVMIDS1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_TLBIVMIDS1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x8300000000b8ll + 0x1000000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x8300000000b8ll + 0x1000000000ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=3))
        return 0x8300000000b8ll + 0x1000000000ll * ((a) & 0x3);
    __bdk_csr_fatal("SMMUX_TLBIVMIDS1", 1, a, 0, 0, 0);
}

#define typedef_BDK_SMMUX_TLBIVMIDS1(a) bdk_smmux_tlbivmids1_t
#define bustype_BDK_SMMUX_TLBIVMIDS1(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_SMMUX_TLBIVMIDS1(a) "SMMUX_TLBIVMIDS1"
#define device_bar_BDK_SMMUX_TLBIVMIDS1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_TLBIVMIDS1(a) (a)
#define arguments_BDK_SMMUX_TLBIVMIDS1(a) (a),-1,-1,-1

/**
 * Register (NCB) smmu#_wcu#_dat
 *
 * SMMU Secure Walker Cache Diagnostic Data Register
 */
union bdk_smmux_wcux_dat
{
    uint64_t u;
    struct bdk_smmux_wcux_dat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal WCU state, for diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](SRO/H) Internal WCU state, for diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_smmux_wcux_dat_s cn; */
};
typedef union bdk_smmux_wcux_dat bdk_smmux_wcux_dat_t;

static inline uint64_t BDK_SMMUX_WCUX_DAT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_SMMUX_WCUX_DAT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a==0) && (b<=1023)))
        return 0x830000024000ll + 0x1000000000ll * ((a) & 0x0) + 8ll * ((b) & 0x3ff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=1) && (b<=2047)))
        return 0x830000024000ll + 0x1000000000ll * ((a) & 0x1) + 8ll * ((b) & 0x7ff);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=3) && (b<=2047)))
        return 0x830000024000ll + 0x1000000000ll * ((a) & 0x3) + 8ll * ((b) & 0x7ff);
    __bdk_csr_fatal("SMMUX_WCUX_DAT", 2, a, b, 0, 0);
}

#define typedef_BDK_SMMUX_WCUX_DAT(a,b) bdk_smmux_wcux_dat_t
#define bustype_BDK_SMMUX_WCUX_DAT(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_SMMUX_WCUX_DAT(a,b) "SMMUX_WCUX_DAT"
#define device_bar_BDK_SMMUX_WCUX_DAT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_SMMUX_WCUX_DAT(a,b) (a)
#define arguments_BDK_SMMUX_WCUX_DAT(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_SMMU_H__ */
