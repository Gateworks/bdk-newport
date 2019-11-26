#ifndef __BDK_CSRS_RST_H__
#define __BDK_CSRS_RST_H__
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
 * OcteonTX RST.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration rst_bar_e
 *
 * RST Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_RST_BAR_E_RST_PF_BAR0_CN8 (0x87e006000000ll)
#define BDK_RST_BAR_E_RST_PF_BAR0_CN8_SIZE 0x800000ull
#define BDK_RST_BAR_E_RST_PF_BAR0_CN9 (0x87e006000000ll)
#define BDK_RST_BAR_E_RST_PF_BAR0_CN9_SIZE 0x10000ull
#define BDK_RST_BAR_E_RST_PF_BAR2 (0x87e00a000000ll)
#define BDK_RST_BAR_E_RST_PF_BAR2_SIZE 0x10000ull
#define BDK_RST_BAR_E_RST_PF_BAR4 (0x87e006f00000ll)
#define BDK_RST_BAR_E_RST_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration rst_boot_fail_e
 *
 * RST Boot Failure Code Enumeration
 * Enumerates the reasons for boot failure, returned to post-boot code
 * in argument register 0 and blinked on GPIO\<11\>.
 */
#define BDK_RST_BOOT_FAIL_E_AUTH (6)
#define BDK_RST_BOOT_FAIL_E_BUS_ERROR (0xb)
#define BDK_RST_BOOT_FAIL_E_DEVICE (3)
#define BDK_RST_BOOT_FAIL_E_GOOD_CN8 (0)
#define BDK_RST_BOOT_FAIL_E_GOOD_CN9 (1)
#define BDK_RST_BOOT_FAIL_E_HASH (8)
#define BDK_RST_BOOT_FAIL_E_KEY (7)
#define BDK_RST_BOOT_FAIL_E_MAGIC (4)
#define BDK_RST_BOOT_FAIL_E_MCORE (5)
#define BDK_RST_BOOT_FAIL_E_METH (2)
#define BDK_RST_BOOT_FAIL_E_SCRIPT_ACC_ERROR (0xa)
#define BDK_RST_BOOT_FAIL_E_SCRIPT_INVALID (9)
#define BDK_RST_BOOT_FAIL_E_UNINIT (0)

/**
 * Enumeration rst_boot_method_e
 *
 * RST Primary Boot-strap Method Enumeration
 * Enumerates the primary (first choice) and secondary (second choice) boot
 * device. Primary boot method is selected with the straps
 * GPIO_STRAP_PIN_E::BOOT_METHOD2..0, and secondary is selected with the straps
 * GPIO_STRAP_PIN_E::BOOT_METHOD5..3.
 *
 * To disable the secondary method, use ::REMOTE.
 */
#define BDK_RST_BOOT_METHOD_E_CCPI0 (9)
#define BDK_RST_BOOT_METHOD_E_CCPI1 (0xa)
#define BDK_RST_BOOT_METHOD_E_CCPI2 (0xb)
#define BDK_RST_BOOT_METHOD_E_EMMC_CS0 (0)
#define BDK_RST_BOOT_METHOD_E_EMMC_CS1 (1)
#define BDK_RST_BOOT_METHOD_E_EMMC_LS (3)
#define BDK_RST_BOOT_METHOD_E_EMMC_SS (2)
#define BDK_RST_BOOT_METHOD_E_PCIE0 (0xc)
#define BDK_RST_BOOT_METHOD_E_PCIE2 (0xd)
#define BDK_RST_BOOT_METHOD_E_REMOTE_CN8 (8)
#define BDK_RST_BOOT_METHOD_E_REMOTE_CN9 (7)
#define BDK_RST_BOOT_METHOD_E_SPI0_CS0 (2)
#define BDK_RST_BOOT_METHOD_E_SPI0_CS1 (3)
#define BDK_RST_BOOT_METHOD_E_SPI1_CS0 (4)
#define BDK_RST_BOOT_METHOD_E_SPI1_CS1 (5)
#define BDK_RST_BOOT_METHOD_E_SPI24 (5)
#define BDK_RST_BOOT_METHOD_E_SPI32 (6)

/**
 * Enumeration rst_dev_e
 *
 * Programmable Reset Device Enumeration
 * Enumerates devices that have programmable reset domains, and index {a} of RST_DEV_MAP().
 */
#define BDK_RST_DEV_E_AVS (1)
#define BDK_RST_DEV_E_CGXX(a) (0x12 + (a))
#define BDK_RST_DEV_E_EMMC (0x19)
#define BDK_RST_DEV_E_GSERX(a) (0x1a + (a))
#define BDK_RST_DEV_E_GSERRX(a) (0x20 + (a))
#define BDK_RST_DEV_E_MPIX(a) (2 + (a))
#define BDK_RST_DEV_E_NCSI (0)
#define BDK_RST_DEV_E_PEMX(a) (0x28 + (a))
#define BDK_RST_DEV_E_RFIFX_CNF95XX(a) (0x26 + (a))
#define BDK_RST_DEV_E_RFIFX_LOKI(a) (0x21 + (a))
#define BDK_RST_DEV_E_ROC_OCLA (0x18)
#define BDK_RST_DEV_E_SGPIO (0x17)
#define BDK_RST_DEV_E_SMI_CN96XX (0x16)
#define BDK_RST_DEV_E_SMI_CN98XX (0x1a)
#define BDK_RST_DEV_E_SMI_CNF95XX (0x16)
#define BDK_RST_DEV_E_SMI_LOKI (0x16)
#define BDK_RST_DEV_E_TWSX(a) (4 + (a))
#define BDK_RST_DEV_E_UAAX(a) (0xa + (a))

/**
 * Enumeration rst_domain_e
 *
 * RST Domain Enumeration
 * This enumerates the values of RST_DEV_MAP()[DMN].
 */
#define BDK_RST_DOMAIN_E_BPHY (5)
#define BDK_RST_DOMAIN_E_CHIP (0)
#define BDK_RST_DOMAIN_E_CORE (1)
#define BDK_RST_DOMAIN_E_MCP (2)
#define BDK_RST_DOMAIN_E_OFF (4)
#define BDK_RST_DOMAIN_E_SCP (3)

/**
 * Enumeration rst_int_vec_e
 *
 * RST MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_RST_INT_VEC_E_INTS (0)

/**
 * Enumeration rst_source_e
 *
 * RST Cause Enumeration
 * Enumerates the reset sources for both reset domain mapping and cause of last reset,
 * corresponding to the bit numbers of RST_LBOOT.
 */
#define BDK_RST_SOURCE_E_BPHY_RESET_PIN (0x30)
#define BDK_RST_SOURCE_E_BPHY_SOFT (0x31)
#define BDK_RST_SOURCE_E_CHIPKILL (4)
#define BDK_RST_SOURCE_E_CHIP_RESET_PIN (2)
#define BDK_RST_SOURCE_E_CHIP_SOFT (3)
#define BDK_RST_SOURCE_E_COLD_SOFT (1)
#define BDK_RST_SOURCE_E_CORE_RESET_PIN (0xb)
#define BDK_RST_SOURCE_E_CORE_SOFT (0xc)
#define BDK_RST_SOURCE_E_CORE_WDOG (0xd)
#define BDK_RST_SOURCE_E_DCOK_PIN (0)
#define BDK_RST_SOURCE_E_MCP_RESET_PIN (8)
#define BDK_RST_SOURCE_E_MCP_SOFT (9)
#define BDK_RST_SOURCE_E_MCP_WDOG (0xa)
#define BDK_RST_SOURCE_E_OCX (0xe)
#define BDK_RST_SOURCE_E_PEM_CHIPX(a) (0x11 + 2 * (a))
#define BDK_RST_SOURCE_E_PEM_COREX(a) (0x10 + 2 * (a))
#define BDK_RST_SOURCE_E_PEM_LINKDOWNX(a) (0x11 + 4 * (a))
#define BDK_RST_SOURCE_E_PEM_PFFLRX(a) (0x13 + 4 * (a))
#define BDK_RST_SOURCE_E_PEM_PWRDOWNX(a) (0x12 + 4 * (a))
#define BDK_RST_SOURCE_E_PERST_PINX(a) (0x10 + 4 * (a))
#define BDK_RST_SOURCE_E_RSVD_F (0xf)
#define BDK_RST_SOURCE_E_SCP_RESET_PIN (5)
#define BDK_RST_SOURCE_E_SCP_SOFT (6)
#define BDK_RST_SOURCE_E_SCP_WDOG (7)

/**
 * Structure rst_boot_stat_s
 *
 * BOOT_STATUS field Structure
 * The ROM boot code stores this data in the RST_BOOT_STATUS register, once per each boot attempt.
 */
union bdk_rst_boot_stat_s
{
    uint32_t u;
    struct bdk_rst_boot_stat_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t trusted               : 1;  /**< [ 15: 15] This was a trusted-mode boot. */
        uint32_t primary               : 1;  /**< [ 14: 14] This was a boot from the primary device. */
        uint32_t scr_done              : 1;  /**< [ 13: 13] The ROM script ran to completion on this boot. */
        uint32_t reserved_7_12         : 6;
        uint32_t boot_method           : 3;  /**< [  6:  4] The boot method for this boot attempt RST_BOOT_METHOD_E. */
        uint32_t fail                  : 4;  /**< [  3:  0] The failure code for this boot attempt RST_BOOT_FAIL_E. */
#else /* Word 0 - Little Endian */
        uint32_t fail                  : 4;  /**< [  3:  0] The failure code for this boot attempt RST_BOOT_FAIL_E. */
        uint32_t boot_method           : 3;  /**< [  6:  4] The boot method for this boot attempt RST_BOOT_METHOD_E. */
        uint32_t reserved_7_12         : 6;
        uint32_t scr_done              : 1;  /**< [ 13: 13] The ROM script ran to completion on this boot. */
        uint32_t primary               : 1;  /**< [ 14: 14] This was a boot from the primary device. */
        uint32_t trusted               : 1;  /**< [ 15: 15] This was a trusted-mode boot. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_boot_stat_s_s cn; */
};

/**
 * Structure rst_pp_pwr_s
 *
 * INTERNAL: Core Reset Power Delivery Structure
 *
 * This structure specifies the layout of RTL reset and power delivery. It is not visible to software.
 */
union bdk_rst_pp_pwr_s
{
    uint32_t u;
    struct bdk_rst_pp_pwr_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t valid                 : 1;  /**< [  9:  9] Data transmitted on interface is valid.. */
        uint32_t ppvid                 : 6;  /**< [  8:  3] Virtual core number. */
        uint32_t dbg_rst               : 1;  /**< [  2:  2] Reset control for the core specified by PPVID. */
        uint32_t pwrdwn                : 1;  /**< [  1:  1] Core does not require power. */
        uint32_t rst                   : 1;  /**< [  0:  0] Reset control for the core specified by PPVID. */
#else /* Word 0 - Little Endian */
        uint32_t rst                   : 1;  /**< [  0:  0] Reset control for the core specified by PPVID. */
        uint32_t pwrdwn                : 1;  /**< [  1:  1] Core does not require power. */
        uint32_t dbg_rst               : 1;  /**< [  2:  2] Reset control for the core specified by PPVID. */
        uint32_t ppvid                 : 6;  /**< [  8:  3] Virtual core number. */
        uint32_t valid                 : 1;  /**< [  9:  9] Data transmitted on interface is valid.. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_pp_pwr_s_s cn8; */
    struct bdk_rst_pp_pwr_s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t valid                 : 1;  /**< [  9:  9] Data transmitted on interface is valid. */
        uint32_t ppvid                 : 6;  /**< [  8:  3] Virtual core number. */
        uint32_t dbg_rst               : 1;  /**< [  2:  2] Reset control for the core specified by PPVID. */
        uint32_t pwrdwn                : 1;  /**< [  1:  1] Core does not require power. */
        uint32_t rst                   : 1;  /**< [  0:  0] Reset control for the core specified by PPVID. */
#else /* Word 0 - Little Endian */
        uint32_t rst                   : 1;  /**< [  0:  0] Reset control for the core specified by PPVID. */
        uint32_t pwrdwn                : 1;  /**< [  1:  1] Core does not require power. */
        uint32_t dbg_rst               : 1;  /**< [  2:  2] Reset control for the core specified by PPVID. */
        uint32_t ppvid                 : 6;  /**< [  8:  3] Virtual core number. */
        uint32_t valid                 : 1;  /**< [  9:  9] Data transmitted on interface is valid. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } cn9;
};

/**
 * Register (RSL) rst_ap#_affinity_const
 *
 * RST Virtual AP Affinity Map Register
 * This register indicates the processor affinity identification and logical core
 * number mapping to physical core numbers. This is indexed by logical core number.
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_apx_affinity_const
{
    uint64_t u;
    struct bdk_rst_apx_affinity_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_56_63        : 8;
        uint64_t core                  : 8;  /**< [ 55: 48](RO) Physical core number. */
        uint64_t reserved_44_47        : 4;
        uint64_t phy_clu               : 4;  /**< [ 43: 40](RO) Physical cluster number. */
        uint64_t reserved_36_39        : 4;
        uint64_t phy_core              : 4;  /**< [ 35: 32](RO) Physical core-within-cluster number. */
        uint64_t fov                   : 1;  /**< [ 31: 31](RO) Set to indicate if the fields are valid. */
        uint64_t u                     : 1;  /**< [ 30: 30](RO) Set to indicate processors are part of a multprocessor system. */
        uint64_t reserved_25_29        : 5;
        uint64_t mt                    : 1;  /**< [ 24: 24](RO) Set to indicate multithreaded and [AFF0] is thread number in core. */
        uint64_t aff2                  : 8;  /**< [ 23: 16](RO/H) Affinity 2 for this logical core number.  In CNXXXX, the node id. */
        uint64_t aff1                  : 8;  /**< [ 15:  8](RO/H) Affinity 1 for this logical core number.  In CNXXXX, the logical cluster id. */
        uint64_t aff0                  : 8;  /**< [  7:  0](RO/H) Affinity 0 for this logical core number.  In CNXXXX, the logical core number within a cluster. */
#else /* Word 0 - Little Endian */
        uint64_t aff0                  : 8;  /**< [  7:  0](RO/H) Affinity 0 for this logical core number.  In CNXXXX, the logical core number within a cluster. */
        uint64_t aff1                  : 8;  /**< [ 15:  8](RO/H) Affinity 1 for this logical core number.  In CNXXXX, the logical cluster id. */
        uint64_t aff2                  : 8;  /**< [ 23: 16](RO/H) Affinity 2 for this logical core number.  In CNXXXX, the node id. */
        uint64_t mt                    : 1;  /**< [ 24: 24](RO) Set to indicate multithreaded and [AFF0] is thread number in core. */
        uint64_t reserved_25_29        : 5;
        uint64_t u                     : 1;  /**< [ 30: 30](RO) Set to indicate processors are part of a multprocessor system. */
        uint64_t fov                   : 1;  /**< [ 31: 31](RO) Set to indicate if the fields are valid. */
        uint64_t phy_core              : 4;  /**< [ 35: 32](RO) Physical core-within-cluster number. */
        uint64_t reserved_36_39        : 4;
        uint64_t phy_clu               : 4;  /**< [ 43: 40](RO) Physical cluster number. */
        uint64_t reserved_44_47        : 4;
        uint64_t core                  : 8;  /**< [ 55: 48](RO) Physical core number. */
        uint64_t reserved_56_63        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_apx_affinity_const_s cn; */
};
typedef union bdk_rst_apx_affinity_const bdk_rst_apx_affinity_const_t;

static inline uint64_t BDK_RST_APX_AFFINITY_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_APX_AFFINITY_CONST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87e006001000ll + 8ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87e006001000ll + 8ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87e006001000ll + 8ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87e006001000ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("RST_APX_AFFINITY_CONST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_APX_AFFINITY_CONST(a) bdk_rst_apx_affinity_const_t
#define bustype_BDK_RST_APX_AFFINITY_CONST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RST_APX_AFFINITY_CONST(a) "RST_APX_AFFINITY_CONST"
#define device_bar_BDK_RST_APX_AFFINITY_CONST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_APX_AFFINITY_CONST(a) (a)
#define arguments_BDK_RST_APX_AFFINITY_CONST(a) (a),-1,-1,-1

/**
 * Register (RSL) rst_bcn_pll
 *
 * RST GSERR Clock PLL Control Register
 * This register should only be programmed while all RFIF logic is in reset.
 * It is accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_bcn_pll
{
    uint64_t u;
    struct bdk_rst_bcn_pll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Programs the active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when PLL has been updated.  Software should wait at least 20uS
                                                                 for clock frequency to be reached before releasing GSERRs from reset.
                                                                 This field is always reinitialized on a chip domain reset.

                                                                 Changing BCN Clock frequency is for diagnostic use only; changes can only be made
                                                                 while all RFIF logic is in reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) BCN PLL frequency to be program in 61.44 MHz increments.  The
                                                                 actual value must be in the range between 295 MHz and 1228.8 MHz.
                                                                 Value will be 307.2 MHz immediately after a cold domain reset. */
        uint64_t reserved_7            : 1;
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) BCN clock frequency.  Actual frequency is [CUR_MUL] * 61.44 MHz.
                                                                 Value will reflect [NXT_MUL] after [NXT_PGM] has been set or 307.2 MHz
                                                                 immediately after a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) BCN clock frequency.  Actual frequency is [CUR_MUL] * 61.44 MHz.
                                                                 Value will reflect [NXT_MUL] after [NXT_PGM] has been set or 307.2 MHz
                                                                 immediately after a cold domain reset. */
        uint64_t reserved_7            : 1;
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) BCN PLL frequency to be program in 61.44 MHz increments.  The
                                                                 actual value must be in the range between 295 MHz and 1228.8 MHz.
                                                                 Value will be 307.2 MHz immediately after a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Programs the active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when PLL has been updated.  Software should wait at least 20uS
                                                                 for clock frequency to be reached before releasing GSERRs from reset.
                                                                 This field is always reinitialized on a chip domain reset.

                                                                 Changing BCN Clock frequency is for diagnostic use only; changes can only be made
                                                                 while all RFIF logic is in reset. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_bcn_pll_s cn; */
};
typedef union bdk_rst_bcn_pll bdk_rst_bcn_pll_t;

#define BDK_RST_BCN_PLL BDK_RST_BCN_PLL_FUNC()
static inline uint64_t BDK_RST_BCN_PLL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_BCN_PLL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e00a001800ll;
    __bdk_csr_fatal("RST_BCN_PLL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_BCN_PLL bdk_rst_bcn_pll_t
#define bustype_BDK_RST_BCN_PLL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_BCN_PLL "RST_BCN_PLL"
#define device_bar_BDK_RST_BCN_PLL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_BCN_PLL 0
#define arguments_BDK_RST_BCN_PLL -1,-1,-1,-1

/**
 * Register (RSL) rst_bist_active
 *
 * RST BIST Active Status Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_bist_active
{
    uint64_t u;
    struct bdk_rst_bist_active_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t bphy                  : 1;  /**< [  6:  6](RO/H) BPHY domain BIST in progress.  When set, memories accociated with
                                                                 the BPHY domain are being tested. */
        uint64_t ap                    : 1;  /**< [  5:  5](RO/H) BIST in progress due to AP cores being put into reset.  When set, memories
                                                                 associated with this group are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t csr                   : 1;  /**< [  4:  4](RO/H) BIST in progress due to access to RST_DEV_MAP().  When set, memories
                                                                 associated with this access are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain BIST in progress.  When set, memories associated with
                                                                 the SCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain BIST in progress.  When set, memories associated with
                                                                 the MCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain BIST in progress.  When set, memories associated with
                                                                 the core domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t chip                  : 1;  /**< [  0:  0](RO/H) Chip BIST in progress.  Always reads 0. */
#else /* Word 0 - Little Endian */
        uint64_t chip                  : 1;  /**< [  0:  0](RO/H) Chip BIST in progress.  Always reads 0. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain BIST in progress.  When set, memories associated with
                                                                 the core domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain BIST in progress.  When set, memories associated with
                                                                 the MCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain BIST in progress.  When set, memories associated with
                                                                 the SCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t csr                   : 1;  /**< [  4:  4](RO/H) BIST in progress due to access to RST_DEV_MAP().  When set, memories
                                                                 associated with this access are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t ap                    : 1;  /**< [  5:  5](RO/H) BIST in progress due to AP cores being put into reset.  When set, memories
                                                                 associated with this group are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t bphy                  : 1;  /**< [  6:  6](RO/H) BPHY domain BIST in progress.  When set, memories accociated with
                                                                 the BPHY domain are being tested. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_bist_active_s cn9; */
    struct bdk_rst_bist_active_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t ap                    : 1;  /**< [  5:  5](RO/H) BIST in progress due to AP cores being put into reset.  When set, memories
                                                                 associated with this group are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t csr                   : 1;  /**< [  4:  4](RO/H) BIST in progress due to access to RST_DEV_MAP().  When set, memories
                                                                 associated with this access are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain BIST in progress.  When set, memories associated with
                                                                 the SCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain BIST in progress.  When set, memories associated with
                                                                 the MCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain BIST in progress.  When set, memories associated with
                                                                 the core domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain BIST in progress.  When set, memories associated with
                                                                 the core domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain BIST in progress.  When set, memories associated with
                                                                 the MCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain BIST in progress.  When set, memories associated with
                                                                 the SCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t csr                   : 1;  /**< [  4:  4](RO/H) BIST in progress due to access to RST_DEV_MAP().  When set, memories
                                                                 associated with this access are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t ap                    : 1;  /**< [  5:  5](RO/H) BIST in progress due to AP cores being put into reset.  When set, memories
                                                                 associated with this group are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_rst_bist_active_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t ap                    : 1;  /**< [  5:  5](RO/H) BIST in progress due to AP cores being put into reset.  When set, memories
                                                                 associated with this group are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t csr                   : 1;  /**< [  4:  4](RO/H) BIST in progress due to access to RST_DEV_MAP().  When set, memories
                                                                 associated with this access are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain BIST in progress.  When set, memories associated with
                                                                 the SCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain BIST in progress.  When set, memories associated with
                                                                 the MCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain BIST in progress.  When set, memories associated with
                                                                 the core domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t chip                  : 1;  /**< [  0:  0](RO/H) Chip BIST in progress.  Always reads 0. */
#else /* Word 0 - Little Endian */
        uint64_t chip                  : 1;  /**< [  0:  0](RO/H) Chip BIST in progress.  Always reads 0. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain BIST in progress.  When set, memories associated with
                                                                 the core domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain BIST in progress.  When set, memories associated with
                                                                 the MCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain BIST in progress.  When set, memories associated with
                                                                 the SCP domain are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t csr                   : 1;  /**< [  4:  4](RO/H) BIST in progress due to access to RST_DEV_MAP().  When set, memories
                                                                 associated with this access are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t ap                    : 1;  /**< [  5:  5](RO/H) BIST in progress due to AP cores being put into reset.  When set, memories
                                                                 associated with this group are being tested.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_bist_active_cn96xxp3 cn98xx; */
    /* struct bdk_rst_bist_active_s cnf95xx; */
    /* struct bdk_rst_bist_active_s loki; */
};
typedef union bdk_rst_bist_active bdk_rst_bist_active_t;

#define BDK_RST_BIST_ACTIVE BDK_RST_BIST_ACTIVE_FUNC()
static inline uint64_t BDK_RST_BIST_ACTIVE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_BIST_ACTIVE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001890ll;
    __bdk_csr_fatal("RST_BIST_ACTIVE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_BIST_ACTIVE bdk_rst_bist_active_t
#define bustype_BDK_RST_BIST_ACTIVE BDK_CSR_TYPE_RSL
#define basename_BDK_RST_BIST_ACTIVE "RST_BIST_ACTIVE"
#define device_bar_BDK_RST_BIST_ACTIVE 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_BIST_ACTIVE 0
#define arguments_BDK_RST_BIST_ACTIVE -1,-1,-1,-1

/**
 * Register (RSL) rst_bist_timer
 *
 * INTERNAL: RST BIST Timer Register
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_bist_timer
{
    uint64_t u;
    struct bdk_rst_bist_timer_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t count                 : 29; /**< [ 28:  0](RO) Number of 50 MHz reference clocks that have elapsed during BIST and repair during the last
                                                                 reset.
                                                                 If MSB is set the BIST chain did not complete as expected. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 29; /**< [ 28:  0](RO) Number of 50 MHz reference clocks that have elapsed during BIST and repair during the last
                                                                 reset.
                                                                 If MSB is set the BIST chain did not complete as expected. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_bist_timer_s cn8; */
    struct bdk_rst_bist_timer_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t count                 : 29; /**< [ 28:  0](RO/H) Number of 100 MHz reference clocks that have elapsed during the
                                                                 last BIST operation.  If MSB is set the BIST did not
                                                                 complete as expected. This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dll_stable. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 29; /**< [ 28:  0](RO/H) Number of 100 MHz reference clocks that have elapsed during the
                                                                 last BIST operation.  If MSB is set the BIST did not
                                                                 complete as expected. This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dll_stable. */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_bist_timer bdk_rst_bist_timer_t;

#define BDK_RST_BIST_TIMER BDK_RST_BIST_TIMER_FUNC()
static inline uint64_t BDK_RST_BIST_TIMER_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_BIST_TIMER_FUNC(void)
{
    return 0x87e006001760ll;
}

#define typedef_BDK_RST_BIST_TIMER bdk_rst_bist_timer_t
#define bustype_BDK_RST_BIST_TIMER BDK_CSR_TYPE_RSL
#define basename_BDK_RST_BIST_TIMER "RST_BIST_TIMER"
#define device_bar_BDK_RST_BIST_TIMER 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_BIST_TIMER 0
#define arguments_BDK_RST_BIST_TIMER -1,-1,-1,-1

/**
 * Register (RSL) rst_boot
 *
 * RST Boot Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_boot
{
    uint64_t u;
    struct bdk_rst_boot_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A 0-to-1 transition of CHIPKILL starts the CHIPKILL timer. When CHIPKILL=1 and the timer
                                                                 expires, chip reset is asserted internally. The CHIPKILL timer can be stopped only by
                                                                 a reset (cold, warm, soft). The length of the CHIPKILL timer is specified by
                                                                 RST_CKILL[TIMER]. This feature is effectively a delayed warm reset. */
        uint64_t reserved_61_62        : 2;
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either MIO_FUS_DAT2[TRUSTZONE_EN], FUSF_CTL[TZ_FORCE2], or the trusted-mode
                                                                 strap GPIO_STRAP\<10\> are set. */
        uint64_t ckill_ppdis           : 1;  /**< [ 59: 59](R/W) Chipkill core disable. When set to 1, cores other than core 0 will immediately
                                                                 be disabled when RST_BOOT[CHIPKILL] is set. Writes have no effect when
                                                                 RST_BOOT[CHIPKILL]=1. */
        uint64_t jt_tstmode            : 1;  /**< [ 58: 58](RO) JTAG test mode. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](RO) Reserved. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to (!trusted_mode && FUSF_CTL[FJ_DIS_HUK]).

                                                                 Software must write a one to this bit when the chain of trust is broken. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S) Disable scan. When written to 1, and FUSF_CTL[ROT_LCK] = 1, reads as 1 and scan is not
                                                                 allowed in the part.
                                                                 This state persists across soft and warm resets.

                                                                 Internal:
                                                                 This state will persist across a simulation */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t reserved_47_52        : 6;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Core-clock multiplier. [C_MUL] = (core-clock speed) / (ref-clock speed). The value
                                                                 ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [C_MUL] is set from the pi_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[127:123]. If the fuse value is \> 0, it is compared with the pi_pll_mul[5:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_39           : 1;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Coprocessor-clock multiplier. [PNR_MUL] = (coprocessor-clock speed) /(ref-clock speed).
                                                                 The value ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [PNR_MUL] is set from the pi_pnr_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[122:119]. If the fuse value is \> 0, it is compared with the pi_pnr_pll_mul[4:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_2_32         : 31;
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W) Remote boot. If set, indicates that core 0 will remain in reset after a
                                                                 chip warm/soft reset. The initial value mimics the setting of the [RBOOT_PIN]. */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO/H) Remote Boot strap. Indicates the state of remote boot as initially determined by
                                                                 GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE. If set core 0 will remain in reset
                                                                 for the cold reset. */
#else /* Word 0 - Little Endian */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO/H) Remote Boot strap. Indicates the state of remote boot as initially determined by
                                                                 GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE. If set core 0 will remain in reset
                                                                 for the cold reset. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W) Remote boot. If set, indicates that core 0 will remain in reset after a
                                                                 chip warm/soft reset. The initial value mimics the setting of the [RBOOT_PIN]. */
        uint64_t reserved_2_32         : 31;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Coprocessor-clock multiplier. [PNR_MUL] = (coprocessor-clock speed) /(ref-clock speed).
                                                                 The value ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [PNR_MUL] is set from the pi_pnr_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[122:119]. If the fuse value is \> 0, it is compared with the pi_pnr_pll_mul[4:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_39           : 1;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Core-clock multiplier. [C_MUL] = (core-clock speed) / (ref-clock speed). The value
                                                                 ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [C_MUL] is set from the pi_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[127:123]. If the fuse value is \> 0, it is compared with the pi_pll_mul[5:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_47_52        : 6;
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S) Disable scan. When written to 1, and FUSF_CTL[ROT_LCK] = 1, reads as 1 and scan is not
                                                                 allowed in the part.
                                                                 This state persists across soft and warm resets.

                                                                 Internal:
                                                                 This state will persist across a simulation */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to (!trusted_mode && FUSF_CTL[FJ_DIS_HUK]).

                                                                 Software must write a one to this bit when the chain of trust is broken. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](RO) Reserved. */
        uint64_t jt_tstmode            : 1;  /**< [ 58: 58](RO) JTAG test mode. */
        uint64_t ckill_ppdis           : 1;  /**< [ 59: 59](R/W) Chipkill core disable. When set to 1, cores other than core 0 will immediately
                                                                 be disabled when RST_BOOT[CHIPKILL] is set. Writes have no effect when
                                                                 RST_BOOT[CHIPKILL]=1. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either MIO_FUS_DAT2[TRUSTZONE_EN], FUSF_CTL[TZ_FORCE2], or the trusted-mode
                                                                 strap GPIO_STRAP\<10\> are set. */
        uint64_t reserved_61_62        : 2;
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A 0-to-1 transition of CHIPKILL starts the CHIPKILL timer. When CHIPKILL=1 and the timer
                                                                 expires, chip reset is asserted internally. The CHIPKILL timer can be stopped only by
                                                                 a reset (cold, warm, soft). The length of the CHIPKILL timer is specified by
                                                                 RST_CKILL[TIMER]. This feature is effectively a delayed warm reset. */
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_boot_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A 0-to-1 transition of CHIPKILL starts the CHIPKILL timer. When CHIPKILL=1 and the timer
                                                                 expires, chip reset is asserted internally. The CHIPKILL timer can be stopped only by
                                                                 a reset (cold, warm, soft). The length of the CHIPKILL timer is specified by
                                                                 RST_CKILL[TIMER]. This feature is effectively a delayed warm reset. */
        uint64_t jtcsrdis              : 1;  /**< [ 62: 62](R/W) JTAG CSR disable. When set to 1, during the next warm or soft reset the JTAG TAP
                                                                 controller will be disabled, i.e. DAP_IMP_DAR will be 0. This field resets to 1
                                                                 in trusted-mode, else 0. */
        uint64_t ejtagdis              : 1;  /**< [ 61: 61](R/W) Reserved. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either MIO_FUS_DAT2[TRUSTZONE_EN], FUSF_CTL[TZ_FORCE2], or the trusted-mode
                                                                 strap GPIO_STRAP\<10\> are set. */
        uint64_t ckill_ppdis           : 1;  /**< [ 59: 59](R/W) Chipkill core disable. When set to 1, cores other than core 0 will immediately
                                                                 be disabled when RST_BOOT[CHIPKILL] is set. Writes have no effect when
                                                                 RST_BOOT[CHIPKILL]=1. */
        uint64_t jt_tstmode            : 1;  /**< [ 58: 58](RO) JTAG test mode. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](RO) Reserved. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to (!trusted_mode && FUSF_CTL[FJ_DIS_HUK]).

                                                                 Software must write a one to this bit when the chain of trust is broken. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S) Disable scan. When written to 1, and FUSF_CTL[ROT_LCK] = 1, reads as 1 and scan is not
                                                                 allowed in the part.
                                                                 This state persists across soft and warm resets.

                                                                 Internal:
                                                                 This state will persist across a simulation */
        uint64_t reserved_47_54        : 8;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Core-clock multiplier. [C_MUL] = (core-clock speed) / (ref-clock speed). The value
                                                                 ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [C_MUL] is set from the pi_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[127:123]. If the fuse value is \> 0, it is compared with the pi_pll_mul[5:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_39           : 1;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Coprocessor-clock multiplier. [PNR_MUL] = (coprocessor-clock speed) /(ref-clock speed).
                                                                 The value ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [PNR_MUL] is set from the pi_pnr_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[122:119]. If the fuse value is \> 0, it is compared with the pi_pnr_pll_mul[4:1]
                                                                 pins and the smaller value is used. */
        uint64_t lboot_oci             : 3;  /**< [ 32: 30](R/W1C/H) Reserved.
                                                                 Internal:
                                                                 Last boot cause mask for CCPI; resets only with PLL_DC_OK.
                                                                 \<32\> = Warm reset due to CCPI link 2 going down.
                                                                 \<31\> = Warm reset due to CCPI link 1 going down.
                                                                 \<30\> = Warm reset due to CCPI link 0 going down. */
        uint64_t lboot_pf_flr          : 4;  /**< [ 29: 26](R/W1C/H) Last boot cause was caused by a PF Function Level Reset event.
                                                                 \<29\> = Warm reset due to PF FLR on PEM3.
                                                                 \<28\> = Warm reset due to PF FLR on PEM2.
                                                                 \<27\> = Warm reset due to PF FLR on PEM1.
                                                                 \<26\> = Warm reset due to PF FLR on PEM0. */
        uint64_t lboot_ckill           : 1;  /**< [ 25: 25](R/W1C/H) Last boot cause was chip kill timer expiring.  See RST_BOOT[CHIPKILL]. */
        uint64_t lboot_jtg             : 1;  /**< [ 24: 24](R/W1C/H) Last boot cause was write to JTG reset. */
        uint64_t lboot_ext45           : 6;  /**< [ 23: 18](R/W1C/H) Reserved. */
        uint64_t lboot_ext23           : 6;  /**< [ 17: 12](R/W1C/H) Last boot cause mask for PEM2; resets only with PLL_DC_OK.
                                                                 \<17\> = Reserved
                                                                 \<16\> = Warm reset due to Cntl2 link-down or hot-reset.
                                                                 \<15\> = Reserved
                                                                 \<14\> = Cntl2 reset due to PERST2_L pin.
                                                                 \<13\> = Reserved
                                                                 \<12\> = Warm reset due to PERST2_L pin. */
        uint64_t lboot                 : 10; /**< [ 11:  2](R/W1C/H) Last boot cause mask for PEM1 and PEM0; resets only with PLL_DC_OK.
                                                                 \<11\> = Soft reset due to watchdog.
                                                                 \<10\> = Soft reset due to RST_SOFT_RST write.
                                                                 \<9\> = Warm reset due to Cntl1 link-down or hot-reset.
                                                                 \<8\> = Warm reset due to Cntl0 link-down or hot-reset.
                                                                 \<7\> = Cntl1 reset due to PERST1_L pin.
                                                                 \<6\> = Cntl0 reset due to PERST0_L pin.
                                                                 \<5\> = Warm reset due to PERST1_L pin.
                                                                 \<4\> = Warm reset due to PERST0_L pin.
                                                                 \<3\> = Warm reset due to CHIP_RESET_L pin.
                                                                 \<2\> = Cold reset due to PLL_DC_OK pin. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W) Remote boot. If set, indicates that core 0 will remain in reset after a
                                                                 chip warm/soft reset. The initial value mimics the setting of the [RBOOT_PIN]. */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO/H) Remote Boot strap. Indicates the state of remote boot as initially determined by
                                                                 GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE. If set core 0 will remain in reset
                                                                 for the cold reset. */
