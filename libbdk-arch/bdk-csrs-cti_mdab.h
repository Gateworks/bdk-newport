#ifndef __BDK_CSRS_CTI_MDAB_H__
#define __BDK_CSRS_CTI_MDAB_H__
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
 * OcteonTX CTI_MDAB.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Register (RSL32b) cti_mdab#_asicctrl
 *
 * CTI Mdab Asicctrl Register
 * I/O port control.
 */
union bdk_cti_mdabx_asicctrl
{
    uint32_t u;
    struct bdk_cti_mdabx_asicctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 24; /**< [ 31:  8](R/W) Software should write the field as all 0s. */
        uint32_t asicctrl              : 8;  /**< [  7:  0](R/W) Set and clear external output signal. */
#else /* Word 0 - Little Endian */
        uint32_t asicctrl              : 8;  /**< [  7:  0](R/W) Set and clear external output signal. */
        uint32_t sbz_0                 : 24; /**< [ 31:  8](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_asicctrl_s cn; */
};
typedef union bdk_cti_mdabx_asicctrl bdk_cti_mdabx_asicctrl_t;

static inline uint64_t BDK_CTI_MDABX_ASICCTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_ASICCTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112144 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_ASICCTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_ASICCTRL(a) bdk_cti_mdabx_asicctrl_t
#define bustype_BDK_CTI_MDABX_ASICCTRL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_ASICCTRL(a) "CTI_MDABX_ASICCTRL"
#define busnum_BDK_CTI_MDABX_ASICCTRL(a) (a)
#define arguments_BDK_CTI_MDABX_ASICCTRL(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_authstatus
 *
 * CTI Mdab Authstatus Register
 * Reports the current status of the authentication control signals.
 */
union bdk_cti_mdabx_authstatus
{
    uint32_t u;
    struct bdk_cti_mdabx_authstatus_s
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
    /* struct bdk_cti_mdabx_authstatus_s cn; */
};
typedef union bdk_cti_mdabx_authstatus bdk_cti_mdabx_authstatus_t;

static inline uint64_t BDK_CTI_MDABX_AUTHSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_AUTHSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fb8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_AUTHSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_AUTHSTATUS(a) bdk_cti_mdabx_authstatus_t
#define bustype_BDK_CTI_MDABX_AUTHSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_AUTHSTATUS(a) "CTI_MDABX_AUTHSTATUS"
#define busnum_BDK_CTI_MDABX_AUTHSTATUS(a) (a)
#define arguments_BDK_CTI_MDABX_AUTHSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_cidr0
 *
 * CTI Mdab Cidr0 Register
 * The CIDR0 register is part of the set of component identification registers.
 */
union bdk_cti_mdabx_cidr0
{
    uint32_t u;
    struct bdk_cti_mdabx_cidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x0D. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x0D. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_cidr0_s cn; */
};
typedef union bdk_cti_mdabx_cidr0 bdk_cti_mdabx_cidr0_t;

static inline uint64_t BDK_CTI_MDABX_CIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112ff0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CIDR0(a) bdk_cti_mdabx_cidr0_t
#define bustype_BDK_CTI_MDABX_CIDR0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CIDR0(a) "CTI_MDABX_CIDR0"
#define busnum_BDK_CTI_MDABX_CIDR0(a) (a)
#define arguments_BDK_CTI_MDABX_CIDR0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_cidr1
 *
 * CTI Mdab Cidr1 Register
 * The CIDR1 register is part of the set of component identification registers.
 */
union bdk_cti_mdabx_cidr1
{
    uint32_t u;
    struct bdk_cti_mdabx_cidr1_s
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
    /* struct bdk_cti_mdabx_cidr1_s cn; */
};
typedef union bdk_cti_mdabx_cidr1 bdk_cti_mdabx_cidr1_t;

static inline uint64_t BDK_CTI_MDABX_CIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112ff4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CIDR1(a) bdk_cti_mdabx_cidr1_t
#define bustype_BDK_CTI_MDABX_CIDR1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CIDR1(a) "CTI_MDABX_CIDR1"
#define busnum_BDK_CTI_MDABX_CIDR1(a) (a)
#define arguments_BDK_CTI_MDABX_CIDR1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_cidr2
 *
 * CTI Mdab Cidr2 Register
 * The CIDR2 register is part of the set of component identification registers.
 */
union bdk_cti_mdabx_cidr2
{
    uint32_t u;
    struct bdk_cti_mdabx_cidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x05. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x05. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_cidr2_s cn; */
};
typedef union bdk_cti_mdabx_cidr2 bdk_cti_mdabx_cidr2_t;

static inline uint64_t BDK_CTI_MDABX_CIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112ff8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CIDR2(a) bdk_cti_mdabx_cidr2_t
#define bustype_BDK_CTI_MDABX_CIDR2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CIDR2(a) "CTI_MDABX_CIDR2"
#define busnum_BDK_CTI_MDABX_CIDR2(a) (a)
#define arguments_BDK_CTI_MDABX_CIDR2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_cidr3
 *
 * CTI Mdab Cidr3 Register
 * The CIDR3 register is part of the set of component identification registers.
 */
union bdk_cti_mdabx_cidr3
{
    uint32_t u;
    struct bdk_cti_mdabx_cidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Returns 0xB1. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Returns 0xB1. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_cidr3_s cn; */
};
typedef union bdk_cti_mdabx_cidr3 bdk_cti_mdabx_cidr3_t;

static inline uint64_t BDK_CTI_MDABX_CIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112ffc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CIDR3(a) bdk_cti_mdabx_cidr3_t
#define bustype_BDK_CTI_MDABX_CIDR3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CIDR3(a) "CTI_MDABX_CIDR3"
#define busnum_BDK_CTI_MDABX_CIDR3(a) (a)
#define arguments_BDK_CTI_MDABX_CIDR3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_claimclr
 *
 * CTI Mdab Claimclr Register
 * This register forms one half of the claim tag value. On writes, this location
 * enables individual bits to be cleared. On reads, it returns the current claim tag
 * value.
 */
union bdk_cti_mdabx_claimclr
{
    uint32_t u;
    struct bdk_cti_mdabx_claimclr_s
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
    /* struct bdk_cti_mdabx_claimclr_s cn; */
};
typedef union bdk_cti_mdabx_claimclr bdk_cti_mdabx_claimclr_t;

static inline uint64_t BDK_CTI_MDABX_CLAIMCLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CLAIMCLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fa4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CLAIMCLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CLAIMCLR(a) bdk_cti_mdabx_claimclr_t
#define bustype_BDK_CTI_MDABX_CLAIMCLR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CLAIMCLR(a) "CTI_MDABX_CLAIMCLR"
#define busnum_BDK_CTI_MDABX_CLAIMCLR(a) (a)
#define arguments_BDK_CTI_MDABX_CLAIMCLR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_claimset
 *
 * CTI Mdab Claimset Register
 * This register forms one half of the claim tag value. On writes, this location
 * enables individual bits to be set. On reads, it returns the number of bits that can
 * be set.
 */
union bdk_cti_mdabx_claimset
{
    uint32_t u;
    struct bdk_cti_mdabx_claimset_s
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
    /* struct bdk_cti_mdabx_claimset_s cn; */
};
typedef union bdk_cti_mdabx_claimset bdk_cti_mdabx_claimset_t;

static inline uint64_t BDK_CTI_MDABX_CLAIMSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CLAIMSET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fa0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CLAIMSET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CLAIMSET(a) bdk_cti_mdabx_claimset_t
#define bustype_BDK_CTI_MDABX_CLAIMSET(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CLAIMSET(a) "CTI_MDABX_CLAIMSET"
#define busnum_BDK_CTI_MDABX_CLAIMSET(a) (a)
#define arguments_BDK_CTI_MDABX_CLAIMSET(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiappclear
 *
 * CTI Mdab Ctiappclear Register
 * The application channel clear register allows software to clear any channel output.
 * This register can be used by software to clear a channel event in place of a
 * hardware source on a trigger input. In a system where all events are sent as single
 * cycle pulses, this register must not be used. It is only retained for compatibility
 * with older systems and software. The register is implemented before the CTIGATE
 * register so, for the channel event to propagate outside the CTI, it is necessary for
 * the corresponding CTIGATE bit to be 1.
 */
union bdk_cti_mdabx_ctiappclear
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiappclear_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
        uint32_t appclear              : 4;  /**< [  3:  0](WO) Clears the corresponding internal channel flag. */
#else /* Word 0 - Little Endian */
        uint32_t appclear              : 4;  /**< [  3:  0](WO) Clears the corresponding internal channel flag. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiappclear_s cn; */
};
typedef union bdk_cti_mdabx_ctiappclear bdk_cti_mdabx_ctiappclear_t;

