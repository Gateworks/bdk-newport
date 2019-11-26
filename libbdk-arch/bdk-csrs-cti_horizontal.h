#ifndef __BDK_CSRS_CTI_HORIZONTAL_H__
#define __BDK_CSRS_CTI_HORIZONTAL_H__
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
 * OcteonTX CTI_HORIZONTAL.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Register (RSL32b) cti_horizontal_asicctrl
 *
 * CTI Horizontal Asicctrl Register
 * I/O port control.
 */
union bdk_cti_horizontal_asicctrl
{
    uint32_t u;
    struct bdk_cti_horizontal_asicctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 24; /**< [ 31:  8](R/W) Software should write the field as all 0s. */
        uint32_t asicctrl              : 8;  /**< [  7:  0](R/W) Set and clear external output signal. */
#else /* Word 0 - Little Endian */
        uint32_t asicctrl              : 8;  /**< [  7:  0](R/W) Set and clear external output signal. */
        uint32_t sbz_0                 : 24; /**< [ 31:  8](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_asicctrl_s cn; */
};
typedef union bdk_cti_horizontal_asicctrl bdk_cti_horizontal_asicctrl_t;

#define BDK_CTI_HORIZONTAL_ASICCTRL BDK_CTI_HORIZONTAL_ASICCTRL_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_ASICCTRL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_ASICCTRL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002144ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_ASICCTRL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_ASICCTRL bdk_cti_horizontal_asicctrl_t
#define bustype_BDK_CTI_HORIZONTAL_ASICCTRL BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_ASICCTRL "CTI_HORIZONTAL_ASICCTRL"
#define busnum_BDK_CTI_HORIZONTAL_ASICCTRL 0
#define arguments_BDK_CTI_HORIZONTAL_ASICCTRL -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_authstatus
 *
 * CTI Horizontal Authstatus Register
 * Reports the current status of the authentication control signals.
 */
union bdk_cti_horizontal_authstatus
{
    uint32_t u;
    struct bdk_cti_horizontal_authstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 20; /**< [ 31: 12](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t hnid                  : 2;  /**< [ 11: 10](RO) Hypervisor non-invasive debug. */
        uint32_t hid                   : 2;  /**< [  9:  8](RO) Hypervisor invasive debug. */
        uint32_t snid                  : 2;  /**< [  7:  6](RO) Secure non-invasive debug. */
        uint32_t sid                   : 2;  /**< [  5:  4](RO) Secure invasive debug. */
        uint32_t nsnid                 : 2;  /**< [  3:  2](RO) Non-secure non-invasive debug. */
        uint32_t nsid                  : 2;  /**< [  1:  0](RO) Non-secure invasive debug. */
#else /* Word 0 - Little Endian */
        uint32_t nsid                  : 2;  /**< [  1:  0](RO) Non-secure invasive debug. */
        uint32_t nsnid                 : 2;  /**< [  3:  2](RO) Non-secure non-invasive debug. */
        uint32_t sid                   : 2;  /**< [  5:  4](RO) Secure invasive debug. */
        uint32_t snid                  : 2;  /**< [  7:  6](RO) Secure non-invasive debug. */
        uint32_t hid                   : 2;  /**< [  9:  8](RO) Hypervisor invasive debug. */
        uint32_t hnid                  : 2;  /**< [ 11: 10](RO) Hypervisor non-invasive debug. */
        uint32_t res0_0                : 20; /**< [ 31: 12](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_authstatus_s cn; */
};
typedef union bdk_cti_horizontal_authstatus bdk_cti_horizontal_authstatus_t;

#define BDK_CTI_HORIZONTAL_AUTHSTATUS BDK_CTI_HORIZONTAL_AUTHSTATUS_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_AUTHSTATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_AUTHSTATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fb8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_AUTHSTATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_AUTHSTATUS bdk_cti_horizontal_authstatus_t
#define bustype_BDK_CTI_HORIZONTAL_AUTHSTATUS BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_AUTHSTATUS "CTI_HORIZONTAL_AUTHSTATUS"
#define busnum_BDK_CTI_HORIZONTAL_AUTHSTATUS 0
#define arguments_BDK_CTI_HORIZONTAL_AUTHSTATUS -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_cidr0
 *
 * CTI Horizontal Cidr0 Register
 * The CIDR0 register is part of the set of component identification registers.
 */
union bdk_cti_horizontal_cidr0
{
    uint32_t u;
    struct bdk_cti_horizontal_cidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x0D. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x0D. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_cidr0_s cn; */
};
typedef union bdk_cti_horizontal_cidr0 bdk_cti_horizontal_cidr0_t;

#define BDK_CTI_HORIZONTAL_CIDR0 BDK_CTI_HORIZONTAL_CIDR0_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CIDR0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CIDR0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002ff0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CIDR0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CIDR0 bdk_cti_horizontal_cidr0_t
#define bustype_BDK_CTI_HORIZONTAL_CIDR0 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CIDR0 "CTI_HORIZONTAL_CIDR0"
#define busnum_BDK_CTI_HORIZONTAL_CIDR0 0
#define arguments_BDK_CTI_HORIZONTAL_CIDR0 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_cidr1
 *
 * CTI Horizontal Cidr1 Register
 * The CIDR1 register is part of the set of component identification registers.
 */
union bdk_cti_horizontal_cidr1
{
    uint32_t u;
    struct bdk_cti_horizontal_cidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t class_f               : 4;  /**< [  7:  4](RO) Component class. Returns 0x9, indicating this is a CoreSight component. */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble. Returns 0x0. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble. Returns 0x0. */
        uint32_t class_f               : 4;  /**< [  7:  4](RO) Component class. Returns 0x9, indicating this is a CoreSight component. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_cidr1_s cn; */
};
typedef union bdk_cti_horizontal_cidr1 bdk_cti_horizontal_cidr1_t;

#define BDK_CTI_HORIZONTAL_CIDR1 BDK_CTI_HORIZONTAL_CIDR1_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CIDR1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CIDR1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002ff4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CIDR1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CIDR1 bdk_cti_horizontal_cidr1_t
#define bustype_BDK_CTI_HORIZONTAL_CIDR1 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CIDR1 "CTI_HORIZONTAL_CIDR1"
#define busnum_BDK_CTI_HORIZONTAL_CIDR1 0
#define arguments_BDK_CTI_HORIZONTAL_CIDR1 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_cidr2
 *
 * CTI Horizontal Cidr2 Register
 * The CIDR2 register is part of the set of component identification registers.
 */
union bdk_cti_horizontal_cidr2
{
    uint32_t u;
    struct bdk_cti_horizontal_cidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x05. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x05. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_cidr2_s cn; */
};
typedef union bdk_cti_horizontal_cidr2 bdk_cti_horizontal_cidr2_t;

#define BDK_CTI_HORIZONTAL_CIDR2 BDK_CTI_HORIZONTAL_CIDR2_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CIDR2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CIDR2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002ff8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CIDR2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CIDR2 bdk_cti_horizontal_cidr2_t
#define bustype_BDK_CTI_HORIZONTAL_CIDR2 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CIDR2 "CTI_HORIZONTAL_CIDR2"
#define busnum_BDK_CTI_HORIZONTAL_CIDR2 0
#define arguments_BDK_CTI_HORIZONTAL_CIDR2 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_cidr3
 *
 * CTI Horizontal Cidr3 Register
 * The CIDR3 register is part of the set of component identification registers.
 */
union bdk_cti_horizontal_cidr3
{
    uint32_t u;
    struct bdk_cti_horizontal_cidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Returns 0xB1. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Returns 0xB1. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_cidr3_s cn; */
};
typedef union bdk_cti_horizontal_cidr3 bdk_cti_horizontal_cidr3_t;

#define BDK_CTI_HORIZONTAL_CIDR3 BDK_CTI_HORIZONTAL_CIDR3_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CIDR3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CIDR3_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002ffcll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CIDR3", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CIDR3 bdk_cti_horizontal_cidr3_t
#define bustype_BDK_CTI_HORIZONTAL_CIDR3 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CIDR3 "CTI_HORIZONTAL_CIDR3"
#define busnum_BDK_CTI_HORIZONTAL_CIDR3 0
#define arguments_BDK_CTI_HORIZONTAL_CIDR3 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_claimclr
 *
 * CTI Horizontal Claimclr Register
 * This register forms one half of the claim tag value. On writes, this location
 * enables individual bits to be cleared. On reads, it returns the current claim tag
 * value.
 */
union bdk_cti_horizontal_claimclr
{
    uint32_t u;
    struct bdk_cti_horizontal_claimclr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t razwi_0               : 28; /**< [ 31:  4](R/W) Read-As-Zero, Writes Ignored. */
        uint32_t clr                   : 4;  /**< [  3:  0](R/W) A bit-programmable register bank that clears the claim tag value. It is zero at
                                                                 reset. It is used by software agents to signal to each other ownership of the
                                                                 hardware. It has no direct effect on the hardware itself. */
#else /* Word 0 - Little Endian */
        uint32_t clr                   : 4;  /**< [  3:  0](R/W) A bit-programmable register bank that clears the claim tag value. It is zero at
                                                                 reset. It is used by software agents to signal to each other ownership of the
                                                                 hardware. It has no direct effect on the hardware itself. */
        uint32_t razwi_0               : 28; /**< [ 31:  4](R/W) Read-As-Zero, Writes Ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_claimclr_s cn; */
};
typedef union bdk_cti_horizontal_claimclr bdk_cti_horizontal_claimclr_t;

#define BDK_CTI_HORIZONTAL_CLAIMCLR BDK_CTI_HORIZONTAL_CLAIMCLR_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CLAIMCLR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CLAIMCLR_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fa4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CLAIMCLR", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CLAIMCLR bdk_cti_horizontal_claimclr_t
#define bustype_BDK_CTI_HORIZONTAL_CLAIMCLR BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CLAIMCLR "CTI_HORIZONTAL_CLAIMCLR"
#define busnum_BDK_CTI_HORIZONTAL_CLAIMCLR 0
#define arguments_BDK_CTI_HORIZONTAL_CLAIMCLR -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_claimset
 *
 * CTI Horizontal Claimset Register
 * This register forms one half of the claim tag value. On writes, this location
 * enables individual bits to be set. On reads, it returns the number of bits that can
 * be set.
 */
