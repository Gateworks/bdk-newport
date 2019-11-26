#ifndef __BDK_CSRS_ATBFUNNEL_MDAB_H__
#define __BDK_CSRS_ATBFUNNEL_MDAB_H__
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
 * OcteonTX ATBFUNNEL_MDAB.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Register (RSL32b) atbfunnel_mdab#_authstatus
 *
 * ATBFUNNEL Mdab Authstatus Register
 * Reports the current status of the authentication control signals.
 */
union bdk_atbfunnel_mdabx_authstatus
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_authstatus_s
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
    /* struct bdk_atbfunnel_mdabx_authstatus_s cn; */
};
typedef union bdk_atbfunnel_mdabx_authstatus bdk_atbfunnel_mdabx_authstatus_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_AUTHSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_AUTHSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fb8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_AUTHSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_AUTHSTATUS(a) bdk_atbfunnel_mdabx_authstatus_t
#define bustype_BDK_ATBFUNNEL_MDABX_AUTHSTATUS(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_AUTHSTATUS(a) "ATBFUNNEL_MDABX_AUTHSTATUS"
#define busnum_BDK_ATBFUNNEL_MDABX_AUTHSTATUS(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_AUTHSTATUS(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_cidr0
 *
 * ATBFUNNEL Mdab Cidr0 Register
 * The CIDR0 register is part of the set of component identification registers.
 */
union bdk_atbfunnel_mdabx_cidr0
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_cidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x0D. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x0D. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_cidr0_s cn; */
};
typedef union bdk_atbfunnel_mdabx_cidr0 bdk_atbfunnel_mdabx_cidr0_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_CIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_CIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111ff0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_CIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_CIDR0(a) bdk_atbfunnel_mdabx_cidr0_t
#define bustype_BDK_ATBFUNNEL_MDABX_CIDR0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_CIDR0(a) "ATBFUNNEL_MDABX_CIDR0"
#define busnum_BDK_ATBFUNNEL_MDABX_CIDR0(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_CIDR0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_cidr1
 *
 * ATBFUNNEL Mdab Cidr1 Register
 * The CIDR1 register is part of the set of component identification registers.
 */
union bdk_atbfunnel_mdabx_cidr1
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_cidr1_s
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
    /* struct bdk_atbfunnel_mdabx_cidr1_s cn; */
};
typedef union bdk_atbfunnel_mdabx_cidr1 bdk_atbfunnel_mdabx_cidr1_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_CIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_CIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111ff4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_CIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_CIDR1(a) bdk_atbfunnel_mdabx_cidr1_t
#define bustype_BDK_ATBFUNNEL_MDABX_CIDR1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_CIDR1(a) "ATBFUNNEL_MDABX_CIDR1"
#define busnum_BDK_ATBFUNNEL_MDABX_CIDR1(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_CIDR1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_cidr2
 *
 * ATBFUNNEL Mdab Cidr2 Register
 * The CIDR2 register is part of the set of component identification registers.
 */
union bdk_atbfunnel_mdabx_cidr2
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_cidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x05. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble. Returns 0x05. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_cidr2_s cn; */
};
typedef union bdk_atbfunnel_mdabx_cidr2 bdk_atbfunnel_mdabx_cidr2_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_CIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_CIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111ff8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_CIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_CIDR2(a) bdk_atbfunnel_mdabx_cidr2_t
#define bustype_BDK_ATBFUNNEL_MDABX_CIDR2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_CIDR2(a) "ATBFUNNEL_MDABX_CIDR2"
#define busnum_BDK_ATBFUNNEL_MDABX_CIDR2(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_CIDR2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_cidr3
 *
 * ATBFUNNEL Mdab Cidr3 Register
 * The CIDR3 register is part of the set of component identification registers.
 */
union bdk_atbfunnel_mdabx_cidr3
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_cidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Returns 0xB1. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble. Returns 0xB1. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_cidr3_s cn; */
};
typedef union bdk_atbfunnel_mdabx_cidr3 bdk_atbfunnel_mdabx_cidr3_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_CIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_CIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111ffc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_CIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_CIDR3(a) bdk_atbfunnel_mdabx_cidr3_t
#define bustype_BDK_ATBFUNNEL_MDABX_CIDR3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_CIDR3(a) "ATBFUNNEL_MDABX_CIDR3"
#define busnum_BDK_ATBFUNNEL_MDABX_CIDR3(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_CIDR3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_claimclr
 *
 * ATBFUNNEL Mdab Claimclr Register
 * This register forms one half of the claim tag value. On writes, this location
 * enables individual bits to be cleared. On reads, it returns the current claim tag
 * value.
 */
union bdk_atbfunnel_mdabx_claimclr
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_claimclr_s
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
    /* struct bdk_atbfunnel_mdabx_claimclr_s cn; */
};
typedef union bdk_atbfunnel_mdabx_claimclr bdk_atbfunnel_mdabx_claimclr_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_CLAIMCLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_CLAIMCLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fa4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_CLAIMCLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_CLAIMCLR(a) bdk_atbfunnel_mdabx_claimclr_t
#define bustype_BDK_ATBFUNNEL_MDABX_CLAIMCLR(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_CLAIMCLR(a) "ATBFUNNEL_MDABX_CLAIMCLR"
#define busnum_BDK_ATBFUNNEL_MDABX_CLAIMCLR(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_CLAIMCLR(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_claimset
 *
 * ATBFUNNEL Mdab Claimset Register
 * This register forms one half of the claim tag value. On writes, this location
 * enables individual bits to be set. On reads, it returns the number of bits that can
 * be set.
 */