#else /* Word 0 - Little Endian */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO/H) Remote Boot strap. Indicates the state of remote boot as initially determined by
                                                                 GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE. If set core 0 will remain in reset
                                                                 for the cold reset. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W) Remote boot. If set, indicates that core 0 will remain in reset after a
                                                                 chip warm/soft reset. The initial value mimics the setting of the [RBOOT_PIN]. */
        uint64_t lboot                 : 10; /**< [ 11:  2](R/W1C/H) Last boot cause mask for PEM1 and PEM0; resets only with PLL_DC_OK.
                                                                 \<11\> = Soft reset due to watchdog.
                                                                 \<10\> = Soft reset due to RST_SOFT_RST write.
                                                                 \<9\> = Warm reset due to Cntl1 link-down or hot-reset.
                                                                 \<8\> = Warm reset due to Cntl0 link-down or hot-reset.
                                                                 \<7\> = Cntl1 reset due to PERST1_L pin.
                                                                 \<6\> = Cntl0 reset due to PERST0_L pin.
                                                                 \<5\> = Warm reset due to PERST1_L pin.
                                                                 \<4\> = Warm reset due to PERST0_L pin.
                                                                 \<3\> = Warm reset due to CHIP_RESET_L pin.
                                                                 \<2\> = Cold reset due to PLL_DC_OK pin. */
        uint64_t lboot_ext23           : 6;  /**< [ 17: 12](R/W1C/H) Last boot cause mask for PEM2; resets only with PLL_DC_OK.
                                                                 \<17\> = Reserved
                                                                 \<16\> = Warm reset due to Cntl2 link-down or hot-reset.
                                                                 \<15\> = Reserved
                                                                 \<14\> = Cntl2 reset due to PERST2_L pin.
                                                                 \<13\> = Reserved
                                                                 \<12\> = Warm reset due to PERST2_L pin. */
        uint64_t lboot_ext45           : 6;  /**< [ 23: 18](R/W1C/H) Reserved. */
        uint64_t lboot_jtg             : 1;  /**< [ 24: 24](R/W1C/H) Last boot cause was write to JTG reset. */
        uint64_t lboot_ckill           : 1;  /**< [ 25: 25](R/W1C/H) Last boot cause was chip kill timer expiring.  See RST_BOOT[CHIPKILL]. */
        uint64_t lboot_pf_flr          : 4;  /**< [ 29: 26](R/W1C/H) Last boot cause was caused by a PF Function Level Reset event.
                                                                 \<29\> = Warm reset due to PF FLR on PEM3.
                                                                 \<28\> = Warm reset due to PF FLR on PEM2.
                                                                 \<27\> = Warm reset due to PF FLR on PEM1.
                                                                 \<26\> = Warm reset due to PF FLR on PEM0. */
        uint64_t lboot_oci             : 3;  /**< [ 32: 30](R/W1C/H) Reserved.
                                                                 Internal:
                                                                 Last boot cause mask for CCPI; resets only with PLL_DC_OK.
                                                                 \<32\> = Warm reset due to CCPI link 2 going down.
                                                                 \<31\> = Warm reset due to CCPI link 1 going down.
                                                                 \<30\> = Warm reset due to CCPI link 0 going down. */
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Coprocessor-clock multiplier. [PNR_MUL] = (coprocessor-clock speed) /(ref-clock speed).
                                                                 The value ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [PNR_MUL] is set from the pi_pnr_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[122:119]. If the fuse value is \> 0, it is compared with the pi_pnr_pll_mul[4:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_39           : 1;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Core-clock multiplier. [C_MUL] = (core-clock speed) / (ref-clock speed). The value
                                                                 ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [C_MUL] is set from the pi_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[127:123]. If the fuse value is \> 0, it is compared with the pi_pll_mul[5:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_47_54        : 8;
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S) Disable scan. When written to 1, and FUSF_CTL[ROT_LCK] = 1, reads as 1 and scan is not
                                                                 allowed in the part.
                                                                 This state persists across soft and warm resets.

                                                                 Internal:
                                                                 This state will persist across a simulation */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to (!trusted_mode && FUSF_CTL[FJ_DIS_HUK]).

                                                                 Software must write a one to this bit when the chain of trust is broken. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](RO) Reserved. */
        uint64_t jt_tstmode            : 1;  /**< [ 58: 58](RO) JTAG test mode. */
        uint64_t ckill_ppdis           : 1;  /**< [ 59: 59](R/W) Chipkill core disable. When set to 1, cores other than core 0 will immediately
                                                                 be disabled when RST_BOOT[CHIPKILL] is set. Writes have no effect when
                                                                 RST_BOOT[CHIPKILL]=1. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either MIO_FUS_DAT2[TRUSTZONE_EN], FUSF_CTL[TZ_FORCE2], or the trusted-mode
                                                                 strap GPIO_STRAP\<10\> are set. */
        uint64_t ejtagdis              : 1;  /**< [ 61: 61](R/W) Reserved. */
        uint64_t jtcsrdis              : 1;  /**< [ 62: 62](R/W) JTAG CSR disable. When set to 1, during the next warm or soft reset the JTAG TAP
                                                                 controller will be disabled, i.e. DAP_IMP_DAR will be 0. This field resets to 1
                                                                 in trusted-mode, else 0. */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A 0-to-1 transition of CHIPKILL starts the CHIPKILL timer. When CHIPKILL=1 and the timer
                                                                 expires, chip reset is asserted internally. The CHIPKILL timer can be stopped only by
                                                                 a reset (cold, warm, soft). The length of the CHIPKILL timer is specified by
                                                                 RST_CKILL[TIMER]. This feature is effectively a delayed warm reset. */
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_boot_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A 0-to-1 transition of CHIPKILL starts the CHIPKILL timer. When CHIPKILL=1 and the timer
                                                                 expires, chip reset is asserted internally. The CHIPKILL timer can be stopped only by
                                                                 a reset (cold, warm, soft). The length of the CHIPKILL timer is specified by
                                                                 RST_CKILL[TIMER]. This feature is effectively a delayed warm reset. */
        uint64_t jtcsrdis              : 1;  /**< [ 62: 62](R/W) JTAG CSR disable. When set to 1, during the next warm or soft reset the JTAG TAP
                                                                 controller will be disabled, i.e. DAP_IMP_DAR will be 0. This field resets to 1
                                                                 in trusted-mode, else 0. */
        uint64_t ejtagdis              : 1;  /**< [ 61: 61](R/W) Reserved. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either MIO_FUS_DAT2[TRUSTZONE_EN], FUSF_CTL[TZ_FORCE2], or the trusted-mode
                                                                 strap GPIO_STRAP\<10\> are set. */
        uint64_t ckill_ppdis           : 1;  /**< [ 59: 59](R/W) Chipkill core disable. When set to 1, cores other than core 0 will immediately
                                                                 be disabled when RST_BOOT[CHIPKILL] is set. Writes have no effect when
                                                                 RST_BOOT[CHIPKILL]=1. */
        uint64_t jt_tstmode            : 1;  /**< [ 58: 58](RO) JTAG test mode. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](RO) Reserved. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to (!trusted_mode && FUSF_CTL[FJ_DIS_HUK]).

                                                                 Software must write a one to this bit when the chain of trust is broken. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S) Disable scan. When written to 1, and FUSF_CTL[ROT_LCK] = 1, reads as 1 and scan is not
                                                                 allowed in the part.
                                                                 This state persists across soft and warm resets.

                                                                 Internal:
                                                                 This state will persist across a simulation */
        uint64_t reserved_47_54        : 8;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Core-clock multiplier. [C_MUL] = (core-clock speed) / (ref-clock speed). The value
                                                                 ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [C_MUL] is set from the pi_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[127:123]. If the fuse value is \> 0, it is compared with the pi_pll_mul[5:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_39           : 1;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Coprocessor-clock multiplier. [PNR_MUL] = (coprocessor-clock speed) /(ref-clock speed).
                                                                 The value ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [PNR_MUL] is set from the pi_pnr_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[122:119]. If the fuse value is \> 0, it is compared with the pi_pnr_pll_mul[4:1]
                                                                 pins and the smaller value is used. */
        uint64_t lboot_oci             : 3;  /**< [ 32: 30](R/W1C/H) Reserved.
                                                                 Internal:
                                                                 Last boot cause mask for CCPI; resets only with PLL_DC_OK.
                                                                 \<32\> = Warm reset due to CCPI link 2 going down.
                                                                 \<31\> = Warm reset due to CCPI link 1 going down.
                                                                 \<30\> = Warm reset due to CCPI link 0 going down. */
        uint64_t reserved_26_29        : 4;
        uint64_t lboot_ckill           : 1;  /**< [ 25: 25](R/W1C/H) Last boot cause was chip kill timer expiring.  See RST_BOOT[CHIPKILL]. */
        uint64_t lboot_jtg             : 1;  /**< [ 24: 24](R/W1C/H) Last boot cause was write to JTG reset. */
        uint64_t lboot_ext45           : 6;  /**< [ 23: 18](R/W1C/H) Reserved. */
        uint64_t lboot_ext23           : 6;  /**< [ 17: 12](R/W1C/H) Last boot cause mask for PEM2; resets only with PLL_DC_OK.
                                                                 \<17\> = Reserved
                                                                 \<16\> = Warm reset due to Cntl2 link-down or hot-reset.
                                                                 \<15\> = Reserved
                                                                 \<14\> = Cntl2 reset due to PERST2_L pin.
                                                                 \<13\> = Reserved
                                                                 \<12\> = Warm reset due to PERST2_L pin. */
        uint64_t lboot                 : 10; /**< [ 11:  2](R/W1C/H) Last boot cause mask for PEM1 and PEM0; resets only with PLL_DC_OK.
                                                                 \<11\> = Soft reset due to watchdog.
                                                                 \<10\> = Soft reset due to RST_SOFT_RST write.
                                                                 \<9\> = Warm reset due to Cntl1 link-down or hot-reset.
                                                                 \<8\> = Warm reset due to Cntl0 link-down or hot-reset.
                                                                 \<7\> = Cntl1 reset due to PERST1_L pin.
                                                                 \<6\> = Cntl0 reset due to PERST0_L pin.
                                                                 \<5\> = Warm reset due to PERST1_L pin.
                                                                 \<4\> = Warm reset due to PERST0_L pin.
                                                                 \<3\> = Warm reset due to CHIP_RESET_L pin.
                                                                 \<2\> = Cold reset due to PLL_DC_OK pin. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W) Remote boot. If set, indicates that core 0 will remain in reset after a
                                                                 chip warm/soft reset. The initial value mimics the setting of the [RBOOT_PIN]. */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO/H) Remote Boot strap. Indicates the state of remote boot as initially determined by
                                                                 GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE. If set core 0 will remain in reset
                                                                 for the cold reset. */
#else /* Word 0 - Little Endian */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO/H) Remote Boot strap. Indicates the state of remote boot as initially determined by
                                                                 GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE. If set core 0 will remain in reset
                                                                 for the cold reset. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W) Remote boot. If set, indicates that core 0 will remain in reset after a
                                                                 chip warm/soft reset. The initial value mimics the setting of the [RBOOT_PIN]. */
        uint64_t lboot                 : 10; /**< [ 11:  2](R/W1C/H) Last boot cause mask for PEM1 and PEM0; resets only with PLL_DC_OK.
                                                                 \<11\> = Soft reset due to watchdog.
                                                                 \<10\> = Soft reset due to RST_SOFT_RST write.
                                                                 \<9\> = Warm reset due to Cntl1 link-down or hot-reset.
                                                                 \<8\> = Warm reset due to Cntl0 link-down or hot-reset.
                                                                 \<7\> = Cntl1 reset due to PERST1_L pin.
                                                                 \<6\> = Cntl0 reset due to PERST0_L pin.
                                                                 \<5\> = Warm reset due to PERST1_L pin.
                                                                 \<4\> = Warm reset due to PERST0_L pin.
                                                                 \<3\> = Warm reset due to CHIP_RESET_L pin.
                                                                 \<2\> = Cold reset due to PLL_DC_OK pin. */
        uint64_t lboot_ext23           : 6;  /**< [ 17: 12](R/W1C/H) Last boot cause mask for PEM2; resets only with PLL_DC_OK.
                                                                 \<17\> = Reserved
                                                                 \<16\> = Warm reset due to Cntl2 link-down or hot-reset.
                                                                 \<15\> = Reserved
                                                                 \<14\> = Cntl2 reset due to PERST2_L pin.
                                                                 \<13\> = Reserved
                                                                 \<12\> = Warm reset due to PERST2_L pin. */
        uint64_t lboot_ext45           : 6;  /**< [ 23: 18](R/W1C/H) Reserved. */
        uint64_t lboot_jtg             : 1;  /**< [ 24: 24](R/W1C/H) Last boot cause was write to JTG reset. */
        uint64_t lboot_ckill           : 1;  /**< [ 25: 25](R/W1C/H) Last boot cause was chip kill timer expiring.  See RST_BOOT[CHIPKILL]. */
        uint64_t reserved_26_29        : 4;
        uint64_t lboot_oci             : 3;  /**< [ 32: 30](R/W1C/H) Reserved.
                                                                 Internal:
                                                                 Last boot cause mask for CCPI; resets only with PLL_DC_OK.
                                                                 \<32\> = Warm reset due to CCPI link 2 going down.
                                                                 \<31\> = Warm reset due to CCPI link 1 going down.
                                                                 \<30\> = Warm reset due to CCPI link 0 going down. */
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Coprocessor-clock multiplier. [PNR_MUL] = (coprocessor-clock speed) /(ref-clock speed).
                                                                 The value ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [PNR_MUL] is set from the pi_pnr_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[122:119]. If the fuse value is \> 0, it is compared with the pi_pnr_pll_mul[4:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_39           : 1;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Core-clock multiplier. [C_MUL] = (core-clock speed) / (ref-clock speed). The value
                                                                 ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [C_MUL] is set from the pi_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[127:123]. If the fuse value is \> 0, it is compared with the pi_pll_mul[5:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_47_54        : 8;
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S) Disable scan. When written to 1, and FUSF_CTL[ROT_LCK] = 1, reads as 1 and scan is not
                                                                 allowed in the part.
                                                                 This state persists across soft and warm resets.

                                                                 Internal:
                                                                 This state will persist across a simulation */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to (!trusted_mode && FUSF_CTL[FJ_DIS_HUK]).

                                                                 Software must write a one to this bit when the chain of trust is broken. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](RO) Reserved. */
        uint64_t jt_tstmode            : 1;  /**< [ 58: 58](RO) JTAG test mode. */
        uint64_t ckill_ppdis           : 1;  /**< [ 59: 59](R/W) Chipkill core disable. When set to 1, cores other than core 0 will immediately
                                                                 be disabled when RST_BOOT[CHIPKILL] is set. Writes have no effect when
                                                                 RST_BOOT[CHIPKILL]=1. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either MIO_FUS_DAT2[TRUSTZONE_EN], FUSF_CTL[TZ_FORCE2], or the trusted-mode
                                                                 strap GPIO_STRAP\<10\> are set. */
        uint64_t ejtagdis              : 1;  /**< [ 61: 61](R/W) Reserved. */
        uint64_t jtcsrdis              : 1;  /**< [ 62: 62](R/W) JTAG CSR disable. When set to 1, during the next warm or soft reset the JTAG TAP
                                                                 controller will be disabled, i.e. DAP_IMP_DAR will be 0. This field resets to 1
                                                                 in trusted-mode, else 0. */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A 0-to-1 transition of CHIPKILL starts the CHIPKILL timer. When CHIPKILL=1 and the timer
                                                                 expires, chip reset is asserted internally. The CHIPKILL timer can be stopped only by
                                                                 a reset (cold, warm, soft). The length of the CHIPKILL timer is specified by
                                                                 RST_CKILL[TIMER]. This feature is effectively a delayed warm reset. */
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_rst_boot_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A 0-to-1 transition of CHIPKILL starts the CHIPKILL timer. When CHIPKILL=1 and the timer
                                                                 expires, chip reset is asserted internally. The CHIPKILL timer can be stopped only by
                                                                 a reset (cold, warm, soft). The length of the CHIPKILL timer is specified by
                                                                 RST_CKILL[TIMER]. This feature is effectively a delayed warm reset. */
        uint64_t jtcsrdis              : 1;  /**< [ 62: 62](R/W) JTAG CSR disable. When set to 1, during the next warm or soft reset the JTAG TAP
                                                                 controller will be disabled, i.e. DAP_IMP_DAR will be 0. This field resets to 1
                                                                 in trusted-mode, else 0. */
        uint64_t ejtagdis              : 1;  /**< [ 61: 61](R/W) Reserved. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either MIO_FUS_DAT2[TRUSTZONE_EN], FUSF_CTL[TZ_FORCE2], or the trusted-mode
                                                                 strap GPIO_STRAP\<10\> are set. */
        uint64_t ckill_ppdis           : 1;  /**< [ 59: 59](R/W) Chipkill core disable. When set to 1, cores other than core 0 will immediately
                                                                 be disabled when RST_BOOT[CHIPKILL] is set. Writes have no effect when
                                                                 RST_BOOT[CHIPKILL]=1. */
        uint64_t jt_tstmode            : 1;  /**< [ 58: 58](RO) JTAG test mode. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](RO) VRM error. VRM did not complete operations within 5.25ms of PLL_DC_OK being
                                                                 asserted. PLLs were released automatically. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to (!trusted_mode && FUSF_CTL[FJ_DIS_HUK]).

                                                                 Software must write a one to this bit when the chain of trust is broken. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S) Disable scan. When written to 1, and FUSF_CTL[ROT_LCK] = 1, reads as 1 and scan is not
                                                                 allowed in the part.
                                                                 This state persists across soft and warm resets.

                                                                 Internal:
                                                                 This state will persist across a simulation */
        uint64_t reserved_47_54        : 8;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Core-clock multiplier. [C_MUL] = (core-clock speed) / (ref-clock speed). The value
                                                                 ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [C_MUL] is set from the pi_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[127:123]. If the fuse value is \> 0, it is compared with the pi_pll_mul[5:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_39           : 1;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Coprocessor-clock multiplier. [PNR_MUL] = (coprocessor-clock speed) /(ref-clock speed).
                                                                 The value ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [PNR_MUL] is set from the pi_pnr_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[122:119]. If the fuse value is \> 0, it is compared with the pi_pnr_pll_mul[4:1]
                                                                 pins and the smaller value is used. */
        uint64_t lboot_oci             : 3;  /**< [ 32: 30](R/W1C/H) Reserved.
                                                                 Internal:
                                                                 Last boot cause mask for CCPI; resets only with PLL_DC_OK.
                                                                 \<32\> = Warm reset due to CCPI link 2 going down.
                                                                 \<31\> = Warm reset due to CCPI link 1 going down.
                                                                 \<30\> = Warm reset due to CCPI link 0 going down. */
        uint64_t lboot_pf_flr          : 4;  /**< [ 29: 26](R/W1C/H) Last boot cause was caused by a PF Function Level Reset event.
                                                                 \<29\> = Warm reset due to PF FLR on PEM3.
                                                                 \<28\> = Warm reset due to PF FLR on PEM2.
                                                                 \<27\> = Warm reset due to PF FLR on PEM1.
                                                                 \<26\> = Warm reset due to PF FLR on PEM0. */
        uint64_t lboot_ckill           : 1;  /**< [ 25: 25](R/W1C/H) Last boot cause was chip kill timer expiring.  See RST_BOOT[CHIPKILL]. */
        uint64_t lboot_jtg             : 1;  /**< [ 24: 24](R/W1C/H) Last boot cause was write to JTG reset. */
        uint64_t lboot_ext45           : 6;  /**< [ 23: 18](R/W1C/H) Reserved. */
        uint64_t lboot_ext23           : 6;  /**< [ 17: 12](R/W1C/H) Last boot cause mask for PEM3 and PEM2; resets only with PLL_DC_OK.
                                                                 \<17\> = Warm reset due to Cntl3 link-down or hot-reset.
                                                                 \<16\> = Warm reset due to Cntl2 link-down or hot-reset.
                                                                 \<15\> = Cntl3 reset due to PERST3_L pin.
                                                                 \<14\> = Cntl2 reset due to PERST2_L pin.
                                                                 \<13\> = Warm reset due to PERST3_L pin.
                                                                 \<12\> = Warm reset due to PERST2_L pin. */
        uint64_t lboot                 : 10; /**< [ 11:  2](R/W1C/H) Last boot cause mask for PEM1 and PEM0; resets only with PLL_DC_OK.
                                                                 \<11\> = Soft reset due to watchdog.
                                                                 \<10\> = Soft reset due to RST_SOFT_RST write.
                                                                 \<9\> = Warm reset due to Cntl1 link-down or hot-reset.
                                                                 \<8\> = Warm reset due to Cntl0 link-down or hot-reset.
                                                                 \<7\> = Cntl1 reset due to PERST1_L pin.
                                                                 \<6\> = Cntl0 reset due to PERST0_L pin.
                                                                 \<5\> = Warm reset due to PERST1_L pin.
                                                                 \<4\> = Warm reset due to PERST0_L pin.
                                                                 \<3\> = Warm reset due to CHIP_RESET_L pin.
                                                                 \<2\> = Cold reset due to PLL_DC_OK pin. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W) Remote boot. If set, indicates that core 0 will remain in reset after a
                                                                 chip warm/soft reset. The initial value mimics the setting of the [RBOOT_PIN]. */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO/H) Remote Boot strap. Indicates the state of remote boot as initially determined by
                                                                 GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE. If set core 0 will remain in reset
                                                                 for the cold reset. */
#else /* Word 0 - Little Endian */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO/H) Remote Boot strap. Indicates the state of remote boot as initially determined by
                                                                 GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE. If set core 0 will remain in reset
                                                                 for the cold reset. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W) Remote boot. If set, indicates that core 0 will remain in reset after a
                                                                 chip warm/soft reset. The initial value mimics the setting of the [RBOOT_PIN]. */
        uint64_t lboot                 : 10; /**< [ 11:  2](R/W1C/H) Last boot cause mask for PEM1 and PEM0; resets only with PLL_DC_OK.
                                                                 \<11\> = Soft reset due to watchdog.
                                                                 \<10\> = Soft reset due to RST_SOFT_RST write.
                                                                 \<9\> = Warm reset due to Cntl1 link-down or hot-reset.
                                                                 \<8\> = Warm reset due to Cntl0 link-down or hot-reset.
                                                                 \<7\> = Cntl1 reset due to PERST1_L pin.
                                                                 \<6\> = Cntl0 reset due to PERST0_L pin.
                                                                 \<5\> = Warm reset due to PERST1_L pin.
                                                                 \<4\> = Warm reset due to PERST0_L pin.
                                                                 \<3\> = Warm reset due to CHIP_RESET_L pin.
                                                                 \<2\> = Cold reset due to PLL_DC_OK pin. */
        uint64_t lboot_ext23           : 6;  /**< [ 17: 12](R/W1C/H) Last boot cause mask for PEM3 and PEM2; resets only with PLL_DC_OK.
                                                                 \<17\> = Warm reset due to Cntl3 link-down or hot-reset.
                                                                 \<16\> = Warm reset due to Cntl2 link-down or hot-reset.
                                                                 \<15\> = Cntl3 reset due to PERST3_L pin.
                                                                 \<14\> = Cntl2 reset due to PERST2_L pin.
                                                                 \<13\> = Warm reset due to PERST3_L pin.
                                                                 \<12\> = Warm reset due to PERST2_L pin. */
        uint64_t lboot_ext45           : 6;  /**< [ 23: 18](R/W1C/H) Reserved. */
        uint64_t lboot_jtg             : 1;  /**< [ 24: 24](R/W1C/H) Last boot cause was write to JTG reset. */
        uint64_t lboot_ckill           : 1;  /**< [ 25: 25](R/W1C/H) Last boot cause was chip kill timer expiring.  See RST_BOOT[CHIPKILL]. */
        uint64_t lboot_pf_flr          : 4;  /**< [ 29: 26](R/W1C/H) Last boot cause was caused by a PF Function Level Reset event.
                                                                 \<29\> = Warm reset due to PF FLR on PEM3.
                                                                 \<28\> = Warm reset due to PF FLR on PEM2.
                                                                 \<27\> = Warm reset due to PF FLR on PEM1.
                                                                 \<26\> = Warm reset due to PF FLR on PEM0. */
        uint64_t lboot_oci             : 3;  /**< [ 32: 30](R/W1C/H) Reserved.
                                                                 Internal:
                                                                 Last boot cause mask for CCPI; resets only with PLL_DC_OK.
                                                                 \<32\> = Warm reset due to CCPI link 2 going down.
                                                                 \<31\> = Warm reset due to CCPI link 1 going down.
                                                                 \<30\> = Warm reset due to CCPI link 0 going down. */
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Coprocessor-clock multiplier. [PNR_MUL] = (coprocessor-clock speed) /(ref-clock speed).
                                                                 The value ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [PNR_MUL] is set from the pi_pnr_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[122:119]. If the fuse value is \> 0, it is compared with the pi_pnr_pll_mul[4:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_39           : 1;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Core-clock multiplier. [C_MUL] = (core-clock speed) / (ref-clock speed). The value
                                                                 ref-clock speed should always be 50 MHz.

                                                                 Internal:
                                                                 [C_MUL] is set from the pi_pll_mul pins plus 6 and is limited by a set of
                                                                 fuses[127:123]. If the fuse value is \> 0, it is compared with the pi_pll_mul[5:1]
                                                                 pins and the smaller value is used. */
        uint64_t reserved_47_54        : 8;
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S) Disable scan. When written to 1, and FUSF_CTL[ROT_LCK] = 1, reads as 1 and scan is not
                                                                 allowed in the part.
                                                                 This state persists across soft and warm resets.

                                                                 Internal:
                                                                 This state will persist across a simulation */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to (!trusted_mode && FUSF_CTL[FJ_DIS_HUK]).

                                                                 Software must write a one to this bit when the chain of trust is broken. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](RO) VRM error. VRM did not complete operations within 5.25ms of PLL_DC_OK being
                                                                 asserted. PLLs were released automatically. */
        uint64_t jt_tstmode            : 1;  /**< [ 58: 58](RO) JTAG test mode. */
        uint64_t ckill_ppdis           : 1;  /**< [ 59: 59](R/W) Chipkill core disable. When set to 1, cores other than core 0 will immediately
                                                                 be disabled when RST_BOOT[CHIPKILL] is set. Writes have no effect when
                                                                 RST_BOOT[CHIPKILL]=1. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either MIO_FUS_DAT2[TRUSTZONE_EN], FUSF_CTL[TZ_FORCE2], or the trusted-mode
                                                                 strap GPIO_STRAP\<10\> are set. */
        uint64_t ejtagdis              : 1;  /**< [ 61: 61](R/W) Reserved. */
        uint64_t jtcsrdis              : 1;  /**< [ 62: 62](R/W) JTAG CSR disable. When set to 1, during the next warm or soft reset the JTAG TAP
                                                                 controller will be disabled, i.e. DAP_IMP_DAR will be 0. This field resets to 1
                                                                 in trusted-mode, else 0. */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A 0-to-1 transition of CHIPKILL starts the CHIPKILL timer. When CHIPKILL=1 and the timer
                                                                 expires, chip reset is asserted internally. The CHIPKILL timer can be stopped only by
                                                                 a reset (cold, warm, soft). The length of the CHIPKILL timer is specified by
                                                                 RST_CKILL[TIMER]. This feature is effectively a delayed warm reset. */
#endif /* Word 0 - End */
    } cn83xx;
    struct bdk_rst_boot_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A zero-to-one transition of CHIPKILL starts the CHIPKILL timer. When set and the timer
                                                                 expires, chip domain reset is asserted.
                                                                 The length of the CHIPKILL timer is specified by RST_CKILL[TIMER].
                                                                 This feature is effectively a delayed reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t jtagdis               : 1;  /**< [ 62: 62](R/W/H) JTAG access disable. When set, the debug access port of the
                                                                 JTAG TAP controller will be disabled, i.e. DAP_IMP_DAR will be zero.
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t scp_jtagdis           : 1;  /**< [ 61: 61](R/W/H) SCP JTAG debugger disable. When set, the SCP debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the MCP EJTAG interface (See [MCP_JTAGDIS]).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO/H) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either FUSF_CTL[TZ_FORCE2], or the trusted mode strap on GPIO number
                                                                 GPIO_STRAP_PIN_E::TRUSTED_MODE is set. */
        uint64_t reserved_58_59        : 2;
        uint64_t vrm_err               : 1;  /**< [ 57: 57](R/W1) Reserved. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set, FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to one if FUSF_CTL[FJ_DIS_HUK] is set and not in trusted mode.
                                                                 It is also set anytime scan mode is activated while FUSF_CTL[FJ_DIS_HUK] is set.
                                                                 Software must set this bit when the chain of trust is broken.
                                                                 This field is reinitialized with either a cold or chip domain reset. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S/H) Disable scan.  When set and FUSF_CTL[ROT_LCK] = 1, scan is not
                                                                 allowed in the part. Read requests return current disable scan status.

                                                                 Internal:
                                                                 The field is actually reset only after DCOK has been left
                                                                 deasserted for an extended period of time. */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t reserved_47_52        : 6;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Current core-clock multiplier. Clock frequency = [C_MUL] * 50 MHz.
                                                                 See RST_CORE_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [C_MUL] is a copy of RST_CORE_PLL[CUR_MUL]. */
        uint64_t reserved_39           : 1;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Current coprocessor-clock multiplier. Clock frequency = [PNR_MUL] * 50 MHz.
                                                                 See RST_PNR_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [PNR_MUL] is a copy of RST_PNR_PLL[CUR_MUL]. */
        uint64_t reserved_31_32        : 2;
        uint64_t cpt_mul               : 7;  /**< [ 30: 24](RO/H) Current crypto-clock multiplier. Clock frequency = [CPT_MUL] * 50 MHz.
                                                                 See RST_CPT_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [CPT_MUL] is a copy of RST_CPT_PLL[CUR_MUL]. */
        uint64_t reserved_2_23         : 22;
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W/H) Remote boot. If set, indicates that SCP will require a write to
                                                                 RST_SCP_DOMAIN_W1C to bring it out of reset.  Otherwise it
                                                                 will automatically come out of reset once the reset source has
                                                                 been deasserted.
                                                                 The initial value is set when [RBOOT_PIN] is true and
                                                                 trustzone has not been enabled.
                                                                 This field is reinitialized with a cold domain reset.

                                                                 Internal:
                                                                 This field is cleared when jtg__rst_disable_remote is active. */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO) Remote boot strap. The value is set when primary boot method is RST_BOOT_METHOD_E::REMOTE
                                                                 when the GPIO pins are sampled on the rising edge of PLL_DCOK. */
#else /* Word 0 - Little Endian */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO) Remote boot strap. The value is set when primary boot method is RST_BOOT_METHOD_E::REMOTE
                                                                 when the GPIO pins are sampled on the rising edge of PLL_DCOK. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W/H) Remote boot. If set, indicates that SCP will require a write to
                                                                 RST_SCP_DOMAIN_W1C to bring it out of reset.  Otherwise it
                                                                 will automatically come out of reset once the reset source has
                                                                 been deasserted.
                                                                 The initial value is set when [RBOOT_PIN] is true and
                                                                 trustzone has not been enabled.
                                                                 This field is reinitialized with a cold domain reset.

                                                                 Internal:
                                                                 This field is cleared when jtg__rst_disable_remote is active. */
        uint64_t reserved_2_23         : 22;
        uint64_t cpt_mul               : 7;  /**< [ 30: 24](RO/H) Current crypto-clock multiplier. Clock frequency = [CPT_MUL] * 50 MHz.
                                                                 See RST_CPT_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [CPT_MUL] is a copy of RST_CPT_PLL[CUR_MUL]. */
        uint64_t reserved_31_32        : 2;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Current coprocessor-clock multiplier. Clock frequency = [PNR_MUL] * 50 MHz.
                                                                 See RST_PNR_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [PNR_MUL] is a copy of RST_PNR_PLL[CUR_MUL]. */
        uint64_t reserved_39           : 1;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Current core-clock multiplier. Clock frequency = [C_MUL] * 50 MHz.
                                                                 See RST_CORE_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [C_MUL] is a copy of RST_CORE_PLL[CUR_MUL]. */
        uint64_t reserved_47_52        : 6;
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S/H) Disable scan.  When set and FUSF_CTL[ROT_LCK] = 1, scan is not
                                                                 allowed in the part. Read requests return current disable scan status.

                                                                 Internal:
                                                                 The field is actually reset only after DCOK has been left
                                                                 deasserted for an extended period of time. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set, FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to one if FUSF_CTL[FJ_DIS_HUK] is set and not in trusted mode.
                                                                 It is also set anytime scan mode is activated while FUSF_CTL[FJ_DIS_HUK] is set.
                                                                 Software must set this bit when the chain of trust is broken.
                                                                 This field is reinitialized with either a cold or chip domain reset. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](R/W1) Reserved. */
        uint64_t reserved_58_59        : 2;
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO/H) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either FUSF_CTL[TZ_FORCE2], or the trusted mode strap on GPIO number
                                                                 GPIO_STRAP_PIN_E::TRUSTED_MODE is set. */
        uint64_t scp_jtagdis           : 1;  /**< [ 61: 61](R/W/H) SCP JTAG debugger disable. When set, the SCP debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the MCP EJTAG interface (See [MCP_JTAGDIS]).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t jtagdis               : 1;  /**< [ 62: 62](R/W/H) JTAG access disable. When set, the debug access port of the
                                                                 JTAG TAP controller will be disabled, i.e. DAP_IMP_DAR will be zero.
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A zero-to-one transition of CHIPKILL starts the CHIPKILL timer. When set and the timer
                                                                 expires, chip domain reset is asserted.
                                                                 The length of the CHIPKILL timer is specified by RST_CKILL[TIMER].
                                                                 This feature is effectively a delayed reset.
                                                                 This field is reinitialized with a chip domain reset. */
#endif /* Word 0 - End */
    } cn9;
    /* struct bdk_rst_boot_cn9 cn96xx; */
    struct bdk_rst_boot_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A zero-to-one transition of CHIPKILL starts the CHIPKILL timer. When set and the timer
                                                                 expires, chip domain reset is asserted.
                                                                 The length of the CHIPKILL timer is specified by RST_CKILL[TIMER].
                                                                 This feature is effectively a delayed reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t jtagdis               : 1;  /**< [ 62: 62](R/W/H) JTAG access disable. When set, the debug access port of the
                                                                 JTAG TAP controller will be disabled, i.e. DAP_IMP_DAR will be zero.
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t scp_jtagdis           : 1;  /**< [ 61: 61](R/W/H) SCP JTAG debugger disable. When set, the SCP debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the MCP EJTAG interface (See [MCP_JTAGDIS]).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO/H) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either FUSF_CTL[TZ_FORCE2], or the trusted mode strap on GPIO number
                                                                 GPIO_STRAP_PIN_E::TRUSTED_MODE is set. */
        uint64_t reserved_58_59        : 2;
        uint64_t vrm_err               : 1;  /**< [ 57: 57](R/W1) Reserved. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set, FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to one if FUSF_CTL[FJ_DIS_HUK] is set and not in trusted mode.
                                                                 It is also set anytime scan mode is activated while FUSF_CTL[FJ_DIS_HUK] is set.
                                                                 Software must set this bit when the chain of trust is broken.
                                                                 This field is reinitialized with either a cold or chip domain reset. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S/H) Disable scan.  When set and FUSF_CTL[ROT_LCK] = 1, scan is not
                                                                 allowed in the part. Read requests return current disable scan status.

                                                                 Internal:
                                                                 The field is actually reset only after DCOK has been left
                                                                 deasserted for an extended period of time. */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t reserved_47_52        : 6;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Current core-clock multiplier. Clock frequency = [C_MUL] * 50 MHz.
                                                                 See RST_CORE_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [C_MUL] is a copy of RST_CORE_PLL[CUR_MUL]. */
        uint64_t reserved_39           : 1;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Current coprocessor-clock multiplier. Clock frequency = [PNR_MUL] * 50 MHz.
                                                                 See RST_PNR_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [PNR_MUL] is a copy of RST_PNR_PLL[CUR_MUL]. */
        uint64_t reserved_31_32        : 2;
        uint64_t cpt_mul               : 7;  /**< [ 30: 24](RO/H) Current crypto-clock multiplier for CPT0. Clock frequency = [CPT_MUL] * 50 MHz.
                                                                 See RST_CPT_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [CPT_MUL] is a copy of RST_CPT_PLL[CUR_MUL]. */
        uint64_t reserved_23           : 1;
        uint64_t cpt1_mul              : 7;  /**< [ 22: 16](RO/H) Current crypto-clock multiplier for CPT1. Clock frequency = [CPT1_MUL] * 50 MHz.
                                                                 See RST_CPT1_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [CPT1_MUL] is a copy of RST_CPT1_PLL[CUR_MUL]. */
        uint64_t reserved_15           : 1;
        uint64_t rxp_mul               : 7;  /**< [ 14:  8](RO/H) Current RXP clock multiplier. Clock frequency = [RXP_MUL] * 50 MHz.
                                                                 See RST_RXP_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [RXP_MUL] is a copy of RST_RXP_PLL[CUR_MUL]. */
        uint64_t reserved_2_7          : 6;
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W/H) Remote boot. If set, indicates that SCP will require a write to
                                                                 RST_SCP_DOMAIN_W1C to bring it out of reset.  Otherwise it
                                                                 will automatically come out of reset once the reset source has
                                                                 been deasserted.
                                                                 The initial value is set when [RBOOT_PIN] is true and
                                                                 trustzone has not been enabled.
                                                                 This field is reinitialized with a cold domain reset.

                                                                 Internal:
                                                                 This field is cleared when jtg__rst_disable_remote is active. */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO) Remote boot strap. The value is set when primary boot method is RST_BOOT_METHOD_E::REMOTE
                                                                 when the GPIO pins are sampled on the rising edge of PLL_DCOK. */