union bdk_cti_horizontal_claimset
{
    uint32_t u;
    struct bdk_cti_horizontal_claimset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t razwi_0               : 28; /**< [ 31:  4](R/W) Read-As-Zero, Writes Ignored. */
        uint32_t set                   : 4;  /**< [  3:  0](R/W) A bit-programmable register bank that sets the claim tag value. A read returns a
                                                                 logic 1 for all implemented locations. */
#else /* Word 0 - Little Endian */
        uint32_t set                   : 4;  /**< [  3:  0](R/W) A bit-programmable register bank that sets the claim tag value. A read returns a
                                                                 logic 1 for all implemented locations. */
        uint32_t razwi_0               : 28; /**< [ 31:  4](R/W) Read-As-Zero, Writes Ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_claimset_s cn; */
};
typedef union bdk_cti_horizontal_claimset bdk_cti_horizontal_claimset_t;

#define BDK_CTI_HORIZONTAL_CLAIMSET BDK_CTI_HORIZONTAL_CLAIMSET_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CLAIMSET_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CLAIMSET_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fa0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CLAIMSET", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CLAIMSET bdk_cti_horizontal_claimset_t
#define bustype_BDK_CTI_HORIZONTAL_CLAIMSET BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CLAIMSET "CTI_HORIZONTAL_CLAIMSET"
#define busnum_BDK_CTI_HORIZONTAL_CLAIMSET 0
#define arguments_BDK_CTI_HORIZONTAL_CLAIMSET -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiappclear
 *
 * CTI Horizontal Ctiappclear Register
 * The application channel clear register allows software to clear any channel output.
 * This register can be used by software to clear a channel event in place of a
 * hardware source on a trigger input. In a system where all events are sent as single
 * cycle pulses, this register must not be used. It is only retained for compatibility
 * with older systems and software. The register is implemented before the CTIGATE
 * register so, for the channel event to propagate outside the CTI, it is necessary for
 * the corresponding CTIGATE bit to be 1.
 */
union bdk_cti_horizontal_ctiappclear
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiappclear_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
        uint32_t appclear              : 4;  /**< [  3:  0](WO) Clears the corresponding internal channel flag. */
#else /* Word 0 - Little Endian */
        uint32_t appclear              : 4;  /**< [  3:  0](WO) Clears the corresponding internal channel flag. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiappclear_s cn; */
};
typedef union bdk_cti_horizontal_ctiappclear bdk_cti_horizontal_ctiappclear_t;

#define BDK_CTI_HORIZONTAL_CTIAPPCLEAR BDK_CTI_HORIZONTAL_CTIAPPCLEAR_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIAPPCLEAR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIAPPCLEAR_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002018ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIAPPCLEAR", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIAPPCLEAR bdk_cti_horizontal_ctiappclear_t
#define bustype_BDK_CTI_HORIZONTAL_CTIAPPCLEAR BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIAPPCLEAR "CTI_HORIZONTAL_CTIAPPCLEAR"
#define busnum_BDK_CTI_HORIZONTAL_CTIAPPCLEAR 0
#define arguments_BDK_CTI_HORIZONTAL_CTIAPPCLEAR -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiapppulse
 *
 * CTI Horizontal Ctiapppulse Register
 * The application channel pulse register allows software to pulse any channel output.
 * This register can be used by software to pulse a channel event in place of a
 * hardware source on a trigger input. The register is implemented before the CTIGATE
 * register so, for the channel event to propagate outside the CTI, it is necessary for
 * the corresponding CTIGATE bit to be 1.
 */
union bdk_cti_horizontal_ctiapppulse
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiapppulse_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
        uint32_t apppulse              : 4;  /**< [  3:  0](WO) Pulses the channel outputs. */
#else /* Word 0 - Little Endian */
        uint32_t apppulse              : 4;  /**< [  3:  0](WO) Pulses the channel outputs. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiapppulse_s cn; */
};
typedef union bdk_cti_horizontal_ctiapppulse bdk_cti_horizontal_ctiapppulse_t;

#define BDK_CTI_HORIZONTAL_CTIAPPPULSE BDK_CTI_HORIZONTAL_CTIAPPPULSE_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIAPPPULSE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIAPPPULSE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600201cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIAPPPULSE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIAPPPULSE bdk_cti_horizontal_ctiapppulse_t
#define bustype_BDK_CTI_HORIZONTAL_CTIAPPPULSE BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIAPPPULSE "CTI_HORIZONTAL_CTIAPPPULSE"
#define busnum_BDK_CTI_HORIZONTAL_CTIAPPPULSE 0
#define arguments_BDK_CTI_HORIZONTAL_CTIAPPPULSE -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiappset
 *
 * CTI Horizontal Ctiappset Register
 * The application channel set register allows software to set any channel output. This
 * register can be used by software to generate a channel event in place of a hardware
 * source on a trigger input. In a system where all events are sent as single cycle
 * pulses, this register must not be used. It is only retained for compatibility with
 * older systems and software. The register is implemented before the CTIGATE register
 * so, for the channel event to propagate outside the CTI, it is necessary for the
 * corresponding CTIGATE bit to be 1.
 */
union bdk_cti_horizontal_ctiappset
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiappset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t appset                : 4;  /**< [  3:  0](R/W) Sets the corresponding internal channel flag. */
#else /* Word 0 - Little Endian */
        uint32_t appset                : 4;  /**< [  3:  0](R/W) Sets the corresponding internal channel flag. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiappset_s cn; */
};
typedef union bdk_cti_horizontal_ctiappset bdk_cti_horizontal_ctiappset_t;

#define BDK_CTI_HORIZONTAL_CTIAPPSET BDK_CTI_HORIZONTAL_CTIAPPSET_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIAPPSET_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIAPPSET_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002014ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIAPPSET", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIAPPSET bdk_cti_horizontal_ctiappset_t
#define bustype_BDK_CTI_HORIZONTAL_CTIAPPSET BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIAPPSET "CTI_HORIZONTAL_CTIAPPSET"
#define busnum_BDK_CTI_HORIZONTAL_CTIAPPSET 0
#define arguments_BDK_CTI_HORIZONTAL_CTIAPPSET -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctichinstatus
 *
 * CTI Horizontal Ctichinstatus Register
 * Channel input status. If the channel input is driven by a source that generates
 * single cycle pulses, this register is generally read as 0.
 */
union bdk_cti_horizontal_ctichinstatus
{
    uint32_t u;
    struct bdk_cti_horizontal_ctichinstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
        uint32_t ctichinstatus         : 4;  /**< [  3:  0](RO) Channel input status. */
#else /* Word 0 - Little Endian */
        uint32_t ctichinstatus         : 4;  /**< [  3:  0](RO) Channel input status. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctichinstatus_s cn; */
};
typedef union bdk_cti_horizontal_ctichinstatus bdk_cti_horizontal_ctichinstatus_t;

#define BDK_CTI_HORIZONTAL_CTICHINSTATUS BDK_CTI_HORIZONTAL_CTICHINSTATUS_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTICHINSTATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTICHINSTATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002138ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTICHINSTATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTICHINSTATUS bdk_cti_horizontal_ctichinstatus_t
#define bustype_BDK_CTI_HORIZONTAL_CTICHINSTATUS BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTICHINSTATUS "CTI_HORIZONTAL_CTICHINSTATUS"
#define busnum_BDK_CTI_HORIZONTAL_CTICHINSTATUS 0
#define arguments_BDK_CTI_HORIZONTAL_CTICHINSTATUS -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctichoutstatus
 *
 * CTI Horizontal Ctichoutstatus Register
 * Channel output status. The register only has meaning if the trigger source drives
 * static levels, rather than pulses.
 */
union bdk_cti_horizontal_ctichoutstatus
{
    uint32_t u;
    struct bdk_cti_horizontal_ctichoutstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
        uint32_t ctichoutstatus        : 4;  /**< [  3:  0](RO) Channel output status. */
#else /* Word 0 - Little Endian */
        uint32_t ctichoutstatus        : 4;  /**< [  3:  0](RO) Channel output status. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctichoutstatus_s cn; */
};
typedef union bdk_cti_horizontal_ctichoutstatus bdk_cti_horizontal_ctichoutstatus_t;

#define BDK_CTI_HORIZONTAL_CTICHOUTSTATUS BDK_CTI_HORIZONTAL_CTICHOUTSTATUS_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTICHOUTSTATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTICHOUTSTATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600213cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTICHOUTSTATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTICHOUTSTATUS bdk_cti_horizontal_ctichoutstatus_t
#define bustype_BDK_CTI_HORIZONTAL_CTICHOUTSTATUS BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTICHOUTSTATUS "CTI_HORIZONTAL_CTICHOUTSTATUS"
#define busnum_BDK_CTI_HORIZONTAL_CTICHOUTSTATUS 0
#define arguments_BDK_CTI_HORIZONTAL_CTICHOUTSTATUS -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_cticontrol
 *
 * CTI Horizontal Cticontrol Register
 * The CTI control register enables and disables the CTI.
 */
union bdk_cti_horizontal_cticontrol
{
    uint32_t u;
    struct bdk_cti_horizontal_cticontrol_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 31; /**< [ 31:  1](R/W) Software should write the field as all 0s. */
        uint32_t ctien                 : 1;  /**< [  0:  0](R/W) Enable control. */
#else /* Word 0 - Little Endian */
        uint32_t ctien                 : 1;  /**< [  0:  0](R/W) Enable control. */
        uint32_t sbz_0                 : 31; /**< [ 31:  1](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_cticontrol_s cn; */
};
typedef union bdk_cti_horizontal_cticontrol bdk_cti_horizontal_cticontrol_t;

#define BDK_CTI_HORIZONTAL_CTICONTROL BDK_CTI_HORIZONTAL_CTICONTROL_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTICONTROL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTICONTROL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002000ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTICONTROL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTICONTROL bdk_cti_horizontal_cticontrol_t
#define bustype_BDK_CTI_HORIZONTAL_CTICONTROL BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTICONTROL "CTI_HORIZONTAL_CTICONTROL"
#define busnum_BDK_CTI_HORIZONTAL_CTICONTROL 0
#define arguments_BDK_CTI_HORIZONTAL_CTICONTROL -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctigate
 *
 * CTI Horizontal Ctigate Register
 * Channel output gate.
 */
