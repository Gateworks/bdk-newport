#ifndef __BDK_CSRS_APBR_H__
#define __BDK_CSRS_APBR_H__
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
 * OcteonTX APBR.
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
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=53))
        return 0x8fb000000000ll + 0x100000ll * ((a) & 0x3f);
    __bdk_csr_fatal("APBRX_CONST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_APBRX_CONST(a) bdk_apbrx_const_t
#define bustype_BDK_APBRX_CONST(a) BDK_CSR_TYPE_NCB
#define basename_BDK_APBRX_CONST(a) "APBRX_CONST"
#define device_bar_BDK_APBRX_CONST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_APBRX_CONST(a) (a)
#define arguments_BDK_APBRX_CONST(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_APBR_H__ */