union bdk_atbfunnel_mdabx_claimset
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_claimset_s
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
    /* struct bdk_atbfunnel_mdabx_claimset_s cn; */
};
typedef union bdk_atbfunnel_mdabx_claimset bdk_atbfunnel_mdabx_claimset_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_CLAIMSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_CLAIMSET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fa0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_CLAIMSET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_CLAIMSET(a) bdk_atbfunnel_mdabx_claimset_t
#define bustype_BDK_ATBFUNNEL_MDABX_CLAIMSET(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_CLAIMSET(a) "ATBFUNNEL_MDABX_CLAIMSET"
#define busnum_BDK_ATBFUNNEL_MDABX_CLAIMSET(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_CLAIMSET(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_devaff0
 *
 * ATBFUNNEL Mdab Devaff0 Register
 * Enables a debugger to determine if two components have an affinity with each other.
 */
union bdk_atbfunnel_mdabx_devaff0
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_devaff0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devaff0               : 32; /**< [ 31:  0](RO) This field is RAZ. */
#else /* Word 0 - Little Endian */
        uint32_t devaff0               : 32; /**< [ 31:  0](RO) This field is RAZ. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_devaff0_s cn; */
};
typedef union bdk_atbfunnel_mdabx_devaff0 bdk_atbfunnel_mdabx_devaff0_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVAFF0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVAFF0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fa8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_DEVAFF0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_DEVAFF0(a) bdk_atbfunnel_mdabx_devaff0_t
#define bustype_BDK_ATBFUNNEL_MDABX_DEVAFF0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_DEVAFF0(a) "ATBFUNNEL_MDABX_DEVAFF0"
#define busnum_BDK_ATBFUNNEL_MDABX_DEVAFF0(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_DEVAFF0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_devaff1
 *
 * ATBFUNNEL Mdab Devaff1 Register
 * Enables a debugger to determine if two components have an affinity with each other.
 */
union bdk_atbfunnel_mdabx_devaff1
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_devaff1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devaff1               : 32; /**< [ 31:  0](RO) This field is RAZ. */
#else /* Word 0 - Little Endian */
        uint32_t devaff1               : 32; /**< [ 31:  0](RO) This field is RAZ. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_devaff1_s cn; */
};
typedef union bdk_atbfunnel_mdabx_devaff1 bdk_atbfunnel_mdabx_devaff1_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVAFF1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVAFF1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fac + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_DEVAFF1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_DEVAFF1(a) bdk_atbfunnel_mdabx_devaff1_t
#define bustype_BDK_ATBFUNNEL_MDABX_DEVAFF1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_DEVAFF1(a) "ATBFUNNEL_MDABX_DEVAFF1"
#define busnum_BDK_ATBFUNNEL_MDABX_DEVAFF1(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_DEVAFF1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_devarch
 *
 * ATBFUNNEL Mdab Devarch Register
 * Identifies the architect and architecture of a CoreSight component. The architect
 * might differ from the designer of a component, for example Arm defines the
 * architecture but another company designs and implements the component.
 */
union bdk_atbfunnel_mdabx_devarch
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_devarch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Returns 0. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) Returns 0, indicating that the DEVARCH register is not present. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Returns 0 */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Returns 0. */
#else /* Word 0 - Little Endian */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Returns 0. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Returns 0 */
        uint32_t present               : 1;  /**< [ 20: 20](RO) Returns 0, indicating that the DEVARCH register is not present. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Returns 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_devarch_s cn; */
};
typedef union bdk_atbfunnel_mdabx_devarch bdk_atbfunnel_mdabx_devarch_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVARCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVARCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fbc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_DEVARCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_DEVARCH(a) bdk_atbfunnel_mdabx_devarch_t
#define bustype_BDK_ATBFUNNEL_MDABX_DEVARCH(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_DEVARCH(a) "ATBFUNNEL_MDABX_DEVARCH"
#define busnum_BDK_ATBFUNNEL_MDABX_DEVARCH(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_DEVARCH(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_devid
 *
 * ATBFUNNEL Mdab Devid Register
 * This register is IMPLEMENTATION DEFINED for each Part Number and Designer. The
 * register indicates the capabilities of the component.
 */
union bdk_atbfunnel_mdabx_devid
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_devid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t scheme                : 4;  /**< [  7:  4](RO) Indicates priority scheme implemented. Input priority is controlled by the
                                                                 PRIORITYCONTROL register. */
        uint32_t portcount             : 4;  /**< [  3:  0](RO) Indicates the number of input ports connected. */
#else /* Word 0 - Little Endian */
        uint32_t portcount             : 4;  /**< [  3:  0](RO) Indicates the number of input ports connected. */
        uint32_t scheme                : 4;  /**< [  7:  4](RO) Indicates priority scheme implemented. Input priority is controlled by the
                                                                 PRIORITYCONTROL register. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_devid_s cn; */
};
typedef union bdk_atbfunnel_mdabx_devid bdk_atbfunnel_mdabx_devid_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fc8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_DEVID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_DEVID(a) bdk_atbfunnel_mdabx_devid_t
#define bustype_BDK_ATBFUNNEL_MDABX_DEVID(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_DEVID(a) "ATBFUNNEL_MDABX_DEVID"
#define busnum_BDK_ATBFUNNEL_MDABX_DEVID(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_DEVID(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_devid1
 *
 * ATBFUNNEL Mdab Devid1 Register
 * Contains an IMPLEMENTATION DEFINED value.
 */