union bdk_cti_horizontal_ctigate
{
    uint32_t u;
    struct bdk_cti_horizontal_ctigate_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t ctigateen             : 4;  /**< [  3:  0](R/W) Enables the propagation of channel events out of the CTI, one bit per channel. */
#else /* Word 0 - Little Endian */
        uint32_t ctigateen             : 4;  /**< [  3:  0](R/W) Enables the propagation of channel events out of the CTI, one bit per channel. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctigate_s cn; */
};
typedef union bdk_cti_horizontal_ctigate bdk_cti_horizontal_ctigate_t;

#define BDK_CTI_HORIZONTAL_CTIGATE BDK_CTI_HORIZONTAL_CTIGATE_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIGATE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIGATE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002140ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIGATE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIGATE bdk_cti_horizontal_ctigate_t
#define bustype_BDK_CTI_HORIZONTAL_CTIGATE BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIGATE "CTI_HORIZONTAL_CTIGATE"
#define busnum_BDK_CTI_HORIZONTAL_CTIGATE 0
#define arguments_BDK_CTI_HORIZONTAL_CTIGATE -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen0
 *
 * CTI Horizontal Ctiinen0 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen0
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen0_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen0 bdk_cti_horizontal_ctiinen0_t;

#define BDK_CTI_HORIZONTAL_CTIINEN0 BDK_CTI_HORIZONTAL_CTIINEN0_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002020ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN0 bdk_cti_horizontal_ctiinen0_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN0 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN0 "CTI_HORIZONTAL_CTIINEN0"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN0 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN0 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen1
 *
 * CTI Horizontal Ctiinen1 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen1
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen1_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen1 bdk_cti_horizontal_ctiinen1_t;

#define BDK_CTI_HORIZONTAL_CTIINEN1 BDK_CTI_HORIZONTAL_CTIINEN1_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002024ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN1 bdk_cti_horizontal_ctiinen1_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN1 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN1 "CTI_HORIZONTAL_CTIINEN1"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN1 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN1 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen10
 *
 * CTI Horizontal Ctiinen10 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen10
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen10_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen10 bdk_cti_horizontal_ctiinen10_t;

#define BDK_CTI_HORIZONTAL_CTIINEN10 BDK_CTI_HORIZONTAL_CTIINEN10_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN10_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN10_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002048ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN10", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN10 bdk_cti_horizontal_ctiinen10_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN10 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN10 "CTI_HORIZONTAL_CTIINEN10"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN10 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN10 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen11
 *
 * CTI Horizontal Ctiinen11 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen11
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen11_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen11 bdk_cti_horizontal_ctiinen11_t;

#define BDK_CTI_HORIZONTAL_CTIINEN11 BDK_CTI_HORIZONTAL_CTIINEN11_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN11_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN11_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600204cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN11", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN11 bdk_cti_horizontal_ctiinen11_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN11 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN11 "CTI_HORIZONTAL_CTIINEN11"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN11 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN11 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen12
 *
 * CTI Horizontal Ctiinen12 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen12
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen12_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen12 bdk_cti_horizontal_ctiinen12_t;

#define BDK_CTI_HORIZONTAL_CTIINEN12 BDK_CTI_HORIZONTAL_CTIINEN12_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN12_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN12_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002050ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN12", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN12 bdk_cti_horizontal_ctiinen12_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN12 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN12 "CTI_HORIZONTAL_CTIINEN12"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN12 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN12 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen13
 *
 * CTI Horizontal Ctiinen13 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen13
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen13_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen13_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen13 bdk_cti_horizontal_ctiinen13_t;

#define BDK_CTI_HORIZONTAL_CTIINEN13 BDK_CTI_HORIZONTAL_CTIINEN13_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN13_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN13_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002054ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN13", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN13 bdk_cti_horizontal_ctiinen13_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN13 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN13 "CTI_HORIZONTAL_CTIINEN13"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN13 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN13 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen14
 *
 * CTI Horizontal Ctiinen14 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen14
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen14_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen14_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen14 bdk_cti_horizontal_ctiinen14_t;

#define BDK_CTI_HORIZONTAL_CTIINEN14 BDK_CTI_HORIZONTAL_CTIINEN14_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN14_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN14_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002058ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN14", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN14 bdk_cti_horizontal_ctiinen14_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN14 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN14 "CTI_HORIZONTAL_CTIINEN14"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN14 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN14 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen15
 *
 * CTI Horizontal Ctiinen15 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen15
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen15_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen15_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen15 bdk_cti_horizontal_ctiinen15_t;

#define BDK_CTI_HORIZONTAL_CTIINEN15 BDK_CTI_HORIZONTAL_CTIINEN15_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN15_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN15_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600205cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN15", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN15 bdk_cti_horizontal_ctiinen15_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN15 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN15 "CTI_HORIZONTAL_CTIINEN15"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN15 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN15 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen16
 *
 * CTI Horizontal Ctiinen16 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen16
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen16_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen16_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen16 bdk_cti_horizontal_ctiinen16_t;

#define BDK_CTI_HORIZONTAL_CTIINEN16 BDK_CTI_HORIZONTAL_CTIINEN16_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN16_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN16_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002060ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN16", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN16 bdk_cti_horizontal_ctiinen16_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN16 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN16 "CTI_HORIZONTAL_CTIINEN16"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN16 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN16 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen17
 *
 * CTI Horizontal Ctiinen17 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen17
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen17_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen17_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen17 bdk_cti_horizontal_ctiinen17_t;

#define BDK_CTI_HORIZONTAL_CTIINEN17 BDK_CTI_HORIZONTAL_CTIINEN17_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN17_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN17_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002064ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN17", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN17 bdk_cti_horizontal_ctiinen17_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN17 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN17 "CTI_HORIZONTAL_CTIINEN17"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN17 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN17 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen18
 *
 * CTI Horizontal Ctiinen18 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen18
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen18_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen18_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen18 bdk_cti_horizontal_ctiinen18_t;

#define BDK_CTI_HORIZONTAL_CTIINEN18 BDK_CTI_HORIZONTAL_CTIINEN18_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN18_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN18_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002068ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN18", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN18 bdk_cti_horizontal_ctiinen18_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN18 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN18 "CTI_HORIZONTAL_CTIINEN18"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN18 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN18 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen19
 *
 * CTI Horizontal Ctiinen19 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen19
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen19_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen19_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen19 bdk_cti_horizontal_ctiinen19_t;

#define BDK_CTI_HORIZONTAL_CTIINEN19 BDK_CTI_HORIZONTAL_CTIINEN19_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN19_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN19_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600206cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN19", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN19 bdk_cti_horizontal_ctiinen19_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN19 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN19 "CTI_HORIZONTAL_CTIINEN19"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN19 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN19 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen2
 *
 * CTI Horizontal Ctiinen2 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen2
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen2_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen2 bdk_cti_horizontal_ctiinen2_t;

#define BDK_CTI_HORIZONTAL_CTIINEN2 BDK_CTI_HORIZONTAL_CTIINEN2_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002028ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN2 bdk_cti_horizontal_ctiinen2_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN2 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN2 "CTI_HORIZONTAL_CTIINEN2"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN2 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN2 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen20
 *
 * CTI Horizontal Ctiinen20 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen20
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen20_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen20_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen20 bdk_cti_horizontal_ctiinen20_t;

#define BDK_CTI_HORIZONTAL_CTIINEN20 BDK_CTI_HORIZONTAL_CTIINEN20_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN20_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN20_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002070ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN20", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN20 bdk_cti_horizontal_ctiinen20_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN20 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN20 "CTI_HORIZONTAL_CTIINEN20"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN20 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN20 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen21
 *
 * CTI Horizontal Ctiinen21 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen21
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen21_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen21_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen21 bdk_cti_horizontal_ctiinen21_t;

#define BDK_CTI_HORIZONTAL_CTIINEN21 BDK_CTI_HORIZONTAL_CTIINEN21_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN21_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN21_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002074ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN21", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN21 bdk_cti_horizontal_ctiinen21_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN21 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN21 "CTI_HORIZONTAL_CTIINEN21"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN21 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN21 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen22
 *
 * CTI Horizontal Ctiinen22 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen22
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen22_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen22_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen22 bdk_cti_horizontal_ctiinen22_t;

#define BDK_CTI_HORIZONTAL_CTIINEN22 BDK_CTI_HORIZONTAL_CTIINEN22_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN22_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN22_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002078ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN22", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN22 bdk_cti_horizontal_ctiinen22_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN22 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN22 "CTI_HORIZONTAL_CTIINEN22"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN22 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN22 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen23
 *
 * CTI Horizontal Ctiinen23 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen23
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen23_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen23_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen23 bdk_cti_horizontal_ctiinen23_t;

#define BDK_CTI_HORIZONTAL_CTIINEN23 BDK_CTI_HORIZONTAL_CTIINEN23_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN23_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN23_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600207cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN23", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN23 bdk_cti_horizontal_ctiinen23_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN23 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN23 "CTI_HORIZONTAL_CTIINEN23"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN23 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN23 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen24
 *
 * CTI Horizontal Ctiinen24 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen24
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen24_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen24_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen24 bdk_cti_horizontal_ctiinen24_t;

#define BDK_CTI_HORIZONTAL_CTIINEN24 BDK_CTI_HORIZONTAL_CTIINEN24_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN24_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN24_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002080ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN24", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN24 bdk_cti_horizontal_ctiinen24_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN24 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN24 "CTI_HORIZONTAL_CTIINEN24"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN24 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN24 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen25
 *
 * CTI Horizontal Ctiinen25 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen25
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen25_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen25_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen25 bdk_cti_horizontal_ctiinen25_t;

#define BDK_CTI_HORIZONTAL_CTIINEN25 BDK_CTI_HORIZONTAL_CTIINEN25_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN25_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN25_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002084ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN25", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN25 bdk_cti_horizontal_ctiinen25_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN25 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN25 "CTI_HORIZONTAL_CTIINEN25"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN25 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN25 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen26
 *
 * CTI Horizontal Ctiinen26 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen26
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen26_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen26_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen26 bdk_cti_horizontal_ctiinen26_t;

#define BDK_CTI_HORIZONTAL_CTIINEN26 BDK_CTI_HORIZONTAL_CTIINEN26_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN26_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN26_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002088ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN26", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN26 bdk_cti_horizontal_ctiinen26_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN26 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN26 "CTI_HORIZONTAL_CTIINEN26"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN26 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN26 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen27
 *
 * CTI Horizontal Ctiinen27 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen27
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen27_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen27_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen27 bdk_cti_horizontal_ctiinen27_t;

