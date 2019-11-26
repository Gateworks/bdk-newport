#ifndef __BDK_CSRS_REE_H__
#define __BDK_CSRS_REE_H__
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
 * OcteonTX REE.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration ree_af_int_vec_e
 *
 * REE MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_REE_AF_INT_VEC_E_AQ (3)
#define BDK_REE_AF_INT_VEC_E_QUE_DONE (2)
#define BDK_REE_AF_INT_VEC_E_RAS (0)
#define BDK_REE_AF_INT_VEC_E_RVU (1)

/**
 * Enumeration ree_desc_mode_e
 *
 * REE Descriptor Mode Flag Enumeration
 * Enumerates REE_INST_S[REE_JOB_CTRL.MODE] and REE_RES_S[REE_RES_STATUS.MODE].
 * Internal:
 * These encodings must be kept updated with Titan REE IP.
 */
#define BDK_REE_DESC_MODE_E_HPM (1)
#define BDK_REE_DESC_MODE_E_NORMAL (0)
#define BDK_REE_DESC_MODE_E_STOP_ANY_MATCH (2)

/**
 * Enumeration ree_desc_type_e
 *
 * REE Descriptor Type Flag Enumeration
 * Enumerates REE_INST_S[REE_JOB_CTRL.TYPE] and REE_RES_S[REE_RES_STATUS.TYPE].
 * Internal:
 * These encodings must be kept updated with Titan REE IP.
 */
#define BDK_REE_DESC_TYPE_E_TYPE_JOB_DESC (0)
#define BDK_REE_DESC_TYPE_E_TYPE_RESULT_DESC (1)

/**
 * Enumeration ree_l2ld_cmd_e
 *
 * REE Load Type Enumeration
 * Enumerates the type of NCB command to use for loads. See REE_AF_QUE()_GCFG[IL2LD_CMD],
 * REE_AF_QUE()_GCFG[PL2LD_CMD], and REE_AF_CTL_CFG[RL2LD_CMD].
 *
 * Internal:
 * If a reserved value is used, hardare defaults to LDI.
 */
#define BDK_REE_L2LD_CMD_E_LDD (0)
#define BDK_REE_L2LD_CMD_E_LDE (2)
#define BDK_REE_L2LD_CMD_E_LDI (1)
#define BDK_REE_L2LD_CMD_E_LDT (4)
#define BDK_REE_L2LD_CMD_E_LDWB (5)
#define BDK_REE_L2LD_CMD_E_LDY (3)

/**
 * Enumeration ree_lf_int_vec_e
 *
 * REE MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_REE_LF_INT_VEC_E_MISC (1)
#define BDK_REE_LF_INT_VEC_E_QUE_DONE (0)

/**
 * Enumeration ree_rof_type_e
 *
 * REE ROF Type Enumeration
 * Enumerates the type of a ROF entry. See REE_ROF_S.
 */
#define BDK_REE_ROF_TYPE_E_CHECK_CSR_CHECKSUM (4)
#define BDK_REE_ROF_TYPE_E_CHECK_CSR_CHECKSUM_EXCLUDE_EM (5)
#define BDK_REE_ROF_TYPE_E_CHECK_CSR_EQ (1)
#define BDK_REE_ROF_TYPE_E_CHECK_CSR_GTE (2)
#define BDK_REE_ROF_TYPE_E_CHECK_CSR_LTE (3)
#define BDK_REE_ROF_TYPE_E_EM (7)
#define BDK_REE_ROF_TYPE_E_IM (6)
#define BDK_REE_ROF_TYPE_E_LEGACY_INSTR (0)

/**
 * Enumeration ree_rtru_init_mode_e
 *
 * Memory Initialization Mode Enumeration
 * Enumerates REE_AF_REEXR_CTRL.INIT_MODE.
 * Internal:
 * These encodings must be kept updated with Titan REE IP.
 */
#define BDK_REE_RTRU_INIT_MODE_E_INIT_MODE_1 (1)
#define BDK_REE_RTRU_INIT_MODE_E_INIT_MODE_2 (2)
#define BDK_REE_RTRU_INIT_MODE_E_RESERVED_INIT_MODE_0 (0)
#define BDK_REE_RTRU_INIT_MODE_E_RESERVED_INIT_MODE_3 (3)

/**
 * Enumeration ree_stype_e
 *
 * REE Store Type Enumeration
 * Enumerates the type of NCB command to use for stores. See REE_AF_QUE()_GCFG[MATCH_STYPE]
 * and REE_AF_QUE()_GCFG[DESCR_STYPE].
 */
#define BDK_REE_STYPE_E_STF (0)
#define BDK_REE_STYPE_E_STP (2)
#define BDK_REE_STYPE_E_STT (1)
#define BDK_REE_STYPE_E_STY (3)

/**
 * Structure ree_af_aq_inst_s
 *
 * REE Administrative Queue Structure
 * This structure describes an administrative instruction.
 */
union bdk_ree_af_aq_inst_s
{
    uint64_t u[2];
    struct bdk_ree_af_aq_inst_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t rof_ptr_addr          : 64; /**< [ 63:  0] ROF data IOVA byte pointer into LLC/DRAM attached memory.
                                                                 Behavior is unpredictable if the address is 0x0.
                                                                 Address must be 128 byte aligned.
                                                                 Address should point to a REE_ROF_S. */
#else /* Word 0 - Little Endian */
        uint64_t rof_ptr_addr          : 64; /**< [ 63:  0] ROF data IOVA byte pointer into LLC/DRAM attached memory.
                                                                 Behavior is unpredictable if the address is 0x0.
                                                                 Address must be 128 byte aligned.
                                                                 Address should point to a REE_ROF_S. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_111_127      : 17;
        uint64_t length                : 15; /**< [110: 96] Is the number of bytes pointed at by [ROF_PTR_ADDR].  [LENGTH] must be nonzero,
                                                                 and multiple of 16 bytes. Maximum length field is 16384 bytes. */
        uint64_t reserved_68_95        : 28;
        uint64_t doneint               : 1;  /**< [ 67: 67] Done interrupt.
                                                                 When [DONEINT] is set and the instruction completes,
                                                                 REE_AF_AQ_DONE[DONE] will be incremented.
                                                                 Typically, this will be set only on instructions that require handoff
                                                                 between hardware and software (for example, on the last programming instruction in a
                                                                 sequence). */
        uint64_t reserved_66           : 1;
        uint64_t nc                    : 1;  /**< [ 65: 65] No cache allocation. [NC] may be set in any case to indicate that the read
                                                                 operations generated should preferably not load cache blocks into the LLC. */
        uint64_t reserved_64           : 1;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64           : 1;
        uint64_t nc                    : 1;  /**< [ 65: 65] No cache allocation. [NC] may be set in any case to indicate that the read
                                                                 operations generated should preferably not load cache blocks into the LLC. */
        uint64_t reserved_66           : 1;
        uint64_t doneint               : 1;  /**< [ 67: 67] Done interrupt.
                                                                 When [DONEINT] is set and the instruction completes,
                                                                 REE_AF_AQ_DONE[DONE] will be incremented.
                                                                 Typically, this will be set only on instructions that require handoff
                                                                 between hardware and software (for example, on the last programming instruction in a
                                                                 sequence). */
        uint64_t reserved_68_95        : 28;
        uint64_t length                : 15; /**< [110: 96] Is the number of bytes pointed at by [ROF_PTR_ADDR].  [LENGTH] must be nonzero,
                                                                 and multiple of 16 bytes. Maximum length field is 16384 bytes. */
        uint64_t reserved_111_127      : 17;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_ree_af_aq_inst_s_s cn; */
};

/**
 * Structure ree_gptr_s
 *
 * REE Generic Pointer Structure
 * This structure is the generic format of pointers in REE_INST_S and in data gather lists.
 */
union bdk_ree_gptr_s
{
    uint64_t u[2];
    struct bdk_ree_gptr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t addr                  : 64; /**< [ 63:  0] When a REE_GPTR_S is in an instruction word, [ADDR] is either:
                                                                 * (a) A direct IOVA byte pointer into LLC/DRAM attached memory.
                                                                 * Or, (b) an IOVA pointer to a data gather list in memory.

                                                                 When a REE_GPTR_S is in a data gather list, [ADDR] is:
                                                                 * (c) An IOVA direct byte pointer into the attached memory.

                                                                 In case (b) above, [ADDR]\<3:0\> must be zero. (Gather list pointers must be 16 byte aligned).

                                                                 In cases (a) or (c) above, for input data pointers, [ADDR] may have any byte alignment.

                                                                 In all cases, bits \<63:53\> are ignored by hardware; software should use a
                                                                 sign-extended bit \<52\> for forward compatibility. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 64; /**< [ 63:  0] When a REE_GPTR_S is in an instruction word, [ADDR] is either:
                                                                 * (a) A direct IOVA byte pointer into LLC/DRAM attached memory.
                                                                 * Or, (b) an IOVA pointer to a data gather list in memory.

                                                                 When a REE_GPTR_S is in a data gather list, [ADDR] is:
                                                                 * (c) An IOVA direct byte pointer into the attached memory.

                                                                 In case (b) above, [ADDR]\<3:0\> must be zero. (Gather list pointers must be 16 byte aligned).

                                                                 In cases (a) or (c) above, for input data pointers, [ADDR] may have any byte alignment.

                                                                 In all cases, bits \<63:53\> are ignored by hardware; software should use a
                                                                 sign-extended bit \<52\> for forward compatibility. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_111_127      : 17;
        uint64_t length                : 15; /**< [110: 96] In case (a) and (c) in the [ADDR] description, [LENGTH] is the number of bytes pointed
                                                                 at by [ADDR].  [LENGTH] must be nonzero in this case and maximum length field is 16384 bytes.
                                                                 In case (b) in the [ADDR] description, [LENGTH] is the number of gather list
                                                                 pointer entries pointed at by [ADDR]. ([LENGTH]*16 is the number of bytes.) [LENGTH]
                                                                 must be at least 1 in this case and maximum of 8. */
        uint64_t reserved_66_95        : 30;
        uint64_t nc                    : 1;  /**< [ 65: 65] No cache allocation. [NC] may be set in any case to indicate that the read
                                                                 operations generated should preferably not load cache blocks into the LLC.
                                                                 Note in case (b) above, [NC] indicates that the gather list should not be
                                                                 loaded into the cache.
                                                                 Note in cases (a) and (c) above, [NC] indicates that the data or results
                                                                 should not be loaded into the LLC. */
        uint64_t reserved_64           : 1;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64           : 1;
        uint64_t nc                    : 1;  /**< [ 65: 65] No cache allocation. [NC] may be set in any case to indicate that the read
                                                                 operations generated should preferably not load cache blocks into the LLC.
                                                                 Note in case (b) above, [NC] indicates that the gather list should not be
                                                                 loaded into the cache.
                                                                 Note in cases (a) and (c) above, [NC] indicates that the data or results
                                                                 should not be loaded into the LLC. */
        uint64_t reserved_66_95        : 30;
        uint64_t length                : 15; /**< [110: 96] In case (a) and (c) in the [ADDR] description, [LENGTH] is the number of bytes pointed
                                                                 at by [ADDR].  [LENGTH] must be nonzero in this case and maximum length field is 16384 bytes.
                                                                 In case (b) in the [ADDR] description, [LENGTH] is the number of gather list
                                                                 pointer entries pointed at by [ADDR]. ([LENGTH]*16 is the number of bytes.) [LENGTH]
                                                                 must be at least 1 in this case and maximum of 8. */
        uint64_t reserved_111_127      : 17;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_ree_gptr_s_s cn; */
};

/**
 * Structure ree_inst_s
 *
 * REE Instruction Structure
 * Each REE instruction has 8 words (called w0 to w7 within the structure).
 */
union bdk_ree_inst_s
{
    uint64_t u[8];
    struct bdk_ree_inst_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ooj                   : 1;  /**< [  8:  8] Out-of-order job:
                                                                   All jobs that submit work to SSO MUST set this field to zero.
                                                                 0 = This job must retire after previously issued in-order jobs to this queue.
                                                                     Ordering is maintained within queues only.
                                                                 1 = This job can be retired as soon as REE engine returns job completion. */
        uint64_t reserved_5_7          : 3;
        uint64_t dg                    : 1;  /**< [  4:  4] Data gather:
                                                                 0 = [INP_PTR_ADDR] points directly to the actual job input data and can be at any byte offset.
                                                                 1 = [INP_PTR_ADDR] points to a gather list of pointers that are read
                                                                 by the REE coprocessor to locate the actual job input data.
                                                                 The [INP_PTR_ADDR] must be 128-byte aligned, and the [INP_PTR_CTL]'s LENGTH field,
                                                                 indicating the number of pointers in the gather list, must be between 1-8. */
        uint64_t reserved_1_3          : 3;
        uint64_t doneint               : 1;  /**< [  0:  0] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, REE_LF_DONE[DONE] will be incremented,
                                                                 and may cause an interrupt.

                                                                 REE increments REE_LF_DONE[DONE] after it writes the REE_RES_S and receives STDN (see
                                                                 [RES_PTR_ADDR]), but the increment is unordered relative any SSO submit (see
                                                                 [WQ_PTR]). [OOJ] has no direct affect on when any REE_LF_DONE[DONE] increment occurs.

                                                                 When [DONEINT] is set and the instruction completes,
                                                                 REE_LF_DONE[DONE] will be incremented. */
#else /* Word 0 - Little Endian */
        uint64_t doneint               : 1;  /**< [  0:  0] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, REE_LF_DONE[DONE] will be incremented,
                                                                 and may cause an interrupt.

                                                                 REE increments REE_LF_DONE[DONE] after it writes the REE_RES_S and receives STDN (see
                                                                 [RES_PTR_ADDR]), but the increment is unordered relative any SSO submit (see
                                                                 [WQ_PTR]). [OOJ] has no direct affect on when any REE_LF_DONE[DONE] increment occurs.

                                                                 When [DONEINT] is set and the instruction completes,
                                                                 REE_LF_DONE[DONE] will be incremented. */
        uint64_t reserved_1_3          : 3;
        uint64_t dg                    : 1;  /**< [  4:  4] Data gather:
                                                                 0 = [INP_PTR_ADDR] points directly to the actual job input data and can be at any byte offset.
                                                                 1 = [INP_PTR_ADDR] points to a gather list of pointers that are read
                                                                 by the REE coprocessor to locate the actual job input data.
                                                                 The [INP_PTR_ADDR] must be 128-byte aligned, and the [INP_PTR_CTL]'s LENGTH field,
                                                                 indicating the number of pointers in the gather list, must be between 1-8. */
        uint64_t reserved_5_7          : 3;
        uint64_t ooj                   : 1;  /**< [  8:  8] Out-of-order job:
                                                                   All jobs that submit work to SSO MUST set this field to zero.
                                                                 0 = This job must retire after previously issued in-order jobs to this queue.
                                                                     Ordering is maintained within queues only.
                                                                 1 = This job can be retired as soon as REE engine returns job completion. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t inp_ptr_addr          : 64; /**< [127: 64] Input data pointer address (REE_GPTR_S format address word definition).
                                                                 Must be nonzero. */
#else /* Word 1 - Little Endian */
        uint64_t inp_ptr_addr          : 64; /**< [127: 64] Input data pointer address (REE_GPTR_S format address word definition).
                                                                 Must be nonzero. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t inp_ptr_ctl           : 64; /**< [191:128] Input data pointer control (REE_GPTR_S format control word definition).
                                                                 For input gather mode, REE_INST_S[DG] must also be set. */
#else /* Word 2 - Little Endian */
        uint64_t inp_ptr_ctl           : 64; /**< [191:128] Input data pointer control (REE_GPTR_S format control word definition).
                                                                 For input gather mode, REE_INST_S[DG] must also be set. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t res_ptr_addr          : 64; /**< [255:192] Job result start pointer 128-byte aligned IOVA.
                                                                 Pointer to start of the location where the job result data (REE_RES_S) and
                                                                 job match data output (REE_MATCH_S) will be written by the REE coprocessor.

                                                                 The REE coprocessor will write exactly 1 job result structure (REE_RES_S)
                                                                 to address [RES_PTR_ADDR]

                                                                 The REE coprocessor will write up to 254 job match structures (REE_MATCH_S)
                                                                 starting at address [RES_PTR_ADDR] + 0x80.

                                                                 REE cannot write the REE_RES_S until after it guarantees that all LLC/DRAM writes have completed
                                                                 related to REE_MATCH_S.

                                                                 If REE_AF_QUE()_GCFG[STRICT_DESCR_WR]=1 and [OOJ]=0 then REE will not write the
                                                                 next REE_RES_S from a
                                                                 given LF queue until it can guarantee that the previous REE_RES_S was written to
                                                                 LLC/DRAM. This mode guarantees
                                                                 that REE_RES_S are written in order to LLC/DRAM.

                                                                 If REE_AF_QUE()_GCFG[STRICT_DESCR_WR]=0 and [OOJ]=0 then REE will perform writes of
                                                                 REE_RES_S in order from a given LF queue
                                                                 but does not guarantee that they are written to LLC/DRAM in order.

                                                                 When [OOJ]=1 REE writes REE_RES_S to LLC/DRAM out of order with respect to how
                                                                 the instructions were enqueued.

                                                                 REE writes the REE_RES_S before any submit to SSO (see [WQ_PTR]),
                                                                 and before any REE_LF_DONE[DONE] increment ((see [DONEINT]).

                                                                 [OOJ] must be zero for REE to submit work to SSO in LF queue order and
                                                                 guarantees that all descriptors have been written to LLC/DRAM. */
#else /* Word 3 - Little Endian */
        uint64_t res_ptr_addr          : 64; /**< [255:192] Job result start pointer 128-byte aligned IOVA.
                                                                 Pointer to start of the location where the job result data (REE_RES_S) and
                                                                 job match data output (REE_MATCH_S) will be written by the REE coprocessor.

                                                                 The REE coprocessor will write exactly 1 job result structure (REE_RES_S)
                                                                 to address [RES_PTR_ADDR]

                                                                 The REE coprocessor will write up to 254 job match structures (REE_MATCH_S)
                                                                 starting at address [RES_PTR_ADDR] + 0x80.

                                                                 REE cannot write the REE_RES_S until after it guarantees that all LLC/DRAM writes have completed
                                                                 related to REE_MATCH_S.

                                                                 If REE_AF_QUE()_GCFG[STRICT_DESCR_WR]=1 and [OOJ]=0 then REE will not write the
                                                                 next REE_RES_S from a
                                                                 given LF queue until it can guarantee that the previous REE_RES_S was written to
                                                                 LLC/DRAM. This mode guarantees
                                                                 that REE_RES_S are written in order to LLC/DRAM.

                                                                 If REE_AF_QUE()_GCFG[STRICT_DESCR_WR]=0 and [OOJ]=0 then REE will perform writes of
                                                                 REE_RES_S in order from a given LF queue
                                                                 but does not guarantee that they are written to LLC/DRAM in order.

                                                                 When [OOJ]=1 REE writes REE_RES_S to LLC/DRAM out of order with respect to how
                                                                 the instructions were enqueued.

                                                                 REE writes the REE_RES_S before any submit to SSO (see [WQ_PTR]),
                                                                 and before any REE_LF_DONE[DONE] increment ((see [DONEINT]).

                                                                 [OOJ] must be zero for REE to submit work to SSO in LF queue order and
                                                                 guarantees that all descriptors have been written to LLC/DRAM. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t wq_ptr                : 64; /**< [319:256] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that the REE coprocessor
                                                                 uses to submit work to the SSO after all match data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:53\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<52\> for forward compatibility.

                                                                 REE adds the work to SSO after writing the REE_RES_S (see [RES_ADDR]), but
                                                                 unordered relative to any REE_LF_DONE[DONE] increment (see [DONEINT]).

                                                                 REE adds SSO work from REE_INST_S's in the same LF/queue that have [OOJ]=0
                                                                 in queue order. REE may add to SSO in any order in all other situations, even
                                                                 amongst instructions in the same queue.

                                                                 Internal:
                                                                 Bits \<63:53\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#else /* Word 4 - Little Endian */
        uint64_t wq_ptr                : 64; /**< [319:256] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that the REE coprocessor
                                                                 uses to submit work to the SSO after all match data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:53\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<52\> for forward compatibility.

                                                                 REE adds the work to SSO after writing the REE_RES_S (see [RES_ADDR]), but
                                                                 unordered relative to any REE_LF_DONE[DONE] increment (see [DONEINT]).

                                                                 REE adds SSO work from REE_INST_S's in the same LF/queue that have [OOJ]=0
                                                                 in queue order. REE may add to SSO in any order in all other situations, even
                                                                 amongst instructions in the same queue.

                                                                 Internal:
                                                                 Bits \<63:53\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_364_383      : 20;
        uint64_t ggrp                  : 10; /**< [363:354] If [WQ_PTR] is nonzero, the SSO guest-group to use when the REE coprocessor
                                                                 submits work to the SSO. For the SSO to not discard the add-work request, the
                                                                 SSO must map [GGRP] as valid in the PF FUNC specified by the corresponding
                                                                 queue's REE_AF_QUE()_GMCTL[SSO_AF_FUNC]. */
        uint64_t tt                    : 2;  /**< [353:352] If [WQ_PTR] is nonzero, the SSO tag type to use when the REE coprocessor submits work to the SSO. */
        uint64_t tag                   : 32; /**< [351:320] If [WQ_PTR] is nonzero, the SSO tag to use when the REE coprocessor submits work to the SSO. */
#else /* Word 5 - Little Endian */
        uint64_t tag                   : 32; /**< [351:320] If [WQ_PTR] is nonzero, the SSO tag to use when the REE coprocessor submits work to the SSO. */
        uint64_t tt                    : 2;  /**< [353:352] If [WQ_PTR] is nonzero, the SSO tag type to use when the REE coprocessor submits work to the SSO. */
        uint64_t ggrp                  : 10; /**< [363:354] If [WQ_PTR] is nonzero, the SSO guest-group to use when the REE coprocessor
                                                                 submits work to the SSO. For the SSO to not discard the add-work request, the
                                                                 SSO must map [GGRP] as valid in the PF FUNC specified by the corresponding
                                                                 queue's REE_AF_QUE()_GMCTL[SSO_AF_FUNC]. */
        uint64_t reserved_364_383      : 20;
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t reserved_447          : 1;
        uint64_t ree_job_length        : 15; /**< [446:432] Total job length (in bytes). Must be between 1 and 16384 inclusive. */
        uint64_t ree_job_ctrl          : 16; /**< [431:416] REE job control field (JOB_DESCRIPTOR_TUPLE.CTRL); by REE_JOB_CTRL_S format definition. */
        uint64_t ree_job_id            : 24; /**< [415:392] Job identifier for software use. */
        uint64_t reserved_384_391      : 8;
#else /* Word 6 - Little Endian */
        uint64_t reserved_384_391      : 8;
        uint64_t ree_job_id            : 24; /**< [415:392] Job identifier for software use. */
        uint64_t ree_job_ctrl          : 16; /**< [431:416] REE job control field (JOB_DESCRIPTOR_TUPLE.CTRL); by REE_JOB_CTRL_S format definition. */
        uint64_t ree_job_length        : 15; /**< [446:432] Total job length (in bytes). Must be between 1 and 16384 inclusive. */
        uint64_t reserved_447          : 1;
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t ree_job_subset_id_3   : 16; /**< [511:496] Job rule subset ID 3, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_2   : 16; /**< [495:480] Job rule subset ID 2, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_1   : 16; /**< [479:464] Job rule subset ID 1, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_0   : 16; /**< [463:448] Job rule subset ID 0.
                                                                 Upper 4 bits were added for virtualization.
                                                                 Each job must specify all subset ID fields.
                                                                 If job requires fewer than 4 unique subsets,
                                                                 populate unused subset ID fields with the same value as [REE_JOB_SUBSET_ID_0]. */
#else /* Word 7 - Little Endian */
        uint64_t ree_job_subset_id_0   : 16; /**< [463:448] Job rule subset ID 0.
                                                                 Upper 4 bits were added for virtualization.
                                                                 Each job must specify all subset ID fields.
                                                                 If job requires fewer than 4 unique subsets,
                                                                 populate unused subset ID fields with the same value as [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_1   : 16; /**< [479:464] Job rule subset ID 1, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_2   : 16; /**< [495:480] Job rule subset ID 2, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_3   : 16; /**< [511:496] Job rule subset ID 3, see similar [REE_JOB_SUBSET_ID_0]. */
#endif /* Word 7 - End */
    } s;
    struct bdk_ree_inst_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t reserved_9_15         : 7;
        uint64_t ooj                   : 1;  /**< [  8:  8] Out-of-order job:
                                                                   All jobs that submit work to SSO MUST set this field to zero.
                                                                 0 = This job must retire after previously issued in-order jobs to this queue.
                                                                     Ordering is maintained within queues only.
                                                                 1 = This job can be retired as soon as REE engine returns job completion. */
        uint64_t reserved_5_7          : 3;
        uint64_t dg                    : 1;  /**< [  4:  4] Data gather:
                                                                 0 = [INP_PTR_ADDR] points directly to the actual job input data and can be at any byte offset.
                                                                 1 = [INP_PTR_ADDR] points to a gather list of pointers that are read
                                                                 by the REE coprocessor to locate the actual job input data.
                                                                 The [INP_PTR_ADDR] must be 128-byte aligned, and the [INP_PTR_CTL]'s LENGTH field,
                                                                 indicating the number of pointers in the gather list, must be between 1-8. */
        uint64_t reserved_1_3          : 3;
        uint64_t doneint               : 1;  /**< [  0:  0] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, REE_LF_DONE[DONE] will be incremented,
                                                                 and may cause an interrupt.

                                                                 REE increments REE_LF_DONE[DONE] after it writes the REE_RES_S and receives STDN (see
                                                                 [RES_PTR_ADDR]), but the increment is unordered relative any SSO submit (see
                                                                 [WQ_PTR]). [OOJ] has no direct affect on when any REE_LF_DONE[DONE] increment occurs.

                                                                 When [DONEINT] is set and the instruction completes,
                                                                 REE_LF_DONE[DONE] will be incremented. */
#else /* Word 0 - Little Endian */
        uint64_t doneint               : 1;  /**< [  0:  0] Done interrupt.
                                                                 0 = No interrupts related to this instruction.
                                                                 1 = When the instruction completes, REE_LF_DONE[DONE] will be incremented,
                                                                 and may cause an interrupt.

                                                                 REE increments REE_LF_DONE[DONE] after it writes the REE_RES_S and receives STDN (see
                                                                 [RES_PTR_ADDR]), but the increment is unordered relative any SSO submit (see
                                                                 [WQ_PTR]). [OOJ] has no direct affect on when any REE_LF_DONE[DONE] increment occurs.

                                                                 When [DONEINT] is set and the instruction completes,
                                                                 REE_LF_DONE[DONE] will be incremented. */
        uint64_t reserved_1_3          : 3;
        uint64_t dg                    : 1;  /**< [  4:  4] Data gather:
                                                                 0 = [INP_PTR_ADDR] points directly to the actual job input data and can be at any byte offset.
                                                                 1 = [INP_PTR_ADDR] points to a gather list of pointers that are read
                                                                 by the REE coprocessor to locate the actual job input data.
                                                                 The [INP_PTR_ADDR] must be 128-byte aligned, and the [INP_PTR_CTL]'s LENGTH field,
                                                                 indicating the number of pointers in the gather list, must be between 1-8. */
        uint64_t reserved_5_7          : 3;
        uint64_t ooj                   : 1;  /**< [  8:  8] Out-of-order job:
                                                                   All jobs that submit work to SSO MUST set this field to zero.
                                                                 0 = This job must retire after previously issued in-order jobs to this queue.
                                                                     Ordering is maintained within queues only.
                                                                 1 = This job can be retired as soon as REE engine returns job completion. */
        uint64_t reserved_9_15         : 7;
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t inp_ptr_addr          : 64; /**< [127: 64] Input data pointer address (REE_GPTR_S format address word definition).
                                                                 Must be nonzero. */
#else /* Word 1 - Little Endian */
        uint64_t inp_ptr_addr          : 64; /**< [127: 64] Input data pointer address (REE_GPTR_S format address word definition).
                                                                 Must be nonzero. */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t inp_ptr_ctl           : 64; /**< [191:128] Input data pointer control (REE_GPTR_S format control word definition).
                                                                 For input gather mode, REE_INST_S[DG] must also be set. */
#else /* Word 2 - Little Endian */
        uint64_t inp_ptr_ctl           : 64; /**< [191:128] Input data pointer control (REE_GPTR_S format control word definition).
                                                                 For input gather mode, REE_INST_S[DG] must also be set. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t res_ptr_addr          : 64; /**< [255:192] Job result start pointer 128-byte aligned IOVA.
                                                                 Pointer to start of the location where the job result data (REE_RES_S) and
                                                                 job match data output (REE_MATCH_S) will be written by the REE coprocessor.

                                                                 The REE coprocessor will write exactly 1 job result structure (REE_RES_S)
                                                                 to address [RES_PTR_ADDR]

                                                                 The REE coprocessor will write up to 254 job match structures (REE_MATCH_S)
                                                                 starting at address [RES_PTR_ADDR] + 0x80.

                                                                 REE cannot write the REE_RES_S until after it guarantees that all LLC/DRAM writes have completed
                                                                 related to REE_MATCH_S.

                                                                 If REE_AF_QUE()_GCFG[STRICT_DESCR_WR]=1 and [OOJ]=0 then REE will not write the
                                                                 next REE_RES_S from a
                                                                 given LF queue until it can guarantee that the previous REE_RES_S was written to
                                                                 LLC/DRAM. This mode guarantees
                                                                 that REE_RES_S are written in order to LLC/DRAM.

                                                                 If REE_AF_QUE()_GCFG[STRICT_DESCR_WR]=0 and [OOJ]=0 then REE will perform writes of
                                                                 REE_RES_S in order from a given LF queue
                                                                 but does not guarantee that they are written to LLC/DRAM in order.

                                                                 When [OOJ]=1 REE writes REE_RES_S to LLC/DRAM out of order with respect to how
                                                                 the instructions were enqueued.

                                                                 REE writes the REE_RES_S before any submit to SSO (see [WQ_PTR]),
                                                                 and before any REE_LF_DONE[DONE] increment ((see [DONEINT]).

                                                                 [OOJ] must be zero for REE to submit work to SSO in LF queue order and
                                                                 guarantees that all descriptors have been written to LLC/DRAM. */
#else /* Word 3 - Little Endian */
        uint64_t res_ptr_addr          : 64; /**< [255:192] Job result start pointer 128-byte aligned IOVA.
                                                                 Pointer to start of the location where the job result data (REE_RES_S) and
                                                                 job match data output (REE_MATCH_S) will be written by the REE coprocessor.

                                                                 The REE coprocessor will write exactly 1 job result structure (REE_RES_S)
                                                                 to address [RES_PTR_ADDR]

                                                                 The REE coprocessor will write up to 254 job match structures (REE_MATCH_S)
                                                                 starting at address [RES_PTR_ADDR] + 0x80.

                                                                 REE cannot write the REE_RES_S until after it guarantees that all LLC/DRAM writes have completed
                                                                 related to REE_MATCH_S.

                                                                 If REE_AF_QUE()_GCFG[STRICT_DESCR_WR]=1 and [OOJ]=0 then REE will not write the
                                                                 next REE_RES_S from a
                                                                 given LF queue until it can guarantee that the previous REE_RES_S was written to
                                                                 LLC/DRAM. This mode guarantees
                                                                 that REE_RES_S are written in order to LLC/DRAM.

                                                                 If REE_AF_QUE()_GCFG[STRICT_DESCR_WR]=0 and [OOJ]=0 then REE will perform writes of
                                                                 REE_RES_S in order from a given LF queue
                                                                 but does not guarantee that they are written to LLC/DRAM in order.

                                                                 When [OOJ]=1 REE writes REE_RES_S to LLC/DRAM out of order with respect to how
                                                                 the instructions were enqueued.

                                                                 REE writes the REE_RES_S before any submit to SSO (see [WQ_PTR]),
                                                                 and before any REE_LF_DONE[DONE] increment ((see [DONEINT]).

                                                                 [OOJ] must be zero for REE to submit work to SSO in LF queue order and
                                                                 guarantees that all descriptors have been written to LLC/DRAM. */
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t wq_ptr                : 64; /**< [319:256] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that the REE coprocessor
                                                                 uses to submit work to the SSO after all match data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:53\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<52\> for forward compatibility.

                                                                 REE adds the work to SSO after writing the REE_RES_S (see [RES_ADDR]), but
                                                                 unordered relative to any REE_LF_DONE[DONE] increment (see [DONEINT]).

                                                                 REE adds SSO work from REE_INST_S's in the same LF/queue that have [OOJ]=0
                                                                 in queue order. REE may add to SSO in any order in all other situations, even
                                                                 amongst instructions in the same queue.

                                                                 Internal:
                                                                 Bits \<63:53\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#else /* Word 4 - Little Endian */
        uint64_t wq_ptr                : 64; /**< [319:256] If [WQ_PTR] is nonzero, it is a pointer to a work-queue entry that the REE coprocessor
                                                                 uses to submit work to the SSO after all match data, and result write operations are
                                                                 visible to other CNXXXX units and the cores.

                                                                 Bits \<2:0\> must be zero.  Bits \<63:53\> are ignored by hardware; software should
                                                                 use a sign-extended bit \<52\> for forward compatibility.

                                                                 REE adds the work to SSO after writing the REE_RES_S (see [RES_ADDR]), but
                                                                 unordered relative to any REE_LF_DONE[DONE] increment (see [DONEINT]).

                                                                 REE adds SSO work from REE_INST_S's in the same LF/queue that have [OOJ]=0
                                                                 in queue order. REE may add to SSO in any order in all other situations, even
                                                                 amongst instructions in the same queue.

                                                                 Internal:
                                                                 Bits \<63:53\>, \<2:0\> are ignored by hardware, treated as always 0x0. */
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_364_383      : 20;
        uint64_t ggrp                  : 10; /**< [363:354] If [WQ_PTR] is nonzero, the SSO guest-group to use when the REE coprocessor
                                                                 submits work to the SSO. For the SSO to not discard the add-work request, the
                                                                 SSO must map [GGRP] as valid in the PF FUNC specified by the corresponding
                                                                 queue's REE_AF_QUE()_GMCTL[SSO_AF_FUNC]. */
        uint64_t tt                    : 2;  /**< [353:352] If [WQ_PTR] is nonzero, the SSO tag type to use when the REE coprocessor submits work to the SSO. */
        uint64_t tag                   : 32; /**< [351:320] If [WQ_PTR] is nonzero, the SSO tag to use when the REE coprocessor submits work to the SSO. */