#else /* Word 0 - Little Endian */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO) Remote boot strap. The value is set when primary boot method is RST_BOOT_METHOD_E::REMOTE
                                                                 when the GPIO pins are sampled on the rising edge of PLL_DCOK. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W/H) Remote boot. If set, indicates that SCP will require a write to
                                                                 RST_SCP_DOMAIN_W1C to bring it out of reset.  Otherwise it
                                                                 will automatically come out of reset once the reset source has
                                                                 been deasserted.
                                                                 The initial value is set when [RBOOT_PIN] is true and
                                                                 trustzone has not been enabled.
                                                                 This field is reinitialized with a cold domain reset.

                                                                 Internal:
                                                                 This field is cleared when jtg__rst_disable_remote is active. */
        uint64_t reserved_2_7          : 6;
        uint64_t rxp_mul               : 7;  /**< [ 14:  8](RO/H) Current RXP clock multiplier. Clock frequency = [RXP_MUL] * 50 MHz.
                                                                 See RST_RXP_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [RXP_MUL] is a copy of RST_RXP_PLL[CUR_MUL]. */
        uint64_t reserved_15           : 1;
        uint64_t cpt1_mul              : 7;  /**< [ 22: 16](RO/H) Current crypto-clock multiplier for CPT1. Clock frequency = [CPT1_MUL] * 50 MHz.
                                                                 See RST_CPT1_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [CPT1_MUL] is a copy of RST_CPT1_PLL[CUR_MUL]. */
        uint64_t reserved_23           : 1;
        uint64_t cpt_mul               : 7;  /**< [ 30: 24](RO/H) Current crypto-clock multiplier for CPT0. Clock frequency = [CPT_MUL] * 50 MHz.
                                                                 See RST_CPT_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [CPT_MUL] is a copy of RST_CPT_PLL[CUR_MUL]. */
        uint64_t reserved_31_32        : 2;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Current coprocessor-clock multiplier. Clock frequency = [PNR_MUL] * 50 MHz.
                                                                 See RST_PNR_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [PNR_MUL] is a copy of RST_PNR_PLL[CUR_MUL]. */
        uint64_t reserved_39           : 1;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Current core-clock multiplier. Clock frequency = [C_MUL] * 50 MHz.
                                                                 See RST_CORE_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [C_MUL] is a copy of RST_CORE_PLL[CUR_MUL]. */
        uint64_t reserved_47_52        : 6;
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S/H) Disable scan.  When set and FUSF_CTL[ROT_LCK] = 1, scan is not
                                                                 allowed in the part. Read requests return current disable scan status.

                                                                 Internal:
                                                                 The field is actually reset only after DCOK has been left
                                                                 deasserted for an extended period of time. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set, FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to one if FUSF_CTL[FJ_DIS_HUK] is set and not in trusted mode.
                                                                 It is also set anytime scan mode is activated while FUSF_CTL[FJ_DIS_HUK] is set.
                                                                 Software must set this bit when the chain of trust is broken.
                                                                 This field is reinitialized with either a cold or chip domain reset. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](R/W1) Reserved. */
        uint64_t reserved_58_59        : 2;
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO/H) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either FUSF_CTL[TZ_FORCE2], or the trusted mode strap on GPIO number
                                                                 GPIO_STRAP_PIN_E::TRUSTED_MODE is set. */
        uint64_t scp_jtagdis           : 1;  /**< [ 61: 61](R/W/H) SCP JTAG debugger disable. When set, the SCP debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the MCP EJTAG interface (See [MCP_JTAGDIS]).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t jtagdis               : 1;  /**< [ 62: 62](R/W/H) JTAG access disable. When set, the debug access port of the
                                                                 JTAG TAP controller will be disabled, i.e. DAP_IMP_DAR will be zero.
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A zero-to-one transition of CHIPKILL starts the CHIPKILL timer. When set and the timer
                                                                 expires, chip domain reset is asserted.
                                                                 The length of the CHIPKILL timer is specified by RST_CKILL[TIMER].
                                                                 This feature is effectively a delayed reset.
                                                                 This field is reinitialized with a chip domain reset. */
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_rst_boot_cnf95xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A zero-to-one transition of CHIPKILL starts the CHIPKILL timer. When set and the timer
                                                                 expires, chip domain reset is asserted.
                                                                 The length of the CHIPKILL timer is specified by RST_CKILL[TIMER].
                                                                 This feature is effectively a delayed reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t jtagdis               : 1;  /**< [ 62: 62](R/W/H) JTAG access disable. When set, the debug access port of the
                                                                 JTAG TAP controller will be disabled, i.e. DAP_IMP_DAR will be zero.
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t scp_jtagdis           : 1;  /**< [ 61: 61](R/W/H) SCP JTAG debugger disable. When set, the SCP debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the MCP EJTAG interface (See [MCP_JTAGDIS]).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO/H) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either FUSF_CTL[TZ_FORCE2], or the trusted mode strap on GPIO number
                                                                 GPIO_STRAP_PIN_E::TRUSTED_MODE is set. */
        uint64_t reserved_58_59        : 2;
        uint64_t vrm_err               : 1;  /**< [ 57: 57](R/W1) Reserved. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set, FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to one if FUSF_CTL[FJ_DIS_HUK] is set and not in trusted mode.
                                                                 It is also set anytime scan mode is activated while FUSF_CTL[FJ_DIS_HUK] is set.
                                                                 Software must set this bit when the chain of trust is broken.
                                                                 This field is reinitialized with either a cold or chip domain reset. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S/H) Disable scan.  When set and FUSF_CTL[ROT_LCK] = 1, scan is not
                                                                 allowed in the part. Read requests return current disable scan status.

                                                                 Internal:
                                                                 The field is actually reset only after DCOK has been left
                                                                 deasserted for an extended period of time. */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t reserved_47_52        : 6;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Current core-clock multiplier. Clock frequency = [C_MUL] * 50 MHz.
                                                                 See RST_CORE_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [C_MUL] is a copy of RST_CORE_PLL[CUR_MUL]. */
        uint64_t reserved_39           : 1;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Current coprocessor-clock multiplier. Clock frequency = [PNR_MUL] * 50 MHz.
                                                                 See RST_PNR_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [PNR_MUL] is a copy of RST_PNR_PLL[CUR_MUL]. */
        uint64_t reserved_31_32        : 2;
        uint64_t cpt_mul               : 7;  /**< [ 30: 24](RO/H) Reserved.
                                                                 Internal:
                                                                 Unused on 95xx. */
        uint64_t reserved_23           : 1;
        uint64_t dsp_mul               : 7;  /**< [ 22: 16](RO/H) Current dsp-clock multiplier. Clock frequency = [DSP_MUL] * 50 MHz.
                                                                 See RST_DSP_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [DSP_MUL] is a copy of RST_DSP_PLL[CUR_MUL]. */
        uint64_t reserved_15           : 1;
        uint64_t bphy_mul              : 7;  /**< [ 14:  8](RO/H) Current bphy-clock multiplier. Clock frequency = [BPHY_MUL] * 50 MHz.
                                                                 See RST_BPHY_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [BPHY_MUL] is a copy of RST_BPHY_PLL[CUR_MUL]. */
        uint64_t reserved_2_7          : 6;
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W/H) Remote boot. If set, indicates that SCP will require a write to
                                                                 RST_SCP_DOMAIN_W1C to bring it out of reset.  Otherwise it
                                                                 will automatically come out of reset once the reset source has
                                                                 been deasserted.
                                                                 The initial value is set when [RBOOT_PIN] is true and
                                                                 trustzone has not been enabled.
                                                                 This field is reinitialized with a cold domain reset.

                                                                 Internal:
                                                                 This field is cleared when jtg__rst_disable_remote is active. */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO) Remote boot strap. The value is set when primary boot method is RST_BOOT_METHOD_E::REMOTE
                                                                 when the GPIO pins are sampled on the rising edge of PLL_DCOK. */
#else /* Word 0 - Little Endian */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO) Remote boot strap. The value is set when primary boot method is RST_BOOT_METHOD_E::REMOTE
                                                                 when the GPIO pins are sampled on the rising edge of PLL_DCOK. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W/H) Remote boot. If set, indicates that SCP will require a write to
                                                                 RST_SCP_DOMAIN_W1C to bring it out of reset.  Otherwise it
                                                                 will automatically come out of reset once the reset source has
                                                                 been deasserted.
                                                                 The initial value is set when [RBOOT_PIN] is true and
                                                                 trustzone has not been enabled.
                                                                 This field is reinitialized with a cold domain reset.

                                                                 Internal:
                                                                 This field is cleared when jtg__rst_disable_remote is active. */
        uint64_t reserved_2_7          : 6;
        uint64_t bphy_mul              : 7;  /**< [ 14:  8](RO/H) Current bphy-clock multiplier. Clock frequency = [BPHY_MUL] * 50 MHz.
                                                                 See RST_BPHY_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [BPHY_MUL] is a copy of RST_BPHY_PLL[CUR_MUL]. */
        uint64_t reserved_15           : 1;
        uint64_t dsp_mul               : 7;  /**< [ 22: 16](RO/H) Current dsp-clock multiplier. Clock frequency = [DSP_MUL] * 50 MHz.
                                                                 See RST_DSP_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [DSP_MUL] is a copy of RST_DSP_PLL[CUR_MUL]. */
        uint64_t reserved_23           : 1;
        uint64_t cpt_mul               : 7;  /**< [ 30: 24](RO/H) Reserved.
                                                                 Internal:
                                                                 Unused on 95xx. */
        uint64_t reserved_31_32        : 2;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Current coprocessor-clock multiplier. Clock frequency = [PNR_MUL] * 50 MHz.
                                                                 See RST_PNR_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [PNR_MUL] is a copy of RST_PNR_PLL[CUR_MUL]. */
        uint64_t reserved_39           : 1;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Current core-clock multiplier. Clock frequency = [C_MUL] * 50 MHz.
                                                                 See RST_CORE_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [C_MUL] is a copy of RST_CORE_PLL[CUR_MUL]. */
        uint64_t reserved_47_52        : 6;
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S/H) Disable scan.  When set and FUSF_CTL[ROT_LCK] = 1, scan is not
                                                                 allowed in the part. Read requests return current disable scan status.

                                                                 Internal:
                                                                 The field is actually reset only after DCOK has been left
                                                                 deasserted for an extended period of time. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set, FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to one if FUSF_CTL[FJ_DIS_HUK] is set and not in trusted mode.
                                                                 It is also set anytime scan mode is activated while FUSF_CTL[FJ_DIS_HUK] is set.
                                                                 Software must set this bit when the chain of trust is broken.
                                                                 This field is reinitialized with either a cold or chip domain reset. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](R/W1) Reserved. */
        uint64_t reserved_58_59        : 2;
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO/H) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either FUSF_CTL[TZ_FORCE2], or the trusted mode strap on GPIO number
                                                                 GPIO_STRAP_PIN_E::TRUSTED_MODE is set. */
        uint64_t scp_jtagdis           : 1;  /**< [ 61: 61](R/W/H) SCP JTAG debugger disable. When set, the SCP debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the MCP EJTAG interface (See [MCP_JTAGDIS]).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t jtagdis               : 1;  /**< [ 62: 62](R/W/H) JTAG access disable. When set, the debug access port of the
                                                                 JTAG TAP controller will be disabled, i.e. DAP_IMP_DAR will be zero.
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A zero-to-one transition of CHIPKILL starts the CHIPKILL timer. When set and the timer
                                                                 expires, chip domain reset is asserted.
                                                                 The length of the CHIPKILL timer is specified by RST_CKILL[TIMER].
                                                                 This feature is effectively a delayed reset.
                                                                 This field is reinitialized with a chip domain reset. */
#endif /* Word 0 - End */
    } cnf95xxp1;
    struct bdk_rst_boot_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A zero-to-one transition of CHIPKILL starts the CHIPKILL timer. When set and the timer
                                                                 expires, chip domain reset is asserted.
                                                                 The length of the CHIPKILL timer is specified by RST_CKILL[TIMER].
                                                                 This feature is effectively a delayed reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t jtagdis               : 1;  /**< [ 62: 62](R/W/H) JTAG access disable. When set, the debug access port of the
                                                                 JTAG TAP controller will be disabled, i.e. DAP_IMP_DAR will be zero.
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t scp_jtagdis           : 1;  /**< [ 61: 61](R/W/H) SCP JTAG debugger disable. When set, the SCP debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the MCP EJTAG interface (See [MCP_JTAGDIS]).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO/H) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either FUSF_CTL[TZ_FORCE2], or the trusted mode strap on GPIO number
                                                                 GPIO_STRAP_PIN_E::TRUSTED_MODE is set. */
        uint64_t reserved_58_59        : 2;
        uint64_t vrm_err               : 1;  /**< [ 57: 57](R/W1) Reserved. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set, FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to one if FUSF_CTL[FJ_DIS_HUK] is set and not in trusted mode.
                                                                 It is also set anytime scan mode is activated while FUSF_CTL[FJ_DIS_HUK] is set.
                                                                 Software must set this bit when the chain of trust is broken.
                                                                 This field is reinitialized with either a cold or chip domain reset. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S/H) Disable scan.  When set and FUSF_CTL[ROT_LCK] = 1, scan is not
                                                                 allowed in the part. Read requests return current disable scan status.

                                                                 Internal:
                                                                 The field is actually reset only after DCOK has been left
                                                                 deasserted for an extended period of time. */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t reserved_47_52        : 6;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Current core-clock multiplier. Clock frequency = [C_MUL] * 50 MHz.
                                                                 See RST_CORE_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [C_MUL] is a copy of RST_CORE_PLL[CUR_MUL]. */
        uint64_t reserved_39           : 1;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Current coprocessor-clock multiplier. Clock frequency = [PNR_MUL] * 50 MHz.
                                                                 See RST_PNR_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [PNR_MUL] is a copy of RST_PNR_PLL[CUR_MUL]. */
        uint64_t reserved_31_32        : 2;
        uint64_t cpt_mul               : 7;  /**< [ 30: 24](RO/H) Reserved.
                                                                 Internal:
                                                                 Unused on 95xx. */
        uint64_t reserved_23           : 1;
        uint64_t dsp_mul               : 7;  /**< [ 22: 16](RO/H) Current DSP-clock multiplier. Clock frequency = [DSP_MUL] * 50 MHz.
                                                                 See RST_DSP_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [DSP_MUL] is a copy of RST_DSP_PLL[CUR_MUL]. */
        uint64_t reserved_15           : 1;
        uint64_t bphy_mul              : 7;  /**< [ 14:  8](RO/H) Current BPHY-clock multiplier. Clock frequency = [BPHY_MUL] * 50 MHz.
                                                                 See RST_BPHY_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [BPHY_MUL] is a copy of RST_BPHY_PLL[CUR_MUL]. */
        uint64_t reserved_2_7          : 6;
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W/H) Remote boot. If set, indicates that SCP will require a write to
                                                                 RST_SCP_DOMAIN_W1C to bring it out of reset.  Otherwise it
                                                                 will automatically come out of reset once the reset source has
                                                                 been deasserted.
                                                                 The initial value is set when [RBOOT_PIN] is true and
                                                                 trustzone has not been enabled.
                                                                 This field is reinitialized with a cold domain reset.

                                                                 Internal:
                                                                 This field is cleared when jtg__rst_disable_remote is active. */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO) Remote boot strap. The value is set when primary boot method is RST_BOOT_METHOD_E::REMOTE
                                                                 when the GPIO pins are sampled on the rising edge of PLL_DCOK. */
#else /* Word 0 - Little Endian */
        uint64_t rboot_pin             : 1;  /**< [  0:  0](RO) Remote boot strap. The value is set when primary boot method is RST_BOOT_METHOD_E::REMOTE
                                                                 when the GPIO pins are sampled on the rising edge of PLL_DCOK. */
        uint64_t rboot                 : 1;  /**< [  1:  1](R/W/H) Remote boot. If set, indicates that SCP will require a write to
                                                                 RST_SCP_DOMAIN_W1C to bring it out of reset.  Otherwise it
                                                                 will automatically come out of reset once the reset source has
                                                                 been deasserted.
                                                                 The initial value is set when [RBOOT_PIN] is true and
                                                                 trustzone has not been enabled.
                                                                 This field is reinitialized with a cold domain reset.

                                                                 Internal:
                                                                 This field is cleared when jtg__rst_disable_remote is active. */
        uint64_t reserved_2_7          : 6;
        uint64_t bphy_mul              : 7;  /**< [ 14:  8](RO/H) Current BPHY-clock multiplier. Clock frequency = [BPHY_MUL] * 50 MHz.
                                                                 See RST_BPHY_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [BPHY_MUL] is a copy of RST_BPHY_PLL[CUR_MUL]. */
        uint64_t reserved_15           : 1;
        uint64_t dsp_mul               : 7;  /**< [ 22: 16](RO/H) Current DSP-clock multiplier. Clock frequency = [DSP_MUL] * 50 MHz.
                                                                 See RST_DSP_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [DSP_MUL] is a copy of RST_DSP_PLL[CUR_MUL]. */
        uint64_t reserved_23           : 1;
        uint64_t cpt_mul               : 7;  /**< [ 30: 24](RO/H) Reserved.
                                                                 Internal:
                                                                 Unused on 95xx. */
        uint64_t reserved_31_32        : 2;
        uint64_t pnr_mul               : 6;  /**< [ 38: 33](RO/H) Current coprocessor-clock multiplier. Clock frequency = [PNR_MUL] * 50 MHz.
                                                                 See RST_PNR_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [PNR_MUL] is a copy of RST_PNR_PLL[CUR_MUL]. */
        uint64_t reserved_39           : 1;
        uint64_t c_mul                 : 7;  /**< [ 46: 40](RO/H) Current core-clock multiplier. Clock frequency = [C_MUL] * 50 MHz.
                                                                 See RST_CORE_PLL for details on programming and initial values.

                                                                 Internal:
                                                                 [C_MUL] is a copy of RST_CORE_PLL[CUR_MUL]. */
        uint64_t reserved_47_52        : 6;
        uint64_t gpio_ejtag            : 1;  /**< [ 53: 53](R/W/H) Use GPIO pins for EJTAG.  When set, the EJTAG chain consisting
                                                                 of MCP and SCP devices is routed directly to GPIO pins.  When
                                                                 cleared these devices are included in the standard JTAG chain.
                                                                 The specific GPIO pins are selected with GPIO_BIT_CFG()[PIN_SEL].
                                                                 This field is reinitialized with a cold domain reset.
                                                                 Reset value is determined by GPIO strap pin number
                                                                 GPIO_STRAP_PIN_E::MCP_DBG_ON_GPIO. */
        uint64_t mcp_jtagdis           : 1;  /**< [ 54: 54](R/W/H) MCP JTAG debugger disable. When set, the MCP Debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the SCP EJTAG interface (See EJTAGDIS).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t dis_scan              : 1;  /**< [ 55: 55](R/W1S/H) Disable scan.  When set and FUSF_CTL[ROT_LCK] = 1, scan is not
                                                                 allowed in the part. Read requests return current disable scan status.

                                                                 Internal:
                                                                 The field is actually reset only after DCOK has been left
                                                                 deasserted for an extended period of time. */
        uint64_t dis_huk               : 1;  /**< [ 56: 56](R/W1S) Disable HUK. Secure only and W1S set-only. When set, FUSF_SSK(),
                                                                 FUSF_HUK(), FUSF_EK(), and FUSF_SW() cannot be read.
                                                                 Resets to one if FUSF_CTL[FJ_DIS_HUK] is set and not in trusted mode.
                                                                 It is also set anytime scan mode is activated while FUSF_CTL[FJ_DIS_HUK] is set.
                                                                 Software must set this bit when the chain of trust is broken.
                                                                 This field is reinitialized with either a cold or chip domain reset. */
        uint64_t vrm_err               : 1;  /**< [ 57: 57](R/W1) Reserved. */
        uint64_t reserved_58_59        : 2;
        uint64_t trusted_mode          : 1;  /**< [ 60: 60](RO/H) When set, chip is operating as a trusted device. This bit is asserted when
                                                                 either FUSF_CTL[TZ_FORCE2], or the trusted mode strap on GPIO number
                                                                 GPIO_STRAP_PIN_E::TRUSTED_MODE is set. */
        uint64_t scp_jtagdis           : 1;  /**< [ 61: 61](R/W/H) SCP JTAG debugger disable. When set, the SCP debug interface of
                                                                 the EJTAG TAP controller will be disabled. This field does not
                                                                 control the MCP EJTAG interface (See [MCP_JTAGDIS]).
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t jtagdis               : 1;  /**< [ 62: 62](R/W/H) JTAG access disable. When set, the debug access port of the
                                                                 JTAG TAP controller will be disabled, i.e. DAP_IMP_DAR will be zero.
                                                                 This field resets to one in trusted mode otherwise it is cleared.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t chipkill              : 1;  /**< [ 63: 63](R/W1S) A zero-to-one transition of CHIPKILL starts the CHIPKILL timer. When set and the timer
                                                                 expires, chip domain reset is asserted.
                                                                 The length of the CHIPKILL timer is specified by RST_CKILL[TIMER].
                                                                 This feature is effectively a delayed reset.
                                                                 This field is reinitialized with a chip domain reset. */
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_rst_boot_cnf95xxp2 loki; */
};
typedef union bdk_rst_boot bdk_rst_boot_t;

#define BDK_RST_BOOT BDK_RST_BOOT_FUNC()
static inline uint64_t BDK_RST_BOOT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_BOOT_FUNC(void)
{
    return 0x87e006001600ll;
}

#define typedef_BDK_RST_BOOT bdk_rst_boot_t
#define bustype_BDK_RST_BOOT BDK_CSR_TYPE_RSL
#define basename_BDK_RST_BOOT "RST_BOOT"
#define device_bar_BDK_RST_BOOT 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_BOOT 0
#define arguments_BDK_RST_BOOT -1,-1,-1,-1

/**
 * Register (RSL) rst_boot_status
 *
 * RST Boot Status Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_boot_status
{
    uint64_t u;
    struct bdk_rst_boot_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t stat3                 : 16; /**< [ 63: 48](R/W) JTAG-accessible boot status word three. Used by software to indicate progress of
                                                                 boot. Accessible via JTG/DTX with offset 17.

                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t stat2                 : 16; /**< [ 47: 32](R/W) JTAG-accessible boot status word two. Used by software to indicate progress of
                                                                 boot. Accessible via JTG/DTX with offset 16.

                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t stat1                 : 16; /**< [ 31: 16](R/W) JTAG-accessible boot status word one. Used by software to indicate progress of
                                                                 boot. Accessible via JTG/DTX with offset 13.

                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t stat0                 : 16; /**< [ 15:  0](R/W) JTAG-accessible boot status word zero. Used by software to indicate progress of
                                                                 boot. Accessible via JTG/DTX with offset 12.

                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t stat0                 : 16; /**< [ 15:  0](R/W) JTAG-accessible boot status word zero. Used by software to indicate progress of
                                                                 boot. Accessible via JTG/DTX with offset 12.

                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t stat1                 : 16; /**< [ 31: 16](R/W) JTAG-accessible boot status word one. Used by software to indicate progress of
                                                                 boot. Accessible via JTG/DTX with offset 13.

                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t stat2                 : 16; /**< [ 47: 32](R/W) JTAG-accessible boot status word two. Used by software to indicate progress of
                                                                 boot. Accessible via JTG/DTX with offset 16.

                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t stat3                 : 16; /**< [ 63: 48](R/W) JTAG-accessible boot status word three. Used by software to indicate progress of
                                                                 boot. Accessible via JTG/DTX with offset 17.

                                                                 This field is always reinitialized on a chip domain reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_boot_status_s cn; */
};
typedef union bdk_rst_boot_status bdk_rst_boot_status_t;

#define BDK_RST_BOOT_STATUS BDK_RST_BOOT_STATUS_FUNC()
static inline uint64_t BDK_RST_BOOT_STATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_BOOT_STATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001800ll;
    __bdk_csr_fatal("RST_BOOT_STATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_BOOT_STATUS bdk_rst_boot_status_t
#define bustype_BDK_RST_BOOT_STATUS BDK_CSR_TYPE_RSL
#define basename_BDK_RST_BOOT_STATUS "RST_BOOT_STATUS"
#define device_bar_BDK_RST_BOOT_STATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_BOOT_STATUS 0
#define arguments_BDK_RST_BOOT_STATUS -1,-1,-1,-1

/**
 * Register (RSL) rst_bphy_domain_w1c
 *
 * RST BPHY Domain Soft Reset Clear Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_bphy_domain_w1c
{
    uint64_t u;
    struct bdk_rst_bphy_domain_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear softare-initiated reset of the BPHY processor and associated logic.
                                                                 When set to one, the soft reset of the bphy is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual bphy domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[BPHY] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[BPHY] is set.
                                                                 This field is always reinitialized on a core domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear softare-initiated reset of the BPHY processor and associated logic.
                                                                 When set to one, the soft reset of the bphy is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual bphy domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[BPHY] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[BPHY] is set.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_bphy_domain_w1c_s cn9; */
    /* struct bdk_rst_bphy_domain_w1c_s cnf95xxp1; */
    struct bdk_rst_bphy_domain_w1c_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear software-initiated reset of the BPHY processor and associated logic.
                                                                 When set to one, the soft reset of the BPHY is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual BPHY domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[BPHY] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[BPHY] is set.
                                                                 This field is always reinitialized on a core domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear software-initiated reset of the BPHY processor and associated logic.
                                                                 When set to one, the soft reset of the BPHY is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual BPHY domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[BPHY] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[BPHY] is set.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_rst_bphy_domain_w1c_cnf95xxp2 loki; */
};
typedef union bdk_rst_bphy_domain_w1c bdk_rst_bphy_domain_w1c_t;

#define BDK_RST_BPHY_DOMAIN_W1C BDK_RST_BPHY_DOMAIN_W1C_FUNC()
static inline uint64_t BDK_RST_BPHY_DOMAIN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_BPHY_DOMAIN_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CNF95XX))
        return 0x87e006001858ll;
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e006001858ll;
    __bdk_csr_fatal("RST_BPHY_DOMAIN_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_BPHY_DOMAIN_W1C bdk_rst_bphy_domain_w1c_t
#define bustype_BDK_RST_BPHY_DOMAIN_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_RST_BPHY_DOMAIN_W1C "RST_BPHY_DOMAIN_W1C"
#define device_bar_BDK_RST_BPHY_DOMAIN_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_BPHY_DOMAIN_W1C 0
#define arguments_BDK_RST_BPHY_DOMAIN_W1C -1,-1,-1,-1

/**
 * Register (RSL) rst_bphy_domain_w1s
 *
 * RST BPHY Domain Soft Reset Set Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_bphy_domain_w1s
{
    uint64_t u;
    struct bdk_rst_bphy_domain_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Set software-initiated reset of BPHY associated logic.
                                                                 When set to one, all logic associated with the bphy domain is placed in reset.
                                                                 Reads of this register show the soft reset state.  Not the actual bphy domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[BPHY] shows
                                                                 the actual reset state.
                                                                 This field is always reinitialized on a core domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Set software-initiated reset of BPHY associated logic.
                                                                 When set to one, all logic associated with the bphy domain is placed in reset.
                                                                 Reads of this register show the soft reset state.  Not the actual bphy domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[BPHY] shows
                                                                 the actual reset state.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_bphy_domain_w1s_s cn9; */
    /* struct bdk_rst_bphy_domain_w1s_s cnf95xxp1; */
    struct bdk_rst_bphy_domain_w1s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Set software-initiated reset of BPHY associated logic.
                                                                 When set to one, all logic associated with the BPHY domain is placed in reset.
                                                                 Reads of this register show the soft reset state.  Not the actual BPHY domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[BPHY] shows
                                                                 the actual reset state.
                                                                 This field is always reinitialized on a core domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Set software-initiated reset of BPHY associated logic.
                                                                 When set to one, all logic associated with the BPHY domain is placed in reset.
                                                                 Reads of this register show the soft reset state.  Not the actual BPHY domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[BPHY] shows
                                                                 the actual reset state.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_rst_bphy_domain_w1s_cnf95xxp2 loki; */
};
typedef union bdk_rst_bphy_domain_w1s bdk_rst_bphy_domain_w1s_t;

#define BDK_RST_BPHY_DOMAIN_W1S BDK_RST_BPHY_DOMAIN_W1S_FUNC()
static inline uint64_t BDK_RST_BPHY_DOMAIN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_BPHY_DOMAIN_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CNF95XX))
        return 0x87e006001850ll;
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e006001850ll;
    __bdk_csr_fatal("RST_BPHY_DOMAIN_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_BPHY_DOMAIN_W1S bdk_rst_bphy_domain_w1s_t
#define bustype_BDK_RST_BPHY_DOMAIN_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_RST_BPHY_DOMAIN_W1S "RST_BPHY_DOMAIN_W1S"
#define device_bar_BDK_RST_BPHY_DOMAIN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_BPHY_DOMAIN_W1S 0
#define arguments_BDK_RST_BPHY_DOMAIN_W1S -1,-1,-1,-1

/**
 * Register (RSL) rst_bphy_pll
 *
 * RST BPHY Clock PLL Control Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_bphy_pll
{
    uint64_t u;
    struct bdk_rst_bphy_pll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) BPHY clockout select.
                                                                   0x0 = BPHY clock divided by 32.
                                                                   0x1 = BPHY clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) BPHY clockout reset. The bphy clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 bclk/dsp_clk/sclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) BPHY PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) BPHY PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) BPHY clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[BPHY_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both pll is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) BPHY PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[BPHY_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) BPHY clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[BPHY_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) BPHY clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[BPHY_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) BPHY PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[BPHY_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both pll is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) BPHY clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[BPHY_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) BPHY PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) BPHY PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 bclk/dsp_clk/sclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) BPHY clockout reset. The bphy clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) BPHY clockout select.
                                                                   0x0 = BPHY clock divided by 32.
                                                                   0x1 = BPHY clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_bphy_pll_s cn9; */
    /* struct bdk_rst_bphy_pll_s cnf95xxp1; */
    struct bdk_rst_bphy_pll_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) BPHY clockout select.
                                                                   0x0 = BPHY clock divided by 32.
                                                                   0x1 = BPHY clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) BPHY clockout reset. The BPHY clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 bclk/dsp_clk/sclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) BPHY PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) BPHY PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) BPHY clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[BPHY_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) BPHY PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[BPHY_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) BPHY clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[BPHY_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) BPHY clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[BPHY_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) BPHY PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[BPHY_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) BPHY clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[BPHY_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) BPHY PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) BPHY PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 bclk/dsp_clk/sclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) BPHY clockout reset. The BPHY clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) BPHY clockout select.
                                                                   0x0 = BPHY clock divided by 32.
                                                                   0x1 = BPHY clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_rst_bphy_pll_cnf95xxp2 loki; */
};
typedef union bdk_rst_bphy_pll bdk_rst_bphy_pll_t;

#define BDK_RST_BPHY_PLL BDK_RST_BPHY_PLL_FUNC()
static inline uint64_t BDK_RST_BPHY_PLL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_BPHY_PLL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CNF95XX))
        return 0x87e00a001768ll;
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e00a001768ll;
    __bdk_csr_fatal("RST_BPHY_PLL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_BPHY_PLL bdk_rst_bphy_pll_t
#define bustype_BDK_RST_BPHY_PLL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_BPHY_PLL "RST_BPHY_PLL"
#define device_bar_BDK_RST_BPHY_PLL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_BPHY_PLL 0
#define arguments_BDK_RST_BPHY_PLL -1,-1,-1,-1

/**
 * Register (RSL) rst_cfg
 *
 * RST Configuration Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_cfg
{
    uint64_t u;
    struct bdk_rst_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bist_delay            : 58; /**< [ 63:  6](RO/H) Reserved. */
        uint64_t reserved_3_5          : 3;
        uint64_t cntl_clr_bist         : 1;  /**< [  2:  2](R/W) Perform clear BIST during control-only reset, instead of a full BIST. A warm/soft reset
                                                                 does not change this field. */
        uint64_t warm_clr_bist         : 1;  /**< [  1:  1](R/W) Perform clear BIST during warm reset, instead of a full BIST. A warm/soft reset does not
                                                                 change this field. Note that a cold reset always performs a full BIST. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t warm_clr_bist         : 1;  /**< [  1:  1](R/W) Perform clear BIST during warm reset, instead of a full BIST. A warm/soft reset does not
                                                                 change this field. Note that a cold reset always performs a full BIST. */
        uint64_t cntl_clr_bist         : 1;  /**< [  2:  2](R/W) Perform clear BIST during control-only reset, instead of a full BIST. A warm/soft reset
                                                                 does not change this field. */
        uint64_t reserved_3_5          : 3;
        uint64_t bist_delay            : 58; /**< [ 63:  6](RO/H) Reserved. */
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_cfg_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t bist_delay            : 58; /**< [ 63:  6](RO/H) Reserved. */
        uint64_t reserved_3_5          : 3;
        uint64_t cntl_clr_bist         : 1;  /**< [  2:  2](R/W) Perform clear BIST during control-only reset, instead of a full BIST. A warm/soft reset
                                                                 does not change this field. */
        uint64_t warm_clr_bist         : 1;  /**< [  1:  1](R/W) Perform clear BIST during warm reset, instead of a full BIST. A warm/soft reset does not
                                                                 change this field. Note that a cold reset always performs a full BIST. */
        uint64_t soft_clr_bist         : 1;  /**< [  0:  0](R/W) Perform clear BIST during soft reset, instead of a full BIST. A warm/soft reset does not
                                                                 change this field. Note that a cold reset always performs a full BIST. */
#else /* Word 0 - Little Endian */
        uint64_t soft_clr_bist         : 1;  /**< [  0:  0](R/W) Perform clear BIST during soft reset, instead of a full BIST. A warm/soft reset does not
                                                                 change this field. Note that a cold reset always performs a full BIST. */
        uint64_t warm_clr_bist         : 1;  /**< [  1:  1](R/W) Perform clear BIST during warm reset, instead of a full BIST. A warm/soft reset does not
                                                                 change this field. Note that a cold reset always performs a full BIST. */
        uint64_t cntl_clr_bist         : 1;  /**< [  2:  2](R/W) Perform clear BIST during control-only reset, instead of a full BIST. A warm/soft reset
                                                                 does not change this field. */
        uint64_t reserved_3_5          : 3;
        uint64_t bist_delay            : 58; /**< [ 63:  6](RO/H) Reserved. */
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_cfg_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t clr_bist              : 1;  /**< [  0:  0](R/W) Perform clear BIST on each chip domain reset, instead of a full BIST.
                                                                 Note that the first BIST during a cold domain reset is always a full BIST.
                                                                 This field is reinitialized with a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t clr_bist              : 1;  /**< [  0:  0](R/W) Perform clear BIST on each chip domain reset, instead of a full BIST.
                                                                 Note that the first BIST during a cold domain reset is always a full BIST.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_cfg bdk_rst_cfg_t;

#define BDK_RST_CFG BDK_RST_CFG_FUNC()
static inline uint64_t BDK_RST_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CFG_FUNC(void)
{
    return 0x87e006001610ll;
}

#define typedef_BDK_RST_CFG bdk_rst_cfg_t
#define bustype_BDK_RST_CFG BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CFG "RST_CFG"
#define device_bar_BDK_RST_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_CFG 0
#define arguments_BDK_RST_CFG -1,-1,-1,-1

/**
 * Register (RSL) rst_chip_domain_w1s
 *
 * RST Chip Domain Soft Pulse Reset Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_chip_domain_w1s
{
    uint64_t u;
    struct bdk_rst_chip_domain_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Software-initiated reset of entire chip domain.
                                                                 When set to one, places the entire chip into reset. At the completion
                                                                 of the reset the field is cleared.  This is similar to asserting and
                                                                 deasserting the CHIP_RESET_L pin.
                                                                 When performing a reset, set this bit and then read any register to
                                                                 confirm that chip is out of reset.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Software-initiated reset of entire chip domain.
                                                                 When set to one, places the entire chip into reset. At the completion
                                                                 of the reset the field is cleared.  This is similar to asserting and
                                                                 deasserting the CHIP_RESET_L pin.
                                                                 When performing a reset, set this bit and then read any register to
                                                                 confirm that chip is out of reset.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_chip_domain_w1s_s cn; */
};
typedef union bdk_rst_chip_domain_w1s bdk_rst_chip_domain_w1s_t;

#define BDK_RST_CHIP_DOMAIN_W1S BDK_RST_CHIP_DOMAIN_W1S_FUNC()
static inline uint64_t BDK_RST_CHIP_DOMAIN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CHIP_DOMAIN_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001810ll;
    __bdk_csr_fatal("RST_CHIP_DOMAIN_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_CHIP_DOMAIN_W1S bdk_rst_chip_domain_w1s_t
#define bustype_BDK_RST_CHIP_DOMAIN_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CHIP_DOMAIN_W1S "RST_CHIP_DOMAIN_W1S"
#define device_bar_BDK_RST_CHIP_DOMAIN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_CHIP_DOMAIN_W1S 0
#define arguments_BDK_RST_CHIP_DOMAIN_W1S -1,-1,-1,-1

/**
 * Register (RSL) rst_ckill
 *
 * RST Chipkill Timer Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_ckill
{
    uint64_t u;
    struct bdk_rst_ckill_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_47_63        : 17;
        uint64_t timer                 : 47; /**< [ 46:  0](R/W/H) Chipkill timer measured in coprocessor-clock cycles. Read requests return
                                                                 current chipkill timer. Write operations have no effect when RST_BOOT[CHIPKILL]
                                                                 = 1. */
#else /* Word 0 - Little Endian */
        uint64_t timer                 : 47; /**< [ 46:  0](R/W/H) Chipkill timer measured in coprocessor-clock cycles. Read requests return
                                                                 current chipkill timer. Write operations have no effect when RST_BOOT[CHIPKILL]
                                                                 = 1. */
        uint64_t reserved_47_63        : 17;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_ckill_s cn8; */
    struct bdk_rst_ckill_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_47_63        : 17;
        uint64_t timer                 : 47; /**< [ 46:  0](R/W/H) Chipkill timer measured in 100 MHz PLL reference clocks. Read
                                                                 requests return current chip kill timer. Write operations have
                                                                 no effect when RST_BOOT[CHIPKILL] is set.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t timer                 : 47; /**< [ 46:  0](R/W/H) Chipkill timer measured in 100 MHz PLL reference clocks. Read
                                                                 requests return current chip kill timer. Write operations have
                                                                 no effect when RST_BOOT[CHIPKILL] is set.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_47_63        : 17;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_ckill bdk_rst_ckill_t;

#define BDK_RST_CKILL BDK_RST_CKILL_FUNC()
static inline uint64_t BDK_RST_CKILL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CKILL_FUNC(void)
{
    return 0x87e006001638ll;
}

#define typedef_BDK_RST_CKILL bdk_rst_ckill_t
#define bustype_BDK_RST_CKILL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CKILL "RST_CKILL"
#define device_bar_BDK_RST_CKILL 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_CKILL 0
#define arguments_BDK_RST_CKILL -1,-1,-1,-1

/**
 * Register (RSL) rst_cold_data#
 *
 * RST Cold Reset Data Registers
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_cold_datax
{
    uint64_t u;
    struct bdk_rst_cold_datax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data registers preserved through warm reset. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data registers preserved through warm reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_cold_datax_s cn8; */
    struct bdk_rst_cold_datax_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data registers preserved through chip, core,
                                                                 MCP and SCP domain resets.
                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W) Scratch data registers preserved through chip, core,
                                                                 MCP and SCP domain resets.
                                                                 This field is always reinitialized on a cold domain reset. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_cold_datax bdk_rst_cold_datax_t;