#define BDK_CTI_HORIZONTAL_CTIINEN27 BDK_CTI_HORIZONTAL_CTIINEN27_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN27_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN27_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600208cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN27", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN27 bdk_cti_horizontal_ctiinen27_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN27 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN27 "CTI_HORIZONTAL_CTIINEN27"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN27 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN27 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen28
 *
 * CTI Horizontal Ctiinen28 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen28
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen28_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen28_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen28 bdk_cti_horizontal_ctiinen28_t;

#define BDK_CTI_HORIZONTAL_CTIINEN28 BDK_CTI_HORIZONTAL_CTIINEN28_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN28_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN28_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002090ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN28", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN28 bdk_cti_horizontal_ctiinen28_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN28 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN28 "CTI_HORIZONTAL_CTIINEN28"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN28 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN28 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen29
 *
 * CTI Horizontal Ctiinen29 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen29
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen29_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen29_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen29 bdk_cti_horizontal_ctiinen29_t;

#define BDK_CTI_HORIZONTAL_CTIINEN29 BDK_CTI_HORIZONTAL_CTIINEN29_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN29_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN29_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002094ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN29", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN29 bdk_cti_horizontal_ctiinen29_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN29 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN29 "CTI_HORIZONTAL_CTIINEN29"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN29 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN29 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen3
 *
 * CTI Horizontal Ctiinen3 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen3
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen3_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen3 bdk_cti_horizontal_ctiinen3_t;

#define BDK_CTI_HORIZONTAL_CTIINEN3 BDK_CTI_HORIZONTAL_CTIINEN3_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN3_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600202cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN3", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN3 bdk_cti_horizontal_ctiinen3_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN3 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN3 "CTI_HORIZONTAL_CTIINEN3"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN3 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN3 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen30
 *
 * CTI Horizontal Ctiinen30 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen30
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen30_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen30_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen30 bdk_cti_horizontal_ctiinen30_t;

#define BDK_CTI_HORIZONTAL_CTIINEN30 BDK_CTI_HORIZONTAL_CTIINEN30_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN30_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN30_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002098ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN30", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN30 bdk_cti_horizontal_ctiinen30_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN30 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN30 "CTI_HORIZONTAL_CTIINEN30"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN30 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN30 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen31
 *
 * CTI Horizontal Ctiinen31 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen31
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen31_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen31_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen31 bdk_cti_horizontal_ctiinen31_t;

#define BDK_CTI_HORIZONTAL_CTIINEN31 BDK_CTI_HORIZONTAL_CTIINEN31_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN31_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN31_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600209cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN31", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN31 bdk_cti_horizontal_ctiinen31_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN31 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN31 "CTI_HORIZONTAL_CTIINEN31"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN31 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN31 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen4
 *
 * CTI Horizontal Ctiinen4 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen4
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen4_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen4 bdk_cti_horizontal_ctiinen4_t;

#define BDK_CTI_HORIZONTAL_CTIINEN4 BDK_CTI_HORIZONTAL_CTIINEN4_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN4_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN4_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002030ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN4", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN4 bdk_cti_horizontal_ctiinen4_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN4 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN4 "CTI_HORIZONTAL_CTIINEN4"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN4 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN4 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen5
 *
 * CTI Horizontal Ctiinen5 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen5
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen5_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen5 bdk_cti_horizontal_ctiinen5_t;

#define BDK_CTI_HORIZONTAL_CTIINEN5 BDK_CTI_HORIZONTAL_CTIINEN5_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN5_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN5_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002034ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN5", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN5 bdk_cti_horizontal_ctiinen5_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN5 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN5 "CTI_HORIZONTAL_CTIINEN5"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN5 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN5 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen6
 *
 * CTI Horizontal Ctiinen6 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen6
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen6_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen6 bdk_cti_horizontal_ctiinen6_t;

#define BDK_CTI_HORIZONTAL_CTIINEN6 BDK_CTI_HORIZONTAL_CTIINEN6_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN6_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN6_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002038ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN6", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN6 bdk_cti_horizontal_ctiinen6_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN6 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN6 "CTI_HORIZONTAL_CTIINEN6"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN6 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN6 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen7
 *
 * CTI Horizontal Ctiinen7 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen7
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen7_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen7 bdk_cti_horizontal_ctiinen7_t;

#define BDK_CTI_HORIZONTAL_CTIINEN7 BDK_CTI_HORIZONTAL_CTIINEN7_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN7_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN7_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600203cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN7", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN7 bdk_cti_horizontal_ctiinen7_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN7 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN7 "CTI_HORIZONTAL_CTIINEN7"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN7 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN7 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen8
 *
 * CTI Horizontal Ctiinen8 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen8
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen8_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen8 bdk_cti_horizontal_ctiinen8_t;

#define BDK_CTI_HORIZONTAL_CTIINEN8 BDK_CTI_HORIZONTAL_CTIINEN8_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN8_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN8_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002040ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN8", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN8 bdk_cti_horizontal_ctiinen8_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN8 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN8 "CTI_HORIZONTAL_CTIINEN8"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN8 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN8 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiinen9
 *
 * CTI Horizontal Ctiinen9 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_horizontal_ctiinen9
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiinen9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiinen9_s cn; */
};
typedef union bdk_cti_horizontal_ctiinen9 bdk_cti_horizontal_ctiinen9_t;

#define BDK_CTI_HORIZONTAL_CTIINEN9 BDK_CTI_HORIZONTAL_CTIINEN9_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN9_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINEN9_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002044ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINEN9", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINEN9 bdk_cti_horizontal_ctiinen9_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINEN9 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINEN9 "CTI_HORIZONTAL_CTIINEN9"
#define busnum_BDK_CTI_HORIZONTAL_CTIINEN9 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINEN9 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiintack
 *
 * CTI Horizontal Ctiintack Register
 * Software acknowledge for trigger outputs. The CTIINTACK register is a bit map that
 * allows selective clearing of trigger output events. If the SW_HANDSHAKE parameter
 * for a trigger output is set, indicating that the output latches HIGH when an event
 * is sent to that output, then the output remains HIGH until the corresponding INTACK
 * bit is written to a 1. A write of a bit to 0 has no effect. This allows different
 * software threads to be responsible for clearing different trigger outputs without
 * needing to perform a read-modify-write operation to find which bits are set.
 */
union bdk_cti_horizontal_ctiintack
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiintack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t intack                : 32; /**< [ 31:  0](WO) Acknowledges the corresponding event_out output. */
#else /* Word 0 - Little Endian */
        uint32_t intack                : 32; /**< [ 31:  0](WO) Acknowledges the corresponding event_out output. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiintack_s cn; */
};
typedef union bdk_cti_horizontal_ctiintack bdk_cti_horizontal_ctiintack_t;