union bdk_atbfunnel_mdabx_devid1
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_devid1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devid1                : 32; /**< [ 31:  0](RO) This field is RAZ. */
#else /* Word 0 - Little Endian */
        uint32_t devid1                : 32; /**< [ 31:  0](RO) This field is RAZ. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_devid1_s cn; */
};
typedef union bdk_atbfunnel_mdabx_devid1 bdk_atbfunnel_mdabx_devid1_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVID1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVID1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fc4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_DEVID1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_DEVID1(a) bdk_atbfunnel_mdabx_devid1_t
#define bustype_BDK_ATBFUNNEL_MDABX_DEVID1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_DEVID1(a) "ATBFUNNEL_MDABX_DEVID1"
#define busnum_BDK_ATBFUNNEL_MDABX_DEVID1(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_DEVID1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_devid2
 *
 * ATBFUNNEL Mdab Devid2 Register
 * Contains an IMPLEMENTATION DEFINED value.
 */
union bdk_atbfunnel_mdabx_devid2
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_devid2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t devid2                : 32; /**< [ 31:  0](RO) This field is RAZ. */
#else /* Word 0 - Little Endian */
        uint32_t devid2                : 32; /**< [ 31:  0](RO) This field is RAZ. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_devid2_s cn; */
};
typedef union bdk_atbfunnel_mdabx_devid2 bdk_atbfunnel_mdabx_devid2_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVID2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVID2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fc0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_DEVID2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_DEVID2(a) bdk_atbfunnel_mdabx_devid2_t
#define bustype_BDK_ATBFUNNEL_MDABX_DEVID2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_DEVID2(a) "ATBFUNNEL_MDABX_DEVID2"
#define busnum_BDK_ATBFUNNEL_MDABX_DEVID2(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_DEVID2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_devtype
 *
 * ATBFUNNEL Mdab Devtype Register
 * A debugger can use this register to get information about a component that has an
 * unrecognized Part number.
 */
union bdk_atbfunnel_mdabx_devtype
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_devtype_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Minor classification. Returns 0x1, indicating this component is a Funnel/Router. */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major classification. Returns 0x2, indicating this component is a Trace Link. */
#else /* Word 0 - Little Endian */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major classification. Returns 0x2, indicating this component is a Trace Link. */
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Minor classification. Returns 0x1, indicating this component is a Funnel/Router. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_devtype_s cn; */
};
typedef union bdk_atbfunnel_mdabx_devtype bdk_atbfunnel_mdabx_devtype_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVTYPE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_DEVTYPE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fcc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_DEVTYPE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_DEVTYPE(a) bdk_atbfunnel_mdabx_devtype_t
#define bustype_BDK_ATBFUNNEL_MDABX_DEVTYPE(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_DEVTYPE(a) "ATBFUNNEL_MDABX_DEVTYPE"
#define busnum_BDK_ATBFUNNEL_MDABX_DEVTYPE(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_DEVTYPE(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_funnelcontrol
 *
 * ATBFUNNEL Mdab Funnelcontrol Register
 * The Funnel Control register is for enabling each of the trace sources and
 * controlling the hold time for switching between them.
 */
union bdk_atbfunnel_mdabx_funnelcontrol
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_funnelcontrol_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 19; /**< [ 31: 13](R/W) Software should write the field as all 0s. */
        uint32_t flush_normal          : 1;  /**< [ 12: 12](R/W) This bit, when clear, allows slave ports that are already flushed to receive
                                                                 further data even if there are other ports that have not completed flush. If
                                                                 set, a port that has completed flush is not be allowed to receive further data
                                                                 until all ports have completed flush. */
        uint32_t ht                    : 4;  /**< [ 11:  8](R/W) Hold time. Value sets the minimum hold time before switching trace sources
                                                                 (funnel inputs) based on the ID. Value used is programmed value + 1. */
        uint32_t ens7                  : 1;  /**< [  7:  7](R/W) Enable slave interface 7. */
        uint32_t ens6                  : 1;  /**< [  6:  6](R/W) Enable slave interface 6. */
        uint32_t ens5                  : 1;  /**< [  5:  5](R/W) Enable slave interface 5. */
        uint32_t ens4                  : 1;  /**< [  4:  4](R/W) Enable slave interface 4. */
        uint32_t ens3                  : 1;  /**< [  3:  3](R/W) Enable slave interface 3. */
        uint32_t ens2                  : 1;  /**< [  2:  2](R/W) Enable slave interface 2. */
        uint32_t ens1                  : 1;  /**< [  1:  1](R/W) Enable slave interface 1. */
        uint32_t ens0                  : 1;  /**< [  0:  0](R/W) Enable slave interface 0. */
