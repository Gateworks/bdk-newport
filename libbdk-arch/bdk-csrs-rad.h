#ifndef __BDK_CSRS_RAD_H__
#define __BDK_CSRS_RAD_H__
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
 * OcteonTX RAD.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration rad_bar_e
 *
 * RAD Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_RAD_BAR_E_RAD_PF_BAR0 (0x870000000000ll)
#define BDK_RAD_BAR_E_RAD_PF_BAR0_SIZE 0x800000ull
#define BDK_RAD_BAR_E_RAD_PF_BAR4 (0x870000f00000ll)
#define BDK_RAD_BAR_E_RAD_PF_BAR4_SIZE 0x100000ull
#define BDK_RAD_BAR_E_RAD_VFX_BAR0(a) (0x870020000000ll + 0x100000ll * (a))
#define BDK_RAD_BAR_E_RAD_VFX_BAR0_SIZE 0x100000ull
#define BDK_RAD_BAR_E_RAD_VFX_BAR4(a) (0x870030000000ll + 0x100000ll * (a))
#define BDK_RAD_BAR_E_RAD_VFX_BAR4_SIZE 0x100000ull

/**
 * Enumeration rad_pf_int_vec_e
 *
 * RAD PF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_RAD_PF_INT_VEC_E_MBOXX(a) (0 + (a))

/**
 * Enumeration rad_vf_int_vec_e
 *
 * RAD VF MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_RAD_VF_INT_VEC_E_INTR (0)

/**
 * Structure rad_cword_s
 *
 * RAD Control Word Structure
 */
union bdk_rad_cword_s
{
    uint64_t u;
    struct bdk_rad_cword_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t istr                  : 8;  /**< [ 63: 56] When [STREN] is set, the SMMU stream for RAD_IWORD_S[PTR]. Else, reserved. */
        uint64_t ostr                  : 8;  /**< [ 55: 48] When [STREN] is set, the SMMU stream for RAD_OWORD_S[PTR]. Else, reserved. */
        uint64_t reserved_39_47        : 9;
        uint64_t stren                 : 1;  /**< [ 38: 38] Stream override enable.
                                                                 0 = Use the default SMMU SR-IOV stream identifier for the queue
                                                                 ({PCC_DEV_CON_E::RAD[15:0], VF_number[7:0] + 1}) for all requests.
                                                                 1 = Use [ISTR] for the low 8-bits of the SMMU stream identifier for RAD_IWORD_S[PTR]
                                                                 streams, and likewise [OSTR] for RAD_OWORD_S[PTR] streams, and RAD_RESP_S[STR] for
                                                                 RAD_RESP_S[PTR] streams.  This does not affect the GIC stream ID used for interrupts.
                                                                 This allows software to accomplish hypervisor-to-guest and guest-to-guest DMAs by using
                                                                 multiple streams in a transaction.

                                                                 This bit should only be set by a hypervisor, and any hypervisor code should enforce guest
                                                                 requests have this bit clear.

                                                                 Internal:
                                                                 When RAD is virtualized this will need a per-queue
                                                                 PF enable. */
        uint64_t dn                    : 1;  /**< [ 37: 37] When set, on completing this transaction RAD will increment RAD_VQ()_DONE_CNT. */
        uint64_t q_cmp                 : 1;  /**< [ 36: 36] Q pipe mode. Must not be set when [QOUT]=0, and must not be set when [Q_XOR] is set.
                                                                 0 = Q pipe is in normal mode.
                                                                 1 = Q pipe is in nonzero byte detect mode. The Q RAD_OWORD_S[PTR] result is the nonzero
                                                                 detect result, which indicates the position of the first nonzero byte in the pipe result
                                                                 bytes. */
        uint64_t p_cmp                 : 1;  /**< [ 35: 35] P pipe mode. Must not be set when [POUT]=0, and must not be set when [P_XOR] is set.
                                                                 0 = P pipe is in normal mode.
                                                                 1 = P pipe is in nonzero byte detect mode. The P RAD_OWORD_S[PTR] result is the nonzero
                                                                 detect result, which indicates the position of the first nonzero byte in the pipe result
                                                                 bytes. */
        uint64_t q_xor                 : 1;  /**< [ 34: 34] Indicates whether the Q output buffer bytes are the normal Q pipe result or the normal Q
                                                                 pipe result exclusive-OR'ed with the P pipe result.

                                                                 When [Q_XOR] = 0 (and [Q_CMP]=0), the Q output buffer bytes are the normal Q pipe result,
                                                                 which does not include the P pipe result in any way.

                                                                 When [Q_XOR] = 1, the Q output buffer bytes are the normal Q pipe result exclusive-OR'ed
                                                                 with the P pipe result, as if the P pipe result were another Q RAD_IWORD_S for the Q pipe
                                                                 with QMULT=1.

                                                                 Must not be set unless both [POUT,QOUT] are set, and must not be set when [Q_CMP] is set. */
        uint64_t p_xor                 : 1;  /**< [ 33: 33] Indicates whether the P output buffer bytes are the normal P pipe result or the normal P
                                                                 pipe result exclusive-OR'ed with the Q pipe result.

                                                                 When [P_XOR]=0 (and [P_CMP] = 0), the P output buffer bytes are the normal P pipe result,
                                                                 which does not include the Q pipe result in any way.

                                                                 When [P_XOR]=1, the P output buffer bytes are the normal P pipe result exclusive-OR'ed
                                                                 with the Q pipe result, as if the Q pipe result were another P RAD_IWORD_S for the P pipe.

                                                                 [P_XOR] must not be set unless both [POUT,QOUT] are set, and must not be set when [P_CMP]
                                                                 is set. */
        uint64_t wqe                   : 1;  /**< [ 32: 32] SSO work queue entry submission.
                                                                 0 = RAD_RESP_S[PTR] if nonzero contains an address to be written in L2/DRAM on
                                                                 completion of this instruction.
                                                                 1 = RAD_RESP_S[PTR] if nonzero contains a work queue entry pointer which RAD
                                                                 will submit to the SSO on completion of this instruction. */
        uint64_t qout                  : 1;  /**< [ 31: 31] Q pipe is used by this instruction. If set, RAD_IWORD_S[QEN] must be set for at least one
                                                                 RAD_IWORD_S. At least one of [QOUT,POUT] must be set. */
        uint64_t pout                  : 1;  /**< [ 30: 30] P pipe is used by this instruction. If set, RAD_IWORD_S[PEN] must be set for at least one
                                                                 RAD_IWORD_S. At least one of [QOUT,POUT] must be set. */
        uint64_t iword                 : 6;  /**< [ 29: 24] Number of input buffers used, must be 1 to 32. If one, a copy operation will be performed
                                                                 (i.e. an XOR with zero.) For copy operations, [Q_XOR] = 0, [P_XOR] = 0, [QOUT] = 1,
                                                                 [POUT] = 0, [QMULT] = 1, [QEN] = 1, [PEN] = 0, and [Q_CMP] = 0. */
        uint64_t size                  : 24; /**< [ 23:  0] Indicates the size in bytes of all input buffers. When [Q_CMP,P_CMP]=0, also indicates the
                                                                 size of the Q/P output buffers. Must be a multiple of 8B (i.e. \<2:0\> must be zero). */
#else /* Word 0 - Little Endian */
        uint64_t size                  : 24; /**< [ 23:  0] Indicates the size in bytes of all input buffers. When [Q_CMP,P_CMP]=0, also indicates the
                                                                 size of the Q/P output buffers. Must be a multiple of 8B (i.e. \<2:0\> must be zero). */
        uint64_t iword                 : 6;  /**< [ 29: 24] Number of input buffers used, must be 1 to 32. If one, a copy operation will be performed
                                                                 (i.e. an XOR with zero.) For copy operations, [Q_XOR] = 0, [P_XOR] = 0, [QOUT] = 1,
                                                                 [POUT] = 0, [QMULT] = 1, [QEN] = 1, [PEN] = 0, and [Q_CMP] = 0. */
        uint64_t pout                  : 1;  /**< [ 30: 30] P pipe is used by this instruction. If set, RAD_IWORD_S[PEN] must be set for at least one
                                                                 RAD_IWORD_S. At least one of [QOUT,POUT] must be set. */
        uint64_t qout                  : 1;  /**< [ 31: 31] Q pipe is used by this instruction. If set, RAD_IWORD_S[QEN] must be set for at least one
                                                                 RAD_IWORD_S. At least one of [QOUT,POUT] must be set. */
        uint64_t wqe                   : 1;  /**< [ 32: 32] SSO work queue entry submission.
                                                                 0 = RAD_RESP_S[PTR] if nonzero contains an address to be written in L2/DRAM on
                                                                 completion of this instruction.
                                                                 1 = RAD_RESP_S[PTR] if nonzero contains a work queue entry pointer which RAD
                                                                 will submit to the SSO on completion of this instruction. */
        uint64_t p_xor                 : 1;  /**< [ 33: 33] Indicates whether the P output buffer bytes are the normal P pipe result or the normal P
                                                                 pipe result exclusive-OR'ed with the Q pipe result.

                                                                 When [P_XOR]=0 (and [P_CMP] = 0), the P output buffer bytes are the normal P pipe result,
                                                                 which does not include the Q pipe result in any way.

                                                                 When [P_XOR]=1, the P output buffer bytes are the normal P pipe result exclusive-OR'ed
                                                                 with the Q pipe result, as if the Q pipe result were another P RAD_IWORD_S for the P pipe.

                                                                 [P_XOR] must not be set unless both [POUT,QOUT] are set, and must not be set when [P_CMP]
                                                                 is set. */
        uint64_t q_xor                 : 1;  /**< [ 34: 34] Indicates whether the Q output buffer bytes are the normal Q pipe result or the normal Q
                                                                 pipe result exclusive-OR'ed with the P pipe result.

                                                                 When [Q_XOR] = 0 (and [Q_CMP]=0), the Q output buffer bytes are the normal Q pipe result,
                                                                 which does not include the P pipe result in any way.

                                                                 When [Q_XOR] = 1, the Q output buffer bytes are the normal Q pipe result exclusive-OR'ed
                                                                 with the P pipe result, as if the P pipe result were another Q RAD_IWORD_S for the Q pipe
                                                                 with QMULT=1.

                                                                 Must not be set unless both [POUT,QOUT] are set, and must not be set when [Q_CMP] is set. */
        uint64_t p_cmp                 : 1;  /**< [ 35: 35] P pipe mode. Must not be set when [POUT]=0, and must not be set when [P_XOR] is set.
                                                                 0 = P pipe is in normal mode.
                                                                 1 = P pipe is in nonzero byte detect mode. The P RAD_OWORD_S[PTR] result is the nonzero
                                                                 detect result, which indicates the position of the first nonzero byte in the pipe result
                                                                 bytes. */
        uint64_t q_cmp                 : 1;  /**< [ 36: 36] Q pipe mode. Must not be set when [QOUT]=0, and must not be set when [Q_XOR] is set.
                                                                 0 = Q pipe is in normal mode.
                                                                 1 = Q pipe is in nonzero byte detect mode. The Q RAD_OWORD_S[PTR] result is the nonzero
                                                                 detect result, which indicates the position of the first nonzero byte in the pipe result
                                                                 bytes. */
        uint64_t dn                    : 1;  /**< [ 37: 37] When set, on completing this transaction RAD will increment RAD_VQ()_DONE_CNT. */
        uint64_t stren                 : 1;  /**< [ 38: 38] Stream override enable.
                                                                 0 = Use the default SMMU SR-IOV stream identifier for the queue
                                                                 ({PCC_DEV_CON_E::RAD[15:0], VF_number[7:0] + 1}) for all requests.
                                                                 1 = Use [ISTR] for the low 8-bits of the SMMU stream identifier for RAD_IWORD_S[PTR]
                                                                 streams, and likewise [OSTR] for RAD_OWORD_S[PTR] streams, and RAD_RESP_S[STR] for
                                                                 RAD_RESP_S[PTR] streams.  This does not affect the GIC stream ID used for interrupts.
                                                                 This allows software to accomplish hypervisor-to-guest and guest-to-guest DMAs by using
                                                                 multiple streams in a transaction.

                                                                 This bit should only be set by a hypervisor, and any hypervisor code should enforce guest
                                                                 requests have this bit clear.

                                                                 Internal:
                                                                 When RAD is virtualized this will need a per-queue
                                                                 PF enable. */
        uint64_t reserved_39_47        : 9;
        uint64_t ostr                  : 8;  /**< [ 55: 48] When [STREN] is set, the SMMU stream for RAD_OWORD_S[PTR]. Else, reserved. */
        uint64_t istr                  : 8;  /**< [ 63: 56] When [STREN] is set, the SMMU stream for RAD_IWORD_S[PTR]. Else, reserved. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_cword_s_s cn; */
};