#define BDK_CTI_HORIZONTAL_CTIINTACK BDK_CTI_HORIZONTAL_CTIINTACK_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINTACK_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIINTACK_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002010ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIINTACK", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIINTACK bdk_cti_horizontal_ctiintack_t
#define bustype_BDK_CTI_HORIZONTAL_CTIINTACK BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIINTACK "CTI_HORIZONTAL_CTIINTACK"
#define busnum_BDK_CTI_HORIZONTAL_CTIINTACK 0
#define arguments_BDK_CTI_HORIZONTAL_CTIINTACK -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten0
 *
 * CTI Horizontal Ctiouten0 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten0
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten0_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten0 bdk_cti_horizontal_ctiouten0_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN0 BDK_CTI_HORIZONTAL_CTIOUTEN0_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020a0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN0 bdk_cti_horizontal_ctiouten0_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN0 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN0 "CTI_HORIZONTAL_CTIOUTEN0"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN0 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN0 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten1
 *
 * CTI Horizontal Ctiouten1 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten1
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten1_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten1 bdk_cti_horizontal_ctiouten1_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN1 BDK_CTI_HORIZONTAL_CTIOUTEN1_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020a4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN1 bdk_cti_horizontal_ctiouten1_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN1 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN1 "CTI_HORIZONTAL_CTIOUTEN1"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN1 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN1 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten10
 *
 * CTI Horizontal Ctiouten10 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten10
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten10_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten10 bdk_cti_horizontal_ctiouten10_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN10 BDK_CTI_HORIZONTAL_CTIOUTEN10_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN10_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN10_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020c8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN10", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN10 bdk_cti_horizontal_ctiouten10_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN10 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN10 "CTI_HORIZONTAL_CTIOUTEN10"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN10 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN10 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten11
 *
 * CTI Horizontal Ctiouten11 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten11
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten11_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten11 bdk_cti_horizontal_ctiouten11_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN11 BDK_CTI_HORIZONTAL_CTIOUTEN11_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN11_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN11_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020ccll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN11", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN11 bdk_cti_horizontal_ctiouten11_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN11 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN11 "CTI_HORIZONTAL_CTIOUTEN11"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN11 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN11 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten12
 *
 * CTI Horizontal Ctiouten12 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten12
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten12_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten12 bdk_cti_horizontal_ctiouten12_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN12 BDK_CTI_HORIZONTAL_CTIOUTEN12_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN12_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN12_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020d0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN12", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN12 bdk_cti_horizontal_ctiouten12_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN12 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN12 "CTI_HORIZONTAL_CTIOUTEN12"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN12 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN12 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten13
 *
 * CTI Horizontal Ctiouten13 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten13
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten13_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten13_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten13 bdk_cti_horizontal_ctiouten13_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN13 BDK_CTI_HORIZONTAL_CTIOUTEN13_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN13_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN13_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020d4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN13", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN13 bdk_cti_horizontal_ctiouten13_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN13 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN13 "CTI_HORIZONTAL_CTIOUTEN13"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN13 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN13 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten14
 *
 * CTI Horizontal Ctiouten14 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten14
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten14_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten14_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten14 bdk_cti_horizontal_ctiouten14_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN14 BDK_CTI_HORIZONTAL_CTIOUTEN14_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN14_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN14_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020d8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN14", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN14 bdk_cti_horizontal_ctiouten14_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN14 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN14 "CTI_HORIZONTAL_CTIOUTEN14"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN14 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN14 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten15
 *
 * CTI Horizontal Ctiouten15 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten15
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten15_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten15_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten15 bdk_cti_horizontal_ctiouten15_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN15 BDK_CTI_HORIZONTAL_CTIOUTEN15_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN15_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN15_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020dcll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN15", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN15 bdk_cti_horizontal_ctiouten15_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN15 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN15 "CTI_HORIZONTAL_CTIOUTEN15"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN15 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN15 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten16
 *
 * CTI Horizontal Ctiouten16 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten16
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten16_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten16_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten16 bdk_cti_horizontal_ctiouten16_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN16 BDK_CTI_HORIZONTAL_CTIOUTEN16_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN16_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN16_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020e0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN16", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN16 bdk_cti_horizontal_ctiouten16_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN16 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN16 "CTI_HORIZONTAL_CTIOUTEN16"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN16 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN16 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten17
 *
 * CTI Horizontal Ctiouten17 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten17
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten17_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten17_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten17 bdk_cti_horizontal_ctiouten17_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN17 BDK_CTI_HORIZONTAL_CTIOUTEN17_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN17_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN17_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020e4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN17", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN17 bdk_cti_horizontal_ctiouten17_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN17 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN17 "CTI_HORIZONTAL_CTIOUTEN17"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN17 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN17 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten18
 *
 * CTI Horizontal Ctiouten18 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten18
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten18_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten18_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten18 bdk_cti_horizontal_ctiouten18_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN18 BDK_CTI_HORIZONTAL_CTIOUTEN18_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN18_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN18_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020e8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN18", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN18 bdk_cti_horizontal_ctiouten18_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN18 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN18 "CTI_HORIZONTAL_CTIOUTEN18"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN18 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN18 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten19
 *
 * CTI Horizontal Ctiouten19 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten19
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten19_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten19_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten19 bdk_cti_horizontal_ctiouten19_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN19 BDK_CTI_HORIZONTAL_CTIOUTEN19_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN19_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN19_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020ecll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN19", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN19 bdk_cti_horizontal_ctiouten19_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN19 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN19 "CTI_HORIZONTAL_CTIOUTEN19"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN19 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN19 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten2
 *
 * CTI Horizontal Ctiouten2 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten2
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten2_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten2 bdk_cti_horizontal_ctiouten2_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN2 BDK_CTI_HORIZONTAL_CTIOUTEN2_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020a8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN2 bdk_cti_horizontal_ctiouten2_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN2 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN2 "CTI_HORIZONTAL_CTIOUTEN2"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN2 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN2 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten20
 *
 * CTI Horizontal Ctiouten20 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten20
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten20_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten20_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten20 bdk_cti_horizontal_ctiouten20_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN20 BDK_CTI_HORIZONTAL_CTIOUTEN20_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN20_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN20_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020f0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN20", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN20 bdk_cti_horizontal_ctiouten20_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN20 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN20 "CTI_HORIZONTAL_CTIOUTEN20"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN20 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN20 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten21
 *
 * CTI Horizontal Ctiouten21 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten21
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten21_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten21_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten21 bdk_cti_horizontal_ctiouten21_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN21 BDK_CTI_HORIZONTAL_CTIOUTEN21_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN21_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN21_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020f4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN21", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN21 bdk_cti_horizontal_ctiouten21_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN21 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN21 "CTI_HORIZONTAL_CTIOUTEN21"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN21 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN21 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten22
 *
 * CTI Horizontal Ctiouten22 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten22
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten22_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten22_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten22 bdk_cti_horizontal_ctiouten22_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN22 BDK_CTI_HORIZONTAL_CTIOUTEN22_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN22_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN22_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020f8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN22", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN22 bdk_cti_horizontal_ctiouten22_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN22 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN22 "CTI_HORIZONTAL_CTIOUTEN22"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN22 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN22 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten23
 *
 * CTI Horizontal Ctiouten23 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten23
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten23_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten23_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten23 bdk_cti_horizontal_ctiouten23_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN23 BDK_CTI_HORIZONTAL_CTIOUTEN23_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN23_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN23_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020fcll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN23", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN23 bdk_cti_horizontal_ctiouten23_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN23 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN23 "CTI_HORIZONTAL_CTIOUTEN23"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN23 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN23 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten24
 *
 * CTI Horizontal Ctiouten24 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten24
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten24_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten24_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten24 bdk_cti_horizontal_ctiouten24_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN24 BDK_CTI_HORIZONTAL_CTIOUTEN24_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN24_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN24_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002100ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN24", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN24 bdk_cti_horizontal_ctiouten24_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN24 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN24 "CTI_HORIZONTAL_CTIOUTEN24"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN24 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN24 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten25
 *
 * CTI Horizontal Ctiouten25 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten25
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten25_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten25_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten25 bdk_cti_horizontal_ctiouten25_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN25 BDK_CTI_HORIZONTAL_CTIOUTEN25_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN25_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN25_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002104ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN25", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN25 bdk_cti_horizontal_ctiouten25_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN25 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN25 "CTI_HORIZONTAL_CTIOUTEN25"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN25 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN25 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten26
 *
 * CTI Horizontal Ctiouten26 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten26
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten26_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten26_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten26 bdk_cti_horizontal_ctiouten26_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN26 BDK_CTI_HORIZONTAL_CTIOUTEN26_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN26_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN26_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002108ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN26", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN26 bdk_cti_horizontal_ctiouten26_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN26 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN26 "CTI_HORIZONTAL_CTIOUTEN26"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN26 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN26 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten27
 *
 * CTI Horizontal Ctiouten27 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten27
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten27_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten27_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten27 bdk_cti_horizontal_ctiouten27_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN27 BDK_CTI_HORIZONTAL_CTIOUTEN27_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN27_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN27_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600210cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN27", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN27 bdk_cti_horizontal_ctiouten27_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN27 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN27 "CTI_HORIZONTAL_CTIOUTEN27"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN27 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN27 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten28
 *
 * CTI Horizontal Ctiouten28 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten28
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten28_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten28_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten28 bdk_cti_horizontal_ctiouten28_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN28 BDK_CTI_HORIZONTAL_CTIOUTEN28_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN28_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN28_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002110ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN28", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN28 bdk_cti_horizontal_ctiouten28_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN28 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN28 "CTI_HORIZONTAL_CTIOUTEN28"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN28 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN28 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten29
 *
 * CTI Horizontal Ctiouten29 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten29
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten29_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten29_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten29 bdk_cti_horizontal_ctiouten29_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN29 BDK_CTI_HORIZONTAL_CTIOUTEN29_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN29_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN29_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002114ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN29", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN29 bdk_cti_horizontal_ctiouten29_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN29 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN29 "CTI_HORIZONTAL_CTIOUTEN29"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN29 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN29 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten3
 *
 * CTI Horizontal Ctiouten3 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten3
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten3_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten3 bdk_cti_horizontal_ctiouten3_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN3 BDK_CTI_HORIZONTAL_CTIOUTEN3_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN3_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020acll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN3", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN3 bdk_cti_horizontal_ctiouten3_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN3 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN3 "CTI_HORIZONTAL_CTIOUTEN3"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN3 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN3 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten30
 *
 * CTI Horizontal Ctiouten30 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten30
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten30_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten30_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten30 bdk_cti_horizontal_ctiouten30_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN30 BDK_CTI_HORIZONTAL_CTIOUTEN30_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN30_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN30_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002118ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN30", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN30 bdk_cti_horizontal_ctiouten30_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN30 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN30 "CTI_HORIZONTAL_CTIOUTEN30"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN30 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN30 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten31
 *
 * CTI Horizontal Ctiouten31 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten31
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten31_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten31_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten31 bdk_cti_horizontal_ctiouten31_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN31 BDK_CTI_HORIZONTAL_CTIOUTEN31_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN31_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN31_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e04600211cll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN31", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN31 bdk_cti_horizontal_ctiouten31_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN31 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN31 "CTI_HORIZONTAL_CTIOUTEN31"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN31 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN31 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten4
 *
 * CTI Horizontal Ctiouten4 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten4
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten4_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten4 bdk_cti_horizontal_ctiouten4_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN4 BDK_CTI_HORIZONTAL_CTIOUTEN4_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN4_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN4_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020b0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN4", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN4 bdk_cti_horizontal_ctiouten4_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN4 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN4 "CTI_HORIZONTAL_CTIOUTEN4"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN4 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN4 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten5
 *
 * CTI Horizontal Ctiouten5 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten5
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten5_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten5 bdk_cti_horizontal_ctiouten5_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN5 BDK_CTI_HORIZONTAL_CTIOUTEN5_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN5_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN5_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020b4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN5", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN5 bdk_cti_horizontal_ctiouten5_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN5 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN5 "CTI_HORIZONTAL_CTIOUTEN5"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN5 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN5 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten6
 *
 * CTI Horizontal Ctiouten6 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten6
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten6_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten6 bdk_cti_horizontal_ctiouten6_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN6 BDK_CTI_HORIZONTAL_CTIOUTEN6_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN6_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN6_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020b8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN6", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN6 bdk_cti_horizontal_ctiouten6_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN6 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN6 "CTI_HORIZONTAL_CTIOUTEN6"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN6 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN6 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten7
 *
 * CTI Horizontal Ctiouten7 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten7
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten7_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten7 bdk_cti_horizontal_ctiouten7_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN7 BDK_CTI_HORIZONTAL_CTIOUTEN7_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN7_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN7_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020bcll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN7", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN7 bdk_cti_horizontal_ctiouten7_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN7 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN7 "CTI_HORIZONTAL_CTIOUTEN7"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN7 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN7 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten8
 *
 * CTI Horizontal Ctiouten8 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten8
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten8_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten8 bdk_cti_horizontal_ctiouten8_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN8 BDK_CTI_HORIZONTAL_CTIOUTEN8_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN8_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN8_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020c0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN8", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN8 bdk_cti_horizontal_ctiouten8_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN8 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN8 "CTI_HORIZONTAL_CTIOUTEN8"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN8 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN8 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctiouten9
 *
 * CTI Horizontal Ctiouten9 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_horizontal_ctiouten9
{
    uint32_t u;
    struct bdk_cti_horizontal_ctiouten9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctiouten9_s cn; */
};
typedef union bdk_cti_horizontal_ctiouten9 bdk_cti_horizontal_ctiouten9_t;