#else /* Word 0 - Little Endian */
        uint32_t ens0                  : 1;  /**< [  0:  0](R/W) Enable slave interface 0. */
        uint32_t ens1                  : 1;  /**< [  1:  1](R/W) Enable slave interface 1. */
        uint32_t ens2                  : 1;  /**< [  2:  2](R/W) Enable slave interface 2. */
        uint32_t ens3                  : 1;  /**< [  3:  3](R/W) Enable slave interface 3. */
        uint32_t ens4                  : 1;  /**< [  4:  4](R/W) Enable slave interface 4. */
        uint32_t ens5                  : 1;  /**< [  5:  5](R/W) Enable slave interface 5. */
        uint32_t ens6                  : 1;  /**< [  6:  6](R/W) Enable slave interface 6. */
        uint32_t ens7                  : 1;  /**< [  7:  7](R/W) Enable slave interface 7. */
        uint32_t ht                    : 4;  /**< [ 11:  8](R/W) Hold time. Value sets the minimum hold time before switching trace sources
                                                                 (funnel inputs) based on the ID. Value used is programmed value + 1. */
        uint32_t flush_normal          : 1;  /**< [ 12: 12](R/W) This bit, when clear, allows slave ports that are already flushed to receive
                                                                 further data even if there are other ports that have not completed flush. If
                                                                 set, a port that has completed flush is not be allowed to receive further data
                                                                 until all ports have completed flush. */
        uint32_t sbz_0                 : 19; /**< [ 31: 13](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_funnelcontrol_s cn; */
};
typedef union bdk_atbfunnel_mdabx_funnelcontrol bdk_atbfunnel_mdabx_funnelcontrol_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_FUNNELCONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_FUNNELCONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111000 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_FUNNELCONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_FUNNELCONTROL(a) bdk_atbfunnel_mdabx_funnelcontrol_t
#define bustype_BDK_ATBFUNNEL_MDABX_FUNNELCONTROL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_FUNNELCONTROL(a) "ATBFUNNEL_MDABX_FUNNELCONTROL"
#define busnum_BDK_ATBFUNNEL_MDABX_FUNNELCONTROL(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_FUNNELCONTROL(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_itatbctr0
 *
 * ATBFUNNEL Mdab Itatbctr0 Register
 * This register allows observability and controllability of the ATBYTES buses, and
 * AFREADY and ATVALID signals into, and out of, the funnel. For slave signals coming
 * into the funnel, the register views the ports that are selected through the funnel
 * control register. Only one port must be selected for integration test.
 */
union bdk_atbfunnel_mdabx_itatbctr0
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_itatbctr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_1                 : 22; /**< [ 31: 10](R/W) Software should write the field as all 0s. */
        uint32_t atbytes               : 2;  /**< [  9:  8](R/W) Reads the value on atbytes_s[1:0] and writes the values on atbytes_m[1:0]. */
        uint32_t sbz_0                 : 6;  /**< [  7:  2](R/W) Software should write the field as all 0s. */
        uint32_t afready               : 1;  /**< [  1:  1](R/W) Reads and controls the afready signals into, and out of, the funnel. */
        uint32_t atvalid               : 1;  /**< [  0:  0](R/W) Reads and controls the atvalid signals into, and out of, the funnel. */
#else /* Word 0 - Little Endian */
        uint32_t atvalid               : 1;  /**< [  0:  0](R/W) Reads and controls the atvalid signals into, and out of, the funnel. */
        uint32_t afready               : 1;  /**< [  1:  1](R/W) Reads and controls the afready signals into, and out of, the funnel. */
        uint32_t sbz_0                 : 6;  /**< [  7:  2](R/W) Software should write the field as all 0s. */
        uint32_t atbytes               : 2;  /**< [  9:  8](R/W) Reads the value on atbytes_s[1:0] and writes the values on atbytes_m[1:0]. */
        uint32_t sbz_1                 : 22; /**< [ 31: 10](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_itatbctr0_s cn; */
};
typedef union bdk_atbfunnel_mdabx_itatbctr0 bdk_atbfunnel_mdabx_itatbctr0_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBCTR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBCTR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111efc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_ITATBCTR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_ITATBCTR0(a) bdk_atbfunnel_mdabx_itatbctr0_t
#define bustype_BDK_ATBFUNNEL_MDABX_ITATBCTR0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_ITATBCTR0(a) "ATBFUNNEL_MDABX_ITATBCTR0"
#define busnum_BDK_ATBFUNNEL_MDABX_ITATBCTR0(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_ITATBCTR0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_itatbctr1
 *
 * ATBFUNNEL Mdab Itatbctr1 Register
 * This register allows observability and controllability of the ATID buses into, and
 * out of, the funnel. For slave signals coming into the funnel, the register views the
 * ports that are selected through the funnel control register. Only one port must be
 * selected for integration test.
 */
union bdk_atbfunnel_mdabx_itatbctr1
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_itatbctr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 25; /**< [ 31:  7](R/W) Software should write the field as all 0s. */
        uint32_t atid                  : 7;  /**< [  6:  0](R/W) When read returns the value on atid_s, when written drives the value on atid_m. */
