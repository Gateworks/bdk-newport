#ifndef __BDK_CSRS_PSBM_H__
#define __BDK_CSRS_PSBM_H__
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
 * Cavium PSBM.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration psbm_bar_e
 *
 * PSBM Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_PSBM_BAR_E_PSBM_PF_BAR0 (0x87e0de000000ll)
#define BDK_PSBM_BAR_E_PSBM_PF_BAR0_SIZE 0x100000ull
#define BDK_PSBM_BAR_E_PSBM_PF_BAR2 (0x87e0df000000ll)
#define BDK_PSBM_BAR_E_PSBM_PF_BAR2_SIZE 0x1000000ull

/**
 * Enumeration psbm_sys_map_e
 *
 * PSBM SYS Slave Enumeration
 * Enumerates the PSB system slave identifiers.
 */
#define BDK_PSBM_SYS_MAP_E_CPT (0xd)
#define BDK_PSBM_SYS_MAP_E_GSERX(a) (5 + (a))
#define BDK_PSBM_SYS_MAP_E_IOBX(a) (3 + (a))
#define BDK_PSBM_SYS_MAP_E_LMCX(a) (0 + (a))

/**
 * Register (NCB32b) psbm_ap#_data#
 *
 * PSBM AP Slave Data Register
 * These registers contain the data captured by the last polling of the AP PSBS slaves.
 */
union bdk_psbm_apx_datax
{
    uint32_t u;
    struct bdk_psbm_apx_datax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W/H) Data read from the specified AP slave's register. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W/H) Data read from the specified AP slave's register. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_apx_datax_s cn; */
};
typedef union bdk_psbm_apx_datax bdk_psbm_apx_datax_t;

static inline uint64_t BDK_PSBM_APX_DATAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_APX_DATAX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=23) && (b<=5)))
        return 0x87e0de010000ll + 0x100ll * ((a) & 0x1f) + 0x10ll * ((b) & 0x7);
    __bdk_csr_fatal("PSBM_APX_DATAX", 2, a, b, 0, 0);
}

#define typedef_BDK_PSBM_APX_DATAX(a,b) bdk_psbm_apx_datax_t
#define bustype_BDK_PSBM_APX_DATAX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_APX_DATAX(a,b) "PSBM_APX_DATAX"
#define device_bar_BDK_PSBM_APX_DATAX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_APX_DATAX(a,b) (a)
#define arguments_BDK_PSBM_APX_DATAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) psbm_ap#_hdr
 *
 * PSBM AP Slave Header Register
 * These registers contain the header captured by the last polling of the AP PSBS
 * slaves. For diagnostic use only.
 */
union bdk_psbm_apx_hdr
{
    uint32_t u;
    struct bdk_psbm_apx_hdr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t cmd                   : 4;  /**< [ 31: 28](R/W/H) PSB command. */
        uint32_t psbs_id               : 8;  /**< [ 27: 20](R/W/H) PSBS slave ID. */
        uint32_t entries               : 4;  /**< [ 19: 16](R/W/H) Number of entries in the slave. */
        uint32_t ras                   : 16; /**< [ 15:  0](R/W/H) RAS capture data. */
#else /* Word 0 - Little Endian */
        uint32_t ras                   : 16; /**< [ 15:  0](R/W/H) RAS capture data. */
        uint32_t entries               : 4;  /**< [ 19: 16](R/W/H) Number of entries in the slave. */
        uint32_t psbs_id               : 8;  /**< [ 27: 20](R/W/H) PSBS slave ID. */
        uint32_t cmd                   : 4;  /**< [ 31: 28](R/W/H) PSB command. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_apx_hdr_s cn; */
};
typedef union bdk_psbm_apx_hdr bdk_psbm_apx_hdr_t;