static inline uint64_t BDK_RST_COLD_DATAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_COLD_DATAX(unsigned long a)
{
    if (a<=5)
        return 0x87e0060017c0ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("RST_COLD_DATAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_COLD_DATAX(a) bdk_rst_cold_datax_t
#define bustype_BDK_RST_COLD_DATAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RST_COLD_DATAX(a) "RST_COLD_DATAX"
#define device_bar_BDK_RST_COLD_DATAX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_COLD_DATAX(a) (a)
#define arguments_BDK_RST_COLD_DATAX(a) (a),-1,-1,-1

/**
 * Register (RSL) rst_cold_domain_w1s
 *
 * RST Cold Domain Pulse Reset Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_cold_domain_w1s
{
    uint64_t u;
    struct bdk_rst_cold_domain_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Software-initiated reset of entire chip emulating a cold domain reset.
                                                                 When set to one, places the entire chip into reset. At the completion
                                                                 of the reset the field is cleared.
                                                                 This action is similar to deasserting and asserting PLL_DCOK with the
                                                                 exception that external pins are not sampled again.
                                                                 When performing a reset, set this bit and
                                                                 then read any register to confirm that chip is out of reset.
                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Software-initiated reset of entire chip emulating a cold domain reset.
                                                                 When set to one, places the entire chip into reset. At the completion
                                                                 of the reset the field is cleared.
                                                                 This action is similar to deasserting and asserting PLL_DCOK with the
                                                                 exception that external pins are not sampled again.
                                                                 When performing a reset, set this bit and
                                                                 then read any register to confirm that chip is out of reset.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_cold_domain_w1s_s cn; */
};
typedef union bdk_rst_cold_domain_w1s bdk_rst_cold_domain_w1s_t;

#define BDK_RST_COLD_DOMAIN_W1S BDK_RST_COLD_DOMAIN_W1S_FUNC()
static inline uint64_t BDK_RST_COLD_DOMAIN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_COLD_DOMAIN_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001808ll;
    __bdk_csr_fatal("RST_COLD_DOMAIN_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_COLD_DOMAIN_W1S bdk_rst_cold_domain_w1s_t
#define bustype_BDK_RST_COLD_DOMAIN_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_RST_COLD_DOMAIN_W1S "RST_COLD_DOMAIN_W1S"
#define device_bar_BDK_RST_COLD_DOMAIN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_COLD_DOMAIN_W1S 0
#define arguments_BDK_RST_COLD_DOMAIN_W1S -1,-1,-1,-1

/**
 * Register (RSL) rst_const
 *
 * RST Constant Register
 * This register is accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_const
{
    uint64_t u;
    struct bdk_rst_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rst_devs              : 8;  /**< [ 15:  8](RO) Number of RST_DEV_E enumeration values supported, and size of RST_DEV_MAP(). */
        uint64_t pems                  : 8;  /**< [  7:  0](RO) Number of PEMs supported by RST, and size of RST_CTL(), RST_SOFT_PRST(). */
#else /* Word 0 - Little Endian */
        uint64_t pems                  : 8;  /**< [  7:  0](RO) Number of PEMs supported by RST, and size of RST_CTL(), RST_SOFT_PRST(). */
        uint64_t rst_devs              : 8;  /**< [ 15:  8](RO) Number of RST_DEV_E enumeration values supported, and size of RST_DEV_MAP(). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_const_s cn9; */
    /* struct bdk_rst_const_s cn96xxp1; */
    struct bdk_rst_const_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rst_devs              : 8;  /**< [ 15:  8](RO) Number of RST_DEV_E enumeration values supported, and size of RST_DEV_MAP(). */
        uint64_t pems                  : 8;  /**< [  7:  0](RO) Number of PEMs supported by RST. */
#else /* Word 0 - Little Endian */
        uint64_t pems                  : 8;  /**< [  7:  0](RO) Number of PEMs supported by RST. */
        uint64_t rst_devs              : 8;  /**< [ 15:  8](RO) Number of RST_DEV_E enumeration values supported, and size of RST_DEV_MAP(). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_const_cn96xxp3 cn98xx; */
    /* struct bdk_rst_const_s cnf95xx; */
    struct bdk_rst_const_loki
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rst_devs              : 8;  /**< [ 15:  8](RO) Number of RST_DEV_E enumeration values supported, and size of RST_DEV_MAP(). */
        uint64_t pems                  : 8;  /**< [  7:  0](RO) Number of PEMs supported by RST */
#else /* Word 0 - Little Endian */
        uint64_t pems                  : 8;  /**< [  7:  0](RO) Number of PEMs supported by RST */
        uint64_t rst_devs              : 8;  /**< [ 15:  8](RO) Number of RST_DEV_E enumeration values supported, and size of RST_DEV_MAP(). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } loki;
};
typedef union bdk_rst_const bdk_rst_const_t;

#define BDK_RST_CONST BDK_RST_CONST_FUNC()
static inline uint64_t BDK_RST_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CONST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e0060018f8ll;
    __bdk_csr_fatal("RST_CONST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_CONST bdk_rst_const_t
#define bustype_BDK_RST_CONST BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CONST "RST_CONST"
#define device_bar_BDK_RST_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_CONST 0
#define arguments_BDK_RST_CONST -1,-1,-1,-1

/**
 * Register (RSL) rst_core_domain_w1c
 *
 * RST Core Domain Soft Reset Clear Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_core_domain_w1c
{
    uint64_t u;
    struct bdk_rst_core_domain_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear software-initiated reset of AP cores, cache, NCB and associated logic.
                                                                 When set to one, the soft reset of the core is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual core domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[CORE] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[CORE] is set.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear software-initiated reset of AP cores, cache, NCB and associated logic.
                                                                 When set to one, the soft reset of the core is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual core domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[CORE] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[CORE] is set.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_core_domain_w1c_s cn; */
};
typedef union bdk_rst_core_domain_w1c bdk_rst_core_domain_w1c_t;

#define BDK_RST_CORE_DOMAIN_W1C BDK_RST_CORE_DOMAIN_W1C_FUNC()
static inline uint64_t BDK_RST_CORE_DOMAIN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CORE_DOMAIN_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001828ll;
    __bdk_csr_fatal("RST_CORE_DOMAIN_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_CORE_DOMAIN_W1C bdk_rst_core_domain_w1c_t
#define bustype_BDK_RST_CORE_DOMAIN_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CORE_DOMAIN_W1C "RST_CORE_DOMAIN_W1C"
#define device_bar_BDK_RST_CORE_DOMAIN_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_CORE_DOMAIN_W1C 0
#define arguments_BDK_RST_CORE_DOMAIN_W1C -1,-1,-1,-1

/**
 * Register (RSL) rst_core_domain_w1s
 *
 * RST Core Domain Soft Reset Set Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_core_domain_w1s
{
    uint64_t u;
    struct bdk_rst_core_domain_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Software-initiated reset of AP cores, cache, NCB and associated logic.
                                                                 When set to one, all logic associated with the core domain is placed in reset.
                                                                 Reads of this register show the soft reset state.  Not the actual core domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[CORE] shows
                                                                 the actual reset state.
                                                                 It is typically cleared by writing to RST_CORE_DOMAIN_W1C.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Software-initiated reset of AP cores, cache, NCB and associated logic.
                                                                 When set to one, all logic associated with the core domain is placed in reset.
                                                                 Reads of this register show the soft reset state.  Not the actual core domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[CORE] shows
                                                                 the actual reset state.
                                                                 It is typically cleared by writing to RST_CORE_DOMAIN_W1C.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_core_domain_w1s_s cn; */
};
typedef union bdk_rst_core_domain_w1s bdk_rst_core_domain_w1s_t;

#define BDK_RST_CORE_DOMAIN_W1S BDK_RST_CORE_DOMAIN_W1S_FUNC()
static inline uint64_t BDK_RST_CORE_DOMAIN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CORE_DOMAIN_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001820ll;
    __bdk_csr_fatal("RST_CORE_DOMAIN_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_CORE_DOMAIN_W1S bdk_rst_core_domain_w1s_t
#define bustype_BDK_RST_CORE_DOMAIN_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CORE_DOMAIN_W1S "RST_CORE_DOMAIN_W1S"
#define device_bar_BDK_RST_CORE_DOMAIN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_CORE_DOMAIN_W1S 0
#define arguments_BDK_RST_CORE_DOMAIN_W1S -1,-1,-1,-1

/**
 * Register (RSL) rst_core_pll
 *
 * RST Core Clock PLL Control Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_core_pll
{
    uint64_t u;
    struct bdk_rst_core_pll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Core clockout select.
                                                                   0x0 = Core clock divided by 32.
                                                                   0x1 = Core clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Core clockout reset. The core clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 cpt_clk/sclk/rclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) Core PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) Core PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Core clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CORE_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Core PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CORE_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Core clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CORE_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Core clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CORE_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Core PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CORE_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Core clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CORE_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) Core PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) Core PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 cpt_clk/sclk/rclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Core clockout reset. The core clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Core clockout select.
                                                                   0x0 = Core clock divided by 32.
                                                                   0x1 = Core clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_core_pll_s cn9; */
    /* struct bdk_rst_core_pll_s cn96xx; */
    struct bdk_rst_core_pll_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Core clockout select.
                                                                   0x0 = Core clock divided by 32.
                                                                   0x1 = Core clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Core clockout reset. The core clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) Core PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) Core PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Core clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CORE_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Core PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CORE_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Core clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CORE_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Core clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CORE_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Core PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CORE_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Core clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CORE_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) Core PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) Core PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Core clockout reset. The core clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Core clockout select.
                                                                   0x0 = Core clock divided by 32.
                                                                   0x1 = Core clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_rst_core_pll_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Core clockout select.
                                                                   0x0 = Core clock divided by 32.
                                                                   0x1 = Core clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Core clockout reset. The core clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 sclk/rclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) Core PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) Core PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Core clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CORE_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Core PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CORE_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Core clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CORE_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Core clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CORE_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Core PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CORE_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Core clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CORE_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) Core PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) Core PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 sclk/rclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Core clockout reset. The core clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Core clockout select.
                                                                   0x0 = Core clock divided by 32.
                                                                   0x1 = Core clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_rst_core_pll_cnf95xx loki; */
};
typedef union bdk_rst_core_pll bdk_rst_core_pll_t;

#define BDK_RST_CORE_PLL BDK_RST_CORE_PLL_FUNC()
static inline uint64_t BDK_RST_CORE_PLL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CORE_PLL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00a001780ll;
    __bdk_csr_fatal("RST_CORE_PLL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_CORE_PLL bdk_rst_core_pll_t
#define bustype_BDK_RST_CORE_PLL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CORE_PLL "RST_CORE_PLL"
#define device_bar_BDK_RST_CORE_PLL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_CORE_PLL 0
#define arguments_BDK_RST_CORE_PLL -1,-1,-1,-1

/**
 * Register (RSL) rst_cpt1_pll
 *
 * RST Crypto Clock1 PLL Control Register
 */
union bdk_rst_cpt1_pll
{
    uint64_t u;
    struct bdk_rst_cpt1_pll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Crypto clockout select.
                                                                   0x0 = Crypto clock divided by 32.
                                                                   0x1 = Crypto clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Crypto clockout reset. The crypto clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 The bit is typically used in conjunction with [NXT_PGM].
                                                                 When [DLY_SWITCH] is zero, [NXT_PGM] can be used to program the inactive
                                                                 PLL and that PLL will remain inactive.  When set to a nonzero value, the
                                                                 hardware will wait for any PLL programming to complete ([NXT_PGM]) and then
                                                                 switch to the inactive PLL after the specified number of PLL reference clocks.
                                                                 Hardware will add additional clocks if required.

                                                                 This field is always reinitialized to 0x0 on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional delay will also be added to wakeup powered down AP cores during
                                                                 a chip reset but that time is not reflected in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) CPT PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) CPT PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Crypto clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CPT_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Crypto PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CPT_MAX_MUL] and
                                                                 a minimum setting of 200 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Crypto clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CPT_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Crypto clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CPT_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Crypto PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CPT_MAX_MUL] and
                                                                 a minimum setting of 200 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Crypto clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CPT_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) CPT PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) CPT PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 The bit is typically used in conjunction with [NXT_PGM].
                                                                 When [DLY_SWITCH] is zero, [NXT_PGM] can be used to program the inactive
                                                                 PLL and that PLL will remain inactive.  When set to a nonzero value, the
                                                                 hardware will wait for any PLL programming to complete ([NXT_PGM]) and then
                                                                 switch to the inactive PLL after the specified number of PLL reference clocks.
                                                                 Hardware will add additional clocks if required.

                                                                 This field is always reinitialized to 0x0 on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional delay will also be added to wakeup powered down AP cores during
                                                                 a chip reset but that time is not reflected in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Crypto clockout reset. The crypto clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Crypto clockout select.
                                                                   0x0 = Crypto clock divided by 32.
                                                                   0x1 = Crypto clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_cpt1_pll_s cn; */
};
typedef union bdk_rst_cpt1_pll bdk_rst_cpt1_pll_t;

#define BDK_RST_CPT1_PLL BDK_RST_CPT1_PLL_FUNC()
static inline uint64_t BDK_RST_CPT1_PLL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CPT1_PLL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00a0017a0ll;
    __bdk_csr_fatal("RST_CPT1_PLL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_CPT1_PLL bdk_rst_cpt1_pll_t
#define bustype_BDK_RST_CPT1_PLL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CPT1_PLL "RST_CPT1_PLL"
#define device_bar_BDK_RST_CPT1_PLL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_CPT1_PLL 0
#define arguments_BDK_RST_CPT1_PLL -1,-1,-1,-1

/**
 * Register (RSL) rst_cpt_pll
 *
 * RST Crypto Clock PLL Control Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_cpt_pll
{
    uint64_t u;
    struct bdk_rst_cpt_pll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Crypto clockout select.
                                                                   0x0 = Crypto clock divided by 32.
                                                                   0x1 = Crypto clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Crypto clockout reset. The crypto clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 The bit is typically used in conjunction with [NXT_PGM].
                                                                 When [DLY_SWITCH] is zero, [NXT_PGM] can be used to program the inactive
                                                                 PLL and that PLL will remain inactive.  When set to a nonzero value, the
                                                                 hardware will wait for any PLL programming to complete ([NXT_PGM]) and then
                                                                 switch to the inactive PLL after the specified number of PLL reference clocks.
                                                                 Hardware will add additional clocks if required.

                                                                 This field is always reinitialized to 0x0 on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 cpt_clk/sclk/rclk notification to hardware.
                                                                 Additional delay will also be added to wakeup powered down AP cores during a
                                                                 chip reset but that time is not reflected in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) CPT PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) CPT PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Crypto clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CPT_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Crypto PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CPT_MAX_MUL] and
                                                                 a minimum setting of 200 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Crypto clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CPT_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Crypto clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CPT_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Crypto PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CPT_MAX_MUL] and
                                                                 a minimum setting of 200 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Crypto clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CPT_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) CPT PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) CPT PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 The bit is typically used in conjunction with [NXT_PGM].
                                                                 When [DLY_SWITCH] is zero, [NXT_PGM] can be used to program the inactive
                                                                 PLL and that PLL will remain inactive.  When set to a nonzero value, the
                                                                 hardware will wait for any PLL programming to complete ([NXT_PGM]) and then
                                                                 switch to the inactive PLL after the specified number of PLL reference clocks.
                                                                 Hardware will add additional clocks if required.

                                                                 This field is always reinitialized to 0x0 on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 cpt_clk/sclk/rclk notification to hardware.
                                                                 Additional delay will also be added to wakeup powered down AP cores during a
                                                                 chip reset but that time is not reflected in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Crypto clockout reset. The crypto clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Crypto clockout select.
                                                                   0x0 = Crypto clock divided by 32.
                                                                   0x1 = Crypto clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_cpt_pll_s cn9; */
    /* struct bdk_rst_cpt_pll_s cn96xx; */
    struct bdk_rst_cpt_pll_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Crypto clockout select.
                                                                   0x0 = Crypto clock divided by 32.
                                                                   0x1 = Crypto clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Crypto clockout reset. The crypto clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 The bit is typically used in conjunction with [NXT_PGM].
                                                                 When [DLY_SWITCH] is zero, [NXT_PGM] can be used to program the inactive
                                                                 PLL and that PLL will remain inactive.  When set to a nonzero value, the
                                                                 hardware will wait for any PLL programming to complete ([NXT_PGM]) and then
                                                                 switch to the inactive PLL after the specified number of PLL reference clocks.
                                                                 Hardware will add additional clocks if required.

                                                                 This field is always reinitialized to 0x0 on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional delay will also be added to wakeup powered down AP cores during
                                                                 a chip reset but that time is not reflected in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) CPT PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) CPT PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Crypto clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CPT_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Crypto PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CPT_MAX_MUL] and
                                                                 a minimum setting of 200 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Crypto clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CPT_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Crypto clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[CPT_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Crypto PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[CPT_MAX_MUL] and
                                                                 a minimum setting of 200 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Crypto clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[CPT_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) CPT PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) CPT PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 The bit is typically used in conjunction with [NXT_PGM].
                                                                 When [DLY_SWITCH] is zero, [NXT_PGM] can be used to program the inactive
                                                                 PLL and that PLL will remain inactive.  When set to a nonzero value, the
                                                                 hardware will wait for any PLL programming to complete ([NXT_PGM]) and then
                                                                 switch to the inactive PLL after the specified number of PLL reference clocks.
                                                                 Hardware will add additional clocks if required.

                                                                 This field is always reinitialized to 0x0 on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional delay will also be added to wakeup powered down AP cores during
                                                                 a chip reset but that time is not reflected in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Crypto clockout reset. The crypto clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Crypto clockout select.
                                                                   0x0 = Crypto clock divided by 32.
                                                                   0x1 = Crypto clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn98xx;
};
typedef union bdk_rst_cpt_pll bdk_rst_cpt_pll_t;

#define BDK_RST_CPT_PLL BDK_RST_CPT_PLL_FUNC()
static inline uint64_t BDK_RST_CPT_PLL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CPT_PLL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX))
        return 0x87e00a001778ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00a001778ll;
    __bdk_csr_fatal("RST_CPT_PLL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_CPT_PLL bdk_rst_cpt_pll_t
#define bustype_BDK_RST_CPT_PLL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CPT_PLL "RST_CPT_PLL"
#define device_bar_BDK_RST_CPT_PLL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_CPT_PLL 0
#define arguments_BDK_RST_CPT_PLL -1,-1,-1,-1

/**
 * Register (RSL) rst_ctl#
 *
 * RST Controllers Registers
 * This register is accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_ctlx
{
    uint64_t u;
    struct bdk_rst_ctlx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t reset_type            : 1;  /**< [ 13: 13](R/W) Type of reset generated internally by PCI MAC PF FLR, link down/hot reset, Powerdown  or
                                                                 PERST events. See [PF_FLR_CHIP], [RST_LINK], [RST_PWRDWN] and [RST_CHIP].

                                                                 0 = Chip and core domain reset. (A chip domain reset always also causes a core
                                                                 domain reset.)
                                                                 1 = Core domain reset.

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1. */
        uint64_t rst_pwrdwn            : 1;  /**< [ 12: 12](R/W) Powerdown event internal reset enable.
                                                                 0 = PEM going into powerdown (L2) does not cause an internal reset.
                                                                 1 = PEM going into powerdown (L2) causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a powerdown event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t prst_pwrdwn           : 1;  /**< [ 11: 11](R/W) PEM reset on power down.
                                                                 0 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for the
                                                                 corresponding controller, and (provided properly configured) the link should
                                                                 come back up automatically.
                                                                 1 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for
                                                                 the corresponding controller and set RST_SOFT_PRST()[SOFT_PRST]. This will
                                                                 hold the link in reset until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) Controls whether corresponding controller PF Function Level Reset causes a chip warm
                                                                 reset like CHIP_RESET_L. A warm/soft reset does not change this field.
                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A warm/soft reset does not change this field. On cold reset, this field is initialized to
                                                                 0. */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reset on link down. When set, a corresponding controller link-down reset or hot
                                                                 reset causes a warm chip reset.

                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 Note that a link-down or hot-reset event can never cause a warm chip reset when the
                                                                 controller is in reset (i.e. can never cause a warm reset when [RST_DONE] = 0). */
        uint64_t host_mode             : 1;  /**< [  6:  6](RO) For all controllers this field is set as host. */
        uint64_t reserved_4_5          : 2;
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven. A warm/soft reset does not change this field. On cold
                                                                 reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1.

                                                                 When set, CNXXXX drives the corresponding PERST*_L pin. Otherwise, CNXXXX does not drive
                                                                 the corresponding PERST*_L pin. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received. A warm/soft reset does
                                                                 not change this field. On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) warm reset the chip.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Controls whether PERST*_L causes a chip warm reset like CHIP_RESET_L. A warm/soft reset
                                                                 does not change this field. On cold reset, this field is initialized to 0.

                                                                 When [RST_RCV] = 0, [RST_CHIP] is ignored.

                                                                 When [RST_RCV] = 1, [RST_CHIP] = 1, and PERST*_L asserts, a chip warm reset is generated. */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.

                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
#else /* Word 0 - Little Endian */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.

                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Controls whether PERST*_L causes a chip warm reset like CHIP_RESET_L. A warm/soft reset
                                                                 does not change this field. On cold reset, this field is initialized to 0.

                                                                 When [RST_RCV] = 0, [RST_CHIP] is ignored.

                                                                 When [RST_RCV] = 1, [RST_CHIP] = 1, and PERST*_L asserts, a chip warm reset is generated. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received. A warm/soft reset does
                                                                 not change this field. On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) warm reset the chip.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored. */
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven. A warm/soft reset does not change this field. On cold
                                                                 reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1.

                                                                 When set, CNXXXX drives the corresponding PERST*_L pin. Otherwise, CNXXXX does not drive
                                                                 the corresponding PERST*_L pin. */
        uint64_t reserved_4_5          : 2;
        uint64_t host_mode             : 1;  /**< [  6:  6](RO) For all controllers this field is set as host. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reset on link down. When set, a corresponding controller link-down reset or hot
                                                                 reset causes a warm chip reset.

                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 Note that a link-down or hot-reset event can never cause a warm chip reset when the
                                                                 controller is in reset (i.e. can never cause a warm reset when [RST_DONE] = 0). */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A warm/soft reset does not change this field. On cold reset, this field is initialized to
                                                                 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) Controls whether corresponding controller PF Function Level Reset causes a chip warm
                                                                 reset like CHIP_RESET_L. A warm/soft reset does not change this field.
                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_pwrdwn           : 1;  /**< [ 11: 11](R/W) PEM reset on power down.
                                                                 0 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for the
                                                                 corresponding controller, and (provided properly configured) the link should
                                                                 come back up automatically.
                                                                 1 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for
                                                                 the corresponding controller and set RST_SOFT_PRST()[SOFT_PRST]. This will
                                                                 hold the link in reset until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t rst_pwrdwn            : 1;  /**< [ 12: 12](R/W) Powerdown event internal reset enable.
                                                                 0 = PEM going into powerdown (L2) does not cause an internal reset.
                                                                 1 = PEM going into powerdown (L2) causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a powerdown event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t reset_type            : 1;  /**< [ 13: 13](R/W) Type of reset generated internally by PCI MAC PF FLR, link down/hot reset, Powerdown  or
                                                                 PERST events. See [PF_FLR_CHIP], [RST_LINK], [RST_PWRDWN] and [RST_CHIP].

                                                                 0 = Chip and core domain reset. (A chip domain reset always also causes a core
                                                                 domain reset.)
                                                                 1 = Core domain reset.

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_ctlx_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) Controls whether corresponding controller PF Function Level Reset causes a chip warm
                                                                 reset like CHIP_RESET_L. A warm/soft reset does not change this field.
                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A warm/soft reset does not change this field. On cold reset, this field is initialized to
                                                                 0. */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reset on link down. When set, a corresponding controller link-down reset or hot
                                                                 reset causes a warm chip reset.

                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 Note that a link-down or hot-reset event can never cause a warm chip reset when the
                                                                 controller is in reset (i.e. can never cause a warm reset when [RST_DONE] = 0). */
        uint64_t host_mode             : 1;  /**< [  6:  6](RO) For all controllers this field is set as host. */
        uint64_t reserved_4_5          : 2;
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven. A warm/soft reset does not change this field. On cold
                                                                 reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1.

                                                                 When set, CNXXXX drives the corresponding PERST*_L pin. Otherwise, CNXXXX does not drive
                                                                 the corresponding PERST*_L pin. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received. A warm/soft reset does
                                                                 not change this field. On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) warm reset the chip.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Controls whether PERST*_L causes a chip warm reset like CHIP_RESET_L. A warm/soft reset
                                                                 does not change this field. On cold reset, this field is initialized to 0.

                                                                 When [RST_RCV] = 0, [RST_CHIP] is ignored.

                                                                 When [RST_RCV] = 1, [RST_CHIP] = 1, and PERST*_L asserts, a chip warm reset is generated. */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.

                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
#else /* Word 0 - Little Endian */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.

                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Controls whether PERST*_L causes a chip warm reset like CHIP_RESET_L. A warm/soft reset
                                                                 does not change this field. On cold reset, this field is initialized to 0.

                                                                 When [RST_RCV] = 0, [RST_CHIP] is ignored.

                                                                 When [RST_RCV] = 1, [RST_CHIP] = 1, and PERST*_L asserts, a chip warm reset is generated. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received. A warm/soft reset does
                                                                 not change this field. On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) warm reset the chip.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored. */
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven. A warm/soft reset does not change this field. On cold
                                                                 reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1.

                                                                 When set, CNXXXX drives the corresponding PERST*_L pin. Otherwise, CNXXXX does not drive
                                                                 the corresponding PERST*_L pin. */
        uint64_t reserved_4_5          : 2;
        uint64_t host_mode             : 1;  /**< [  6:  6](RO) For all controllers this field is set as host. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reset on link down. When set, a corresponding controller link-down reset or hot
                                                                 reset causes a warm chip reset.

                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 Note that a link-down or hot-reset event can never cause a warm chip reset when the
                                                                 controller is in reset (i.e. can never cause a warm reset when [RST_DONE] = 0). */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A warm/soft reset does not change this field. On cold reset, this field is initialized to
                                                                 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) Controls whether corresponding controller PF Function Level Reset causes a chip warm
                                                                 reset like CHIP_RESET_L. A warm/soft reset does not change this field.
                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_ctlx_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A warm/soft reset does not change this field. On cold reset, this field is initialized to
                                                                 0. */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reset on link down. When set, a corresponding controller link-down reset or hot
                                                                 reset causes a warm chip reset.

                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 Note that a link-down or hot-reset event can never cause a warm chip reset when the
                                                                 controller is in reset (i.e. can never cause a warm reset when [RST_DONE] = 0). */
        uint64_t host_mode             : 1;  /**< [  6:  6](RO) For all controllers this field is set as host. */
        uint64_t reserved_4_5          : 2;
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven. A warm/soft reset does not change this field. On cold
                                                                 reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1.

                                                                 When set, CNXXXX drives the corresponding PERST*_L pin. Otherwise, CNXXXX does not drive
                                                                 the corresponding PERST*_L pin. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received. A warm/soft reset does
                                                                 not change this field. On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) warm reset the chip.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Controls whether PERST*_L causes a chip warm reset like CHIP_RESET_L. A warm/soft reset
                                                                 does not change this field. On cold reset, this field is initialized to 0.

                                                                 When [RST_RCV] = 0, [RST_CHIP] is ignored.

                                                                 When [RST_RCV] = 1, [RST_CHIP] = 1, and PERST*_L asserts, a chip warm reset is generated. */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.

                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
#else /* Word 0 - Little Endian */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.

                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Controls whether PERST*_L causes a chip warm reset like CHIP_RESET_L. A warm/soft reset
                                                                 does not change this field. On cold reset, this field is initialized to 0.

                                                                 When [RST_RCV] = 0, [RST_CHIP] is ignored.

                                                                 When [RST_RCV] = 1, [RST_CHIP] = 1, and PERST*_L asserts, a chip warm reset is generated. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received. A warm/soft reset does
                                                                 not change this field. On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) warm reset the chip.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored. */
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven. A warm/soft reset does not change this field. On cold
                                                                 reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1.

                                                                 When set, CNXXXX drives the corresponding PERST*_L pin. Otherwise, CNXXXX does not drive
                                                                 the corresponding PERST*_L pin. */
        uint64_t reserved_4_5          : 2;
        uint64_t host_mode             : 1;  /**< [  6:  6](RO) For all controllers this field is set as host. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reset on link down. When set, a corresponding controller link-down reset or hot
                                                                 reset causes a warm chip reset.

                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 Note that a link-down or hot-reset event can never cause a warm chip reset when the
                                                                 controller is in reset (i.e. can never cause a warm reset when [RST_DONE] = 0). */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A warm/soft reset does not change this field. On cold reset, this field is initialized to
                                                                 0. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } cn81xx;
    struct bdk_rst_ctlx_cn83xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) Controls whether corresponding controller PF Function Level Reset causes a chip warm
                                                                 reset like CHIP_RESET_L. A warm/soft reset does not change this field.
                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A warm/soft reset does not change this field. On cold reset, this field is initialized to
                                                                 0. */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reset on link down. When set, a corresponding controller link-down reset or hot
                                                                 reset causes a warm chip reset.

                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 Note that a link-down or hot-reset event can never cause a warm chip reset when the
                                                                 controller is in reset (i.e. can never cause a warm reset when [RST_DONE] = 0). */
        uint64_t host_mode             : 1;  /**< [  6:  6](RO) Read-only access to the corresponding PEM()_CFG[HOSTMD] field indicating PEMn is root
                                                                 complex (host). For controllers 0 and 2  the initial value is determined by straps. For
                                                                 controllers 1 and 3 this field is initially set as host. */
        uint64_t reserved_4_5          : 2;
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven. A warm/soft reset does not change this field. On cold
                                                                 reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1.

                                                                 When set, CNXXXX drives the corresponding PERST*_L pin. Otherwise, CNXXXX does not drive
                                                                 the corresponding PERST*_L pin. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received. A warm/soft reset does
                                                                 not change this field. On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) warm reset the chip.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Controls whether PERST*_L causes a chip warm reset like CHIP_RESET_L. A warm/soft reset
                                                                 does not change this field. On cold reset, this field is initialized to 0.

                                                                 When [RST_RCV] = 0, [RST_CHIP] is ignored.

                                                                 When [RST_RCV] = 1, [RST_CHIP] = 1, and PERST*_L asserts, a chip warm reset is generated. */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.

                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
#else /* Word 0 - Little Endian */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.

                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Controls whether PERST*_L causes a chip warm reset like CHIP_RESET_L. A warm/soft reset
                                                                 does not change this field. On cold reset, this field is initialized to 0.

                                                                 When [RST_RCV] = 0, [RST_CHIP] is ignored.

                                                                 When [RST_RCV] = 1, [RST_CHIP] = 1, and PERST*_L asserts, a chip warm reset is generated. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received. A warm/soft reset does
                                                                 not change this field. On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) warm reset the chip.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored. */
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven. A warm/soft reset does not change this field. On cold
                                                                 reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1.

                                                                 When set, CNXXXX drives the corresponding PERST*_L pin. Otherwise, CNXXXX does not drive
                                                                 the corresponding PERST*_L pin. */
        uint64_t reserved_4_5          : 2;
        uint64_t host_mode             : 1;  /**< [  6:  6](RO) Read-only access to the corresponding PEM()_CFG[HOSTMD] field indicating PEMn is root
                                                                 complex (host). For controllers 0 and 2  the initial value is determined by straps. For
                                                                 controllers 1 and 3 this field is initially set as host. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reset on link down. When set, a corresponding controller link-down reset or hot
                                                                 reset causes a warm chip reset.

                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0.

                                                                 Note that a link-down or hot-reset event can never cause a warm chip reset when the
                                                                 controller is in reset (i.e. can never cause a warm reset when [RST_DONE] = 0). */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A warm/soft reset does not change this field. On cold reset, this field is initialized to
                                                                 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) Controls whether corresponding controller PF Function Level Reset causes a chip warm
                                                                 reset like CHIP_RESET_L. A warm/soft reset does not change this field.
                                                                 On cold reset, this field is initialized as follows:

                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.

                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn83xx;
    struct bdk_rst_ctlx_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t reset_type            : 1;  /**< [ 13: 13](R/W) Type of reset generated internally by PCI MAC PF FLR, link down/hot reset, Powerdown  or
                                                                 PERST events. See [PF_FLR_CHIP], [RST_LINK], [RST_PWRDWN] and [RST_CHIP].

                                                                 0 = Chip and core domain reset. (A chip domain reset always also causes a core
                                                                 domain reset.)
                                                                 1 = Core domain reset.

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1. */
        uint64_t rst_pwrdwn            : 1;  /**< [ 12: 12](R/W) Powerdown event internal reset enable.
                                                                 0 = PEM going into powerdown (L2) does not cause an internal reset.
                                                                 1 = PEM going into powerdown (L2) causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a powerdown event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t prst_pwrdwn           : 1;  /**< [ 11: 11](R/W) PEM reset on power down.
                                                                 0 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for the
                                                                 corresponding controller, and (provided properly configured) the link should
                                                                 come back up automatically.
                                                                 1 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for
                                                                 the corresponding controller and set RST_SOFT_PRST()[SOFT_PRST]. This will
                                                                 hold the link in reset until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) PF FLR internal reset enable.
                                                                 0 = PF FLR events will not cause an internal reset.
                                                                 1 = A PF FLR event received by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Link down / hot reset event internal reset enable.
                                                                 0 = Link down or hot reset do not cause an internal reset.
                                                                 1 = A link-down or hot-reset event on the PCIe interface causes the internal
                                                                 reset specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a link-down or hot reset event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t host_mode             : 1;  /**< [  6:  6](RO/H) Read-only access to the corresponding PEM()_CFG[HOSTMD] field
                                                                 indicating PEMn is root complex (host). */
        uint64_t reserved_4_5          : 2;
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is cleared.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is set.

                                                                 This bit must not be changed in the same write that sets [RST_RCV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) cause a domain reset.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored.

                                                                 This bit must not be changed in the same write that sets [RST_DRV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other.
                                                                 If this bit is written while PERSTx_L pin is de-asserted then the MAC can come
                                                                 out of reset unexpectedly. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) PERST internal reset enable. When set along with [RST_RCV],
                                                                 logic will generate an internal reset specified by [RESET_TYPE]
                                                                 when the corresponding PERST*_L pin is asserted.  When cleared or
                                                                 when [RST_RCV] is cleared, the PERST*_L does not cause an internal reset.

                                                                 If this bit is written while PERSTx_L pin is asserted and [RST_RCV]=1 then an
                                                                 internal reset can occur unexpectedly.

                                                                 During a cold domain reset this field is initialized to zero. */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.
                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