#else /* Word 0 - Little Endian */
        uint32_t atid                  : 7;  /**< [  6:  0](R/W) When read returns the value on atid_s, when written drives the value on atid_m. */
        uint32_t sbz_0                 : 25; /**< [ 31:  7](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_itatbctr1_s cn; */
};
typedef union bdk_atbfunnel_mdabx_itatbctr1 bdk_atbfunnel_mdabx_itatbctr1_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBCTR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBCTR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111ef8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_ITATBCTR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_ITATBCTR1(a) bdk_atbfunnel_mdabx_itatbctr1_t
#define bustype_BDK_ATBFUNNEL_MDABX_ITATBCTR1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_ITATBCTR1(a) "ATBFUNNEL_MDABX_ITATBCTR1"
#define busnum_BDK_ATBFUNNEL_MDABX_ITATBCTR1(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_ITATBCTR1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_itatbctr2
 *
 * ATBFUNNEL Mdab Itatbctr2 Register
 * This register allows observability and controllability of the afvalid and atready
 * signals into, and out of, the funnel. For slave signals coming into the funnel, the
 * register views the ports that are selected through the funnel control register. Only
 * one port must be selected for integration test.
 */
union bdk_atbfunnel_mdabx_itatbctr2
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_itatbctr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 30; /**< [ 31:  2](R/W) Software should write the field as all 0s. */
        uint32_t afvalid               : 1;  /**< [  1:  1](R/W) Reads and controls the afvalid signals into, and out of, the funnel. */
        uint32_t atready               : 1;  /**< [  0:  0](R/W) Reads and controls the atready signal into, and out of, the funnel. */
#else /* Word 0 - Little Endian */
        uint32_t atready               : 1;  /**< [  0:  0](R/W) Reads and controls the atready signal into, and out of, the funnel. */
        uint32_t afvalid               : 1;  /**< [  1:  1](R/W) Reads and controls the afvalid signals into, and out of, the funnel. */
        uint32_t sbz_0                 : 30; /**< [ 31:  2](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_itatbctr2_s cn; */
};
typedef union bdk_atbfunnel_mdabx_itatbctr2 bdk_atbfunnel_mdabx_itatbctr2_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBCTR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBCTR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111ef4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_ITATBCTR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_ITATBCTR2(a) bdk_atbfunnel_mdabx_itatbctr2_t
#define bustype_BDK_ATBFUNNEL_MDABX_ITATBCTR2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_ITATBCTR2(a) "ATBFUNNEL_MDABX_ITATBCTR2"
#define busnum_BDK_ATBFUNNEL_MDABX_ITATBCTR2(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_ITATBCTR2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_itatbctr3
 *
 * ATBFUNNEL Mdab Itatbctr3 Register
 * This register allows observability and controllability of the SYNCREQ signals into,
 * and out of, the funnel. Only one slave interface must be selected for integration
 * test. The syncreq receiver on the master interface has a latching function to
 * capture a pulse arriving on that input. The arrival of a pulse sets the latch so
 * that the value can be read. Reading the register clears the latch. Reading a 1
 * indicates that a syncreq_m pulse arrived since the last read. Reading a 0 indicates
 * that no syncreq_m pulse has arrived. Writing a 1 to the register causes a syncreq_s
 * pulse to be generated to the upstream component.
 */
union bdk_atbfunnel_mdabx_itatbctr3
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_itatbctr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 31; /**< [ 31:  1](R/W) Software should write the field as all 0s. */
        uint32_t syncreq               : 1;  /**< [  0:  0](R/W) Reads and controls the SYNCREQ signals into, and out of, the funnel. Reading clears the latch. */
#else /* Word 0 - Little Endian */
        uint32_t syncreq               : 1;  /**< [  0:  0](R/W) Reads and controls the SYNCREQ signals into, and out of, the funnel. Reading clears the latch. */
        uint32_t sbz_0                 : 31; /**< [ 31:  1](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_itatbctr3_s cn; */
};
typedef union bdk_atbfunnel_mdabx_itatbctr3 bdk_atbfunnel_mdabx_itatbctr3_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBCTR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBCTR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111ef0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_ITATBCTR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_ITATBCTR3(a) bdk_atbfunnel_mdabx_itatbctr3_t
#define bustype_BDK_ATBFUNNEL_MDABX_ITATBCTR3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_ITATBCTR3(a) "ATBFUNNEL_MDABX_ITATBCTR3"
#define busnum_BDK_ATBFUNNEL_MDABX_ITATBCTR3(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_ITATBCTR3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_itatbdata0
 *
 * ATBFUNNEL Mdab Itatbdata0 Register
 * This register allows observability and controllability of the ATDATA buses into and
 * out of the funnel. For slave signals coming into the funnel, the register views the
 * ports that are selected through the funnel control register. Only one port must be
 * selected for integration test.
 */
