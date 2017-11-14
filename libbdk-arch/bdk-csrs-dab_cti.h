#ifndef __BDK_CSRS_DAB_CTI_H__
#define __BDK_CSRS_DAB_CTI_H__
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
 * Cavium DAB_CTI.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Register (DAB32b) cti#_asicctl
 *
 * CTI External Multiplexer Control Register
 * Provides a control for external multiplexing of additional triggers.
 */
union bdk_ctix_asicctl
{
    uint32_t u;
    struct bdk_ctix_asicctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t asicctl               : 3;  /**< [  2:  0](R/W) Implementation defined ASIC control. Provides a control for
                                                                 external multiplexing of additional triggers.
                                                                 If external multiplexing of trigger signals is implemented
                                                                     then the number of multiplexed signals on each trigger must be
                                                                     reflected in CTI()_CTIDEVID[EXTMUXNUM].
                                                                 If CTI()_CTIDEVID[EXTMUXNUM] is zero, this field is 0x0. */
#else /* Word 0 - Little Endian */
        uint32_t asicctl               : 3;  /**< [  2:  0](R/W) Implementation defined ASIC control. Provides a control for
                                                                 external multiplexing of additional triggers.
                                                                 If external multiplexing of trigger signals is implemented
                                                                     then the number of multiplexed signals on each trigger must be
                                                                     reflected in CTI()_CTIDEVID[EXTMUXNUM].
                                                                 If CTI()_CTIDEVID[EXTMUXNUM] is zero, this field is 0x0. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_asicctl_s cn8; */
    struct bdk_ctix_asicctl_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t asicctl               : 3;  /**< [  2:  0](RAZ) Implementation defined ASIC control. Provides a control for
                                                                 external multiplexing of additional triggers.
                                                                 If external multiplexing of trigger signals is implemented
                                                                     then the number of multiplexed signals on each trigger must be
                                                                     reflected in CTI()_CTIDEVID[EXTMUXNUM].
                                                                 If CTI()_CTIDEVID[EXTMUXNUM] is zero, this field is 0x0.

                                                                 Since CTI()_CTIDEVID[EXTMUXNUM] is zero, this field is 0x0. */
#else /* Word 0 - Little Endian */
        uint32_t asicctl               : 3;  /**< [  2:  0](RAZ) Implementation defined ASIC control. Provides a control for
                                                                 external multiplexing of additional triggers.
                                                                 If external multiplexing of trigger signals is implemented
                                                                     then the number of multiplexed signals on each trigger must be
                                                                     reflected in CTI()_CTIDEVID[EXTMUXNUM].
                                                                 If CTI()_CTIDEVID[EXTMUXNUM] is zero, this field is 0x0.

                                                                 Since CTI()_CTIDEVID[EXTMUXNUM] is zero, this field is 0x0. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ctix_asicctl bdk_ctix_asicctl_t;

static inline uint64_t BDK_CTIX_ASICCTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_ASICCTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010144ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010144ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010144ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010144ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_ASICCTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_ASICCTL(a) bdk_ctix_asicctl_t
#define bustype_BDK_CTIX_ASICCTL(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_ASICCTL(a) "CTIX_ASICCTL"
#define busnum_BDK_CTIX_ASICCTL(a) (a)
#define arguments_BDK_CTIX_ASICCTL(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_claimclr_el1
 *
 * CTI Claim Tag Clear Register
 * Used by software to read the values of the CLAIM bits, and to
 *      clear these bits to zero.
 */
union bdk_ctix_claimclr_el1
{
    uint32_t u;
    struct bdk_ctix_claimclr_el1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    struct bdk_ctix_claimclr_el1_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t claim                 : 8;  /**< [  7:  0](R/W) Claim clear bits. Reading this field returns the current value
                                                                     of the CLAIM bits.
                                                                 Writing a one to one of these bits clears the corresponding
                                                                     CLAIM bit to zero. This is an indirect write to the CLAIM bits.
                                                                 A single write operation can clear multiple bits to zero. Writing
                                                                     zero to one of these bits has no effect. */
#else /* Word 0 - Little Endian */
        uint32_t claim                 : 8;  /**< [  7:  0](R/W) Claim clear bits. Reading this field returns the current value
                                                                     of the CLAIM bits.
                                                                 Writing a one to one of these bits clears the corresponding
                                                                     CLAIM bit to zero. This is an indirect write to the CLAIM bits.
                                                                 A single write operation can clear multiple bits to zero. Writing
                                                                     zero to one of these bits has no effect. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ctix_claimclr_el1_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t clr                   : 8;  /**< [  7:  0](R/W1C) Claim clear bits. Reading this field returns the current value
                                                                     of the CLAIM bits.
                                                                 Writing a one to one of these bits clears the corresponding
                                                                     CLAIM bit to zero. This is an indirect write to the CLAIM bits.
                                                                 A single write operation can clear multiple bits to zero. Writing
                                                                     zero to one of these bits has no effect. */
#else /* Word 0 - Little Endian */
        uint32_t clr                   : 8;  /**< [  7:  0](R/W1C) Claim clear bits. Reading this field returns the current value
                                                                     of the CLAIM bits.
                                                                 Writing a one to one of these bits clears the corresponding
                                                                     CLAIM bit to zero. This is an indirect write to the CLAIM bits.
                                                                 A single write operation can clear multiple bits to zero. Writing
                                                                     zero to one of these bits has no effect. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ctix_claimclr_el1 bdk_ctix_claimclr_el1_t;

static inline uint64_t BDK_CTIX_CLAIMCLR_EL1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CLAIMCLR_EL1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fa4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fa4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fa4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fa4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CLAIMCLR_EL1", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CLAIMCLR_EL1(a) bdk_ctix_claimclr_el1_t
#define bustype_BDK_CTIX_CLAIMCLR_EL1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CLAIMCLR_EL1(a) "CTIX_CLAIMCLR_EL1"
#define busnum_BDK_CTIX_CLAIMCLR_EL1(a) (a)
#define arguments_BDK_CTIX_CLAIMCLR_EL1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_claimset_el1
 *
 * CTI Claim Tag Set Register
 * Used by software to set CLAIM bits to one.
 */
union bdk_ctix_claimset_el1
{
    uint32_t u;
    struct bdk_ctix_claimset_el1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    struct bdk_ctix_claimset_el1_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t claim                 : 8;  /**< [  7:  0](R/W) Claim set bits. RAO.
                                                                 Writing a one to one of these bits sets the corresponding CLAIM
                                                                     bit to one. This is an indirect write to the CLAIM bits.
                                                                 A single write operation can set multiple bits to one. Writing zero
                                                                     to one of these bits has no effect. */
#else /* Word 0 - Little Endian */
        uint32_t claim                 : 8;  /**< [  7:  0](R/W) Claim set bits. RAO.
                                                                 Writing a one to one of these bits sets the corresponding CLAIM
                                                                     bit to one. This is an indirect write to the CLAIM bits.
                                                                 A single write operation can set multiple bits to one. Writing zero
                                                                     to one of these bits has no effect. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ctix_claimset_el1_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t set                   : 8;  /**< [  7:  0](R/W1S) Claim set bits. RAO.
                                                                 Writing a one to one of these bits sets the corresponding CLAIM
                                                                     bit to one. This is an indirect write to the CLAIM bits.
                                                                 A single write operation can set multiple bits to one. Writing zero
                                                                     to one of these bits has no effect. */
#else /* Word 0 - Little Endian */
        uint32_t set                   : 8;  /**< [  7:  0](R/W1S) Claim set bits. RAO.
                                                                 Writing a one to one of these bits sets the corresponding CLAIM
                                                                     bit to one. This is an indirect write to the CLAIM bits.
                                                                 A single write operation can set multiple bits to one. Writing zero
                                                                     to one of these bits has no effect. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ctix_claimset_el1 bdk_ctix_claimset_el1_t;

static inline uint64_t BDK_CTIX_CLAIMSET_EL1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CLAIMSET_EL1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fa0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fa0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fa0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fa0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CLAIMSET_EL1", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CLAIMSET_EL1(a) bdk_ctix_claimset_el1_t
#define bustype_BDK_CTIX_CLAIMSET_EL1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CLAIMSET_EL1(a) "CTIX_CLAIMSET_EL1"
#define busnum_BDK_CTIX_CLAIMSET_EL1(a) (a)
#define arguments_BDK_CTIX_CLAIMSET_EL1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctiappclear
 *
 * CTI Application Trigger Clear Register
 * Clears bits of the application trigger register.
 */
union bdk_ctix_ctiappclear
{
    uint32_t u;
    struct bdk_ctix_ctiappclear_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctiappclear_s cn; */
};
typedef union bdk_ctix_ctiappclear bdk_ctix_ctiappclear_t;

static inline uint64_t BDK_CTIX_CTIAPPCLEAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIAPPCLEAR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010018ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010018ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010018ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010018ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIAPPCLEAR", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIAPPCLEAR(a) bdk_ctix_ctiappclear_t
#define bustype_BDK_CTIX_CTIAPPCLEAR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIAPPCLEAR(a) "CTIX_CTIAPPCLEAR"
#define busnum_BDK_CTIX_CTIAPPCLEAR(a) (a)
#define arguments_BDK_CTIX_CTIAPPCLEAR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctiapppulse
 *
 * CTI Application Pulse Register
 * Causes event pulses to be generated on ECT channels.
 */
union bdk_ctix_ctiapppulse
{
    uint32_t u;
    struct bdk_ctix_ctiapppulse_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t apppulse              : 3;  /**< [  2:  0](WO) Generate event pulse on ECT channel \<x\>.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 Writing to this bit has the following effect:
                                                                 0 = No effect.
                                                                 1 = Channel \<x\> event pulse generated for one clock period. */
#else /* Word 0 - Little Endian */
        uint32_t apppulse              : 3;  /**< [  2:  0](WO) Generate event pulse on ECT channel \<x\>.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 Writing to this bit has the following effect:
                                                                 0 = No effect.
                                                                 1 = Channel \<x\> event pulse generated for one clock period. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctiapppulse_s cn; */
};
typedef union bdk_ctix_ctiapppulse bdk_ctix_ctiapppulse_t;

static inline uint64_t BDK_CTIX_CTIAPPPULSE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIAPPPULSE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a00801001cll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a00801001cll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a00801001cll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a00801001cll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIAPPPULSE", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIAPPPULSE(a) bdk_ctix_ctiapppulse_t
#define bustype_BDK_CTIX_CTIAPPPULSE(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIAPPPULSE(a) "CTIX_CTIAPPPULSE"
#define busnum_BDK_CTIX_CTIAPPPULSE(a) (a)
#define arguments_BDK_CTIX_CTIAPPPULSE(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctiappset
 *
 * CTI Application Trigger Set Register
 * Sets bits of the application trigger register.
 */
union bdk_ctix_ctiappset
{
    uint32_t u;
    struct bdk_ctix_ctiappset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t trig                  : 3;  /**< [  2:  0](R/W1S/H) Application trigger \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 If the ECT does not support multicycle channel events, use of
                                                                     CTIAPPSET is deprecated and the debugger must only use
                                                                     CTIAPPPULSE.
                                                                 0 = Reading this means the application trigger is inactive.
                                                                     Writing this has no effect.
                                                                 1 = Reading this means the application trigger is active. Writing
                                                                     this sets the corresponding bit in CTIAPPTRIG to one and
                                                                     generates a channel event.

                                                                 In CNXXXX always 0x0 as it doesn't support multicycle channel events. */
#else /* Word 0 - Little Endian */
        uint32_t trig                  : 3;  /**< [  2:  0](R/W1S/H) Application trigger \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 If the ECT does not support multicycle channel events, use of
                                                                     CTIAPPSET is deprecated and the debugger must only use
                                                                     CTIAPPPULSE.
                                                                 0 = Reading this means the application trigger is inactive.
                                                                     Writing this has no effect.
                                                                 1 = Reading this means the application trigger is active. Writing
                                                                     this sets the corresponding bit in CTIAPPTRIG to one and
                                                                     generates a channel event.

                                                                 In CNXXXX always 0x0 as it doesn't support multicycle channel events. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    struct bdk_ctix_ctiappset_cn88xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } cn88xxp1;
    /* struct bdk_ctix_ctiappset_s cn9; */
    /* struct bdk_ctix_ctiappset_s cn81xx; */
    /* struct bdk_ctix_ctiappset_s cn83xx; */
    struct bdk_ctix_ctiappset_cn88xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t trig                  : 3;  /**< [  2:  0](R/W1S/H) Application trigger \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 If the ECT does not support multicycle channel events, use of
                                                                     CTIAPPSET is deprecated and the debugger must only use
                                                                     CTIAPPPULSE.
                                                                 0 = Reading this means the application trigger is inactive.
                                                                     Writing this has no effect.
                                                                 1 = Reading this means the application trigger is active. Writing
                                                                     this sets the corresponding bit in CTIAPPTRIG to one and
                                                                     generates a channel event.

                                                                 In CNXXXX always 0x0 as it doesn't support multicycle channel events.

                                                                 For pass 1 is RO, for pass 2 changed to R/W. */
#else /* Word 0 - Little Endian */
        uint32_t trig                  : 3;  /**< [  2:  0](R/W1S/H) Application trigger \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 If the ECT does not support multicycle channel events, use of
                                                                     CTIAPPSET is deprecated and the debugger must only use
                                                                     CTIAPPPULSE.
                                                                 0 = Reading this means the application trigger is inactive.
                                                                     Writing this has no effect.
                                                                 1 = Reading this means the application trigger is active. Writing
                                                                     this sets the corresponding bit in CTIAPPTRIG to one and
                                                                     generates a channel event.

                                                                 In CNXXXX always 0x0 as it doesn't support multicycle channel events.

                                                                 For pass 1 is RO, for pass 2 changed to R/W. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } cn88xxp2;
};
typedef union bdk_ctix_ctiappset bdk_ctix_ctiappset_t;

static inline uint64_t BDK_CTIX_CTIAPPSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIAPPSET(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010014ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010014ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010014ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010014ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIAPPSET", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIAPPSET(a) bdk_ctix_ctiappset_t
#define bustype_BDK_CTIX_CTIAPPSET(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIAPPSET(a) "CTIX_CTIAPPSET"
#define busnum_BDK_CTIX_CTIAPPSET(a) (a)
#define arguments_BDK_CTIX_CTIAPPSET(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctiauthstatus
 *
 * CTI Authentication Status Register
 * Provides information about the state of the implementation defined authentication
 * interface.
 */
union bdk_ctix_ctiauthstatus
{
    uint32_t u;
    struct bdk_ctix_ctiauthstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t nsnid1                : 1;  /**< [  3:  3](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as DBGAUTHSTATUS_EL1.SNID.
                                                                 Otherwise, holds the same value as DBGAUTHSTATUS_EL1.NSNID. */
        uint32_t nsnid0                : 1;  /**< [  2:  2](RO/H) Reserved. */
        uint32_t nsid1                 : 1;  /**< [  1:  1](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as DBGAUTHSTATUS_EL1.SID.
                                                                 Otherwise, holds the same value as DBGAUTHSTATUS_EL1.NSID. */
        uint32_t nsid0                 : 1;  /**< [  0:  0](RO/H) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t nsid0                 : 1;  /**< [  0:  0](RO/H) Reserved. */
        uint32_t nsid1                 : 1;  /**< [  1:  1](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as DBGAUTHSTATUS_EL1.SID.
                                                                 Otherwise, holds the same value as DBGAUTHSTATUS_EL1.NSID. */
        uint32_t nsnid0                : 1;  /**< [  2:  2](RO/H) Reserved. */
        uint32_t nsnid1                : 1;  /**< [  3:  3](RO) If EL3 is not implemented and the processor is secure, holds
                                                                     the same value as DBGAUTHSTATUS_EL1.SNID.
                                                                 Otherwise, holds the same value as DBGAUTHSTATUS_EL1.NSNID. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctiauthstatus_s cn; */
};
typedef union bdk_ctix_ctiauthstatus bdk_ctix_ctiauthstatus_t;

static inline uint64_t BDK_CTIX_CTIAUTHSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIAUTHSTATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fb8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fb8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fb8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fb8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIAUTHSTATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIAUTHSTATUS(a) bdk_ctix_ctiauthstatus_t
#define bustype_BDK_CTIX_CTIAUTHSTATUS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIAUTHSTATUS(a) "CTIX_CTIAUTHSTATUS"
#define busnum_BDK_CTIX_CTIAUTHSTATUS(a) (a)
#define arguments_BDK_CTIX_CTIAUTHSTATUS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctichinstatus
 *
 * CTI Channel In Status Register
 * Provides the raw status of the ECT channel inputs.
 */
union bdk_ctix_ctichinstatus
{
    uint32_t u;
    struct bdk_ctix_ctichinstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t chin                  : 3;  /**< [  2:  0](RO) Input channel \<n\> status.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are 0.

                                                                 0 = Input channel \<n\> is inactive.
                                                                 1 = Input channel \<n\> is active. */
#else /* Word 0 - Little Endian */
        uint32_t chin                  : 3;  /**< [  2:  0](RO) Input channel \<n\> status.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are 0.

                                                                 0 = Input channel \<n\> is inactive.
                                                                 1 = Input channel \<n\> is active. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctichinstatus_s cn; */
};
typedef union bdk_ctix_ctichinstatus bdk_ctix_ctichinstatus_t;

static inline uint64_t BDK_CTIX_CTICHINSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTICHINSTATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010138ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010138ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010138ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010138ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTICHINSTATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTICHINSTATUS(a) bdk_ctix_ctichinstatus_t
#define bustype_BDK_CTIX_CTICHINSTATUS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTICHINSTATUS(a) "CTIX_CTICHINSTATUS"
#define busnum_BDK_CTIX_CTICHINSTATUS(a) (a)
#define arguments_BDK_CTIX_CTICHINSTATUS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctichoutstatus
 *
 * CTI Channel Out Status Register
 * Provides the status of the ECT channel outputs.
 */
union bdk_ctix_ctichoutstatus
{
    uint32_t u;
    struct bdk_ctix_ctichoutstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t chout                 : 3;  /**< [  2:  0](RO) Output channel \<n\> status.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are 0.

                                                                 0 = Output channel \<n\> is inactive.
                                                                 1 = Output channel \<n\> is active. */
#else /* Word 0 - Little Endian */
        uint32_t chout                 : 3;  /**< [  2:  0](RO) Output channel \<n\> status.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are 0.

                                                                 0 = Output channel \<n\> is inactive.
                                                                 1 = Output channel \<n\> is active. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctichoutstatus_s cn; */
};
typedef union bdk_ctix_ctichoutstatus bdk_ctix_ctichoutstatus_t;

static inline uint64_t BDK_CTIX_CTICHOUTSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTICHOUTSTATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a00801013cll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a00801013cll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a00801013cll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a00801013cll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTICHOUTSTATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTICHOUTSTATUS(a) bdk_ctix_ctichoutstatus_t
#define bustype_BDK_CTIX_CTICHOUTSTATUS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTICHOUTSTATUS(a) "CTIX_CTICHOUTSTATUS"
#define busnum_BDK_CTIX_CTICHOUTSTATUS(a) (a)
#define arguments_BDK_CTIX_CTICHOUTSTATUS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_cticidr0
 *
 * CTI Component Identification Register 0
 * Provides information to identify a component.
 */
union bdk_ctix_cticidr0
{
    uint32_t u;
    struct bdk_ctix_cticidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0x0D. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0x0D. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_cticidr0_s cn; */
};
typedef union bdk_ctix_cticidr0 bdk_ctix_cticidr0_t;

static inline uint64_t BDK_CTIX_CTICIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTICIDR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010ff0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010ff0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010ff0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010ff0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTICIDR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTICIDR0(a) bdk_ctix_cticidr0_t
#define bustype_BDK_CTIX_CTICIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTICIDR0(a) "CTIX_CTICIDR0"
#define busnum_BDK_CTIX_CTICIDR0(a) (a)
#define arguments_BDK_CTIX_CTICIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_cticidr1
 *
 * CTI Component Identification Register 1
 * Provides information to identify a component.
 */
union bdk_ctix_cticidr1
{
    uint32_t u;
    struct bdk_ctix_cticidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0x9 = Debug component. */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble. */
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0x9 = Debug component. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_cticidr1_s cn; */
};
typedef union bdk_ctix_cticidr1 bdk_ctix_cticidr1_t;

static inline uint64_t BDK_CTIX_CTICIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTICIDR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010ff4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010ff4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010ff4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010ff4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTICIDR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTICIDR1(a) bdk_ctix_cticidr1_t
#define bustype_BDK_CTIX_CTICIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTICIDR1(a) "CTIX_CTICIDR1"
#define busnum_BDK_CTIX_CTICIDR1(a) (a)
#define arguments_BDK_CTIX_CTICIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_cticidr2
 *
 * CTI Component Identification Register 2
 * Provides information to identify a component.
 */
union bdk_ctix_cticidr2
{
    uint32_t u;
    struct bdk_ctix_cticidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0x05. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0x05. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_cticidr2_s cn; */
};
typedef union bdk_ctix_cticidr2 bdk_ctix_cticidr2_t;

static inline uint64_t BDK_CTIX_CTICIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTICIDR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010ff8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010ff8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010ff8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010ff8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTICIDR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTICIDR2(a) bdk_ctix_cticidr2_t
#define bustype_BDK_CTIX_CTICIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTICIDR2(a) "CTIX_CTICIDR2"
#define busnum_BDK_CTIX_CTICIDR2(a) (a)
#define arguments_BDK_CTIX_CTICIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_cticidr3
 *
 * CTI Component Identification Register 3
 * Provides information to identify a component.
 */
union bdk_ctix_cticidr3
{
    uint32_t u;
    struct bdk_ctix_cticidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0xB1. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Must read as 0xB1. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_cticidr3_s cn; */
};
typedef union bdk_ctix_cticidr3 bdk_ctix_cticidr3_t;

static inline uint64_t BDK_CTIX_CTICIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTICIDR3(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010ffcll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010ffcll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010ffcll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010ffcll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTICIDR3", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTICIDR3(a) bdk_ctix_cticidr3_t
#define bustype_BDK_CTIX_CTICIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTICIDR3(a) "CTIX_CTICIDR3"
#define busnum_BDK_CTIX_CTICIDR3(a) (a)
#define arguments_BDK_CTIX_CTICIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_cticontrol
 *
 * CTI Control Register
 * Controls whether the CTI is enabled.
 */
union bdk_ctix_cticontrol
{
    uint32_t u;
    struct bdk_ctix_cticontrol_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t glben                 : 1;  /**< [  0:  0](R/W) Enables or disables the CTI mapping functions.
                                                                 When the mapping functions are disabled, no new events are
                                                                     signaled on either output triggers or output channels. If a
                                                                     previously asserted output trigger has not been acknowledged,
                                                                     it remains asserted after the mapping functions are disabled.
                                                                     All output triggers are disabled by CTI reset.

                                                                 0 = CTI mapping functions disabled.
                                                                 1 = CTI mapping functions enabled. */
#else /* Word 0 - Little Endian */
        uint32_t glben                 : 1;  /**< [  0:  0](R/W) Enables or disables the CTI mapping functions.
                                                                 When the mapping functions are disabled, no new events are
                                                                     signaled on either output triggers or output channels. If a
                                                                     previously asserted output trigger has not been acknowledged,
                                                                     it remains asserted after the mapping functions are disabled.
                                                                     All output triggers are disabled by CTI reset.

                                                                 0 = CTI mapping functions disabled.
                                                                 1 = CTI mapping functions enabled. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_cticontrol_s cn; */
};
typedef union bdk_ctix_cticontrol bdk_ctix_cticontrol_t;

static inline uint64_t BDK_CTIX_CTICONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTICONTROL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010000ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010000ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010000ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010000ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTICONTROL", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTICONTROL(a) bdk_ctix_cticontrol_t
#define bustype_BDK_CTIX_CTICONTROL(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTICONTROL(a) "CTIX_CTICONTROL"
#define busnum_BDK_CTIX_CTICONTROL(a) (a)
#define arguments_BDK_CTIX_CTICONTROL(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctidevaff0
 *
 * CTI Device Affinity Register 0
 * Copy of the low half of the processor MPIDR_EL1 register that
 *     allows a debugger to determine which processor in a
 *     multiprocessor system the CTI component relates to.
 */
union bdk_ctix_ctidevaff0
{
    uint32_t u;
    struct bdk_ctix_ctidevaff0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO) MPIDR_EL1 low half. Read-only copy of the low half of MPIDR_EL1, as seen from
                                                                 the highest implemented exception level. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO) MPIDR_EL1 low half. Read-only copy of the low half of MPIDR_EL1, as seen from
                                                                 the highest implemented exception level. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctidevaff0_s cn; */
};
typedef union bdk_ctix_ctidevaff0 bdk_ctix_ctidevaff0_t;

static inline uint64_t BDK_CTIX_CTIDEVAFF0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIDEVAFF0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fa8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fa8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fa8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fa8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIDEVAFF0", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIDEVAFF0(a) bdk_ctix_ctidevaff0_t
#define bustype_BDK_CTIX_CTIDEVAFF0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIDEVAFF0(a) "CTIX_CTIDEVAFF0"
#define busnum_BDK_CTIX_CTIDEVAFF0(a) (a)
#define arguments_BDK_CTIX_CTIDEVAFF0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctidevaff1
 *
 * CTI Device Affinity Register 1
 * Copy of the high half of the processor MPIDR_EL1 register that
 *     allows a debugger to determine which processor in a
 *     multiprocessor system the CTI component relates to.
 */
union bdk_ctix_ctidevaff1
{
    uint32_t u;
    struct bdk_ctix_ctidevaff1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO) MPIDR_EL1 high half. Read-only copy of the high half of MPIDR_EL1, as seen from
                                                                 the highest implemented exception level. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](RO) MPIDR_EL1 high half. Read-only copy of the high half of MPIDR_EL1, as seen from
                                                                 the highest implemented exception level. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctidevaff1_s cn; */
};
typedef union bdk_ctix_ctidevaff1 bdk_ctix_ctidevaff1_t;

static inline uint64_t BDK_CTIX_CTIDEVAFF1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIDEVAFF1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010facll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010facll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010facll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010facll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIDEVAFF1", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIDEVAFF1(a) bdk_ctix_ctidevaff1_t
#define bustype_BDK_CTIX_CTIDEVAFF1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIDEVAFF1(a) "CTIX_CTIDEVAFF1"
#define busnum_BDK_CTIX_CTIDEVAFF1(a) (a)
#define arguments_BDK_CTIX_CTIDEVAFF1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctidevarch
 *
 * CTI Device Architecture Register
 * Identifies the programmers' model architecture.
 */
union bdk_ctix_ctidevarch
{
    uint32_t u;
    struct bdk_ctix_ctidevarch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. This is ARM Limited.

                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.

                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is one in v8-A. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by ARM this is the minor revision.
                                                                 For CTI, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by ARM this is further subdivided.
                                                                 For CTI:
                                                                  Bits [15:12] are the architecture version, 0x1.
                                                                  Bits [11:0] are the architecture part number, 0xA14.
                                                                 This corresponds to CTI architecture version CTIv2. */
#else /* Word 0 - Little Endian */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by ARM this is further subdivided.
                                                                 For CTI:
                                                                  Bits [15:12] are the architecture version, 0x1.
                                                                  Bits [11:0] are the architecture part number, 0xA14.
                                                                 This corresponds to CTI architecture version CTIv2. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by ARM this is the minor revision.
                                                                 For CTI, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is one in v8-A. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. This is ARM Limited.

                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.

                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctidevarch_s cn; */
};
typedef union bdk_ctix_ctidevarch bdk_ctix_ctidevarch_t;

static inline uint64_t BDK_CTIX_CTIDEVARCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIDEVARCH(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fbcll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fbcll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fbcll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fbcll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIDEVARCH", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIDEVARCH(a) bdk_ctix_ctidevarch_t
#define bustype_BDK_CTIX_CTIDEVARCH(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIDEVARCH(a) "CTIX_CTIDEVARCH"
#define busnum_BDK_CTIX_CTIDEVARCH(a) (a)
#define arguments_BDK_CTIX_CTIDEVARCH(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctidevid
 *
 * CTI Device ID Register 0
 * Describes the component to the debugger.
 */
union bdk_ctix_ctidevid
{
    uint32_t u;
    struct bdk_ctix_ctidevid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_26_31        : 6;
        uint32_t inout_gate            : 2;  /**< [ 25: 24](RO) Input/output options. Indicates presence of the input gate. If
                                                                     the CTM is not implemented, this field is zero.
                                                                 All other values are reserved.
                                                                 0x0 = CTIGATE does not mask propagation of input events from
                                                                     external channels.
                                                                 0x1 = CTIGATE masks propagation of input events from external
                                                                     channels. */
        uint32_t reserved_22_23        : 2;
        uint32_t numchan               : 6;  /**< [ 21: 16](RO) Number of ECT channels implemented. Implementation defined.
                                                                 For v8-A, valid values are:
                                                                 0x3 = 3 channels (0..2) implemented.
                                                                 0x4 = 4 channels (0..3) implemented.
                                                                 0x5 = 5 channels (0..4) implemented.
                                                                 0x6 = 6 channels (0..5) implemented.
                                                                 and so on up to 0x20.
                                                                 All other values are reserved. */
        uint32_t reserved_14_15        : 2;
        uint32_t numtrig               : 6;  /**< [ 13:  8](RO) Number of triggers implemented. implementation defined. This
                                                                     is one more than the index of the largest trigger, rather than
                                                                     the actual number of triggers.
                                                                 For v8-A, valid values are:
                                                                 0x3 = Up to 3 triggers (0..2) implemented.
                                                                 0x8 = Up to 8 triggers (0..7) implemented.
                                                                 0x9 = Up to 9 triggers (0..8) implemented.
                                                                 0xa = Up to 10 triggers (0..9) implemented.
                                                                 and so on up to 0x20.

                                                                 All other values are reserved. If the trace extension is implemented, this field
                                                                 must be at least 0x8. There is no guarantee that any of the implemented
                                                                 triggers, including the highest numbered, are connected to any components. */
        uint32_t reserved_5_7          : 3;
        uint32_t extmuxnum             : 5;  /**< [  4:  0](RO) Maximum number of external triggers available for multiplexing
                                                                     into the CTI. This relates only to additional external
                                                                     triggers outside those defined for v8-A. */
#else /* Word 0 - Little Endian */
        uint32_t extmuxnum             : 5;  /**< [  4:  0](RO) Maximum number of external triggers available for multiplexing
                                                                     into the CTI. This relates only to additional external
                                                                     triggers outside those defined for v8-A. */
        uint32_t reserved_5_7          : 3;
        uint32_t numtrig               : 6;  /**< [ 13:  8](RO) Number of triggers implemented. implementation defined. This
                                                                     is one more than the index of the largest trigger, rather than
                                                                     the actual number of triggers.
                                                                 For v8-A, valid values are:
                                                                 0x3 = Up to 3 triggers (0..2) implemented.
                                                                 0x8 = Up to 8 triggers (0..7) implemented.
                                                                 0x9 = Up to 9 triggers (0..8) implemented.
                                                                 0xa = Up to 10 triggers (0..9) implemented.
                                                                 and so on up to 0x20.

                                                                 All other values are reserved. If the trace extension is implemented, this field
                                                                 must be at least 0x8. There is no guarantee that any of the implemented
                                                                 triggers, including the highest numbered, are connected to any components. */
        uint32_t reserved_14_15        : 2;
        uint32_t numchan               : 6;  /**< [ 21: 16](RO) Number of ECT channels implemented. Implementation defined.
                                                                 For v8-A, valid values are:
                                                                 0x3 = 3 channels (0..2) implemented.
                                                                 0x4 = 4 channels (0..3) implemented.
                                                                 0x5 = 5 channels (0..4) implemented.
                                                                 0x6 = 6 channels (0..5) implemented.
                                                                 and so on up to 0x20.
                                                                 All other values are reserved. */
        uint32_t reserved_22_23        : 2;
        uint32_t inout_gate            : 2;  /**< [ 25: 24](RO) Input/output options. Indicates presence of the input gate. If
                                                                     the CTM is not implemented, this field is zero.
                                                                 All other values are reserved.
                                                                 0x0 = CTIGATE does not mask propagation of input events from
                                                                     external channels.
                                                                 0x1 = CTIGATE masks propagation of input events from external
                                                                     channels. */
        uint32_t reserved_26_31        : 6;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctidevid_s cn; */
};
typedef union bdk_ctix_ctidevid bdk_ctix_ctidevid_t;

static inline uint64_t BDK_CTIX_CTIDEVID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIDEVID(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fc8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fc8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fc8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fc8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIDEVID", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIDEVID(a) bdk_ctix_ctidevid_t
#define bustype_BDK_CTIX_CTIDEVID(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIDEVID(a) "CTIX_CTIDEVID"
#define busnum_BDK_CTIX_CTIDEVID(a) (a)
#define arguments_BDK_CTIX_CTIDEVID(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctidevid1
 *
 * CTI Device ID Register 1
 * Reserved for future information about the component to the debugger.
 */
union bdk_ctix_ctidevid1
{
    uint32_t u;
    struct bdk_ctix_ctidevid1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctidevid1_s cn; */
};
typedef union bdk_ctix_ctidevid1 bdk_ctix_ctidevid1_t;

static inline uint64_t BDK_CTIX_CTIDEVID1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIDEVID1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fc4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fc4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fc4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fc4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIDEVID1", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIDEVID1(a) bdk_ctix_ctidevid1_t
#define bustype_BDK_CTIX_CTIDEVID1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIDEVID1(a) "CTIX_CTIDEVID1"
#define busnum_BDK_CTIX_CTIDEVID1(a) (a)
#define arguments_BDK_CTIX_CTIDEVID1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctidevid2
 *
 * CTI Device ID Register 2
 * Reserved for future information about the CTI component to the
 *     debugger.
 */
union bdk_ctix_ctidevid2
{
    uint32_t u;
    struct bdk_ctix_ctidevid2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctidevid2_s cn; */
};
typedef union bdk_ctix_ctidevid2 bdk_ctix_ctidevid2_t;

static inline uint64_t BDK_CTIX_CTIDEVID2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIDEVID2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fc0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fc0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fc0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fc0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIDEVID2", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIDEVID2(a) bdk_ctix_ctidevid2_t
#define bustype_BDK_CTIX_CTIDEVID2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIDEVID2(a) "CTIX_CTIDEVID2"
#define busnum_BDK_CTIX_CTIDEVID2(a) (a)
#define arguments_BDK_CTIX_CTIDEVID2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctidevtype
 *
 * CTI Device Type Register
 * Indicates to a debugger that this component is part of a processor's cross-trigger
 * interface.
 */
union bdk_ctix_ctidevtype
{
    uint32_t u;
    struct bdk_ctix_ctidevtype_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Subtype. Must read as 0x1. */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major type. Must read as 0x4. */
#else /* Word 0 - Little Endian */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major type. Must read as 0x4. */
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Subtype. Must read as 0x1. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctidevtype_s cn; */
};
typedef union bdk_ctix_ctidevtype bdk_ctix_ctidevtype_t;

static inline uint64_t BDK_CTIX_CTIDEVTYPE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIDEVTYPE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fccll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fccll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fccll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fccll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIDEVTYPE", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIDEVTYPE(a) bdk_ctix_ctidevtype_t
#define bustype_BDK_CTIX_CTIDEVTYPE(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIDEVTYPE(a) "CTIX_CTIDEVTYPE"
#define busnum_BDK_CTIX_CTIDEVTYPE(a) (a)
#define arguments_BDK_CTIX_CTIDEVTYPE(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctigate
 *
 * CTI Channel Gate Enable Register
 * Determines whether events on channels propagate through the
 *     CTM to other ECT components, or from the CTM into the CTI.
 */
union bdk_ctix_ctigate
{
    uint32_t u;
    struct bdk_ctix_ctigate_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t gate                  : 3;  /**< [  2:  0](R/W) Channel \<x\> gate enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = Disable output and, if CTI()_CTIDEVID[INOUT] = 0x1.
                                                                 1 = Enable output and, if CTI()_CTIDEVID[INOUT] = 0x1. */
#else /* Word 0 - Little Endian */
        uint32_t gate                  : 3;  /**< [  2:  0](R/W) Channel \<x\> gate enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = Disable output and, if CTI()_CTIDEVID[INOUT] = 0x1.
                                                                 1 = Enable output and, if CTI()_CTIDEVID[INOUT] = 0x1. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctigate_s cn; */
};
typedef union bdk_ctix_ctigate bdk_ctix_ctigate_t;

static inline uint64_t BDK_CTIX_CTIGATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIGATE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010140ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010140ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010140ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010140ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIGATE", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIGATE(a) bdk_ctix_ctigate_t
#define bustype_BDK_CTIX_CTIGATE(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIGATE(a) "CTIX_CTIGATE"
#define busnum_BDK_CTIX_CTIGATE(a) (a)
#define arguments_BDK_CTIX_CTIGATE(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctiinen#
 *
 * CTI Input Trigger to Output Channel Enable Registers
 * Enables the signaling of an event on output channels when
 *     input trigger event n is received by the CTI.
 */
union bdk_ctix_ctiinenx
{
    uint32_t u;
    struct bdk_ctix_ctiinenx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t inen                  : 3;  /**< [  2:  0](R/W) Input trigger \<n\> to output channel \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = Input trigger \<n\> will not generate an event on output channel
                                                                     \<x\>.
                                                                 1 = Input trigger \<n\> will generate an event on output channel
                                                                     \<x\>.

                                                                 In CNXXXX CTIINEN(3..31) are ignored as there are only 3 channels. */
#else /* Word 0 - Little Endian */
        uint32_t inen                  : 3;  /**< [  2:  0](R/W) Input trigger \<n\> to output channel \<x\> enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = Input trigger \<n\> will not generate an event on output channel
                                                                     \<x\>.
                                                                 1 = Input trigger \<n\> will generate an event on output channel
                                                                     \<x\>.

                                                                 In CNXXXX CTIINEN(3..31) are ignored as there are only 3 channels. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctiinenx_s cn; */
};
typedef union bdk_ctix_ctiinenx bdk_ctix_ctiinenx_t;

static inline uint64_t BDK_CTIX_CTIINENX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIINENX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a<=3) && (b<=2)))
        return 0x87a008010020ll + 0x80000ll * ((a) & 0x3) + 4ll * ((b) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=23) && (b<=2)))
        return 0x87a008010020ll + 0x80000ll * ((a) & 0x1f) + 4ll * ((b) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=47) && (b<=2)))
        return 0x87a008010020ll + 0x80000ll * ((a) & 0x3f) + 4ll * ((b) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=23) && (b<=9)))
        return 0x87a008010020ll + 0x80000ll * ((a) & 0x1f) + 4ll * ((b) & 0xf);
    __bdk_csr_fatal("CTIX_CTIINENX", 2, a, b, 0, 0);
}