#else /* Word 0 - Little Endian */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.
                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) PERST internal reset enable. When set along with [RST_RCV],
                                                                 logic will generate an internal reset specified by [RESET_TYPE]
                                                                 when the corresponding PERST*_L pin is asserted.  When cleared or
                                                                 when [RST_RCV] is cleared, the PERST*_L does not cause an internal reset.

                                                                 If this bit is written while PERSTx_L pin is asserted and [RST_RCV]=1 then an
                                                                 internal reset can occur unexpectedly.

                                                                 During a cold domain reset this field is initialized to zero. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) cause a domain reset.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored.

                                                                 This bit must not be changed in the same write that sets [RST_DRV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other.
                                                                 If this bit is written while PERSTx_L pin is de-asserted then the MAC can come
                                                                 out of reset unexpectedly. */
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is cleared.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is set.

                                                                 This bit must not be changed in the same write that sets [RST_RCV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other. */
        uint64_t reserved_4_5          : 2;
        uint64_t host_mode             : 1;  /**< [  6:  6](RO/H) Read-only access to the corresponding PEM()_CFG[HOSTMD] field
                                                                 indicating PEMn is root complex (host). */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Link down / hot reset event internal reset enable.
                                                                 0 = Link down or hot reset do not cause an internal reset.
                                                                 1 = A link-down or hot-reset event on the PCIe interface causes the internal
                                                                 reset specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a link-down or hot reset event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down or hot-reset will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and set RST_SOFT_PRST()[SOFT_PRST]. This will hold the link in reset
                                                                 until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) PF FLR internal reset enable.
                                                                 0 = PF FLR events will not cause an internal reset.
                                                                 1 = A PF FLR event received by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_pwrdwn           : 1;  /**< [ 11: 11](R/W) PEM reset on power down.
                                                                 0 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for the
                                                                 corresponding controller, and (provided properly configured) the link should
                                                                 come back up automatically.
                                                                 1 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for
                                                                 the corresponding controller and set RST_SOFT_PRST()[SOFT_PRST]. This will
                                                                 hold the link in reset until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t rst_pwrdwn            : 1;  /**< [ 12: 12](R/W) Powerdown event internal reset enable.
                                                                 0 = PEM going into powerdown (L2) does not cause an internal reset.
                                                                 1 = PEM going into powerdown (L2) causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a powerdown event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t reset_type            : 1;  /**< [ 13: 13](R/W) Type of reset generated internally by PCI MAC PF FLR, link down/hot reset, Powerdown  or
                                                                 PERST events. See [PF_FLR_CHIP], [RST_LINK], [RST_PWRDWN] and [RST_CHIP].

                                                                 0 = Chip and core domain reset. (A chip domain reset always also causes a core
                                                                 domain reset.)
                                                                 1 = Core domain reset.

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } cn9;
    /* struct bdk_rst_ctlx_cn9 cn96xx; */
    struct bdk_rst_ctlx_cnf95xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t reset_type            : 1;  /**< [ 13: 13](R/W) Type of reset generated internally by PCI MAC PF FLR, link down/hot reset, Powerdown  or
                                                                 PERST events. See [PF_FLR_CHIP], [RST_LINK], [RST_PWRDWN] and [RST_CHIP].

                                                                 0 = Chip and core domain reset. (A chip domain reset always also causes a core
                                                                 domain reset.)
                                                                 1 = Core domain reset.

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1. */
        uint64_t rst_pwrdwn            : 1;  /**< [ 12: 12](R/W) Powerdown event internal reset enable.
                                                                 0 = PEM going into powerdown (L2) does not cause an internal reset.
                                                                 1 = PEM going into powerdown (L2) causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a powerdown event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t prst_pwrdwn           : 1;  /**< [ 11: 11](R/W) PEM reset on power down.
                                                                 0 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for the
                                                                 corresponding controller, and (provided properly configured) the link should
                                                                 come back up automatically.
                                                                 1 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for
                                                                 the corresponding controller and set RST_SOFT_PRST()[SOFT_PRST]. This will
                                                                 hold the link in reset until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) PF FLR internal reset enable.
                                                                 0 = PF FLR events will not cause an internal reset.
                                                                 1 = A PF FLR event received by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down event will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down event detected by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Link down / hot reset event internal reset enable.
                                                                 0 = Link down or hot reset do not cause an internal reset.
                                                                 1 = A link-down or hot-reset event on the PCIe interface causes the internal
                                                                 reset specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a link-down or hot reset event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t host_mode             : 1;  /**< [  6:  6](RO/H) Read-only access to the corresponding PEM()_CFG[HOSTMD] field
                                                                 indicating PEMn is root complex (host). */
        uint64_t reserved_4_5          : 2;
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is cleared.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is set.

                                                                 This bit must not be changed in the same write that sets [RST_RCV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) cause a domain reset.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored.

                                                                 This bit must not be changed in the same write that sets [RST_DRV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other.
                                                                 If this bit is written while PERSTx_L pin is de-asserted then the MAC can come
                                                                 out of reset unexpectedly. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) PERST internal reset enable. When set along with [RST_RCV],
                                                                 logic will generate an internal reset specified by [RESET_TYPE]
                                                                 when the corresponding PERST*_L pin is asserted.  When cleared or
                                                                 when [RST_RCV] is cleared, the PERST*_L does not cause an internal reset.

                                                                 If this bit is written while PERSTx_L pin is asserted and [RST_RCV]=1 then an
                                                                 internal reset can occur unexpectedly.

                                                                 During a cold domain reset this field is initialized to zero. */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.
                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
#else /* Word 0 - Little Endian */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.
                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) PERST internal reset enable. When set along with [RST_RCV],
                                                                 logic will generate an internal reset specified by [RESET_TYPE]
                                                                 when the corresponding PERST*_L pin is asserted.  When cleared or
                                                                 when [RST_RCV] is cleared, the PERST*_L does not cause an internal reset.

                                                                 If this bit is written while PERSTx_L pin is asserted and [RST_RCV]=1 then an
                                                                 internal reset can occur unexpectedly.

                                                                 During a cold domain reset this field is initialized to zero. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reset received. Controls whether PERST*_L is received.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) cause a domain reset.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored.

                                                                 This bit must not be changed in the same write that sets [RST_DRV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other.
                                                                 If this bit is written while PERSTx_L pin is de-asserted then the MAC can come
                                                                 out of reset unexpectedly. */
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Controls whether PERST*_L is driven.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is cleared.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is set.

                                                                 This bit must not be changed in the same write that sets [RST_RCV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other. */
        uint64_t reserved_4_5          : 2;
        uint64_t host_mode             : 1;  /**< [  6:  6](RO/H) Read-only access to the corresponding PEM()_CFG[HOSTMD] field
                                                                 indicating PEMn is root complex (host). */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Link down / hot reset event internal reset enable.
                                                                 0 = Link down or hot reset do not cause an internal reset.
                                                                 1 = A link-down or hot-reset event on the PCIe interface causes the internal
                                                                 reset specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a link-down or hot reset event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) PEM reset on link down.
                                                                 0 = Link-down event will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down event detected by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) PF FLR internal reset enable.
                                                                 0 = PF FLR events will not cause an internal reset.
                                                                 1 = A PF FLR event received by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_pwrdwn           : 1;  /**< [ 11: 11](R/W) PEM reset on power down.
                                                                 0 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for the
                                                                 corresponding controller, and (provided properly configured) the link should
                                                                 come back up automatically.
                                                                 1 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for
                                                                 the corresponding controller and set RST_SOFT_PRST()[SOFT_PRST]. This will
                                                                 hold the link in reset until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t rst_pwrdwn            : 1;  /**< [ 12: 12](R/W) Powerdown event internal reset enable.
                                                                 0 = PEM going into powerdown (L2) does not cause an internal reset.
                                                                 1 = PEM going into powerdown (L2) causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a powerdown event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t reset_type            : 1;  /**< [ 13: 13](R/W) Type of reset generated internally by PCI MAC PF FLR, link down/hot reset, Powerdown  or
                                                                 PERST events. See [PF_FLR_CHIP], [RST_LINK], [RST_PWRDWN] and [RST_CHIP].

                                                                 0 = Chip and core domain reset. (A chip domain reset always also causes a core
                                                                 domain reset.)
                                                                 1 = Core domain reset.

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } cnf95xxp1;
    struct bdk_rst_ctlx_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_14_63        : 50;
        uint64_t reset_type            : 1;  /**< [ 13: 13](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Type of reset generated internally by PCI MAC PF FLR, link down/hot reset, Powerdown  or
                                                                 PERST events. See [PF_FLR_CHIP], [RST_LINK], [RST_PWRDWN] and [RST_CHIP].

                                                                 0 = Chip and core domain reset. (A chip domain reset always also causes a core
                                                                 domain reset.)
                                                                 1 = Core domain reset.

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1. */
        uint64_t rst_pwrdwn            : 1;  /**< [ 12: 12](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Powerdown event internal reset enable.
                                                                 0 = PEM going into powerdown (L2) does not cause an internal reset.
                                                                 1 = PEM going into powerdown (L2) causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a powerdown event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t prst_pwrdwn           : 1;  /**< [ 11: 11](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 PEM reset on power down.
                                                                 0 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for the
                                                                 corresponding controller, and (provided properly configured) the link should
                                                                 come back up automatically.
                                                                 1 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for
                                                                 the corresponding controller and set RST_SOFT_PRST()[SOFT_PRST]. This will
                                                                 hold the link in reset until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 PF FLR internal reset enable.
                                                                 0 = PF FLR events will not cause an internal reset.
                                                                 1 = A PF FLR event received by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 PEM reset on link down.
                                                                 0 = Link-down event will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down event detected by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Link down / hot reset event internal reset enable.
                                                                 0 = Link down or hot reset do not cause an internal reset.
                                                                 1 = A link-down or hot-reset event on the PCIe interface causes the internal
                                                                 reset specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a link-down or hot reset event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t host_mode             : 1;  /**< [  6:  6](RO/H) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Read-only access to the corresponding PEM()_CFG[HOSTMD] field
                                                                 indicating PEMn is root complex (host). */
        uint64_t reserved_4_5          : 2;
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Controls whether PERST*_L is driven.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is cleared.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is set.

                                                                 This bit must not be changed in the same write that sets [RST_RCV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Reset received. Controls whether PERST*_L is received.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) cause a domain reset.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored.

                                                                 This bit must not be changed in the same write that sets [RST_DRV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other.
                                                                 If this bit is written while PERSTx_L pin is de-asserted then the MAC can come
                                                                 out of reset unexpectedly. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 PERST internal reset enable. When set along with [RST_RCV],
                                                                 logic will generate an internal reset specified by [RESET_TYPE]
                                                                 when the corresponding PERST*_L pin is asserted.  When cleared or
                                                                 when [RST_RCV] is cleared, the PERST*_L does not cause an internal reset.

                                                                 If this bit is written while PERSTx_L pin is asserted and [RST_RCV]=1 then an
                                                                 internal reset can occur unexpectedly.

                                                                 During a cold domain reset this field is initialized to zero. */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.
                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
#else /* Word 0 - Little Endian */
        uint64_t rst_val               : 1;  /**< [  0:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Read-only access to PERST*_L. Unpredictable when [RST_RCV] = 0.

                                                                 Reads as 1 when [RST_RCV] = 1 and the PERST*_L pin is asserted.
                                                                 Reads as 0 when [RST_RCV] = 1 and the PERST*_L pin is not asserted. */
        uint64_t rst_chip              : 1;  /**< [  1:  1](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 PERST internal reset enable. When set along with [RST_RCV],
                                                                 logic will generate an internal reset specified by [RESET_TYPE]
                                                                 when the corresponding PERST*_L pin is asserted.  When cleared or
                                                                 when [RST_RCV] is cleared, the PERST*_L does not cause an internal reset.

                                                                 If this bit is written while PERSTx_L pin is asserted and [RST_RCV]=1 then an
                                                                 internal reset can occur unexpectedly.

                                                                 During a cold domain reset this field is initialized to zero. */
        uint64_t rst_rcv               : 1;  /**< [  2:  2](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Reset received. Controls whether PERST*_L is received.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 When [RST_RCV] = 1, the PERST*_L value is received and can be used to reset the
                                                                 controller and (optionally, based on [RST_CHIP]) cause a domain reset.

                                                                 When [RST_RCV] = 1 (and [RST_CHIP] = 0), RST_INT[PERST*] gets set when the PERST*_L
                                                                 pin asserts. (This interrupt can alert software whenever the external reset pin initiates
                                                                 a controller reset sequence.)

                                                                 [RST_VAL] gives the PERST*_L pin value when [RST_RCV] = 1.

                                                                 When [RST_RCV] = 0, the PERST*_L pin value is ignored.

                                                                 This bit must not be changed in the same write that sets [RST_DRV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other.
                                                                 If this bit is written while PERSTx_L pin is de-asserted then the MAC can come
                                                                 out of reset unexpectedly. */
        uint64_t rst_drv               : 1;  /**< [  3:  3](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Controls whether PERST*_L is driven.
                                                                 This field is always reinitialized on a cold domain reset.
                                                                 The field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is cleared.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is set.

                                                                 This bit must not be changed in the same write that sets [RST_RCV]=1; separate
                                                                 writes to RST_CTL() are required to clear one bit and then set the other. */
        uint64_t reserved_4_5          : 2;
        uint64_t host_mode             : 1;  /**< [  6:  6](RO/H) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Read-only access to the corresponding PEM()_CFG[HOSTMD] field
                                                                 indicating PEMn is root complex (host). */
        uint64_t rst_link              : 1;  /**< [  7:  7](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Link down / hot reset event internal reset enable.
                                                                 0 = Link down or hot reset do not cause an internal reset.
                                                                 1 = A link-down or hot-reset event on the PCIe interface causes the internal
                                                                 reset specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a link-down or hot reset event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t rst_done              : 1;  /**< [  8:  8](RO/H) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Reset done. Indicates the controller reset status. [RST_DONE] is always 0
                                                                 (i.e. the controller is held in reset) when
                                                                 * RST_SOFT_PRST()[SOFT_PRST] = 1, or
                                                                 * [RST_RCV] = 1 and PERST*_L pin is asserted. */
        uint64_t prst_link             : 1;  /**< [  9:  9](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 PEM reset on link down.
                                                                 0 = Link-down event will set RST_INT[RST_LINK] for the corresponding
                                                                 controller, and (provided properly configured) the link should come back up
                                                                 automatically.
                                                                 1 = Link-down event detected by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t pf_flr_chip           : 1;  /**< [ 10: 10](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 PF FLR internal reset enable.
                                                                 0 = PF FLR events will not cause an internal reset.
                                                                 1 = A PF FLR event received by the PCIe logic causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 1.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 0. */
        uint64_t prst_pwrdwn           : 1;  /**< [ 11: 11](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 PEM reset on power down.
                                                                 0 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for the
                                                                 corresponding controller, and (provided properly configured) the link should
                                                                 come back up automatically.
                                                                 1 = PEM entering L2/P2 power state will set RST_INT[RST_PWRDWN] for
                                                                 the corresponding controller and set RST_SOFT_PRST()[SOFT_PRST]. This will
                                                                 hold the link in reset until software clears RST_SOFT_PRST()[SOFT_PRST].

                                                                 A core/chip reset does not change this field. On cold reset, this field is
                                                                 initialized to 0. */
        uint64_t rst_pwrdwn            : 1;  /**< [ 12: 12](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Powerdown event internal reset enable.
                                                                 0 = PEM going into powerdown (L2) does not cause an internal reset.
                                                                 1 = PEM going into powerdown (L2) causes the internal reset
                                                                 specified by [RESET_TYPE].

                                                                 On a cold reset, the field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] is set.
                                                                 _ 1 when RST_CTL()[HOST_MODE] is cleared.

                                                                 Note that a powerdown event can never cause a domain reset when the
                                                                 controller is already in reset (i.e. when [RST_DONE] = 0). */
        uint64_t reset_type            : 1;  /**< [ 13: 13](R/W) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Type of reset generated internally by PCI MAC PF FLR, link down/hot reset, Powerdown  or
                                                                 PERST events. See [PF_FLR_CHIP], [RST_LINK], [RST_PWRDWN] and [RST_CHIP].

                                                                 0 = Chip and core domain reset. (A chip domain reset always also causes a core
                                                                 domain reset.)
                                                                 1 = Core domain reset.

                                                                 On cold reset, this field is initialized as follows:
                                                                 _ 0 when RST_CTL()[HOST_MODE] = 0.
                                                                 _ 1 when RST_CTL()[HOST_MODE] = 1. */
        uint64_t reserved_14_63        : 50;
#endif /* Word 0 - End */
    } cnf95xxp2;
};
typedef union bdk_rst_ctlx bdk_rst_ctlx_t;

static inline uint64_t BDK_RST_CTLX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_CTLX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=2))
        return 0x87e006001640ll + 8ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e006001640ll + 8ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=3))
        return 0x87e006001640ll + 8ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e006001640ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("RST_CTLX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_CTLX(a) bdk_rst_ctlx_t
#define bustype_BDK_RST_CTLX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RST_CTLX(a) "RST_CTLX"
#define device_bar_BDK_RST_CTLX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_CTLX(a) (a)
#define arguments_BDK_RST_CTLX(a) (a),-1,-1,-1

/**
 * Register (RSL) rst_dbg_reset
 *
 * INTERNAL: RST Debug Logic Reset Register
 *
 * This register contains the reset control for each core's debug logic.
 * Debug reset is not supported.
 */
union bdk_rst_dbg_reset
{
    uint64_t u;
    struct bdk_rst_dbg_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t rst                   : 24; /**< [ 23:  0](R/W) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 24; /**< [ 23:  0](R/W) Reserved. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_dbg_reset_s cn8; */
    struct bdk_rst_dbg_reset_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t rst                   : 4;  /**< [  3:  0](R/W) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 4;  /**< [  3:  0](R/W) Reserved. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_dbg_reset_s cn83xx; */
};
typedef union bdk_rst_dbg_reset bdk_rst_dbg_reset_t;

#define BDK_RST_DBG_RESET BDK_RST_DBG_RESET_FUNC()
static inline uint64_t BDK_RST_DBG_RESET_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_DBG_RESET_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x87e006001750ll;
    __bdk_csr_fatal("RST_DBG_RESET", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_DBG_RESET bdk_rst_dbg_reset_t
#define bustype_BDK_RST_DBG_RESET BDK_CSR_TYPE_RSL
#define basename_BDK_RST_DBG_RESET "RST_DBG_RESET"
#define device_bar_BDK_RST_DBG_RESET 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_DBG_RESET 0
#define arguments_BDK_RST_DBG_RESET -1,-1,-1,-1

/**
 * Register (RSL) rst_debug
 *
 * RST Debug Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_debug
{
    uint64_t u;
    struct bdk_rst_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t suspend_rstpwr        : 1;  /**< [  5:  5](R/W) Stop RSTPWR bus.
                                                                 Setting this field will stop AP resets from getting to the cores.
                                                                 Clearing this field will restart communication starting with AP0.
                                                                 This allows test sequences to predict AP resets with much greater accuracy.
                                                                 For diagnostic and test use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t div_clk_rst           : 1;  /**< [  4:  4](R/W) Forces Clock Divider Reset.
                                                                 Setting this field will force fixed clock dividers into reset.
                                                                 Clearing this field will enable clock dividers.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Currently only used in BPHY on f95n */
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on. For diagnostic use only. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t div_clk_rst           : 1;  /**< [  4:  4](R/W) Forces Clock Divider Reset.
                                                                 Setting this field will force fixed clock dividers into reset.
                                                                 Clearing this field will enable clock dividers.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Currently only used in BPHY on f95n */
        uint64_t suspend_rstpwr        : 1;  /**< [  5:  5](R/W) Stop RSTPWR bus.
                                                                 Setting this field will stop AP resets from getting to the cores.
                                                                 Clearing this field will restart communication starting with AP0.
                                                                 This allows test sequences to predict AP resets with much greater accuracy.
                                                                 For diagnostic and test use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_debug_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on. For diagnostic use only. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_debug_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t suspend_rstpwr        : 1;  /**< [  5:  5](R/W) Stop RSTPWR bus.
                                                                 Setting this field will stop AP resets from getting to the cores.
                                                                 Clearing this field will restart communication starting with AP0.
                                                                 This allows test sequences to predict AP resets with much greater accuracy.
                                                                 For diagnostic and test use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t div_clk_rst           : 1;  /**< [  4:  4](R/W) Forces Clock Divider Reset.
                                                                 Setting this field will force fixed clock dividers into reset.
                                                                 Clearing this field will enable clock dividers.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Currently only used in BPHY on f95n */
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t div_clk_rst           : 1;  /**< [  4:  4](R/W) Forces Clock Divider Reset.
                                                                 Setting this field will force fixed clock dividers into reset.
                                                                 Clearing this field will enable clock dividers.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Currently only used in BPHY on f95n */
        uint64_t suspend_rstpwr        : 1;  /**< [  5:  5](R/W) Stop RSTPWR bus.
                                                                 Setting this field will stop AP resets from getting to the cores.
                                                                 Clearing this field will restart communication starting with AP0.
                                                                 This allows test sequences to predict AP resets with much greater accuracy.
                                                                 For diagnostic and test use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_debug_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_rst_debug_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t suspend_rstpwr        : 1;  /**< [  5:  5](R/W) Stop RSTPWR bus.
                                                                 Setting this field will stop AP resets from getting to the cores.
                                                                 Clearing this field will restart communication starting with AP0.
                                                                 This allows test sequences to predict AP resets with much greater accuracy.
                                                                 For diagnostic and test use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_4            : 1;
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_4            : 1;
        uint64_t suspend_rstpwr        : 1;  /**< [  5:  5](R/W) Stop RSTPWR bus.
                                                                 Setting this field will stop AP resets from getting to the cores.
                                                                 Clearing this field will restart communication starting with AP0.
                                                                 This allows test sequences to predict AP resets with much greater accuracy.
                                                                 For diagnostic and test use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_debug_cn96xxp3 cn98xx; */
    /* struct bdk_rst_debug_cn96xxp1 cnf95xx; */
    struct bdk_rst_debug_loki
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t suspend_rstpwr        : 1;  /**< [  5:  5](R/W) Stop RSTPWR bus.
                                                                 Setting this field will stop AP resets from getting to the cores.
                                                                 Clearing this field will restart communication starting with AP0.
                                                                 This will allow test sequences to predict AP resets with much greater accuracy.
                                                                 For diagnostic and test use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t div_clk_rst           : 1;  /**< [  4:  4](R/W) Forces Clock Divider Reset.
                                                                 Setting this field will force fixed clock dividers into reset.
                                                                 Clearing this field will enable clock dividers.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Currently only used in BPHY on f95n */
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force conditional clock used for interrupt logic to always be on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t clk_cng               : 1;  /**< [  1:  1](R/W) Force clock-changing indicator on.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Forces store-n-forward across clock domains. */
        uint64_t clkena_on             : 1;  /**< [  2:  2](R/W) Force global clock enable on.
                                                                 Setting this field will force all clocks on while they are in reset and
                                                                 will dramatically increase power consumption.
                                                                 For diagnostic use only.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dll_csr_wakeup        : 1;  /**< [  3:  3](R/W) Forces DLL setting to unlock.
                                                                 Setting this field will force all DLLs to track clock changes.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t div_clk_rst           : 1;  /**< [  4:  4](R/W) Forces Clock Divider Reset.
                                                                 Setting this field will force fixed clock dividers into reset.
                                                                 Clearing this field will enable clock dividers.
                                                                 For diagnostic use only.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Currently only used in BPHY on f95n */
        uint64_t suspend_rstpwr        : 1;  /**< [  5:  5](R/W) Stop RSTPWR bus.
                                                                 Setting this field will stop AP resets from getting to the cores.
                                                                 Clearing this field will restart communication starting with AP0.
                                                                 This will allow test sequences to predict AP resets with much greater accuracy.
                                                                 For diagnostic and test use only.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } loki;
};
typedef union bdk_rst_debug bdk_rst_debug_t;

#define BDK_RST_DEBUG BDK_RST_DEBUG_FUNC()
static inline uint64_t BDK_RST_DEBUG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_DEBUG_FUNC(void)
{
    return 0x87e0060017b0ll;
}

#define typedef_BDK_RST_DEBUG bdk_rst_debug_t
#define bustype_BDK_RST_DEBUG BDK_CSR_TYPE_RSL
#define basename_BDK_RST_DEBUG "RST_DEBUG"
#define device_bar_BDK_RST_DEBUG 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_DEBUG 0
#define arguments_BDK_RST_DEBUG -1,-1,-1,-1

/**
 * Register (RSL) rst_delay
 *
 * RST Delay Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_delay
{
    uint64_t u;
    struct bdk_rst_delay_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t warm_rst_dly          : 16; /**< [ 31: 16](R/W) Warm reset delay. A warm reset immediately causes an early warm-reset notification, but
                                                                 the assertion of warm reset is delayed this many coprocessor-clock cycles. A warm/soft
                                                                 reset does not change this field.
                                                                 This must be at least 0x200 coprocessor-clock cycles. */
        uint64_t reserved_0_15         : 16;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_15         : 16;
        uint64_t warm_rst_dly          : 16; /**< [ 31: 16](R/W) Warm reset delay. A warm reset immediately causes an early warm-reset notification, but
                                                                 the assertion of warm reset is delayed this many coprocessor-clock cycles. A warm/soft
                                                                 reset does not change this field.
                                                                 This must be at least 0x200 coprocessor-clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_delay_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t warm_rst_dly          : 16; /**< [ 31: 16](R/W) Warm reset delay. A warm reset immediately causes an early warm-reset notification, but
                                                                 the assertion of warm reset is delayed this many coprocessor-clock cycles. A warm/soft
                                                                 reset does not change this field.
                                                                 This must be at least 0x200 coprocessor-clock cycles. */
        uint64_t soft_rst_dly          : 16; /**< [ 15:  0](R/W) Soft reset delay. A soft reset immediately causes an early soft-reset notification, but
                                                                 the assertion of soft reset is delayed this many coprocessor-clock cycles. A warm/soft
                                                                 reset does not change this field.
                                                                 This must be at least 0x200 coprocessor-clock cycles. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst_dly          : 16; /**< [ 15:  0](R/W) Soft reset delay. A soft reset immediately causes an early soft-reset notification, but
                                                                 the assertion of soft reset is delayed this many coprocessor-clock cycles. A warm/soft
                                                                 reset does not change this field.
                                                                 This must be at least 0x200 coprocessor-clock cycles. */
        uint64_t warm_rst_dly          : 16; /**< [ 31: 16](R/W) Warm reset delay. A warm reset immediately causes an early warm-reset notification, but
                                                                 the assertion of warm reset is delayed this many coprocessor-clock cycles. A warm/soft
                                                                 reset does not change this field.
                                                                 This must be at least 0x200 coprocessor-clock cycles. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_delay_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rst_dly               : 16; /**< [ 15:  0](R/W) Reset delay. Chip and core domain resets immediately causes an early reset
                                                                 notification to the DDR interface.  The assertion of the domain reset is delayed
                                                                 by this many 100 MHz PLL reference clocks. The minimum value is 1 uS.
                                                                 Typical value is 4 uS once DDR has been initialized.
                                                                 This field is reinitialized with a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst_dly               : 16; /**< [ 15:  0](R/W) Reset delay. Chip and core domain resets immediately causes an early reset
                                                                 notification to the DDR interface.  The assertion of the domain reset is delayed
                                                                 by this many 100 MHz PLL reference clocks. The minimum value is 1 uS.
                                                                 Typical value is 4 uS once DDR has been initialized.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } cn9;
    /* struct bdk_rst_delay_cn9 cn96xxp1; */
    struct bdk_rst_delay_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t rst_dly               : 16; /**< [ 15:  0](R/W) Reset delay. Chip and core domain resets immediately causes an early reset
                                                                 notification to the DDR interface.  The assertion of the domain reset is delayed
                                                                 by this many 100 MHz PLL reference clocks. The minimum value is 1 uS.
                                                                 Typical value is 5 uS once core domain has been brought out of reset.
                                                                 This field is reinitialized with a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst_dly               : 16; /**< [ 15:  0](R/W) Reset delay. Chip and core domain resets immediately causes an early reset
                                                                 notification to the DDR interface.  The assertion of the domain reset is delayed
                                                                 by this many 100 MHz PLL reference clocks. The minimum value is 1 uS.
                                                                 Typical value is 5 uS once core domain has been brought out of reset.
                                                                 This field is reinitialized with a cold domain reset. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_delay_cn96xxp3 cn98xx; */
    /* struct bdk_rst_delay_cn96xxp3 cnf95xx; */
    /* struct bdk_rst_delay_cn96xxp3 loki; */
};
typedef union bdk_rst_delay bdk_rst_delay_t;

#define BDK_RST_DELAY BDK_RST_DELAY_FUNC()
static inline uint64_t BDK_RST_DELAY_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_DELAY_FUNC(void)
{
    return 0x87e006001608ll;
}

#define typedef_BDK_RST_DELAY bdk_rst_delay_t
#define bustype_BDK_RST_DELAY BDK_CSR_TYPE_RSL
#define basename_BDK_RST_DELAY "RST_DELAY"
#define device_bar_BDK_RST_DELAY 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_DELAY 0
#define arguments_BDK_RST_DELAY -1,-1,-1,-1

/**
 * Register (RSL) rst_dev_map#
 *
 * RST Device Map Register
 * This register configures the reset domain of devices. Index {a} is enumerated by RST_DEV_E.
 * Writes to these registers should only occur when all the bits of RST_BIST_ACTIVE are clear.
 * See RST_BIST_ACTIVE for details.
 * Only one RST_DEV_MAP() should be written at a time.
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_dev_mapx
{
    uint64_t u;
    struct bdk_rst_dev_mapx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t dmn                   : 3;  /**< [  2:  0](R/W) Map of programmable devices to reset domains. When the specified domain reset
                                                                 occurs the corresponding device will reset. Devices are numbered according to
                                                                 RST_DEV_E.

                                                                 GSERs should be mapped to the same domain as the PEM, CGX or NCSI device they are
                                                                 associated with.

                                                                 If any PCIEx_EP_STRAP is set then all RST_DEV_MAP(GSERx) are mapped to chip reset.

                                                                 See RST_DOMAIN_E for field encodings.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 RST_DEV_MAP()[DMN] resets to core domain for everything except AVS, EMM, MPI\<1:0\>
                                                                 and NCSI which reset to SCP domain, and GSER which are set to chip in EP mode.

                                                                 This is based on cold reset so software could e.g. choose to put a PEM GSER into
                                                                 endpoint based on knowledge outside the straps (that RST uses to reset this
                                                                 table). */
#else /* Word 0 - Little Endian */
        uint64_t dmn                   : 3;  /**< [  2:  0](R/W) Map of programmable devices to reset domains. When the specified domain reset
                                                                 occurs the corresponding device will reset. Devices are numbered according to
                                                                 RST_DEV_E.

                                                                 GSERs should be mapped to the same domain as the PEM, CGX or NCSI device they are
                                                                 associated with.

                                                                 If any PCIEx_EP_STRAP is set then all RST_DEV_MAP(GSERx) are mapped to chip reset.

                                                                 See RST_DOMAIN_E for field encodings.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 RST_DEV_MAP()[DMN] resets to core domain for everything except AVS, EMM, MPI\<1:0\>
                                                                 and NCSI which reset to SCP domain, and GSER which are set to chip in EP mode.

                                                                 This is based on cold reset so software could e.g. choose to put a PEM GSER into
                                                                 endpoint based on knowledge outside the straps (that RST uses to reset this
                                                                 table). */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_dev_mapx_s cn; */
};
typedef union bdk_rst_dev_mapx bdk_rst_dev_mapx_t;

static inline uint64_t BDK_RST_DEV_MAPX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_DEV_MAPX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=47))
        return 0x87e00a001a00ll + 8ll * ((a) & 0x3f);
    __bdk_csr_fatal("RST_DEV_MAPX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_DEV_MAPX(a) bdk_rst_dev_mapx_t
#define bustype_BDK_RST_DEV_MAPX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RST_DEV_MAPX(a) "RST_DEV_MAPX"
#define device_bar_BDK_RST_DEV_MAPX(a) 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_DEV_MAPX(a) (a)
#define arguments_BDK_RST_DEV_MAPX(a) (a),-1,-1,-1

/**
 * Register (RSL) rst_dsp_pll
 *
 * RST DSP Clock PLL Control Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_dsp_pll
{
    uint64_t u;
    struct bdk_rst_dsp_pll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) DSP clockout select.
                                                                   0x0 = DSP clock divided by 32.
                                                                   0x1 = DSP clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) DSP clockout reset. The dsp clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occured.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 bclk/dsp_clk/sclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) DSP PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) DSP PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) DSP clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[DSP_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) DSP PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[DSP_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) DSP clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[DSP_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) DSP clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[DSP_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) DSP PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[DSP_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) DSP clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[DSP_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) DSP PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) DSP PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 bclk/dsp_clk/sclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occured.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) DSP clockout reset. The dsp clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) DSP clockout select.
                                                                   0x0 = DSP clock divided by 32.
                                                                   0x1 = DSP clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_dsp_pll_s cn9; */
    /* struct bdk_rst_dsp_pll_s cnf95xxp1; */
    struct bdk_rst_dsp_pll_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) DSP clockout select.
                                                                   0x0 = DSP clock divided by 32.
                                                                   0x1 = DSP clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) DSP clockout reset. The DSP clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occured.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 bclk/dsp_clk/sclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) DSP PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) DSP PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) DSP clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[DSP_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) DSP PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[DSP_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) DSP clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[DSP_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) DSP clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[DSP_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) DSP PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[DSP_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) DSP clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[DSP_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) DSP PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) DSP PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 bclk/dsp_clk/sclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occured.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) DSP clockout reset. The DSP clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) DSP clockout select.
                                                                   0x0 = DSP clock divided by 32.
                                                                   0x1 = DSP clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cnf95xxp2;
    /* struct bdk_rst_dsp_pll_cnf95xxp2 loki; */
};
typedef union bdk_rst_dsp_pll bdk_rst_dsp_pll_t;

#define BDK_RST_DSP_PLL BDK_RST_DSP_PLL_FUNC()
static inline uint64_t BDK_RST_DSP_PLL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_DSP_PLL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CNF95XX))
        return 0x87e00a001770ll;
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e00a001770ll;
    __bdk_csr_fatal("RST_DSP_PLL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_DSP_PLL bdk_rst_dsp_pll_t
#define bustype_BDK_RST_DSP_PLL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_DSP_PLL "RST_DSP_PLL"
#define device_bar_BDK_RST_DSP_PLL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_DSP_PLL 0
#define arguments_BDK_RST_DSP_PLL -1,-1,-1,-1

/**
 * Register (RSL) rst_eco
 *
 * INTERNAL: RST ECO Register
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_eco
{
    uint64_t u;
    struct bdk_rst_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_eco_s cn8; */
    struct bdk_rst_eco_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops.
                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_eco bdk_rst_eco_t;

#define BDK_RST_ECO BDK_RST_ECO_FUNC()
static inline uint64_t BDK_RST_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_ECO_FUNC(void)
{
    return 0x87e0060017b8ll;
}

#define typedef_BDK_RST_ECO bdk_rst_eco_t
#define bustype_BDK_RST_ECO BDK_CSR_TYPE_RSL
#define basename_BDK_RST_ECO "RST_ECO"
#define device_bar_BDK_RST_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_ECO 0
#define arguments_BDK_RST_ECO -1,-1,-1,-1

/**
 * Register (RSL) rst_gclk_pll
 *
 * RST GSERR Clock PLL Control Register
 * This register should only be programmed while GSERR logic is in reset.
 * It is accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_gclk_pll
{
    uint64_t u;
    struct bdk_rst_gclk_pll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Programs the active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when PLL has been updated.  Software should wait at least 20uS
                                                                 for clock frequency to be reached before releasing GSERRs from reset.
                                                                 This field is always reinitialized on a chip domain reset.

                                                                 Changing GCLK frequency is for diagnostic use only; changes can only be made
                                                                 while all GSERR are in reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) GSERR PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value must be in the range between 200 MHz and 600 MHz.
                                                                 Value will be 400 MHz immediately after a cold domain reset. */
        uint64_t reserved_7            : 1;
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) GSERR clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [NXT_PGM] has been set or 400 MHz
                                                                 immediately after a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) GSERR clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [NXT_PGM] has been set or 400 MHz
                                                                 immediately after a cold domain reset. */
        uint64_t reserved_7            : 1;
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) GSERR PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value must be in the range between 200 MHz and 600 MHz.
                                                                 Value will be 400 MHz immediately after a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Programs the active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when PLL has been updated.  Software should wait at least 20uS
                                                                 for clock frequency to be reached before releasing GSERRs from reset.
                                                                 This field is always reinitialized on a chip domain reset.

                                                                 Changing GCLK frequency is for diagnostic use only; changes can only be made
                                                                 while all GSERR are in reset. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_gclk_pll_s cn9; */
    /* struct bdk_rst_gclk_pll_s cn96xx; */
    /* struct bdk_rst_gclk_pll_s cn98xx; */
    /* struct bdk_rst_gclk_pll_s cnf95xx; */
    struct bdk_rst_gclk_pll_loki
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Programs the active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when PLL has been updated.  Software should wait at least 20uS
                                                                 for clock frequency to be reached before releasing RFIFs from reset.
                                                                 This field is always reinitialized on a chip domain reset.

                                                                 Changing GSERR Clock frequency is for diagnostic use only; changes can only be made
                                                                 while GSERR logic is in reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) GSERR PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value must be in the range between 200 MHz and 600 MHz.
                                                                 Value will be 400 MHz immediately after a cold domain reset. */
        uint64_t reserved_7            : 1;
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) GSERR clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [NXT_PGM] has been set or 400 MHz
                                                                 immediately after a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) GSERR clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [NXT_PGM] has been set or 400 MHz
                                                                 immediately after a cold domain reset. */
        uint64_t reserved_7            : 1;
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) GSERR PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value must be in the range between 200 MHz and 600 MHz.
                                                                 Value will be 400 MHz immediately after a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Programs the active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when PLL has been updated.  Software should wait at least 20uS
                                                                 for clock frequency to be reached before releasing RFIFs from reset.
                                                                 This field is always reinitialized on a chip domain reset.

                                                                 Changing GSERR Clock frequency is for diagnostic use only; changes can only be made
                                                                 while GSERR logic is in reset. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } loki;
};
typedef union bdk_rst_gclk_pll bdk_rst_gclk_pll_t;

#define BDK_RST_GCLK_PLL BDK_RST_GCLK_PLL_FUNC()
static inline uint64_t BDK_RST_GCLK_PLL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_GCLK_PLL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X))
        return 0x87e00a0017f8ll;
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00a0017f8ll;
    if (bdk_is_model(OCTEONTX_CNF95XX_PASS2_X))
        return 0x87e00a0017f8ll;
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e00a0017f8ll;
    __bdk_csr_fatal("RST_GCLK_PLL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_GCLK_PLL bdk_rst_gclk_pll_t
#define bustype_BDK_RST_GCLK_PLL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_GCLK_PLL "RST_GCLK_PLL"
#define device_bar_BDK_RST_GCLK_PLL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_GCLK_PLL 0
#define arguments_BDK_RST_GCLK_PLL -1,-1,-1,-1

/**
 * Register (RSL) rst_int
 *
 * RST Interrupt Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_int
{
    uint64_t u;
    struct bdk_rst_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) BPHY domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) A controller power down (PEM in L2 state) occurred while RST_CTL()[RST_PWRDWN] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_4_31         : 28;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller. */
        uint64_t reserved_4_31         : 28;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) A controller power down (PEM in L2 state) occurred while RST_CTL()[RST_PWRDWN] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) BPHY domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_int_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t perst                 : 4;  /**< [ 11:  8](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller. */
        uint64_t reserved_4_7          : 4;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller. */
        uint64_t reserved_4_7          : 4;
        uint64_t perst                 : 4;  /**< [ 11:  8](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_int_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t perst                 : 3;  /**< [ 10:  8](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller. */
        uint64_t reserved_3_7          : 5;
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller. */
        uint64_t reserved_3_7          : 5;
        uint64_t perst                 : 3;  /**< [ 10:  8](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_int_cn8 cn83xx; */
    struct bdk_rst_int_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) BPHY domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) A controller power down (PEM in L2 state) occurred while RST_CTL()[RST_PWRDWN] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_20_31        : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_4_15         : 12;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_4_15         : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_20_31        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) A controller power down (PEM in L2 state) occurred while RST_CTL()[RST_PWRDWN] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) BPHY domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_int_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) A controller power down (PEM in L2 state) occurred while RST_CTL()[RST_PWRDWN] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_20_31        : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_4_15         : 12;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_4_15         : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_20_31        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) A controller power down (PEM in L2 state) occurred while RST_CTL()[RST_PWRDWN] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_rst_int_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_int_cn96xxp3 cn98xx; */
    struct bdk_rst_int_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) BPHY domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_33_47        : 15;
        uint64_t rst_pwrdwn            : 1;  /**< [ 32: 32](R/W1C/H) A controller power down (PEM in L2 state) occurred while RST_CTL()[RST_PWRDWN] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_17_31        : 15;
        uint64_t perst                 : 1;  /**< [ 16: 16](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_1_15         : 15;
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W1C/H) A controller link-down/hot-reset occurred while RST_CTL()[RST_LINK] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_1_15         : 15;
        uint64_t perst                 : 1;  /**< [ 16: 16](R/W1C/H) PERST*_L asserted while RST_CTL()[RST_RCV] = 1 and RST_CTL()[RST_CHIP] = 0. One bit
                                                                 corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_17_31        : 15;
        uint64_t rst_pwrdwn            : 1;  /**< [ 32: 32](R/W1C/H) A controller power down (PEM in L2 state) occurred while RST_CTL()[RST_PWRDWN] = 0. Software must
                                                                 assert then deassert RST_SOFT_PRST()[SOFT_PRST]. One bit corresponds to each controller.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_33_47        : 15;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) BPHY domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cnf95xx;
    struct bdk_rst_int_loki
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) BPHY domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Core domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) MCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) SCP domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) BPHY domain entered reset.
                                                                 This field is reinitialized with a chip domain reset. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } loki;
};
typedef union bdk_rst_int bdk_rst_int_t;

#define BDK_RST_INT BDK_RST_INT_FUNC()
static inline uint64_t BDK_RST_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_INT_FUNC(void)
{
    return 0x87e006001628ll;
}

#define typedef_BDK_RST_INT bdk_rst_int_t
#define bustype_BDK_RST_INT BDK_CSR_TYPE_RSL
#define basename_BDK_RST_INT "RST_INT"
#define device_bar_BDK_RST_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_INT 0
#define arguments_BDK_RST_INT -1,-1,-1,-1

/**
 * Register (RSL) rst_int_ena_w1c
 *
 * RST Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_rst_int_ena_w1c
{
    uint64_t u;
    struct bdk_rst_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) Reads or clears enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_4_31         : 28;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
        uint64_t reserved_4_31         : 28;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) Reads or clears enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_int_ena_w1c_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t perst                 : 4;  /**< [ 11:  8](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_4_7          : 4;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
        uint64_t reserved_4_7          : 4;
        uint64_t perst                 : 4;  /**< [ 11:  8](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_int_ena_w1c_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t perst                 : 3;  /**< [ 10:  8](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_3_7          : 5;
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
        uint64_t reserved_3_7          : 5;
        uint64_t perst                 : 3;  /**< [ 10:  8](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_int_ena_w1c_cn8 cn83xx; */
    struct bdk_rst_int_ena_w1c_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) Reads or clears enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_20_31        : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_4_15         : 12;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
        uint64_t reserved_4_15         : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_20_31        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) Reads or clears enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_int_ena_w1c_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) Reads or clears enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_20_31        : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_4_15         : 12;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
        uint64_t reserved_4_15         : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_20_31        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1C/H) Reads or clears enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_rst_int_ena_w1c_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_int_ena_w1c_cn96xxp3 cn98xx; */
    struct bdk_rst_int_ena_w1c_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_33_47        : 15;
        uint64_t rst_pwrdwn            : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_17_31        : 15;
        uint64_t perst                 : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_1_15         : 15;
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for RST_INT[RST_LINK]. */
        uint64_t reserved_1_15         : 15;
        uint64_t perst                 : 1;  /**< [ 16: 16](R/W1C/H) Reads or clears enable for RST_INT[PERST]. */
        uint64_t reserved_17_31        : 15;
        uint64_t rst_pwrdwn            : 1;  /**< [ 32: 32](R/W1C/H) Reads or clears enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_33_47        : 15;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cnf95xx;
    struct bdk_rst_int_ena_w1c_loki
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1C/H) Reads or clears enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1C/H) Reads or clears enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1C/H) Reads or clears enable for RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1C/H) Reads or clears enable for RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } loki;
};
typedef union bdk_rst_int_ena_w1c bdk_rst_int_ena_w1c_t;

#define BDK_RST_INT_ENA_W1C BDK_RST_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_RST_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_INT_ENA_W1C_FUNC(void)
{
    return 0x87e0060016a8ll;
}

#define typedef_BDK_RST_INT_ENA_W1C bdk_rst_int_ena_w1c_t
#define bustype_BDK_RST_INT_ENA_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_RST_INT_ENA_W1C "RST_INT_ENA_W1C"
#define device_bar_BDK_RST_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_INT_ENA_W1C 0
#define arguments_BDK_RST_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RSL) rst_int_ena_w1s
 *
 * RST Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_rst_int_ena_w1s
{
    uint64_t u;
    struct bdk_rst_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_4_31         : 28;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
        uint64_t reserved_4_31         : 28;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_int_ena_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t perst                 : 4;  /**< [ 11:  8](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_4_7          : 4;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
        uint64_t reserved_4_7          : 4;
        uint64_t perst                 : 4;  /**< [ 11:  8](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_int_ena_w1s_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t perst                 : 3;  /**< [ 10:  8](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_3_7          : 5;
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
        uint64_t reserved_3_7          : 5;
        uint64_t perst                 : 3;  /**< [ 10:  8](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_int_ena_w1s_cn8 cn83xx; */
    struct bdk_rst_int_ena_w1s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_20_31        : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_4_15         : 12;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
        uint64_t reserved_4_15         : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_20_31        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_int_ena_w1s_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_20_31        : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_4_15         : 12;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
        uint64_t reserved_4_15         : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_20_31        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_rst_int_ena_w1s_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_int_ena_w1s_cn96xxp3 cn98xx; */
    struct bdk_rst_int_ena_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_33_47        : 15;
        uint64_t rst_pwrdwn            : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_17_31        : 15;
        uint64_t perst                 : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_1_15         : 15;
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for RST_INT[RST_LINK]. */
        uint64_t reserved_1_15         : 15;
        uint64_t perst                 : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets enable for RST_INT[PERST]. */
        uint64_t reserved_17_31        : 15;
        uint64_t rst_pwrdwn            : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets enable for RST_INT[RST_PWRDWN]. */
        uint64_t reserved_33_47        : 15;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cnf95xx;
    struct bdk_rst_int_ena_w1s_loki
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets enable for RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets enable for RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets enable for RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets enable for RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } loki;
};
typedef union bdk_rst_int_ena_w1s bdk_rst_int_ena_w1s_t;