#define BDK_CTI_HORIZONTAL_CTIOUTEN9 BDK_CTI_HORIZONTAL_CTIOUTEN9_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN9_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTIOUTEN9_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e0460020c4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTIOUTEN9", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTIOUTEN9 bdk_cti_horizontal_ctiouten9_t
#define bustype_BDK_CTI_HORIZONTAL_CTIOUTEN9 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTIOUTEN9 "CTI_HORIZONTAL_CTIOUTEN9"
#define busnum_BDK_CTI_HORIZONTAL_CTIOUTEN9 0
#define arguments_BDK_CTI_HORIZONTAL_CTIOUTEN9 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctitriginstatus
 *
 * CTI Horizontal Ctitriginstatus Register
 * Trigger input status. If the event_in input is driven by a source that generates
 * single cycle pulses, this register is generally read as 0.
 */
union bdk_cti_horizontal_ctitriginstatus
{
    uint32_t u;
    struct bdk_cti_horizontal_ctitriginstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t triginstatus          : 32; /**< [ 31:  0](RO) Trigger input status. */
#else /* Word 0 - Little Endian */
        uint32_t triginstatus          : 32; /**< [ 31:  0](RO) Trigger input status. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctitriginstatus_s cn; */
};
typedef union bdk_cti_horizontal_ctitriginstatus bdk_cti_horizontal_ctitriginstatus_t;

#define BDK_CTI_HORIZONTAL_CTITRIGINSTATUS BDK_CTI_HORIZONTAL_CTITRIGINSTATUS_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTITRIGINSTATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTITRIGINSTATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002130ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTITRIGINSTATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTITRIGINSTATUS bdk_cti_horizontal_ctitriginstatus_t
#define bustype_BDK_CTI_HORIZONTAL_CTITRIGINSTATUS BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTITRIGINSTATUS "CTI_HORIZONTAL_CTITRIGINSTATUS"
#define busnum_BDK_CTI_HORIZONTAL_CTITRIGINSTATUS 0
#define arguments_BDK_CTI_HORIZONTAL_CTITRIGINSTATUS -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ctitrigoutstatus
 *
 * CTI Horizontal Ctitrigoutstatus Register
 * Trigger output status. The register only has meaning if the trigger source drives
 * static levels, rather than pulses.
 */
union bdk_cti_horizontal_ctitrigoutstatus
{
    uint32_t u;
    struct bdk_cti_horizontal_ctitrigoutstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t trigoutstatus         : 32; /**< [ 31:  0](RO) Trigger output status. */
#else /* Word 0 - Little Endian */
        uint32_t trigoutstatus         : 32; /**< [ 31:  0](RO) Trigger output status. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ctitrigoutstatus_s cn; */
};
typedef union bdk_cti_horizontal_ctitrigoutstatus bdk_cti_horizontal_ctitrigoutstatus_t;

#define BDK_CTI_HORIZONTAL_CTITRIGOUTSTATUS BDK_CTI_HORIZONTAL_CTITRIGOUTSTATUS_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_CTITRIGOUTSTATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_CTITRIGOUTSTATUS_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002134ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_CTITRIGOUTSTATUS", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_CTITRIGOUTSTATUS bdk_cti_horizontal_ctitrigoutstatus_t
#define bustype_BDK_CTI_HORIZONTAL_CTITRIGOUTSTATUS BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_CTITRIGOUTSTATUS "CTI_HORIZONTAL_CTITRIGOUTSTATUS"
#define busnum_BDK_CTI_HORIZONTAL_CTITRIGOUTSTATUS 0
#define arguments_BDK_CTI_HORIZONTAL_CTITRIGOUTSTATUS -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_devaff0
 *
 * CTI Horizontal Devaff0 Register
 * Enables a debugger to determine if two components have an affinity with each other.
 */
union bdk_cti_horizontal_devaff0
{
    uint32_t u;
    struct bdk_cti_horizontal_devaff0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devaff0               : 32; /**< [ 31:  0](RO) Lower 32-bits of DEVAFF. The value is set by the devaff[31:0] tie-off inputs. */
#else /* Word 0 - Little Endian */
        uint32_t devaff0               : 32; /**< [ 31:  0](RO) Lower 32-bits of DEVAFF. The value is set by the devaff[31:0] tie-off inputs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_devaff0_s cn; */
};
typedef union bdk_cti_horizontal_devaff0 bdk_cti_horizontal_devaff0_t;

#define BDK_CTI_HORIZONTAL_DEVAFF0 BDK_CTI_HORIZONTAL_DEVAFF0_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_DEVAFF0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_DEVAFF0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fa8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_DEVAFF0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_DEVAFF0 bdk_cti_horizontal_devaff0_t
#define bustype_BDK_CTI_HORIZONTAL_DEVAFF0 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_DEVAFF0 "CTI_HORIZONTAL_DEVAFF0"
#define busnum_BDK_CTI_HORIZONTAL_DEVAFF0 0
#define arguments_BDK_CTI_HORIZONTAL_DEVAFF0 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_devaff1
 *
 * CTI Horizontal Devaff1 Register
 * Enables a debugger to determine if two components have an affinity with each other.
 */
union bdk_cti_horizontal_devaff1
{
    uint32_t u;
    struct bdk_cti_horizontal_devaff1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devaff1               : 32; /**< [ 31:  0](RO) Upper 32-bits of DEVAFF. The value is set by the devaff[63:32] tie-off inputs. */
#else /* Word 0 - Little Endian */
        uint32_t devaff1               : 32; /**< [ 31:  0](RO) Upper 32-bits of DEVAFF. The value is set by the devaff[63:32] tie-off inputs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_devaff1_s cn; */
};
typedef union bdk_cti_horizontal_devaff1 bdk_cti_horizontal_devaff1_t;

#define BDK_CTI_HORIZONTAL_DEVAFF1 BDK_CTI_HORIZONTAL_DEVAFF1_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_DEVAFF1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_DEVAFF1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002facll;
    __bdk_csr_fatal("CTI_HORIZONTAL_DEVAFF1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_DEVAFF1 bdk_cti_horizontal_devaff1_t
#define bustype_BDK_CTI_HORIZONTAL_DEVAFF1 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_DEVAFF1 "CTI_HORIZONTAL_DEVAFF1"
#define busnum_BDK_CTI_HORIZONTAL_DEVAFF1 0
#define arguments_BDK_CTI_HORIZONTAL_DEVAFF1 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_devarch
 *
 * CTI Horizontal Devarch Register
 * Identifies the architect and architecture of a CoreSight component. The architect
 * might differ from the designer of a component, for example Arm defines the
 * architecture but another company designs and implements the component.
 */
union bdk_cti_horizontal_devarch
{
    uint32_t u;
    struct bdk_cti_horizontal_devarch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Returns 0x23b, denoting Arm as architect of the component. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) Returns 1, indicating that the DEVARCH register is present. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Architecture revision. Returns the revision of the architecture that the ARCHID field specifies. */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Architecture ID. Returns 0x1a14, identifying Cross Trigger Interface architecture v2. */
#else /* Word 0 - Little Endian */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Architecture ID. Returns 0x1a14, identifying Cross Trigger Interface architecture v2. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Architecture revision. Returns the revision of the architecture that the ARCHID field specifies. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) Returns 1, indicating that the DEVARCH register is present. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Returns 0x23b, denoting Arm as architect of the component. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_devarch_s cn; */
};
typedef union bdk_cti_horizontal_devarch bdk_cti_horizontal_devarch_t;

