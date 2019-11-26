#ifndef __BDK_CSRS_LBK_H__
#define __BDK_CSRS_LBK_H__
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
 * OcteonTX LBK.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration lbk_bar_e
 *
 * LBK Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_LBK_BAR_E_LBKX_PF_BAR0_CN8(a) (0x87e018000000ll + 0x1000000ll * (a))
#define BDK_LBK_BAR_E_LBKX_PF_BAR0_CN8_SIZE 0x100000ull
#define BDK_LBK_BAR_E_LBKX_PF_BAR0_CN9(a) (0x87e018000000ll + 0x1000000ll * (a))
#define BDK_LBK_BAR_E_LBKX_PF_BAR0_CN9_SIZE 0x10000ull
#define BDK_LBK_BAR_E_LBKX_PF_BAR4(a) (0x87e018f00000ll + 0x1000000ll * (a))
#define BDK_LBK_BAR_E_LBKX_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration lbk_connect_e
 *
 * LBK Source Connection Enumeration
 * Enumerates LBK()_CONST[SRC] and LBK()_CONST[DEST].
 */
#define BDK_LBK_CONNECT_E_NICX(a) (0 + (a))
#define BDK_LBK_CONNECT_E_NIXX(a) (0 + (a))
#define BDK_LBK_CONNECT_E_PKIX(a) (4 + (a))
#define BDK_LBK_CONNECT_E_PKOX(a) (8 + (a))

/**
 * Enumeration lbk_int_vec_e
 *
 * LBK MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_LBK_INT_VEC_E_ERR (0)

/**
 * Register (RSL) lbk#_bist_result
 *
 * LBK BIST Result Register
 * This register provides access to the internal BIST results. Each bit is the BIST result of an
 * individual memory (per bit, 0 = pass and 1 = fail).
 */
union bdk_lbkx_bist_result
{
    uint64_t u;
    struct bdk_lbkx_bist_result_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t dat                   : 1;  /**< [  0:  0](RO) BIST result of the data FIFO RAM. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 1;  /**< [  0:  0](RO) BIST result of the data FIFO RAM. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_bist_result_s cn; */
};
typedef union bdk_lbkx_bist_result bdk_lbkx_bist_result_t;