#define BDK_RST_INT_ENA_W1S BDK_RST_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_RST_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_INT_ENA_W1S_FUNC(void)
{
    return 0x87e0060016a0ll;
}

#define typedef_BDK_RST_INT_ENA_W1S bdk_rst_int_ena_w1s_t
#define bustype_BDK_RST_INT_ENA_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_RST_INT_ENA_W1S "RST_INT_ENA_W1S"
#define device_bar_BDK_RST_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_INT_ENA_W1S 0
#define arguments_BDK_RST_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RSL) rst_int_w1s
 *
 * RST Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_rst_int_w1s
{
    uint64_t u;
    struct bdk_rst_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets RST_INT[RST_PWRDWN]. */
        uint64_t reserved_4_31         : 28;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
        uint64_t reserved_4_31         : 28;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets RST_INT[RST_PWRDWN]. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_int_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_12_63        : 52;
        uint64_t perst                 : 4;  /**< [ 11:  8](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_4_7          : 4;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
        uint64_t reserved_4_7          : 4;
        uint64_t perst                 : 4;  /**< [ 11:  8](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_12_63        : 52;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_int_w1s_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t perst                 : 3;  /**< [ 10:  8](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_3_7          : 5;
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
        uint64_t reserved_3_7          : 5;
        uint64_t perst                 : 3;  /**< [ 10:  8](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_int_w1s_cn8 cn83xx; */
    struct bdk_rst_int_w1s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets RST_INT[RST_PWRDWN]. */
        uint64_t reserved_20_31        : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_4_15         : 12;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
        uint64_t reserved_4_15         : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_20_31        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets RST_INT[RST_PWRDWN]. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_int_w1s_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t reserved_36_47        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets RST_INT[RST_PWRDWN]. */
        uint64_t reserved_20_31        : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_4_15         : 12;
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 4;  /**< [  3:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
        uint64_t reserved_4_15         : 12;
        uint64_t perst                 : 4;  /**< [ 19: 16](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_20_31        : 12;
        uint64_t rst_pwrdwn            : 4;  /**< [ 35: 32](R/W1S/H) Reads or sets RST_INT[RST_PWRDWN]. */
        uint64_t reserved_36_47        : 12;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_rst_int_w1s_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_int_w1s_cn96xxp3 cn98xx; */
    struct bdk_rst_int_w1s_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t reserved_33_47        : 15;
        uint64_t rst_pwrdwn            : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets RST_INT[RST_PWRDWN]. */
        uint64_t reserved_17_31        : 15;
        uint64_t perst                 : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_1_15         : 15;
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets RST_INT[RST_LINK]. */
        uint64_t reserved_1_15         : 15;
        uint64_t perst                 : 1;  /**< [ 16: 16](R/W1S/H) Reads or sets RST_INT[PERST]. */
        uint64_t reserved_17_31        : 15;
        uint64_t rst_pwrdwn            : 1;  /**< [ 32: 32](R/W1S/H) Reads or sets RST_INT[RST_PWRDWN]. */
        uint64_t reserved_33_47        : 15;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } cnf95xx;
    struct bdk_rst_int_w1s_loki
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets RST_INT[BPHY_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t reserved_0_47         : 48;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_47         : 48;
        uint64_t core_reset            : 1;  /**< [ 48: 48](R/W1S/H) Reads or sets RST_INT[CORE_RESET]. */
        uint64_t mcp_reset             : 1;  /**< [ 49: 49](R/W1S/H) Reads or sets RST_INT[MCP_RESET]. */
        uint64_t scp_reset             : 1;  /**< [ 50: 50](R/W1S/H) Reads or sets RST_INT[SCP_RESET]. */
        uint64_t bphy_reset            : 1;  /**< [ 51: 51](R/W1S/H) Reads or sets RST_INT[BPHY_RESET]. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } loki;
};
typedef union bdk_rst_int_w1s bdk_rst_int_w1s_t;

#define BDK_RST_INT_W1S BDK_RST_INT_W1S_FUNC()
static inline uint64_t BDK_RST_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_INT_W1S_FUNC(void)
{
    return 0x87e006001630ll;
}

#define typedef_BDK_RST_INT_W1S bdk_rst_int_w1s_t
#define bustype_BDK_RST_INT_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_RST_INT_W1S "RST_INT_W1S"
#define device_bar_BDK_RST_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_INT_W1S 0
#define arguments_BDK_RST_INT_W1S -1,-1,-1,-1

/**
 * Register (RSL) rst_lboot
 *
 * RST Last Boot Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_lboot
{
    uint64_t u;
    struct bdk_rst_lboot_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t lboot                 : 50; /**< [ 49:  0](R/W1C/H) Bit vector of last reset cause(es).  The value reset with a
                                                                 cold domain reset.
                                                                 Bit numbers are enumerated by RST_SOURCE_E. */
#else /* Word 0 - Little Endian */
        uint64_t lboot                 : 50; /**< [ 49:  0](R/W1C/H) Bit vector of last reset cause(es).  The value reset with a
                                                                 cold domain reset.
                                                                 Bit numbers are enumerated by RST_SOURCE_E. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_lboot_s cn9; */
    struct bdk_rst_lboot_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t lboot                 : 48; /**< [ 47:  0](R/W1C/H) Bit vector of last reset cause(es).  The value reset with a
                                                                 cold domain reset.
                                                                 Bit numbers are enumerated by RST_SOURCE_E. */
#else /* Word 0 - Little Endian */
        uint64_t lboot                 : 48; /**< [ 47:  0](R/W1C/H) Bit vector of last reset cause(es).  The value reset with a
                                                                 cold domain reset.
                                                                 Bit numbers are enumerated by RST_SOURCE_E. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_rst_lboot_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t lboot                 : 48; /**< [ 47:  0](R/W1C/H) Bit vector of last reset cause(es).
                                                                 Bit numbers are enumerated by RST_SOURCE_E.
                                                                 Unused bits always read as zero.

                                                                 The value reset with a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t lboot                 : 48; /**< [ 47:  0](R/W1C/H) Bit vector of last reset cause(es).
                                                                 Bit numbers are enumerated by RST_SOURCE_E.
                                                                 Unused bits always read as zero.

                                                                 The value reset with a cold domain reset. */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } cn96xxp3;
    struct bdk_rst_lboot_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t lboot                 : 32; /**< [ 31:  0](R/W1C/H) Bit vector of last reset cause(es).  The value reset with a
                                                                 cold domain reset.
                                                                 Bit numbers are enumerated by RST_SOURCE_E. */
#else /* Word 0 - Little Endian */
        uint64_t lboot                 : 32; /**< [ 31:  0](R/W1C/H) Bit vector of last reset cause(es).  The value reset with a
                                                                 cold domain reset.
                                                                 Bit numbers are enumerated by RST_SOURCE_E. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_rst_lboot_s cnf95xx; */
    /* struct bdk_rst_lboot_s loki; */
};
typedef union bdk_rst_lboot bdk_rst_lboot_t;

#define BDK_RST_LBOOT BDK_RST_LBOOT_FUNC()
static inline uint64_t BDK_RST_LBOOT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_LBOOT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001620ll;
    __bdk_csr_fatal("RST_LBOOT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_LBOOT bdk_rst_lboot_t
#define bustype_BDK_RST_LBOOT BDK_CSR_TYPE_RSL
#define basename_BDK_RST_LBOOT "RST_LBOOT"
#define device_bar_BDK_RST_LBOOT 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_LBOOT 0
#define arguments_BDK_RST_LBOOT -1,-1,-1,-1

/**
 * Register (RSL) rst_mcp_domain_w1c
 *
 * RST MCP Domain Soft Reset Clear Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_mcp_domain_w1c
{
    uint64_t u;
    struct bdk_rst_mcp_domain_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear software-initiated reset of the MCP processor and associated logic.
                                                                 When set to one, the soft reset of the MCP is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual MCP domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[MCP] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[MCP] is set.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear software-initiated reset of the MCP processor and associated logic.
                                                                 When set to one, the soft reset of the MCP is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual MCP domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[MCP] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[MCP] is set.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_mcp_domain_w1c_s cn; */
};
typedef union bdk_rst_mcp_domain_w1c bdk_rst_mcp_domain_w1c_t;

#define BDK_RST_MCP_DOMAIN_W1C BDK_RST_MCP_DOMAIN_W1C_FUNC()
static inline uint64_t BDK_RST_MCP_DOMAIN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_MCP_DOMAIN_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001838ll;
    __bdk_csr_fatal("RST_MCP_DOMAIN_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_MCP_DOMAIN_W1C bdk_rst_mcp_domain_w1c_t
#define bustype_BDK_RST_MCP_DOMAIN_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_RST_MCP_DOMAIN_W1C "RST_MCP_DOMAIN_W1C"
#define device_bar_BDK_RST_MCP_DOMAIN_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_MCP_DOMAIN_W1C 0
#define arguments_BDK_RST_MCP_DOMAIN_W1C -1,-1,-1,-1

/**
 * Register (RSL) rst_mcp_domain_w1s
 *
 * RST MCP Domain Soft Reset Set Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_mcp_domain_w1s
{
    uint64_t u;
    struct bdk_rst_mcp_domain_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Set software-initiated reset of MCP core and associated logic.
                                                                 When set to one, all logic associated with the MCP domain is placed in reset.
                                                                 Reads of this register show the soft reset state.  Not the actual MCP domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[MCP] shows
                                                                 the actual reset state.
                                                                 It is typically cleared by writing to RST_MCP_DOMAIN_W1C.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Set software-initiated reset of MCP core and associated logic.
                                                                 When set to one, all logic associated with the MCP domain is placed in reset.
                                                                 Reads of this register show the soft reset state.  Not the actual MCP domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[MCP] shows
                                                                 the actual reset state.
                                                                 It is typically cleared by writing to RST_MCP_DOMAIN_W1C.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_mcp_domain_w1s_s cn; */
};
typedef union bdk_rst_mcp_domain_w1s bdk_rst_mcp_domain_w1s_t;

#define BDK_RST_MCP_DOMAIN_W1S BDK_RST_MCP_DOMAIN_W1S_FUNC()
static inline uint64_t BDK_RST_MCP_DOMAIN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_MCP_DOMAIN_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001830ll;
    __bdk_csr_fatal("RST_MCP_DOMAIN_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_MCP_DOMAIN_W1S bdk_rst_mcp_domain_w1s_t
#define bustype_BDK_RST_MCP_DOMAIN_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_RST_MCP_DOMAIN_W1S "RST_MCP_DOMAIN_W1S"
#define device_bar_BDK_RST_MCP_DOMAIN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_MCP_DOMAIN_W1S 0
#define arguments_BDK_RST_MCP_DOMAIN_W1S -1,-1,-1,-1

/**
 * Register (RSL) rst_msix_pba#
 *
 * RST MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the RST_INT_VEC_E
 * enumeration.
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_msix_pbax
{
    uint64_t u;
    struct bdk_rst_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RST_MSIX_VEC()_CTL, enumerated by
                                                                 RST_INT_VEC_E. Bits that have no associated RST_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RST_MSIX_VEC()_CTL, enumerated by
                                                                 RST_INT_VEC_E. Bits that have no associated RST_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_msix_pbax_s cn8; */
    struct bdk_rst_msix_pbax_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RST_MSIX_VEC()_CTL, enumerated by
                                                                 RST_INT_VEC_E. Bits that have no associated RST_INT_VEC_E are 0.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated RST_MSIX_VEC()_CTL, enumerated by
                                                                 RST_INT_VEC_E. Bits that have no associated RST_INT_VEC_E are 0.
                                                                 This field is always reinitialized on a chip domain reset. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_msix_pbax bdk_rst_msix_pbax_t;

static inline uint64_t BDK_RST_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_MSIX_PBAX(unsigned long a)
{
    if (a==0)
        return 0x87e006ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("RST_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_MSIX_PBAX(a) bdk_rst_msix_pbax_t
#define bustype_BDK_RST_MSIX_PBAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RST_MSIX_PBAX(a) "RST_MSIX_PBAX"
#define device_bar_BDK_RST_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_RST_MSIX_PBAX(a) (a)
#define arguments_BDK_RST_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (RSL) rst_msix_vec#_addr
 *
 * RST MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the RST_INT_VEC_E enumeration.
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_msix_vecx_addr
{
    uint64_t u;
    struct bdk_rst_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector can be read or written by either secure or nonsecure states.
                                                                 1 = This vector's RST_MSIX_VEC()_ADDR, RST_MSIX_VEC()_CTL, and
                                                                 corresponding bit of RST_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_RST_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector can be read or written by either secure or nonsecure states.
                                                                 1 = This vector's RST_MSIX_VEC()_ADDR, RST_MSIX_VEC()_CTL, and
                                                                 corresponding bit of RST_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_RST_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_msix_vecx_addr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector can be read or written by either secure or nonsecure states.
                                                                 1 = This vector's RST_MSIX_VEC()_ADDR, RST_MSIX_VEC()_CTL, and
                                                                 corresponding bit of RST_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_RST_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector can be read or written by either secure or nonsecure states.
                                                                 1 = This vector's RST_MSIX_VEC()_ADDR, RST_MSIX_VEC()_CTL, and
                                                                 corresponding bit of RST_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_RST_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_msix_vecx_addr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                   0 = This vector can be read or written by either secure or nonsecure states.
                                                                   1 = This vector's RST_MSIX_VEC()_ADDR, RST_MSIX_VEC()_CTL, and
                                                                       corresponding bit of RST_MSIX_PBA() are RAZ/WI and does not cause
                                                                       a fault when accessed by the nonsecure world.

                                                                 If PCCPF_RST_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                   0 = This vector can be read or written by either secure or nonsecure states.
                                                                   1 = This vector's RST_MSIX_VEC()_ADDR, RST_MSIX_VEC()_CTL, and
                                                                       corresponding bit of RST_MSIX_PBA() are RAZ/WI and does not cause
                                                                       a fault when accessed by the nonsecure world.

                                                                 If PCCPF_RST_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn9;
    /* struct bdk_rst_msix_vecx_addr_cn9 cn96xxp1; */
    struct bdk_rst_msix_vecx_addr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's RST_MSIX_VEC()_ADDR, RST_MSIX_VEC()_CTL, and
                                                                 corresponding bit of RST_MSIX_PBA() are RAZ/WI and does not cause
                                                                 a fault when accessed by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_RST_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set.
                                                                 This field is always reinitialized on a chip domain reset.

                                                                 Also note the following:
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_EN]=1, all secure vectors (including secure
                                                                 VF vectors) will act as if PCCPF/PCCVF_XXX_MSIX_CAP_HDR[MSIXEN]=1,
                                                                 PCCPF/PCCVF_XXX_MSIX_CAP_HDR[FUNM]=0 and PCCPF/PCCVF_XXX_CMD[ME]=1.
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1, all secure vectors (including
                                                                 secure VF vectors) are considered physical, regardless of
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's RST_MSIX_VEC()_ADDR, RST_MSIX_VEC()_CTL, and
                                                                 corresponding bit of RST_MSIX_PBA() are RAZ/WI and does not cause
                                                                 a fault when accessed by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_RST_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set.
                                                                 This field is always reinitialized on a chip domain reset.

                                                                 Also note the following:
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_EN]=1, all secure vectors (including secure
                                                                 VF vectors) will act as if PCCPF/PCCVF_XXX_MSIX_CAP_HDR[MSIXEN]=1,
                                                                 PCCPF/PCCVF_XXX_MSIX_CAP_HDR[FUNM]=0 and PCCPF/PCCVF_XXX_CMD[ME]=1.
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1, all secure vectors (including
                                                                 secure VF vectors) are considered physical, regardless of
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_msix_vecx_addr_cn96xxp3 cn98xx; */
    /* struct bdk_rst_msix_vecx_addr_cn96xxp3 cnf95xx; */
    /* struct bdk_rst_msix_vecx_addr_cn96xxp3 loki; */
};
typedef union bdk_rst_msix_vecx_addr bdk_rst_msix_vecx_addr_t;

static inline uint64_t BDK_RST_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_MSIX_VECX_ADDR(unsigned long a)
{
    if (a==0)
        return 0x87e006f00000ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("RST_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_MSIX_VECX_ADDR(a) bdk_rst_msix_vecx_addr_t
#define bustype_BDK_RST_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RST_MSIX_VECX_ADDR(a) "RST_MSIX_VECX_ADDR"
#define device_bar_BDK_RST_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_RST_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_RST_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) rst_msix_vec#_ctl
 *
 * RST MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the RST_INT_VEC_E enumeration.
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_rst_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_msix_vecx_ctl_cn8
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
    } cn8;
    struct bdk_rst_msix_vecx_ctl_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts are sent to this vector.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_msix_vecx_ctl bdk_rst_msix_vecx_ctl_t;

static inline uint64_t BDK_RST_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_MSIX_VECX_CTL(unsigned long a)
{
    if (a==0)
        return 0x87e006f00008ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("RST_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_MSIX_VECX_CTL(a) bdk_rst_msix_vecx_ctl_t
#define bustype_BDK_RST_MSIX_VECX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RST_MSIX_VECX_CTL(a) "RST_MSIX_VECX_CTL"
#define device_bar_BDK_RST_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_RST_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_RST_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) rst_ocx
 *
 * INTERNAL: RST OCX Register
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_ocx
{
    uint64_t u;
    struct bdk_rst_ocx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W) Reserved. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 3;  /**< [  2:  0](R/W) Reserved. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_ocx_s cn8; */
    struct bdk_rst_ocx_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W) Reserved.
                                                                 Internal:
                                                                 Controls whether the OCX CCPI link going down causes a reset.
                                                                 This field is reinitialized with a core domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst_link              : 1;  /**< [  0:  0](R/W) Reserved.
                                                                 Internal:
                                                                 Controls whether the OCX CCPI link going down causes a reset.
                                                                 This field is reinitialized with a core domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_ocx bdk_rst_ocx_t;

#define BDK_RST_OCX BDK_RST_OCX_FUNC()
static inline uint64_t BDK_RST_OCX_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_OCX_FUNC(void)
{
    return 0x87e006001618ll;
}

#define typedef_BDK_RST_OCX bdk_rst_ocx_t
#define bustype_BDK_RST_OCX BDK_CSR_TYPE_RSL
#define basename_BDK_RST_OCX "RST_OCX"
#define device_bar_BDK_RST_OCX 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_OCX 0
#define arguments_BDK_RST_OCX -1,-1,-1,-1

/**
 * Register (RSL) rst_osc_cntr
 *
 * INTERNAL: RST Internal Ring-Oscillator Counter Register
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_osc_cntr
{
    uint64_t u;
    struct bdk_rst_osc_cntr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](RO/H) Internal ring-oscillator clock count.  Updated every 16 reference clocks. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](RO/H) Internal ring-oscillator clock count.  Updated every 16 reference clocks. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_osc_cntr_s cn8; */
    struct bdk_rst_osc_cntr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](RO/H) Internal ring-oscillator clock count.
                                                                 Updated every 16 PLL reference clocks.
                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](RO/H) Internal ring-oscillator clock count.
                                                                 Updated every 16 PLL reference clocks.
                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_osc_cntr bdk_rst_osc_cntr_t;

#define BDK_RST_OSC_CNTR BDK_RST_OSC_CNTR_FUNC()
static inline uint64_t BDK_RST_OSC_CNTR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_OSC_CNTR_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x87e006001778ll;
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001768ll;
    __bdk_csr_fatal("RST_OSC_CNTR", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_OSC_CNTR bdk_rst_osc_cntr_t
#define bustype_BDK_RST_OSC_CNTR BDK_CSR_TYPE_RSL
#define basename_BDK_RST_OSC_CNTR "RST_OSC_CNTR"
#define device_bar_BDK_RST_OSC_CNTR 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_OSC_CNTR 0
#define arguments_BDK_RST_OSC_CNTR -1,-1,-1,-1

/**
 * Register (RSL) rst_out_ctl
 *
 * RST External Reset Control Register
 * This register is accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_out_ctl
{
    uint64_t u;
    struct bdk_rst_out_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t bphy_rst              : 1;  /**< [  4:  4](R/W) BPHY reset output. When set by software, this field drives the GPIO_PIN_SEL_E::BPHY_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a BPHY
                                                                 domain reset.
                                                                 This field is always reinitialized on a BPHY domain reset. */
        uint64_t scp_rst               : 1;  /**< [  3:  3](R/W) SCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::SCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a SCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an SCP domain reset. */
        uint64_t mcp_rst               : 1;  /**< [  2:  2](R/W) MCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::MCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a MCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an MCP domain reset. */
        uint64_t core_rst              : 1;  /**< [  1:  1](R/W) Core reset output. When set by software, this field drives the GPIO_PIN_SEL_E::CORE_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a core
                                                                 domain reset.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t core_rst              : 1;  /**< [  1:  1](R/W) Core reset output. When set by software, this field drives the GPIO_PIN_SEL_E::CORE_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a core
                                                                 domain reset.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t mcp_rst               : 1;  /**< [  2:  2](R/W) MCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::MCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a MCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an MCP domain reset. */
        uint64_t scp_rst               : 1;  /**< [  3:  3](R/W) SCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::SCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a SCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an SCP domain reset. */
        uint64_t bphy_rst              : 1;  /**< [  4:  4](R/W) BPHY reset output. When set by software, this field drives the GPIO_PIN_SEL_E::BPHY_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a BPHY
                                                                 domain reset.
                                                                 This field is always reinitialized on a BPHY domain reset. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_out_ctl_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W) Soft reset. When set to 1 by software, this field drives the CHIP_RESET_OUT_L pin
                                                                 active low. In this case the field must also be cleared by software to deassert
                                                                 the pin. The pin is also automatically asserted and deasserted by hardware
                                                                 during a cold/warm/soft reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W) Soft reset. When set to 1 by software, this field drives the CHIP_RESET_OUT_L pin
                                                                 active low. In this case the field must also be cleared by software to deassert
                                                                 the pin. The pin is also automatically asserted and deasserted by hardware
                                                                 during a cold/warm/soft reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_out_ctl_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t bphy_rst              : 1;  /**< [  4:  4](R/W) BPHY reset output. When set by software, this field drives the GPIO_PIN_SEL_E::BPHY_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a BPHY
                                                                 domain reset.
                                                                 This field is always reinitialized on a BPHY domain reset. */
        uint64_t scp_rst               : 1;  /**< [  3:  3](R/W) SCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::SCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a SCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an SCP domain reset. */
        uint64_t mcp_rst               : 1;  /**< [  2:  2](R/W) MCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::MCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a MCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an MCP domain reset. */
        uint64_t core_rst              : 1;  /**< [  1:  1](R/W) Core reset output. When set by software, this field drives the GPIO_PIN_SEL_E::CORE_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a core
                                                                 domain reset.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t chip_rst              : 1;  /**< [  0:  0](R/W) Chip domain reset output. When set to one by software, this field drives the
                                                                 CHIP_RESET_OUT_L pin active low. If this field is set my software then it must also be
                                                                 cleared to deassert the pin. The pin is also automatically asserted and deasserted by
                                                                 hardware during a chip domain reset.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t chip_rst              : 1;  /**< [  0:  0](R/W) Chip domain reset output. When set to one by software, this field drives the
                                                                 CHIP_RESET_OUT_L pin active low. If this field is set my software then it must also be
                                                                 cleared to deassert the pin. The pin is also automatically asserted and deasserted by
                                                                 hardware during a chip domain reset.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t core_rst              : 1;  /**< [  1:  1](R/W) Core reset output. When set by software, this field drives the GPIO_PIN_SEL_E::CORE_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a core
                                                                 domain reset.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t mcp_rst               : 1;  /**< [  2:  2](R/W) MCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::MCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a MCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an MCP domain reset. */
        uint64_t scp_rst               : 1;  /**< [  3:  3](R/W) SCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::SCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a SCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an SCP domain reset. */
        uint64_t bphy_rst              : 1;  /**< [  4:  4](R/W) BPHY reset output. When set by software, this field drives the GPIO_PIN_SEL_E::BPHY_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a BPHY
                                                                 domain reset.
                                                                 This field is always reinitialized on a BPHY domain reset. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_out_ctl_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t scp_rst               : 1;  /**< [  3:  3](R/W) SCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::SCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a SCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an SCP domain reset. */
        uint64_t mcp_rst               : 1;  /**< [  2:  2](R/W) MCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::MCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a MCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an MCP domain reset. */
        uint64_t core_rst              : 1;  /**< [  1:  1](R/W) Core reset output. When set by software, this field drives the GPIO_PIN_SEL_E::CORE_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a core
                                                                 domain reset.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t chip_rst              : 1;  /**< [  0:  0](R/W) Chip domain reset output. When set to one by software, this field drives the
                                                                 CHIP_RESET_OUT_L pin active low. If this field is set my software then it must also be
                                                                 cleared to deassert the pin. The pin is also automatically asserted and deasserted by
                                                                 hardware during a chip domain reset.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t chip_rst              : 1;  /**< [  0:  0](R/W) Chip domain reset output. When set to one by software, this field drives the
                                                                 CHIP_RESET_OUT_L pin active low. If this field is set my software then it must also be
                                                                 cleared to deassert the pin. The pin is also automatically asserted and deasserted by
                                                                 hardware during a chip domain reset.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t core_rst              : 1;  /**< [  1:  1](R/W) Core reset output. When set by software, this field drives the GPIO_PIN_SEL_E::CORE_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a core
                                                                 domain reset.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t mcp_rst               : 1;  /**< [  2:  2](R/W) MCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::MCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a MCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an MCP domain reset. */
        uint64_t scp_rst               : 1;  /**< [  3:  3](R/W) SCP reset output. When set by software, this field drives the GPIO_PIN_SEL_E::SCP_RESET_OUT
                                                                 selectable pin active. The pin can be assigned using GPIO_BIT_CFG(). If this
                                                                 field is set by software then it must also be cleared to deassert the pin.
                                                                 The pin is also automatically asserted and deasserted by hardware during a SCP
                                                                 domain reset.
                                                                 This field is always reinitialized on an SCP domain reset. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_rst_out_ctl_cn96xx cn98xx; */
    /* struct bdk_rst_out_ctl_cn9 cnf95xx; */
    /* struct bdk_rst_out_ctl_cn9 loki; */
};
typedef union bdk_rst_out_ctl bdk_rst_out_ctl_t;

#define BDK_RST_OUT_CTL BDK_RST_OUT_CTL_FUNC()
static inline uint64_t BDK_RST_OUT_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_OUT_CTL_FUNC(void)
{
    return 0x87e006001688ll;
}

#define typedef_BDK_RST_OUT_CTL bdk_rst_out_ctl_t
#define bustype_BDK_RST_OUT_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_OUT_CTL "RST_OUT_CTL"
#define device_bar_BDK_RST_OUT_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_OUT_CTL 0
#define arguments_BDK_RST_OUT_CTL -1,-1,-1,-1

/**
 * Register (RSL) rst_pll_limit
 *
 * RST PLL Maximum Frequency Limit Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_pll_limit
{
    uint64_t u;
    struct bdk_rst_pll_limit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_23_63        : 41;
        uint64_t cpt_max_mul           : 7;  /**< [ 22: 16](R/W/H) Crypto clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_CPT_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value. Values 1-3 are considered illegal
                                                                 since the minimum PLL frequency is 200 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CPT_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_15           : 1;
        uint64_t core_max_mul          : 7;  /**< [ 14:  8](R/W/H) Core clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_CORE_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CORE_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_7            : 1;
        uint64_t pnr_max_mul           : 7;  /**< [  6:  0](R/W/H) Coprocessor clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_PNR_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::PNR_MAX_MUL() fuses on a chip domain
                                                                 reset. */
#else /* Word 0 - Little Endian */
        uint64_t pnr_max_mul           : 7;  /**< [  6:  0](R/W/H) Coprocessor clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_PNR_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::PNR_MAX_MUL() fuses on a chip domain
                                                                 reset. */
        uint64_t reserved_7            : 1;
        uint64_t core_max_mul          : 7;  /**< [ 14:  8](R/W/H) Core clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_CORE_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CORE_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_15           : 1;
        uint64_t cpt_max_mul           : 7;  /**< [ 22: 16](R/W/H) Crypto clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_CPT_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value. Values 1-3 are considered illegal
                                                                 since the minimum PLL frequency is 200 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CPT_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_23_63        : 41;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_pll_limit_s cn9; */
    /* struct bdk_rst_pll_limit_s cn96xx; */
    struct bdk_rst_pll_limit_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_39_63        : 25;
        uint64_t rxp_max_mul           : 7;  /**< [ 38: 32](R/W/H) RXP clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_RXP_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value. Values 1-3 are considered illegal
                                                                 since the minimum PLL frequency is 200 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::RXP_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_31           : 1;
        uint64_t cpt1_max_mul          : 7;  /**< [ 30: 24](R/W/H) Crypto clock maximum PLL multiplier for CPT1.
                                                                 This field is used to limit the RST_CPT1_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value. Values 1-3 are considered illegal
                                                                 since the minimum PLL frequency is 200 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CPT_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_23           : 1;
        uint64_t cpt_max_mul           : 7;  /**< [ 22: 16](R/W/H) Crypto clock maximum PLL multiplier for CPT0.
                                                                 This field is used to limit the RST_CPT_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value. Values 1-3 are considered illegal
                                                                 since the minimum PLL frequency is 200 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CPT_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_15           : 1;
        uint64_t core_max_mul          : 7;  /**< [ 14:  8](R/W/H) Core clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_CORE_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CORE_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_7            : 1;
        uint64_t pnr_max_mul           : 7;  /**< [  6:  0](R/W/H) Coprocessor clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_PNR_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::PNR_MAX_MUL() fuses on a chip domain
                                                                 reset. */
#else /* Word 0 - Little Endian */
        uint64_t pnr_max_mul           : 7;  /**< [  6:  0](R/W/H) Coprocessor clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_PNR_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::PNR_MAX_MUL() fuses on a chip domain
                                                                 reset. */
        uint64_t reserved_7            : 1;
        uint64_t core_max_mul          : 7;  /**< [ 14:  8](R/W/H) Core clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_CORE_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CORE_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_15           : 1;
        uint64_t cpt_max_mul           : 7;  /**< [ 22: 16](R/W/H) Crypto clock maximum PLL multiplier for CPT0.
                                                                 This field is used to limit the RST_CPT_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value. Values 1-3 are considered illegal
                                                                 since the minimum PLL frequency is 200 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CPT_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_23           : 1;
        uint64_t cpt1_max_mul          : 7;  /**< [ 30: 24](R/W/H) Crypto clock maximum PLL multiplier for CPT1.
                                                                 This field is used to limit the RST_CPT1_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value. Values 1-3 are considered illegal
                                                                 since the minimum PLL frequency is 200 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CPT_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_31           : 1;
        uint64_t rxp_max_mul           : 7;  /**< [ 38: 32](R/W/H) RXP clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_RXP_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value. Values 1-3 are considered illegal
                                                                 since the minimum PLL frequency is 200 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::RXP_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_39_63        : 25;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_rst_pll_limit_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_39_63        : 25;
        uint64_t bphy_max_mul          : 7;  /**< [ 38: 32](R/W/H) BPHY clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_DSP_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::BPHY_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_31           : 1;
        uint64_t dsp_max_mul           : 7;  /**< [ 30: 24](R/W/H) DSP clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_DSP_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::DSP_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_23           : 1;
        uint64_t cpt_max_mul           : 7;  /**< [ 22: 16](R/W/H) Reserved.
                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CPT_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_15           : 1;
        uint64_t core_max_mul          : 7;  /**< [ 14:  8](R/W/H) Core clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_CORE_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CORE_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_7            : 1;
        uint64_t pnr_max_mul           : 7;  /**< [  6:  0](R/W/H) Coprocessor clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_PNR_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::PNR_MAX_MUL() fuses on a chip domain
                                                                 reset. */
#else /* Word 0 - Little Endian */
        uint64_t pnr_max_mul           : 7;  /**< [  6:  0](R/W/H) Coprocessor clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_PNR_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::PNR_MAX_MUL() fuses on a chip domain
                                                                 reset. */
        uint64_t reserved_7            : 1;
        uint64_t core_max_mul          : 7;  /**< [ 14:  8](R/W/H) Core clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_CORE_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CORE_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_15           : 1;
        uint64_t cpt_max_mul           : 7;  /**< [ 22: 16](R/W/H) Reserved.
                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::CPT_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_23           : 1;
        uint64_t dsp_max_mul           : 7;  /**< [ 30: 24](R/W/H) DSP clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_DSP_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::DSP_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_31           : 1;
        uint64_t bphy_max_mul          : 7;  /**< [ 38: 32](R/W/H) BPHY clock maximum PLL multiplier.
                                                                 This field is used to limit the RST_DSP_PLL[CUR_MUL] value.
                                                                 A value of zero is considered unlimited.  Once the value
                                                                 of this field is nonzero, any new values written into this field
                                                                 cannot exceed the previous value.  Values 1-5 are considered illegal
                                                                 since the minimum PLL frequency is 300 MHz.

                                                                 Internal:
                                                                 The field is initialized to FUS_FUSE_NUM_E::BPHY_MAX_MUL() fuses on a chip domain reset. */
        uint64_t reserved_39_63        : 25;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_rst_pll_limit_cnf95xx loki; */
};
typedef union bdk_rst_pll_limit bdk_rst_pll_limit_t;