#define BDK_CTI_HORIZONTAL_DEVARCH BDK_CTI_HORIZONTAL_DEVARCH_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_DEVARCH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_DEVARCH_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fbcll;
    __bdk_csr_fatal("CTI_HORIZONTAL_DEVARCH", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_DEVARCH bdk_cti_horizontal_devarch_t
#define bustype_BDK_CTI_HORIZONTAL_DEVARCH BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_DEVARCH "CTI_HORIZONTAL_DEVARCH"
#define busnum_BDK_CTI_HORIZONTAL_DEVARCH 0
#define arguments_BDK_CTI_HORIZONTAL_DEVARCH -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_devid
 *
 * CTI Horizontal Devid Register
 * This register is IMPLEMENTATION DEFINED for each Part Number and Designer. The
 * register indicates the capabilities of the component.
 */
union bdk_cti_horizontal_devid
{
    uint32_t u;
    struct bdk_cti_horizontal_devid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_2                : 7;  /**< [ 31: 25](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t inout_f               : 1;  /**< [ 24: 24](RO) Indicates channel inputs are also masked by the CTIGATE register. Always 1. */
        uint32_t res0_1                : 4;  /**< [ 23: 20](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t num_ch                : 4;  /**< [ 19: 16](RO) The number of channels. Always 4. */
        uint32_t num_trig              : 8;  /**< [ 15:  8](RO) Indicates the maximum number of triggers - the maximum of the two parameters,
                                                                 NUM_EVENT_SLAVES and NUM_EVENT_MASTERS. */
        uint32_t res0_0                : 3;  /**< [  7:  5](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t ext_mux_num           : 5;  /**< [  4:  0](RO) Indicates the value of the EXT_MUX_NUM parameter, which determines if there is
                                                                 any external multiplexing on the trigger inputs and outputs. 0 indicates no
                                                                 multiplexing. */
#else /* Word 0 - Little Endian */
        uint32_t ext_mux_num           : 5;  /**< [  4:  0](RO) Indicates the value of the EXT_MUX_NUM parameter, which determines if there is
                                                                 any external multiplexing on the trigger inputs and outputs. 0 indicates no
                                                                 multiplexing. */
        uint32_t res0_0                : 3;  /**< [  7:  5](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t num_trig              : 8;  /**< [ 15:  8](RO) Indicates the maximum number of triggers - the maximum of the two parameters,
                                                                 NUM_EVENT_SLAVES and NUM_EVENT_MASTERS. */
        uint32_t num_ch                : 4;  /**< [ 19: 16](RO) The number of channels. Always 4. */
        uint32_t res0_1                : 4;  /**< [ 23: 20](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t inout_f               : 1;  /**< [ 24: 24](RO) Indicates channel inputs are also masked by the CTIGATE register. Always 1. */
        uint32_t res0_2                : 7;  /**< [ 31: 25](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_devid_s cn; */
};
typedef union bdk_cti_horizontal_devid bdk_cti_horizontal_devid_t;

#define BDK_CTI_HORIZONTAL_DEVID BDK_CTI_HORIZONTAL_DEVID_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_DEVID_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_DEVID_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fc8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_DEVID", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_DEVID bdk_cti_horizontal_devid_t
#define bustype_BDK_CTI_HORIZONTAL_DEVID BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_DEVID "CTI_HORIZONTAL_DEVID"
#define busnum_BDK_CTI_HORIZONTAL_DEVID 0
#define arguments_BDK_CTI_HORIZONTAL_DEVID -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_devtype
 *
 * CTI Horizontal Devtype Register
 * A debugger can use this register to get information about a component that has an
 * unrecognized Part number.
 */
union bdk_cti_horizontal_devtype
{
    uint32_t u;
    struct bdk_cti_horizontal_devtype_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Minor classification. Returns 0x1, indicating this component is a Trigger-Matrix. */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major classification. Returns 0x4, indicating this component performs Debug Control. */
#else /* Word 0 - Little Endian */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major classification. Returns 0x4, indicating this component performs Debug Control. */
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Minor classification. Returns 0x1, indicating this component is a Trigger-Matrix. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_devtype_s cn; */
};
typedef union bdk_cti_horizontal_devtype bdk_cti_horizontal_devtype_t;

#define BDK_CTI_HORIZONTAL_DEVTYPE BDK_CTI_HORIZONTAL_DEVTYPE_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_DEVTYPE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_DEVTYPE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fccll;
    __bdk_csr_fatal("CTI_HORIZONTAL_DEVTYPE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_DEVTYPE bdk_cti_horizontal_devtype_t
#define bustype_BDK_CTI_HORIZONTAL_DEVTYPE BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_DEVTYPE "CTI_HORIZONTAL_DEVTYPE"
#define busnum_BDK_CTI_HORIZONTAL_DEVTYPE 0
#define arguments_BDK_CTI_HORIZONTAL_DEVTYPE -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_itchin
 *
 * CTI Horizontal Itchin Register
 * Integration test to view channel events. The integration test register includes a
 * latch that is set when a pulse is received on a channel input. When read, a register
 * bit reads as 1 if the channel has received a pulse since it was last read. The act
 * of reading the register automatically clears the 1 to a 0. When performing
 * integration testing it is therefore important to coordinate the setting of event
 * latches and reading/clearing them.
 */
union bdk_cti_horizontal_itchin
{
    uint32_t u;
    struct bdk_cti_horizontal_itchin_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
        uint32_t ctichin               : 4;  /**< [  3:  0](RO) Reads the latched value of the channel inputs. */
#else /* Word 0 - Little Endian */
        uint32_t ctichin               : 4;  /**< [  3:  0](RO) Reads the latched value of the channel inputs. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_itchin_s cn; */
};
typedef union bdk_cti_horizontal_itchin bdk_cti_horizontal_itchin_t;

#define BDK_CTI_HORIZONTAL_ITCHIN BDK_CTI_HORIZONTAL_ITCHIN_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_ITCHIN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_ITCHIN_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002ef4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_ITCHIN", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_ITCHIN bdk_cti_horizontal_itchin_t
#define bustype_BDK_CTI_HORIZONTAL_ITCHIN BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_ITCHIN "CTI_HORIZONTAL_ITCHIN"
#define busnum_BDK_CTI_HORIZONTAL_ITCHIN 0
#define arguments_BDK_CTI_HORIZONTAL_ITCHIN -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_itchout
 *
 * CTI Horizontal Itchout Register
 * Integration test mode register, used to generate channel events. Writing to the
 * register creates a single pulse on the output. ITCHOUT is self-clearing.
 */
union bdk_cti_horizontal_itchout
{
    uint32_t u;
    struct bdk_cti_horizontal_itchout_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t ctichout              : 4;  /**< [  3:  0](R/W) Pulses the channel outputs. */
#else /* Word 0 - Little Endian */
        uint32_t ctichout              : 4;  /**< [  3:  0](R/W) Pulses the channel outputs. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_itchout_s cn; */
};
typedef union bdk_cti_horizontal_itchout bdk_cti_horizontal_itchout_t;

#define BDK_CTI_HORIZONTAL_ITCHOUT BDK_CTI_HORIZONTAL_ITCHOUT_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_ITCHOUT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_ITCHOUT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002ee4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_ITCHOUT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_ITCHOUT bdk_cti_horizontal_itchout_t
#define bustype_BDK_CTI_HORIZONTAL_ITCHOUT BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_ITCHOUT "CTI_HORIZONTAL_ITCHOUT"
#define busnum_BDK_CTI_HORIZONTAL_ITCHOUT 0
#define arguments_BDK_CTI_HORIZONTAL_ITCHOUT -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_itctrl
 *
 * CTI Horizontal Itctrl Register
 * The Integration Mode Control register is used to enable topology detection.
 */
union bdk_cti_horizontal_itctrl
{
    uint32_t u;
    struct bdk_cti_horizontal_itctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t razwi_0               : 31; /**< [ 31:  1](R/W) Read-As-Zero, Writes Ignored. */
        uint32_t ime                   : 1;  /**< [  0:  0](R/W) Integration Mode Enable. When set, the component enters integration mode,
                                                                 enabling topology detection or integration testing to be performed. */
#else /* Word 0 - Little Endian */
        uint32_t ime                   : 1;  /**< [  0:  0](R/W) Integration Mode Enable. When set, the component enters integration mode,
                                                                 enabling topology detection or integration testing to be performed. */
        uint32_t razwi_0               : 31; /**< [ 31:  1](R/W) Read-As-Zero, Writes Ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_itctrl_s cn; */
};
typedef union bdk_cti_horizontal_itctrl bdk_cti_horizontal_itctrl_t;

#define BDK_CTI_HORIZONTAL_ITCTRL BDK_CTI_HORIZONTAL_ITCTRL_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_ITCTRL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_ITCTRL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002f00ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_ITCTRL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_ITCTRL bdk_cti_horizontal_itctrl_t
#define bustype_BDK_CTI_HORIZONTAL_ITCTRL BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_ITCTRL "CTI_HORIZONTAL_ITCTRL"
#define busnum_BDK_CTI_HORIZONTAL_ITCTRL 0
#define arguments_BDK_CTI_HORIZONTAL_ITCTRL -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ittrigin
 *
 * CTI Horizontal Ittrigin Register
 * Integration test to view trigger events. The integration test register includes a
 * latch that is set when a pulse is received on a trigger input. When read, a register
 * bit reads as 1 if the trigger input has received a pulse since it was last read. The
 * act of reading the register automatically clears the 1 to a 0. When performing
 * integration testing it is therefore important to coordinate the setting of event
 * latches and reading/clearing them.
 */
union bdk_cti_horizontal_ittrigin
{
    uint32_t u;
    struct bdk_cti_horizontal_ittrigin_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ctitrigin             : 32; /**< [ 31:  0](RO) Reads the latched value of the trigger inputs. */
#else /* Word 0 - Little Endian */
        uint32_t ctitrigin             : 32; /**< [ 31:  0](RO) Reads the latched value of the trigger inputs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ittrigin_s cn; */
};
typedef union bdk_cti_horizontal_ittrigin bdk_cti_horizontal_ittrigin_t;

#define BDK_CTI_HORIZONTAL_ITTRIGIN BDK_CTI_HORIZONTAL_ITTRIGIN_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_ITTRIGIN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_ITTRIGIN_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002ef8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_ITTRIGIN", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_ITTRIGIN bdk_cti_horizontal_ittrigin_t
#define bustype_BDK_CTI_HORIZONTAL_ITTRIGIN BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_ITTRIGIN "CTI_HORIZONTAL_ITTRIGIN"
#define busnum_BDK_CTI_HORIZONTAL_ITTRIGIN 0
#define arguments_BDK_CTI_HORIZONTAL_ITTRIGIN -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_ittrigout
 *
 * CTI Horizontal Ittrigout Register
 * Integration test to generate trigger events.
 */
union bdk_cti_horizontal_ittrigout
{
    uint32_t u;
    struct bdk_cti_horizontal_ittrigout_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ctitrigout            : 32; /**< [ 31:  0](R/W) Set/clear trigger output signal. Reads return the value in the register. Writes: */
#else /* Word 0 - Little Endian */
        uint32_t ctitrigout            : 32; /**< [ 31:  0](R/W) Set/clear trigger output signal. Reads return the value in the register. Writes: */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_ittrigout_s cn; */
};
typedef union bdk_cti_horizontal_ittrigout bdk_cti_horizontal_ittrigout_t;

#define BDK_CTI_HORIZONTAL_ITTRIGOUT BDK_CTI_HORIZONTAL_ITTRIGOUT_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_ITTRIGOUT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_ITTRIGOUT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002ee8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_ITTRIGOUT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_ITTRIGOUT bdk_cti_horizontal_ittrigout_t
#define bustype_BDK_CTI_HORIZONTAL_ITTRIGOUT BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_ITTRIGOUT "CTI_HORIZONTAL_ITTRIGOUT"
#define busnum_BDK_CTI_HORIZONTAL_ITTRIGOUT 0
#define arguments_BDK_CTI_HORIZONTAL_ITTRIGOUT -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_pidr0
 *
 * CTI Horizontal Pidr0 Register
 * The PIDR0 register is part of the set of peripheral identification registers.
 */
union bdk_cti_horizontal_pidr0
{
    uint32_t u;
    struct bdk_cti_horizontal_pidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number, bits[7:0]. Taken together with PIDR1.PART_1 it indicates the
                                                                 component. The Part Number is selected by the designer of the component. */
#else /* Word 0 - Little Endian */
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number, bits[7:0]. Taken together with PIDR1.PART_1 it indicates the
                                                                 component. The Part Number is selected by the designer of the component. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_pidr0_s cn; */
};
typedef union bdk_cti_horizontal_pidr0 bdk_cti_horizontal_pidr0_t;

#define BDK_CTI_HORIZONTAL_PIDR0 BDK_CTI_HORIZONTAL_PIDR0_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR0_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fe0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_PIDR0", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_PIDR0 bdk_cti_horizontal_pidr0_t
#define bustype_BDK_CTI_HORIZONTAL_PIDR0 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_PIDR0 "CTI_HORIZONTAL_PIDR0"
#define busnum_BDK_CTI_HORIZONTAL_PIDR0 0
#define arguments_BDK_CTI_HORIZONTAL_PIDR0 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_pidr1
 *
 * CTI Horizontal Pidr1 Register
 * The PIDR1 register is part of the set of peripheral identification registers.
 */
union bdk_cti_horizontal_pidr1
{
    uint32_t u;
    struct bdk_cti_horizontal_pidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code, bits[3:0]. Together, with PIDR4.DES_2 and
                                                                 PIDR2.DES_1, they indicate the designer of the component and not the
                                                                 implementer, except where the two are the same. */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number, bits[11:8]. Taken together with PIDR0.PART_0 it indicates the
                                                                 component. The Part Number is selected by the designer of the component. */
#else /* Word 0 - Little Endian */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number, bits[11:8]. Taken together with PIDR0.PART_0 it indicates the
                                                                 component. The Part Number is selected by the designer of the component. */
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code, bits[3:0]. Together, with PIDR4.DES_2 and
                                                                 PIDR2.DES_1, they indicate the designer of the component and not the
                                                                 implementer, except where the two are the same. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_pidr1_s cn; */
};
typedef union bdk_cti_horizontal_pidr1 bdk_cti_horizontal_pidr1_t;

#define BDK_CTI_HORIZONTAL_PIDR1 BDK_CTI_HORIZONTAL_PIDR1_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR1_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fe4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_PIDR1", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_PIDR1 bdk_cti_horizontal_pidr1_t
#define bustype_BDK_CTI_HORIZONTAL_PIDR1 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_PIDR1 "CTI_HORIZONTAL_PIDR1"
#define busnum_BDK_CTI_HORIZONTAL_PIDR1 0
#define arguments_BDK_CTI_HORIZONTAL_PIDR1 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_pidr2
 *
 * CTI Horizontal Pidr2 Register
 * The PIDR2 register is part of the set of peripheral identification registers.
 */
union bdk_cti_horizontal_pidr2
{
    uint32_t u;
    struct bdk_cti_horizontal_pidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Revision. It is an incremental value starting at 0x0 for the first design of a
                                                                 component. See the css600 Component list in Chapter 1 for information on the RTL
                                                                 revision of the component. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) 1 - Always set. Indicates that a JEDEC assigned value is used. */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code, bits[6:4]. Together, with PIDR4.DES_2 and
                                                                 PIDR1.DES_0, they indicate the designer of the component and not the
                                                                 implementer, except where the two are the same. */
#else /* Word 0 - Little Endian */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code, bits[6:4]. Together, with PIDR4.DES_2 and
                                                                 PIDR1.DES_0, they indicate the designer of the component and not the
                                                                 implementer, except where the two are the same. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) 1 - Always set. Indicates that a JEDEC assigned value is used. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Revision. It is an incremental value starting at 0x0 for the first design of a
                                                                 component. See the css600 Component list in Chapter 1 for information on the RTL
                                                                 revision of the component. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_pidr2_s cn; */
};
typedef union bdk_cti_horizontal_pidr2 bdk_cti_horizontal_pidr2_t;

