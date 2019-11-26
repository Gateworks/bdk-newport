#ifndef __BDK_CSRS_DAB_ETR_H__
#define __BDK_CSRS_DAB_ETR_H__
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
 * OcteonTX DAB_ETR.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Register (DAB32b) etr#_authstatus
 *
 * ETR Authentication Status Register
 * ETR authentication status register for ap core.
 * Read only register
 */
union bdk_etrx_authstatus
{
    uint32_t u;
    struct bdk_etrx_authstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t snid                  : 2;  /**< [  7:  6](RAZ) Secure non-invasive debug.
                                                                 Possible values of this field are:
                                                                   0x0 = Not implemented. EL3 is not implemented and the processor is nonsecure.
                                                                   0x2 = Implemented and disabled. ExternalSecureNoninvasiveDebugEnabled() == FALSE.
                                                                   0x3 = Implemented and enabled. ExternalSecureNoninvasiveDebugEnabled() == TRUE.
                                                                   _ Other values are reserved.

                                                                 Internal:
                                                                 RTL: SNID[1]=1, SNID[0]=(SPIDEN || SPNIDEN) && (NIDEN || DBGEN). */
        uint32_t sid                   : 2;  /**< [  5:  4](RO) Secure invasive debug.
                                                                 Possible values of this field are:
                                                                   0x0 = Not implemented. EL3 is not implemented and the processor is nonsecure.
                                                                   0x2 = Implemented and disabled. ExternalSecureInvasiveDebugEnabled() == FALSE.
                                                                   0x3 = Implemented and enabled. ExternalSecureInvasiveDebugEnabled() == TRUE.
                                                                   _ Other values are reserved.  For CNXXXX allowed values are 0x2 and 0x3.

                                                                 Internal:
                                                                 RTL: SID[1]=1, SID[0]=(SPIDEN || DBGEN). */
        uint32_t nsnid                 : 2;  /**< [  3:  2](RAZ) Nonsecure non-invasive debug.
                                                                 Possible values of this field are:
                                                                   0x0 = Not implemented. EL3 is not implemented and the processor is secure.
                                                                   0x2 = Implemented and disabled. ExternalNoninvasiveDebugEnabled() == FALSE.
                                                                   0x3 = Implemented and enabled. ExternalNoninvasiveDebugEnabled() == TRUE.
                                                                   _ Other values are reserved.

                                                                 Internal:
                                                                 RTL: NSNID[1]=1, NSNID[0]=(NIDEN || DBGEN). */
        uint32_t nsid                  : 2;  /**< [  1:  0](RAZ) Nonsecure invasive debug.
                                                                 Possible values of this field are:
                                                                   0x0 = Not implemented. EL3 is not implemented and the processor is secure.
                                                                   0x2 = Implemented and disabled. ExternalInvasiveDebugEnabled() == FALSE.
                                                                   0x3 = Implemented and enabled. ExternalInvasiveDebugEnabled() == TRUE.
                                                                   _ Other values are reserved.

                                                                 Internal:
                                                                 RTL: NSID[1]=1, NSID[0]= DBGEN. */
#else /* Word 0 - Little Endian */
        uint32_t nsid                  : 2;  /**< [  1:  0](RAZ) Nonsecure invasive debug.
                                                                 Possible values of this field are:
                                                                   0x0 = Not implemented. EL3 is not implemented and the processor is secure.
                                                                   0x2 = Implemented and disabled. ExternalInvasiveDebugEnabled() == FALSE.
                                                                   0x3 = Implemented and enabled. ExternalInvasiveDebugEnabled() == TRUE.
                                                                   _ Other values are reserved.

                                                                 Internal:
                                                                 RTL: NSID[1]=1, NSID[0]= DBGEN. */
        uint32_t nsnid                 : 2;  /**< [  3:  2](RAZ) Nonsecure non-invasive debug.
                                                                 Possible values of this field are:
                                                                   0x0 = Not implemented. EL3 is not implemented and the processor is secure.
                                                                   0x2 = Implemented and disabled. ExternalNoninvasiveDebugEnabled() == FALSE.
                                                                   0x3 = Implemented and enabled. ExternalNoninvasiveDebugEnabled() == TRUE.
                                                                   _ Other values are reserved.

                                                                 Internal:
                                                                 RTL: NSNID[1]=1, NSNID[0]=(NIDEN || DBGEN). */
        uint32_t sid                   : 2;  /**< [  5:  4](RO) Secure invasive debug.
                                                                 Possible values of this field are:
                                                                   0x0 = Not implemented. EL3 is not implemented and the processor is nonsecure.
                                                                   0x2 = Implemented and disabled. ExternalSecureInvasiveDebugEnabled() == FALSE.
                                                                   0x3 = Implemented and enabled. ExternalSecureInvasiveDebugEnabled() == TRUE.
                                                                   _ Other values are reserved.  For CNXXXX allowed values are 0x2 and 0x3.

                                                                 Internal:
                                                                 RTL: SID[1]=1, SID[0]=(SPIDEN || DBGEN). */
        uint32_t snid                  : 2;  /**< [  7:  6](RAZ) Secure non-invasive debug.
                                                                 Possible values of this field are:
                                                                   0x0 = Not implemented. EL3 is not implemented and the processor is nonsecure.
                                                                   0x2 = Implemented and disabled. ExternalSecureNoninvasiveDebugEnabled() == FALSE.
                                                                   0x3 = Implemented and enabled. ExternalSecureNoninvasiveDebugEnabled() == TRUE.
                                                                   _ Other values are reserved.

                                                                 Internal:
                                                                 RTL: SNID[1]=1, SNID[0]=(SPIDEN || SPNIDEN) && (NIDEN || DBGEN). */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_authstatus_s cn; */
};
typedef union bdk_etrx_authstatus bdk_etrx_authstatus_t;

static inline uint64_t BDK_ETRX_AUTHSTATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_AUTHSTATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fb8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fb8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fb8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fb8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_AUTHSTATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_AUTHSTATUS(a) bdk_etrx_authstatus_t
#define bustype_BDK_ETRX_AUTHSTATUS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_AUTHSTATUS(a) "ETRX_AUTHSTATUS"
#define busnum_BDK_ETRX_AUTHSTATUS(a) (a)
#define arguments_BDK_ETRX_AUTHSTATUS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_busctl
 *
 * ETR AXI Master Bus Control Register
 * The ETR hardware generated write path is fixed. That is, the RTL will always write
 * 8B words to a buffer located in secure physical address space, as determined by writing
 * to ETR_DBA, ETR_WTRPOINTER, and ETR_WTRPOINTERHI.  Hardware ignores all cache/memory
 * attributes.
 */
union bdk_etrx_busctl
{
    uint32_t u;
    struct bdk_etrx_busctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t battr7to4             : 4;  /**< [ 19: 16](R/W) BAttr[7:4], together with BAttr[3:0] specify memory type. Hardware ignores this field. */
        uint32_t reserved_12_15        : 4;
        uint32_t wrburstlen            : 4;  /**< [ 11:  8](R/W) Write Burst Length. Hardware always writes 8B words. */
        uint32_t reserved_6_7          : 2;
        uint32_t battr3to0             : 4;  /**< [  5:  2](R/W) BAttr[3:0], together with BAttr[7:4] specify memory type. Hardware ignores this field. */
        uint32_t nsec                  : 1;  /**< [  1:  1](R/W) Secure memory attribute. */
        uint32_t privileged            : 1;  /**< [  0:  0](RO) Privileged memory attribute. Hardware ignores this field. */
#else /* Word 0 - Little Endian */
        uint32_t privileged            : 1;  /**< [  0:  0](RO) Privileged memory attribute. Hardware ignores this field. */
        uint32_t nsec                  : 1;  /**< [  1:  1](R/W) Secure memory attribute. */
        uint32_t battr3to0             : 4;  /**< [  5:  2](R/W) BAttr[3:0], together with BAttr[7:4] specify memory type. Hardware ignores this field. */
        uint32_t reserved_6_7          : 2;
        uint32_t wrburstlen            : 4;  /**< [ 11:  8](R/W) Write Burst Length. Hardware always writes 8B words. */
        uint32_t reserved_12_15        : 4;
        uint32_t battr7to4             : 4;  /**< [ 19: 16](R/W) BAttr[7:4], together with BAttr[3:0] specify memory type. Hardware ignores this field. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_busctl_s cn; */
};
typedef union bdk_etrx_busctl bdk_etrx_busctl_t;

static inline uint64_t BDK_ETRX_BUSCTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_BUSCTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040110ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040110ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040110ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040110ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_BUSCTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_BUSCTL(a) bdk_etrx_busctl_t
#define bustype_BDK_ETRX_BUSCTL(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_BUSCTL(a) "ETRX_BUSCTL"
#define busnum_BDK_ETRX_BUSCTL(a) (a)
#define arguments_BDK_ETRX_BUSCTL(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_cidr0
 *
 * ETR Component Identification Register 0
 * This register provides information to identify a debug component.
 */
union bdk_etrx_cidr0
{
    uint32_t u;
    struct bdk_etrx_cidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_0               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_cidr0_s cn; */
};
typedef union bdk_etrx_cidr0 bdk_etrx_cidr0_t;

static inline uint64_t BDK_ETRX_CIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_CIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040ff0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040ff0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040ff0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040ff0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_CIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_CIDR0(a) bdk_etrx_cidr0_t
#define bustype_BDK_ETRX_CIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_CIDR0(a) "ETRX_CIDR0"
#define busnum_BDK_ETRX_CIDR0(a) (a)
#define arguments_BDK_ETRX_CIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_cidr1
 *
 * ETR Component Identification Register 1
 * This register provides information to identify a debug component.
 */
