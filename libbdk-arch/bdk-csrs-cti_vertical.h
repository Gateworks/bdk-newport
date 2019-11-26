#ifndef __BDK_CSRS_CTI_VERTICAL_H__
#define __BDK_CSRS_CTI_VERTICAL_H__
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
 * OcteonTX CTI_VERTICAL.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Register (RSL32b) cti_vertical#_asicctrl
 *
 * CTI Vertical Asicctrl Register
 * I/O port control.
 */
union bdk_cti_verticalx_asicctrl
{
    uint32_t u;
    struct bdk_cti_verticalx_asicctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 24; /**< [ 31:  8](R/W) Software should write the field as all 0s. */
        uint32_t asicctrl              : 8;  /**< [  7:  0](R/W) Set and clear external output signal. */
#else /* Word 0 - Little Endian */
        uint32_t asicctrl              : 8;  /**< [  7:  0](R/W) Set and clear external output signal. */
        uint32_t sbz_0                 : 24; /**< [ 31:  8](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_asicctrl_s cn; */
};
typedef union bdk_cti_verticalx_asicctrl bdk_cti_verticalx_asicctrl_t;

static inline uint64_t BDK_CTI_VERTICALX_ASICCTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_ASICCTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102144ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_ASICCTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_ASICCTRL(a) bdk_cti_verticalx_asicctrl_t
#define bustype_BDK_CTI_VERTICALX_ASICCTRL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_ASICCTRL(a) "CTI_VERTICALX_ASICCTRL"
#define busnum_BDK_CTI_VERTICALX_ASICCTRL(a) (a)
#define arguments_BDK_CTI_VERTICALX_ASICCTRL(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_authstatus
 *
 * CTI Vertical Authstatus Register
 * Reports the current status of the authentication control signals.
 */
union bdk_cti_verticalx_authstatus
{
    uint32_t u;
    struct bdk_cti_verticalx_authstatus_s
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
    /* struct bdk_cti_verticalx_authstatus_s cn; */
};
typedef union bdk_cti_verticalx_authstatus bdk_cti_verticalx_authstatus_t;

static inline uint64_t BDK_CTI_VERTICALX_AUTHSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_AUTHSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fb8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_AUTHSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_AUTHSTATUS(a) bdk_cti_verticalx_authstatus_t
#define bustype_BDK_CTI_VERTICALX_AUTHSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_AUTHSTATUS(a) "CTI_VERTICALX_AUTHSTATUS"
#define busnum_BDK_CTI_VERTICALX_AUTHSTATUS(a) (a)
#define arguments_BDK_CTI_VERTICALX_AUTHSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_cidr0
 *
 * CTI Vertical Cidr0 Register
 * The CIDR0 register is part of the set of component identification registers.
 */
union bdk_cti_verticalx_cidr0
{
    uint32_t u;
    struct bdk_cti_verticalx_cidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x0D. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x0D. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_cidr0_s cn; */
};
typedef union bdk_cti_verticalx_cidr0 bdk_cti_verticalx_cidr0_t;

static inline uint64_t BDK_CTI_VERTICALX_CIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102ff0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CIDR0(a) bdk_cti_verticalx_cidr0_t
#define bustype_BDK_CTI_VERTICALX_CIDR0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CIDR0(a) "CTI_VERTICALX_CIDR0"
#define busnum_BDK_CTI_VERTICALX_CIDR0(a) (a)
#define arguments_BDK_CTI_VERTICALX_CIDR0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_cidr1
 *
 * CTI Vertical Cidr1 Register
 * The CIDR1 register is part of the set of component identification registers.
 */
union bdk_cti_verticalx_cidr1
{
    uint32_t u;
    struct bdk_cti_verticalx_cidr1_s
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
    /* struct bdk_cti_verticalx_cidr1_s cn; */
};
typedef union bdk_cti_verticalx_cidr1 bdk_cti_verticalx_cidr1_t;

static inline uint64_t BDK_CTI_VERTICALX_CIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102ff4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CIDR1(a) bdk_cti_verticalx_cidr1_t
#define bustype_BDK_CTI_VERTICALX_CIDR1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CIDR1(a) "CTI_VERTICALX_CIDR1"
#define busnum_BDK_CTI_VERTICALX_CIDR1(a) (a)
#define arguments_BDK_CTI_VERTICALX_CIDR1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_cidr2
 *
 * CTI Vertical Cidr2 Register
 * The CIDR2 register is part of the set of component identification registers.
 */
union bdk_cti_verticalx_cidr2
{
    uint32_t u;
    struct bdk_cti_verticalx_cidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x05. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x05. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_cidr2_s cn; */
};
typedef union bdk_cti_verticalx_cidr2 bdk_cti_verticalx_cidr2_t;

static inline uint64_t BDK_CTI_VERTICALX_CIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102ff8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CIDR2(a) bdk_cti_verticalx_cidr2_t
#define bustype_BDK_CTI_VERTICALX_CIDR2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CIDR2(a) "CTI_VERTICALX_CIDR2"
#define busnum_BDK_CTI_VERTICALX_CIDR2(a) (a)
#define arguments_BDK_CTI_VERTICALX_CIDR2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_cidr3
 *
 * CTI Vertical Cidr3 Register
 * The CIDR3 register is part of the set of component identification registers.
 */
union bdk_cti_verticalx_cidr3
{
    uint32_t u;
    struct bdk_cti_verticalx_cidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Returns 0xB1. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Returns 0xB1. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_cidr3_s cn; */
};
typedef union bdk_cti_verticalx_cidr3 bdk_cti_verticalx_cidr3_t;

static inline uint64_t BDK_CTI_VERTICALX_CIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102ffcll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CIDR3(a) bdk_cti_verticalx_cidr3_t
#define bustype_BDK_CTI_VERTICALX_CIDR3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CIDR3(a) "CTI_VERTICALX_CIDR3"
#define busnum_BDK_CTI_VERTICALX_CIDR3(a) (a)
#define arguments_BDK_CTI_VERTICALX_CIDR3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_claimclr
 *
 * CTI Vertical Claimclr Register
 * This register forms one half of the claim tag value. On writes, this location
 * enables individual bits to be cleared. On reads, it returns the current claim tag
 * value.
 */
union bdk_cti_verticalx_claimclr
{
    uint32_t u;
    struct bdk_cti_verticalx_claimclr_s
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
    /* struct bdk_cti_verticalx_claimclr_s cn; */
};
typedef union bdk_cti_verticalx_claimclr bdk_cti_verticalx_claimclr_t;

static inline uint64_t BDK_CTI_VERTICALX_CLAIMCLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CLAIMCLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fa4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CLAIMCLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CLAIMCLR(a) bdk_cti_verticalx_claimclr_t
#define bustype_BDK_CTI_VERTICALX_CLAIMCLR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CLAIMCLR(a) "CTI_VERTICALX_CLAIMCLR"
#define busnum_BDK_CTI_VERTICALX_CLAIMCLR(a) (a)
#define arguments_BDK_CTI_VERTICALX_CLAIMCLR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_claimset
 *
 * CTI Vertical Claimset Register
 * This register forms one half of the claim tag value. On writes, this location
 * enables individual bits to be set. On reads, it returns the number of bits that can
 * be set.
 */
union bdk_cti_verticalx_claimset
{
    uint32_t u;
    struct bdk_cti_verticalx_claimset_s
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
    /* struct bdk_cti_verticalx_claimset_s cn; */
};
typedef union bdk_cti_verticalx_claimset bdk_cti_verticalx_claimset_t;