static inline uint64_t BDK_CTI_MDABX_CTIAPPCLEAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIAPPCLEAR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112018 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIAPPCLEAR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIAPPCLEAR(a) bdk_cti_mdabx_ctiappclear_t
#define bustype_BDK_CTI_MDABX_CTIAPPCLEAR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIAPPCLEAR(a) "CTI_MDABX_CTIAPPCLEAR"
#define busnum_BDK_CTI_MDABX_CTIAPPCLEAR(a) (a)
#define arguments_BDK_CTI_MDABX_CTIAPPCLEAR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiapppulse
 *
 * CTI Mdab Ctiapppulse Register
 * The application channel pulse register allows software to pulse any channel output.
 * This register can be used by software to pulse a channel event in place of a
 * hardware source on a trigger input. The register is implemented before the CTIGATE
 * register so, for the channel event to propagate outside the CTI, it is necessary for
 * the corresponding CTIGATE bit to be 1.
 */
union bdk_cti_mdabx_ctiapppulse
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiapppulse_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
        uint32_t apppulse              : 4;  /**< [  3:  0](WO) Pulses the channel outputs. */
#else /* Word 0 - Little Endian */
        uint32_t apppulse              : 4;  /**< [  3:  0](WO) Pulses the channel outputs. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](WO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiapppulse_s cn; */
};
typedef union bdk_cti_mdabx_ctiapppulse bdk_cti_mdabx_ctiapppulse_t;

static inline uint64_t BDK_CTI_MDABX_CTIAPPPULSE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIAPPPULSE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611201c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIAPPPULSE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIAPPPULSE(a) bdk_cti_mdabx_ctiapppulse_t
#define bustype_BDK_CTI_MDABX_CTIAPPPULSE(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIAPPPULSE(a) "CTI_MDABX_CTIAPPPULSE"
#define busnum_BDK_CTI_MDABX_CTIAPPPULSE(a) (a)
#define arguments_BDK_CTI_MDABX_CTIAPPPULSE(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiappset
 *
 * CTI Mdab Ctiappset Register
 * The application channel set register allows software to set any channel output. This
 * register can be used by software to generate a channel event in place of a hardware
 * source on a trigger input. In a system where all events are sent as single cycle
 * pulses, this register must not be used. It is only retained for compatibility with
 * older systems and software. The register is implemented before the CTIGATE register
 * so, for the channel event to propagate outside the CTI, it is necessary for the
 * corresponding CTIGATE bit to be 1.
 */
union bdk_cti_mdabx_ctiappset
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiappset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t appset                : 4;  /**< [  3:  0](R/W) Sets the corresponding internal channel flag. */
#else /* Word 0 - Little Endian */
        uint32_t appset                : 4;  /**< [  3:  0](R/W) Sets the corresponding internal channel flag. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiappset_s cn; */
};
typedef union bdk_cti_mdabx_ctiappset bdk_cti_mdabx_ctiappset_t;

static inline uint64_t BDK_CTI_MDABX_CTIAPPSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIAPPSET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112014 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIAPPSET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIAPPSET(a) bdk_cti_mdabx_ctiappset_t
#define bustype_BDK_CTI_MDABX_CTIAPPSET(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIAPPSET(a) "CTI_MDABX_CTIAPPSET"
#define busnum_BDK_CTI_MDABX_CTIAPPSET(a) (a)
#define arguments_BDK_CTI_MDABX_CTIAPPSET(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctichinstatus
 *
 * CTI Mdab Ctichinstatus Register
 * Channel input status. If the channel input is driven by a source that generates
 * single cycle pulses, this register is generally read as 0.
 */
union bdk_cti_mdabx_ctichinstatus
{
    uint32_t u;
    struct bdk_cti_mdabx_ctichinstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
        uint32_t ctichinstatus         : 4;  /**< [  3:  0](RO) Channel input status. */
#else /* Word 0 - Little Endian */
        uint32_t ctichinstatus         : 4;  /**< [  3:  0](RO) Channel input status. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctichinstatus_s cn; */
};
typedef union bdk_cti_mdabx_ctichinstatus bdk_cti_mdabx_ctichinstatus_t;

static inline uint64_t BDK_CTI_MDABX_CTICHINSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTICHINSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112138 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTICHINSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTICHINSTATUS(a) bdk_cti_mdabx_ctichinstatus_t
#define bustype_BDK_CTI_MDABX_CTICHINSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTICHINSTATUS(a) "CTI_MDABX_CTICHINSTATUS"
#define busnum_BDK_CTI_MDABX_CTICHINSTATUS(a) (a)
#define arguments_BDK_CTI_MDABX_CTICHINSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctichoutstatus
 *
 * CTI Mdab Ctichoutstatus Register
 * Channel output status. The register only has meaning if the trigger source drives
 * static levels, rather than pulses.
 */
union bdk_cti_mdabx_ctichoutstatus
{
    uint32_t u;
    struct bdk_cti_mdabx_ctichoutstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
        uint32_t ctichoutstatus        : 4;  /**< [  3:  0](RO) Channel output status. */
#else /* Word 0 - Little Endian */
        uint32_t ctichoutstatus        : 4;  /**< [  3:  0](RO) Channel output status. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctichoutstatus_s cn; */
};
typedef union bdk_cti_mdabx_ctichoutstatus bdk_cti_mdabx_ctichoutstatus_t;

static inline uint64_t BDK_CTI_MDABX_CTICHOUTSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTICHOUTSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611213c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTICHOUTSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTICHOUTSTATUS(a) bdk_cti_mdabx_ctichoutstatus_t
#define bustype_BDK_CTI_MDABX_CTICHOUTSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTICHOUTSTATUS(a) "CTI_MDABX_CTICHOUTSTATUS"
#define busnum_BDK_CTI_MDABX_CTICHOUTSTATUS(a) (a)
#define arguments_BDK_CTI_MDABX_CTICHOUTSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_cticontrol
 *
 * CTI Mdab Cticontrol Register
 * The CTI control register enables and disables the CTI.
 */
union bdk_cti_mdabx_cticontrol
{
    uint32_t u;
    struct bdk_cti_mdabx_cticontrol_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 31; /**< [ 31:  1](R/W) Software should write the field as all 0s. */
        uint32_t ctien                 : 1;  /**< [  0:  0](R/W) Enable control. */
#else /* Word 0 - Little Endian */
        uint32_t ctien                 : 1;  /**< [  0:  0](R/W) Enable control. */
        uint32_t sbz_0                 : 31; /**< [ 31:  1](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_cticontrol_s cn; */
};
typedef union bdk_cti_mdabx_cticontrol bdk_cti_mdabx_cticontrol_t;

static inline uint64_t BDK_CTI_MDABX_CTICONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTICONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112000 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTICONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTICONTROL(a) bdk_cti_mdabx_cticontrol_t
#define bustype_BDK_CTI_MDABX_CTICONTROL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTICONTROL(a) "CTI_MDABX_CTICONTROL"
#define busnum_BDK_CTI_MDABX_CTICONTROL(a) (a)
#define arguments_BDK_CTI_MDABX_CTICONTROL(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctigate
 *
 * CTI Mdab Ctigate Register
 * Channel output gate.
 */
union bdk_cti_mdabx_ctigate
{
    uint32_t u;
    struct bdk_cti_mdabx_ctigate_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t ctigateen             : 4;  /**< [  3:  0](R/W) Enables the propagation of channel events out of the CTI, one bit per channel. */
#else /* Word 0 - Little Endian */
        uint32_t ctigateen             : 4;  /**< [  3:  0](R/W) Enables the propagation of channel events out of the CTI, one bit per channel. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctigate_s cn; */
};
typedef union bdk_cti_mdabx_ctigate bdk_cti_mdabx_ctigate_t;