/**
 * Structure rad_iword_s
 *
 * RAD Input Pointer Structure
 * RAD_IWORD_S points to where to read the input buffer data from. Each RAD_IWORD_S indicates
 * whether the buffer should be accumulated by the P pipe, the Q pipe, or both. The RAD_IWORD_S
 * also supplies the Q pipe multiplier for the buffer (QMULT).
 */
union bdk_rad_iword_s
{
    uint64_t u;
    struct bdk_rad_iword_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t qmult                 : 8;  /**< [ 63: 56] The Q pipe multiplier for the input buffer. Must must be zero when [QEN] is not set;
                                                                 [QMULT] must be nonzero when [QEN] is set. When [QMULT] is 1, the multiplication
                                                                 simplifies to the identity function, and the Q pipe performs the same XOR function as the
                                                                 P pipe. */
        uint64_t nc                    : 1;  /**< [ 55: 55] When set, indicates that RAD should not allocate L2 cache space for this input buffer data
                                                                 on L2 cache misses. Setting [NC] may improve performance in some circumstances, as the L2
                                                                 cache may not be polluted with input buffer data. */
        uint64_t qen                   : 1;  /**< [ 54: 54] Indicates that this input buffer data should participate in the Q pipe result. The Q pipe
                                                                 hardware multiplies each participating input byte by RAD_IWORD_S[QMULT] before
                                                                 accumulating them
                                                                 by exclusive-OR'ing. Must not be set when RAD_CWORD_S[QOUT] is not set. If
                                                                 RAD_CWORD_S[QOUT] is set, [QEN] must be set for at least one RAD_IWORD_S. */
        uint64_t pen                   : 1;  /**< [ 53: 53] Indicates that this input buffer data should participate in the P pipe result.
                                                                 The P pipe hardware accumulates each participating input byte by bit-wise exclusive-OR'ing
                                                                 it.
                                                                 [PEN] must not be set when RAD_CWORD_S[POUT] is not set.
                                                                 If RAD_CWORD_S[POUT] is set, [PEN] must be set for at least one RAD_IWORD_S. */
        uint64_t reserved_49_52        : 4;
        uint64_t ptr                   : 49; /**< [ 48:  0] The starting IOVA of the input buffer in L2/DRAM. Must be naturally aligned on an
                                                                 eight-byte boundary (i.e. \<2:0\> must be zero). The SMMU stream used may be overridden with
                                                                 RAD_CWORD_S[ISTR]. */
#else /* Word 0 - Little Endian */
        uint64_t ptr                   : 49; /**< [ 48:  0] The starting IOVA of the input buffer in L2/DRAM. Must be naturally aligned on an
                                                                 eight-byte boundary (i.e. \<2:0\> must be zero). The SMMU stream used may be overridden with
                                                                 RAD_CWORD_S[ISTR]. */
        uint64_t reserved_49_52        : 4;
        uint64_t pen                   : 1;  /**< [ 53: 53] Indicates that this input buffer data should participate in the P pipe result.
                                                                 The P pipe hardware accumulates each participating input byte by bit-wise exclusive-OR'ing
                                                                 it.
                                                                 [PEN] must not be set when RAD_CWORD_S[POUT] is not set.
                                                                 If RAD_CWORD_S[POUT] is set, [PEN] must be set for at least one RAD_IWORD_S. */
        uint64_t qen                   : 1;  /**< [ 54: 54] Indicates that this input buffer data should participate in the Q pipe result. The Q pipe
                                                                 hardware multiplies each participating input byte by RAD_IWORD_S[QMULT] before
                                                                 accumulating them
                                                                 by exclusive-OR'ing. Must not be set when RAD_CWORD_S[QOUT] is not set. If
                                                                 RAD_CWORD_S[QOUT] is set, [QEN] must be set for at least one RAD_IWORD_S. */
        uint64_t nc                    : 1;  /**< [ 55: 55] When set, indicates that RAD should not allocate L2 cache space for this input buffer data
                                                                 on L2 cache misses. Setting [NC] may improve performance in some circumstances, as the L2
                                                                 cache may not be polluted with input buffer data. */
        uint64_t qmult                 : 8;  /**< [ 63: 56] The Q pipe multiplier for the input buffer. Must must be zero when [QEN] is not set;
                                                                 [QMULT] must be nonzero when [QEN] is set. When [QMULT] is 1, the multiplication
                                                                 simplifies to the identity function, and the Q pipe performs the same XOR function as the
                                                                 P pipe. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_iword_s_s cn; */
};

/**
 * Structure rad_nzdist_s
 *
 * RAD Non-Zero Result Structure
 * Data written to RAD_OWORD_S[PTR] with nonzero result.
 * RAD_REG_CTL[STORE_BE] indicates the endianness of this structure.
 */
union bdk_rad_nzdist_s
{
    uint64_t u;
    struct bdk_rad_nzdist_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t nzdist                : 24; /**< [ 23:  0] Location of first pipe result byte that is nonzero. If all pipe result bytes are zero for
                                                                 this instruction, NZDIST = RAD_CWORD_S[SIZE]. */
#else /* Word 0 - Little Endian */
        uint64_t nzdist                : 24; /**< [ 23:  0] Location of first pipe result byte that is nonzero. If all pipe result bytes are zero for
                                                                 this instruction, NZDIST = RAD_CWORD_S[SIZE]. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_nzdist_s_s cn; */
};

/**
 * Structure rad_oword_s
 *
 * RAD Output Pointer Structure
 * RAD_OWORD_S points to where to output data to.
 */
union bdk_rad_oword_s
{
    uint64_t u;
    struct bdk_rad_oword_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_58_63        : 6;
        uint64_t fw                    : 1;  /**< [ 57: 57] When set, indicates that RAD can modify any byte in any (128B) cache line touched by
                                                                 L2/DRAM addresses [PTR] through [PTR]+RAD_CWORD_S[SIZE]. Setting [FW] can improve hardware
                                                                 performance, as some DRAM loads can be avoided on L2 cache misses. The Q [FW] must not be
                                                                 set when RAD_CWORD_S[Q_CMP] is set, and the P [FW] must not be set when RAD_CWORD_S[P_CMP]
                                                                 is set. */
        uint64_t nc                    : 1;  /**< [ 56: 56] When set, indicates that RAD should not allocate L2 cache space for the P/Q data on L2
                                                                 cache misses. [NC] should typically be clear, though setting [NC] can improve performance
                                                                 in some circumstances, as the L2 cache will not be polluted by P/Q data. The Q
                                                                 RAD_OWORD_S[NC] must not be set when RAD_CWORD_S[Q_CMP] is set, and the P RAD_OWORD_S[NC]
                                                                 must not be set when RAD_CWORD_S[P_CMP] is set. */
        uint64_t reserved_49_55        : 7;
        uint64_t p_ptr                 : 49; /**< [ 48:  0] When RAD_CWORD_S[P_CMP,Q_CMP]=0, [PTR] indicates the starting IOVA of the L2/DRAM
                                                                 buffer that will receive the P/Q data.  The SMMU stream used may be overridden with
                                                                 RAD_CWORD_S[OSTR].

                                                                 In the non-compare mode, the output buffer receives
                                                                 all of the output buffer bytes.

                                                                 When RAD_CWORD_S[P_CMP,Q_CMP]=1, the corresponding P/Q pipe is in compare mode, and the
                                                                 only output of the pipe is the nonzero detect result. In this case, [PTR] indicates the
                                                                 8-byte location of the nonzero detect result, which is written with RAD_NZDIST_S.

                                                                 [P_PTR] must be naturally-aligned on an 8-byte boundary (i.e. \<2:0\> must be zero). */
#else /* Word 0 - Little Endian */
        uint64_t p_ptr                 : 49; /**< [ 48:  0] When RAD_CWORD_S[P_CMP,Q_CMP]=0, [PTR] indicates the starting IOVA of the L2/DRAM
                                                                 buffer that will receive the P/Q data.  The SMMU stream used may be overridden with
                                                                 RAD_CWORD_S[OSTR].

                                                                 In the non-compare mode, the output buffer receives
                                                                 all of the output buffer bytes.

                                                                 When RAD_CWORD_S[P_CMP,Q_CMP]=1, the corresponding P/Q pipe is in compare mode, and the
                                                                 only output of the pipe is the nonzero detect result. In this case, [PTR] indicates the
                                                                 8-byte location of the nonzero detect result, which is written with RAD_NZDIST_S.

                                                                 [P_PTR] must be naturally-aligned on an 8-byte boundary (i.e. \<2:0\> must be zero). */
        uint64_t reserved_49_55        : 7;
        uint64_t nc                    : 1;  /**< [ 56: 56] When set, indicates that RAD should not allocate L2 cache space for the P/Q data on L2
                                                                 cache misses. [NC] should typically be clear, though setting [NC] can improve performance
                                                                 in some circumstances, as the L2 cache will not be polluted by P/Q data. The Q
                                                                 RAD_OWORD_S[NC] must not be set when RAD_CWORD_S[Q_CMP] is set, and the P RAD_OWORD_S[NC]
                                                                 must not be set when RAD_CWORD_S[P_CMP] is set. */
        uint64_t fw                    : 1;  /**< [ 57: 57] When set, indicates that RAD can modify any byte in any (128B) cache line touched by
                                                                 L2/DRAM addresses [PTR] through [PTR]+RAD_CWORD_S[SIZE]. Setting [FW] can improve hardware
                                                                 performance, as some DRAM loads can be avoided on L2 cache misses. The Q [FW] must not be
                                                                 set when RAD_CWORD_S[Q_CMP] is set, and the P [FW] must not be set when RAD_CWORD_S[P_CMP]
                                                                 is set. */
        uint64_t reserved_58_63        : 6;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_oword_s_s cn; */
};

/**
 * Structure rad_resp_s
 *
 * RAD Response Pointer Structure
 * This structure contains a pointer to the L2/DRAM byte to zero after completing the instruction.
 */
union bdk_rad_resp_s
{
    uint64_t u[2];
    struct bdk_rad_resp_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t istr                  : 8;  /**< [ 63: 56] When RAD_CWORD_S[WQE] is clear, and RAD_CWORD_S[STREN] is set, the SMMU stream
                                                                 for [PTR]. */
        uint64_t reserved_44_55        : 12;
        uint64_t ggrp                  : 10; /**< [ 43: 34] When RAD_CWORD_S[WQE] is set and [PTR] != 0, the SSO guest-group to use when RAD
                                                                 submits work to SSO.
                                                                 For the SSO to not discard the add-work request, SSO_PF_MAP() must
                                                                 map [GGRP] and RAD_GMCTL[GMID] as valid. */
        uint64_t tt                    : 2;  /**< [ 33: 32] When RAD_CWORD_S[WQE] is set and [PTR] != 0, the SSO tag type to use when RAD
                                                                 submits work to SSO. */
        uint64_t tag                   : 32; /**< [ 31:  0] When RAD_CWORD_S[WQE] is set and [PTR] != 0, the SSO tag to use when RAD submits
                                                                 work to SSO. */
#else /* Word 0 - Little Endian */
        uint64_t tag                   : 32; /**< [ 31:  0] When RAD_CWORD_S[WQE] is set and [PTR] != 0, the SSO tag to use when RAD submits
                                                                 work to SSO. */
        uint64_t tt                    : 2;  /**< [ 33: 32] When RAD_CWORD_S[WQE] is set and [PTR] != 0, the SSO tag type to use when RAD
                                                                 submits work to SSO. */
        uint64_t ggrp                  : 10; /**< [ 43: 34] When RAD_CWORD_S[WQE] is set and [PTR] != 0, the SSO guest-group to use when RAD
                                                                 submits work to SSO.
                                                                 For the SSO to not discard the add-work request, SSO_PF_MAP() must
                                                                 map [GGRP] and RAD_GMCTL[GMID] as valid. */
        uint64_t reserved_44_55        : 12;
        uint64_t istr                  : 8;  /**< [ 63: 56] When RAD_CWORD_S[WQE] is clear, and RAD_CWORD_S[STREN] is set, the SMMU stream
                                                                 for [PTR]. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_113_127      : 15;
        uint64_t ptr                   : 49; /**< [112: 64] When RAD_CWORD_S[WQE] is clear and [PTR] != 0, RAD writes the L2/DRAM IOVA byte
                                                                 indicated by [PTR] to zero after completing the
                                                                 instruction. RAD_REG_CTL[STORE_BE] indicates the endianness of [PTR]. The SMMU
                                                                 stream used may be overridden with [STR].

                                                                 When RAD_CWORD_S[WQE] is set and [PTR] != 0, it is a pointer to a work-queue
                                                                 entry that RAD submits work to SSO after completing the instruction. [PTR] must
                                                                 be naturally-aligned on an 8B boundary (i.e. \<2:0\> must be zero). */
#else /* Word 1 - Little Endian */
        uint64_t ptr                   : 49; /**< [112: 64] When RAD_CWORD_S[WQE] is clear and [PTR] != 0, RAD writes the L2/DRAM IOVA byte
                                                                 indicated by [PTR] to zero after completing the
                                                                 instruction. RAD_REG_CTL[STORE_BE] indicates the endianness of [PTR]. The SMMU
                                                                 stream used may be overridden with [STR].

                                                                 When RAD_CWORD_S[WQE] is set and [PTR] != 0, it is a pointer to a work-queue
                                                                 entry that RAD submits work to SSO after completing the instruction. [PTR] must
                                                                 be naturally-aligned on an 8B boundary (i.e. \<2:0\> must be zero). */
        uint64_t reserved_113_127      : 15;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_rad_resp_s_s cn; */
};

