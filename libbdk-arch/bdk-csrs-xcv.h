#ifndef __BDK_CSRS_XCV_H__
#define __BDK_CSRS_XCV_H__
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
 * OcteonTX XCV.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration xcv_bar_e
 *
 * XCV Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_XCV_BAR_E_XCVX_PF_BAR0(a) (0x87e0db000000ll + 0ll * (a))
#define BDK_XCV_BAR_E_XCVX_PF_BAR0_SIZE 0x100000ull
#define BDK_XCV_BAR_E_XCVX_PF_BAR4(a) (0x87e0dbf00000ll + 0ll * (a))
#define BDK_XCV_BAR_E_XCVX_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration xcv_int_vec_e
 *
 * XCV MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_XCV_INT_VEC_E_INT (0)

/**
 * Register (RSL) xcv#_batch_crd_ret
 *
 * XCV Batch Credit Return Register
 */
union bdk_xcvx_batch_crd_ret
{
    uint64_t u;
    struct bdk_xcvx_batch_crd_ret_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t crd_ret               : 1;  /**< [  0:  0](WO) In case of the reset event, when this register is written XCV sends out the
                                                                 initial credit batch to BGX. Initial credit value of 16. The write will only
                                                                 take effect when XCV_RESET[ENABLE] is set. */
#else /* Word 0 - Little Endian */
        uint64_t crd_ret               : 1;  /**< [  0:  0](WO) In case of the reset event, when this register is written XCV sends out the
                                                                 initial credit batch to BGX. Initial credit value of 16. The write will only
                                                                 take effect when XCV_RESET[ENABLE] is set. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_batch_crd_ret_s cn; */
};
typedef union bdk_xcvx_batch_crd_ret bdk_xcvx_batch_crd_ret_t;

static inline uint64_t BDK_XCVX_BATCH_CRD_RET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_BATCH_CRD_RET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000100ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_BATCH_CRD_RET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_BATCH_CRD_RET(a) bdk_xcvx_batch_crd_ret_t
#define bustype_BDK_XCVX_BATCH_CRD_RET(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_BATCH_CRD_RET(a) "XCVX_BATCH_CRD_RET"
#define device_bar_BDK_XCVX_BATCH_CRD_RET(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_BATCH_CRD_RET(a) (a)
#define arguments_BDK_XCVX_BATCH_CRD_RET(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_comp_ctl
 *
 * XCV Compensation Controller Register
 * This register controls programmable compensation.
 */