#define typedef_BDK_CTIX_CTIINENX(a,b) bdk_ctix_ctiinenx_t
#define bustype_BDK_CTIX_CTIINENX(a,b) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIINENX(a,b) "CTIX_CTIINENX"
#define busnum_BDK_CTIX_CTIINENX(a,b) (a)
#define arguments_BDK_CTIX_CTIINENX(a,b) (a),(b),-1,-1

/**
 * Register (DAB32b) cti#_ctiintack
 *
 * CTI Output Trigger Acknowledge Register
 * Creates soft acknowledges for output triggers.
 */
union bdk_ctix_ctiintack
{
    uint32_t u;
    struct bdk_ctix_ctiintack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t ack                   : 3;  /**< [  2:  0](RO) Acknowledge for output trigger \<n\>.
                                                                 N is the number of CTI triggers implemented as defined by
                                                                     CTI()_CTIDEVID[NUMTRIG]. Bits [31:N] are RAZ/WI.

                                                                 If any of the following is true, writes to ACK\<n\> are ignored:
                                                                 * n \>= CTI()_CTIDEVID[NUMTRIG], the number of implemented triggers.
                                                                 * Output trigger n is not active.
                                                                 * The channel mapping function output, as controlled by
                                                                     CTIOUTEN\<n\>, is still active.

                                                                 Otherwise, if any of the following are true, it is
                                                                     implementation defined whether writes to ACK\<n\> are ignored:
                                                                 * Output trigger n is not implemented.
                                                                 * Output trigger n is not connected.
                                                                 * Output trigger n is self-acknowledging and does not require
                                                                     software acknowledge.

                                                                 Otherwise, the behavior on writes to ACK\<n\> is as follows:
                                                                 0 = No effect.
                                                                 1 = Deactivate the trigger. */
#else /* Word 0 - Little Endian */
        uint32_t ack                   : 3;  /**< [  2:  0](RO) Acknowledge for output trigger \<n\>.
                                                                 N is the number of CTI triggers implemented as defined by
                                                                     CTI()_CTIDEVID[NUMTRIG]. Bits [31:N] are RAZ/WI.

                                                                 If any of the following is true, writes to ACK\<n\> are ignored:
                                                                 * n \>= CTI()_CTIDEVID[NUMTRIG], the number of implemented triggers.
                                                                 * Output trigger n is not active.
                                                                 * The channel mapping function output, as controlled by
                                                                     CTIOUTEN\<n\>, is still active.

                                                                 Otherwise, if any of the following are true, it is
                                                                     implementation defined whether writes to ACK\<n\> are ignored:
                                                                 * Output trigger n is not implemented.
                                                                 * Output trigger n is not connected.
                                                                 * Output trigger n is self-acknowledging and does not require
                                                                     software acknowledge.

                                                                 Otherwise, the behavior on writes to ACK\<n\> is as follows:
                                                                 0 = No effect.
                                                                 1 = Deactivate the trigger. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctiintack_s cn; */
};
typedef union bdk_ctix_ctiintack bdk_ctix_ctiintack_t;

