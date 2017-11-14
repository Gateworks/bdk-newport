#ifndef __BDK_CSRS_DDF_H__
#define __BDK_CSRS_DDF_H__
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
 * Cavium DDF.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration ddf_bar_e
 *
 * DDF Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_DDF_BAR_E_DDFX_PF_BAR0(a) (0x809000000000ll + 0ll * (a))
#define BDK_DDF_BAR_E_DDFX_PF_BAR0_SIZE 0x10000000ull
#define BDK_DDF_BAR_E_DDFX_PF_BAR4(a) (0x809010000000ll + 0ll * (a))
#define BDK_DDF_BAR_E_DDFX_PF_BAR4_SIZE 0x100000ull
#define BDK_DDF_BAR_E_DDFX_VFX_BAR0(a,b) (0x809020000000ll + 0ll * (a) + 0x100000ll * (b))
#define BDK_DDF_BAR_E_DDFX_VFX_BAR0_SIZE 0x100000ull
#define BDK_DDF_BAR_E_DDFX_VFX_BAR4(a,b) (0x809030000000ll + 0ll * (a) + 0x100000ll * (b))
#define BDK_DDF_BAR_E_DDFX_VFX_BAR4_SIZE 0x100000ull

/**
 * Enumeration ddf_cacpart_e
 *
 * DDF Cache Partition Policy Enumeration
 * Enumerates the cache partition policy.
 */
#define BDK_DDF_CACPART_E_EVEN (1)
#define BDK_DDF_CACPART_E_GANG (3)
#define BDK_DDF_CACPART_E_NONE (0)
#define BDK_DDF_CACPART_E_NONGANG (2)

/**
 * Enumeration ddf_comp_e
 *
 * DDF Completion Status Enumeration
 * Enumerates the status values of DDF_RES_FIND_S/DDF_RES_MATCH_S[COMPCODE].
 */
#define BDK_DDF_COMP_E_FAULT (2)
#define BDK_DDF_COMP_E_FILTER_TOO_BIG (5)
#define BDK_DDF_COMP_E_FULL (3)
#define BDK_DDF_COMP_E_GOOD (1)
#define BDK_DDF_COMP_E_HDR_ALIGN (0xf)
#define BDK_DDF_COMP_E_HDR_LT_NEST (8)
#define BDK_DDF_COMP_E_HDR_TOO_BIG (6)
#define BDK_DDF_COMP_E_ILLEGAL_OPCODE (0x12)
#define BDK_DDF_COMP_E_ILLEGAL_QWORDS (4)
#define BDK_DDF_COMP_E_KEY_GT_NEST (9)
#define BDK_DDF_COMP_E_KEY_SIZE (0xa)
#define BDK_DDF_COMP_E_NOTDONE (0)
#define BDK_DDF_COMP_E_NO_HDR (0xc)
#define BDK_DDF_COMP_E_NO_RANK (0xb)
#define BDK_DDF_COMP_E_NO_RB (0xd)
#define BDK_DDF_COMP_E_RANK_ALIGN (0xe)
#define BDK_DDF_COMP_E_RB_ALIGN (0x10)
#define BDK_DDF_COMP_E_RES_ALIGN (0x11)
#define BDK_DDF_COMP_E_WAY_TOO_BIG (7)

/**
 * Enumeration ddf_op_e
 *
 * DDF Instruction Operation Enumeration
 * Enumerates the values of DDF_INST_FIND_S[OP]/DDF_INST_MATCH_S[OP].
 */
#define BDK_DDF_OP_E_FABS_SET (0x18)
#define BDK_DDF_OP_E_FEMPTY_INS (0x1f)
#define BDK_DDF_OP_E_FIND (0x10)
#define BDK_DDF_OP_E_FIND_DEL (0x13)
#define BDK_DDF_OP_E_FIND_INS (0x12)
#define BDK_DDF_OP_E_FIND_SET (0x11)
#define BDK_DDF_OP_E_MATCH (0x20)
#define BDK_DDF_OP_E_MATCH_DEL (0x23)
#define BDK_DDF_OP_E_MATCH_INS (0x22)
#define BDK_DDF_OP_E_MATCH_SET (0x21)
#define BDK_DDF_OP_E_NOP (0)
#define BDK_DDF_OP_E_RABS_SET (0x28)
#define BDK_DDF_OP_E_REMPTY_INS (0x2f)

/**
 * Enumeration ddf_pf_int_vec_e
 *
 * DDF PF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_DDF_PF_INT_VEC_E_ECC0 (0)
#define BDK_DDF_PF_INT_VEC_E_MBOXX(a) (3 + (a))
#define BDK_DDF_PF_INT_VEC_E_NOINT0 (1)
#define BDK_DDF_PF_INT_VEC_E_NOINT1 (2)

/**
 * Enumeration ddf_rams_e
 *
 * DDF RAM Field Enumeration
 * Enumerates the relative bit positions within DDF()_PF_ECC0_CTL[CDIS].
 */
#define BDK_DDF_RAMS_E_COMP_FIFO (0xf)
#define BDK_DDF_RAMS_E_CQM_BPTR (3)
#define BDK_DDF_RAMS_E_CQM_CTLMEM (2)
#define BDK_DDF_RAMS_E_CQM_DONE_CNT (0xd)
#define BDK_DDF_RAMS_E_CQM_DONE_TIMER (0xe)
#define BDK_DDF_RAMS_E_CQM_GMID (4)
#define BDK_DDF_RAMS_E_CQM_INSTFIF0 (5)
#define BDK_DDF_RAMS_E_CQM_INSTFIF1 (6)
#define BDK_DDF_RAMS_E_CQM_INSTFIF2 (7)
#define BDK_DDF_RAMS_E_CQM_INSTFIF3 (8)
#define BDK_DDF_RAMS_E_CQM_INSTFIF4 (9)
#define BDK_DDF_RAMS_E_CQM_INSTFIF5 (0xa)
#define BDK_DDF_RAMS_E_CQM_INSTFIF6 (0xb)
#define BDK_DDF_RAMS_E_CQM_INSTFIF7 (0xc)
#define BDK_DDF_RAMS_E_DMEM0 (0x12)
#define BDK_DDF_RAMS_E_DMEM1 (0x13)
#define BDK_DDF_RAMS_E_FPA_MEM (0x11)
#define BDK_DDF_RAMS_E_LFIFO0 (0x14)
#define BDK_DDF_RAMS_E_LFIFO1 (0x15)
#define BDK_DDF_RAMS_E_MBOX_MEM (0x10)
#define BDK_DDF_RAMS_E_MSIX_VMEM (0x16)
#define BDK_DDF_RAMS_E_NCBI_DATFIF (0)
#define BDK_DDF_RAMS_E_NCBO_MEM0 (1)

/**
 * Enumeration ddf_res_type_e
 *
 * DDF Result Type Enumeration
 * Enumerates the values of DDF_RES_MATCH_S[RES_TYPE] and DDF_RES_FIND_S[RES_TYPE].
 */
#define BDK_DDF_RES_TYPE_E_FIND (1)
#define BDK_DDF_RES_TYPE_E_MATCH (2)
#define BDK_DDF_RES_TYPE_E_NOP (0)

/**
 * Enumeration ddf_vf_int_vec_e
 *
 * DDF VF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_DDF_VF_INT_VEC_E_DONE (1)
#define BDK_DDF_VF_INT_VEC_E_MISC (0)

/**
 * Structure ddf_inst_find_s
 *
 * DDF Find Instruction Structure
 * This structure specifies the find instruction. Instructions are stored in memory as
 * little-endian unless DDF()_PF_Q()_CTL[INST_BE] is set.
 */
union bdk_ddf_inst_find_s
{
    uint64_t u[16];
    struct bdk_ddf_inst_find_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t rank_abs              : 1;  /**< [ 55: 55] Absolute rank.
                                                                 0 = [HDR_ADDR] and [RANK_ADDR] point to rank 0, and the rank used is calculated using rank
                                                                 bits from the key.
                                                                 1 = [HDR_ADDR] and [RANK_ADDR] point to an absolute rank. */
        uint64_t victen                : 1;  /**< [ 54: 54] Victim enable.
                                                                 _ 0 = No victim present in header, or do not operate on the victim.
                                                                 _ 1 and [OP]!=DDF_OP_E::FABS_SET: Check for victim in filter header and put in
                                                                 to header on add for overflow.
                                                                 _ 1 and [OP]=DDF_OP_E::FABS_SET: Modify the victim. */
        uint64_t nest                  : 2;  /**< [ 53: 52] Nest location. If [OP] = DDF_OP_E::FABS_SET, which nest number in the bucket,
                                                                 otherwise reserved. */
        uint64_t way_abs               : 1;  /**< [ 51: 51] Way is absolute.
                                                                 0 = Search/delete from any way, insert into [WAY].
                                                                 1 = Search/insert/delete only in the way provided in [WAY]. */
        uint64_t way                   : 3;  /**< [ 50: 48] Which way number. If [OP] = DDF_OP_E::FIND_INS or DDF_OP_E::FEMPTY_INS or
                                                                 DDF_OP_E::FABS_SET, or [WAY_ABS] is set, which way number, otherwise ignored. */
        uint64_t reserved_22_47        : 26;
        uint64_t rr                    : 1;  /**< [ 21: 21] Return result. If set, include key data in DDF_RES_FIND_S. */
        uint64_t cacs                  : 1;  /**< [ 20: 20] L2 cache filter data. If set, when reading the filter data, allocate into L2 cache using
                                                                 the LD command specified in PF_Q()_CTL2[D_LD_CMD]. If clear, do not allocate if not
                                                                 already
                                                                 in L2 cache and use the LDT load command. */
        uint64_t cach                  : 1;  /**< [ 19: 19] L2 cache header. If set, when reading the header, allocate into L2 cache using the LD
                                                                 command specified in PF_Q()_CTL2[D_LD_CMD].
                                                                 If clear, do not allocate if not already in L2 cache and use the LDT load command. */
        uint64_t sync                  : 1;  /**< [ 18: 18] Synchronize. If set, insure all structures
                                                                 are written to memory before completing this instruction. */
        uint64_t gang                  : 1;  /**< [ 17: 17] Gang with next instruction. If set, a hint to hardware that this instruction's
                                                                 filter or match data need not be immediately written to memory, in the hope that
                                                                 the next instruction will access the same data. */
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, DDF()_VQ()_DONE[DONE] will be incremented,
                                                                 and based on the rules described there an interrupt may occur. */
        uint64_t qwords                : 8;  /**< [ 15:  8] Number of 8-byte quadwords in request. Must be 1-16. If less than the size of
                                                                 this structure then structure elements described here are not interpreted from
                                                                 memory and behave as if zero.

                                                                 Internal:
                                                                 In hardware, push/pop zeros for (QWORDS..15) into the
                                                                 instruction queue.  As VQs are virtualized, DDF must not hang on invalid instructions. */
        uint64_t op                    : 8;  /**< [  7:  0] Operation to perform. Enumerated by DDF_OP_E. */
#else /* Word 0 - Little Endian */
        uint64_t op                    : 8;  /**< [  7:  0] Operation to perform. Enumerated by DDF_OP_E. */
        uint64_t qwords                : 8;  /**< [ 15:  8] Number of 8-byte quadwords in request. Must be 1-16. If less than the size of
                                                                 this structure then structure elements described here are not interpreted from
                                                                 memory and behave as if zero.

                                                                 Internal:
                                                                 In hardware, push/pop zeros for (QWORDS..15) into the
                                                                 instruction queue.  As VQs are virtualized, DDF must not hang on invalid instructions. */
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, DDF()_VQ()_DONE[DONE] will be incremented,
                                                                 and based on the rules described there an interrupt may occur. */
        uint64_t gang                  : 1;  /**< [ 17: 17] Gang with next instruction. If set, a hint to hardware that this instruction's
                                                                 filter or match data need not be immediately written to memory, in the hope that
                                                                 the next instruction will access the same data. */
        uint64_t sync                  : 1;  /**< [ 18: 18] Synchronize. If set, insure all structures
                                                                 are written to memory before completing this instruction. */
        uint64_t cach                  : 1;  /**< [ 19: 19] L2 cache header. If set, when reading the header, allocate into L2 cache using the LD
                                                                 command specified in PF_Q()_CTL2[D_LD_CMD].
                                                                 If clear, do not allocate if not already in L2 cache and use the LDT load command. */
        uint64_t cacs                  : 1;  /**< [ 20: 20] L2 cache filter data. If set, when reading the filter data, allocate into L2 cache using
                                                                 the LD command specified in PF_Q()_CTL2[D_LD_CMD]. If clear, do not allocate if not
                                                                 already
                                                                 in L2 cache and use the LDT load command. */
        uint64_t rr                    : 1;  /**< [ 21: 21] Return result. If set, include key data in DDF_RES_FIND_S. */
        uint64_t reserved_22_47        : 26;
        uint64_t way                   : 3;  /**< [ 50: 48] Which way number. If [OP] = DDF_OP_E::FIND_INS or DDF_OP_E::FEMPTY_INS or
                                                                 DDF_OP_E::FABS_SET, or [WAY_ABS] is set, which way number, otherwise ignored. */
        uint64_t way_abs               : 1;  /**< [ 51: 51] Way is absolute.
                                                                 0 = Search/delete from any way, insert into [WAY].
                                                                 1 = Search/insert/delete only in the way provided in [WAY]. */
        uint64_t nest                  : 2;  /**< [ 53: 52] Nest location. If [OP] = DDF_OP_E::FABS_SET, which nest number in the bucket,
                                                                 otherwise reserved. */
        uint64_t victen                : 1;  /**< [ 54: 54] Victim enable.
                                                                 _ 0 = No victim present in header, or do not operate on the victim.
                                                                 _ 1 and [OP]!=DDF_OP_E::FABS_SET: Check for victim in filter header and put in
                                                                 to header on add for overflow.
                                                                 _ 1 and [OP]=DDF_OP_E::FABS_SET: Modify the victim. */
        uint64_t rank_abs              : 1;  /**< [ 55: 55] Absolute rank.
                                                                 0 = [HDR_ADDR] and [RANK_ADDR] point to rank 0, and the rank used is calculated using rank
                                                                 bits from the key.
                                                                 1 = [HDR_ADDR] and [RANK_ADDR] point to an absolute rank. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write DDF_RES_FIND_S.
                                                                 If zero, no result structure will be written.

                                                                 If [RR] is clear, address must be 16-byte aligned.
                                                                 If [RR] is set, address must be 128-byte aligned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#else /* Word 1 - Little Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write DDF_RES_FIND_S.
                                                                 If zero, no result structure will be written.

                                                                 If [RR] is clear, address must be 16-byte aligned.
                                                                 If [RR] is set, address must be 128-byte aligned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t tag_rank              : 5;  /**< [191:187] If set, extract [TAG_RANK] number of bits from the computed rank number and
                                                                 exclusive-or into the SSO TAG. If [RANK_ABS]=1 computed rank number is 0.
                                                                    0x00: SSO tag = [TAG] ^ {0x0}.
                                                                    0x01: SSO tag = [TAG] ^ {DDF_RES_FIND_S[RANK]\<0\>}.
                                                                    ...
                                                                    0x1F: SSO tag = [TAG] ^ {DDF_RES_FIND_S[RANK]\<30:0\>}. */
        uint64_t reserved_172_186      : 15;
        uint64_t grp                   : 10; /**< [171:162] If [WQ_PTR] is nonzero, the SSO guest-group to use when DDF submits work to
                                                                 SSO.
                                                                 For the SSO to not discard the add-work request, FPA_PF_MAP() must map
                                                                 [GRP] and DDF()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t tt                    : 2;  /**< [161:160] If [WQ_PTR] is nonzero, the SSO tag type to use when DDF submits work to SSO. */
        uint64_t tag                   : 32; /**< [159:128] If [WQ_PTR] is nonzero, the SSO tag to use when DDF submits work to SSO. */
#else /* Word 2 - Little Endian */
        uint64_t tag                   : 32; /**< [159:128] If [WQ_PTR] is nonzero, the SSO tag to use when DDF submits work to SSO. */
        uint64_t tt                    : 2;  /**< [161:160] If [WQ_PTR] is nonzero, the SSO tag type to use when DDF submits work to SSO. */
        uint64_t grp                   : 10; /**< [171:162] If [WQ_PTR] is nonzero, the SSO guest-group to use when DDF submits work to
                                                                 SSO.
                                                                 For the SSO to not discard the add-work request, FPA_PF_MAP() must map
                                                                 [GRP] and DDF()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t reserved_172_186      : 15;
        uint64_t tag_rank              : 5;  /**< [191:187] If set, extract [TAG_RANK] number of bits from the computed rank number and
                                                                 exclusive-or into the SSO TAG. If [RANK_ABS]=1 computed rank number is 0.
                                                                    0x00: SSO tag = [TAG] ^ {0x0}.
                                                                    0x01: SSO tag = [TAG] ^ {DDF_RES_FIND_S[RANK]\<0\>}.
                                                                    ...
                                                                    0x1F: SSO tag = [TAG] ^ {DDF_RES_FIND_S[RANK]\<30:0\>}. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that DDF submits
                                                                 work to SSO after all context, output data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:49\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<48\> for forward compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#else /* Word 3 - Little Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that DDF submits
                                                                 work to SSO after all context, output data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:49\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<48\> for forward compatibility.

                                                                 Internal:
                                                                 Bits \<63:49\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reserved_288_319      : 32;
        uint64_t set_bdis              : 32; /**< [287:256] Set byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA3] byte. If
                                                                 that bit is clear the corresponding byte will be set in the record. Only bits
                                                                 [SET_BDIS]\<NESTSZM1:0\> have an effect on nests and on the lower 2^[NESTSZP2]
                                                                 bytes of the header. Bucket fields of the nest and header are not settable. */
#else /* Word 4 - Little Endian */
        uint64_t set_bdis              : 32; /**< [287:256] Set byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA3] byte. If
                                                                 that bit is clear the corresponding byte will be set in the record. Only bits
                                                                 [SET_BDIS]\<NESTSZM1:0\> have an effect on nests and on the lower 2^[NESTSZP2]
                                                                 bytes of the header. Bucket fields of the nest and header are not settable. */
        uint64_t reserved_288_319      : 32;
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_380_383      : 4;
        uint64_t nwayp2                : 2;  /**< [379:378] Number of ways as power-of-2.
                                                                    0x0 = 1 way.
                                                                    0x1 = 2 ways.
                                                                    0x2 = 4 ways.
                                                                    0x3 = 8 ways. */
        uint64_t hdrszp2               : 3;  /**< [377:375] Size of a single-way's filter header as power-of-2.
                                                                    0x0 = Reserved. (Hardware treats as 0x1).
                                                                    0x1 = 2 bytes.
                                                                    0x2 = 4 bytes.
                                                                    0x3 = 8 bytes.
                                                                    0x4 = 16 bytes.
                                                                    0x5 = 32 bytes. (See note - must have 1, 2 or 4 ways).
                                                                    0x6 = 64 bytes. (See note - must have 1 or 2 ways).
                                                                    0x7 = Reserved. (Hardware treats as 0x6).

                                                                 The size of a header for all ways (2^[NWAYP2])*(2^[HDRSZP2]) cannot be larger than 128
                                                                 bytes.

                                                                 2^[HDRSZP2] must be \>= (2^[NESTSZP2]) + ceiling([NBUCKP2]/8).

                                                                 If [VICTEN] is clear, this is ignored. */
        uint64_t nestszp2              : 3;  /**< [374:372] Size of a nest entry as power-of-2.
                                                                    0x0 = Reserved.
                                                                    0x1 = 2 bytes.
                                                                    0x2 = 4 bytes.
                                                                    0x3 = 8 bytes.
                                                                    0x4 = 16 bytes.
                                                                    0x5 = 32 bytes.
                                                                    0x6 = Reserved.
                                                                    0x7 = Reserved.

                                                                 The total size of a filter, e.g. (2^[NBUCKP2]) * 4 * 2^[NESTSZP2]) cannot be
                                                                 larger than 512 bytes. Reserved values default to 0x1.

                                                                 The size of a bucket, e.g. 4 * (2^[NESTSZP2]) cannot be larger than 128 bytes.

                                                                 Internal:
                                                                 This means a 32-byte SHA256 cannot have any payload (software must use separate
                                                                 table). Limiting to 32 byte nests means all 4 nests fit in a cache line. */
        uint64_t reserved_371          : 1;
        uint64_t nbuckp2               : 3;  /**< [370:368] Number of buckets per filter as a power-of-2.
                                                                   0x0 = 1 bucket/filter.
                                                                   0x1 = 2^1 = 2 buckets/filter.
                                                                   0x2 = 2^2 = 4 buckets/filter.
                                                                   0x3 = 2^3 = 8 buckets/filter.
                                                                   0x4 = 2^4 = 16 buckets/filter.
                                                                   0x5 = 2^5 = 32 buckets/filter.
                                                                   0x6 = 2^6 = 64 buckets/filter.
                                                                   0x7 = Reserved. (Hardware treats as 0x6).

                                                                 The total size of a filter, e.g. (2^[NBUCKP2])*4*2^[NESTSZP2]) cannot be larger than 512
                                                                 bytes. */
        uint64_t tagbitsm1             : 8;  /**< [367:360] Number of tag bits minus one. Maximum of 0xFF corresponds to a complete 256 bit key. */
        uint64_t reserved_359          : 1;
        uint64_t cuckoo                : 7;  /**< [358:352] Cuckoo retries.
                                                                 For [OP] = DDF_OP_E::FIND_INS, the the number of times to perform cuckoo replacements.
                                                                 0x0 disables retrying.  For a filter of 64 buckets, 64 would be a typical maximum. */
        uint64_t nrankm1               : 32; /**< [351:320] Number of ranks minus one. Does not need to be a power-of-2. */
#else /* Word 5 - Little Endian */
        uint64_t nrankm1               : 32; /**< [351:320] Number of ranks minus one. Does not need to be a power-of-2. */
        uint64_t cuckoo                : 7;  /**< [358:352] Cuckoo retries.
                                                                 For [OP] = DDF_OP_E::FIND_INS, the the number of times to perform cuckoo replacements.
                                                                 0x0 disables retrying.  For a filter of 64 buckets, 64 would be a typical maximum. */
        uint64_t reserved_359          : 1;
        uint64_t tagbitsm1             : 8;  /**< [367:360] Number of tag bits minus one. Maximum of 0xFF corresponds to a complete 256 bit key. */
        uint64_t nbuckp2               : 3;  /**< [370:368] Number of buckets per filter as a power-of-2.
                                                                   0x0 = 1 bucket/filter.
                                                                   0x1 = 2^1 = 2 buckets/filter.
                                                                   0x2 = 2^2 = 4 buckets/filter.
                                                                   0x3 = 2^3 = 8 buckets/filter.
                                                                   0x4 = 2^4 = 16 buckets/filter.
                                                                   0x5 = 2^5 = 32 buckets/filter.
                                                                   0x6 = 2^6 = 64 buckets/filter.
                                                                   0x7 = Reserved. (Hardware treats as 0x6).

                                                                 The total size of a filter, e.g. (2^[NBUCKP2])*4*2^[NESTSZP2]) cannot be larger than 512
                                                                 bytes. */
        uint64_t reserved_371          : 1;
        uint64_t nestszp2              : 3;  /**< [374:372] Size of a nest entry as power-of-2.
                                                                    0x0 = Reserved.
                                                                    0x1 = 2 bytes.
                                                                    0x2 = 4 bytes.
                                                                    0x3 = 8 bytes.
                                                                    0x4 = 16 bytes.
                                                                    0x5 = 32 bytes.
                                                                    0x6 = Reserved.
                                                                    0x7 = Reserved.

                                                                 The total size of a filter, e.g. (2^[NBUCKP2]) * 4 * 2^[NESTSZP2]) cannot be
                                                                 larger than 512 bytes. Reserved values default to 0x1.

                                                                 The size of a bucket, e.g. 4 * (2^[NESTSZP2]) cannot be larger than 128 bytes.

                                                                 Internal:
                                                                 This means a 32-byte SHA256 cannot have any payload (software must use separate
                                                                 table). Limiting to 32 byte nests means all 4 nests fit in a cache line. */
        uint64_t hdrszp2               : 3;  /**< [377:375] Size of a single-way's filter header as power-of-2.
                                                                    0x0 = Reserved. (Hardware treats as 0x1).
                                                                    0x1 = 2 bytes.
                                                                    0x2 = 4 bytes.
                                                                    0x3 = 8 bytes.
                                                                    0x4 = 16 bytes.
                                                                    0x5 = 32 bytes. (See note - must have 1, 2 or 4 ways).
                                                                    0x6 = 64 bytes. (See note - must have 1 or 2 ways).
                                                                    0x7 = Reserved. (Hardware treats as 0x6).

                                                                 The size of a header for all ways (2^[NWAYP2])*(2^[HDRSZP2]) cannot be larger than 128
                                                                 bytes.

                                                                 2^[HDRSZP2] must be \>= (2^[NESTSZP2]) + ceiling([NBUCKP2]/8).

                                                                 If [VICTEN] is clear, this is ignored. */
        uint64_t nwayp2                : 2;  /**< [379:378] Number of ways as power-of-2.
                                                                    0x0 = 1 way.
                                                                    0x1 = 2 ways.
                                                                    0x2 = 4 ways.
                                                                    0x3 = 8 ways. */
        uint64_t reserved_380_383      : 4;
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t hdr_addr              : 64; /**< [447:384] Header IOVA. Must be nonzero when [VICTEN] is set, otherwise reserved. Must be aligned to
                                                                 a 2^[NWAYP2 + HDRSZP2] byte boundary, minimum alignment of 4 bytes.

                                                                 If [RANK_ABS]=0, points to rank 0 way 0's header. Hardware accesses the way 0
                                                                 header at address [HDR_ADDR] + computed_rank * (2^[NWAYP2]) * (2^[HDRSZP2]).

                                                                 If [RANK_ABS]=1, points to the desired rank's way 0 header. Hardware accesses
                                                                 the way 0 header at address [HDR_ADDR].

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#else /* Word 6 - Little Endian */
        uint64_t hdr_addr              : 64; /**< [447:384] Header IOVA. Must be nonzero when [VICTEN] is set, otherwise reserved. Must be aligned to
                                                                 a 2^[NWAYP2 + HDRSZP2] byte boundary, minimum alignment of 4 bytes.

                                                                 If [RANK_ABS]=0, points to rank 0 way 0's header. Hardware accesses the way 0
                                                                 header at address [HDR_ADDR] + computed_rank * (2^[NWAYP2]) * (2^[HDRSZP2]).

                                                                 If [RANK_ABS]=1, points to the desired rank's way 0 header. Hardware accesses
                                                                 the way 0 header at address [HDR_ADDR].

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t rank_addr             : 64; /**< [511:448] Must be nonzero. Must be aligned to a 2^[NBUCKP2+NESTSZP2+2] byte boundary, minimum
                                                                 alignment of 16 bytes.

                                                                 If [RANK_ABS]=0, IOVA for rank 0, bucket 0, way 0, nest 0.

                                                                 If [RANK_ABS]=1, IOVA for precise rank, bucket 0, way 0, nest 0.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#else /* Word 7 - Little Endian */
        uint64_t rank_addr             : 64; /**< [511:448] Must be nonzero. Must be aligned to a 2^[NBUCKP2+NESTSZP2+2] byte boundary, minimum
                                                                 alignment of 16 bytes.

                                                                 If [RANK_ABS]=0, IOVA for rank 0, bucket 0, way 0, nest 0.

                                                                 If [RANK_ABS]=1, IOVA for precise rank, bucket 0, way 0, nest 0.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t keydata0              : 64; /**< [575:512] Key or opaque data bytes. */
#else /* Word 8 - Little Endian */
        uint64_t keydata0              : 64; /**< [575:512] Key or opaque data bytes. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t keydata1              : 64; /**< [639:576] Extension of [KEYDATA0]. */
#else /* Word 9 - Little Endian */
        uint64_t keydata1              : 64; /**< [639:576] Extension of [KEYDATA0]. */
#endif /* Word 9 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 10 - Big Endian */
        uint64_t keydata2              : 64; /**< [703:640] Extension of [KEYDATA0]. */
#else /* Word 10 - Little Endian */
        uint64_t keydata2              : 64; /**< [703:640] Extension of [KEYDATA0]. */
#endif /* Word 10 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 11 - Big Endian */
        uint64_t keydata3              : 64; /**< [767:704] Extension of [KEYDATA0]. */
#else /* Word 11 - Little Endian */
        uint64_t keydata3              : 64; /**< [767:704] Extension of [KEYDATA0]. */
#endif /* Word 11 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 12 - Big Endian */
        uint64_t reserved_768_831      : 64;
#else /* Word 12 - Little Endian */
        uint64_t reserved_768_831      : 64;
#endif /* Word 12 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 13 - Big Endian */
        uint64_t reserved_832_895      : 64;
#else /* Word 13 - Little Endian */
        uint64_t reserved_832_895      : 64;
#endif /* Word 13 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 14 - Big Endian */
        uint64_t reserved_896_959      : 64;
#else /* Word 14 - Little Endian */
        uint64_t reserved_896_959      : 64;
#endif /* Word 14 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 15 - Big Endian */
        uint64_t reserved_960_1023     : 64;
#else /* Word 15 - Little Endian */
        uint64_t reserved_960_1023     : 64;
#endif /* Word 15 - End */
    } s;
    /* struct bdk_ddf_inst_find_s_s cn; */
};

