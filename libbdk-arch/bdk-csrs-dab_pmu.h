#ifndef __BDK_CSRS_DAB_PMU_H__
#define __BDK_CSRS_DAB_PMU_H__
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
 * Cavium DAB_PMU.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration pmu_perf_e
 *
 * Performance Counter Event Enumeration
 * Enumerates the events that may be counted.  See PMU()_PMEVTYPER()_EL0[EVTCOUNT].
 * Internal:
 * \<pre\>
 *    0x0000 to 0x003F    Common architectural and microarchitectural events
 *       0x0020 to 0x03F      ARM house style events
 *       0x0040 to 0x04F      ARM Recommended, implementation defined events (Aka ARM House
 * Style)
 *    0x0040 to 0x00BF    ARM recommended common architectural and microarchitectural events.
 * IMPLEMENTATION DEFINED
 *    0x00C0 to 0x3FFF    IMPLEMENTATION DEFINED
 *      0x0180 to 0x01B7     Cavium Misc Counters
 *      0x01B8 to 0x01FF     Cavium - special instructions and events
 *      0x0300 to 0x03FF     Cavium - can be secure mode only
 *    0x4000 to 0x403F    Common architectural and microarchitectural events (PMCEID0_EL0[63:32],
 * PMCEID0_EL1[63:32])
 *    0x4040 to 0x40BF    ARM recommended common architectural and microarchitectural events.
 * IMPLEMENTATION DEFINED
 *    0x40C0 to 0x7FFF    IMPLEMENTATION DEFINED
 *    0x8000 to 0x80BF    Reserved
 *    0x80C0 to 0xBFFF    IMPLEMENTATION DEFINED
 *    0xC000 to 0xC0BF    Reserved
 *    0xC0C0 to 0xFFFF    IMPLEMENTATION DEFINED
 * \</pre\>
 */