static inline uint64_t BDK_LBKX_BIST_RESULT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_BIST_RESULT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000020ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000020ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("LBKX_BIST_RESULT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_BIST_RESULT(a) bdk_lbkx_bist_result_t
#define bustype_BDK_LBKX_BIST_RESULT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_BIST_RESULT(a) "LBKX_BIST_RESULT"
#define device_bar_BDK_LBKX_BIST_RESULT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_BIST_RESULT(a) (a)
#define arguments_BDK_LBKX_BIST_RESULT(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_bp_test
 *
 * INTERNAL: Loopback Backpressure Test Register
 */
union bdk_lbkx_bp_test
{
    uint64_t u;
    struct bdk_lbkx_bp_test_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Backpressure express FIFO controller from sending out X2P request that is
                                                                 asking for X2P grant.
                                                                 \<60\> = Backpressure normal FIFO controller from sending out X2P request that is
                                                                 asking for X2P grant. */
        uint64_t reserved_24_59        : 36;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = Reserved.
                                                                   \<21:20\> = Reserved.
                                                                   \<19:18\> = Config 1 for bit 61.
                                                                   \<17:16\> = Config 0 for bit 60. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one.
                                                                 For non-100% bp configurations, a small lfsr frequency will cause more frequent
                                                                 toggling of the backpressure signal while a larger frequency will produce longer
                                                                 segments of asserted or deasserted backpressure. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one.
                                                                 For non-100% bp configurations, a small lfsr frequency will cause more frequent
                                                                 toggling of the backpressure signal while a larger frequency will produce longer
                                                                 segments of asserted or deasserted backpressure. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 8;  /**< [ 23: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                   \<23:22\> = Reserved.
                                                                   \<21:20\> = Reserved.
                                                                   \<19:18\> = Config 1 for bit 61.
                                                                   \<17:16\> = Config 0 for bit 60. */
        uint64_t reserved_24_59        : 36;
        uint64_t enable                : 4;  /**< [ 63: 60](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 \<63\> = Reserved.
                                                                 \<62\> = Reserved.
                                                                 \<61\> = Backpressure express FIFO controller from sending out X2P request that is
                                                                 asking for X2P grant.
                                                                 \<60\> = Backpressure normal FIFO controller from sending out X2P request that is
                                                                 asking for X2P grant. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_bp_test_s cn; */
};
typedef union bdk_lbkx_bp_test bdk_lbkx_bp_test_t;

static inline uint64_t BDK_LBKX_BP_TEST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_BP_TEST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x87e018000028ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=3))
        return 0x87e018000028ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e018000028ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e018000028ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("LBKX_BP_TEST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_BP_TEST(a) bdk_lbkx_bp_test_t
#define bustype_BDK_LBKX_BP_TEST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_BP_TEST(a) "LBKX_BP_TEST"
#define device_bar_BDK_LBKX_BP_TEST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_BP_TEST(a) (a)
#define arguments_BDK_LBKX_BP_TEST(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_ch#_pkind
 *
 * LBK Channel to Port Kind Register
 */
union bdk_lbkx_chx_pkind
{
    uint64_t u;
    struct bdk_lbkx_chx_pkind_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t pkind                 : 6;  /**< [  5:  0](R/W) Loopback pkind for the respective loopback channel. */
#else /* Word 0 - Little Endian */
        uint64_t pkind                 : 6;  /**< [  5:  0](R/W) Loopback pkind for the respective loopback channel. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_chx_pkind_s cn; */
};
typedef union bdk_lbkx_chx_pkind bdk_lbkx_chx_pkind_t;

static inline uint64_t BDK_LBKX_CHX_PKIND(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_CHX_PKIND(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b<=63)))
        return 0x87e018000200ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=3) && (b<=63)))
        return 0x87e018000200ll + 0x1000000ll * ((a) & 0x3) + 8ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a==0) && (b<=63)))
        return 0x87e018000200ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=3) && (b<=63)))
        return 0x87e018000200ll + 0x1000000ll * ((a) & 0x3) + 8ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a==0) && (b<=63)))
        return 0x87e018000200ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a==0) && (b<=63)))
        return 0x87e018000200ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x3f);
    __bdk_csr_fatal("LBKX_CHX_PKIND", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_CHX_PKIND(a,b) bdk_lbkx_chx_pkind_t
#define bustype_BDK_LBKX_CHX_PKIND(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_CHX_PKIND(a,b) "LBKX_CHX_PKIND"
#define device_bar_BDK_LBKX_CHX_PKIND(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_CHX_PKIND(a,b) (a)
#define arguments_BDK_LBKX_CHX_PKIND(a,b) (a),(b),-1,-1

/**
 * Register (RSL) lbk#_clk_gate_ctl
 *
 * LBK Reset Register
 * This register is for diagnostic use only.
 */
union bdk_lbkx_clk_gate_ctl
{
    uint64_t u;
    struct bdk_lbkx_clk_gate_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t dis                   : 1;  /**< [  0:  0](R/W) Clock gate disable. When set, forces gated clock to always on. */
#else /* Word 0 - Little Endian */
        uint64_t dis                   : 1;  /**< [  0:  0](R/W) Clock gate disable. When set, forces gated clock to always on. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_clk_gate_ctl_s cn8; */
    struct bdk_lbkx_clk_gate_ctl_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t dis                   : 1;  /**< [  0:  0](R/W) Clock gate disable. When set, forces gated clock to always on. For diagnostic
                                                                 use only. */
#else /* Word 0 - Little Endian */
        uint64_t dis                   : 1;  /**< [  0:  0](R/W) Clock gate disable. When set, forces gated clock to always on. For diagnostic
                                                                 use only. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_lbkx_clk_gate_ctl bdk_lbkx_clk_gate_ctl_t;

static inline uint64_t BDK_LBKX_CLK_GATE_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_CLK_GATE_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000008ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000008ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x87e018000008ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=3))
        return 0x87e018000008ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e018000008ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e018000008ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("LBKX_CLK_GATE_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_CLK_GATE_CTL(a) bdk_lbkx_clk_gate_ctl_t
#define bustype_BDK_LBKX_CLK_GATE_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_CLK_GATE_CTL(a) "LBKX_CLK_GATE_CTL"
#define device_bar_BDK_LBKX_CLK_GATE_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_CLK_GATE_CTL(a) (a)
#define arguments_BDK_LBKX_CLK_GATE_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_const
 *
 * LBK Constants Register
 * This register contains constants for software discovery.
 */
union bdk_lbkx_const
{
    uint64_t u;
    struct bdk_lbkx_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What blocks this LBK transmits traffic to. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::NIC(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What blocks this LBK receives traffic from. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::NIC(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in loopback data FIFO.
                                                                 For LBK0, 0x3000.

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
#else /* Word 0 - Little Endian */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in loopback data FIFO.
                                                                 For LBK0, 0x3000.

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What blocks this LBK receives traffic from. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::NIC(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What blocks this LBK transmits traffic to. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::NIC(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_const_s cn8; */
    /* struct bdk_lbkx_const_s cn81xx; */
    struct bdk_lbkx_const_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What blocks this LBK connects. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::PKI(0).
                                                                 For LBK1, indicates LBK_CONNECT_E::PKI(0).
                                                                 For LBK2, indicates LBK_CONNECT_E::NIC(0).
                                                                 For LBK3, indicates LBK_CONNECT_E::NIC(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What blocks this LBK connects. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::PKO(0).
                                                                 For LBK1, indicates LBK_CONNECT_E::NIC(0).
                                                                 For LBK2, indicates LBK_CONNECT_E::PKO(0).
                                                                 For LBK3, indicates LBK_CONNECT_E::NIC(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in loopback data FIFO.
                                                                 For LBK0, 0x1000.
                                                                 For LBK1, 0x3000.
                                                                 For LBK2, 0x1000.
                                                                 For LBK3, 0x3000.

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
#else /* Word 0 - Little Endian */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in loopback data FIFO.
                                                                 For LBK0, 0x1000.
                                                                 For LBK1, 0x3000.
                                                                 For LBK2, 0x1000.
                                                                 For LBK3, 0x3000.

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What blocks this LBK connects. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::PKO(0).
                                                                 For LBK1, indicates LBK_CONNECT_E::NIC(0).
                                                                 For LBK2, indicates LBK_CONNECT_E::PKO(0).
                                                                 For LBK3, indicates LBK_CONNECT_E::NIC(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What blocks this LBK connects. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::PKI(0).
                                                                 For LBK1, indicates LBK_CONNECT_E::PKI(0).
                                                                 For LBK2, indicates LBK_CONNECT_E::NIC(0).
                                                                 For LBK3, indicates LBK_CONNECT_E::NIC(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn83xx;
    struct bdk_lbkx_const_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What blocks this LBK transmits traffic to. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::NIX(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What blocks this LBK receives traffic from. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::NIX(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in loopback data FIFO.
                                                                 For LBK0, 0x3000 for each of FIFOs (express/non-express).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
#else /* Word 0 - Little Endian */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in loopback data FIFO.
                                                                 For LBK0, 0x3000 for each of FIFOs (express/non-express).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What blocks this LBK receives traffic from. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::NIX(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What blocks this LBK transmits traffic to. Enumerated by LBK_CONNECT_E.
                                                                 For LBK0, indicates LBK_CONNECT_E::NIX(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn9;
    /* struct bdk_lbkx_const_cn9 cn96xxp1; */
    struct bdk_lbkx_const_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What block this LBK transmits traffic to. Enumerated by LBK_CONNECT_E.
                                                                 For LBK(0), indicates LBK_CONNECT_E::NIX(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What block this LBK receives traffic from. Enumerated by LBK_CONNECT_E.
                                                                 For LBK(0), indicates LBK_CONNECT_E::NIX(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in each loopback data FIFO (express/non-express).
                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
#else /* Word 0 - Little Endian */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in each loopback data FIFO (express/non-express).
                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What block this LBK receives traffic from. Enumerated by LBK_CONNECT_E.
                                                                 For LBK(0), indicates LBK_CONNECT_E::NIX(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What block this LBK transmits traffic to. Enumerated by LBK_CONNECT_E.
                                                                 For LBK(0), indicates LBK_CONNECT_E::NIX(0).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn96xxp3;
    struct bdk_lbkx_const_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What block this LBK transmits traffic to. Enumerated by LBK_CONNECT_E.
                                                                 For LBK(0), indicates LBK_CONNECT_E::NIX(0).
                                                                 For LBK(1), indicates LBK_CONNECT_E::NIX(1).
                                                                 For LBK(2), indicates LBK_CONNECT_E::NIX(0).
                                                                 For LBK(3), indicates LBK_CONNECT_E::NIX(1).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What block this LBK receives traffic from. Enumerated by LBK_CONNECT_E.
                                                                 For LBK(0), indicates LBK_CONNECT_E::NIX(0).
                                                                 For LBK(1), indicates LBK_CONNECT_E::NIX(0).
                                                                 For LBK(2), indicates LBK_CONNECT_E::NIX(1).
                                                                 For LBK(3), indicates LBK_CONNECT_E::NIX(1).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in each loopback data FIFO (express/non-express).
                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
#else /* Word 0 - Little Endian */
        uint64_t buf_size              : 24; /**< [ 23:  0](RO) Number of bytes in each loopback data FIFO (express/non-express).
                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t src                   : 4;  /**< [ 27: 24](RO) What block this LBK receives traffic from. Enumerated by LBK_CONNECT_E.
                                                                 For LBK(0), indicates LBK_CONNECT_E::NIX(0).
                                                                 For LBK(1), indicates LBK_CONNECT_E::NIX(0).
                                                                 For LBK(2), indicates LBK_CONNECT_E::NIX(1).
                                                                 For LBK(3), indicates LBK_CONNECT_E::NIX(1).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t dest                  : 4;  /**< [ 31: 28](RO) What block this LBK transmits traffic to. Enumerated by LBK_CONNECT_E.
                                                                 For LBK(0), indicates LBK_CONNECT_E::NIX(0).
                                                                 For LBK(1), indicates LBK_CONNECT_E::NIX(1).
                                                                 For LBK(2), indicates LBK_CONNECT_E::NIX(0).
                                                                 For LBK(3), indicates LBK_CONNECT_E::NIX(1).

                                                                 Internal:
                                                                 lbk.v takes this from input straps set by the instantiation. */
        uint64_t chan                  : 16; /**< [ 47: 32](RO) Number of channels supported. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_lbkx_const_cn9 cnf95xxp1; */
    /* struct bdk_lbkx_const_cn96xxp3 cnf95xxp2; */
    /* struct bdk_lbkx_const_cn96xxp3 loki; */
};
typedef union bdk_lbkx_const bdk_lbkx_const_t;

static inline uint64_t BDK_LBKX_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_CONST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000010ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000010ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x87e018000010ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=3))
        return 0x87e018000010ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e018000010ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e018000010ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("LBKX_CONST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_CONST(a) bdk_lbkx_const_t
#define bustype_BDK_LBKX_CONST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_CONST(a) "LBKX_CONST"
#define device_bar_BDK_LBKX_CONST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_CONST(a) (a)
#define arguments_BDK_LBKX_CONST(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_const1
 *
 * LBK Constants 1 Register
 * This register contains constants for software discovery.
 */
union bdk_lbkx_const1
{
    uint64_t u;
    struct bdk_lbkx_const1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_const1_s cn; */
};
typedef union bdk_lbkx_const1 bdk_lbkx_const1_t;

static inline uint64_t BDK_LBKX_CONST1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_CONST1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000018ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000018ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x87e018000018ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=3))
        return 0x87e018000018ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e018000018ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e018000018ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("LBKX_CONST1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_CONST1(a) bdk_lbkx_const1_t
#define bustype_BDK_LBKX_CONST1(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_CONST1(a) "LBKX_CONST1"
#define device_bar_BDK_LBKX_CONST1(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_CONST1(a) (a)
#define arguments_BDK_LBKX_CONST1(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_csclk_active_pc
 *
 * LBK Conditional Clock Counter Register
 * This register counts conditional clocks cycles.
 */
union bdk_lbkx_csclk_active_pc
{
    uint64_t u;
    struct bdk_lbkx_csclk_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_csclk_active_pc_s cn; */
};
typedef union bdk_lbkx_csclk_active_pc bdk_lbkx_csclk_active_pc_t;

static inline uint64_t BDK_LBKX_CSCLK_ACTIVE_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_CSCLK_ACTIVE_PC(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x87e018000030ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=3))
        return 0x87e018000030ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e018000030ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e018000030ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("LBKX_CSCLK_ACTIVE_PC", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_CSCLK_ACTIVE_PC(a) bdk_lbkx_csclk_active_pc_t
#define bustype_BDK_LBKX_CSCLK_ACTIVE_PC(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_CSCLK_ACTIVE_PC(a) "LBKX_CSCLK_ACTIVE_PC"
#define device_bar_BDK_LBKX_CSCLK_ACTIVE_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_CSCLK_ACTIVE_PC(a) (a)
#define arguments_BDK_LBKX_CSCLK_ACTIVE_PC(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_ecc_cfg
 *
 * LBK ECC Configuration Register
 */
union bdk_lbkx_ecc_cfg
{
    uint64_t u;
    struct bdk_lbkx_ecc_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t dat_flip              : 2;  /**< [  2:  1](R/W) Testing feature. Flip syndrome bits \<1:0\> on writes to the data FIFO RAM to test
                                                                 single-bit or double-bit errors. */
        uint64_t dat_cdis              : 1;  /**< [  0:  0](R/W) Disable ECC corrector on data FIFO RAM outputs. */
#else /* Word 0 - Little Endian */
        uint64_t dat_cdis              : 1;  /**< [  0:  0](R/W) Disable ECC corrector on data FIFO RAM outputs. */
        uint64_t dat_flip              : 2;  /**< [  2:  1](R/W) Testing feature. Flip syndrome bits \<1:0\> on writes to the data FIFO RAM to test
                                                                 single-bit or double-bit errors. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_ecc_cfg_s cn; */
};
typedef union bdk_lbkx_ecc_cfg bdk_lbkx_ecc_cfg_t;

static inline uint64_t BDK_LBKX_ECC_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_ECC_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000060ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000060ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("LBKX_ECC_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_ECC_CFG(a) bdk_lbkx_ecc_cfg_t
#define bustype_BDK_LBKX_ECC_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_ECC_CFG(a) "LBKX_ECC_CFG"
#define device_bar_BDK_LBKX_ECC_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_ECC_CFG(a) (a)
#define arguments_BDK_LBKX_ECC_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_err_int
 *
 * LBK Error Interrupt Register
 */
union bdk_lbkx_err_int
{
    uint64_t u;
    struct bdk_lbkx_err_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1C/H) Internal assertion, packet channel credit FIFO had an overflow. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1C/H) Internal assertion, packet channel credit FIFO had an underflow. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1C/H) Internal assertion, packet data FIFO had an overflow. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1C/H) Internal assertion, packet data FIFO had an underflow. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1C/H) Data RAM had a ECC double-bit error. */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1C/H) Data RAM had a ECC single-bit error. */
#else /* Word 0 - Little Endian */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1C/H) Data RAM had a ECC single-bit error. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1C/H) Data RAM had a ECC double-bit error. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1C/H) Internal assertion, packet data FIFO had an underflow. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1C/H) Internal assertion, packet data FIFO had an overflow. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1C/H) Internal assertion, packet channel credit FIFO had an underflow. */
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1C/H) Internal assertion, packet channel credit FIFO had an overflow. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_err_int_s cn; */
};
typedef union bdk_lbkx_err_int bdk_lbkx_err_int_t;

static inline uint64_t BDK_LBKX_ERR_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_ERR_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000040ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000040ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("LBKX_ERR_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_ERR_INT(a) bdk_lbkx_err_int_t
#define bustype_BDK_LBKX_ERR_INT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_ERR_INT(a) "LBKX_ERR_INT"
#define device_bar_BDK_LBKX_ERR_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_ERR_INT(a) (a)
#define arguments_BDK_LBKX_ERR_INT(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_err_int_ena_w1c
 *
 * LBK Error Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_lbkx_err_int_ena_w1c
{
    uint64_t u;
    struct bdk_lbkx_err_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[CHAN_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[CHAN_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[DAT_OFLOW]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[DAT_DBE]. */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[DAT_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[DAT_SBE]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[DAT_DBE]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[DAT_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[CHAN_UFLOW]. */
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for LBK(0)_ERR_INT[CHAN_OFLOW]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_err_int_ena_w1c_s cn8; */
    /* struct bdk_lbkx_err_int_ena_w1c_s cn81xx; */
    struct bdk_lbkx_err_int_ena_w1c_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[CHAN_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[CHAN_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[DAT_OFLOW]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[DAT_DBE]. */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[DAT_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[DAT_SBE]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[DAT_DBE]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[DAT_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[CHAN_UFLOW]. */
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for LBK(0..3)_ERR_INT[CHAN_OFLOW]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_lbkx_err_int_ena_w1c bdk_lbkx_err_int_ena_w1c_t;

static inline uint64_t BDK_LBKX_ERR_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_ERR_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000050ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000050ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("LBKX_ERR_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_ERR_INT_ENA_W1C(a) bdk_lbkx_err_int_ena_w1c_t
#define bustype_BDK_LBKX_ERR_INT_ENA_W1C(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_ERR_INT_ENA_W1C(a) "LBKX_ERR_INT_ENA_W1C"
#define device_bar_BDK_LBKX_ERR_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_ERR_INT_ENA_W1C(a) (a)
#define arguments_BDK_LBKX_ERR_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_err_int_ena_w1s
 *
 * LBK Error Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_lbkx_err_int_ena_w1s
{
    uint64_t u;
    struct bdk_lbkx_err_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[CHAN_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[CHAN_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[DAT_OFLOW]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[DAT_DBE]. */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[DAT_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[DAT_SBE]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[DAT_DBE]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[DAT_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[CHAN_UFLOW]. */
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for LBK(0)_ERR_INT[CHAN_OFLOW]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_err_int_ena_w1s_s cn8; */
    /* struct bdk_lbkx_err_int_ena_w1s_s cn81xx; */
    struct bdk_lbkx_err_int_ena_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[CHAN_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[CHAN_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[DAT_OFLOW]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[DAT_DBE]. */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[DAT_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[DAT_SBE]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[DAT_DBE]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[DAT_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[CHAN_UFLOW]. */
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for LBK(0..3)_ERR_INT[CHAN_OFLOW]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_lbkx_err_int_ena_w1s bdk_lbkx_err_int_ena_w1s_t;

static inline uint64_t BDK_LBKX_ERR_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_ERR_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000058ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000058ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("LBKX_ERR_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_ERR_INT_ENA_W1S(a) bdk_lbkx_err_int_ena_w1s_t
#define bustype_BDK_LBKX_ERR_INT_ENA_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_ERR_INT_ENA_W1S(a) "LBKX_ERR_INT_ENA_W1S"
#define device_bar_BDK_LBKX_ERR_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_ERR_INT_ENA_W1S(a) (a)
#define arguments_BDK_LBKX_ERR_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_err_int_w1s
 *
 * LBK Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_lbkx_err_int_w1s
{
    uint64_t u;
    struct bdk_lbkx_err_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets LBK(0)_ERR_INT[CHAN_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets LBK(0)_ERR_INT[CHAN_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1S/H) Reads or sets LBK(0)_ERR_INT[DAT_OFLOW]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets LBK(0)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets LBK(0)_ERR_INT[DAT_DBE]. */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets LBK(0)_ERR_INT[DAT_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets LBK(0)_ERR_INT[DAT_SBE]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets LBK(0)_ERR_INT[DAT_DBE]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets LBK(0)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1S/H) Reads or sets LBK(0)_ERR_INT[DAT_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets LBK(0)_ERR_INT[CHAN_UFLOW]. */
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets LBK(0)_ERR_INT[CHAN_OFLOW]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_err_int_w1s_s cn8; */
    /* struct bdk_lbkx_err_int_w1s_s cn81xx; */
    struct bdk_lbkx_err_int_w1s_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[CHAN_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[CHAN_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[DAT_OFLOW]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[DAT_DBE]. */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[DAT_SBE]. */
#else /* Word 0 - Little Endian */
        uint64_t dat_sbe               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[DAT_SBE]. */
        uint64_t dat_dbe               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[DAT_DBE]. */
        uint64_t dat_uflow             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[DAT_UFLOW]. */
        uint64_t dat_oflow             : 1;  /**< [  3:  3](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[DAT_OFLOW]. */
        uint64_t chan_uflow            : 1;  /**< [  4:  4](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[CHAN_UFLOW]. */
        uint64_t chan_oflow            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets LBK(0..3)_ERR_INT[CHAN_OFLOW]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn83xx;
};
typedef union bdk_lbkx_err_int_w1s bdk_lbkx_err_int_w1s_t;

static inline uint64_t BDK_LBKX_ERR_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_ERR_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000048ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000048ll + 0x1000000ll * ((a) & 0x3);
    __bdk_csr_fatal("LBKX_ERR_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_ERR_INT_W1S(a) bdk_lbkx_err_int_w1s_t
#define bustype_BDK_LBKX_ERR_INT_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_ERR_INT_W1S(a) "LBKX_ERR_INT_W1S"
#define device_bar_BDK_LBKX_ERR_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_ERR_INT_W1S(a) (a)
#define arguments_BDK_LBKX_ERR_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) lbk#_msix_pba#
 *
 * LBK MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the LBK_INT_VEC_E enumeration.
 */
union bdk_lbkx_msix_pbax
{
    uint64_t u;
    struct bdk_lbkx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated LBK()_MSIX_VEC()_CTL, enumerated by
                                                                 LBK_INT_VEC_E. Bits that have no associated LBK_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated LBK()_MSIX_VEC()_CTL, enumerated by
                                                                 LBK_INT_VEC_E. Bits that have no associated LBK_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_msix_pbax_s cn; */
};
typedef union bdk_lbkx_msix_pbax bdk_lbkx_msix_pbax_t;

static inline uint64_t BDK_LBKX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e018ff0000ll + 0x1000000ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=3) && (b==0)))
        return 0x87e018ff0000ll + 0x1000000ll * ((a) & 0x3) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("LBKX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_MSIX_PBAX(a,b) bdk_lbkx_msix_pbax_t
#define bustype_BDK_LBKX_MSIX_PBAX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_MSIX_PBAX(a,b) "LBKX_MSIX_PBAX"
#define device_bar_BDK_LBKX_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_LBKX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_LBKX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) lbk#_msix_vec#_addr
 *
 * LBK MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the LBK_INT_VEC_E enumeration.
 */
union bdk_lbkx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_lbkx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's LBK()_MSIX_VEC()_ADDR, LBK()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of LBK()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_LBK_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's LBK()_MSIX_VEC()_ADDR, LBK()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of LBK()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_LBK_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_msix_vecx_addr_s cn; */
};
typedef union bdk_lbkx_msix_vecx_addr bdk_lbkx_msix_vecx_addr_t;

static inline uint64_t BDK_LBKX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e018f00000ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=3) && (b==0)))
        return 0x87e018f00000ll + 0x1000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("LBKX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_MSIX_VECX_ADDR(a,b) bdk_lbkx_msix_vecx_addr_t
#define bustype_BDK_LBKX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_MSIX_VECX_ADDR(a,b) "LBKX_MSIX_VECX_ADDR"
#define device_bar_BDK_LBKX_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_LBKX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_LBKX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) lbk#_msix_vec#_ctl
 *
 * LBK MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the LBK_INT_VEC_E enumeration.
 */
union bdk_lbkx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_lbkx_msix_vecx_ctl_s
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
    /* struct bdk_lbkx_msix_vecx_ctl_s cn; */
};
typedef union bdk_lbkx_msix_vecx_ctl bdk_lbkx_msix_vecx_ctl_t;

static inline uint64_t BDK_LBKX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e018f00008ll + 0x1000000ll * ((a) & 0x0) + 0x10ll * ((b) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && ((a<=3) && (b==0)))
        return 0x87e018f00008ll + 0x1000000ll * ((a) & 0x3) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("LBKX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_MSIX_VECX_CTL(a,b) bdk_lbkx_msix_vecx_ctl_t
#define bustype_BDK_LBKX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_MSIX_VECX_CTL(a,b) "LBKX_MSIX_VECX_CTL"
#define device_bar_BDK_LBKX_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_LBKX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_LBKX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) lbk#_sft_rst
 *
 * LBK Reset Register
 */
union bdk_lbkx_sft_rst
{
    uint64_t u;
    struct bdk_lbkx_sft_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1) Reset. When set, causes a reset of LBK, excluding RSL. */
#else /* Word 0 - Little Endian */
        uint64_t reset                 : 1;  /**< [  0:  0](R/W1) Reset. When set, causes a reset of LBK, excluding RSL. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_lbkx_sft_rst_s cn; */
};
typedef union bdk_lbkx_sft_rst bdk_lbkx_sft_rst_t;

static inline uint64_t BDK_LBKX_SFT_RST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_LBKX_SFT_RST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e018000000ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e018000000ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX) && (a==0))
        return 0x87e018000000ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=3))
        return 0x87e018000000ll + 0x1000000ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e018000000ll + 0x1000000ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_LOKI) && (a==0))
        return 0x87e018000000ll + 0x1000000ll * ((a) & 0x0);
    __bdk_csr_fatal("LBKX_SFT_RST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_LBKX_SFT_RST(a) bdk_lbkx_sft_rst_t
#define bustype_BDK_LBKX_SFT_RST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_LBKX_SFT_RST(a) "LBKX_SFT_RST"
#define device_bar_BDK_LBKX_SFT_RST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_LBKX_SFT_RST(a) (a)
#define arguments_BDK_LBKX_SFT_RST(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_LBK_H__ */