/**
 * Structure ddf_inst_match_s
 *
 * DDF Record Match Instruction Structure
 * This structure specifies the record-match instruction. Instructions are stored in
 * memory as little-endian unless DDF()_PF_Q()_CTL[INST_BE] is set.
 */
union bdk_ddf_inst_match_s
{
    uint64_t u[16];
    struct bdk_ddf_inst_match_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nrec                  : 16; /**< [ 63: 48] Number of records to compare.
                                                                 Typically the same as the number of records in a record block.
                                                                 If 0x0, compare nothing and return DDF_COMP_E::NO_RB. */
        uint64_t recszm1               : 8;  /**< [ 47: 40] Record size in bytes minus one.  Number of bytes must be multiple of 4
                                                                 and are not required to be powers of 2. Hardware enforces bits 1:0 are set and bits 7:6
                                                                 are clear.

                                                                 0x3 = 4 bytes.
                                                                 0x7 = 8 bytes.
                                                                 0xF = 16 bytes.
                                                                 0x13 = 20 bytes.
                                                                 0x17 = 24 bytes.
                                                                 _ ...
                                                                 0x3F = 64 bytes.

                                                                 Internal:
                                                                 Must support non-power-of-2. */
        uint64_t reserved_23_39        : 17;
        uint64_t multm                 : 1;  /**< [ 22: 22] Multiple matches, applies to DDF_INST_MATCH_S::MATCH_SET,MATCH_INS,MATCH_DEL.

                                                                 0 = A match is only expected in one record. Once a record is found to match, ignore
                                                                 further comparisons.

                                                                 1 = A match may occur in multiple records. If a record is found to match, continue to
                                                                 compare or update all records in all record-sets.

                                                                 For MATCH_INS on an empty record, only 1 record is inserted. */
        uint64_t rr                    : 1;  /**< [ 21: 21] Return result. If set, include key data in DDF_RES_MATCH_S. */
        uint64_t cacr                  : 1;  /**< [ 20: 20] L2 cache record data. If set, when reading record data, allocate into L2 cache using the
                                                                 LD command specified in PF_Q()_CTL2[D_LD_CMD]. If clear, do not allocate if not already in
                                                                 L2 cache and use the LDT load command. */
        uint64_t reserved_19           : 1;
        uint64_t sync                  : 1;  /**< [ 18: 18] See DDF_INST_FIND_S[SYNC]. */
        uint64_t gang                  : 1;  /**< [ 17: 17] See DDF_INST_FIND_S[GANG]. */
        uint64_t doneint               : 1;  /**< [ 16: 16] See DDF_INST_FIND_S[DONEINT]. */
        uint64_t qwords                : 8;  /**< [ 15:  8] See DDF_INST_FIND_S[QWORDS]. */
        uint64_t op                    : 8;  /**< [  7:  0] See DDF_INST_FIND_S[OP]. */
#else /* Word 0 - Little Endian */
        uint64_t op                    : 8;  /**< [  7:  0] See DDF_INST_FIND_S[OP]. */
        uint64_t qwords                : 8;  /**< [ 15:  8] See DDF_INST_FIND_S[QWORDS]. */
        uint64_t doneint               : 1;  /**< [ 16: 16] See DDF_INST_FIND_S[DONEINT]. */
        uint64_t gang                  : 1;  /**< [ 17: 17] See DDF_INST_FIND_S[GANG]. */
        uint64_t sync                  : 1;  /**< [ 18: 18] See DDF_INST_FIND_S[SYNC]. */
        uint64_t reserved_19           : 1;
        uint64_t cacr                  : 1;  /**< [ 20: 20] L2 cache record data. If set, when reading record data, allocate into L2 cache using the
                                                                 LD command specified in PF_Q()_CTL2[D_LD_CMD]. If clear, do not allocate if not already in
                                                                 L2 cache and use the LDT load command. */
        uint64_t rr                    : 1;  /**< [ 21: 21] Return result. If set, include key data in DDF_RES_MATCH_S. */
        uint64_t multm                 : 1;  /**< [ 22: 22] Multiple matches, applies to DDF_INST_MATCH_S::MATCH_SET,MATCH_INS,MATCH_DEL.

                                                                 0 = A match is only expected in one record. Once a record is found to match, ignore
                                                                 further comparisons.

                                                                 1 = A match may occur in multiple records. If a record is found to match, continue to
                                                                 compare or update all records in all record-sets.

                                                                 For MATCH_INS on an empty record, only 1 record is inserted. */
        uint64_t reserved_23_39        : 17;
        uint64_t recszm1               : 8;  /**< [ 47: 40] Record size in bytes minus one.  Number of bytes must be multiple of 4
                                                                 and are not required to be powers of 2. Hardware enforces bits 1:0 are set and bits 7:6
                                                                 are clear.

                                                                 0x3 = 4 bytes.
                                                                 0x7 = 8 bytes.
                                                                 0xF = 16 bytes.
                                                                 0x13 = 20 bytes.
                                                                 0x17 = 24 bytes.
                                                                 _ ...
                                                                 0x3F = 64 bytes.

                                                                 Internal:
                                                                 Must support non-power-of-2. */
        uint64_t nrec                  : 16; /**< [ 63: 48] Number of records to compare.
                                                                 Typically the same as the number of records in a record block.
                                                                 If 0x0, compare nothing and return DDF_COMP_E::NO_RB. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write DDF_RES_MATCH_S.
                                                                 If zero, no result structure will be written.

                                                                 If [RR] is clear, address must be 16-byte aligned.
                                                                 If [RR] is set, address must be 128-byte aligned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#else /* Word 1 - Little Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write DDF_RES_MATCH_S.
                                                                 If zero, no result structure will be written.

                                                                 If [RR] is clear, address must be 16-byte aligned.
                                                                 If [RR] is set, address must be 128-byte aligned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_172_191      : 20;
        uint64_t grp                   : 10; /**< [171:162] See DDF_INST_FIND_S[GRP]. */
        uint64_t tt                    : 2;  /**< [161:160] See DDF_INST_FIND_S[TT]. */
        uint64_t tag                   : 32; /**< [159:128] See DDF_INST_FIND_S[TAG]. */
#else /* Word 2 - Little Endian */
        uint64_t tag                   : 32; /**< [159:128] See DDF_INST_FIND_S[TAG]. */
        uint64_t tt                    : 2;  /**< [161:160] See DDF_INST_FIND_S[TT]. */
        uint64_t grp                   : 10; /**< [171:162] See DDF_INST_FIND_S[GRP]. */
        uint64_t reserved_172_191      : 20;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] See DDF_INST_FIND_S[WQ_PTR]. */
#else /* Word 3 - Little Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] See DDF_INST_FIND_S[WQ_PTR]. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t rb_addr               : 64; /**< [319:256] Record block IOVA.
                                                                 For DDF_OP_E::RABS_SET instruction, pointer to data to change.
                                                                 Must be aligned to DDF_INST_MATCH_S[RECSZM1]+1 bytes.
                                                                 If 0x0, this record block is not used, and DDF_COMP_E::NO_RB is returned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility.
                                                                 Bits \<1:0\> are ignored by hardware and assumed to be 0. */
#else /* Word 4 - Little Endian */
        uint64_t rb_addr               : 64; /**< [319:256] Record block IOVA.
                                                                 For DDF_OP_E::RABS_SET instruction, pointer to data to change.
                                                                 Must be aligned to DDF_INST_MATCH_S[RECSZM1]+1 bytes.
                                                                 If 0x0, this record block is not used, and DDF_COMP_E::NO_RB is returned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility.
                                                                 Bits \<1:0\> are ignored by hardware and assumed to be 0. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_320_383      : 64;
#else /* Word 5 - Little Endian */
        uint64_t reserved_320_383      : 64;
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t set_bdis              : 64; /**< [447:384] Set byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA7] byte. If
                                                                 that bit is clear the corresponding byte will be set in the record. Only bits
                                                                 [SET_BDIS]\<RECSZM1:0\> have an effect. */
#else /* Word 6 - Little Endian */
        uint64_t set_bdis              : 64; /**< [447:384] Set byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA7] byte. If
                                                                 that bit is clear the corresponding byte will be set in the record. Only bits
                                                                 [SET_BDIS]\<RECSZM1:0\> have an effect. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t cmp_bdis              : 64; /**< [511:448] Compare byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA7]
                                                                 byte. If that clear is set the corresponding byte must be identical to that byte
                                                                 in the record to be considered a match. Only bits [CMP_BDIS]\<RECSZM1:0\> have an
                                                                 effect. */
#else /* Word 7 - Little Endian */
        uint64_t cmp_bdis              : 64; /**< [511:448] Compare byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA7]
                                                                 byte. If that clear is set the corresponding byte must be identical to that byte
                                                                 in the record to be considered a match. Only bits [CMP_BDIS]\<RECSZM1:0\> have an
                                                                 effect. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t keydata0              : 64; /**< [575:512] Key or opaque data bytes. */
#else /* Word 8 - Little Endian */
        uint64_t keydata0              : 64; /**< [575:512] Key or opaque data bytes. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t keydata1              : 64; /**< [639:576] Extension of [KEYDATA0]. */
#else /* Word 9 - Little Endian */
        uint64_t keydata1              : 64; /**< [639:576] Extension of [KEYDATA0]. */
#endif /* Word 9 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 10 - Big Endian */
        uint64_t keydata2              : 64; /**< [703:640] Extension of [KEYDATA0]. */
#else /* Word 10 - Little Endian */
        uint64_t keydata2              : 64; /**< [703:640] Extension of [KEYDATA0]. */
#endif /* Word 10 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 11 - Big Endian */
        uint64_t keydata3              : 64; /**< [767:704] Extension of [KEYDATA0]. */
#else /* Word 11 - Little Endian */
        uint64_t keydata3              : 64; /**< [767:704] Extension of [KEYDATA0]. */
#endif /* Word 11 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 12 - Big Endian */
        uint64_t keydata4              : 64; /**< [831:768] Extension of [KEYDATA0]. */
#else /* Word 12 - Little Endian */
        uint64_t keydata4              : 64; /**< [831:768] Extension of [KEYDATA0]. */
#endif /* Word 12 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 13 - Big Endian */
        uint64_t keydata5              : 64; /**< [895:832] Extension of [KEYDATA0]. */
#else /* Word 13 - Little Endian */
        uint64_t keydata5              : 64; /**< [895:832] Extension of [KEYDATA0]. */
#endif /* Word 13 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 14 - Big Endian */
        uint64_t keydata6              : 64; /**< [959:896] Extension of [KEYDATA0]. */
#else /* Word 14 - Little Endian */
        uint64_t keydata6              : 64; /**< [959:896] Extension of [KEYDATA0]. */
#endif /* Word 14 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 15 - Big Endian */
        uint64_t keydata7              : 64; /**< [1023:960] Extension of [KEYDATA0]. */
#else /* Word 15 - Little Endian */
        uint64_t keydata7              : 64; /**< [1023:960] Extension of [KEYDATA0]. */
#endif /* Word 15 - End */
    } s;
    struct bdk_ddf_inst_match_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nrec                  : 16; /**< [ 63: 48] Number of records to compare.
                                                                 Typically the same as the number of records in a record block.
                                                                 If 0x0, compare nothing and return DDF_COMP_E::NO_RB. */
        uint64_t recszm1               : 8;  /**< [ 47: 40] Record size in bytes minus one.  Number of bytes must be multiple of 4
                                                                 and are not required to be powers of 2. Hardware enforces bits 1:0 are set and bits 7:6
                                                                 are clear.

                                                                 0x3 = 4 bytes.
                                                                 0x7 = 8 bytes.
                                                                 0xF = 16 bytes.
                                                                 0x13 = 20 bytes.
                                                                 0x17 = 24 bytes.
                                                                 _ ...
                                                                 0x3F = 64 bytes.

                                                                 Internal:
                                                                 Must support non-power-of-2. */
        uint64_t reserved_32_39        : 8;
        uint64_t reserved_23_31        : 9;
        uint64_t multm                 : 1;  /**< [ 22: 22] Multiple matches, applies to DDF_INST_MATCH_S::MATCH_SET,MATCH_INS,MATCH_DEL.

                                                                 0 = A match is only expected in one record. Once a record is found to match, ignore
                                                                 further comparisons.

                                                                 1 = A match may occur in multiple records. If a record is found to match, continue to
                                                                 compare or update all records in all record-sets.

                                                                 For MATCH_INS on an empty record, only 1 record is inserted. */
        uint64_t rr                    : 1;  /**< [ 21: 21] Return result. If set, include key data in DDF_RES_MATCH_S. */
        uint64_t cacr                  : 1;  /**< [ 20: 20] L2 cache record data. If set, when reading record data, allocate into L2 cache using the
                                                                 LD command specified in PF_Q()_CTL2[D_LD_CMD]. If clear, do not allocate if not already in
                                                                 L2 cache and use the LDT load command. */
        uint64_t reserved_19           : 1;
        uint64_t sync                  : 1;  /**< [ 18: 18] See DDF_INST_FIND_S[SYNC]. */
        uint64_t gang                  : 1;  /**< [ 17: 17] See DDF_INST_FIND_S[GANG]. */
        uint64_t doneint               : 1;  /**< [ 16: 16] See DDF_INST_FIND_S[DONEINT]. */
        uint64_t qwords                : 8;  /**< [ 15:  8] See DDF_INST_FIND_S[QWORDS]. */
        uint64_t op                    : 8;  /**< [  7:  0] See DDF_INST_FIND_S[OP]. */
#else /* Word 0 - Little Endian */
        uint64_t op                    : 8;  /**< [  7:  0] See DDF_INST_FIND_S[OP]. */
        uint64_t qwords                : 8;  /**< [ 15:  8] See DDF_INST_FIND_S[QWORDS]. */
        uint64_t doneint               : 1;  /**< [ 16: 16] See DDF_INST_FIND_S[DONEINT]. */
        uint64_t gang                  : 1;  /**< [ 17: 17] See DDF_INST_FIND_S[GANG]. */
        uint64_t sync                  : 1;  /**< [ 18: 18] See DDF_INST_FIND_S[SYNC]. */
        uint64_t reserved_19           : 1;
        uint64_t cacr                  : 1;  /**< [ 20: 20] L2 cache record data. If set, when reading record data, allocate into L2 cache using the
                                                                 LD command specified in PF_Q()_CTL2[D_LD_CMD]. If clear, do not allocate if not already in
                                                                 L2 cache and use the LDT load command. */
        uint64_t rr                    : 1;  /**< [ 21: 21] Return result. If set, include key data in DDF_RES_MATCH_S. */
        uint64_t multm                 : 1;  /**< [ 22: 22] Multiple matches, applies to DDF_INST_MATCH_S::MATCH_SET,MATCH_INS,MATCH_DEL.

                                                                 0 = A match is only expected in one record. Once a record is found to match, ignore
                                                                 further comparisons.

                                                                 1 = A match may occur in multiple records. If a record is found to match, continue to
                                                                 compare or update all records in all record-sets.

                                                                 For MATCH_INS on an empty record, only 1 record is inserted. */
        uint64_t reserved_23_31        : 9;
        uint64_t reserved_32_39        : 8;
        uint64_t recszm1               : 8;  /**< [ 47: 40] Record size in bytes minus one.  Number of bytes must be multiple of 4
                                                                 and are not required to be powers of 2. Hardware enforces bits 1:0 are set and bits 7:6
                                                                 are clear.

                                                                 0x3 = 4 bytes.
                                                                 0x7 = 8 bytes.
                                                                 0xF = 16 bytes.
                                                                 0x13 = 20 bytes.
                                                                 0x17 = 24 bytes.
                                                                 _ ...
                                                                 0x3F = 64 bytes.

                                                                 Internal:
                                                                 Must support non-power-of-2. */
        uint64_t nrec                  : 16; /**< [ 63: 48] Number of records to compare.
                                                                 Typically the same as the number of records in a record block.
                                                                 If 0x0, compare nothing and return DDF_COMP_E::NO_RB. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write DDF_RES_MATCH_S.
                                                                 If zero, no result structure will be written.

                                                                 If [RR] is clear, address must be 16-byte aligned.
                                                                 If [RR] is set, address must be 128-byte aligned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#else /* Word 1 - Little Endian */
        uint64_t res_addr              : 64; /**< [127: 64] Result IOVA.
                                                                 If nonzero, specifies where to write DDF_RES_MATCH_S.
                                                                 If zero, no result structure will be written.

                                                                 If [RR] is clear, address must be 16-byte aligned.
                                                                 If [RR] is set, address must be 128-byte aligned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t reserved_172_191      : 20;
        uint64_t grp                   : 10; /**< [171:162] See DDF_INST_FIND_S[GRP]. */
        uint64_t tt                    : 2;  /**< [161:160] See DDF_INST_FIND_S[TT]. */
        uint64_t tag                   : 32; /**< [159:128] See DDF_INST_FIND_S[TAG]. */