#define BDK_CTI_HORIZONTAL_PIDR2 BDK_CTI_HORIZONTAL_PIDR2_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR2_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fe8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_PIDR2", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_PIDR2 bdk_cti_horizontal_pidr2_t
#define bustype_BDK_CTI_HORIZONTAL_PIDR2 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_PIDR2 "CTI_HORIZONTAL_PIDR2"
#define busnum_BDK_CTI_HORIZONTAL_PIDR2 0
#define arguments_BDK_CTI_HORIZONTAL_PIDR2 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_pidr3
 *
 * CTI Horizontal Pidr3 Register
 * The PIDR3 register is part of the set of peripheral identification registers.
 */
union bdk_cti_horizontal_pidr3
{
    uint32_t u;
    struct bdk_cti_horizontal_pidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t revand                : 4;  /**< [  7:  4](RO) This field indicates minor errata fixes specific to this design, for example
                                                                 metal fixes after implementation. In most cases this field is 0x0. */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer Modified. Where the component is reusable IP, this value indicates if
                                                                 the customer has modified the behavior of the component. In most cases this
                                                                 field is 0x0. */
#else /* Word 0 - Little Endian */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer Modified. Where the component is reusable IP, this value indicates if
                                                                 the customer has modified the behavior of the component. In most cases this
                                                                 field is 0x0. */
        uint32_t revand                : 4;  /**< [  7:  4](RO) This field indicates minor errata fixes specific to this design, for example
                                                                 metal fixes after implementation. In most cases this field is 0x0. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_pidr3_s cn; */
};
typedef union bdk_cti_horizontal_pidr3 bdk_cti_horizontal_pidr3_t;

#define BDK_CTI_HORIZONTAL_PIDR3 BDK_CTI_HORIZONTAL_PIDR3_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR3_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR3_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fecll;
    __bdk_csr_fatal("CTI_HORIZONTAL_PIDR3", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_PIDR3 bdk_cti_horizontal_pidr3_t
#define bustype_BDK_CTI_HORIZONTAL_PIDR3 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_PIDR3 "CTI_HORIZONTAL_PIDR3"
#define busnum_BDK_CTI_HORIZONTAL_PIDR3 0
#define arguments_BDK_CTI_HORIZONTAL_PIDR3 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_pidr4
 *
 * CTI Horizontal Pidr4 Register
 * The PIDR4 register is part of the set of peripheral identification registers.
 */
union bdk_cti_horizontal_pidr4
{
    uint32_t u;
    struct bdk_cti_horizontal_pidr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t size                  : 4;  /**< [  7:  4](RO) Indicates the memory size that is used by this component. Returns 0 indicating
                                                                 that the component uses an UNKNOWN number of 4KB blocks. Using the SIZE field to
                                                                 indicate the size of the component is deprecated. */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code. Together, with PIDR2.DES_1 and PIDR1.DES_0, they
                                                                 indicate the designer of the component and not the implementer, except where the
                                                                 two are the same. */
#else /* Word 0 - Little Endian */
        uint32_t des_2                 : 4;  /**< [  3:  0](RO) JEP106 continuation code. Together, with PIDR2.DES_1 and PIDR1.DES_0, they
                                                                 indicate the designer of the component and not the implementer, except where the
                                                                 two are the same. */
        uint32_t size                  : 4;  /**< [  7:  4](RO) Indicates the memory size that is used by this component. Returns 0 indicating
                                                                 that the component uses an UNKNOWN number of 4KB blocks. Using the SIZE field to
                                                                 indicate the size of the component is deprecated. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_pidr4_s cn; */
};
typedef union bdk_cti_horizontal_pidr4 bdk_cti_horizontal_pidr4_t;

#define BDK_CTI_HORIZONTAL_PIDR4 BDK_CTI_HORIZONTAL_PIDR4_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR4_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR4_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fd0ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_PIDR4", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_PIDR4 bdk_cti_horizontal_pidr4_t
#define bustype_BDK_CTI_HORIZONTAL_PIDR4 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_PIDR4 "CTI_HORIZONTAL_PIDR4"
#define busnum_BDK_CTI_HORIZONTAL_PIDR4 0
#define arguments_BDK_CTI_HORIZONTAL_PIDR4 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_pidr5
 *
 * CTI Horizontal Pidr5 Register
 * The PIDR5 register is part of the set of peripheral identification registers.
 */
union bdk_cti_horizontal_pidr5
{
    uint32_t u;
    struct bdk_cti_horizontal_pidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr5                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr5                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_pidr5_s cn; */
};
typedef union bdk_cti_horizontal_pidr5 bdk_cti_horizontal_pidr5_t;

#define BDK_CTI_HORIZONTAL_PIDR5 BDK_CTI_HORIZONTAL_PIDR5_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR5_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR5_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fd4ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_PIDR5", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_PIDR5 bdk_cti_horizontal_pidr5_t
#define bustype_BDK_CTI_HORIZONTAL_PIDR5 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_PIDR5 "CTI_HORIZONTAL_PIDR5"
#define busnum_BDK_CTI_HORIZONTAL_PIDR5 0
#define arguments_BDK_CTI_HORIZONTAL_PIDR5 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_pidr6
 *
 * CTI Horizontal Pidr6 Register
 * The PIDR6 register is part of the set of peripheral identification registers.
 */
union bdk_cti_horizontal_pidr6
{
    uint32_t u;
    struct bdk_cti_horizontal_pidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr6                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr6                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_pidr6_s cn; */
};
typedef union bdk_cti_horizontal_pidr6 bdk_cti_horizontal_pidr6_t;

#define BDK_CTI_HORIZONTAL_PIDR6 BDK_CTI_HORIZONTAL_PIDR6_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR6_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR6_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fd8ll;
    __bdk_csr_fatal("CTI_HORIZONTAL_PIDR6", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_PIDR6 bdk_cti_horizontal_pidr6_t
#define bustype_BDK_CTI_HORIZONTAL_PIDR6 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_PIDR6 "CTI_HORIZONTAL_PIDR6"
#define busnum_BDK_CTI_HORIZONTAL_PIDR6 0
#define arguments_BDK_CTI_HORIZONTAL_PIDR6 -1,-1,-1,-1

/**
 * Register (RSL32b) cti_horizontal_pidr7
 *
 * CTI Horizontal Pidr7 Register
 * The PIDR7 register is part of the set of peripheral identification registers.
 */
union bdk_cti_horizontal_pidr7
{
    uint32_t u;
    struct bdk_cti_horizontal_pidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr7                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr7                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_horizontal_pidr7_s cn; */
};
typedef union bdk_cti_horizontal_pidr7 bdk_cti_horizontal_pidr7_t;

#define BDK_CTI_HORIZONTAL_PIDR7 BDK_CTI_HORIZONTAL_PIDR7_FUNC()
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR7_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_HORIZONTAL_PIDR7_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_LOKI))
        return 0x87e046002fdcll;
    __bdk_csr_fatal("CTI_HORIZONTAL_PIDR7", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_HORIZONTAL_PIDR7 bdk_cti_horizontal_pidr7_t
#define bustype_BDK_CTI_HORIZONTAL_PIDR7 BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_HORIZONTAL_PIDR7 "CTI_HORIZONTAL_PIDR7"
#define busnum_BDK_CTI_HORIZONTAL_PIDR7 0
#define arguments_BDK_CTI_HORIZONTAL_PIDR7 -1,-1,-1,-1

#endif /* __BDK_CSRS_CTI_HORIZONTAL_H__ */