union bdk_atbfunnel_mdabx_itatbdata0
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_itatbdata0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 15; /**< [ 31: 17](R/W) Software should write the field as all 0s. */
        uint32_t atdata127             : 1;  /**< [ 16: 16](R/W) Reads atdata_s[127] and writes atdata_m[127]. */
        uint32_t atdata119             : 1;  /**< [ 15: 15](R/W) Reads atdata_s[119] and writes atdata_m[119]. */
        uint32_t atdata111             : 1;  /**< [ 14: 14](R/W) Reads atdata_s[111] and writes atdata_m[111]. */
        uint32_t atdata103             : 1;  /**< [ 13: 13](R/W) Reads atdata_s[103] and writes atdata_m[103]. */
        uint32_t atdata95              : 1;  /**< [ 12: 12](R/W) Reads atdata_s[95] and writes atdata_m[95]. */
        uint32_t atdata87              : 1;  /**< [ 11: 11](R/W) Reads atdata_s[87] and writes atdata_m[87]. */
        uint32_t atdata79              : 1;  /**< [ 10: 10](R/W) Reads atdata_s[79] and writes atdata_m[79]. */
        uint32_t atdata71              : 1;  /**< [  9:  9](R/W) Reads atdata_s[71] and writes atdata_m[71]. */
        uint32_t atdata63              : 1;  /**< [  8:  8](R/W) Reads atdata_s[63] and writes atdata_m[63]. */
        uint32_t atdata55              : 1;  /**< [  7:  7](R/W) Reads atdata_s[55] and writes atdata_m[55]. */
        uint32_t atdata47              : 1;  /**< [  6:  6](R/W) Reads atdata_s[47] and writes atdata_m[47]. */
        uint32_t atdata39              : 1;  /**< [  5:  5](R/W) Reads atdata_s[39] and writes atdata_m[39]. */
        uint32_t atdata31              : 1;  /**< [  4:  4](R/W) Reads atdata_s[31] and writes atdata_m[31]. */
        uint32_t atdata23              : 1;  /**< [  3:  3](R/W) Reads atdata_s[23] and writes atdata_m[23]. */
        uint32_t atdata15              : 1;  /**< [  2:  2](R/W) Reads atdata_s[15] and writes atdata_m[15]. */
        uint32_t atdata7               : 1;  /**< [  1:  1](R/W) Reads atdata_s[7] and writes atdata_m[7]. */
        uint32_t atdata0               : 1;  /**< [  0:  0](R/W) Reads atdata_s[0] and writes atdata_m[0]. */
#else /* Word 0 - Little Endian */
        uint32_t atdata0               : 1;  /**< [  0:  0](R/W) Reads atdata_s[0] and writes atdata_m[0]. */
        uint32_t atdata7               : 1;  /**< [  1:  1](R/W) Reads atdata_s[7] and writes atdata_m[7]. */
        uint32_t atdata15              : 1;  /**< [  2:  2](R/W) Reads atdata_s[15] and writes atdata_m[15]. */
        uint32_t atdata23              : 1;  /**< [  3:  3](R/W) Reads atdata_s[23] and writes atdata_m[23]. */
        uint32_t atdata31              : 1;  /**< [  4:  4](R/W) Reads atdata_s[31] and writes atdata_m[31]. */
        uint32_t atdata39              : 1;  /**< [  5:  5](R/W) Reads atdata_s[39] and writes atdata_m[39]. */
        uint32_t atdata47              : 1;  /**< [  6:  6](R/W) Reads atdata_s[47] and writes atdata_m[47]. */
        uint32_t atdata55              : 1;  /**< [  7:  7](R/W) Reads atdata_s[55] and writes atdata_m[55]. */
        uint32_t atdata63              : 1;  /**< [  8:  8](R/W) Reads atdata_s[63] and writes atdata_m[63]. */
        uint32_t atdata71              : 1;  /**< [  9:  9](R/W) Reads atdata_s[71] and writes atdata_m[71]. */
        uint32_t atdata79              : 1;  /**< [ 10: 10](R/W) Reads atdata_s[79] and writes atdata_m[79]. */
        uint32_t atdata87              : 1;  /**< [ 11: 11](R/W) Reads atdata_s[87] and writes atdata_m[87]. */
        uint32_t atdata95              : 1;  /**< [ 12: 12](R/W) Reads atdata_s[95] and writes atdata_m[95]. */
        uint32_t atdata103             : 1;  /**< [ 13: 13](R/W) Reads atdata_s[103] and writes atdata_m[103]. */
        uint32_t atdata111             : 1;  /**< [ 14: 14](R/W) Reads atdata_s[111] and writes atdata_m[111]. */
        uint32_t atdata119             : 1;  /**< [ 15: 15](R/W) Reads atdata_s[119] and writes atdata_m[119]. */
        uint32_t atdata127             : 1;  /**< [ 16: 16](R/W) Reads atdata_s[127] and writes atdata_m[127]. */
        uint32_t sbz_0                 : 15; /**< [ 31: 17](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_itatbdata0_s cn; */
};
typedef union bdk_atbfunnel_mdabx_itatbdata0 bdk_atbfunnel_mdabx_itatbdata0_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBDATA0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_ITATBDATA0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111eec + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_ITATBDATA0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_ITATBDATA0(a) bdk_atbfunnel_mdabx_itatbdata0_t
#define bustype_BDK_ATBFUNNEL_MDABX_ITATBDATA0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_ITATBDATA0(a) "ATBFUNNEL_MDABX_ITATBDATA0"
#define busnum_BDK_ATBFUNNEL_MDABX_ITATBDATA0(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_ITATBDATA0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_itctrl
 *
 * ATBFUNNEL Mdab Itctrl Register
 * The Integration Mode Control register is used to enable topology detection.
 */
union bdk_atbfunnel_mdabx_itctrl
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_itctrl_s
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
    /* struct bdk_atbfunnel_mdabx_itctrl_s cn; */
};
typedef union bdk_atbfunnel_mdabx_itctrl bdk_atbfunnel_mdabx_itctrl_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_ITCTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_ITCTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111f00 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_ITCTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_ITCTRL(a) bdk_atbfunnel_mdabx_itctrl_t
#define bustype_BDK_ATBFUNNEL_MDABX_ITCTRL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_ITCTRL(a) "ATBFUNNEL_MDABX_ITCTRL"
#define busnum_BDK_ATBFUNNEL_MDABX_ITCTRL(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_ITCTRL(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_pidr0
 *
 * ATBFUNNEL Mdab Pidr0 Register
 * The PIDR0 register is part of the set of peripheral identification registers.
 */