#define BDK_RST_PLL_LIMIT BDK_RST_PLL_LIMIT_FUNC()
static inline uint64_t BDK_RST_PLL_LIMIT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_PLL_LIMIT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00a001790ll;
    __bdk_csr_fatal("RST_PLL_LIMIT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_PLL_LIMIT bdk_rst_pll_limit_t
#define bustype_BDK_RST_PLL_LIMIT BDK_CSR_TYPE_RSL
#define basename_BDK_RST_PLL_LIMIT "RST_PLL_LIMIT"
#define device_bar_BDK_RST_PLL_LIMIT 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_PLL_LIMIT 0
#define arguments_BDK_RST_PLL_LIMIT -1,-1,-1,-1

/**
 * Register (RSL) rst_pnr_pll
 *
 * RST Coprocessor Clock PLL Control Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_pnr_pll
{
    uint64_t u;
    struct bdk_rst_pnr_pll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Coprocessor clockout select.
                                                                   0x0 = Coprocessor clock divided by 32.
                                                                   0x1 = Coprocessor clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Coprocessor clockout reset. The coprocessor clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 cpt_clk/sclk/rclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) PNR PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) PNR PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Coprocessor clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[PNR_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLLs are updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Coprocessor PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[PNR_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Coprocessor clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[PNR_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Coprocessor clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[PNR_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Coprocessor PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[PNR_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLLs are updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Coprocessor clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[PNR_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) PNR PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) PNR PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 cpt_clk/sclk/rclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Coprocessor clockout reset. The coprocessor clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Coprocessor clockout select.
                                                                   0x0 = Coprocessor clock divided by 32.
                                                                   0x1 = Coprocessor clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_pnr_pll_s cn9; */
    /* struct bdk_rst_pnr_pll_s cn96xx; */
    struct bdk_rst_pnr_pll_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Coprocessor clockout select.
                                                                   0x0 = Coprocessor clock divided by 32.
                                                                   0x1 = Coprocessor clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Coprocessor clockout reset. The coprocessor clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) PNR PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) PNR PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Coprocessor clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[PNR_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLLs are updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Coprocessor PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[PNR_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Coprocessor clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[PNR_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Coprocessor clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[PNR_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Coprocessor PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[PNR_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLLs are updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Coprocessor clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[PNR_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) PNR PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) PNR PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Coprocessor clockout reset. The coprocessor clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Coprocessor clockout select.
                                                                   0x0 = Coprocessor clock divided by 32.
                                                                   0x1 = Coprocessor clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn98xx;
    struct bdk_rst_pnr_pll_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Coprocessor clockout select.
                                                                   0x0 = Coprocessor clock divided by 32.
                                                                   0x1 = Coprocessor clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Coprocessor clockout reset. The coprocessor clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 sclk/rclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) PNR PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) PNR PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Coprocessor clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[PNR_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLLs are updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Coprocessor PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[PNR_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Coprocessor clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[PNR_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) Coprocessor clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[PNR_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) Coprocessor PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[PNR_MAX_MUL] and
                                                                 a minimum setting of 300 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLLs are updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) Coprocessor clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[PNR_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) PNR PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) PNR PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.

                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 sclk/rclk notification to hardware.
                                                                 Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) Coprocessor clockout reset. The coprocessor clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) Coprocessor clockout select.
                                                                   0x0 = Coprocessor clock divided by 32.
                                                                   0x1 = Coprocessor clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_rst_pnr_pll_cnf95xx loki; */
};
typedef union bdk_rst_pnr_pll bdk_rst_pnr_pll_t;

#define BDK_RST_PNR_PLL BDK_RST_PNR_PLL_FUNC()
static inline uint64_t BDK_RST_PNR_PLL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_PNR_PLL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00a001788ll;
    __bdk_csr_fatal("RST_PNR_PLL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_PNR_PLL bdk_rst_pnr_pll_t
#define bustype_BDK_RST_PNR_PLL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_PNR_PLL "RST_PNR_PLL"
#define device_bar_BDK_RST_PNR_PLL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_PNR_PLL 0
#define arguments_BDK_RST_PNR_PLL -1,-1,-1,-1

/**
 * Register (RSL) rst_power_dbg
 *
 * RST Core-Power Debug-Control Register
 */
union bdk_rst_power_dbg
{
    uint64_t u;
    struct bdk_rst_power_dbg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t str                   : 3;  /**< [  2:  0](R/W) Reserved.
                                                                 Internal:
                                                                 Internal power driver strength. Resets only on cold reset. */
#else /* Word 0 - Little Endian */
        uint64_t str                   : 3;  /**< [  2:  0](R/W) Reserved.
                                                                 Internal:
                                                                 Internal power driver strength. Resets only on cold reset. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_power_dbg_s cn; */
};
typedef union bdk_rst_power_dbg bdk_rst_power_dbg_t;

#define BDK_RST_POWER_DBG BDK_RST_POWER_DBG_FUNC()
static inline uint64_t BDK_RST_POWER_DBG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_POWER_DBG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x87e006001708ll;
    __bdk_csr_fatal("RST_POWER_DBG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_POWER_DBG bdk_rst_power_dbg_t
#define bustype_BDK_RST_POWER_DBG BDK_CSR_TYPE_RSL
#define basename_BDK_RST_POWER_DBG "RST_POWER_DBG"
#define device_bar_BDK_RST_POWER_DBG 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_POWER_DBG 0
#define arguments_BDK_RST_POWER_DBG -1,-1,-1,-1

/**
 * Register (RSL) rst_pp_available
 *
 * RST Core Availability Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_pp_available
{
    uint64_t u;
    struct bdk_rst_pp_available_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t present               : 36; /**< [ 35:  0](RO) Each bit set indicates a physical core is present. */
#else /* Word 0 - Little Endian */
        uint64_t present               : 36; /**< [ 35:  0](RO) Each bit set indicates a physical core is present. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_pp_available_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t present               : 24; /**< [ 23:  0](RO) Each bit set indicates a physical core is present. */
#else /* Word 0 - Little Endian */
        uint64_t present               : 24; /**< [ 23:  0](RO) Each bit set indicates a physical core is present. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_pp_available_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t present               : 4;  /**< [  3:  0](RO) Each bit set indicates a physical core is present. */
#else /* Word 0 - Little Endian */
        uint64_t present               : 4;  /**< [  3:  0](RO) Each bit set indicates a physical core is present. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_pp_available_cn8 cn83xx; */
    /* struct bdk_rst_pp_available_s cn9; */
    /* struct bdk_rst_pp_available_cn8 cn96xx; */
    /* struct bdk_rst_pp_available_s cn98xx; */
    struct bdk_rst_pp_available_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t present               : 6;  /**< [  5:  0](RO) Each bit set indicates a physical core is present. */
#else /* Word 0 - Little Endian */
        uint64_t present               : 6;  /**< [  5:  0](RO) Each bit set indicates a physical core is present. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_rst_pp_available_cnf95xx loki; */
};
typedef union bdk_rst_pp_available bdk_rst_pp_available_t;

#define BDK_RST_PP_AVAILABLE BDK_RST_PP_AVAILABLE_FUNC()
static inline uint64_t BDK_RST_PP_AVAILABLE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_PP_AVAILABLE_FUNC(void)
{
    return 0x87e006001738ll;
}

#define typedef_BDK_RST_PP_AVAILABLE bdk_rst_pp_available_t
#define bustype_BDK_RST_PP_AVAILABLE BDK_CSR_TYPE_RSL
#define basename_BDK_RST_PP_AVAILABLE "RST_PP_AVAILABLE"
#define device_bar_BDK_RST_PP_AVAILABLE 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_PP_AVAILABLE 0
#define arguments_BDK_RST_PP_AVAILABLE -1,-1,-1,-1

/**
 * Register (RSL) rst_pp_pending
 *
 * RST Cores Reset Pending Register
 * This register contains the reset status for each core.
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_pp_pending
{
    uint64_t u;
    struct bdk_rst_pp_pending_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t pend                  : 36; /**< [ 35:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 64K core-clock cycles between each core reset applies to satisfy power
                                                                 management.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 36; /**< [ 35:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 64K core-clock cycles between each core reset applies to satisfy power
                                                                 management.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_pp_pending_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t pend                  : 24; /**< [ 23:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 64K core-clock cycles between each core reset applies to satisfy power
                                                                 management.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 24; /**< [ 23:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 64K core-clock cycles between each core reset applies to satisfy power
                                                                 management.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_pp_pending_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t pend                  : 4;  /**< [  3:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 64K core-clock cycles between each core reset applies to satisfy power
                                                                 management.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 4;  /**< [  3:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 64K core-clock cycles between each core reset applies to satisfy power
                                                                 management.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_pp_pending_cn8 cn83xx; */
    struct bdk_rst_pp_pending_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t pend                  : 36; /**< [ 35:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 32K core-clock cycles between each core reset applies to satisfy power
                                                                 management.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 36; /**< [ 35:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 32K core-clock cycles between each core reset applies to satisfy power
                                                                 management.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_pp_pending_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t pend                  : 24; /**< [ 23:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 32K core-clock cycles between each core reset applies to satisfy power
                                                                 management.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 24; /**< [ 23:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 32K core-clock cycles between each core reset applies to satisfy power
                                                                 management.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_rst_pp_pending_cn9 cn98xx; */
    struct bdk_rst_pp_pending_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t pend                  : 6;  /**< [  5:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 32K core-clock cycles between each core reset applies to satisfy power
                                                                 management.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 6;  /**< [  5:  0](RO/H) Set if corresponding core is waiting to change its reset state. Normally a reset change
                                                                 occurs immediately but if RST_PP_POWER[GATE] = 1 and the core is released from
                                                                 reset a delay of 32K core-clock cycles between each core reset applies to satisfy power
                                                                 management.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_rst_pp_pending_cnf95xx loki; */
};
typedef union bdk_rst_pp_pending bdk_rst_pp_pending_t;

#define BDK_RST_PP_PENDING BDK_RST_PP_PENDING_FUNC()
static inline uint64_t BDK_RST_PP_PENDING_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_PP_PENDING_FUNC(void)
{
    return 0x87e006001748ll;
}

#define typedef_BDK_RST_PP_PENDING bdk_rst_pp_pending_t
#define bustype_BDK_RST_PP_PENDING BDK_CSR_TYPE_RSL
#define basename_BDK_RST_PP_PENDING "RST_PP_PENDING"
#define device_bar_BDK_RST_PP_PENDING 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_PP_PENDING 0
#define arguments_BDK_RST_PP_PENDING -1,-1,-1,-1

/**
 * Register (RSL) rst_pp_power
 *
 * RST Core Power Control Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_pp_power
{
    uint64_t u;
    struct bdk_rst_pp_power_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t gate                  : 36; /**< [ 35:  0](R/W) Power down enable. When a bit in this field and the corresponding RST_PP_RESET bit are
                                                                 set,
                                                                 the core
                                                                 has voltage removed to save power. In typical operation these bits are set up during
                                                                 initialization and core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t gate                  : 36; /**< [ 35:  0](R/W) Power down enable. When a bit in this field and the corresponding RST_PP_RESET bit are
                                                                 set,
                                                                 the core
                                                                 has voltage removed to save power. In typical operation these bits are set up during
                                                                 initialization and core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_pp_power_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t gate                  : 24; /**< [ 23:  0](R/W) Power down enable. When a bit in this field and the corresponding RST_PP_RESET bit are
                                                                 set,
                                                                 the core
                                                                 has voltage removed to save power. In typical operation these bits are set up during
                                                                 initialization and core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t gate                  : 24; /**< [ 23:  0](R/W) Power down enable. When a bit in this field and the corresponding RST_PP_RESET bit are
                                                                 set,
                                                                 the core
                                                                 has voltage removed to save power. In typical operation these bits are set up during
                                                                 initialization and core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_pp_power_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t gate                  : 4;  /**< [  3:  0](R/W) Power down enable. When a bit in this field and the corresponding RST_PP_RESET bit are
                                                                 set,
                                                                 the core
                                                                 has voltage removed to save power. In typical operation these bits are set up during
                                                                 initialization and core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t gate                  : 4;  /**< [  3:  0](R/W) Power down enable. When a bit in this field and the corresponding RST_PP_RESET bit are
                                                                 set,
                                                                 the core
                                                                 has voltage removed to save power. In typical operation these bits are set up during
                                                                 initialization and core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_pp_power_cn8 cn83xx; */
    struct bdk_rst_pp_power_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t gate                  : 36; /**< [ 35:  0](R/W) When a bit in this field and the corresponding
                                                                 RST_PP_RESET bit are set, the AP core is reduced to minimum power consumption.
                                                                 In typical operation these bits are set up during initialization and the
                                                                 AP core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding AP core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 Internal:
                                                                 Note this does not power off the cores, but only reduces power. There is no
                                                                 per-core power gating in CNXXXX. */
#else /* Word 0 - Little Endian */
        uint64_t gate                  : 36; /**< [ 35:  0](R/W) When a bit in this field and the corresponding
                                                                 RST_PP_RESET bit are set, the AP core is reduced to minimum power consumption.
                                                                 In typical operation these bits are set up during initialization and the
                                                                 AP core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding AP core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 Internal:
                                                                 Note this does not power off the cores, but only reduces power. There is no
                                                                 per-core power gating in CNXXXX. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_pp_power_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t gate                  : 24; /**< [ 23:  0](R/W) When a bit in this field and the corresponding
                                                                 RST_PP_RESET bit are set, the AP core is reduced to minimum power consumption.
                                                                 In typical operation these bits are set up during initialization and the
                                                                 AP core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding AP core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 Internal:
                                                                 Note this does not power off the cores, but only reduces power. There is no
                                                                 per-core power gating in CNXXXX. */
#else /* Word 0 - Little Endian */
        uint64_t gate                  : 24; /**< [ 23:  0](R/W) When a bit in this field and the corresponding
                                                                 RST_PP_RESET bit are set, the AP core is reduced to minimum power consumption.
                                                                 In typical operation these bits are set up during initialization and the
                                                                 AP core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding AP core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 Internal:
                                                                 Note this does not power off the cores, but only reduces power. There is no
                                                                 per-core power gating in CNXXXX. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_rst_pp_power_cn9 cn98xx; */
    struct bdk_rst_pp_power_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t gate                  : 6;  /**< [  5:  0](R/W) When a bit in this field and the corresponding
                                                                 RST_PP_RESET bit are set, the AP core is reduced to minimum power consumption.
                                                                 In typical operation these bits are set up during initialization and the
                                                                 AP core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding AP core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 Internal:
                                                                 Note this does not power off the cores, but only reduces power. There is no
                                                                 per-core power gating in CNXXXX. */
#else /* Word 0 - Little Endian */
        uint64_t gate                  : 6;  /**< [  5:  0](R/W) When a bit in this field and the corresponding
                                                                 RST_PP_RESET bit are set, the AP core is reduced to minimum power consumption.
                                                                 In typical operation these bits are set up during initialization and the
                                                                 AP core resets are controlled through RST_PP_RESET. These bits can only be
                                                                 changed when the corresponding AP core is in reset.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.
                                                                 This field is always reinitialized on a core domain reset.

                                                                 Internal:
                                                                 Note this does not power off the cores, but only reduces power. There is no
                                                                 per-core power gating in CNXXXX. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_rst_pp_power_cnf95xx loki; */
};
typedef union bdk_rst_pp_power bdk_rst_pp_power_t;

#define BDK_RST_PP_POWER BDK_RST_PP_POWER_FUNC()
static inline uint64_t BDK_RST_PP_POWER_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_PP_POWER_FUNC(void)
{
    return 0x87e006001700ll;
}

#define typedef_BDK_RST_PP_POWER bdk_rst_pp_power_t
#define bustype_BDK_RST_PP_POWER BDK_CSR_TYPE_RSL
#define basename_BDK_RST_PP_POWER "RST_PP_POWER"
#define device_bar_BDK_RST_PP_POWER 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_PP_POWER 0
#define arguments_BDK_RST_PP_POWER -1,-1,-1,-1

/**
 * Register (RSL) rst_pp_power_stat
 *
 * RST Core-Power Status Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_pp_power_stat
{
    uint64_t u;
    struct bdk_rst_pp_power_stat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t down                  : 36; /**< [ 35:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t down                  : 36; /**< [ 35:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_pp_power_stat_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t down                  : 24; /**< [ 23:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t down                  : 24; /**< [ 23:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_pp_power_stat_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t down                  : 4;  /**< [  3:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
#else /* Word 0 - Little Endian */
        uint64_t down                  : 4;  /**< [  3:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_pp_power_stat_cn8 cn83xx; */
    struct bdk_rst_pp_power_stat_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t down                  : 36; /**< [ 35:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.

                                                                 This field is reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t down                  : 36; /**< [ 35:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.

                                                                 This field is reinitialized on a cold domain reset. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_pp_power_stat_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t down                  : 24; /**< [ 23:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.

                                                                 This field is reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t down                  : 24; /**< [ 23:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.

                                                                 This field is reinitialized on a cold domain reset. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_rst_pp_power_stat_cn9 cn98xx; */
    struct bdk_rst_pp_power_stat_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t down                  : 6;  /**< [  5:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.

                                                                 This field is reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t down                  : 6;  /**< [  5:  0](RO/H) Reserved.
                                                                 Internal:
                                                                 Core Powerdown. When set, each bit indicates the core is currently powered down.
                                                                 Typically this occurs when the corresponding RST_PP_RESET and RST_PP_POWER bits are set.
                                                                 If the core is powered down when RST_PP_PENDING and RST_PP_RESET are both clear then the
                                                                 core should be reset again by setting the RST_PP_RESET and then clearing it.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores.

                                                                 This field is reinitialized on a cold domain reset. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_rst_pp_power_stat_cnf95xx loki; */
};
typedef union bdk_rst_pp_power_stat bdk_rst_pp_power_stat_t;

#define BDK_RST_PP_POWER_STAT BDK_RST_PP_POWER_STAT_FUNC()
static inline uint64_t BDK_RST_PP_POWER_STAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_PP_POWER_STAT_FUNC(void)
{
    return 0x87e006001710ll;
}

#define typedef_BDK_RST_PP_POWER_STAT bdk_rst_pp_power_stat_t
#define bustype_BDK_RST_PP_POWER_STAT BDK_CSR_TYPE_RSL
#define basename_BDK_RST_PP_POWER_STAT "RST_PP_POWER_STAT"
#define device_bar_BDK_RST_PP_POWER_STAT 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_PP_POWER_STAT 0
#define arguments_BDK_RST_PP_POWER_STAT -1,-1,-1,-1

/**
 * Register (RSL) rst_pp_reset
 *
 * RST Core Reset Register
 * This register contains the reset control for each core.
 * Write operations to this register should occur only if
 * RST_PP_PENDING is cleared.
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_pp_reset
{
    uint64_t u;
    struct bdk_rst_pp_reset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_0_63         : 64;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_63         : 64;
#endif /* Word 0 - End */
    } s;
    struct bdk_rst_pp_reset_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t rst                   : 23; /**< [ 23:  1](R/W/H) Core reset for cores 1 and above. Writing a 1 holds the corresponding core in reset,
                                                                 writing a 0 releases from reset. These bits may also be cleared by either DAP or CIC
                                                                 activity.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t rst0                  : 1;  /**< [  0:  0](R/W/H) Core reset for core 0, depends on if GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE.
                                                                 This bit may also be cleared by either DAP or CIC activity. */
#else /* Word 0 - Little Endian */
        uint64_t rst0                  : 1;  /**< [  0:  0](R/W/H) Core reset for core 0, depends on if GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE.
                                                                 This bit may also be cleared by either DAP or CIC activity. */
        uint64_t rst                   : 23; /**< [ 23:  1](R/W/H) Core reset for cores 1 and above. Writing a 1 holds the corresponding core in reset,
                                                                 writing a 0 releases from reset. These bits may also be cleared by either DAP or CIC
                                                                 activity.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_rst_pp_reset_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t rst                   : 3;  /**< [  3:  1](R/W/H) Core reset for cores 1 and above. Writing a 1 holds the corresponding core in reset,
                                                                 writing a 0 releases from reset. These bits may also be cleared by either DAP or CIC
                                                                 activity.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t rst0                  : 1;  /**< [  0:  0](R/W/H) Core reset for core 0, depends on if GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE.
                                                                 This bit may also be cleared by either DAP or CIC activity. */
#else /* Word 0 - Little Endian */
        uint64_t rst0                  : 1;  /**< [  0:  0](R/W/H) Core reset for core 0, depends on if GPIO_STRAP\<2:0\> = RST_BOOT_METHOD_E::REMOTE.
                                                                 This bit may also be cleared by either DAP or CIC activity. */
        uint64_t rst                   : 3;  /**< [  3:  1](R/W/H) Core reset for cores 1 and above. Writing a 1 holds the corresponding core in reset,
                                                                 writing a 0 releases from reset. These bits may also be cleared by either DAP or CIC
                                                                 activity.

                                                                 The upper bits of this field remain accessible but will have no effect if the cores
                                                                 are disabled. The number of bits set in RST_PP_AVAILABLE indicate the number of cores. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_pp_reset_cn8 cn83xx; */
    struct bdk_rst_pp_reset_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_36_63        : 28;
        uint64_t rst                   : 36; /**< [ 35:  0](R/W/H) AP core resets. Writing a one holds the corresponding AP core in reset,
                                                                 writing a zero releases it from reset. These bits may also be cleared by
                                                                 either DAP or CIC activity.
                                                                 This field is always reinitialized on a core domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 36; /**< [ 35:  0](R/W/H) AP core resets. Writing a one holds the corresponding AP core in reset,
                                                                 writing a zero releases it from reset. These bits may also be cleared by
                                                                 either DAP or CIC activity.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t reserved_36_63        : 28;
#endif /* Word 0 - End */
    } cn9;
    struct bdk_rst_pp_reset_cn96xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t rst                   : 24; /**< [ 23:  0](R/W/H) AP core resets. Writing a one holds the corresponding AP core in reset,
                                                                 writing a zero releases it from reset. These bits may also be cleared by
                                                                 either DAP or CIC activity.
                                                                 This field is always reinitialized on a core domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 24; /**< [ 23:  0](R/W/H) AP core resets. Writing a one holds the corresponding AP core in reset,
                                                                 writing a zero releases it from reset. These bits may also be cleared by
                                                                 either DAP or CIC activity.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } cn96xx;
    /* struct bdk_rst_pp_reset_cn9 cn98xx; */
    struct bdk_rst_pp_reset_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t rst                   : 6;  /**< [  5:  0](R/W/H) AP core resets. Writing a one holds the corresponding AP core in reset,
                                                                 writing a zero releases it from reset. These bits may also be cleared by
                                                                 either DAP or CIC activity.
                                                                 This field is always reinitialized on a core domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 6;  /**< [  5:  0](R/W/H) AP core resets. Writing a one holds the corresponding AP core in reset,
                                                                 writing a zero releases it from reset. These bits may also be cleared by
                                                                 either DAP or CIC activity.
                                                                 This field is always reinitialized on a core domain reset. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_rst_pp_reset_cnf95xx loki; */
};
typedef union bdk_rst_pp_reset bdk_rst_pp_reset_t;

#define BDK_RST_PP_RESET BDK_RST_PP_RESET_FUNC()
static inline uint64_t BDK_RST_PP_RESET_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_PP_RESET_FUNC(void)
{
    return 0x87e006001740ll;
}

#define typedef_BDK_RST_PP_RESET bdk_rst_pp_reset_t
#define bustype_BDK_RST_PP_RESET BDK_CSR_TYPE_RSL
#define basename_BDK_RST_PP_RESET "RST_PP_RESET"
#define device_bar_BDK_RST_PP_RESET 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_PP_RESET 0
#define arguments_BDK_RST_PP_RESET -1,-1,-1,-1

/**
 * Register (RSL) rst_ref_check
 *
 * INTERNAL: RST Reference Clock Checker Register
 *
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_ref_check
{
    uint64_t u;
    struct bdk_rst_ref_check_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t range                 : 1;  /**< [ 63: 63](RO/H) Reference ever out of range. Set when either:
                                                                 * Reference clock was outside operating range of 25 to 100 MHz.
                                                                 * Reference clock increased or decreased in frequency. */
        uint64_t reserved_48_62        : 15;
        uint64_t pcycle                : 16; /**< [ 47: 32](RO/H) Previous cycle count.  Sum of last [CNT0] and [CNT1]. */
        uint64_t cnt1                  : 16; /**< [ 31: 16](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was high.
                                                                 When used with [CNT0] the internal ring-oscillator frequency can be determined. */
        uint64_t cnt0                  : 16; /**< [ 15:  0](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was low.
                                                                 When used with [CNT1] the internal ring-oscillator frequency can be determined. */
#else /* Word 0 - Little Endian */
        uint64_t cnt0                  : 16; /**< [ 15:  0](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was low.
                                                                 When used with [CNT1] the internal ring-oscillator frequency can be determined. */
        uint64_t cnt1                  : 16; /**< [ 31: 16](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was high.
                                                                 When used with [CNT0] the internal ring-oscillator frequency can be determined. */
        uint64_t pcycle                : 16; /**< [ 47: 32](RO/H) Previous cycle count.  Sum of last [CNT0] and [CNT1]. */
        uint64_t reserved_48_62        : 15;
        uint64_t range                 : 1;  /**< [ 63: 63](RO/H) Reference ever out of range. Set when either:
                                                                 * Reference clock was outside operating range of 25 to 100 MHz.
                                                                 * Reference clock increased or decreased in frequency. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_ref_check_s cn8; */
    struct bdk_rst_ref_check_cn81xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t range                 : 1;  /**< [ 63: 63](RO/H) Reference ever out of range. Set when either:
                                                                 * Reference clock was outside operating range of 25 to 100 MHz.
                                                                 * Reference clock increased or decreased in frequency. */
        uint64_t reserved_48_62        : 15;
        uint64_t reserved_32_47        : 16;
        uint64_t cnt1                  : 16; /**< [ 31: 16](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was high.
                                                                 When used with [CNT0] the internal ring-oscillator frequency can be determined. */
        uint64_t cnt0                  : 16; /**< [ 15:  0](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was low.
                                                                 When used with [CNT1] the internal ring-oscillator frequency can be determined. */
#else /* Word 0 - Little Endian */
        uint64_t cnt0                  : 16; /**< [ 15:  0](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was low.
                                                                 When used with [CNT1] the internal ring-oscillator frequency can be determined. */
        uint64_t cnt1                  : 16; /**< [ 31: 16](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was high.
                                                                 When used with [CNT0] the internal ring-oscillator frequency can be determined. */
        uint64_t reserved_32_47        : 16;
        uint64_t reserved_48_62        : 15;
        uint64_t range                 : 1;  /**< [ 63: 63](RO/H) Reference ever out of range. Set when either:
                                                                 * Reference clock was outside operating range of 25 to 100 MHz.
                                                                 * Reference clock increased or decreased in frequency. */
#endif /* Word 0 - End */
    } cn81xx;
    /* struct bdk_rst_ref_check_s cn83xx; */
    struct bdk_rst_ref_check_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t range                 : 1;  /**< [ 63: 63](RO/H) Reference ever out of range. Set when either:
                                                                 * Reference clock was outside operating range of 85 to 115 MHz.
                                                                 * Reference increased or decreased in frequency.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t reserved_48_62        : 15;
        uint64_t pcycle                : 16; /**< [ 47: 32](RO/H) Previous cycle count. Sum of last [CNT0] and [CNT1]. */
        uint64_t cnt1                  : 16; /**< [ 31: 16](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was high.
                                                                 When used with [CNT0] the internal ring-oscillator frequency can be determined.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t cnt0                  : 16; /**< [ 15:  0](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was low.
                                                                 When used with [CNT1] the internal ring-oscillator frequency can be determined.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
#else /* Word 0 - Little Endian */
        uint64_t cnt0                  : 16; /**< [ 15:  0](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was low.
                                                                 When used with [CNT1] the internal ring-oscillator frequency can be determined.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t cnt1                  : 16; /**< [ 31: 16](RO/H) Number of internal ring-oscillator clock pulses counted over 16 reference clocks
                                                                 while reference clock was high.
                                                                 When used with [CNT0] the internal ring-oscillator frequency can be determined.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
        uint64_t pcycle                : 16; /**< [ 47: 32](RO/H) Previous cycle count. Sum of last [CNT0] and [CNT1]. */
        uint64_t reserved_48_62        : 15;
        uint64_t range                 : 1;  /**< [ 63: 63](RO/H) Reference ever out of range. Set when either:
                                                                 * Reference clock was outside operating range of 85 to 115 MHz.
                                                                 * Reference increased or decreased in frequency.

                                                                 This field is reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 This field is reinitialized on the falling edge of dcok. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_ref_check bdk_rst_ref_check_t;

#define BDK_RST_REF_CHECK BDK_RST_REF_CHECK_FUNC()
static inline uint64_t BDK_RST_REF_CHECK_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_REF_CHECK_FUNC(void)
{
    return 0x87e006001770ll;
}

#define typedef_BDK_RST_REF_CHECK bdk_rst_ref_check_t
#define bustype_BDK_RST_REF_CHECK BDK_CSR_TYPE_RSL
#define basename_BDK_RST_REF_CHECK "RST_REF_CHECK"
#define device_bar_BDK_RST_REF_CHECK 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_REF_CHECK 0
#define arguments_BDK_RST_REF_CHECK -1,-1,-1,-1

/**
 * Register (RSL) rst_ref_cntr
 *
 * RST Reference-Counter Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_ref_cntr
{
    uint64_t u;
    struct bdk_rst_ref_cntr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Count. The counter is initialized to 0x0 during a cold reset and is otherwise continuously
                                                                 running.
                                                                 CNT is incremented every reference-clock cycle (i.e. at 50 MHz). */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Count. The counter is initialized to 0x0 during a cold reset and is otherwise continuously
                                                                 running.
                                                                 CNT is incremented every reference-clock cycle (i.e. at 50 MHz). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_ref_cntr_s cn8; */
    struct bdk_rst_ref_cntr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Reference count. [CNT] is incremented every 100 MHz reference clock.
                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 64; /**< [ 63:  0](R/W/H) Reference count. [CNT] is incremented every 100 MHz reference clock.
                                                                 This field is always reinitialized on a cold domain reset. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_ref_cntr bdk_rst_ref_cntr_t;

#define BDK_RST_REF_CNTR BDK_RST_REF_CNTR_FUNC()
static inline uint64_t BDK_RST_REF_CNTR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_REF_CNTR_FUNC(void)
{
    return 0x87e006001758ll;
}

#define typedef_BDK_RST_REF_CNTR bdk_rst_ref_cntr_t
#define bustype_BDK_RST_REF_CNTR BDK_CSR_TYPE_RSL
#define basename_BDK_RST_REF_CNTR "RST_REF_CNTR"
#define device_bar_BDK_RST_REF_CNTR 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_REF_CNTR 0
#define arguments_BDK_RST_REF_CNTR -1,-1,-1,-1

/**
 * Register (RSL) rst_refc_ctl
 *
 * RST Common Reference Clock Input Control Register
 * This register is accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_refc_ctl
{
    uint64_t u;
    struct bdk_rst_refc_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t cclk2_sel             : 2;  /**< [  8:  7](R/W) Common clock 2 termination select.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = HCSL termination.

                                                                 The field is initialized on a cold domain reset. */
        uint64_t cclk2_pwdn            : 1;  /**< [  6:  6](R/W) Common clock 2 receiver power down.
                                                                 When set, receiver is powered down.
                                                                 The field is initialized on a cold domain reset.

                                                                 Internal:
                                                                 The receiver is also forced into powerdown when jtg__rst_pll.iddq_mode is set. */
        uint64_t cclk1_sel             : 2;  /**< [  5:  4](R/W) Common clock 1 termination select.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = HCSL termination.

                                                                 The field is initialized on a cold domain reset. */
        uint64_t cclk1_pwdn            : 1;  /**< [  3:  3](R/W) Common clock 1 receiver power down.
                                                                 When set, receiver is powered down.
                                                                 The field is initialized on a cold domain reset.

                                                                 Internal:
                                                                 The receiver is also forced into powerdown when jtg__rst_pll.iddq_mode is set. */
        uint64_t cclk0_sel             : 2;  /**< [  2:  1](RO/H) Common clock 0 termination select determined by hardware.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = HCSL termination.

                                                                 The value is determined at DC_OK assertion from the straps
                                                                 GPIO_STRAP_PIN_E::GSER_CLK0_TERM_SEL0 and 1. */
        uint64_t cclk0_pwdn            : 1;  /**< [  0:  0](RAZ) Common clock 0 receiver power down.
                                                                 Never powered down.  Reads as zero. */
#else /* Word 0 - Little Endian */
        uint64_t cclk0_pwdn            : 1;  /**< [  0:  0](RAZ) Common clock 0 receiver power down.
                                                                 Never powered down.  Reads as zero. */
        uint64_t cclk0_sel             : 2;  /**< [  2:  1](RO/H) Common clock 0 termination select determined by hardware.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = HCSL termination.

                                                                 The value is determined at DC_OK assertion from the straps
                                                                 GPIO_STRAP_PIN_E::GSER_CLK0_TERM_SEL0 and 1. */
        uint64_t cclk1_pwdn            : 1;  /**< [  3:  3](R/W) Common clock 1 receiver power down.
                                                                 When set, receiver is powered down.
                                                                 The field is initialized on a cold domain reset.

                                                                 Internal:
                                                                 The receiver is also forced into powerdown when jtg__rst_pll.iddq_mode is set. */
        uint64_t cclk1_sel             : 2;  /**< [  5:  4](R/W) Common clock 1 termination select.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = HCSL termination.

                                                                 The field is initialized on a cold domain reset. */
        uint64_t cclk2_pwdn            : 1;  /**< [  6:  6](R/W) Common clock 2 receiver power down.
                                                                 When set, receiver is powered down.
                                                                 The field is initialized on a cold domain reset.

                                                                 Internal:
                                                                 The receiver is also forced into powerdown when jtg__rst_pll.iddq_mode is set. */
        uint64_t cclk2_sel             : 2;  /**< [  8:  7](R/W) Common clock 2 termination select.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = HCSL termination.

                                                                 The field is initialized on a cold domain reset. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_refc_ctl_s cn9; */
    /* struct bdk_rst_refc_ctl_s cn96xxp1; */
    struct bdk_rst_refc_ctl_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t cclk2_sel             : 2;  /**< [  8:  7](R/W) Reserved.  See GSERR()_COMMON_PHY_CTRL_BCFG[REFCLK_HIZ_ENA]. */
        uint64_t cclk2_pwdn            : 1;  /**< [  6:  6](R/W) Reserved.  See GSERR()_COMMON_PHY_CTRL_BCFG[REFCLK_PAD_ENA]. */
        uint64_t cclk1_sel             : 2;  /**< [  5:  4](R/W) Reserved.  See GSERP()_COMMON_PHY_CTRL_BCFG[REFCLK_HIZ_ENA]. */
        uint64_t cclk1_pwdn            : 1;  /**< [  3:  3](R/W) Reserved.  See GSERP()_COMMON_PHY_CTRL_BCFG[REFCLK_PAD_ENA]. */
        uint64_t cclk0_sel             : 2;  /**< [  2:  1](RO/H) Common clock 0 termination select determined by hardware.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved.

                                                                 The value is determined at DC_OK assertion from the straps
                                                                 GPIO_STRAP_PIN_E::GSER_CLK0_TERM_SEL0 and 1. */
        uint64_t cclk0_pwdn            : 1;  /**< [  0:  0](RAZ) Common clock 0 receiver power down.
                                                                 Never powered down.  Reads as zero. */
#else /* Word 0 - Little Endian */
        uint64_t cclk0_pwdn            : 1;  /**< [  0:  0](RAZ) Common clock 0 receiver power down.
                                                                 Never powered down.  Reads as zero. */
        uint64_t cclk0_sel             : 2;  /**< [  2:  1](RO/H) Common clock 0 termination select determined by hardware.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved.

                                                                 The value is determined at DC_OK assertion from the straps
                                                                 GPIO_STRAP_PIN_E::GSER_CLK0_TERM_SEL0 and 1. */
        uint64_t cclk1_pwdn            : 1;  /**< [  3:  3](R/W) Reserved.  See GSERP()_COMMON_PHY_CTRL_BCFG[REFCLK_PAD_ENA]. */
        uint64_t cclk1_sel             : 2;  /**< [  5:  4](R/W) Reserved.  See GSERP()_COMMON_PHY_CTRL_BCFG[REFCLK_HIZ_ENA]. */
        uint64_t cclk2_pwdn            : 1;  /**< [  6:  6](R/W) Reserved.  See GSERR()_COMMON_PHY_CTRL_BCFG[REFCLK_PAD_ENA]. */
        uint64_t cclk2_sel             : 2;  /**< [  8:  7](R/W) Reserved.  See GSERR()_COMMON_PHY_CTRL_BCFG[REFCLK_HIZ_ENA]. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_refc_ctl_cn96xxp3 cn98xx; */
    /* struct bdk_rst_refc_ctl_s cnf95xxp1; */
    struct bdk_rst_refc_ctl_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t cclk2_sel             : 2;  /**< [  8:  7](R/W) Reserved. */
        uint64_t cclk2_pwdn            : 1;  /**< [  6:  6](R/W) Reserved. */
        uint64_t cclk1_sel             : 2;  /**< [  5:  4](R/W) Reserved. */
        uint64_t cclk1_pwdn            : 1;  /**< [  3:  3](R/W) Reserved. */
        uint64_t cclk0_sel             : 2;  /**< [  2:  1](RO/H) Common clock 0 termination select determined by hardware.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved.

                                                                 The value is determined at DC_OK assertion from the straps
                                                                 GPIO_STRAP_PIN_E::GSER_CLK0_TERM_SEL0 and 1. */
        uint64_t cclk0_pwdn            : 1;  /**< [  0:  0](RAZ) Common clock 0 receiver power down.
                                                                 Never powered down.  Reads as zero. */
#else /* Word 0 - Little Endian */
        uint64_t cclk0_pwdn            : 1;  /**< [  0:  0](RAZ) Common clock 0 receiver power down.
                                                                 Never powered down.  Reads as zero. */
        uint64_t cclk0_sel             : 2;  /**< [  2:  1](RO/H) Common clock 0 termination select determined by hardware.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved.

                                                                 The value is determined at DC_OK assertion from the straps
                                                                 GPIO_STRAP_PIN_E::GSER_CLK0_TERM_SEL0 and 1. */
        uint64_t cclk1_pwdn            : 1;  /**< [  3:  3](R/W) Reserved. */
        uint64_t cclk1_sel             : 2;  /**< [  5:  4](R/W) Reserved. */
        uint64_t cclk2_pwdn            : 1;  /**< [  6:  6](R/W) Reserved. */
        uint64_t cclk2_sel             : 2;  /**< [  8:  7](R/W) Reserved. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } cnf95xxp2;
    struct bdk_rst_refc_ctl_loki
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t cclk2_sel             : 2;  /**< [  8:  7](R/W) Reserved.  See GSERR/GSERC()_COMMON_PHY_CTRL_BCFG[REFCLK_HIZ_ENA]. */
        uint64_t cclk2_pwdn            : 1;  /**< [  6:  6](R/W) Reserved.  See GSERR/GSERC()_COMMON_PHY_CTRL_BCFG[REFCLK_PAD_ENA]. */
        uint64_t cclk1_sel             : 2;  /**< [  5:  4](R/W) Reserved.  See GSERP()_COMMON_PHY_CTRL_BCFG[REFCLK_HIZ_ENA]. */
        uint64_t cclk1_pwdn            : 1;  /**< [  3:  3](R/W) Reserved.  See GSERP()_COMMON_PHY_CTRL_BCFG[REFCLK_PAD_ENA]. */
        uint64_t cclk0_sel             : 2;  /**< [  2:  1](RO/H) Common clock 0 termination select determined by hardware.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved.

                                                                 The value is determined at DC_OK assertion from the straps
                                                                 GPIO_STRAP_PIN_E::GSER_CLK0_TERM_SEL0 and 1. */
        uint64_t cclk0_pwdn            : 1;  /**< [  0:  0](RAZ) Common clock 0 receiver power down.
                                                                 Never powered down.  Reads as zero. */