union bdk_xcvx_comp_ctl
{
    uint64_t u;
    struct bdk_xcvx_comp_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t drv_byp               : 1;  /**< [ 63: 63](R/W) When set, bypass the compensation controller and use
                                                                 [DRV_NCTL] and [DRV_PCTL]. */
        uint64_t reserved_61_62        : 2;
        uint64_t cmp_pctl              : 5;  /**< [ 60: 56](RO/H) PCTL drive strength from the hardware compensation controller. */
        uint64_t reserved_53_55        : 3;
        uint64_t cmp_nctl              : 5;  /**< [ 52: 48](RO/H) NCTL drive strength from the hardware compensation controller. */
        uint64_t reserved_45_47        : 3;
        uint64_t drv_pctl              : 5;  /**< [ 44: 40](R/W) PCTL drive strength to use in bypass mode.
                                                                 Value of 11 is for 50 ohm termination. */
        uint64_t reserved_37_39        : 3;
        uint64_t drv_nctl              : 5;  /**< [ 36: 32](R/W) NCTL drive strength to use in bypass mode.
                                                                 Value of 14 is for 50 ohm termination. */
        uint64_t reserved_31           : 1;
        uint64_t pctl_lock             : 1;  /**< [ 30: 30](RO/H) PCTL lock. */
        uint64_t pctl_sat              : 1;  /**< [ 29: 29](RO/H) PCTL saturate. */
        uint64_t reserved_28           : 1;
        uint64_t nctl_lock             : 1;  /**< [ 27: 27](RO/H) NCTL lock. */
        uint64_t reserved_1_26         : 26;
        uint64_t nctl_sat              : 1;  /**< [  0:  0](RO/H) NCTL saturate. */
#else /* Word 0 - Little Endian */
        uint64_t nctl_sat              : 1;  /**< [  0:  0](RO/H) NCTL saturate. */
        uint64_t reserved_1_26         : 26;
        uint64_t nctl_lock             : 1;  /**< [ 27: 27](RO/H) NCTL lock. */
        uint64_t reserved_28           : 1;
        uint64_t pctl_sat              : 1;  /**< [ 29: 29](RO/H) PCTL saturate. */
        uint64_t pctl_lock             : 1;  /**< [ 30: 30](RO/H) PCTL lock. */
        uint64_t reserved_31           : 1;
        uint64_t drv_nctl              : 5;  /**< [ 36: 32](R/W) NCTL drive strength to use in bypass mode.
                                                                 Value of 14 is for 50 ohm termination. */
        uint64_t reserved_37_39        : 3;
        uint64_t drv_pctl              : 5;  /**< [ 44: 40](R/W) PCTL drive strength to use in bypass mode.
                                                                 Value of 11 is for 50 ohm termination. */
        uint64_t reserved_45_47        : 3;
        uint64_t cmp_nctl              : 5;  /**< [ 52: 48](RO/H) NCTL drive strength from the hardware compensation controller. */
        uint64_t reserved_53_55        : 3;
        uint64_t cmp_pctl              : 5;  /**< [ 60: 56](RO/H) PCTL drive strength from the hardware compensation controller. */
        uint64_t reserved_61_62        : 2;
        uint64_t drv_byp               : 1;  /**< [ 63: 63](R/W) When set, bypass the compensation controller and use
                                                                 [DRV_NCTL] and [DRV_PCTL]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_comp_ctl_s cn; */
};
typedef union bdk_xcvx_comp_ctl bdk_xcvx_comp_ctl_t;

static inline uint64_t BDK_XCVX_COMP_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_COMP_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000020ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_COMP_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_COMP_CTL(a) bdk_xcvx_comp_ctl_t
#define bustype_BDK_XCVX_COMP_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_COMP_CTL(a) "XCVX_COMP_CTL"
#define device_bar_BDK_XCVX_COMP_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_COMP_CTL(a) (a)
#define arguments_BDK_XCVX_COMP_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_ctl
 *
 * XCV Control Register
 * This register contains the status control bits.
 */
union bdk_xcvx_ctl
{
    uint64_t u;
    struct bdk_xcvx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t lpbk_ext              : 1;  /**< [  3:  3](R/W) Enable external loopback mode. External loopback loops the RX datapath to the TX
                                                                 datapath. For correct operation, the following CSRs must be configured:
                                                                 * XCV_CTL[SPEED]          = 0x2.
                                                                 * XCV_DLL_CTL[REFCLK_SEL] = 1.
                                                                 * XCV_RESET[CLKRST]       = 1. */
        uint64_t lpbk_int              : 1;  /**< [  2:  2](R/W) Enable internal loopback mode. Internal loopback loops the TX datapath to the RX
                                                                 datapath. For correct operation, the following CSRs must be configured:
                                                                 * XCV_CTL[SPEED]          = 0x2.
                                                                 * XCV_DLL_CTL[REFCLK_SEL] = 0.
                                                                 * XCV_RESET[CLKRST]       = 0. */
        uint64_t speed                 : 2;  /**< [  1:  0](R/W) XCV operational speed:
                                                                   0x0 = 10 Mbps.
                                                                   0x1 = 100 Mbps.
                                                                   0x2 = 1 Gbps.
                                                                   0x3 = Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t speed                 : 2;  /**< [  1:  0](R/W) XCV operational speed:
                                                                   0x0 = 10 Mbps.
                                                                   0x1 = 100 Mbps.
                                                                   0x2 = 1 Gbps.
                                                                   0x3 = Reserved. */
        uint64_t lpbk_int              : 1;  /**< [  2:  2](R/W) Enable internal loopback mode. Internal loopback loops the TX datapath to the RX
                                                                 datapath. For correct operation, the following CSRs must be configured:
                                                                 * XCV_CTL[SPEED]          = 0x2.
                                                                 * XCV_DLL_CTL[REFCLK_SEL] = 0.
                                                                 * XCV_RESET[CLKRST]       = 0. */
        uint64_t lpbk_ext              : 1;  /**< [  3:  3](R/W) Enable external loopback mode. External loopback loops the RX datapath to the TX
                                                                 datapath. For correct operation, the following CSRs must be configured:
                                                                 * XCV_CTL[SPEED]          = 0x2.
                                                                 * XCV_DLL_CTL[REFCLK_SEL] = 1.
                                                                 * XCV_RESET[CLKRST]       = 1. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_ctl_s cn; */
};
typedef union bdk_xcvx_ctl bdk_xcvx_ctl_t;