#else /* Word 2 - Little Endian */
        uint64_t tag                   : 32; /**< [159:128] See DDF_INST_FIND_S[TAG]. */
        uint64_t tt                    : 2;  /**< [161:160] See DDF_INST_FIND_S[TT]. */
        uint64_t grp                   : 10; /**< [171:162] See DDF_INST_FIND_S[GRP]. */
        uint64_t reserved_172_191      : 20;
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] See DDF_INST_FIND_S[WQ_PTR]. */
#else /* Word 3 - Little Endian */
        uint64_t wq_ptr                : 64; /**< [255:192] See DDF_INST_FIND_S[WQ_PTR]. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t rb_addr               : 64; /**< [319:256] Record block IOVA.
                                                                 For DDF_OP_E::RABS_SET instruction, pointer to data to change.
                                                                 Must be aligned to DDF_INST_MATCH_S[RECSZM1]+1 bytes.
                                                                 If 0x0, this record block is not used, and DDF_COMP_E::NO_RB is returned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility.
                                                                 Bits \<1:0\> are ignored by hardware and assumed to be 0. */
#else /* Word 4 - Little Endian */
        uint64_t rb_addr               : 64; /**< [319:256] Record block IOVA.
                                                                 For DDF_OP_E::RABS_SET instruction, pointer to data to change.
                                                                 Must be aligned to DDF_INST_MATCH_S[RECSZM1]+1 bytes.
                                                                 If 0x0, this record block is not used, and DDF_COMP_E::NO_RB is returned.

                                                                 Bits \<63:49\> are ignored by hardware; software should use a sign-extended bit
                                                                 \<48\> for forward compatibility.
                                                                 Bits \<1:0\> are ignored by hardware and assumed to be 0. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_320_383      : 64;
#else /* Word 5 - Little Endian */
        uint64_t reserved_320_383      : 64;
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t set_bdis              : 64; /**< [447:384] Set byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA7] byte. If
                                                                 that bit is clear the corresponding byte will be set in the record. Only bits
                                                                 [SET_BDIS]\<RECSZM1:0\> have an effect. */
#else /* Word 6 - Little Endian */
        uint64_t set_bdis              : 64; /**< [447:384] Set byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA7] byte. If
                                                                 that bit is clear the corresponding byte will be set in the record. Only bits
                                                                 [SET_BDIS]\<RECSZM1:0\> have an effect. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t cmp_bdis              : 64; /**< [511:448] Compare byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA7]
                                                                 byte. If that clear is set the corresponding byte must be identical to that byte
                                                                 in the record to be considered a match. Only bits [CMP_BDIS]\<RECSZM1:0\> have an
                                                                 effect. */
#else /* Word 7 - Little Endian */
        uint64_t cmp_bdis              : 64; /**< [511:448] Compare byte disables. One bit corresponds to each [KEYDATA0]..[KEYDATA7]
                                                                 byte. If that clear is set the corresponding byte must be identical to that byte
                                                                 in the record to be considered a match. Only bits [CMP_BDIS]\<RECSZM1:0\> have an
                                                                 effect. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t keydata0              : 64; /**< [575:512] Key or opaque data bytes. */
#else /* Word 8 - Little Endian */
        uint64_t keydata0              : 64; /**< [575:512] Key or opaque data bytes. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t keydata1              : 64; /**< [639:576] Extension of [KEYDATA0]. */
#else /* Word 9 - Little Endian */
        uint64_t keydata1              : 64; /**< [639:576] Extension of [KEYDATA0]. */
#endif /* Word 9 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 10 - Big Endian */
        uint64_t keydata2              : 64; /**< [703:640] Extension of [KEYDATA0]. */
#else /* Word 10 - Little Endian */
        uint64_t keydata2              : 64; /**< [703:640] Extension of [KEYDATA0]. */
#endif /* Word 10 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 11 - Big Endian */
        uint64_t keydata3              : 64; /**< [767:704] Extension of [KEYDATA0]. */
#else /* Word 11 - Little Endian */
        uint64_t keydata3              : 64; /**< [767:704] Extension of [KEYDATA0]. */
#endif /* Word 11 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 12 - Big Endian */
        uint64_t keydata4              : 64; /**< [831:768] Extension of [KEYDATA0]. */
#else /* Word 12 - Little Endian */
        uint64_t keydata4              : 64; /**< [831:768] Extension of [KEYDATA0]. */
#endif /* Word 12 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 13 - Big Endian */
        uint64_t keydata5              : 64; /**< [895:832] Extension of [KEYDATA0]. */
#else /* Word 13 - Little Endian */
        uint64_t keydata5              : 64; /**< [895:832] Extension of [KEYDATA0]. */
#endif /* Word 13 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 14 - Big Endian */
        uint64_t keydata6              : 64; /**< [959:896] Extension of [KEYDATA0]. */
#else /* Word 14 - Little Endian */
        uint64_t keydata6              : 64; /**< [959:896] Extension of [KEYDATA0]. */
#endif /* Word 14 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 15 - Big Endian */
        uint64_t keydata7              : 64; /**< [1023:960] Extension of [KEYDATA0]. */
#else /* Word 15 - Little Endian */
        uint64_t keydata7              : 64; /**< [1023:960] Extension of [KEYDATA0]. */
#endif /* Word 15 - End */
    } cn;
};

/**
 * Structure ddf_res_find_s
 *
 * DDF Result of Filter Find Structure
 * This structure specifies the result structure written by DDF after it completes a
 * DDF_INST_FIND_S. Each instruction completion produces exactly one result structure
 *
 * DDF always writes the first 16 bytes of this structure.  If DDF_INST_FIND_S[RR] is
 * set DDF will update an entire cache line, but only write valid data to the fields
 * specified depending on the required amount of [RDATA0]..[3] data, other bytes in the
 * line are undefined.
 *
 * This structure is stored in memory as little-endian unless DDF()_PF_Q()_CTL[INST_BE]
 * is set.
 *
 * Internal:
 * When DDF_INST_FIND_S[RR] is set it can use a full-cacheline write with fewer than
 * a cache-lines worth of NCB data ticks.
 */
union bdk_ddf_res_find_s
{
    uint64_t u[6];
    struct bdk_ddf_res_find_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t vmv                   : 1;  /**< [ 55: 55] For FIND_DEL, set if a victim was moved into the deleted nest from the header,
                                                                  same way. Will be clear for all other instructions. */
        uint64_t cuckoo                : 7;  /**< [ 54: 48] Number of cuckoo replacements made on insert. Valid only for DDF_OP_E::FIND_INS. */
        uint64_t hits                  : 8;  /**< [ 47: 40] Hit secondary-ways. Bitmask of ways in which the item was found using the secondary bucket
                                                                 number. For FIND_SET/FIND_INS/FIND_DEL/FEMPTY_INS a single bit in [HITP], [HITS] or
                                                                 [HITVIC] will be set. For FIND with PBKT equal SBKT the same bits in [HITP] and [HITS]
                                                                 will be set. For NBUCKP2 equal 0 only the [HITP] or [HITV] bits may be set.

                                                                 Will be 0x00 for DDF_OP_E::FABS_SET. */
        uint64_t hitp                  : 8;  /**< [ 39: 32] Hit primary-ways. Bitmask of ways in which the item was found using the primary bucket
                                                                 number. For FIND_SET/FIND_INS/FIND_DEL/FEMPTY_INS a single bit in [HITP], [HITS] or
                                                                 [HITVIC] will be set. For FIND with PBKT equal SBKT the same bits in [HITP] and [HITS]
                                                                 will be set. For NBUCKP2 equal 0 only the [HITP] or [HITV] bits may be set.

                                                                 Will be 0x00 for DDF_OP_E::FABS_SET. */
        uint64_t hitvict               : 8;  /**< [ 31: 24] Hit victim-ways. Bitmask of ways in which the item was found as a victim, else clear.
                                                                 For FIND_SET/FIND_INS/FIND_DEL/FEMPTY_INS a single bit in [HITP], [HITS] or [HITVIC] will
                                                                 be set indicating the set/inserted/deleted location.

                                                                 Will be 0x00 for DDF_OP_E::FABS_SET. */
        uint64_t nest                  : 2;  /**< [ 23: 22] Hit nest number. Set to DDF_INST_FIND_S[NEST] for FABS_SET. Indicates selected nest number
                                                                 for FIND, FIND_SET, FIND_INS, FIND_DEL, FEMPTY_INS when [HITP] or [HITS] != 0x0, else
                                                                 clear. Unpredictable unless [COMPCODE] equals DDF_COMP_E::GOOD. */
        uint64_t reserved_17_21        : 5;
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt. This bit is copied from the corresponding instruction's
                                                                 DDF_INST_FIND_S[DONEINT]. */
        uint64_t res_type              : 8;  /**< [ 15:  8] Type of response structure, enumerated by DDF_RES_TYPE_E. */
        uint64_t compcode              : 8;  /**< [  7:  0] Indicates completion/error status of the DDF coprocessor for the
                                                                 associated instruction, as enumerated by DDF_COMP_E. Core
                                                                 software may write the memory location containing [COMPCODE] to 0x0
                                                                 before ringing the doorbell, and then poll for completion by
                                                                 checking for a nonzero value.

                                                                 Once the core observes a nonzero [COMPCODE] value in this case, the DDF
                                                                 coprocessor will have also completed L2/DRAM write operations for all context,
                                                                 output stream, and result data. */
#else /* Word 0 - Little Endian */
        uint64_t compcode              : 8;  /**< [  7:  0] Indicates completion/error status of the DDF coprocessor for the
                                                                 associated instruction, as enumerated by DDF_COMP_E. Core
                                                                 software may write the memory location containing [COMPCODE] to 0x0
                                                                 before ringing the doorbell, and then poll for completion by
                                                                 checking for a nonzero value.

                                                                 Once the core observes a nonzero [COMPCODE] value in this case, the DDF
                                                                 coprocessor will have also completed L2/DRAM write operations for all context,
                                                                 output stream, and result data. */
        uint64_t res_type              : 8;  /**< [ 15:  8] Type of response structure, enumerated by DDF_RES_TYPE_E. */
        uint64_t doneint               : 1;  /**< [ 16: 16] Done interrupt. This bit is copied from the corresponding instruction's
                                                                 DDF_INST_FIND_S[DONEINT]. */
        uint64_t reserved_17_21        : 5;
        uint64_t nest                  : 2;  /**< [ 23: 22] Hit nest number. Set to DDF_INST_FIND_S[NEST] for FABS_SET. Indicates selected nest number
                                                                 for FIND, FIND_SET, FIND_INS, FIND_DEL, FEMPTY_INS when [HITP] or [HITS] != 0x0, else
                                                                 clear. Unpredictable unless [COMPCODE] equals DDF_COMP_E::GOOD. */
        uint64_t hitvict               : 8;  /**< [ 31: 24] Hit victim-ways. Bitmask of ways in which the item was found as a victim, else clear.
                                                                 For FIND_SET/FIND_INS/FIND_DEL/FEMPTY_INS a single bit in [HITP], [HITS] or [HITVIC] will
                                                                 be set indicating the set/inserted/deleted location.

                                                                 Will be 0x00 for DDF_OP_E::FABS_SET. */
        uint64_t hitp                  : 8;  /**< [ 39: 32] Hit primary-ways. Bitmask of ways in which the item was found using the primary bucket
                                                                 number. For FIND_SET/FIND_INS/FIND_DEL/FEMPTY_INS a single bit in [HITP], [HITS] or
                                                                 [HITVIC] will be set. For FIND with PBKT equal SBKT the same bits in [HITP] and [HITS]
                                                                 will be set. For NBUCKP2 equal 0 only the [HITP] or [HITV] bits may be set.

                                                                 Will be 0x00 for DDF_OP_E::FABS_SET. */
        uint64_t hits                  : 8;  /**< [ 47: 40] Hit secondary-ways. Bitmask of ways in which the item was found using the secondary bucket
                                                                 number. For FIND_SET/FIND_INS/FIND_DEL/FEMPTY_INS a single bit in [HITP], [HITS] or
                                                                 [HITVIC] will be set. For FIND with PBKT equal SBKT the same bits in [HITP] and [HITS]
                                                                 will be set. For NBUCKP2 equal 0 only the [HITP] or [HITV] bits may be set.

                                                                 Will be 0x00 for DDF_OP_E::FABS_SET. */
        uint64_t cuckoo                : 7;  /**< [ 54: 48] Number of cuckoo replacements made on insert. Valid only for DDF_OP_E::FIND_INS. */
        uint64_t vmv                   : 1;  /**< [ 55: 55] For FIND_DEL, set if a victim was moved into the deleted nest from the header,
                                                                  same way. Will be clear for all other instructions. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_118_127      : 10;
        uint64_t bktb                  : 6;  /**< [117:112] BucketB number of the nest that is returned in [RDATA0]..[3]. Valid only for a
                                                                 DDF_OP_E::FIND_INS or FEMPTY_INS that results in a cuckoo displacement as indicated by
                                                                 [COMPCODE] of DDF_COMP_E::FULL. The key for the displaced nest can be reconstructed from
                                                                 DDF_RES_FIND_S::RANK, DDF_RES_FIND_S::BKTB and [RDATA0]..[3]. Requires [RR] be set. */
        uint64_t reserved_110_111      : 2;
        uint64_t sbkt                  : 6;  /**< [109:104] Calculated secondary bucket number. */
        uint64_t reserved_102_103      : 2;
        uint64_t pbkt                  : 6;  /**< [101: 96] Calculated primary bucket number. */
        uint64_t rank                  : 32; /**< [ 95: 64] Calculated rank number. Is zero if DDF_INST_FIND_S[RANK_ABS] was set. */
#else /* Word 1 - Little Endian */
        uint64_t rank                  : 32; /**< [ 95: 64] Calculated rank number. Is zero if DDF_INST_FIND_S[RANK_ABS] was set. */
        uint64_t pbkt                  : 6;  /**< [101: 96] Calculated primary bucket number. */
        uint64_t reserved_102_103      : 2;
        uint64_t sbkt                  : 6;  /**< [109:104] Calculated secondary bucket number. */
        uint64_t reserved_110_111      : 2;
        uint64_t bktb                  : 6;  /**< [117:112] BucketB number of the nest that is returned in [RDATA0]..[3]. Valid only for a
                                                                 DDF_OP_E::FIND_INS or FEMPTY_INS that results in a cuckoo displacement as indicated by
                                                                 [COMPCODE] of DDF_COMP_E::FULL. The key for the displaced nest can be reconstructed from
                                                                 DDF_RES_FIND_S::RANK, DDF_RES_FIND_S::BKTB and [RDATA0]..[3]. Requires [RR] be set. */
        uint64_t reserved_118_127      : 10;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t rdata0                : 64; /**< [191:128] Key data bytes read from the nest or header before any update.

                                                                 If multiple hits resulted from a DDF_OP_E::FIND the nest data from [NEST] from the lowest
                                                                 matching way is returned.

                                                                 If both [HITP] and [HITS] are set in the lowest matching way, the primary nest is
                                                                 returned.

                                                                 For DDF_OP_E::FABS_SET the nest or header data as selected by [WAY],[PBKT],[NEST],[VICTEN]
                                                                 from [KEYDATA0]..[3] is returned.

                                                                 The data is read from the nest before any updates take place, including empty nest inserts
                                                                 where RDATA will be all zeroes. RDATA will also be all zeroes if [HITP], [HITS] and [HITV]
                                                                 are clear, except for a FEMPTY_INS or FIND_INS that returns DDF_COMP_E::FULL. In this case
                                                                 RDATA0..3 will contain the unplaced/displaced key data.

                                                                 [RDATA0]..[3] is only written if DDF_RES_FIND_S::RR is set.

                                                                 In the unique case of a hit on a 64B header, the alt-bucket is not returned in RDATA. It
                                                                 is however always returned in [SBKT]. */
#else /* Word 2 - Little Endian */
        uint64_t rdata0                : 64; /**< [191:128] Key data bytes read from the nest or header before any update.

                                                                 If multiple hits resulted from a DDF_OP_E::FIND the nest data from [NEST] from the lowest
                                                                 matching way is returned.

                                                                 If both [HITP] and [HITS] are set in the lowest matching way, the primary nest is
                                                                 returned.

                                                                 For DDF_OP_E::FABS_SET the nest or header data as selected by [WAY],[PBKT],[NEST],[VICTEN]
                                                                 from [KEYDATA0]..[3] is returned.

                                                                 The data is read from the nest before any updates take place, including empty nest inserts
                                                                 where RDATA will be all zeroes. RDATA will also be all zeroes if [HITP], [HITS] and [HITV]
                                                                 are clear, except for a FEMPTY_INS or FIND_INS that returns DDF_COMP_E::FULL. In this case
                                                                 RDATA0..3 will contain the unplaced/displaced key data.

                                                                 [RDATA0]..[3] is only written if DDF_RES_FIND_S::RR is set.

                                                                 In the unique case of a hit on a 64B header, the alt-bucket is not returned in RDATA. It
                                                                 is however always returned in [SBKT]. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t rdata1                : 64; /**< [255:192] Extension of [RDATA0]. */
#else /* Word 3 - Little Endian */
        uint64_t rdata1                : 64; /**< [255:192] Extension of [RDATA0]. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t rdata2                : 64; /**< [319:256] Extension of [RDATA0]. */
#else /* Word 4 - Little Endian */
        uint64_t rdata2                : 64; /**< [319:256] Extension of [RDATA0]. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t rdata3                : 64; /**< [383:320] Extension of [RDATA0]. */
#else /* Word 5 - Little Endian */
        uint64_t rdata3                : 64; /**< [383:320] Extension of [RDATA0]. */
#endif /* Word 5 - End */
    } s;
    /* struct bdk_ddf_res_find_s_s cn; */
};

/**
 * Structure ddf_res_match_s
 *
 * DDF Result of Record Match Structure
 * This structure specifies the result structure written by DDF after it completes a
 * DDF_INST_MATCH_S. Each instruction completion produces exactly one result structure
 *
 * DDF always writes the first 16 bytes of this structure.  If DDF_INST_MATCH_S[RR] is
 * set DDF will update an entire cache line, but only write valid data to the fields
 * specified depending on the required amount of [RDATA0]..[7] data.
 *
 * This structure is stored in memory as little-endian unless DDF()_PF_Q()_CTL[INST_BE]
 * is set.
 *
 * Internal:
 * When DDF_INST_MATCH_S[RR] is set it can use a full-cacheline write with fewer than
 * a cache-lines worth of NCB data ticks.
 */
union bdk_ddf_res_match_s
{
    uint64_t u[10];
    struct bdk_ddf_res_match_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hitrec                : 16; /**< [ 63: 48] Hit record. Record number in which the key was found or inserted into.

                                                                 For DDF_OP_E::RABS_SET, unpredictable. */
        uint64_t reserved_23_47        : 25;
        uint64_t hit                   : 1;  /**< [ 22: 22] Hit. Set if item was found before any change was applied, i.e. for
                                                                 DDF_OP_E::MATCH_INS, will be set if the record hit an existing record and clear
                                                                 if inserted into a previously empty location.

                                                                 For DDF_OP_E::REMPTY_INS, always clear.  For DDF_OP_E::RABS_SET, always clear. */
        uint64_t reserved_17_21        : 5;
        uint64_t doneint               : 1;  /**< [ 16: 16] See DDF_RES_FIND_S[DONEINT]. */
        uint64_t res_type              : 8;  /**< [ 15:  8] See DDF_RES_FIND_S[RES_TYPE]. */
        uint64_t compcode              : 8;  /**< [  7:  0] See DDF_RES_FIND_S[COMPCODE]. */
#else /* Word 0 - Little Endian */
        uint64_t compcode              : 8;  /**< [  7:  0] See DDF_RES_FIND_S[COMPCODE]. */
        uint64_t res_type              : 8;  /**< [ 15:  8] See DDF_RES_FIND_S[RES_TYPE]. */
        uint64_t doneint               : 1;  /**< [ 16: 16] See DDF_RES_FIND_S[DONEINT]. */
        uint64_t reserved_17_21        : 5;
        uint64_t hit                   : 1;  /**< [ 22: 22] Hit. Set if item was found before any change was applied, i.e. for
                                                                 DDF_OP_E::MATCH_INS, will be set if the record hit an existing record and clear
                                                                 if inserted into a previously empty location.

                                                                 For DDF_OP_E::REMPTY_INS, always clear.  For DDF_OP_E::RABS_SET, always clear. */
        uint64_t reserved_23_47        : 25;
        uint64_t hitrec                : 16; /**< [ 63: 48] Hit record. Record number in which the key was found or inserted into.

                                                                 For DDF_OP_E::RABS_SET, unpredictable. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_64_127       : 64;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_127       : 64;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t rdata0                : 64; /**< [191:128] Record data bytes read before any update.
                                                                 If [HIT] is set, the data read from record. In the case of multiple matches and
                                                                 modifications the contents of the first record are returned. In all other cases RDATA will
                                                                 be all zeroes. */
#else /* Word 2 - Little Endian */
        uint64_t rdata0                : 64; /**< [191:128] Record data bytes read before any update.
                                                                 If [HIT] is set, the data read from record. In the case of multiple matches and
                                                                 modifications the contents of the first record are returned. In all other cases RDATA will
                                                                 be all zeroes. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t rdata1                : 64; /**< [255:192] Extension of [RDATA0]. */
#else /* Word 3 - Little Endian */
        uint64_t rdata1                : 64; /**< [255:192] Extension of [RDATA0]. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t rdata2                : 64; /**< [319:256] Extension of [RDATA0]. */
#else /* Word 4 - Little Endian */
        uint64_t rdata2                : 64; /**< [319:256] Extension of [RDATA0]. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t rdata3                : 64; /**< [383:320] Extension of [RDATA0]. */
#else /* Word 5 - Little Endian */
        uint64_t rdata3                : 64; /**< [383:320] Extension of [RDATA0]. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t rdata4                : 64; /**< [447:384] Extension of [RDATA0]. */
#else /* Word 6 - Little Endian */
        uint64_t rdata4                : 64; /**< [447:384] Extension of [RDATA0]. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t rdata5                : 64; /**< [511:448] Extension of [RDATA0]. */
#else /* Word 7 - Little Endian */
        uint64_t rdata5                : 64; /**< [511:448] Extension of [RDATA0]. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t rdata6                : 64; /**< [575:512] Extension of [RDATA0]. */
#else /* Word 8 - Little Endian */
        uint64_t rdata6                : 64; /**< [575:512] Extension of [RDATA0]. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t rdata7                : 64; /**< [639:576] Extension of [RDATA0]. */
#else /* Word 9 - Little Endian */
        uint64_t rdata7                : 64; /**< [639:576] Extension of [RDATA0]. */
#endif /* Word 9 - End */
    } s;
    struct bdk_ddf_res_match_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t hitrec                : 16; /**< [ 63: 48] Hit record. Record number in which the key was found or inserted into.

                                                                 For DDF_OP_E::RABS_SET, unpredictable. */
        uint64_t reserved_24_47        : 24;
        uint64_t reserved_23           : 1;
        uint64_t hit                   : 1;  /**< [ 22: 22] Hit. Set if item was found before any change was applied, i.e. for
                                                                 DDF_OP_E::MATCH_INS, will be set if the record hit an existing record and clear
                                                                 if inserted into a previously empty location.

                                                                 For DDF_OP_E::REMPTY_INS, always clear.  For DDF_OP_E::RABS_SET, always clear. */
        uint64_t reserved_17_21        : 5;
        uint64_t doneint               : 1;  /**< [ 16: 16] See DDF_RES_FIND_S[DONEINT]. */
        uint64_t res_type              : 8;  /**< [ 15:  8] See DDF_RES_FIND_S[RES_TYPE]. */
        uint64_t compcode              : 8;  /**< [  7:  0] See DDF_RES_FIND_S[COMPCODE]. */