#define BDK_PMU_PERF_E_AES_FOLDED (0x4c14)
#define BDK_PMU_PERF_E_ASE_SPEC (0x74)
#define BDK_PMU_PERF_E_ASID_OVF (0x300)
#define BDK_PMU_PERF_E_BADD (0xe0)
#define BDK_PMU_PERF_E_BADDL2 (0xe1)
#define BDK_PMU_PERF_E_BFILL (0xe2)
#define BDK_PMU_PERF_E_BR (0xc7)
#define BDK_PMU_PERF_E_BRMIS (0xc8)
#define BDK_PMU_PERF_E_BR_COND_RETIRED (0x4c35)
#define BDK_PMU_PERF_E_BR_FOLDED (0xc5)
#define BDK_PMU_PERF_E_BR_FOLDED_RAW (0xc6)
#define BDK_PMU_PERF_E_BR_FOLDED_SPEC (0xc6)
#define BDK_PMU_PERF_E_BR_IMMED_RETIRED (0xd)
#define BDK_PMU_PERF_E_BR_IMMED_SPEC (0x78)
#define BDK_PMU_PERF_E_BR_INDIRECT_SPEC (0x7a)
#define BDK_PMU_PERF_E_BR_MIS_PRED (0x10)
#define BDK_PMU_PERF_E_BR_MIS_PRED_RETIRED (0x22)
#define BDK_PMU_PERF_E_BR_PRED (0x12)
#define BDK_PMU_PERF_E_BR_REMOVED (0x4c44)
#define BDK_PMU_PERF_E_BR_RETIRED (0x21)
#define BDK_PMU_PERF_E_BR_RETURN_RETIRED (0xe)
#define BDK_PMU_PERF_E_BR_RETURN_SPEC (0x79)
#define BDK_PMU_PERF_E_BR_UNCOND_NOLINK_RETIRED (0x4c36)
#define BDK_PMU_PERF_E_BUS_ACCESS (0x19)
#define BDK_PMU_PERF_E_BUS_ACCESS_LD (0x60)
#define BDK_PMU_PERF_E_BUS_ACCESS_NORMAL (0x64)
#define BDK_PMU_PERF_E_BUS_ACCESS_NOT_SHARED (0x63)
#define BDK_PMU_PERF_E_BUS_ACCESS_PERIPH (0x65)
#define BDK_PMU_PERF_E_BUS_ACCESS_SHARED (0x62)
#define BDK_PMU_PERF_E_BUS_ACCESS_ST (0x61)
#define BDK_PMU_PERF_E_BUS_CYCLES (0x1d)
#define BDK_PMU_PERF_E_CAS_SPEC (0x4c23)
#define BDK_PMU_PERF_E_CDMISS (0xe6)
#define BDK_PMU_PERF_E_CHAIN (0x1e)
#define BDK_PMU_PERF_E_CID_WRITE_RETIRED (0xb)
#define BDK_PMU_PERF_E_CIMISS (0xd8)
#define BDK_PMU_PERF_E_CONST_REMOVED (0x4c13)
#define BDK_PMU_PERF_E_CPU_CYCLES (0x11)
#define BDK_PMU_PERF_E_CRYPTO_SPEC (0x77)
#define BDK_PMU_PERF_E_DC_CIVAC (0x1be)
#define BDK_PMU_PERF_E_DC_CVAC (0x1bf)
#define BDK_PMU_PERF_E_DC_CVAU (0x1c0)
#define BDK_PMU_PERF_E_DC_ISW_L1 (0x1c1)
#define BDK_PMU_PERF_E_DC_ISW_L2 (0x1c2)
#define BDK_PMU_PERF_E_DC_IVAC (0x1c3)
#define BDK_PMU_PERF_E_DDIDS (0xe3)
#define BDK_PMU_PERF_E_DIDNA (0xe5)
#define BDK_PMU_PERF_E_DIDNT_DUAL_ISSUE_REASONX(a) (0x4e00 + (a))
#define BDK_PMU_PERF_E_DIDNT_ISSUE_REASONX(a) (0x4d00 + (a))
#define BDK_PMU_PERF_E_DISSUE (0xc4)
#define BDK_PMU_PERF_E_DMB_ISH (0x1f2)
#define BDK_PMU_PERF_E_DMB_NSH (0x1f1)
#define BDK_PMU_PERF_E_DMB_OSH (0x1f3)
#define BDK_PMU_PERF_E_DMB_SPEC (0x7e)
#define BDK_PMU_PERF_E_DMB_SY (0x1f4)
#define BDK_PMU_PERF_E_DP_SPEC (0x73)
#define BDK_PMU_PERF_E_DSB_ISH (0x1f6)
#define BDK_PMU_PERF_E_DSB_NSH (0x1f5)
#define BDK_PMU_PERF_E_DSB_OSH (0x1f7)
#define BDK_PMU_PERF_E_DSB_SPEC (0x7d)
#define BDK_PMU_PERF_E_DSB_SY (0x1f8)
#define BDK_PMU_PERF_E_DTLB_WALK (0x34)
#define BDK_PMU_PERF_E_ERET_MIS (0xe7)
#define BDK_PMU_PERF_E_EXC_DABORT (0x84)
#define BDK_PMU_PERF_E_EXC_FIQ (0x87)
#define BDK_PMU_PERF_E_EXC_HVC (0x8a)
#define BDK_PMU_PERF_E_EXC_IRQ (0x86)
#define BDK_PMU_PERF_E_EXC_PABORT (0x83)
#define BDK_PMU_PERF_E_EXC_RETURN (0xa)
#define BDK_PMU_PERF_E_EXC_SMC (0x88)
#define BDK_PMU_PERF_E_EXC_SVC (0x82)
#define BDK_PMU_PERF_E_EXC_TAKEN (9)
#define BDK_PMU_PERF_E_EXC_TRAP_DABORT (0x8c)
#define BDK_PMU_PERF_E_EXC_TRAP_FIQ (0x8f)
#define BDK_PMU_PERF_E_EXC_TRAP_IRQ (0x8e)
#define BDK_PMU_PERF_E_EXC_TRAP_OTHER (0x8d)
#define BDK_PMU_PERF_E_EXC_TRAP_PABORT (0x8b)
#define BDK_PMU_PERF_E_EXC_UNDEF (0x81)
#define BDK_PMU_PERF_E_FISSION_SPEC (0x4c31)
#define BDK_PMU_PERF_E_FLEX_EX_DEL0 (0x180)
#define BDK_PMU_PERF_E_FLEX_EX_DEL1 (0x181)
#define BDK_PMU_PERF_E_FLEX_EX_DEL2 (0x182)
#define BDK_PMU_PERF_E_FLEX_EX_DEL3 (0x183)
#define BDK_PMU_PERF_E_FP_SIMD_SPEC (0x4c34)
#define BDK_PMU_PERF_E_FUSION_SPEC (0x4c30)
#define BDK_PMU_PERF_E_F_MASK_CYC (0x302)
#define BDK_PMU_PERF_E_GLBL_SYNC (0x1b8)
#define BDK_PMU_PERF_E_IC_IALLUX (0x1ba)
#define BDK_PMU_PERF_E_IC_IALLU_RCVD (0x1bc)
#define BDK_PMU_PERF_E_IC_IVAU (0x1bb)
#define BDK_PMU_PERF_E_IC_IVAU_RCVD (0x1bd)
#define BDK_PMU_PERF_E_IDIDS (0xe4)
#define BDK_PMU_PERF_E_IFILL (0xd3)
#define BDK_PMU_PERF_E_II (0xd6)
#define BDK_PMU_PERF_E_INST_RETIRED (8)
#define BDK_PMU_PERF_E_INST_SPEC (0x1b)
#define BDK_PMU_PERF_E_INT_ARITH_LOGIC_SPEC (0x4c32)
#define BDK_PMU_PERF_E_INT_SIMD_SPEC (0x4c33)
#define BDK_PMU_PERF_E_IP (0xd7)
#define BDK_PMU_PERF_E_IPREF_LDI (0xd1)
#define BDK_PMU_PERF_E_ISB (0x1f0)
#define BDK_PMU_PERF_E_ISB_SPEC (0x7c)
#define BDK_PMU_PERF_E_ISSUE (0xc1)
#define BDK_PMU_PERF_E_ISSUE_CSRCLK (0xee)
#define BDK_PMU_PERF_E_ISSUE_ECLK (0xc0)
#define BDK_PMU_PERF_E_ITLB_WALK (0x35)
#define BDK_PMU_PERF_E_IUNA (0xcc)
#define BDK_PMU_PERF_E_I_MASK_CYC (0x303)
#define BDK_PMU_PERF_E_L0D_TLB_REFILL (0x190)
#define BDK_PMU_PERF_E_L0D_TLB_REFILL_LD (0x191)
#define BDK_PMU_PERF_E_L0D_TLB_REFILL_ST (0x192)
#define BDK_PMU_PERF_E_L0I_TLB_REFILL (0x18f)
#define BDK_PMU_PERF_E_L1D_CACHE (4)
#define BDK_PMU_PERF_E_L1D_CACHE_ALLOCATE (0x1f)
#define BDK_PMU_PERF_E_L1D_CACHE_INVAL (0x48)
#define BDK_PMU_PERF_E_L1D_CACHE_LD (0x40)
#define BDK_PMU_PERF_E_L1D_CACHE_MISS_ST (0xe9)
#define BDK_PMU_PERF_E_L1D_CACHE_PREF (0xea)
#define BDK_PMU_PERF_E_L1D_CACHE_PREF_HARDWARE_SPEC (0x4c26)
#define BDK_PMU_PERF_E_L1D_CACHE_PREF_HARDWARE_SPEC_DROPPED (0x4c27)
#define BDK_PMU_PERF_E_L1D_CACHE_REFILL (3)
#define BDK_PMU_PERF_E_L1D_CACHE_REFILL_INNER (0x44)
#define BDK_PMU_PERF_E_L1D_CACHE_REFILL_LD (0x42)
#define BDK_PMU_PERF_E_L1D_CACHE_REFILL_OUTER (0x45)
#define BDK_PMU_PERF_E_L1D_CACHE_REFILL_PREF (0xeb)
#define BDK_PMU_PERF_E_L1D_CACHE_REFILL_ST (0x43)
#define BDK_PMU_PERF_E_L1D_CACHE_ST (0x41)
#define BDK_PMU_PERF_E_L1D_CACHE_WB (0x15)
#define BDK_PMU_PERF_E_L1D_CACHE_WB_CLEAN (0x47)
#define BDK_PMU_PERF_E_L1D_CACHE_WB_VICTIM (0x46)
#define BDK_PMU_PERF_E_L1D_PTW_ACC_IPA_S1 (0x198)
#define BDK_PMU_PERF_E_L1D_PTW_ACC_L0_S1 (0x194)
#define BDK_PMU_PERF_E_L1D_PTW_ACC_L1_S1 (0x195)
#define BDK_PMU_PERF_E_L1D_PTW_ACC_L2_S1 (0x196)
#define BDK_PMU_PERF_E_L1D_PTW_ACC_L3_S1 (0x197)
#define BDK_PMU_PERF_E_L1D_PTW_PWC_REFILL_L0_S1 (0x19e)
#define BDK_PMU_PERF_E_L1D_PTW_PWC_REFILL_L0_S2 (0x1a2)
#define BDK_PMU_PERF_E_L1D_PTW_PWC_REFILL_L1_S1 (0x19f)
#define BDK_PMU_PERF_E_L1D_PTW_PWC_REFILL_L1_S2 (0x1a3)
#define BDK_PMU_PERF_E_L1D_PTW_PWC_REFILL_L2_S1 (0x1a0)
#define BDK_PMU_PERF_E_L1D_PTW_PWC_REFILL_L2_S2 (0x1a4)
#define BDK_PMU_PERF_E_L1D_PTW_PWC_REFILL_L3_S1 (0x1a1)
#define BDK_PMU_PERF_E_L1D_PTW_PWC_REFILL_L3_S2 (0x1a5)
#define BDK_PMU_PERF_E_L1D_PTW_REFILL_IPA_S2 (0x19d)
#define BDK_PMU_PERF_E_L1D_PTW_REFILL_L0_S1 (0x199)
#define BDK_PMU_PERF_E_L1D_PTW_REFILL_L1_S1 (0x19a)
#define BDK_PMU_PERF_E_L1D_PTW_REFILL_L2_S1 (0x19b)
#define BDK_PMU_PERF_E_L1D_PTW_REFILL_L3_S1 (0x19c)
#define BDK_PMU_PERF_E_L1D_TLB (0x25)
#define BDK_PMU_PERF_E_L1D_TLB_LD (0x4e)
#define BDK_PMU_PERF_E_L1D_TLB_REFILL (5)
#define BDK_PMU_PERF_E_L1D_TLB_REFILL_LD (0x4c)
#define BDK_PMU_PERF_E_L1D_TLB_REFILL_ST (0x4d)
#define BDK_PMU_PERF_E_L1D_TLB_ST (0x4f)
#define BDK_PMU_PERF_E_L1I_CACHE (0x14)
#define BDK_PMU_PERF_E_L1I_CACHE_PREF (0xec)
#define BDK_PMU_PERF_E_L1I_CACHE_REFILL (1)
#define BDK_PMU_PERF_E_L1I_CACHE_REFILL_PREF (0xed)
#define BDK_PMU_PERF_E_L1I_PTW_ACC_IPA_S1 (0x1aa)
#define BDK_PMU_PERF_E_L1I_PTW_ACC_L0_S1 (0x1a6)
#define BDK_PMU_PERF_E_L1I_PTW_ACC_L1_S1 (0x1a7)
#define BDK_PMU_PERF_E_L1I_PTW_ACC_L2_S1 (0x1a8)
#define BDK_PMU_PERF_E_L1I_PTW_ACC_L3_S1 (0x1a9)
#define BDK_PMU_PERF_E_L1I_PTW_PWC_REFILL_L0_S1 (0x1b0)
#define BDK_PMU_PERF_E_L1I_PTW_PWC_REFILL_L0_S2 (0x1b4)
#define BDK_PMU_PERF_E_L1I_PTW_PWC_REFILL_L1_S1 (0x1b1)
#define BDK_PMU_PERF_E_L1I_PTW_PWC_REFILL_L1_S2 (0x1b5)
#define BDK_PMU_PERF_E_L1I_PTW_PWC_REFILL_L2_S1 (0x1b2)
#define BDK_PMU_PERF_E_L1I_PTW_PWC_REFILL_L2_S2 (0x1b6)
#define BDK_PMU_PERF_E_L1I_PTW_PWC_REFILL_L3_S1 (0x1b3)
#define BDK_PMU_PERF_E_L1I_PTW_PWC_REFILL_L3_S2 (0x1b7)
#define BDK_PMU_PERF_E_L1I_PTW_REFILL_IPA_S2 (0x1af)
#define BDK_PMU_PERF_E_L1I_PTW_REFILL_L0_S1 (0x1ab)
#define BDK_PMU_PERF_E_L1I_PTW_REFILL_L1_S1 (0x1ac)
#define BDK_PMU_PERF_E_L1I_PTW_REFILL_L2_S1 (0x1ad)
#define BDK_PMU_PERF_E_L1I_PTW_REFILL_L3_S1 (0x1ae)
#define BDK_PMU_PERF_E_L1I_TLB (0x26)
#define BDK_PMU_PERF_E_L1I_TLB_REFILL (2)
#define BDK_PMU_PERF_E_L2C_EVENT_1 (0x4c00)
#define BDK_PMU_PERF_E_L2C_EVENT_10 (0x4c09)
#define BDK_PMU_PERF_E_L2C_EVENT_11 (0x4c0a)
#define BDK_PMU_PERF_E_L2C_EVENT_12 (0x4c0b)
#define BDK_PMU_PERF_E_L2C_EVENT_13 (0x4c0c)
#define BDK_PMU_PERF_E_L2C_EVENT_14 (0x4c0d)
#define BDK_PMU_PERF_E_L2C_EVENT_15 (0x4c0e)
#define BDK_PMU_PERF_E_L2C_EVENT_2 (0x4c01)
#define BDK_PMU_PERF_E_L2C_EVENT_3 (0x4c02)
#define BDK_PMU_PERF_E_L2C_EVENT_4 (0x4c03)
#define BDK_PMU_PERF_E_L2C_EVENT_5 (0x4c04)
#define BDK_PMU_PERF_E_L2C_EVENT_6 (0x4c05)
#define BDK_PMU_PERF_E_L2C_EVENT_7 (0x4c06)
#define BDK_PMU_PERF_E_L2C_EVENT_8 (0x4c07)
#define BDK_PMU_PERF_E_L2C_EVENT_9 (0x4c08)
#define BDK_PMU_PERF_E_L2D_CACHE (0x16)
#define BDK_PMU_PERF_E_L2D_CACHE_ALLOCATE (0x20)
#define BDK_PMU_PERF_E_L2D_CACHE_CACHE_INVAL (0x58)
#define BDK_PMU_PERF_E_L2D_CACHE_LD (0x50)
#define BDK_PMU_PERF_E_L2D_CACHE_REFILL (0x17)
#define BDK_PMU_PERF_E_L2D_CACHE_REFILL_LD (0x52)
#define BDK_PMU_PERF_E_L2D_CACHE_REFILL_ST (0x53)
#define BDK_PMU_PERF_E_L2D_CACHE_ST (0x51)
#define BDK_PMU_PERF_E_L2D_CACHE_WB (0x18)
#define BDK_PMU_PERF_E_L2D_CACHE_WB_CLEAN (0x57)
#define BDK_PMU_PERF_E_L2D_CACHE_WB_VICTIM (0x56)
#define BDK_PMU_PERF_E_L2D_TLB (0x2f)
#define BDK_PMU_PERF_E_L2D_TLB_REFILL (0x2d)
#define BDK_PMU_PERF_E_L2D_TLB_REFILL_LD (0x5c)
#define BDK_PMU_PERF_E_L2D_TLB_REFILL_ST (0x5d)
#define BDK_PMU_PERF_E_L2I_CACHE (0x27)
#define BDK_PMU_PERF_E_L2I_CACHE_REFILL (0x28)
#define BDK_PMU_PERF_E_L2I_TLB (0x30)
#define BDK_PMU_PERF_E_L2I_TLB_REFILL (0x2e)
#define BDK_PMU_PERF_E_L3D_CACHE (0x2b)
#define BDK_PMU_PERF_E_L3D_CACHE_ALLOCATE (0x29)
#define BDK_PMU_PERF_E_L3D_CACHE_RD (0xa0)
#define BDK_PMU_PERF_E_L3D_CACHE_REFILL (0x2a)
#define BDK_PMU_PERF_E_L3D_CACHE_REFILL_RD (0xa2)
#define BDK_PMU_PERF_E_L3D_CACHE_REFILL_WR (0xa3)
#define BDK_PMU_PERF_E_L3D_CACHE_WB (0x2c)
#define BDK_PMU_PERF_E_L3D_CACHE_WB_VICTIM (0xa6)
#define BDK_PMU_PERF_E_L3D_CACHE_WR (0xa1)
#define BDK_PMU_PERF_E_L3D_EVENT_1 (0x4c00)
#define BDK_PMU_PERF_E_L3D_EVENT_10 (0x4c09)
#define BDK_PMU_PERF_E_L3D_EVENT_11 (0x4c0a)
#define BDK_PMU_PERF_E_L3D_EVENT_12 (0x4c0b)
#define BDK_PMU_PERF_E_L3D_EVENT_13 (0x4c0c)
#define BDK_PMU_PERF_E_L3D_EVENT_14 (0x4c0d)
#define BDK_PMU_PERF_E_L3D_EVENT_15 (0x4c0e)
#define BDK_PMU_PERF_E_L3D_EVENT_16 (0x4c0f)
#define BDK_PMU_PERF_E_L3D_EVENT_17 (0x4c10)
#define BDK_PMU_PERF_E_L3D_EVENT_18 (0x4c11)
#define BDK_PMU_PERF_E_L3D_EVENT_2 (0x4c01)
#define BDK_PMU_PERF_E_L3D_EVENT_3 (0x4c02)
#define BDK_PMU_PERF_E_L3D_EVENT_4 (0x4c03)
#define BDK_PMU_PERF_E_L3D_EVENT_5 (0x4c04)
#define BDK_PMU_PERF_E_L3D_EVENT_6 (0x4c05)
#define BDK_PMU_PERF_E_L3D_EVENT_7 (0x4c06)
#define BDK_PMU_PERF_E_L3D_EVENT_8 (0x4c07)
#define BDK_PMU_PERF_E_L3D_EVENT_9 (0x4c08)
#define BDK_PMU_PERF_E_L3I_CACHE (0x1fc)
#define BDK_PMU_PERF_E_L3I_CACHE_REFILL (0x1fd)
#define BDK_PMU_PERF_E_LDREX_SPEC (0x6c)
#define BDK_PMU_PERF_E_LDST_SPEC (0x72)
#define BDK_PMU_PERF_E_LDX (0x1f9)
#define BDK_PMU_PERF_E_LD_DEV_IO (0x188)
#define BDK_PMU_PERF_E_LD_DEV_MEM (0x18a)
#define BDK_PMU_PERF_E_LD_NORM_IO (0x184)
#define BDK_PMU_PERF_E_LD_NORM_MEM (0x186)
#define BDK_PMU_PERF_E_LD_RETIRED (6)
#define BDK_PMU_PERF_E_LD_SPEC (0x70)
#define BDK_PMU_PERF_E_LL_CACHE (0x32)
#define BDK_PMU_PERF_E_LL_CACHE_MISS (0x33)
#define BDK_PMU_PERF_E_LL_CACHE_MISS_RD (0x37)
#define BDK_PMU_PERF_E_LL_CACHE_RD (0x36)
#define BDK_PMU_PERF_E_LOAD_ATOMIC_RETIRED_CYCLES (0x4c22)
#define BDK_PMU_PERF_E_LOAD_ATOMIC_SPEC (0x4c20)
#define BDK_PMU_PERF_E_LOAD_PORT_COLLISION (0x4c24)
#define BDK_PMU_PERF_E_LOAD_PORT_SUCCESS (0x4c25)
#define BDK_PMU_PERF_E_MAF_ENTRIES_CREATED_COUNT_ONE (0x4c29)
#define BDK_PMU_PERF_E_MAF_ENTRIES_CREATED_COUNT_TWOPLUS (0x4c2a)
#define BDK_PMU_PERF_E_MAF_ENTRIES_CREATED_COUNT_ZERO (0x4c28)
#define BDK_PMU_PERF_E_MEMORY_ERROR (0x1a)
#define BDK_PMU_PERF_E_MEM_ACCESS (0x13)
#define BDK_PMU_PERF_E_MEM_ACCESS_LD (0x66)
#define BDK_PMU_PERF_E_MEM_ACCESS_ST (0x67)
#define BDK_PMU_PERF_E_MOV_REMOVED (0x4c12)
#define BDK_PMU_PERF_E_MSR_HAZTR (0xe8)
#define BDK_PMU_PERF_E_NISSUE (0xc2)
#define BDK_PMU_PERF_E_NO_INFLIGHT_MEMORY_MICROOP_CYCLES (0x4c43)
#define BDK_PMU_PERF_E_NO_INFLIGHT_MICROOP_CYCLES (0x4c42)
#define BDK_PMU_PERF_E_NO_PHYSICAL_REGISTER_CYCLES (0x4c2c)
#define BDK_PMU_PERF_E_NO_RBUF_MAF_ENTRY_CYCLES (0xe5)
#define BDK_PMU_PERF_E_NO_WBUF_MAF_ENTRY_CYCLES (0xde)
#define BDK_PMU_PERF_E_NUM_ERET (0x4c38)
#define BDK_PMU_PERF_E_NUM_INTERRUPT (0x4c37)
#define BDK_PMU_PERF_E_ORDER_VIOLATION_REPLAY (0x4c1d)
#define BDK_PMU_PERF_E_PC_WRITE_RETIRED (0xc)
#define BDK_PMU_PERF_E_PIPE0_NOISSUE (0x4c15)
#define BDK_PMU_PERF_E_PIPE1_NOISSUE (0x4c16)
#define BDK_PMU_PERF_E_PIPE2_NOISSUE (0x4c17)
#define BDK_PMU_PERF_E_PIPE3_NOISSUE (0x4c18)
#define BDK_PMU_PERF_E_PIPE4_NOISSUE (0x4c19)
#define BDK_PMU_PERF_E_PISSUE (0x4c2f)
#define BDK_PMU_PERF_E_PTW_CYCLES (0x193)
#define BDK_PMU_PERF_E_QISSUE (0x4c2e)
#define BDK_PMU_PERF_E_RC_LD_SPEC (0x90)
#define BDK_PMU_PERF_E_RC_ST_SPEC (0x91)
#define BDK_PMU_PERF_E_REMOTE_ACCESS (0x31)
#define BDK_PMU_PERF_E_REMOTE_ACCESS_RD (0x38)
#define BDK_PMU_PERF_E_REPLAY (0xcb)
#define BDK_PMU_PERF_E_RESERVED_00E6 (0xe6)
#define BDK_PMU_PERF_E_RESERVED_0180 (0x180)
#define BDK_PMU_PERF_E_RESERVED_0181 (0x181)
#define BDK_PMU_PERF_E_RESERVED_0182 (0x182)
#define BDK_PMU_PERF_E_RESERVED_0183 (0x183)
#define BDK_PMU_PERF_E_RESERVED_0194 (0x194)
#define BDK_PMU_PERF_E_RESERVED_0195 (0x195)
#define BDK_PMU_PERF_E_RESERVED_0196 (0x196)
#define BDK_PMU_PERF_E_RESERVED_0197 (0x197)
#define BDK_PMU_PERF_E_RESERVED_0198 (0x198)
#define BDK_PMU_PERF_E_RESERVED_0199 (0x199)
#define BDK_PMU_PERF_E_RESERVED_019A (0x19a)
#define BDK_PMU_PERF_E_RESERVED_019B (0x19b)
#define BDK_PMU_PERF_E_RESERVED_019C (0x19c)
#define BDK_PMU_PERF_E_RESERVED_019D (0x19d)
#define BDK_PMU_PERF_E_RESERVED_01A6 (0x1a6)
#define BDK_PMU_PERF_E_RESERVED_01A7 (0x1a7)
#define BDK_PMU_PERF_E_RESERVED_01A8 (0x1a8)
#define BDK_PMU_PERF_E_RESERVED_01A9 (0x1a9)
#define BDK_PMU_PERF_E_RESERVED_01AA (0x1aa)
#define BDK_PMU_PERF_E_RESERVED_01AB (0x1ab)
#define BDK_PMU_PERF_E_RESERVED_01AC (0x1ac)
#define BDK_PMU_PERF_E_RESERVED_01AD (0x1ad)
#define BDK_PMU_PERF_E_RESERVED_01AE (0x1ae)
#define BDK_PMU_PERF_E_RESERVED_01AF (0x1af)
#define BDK_PMU_PERF_E_RESERVED_4C1A (0x4c1a)
#define BDK_PMU_PERF_E_RESERVED_4C1B (0x4c1b)
#define BDK_PMU_PERF_E_RESERVED_4C1C (0x4c1c)
#define BDK_PMU_PERF_E_RESERVED_4C1E (0x4c1e)
#define BDK_PMU_PERF_E_RESERVED_4C2B (0x4c2b)
#define BDK_PMU_PERF_E_RESERVED_4D00X(a) (0x4d00 + (a))
#define BDK_PMU_PERF_E_RESERVED_4E00X(a) (0x4e00 + (a))
#define BDK_PMU_PERF_E_SAMPLE_COLLISON (0x4003)
#define BDK_PMU_PERF_E_SAMPLE_FEED (0x4001)
#define BDK_PMU_PERF_E_SAMPLE_FILTRATE (0x4002)
#define BDK_PMU_PERF_E_SAMPLE_POP (0x4000)
#define BDK_PMU_PERF_E_SEV (0x1b9)
#define BDK_PMU_PERF_E_SISSUE (0xc3)
#define BDK_PMU_PERF_E_STALL_BACKEND (0x24)
#define BDK_PMU_PERF_E_STALL_FRONTEND (0x23)
#define BDK_PMU_PERF_E_STORE_ATOMIC_SPEC (0x4c21)
#define BDK_PMU_PERF_E_STREX_FAIL_SPEC (0x6e)
#define BDK_PMU_PERF_E_STREX_PASS_SPEC (0x6d)
#define BDK_PMU_PERF_E_STX (0x1fa)
#define BDK_PMU_PERF_E_STX_FAIL (0x1fb)
#define BDK_PMU_PERF_E_ST_DEV_IO (0x189)
#define BDK_PMU_PERF_E_ST_DEV_MEM (0x18b)
#define BDK_PMU_PERF_E_ST_NORM_IO (0x185)
#define BDK_PMU_PERF_E_ST_NORM_MEM (0x187)
#define BDK_PMU_PERF_E_ST_RETIRED (7)
#define BDK_PMU_PERF_E_ST_SPEC (0x71)
#define BDK_PMU_PERF_E_SWP_SPEC (0x4c39)
#define BDK_PMU_PERF_E_SW_INCR (0)
#define BDK_PMU_PERF_E_THROTTLE_OFF (0xef)
#define BDK_PMU_PERF_E_TISSUE (0x4c2d)
#define BDK_PMU_PERF_E_TLBI_ALLE1 (0x1c6)
#define BDK_PMU_PERF_E_TLBI_ALLE1IS (0x1c7)
#define BDK_PMU_PERF_E_TLBI_ALLE2 (0x1c8)
#define BDK_PMU_PERF_E_TLBI_ALLE2IS (0x1c9)
#define BDK_PMU_PERF_E_TLBI_ALLE3 (0x1ca)
#define BDK_PMU_PERF_E_TLBI_ALLE3IS (0x1cb)
#define BDK_PMU_PERF_E_TLBI_ASIDE1 (0x1cc)
#define BDK_PMU_PERF_E_TLBI_ASIDE1IS (0x1cd)
#define BDK_PMU_PERF_E_TLBI_IPAS2E1 (0x1ce)
#define BDK_PMU_PERF_E_TLBI_IPAS2E1IS (0x1cf)
#define BDK_PMU_PERF_E_TLBI_IPAS2LE1 (0x1d0)
#define BDK_PMU_PERF_E_TLBI_IPAS2LE1IS (0x1d1)
#define BDK_PMU_PERF_E_TLBI_NOPS (0x1ef)
#define BDK_PMU_PERF_E_TLBI_RCVD (0x1c5)
#define BDK_PMU_PERF_E_TLBI_SENT (0x1c4)
#define BDK_PMU_PERF_E_TLBI_VAAE1 (0x1d2)
#define BDK_PMU_PERF_E_TLBI_VAAE1IS (0x1d3)
#define BDK_PMU_PERF_E_TLBI_VAALE1 (0x1d4)
#define BDK_PMU_PERF_E_TLBI_VAALE1IS (0x1d5)
#define BDK_PMU_PERF_E_TLBI_VAE1 (0x1d6)
#define BDK_PMU_PERF_E_TLBI_VAE1IS (0x1d7)
#define BDK_PMU_PERF_E_TLBI_VAE2 (0x1d8)
#define BDK_PMU_PERF_E_TLBI_VAE2IS (0x1d9)
#define BDK_PMU_PERF_E_TLBI_VAE3 (0x1da)
#define BDK_PMU_PERF_E_TLBI_VAE3IS (0x1db)
#define BDK_PMU_PERF_E_TLBI_VALE1 (0x1dc)
#define BDK_PMU_PERF_E_TLBI_VALE1IS (0x1dd)
#define BDK_PMU_PERF_E_TLBI_VALE2 (0x1de)
#define BDK_PMU_PERF_E_TLBI_VALE2IS (0x1df)
#define BDK_PMU_PERF_E_TLBI_VALE3 (0x1e0)
#define BDK_PMU_PERF_E_TLBI_VALE3IS (0x1e1)
#define BDK_PMU_PERF_E_TLBI_VMALLE1 (0x1e2)
#define BDK_PMU_PERF_E_TLBI_VMALLE1IS (0x1e3)
#define BDK_PMU_PERF_E_TLBI_VMALLS12E1 (0x1e4)
#define BDK_PMU_PERF_E_TLBI_VMALLS12E1IS (0x1e5)
#define BDK_PMU_PERF_E_TLB_REFILL_TTBR0_ELX (0x18c)
#define BDK_PMU_PERF_E_TLB_REFILL_TTBR1_ELX (0x18d)
#define BDK_PMU_PERF_E_TLB_REFILL_VTTBR_EL2 (0x18e)
#define BDK_PMU_PERF_E_TRAP (0xcd)
#define BDK_PMU_PERF_E_TRAP_REASONX(a) (0x4f00 + (a))
#define BDK_PMU_PERF_E_TTBR_WRITE_RETIRED (0x1c)
#define BDK_PMU_PERF_E_ULOAD (0xce)
#define BDK_PMU_PERF_E_UNALIGNED_FLOW_ALIGNED (0x4c1f)
#define BDK_PMU_PERF_E_UNALIGNED_FLOW_UNALIGNED (0x4c41)
#define BDK_PMU_PERF_E_UNALIGNED_LDST_RETIRED (0xf)
#define BDK_PMU_PERF_E_UNALIGNED_LDST_SPEC (0x6a)
#define BDK_PMU_PERF_E_UNALIGNED_LD_RETIRED (0xce)
#define BDK_PMU_PERF_E_UNALIGNED_LD_SPEC (0x68)
#define BDK_PMU_PERF_E_UNALIGNED_REPLAY (0xcc)
#define BDK_PMU_PERF_E_UNALIGNED_ST_RETIRED (0xcf)
#define BDK_PMU_PERF_E_UNALIGNED_ST_SPEC (0x69)
#define BDK_PMU_PERF_E_USTORE (0xcf)
#define BDK_PMU_PERF_E_VFP_SPEC (0x75)
#define BDK_PMU_PERF_E_VMID_OVF (0x301)
#define BDK_PMU_PERF_E_WBUF (0xdb)
#define BDK_PMU_PERF_E_WBUFFL (0xde)
#define BDK_PMU_PERF_E_WBUFLD (0xdd)
#define BDK_PMU_PERF_E_WBUFTR (0xdf)
#define BDK_PMU_PERF_E_WDAT (0xdc)
#define BDK_PMU_PERF_E_WFI_WFE_WAIT_CYCLES (0x4c40)