union bdk_atbfunnel_mdabx_pidr0
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_pidr0_s
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
    /* struct bdk_atbfunnel_mdabx_pidr0_s cn; */
};
typedef union bdk_atbfunnel_mdabx_pidr0 bdk_atbfunnel_mdabx_pidr0_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fe0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_PIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_PIDR0(a) bdk_atbfunnel_mdabx_pidr0_t
#define bustype_BDK_ATBFUNNEL_MDABX_PIDR0(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_PIDR0(a) "ATBFUNNEL_MDABX_PIDR0"
#define busnum_BDK_ATBFUNNEL_MDABX_PIDR0(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_PIDR0(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_pidr1
 *
 * ATBFUNNEL Mdab Pidr1 Register
 * The PIDR1 register is part of the set of peripheral identification registers.
 */
union bdk_atbfunnel_mdabx_pidr1
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_pidr1_s
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
    /* struct bdk_atbfunnel_mdabx_pidr1_s cn; */
};
typedef union bdk_atbfunnel_mdabx_pidr1 bdk_atbfunnel_mdabx_pidr1_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fe4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_PIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_PIDR1(a) bdk_atbfunnel_mdabx_pidr1_t
#define bustype_BDK_ATBFUNNEL_MDABX_PIDR1(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_PIDR1(a) "ATBFUNNEL_MDABX_PIDR1"
#define busnum_BDK_ATBFUNNEL_MDABX_PIDR1(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_PIDR1(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_pidr2
 *
 * ATBFUNNEL Mdab Pidr2 Register
 * The PIDR2 register is part of the set of peripheral identification registers.
 */
union bdk_atbfunnel_mdabx_pidr2
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_pidr2_s
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
    /* struct bdk_atbfunnel_mdabx_pidr2_s cn; */
};
typedef union bdk_atbfunnel_mdabx_pidr2 bdk_atbfunnel_mdabx_pidr2_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fe8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_PIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_PIDR2(a) bdk_atbfunnel_mdabx_pidr2_t
#define bustype_BDK_ATBFUNNEL_MDABX_PIDR2(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_PIDR2(a) "ATBFUNNEL_MDABX_PIDR2"
#define busnum_BDK_ATBFUNNEL_MDABX_PIDR2(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_PIDR2(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_pidr3
 *
 * ATBFUNNEL Mdab Pidr3 Register
 * The PIDR3 register is part of the set of peripheral identification registers.
 */
union bdk_atbfunnel_mdabx_pidr3
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_pidr3_s
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
    /* struct bdk_atbfunnel_mdabx_pidr3_s cn; */
};
typedef union bdk_atbfunnel_mdabx_pidr3 bdk_atbfunnel_mdabx_pidr3_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fec + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_PIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_PIDR3(a) bdk_atbfunnel_mdabx_pidr3_t
#define bustype_BDK_ATBFUNNEL_MDABX_PIDR3(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_PIDR3(a) "ATBFUNNEL_MDABX_PIDR3"
#define busnum_BDK_ATBFUNNEL_MDABX_PIDR3(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_PIDR3(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_pidr4
 *
 * ATBFUNNEL Mdab Pidr4 Register
 * The PIDR4 register is part of the set of peripheral identification registers.
 */
union bdk_atbfunnel_mdabx_pidr4
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_pidr4_s
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
    /* struct bdk_atbfunnel_mdabx_pidr4_s cn; */
};
typedef union bdk_atbfunnel_mdabx_pidr4 bdk_atbfunnel_mdabx_pidr4_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fd0 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_PIDR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_PIDR4(a) bdk_atbfunnel_mdabx_pidr4_t
#define bustype_BDK_ATBFUNNEL_MDABX_PIDR4(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_PIDR4(a) "ATBFUNNEL_MDABX_PIDR4"
#define busnum_BDK_ATBFUNNEL_MDABX_PIDR4(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_PIDR4(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_pidr5
 *
 * ATBFUNNEL Mdab Pidr5 Register
 * The PIDR5 register is part of the set of peripheral identification registers.
 */
union bdk_atbfunnel_mdabx_pidr5
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_pidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr5                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr5                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_pidr5_s cn; */
};
typedef union bdk_atbfunnel_mdabx_pidr5 bdk_atbfunnel_mdabx_pidr5_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fd4 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_PIDR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_PIDR5(a) bdk_atbfunnel_mdabx_pidr5_t
#define bustype_BDK_ATBFUNNEL_MDABX_PIDR5(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_PIDR5(a) "ATBFUNNEL_MDABX_PIDR5"
#define busnum_BDK_ATBFUNNEL_MDABX_PIDR5(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_PIDR5(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_pidr6
 *
 * ATBFUNNEL Mdab Pidr6 Register
 * The PIDR6 register is part of the set of peripheral identification registers.
 */