static inline uint64_t BDK_CTI_VERTICALX_CLAIMSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CLAIMSET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fa0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CLAIMSET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CLAIMSET(a) bdk_cti_verticalx_claimset_t
#define bustype_BDK_CTI_VERTICALX_CLAIMSET(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CLAIMSET(a) "CTI_VERTICALX_CLAIMSET"
#define busnum_BDK_CTI_VERTICALX_CLAIMSET(a) (a)
#define arguments_BDK_CTI_VERTICALX_CLAIMSET(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiappclear
 *
 * CTI Vertical Ctiappclear Register
 * The application channel clear register allows software to clear any channel output.
 * This register can be used by software to clear a channel event in place of a
 * hardware source on a trigger input. In a system where all events are sent as single
 * cycle pulses, this register must not be used. It is only retained for compatibility
 * with older systems and software. The register is implemented before the CTIGATE
 * register so, for the channel event to propagate outside the CTI, it is necessary for
 * the corresponding CTIGATE bit to be 1.
 */
union bdk_cti_verticalx_ctiappclear
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiappclear_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
        uint32_t appclear              : 4;  /**< [  3:  0](WO) Clears the corresponding internal channel flag. */
#else /* Word 0 - Little Endian */
        uint32_t appclear              : 4;  /**< [  3:  0](WO) Clears the corresponding internal channel flag. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiappclear_s cn; */
};
typedef union bdk_cti_verticalx_ctiappclear bdk_cti_verticalx_ctiappclear_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIAPPCLEAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIAPPCLEAR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102018ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIAPPCLEAR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIAPPCLEAR(a) bdk_cti_verticalx_ctiappclear_t
#define bustype_BDK_CTI_VERTICALX_CTIAPPCLEAR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIAPPCLEAR(a) "CTI_VERTICALX_CTIAPPCLEAR"
#define busnum_BDK_CTI_VERTICALX_CTIAPPCLEAR(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIAPPCLEAR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiapppulse
 *
 * CTI Vertical Ctiapppulse Register
 * The application channel pulse register allows software to pulse any channel output.
 * This register can be used by software to pulse a channel event in place of a
 * hardware source on a trigger input. The register is implemented before the CTIGATE
 * register so, for the channel event to propagate outside the CTI, it is necessary for
 * the corresponding CTIGATE bit to be 1.
 */
union bdk_cti_verticalx_ctiapppulse
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiapppulse_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
        uint32_t apppulse              : 4;  /**< [  3:  0](WO) Pulses the channel outputs. */
#else /* Word 0 - Little Endian */
        uint32_t apppulse              : 4;  /**< [  3:  0](WO) Pulses the channel outputs. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiapppulse_s cn; */
};
typedef union bdk_cti_verticalx_ctiapppulse bdk_cti_verticalx_ctiapppulse_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIAPPPULSE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIAPPPULSE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610201cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIAPPPULSE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIAPPPULSE(a) bdk_cti_verticalx_ctiapppulse_t
#define bustype_BDK_CTI_VERTICALX_CTIAPPPULSE(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIAPPPULSE(a) "CTI_VERTICALX_CTIAPPPULSE"
#define busnum_BDK_CTI_VERTICALX_CTIAPPPULSE(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIAPPPULSE(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiappset
 *
 * CTI Vertical Ctiappset Register
 * The application channel set register allows software to set any channel output. This
 * register can be used by software to generate a channel event in place of a hardware
 * source on a trigger input. In a system where all events are sent as single cycle
 * pulses, this register must not be used. It is only retained for compatibility with
 * older systems and software. The register is implemented before the CTIGATE register
 * so, for the channel event to propagate outside the CTI, it is necessary for the
 * corresponding CTIGATE bit to be 1.
 */
union bdk_cti_verticalx_ctiappset
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiappset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t appset                : 4;  /**< [  3:  0](R/W) Sets the corresponding internal channel flag. */
#else /* Word 0 - Little Endian */
        uint32_t appset                : 4;  /**< [  3:  0](R/W) Sets the corresponding internal channel flag. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiappset_s cn; */
};
typedef union bdk_cti_verticalx_ctiappset bdk_cti_verticalx_ctiappset_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIAPPSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIAPPSET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102014ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIAPPSET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIAPPSET(a) bdk_cti_verticalx_ctiappset_t
#define bustype_BDK_CTI_VERTICALX_CTIAPPSET(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIAPPSET(a) "CTI_VERTICALX_CTIAPPSET"
#define busnum_BDK_CTI_VERTICALX_CTIAPPSET(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIAPPSET(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctichinstatus
 *
 * CTI Vertical Ctichinstatus Register
 * Channel input status. If the channel input is driven by a source that generates
 * single cycle pulses, this register is generally read as 0.
 */
union bdk_cti_verticalx_ctichinstatus
{
    uint32_t u;
    struct bdk_cti_verticalx_ctichinstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
        uint32_t ctichinstatus         : 4;  /**< [  3:  0](RO) Channel input status. */
#else /* Word 0 - Little Endian */
        uint32_t ctichinstatus         : 4;  /**< [  3:  0](RO) Channel input status. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctichinstatus_s cn; */
};
typedef union bdk_cti_verticalx_ctichinstatus bdk_cti_verticalx_ctichinstatus_t;

static inline uint64_t BDK_CTI_VERTICALX_CTICHINSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTICHINSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102138ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTICHINSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTICHINSTATUS(a) bdk_cti_verticalx_ctichinstatus_t
#define bustype_BDK_CTI_VERTICALX_CTICHINSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTICHINSTATUS(a) "CTI_VERTICALX_CTICHINSTATUS"
#define busnum_BDK_CTI_VERTICALX_CTICHINSTATUS(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTICHINSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctichoutstatus
 *
 * CTI Vertical Ctichoutstatus Register
 * Channel output status. The register only has meaning if the trigger source drives
 * static levels, rather than pulses.
 */
union bdk_cti_verticalx_ctichoutstatus
{
    uint32_t u;
    struct bdk_cti_verticalx_ctichoutstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
        uint32_t ctichoutstatus        : 4;  /**< [  3:  0](RO) Channel output status. */
#else /* Word 0 - Little Endian */
        uint32_t ctichoutstatus        : 4;  /**< [  3:  0](RO) Channel output status. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctichoutstatus_s cn; */
};
typedef union bdk_cti_verticalx_ctichoutstatus bdk_cti_verticalx_ctichoutstatus_t;

static inline uint64_t BDK_CTI_VERTICALX_CTICHOUTSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTICHOUTSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610213cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTICHOUTSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTICHOUTSTATUS(a) bdk_cti_verticalx_ctichoutstatus_t
#define bustype_BDK_CTI_VERTICALX_CTICHOUTSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTICHOUTSTATUS(a) "CTI_VERTICALX_CTICHOUTSTATUS"
#define busnum_BDK_CTI_VERTICALX_CTICHOUTSTATUS(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTICHOUTSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_cticontrol
 *
 * CTI Vertical Cticontrol Register
 * The CTI control register enables and disables the CTI.
 */
union bdk_cti_verticalx_cticontrol
{
    uint32_t u;
    struct bdk_cti_verticalx_cticontrol_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 31; /**< [ 31:  1](R/W) Software should write the field as all 0s. */
        uint32_t ctien                 : 1;  /**< [  0:  0](R/W) Enable control. */
#else /* Word 0 - Little Endian */
        uint32_t ctien                 : 1;  /**< [  0:  0](R/W) Enable control. */
        uint32_t sbz_0                 : 31; /**< [ 31:  1](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_cticontrol_s cn; */
};
typedef union bdk_cti_verticalx_cticontrol bdk_cti_verticalx_cticontrol_t;

static inline uint64_t BDK_CTI_VERTICALX_CTICONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTICONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102000ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTICONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTICONTROL(a) bdk_cti_verticalx_cticontrol_t
#define bustype_BDK_CTI_VERTICALX_CTICONTROL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTICONTROL(a) "CTI_VERTICALX_CTICONTROL"
#define busnum_BDK_CTI_VERTICALX_CTICONTROL(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTICONTROL(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctigate
 *
 * CTI Vertical Ctigate Register
 * Channel output gate.
 */
