#ifndef __BDK_CSRS_LMT_H__
#define __BDK_CSRS_LMT_H__
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
 * OcteonTX LMT.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Register (RVU_PFVF_BAR2) lmt_lf_lmtcancel
 *
 * RVU VF LMT Cancel Register
 */
union bdk_lmt_lf_lmtcancel
{
    uint64_t u;
    struct bdk_lmt_lf_lmtcancel_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](WO) This register's address is used to perform an AP LMTCANCEL operation. This is
                                                                 only used by code executing on AP cores and has no function when accessed by
                                                                 other entities.

                                                                 Internal:
                                                                 LMTLINE and LMTCANCEL addresses are consumed by APs and never received by
                                                                 RVU. See also RVU_BLOCK_ADDR_E::LMT. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](WO) This register's address is used to perform an AP LMTCANCEL operation. This is
                                                                 only used by code executing on AP cores and has no function when accessed by
                                                                 other entities.

                                                                 Internal:
                                                                 LMTLINE and LMTCANCEL addresses are consumed by APs and never received by
                                                                 RVU. See also RVU_BLOCK_ADDR_E::LMT. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lmt_lf_lmtcancel_s cn; */
};
typedef union bdk_lmt_lf_lmtcancel bdk_lmt_lf_lmtcancel_t;

#define BDK_LMT_LF_LMTCANCEL BDK_LMT_LF_LMTCANCEL_FUNC()
static inline uint64_t BDK_LMT_LF_LMTCANCEL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LMT_LF_LMTCANCEL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x840200100400ll;
    __bdk_csr_fatal("LMT_LF_LMTCANCEL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LMT_LF_LMTCANCEL bdk_lmt_lf_lmtcancel_t
#define bustype_BDK_LMT_LF_LMTCANCEL BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_LMT_LF_LMTCANCEL "LMT_LF_LMTCANCEL"
#define device_bar_BDK_LMT_LF_LMTCANCEL 0x2 /* RVU_BAR2 */
#define busnum_BDK_LMT_LF_LMTCANCEL 0
#define arguments_BDK_LMT_LF_LMTCANCEL -1,-1,-1,-1

/**
 * Register (RVU_PFVF_BAR2) lmt_lf_lmtline#
 *
 * RVU VF LMT Line Registers
 */
union bdk_lmt_lf_lmtlinex
{
    uint64_t u;
    struct bdk_lmt_lf_lmtlinex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](WO) This register's address is the 128-byte LMTLINE used to form LMTST
                                                                 operations. This is only used by code executing on AP cores and has no function
                                                                 when accessed by other entities.

                                                                 Internal:
                                                                 LMTLINE and LMTCANCEL addresses are consumed by APs and never received by
                                                                 RVU. See also RVU_BLOCK_ADDR_E::LMT. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](WO) This register's address is the 128-byte LMTLINE used to form LMTST
                                                                 operations. This is only used by code executing on AP cores and has no function
                                                                 when accessed by other entities.

                                                                 Internal:
                                                                 LMTLINE and LMTCANCEL addresses are consumed by APs and never received by
                                                                 RVU. See also RVU_BLOCK_ADDR_E::LMT. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lmt_lf_lmtlinex_s cn; */
};
typedef union bdk_lmt_lf_lmtlinex bdk_lmt_lf_lmtlinex_t;

static inline uint64_t BDK_LMT_LF_LMTLINEX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LMT_LF_LMTLINEX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=15))
        return 0x840200100000ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("LMT_LF_LMTLINEX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LMT_LF_LMTLINEX(a) bdk_lmt_lf_lmtlinex_t
#define bustype_BDK_LMT_LF_LMTLINEX(a) BDK_CSR_TYPE_RVU_PFVF_BAR2
#define basename_BDK_LMT_LF_LMTLINEX(a) "LMT_LF_LMTLINEX"
#define device_bar_BDK_LMT_LF_LMTLINEX(a) 0x2 /* RVU_BAR2 */
#define busnum_BDK_LMT_LF_LMTLINEX(a) (a)
#define arguments_BDK_LMT_LF_LMTLINEX(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_LMT_H__ */