/**
 * Register (DAB32b) pmu#_pmauthstatus
 *
 * Performance Monitors Authentication Status Register
 * Provides information about the state of the implementation
 * defined authentication interface for performance monitors.
 */
union bdk_pmux_pmauthstatus
{
    uint32_t u;
    struct bdk_pmux_pmauthstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t snid                  : 2;  /**< [  7:  6](RO) Holds the same value as DBGAUTHSTATUS_EL1.SNID. */
        uint32_t reserved_4_5          : 2;
        uint32_t nsnid                 : 2;  /**< [  3:  2](RO) Holds the same value as DBGAUTHSTATUS_EL1.NSNID. */
        uint32_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_1          : 2;
        uint32_t nsnid                 : 2;  /**< [  3:  2](RO) Holds the same value as DBGAUTHSTATUS_EL1.NSNID. */
        uint32_t reserved_4_5          : 2;
        uint32_t snid                  : 2;  /**< [  7:  6](RO) Holds the same value as DBGAUTHSTATUS_EL1.SNID. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmauthstatus_s cn; */
};
typedef union bdk_pmux_pmauthstatus bdk_pmux_pmauthstatus_t;

static inline uint64_t BDK_PMUX_PMAUTHSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMAUTHSTATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fb8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fb8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fb8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fb8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMAUTHSTATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMAUTHSTATUS(a) bdk_pmux_pmauthstatus_t
#define bustype_BDK_PMUX_PMAUTHSTATUS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMAUTHSTATUS(a) "PMUX_PMAUTHSTATUS"
#define busnum_BDK_PMUX_PMAUTHSTATUS(a) (a)
#define arguments_BDK_PMUX_PMAUTHSTATUS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmccfiltr_el0
 *
 * Performance Monitors Cycle Counter Filter Register
 * Determines the modes in which the cycle counter, PMU()_PMCCNTR_EL0,
 *     increments.
 */
union bdk_pmux_pmccfiltr_el0
{
    uint32_t u;
    struct bdk_pmux_pmccfiltr_el0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count cycles in EL1.
                                                                 1 = Do not count cycles in EL1. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count cycles in EL0.
                                                                 1 = Do not count cycles in EL0. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, cycles in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, cycles in nonsecure EL1 are not counted. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, cycles in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, cycles in nonsecure EL0 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count cycles in EL2.
                                                                 1 = Count cycles in EL2. */
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, cycles in
                                                                     secure EL3 are counted.
                                                                 Otherwise, cycles in secure EL3 are not counted. */
        uint32_t reserved_0_25         : 26;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_25         : 26;
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, cycles in
                                                                     secure EL3 are counted.
                                                                 Otherwise, cycles in secure EL3 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count cycles in EL2.
                                                                 1 = Count cycles in EL2. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, cycles in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, cycles in nonsecure EL0 are not counted. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, cycles in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, cycles in nonsecure EL1 are not counted. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count cycles in EL0.
                                                                 1 = Do not count cycles in EL0. */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count cycles in EL1.
                                                                 1 = Do not count cycles in EL1. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmccfiltr_el0_s cn; */
};
typedef union bdk_pmux_pmccfiltr_el0 bdk_pmux_pmccfiltr_el0_t;

static inline uint64_t BDK_PMUX_PMCCFILTR_EL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCCFILTR_EL0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a00802047cll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a00802047cll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a00802047cll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a00802047cll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCCFILTR_EL0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCCFILTR_EL0(a) bdk_pmux_pmccfiltr_el0_t
#define bustype_BDK_PMUX_PMCCFILTR_EL0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCCFILTR_EL0(a) "PMUX_PMCCFILTR_EL0"
#define busnum_BDK_PMUX_PMCCFILTR_EL0(a) (a)
#define arguments_BDK_PMUX_PMCCFILTR_EL0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmccntr_el0_hi
 *
 * Performance Monitors Cycle Counter High Register
 * Holds the value of the processor cycle counter, CCNT, that counts processor clock cycles.
 */
union bdk_pmux_pmccntr_el0_hi
{
    uint32_t u;
    struct bdk_pmux_pmccntr_el0_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t value                 : 32; /**< [ 31:  0](R/W) Cycle count. Depending on the values of PMU()_PMCR_EL0[LC,D], the cycle count
                                                                 increments in one of the following ways:
                                                                 * Every processor clock cycle.
                                                                 * Every 64th processor clock cycle.
                                                                 The cycle count can be reset to zero by writing 1 to PMU()_PMCR_EL0[C]. */
#else /* Word 0 - Little Endian */
        uint32_t value                 : 32; /**< [ 31:  0](R/W) Cycle count. Depending on the values of PMU()_PMCR_EL0[LC,D], the cycle count
                                                                 increments in one of the following ways:
                                                                 * Every processor clock cycle.
                                                                 * Every 64th processor clock cycle.
                                                                 The cycle count can be reset to zero by writing 1 to PMU()_PMCR_EL0[C]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmccntr_el0_hi_s cn; */
};
typedef union bdk_pmux_pmccntr_el0_hi bdk_pmux_pmccntr_el0_hi_t;

static inline uint64_t BDK_PMUX_PMCCNTR_EL0_HI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCCNTR_EL0_HI(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a0080200fcll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a0080200fcll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a0080200fcll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a0080200fcll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCCNTR_EL0_HI", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCCNTR_EL0_HI(a) bdk_pmux_pmccntr_el0_hi_t
#define bustype_BDK_PMUX_PMCCNTR_EL0_HI(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCCNTR_EL0_HI(a) "PMUX_PMCCNTR_EL0_HI"
#define busnum_BDK_PMUX_PMCCNTR_EL0_HI(a) (a)
#define arguments_BDK_PMUX_PMCCNTR_EL0_HI(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmccntr_el0_lo
 *
 * Performance Monitors Cycle Counter Low Register
 * Holds the value of the processor cycle counter, CCNT, that counts processor clock cycles.
 */
union bdk_pmux_pmccntr_el0_lo
{
    uint32_t u;
    struct bdk_pmux_pmccntr_el0_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t value                 : 32; /**< [ 31:  0](R/W) Cycle count. Depending on the values of PMU()_PMCR_EL0[LC,D], the cycle count
                                                                 increments in one of the following ways:
                                                                 * Every processor clock cycle.
                                                                 * Every 64th processor clock cycle.
                                                                 The cycle count can be reset to zero by writing 1 to PMU()_PMCR_EL0[C]. */
#else /* Word 0 - Little Endian */
        uint32_t value                 : 32; /**< [ 31:  0](R/W) Cycle count. Depending on the values of PMU()_PMCR_EL0[LC,D], the cycle count
                                                                 increments in one of the following ways:
                                                                 * Every processor clock cycle.
                                                                 * Every 64th processor clock cycle.
                                                                 The cycle count can be reset to zero by writing 1 to PMU()_PMCR_EL0[C]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmccntr_el0_lo_s cn; */
};
typedef union bdk_pmux_pmccntr_el0_lo bdk_pmux_pmccntr_el0_lo_t;

static inline uint64_t BDK_PMUX_PMCCNTR_EL0_LO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCCNTR_EL0_LO(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a0080200f8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a0080200f8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a0080200f8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a0080200f8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCCNTR_EL0_LO", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCCNTR_EL0_LO(a) bdk_pmux_pmccntr_el0_lo_t
#define bustype_BDK_PMUX_PMCCNTR_EL0_LO(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCCNTR_EL0_LO(a) "PMUX_PMCCNTR_EL0_LO"
#define busnum_BDK_PMUX_PMCCNTR_EL0_LO(a) (a)
#define arguments_BDK_PMUX_PMCCNTR_EL0_LO(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmceid0
 *
 * Performance Monitors Common Event Identification Register 0
 * Defines which common architectural and common
 *     microarchitectural feature events are implemented. If a
 *     particular bit is set to one, then the event for that bit is
 *     implemented. Alias for PMU()_PMCEID1_EL0[31:0].
 */
union bdk_pmux_pmceid0
{
    uint32_t u;
    struct bdk_pmux_pmceid0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RO) Common architectural and microarchitectural feature events that can be counted
                                                                 by the PMU event counters.

                                                                 In CNXXXX, the following bits are set to indicate the corresponding events are
                                                                 implemented:
                                                                   30 = 0x001e = CHAIN.
                                                                   28 = 0x001c = TTBR_WRITE_RETIRED.
                                                                   27 = 0x001b = INST_SPEC.
                                                                   26 = 0x001a = MEMORY_ERROR.
                                                                   24 = 0x0018 = L2D_CACHE_WB.
                                                                   23 = 0x0017 = L2D_CACHE_REFILL.
                                                                   22 = 0x0016 = L2D_CACHE.
                                                                   20 = 0x0014 = L1I_CACHE.
                                                                   19 = 0x0013 = MEM_ACCESS.
                                                                   18 = 0x0012 = BR_PRED.
                                                                   17 = 0x0011 = CPU_CYCLES.
                                                                   16 = 0x0010 = BR_MIS_PRED.
                                                                   15 = 0x000f = UNALIGNED_LDST_RETIRED.
                                                                   14 = 0x000e = BR_RETURN_RETIRED.
                                                                   13 = 0x000d = BR_IMMED_RETIRED.
                                                                   12 = 0x000c = PC_WRITE_RETIRED.
                                                                   11 = 0x000b = CID_WRITE_RETIRED.
                                                                   10 = 0x000a = EXC_RETURN.
                                                                    9 = 0x0009 = EXC_TAKEN.
                                                                    8 = 0x0008 = INST_RETIRED.
                                                                    7 = 0x0007 = ST_RETIRED.
                                                                    6 = 0x0006 = LD_RETIRED.
                                                                    5 = 0x0005 = L1D_TLB_REFILL.
                                                                    4 = 0x0004 = L1D_CACHE.
                                                                    3 = 0x0003 = L1D_CACHE_REFILL.
                                                                    2 = 0x0002 = L1I_TLB_REFILL.
                                                                    1 = 0x0001 = L1I_CACHE_REFILL.
                                                                    0 = 0x0000 = SW_INCR. */
#else /* Word 0 - Little Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RO) Common architectural and microarchitectural feature events that can be counted
                                                                 by the PMU event counters.

                                                                 In CNXXXX, the following bits are set to indicate the corresponding events are
                                                                 implemented:
                                                                   30 = 0x001e = CHAIN.
                                                                   28 = 0x001c = TTBR_WRITE_RETIRED.
                                                                   27 = 0x001b = INST_SPEC.
                                                                   26 = 0x001a = MEMORY_ERROR.
                                                                   24 = 0x0018 = L2D_CACHE_WB.
                                                                   23 = 0x0017 = L2D_CACHE_REFILL.
                                                                   22 = 0x0016 = L2D_CACHE.
                                                                   20 = 0x0014 = L1I_CACHE.
                                                                   19 = 0x0013 = MEM_ACCESS.
                                                                   18 = 0x0012 = BR_PRED.
                                                                   17 = 0x0011 = CPU_CYCLES.
                                                                   16 = 0x0010 = BR_MIS_PRED.
                                                                   15 = 0x000f = UNALIGNED_LDST_RETIRED.
                                                                   14 = 0x000e = BR_RETURN_RETIRED.
                                                                   13 = 0x000d = BR_IMMED_RETIRED.
                                                                   12 = 0x000c = PC_WRITE_RETIRED.
                                                                   11 = 0x000b = CID_WRITE_RETIRED.
                                                                   10 = 0x000a = EXC_RETURN.
                                                                    9 = 0x0009 = EXC_TAKEN.
                                                                    8 = 0x0008 = INST_RETIRED.
                                                                    7 = 0x0007 = ST_RETIRED.
                                                                    6 = 0x0006 = LD_RETIRED.
                                                                    5 = 0x0005 = L1D_TLB_REFILL.
                                                                    4 = 0x0004 = L1D_CACHE.
                                                                    3 = 0x0003 = L1D_CACHE_REFILL.
                                                                    2 = 0x0002 = L1I_TLB_REFILL.
                                                                    1 = 0x0001 = L1I_CACHE_REFILL.
                                                                    0 = 0x0000 = SW_INCR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmceid0_s cn; */
};
typedef union bdk_pmux_pmceid0 bdk_pmux_pmceid0_t;

static inline uint64_t BDK_PMUX_PMCEID0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCEID0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020e20ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020e20ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020e20ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020e20ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCEID0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCEID0(a) bdk_pmux_pmceid0_t
#define bustype_BDK_PMUX_PMCEID0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCEID0(a) "PMUX_PMCEID0"
#define busnum_BDK_PMUX_PMCEID0(a) (a)
#define arguments_BDK_PMUX_PMCEID0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmceid1
 *
 * Performance Monitors Common Event Identification Register 1
 * Reserved for future indication of which common architectural
 *     and common microarchitectural feature events are implemented.
 *     These events are in the range 0x20-0x3f.
 *     Alias for PMU()_PMCEID1_EL0[31:0].
 */
union bdk_pmux_pmceid1
{
    uint32_t u;
    struct bdk_pmux_pmceid1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RO) Common architectural and microarchitectural feature events that can be counted
                                                                 by the PMU event counters.

                                                                 In CNXXXX, the following bits are set to indicate the corresponding events are
                                                                 implemented:
                                                                   15 = 0x002f = L2D_TLB.
                                                                   14 = 0x002e = L2I_TLB_REFILL.
                                                                   13 = 0x002d = L2D_TLB_REFILL.
                                                                   8  = 0x0028 = L2I_CACHE_REFILL.
                                                                   7  = 0x0027 = L2I_CACHE.
                                                                   6  = 0x0026 = L1I_TLB.
                                                                   5  = 0x0025 = L1D_TLB.
                                                                   4  = 0x0024 = STALL_BACKEND.
                                                                   3  = 0x0023 = STALL_FRONTEND.
                                                                   2  = 0x0022 = BR_MIS_PRED_RETIRED.
                                                                   1  = 0x0021 = BR_RETIRED. */
#else /* Word 0 - Little Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RO) Common architectural and microarchitectural feature events that can be counted
                                                                 by the PMU event counters.

                                                                 In CNXXXX, the following bits are set to indicate the corresponding events are
                                                                 implemented:
                                                                   15 = 0x002f = L2D_TLB.
                                                                   14 = 0x002e = L2I_TLB_REFILL.
                                                                   13 = 0x002d = L2D_TLB_REFILL.
                                                                   8  = 0x0028 = L2I_CACHE_REFILL.
                                                                   7  = 0x0027 = L2I_CACHE.
                                                                   6  = 0x0026 = L1I_TLB.
                                                                   5  = 0x0025 = L1D_TLB.
                                                                   4  = 0x0024 = STALL_BACKEND.
                                                                   3  = 0x0023 = STALL_FRONTEND.
                                                                   2  = 0x0022 = BR_MIS_PRED_RETIRED.
                                                                   1  = 0x0021 = BR_RETIRED. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmceid1_s cn8; */
    struct bdk_pmux_pmceid1_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RO) Common architectural and microarchitectural feature events that can be counted
                                                                 by the PMU event counters.

                                                                 In CNXXXX, the following bits are set to indicate the corresponding events are
                                                                 implemented:
                                                                   23 = 0X0038 = REMOTE_ACCESS_RD.
                                                                   22 = 0X0037 = LL_CACHE_MISS_RD.
                                                                   21 = 0X0036 = LL_CACHE_RD.
                                                                   20 = 0X0035 = ITLB_WALK.
                                                                   19 = 0X0034 = DTLB_WALK.
                                                                   18 = 0X0033 = LL_CACHE MISS.
                                                                   17 = 0X0032 = LL_CACHE.
                                                                   16 = 0X0031 = REMOTE_ACCESS.
                                                                   15 = 0x002f = L2D_TLB.
                                                                   14 = 0x002e = L2I_TLB_REFILL.
                                                                   13 = 0x002d = L2D_TLB_REFILL.
                                                                   8  = 0x0028 = L2I_CACHE_REFILL.
                                                                   7  = 0x0027 = L2I_CACHE.
                                                                   6  = 0x0026 = L1I_TLB.
                                                                   5  = 0x0025 = L1D_TLB.
                                                                   4  = 0x0024 = STALL_BACKEND.
                                                                   3  = 0x0023 = STALL_FRONTEND.
                                                                   2  = 0x0022 = BR_MIS_PRED_RETIRED.
                                                                   1  = 0x0021 = BR_RETIRED. */
#else /* Word 0 - Little Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RO) Common architectural and microarchitectural feature events that can be counted
                                                                 by the PMU event counters.

                                                                 In CNXXXX, the following bits are set to indicate the corresponding events are
                                                                 implemented:
                                                                   23 = 0X0038 = REMOTE_ACCESS_RD.
                                                                   22 = 0X0037 = LL_CACHE_MISS_RD.
                                                                   21 = 0X0036 = LL_CACHE_RD.
                                                                   20 = 0X0035 = ITLB_WALK.
                                                                   19 = 0X0034 = DTLB_WALK.
                                                                   18 = 0X0033 = LL_CACHE MISS.
                                                                   17 = 0X0032 = LL_CACHE.
                                                                   16 = 0X0031 = REMOTE_ACCESS.
                                                                   15 = 0x002f = L2D_TLB.
                                                                   14 = 0x002e = L2I_TLB_REFILL.
                                                                   13 = 0x002d = L2D_TLB_REFILL.
                                                                   8  = 0x0028 = L2I_CACHE_REFILL.
                                                                   7  = 0x0027 = L2I_CACHE.
                                                                   6  = 0x0026 = L1I_TLB.
                                                                   5  = 0x0025 = L1D_TLB.
                                                                   4  = 0x0024 = STALL_BACKEND.
                                                                   3  = 0x0023 = STALL_FRONTEND.
                                                                   2  = 0x0022 = BR_MIS_PRED_RETIRED.
                                                                   1  = 0x0021 = BR_RETIRED. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_pmux_pmceid1 bdk_pmux_pmceid1_t;