#else /* Word 5 - Little Endian */
        uint64_t tag                   : 32; /**< [351:320] If [WQ_PTR] is nonzero, the SSO tag to use when the REE coprocessor submits work to the SSO. */
        uint64_t tt                    : 2;  /**< [353:352] If [WQ_PTR] is nonzero, the SSO tag type to use when the REE coprocessor submits work to the SSO. */
        uint64_t ggrp                  : 10; /**< [363:354] If [WQ_PTR] is nonzero, the SSO guest-group to use when the REE coprocessor
                                                                 submits work to the SSO. For the SSO to not discard the add-work request, the
                                                                 SSO must map [GGRP] as valid in the PF FUNC specified by the corresponding
                                                                 queue's REE_AF_QUE()_GMCTL[SSO_AF_FUNC]. */
        uint64_t reserved_364_383      : 20;
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t reserved_447          : 1;
        uint64_t ree_job_length        : 15; /**< [446:432] Total job length (in bytes). Must be between 1 and 16384 inclusive. */
        uint64_t ree_job_ctrl          : 16; /**< [431:416] REE job control field (JOB_DESCRIPTOR_TUPLE.CTRL); by REE_JOB_CTRL_S format definition. */
        uint64_t ree_job_id            : 24; /**< [415:392] Job identifier for software use. */
        uint64_t reserved_384_391      : 8;
#else /* Word 6 - Little Endian */
        uint64_t reserved_384_391      : 8;
        uint64_t ree_job_id            : 24; /**< [415:392] Job identifier for software use. */
        uint64_t ree_job_ctrl          : 16; /**< [431:416] REE job control field (JOB_DESCRIPTOR_TUPLE.CTRL); by REE_JOB_CTRL_S format definition. */
        uint64_t ree_job_length        : 15; /**< [446:432] Total job length (in bytes). Must be between 1 and 16384 inclusive. */
        uint64_t reserved_447          : 1;
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t ree_job_subset_id_3   : 16; /**< [511:496] Job rule subset ID 3, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_2   : 16; /**< [495:480] Job rule subset ID 2, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_1   : 16; /**< [479:464] Job rule subset ID 1, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_0   : 16; /**< [463:448] Job rule subset ID 0.
                                                                 Upper 4 bits were added for virtualization.
                                                                 Each job must specify all subset ID fields.
                                                                 If job requires fewer than 4 unique subsets,
                                                                 populate unused subset ID fields with the same value as [REE_JOB_SUBSET_ID_0]. */
#else /* Word 7 - Little Endian */
        uint64_t ree_job_subset_id_0   : 16; /**< [463:448] Job rule subset ID 0.
                                                                 Upper 4 bits were added for virtualization.
                                                                 Each job must specify all subset ID fields.
                                                                 If job requires fewer than 4 unique subsets,
                                                                 populate unused subset ID fields with the same value as [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_1   : 16; /**< [479:464] Job rule subset ID 1, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_2   : 16; /**< [495:480] Job rule subset ID 2, see similar [REE_JOB_SUBSET_ID_0]. */
        uint64_t ree_job_subset_id_3   : 16; /**< [511:496] Job rule subset ID 3, see similar [REE_JOB_SUBSET_ID_0]. */
#endif /* Word 7 - End */
    } cn;
};

/**
 * Structure ree_job_ctrl_s
 *
 * REE Job Control field Structure
 * This structure is the format of JOB_DESCRIPTOR_TUPLE.CTRL.
 */
union bdk_ree_job_ctrl_s
{
    uint32_t u;
    struct bdk_ree_job_ctrl_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t mode                  : 2;  /**< [  9:  8] REE mode flag. */
        uint32_t reserved_3_7          : 5;
        uint32_t job_type              : 3;  /**< [  2:  0] REE Type flag. Set to 0x0. */
#else /* Word 0 - Little Endian */
        uint32_t job_type              : 3;  /**< [  2:  0] REE Type flag. Set to 0x0. */
        uint32_t reserved_3_7          : 5;
        uint32_t mode                  : 2;  /**< [  9:  8] REE mode flag. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    struct bdk_ree_job_ctrl_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t reserved_10_15        : 6;
        uint32_t mode                  : 2;  /**< [  9:  8] REE mode flag. */
        uint32_t reserved_3_7          : 5;
        uint32_t job_type              : 3;  /**< [  2:  0] REE Type flag. Set to 0x0. */
#else /* Word 0 - Little Endian */
        uint32_t job_type              : 3;  /**< [  2:  0] REE Type flag. Set to 0x0. */
        uint32_t reserved_3_7          : 5;
        uint32_t mode                  : 2;  /**< [  9:  8] REE mode flag. */
        uint32_t reserved_10_15        : 6;
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } cn;
};

/**
 * Structure ree_match_s
 *
 * REE Result Match Structure
 * The REE coprocessor writes up to 254 matches in REE_RES_S words {257..4}.
 * A single match is a 3-tuple including the matched rule-id, match position and match length.
 */
union bdk_ree_match_s
{
    uint64_t u;
    struct bdk_ree_match_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t match_length          : 15; /**< [ 62: 48] Length of match (in bytes). */
        uint64_t reserved_46_47        : 2;
        uint64_t start_ptr             : 14; /**< [ 45: 32] Starting byte position for matched rule. */
        uint64_t ree_rule_id           : 32; /**< [ 31:  0] REE rule identifier for matched rule. */
#else /* Word 0 - Little Endian */
        uint64_t ree_rule_id           : 32; /**< [ 31:  0] REE rule identifier for matched rule. */
        uint64_t start_ptr             : 14; /**< [ 45: 32] Starting byte position for matched rule. */
        uint64_t reserved_46_47        : 2;
        uint64_t match_length          : 15; /**< [ 62: 48] Length of match (in bytes). */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ree_match_s_s cn; */
};

/**
 * Structure ree_res_s
 *
 * REE Result Structure
 * The REE coprocessor writes this 128-byte result structure after it completes the
 * instruction. Each invocation of the REE coprocessor produces exactly one result
 * structure.
 */
union bdk_ree_res_s
{
    uint64_t u[8];
    struct bdk_ree_res_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t ree_res_mcnt          : 8;  /**< [ 63: 56] MATCH_COUNT.
                                                                 The total number of matches returned by the REE engine for this job.
                                                                 If the job was submitted with the control flag REE_JOB_CTRL_S[MODE]==HPM,
                                                                 the number of matches returned will be in the range [0:1].
                                                                 Otherwise, the number of matches returned will be in the range [0:max_match].
                                                                 See REE_AF_REEXM_MAX_MATCH\<31:0\> for the legal values of max_match. */
        uint64_t ree_res_dmcnt         : 8;  /**< [ 55: 48] DETECTED_MATCH_COUNT.
                                                                 Number of matches detected in job.
                                                                 This value saturates at 254. */
        uint64_t ree_res_status        : 16; /**< [ 47: 32] REE job result status field (RESPONSE_DESCRIPTOR_TUPLE.STATUS); by
                                                                 REE_RES_STATUS_S format definition. */
        uint64_t ree_res_job_id        : 24; /**< [ 31:  8] Matches in the input job ID supplied in REE_INST_S[REE_JOB_ID] */
        uint64_t hwjid                 : 7;  /**< [  7:  1] Matches the hardware-inflight job ID used during execution. */
        uint64_t done                  : 1;  /**< [  0:  0] Will be written to one when on job completion. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0] Will be written to one when on job completion. */
        uint64_t hwjid                 : 7;  /**< [  7:  1] Matches the hardware-inflight job ID used during execution. */
        uint64_t ree_res_job_id        : 24; /**< [ 31:  8] Matches in the input job ID supplied in REE_INST_S[REE_JOB_ID] */
        uint64_t ree_res_status        : 16; /**< [ 47: 32] REE job result status field (RESPONSE_DESCRIPTOR_TUPLE.STATUS); by
                                                                 REE_RES_STATUS_S format definition. */
        uint64_t ree_res_dmcnt         : 8;  /**< [ 55: 48] DETECTED_MATCH_COUNT.
                                                                 Number of matches detected in job.
                                                                 This value saturates at 254. */
        uint64_t ree_res_mcnt          : 8;  /**< [ 63: 56] MATCH_COUNT.
                                                                 The total number of matches returned by the REE engine for this job.
                                                                 If the job was submitted with the control flag REE_JOB_CTRL_S[MODE]==HPM,
                                                                 the number of matches returned will be in the range [0:1].
                                                                 Otherwise, the number of matches returned will be in the range [0:max_match].
                                                                 See REE_AF_REEXM_MAX_MATCH\<31:0\> for the legal values of max_match. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t pmi_min_byte_ptr      : 16; /**< [127:112] Minimum BYTE_PTR for threads still active at the end of job.
                                                                 De facto REEX will only use 15 lsbits (bit 63 is reserved). */
        uint64_t ree_meta_lcnt         : 16; /**< [111: 96] LATENCY_COUNT.
                                                                 How long it took REEX to scan job in multiples of 256 core_clk cycles. */
        uint64_t ree_meta_icnt         : 16; /**< [ 95: 80] INSTRUCTION_CONT.
                                                                 The number of REE instructions executed in this job. */
        uint64_t ree_meta_ptcnt        : 16; /**< [ 79: 64] PRIMARY_THREAD_COUNT.
                                                                 The number of REE primary threads triggered in this job. */
#else /* Word 1 - Little Endian */
        uint64_t ree_meta_ptcnt        : 16; /**< [ 79: 64] PRIMARY_THREAD_COUNT.
                                                                 The number of REE primary threads triggered in this job. */
        uint64_t ree_meta_icnt         : 16; /**< [ 95: 80] INSTRUCTION_CONT.
                                                                 The number of REE instructions executed in this job. */
        uint64_t ree_meta_lcnt         : 16; /**< [111: 96] LATENCY_COUNT.
                                                                 How long it took REEX to scan job in multiples of 256 core_clk cycles. */
        uint64_t pmi_min_byte_ptr      : 16; /**< [127:112] Minimum BYTE_PTR for threads still active at the end of job.
                                                                 De facto REEX will only use 15 lsbits (bit 63 is reserved). */
#endif /* Word 1 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 2 - Big Endian */
        uint64_t doneint               : 1;  /**< [191:191] Done interrupt has been set. This bit is copied from the corresponding REE
                                                                 instruction REE_INST_S[DONEINT] on job completion (after the interrupt has been
                                                                 signaled).

                                                                 Internal:
                                                                 FIXME need to check with REE team about the utility of this bit in the
                                                                 output. Seems like this overlaps with other done indicators. */
        uint64_t reserved_129_190      : 62;
        uint64_t ree_err               : 1;  /**< [128:128] Indicates load of payload data received an NCB error response. */
#else /* Word 2 - Little Endian */
        uint64_t ree_err               : 1;  /**< [128:128] Indicates load of payload data received an NCB error response. */
        uint64_t reserved_129_190      : 62;
        uint64_t doneint               : 1;  /**< [191:191] Done interrupt has been set. This bit is copied from the corresponding REE
                                                                 instruction REE_INST_S[DONEINT] on job completion (after the interrupt has been
                                                                 signaled).

                                                                 Internal:
                                                                 FIXME need to check with REE team about the utility of this bit in the
                                                                 output. Seems like this overlaps with other done indicators. */
#endif /* Word 2 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 3 - Big Endian */
        uint64_t reserved_192_255      : 64;
#else /* Word 3 - Little Endian */
        uint64_t reserved_192_255      : 64;
#endif /* Word 3 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 4 - Big Endian */
        uint64_t reserved_256_319      : 64;
#else /* Word 4 - Little Endian */
        uint64_t reserved_256_319      : 64;
#endif /* Word 4 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 5 - Big Endian */
        uint64_t reserved_320_383      : 64;
#else /* Word 5 - Little Endian */
        uint64_t reserved_320_383      : 64;
#endif /* Word 5 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 6 - Big Endian */
        uint64_t reserved_384_447      : 64;
#else /* Word 6 - Little Endian */
        uint64_t reserved_384_447      : 64;
#endif /* Word 6 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 7 - Big Endian */
        uint64_t reserved_448_511      : 64;
#else /* Word 7 - Little Endian */
        uint64_t reserved_448_511      : 64;
#endif /* Word 7 - End */
    } s;
    /* struct bdk_ree_res_s_s cn; */
};

/**
 * Structure ree_res_status_s
 *
 * REE Response Status field Structure
 * This structure is the format of RESPONSE_DESCRIPTOR_TUPLE.STATUS.
 */
union bdk_ree_res_status_s
{
    uint32_t u;
    struct bdk_ree_res_status_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_15_31        : 17;
        uint32_t pmi_eoj               : 1;  /**< [ 14: 14] partial match indicator, end of job. */
        uint32_t pmi_soj               : 1;  /**< [ 13: 13] Partial match indicator, start of job. */
        uint32_t reserved_10_12        : 3;
        uint32_t mode                  : 2;  /**< [  9:  8] REE mode flag */
        uint32_t mp_cnt_det            : 1;  /**< [  7:  7] MAX_PREFIX_COUNT_DETECTED */
        uint32_t mm_cnt_det            : 1;  /**< [  6:  6] MAX_MATCH_COUNT_DETECTED */
        uint32_t ml_cnt_det            : 1;  /**< [  5:  5] MAX_LATENCY_COUNT_DETECTED */
        uint32_t mst_cnt_det           : 1;  /**< [  4:  4] MAX_SECONDARY_THREAD_COUNT_DETECTED */
        uint32_t mpt_cnt_det           : 1;  /**< [  3:  3] MAX_PRIMARY_THREAD_COUNT_DETECTED */
        uint32_t job_type              : 3;  /**< [  2:  0] REE type flag. Set to 0x1. */
#else /* Word 0 - Little Endian */
        uint32_t job_type              : 3;  /**< [  2:  0] REE type flag. Set to 0x1. */
        uint32_t mpt_cnt_det           : 1;  /**< [  3:  3] MAX_PRIMARY_THREAD_COUNT_DETECTED */
        uint32_t mst_cnt_det           : 1;  /**< [  4:  4] MAX_SECONDARY_THREAD_COUNT_DETECTED */
        uint32_t ml_cnt_det            : 1;  /**< [  5:  5] MAX_LATENCY_COUNT_DETECTED */
        uint32_t mm_cnt_det            : 1;  /**< [  6:  6] MAX_MATCH_COUNT_DETECTED */
        uint32_t mp_cnt_det            : 1;  /**< [  7:  7] MAX_PREFIX_COUNT_DETECTED */
        uint32_t mode                  : 2;  /**< [  9:  8] REE mode flag */
        uint32_t reserved_10_12        : 3;
        uint32_t pmi_soj               : 1;  /**< [ 13: 13] Partial match indicator, start of job. */
        uint32_t pmi_eoj               : 1;  /**< [ 14: 14] partial match indicator, end of job. */
        uint32_t reserved_15_31        : 17;
#endif /* Word 0 - End */
    } s;
    struct bdk_ree_res_status_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t reserved_15           : 1;
        uint32_t pmi_eoj               : 1;  /**< [ 14: 14] partial match indicator, end of job. */
        uint32_t pmi_soj               : 1;  /**< [ 13: 13] Partial match indicator, start of job. */
        uint32_t reserved_12           : 1;
        uint32_t reserved_10_11        : 2;
        uint32_t mode                  : 2;  /**< [  9:  8] REE mode flag */
        uint32_t mp_cnt_det            : 1;  /**< [  7:  7] MAX_PREFIX_COUNT_DETECTED */
        uint32_t mm_cnt_det            : 1;  /**< [  6:  6] MAX_MATCH_COUNT_DETECTED */
        uint32_t ml_cnt_det            : 1;  /**< [  5:  5] MAX_LATENCY_COUNT_DETECTED */
        uint32_t mst_cnt_det           : 1;  /**< [  4:  4] MAX_SECONDARY_THREAD_COUNT_DETECTED */
        uint32_t mpt_cnt_det           : 1;  /**< [  3:  3] MAX_PRIMARY_THREAD_COUNT_DETECTED */
        uint32_t job_type              : 3;  /**< [  2:  0] REE type flag. Set to 0x1. */
#else /* Word 0 - Little Endian */
        uint32_t job_type              : 3;  /**< [  2:  0] REE type flag. Set to 0x1. */
        uint32_t mpt_cnt_det           : 1;  /**< [  3:  3] MAX_PRIMARY_THREAD_COUNT_DETECTED */
        uint32_t mst_cnt_det           : 1;  /**< [  4:  4] MAX_SECONDARY_THREAD_COUNT_DETECTED */
        uint32_t ml_cnt_det            : 1;  /**< [  5:  5] MAX_LATENCY_COUNT_DETECTED */
        uint32_t mm_cnt_det            : 1;  /**< [  6:  6] MAX_MATCH_COUNT_DETECTED */
        uint32_t mp_cnt_det            : 1;  /**< [  7:  7] MAX_PREFIX_COUNT_DETECTED */
        uint32_t mode                  : 2;  /**< [  9:  8] REE mode flag */
        uint32_t reserved_10_11        : 2;
        uint32_t reserved_12           : 1;
        uint32_t pmi_soj               : 1;  /**< [ 13: 13] Partial match indicator, start of job. */
        uint32_t pmi_eoj               : 1;  /**< [ 14: 14] partial match indicator, end of job. */
        uint32_t reserved_15           : 1;
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } cn;
};

/**
 * Structure ree_rof_s
 *
 * REE ROF Structure
 * This structure defines the format for one entry of REEX ROF file.
 */
union bdk_ree_rof_s
{
    uint64_t u[2];
    struct bdk_ree_rof_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t typ                   : 8;  /**< [ 39: 32] Type of ROF entry. */
        uint64_t reserved_24_31        : 8;
        uint64_t addr                  : 24; /**< [ 23:  0] This field contains REEX CSR address or REEX RTU CSR address. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 24; /**< [ 23:  0] This field contains REEX CSR address or REEX RTU CSR address. */
        uint64_t reserved_24_31        : 8;
        uint64_t typ                   : 8;  /**< [ 39: 32] Type of ROF entry. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t data                  : 64; /**< [127: 64] ROF data. */
#else /* Word 1 - Little Endian */
        uint64_t data                  : 64; /**< [127: 64] ROF data. */
#endif /* Word 1 - End */
    } s;
    /* struct bdk_ree_rof_s_s cn; */
};

/**
 * Register (RVU_PF_BAR0) ree#_af_active_pc
 *
 * REE AF Conditional Clock Counter Register
 */
union bdk_reex_af_active_pc
{
    uint64_t u;
    struct bdk_reex_af_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_active_pc_s cn; */
};
typedef union bdk_reex_af_active_pc bdk_reex_af_active_pc_t;

static inline uint64_t BDK_REEX_AF_ACTIVE_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_ACTIVE_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000450ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_ACTIVE_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_ACTIVE_PC(a) bdk_reex_af_active_pc_t
#define bustype_BDK_REEX_AF_ACTIVE_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_ACTIVE_PC(a) "REEX_AF_ACTIVE_PC"
#define device_bar_BDK_REEX_AF_ACTIVE_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_ACTIVE_PC(a) (a)
#define arguments_BDK_REEX_AF_ACTIVE_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_ctl_cfg
 *
 * REE Controller Configuration Register
 * This register controls the behavior of the REE DMA engines for AQ. It is recommended
 * to keep default
 * values for normal operation. Changing the values of the fields may be useful for diagnostics.
 */
union bdk_reex_af_aq_ctl_cfg
{
    uint64_t u;
    struct bdk_reex_af_aq_ctl_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t il2_ldwb              : 1;  /**< [ 15: 15](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues regular NCB loads towards the cache, which will cause the
                                                                 line to be written back before being replaced.

                                                                 1 = The hardware issues LDWB read-and-invalidate NCB commands towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware. */
        uint64_t pl2ld_cmd             : 3;  /**< [ 14: 12](R/W) NCB load command to use for fetching payload and gather pointers.
                                                                 If REE_AF_AQ_INST_S[NC] is set then the LDT instruction will be used, otherwise
                                                                 this field will be used to select load instruction. Enumerated by REE_L2LD_CMD_E. */
        uint64_t il2_pc                : 1;  /**< [ 11: 11](R/W) This bit controls the NCB load command type for REE_AF_AQ_INST_S loads.
                                                                 1 = If loading the first half of a cache line for an instruction use NCB command
                                                                 from [IL2LD_CMD]. When loading the second half of cache line or the full
                                                                 cache line for an instruction use LDWB if [IL2_LDWB] is set otherwise use LDT.

                                                                 0 = Hardware uses NCB command from [IL2LD_CMD] for all loads of REE_AF_AQ_INST_S. */
        uint64_t il2ld_cmd             : 3;  /**< [ 10:  8](R/W) NCB load command to use for fetching instruction (REE_AF_AQ_INST_S).
                                                                 See [IL2_PC] for more information.
                                                                 Enumerated by REE_L2LD_CMD_E. */
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t il2ld_cmd             : 3;  /**< [ 10:  8](R/W) NCB load command to use for fetching instruction (REE_AF_AQ_INST_S).
                                                                 See [IL2_PC] for more information.
                                                                 Enumerated by REE_L2LD_CMD_E. */
        uint64_t il2_pc                : 1;  /**< [ 11: 11](R/W) This bit controls the NCB load command type for REE_AF_AQ_INST_S loads.
                                                                 1 = If loading the first half of a cache line for an instruction use NCB command
                                                                 from [IL2LD_CMD]. When loading the second half of cache line or the full
                                                                 cache line for an instruction use LDWB if [IL2_LDWB] is set otherwise use LDT.

                                                                 0 = Hardware uses NCB command from [IL2LD_CMD] for all loads of REE_AF_AQ_INST_S. */
        uint64_t pl2ld_cmd             : 3;  /**< [ 14: 12](R/W) NCB load command to use for fetching payload and gather pointers.
                                                                 If REE_AF_AQ_INST_S[NC] is set then the LDT instruction will be used, otherwise
                                                                 this field will be used to select load instruction. Enumerated by REE_L2LD_CMD_E. */
        uint64_t il2_ldwb              : 1;  /**< [ 15: 15](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues regular NCB loads towards the cache, which will cause the
                                                                 line to be written back before being replaced.

                                                                 1 = The hardware issues LDWB read-and-invalidate NCB commands towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_ctl_cfg_s cn; */
};
typedef union bdk_reex_af_aq_ctl_cfg bdk_reex_af_aq_ctl_cfg_t;

static inline uint64_t BDK_REEX_AF_AQ_CTL_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_CTL_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000118ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_CTL_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_CTL_CFG(a) bdk_reex_af_aq_ctl_cfg_t
#define bustype_BDK_REEX_AF_AQ_CTL_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_CTL_CFG(a) "REEX_AF_AQ_CTL_CFG"
#define device_bar_BDK_REEX_AF_AQ_CTL_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_CTL_CFG(a) (a)
#define arguments_BDK_REEX_AF_AQ_CTL_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_done
 *
 * REE Administrative Queue Done Count Registers
 * This register contains the AQ instruction done count.
 */
union bdk_reex_af_aq_done
{
    uint64_t u;
    struct bdk_reex_af_aq_done_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t done                  : 20; /**< [ 19:  0](R/W/H) Done count. When REE_AF_AQ_INST_S[DONEINT] is set and that instruction completes,
                                                                 REE_AF_AQ_DONE[DONE] is incremented. Writes to this field are for diagnostic use only;
                                                                 instead software writes REE_AF_AQ_DONE_ACK[DONE_ACK] with the number of decrements for
                                                                 this field.

                                                                 Interrupts are sent as follows:

                                                                 * When REE_AF_AQ_DONE[DONE] = 0, then no results are pending.

                                                                 * When REE_AF_AQ_DONE[DONE] != 0, then the interrupt is sent.

                                                                 * When REE_AF_AQ_DONE_ACK is written, DONE is decremented.

                                                                 * When REE_AF_AQ_DONE_INT_ENA_W1S[DONE_ENA] = 0, interrupts are not sent.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 20; /**< [ 19:  0](R/W/H) Done count. When REE_AF_AQ_INST_S[DONEINT] is set and that instruction completes,
                                                                 REE_AF_AQ_DONE[DONE] is incremented. Writes to this field are for diagnostic use only;
                                                                 instead software writes REE_AF_AQ_DONE_ACK[DONE_ACK] with the number of decrements for
                                                                 this field.

                                                                 Interrupts are sent as follows:

                                                                 * When REE_AF_AQ_DONE[DONE] = 0, then no results are pending.

                                                                 * When REE_AF_AQ_DONE[DONE] != 0, then the interrupt is sent.

                                                                 * When REE_AF_AQ_DONE_ACK is written, DONE is decremented.

                                                                 * When REE_AF_AQ_DONE_INT_ENA_W1S[DONE_ENA] = 0, interrupts are not sent.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_done_s cn; */
};
typedef union bdk_reex_af_aq_done bdk_reex_af_aq_done_t;

static inline uint64_t BDK_REEX_AF_AQ_DONE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_DONE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000128ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_DONE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_DONE(a) bdk_reex_af_aq_done_t
#define bustype_BDK_REEX_AF_AQ_DONE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_DONE(a) "REEX_AF_AQ_DONE"
#define device_bar_BDK_REEX_AF_AQ_DONE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_DONE(a) (a)
#define arguments_BDK_REEX_AF_AQ_DONE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_done_ack
 *
 * REE Administrative Queue Done Count Ack Registers
 * This register is written by software to acknowledge interrupts.
 */
union bdk_reex_af_aq_done_ack
{
    uint64_t u;
    struct bdk_reex_af_aq_done_ack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to REE_AF_AQ_DONE[DONE]. When read, returns REE_AF_AQ_DONE[DONE].

                                                                 Written by software to acknowledge interrupts. If REE_AF_AQ_DONE[DONE] is still
                                                                 nonzero, the interrupt will be re-sent if the conditions described in
                                                                 REE_AF_AQ_DONE[DONE] are satisfied. */
#else /* Word 0 - Little Endian */
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to REE_AF_AQ_DONE[DONE]. When read, returns REE_AF_AQ_DONE[DONE].

                                                                 Written by software to acknowledge interrupts. If REE_AF_AQ_DONE[DONE] is still
                                                                 nonzero, the interrupt will be re-sent if the conditions described in
                                                                 REE_AF_AQ_DONE[DONE] are satisfied. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_done_ack_s cn; */
};
typedef union bdk_reex_af_aq_done_ack bdk_reex_af_aq_done_ack_t;

static inline uint64_t BDK_REEX_AF_AQ_DONE_ACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_DONE_ACK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000130ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_DONE_ACK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_DONE_ACK(a) bdk_reex_af_aq_done_ack_t
#define bustype_BDK_REEX_AF_AQ_DONE_ACK(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_DONE_ACK(a) "REEX_AF_AQ_DONE_ACK"
#define device_bar_BDK_REEX_AF_AQ_DONE_ACK(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_DONE_ACK(a) (a)
#define arguments_BDK_REEX_AF_AQ_DONE_ACK(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_done_int
 *
 * INTERNAL: REE Administrative Queue Done Interrupt Clear Registers
 *
 * Internal:
 * This CSR description is only here to keep the scripts happy.
 */
union bdk_reex_af_aq_done_int
{
    uint64_t u;
    struct bdk_reex_af_aq_done_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See ree_AQ_DONE[DONE].  Note this bit is read-only - acknowledge
                                                                 interrupts using REE_AF_AQ_DONE_ACK.

                                                                 To test interrupts, write REE_AF_AQ_DONE_ACK to make REE_AF_AQ_DONE[DONE] nonzero.

                                                                 Internal:
                                                                 This is called the conceptual interrupt bit in the REE_AF_AQ_DONE[DONE] documentation.
                                                                 This bit does not need to be implemented, and this CSR could be removed (except
                                                                 that the scripts will blow up). */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See ree_AQ_DONE[DONE].  Note this bit is read-only - acknowledge
                                                                 interrupts using REE_AF_AQ_DONE_ACK.

                                                                 To test interrupts, write REE_AF_AQ_DONE_ACK to make REE_AF_AQ_DONE[DONE] nonzero.

                                                                 Internal:
                                                                 This is called the conceptual interrupt bit in the REE_AF_AQ_DONE[DONE] documentation.
                                                                 This bit does not need to be implemented, and this CSR could be removed (except
                                                                 that the scripts will blow up). */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_done_int_s cn; */
};
typedef union bdk_reex_af_aq_done_int bdk_reex_af_aq_done_int_t;

static inline uint64_t BDK_REEX_AF_AQ_DONE_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_DONE_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000150ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_DONE_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_DONE_INT(a) bdk_reex_af_aq_done_int_t
#define bustype_BDK_REEX_AF_AQ_DONE_INT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_DONE_INT(a) "REEX_AF_AQ_DONE_INT"
#define device_bar_BDK_REEX_AF_AQ_DONE_INT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_DONE_INT(a) (a)
#define arguments_BDK_REEX_AF_AQ_DONE_INT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_done_int_ena_w1c
 *
 * REE Administrative Queue Done Interrupt Enable Clear Registers
 * Write 1 to these registers to disable the DONEINT interrupt for the AQ.
 */
union bdk_reex_af_aq_done_int_ena_w1c
{
    uint64_t u;
    struct bdk_reex_af_aq_done_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done_ena              : 1;  /**< [  0:  0](R/W1C/H) Writing 1 will disable DONEINT for this queue. Writing 0 has no effect.
                                                                 A read will return the DONEINT enable bit. */
#else /* Word 0 - Little Endian */
        uint64_t done_ena              : 1;  /**< [  0:  0](R/W1C/H) Writing 1 will disable DONEINT for this queue. Writing 0 has no effect.
                                                                 A read will return the DONEINT enable bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_done_int_ena_w1c_s cn; */
};
typedef union bdk_reex_af_aq_done_int_ena_w1c bdk_reex_af_aq_done_int_ena_w1c_t;

static inline uint64_t BDK_REEX_AF_AQ_DONE_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_DONE_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000170ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_DONE_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_DONE_INT_ENA_W1C(a) bdk_reex_af_aq_done_int_ena_w1c_t
#define bustype_BDK_REEX_AF_AQ_DONE_INT_ENA_W1C(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_DONE_INT_ENA_W1C(a) "REEX_AF_AQ_DONE_INT_ENA_W1C"
#define device_bar_BDK_REEX_AF_AQ_DONE_INT_ENA_W1C(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_DONE_INT_ENA_W1C(a) (a)
#define arguments_BDK_REEX_AF_AQ_DONE_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_done_int_ena_w1s
 *
 * REE AQ Queue Done Interrupt Enable Set Registers
 * Write 1 to these registers to enable the DONEINT interrupt for the AQ.
 */
union bdk_reex_af_aq_done_int_ena_w1s
{
    uint64_t u;
    struct bdk_reex_af_aq_done_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done_ena              : 1;  /**< [  0:  0](R/W1S/H) Writing a 1 will enable DONEINT for AQ. Writing a 0 has no effect.
                                                                 A read will return the DONEINT enable bit. */
#else /* Word 0 - Little Endian */
        uint64_t done_ena              : 1;  /**< [  0:  0](R/W1S/H) Writing a 1 will enable DONEINT for AQ. Writing a 0 has no effect.
                                                                 A read will return the DONEINT enable bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_done_int_ena_w1s_s cn; */
};
typedef union bdk_reex_af_aq_done_int_ena_w1s bdk_reex_af_aq_done_int_ena_w1s_t;