union bdk_atbfunnel_mdabx_pidr6
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_pidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr6                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr6                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_pidr6_s cn; */
};
typedef union bdk_atbfunnel_mdabx_pidr6 bdk_atbfunnel_mdabx_pidr6_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fd8 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_PIDR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_PIDR6(a) bdk_atbfunnel_mdabx_pidr6_t
#define bustype_BDK_ATBFUNNEL_MDABX_PIDR6(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_PIDR6(a) "ATBFUNNEL_MDABX_PIDR6"
#define busnum_BDK_ATBFUNNEL_MDABX_PIDR6(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_PIDR6(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_pidr7
 *
 * ATBFUNNEL Mdab Pidr7 Register
 * The PIDR7 register is part of the set of peripheral identification registers.
 */
union bdk_atbfunnel_mdabx_pidr7
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_pidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
        uint32_t pidr7                 : 8;  /**< [  7:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t pidr7                 : 8;  /**< [  7:  0](RO) Reserved. */
        uint32_t res0_0                : 24; /**< [ 31:  8](RO) Reserved bit or field with Should-Be-Zero-or-Preserved (SBZP) behavior. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_pidr7_s cn; */
};
typedef union bdk_atbfunnel_mdabx_pidr7 bdk_atbfunnel_mdabx_pidr7_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_PIDR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111fdc + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_PIDR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_PIDR7(a) bdk_atbfunnel_mdabx_pidr7_t
#define bustype_BDK_ATBFUNNEL_MDABX_PIDR7(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_PIDR7(a) "ATBFUNNEL_MDABX_PIDR7"
#define busnum_BDK_ATBFUNNEL_MDABX_PIDR7(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_PIDR7(a) (a),-1,-1,-1

/**
 * Register (RSL32b) atbfunnel_mdab#_prioritycontrol
 *
 * ATBFUNNEL Mdab Prioritycontrol Register
 * The Priority Control register is for setting the priority of each port of the
 * funnel. It is a requirement of the programming software that the ports are all
 * disabled before the priority control register contents are changed. Changing the
 * port priorities in real time is not supported. If the priority control register is
 * written when one or more of the ports are enabled, then the write is silently
 * rejected and the value in the priority control register remains unchanged. The lower
 * the priority value, the higher is its priority when selecting the next port to be
 * serviced. If two or more ports have the same priority value, then the lowest
 * numbered port is serviced first.
 */
union bdk_atbfunnel_mdabx_prioritycontrol
{
    uint32_t u;
    struct bdk_atbfunnel_mdabx_prioritycontrol_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t sbz_0                 : 8;  /**< [ 31: 24](R/W) Software should write the field as all 0s. */
        uint32_t priport7              : 3;  /**< [ 23: 21](R/W) Priority value for port 7 */
        uint32_t priport6              : 3;  /**< [ 20: 18](R/W) Priority value for port 6 */
        uint32_t priport5              : 3;  /**< [ 17: 15](R/W) Priority value for port 5 */
        uint32_t priport4              : 3;  /**< [ 14: 12](R/W) Priority value for port 4 */
        uint32_t priport3              : 3;  /**< [ 11:  9](R/W) Priority value for port 3 */
        uint32_t priport2              : 3;  /**< [  8:  6](R/W) Priority value for port 2 */
        uint32_t priport1              : 3;  /**< [  5:  3](R/W) Priority value for port 1 */
        uint32_t priport0              : 3;  /**< [  2:  0](R/W) Priority value for port 0 */
#else /* Word 0 - Little Endian */
        uint32_t priport0              : 3;  /**< [  2:  0](R/W) Priority value for port 0 */
        uint32_t priport1              : 3;  /**< [  5:  3](R/W) Priority value for port 1 */
        uint32_t priport2              : 3;  /**< [  8:  6](R/W) Priority value for port 2 */
        uint32_t priport3              : 3;  /**< [ 11:  9](R/W) Priority value for port 3 */
        uint32_t priport4              : 3;  /**< [ 14: 12](R/W) Priority value for port 4 */
        uint32_t priport5              : 3;  /**< [ 17: 15](R/W) Priority value for port 5 */
        uint32_t priport6              : 3;  /**< [ 20: 18](R/W) Priority value for port 6 */
        uint32_t priport7              : 3;  /**< [ 23: 21](R/W) Priority value for port 7 */
        uint32_t sbz_0                 : 8;  /**< [ 31: 24](R/W) Software should write the field as all 0s. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_atbfunnel_mdabx_prioritycontrol_s cn; */
};
typedef union bdk_atbfunnel_mdabx_prioritycontrol bdk_atbfunnel_mdabx_prioritycontrol_t;

static inline uint64_t BDK_ATBFUNNEL_MDABX_PRIORITYCONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ATBFUNNEL_MDABX_PRIORITYCONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=15))
        return 0x87e046111004 + ((a>>2)*0x100000+(a&0x3)*0x10000);
    __bdk_csr_fatal("ATBFUNNEL_MDABX_PRIORITYCONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ATBFUNNEL_MDABX_PRIORITYCONTROL(a) bdk_atbfunnel_mdabx_prioritycontrol_t
#define bustype_BDK_ATBFUNNEL_MDABX_PRIORITYCONTROL(a) BDK_CSR_TYPE_RSL32b
#define basename_BDK_ATBFUNNEL_MDABX_PRIORITYCONTROL(a) "ATBFUNNEL_MDABX_PRIORITYCONTROL"
#define busnum_BDK_ATBFUNNEL_MDABX_PRIORITYCONTROL(a) (a)
#define arguments_BDK_ATBFUNNEL_MDABX_PRIORITYCONTROL(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_ATBFUNNEL_MDAB_H__ */