#else /* Word 0 - Little Endian */
        uint64_t compcode              : 8;  /**< [  7:  0] See DDF_RES_FIND_S[COMPCODE]. */
        uint64_t res_type              : 8;  /**< [ 15:  8] See DDF_RES_FIND_S[RES_TYPE]. */
        uint64_t doneint               : 1;  /**< [ 16: 16] See DDF_RES_FIND_S[DONEINT]. */
        uint64_t reserved_17_21        : 5;
        uint64_t hit                   : 1;  /**< [ 22: 22] Hit. Set if item was found before any change was applied, i.e. for
                                                                 DDF_OP_E::MATCH_INS, will be set if the record hit an existing record and clear
                                                                 if inserted into a previously empty location.

                                                                 For DDF_OP_E::REMPTY_INS, always clear.  For DDF_OP_E::RABS_SET, always clear. */
        uint64_t reserved_23           : 1;
        uint64_t reserved_24_47        : 24;
        uint64_t hitrec                : 16; /**< [ 63: 48] Hit record. Record number in which the key was found or inserted into.

                                                                 For DDF_OP_E::RABS_SET, unpredictable. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_64_127       : 64;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_127       : 64;
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t rdata0                : 64; /**< [191:128] Record data bytes read before any update.
                                                                 If [HIT] is set, the data read from record. In the case of multiple matches and
                                                                 modifications the contents of the first record are returned. In all other cases RDATA will
                                                                 be all zeroes. */
#else /* Word 2 - Little Endian */
        uint64_t rdata0                : 64; /**< [191:128] Record data bytes read before any update.
                                                                 If [HIT] is set, the data read from record. In the case of multiple matches and
                                                                 modifications the contents of the first record are returned. In all other cases RDATA will
                                                                 be all zeroes. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t rdata1                : 64; /**< [255:192] Extension of [RDATA0]. */
#else /* Word 3 - Little Endian */
        uint64_t rdata1                : 64; /**< [255:192] Extension of [RDATA0]. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t rdata2                : 64; /**< [319:256] Extension of [RDATA0]. */
#else /* Word 4 - Little Endian */
        uint64_t rdata2                : 64; /**< [319:256] Extension of [RDATA0]. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t rdata3                : 64; /**< [383:320] Extension of [RDATA0]. */
#else /* Word 5 - Little Endian */
        uint64_t rdata3                : 64; /**< [383:320] Extension of [RDATA0]. */
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t rdata4                : 64; /**< [447:384] Extension of [RDATA0]. */
#else /* Word 6 - Little Endian */
        uint64_t rdata4                : 64; /**< [447:384] Extension of [RDATA0]. */
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t rdata5                : 64; /**< [511:448] Extension of [RDATA0]. */
#else /* Word 7 - Little Endian */
        uint64_t rdata5                : 64; /**< [511:448] Extension of [RDATA0]. */
#endif /* Word 7 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 8 - Big Endian */
        uint64_t rdata6                : 64; /**< [575:512] Extension of [RDATA0]. */
#else /* Word 8 - Little Endian */
        uint64_t rdata6                : 64; /**< [575:512] Extension of [RDATA0]. */
#endif /* Word 8 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 9 - Big Endian */
        uint64_t rdata7                : 64; /**< [639:576] Extension of [RDATA0]. */
#else /* Word 9 - Little Endian */
        uint64_t rdata7                : 64; /**< [639:576] Extension of [RDATA0]. */
#endif /* Word 9 - End */
    } cn;
};

/**
 * Register (NCB) ddf#_cqm_core_obs0
 *
 * INTERNAL: DDF CQM Core Observability Debug Register
 */
union bdk_ddfx_cqm_core_obs0
{
    uint64_t u;
    struct bdk_ddfx_cqm_core_obs0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t instfif7_cnt          : 8;  /**< [ 63: 56](RO/H) Number of instruction words prefetched for group 7. */
        uint64_t instfif6_cnt          : 8;  /**< [ 55: 48](RO/H) Number of instruction words prefetched for group 6. */
        uint64_t instfif5_cnt          : 8;  /**< [ 47: 40](RO/H) Number of instruction words prefetched for group 5. */
        uint64_t instfif4_cnt          : 8;  /**< [ 39: 32](RO/H) Number of instruction words prefetched for group 4. */
        uint64_t instfif3_cnt          : 8;  /**< [ 31: 24](RO/H) Number of instruction words prefetched for group 3. */
        uint64_t instfif2_cnt          : 8;  /**< [ 23: 16](RO/H) Number of instruction words prefetched for group 2. */
        uint64_t instfif1_cnt          : 8;  /**< [ 15:  8](RO/H) Number of instruction words prefetched for group 1. */
        uint64_t instfif0_cnt          : 8;  /**< [  7:  0](RO/H) Number of instruction words prefetched for group 0. */
#else /* Word 0 - Little Endian */
        uint64_t instfif0_cnt          : 8;  /**< [  7:  0](RO/H) Number of instruction words prefetched for group 0. */
        uint64_t instfif1_cnt          : 8;  /**< [ 15:  8](RO/H) Number of instruction words prefetched for group 1. */
        uint64_t instfif2_cnt          : 8;  /**< [ 23: 16](RO/H) Number of instruction words prefetched for group 2. */
        uint64_t instfif3_cnt          : 8;  /**< [ 31: 24](RO/H) Number of instruction words prefetched for group 3. */
        uint64_t instfif4_cnt          : 8;  /**< [ 39: 32](RO/H) Number of instruction words prefetched for group 4. */
        uint64_t instfif5_cnt          : 8;  /**< [ 47: 40](RO/H) Number of instruction words prefetched for group 5. */
        uint64_t instfif6_cnt          : 8;  /**< [ 55: 48](RO/H) Number of instruction words prefetched for group 6. */
        uint64_t instfif7_cnt          : 8;  /**< [ 63: 56](RO/H) Number of instruction words prefetched for group 7. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_cqm_core_obs0_s cn; */
};
typedef union bdk_ddfx_cqm_core_obs0 bdk_ddfx_cqm_core_obs0_t;

static inline uint64_t BDK_DDFX_CQM_CORE_OBS0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_CQM_CORE_OBS0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x8090000001a0ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_CQM_CORE_OBS0", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_CQM_CORE_OBS0(a) bdk_ddfx_cqm_core_obs0_t
#define bustype_BDK_DDFX_CQM_CORE_OBS0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_CQM_CORE_OBS0(a) "DDFX_CQM_CORE_OBS0"
#define device_bar_BDK_DDFX_CQM_CORE_OBS0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_CQM_CORE_OBS0(a) (a)
#define arguments_BDK_DDFX_CQM_CORE_OBS0(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_cqm_core_obs1
 *
 * INTERNAL: DDF CQM Core Observability Debug Register
 */
union bdk_ddfx_cqm_core_obs1
{
    uint64_t u;
    struct bdk_ddfx_cqm_core_obs1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t ncbi_ptr_req          : 1;  /**< [ 49: 49](RO/H) CQM_CORE is waiting to issue an NCBI Request for instruction pointer fetch */
        uint64_t ncbi_req_rdy          : 1;  /**< [ 48: 48](RO/H) CQM_CORE is waiting to issue an NCBI Request for instruction fetch */
        uint64_t grp_rdy_hi_pri        : 8;  /**< [ 47: 40](RO/H) If set the corresponding group has high priority queues waiting to fetch
                                                                 instructions. */
        uint64_t grp_rdy_lo_pri        : 8;  /**< [ 39: 32](RO/H) If set the corresponding group has low priority queues waiting to fetch */
        uint64_t vqfif7_cnt            : 4;  /**< [ 31: 28](RO/H) Number of instructions getting prefetched for group 7. */
        uint64_t vqfif6_cnt            : 4;  /**< [ 27: 24](RO/H) Number of instructions getting prefetched for group 6. */
        uint64_t vqfif5_cnt            : 4;  /**< [ 23: 20](RO/H) Number of instructions getting prefetched for group 5. */
        uint64_t vqfif4_cnt            : 4;  /**< [ 19: 16](RO/H) Number of instructions getting prefetched for group 4. */
        uint64_t vqfif3_cnt            : 4;  /**< [ 15: 12](RO/H) Number of instructions getting prefetched for group 3. */
        uint64_t vqfif2_cnt            : 4;  /**< [ 11:  8](RO/H) Number of instructions getting prefetched for group 2. */
        uint64_t vqfif1_cnt            : 4;  /**< [  7:  4](RO/H) Number of instructions getting prefetched for group 1. */
        uint64_t vqfif0_cnt            : 4;  /**< [  3:  0](RO/H) Number of instructions getting prefetched for group 0. */
#else /* Word 0 - Little Endian */
        uint64_t vqfif0_cnt            : 4;  /**< [  3:  0](RO/H) Number of instructions getting prefetched for group 0. */
        uint64_t vqfif1_cnt            : 4;  /**< [  7:  4](RO/H) Number of instructions getting prefetched for group 1. */
        uint64_t vqfif2_cnt            : 4;  /**< [ 11:  8](RO/H) Number of instructions getting prefetched for group 2. */
        uint64_t vqfif3_cnt            : 4;  /**< [ 15: 12](RO/H) Number of instructions getting prefetched for group 3. */
        uint64_t vqfif4_cnt            : 4;  /**< [ 19: 16](RO/H) Number of instructions getting prefetched for group 4. */
        uint64_t vqfif5_cnt            : 4;  /**< [ 23: 20](RO/H) Number of instructions getting prefetched for group 5. */
        uint64_t vqfif6_cnt            : 4;  /**< [ 27: 24](RO/H) Number of instructions getting prefetched for group 6. */
        uint64_t vqfif7_cnt            : 4;  /**< [ 31: 28](RO/H) Number of instructions getting prefetched for group 7. */
        uint64_t grp_rdy_lo_pri        : 8;  /**< [ 39: 32](RO/H) If set the corresponding group has low priority queues waiting to fetch */
        uint64_t grp_rdy_hi_pri        : 8;  /**< [ 47: 40](RO/H) If set the corresponding group has high priority queues waiting to fetch
                                                                 instructions. */
        uint64_t ncbi_req_rdy          : 1;  /**< [ 48: 48](RO/H) CQM_CORE is waiting to issue an NCBI Request for instruction fetch */
        uint64_t ncbi_ptr_req          : 1;  /**< [ 49: 49](RO/H) CQM_CORE is waiting to issue an NCBI Request for instruction pointer fetch */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_cqm_core_obs1_s cn; */
};
typedef union bdk_ddfx_cqm_core_obs1 bdk_ddfx_cqm_core_obs1_t;

static inline uint64_t BDK_DDFX_CQM_CORE_OBS1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_CQM_CORE_OBS1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x8090000001a8ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_CQM_CORE_OBS1", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_CQM_CORE_OBS1(a) bdk_ddfx_cqm_core_obs1_t
#define bustype_BDK_DDFX_CQM_CORE_OBS1(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_CQM_CORE_OBS1(a) "DDFX_CQM_CORE_OBS1"
#define device_bar_BDK_DDFX_CQM_CORE_OBS1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_CQM_CORE_OBS1(a) (a)
#define arguments_BDK_DDFX_CQM_CORE_OBS1(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_ncbi_obs
 *
 * INTERNAL: DDF NCBI Observability Debug Register
 */
union bdk_ddfx_ncbi_obs
{
    uint64_t u;
    struct bdk_ddfx_ncbi_obs_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t datfif_cnt            : 8;  /**< [ 39: 32](RO/H) Number of pending data cycles to be sent to NCBI. */
        uint64_t cmdfif_cnt            : 8;  /**< [ 31: 24](RO/H) Number of pending commands to be sent to NCBI. */
        uint64_t reserved_22_23        : 2;
        uint64_t csr_rsp_dat           : 1;  /**< [ 21: 21](RO/H) CSR Response data available to be sent to NCBI.                                            . */
        uint64_t csr_rsp_val           : 1;  /**< [ 20: 20](RO/H) CSR Response available to be sent to NCBI. */
        uint64_t csr_cc_req            : 4;  /**< [ 19: 16](RO/H) Transfer cycles requested for CSR responses. */
        uint64_t res_cc_req            : 4;  /**< [ 15: 12](RO/H) Transfer cycles requested for result structure stores. */
        uint64_t ifc_cc_req            : 4;  /**< [ 11:  8](RO/H) Transfer cycles requested for instruction fetches. */
        uint64_t eng_cc_req            : 4;  /**< [  7:  4](RO/H) Transfer cycles requested from the engines. */
        uint64_t cdei_cc_left          : 4;  /**< [  3:  0](RO/H) Transfer cycles remaining to complete receiving transaction from DDF_NCBI input. */
#else /* Word 0 - Little Endian */
        uint64_t cdei_cc_left          : 4;  /**< [  3:  0](RO/H) Transfer cycles remaining to complete receiving transaction from DDF_NCBI input. */
        uint64_t eng_cc_req            : 4;  /**< [  7:  4](RO/H) Transfer cycles requested from the engines. */
        uint64_t ifc_cc_req            : 4;  /**< [ 11:  8](RO/H) Transfer cycles requested for instruction fetches. */
        uint64_t res_cc_req            : 4;  /**< [ 15: 12](RO/H) Transfer cycles requested for result structure stores. */
        uint64_t csr_cc_req            : 4;  /**< [ 19: 16](RO/H) Transfer cycles requested for CSR responses. */
        uint64_t csr_rsp_val           : 1;  /**< [ 20: 20](RO/H) CSR Response available to be sent to NCBI. */
        uint64_t csr_rsp_dat           : 1;  /**< [ 21: 21](RO/H) CSR Response data available to be sent to NCBI.                                            . */
        uint64_t reserved_22_23        : 2;
        uint64_t cmdfif_cnt            : 8;  /**< [ 31: 24](RO/H) Number of pending commands to be sent to NCBI. */
        uint64_t datfif_cnt            : 8;  /**< [ 39: 32](RO/H) Number of pending data cycles to be sent to NCBI. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_ncbi_obs_s cn; */
};
typedef union bdk_ddfx_ncbi_obs bdk_ddfx_ncbi_obs_t;

static inline uint64_t BDK_DDFX_NCBI_OBS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_NCBI_OBS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000190ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_NCBI_OBS", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_NCBI_OBS(a) bdk_ddfx_ncbi_obs_t
#define bustype_BDK_DDFX_NCBI_OBS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_NCBI_OBS(a) "DDFX_NCBI_OBS"
#define device_bar_BDK_DDFX_NCBI_OBS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_NCBI_OBS(a) (a)
#define arguments_BDK_DDFX_NCBI_OBS(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_active_cycles_pc
 *
 * DDF PF Active Cycles Register
 */
union bdk_ddfx_pf_active_cycles_pc
{
    uint64_t u;
    struct bdk_ddfx_pf_active_cycles_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the conditional clocks are active.
                                                                 Internal:
                                                                 Includes CDE internal or any engine clock being enabled. */
#else /* Word 0 - Little Endian */
        uint64_t act_cyc               : 64; /**< [ 63:  0](RO/H) Counts every coprocessor-clock cycle that the conditional clocks are active.
                                                                 Internal:
                                                                 Includes CDE internal or any engine clock being enabled. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_active_cycles_pc_s cn; */
};
typedef union bdk_ddfx_pf_active_cycles_pc bdk_ddfx_pf_active_cycles_pc_t;

static inline uint64_t BDK_DDFX_PF_ACTIVE_CYCLES_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_ACTIVE_CYCLES_PC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000010100ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_ACTIVE_CYCLES_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_ACTIVE_CYCLES_PC(a) bdk_ddfx_pf_active_cycles_pc_t
#define bustype_BDK_DDFX_PF_ACTIVE_CYCLES_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_ACTIVE_CYCLES_PC(a) "DDFX_PF_ACTIVE_CYCLES_PC"
#define device_bar_BDK_DDFX_PF_ACTIVE_CYCLES_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_ACTIVE_CYCLES_PC(a) (a)
#define arguments_BDK_DDFX_PF_ACTIVE_CYCLES_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_bist_status
 *
 * DDF PF Control Bist Status Register
 * This register has the BIST status of memories. Each bit is the BIST result of an
 * individual memory (per bit, 0 = pass and 1 = fail).
 */
union bdk_ddfx_pf_bist_status
{
    uint64_t u;
    struct bdk_ddfx_pf_bist_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t bstatus               : 32; /**< [ 31:  0](RO/H) BIST status. One bit per memory, enumerated by DDF_RAMS_E. */
#else /* Word 0 - Little Endian */
        uint64_t bstatus               : 32; /**< [ 31:  0](RO/H) BIST status. One bit per memory, enumerated by DDF_RAMS_E. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_bist_status_s cn; */
};
typedef union bdk_ddfx_pf_bist_status bdk_ddfx_pf_bist_status_t;

static inline uint64_t BDK_DDFX_PF_BIST_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_BIST_STATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000160ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_BIST_STATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_BIST_STATUS(a) bdk_ddfx_pf_bist_status_t
#define bustype_BDK_DDFX_PF_BIST_STATUS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_BIST_STATUS(a) "DDFX_PF_BIST_STATUS"
#define device_bar_BDK_DDFX_PF_BIST_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_BIST_STATUS(a) (a)
#define arguments_BDK_DDFX_PF_BIST_STATUS(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_bp_test
 *
 * INTERNAL: DDF PF Backpressure Test Register
 */
union bdk_ddfx_pf_bp_test
{
    uint64_t u;
    struct bdk_ddfx_pf_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = NCBI requests.
                                                                 \<62\> = Instruction prefetching.
                                                                 \<61\> = GMID RAM access arbitration.
                                                                 \<60\> = Reserved. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = NCBI requests.
                                                                 \<62\> = Instruction prefetching.
                                                                 \<61\> = GMID RAM access arbitration.
                                                                 \<60\> = Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_bp_test_s cn; */
};
typedef union bdk_ddfx_pf_bp_test bdk_ddfx_pf_bp_test_t;

static inline uint64_t BDK_DDFX_PF_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_BP_TEST(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000180ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_BP_TEST", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_BP_TEST(a) bdk_ddfx_pf_bp_test_t
#define bustype_BDK_DDFX_PF_BP_TEST(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_BP_TEST(a) "DDFX_PF_BP_TEST"
#define device_bar_BDK_DDFX_PF_BP_TEST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_BP_TEST(a) (a)
#define arguments_BDK_DDFX_PF_BP_TEST(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_bp_test0
 *
 * INTERNAL: DDF Backpressure Test Register 0
 */
union bdk_ddfx_pf_bp_test0
{
    uint64_t u;
    struct bdk_ddfx_pf_bp_test0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 5;  /**< [ 63: 59](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = LD/ST State machine Back Pressure.
                                                                 \<62\> = DREQ aribter enable.
                                                                 \<61\> = dmem arbiter enable.
                                                                 \<60\> = Line release arbiter enable.
                                                                 \<59\> = CAM arbiter enable. */
        uint64_t reserved_26_58        : 33;
        uint64_t bp_cfg                : 10; /**< [ 25: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<25:23\> = BP_CFG4.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 10; /**< [ 25: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<25:23\> = BP_CFG4.
                                                                   \<23:22\> = BP_CFG3.
                                                                   \<21:20\> = BP_CFG2.
                                                                   \<19:18\> = BP_CFG1.
                                                                   \<17:16\> = BP_CFG0. */
        uint64_t reserved_26_58        : 33;
        uint64_t enable                : 5;  /**< [ 63: 59](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = LD/ST State machine Back Pressure.
                                                                 \<62\> = DREQ aribter enable.
                                                                 \<61\> = dmem arbiter enable.
                                                                 \<60\> = Line release arbiter enable.
                                                                 \<59\> = CAM arbiter enable. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_bp_test0_s cn; */
};
typedef union bdk_ddfx_pf_bp_test0 bdk_ddfx_pf_bp_test0_t;

static inline uint64_t BDK_DDFX_PF_BP_TEST0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_BP_TEST0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809008001200ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_BP_TEST0", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_BP_TEST0(a) bdk_ddfx_pf_bp_test0_t
#define bustype_BDK_DDFX_PF_BP_TEST0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_BP_TEST0(a) "DDFX_PF_BP_TEST0"
#define device_bar_BDK_DDFX_PF_BP_TEST0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_BP_TEST0(a) (a)
#define arguments_BDK_DDFX_PF_BP_TEST0(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_cac_miss_pc
 *
 * DDF PF Cache Miss Performance Counter Register
 * This register controls diagnostic features.
 */
union bdk_ddfx_pf_cac_miss_pc
{
    uint64_t u;
    struct bdk_ddfx_pf_cac_miss_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Cache miss counter. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](RO/H) Cache miss counter. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_cac_miss_pc_s cn; */
};
typedef union bdk_ddfx_pf_cac_miss_pc bdk_ddfx_pf_cac_miss_pc_t;

static inline uint64_t BDK_DDFX_PF_CAC_MISS_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_CAC_MISS_PC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000620ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_CAC_MISS_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_CAC_MISS_PC(a) bdk_ddfx_pf_cac_miss_pc_t
#define bustype_BDK_DDFX_PF_CAC_MISS_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_CAC_MISS_PC(a) "DDFX_PF_CAC_MISS_PC"
#define device_bar_BDK_DDFX_PF_CAC_MISS_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_CAC_MISS_PC(a) (a)
#define arguments_BDK_DDFX_PF_CAC_MISS_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_constants
 *
 * DDF PF Constants Register
 * This register contains implementation-related parameters of DDF in CNXXXX.
 */
union bdk_ddfx_pf_constants
{
    uint64_t u;
    struct bdk_ddfx_pf_constants_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t vq                    : 8;  /**< [  7:  0](RO) Number of VQs. */
#else /* Word 0 - Little Endian */
        uint64_t vq                    : 8;  /**< [  7:  0](RO) Number of VQs. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_constants_s cn; */
};
typedef union bdk_ddfx_pf_constants bdk_ddfx_pf_constants_t;