static inline uint64_t BDK_REEX_AF_AQ_DONE_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_DONE_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000168ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_DONE_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_DONE_INT_ENA_W1S(a) bdk_reex_af_aq_done_int_ena_w1s_t
#define bustype_BDK_REEX_AF_AQ_DONE_INT_ENA_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_DONE_INT_ENA_W1S(a) "REEX_AF_AQ_DONE_INT_ENA_W1S"
#define device_bar_BDK_REEX_AF_AQ_DONE_INT_ENA_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_DONE_INT_ENA_W1S(a) (a)
#define arguments_BDK_REEX_AF_AQ_DONE_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_done_int_w1s
 *
 * INTERNAL: REE Administrative Queue Done Interrupt Set Registers
 *
 * Internal:
 * This CSR description is only here to keep the scripts happy.
 */
union bdk_reex_af_aq_done_int_w1s
{
    uint64_t u;
    struct bdk_reex_af_aq_done_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See ree_AQ_DONE[DONE].  Note this bit is read-only - acknowledge
                                                                 interrupts using REE_AF_AQ_DONE_ACK.

                                                                 To test interrupts, write REE_AF_AQ_DONE_ACK to make REE_AF_AQ_DONE[DONE] nonzero.

                                                                 Internal:
                                                                 This is called the conceptual interrupt bit in the REE_AF_AQ_DONE[DONE] documentation.
                                                                 This bit does not need to be implemented, and this CSR could be removed (except
                                                                 that the scripts will blow up). */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See ree_AQ_DONE[DONE].  Note this bit is read-only - acknowledge
                                                                 interrupts using REE_AF_AQ_DONE_ACK.

                                                                 To test interrupts, write REE_AF_AQ_DONE_ACK to make REE_AF_AQ_DONE[DONE] nonzero.

                                                                 Internal:
                                                                 This is called the conceptual interrupt bit in the REE_AF_AQ_DONE[DONE] documentation.
                                                                 This bit does not need to be implemented, and this CSR could be removed (except
                                                                 that the scripts will blow up). */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_done_int_w1s_s cn; */
};
typedef union bdk_reex_af_aq_done_int_w1s bdk_reex_af_aq_done_int_w1s_t;

static inline uint64_t BDK_REEX_AF_AQ_DONE_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_DONE_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000160ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_DONE_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_DONE_INT_W1S(a) bdk_reex_af_aq_done_int_w1s_t
#define bustype_BDK_REEX_AF_AQ_DONE_INT_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_DONE_INT_W1S(a) "REEX_AF_AQ_DONE_INT_W1S"
#define device_bar_BDK_REEX_AF_AQ_DONE_INT_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_DONE_INT_W1S(a) (a)
#define arguments_BDK_REEX_AF_AQ_DONE_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_doorbell
 *
 * REE Administrative Queue Doorbell Registers
 * Doorbells for the REE administrative instruction queues.
 */
union bdk_reex_af_aq_doorbell
{
    uint64_t u;
    struct bdk_reex_af_aq_doorbell_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) When written, the number of instructions to add to the REE administrative
                                                                 instruction doorbell count.
                                                                 When read, the current total doorbell count.

                                                                 Writes to [DBELL_CNT] are ignored when queue is disabled. */
#else /* Word 0 - Little Endian */
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) When written, the number of instructions to add to the REE administrative
                                                                 instruction doorbell count.
                                                                 When read, the current total doorbell count.

                                                                 Writes to [DBELL_CNT] are ignored when queue is disabled. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_doorbell_s cn; */
};
typedef union bdk_reex_af_aq_doorbell bdk_reex_af_aq_doorbell_t;

static inline uint64_t BDK_REEX_AF_AQ_DOORBELL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_DOORBELL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000200ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_DOORBELL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_DOORBELL(a) bdk_reex_af_aq_doorbell_t
#define bustype_BDK_REEX_AF_AQ_DOORBELL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_DOORBELL(a) "REEX_AF_AQ_DOORBELL"
#define device_bar_BDK_REEX_AF_AQ_DOORBELL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_DOORBELL(a) (a)
#define arguments_BDK_REEX_AF_AQ_DOORBELL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_ena
 *
 * REE Administrative Queue Enable Register
 * If a AQ is disabled, REE CTL stops fetching instructions from the AQ.
 */
union bdk_reex_af_aq_ena
{
    uint64_t u;
    struct bdk_reex_af_aq_ena_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) 0 = logical administrative instruction queue is disabled.
                                                                 1 = Enables the logical administrative instruction queue.

                                                                 Program REE_AF_AQ_SBUF_ADDR, and REE_AF_AQ_SBUF_CTL before you set ENA.

                                                                 Software must only transition [ENA] 0-\>1 when the queue is quiescent. See
                                                                 REE_AF_AQ_OUTSTAND_JOB[OJOB_CNT].

                                                                 Transition of [ENA] 0-\>1 will set REE_AF_AQ_DOORBELL[DBELL_CNT] to
                                                                 zero and REE_AF_AQ_SBUF_ADDR[PTR] and REE_AF_AQ_SBUF_ADDR[off] are set to starting
                                                                 IOVA.

                                                                 Hardware will clear ENA if any of the REE_LF_MISC_INT bits are set. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) 0 = logical administrative instruction queue is disabled.
                                                                 1 = Enables the logical administrative instruction queue.

                                                                 Program REE_AF_AQ_SBUF_ADDR, and REE_AF_AQ_SBUF_CTL before you set ENA.

                                                                 Software must only transition [ENA] 0-\>1 when the queue is quiescent. See
                                                                 REE_AF_AQ_OUTSTAND_JOB[OJOB_CNT].

                                                                 Transition of [ENA] 0-\>1 will set REE_AF_AQ_DOORBELL[DBELL_CNT] to
                                                                 zero and REE_AF_AQ_SBUF_ADDR[PTR] and REE_AF_AQ_SBUF_ADDR[off] are set to starting
                                                                 IOVA.

                                                                 Hardware will clear ENA if any of the REE_LF_MISC_INT bits are set. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_ena_s cn; */
};
typedef union bdk_reex_af_aq_ena bdk_reex_af_aq_ena_t;

static inline uint64_t BDK_REEX_AF_AQ_ENA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_ENA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000180ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_ENA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_ENA(a) bdk_reex_af_aq_ena_t
#define bustype_BDK_REEX_AF_AQ_ENA(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_ENA(a) "REEX_AF_AQ_ENA"
#define device_bar_BDK_REEX_AF_AQ_ENA(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_ENA(a) (a)
#define arguments_BDK_REEX_AF_AQ_ENA(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_int
 *
 * REE Admin Queue Error Interrupt Register
 * These registers contain the AQ error interrupts.
 */
union bdk_reex_af_aq_int
{
    uint64_t u;
    struct bdk_reex_af_aq_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t plle                  : 1;  /**< [  3:  3](R/W1C/H) Payload length error. Payload length was not multiple of 16 bytes between 16 and 16384 inclusive. */
        uint64_t prde                  : 1;  /**< [  2:  2](R/W1C/H) Payload NCB read response error. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1C/H) Instruction NCB read response error. */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1C/H) Doorbell overflow. */
#else /* Word 0 - Little Endian */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1C/H) Doorbell overflow. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1C/H) Instruction NCB read response error. */
        uint64_t prde                  : 1;  /**< [  2:  2](R/W1C/H) Payload NCB read response error. */
        uint64_t plle                  : 1;  /**< [  3:  3](R/W1C/H) Payload length error. Payload length was not multiple of 16 bytes between 16 and 16384 inclusive. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_int_s cn; */
};
typedef union bdk_reex_af_aq_int bdk_reex_af_aq_int_t;

static inline uint64_t BDK_REEX_AF_AQ_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046020ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_INT(a) bdk_reex_af_aq_int_t
#define bustype_BDK_REEX_AF_AQ_INT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_INT(a) "REEX_AF_AQ_INT"
#define device_bar_BDK_REEX_AF_AQ_INT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_INT(a) (a)
#define arguments_BDK_REEX_AF_AQ_INT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_int_ena_w1c
 *
 * REE Admin Queue Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_reex_af_aq_int_ena_w1c
{
    uint64_t u;
    struct bdk_reex_af_aq_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t plle                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for REE_AF_AQ_INT[PLLE]. */
        uint64_t prde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for REE_AF_AQ_INT[PRDE]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for REE_AF_AQ_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for REE_AF_AQ_INT[DOVF]. */
#else /* Word 0 - Little Endian */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for REE_AF_AQ_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for REE_AF_AQ_INT[IRDE]. */
        uint64_t prde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for REE_AF_AQ_INT[PRDE]. */
        uint64_t plle                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for REE_AF_AQ_INT[PLLE]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_int_ena_w1c_s cn; */
};
typedef union bdk_reex_af_aq_int_ena_w1c bdk_reex_af_aq_int_ena_w1c_t;

static inline uint64_t BDK_REEX_AF_AQ_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046038ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_INT_ENA_W1C(a) bdk_reex_af_aq_int_ena_w1c_t
#define bustype_BDK_REEX_AF_AQ_INT_ENA_W1C(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_INT_ENA_W1C(a) "REEX_AF_AQ_INT_ENA_W1C"
#define device_bar_BDK_REEX_AF_AQ_INT_ENA_W1C(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_INT_ENA_W1C(a) (a)
#define arguments_BDK_REEX_AF_AQ_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_int_ena_w1s
 *
 * REE Admin Queue Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_reex_af_aq_int_ena_w1s
{
    uint64_t u;
    struct bdk_reex_af_aq_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t plle                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for REE_AF_AQ_INT[PLLE]. */
        uint64_t prde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for REE_AF_AQ_INT[PRDE]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for REE_AF_AQ_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for REE_AF_AQ_INT[DOVF]. */
#else /* Word 0 - Little Endian */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for REE_AF_AQ_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for REE_AF_AQ_INT[IRDE]. */
        uint64_t prde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for REE_AF_AQ_INT[PRDE]. */
        uint64_t plle                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for REE_AF_AQ_INT[PLLE]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_int_ena_w1s_s cn; */
};
typedef union bdk_reex_af_aq_int_ena_w1s bdk_reex_af_aq_int_ena_w1s_t;

static inline uint64_t BDK_REEX_AF_AQ_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046030ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_INT_ENA_W1S(a) bdk_reex_af_aq_int_ena_w1s_t
#define bustype_BDK_REEX_AF_AQ_INT_ENA_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_INT_ENA_W1S(a) "REEX_AF_AQ_INT_ENA_W1S"
#define device_bar_BDK_REEX_AF_AQ_INT_ENA_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_INT_ENA_W1S(a) (a)
#define arguments_BDK_REEX_AF_AQ_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_int_w1s
 *
 * REE Admin Queue Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_reex_af_aq_int_w1s
{
    uint64_t u;
    struct bdk_reex_af_aq_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t plle                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets REE_AF_AQ_INT[PLLE]. */
        uint64_t prde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets REE_AF_AQ_INT[PRDE]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets REE_AF_AQ_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets REE_AF_AQ_INT[DOVF]. */
#else /* Word 0 - Little Endian */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets REE_AF_AQ_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets REE_AF_AQ_INT[IRDE]. */
        uint64_t prde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets REE_AF_AQ_INT[PRDE]. */
        uint64_t plle                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets REE_AF_AQ_INT[PLLE]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_int_w1s_s cn; */
};
typedef union bdk_reex_af_aq_int_w1s bdk_reex_af_aq_int_w1s_t;

static inline uint64_t BDK_REEX_AF_AQ_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046028ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_INT_W1S(a) bdk_reex_af_aq_int_w1s_t
#define bustype_BDK_REEX_AF_AQ_INT_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_INT_W1S(a) "REEX_AF_AQ_INT_W1S"
#define device_bar_BDK_REEX_AF_AQ_INT_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_INT_W1S(a) (a)
#define arguments_BDK_REEX_AF_AQ_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_outstand_job
 *
 * REE Administrative Queue Outstanding Job Register
 */
union bdk_reex_af_aq_outstand_job
{
    uint64_t u;
    struct bdk_reex_af_aq_outstand_job_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ojob_cnt              : 9;  /**< [  8:  0](R/W/H) Number of outstanding jobs. A job is outstanding from the time it is removed
                                                                 from the doorbell count to the time it is retired. */
#else /* Word 0 - Little Endian */
        uint64_t ojob_cnt              : 9;  /**< [  8:  0](R/W/H) Number of outstanding jobs. A job is outstanding from the time it is removed
                                                                 from the doorbell count to the time it is retired. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_outstand_job_s cn; */
};
typedef union bdk_reex_af_aq_outstand_job bdk_reex_af_aq_outstand_job_t;

static inline uint64_t BDK_REEX_AF_AQ_OUTSTAND_JOB(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_OUTSTAND_JOB(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000220ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_OUTSTAND_JOB", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_OUTSTAND_JOB(a) bdk_reex_af_aq_outstand_job_t
#define bustype_BDK_REEX_AF_AQ_OUTSTAND_JOB(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_OUTSTAND_JOB(a) "REEX_AF_AQ_OUTSTAND_JOB"
#define device_bar_BDK_REEX_AF_AQ_OUTSTAND_JOB(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_OUTSTAND_JOB(a) (a)
#define arguments_BDK_REEX_AF_AQ_OUTSTAND_JOB(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_pp_wait
 *
 * REE Administrative Queue Programing Plane Wait Registers
 * Specifies how long to wait after the REEX programming plane has written the last
 * instruction before we increment REE_AF_AQ_DONE[DONE].
 */
union bdk_reex_af_aq_pp_wait
{
    uint64_t u;
    struct bdk_reex_af_aq_pp_wait_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t enable                : 1;  /**< [ 16: 16](R/W) This is enable bit for the DLY_TIME feature. By default, it is disabled (0).
                                                                 Set to 1 (enable) in order to count DLY_TIME microseconds in addition to
                                                                 the REEX indication, to determine that the programming is over (and interrupt can be asserted).
                                                                 For the REEX indication we use the pp_rtru_done, after the PP FIFO is empty (after DONE instruction
                                                                 had been enqueued to REEX PP FIFO). */
        uint64_t dly_time              : 16; /**< [ 15:  0](R/W) When REE_AF_AQ_INST_S[DONEINT] is set in an instruction, REE will
                                                                 wait [DLY_TIME] microseconds after the programing plane FIFO is empty before
                                                                 it increments REE_AF_AQ_DONE[DONE].
                                                                 The implementation of timer is accurate. */
#else /* Word 0 - Little Endian */
        uint64_t dly_time              : 16; /**< [ 15:  0](R/W) When REE_AF_AQ_INST_S[DONEINT] is set in an instruction, REE will
                                                                 wait [DLY_TIME] microseconds after the programing plane FIFO is empty before
                                                                 it increments REE_AF_AQ_DONE[DONE].
                                                                 The implementation of timer is accurate. */
        uint64_t enable                : 1;  /**< [ 16: 16](R/W) This is enable bit for the DLY_TIME feature. By default, it is disabled (0).
                                                                 Set to 1 (enable) in order to count DLY_TIME microseconds in addition to
                                                                 the REEX indication, to determine that the programming is over (and interrupt can be asserted).
                                                                 For the REEX indication we use the pp_rtru_done, after the PP FIFO is empty (after DONE instruction
                                                                 had been enqueued to REEX PP FIFO). */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_pp_wait_s cn; */
};
typedef union bdk_reex_af_aq_pp_wait bdk_reex_af_aq_pp_wait_t;

static inline uint64_t BDK_REEX_AF_AQ_PP_WAIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_PP_WAIT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000120ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_PP_WAIT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_PP_WAIT(a) bdk_reex_af_aq_pp_wait_t
#define bustype_BDK_REEX_AF_AQ_PP_WAIT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_PP_WAIT(a) "REEX_AF_AQ_PP_WAIT"
#define device_bar_BDK_REEX_AF_AQ_PP_WAIT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_PP_WAIT(a) (a)
#define arguments_BDK_REEX_AF_AQ_PP_WAIT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_sbuf_addr
 *
 * REE Administrative Queue Starting Buffer Address Registers
 * This register sets the starting buffer address for the administrative instruction
 * queue. When quiescent (i.e.
 * outstanding AQ doorbell count is 0 and
 * REE_AF_AQ_OUTSTAND_JOB[OJOB_CNT] is 0), it is safe to rewrite this
 * register. This register must be programmed after software programs the
 * corresponding REE_AF_AQ_SBUF_CTL and before REE_AF_AQ_ENA[ENA] is set to 1.
 */
union bdk_reex_af_aq_sbuf_addr
{
    uint64_t u;
    struct bdk_reex_af_aq_sbuf_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) Instruction buffer pointer bits \<52:7\> (128-byte aligned). Behavior is unpredictable if
                                                                 the address is 0x0.  When written, it is the initial buffer starting IOVA; when read, it
                                                                 is the next read pointer IOVA to be requested from NCB.
                                                                 [PTR] is overwritten with the next pointer each time that the command buffer
                                                                 segment is exhausted. New commands will then be read from the newly specified command
                                                                 buffer pointer. */
        uint64_t off                   : 7;  /**< [  6:  0](RO/H) When written, the value is ignored. When read, the returned value is the offset
                                                                 of the next read pointer. */
#else /* Word 0 - Little Endian */
        uint64_t off                   : 7;  /**< [  6:  0](RO/H) When written, the value is ignored. When read, the returned value is the offset
                                                                 of the next read pointer. */
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) Instruction buffer pointer bits \<52:7\> (128-byte aligned). Behavior is unpredictable if
                                                                 the address is 0x0.  When written, it is the initial buffer starting IOVA; when read, it
                                                                 is the next read pointer IOVA to be requested from NCB.
                                                                 [PTR] is overwritten with the next pointer each time that the command buffer
                                                                 segment is exhausted. New commands will then be read from the newly specified command
                                                                 buffer pointer. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_sbuf_addr_s cn; */
};
typedef union bdk_reex_af_aq_sbuf_addr bdk_reex_af_aq_sbuf_addr_t;

static inline uint64_t BDK_REEX_AF_AQ_SBUF_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_SBUF_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000110ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_SBUF_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_SBUF_ADDR(a) bdk_reex_af_aq_sbuf_addr_t
#define bustype_BDK_REEX_AF_AQ_SBUF_ADDR(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_SBUF_ADDR(a) "REEX_AF_AQ_SBUF_ADDR"
#define device_bar_BDK_REEX_AF_AQ_SBUF_ADDR(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_SBUF_ADDR(a) (a)
#define arguments_BDK_REEX_AF_AQ_SBUF_ADDR(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_aq_sbuf_ctl
 *
 * REE Administrative Queue Buffer Parameter Registers
 * These registers set the buffer parameters for the administrative instruction queue.
 * When quiescent (i.e.
 * outstanding AQ doorbell count is 0 and
 * REE_AF_AQ_OUTSTAND_JOB[OJOB_CNT] is 0.), it is safe to rewrite this
 * register. These registers must be programmed before software programs the
 * corresponding REE_AF_AQ_SBUF_ADDR and before REE_AF_AQ_ENA[ENA] is set to 1.
 */
union bdk_reex_af_aq_sbuf_ctl
{
    uint64_t u;
    struct bdk_reex_af_aq_sbuf_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t size                  : 17; /**< [ 48: 32](R/W) Administrative Instruction buffer size, in units of 128 bytes (8*REE_AF_AQ_INST_S). */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t size                  : 17; /**< [ 48: 32](R/W) Administrative Instruction buffer size, in units of 128 bytes (8*REE_AF_AQ_INST_S). */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_aq_sbuf_ctl_s cn; */
};
typedef union bdk_reex_af_aq_sbuf_ctl bdk_reex_af_aq_sbuf_ctl_t;

static inline uint64_t BDK_REEX_AF_AQ_SBUF_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_AQ_SBUF_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000100ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_AQ_SBUF_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_AQ_SBUF_CTL(a) bdk_reex_af_aq_sbuf_ctl_t
#define bustype_BDK_REEX_AF_AQ_SBUF_CTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_AQ_SBUF_CTL(a) "REEX_AF_AQ_SBUF_CTL"
#define device_bar_BDK_REEX_AF_AQ_SBUF_CTL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_AQ_SBUF_CTL(a) (a)
#define arguments_BDK_REEX_AF_AQ_SBUF_CTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_bar2_alias#
 *
 * INTERNAL: REE Admin Function  BAR2 Alias Registers
 *
 * These registers alias to the REE BAR2 registers for the PF and function
 * selected by REE_AF_BAR2_SEL[PF_FUNC].
 */
union bdk_reex_af_bar2_aliasx
{
    uint64_t u;
    struct bdk_reex_af_bar2_aliasx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Aliased register data. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Aliased register data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_bar2_aliasx_s cn; */
};
typedef union bdk_reex_af_bar2_aliasx bdk_reex_af_bar2_aliasx_t;

static inline uint64_t BDK_REEX_AF_BAR2_ALIASX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_BAR2_ALIASX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=131071)))
        return 0x840149100000ll + 0x10000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1ffff);
    __bdk_csr_fatal("REEX_AF_BAR2_ALIASX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_BAR2_ALIASX(a,b) bdk_reex_af_bar2_aliasx_t
#define bustype_BDK_REEX_AF_BAR2_ALIASX(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_BAR2_ALIASX(a,b) "REEX_AF_BAR2_ALIASX"
#define device_bar_BDK_REEX_AF_BAR2_ALIASX(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_BAR2_ALIASX(a,b) (a)
#define arguments_BDK_REEX_AF_BAR2_ALIASX(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_bar2_sel
 *
 * INTERNAL: REE Admin Function BAR2 Select Register
 *
 * This register configures BAR2 accesses from the REE_AF_BAR2_ALIAS() registers in BAR0.
 */
union bdk_reex_af_bar2_sel
{
    uint64_t u;
    struct bdk_reex_af_bar2_sel_s
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
    /* struct bdk_reex_af_bar2_sel_s cn; */
};
typedef union bdk_reex_af_bar2_sel bdk_reex_af_bar2_sel_t;

static inline uint64_t BDK_REEX_AF_BAR2_SEL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_BAR2_SEL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840149000000ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_BAR2_SEL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_BAR2_SEL(a) bdk_reex_af_bar2_sel_t
#define bustype_BDK_REEX_AF_BAR2_SEL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_BAR2_SEL(a) "REEX_AF_BAR2_SEL"
#define device_bar_BDK_REEX_AF_BAR2_SEL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_BAR2_SEL(a) (a)
#define arguments_BDK_REEX_AF_BAR2_SEL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_blk_rst
 *
 * REE AF Block Reset Registers
 * Writing a 1 to REE_AF_BLK_RST[RST] resets the REE. After receiving a store to this CSR, the REE
 * must not be sent any other operations for TBD coprocessor-clock cycles.
 */
union bdk_reex_af_blk_rst
{
    uint64_t u;
    struct bdk_reex_af_blk_rst_s
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
    /* struct bdk_reex_af_blk_rst_s cn; */
};
typedef union bdk_reex_af_blk_rst bdk_reex_af_blk_rst_t;

static inline uint64_t BDK_REEX_AF_BLK_RST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_BLK_RST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140045000ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_BLK_RST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_BLK_RST(a) bdk_reex_af_blk_rst_t
#define bustype_BDK_REEX_AF_BLK_RST(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_BLK_RST(a) "REEX_AF_BLK_RST"
#define device_bar_BDK_REEX_AF_BLK_RST(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_BLK_RST(a) (a)
#define arguments_BDK_REEX_AF_BLK_RST(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_bp_test
 *
 * INTERNAL: |
 *   REE Backpressure Test Register
 */
union bdk_reex_af_bp_test
{
    uint64_t u;
    struct bdk_reex_af_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 16; /**< [ 63: 48](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Randomly make REE memory interface (rmif) not ready.
                                                                 \<60\> = Randomly make REEX response match FIFO (rrmf) empty.
                                                                 \<59\> = Randomly make REEX response descriptor FIFO (rrdf) empty.
                                                                 \<58\> = Randomly make NCBI match request FIFO (match_req_0) output not valid.
                                                                 \<57\> = Randomly make NCBI rdc request FIFO (rdc_req_fifo) output not valid.
                                                                 \<56\> = Randomly make NCBI rmic request FIFO (rmic_req_fifo) output not valid.
                                                                 \<55\> = Randomly make NCBI ddf request FIFO (ddf_req_fifo) output not valid.
                                                                 \<54\> = Randomly make NCBI ifi instruction request FIFO (ifi_instr_req) output not valid.
                                                                 \<53\> = Randomly make SJD packet FIFO (ree_pkt_fifo) output not valid.
                                                                 \<52\> = Randomly make RJD instruction pending FIFO (instr_pnd_fifo) output not valid.
                                                                 \<51\> = Randomly make DPR gather pointer FIFO (gthr_ptr_fifo) output not valid.
                                                                 \<50\> = Randomly make DPR data ready FIFO (data_rdy_fifo) output not valid.
                                                                 \<49\> = Randomly make DDF gather request FIFO (gthr_req_fifo) output not valid.
                                                                 \<48\> = Randomly make DDF DMA request FIFO (dma_req_fifo) output not valid. */
        uint64_t bp_cfg                : 32; /**< [ 47: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                    \<47:46\> = Reserved.
                                                                    \<45:44\> = Reserved.
                                                                    \<43:42\> = Config 13.
                                                                    \<41:40\> = Config 12.
                                                                    \<39:38\> = Config 11.
                                                                    \<37:36\> = Config 10.
                                                                    \<35:34\> = Config 9.
                                                                    \<33:32\> = Config 8.
                                                                    \<31:30\> = Config 7.
                                                                    \<29:28\> = Config 6.
                                                                    \<27:26\> = Config 5.
                                                                    \<25:24\> = Config 4.
                                                                    \<23:22\> = Config 3.
                                                                    \<21:20\> = Config 2.
                                                                    \<19:18\> = Config 1.
                                                                    \<17:16\> = Config 0.

                                                                  When using 0x0, the constant backpressure means the testbench must toggle the
                                                                  corresponding [ENABLE] bit to keep traffic flowing. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 32; /**< [ 47: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                    \<47:46\> = Reserved.
                                                                    \<45:44\> = Reserved.
                                                                    \<43:42\> = Config 13.
                                                                    \<41:40\> = Config 12.
                                                                    \<39:38\> = Config 11.
                                                                    \<37:36\> = Config 10.
                                                                    \<35:34\> = Config 9.
                                                                    \<33:32\> = Config 8.
                                                                    \<31:30\> = Config 7.
                                                                    \<29:28\> = Config 6.
                                                                    \<27:26\> = Config 5.
                                                                    \<25:24\> = Config 4.
                                                                    \<23:22\> = Config 3.
                                                                    \<21:20\> = Config 2.
                                                                    \<19:18\> = Config 1.
                                                                    \<17:16\> = Config 0.

                                                                  When using 0x0, the constant backpressure means the testbench must toggle the
                                                                  corresponding [ENABLE] bit to keep traffic flowing. */
        uint64_t enable                : 16; /**< [ 63: 48](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Randomly make REE memory interface (rmif) not ready.
                                                                 \<60\> = Randomly make REEX response match FIFO (rrmf) empty.
                                                                 \<59\> = Randomly make REEX response descriptor FIFO (rrdf) empty.
                                                                 \<58\> = Randomly make NCBI match request FIFO (match_req_0) output not valid.
                                                                 \<57\> = Randomly make NCBI rdc request FIFO (rdc_req_fifo) output not valid.
                                                                 \<56\> = Randomly make NCBI rmic request FIFO (rmic_req_fifo) output not valid.
                                                                 \<55\> = Randomly make NCBI ddf request FIFO (ddf_req_fifo) output not valid.
                                                                 \<54\> = Randomly make NCBI ifi instruction request FIFO (ifi_instr_req) output not valid.
                                                                 \<53\> = Randomly make SJD packet FIFO (ree_pkt_fifo) output not valid.
                                                                 \<52\> = Randomly make RJD instruction pending FIFO (instr_pnd_fifo) output not valid.
                                                                 \<51\> = Randomly make DPR gather pointer FIFO (gthr_ptr_fifo) output not valid.
                                                                 \<50\> = Randomly make DPR data ready FIFO (data_rdy_fifo) output not valid.
                                                                 \<49\> = Randomly make DDF gather request FIFO (gthr_req_fifo) output not valid.
                                                                 \<48\> = Randomly make DDF DMA request FIFO (dma_req_fifo) output not valid. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_bp_test_s cn; */
};
typedef union bdk_reex_af_bp_test bdk_reex_af_bp_test_t;

static inline uint64_t BDK_REEX_AF_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_BP_TEST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140003400ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_BP_TEST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_BP_TEST(a) bdk_reex_af_bp_test_t
#define bustype_BDK_REEX_AF_BP_TEST(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_BP_TEST(a) "REEX_AF_BP_TEST"
#define device_bar_BDK_REEX_AF_BP_TEST(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_BP_TEST(a) (a)
#define arguments_BDK_REEX_AF_BP_TEST(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_cmd_ctl
 *
 * REE Clock/Reset Control Register
 * This register controls clock and reset.
 */
union bdk_reex_af_cmd_ctl
{
    uint64_t u;
    struct bdk_reex_af_cmd_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t reex_force_cclk       : 1;  /**< [  2:  2](R/W) When this bit is one, force the REEX conditional clock is always on.
                                                                 For diagnostic use only. */
        uint64_t ree_force_csclk       : 1;  /**< [  1:  1](R/W) When this bit is one, force the REE conditional clock always on.
                                                                 For diagnostic use only. */
        uint64_t ncb_force_clken       : 1;  /**< [  0:  0](R/W) When this bit is one, force the clock enable on NCBI bus to always on. For
                                                                 diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t ncb_force_clken       : 1;  /**< [  0:  0](R/W) When this bit is one, force the clock enable on NCBI bus to always on. For
                                                                 diagnostic use only. */
        uint64_t ree_force_csclk       : 1;  /**< [  1:  1](R/W) When this bit is one, force the REE conditional clock always on.
                                                                 For diagnostic use only. */
        uint64_t reex_force_cclk       : 1;  /**< [  2:  2](R/W) When this bit is one, force the REEX conditional clock is always on.
                                                                 For diagnostic use only. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_cmd_ctl_s cn; */
};
typedef union bdk_reex_af_cmd_ctl bdk_reex_af_cmd_ctl_t;

static inline uint64_t BDK_REEX_AF_CMD_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_CMD_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000000ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_CMD_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_CMD_CTL(a) bdk_reex_af_cmd_ctl_t
#define bustype_BDK_REEX_AF_CMD_CTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_CMD_CTL(a) "REEX_AF_CMD_CTL"
#define device_bar_BDK_REEX_AF_CMD_CTL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_CMD_CTL(a) (a)
#define arguments_BDK_REEX_AF_CMD_CTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_constants
 *
 * REE Constants Register
 * This register contains implementation-related parameters of the REE core in this
 * chip.
 */
union bdk_reex_af_constants
{
    uint64_t u;
    struct bdk_reex_af_constants_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t lf                    : 8;  /**< [  7:  0](RO) Number of LFs. */
#else /* Word 0 - Little Endian */
        uint64_t lf                    : 8;  /**< [  7:  0](RO) Number of LFs. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_constants_s cn; */
};
typedef union bdk_reex_af_constants bdk_reex_af_constants_t;

static inline uint64_t BDK_REEX_AF_CONSTANTS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_CONSTANTS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400000a0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_CONSTANTS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_CONSTANTS(a) bdk_reex_af_constants_t
#define bustype_BDK_REEX_AF_CONSTANTS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_CONSTANTS(a) "REEX_AF_CONSTANTS"
#define device_bar_BDK_REEX_AF_CONSTANTS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_CONSTANTS(a) (a)
#define arguments_BDK_REEX_AF_CONSTANTS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_core_reset
 *
 * REE Core Reset Register
 * This register resets the REE cores.
 */
union bdk_reex_af_core_reset
{
    uint64_t u;
    struct bdk_reex_af_core_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t reset                 : 1;  /**< [  0:  0](R/W) When set, the REEX core will be put into reset. When clear, the core is out of
                                                                 reset. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t reset                 : 1;  /**< [  0:  0](R/W) When set, the REEX core will be put into reset. When clear, the core is out of
                                                                 reset. For diagnostic use only. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_core_reset_s cn; */
};
typedef union bdk_reex_af_core_reset bdk_reex_af_core_reset_t;

static inline uint64_t BDK_REEX_AF_CORE_RESET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_CORE_RESET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000310ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_CORE_RESET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_CORE_RESET(a) bdk_reex_af_core_reset_t
#define bustype_BDK_REEX_AF_CORE_RESET(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_CORE_RESET(a) "REEX_AF_CORE_RESET"
#define device_bar_BDK_REEX_AF_CORE_RESET(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_CORE_RESET(a) (a)
#define arguments_BDK_REEX_AF_CORE_RESET(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_crdt_halt_ncb_req_pc
 *
 * REE Data FIFO Credit Halt NCB Load Requests Counter Register
 */
union bdk_reex_af_crdt_halt_ncb_req_pc
{
    uint64_t u;
    struct bdk_reex_af_crdt_halt_ncb_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Performance counter. Number of cycles REE can't issue NCB load-requests of jobs' data,
                                                                 due lack of data-FIFO credits, which located at SJD. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Performance counter. Number of cycles REE can't issue NCB load-requests of jobs' data,
                                                                 due lack of data-FIFO credits, which located at SJD. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_crdt_halt_ncb_req_pc_s cn; */
};
typedef union bdk_reex_af_crdt_halt_ncb_req_pc bdk_reex_af_crdt_halt_ncb_req_pc_t;

static inline uint64_t BDK_REEX_AF_CRDT_HALT_NCB_REQ_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_CRDT_HALT_NCB_REQ_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000480ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_CRDT_HALT_NCB_REQ_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_CRDT_HALT_NCB_REQ_PC(a) bdk_reex_af_crdt_halt_ncb_req_pc_t
#define bustype_BDK_REEX_AF_CRDT_HALT_NCB_REQ_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_CRDT_HALT_NCB_REQ_PC(a) "REEX_AF_CRDT_HALT_NCB_REQ_PC"
#define device_bar_BDK_REEX_AF_CRDT_HALT_NCB_REQ_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_CRDT_HALT_NCB_REQ_PC(a) (a)
#define arguments_BDK_REEX_AF_CRDT_HALT_NCB_REQ_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_ctl_cfg
 *
 * REE Controller Configuration Register
 * This register controls the behavior of the REE DMA engines. It is recommended to keep default
 * values for normal operation. Changing the values of the fields may be useful for diagnostics.
 */
union bdk_reex_af_ctl_cfg
{
    uint64_t u;
    struct bdk_reex_af_ctl_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_26_63        : 38;
        uint64_t lo_pri_thr            : 6;  /**< [ 25: 20](R/W) This register sets the threshold for how many high priority jobs will be
                                                                 serviced before a low priority job is serviced (jobs here mean arbiter selections, which
                                                                 could translate to 1 or 2 jobs de-facto).
                                                                 REE_AF_QUE()_SBUF_CTL[PRI] controls if a given queue is high priority or low priority. */
        uint64_t reserved_19           : 1;
        uint64_t rl2ld_cmd             : 3;  /**< [ 18: 16](R/W) This field indicates the NCB load command to use for REEX memory requests. This
                                                                 field is enumerated by REE_L2LD_CMD_E, but REE_L2LD_CMD_E::LDWB and
                                                                 REE_L2LD_CMD_E::LDE must not be used. */
        uint64_t reserved_1_15         : 15;
        uint64_t rd_psn_ign            : 1;  /**< [  0:  0](R/W) Read poison ignore.

                                                                 0 = Poisons received on a NCB instruction response are fatal and set interrupt
                                                                 REE_AF_RAS[LD_CMD_PSN], poisons received on a NCB DMA data response are
                                                                 propagated into result structure and set interrupt REE_AF_RAS[LD_DAT_PSN].

                                                                 1 = Poisons received on a NCB instruction response are ignored and set interrupt
                                                                 REE_AF_RAS[LD_CMD_PSN], poisons received on a NCB DMA data response are
                                                                 ignored and set interrupt REE_AF_RAS[LD_DAT_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t rd_psn_ign            : 1;  /**< [  0:  0](R/W) Read poison ignore.

                                                                 0 = Poisons received on a NCB instruction response are fatal and set interrupt
                                                                 REE_AF_RAS[LD_CMD_PSN], poisons received on a NCB DMA data response are
                                                                 propagated into result structure and set interrupt REE_AF_RAS[LD_DAT_PSN].

                                                                 1 = Poisons received on a NCB instruction response are ignored and set interrupt
                                                                 REE_AF_RAS[LD_CMD_PSN], poisons received on a NCB DMA data response are
                                                                 ignored and set interrupt REE_AF_RAS[LD_DAT_PSN]. */
        uint64_t reserved_1_15         : 15;
        uint64_t rl2ld_cmd             : 3;  /**< [ 18: 16](R/W) This field indicates the NCB load command to use for REEX memory requests. This
                                                                 field is enumerated by REE_L2LD_CMD_E, but REE_L2LD_CMD_E::LDWB and
                                                                 REE_L2LD_CMD_E::LDE must not be used. */
        uint64_t reserved_19           : 1;
        uint64_t lo_pri_thr            : 6;  /**< [ 25: 20](R/W) This register sets the threshold for how many high priority jobs will be
                                                                 serviced before a low priority job is serviced (jobs here mean arbiter selections, which
                                                                 could translate to 1 or 2 jobs de-facto).
                                                                 REE_AF_QUE()_SBUF_CTL[PRI] controls if a given queue is high priority or low priority. */
        uint64_t reserved_26_63        : 38;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_ctl_cfg_s cn; */
};
typedef union bdk_reex_af_ctl_cfg bdk_reex_af_ctl_cfg_t;

static inline uint64_t BDK_REEX_AF_CTL_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_CTL_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000560ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_CTL_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_CTL_CFG(a) bdk_reex_af_ctl_cfg_t
#define bustype_BDK_REEX_AF_CTL_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_CTL_CFG(a) "REEX_AF_CTL_CFG"
#define device_bar_BDK_REEX_AF_CTL_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_CTL_CFG(a) (a)
#define arguments_BDK_REEX_AF_CTL_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_dbg_que#_sta
 *
 * REE Queue Status Registers
 * These registers reflect status of the REE instruction queues and are for debug use only.
 */
union bdk_reex_af_dbg_quex_sta
{
    uint64_t u;
    struct bdk_reex_af_dbg_quex_sta_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) Queue state. 0 = queue is idle; 1 = queue is busy. */
        uint64_t outstanding           : 1;  /**< [ 62: 62](RO/H) When set, the queue is waiting for outstanding NCB transaction(s).  Otherwise, there are
                                                                 no outstanding NCB transactions and the queue can be reset. */
        uint64_t reserved_56_61        : 6;
        uint64_t rqwc                  : 24; /**< [ 55: 32](RO/H) Number of remaining instruction qwords to be fetched. */
        uint64_t nii                   : 32; /**< [ 31:  0](RO/H) Number of instructions issued from this queue. Reset to 0x0 when REE_LF_SBUF_ADDR
                                                                 is written. */
#else /* Word 0 - Little Endian */
        uint64_t nii                   : 32; /**< [ 31:  0](RO/H) Number of instructions issued from this queue. Reset to 0x0 when REE_LF_SBUF_ADDR
                                                                 is written. */
        uint64_t rqwc                  : 24; /**< [ 55: 32](RO/H) Number of remaining instruction qwords to be fetched. */
        uint64_t reserved_56_61        : 6;
        uint64_t outstanding           : 1;  /**< [ 62: 62](RO/H) When set, the queue is waiting for outstanding NCB transaction(s).  Otherwise, there are
                                                                 no outstanding NCB transactions and the queue can be reset. */
        uint64_t busy                  : 1;  /**< [ 63: 63](RO/H) Queue state. 0 = queue is idle; 1 = queue is busy. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_dbg_quex_sta_s cn; */
};
typedef union bdk_reex_af_dbg_quex_sta bdk_reex_af_dbg_quex_sta_t;