static inline uint64_t BDK_XCVX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000030ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_CTL(a) bdk_xcvx_ctl_t
#define bustype_BDK_XCVX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_CTL(a) "XCVX_CTL"
#define device_bar_BDK_XCVX_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_CTL(a) (a)
#define arguments_BDK_XCVX_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_dll_ctl
 *
 * XCV DLL Controller Register
 * The RGMII timing specification requires that devices transmit clock and
 * data synchronously. The specification requires external sources (namely
 * the PC board trace routes) to introduce the appropriate 1.5 to 2.0 ns of
 * delay.
 *
 * To eliminate the need for the PC board delays, the RGMII interface has optional
 * on-board DLLs for both transmit and receive. For correct operation, at most one
 * of the transmitter, board, or receiver involved in an RGMII link should
 * introduce delay. By default/reset, the RGMII receivers delay the received clock,
 * and the RGMII transmitters do not delay the transmitted clock. Whether this
 * default works as-is with a given link partner depends on the behavior of the
 * link partner and the PC board.
 *
 * These are the possible modes of RGMII receive operation:
 *
 * * XCV()_DLL_CTL[CLKRX_BYP] = 0 (reset value) - The RGMII
 * receive interface introduces clock delay using its internal DLL.
 * This mode is appropriate if neither the remote
 * transmitter nor the PC board delays the clock.
 *
 * * XCV()_DLL_CTL[CLKRX_BYP] = 1, [CLKRX_SET] = 0x0 - The
 * RGMII receive interface introduces no clock delay. This mode
 * is appropriate if either the remote transmitter or the PC board
 * delays the clock.
 *
 * These are the possible modes of RGMII transmit operation:
 *
 * * XCV()_DLL_CTL[CLKTX_BYP] = 1, [CLKTX_SET] = 0x0 (reset value) -
 * The RGMII transmit interface introduces no clock
 * delay. This mode is appropriate is either the remote receiver
 * or the PC board delays the clock.
 *
 * * XCV()_DLL_CTL[CLKTX_BYP] = 0 - The RGMII transmit
 * interface introduces clock delay using its internal DLL.
 * This mode is appropriate if neither the remote receiver
 * nor the PC board delays the clock.
 */