static inline uint64_t BDK_CTIX_CTIINTACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIINTACK(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010010ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010010ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010010ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010010ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIINTACK", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIINTACK(a) bdk_ctix_ctiintack_t
#define bustype_BDK_CTIX_CTIINTACK(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIINTACK(a) "CTIX_CTIINTACK"
#define busnum_BDK_CTIX_CTIINTACK(a) (a)
#define arguments_BDK_CTIX_CTIINTACK(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctiitctrl
 *
 * CTI Integration mode Control Register
 * Enables the CTI to switch from its default mode into
 *     integration mode, where test software can control directly the
 *     inputs and outputs of the processor, for integration testing
 *     or topology detection.
 */
union bdk_ctix_ctiitctrl
{
    uint32_t u;
    struct bdk_ctix_ctiitctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. When IME == 1, the device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
#else /* Word 0 - Little Endian */
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. When IME == 1, the device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctiitctrl_s cn8; */
    struct bdk_ctix_ctiitctrl_cn9
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
typedef union bdk_ctix_ctiitctrl bdk_ctix_ctiitctrl_t;

static inline uint64_t BDK_CTIX_CTIITCTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIITCTRL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010f00ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010f00ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010f00ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010f00ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIITCTRL", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIITCTRL(a) bdk_ctix_ctiitctrl_t
#define bustype_BDK_CTIX_CTIITCTRL(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIITCTRL(a) "CTIX_CTIITCTRL"
#define busnum_BDK_CTIX_CTIITCTRL(a) (a)
#define arguments_BDK_CTIX_CTIITCTRL(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctilar
 *
 * CTI Lock Access Register
 * Allows or disallows access to the CTI registers through a
 *     memory-mapped interface.
 */
union bdk_ctix_ctilar
{
    uint32_t u;
    struct bdk_ctix_ctilar_s
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
    /* struct bdk_ctix_ctilar_s cn; */
};
typedef union bdk_ctix_ctilar bdk_ctix_ctilar_t;

static inline uint64_t BDK_CTIX_CTILAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTILAR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fb0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fb0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fb0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fb0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTILAR", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTILAR(a) bdk_ctix_ctilar_t
#define bustype_BDK_CTIX_CTILAR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTILAR(a) "CTIX_CTILAR"
#define busnum_BDK_CTIX_CTILAR(a) (a)
#define arguments_BDK_CTIX_CTILAR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctilsr
 *
 * CTI Lock Status Register
 * Indicates the current status of the software lock for CTI
 *     registers.
 */
union bdk_ctix_ctilsr
{
    uint32_t u;
    struct bdk_ctix_ctilsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t ntt                   : 1;  /**< [  2:  2](RO) Not thirty-two bit access required. */
        uint32_t slk                   : 1;  /**< [  1:  1](RO/H) Software lock status for this component. For an access to LSR
                                                                     that is not a memory-mapped access, or when the software lock
                                                                     is not implemented, this field is zero.
                                                                 For memory-mapped accesses when the software lock is
                                                                     implemented, possible values of this field are:
                                                                 0 = Lock clear. Writes are permitted to this component's
                                                                     registers.
                                                                 1 = Lock set. Writes to this component's registers are ignored,
                                                                     and reads have no side effects. */
        uint32_t sli                   : 1;  /**< [  0:  0](RO) Software lock implemented. For an access to LSR that is not a
                                                                     memory-mapped access, this field is zero. For memory-mapped
                                                                     accesses, the value of this field is implementation defined.
                                                                     Permitted values are:
                                                                 0 = Software lock not implemented or not memory-mapped access.
                                                                 1 = Software lock implemented and memory-mapped access. */
#else /* Word 0 - Little Endian */
        uint32_t sli                   : 1;  /**< [  0:  0](RO) Software lock implemented. For an access to LSR that is not a
                                                                     memory-mapped access, this field is zero. For memory-mapped
                                                                     accesses, the value of this field is implementation defined.
                                                                     Permitted values are:
                                                                 0 = Software lock not implemented or not memory-mapped access.
                                                                 1 = Software lock implemented and memory-mapped access. */
        uint32_t slk                   : 1;  /**< [  1:  1](RO/H) Software lock status for this component. For an access to LSR
                                                                     that is not a memory-mapped access, or when the software lock
                                                                     is not implemented, this field is zero.
                                                                 For memory-mapped accesses when the software lock is
                                                                     implemented, possible values of this field are:
                                                                 0 = Lock clear. Writes are permitted to this component's
                                                                     registers.
                                                                 1 = Lock set. Writes to this component's registers are ignored,
                                                                     and reads have no side effects. */
        uint32_t ntt                   : 1;  /**< [  2:  2](RO) Not thirty-two bit access required. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctilsr_s cn; */
};
typedef union bdk_ctix_ctilsr bdk_ctix_ctilsr_t;

static inline uint64_t BDK_CTIX_CTILSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTILSR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fb4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fb4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fb4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fb4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTILSR", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTILSR(a) bdk_ctix_ctilsr_t
#define bustype_BDK_CTIX_CTILSR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTILSR(a) "CTIX_CTILSR"
#define busnum_BDK_CTIX_CTILSR(a) (a)
#define arguments_BDK_CTIX_CTILSR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctiouten#
 *
 * CTI Input Channel to Output Trigger Enable Registers
 * Defines which input channels generate output trigger n.
 */
union bdk_ctix_ctioutenx
{
    uint32_t u;
    struct bdk_ctix_ctioutenx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t outen                 : 3;  /**< [  2:  0](R/W) Input channel \<x\> to output trigger \<n\> enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = An event on input channel \<x\> will not cause output trigger
                                                                     \<n\> to be asserted.
                                                                 1 = An event on input channel \<x\> will cause output trigger \<n\> to
                                                                     be asserted.

                                                                 In CNXXXX CTIOUTEN(3..31) are ignored as there are only 3 channels. */
#else /* Word 0 - Little Endian */
        uint32_t outen                 : 3;  /**< [  2:  0](R/W) Input channel \<x\> to output trigger \<n\> enable.
                                                                 N is the number of ECT channels implemented as defined by
                                                                     CTI()_CTIDEVID[NUMCHAN].
                                                                 Bits [31:N] are RAZ/WI.

                                                                 0 = An event on input channel \<x\> will not cause output trigger
                                                                     \<n\> to be asserted.
                                                                 1 = An event on input channel \<x\> will cause output trigger \<n\> to
                                                                     be asserted.

                                                                 In CNXXXX CTIOUTEN(3..31) are ignored as there are only 3 channels. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctioutenx_s cn; */
};
typedef union bdk_ctix_ctioutenx bdk_ctix_ctioutenx_t;

static inline uint64_t BDK_CTIX_CTIOUTENX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIOUTENX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && ((a<=3) && (b<=2)))
        return 0x87a0080100a0ll + 0x80000ll * ((a) & 0x3) + 4ll * ((b) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && ((a<=23) && (b<=2)))
        return 0x87a0080100a0ll + 0x80000ll * ((a) & 0x1f) + 4ll * ((b) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && ((a<=47) && (b<=2)))
        return 0x87a0080100a0ll + 0x80000ll * ((a) & 0x3f) + 4ll * ((b) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=23) && (b<=9)))
        return 0x87a0080100a0ll + 0x80000ll * ((a) & 0x1f) + 4ll * ((b) & 0xf);
    __bdk_csr_fatal("CTIX_CTIOUTENX", 2, a, b, 0, 0);
}