static inline uint64_t BDK_REEX_AF_DBG_QUEX_STA(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_DBG_QUEX_STA(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=35)))
        return 0x840140001800ll + 0x10000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("REEX_AF_DBG_QUEX_STA", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_DBG_QUEX_STA(a,b) bdk_reex_af_dbg_quex_sta_t
#define bustype_BDK_REEX_AF_DBG_QUEX_STA(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_DBG_QUEX_STA(a,b) "REEX_AF_DBG_QUEX_STA"
#define device_bar_BDK_REEX_AF_DBG_QUEX_STA(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_DBG_QUEX_STA(a,b) (a)
#define arguments_BDK_REEX_AF_DBG_QUEX_STA(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_eco
 *
 * INTERNAL: REE ECO Register
 */
union bdk_reex_af_eco
{
    uint64_t u;
    struct bdk_reex_af_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t eco_rw                : 64; /**< [ 63:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 64; /**< [ 63:  0](R/W) Reserved for ECO usage. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_eco_s cn; */
};
typedef union bdk_reex_af_eco bdk_reex_af_eco_t;

static inline uint64_t BDK_REEX_AF_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400005f0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_ECO(a) bdk_reex_af_eco_t
#define bustype_BDK_REEX_AF_ECO(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_ECO(a) "REEX_AF_ECO"
#define device_bar_BDK_REEX_AF_ECO(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_ECO(a) (a)
#define arguments_BDK_REEX_AF_ECO(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_em_base
 *
 * REE External Memory Virtual Base Register
 * This register configures virtual addressing to DRAM reads from REEX.
 */
union bdk_reex_af_em_base
{
    uint64_t u;
    struct bdk_reex_af_em_base_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t base_adr              : 53; /**< [ 52:  0](R/W) IOVA base address for the memory image of regular expressions graphs.
                                                                 All REEX memory requests will add this base register to the address provided by REEX. */
#else /* Word 0 - Little Endian */
        uint64_t base_adr              : 53; /**< [ 52:  0](R/W) IOVA base address for the memory image of regular expressions graphs.
                                                                 All REEX memory requests will add this base register to the address provided by REEX. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_em_base_s cn; */
};
typedef union bdk_reex_af_em_base bdk_reex_af_em_base_t;

static inline uint64_t BDK_REEX_AF_EM_BASE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_EM_BASE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000300ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_EM_BASE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_EM_BASE(a) bdk_reex_af_em_base_t
#define bustype_BDK_REEX_AF_EM_BASE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_EM_BASE(a) "REEX_AF_EM_BASE"
#define device_bar_BDK_REEX_AF_EM_BASE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_EM_BASE(a) (a)
#define arguments_BDK_REEX_AF_EM_BASE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_em_pf_func
 *
 * RVU Admin Function External Memory PF FUNC Register
 */
union bdk_reex_af_em_pf_func
{
    uint64_t u;
    struct bdk_reex_af_em_pf_func_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t pf_func               : 16; /**< [ 15:  0](R/W) PF FUNC used to for memory requests made by REEX for fetching graph data.

                                                                 RVU_PF_FUNC_S describes the format of [PF_FUNC]. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](R/W) PF FUNC used to for memory requests made by REEX for fetching graph data.

                                                                 RVU_PF_FUNC_S describes the format of [PF_FUNC]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_em_pf_func_s cn; */
};
typedef union bdk_reex_af_em_pf_func bdk_reex_af_em_pf_func_t;

static inline uint64_t BDK_REEX_AF_EM_PF_FUNC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_EM_PF_FUNC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000308ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_EM_PF_FUNC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_EM_PF_FUNC(a) bdk_reex_af_em_pf_func_t
#define bustype_BDK_REEX_AF_EM_PF_FUNC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_EM_PF_FUNC(a) "REEX_AF_EM_PF_FUNC"
#define device_bar_BDK_REEX_AF_EM_PF_FUNC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_EM_PF_FUNC(a) (a)
#define arguments_BDK_REEX_AF_EM_PF_FUNC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_em_phys_en
 *
 * REE External Memory Physical Base Register
 * This register configures physical addressing to DRAM reads from REEX.
 */
union bdk_reex_af_em_phys_en
{
    uint64_t u;
    struct bdk_reex_af_em_phys_en_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t em_phys_addr_en       : 1;  /**< [ 63: 63](SR/W) When 0, use virtual base address from REE_AF_EM_BASE (default).
                                                                 When 1, use physical base address EM_PHYS_ADDR, and set transactions to
                                                                 non secure physical (ns=1, paddr=1).
                                                                 Use physical base address mode to handle performance issues due to heavy load on SMMU. */
        uint64_t reserved_53_62        : 10;
        uint64_t em_phys_addr          : 53; /**< [ 52:  0](SR/W) Physical base address for DRAM loads, used only when [EM_PHYS_ADDR_EN]=1. */
#else /* Word 0 - Little Endian */
        uint64_t em_phys_addr          : 53; /**< [ 52:  0](SR/W) Physical base address for DRAM loads, used only when [EM_PHYS_ADDR_EN]=1. */
        uint64_t reserved_53_62        : 10;
        uint64_t em_phys_addr_en       : 1;  /**< [ 63: 63](SR/W) When 0, use virtual base address from REE_AF_EM_BASE (default).
                                                                 When 1, use physical base address EM_PHYS_ADDR, and set transactions to
                                                                 non secure physical (ns=1, paddr=1).
                                                                 Use physical base address mode to handle performance issues due to heavy load on SMMU. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_em_phys_en_s cn; */
};
typedef union bdk_reex_af_em_phys_en bdk_reex_af_em_phys_en_t;

static inline uint64_t BDK_REEX_AF_EM_PHYS_EN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_EM_PHYS_EN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400002f8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_EM_PHYS_EN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_EM_PHYS_EN(a) bdk_reex_af_em_phys_en_t
#define bustype_BDK_REEX_AF_EM_PHYS_EN(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_EM_PHYS_EN(a) "REEX_AF_EM_PHYS_EN"
#define device_bar_BDK_REEX_AF_EM_PHYS_EN(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_EM_PHYS_EN(a) (a)
#define arguments_BDK_REEX_AF_EM_PHYS_EN(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_graceful_dis_ctl
 *
 * REE AF Queue Graceful Disable Control Register
 * This register allows to gracefully disable a queue.
 * When a queue is gracefully disabled:
 * * REE CTL stops fetching new instructions from the queue.
 * * Instructions already fetched are executed normally.
 * * REE_LF_DOORBELL[DBELL_CNT] continues to be updated.
 * When a queue is later re-enabled:
 * * REE CTL resumes fetching instructions from the queue.
 * * REE_LF_DOORBELL[DBELL_CNT] is not reset.
 */
union bdk_reex_af_graceful_dis_ctl
{
    uint64_t u;
    struct bdk_reex_af_graceful_dis_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t dis_ctl               : 36; /**< [ 35:  0](R/W) Bit i=0..35 is for disabling queue[i].
                                                                 0 = Logical instruction queue is enabled (if the corresponding REE_LF_ENA[ENA] is also enabled).
                                                                 1 = Gracefully disables the logical instruction queue. */
#else /* Word 0 - Little Endian */
        uint64_t dis_ctl               : 36; /**< [ 35:  0](R/W) Bit i=0..35 is for disabling queue[i].
                                                                 0 = Logical instruction queue is enabled (if the corresponding REE_LF_ENA[ENA] is also enabled).
                                                                 1 = Gracefully disables the logical instruction queue. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_graceful_dis_ctl_s cn; */
};
typedef union bdk_reex_af_graceful_dis_ctl bdk_reex_af_graceful_dis_ctl_t;

static inline uint64_t BDK_REEX_AF_GRACEFUL_DIS_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_GRACEFUL_DIS_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046100ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_GRACEFUL_DIS_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_GRACEFUL_DIS_CTL(a) bdk_reex_af_graceful_dis_ctl_t
#define bustype_BDK_REEX_AF_GRACEFUL_DIS_CTL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_GRACEFUL_DIS_CTL(a) "REEX_AF_GRACEFUL_DIS_CTL"
#define device_bar_BDK_REEX_AF_GRACEFUL_DIS_CTL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_GRACEFUL_DIS_CTL(a) (a)
#define arguments_BDK_REEX_AF_GRACEFUL_DIS_CTL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_graceful_dis_status
 *
 * REE AF Queue Graceful Disable Status Register
 * This register contains status information for gracefully-disabled queues.
 */
union bdk_reex_af_graceful_dis_status
{
    uint64_t u;
    struct bdk_reex_af_graceful_dis_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t dis_status            : 36; /**< [ 35:  0](RO/H) Bit i=0..35 reflects status of queue[i].
                                                                 0 = Queue is not gracefully-disabled.
                                                                 1 = Queue was gracefully-disabled (i.e. REE_AF_LF_GRACEFUL_DIS_CTL[DISABLE] is
                                                                 set and REE_LF_OUTSTAND_JOB[OJOB_CNT] is 0) */
#else /* Word 0 - Little Endian */
        uint64_t dis_status            : 36; /**< [ 35:  0](RO/H) Bit i=0..35 reflects status of queue[i].
                                                                 0 = Queue is not gracefully-disabled.
                                                                 1 = Queue was gracefully-disabled (i.e. REE_AF_LF_GRACEFUL_DIS_CTL[DISABLE] is
                                                                 set and REE_LF_OUTSTAND_JOB[OJOB_CNT] is 0) */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_graceful_dis_status_s cn; */
};
typedef union bdk_reex_af_graceful_dis_status bdk_reex_af_graceful_dis_status_t;

static inline uint64_t BDK_REEX_AF_GRACEFUL_DIS_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_GRACEFUL_DIS_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046110ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_GRACEFUL_DIS_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_GRACEFUL_DIS_STATUS(a) bdk_reex_af_graceful_dis_status_t
#define bustype_BDK_REEX_AF_GRACEFUL_DIS_STATUS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_GRACEFUL_DIS_STATUS(a) "REEX_AF_GRACEFUL_DIS_STATUS"
#define device_bar_BDK_REEX_AF_GRACEFUL_DIS_STATUS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_GRACEFUL_DIS_STATUS(a) (a)
#define arguments_BDK_REEX_AF_GRACEFUL_DIS_STATUS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_inst_latency_pc
 *
 * REE AF Instruction Latency Counter Register
 * Internal:
 * Hardware increments outstanding counter when NCB load request is sent for an LF
 * instruction.
 * Hardware decrements outstanding counter when either stdn is received for descriptor
 * write or if instruction indicated to send to SSO, then after we send SSO request.
 *
 * This register is incremented by the outstanding counter value each cycle
 * outstaniding count!=0.
 * Note: For error cases where we drop instructions count is decremented at the point
 * error was detected.
 */
union bdk_reex_af_inst_latency_pc
{
    uint64_t u;
    struct bdk_reex_af_inst_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for an instruction to complete (i.e., have the REE_RES_S
                                                                 result committed to memory).  Incremented every coprocessor-clock by the
                                                                 number of instructions active in that cycle. This may be divided by
                                                                 REE_AF_RD_REQ_PC to determine the average hardware instruction latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for an instruction to complete (i.e., have the REE_RES_S
                                                                 result committed to memory).  Incremented every coprocessor-clock by the
                                                                 number of instructions active in that cycle. This may be divided by
                                                                 REE_AF_RD_REQ_PC to determine the average hardware instruction latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_inst_latency_pc_s cn; */
};
typedef union bdk_reex_af_inst_latency_pc bdk_reex_af_inst_latency_pc_t;

static inline uint64_t BDK_REEX_AF_INST_LATENCY_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_INST_LATENCY_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000420ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_INST_LATENCY_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_INST_LATENCY_PC(a) bdk_reex_af_inst_latency_pc_t
#define bustype_BDK_REEX_AF_INST_LATENCY_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_INST_LATENCY_PC(a) "REEX_AF_INST_LATENCY_PC"
#define device_bar_BDK_REEX_AF_INST_LATENCY_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_INST_LATENCY_PC(a) (a)
#define arguments_BDK_REEX_AF_INST_LATENCY_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_inst_req_pc
 *
 * REE AF Instruction Request Performance Counter Register
 */
union bdk_reex_af_inst_req_pc
{
    uint64_t u;
    struct bdk_reex_af_inst_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of instructions (REE_INST_S) that have started processing. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of instructions (REE_INST_S) that have started processing. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_inst_req_pc_s cn; */
};
typedef union bdk_reex_af_inst_req_pc bdk_reex_af_inst_req_pc_t;

static inline uint64_t BDK_REEX_AF_INST_REQ_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_INST_REQ_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000410ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_INST_REQ_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_INST_REQ_PC(a) bdk_reex_af_inst_req_pc_t
#define bustype_BDK_REEX_AF_INST_REQ_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_INST_REQ_PC(a) "REEX_AF_INST_REQ_PC"
#define device_bar_BDK_REEX_AF_INST_REQ_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_INST_REQ_PC(a) (a)
#define arguments_BDK_REEX_AF_INST_REQ_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_lf_rst
 *
 * REE AF LF Reset Register
 */
union bdk_reex_af_lf_rst
{
    uint64_t u;
    struct bdk_reex_af_lf_rst_s
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
    /* struct bdk_reex_af_lf_rst_s cn; */
};
typedef union bdk_reex_af_lf_rst bdk_reex_af_lf_rst_t;

static inline uint64_t BDK_REEX_AF_LF_RST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_LF_RST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140043000ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_LF_RST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_LF_RST(a) bdk_reex_af_lf_rst_t
#define bustype_BDK_REEX_AF_LF_RST(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_LF_RST(a) "REEX_AF_LF_RST"
#define device_bar_BDK_REEX_AF_LF_RST(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_LF_RST(a) (a)
#define arguments_BDK_REEX_AF_LF_RST(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_pf_func
 *
 * RVU Admin Function PF FUNC Register
 */
union bdk_reex_af_pf_func
{
    uint64_t u;
    struct bdk_reex_af_pf_func_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t pf_func               : 16; /**< [ 15:  0](R/W) PF FUNC used to AQ fetches. AQ fetches are instruction fetches (REE_AF_AQ_INST_S)
                                                                 and data the instruction points to REE_AF_AQ_INST_S[ROF_PTR_ADDR].

                                                                 RVU_PF_FUNC_S describes the format of [PF_FUNC]. */
#else /* Word 0 - Little Endian */
        uint64_t pf_func               : 16; /**< [ 15:  0](R/W) PF FUNC used to AQ fetches. AQ fetches are instruction fetches (REE_AF_AQ_INST_S)
                                                                 and data the instruction points to REE_AF_AQ_INST_S[ROF_PTR_ADDR].

                                                                 RVU_PF_FUNC_S describes the format of [PF_FUNC]. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_pf_func_s cn; */
};
typedef union bdk_reex_af_pf_func bdk_reex_af_pf_func_t;

static inline uint64_t BDK_REEX_AF_PF_FUNC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_PF_FUNC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000210ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_PF_FUNC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_PF_FUNC(a) bdk_reex_af_pf_func_t
#define bustype_BDK_REEX_AF_PF_FUNC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_PF_FUNC(a) "REEX_AF_PF_FUNC"
#define device_bar_BDK_REEX_AF_PF_FUNC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_PF_FUNC(a) (a)
#define arguments_BDK_REEX_AF_PF_FUNC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_que#_gcfg
 *
 * REE Queue General Configuration Registers
 * These registers provide control per instruction queue.
 */
union bdk_reex_af_quex_gcfg
{
    uint64_t u;
    struct bdk_reex_af_quex_gcfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t il2_ldwb              : 1;  /**< [ 15: 15](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues regular NCB loads towards the cache, which will cause the
                                                                 line to be written back before being replaced.

                                                                 1 = The hardware issues LDWB read-and-invalidate NCB commands towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware. */
        uint64_t pl2ld_cmd             : 3;  /**< [ 14: 12](R/W) This field indicates the NCB load command to use for fetching payload and gather pointers.
                                                                 If the REE_INST_S[INP_PTR_CTL.NC] is set then the LDT instruction will be used, otherwise
                                                                 this field will be used to select load instruction. Enumerated by REE_L2LD_CMD_E. */
        uint64_t il2_pc                : 1;  /**< [ 11: 11](R/W) This bit controls the NCB load command type for REE_INST_S loads.
                                                                 1 = If loading the first half of a cache line for an instruction use NCB command
                                                                 from [IL2LD_CMD]. When loading the second half of cache line or the full
                                                                 cache line for an instruction use LDWB if [IL2_LDWB] is set otherwise use LDT.

                                                                 0 = Hardware uses NCB command from [IL2LD_CMD] for all loads of instructions. */
        uint64_t il2ld_cmd             : 3;  /**< [ 10:  8](R/W) Indicates the NCB load command to use for fetching instructions
                                                                 (REE_INST_S).
                                                                 See [IL2_PC] for more information.
                                                                 Enumerated by REE_L2LD_CMD_E. */
        uint64_t match_stype           : 2;  /**< [  7:  6](R/W) Type of NCB store command to use when writing REE_MATCH_S to LLC/DRAM.
                                                                 Enumerated by REE_STYPE_E. */
        uint64_t descr_stype           : 2;  /**< [  5:  4](R/W) Type of NCB store command to use when writing REE_RES_S to LLC/DRAM.
                                                                 It is recommend to use STF or STY.
                                                                 Enumerated by REE_STYPE_E. */
        uint64_t reserved_1_3          : 3;
        uint64_t strict_descr_wr       : 1;  /**< [  0:  0](R/W) Strict descriptor write.

                                                                 0 = When REE_INST_S[OOJ]=0 then REE will perform a descriptor write in queue
                                                                 order. REE doesn't guarantee that between descriptors from same queue that they
                                                                 are written to LLC/DRAM in order.  However, when SSO is used, REE does guarantee
                                                                 that all descriptors were written to LLC/DRAM in order before the job is
                                                                 submitted to SSO.

                                                                 1 = When REE_INST_S[OOJ]=0 then REE will not perform a descriptor write from the
                                                                 same queue until it guarantees that the LLC/DRAM has been written. */
#else /* Word 0 - Little Endian */
        uint64_t strict_descr_wr       : 1;  /**< [  0:  0](R/W) Strict descriptor write.

                                                                 0 = When REE_INST_S[OOJ]=0 then REE will perform a descriptor write in queue
                                                                 order. REE doesn't guarantee that between descriptors from same queue that they
                                                                 are written to LLC/DRAM in order.  However, when SSO is used, REE does guarantee
                                                                 that all descriptors were written to LLC/DRAM in order before the job is
                                                                 submitted to SSO.

                                                                 1 = When REE_INST_S[OOJ]=0 then REE will not perform a descriptor write from the
                                                                 same queue until it guarantees that the LLC/DRAM has been written. */
        uint64_t reserved_1_3          : 3;
        uint64_t descr_stype           : 2;  /**< [  5:  4](R/W) Type of NCB store command to use when writing REE_RES_S to LLC/DRAM.
                                                                 It is recommend to use STF or STY.
                                                                 Enumerated by REE_STYPE_E. */
        uint64_t match_stype           : 2;  /**< [  7:  6](R/W) Type of NCB store command to use when writing REE_MATCH_S to LLC/DRAM.
                                                                 Enumerated by REE_STYPE_E. */
        uint64_t il2ld_cmd             : 3;  /**< [ 10:  8](R/W) Indicates the NCB load command to use for fetching instructions
                                                                 (REE_INST_S).
                                                                 See [IL2_PC] for more information.
                                                                 Enumerated by REE_L2LD_CMD_E. */
        uint64_t il2_pc                : 1;  /**< [ 11: 11](R/W) This bit controls the NCB load command type for REE_INST_S loads.
                                                                 1 = If loading the first half of a cache line for an instruction use NCB command
                                                                 from [IL2LD_CMD]. When loading the second half of cache line or the full
                                                                 cache line for an instruction use LDWB if [IL2_LDWB] is set otherwise use LDT.

                                                                 0 = Hardware uses NCB command from [IL2LD_CMD] for all loads of instructions. */
        uint64_t pl2ld_cmd             : 3;  /**< [ 14: 12](R/W) This field indicates the NCB load command to use for fetching payload and gather pointers.
                                                                 If the REE_INST_S[INP_PTR_CTL.NC] is set then the LDT instruction will be used, otherwise
                                                                 this field will be used to select load instruction. Enumerated by REE_L2LD_CMD_E. */
        uint64_t il2_ldwb              : 1;  /**< [ 15: 15](R/W) Instruction load don't write back.

                                                                 0 = The hardware issues regular NCB loads towards the cache, which will cause the
                                                                 line to be written back before being replaced.

                                                                 1 = The hardware issues LDWB read-and-invalidate NCB commands towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_quex_gcfg_s cn; */
};
typedef union bdk_reex_af_quex_gcfg bdk_reex_af_quex_gcfg_t;

static inline uint64_t BDK_REEX_AF_QUEX_GCFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_QUEX_GCFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=35)))
        return 0x840140001a00ll + 0x10000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("REEX_AF_QUEX_GCFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_QUEX_GCFG(a,b) bdk_reex_af_quex_gcfg_t
#define bustype_BDK_REEX_AF_QUEX_GCFG(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_QUEX_GCFG(a,b) "REEX_AF_QUEX_GCFG"
#define device_bar_BDK_REEX_AF_QUEX_GCFG(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_QUEX_GCFG(a,b) (a)
#define arguments_BDK_REEX_AF_QUEX_GCFG(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_que#_gmctl
 *
 * REE Queue Guest Machine Control Register
 * This register configures queues.
 */
union bdk_reex_af_quex_gmctl
{
    uint64_t u;
    struct bdk_reex_af_quex_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t sso_af_func           : 16; /**< [ 15:  0](R/W) SSO RVU physical and virtual function. Indicates the RVU PF and VF to which
                                                                 queue's SSO add works are sent. */
#else /* Word 0 - Little Endian */
        uint64_t sso_af_func           : 16; /**< [ 15:  0](R/W) SSO RVU physical and virtual function. Indicates the RVU PF and VF to which
                                                                 queue's SSO add works are sent. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_quex_gmctl_s cn; */
};
typedef union bdk_reex_af_quex_gmctl bdk_reex_af_quex_gmctl_t;

static inline uint64_t BDK_REEX_AF_QUEX_GMCTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_QUEX_GMCTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=35)))
        return 0x840140000800ll + 0x10000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("REEX_AF_QUEX_GMCTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_QUEX_GMCTL(a,b) bdk_reex_af_quex_gmctl_t
#define bustype_BDK_REEX_AF_QUEX_GMCTL(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_QUEX_GMCTL(a,b) "REEX_AF_QUEX_GMCTL"
#define device_bar_BDK_REEX_AF_QUEX_GMCTL(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_QUEX_GMCTL(a,b) (a)
#define arguments_BDK_REEX_AF_QUEX_GMCTL(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_que#_sbuf_ctl
 *
 * REE Queue Buffer Parameter Registers
 * These registers set the buffer parameters for the instruction queues. When quiescent (i.e.
 * outstanding doorbell count is 0 and REE_LF_OUTSTAND_JOB[OJOB_CNT] is 0), it is safe
 * to rewrite this register. These registers must be programmed before software
 * programs the
 * corresponding REE_LF_SBUF_ADDR and before setting REE_LF_ENA[ENA].
 */
union bdk_reex_af_quex_sbuf_ctl
{
    uint64_t u;
    struct bdk_reex_af_quex_sbuf_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t size                  : 19; /**< [ 50: 32](R/W) Instruction buffer size, in units of 128 bytes (2*REE_INST_S), per ring. [SIZE]
                                                                 must be a power of 2. */
        uint64_t reserved_1_31         : 31;
        uint64_t pri                   : 1;  /**< [  0:  0](R/W) Queue priority.
                                                                 0 = Queue has lower priority. Round-robin between lower priority queues.
                                                                 1 = Queue has higher priority. Round-robin between higher priority queues. */
#else /* Word 0 - Little Endian */
        uint64_t pri                   : 1;  /**< [  0:  0](R/W) Queue priority.
                                                                 0 = Queue has lower priority. Round-robin between lower priority queues.
                                                                 1 = Queue has higher priority. Round-robin between higher priority queues. */
        uint64_t reserved_1_31         : 31;
        uint64_t size                  : 19; /**< [ 50: 32](R/W) Instruction buffer size, in units of 128 bytes (2*REE_INST_S), per ring. [SIZE]
                                                                 must be a power of 2. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_quex_sbuf_ctl_s cn; */
};
typedef union bdk_reex_af_quex_sbuf_ctl bdk_reex_af_quex_sbuf_ctl_t;

static inline uint64_t BDK_REEX_AF_QUEX_SBUF_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_QUEX_SBUF_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=35)))
        return 0x840140001200ll + 0x10000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("REEX_AF_QUEX_SBUF_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_QUEX_SBUF_CTL(a,b) bdk_reex_af_quex_sbuf_ctl_t
#define bustype_BDK_REEX_AF_QUEX_SBUF_CTL(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_QUEX_SBUF_CTL(a,b) "REEX_AF_QUEX_SBUF_CTL"
#define device_bar_BDK_REEX_AF_QUEX_SBUF_CTL(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_QUEX_SBUF_CTL(a,b) (a)
#define arguments_BDK_REEX_AF_QUEX_SBUF_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_ras
 *
 * REE AF RAS Register
 * This register contains AF RAS error flags for REE.
 */
union bdk_reex_af_ras
{
    uint64_t u;
    struct bdk_reex_af_ras_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t ld_reex_psn           : 1;  /**< [  2:  2](R/W1C/H) Poison received on a REEX response. */
        uint64_t ld_cmd_psn            : 1;  /**< [  1:  1](R/W1C/H) Poison received on a NCB instruction response, which include AQ instructions, LF
                                                                 instructions and gather pointer loads. */
        uint64_t ld_dat_psn            : 1;  /**< [  0:  0](R/W1C/H) Poison received on a NCB data response. */
#else /* Word 0 - Little Endian */
        uint64_t ld_dat_psn            : 1;  /**< [  0:  0](R/W1C/H) Poison received on a NCB data response. */
        uint64_t ld_cmd_psn            : 1;  /**< [  1:  1](R/W1C/H) Poison received on a NCB instruction response, which include AQ instructions, LF
                                                                 instructions and gather pointer loads. */
        uint64_t ld_reex_psn           : 1;  /**< [  2:  2](R/W1C/H) Poison received on a REEX response. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_ras_s cn; */
};
typedef union bdk_reex_af_ras bdk_reex_af_ras_t;

static inline uint64_t BDK_REEX_AF_RAS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RAS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000980ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RAS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RAS(a) bdk_reex_af_ras_t
#define bustype_BDK_REEX_AF_RAS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RAS(a) "REEX_AF_RAS"
#define device_bar_BDK_REEX_AF_RAS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RAS(a) (a)
#define arguments_BDK_REEX_AF_RAS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_ras_ena_w1c
 *
 * REE AF RAS Register
 * This register clears interrupt enable bits.
 */
union bdk_reex_af_ras_ena_w1c
{
    uint64_t u;
    struct bdk_reex_af_ras_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t ld_reex_psn           : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for REE_AF_RAS[LD_REEX_PSN]. */
        uint64_t ld_cmd_psn            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for REE_AF_RAS[LD_CMD_PSN]. */
        uint64_t ld_dat_psn            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for REE_AF_RAS[LD_DAT_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t ld_dat_psn            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for REE_AF_RAS[LD_DAT_PSN]. */
        uint64_t ld_cmd_psn            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for REE_AF_RAS[LD_CMD_PSN]. */
        uint64_t ld_reex_psn           : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for REE_AF_RAS[LD_REEX_PSN]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_ras_ena_w1c_s cn; */
};
typedef union bdk_reex_af_ras_ena_w1c bdk_reex_af_ras_ena_w1c_t;

static inline uint64_t BDK_REEX_AF_RAS_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RAS_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000990ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RAS_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RAS_ENA_W1C(a) bdk_reex_af_ras_ena_w1c_t
#define bustype_BDK_REEX_AF_RAS_ENA_W1C(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RAS_ENA_W1C(a) "REEX_AF_RAS_ENA_W1C"
#define device_bar_BDK_REEX_AF_RAS_ENA_W1C(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RAS_ENA_W1C(a) (a)
#define arguments_BDK_REEX_AF_RAS_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_ras_ena_w1s
 *
 * REE AF RAS Register
 * This register sets interrupt enable bits.
 */
union bdk_reex_af_ras_ena_w1s
{
    uint64_t u;
    struct bdk_reex_af_ras_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t ld_reex_psn           : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for REE_AF_RAS[LD_REEX_PSN]. */
        uint64_t ld_cmd_psn            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for REE_AF_RAS[LD_CMD_PSN]. */
        uint64_t ld_dat_psn            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for REE_AF_RAS[LD_DAT_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t ld_dat_psn            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for REE_AF_RAS[LD_DAT_PSN]. */
        uint64_t ld_cmd_psn            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for REE_AF_RAS[LD_CMD_PSN]. */
        uint64_t ld_reex_psn           : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for REE_AF_RAS[LD_REEX_PSN]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_ras_ena_w1s_s cn; */
};
typedef union bdk_reex_af_ras_ena_w1s bdk_reex_af_ras_ena_w1s_t;

static inline uint64_t BDK_REEX_AF_RAS_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RAS_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000998ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RAS_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RAS_ENA_W1S(a) bdk_reex_af_ras_ena_w1s_t
#define bustype_BDK_REEX_AF_RAS_ENA_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RAS_ENA_W1S(a) "REEX_AF_RAS_ENA_W1S"
#define device_bar_BDK_REEX_AF_RAS_ENA_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RAS_ENA_W1S(a) (a)
#define arguments_BDK_REEX_AF_RAS_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_ras_w1s
 *
 * REE AF RAS Register
 * This register sets interrupt bits.
 */
union bdk_reex_af_ras_w1s
{
    uint64_t u;
    struct bdk_reex_af_ras_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t ld_reex_psn           : 1;  /**< [  2:  2](R/W1S/H) Reads or sets REE_AF_RAS[LD_REEX_PSN]. */
        uint64_t ld_cmd_psn            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets REE_AF_RAS[LD_CMD_PSN]. */
        uint64_t ld_dat_psn            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets REE_AF_RAS[LD_DAT_PSN]. */
#else /* Word 0 - Little Endian */
        uint64_t ld_dat_psn            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets REE_AF_RAS[LD_DAT_PSN]. */
        uint64_t ld_cmd_psn            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets REE_AF_RAS[LD_CMD_PSN]. */
        uint64_t ld_reex_psn           : 1;  /**< [  2:  2](R/W1S/H) Reads or sets REE_AF_RAS[LD_REEX_PSN]. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_ras_w1s_s cn; */
};
typedef union bdk_reex_af_ras_w1s bdk_reex_af_ras_w1s_t;

static inline uint64_t BDK_REEX_AF_RAS_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RAS_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000988ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RAS_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RAS_W1S(a) bdk_reex_af_ras_w1s_t
#define bustype_BDK_REEX_AF_RAS_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RAS_W1S(a) "REEX_AF_RAS_W1S"
#define device_bar_BDK_REEX_AF_RAS_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RAS_W1S(a) (a)
#define arguments_BDK_REEX_AF_RAS_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_rd_latency_pc
 *
 * REE AF Read Latency Counter Register
 */
union bdk_reex_af_rd_latency_pc
{
    uint64_t u;
    struct bdk_reex_af_rd_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for NCB read returns. Incremented every
                                                                 coprocessor-clock by the number of read transactions outstanding in that cycle. This
                                                                 may be divided by REE_AF_RD_REQ_PC to determine the average read latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for NCB read returns. Incremented every
                                                                 coprocessor-clock by the number of read transactions outstanding in that cycle. This
                                                                 may be divided by REE_AF_RD_REQ_PC to determine the average read latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_rd_latency_pc_s cn; */
};
typedef union bdk_reex_af_rd_latency_pc bdk_reex_af_rd_latency_pc_t;

static inline uint64_t BDK_REEX_AF_RD_LATENCY_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RD_LATENCY_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000440ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RD_LATENCY_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RD_LATENCY_PC(a) bdk_reex_af_rd_latency_pc_t
#define bustype_BDK_REEX_AF_RD_LATENCY_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RD_LATENCY_PC(a) "REEX_AF_RD_LATENCY_PC"
#define device_bar_BDK_REEX_AF_RD_LATENCY_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RD_LATENCY_PC(a) (a)
#define arguments_BDK_REEX_AF_RD_LATENCY_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_rd_req_pc
 *
 * REE AF Read Request Performance Counter Register
 */
union bdk_reex_af_rd_req_pc
{
    uint64_t u;
    struct bdk_reex_af_rd_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of NCB read requests issued. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of NCB read requests issued. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_rd_req_pc_s cn; */
};
typedef union bdk_reex_af_rd_req_pc bdk_reex_af_rd_req_pc_t;

static inline uint64_t BDK_REEX_AF_RD_REQ_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RD_REQ_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000430ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RD_REQ_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RD_REQ_PC(a) bdk_reex_af_rd_req_pc_t
#define bustype_BDK_REEX_AF_RD_REQ_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RD_REQ_PC(a) "REEX_AF_RD_REQ_PC"
#define device_bar_BDK_REEX_AF_RD_REQ_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RD_REQ_PC(a) (a)
#define arguments_BDK_REEX_AF_RD_REQ_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reex_active_jobs_pc
 *
 * REE AF REEX Active Jobs Counter Register
 */
union bdk_reex_af_reex_active_jobs_pc
{
    uint64_t u;
    struct bdk_reex_af_reex_active_jobs_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Performance counter. Number of active jobs existing in REEX. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Performance counter. Number of active jobs existing in REEX. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reex_active_jobs_pc_s cn; */
};
typedef union bdk_reex_af_reex_active_jobs_pc bdk_reex_af_reex_active_jobs_pc_t;

static inline uint64_t BDK_REEX_AF_REEX_ACTIVE_JOBS_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEX_ACTIVE_JOBS_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000490ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEX_ACTIVE_JOBS_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEX_ACTIVE_JOBS_PC(a) bdk_reex_af_reex_active_jobs_pc_t
#define bustype_BDK_REEX_AF_REEX_ACTIVE_JOBS_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEX_ACTIVE_JOBS_PC(a) "REEX_AF_REEX_ACTIVE_JOBS_PC"
#define device_bar_BDK_REEX_AF_REEX_ACTIVE_JOBS_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEX_ACTIVE_JOBS_PC(a) (a)
#define arguments_BDK_REEX_AF_REEX_ACTIVE_JOBS_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reex_rd_latency_pc
 *
 * REE AF REEX Read Latency Counter Register
 */
union bdk_reex_af_reex_rd_latency_pc
{
    uint64_t u;
    struct bdk_reex_af_reex_rd_latency_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for NCB REEX-read returns. Incremented every
                                                                 coprocessor-clock by the number of REEX read transactions outstanding in that cycle. This
                                                                 may be divided by REE_AF_REEX_RD_REQ_PC to determine the average read latency. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of cycles waiting for NCB REEX-read returns. Incremented every
                                                                 coprocessor-clock by the number of REEX read transactions outstanding in that cycle. This
                                                                 may be divided by REE_AF_REEX_RD_REQ_PC to determine the average read latency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reex_rd_latency_pc_s cn; */
};
typedef union bdk_reex_af_reex_rd_latency_pc bdk_reex_af_reex_rd_latency_pc_t;

static inline uint64_t BDK_REEX_AF_REEX_RD_LATENCY_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEX_RD_LATENCY_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000470ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEX_RD_LATENCY_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEX_RD_LATENCY_PC(a) bdk_reex_af_reex_rd_latency_pc_t
#define bustype_BDK_REEX_AF_REEX_RD_LATENCY_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEX_RD_LATENCY_PC(a) "REEX_AF_REEX_RD_LATENCY_PC"
#define device_bar_BDK_REEX_AF_REEX_RD_LATENCY_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEX_RD_LATENCY_PC(a) (a)
#define arguments_BDK_REEX_AF_REEX_RD_LATENCY_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reex_rd_req_pc
 *
 * REE AF REEX Read Request Performance Counter Register
 */
union bdk_reex_af_reex_rd_req_pc
{
    uint64_t u;
    struct bdk_reex_af_reex_rd_req_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of NCB REEX-read requests issued. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Number of NCB REEX-read requests issued. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reex_rd_req_pc_s cn; */
};
typedef union bdk_reex_af_reex_rd_req_pc bdk_reex_af_reex_rd_req_pc_t;

static inline uint64_t BDK_REEX_AF_REEX_RD_REQ_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEX_RD_REQ_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000460ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEX_RD_REQ_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEX_RD_REQ_PC(a) bdk_reex_af_reex_rd_req_pc_t
#define bustype_BDK_REEX_AF_REEX_RD_REQ_PC(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEX_RD_REQ_PC(a) "REEX_AF_REEX_RD_REQ_PC"
#define device_bar_BDK_REEX_AF_REEX_RD_REQ_PC(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEX_RD_REQ_PC(a) (a)
#define arguments_BDK_REEX_AF_REEX_RD_REQ_PC(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_capability_1
 *
 * REE AF REEX Main Capability 1 Register
 * This register contains capability information about REEX.
 */
union bdk_reex_af_reexm_capability_1
{
    uint64_t u;
    struct bdk_reex_af_reexm_capability_1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t num_tces              : 8;  /**< [ 31: 24](RO) Number of thread control engines (16 per cluster). */
        uint64_t num_jces              : 8;  /**< [ 23: 16](RO) Number of job control engines (8 per cluster). */
        uint64_t num_clusters          : 8;  /**< [ 15:  8](RO) Number of clusters. */
        uint64_t data_width            : 8;  /**< [  7:  0](RO) Width of job-data buses (In/Out) - log2 of value. Value 0x06 represents 64 bit. */
#else /* Word 0 - Little Endian */
        uint64_t data_width            : 8;  /**< [  7:  0](RO) Width of job-data buses (In/Out) - log2 of value. Value 0x06 represents 64 bit. */
        uint64_t num_clusters          : 8;  /**< [ 15:  8](RO) Number of clusters. */
        uint64_t num_jces              : 8;  /**< [ 23: 16](RO) Number of job control engines (8 per cluster). */
        uint64_t num_tces              : 8;  /**< [ 31: 24](RO) Number of thread control engines (16 per cluster). */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_capability_1_s cn; */
};
typedef union bdk_reex_af_reexm_capability_1 bdk_reex_af_reexm_capability_1_t;

static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008018ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CAPABILITY_1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CAPABILITY_1(a) bdk_reex_af_reexm_capability_1_t
#define bustype_BDK_REEX_AF_REEXM_CAPABILITY_1(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CAPABILITY_1(a) "REEX_AF_REEXM_CAPABILITY_1"
#define device_bar_BDK_REEX_AF_REEXM_CAPABILITY_1(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CAPABILITY_1(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CAPABILITY_1(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_capability_2
 *
 * REE AF REEX Main Capability 2 Register
 * This register contains capability information about REEX.
 */
union bdk_reex_af_reexm_capability_2
{
    uint64_t u;
    struct bdk_reex_af_reexm_capability_2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t pp_if                 : 8;  /**< [ 31: 24](RO) Programming Plane Interface type. Value 0x01 represents Native. */
        uint64_t emce_if               : 8;  /**< [ 23: 16](RO) External Memory Control Engine Application Interface type.
                                                                 Value 0x16 means AXI Master Read only. */
        uint64_t data_plane_if         : 8;  /**< [ 15:  8](RO) Data Plane Interface type. Value 0x01 represents Native. */
        uint64_t ctrl_plane_if         : 8;  /**< [  7:  0](RO) Control Plane Interface type. Value 0x01 represents Native. */
#else /* Word 0 - Little Endian */
        uint64_t ctrl_plane_if         : 8;  /**< [  7:  0](RO) Control Plane Interface type. Value 0x01 represents Native. */
        uint64_t data_plane_if         : 8;  /**< [ 15:  8](RO) Data Plane Interface type. Value 0x01 represents Native. */
        uint64_t emce_if               : 8;  /**< [ 23: 16](RO) External Memory Control Engine Application Interface type.
                                                                 Value 0x16 means AXI Master Read only. */
        uint64_t pp_if                 : 8;  /**< [ 31: 24](RO) Programming Plane Interface type. Value 0x01 represents Native. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_capability_2_s cn; */
};
typedef union bdk_reex_af_reexm_capability_2 bdk_reex_af_reexm_capability_2_t;

static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008020ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CAPABILITY_2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CAPABILITY_2(a) bdk_reex_af_reexm_capability_2_t
#define bustype_BDK_REEX_AF_REEXM_CAPABILITY_2(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CAPABILITY_2(a) "REEX_AF_REEXM_CAPABILITY_2"
#define device_bar_BDK_REEX_AF_REEXM_CAPABILITY_2(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CAPABILITY_2(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CAPABILITY_2(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_capability_3
 *
 * REE AF REEX Main Capability 3 Register
 * This register contains capability information about REEX.
 */
union bdk_reex_af_reexm_capability_3
{
    uint64_t u;
    struct bdk_reex_af_reexm_capability_3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t ppe_instr_ram_1_3     : 4;  /**< [ 31: 28](RO) Address widths for PPE instruction RAM 1_3. */
        uint64_t ppe_instr_ram_1_2     : 4;  /**< [ 27: 24](RO) Address widths for PPE instruction RAM 1_2. */
        uint64_t ppe_instr_ram_1_1     : 4;  /**< [ 23: 20](RO) Address widths for PPE instruction RAM 1_1. */
        uint64_t ppe_instr_ram_1_0     : 4;  /**< [ 19: 16](RO) Address widths for PPE instruction RAM 1_0. */
        uint64_t vppe_instr_ram_0_1    : 4;  /**< [ 15: 12](RO) Address widths for VPPE instruction RAM 0_1. */
        uint64_t vppe_instr_ram_0_0    : 4;  /**< [ 11:  8](RO) Address widths for VPPE instruction RAM 0_0. */
        uint64_t ppe_change_case_ram   : 4;  /**< [  7:  4](RO) Address widths for PPE change Case RAM. */
        uint64_t ppe_instr_ram_0_0     : 4;  /**< [  3:  0](RO) Address widths for PPE instruction RAM 0_0. */
#else /* Word 0 - Little Endian */
        uint64_t ppe_instr_ram_0_0     : 4;  /**< [  3:  0](RO) Address widths for PPE instruction RAM 0_0. */
        uint64_t ppe_change_case_ram   : 4;  /**< [  7:  4](RO) Address widths for PPE change Case RAM. */
        uint64_t vppe_instr_ram_0_0    : 4;  /**< [ 11:  8](RO) Address widths for VPPE instruction RAM 0_0. */
        uint64_t vppe_instr_ram_0_1    : 4;  /**< [ 15: 12](RO) Address widths for VPPE instruction RAM 0_1. */
        uint64_t ppe_instr_ram_1_0     : 4;  /**< [ 19: 16](RO) Address widths for PPE instruction RAM 1_0. */
        uint64_t ppe_instr_ram_1_1     : 4;  /**< [ 23: 20](RO) Address widths for PPE instruction RAM 1_1. */
        uint64_t ppe_instr_ram_1_2     : 4;  /**< [ 27: 24](RO) Address widths for PPE instruction RAM 1_2. */
        uint64_t ppe_instr_ram_1_3     : 4;  /**< [ 31: 28](RO) Address widths for PPE instruction RAM 1_3. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_capability_3_s cn; */
};
typedef union bdk_reex_af_reexm_capability_3 bdk_reex_af_reexm_capability_3_t;

static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008028ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CAPABILITY_3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CAPABILITY_3(a) bdk_reex_af_reexm_capability_3_t
#define bustype_BDK_REEX_AF_REEXM_CAPABILITY_3(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CAPABILITY_3(a) "REEX_AF_REEXM_CAPABILITY_3"
#define device_bar_BDK_REEX_AF_REEXM_CAPABILITY_3(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CAPABILITY_3(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CAPABILITY_3(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_capability_4
 *
 * REE AF REEX Main Capability 4 Register
 * This register contains capability information about REEX.
 */
union bdk_reex_af_reexm_capability_4
{
    uint64_t u;
    struct bdk_reex_af_reexm_capability_4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t ppe_instr_ram_3_3     : 4;  /**< [ 31: 28](RO) Address widths for PPE instruction RAM 3_3. */
        uint64_t ppe_instr_ram_3_2     : 4;  /**< [ 27: 24](RO) Address widths for PPE instruction RAM 3_2. */
        uint64_t ppe_instr_ram_3_1     : 4;  /**< [ 23: 20](RO) Address widths for PPE instruction RAM 3_1. */
        uint64_t ppe_instr_ram_3_0     : 4;  /**< [ 19: 16](RO) Address widths for PPE instruction RAM 3_0. */
        uint64_t ppe_instr_ram_2_3     : 4;  /**< [ 15: 12](RO) Address widths for PPE instruction RAM 2_3. */
        uint64_t ppe_instr_ram_2_2     : 4;  /**< [ 11:  8](RO) Address widths for PPE instruction RAM 2_2. */
        uint64_t ppe_instr_ram_2_1     : 4;  /**< [  7:  4](RO) Address widths for PPE instruction RAM 2_1. */
        uint64_t ppe_instr_ram_2_0     : 4;  /**< [  3:  0](RO) Address widths for PPE instruction RAM 2_0. */
#else /* Word 0 - Little Endian */
        uint64_t ppe_instr_ram_2_0     : 4;  /**< [  3:  0](RO) Address widths for PPE instruction RAM 2_0. */
        uint64_t ppe_instr_ram_2_1     : 4;  /**< [  7:  4](RO) Address widths for PPE instruction RAM 2_1. */
        uint64_t ppe_instr_ram_2_2     : 4;  /**< [ 11:  8](RO) Address widths for PPE instruction RAM 2_2. */
        uint64_t ppe_instr_ram_2_3     : 4;  /**< [ 15: 12](RO) Address widths for PPE instruction RAM 2_3. */
        uint64_t ppe_instr_ram_3_0     : 4;  /**< [ 19: 16](RO) Address widths for PPE instruction RAM 3_0. */
        uint64_t ppe_instr_ram_3_1     : 4;  /**< [ 23: 20](RO) Address widths for PPE instruction RAM 3_1. */
        uint64_t ppe_instr_ram_3_2     : 4;  /**< [ 27: 24](RO) Address widths for PPE instruction RAM 3_2. */
        uint64_t ppe_instr_ram_3_3     : 4;  /**< [ 31: 28](RO) Address widths for PPE instruction RAM 3_3. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_capability_4_s cn; */
};
typedef union bdk_reex_af_reexm_capability_4 bdk_reex_af_reexm_capability_4_t;

static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008030ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CAPABILITY_4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CAPABILITY_4(a) bdk_reex_af_reexm_capability_4_t
#define bustype_BDK_REEX_AF_REEXM_CAPABILITY_4(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CAPABILITY_4(a) "REEX_AF_REEXM_CAPABILITY_4"
#define device_bar_BDK_REEX_AF_REEXM_CAPABILITY_4(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CAPABILITY_4(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CAPABILITY_4(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_capability_5
 *
 * REE AF REEX Main Capability 5 Register
 * This register contains capability information about REEX.
 */
union bdk_reex_af_reexm_capability_5
{
    uint64_t u;
    struct bdk_reex_af_reexm_capability_5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t max_num_match_per_job : 16; /**< [ 31: 16](RO) Maximum number of matches returned per job. */
        uint64_t max_num_pf_per_job    : 16; /**< [ 15:  0](RO) Maximum number of prefixes per job. */
#else /* Word 0 - Little Endian */
        uint64_t max_num_pf_per_job    : 16; /**< [ 15:  0](RO) Maximum number of prefixes per job. */
        uint64_t max_num_match_per_job : 16; /**< [ 31: 16](RO) Maximum number of matches returned per job. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_capability_5_s cn; */
};
typedef union bdk_reex_af_reexm_capability_5 bdk_reex_af_reexm_capability_5_t;

static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008038ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CAPABILITY_5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CAPABILITY_5(a) bdk_reex_af_reexm_capability_5_t
#define bustype_BDK_REEX_AF_REEXM_CAPABILITY_5(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CAPABILITY_5(a) "REEX_AF_REEXM_CAPABILITY_5"
#define device_bar_BDK_REEX_AF_REEXM_CAPABILITY_5(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CAPABILITY_5(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CAPABILITY_5(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_capability_6
 *
 * REE AF REEX Main Capability 6 Register
 * This register contains capability information about REEX.
 */
union bdk_reex_af_reexm_capability_6
{
    uint64_t u;
    struct bdk_reex_af_reexm_capability_6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t l2_cache_size_kb      : 16; /**< [ 31: 16](RO) L2 cache size (KB). */
        uint64_t l1_cache_size_kb      : 8;  /**< [ 15:  8](RO) L1 cache size (KB). */
        uint64_t tcm_size_kb           : 8;  /**< [  7:  0](RO) Tightly coupled memory size (KB). */
#else /* Word 0 - Little Endian */
        uint64_t tcm_size_kb           : 8;  /**< [  7:  0](RO) Tightly coupled memory size (KB). */
        uint64_t l1_cache_size_kb      : 8;  /**< [ 15:  8](RO) L1 cache size (KB). */
        uint64_t l2_cache_size_kb      : 16; /**< [ 31: 16](RO) L2 cache size (KB). */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_capability_6_s cn; */
};
typedef union bdk_reex_af_reexm_capability_6 bdk_reex_af_reexm_capability_6_t;

static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008040ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CAPABILITY_6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CAPABILITY_6(a) bdk_reex_af_reexm_capability_6_t
#define bustype_BDK_REEX_AF_REEXM_CAPABILITY_6(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CAPABILITY_6(a) "REEX_AF_REEXM_CAPABILITY_6"
#define device_bar_BDK_REEX_AF_REEXM_CAPABILITY_6(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CAPABILITY_6(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CAPABILITY_6(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_capability_7
 *
 * REE AF REEX Main Capability 7 Register
 * This register contains capability information about REEX.
 */
union bdk_reex_af_reexm_capability_7
{
    uint64_t u;
    struct bdk_reex_af_reexm_capability_7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t unix_time             : 32; /**< [ 31:  0](RO) Unix timestamp for RTL drop. Value is drop-specific. */
#else /* Word 0 - Little Endian */
        uint64_t unix_time             : 32; /**< [ 31:  0](RO) Unix timestamp for RTL drop. Value is drop-specific. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_capability_7_s cn; */
};
typedef union bdk_reex_af_reexm_capability_7 bdk_reex_af_reexm_capability_7_t;

static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CAPABILITY_7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008048ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CAPABILITY_7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CAPABILITY_7(a) bdk_reex_af_reexm_capability_7_t
#define bustype_BDK_REEX_AF_REEXM_CAPABILITY_7(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CAPABILITY_7(a) "REEX_AF_REEXM_CAPABILITY_7"
#define device_bar_BDK_REEX_AF_REEXM_CAPABILITY_7(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CAPABILITY_7(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CAPABILITY_7(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_clstr_mask
 *
 * REE AF REEX Main Cluster Mask Register
 */
union bdk_reex_af_reexm_clstr_mask
{
    uint64_t u;
    struct bdk_reex_af_reexm_clstr_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t reex_reserved_1       : 24; /**< [ 31:  8](R/W) Reserved. */
        uint64_t mask                  : 8;  /**< [  7:  0](R/W) Mask (disable) clusters. Bit i=0..7 is for disabling cluster[i]. */
#else /* Word 0 - Little Endian */
        uint64_t mask                  : 8;  /**< [  7:  0](R/W) Mask (disable) clusters. Bit i=0..7 is for disabling cluster[i]. */
        uint64_t reex_reserved_1       : 24; /**< [ 31:  8](R/W) Reserved. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_clstr_mask_s cn; */
};
typedef union bdk_reex_af_reexm_clstr_mask bdk_reex_af_reexm_clstr_mask_t;

static inline uint64_t BDK_REEX_AF_REEXM_CLSTR_MASK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CLSTR_MASK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080f0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CLSTR_MASK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CLSTR_MASK(a) bdk_reex_af_reexm_clstr_mask_t
#define bustype_BDK_REEX_AF_REEXM_CLSTR_MASK(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CLSTR_MASK(a) "REEX_AF_REEXM_CLSTR_MASK"
#define device_bar_BDK_REEX_AF_REEXM_CLSTR_MASK(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CLSTR_MASK(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CLSTR_MASK(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_core_clk_count
 *
 * REE AF REEX Main Core Clock Count Register
 */
union bdk_reex_af_reexm_core_clk_count
{
    uint64_t u;
    struct bdk_reex_af_reexm_core_clk_count_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Number of core-clock cycles since initialization triggered. Wraps around. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Number of core-clock cycles since initialization triggered. Wraps around. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_core_clk_count_s cn; */
};
typedef union bdk_reex_af_reexm_core_clk_count bdk_reex_af_reexm_core_clk_count_t;

static inline uint64_t BDK_REEX_AF_REEXM_CORE_CLK_COUNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CORE_CLK_COUNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008080ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CORE_CLK_COUNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CORE_CLK_COUNT(a) bdk_reex_af_reexm_core_clk_count_t
#define bustype_BDK_REEX_AF_REEXM_CORE_CLK_COUNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CORE_CLK_COUNT(a) "REEX_AF_REEXM_CORE_CLK_COUNT"
#define device_bar_BDK_REEX_AF_REEXM_CORE_CLK_COUNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CORE_CLK_COUNT(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CORE_CLK_COUNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_ctrl
 *
 * REE AF REEX Main Control Register
 */
union bdk_reex_af_reexm_ctrl
{
    uint64_t u;
    struct bdk_reex_af_reexm_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t reex_reserved_1       : 28; /**< [ 31:  4](R/W) Reserved. Must be kept 0.
                                                                 Internal:
                                                                 Bits 7,5,4 are disable bits for L2_CACHE, Match-FIFO, Result-Descriptor FIFO,
                                                                 respcetively, for Titan internal use.
                                                                 Bits 5,4 must be set to 0, otherwise REEX FIFOs might not be in sync, and REE
                                                                 might get hung up waiting for Matches or Descriptors. */
        uint64_t go                    : 1;  /**< [  3:  3](R/W) Set this bit to cause REEX to start scanning jobs for matches. */
        uint64_t reex_reserved_2       : 2;  /**< [  2:  1](R/W) Reserved, Must be kept 0. */
        uint64_t init                  : 1;  /**< [  0:  0](R/W) Set to initialize REEX. */
#else /* Word 0 - Little Endian */
        uint64_t init                  : 1;  /**< [  0:  0](R/W) Set to initialize REEX. */
        uint64_t reex_reserved_2       : 2;  /**< [  2:  1](R/W) Reserved, Must be kept 0. */
        uint64_t go                    : 1;  /**< [  3:  3](R/W) Set this bit to cause REEX to start scanning jobs for matches. */
        uint64_t reex_reserved_1       : 28; /**< [ 31:  4](R/W) Reserved. Must be kept 0.
                                                                 Internal:
                                                                 Bits 7,5,4 are disable bits for L2_CACHE, Match-FIFO, Result-Descriptor FIFO,
                                                                 respcetively, for Titan internal use.
                                                                 Bits 5,4 must be set to 0, otherwise REEX FIFOs might not be in sync, and REE
                                                                 might get hung up waiting for Matches or Descriptors. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_ctrl_s cn; */
};
typedef union bdk_reex_af_reexm_ctrl bdk_reex_af_reexm_ctrl_t;

static inline uint64_t BDK_REEX_AF_REEXM_CTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_CTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080c0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_CTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_CTRL(a) bdk_reex_af_reexm_ctrl_t
#define bustype_BDK_REEX_AF_REEXM_CTRL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_CTRL(a) "REEX_AF_REEXM_CTRL"
#define device_bar_BDK_REEX_AF_REEXM_CTRL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_CTRL(a) (a)
#define arguments_BDK_REEX_AF_REEXM_CTRL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_dos_count
 *
 * REE AF REEX Main Max DOS Count Register
 */
union bdk_reex_af_reexm_dos_count
{
    uint64_t u;
    struct bdk_reex_af_reexm_dos_count_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Number of jobs where the number of prefixes detected has reached
                                                                 MAX_PREFIX_COUNT which can be used to indicate that a DoS attempt has occurred. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Number of jobs where the number of prefixes detected has reached
                                                                 MAX_PREFIX_COUNT which can be used to indicate that a DoS attempt has occurred. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_dos_count_s cn; */
};
typedef union bdk_reex_af_reexm_dos_count bdk_reex_af_reexm_dos_count_t;

static inline uint64_t BDK_REEX_AF_REEXM_DOS_COUNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_DOS_COUNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008068ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_DOS_COUNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_DOS_COUNT(a) bdk_reex_af_reexm_dos_count_t
#define bustype_BDK_REEX_AF_REEXM_DOS_COUNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_DOS_COUNT(a) "REEX_AF_REEXM_DOS_COUNT"
#define device_bar_BDK_REEX_AF_REEXM_DOS_COUNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_DOS_COUNT(a) (a)
#define arguments_BDK_REEX_AF_REEXM_DOS_COUNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_fifo_status_0
 *
 * REE AF REEX Job Request FIFOs Status Register
 */
union bdk_reex_af_reexm_fifo_status_0
{
    uint64_t u;
    struct bdk_reex_af_reexm_fifo_status_0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t jf_num_entries        : 16; /**< [ 31: 16](RO/H) Fill level of REEX job FIFO. */
        uint64_t jdf_num_entries       : 16; /**< [ 15:  0](RO/H) Fill level of REEX job descriptor FIFO. */
#else /* Word 0 - Little Endian */
        uint64_t jdf_num_entries       : 16; /**< [ 15:  0](RO/H) Fill level of REEX job descriptor FIFO. */
        uint64_t jf_num_entries        : 16; /**< [ 31: 16](RO/H) Fill level of REEX job FIFO. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_fifo_status_0_s cn; */
};
typedef union bdk_reex_af_reexm_fifo_status_0 bdk_reex_af_reexm_fifo_status_0_t;

static inline uint64_t BDK_REEX_AF_REEXM_FIFO_STATUS_0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_FIFO_STATUS_0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008058ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_FIFO_STATUS_0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_FIFO_STATUS_0(a) bdk_reex_af_reexm_fifo_status_0_t
#define bustype_BDK_REEX_AF_REEXM_FIFO_STATUS_0(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_FIFO_STATUS_0(a) "REEX_AF_REEXM_FIFO_STATUS_0"
#define device_bar_BDK_REEX_AF_REEXM_FIFO_STATUS_0(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_FIFO_STATUS_0(a) (a)
#define arguments_BDK_REEX_AF_REEXM_FIFO_STATUS_0(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_fifo_status_1
 *
 * REE AF REEX Job Response FIFOs Status Register
 */
union bdk_reex_af_reexm_fifo_status_1
{
    uint64_t u;
    struct bdk_reex_af_reexm_fifo_status_1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t mf_num_entries        : 16; /**< [ 31: 16](RO/H) Fill level of REEX match FIFO. */
        uint64_t rdf_num_entries       : 16; /**< [ 15:  0](RO/H) Fill level of REEX response descriptor FIFO. */
#else /* Word 0 - Little Endian */
        uint64_t rdf_num_entries       : 16; /**< [ 15:  0](RO/H) Fill level of REEX response descriptor FIFO. */
        uint64_t mf_num_entries        : 16; /**< [ 31: 16](RO/H) Fill level of REEX match FIFO. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_fifo_status_1_s cn; */
};
typedef union bdk_reex_af_reexm_fifo_status_1 bdk_reex_af_reexm_fifo_status_1_t;

static inline uint64_t BDK_REEX_AF_REEXM_FIFO_STATUS_1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_FIFO_STATUS_1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008060ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_FIFO_STATUS_1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_FIFO_STATUS_1(a) bdk_reex_af_reexm_fifo_status_1_t
#define bustype_BDK_REEX_AF_REEXM_FIFO_STATUS_1(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_FIFO_STATUS_1(a) "REEX_AF_REEXM_FIFO_STATUS_1"
#define device_bar_BDK_REEX_AF_REEXM_FIFO_STATUS_1(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_FIFO_STATUS_1(a) (a)
#define arguments_BDK_REEX_AF_REEXM_FIFO_STATUS_1(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_identifier
 *
 * REE AF REEX Main Identifier Register
 * This register provides identification information about REEX.
 */
union bdk_reex_af_reexm_identifier
{
    uint64_t u;
    struct bdk_reex_af_reexm_identifier_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t minor_ver             : 8;  /**< [ 31: 24](RO) Minor version identifier. */
        uint64_t major_ver             : 8;  /**< [ 23: 16](RO) Major version identifier. */
        uint64_t product_id            : 8;  /**< [ 15:  8](RO) Product identifier. Set to 0x52 i.e R for REEX. */
        uint64_t vendor_id             : 8;  /**< [  7:  0](RO) VendoriIdentifier. */
#else /* Word 0 - Little Endian */
        uint64_t vendor_id             : 8;  /**< [  7:  0](RO) VendoriIdentifier. */
        uint64_t product_id            : 8;  /**< [ 15:  8](RO) Product identifier. Set to 0x52 i.e R for REEX. */
        uint64_t major_ver             : 8;  /**< [ 23: 16](RO) Major version identifier. */
        uint64_t minor_ver             : 8;  /**< [ 31: 24](RO) Minor version identifier. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_identifier_s cn; */
};
typedef union bdk_reex_af_reexm_identifier bdk_reex_af_reexm_identifier_t;

static inline uint64_t BDK_REEX_AF_REEXM_IDENTIFIER(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_IDENTIFIER(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008000ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_IDENTIFIER", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_IDENTIFIER(a) bdk_reex_af_reexm_identifier_t
#define bustype_BDK_REEX_AF_REEXM_IDENTIFIER(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_IDENTIFIER(a) "REEX_AF_REEXM_IDENTIFIER"
#define device_bar_BDK_REEX_AF_REEXM_IDENTIFIER(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_IDENTIFIER(a) (a)
#define arguments_BDK_REEX_AF_REEXM_IDENTIFIER(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_intr_clstr_mask
 *
 * REE AF REEX Main Intra Cluster Mask Register
 * Support masking of JCEs and TCEs, inside all clusters not totally masked by
 * REE_AF_REEXM_CLSTR_MASK.
 */
union bdk_reex_af_reexm_intr_clstr_mask
{
    uint64_t u;
    struct bdk_reex_af_reexm_intr_clstr_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t tce_mask              : 16; /**< [ 31: 16](R/W) Mask (disable) TCEs in cluster. */
        uint64_t reex_reserved_1       : 8;  /**< [ 15:  8](R/W) Reserved. */
        uint64_t jce_mask              : 8;  /**< [  7:  0](R/W) Mask (disable) JCEs in cluster. */
#else /* Word 0 - Little Endian */
        uint64_t jce_mask              : 8;  /**< [  7:  0](R/W) Mask (disable) JCEs in cluster. */
        uint64_t reex_reserved_1       : 8;  /**< [ 15:  8](R/W) Reserved. */
        uint64_t tce_mask              : 16; /**< [ 31: 16](R/W) Mask (disable) TCEs in cluster. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_intr_clstr_mask_s cn; */
};
typedef union bdk_reex_af_reexm_intr_clstr_mask bdk_reex_af_reexm_intr_clstr_mask_t;

static inline uint64_t BDK_REEX_AF_REEXM_INTR_CLSTR_MASK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_INTR_CLSTR_MASK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080f8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_INTR_CLSTR_MASK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_INTR_CLSTR_MASK(a) bdk_reex_af_reexm_intr_clstr_mask_t
#define bustype_BDK_REEX_AF_REEXM_INTR_CLSTR_MASK(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_INTR_CLSTR_MASK(a) "REEX_AF_REEXM_INTR_CLSTR_MASK"
#define device_bar_BDK_REEX_AF_REEXM_INTR_CLSTR_MASK(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_INTR_CLSTR_MASK(a) (a)
#define arguments_BDK_REEX_AF_REEXM_INTR_CLSTR_MASK(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_job_byt_count_0
 *
 * REE AF REEX Main Job Byte Count LSB Register
 */
union bdk_reex_af_reexm_job_byt_count_0
{
    uint64_t u;
    struct bdk_reex_af_reexm_job_byt_count_0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Total number of job data bytes parsed, 32 lower bits. Wraps around. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Total number of job data bytes parsed, 32 lower bits. Wraps around. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_job_byt_count_0_s cn; */
};
typedef union bdk_reex_af_reexm_job_byt_count_0 bdk_reex_af_reexm_job_byt_count_0_t;

static inline uint64_t BDK_REEX_AF_REEXM_JOB_BYT_COUNT_0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_JOB_BYT_COUNT_0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080a0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_JOB_BYT_COUNT_0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_0(a) bdk_reex_af_reexm_job_byt_count_0_t
#define bustype_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_0(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_0(a) "REEX_AF_REEXM_JOB_BYT_COUNT_0"
#define device_bar_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_0(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_0(a) (a)
#define arguments_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_0(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_job_byt_count_1
 *
 * REE AF REEX Main Job Byte Count MSB Register
 */
union bdk_reex_af_reexm_job_byt_count_1
{
    uint64_t u;
    struct bdk_reex_af_reexm_job_byt_count_1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Total number of job data bytes parsed, 32 higher bits.  Wraps around. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Total number of job data bytes parsed, 32 higher bits.  Wraps around. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_job_byt_count_1_s cn; */
};
typedef union bdk_reex_af_reexm_job_byt_count_1 bdk_reex_af_reexm_job_byt_count_1_t;

static inline uint64_t BDK_REEX_AF_REEXM_JOB_BYT_COUNT_1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_JOB_BYT_COUNT_1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080a8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_JOB_BYT_COUNT_1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_1(a) bdk_reex_af_reexm_job_byt_count_1_t
#define bustype_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_1(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_1(a) "REEX_AF_REEXM_JOB_BYT_COUNT_1"
#define device_bar_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_1(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_1(a) (a)
#define arguments_BDK_REEX_AF_REEXM_JOB_BYT_COUNT_1(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_job_count
 *
 * REE AF REEX Main Job Count Register
 */
union bdk_reex_af_reexm_job_count
{
    uint64_t u;
    struct bdk_reex_af_reexm_job_count_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Number of valid jobs ingressed. Wraps around. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Number of valid jobs ingressed. Wraps around. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_job_count_s cn; */
};
typedef union bdk_reex_af_reexm_job_count bdk_reex_af_reexm_job_count_t;

static inline uint64_t BDK_REEX_AF_REEXM_JOB_COUNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_JOB_COUNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008090ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_JOB_COUNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_JOB_COUNT(a) bdk_reex_af_reexm_job_count_t
#define bustype_BDK_REEX_AF_REEXM_JOB_COUNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_JOB_COUNT(a) "REEX_AF_REEXM_JOB_COUNT"
#define device_bar_BDK_REEX_AF_REEXM_JOB_COUNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_JOB_COUNT(a) (a)
#define arguments_BDK_REEX_AF_REEXM_JOB_COUNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_match_count
 *
 * REE AF REEX Main Match Count Register
 */
union bdk_reex_af_reexm_match_count
{
    uint64_t u;
    struct bdk_reex_af_reexm_match_count_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Total number of matches detected.  Wraps around. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Total number of matches detected.  Wraps around. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_match_count_s cn; */
};
typedef union bdk_reex_af_reexm_match_count bdk_reex_af_reexm_match_count_t;

static inline uint64_t BDK_REEX_AF_REEXM_MATCH_COUNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_MATCH_COUNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080b8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_MATCH_COUNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_MATCH_COUNT(a) bdk_reex_af_reexm_match_count_t
#define bustype_BDK_REEX_AF_REEXM_MATCH_COUNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_MATCH_COUNT(a) "REEX_AF_REEXM_MATCH_COUNT"
#define device_bar_BDK_REEX_AF_REEXM_MATCH_COUNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_MATCH_COUNT(a) (a)
#define arguments_BDK_REEX_AF_REEXM_MATCH_COUNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_max_latency_cnt
 *
 * REE AF REEX Main Max Latency Count Register
 */
union bdk_reex_af_reexm_max_latency_cnt
{
    uint64_t u;
    struct bdk_reex_af_reexm_max_latency_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t reex_reserved_1       : 16; /**< [ 31: 16](R/W) Reserved. */
        uint64_t count                 : 16; /**< [ 15:  0](R/W) Maximum LATENCY_COUNT value per job before primary threads are aborted.
                                                                 Use this as a proxy for providing an upper bound on job latency.
                                                                 This register indicates a target maximum latency, but actual LATENCY_COUNT
                                                                 value returned for a job can be bigger due to house-keeping overheads.
                                                                 Range 0 to 65535, value 0 means unlimited.
                                                                 If maximum has been reached, MAX_LATENCY_COUNT_DETECTED is asserted and further threads aborted. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 16; /**< [ 15:  0](R/W) Maximum LATENCY_COUNT value per job before primary threads are aborted.
                                                                 Use this as a proxy for providing an upper bound on job latency.
                                                                 This register indicates a target maximum latency, but actual LATENCY_COUNT
                                                                 value returned for a job can be bigger due to house-keeping overheads.
                                                                 Range 0 to 65535, value 0 means unlimited.
                                                                 If maximum has been reached, MAX_LATENCY_COUNT_DETECTED is asserted and further threads aborted. */
        uint64_t reex_reserved_1       : 16; /**< [ 31: 16](R/W) Reserved. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_max_latency_cnt_s cn; */
};
typedef union bdk_reex_af_reexm_max_latency_cnt bdk_reex_af_reexm_max_latency_cnt_t;

static inline uint64_t BDK_REEX_AF_REEXM_MAX_LATENCY_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_MAX_LATENCY_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080e0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_MAX_LATENCY_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_MAX_LATENCY_CNT(a) bdk_reex_af_reexm_max_latency_cnt_t
#define bustype_BDK_REEX_AF_REEXM_MAX_LATENCY_CNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_MAX_LATENCY_CNT(a) "REEX_AF_REEXM_MAX_LATENCY_CNT"
#define device_bar_BDK_REEX_AF_REEXM_MAX_LATENCY_CNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_MAX_LATENCY_CNT(a) (a)
#define arguments_BDK_REEX_AF_REEXM_MAX_LATENCY_CNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_max_match
 *
 * REE AF REEX Main Max MATCH Register
 */
union bdk_reex_af_reexm_max_match
{
    uint64_t u;
    struct bdk_reex_af_reexm_max_match_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t max                   : 8;  /**< [  7:  0](R/W) Maximum number of matches to return per job.
                                                                 Once this number of matches have been found, no further primary threads
                                                                 are generated for the job (returned matches are not necessarily lowest start_ptr).
                                                                 Range 0 to 254 (includes saturation logic), value 0 means no matches are returned.
                                                                 If maximum has been reached, MAX_MATCH_COUNT_DETECTED is asserted and further threads aborted. */
#else /* Word 0 - Little Endian */
        uint64_t max                   : 8;  /**< [  7:  0](R/W) Maximum number of matches to return per job.
                                                                 Once this number of matches have been found, no further primary threads
                                                                 are generated for the job (returned matches are not necessarily lowest start_ptr).
                                                                 Range 0 to 254 (includes saturation logic), value 0 means no matches are returned.
                                                                 If maximum has been reached, MAX_MATCH_COUNT_DETECTED is asserted and further threads aborted. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_max_match_s cn; */
};
typedef union bdk_reex_af_reexm_max_match bdk_reex_af_reexm_max_match_t;

static inline uint64_t BDK_REEX_AF_REEXM_MAX_MATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_MAX_MATCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080c8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_MAX_MATCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_MAX_MATCH(a) bdk_reex_af_reexm_max_match_t
#define bustype_BDK_REEX_AF_REEXM_MAX_MATCH(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_MAX_MATCH(a) "REEX_AF_REEXM_MAX_MATCH"
#define device_bar_BDK_REEX_AF_REEXM_MAX_MATCH(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_MAX_MATCH(a) (a)
#define arguments_BDK_REEX_AF_REEXM_MAX_MATCH(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_max_pre_cnt
 *
 * REE AF REEX Main Max Prefix Count Register
 */
union bdk_reex_af_reexm_max_pre_cnt
{
    uint64_t u;
    struct bdk_reex_af_reexm_max_pre_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t count                 : 10; /**< [  9:  0](R/W) Maximum number of prefixes detected per job that are converted to thread searches.
                                                                 Use this as a proxy for denial of service detection.
                                                                 Range 0 to 1008 (includes saturation logic), value 0 means no matches are returned.
                                                                 If maximum has been reached, MAX_PREFIX_COUNT_DETECTED is asserted and further threads aborted. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 10; /**< [  9:  0](R/W) Maximum number of prefixes detected per job that are converted to thread searches.
                                                                 Use this as a proxy for denial of service detection.
                                                                 Range 0 to 1008 (includes saturation logic), value 0 means no matches are returned.
                                                                 If maximum has been reached, MAX_PREFIX_COUNT_DETECTED is asserted and further threads aborted. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_max_pre_cnt_s cn; */
};
typedef union bdk_reex_af_reexm_max_pre_cnt bdk_reex_af_reexm_max_pre_cnt_t;

static inline uint64_t BDK_REEX_AF_REEXM_MAX_PRE_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_MAX_PRE_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080d0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_MAX_PRE_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_MAX_PRE_CNT(a) bdk_reex_af_reexm_max_pre_cnt_t
#define bustype_BDK_REEX_AF_REEXM_MAX_PRE_CNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_MAX_PRE_CNT(a) "REEX_AF_REEXM_MAX_PRE_CNT"
#define device_bar_BDK_REEX_AF_REEXM_MAX_PRE_CNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_MAX_PRE_CNT(a) (a)
#define arguments_BDK_REEX_AF_REEXM_MAX_PRE_CNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_max_pthread_cnt
 *
 * REE AF REEX Main Max Primary Thread Count Register
 */
union bdk_reex_af_reexm_max_pthread_cnt
{
    uint64_t u;
    struct bdk_reex_af_reexm_max_pthread_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t reex_reserved_1       : 16; /**< [ 31: 16](R/W) Reserved. */
        uint64_t count                 : 16; /**< [ 15:  0](R/W) Maximum number of primary threads per job. Range 0 to 65535, value 0 means unlimited.
                                                                 If maximum has been reached, MAX_PRIMARY_THREAD_COUNT_DETECTED is asserted and
                                                                 further threads aborted. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 16; /**< [ 15:  0](R/W) Maximum number of primary threads per job. Range 0 to 65535, value 0 means unlimited.
                                                                 If maximum has been reached, MAX_PRIMARY_THREAD_COUNT_DETECTED is asserted and
                                                                 further threads aborted. */
        uint64_t reex_reserved_1       : 16; /**< [ 31: 16](R/W) Reserved. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_max_pthread_cnt_s cn; */
};
typedef union bdk_reex_af_reexm_max_pthread_cnt bdk_reex_af_reexm_max_pthread_cnt_t;

static inline uint64_t BDK_REEX_AF_REEXM_MAX_PTHREAD_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_MAX_PTHREAD_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080d8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_MAX_PTHREAD_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_MAX_PTHREAD_CNT(a) bdk_reex_af_reexm_max_pthread_cnt_t
#define bustype_BDK_REEX_AF_REEXM_MAX_PTHREAD_CNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_MAX_PTHREAD_CNT(a) "REEX_AF_REEXM_MAX_PTHREAD_CNT"
#define device_bar_BDK_REEX_AF_REEXM_MAX_PTHREAD_CNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_MAX_PTHREAD_CNT(a) (a)
#define arguments_BDK_REEX_AF_REEXM_MAX_PTHREAD_CNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_response_count
 *
 * REE AF REEX Main Response Descriptor Count Register
 */
union bdk_reex_af_reexm_response_count
{
    uint64_t u;
    struct bdk_reex_af_reexm_response_count_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Total number of response descriptors dispatched.  Wraps around. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Total number of response descriptors dispatched.  Wraps around. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_response_count_s cn; */
};
typedef union bdk_reex_af_reexm_response_count bdk_reex_af_reexm_response_count_t;

static inline uint64_t BDK_REEX_AF_REEXM_RESPONSE_COUNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_RESPONSE_COUNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080b0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_RESPONSE_COUNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_RESPONSE_COUNT(a) bdk_reex_af_reexm_response_count_t
#define bustype_BDK_REEX_AF_REEXM_RESPONSE_COUNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_RESPONSE_COUNT(a) "REEX_AF_REEXM_RESPONSE_COUNT"
#define device_bar_BDK_REEX_AF_REEXM_RESPONSE_COUNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_RESPONSE_COUNT(a) (a)
#define arguments_BDK_REEX_AF_REEXM_RESPONSE_COUNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_revision
 *
 * REE AF REEX Main Revision Register
 * This register contains capability information about REEX.
 */
union bdk_reex_af_reexm_revision
{
    uint64_t u;
    struct bdk_reex_af_reexm_revision_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t rev                   : 32; /**< [ 31:  0](RO) Subversion revision number. Value is drop specific. */
#else /* Word 0 - Little Endian */
        uint64_t rev                   : 32; /**< [ 31:  0](RO) Subversion revision number. Value is drop specific. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_revision_s cn; */
};
typedef union bdk_reex_af_reexm_revision bdk_reex_af_reexm_revision_t;

static inline uint64_t BDK_REEX_AF_REEXM_REVISION(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_REVISION(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008008ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_REVISION", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_REVISION(a) bdk_reex_af_reexm_revision_t
#define bustype_BDK_REEX_AF_REEXM_REVISION(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_REVISION(a) "REEX_AF_REEXM_REVISION"
#define device_bar_BDK_REEX_AF_REEXM_REVISION(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_REVISION(a) (a)
#define arguments_BDK_REEX_AF_REEXM_REVISION(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_scratch
 *
 * REE AF REEX Main Scratch Register
 */
union bdk_reex_af_reexm_scratch
{
    uint64_t u;
    struct bdk_reex_af_reexm_scratch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t scratch               : 32; /**< [ 31:  0](R/W) Scratch register, for SW use only (ignored by REEX). */
#else /* Word 0 - Little Endian */
        uint64_t scratch               : 32; /**< [ 31:  0](R/W) Scratch register, for SW use only (ignored by REEX). */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_scratch_s cn; */
};
typedef union bdk_reex_af_reexm_scratch bdk_reex_af_reexm_scratch_t;

static inline uint64_t BDK_REEX_AF_REEXM_SCRATCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_SCRATCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400080e8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_SCRATCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_SCRATCH(a) bdk_reex_af_reexm_scratch_t
#define bustype_BDK_REEX_AF_REEXM_SCRATCH(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_SCRATCH(a) "REEX_AF_REEXM_SCRATCH"
#define device_bar_BDK_REEX_AF_REEXM_SCRATCH(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_SCRATCH(a) (a)
#define arguments_BDK_REEX_AF_REEXM_SCRATCH(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexm_status
 *
 * REE AF REEX Main Status Register
 */
union bdk_reex_af_reexm_status
{
    uint64_t u;
    struct bdk_reex_af_reexm_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t idle                  : 1;  /**< [  6:  6](RO/H) --
                                                                 Internal:
                                                                 Indicates that there are no jobs in REEX (for debug) */
        uint64_t reserved_4_5          : 2;
        uint64_t going                 : 1;  /**< [  3:  3](RO/H) --
                                                                 Internal:
                                                                 Indicates that one or more jobs are in REEX (for debug) */
        uint64_t reserved_1_2          : 2;
        uint64_t init_done             : 1;  /**< [  0:  0](RO/H) After software sets and clears REEXM_CTRL[INIT], it must poll [INIT_DONE] until
                                                                 set, which indicates REEX has been initialized. */
#else /* Word 0 - Little Endian */
        uint64_t init_done             : 1;  /**< [  0:  0](RO/H) After software sets and clears REEXM_CTRL[INIT], it must poll [INIT_DONE] until
                                                                 set, which indicates REEX has been initialized. */
        uint64_t reserved_1_2          : 2;
        uint64_t going                 : 1;  /**< [  3:  3](RO/H) --
                                                                 Internal:
                                                                 Indicates that one or more jobs are in REEX (for debug) */
        uint64_t reserved_4_5          : 2;
        uint64_t idle                  : 1;  /**< [  6:  6](RO/H) --
                                                                 Internal:
                                                                 Indicates that there are no jobs in REEX (for debug) */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexm_status_s cn; */
};
typedef union bdk_reex_af_reexm_status bdk_reex_af_reexm_status_t;

static inline uint64_t BDK_REEX_AF_REEXM_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXM_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008050ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXM_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXM_STATUS(a) bdk_reex_af_reexm_status_t
#define bustype_BDK_REEX_AF_REEXM_STATUS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXM_STATUS(a) "REEX_AF_REEXM_STATUS"
#define device_bar_BDK_REEX_AF_REEXM_STATUS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXM_STATUS(a) (a)
#define arguments_BDK_REEX_AF_REEXM_STATUS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_capability
 *
 * REE AF REEX RTRU Capability Register
 * This register contains capability information about REEX.
 */
union bdk_reex_af_reexr_capability
{
    uint64_t u;
    struct bdk_reex_af_reexr_capability_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t rtru_fifo_width       : 16; /**< [ 31: 16](RO) RTRU FIFO data width. */
        uint64_t rtru_fifo_depth       : 16; /**< [ 15:  0](RO) RTRU FIFO maximum legal number of entries. */
#else /* Word 0 - Little Endian */
        uint64_t rtru_fifo_depth       : 16; /**< [ 15:  0](RO) RTRU FIFO maximum legal number of entries. */
        uint64_t rtru_fifo_width       : 16; /**< [ 31: 16](RO) RTRU FIFO data width. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_capability_s cn; */
};
typedef union bdk_reex_af_reexr_capability bdk_reex_af_reexr_capability_t;

static inline uint64_t BDK_REEX_AF_REEXR_CAPABILITY(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_CAPABILITY(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008210ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_CAPABILITY", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_CAPABILITY(a) bdk_reex_af_reexr_capability_t
#define bustype_BDK_REEX_AF_REEXR_CAPABILITY(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_CAPABILITY(a) "REEX_AF_REEXR_CAPABILITY"
#define device_bar_BDK_REEX_AF_REEXR_CAPABILITY(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_CAPABILITY(a) (a)
#define arguments_BDK_REEX_AF_REEXR_CAPABILITY(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_ck_sum_0
 *
 * REE AF REEX RTRU Checksum 0 Register
 * This register contains address checksum value.
 */
union bdk_reex_af_reexr_ck_sum_0
{
    uint64_t u;
    struct bdk_reex_af_reexr_ck_sum_0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t value                 : 32; /**< [ 31:  0](RO/H) RTRU address checksum value. */
#else /* Word 0 - Little Endian */
        uint64_t value                 : 32; /**< [ 31:  0](RO/H) RTRU address checksum value. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_ck_sum_0_s cn; */
};
typedef union bdk_reex_af_reexr_ck_sum_0 bdk_reex_af_reexr_ck_sum_0_t;

static inline uint64_t BDK_REEX_AF_REEXR_CK_SUM_0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_CK_SUM_0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008280ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_CK_SUM_0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_CK_SUM_0(a) bdk_reex_af_reexr_ck_sum_0_t
#define bustype_BDK_REEX_AF_REEXR_CK_SUM_0(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_CK_SUM_0(a) "REEX_AF_REEXR_CK_SUM_0"
#define device_bar_BDK_REEX_AF_REEXR_CK_SUM_0(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_CK_SUM_0(a) (a)
#define arguments_BDK_REEX_AF_REEXR_CK_SUM_0(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_ck_sum_1
 *
 * REE AF REEX RTRU Checksum 1 Register
 * This register contains data[31:0] checksum value.
 */
union bdk_reex_af_reexr_ck_sum_1
{
    uint64_t u;
    struct bdk_reex_af_reexr_ck_sum_1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t value                 : 32; /**< [ 31:  0](RO/H) Data\<31:0\> checksum value. */
#else /* Word 0 - Little Endian */
        uint64_t value                 : 32; /**< [ 31:  0](RO/H) Data\<31:0\> checksum value. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_ck_sum_1_s cn; */
};
typedef union bdk_reex_af_reexr_ck_sum_1 bdk_reex_af_reexr_ck_sum_1_t;

static inline uint64_t BDK_REEX_AF_REEXR_CK_SUM_1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_CK_SUM_1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008288ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_CK_SUM_1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_CK_SUM_1(a) bdk_reex_af_reexr_ck_sum_1_t
#define bustype_BDK_REEX_AF_REEXR_CK_SUM_1(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_CK_SUM_1(a) "REEX_AF_REEXR_CK_SUM_1"
#define device_bar_BDK_REEX_AF_REEXR_CK_SUM_1(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_CK_SUM_1(a) (a)
#define arguments_BDK_REEX_AF_REEXR_CK_SUM_1(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_ck_sum_2
 *
 * REE AF REEX RTRU Checksum 2 Register
 * This register contains data[63:32] checksum value.
 */
union bdk_reex_af_reexr_ck_sum_2
{
    uint64_t u;
    struct bdk_reex_af_reexr_ck_sum_2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t value                 : 32; /**< [ 31:  0](RO/H) Data[63:32] checksum value. */
#else /* Word 0 - Little Endian */
        uint64_t value                 : 32; /**< [ 31:  0](RO/H) Data[63:32] checksum value. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_ck_sum_2_s cn; */
};
typedef union bdk_reex_af_reexr_ck_sum_2 bdk_reex_af_reexr_ck_sum_2_t;

static inline uint64_t BDK_REEX_AF_REEXR_CK_SUM_2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_CK_SUM_2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008290ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_CK_SUM_2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_CK_SUM_2(a) bdk_reex_af_reexr_ck_sum_2_t
#define bustype_BDK_REEX_AF_REEXR_CK_SUM_2(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_CK_SUM_2(a) "REEX_AF_REEXR_CK_SUM_2"
#define device_bar_BDK_REEX_AF_REEXR_CK_SUM_2(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_CK_SUM_2(a) (a)
#define arguments_BDK_REEX_AF_REEXR_CK_SUM_2(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_ctrl
 *
 * REE AF REEX RTRU Control Register
 * This register controls the REEX programming plane.
 */
union bdk_reex_af_reexr_ctrl
{
    uint64_t u;
    struct bdk_reex_af_reexr_ctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t reex_reserved_2       : 26; /**< [ 31:  6](R/W) Reserved, keep 0. */
        uint64_t init_mode             : 2;  /**< [  5:  4](R/W) Init mode regarding memories.
                                                                 Internal:
                                                                 First init value should be 0x1, and change to 0x2 for further inits.
                                                                 Modes 0x0 and 0x3 are not supported by REE. */
        uint64_t reex_reserved_1       : 2;  /**< [  3:  2](R/W) Reserved, keep 0. */
        uint64_t go                    : 1;  /**< [  1:  1](R/W) GO. */
        uint64_t init                  : 1;  /**< [  0:  0](R/W) Initialize REEX. */
#else /* Word 0 - Little Endian */
        uint64_t init                  : 1;  /**< [  0:  0](R/W) Initialize REEX. */
        uint64_t go                    : 1;  /**< [  1:  1](R/W) GO. */
        uint64_t reex_reserved_1       : 2;  /**< [  3:  2](R/W) Reserved, keep 0. */
        uint64_t init_mode             : 2;  /**< [  5:  4](R/W) Init mode regarding memories.
                                                                 Internal:
                                                                 First init value should be 0x1, and change to 0x2 for further inits.
                                                                 Modes 0x0 and 0x3 are not supported by REE. */
        uint64_t reex_reserved_2       : 26; /**< [ 31:  6](R/W) Reserved, keep 0. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_ctrl_s cn; */
};
typedef union bdk_reex_af_reexr_ctrl bdk_reex_af_reexr_ctrl_t;

static inline uint64_t BDK_REEX_AF_REEXR_CTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_CTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400082c0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_CTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_CTRL(a) bdk_reex_af_reexr_ctrl_t
#define bustype_BDK_REEX_AF_REEXR_CTRL(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_CTRL(a) "REEX_AF_REEXR_CTRL"
#define device_bar_BDK_REEX_AF_REEXR_CTRL(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_CTRL(a) (a)
#define arguments_BDK_REEX_AF_REEXR_CTRL(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_dscrd_count
 *
 * REE AF REEX RTRU Discarded Entries Count Register
 * This register contains number of discarded entries read from RTRU_FIFO,
 * as they targeted EM (write path to EM is not enabled).
 */
union bdk_reex_af_reexr_dscrd_count
{
    uint64_t u;
    struct bdk_reex_af_reexr_dscrd_count_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Discarded RTRU entries count. Saturates at 32'hffffffff. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Discarded RTRU entries count. Saturates at 32'hffffffff. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_dscrd_count_s cn; */
};
typedef union bdk_reex_af_reexr_dscrd_count bdk_reex_af_reexr_dscrd_count_t;

static inline uint64_t BDK_REEX_AF_REEXR_DSCRD_COUNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_DSCRD_COUNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400082a0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_DSCRD_COUNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_DSCRD_COUNT(a) bdk_reex_af_reexr_dscrd_count_t
#define bustype_BDK_REEX_AF_REEXR_DSCRD_COUNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_DSCRD_COUNT(a) "REEX_AF_REEXR_DSCRD_COUNT"
#define device_bar_BDK_REEX_AF_REEXR_DSCRD_COUNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_DSCRD_COUNT(a) (a)
#define arguments_BDK_REEX_AF_REEXR_DSCRD_COUNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_fifo_status
 *
 * REE AF REEX RTRU FIFO Status Register
 * This register contains status information about RTRU.
 */
union bdk_reex_af_reexr_fifo_status
{
    uint64_t u;
    struct bdk_reex_af_reexr_fifo_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t num_entries           : 16; /**< [ 15:  0](RO/H) Fill level of the RTRU FIFO. */
#else /* Word 0 - Little Endian */
        uint64_t num_entries           : 16; /**< [ 15:  0](RO/H) Fill level of the RTRU FIFO. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_fifo_status_s cn; */
};
typedef union bdk_reex_af_reexr_fifo_status bdk_reex_af_reexr_fifo_status_t;

static inline uint64_t BDK_REEX_AF_REEXR_FIFO_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_FIFO_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008258ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_FIFO_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_FIFO_STATUS(a) bdk_reex_af_reexr_fifo_status_t
#define bustype_BDK_REEX_AF_REEXR_FIFO_STATUS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_FIFO_STATUS(a) "REEX_AF_REEXR_FIFO_STATUS"
#define device_bar_BDK_REEX_AF_REEXR_FIFO_STATUS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_FIFO_STATUS(a) (a)
#define arguments_BDK_REEX_AF_REEXR_FIFO_STATUS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_rof_metadata
 *
 * REE AF REEX RTRU Metadata Register
 * Metadata value.
 */
union bdk_reex_af_reexr_rof_metadata
{
    uint64_t u;
    struct bdk_reex_af_reexr_rof_metadata_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t metadata              : 32; /**< [ 31:  0](RO/H) Metadata value embedded in rules memories (T2.0).
                                                                 This could indicate PTPB, but if PTPB gets deprecated as it is less relevant
                                                                 for bi-directional walk support, it could be populated with user-specified value.
                                                                 Value change - same behavior as ROF_REVISION above. */
#else /* Word 0 - Little Endian */
        uint64_t metadata              : 32; /**< [ 31:  0](RO/H) Metadata value embedded in rules memories (T2.0).
                                                                 This could indicate PTPB, but if PTPB gets deprecated as it is less relevant
                                                                 for bi-directional walk support, it could be populated with user-specified value.
                                                                 Value change - same behavior as ROF_REVISION above. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_rof_metadata_s cn; */
};
typedef union bdk_reex_af_reexr_rof_metadata bdk_reex_af_reexr_rof_metadata_t;

static inline uint64_t BDK_REEX_AF_REEXR_ROF_METADATA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_ROF_METADATA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400082b8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_ROF_METADATA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_ROF_METADATA(a) bdk_reex_af_reexr_rof_metadata_t
#define bustype_BDK_REEX_AF_REEXR_ROF_METADATA(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_ROF_METADATA(a) "REEX_AF_REEXR_ROF_METADATA"
#define device_bar_BDK_REEX_AF_REEXR_ROF_METADATA(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_ROF_METADATA(a) (a)
#define arguments_BDK_REEX_AF_REEXR_ROF_METADATA(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_rof_revision
 *
 * REE AF REEX RTRU Revision Register
 * Revision number.
 */
union bdk_reex_af_reexr_rof_revision
{
    uint64_t u;
    struct bdk_reex_af_reexr_rof_revision_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t revision              : 32; /**< [ 31:  0](RO) Revision value embedded in rules memories.
                                                                 It can change if there is a non-zero entry for a specific address is inserted in
                                                                 the ROF file and written to the rules memories. */
#else /* Word 0 - Little Endian */
        uint64_t revision              : 32; /**< [ 31:  0](RO) Revision value embedded in rules memories.
                                                                 It can change if there is a non-zero entry for a specific address is inserted in
                                                                 the ROF file and written to the rules memories. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_rof_revision_s cn; */
};
typedef union bdk_reex_af_reexr_rof_revision bdk_reex_af_reexr_rof_revision_t;

static inline uint64_t BDK_REEX_AF_REEXR_ROF_REVISION(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_ROF_REVISION(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400082b0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_ROF_REVISION", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_ROF_REVISION(a) bdk_reex_af_reexr_rof_revision_t
#define bustype_BDK_REEX_AF_REEXR_ROF_REVISION(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_ROF_REVISION(a) "REEX_AF_REEXR_ROF_REVISION"
#define device_bar_BDK_REEX_AF_REEXR_ROF_REVISION(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_ROF_REVISION(a) (a)
#define arguments_BDK_REEX_AF_REEXR_ROF_REVISION(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_rtru_count
 *
 * REE AF REEX RTRU Count Register
 * Number of completed RTRUs.
 */
union bdk_reex_af_reexr_rtru_count
{
    uint64_t u;
    struct bdk_reex_af_reexr_rtru_count_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Number of completed RTRUs. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 32; /**< [ 31:  0](RO/H) Number of completed RTRUs. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_rtru_count_s cn; */
};
typedef union bdk_reex_af_reexr_rtru_count bdk_reex_af_reexr_rtru_count_t;

static inline uint64_t BDK_REEX_AF_REEXR_RTRU_COUNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_RTRU_COUNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400082a8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_RTRU_COUNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_RTRU_COUNT(a) bdk_reex_af_reexr_rtru_count_t
#define bustype_BDK_REEX_AF_REEXR_RTRU_COUNT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_RTRU_COUNT(a) "REEX_AF_REEXR_RTRU_COUNT"
#define device_bar_BDK_REEX_AF_REEXR_RTRU_COUNT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_RTRU_COUNT(a) (a)
#define arguments_BDK_REEX_AF_REEXR_RTRU_COUNT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexr_status
 *
 * REE AF REEX RTRU Status Register
 * This register contains status information about RTRU.
 */
union bdk_reex_af_reexr_status
{
    uint64_t u;
    struct bdk_reex_af_reexr_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t em_init_done          : 1;  /**< [  7:  7](RO/H) Asserted if External memory initialization is complete. */
        uint64_t l2_cache_init_done    : 1;  /**< [  6:  6](RO/H) Asserted if REEX L2 cache initialization is complete. */
        uint64_t l1_cache_init_done    : 1;  /**< [  5:  5](RO/H) Asserted if REEX L1 cache initialization is complete. */
        uint64_t im_init_done          : 1;  /**< [  4:  4](RO/H) Asserted if REEX Internal memory initialization is complete. */
        uint64_t reserved_2_3          : 2;
        uint64_t update_done           : 1;  /**< [  1:  1](RO/H) Asserted if rules update transaction is complete. */
        uint64_t update_req            : 1;  /**< [  0:  0](RO/H) Update required is asserted if a rules update is required i.e. one or more
                                                                 values have been written to the RTRU FIFO. */
#else /* Word 0 - Little Endian */
        uint64_t update_req            : 1;  /**< [  0:  0](RO/H) Update required is asserted if a rules update is required i.e. one or more
                                                                 values have been written to the RTRU FIFO. */
        uint64_t update_done           : 1;  /**< [  1:  1](RO/H) Asserted if rules update transaction is complete. */
        uint64_t reserved_2_3          : 2;
        uint64_t im_init_done          : 1;  /**< [  4:  4](RO/H) Asserted if REEX Internal memory initialization is complete. */
        uint64_t l1_cache_init_done    : 1;  /**< [  5:  5](RO/H) Asserted if REEX L1 cache initialization is complete. */
        uint64_t l2_cache_init_done    : 1;  /**< [  6:  6](RO/H) Asserted if REEX L2 cache initialization is complete. */
        uint64_t em_init_done          : 1;  /**< [  7:  7](RO/H) Asserted if External memory initialization is complete. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexr_status_s cn; */
};
typedef union bdk_reex_af_reexr_status bdk_reex_af_reexr_status_t;

static inline uint64_t BDK_REEX_AF_REEXR_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXR_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008250ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXR_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXR_STATUS(a) bdk_reex_af_reexr_status_t
#define bustype_BDK_REEX_AF_REEXR_STATUS(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXR_STATUS(a) "REEX_AF_REEXR_STATUS"
#define device_bar_BDK_REEX_AF_REEXR_STATUS(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXR_STATUS(a) (a)
#define arguments_BDK_REEX_AF_REEXR_STATUS(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_cluster_0
 *
 * REE AF REEX STAT CLUSTER_0 Register
 * Statistics for REEX cluster 0.
 */
union bdk_reex_af_reexs_cluster_0
{
    uint64_t u;
    struct bdk_reex_af_reexs_cluster_0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_cluster_0_s cn; */
};
typedef union bdk_reex_af_reexs_cluster_0 bdk_reex_af_reexs_cluster_0_t;

static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008400ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_CLUSTER_0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_CLUSTER_0(a) bdk_reex_af_reexs_cluster_0_t
#define bustype_BDK_REEX_AF_REEXS_CLUSTER_0(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_CLUSTER_0(a) "REEX_AF_REEXS_CLUSTER_0"
#define device_bar_BDK_REEX_AF_REEXS_CLUSTER_0(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_CLUSTER_0(a) (a)
#define arguments_BDK_REEX_AF_REEXS_CLUSTER_0(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_cluster_1
 *
 * REE AF REEX STAT CLUSTER_1 Register
 * Statistics for REEX cluster 1.
 */
union bdk_reex_af_reexs_cluster_1
{
    uint64_t u;
    struct bdk_reex_af_reexs_cluster_1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_cluster_1_s cn; */
};
typedef union bdk_reex_af_reexs_cluster_1 bdk_reex_af_reexs_cluster_1_t;

static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008408ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_CLUSTER_1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_CLUSTER_1(a) bdk_reex_af_reexs_cluster_1_t
#define bustype_BDK_REEX_AF_REEXS_CLUSTER_1(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_CLUSTER_1(a) "REEX_AF_REEXS_CLUSTER_1"
#define device_bar_BDK_REEX_AF_REEXS_CLUSTER_1(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_CLUSTER_1(a) (a)
#define arguments_BDK_REEX_AF_REEXS_CLUSTER_1(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_cluster_2
 *
 * REE AF REEX STAT CLUSTER_2 Register
 * Statistics for REEX cluster 2.
 */
union bdk_reex_af_reexs_cluster_2
{
    uint64_t u;
    struct bdk_reex_af_reexs_cluster_2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_cluster_2_s cn; */
};
typedef union bdk_reex_af_reexs_cluster_2 bdk_reex_af_reexs_cluster_2_t;

static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008410ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_CLUSTER_2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_CLUSTER_2(a) bdk_reex_af_reexs_cluster_2_t
#define bustype_BDK_REEX_AF_REEXS_CLUSTER_2(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_CLUSTER_2(a) "REEX_AF_REEXS_CLUSTER_2"
#define device_bar_BDK_REEX_AF_REEXS_CLUSTER_2(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_CLUSTER_2(a) (a)
#define arguments_BDK_REEX_AF_REEXS_CLUSTER_2(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_cluster_3
 *
 * REE AF REEX STAT CLUSTER_3 Register
 * Statistics for REEX cluster 3.
 */
union bdk_reex_af_reexs_cluster_3
{
    uint64_t u;
    struct bdk_reex_af_reexs_cluster_3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_cluster_3_s cn; */
};
typedef union bdk_reex_af_reexs_cluster_3 bdk_reex_af_reexs_cluster_3_t;

static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008418ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_CLUSTER_3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_CLUSTER_3(a) bdk_reex_af_reexs_cluster_3_t
#define bustype_BDK_REEX_AF_REEXS_CLUSTER_3(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_CLUSTER_3(a) "REEX_AF_REEXS_CLUSTER_3"
#define device_bar_BDK_REEX_AF_REEXS_CLUSTER_3(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_CLUSTER_3(a) (a)
#define arguments_BDK_REEX_AF_REEXS_CLUSTER_3(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_cluster_4
 *
 * REE AF REEX STAT CLUSTER_4 Register
 * Statistics for REEX cluster 4.
 */
union bdk_reex_af_reexs_cluster_4
{
    uint64_t u;
    struct bdk_reex_af_reexs_cluster_4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_cluster_4_s cn; */
};
typedef union bdk_reex_af_reexs_cluster_4 bdk_reex_af_reexs_cluster_4_t;

static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008420ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_CLUSTER_4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_CLUSTER_4(a) bdk_reex_af_reexs_cluster_4_t
#define bustype_BDK_REEX_AF_REEXS_CLUSTER_4(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_CLUSTER_4(a) "REEX_AF_REEXS_CLUSTER_4"
#define device_bar_BDK_REEX_AF_REEXS_CLUSTER_4(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_CLUSTER_4(a) (a)
#define arguments_BDK_REEX_AF_REEXS_CLUSTER_4(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_cluster_5
 *
 * REE AF REEX STAT CLUSTER_5 Register
 * Statistics for REEX cluster 5.
 */
union bdk_reex_af_reexs_cluster_5
{
    uint64_t u;
    struct bdk_reex_af_reexs_cluster_5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_cluster_5_s cn; */
};
typedef union bdk_reex_af_reexs_cluster_5 bdk_reex_af_reexs_cluster_5_t;

static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008428ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_CLUSTER_5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_CLUSTER_5(a) bdk_reex_af_reexs_cluster_5_t
#define bustype_BDK_REEX_AF_REEXS_CLUSTER_5(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_CLUSTER_5(a) "REEX_AF_REEXS_CLUSTER_5"
#define device_bar_BDK_REEX_AF_REEXS_CLUSTER_5(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_CLUSTER_5(a) (a)
#define arguments_BDK_REEX_AF_REEXS_CLUSTER_5(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_cluster_6
 *
 * REE AF REEX STAT CLUSTER_6 Register
 * Statistics for REEX cluster 6.
 */
union bdk_reex_af_reexs_cluster_6
{
    uint64_t u;
    struct bdk_reex_af_reexs_cluster_6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_cluster_6_s cn; */
};
typedef union bdk_reex_af_reexs_cluster_6 bdk_reex_af_reexs_cluster_6_t;

static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008430ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_CLUSTER_6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_CLUSTER_6(a) bdk_reex_af_reexs_cluster_6_t
#define bustype_BDK_REEX_AF_REEXS_CLUSTER_6(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_CLUSTER_6(a) "REEX_AF_REEXS_CLUSTER_6"
#define device_bar_BDK_REEX_AF_REEXS_CLUSTER_6(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_CLUSTER_6(a) (a)
#define arguments_BDK_REEX_AF_REEXS_CLUSTER_6(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_cluster_7
 *
 * REE AF REEX STAT CLUSTER_7 Register
 * Statistics for REEX cluster 7.
 */
union bdk_reex_af_reexs_cluster_7
{
    uint64_t u;
    struct bdk_reex_af_reexs_cluster_7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t jce_idle_1d           : 8;  /**< [  7:  0](RO/H) Each bit is asserted if associated JCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles. */
        uint64_t tce_idle_1d           : 8;  /**< [ 15:  8](RO/H) Each bit is asserted if associated TCE(7:0) was idle
                                                                 for the previous window block of 256 clock cycles.

                                                                 Internal:
                                                                 FIXME - Titan to fix, there are now 16 TCEs per cluster, but only 8 bits.
                                                                 Also, reset value might be wrong, Titan to update. */
        uint64_t hit_duty_cycle        : 8;  /**< [ 23: 16](RO/H) Number of clock cycles HIT was asserted in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t instruction_duty_cycle : 8; /**< [ 31: 24](RO/H) Number of instructions that were executed in the previous
                                                                 window block of 256 clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_cluster_7_s cn; */
};
typedef union bdk_reex_af_reexs_cluster_7 bdk_reex_af_reexs_cluster_7_t;

static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_CLUSTER_7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140008438ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_CLUSTER_7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_CLUSTER_7(a) bdk_reex_af_reexs_cluster_7_t
#define bustype_BDK_REEX_AF_REEXS_CLUSTER_7(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_CLUSTER_7(a) "REEX_AF_REEXS_CLUSTER_7"
#define device_bar_BDK_REEX_AF_REEXS_CLUSTER_7(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_CLUSTER_7(a) (a)
#define arguments_BDK_REEX_AF_REEXS_CLUSTER_7(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_dp
 *
 * REE AF REEX STAT DP Register
 * REEX statistics for data plane interface.
 */
union bdk_reex_af_reexs_dp
{
    uint64_t u;
    struct bdk_reex_af_reexs_dp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t mf_re_duty_cycle      : 8;  /**< [ 31: 24](RO/H) Number of clock cycles the MF was read from
                                                                 in previous window component of 256 clock cycles. */
        uint64_t rdf_re_duty_cycle     : 8;  /**< [ 23: 16](RO/H) Number of clock cycles the RDF was read from
                                                                 in previous window component of 256 clock cycles. */
        uint64_t jf_we_duty_cycle      : 8;  /**< [ 15:  8](RO/H) Number of clock cycles the JF was written to
                                                                 in previous window component of 256 clock cycles. */
        uint64_t jdf_we_duty_cycle     : 8;  /**< [  7:  0](RO/H) Number of clock cycles the JDF was written to
                                                                 in previous window component of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t jdf_we_duty_cycle     : 8;  /**< [  7:  0](RO/H) Number of clock cycles the JDF was written to
                                                                 in previous window component of 256 clock cycles. */
        uint64_t jf_we_duty_cycle      : 8;  /**< [ 15:  8](RO/H) Number of clock cycles the JF was written to
                                                                 in previous window component of 256 clock cycles. */
        uint64_t rdf_re_duty_cycle     : 8;  /**< [ 23: 16](RO/H) Number of clock cycles the RDF was read from
                                                                 in previous window component of 256 clock cycles. */
        uint64_t mf_re_duty_cycle      : 8;  /**< [ 31: 24](RO/H) Number of clock cycles the MF was read from
                                                                 in previous window component of 256 clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_dp_s cn; */
};
typedef union bdk_reex_af_reexs_dp bdk_reex_af_reexs_dp_t;

static inline uint64_t BDK_REEX_AF_REEXS_DP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_DP(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400084f8ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_DP", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_DP(a) bdk_reex_af_reexs_dp_t
#define bustype_BDK_REEX_AF_REEXS_DP(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_DP(a) "REEX_AF_REEXS_DP"
#define device_bar_BDK_REEX_AF_REEXS_DP(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_DP(a) (a)
#define arguments_BDK_REEX_AF_REEXS_DP(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_l2_cache
 *
 * REE AF REEX STAT L2_CACHE Register
 * Statistics for L2 Cache.
 */
union bdk_reex_af_reexs_l2_cache
{
    uint64_t u;
    struct bdk_reex_af_reexs_l2_cache_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t rd_pend_comp_fifo_fill : 8; /**< [ 31: 24](RO/H) Number of entries in the READ_PENDING_COMPLETION_FIFO */
        uint64_t req_fifo_fill         : 8;  /**< [ 23: 16](RO/H) Number of entries in the REQUEST_FIFO */
        uint64_t cache_miss_duty_cycle : 8;  /**< [ 15:  8](RO/H) Number of clock cycles in the MPFE detected an L2 cache miss in the
                                                                 previous window of 256 clock cycles. */
        uint64_t cache_hit_duty_cycle  : 8;  /**< [  7:  0](RO/H) Number of clock cycles in the MPFE detected an L2 cache hit in the
                                                                 previous window of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t cache_hit_duty_cycle  : 8;  /**< [  7:  0](RO/H) Number of clock cycles in the MPFE detected an L2 cache hit in the
                                                                 previous window of 256 clock cycles. */
        uint64_t cache_miss_duty_cycle : 8;  /**< [ 15:  8](RO/H) Number of clock cycles in the MPFE detected an L2 cache miss in the
                                                                 previous window of 256 clock cycles. */
        uint64_t req_fifo_fill         : 8;  /**< [ 23: 16](RO/H) Number of entries in the REQUEST_FIFO */
        uint64_t rd_pend_comp_fifo_fill : 8; /**< [ 31: 24](RO/H) Number of entries in the READ_PENDING_COMPLETION_FIFO */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_l2_cache_s cn; */
};
typedef union bdk_reex_af_reexs_l2_cache bdk_reex_af_reexs_l2_cache_t;

static inline uint64_t BDK_REEX_AF_REEXS_L2_CACHE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_L2_CACHE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400084c0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_L2_CACHE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_L2_CACHE(a) bdk_reex_af_reexs_l2_cache_t
#define bustype_BDK_REEX_AF_REEXS_L2_CACHE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_L2_CACHE(a) "REEX_AF_REEXS_L2_CACHE"
#define device_bar_BDK_REEX_AF_REEXS_L2_CACHE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_L2_CACHE(a) (a)
#define arguments_BDK_REEX_AF_REEXS_L2_CACHE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_reexs_pe
 *
 * REE AF REEX STAT PE Register
 * REEX statistics for PE.
 */
union bdk_reex_af_reexs_pe
{
    uint64_t u;
    struct bdk_reex_af_reexs_pe_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t pthread_valid_duty_cycle : 8;/**< [ 15:  8](RO/H) Number of clock cycles the PE dispatched a primary thread
                                                                 in the previous window component of 256 clock cycles. */
        uint64_t nd_duty_cycle         : 8;  /**< [  7:  0](RO/H) Number of clock cycles the PE received a new data word
                                                                 in the previous window component of 256 clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t nd_duty_cycle         : 8;  /**< [  7:  0](RO/H) Number of clock cycles the PE received a new data word
                                                                 in the previous window component of 256 clock cycles. */
        uint64_t pthread_valid_duty_cycle : 8;/**< [ 15:  8](RO/H) Number of clock cycles the PE dispatched a primary thread
                                                                 in the previous window component of 256 clock cycles. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_reexs_pe_s cn; */
};
typedef union bdk_reex_af_reexs_pe bdk_reex_af_reexs_pe_t;

static inline uint64_t BDK_REEX_AF_REEXS_PE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_REEXS_PE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x8401400084e0ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_REEXS_PE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_REEXS_PE(a) bdk_reex_af_reexs_pe_t
#define bustype_BDK_REEX_AF_REEXS_PE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_REEXS_PE(a) "REEX_AF_REEXS_PE"
#define device_bar_BDK_REEX_AF_REEXS_PE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_REEXS_PE(a) (a)
#define arguments_BDK_REEX_AF_REEXS_PE(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_rvu_int
 *
 * REE AF RVU Interrupt Register
 * This register contains RVU error interrupt summary bits.
 */
union bdk_reex_af_rvu_int
{
    uint64_t u;
    struct bdk_reex_af_rvu_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Unmapped slot. Received an I/O request to a VF/PF slot in BAR2 that is not
                                                                 reverse mapped to an LF. See REE_PRIV_LF()_CFG.

                                                                 Internal:
                                                                 A reverse lookup using REE_AF_RVU_LF_CFG_DEBUG will never set this bit. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Unmapped slot. Received an I/O request to a VF/PF slot in BAR2 that is not
                                                                 reverse mapped to an LF. See REE_PRIV_LF()_CFG.

                                                                 Internal:
                                                                 A reverse lookup using REE_AF_RVU_LF_CFG_DEBUG will never set this bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_rvu_int_s cn; */
};
typedef union bdk_reex_af_rvu_int bdk_reex_af_rvu_int_t;

static inline uint64_t BDK_REEX_AF_RVU_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RVU_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046000ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RVU_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RVU_INT(a) bdk_reex_af_rvu_int_t
#define bustype_BDK_REEX_AF_RVU_INT(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RVU_INT(a) "REEX_AF_RVU_INT"
#define device_bar_BDK_REEX_AF_RVU_INT(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RVU_INT(a) (a)
#define arguments_BDK_REEX_AF_RVU_INT(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_rvu_int_ena_w1c
 *
 * REE AF RVU Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_reex_af_rvu_int_ena_w1c
{
    uint64_t u;
    struct bdk_reex_af_rvu_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for REE_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using REE_AF_RVU_LF_CFG_DEBUG will never set this bit. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for REE_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using REE_AF_RVU_LF_CFG_DEBUG will never set this bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_rvu_int_ena_w1c_s cn; */
};
typedef union bdk_reex_af_rvu_int_ena_w1c bdk_reex_af_rvu_int_ena_w1c_t;

static inline uint64_t BDK_REEX_AF_RVU_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RVU_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046018ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RVU_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RVU_INT_ENA_W1C(a) bdk_reex_af_rvu_int_ena_w1c_t
#define bustype_BDK_REEX_AF_RVU_INT_ENA_W1C(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RVU_INT_ENA_W1C(a) "REEX_AF_RVU_INT_ENA_W1C"
#define device_bar_BDK_REEX_AF_RVU_INT_ENA_W1C(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RVU_INT_ENA_W1C(a) (a)
#define arguments_BDK_REEX_AF_RVU_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_rvu_int_ena_w1s
 *
 * REE AF RVU Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_reex_af_rvu_int_ena_w1s
{
    uint64_t u;
    struct bdk_reex_af_rvu_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for REE_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using REE_AF_RVU_LF_CFG_DEBUG will never set this bit. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for REE_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using REE_AF_RVU_LF_CFG_DEBUG will never set this bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_rvu_int_ena_w1s_s cn; */
};
typedef union bdk_reex_af_rvu_int_ena_w1s bdk_reex_af_rvu_int_ena_w1s_t;

static inline uint64_t BDK_REEX_AF_RVU_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RVU_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046010ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RVU_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RVU_INT_ENA_W1S(a) bdk_reex_af_rvu_int_ena_w1s_t
#define bustype_BDK_REEX_AF_RVU_INT_ENA_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RVU_INT_ENA_W1S(a) "REEX_AF_RVU_INT_ENA_W1S"
#define device_bar_BDK_REEX_AF_RVU_INT_ENA_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RVU_INT_ENA_W1S(a) (a)
#define arguments_BDK_REEX_AF_RVU_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_rvu_int_w1s
 *
 * REE AF RVU Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_reex_af_rvu_int_w1s
{
    uint64_t u;
    struct bdk_reex_af_rvu_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets REE_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using REE_AF_RVU_LF_CFG_DEBUG will never set this bit. */
#else /* Word 0 - Little Endian */
        uint64_t unmapped_slot         : 1;  /**< [  0:  0](R/W1S/H) Reads or sets REE_AF_RVU_INT[UNMAPPED_SLOT].
                                                                 Internal:
                                                                 A reverse lookup using REE_AF_RVU_LF_CFG_DEBUG will never set this bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_rvu_int_w1s_s cn; */
};
typedef union bdk_reex_af_rvu_int_w1s bdk_reex_af_rvu_int_w1s_t;

static inline uint64_t BDK_REEX_AF_RVU_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RVU_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140046008ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RVU_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RVU_INT_W1S(a) bdk_reex_af_rvu_int_w1s_t
#define bustype_BDK_REEX_AF_RVU_INT_W1S(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RVU_INT_W1S(a) "REEX_AF_RVU_INT_W1S"
#define device_bar_BDK_REEX_AF_RVU_INT_W1S(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RVU_INT_W1S(a) (a)
#define arguments_BDK_REEX_AF_RVU_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_rvu_lf_cfg_debug
 *
 * REE Privileged LF Configuration Debug Registers
 * This debug register allows software to look up the reverse mapping from VF/PF
 * slot to LF. The forward mapping is programmed with REE_PRIV_LF()_CFG.
 */
union bdk_reex_af_rvu_lf_cfg_debug
{
    uint64_t u;
    struct bdk_reex_af_rvu_lf_cfg_debug_s
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
    /* struct bdk_reex_af_rvu_lf_cfg_debug_s cn; */
};
typedef union bdk_reex_af_rvu_lf_cfg_debug bdk_reex_af_rvu_lf_cfg_debug_t;

static inline uint64_t BDK_REEX_AF_RVU_LF_CFG_DEBUG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_RVU_LF_CFG_DEBUG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140044000ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_RVU_LF_CFG_DEBUG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_RVU_LF_CFG_DEBUG(a) bdk_reex_af_rvu_lf_cfg_debug_t
#define bustype_BDK_REEX_AF_RVU_LF_CFG_DEBUG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_RVU_LF_CFG_DEBUG(a) "REEX_AF_RVU_LF_CFG_DEBUG"
#define device_bar_BDK_REEX_AF_RVU_LF_CFG_DEBUG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_RVU_LF_CFG_DEBUG(a) (a)
#define arguments_BDK_REEX_AF_RVU_LF_CFG_DEBUG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_af_throttle
 *
 * REE Throttle Register
 * This register controls transaction throttling.
 * This register should only be updated at configuration time.
 */
union bdk_reex_af_throttle
{
    uint64_t u;
    struct bdk_reex_af_throttle_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t ld_infl               : 7;  /**< [  6:  0](R/W) Maximum number of in-flight data fetch transactions on the NCB. Larger values may improve
                                                                 REE performance but may starve other devices on the same NCB. Maximal allowed value is 0x40.

                                                                 The value zero causes the REE instruction execution unit to temporarily suspend
                                                                 NCB read accesses; such use is for diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t ld_infl               : 7;  /**< [  6:  0](R/W) Maximum number of in-flight data fetch transactions on the NCB. Larger values may improve
                                                                 REE performance but may starve other devices on the same NCB. Maximal allowed value is 0x40.

                                                                 The value zero causes the REE instruction execution unit to temporarily suspend
                                                                 NCB read accesses; such use is for diagnostic use only. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_af_throttle_s cn; */
};
typedef union bdk_reex_af_throttle bdk_reex_af_throttle_t;

static inline uint64_t BDK_REEX_AF_THROTTLE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_AF_THROTTLE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140000010ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_AF_THROTTLE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_AF_THROTTLE(a) bdk_reex_af_throttle_t
#define bustype_BDK_REEX_AF_THROTTLE(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_AF_THROTTLE(a) "REEX_AF_THROTTLE"
#define device_bar_BDK_REEX_AF_THROTTLE(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_AF_THROTTLE(a) (a)
#define arguments_BDK_REEX_AF_THROTTLE(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_done
 *
 * REE LF Queue Done Count Registers
 * These registers contain the per-queue instruction done count.
 */
union bdk_reex_lf_done
{
    uint64_t u;
    struct bdk_reex_lf_done_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t done                  : 20; /**< [ 19:  0](R/W/H) Done count. When REE_INST_S[DONEINT] set and that instruction completes,
                                                                 REE_LF_DONE[DONE] is incremented. Writes to this field are for diagnostic use only;
                                                                 instead software writes REE_LF_DONE_ACK[DONE_ACK] with the number of decrements for
                                                                 this field.

                                                                 Interrupts are sent as follows:

                                                                 * When REE_LF_DONE[DONE] = 0, then no results are pending, the interrupt coalescing
                                                                 timer is held to zero, and an interrupt is not sent.

                                                                 * When REE_LF_DONE[DONE] != 0, then the interrupt coalescing timer counts. If
                                                                 the counter is \>= REE_LF_DONE_WAIT[TIME_WAIT] microseconds, or REE_LF_DONE[DONE]
                                                                 \>= REE_LF_DONE_WAIT[NUM_WAIT], i.e. enough time has passed or enough results
                                                                 have arrived, then the interrupt is sent.  Otherwise, it is not sent due to
                                                                 coalescing.

                                                                 * When REE_LF_DONE_ACK is written, the interrupt coalescing timer restarts.
                                                                 Note that after decrementing, this interrupt equation is recomputed.  For example, if
                                                                 REE_LF_DONE[DONE] \>= REE_LF_DONE_WAIT[NUM_WAIT] and the timer is zero, the
                                                                 interrupt will be resent immediately.  This covers the race case between software
                                                                 acknowledging an interrupt and a result returning.

                                                                 * When REE_LF_DONE_INT_ENA_W1S[DONE_ENA] = 0, interrupts are not sent, but the counting
                                                                 described above still occurs.

                                                                 Since REE instructions within a queue can complete out-of-order when the queue is mapped
                                                                 to multiple REE engines, if software is using completion interrupts the suggested scheme
                                                                 is to request a DONEINT on each request, and when an interrupt arrives perform a "greedy"
                                                                 scan for completions; even if a later command is acknowledged first this will not result
                                                                 in missing a completion. Software could also use REE_RES_S[DONEINT] to check when
                                                                 instruction needs to be counted into REE_LF_DONE/REE_LF_DONE_ACK.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 20; /**< [ 19:  0](R/W/H) Done count. When REE_INST_S[DONEINT] set and that instruction completes,
                                                                 REE_LF_DONE[DONE] is incremented. Writes to this field are for diagnostic use only;
                                                                 instead software writes REE_LF_DONE_ACK[DONE_ACK] with the number of decrements for
                                                                 this field.

                                                                 Interrupts are sent as follows:

                                                                 * When REE_LF_DONE[DONE] = 0, then no results are pending, the interrupt coalescing
                                                                 timer is held to zero, and an interrupt is not sent.

                                                                 * When REE_LF_DONE[DONE] != 0, then the interrupt coalescing timer counts. If
                                                                 the counter is \>= REE_LF_DONE_WAIT[TIME_WAIT] microseconds, or REE_LF_DONE[DONE]
                                                                 \>= REE_LF_DONE_WAIT[NUM_WAIT], i.e. enough time has passed or enough results
                                                                 have arrived, then the interrupt is sent.  Otherwise, it is not sent due to
                                                                 coalescing.

                                                                 * When REE_LF_DONE_ACK is written, the interrupt coalescing timer restarts.
                                                                 Note that after decrementing, this interrupt equation is recomputed.  For example, if
                                                                 REE_LF_DONE[DONE] \>= REE_LF_DONE_WAIT[NUM_WAIT] and the timer is zero, the
                                                                 interrupt will be resent immediately.  This covers the race case between software
                                                                 acknowledging an interrupt and a result returning.

                                                                 * When REE_LF_DONE_INT_ENA_W1S[DONE_ENA] = 0, interrupts are not sent, but the counting
                                                                 described above still occurs.

                                                                 Since REE instructions within a queue can complete out-of-order when the queue is mapped
                                                                 to multiple REE engines, if software is using completion interrupts the suggested scheme
                                                                 is to request a DONEINT on each request, and when an interrupt arrives perform a "greedy"
                                                                 scan for completions; even if a later command is acknowledged first this will not result
                                                                 in missing a completion. Software could also use REE_RES_S[DONEINT] to check when
                                                                 instruction needs to be counted into REE_LF_DONE/REE_LF_DONE_ACK.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_done_s cn; */
};
typedef union bdk_reex_lf_done bdk_reex_lf_done_t;

static inline uint64_t BDK_REEX_LF_DONE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_DONE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400100ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_DONE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_DONE(a) bdk_reex_lf_done_t
#define bustype_BDK_REEX_LF_DONE(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_DONE(a) "REEX_LF_DONE"
#define device_bar_BDK_REEX_LF_DONE(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_DONE(a) (a)
#define arguments_BDK_REEX_LF_DONE(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_done_ack
 *
 * REE LF Queue Done Count Ack Registers
 * This register is written by software to acknowledge interrupts.
 */
union bdk_reex_lf_done_ack
{
    uint64_t u;
    struct bdk_reex_lf_done_ack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to REE_LF_DONE[DONE]. When read, returns REE_LF_DONE[DONE].

                                                                 Written by software to acknowledge interrupts. If REE_LF_DONE[DONE] is still
                                                                 nonzero, the interrupt will be re-sent if the conditions described in
                                                                 REE_LF_DONE[DONE] are satisfied. */
#else /* Word 0 - Little Endian */
        uint64_t done_ack              : 20; /**< [ 19:  0](R/W/H) Number of decrements to REE_LF_DONE[DONE]. When read, returns REE_LF_DONE[DONE].

                                                                 Written by software to acknowledge interrupts. If REE_LF_DONE[DONE] is still
                                                                 nonzero, the interrupt will be re-sent if the conditions described in
                                                                 REE_LF_DONE[DONE] are satisfied. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_done_ack_s cn; */
};
typedef union bdk_reex_lf_done_ack bdk_reex_lf_done_ack_t;

static inline uint64_t BDK_REEX_LF_DONE_ACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_DONE_ACK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400110ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_DONE_ACK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_DONE_ACK(a) bdk_reex_lf_done_ack_t
#define bustype_BDK_REEX_LF_DONE_ACK(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_DONE_ACK(a) "REEX_LF_DONE_ACK"
#define device_bar_BDK_REEX_LF_DONE_ACK(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_DONE_ACK(a) (a)
#define arguments_BDK_REEX_LF_DONE_ACK(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_done_int
 *
 * INTERNAL: REE Queue Done Interrupt Clear Registers
 *
 * Internal:
 * This CSR description is only here to keep the scripts happy.
 */
union bdk_reex_lf_done_int
{
    uint64_t u;
    struct bdk_reex_lf_done_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See ree_LF_DONE[DONE].  Note this bit is read-only - acknowledge
                                                                 interrupts using REE_LF_DONE_ACK.

                                                                 To test interrupts, write REE_LF_DONE_ACK to make REE_LF_DONE[DONE] nonzero.

                                                                 Internal:
                                                                 This is called the conceptual interrupt bit in the REE_LF_DONE[DONE] documentation.
                                                                 This bit does not need to be implemented, and this CSR could be removed (except
                                                                 that the scripts will blow up). */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See ree_LF_DONE[DONE].  Note this bit is read-only - acknowledge
                                                                 interrupts using REE_LF_DONE_ACK.

                                                                 To test interrupts, write REE_LF_DONE_ACK to make REE_LF_DONE[DONE] nonzero.

                                                                 Internal:
                                                                 This is called the conceptual interrupt bit in the REE_LF_DONE[DONE] documentation.
                                                                 This bit does not need to be implemented, and this CSR could be removed (except
                                                                 that the scripts will blow up). */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_done_int_s cn; */
};
typedef union bdk_reex_lf_done_int bdk_reex_lf_done_int_t;

static inline uint64_t BDK_REEX_LF_DONE_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_DONE_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400120ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_DONE_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_DONE_INT(a) bdk_reex_lf_done_int_t
#define bustype_BDK_REEX_LF_DONE_INT(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_DONE_INT(a) "REEX_LF_DONE_INT"
#define device_bar_BDK_REEX_LF_DONE_INT(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_DONE_INT(a) (a)
#define arguments_BDK_REEX_LF_DONE_INT(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_done_int_ena_w1c
 *
 * REE LF Queue Done Interrupt Enable Clear Registers
 * Write 1 to these registers to disable the DONEINT interrupt for the queue.
 */
union bdk_reex_lf_done_int_ena_w1c
{
    uint64_t u;
    struct bdk_reex_lf_done_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done_ena              : 1;  /**< [  0:  0](R/W1C/H) Writing 1 will disable DONEINT for this queue. Writing 0 has no effect.
                                                                 A read will return the DONEINT enable bit. */
#else /* Word 0 - Little Endian */
        uint64_t done_ena              : 1;  /**< [  0:  0](R/W1C/H) Writing 1 will disable DONEINT for this queue. Writing 0 has no effect.
                                                                 A read will return the DONEINT enable bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_done_int_ena_w1c_s cn; */
};
typedef union bdk_reex_lf_done_int_ena_w1c bdk_reex_lf_done_int_ena_w1c_t;

static inline uint64_t BDK_REEX_LF_DONE_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_DONE_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400140ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_DONE_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_DONE_INT_ENA_W1C(a) bdk_reex_lf_done_int_ena_w1c_t
#define bustype_BDK_REEX_LF_DONE_INT_ENA_W1C(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_DONE_INT_ENA_W1C(a) "REEX_LF_DONE_INT_ENA_W1C"
#define device_bar_BDK_REEX_LF_DONE_INT_ENA_W1C(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_DONE_INT_ENA_W1C(a) (a)
#define arguments_BDK_REEX_LF_DONE_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_done_int_ena_w1s
 *
 * REE LF Queue Done Interrupt Enable Set Registers
 * Write 1 to these registers to enable the DONEINT interrupt for the queue.
 */
union bdk_reex_lf_done_int_ena_w1s
{
    uint64_t u;
    struct bdk_reex_lf_done_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done_ena              : 1;  /**< [  0:  0](R/W1S/H) Writing a 1 will enable DONEINT for this queue. Writing a 0 has no effect.
                                                                 A read will return the DONEINT enable bit. */
#else /* Word 0 - Little Endian */
        uint64_t done_ena              : 1;  /**< [  0:  0](R/W1S/H) Writing a 1 will enable DONEINT for this queue. Writing a 0 has no effect.
                                                                 A read will return the DONEINT enable bit. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_done_int_ena_w1s_s cn; */
};
typedef union bdk_reex_lf_done_int_ena_w1s bdk_reex_lf_done_int_ena_w1s_t;

static inline uint64_t BDK_REEX_LF_DONE_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_DONE_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400138ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_DONE_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_DONE_INT_ENA_W1S(a) bdk_reex_lf_done_int_ena_w1s_t
#define bustype_BDK_REEX_LF_DONE_INT_ENA_W1S(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_DONE_INT_ENA_W1S(a) "REEX_LF_DONE_INT_ENA_W1S"
#define device_bar_BDK_REEX_LF_DONE_INT_ENA_W1S(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_DONE_INT_ENA_W1S(a) (a)
#define arguments_BDK_REEX_LF_DONE_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_done_int_w1s
 *
 * INTERNAL: REE Queue Done Interrupt Set Registers
 *
 * Internal:
 * This CSR description is only here to keep the scripts happy.
 */
union bdk_reex_lf_done_int_w1s
{
    uint64_t u;
    struct bdk_reex_lf_done_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See ree_LF_DONE[DONE].  Note this bit is read-only - acknowledge
                                                                 interrupts using REE_LF_DONE_ACK.

                                                                 To test interrupts, write REE_LF_DONE_ACK to make REE_LF_DONE[DONE] nonzero.

                                                                 Internal:
                                                                 This is called the conceptual interrupt bit in the REE_LF_DONE[DONE] documentation.
                                                                 This bit does not need to be implemented, and this CSR could be removed (except
                                                                 that the scripts will blow up). */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](RO/H) Done interrupt. See ree_LF_DONE[DONE].  Note this bit is read-only - acknowledge
                                                                 interrupts using REE_LF_DONE_ACK.

                                                                 To test interrupts, write REE_LF_DONE_ACK to make REE_LF_DONE[DONE] nonzero.

                                                                 Internal:
                                                                 This is called the conceptual interrupt bit in the REE_LF_DONE[DONE] documentation.
                                                                 This bit does not need to be implemented, and this CSR could be removed (except
                                                                 that the scripts will blow up). */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_done_int_w1s_s cn; */
};
typedef union bdk_reex_lf_done_int_w1s bdk_reex_lf_done_int_w1s_t;

static inline uint64_t BDK_REEX_LF_DONE_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_DONE_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400130ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_DONE_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_DONE_INT_W1S(a) bdk_reex_lf_done_int_w1s_t
#define bustype_BDK_REEX_LF_DONE_INT_W1S(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_DONE_INT_W1S(a) "REEX_LF_DONE_INT_W1S"
#define device_bar_BDK_REEX_LF_DONE_INT_W1S(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_DONE_INT_W1S(a) (a)
#define arguments_BDK_REEX_LF_DONE_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_done_wait
 *
 * REE LF Queue Done Interrupt Coalescing Wait Registers
 * Specifies the per-queue interrupt coalescing settings.
 */
union bdk_reex_lf_done_wait
{
    uint64_t u;
    struct bdk_reex_lf_done_wait_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t time_wait             : 16; /**< [ 47: 32](R/W) Timer hold-off. When REE_LF_DONE[DONE] = 0, or REE_LF_DONE_ACK is written a
                                                                 timer is cleared. When the timer reaches [TIME_WAIT] microseconds then interrupt
                                                                 coalescing ends; see REE_LF_DONE[DONE]. If zero, time coalescing is disabled.

                                                                 The implementation of timer is such that the timer can expire up to 1us less then TIME_WAIT.
                                                                 Range of timer = [TIME_WAIT] * 1 us - (0 to 1 us). */
        uint64_t reserved_20_31        : 12;
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of messages hold-off.  When REE_LF_DONE[DONE] \>= [NUM_WAIT] then interrupt
                                                                 coalescing ends; see REE_LF_DONE[DONE]. If zero, same behavior as 0x1. */
#else /* Word 0 - Little Endian */
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of messages hold-off.  When REE_LF_DONE[DONE] \>= [NUM_WAIT] then interrupt
                                                                 coalescing ends; see REE_LF_DONE[DONE]. If zero, same behavior as 0x1. */
        uint64_t reserved_20_31        : 12;
        uint64_t time_wait             : 16; /**< [ 47: 32](R/W) Timer hold-off. When REE_LF_DONE[DONE] = 0, or REE_LF_DONE_ACK is written a
                                                                 timer is cleared. When the timer reaches [TIME_WAIT] microseconds then interrupt
                                                                 coalescing ends; see REE_LF_DONE[DONE]. If zero, time coalescing is disabled.

                                                                 The implementation of timer is such that the timer can expire up to 1us less then TIME_WAIT.
                                                                 Range of timer = [TIME_WAIT] * 1 us - (0 to 1 us). */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_done_wait_s cn; */
};
typedef union bdk_reex_lf_done_wait bdk_reex_lf_done_wait_t;

static inline uint64_t BDK_REEX_LF_DONE_WAIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_DONE_WAIT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400148ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_DONE_WAIT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_DONE_WAIT(a) bdk_reex_lf_done_wait_t
#define bustype_BDK_REEX_LF_DONE_WAIT(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_DONE_WAIT(a) "REEX_LF_DONE_WAIT"
#define device_bar_BDK_REEX_LF_DONE_WAIT(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_DONE_WAIT(a) (a)
#define arguments_BDK_REEX_LF_DONE_WAIT(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_doorbell
 *
 * REE LF Queue Doorbell Registers
 * Doorbells for the REE instruction queues.
 */
union bdk_reex_lf_doorbell
{
    uint64_t u;
    struct bdk_reex_lf_doorbell_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) When written, the number of instructions to add to the REE instruction doorbell count.
                                                                 When read, the current total doorbell count.

                                                                 Writes to [DBELL_CNT] are ignored when queue is disabled. */
#else /* Word 0 - Little Endian */
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) When written, the number of instructions to add to the REE instruction doorbell count.
                                                                 When read, the current total doorbell count.

                                                                 Writes to [DBELL_CNT] are ignored when queue is disabled. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_doorbell_s cn; */
};
typedef union bdk_reex_lf_doorbell bdk_reex_lf_doorbell_t;

static inline uint64_t BDK_REEX_LF_DOORBELL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_DOORBELL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400400ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_DOORBELL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_DOORBELL(a) bdk_reex_lf_doorbell_t
#define bustype_BDK_REEX_LF_DOORBELL(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_DOORBELL(a) "REEX_LF_DOORBELL"
#define device_bar_BDK_REEX_LF_DOORBELL(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_DOORBELL(a) (a)
#define arguments_BDK_REEX_LF_DOORBELL(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_ena
 *
 * REE LF Queue Enable Register
 * If a queue is disabled, REE CTL stops fetching instructions from the queue.
 */
union bdk_reex_lf_ena
{
    uint64_t u;
    struct bdk_reex_lf_ena_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) 0 = Logical instruction queue is disabled.
                                                                 1 = Enables the logical instruction queue.

                                                                 Program REE_LF_SBUF_ADDR, and REE_AF_QUE()_SBUF_CTL before you set ENA.

                                                                 Software must only transition [ENA] 0-\>1 when the queue is quiescent. See
                                                                 REE_LF_OUTSTAND_JOB[OJOB_CNT].

                                                                 Transition of [ENA] 0-\>1 will set REE_LF_DOORBELL[DBELL_CNT] to
                                                                 zero and REE_LF_SBUF_ADDR[PTR] and REE_LF_SBUF_ADDR[off] are set to starting
                                                                 IOVA.

                                                                 Hardware will clear ENA if any of the REE_LF_MISC_INT bits are set. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W/H) 0 = Logical instruction queue is disabled.
                                                                 1 = Enables the logical instruction queue.

                                                                 Program REE_LF_SBUF_ADDR, and REE_AF_QUE()_SBUF_CTL before you set ENA.

                                                                 Software must only transition [ENA] 0-\>1 when the queue is quiescent. See
                                                                 REE_LF_OUTSTAND_JOB[OJOB_CNT].

                                                                 Transition of [ENA] 0-\>1 will set REE_LF_DOORBELL[DBELL_CNT] to
                                                                 zero and REE_LF_SBUF_ADDR[PTR] and REE_LF_SBUF_ADDR[off] are set to starting
                                                                 IOVA.

                                                                 Hardware will clear ENA if any of the REE_LF_MISC_INT bits are set. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_ena_s cn; */
};
typedef union bdk_reex_lf_ena bdk_reex_lf_ena_t;

static inline uint64_t BDK_REEX_LF_ENA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_ENA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400010ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_ENA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_ENA(a) bdk_reex_lf_ena_t
#define bustype_BDK_REEX_LF_ENA(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_ENA(a) "REEX_LF_ENA"
#define device_bar_BDK_REEX_LF_ENA(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_ENA(a) (a)
#define arguments_BDK_REEX_LF_ENA(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_misc_int
 *
 * REE Queue Error Interrupt Register
 * These registers contain the per-queue error interrupts.
 */
union bdk_reex_lf_misc_int
{
    uint64_t u;
    struct bdk_reex_lf_misc_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t plle                  : 1;  /**< [  9:  9](R/W1C/H) Payload length error. Payload length not between 1 and 16384 inclusive. */
        uint64_t glse                  : 1;  /**< [  8:  8](R/W1C/H) Gather list size error. Gather list size is not between 1 and 8 entries inclusive. */
        uint64_t gdle                  : 1;  /**< [  7:  7](R/W1C/H) Gather data length error. Gather data length not equal to job length. */
        uint64_t idle                  : 1;  /**< [  6:  6](R/W1C/H) Instruction data length error. Data length not equal to job length. */
        uint64_t reserved_5            : 1;
        uint64_t nwrp                  : 1;  /**< [  4:  4](R/W1C/H) NCB write response error. */
        uint64_t reserved_3            : 1;
        uint64_t grde                  : 1;  /**< [  2:  2](R/W1C/H) Gather pointer NCB read response error. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1C/H) Instruction NCB read response error. */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1C/H) Doorbell overflow. */
#else /* Word 0 - Little Endian */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1C/H) Doorbell overflow. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1C/H) Instruction NCB read response error. */
        uint64_t grde                  : 1;  /**< [  2:  2](R/W1C/H) Gather pointer NCB read response error. */
        uint64_t reserved_3            : 1;
        uint64_t nwrp                  : 1;  /**< [  4:  4](R/W1C/H) NCB write response error. */
        uint64_t reserved_5            : 1;
        uint64_t idle                  : 1;  /**< [  6:  6](R/W1C/H) Instruction data length error. Data length not equal to job length. */
        uint64_t gdle                  : 1;  /**< [  7:  7](R/W1C/H) Gather data length error. Gather data length not equal to job length. */
        uint64_t glse                  : 1;  /**< [  8:  8](R/W1C/H) Gather list size error. Gather list size is not between 1 and 8 entries inclusive. */
        uint64_t plle                  : 1;  /**< [  9:  9](R/W1C/H) Payload length error. Payload length not between 1 and 16384 inclusive. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_misc_int_s cn; */
};
typedef union bdk_reex_lf_misc_int bdk_reex_lf_misc_int_t;

static inline uint64_t BDK_REEX_LF_MISC_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_MISC_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400300ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_MISC_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_MISC_INT(a) bdk_reex_lf_misc_int_t
#define bustype_BDK_REEX_LF_MISC_INT(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_MISC_INT(a) "REEX_LF_MISC_INT"
#define device_bar_BDK_REEX_LF_MISC_INT(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_MISC_INT(a) (a)
#define arguments_BDK_REEX_LF_MISC_INT(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_misc_int_ena_w1c
 *
 * REE VF Queue Misc Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_reex_lf_misc_int_ena_w1c
{
    uint64_t u;
    struct bdk_reex_lf_misc_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t plle                  : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[PLLE]. */
        uint64_t glse                  : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[GLSE]. */
        uint64_t gdle                  : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[GDLE]. */
        uint64_t idle                  : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[IDLE]. */
        uint64_t reserved_5            : 1;
        uint64_t nwrp                  : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[NWRP]. */
        uint64_t reserved_3            : 1;
        uint64_t grde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[GRDE]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[DOVF]. */
#else /* Word 0 - Little Endian */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[IRDE]. */
        uint64_t grde                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[GRDE]. */
        uint64_t reserved_3            : 1;
        uint64_t nwrp                  : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[NWRP]. */
        uint64_t reserved_5            : 1;
        uint64_t idle                  : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[IDLE]. */
        uint64_t gdle                  : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[GDLE]. */
        uint64_t glse                  : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[GLSE]. */
        uint64_t plle                  : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for REE_LF_MISC_INT[PLLE]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_misc_int_ena_w1c_s cn; */
};
typedef union bdk_reex_lf_misc_int_ena_w1c bdk_reex_lf_misc_int_ena_w1c_t;

static inline uint64_t BDK_REEX_LF_MISC_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_MISC_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400330ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_MISC_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_MISC_INT_ENA_W1C(a) bdk_reex_lf_misc_int_ena_w1c_t
#define bustype_BDK_REEX_LF_MISC_INT_ENA_W1C(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_MISC_INT_ENA_W1C(a) "REEX_LF_MISC_INT_ENA_W1C"
#define device_bar_BDK_REEX_LF_MISC_INT_ENA_W1C(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_MISC_INT_ENA_W1C(a) (a)
#define arguments_BDK_REEX_LF_MISC_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_misc_int_ena_w1s
 *
 * REE LF Queue Misc Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_reex_lf_misc_int_ena_w1s
{
    uint64_t u;
    struct bdk_reex_lf_misc_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t plle                  : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[PLLE]. */
        uint64_t glse                  : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[GLSE]. */
        uint64_t gdle                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[GDLE]. */
        uint64_t idle                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[IDLE]. */
        uint64_t reserved_5            : 1;
        uint64_t nwrp                  : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[NWRP]. */
        uint64_t reserved_3            : 1;
        uint64_t grde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[GRDE]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[DOVF]. */
#else /* Word 0 - Little Endian */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[IRDE]. */
        uint64_t grde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[GRDE]. */
        uint64_t reserved_3            : 1;
        uint64_t nwrp                  : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[NWRP]. */
        uint64_t reserved_5            : 1;
        uint64_t idle                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[IDLE]. */
        uint64_t gdle                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[GDLE]. */
        uint64_t glse                  : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[GLSE]. */
        uint64_t plle                  : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for REE_LF_MISC_INT[PLLE]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_misc_int_ena_w1s_s cn; */
};
typedef union bdk_reex_lf_misc_int_ena_w1s bdk_reex_lf_misc_int_ena_w1s_t;

static inline uint64_t BDK_REEX_LF_MISC_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_MISC_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400320ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_MISC_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_MISC_INT_ENA_W1S(a) bdk_reex_lf_misc_int_ena_w1s_t
#define bustype_BDK_REEX_LF_MISC_INT_ENA_W1S(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_MISC_INT_ENA_W1S(a) "REEX_LF_MISC_INT_ENA_W1S"
#define device_bar_BDK_REEX_LF_MISC_INT_ENA_W1S(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_MISC_INT_ENA_W1S(a) (a)
#define arguments_BDK_REEX_LF_MISC_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_misc_int_w1s
 *
 * REE LF Queue Misc Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_reex_lf_misc_int_w1s
{
    uint64_t u;
    struct bdk_reex_lf_misc_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t plle                  : 1;  /**< [  9:  9](R/W1S/H) Reads or sets REE_LF_MISC_INT[PLLE]. */
        uint64_t glse                  : 1;  /**< [  8:  8](R/W1S/H) Reads or sets REE_LF_MISC_INT[GLSE]. */
        uint64_t gdle                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets REE_LF_MISC_INT[GDLE]. */
        uint64_t idle                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets REE_LF_MISC_INT[IDLE]. */
        uint64_t reserved_5            : 1;
        uint64_t nwrp                  : 1;  /**< [  4:  4](R/W1S/H) Reads or sets REE_LF_MISC_INT[NWRP]. */
        uint64_t reserved_3            : 1;
        uint64_t grde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets REE_LF_MISC_INT[GRDE]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets REE_LF_MISC_INT[IRDE]. */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets REE_LF_MISC_INT[DOVF]. */
#else /* Word 0 - Little Endian */
        uint64_t dovf                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets REE_LF_MISC_INT[DOVF]. */
        uint64_t irde                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets REE_LF_MISC_INT[IRDE]. */
        uint64_t grde                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets REE_LF_MISC_INT[GRDE]. */
        uint64_t reserved_3            : 1;
        uint64_t nwrp                  : 1;  /**< [  4:  4](R/W1S/H) Reads or sets REE_LF_MISC_INT[NWRP]. */
        uint64_t reserved_5            : 1;
        uint64_t idle                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets REE_LF_MISC_INT[IDLE]. */
        uint64_t gdle                  : 1;  /**< [  7:  7](R/W1S/H) Reads or sets REE_LF_MISC_INT[GDLE]. */
        uint64_t glse                  : 1;  /**< [  8:  8](R/W1S/H) Reads or sets REE_LF_MISC_INT[GLSE]. */
        uint64_t plle                  : 1;  /**< [  9:  9](R/W1S/H) Reads or sets REE_LF_MISC_INT[PLLE]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_misc_int_w1s_s cn; */
};
typedef union bdk_reex_lf_misc_int_w1s bdk_reex_lf_misc_int_w1s_t;

static inline uint64_t BDK_REEX_LF_MISC_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_MISC_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400310ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_MISC_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_MISC_INT_W1S(a) bdk_reex_lf_misc_int_w1s_t
#define bustype_BDK_REEX_LF_MISC_INT_W1S(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_MISC_INT_W1S(a) "REEX_LF_MISC_INT_W1S"
#define device_bar_BDK_REEX_LF_MISC_INT_W1S(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_MISC_INT_W1S(a) (a)
#define arguments_BDK_REEX_LF_MISC_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_outstand_job
 *
 * REE LF Queue Outstanding Job Count Registers
 * The number of outstanding jobs.  A job is outstanding from the time it is removed
 * from the doorbell count to the time it is retired.
 */
union bdk_reex_lf_outstand_job
{
    uint64_t u;
    struct bdk_reex_lf_outstand_job_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t ojob_cnt              : 8;  /**< [  7:  0](R/W/H) Number of outstanding jobs. */
#else /* Word 0 - Little Endian */
        uint64_t ojob_cnt              : 8;  /**< [  7:  0](R/W/H) Number of outstanding jobs. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_outstand_job_s cn; */
};
typedef union bdk_reex_lf_outstand_job bdk_reex_lf_outstand_job_t;

static inline uint64_t BDK_REEX_LF_OUTSTAND_JOB(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_OUTSTAND_JOB(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400410ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_OUTSTAND_JOB", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_OUTSTAND_JOB(a) bdk_reex_lf_outstand_job_t
#define bustype_BDK_REEX_LF_OUTSTAND_JOB(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_OUTSTAND_JOB(a) "REEX_LF_OUTSTAND_JOB"
#define device_bar_BDK_REEX_LF_OUTSTAND_JOB(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_OUTSTAND_JOB(a) (a)
#define arguments_BDK_REEX_LF_OUTSTAND_JOB(a) (a),-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) ree#_lf_sbuf_addr
 *
 * REE LF Queue Starting Buffer Address Registers
 * These registers set the buffer addresses for the instruction queues. When quiescent (i.e.
 * outstanding doorbell count is 0 and REE_LF_OUTSTAND_JOB[OJOB_CNT] is zero), it is
 * safe to rewrite this register. These registers must be programmed after software
 * programs the
 * corresponding REE_AF_QUE()_SBUF_CTL and before setting REE_LF_ENA[ENA].
 */
union bdk_reex_lf_sbuf_addr
{
    uint64_t u;
    struct bdk_reex_lf_sbuf_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) Instruction buffer pointer bits \<52:7\> (128-byte aligned). Behavior is unpredictable if
                                                                 the address is 0x0.  When written, it is the initial buffer starting IOVA; when read, it
                                                                 is the next read pointer IOVA to be requested from NCB.
                                                                 [PTR] is overwritten with the next pointer each time that the command buffer
                                                                 segment is exhausted. New commands will then be read from the newly specified command
                                                                 buffer pointer. */
        uint64_t off                   : 7;  /**< [  6:  0](RO/H) When written, the value is ignored. When read, the returned value is the offset
                                                                 of the next read pointer. */
#else /* Word 0 - Little Endian */
        uint64_t off                   : 7;  /**< [  6:  0](RO/H) When written, the value is ignored. When read, the returned value is the offset
                                                                 of the next read pointer. */
        uint64_t ptr                   : 46; /**< [ 52:  7](R/W/H) Instruction buffer pointer bits \<52:7\> (128-byte aligned). Behavior is unpredictable if
                                                                 the address is 0x0.  When written, it is the initial buffer starting IOVA; when read, it
                                                                 is the next read pointer IOVA to be requested from NCB.
                                                                 [PTR] is overwritten with the next pointer each time that the command buffer
                                                                 segment is exhausted. New commands will then be read from the newly specified command
                                                                 buffer pointer. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_lf_sbuf_addr_s cn; */
};
typedef union bdk_reex_lf_sbuf_addr bdk_reex_lf_sbuf_addr_t;

static inline uint64_t BDK_REEX_LF_SBUF_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_LF_SBUF_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840201400020ll + 0x100000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_LF_SBUF_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_LF_SBUF_ADDR(a) bdk_reex_lf_sbuf_addr_t
#define bustype_BDK_REEX_LF_SBUF_ADDR(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_REEX_LF_SBUF_ADDR(a) "REEX_LF_SBUF_ADDR"
#define device_bar_BDK_REEX_LF_SBUF_ADDR(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_REEX_LF_SBUF_ADDR(a) (a)
#define arguments_BDK_REEX_LF_SBUF_ADDR(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_priv_af_int_cfg
 *
 * REE Privileged Admin Function Interrupt Configuration Register
 */
union bdk_reex_priv_af_int_cfg
{
    uint64_t u;
    struct bdk_reex_priv_af_int_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by REE_AF_INT_VEC_E. */
        uint64_t reserved_11           : 1;
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of AF interrupt vectors enumerated by
                                                                 REE_AF_INT_VEC_E in RVU PF(0)'s MSI-X table. This offset is added to each
                                                                 enumerated value to obtain the corresponding MSI-X vector index. The
                                                                 highest enumerated value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF(0)_MSIX_CFG[PF_MSIXT_SIZEM1]. */
#else /* Word 0 - Little Endian */
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of AF interrupt vectors enumerated by
                                                                 REE_AF_INT_VEC_E in RVU PF(0)'s MSI-X table. This offset is added to each
                                                                 enumerated value to obtain the corresponding MSI-X vector index. The
                                                                 highest enumerated value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF(0)_MSIX_CFG[PF_MSIXT_SIZEM1]. */
        uint64_t reserved_11           : 1;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by REE_AF_INT_VEC_E. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_priv_af_int_cfg_s cn; */
};
typedef union bdk_reex_priv_af_int_cfg bdk_reex_priv_af_int_cfg_t;

static inline uint64_t BDK_REEX_PRIV_AF_INT_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_PRIV_AF_INT_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=1))
        return 0x840140004000ll + 0x10000000ll * ((a) & 0x1);
    __bdk_csr_fatal("REEX_PRIV_AF_INT_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_PRIV_AF_INT_CFG(a) bdk_reex_priv_af_int_cfg_t
#define bustype_BDK_REEX_PRIV_AF_INT_CFG(a) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_PRIV_AF_INT_CFG(a) "REEX_PRIV_AF_INT_CFG"
#define device_bar_BDK_REEX_PRIV_AF_INT_CFG(a) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_PRIV_AF_INT_CFG(a) (a)
#define arguments_BDK_REEX_PRIV_AF_INT_CFG(a) (a),-1,-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_priv_lf#_cfg
 *
 * REE Privileged LF Configuration Registers
 */
union bdk_reex_priv_lfx_cfg
{
    uint64_t u;
    struct bdk_reex_priv_lfx_cfg_s
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
    /* struct bdk_reex_priv_lfx_cfg_s cn; */
};
typedef union bdk_reex_priv_lfx_cfg bdk_reex_priv_lfx_cfg_t;

static inline uint64_t BDK_REEX_PRIV_LFX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_PRIV_LFX_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=35)))
        return 0x840140041000ll + 0x10000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("REEX_PRIV_LFX_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_PRIV_LFX_CFG(a,b) bdk_reex_priv_lfx_cfg_t
#define bustype_BDK_REEX_PRIV_LFX_CFG(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_PRIV_LFX_CFG(a,b) "REEX_PRIV_LFX_CFG"
#define device_bar_BDK_REEX_PRIV_LFX_CFG(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_PRIV_LFX_CFG(a,b) (a)
#define arguments_BDK_REEX_PRIV_LFX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (RVU_PF_BAR0) ree#_priv_lf#_int_cfg
 *
 * REE Privileged LF Interrupt Configuration Registers
 */
union bdk_reex_priv_lfx_int_cfg
{
    uint64_t u;
    struct bdk_reex_priv_lfx_int_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by REE_LF_INT_VEC_E. */
        uint64_t reserved_11           : 1;
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of LF interrupt vectors enumerated by the block's
                                                                 REE_LF_INT_VEC_E in the MSI-X table of the corresponding RVU VF/PF (see
                                                                 REE_PRIV_LF()_CFG[PF_FUNC]). This offset is added to each enumerated value
                                                                 to obtain the corresponding MSI-X vector index. The highest enumerated
                                                                 value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF()_MSIX_CFG[PF_MSIXT_SIZEM1,VF_MSIXT_SIZEM1]. */
#else /* Word 0 - Little Endian */
        uint64_t msix_offset           : 11; /**< [ 10:  0](R/W) MSI-X offset. Offset of LF interrupt vectors enumerated by the block's
                                                                 REE_LF_INT_VEC_E in the MSI-X table of the corresponding RVU VF/PF (see
                                                                 REE_PRIV_LF()_CFG[PF_FUNC]). This offset is added to each enumerated value
                                                                 to obtain the corresponding MSI-X vector index. The highest enumerated
                                                                 value plus [MSIX_OFFSET] must be less than or equal to
                                                                 RVU_PRIV_PF()_MSIX_CFG[PF_MSIXT_SIZEM1,VF_MSIXT_SIZEM1]. */
        uint64_t reserved_11           : 1;
        uint64_t msix_size             : 8;  /**< [ 19: 12](RO) Number of interrupt vectors enumerated by REE_LF_INT_VEC_E. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_reex_priv_lfx_int_cfg_s cn; */
};
typedef union bdk_reex_priv_lfx_int_cfg bdk_reex_priv_lfx_int_cfg_t;

static inline uint64_t BDK_REEX_PRIV_LFX_INT_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_REEX_PRIV_LFX_INT_CFG(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=1) && (b<=35)))
        return 0x840140042000ll + 0x10000000ll * ((a) & 0x1) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("REEX_PRIV_LFX_INT_CFG", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_REEX_PRIV_LFX_INT_CFG(a,b) bdk_reex_priv_lfx_int_cfg_t
#define bustype_BDK_REEX_PRIV_LFX_INT_CFG(a,b) BDK_CSR_TYPE_RVU_PF_BAR0
#define basename_BDK_REEX_PRIV_LFX_INT_CFG(a,b) "REEX_PRIV_LFX_INT_CFG"
#define device_bar_BDK_REEX_PRIV_LFX_INT_CFG(a,b) 0x0 /* RVU_BAR0 */
#define busnum_BDK_REEX_PRIV_LFX_INT_CFG(a,b) (a)
#define arguments_BDK_REEX_PRIV_LFX_INT_CFG(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_REE_H__ */