static inline uint64_t BDK_PMUX_PMCEID1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCEID1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020e24ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020e24ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020e24ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020e24ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCEID1", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCEID1(a) bdk_pmux_pmceid1_t
#define bustype_BDK_PMUX_PMCEID1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCEID1(a) "PMUX_PMCEID1"
#define busnum_BDK_PMUX_PMCEID1(a) (a)
#define arguments_BDK_PMUX_PMCEID1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmceid2
 *
 * Performance Monitors Common Event Identification Register 2
 * Reserved for future indication of which common architectural
 *     and common microarchitectural feature events are implemented.
 *     These events are in the range 0x4000-0x401f
 *     Alias for PMU()_PMCEID0_EL0[63:32]
 */
union bdk_pmux_pmceid2
{
    uint32_t u;
    struct bdk_pmux_pmceid2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RAZ) Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmceid2_s cn8; */
    struct bdk_pmux_pmceid2_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RO) Common architectural and microarchitectural feature events that can be counted
                                                                 by the PMU event counters.

                                                                 In CNXXXX, the following bits are set to indicate the corresponding events are
                                                                 implemented:
                                                                   3  = 0x4003 = SAMPLE_COLLISION.
                                                                   2  = 0x4002 = SAMPLE_FILTRATE.
                                                                   1  = 0x4001 = SAMPLE_FEED.
                                                                   0  = 0x4000 = SAMPLE_POP. */
#else /* Word 0 - Little Endian */
        uint32_t ce                    : 32; /**< [ 31:  0](RO) Common architectural and microarchitectural feature events that can be counted
                                                                 by the PMU event counters.

                                                                 In CNXXXX, the following bits are set to indicate the corresponding events are
                                                                 implemented:
                                                                   3  = 0x4003 = SAMPLE_COLLISION.
                                                                   2  = 0x4002 = SAMPLE_FILTRATE.
                                                                   1  = 0x4001 = SAMPLE_FEED.
                                                                   0  = 0x4000 = SAMPLE_POP. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_pmux_pmceid2 bdk_pmux_pmceid2_t;

static inline uint64_t BDK_PMUX_PMCEID2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCEID2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020e28ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020e28ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020e28ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020e28ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCEID2", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCEID2(a) bdk_pmux_pmceid2_t
#define bustype_BDK_PMUX_PMCEID2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCEID2(a) "PMUX_PMCEID2"
#define busnum_BDK_PMUX_PMCEID2(a) (a)
#define arguments_BDK_PMUX_PMCEID2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmceid3
 *
 * Performance Monitors Common Event Identification Register 3
 * Reserved for future indication of which common architectural
 *     and common microarchitectural feature events are implemented.
 *     These events are in the range 0x4020-0x403f
 *     Alias for PMU()_PMCEID1_EL0[63:32]
 */
union bdk_pmux_pmceid3
{
    uint32_t u;
    struct bdk_pmux_pmceid3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmceid3_s cn; */
};
typedef union bdk_pmux_pmceid3 bdk_pmux_pmceid3_t;