static inline uint64_t BDK_DDFX_PF_CONSTANTS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_CONSTANTS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000000ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_CONSTANTS", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_CONSTANTS(a) bdk_ddfx_pf_constants_t
#define bustype_BDK_DDFX_PF_CONSTANTS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_CONSTANTS(a) "DDFX_PF_CONSTANTS"
#define device_bar_BDK_DDFX_PF_CONSTANTS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_CONSTANTS(a) (a)
#define arguments_BDK_DDFX_PF_CONSTANTS(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_ctl
 *
 * DDF PF Control Register
 * This register controls diagnostic features. This register should be changed only when
 * quiescent (see DDF()_VQ()_INPROG[INFLIGHT]).
 */
union bdk_ddfx_pf_ctl
{
    uint64_t u;
    struct bdk_ddfx_pf_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t fault_dis             : 1;  /**< [ 11: 11](R/W) Disable LD/ST fault detection. For diagnostic use only.
                                                                 Internal:
                                                                 To override fault consequences. */
        uint64_t stdn_sync_dis         : 1;  /**< [ 10: 10](R/W) Disable gating of result store on receipt of all NCB store-done's associated with cache
                                                                 flushes.  For diagnostic use only.

                                                                 Internal:
                                                                 To override stdn_sync halts. */
        uint64_t cacgang_disable       : 1;  /**< [  9:  9](R/W) Disable LRU gang list. For diagnostic use only. */
        uint64_t cacfree_thrsh         : 2;  /**< [  8:  7](R/W) Minimum number of cache entries to keep available for new instructions, equals 2^[3+CACFREE_THRSH]. */
        uint64_t eng_disable           : 4;  /**< [  6:  3](R/W) Set to disable individual filter and record engines. Bit 0 for fproc0, bit 1 for fproc1,
                                                                 bit 2 for rproc0, bit3 for rproc1. Should always have one of each type enabled, or
                                                                 guarantee that FIND instructions are always sent on group 0 and MATCH instructions on
                                                                 group 1. Otherwise hardware operation is undefined. */
        uint64_t synctimer_dis         : 1;  /**< [  2:  2](R/W) Cause hardware to flush entire DDF cache every 1M system clocks. */
        uint64_t cacpart               : 2;  /**< [  1:  0](R/W) Sets cache partition policy as enumerated in DDF_CACPART_E. */
#else /* Word 0 - Little Endian */
        uint64_t cacpart               : 2;  /**< [  1:  0](R/W) Sets cache partition policy as enumerated in DDF_CACPART_E. */
        uint64_t synctimer_dis         : 1;  /**< [  2:  2](R/W) Cause hardware to flush entire DDF cache every 1M system clocks. */
        uint64_t eng_disable           : 4;  /**< [  6:  3](R/W) Set to disable individual filter and record engines. Bit 0 for fproc0, bit 1 for fproc1,
                                                                 bit 2 for rproc0, bit3 for rproc1. Should always have one of each type enabled, or
                                                                 guarantee that FIND instructions are always sent on group 0 and MATCH instructions on
                                                                 group 1. Otherwise hardware operation is undefined. */
        uint64_t cacfree_thrsh         : 2;  /**< [  8:  7](R/W) Minimum number of cache entries to keep available for new instructions, equals 2^[3+CACFREE_THRSH]. */
        uint64_t cacgang_disable       : 1;  /**< [  9:  9](R/W) Disable LRU gang list. For diagnostic use only. */
        uint64_t stdn_sync_dis         : 1;  /**< [ 10: 10](R/W) Disable gating of result store on receipt of all NCB store-done's associated with cache
                                                                 flushes.  For diagnostic use only.

                                                                 Internal:
                                                                 To override stdn_sync halts. */
        uint64_t fault_dis             : 1;  /**< [ 11: 11](R/W) Disable LD/ST fault detection. For diagnostic use only.
                                                                 Internal:
                                                                 To override fault consequences. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_ctl_s cn; */
};
typedef union bdk_ddfx_pf_ctl bdk_ddfx_pf_ctl_t;

static inline uint64_t BDK_DDFX_PF_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000600ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_CTL(a) bdk_ddfx_pf_ctl_t
#define bustype_BDK_DDFX_PF_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_CTL(a) "DDFX_PF_CTL"
#define device_bar_BDK_DDFX_PF_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_CTL(a) (a)
#define arguments_BDK_DDFX_PF_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_ctl2
 *
 * DDF PF Control Register 2
 * This register controls diagnostic features.
 */
union bdk_ddfx_pf_ctl2
{
    uint64_t u;
    struct bdk_ddfx_pf_ctl2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t cacflush              : 1;  /**< [  0:  0](R/W1S/H) When written with one, request that hardware flush the DDF cache (for all
                                                                 streams and addresses). This bit will stay set until the flush is completed,
                                                                 then be cleared.

                                                                 New transactions may simultaneously fill the cache, and will not block this bit
                                                                 clearing, so to insure complete emptiness all DDF()_VQ()_CTL[ENA] must be clear. */
#else /* Word 0 - Little Endian */
        uint64_t cacflush              : 1;  /**< [  0:  0](R/W1S/H) When written with one, request that hardware flush the DDF cache (for all
                                                                 streams and addresses). This bit will stay set until the flush is completed,
                                                                 then be cleared.

                                                                 New transactions may simultaneously fill the cache, and will not block this bit
                                                                 clearing, so to insure complete emptiness all DDF()_VQ()_CTL[ENA] must be clear. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_ctl2_s cn; */
};
typedef union bdk_ddfx_pf_ctl2 bdk_ddfx_pf_ctl2_t;

static inline uint64_t BDK_DDFX_PF_CTL2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_CTL2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000610ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_CTL2", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_CTL2(a) bdk_ddfx_pf_ctl2_t
#define bustype_BDK_DDFX_PF_CTL2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_CTL2(a) "DDFX_PF_CTL2"
#define device_bar_BDK_DDFX_PF_CTL2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_CTL2(a) (a)
#define arguments_BDK_DDFX_PF_CTL2(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_diag
 *
 * DDF PF Diagnostic Control Register
 * This register controls diagnostic features.
 */
union bdk_ddfx_pf_diag
{
    uint64_t u;
    struct bdk_ddfx_pf_diag_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t forceclk              : 1;  /**< [  8:  8](R/W) When this bit is set to 1, it forces DDF clocks on. For diagnostic use only. */
        uint64_t ld_infl               : 8;  /**< [  7:  0](R/W) Maximum number of in-flight data fetch transactions on the NCB. Larger values
                                                                 may improve DDF performance but may starve other devices on the same NCB. Values
                                                                 \> 64 are treated as 64. */
#else /* Word 0 - Little Endian */
        uint64_t ld_infl               : 8;  /**< [  7:  0](R/W) Maximum number of in-flight data fetch transactions on the NCB. Larger values
                                                                 may improve DDF performance but may starve other devices on the same NCB. Values
                                                                 \> 64 are treated as 64. */
        uint64_t forceclk              : 1;  /**< [  8:  8](R/W) When this bit is set to 1, it forces DDF clocks on. For diagnostic use only. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_diag_s cn; */
};
typedef union bdk_ddfx_pf_diag bdk_ddfx_pf_diag_t;

static inline uint64_t BDK_DDFX_PF_DIAG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_DIAG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000120ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_DIAG", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_DIAG(a) bdk_ddfx_pf_diag_t
#define bustype_BDK_DDFX_PF_DIAG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_DIAG(a) "DDFX_PF_DIAG"
#define device_bar_BDK_DDFX_PF_DIAG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_DIAG(a) (a)
#define arguments_BDK_DDFX_PF_DIAG(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_diag2
 *
 * DDF PF Diagnostic Control Register 2
 * This register controls diagnostic features.
 */
union bdk_ddfx_pf_diag2
{
    uint64_t u;
    struct bdk_ddfx_pf_diag2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t gang_list_cnt         : 8;  /**< [ 31: 24](RO/H) Number of entries on the gang cache lru list. */
        uint64_t link_list_cnt         : 8;  /**< [ 23: 16](RO/H) Number of entries on the link cache lru list. */
        uint64_t flsh_list_cnt         : 8;  /**< [ 15:  8](RO/H) Number of entries on the flush cache lru list. */
        uint64_t free_list_cnt         : 8;  /**< [  7:  0](RO/H) Number of entries on the free cache lru list. */
#else /* Word 0 - Little Endian */
        uint64_t free_list_cnt         : 8;  /**< [  7:  0](RO/H) Number of entries on the free cache lru list. */
        uint64_t flsh_list_cnt         : 8;  /**< [ 15:  8](RO/H) Number of entries on the flush cache lru list. */
        uint64_t link_list_cnt         : 8;  /**< [ 23: 16](RO/H) Number of entries on the link cache lru list. */
        uint64_t gang_list_cnt         : 8;  /**< [ 31: 24](RO/H) Number of entries on the gang cache lru list. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_diag2_s cn; */
};
typedef union bdk_ddfx_pf_diag2 bdk_ddfx_pf_diag2_t;

static inline uint64_t BDK_DDFX_PF_DIAG2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_DIAG2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000630ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_DIAG2", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_DIAG2(a) bdk_ddfx_pf_diag2_t
#define bustype_BDK_DDFX_PF_DIAG2(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_DIAG2(a) "DDFX_PF_DIAG2"
#define device_bar_BDK_DDFX_PF_DIAG2(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_DIAG2(a) (a)
#define arguments_BDK_DDFX_PF_DIAG2(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_diag_cam#
 *
 * DDF PF Diagnostic CAM Access Register
 * This register provides diagnostic read access to the CAM.
 */
union bdk_ddfx_pf_diag_camx
{
    uint64_t u;
    struct bdk_ddfx_pf_diag_camx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Cam contents. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) Cam contents. For diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_diag_camx_s cn; */
};
typedef union bdk_ddfx_pf_diag_camx bdk_ddfx_pf_diag_camx_t;

static inline uint64_t BDK_DDFX_PF_DIAG_CAMX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_DIAG_CAMX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=127)))
        return 0x809000000800ll + 0ll * ((a) & 0x0) + 8ll * ((b) & 0x7f);
    __bdk_csr_fatal("DDFX_PF_DIAG_CAMX", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_DIAG_CAMX(a,b) bdk_ddfx_pf_diag_camx_t
#define bustype_BDK_DDFX_PF_DIAG_CAMX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_DIAG_CAMX(a,b) "DDFX_PF_DIAG_CAMX"
#define device_bar_BDK_DDFX_PF_DIAG_CAMX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_DIAG_CAMX(a,b) (a)
#define arguments_BDK_DDFX_PF_DIAG_CAMX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_diag_dmem#
 *
 * DDF PF Diagnostic DMEM Access Register
 * This register provides diagnostic read access to the DMEM.
 */
union bdk_ddfx_pf_diag_dmemx
{
    uint64_t u;
    struct bdk_ddfx_pf_diag_dmemx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) DMEM contents. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](RO/H) DMEM contents. For diagnostic use only. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_diag_dmemx_s cn; */
};
typedef union bdk_ddfx_pf_diag_dmemx bdk_ddfx_pf_diag_dmemx_t;

static inline uint64_t BDK_DDFX_PF_DIAG_DMEMX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_DIAG_DMEMX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=2047)))
        return 0x809000004000ll + 0ll * ((a) & 0x0) + 8ll * ((b) & 0x7ff);
    __bdk_csr_fatal("DDFX_PF_DIAG_DMEMX", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_DIAG_DMEMX(a,b) bdk_ddfx_pf_diag_dmemx_t
#define bustype_BDK_DDFX_PF_DIAG_DMEMX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_DIAG_DMEMX(a,b) "DDFX_PF_DIAG_DMEMX"
#define device_bar_BDK_DDFX_PF_DIAG_DMEMX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_DIAG_DMEMX(a,b) (a)
#define arguments_BDK_DDFX_PF_DIAG_DMEMX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_ecc0_ctl
 *
 * DDF PF ECC Control Register
 * This register enables ECC for each individual internal memory that requires ECC. For debug
 * purposes, it can also flip one or two bits in the ECC data.
 */
union bdk_ddfx_pf_ecc0_ctl
{
    uint64_t u;
    struct bdk_ddfx_pf_ecc0_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t cdis                  : 32; /**< [ 31:  0](R/W) Disables ECC correction on each RAM.  Bit positions enumerated with DDF_RAMS_E. */
#else /* Word 0 - Little Endian */
        uint64_t cdis                  : 32; /**< [ 31:  0](R/W) Disables ECC correction on each RAM.  Bit positions enumerated with DDF_RAMS_E. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_ecc0_ctl_s cn; */
};
typedef union bdk_ddfx_pf_ecc0_ctl bdk_ddfx_pf_ecc0_ctl_t;

static inline uint64_t BDK_DDFX_PF_ECC0_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_ECC0_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000200ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_ECC0_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_ECC0_CTL(a) bdk_ddfx_pf_ecc0_ctl_t
#define bustype_BDK_DDFX_PF_ECC0_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_ECC0_CTL(a) "DDFX_PF_ECC0_CTL"
#define device_bar_BDK_DDFX_PF_ECC0_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_ECC0_CTL(a) (a)
#define arguments_BDK_DDFX_PF_ECC0_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_ecc0_ena_w1c
 *
 * DDF ECC Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_ddfx_pf_ecc0_ena_w1c
{
    uint64_t u;
    struct bdk_ddfx_pf_ecc0_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dbe                   : 32; /**< [ 63: 32](R/W1C/H) Reads or clears enable for DDF(0)_PF_ECC0_INT[DBE]. */
        uint64_t sbe                   : 32; /**< [ 31:  0](R/W1C/H) Reads or clears enable for DDF(0)_PF_ECC0_INT[SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t sbe                   : 32; /**< [ 31:  0](R/W1C/H) Reads or clears enable for DDF(0)_PF_ECC0_INT[SBE]. */
        uint64_t dbe                   : 32; /**< [ 63: 32](R/W1C/H) Reads or clears enable for DDF(0)_PF_ECC0_INT[DBE]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_ecc0_ena_w1c_s cn; */
};
typedef union bdk_ddfx_pf_ecc0_ena_w1c bdk_ddfx_pf_ecc0_ena_w1c_t;

static inline uint64_t BDK_DDFX_PF_ECC0_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_ECC0_ENA_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000250ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_ECC0_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_ECC0_ENA_W1C(a) bdk_ddfx_pf_ecc0_ena_w1c_t
#define bustype_BDK_DDFX_PF_ECC0_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_ECC0_ENA_W1C(a) "DDFX_PF_ECC0_ENA_W1C"
#define device_bar_BDK_DDFX_PF_ECC0_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_ECC0_ENA_W1C(a) (a)
#define arguments_BDK_DDFX_PF_ECC0_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_ecc0_ena_w1s
 *
 * DDF ECC Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_ddfx_pf_ecc0_ena_w1s
{
    uint64_t u;
    struct bdk_ddfx_pf_ecc0_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dbe                   : 32; /**< [ 63: 32](R/W1S/H) Reads or sets enable for DDF(0)_PF_ECC0_INT[DBE]. */
        uint64_t sbe                   : 32; /**< [ 31:  0](R/W1S/H) Reads or sets enable for DDF(0)_PF_ECC0_INT[SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t sbe                   : 32; /**< [ 31:  0](R/W1S/H) Reads or sets enable for DDF(0)_PF_ECC0_INT[SBE]. */
        uint64_t dbe                   : 32; /**< [ 63: 32](R/W1S/H) Reads or sets enable for DDF(0)_PF_ECC0_INT[DBE]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_ecc0_ena_w1s_s cn; */
};
typedef union bdk_ddfx_pf_ecc0_ena_w1s bdk_ddfx_pf_ecc0_ena_w1s_t;

static inline uint64_t BDK_DDFX_PF_ECC0_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_ECC0_ENA_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000240ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_ECC0_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_ECC0_ENA_W1S(a) bdk_ddfx_pf_ecc0_ena_w1s_t
#define bustype_BDK_DDFX_PF_ECC0_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_ECC0_ENA_W1S(a) "DDFX_PF_ECC0_ENA_W1S"
#define device_bar_BDK_DDFX_PF_ECC0_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_ECC0_ENA_W1S(a) (a)
#define arguments_BDK_DDFX_PF_ECC0_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_ecc0_flip
 *
 * DDF PF ECC Flip Syndrome Register
 * This register enables ECC for each individual internal memory that requires ECC. For debug
 * purposes, it can also flip one or two bits in the ECC data.
 */
union bdk_ddfx_pf_ecc0_flip
{
    uint64_t u;
    struct bdk_ddfx_pf_ecc0_flip_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t flip1                 : 32; /**< [ 63: 32](R/W) Flips syndome bit 1 on writes.  Bit positions enumerated with DDF_RAMS_E. */
        uint64_t flip0                 : 32; /**< [ 31:  0](R/W) Flips syndome bit 0 on writes.  Bit positions enumerated with DDF_RAMS_E. */
#else /* Word 0 - Little Endian */
        uint64_t flip0                 : 32; /**< [ 31:  0](R/W) Flips syndome bit 0 on writes.  Bit positions enumerated with DDF_RAMS_E. */
        uint64_t flip1                 : 32; /**< [ 63: 32](R/W) Flips syndome bit 1 on writes.  Bit positions enumerated with DDF_RAMS_E. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_ecc0_flip_s cn; */
};
typedef union bdk_ddfx_pf_ecc0_flip bdk_ddfx_pf_ecc0_flip_t;

static inline uint64_t BDK_DDFX_PF_ECC0_FLIP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_ECC0_FLIP(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000210ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_ECC0_FLIP", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_ECC0_FLIP(a) bdk_ddfx_pf_ecc0_flip_t
#define bustype_BDK_DDFX_PF_ECC0_FLIP(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_ECC0_FLIP(a) "DDFX_PF_ECC0_FLIP"
#define device_bar_BDK_DDFX_PF_ECC0_FLIP(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_ECC0_FLIP(a) (a)
#define arguments_BDK_DDFX_PF_ECC0_FLIP(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_ecc0_int
 *
 * DDF ECC Interrupt Status Register
 * This register contains the status of the ECC interrupt sources.
 */
union bdk_ddfx_pf_ecc0_int
{
    uint64_t u;
    struct bdk_ddfx_pf_ecc0_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dbe                   : 32; /**< [ 63: 32](R/W1C/H) Double-bit error detected in internal RAM. One bit per memory, enumerated by
                                                                 DDF_RAMS_E. */
        uint64_t sbe                   : 32; /**< [ 31:  0](R/W1C/H) Single-bit error detected in internal RAM. One bit per memory, enumerated by
                                                                 DDF_RAMS_E. */
#else /* Word 0 - Little Endian */
        uint64_t sbe                   : 32; /**< [ 31:  0](R/W1C/H) Single-bit error detected in internal RAM. One bit per memory, enumerated by
                                                                 DDF_RAMS_E. */
        uint64_t dbe                   : 32; /**< [ 63: 32](R/W1C/H) Double-bit error detected in internal RAM. One bit per memory, enumerated by
                                                                 DDF_RAMS_E. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_ecc0_int_s cn; */
};
typedef union bdk_ddfx_pf_ecc0_int bdk_ddfx_pf_ecc0_int_t;

static inline uint64_t BDK_DDFX_PF_ECC0_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_ECC0_INT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000220ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_ECC0_INT", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_ECC0_INT(a) bdk_ddfx_pf_ecc0_int_t
#define bustype_BDK_DDFX_PF_ECC0_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_ECC0_INT(a) "DDFX_PF_ECC0_INT"
#define device_bar_BDK_DDFX_PF_ECC0_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_ECC0_INT(a) (a)
#define arguments_BDK_DDFX_PF_ECC0_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_ecc0_int_w1s
 *
 * DDF ECC Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_ddfx_pf_ecc0_int_w1s
{
    uint64_t u;
    struct bdk_ddfx_pf_ecc0_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dbe                   : 32; /**< [ 63: 32](R/W1S/H) Reads or sets DDF(0)_PF_ECC0_INT[DBE]. */
        uint64_t sbe                   : 32; /**< [ 31:  0](R/W1S/H) Reads or sets DDF(0)_PF_ECC0_INT[SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t sbe                   : 32; /**< [ 31:  0](R/W1S/H) Reads or sets DDF(0)_PF_ECC0_INT[SBE]. */
        uint64_t dbe                   : 32; /**< [ 63: 32](R/W1S/H) Reads or sets DDF(0)_PF_ECC0_INT[DBE]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_ecc0_int_w1s_s cn; */
};
typedef union bdk_ddfx_pf_ecc0_int_w1s bdk_ddfx_pf_ecc0_int_w1s_t;

static inline uint64_t BDK_DDFX_PF_ECC0_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_ECC0_INT_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000230ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_ECC0_INT_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_ECC0_INT_W1S(a) bdk_ddfx_pf_ecc0_int_w1s_t
#define bustype_BDK_DDFX_PF_ECC0_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_ECC0_INT_W1S(a) "DDFX_PF_ECC0_INT_W1S"
#define device_bar_BDK_DDFX_PF_ECC0_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_ECC0_INT_W1S(a) (a)
#define arguments_BDK_DDFX_PF_ECC0_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_eco
 *
 * INTERNAL: DDF PF ECO Register
 */
union bdk_ddfx_pf_eco
{
    uint64_t u;
    struct bdk_ddfx_pf_eco_s
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
    /* struct bdk_ddfx_pf_eco_s cn; */
};
typedef union bdk_ddfx_pf_eco bdk_ddfx_pf_eco_t;

static inline uint64_t BDK_DDFX_PF_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_ECO(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000140ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_ECO", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_ECO(a) bdk_ddfx_pf_eco_t
#define bustype_BDK_DDFX_PF_ECO(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_ECO(a) "DDFX_PF_ECO"
#define device_bar_BDK_DDFX_PF_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_ECO(a) (a)
#define arguments_BDK_DDFX_PF_ECO(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_inst_latency_pc
 *
 * DDF PF Instruction Latency Counter Register
 */
union bdk_ddfx_pf_inst_latency_pc
{
    uint64_t u;
    struct bdk_ddfx_pf_inst_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for an instruction to complete (have the store of
                                                                 DDF_RES_S reach the commit point). Incremented every coprocessor-clock by the
                                                                 number of instructions active in that cycle. This may be divided by
                                                                 DDF()_PF_RD_REQ_PC to determine the average hardware instruction latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for an instruction to complete (have the store of
                                                                 DDF_RES_S reach the commit point). Incremented every coprocessor-clock by the
                                                                 number of instructions active in that cycle. This may be divided by
                                                                 DDF()_PF_RD_REQ_PC to determine the average hardware instruction latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_inst_latency_pc_s cn; */
};
typedef union bdk_ddfx_pf_inst_latency_pc bdk_ddfx_pf_inst_latency_pc_t;

static inline uint64_t BDK_DDFX_PF_INST_LATENCY_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_INST_LATENCY_PC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000010020ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_INST_LATENCY_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_INST_LATENCY_PC(a) bdk_ddfx_pf_inst_latency_pc_t
#define bustype_BDK_DDFX_PF_INST_LATENCY_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_INST_LATENCY_PC(a) "DDFX_PF_INST_LATENCY_PC"
#define device_bar_BDK_DDFX_PF_INST_LATENCY_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_INST_LATENCY_PC(a) (a)
#define arguments_BDK_DDFX_PF_INST_LATENCY_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_inst_req_pc
 *
 * DDF PF Instruction Request Performance Counter Register
 */
union bdk_ddfx_pf_inst_req_pc
{
    uint64_t u;
    struct bdk_ddfx_pf_inst_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of instructions that have started processing. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of instructions that have started processing. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_inst_req_pc_s cn; */
};
typedef union bdk_ddfx_pf_inst_req_pc bdk_ddfx_pf_inst_req_pc_t;

static inline uint64_t BDK_DDFX_PF_INST_REQ_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_INST_REQ_PC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000010000ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_INST_REQ_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_INST_REQ_PC(a) bdk_ddfx_pf_inst_req_pc_t
#define bustype_BDK_DDFX_PF_INST_REQ_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_INST_REQ_PC(a) "DDFX_PF_INST_REQ_PC"
#define device_bar_BDK_DDFX_PF_INST_REQ_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_INST_REQ_PC(a) (a)
#define arguments_BDK_DDFX_PF_INST_REQ_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_mbox_ena_w1c#
 *
 * DDF PF Mailbox Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_ddfx_pf_mbox_ena_w1cx
{
    uint64_t u;
    struct bdk_ddfx_pf_mbox_ena_w1cx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for DDF(0)_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for DDF(0)_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_mbox_ena_w1cx_s cn; */
};
typedef union bdk_ddfx_pf_mbox_ena_w1cx bdk_ddfx_pf_mbox_ena_w1cx_t;

static inline uint64_t BDK_DDFX_PF_MBOX_ENA_W1CX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_MBOX_ENA_W1CX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b==0)))
        return 0x809000000440ll + 0ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("DDFX_PF_MBOX_ENA_W1CX", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_MBOX_ENA_W1CX(a,b) bdk_ddfx_pf_mbox_ena_w1cx_t
#define bustype_BDK_DDFX_PF_MBOX_ENA_W1CX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_MBOX_ENA_W1CX(a,b) "DDFX_PF_MBOX_ENA_W1CX"
#define device_bar_BDK_DDFX_PF_MBOX_ENA_W1CX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_MBOX_ENA_W1CX(a,b) (a)
#define arguments_BDK_DDFX_PF_MBOX_ENA_W1CX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_mbox_ena_w1s#
 *
 * DDF PF Mailbox Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_ddfx_pf_mbox_ena_w1sx
{
    uint64_t u;
    struct bdk_ddfx_pf_mbox_ena_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for DDF(0)_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for DDF(0)_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_mbox_ena_w1sx_s cn; */
};
typedef union bdk_ddfx_pf_mbox_ena_w1sx bdk_ddfx_pf_mbox_ena_w1sx_t;

static inline uint64_t BDK_DDFX_PF_MBOX_ENA_W1SX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_MBOX_ENA_W1SX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b==0)))
        return 0x809000000460ll + 0ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("DDFX_PF_MBOX_ENA_W1SX", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_MBOX_ENA_W1SX(a,b) bdk_ddfx_pf_mbox_ena_w1sx_t
#define bustype_BDK_DDFX_PF_MBOX_ENA_W1SX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_MBOX_ENA_W1SX(a,b) "DDFX_PF_MBOX_ENA_W1SX"
#define device_bar_BDK_DDFX_PF_MBOX_ENA_W1SX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_MBOX_ENA_W1SX(a,b) (a)
#define arguments_BDK_DDFX_PF_MBOX_ENA_W1SX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_mbox_int#
 *
 * DDF PF Mailbox Interrupt Registers
 */
union bdk_ddfx_pf_mbox_intx
{
    uint64_t u;
    struct bdk_ddfx_pf_mbox_intx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF. Each bit is set when the associated
                                                                 DDF()_VF()_PF_MBOX(1) is written. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1C/H) One interrupt bit per VF. Each bit is set when the associated
                                                                 DDF()_VF()_PF_MBOX(1) is written. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_mbox_intx_s cn; */
};
typedef union bdk_ddfx_pf_mbox_intx bdk_ddfx_pf_mbox_intx_t;