union bdk_xcvx_dll_ctl
{
    uint64_t u;
    struct bdk_xcvx_dll_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lock                  : 1;  /**< [ 31: 31](RO/H) DLL is locked. */
        uint64_t clk_set               : 7;  /**< [ 30: 24](RO/H) The clock delay as determined by the on-board hardware DLL. */
        uint64_t clkrx_byp             : 1;  /**< [ 23: 23](R/W) Bypass the RX clock delay setting.
                                                                 Skews RXC from RXD, RXCTL.
                                                                 By default, hardware internally shifts the RXC clock
                                                                 to sample RXD,RXCTL assuming clock and data and
                                                                 sourced synchronously from the link partner. */
        uint64_t clkrx_set             : 7;  /**< [ 22: 16](R/W) RX clock delay setting to use in bypass mode.
                                                                 Skews RXC from RXD. */
        uint64_t clktx_byp             : 1;  /**< [ 15: 15](R/W) Bypass the TX clock delay setting.
                                                                 Skews TXC from TXD, TXCTL.
                                                                 By default, clock and data and sourced
                                                                 synchronously. */
        uint64_t clktx_set             : 7;  /**< [ 14:  8](R/W) TX clock delay setting to use in bypass mode.
                                                                 Skews TXC from TXD. */
        uint64_t reserved_2_7          : 6;
        uint64_t refclk_sel            : 2;  /**< [  1:  0](R/W) Select the reference clock to use.  Normal RGMII specification requires a 125MHz
                                                                 oscillator.
                                                                 To reduce system cost, a 500MHz coprocessor clock can be divided down and remove the
                                                                 requirements for the external oscillator. Additionally, in some well defined systems, the
                                                                 link partner may be able to source the RXC. The RGMII would operate correctly in 1000Mbs
                                                                 mode only.
                                                                 0x0 = RGMII REFCLK.
                                                                 0x1 = RGMII RXC (1000Mbs only).
                                                                 0x2 = Divided coprocessor clock.
                                                                 0x3 = Reserved.

                                                                 Internal:
                                                                 Some programming magic could allow for 10/100 operation if
                                                                 critical, use encoding 0x1 but some programming restrictions would apply. */
#else /* Word 0 - Little Endian */
        uint64_t refclk_sel            : 2;  /**< [  1:  0](R/W) Select the reference clock to use.  Normal RGMII specification requires a 125MHz
                                                                 oscillator.
                                                                 To reduce system cost, a 500MHz coprocessor clock can be divided down and remove the
                                                                 requirements for the external oscillator. Additionally, in some well defined systems, the
                                                                 link partner may be able to source the RXC. The RGMII would operate correctly in 1000Mbs
                                                                 mode only.
                                                                 0x0 = RGMII REFCLK.
                                                                 0x1 = RGMII RXC (1000Mbs only).
                                                                 0x2 = Divided coprocessor clock.
                                                                 0x3 = Reserved.

                                                                 Internal:
                                                                 Some programming magic could allow for 10/100 operation if
                                                                 critical, use encoding 0x1 but some programming restrictions would apply. */
        uint64_t reserved_2_7          : 6;
        uint64_t clktx_set             : 7;  /**< [ 14:  8](R/W) TX clock delay setting to use in bypass mode.
                                                                 Skews TXC from TXD. */
        uint64_t clktx_byp             : 1;  /**< [ 15: 15](R/W) Bypass the TX clock delay setting.
                                                                 Skews TXC from TXD, TXCTL.
                                                                 By default, clock and data and sourced
                                                                 synchronously. */
        uint64_t clkrx_set             : 7;  /**< [ 22: 16](R/W) RX clock delay setting to use in bypass mode.
                                                                 Skews RXC from RXD. */
        uint64_t clkrx_byp             : 1;  /**< [ 23: 23](R/W) Bypass the RX clock delay setting.
                                                                 Skews RXC from RXD, RXCTL.
                                                                 By default, hardware internally shifts the RXC clock
                                                                 to sample RXD,RXCTL assuming clock and data and
                                                                 sourced synchronously from the link partner. */
        uint64_t clk_set               : 7;  /**< [ 30: 24](RO/H) The clock delay as determined by the on-board hardware DLL. */
        uint64_t lock                  : 1;  /**< [ 31: 31](RO/H) DLL is locked. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_dll_ctl_s cn; */
};
typedef union bdk_xcvx_dll_ctl bdk_xcvx_dll_ctl_t;

static inline uint64_t BDK_XCVX_DLL_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_DLL_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000010ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_DLL_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_DLL_CTL(a) bdk_xcvx_dll_ctl_t
#define bustype_BDK_XCVX_DLL_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_DLL_CTL(a) "XCVX_DLL_CTL"
#define device_bar_BDK_XCVX_DLL_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_DLL_CTL(a) (a)
#define arguments_BDK_XCVX_DLL_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_eco
 *
 * INTERNAL: XCV ECO Register
 */
union bdk_xcvx_eco
{
    uint64_t u;
    struct bdk_xcvx_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t eco_rw                : 16; /**< [ 15:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 16; /**< [ 15:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_eco_s cn; */
};
typedef union bdk_xcvx_eco bdk_xcvx_eco_t;

static inline uint64_t BDK_XCVX_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000200ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_ECO(a) bdk_xcvx_eco_t
#define bustype_BDK_XCVX_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_ECO(a) "XCVX_ECO"
#define device_bar_BDK_XCVX_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_ECO(a) (a)
#define arguments_BDK_XCVX_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_inbnd_status
 *
 * XCV Inband Status Register
 * This register contains RGMII inband status.
 */