static inline uint64_t BDK_PMUX_PMCEID3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCEID3(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020e2cll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020e2cll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020e2cll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020e2cll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCEID3", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCEID3(a) bdk_pmux_pmceid3_t
#define bustype_BDK_PMUX_PMCEID3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCEID3(a) "PMUX_PMCEID3"
#define busnum_BDK_PMUX_PMCEID3(a) (a)
#define arguments_BDK_PMUX_PMCEID3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcfgr
 *
 * Performance Monitors Configuration Register
 * Contains PMU-specific configuration data.
 */
union bdk_pmux_pmcfgr
{
    uint32_t u;
    struct bdk_pmux_pmcfgr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t uen                   : 1;  /**< [ 19: 19](RO) User-mode enable register supported. PMUSERENR_EL0 is not
                                                                     visible in the external debug interface, so this bit is RES0. */
        uint32_t wt                    : 1;  /**< [ 18: 18](RO) This feature is not supported, so this bit is RES0. */
        uint32_t na                    : 1;  /**< [ 17: 17](RO) This feature is not supported, so this bit is RES0. */
        uint32_t ex                    : 1;  /**< [ 16: 16](RO) Export supported. Value is implementation defined.
                                                                 0 = PMU()_PMCR_EL0[X] is RES0.
                                                                 1 = PMU()_PMCR_EL0[X] is read/write.

                                                                 Not supported. */
        uint32_t ccd                   : 1;  /**< [ 15: 15](RO) Cycle counter has prescale. This is RES1 if AArch32 is
                                                                     supported at any EL, and RES0 otherwise.
                                                                 0 = PMU()_PMCR_EL0[D] is RES0.
                                                                 1 = PMU()_PMCR_EL0[D] is read/write. */
        uint32_t cc                    : 1;  /**< [ 14: 14](RO) Dedicated cycle counter (counter 31) supported. This bit is
                                                                     RES1. */
        uint32_t size                  : 6;  /**< [ 13:  8](RO) Size of counters. This field determines the spacing of
                                                                     counters in the memory-map.
                                                                 In v8-A the counters are at doubleword-aligned addresses, and
                                                                     the largest counter is 64-bits, so this field is 0x3f. */
        uint32_t n                     : 8;  /**< [  7:  0](RO) Number of counters implemented in addition to the cycle
                                                                     counter, PMU()_PMCCNTR_EL0. The maximum number of event counters is
                                                                     31, so bits[7:5] are always RES0.
                                                                 and so on up to 0x1F PMU()_PMCCNTR_EL0 and 31 event counters
                                                                     implemented.
                                                                 0x0 = Only PMU()_PMCCNTR_EL0 implemented.
                                                                 0x1 = PMU()_PMCCNTR_EL0 plus one event counter implemented. */
#else /* Word 0 - Little Endian */
        uint32_t n                     : 8;  /**< [  7:  0](RO) Number of counters implemented in addition to the cycle
                                                                     counter, PMU()_PMCCNTR_EL0. The maximum number of event counters is
                                                                     31, so bits[7:5] are always RES0.
                                                                 and so on up to 0x1F PMU()_PMCCNTR_EL0 and 31 event counters
                                                                     implemented.
                                                                 0x0 = Only PMU()_PMCCNTR_EL0 implemented.
                                                                 0x1 = PMU()_PMCCNTR_EL0 plus one event counter implemented. */
        uint32_t size                  : 6;  /**< [ 13:  8](RO) Size of counters. This field determines the spacing of
                                                                     counters in the memory-map.
                                                                 In v8-A the counters are at doubleword-aligned addresses, and
                                                                     the largest counter is 64-bits, so this field is 0x3f. */
        uint32_t cc                    : 1;  /**< [ 14: 14](RO) Dedicated cycle counter (counter 31) supported. This bit is
                                                                     RES1. */
        uint32_t ccd                   : 1;  /**< [ 15: 15](RO) Cycle counter has prescale. This is RES1 if AArch32 is
                                                                     supported at any EL, and RES0 otherwise.
                                                                 0 = PMU()_PMCR_EL0[D] is RES0.
                                                                 1 = PMU()_PMCR_EL0[D] is read/write. */
        uint32_t ex                    : 1;  /**< [ 16: 16](RO) Export supported. Value is implementation defined.
                                                                 0 = PMU()_PMCR_EL0[X] is RES0.
                                                                 1 = PMU()_PMCR_EL0[X] is read/write.

                                                                 Not supported. */
        uint32_t na                    : 1;  /**< [ 17: 17](RO) This feature is not supported, so this bit is RES0. */
        uint32_t wt                    : 1;  /**< [ 18: 18](RO) This feature is not supported, so this bit is RES0. */
        uint32_t uen                   : 1;  /**< [ 19: 19](RO) User-mode enable register supported. PMUSERENR_EL0 is not
                                                                     visible in the external debug interface, so this bit is RES0. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcfgr_s cn; */
};
typedef union bdk_pmux_pmcfgr bdk_pmux_pmcfgr_t;

static inline uint64_t BDK_PMUX_PMCFGR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCFGR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020e00ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020e00ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020e00ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020e00ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCFGR", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCFGR(a) bdk_pmux_pmcfgr_t
#define bustype_BDK_PMUX_PMCFGR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCFGR(a) "PMUX_PMCFGR"
#define busnum_BDK_PMUX_PMCFGR(a) (a)
#define arguments_BDK_PMUX_PMCFGR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcid1sr
 *
 * AP CONTEXTIDR_EL1 Sample Register
 * Contains the sampled value of CONTEXTIDR_EL1, captured on
 *     reading the low half of PMPCSR.
 * When DBG()_EDSCR[SC2] is set, if the sampled PC was from nonsecure state and EL2 is using
 * AArch64,
 * PMVIDSR is written with the value of CONTEXTIDR_EL2 associated with the most recent PMPCSR
 * sample.
 * Otherwise, PMVIDSR becomes unknown.
 */
union bdk_pmux_pmcid1sr
{
    uint32_t u;
    struct bdk_pmux_pmcid1sr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t contextidr            : 32; /**< [ 31:  0](RO) The sampled value of CONTEXTIDR_EL1, captured on reading the
                                                                     low half of PMPCSR.
                                                                 If EL3 is implemented and using AArch32 then CONTEXTIDR is a
                                                                     banked register, and PMCID1SR samples the current banked copy
                                                                     of CONTEXTIDR. */
#else /* Word 0 - Little Endian */
        uint32_t contextidr            : 32; /**< [ 31:  0](RO) The sampled value of CONTEXTIDR_EL1, captured on reading the
                                                                     low half of PMPCSR.
                                                                 If EL3 is implemented and using AArch32 then CONTEXTIDR is a
                                                                     banked register, and PMCID1SR samples the current banked copy
                                                                     of CONTEXTIDR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcid1sr_s cn; */
};
typedef union bdk_pmux_pmcid1sr bdk_pmux_pmcid1sr_t;

static inline uint64_t BDK_PMUX_PMCID1SR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCID1SR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020208ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCID1SR", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCID1SR(a) bdk_pmux_pmcid1sr_t
#define bustype_BDK_PMUX_PMCID1SR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCID1SR(a) "PMUX_PMCID1SR"
#define busnum_BDK_PMUX_PMCID1SR(a) (a)
#define arguments_BDK_PMUX_PMCID1SR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcid1sr_alias
 *
 * AP CONTEXTIDR_EL1 Sample Register
 */
union bdk_pmux_pmcid1sr_alias
{
    uint32_t u;
    struct bdk_pmux_pmcid1sr_alias_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t contextidr            : 32; /**< [ 31:  0](RO) The sampled value of CONTEXTIDR_EL1, captured on reading the
                                                                     low half of PMPCSR.
                                                                 If EL3 is implemented and using AArch32 then CONTEXTIDR is a
                                                                     banked register, and PMCID1SR samples the current banked copy
                                                                     of CONTEXTIDR. */
#else /* Word 0 - Little Endian */
        uint32_t contextidr            : 32; /**< [ 31:  0](RO) The sampled value of CONTEXTIDR_EL1, captured on reading the
                                                                     low half of PMPCSR.
                                                                 If EL3 is implemented and using AArch32 then CONTEXTIDR is a
                                                                     banked register, and PMCID1SR samples the current banked copy
                                                                     of CONTEXTIDR. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcid1sr_alias_s cn; */
};
typedef union bdk_pmux_pmcid1sr_alias bdk_pmux_pmcid1sr_alias_t;

static inline uint64_t BDK_PMUX_PMCID1SR_ALIAS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCID1SR_ALIAS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020228ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCID1SR_ALIAS", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCID1SR_ALIAS(a) bdk_pmux_pmcid1sr_alias_t
#define bustype_BDK_PMUX_PMCID1SR_ALIAS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCID1SR_ALIAS(a) "PMUX_PMCID1SR_ALIAS"
#define busnum_BDK_PMUX_PMCID1SR_ALIAS(a) (a)
#define arguments_BDK_PMUX_PMCID1SR_ALIAS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcid2sr
 *
 * AP Virtual Context Sample Register
 * Alias of PMU(0..23)_PMVIDSR
 */
union bdk_pmux_pmcid2sr
{
    uint32_t u;
    struct bdk_pmux_pmcid2sr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t vmid                  : 16; /**< [ 15:  0](RO) VMID sample. The value of VTTBR_EL2[VMID] associated with the
                                                                     most recent PMPCSR sample. If PMVIDSR[NS] = 0 or PMVIDSR[E2] =
                                                                     1, this field is 0x0. When the SC2 bit is set to zero, PMVIDSR[15:0]
                                                                     is extended to sample the 16-bit VMID if VTCR_EL2[VS] is set to one. */
#else /* Word 0 - Little Endian */
        uint32_t vmid                  : 16; /**< [ 15:  0](RO) VMID sample. The value of VTTBR_EL2[VMID] associated with the
                                                                     most recent PMPCSR sample. If PMVIDSR[NS] = 0 or PMVIDSR[E2] =
                                                                     1, this field is 0x0. When the SC2 bit is set to zero, PMVIDSR[15:0]
                                                                     is extended to sample the 16-bit VMID if VTCR_EL2[VS] is set to one. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcid2sr_s cn; */
};
typedef union bdk_pmux_pmcid2sr bdk_pmux_pmcid2sr_t;

static inline uint64_t BDK_PMUX_PMCID2SR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCID2SR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a00802022cll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCID2SR", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCID2SR(a) bdk_pmux_pmcid2sr_t
#define bustype_BDK_PMUX_PMCID2SR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCID2SR(a) "PMUX_PMCID2SR"
#define busnum_BDK_PMUX_PMCID2SR(a) (a)
#define arguments_BDK_PMUX_PMCID2SR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcidr0
 *
 * Performance Monitors Component Identification Register 0
 * This register provides information to identify a debug component.
 */
union bdk_pmux_pmcidr0
{
    uint32_t u;
    struct bdk_pmux_pmcidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcidr0_s cn; */
};
typedef union bdk_pmux_pmcidr0 bdk_pmux_pmcidr0_t;

static inline uint64_t BDK_PMUX_PMCIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCIDR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020ff0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020ff0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020ff0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020ff0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCIDR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCIDR0(a) bdk_pmux_pmcidr0_t
#define bustype_BDK_PMUX_PMCIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCIDR0(a) "PMUX_PMCIDR0"
#define busnum_BDK_PMUX_PMCIDR0(a) (a)
#define arguments_BDK_PMUX_PMCIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcidr1
 *
 * Performance Monitors Component Identification Register 1
 * This register provides information to identify a debug component.
 */
union bdk_pmux_pmcidr1
{
    uint32_t u;
    struct bdk_pmux_pmcidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0x9 = Debug component. */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble identification value. */
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0x9 = Debug component. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcidr1_s cn; */
};
typedef union bdk_pmux_pmcidr1 bdk_pmux_pmcidr1_t;

static inline uint64_t BDK_PMUX_PMCIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCIDR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020ff4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020ff4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020ff4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020ff4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCIDR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCIDR1(a) bdk_pmux_pmcidr1_t
#define bustype_BDK_PMUX_PMCIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCIDR1(a) "PMUX_PMCIDR1"
#define busnum_BDK_PMUX_PMCIDR1(a) (a)
#define arguments_BDK_PMUX_PMCIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcidr2
 *
 * Performance Monitors Component Identification Register 2
 * This register provides information to identify a debug component.
 */
union bdk_pmux_pmcidr2
{
    uint32_t u;
    struct bdk_pmux_pmcidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcidr2_s cn; */
};
typedef union bdk_pmux_pmcidr2 bdk_pmux_pmcidr2_t;

static inline uint64_t BDK_PMUX_PMCIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCIDR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020ff8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020ff8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020ff8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020ff8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCIDR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCIDR2(a) bdk_pmux_pmcidr2_t
#define bustype_BDK_PMUX_PMCIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCIDR2(a) "PMUX_PMCIDR2"
#define busnum_BDK_PMUX_PMCIDR2(a) (a)
#define arguments_BDK_PMUX_PMCIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcidr3
 *
 * Performance Monitors Component Identification Register 3
 * This register provides information to identify a debug component.
 */
union bdk_pmux_pmcidr3
{
    uint32_t u;
    struct bdk_pmux_pmcidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcidr3_s cn; */
};
typedef union bdk_pmux_pmcidr3 bdk_pmux_pmcidr3_t;

static inline uint64_t BDK_PMUX_PMCIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCIDR3(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020ffcll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020ffcll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020ffcll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020ffcll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCIDR3", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCIDR3(a) bdk_pmux_pmcidr3_t
#define bustype_BDK_PMUX_PMCIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCIDR3(a) "PMUX_PMCIDR3"
#define busnum_BDK_PMUX_PMCIDR3(a) (a)
#define arguments_BDK_PMUX_PMCIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcntenclr_el0
 *
 * Performance Monitors Count Enable Clear Register
 * Disables the cycle count register, PMU()_PMCCNTR_EL0, and any
 *     implemented event counters PMEVCNTR\<x\>. Reading this register
 *     shows which counters are enabled.
 */
union bdk_pmux_pmcntenclr_el0
{
    uint32_t u;
    struct bdk_pmux_pmcntenclr_el0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 disable bit. Disables the cycle counter register.
                                                                     Possible values are:
                                                                 0 = When read, means the cycle counter is disabled. When written,
                                                                     has no effect.
                                                                 1 = When read, means the cycle counter is enabled. When written,
                                                                     disables the cycle counter. */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter disable bit for PMEVCNTR\<x\>.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values of each bit are:
                                                                 0 = When read, means that PMEVCNTR\<x\> is disabled. When written,
                                                                     has no effect.
                                                                 1 = When read, means that PMEVCNTR\<x\> is enabled. When written,
                                                                     disables PMEVCNTR\<x\>. */
#else /* Word 0 - Little Endian */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter disable bit for PMEVCNTR\<x\>.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values of each bit are:
                                                                 0 = When read, means that PMEVCNTR\<x\> is disabled. When written,
                                                                     has no effect.
                                                                 1 = When read, means that PMEVCNTR\<x\> is enabled. When written,
                                                                     disables PMEVCNTR\<x\>. */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 disable bit. Disables the cycle counter register.
                                                                     Possible values are:
                                                                 0 = When read, means the cycle counter is disabled. When written,
                                                                     has no effect.
                                                                 1 = When read, means the cycle counter is enabled. When written,
                                                                     disables the cycle counter. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcntenclr_el0_s cn; */
};
typedef union bdk_pmux_pmcntenclr_el0 bdk_pmux_pmcntenclr_el0_t;

static inline uint64_t BDK_PMUX_PMCNTENCLR_EL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCNTENCLR_EL0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020c20ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020c20ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020c20ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020c20ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCNTENCLR_EL0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCNTENCLR_EL0(a) bdk_pmux_pmcntenclr_el0_t
#define bustype_BDK_PMUX_PMCNTENCLR_EL0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCNTENCLR_EL0(a) "PMUX_PMCNTENCLR_EL0"
#define busnum_BDK_PMUX_PMCNTENCLR_EL0(a) (a)
#define arguments_BDK_PMUX_PMCNTENCLR_EL0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcntenset_el0
 *
 * Performance Monitors Count Enable Set Register
 * Enables the cycle count register, PMU()_PMCCNTR_EL0, and any
 *     implemented event counters PMEVCNTR\<x\>. Reading this register
 *     shows which counters are enabled.
 */
union bdk_pmux_pmcntenset_el0
{
    uint32_t u;
    struct bdk_pmux_pmcntenset_el0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 enable bit. Enables the cycle counter register.
                                                                     Possible values are:
                                                                 0 = When read, means the cycle counter is disabled. When written,
                                                                     has no effect.
                                                                 1 = When read, means the cycle counter is enabled. When written,
                                                                     enables the cycle counter. */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter enable bit for PMEVCNTR\<x\>.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values of each bit are:
                                                                 0 = When read, means that PMEVCNTR\<x\> is disabled. When written,
                                                                     has no effect.
                                                                 1 = When read, means that PMEVCNTR\<x\> event counter is enabled.
                                                                     When written, enables PMEVCNTR\<x\>. */
#else /* Word 0 - Little Endian */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter enable bit for PMEVCNTR\<x\>.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values of each bit are:
                                                                 0 = When read, means that PMEVCNTR\<x\> is disabled. When written,
                                                                     has no effect.
                                                                 1 = When read, means that PMEVCNTR\<x\> event counter is enabled.
                                                                     When written, enables PMEVCNTR\<x\>. */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 enable bit. Enables the cycle counter register.
                                                                     Possible values are:
                                                                 0 = When read, means the cycle counter is disabled. When written,
                                                                     has no effect.
                                                                 1 = When read, means the cycle counter is enabled. When written,
                                                                     enables the cycle counter. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmcntenset_el0_s cn; */
};
typedef union bdk_pmux_pmcntenset_el0 bdk_pmux_pmcntenset_el0_t;

static inline uint64_t BDK_PMUX_PMCNTENSET_EL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCNTENSET_EL0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020c00ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020c00ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020c00ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020c00ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCNTENSET_EL0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCNTENSET_EL0(a) bdk_pmux_pmcntenset_el0_t
#define bustype_BDK_PMUX_PMCNTENSET_EL0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCNTENSET_EL0(a) "PMUX_PMCNTENSET_EL0"
#define busnum_BDK_PMUX_PMCNTENSET_EL0(a) (a)
#define arguments_BDK_PMUX_PMCNTENSET_EL0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmcr_el0
 *
 * Performance Monitors Control Register
 * Provides details of the performance monitors implementation,
 *     including the number of counters implemented, and configures
 *     and controls the counters.
 */
union bdk_pmux_pmcr_el0
{
    uint32_t u;
    struct bdk_pmux_pmcr_el0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_7_31         : 25;
        uint32_t lc                    : 1;  /**< [  6:  6](R/W) Long cycle counter enable. Determines which PMU()_PMCCNTR_EL0 bit
                                                                     generates an overflow recorded by PMOVSR[31].
                                                                 ARM deprecates use of PMU()_PMCR_EL0[LC] = 0.
                                                                 0 = Cycle counter overflow on increment that changes
                                                                     PMU()_PMCCNTR_EL0[31] from one to zero.
                                                                 1 = Cycle counter overflow on increment that changes
                                                                     PMU()_PMCCNTR_EL0[63] from one to zero. */
        uint32_t dp                    : 1;  /**< [  5:  5](R/W) Disable cycle counter when event counting is prohibited. The
                                                                     possible values of this bit are:
                                                                 Event counting is prohibited when
                                                                     ProfilingProhibited(IsSecure(),PSTATE.EL) == TRUE. See the
                                                                     "Performance Monitors and Security" section of the ARMv8 Debug
                                                                     Specification, PRD03-PRDC-010486.
                                                                 This bit is RW.
                                                                 0 =  PMU()_PMCCNTR_EL0, if enabled, counts when event counting is
                                                                     prohibited.
                                                                 1 =  PMU()_PMCCNTR_EL0 does not count when event counting is prohibited. */
        uint32_t x                     : 1;  /**< [  4:  4](R/W) Enable export of events in an implementation defined event
                                                                     stream. The possible values of this bit are:
                                                                 This bit is used to permit events to be exported to another
                                                                     debug device, such as an OPTIONAL trace extension, over an
                                                                     event bus. If the implementation does not include such an
                                                                     event bus, this bit is RAZ/WI.
                                                                 This bit does not affect the generation of performance
                                                                     monitors overflow interrupt requests or signaling to a cross
                                                                     trigger interface (CTI) that can be implemented as signals
                                                                     exported from the processor.
                                                                 If the implementation does not include an exported event
                                                                     stream, this bit is RAZ/WI. Otherwise this bit is RW.
                                                                 0 = Do not export events.
                                                                 1 = Export events where not prohibited. */
        uint32_t d_clk                 : 1;  /**< [  3:  3](R/W) Clock divider. The possible values of this bit are:
                                                                 This bit is RW.
                                                                 If PMU()_PMCR_EL0[LC] == 1, this bit is ignored and the cycle counter
                                                                     counts every clock cycle.
                                                                 ARM deprecates use of PMU()_PMCR[D] = 1.
                                                                 0 = When enabled, PMU()_PMCCNTR_EL0 counts every clock cycle.
                                                                 1 = When enabled, PMU()_PMCCNTR_EL0 counts once every 64 clock cycles. */
        uint32_t c_rst                 : 1;  /**< [  2:  2](R/W) Cycle counter reset. This bit is WO. The effects of writing to
                                                                     this bit are:
                                                                 This bit always reads as zero.
                                                                 Resetting PMU()_PMCCNTR_EL0 does not clear the PMU()_PMCCNTR_EL0 overflow
                                                                     bit to zero.
                                                                 0 = No action.
                                                                 1 = Reset PMU()_PMCCNTR_EL0 to zero. */
        uint32_t p                     : 1;  /**< [  1:  1](R/W) Event counter reset. This bit is WO. The effects of writing to
                                                                     this bit are:
                                                                 This bit always reads as zero.
                                                                 Resetting the event counters does not clear any overflow bits
                                                                     to zero.
                                                                 0 = No action.
                                                                 1 = Reset all event counters, not including PMU()_PMCCNTR_EL0, to zero. */
        uint32_t en                    : 1;  /**< [  0:  0](R/W) Enable. The possible values of this bit are:
                                                                 This bit is RW.
                                                                 0 = All counters, including PMU()_PMCCNTR_EL0, are disabled.
                                                                 1 = All counters are enabled by PMU()_PMCNTENSET_EL0. */
#else /* Word 0 - Little Endian */
        uint32_t en                    : 1;  /**< [  0:  0](R/W) Enable. The possible values of this bit are:
                                                                 This bit is RW.
                                                                 0 = All counters, including PMU()_PMCCNTR_EL0, are disabled.
                                                                 1 = All counters are enabled by PMU()_PMCNTENSET_EL0. */
        uint32_t p                     : 1;  /**< [  1:  1](R/W) Event counter reset. This bit is WO. The effects of writing to
                                                                     this bit are:
                                                                 This bit always reads as zero.
                                                                 Resetting the event counters does not clear any overflow bits
                                                                     to zero.
                                                                 0 = No action.
                                                                 1 = Reset all event counters, not including PMU()_PMCCNTR_EL0, to zero. */
        uint32_t c_rst                 : 1;  /**< [  2:  2](R/W) Cycle counter reset. This bit is WO. The effects of writing to
                                                                     this bit are:
                                                                 This bit always reads as zero.
                                                                 Resetting PMU()_PMCCNTR_EL0 does not clear the PMU()_PMCCNTR_EL0 overflow
                                                                     bit to zero.
                                                                 0 = No action.
                                                                 1 = Reset PMU()_PMCCNTR_EL0 to zero. */
        uint32_t d_clk                 : 1;  /**< [  3:  3](R/W) Clock divider. The possible values of this bit are:
                                                                 This bit is RW.
                                                                 If PMU()_PMCR_EL0[LC] == 1, this bit is ignored and the cycle counter
                                                                     counts every clock cycle.
                                                                 ARM deprecates use of PMU()_PMCR[D] = 1.
                                                                 0 = When enabled, PMU()_PMCCNTR_EL0 counts every clock cycle.
                                                                 1 = When enabled, PMU()_PMCCNTR_EL0 counts once every 64 clock cycles. */
        uint32_t x                     : 1;  /**< [  4:  4](R/W) Enable export of events in an implementation defined event
                                                                     stream. The possible values of this bit are:
                                                                 This bit is used to permit events to be exported to another
                                                                     debug device, such as an OPTIONAL trace extension, over an
                                                                     event bus. If the implementation does not include such an
                                                                     event bus, this bit is RAZ/WI.
                                                                 This bit does not affect the generation of performance
                                                                     monitors overflow interrupt requests or signaling to a cross
                                                                     trigger interface (CTI) that can be implemented as signals
                                                                     exported from the processor.
                                                                 If the implementation does not include an exported event
                                                                     stream, this bit is RAZ/WI. Otherwise this bit is RW.
                                                                 0 = Do not export events.
                                                                 1 = Export events where not prohibited. */
        uint32_t dp                    : 1;  /**< [  5:  5](R/W) Disable cycle counter when event counting is prohibited. The
                                                                     possible values of this bit are:
                                                                 Event counting is prohibited when
                                                                     ProfilingProhibited(IsSecure(),PSTATE.EL) == TRUE. See the
                                                                     "Performance Monitors and Security" section of the ARMv8 Debug
                                                                     Specification, PRD03-PRDC-010486.
                                                                 This bit is RW.
                                                                 0 =  PMU()_PMCCNTR_EL0, if enabled, counts when event counting is
                                                                     prohibited.
                                                                 1 =  PMU()_PMCCNTR_EL0 does not count when event counting is prohibited. */
        uint32_t lc                    : 1;  /**< [  6:  6](R/W) Long cycle counter enable. Determines which PMU()_PMCCNTR_EL0 bit
                                                                     generates an overflow recorded by PMOVSR[31].
                                                                 ARM deprecates use of PMU()_PMCR_EL0[LC] = 0.
                                                                 0 = Cycle counter overflow on increment that changes
                                                                     PMU()_PMCCNTR_EL0[31] from one to zero.
                                                                 1 = Cycle counter overflow on increment that changes
                                                                     PMU()_PMCCNTR_EL0[63] from one to zero. */
        uint32_t reserved_7_31         : 25;
#endif /* Word 0 - End */
    } s;
    struct bdk_pmux_pmcr_el0_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_11_31        : 21;
        uint32_t reserved_7_10         : 4;
        uint32_t lc                    : 1;  /**< [  6:  6](R/W) Long cycle counter enable. Determines which PMU()_PMCCNTR_EL0 bit
                                                                     generates an overflow recorded by PMOVSR[31].
                                                                 ARM deprecates use of PMU()_PMCR_EL0[LC] = 0.
                                                                 0 = Cycle counter overflow on increment that changes
                                                                     PMU()_PMCCNTR_EL0[31] from one to zero.
                                                                 1 = Cycle counter overflow on increment that changes
                                                                     PMU()_PMCCNTR_EL0[63] from one to zero. */
        uint32_t dp                    : 1;  /**< [  5:  5](R/W) Disable cycle counter when event counting is prohibited. The
                                                                     possible values of this bit are:
                                                                 Event counting is prohibited when
                                                                     ProfilingProhibited(IsSecure(),PSTATE.EL) == TRUE. See the
                                                                     "Performance Monitors and Security" section of the ARMv8 Debug
                                                                     Specification, PRD03-PRDC-010486.
                                                                 This bit is RW.
                                                                 0 =  PMU()_PMCCNTR_EL0, if enabled, counts when event counting is
                                                                     prohibited.
                                                                 1 =  PMU()_PMCCNTR_EL0 does not count when event counting is prohibited. */
        uint32_t x                     : 1;  /**< [  4:  4](R/W) Enable export of events in an implementation defined event
                                                                     stream. The possible values of this bit are:
                                                                 This bit is used to permit events to be exported to another
                                                                     debug device, such as an OPTIONAL trace extension, over an
                                                                     event bus. If the implementation does not include such an
                                                                     event bus, this bit is RAZ/WI.
                                                                 This bit does not affect the generation of performance
                                                                     monitors overflow interrupt requests or signaling to a cross
                                                                     trigger interface (CTI) that can be implemented as signals
                                                                     exported from the processor.
                                                                 If the implementation does not include an exported event
                                                                     stream, this bit is RAZ/WI. Otherwise this bit is RW.
                                                                 0 = Do not export events.
                                                                 1 = Export events where not prohibited. */
        uint32_t d_clk                 : 1;  /**< [  3:  3](R/W) Clock divider. The possible values of this bit are:
                                                                 This bit is RW.
                                                                 If PMU()_PMCR_EL0[LC] == 1, this bit is ignored and the cycle counter
                                                                     counts every clock cycle.
                                                                 ARM deprecates use of PMU()_PMCR[D] = 1.
                                                                 0 = When enabled, PMU()_PMCCNTR_EL0 counts every clock cycle.
                                                                 1 = When enabled, PMU()_PMCCNTR_EL0 counts once every 64 clock cycles. */
        uint32_t c_rst                 : 1;  /**< [  2:  2](R/W) Cycle counter reset. This bit is WO. The effects of writing to
                                                                     this bit are:
                                                                 This bit always reads as zero.
                                                                 Resetting PMU()_PMCCNTR_EL0 does not clear the PMU()_PMCCNTR_EL0 overflow
                                                                     bit to zero.
                                                                 0 = No action.
                                                                 1 = Reset PMU()_PMCCNTR_EL0 to zero. */
        uint32_t p                     : 1;  /**< [  1:  1](R/W) Event counter reset. This bit is WO. The effects of writing to
                                                                     this bit are:
                                                                 This bit always reads as zero.
                                                                 Resetting the event counters does not clear any overflow bits
                                                                     to zero.
                                                                 0 = No action.
                                                                 1 = Reset all event counters, not including PMU()_PMCCNTR_EL0, to zero. */
        uint32_t en                    : 1;  /**< [  0:  0](R/W) Enable. The possible values of this bit are:
                                                                 This bit is RW.
                                                                 0 = All counters, including PMU()_PMCCNTR_EL0, are disabled.
                                                                 1 = All counters are enabled by PMU()_PMCNTENSET_EL0. */
#else /* Word 0 - Little Endian */
        uint32_t en                    : 1;  /**< [  0:  0](R/W) Enable. The possible values of this bit are:
                                                                 This bit is RW.
                                                                 0 = All counters, including PMU()_PMCCNTR_EL0, are disabled.
                                                                 1 = All counters are enabled by PMU()_PMCNTENSET_EL0. */
        uint32_t p                     : 1;  /**< [  1:  1](R/W) Event counter reset. This bit is WO. The effects of writing to
                                                                     this bit are:
                                                                 This bit always reads as zero.
                                                                 Resetting the event counters does not clear any overflow bits
                                                                     to zero.
                                                                 0 = No action.
                                                                 1 = Reset all event counters, not including PMU()_PMCCNTR_EL0, to zero. */
        uint32_t c_rst                 : 1;  /**< [  2:  2](R/W) Cycle counter reset. This bit is WO. The effects of writing to
                                                                     this bit are:
                                                                 This bit always reads as zero.
                                                                 Resetting PMU()_PMCCNTR_EL0 does not clear the PMU()_PMCCNTR_EL0 overflow
                                                                     bit to zero.
                                                                 0 = No action.
                                                                 1 = Reset PMU()_PMCCNTR_EL0 to zero. */
        uint32_t d_clk                 : 1;  /**< [  3:  3](R/W) Clock divider. The possible values of this bit are:
                                                                 This bit is RW.
                                                                 If PMU()_PMCR_EL0[LC] == 1, this bit is ignored and the cycle counter
                                                                     counts every clock cycle.
                                                                 ARM deprecates use of PMU()_PMCR[D] = 1.
                                                                 0 = When enabled, PMU()_PMCCNTR_EL0 counts every clock cycle.
                                                                 1 = When enabled, PMU()_PMCCNTR_EL0 counts once every 64 clock cycles. */
        uint32_t x                     : 1;  /**< [  4:  4](R/W) Enable export of events in an implementation defined event
                                                                     stream. The possible values of this bit are:
                                                                 This bit is used to permit events to be exported to another
                                                                     debug device, such as an OPTIONAL trace extension, over an
                                                                     event bus. If the implementation does not include such an
                                                                     event bus, this bit is RAZ/WI.
                                                                 This bit does not affect the generation of performance
                                                                     monitors overflow interrupt requests or signaling to a cross
                                                                     trigger interface (CTI) that can be implemented as signals
                                                                     exported from the processor.
                                                                 If the implementation does not include an exported event
                                                                     stream, this bit is RAZ/WI. Otherwise this bit is RW.
                                                                 0 = Do not export events.
                                                                 1 = Export events where not prohibited. */
        uint32_t dp                    : 1;  /**< [  5:  5](R/W) Disable cycle counter when event counting is prohibited. The
                                                                     possible values of this bit are:
                                                                 Event counting is prohibited when
                                                                     ProfilingProhibited(IsSecure(),PSTATE.EL) == TRUE. See the
                                                                     "Performance Monitors and Security" section of the ARMv8 Debug
                                                                     Specification, PRD03-PRDC-010486.
                                                                 This bit is RW.
                                                                 0 =  PMU()_PMCCNTR_EL0, if enabled, counts when event counting is
                                                                     prohibited.
                                                                 1 =  PMU()_PMCCNTR_EL0 does not count when event counting is prohibited. */
        uint32_t lc                    : 1;  /**< [  6:  6](R/W) Long cycle counter enable. Determines which PMU()_PMCCNTR_EL0 bit
                                                                     generates an overflow recorded by PMOVSR[31].
                                                                 ARM deprecates use of PMU()_PMCR_EL0[LC] = 0.
                                                                 0 = Cycle counter overflow on increment that changes
                                                                     PMU()_PMCCNTR_EL0[31] from one to zero.
                                                                 1 = Cycle counter overflow on increment that changes
                                                                     PMU()_PMCCNTR_EL0[63] from one to zero. */
        uint32_t reserved_7_10         : 4;
        uint32_t reserved_11_31        : 21;
#endif /* Word 0 - End */
    } cn;
};
typedef union bdk_pmux_pmcr_el0 bdk_pmux_pmcr_el0_t;