static inline uint64_t BDK_DDFX_PF_MBOX_INTX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_MBOX_INTX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b==0)))
        return 0x809000000400ll + 0ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("DDFX_PF_MBOX_INTX", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_MBOX_INTX(a,b) bdk_ddfx_pf_mbox_intx_t
#define bustype_BDK_DDFX_PF_MBOX_INTX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_MBOX_INTX(a,b) "DDFX_PF_MBOX_INTX"
#define device_bar_BDK_DDFX_PF_MBOX_INTX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_MBOX_INTX(a,b) (a)
#define arguments_BDK_DDFX_PF_MBOX_INTX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_mbox_int_w1s#
 *
 * DDF PF Mailbox Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_ddfx_pf_mbox_int_w1sx
{
    uint64_t u;
    struct bdk_ddfx_pf_mbox_int_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets DDF(0)_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 64; /**< [ 63:  0](R/W1S/H) Reads or sets DDF(0)_PF_MBOX_INT(0)[MBOX]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_mbox_int_w1sx_s cn; */
};
typedef union bdk_ddfx_pf_mbox_int_w1sx bdk_ddfx_pf_mbox_int_w1sx_t;

static inline uint64_t BDK_DDFX_PF_MBOX_INT_W1SX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_MBOX_INT_W1SX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b==0)))
        return 0x809000000420ll + 0ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("DDFX_PF_MBOX_INT_W1SX", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_MBOX_INT_W1SX(a,b) bdk_ddfx_pf_mbox_int_w1sx_t
#define bustype_BDK_DDFX_PF_MBOX_INT_W1SX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_MBOX_INT_W1SX(a,b) "DDFX_PF_MBOX_INT_W1SX"
#define device_bar_BDK_DDFX_PF_MBOX_INT_W1SX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_MBOX_INT_W1SX(a,b) (a)
#define arguments_BDK_DDFX_PF_MBOX_INT_W1SX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_msix_pba#
 *
 * DDF PF MSI-X Pending-Bit-Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the
 * DDF_PF_INT_VEC_E enumeration.
 */
union bdk_ddfx_pf_msix_pbax
{
    uint64_t u;
    struct bdk_ddfx_pf_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated DDF()_PF_MSIX_VEC()_CTL, enumerated by
                                                                 DDF_PF_INT_VEC_E. Bits that have no associated DDF_PF_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated DDF()_PF_MSIX_VEC()_CTL, enumerated by
                                                                 DDF_PF_INT_VEC_E. Bits that have no associated DDF_PF_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_msix_pbax_s cn; */
};
typedef union bdk_ddfx_pf_msix_pbax bdk_ddfx_pf_msix_pbax_t;

static inline uint64_t BDK_DDFX_PF_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b==0)))
        return 0x8090100f0000ll + 0ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("DDFX_PF_MSIX_PBAX", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_MSIX_PBAX(a,b) bdk_ddfx_pf_msix_pbax_t
#define bustype_BDK_DDFX_PF_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_MSIX_PBAX(a,b) "DDFX_PF_MSIX_PBAX"
#define device_bar_BDK_DDFX_PF_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_DDFX_PF_MSIX_PBAX(a,b) (a)
#define arguments_BDK_DDFX_PF_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_msix_vec#_addr
 *
 * DDF PF MSI-X Vector-Table Address Registers
 * This register is the MSI-X vector table, indexed by the DDF_PF_INT_VEC_E enumeration.
 */
union bdk_ddfx_pf_msix_vecx_addr
{
    uint64_t u;
    struct bdk_ddfx_pf_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's DDF()_PF_MSIX_VEC()_ADDR, DDF()_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of DDF()_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_DDF_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's DDF()_PF_MSIX_VEC()_ADDR, DDF()_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of DDF()_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_DDF_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_msix_vecx_addr_s cn; */
};
typedef union bdk_ddfx_pf_msix_vecx_addr bdk_ddfx_pf_msix_vecx_addr_t;

static inline uint64_t BDK_DDFX_PF_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=3)))
        return 0x809010000000ll + 0ll * ((a) & 0x0) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("DDFX_PF_MSIX_VECX_ADDR", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_MSIX_VECX_ADDR(a,b) bdk_ddfx_pf_msix_vecx_addr_t
#define bustype_BDK_DDFX_PF_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_MSIX_VECX_ADDR(a,b) "DDFX_PF_MSIX_VECX_ADDR"
#define device_bar_BDK_DDFX_PF_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_DDFX_PF_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_DDFX_PF_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_msix_vec#_ctl
 *
 * DDF PF MSI-X Vector-Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the DDF_PF_INT_VEC_E enumeration.
 */
union bdk_ddfx_pf_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_ddfx_pf_msix_vecx_ctl_s
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
    /* struct bdk_ddfx_pf_msix_vecx_ctl_s cn; */
};
typedef union bdk_ddfx_pf_msix_vecx_ctl bdk_ddfx_pf_msix_vecx_ctl_t;

static inline uint64_t BDK_DDFX_PF_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=3)))
        return 0x809010000008ll + 0ll * ((a) & 0x0) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("DDFX_PF_MSIX_VECX_CTL", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_MSIX_VECX_CTL(a,b) bdk_ddfx_pf_msix_vecx_ctl_t
#define bustype_BDK_DDFX_PF_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_MSIX_VECX_CTL(a,b) "DDFX_PF_MSIX_VECX_CTL"
#define device_bar_BDK_DDFX_PF_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_DDFX_PF_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_DDFX_PF_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_noint0_ena_w1c
 *
 * INTERNAL: DDF Unused Interrupt Enable Clear Registers
 *
 * This register clears interrupt enable bits.
 */
union bdk_ddfx_pf_noint0_ena_w1c
{
    uint64_t u;
    struct bdk_ddfx_pf_noint0_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t noint0                : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for DDF(0)_PF_NOINT0_INT[NOINT0]. */
#else /* Word 0 - Little Endian */
        uint64_t noint0                : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for DDF(0)_PF_NOINT0_INT[NOINT0]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_noint0_ena_w1c_s cn; */
};
typedef union bdk_ddfx_pf_noint0_ena_w1c bdk_ddfx_pf_noint0_ena_w1c_t;

static inline uint64_t BDK_DDFX_PF_NOINT0_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_NOINT0_ENA_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000540ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_NOINT0_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_NOINT0_ENA_W1C(a) bdk_ddfx_pf_noint0_ena_w1c_t
#define bustype_BDK_DDFX_PF_NOINT0_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_NOINT0_ENA_W1C(a) "DDFX_PF_NOINT0_ENA_W1C"
#define device_bar_BDK_DDFX_PF_NOINT0_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_NOINT0_ENA_W1C(a) (a)
#define arguments_BDK_DDFX_PF_NOINT0_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_noint0_ena_w1s
 *
 * INTERNAL: DDF Unused Interrupt Enable Set Registers
 *
 * This register sets interrupt enable bits.
 */
union bdk_ddfx_pf_noint0_ena_w1s
{
    uint64_t u;
    struct bdk_ddfx_pf_noint0_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t noint0                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for DDF(0)_PF_NOINT0_INT[NOINT0]. */
#else /* Word 0 - Little Endian */
        uint64_t noint0                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for DDF(0)_PF_NOINT0_INT[NOINT0]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_noint0_ena_w1s_s cn; */
};
typedef union bdk_ddfx_pf_noint0_ena_w1s bdk_ddfx_pf_noint0_ena_w1s_t;

static inline uint64_t BDK_DDFX_PF_NOINT0_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_NOINT0_ENA_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000560ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_NOINT0_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_NOINT0_ENA_W1S(a) bdk_ddfx_pf_noint0_ena_w1s_t
#define bustype_BDK_DDFX_PF_NOINT0_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_NOINT0_ENA_W1S(a) "DDFX_PF_NOINT0_ENA_W1S"
#define device_bar_BDK_DDFX_PF_NOINT0_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_NOINT0_ENA_W1S(a) (a)
#define arguments_BDK_DDFX_PF_NOINT0_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_noint0_int
 *
 * INTERNAL: DDF Unused Interrupt Registers
 *
 * Internal:
 * This register exists only to aid alignment with CDE interrupts.
 */
union bdk_ddfx_pf_noint0_int
{
    uint64_t u;
    struct bdk_ddfx_pf_noint0_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t noint0                : 64; /**< [ 63:  0](R/W1C/H) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t noint0                : 64; /**< [ 63:  0](R/W1C/H) Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_noint0_int_s cn; */
};
typedef union bdk_ddfx_pf_noint0_int bdk_ddfx_pf_noint0_int_t;

static inline uint64_t BDK_DDFX_PF_NOINT0_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_NOINT0_INT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000500ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_NOINT0_INT", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_NOINT0_INT(a) bdk_ddfx_pf_noint0_int_t
#define bustype_BDK_DDFX_PF_NOINT0_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_NOINT0_INT(a) "DDFX_PF_NOINT0_INT"
#define device_bar_BDK_DDFX_PF_NOINT0_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_NOINT0_INT(a) (a)
#define arguments_BDK_DDFX_PF_NOINT0_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_noint0_int_w1s
 *
 * INTERNAL: DDF Unused Interrupt Set Registers
 *
 * This register sets interrupt bits.
 */
union bdk_ddfx_pf_noint0_int_w1s
{
    uint64_t u;
    struct bdk_ddfx_pf_noint0_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t noint0                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets DDF(0)_PF_NOINT0_INT[NOINT0]. */
#else /* Word 0 - Little Endian */
        uint64_t noint0                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets DDF(0)_PF_NOINT0_INT[NOINT0]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_noint0_int_w1s_s cn; */
};
typedef union bdk_ddfx_pf_noint0_int_w1s bdk_ddfx_pf_noint0_int_w1s_t;

static inline uint64_t BDK_DDFX_PF_NOINT0_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_NOINT0_INT_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000520ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_NOINT0_INT_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_NOINT0_INT_W1S(a) bdk_ddfx_pf_noint0_int_w1s_t
#define bustype_BDK_DDFX_PF_NOINT0_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_NOINT0_INT_W1S(a) "DDFX_PF_NOINT0_INT_W1S"
#define device_bar_BDK_DDFX_PF_NOINT0_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_NOINT0_INT_W1S(a) (a)
#define arguments_BDK_DDFX_PF_NOINT0_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_noint1_ena_w1c
 *
 * INTERNAL: DDF Unused Interrupt Enable Clear Registers
 *
 * This register clears interrupt enable bits.
 */
union bdk_ddfx_pf_noint1_ena_w1c
{
    uint64_t u;
    struct bdk_ddfx_pf_noint1_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t noint1                : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for DDF(0)_PF_NOINT1_INT[NOINT1]. */
#else /* Word 0 - Little Endian */
        uint64_t noint1                : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for DDF(0)_PF_NOINT1_INT[NOINT1]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_noint1_ena_w1c_s cn; */
};
typedef union bdk_ddfx_pf_noint1_ena_w1c bdk_ddfx_pf_noint1_ena_w1c_t;

static inline uint64_t BDK_DDFX_PF_NOINT1_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_NOINT1_ENA_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x8090000005a0ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_NOINT1_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_NOINT1_ENA_W1C(a) bdk_ddfx_pf_noint1_ena_w1c_t
#define bustype_BDK_DDFX_PF_NOINT1_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_NOINT1_ENA_W1C(a) "DDFX_PF_NOINT1_ENA_W1C"
#define device_bar_BDK_DDFX_PF_NOINT1_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_NOINT1_ENA_W1C(a) (a)
#define arguments_BDK_DDFX_PF_NOINT1_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_noint1_ena_w1s
 *
 * INTERNAL: DDF Unused Interrupt Enable Set Registers
 *
 * This register sets interrupt enable bits.
 */
union bdk_ddfx_pf_noint1_ena_w1s
{
    uint64_t u;
    struct bdk_ddfx_pf_noint1_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t noint1                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for DDF(0)_PF_NOINT1_INT[NOINT1]. */
#else /* Word 0 - Little Endian */
        uint64_t noint1                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for DDF(0)_PF_NOINT1_INT[NOINT1]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_noint1_ena_w1s_s cn; */
};
typedef union bdk_ddfx_pf_noint1_ena_w1s bdk_ddfx_pf_noint1_ena_w1s_t;

static inline uint64_t BDK_DDFX_PF_NOINT1_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_NOINT1_ENA_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x8090000005b0ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_NOINT1_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_NOINT1_ENA_W1S(a) bdk_ddfx_pf_noint1_ena_w1s_t
#define bustype_BDK_DDFX_PF_NOINT1_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_NOINT1_ENA_W1S(a) "DDFX_PF_NOINT1_ENA_W1S"
#define device_bar_BDK_DDFX_PF_NOINT1_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_NOINT1_ENA_W1S(a) (a)
#define arguments_BDK_DDFX_PF_NOINT1_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_noint1_int
 *
 * INTERNAL: DDF Unused Interrupt Registers
 *
 * Internal:
 * This register exists only to aid alignment with CDE interrupts.
 */
union bdk_ddfx_pf_noint1_int
{
    uint64_t u;
    struct bdk_ddfx_pf_noint1_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t noint1                : 64; /**< [ 63:  0](R/W1C/H) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t noint1                : 64; /**< [ 63:  0](R/W1C/H) Reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_noint1_int_s cn; */
};
typedef union bdk_ddfx_pf_noint1_int bdk_ddfx_pf_noint1_int_t;

static inline uint64_t BDK_DDFX_PF_NOINT1_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_NOINT1_INT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000580ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_NOINT1_INT", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_NOINT1_INT(a) bdk_ddfx_pf_noint1_int_t
#define bustype_BDK_DDFX_PF_NOINT1_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_NOINT1_INT(a) "DDFX_PF_NOINT1_INT"
#define device_bar_BDK_DDFX_PF_NOINT1_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_NOINT1_INT(a) (a)
#define arguments_BDK_DDFX_PF_NOINT1_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_noint1_int_w1s
 *
 * INTERNAL: DDF Unused Interrupt Set Registers
 *
 * This register sets interrupt bits.
 */
union bdk_ddfx_pf_noint1_int_w1s
{
    uint64_t u;
    struct bdk_ddfx_pf_noint1_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t noint1                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets DDF(0)_PF_NOINT1_INT[NOINT1]. */
#else /* Word 0 - Little Endian */
        uint64_t noint1                : 64; /**< [ 63:  0](R/W1S/H) Reads or sets DDF(0)_PF_NOINT1_INT[NOINT1]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_noint1_int_w1s_s cn; */
};
typedef union bdk_ddfx_pf_noint1_int_w1s bdk_ddfx_pf_noint1_int_w1s_t;

static inline uint64_t BDK_DDFX_PF_NOINT1_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_NOINT1_INT_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000590ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_NOINT1_INT_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_NOINT1_INT_W1S(a) bdk_ddfx_pf_noint1_int_w1s_t
#define bustype_BDK_DDFX_PF_NOINT1_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_NOINT1_INT_W1S(a) "DDFX_PF_NOINT1_INT_W1S"
#define device_bar_BDK_DDFX_PF_NOINT1_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_NOINT1_INT_W1S(a) (a)
#define arguments_BDK_DDFX_PF_NOINT1_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_q#_ctl
 *
 * DDF Queue Control Register
 * This register configures queues. This register should be changed only when quiescent
 * (see DDF()_VQ()_INPROG[INFLIGHT]).
 */
union bdk_ddfx_pf_qx_ctl
{
    uint64_t u;
    struct bdk_ddfx_pf_qx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t aura                  : 12; /**< [ 59: 48](R/W) Guest-aura for returning this queue's instruction-chunk buffers to FPA.
                                                                 Only used when [INST_FREE] is set.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and DDF()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t reserved_45_47        : 3;
        uint64_t size                  : 13; /**< [ 44: 32](R/W) Command-buffer size, in number of 64-bit words per command buffer segment.
                                                                 Must be 16*n + 1, where n is the number of instructions per buffer segment. */
        uint64_t reserved_11_31        : 21;
        uint64_t cont_err              : 1;  /**< [ 10: 10](R/W) Continue on error.

                                                                 0 = When DDF()_VQ()_MISC_INT[NWRP], DDF()_VQ()_MISC_INT[IRDE] or
                                                                 DDF()_VQ()_MISC_INT[DOVF] are set by hardware or software via
                                                                 DDF(0)_VQ()_MISC_INT_W1S, then DDF()_VQ()_CTL[ENA] is cleared.  Due to
                                                                 pipelining, additional instructions may have been processed between the
                                                                 instruction causing the error and the next instruction in the disabled queue
                                                                 (the instruction at DDF()_VQ()_SADDR).

                                                                 1 = Ignore errors and continue processing instructions. For diagnostic use only. */
        uint64_t inst_free             : 1;  /**< [  9:  9](R/W) Instruction FPA free. When set, when DDF reaches the end of an instruction
                                                                 chunk, that chunk will be freed to the FPA. */
        uint64_t inst_be               : 1;  /**< [  8:  8](R/W) Instruction big-endian control. When set, instructions, instruction next chunk
                                                                 pointers, and result structures are stored in big-endian format in memory. */
        uint64_t iqb_ldwb              : 1;  /**< [  7:  7](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues NCB transient load (LDT) towards the cache, which if the
                                                                 line hits and is is dirty will cause the line to be written back before being
                                                                 replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Reads that do not consume the last word of a cache line always use LDI. */
        uint64_t reserved_2_6          : 5;
        uint64_t grp                   : 1;  /**< [  1:  1](R/W) Engine group. For optimal performance group 0 should always be used for
                                                                 DDF_INST_FIND_S instructions and group 1 for DDF_INST_MATCH_S instructions. */
        uint64_t pri                   : 1;  /**< [  0:  0](R/W) Queue priority.
                                                                 1 = This queue has higher priority. Round-robin between higher priority queues.
                                                                 0 = This queue has lower priority. Round-robin between lower priority queues. */
#else /* Word 0 - Little Endian */
        uint64_t pri                   : 1;  /**< [  0:  0](R/W) Queue priority.
                                                                 1 = This queue has higher priority. Round-robin between higher priority queues.
                                                                 0 = This queue has lower priority. Round-robin between lower priority queues. */
        uint64_t grp                   : 1;  /**< [  1:  1](R/W) Engine group. For optimal performance group 0 should always be used for
                                                                 DDF_INST_FIND_S instructions and group 1 for DDF_INST_MATCH_S instructions. */
        uint64_t reserved_2_6          : 5;
        uint64_t iqb_ldwb              : 1;  /**< [  7:  7](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues NCB transient load (LDT) towards the cache, which if the
                                                                 line hits and is is dirty will cause the line to be written back before being
                                                                 replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Reads that do not consume the last word of a cache line always use LDI. */
        uint64_t inst_be               : 1;  /**< [  8:  8](R/W) Instruction big-endian control. When set, instructions, instruction next chunk
                                                                 pointers, and result structures are stored in big-endian format in memory. */
        uint64_t inst_free             : 1;  /**< [  9:  9](R/W) Instruction FPA free. When set, when DDF reaches the end of an instruction
                                                                 chunk, that chunk will be freed to the FPA. */
        uint64_t cont_err              : 1;  /**< [ 10: 10](R/W) Continue on error.

                                                                 0 = When DDF()_VQ()_MISC_INT[NWRP], DDF()_VQ()_MISC_INT[IRDE] or
                                                                 DDF()_VQ()_MISC_INT[DOVF] are set by hardware or software via
                                                                 DDF(0)_VQ()_MISC_INT_W1S, then DDF()_VQ()_CTL[ENA] is cleared.  Due to
                                                                 pipelining, additional instructions may have been processed between the
                                                                 instruction causing the error and the next instruction in the disabled queue
                                                                 (the instruction at DDF()_VQ()_SADDR).

                                                                 1 = Ignore errors and continue processing instructions. For diagnostic use only. */
        uint64_t reserved_11_31        : 21;
        uint64_t size                  : 13; /**< [ 44: 32](R/W) Command-buffer size, in number of 64-bit words per command buffer segment.
                                                                 Must be 16*n + 1, where n is the number of instructions per buffer segment. */
        uint64_t reserved_45_47        : 3;
        uint64_t aura                  : 12; /**< [ 59: 48](R/W) Guest-aura for returning this queue's instruction-chunk buffers to FPA.
                                                                 Only used when [INST_FREE] is set.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and DDF()_PF_Q()_GMCTL[GMID] as valid. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_qx_ctl_s cn; */
};
typedef union bdk_ddfx_pf_qx_ctl bdk_ddfx_pf_qx_ctl_t;

static inline uint64_t BDK_DDFX_PF_QX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_QX_CTL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809008000000ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_PF_QX_CTL", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_QX_CTL(a,b) bdk_ddfx_pf_qx_ctl_t
#define bustype_BDK_DDFX_PF_QX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_QX_CTL(a,b) "DDFX_PF_QX_CTL"
#define device_bar_BDK_DDFX_PF_QX_CTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_QX_CTL(a,b) (a)
#define arguments_BDK_DDFX_PF_QX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_q#_ctl2
 *
 * DDF Queue Control 2 Register
 * This register configures queues. This register should be changed only when quiescent
 * (see DDF()_VQ()_INPROG[INFLIGHT]).
 */
union bdk_ddfx_pf_qx_ctl2
{
    uint64_t u;
    struct bdk_ddfx_pf_qx_ctl2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t cachedis              : 1;  /**< [  4:  4](R/W) No caching.
                                                                 0 = DDF may cache read/writes between instructions if the IOVA and [STRM] match.
                                                                 1 = DDF may cache read/writes within an instruction, but will flush and
                                                                 invalidate the cache after completing an instruction to this queue.
                                                                 Multiple engines will not access the cache simultaniously, reducing engine
                                                                 parallelism. */
        uint64_t d_st_cmd              : 2;  /**< [  3:  2](R/W) Which NCB store command to use for filter/record data writes.
                                                                 0x0 = STP for partial cache lines, STF for full cache lines.
                                                                 0x1 = STT. Store and don't allocate.
                                                                 0x2 = STY. Store and allocate. */
        uint64_t d_ld_cmd              : 2;  /**< [  1:  0](R/W) Which NCB load command to use for filter/record data reads.
                                                                 0x0 = LDD. Read and cache.
                                                                 0x1 = LDI. Read and cache read-only.
                                                                 0x2 = LDE. Read and cache with write-intent.
                                                                 0x3 = LDY. Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t d_ld_cmd              : 2;  /**< [  1:  0](R/W) Which NCB load command to use for filter/record data reads.
                                                                 0x0 = LDD. Read and cache.
                                                                 0x1 = LDI. Read and cache read-only.
                                                                 0x2 = LDE. Read and cache with write-intent.
                                                                 0x3 = LDY. Reserved. */
        uint64_t d_st_cmd              : 2;  /**< [  3:  2](R/W) Which NCB store command to use for filter/record data writes.
                                                                 0x0 = STP for partial cache lines, STF for full cache lines.
                                                                 0x1 = STT. Store and don't allocate.
                                                                 0x2 = STY. Store and allocate. */
        uint64_t cachedis              : 1;  /**< [  4:  4](R/W) No caching.
                                                                 0 = DDF may cache read/writes between instructions if the IOVA and [STRM] match.
                                                                 1 = DDF may cache read/writes within an instruction, but will flush and
                                                                 invalidate the cache after completing an instruction to this queue.
                                                                 Multiple engines will not access the cache simultaniously, reducing engine
                                                                 parallelism. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_qx_ctl2_s cn; */
};
typedef union bdk_ddfx_pf_qx_ctl2 bdk_ddfx_pf_qx_ctl2_t;

static inline uint64_t BDK_DDFX_PF_QX_CTL2(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_QX_CTL2(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809008000100ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_PF_QX_CTL2", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_QX_CTL2(a,b) bdk_ddfx_pf_qx_ctl2_t
#define bustype_BDK_DDFX_PF_QX_CTL2(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_QX_CTL2(a,b) "DDFX_PF_QX_CTL2"
#define device_bar_BDK_DDFX_PF_QX_CTL2(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_QX_CTL2(a,b) (a)
#define arguments_BDK_DDFX_PF_QX_CTL2(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_q#_gmctl
 *
 * DDF Queue Guest Machine Control Register
 * This register configures queues. This register should be changed only when quiescent
 * (see DDF()_VQ()_INPROG[INFLIGHT]).
 */
union bdk_ddfx_pf_qx_gmctl
{
    uint64_t u;
    struct bdk_ddfx_pf_qx_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Low 8 bits of the SMMU stream identifier to use when issuing requests.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc.

                                                                 Maximum legal value is 64. */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer free, or to SSO for all submit work operations initiated by this queue.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer free, or to SSO for all submit work operations initiated by this queue.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
        uint64_t strm                  : 8;  /**< [ 23: 16](R/W) Low 8 bits of the SMMU stream identifier to use when issuing requests.

                                                                 Stream 0x0 corresponds to the PF, and VFs start at 0x1.

                                                                 Reset such that VF0/index 0 is 0x1, VF1/index 1 is 0x2, etc.

                                                                 Maximum legal value is 64. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_qx_gmctl_s cn; */
};
typedef union bdk_ddfx_pf_qx_gmctl bdk_ddfx_pf_qx_gmctl_t;

static inline uint64_t BDK_DDFX_PF_QX_GMCTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_QX_GMCTL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809008000020ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_PF_QX_GMCTL", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_PF_QX_GMCTL(a,b) bdk_ddfx_pf_qx_gmctl_t
#define bustype_BDK_DDFX_PF_QX_GMCTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_QX_GMCTL(a,b) "DDFX_PF_QX_GMCTL"
#define device_bar_BDK_DDFX_PF_QX_GMCTL(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_QX_GMCTL(a,b) (a)
#define arguments_BDK_DDFX_PF_QX_GMCTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_pf_rd_latency_pc
 *
 * DDF PF Read Latency Counter Register
 */
union bdk_ddfx_pf_rd_latency_pc
{
    uint64_t u;
    struct bdk_ddfx_pf_rd_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for L2C read returns. Incremented every
                                                                 coprocessor-clock by the number of transactions outstanding in that cycle. This
                                                                 may be divided by DDF()_PF_RD_REQ_PC to determine the average read latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for L2C read returns. Incremented every
                                                                 coprocessor-clock by the number of transactions outstanding in that cycle. This
                                                                 may be divided by DDF()_PF_RD_REQ_PC to determine the average read latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_rd_latency_pc_s cn; */
};
typedef union bdk_ddfx_pf_rd_latency_pc bdk_ddfx_pf_rd_latency_pc_t;

static inline uint64_t BDK_DDFX_PF_RD_LATENCY_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_RD_LATENCY_PC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000010060ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_RD_LATENCY_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_RD_LATENCY_PC(a) bdk_ddfx_pf_rd_latency_pc_t
#define bustype_BDK_DDFX_PF_RD_LATENCY_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_RD_LATENCY_PC(a) "DDFX_PF_RD_LATENCY_PC"
#define device_bar_BDK_DDFX_PF_RD_LATENCY_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_RD_LATENCY_PC(a) (a)
#define arguments_BDK_DDFX_PF_RD_LATENCY_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_rd_req_pc
 *
 * DDF PF Read Request Performance Counter Register
 */
union bdk_ddfx_pf_rd_req_pc
{
    uint64_t u;
    struct bdk_ddfx_pf_rd_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of L2C read requests. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of L2C read requests. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_rd_req_pc_s cn; */
};
typedef union bdk_ddfx_pf_rd_req_pc bdk_ddfx_pf_rd_req_pc_t;

static inline uint64_t BDK_DDFX_PF_RD_REQ_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_RD_REQ_PC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000010040ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_RD_REQ_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_RD_REQ_PC(a) bdk_ddfx_pf_rd_req_pc_t
#define bustype_BDK_DDFX_PF_RD_REQ_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_RD_REQ_PC(a) "DDFX_PF_RD_REQ_PC"
#define device_bar_BDK_DDFX_PF_RD_REQ_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_RD_REQ_PC(a) (a)
#define arguments_BDK_DDFX_PF_RD_REQ_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_reset
 *
 * DDF PF Reset Register
 * This register controls clock and reset.
 */
union bdk_ddfx_pf_reset
{
    uint64_t u;
    struct bdk_ddfx_pf_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1) Reset one-shot pulse to reset DDF subsystem. */
#else /* Word 0 - Little Endian */
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1) Reset one-shot pulse to reset DDF subsystem. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_reset_s cn; */
};
typedef union bdk_ddfx_pf_reset bdk_ddfx_pf_reset_t;

static inline uint64_t BDK_DDFX_PF_RESET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_RESET(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x809000000100ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("DDFX_PF_RESET", 1, a, 0, 0, 0);
}

#define typedef_BDK_DDFX_PF_RESET(a) bdk_ddfx_pf_reset_t
#define bustype_BDK_DDFX_PF_RESET(a) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_RESET(a) "DDFX_PF_RESET"
#define device_bar_BDK_DDFX_PF_RESET(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_RESET(a) (a)
#define arguments_BDK_DDFX_PF_RESET(a) (a),-1,-1,-1

/**
 * Register (NCB) ddf#_pf_vf#_mbox#
 *
 * DDF PF/VF Mailbox Registers
 */
union bdk_ddfx_pf_vfx_mboxx
{
    uint64_t u;
    struct bdk_ddfx_pf_vfx_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 DDF()_VF()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing DDF()_PF_VF()_MBOX(0) (but not
                                                                 DDF()_VF()_PF_MBOX(0)) will set the corresponding
                                                                 DDF()_VQ()_MISC_INT[MBOX] which if appropriately enabled will send an interrupt
                                                                 to the VF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 DDF()_VF()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing DDF()_PF_VF()_MBOX(0) (but not
                                                                 DDF()_VF()_PF_MBOX(0)) will set the corresponding
                                                                 DDF()_VQ()_MISC_INT[MBOX] which if appropriately enabled will send an interrupt
                                                                 to the VF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_pf_vfx_mboxx_s cn; */
};
typedef union bdk_ddfx_pf_vfx_mboxx bdk_ddfx_pf_vfx_mboxx_t;

static inline uint64_t BDK_DDFX_PF_VFX_MBOXX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_PF_VFX_MBOXX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63) && (c<=1)))
        return 0x809008001000ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 0x100ll * ((c) & 0x1);
    __bdk_csr_fatal("DDFX_PF_VFX_MBOXX", 3, a, b, c, 0);
}