union bdk_xcvx_inbnd_status
{
    uint64_t u;
    struct bdk_xcvx_inbnd_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t duplex                : 1;  /**< [  3:  3](RO/H) RGMII in-band status - link duplex:
                                                                 0 = Half-duplex.
                                                                 1 = Full-duplex. */
        uint64_t speed                 : 2;  /**< [  2:  1](RO/H) RGMII in-band status - link speed:
                                                                 0x0 = 10 Mbps.
                                                                 0x1 = 100 Mbps.
                                                                 0x2 = 1000 Mbps.
                                                                 0x3 = Reserved. */
        uint64_t link                  : 1;  /**< [  0:  0](RO/H) RGMII in-band status - link enable/up:
                                                                 0 = Link down.
                                                                 1 = Link up. */
#else /* Word 0 - Little Endian */
        uint64_t link                  : 1;  /**< [  0:  0](RO/H) RGMII in-band status - link enable/up:
                                                                 0 = Link down.
                                                                 1 = Link up. */
        uint64_t speed                 : 2;  /**< [  2:  1](RO/H) RGMII in-band status - link speed:
                                                                 0x0 = 10 Mbps.
                                                                 0x1 = 100 Mbps.
                                                                 0x2 = 1000 Mbps.
                                                                 0x3 = Reserved. */
        uint64_t duplex                : 1;  /**< [  3:  3](RO/H) RGMII in-band status - link duplex:
                                                                 0 = Half-duplex.
                                                                 1 = Full-duplex. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_inbnd_status_s cn; */
};
typedef union bdk_xcvx_inbnd_status bdk_xcvx_inbnd_status_t;

static inline uint64_t BDK_XCVX_INBND_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_INBND_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000080ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_INBND_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_INBND_STATUS(a) bdk_xcvx_inbnd_status_t
#define bustype_BDK_XCVX_INBND_STATUS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_INBND_STATUS(a) "XCVX_INBND_STATUS"
#define device_bar_BDK_XCVX_INBND_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_INBND_STATUS(a) (a)
#define arguments_BDK_XCVX_INBND_STATUS(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_int
 *
 * XCV Interupt Register
 * This register flags error for TX FIFO overflow, TX FIFO underflow and incomplete byte for
 * 10/100 Mode.
 * It also flags status change for link duplex, link speed and link up/down.
 */
union bdk_xcvx_int
{
    uint64_t u;
    struct bdk_xcvx_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t tx_ovrflw             : 1;  /**< [  6:  6](R/W1C/H) Flags the TX FIFO overflow error case. */
        uint64_t tx_undflw             : 1;  /**< [  5:  5](R/W1C/H) Flags the TX FIFO underflow error case. */
        uint64_t incomp_byte           : 1;  /**< [  4:  4](R/W1C/H) Flags the incomplete byte error cases for 10/100 mode. */
        uint64_t duplex                : 1;  /**< [  3:  3](R/W1C/H) Status change for link duplex. */
        uint64_t reserved_2            : 1;
        uint64_t speed                 : 1;  /**< [  1:  1](R/W1C/H) Status change for link speed. */
        uint64_t link                  : 1;  /**< [  0:  0](R/W1C/H) Status change for link up/down status. */
#else /* Word 0 - Little Endian */
        uint64_t link                  : 1;  /**< [  0:  0](R/W1C/H) Status change for link up/down status. */
        uint64_t speed                 : 1;  /**< [  1:  1](R/W1C/H) Status change for link speed. */
        uint64_t reserved_2            : 1;
        uint64_t duplex                : 1;  /**< [  3:  3](R/W1C/H) Status change for link duplex. */
        uint64_t incomp_byte           : 1;  /**< [  4:  4](R/W1C/H) Flags the incomplete byte error cases for 10/100 mode. */
        uint64_t tx_undflw             : 1;  /**< [  5:  5](R/W1C/H) Flags the TX FIFO underflow error case. */
        uint64_t tx_ovrflw             : 1;  /**< [  6:  6](R/W1C/H) Flags the TX FIFO overflow error case. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_int_s cn; */
};
typedef union bdk_xcvx_int bdk_xcvx_int_t;