static inline uint64_t BDK_PMUX_PMCR_EL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMCR_EL0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020e04ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020e04ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020e04ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020e04ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMCR_EL0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMCR_EL0(a) bdk_pmux_pmcr_el0_t
#define bustype_BDK_PMUX_PMCR_EL0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMCR_EL0(a) "PMUX_PMCR_EL0"
#define busnum_BDK_PMUX_PMCR_EL0(a) (a)
#define arguments_BDK_PMUX_PMCR_EL0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmdevaff0
 *
 * Performance Monitors Device Affinity Register 0
 * Copy of the low half of the processor MPIDR_EL1 register that
 *     allows a debugger to determine which processor in a
 *     multiprocessor system the performance monitor component
 *     relates to.
 */
union bdk_pmux_pmdevaff0
{
    uint32_t u;
    struct bdk_pmux_pmdevaff0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO) MPIDR_EL1 low half
                                                                 MPIDR_EL1 low half. Read-only copy of the low half of
                                                                    MPIDR_EL1, as seen from the highest implemented exception
                                                                    level. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO) MPIDR_EL1 low half
                                                                 MPIDR_EL1 low half. Read-only copy of the low half of
                                                                    MPIDR_EL1, as seen from the highest implemented exception
                                                                    level. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmdevaff0_s cn; */
};
typedef union bdk_pmux_pmdevaff0 bdk_pmux_pmdevaff0_t;

static inline uint64_t BDK_PMUX_PMDEVAFF0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMDEVAFF0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fa8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fa8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fa8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fa8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMDEVAFF0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMDEVAFF0(a) bdk_pmux_pmdevaff0_t
#define bustype_BDK_PMUX_PMDEVAFF0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMDEVAFF0(a) "PMUX_PMDEVAFF0"
#define busnum_BDK_PMUX_PMDEVAFF0(a) (a)
#define arguments_BDK_PMUX_PMDEVAFF0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmdevaff1
 *
 * Performance Monitors Device Affinity Register 1
 * Copy of the high half of the processor MPIDR_EL1 register that
 *     allows a debugger to determine which processor in a
 *     multiprocessor system the performance monitor component
 *     relates to.
 */
union bdk_pmux_pmdevaff1
{
    uint32_t u;
    struct bdk_pmux_pmdevaff1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO) MPIDR_EL1 high half
                                                                 MPIDR_EL1 high half. Read-only copy of the high half of
                                                                    MPIDR_EL1, as seen from the highest implemented exception
                                                                    level. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO) MPIDR_EL1 high half
                                                                 MPIDR_EL1 high half. Read-only copy of the high half of
                                                                    MPIDR_EL1, as seen from the highest implemented exception
                                                                    level. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmdevaff1_s cn; */
};
typedef union bdk_pmux_pmdevaff1 bdk_pmux_pmdevaff1_t;

static inline uint64_t BDK_PMUX_PMDEVAFF1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMDEVAFF1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020facll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020facll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020facll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020facll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMDEVAFF1", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMDEVAFF1(a) bdk_pmux_pmdevaff1_t
#define bustype_BDK_PMUX_PMDEVAFF1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMDEVAFF1(a) "PMUX_PMDEVAFF1"
#define busnum_BDK_PMUX_PMDEVAFF1(a) (a)
#define arguments_BDK_PMUX_PMDEVAFF1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmdevarch
 *
 * Performance Monitors Device Architecture Register
 */
union bdk_pmux_pmdevarch
{
    uint32_t u;
    struct bdk_pmux_pmdevarch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. For performance
                                                                     monitors, this is ARM limited.

                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.

                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by ARM this is the minor revision.
                                                                 For performance monitors, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by ARM this is further subdivided.
                                                                 For performance monitors:
                                                                  Bits [15:12] are the architecture version, 0x2.
                                                                  Bits [11:0] are the architecture part number, 0xA16.

                                                                 This corresponds to performance monitors architecture version
                                                                     PMUv3. */
#else /* Word 0 - Little Endian */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by ARM this is further subdivided.
                                                                 For performance monitors:
                                                                  Bits [15:12] are the architecture version, 0x2.
                                                                  Bits [11:0] are the architecture part number, 0xA16.

                                                                 This corresponds to performance monitors architecture version
                                                                     PMUv3. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by ARM this is the minor revision.
                                                                 For performance monitors, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. For performance
                                                                     monitors, this is ARM limited.

                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.

                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmdevarch_s cn; */
};
typedef union bdk_pmux_pmdevarch bdk_pmux_pmdevarch_t;

static inline uint64_t BDK_PMUX_PMDEVARCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMDEVARCH(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fbcll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fbcll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fbcll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fbcll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMDEVARCH", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMDEVARCH(a) bdk_pmux_pmdevarch_t
#define bustype_BDK_PMUX_PMDEVARCH(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMDEVARCH(a) "PMUX_PMDEVARCH"
#define busnum_BDK_PMUX_PMDEVARCH(a) (a)
#define arguments_BDK_PMUX_PMDEVARCH(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmdevid
 *
 * Performance Monitors Device ID Register
 * Indicates to a debugger that the PC sample mechanism is implemented.
 */
union bdk_pmux_pmdevid
{
    uint32_t u;
    struct bdk_pmux_pmdevid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t pcsample              : 4;  /**< [  3:  0](RO) 0 = PC sample mechanism not implemented.
                                                                 1 = PC sample mechanism implemented. */
#else /* Word 0 - Little Endian */
        uint32_t pcsample              : 4;  /**< [  3:  0](RO) 0 = PC sample mechanism not implemented.
                                                                 1 = PC sample mechanism implemented. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmdevid_s cn; */
};
typedef union bdk_pmux_pmdevid bdk_pmux_pmdevid_t;

static inline uint64_t BDK_PMUX_PMDEVID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMDEVID(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fc8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMDEVID", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMDEVID(a) bdk_pmux_pmdevid_t
#define bustype_BDK_PMUX_PMDEVID(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMDEVID(a) "PMUX_PMDEVID"
#define busnum_BDK_PMUX_PMDEVID(a) (a)
#define arguments_BDK_PMUX_PMDEVID(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmdevtype
 *
 * Performance Monitors Device Type Register
 * Indicates to a debugger that this component is part of a
 *     processor's performance monitor interface.
 */
union bdk_pmux_pmdevtype
{
    uint32_t u;
    struct bdk_pmux_pmdevtype_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Subtype. Must read as 0x1. */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major type. Must read as 0x6. */
#else /* Word 0 - Little Endian */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major type. Must read as 0x6. */
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Subtype. Must read as 0x1. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmdevtype_s cn; */
};
typedef union bdk_pmux_pmdevtype bdk_pmux_pmdevtype_t;

static inline uint64_t BDK_PMUX_PMDEVTYPE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMDEVTYPE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fccll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fccll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fccll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fccll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMDEVTYPE", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMDEVTYPE(a) bdk_pmux_pmdevtype_t
#define bustype_BDK_PMUX_PMDEVTYPE(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMDEVTYPE(a) "PMUX_PMDEVTYPE"
#define busnum_BDK_PMUX_PMDEVTYPE(a) (a)
#define arguments_BDK_PMUX_PMDEVTYPE(a) (a),-1,-1,-1

/**
 * Register (DAB) pmu#_pmevcntr#_el0
 *
 * Performance Monitors Event Count Registers
 * This register contains the event counters.
 */
union bdk_pmux_pmevcntrx_el0
{
    uint64_t u;
    struct bdk_pmux_pmevcntrx_el0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Event counter. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Event counter. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmevcntrx_el0_s cn; */
};
typedef union bdk_pmux_pmevcntrx_el0 bdk_pmux_pmevcntrx_el0_t;

static inline uint64_t BDK_PMUX_PMEVCNTRX_EL0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMEVCNTRX_EL0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a<=3) && (b<=5)))
        return 0x87a008020000ll + 0x80000ll * ((a) & 0x3) + 8ll * ((b) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=23) && (b<=5)))
        return 0x87a008020000ll + 0x80000ll * ((a) & 0x1f) + 8ll * ((b) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=47) && (b<=5)))
        return 0x87a008020000ll + 0x80000ll * ((a) & 0x3f) + 8ll * ((b) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=23) && (b<=5)))
        return 0x87a008020000ll + 0x80000ll * ((a) & 0x1f) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("PMUX_PMEVCNTRX_EL0", 2, a, b, 0, 0);
}

#define typedef_BDK_PMUX_PMEVCNTRX_EL0(a,b) bdk_pmux_pmevcntrx_el0_t
#define bustype_BDK_PMUX_PMEVCNTRX_EL0(a,b) BDK_CSR_TYPE_DAB
#define basename_BDK_PMUX_PMEVCNTRX_EL0(a,b) "PMUX_PMEVCNTRX_EL0"
#define busnum_BDK_PMUX_PMEVCNTRX_EL0(a,b) (a)
#define arguments_BDK_PMUX_PMEVCNTRX_EL0(a,b) (a),(b),-1,-1

/**
 * Register (DAB32b) pmu#_pmevtyper#_el0
 *
 * Performance Monitors Event Type Registers
 * This register contains the event counters.
 */
union bdk_pmux_pmevtyperx_el0
{
    uint32_t u;
    struct bdk_pmux_pmevtyperx_el0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL1.
                                                                 1 = Do not count events in EL1. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL0.
                                                                 1 = Do not count events in EL0. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, events in nonsecure EL1 are not counted. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, events in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, events in nonsecure EL0 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count events in EL2.
                                                                 1 = Count events in EL2. */
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     secure EL3 are counted.
                                                                 Otherwise, events in secure EL3 are not counted. */
        uint32_t reserved_16_25        : 10;
        uint32_t evtcount              : 16; /**< [ 15:  0](R/W) Event to count. */
#else /* Word 0 - Little Endian */
        uint32_t evtcount              : 16; /**< [ 15:  0](R/W) Event to count. */
        uint32_t reserved_16_25        : 10;
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     secure EL3 are counted.
                                                                 Otherwise, events in secure EL3 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count events in EL2.
                                                                 1 = Count events in EL2. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, events in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, events in nonsecure EL0 are not counted. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, events in nonsecure EL1 are not counted. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL0.
                                                                 1 = Do not count events in EL0. */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL1.
                                                                 1 = Do not count events in EL1. */
#endif /* Word 0 - End */
    } s;
    struct bdk_pmux_pmevtyperx_el0_cn88xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL1.
                                                                 1 = Do not count events in EL1. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL0.
                                                                 1 = Do not count events in EL0. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, events in nonsecure EL1 are not counted. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, events in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, events in nonsecure EL0 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count events in EL2.
                                                                 1 = Count events in EL2. */
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     secure EL3 are counted.
                                                                 Otherwise, events in secure EL3 are not counted. */
        uint32_t reserved_10_25        : 16;
        uint32_t evtcount              : 10; /**< [  9:  0](R/W) Event to count. */
#else /* Word 0 - Little Endian */
        uint32_t evtcount              : 10; /**< [  9:  0](R/W) Event to count. */
        uint32_t reserved_10_25        : 16;
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     secure EL3 are counted.
                                                                 Otherwise, events in secure EL3 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count events in EL2.
                                                                 1 = Count events in EL2. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, events in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, events in nonsecure EL0 are not counted. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, events in nonsecure EL1 are not counted. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL0.
                                                                 1 = Do not count events in EL0. */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL1.
                                                                 1 = Do not count events in EL1. */
#endif /* Word 0 - End */
    } cn88xxp1;
    struct bdk_pmux_pmevtyperx_el0_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL1.
                                                                 1 = Do not count events in EL1. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL0.
                                                                 1 = Do not count events in EL0. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, events in nonsecure EL1 are not counted. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, events in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, events in nonsecure EL0 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count events in EL2.
                                                                 1 = Count events in EL2. */
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     secure EL3 are counted.
                                                                 Otherwise, events in secure EL3 are not counted. */
        uint32_t reserved_16_25        : 10;
        uint32_t evtcount              : 16; /**< [ 15:  0](R/W) Event to count. The event number of the event that is counted
                                                                     by event counter PMU()_PMEVCNTR()_EL0.
                                                                 Enumerated by PMU_PERF_E.

                                                                 Software must program this field with an event defined by the
                                                                     processor or a common event defined by the architecture.
                                                                 If evtCount is programmed to an event that is reserved or not
                                                                     implemented, the behavior depends on the event type.
                                                                 For common architectural and microarchitectural events:
                                                                  no events are counted.
                                                                  The value read back on evtCount is the value written.
                                                                 For implementation defined events:
                                                                  It is UNPREDICTABLE what event, if any, is counted.
                                                                     UNPREDICTABLE in this case means the event must not expose
                                                                     privileged information.
                                                                  The value read back on evtCount is an unknown value with the
                                                                     same effect.
                                                                 ARM recommends that the behavior across a family of
                                                                     implementations is defined such that if a given implementation
                                                                     does not include an event from a set of common implementation
                                                                     defined events, then no event is counted and the value read
                                                                     back on evtCount is the value written. */
#else /* Word 0 - Little Endian */
        uint32_t evtcount              : 16; /**< [ 15:  0](R/W) Event to count. The event number of the event that is counted
                                                                     by event counter PMU()_PMEVCNTR()_EL0.
                                                                 Enumerated by PMU_PERF_E.

                                                                 Software must program this field with an event defined by the
                                                                     processor or a common event defined by the architecture.
                                                                 If evtCount is programmed to an event that is reserved or not
                                                                     implemented, the behavior depends on the event type.
                                                                 For common architectural and microarchitectural events:
                                                                  no events are counted.
                                                                  The value read back on evtCount is the value written.
                                                                 For implementation defined events:
                                                                  It is UNPREDICTABLE what event, if any, is counted.
                                                                     UNPREDICTABLE in this case means the event must not expose
                                                                     privileged information.
                                                                  The value read back on evtCount is an unknown value with the
                                                                     same effect.
                                                                 ARM recommends that the behavior across a family of
                                                                     implementations is defined such that if a given implementation
                                                                     does not include an event from a set of common implementation
                                                                     defined events, then no event is counted and the value read
                                                                     back on evtCount is the value written. */
        uint32_t reserved_16_25        : 10;
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     secure EL3 are counted.
                                                                 Otherwise, events in secure EL3 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count events in EL2.
                                                                 1 = Count events in EL2. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, events in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, events in nonsecure EL0 are not counted. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, events in nonsecure EL1 are not counted. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL0.
                                                                 1 = Do not count events in EL0. */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL1.
                                                                 1 = Do not count events in EL1. */
#endif /* Word 0 - End */
    } cn9;
    struct bdk_pmux_pmevtyperx_el0_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL1.
                                                                 1 = Do not count events in EL1. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL0.
                                                                 1 = Do not count events in EL0. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, events in nonsecure EL1 are not counted. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, events in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, events in nonsecure EL0 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count events in EL2.
                                                                 1 = Count events in EL2. */
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     secure EL3 are counted.
                                                                 Otherwise, events in secure EL3 are not counted. */
        uint32_t reserved_16_25        : 10;
        uint32_t evtcount              : 16; /**< [ 15:  0](R/W) Event to count. The event number of the event that is counted
                                                                     by event counter PMU()_PMEVCNTR()_EL0.
                                                                 Enumerated by PMU_PERF_E.

                                                                 Software must program this field with an event defined by the
                                                                     processor or a common event defined by the architecture.
                                                                 If evtCount is programmed to an event that is reserved or not
                                                                     implemented, the behavior depends on the event type.
                                                                 For common architectural and microarchitectural events:
                                                                  no events are counted.
                                                                  The value read back on evtCount is the value written.
                                                                 For implementation defined events:
                                                                  It is UNPREDICTABLE what event, if any, is counted.
                                                                     UNPREDICTABLE in this case means the event must not expose
                                                                     privileged information.
                                                                  The value read back on evtCount is an UNKNOWN value with the
                                                                     same effect.
                                                                 ARM recommends that the behavior across a family of
                                                                     implementations is defined such that if a given implementation
                                                                     does not include an event from a set of common implementation
                                                                     defined events, then no event is counted and the value read
                                                                     back on evtCount is the value written. */
