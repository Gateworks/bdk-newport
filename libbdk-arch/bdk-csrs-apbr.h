#ifndef __BDK_CSRS_APBR_H__
#define __BDK_CSRS_APBR_H__
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
 * Cavium APBR.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration apbr_bar_e
 *
 * APBR Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_APBR_BAR_E_APBRX_PF_BAR0(a) (0x8fb000000000ll + 0x100000ll * (a))
#define BDK_APBR_BAR_E_APBRX_PF_BAR0_SIZE 0x100000ull

/**
 * Register (NCB) apbr#_const
 *
 * INTERNAL: APBR Fake Register
 *
 * This register is only to satisfy the tools, it has no physical manifestation.
 */
union bdk_apbrx_const
{
    uint64_t u;
    struct bdk_apbrx_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_apbrx_const_s cn; */
};
typedef union bdk_apbrx_const bdk_apbrx_const_t;

static inline uint64_t BDK_APBRX_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_APBRX_CONST(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=53))
        return 0x8fb000000000ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("APBRX_CONST", 1, a, 0, 0, 0);
}

#define typedef_BDK_APBRX_CONST(a) bdk_apbrx_const_t
#define bustype_BDK_APBRX_CONST(a) BDK_CSR_TYPE_NCB
#define basename_BDK_APBRX_CONST(a) "APBRX_CONST"
#define device_bar_BDK_APBRX_CONST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_APBRX_CONST(a) (a)
#define arguments_BDK_APBRX_CONST(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_APBR_H__ */