#else /* Word 0 - Little Endian */
        uint64_t cclk0_pwdn            : 1;  /**< [  0:  0](RAZ) Common clock 0 receiver power down.
                                                                 Never powered down.  Reads as zero. */
        uint64_t cclk0_sel             : 2;  /**< [  2:  1](RO/H) Common clock 0 termination select determined by hardware.
                                                                 0x0 = No termination.
                                                                 0x1 = LVPECL termination.
                                                                 0x2 = Reserved.
                                                                 0x3 = Reserved.

                                                                 The value is determined at DC_OK assertion from the straps
                                                                 GPIO_STRAP_PIN_E::GSER_CLK0_TERM_SEL0 and 1. */
        uint64_t cclk1_pwdn            : 1;  /**< [  3:  3](R/W) Reserved.  See GSERP()_COMMON_PHY_CTRL_BCFG[REFCLK_PAD_ENA]. */
        uint64_t cclk1_sel             : 2;  /**< [  5:  4](R/W) Reserved.  See GSERP()_COMMON_PHY_CTRL_BCFG[REFCLK_HIZ_ENA]. */
        uint64_t cclk2_pwdn            : 1;  /**< [  6:  6](R/W) Reserved.  See GSERR/GSERC()_COMMON_PHY_CTRL_BCFG[REFCLK_PAD_ENA]. */
        uint64_t cclk2_sel             : 2;  /**< [  8:  7](R/W) Reserved.  See GSERR/GSERC()_COMMON_PHY_CTRL_BCFG[REFCLK_HIZ_ENA]. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } loki;
};
typedef union bdk_rst_refc_ctl bdk_rst_refc_ctl_t;

#define BDK_RST_REFC_CTL BDK_RST_REFC_CTL_FUNC()
static inline uint64_t BDK_RST_REFC_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_REFC_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e00a001798ll;
    __bdk_csr_fatal("RST_REFC_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_REFC_CTL bdk_rst_refc_ctl_t
#define bustype_BDK_RST_REFC_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_REFC_CTL "RST_REFC_CTL"
#define device_bar_BDK_RST_REFC_CTL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_REFC_CTL 0
#define arguments_BDK_RST_REFC_CTL -1,-1,-1,-1

/**
 * Register (RSL) rst_reset_active
 *
 * RST Domain Reset Active Status Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_reset_active
{
    uint64_t u;
    struct bdk_rst_reset_active_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t bphy                  : 1;  /**< [  4:  4](RO/H) BPHY domain reset status.  When set, BPHY domain is in reset.
                                                                 Default reset value is one after a chip or core reset. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain reset status.  When set, SCP domain is in reset.
                                                                 Default reset value is zero after a chip reset. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain reset status.  When set, MCP domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain reset status.  When set, core domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t chip                  : 1;  /**< [  0:  0](RO/H) Chip domain reset status.  Always reads 0. */
#else /* Word 0 - Little Endian */
        uint64_t chip                  : 1;  /**< [  0:  0](RO/H) Chip domain reset status.  Always reads 0. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain reset status.  When set, core domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain reset status.  When set, MCP domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain reset status.  When set, SCP domain is in reset.
                                                                 Default reset value is zero after a chip reset. */
        uint64_t bphy                  : 1;  /**< [  4:  4](RO/H) BPHY domain reset status.  When set, BPHY domain is in reset.
                                                                 Default reset value is one after a chip or core reset. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_reset_active_s cn9; */
    struct bdk_rst_reset_active_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain reset status.  When set, SCP domain is in reset.
                                                                 Default reset value is zero after a chip reset. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain reset status.  When set, MCP domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain reset status.  When set, core domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain reset status.  When set, core domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain reset status.  When set, MCP domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain reset status.  When set, SCP domain is in reset.
                                                                 Default reset value is zero after a chip reset. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_rst_reset_active_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain reset status.  When set, SCP domain is in reset.
                                                                 Default reset value is zero after a chip reset. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain reset status.  When set, MCP domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain reset status.  When set, core domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t chip                  : 1;  /**< [  0:  0](RO/H) Chip domain reset status.  Always reads 0. */
#else /* Word 0 - Little Endian */
        uint64_t chip                  : 1;  /**< [  0:  0](RO/H) Chip domain reset status.  Always reads 0. */
        uint64_t core                  : 1;  /**< [  1:  1](RO/H) Core domain reset status.  When set, core domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t mcp                   : 1;  /**< [  2:  2](RO/H) MCP domain reset status.  When set, MCP domain is in reset.
                                                                 Default reset value is one after a chip reset. */
        uint64_t scp                   : 1;  /**< [  3:  3](RO/H) SCP domain reset status.  When set, SCP domain is in reset.
                                                                 Default reset value is zero after a chip reset. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_rst_reset_active_cn96xxp3 cn98xx; */
    /* struct bdk_rst_reset_active_s cnf95xx; */
    /* struct bdk_rst_reset_active_s loki; */
};
typedef union bdk_rst_reset_active bdk_rst_reset_active_t;

#define BDK_RST_RESET_ACTIVE BDK_RST_RESET_ACTIVE_FUNC()
static inline uint64_t BDK_RST_RESET_ACTIVE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_RESET_ACTIVE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001888ll;
    __bdk_csr_fatal("RST_RESET_ACTIVE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_RESET_ACTIVE bdk_rst_reset_active_t
#define bustype_BDK_RST_RESET_ACTIVE BDK_CSR_TYPE_RSL
#define basename_BDK_RST_RESET_ACTIVE "RST_RESET_ACTIVE"
#define device_bar_BDK_RST_RESET_ACTIVE 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_RESET_ACTIVE 0
#define arguments_BDK_RST_RESET_ACTIVE -1,-1,-1,-1

/**
 * Register (RSL) rst_rxp_pll
 *
 * RST Regular Expression Clock PLL Control Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_rxp_pll
{
    uint64_t u;
    struct bdk_rst_rxp_pll_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) RXP clockout select.
                                                                   0x0 = RXP clock divided by 32.
                                                                   0x1 = RXP clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) RXP clockout reset. The RXP clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) RXP PLL1 power down.  When set PLL is currently powered down. */
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) RXP PLL0 power down.  When set PLL is currently powered down. */
        uint64_t reserved_23_29        : 7;
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) RXP clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[RXP_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) RXP PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[RXP_MAX_MUL] and
                                                                 a minimum setting of 200 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) RXP clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[RXP_MAX_MUL]. */
#else /* Word 0 - Little Endian */
        uint64_t cur_mul               : 7;  /**< [  6:  0](RO/H) RXP clock frequency.  Actual frequency is [CUR_MUL] * 50 MHz.
                                                                 Value will reflect [NXT_MUL] after [DLY_SWITCH] has completed or [INIT_MUL]
                                                                 immediately after a cold or chip domain reset.  In both cases, value
                                                                 is limited by RST_PLL_LIMIT[RXP_MAX_MUL]. */
        uint64_t active_pll            : 1;  /**< [  7:  7](RO) Indicates which physical PLL is in use. For diagnostic use only. */
        uint64_t nxt_mul               : 7;  /**< [ 14:  8](R/W) RXP PLL frequency to be program in 50 MHz increments.  The
                                                                 actual value used is limited by RST_PLL_LIMIT[RXP_MAX_MUL] and
                                                                 a minimum setting of 200 MHz.
                                                                 Value will match [INIT_MUL] immediately after a cold or chip domain reset. */
        uint64_t nxt_pgm               : 1;  /**< [ 15: 15](R/W/H) Program non-active PLL using [NXT_MUL]. Hardware automatically
                                                                 clears bit when both PLL is updated and any delay specified
                                                                 in [DLY_SWITCH] has completed.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t init_mul              : 7;  /**< [ 22: 16](R/W) RXP clock multiplier to be used during a core or chip domain
                                                                 reset.  Actual frequency is [INIT_MUL] * 50 MHz.  The actual value
                                                                 used is limited by RST_PLL_LIMIT[RXP_MAX_MUL].
                                                                 This field maintains its current value when written with a zero.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_23_29        : 7;
        uint64_t pll0_pd               : 1;  /**< [ 30: 30](RO) RXP PLL0 power down.  When set PLL is currently powered down. */
        uint64_t pll1_pd               : 1;  /**< [ 31: 31](RO) RXP PLL1 power down.  When set PLL is currently powered down. */
        uint64_t dly_switch            : 12; /**< [ 43: 32](R/W/H) Switch the active PLL after delaying this number of 100 MHz clocks.
                                                                 When set to a nonzero value, the hardware will wait for
                                                                 any PLL programming to complete and then switch to the inactive
                                                                 PLL after the specified number of PLL reference clocks. Hardware
                                                                 will add additional clocks if required.
                                                                 This field is always reinitialized on a cold domain reset.

                                                                 Internal:
                                                                 Hardware will add counts to maintain 256 rxp_clk/cpt_clk/sclk/rclk notification to
                                                                 hardware.  Additional time will be added to wake up powered-down AP cores but that
                                                                 time not be included in this count. */
        uint64_t pd_switch             : 1;  /**< [ 44: 44](R/W) PLL powerdown on switch.  When set, hardware automatically
                                                                 powers down the inactive PLL after the switch has occurred.
                                                                 When cleared, the inactive PLL remains in operation.
                                                                 If [PD_SWITCH] is written to a one while both [DLY_SWITCH] and
                                                                 [NXT_PGM] are cleared then the inactive PLL will immediately powerdown.

                                                                 Note that a powered-down PLL requires an additional 575 reference
                                                                 clocks to become active.  This time is automatically added by the
                                                                 hardware.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_45_47        : 3;
        uint64_t cout_reset            : 1;  /**< [ 48: 48](R/W) RXP clockout reset. The RXP clockout should be placed in
                                                                 reset at least 10 PLL reference clocks prior
                                                                 to changing [COUT_SEL]. It should remain under reset for at least 10
                                                                 PLL reference clocks after [COUT_SEL] changes.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t cout_sel              : 2;  /**< [ 50: 49](R/W) RXP clockout select.
                                                                   0x0 = RXP clock divided by 32.
                                                                   0x1 = RXP clock tree output divided by 32.
                                                                   0x2 = PLL0 output divided by 32.
                                                                   0x3 = PLL1 output divided by 32.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_rxp_pll_s cn; */
};
typedef union bdk_rst_rxp_pll bdk_rst_rxp_pll_t;

#define BDK_RST_RXP_PLL BDK_RST_RXP_PLL_FUNC()
static inline uint64_t BDK_RST_RXP_PLL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_RXP_PLL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN98XX))
        return 0x87e00a0017a8ll;
    __bdk_csr_fatal("RST_RXP_PLL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_RXP_PLL bdk_rst_rxp_pll_t
#define bustype_BDK_RST_RXP_PLL BDK_CSR_TYPE_RSL
#define basename_BDK_RST_RXP_PLL "RST_RXP_PLL"
#define device_bar_BDK_RST_RXP_PLL 0x2 /* PF_BAR2 */
#define busnum_BDK_RST_RXP_PLL 0
#define arguments_BDK_RST_RXP_PLL -1,-1,-1,-1

/**
 * Register (RSL) rst_scp_domain_w1c
 *
 * RST SCP Domain Soft Reset Clear Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_scp_domain_w1c
{
    uint64_t u;
    struct bdk_rst_scp_domain_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear software-initiated reset of the SCP processor and associated logic.
                                                                 When set to one, the soft reset of the SCP is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual SCP domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[SCP] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[SCP] is set.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1C/H) Clear software-initiated reset of the SCP processor and associated logic.
                                                                 When set to one, the soft reset of the SCP is removed.
                                                                 Reads of this register show the soft reset state.  Not the actual SCP domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[SCP] shows
                                                                 the actual reset state.  To compensate for delays in reset, this field should only
                                                                 be set if RST_RESET_ACTIVE[SCP] is set.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_scp_domain_w1c_s cn; */
};
typedef union bdk_rst_scp_domain_w1c bdk_rst_scp_domain_w1c_t;

#define BDK_RST_SCP_DOMAIN_W1C BDK_RST_SCP_DOMAIN_W1C_FUNC()
static inline uint64_t BDK_RST_SCP_DOMAIN_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_SCP_DOMAIN_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001848ll;
    __bdk_csr_fatal("RST_SCP_DOMAIN_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_SCP_DOMAIN_W1C bdk_rst_scp_domain_w1c_t
#define bustype_BDK_RST_SCP_DOMAIN_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_RST_SCP_DOMAIN_W1C "RST_SCP_DOMAIN_W1C"
#define device_bar_BDK_RST_SCP_DOMAIN_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_SCP_DOMAIN_W1C 0
#define arguments_BDK_RST_SCP_DOMAIN_W1C -1,-1,-1,-1

/**
 * Register (RSL) rst_scp_domain_w1s
 *
 * RST SCP Domain Soft Reset Set Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_scp_domain_w1s
{
    uint64_t u;
    struct bdk_rst_scp_domain_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Set software-initiated reset of SCP core and associated logic.
                                                                 When set to one, all logic associated with the SCP domain is placed in reset.
                                                                 If RST_BOOT[RBOOT] is set, the SCP soft reset will stay asserted until
                                                                 RST_SCP_DOMAIN_W1C is written.  Otherwise it will automatically deassert.
                                                                 Reads of this register show the soft reset state.  Not the actual SCP domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[SCP] shows
                                                                 the actual reset state.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](R/W1S/H) Set software-initiated reset of SCP core and associated logic.
                                                                 When set to one, all logic associated with the SCP domain is placed in reset.
                                                                 If RST_BOOT[RBOOT] is set, the SCP soft reset will stay asserted until
                                                                 RST_SCP_DOMAIN_W1C is written.  Otherwise it will automatically deassert.
                                                                 Reads of this register show the soft reset state.  Not the actual SCP domain reset.
                                                                 Other factors may keep the reset active, reading RST_RESET_ACTIVE[SCP] shows
                                                                 the actual reset state.
                                                                 This field is always reinitialized on a chip domain reset. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_scp_domain_w1s_s cn; */
};
typedef union bdk_rst_scp_domain_w1s bdk_rst_scp_domain_w1s_t;

#define BDK_RST_SCP_DOMAIN_W1S BDK_RST_SCP_DOMAIN_W1S_FUNC()
static inline uint64_t BDK_RST_SCP_DOMAIN_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_SCP_DOMAIN_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001840ll;
    __bdk_csr_fatal("RST_SCP_DOMAIN_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_SCP_DOMAIN_W1S bdk_rst_scp_domain_w1s_t
#define bustype_BDK_RST_SCP_DOMAIN_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_RST_SCP_DOMAIN_W1S "RST_SCP_DOMAIN_W1S"
#define device_bar_BDK_RST_SCP_DOMAIN_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_SCP_DOMAIN_W1S 0
#define arguments_BDK_RST_SCP_DOMAIN_W1S -1,-1,-1,-1

/**
 * Register (RSL) rst_soft_prst#
 *
 * RST PCIe Soft Reset Registers
 * This register is accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_soft_prstx
{
    uint64_t u;
    struct bdk_rst_soft_prstx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_prst             : 1;  /**< [  0:  0](R/W) Soft PCIe reset. Resets the PCIe logic and corresponding common logic associated with the
                                                                 SLI controller in
                                                                 all modes, not just RC mode.
                                                                 * If RST_CTL()[HOST_MODE] = 0, [SOFT_PRST] resets to 0.
                                                                 * If RST_CTL()[HOST_MODE] = 1, [SOFT_PRST] resets to 1.

                                                                 When CNXXXX is configured to drive PERST*_L (i.e.
                                                                 RST_CTL()[RST_DRV] = 1), this controls the output value on PERST*_L.

                                                                 Internal:
                                                                 This bit is also forced high if the corresponding PEM Cripple Fuse is set. */
#else /* Word 0 - Little Endian */
        uint64_t soft_prst             : 1;  /**< [  0:  0](R/W) Soft PCIe reset. Resets the PCIe logic and corresponding common logic associated with the
                                                                 SLI controller in
                                                                 all modes, not just RC mode.
                                                                 * If RST_CTL()[HOST_MODE] = 0, [SOFT_PRST] resets to 0.
                                                                 * If RST_CTL()[HOST_MODE] = 1, [SOFT_PRST] resets to 1.

                                                                 When CNXXXX is configured to drive PERST*_L (i.e.
                                                                 RST_CTL()[RST_DRV] = 1), this controls the output value on PERST*_L.

                                                                 Internal:
                                                                 This bit is also forced high if the corresponding PEM Cripple Fuse is set. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_soft_prstx_s cn8; */
    struct bdk_rst_soft_prstx_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_prst             : 1;  /**< [  0:  0](R/W/H) Soft PCIe reset. Resets the PEM and corresponding GSER SerDes logic.
                                                                 This field is initialized as follows during cold domain resets:
                                                                 * If RST_CTL()[HOST_MODE] is clear, [SOFT_PRST] resets to 0.
                                                                 * If RST_CTL()[HOST_MODE] is set, [SOFT_PRST] resets to 1.

                                                                 It is set by hardware under three conditions:
                                                                 * If RST_CTL()[HOST_MODE] and the PEM domain is reset.
                                                                 * If RST_CTL()[PRST_LINK] is set and the link goes down.
                                                                 * If RST_CTL()[PRST_PWRDWN] is set and the PEM is powered down.

                                                                 When RST_CTL()[RST_DRV] is set, this controls the output value on PERST*_L.
                                                                 While RST_CTL()[RST_DRV] is set, hardware does not guarantee a minimum assertion time.
                                                                 Table 2-4 in section 2.6.2 of the PCIE CEM spec states that PERST*_L must be
                                                                 asserted for at least 100 us.

                                                                 In the endpoint case, the hardware requires that this signal be set for a
                                                                 minimum of 5 us to guarantee that the PCIe interface shuts down completely.

                                                                 These time period must be implemented by software.

                                                                 When RST_CTL()[RST_DRV] is clear and [SOFT_PRST] has been set by either hardware
                                                                 or software, a minimum assertion time of 2uS is required.

                                                                 Internal:
                                                                 This bit is also forced high if the corresponding PEM cripple fuse is set. */
#else /* Word 0 - Little Endian */
        uint64_t soft_prst             : 1;  /**< [  0:  0](R/W/H) Soft PCIe reset. Resets the PEM and corresponding GSER SerDes logic.
                                                                 This field is initialized as follows during cold domain resets:
                                                                 * If RST_CTL()[HOST_MODE] is clear, [SOFT_PRST] resets to 0.
                                                                 * If RST_CTL()[HOST_MODE] is set, [SOFT_PRST] resets to 1.

                                                                 It is set by hardware under three conditions:
                                                                 * If RST_CTL()[HOST_MODE] and the PEM domain is reset.
                                                                 * If RST_CTL()[PRST_LINK] is set and the link goes down.
                                                                 * If RST_CTL()[PRST_PWRDWN] is set and the PEM is powered down.

                                                                 When RST_CTL()[RST_DRV] is set, this controls the output value on PERST*_L.
                                                                 While RST_CTL()[RST_DRV] is set, hardware does not guarantee a minimum assertion time.
                                                                 Table 2-4 in section 2.6.2 of the PCIE CEM spec states that PERST*_L must be
                                                                 asserted for at least 100 us.

                                                                 In the endpoint case, the hardware requires that this signal be set for a
                                                                 minimum of 5 us to guarantee that the PCIe interface shuts down completely.

                                                                 These time period must be implemented by software.

                                                                 When RST_CTL()[RST_DRV] is clear and [SOFT_PRST] has been set by either hardware
                                                                 or software, a minimum assertion time of 2uS is required.

                                                                 Internal:
                                                                 This bit is also forced high if the corresponding PEM cripple fuse is set. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn9;
    /* struct bdk_rst_soft_prstx_cn9 cn96xx; */
    /* struct bdk_rst_soft_prstx_cn9 cnf95xxp1; */
    struct bdk_rst_soft_prstx_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_prst             : 1;  /**< [  0:  0](R/W/H) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Soft PCIe reset. Resets the PEM and corresponding GSER SerDes logic.
                                                                 This field is initialized as follows during cold domain resets:
                                                                 * If RST_CTL()[HOST_MODE] is clear, [SOFT_PRST] resets to 0.
                                                                 * If RST_CTL()[HOST_MODE] is set, [SOFT_PRST] resets to 1.

                                                                 It is set by hardware under three conditions:
                                                                 * If RST_CTL()[HOST_MODE] and the PEM domain is reset.
                                                                 * If RST_CTL()[PRST_LINK] is set and the link goes down.
                                                                 * If RST_CTL()[PRST_PWRDWN] is set and the PEM is powered down.

                                                                 When RST_CTL()[RST_DRV] is set, this controls the output value on PERST*_L.
                                                                 While RST_CTL()[RST_DRV] is set, hardware does not guarantee a minimum assertion time.
                                                                 Table 2-4 in section 2.6.2 of the PCIE CEM spec states that PERST*_L must be
                                                                 asserted for at least 100 us.

                                                                 In the endpoint case, the hardware requires that this signal be set for a
                                                                 minimum of 5 us to guarantee that the PCIe interface shuts down completely.

                                                                 These time period must be implemented by software.

                                                                 When RST_CTL()[RST_DRV] is clear and [SOFT_PRST] has been set by either hardware
                                                                 or software, a minimum assertion time of 2uS is required.
                                                                 This bit is also forced high if the corresponding PEM cripple fuse is set. */
#else /* Word 0 - Little Endian */
        uint64_t soft_prst             : 1;  /**< [  0:  0](R/W/H) Reserved.
                                                                 Internal:
                                                                 In pass A0, but PCI is defeatured.
                                                                 Soft PCIe reset. Resets the PEM and corresponding GSER SerDes logic.
                                                                 This field is initialized as follows during cold domain resets:
                                                                 * If RST_CTL()[HOST_MODE] is clear, [SOFT_PRST] resets to 0.
                                                                 * If RST_CTL()[HOST_MODE] is set, [SOFT_PRST] resets to 1.

                                                                 It is set by hardware under three conditions:
                                                                 * If RST_CTL()[HOST_MODE] and the PEM domain is reset.
                                                                 * If RST_CTL()[PRST_LINK] is set and the link goes down.
                                                                 * If RST_CTL()[PRST_PWRDWN] is set and the PEM is powered down.

                                                                 When RST_CTL()[RST_DRV] is set, this controls the output value on PERST*_L.
                                                                 While RST_CTL()[RST_DRV] is set, hardware does not guarantee a minimum assertion time.
                                                                 Table 2-4 in section 2.6.2 of the PCIE CEM spec states that PERST*_L must be
                                                                 asserted for at least 100 us.

                                                                 In the endpoint case, the hardware requires that this signal be set for a
                                                                 minimum of 5 us to guarantee that the PCIe interface shuts down completely.

                                                                 These time period must be implemented by software.

                                                                 When RST_CTL()[RST_DRV] is clear and [SOFT_PRST] has been set by either hardware
                                                                 or software, a minimum assertion time of 2uS is required.
                                                                 This bit is also forced high if the corresponding PEM cripple fuse is set. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cnf95xxp2;
};
typedef union bdk_rst_soft_prstx bdk_rst_soft_prstx_t;

static inline uint64_t BDK_RST_SOFT_PRSTX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_SOFT_PRSTX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=2))
        return 0x87e0060016c0ll + 8ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN83XX) && (a<=3))
        return 0x87e0060016c0ll + 8ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_X) && (a<=3))
        return 0x87e0060016c0ll + 8ll * ((a) & 0x3);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a==0))
        return 0x87e0060016c0ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("RST_SOFT_PRSTX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_SOFT_PRSTX(a) bdk_rst_soft_prstx_t
#define bustype_BDK_RST_SOFT_PRSTX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_RST_SOFT_PRSTX(a) "RST_SOFT_PRSTX"
#define device_bar_BDK_RST_SOFT_PRSTX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_SOFT_PRSTX(a) (a)
#define arguments_BDK_RST_SOFT_PRSTX(a) (a),-1,-1,-1

/**
 * Register (RSL) rst_soft_rst
 *
 * RST Soft Reset Register
 */
union bdk_rst_soft_rst
{
    uint64_t u;
    struct bdk_rst_soft_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t soft_rst              : 1;  /**< [  0:  0](WO) Soft reset. When set to 1, resets the CNXXXX core. When performing a soft reset from a
                                                                 remote PCIe host,
                                                                 always read this register and wait for the results before setting [SOFT_RST] to 1. */
#else /* Word 0 - Little Endian */
        uint64_t soft_rst              : 1;  /**< [  0:  0](WO) Soft reset. When set to 1, resets the CNXXXX core. When performing a soft reset from a
                                                                 remote PCIe host,
                                                                 always read this register and wait for the results before setting [SOFT_RST] to 1. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_soft_rst_s cn; */
};
typedef union bdk_rst_soft_rst bdk_rst_soft_rst_t;

#define BDK_RST_SOFT_RST BDK_RST_SOFT_RST_FUNC()
static inline uint64_t BDK_RST_SOFT_RST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_SOFT_RST_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x87e006001680ll;
    __bdk_csr_fatal("RST_SOFT_RST", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_SOFT_RST bdk_rst_soft_rst_t
#define bustype_BDK_RST_SOFT_RST BDK_CSR_TYPE_RSL
#define basename_BDK_RST_SOFT_RST "RST_SOFT_RST"
#define device_bar_BDK_RST_SOFT_RST 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_SOFT_RST 0
#define arguments_BDK_RST_SOFT_RST -1,-1,-1,-1

/**
 * Register (RSL) rst_src_map
 *
 * RST Source Domain Map Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_src_map
{
    uint64_t u;
    struct bdk_rst_src_map_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t ocx_to_chip           : 1;  /**< [ 12: 12](R/W) Reserved.
                                                                 Internal:
                                                                 OCX linkdown mapped to chip domain reset.
                                                                 When RST_OCX[RST_LINK] is set:
                                                                 0 = OCX transition from link up to link down will cause a core domain reset.
                                                                 1 = OCX transition from link up to link down will cause both a core domain reset
                                                                     and a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_11           : 1;
        uint64_t scp_to_mcp            : 1;  /**< [ 10: 10](R/W) SCP watchdog and pin resets mapped to MCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause an MCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_core           : 1;  /**< [  9:  9](R/W) SCP watchdog and pin resets mapped to core domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause a core domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_chip           : 1;  /**< [  8:  8](R/W) SCP watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t mcp_to_scp            : 1;  /**< [  7:  7](R/W) MCP watchdog and pin resets mapped to SCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause an SCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_6            : 1;
        uint64_t mcp_to_core           : 1;  /**< [  5:  5](R/W) MCP watchdog and pin resets mapped to core domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause a core domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t mcp_to_chip           : 1;  /**< [  4:  4](R/W) MCP watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t core_to_scp           : 1;  /**< [  3:  3](R/W) Core watchdog and pin resets mapped to SCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause an SCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t core_to_mcp           : 1;  /**< [  2:  2](R/W) Core watchdog and pin resets mapped to MCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause an MCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_1            : 1;
        uint64_t core_to_chip          : 1;  /**< [  0:  0](R/W) Core watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t core_to_chip          : 1;  /**< [  0:  0](R/W) Core watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_1            : 1;
        uint64_t core_to_mcp           : 1;  /**< [  2:  2](R/W) Core watchdog and pin resets mapped to MCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause an MCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t core_to_scp           : 1;  /**< [  3:  3](R/W) Core watchdog and pin resets mapped to SCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause an SCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t mcp_to_chip           : 1;  /**< [  4:  4](R/W) MCP watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t mcp_to_core           : 1;  /**< [  5:  5](R/W) MCP watchdog and pin resets mapped to core domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause a core domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_6            : 1;
        uint64_t mcp_to_scp            : 1;  /**< [  7:  7](R/W) MCP watchdog and pin resets mapped to SCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause an SCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_chip           : 1;  /**< [  8:  8](R/W) SCP watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_core           : 1;  /**< [  9:  9](R/W) SCP watchdog and pin resets mapped to core domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause a core domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_mcp            : 1;  /**< [ 10: 10](R/W) SCP watchdog and pin resets mapped to MCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause an MCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_11           : 1;
        uint64_t ocx_to_chip           : 1;  /**< [ 12: 12](R/W) Reserved.
                                                                 Internal:
                                                                 OCX linkdown mapped to chip domain reset.
                                                                 When RST_OCX[RST_LINK] is set:
                                                                 0 = OCX transition from link up to link down will cause a core domain reset.
                                                                 1 = OCX transition from link up to link down will cause both a core domain reset
                                                                     and a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_src_map_s cn9; */
    /* struct bdk_rst_src_map_s cn96xx; */
    /* struct bdk_rst_src_map_s cn98xx; */
    struct bdk_rst_src_map_cnf95xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t ocx_to_chip           : 1;  /**< [ 12: 12](R/W) Reserved.
                                                                 Internal:
                                                                 OCX linkdown mapped to chip domain reset.
                                                                 When RST_OCX[RST_LINK] is set:
                                                                   0 = OCX transition from link up to link down will cause a core domain reset.
                                                                   1 = OCX transition from link up to link down will cause both a core domain reset
                                                                   and a chip domain reset.

                                                                   This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_11           : 1;
        uint64_t scp_to_mcp            : 1;  /**< [ 10: 10](R/W) SCP watchdog and pin resets mapped to MCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause an MCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_core           : 1;  /**< [  9:  9](R/W) SCP watchdog and pin resets mapped to core domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause a core domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_chip           : 1;  /**< [  8:  8](R/W) SCP watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t mcp_to_scp            : 1;  /**< [  7:  7](R/W) MCP watchdog and pin resets mapped to SCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause an SCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_6            : 1;
        uint64_t mcp_to_core           : 1;  /**< [  5:  5](R/W) MCP watchdog and pin resets mapped to core domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause a core domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t mcp_to_chip           : 1;  /**< [  4:  4](R/W) MCP watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t core_to_scp           : 1;  /**< [  3:  3](R/W) Core watchdog and pin resets mapped to SCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause an SCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t core_to_mcp           : 1;  /**< [  2:  2](R/W) Core watchdog and pin resets mapped to MCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause an MCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_1            : 1;
        uint64_t core_to_chip          : 1;  /**< [  0:  0](R/W) Core watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t core_to_chip          : 1;  /**< [  0:  0](R/W) Core watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_1            : 1;
        uint64_t core_to_mcp           : 1;  /**< [  2:  2](R/W) Core watchdog and pin resets mapped to MCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause an MCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t core_to_scp           : 1;  /**< [  3:  3](R/W) Core watchdog and pin resets mapped to SCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = Core reset pin or the AP watchdog will additionally
                                                                     cause an SCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t mcp_to_chip           : 1;  /**< [  4:  4](R/W) MCP watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t mcp_to_core           : 1;  /**< [  5:  5](R/W) MCP watchdog and pin resets mapped to core domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause a core domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_6            : 1;
        uint64_t mcp_to_scp            : 1;  /**< [  7:  7](R/W) MCP watchdog and pin resets mapped to SCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = MCP reset pin or the MCP watchdog will additionally
                                                                     cause an SCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_chip           : 1;  /**< [  8:  8](R/W) SCP watchdog and pin resets mapped to chip domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause a chip domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_core           : 1;  /**< [  9:  9](R/W) SCP watchdog and pin resets mapped to core domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause a core domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t scp_to_mcp            : 1;  /**< [ 10: 10](R/W) SCP watchdog and pin resets mapped to MCP domain reset.
                                                                 0 = Mapping disabled.
                                                                 1 = SCP reset pin or the SCP watchdog will additionally
                                                                     cause an MCP domain reset.

                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_11           : 1;
        uint64_t ocx_to_chip           : 1;  /**< [ 12: 12](R/W) Reserved.
                                                                 Internal:
                                                                 OCX linkdown mapped to chip domain reset.
                                                                 When RST_OCX[RST_LINK] is set:
                                                                   0 = OCX transition from link up to link down will cause a core domain reset.
                                                                   1 = OCX transition from link up to link down will cause both a core domain reset
                                                                   and a chip domain reset.

                                                                   This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } cnf95xx;
    /* struct bdk_rst_src_map_cnf95xx loki; */
};
typedef union bdk_rst_src_map bdk_rst_src_map_t;

#define BDK_RST_SRC_MAP BDK_RST_SRC_MAP_FUNC()
static inline uint64_t BDK_RST_SRC_MAP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_SRC_MAP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e006001898ll;
    __bdk_csr_fatal("RST_SRC_MAP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_SRC_MAP bdk_rst_src_map_t
#define bustype_BDK_RST_SRC_MAP BDK_CSR_TYPE_RSL
#define basename_BDK_RST_SRC_MAP "RST_SRC_MAP"
#define device_bar_BDK_RST_SRC_MAP 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_SRC_MAP 0
#define arguments_BDK_RST_SRC_MAP -1,-1,-1,-1

/**
 * Register (RSL) rst_sw_w1s
 *
 * RST Software W1S Data Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_sw_w1s
{
    uint64_t u;
    struct bdk_rst_sw_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W1S) Data register that can be set by software and is only cleared
                                                                 on initialization.
                                                                 This field is always reinitialized on a chip domain reset. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W1S) Data register that can be set by software and is only cleared
                                                                 on initialization.
                                                                 This field is always reinitialized on a chip domain reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_sw_w1s_s cn; */
};
typedef union bdk_rst_sw_w1s bdk_rst_sw_w1s_t;

#define BDK_RST_SW_W1S BDK_RST_SW_W1S_FUNC()
static inline uint64_t BDK_RST_SW_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_SW_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e0060017f0ll;
    __bdk_csr_fatal("RST_SW_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_RST_SW_W1S bdk_rst_sw_w1s_t
#define bustype_BDK_RST_SW_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_RST_SW_W1S "RST_SW_W1S"
#define device_bar_BDK_RST_SW_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_SW_W1S 0
#define arguments_BDK_RST_SW_W1S -1,-1,-1,-1

/**
 * Register (RSL) rst_thermal_alert
 *
 * RST Thermal Alert Register
 * This register is not accessible through ROM scripts; see SCR_WRITE32_S[ADDR].
 */
union bdk_rst_thermal_alert
{
    uint64_t u;
    struct bdk_rst_thermal_alert_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t trip                  : 1;  /**< [  8:  8](R/W1S/H) Thermal trip pin. When set to 1, drives the THERMAL_TRIP_N pin active low. This field is
                                                                 set by either of the
                                                                 on-board temperature sensors reaching a failure threshold or writing this bit.
                                                                 The bit can only be cleared by a deassertion of the PLL_DC_OK pin which completely resets
                                                                 the chip. */
        uint64_t reserved_1_7          : 7;
        uint64_t alert                 : 1;  /**< [  0:  0](RO/H) Thermal alert status. When set to 1, indicates the temperature sensor is currently at the
                                                                 failure threshold. */
#else /* Word 0 - Little Endian */
        uint64_t alert                 : 1;  /**< [  0:  0](RO/H) Thermal alert status. When set to 1, indicates the temperature sensor is currently at the
                                                                 failure threshold. */
        uint64_t reserved_1_7          : 7;
        uint64_t trip                  : 1;  /**< [  8:  8](R/W1S/H) Thermal trip pin. When set to 1, drives the THERMAL_TRIP_N pin active low. This field is
                                                                 set by either of the
                                                                 on-board temperature sensors reaching a failure threshold or writing this bit.
                                                                 The bit can only be cleared by a deassertion of the PLL_DC_OK pin which completely resets
                                                                 the chip. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_rst_thermal_alert_s cn8; */
    struct bdk_rst_thermal_alert_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t trip                  : 1;  /**< [  8:  8](R/W1S/H) Thermal trip pin. When set, drives the THERMAL_TRIP_L pin active low.
                                                                 This field is set by one of the on-board temperature sensors reaching a
                                                                 failure threshold or writing this bit.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_1_7          : 7;
        uint64_t alert                 : 1;  /**< [  0:  0](RO/H) Thermal alert status. When set to one, indicates a temperature sensor is
                                                                 currently at the failure threshold. */
#else /* Word 0 - Little Endian */
        uint64_t alert                 : 1;  /**< [  0:  0](RO/H) Thermal alert status. When set to one, indicates a temperature sensor is
                                                                 currently at the failure threshold. */
        uint64_t reserved_1_7          : 7;
        uint64_t trip                  : 1;  /**< [  8:  8](R/W1S/H) Thermal trip pin. When set, drives the THERMAL_TRIP_L pin active low.
                                                                 This field is set by one of the on-board temperature sensors reaching a
                                                                 failure threshold or writing this bit.
                                                                 This field is always reinitialized on a cold domain reset. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_rst_thermal_alert bdk_rst_thermal_alert_t;

#define BDK_RST_THERMAL_ALERT BDK_RST_THERMAL_ALERT_FUNC()
static inline uint64_t BDK_RST_THERMAL_ALERT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_RST_THERMAL_ALERT_FUNC(void)
{
    return 0x87e006001690ll;
}

#define typedef_BDK_RST_THERMAL_ALERT bdk_rst_thermal_alert_t
#define bustype_BDK_RST_THERMAL_ALERT BDK_CSR_TYPE_RSL
#define basename_BDK_RST_THERMAL_ALERT "RST_THERMAL_ALERT"
#define device_bar_BDK_RST_THERMAL_ALERT 0x0 /* PF_BAR0 */
#define busnum_BDK_RST_THERMAL_ALERT 0
#define arguments_BDK_RST_THERMAL_ALERT -1,-1,-1,-1

#endif /* __BDK_CSRS_RST_H__ */