union bdk_cti_verticalx_ctigate
{
    uint32_t u;
    struct bdk_cti_verticalx_ctigate_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t ctigateen             : 4;  /**< [  3:  0](R/W) Enables the propagation of channel events out of the CTI, one bit per channel. */
#else /* Word 0 - Little Endian */
        uint32_t ctigateen             : 4;  /**< [  3:  0](R/W) Enables the propagation of channel events out of the CTI, one bit per channel. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctigate_s cn; */
};
typedef union bdk_cti_verticalx_ctigate bdk_cti_verticalx_ctigate_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIGATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIGATE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102140ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIGATE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIGATE(a) bdk_cti_verticalx_ctigate_t
#define bustype_BDK_CTI_VERTICALX_CTIGATE(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIGATE(a) "CTI_VERTICALX_CTIGATE"
#define busnum_BDK_CTI_VERTICALX_CTIGATE(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIGATE(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen0
 *
 * CTI Vertical Ctiinen0 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen0
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen0_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen0 bdk_cti_verticalx_ctiinen0_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102020ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN0(a) bdk_cti_verticalx_ctiinen0_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN0(a) "CTI_VERTICALX_CTIINEN0"
#define busnum_BDK_CTI_VERTICALX_CTIINEN0(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen1
 *
 * CTI Vertical Ctiinen1 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen1
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen1_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen1 bdk_cti_verticalx_ctiinen1_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102024ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN1(a) bdk_cti_verticalx_ctiinen1_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN1(a) "CTI_VERTICALX_CTIINEN1"
#define busnum_BDK_CTI_VERTICALX_CTIINEN1(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen10
 *
 * CTI Vertical Ctiinen10 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen10
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen10_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen10 bdk_cti_verticalx_ctiinen10_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN10(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN10(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102048ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN10", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN10(a) bdk_cti_verticalx_ctiinen10_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN10(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN10(a) "CTI_VERTICALX_CTIINEN10"
#define busnum_BDK_CTI_VERTICALX_CTIINEN10(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN10(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen11
 *
 * CTI Vertical Ctiinen11 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen11
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen11_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen11 bdk_cti_verticalx_ctiinen11_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN11(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN11(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610204cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN11", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN11(a) bdk_cti_verticalx_ctiinen11_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN11(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN11(a) "CTI_VERTICALX_CTIINEN11"
#define busnum_BDK_CTI_VERTICALX_CTIINEN11(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN11(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen12
 *
 * CTI Vertical Ctiinen12 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen12
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen12_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen12 bdk_cti_verticalx_ctiinen12_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN12(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN12(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102050ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN12", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN12(a) bdk_cti_verticalx_ctiinen12_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN12(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN12(a) "CTI_VERTICALX_CTIINEN12"
#define busnum_BDK_CTI_VERTICALX_CTIINEN12(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN12(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen13
 *
 * CTI Vertical Ctiinen13 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen13
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen13_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen13_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen13 bdk_cti_verticalx_ctiinen13_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN13(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN13(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102054ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN13", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN13(a) bdk_cti_verticalx_ctiinen13_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN13(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN13(a) "CTI_VERTICALX_CTIINEN13"
#define busnum_BDK_CTI_VERTICALX_CTIINEN13(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN13(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen14
 *
 * CTI Vertical Ctiinen14 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen14
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen14_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen14_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen14 bdk_cti_verticalx_ctiinen14_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN14(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN14(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102058ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN14", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN14(a) bdk_cti_verticalx_ctiinen14_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN14(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN14(a) "CTI_VERTICALX_CTIINEN14"
#define busnum_BDK_CTI_VERTICALX_CTIINEN14(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN14(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen15
 *
 * CTI Vertical Ctiinen15 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen15
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen15_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen15_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen15 bdk_cti_verticalx_ctiinen15_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN15(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN15(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610205cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN15", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN15(a) bdk_cti_verticalx_ctiinen15_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN15(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN15(a) "CTI_VERTICALX_CTIINEN15"
#define busnum_BDK_CTI_VERTICALX_CTIINEN15(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN15(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen16
 *
 * CTI Vertical Ctiinen16 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen16
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen16_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen16_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen16 bdk_cti_verticalx_ctiinen16_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN16(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN16(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102060ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN16", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN16(a) bdk_cti_verticalx_ctiinen16_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN16(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN16(a) "CTI_VERTICALX_CTIINEN16"
#define busnum_BDK_CTI_VERTICALX_CTIINEN16(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN16(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen17
 *
 * CTI Vertical Ctiinen17 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen17
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen17_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen17_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen17 bdk_cti_verticalx_ctiinen17_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN17(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN17(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102064ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN17", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN17(a) bdk_cti_verticalx_ctiinen17_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN17(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN17(a) "CTI_VERTICALX_CTIINEN17"
#define busnum_BDK_CTI_VERTICALX_CTIINEN17(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN17(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen18
 *
 * CTI Vertical Ctiinen18 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen18
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen18_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen18_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen18 bdk_cti_verticalx_ctiinen18_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN18(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN18(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102068ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN18", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN18(a) bdk_cti_verticalx_ctiinen18_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN18(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN18(a) "CTI_VERTICALX_CTIINEN18"
#define busnum_BDK_CTI_VERTICALX_CTIINEN18(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN18(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen19
 *
 * CTI Vertical Ctiinen19 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen19
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen19_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen19_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen19 bdk_cti_verticalx_ctiinen19_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN19(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN19(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610206cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN19", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN19(a) bdk_cti_verticalx_ctiinen19_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN19(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN19(a) "CTI_VERTICALX_CTIINEN19"
#define busnum_BDK_CTI_VERTICALX_CTIINEN19(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN19(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen2
 *
 * CTI Vertical Ctiinen2 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen2
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen2_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen2 bdk_cti_verticalx_ctiinen2_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102028ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN2(a) bdk_cti_verticalx_ctiinen2_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN2(a) "CTI_VERTICALX_CTIINEN2"
#define busnum_BDK_CTI_VERTICALX_CTIINEN2(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen20
 *
 * CTI Vertical Ctiinen20 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen20
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen20_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen20_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen20 bdk_cti_verticalx_ctiinen20_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN20(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN20(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102070ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN20", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN20(a) bdk_cti_verticalx_ctiinen20_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN20(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN20(a) "CTI_VERTICALX_CTIINEN20"
#define busnum_BDK_CTI_VERTICALX_CTIINEN20(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN20(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen21
 *
 * CTI Vertical Ctiinen21 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen21
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen21_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen21_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen21 bdk_cti_verticalx_ctiinen21_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN21(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN21(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102074ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN21", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN21(a) bdk_cti_verticalx_ctiinen21_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN21(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN21(a) "CTI_VERTICALX_CTIINEN21"
#define busnum_BDK_CTI_VERTICALX_CTIINEN21(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN21(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen22
 *
 * CTI Vertical Ctiinen22 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen22
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen22_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen22_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen22 bdk_cti_verticalx_ctiinen22_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN22(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN22(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102078ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN22", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN22(a) bdk_cti_verticalx_ctiinen22_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN22(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN22(a) "CTI_VERTICALX_CTIINEN22"
#define busnum_BDK_CTI_VERTICALX_CTIINEN22(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN22(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen23
 *
 * CTI Vertical Ctiinen23 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen23
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen23_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen23_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen23 bdk_cti_verticalx_ctiinen23_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN23(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN23(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610207cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN23", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN23(a) bdk_cti_verticalx_ctiinen23_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN23(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN23(a) "CTI_VERTICALX_CTIINEN23"
#define busnum_BDK_CTI_VERTICALX_CTIINEN23(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN23(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen24
 *
 * CTI Vertical Ctiinen24 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen24
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen24_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen24_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen24 bdk_cti_verticalx_ctiinen24_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN24(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN24(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102080ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN24", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN24(a) bdk_cti_verticalx_ctiinen24_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN24(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN24(a) "CTI_VERTICALX_CTIINEN24"
#define busnum_BDK_CTI_VERTICALX_CTIINEN24(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN24(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen25
 *
 * CTI Vertical Ctiinen25 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen25
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen25_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen25_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen25 bdk_cti_verticalx_ctiinen25_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN25(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN25(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102084ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN25", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN25(a) bdk_cti_verticalx_ctiinen25_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN25(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN25(a) "CTI_VERTICALX_CTIINEN25"
#define busnum_BDK_CTI_VERTICALX_CTIINEN25(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN25(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen26
 *
 * CTI Vertical Ctiinen26 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen26
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen26_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen26_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen26 bdk_cti_verticalx_ctiinen26_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN26(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN26(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102088ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN26", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN26(a) bdk_cti_verticalx_ctiinen26_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN26(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN26(a) "CTI_VERTICALX_CTIINEN26"
#define busnum_BDK_CTI_VERTICALX_CTIINEN26(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN26(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen27
 *
 * CTI Vertical Ctiinen27 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen27
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen27_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen27_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen27 bdk_cti_verticalx_ctiinen27_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN27(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN27(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610208cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN27", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN27(a) bdk_cti_verticalx_ctiinen27_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN27(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN27(a) "CTI_VERTICALX_CTIINEN27"
#define busnum_BDK_CTI_VERTICALX_CTIINEN27(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN27(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen28
 *
 * CTI Vertical Ctiinen28 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen28
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen28_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen28_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen28 bdk_cti_verticalx_ctiinen28_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN28(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN28(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102090ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN28", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN28(a) bdk_cti_verticalx_ctiinen28_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN28(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN28(a) "CTI_VERTICALX_CTIINEN28"
#define busnum_BDK_CTI_VERTICALX_CTIINEN28(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN28(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen29
 *
 * CTI Vertical Ctiinen29 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen29
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen29_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen29_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen29 bdk_cti_verticalx_ctiinen29_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN29(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN29(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102094ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN29", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN29(a) bdk_cti_verticalx_ctiinen29_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN29(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN29(a) "CTI_VERTICALX_CTIINEN29"
#define busnum_BDK_CTI_VERTICALX_CTIINEN29(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN29(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen3
 *
 * CTI Vertical Ctiinen3 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen3
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen3_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen3 bdk_cti_verticalx_ctiinen3_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610202cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN3(a) bdk_cti_verticalx_ctiinen3_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN3(a) "CTI_VERTICALX_CTIINEN3"
#define busnum_BDK_CTI_VERTICALX_CTIINEN3(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen30
 *
 * CTI Vertical Ctiinen30 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen30
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen30_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen30_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen30 bdk_cti_verticalx_ctiinen30_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN30(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN30(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102098ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN30", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN30(a) bdk_cti_verticalx_ctiinen30_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN30(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN30(a) "CTI_VERTICALX_CTIINEN30"
#define busnum_BDK_CTI_VERTICALX_CTIINEN30(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN30(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen31
 *
 * CTI Vertical Ctiinen31 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen31
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen31_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen31_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen31 bdk_cti_verticalx_ctiinen31_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN31(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN31(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610209cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN31", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN31(a) bdk_cti_verticalx_ctiinen31_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN31(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN31(a) "CTI_VERTICALX_CTIINEN31"
#define busnum_BDK_CTI_VERTICALX_CTIINEN31(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN31(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen4
 *
 * CTI Vertical Ctiinen4 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen4
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen4_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen4 bdk_cti_verticalx_ctiinen4_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102030ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN4(a) bdk_cti_verticalx_ctiinen4_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN4(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN4(a) "CTI_VERTICALX_CTIINEN4"
#define busnum_BDK_CTI_VERTICALX_CTIINEN4(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN4(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen5
 *
 * CTI Vertical Ctiinen5 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen5
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen5_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen5 bdk_cti_verticalx_ctiinen5_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102034ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN5(a) bdk_cti_verticalx_ctiinen5_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN5(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN5(a) "CTI_VERTICALX_CTIINEN5"
#define busnum_BDK_CTI_VERTICALX_CTIINEN5(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN5(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen6
 *
 * CTI Vertical Ctiinen6 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen6
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen6_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen6 bdk_cti_verticalx_ctiinen6_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102038ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN6(a) bdk_cti_verticalx_ctiinen6_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN6(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN6(a) "CTI_VERTICALX_CTIINEN6"
#define busnum_BDK_CTI_VERTICALX_CTIINEN6(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN6(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen7
 *
 * CTI Vertical Ctiinen7 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen7
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen7_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen7 bdk_cti_verticalx_ctiinen7_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610203cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN7(a) bdk_cti_verticalx_ctiinen7_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN7(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN7(a) "CTI_VERTICALX_CTIINEN7"
#define busnum_BDK_CTI_VERTICALX_CTIINEN7(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN7(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen8
 *
 * CTI Vertical Ctiinen8 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen8
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen8_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen8 bdk_cti_verticalx_ctiinen8_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN8(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN8(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102040ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN8", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN8(a) bdk_cti_verticalx_ctiinen8_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN8(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN8(a) "CTI_VERTICALX_CTIINEN8"
#define busnum_BDK_CTI_VERTICALX_CTIINEN8(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN8(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiinen9
 *
 * CTI Vertical Ctiinen9 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_verticalx_ctiinen9
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiinen9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiinen9_s cn; */
};
typedef union bdk_cti_verticalx_ctiinen9 bdk_cti_verticalx_ctiinen9_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINEN9(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINEN9(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102044ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINEN9", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINEN9(a) bdk_cti_verticalx_ctiinen9_t
#define bustype_BDK_CTI_VERTICALX_CTIINEN9(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINEN9(a) "CTI_VERTICALX_CTIINEN9"
#define busnum_BDK_CTI_VERTICALX_CTIINEN9(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINEN9(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiintack
 *
 * CTI Vertical Ctiintack Register
 * Software acknowledge for trigger outputs. The CTIINTACK register is a bit map that
 * allows selective clearing of trigger output events. If the SW_HANDSHAKE parameter
 * for a trigger output is set, indicating that the output latches HIGH when an event
 * is sent to that output, then the output remains HIGH until the corresponding INTACK
 * bit is written to a 1. A write of a bit to 0 has no effect. This allows different
 * software threads to be responsible for clearing different trigger outputs without
 * needing to perform a read-modify-write operation to find which bits are set.
 */
union bdk_cti_verticalx_ctiintack
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiintack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t intack                : 32; /**< [ 31:  0](WO) Acknowledges the corresponding event_out output. */
#else /* Word 0 - Little Endian */
        uint32_t intack                : 32; /**< [ 31:  0](WO) Acknowledges the corresponding event_out output. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiintack_s cn; */
};
typedef union bdk_cti_verticalx_ctiintack bdk_cti_verticalx_ctiintack_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIINTACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIINTACK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102010ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIINTACK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIINTACK(a) bdk_cti_verticalx_ctiintack_t
#define bustype_BDK_CTI_VERTICALX_CTIINTACK(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIINTACK(a) "CTI_VERTICALX_CTIINTACK"
#define busnum_BDK_CTI_VERTICALX_CTIINTACK(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIINTACK(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten0
 *
 * CTI Vertical Ctiouten0 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten0
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten0_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten0 bdk_cti_verticalx_ctiouten0_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020a0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN0(a) bdk_cti_verticalx_ctiouten0_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN0(a) "CTI_VERTICALX_CTIOUTEN0"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN0(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten1
 *
 * CTI Vertical Ctiouten1 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten1
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten1_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten1 bdk_cti_verticalx_ctiouten1_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020a4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN1(a) bdk_cti_verticalx_ctiouten1_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN1(a) "CTI_VERTICALX_CTIOUTEN1"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN1(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten10
 *
 * CTI Vertical Ctiouten10 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten10
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten10_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten10 bdk_cti_verticalx_ctiouten10_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN10(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN10(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020c8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN10", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN10(a) bdk_cti_verticalx_ctiouten10_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN10(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN10(a) "CTI_VERTICALX_CTIOUTEN10"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN10(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN10(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten11
 *
 * CTI Vertical Ctiouten11 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten11
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten11_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten11 bdk_cti_verticalx_ctiouten11_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN11(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN11(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020ccll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN11", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN11(a) bdk_cti_verticalx_ctiouten11_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN11(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN11(a) "CTI_VERTICALX_CTIOUTEN11"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN11(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN11(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten12
 *
 * CTI Vertical Ctiouten12 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten12
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten12_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten12 bdk_cti_verticalx_ctiouten12_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN12(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN12(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020d0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN12", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN12(a) bdk_cti_verticalx_ctiouten12_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN12(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN12(a) "CTI_VERTICALX_CTIOUTEN12"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN12(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN12(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten13
 *
 * CTI Vertical Ctiouten13 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten13
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten13_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten13_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten13 bdk_cti_verticalx_ctiouten13_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN13(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN13(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020d4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN13", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN13(a) bdk_cti_verticalx_ctiouten13_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN13(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN13(a) "CTI_VERTICALX_CTIOUTEN13"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN13(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN13(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten14
 *
 * CTI Vertical Ctiouten14 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten14
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten14_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten14_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten14 bdk_cti_verticalx_ctiouten14_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN14(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN14(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020d8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN14", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN14(a) bdk_cti_verticalx_ctiouten14_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN14(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN14(a) "CTI_VERTICALX_CTIOUTEN14"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN14(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN14(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten15
 *
 * CTI Vertical Ctiouten15 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten15
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten15_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten15_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten15 bdk_cti_verticalx_ctiouten15_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN15(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN15(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020dcll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN15", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN15(a) bdk_cti_verticalx_ctiouten15_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN15(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN15(a) "CTI_VERTICALX_CTIOUTEN15"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN15(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN15(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten16
 *
 * CTI Vertical Ctiouten16 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten16
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten16_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten16_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten16 bdk_cti_verticalx_ctiouten16_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN16(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN16(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020e0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN16", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN16(a) bdk_cti_verticalx_ctiouten16_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN16(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN16(a) "CTI_VERTICALX_CTIOUTEN16"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN16(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN16(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten17
 *
 * CTI Vertical Ctiouten17 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten17
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten17_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten17_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten17 bdk_cti_verticalx_ctiouten17_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN17(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN17(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020e4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN17", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN17(a) bdk_cti_verticalx_ctiouten17_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN17(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN17(a) "CTI_VERTICALX_CTIOUTEN17"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN17(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN17(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten18
 *
 * CTI Vertical Ctiouten18 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten18
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten18_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten18_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten18 bdk_cti_verticalx_ctiouten18_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN18(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN18(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020e8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN18", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN18(a) bdk_cti_verticalx_ctiouten18_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN18(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN18(a) "CTI_VERTICALX_CTIOUTEN18"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN18(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN18(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten19
 *
 * CTI Vertical Ctiouten19 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten19
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten19_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten19_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten19 bdk_cti_verticalx_ctiouten19_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN19(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN19(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020ecll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN19", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN19(a) bdk_cti_verticalx_ctiouten19_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN19(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN19(a) "CTI_VERTICALX_CTIOUTEN19"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN19(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN19(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten2
 *
 * CTI Vertical Ctiouten2 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten2
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten2_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten2 bdk_cti_verticalx_ctiouten2_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020a8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN2(a) bdk_cti_verticalx_ctiouten2_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN2(a) "CTI_VERTICALX_CTIOUTEN2"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN2(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten20
 *
 * CTI Vertical Ctiouten20 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten20
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten20_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten20_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten20 bdk_cti_verticalx_ctiouten20_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN20(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN20(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020f0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN20", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN20(a) bdk_cti_verticalx_ctiouten20_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN20(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN20(a) "CTI_VERTICALX_CTIOUTEN20"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN20(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN20(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten21
 *
 * CTI Vertical Ctiouten21 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten21
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten21_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten21_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten21 bdk_cti_verticalx_ctiouten21_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN21(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN21(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020f4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN21", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN21(a) bdk_cti_verticalx_ctiouten21_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN21(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN21(a) "CTI_VERTICALX_CTIOUTEN21"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN21(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN21(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten22
 *
 * CTI Vertical Ctiouten22 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten22
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten22_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten22_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten22 bdk_cti_verticalx_ctiouten22_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN22(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN22(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020f8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN22", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN22(a) bdk_cti_verticalx_ctiouten22_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN22(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN22(a) "CTI_VERTICALX_CTIOUTEN22"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN22(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN22(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten23
 *
 * CTI Vertical Ctiouten23 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten23
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten23_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten23_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten23 bdk_cti_verticalx_ctiouten23_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN23(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN23(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020fcll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN23", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN23(a) bdk_cti_verticalx_ctiouten23_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN23(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN23(a) "CTI_VERTICALX_CTIOUTEN23"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN23(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN23(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten24
 *
 * CTI Vertical Ctiouten24 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten24
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten24_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten24_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten24 bdk_cti_verticalx_ctiouten24_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN24(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN24(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102100ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN24", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN24(a) bdk_cti_verticalx_ctiouten24_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN24(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN24(a) "CTI_VERTICALX_CTIOUTEN24"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN24(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN24(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten25
 *
 * CTI Vertical Ctiouten25 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten25
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten25_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten25_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten25 bdk_cti_verticalx_ctiouten25_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN25(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN25(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102104ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN25", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN25(a) bdk_cti_verticalx_ctiouten25_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN25(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN25(a) "CTI_VERTICALX_CTIOUTEN25"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN25(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN25(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten26
 *
 * CTI Vertical Ctiouten26 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten26
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten26_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten26_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten26 bdk_cti_verticalx_ctiouten26_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN26(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN26(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102108ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN26", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN26(a) bdk_cti_verticalx_ctiouten26_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN26(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN26(a) "CTI_VERTICALX_CTIOUTEN26"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN26(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN26(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten27
 *
 * CTI Vertical Ctiouten27 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten27
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten27_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten27_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten27 bdk_cti_verticalx_ctiouten27_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN27(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN27(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610210cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN27", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN27(a) bdk_cti_verticalx_ctiouten27_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN27(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN27(a) "CTI_VERTICALX_CTIOUTEN27"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN27(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN27(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten28
 *
 * CTI Vertical Ctiouten28 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten28
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten28_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten28_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten28 bdk_cti_verticalx_ctiouten28_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN28(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN28(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102110ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN28", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN28(a) bdk_cti_verticalx_ctiouten28_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN28(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN28(a) "CTI_VERTICALX_CTIOUTEN28"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN28(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN28(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten29
 *
 * CTI Vertical Ctiouten29 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten29
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten29_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten29_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten29 bdk_cti_verticalx_ctiouten29_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN29(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN29(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102114ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN29", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN29(a) bdk_cti_verticalx_ctiouten29_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN29(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN29(a) "CTI_VERTICALX_CTIOUTEN29"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN29(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN29(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten3
 *
 * CTI Vertical Ctiouten3 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten3
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten3_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten3 bdk_cti_verticalx_ctiouten3_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020acll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN3(a) bdk_cti_verticalx_ctiouten3_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN3(a) "CTI_VERTICALX_CTIOUTEN3"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN3(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten30
 *
 * CTI Vertical Ctiouten30 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten30
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten30_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten30_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten30 bdk_cti_verticalx_ctiouten30_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN30(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN30(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102118ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN30", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN30(a) bdk_cti_verticalx_ctiouten30_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN30(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN30(a) "CTI_VERTICALX_CTIOUTEN30"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN30(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN30(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten31
 *
 * CTI Vertical Ctiouten31 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten31
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten31_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten31_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten31 bdk_cti_verticalx_ctiouten31_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN31(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN31(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e04610211cll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN31", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN31(a) bdk_cti_verticalx_ctiouten31_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN31(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN31(a) "CTI_VERTICALX_CTIOUTEN31"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN31(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN31(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten4
 *
 * CTI Vertical Ctiouten4 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten4
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten4_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten4 bdk_cti_verticalx_ctiouten4_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020b0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN4(a) bdk_cti_verticalx_ctiouten4_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN4(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN4(a) "CTI_VERTICALX_CTIOUTEN4"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN4(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN4(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten5
 *
 * CTI Vertical Ctiouten5 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten5
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten5_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten5 bdk_cti_verticalx_ctiouten5_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020b4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN5(a) bdk_cti_verticalx_ctiouten5_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN5(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN5(a) "CTI_VERTICALX_CTIOUTEN5"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN5(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN5(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten6
 *
 * CTI Vertical Ctiouten6 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten6
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten6_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten6 bdk_cti_verticalx_ctiouten6_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020b8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN6(a) bdk_cti_verticalx_ctiouten6_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN6(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN6(a) "CTI_VERTICALX_CTIOUTEN6"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN6(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN6(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten7
 *
 * CTI Vertical Ctiouten7 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten7
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten7_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten7 bdk_cti_verticalx_ctiouten7_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020bcll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN7(a) bdk_cti_verticalx_ctiouten7_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN7(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN7(a) "CTI_VERTICALX_CTIOUTEN7"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN7(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN7(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten8
 *
 * CTI Vertical Ctiouten8 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten8
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten8_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten8 bdk_cti_verticalx_ctiouten8_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN8(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN8(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020c0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN8", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN8(a) bdk_cti_verticalx_ctiouten8_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN8(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN8(a) "CTI_VERTICALX_CTIOUTEN8"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN8(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN8(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctiouten9
 *
 * CTI Vertical Ctiouten9 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_verticalx_ctiouten9
{
    uint32_t u;
    struct bdk_cti_verticalx_ctiouten9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctiouten9_s cn; */
};
typedef union bdk_cti_verticalx_ctiouten9 bdk_cti_verticalx_ctiouten9_t;

static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN9(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTIOUTEN9(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e0461020c4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTIOUTEN9", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTIOUTEN9(a) bdk_cti_verticalx_ctiouten9_t
#define bustype_BDK_CTI_VERTICALX_CTIOUTEN9(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTIOUTEN9(a) "CTI_VERTICALX_CTIOUTEN9"
#define busnum_BDK_CTI_VERTICALX_CTIOUTEN9(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTIOUTEN9(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctitriginstatus
 *
 * CTI Vertical Ctitriginstatus Register
 * Trigger input status. If the event_in input is driven by a source that generates
 * single cycle pulses, this register is generally read as 0.
 */
union bdk_cti_verticalx_ctitriginstatus
{
    uint32_t u;
    struct bdk_cti_verticalx_ctitriginstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t triginstatus          : 32; /**< [ 31:  0](RO) Trigger input status. */
#else /* Word 0 - Little Endian */
        uint32_t triginstatus          : 32; /**< [ 31:  0](RO) Trigger input status. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctitriginstatus_s cn; */
};
typedef union bdk_cti_verticalx_ctitriginstatus bdk_cti_verticalx_ctitriginstatus_t;

static inline uint64_t BDK_CTI_VERTICALX_CTITRIGINSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTITRIGINSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102130ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTITRIGINSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTITRIGINSTATUS(a) bdk_cti_verticalx_ctitriginstatus_t
#define bustype_BDK_CTI_VERTICALX_CTITRIGINSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTITRIGINSTATUS(a) "CTI_VERTICALX_CTITRIGINSTATUS"
#define busnum_BDK_CTI_VERTICALX_CTITRIGINSTATUS(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTITRIGINSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ctitrigoutstatus
 *
 * CTI Vertical Ctitrigoutstatus Register
 * Trigger output status. The register only has meaning if the trigger source drives
 * static levels, rather than pulses.
 */
union bdk_cti_verticalx_ctitrigoutstatus
{
    uint32_t u;
    struct bdk_cti_verticalx_ctitrigoutstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t trigoutstatus         : 32; /**< [ 31:  0](RO) Trigger output status. */
#else /* Word 0 - Little Endian */
        uint32_t trigoutstatus         : 32; /**< [ 31:  0](RO) Trigger output status. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ctitrigoutstatus_s cn; */
};
typedef union bdk_cti_verticalx_ctitrigoutstatus bdk_cti_verticalx_ctitrigoutstatus_t;

static inline uint64_t BDK_CTI_VERTICALX_CTITRIGOUTSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_CTITRIGOUTSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102134ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_CTITRIGOUTSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_CTITRIGOUTSTATUS(a) bdk_cti_verticalx_ctitrigoutstatus_t
#define bustype_BDK_CTI_VERTICALX_CTITRIGOUTSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_CTITRIGOUTSTATUS(a) "CTI_VERTICALX_CTITRIGOUTSTATUS"
#define busnum_BDK_CTI_VERTICALX_CTITRIGOUTSTATUS(a) (a)
#define arguments_BDK_CTI_VERTICALX_CTITRIGOUTSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_devaff0
 *
 * CTI Vertical Devaff0 Register
 * Enables a debugger to determine if two components have an affinity with each other.
 */
union bdk_cti_verticalx_devaff0
{
    uint32_t u;
    struct bdk_cti_verticalx_devaff0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devaff0               : 32; /**< [ 31:  0](RO) Lower 32-bits of DEVAFF. The value is set by the devaff[31:0] tie-off inputs. */
#else /* Word 0 - Little Endian */
        uint32_t devaff0               : 32; /**< [ 31:  0](RO) Lower 32-bits of DEVAFF. The value is set by the devaff[31:0] tie-off inputs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_devaff0_s cn; */
};
typedef union bdk_cti_verticalx_devaff0 bdk_cti_verticalx_devaff0_t;

static inline uint64_t BDK_CTI_VERTICALX_DEVAFF0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_DEVAFF0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fa8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_DEVAFF0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_DEVAFF0(a) bdk_cti_verticalx_devaff0_t
#define bustype_BDK_CTI_VERTICALX_DEVAFF0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_DEVAFF0(a) "CTI_VERTICALX_DEVAFF0"
#define busnum_BDK_CTI_VERTICALX_DEVAFF0(a) (a)
#define arguments_BDK_CTI_VERTICALX_DEVAFF0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_devaff1
 *
 * CTI Vertical Devaff1 Register
 * Enables a debugger to determine if two components have an affinity with each other.
 */
union bdk_cti_verticalx_devaff1
{
    uint32_t u;
    struct bdk_cti_verticalx_devaff1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devaff1               : 32; /**< [ 31:  0](RO) Upper 32-bits of DEVAFF. The value is set by the devaff[63:32] tie-off inputs. */
#else /* Word 0 - Little Endian */
        uint32_t devaff1               : 32; /**< [ 31:  0](RO) Upper 32-bits of DEVAFF. The value is set by the devaff[63:32] tie-off inputs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_devaff1_s cn; */
};
typedef union bdk_cti_verticalx_devaff1 bdk_cti_verticalx_devaff1_t;

static inline uint64_t BDK_CTI_VERTICALX_DEVAFF1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_DEVAFF1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102facll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_DEVAFF1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_DEVAFF1(a) bdk_cti_verticalx_devaff1_t
#define bustype_BDK_CTI_VERTICALX_DEVAFF1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_DEVAFF1(a) "CTI_VERTICALX_DEVAFF1"
#define busnum_BDK_CTI_VERTICALX_DEVAFF1(a) (a)
#define arguments_BDK_CTI_VERTICALX_DEVAFF1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_devarch
 *
 * CTI Vertical Devarch Register
 * Identifies the architect and architecture of a CoreSight component. The architect
 * might differ from the designer of a component, for example Arm defines the
 * architecture but another company designs and implements the component.
 */
union bdk_cti_verticalx_devarch
{
    uint32_t u;
    struct bdk_cti_verticalx_devarch_s
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
    /* struct bdk_cti_verticalx_devarch_s cn; */
};
typedef union bdk_cti_verticalx_devarch bdk_cti_verticalx_devarch_t;

static inline uint64_t BDK_CTI_VERTICALX_DEVARCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_DEVARCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fbcll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_DEVARCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_DEVARCH(a) bdk_cti_verticalx_devarch_t
#define bustype_BDK_CTI_VERTICALX_DEVARCH(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_DEVARCH(a) "CTI_VERTICALX_DEVARCH"
#define busnum_BDK_CTI_VERTICALX_DEVARCH(a) (a)
#define arguments_BDK_CTI_VERTICALX_DEVARCH(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_devid
 *
 * CTI Vertical Devid Register
 * This register is IMPLEMENTATION DEFINED for each Part Number and Designer. The
 * register indicates the capabilities of the component.
 */
union bdk_cti_verticalx_devid
{
    uint32_t u;
    struct bdk_cti_verticalx_devid_s
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
    /* struct bdk_cti_verticalx_devid_s cn; */
};
typedef union bdk_cti_verticalx_devid bdk_cti_verticalx_devid_t;

static inline uint64_t BDK_CTI_VERTICALX_DEVID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_DEVID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fc8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_DEVID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_DEVID(a) bdk_cti_verticalx_devid_t
#define bustype_BDK_CTI_VERTICALX_DEVID(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_DEVID(a) "CTI_VERTICALX_DEVID"
#define busnum_BDK_CTI_VERTICALX_DEVID(a) (a)
#define arguments_BDK_CTI_VERTICALX_DEVID(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_devtype
 *
 * CTI Vertical Devtype Register
 * A debugger can use this register to get information about a component that has an
 * unrecognized Part number.
 */
union bdk_cti_verticalx_devtype
{
    uint32_t u;
    struct bdk_cti_verticalx_devtype_s
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
    /* struct bdk_cti_verticalx_devtype_s cn; */
};
typedef union bdk_cti_verticalx_devtype bdk_cti_verticalx_devtype_t;

static inline uint64_t BDK_CTI_VERTICALX_DEVTYPE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_DEVTYPE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fccll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_DEVTYPE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_DEVTYPE(a) bdk_cti_verticalx_devtype_t
#define bustype_BDK_CTI_VERTICALX_DEVTYPE(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_DEVTYPE(a) "CTI_VERTICALX_DEVTYPE"
#define busnum_BDK_CTI_VERTICALX_DEVTYPE(a) (a)
#define arguments_BDK_CTI_VERTICALX_DEVTYPE(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_itchin
 *
 * CTI Vertical Itchin Register
 * Integration test to view channel events. The integration test register includes a
 * latch that is set when a pulse is received on a channel input. When read, a register
 * bit reads as 1 if the channel has received a pulse since it was last read. The act
 * of reading the register automatically clears the 1 to a 0. When performing
 * integration testing it is therefore important to coordinate the setting of event
 * latches and reading/clearing them.
 */
union bdk_cti_verticalx_itchin
{
    uint32_t u;
    struct bdk_cti_verticalx_itchin_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
        uint32_t ctichin               : 4;  /**< [  3:  0](RO) Reads the latched value of the channel inputs. */
#else /* Word 0 - Little Endian */
        uint32_t ctichin               : 4;  /**< [  3:  0](RO) Reads the latched value of the channel inputs. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_itchin_s cn; */
};
typedef union bdk_cti_verticalx_itchin bdk_cti_verticalx_itchin_t;

static inline uint64_t BDK_CTI_VERTICALX_ITCHIN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_ITCHIN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102ef4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_ITCHIN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_ITCHIN(a) bdk_cti_verticalx_itchin_t
#define bustype_BDK_CTI_VERTICALX_ITCHIN(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_ITCHIN(a) "CTI_VERTICALX_ITCHIN"
#define busnum_BDK_CTI_VERTICALX_ITCHIN(a) (a)
#define arguments_BDK_CTI_VERTICALX_ITCHIN(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_itchout
 *
 * CTI Vertical Itchout Register
 * Integration test mode register, used to generate channel events. Writing to the
 * register creates a single pulse on the output. ITCHOUT is self-clearing.
 */
union bdk_cti_verticalx_itchout
{
    uint32_t u;
    struct bdk_cti_verticalx_itchout_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t ctichout              : 4;  /**< [  3:  0](R/W) Pulses the channel outputs. */
#else /* Word 0 - Little Endian */
        uint32_t ctichout              : 4;  /**< [  3:  0](R/W) Pulses the channel outputs. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_itchout_s cn; */
};
typedef union bdk_cti_verticalx_itchout bdk_cti_verticalx_itchout_t;

static inline uint64_t BDK_CTI_VERTICALX_ITCHOUT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_ITCHOUT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102ee4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_ITCHOUT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_ITCHOUT(a) bdk_cti_verticalx_itchout_t
#define bustype_BDK_CTI_VERTICALX_ITCHOUT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_ITCHOUT(a) "CTI_VERTICALX_ITCHOUT"
#define busnum_BDK_CTI_VERTICALX_ITCHOUT(a) (a)
#define arguments_BDK_CTI_VERTICALX_ITCHOUT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_itctrl
 *
 * CTI Vertical Itctrl Register
 * The Integration Mode Control register is used to enable topology detection.
 */
union bdk_cti_verticalx_itctrl
{
    uint32_t u;
    struct bdk_cti_verticalx_itctrl_s
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
    /* struct bdk_cti_verticalx_itctrl_s cn; */
};
typedef union bdk_cti_verticalx_itctrl bdk_cti_verticalx_itctrl_t;

static inline uint64_t BDK_CTI_VERTICALX_ITCTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_ITCTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102f00ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_ITCTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_ITCTRL(a) bdk_cti_verticalx_itctrl_t
#define bustype_BDK_CTI_VERTICALX_ITCTRL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_ITCTRL(a) "CTI_VERTICALX_ITCTRL"
#define busnum_BDK_CTI_VERTICALX_ITCTRL(a) (a)
#define arguments_BDK_CTI_VERTICALX_ITCTRL(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ittrigin
 *
 * CTI Vertical Ittrigin Register
 * Integration test to view trigger events. The integration test register includes a
 * latch that is set when a pulse is received on a trigger input. When read, a register
 * bit reads as 1 if the trigger input has received a pulse since it was last read. The
 * act of reading the register automatically clears the 1 to a 0. When performing
 * integration testing it is therefore important to coordinate the setting of event
 * latches and reading/clearing them.
 */
union bdk_cti_verticalx_ittrigin
{
    uint32_t u;
    struct bdk_cti_verticalx_ittrigin_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ctitrigin             : 32; /**< [ 31:  0](RO) Reads the latched value of the trigger inputs. */
#else /* Word 0 - Little Endian */
        uint32_t ctitrigin             : 32; /**< [ 31:  0](RO) Reads the latched value of the trigger inputs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ittrigin_s cn; */
};
typedef union bdk_cti_verticalx_ittrigin bdk_cti_verticalx_ittrigin_t;

static inline uint64_t BDK_CTI_VERTICALX_ITTRIGIN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_ITTRIGIN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102ef8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_ITTRIGIN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_ITTRIGIN(a) bdk_cti_verticalx_ittrigin_t
#define bustype_BDK_CTI_VERTICALX_ITTRIGIN(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_ITTRIGIN(a) "CTI_VERTICALX_ITTRIGIN"
#define busnum_BDK_CTI_VERTICALX_ITTRIGIN(a) (a)
#define arguments_BDK_CTI_VERTICALX_ITTRIGIN(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_ittrigout
 *
 * CTI Vertical Ittrigout Register
 * Integration test to generate trigger events.
 */
union bdk_cti_verticalx_ittrigout
{
    uint32_t u;
    struct bdk_cti_verticalx_ittrigout_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ctitrigout            : 32; /**< [ 31:  0](R/W) Set/clear trigger output signal. Reads return the value in the register. Writes: */
#else /* Word 0 - Little Endian */
        uint32_t ctitrigout            : 32; /**< [ 31:  0](R/W) Set/clear trigger output signal. Reads return the value in the register. Writes: */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_ittrigout_s cn; */
};
typedef union bdk_cti_verticalx_ittrigout bdk_cti_verticalx_ittrigout_t;

static inline uint64_t BDK_CTI_VERTICALX_ITTRIGOUT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_ITTRIGOUT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102ee8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_ITTRIGOUT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_ITTRIGOUT(a) bdk_cti_verticalx_ittrigout_t
#define bustype_BDK_CTI_VERTICALX_ITTRIGOUT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_ITTRIGOUT(a) "CTI_VERTICALX_ITTRIGOUT"
#define busnum_BDK_CTI_VERTICALX_ITTRIGOUT(a) (a)
#define arguments_BDK_CTI_VERTICALX_ITTRIGOUT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_pidr0
 *
 * CTI Vertical Pidr0 Register
 * The PIDR0 register is part of the set of peripheral identification registers.
 */
union bdk_cti_verticalx_pidr0
{
    uint32_t u;
    struct bdk_cti_verticalx_pidr0_s
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
    /* struct bdk_cti_verticalx_pidr0_s cn; */
};
typedef union bdk_cti_verticalx_pidr0 bdk_cti_verticalx_pidr0_t;

static inline uint64_t BDK_CTI_VERTICALX_PIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_PIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fe0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_PIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_PIDR0(a) bdk_cti_verticalx_pidr0_t
#define bustype_BDK_CTI_VERTICALX_PIDR0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_PIDR0(a) "CTI_VERTICALX_PIDR0"
#define busnum_BDK_CTI_VERTICALX_PIDR0(a) (a)
#define arguments_BDK_CTI_VERTICALX_PIDR0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_pidr1
 *
 * CTI Vertical Pidr1 Register
 * The PIDR1 register is part of the set of peripheral identification registers.
 */
union bdk_cti_verticalx_pidr1
{
    uint32_t u;
    struct bdk_cti_verticalx_pidr1_s
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
    /* struct bdk_cti_verticalx_pidr1_s cn; */
};
typedef union bdk_cti_verticalx_pidr1 bdk_cti_verticalx_pidr1_t;

static inline uint64_t BDK_CTI_VERTICALX_PIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_PIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fe4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_PIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_PIDR1(a) bdk_cti_verticalx_pidr1_t
#define bustype_BDK_CTI_VERTICALX_PIDR1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_PIDR1(a) "CTI_VERTICALX_PIDR1"
#define busnum_BDK_CTI_VERTICALX_PIDR1(a) (a)
#define arguments_BDK_CTI_VERTICALX_PIDR1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_pidr2
 *
 * CTI Vertical Pidr2 Register
 * The PIDR2 register is part of the set of peripheral identification registers.
 */
union bdk_cti_verticalx_pidr2
{
    uint32_t u;
    struct bdk_cti_verticalx_pidr2_s
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
    /* struct bdk_cti_verticalx_pidr2_s cn; */
};
typedef union bdk_cti_verticalx_pidr2 bdk_cti_verticalx_pidr2_t;

static inline uint64_t BDK_CTI_VERTICALX_PIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_PIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fe8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_PIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_PIDR2(a) bdk_cti_verticalx_pidr2_t
#define bustype_BDK_CTI_VERTICALX_PIDR2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_PIDR2(a) "CTI_VERTICALX_PIDR2"
#define busnum_BDK_CTI_VERTICALX_PIDR2(a) (a)
#define arguments_BDK_CTI_VERTICALX_PIDR2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_pidr3
 *
 * CTI Vertical Pidr3 Register
 * The PIDR3 register is part of the set of peripheral identification registers.
 */
union bdk_cti_verticalx_pidr3
{
    uint32_t u;
    struct bdk_cti_verticalx_pidr3_s
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
    /* struct bdk_cti_verticalx_pidr3_s cn; */
};
typedef union bdk_cti_verticalx_pidr3 bdk_cti_verticalx_pidr3_t;

static inline uint64_t BDK_CTI_VERTICALX_PIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_PIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fecll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_PIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_PIDR3(a) bdk_cti_verticalx_pidr3_t
#define bustype_BDK_CTI_VERTICALX_PIDR3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_PIDR3(a) "CTI_VERTICALX_PIDR3"
#define busnum_BDK_CTI_VERTICALX_PIDR3(a) (a)
#define arguments_BDK_CTI_VERTICALX_PIDR3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_pidr4
 *
 * CTI Vertical Pidr4 Register
 * The PIDR4 register is part of the set of peripheral identification registers.
 */
union bdk_cti_verticalx_pidr4
{
    uint32_t u;
    struct bdk_cti_verticalx_pidr4_s
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
    /* struct bdk_cti_verticalx_pidr4_s cn; */
};
typedef union bdk_cti_verticalx_pidr4 bdk_cti_verticalx_pidr4_t;

static inline uint64_t BDK_CTI_VERTICALX_PIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_PIDR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fd0ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_PIDR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_PIDR4(a) bdk_cti_verticalx_pidr4_t
#define bustype_BDK_CTI_VERTICALX_PIDR4(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_PIDR4(a) "CTI_VERTICALX_PIDR4"
#define busnum_BDK_CTI_VERTICALX_PIDR4(a) (a)
#define arguments_BDK_CTI_VERTICALX_PIDR4(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_pidr5
 *
 * CTI Vertical Pidr5 Register
 * The PIDR5 register is part of the set of peripheral identification registers.
 */
union bdk_cti_verticalx_pidr5
{
    uint32_t u;
    struct bdk_cti_verticalx_pidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr5                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr5                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_pidr5_s cn; */
};
typedef union bdk_cti_verticalx_pidr5 bdk_cti_verticalx_pidr5_t;

static inline uint64_t BDK_CTI_VERTICALX_PIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_PIDR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fd4ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_PIDR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_PIDR5(a) bdk_cti_verticalx_pidr5_t
#define bustype_BDK_CTI_VERTICALX_PIDR5(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_PIDR5(a) "CTI_VERTICALX_PIDR5"
#define busnum_BDK_CTI_VERTICALX_PIDR5(a) (a)
#define arguments_BDK_CTI_VERTICALX_PIDR5(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_pidr6
 *
 * CTI Vertical Pidr6 Register
 * The PIDR6 register is part of the set of peripheral identification registers.
 */
union bdk_cti_verticalx_pidr6
{
    uint32_t u;
    struct bdk_cti_verticalx_pidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr6                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr6                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_pidr6_s cn; */
};
typedef union bdk_cti_verticalx_pidr6 bdk_cti_verticalx_pidr6_t;

static inline uint64_t BDK_CTI_VERTICALX_PIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_PIDR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fd8ll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_PIDR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_PIDR6(a) bdk_cti_verticalx_pidr6_t
#define bustype_BDK_CTI_VERTICALX_PIDR6(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_PIDR6(a) "CTI_VERTICALX_PIDR6"
#define busnum_BDK_CTI_VERTICALX_PIDR6(a) (a)
#define arguments_BDK_CTI_VERTICALX_PIDR6(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_vertical#_pidr7
 *
 * CTI Vertical Pidr7 Register
 * The PIDR7 register is part of the set of peripheral identification registers.
 */
union bdk_cti_verticalx_pidr7
{
    uint32_t u;
    struct bdk_cti_verticalx_pidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr7                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr7                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_verticalx_pidr7_s cn; */
};
typedef union bdk_cti_verticalx_pidr7 bdk_cti_verticalx_pidr7_t;

static inline uint64_t BDK_CTI_VERTICALX_PIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_VERTICALX_PIDR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=3))
        return 0x87e046102fdcll + 0x100000ll * ((a) & 0x3);
    __bdk_csr_fatal("CTI_VERTICALX_PIDR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_VERTICALX_PIDR7(a) bdk_cti_verticalx_pidr7_t
#define bustype_BDK_CTI_VERTICALX_PIDR7(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_VERTICALX_PIDR7(a) "CTI_VERTICALX_PIDR7"
#define busnum_BDK_CTI_VERTICALX_PIDR7(a) (a)
#define arguments_BDK_CTI_VERTICALX_PIDR7(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_CTI_VERTICAL_H__ */