#define typedef_BDK_CTIX_CTIOUTENX(a,b) bdk_ctix_ctioutenx_t
#define bustype_BDK_CTIX_CTIOUTENX(a,b) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIOUTENX(a,b) "CTIX_CTIOUTENX"
#define busnum_BDK_CTIX_CTIOUTENX(a,b) (a)
#define arguments_BDK_CTIX_CTIOUTENX(a,b) (a),(b),-1,-1

/**
 * Register (DAB32b) cti#_ctipidr0
 *
 * CTI Peripheral Identification Register 0
 * Provides information to identify a component.
 */
union bdk_ctix_ctipidr0
{
    uint32_t u;
    struct bdk_ctix_ctipidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::CTI. */
#else /* Word 0 - Little Endian */
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::CTI. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctipidr0_s cn; */
};
typedef union bdk_ctix_ctipidr0 bdk_ctix_ctipidr0_t;

static inline uint64_t BDK_CTIX_CTIPIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIPIDR0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fe0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fe0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fe0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fe0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIPIDR0", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIPIDR0(a) bdk_ctix_ctipidr0_t
#define bustype_BDK_CTIX_CTIPIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIPIDR0(a) "CTIX_CTIPIDR0"
#define busnum_BDK_CTIX_CTIPIDR0(a) (a)
#define arguments_BDK_CTIX_CTIPIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctipidr1
 *
 * CTI Peripheral Identification Register 1
 * Provides information to identify a component.
 */