static inline uint64_t BDK_PSBM_APX_HDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_APX_HDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x87e0de018000ll + 0x10ll * ((a) & 0x1f);
    __bdk_csr_fatal("PSBM_APX_HDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_PSBM_APX_HDR(a) bdk_psbm_apx_hdr_t
#define bustype_BDK_PSBM_APX_HDR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_APX_HDR(a) "PSBM_APX_HDR"
#define device_bar_BDK_PSBM_APX_HDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_APX_HDR(a) (a)
#define arguments_BDK_PSBM_APX_HDR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) psbm_const
 *
 * PSBM Constants Register
 * This register is for software discovery of PSBM features.
 */
union bdk_psbm_const
{
    uint32_t u;
    struct bdk_psbm_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ap_slaves             : 8;  /**< [ 31: 24](RO) Maximum number of AP slaves connected to PSBM. This number may exceed the number
                                                                 of cores implemented in a given SKU; software should access CSRs and expect
                                                                 results only for those slaves which are out of reset. */
        uint32_t ap_entries            : 8;  /**< [ 23: 16](RO) Number of 32-bit values in each AP slave. */
        uint32_t sys_slaves            : 8;  /**< [ 15:  8](RO) Maximum number of ROC chains connected to PSBM. */
        uint32_t sys_entries           : 8;  /**< [  7:  0](RO) Number of 32-bit values in each ROC slave. */
#else /* Word 0 - Little Endian */
        uint32_t sys_entries           : 8;  /**< [  7:  0](RO) Number of 32-bit values in each ROC slave. */
        uint32_t sys_slaves            : 8;  /**< [ 15:  8](RO) Maximum number of ROC chains connected to PSBM. */
        uint32_t ap_entries            : 8;  /**< [ 23: 16](RO) Number of 32-bit values in each AP slave. */
        uint32_t ap_slaves             : 8;  /**< [ 31: 24](RO) Maximum number of AP slaves connected to PSBM. This number may exceed the number
                                                                 of cores implemented in a given SKU; software should access CSRs and expect
                                                                 results only for those slaves which are out of reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_const_s cn; */
};
typedef union bdk_psbm_const bdk_psbm_const_t;

#define BDK_PSBM_CONST BDK_PSBM_CONST_FUNC()
static inline uint64_t BDK_PSBM_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_CONST_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0de000008ll;
    __bdk_csr_fatal("PSBM_CONST", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PSBM_CONST bdk_psbm_const_t
#define bustype_BDK_PSBM_CONST BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_CONST "PSBM_CONST"
#define device_bar_BDK_PSBM_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_CONST 0
#define arguments_BDK_PSBM_CONST -1,-1,-1,-1

/**
 * Register (NCB32b) psbm_const1
 *
 * PSBM Constants Register 1
 * PSBM Constant 1 values
 */
union bdk_psbm_const1
{
    uint32_t u;
    struct bdk_psbm_const1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_const1_s cn; */
};
typedef union bdk_psbm_const1 bdk_psbm_const1_t;

#define BDK_PSBM_CONST1 BDK_PSBM_CONST1_FUNC()
static inline uint64_t BDK_PSBM_CONST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_CONST1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0de000010ll;
    __bdk_csr_fatal("PSBM_CONST1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PSBM_CONST1 bdk_psbm_const1_t
#define bustype_BDK_PSBM_CONST1 BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_CONST1 "PSBM_CONST1"
#define device_bar_BDK_PSBM_CONST1 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_CONST1 0
#define arguments_BDK_PSBM_CONST1 -1,-1,-1,-1

/**
 * Register (NCB32b) psbm_ctl
 *
 * PSBM Control Register
 */
union bdk_psbm_ctl
{
    uint32_t u;
    struct bdk_psbm_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t done                  : 1;  /**< [ 31: 31](RO/H) Cleared by PSBM when software writes one to [START], and stays cleared until set
                                                                 by PSBM when data collection is complete. */
        uint32_t reserved_1_30         : 30;
        uint32_t start                 : 1;  /**< [  0:  0](WO) When written with one, start a poll of the PSB registers. */
#else /* Word 0 - Little Endian */
        uint32_t start                 : 1;  /**< [  0:  0](WO) When written with one, start a poll of the PSB registers. */
        uint32_t reserved_1_30         : 30;
        uint32_t done                  : 1;  /**< [ 31: 31](RO/H) Cleared by PSBM when software writes one to [START], and stays cleared until set
                                                                 by PSBM when data collection is complete. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_ctl_s cn; */
};
typedef union bdk_psbm_ctl bdk_psbm_ctl_t;

#define BDK_PSBM_CTL BDK_PSBM_CTL_FUNC()
static inline uint64_t BDK_PSBM_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0de000000ll;
    __bdk_csr_fatal("PSBM_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PSBM_CTL bdk_psbm_ctl_t
#define bustype_BDK_PSBM_CTL BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_CTL "PSBM_CTL"
#define device_bar_BDK_PSBM_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_CTL 0
#define arguments_BDK_PSBM_CTL -1,-1,-1,-1

/**
 * Register (NCB32b) psbm_eco
 *
 * INTERNAL: PSBM ECO Register
 */
union bdk_psbm_eco
{
    uint32_t u;
    struct bdk_psbm_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint32_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_eco_s cn; */
};
typedef union bdk_psbm_eco bdk_psbm_eco_t;

#define BDK_PSBM_ECO BDK_PSBM_ECO_FUNC()
static inline uint64_t BDK_PSBM_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_ECO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0de000018ll;
    __bdk_csr_fatal("PSBM_ECO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PSBM_ECO bdk_psbm_eco_t
#define bustype_BDK_PSBM_ECO BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_ECO "PSBM_ECO"
#define device_bar_BDK_PSBM_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_ECO 0
#define arguments_BDK_PSBM_ECO -1,-1,-1,-1

/**
 * Register (NCB32b) psbm_lint
 *
 * PSBM Interrupt Register
 */
union bdk_psbm_lint
{
    uint32_t u;
    struct bdk_psbm_lint_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wakeup                : 1;  /**< [  0:  0](R/W1C/H) PSB slave wakeup interrupt. */
#else /* Word 0 - Little Endian */
        uint32_t wakeup                : 1;  /**< [  0:  0](R/W1C/H) PSB slave wakeup interrupt. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_lint_s cn; */
};
typedef union bdk_psbm_lint bdk_psbm_lint_t;

#define BDK_PSBM_LINT BDK_PSBM_LINT_FUNC()
static inline uint64_t BDK_PSBM_LINT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_LINT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0de000020ll;
    __bdk_csr_fatal("PSBM_LINT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PSBM_LINT bdk_psbm_lint_t
#define bustype_BDK_PSBM_LINT BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_LINT "PSBM_LINT"
#define device_bar_BDK_PSBM_LINT 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_LINT 0
#define arguments_BDK_PSBM_LINT -1,-1,-1,-1

/**
 * Register (NCB32b) psbm_lint_ena_w1c
 *
 * PSBM Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_psbm_lint_ena_w1c
{
    uint32_t u;
    struct bdk_psbm_lint_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wakeup                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PSBM_LINT[WAKEUP]. */
#else /* Word 0 - Little Endian */
        uint32_t wakeup                : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PSBM_LINT[WAKEUP]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_lint_ena_w1c_s cn; */
};
typedef union bdk_psbm_lint_ena_w1c bdk_psbm_lint_ena_w1c_t;

#define BDK_PSBM_LINT_ENA_W1C BDK_PSBM_LINT_ENA_W1C_FUNC()
static inline uint64_t BDK_PSBM_LINT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_LINT_ENA_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0de000030ll;
    __bdk_csr_fatal("PSBM_LINT_ENA_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PSBM_LINT_ENA_W1C bdk_psbm_lint_ena_w1c_t
#define bustype_BDK_PSBM_LINT_ENA_W1C BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_LINT_ENA_W1C "PSBM_LINT_ENA_W1C"
#define device_bar_BDK_PSBM_LINT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_LINT_ENA_W1C 0
#define arguments_BDK_PSBM_LINT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB32b) psbm_lint_ena_w1s
 *
 * PSBM Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_psbm_lint_ena_w1s
{
    uint32_t u;
    struct bdk_psbm_lint_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wakeup                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PSBM_LINT[WAKEUP]. */
#else /* Word 0 - Little Endian */
        uint32_t wakeup                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PSBM_LINT[WAKEUP]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_lint_ena_w1s_s cn; */
};
typedef union bdk_psbm_lint_ena_w1s bdk_psbm_lint_ena_w1s_t;

#define BDK_PSBM_LINT_ENA_W1S BDK_PSBM_LINT_ENA_W1S_FUNC()
static inline uint64_t BDK_PSBM_LINT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_LINT_ENA_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0de000038ll;
    __bdk_csr_fatal("PSBM_LINT_ENA_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PSBM_LINT_ENA_W1S bdk_psbm_lint_ena_w1s_t
#define bustype_BDK_PSBM_LINT_ENA_W1S BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_LINT_ENA_W1S "PSBM_LINT_ENA_W1S"
#define device_bar_BDK_PSBM_LINT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_LINT_ENA_W1S 0
#define arguments_BDK_PSBM_LINT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB32b) psbm_lint_w1s
 *
 * PSBM Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_psbm_lint_w1s
{
    uint32_t u;
    struct bdk_psbm_lint_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wakeup                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PSBM_LINT[WAKEUP]. */
#else /* Word 0 - Little Endian */
        uint32_t wakeup                : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PSBM_LINT[WAKEUP]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_lint_w1s_s cn; */
};
typedef union bdk_psbm_lint_w1s bdk_psbm_lint_w1s_t;

#define BDK_PSBM_LINT_W1S BDK_PSBM_LINT_W1S_FUNC()
static inline uint64_t BDK_PSBM_LINT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_LINT_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0de000028ll;
    __bdk_csr_fatal("PSBM_LINT_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PSBM_LINT_W1S bdk_psbm_lint_w1s_t
#define bustype_BDK_PSBM_LINT_W1S BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_LINT_W1S "PSBM_LINT_W1S"
#define device_bar_BDK_PSBM_LINT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_LINT_W1S 0
#define arguments_BDK_PSBM_LINT_W1S -1,-1,-1,-1

/**
 * Register (NCB32b) psbm_sys#_data#
 *
 * PSBM ROC Data Register
 * These registers contain the data captured by the last polling of the SYS PSBS slaves.
 * Index {a} is enumerated by PSBM_SYS_MAP_E.
 */
union bdk_psbm_sysx_datax
{
    uint32_t u;
    struct bdk_psbm_sysx_datax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W/H) Data read from the specified ROC device's register. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W/H) Data read from the specified ROC device's register. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_sysx_datax_s cn; */
};
typedef union bdk_psbm_sysx_datax bdk_psbm_sysx_datax_t;

static inline uint64_t BDK_PSBM_SYSX_DATAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_SYSX_DATAX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=13) && (b<=5)))
        return 0x87e0de020000ll + 0x100ll * ((a) & 0xf) + 0x10ll * ((b) & 0x7);
    __bdk_csr_fatal("PSBM_SYSX_DATAX", 2, a, b, 0, 0);
}

#define typedef_BDK_PSBM_SYSX_DATAX(a,b) bdk_psbm_sysx_datax_t
#define bustype_BDK_PSBM_SYSX_DATAX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_SYSX_DATAX(a,b) "PSBM_SYSX_DATAX"
#define device_bar_BDK_PSBM_SYSX_DATAX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_SYSX_DATAX(a,b) (a)
#define arguments_BDK_PSBM_SYSX_DATAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) psbm_sys#_hdr
 *
 * PSBM SYS Slave Header Register
 * These registers contain the header captured by the last polling of the SYS PSBS
 * slaves. Index {a} is enumerated by PSBM_SYS_MAP_E. For diagnostic use only.
 */
union bdk_psbm_sysx_hdr
{
    uint32_t u;
    struct bdk_psbm_sysx_hdr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t cmd                   : 4;  /**< [ 31: 28](R/W/H) PSB command. */
        uint32_t psbs_id               : 8;  /**< [ 27: 20](R/W/H) PSBS slave ID. */
        uint32_t entries               : 4;  /**< [ 19: 16](R/W/H) Number of entries in the slave. */
        uint32_t ras                   : 16; /**< [ 15:  0](R/W/H) RAS capture data. */
#else /* Word 0 - Little Endian */
        uint32_t ras                   : 16; /**< [ 15:  0](R/W/H) RAS capture data. */
        uint32_t entries               : 4;  /**< [ 19: 16](R/W/H) Number of entries in the slave. */
        uint32_t psbs_id               : 8;  /**< [ 27: 20](R/W/H) PSBS slave ID. */
        uint32_t cmd                   : 4;  /**< [ 31: 28](R/W/H) PSB command. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_psbm_sysx_hdr_s cn; */
};
typedef union bdk_psbm_sysx_hdr bdk_psbm_sysx_hdr_t;

static inline uint64_t BDK_PSBM_SYSX_HDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PSBM_SYSX_HDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=13))
        return 0x87e0de028000ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("PSBM_SYSX_HDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_PSBM_SYSX_HDR(a) bdk_psbm_sysx_hdr_t
#define bustype_BDK_PSBM_SYSX_HDR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_PSBM_SYSX_HDR(a) "PSBM_SYSX_HDR"
#define device_bar_BDK_PSBM_SYSX_HDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PSBM_SYSX_HDR(a) (a)
#define arguments_BDK_PSBM_SYSX_HDR(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_PSBM_H__ */