union bdk_etrx_cidr1
{
    uint32_t u;
    struct bdk_etrx_cidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0x9 = CoreSight component. */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_1               : 4;  /**< [  3:  0](RO) Preamble identification value. */
        uint32_t cclass                : 4;  /**< [  7:  4](RO) Component class. 0x9 = CoreSight component. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_cidr1_s cn; */
};
typedef union bdk_etrx_cidr1 bdk_etrx_cidr1_t;

static inline uint64_t BDK_ETRX_CIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_CIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040ff4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040ff4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040ff4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040ff4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_CIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_CIDR1(a) bdk_etrx_cidr1_t
#define bustype_BDK_ETRX_CIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_CIDR1(a) "ETRX_CIDR1"
#define busnum_BDK_ETRX_CIDR1(a) (a)
#define arguments_BDK_ETRX_CIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_cidr2
 *
 * ETR Component Identification Register 2
 * This register provides information to identify a debug component.
 */
union bdk_etrx_cidr2
{
    uint32_t u;
    struct bdk_etrx_cidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_2               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_cidr2_s cn; */
};
typedef union bdk_etrx_cidr2 bdk_etrx_cidr2_t;

static inline uint64_t BDK_ETRX_CIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_CIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040ff8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040ff8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040ff8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040ff8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_CIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_CIDR2(a) bdk_etrx_cidr2_t
#define bustype_BDK_ETRX_CIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_CIDR2(a) "ETRX_CIDR2"
#define busnum_BDK_ETRX_CIDR2(a) (a)
#define arguments_BDK_ETRX_CIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_cidr3
 *
 * ETR Component Identification Register 3
 * This register provides information to identify a debug component.
 */
union bdk_etrx_cidr3
{
    uint32_t u;
    struct bdk_etrx_cidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
#else /* Word 0 - Little Endian */
        uint32_t prmbl_3               : 8;  /**< [  7:  0](RO) Preamble identification value. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_cidr3_s cn; */
};
typedef union bdk_etrx_cidr3 bdk_etrx_cidr3_t;

static inline uint64_t BDK_ETRX_CIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_CIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040ffcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040ffcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040ffcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040ffcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_CIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_CIDR3(a) bdk_etrx_cidr3_t
#define bustype_BDK_ETRX_CIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_CIDR3(a) "ETRX_CIDR3"
#define busnum_BDK_ETRX_CIDR3(a) (a)
#define arguments_BDK_ETRX_CIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_claimclr
 *
 * ETR Claim Tag Clear Register
 * Software can use this to:
 *   1. Clear bits in the claim tag to zero.
 *   2. Read the value of the claim tag.
 */
union bdk_etrx_claimclr
{
    uint32_t u;
    struct bdk_etrx_claimclr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t clr                   : 8;  /**< [  7:  0](R/W1C) When a write to one of these bits occurs, with the value:
                                                                   0 = The register ignores the write.
                                                                   1 = If the bit is supported then it is set to zero.
                                                                      A single write operation can set multiple bits to zero.

                                                                 A Read returns the value of the claim tag. */
#else /* Word 0 - Little Endian */
        uint32_t clr                   : 8;  /**< [  7:  0](R/W1C) When a write to one of these bits occurs, with the value:
                                                                   0 = The register ignores the write.
                                                                   1 = If the bit is supported then it is set to zero.
                                                                      A single write operation can set multiple bits to zero.

                                                                 A Read returns the value of the claim tag. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_claimclr_s cn; */
};
typedef union bdk_etrx_claimclr bdk_etrx_claimclr_t;

static inline uint64_t BDK_ETRX_CLAIMCLR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_CLAIMCLR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fa4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fa4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fa4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fa4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_CLAIMCLR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_CLAIMCLR(a) bdk_etrx_claimclr_t
#define bustype_BDK_ETRX_CLAIMCLR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_CLAIMCLR(a) "ETRX_CLAIMCLR"
#define busnum_BDK_ETRX_CLAIMCLR(a) (a)
#define arguments_BDK_ETRX_CLAIMCLR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_control
 *
 * ETR Control Register
 * Controls trace stream capture.
 */
union bdk_etrx_control
{
    uint32_t u;
    struct bdk_etrx_control_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t tracecapten           : 1;  /**< [  0:  0](R/W) Controls trace capture event */
#else /* Word 0 - Little Endian */
        uint32_t tracecapten           : 1;  /**< [  0:  0](R/W) Controls trace capture event */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_control_s cn; */
};
typedef union bdk_etrx_control bdk_etrx_control_t;

static inline uint64_t BDK_ETRX_CONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_CONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040020ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040020ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040020ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040020ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_CONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_CONTROL(a) bdk_etrx_control_t
#define bustype_BDK_ETRX_CONTROL(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_CONTROL(a) "ETRX_CONTROL"
#define busnum_BDK_ETRX_CONTROL(a) (a)
#define arguments_BDK_ETRX_CONTROL(a) (a),-1,-1,-1

/**
 * Register (DAB) etr#_dba
 *
 * ETR Data Buffer Address Register
 * This register enable the TMC to locate
 * the trace buffer in system memory.
 */
union bdk_etrx_dba
{
    uint64_t u;
    struct bdk_etrx_dba_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t address               : 64; /**< [ 63:  0](R/W) This register enable the TMC to locate
                                                                 the trace buffer in system memory. */
#else /* Word 0 - Little Endian */
        uint64_t address               : 64; /**< [ 63:  0](R/W) This register enable the TMC to locate
                                                                 the trace buffer in system memory. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_dba_s cn; */
};
typedef union bdk_etrx_dba bdk_etrx_dba_t;