#else /* Word 0 - Little Endian */
        uint32_t evtcount              : 16; /**< [ 15:  0](R/W) Event to count. The event number of the event that is counted
                                                                     by event counter PMU()_PMEVCNTR()_EL0.
                                                                 Enumerated by PMU_PERF_E.

                                                                 Software must program this field with an event defined by the
                                                                     processor or a common event defined by the architecture.
                                                                 If evtCount is programmed to an event that is reserved or not
                                                                     implemented, the behavior depends on the event type.
                                                                 For common architectural and microarchitectural events:
                                                                  no events are counted.
                                                                  The value read back on evtCount is the value written.
                                                                 For implementation defined events:
                                                                  It is UNPREDICTABLE what event, if any, is counted.
                                                                     UNPREDICTABLE in this case means the event must not expose
                                                                     privileged information.
                                                                  The value read back on evtCount is an UNKNOWN value with the
                                                                     same effect.
                                                                 ARM recommends that the behavior across a family of
                                                                     implementations is defined such that if a given implementation
                                                                     does not include an event from a set of common implementation
                                                                     defined events, then no event is counted and the value read
                                                                     back on evtCount is the value written. */
        uint32_t reserved_16_25        : 10;
        uint32_t m                     : 1;  /**< [ 26: 26](R/W) Secure EL3 filtering bit. Most applications can ignore this
                                                                     bit and set the value to zero. If EL3 is not implemented, this
                                                                     bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     secure EL3 are counted.
                                                                 Otherwise, events in secure EL3 are not counted. */
        uint32_t nsh                   : 1;  /**< [ 27: 27](R/W) Nonsecure hyp modes filtering bit. Controls counting in
                                                                     nonsecure EL2. If EL2 is not implemented, this bit is RES0.
                                                                 0 = Do not count events in EL2.
                                                                 1 = Count events in EL2. */
        uint32_t nsu                   : 1;  /**< [ 28: 28](R/W) Nonsecure user modes filtering bit. Controls counting in
                                                                     nonsecure EL0. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of U, events in
                                                                     nonsecure EL0 are counted.
                                                                 Otherwise, events in nonsecure EL0 are not counted. */
        uint32_t nsk                   : 1;  /**< [ 29: 29](R/W) Nonsecure kernel modes filtering bit. Controls counting in
                                                                     nonsecure EL1. If EL3 is not implemented, this bit is RES0.
                                                                 If the value of this bit is equal to the value of P, events in
                                                                     nonsecure EL1 are counted.
                                                                 Otherwise, events in nonsecure EL1 are not counted. */
        uint32_t u                     : 1;  /**< [ 30: 30](R/W) EL0 filtering bit. Controls counting in EL0. If EL3 is
                                                                     implemented, then counting in nonsecure EL0 is further
                                                                     controlled by [NSU]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL0.
                                                                 1 = Do not count events in EL0. */
        uint32_t p                     : 1;  /**< [ 31: 31](R/W) EL1 modes filtering bit. Controls counting in EL1. If EL3 is
                                                                     implemented, then counting in nonsecure EL1 is further
                                                                     controlled by [NSK]. The possible values of this bit
                                                                     are:
                                                                 0 = Count events in EL1.
                                                                 1 = Do not count events in EL1. */
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_pmux_pmevtyperx_el0_cn81xx cn83xx; */
    /* struct bdk_pmux_pmevtyperx_el0_cn81xx cn88xxp2; */
};
typedef union bdk_pmux_pmevtyperx_el0 bdk_pmux_pmevtyperx_el0_t;

static inline uint64_t BDK_PMUX_PMEVTYPERX_EL0(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMEVTYPERX_EL0(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a<=3) && (b<=5)))
        return 0x87a008020400ll + 0x80000ll * ((a) & 0x3) + 4ll * ((b) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=23) && (b<=5)))
        return 0x87a008020400ll + 0x80000ll * ((a) & 0x1f) + 4ll * ((b) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=47) && (b<=5)))
        return 0x87a008020400ll + 0x80000ll * ((a) & 0x3f) + 4ll * ((b) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=23) && (b<=5)))
        return 0x87a008020400ll + 0x80000ll * ((a) & 0x1f) + 4ll * ((b) & 0x7);
    __bdk_csr_fatal("PMUX_PMEVTYPERX_EL0", 2, a, b, 0, 0);
}

#define typedef_BDK_PMUX_PMEVTYPERX_EL0(a,b) bdk_pmux_pmevtyperx_el0_t
#define bustype_BDK_PMUX_PMEVTYPERX_EL0(a,b) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMEVTYPERX_EL0(a,b) "PMUX_PMEVTYPERX_EL0"
#define busnum_BDK_PMUX_PMEVTYPERX_EL0(a,b) (a)
#define arguments_BDK_PMUX_PMEVTYPERX_EL0(a,b) (a),(b),-1,-1

/**
 * Register (DAB32b) pmu#_pmintenclr_el1
 *
 * Performance Monitors Interrupt Enable Clear Register
 * Disables the generation of interrupt requests on overflows
 *     from the cycle count register, PMU()_PMCCNTR_EL0, and the event
 *     counters PMEVCNTR\<n\>_EL0. Reading the register shows which
 *     overflow interrupt requests are enabled.
 */
union bdk_pmux_pmintenclr_el1
{
    uint32_t u;
    struct bdk_pmux_pmintenclr_el1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 overflow interrupt request disable bit. Possible
                                                                     values are:
                                                                 0 = When read, means the cycle counter overflow interrupt request
                                                                     is disabled. When written, has no effect.
                                                                 1 = When read, means the cycle counter overflow interrupt request
                                                                     is enabled. When written, disables the cycle count overflow
                                                                     interrupt request. */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter overflow interrupt request disable bit for
                                                                     PMEVCNTR\<x\>_EL0.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values are:
                                                                 0 = When read, means that the PMEVCNTR\<x\>_EL0 event counter
                                                                     interrupt request is disabled. When written, has no effect.
                                                                 1 = When read, means that the PMEVCNTR\<x\>_EL0 event counter
                                                                     interrupt request is enabled. When written, disables the
                                                                     PMEVCNTR\<x\>_EL0 interrupt request. */
#else /* Word 0 - Little Endian */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter overflow interrupt request disable bit for
                                                                     PMEVCNTR\<x\>_EL0.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values are:
                                                                 0 = When read, means that the PMEVCNTR\<x\>_EL0 event counter
                                                                     interrupt request is disabled. When written, has no effect.
                                                                 1 = When read, means that the PMEVCNTR\<x\>_EL0 event counter
                                                                     interrupt request is enabled. When written, disables the
                                                                     PMEVCNTR\<x\>_EL0 interrupt request. */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 overflow interrupt request disable bit. Possible
                                                                     values are:
                                                                 0 = When read, means the cycle counter overflow interrupt request
                                                                     is disabled. When written, has no effect.
                                                                 1 = When read, means the cycle counter overflow interrupt request
                                                                     is enabled. When written, disables the cycle count overflow
                                                                     interrupt request. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmintenclr_el1_s cn; */
};
typedef union bdk_pmux_pmintenclr_el1 bdk_pmux_pmintenclr_el1_t;

static inline uint64_t BDK_PMUX_PMINTENCLR_EL1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMINTENCLR_EL1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020c60ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020c60ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020c60ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020c60ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMINTENCLR_EL1", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMINTENCLR_EL1(a) bdk_pmux_pmintenclr_el1_t
#define bustype_BDK_PMUX_PMINTENCLR_EL1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMINTENCLR_EL1(a) "PMUX_PMINTENCLR_EL1"
#define busnum_BDK_PMUX_PMINTENCLR_EL1(a) (a)
#define arguments_BDK_PMUX_PMINTENCLR_EL1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmintenset_el1
 *
 * Performance Monitors Interrupt Enable Set Register
 * Enables the generation of interrupt requests on overflows from
 *     the cycle count register, PMU()_PMCCNTR_EL0, and the event counters
 *     PMEVCNTR\<n\>_EL0. Reading the register shows which overflow
 *     interrupt requests are enabled.
 */
union bdk_pmux_pmintenset_el1
{
    uint32_t u;
    struct bdk_pmux_pmintenset_el1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 overflow interrupt request enable bit. Possible
                                                                     values are:
                                                                 0 = When read, means the cycle counter overflow interrupt request
                                                                     is disabled. When written, has no effect.
                                                                 1 = When read, means the cycle counter overflow interrupt request
                                                                     is enabled. When written, enables the cycle count overflow
                                                                     interrupt request. */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter overflow interrupt request enable bit for
                                                                     PMEVCNTR\<x\>_EL0.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values are:
                                                                 0 = When read, means that the PMEVCNTR\<x\>_EL0 event counter
                                                                     interrupt request is disabled. When written, has no effect.
                                                                 1 = When read, means that the PMEVCNTR\<x\>_EL0 event counter
                                                                     interrupt request is enabled. When written, enables the
                                                                     PMEVCNTR\<x\>_EL0 interrupt request. */
#else /* Word 0 - Little Endian */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter overflow interrupt request enable bit for
                                                                     PMEVCNTR\<x\>_EL0.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values are:
                                                                 0 = When read, means that the PMEVCNTR\<x\>_EL0 event counter
                                                                     interrupt request is disabled. When written, has no effect.
                                                                 1 = When read, means that the PMEVCNTR\<x\>_EL0 event counter
                                                                     interrupt request is enabled. When written, enables the
                                                                     PMEVCNTR\<x\>_EL0 interrupt request. */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 overflow interrupt request enable bit. Possible
                                                                     values are:
                                                                 0 = When read, means the cycle counter overflow interrupt request
                                                                     is disabled. When written, has no effect.
                                                                 1 = When read, means the cycle counter overflow interrupt request
                                                                     is enabled. When written, enables the cycle count overflow
                                                                     interrupt request. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmintenset_el1_s cn; */
};
typedef union bdk_pmux_pmintenset_el1 bdk_pmux_pmintenset_el1_t;

static inline uint64_t BDK_PMUX_PMINTENSET_EL1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMINTENSET_EL1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020c40ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020c40ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020c40ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020c40ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMINTENSET_EL1", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMINTENSET_EL1(a) bdk_pmux_pmintenset_el1_t
#define bustype_BDK_PMUX_PMINTENSET_EL1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMINTENSET_EL1(a) "PMUX_PMINTENSET_EL1"
#define busnum_BDK_PMUX_PMINTENSET_EL1(a) (a)
#define arguments_BDK_PMUX_PMINTENSET_EL1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmitctrl
 *
 * Performance Monitors Integration Mode Control Register
 * Enables the performance monitors to switch from default mode
 *     into integration mode, where test software can control
 *     directly the inputs and outputs of the processor, for
 *     integration testing or topology detection.
 */