static inline uint64_t BDK_CTI_MDABX_CTIGATE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIGATE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112140 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIGATE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIGATE(a) bdk_cti_mdabx_ctigate_t
#define bustype_BDK_CTI_MDABX_CTIGATE(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIGATE(a) "CTI_MDABX_CTIGATE"
#define busnum_BDK_CTI_MDABX_CTIGATE(a) (a)
#define arguments_BDK_CTI_MDABX_CTIGATE(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen0
 *
 * CTI Mdab Ctiinen0 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen0
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen0_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen0 bdk_cti_mdabx_ctiinen0_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112020 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN0(a) bdk_cti_mdabx_ctiinen0_t
#define bustype_BDK_CTI_MDABX_CTIINEN0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN0(a) "CTI_MDABX_CTIINEN0"
#define busnum_BDK_CTI_MDABX_CTIINEN0(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen1
 *
 * CTI Mdab Ctiinen1 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen1
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen1_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen1 bdk_cti_mdabx_ctiinen1_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112024 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN1(a) bdk_cti_mdabx_ctiinen1_t
#define bustype_BDK_CTI_MDABX_CTIINEN1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN1(a) "CTI_MDABX_CTIINEN1"
#define busnum_BDK_CTI_MDABX_CTIINEN1(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen10
 *
 * CTI Mdab Ctiinen10 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen10
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen10_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen10 bdk_cti_mdabx_ctiinen10_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN10(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN10(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112048 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN10", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN10(a) bdk_cti_mdabx_ctiinen10_t
#define bustype_BDK_CTI_MDABX_CTIINEN10(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN10(a) "CTI_MDABX_CTIINEN10"
#define busnum_BDK_CTI_MDABX_CTIINEN10(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN10(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen11
 *
 * CTI Mdab Ctiinen11 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen11
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen11_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen11 bdk_cti_mdabx_ctiinen11_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN11(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN11(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611204c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN11", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN11(a) bdk_cti_mdabx_ctiinen11_t
#define bustype_BDK_CTI_MDABX_CTIINEN11(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN11(a) "CTI_MDABX_CTIINEN11"
#define busnum_BDK_CTI_MDABX_CTIINEN11(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN11(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen12
 *
 * CTI Mdab Ctiinen12 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen12
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen12_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen12 bdk_cti_mdabx_ctiinen12_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN12(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN12(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112050 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN12", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN12(a) bdk_cti_mdabx_ctiinen12_t
#define bustype_BDK_CTI_MDABX_CTIINEN12(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN12(a) "CTI_MDABX_CTIINEN12"
#define busnum_BDK_CTI_MDABX_CTIINEN12(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN12(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen13
 *
 * CTI Mdab Ctiinen13 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen13
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen13_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen13_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen13 bdk_cti_mdabx_ctiinen13_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN13(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN13(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112054 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN13", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN13(a) bdk_cti_mdabx_ctiinen13_t
#define bustype_BDK_CTI_MDABX_CTIINEN13(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN13(a) "CTI_MDABX_CTIINEN13"
#define busnum_BDK_CTI_MDABX_CTIINEN13(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN13(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen14
 *
 * CTI Mdab Ctiinen14 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen14
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen14_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen14_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen14 bdk_cti_mdabx_ctiinen14_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN14(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN14(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112058 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN14", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN14(a) bdk_cti_mdabx_ctiinen14_t
#define bustype_BDK_CTI_MDABX_CTIINEN14(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN14(a) "CTI_MDABX_CTIINEN14"
#define busnum_BDK_CTI_MDABX_CTIINEN14(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN14(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen15
 *
 * CTI Mdab Ctiinen15 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen15
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen15_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen15_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen15 bdk_cti_mdabx_ctiinen15_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN15(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN15(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611205c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN15", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN15(a) bdk_cti_mdabx_ctiinen15_t
#define bustype_BDK_CTI_MDABX_CTIINEN15(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN15(a) "CTI_MDABX_CTIINEN15"
#define busnum_BDK_CTI_MDABX_CTIINEN15(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN15(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen16
 *
 * CTI Mdab Ctiinen16 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen16
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen16_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen16_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen16 bdk_cti_mdabx_ctiinen16_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN16(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN16(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112060 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN16", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN16(a) bdk_cti_mdabx_ctiinen16_t
#define bustype_BDK_CTI_MDABX_CTIINEN16(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN16(a) "CTI_MDABX_CTIINEN16"
#define busnum_BDK_CTI_MDABX_CTIINEN16(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN16(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen17
 *
 * CTI Mdab Ctiinen17 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen17
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen17_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen17_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen17 bdk_cti_mdabx_ctiinen17_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN17(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN17(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112064 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN17", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN17(a) bdk_cti_mdabx_ctiinen17_t
#define bustype_BDK_CTI_MDABX_CTIINEN17(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN17(a) "CTI_MDABX_CTIINEN17"
#define busnum_BDK_CTI_MDABX_CTIINEN17(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN17(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen18
 *
 * CTI Mdab Ctiinen18 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen18
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen18_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen18_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen18 bdk_cti_mdabx_ctiinen18_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN18(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN18(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112068 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN18", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN18(a) bdk_cti_mdabx_ctiinen18_t
#define bustype_BDK_CTI_MDABX_CTIINEN18(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN18(a) "CTI_MDABX_CTIINEN18"
#define busnum_BDK_CTI_MDABX_CTIINEN18(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN18(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen19
 *
 * CTI Mdab Ctiinen19 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen19
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen19_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen19_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen19 bdk_cti_mdabx_ctiinen19_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN19(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN19(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611206c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN19", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN19(a) bdk_cti_mdabx_ctiinen19_t
#define bustype_BDK_CTI_MDABX_CTIINEN19(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN19(a) "CTI_MDABX_CTIINEN19"
#define busnum_BDK_CTI_MDABX_CTIINEN19(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN19(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen2
 *
 * CTI Mdab Ctiinen2 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen2
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen2_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen2 bdk_cti_mdabx_ctiinen2_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112028 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN2(a) bdk_cti_mdabx_ctiinen2_t
#define bustype_BDK_CTI_MDABX_CTIINEN2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN2(a) "CTI_MDABX_CTIINEN2"
#define busnum_BDK_CTI_MDABX_CTIINEN2(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen20
 *
 * CTI Mdab Ctiinen20 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen20
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen20_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen20_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen20 bdk_cti_mdabx_ctiinen20_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN20(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN20(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112070 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN20", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN20(a) bdk_cti_mdabx_ctiinen20_t
#define bustype_BDK_CTI_MDABX_CTIINEN20(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN20(a) "CTI_MDABX_CTIINEN20"
#define busnum_BDK_CTI_MDABX_CTIINEN20(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN20(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen21
 *
 * CTI Mdab Ctiinen21 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen21
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen21_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen21_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen21 bdk_cti_mdabx_ctiinen21_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN21(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN21(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112074 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN21", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN21(a) bdk_cti_mdabx_ctiinen21_t
#define bustype_BDK_CTI_MDABX_CTIINEN21(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN21(a) "CTI_MDABX_CTIINEN21"
#define busnum_BDK_CTI_MDABX_CTIINEN21(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN21(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen22
 *
 * CTI Mdab Ctiinen22 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen22
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen22_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen22_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen22 bdk_cti_mdabx_ctiinen22_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN22(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN22(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112078 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN22", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN22(a) bdk_cti_mdabx_ctiinen22_t
#define bustype_BDK_CTI_MDABX_CTIINEN22(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN22(a) "CTI_MDABX_CTIINEN22"
#define busnum_BDK_CTI_MDABX_CTIINEN22(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN22(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen23
 *
 * CTI Mdab Ctiinen23 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen23
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen23_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen23_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen23 bdk_cti_mdabx_ctiinen23_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN23(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN23(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611207c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN23", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN23(a) bdk_cti_mdabx_ctiinen23_t
#define bustype_BDK_CTI_MDABX_CTIINEN23(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN23(a) "CTI_MDABX_CTIINEN23"
#define busnum_BDK_CTI_MDABX_CTIINEN23(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN23(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen24
 *
 * CTI Mdab Ctiinen24 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen24
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen24_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen24_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen24 bdk_cti_mdabx_ctiinen24_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN24(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN24(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112080 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN24", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN24(a) bdk_cti_mdabx_ctiinen24_t
#define bustype_BDK_CTI_MDABX_CTIINEN24(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN24(a) "CTI_MDABX_CTIINEN24"
#define busnum_BDK_CTI_MDABX_CTIINEN24(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN24(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen25
 *
 * CTI Mdab Ctiinen25 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen25
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen25_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen25_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen25 bdk_cti_mdabx_ctiinen25_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN25(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN25(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112084 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN25", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN25(a) bdk_cti_mdabx_ctiinen25_t
#define bustype_BDK_CTI_MDABX_CTIINEN25(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN25(a) "CTI_MDABX_CTIINEN25"
#define busnum_BDK_CTI_MDABX_CTIINEN25(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN25(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen26
 *
 * CTI Mdab Ctiinen26 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen26
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen26_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen26_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen26 bdk_cti_mdabx_ctiinen26_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN26(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN26(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112088 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN26", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN26(a) bdk_cti_mdabx_ctiinen26_t
#define bustype_BDK_CTI_MDABX_CTIINEN26(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN26(a) "CTI_MDABX_CTIINEN26"
#define busnum_BDK_CTI_MDABX_CTIINEN26(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN26(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen27
 *
 * CTI Mdab Ctiinen27 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen27
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen27_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen27_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen27 bdk_cti_mdabx_ctiinen27_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN27(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN27(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611208c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN27", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN27(a) bdk_cti_mdabx_ctiinen27_t
#define bustype_BDK_CTI_MDABX_CTIINEN27(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN27(a) "CTI_MDABX_CTIINEN27"
#define busnum_BDK_CTI_MDABX_CTIINEN27(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN27(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen28
 *
 * CTI Mdab Ctiinen28 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen28
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen28_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen28_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen28 bdk_cti_mdabx_ctiinen28_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN28(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN28(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112090 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN28", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN28(a) bdk_cti_mdabx_ctiinen28_t
#define bustype_BDK_CTI_MDABX_CTIINEN28(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN28(a) "CTI_MDABX_CTIINEN28"
#define busnum_BDK_CTI_MDABX_CTIINEN28(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN28(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen29
 *
 * CTI Mdab Ctiinen29 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen29
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen29_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen29_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen29 bdk_cti_mdabx_ctiinen29_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN29(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN29(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112094 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN29", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN29(a) bdk_cti_mdabx_ctiinen29_t
#define bustype_BDK_CTI_MDABX_CTIINEN29(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN29(a) "CTI_MDABX_CTIINEN29"
#define busnum_BDK_CTI_MDABX_CTIINEN29(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN29(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen3
 *
 * CTI Mdab Ctiinen3 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen3
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen3_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen3 bdk_cti_mdabx_ctiinen3_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611202c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN3(a) bdk_cti_mdabx_ctiinen3_t
#define bustype_BDK_CTI_MDABX_CTIINEN3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN3(a) "CTI_MDABX_CTIINEN3"
#define busnum_BDK_CTI_MDABX_CTIINEN3(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen30
 *
 * CTI Mdab Ctiinen30 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen30
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen30_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen30_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen30 bdk_cti_mdabx_ctiinen30_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN30(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN30(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112098 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN30", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN30(a) bdk_cti_mdabx_ctiinen30_t
#define bustype_BDK_CTI_MDABX_CTIINEN30(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN30(a) "CTI_MDABX_CTIINEN30"
#define busnum_BDK_CTI_MDABX_CTIINEN30(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN30(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen31
 *
 * CTI Mdab Ctiinen31 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen31
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen31_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen31_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen31 bdk_cti_mdabx_ctiinen31_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN31(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN31(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611209c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN31", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN31(a) bdk_cti_mdabx_ctiinen31_t
#define bustype_BDK_CTI_MDABX_CTIINEN31(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN31(a) "CTI_MDABX_CTIINEN31"
#define busnum_BDK_CTI_MDABX_CTIINEN31(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN31(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen4
 *
 * CTI Mdab Ctiinen4 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen4
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen4_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen4 bdk_cti_mdabx_ctiinen4_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112030 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN4(a) bdk_cti_mdabx_ctiinen4_t
#define bustype_BDK_CTI_MDABX_CTIINEN4(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN4(a) "CTI_MDABX_CTIINEN4"
#define busnum_BDK_CTI_MDABX_CTIINEN4(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN4(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen5
 *
 * CTI Mdab Ctiinen5 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen5
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen5_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen5 bdk_cti_mdabx_ctiinen5_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112034 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN5(a) bdk_cti_mdabx_ctiinen5_t
#define bustype_BDK_CTI_MDABX_CTIINEN5(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN5(a) "CTI_MDABX_CTIINEN5"
#define busnum_BDK_CTI_MDABX_CTIINEN5(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN5(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen6
 *
 * CTI Mdab Ctiinen6 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen6
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen6_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen6 bdk_cti_mdabx_ctiinen6_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112038 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN6(a) bdk_cti_mdabx_ctiinen6_t
#define bustype_BDK_CTI_MDABX_CTIINEN6(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN6(a) "CTI_MDABX_CTIINEN6"
#define busnum_BDK_CTI_MDABX_CTIINEN6(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN6(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen7
 *
 * CTI Mdab Ctiinen7 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen7
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen7_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen7 bdk_cti_mdabx_ctiinen7_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611203c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN7(a) bdk_cti_mdabx_ctiinen7_t
#define bustype_BDK_CTI_MDABX_CTIINEN7(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN7(a) "CTI_MDABX_CTIINEN7"
#define busnum_BDK_CTI_MDABX_CTIINEN7(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN7(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen8
 *
 * CTI Mdab Ctiinen8 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen8
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen8_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen8 bdk_cti_mdabx_ctiinen8_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN8(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN8(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112040 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN8", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN8(a) bdk_cti_mdabx_ctiinen8_t
#define bustype_BDK_CTI_MDABX_CTIINEN8(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN8(a) "CTI_MDABX_CTIINEN8"
#define busnum_BDK_CTI_MDABX_CTIINEN8(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN8(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiinen9
 *
 * CTI Mdab Ctiinen9 Register
 * This register maps trigger inputs to channels in the cross trigger system. The
 * CTIINEN registers are bit maps that allow the trigger input to be mapped to any
 * channel output, including none (0x0) and all (0xF). There is one register per
 * trigger input, so it is possible to map any combination of trigger inputs to any
 * channel outputs.
 */
union bdk_cti_mdabx_ctiinen9
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiinen9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
#else /* Word 0 - Little Endian */
        uint32_t triginen              : 4;  /**< [  3:  0](R/W) Trigger input to channel mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiinen9_s cn; */
};
typedef union bdk_cti_mdabx_ctiinen9 bdk_cti_mdabx_ctiinen9_t;

static inline uint64_t BDK_CTI_MDABX_CTIINEN9(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINEN9(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112044 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINEN9", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINEN9(a) bdk_cti_mdabx_ctiinen9_t
#define bustype_BDK_CTI_MDABX_CTIINEN9(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINEN9(a) "CTI_MDABX_CTIINEN9"
#define busnum_BDK_CTI_MDABX_CTIINEN9(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINEN9(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiintack
 *
 * CTI Mdab Ctiintack Register
 * Software acknowledge for trigger outputs. The CTIINTACK register is a bit map that
 * allows selective clearing of trigger output events. If the SW_HANDSHAKE parameter
 * for a trigger output is set, indicating that the output latches HIGH when an event
 * is sent to that output, then the output remains HIGH until the corresponding INTACK
 * bit is written to a 1. A write of a bit to 0 has no effect. This allows different
 * software threads to be responsible for clearing different trigger outputs without
 * needing to perform a read-modify-write operation to find which bits are set.
 */
union bdk_cti_mdabx_ctiintack
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiintack_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t intack                : 32; /**< [ 31:  0](WO) Acknowledges the corresponding event_out output. */
#else /* Word 0 - Little Endian */
        uint32_t intack                : 32; /**< [ 31:  0](WO) Acknowledges the corresponding event_out output. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiintack_s cn; */
};
typedef union bdk_cti_mdabx_ctiintack bdk_cti_mdabx_ctiintack_t;

static inline uint64_t BDK_CTI_MDABX_CTIINTACK(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIINTACK(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112010 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIINTACK", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIINTACK(a) bdk_cti_mdabx_ctiintack_t
#define bustype_BDK_CTI_MDABX_CTIINTACK(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIINTACK(a) "CTI_MDABX_CTIINTACK"
#define busnum_BDK_CTI_MDABX_CTIINTACK(a) (a)
#define arguments_BDK_CTI_MDABX_CTIINTACK(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten0
 *
 * CTI Mdab Ctiouten0 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten0
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten0_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten0 bdk_cti_mdabx_ctiouten0_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120a0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN0(a) bdk_cti_mdabx_ctiouten0_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN0(a) "CTI_MDABX_CTIOUTEN0"
#define busnum_BDK_CTI_MDABX_CTIOUTEN0(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten1
 *
 * CTI Mdab Ctiouten1 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten1
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten1_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten1 bdk_cti_mdabx_ctiouten1_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120a4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN1(a) bdk_cti_mdabx_ctiouten1_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN1(a) "CTI_MDABX_CTIOUTEN1"
#define busnum_BDK_CTI_MDABX_CTIOUTEN1(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten10
 *
 * CTI Mdab Ctiouten10 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten10
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten10_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten10_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten10 bdk_cti_mdabx_ctiouten10_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN10(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN10(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120c8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN10", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN10(a) bdk_cti_mdabx_ctiouten10_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN10(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN10(a) "CTI_MDABX_CTIOUTEN10"
#define busnum_BDK_CTI_MDABX_CTIOUTEN10(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN10(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten11
 *
 * CTI Mdab Ctiouten11 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten11
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten11_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten11_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten11 bdk_cti_mdabx_ctiouten11_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN11(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN11(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120cc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN11", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN11(a) bdk_cti_mdabx_ctiouten11_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN11(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN11(a) "CTI_MDABX_CTIOUTEN11"
#define busnum_BDK_CTI_MDABX_CTIOUTEN11(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN11(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten12
 *
 * CTI Mdab Ctiouten12 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten12
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten12_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten12_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten12 bdk_cti_mdabx_ctiouten12_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN12(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN12(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120d0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN12", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN12(a) bdk_cti_mdabx_ctiouten12_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN12(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN12(a) "CTI_MDABX_CTIOUTEN12"
#define busnum_BDK_CTI_MDABX_CTIOUTEN12(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN12(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten13
 *
 * CTI Mdab Ctiouten13 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten13
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten13_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten13_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten13 bdk_cti_mdabx_ctiouten13_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN13(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN13(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120d4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN13", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN13(a) bdk_cti_mdabx_ctiouten13_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN13(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN13(a) "CTI_MDABX_CTIOUTEN13"
#define busnum_BDK_CTI_MDABX_CTIOUTEN13(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN13(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten14
 *
 * CTI Mdab Ctiouten14 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten14
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten14_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten14_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten14 bdk_cti_mdabx_ctiouten14_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN14(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN14(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120d8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN14", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN14(a) bdk_cti_mdabx_ctiouten14_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN14(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN14(a) "CTI_MDABX_CTIOUTEN14"
#define busnum_BDK_CTI_MDABX_CTIOUTEN14(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN14(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten15
 *
 * CTI Mdab Ctiouten15 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten15
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten15_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten15_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten15 bdk_cti_mdabx_ctiouten15_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN15(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN15(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120dc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN15", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN15(a) bdk_cti_mdabx_ctiouten15_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN15(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN15(a) "CTI_MDABX_CTIOUTEN15"
#define busnum_BDK_CTI_MDABX_CTIOUTEN15(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN15(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten16
 *
 * CTI Mdab Ctiouten16 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten16
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten16_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten16_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten16 bdk_cti_mdabx_ctiouten16_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN16(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN16(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120e0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN16", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN16(a) bdk_cti_mdabx_ctiouten16_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN16(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN16(a) "CTI_MDABX_CTIOUTEN16"
#define busnum_BDK_CTI_MDABX_CTIOUTEN16(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN16(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten17
 *
 * CTI Mdab Ctiouten17 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten17
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten17_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten17_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten17 bdk_cti_mdabx_ctiouten17_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN17(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN17(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120e4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN17", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN17(a) bdk_cti_mdabx_ctiouten17_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN17(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN17(a) "CTI_MDABX_CTIOUTEN17"
#define busnum_BDK_CTI_MDABX_CTIOUTEN17(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN17(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten18
 *
 * CTI Mdab Ctiouten18 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten18
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten18_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten18_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten18 bdk_cti_mdabx_ctiouten18_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN18(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN18(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120e8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN18", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN18(a) bdk_cti_mdabx_ctiouten18_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN18(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN18(a) "CTI_MDABX_CTIOUTEN18"
#define busnum_BDK_CTI_MDABX_CTIOUTEN18(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN18(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten19
 *
 * CTI Mdab Ctiouten19 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten19
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten19_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten19_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten19 bdk_cti_mdabx_ctiouten19_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN19(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN19(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120ec + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN19", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN19(a) bdk_cti_mdabx_ctiouten19_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN19(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN19(a) "CTI_MDABX_CTIOUTEN19"
#define busnum_BDK_CTI_MDABX_CTIOUTEN19(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN19(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten2
 *
 * CTI Mdab Ctiouten2 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten2
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten2_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten2 bdk_cti_mdabx_ctiouten2_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120a8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN2(a) bdk_cti_mdabx_ctiouten2_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN2(a) "CTI_MDABX_CTIOUTEN2"
#define busnum_BDK_CTI_MDABX_CTIOUTEN2(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten20
 *
 * CTI Mdab Ctiouten20 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten20
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten20_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten20_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten20 bdk_cti_mdabx_ctiouten20_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN20(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN20(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120f0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN20", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN20(a) bdk_cti_mdabx_ctiouten20_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN20(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN20(a) "CTI_MDABX_CTIOUTEN20"
#define busnum_BDK_CTI_MDABX_CTIOUTEN20(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN20(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten21
 *
 * CTI Mdab Ctiouten21 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten21
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten21_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten21_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten21 bdk_cti_mdabx_ctiouten21_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN21(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN21(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120f4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN21", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN21(a) bdk_cti_mdabx_ctiouten21_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN21(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN21(a) "CTI_MDABX_CTIOUTEN21"
#define busnum_BDK_CTI_MDABX_CTIOUTEN21(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN21(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten22
 *
 * CTI Mdab Ctiouten22 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten22
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten22_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten22_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten22 bdk_cti_mdabx_ctiouten22_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN22(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN22(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120f8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN22", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN22(a) bdk_cti_mdabx_ctiouten22_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN22(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN22(a) "CTI_MDABX_CTIOUTEN22"
#define busnum_BDK_CTI_MDABX_CTIOUTEN22(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN22(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten23
 *
 * CTI Mdab Ctiouten23 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten23
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten23_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten23_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten23 bdk_cti_mdabx_ctiouten23_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN23(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN23(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120fc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN23", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN23(a) bdk_cti_mdabx_ctiouten23_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN23(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN23(a) "CTI_MDABX_CTIOUTEN23"
#define busnum_BDK_CTI_MDABX_CTIOUTEN23(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN23(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten24
 *
 * CTI Mdab Ctiouten24 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten24
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten24_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten24_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten24 bdk_cti_mdabx_ctiouten24_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN24(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN24(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112100 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN24", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN24(a) bdk_cti_mdabx_ctiouten24_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN24(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN24(a) "CTI_MDABX_CTIOUTEN24"
#define busnum_BDK_CTI_MDABX_CTIOUTEN24(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN24(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten25
 *
 * CTI Mdab Ctiouten25 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten25
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten25_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten25_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten25 bdk_cti_mdabx_ctiouten25_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN25(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN25(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112104 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN25", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN25(a) bdk_cti_mdabx_ctiouten25_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN25(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN25(a) "CTI_MDABX_CTIOUTEN25"
#define busnum_BDK_CTI_MDABX_CTIOUTEN25(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN25(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten26
 *
 * CTI Mdab Ctiouten26 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten26
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten26_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten26_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten26 bdk_cti_mdabx_ctiouten26_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN26(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN26(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112108 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN26", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN26(a) bdk_cti_mdabx_ctiouten26_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN26(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN26(a) "CTI_MDABX_CTIOUTEN26"
#define busnum_BDK_CTI_MDABX_CTIOUTEN26(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN26(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten27
 *
 * CTI Mdab Ctiouten27 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten27
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten27_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten27_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten27 bdk_cti_mdabx_ctiouten27_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN27(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN27(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611210c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN27", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN27(a) bdk_cti_mdabx_ctiouten27_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN27(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN27(a) "CTI_MDABX_CTIOUTEN27"
#define busnum_BDK_CTI_MDABX_CTIOUTEN27(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN27(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten28
 *
 * CTI Mdab Ctiouten28 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten28
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten28_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten28_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten28 bdk_cti_mdabx_ctiouten28_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN28(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN28(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112110 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN28", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN28(a) bdk_cti_mdabx_ctiouten28_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN28(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN28(a) "CTI_MDABX_CTIOUTEN28"
#define busnum_BDK_CTI_MDABX_CTIOUTEN28(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN28(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten29
 *
 * CTI Mdab Ctiouten29 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten29
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten29_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten29_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten29 bdk_cti_mdabx_ctiouten29_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN29(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN29(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112114 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN29", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN29(a) bdk_cti_mdabx_ctiouten29_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN29(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN29(a) "CTI_MDABX_CTIOUTEN29"
#define busnum_BDK_CTI_MDABX_CTIOUTEN29(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN29(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten3
 *
 * CTI Mdab Ctiouten3 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten3
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten3_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten3 bdk_cti_mdabx_ctiouten3_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120ac + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN3(a) bdk_cti_mdabx_ctiouten3_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN3(a) "CTI_MDABX_CTIOUTEN3"
#define busnum_BDK_CTI_MDABX_CTIOUTEN3(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten30
 *
 * CTI Mdab Ctiouten30 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten30
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten30_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten30_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten30 bdk_cti_mdabx_ctiouten30_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN30(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN30(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112118 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN30", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN30(a) bdk_cti_mdabx_ctiouten30_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN30(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN30(a) "CTI_MDABX_CTIOUTEN30"
#define busnum_BDK_CTI_MDABX_CTIOUTEN30(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN30(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten31
 *
 * CTI Mdab Ctiouten31 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten31
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten31_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten31_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten31 bdk_cti_mdabx_ctiouten31_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN31(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN31(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e04611211c + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN31", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN31(a) bdk_cti_mdabx_ctiouten31_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN31(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN31(a) "CTI_MDABX_CTIOUTEN31"
#define busnum_BDK_CTI_MDABX_CTIOUTEN31(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN31(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten4
 *
 * CTI Mdab Ctiouten4 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten4
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten4_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten4 bdk_cti_mdabx_ctiouten4_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120b0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN4(a) bdk_cti_mdabx_ctiouten4_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN4(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN4(a) "CTI_MDABX_CTIOUTEN4"
#define busnum_BDK_CTI_MDABX_CTIOUTEN4(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN4(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten5
 *
 * CTI Mdab Ctiouten5 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten5
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten5_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten5 bdk_cti_mdabx_ctiouten5_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120b4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN5(a) bdk_cti_mdabx_ctiouten5_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN5(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN5(a) "CTI_MDABX_CTIOUTEN5"
#define busnum_BDK_CTI_MDABX_CTIOUTEN5(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN5(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten6
 *
 * CTI Mdab Ctiouten6 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten6
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten6_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten6 bdk_cti_mdabx_ctiouten6_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120b8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN6(a) bdk_cti_mdabx_ctiouten6_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN6(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN6(a) "CTI_MDABX_CTIOUTEN6"
#define busnum_BDK_CTI_MDABX_CTIOUTEN6(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN6(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten7
 *
 * CTI Mdab Ctiouten7 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten7
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten7_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten7 bdk_cti_mdabx_ctiouten7_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120bc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN7(a) bdk_cti_mdabx_ctiouten7_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN7(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN7(a) "CTI_MDABX_CTIOUTEN7"
#define busnum_BDK_CTI_MDABX_CTIOUTEN7(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN7(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten8
 *
 * CTI Mdab Ctiouten8 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten8
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten8_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten8_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten8 bdk_cti_mdabx_ctiouten8_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN8(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN8(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120c0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN8", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN8(a) bdk_cti_mdabx_ctiouten8_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN8(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN8(a) "CTI_MDABX_CTIOUTEN8"
#define busnum_BDK_CTI_MDABX_CTIOUTEN8(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN8(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctiouten9
 *
 * CTI Mdab Ctiouten9 Register
 * This register maps channels in the cross trigger system to trigger outputs. The
 * CTIOUTEN registers are bit maps that allow any channel input to be mapped to the
 * trigger output, including none (0x0) and all (0xF). There is one register per
 * trigger output so it is possible to map any channel input to any combination of
 * trigger outputs.
 */
union bdk_cti_mdabx_ctiouten9
{
    uint32_t u;
    struct bdk_cti_mdabx_ctiouten9_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
#else /* Word 0 - Little Endian */
        uint32_t trigouten             : 4;  /**< [  3:  0](R/W) Channel to trigger output mapping. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctiouten9_s cn; */
};
typedef union bdk_cti_mdabx_ctiouten9 bdk_cti_mdabx_ctiouten9_t;

static inline uint64_t BDK_CTI_MDABX_CTIOUTEN9(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTIOUTEN9(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e0461120c4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTIOUTEN9", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTIOUTEN9(a) bdk_cti_mdabx_ctiouten9_t
#define bustype_BDK_CTI_MDABX_CTIOUTEN9(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTIOUTEN9(a) "CTI_MDABX_CTIOUTEN9"
#define busnum_BDK_CTI_MDABX_CTIOUTEN9(a) (a)
#define arguments_BDK_CTI_MDABX_CTIOUTEN9(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctitriginstatus
 *
 * CTI Mdab Ctitriginstatus Register
 * Trigger input status. If the event_in input is driven by a source that generates
 * single cycle pulses, this register is generally read as 0.
 */
union bdk_cti_mdabx_ctitriginstatus
{
    uint32_t u;
    struct bdk_cti_mdabx_ctitriginstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t triginstatus          : 32; /**< [ 31:  0](RO) Trigger input status. */
#else /* Word 0 - Little Endian */
        uint32_t triginstatus          : 32; /**< [ 31:  0](RO) Trigger input status. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctitriginstatus_s cn; */
};
typedef union bdk_cti_mdabx_ctitriginstatus bdk_cti_mdabx_ctitriginstatus_t;

static inline uint64_t BDK_CTI_MDABX_CTITRIGINSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTITRIGINSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112130 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTITRIGINSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTITRIGINSTATUS(a) bdk_cti_mdabx_ctitriginstatus_t
#define bustype_BDK_CTI_MDABX_CTITRIGINSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTITRIGINSTATUS(a) "CTI_MDABX_CTITRIGINSTATUS"
#define busnum_BDK_CTI_MDABX_CTITRIGINSTATUS(a) (a)
#define arguments_BDK_CTI_MDABX_CTITRIGINSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ctitrigoutstatus
 *
 * CTI Mdab Ctitrigoutstatus Register
 * Trigger output status. The register only has meaning if the trigger source drives
 * static levels, rather than pulses.
 */
union bdk_cti_mdabx_ctitrigoutstatus
{
    uint32_t u;
    struct bdk_cti_mdabx_ctitrigoutstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t trigoutstatus         : 32; /**< [ 31:  0](RO) Trigger output status. */
#else /* Word 0 - Little Endian */
        uint32_t trigoutstatus         : 32; /**< [ 31:  0](RO) Trigger output status. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ctitrigoutstatus_s cn; */
};
typedef union bdk_cti_mdabx_ctitrigoutstatus bdk_cti_mdabx_ctitrigoutstatus_t;

static inline uint64_t BDK_CTI_MDABX_CTITRIGOUTSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_CTITRIGOUTSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112134 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_CTITRIGOUTSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_CTITRIGOUTSTATUS(a) bdk_cti_mdabx_ctitrigoutstatus_t
#define bustype_BDK_CTI_MDABX_CTITRIGOUTSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_CTITRIGOUTSTATUS(a) "CTI_MDABX_CTITRIGOUTSTATUS"
#define busnum_BDK_CTI_MDABX_CTITRIGOUTSTATUS(a) (a)
#define arguments_BDK_CTI_MDABX_CTITRIGOUTSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_devaff0
 *
 * CTI Mdab Devaff0 Register
 * Enables a debugger to determine if two components have an affinity with each other.
 */
union bdk_cti_mdabx_devaff0
{
    uint32_t u;
    struct bdk_cti_mdabx_devaff0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devaff0               : 32; /**< [ 31:  0](RO) Lower 32-bits of DEVAFF. The value is set by the devaff[31:0] tie-off inputs. */
#else /* Word 0 - Little Endian */
        uint32_t devaff0               : 32; /**< [ 31:  0](RO) Lower 32-bits of DEVAFF. The value is set by the devaff[31:0] tie-off inputs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_devaff0_s cn; */
};
typedef union bdk_cti_mdabx_devaff0 bdk_cti_mdabx_devaff0_t;

static inline uint64_t BDK_CTI_MDABX_DEVAFF0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_DEVAFF0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fa8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_DEVAFF0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_DEVAFF0(a) bdk_cti_mdabx_devaff0_t
#define bustype_BDK_CTI_MDABX_DEVAFF0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_DEVAFF0(a) "CTI_MDABX_DEVAFF0"
#define busnum_BDK_CTI_MDABX_DEVAFF0(a) (a)
#define arguments_BDK_CTI_MDABX_DEVAFF0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_devaff1
 *
 * CTI Mdab Devaff1 Register
 * Enables a debugger to determine if two components have an affinity with each other.
 */
union bdk_cti_mdabx_devaff1
{
    uint32_t u;
    struct bdk_cti_mdabx_devaff1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devaff1               : 32; /**< [ 31:  0](RO) Upper 32-bits of DEVAFF. The value is set by the devaff[63:32] tie-off inputs. */
#else /* Word 0 - Little Endian */
        uint32_t devaff1               : 32; /**< [ 31:  0](RO) Upper 32-bits of DEVAFF. The value is set by the devaff[63:32] tie-off inputs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_devaff1_s cn; */
};
typedef union bdk_cti_mdabx_devaff1 bdk_cti_mdabx_devaff1_t;

static inline uint64_t BDK_CTI_MDABX_DEVAFF1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_DEVAFF1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fac + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_DEVAFF1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_DEVAFF1(a) bdk_cti_mdabx_devaff1_t
#define bustype_BDK_CTI_MDABX_DEVAFF1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_DEVAFF1(a) "CTI_MDABX_DEVAFF1"
#define busnum_BDK_CTI_MDABX_DEVAFF1(a) (a)
#define arguments_BDK_CTI_MDABX_DEVAFF1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_devarch
 *
 * CTI Mdab Devarch Register
 * Identifies the architect and architecture of a CoreSight component. The architect
 * might differ from the designer of a component, for example Arm defines the
 * architecture but another company designs and implements the component.
 */
union bdk_cti_mdabx_devarch
{
    uint32_t u;
    struct bdk_cti_mdabx_devarch_s
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
    /* struct bdk_cti_mdabx_devarch_s cn; */
};
typedef union bdk_cti_mdabx_devarch bdk_cti_mdabx_devarch_t;

static inline uint64_t BDK_CTI_MDABX_DEVARCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_DEVARCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fbc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_DEVARCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_DEVARCH(a) bdk_cti_mdabx_devarch_t
#define bustype_BDK_CTI_MDABX_DEVARCH(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_DEVARCH(a) "CTI_MDABX_DEVARCH"
#define busnum_BDK_CTI_MDABX_DEVARCH(a) (a)
#define arguments_BDK_CTI_MDABX_DEVARCH(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_devid
 *
 * CTI Mdab Devid Register
 * This register is IMPLEMENTATION DEFINED for each Part Number and Designer. The
 * register indicates the capabilities of the component.
 */
union bdk_cti_mdabx_devid
{
    uint32_t u;
    struct bdk_cti_mdabx_devid_s
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
    /* struct bdk_cti_mdabx_devid_s cn; */
};
typedef union bdk_cti_mdabx_devid bdk_cti_mdabx_devid_t;

static inline uint64_t BDK_CTI_MDABX_DEVID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_DEVID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fc8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_DEVID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_DEVID(a) bdk_cti_mdabx_devid_t
#define bustype_BDK_CTI_MDABX_DEVID(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_DEVID(a) "CTI_MDABX_DEVID"
#define busnum_BDK_CTI_MDABX_DEVID(a) (a)
#define arguments_BDK_CTI_MDABX_DEVID(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_devtype
 *
 * CTI Mdab Devtype Register
 * A debugger can use this register to get information about a component that has an
 * unrecognized Part number.
 */
union bdk_cti_mdabx_devtype
{
    uint32_t u;
    struct bdk_cti_mdabx_devtype_s
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
    /* struct bdk_cti_mdabx_devtype_s cn; */
};
typedef union bdk_cti_mdabx_devtype bdk_cti_mdabx_devtype_t;

static inline uint64_t BDK_CTI_MDABX_DEVTYPE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_DEVTYPE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fcc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_DEVTYPE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_DEVTYPE(a) bdk_cti_mdabx_devtype_t
#define bustype_BDK_CTI_MDABX_DEVTYPE(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_DEVTYPE(a) "CTI_MDABX_DEVTYPE"
#define busnum_BDK_CTI_MDABX_DEVTYPE(a) (a)
#define arguments_BDK_CTI_MDABX_DEVTYPE(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_itchin
 *
 * CTI Mdab Itchin Register
 * Integration test to view channel events. The integration test register includes a
 * latch that is set when a pulse is received on a channel input. When read, a register
 * bit reads as 1 if the channel has received a pulse since it was last read. The act
 * of reading the register automatically clears the 1 to a 0. When performing
 * integration testing it is therefore important to coordinate the setting of event
 * latches and reading/clearing them.
 */
union bdk_cti_mdabx_itchin
{
    uint32_t u;
    struct bdk_cti_mdabx_itchin_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
        uint32_t ctichin               : 4;  /**< [  3:  0](RO) Reads the latched value of the channel inputs. */
#else /* Word 0 - Little Endian */
        uint32_t ctichin               : 4;  /**< [  3:  0](RO) Reads the latched value of the channel inputs. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](RO) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_itchin_s cn; */
};
typedef union bdk_cti_mdabx_itchin bdk_cti_mdabx_itchin_t;

static inline uint64_t BDK_CTI_MDABX_ITCHIN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_ITCHIN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112ef4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_ITCHIN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_ITCHIN(a) bdk_cti_mdabx_itchin_t
#define bustype_BDK_CTI_MDABX_ITCHIN(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_ITCHIN(a) "CTI_MDABX_ITCHIN"
#define busnum_BDK_CTI_MDABX_ITCHIN(a) (a)
#define arguments_BDK_CTI_MDABX_ITCHIN(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_itchout
 *
 * CTI Mdab Itchout Register
 * Integration test mode register, used to generate channel events. Writing to the
 * register creates a single pulse on the output. ITCHOUT is self-clearing.
 */
union bdk_cti_mdabx_itchout
{
    uint32_t u;
    struct bdk_cti_mdabx_itchout_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
        uint32_t ctichout              : 4;  /**< [  3:  0](R/W) Pulses the channel outputs. */
#else /* Word 0 - Little Endian */
        uint32_t ctichout              : 4;  /**< [  3:  0](R/W) Pulses the channel outputs. */
        uint32_t sbz_0                 : 28; /**< [ 31:  4](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_itchout_s cn; */
};
typedef union bdk_cti_mdabx_itchout bdk_cti_mdabx_itchout_t;

static inline uint64_t BDK_CTI_MDABX_ITCHOUT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_ITCHOUT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112ee4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_ITCHOUT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_ITCHOUT(a) bdk_cti_mdabx_itchout_t
#define bustype_BDK_CTI_MDABX_ITCHOUT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_ITCHOUT(a) "CTI_MDABX_ITCHOUT"
#define busnum_BDK_CTI_MDABX_ITCHOUT(a) (a)
#define arguments_BDK_CTI_MDABX_ITCHOUT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_itctrl
 *
 * CTI Mdab Itctrl Register
 * The Integration Mode Control register is used to enable topology detection.
 */
union bdk_cti_mdabx_itctrl
{
    uint32_t u;
    struct bdk_cti_mdabx_itctrl_s
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
    /* struct bdk_cti_mdabx_itctrl_s cn; */
};
typedef union bdk_cti_mdabx_itctrl bdk_cti_mdabx_itctrl_t;

static inline uint64_t BDK_CTI_MDABX_ITCTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_ITCTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112f00 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_ITCTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_ITCTRL(a) bdk_cti_mdabx_itctrl_t
#define bustype_BDK_CTI_MDABX_ITCTRL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_ITCTRL(a) "CTI_MDABX_ITCTRL"
#define busnum_BDK_CTI_MDABX_ITCTRL(a) (a)
#define arguments_BDK_CTI_MDABX_ITCTRL(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ittrigin
 *
 * CTI Mdab Ittrigin Register
 * Integration test to view trigger events. The integration test register includes a
 * latch that is set when a pulse is received on a trigger input. When read, a register
 * bit reads as 1 if the trigger input has received a pulse since it was last read. The
 * act of reading the register automatically clears the 1 to a 0. When performing
 * integration testing it is therefore important to coordinate the setting of event
 * latches and reading/clearing them.
 */
union bdk_cti_mdabx_ittrigin
{
    uint32_t u;
    struct bdk_cti_mdabx_ittrigin_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ctitrigin             : 32; /**< [ 31:  0](RO) Reads the latched value of the trigger inputs. */
#else /* Word 0 - Little Endian */
        uint32_t ctitrigin             : 32; /**< [ 31:  0](RO) Reads the latched value of the trigger inputs. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ittrigin_s cn; */
};
typedef union bdk_cti_mdabx_ittrigin bdk_cti_mdabx_ittrigin_t;

static inline uint64_t BDK_CTI_MDABX_ITTRIGIN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_ITTRIGIN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112ef8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_ITTRIGIN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_ITTRIGIN(a) bdk_cti_mdabx_ittrigin_t
#define bustype_BDK_CTI_MDABX_ITTRIGIN(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_ITTRIGIN(a) "CTI_MDABX_ITTRIGIN"
#define busnum_BDK_CTI_MDABX_ITTRIGIN(a) (a)
#define arguments_BDK_CTI_MDABX_ITTRIGIN(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_ittrigout
 *
 * CTI Mdab Ittrigout Register
 * Integration test to generate trigger events.
 */
union bdk_cti_mdabx_ittrigout
{
    uint32_t u;
    struct bdk_cti_mdabx_ittrigout_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ctitrigout            : 32; /**< [ 31:  0](R/W) Set/clear trigger output signal. Reads return the value in the register. Writes: */
#else /* Word 0 - Little Endian */
        uint32_t ctitrigout            : 32; /**< [ 31:  0](R/W) Set/clear trigger output signal. Reads return the value in the register. Writes: */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_ittrigout_s cn; */
};
typedef union bdk_cti_mdabx_ittrigout bdk_cti_mdabx_ittrigout_t;

static inline uint64_t BDK_CTI_MDABX_ITTRIGOUT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_ITTRIGOUT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112ee8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_ITTRIGOUT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_ITTRIGOUT(a) bdk_cti_mdabx_ittrigout_t
#define bustype_BDK_CTI_MDABX_ITTRIGOUT(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_ITTRIGOUT(a) "CTI_MDABX_ITTRIGOUT"
#define busnum_BDK_CTI_MDABX_ITTRIGOUT(a) (a)
#define arguments_BDK_CTI_MDABX_ITTRIGOUT(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_pidr0
 *
 * CTI Mdab Pidr0 Register
 * The PIDR0 register is part of the set of peripheral identification registers.
 */
union bdk_cti_mdabx_pidr0
{
    uint32_t u;
    struct bdk_cti_mdabx_pidr0_s
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
    /* struct bdk_cti_mdabx_pidr0_s cn; */
};
typedef union bdk_cti_mdabx_pidr0 bdk_cti_mdabx_pidr0_t;

static inline uint64_t BDK_CTI_MDABX_PIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_PIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fe0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_PIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_PIDR0(a) bdk_cti_mdabx_pidr0_t
#define bustype_BDK_CTI_MDABX_PIDR0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_PIDR0(a) "CTI_MDABX_PIDR0"
#define busnum_BDK_CTI_MDABX_PIDR0(a) (a)
#define arguments_BDK_CTI_MDABX_PIDR0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_pidr1
 *
 * CTI Mdab Pidr1 Register
 * The PIDR1 register is part of the set of peripheral identification registers.
 */
union bdk_cti_mdabx_pidr1
{
    uint32_t u;
    struct bdk_cti_mdabx_pidr1_s
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
    /* struct bdk_cti_mdabx_pidr1_s cn; */
};
typedef union bdk_cti_mdabx_pidr1 bdk_cti_mdabx_pidr1_t;

static inline uint64_t BDK_CTI_MDABX_PIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_PIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fe4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_PIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_PIDR1(a) bdk_cti_mdabx_pidr1_t
#define bustype_BDK_CTI_MDABX_PIDR1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_PIDR1(a) "CTI_MDABX_PIDR1"
#define busnum_BDK_CTI_MDABX_PIDR1(a) (a)
#define arguments_BDK_CTI_MDABX_PIDR1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_pidr2
 *
 * CTI Mdab Pidr2 Register
 * The PIDR2 register is part of the set of peripheral identification registers.
 */
union bdk_cti_mdabx_pidr2
{
    uint32_t u;
    struct bdk_cti_mdabx_pidr2_s
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
    /* struct bdk_cti_mdabx_pidr2_s cn; */
};
typedef union bdk_cti_mdabx_pidr2 bdk_cti_mdabx_pidr2_t;

static inline uint64_t BDK_CTI_MDABX_PIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_PIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fe8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_PIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_PIDR2(a) bdk_cti_mdabx_pidr2_t
#define bustype_BDK_CTI_MDABX_PIDR2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_PIDR2(a) "CTI_MDABX_PIDR2"
#define busnum_BDK_CTI_MDABX_PIDR2(a) (a)
#define arguments_BDK_CTI_MDABX_PIDR2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_pidr3
 *
 * CTI Mdab Pidr3 Register
 * The PIDR3 register is part of the set of peripheral identification registers.
 */
union bdk_cti_mdabx_pidr3
{
    uint32_t u;
    struct bdk_cti_mdabx_pidr3_s
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
    /* struct bdk_cti_mdabx_pidr3_s cn; */
};
typedef union bdk_cti_mdabx_pidr3 bdk_cti_mdabx_pidr3_t;

static inline uint64_t BDK_CTI_MDABX_PIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_PIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fec + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_PIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_PIDR3(a) bdk_cti_mdabx_pidr3_t
#define bustype_BDK_CTI_MDABX_PIDR3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_PIDR3(a) "CTI_MDABX_PIDR3"
#define busnum_BDK_CTI_MDABX_PIDR3(a) (a)
#define arguments_BDK_CTI_MDABX_PIDR3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_pidr4
 *
 * CTI Mdab Pidr4 Register
 * The PIDR4 register is part of the set of peripheral identification registers.
 */
union bdk_cti_mdabx_pidr4
{
    uint32_t u;
    struct bdk_cti_mdabx_pidr4_s
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
    /* struct bdk_cti_mdabx_pidr4_s cn; */
};
typedef union bdk_cti_mdabx_pidr4 bdk_cti_mdabx_pidr4_t;

static inline uint64_t BDK_CTI_MDABX_PIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_PIDR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fd0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_PIDR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_PIDR4(a) bdk_cti_mdabx_pidr4_t
#define bustype_BDK_CTI_MDABX_PIDR4(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_PIDR4(a) "CTI_MDABX_PIDR4"
#define busnum_BDK_CTI_MDABX_PIDR4(a) (a)
#define arguments_BDK_CTI_MDABX_PIDR4(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_pidr5
 *
 * CTI Mdab Pidr5 Register
 * The PIDR5 register is part of the set of peripheral identification registers.
 */
union bdk_cti_mdabx_pidr5
{
    uint32_t u;
    struct bdk_cti_mdabx_pidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr5                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr5                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_pidr5_s cn; */
};
typedef union bdk_cti_mdabx_pidr5 bdk_cti_mdabx_pidr5_t;

static inline uint64_t BDK_CTI_MDABX_PIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_PIDR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fd4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_PIDR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_PIDR5(a) bdk_cti_mdabx_pidr5_t
#define bustype_BDK_CTI_MDABX_PIDR5(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_PIDR5(a) "CTI_MDABX_PIDR5"
#define busnum_BDK_CTI_MDABX_PIDR5(a) (a)
#define arguments_BDK_CTI_MDABX_PIDR5(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_pidr6
 *
 * CTI Mdab Pidr6 Register
 * The PIDR6 register is part of the set of peripheral identification registers.
 */
union bdk_cti_mdabx_pidr6
{
    uint32_t u;
    struct bdk_cti_mdabx_pidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr6                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr6                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_pidr6_s cn; */
};
typedef union bdk_cti_mdabx_pidr6 bdk_cti_mdabx_pidr6_t;

static inline uint64_t BDK_CTI_MDABX_PIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_PIDR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fd8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_PIDR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_PIDR6(a) bdk_cti_mdabx_pidr6_t
#define bustype_BDK_CTI_MDABX_PIDR6(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_PIDR6(a) "CTI_MDABX_PIDR6"
#define busnum_BDK_CTI_MDABX_PIDR6(a) (a)
#define arguments_BDK_CTI_MDABX_PIDR6(a) (a),-1,-1,-1

/**
 * Register (RSL32b) cti_mdab#_pidr7
 *
 * CTI Mdab Pidr7 Register
 * The PIDR7 register is part of the set of peripheral identification registers.
 */
union bdk_cti_mdabx_pidr7
{
    uint32_t u;
    struct bdk_cti_mdabx_pidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr7                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr7                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cti_mdabx_pidr7_s cn; */
};
typedef union bdk_cti_mdabx_pidr7 bdk_cti_mdabx_pidr7_t;

static inline uint64_t BDK_CTI_MDABX_PIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CTI_MDABX_PIDR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046112fdc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("CTI_MDABX_PIDR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_CTI_MDABX_PIDR7(a) bdk_cti_mdabx_pidr7_t
#define bustype_BDK_CTI_MDABX_PIDR7(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_CTI_MDABX_PIDR7(a) "CTI_MDABX_PIDR7"
#define busnum_BDK_CTI_MDABX_PIDR7(a) (a)
#define arguments_BDK_CTI_MDABX_PIDR7(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_CTI_MDAB_H__ */