#define typedef_BDK_DDFX_PF_VFX_MBOXX(a,b,c) bdk_ddfx_pf_vfx_mboxx_t
#define bustype_BDK_DDFX_PF_VFX_MBOXX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_PF_VFX_MBOXX(a,b,c) "DDFX_PF_VFX_MBOXX"
#define device_bar_BDK_DDFX_PF_VFX_MBOXX(a,b,c) 0x0 /* PF_BAR0 */
#define busnum_BDK_DDFX_PF_VFX_MBOXX(a,b,c) (a)
#define arguments_BDK_DDFX_PF_VFX_MBOXX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) ddf#_vf#_msix_pba#
 *
 * DDF VF MSI-X Pending-Bit-Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the DDF_VF_INT_VEC_E
 * enumeration.
 */
union bdk_ddfx_vfx_msix_pbax
{
    uint64_t u;
    struct bdk_ddfx_vfx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated DDF()_PF_MSIX_VEC()_CTL, enumerated by
                                                                 DDF_PF_INT_VEC_E. Bits that have no associated DDF_PF_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated DDF()_PF_MSIX_VEC()_CTL, enumerated by
                                                                 DDF_PF_INT_VEC_E. Bits that have no associated DDF_PF_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vfx_msix_pbax_s cn; */
};
typedef union bdk_ddfx_vfx_msix_pbax bdk_ddfx_vfx_msix_pbax_t;

static inline uint64_t BDK_DDFX_VFX_MSIX_PBAX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VFX_MSIX_PBAX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63) && (c==0)))
        return 0x8090300f0000ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 8ll * ((c) & 0x0);
    __bdk_csr_fatal("DDFX_VFX_MSIX_PBAX", 3, a, b, c, 0);
}

#define typedef_BDK_DDFX_VFX_MSIX_PBAX(a,b,c) bdk_ddfx_vfx_msix_pbax_t
#define bustype_BDK_DDFX_VFX_MSIX_PBAX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VFX_MSIX_PBAX(a,b,c) "DDFX_VFX_MSIX_PBAX"
#define device_bar_BDK_DDFX_VFX_MSIX_PBAX(a,b,c) 0x4 /* VF_BAR4 */
#define busnum_BDK_DDFX_VFX_MSIX_PBAX(a,b,c) (a)
#define arguments_BDK_DDFX_VFX_MSIX_PBAX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) ddf#_vf#_msix_vec#_addr
 *
 * DDF VF MSI-X Vector-Table Address Registers
 * This register is the MSI-X vector table, indexed by the DDF_VF_INT_VEC_E enumeration.
 */
union bdk_ddfx_vfx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_ddfx_vfx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_DDF_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_DDF_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vfx_msix_vecx_addr_s cn; */
};
typedef union bdk_ddfx_vfx_msix_vecx_addr bdk_ddfx_vfx_msix_vecx_addr_t;

static inline uint64_t BDK_DDFX_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63) && (c<=1)))
        return 0x809030000000ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 0x10ll * ((c) & 0x1);
    __bdk_csr_fatal("DDFX_VFX_MSIX_VECX_ADDR", 3, a, b, c, 0);
}

#define typedef_BDK_DDFX_VFX_MSIX_VECX_ADDR(a,b,c) bdk_ddfx_vfx_msix_vecx_addr_t
#define bustype_BDK_DDFX_VFX_MSIX_VECX_ADDR(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VFX_MSIX_VECX_ADDR(a,b,c) "DDFX_VFX_MSIX_VECX_ADDR"
#define device_bar_BDK_DDFX_VFX_MSIX_VECX_ADDR(a,b,c) 0x4 /* VF_BAR4 */
#define busnum_BDK_DDFX_VFX_MSIX_VECX_ADDR(a,b,c) (a)
#define arguments_BDK_DDFX_VFX_MSIX_VECX_ADDR(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) ddf#_vf#_msix_vec#_ctl
 *
 * DDF VF MSI-X Vector-Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the DDF_VF_INT_VEC_E enumeration.
 */
union bdk_ddfx_vfx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_ddfx_vfx_msix_vecx_ctl_s
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
    /* struct bdk_ddfx_vfx_msix_vecx_ctl_s cn; */
};
typedef union bdk_ddfx_vfx_msix_vecx_ctl bdk_ddfx_vfx_msix_vecx_ctl_t;

static inline uint64_t BDK_DDFX_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63) && (c<=1)))
        return 0x809030000008ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 0x10ll * ((c) & 0x1);
    __bdk_csr_fatal("DDFX_VFX_MSIX_VECX_CTL", 3, a, b, c, 0);
}

#define typedef_BDK_DDFX_VFX_MSIX_VECX_CTL(a,b,c) bdk_ddfx_vfx_msix_vecx_ctl_t
#define bustype_BDK_DDFX_VFX_MSIX_VECX_CTL(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VFX_MSIX_VECX_CTL(a,b,c) "DDFX_VFX_MSIX_VECX_CTL"
#define device_bar_BDK_DDFX_VFX_MSIX_VECX_CTL(a,b,c) 0x4 /* VF_BAR4 */
#define busnum_BDK_DDFX_VFX_MSIX_VECX_CTL(a,b,c) (a)
#define arguments_BDK_DDFX_VFX_MSIX_VECX_CTL(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) ddf#_vf#_pf_mbox#
 *
 * DDF VF/PF Mailbox Registers
 */
union bdk_ddfx_vfx_pf_mboxx
{
    uint64_t u;
    struct bdk_ddfx_vfx_pf_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using DDF()_PF_VF()_MBOX(). MBOX(0) is
                                                                 typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 DDF()_VF()_PF_MBOX(1) (but not DDF()_PF_VF()_MBOX(1)) will set the
                                                                 corresponding DDF()_PF_MBOX_INT() bit, which if appropriately enabled will send an
                                                                 interrupt to the PF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using DDF()_PF_VF()_MBOX(). MBOX(0) is
                                                                 typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 DDF()_VF()_PF_MBOX(1) (but not DDF()_PF_VF()_MBOX(1)) will set the
                                                                 corresponding DDF()_PF_MBOX_INT() bit, which if appropriately enabled will send an
                                                                 interrupt to the PF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vfx_pf_mboxx_s cn; */
};
typedef union bdk_ddfx_vfx_pf_mboxx bdk_ddfx_vfx_pf_mboxx_t;

static inline uint64_t BDK_DDFX_VFX_PF_MBOXX(unsigned long a, unsigned long b, unsigned long c) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VFX_PF_MBOXX(unsigned long a, unsigned long b, unsigned long c)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63) && (c<=1)))
        return 0x809020001000ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f) + 8ll * ((c) & 0x1);
    __bdk_csr_fatal("DDFX_VFX_PF_MBOXX", 3, a, b, c, 0);
}

#define typedef_BDK_DDFX_VFX_PF_MBOXX(a,b,c) bdk_ddfx_vfx_pf_mboxx_t
#define bustype_BDK_DDFX_VFX_PF_MBOXX(a,b,c) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VFX_PF_MBOXX(a,b,c) "DDFX_VFX_PF_MBOXX"
#define device_bar_BDK_DDFX_VFX_PF_MBOXX(a,b,c) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VFX_PF_MBOXX(a,b,c) (a)
#define arguments_BDK_DDFX_VFX_PF_MBOXX(a,b,c) (a),(b),(c),-1

/**
 * Register (NCB) ddf#_vq#_ctl
 *
 * DDF VF Queue Control Registers
 * This register configures queues. This register should be changed (other than
 * clearing [ENA]) only when quiescent (see DDF()_VQ()_INPROG[INFLIGHT]).
 */
union bdk_ddfx_vqx_ctl
{
    uint64_t u;
    struct bdk_ddfx_vqx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) Enables the logical instruction queue. See also DDF()_PF_Q()_CTL[CONT_ERR] and
                                                                 DDF()_VQ()_INPROG[INFLIGHT].
                                                                 1 = Queue is enabled.
                                                                 0 = Queue is disabled. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) Enables the logical instruction queue. See also DDF()_PF_Q()_CTL[CONT_ERR] and
                                                                 DDF()_VQ()_INPROG[INFLIGHT].
                                                                 1 = Queue is enabled.
                                                                 0 = Queue is disabled. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_ctl_s cn; */
};
typedef union bdk_ddfx_vqx_ctl bdk_ddfx_vqx_ctl_t;

static inline uint64_t BDK_DDFX_VQX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_CTL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000100ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_CTL", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_CTL(a,b) bdk_ddfx_vqx_ctl_t
#define bustype_BDK_DDFX_VQX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_CTL(a,b) "DDFX_VQX_CTL"
#define device_bar_BDK_DDFX_VQX_CTL(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_CTL(a,b) (a)
#define arguments_BDK_DDFX_VQX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_done
 *
 * DDF Queue Done Count Registers
 * These registers contain the per-queue instruction done count.
 */
union bdk_ddfx_vqx_done
{
    uint64_t u;
    struct bdk_ddfx_vqx_done_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t done                  : 20; /**< [ 19:  0](R/W/H) Done count. When DDF_INST_S[DONEINT] set and that instruction completes,
                                                                 DDF()_VQ()_DONE[DONE] is incremented when the instruction finishes. Write to
                                                                 this field are for diagnostic use only; instead software writes
                                                                 DDF()_VQ()_DONE_ACK with the number of decrements for this field.

                                                                 Interrupts are sent as follows:

                                                                 * When DDF()_VQ()_DONE[DONE] = 0, then no results are pending, the interrupt
                                                                 coalescing timer is held to zero, and an interrupt is not sent.

                                                                 * When DDF()_VQ()_DONE[DONE] != 0, then the interrupt coalescing timer
                                                                 counts. If the counter is \>= DDF()_VQ()_DONE_WAIT[TIME_WAIT]*1024, or
                                                                 DDF()_VQ()_DONE[DONE] \>= DDF()_VQ()_DONE_WAIT[NUM_WAIT], i.e. enough time has
                                                                 passed or enough results have arrived, then the interrupt is sent.  Otherwise,
                                                                 it is not sent due to coalescing.

                                                                 * When DDF()_VQ()_DONE_ACK is written (or DDF()_VQ()_DONE is written but this is
                                                                 not typical), the interrupt coalescing timer restarts.  Note after decrementing
                                                                 this interrupt equation is recomputed, for example if DDF()_VQ()_DONE[DONE] \>=
                                                                 DDF()_VQ()_DONE_WAIT[NUM_WAIT] and because the timer is zero, the interrupt will
                                                                 be resent immediately.  (This covers the race case between software
                                                                 acknowledging an interrupt and a result returning.)

                                                                 * When DDF()_VQ()_DONE_ENA_W1S[DONE] = 0, interrupts are not sent, but the
                                                                 counting described above still occurs.

                                                                 Since DDF instructions complete out-of-order, if software is using completion
                                                                 interrupts the suggested scheme is to request a DONEINT on each request, and
                                                                 when an interrupt arrives perform a "greedy" scan for completions; even if a
                                                                 later command is acknowledged first this will not result in missing a
                                                                 completion.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 20; /**< [ 19:  0](R/W/H) Done count. When DDF_INST_S[DONEINT] set and that instruction completes,
                                                                 DDF()_VQ()_DONE[DONE] is incremented when the instruction finishes. Write to
                                                                 this field are for diagnostic use only; instead software writes
                                                                 DDF()_VQ()_DONE_ACK with the number of decrements for this field.

                                                                 Interrupts are sent as follows:

                                                                 * When DDF()_VQ()_DONE[DONE] = 0, then no results are pending, the interrupt
                                                                 coalescing timer is held to zero, and an interrupt is not sent.

                                                                 * When DDF()_VQ()_DONE[DONE] != 0, then the interrupt coalescing timer
                                                                 counts. If the counter is \>= DDF()_VQ()_DONE_WAIT[TIME_WAIT]*1024, or
                                                                 DDF()_VQ()_DONE[DONE] \>= DDF()_VQ()_DONE_WAIT[NUM_WAIT], i.e. enough time has
                                                                 passed or enough results have arrived, then the interrupt is sent.  Otherwise,
                                                                 it is not sent due to coalescing.

                                                                 * When DDF()_VQ()_DONE_ACK is written (or DDF()_VQ()_DONE is written but this is
                                                                 not typical), the interrupt coalescing timer restarts.  Note after decrementing
                                                                 this interrupt equation is recomputed, for example if DDF()_VQ()_DONE[DONE] \>=
                                                                 DDF()_VQ()_DONE_WAIT[NUM_WAIT] and because the timer is zero, the interrupt will
                                                                 be resent immediately.  (This covers the race case between software
                                                                 acknowledging an interrupt and a result returning.)

                                                                 * When DDF()_VQ()_DONE_ENA_W1S[DONE] = 0, interrupts are not sent, but the
                                                                 counting described above still occurs.

                                                                 Since DDF instructions complete out-of-order, if software is using completion
                                                                 interrupts the suggested scheme is to request a DONEINT on each request, and
                                                                 when an interrupt arrives perform a "greedy" scan for completions; even if a
                                                                 later command is acknowledged first this will not result in missing a
                                                                 completion.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_done_s cn; */
};
typedef union bdk_ddfx_vqx_done bdk_ddfx_vqx_done_t;