union bdk_pmux_pmitctrl
{
    uint32_t u;
    struct bdk_pmux_pmitctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable. When IME == 1, the device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. */
#else /* Word 0 - Little Endian */
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable. When IME == 1, the device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmitctrl_s cn8; */
    struct bdk_pmux_pmitctrl_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. The device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
#else /* Word 0 - Little Endian */
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. The device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_pmux_pmitctrl bdk_pmux_pmitctrl_t;

static inline uint64_t BDK_PMUX_PMITCTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMITCTRL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020f00ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020f00ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020f00ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020f00ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMITCTRL", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMITCTRL(a) bdk_pmux_pmitctrl_t
#define bustype_BDK_PMUX_PMITCTRL(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMITCTRL(a) "PMUX_PMITCTRL"
#define busnum_BDK_PMUX_PMITCTRL(a) (a)
#define arguments_BDK_PMUX_PMITCTRL(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmlar
 *
 * Performance Monitors Lock Access Register
 * Allows or disallows access to the performance monitors
 *     registers through a memory-mapped interface.
 */
union bdk_pmux_pmlar
{
    uint32_t u;
    struct bdk_pmux_pmlar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t key                   : 32; /**< [ 31:  0](WO) Lock access control. Writing the key value 0xC5ACCE55 unlocks the lock.
                                                                 Writing any other value to this register locks the lock, disabling write
                                                                 accesses to this component's registers through a memory mapped interface. */
#else /* Word 0 - Little Endian */
        uint32_t key                   : 32; /**< [ 31:  0](WO) Lock access control. Writing the key value 0xC5ACCE55 unlocks the lock.
                                                                 Writing any other value to this register locks the lock, disabling write
                                                                 accesses to this component's registers through a memory mapped interface. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmlar_s cn; */
};
typedef union bdk_pmux_pmlar bdk_pmux_pmlar_t;

static inline uint64_t BDK_PMUX_PMLAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMLAR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fb0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fb0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fb0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fb0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMLAR", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMLAR(a) bdk_pmux_pmlar_t
#define bustype_BDK_PMUX_PMLAR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMLAR(a) "PMUX_PMLAR"
#define busnum_BDK_PMUX_PMLAR(a) (a)
#define arguments_BDK_PMUX_PMLAR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmlsr
 *
 * Performance Monitors Lock Status Register
 * Indicates the current status of the software lock for
 *     performance monitors registers.
 */
union bdk_pmux_pmlsr
{
    uint32_t u;
    struct bdk_pmux_pmlsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t ntt                   : 1;  /**< [  2:  2](RO) Not thirty-two bit access required. Always clear. */
        uint32_t slk                   : 1;  /**< [  1:  1](RO/H) Software lock status for this component. For an access to LSR
                                                                     that is not a memory-mapped access, or when the software lock
                                                                     is not implemented, this field is RES0.
                                                                 On external debug reset, the field resets to one.
                                                                 For memory-mapped accesses when the software lock is
                                                                     implemented, possible values of this field are:
                                                                 0 = Lock clear. Writes are permitted to this component's
                                                                     registers.
                                                                 1 = Lock set. Writes to this component's registers are ignored,
                                                                     and reads have no side effects. */
        uint32_t sli                   : 1;  /**< [  0:  0](RO) Software lock implemented. For an access to LSR that is not a
                                                                     memory-mapped access, this field reads as zero. For memory-mapped
                                                                     accesses, the value of this field is implementation defined.
                                                                     Permitted values are:
                                                                 0 = Software lock not implemented or not memory-mapped access.
                                                                 1 = Software lock implemented and memory-mapped access. */
#else /* Word 0 - Little Endian */
        uint32_t sli                   : 1;  /**< [  0:  0](RO) Software lock implemented. For an access to LSR that is not a
                                                                     memory-mapped access, this field reads as zero. For memory-mapped
                                                                     accesses, the value of this field is implementation defined.
                                                                     Permitted values are:
                                                                 0 = Software lock not implemented or not memory-mapped access.
                                                                 1 = Software lock implemented and memory-mapped access. */
        uint32_t slk                   : 1;  /**< [  1:  1](RO/H) Software lock status for this component. For an access to LSR
                                                                     that is not a memory-mapped access, or when the software lock
                                                                     is not implemented, this field is RES0.
                                                                 On external debug reset, the field resets to one.
                                                                 For memory-mapped accesses when the software lock is
                                                                     implemented, possible values of this field are:
                                                                 0 = Lock clear. Writes are permitted to this component's
                                                                     registers.
                                                                 1 = Lock set. Writes to this component's registers are ignored,
                                                                     and reads have no side effects. */
        uint32_t ntt                   : 1;  /**< [  2:  2](RO) Not thirty-two bit access required. Always clear. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmlsr_s cn; */
};
typedef union bdk_pmux_pmlsr bdk_pmux_pmlsr_t;

static inline uint64_t BDK_PMUX_PMLSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMLSR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fb4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fb4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fb4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fb4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMLSR", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMLSR(a) bdk_pmux_pmlsr_t
#define bustype_BDK_PMUX_PMLSR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMLSR(a) "PMUX_PMLSR"
#define busnum_BDK_PMUX_PMLSR(a) (a)
#define arguments_BDK_PMUX_PMLSR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmovsclr_el0
 *
 * Performance Monitors Overflow Flag Status Clear Register
 * Contains the state of the overflow bit for the cycle count
 *     register, PMU()_PMCCNTR_EL0, and each of the implemented event
 *     counters PMEVCNTR\<x\>. Writing to this register clears these
 *     bits.
 */
union bdk_pmux_pmovsclr_el0
{
    uint32_t u;
    struct bdk_pmux_pmovsclr_el0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 overflow bit. Possible values are:
                                                                 PMU()_PMCR_EL0[LC] is used to control from which bit of PMU()_PMCCNTR_EL0
                                                                     (bit 31 or bit 63) an overflow is detected.
                                                                 0 = When read, means the cycle counter has not overflowed. When
                                                                     written, has no effect.
                                                                 1 = When read, means the cycle counter has overflowed. When
                                                                     written, clears the overflow bit to zero. */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter overflow clear bit for PMEVCNTR\<x\>.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values of each bit are:
                                                                 0 = When read, means that PMEVCNTR\<x\> has not overflowed. When
                                                                     written, has no effect.
                                                                 1 = When read, means that PMEVCNTR\<x\> has overflowed. When
                                                                     written, clears the PMEVCNTR\<x\> overflow bit to zero. */
#else /* Word 0 - Little Endian */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter overflow clear bit for PMEVCNTR\<x\>.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values of each bit are:
                                                                 0 = When read, means that PMEVCNTR\<x\> has not overflowed. When
                                                                     written, has no effect.
                                                                 1 = When read, means that PMEVCNTR\<x\> has overflowed. When
                                                                     written, clears the PMEVCNTR\<x\> overflow bit to zero. */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 overflow bit. Possible values are:
                                                                 PMU()_PMCR_EL0[LC] is used to control from which bit of PMU()_PMCCNTR_EL0
                                                                     (bit 31 or bit 63) an overflow is detected.
                                                                 0 = When read, means the cycle counter has not overflowed. When
                                                                     written, has no effect.
                                                                 1 = When read, means the cycle counter has overflowed. When
                                                                     written, clears the overflow bit to zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmovsclr_el0_s cn; */
};
typedef union bdk_pmux_pmovsclr_el0 bdk_pmux_pmovsclr_el0_t;

static inline uint64_t BDK_PMUX_PMOVSCLR_EL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMOVSCLR_EL0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020c80ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020c80ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020c80ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020c80ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMOVSCLR_EL0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMOVSCLR_EL0(a) bdk_pmux_pmovsclr_el0_t
#define bustype_BDK_PMUX_PMOVSCLR_EL0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMOVSCLR_EL0(a) "PMUX_PMOVSCLR_EL0"
#define busnum_BDK_PMUX_PMOVSCLR_EL0(a) (a)
#define arguments_BDK_PMUX_PMOVSCLR_EL0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmovsset_el0
 *
 * Performance Monitors Overflow Flag Status Set Register
 * Sets the state of the overflow bit for the cycle count
 *     register, PMU()_PMCCNTR_EL0, and each of the implemented event
 *     counters PMEVCNTR\<x\>.
 */
union bdk_pmux_pmovsset_el0
{
    uint32_t u;
    struct bdk_pmux_pmovsset_el0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 overflow bit. Possible values are:
                                                                 0 = When read, means the cycle counter has not overflowed. When
                                                                     written, has no effect.
                                                                 1 = When read, means the cycle counter has overflowed. When
                                                                     written, sets the overflow bit to one. */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter overflow set bit for PMEVCNTR\<x\>.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values are:
                                                                 0 = When read, means that PMEVCNTR\<x\> has not overflowed. When
                                                                     written, has no effect.
                                                                 1 = When read, means that PMEVCNTR\<x\> has overflowed. When
                                                                     written, sets the PMEVCNTR\<x\> overflow bit to one. */
#else /* Word 0 - Little Endian */
        uint32_t p                     : 31; /**< [ 30:  0](R/W) Event counter overflow set bit for PMEVCNTR\<x\>.
                                                                 N is the value in PMU()_PMCR_EL0[N]. Bits [30:N] are RAZ/WI.
                                                                 Possible values are:
                                                                 0 = When read, means that PMEVCNTR\<x\> has not overflowed. When
                                                                     written, has no effect.
                                                                 1 = When read, means that PMEVCNTR\<x\> has overflowed. When
                                                                     written, sets the PMEVCNTR\<x\> overflow bit to one. */
        uint32_t c_set                 : 1;  /**< [ 31: 31](R/W) PMU()_PMCCNTR_EL0 overflow bit. Possible values are:
                                                                 0 = When read, means the cycle counter has not overflowed. When
                                                                     written, has no effect.
                                                                 1 = When read, means the cycle counter has overflowed. When
                                                                     written, sets the overflow bit to one. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmovsset_el0_s cn; */
};
typedef union bdk_pmux_pmovsset_el0 bdk_pmux_pmovsset_el0_t;

static inline uint64_t BDK_PMUX_PMOVSSET_EL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMOVSSET_EL0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020cc0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020cc0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020cc0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020cc0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMOVSSET_EL0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMOVSSET_EL0(a) bdk_pmux_pmovsset_el0_t
#define bustype_BDK_PMUX_PMOVSSET_EL0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMOVSSET_EL0(a) "PMUX_PMOVSSET_EL0"
#define busnum_BDK_PMUX_PMOVSSET_EL0(a) (a)
#define arguments_BDK_PMUX_PMOVSSET_EL0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpcsr_hi
 *
 * AP Program Counter Sample High Register
 * PC bits 63:32 sampled when PMPCSR_LO is read.
 * When DBG()_EDSCR[SC2] is set, PMPCSR_HI[23:0] is set to bits [55:32] of the sampled PC, and
 * PMPCSR_HI[31:29] record the NS-state [31] and Exception level [30:29].
 */
union bdk_pmux_pmpcsr_hi
{
    uint32_t u;
    struct bdk_pmux_pmpcsr_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t non_secure            : 1;  /**< [ 31: 31](RO) Reserved. */
        uint32_t el                    : 2;  /**< [ 30: 29](RO) Reserved. */
        uint32_t reserved_24_28        : 5;
        uint32_t pc_55_32              : 24; /**< [ 23:  0](RO) Count. */
#else /* Word 0 - Little Endian */
        uint32_t pc_55_32              : 24; /**< [ 23:  0](RO) Count. */
        uint32_t reserved_24_28        : 5;
        uint32_t el                    : 2;  /**< [ 30: 29](RO) Reserved. */
        uint32_t non_secure            : 1;  /**< [ 31: 31](RO) Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpcsr_hi_s cn; */
};
typedef union bdk_pmux_pmpcsr_hi bdk_pmux_pmpcsr_hi_t;

static inline uint64_t BDK_PMUX_PMPCSR_HI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPCSR_HI(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020204ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPCSR_HI", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPCSR_HI(a) bdk_pmux_pmpcsr_hi_t
#define bustype_BDK_PMUX_PMPCSR_HI(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPCSR_HI(a) "PMUX_PMPCSR_HI"
#define busnum_BDK_PMUX_PMPCSR_HI(a) (a)
#define arguments_BDK_PMUX_PMPCSR_HI(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpcsr_hi_alias
 *
 * AP Program Counter Sample High Register
 */
union bdk_pmux_pmpcsr_hi_alias
{
    uint32_t u;
    struct bdk_pmux_pmpcsr_hi_alias_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t non_secure            : 1;  /**< [ 31: 31](RO) Reserved. */
        uint32_t el                    : 2;  /**< [ 30: 29](RO) Reserved. */
        uint32_t reserved_24_28        : 5;
        uint32_t pc_55_32              : 24; /**< [ 23:  0](RO) Count. */
#else /* Word 0 - Little Endian */
        uint32_t pc_55_32              : 24; /**< [ 23:  0](RO) Count. */
        uint32_t reserved_24_28        : 5;
        uint32_t el                    : 2;  /**< [ 30: 29](RO) Reserved. */
        uint32_t non_secure            : 1;  /**< [ 31: 31](RO) Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpcsr_hi_alias_s cn; */
};
typedef union bdk_pmux_pmpcsr_hi_alias bdk_pmux_pmpcsr_hi_alias_t;

static inline uint64_t BDK_PMUX_PMPCSR_HI_ALIAS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPCSR_HI_ALIAS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020224ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPCSR_HI_ALIAS", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPCSR_HI_ALIAS(a) bdk_pmux_pmpcsr_hi_alias_t
#define bustype_BDK_PMUX_PMPCSR_HI_ALIAS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPCSR_HI_ALIAS(a) "PMUX_PMPCSR_HI_ALIAS"
#define busnum_BDK_PMUX_PMPCSR_HI_ALIAS(a) (a)
#define arguments_BDK_PMUX_PMPCSR_HI_ALIAS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpcsr_lo
 *
 * AP Program Counter Sample Low Register
 * Low order 32 bits of the sampled PC.  May be used to capture PC values when sampling is
 * enabled.
 * When read, causes the capture of the low PC bits, PMCID1SR (Context), PMCID2SR (Context),
 * PMVIDSR (VMID) and PMPCSR_HI.
 */
union bdk_pmux_pmpcsr_lo
{
    uint32_t u;
    struct bdk_pmux_pmpcsr_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t pc_31_0               : 32; /**< [ 31:  0](RO) Count. */
#else /* Word 0 - Little Endian */
        uint32_t pc_31_0               : 32; /**< [ 31:  0](RO) Count. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpcsr_lo_s cn; */
};
typedef union bdk_pmux_pmpcsr_lo bdk_pmux_pmpcsr_lo_t;

static inline uint64_t BDK_PMUX_PMPCSR_LO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPCSR_LO(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020200ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPCSR_LO", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPCSR_LO(a) bdk_pmux_pmpcsr_lo_t
#define bustype_BDK_PMUX_PMPCSR_LO(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPCSR_LO(a) "PMUX_PMPCSR_LO"
#define busnum_BDK_PMUX_PMPCSR_LO(a) (a)
#define arguments_BDK_PMUX_PMPCSR_LO(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpcsr_lo_alias
 *
 * AP Program Counter Sample Low Register
 */
union bdk_pmux_pmpcsr_lo_alias
{
    uint32_t u;
    struct bdk_pmux_pmpcsr_lo_alias_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t pc_31_0               : 32; /**< [ 31:  0](RO) Count. */
#else /* Word 0 - Little Endian */
        uint32_t pc_31_0               : 32; /**< [ 31:  0](RO) Count. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpcsr_lo_alias_s cn; */
};
typedef union bdk_pmux_pmpcsr_lo_alias bdk_pmux_pmpcsr_lo_alias_t;

static inline uint64_t BDK_PMUX_PMPCSR_LO_ALIAS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPCSR_LO_ALIAS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020220ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPCSR_LO_ALIAS", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPCSR_LO_ALIAS(a) bdk_pmux_pmpcsr_lo_alias_t
#define bustype_BDK_PMUX_PMPCSR_LO_ALIAS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPCSR_LO_ALIAS(a) "PMUX_PMPCSR_LO_ALIAS"
#define busnum_BDK_PMUX_PMPCSR_LO_ALIAS(a) (a)
#define arguments_BDK_PMUX_PMPCSR_LO_ALIAS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpidr0
 *
 * Performance Monitors Peripheral Identification Register 0
 * Provides information to identify a performance monitor
 *     component.
 */
union bdk_pmux_pmpidr0
{
    uint32_t u;
    struct bdk_pmux_pmpidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::PMU. */
#else /* Word 0 - Little Endian */
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::PMU. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpidr0_s cn; */
};
typedef union bdk_pmux_pmpidr0 bdk_pmux_pmpidr0_t;

static inline uint64_t BDK_PMUX_PMPIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPIDR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fe0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fe0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fe0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fe0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPIDR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPIDR0(a) bdk_pmux_pmpidr0_t
#define bustype_BDK_PMUX_PMPIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPIDR0(a) "PMUX_PMPIDR0"
#define busnum_BDK_PMUX_PMPIDR0(a) (a)
#define arguments_BDK_PMUX_PMPIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpidr1
 *
 * Performance Monitors Peripheral Identification Register 1
 * Provides information to identify a performance monitor
 *     component.
 */
union bdk_pmux_pmpidr1
{
    uint32_t u;
    struct bdk_pmux_pmpidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Cavium code is 0x4C. */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
#else /* Word 0 - Little Endian */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Cavium code is 0x4C. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpidr1_s cn; */
};
typedef union bdk_pmux_pmpidr1 bdk_pmux_pmpidr1_t;

static inline uint64_t BDK_PMUX_PMPIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPIDR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fe4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fe4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fe4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fe4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPIDR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPIDR1(a) bdk_pmux_pmpidr1_t
#define bustype_BDK_PMUX_PMPIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPIDR1(a) "PMUX_PMPIDR1"
#define busnum_BDK_PMUX_PMPIDR1(a) (a)
#define arguments_BDK_PMUX_PMPIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpidr2
 *
 * Performance Monitors Peripheral Identification Register 2
 * Provides information to identify a performance monitor
 *     component.
 */
union bdk_pmux_pmpidr2
{
    uint32_t u;
    struct bdk_pmux_pmpidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by ARM. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by ARM. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpidr2_s cn; */
};
typedef union bdk_pmux_pmpidr2 bdk_pmux_pmpidr2_t;

static inline uint64_t BDK_PMUX_PMPIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPIDR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fe8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fe8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fe8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fe8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPIDR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPIDR2(a) bdk_pmux_pmpidr2_t
#define bustype_BDK_PMUX_PMPIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPIDR2(a) "PMUX_PMPIDR2"
#define busnum_BDK_PMUX_PMPIDR2(a) (a)
#define arguments_BDK_PMUX_PMPIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpidr3
 *
 * Performance Monitors Peripheral Identification Register 3
 * Provides information to identify a performance monitor
 *     component.
 */
union bdk_pmux_pmpidr3
{
    uint32_t u;
    struct bdk_pmux_pmpidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer modified. 0x1 = Overall product information should be consulted for
                                                                 product, major and minor pass numbers. */
#else /* Word 0 - Little Endian */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer modified. 0x1 = Overall product information should be consulted for
                                                                 product, major and minor pass numbers. */
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpidr3_s cn; */
};
typedef union bdk_pmux_pmpidr3 bdk_pmux_pmpidr3_t;

static inline uint64_t BDK_PMUX_PMPIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPIDR3(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fecll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fecll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fecll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fecll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPIDR3", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPIDR3(a) bdk_pmux_pmpidr3_t
#define bustype_BDK_PMUX_PMPIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPIDR3(a) "PMUX_PMPIDR3"
#define busnum_BDK_PMUX_PMPIDR3(a) (a)
#define arguments_BDK_PMUX_PMPIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpidr4
 *
 * Performance Monitors Peripheral Identification Register 4
 * Provides information to identify a performance monitor
 *     component.
 */
union bdk_pmux_pmpidr4
{
    uint32_t u;
    struct bdk_pmux_pmpidr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t size                  : 4;  /**< [  7:  4](RO) Size of the component. Log2 of the number of
                                                                     4 KB pages from the start of the component to the end of the
                                                                     component ID registers. */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
#else /* Word 0 - Little Endian */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
        uint32_t size                  : 4;  /**< [  7:  4](RO) Size of the component. Log2 of the number of
                                                                     4 KB pages from the start of the component to the end of the
                                                                     component ID registers. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpidr4_s cn; */
};
typedef union bdk_pmux_pmpidr4 bdk_pmux_pmpidr4_t;

static inline uint64_t BDK_PMUX_PMPIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPIDR4(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fd0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fd0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fd0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fd0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPIDR4", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPIDR4(a) bdk_pmux_pmpidr4_t
#define bustype_BDK_PMUX_PMPIDR4(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPIDR4(a) "PMUX_PMPIDR4"
#define busnum_BDK_PMUX_PMPIDR4(a) (a)
#define arguments_BDK_PMUX_PMPIDR4(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpidr5
 *
 * Performance Monitors Peripheral Identification Register 5
 */
union bdk_pmux_pmpidr5
{
    uint32_t u;
    struct bdk_pmux_pmpidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpidr5_s cn; */
};
typedef union bdk_pmux_pmpidr5 bdk_pmux_pmpidr5_t;

static inline uint64_t BDK_PMUX_PMPIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPIDR5(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fd4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fd4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fd4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fd4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPIDR5", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPIDR5(a) bdk_pmux_pmpidr5_t
#define bustype_BDK_PMUX_PMPIDR5(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPIDR5(a) "PMUX_PMPIDR5"
#define busnum_BDK_PMUX_PMPIDR5(a) (a)
#define arguments_BDK_PMUX_PMPIDR5(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpidr6
 *
 * Performance Monitors Peripheral Identification Register 6
 */
union bdk_pmux_pmpidr6
{
    uint32_t u;
    struct bdk_pmux_pmpidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpidr6_s cn; */
};
typedef union bdk_pmux_pmpidr6 bdk_pmux_pmpidr6_t;

static inline uint64_t BDK_PMUX_PMPIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPIDR6(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fd8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fd8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fd8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fd8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPIDR6", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPIDR6(a) bdk_pmux_pmpidr6_t
#define bustype_BDK_PMUX_PMPIDR6(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPIDR6(a) "PMUX_PMPIDR6"
#define busnum_BDK_PMUX_PMPIDR6(a) (a)
#define arguments_BDK_PMUX_PMPIDR6(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmpidr7
 *
 * Performance Monitors Peripheral Identification Register 7
 */
union bdk_pmux_pmpidr7
{
    uint32_t u;
    struct bdk_pmux_pmpidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmpidr7_s cn; */
};
typedef union bdk_pmux_pmpidr7 bdk_pmux_pmpidr7_t;

static inline uint64_t BDK_PMUX_PMPIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMPIDR7(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020fdcll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020fdcll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020fdcll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020fdcll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMPIDR7", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMPIDR7(a) bdk_pmux_pmpidr7_t
#define bustype_BDK_PMUX_PMPIDR7(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMPIDR7(a) "PMUX_PMPIDR7"
#define busnum_BDK_PMUX_PMPIDR7(a) (a)
#define arguments_BDK_PMUX_PMPIDR7(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmswinc_el0
 *
 * Performance Monitors Software Increment Register
 * Increments a counter that is configured to count the software
 *     increment event, event0x00.
 */
union bdk_pmux_pmswinc_el0
{
    uint32_t u;
    struct bdk_pmux_pmswinc_el0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t p                     : 31; /**< [ 30:  0](RO) Event counter software increment bit for PMEVCNTR\<x\>.
                                                                 P\<x\> is WI if x \>= PMU()_PMCR_EL0[N], the number of implemented
                                                                     counters.
                                                                 Otherwise, the effects of writing to this bit are:
                                                                 0 = No action. The write to this bit is ignored.
                                                                 1 = It is CONSTRAINED UNPREDICTABLE whether a SW_INCR event is
                                                                     generated for event counter x. */
#else /* Word 0 - Little Endian */
        uint32_t p                     : 31; /**< [ 30:  0](RO) Event counter software increment bit for PMEVCNTR\<x\>.
                                                                 P\<x\> is WI if x \>= PMU()_PMCR_EL0[N], the number of implemented
                                                                     counters.
                                                                 Otherwise, the effects of writing to this bit are:
                                                                 0 = No action. The write to this bit is ignored.
                                                                 1 = It is CONSTRAINED UNPREDICTABLE whether a SW_INCR event is
                                                                     generated for event counter x. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmswinc_el0_s cn; */
};
typedef union bdk_pmux_pmswinc_el0 bdk_pmux_pmswinc_el0_t;

static inline uint64_t BDK_PMUX_PMSWINC_EL0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMSWINC_EL0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008020ca0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008020ca0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008020ca0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008020ca0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMSWINC_EL0", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMSWINC_EL0(a) bdk_pmux_pmswinc_el0_t
#define bustype_BDK_PMUX_PMSWINC_EL0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMSWINC_EL0(a) "PMUX_PMSWINC_EL0"
#define busnum_BDK_PMUX_PMSWINC_EL0(a) (a)
#define arguments_BDK_PMUX_PMSWINC_EL0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) pmu#_pmvidsr
 *
 * AP Virtual Context Sample Register
 * Contains sampled values captured on reading PMPCSR.
 */
union bdk_pmux_pmvidsr
{
    uint32_t u;
    struct bdk_pmux_pmvidsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t vmid                  : 16; /**< [ 15:  0](RO) VMID sample. The value of VTTBR_EL2[VMID] associated with the
                                                                     most recent PMPCSR sample. If PMVIDSR[NS] = 0 or PMVIDSR[E2] =
                                                                     1, this field is 0x0. When the SC2 bit is set to zero, PMVIDSR[15:0]
                                                                     is extended to sample the 16-bit VMID if VTCR_EL2[VS] is set to one. */
#else /* Word 0 - Little Endian */
        uint32_t vmid                  : 16; /**< [ 15:  0](RO) VMID sample. The value of VTTBR_EL2[VMID] associated with the
                                                                     most recent PMPCSR sample. If PMVIDSR[NS] = 0 or PMVIDSR[E2] =
                                                                     1, this field is 0x0. When the SC2 bit is set to zero, PMVIDSR[15:0]
                                                                     is extended to sample the 16-bit VMID if VTCR_EL2[VS] is set to one. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pmux_pmvidsr_s cn; */
};
typedef union bdk_pmux_pmvidsr bdk_pmux_pmvidsr_t;

static inline uint64_t BDK_PMUX_PMVIDSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PMUX_PMVIDSR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a00802020cll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("PMUX_PMVIDSR", 1, a, 0, 0, 0);
}

#define typedef_BDK_PMUX_PMVIDSR(a) bdk_pmux_pmvidsr_t
#define bustype_BDK_PMUX_PMVIDSR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_PMUX_PMVIDSR(a) "PMUX_PMVIDSR"
#define busnum_BDK_PMUX_PMVIDSR(a) (a)
#define arguments_BDK_PMUX_PMVIDSR(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_DAB_PMU_H__ */