union bdk_ctix_ctipidr1
{
    uint32_t u;
    struct bdk_ctix_ctipidr1_s
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
    /* struct bdk_ctix_ctipidr1_s cn; */
};
typedef union bdk_ctix_ctipidr1 bdk_ctix_ctipidr1_t;

static inline uint64_t BDK_CTIX_CTIPIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIPIDR1(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fe4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fe4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fe4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fe4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIPIDR1", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIPIDR1(a) bdk_ctix_ctipidr1_t
#define bustype_BDK_CTIX_CTIPIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIPIDR1(a) "CTIX_CTIPIDR1"
#define busnum_BDK_CTIX_CTIPIDR1(a) (a)
#define arguments_BDK_CTIX_CTIPIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctipidr2
 *
 * CTI Peripheral Identification Register 2
 * Provides information to identify a component.
 */
union bdk_ctix_ctipidr2
{
    uint32_t u;
    struct bdk_ctix_ctipidr2_s
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
    /* struct bdk_ctix_ctipidr2_s cn; */
};
typedef union bdk_ctix_ctipidr2 bdk_ctix_ctipidr2_t;

static inline uint64_t BDK_CTIX_CTIPIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIPIDR2(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fe8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fe8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fe8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fe8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIPIDR2", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIPIDR2(a) bdk_ctix_ctipidr2_t
#define bustype_BDK_CTIX_CTIPIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIPIDR2(a) "CTIX_CTIPIDR2"
#define busnum_BDK_CTIX_CTIPIDR2(a) (a)
#define arguments_BDK_CTIX_CTIPIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctipidr3
 *
 * CTI Peripheral Identification Register 3
 * Provides information to identify a component.
 */
union bdk_ctix_ctipidr3
{
    uint32_t u;
    struct bdk_ctix_ctipidr3_s
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
    /* struct bdk_ctix_ctipidr3_s cn; */
};
typedef union bdk_ctix_ctipidr3 bdk_ctix_ctipidr3_t;

static inline uint64_t BDK_CTIX_CTIPIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIPIDR3(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fecll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fecll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fecll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fecll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIPIDR3", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIPIDR3(a) bdk_ctix_ctipidr3_t
#define bustype_BDK_CTIX_CTIPIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIPIDR3(a) "CTIX_CTIPIDR3"
#define busnum_BDK_CTIX_CTIPIDR3(a) (a)
#define arguments_BDK_CTIX_CTIPIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctipidr4
 *
 * CTI Peripheral Identification Register 4
 * Provides information to identify a component.
 */
union bdk_ctix_ctipidr4
{
    uint32_t u;
    struct bdk_ctix_ctipidr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t size                  : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
#else /* Word 0 - Little Endian */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
        uint32_t size                  : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctipidr4_s cn; */
};
typedef union bdk_ctix_ctipidr4 bdk_ctix_ctipidr4_t;

static inline uint64_t BDK_CTIX_CTIPIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIPIDR4(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fd0ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fd0ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fd0ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fd0ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIPIDR4", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIPIDR4(a) bdk_ctix_ctipidr4_t
#define bustype_BDK_CTIX_CTIPIDR4(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIPIDR4(a) "CTIX_CTIPIDR4"
#define busnum_BDK_CTIX_CTIPIDR4(a) (a)
#define arguments_BDK_CTIX_CTIPIDR4(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctipidr5
 *
 * CTI Peripheral Identification Register 5
 * Provides information to identify an external debug component.
 */
union bdk_ctix_ctipidr5
{
    uint32_t u;
    struct bdk_ctix_ctipidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctipidr5_s cn; */
};
typedef union bdk_ctix_ctipidr5 bdk_ctix_ctipidr5_t;

static inline uint64_t BDK_CTIX_CTIPIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIPIDR5(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fd4ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fd4ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fd4ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fd4ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIPIDR5", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIPIDR5(a) bdk_ctix_ctipidr5_t
#define bustype_BDK_CTIX_CTIPIDR5(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIPIDR5(a) "CTIX_CTIPIDR5"
#define busnum_BDK_CTIX_CTIPIDR5(a) (a)
#define arguments_BDK_CTIX_CTIPIDR5(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctipidr6
 *
 * CTI Peripheral Identification Register 6
 * Provides information to identify an external debug component.
 */
union bdk_ctix_ctipidr6
{
    uint32_t u;
    struct bdk_ctix_ctipidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctipidr6_s cn; */
};
typedef union bdk_ctix_ctipidr6 bdk_ctix_ctipidr6_t;

static inline uint64_t BDK_CTIX_CTIPIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIPIDR6(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fd8ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fd8ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fd8ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fd8ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIPIDR6", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIPIDR6(a) bdk_ctix_ctipidr6_t
#define bustype_BDK_CTIX_CTIPIDR6(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIPIDR6(a) "CTIX_CTIPIDR6"
#define busnum_BDK_CTIX_CTIPIDR6(a) (a)
#define arguments_BDK_CTIX_CTIPIDR6(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctipidr7
 *
 * CTI Peripheral Identification Register 7
 * Provides information to identify an external debug component.
 */
union bdk_ctix_ctipidr7
{
    uint32_t u;
    struct bdk_ctix_ctipidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctipidr7_s cn; */
};
typedef union bdk_ctix_ctipidr7 bdk_ctix_ctipidr7_t;

static inline uint64_t BDK_CTIX_CTIPIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTIPIDR7(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010fdcll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010fdcll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010fdcll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010fdcll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTIPIDR7", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTIPIDR7(a) bdk_ctix_ctipidr7_t
#define bustype_BDK_CTIX_CTIPIDR7(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTIPIDR7(a) "CTIX_CTIPIDR7"
#define busnum_BDK_CTIX_CTIPIDR7(a) (a)
#define arguments_BDK_CTIX_CTIPIDR7(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctitriginstatus
 *
 * CTI Trigger In Status Register
 * Provides the status of the trigger inputs.
 */
union bdk_ctix_ctitriginstatus
{
    uint32_t u;
    struct bdk_ctix_ctitriginstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t trin                  : 3;  /**< [  2:  0](RO) Trigger input \<n\> status.
                                                                 N is the number of CTI triggers implemented as defined by
                                                                     CTI()_CTIDEVID[NUMTRIG].
                                                                 Bits [31:N] are 0.

                                                                 Not implemented and not connected input triggers are always inactive.
                                                                 0 = Input trigger n is inactive.
                                                                 1 = Input trigger n is active. */
#else /* Word 0 - Little Endian */
        uint32_t trin                  : 3;  /**< [  2:  0](RO) Trigger input \<n\> status.
                                                                 N is the number of CTI triggers implemented as defined by
                                                                     CTI()_CTIDEVID[NUMTRIG].
                                                                 Bits [31:N] are 0.

                                                                 Not implemented and not connected input triggers are always inactive.
                                                                 0 = Input trigger n is inactive.
                                                                 1 = Input trigger n is active. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctitriginstatus_s cn; */
};
typedef union bdk_ctix_ctitriginstatus bdk_ctix_ctitriginstatus_t;

static inline uint64_t BDK_CTIX_CTITRIGINSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTITRIGINSTATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010130ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010130ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010130ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010130ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTITRIGINSTATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTITRIGINSTATUS(a) bdk_ctix_ctitriginstatus_t
#define bustype_BDK_CTIX_CTITRIGINSTATUS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTITRIGINSTATUS(a) "CTIX_CTITRIGINSTATUS"
#define busnum_BDK_CTIX_CTITRIGINSTATUS(a) (a)
#define arguments_BDK_CTIX_CTITRIGINSTATUS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) cti#_ctitrigoutstatus
 *
 * CTI Trigger Out Status Register
 * Provides the status of the trigger outputs.
 */
union bdk_ctix_ctitrigoutstatus
{
    uint32_t u;
    struct bdk_ctix_ctitrigoutstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t trout                 : 3;  /**< [  2:  0](RO) Trigger output \<n\> status.
                                                                 N is the number of CTI triggers implemented as defined by
                                                                     CTI()_CTIDEVID[NUMTRIG].
                                                                 Bits [31:N] are 0.

                                                                 If output trigger \<n\> is implemented and connected, possible
                                                                     values of this bit are:
                                                                 Otherwise it is implementation defined whether TROUT\<n\> is 0
                                                                     or behaves as above.
                                                                 0 = Output trigger n is inactive.
                                                                 1 = Output trigger n is active. */
#else /* Word 0 - Little Endian */
        uint32_t trout                 : 3;  /**< [  2:  0](RO) Trigger output \<n\> status.
                                                                 N is the number of CTI triggers implemented as defined by
                                                                     CTI()_CTIDEVID[NUMTRIG].
                                                                 Bits [31:N] are 0.

                                                                 If output trigger \<n\> is implemented and connected, possible
                                                                     values of this bit are:
                                                                 Otherwise it is implementation defined whether TROUT\<n\> is 0
                                                                     or behaves as above.
                                                                 0 = Output trigger n is inactive.
                                                                 1 = Output trigger n is active. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ctix_ctitrigoutstatus_s cn; */
};
typedef union bdk_ctix_ctitrigoutstatus bdk_ctix_ctitrigoutstatus_t;

static inline uint64_t BDK_CTIX_CTITRIGOUTSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTIX_CTITRIGOUTSTATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87a008010134ll + 0x80000ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=23))
        return 0x87a008010134ll + 0x80000ll * ((a) & 0x1f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=47))
        return 0x87a008010134ll + 0x80000ll * ((a) & 0x3f);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87a008010134ll + 0x80000ll * ((a) & 0x1f);
    __bdk_csr_fatal("CTIX_CTITRIGOUTSTATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_CTIX_CTITRIGOUTSTATUS(a) bdk_ctix_ctitrigoutstatus_t
#define bustype_BDK_CTIX_CTITRIGOUTSTATUS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_CTIX_CTITRIGOUTSTATUS(a) "CTIX_CTITRIGOUTSTATUS"
#define busnum_BDK_CTIX_CTITRIGOUTSTATUS(a) (a)
#define arguments_BDK_CTIX_CTITRIGOUTSTATUS(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_DAB_CTI_H__ */