/**
 * Register (NCB) rad_eco
 *
 * INTERNAL: RAD ECO Register
 */
union bdk_rad_eco
{
    uint64_t u;
    struct bdk_rad_eco_s
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
    /* struct bdk_rad_eco_s cn; */
};
typedef union bdk_rad_eco bdk_rad_eco_t;

#define BDK_RAD_ECO BDK_RAD_ECO_FUNC()
static inline uint64_t BDK_RAD_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_ECO_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000168ll;
    __bdk_csr_fatal("RAD_ECO", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_ECO bdk_rad_eco_t
#define bustype_BDK_RAD_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_ECO "RAD_ECO"
#define device_bar_BDK_RAD_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_ECO 0
#define arguments_BDK_RAD_ECO -1,-1,-1,-1

/**
 * Register (NCB) rad_gmctl
 *
 * RAD Guest Machine Control Register
 */
union bdk_rad_gmctl
{
    uint64_t u;
    struct bdk_rad_gmctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer free, or to SSO for all submit work operations initiated by this queue.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
#else /* Word 0 - Little Endian */
        uint64_t gmid                  : 16; /**< [ 15:  0](R/W) Guest machine identifier. The GMID to send to FPA for all
                                                                 buffer free, or to SSO for all submit work operations initiated by this queue.
                                                                 Must be nonzero or FPA/SSO will drop requests; see FPA_PF_MAP() and SSO_PF_MAP(). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_gmctl_s cn; */
};
typedef union bdk_rad_gmctl bdk_rad_gmctl_t;

#define BDK_RAD_GMCTL BDK_RAD_GMCTL_FUNC()
static inline uint64_t BDK_RAD_GMCTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_GMCTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000090ll;
    __bdk_csr_fatal("RAD_GMCTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_GMCTL bdk_rad_gmctl_t
#define bustype_BDK_RAD_GMCTL BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_GMCTL "RAD_GMCTL"
#define device_bar_BDK_RAD_GMCTL 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_GMCTL 0
#define arguments_BDK_RAD_GMCTL -1,-1,-1,-1

/**
 * Register (NCB) rad_mem_debug0
 *
 * INTERNAL: RAD Memory Debug0 Register
 *
 * This CSR is a memory of 32 entries, and thus RAD_REG_READ_IDX must be written before
 * any CSR read operations to this address can be performed. A read of any entry that has not
 * been previously written is illegal and will result in unpredictable CSR read data.
 */
union bdk_rad_mem_debug0
{
    uint64_t u;
    struct bdk_rad_mem_debug0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t iword                 : 64; /**< [ 63:  0](RO/H) IWord */
#else /* Word 0 - Little Endian */
        uint64_t iword                 : 64; /**< [ 63:  0](RO/H) IWord */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_mem_debug0_s cn; */
};
typedef union bdk_rad_mem_debug0 bdk_rad_mem_debug0_t;

#define BDK_RAD_MEM_DEBUG0 BDK_RAD_MEM_DEBUG0_FUNC()
static inline uint64_t BDK_RAD_MEM_DEBUG0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_MEM_DEBUG0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000001000ll;
    __bdk_csr_fatal("RAD_MEM_DEBUG0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_MEM_DEBUG0 bdk_rad_mem_debug0_t
#define bustype_BDK_RAD_MEM_DEBUG0 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_MEM_DEBUG0 "RAD_MEM_DEBUG0"
#define device_bar_BDK_RAD_MEM_DEBUG0 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_MEM_DEBUG0 0
#define arguments_BDK_RAD_MEM_DEBUG0 -1,-1,-1,-1

/**
 * Register (NCB) rad_mem_debug1
 *
 * INTERNAL: RAD Memory Debug1 Register
 *
 * This CSR is a memory of 256 entries, and thus, RAD_REG_READ_IDX must be written before
 * any CSR read operations to this address can be performed. A read of any entry that has not
 * been previously written is illegal and will result in unpredictable CSR read data.
 */
union bdk_rad_mem_debug1
{
    uint64_t u;
    struct bdk_rad_mem_debug1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t p_dat                 : 64; /**< [ 63:  0](RO/H) P data */
#else /* Word 0 - Little Endian */
        uint64_t p_dat                 : 64; /**< [ 63:  0](RO/H) P data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_mem_debug1_s cn; */
};
typedef union bdk_rad_mem_debug1 bdk_rad_mem_debug1_t;

#define BDK_RAD_MEM_DEBUG1 BDK_RAD_MEM_DEBUG1_FUNC()
static inline uint64_t BDK_RAD_MEM_DEBUG1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_MEM_DEBUG1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000001008ll;
    __bdk_csr_fatal("RAD_MEM_DEBUG1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_MEM_DEBUG1 bdk_rad_mem_debug1_t
#define bustype_BDK_RAD_MEM_DEBUG1 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_MEM_DEBUG1 "RAD_MEM_DEBUG1"
#define device_bar_BDK_RAD_MEM_DEBUG1 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_MEM_DEBUG1 0
#define arguments_BDK_RAD_MEM_DEBUG1 -1,-1,-1,-1

/**
 * Register (NCB) rad_mem_debug2
 *
 * INTERNAL: RAD Memory Debug2 Register
 *
 * This CSR is a memory of 256 entries, and thus, RAD_REG_READ_IDX must be written before
 * any CSR read operations to this address can be performed. A read of any entry that has not
 * been previously written is illegal and will result in unpredictable CSR read data.
 */
union bdk_rad_mem_debug2
{
    uint64_t u;
    struct bdk_rad_mem_debug2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t q_dat                 : 64; /**< [ 63:  0](RO/H) Q data */
#else /* Word 0 - Little Endian */
        uint64_t q_dat                 : 64; /**< [ 63:  0](RO/H) Q data */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_mem_debug2_s cn; */
};
typedef union bdk_rad_mem_debug2 bdk_rad_mem_debug2_t;

#define BDK_RAD_MEM_DEBUG2 BDK_RAD_MEM_DEBUG2_FUNC()
static inline uint64_t BDK_RAD_MEM_DEBUG2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_MEM_DEBUG2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000001010ll;
    __bdk_csr_fatal("RAD_MEM_DEBUG2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_MEM_DEBUG2 bdk_rad_mem_debug2_t
#define bustype_BDK_RAD_MEM_DEBUG2 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_MEM_DEBUG2 "RAD_MEM_DEBUG2"
#define device_bar_BDK_RAD_MEM_DEBUG2 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_MEM_DEBUG2 0
#define arguments_BDK_RAD_MEM_DEBUG2 -1,-1,-1,-1

/**
 * Register (NCB) rad_pf_mbox_ena_w1c#
 *
 * RAD PF Mailbox Enable Clear Registers
 * This register clears interrupt enable bits.
 */
union bdk_rad_pf_mbox_ena_w1cx
{
    uint64_t u;
    struct bdk_rad_pf_mbox_ena_w1cx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RAD_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RAD_PF_MBOX_INT(0)[MBOX]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_pf_mbox_ena_w1cx_s cn; */
};
typedef union bdk_rad_pf_mbox_ena_w1cx bdk_rad_pf_mbox_ena_w1cx_t;

static inline uint64_t BDK_RAD_PF_MBOX_ENA_W1CX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_PF_MBOX_ENA_W1CX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870000000440ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_PF_MBOX_ENA_W1CX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_PF_MBOX_ENA_W1CX(a) bdk_rad_pf_mbox_ena_w1cx_t
#define bustype_BDK_RAD_PF_MBOX_ENA_W1CX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_PF_MBOX_ENA_W1CX(a) "RAD_PF_MBOX_ENA_W1CX"
#define device_bar_BDK_RAD_PF_MBOX_ENA_W1CX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_PF_MBOX_ENA_W1CX(a) (a)
#define arguments_BDK_RAD_PF_MBOX_ENA_W1CX(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_pf_mbox_ena_w1s#
 *
 * RAD PF Mailbox Enable Set Registers
 * This register sets interrupt enable bits.
 */
union bdk_rad_pf_mbox_ena_w1sx
{
    uint64_t u;
    struct bdk_rad_pf_mbox_ena_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RAD_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RAD_PF_MBOX_INT(0)[MBOX]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_pf_mbox_ena_w1sx_s cn; */
};
typedef union bdk_rad_pf_mbox_ena_w1sx bdk_rad_pf_mbox_ena_w1sx_t;

static inline uint64_t BDK_RAD_PF_MBOX_ENA_W1SX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_PF_MBOX_ENA_W1SX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870000000460ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_PF_MBOX_ENA_W1SX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_PF_MBOX_ENA_W1SX(a) bdk_rad_pf_mbox_ena_w1sx_t
#define bustype_BDK_RAD_PF_MBOX_ENA_W1SX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_PF_MBOX_ENA_W1SX(a) "RAD_PF_MBOX_ENA_W1SX"
#define device_bar_BDK_RAD_PF_MBOX_ENA_W1SX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_PF_MBOX_ENA_W1SX(a) (a)
#define arguments_BDK_RAD_PF_MBOX_ENA_W1SX(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_pf_mbox_int#
 *
 * RAD PF Mailbox Interrupt Registers
 */
union bdk_rad_pf_mbox_intx
{
    uint64_t u;
    struct bdk_rad_pf_mbox_intx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) One interrupt bit per VF. Each bit is set when the associated
                                                                 RAD_VF(0)_PF_MBOX(1) is written.
                                                                 Bits corresponding to unimplemented VFs (above bit 0) are never set by hardware. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1C/H) One interrupt bit per VF. Each bit is set when the associated
                                                                 RAD_VF(0)_PF_MBOX(1) is written.
                                                                 Bits corresponding to unimplemented VFs (above bit 0) are never set by hardware. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_pf_mbox_intx_s cn; */
};
typedef union bdk_rad_pf_mbox_intx bdk_rad_pf_mbox_intx_t;

static inline uint64_t BDK_RAD_PF_MBOX_INTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_PF_MBOX_INTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870000000400ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_PF_MBOX_INTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_PF_MBOX_INTX(a) bdk_rad_pf_mbox_intx_t
#define bustype_BDK_RAD_PF_MBOX_INTX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_PF_MBOX_INTX(a) "RAD_PF_MBOX_INTX"
#define device_bar_BDK_RAD_PF_MBOX_INTX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_PF_MBOX_INTX(a) (a)
#define arguments_BDK_RAD_PF_MBOX_INTX(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_pf_mbox_int_w1s#
 *
 * RAD PF Mailbox Interrupt Set Registers
 * This register sets interrupt bits.
 */
union bdk_rad_pf_mbox_int_w1sx
{
    uint64_t u;
    struct bdk_rad_pf_mbox_int_w1sx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RAD_PF_MBOX_INT(0)[MBOX]. */
#else /* Word 0 - Little Endian */
        uint64_t mbox                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RAD_PF_MBOX_INT(0)[MBOX]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_pf_mbox_int_w1sx_s cn; */
};
typedef union bdk_rad_pf_mbox_int_w1sx bdk_rad_pf_mbox_int_w1sx_t;

static inline uint64_t BDK_RAD_PF_MBOX_INT_W1SX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_PF_MBOX_INT_W1SX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870000000420ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_PF_MBOX_INT_W1SX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_PF_MBOX_INT_W1SX(a) bdk_rad_pf_mbox_int_w1sx_t
#define bustype_BDK_RAD_PF_MBOX_INT_W1SX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_PF_MBOX_INT_W1SX(a) "RAD_PF_MBOX_INT_W1SX"
#define device_bar_BDK_RAD_PF_MBOX_INT_W1SX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_PF_MBOX_INT_W1SX(a) (a)
#define arguments_BDK_RAD_PF_MBOX_INT_W1SX(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_pf_msix_pba#
 *
 * RAD PF MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the RAD_PF_INT_VEC_E
 * enumeration.
 */
union bdk_rad_pf_msix_pbax
{
    uint64_t u;
    struct bdk_rad_pf_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RAD_PF_MSIX_VEC()_CTL, enumerated by
                                                                 RAD_PF_INT_VEC_E. Bits that have no associated RAD_PF_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RAD_PF_MSIX_VEC()_CTL, enumerated by
                                                                 RAD_PF_INT_VEC_E. Bits that have no associated RAD_PF_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_pf_msix_pbax_s cn; */
};
typedef union bdk_rad_pf_msix_pbax bdk_rad_pf_msix_pbax_t;

static inline uint64_t BDK_RAD_PF_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_PF_MSIX_PBAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870000ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_PF_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_PF_MSIX_PBAX(a) bdk_rad_pf_msix_pbax_t
#define bustype_BDK_RAD_PF_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_PF_MSIX_PBAX(a) "RAD_PF_MSIX_PBAX"
#define device_bar_BDK_RAD_PF_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_RAD_PF_MSIX_PBAX(a) (a)
#define arguments_BDK_RAD_PF_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_pf_msix_vec#_addr
 *
 * RAD PF MSI-X Vector Table Address Registers
 * This register is the MSI-X vector table, indexed by the RAD_PF_INT_VEC_E enumeration.
 */
union bdk_rad_pf_msix_vecx_addr
{
    uint64_t u;
    struct bdk_rad_pf_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's RAD_PF_MSIX_VEC()_ADDR, RAD_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of RAD_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_RAD_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's RAD_PF_MSIX_VEC()_ADDR, RAD_PF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of RAD_PF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_RAD_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_pf_msix_vecx_addr_s cn; */
};
typedef union bdk_rad_pf_msix_vecx_addr bdk_rad_pf_msix_vecx_addr_t;

static inline uint64_t BDK_RAD_PF_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_PF_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870000f00000ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_PF_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_PF_MSIX_VECX_ADDR(a) bdk_rad_pf_msix_vecx_addr_t
#define bustype_BDK_RAD_PF_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_PF_MSIX_VECX_ADDR(a) "RAD_PF_MSIX_VECX_ADDR"
#define device_bar_BDK_RAD_PF_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_RAD_PF_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_RAD_PF_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_pf_msix_vec#_ctl
 *
 * RAD PF MSI-X Vector Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the RAD_PF_INT_VEC_E enumeration.
 */
union bdk_rad_pf_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_rad_pf_msix_vecx_ctl_s
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
    /* struct bdk_rad_pf_msix_vecx_ctl_s cn; */
};
typedef union bdk_rad_pf_msix_vecx_ctl bdk_rad_pf_msix_vecx_ctl_t;

static inline uint64_t BDK_RAD_PF_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_PF_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870000f00008ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_PF_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_PF_MSIX_VECX_CTL(a) bdk_rad_pf_msix_vecx_ctl_t
#define bustype_BDK_RAD_PF_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_PF_MSIX_VECX_CTL(a) "RAD_PF_MSIX_VECX_CTL"
#define device_bar_BDK_RAD_PF_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_RAD_PF_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_RAD_PF_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_pf_vf#_mbox#
 *
 * RAD PF/VF Mailbox Registers
 */
union bdk_rad_pf_vfx_mboxx
{
    uint64_t u;
    struct bdk_rad_pf_vfx_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 RAD_VF()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing RAD_PF_VF(0)_MBOX(0) (but not
                                                                 RAD_VF(0)_PF_MBOX(0)) will set the corresponding
                                                                 RAD_VF()_INT[MBOX] which if appropriately enabled will send an interrupt
                                                                 to the VF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These PF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. Each corresponding VF may access the same storage using
                                                                 RAD_VF()_PF_MBOX(). MBOX(0) is typically used for PF to VF signaling, MBOX(1)
                                                                 for VF to PF. Writing RAD_PF_VF(0)_MBOX(0) (but not
                                                                 RAD_VF(0)_PF_MBOX(0)) will set the corresponding
                                                                 RAD_VF()_INT[MBOX] which if appropriately enabled will send an interrupt
                                                                 to the VF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_pf_vfx_mboxx_s cn; */
};
typedef union bdk_rad_pf_vfx_mboxx bdk_rad_pf_vfx_mboxx_t;

static inline uint64_t BDK_RAD_PF_VFX_MBOXX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_PF_VFX_MBOXX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=1)))
        return 0x870000002000ll + 0x10ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("RAD_PF_VFX_MBOXX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_PF_VFX_MBOXX(a,b) bdk_rad_pf_vfx_mboxx_t
#define bustype_BDK_RAD_PF_VFX_MBOXX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_PF_VFX_MBOXX(a,b) "RAD_PF_VFX_MBOXX"
#define device_bar_BDK_RAD_PF_VFX_MBOXX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_PF_VFX_MBOXX(a,b) (a)
#define arguments_BDK_RAD_PF_VFX_MBOXX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) rad_reg_bist_result
 *
 * RAD BIST Result Register
 * This register provides access to internal BIST results. Each bit is the BIST result of an
 * individual memory (per bit, 0 = pass, 1 = fail).
 */
union bdk_rad_reg_bist_result
{
    uint64_t u;
    struct bdk_rad_reg_bist_result_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t csr_msix              : 1;  /**< [  7:  7](RO/H) BIST result of the CSR MSIX memory.
                                                                 Internal:
                                                                 csr.msix_mem. */
        uint64_t csr_fifo              : 1;  /**< [  6:  6](RO/H) BIST result of the CSR FIFO memory.
                                                                 Internal:
                                                                 csr.csr_fifo. */
        uint64_t sta                   : 1;  /**< [  5:  5](RO/H) BIST result of the STA memories. */
        uint64_t ncb_oub               : 1;  /**< [  4:  4](RO/H) BIST result of the NCB OUB memories. */
        uint64_t ncb_inb               : 2;  /**< [  3:  2](RO/H) BIST result of the NCB INB memories. */
        uint64_t dat                   : 2;  /**< [  1:  0](RO/H) BIST result of the DAT memories. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 2;  /**< [  1:  0](RO/H) BIST result of the DAT memories. */
        uint64_t ncb_inb               : 2;  /**< [  3:  2](RO/H) BIST result of the NCB INB memories. */
        uint64_t ncb_oub               : 1;  /**< [  4:  4](RO/H) BIST result of the NCB OUB memories. */
        uint64_t sta                   : 1;  /**< [  5:  5](RO/H) BIST result of the STA memories. */
        uint64_t csr_fifo              : 1;  /**< [  6:  6](RO/H) BIST result of the CSR FIFO memory.
                                                                 Internal:
                                                                 csr.csr_fifo. */
        uint64_t csr_msix              : 1;  /**< [  7:  7](RO/H) BIST result of the CSR MSIX memory.
                                                                 Internal:
                                                                 csr.msix_mem. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_bist_result_s cn; */
};
typedef union bdk_rad_reg_bist_result bdk_rad_reg_bist_result_t;

#define BDK_RAD_REG_BIST_RESULT BDK_RAD_REG_BIST_RESULT_FUNC()
static inline uint64_t BDK_RAD_REG_BIST_RESULT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_BIST_RESULT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000080ll;
    __bdk_csr_fatal("RAD_REG_BIST_RESULT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_BIST_RESULT bdk_rad_reg_bist_result_t
#define bustype_BDK_RAD_REG_BIST_RESULT BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_BIST_RESULT "RAD_REG_BIST_RESULT"
#define device_bar_BDK_RAD_REG_BIST_RESULT 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_BIST_RESULT 0
#define arguments_BDK_RAD_REG_BIST_RESULT -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_cmd_buf
 *
 * RAD Command Buffer Register
 * This register sets the command-buffer parameters.
 */
union bdk_rad_reg_cmd_buf
{
    uint64_t u;
    struct bdk_rad_reg_cmd_buf_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_60_63        : 4;
        uint64_t aura                  : 12; /**< [ 59: 48](R/W) Guest-aura for returning this queue's instruction-chunk buffers to FPA.
                                                                 Only used when [DFB] is clear.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and RAD_GMCTL[GMID] as valid. */
        uint64_t ldwb                  : 1;  /**< [ 47: 47](R/W) Load don't write back.

                                                                 0 = The hardware issues NCB regular load towards the cache, which will cause the
                                                                 line to be written back before being replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Partial cache line reads always use LDI. */
        uint64_t dfb                   : 1;  /**< [ 46: 46](R/W) Don't free instruction buffers.
                                                                 0 = When RAD reaches the end of an instruction chunk, that chunk will be freed
                                                                 to the FPA.
                                                                 1 = Instruction chunks are not freed to FPA. */
        uint64_t size                  : 13; /**< [ 45: 33](R/W) Number of uint64 words per command buffer segment. */
        uint64_t reserved_0_32         : 33;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_32         : 33;
        uint64_t size                  : 13; /**< [ 45: 33](R/W) Number of uint64 words per command buffer segment. */
        uint64_t dfb                   : 1;  /**< [ 46: 46](R/W) Don't free instruction buffers.
                                                                 0 = When RAD reaches the end of an instruction chunk, that chunk will be freed
                                                                 to the FPA.
                                                                 1 = Instruction chunks are not freed to FPA. */
        uint64_t ldwb                  : 1;  /**< [ 47: 47](R/W) Load don't write back.

                                                                 0 = The hardware issues NCB regular load towards the cache, which will cause the
                                                                 line to be written back before being replaced.

                                                                 1 = The hardware issues NCB LDWB read-and-invalidate command towards the cache
                                                                 when fetching the last word of instructions; as a result the line will not be
                                                                 written back when replaced.  This improves performance, but software must not
                                                                 read the instructions after they are posted to the hardware.

                                                                 Partial cache line reads always use LDI. */
        uint64_t aura                  : 12; /**< [ 59: 48](R/W) Guest-aura for returning this queue's instruction-chunk buffers to FPA.
                                                                 Only used when [DFB] is clear.
                                                                 For the FPA to not discard the request, FPA_PF_MAP() must map
                                                                 [AURA] and RAD_GMCTL[GMID] as valid. */
        uint64_t reserved_60_63        : 4;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_cmd_buf_s cn; */
};
typedef union bdk_rad_reg_cmd_buf bdk_rad_reg_cmd_buf_t;

#define BDK_RAD_REG_CMD_BUF BDK_RAD_REG_CMD_BUF_FUNC()
static inline uint64_t BDK_RAD_REG_CMD_BUF_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_CMD_BUF_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000008ll;
    __bdk_csr_fatal("RAD_REG_CMD_BUF", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_CMD_BUF bdk_rad_reg_cmd_buf_t
#define bustype_BDK_RAD_REG_CMD_BUF BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_CMD_BUF "RAD_REG_CMD_BUF"
#define device_bar_BDK_RAD_REG_CMD_BUF 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_CMD_BUF 0
#define arguments_BDK_RAD_REG_CMD_BUF -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_ctl
 *
 * RAD Control Register
 */
union bdk_rad_reg_ctl
{
    uint64_t u;
    struct bdk_rad_reg_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t inst_be               : 1;  /**< [  7:  7](R/W) Instruction/response structures (RAD_CWORD_S, RAD_IWORD_S, RAD_OWORD_S, RAD_RESP_S,
                                                                 RAD_NZDIST_S) are big-endian. */
        uint64_t reserved_6            : 1;
        uint64_t max_read              : 4;  /**< [  5:  2](R/W) Maximum number of outstanding data read commands as a throttle to control IOB
                                                                 usage. Values greater than 0x8 are illegal. */
        uint64_t store_be              : 1;  /**< [  1:  1](R/W) Force STORE0 byte write address to big-endian. Generally, this is not changed as data is
                                                                 byte invariant. */
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1/H) Reset one-shot pulse (lasts for 4 cycles). */
#else /* Word 0 - Little Endian */
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1/H) Reset one-shot pulse (lasts for 4 cycles). */
        uint64_t store_be              : 1;  /**< [  1:  1](R/W) Force STORE0 byte write address to big-endian. Generally, this is not changed as data is
                                                                 byte invariant. */
        uint64_t max_read              : 4;  /**< [  5:  2](R/W) Maximum number of outstanding data read commands as a throttle to control IOB
                                                                 usage. Values greater than 0x8 are illegal. */
        uint64_t reserved_6            : 1;
        uint64_t inst_be               : 1;  /**< [  7:  7](R/W) Instruction/response structures (RAD_CWORD_S, RAD_IWORD_S, RAD_OWORD_S, RAD_RESP_S,
                                                                 RAD_NZDIST_S) are big-endian. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_ctl_s cn; */
};
typedef union bdk_rad_reg_ctl bdk_rad_reg_ctl_t;

#define BDK_RAD_REG_CTL BDK_RAD_REG_CTL_FUNC()
static inline uint64_t BDK_RAD_REG_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000000ll;
    __bdk_csr_fatal("RAD_REG_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_CTL bdk_rad_reg_ctl_t
#define bustype_BDK_RAD_REG_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_CTL "RAD_REG_CTL"
#define device_bar_BDK_RAD_REG_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_CTL 0
#define arguments_BDK_RAD_REG_CTL -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug0
 *
 * INTERNAL: RAD Debug0 Register
 */
union bdk_rad_reg_debug0
{
    uint64_t u;
    struct bdk_rad_reg_debug0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_57_63        : 7;
        uint64_t loop                  : 25; /**< [ 56: 32](RO/H) Loop offset */
        uint64_t reserved_22_31        : 10;
        uint64_t iridx                 : 6;  /**< [ 21: 16](RO/H) IWords read index */
        uint64_t reserved_14_15        : 2;
        uint64_t iwidx                 : 6;  /**< [ 13:  8](RO/H) IWords write index */
        uint64_t owordqv               : 1;  /**< [  7:  7](RO/H) Valid for OWORDQ */
        uint64_t owordpv               : 1;  /**< [  6:  6](RO/H) Valid for OWORDP */
        uint64_t commit                : 1;  /**< [  5:  5](RO/H) Waiting for write commit */
        uint64_t state                 : 5;  /**< [  4:  0](RO/H) Main state */
#else /* Word 0 - Little Endian */
        uint64_t state                 : 5;  /**< [  4:  0](RO/H) Main state */
        uint64_t commit                : 1;  /**< [  5:  5](RO/H) Waiting for write commit */
        uint64_t owordpv               : 1;  /**< [  6:  6](RO/H) Valid for OWORDP */
        uint64_t owordqv               : 1;  /**< [  7:  7](RO/H) Valid for OWORDQ */
        uint64_t iwidx                 : 6;  /**< [ 13:  8](RO/H) IWords write index */
        uint64_t reserved_14_15        : 2;
        uint64_t iridx                 : 6;  /**< [ 21: 16](RO/H) IWords read index */
        uint64_t reserved_22_31        : 10;
        uint64_t loop                  : 25; /**< [ 56: 32](RO/H) Loop offset */
        uint64_t reserved_57_63        : 7;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug0_s cn; */
};
typedef union bdk_rad_reg_debug0 bdk_rad_reg_debug0_t;

#define BDK_RAD_REG_DEBUG0 BDK_RAD_REG_DEBUG0_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000100ll;
    __bdk_csr_fatal("RAD_REG_DEBUG0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG0 bdk_rad_reg_debug0_t
#define bustype_BDK_RAD_REG_DEBUG0 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG0 "RAD_REG_DEBUG0"
#define device_bar_BDK_RAD_REG_DEBUG0 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG0 0
#define arguments_BDK_RAD_REG_DEBUG0 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug1
 *
 * INTERNAL: RAD Debug1 Register
 */
union bdk_rad_reg_debug1
{
    uint64_t u;
    struct bdk_rad_reg_debug1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cword                 : 64; /**< [ 63:  0](RO/H) CWord */
#else /* Word 0 - Little Endian */
        uint64_t cword                 : 64; /**< [ 63:  0](RO/H) CWord */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug1_s cn; */
};
typedef union bdk_rad_reg_debug1 bdk_rad_reg_debug1_t;

#define BDK_RAD_REG_DEBUG1 BDK_RAD_REG_DEBUG1_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000108ll;
    __bdk_csr_fatal("RAD_REG_DEBUG1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG1 bdk_rad_reg_debug1_t
#define bustype_BDK_RAD_REG_DEBUG1 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG1 "RAD_REG_DEBUG1"
#define device_bar_BDK_RAD_REG_DEBUG1 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG1 0
#define arguments_BDK_RAD_REG_DEBUG1 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug10
 *
 * INTERNAL: RAD Debug10 Register
 */
union bdk_rad_reg_debug10
{
    uint64_t u;
    struct bdk_rad_reg_debug10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t flags                 : 8;  /**< [ 63: 56](RO/H) OCTL flags */
        uint64_t size                  : 16; /**< [ 55: 40](RO/H) OCTL size in bytes */
        uint64_t ptr                   : 40; /**< [ 39:  0](RO/H) OCTL pointer (address [41:40] not included) */
#else /* Word 0 - Little Endian */
        uint64_t ptr                   : 40; /**< [ 39:  0](RO/H) OCTL pointer (address [41:40] not included) */
        uint64_t size                  : 16; /**< [ 55: 40](RO/H) OCTL size in bytes */
        uint64_t flags                 : 8;  /**< [ 63: 56](RO/H) OCTL flags */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug10_s cn; */
};
typedef union bdk_rad_reg_debug10 bdk_rad_reg_debug10_t;

#define BDK_RAD_REG_DEBUG10 BDK_RAD_REG_DEBUG10_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG10_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG10_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000150ll;
    __bdk_csr_fatal("RAD_REG_DEBUG10", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG10 bdk_rad_reg_debug10_t
#define bustype_BDK_RAD_REG_DEBUG10 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG10 "RAD_REG_DEBUG10"
#define device_bar_BDK_RAD_REG_DEBUG10 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG10 0
#define arguments_BDK_RAD_REG_DEBUG10 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug11
 *
 * INTERNAL: RAD Debug11 Register
 */
union bdk_rad_reg_debug11
{
    uint64_t u;
    struct bdk_rad_reg_debug11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t q                     : 1;  /**< [ 12: 12](RO/H) OCTL Q flag */
        uint64_t p                     : 1;  /**< [ 11: 11](RO/H) OCTL P flag */
        uint64_t wc                    : 1;  /**< [ 10: 10](RO/H) OCTL write commit flag */
        uint64_t eod                   : 1;  /**< [  9:  9](RO/H) OCTL EOD flag */
        uint64_t sod                   : 1;  /**< [  8:  8](RO/H) OCTL SOD flag */
        uint64_t idx                   : 8;  /**< [  7:  0](RO/H) OCTL index */
#else /* Word 0 - Little Endian */
        uint64_t idx                   : 8;  /**< [  7:  0](RO/H) OCTL index */
        uint64_t sod                   : 1;  /**< [  8:  8](RO/H) OCTL SOD flag */
        uint64_t eod                   : 1;  /**< [  9:  9](RO/H) OCTL EOD flag */
        uint64_t wc                    : 1;  /**< [ 10: 10](RO/H) OCTL write commit flag */
        uint64_t p                     : 1;  /**< [ 11: 11](RO/H) OCTL P flag */
        uint64_t q                     : 1;  /**< [ 12: 12](RO/H) OCTL Q flag */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug11_s cn; */
};
typedef union bdk_rad_reg_debug11 bdk_rad_reg_debug11_t;

#define BDK_RAD_REG_DEBUG11 BDK_RAD_REG_DEBUG11_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG11_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG11_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000158ll;
    __bdk_csr_fatal("RAD_REG_DEBUG11", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG11 bdk_rad_reg_debug11_t
#define bustype_BDK_RAD_REG_DEBUG11 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG11 "RAD_REG_DEBUG11"
#define device_bar_BDK_RAD_REG_DEBUG11 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG11 0
#define arguments_BDK_RAD_REG_DEBUG11 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug12
 *
 * INTERNAL: RAD Debug12 Register
 */
union bdk_rad_reg_debug12
{
    uint64_t u;
    struct bdk_rad_reg_debug12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_15_63        : 49;
        uint64_t asserts               : 15; /**< [ 14:  0](RO/H) Various assertion checks */
#else /* Word 0 - Little Endian */
        uint64_t asserts               : 15; /**< [ 14:  0](RO/H) Various assertion checks */
        uint64_t reserved_15_63        : 49;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug12_s cn; */
};
typedef union bdk_rad_reg_debug12 bdk_rad_reg_debug12_t;

#define BDK_RAD_REG_DEBUG12 BDK_RAD_REG_DEBUG12_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG12_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG12_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000160ll;
    __bdk_csr_fatal("RAD_REG_DEBUG12", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG12 bdk_rad_reg_debug12_t
#define bustype_BDK_RAD_REG_DEBUG12 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG12 "RAD_REG_DEBUG12"
#define device_bar_BDK_RAD_REG_DEBUG12 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG12 0
#define arguments_BDK_RAD_REG_DEBUG12 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug2
 *
 * INTERNAL: RAD Debug2 Register
 */
union bdk_rad_reg_debug2
{
    uint64_t u;
    struct bdk_rad_reg_debug2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t owordp                : 64; /**< [ 63:  0](RO/H) OWordP */
#else /* Word 0 - Little Endian */
        uint64_t owordp                : 64; /**< [ 63:  0](RO/H) OWordP */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug2_s cn; */
};
typedef union bdk_rad_reg_debug2 bdk_rad_reg_debug2_t;

#define BDK_RAD_REG_DEBUG2 BDK_RAD_REG_DEBUG2_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000110ll;
    __bdk_csr_fatal("RAD_REG_DEBUG2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG2 bdk_rad_reg_debug2_t
#define bustype_BDK_RAD_REG_DEBUG2 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG2 "RAD_REG_DEBUG2"
#define device_bar_BDK_RAD_REG_DEBUG2 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG2 0
#define arguments_BDK_RAD_REG_DEBUG2 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug3
 *
 * INTERNAL: RAD Debug3 Register
 */
union bdk_rad_reg_debug3
{
    uint64_t u;
    struct bdk_rad_reg_debug3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t owordq                : 64; /**< [ 63:  0](RO/H) OWordQ */
#else /* Word 0 - Little Endian */
        uint64_t owordq                : 64; /**< [ 63:  0](RO/H) OWordQ */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug3_s cn; */
};
typedef union bdk_rad_reg_debug3 bdk_rad_reg_debug3_t;

#define BDK_RAD_REG_DEBUG3 BDK_RAD_REG_DEBUG3_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG3_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000118ll;
    __bdk_csr_fatal("RAD_REG_DEBUG3", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG3 bdk_rad_reg_debug3_t
#define bustype_BDK_RAD_REG_DEBUG3 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG3 "RAD_REG_DEBUG3"
#define device_bar_BDK_RAD_REG_DEBUG3 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG3 0
#define arguments_BDK_RAD_REG_DEBUG3 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug4
 *
 * INTERNAL: RAD Debug4 Register
 */
union bdk_rad_reg_debug4
{
    uint64_t u;
    struct bdk_rad_reg_debug4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t rword                 : 64; /**< [ 63:  0](RO/H) RWord */
#else /* Word 0 - Little Endian */
        uint64_t rword                 : 64; /**< [ 63:  0](RO/H) RWord */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug4_s cn; */
};
typedef union bdk_rad_reg_debug4 bdk_rad_reg_debug4_t;

#define BDK_RAD_REG_DEBUG4 BDK_RAD_REG_DEBUG4_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG4_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG4_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000120ll;
    __bdk_csr_fatal("RAD_REG_DEBUG4", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG4 bdk_rad_reg_debug4_t
#define bustype_BDK_RAD_REG_DEBUG4 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG4 "RAD_REG_DEBUG4"
#define device_bar_BDK_RAD_REG_DEBUG4 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG4 0
#define arguments_BDK_RAD_REG_DEBUG4 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug5
 *
 * INTERNAL: RAD Debug5 Register
 */
union bdk_rad_reg_debug5
{
    uint64_t u;
    struct bdk_rad_reg_debug5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t niropc7               : 3;  /**< [ 52: 50](RO/H) IOBI ropc (stage7 grant) */
        uint64_t nirque7               : 2;  /**< [ 49: 48](RO/H) IOBI rque (stage7 grant) */
        uint64_t nirval7               : 5;  /**< [ 47: 43](RO/H) IOBI rval (stage7 grant) */
        uint64_t niropc6               : 3;  /**< [ 42: 40](RO/H) IOBI ropc (stage6 arb) */
        uint64_t nirque6               : 2;  /**< [ 39: 38](RO/H) IOBI rque (stage6 arb) */
        uint64_t nirarb6               : 1;  /**< [ 37: 37](RO/H) IOBI rarb (stage6 arb) */
        uint64_t nirval6               : 5;  /**< [ 36: 32](RO/H) IOBI rval (stage6 arb) */
        uint64_t niridx1               : 4;  /**< [ 31: 28](RO/H) IOBI ridx1 */
        uint64_t niwidx1               : 4;  /**< [ 27: 24](RO/H) IOBI widx1 */
        uint64_t niridx0               : 4;  /**< [ 23: 20](RO/H) IOBI ridx0 */
        uint64_t niwidx0               : 4;  /**< [ 19: 16](RO/H) IOBI widx0 */
        uint64_t wccreds               : 2;  /**< [ 15: 14](RO/H) WC credits */
        uint64_t fpacreds              : 2;  /**< [ 13: 12](RO/H) FPA credits */
        uint64_t reserved_10_11        : 2;
        uint64_t ssocreds              : 2;  /**< [  9:  8](RO/H) SSO credits */
        uint64_t n1creds               : 4;  /**< [  7:  4](RO/H) IOBI1 credits */
        uint64_t n0creds               : 4;  /**< [  3:  0](RO/H) IOBI0 credits */
#else /* Word 0 - Little Endian */
        uint64_t n0creds               : 4;  /**< [  3:  0](RO/H) IOBI0 credits */
        uint64_t n1creds               : 4;  /**< [  7:  4](RO/H) IOBI1 credits */
        uint64_t ssocreds              : 2;  /**< [  9:  8](RO/H) SSO credits */
        uint64_t reserved_10_11        : 2;
        uint64_t fpacreds              : 2;  /**< [ 13: 12](RO/H) FPA credits */
        uint64_t wccreds               : 2;  /**< [ 15: 14](RO/H) WC credits */
        uint64_t niwidx0               : 4;  /**< [ 19: 16](RO/H) IOBI widx0 */
        uint64_t niridx0               : 4;  /**< [ 23: 20](RO/H) IOBI ridx0 */
        uint64_t niwidx1               : 4;  /**< [ 27: 24](RO/H) IOBI widx1 */
        uint64_t niridx1               : 4;  /**< [ 31: 28](RO/H) IOBI ridx1 */
        uint64_t nirval6               : 5;  /**< [ 36: 32](RO/H) IOBI rval (stage6 arb) */
        uint64_t nirarb6               : 1;  /**< [ 37: 37](RO/H) IOBI rarb (stage6 arb) */
        uint64_t nirque6               : 2;  /**< [ 39: 38](RO/H) IOBI rque (stage6 arb) */
        uint64_t niropc6               : 3;  /**< [ 42: 40](RO/H) IOBI ropc (stage6 arb) */
        uint64_t nirval7               : 5;  /**< [ 47: 43](RO/H) IOBI rval (stage7 grant) */
        uint64_t nirque7               : 2;  /**< [ 49: 48](RO/H) IOBI rque (stage7 grant) */
        uint64_t niropc7               : 3;  /**< [ 52: 50](RO/H) IOBI ropc (stage7 grant) */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug5_s cn; */
};
typedef union bdk_rad_reg_debug5 bdk_rad_reg_debug5_t;

#define BDK_RAD_REG_DEBUG5 BDK_RAD_REG_DEBUG5_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG5_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG5_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000128ll;
    __bdk_csr_fatal("RAD_REG_DEBUG5", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG5 bdk_rad_reg_debug5_t
#define bustype_BDK_RAD_REG_DEBUG5 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG5 "RAD_REG_DEBUG5"
#define device_bar_BDK_RAD_REG_DEBUG5 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG5 0
#define arguments_BDK_RAD_REG_DEBUG5 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug6
 *
 * INTERNAL: RAD Debug6 Register
 */
union bdk_rad_reg_debug6
{
    uint64_t u;
    struct bdk_rad_reg_debug6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 8;  /**< [ 63: 56](RO/H) CCTL count [7:0] in bytes */
        uint64_t size                  : 16; /**< [ 55: 40](RO/H) CCTL size in bytes */
        uint64_t ptr                   : 40; /**< [ 39:  0](RO/H) CCTL pointer (address [41:40] not included) */
#else /* Word 0 - Little Endian */
        uint64_t ptr                   : 40; /**< [ 39:  0](RO/H) CCTL pointer (address [41:40] not included) */
        uint64_t size                  : 16; /**< [ 55: 40](RO/H) CCTL size in bytes */
        uint64_t cnt                   : 8;  /**< [ 63: 56](RO/H) CCTL count [7:0] in bytes */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug6_s cn; */
};
typedef union bdk_rad_reg_debug6 bdk_rad_reg_debug6_t;

#define BDK_RAD_REG_DEBUG6 BDK_RAD_REG_DEBUG6_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG6_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG6_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000130ll;
    __bdk_csr_fatal("RAD_REG_DEBUG6", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG6 bdk_rad_reg_debug6_t
#define bustype_BDK_RAD_REG_DEBUG6 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG6 "RAD_REG_DEBUG6"
#define device_bar_BDK_RAD_REG_DEBUG6 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG6 0
#define arguments_BDK_RAD_REG_DEBUG6 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug7
 *
 * INTERNAL: RAD Debug7 Register
 */
union bdk_rad_reg_debug7
{
    uint64_t u;
    struct bdk_rad_reg_debug7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_15_63        : 49;
        uint64_t cnt                   : 15; /**< [ 14:  0](RO/H) CCTL count [22:8] in bytes */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 15; /**< [ 14:  0](RO/H) CCTL count [22:8] in bytes */
        uint64_t reserved_15_63        : 49;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug7_s cn; */
};
typedef union bdk_rad_reg_debug7 bdk_rad_reg_debug7_t;

#define BDK_RAD_REG_DEBUG7 BDK_RAD_REG_DEBUG7_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG7_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG7_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000138ll;
    __bdk_csr_fatal("RAD_REG_DEBUG7", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG7 bdk_rad_reg_debug7_t
#define bustype_BDK_RAD_REG_DEBUG7 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG7 "RAD_REG_DEBUG7"
#define device_bar_BDK_RAD_REG_DEBUG7 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG7 0
#define arguments_BDK_RAD_REG_DEBUG7 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug8
 *
 * INTERNAL: RAD Debug8 Register
 */
union bdk_rad_reg_debug8
{
    uint64_t u;
    struct bdk_rad_reg_debug8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t flags                 : 8;  /**< [ 63: 56](RO/H) ICTL flags */
        uint64_t size                  : 16; /**< [ 55: 40](RO/H) ICTL size in bytes */
        uint64_t ptr                   : 40; /**< [ 39:  0](RO/H) ICTL pointer (address [41:40] not included) */
#else /* Word 0 - Little Endian */
        uint64_t ptr                   : 40; /**< [ 39:  0](RO/H) ICTL pointer (address [41:40] not included) */
        uint64_t size                  : 16; /**< [ 55: 40](RO/H) ICTL size in bytes */
        uint64_t flags                 : 8;  /**< [ 63: 56](RO/H) ICTL flags */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug8_s cn; */
};
typedef union bdk_rad_reg_debug8 bdk_rad_reg_debug8_t;

#define BDK_RAD_REG_DEBUG8 BDK_RAD_REG_DEBUG8_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG8_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG8_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000140ll;
    __bdk_csr_fatal("RAD_REG_DEBUG8", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG8 bdk_rad_reg_debug8_t
#define bustype_BDK_RAD_REG_DEBUG8 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG8 "RAD_REG_DEBUG8"
#define device_bar_BDK_RAD_REG_DEBUG8 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG8 0
#define arguments_BDK_RAD_REG_DEBUG8 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_debug9
 *
 * INTERNAL: RAD Debug9 Register
 */
union bdk_rad_reg_debug9
{
    uint64_t u;
    struct bdk_rad_reg_debug9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t eod                   : 1;  /**< [ 19: 19](RO/H) ICTL eod flag */
        uint64_t ini                   : 1;  /**< [ 18: 18](RO/H) ICTL init flag */
        uint64_t q                     : 1;  /**< [ 17: 17](RO/H) ICTL q enable */
        uint64_t p                     : 1;  /**< [ 16: 16](RO/H) ICTL p enable */
        uint64_t mul                   : 8;  /**< [ 15:  8](RO/H) ICTL multiplier */
        uint64_t idx                   : 8;  /**< [  7:  0](RO/H) ICTL index */
#else /* Word 0 - Little Endian */
        uint64_t idx                   : 8;  /**< [  7:  0](RO/H) ICTL index */
        uint64_t mul                   : 8;  /**< [ 15:  8](RO/H) ICTL multiplier */
        uint64_t p                     : 1;  /**< [ 16: 16](RO/H) ICTL p enable */
        uint64_t q                     : 1;  /**< [ 17: 17](RO/H) ICTL q enable */
        uint64_t ini                   : 1;  /**< [ 18: 18](RO/H) ICTL init flag */
        uint64_t eod                   : 1;  /**< [ 19: 19](RO/H) ICTL eod flag */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_debug9_s cn; */
};
typedef union bdk_rad_reg_debug9 bdk_rad_reg_debug9_t;

#define BDK_RAD_REG_DEBUG9 BDK_RAD_REG_DEBUG9_FUNC()
static inline uint64_t BDK_RAD_REG_DEBUG9_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_DEBUG9_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000148ll;
    __bdk_csr_fatal("RAD_REG_DEBUG9", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_DEBUG9 bdk_rad_reg_debug9_t
#define bustype_BDK_RAD_REG_DEBUG9 BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_DEBUG9 "RAD_REG_DEBUG9"
#define device_bar_BDK_RAD_REG_DEBUG9 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_DEBUG9 0
#define arguments_BDK_RAD_REG_DEBUG9 -1,-1,-1,-1

/**
 * Register (NCB) rad_reg_read_idx
 *
 * INTERNAL: RAD Read Index Register
 *
 * This register is for debug purposes only. It provides the read index during a CSR read
 * operation to any of the CSRs that are physically stored as memories. The mnemonics for these
 * CSRs begin with the prefix RAD_MEM_.
 * IDX[7:0] is the read index. INC[7:0] is an increment that is added to IDX[7:0] after any
 * CSR read. The intended use is to initially write this CSR such that IDX = 0 and INC = 1. Then,
 * the entire contents of a CSR memory can be read with consecutive CSR read commands.
 */
union bdk_rad_reg_read_idx
{
    uint64_t u;
    struct bdk_rad_reg_read_idx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t inc                   : 8;  /**< [ 15:  8](R/W) Increment to add to the current index for the next index. */
        uint64_t idx                   : 8;  /**< [  7:  0](R/W/H) Index to use for next memory CSR read operation. */
#else /* Word 0 - Little Endian */
        uint64_t idx                   : 8;  /**< [  7:  0](R/W/H) Index to use for next memory CSR read operation. */
        uint64_t inc                   : 8;  /**< [ 15:  8](R/W) Increment to add to the current index for the next index. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_reg_read_idx_s cn; */
};
typedef union bdk_rad_reg_read_idx bdk_rad_reg_read_idx_t;

#define BDK_RAD_REG_READ_IDX BDK_RAD_REG_READ_IDX_FUNC()
static inline uint64_t BDK_RAD_REG_READ_IDX_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_REG_READ_IDX_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
        return 0x870000000018ll;
    __bdk_csr_fatal("RAD_REG_READ_IDX", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_REG_READ_IDX bdk_rad_reg_read_idx_t
#define bustype_BDK_RAD_REG_READ_IDX BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_REG_READ_IDX "RAD_REG_READ_IDX"
#define device_bar_BDK_RAD_REG_READ_IDX 0x0 /* PF_BAR0 */
#define busnum_BDK_RAD_REG_READ_IDX 0
#define arguments_BDK_RAD_REG_READ_IDX -1,-1,-1,-1

/**
 * Register (NCB) rad_vf#_int
 *
 * RAD VF Interrupt Clear Register
 */
union bdk_rad_vfx_int
{
    uint64_t u;
    struct bdk_rad_vfx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t dat_err               : 1;  /**< [  3:  3](R/W1C/H) An error was detected in memory access. */
        uint64_t mbox                  : 1;  /**< [  2:  2](R/W1C/H) PF to VF mailbox interrupt. Set when RAD_VF(0)_PF_MBOX(0)
                                                                 is written. */
        uint64_t done                  : 1;  /**< [  1:  1](RO/H) Done interrupt. See RAD_VQ()_DONE_CNT[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use RAD_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 RAD_VQ()_DONE_CNT[DONE]. */
        uint64_t doorbell              : 1;  /**< [  0:  0](R/W1C/H) Doorbell interrupt.  Set to indicate error that doorbell count has overflowed. */
#else /* Word 0 - Little Endian */
        uint64_t doorbell              : 1;  /**< [  0:  0](R/W1C/H) Doorbell interrupt.  Set to indicate error that doorbell count has overflowed. */
        uint64_t done                  : 1;  /**< [  1:  1](RO/H) Done interrupt. See RAD_VQ()_DONE_CNT[DONE].  Note this bit is read-only, to acknowledge
                                                                 interrupts use RAD_VQ()_DONE_ACK. To test interrupts, write nonzero to
                                                                 RAD_VQ()_DONE_CNT[DONE]. */
        uint64_t mbox                  : 1;  /**< [  2:  2](R/W1C/H) PF to VF mailbox interrupt. Set when RAD_VF(0)_PF_MBOX(0)
                                                                 is written. */
        uint64_t dat_err               : 1;  /**< [  3:  3](R/W1C/H) An error was detected in memory access. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vfx_int_s cn; */
};
typedef union bdk_rad_vfx_int bdk_rad_vfx_int_t;

static inline uint64_t BDK_RAD_VFX_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VFX_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020000100ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VFX_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VFX_INT(a) bdk_rad_vfx_int_t
#define bustype_BDK_RAD_VFX_INT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VFX_INT(a) "RAD_VFX_INT"
#define device_bar_BDK_RAD_VFX_INT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VFX_INT(a) (a)
#define arguments_BDK_RAD_VFX_INT(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_vf#_int_ena_w1c
 *
 * RAD VF Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_rad_vfx_int_ena_w1c
{
    uint64_t u;
    struct bdk_rad_vfx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t dat_err               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RAD_VF()_INT[ERR]. */
        uint64_t mbox                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RAD_VF()_INT[MBOX]. */
        uint64_t done                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RAD_VF()_INT[DONE]. */
        uint64_t doorbell              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RAD_VF()_INT[DOORBELL]. */
#else /* Word 0 - Little Endian */
        uint64_t doorbell              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RAD_VF()_INT[DOORBELL]. */
        uint64_t done                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for RAD_VF()_INT[DONE]. */
        uint64_t mbox                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for RAD_VF()_INT[MBOX]. */
        uint64_t dat_err               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for RAD_VF()_INT[ERR]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vfx_int_ena_w1c_s cn; */
};
typedef union bdk_rad_vfx_int_ena_w1c bdk_rad_vfx_int_ena_w1c_t;

static inline uint64_t BDK_RAD_VFX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VFX_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020000120ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VFX_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VFX_INT_ENA_W1C(a) bdk_rad_vfx_int_ena_w1c_t
#define bustype_BDK_RAD_VFX_INT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VFX_INT_ENA_W1C(a) "RAD_VFX_INT_ENA_W1C"
#define device_bar_BDK_RAD_VFX_INT_ENA_W1C(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VFX_INT_ENA_W1C(a) (a)
#define arguments_BDK_RAD_VFX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_vf#_int_ena_w1s
 *
 * RAD VF Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_rad_vfx_int_ena_w1s
{
    uint64_t u;
    struct bdk_rad_vfx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t dat_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RAD_VF()_INT[ERR]. */
        uint64_t mbox                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RAD_VF()_INT[MBOX]. */
        uint64_t done                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RAD_VF()_INT[DONE]. */
        uint64_t doorbell              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RAD_VF()_INT[DOORBELL]. */
#else /* Word 0 - Little Endian */
        uint64_t doorbell              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RAD_VF()_INT[DOORBELL]. */
        uint64_t done                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for RAD_VF()_INT[DONE]. */
        uint64_t mbox                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for RAD_VF()_INT[MBOX]. */
        uint64_t dat_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for RAD_VF()_INT[ERR]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vfx_int_ena_w1s_s cn; */
};
typedef union bdk_rad_vfx_int_ena_w1s bdk_rad_vfx_int_ena_w1s_t;

static inline uint64_t BDK_RAD_VFX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VFX_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020000130ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VFX_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VFX_INT_ENA_W1S(a) bdk_rad_vfx_int_ena_w1s_t
#define bustype_BDK_RAD_VFX_INT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VFX_INT_ENA_W1S(a) "RAD_VFX_INT_ENA_W1S"
#define device_bar_BDK_RAD_VFX_INT_ENA_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VFX_INT_ENA_W1S(a) (a)
#define arguments_BDK_RAD_VFX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_vf#_int_w1s
 *
 * RAD VF Interrupt Set Register
 */
union bdk_rad_vfx_int_w1s
{
    uint64_t u;
    struct bdk_rad_vfx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t dat_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RAD_VF()_INT[ERR]. */
        uint64_t mbox                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RAD_VF()_INT[MBOX]. */
        uint64_t done                  : 1;  /**< [  1:  1](RO/H) Done interrupt. See RAD_VQ()_DONE_CNT[DONE]. */
        uint64_t doorbell              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RAD_VF()_INT[DOORBELL]. */
#else /* Word 0 - Little Endian */
        uint64_t doorbell              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RAD_VF()_INT[DOORBELL]. */
        uint64_t done                  : 1;  /**< [  1:  1](RO/H) Done interrupt. See RAD_VQ()_DONE_CNT[DONE]. */
        uint64_t mbox                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets RAD_VF()_INT[MBOX]. */
        uint64_t dat_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets RAD_VF()_INT[ERR]. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vfx_int_w1s_s cn; */
};
typedef union bdk_rad_vfx_int_w1s bdk_rad_vfx_int_w1s_t;

static inline uint64_t BDK_RAD_VFX_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VFX_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020000110ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VFX_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VFX_INT_W1S(a) bdk_rad_vfx_int_w1s_t
#define bustype_BDK_RAD_VFX_INT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VFX_INT_W1S(a) "RAD_VFX_INT_W1S"
#define device_bar_BDK_RAD_VFX_INT_W1S(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VFX_INT_W1S(a) (a)
#define arguments_BDK_RAD_VFX_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_vf#_msix_pba#
 *
 * RAD VF MSI-X Pending-Bit-Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the RAD_VF_INT_VEC_E
 * enumeration.
 */
union bdk_rad_vfx_msix_pbax
{
    uint64_t u;
    struct bdk_rad_vfx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RAD_PF_MSIX_VEC()_CTL, enumerated by
                                                                 RAD_PF_INT_VEC_E. Bits that have no associated RAD_PF_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RAD_PF_MSIX_VEC()_CTL, enumerated by
                                                                 RAD_PF_INT_VEC_E. Bits that have no associated RAD_PF_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vfx_msix_pbax_s cn; */
};
typedef union bdk_rad_vfx_msix_pbax bdk_rad_vfx_msix_pbax_t;

static inline uint64_t BDK_RAD_VFX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VFX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b==0)))
        return 0x8700300f0000ll + 0x100000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("RAD_VFX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VFX_MSIX_PBAX(a,b) bdk_rad_vfx_msix_pbax_t
#define bustype_BDK_RAD_VFX_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VFX_MSIX_PBAX(a,b) "RAD_VFX_MSIX_PBAX"
#define device_bar_BDK_RAD_VFX_MSIX_PBAX(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_RAD_VFX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_RAD_VFX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) rad_vf#_msix_vec#_addr
 *
 * RAD VF MSI-X Vector-Table Address Registers
 * This register is the MSI-X vector table, indexed by the RAD_VF_INT_VEC_E enumeration.
 */
union bdk_rad_vfx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_rad_vfx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_RAD_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](RAZ) Secure vector. Zero as not supported on a per-vector basis for VFs; use
                                                                 PCCPF_RAD_VSEC_SCTL[MSIX_SEC] instead (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]). */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vfx_msix_vecx_addr_s cn; */
};
typedef union bdk_rad_vfx_msix_vecx_addr bdk_rad_vfx_msix_vecx_addr_t;

static inline uint64_t BDK_RAD_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VFX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b==0)))
        return 0x870030000000ll + 0x100000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("RAD_VFX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VFX_MSIX_VECX_ADDR(a,b) bdk_rad_vfx_msix_vecx_addr_t
#define bustype_BDK_RAD_VFX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VFX_MSIX_VECX_ADDR(a,b) "RAD_VFX_MSIX_VECX_ADDR"
#define device_bar_BDK_RAD_VFX_MSIX_VECX_ADDR(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_RAD_VFX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_RAD_VFX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) rad_vf#_msix_vec#_ctl
 *
 * RAD VF MSI-X Vector-Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the RAD_VF_INT_VEC_E enumeration.
 */
union bdk_rad_vfx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_rad_vfx_msix_vecx_ctl_s
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
    /* struct bdk_rad_vfx_msix_vecx_ctl_s cn; */
};
typedef union bdk_rad_vfx_msix_vecx_ctl bdk_rad_vfx_msix_vecx_ctl_t;

static inline uint64_t BDK_RAD_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VFX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b==0)))
        return 0x870030000008ll + 0x100000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("RAD_VFX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VFX_MSIX_VECX_CTL(a,b) bdk_rad_vfx_msix_vecx_ctl_t
#define bustype_BDK_RAD_VFX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VFX_MSIX_VECX_CTL(a,b) "RAD_VFX_MSIX_VECX_CTL"
#define device_bar_BDK_RAD_VFX_MSIX_VECX_CTL(a,b) 0x4 /* VF_BAR4 */
#define busnum_BDK_RAD_VFX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_RAD_VFX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) rad_vf#_pf_mbox#
 *
 * RAD VF/PF Mailbox Registers
 */
union bdk_rad_vfx_pf_mboxx
{
    uint64_t u;
    struct bdk_rad_vfx_pf_mboxx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using RAD_PF_VF()_MBOX(). MBOX(0) is
                                                                 typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 RAD_VF(0)_PF_MBOX(1) (but not RAD_PF_VF(0)_MBOX(1)) will set the
                                                                 corresponding RAD_PF_MBOX_INT() bit, which if appropriately enabled will send an
                                                                 interrupt to the PF. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Mailbox data. These VF registers access the 16-byte-per-VF VF/PF mailbox
                                                                 RAM. The PF may access the same storage using RAD_PF_VF()_MBOX(). MBOX(0) is
                                                                 typically used for PF to VF signaling, MBOX(1) for VF to PF. Writing
                                                                 RAD_VF(0)_PF_MBOX(1) (but not RAD_PF_VF(0)_MBOX(1)) will set the
                                                                 corresponding RAD_PF_MBOX_INT() bit, which if appropriately enabled will send an
                                                                 interrupt to the PF. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vfx_pf_mboxx_s cn; */
};
typedef union bdk_rad_vfx_pf_mboxx bdk_rad_vfx_pf_mboxx_t;

static inline uint64_t BDK_RAD_VFX_PF_MBOXX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VFX_PF_MBOXX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a==0) && (b<=1)))
        return 0x870020001000ll + 0x100000ll * ((a) & 0x0) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("RAD_VFX_PF_MBOXX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VFX_PF_MBOXX(a,b) bdk_rad_vfx_pf_mboxx_t
#define bustype_BDK_RAD_VFX_PF_MBOXX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VFX_PF_MBOXX(a,b) "RAD_VFX_PF_MBOXX"
#define device_bar_BDK_RAD_VFX_PF_MBOXX(a,b) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VFX_PF_MBOXX(a,b) (a)
#define arguments_BDK_RAD_VFX_PF_MBOXX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) rad_vq#_cmd_ptr
 *
 * RAD VF Queue Command Buffer Pointer Register
 * This register sets the command-buffer parameters.
 */
union bdk_rad_vqx_cmd_ptr
{
    uint64_t u;
    struct bdk_rad_vqx_cmd_ptr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) Initial command-buffer IOVA (128-byte aligned). Overwritten each time the
                                                                 command-buffer segment is exhausted. */
        uint64_t reserved_0_6          : 7;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_6          : 7;
        uint64_t ptr                   : 42; /**< [ 48:  7](R/W/H) Initial command-buffer IOVA (128-byte aligned). Overwritten each time the
                                                                 command-buffer segment is exhausted. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vqx_cmd_ptr_s cn; */
};
typedef union bdk_rad_vqx_cmd_ptr bdk_rad_vqx_cmd_ptr_t;

static inline uint64_t BDK_RAD_VQX_CMD_PTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VQX_CMD_PTR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020000020ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VQX_CMD_PTR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VQX_CMD_PTR(a) bdk_rad_vqx_cmd_ptr_t
#define bustype_BDK_RAD_VQX_CMD_PTR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VQX_CMD_PTR(a) "RAD_VQX_CMD_PTR"
#define device_bar_BDK_RAD_VQX_CMD_PTR(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VQX_CMD_PTR(a) (a)
#define arguments_BDK_RAD_VQX_CMD_PTR(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_vq#_done_ack
 *
 * RAD VF Queue Interrupt Done Ack Register
 */
union bdk_rad_vqx_done_ack
{
    uint64_t u;
    struct bdk_rad_vqx_done_ack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_21_63        : 43;
        uint64_t done_ack              : 21; /**< [ 20:  0](WO) Number of decrements to RAD_VQ()_DONE_CNT[DONE].

                                                                 Written by software to acknowledge interrupts.  If RAD_VQ()_DONE_CNT[DONE] is still
                                                                 nonzero the interrupt will be re-sent if the conditions described in
                                                                 RAD_VQ()_DONE_CNT[DONE] are satified. */
#else /* Word 0 - Little Endian */
        uint64_t done_ack              : 21; /**< [ 20:  0](WO) Number of decrements to RAD_VQ()_DONE_CNT[DONE].

                                                                 Written by software to acknowledge interrupts.  If RAD_VQ()_DONE_CNT[DONE] is still
                                                                 nonzero the interrupt will be re-sent if the conditions described in
                                                                 RAD_VQ()_DONE_CNT[DONE] are satified. */
        uint64_t reserved_21_63        : 43;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vqx_done_ack_s cn; */
};
typedef union bdk_rad_vqx_done_ack bdk_rad_vqx_done_ack_t;

static inline uint64_t BDK_RAD_VQX_DONE_ACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VQX_DONE_ACK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020000040ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VQX_DONE_ACK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VQX_DONE_ACK(a) bdk_rad_vqx_done_ack_t
#define bustype_BDK_RAD_VQX_DONE_ACK(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VQX_DONE_ACK(a) "RAD_VQX_DONE_ACK"
#define device_bar_BDK_RAD_VQX_DONE_ACK(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VQX_DONE_ACK(a) (a)
#define arguments_BDK_RAD_VQX_DONE_ACK(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_vq#_done_cnt
 *
 * RAD VF Queue Done Count Register
 */
union bdk_rad_vqx_done_cnt
{
    uint64_t u;
    struct bdk_rad_vqx_done_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_21_63        : 43;
        uint64_t done                  : 21; /**< [ 20:  0](R/W/H) When an instruction with RAD_CWORD_S[DN] completes, [DONE] is
                                                                 incremented. Writes to this field are for diagnostic use only; instead software
                                                                 writes RAD_VQ()_DONE_ACK[DONE_ACK] with the number of decrements for this field.

                                                                 Interrupts are sent as follows:

                                                                 * When RAD_VQ()_DONE_CNT[DONE] = 0, then no results are pending, the interrupt coalescing
                                                                 timer is held to zero, and an interrupt is not sent.

                                                                 * When RAD_VQ()_DONE_CNT[DONE] != 0, then the interrupt coalescing timer counts. If
                                                                 the counter is \>= RAD_VQ()_DONE_WAIT[TIME_WAIT]*1024, or RAD_VQ()_DONE_CNT[DONE] \>=
                                                                 RAD_VQ()_DONE_WAIT[NUM_WAIT], i.e. enough time has passed or enough results have
                                                                 arrived, then the interrupt is sent.  Otherwise, it is not sent due to
                                                                 coalescing.

                                                                 * When RAD_DONE_ACK is written, the interrupt coalescing timer restarts.  Note
                                                                 after decrementing this interrupt equation is recomputed, for example if
                                                                 RAD_DONE_CNT[DONE] \>= RAD_DONE_WAIT[NUM_WAIT] and because the timer is zero, the
                                                                 interrupt will be resent immediately.  (This covers the race case between
                                                                 software acknowledging an interrupt and a result returning.)

                                                                 * When RAD_VF()_INT_ENA_W1S[DONE] = 0, interrupts are not sent, but the counting described
                                                                 above still occurs.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 21; /**< [ 20:  0](R/W/H) When an instruction with RAD_CWORD_S[DN] completes, [DONE] is
                                                                 incremented. Writes to this field are for diagnostic use only; instead software
                                                                 writes RAD_VQ()_DONE_ACK[DONE_ACK] with the number of decrements for this field.

                                                                 Interrupts are sent as follows:

                                                                 * When RAD_VQ()_DONE_CNT[DONE] = 0, then no results are pending, the interrupt coalescing
                                                                 timer is held to zero, and an interrupt is not sent.

                                                                 * When RAD_VQ()_DONE_CNT[DONE] != 0, then the interrupt coalescing timer counts. If
                                                                 the counter is \>= RAD_VQ()_DONE_WAIT[TIME_WAIT]*1024, or RAD_VQ()_DONE_CNT[DONE] \>=
                                                                 RAD_VQ()_DONE_WAIT[NUM_WAIT], i.e. enough time has passed or enough results have
                                                                 arrived, then the interrupt is sent.  Otherwise, it is not sent due to
                                                                 coalescing.

                                                                 * When RAD_DONE_ACK is written, the interrupt coalescing timer restarts.  Note
                                                                 after decrementing this interrupt equation is recomputed, for example if
                                                                 RAD_DONE_CNT[DONE] \>= RAD_DONE_WAIT[NUM_WAIT] and because the timer is zero, the
                                                                 interrupt will be resent immediately.  (This covers the race case between
                                                                 software acknowledging an interrupt and a result returning.)

                                                                 * When RAD_VF()_INT_ENA_W1S[DONE] = 0, interrupts are not sent, but the counting described
                                                                 above still occurs.

                                                                 Software is responsible for making sure [DONE] does not overflow; for example by
                                                                 insuring there are not more than 2^20-1 instructions in flight that may request
                                                                 interrupts. */
        uint64_t reserved_21_63        : 43;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vqx_done_cnt_s cn; */
};
typedef union bdk_rad_vqx_done_cnt bdk_rad_vqx_done_cnt_t;

static inline uint64_t BDK_RAD_VQX_DONE_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VQX_DONE_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020000038ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VQX_DONE_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VQX_DONE_CNT(a) bdk_rad_vqx_done_cnt_t
#define bustype_BDK_RAD_VQX_DONE_CNT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VQX_DONE_CNT(a) "RAD_VQX_DONE_CNT"
#define device_bar_BDK_RAD_VQX_DONE_CNT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VQX_DONE_CNT(a) (a)
#define arguments_BDK_RAD_VQX_DONE_CNT(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_vq#_done_wait
 *
 * RAD VF Queue Done Interrupt Coalescing Wait Registers
 * Specifies the interrupt coalescing settings.
 */
union bdk_rad_vqx_done_wait
{
    uint64_t u;
    struct bdk_rad_vqx_done_wait_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t time_wait             : 16; /**< [ 47: 32](R/W) Time hold-off. When RAD_VQ()_DONE_CNT[DONE] = 0, or RAD_VQ()_DONE_ACK is written a timer
                                                                 is
                                                                 cleared. When the timer reaches [TIME_WAIT]*1024 then interrupt coalescing ends; see
                                                                 RAD_VQ()_DONE_CNT[DONE]. If zero, time coalescing is disabled. */
        uint64_t reserved_20_31        : 12;
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of messages hold-off. When RAD_VQ()_DONE_CNT[DONE] \>= [NUM_WAIT] then interrupt
                                                                 coalescing ends; see RAD_VQ()_DONE_CNT[DONE]. If zero, message number coalescing is
                                                                 disabled. */
#else /* Word 0 - Little Endian */
        uint64_t num_wait              : 20; /**< [ 19:  0](R/W) Number of messages hold-off. When RAD_VQ()_DONE_CNT[DONE] \>= [NUM_WAIT] then interrupt
                                                                 coalescing ends; see RAD_VQ()_DONE_CNT[DONE]. If zero, message number coalescing is
                                                                 disabled. */
        uint64_t reserved_20_31        : 12;
        uint64_t time_wait             : 16; /**< [ 47: 32](R/W) Time hold-off. When RAD_VQ()_DONE_CNT[DONE] = 0, or RAD_VQ()_DONE_ACK is written a timer
                                                                 is
                                                                 cleared. When the timer reaches [TIME_WAIT]*1024 then interrupt coalescing ends; see
                                                                 RAD_VQ()_DONE_CNT[DONE]. If zero, time coalescing is disabled. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vqx_done_wait_s cn; */
};
typedef union bdk_rad_vqx_done_wait bdk_rad_vqx_done_wait_t;

static inline uint64_t BDK_RAD_VQX_DONE_WAIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VQX_DONE_WAIT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020000058ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VQX_DONE_WAIT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VQX_DONE_WAIT(a) bdk_rad_vqx_done_wait_t
#define bustype_BDK_RAD_VQX_DONE_WAIT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VQX_DONE_WAIT(a) "RAD_VQX_DONE_WAIT"
#define device_bar_BDK_RAD_VQX_DONE_WAIT(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VQX_DONE_WAIT(a) (a)
#define arguments_BDK_RAD_VQX_DONE_WAIT(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_vq#_doorbell
 *
 * RAD VF Queue Doorbell Register
 */
union bdk_rad_vqx_doorbell
{
    uint64_t u;
    struct bdk_rad_vqx_doorbell_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) Number of instruction queue 64-bit words to add to the RAD instruction doorbell count.
                                                                 RAD instructions are from 4 to 36 words. */
#else /* Word 0 - Little Endian */
        uint64_t dbell_cnt             : 20; /**< [ 19:  0](R/W/H) Number of instruction queue 64-bit words to add to the RAD instruction doorbell count.
                                                                 RAD instructions are from 4 to 36 words. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vqx_doorbell_s cn; */
};
typedef union bdk_rad_vqx_doorbell bdk_rad_vqx_doorbell_t;

static inline uint64_t BDK_RAD_VQX_DOORBELL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VQX_DOORBELL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020010000ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VQX_DOORBELL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VQX_DOORBELL(a) bdk_rad_vqx_doorbell_t
#define bustype_BDK_RAD_VQX_DOORBELL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VQX_DOORBELL(a) "RAD_VQX_DOORBELL"
#define device_bar_BDK_RAD_VQX_DOORBELL(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VQX_DOORBELL(a) (a)
#define arguments_BDK_RAD_VQX_DOORBELL(a) (a),-1,-1,-1

/**
 * Register (NCB) rad_vq#_polynomial
 *
 * RAD VF Queue Polynomial Register
 * The polynomial is x^8 + C7*x^7 + C6*x^6 + C5*x^5 + C4*x^4 + C3*x^3 + C2*x^2 + C1*x^1 + C0.
 */
union bdk_rad_vqx_polynomial
{
    uint64_t u;
    struct bdk_rad_vqx_polynomial_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t coeffs                : 8;  /**< [  7:  0](R/W) Coefficients of GF(2^8) irreducible polynomial.
                                                                 Must be 0x1D, 0x2B, 0x2D, 0x4D, 0x5F, 0x63, 0x65, 0x69, 0x71, 0x87, 0x8D, 0xA9, 0xC3,
                                                                 0xCF, 0xE7, or 0xF5. */
#else /* Word 0 - Little Endian */
        uint64_t coeffs                : 8;  /**< [  7:  0](R/W) Coefficients of GF(2^8) irreducible polynomial.
                                                                 Must be 0x1D, 0x2B, 0x2D, 0x4D, 0x5F, 0x63, 0x65, 0x69, 0x71, 0x87, 0x8D, 0xA9, 0xC3,
                                                                 0xCF, 0xE7, or 0xF5. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rad_vqx_polynomial_s cn; */
};
typedef union bdk_rad_vqx_polynomial bdk_rad_vqx_polynomial_t;

static inline uint64_t BDK_RAD_VQX_POLYNOMIAL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RAD_VQX_POLYNOMIAL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN83XX) && (a==0))
        return 0x870020000010ll + 0x100000ll * ((a) & 0x0);
    __bdk_csr_fatal("RAD_VQX_POLYNOMIAL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RAD_VQX_POLYNOMIAL(a) bdk_rad_vqx_polynomial_t
#define bustype_BDK_RAD_VQX_POLYNOMIAL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_RAD_VQX_POLYNOMIAL(a) "RAD_VQX_POLYNOMIAL"
#define device_bar_BDK_RAD_VQX_POLYNOMIAL(a) 0x0 /* VF_BAR0 */
#define busnum_BDK_RAD_VQX_POLYNOMIAL(a) (a)
#define arguments_BDK_RAD_VQX_POLYNOMIAL(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_RAD_H__ */