static inline uint64_t BDK_XCVX_INT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_INT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000040ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_INT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_INT(a) bdk_xcvx_int_t
#define bustype_BDK_XCVX_INT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_INT(a) "XCVX_INT"
#define device_bar_BDK_XCVX_INT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_INT(a) (a)
#define arguments_BDK_XCVX_INT(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_int_ena_w1c
 *
 * Loopback Error Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_xcvx_int_ena_w1c
{
    uint64_t u;
    struct bdk_xcvx_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t tx_ovrflw             : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for XCV(0)_INT[TX_OVRFLW]. */
        uint64_t tx_undflw             : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for XCV(0)_INT[TX_UNDFLW]. */
        uint64_t incomp_byte           : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for XCV(0)_INT[INCOMP_BYTE]. */
        uint64_t duplex                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for XCV(0)_INT[DUPLEX]. */
        uint64_t reserved_2            : 1;
        uint64_t speed                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for XCV(0)_INT[SPEED]. */
        uint64_t link                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCV(0)_INT[LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t link                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCV(0)_INT[LINK]. */
        uint64_t speed                 : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for XCV(0)_INT[SPEED]. */
        uint64_t reserved_2            : 1;
        uint64_t duplex                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for XCV(0)_INT[DUPLEX]. */
        uint64_t incomp_byte           : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for XCV(0)_INT[INCOMP_BYTE]. */
        uint64_t tx_undflw             : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for XCV(0)_INT[TX_UNDFLW]. */
        uint64_t tx_ovrflw             : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for XCV(0)_INT[TX_OVRFLW]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_int_ena_w1c_s cn; */
};
typedef union bdk_xcvx_int_ena_w1c bdk_xcvx_int_ena_w1c_t;

static inline uint64_t BDK_XCVX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000050ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_INT_ENA_W1C(a) bdk_xcvx_int_ena_w1c_t
#define bustype_BDK_XCVX_INT_ENA_W1C(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_INT_ENA_W1C(a) "XCVX_INT_ENA_W1C"
#define device_bar_BDK_XCVX_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_INT_ENA_W1C(a) (a)
#define arguments_BDK_XCVX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_int_ena_w1s
 *
 * Loopback Error Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_xcvx_int_ena_w1s
{
    uint64_t u;
    struct bdk_xcvx_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t tx_ovrflw             : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for XCV(0)_INT[TX_OVRFLW]. */
        uint64_t tx_undflw             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for XCV(0)_INT[TX_UNDFLW]. */
        uint64_t incomp_byte           : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for XCV(0)_INT[INCOMP_BYTE]. */
        uint64_t duplex                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for XCV(0)_INT[DUPLEX]. */
        uint64_t reserved_2            : 1;
        uint64_t speed                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for XCV(0)_INT[SPEED]. */
        uint64_t link                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCV(0)_INT[LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t link                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCV(0)_INT[LINK]. */
        uint64_t speed                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for XCV(0)_INT[SPEED]. */
        uint64_t reserved_2            : 1;
        uint64_t duplex                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for XCV(0)_INT[DUPLEX]. */
        uint64_t incomp_byte           : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for XCV(0)_INT[INCOMP_BYTE]. */
        uint64_t tx_undflw             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for XCV(0)_INT[TX_UNDFLW]. */
        uint64_t tx_ovrflw             : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for XCV(0)_INT[TX_OVRFLW]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_int_ena_w1s_s cn; */
};
typedef union bdk_xcvx_int_ena_w1s bdk_xcvx_int_ena_w1s_t;

static inline uint64_t BDK_XCVX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000058ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_INT_ENA_W1S(a) bdk_xcvx_int_ena_w1s_t
#define bustype_BDK_XCVX_INT_ENA_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_INT_ENA_W1S(a) "XCVX_INT_ENA_W1S"
#define device_bar_BDK_XCVX_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_INT_ENA_W1S(a) (a)
#define arguments_BDK_XCVX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_int_w1s
 *
 * Loopback Error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_xcvx_int_w1s
{
    uint64_t u;
    struct bdk_xcvx_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t tx_ovrflw             : 1;  /**< [  6:  6](R/W1S/H) Reads or sets XCV(0)_INT[TX_OVRFLW]. */
        uint64_t tx_undflw             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets XCV(0)_INT[TX_UNDFLW]. */
        uint64_t incomp_byte           : 1;  /**< [  4:  4](R/W1S/H) Reads or sets XCV(0)_INT[INCOMP_BYTE]. */
        uint64_t duplex                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets XCV(0)_INT[DUPLEX]. */
        uint64_t reserved_2            : 1;
        uint64_t speed                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets XCV(0)_INT[SPEED]. */
        uint64_t link                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCV(0)_INT[LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t link                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCV(0)_INT[LINK]. */
        uint64_t speed                 : 1;  /**< [  1:  1](R/W1S/H) Reads or sets XCV(0)_INT[SPEED]. */
        uint64_t reserved_2            : 1;
        uint64_t duplex                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets XCV(0)_INT[DUPLEX]. */
        uint64_t incomp_byte           : 1;  /**< [  4:  4](R/W1S/H) Reads or sets XCV(0)_INT[INCOMP_BYTE]. */
        uint64_t tx_undflw             : 1;  /**< [  5:  5](R/W1S/H) Reads or sets XCV(0)_INT[TX_UNDFLW]. */
        uint64_t tx_ovrflw             : 1;  /**< [  6:  6](R/W1S/H) Reads or sets XCV(0)_INT[TX_OVRFLW]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_int_w1s_s cn; */
};
typedef union bdk_xcvx_int_w1s bdk_xcvx_int_w1s_t;

static inline uint64_t BDK_XCVX_INT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_INT_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000048ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_INT_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_INT_W1S(a) bdk_xcvx_int_w1s_t
#define bustype_BDK_XCVX_INT_W1S(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_INT_W1S(a) "XCVX_INT_W1S"
#define device_bar_BDK_XCVX_INT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_INT_W1S(a) (a)
#define arguments_BDK_XCVX_INT_W1S(a) (a),-1,-1,-1

/**
 * Register (RSL) xcv#_msix_pba#
 *
 * XCV MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the XCV_INT_VEC_E enumeration.
 */
union bdk_xcvx_msix_pbax
{
    uint64_t u;
    struct bdk_xcvx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated XCV_MSIX_VEC()_CTL, enumerated by
                                                                 XCV_INT_VEC_E. Bits that have no associated XCV_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated XCV_MSIX_VEC()_CTL, enumerated by
                                                                 XCV_INT_VEC_E. Bits that have no associated XCV_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_msix_pbax_s cn; */
};
typedef union bdk_xcvx_msix_pbax bdk_xcvx_msix_pbax_t;

static inline uint64_t BDK_XCVX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0dbff0000ll + 0ll * ((a) & 0x0) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("XCVX_MSIX_PBAX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_MSIX_PBAX(a,b) bdk_xcvx_msix_pbax_t
#define bustype_BDK_XCVX_MSIX_PBAX(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_MSIX_PBAX(a,b) "XCVX_MSIX_PBAX"
#define device_bar_BDK_XCVX_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_XCVX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_XCVX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (RSL) xcv#_msix_vec#_addr
 *
 * XCV MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the XCV_INT_VEC_E enumeration.
 */
union bdk_xcvx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_xcvx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's XCV_MSIX_VEC()_ADDR, XCV_MSIX_VEC()_CTL, and corresponding
                                                                 bit of XCV_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_XCV_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's XCV_MSIX_VEC()_ADDR, XCV_MSIX_VEC()_CTL, and corresponding
                                                                 bit of XCV_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_XCV_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_msix_vecx_addr_s cn; */
};
typedef union bdk_xcvx_msix_vecx_addr bdk_xcvx_msix_vecx_addr_t;

static inline uint64_t BDK_XCVX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0dbf00000ll + 0ll * ((a) & 0x0) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("XCVX_MSIX_VECX_ADDR", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_MSIX_VECX_ADDR(a,b) bdk_xcvx_msix_vecx_addr_t
#define bustype_BDK_XCVX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_MSIX_VECX_ADDR(a,b) "XCVX_MSIX_VECX_ADDR"
#define device_bar_BDK_XCVX_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_XCVX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_XCVX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (RSL) xcv#_msix_vec#_ctl
 *
 * XCV MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the XCV_INT_VEC_E enumeration.
 */
union bdk_xcvx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_xcvx_msix_vecx_ctl_s
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
    /* struct bdk_xcvx_msix_vecx_ctl_s cn; */
};
typedef union bdk_xcvx_msix_vecx_ctl bdk_xcvx_msix_vecx_ctl_t;

static inline uint64_t BDK_XCVX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a==0) && (b==0)))
        return 0x87e0dbf00008ll + 0ll * ((a) & 0x0) + 0x10ll * ((b) & 0x0);
    __bdk_csr_fatal("XCVX_MSIX_VECX_CTL", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_MSIX_VECX_CTL(a,b) bdk_xcvx_msix_vecx_ctl_t
#define bustype_BDK_XCVX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_MSIX_VECX_CTL(a,b) "XCVX_MSIX_VECX_CTL"
#define device_bar_BDK_XCVX_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_XCVX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_XCVX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (RSL) xcv#_reset
 *
 * XCV Reset Registers
 * This register controls reset.
 */
union bdk_xcvx_reset
{
    uint64_t u;
    struct bdk_xcvx_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Port enable. */
        uint64_t reserved_16_62        : 47;
        uint64_t clkrst                : 1;  /**< [ 15: 15](R/W) DLL CLK reset. [CLKRST] must be set if DLL bypass mode
                                                                 XCV_DLL_CTL[CLKRX_BYP,CLKTX_BYP] is used. */
        uint64_t reserved_12_14        : 3;
        uint64_t dllrst                : 1;  /**< [ 11: 11](R/W) DLL reset. */
        uint64_t reserved_8_10         : 3;
        uint64_t comp                  : 1;  /**< [  7:  7](R/W) Compensation enable. */
        uint64_t reserved_4_6          : 3;
        uint64_t tx_pkt_rst_n          : 1;  /**< [  3:  3](R/W) Packet reset for TX. */
        uint64_t tx_dat_rst_n          : 1;  /**< [  2:  2](R/W) Datapath reset for TX. */
        uint64_t rx_pkt_rst_n          : 1;  /**< [  1:  1](R/W) Packet reset for RX. */
        uint64_t rx_dat_rst_n          : 1;  /**< [  0:  0](R/W) Datapath reset for RX. */
#else /* Word 0 - Little Endian */
        uint64_t rx_dat_rst_n          : 1;  /**< [  0:  0](R/W) Datapath reset for RX. */
        uint64_t rx_pkt_rst_n          : 1;  /**< [  1:  1](R/W) Packet reset for RX. */
        uint64_t tx_dat_rst_n          : 1;  /**< [  2:  2](R/W) Datapath reset for TX. */
        uint64_t tx_pkt_rst_n          : 1;  /**< [  3:  3](R/W) Packet reset for TX. */
        uint64_t reserved_4_6          : 3;
        uint64_t comp                  : 1;  /**< [  7:  7](R/W) Compensation enable. */
        uint64_t reserved_8_10         : 3;
        uint64_t dllrst                : 1;  /**< [ 11: 11](R/W) DLL reset. */
        uint64_t reserved_12_14        : 3;
        uint64_t clkrst                : 1;  /**< [ 15: 15](R/W) DLL CLK reset. [CLKRST] must be set if DLL bypass mode
                                                                 XCV_DLL_CTL[CLKRX_BYP,CLKTX_BYP] is used. */
        uint64_t reserved_16_62        : 47;
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Port enable. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcvx_reset_s cn; */
};
typedef union bdk_xcvx_reset bdk_xcvx_reset_t;

static inline uint64_t BDK_XCVX_RESET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCVX_RESET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x87e0db000000ll + 0ll * ((a) & 0x0);
    __bdk_csr_fatal("XCVX_RESET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_XCVX_RESET(a) bdk_xcvx_reset_t
#define bustype_BDK_XCVX_RESET(a) BDK_CSR_TYPE_RSL
#define basename_BDK_XCVX_RESET(a) "XCVX_RESET"
#define device_bar_BDK_XCVX_RESET(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCVX_RESET(a) (a)
#define arguments_BDK_XCVX_RESET(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_XCV_H__ */