static inline uint64_t BDK_ETRX_DBA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_DBA(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040118ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040118ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040118ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040118ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_DBA", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_DBA(a) bdk_etrx_dba_t
#define bustype_BDK_ETRX_DBA(a) BDK_CSR_TYPE_DAB
#define basename_BDK_ETRX_DBA(a) "ETRX_DBA"
#define busnum_BDK_ETRX_DBA(a) (a)
#define arguments_BDK_ETRX_DBA(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_devarch
 *
 * ETR External Debug Device Architecture Register
 * Identifies the programmers' model architecture of the external
 *     ETR component.
 */
union bdk_etrx_devarch
{
    uint32_t u;
    struct bdk_etrx_devarch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. For debug, this is
                                                                     ARM Limited.
                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.
                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by ARM this is the minor revision.
                                                                 For debug, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by ARM this is further subdivided.
                                                                 For debug:
                                                                  Bits [15:12] are the architecture version, 0x8, v8.2.
                                                                  Bits [11:0] are the architecture part number, 0xA15. */
#else /* Word 0 - Little Endian */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by ARM this is further subdivided.
                                                                 For debug:
                                                                  Bits [15:12] are the architecture version, 0x8, v8.2.
                                                                  Bits [11:0] are the architecture part number, 0xA15. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by ARM this is the minor revision.
                                                                 For debug, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. For debug, this is
                                                                     ARM Limited.
                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.
                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_devarch_s cn9; */
    /* struct bdk_etrx_devarch_s cn96xxp1; */
    struct bdk_etrx_devarch_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. For debug, this is
                                                                     Arm Limited.
                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.
                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by Arm this is the minor revision.
                                                                 For debug, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by Arm this is further subdivided.
                                                                 For debug:
                                                                  Bits [15:12] are the architecture version, 0x8, v8.2.
                                                                  Bits [11:0] are the architecture part number, 0xA15. */
#else /* Word 0 - Little Endian */
        uint32_t archid                : 16; /**< [ 15:  0](RO) Defines this part to be a v8-A debug component. For
                                                                     architectures defined by Arm this is further subdivided.
                                                                 For debug:
                                                                  Bits [15:12] are the architecture version, 0x8, v8.2.
                                                                  Bits [11:0] are the architecture part number, 0xA15. */
        uint32_t revision              : 4;  /**< [ 19: 16](RO) Defines the architecture revision. For architectures defined
                                                                     by Arm this is the minor revision.
                                                                 For debug, the revision defined by v8-A is 0x0.
                                                                 All other values are reserved. */
        uint32_t present               : 1;  /**< [ 20: 20](RO) When set to one, indicates that the DEVARCH is present.
                                                                 This field is 1 in v8-A. */
        uint32_t architect             : 11; /**< [ 31: 21](RO) Defines the architecture of the component. For debug, this is
                                                                     Arm Limited.
                                                                 Bits [31:28] are the JEP 106 continuation code, 0x4.
                                                                 Bits [27:21] are the JEP 106 ID code, 0x3B. */
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_etrx_devarch_cn96xxp3 cn98xx; */
    /* struct bdk_etrx_devarch_cn96xxp3 cnf95xx; */
    /* struct bdk_etrx_devarch_cn96xxp3 loki; */
};
typedef union bdk_etrx_devarch bdk_etrx_devarch_t;

static inline uint64_t BDK_ETRX_DEVARCH(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_DEVARCH(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fbcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fbcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fbcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fbcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_DEVARCH", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_DEVARCH(a) bdk_etrx_devarch_t
#define bustype_BDK_ETRX_DEVARCH(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_DEVARCH(a) "ETRX_DEVARCH"
#define busnum_BDK_ETRX_DEVARCH(a) (a)
#define arguments_BDK_ETRX_DEVARCH(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_devid
 *
 * ETR Device Configuration Register
 * This register provides CoreSight discovery information.
 */
union bdk_etrx_devid
{
    uint32_t u;
    struct bdk_etrx_devid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t irq                   : 2;  /**< [ 31: 30](RO) Defines the interrupt controls.
                                                                   0x0 = No interrupts implemented.
                                                                   0x1 = Wired interrupts implemented.
                                                                   0x2 = Message-signaled interrupts implemented. */
        uint32_t cachetype             : 2;  /**< [ 29: 28](RO) Defines the format of the BUSCTL bus control fields.
                                                                   0x0 = ETR()_BUSCTL[SSH, SORGN, SIRGN, BSH] are not implemented.
                                                                   0x1 = ETR()_BUSCTL[SSH, SORGN, SIRGN, BSH, BATTR] implementation defined non-generic
                                                                 format.
                                                                   0x2 = ETR()_BUSCTL[SSH, SORGN, SIRGN, BSH, BATTR] generic format with only outer
                                                                 attributes.
                                                                   0x3 = ETR()_BUSCTL[SSH, SORGN, SIRGN, BSH, BATTR] generic format with separate inner and
                                                                 outer
                                                                 attributes. */
        uint32_t modes                 : 3;  /**< [ 27: 25](RO) Implemented modes. Indicates which modes, and associated registers, are implemented.
                                                                 The defined values of this field are:
                                                                   0x0 = Circular Buffer and Software Read FIFO mode implemented. The RRP, RRD, LBUFLEVEL,
                                                                   _     CBUFLEVEL and BUFWM registers are all implemented.
                                                                   0x2 = Circular Buffer mode only. The RRP, RRD, LBUFLEVEL, CBUFLEVEL and BUFWM registers
                                                                   _     are not implemented.
                                                                   All other values are reserved. */
        uint32_t noscat                : 1;  /**< [ 24: 24](RO) Scatter mode. Indicates whether Scatter mode is supported.
                                                                   0 = Scatter mode is implemented.
                                                                   1 = Scatter mode is not implemented. */
        uint32_t aw                    : 7;  /**< [ 23: 17](RO) Defines the address bus width.
                                                                 The defined values of this field are:
                                                                   0x00 = Configured as a streaming device.
                                                                   0x20 = 32-bit bus.
                                                                   0x28 = 40-bit bus.
                                                                   0x2C = 44-bit bus.
                                                                   0x30 = 48-bit bus.
                                                                   0x34 = 52-bit bus. */
        uint32_t awvalid               : 1;  /**< [ 16: 16](RO) Indicates [AW] contains a meaningful value. */
        uint32_t reserved_15           : 1;
        uint32_t exmemwidth            : 1;  /**< [ 14: 14](RO) Together with bits \<10:8\> defines the required alignment of registers.
                                                                 The defined values of this field DEVID\<15:14, 10:8\> are:
                                                                   0x01 = Registers must be 16-bit(2 bytes) aligned.
                                                                   0x02 = Registers must be 32-bit(4 bytes) aligned.
                                                                   0x03 = Registers must be 64-bit(8 bytes) aligned.
                                                                   0x04 = Registers must be 16-byte aligned.
                                                                      ...........
                                                                   0x0B = Registers must be 2048-byte aligned. */
        uint32_t wbufdepth             : 3;  /**< [ 13: 11](RO) This values indicates, in power of two, the number of entries in the write buffer.
                                                                 Each entry is of size ATB_DATA_WIDTH.
                                                                   0x0 = Implementation defined.
                                                                   0x2 = Depth of write buffer is 4 entries.
                                                                   0x3 = Depth of write buffer is 8 entries.
                                                                   0x4 = Depth of write buffer is 16 entries.
                                                                   0x5 = Depth of write buffer is 32 entries. */
        uint32_t memwidth              : 3;  /**< [ 10:  8](RO) See [EXMEMWIDTH]. */
        uint32_t configtype            : 2;  /**< [  7:  6](RO) This value indicates TMC configuration types.
                                                                   0x0 = ETB.
                                                                   0x1 = ETR.
                                                                   0x2 = ETF. */
        uint32_t clkscheme             : 1;  /**< [  5:  5](RO) Reserved. */
        uint32_t atbinportcount        : 5;  /**< [  4:  0](RO) Reserved. */
#else /* Word 0 - Little Endian */
        uint32_t atbinportcount        : 5;  /**< [  4:  0](RO) Reserved. */
        uint32_t clkscheme             : 1;  /**< [  5:  5](RO) Reserved. */
        uint32_t configtype            : 2;  /**< [  7:  6](RO) This value indicates TMC configuration types.
                                                                   0x0 = ETB.
                                                                   0x1 = ETR.
                                                                   0x2 = ETF. */
        uint32_t memwidth              : 3;  /**< [ 10:  8](RO) See [EXMEMWIDTH]. */
        uint32_t wbufdepth             : 3;  /**< [ 13: 11](RO) This values indicates, in power of two, the number of entries in the write buffer.
                                                                 Each entry is of size ATB_DATA_WIDTH.
                                                                   0x0 = Implementation defined.
                                                                   0x2 = Depth of write buffer is 4 entries.
                                                                   0x3 = Depth of write buffer is 8 entries.
                                                                   0x4 = Depth of write buffer is 16 entries.
                                                                   0x5 = Depth of write buffer is 32 entries. */
        uint32_t exmemwidth            : 1;  /**< [ 14: 14](RO) Together with bits \<10:8\> defines the required alignment of registers.
                                                                 The defined values of this field DEVID\<15:14, 10:8\> are:
                                                                   0x01 = Registers must be 16-bit(2 bytes) aligned.
                                                                   0x02 = Registers must be 32-bit(4 bytes) aligned.
                                                                   0x03 = Registers must be 64-bit(8 bytes) aligned.
                                                                   0x04 = Registers must be 16-byte aligned.
                                                                      ...........
                                                                   0x0B = Registers must be 2048-byte aligned. */
        uint32_t reserved_15           : 1;
        uint32_t awvalid               : 1;  /**< [ 16: 16](RO) Indicates [AW] contains a meaningful value. */
        uint32_t aw                    : 7;  /**< [ 23: 17](RO) Defines the address bus width.
                                                                 The defined values of this field are:
                                                                   0x00 = Configured as a streaming device.
                                                                   0x20 = 32-bit bus.
                                                                   0x28 = 40-bit bus.
                                                                   0x2C = 44-bit bus.
                                                                   0x30 = 48-bit bus.
                                                                   0x34 = 52-bit bus. */
        uint32_t noscat                : 1;  /**< [ 24: 24](RO) Scatter mode. Indicates whether Scatter mode is supported.
                                                                   0 = Scatter mode is implemented.
                                                                   1 = Scatter mode is not implemented. */
        uint32_t modes                 : 3;  /**< [ 27: 25](RO) Implemented modes. Indicates which modes, and associated registers, are implemented.
                                                                 The defined values of this field are:
                                                                   0x0 = Circular Buffer and Software Read FIFO mode implemented. The RRP, RRD, LBUFLEVEL,
                                                                   _     CBUFLEVEL and BUFWM registers are all implemented.
                                                                   0x2 = Circular Buffer mode only. The RRP, RRD, LBUFLEVEL, CBUFLEVEL and BUFWM registers
                                                                   _     are not implemented.
                                                                   All other values are reserved. */
        uint32_t cachetype             : 2;  /**< [ 29: 28](RO) Defines the format of the BUSCTL bus control fields.
                                                                   0x0 = ETR()_BUSCTL[SSH, SORGN, SIRGN, BSH] are not implemented.
                                                                   0x1 = ETR()_BUSCTL[SSH, SORGN, SIRGN, BSH, BATTR] implementation defined non-generic
                                                                 format.
                                                                   0x2 = ETR()_BUSCTL[SSH, SORGN, SIRGN, BSH, BATTR] generic format with only outer
                                                                 attributes.
                                                                   0x3 = ETR()_BUSCTL[SSH, SORGN, SIRGN, BSH, BATTR] generic format with separate inner and
                                                                 outer
                                                                 attributes. */
        uint32_t irq                   : 2;  /**< [ 31: 30](RO) Defines the interrupt controls.
                                                                   0x0 = No interrupts implemented.
                                                                   0x1 = Wired interrupts implemented.
                                                                   0x2 = Message-signaled interrupts implemented. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_devid_s cn; */
};
typedef union bdk_etrx_devid bdk_etrx_devid_t;

static inline uint64_t BDK_ETRX_DEVID(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_DEVID(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fc8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fc8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fc8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fc8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_DEVID", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_DEVID(a) bdk_etrx_devid_t
#define bustype_BDK_ETRX_DEVID(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_DEVID(a) "ETRX_DEVID"
#define busnum_BDK_ETRX_DEVID(a) (a)
#define arguments_BDK_ETRX_DEVID(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_devtype
 *
 * ETR Device Type Register
 * Provides a debugger with information about the component when the part number field
 * is not recognized. The debugger can then report this information.
 */
union bdk_etrx_devtype
{
    uint32_t u;
    struct bdk_etrx_devtype_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Subtype. */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major type. */
#else /* Word 0 - Little Endian */
        uint32_t major                 : 4;  /**< [  3:  0](RO) Major type. */
        uint32_t sub                   : 4;  /**< [  7:  4](RO) Subtype. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_devtype_s cn; */
};
typedef union bdk_etrx_devtype bdk_etrx_devtype_t;

static inline uint64_t BDK_ETRX_DEVTYPE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_DEVTYPE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fccll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fccll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fccll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fccll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_DEVTYPE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_DEVTYPE(a) bdk_etrx_devtype_t
#define bustype_BDK_ETRX_DEVTYPE(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_DEVTYPE(a) "ETRX_DEVTYPE"
#define busnum_BDK_ETRX_DEVTYPE(a) (a)
#define arguments_BDK_ETRX_DEVTYPE(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_ffcr
 *
 * ETR Formatter and Flush Control Register
 * This register provides a control for external multiplexing of additional triggers.
 */
union bdk_etrx_ffcr
{
    uint32_t u;
    struct bdk_etrx_ffcr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t stopontrigevt         : 1;  /**< [ 13: 13](R/W) If this bit is set, the formatter is stopped when a Trigger Event has been observed.

                                                                 0x0 = Trace capture is not stopped when a Trigger Event is observed.
                                                                 0x1 = Trace capture is stopped when a Trigger Event is observed. */
        uint32_t stoponfl              : 1;  /**< [ 12: 12](R/W) If this bit is set, the formatter is stopped on completion of a flush operation.

                                                                 0x0 = Trace capture is not stopped when FLUSH is completed.
                                                                 0x1 = Trace capture is stopped when FLUSH is completed. */
        uint32_t reserved_7_11         : 5;
        uint32_t manflush              : 1;  /**< [  6:  6](R/W) Manually generate a flush of the system. Setting this bit causes a flush to be generated.

                                                                 0x0 = Manual Flush is not initiated.
                                                                 0x1 = Manual Flush is initiated. */
        uint32_t fontrigevt            : 1;  /**< [  5:  5](R/W) Hardware ignores this field. */
        uint32_t fonflin               : 1;  /**< [  4:  4](R/W) Hardware ignores this field. */
        uint32_t reserved_0_3          : 4;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_3          : 4;
        uint32_t fonflin               : 1;  /**< [  4:  4](R/W) Hardware ignores this field. */
        uint32_t fontrigevt            : 1;  /**< [  5:  5](R/W) Hardware ignores this field. */
        uint32_t manflush              : 1;  /**< [  6:  6](R/W) Manually generate a flush of the system. Setting this bit causes a flush to be generated.

                                                                 0x0 = Manual Flush is not initiated.
                                                                 0x1 = Manual Flush is initiated. */
        uint32_t reserved_7_11         : 5;
        uint32_t stoponfl              : 1;  /**< [ 12: 12](R/W) If this bit is set, the formatter is stopped on completion of a flush operation.

                                                                 0x0 = Trace capture is not stopped when FLUSH is completed.
                                                                 0x1 = Trace capture is stopped when FLUSH is completed. */
        uint32_t stopontrigevt         : 1;  /**< [ 13: 13](R/W) If this bit is set, the formatter is stopped when a Trigger Event has been observed.

                                                                 0x0 = Trace capture is not stopped when a Trigger Event is observed.
                                                                 0x1 = Trace capture is stopped when a Trigger Event is observed. */
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_ffcr_s cn; */
};
typedef union bdk_etrx_ffcr bdk_etrx_ffcr_t;

static inline uint64_t BDK_ETRX_FFCR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_FFCR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040304ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040304ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040304ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040304ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_FFCR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_FFCR(a) bdk_etrx_ffcr_t
#define bustype_BDK_ETRX_FFCR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_FFCR(a) "ETRX_FFCR"
#define busnum_BDK_ETRX_FFCR(a) (a)
#define arguments_BDK_ETRX_FFCR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_ffsr
 *
 * ETR Formatter and Flush Status Register
 * This register determines whether events on channels propagate through the
 * CTM to other ECT components, or from the CTM into the ETR.
 */
union bdk_etrx_ffsr
{
    uint32_t u;
    struct bdk_etrx_ffsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t bypassnopad           : 1;  /**< [  5:  5](RO) No padding in bypass. Indicates whether the ETR inserts the stop sequence when
                                                                 trace is disabled and bypass mode is selected. The defined values of this bit are:
                                                                   0x0 = ETR inserts the stop sequence at end of trace in bypass mode.
                                                                   0x1 = ETR does not insert the stop sequence at end of trace in bypass mode. */
        uint32_t ftnotpresent          : 1;  /**< [  4:  4](RO) Formatter not present. Indicates the presence of the formatter. The defined values of this
                                                                 bit are:
                                                                   0x0 = Formatter is implemented.
                                                                   0x1 = Formatter is not implemented. */
        uint32_t ftnonstop             : 1;  /**< [  3:  3](RO) Non-stop. Indicates the trace cannot be stopped.
                                                                 The ETR can always be stopped. */
        uint32_t tcpresent             : 1;  /**< [  2:  2](RO) TRACECTL present. Indicates presence of the TRACECTL pin.
                                                                 The ETR does not include a trace port and so never implements a TRACECTL pin. */
        uint32_t ftstopped             : 1;  /**< [  1:  1](RO) This bit behaves in the same way as the FtEmpty bit in the ETR_STATUS Register.
                                                                 The FtStopped bit is deprecated and is present in this register to support
                                                                 backwards-compatibility with earlier versions of the ETB. */
        uint32_t flinprog              : 1;  /**< [  0:  0](RO) This bit indicates whether the ETR is currently processing a flush operation.

                                                                 The flush initiation is controlled by the flush-control bits in the ETR_FFCR Register.
                                                                 0x0 = No flush activity in progress.
                                                                 0x1 = Flush in progress. */
#else /* Word 0 - Little Endian */
        uint32_t flinprog              : 1;  /**< [  0:  0](RO) This bit indicates whether the ETR is currently processing a flush operation.

                                                                 The flush initiation is controlled by the flush-control bits in the ETR_FFCR Register.
                                                                 0x0 = No flush activity in progress.
                                                                 0x1 = Flush in progress. */
        uint32_t ftstopped             : 1;  /**< [  1:  1](RO) This bit behaves in the same way as the FtEmpty bit in the ETR_STATUS Register.
                                                                 The FtStopped bit is deprecated and is present in this register to support
                                                                 backwards-compatibility with earlier versions of the ETB. */
        uint32_t tcpresent             : 1;  /**< [  2:  2](RO) TRACECTL present. Indicates presence of the TRACECTL pin.
                                                                 The ETR does not include a trace port and so never implements a TRACECTL pin. */
        uint32_t ftnonstop             : 1;  /**< [  3:  3](RO) Non-stop. Indicates the trace cannot be stopped.
                                                                 The ETR can always be stopped. */
        uint32_t ftnotpresent          : 1;  /**< [  4:  4](RO) Formatter not present. Indicates the presence of the formatter. The defined values of this
                                                                 bit are:
                                                                   0x0 = Formatter is implemented.
                                                                   0x1 = Formatter is not implemented. */
        uint32_t bypassnopad           : 1;  /**< [  5:  5](RO) No padding in bypass. Indicates whether the ETR inserts the stop sequence when
                                                                 trace is disabled and bypass mode is selected. The defined values of this bit are:
                                                                   0x0 = ETR inserts the stop sequence at end of trace in bypass mode.
                                                                   0x1 = ETR does not insert the stop sequence at end of trace in bypass mode. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_ffsr_s cn; */
};
typedef union bdk_etrx_ffsr bdk_etrx_ffsr_t;

static inline uint64_t BDK_ETRX_FFSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_FFSR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040300ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040300ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040300ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040300ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_FFSR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_FFSR(a) bdk_etrx_ffsr_t
#define bustype_BDK_ETRX_FFSR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_FFSR(a) "ETRX_FFSR"
#define busnum_BDK_ETRX_FFSR(a) (a)
#define arguments_BDK_ETRX_FFSR(a) (a),-1,-1,-1

/**
 * Register (DAB) etr#_irqcr0
 *
 * ETR Interrupt Configuration Register 0
 */
union bdk_etrx_irqcr0
{
    uint64_t u;
    struct bdk_etrx_irqcr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) Message Signaled Interrupt IOVA. Specifies the address that the node writes to
                                                                 signal an interrupt. */
        uint64_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_1          : 2;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) Message Signaled Interrupt IOVA. Specifies the address that the node writes to
                                                                 signal an interrupt. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_irqcr0_s cn; */
};
typedef union bdk_etrx_irqcr0 bdk_etrx_irqcr0_t;

static inline uint64_t BDK_ETRX_IRQCR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_IRQCR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040e80ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040e80ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040e80ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040e80ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_IRQCR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_IRQCR0(a) bdk_etrx_irqcr0_t
#define bustype_BDK_ETRX_IRQCR0(a) BDK_CSR_TYPE_DAB
#define basename_BDK_ETRX_IRQCR0(a) "ETRX_IRQCR0"
#define busnum_BDK_ETRX_IRQCR0(a) (a)
#define arguments_BDK_ETRX_IRQCR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_irqcr1
 *
 * ETR Interrupt Configuration Register 1
 */
union bdk_etrx_irqcr1
{
    uint32_t u;
    struct bdk_etrx_irqcr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_irqcr1_s cn; */
};
typedef union bdk_etrx_irqcr1 bdk_etrx_irqcr1_t;

static inline uint64_t BDK_ETRX_IRQCR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_IRQCR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040e88ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040e88ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040e88ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040e88ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_IRQCR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_IRQCR1(a) bdk_etrx_irqcr1_t
#define bustype_BDK_ETRX_IRQCR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_IRQCR1(a) "ETRX_IRQCR1"
#define busnum_BDK_ETRX_IRQCR1(a) (a)
#define arguments_BDK_ETRX_IRQCR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_irqcr2
 *
 * ETR Interrupt Configuration Register 2
 */
union bdk_etrx_irqcr2
{
    uint32_t u;
    struct bdk_etrx_irqcr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t msien                 : 1;  /**< [  7:  7](R/W) Message-signaled interrupt enable.
                                                                   0 = Disabled.
                                                                   1 = Enabled. */
        uint32_t nsmsi                 : 1;  /**< [  6:  6](R/W) This bit is an optional extension for secure-only error records.
                                                                 It provides the non-secure attribute for the MSI vector.
                                                                   0 = Secure.
                                                                   1 = Non-secure. */
        uint32_t sh                    : 2;  /**< [  5:  4](RO) Shareability. Defines the shareability domain for message signaled interrupts.
                                                                 This field is RES0 if the ETR does not support configuring the shareability domain.
                                                                   0x0 = Not shared.
                                                                   0x2 = Outer shareable.
                                                                   0x3 = Inner shareable.

                                                                 In CNXXXX, ignored. */
        uint32_t memattr               : 4;  /**< [  3:  0](RO) MSI-X memory attributes. In CNXXXX, ignored.
                                                                 This field is RES0 if the ETR does not support configuring the shareability domain. */
#else /* Word 0 - Little Endian */
        uint32_t memattr               : 4;  /**< [  3:  0](RO) MSI-X memory attributes. In CNXXXX, ignored.
                                                                 This field is RES0 if the ETR does not support configuring the shareability domain. */
        uint32_t sh                    : 2;  /**< [  5:  4](RO) Shareability. Defines the shareability domain for message signaled interrupts.
                                                                 This field is RES0 if the ETR does not support configuring the shareability domain.
                                                                   0x0 = Not shared.
                                                                   0x2 = Outer shareable.
                                                                   0x3 = Inner shareable.

                                                                 In CNXXXX, ignored. */
        uint32_t nsmsi                 : 1;  /**< [  6:  6](R/W) This bit is an optional extension for secure-only error records.
                                                                 It provides the non-secure attribute for the MSI vector.
                                                                   0 = Secure.
                                                                   1 = Non-secure. */
        uint32_t msien                 : 1;  /**< [  7:  7](R/W) Message-signaled interrupt enable.
                                                                   0 = Disabled.
                                                                   1 = Enabled. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_irqcr2_s cn; */
};
typedef union bdk_etrx_irqcr2 bdk_etrx_irqcr2_t;

static inline uint64_t BDK_ETRX_IRQCR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_IRQCR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040e8cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040e8cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040e8cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040e8cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_IRQCR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_IRQCR2(a) bdk_etrx_irqcr2_t
#define bustype_BDK_ETRX_IRQCR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_IRQCR2(a) "ETRX_IRQCR2"
#define busnum_BDK_ETRX_IRQCR2(a) (a)
#define arguments_BDK_ETRX_IRQCR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_itctrl
 *
 * ETR TRC Integration mode Control Register
 * Enables the TRC to switch from its default mode into
 *     integration mode, where test software can control directly the
 *     inputs and outputs of the processor, for integration testing
 *     or topology detection.
 */
union bdk_etrx_itctrl
{
    uint32_t u;
    struct bdk_etrx_itctrl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. The device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
#else /* Word 0 - Little Endian */
        uint32_t ime                   : 1;  /**< [  0:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. The device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_itctrl_s cn; */
};
typedef union bdk_etrx_itctrl bdk_etrx_itctrl_t;

static inline uint64_t BDK_ETRX_ITCTRL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_ITCTRL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040f00ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040f00ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040f00ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040f00ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_ITCTRL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_ITCTRL(a) bdk_etrx_itctrl_t
#define bustype_BDK_ETRX_ITCTRL(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_ITCTRL(a) "ETRX_ITCTRL"
#define busnum_BDK_ETRX_ITCTRL(a) (a)
#define arguments_BDK_ETRX_ITCTRL(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_lar
 *
 * ETR Management Software Lock Access Register
 * Allows or disallows access to the TRC registers through a
 *     memory-mapped interface.
 */
union bdk_etrx_lar
{
    uint32_t u;
    struct bdk_etrx_lar_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t key                   : 32; /**< [ 31:  0](WO) Lock access control. The software lock is not implemented for ETR.
                                                                 Writes to this register will be ignored. */
#else /* Word 0 - Little Endian */
        uint32_t key                   : 32; /**< [ 31:  0](WO) Lock access control. The software lock is not implemented for ETR.
                                                                 Writes to this register will be ignored. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_lar_s cn; */
};
typedef union bdk_etrx_lar bdk_etrx_lar_t;

static inline uint64_t BDK_ETRX_LAR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_LAR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fb0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fb0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fb0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fb0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_LAR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_LAR(a) bdk_etrx_lar_t
#define bustype_BDK_ETRX_LAR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_LAR(a) "ETRX_LAR"
#define busnum_BDK_ETRX_LAR(a) (a)
#define arguments_BDK_ETRX_LAR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_lsr
 *
 * ETR Management Software Lock Status Register
 * Indicates the current status of the software lock for TRC
 *     registers.
 */
union bdk_etrx_lsr
{
    uint32_t u;
    struct bdk_etrx_lsr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_3_31         : 29;
        uint32_t ntt                   : 1;  /**< [  2:  2](RO) Not thirty-two bit access required. */
        uint32_t slk                   : 1;  /**< [  1:  1](RO/H) Software lock status for this component. For an access to LSR
                                                                     that is not a memory-mapped access, or when the software lock
                                                                     is not implemented, this field is zero.
                                                                 For memory-mapped accesses when the software lock is
                                                                     implemented, possible values of this field are:
                                                                 0 = Lock clear. Writes are permitted to this component's
                                                                     registers.
                                                                 1 = Lock set. Writes to this component's registers are ignored,
                                                                     and reads have no side effects. */
        uint32_t sli                   : 1;  /**< [  0:  0](RO) Software lock implemented. For an access to LSR that is not a
                                                                     memory-mapped access, this field is zero. For memory-mapped
                                                                     accesses, the value of this field is implementation defined.
                                                                     Permitted values are:
                                                                 0 = Software lock not implemented or not memory-mapped access.
                                                                 1 = Software lock implemented and memory-mapped access. */
#else /* Word 0 - Little Endian */
        uint32_t sli                   : 1;  /**< [  0:  0](RO) Software lock implemented. For an access to LSR that is not a
                                                                     memory-mapped access, this field is zero. For memory-mapped
                                                                     accesses, the value of this field is implementation defined.
                                                                     Permitted values are:
                                                                 0 = Software lock not implemented or not memory-mapped access.
                                                                 1 = Software lock implemented and memory-mapped access. */
        uint32_t slk                   : 1;  /**< [  1:  1](RO/H) Software lock status for this component. For an access to LSR
                                                                     that is not a memory-mapped access, or when the software lock
                                                                     is not implemented, this field is zero.
                                                                 For memory-mapped accesses when the software lock is
                                                                     implemented, possible values of this field are:
                                                                 0 = Lock clear. Writes are permitted to this component's
                                                                     registers.
                                                                 1 = Lock set. Writes to this component's registers are ignored,
                                                                     and reads have no side effects. */
        uint32_t ntt                   : 1;  /**< [  2:  2](RO) Not thirty-two bit access required. */
        uint32_t reserved_3_31         : 29;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_lsr_s cn; */
};
typedef union bdk_etrx_lsr bdk_etrx_lsr_t;

static inline uint64_t BDK_ETRX_LSR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_LSR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fb4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fb4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fb4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fb4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_LSR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_LSR(a) bdk_etrx_lsr_t
#define bustype_BDK_ETRX_LSR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_LSR(a) "ETRX_LSR"
#define busnum_BDK_ETRX_LSR(a) (a)
#define arguments_BDK_ETRX_LSR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_mode
 *
 * ETR Mode Register
 * This register controls TMC operation mode. For ETR, the TMC can operate as software
 * FIFO mode and circular buffer mode.
 */
union bdk_etrx_mode
{
    uint32_t u;
    struct bdk_etrx_mode_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_7_31         : 25;
        uint32_t irqonready            : 1;  /**< [  6:  6](R/W) Interrupt on ready.
                                                                   0 = No interrupt generated.
                                                                   1 = Interrupt generated when ETR()_STATUS[TMCREADY] becomes set to one. */
        uint32_t irqonfull             : 1;  /**< [  5:  5](R/W) Interrupt on full.
                                                                   0 = No interrupt generated.
                                                                   1 = Interrupt generated when ETR()_STATUS[FULL] becomes set to one. */
        uint32_t stallonstop           : 1;  /**< [  4:  4](R/W) Stall trace input when formatter stops.
                                                                   0 = Discard trace when stopped.
                                                                   1 = Do not discard trace when stopped. */
        uint32_t reserved_2_3          : 2;
        uint32_t mode                  : 2;  /**< [  1:  0](RO) Select the operation mode:
                                                                 0x0 = Circular buffer mode. The trace memeory is used as a circular buffer.
                                                                 0x1 = Software FIFO mode. This mode is not supported by the hardware. */
#else /* Word 0 - Little Endian */
        uint32_t mode                  : 2;  /**< [  1:  0](RO) Select the operation mode:
                                                                 0x0 = Circular buffer mode. The trace memeory is used as a circular buffer.
                                                                 0x1 = Software FIFO mode. This mode is not supported by the hardware. */
        uint32_t reserved_2_3          : 2;
        uint32_t stallonstop           : 1;  /**< [  4:  4](R/W) Stall trace input when formatter stops.
                                                                   0 = Discard trace when stopped.
                                                                   1 = Do not discard trace when stopped. */
        uint32_t irqonfull             : 1;  /**< [  5:  5](R/W) Interrupt on full.
                                                                   0 = No interrupt generated.
                                                                   1 = Interrupt generated when ETR()_STATUS[FULL] becomes set to one. */
        uint32_t irqonready            : 1;  /**< [  6:  6](R/W) Interrupt on ready.
                                                                   0 = No interrupt generated.
                                                                   1 = Interrupt generated when ETR()_STATUS[TMCREADY] becomes set to one. */
        uint32_t reserved_7_31         : 25;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_mode_s cn; */
};
typedef union bdk_etrx_mode bdk_etrx_mode_t;

static inline uint64_t BDK_ETRX_MODE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_MODE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040028ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040028ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040028ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040028ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_MODE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_MODE(a) bdk_etrx_mode_t
#define bustype_BDK_ETRX_MODE(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_MODE(a) "ETRX_MODE"
#define busnum_BDK_ETRX_MODE(a) (a)
#define arguments_BDK_ETRX_MODE(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pidr0
 *
 * ETR Peripheral Identification Register 0
 * This register provides information to identify a debug component.
 */
union bdk_etrx_pidr0
{
    uint32_t u;
    struct bdk_etrx_pidr0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::ETR. */
#else /* Word 0 - Little Endian */
        uint32_t part_0                : 8;  /**< [  7:  0](RO) Part number \<7:0\>.  Indicates PCC_PIDR_PARTNUM0_E::ETR. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pidr0_s cn; */
};
typedef union bdk_etrx_pidr0 bdk_etrx_pidr0_t;

static inline uint64_t BDK_ETRX_PIDR0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PIDR0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fe0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fe0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fe0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fe0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PIDR0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PIDR0(a) bdk_etrx_pidr0_t
#define bustype_BDK_ETRX_PIDR0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PIDR0(a) "ETRX_PIDR0"
#define busnum_BDK_ETRX_PIDR0(a) (a)
#define arguments_BDK_ETRX_PIDR0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pidr1
 *
 * ETR Peripheral Identification Register 1
 * This register provides information to identify a debug component.
 */
union bdk_etrx_pidr1
{
    uint32_t u;
    struct bdk_etrx_pidr1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Cavium code is 0x4C. */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
#else /* Word 0 - Little Endian */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Cavium code is 0x4C. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pidr1_s cn9; */
    /* struct bdk_etrx_pidr1_s cn96xxp1; */
    struct bdk_etrx_pidr1_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Marvell (Cavium) code is 0x4C. */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
#else /* Word 0 - Little Endian */
        uint32_t part_1                : 4;  /**< [  3:  0](RO) Part number \<11:8\>.  Indicates PCC_PIDR_PARTNUM1_E::COMP. */
        uint32_t des_0                 : 4;  /**< [  7:  4](RO) JEP106 identification code \<3:0\>. Marvell (Cavium) code is 0x4C. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_etrx_pidr1_cn96xxp3 cn98xx; */
    /* struct bdk_etrx_pidr1_cn96xxp3 cnf95xx; */
    /* struct bdk_etrx_pidr1_cn96xxp3 loki; */
};
typedef union bdk_etrx_pidr1 bdk_etrx_pidr1_t;

static inline uint64_t BDK_ETRX_PIDR1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PIDR1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fe4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fe4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fe4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fe4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PIDR1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PIDR1(a) bdk_etrx_pidr1_t
#define bustype_BDK_ETRX_PIDR1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PIDR1(a) "ETRX_PIDR1"
#define busnum_BDK_ETRX_PIDR1(a) (a)
#define arguments_BDK_ETRX_PIDR1(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pidr2
 *
 * ETR Peripheral Identification Register 2
 * This register provides information to identify a debug component.
 */
union bdk_etrx_pidr2
{
    uint32_t u;
    struct bdk_etrx_pidr2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by ARM. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by ARM. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pidr2_s cn9; */
    /* struct bdk_etrx_pidr2_s cn96xxp1; */
    struct bdk_etrx_pidr2_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by Arm. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Marvell (Cavium) code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Marvell (Cavium) code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by Arm. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn96xxp3;
    struct bdk_etrx_pidr2_cn98xx
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by Arm. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
#else /* Word 0 - Little Endian */
        uint32_t des_1                 : 3;  /**< [  2:  0](RO) JEP106 identification code \<6:4\>. Cavium code is 0x4C. */
        uint32_t jedec                 : 1;  /**< [  3:  3](RO) JEDEC assigned. */
        uint32_t revision              : 4;  /**< [  7:  4](RO) Architectural revision, as assigned by Arm. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn98xx;
    /* struct bdk_etrx_pidr2_cn98xx cnf95xxp1; */
    /* struct bdk_etrx_pidr2_cn96xxp3 cnf95xxp2; */
    /* struct bdk_etrx_pidr2_cn96xxp3 loki; */
};
typedef union bdk_etrx_pidr2 bdk_etrx_pidr2_t;

static inline uint64_t BDK_ETRX_PIDR2(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PIDR2(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fe8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fe8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fe8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fe8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PIDR2", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PIDR2(a) bdk_etrx_pidr2_t
#define bustype_BDK_ETRX_PIDR2(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PIDR2(a) "ETRX_PIDR2"
#define busnum_BDK_ETRX_PIDR2(a) (a)
#define arguments_BDK_ETRX_PIDR2(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pidr3
 *
 * ETR Peripheral Identification Register 3
 * This register provides information to identify a debug component.
 */
union bdk_etrx_pidr3
{
    uint32_t u;
    struct bdk_etrx_pidr3_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer modified. 0x1 = Overall product information should be consulted for
                                                                 product, major and minor pass numbers. */
#else /* Word 0 - Little Endian */
        uint32_t cmod                  : 4;  /**< [  3:  0](RO) Customer modified. 0x1 = Overall product information should be consulted for
                                                                 product, major and minor pass numbers. */
        uint32_t revand                : 4;  /**< [  7:  4](RO) Manufacturer revision number. For CNXXXX always 0x0. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pidr3_s cn; */
};
typedef union bdk_etrx_pidr3 bdk_etrx_pidr3_t;

static inline uint64_t BDK_ETRX_PIDR3(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PIDR3(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fecll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fecll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fecll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fecll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PIDR3", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PIDR3(a) bdk_etrx_pidr3_t
#define bustype_BDK_ETRX_PIDR3(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PIDR3(a) "ETRX_PIDR3"
#define busnum_BDK_ETRX_PIDR3(a) (a)
#define arguments_BDK_ETRX_PIDR3(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pidr4
 *
 * ETR Peripheral Identification Register 4
 * This register provides information to identify a debug component.
 */
union bdk_etrx_pidr4
{
    uint32_t u;
    struct bdk_etrx_pidr4_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t fourkbcount           : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t jep106cont            : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
#else /* Word 0 - Little Endian */
        uint32_t jep106cont            : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Cavium. */
        uint32_t fourkbcount           : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pidr4_s cn9; */
    /* struct bdk_etrx_pidr4_s cn96xxp1; */
    struct bdk_etrx_pidr4_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t fourkbcount           : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t jep106cont            : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Marvell (Cavium). */
#else /* Word 0 - Little Endian */
        uint32_t jep106cont            : 4;  /**< [  3:  0](RO) JEP106 continuation code, least significant nibble. Indicates Marvell (Cavium). */
        uint32_t fourkbcount           : 4;  /**< [  7:  4](RO) Size of the component. Log\<sub\>2\</sub\> of the number of 4KB pages from the
                                                                 start of the component to the end of the component ID registers. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_etrx_pidr4_s cn98xx; */
    /* struct bdk_etrx_pidr4_s cnf95xxp1; */
    /* struct bdk_etrx_pidr4_cn96xxp3 cnf95xxp2; */
    /* struct bdk_etrx_pidr4_cn96xxp3 loki; */
};
typedef union bdk_etrx_pidr4 bdk_etrx_pidr4_t;

static inline uint64_t BDK_ETRX_PIDR4(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PIDR4(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fd0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fd0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fd0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fd0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PIDR4", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PIDR4(a) bdk_etrx_pidr4_t
#define bustype_BDK_ETRX_PIDR4(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PIDR4(a) "ETRX_PIDR4"
#define busnum_BDK_ETRX_PIDR4(a) (a)
#define arguments_BDK_ETRX_PIDR4(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pidr5
 *
 * ETR Peripheral Identification Register 5
 * This register provides information to identify a debug component.
 */
union bdk_etrx_pidr5
{
    uint32_t u;
    struct bdk_etrx_pidr5_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pidr5_s cn; */
};
typedef union bdk_etrx_pidr5 bdk_etrx_pidr5_t;

static inline uint64_t BDK_ETRX_PIDR5(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PIDR5(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fd4ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fd4ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fd4ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fd4ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PIDR5", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PIDR5(a) bdk_etrx_pidr5_t
#define bustype_BDK_ETRX_PIDR5(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PIDR5(a) "ETRX_PIDR5"
#define busnum_BDK_ETRX_PIDR5(a) (a)
#define arguments_BDK_ETRX_PIDR5(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pidr6
 *
 * ETR Peripheral Identification Register 6
 * This register provides information to identify a debug component.
 */
union bdk_etrx_pidr6
{
    uint32_t u;
    struct bdk_etrx_pidr6_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pidr6_s cn; */
};
typedef union bdk_etrx_pidr6 bdk_etrx_pidr6_t;

static inline uint64_t BDK_ETRX_PIDR6(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PIDR6(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fd8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fd8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fd8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fd8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PIDR6", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PIDR6(a) bdk_etrx_pidr6_t
#define bustype_BDK_ETRX_PIDR6(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PIDR6(a) "ETRX_PIDR6"
#define busnum_BDK_ETRX_PIDR6(a) (a)
#define arguments_BDK_ETRX_PIDR6(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pidr7
 *
 * ETR Peripheral Identification Register 7
 * This register provides information to identify a debug component.
 */
union bdk_etrx_pidr7
{
    uint32_t u;
    struct bdk_etrx_pidr7_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pidr7_s cn; */
};
typedef union bdk_etrx_pidr7 bdk_etrx_pidr7_t;

static inline uint64_t BDK_ETRX_PIDR7(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PIDR7(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fdcll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fdcll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fdcll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fdcll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PIDR7", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PIDR7(a) bdk_etrx_pidr7_t
#define bustype_BDK_ETRX_PIDR7(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PIDR7(a) "ETRX_PIDR7"
#define busnum_BDK_ETRX_PIDR7(a) (a)
#define arguments_BDK_ETRX_PIDR7(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pscr
 *
 * ETR Periodic Synchronization Counter Register
 * This register enables the ETR to switch from its default mode into integration mode,
 * where test software can control directly the inputs and outputs of the processor,
 * for integration testing or topology detection.
 */
union bdk_etrx_pscr
{
    uint32_t u;
    struct bdk_etrx_pscr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_5_31         : 27;
        uint32_t pscount               : 5;  /**< [  4:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. When IME == 1, the device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
#else /* Word 0 - Little Endian */
        uint32_t pscount               : 5;  /**< [  4:  0](RO) Integration mode enable.
                                                                 0 = Normal operation.
                                                                 1 = Integration mode enabled. When IME == 1, the device reverts to
                                                                     an integration mode to enable integration testing or topology
                                                                     detection. The integration mode behavior is implementation
                                                                     defined. */
        uint32_t reserved_5_31         : 27;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pscr_s cn; */
};
typedef union bdk_etrx_pscr bdk_etrx_pscr_t;

static inline uint64_t BDK_ETRX_PSCR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PSCR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040308ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040308ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040308ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040308ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PSCR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PSCR(a) bdk_etrx_pscr_t
#define bustype_BDK_ETRX_PSCR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PSCR(a) "ETRX_PSCR"
#define busnum_BDK_ETRX_PSCR(a) (a)
#define arguments_BDK_ETRX_PSCR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_pwrcontrol
 *
 * ETR Power Control Register
 * This register controls TMC response to a power quiescence request.
 */
union bdk_etrx_pwrcontrol
{
    uint32_t u;
    struct bdk_etrx_pwrcontrol_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t disablepd             : 1;  /**< [  0:  0](R/W) Allow TMC power down.
                                                                   0 = Accept power quiescence request.
                                                                   1 = Deny power quiescence request.

                                                                 Software must set this bit to one when it configures TMC for trace capture. */
#else /* Word 0 - Little Endian */
        uint32_t disablepd             : 1;  /**< [  0:  0](R/W) Allow TMC power down.
                                                                   0 = Accept power quiescence request.
                                                                   1 = Deny power quiescence request.

                                                                 Software must set this bit to one when it configures TMC for trace capture. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_pwrcontrol_s cn; */
};
typedef union bdk_etrx_pwrcontrol bdk_etrx_pwrcontrol_t;

static inline uint64_t BDK_ETRX_PWRCONTROL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_PWRCONTROL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a0080400f0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a0080400f0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a0080400f0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a0080400f0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_PWRCONTROL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_PWRCONTROL(a) bdk_etrx_pwrcontrol_t
#define bustype_BDK_ETRX_PWRCONTROL(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_PWRCONTROL(a) "ETRX_PWRCONTROL"
#define busnum_BDK_ETRX_PWRCONTROL(a) (a)
#define arguments_BDK_ETRX_PWRCONTROL(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_ramsize
 *
 * ETR RAM Size Register
 */
union bdk_etrx_ramsize
{
    uint32_t u;
    struct bdk_etrx_ramsize_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_31           : 1;
        uint32_t rsz                   : 31; /**< [ 30:  0](R/W) Size of the buffer in memory in 64-bit words.
                                                                 For example, for 1KB buffer this register is 0x00000080.
                                                                 For 4GB buffer this register is 0x20000000. */
#else /* Word 0 - Little Endian */
        uint32_t rsz                   : 31; /**< [ 30:  0](R/W) Size of the buffer in memory in 64-bit words.
                                                                 For example, for 1KB buffer this register is 0x00000080.
                                                                 For 4GB buffer this register is 0x20000000. */
        uint32_t reserved_31           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_ramsize_s cn; */
};
typedef union bdk_etrx_ramsize bdk_etrx_ramsize_t;

static inline uint64_t BDK_ETRX_RAMSIZE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_RAMSIZE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040004ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040004ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040004ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040004ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_RAMSIZE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_RAMSIZE(a) bdk_etrx_ramsize_t
#define bustype_BDK_ETRX_RAMSIZE(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_RAMSIZE(a) "ETRX_RAMSIZE"
#define busnum_BDK_ETRX_RAMSIZE(a) (a)
#define arguments_BDK_ETRX_RAMSIZE(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_status
 *
 * ETR Status Register
 */
union bdk_etrx_status
{
    uint32_t u;
    struct bdk_etrx_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_7_31         : 25;
        uint32_t msi                   : 1;  /**< [  6:  6](RO) Message-signaled interrupt status.
                                                                 Indicates that a message signaled interrupt is in flight.
                                                                   0 = No interrupt is in flight.
                                                                   1 = An interrupt message has been sent and the acknowledge not yet received. */
        uint32_t memerr                : 1;  /**< [  5:  5](RO) Error has occurred on a memory transaction.
                                                                 This bit is cleared by:
                                                                   1. Writing to this register with this bit set when [TMCREADY] is 1.
                                                                   2. Setting [TRACECAPTEN] when [TRACECAPTEN] is zero. */
        uint32_t empty                 : 1;  /**< [  4:  4](RO) If set, this bit indicates that the TMC does not contain any valid trace data in the
                                                                 memory.
                                                                 This does not, however, mean that the pipeline stages within the TMC are empty.
                                                                 To determine whether the pipeline stages within TMC are empty, read [TMCREADY].
                                                                 This bit is valid when [TRACECAPTEN] is 1.
                                                                 This bit reads as zero when [TRACECAPTEN] is zero. */
        uint32_t ftempty               : 1;  /**< [  3:  3](RO) This bit is set when trace capture has stopped, and all internal pipelines and buffers
                                                                 have drained.
                                                                 Unlike [TMCREADY], it is not affected by buffer drains and AXI accesses. */
        uint32_t tmcready              : 1;  /**< [  2:  2](RO) This bit is set when all the following are true:
                                                                   1. Trace capture has stopped and all internal pipelines and buffers have drained.
                                                                   2. The TMC is not draining because of ETR_FFCR[DRAINBUFFER] being 1.
                                                                   3. In ETR configuration, the memory interface is not busy. This case can be used to
                                                                 detect
                                                                      page table reads in scatter-gather mode when in stopped state. */
        uint32_t triggered             : 1;  /**< [  1:  1](RO) Set when trace capture is in progress and the TMC has detected a trigger
                                                                 event. This bit is cleared when leaving disabled state. */
        uint32_t full                  : 1;  /**< [  0:  0](RO) This bit can help to determine how much of the trace buffer contains valid data.
                                                                 When entering disabled state, this bit retains previous value.
                                                                 When exiting disabled state, this bit is cleared. */
#else /* Word 0 - Little Endian */
        uint32_t full                  : 1;  /**< [  0:  0](RO) This bit can help to determine how much of the trace buffer contains valid data.
                                                                 When entering disabled state, this bit retains previous value.
                                                                 When exiting disabled state, this bit is cleared. */
        uint32_t triggered             : 1;  /**< [  1:  1](RO) Set when trace capture is in progress and the TMC has detected a trigger
                                                                 event. This bit is cleared when leaving disabled state. */
        uint32_t tmcready              : 1;  /**< [  2:  2](RO) This bit is set when all the following are true:
                                                                   1. Trace capture has stopped and all internal pipelines and buffers have drained.
                                                                   2. The TMC is not draining because of ETR_FFCR[DRAINBUFFER] being 1.
                                                                   3. In ETR configuration, the memory interface is not busy. This case can be used to
                                                                 detect
                                                                      page table reads in scatter-gather mode when in stopped state. */
        uint32_t ftempty               : 1;  /**< [  3:  3](RO) This bit is set when trace capture has stopped, and all internal pipelines and buffers
                                                                 have drained.
                                                                 Unlike [TMCREADY], it is not affected by buffer drains and AXI accesses. */
        uint32_t empty                 : 1;  /**< [  4:  4](RO) If set, this bit indicates that the TMC does not contain any valid trace data in the
                                                                 memory.
                                                                 This does not, however, mean that the pipeline stages within the TMC are empty.
                                                                 To determine whether the pipeline stages within TMC are empty, read [TMCREADY].
                                                                 This bit is valid when [TRACECAPTEN] is 1.
                                                                 This bit reads as zero when [TRACECAPTEN] is zero. */
        uint32_t memerr                : 1;  /**< [  5:  5](RO) Error has occurred on a memory transaction.
                                                                 This bit is cleared by:
                                                                   1. Writing to this register with this bit set when [TMCREADY] is 1.
                                                                   2. Setting [TRACECAPTEN] when [TRACECAPTEN] is zero. */
        uint32_t msi                   : 1;  /**< [  6:  6](RO) Message-signaled interrupt status.
                                                                 Indicates that a message signaled interrupt is in flight.
                                                                   0 = No interrupt is in flight.
                                                                   1 = An interrupt message has been sent and the acknowledge not yet received. */
        uint32_t reserved_7_31         : 25;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_status_s cn; */
};
typedef union bdk_etrx_status bdk_etrx_status_t;

static inline uint64_t BDK_ETRX_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_STATUS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00804000cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00804000cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00804000cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00804000cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_STATUS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_STATUS(a) bdk_etrx_status_t
#define bustype_BDK_ETRX_STATUS(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_STATUS(a) "ETRX_STATUS"
#define busnum_BDK_ETRX_STATUS(a) (a)
#define arguments_BDK_ETRX_STATUS(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_trcclaimset
 *
 * ETR Claim Tag Set Register
 * Software can use this to:
 *   1. Set bits in the claim tag to one.
 *   2. discover the number of bits that the claim tag supports.
 */
union bdk_etrx_trcclaimset
{
    uint32_t u;
    struct bdk_etrx_trcclaimset_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t set                   : 8;  /**< [  7:  0](R/W1S) When a write to one of these bits occurs, with the value:
                                                                   0 = The register ignores the write.
                                                                   1 = If the bit is supported then it is set to one.
                                                                      A single write operation can set multiple bits to one.

                                                                 Software must use the TRCCLAIMCLR register to:
                                                                   Read the value of the claim tag.
                                                                   Clear a claim tag bit to zero. */
#else /* Word 0 - Little Endian */
        uint32_t set                   : 8;  /**< [  7:  0](R/W1S) When a write to one of these bits occurs, with the value:
                                                                   0 = The register ignores the write.
                                                                   1 = If the bit is supported then it is set to one.
                                                                      A single write operation can set multiple bits to one.

                                                                 Software must use the TRCCLAIMCLR register to:
                                                                   Read the value of the claim tag.
                                                                   Clear a claim tag bit to zero. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_trcclaimset_s cn; */
};
typedef union bdk_etrx_trcclaimset bdk_etrx_trcclaimset_t;

static inline uint64_t BDK_ETRX_TRCCLAIMSET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_TRCCLAIMSET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fa0ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fa0ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fa0ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fa0ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_TRCCLAIMSET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_TRCCLAIMSET(a) bdk_etrx_trcclaimset_t
#define bustype_BDK_ETRX_TRCCLAIMSET(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_TRCCLAIMSET(a) "ETRX_TRCCLAIMSET"
#define busnum_BDK_ETRX_TRCCLAIMSET(a) (a)
#define arguments_BDK_ETRX_TRCCLAIMSET(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_trigcntr
 *
 * ETR Trigger Counter Register
 * The number of 32-bit words written into the trace RAM following the trigger is the
 * value stored in this register plus one.
 */
union bdk_etrx_trigcntr
{
    uint32_t u;
    struct bdk_etrx_trigcntr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t trg                   : 32; /**< [ 31:  0](R/W) The number of 32-bit words between a TRIGIN or trigger packet and a trigger
                                                                 event. This register is ignored when TMC is in software FIFO mode or hardware
                                                                 FIFO mode. */
#else /* Word 0 - Little Endian */
        uint32_t trg                   : 32; /**< [ 31:  0](R/W) The number of 32-bit words between a TRIGIN or trigger packet and a trigger
                                                                 event. This register is ignored when TMC is in software FIFO mode or hardware
                                                                 FIFO mode. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_trigcntr_s cn; */
};
typedef union bdk_etrx_trigcntr bdk_etrx_trigcntr_t;

static inline uint64_t BDK_ETRX_TRIGCNTR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_TRIGCNTR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00804001cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00804001cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00804001cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00804001cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_TRIGCNTR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_TRIGCNTR(a) bdk_etrx_trigcntr_t
#define bustype_BDK_ETRX_TRIGCNTR(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_TRIGCNTR(a) "ETRX_TRIGCNTR"
#define busnum_BDK_ETRX_TRIGCNTR(a) (a)
#define arguments_BDK_ETRX_TRIGCNTR(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_wtrpointer
 *
 * ETR RAM Write Pointer Register
 * This register is used together with ETR()_RWPHI as the write pointer used to write
 * entries into trace RAM.
 */
union bdk_etrx_wtrpointer
{
    uint32_t u;
    struct bdk_etrx_wtrpointer_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t rwp                   : 32; /**< [ 31:  0](R/W) Bits \<31:0\> of the write pointer in the trace memory that are accessed on a
                                                                 subsequent write to the trace memory. */
#else /* Word 0 - Little Endian */
        uint32_t rwp                   : 32; /**< [ 31:  0](R/W) Bits \<31:0\> of the write pointer in the trace memory that are accessed on a
                                                                 subsequent write to the trace memory. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_wtrpointer_s cn; */
};
typedef union bdk_etrx_wtrpointer bdk_etrx_wtrpointer_t;

static inline uint64_t BDK_ETRX_WTRPOINTER(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_WTRPOINTER(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040018ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040018ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040018ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040018ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_WTRPOINTER", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_WTRPOINTER(a) bdk_etrx_wtrpointer_t
#define bustype_BDK_ETRX_WTRPOINTER(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_WTRPOINTER(a) "ETRX_WTRPOINTER"
#define busnum_BDK_ETRX_WTRPOINTER(a) (a)
#define arguments_BDK_ETRX_WTRPOINTER(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etr#_wtrpointerhi
 *
 * ETR Write Pointer High Register
 * In the ETR configuration, memory addresses are 40 bits wide. This register is used
 * together with ETR()_RWP to write entries into the trace memory.
 */
union bdk_etrx_wtrpointerhi
{
    uint32_t u;
    struct bdk_etrx_wtrpointerhi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t rwphi                 : 32; /**< [ 31:  0](R/W) Bit[19:0] : Bits \<51:32\> of the write pointer. */
#else /* Word 0 - Little Endian */
        uint32_t rwphi                 : 32; /**< [ 31:  0](R/W) Bit[19:0] : Bits \<51:32\> of the write pointer. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrx_wtrpointerhi_s cn; */
};
typedef union bdk_etrx_wtrpointerhi bdk_etrx_wtrpointerhi_t;

static inline uint64_t BDK_ETRX_WTRPOINTERHI(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRX_WTRPOINTERHI(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a00804003cll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a00804003cll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a00804003cll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a00804003cll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRX_WTRPOINTERHI", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRX_WTRPOINTERHI(a) bdk_etrx_wtrpointerhi_t
#define bustype_BDK_ETRX_WTRPOINTERHI(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRX_WTRPOINTERHI(a) "ETRX_WTRPOINTERHI"
#define busnum_BDK_ETRX_WTRPOINTERHI(a) (a)
#define arguments_BDK_ETRX_WTRPOINTERHI(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etrc#_devaff0
 *
 * ETR Management Device Affinity Register 0
 * This register returns the lower 32 bits of the PE MPIDR, that is MPIDR[31:0].
 */
union bdk_etrcx_devaff0
{
    uint32_t u;
    struct bdk_etrcx_devaff0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t aff2                  : 8;  /**< [ 23: 16](RO/H) AFF2, this is node id. */
        uint32_t aff1                  : 8;  /**< [ 15:  8](RO/H) AFF1, this is the group of 16 cores within a node. */
        uint32_t aff0                  : 8;  /**< [  7:  0](RO/H) AFF0, this is the core within a group of 16. */
#else /* Word 0 - Little Endian */
        uint32_t aff0                  : 8;  /**< [  7:  0](RO/H) AFF0, this is the core within a group of 16. */
        uint32_t aff1                  : 8;  /**< [ 15:  8](RO/H) AFF1, this is the group of 16 cores within a node. */
        uint32_t aff2                  : 8;  /**< [ 23: 16](RO/H) AFF2, this is node id. */
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrcx_devaff0_s cn; */
};
typedef union bdk_etrcx_devaff0 bdk_etrcx_devaff0_t;

static inline uint64_t BDK_ETRCX_DEVAFF0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRCX_DEVAFF0(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040fa8ll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040fa8ll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040fa8ll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040fa8ll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRCX_DEVAFF0", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRCX_DEVAFF0(a) bdk_etrcx_devaff0_t
#define bustype_BDK_ETRCX_DEVAFF0(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRCX_DEVAFF0(a) "ETRCX_DEVAFF0"
#define busnum_BDK_ETRCX_DEVAFF0(a) (a)
#define arguments_BDK_ETRCX_DEVAFF0(a) (a),-1,-1,-1

/**
 * Register (DAB32b) etrc#_devaff1
 *
 * ETR Management Device Affinity Register 1
 * This register returns the upper 32 bits of the PE MPIDR, that is MPIDR[63:32].
 */
union bdk_etrcx_devaff1
{
    uint32_t u;
    struct bdk_etrcx_devaff1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_31         : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_etrcx_devaff1_s cn; */
};
typedef union bdk_etrcx_devaff1 bdk_etrcx_devaff1_t;

static inline uint64_t BDK_ETRCX_DEVAFF1(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_ETRCX_DEVAFF1(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=23))
        return 0x87a008040facll + 0x80000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=35))
        return 0x87a008040facll + 0x80000ll * ((a) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=5))
        return 0x87a008040facll + 0x80000ll * ((a) & 0x7);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=5))
        return 0x87a008040facll + 0x80000ll * ((a) & 0x7);
    __bdk_csr_fatal("ETRCX_DEVAFF1", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_ETRCX_DEVAFF1(a) bdk_etrcx_devaff1_t
#define bustype_BDK_ETRCX_DEVAFF1(a) BDK_CSR_TYPE_DAB32b
#define basename_BDK_ETRCX_DEVAFF1(a) "ETRCX_DEVAFF1"
#define busnum_BDK_ETRCX_DEVAFF1(a) (a)
#define arguments_BDK_ETRCX_DEVAFF1(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_DAB_ETR_H__ */