static inline uint64_t BDK_DDFX_VQX_DONE(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_DONE(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000420ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_DONE", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_DONE(a,b) bdk_ddfx_vqx_done_t
#define bustype_BDK_DDFX_VQX_DONE(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_DONE(a,b) "DDFX_VQX_DONE"
#define device_bar_BDK_DDFX_VQX_DONE(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_DONE(a,b) (a)
#define arguments_BDK_DDFX_VQX_DONE(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_done_ack
 *
 * DDF Queue Done Count Ack Registers
 * This register is written by software to acknowledge interrupts.
 */
union bdk_ddfx_vqx_done_ack
{
    uint64_t u;
    struct bdk_ddfx_vqx_done_ack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to DDF()_VQ()_DONE[DONE]. Reads DDF()_VQ()_DONE[DONE].

                                                                 Written by software to acknowledge interrupts. If DDF()_VQ()_DONE[DONE] is still
                                                                 nonzero the interrupt will be re-sent if the conditions described in
                                                                 DDF()_VQ()_DONE[DONE] are satisfied. */
#else /* Word 0 - Little Endian */
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to DDF()_VQ()_DONE[DONE]. Reads DDF()_VQ()_DONE[DONE].

                                                                 Written by software to acknowledge interrupts. If DDF()_VQ()_DONE[DONE] is still
                                                                 nonzero the interrupt will be re-sent if the conditions described in
                                                                 DDF()_VQ()_DONE[DONE] are satisfied. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_done_ack_s cn; */
};
typedef union bdk_ddfx_vqx_done_ack bdk_ddfx_vqx_done_ack_t;

static inline uint64_t BDK_DDFX_VQX_DONE_ACK(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_DONE_ACK(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000440ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_DONE_ACK", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_DONE_ACK(a,b) bdk_ddfx_vqx_done_ack_t
#define bustype_BDK_DDFX_VQX_DONE_ACK(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_DONE_ACK(a,b) "DDFX_VQX_DONE_ACK"
#define device_bar_BDK_DDFX_VQX_DONE_ACK(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_DONE_ACK(a,b) (a)
#define arguments_BDK_DDFX_VQX_DONE_ACK(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_done_ena_w1c
 *
 * DDF Queue Done Interrupt Enable Clear Registers
 */
union bdk_ddfx_vqx_done_ena_w1c
{
    uint64_t u;
    struct bdk_ddfx_vqx_done_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Read or clears DDF()_VQ()_DONE_ENA_W1S[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Read or clears DDF()_VQ()_DONE_ENA_W1S[DONE]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_done_ena_w1c_s cn; */
};
typedef union bdk_ddfx_vqx_done_ena_w1c bdk_ddfx_vqx_done_ena_w1c_t;

static inline uint64_t BDK_DDFX_VQX_DONE_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_DONE_ENA_W1C(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000478ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_DONE_ENA_W1C", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_DONE_ENA_W1C(a,b) bdk_ddfx_vqx_done_ena_w1c_t
#define bustype_BDK_DDFX_VQX_DONE_ENA_W1C(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_DONE_ENA_W1C(a,b) "DDFX_VQX_DONE_ENA_W1C"
#define device_bar_BDK_DDFX_VQX_DONE_ENA_W1C(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_DONE_ENA_W1C(a,b) (a)
#define arguments_BDK_DDFX_VQX_DONE_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_done_ena_w1s
 *
 * DDF Queue Done Interrupt Enable Set Registers
 * Write 1 to these registers will enable the DONEINT interrupt for the queue.
 */
union bdk_ddfx_vqx_done_ena_w1s
{
    uint64_t u;
    struct bdk_ddfx_vqx_done_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Write 1 will enable DONEINT for this queue. Write 0 has no effect.
                                                                 Read will return the enable bit. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Write 1 will enable DONEINT for this queue. Write 0 has no effect.
                                                                 Read will return the enable bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_done_ena_w1s_s cn; */
};
typedef union bdk_ddfx_vqx_done_ena_w1s bdk_ddfx_vqx_done_ena_w1s_t;

static inline uint64_t BDK_DDFX_VQX_DONE_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_DONE_ENA_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000470ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_DONE_ENA_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_DONE_ENA_W1S(a,b) bdk_ddfx_vqx_done_ena_w1s_t
#define bustype_BDK_DDFX_VQX_DONE_ENA_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_DONE_ENA_W1S(a,b) "DDFX_VQX_DONE_ENA_W1S"
#define device_bar_BDK_DDFX_VQX_DONE_ENA_W1S(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_DONE_ENA_W1S(a,b) (a)
#define arguments_BDK_DDFX_VQX_DONE_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_done_int_w1c
 *
 * DDF Queue Done Interrupt Clear Registers
 */
union bdk_ddfx_vqx_done_int_w1c
{
    uint64_t u;
    struct bdk_ddfx_vqx_done_int_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See DDF()_VQ()_DONE[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use DDF()_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 DDF()_VQ()_DONE[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See DDF()_VQ()_DONE[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use DDF()_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 DDF()_VQ()_DONE[DONE]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_done_int_w1c_s cn; */
};
typedef union bdk_ddfx_vqx_done_int_w1c bdk_ddfx_vqx_done_int_w1c_t;

static inline uint64_t BDK_DDFX_VQX_DONE_INT_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_DONE_INT_W1C(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000468ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_DONE_INT_W1C", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_DONE_INT_W1C(a,b) bdk_ddfx_vqx_done_int_w1c_t
#define bustype_BDK_DDFX_VQX_DONE_INT_W1C(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_DONE_INT_W1C(a,b) "DDFX_VQX_DONE_INT_W1C"
#define device_bar_BDK_DDFX_VQX_DONE_INT_W1C(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_DONE_INT_W1C(a,b) (a)
#define arguments_BDK_DDFX_VQX_DONE_INT_W1C(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_done_int_w1s
 *
 * DDF Queue Done Interrupt Set Registers
 */
union bdk_ddfx_vqx_done_int_w1s
{
    uint64_t u;
    struct bdk_ddfx_vqx_done_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See DDF()_VQ()_DONE[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use DDF()_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 DDF()_VQ()_DONE[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See DDF()_VQ()_DONE[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use DDF()_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 DDF()_VQ()_DONE[DONE]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_done_int_w1s_s cn; */
};
typedef union bdk_ddfx_vqx_done_int_w1s bdk_ddfx_vqx_done_int_w1s_t;

static inline uint64_t BDK_DDFX_VQX_DONE_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_DONE_INT_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000460ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_DONE_INT_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_DONE_INT_W1S(a,b) bdk_ddfx_vqx_done_int_w1s_t
#define bustype_BDK_DDFX_VQX_DONE_INT_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_DONE_INT_W1S(a,b) "DDFX_VQX_DONE_INT_W1S"
#define device_bar_BDK_DDFX_VQX_DONE_INT_W1S(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_DONE_INT_W1S(a,b) (a)
#define arguments_BDK_DDFX_VQX_DONE_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_done_wait
 *
 * DDF Queue Done Interrupt Coalescing Wait Registers
 * Specifies the per queue interrupt coalescing settings.
 */
union bdk_ddfx_vqx_done_wait
{
    uint64_t u;
    struct bdk_ddfx_vqx_done_wait_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t time_wait             : 16; /**< [ 47: 32](R/W) Time hold-off. When DDF()_VQ()_DONE[DONE] = 0, or DDF()_VQ()_DONE_ACK is written
                                                                 a timer is cleared. When the timer reaches [TIME_WAIT]*1024 then interrupt
                                                                 coalescing ends; see DDF()_VQ()_DONE[DONE]. If 0x0, time coalescing is disabled. */
        uint64_t reserved_20_31        : 12;
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of messages hold-off. When DDF()_VQ()_DONE[DONE] \>= [NUM_WAIT] then
                                                                 interrupt coalescing ends; see DDF()_VQ()_DONE[DONE]. If 0x0, same behavior as
                                                                 0x1. */
#else /* Word 0 - Little Endian */
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of messages hold-off. When DDF()_VQ()_DONE[DONE] \>= [NUM_WAIT] then
                                                                 interrupt coalescing ends; see DDF()_VQ()_DONE[DONE]. If 0x0, same behavior as
                                                                 0x1. */
        uint64_t reserved_20_31        : 12;
        uint64_t time_wait             : 16; /**< [ 47: 32](R/W) Time hold-off. When DDF()_VQ()_DONE[DONE] = 0, or DDF()_VQ()_DONE_ACK is written
                                                                 a timer is cleared. When the timer reaches [TIME_WAIT]*1024 then interrupt
                                                                 coalescing ends; see DDF()_VQ()_DONE[DONE]. If 0x0, time coalescing is disabled. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_done_wait_s cn; */
};
typedef union bdk_ddfx_vqx_done_wait bdk_ddfx_vqx_done_wait_t;

static inline uint64_t BDK_DDFX_VQX_DONE_WAIT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_DONE_WAIT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000400ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_DONE_WAIT", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_DONE_WAIT(a,b) bdk_ddfx_vqx_done_wait_t
#define bustype_BDK_DDFX_VQX_DONE_WAIT(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_DONE_WAIT(a,b) "DDFX_VQX_DONE_WAIT"
#define device_bar_BDK_DDFX_VQX_DONE_WAIT(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_DONE_WAIT(a,b) (a)
#define arguments_BDK_DDFX_VQX_DONE_WAIT(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_doorbell
 *
 * DDF Queue Doorbell Registers
 * Doorbells for the DDF instruction queues.
 */
union bdk_ddfx_vqx_doorbell
{
    uint64_t u;
    struct bdk_ddfx_vqx_doorbell_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) Number of instruction queue 64-bit words to add to the DDF instruction doorbell
                                                                 count.  Readback value is the the current number of pending doorbell requests.
                                                                 If counter overflows DDF()_VQ()_MISC_INT[DBELL_DOVF] is set.

                                                                 To reset the count back to zero, write one to clear
                                                                 DDF()_VQ()_MISC_INT_ENA_W1C[DBELL_DOVF], then write a value of 2^20 minus the
                                                                 read [DBELL_CNT], then write one to DDF()_VQ()_MISC_INT_W1C[DBELL_DOVF] and
                                                                 DDF()_VQ()_MISC_INT_ENA_W1S[DBELL_DOVF].

                                                                 CPT: Must be a multiple of 8. All CPT instructions are 8 words and require a
                                                                 doorbell count of multiple of 8.

                                                                 DDF: Must be a multiple of 16. All DDF instructions are 16 words and require a
                                                                 doorbell count of multiple of 16. */
#else /* Word 0 - Little Endian */
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) Number of instruction queue 64-bit words to add to the DDF instruction doorbell
                                                                 count.  Readback value is the the current number of pending doorbell requests.
                                                                 If counter overflows DDF()_VQ()_MISC_INT[DBELL_DOVF] is set.

                                                                 To reset the count back to zero, write one to clear
                                                                 DDF()_VQ()_MISC_INT_ENA_W1C[DBELL_DOVF], then write a value of 2^20 minus the
                                                                 read [DBELL_CNT], then write one to DDF()_VQ()_MISC_INT_W1C[DBELL_DOVF] and
                                                                 DDF()_VQ()_MISC_INT_ENA_W1S[DBELL_DOVF].

                                                                 CPT: Must be a multiple of 8. All CPT instructions are 8 words and require a
                                                                 doorbell count of multiple of 8.

                                                                 DDF: Must be a multiple of 16. All DDF instructions are 16 words and require a
                                                                 doorbell count of multiple of 16. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_doorbell_s cn; */
};
typedef union bdk_ddfx_vqx_doorbell bdk_ddfx_vqx_doorbell_t;

static inline uint64_t BDK_DDFX_VQX_DOORBELL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_DOORBELL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000600ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_DOORBELL", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_DOORBELL(a,b) bdk_ddfx_vqx_doorbell_t
#define bustype_BDK_DDFX_VQX_DOORBELL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_DOORBELL(a,b) "DDFX_VQX_DOORBELL"
#define device_bar_BDK_DDFX_VQX_DOORBELL(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_DOORBELL(a,b) (a)
#define arguments_BDK_DDFX_VQX_DOORBELL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_inprog
 *
 * DDF Queue In Progress Count Registers
 * These registers contain the per-queue instruction in flight registers.
 */
union bdk_ddfx_vqx_inprog
{
    uint64_t u;
    struct bdk_ddfx_vqx_inprog_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t inflight              : 8;  /**< [  7:  0](RO/H) Inflight count. Counts the number of instructions for the VF for which DDF is
                                                                 fetching, executing or responding to instructions. However this does not include
                                                                 any interrupts that are awaiting software handling (DDF()_VQ()_DONE[DONE] !=
                                                                 0x0).

                                                                 A queue may not be reconfigured until:
                                                                   1. DDF()_VQ()_CTL[ENA] is cleared by software.
                                                                   2. [INFLIGHT] is polled until equals to zero. */
#else /* Word 0 - Little Endian */
        uint64_t inflight              : 8;  /**< [  7:  0](RO/H) Inflight count. Counts the number of instructions for the VF for which DDF is
                                                                 fetching, executing or responding to instructions. However this does not include
                                                                 any interrupts that are awaiting software handling (DDF()_VQ()_DONE[DONE] !=
                                                                 0x0).

                                                                 A queue may not be reconfigured until:
                                                                   1. DDF()_VQ()_CTL[ENA] is cleared by software.
                                                                   2. [INFLIGHT] is polled until equals to zero. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_inprog_s cn; */
};
typedef union bdk_ddfx_vqx_inprog bdk_ddfx_vqx_inprog_t;

static inline uint64_t BDK_DDFX_VQX_INPROG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_INPROG(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000410ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_INPROG", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_INPROG(a,b) bdk_ddfx_vqx_inprog_t
#define bustype_BDK_DDFX_VQX_INPROG(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_INPROG(a,b) "DDFX_VQX_INPROG"
#define device_bar_BDK_DDFX_VQX_INPROG(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_INPROG(a,b) (a)
#define arguments_BDK_DDFX_VQX_INPROG(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_misc_ena_w1c
 *
 * DDF Queue Misc Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_ddfx_vqx_misc_ena_w1c
{
    uint64_t u;
    struct bdk_ddfx_vqx_misc_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for DDF(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_misc_ena_w1c_s cn; */
};
typedef union bdk_ddfx_vqx_misc_ena_w1c bdk_ddfx_vqx_misc_ena_w1c_t;

static inline uint64_t BDK_DDFX_VQX_MISC_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_MISC_ENA_W1C(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000518ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_MISC_ENA_W1C", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_MISC_ENA_W1C(a,b) bdk_ddfx_vqx_misc_ena_w1c_t
#define bustype_BDK_DDFX_VQX_MISC_ENA_W1C(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_MISC_ENA_W1C(a,b) "DDFX_VQX_MISC_ENA_W1C"
#define device_bar_BDK_DDFX_VQX_MISC_ENA_W1C(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_MISC_ENA_W1C(a,b) (a)
#define arguments_BDK_DDFX_VQX_MISC_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_misc_ena_w1s
 *
 * DDF Queue Misc Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_ddfx_vqx_misc_ena_w1s
{
    uint64_t u;
    struct bdk_ddfx_vqx_misc_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for DDF(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_misc_ena_w1s_s cn; */
};
typedef union bdk_ddfx_vqx_misc_ena_w1s bdk_ddfx_vqx_misc_ena_w1s_t;

static inline uint64_t BDK_DDFX_VQX_MISC_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_MISC_ENA_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000510ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_MISC_ENA_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_MISC_ENA_W1S(a,b) bdk_ddfx_vqx_misc_ena_w1s_t
#define bustype_BDK_DDFX_VQX_MISC_ENA_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_MISC_ENA_W1S(a,b) "DDFX_VQX_MISC_ENA_W1S"
#define device_bar_BDK_DDFX_VQX_MISC_ENA_W1S(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_MISC_ENA_W1S(a,b) (a)
#define arguments_BDK_DDFX_VQX_MISC_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_misc_int
 *
 * DDF Queue Misc Interrupt Register
 * These registers contain the per-queue miscellaneous interrupts.
 */
union bdk_ddfx_vqx_misc_int
{
    uint64_t u;
    struct bdk_ddfx_vqx_misc_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Translation fault detected. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Hardware error from engines. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reserved. Never set by DDF hardware. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) NCB result write response error. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Instruction NCB read response error. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Doorbell overflow. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) PF to VF mailbox interrupt. Set when DDF(0)_VF(0..63)_PF_MBOX(0)
                                                                 is written. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) PF to VF mailbox interrupt. Set when DDF(0)_VF(0..63)_PF_MBOX(0)
                                                                 is written. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1C/H) Doorbell overflow. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1C/H) Instruction NCB read response error. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1C/H) NCB result write response error. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1C/H) Reserved. Never set by DDF hardware. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1C/H) Hardware error from engines. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1C/H) Translation fault detected. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_misc_int_s cn; */
};
typedef union bdk_ddfx_vqx_misc_int bdk_ddfx_vqx_misc_int_t;

static inline uint64_t BDK_DDFX_VQX_MISC_INT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_MISC_INT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000500ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_MISC_INT", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_MISC_INT(a,b) bdk_ddfx_vqx_misc_int_t
#define bustype_BDK_DDFX_VQX_MISC_INT(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_MISC_INT(a,b) "DDFX_VQX_MISC_INT"
#define device_bar_BDK_DDFX_VQX_MISC_INT(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_MISC_INT(a,b) (a)
#define arguments_BDK_DDFX_VQX_MISC_INT(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_misc_int_w1s
 *
 * DDF Queue Misc Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_ddfx_vqx_misc_int_w1s
{
    uint64_t u;
    struct bdk_ddfx_vqx_misc_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[MBOX]. */
        uint64_t dovf                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[IRDE]. */
        uint64_t nwrp                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[NWRP]. */
        uint64_t swerr                 : 1;  /**< [  4:  4](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[SWERR]. */
        uint64_t hwerr                 : 1;  /**< [  5:  5](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[HWERR]. */
        uint64_t fault                 : 1;  /**< [  6:  6](R/W1S/H) Reads or sets DDF(0)_VQ(0..63)_MISC_INT[FAULT]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_misc_int_w1s_s cn; */
};
typedef union bdk_ddfx_vqx_misc_int_w1s bdk_ddfx_vqx_misc_int_w1s_t;

static inline uint64_t BDK_DDFX_VQX_MISC_INT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_MISC_INT_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000508ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_MISC_INT_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_MISC_INT_W1S(a,b) bdk_ddfx_vqx_misc_int_w1s_t
#define bustype_BDK_DDFX_VQX_MISC_INT_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_MISC_INT_W1S(a,b) "DDFX_VQX_MISC_INT_W1S"
#define device_bar_BDK_DDFX_VQX_MISC_INT_W1S(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_MISC_INT_W1S(a,b) (a)
#define arguments_BDK_DDFX_VQX_MISC_INT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB) ddf#_vq#_saddr
 *
 * DDF Queue Starting Buffer Address Registers
 * These registers set the instruction buffer starting address.
 */
union bdk_ddfx_vqx_saddr
{
    uint64_t u;
    struct bdk_ddfx_vqx_saddr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t ptr                   : 43; /**< [ 48:  6](R/W/H) Instruction buffer IOVA \<48:7\> (128-byte aligned). When written, it is the initial
                                                                 buffer starting address; when read, it is the next read pointer to be requested from L2C.
                                                                 [PTR] is overwritten with the next pointer each time that the command buffer
                                                                 segment is exhausted. New commands will then be read from the newly specified command
                                                                 buffer pointer.

                                                                 Bit\<6\> must be zero. */
        uint64_t off                   : 6;  /**< [  5:  0](RAZ) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t off                   : 6;  /**< [  5:  0](RAZ) Reserved. */
        uint64_t ptr                   : 43; /**< [ 48:  6](R/W/H) Instruction buffer IOVA \<48:7\> (128-byte aligned). When written, it is the initial
                                                                 buffer starting address; when read, it is the next read pointer to be requested from L2C.
                                                                 [PTR] is overwritten with the next pointer each time that the command buffer
                                                                 segment is exhausted. New commands will then be read from the newly specified command
                                                                 buffer pointer.

                                                                 Bit\<6\> must be zero. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ddfx_vqx_saddr_s cn; */
};
typedef union bdk_ddfx_vqx_saddr bdk_ddfx_vqx_saddr_t;

static inline uint64_t BDK_DDFX_VQX_SADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DDFX_VQX_SADDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a==0) && (b<=63)))
        return 0x809020000200ll + 0ll * ((a) & 0x0) + 0x100000ll * ((b) & 0x3f);
    __bdk_csr_fatal("DDFX_VQX_SADDR", 2, a, b, 0, 0);
}

#define typedef_BDK_DDFX_VQX_SADDR(a,b) bdk_ddfx_vqx_saddr_t
#define bustype_BDK_DDFX_VQX_SADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_DDFX_VQX_SADDR(a,b) "DDFX_VQX_SADDR"
#define device_bar_BDK_DDFX_VQX_SADDR(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_DDFX_VQX_SADDR(a,b) (a)
#define arguments_BDK_DDFX_VQX_SADDR(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_DDF_H__ */
