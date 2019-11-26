#ifndef __BDK_CSRS_PCM_H__
#define __BDK_CSRS_PCM_H__
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
 * OcteonTX PCM.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration pcm_bar_e
 *
 * PCM Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_PCM_BAR_E_PCM_PF_BAR0 (0x806000000000ll)
#define BDK_PCM_BAR_E_PCM_PF_BAR0_SIZE 0x800000ull
#define BDK_PCM_BAR_E_PCM_PF_BAR4 (0x806000f00000ll)
#define BDK_PCM_BAR_E_PCM_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration pcm_int_vec_e
 *
 * PCM MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_PCM_INT_VEC_E_TEX(a) (0 + (a))

/**
 * Register (NCB) pcm_clk#_cfg
 *
 * PCM Clock Configuration Register
 */
union bdk_pcm_clkx_cfg
{
    uint64_t u;
    struct bdk_pcm_clkx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t fsyncgood             : 1;  /**< [ 63: 63](RO/H) FSYNC status.
                                                                 0 = None/extra fsync pulse seen on most recent frame.
                                                                 1 = Last frame had a correctly positioned fsync pulse.

                                                                 NOTE: This is intended for startup. the FSYNCEXTRA and FSYNCMISSING interrupts
                                                                 are intended for detecting loss of sync during normal operation. */
        uint64_t reserved_48_62        : 15;
        uint64_t fsyncsamp             : 16; /**< [ 47: 32](R/W) Number of coprocessor clocks from internal BCLK edge to sample FSYNC.
                                                                 Used to sync to the start of a frame and to check for FSYNC errors. */
        uint64_t reserved_26_31        : 6;
        uint64_t fsynclen              : 5;  /**< [ 25: 21](R/W) Number of 1/2 BCLKs FSYNC is asserted for.
                                                                 Only used when GEN==1. */
        uint64_t fsyncloc              : 5;  /**< [ 20: 16](R/W) FSYNC location, in 1/2 BCLKS before timeslot 0, bit 0.
                                                                 Used to detect framing errors and
                                                                 therefore must have a correct value even if GEN=0. */
        uint64_t numslots              : 10; /**< [ 15:  6](R/W) Number of 8-bit slots in a frame.
                                                                 This, along with [EXTRABIT] and Fbclk
                                                                 determines FSYNC frequency when GEN = 1.
                                                                 Also used to detect framing errors and
                                                                 therefore must have a correct value even if GEN = 0. */
        uint64_t extrabit              : 1;  /**< [  5:  5](R/W) Add extra.
                                                                 0 = No frame bit.
                                                                 1 = Add one extra bit time for frame bit.

                                                                 If GEN == 1, then FSYNC will be delayed one extra bit time.

                                                                 Also used to detect framing errors and therefore must have a correct value even
                                                                 if GEN=0.

                                                                 The extra bit comes from the LSB/MSB of the first byte of the frame in the
                                                                 transmit memory region.  LSB vs MSB is determined from the setting of
                                                                 PCM_TE()_TDM_CFG[LSBFIRST]. */
        uint64_t bitlen                : 2;  /**< [  4:  3](R/W) Number of BCLKs in a bit time.
                                                                 0 = 1 BCLK.
                                                                 1 = 2 BCLKs.
                                                                 2 = 4 BCLKs.
                                                                 3 = Reserved. */
        uint64_t bclkpol               : 1;  /**< [  2:  2](R/W) BCLK polarity.
                                                                 0 = BCLK rise edge is start of bit time.
                                                                 1 = BCLK fall edge is start of bit time.

                                                                 Also used to detect framing errors and therefore must have a correct value even
                                                                 if GEN=0. */
        uint64_t fsyncpol              : 1;  /**< [  1:  1](R/W) FSYNC polarity.
                                                                 0 = FSYNC idles low, asserts high.
                                                                 1 = FSYNC idles high, asserts low.

                                                                 Also used to detect framing errors and therefore must have a correct value even
                                                                 if GEN=0. */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) Clock enable.
                                                                 0 = Clock receiving logic is doing nothing.
                                                                 1 = Clock receiving logic is looking for sync. */
#else /* Word 0 - Little Endian */
        uint64_t ena                   : 1;  /**< [  0:  0](R/W) Clock enable.
                                                                 0 = Clock receiving logic is doing nothing.
                                                                 1 = Clock receiving logic is looking for sync. */
        uint64_t fsyncpol              : 1;  /**< [  1:  1](R/W) FSYNC polarity.
                                                                 0 = FSYNC idles low, asserts high.
                                                                 1 = FSYNC idles high, asserts low.

                                                                 Also used to detect framing errors and therefore must have a correct value even
                                                                 if GEN=0. */
        uint64_t bclkpol               : 1;  /**< [  2:  2](R/W) BCLK polarity.
                                                                 0 = BCLK rise edge is start of bit time.
                                                                 1 = BCLK fall edge is start of bit time.

                                                                 Also used to detect framing errors and therefore must have a correct value even
                                                                 if GEN=0. */
        uint64_t bitlen                : 2;  /**< [  4:  3](R/W) Number of BCLKs in a bit time.
                                                                 0 = 1 BCLK.
                                                                 1 = 2 BCLKs.
                                                                 2 = 4 BCLKs.
                                                                 3 = Reserved. */
        uint64_t extrabit              : 1;  /**< [  5:  5](R/W) Add extra.
                                                                 0 = No frame bit.
                                                                 1 = Add one extra bit time for frame bit.

                                                                 If GEN == 1, then FSYNC will be delayed one extra bit time.

                                                                 Also used to detect framing errors and therefore must have a correct value even
                                                                 if GEN=0.

                                                                 The extra bit comes from the LSB/MSB of the first byte of the frame in the
                                                                 transmit memory region.  LSB vs MSB is determined from the setting of
                                                                 PCM_TE()_TDM_CFG[LSBFIRST]. */
        uint64_t numslots              : 10; /**< [ 15:  6](R/W) Number of 8-bit slots in a frame.
                                                                 This, along with [EXTRABIT] and Fbclk
                                                                 determines FSYNC frequency when GEN = 1.
                                                                 Also used to detect framing errors and
                                                                 therefore must have a correct value even if GEN = 0. */
        uint64_t fsyncloc              : 5;  /**< [ 20: 16](R/W) FSYNC location, in 1/2 BCLKS before timeslot 0, bit 0.
                                                                 Used to detect framing errors and
                                                                 therefore must have a correct value even if GEN=0. */
        uint64_t fsynclen              : 5;  /**< [ 25: 21](R/W) Number of 1/2 BCLKs FSYNC is asserted for.
                                                                 Only used when GEN==1. */
        uint64_t reserved_26_31        : 6;
        uint64_t fsyncsamp             : 16; /**< [ 47: 32](R/W) Number of coprocessor clocks from internal BCLK edge to sample FSYNC.
                                                                 Used to sync to the start of a frame and to check for FSYNC errors. */
        uint64_t reserved_48_62        : 15;
        uint64_t fsyncgood             : 1;  /**< [ 63: 63](RO/H) FSYNC status.
                                                                 0 = None/extra fsync pulse seen on most recent frame.
                                                                 1 = Last frame had a correctly positioned fsync pulse.

                                                                 NOTE: This is intended for startup. the FSYNCEXTRA and FSYNCMISSING interrupts
                                                                 are intended for detecting loss of sync during normal operation. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_clkx_cfg_s cn; */
};
typedef union bdk_pcm_clkx_cfg bdk_pcm_clkx_cfg_t;

static inline uint64_t BDK_PCM_CLKX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_CLKX_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=1))
        return 0x806000000000ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PCM_CLKX_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_CLKX_CFG(a) bdk_pcm_clkx_cfg_t
#define bustype_BDK_PCM_CLKX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_CLKX_CFG(a) "PCM_CLKX_CFG"
#define device_bar_BDK_PCM_CLKX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_CLKX_CFG(a) (a)
#define arguments_BDK_PCM_CLKX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_clk#_dbg
 *
 * INTERNAL: PCM Clock Debug Information Register
 */
union bdk_pcm_clkx_dbg
{
    uint64_t u;
    struct bdk_pcm_clkx_dbg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t debuginfo             : 64; /**< [ 63:  0](RO/H) Miscellaneous debug information. */
#else /* Word 0 - Little Endian */
        uint64_t debuginfo             : 64; /**< [ 63:  0](RO/H) Miscellaneous debug information. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_clkx_dbg_s cn; */
};
typedef union bdk_pcm_clkx_dbg bdk_pcm_clkx_dbg_t;

static inline uint64_t BDK_PCM_CLKX_DBG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_CLKX_DBG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=1))
        return 0x806000000038ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PCM_CLKX_DBG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_CLKX_DBG(a) bdk_pcm_clkx_dbg_t
#define bustype_BDK_PCM_CLKX_DBG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_CLKX_DBG(a) "PCM_CLKX_DBG"
#define device_bar_BDK_PCM_CLKX_DBG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_CLKX_DBG(a) (a)
#define arguments_BDK_PCM_CLKX_DBG(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_clk#_gen
 *
 * PCM Clock Generation Register
 */
union bdk_pcm_clkx_gen
{
    uint64_t u;
    struct bdk_pcm_clkx_gen_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t deltasamp             : 16; /**< [ 63: 48](R/W) Signed number of coprocessor clocks to move sampled BCLK edge.
                                                                 The complete number of coprocessor clocks to move is:

                                                                   _ [NUMSAMP] + 2 + 1 + [DELTASAMP]

                                                                 _ [NUMSAMP] to compensate for sampling delay.
                                                                 _ + 2 to compensate for dual-rank synchronizer.
                                                                 _ + 1 for uncertainity.
                                                                 + + [DELTASAMP] to CMA/debugging. */
        uint64_t numsamp               : 16; /**< [ 47: 32](R/W) Number of coprocessor clocks samples to detect BCLK change
                                                                 when receiving clock. */
        uint64_t n                     : 32; /**< [ 31:  0](R/W) Determines BCLK frequency when generating clock.
                                                                 _ Fbclk = Fcoprocessor_clk * N / 2^32
                                                                 _ N = (Fbclk / Fcoprocessor_clk) * 2^32

                                                                 Writing N = 0 stops the clock generator, and causes bclk and fsync to be
                                                                 received. */
#else /* Word 0 - Little Endian */
        uint64_t n                     : 32; /**< [ 31:  0](R/W) Determines BCLK frequency when generating clock.
                                                                 _ Fbclk = Fcoprocessor_clk * N / 2^32
                                                                 _ N = (Fbclk / Fcoprocessor_clk) * 2^32

                                                                 Writing N = 0 stops the clock generator, and causes bclk and fsync to be
                                                                 received. */
        uint64_t numsamp               : 16; /**< [ 47: 32](R/W) Number of coprocessor clocks samples to detect BCLK change
                                                                 when receiving clock. */
        uint64_t deltasamp             : 16; /**< [ 63: 48](R/W) Signed number of coprocessor clocks to move sampled BCLK edge.
                                                                 The complete number of coprocessor clocks to move is:

                                                                   _ [NUMSAMP] + 2 + 1 + [DELTASAMP]

                                                                 _ [NUMSAMP] to compensate for sampling delay.
                                                                 _ + 2 to compensate for dual-rank synchronizer.
                                                                 _ + 1 for uncertainity.
                                                                 + + [DELTASAMP] to CMA/debugging. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_clkx_gen_s cn; */
};
typedef union bdk_pcm_clkx_gen bdk_pcm_clkx_gen_t;

static inline uint64_t BDK_PCM_CLKX_GEN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_CLKX_GEN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=1))
        return 0x806000000008ll + 0x10000ll * ((a) & 0x1);
    __bdk_csr_fatal("PCM_CLKX_GEN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_CLKX_GEN(a) bdk_pcm_clkx_gen_t
#define bustype_BDK_PCM_CLKX_GEN(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_CLKX_GEN(a) "PCM_CLKX_GEN"
#define device_bar_BDK_PCM_CLKX_GEN(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_CLKX_GEN(a) (a)
#define arguments_BDK_PCM_CLKX_GEN(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_msix_pba#
 *
 * PCM MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the PCM_INT_VEC_E enumeration.
 */
union bdk_pcm_msix_pbax
{
    uint64_t u;
    struct bdk_pcm_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated PCM_MSIX_VEC()_CTL, enumerated by PCM_INT_VEC_E. Bits
                                                                 that have no associated PCM_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated PCM_MSIX_VEC()_CTL, enumerated by PCM_INT_VEC_E. Bits
                                                                 that have no associated PCM_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_msix_pbax_s cn; */
};
typedef union bdk_pcm_msix_pbax bdk_pcm_msix_pbax_t;

static inline uint64_t BDK_PCM_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_MSIX_PBAX(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a==0))
        return 0x806000ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("PCM_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_MSIX_PBAX(a) bdk_pcm_msix_pbax_t
#define bustype_BDK_PCM_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_MSIX_PBAX(a) "PCM_MSIX_PBAX"
#define device_bar_BDK_PCM_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_PCM_MSIX_PBAX(a) (a)
#define arguments_BDK_PCM_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_msix_vec#_addr
 *
 * PCM MSI-X Vector Table Address Registers
 * This register is the MSI-X vector table, indexed by the PCM_INT_VEC_E enumeration.
 */
union bdk_pcm_msix_vecx_addr
{
    uint64_t u;
    struct bdk_pcm_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's PCM_MSIX_VEC()_ADDR, PCM_MSIX_VEC()_CTL, and corresponding
                                                                 bit of PCM_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_PCM_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's PCM_MSIX_VEC()_ADDR, PCM_MSIX_VEC()_CTL, and corresponding
                                                                 bit of PCM_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_PCM_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_msix_vecx_addr_s cn; */
};
typedef union bdk_pcm_msix_vecx_addr bdk_pcm_msix_vecx_addr_t;

static inline uint64_t BDK_PCM_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000f00000ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_MSIX_VECX_ADDR(a) bdk_pcm_msix_vecx_addr_t
#define bustype_BDK_PCM_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_MSIX_VECX_ADDR(a) "PCM_MSIX_VECX_ADDR"
#define device_bar_BDK_PCM_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_PCM_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_PCM_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_msix_vec#_ctl
 *
 * PCM MSI-X Vector Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the PCM_INT_VEC_E enumeration.
 */
union bdk_pcm_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_pcm_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 20; /**< [ 19:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t reserved_20_31        : 12;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_msix_vecx_ctl_s cn; */
};
typedef union bdk_pcm_msix_vecx_ctl bdk_pcm_msix_vecx_ctl_t;

static inline uint64_t BDK_PCM_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000f00008ll + 0x10ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_MSIX_VECX_CTL(a) bdk_pcm_msix_vecx_ctl_t
#define bustype_BDK_PCM_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_MSIX_VECX_CTL(a) "PCM_MSIX_VECX_CTL"
#define device_bar_BDK_PCM_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_PCM_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_PCM_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_dma_cfg
 *
 * PCM DMA Configuration Register
 */
union bdk_pcm_tex_dma_cfg
{
    uint64_t u;
    struct bdk_pcm_tex_dma_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t rdpend                : 1;  /**< [ 63: 63](RO/H) Reads pending.
                                                                 0 = No L2C read responses pending.
                                                                 1 = L2C read responses are outstanding.

                                                                 When restarting after stopping a running TDM engine, software must wait for
                                                                 [RDPEND] to read 0 before writing PCMn_TDM_CFG[ENABLE] to a 1. */
        uint64_t reserved_54_62        : 9;
        uint64_t rxslots               : 10; /**< [ 53: 44](R/W) Number of 8-bit slots to receive per frame (number of slots in a receive
                                                                 superframe).
                                                                 Maximum value is 512 slots. Zero means no slot is provisioned. Note that the sum of all
                                                                 ones in PCM_TE()_RXMASK() must equal the value of this field. */
        uint64_t reserved_42_43        : 2;
        uint64_t txslots               : 10; /**< [ 41: 32](R/W) Number of 8-bit slots to transmit per frame (number of slots in a transmit
                                                                 superframe).
                                                                 Maximum value is 512 slots. Zero means no slot is provisioned. Note that the sum of all
                                                                 ones in PCM_TE()_TXMASK() must equal the value of this field. */
        uint64_t reserved_30_31        : 2;
        uint64_t rxst                  : 10; /**< [ 29: 20](R/W) Number of frame writes for interrupt. */
        uint64_t reserved_19           : 1;
        uint64_t useldt                : 1;  /**< [ 18: 18](R/W) Use LDT.
                                                                 0 = Use LDI command to read from L2C.
                                                                 1 = Use LDT command to read from L2C. */
        uint64_t txrd                  : 10; /**< [ 17:  8](R/W) Number of frame reads for interrupt. */
        uint64_t fetchsiz              : 4;  /**< [  7:  4](R/W) FETCHSIZ+1 timeslots are read when threshold is reached. */
        uint64_t thresh                : 4;  /**< [  3:  0](R/W) If number of bytes remaining in the DMA fifo is \<=
                                                                 [THRESH], initiate a fetch of timeslot data from the
                                                                 transmit memory region.

                                                                 There are only 16B of buffer for each engine
                                                                 so the seetings for [FETCHSIZ] and [THRESH] must be
                                                                 such that the buffer will not be overrun:

                                                                 _ [THRESH] + min([FETCHSIZ] + 1,[TXSLOTS]) must be \<= 16. */
#else /* Word 0 - Little Endian */
        uint64_t thresh                : 4;  /**< [  3:  0](R/W) If number of bytes remaining in the DMA fifo is \<=
                                                                 [THRESH], initiate a fetch of timeslot data from the
                                                                 transmit memory region.

                                                                 There are only 16B of buffer for each engine
                                                                 so the seetings for [FETCHSIZ] and [THRESH] must be
                                                                 such that the buffer will not be overrun:

                                                                 _ [THRESH] + min([FETCHSIZ] + 1,[TXSLOTS]) must be \<= 16. */
        uint64_t fetchsiz              : 4;  /**< [  7:  4](R/W) FETCHSIZ+1 timeslots are read when threshold is reached. */
        uint64_t txrd                  : 10; /**< [ 17:  8](R/W) Number of frame reads for interrupt. */
        uint64_t useldt                : 1;  /**< [ 18: 18](R/W) Use LDT.
                                                                 0 = Use LDI command to read from L2C.
                                                                 1 = Use LDT command to read from L2C. */
        uint64_t reserved_19           : 1;
        uint64_t rxst                  : 10; /**< [ 29: 20](R/W) Number of frame writes for interrupt. */
        uint64_t reserved_30_31        : 2;
        uint64_t txslots               : 10; /**< [ 41: 32](R/W) Number of 8-bit slots to transmit per frame (number of slots in a transmit
                                                                 superframe).
                                                                 Maximum value is 512 slots. Zero means no slot is provisioned. Note that the sum of all
                                                                 ones in PCM_TE()_TXMASK() must equal the value of this field. */
        uint64_t reserved_42_43        : 2;
        uint64_t rxslots               : 10; /**< [ 53: 44](R/W) Number of 8-bit slots to receive per frame (number of slots in a receive
                                                                 superframe).
                                                                 Maximum value is 512 slots. Zero means no slot is provisioned. Note that the sum of all
                                                                 ones in PCM_TE()_RXMASK() must equal the value of this field. */
        uint64_t reserved_54_62        : 9;
        uint64_t rdpend                : 1;  /**< [ 63: 63](RO/H) Reads pending.
                                                                 0 = No L2C read responses pending.
                                                                 1 = L2C read responses are outstanding.

                                                                 When restarting after stopping a running TDM engine, software must wait for
                                                                 [RDPEND] to read 0 before writing PCMn_TDM_CFG[ENABLE] to a 1. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_dma_cfg_s cn; */
};
typedef union bdk_pcm_tex_dma_cfg bdk_pcm_tex_dma_cfg_t;

static inline uint64_t BDK_PCM_TEX_DMA_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_DMA_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000018ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_DMA_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_DMA_CFG(a) bdk_pcm_tex_dma_cfg_t
#define bustype_BDK_PCM_TEX_DMA_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_DMA_CFG(a) "PCM_TEX_DMA_CFG"
#define device_bar_BDK_PCM_TEX_DMA_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_DMA_CFG(a) (a)
#define arguments_BDK_PCM_TEX_DMA_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_int_ena_w1c
 *
 * PCM Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pcm_tex_int_ena_w1c
{
    uint64_t u;
    struct bdk_pcm_tex_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t rxovf                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[RXOVF]. */
        uint64_t txempty               : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[TXEMPTY]. */
        uint64_t txrd                  : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[TXRD]. */
        uint64_t txwrap                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[TXWRAP]. */
        uint64_t rxst                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[RXST]. */
        uint64_t rxwrap                : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[RXWRAP]. */
        uint64_t fsyncextra            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[FSYNCEXTRA]. */
        uint64_t fsyncmissed           : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[FSYNCMISSED]. */
#else /* Word 0 - Little Endian */
        uint64_t fsyncmissed           : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[FSYNCMISSED]. */
        uint64_t fsyncextra            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[FSYNCEXTRA]. */
        uint64_t rxwrap                : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[RXWRAP]. */
        uint64_t rxst                  : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[RXST]. */
        uint64_t txwrap                : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[TXWRAP]. */
        uint64_t txrd                  : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[TXRD]. */
        uint64_t txempty               : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[TXEMPTY]. */
        uint64_t rxovf                 : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PCM_TE(0..3)_INT_SUM[RXOVF]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_int_ena_w1c_s cn; */
};
typedef union bdk_pcm_tex_int_ena_w1c bdk_pcm_tex_int_ena_w1c_t;

static inline uint64_t BDK_PCM_TEX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_INT_ENA_W1C(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000078ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_INT_ENA_W1C", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_INT_ENA_W1C(a) bdk_pcm_tex_int_ena_w1c_t
#define bustype_BDK_PCM_TEX_INT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_INT_ENA_W1C(a) "PCM_TEX_INT_ENA_W1C"
#define device_bar_BDK_PCM_TEX_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_INT_ENA_W1C(a) (a)
#define arguments_BDK_PCM_TEX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_int_ena_w1s
 *
 * PCM Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pcm_tex_int_ena_w1s
{
    uint64_t u;
    struct bdk_pcm_tex_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t rxovf                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[RXOVF]. */
        uint64_t txempty               : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[TXEMPTY]. */
        uint64_t txrd                  : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[TXRD]. */
        uint64_t txwrap                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[TXWRAP]. */
        uint64_t rxst                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[RXST]. */
        uint64_t rxwrap                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[RXWRAP]. */
        uint64_t fsyncextra            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[FSYNCEXTRA]. */
        uint64_t fsyncmissed           : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[FSYNCMISSED]. */
#else /* Word 0 - Little Endian */
        uint64_t fsyncmissed           : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[FSYNCMISSED]. */
        uint64_t fsyncextra            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[FSYNCEXTRA]. */
        uint64_t rxwrap                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[RXWRAP]. */
        uint64_t rxst                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[RXST]. */
        uint64_t txwrap                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[TXWRAP]. */
        uint64_t txrd                  : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[TXRD]. */
        uint64_t txempty               : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[TXEMPTY]. */
        uint64_t rxovf                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PCM_TE(0..3)_INT_SUM[RXOVF]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_int_ena_w1s_s cn; */
};
typedef union bdk_pcm_tex_int_ena_w1s bdk_pcm_tex_int_ena_w1s_t;

static inline uint64_t BDK_PCM_TEX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_INT_ENA_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000070ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_INT_ENA_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_INT_ENA_W1S(a) bdk_pcm_tex_int_ena_w1s_t
#define bustype_BDK_PCM_TEX_INT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_INT_ENA_W1S(a) "PCM_TEX_INT_ENA_W1S"
#define device_bar_BDK_PCM_TEX_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_INT_ENA_W1S(a) (a)
#define arguments_BDK_PCM_TEX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_int_sum
 *
 * PCM Interrupt Summary Register
 */
union bdk_pcm_tex_int_sum
{
    uint64_t u;
    struct bdk_pcm_tex_int_sum_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t rxovf                 : 1;  /**< [  7:  7](R/W1C/H) RX byte overflowed. */
        uint64_t txempty               : 1;  /**< [  6:  6](R/W1C/H) TX byte was empty when sampled. */
        uint64_t txrd                  : 1;  /**< [  5:  5](R/W1C/H) DMA engine frame read interrupt occurred. */
        uint64_t txwrap                : 1;  /**< [  4:  4](R/W1C/H) TX region wrap interrupt occurred. */
        uint64_t rxst                  : 1;  /**< [  3:  3](R/W1C/H) DMA engine frame store interrupt occurred. */
        uint64_t rxwrap                : 1;  /**< [  2:  2](R/W1C/H) RX region wrap interrupt occurred. */
        uint64_t fsyncextra            : 1;  /**< [  1:  1](R/W1C/H) FSYNC extra interrupt occurred. */
        uint64_t fsyncmissed           : 1;  /**< [  0:  0](R/W1C/H) FSYNC missed interrupt occurred. */
#else /* Word 0 - Little Endian */
        uint64_t fsyncmissed           : 1;  /**< [  0:  0](R/W1C/H) FSYNC missed interrupt occurred. */
        uint64_t fsyncextra            : 1;  /**< [  1:  1](R/W1C/H) FSYNC extra interrupt occurred. */
        uint64_t rxwrap                : 1;  /**< [  2:  2](R/W1C/H) RX region wrap interrupt occurred. */
        uint64_t rxst                  : 1;  /**< [  3:  3](R/W1C/H) DMA engine frame store interrupt occurred. */
        uint64_t txwrap                : 1;  /**< [  4:  4](R/W1C/H) TX region wrap interrupt occurred. */
        uint64_t txrd                  : 1;  /**< [  5:  5](R/W1C/H) DMA engine frame read interrupt occurred. */
        uint64_t txempty               : 1;  /**< [  6:  6](R/W1C/H) TX byte was empty when sampled. */
        uint64_t rxovf                 : 1;  /**< [  7:  7](R/W1C/H) RX byte overflowed. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_int_sum_s cn; */
};
typedef union bdk_pcm_tex_int_sum bdk_pcm_tex_int_sum_t;

static inline uint64_t BDK_PCM_TEX_INT_SUM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_INT_SUM(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000028ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_INT_SUM", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_INT_SUM(a) bdk_pcm_tex_int_sum_t
#define bustype_BDK_PCM_TEX_INT_SUM(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_INT_SUM(a) "PCM_TEX_INT_SUM"
#define device_bar_BDK_PCM_TEX_INT_SUM(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_INT_SUM(a) (a)
#define arguments_BDK_PCM_TEX_INT_SUM(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_int_sum_w1s
 *
 * PCM Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pcm_tex_int_sum_w1s
{
    uint64_t u;
    struct bdk_pcm_tex_int_sum_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t rxovf                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[RXOVF]. */
        uint64_t txempty               : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[TXEMPTY]. */
        uint64_t txrd                  : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[TXRD]. */
        uint64_t txwrap                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[TXWRAP]. */
        uint64_t rxst                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[RXST]. */
        uint64_t rxwrap                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[RXWRAP]. */
        uint64_t fsyncextra            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[FSYNCEXTRA]. */
        uint64_t fsyncmissed           : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[FSYNCMISSED]. */
#else /* Word 0 - Little Endian */
        uint64_t fsyncmissed           : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[FSYNCMISSED]. */
        uint64_t fsyncextra            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[FSYNCEXTRA]. */
        uint64_t rxwrap                : 1;  /**< [  2:  2](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[RXWRAP]. */
        uint64_t rxst                  : 1;  /**< [  3:  3](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[RXST]. */
        uint64_t txwrap                : 1;  /**< [  4:  4](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[TXWRAP]. */
        uint64_t txrd                  : 1;  /**< [  5:  5](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[TXRD]. */
        uint64_t txempty               : 1;  /**< [  6:  6](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[TXEMPTY]. */
        uint64_t rxovf                 : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PCM_TE(0..3)_INT_SUM[RXOVF]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_int_sum_w1s_s cn; */
};
typedef union bdk_pcm_tex_int_sum_w1s bdk_pcm_tex_int_sum_w1s_t;

static inline uint64_t BDK_PCM_TEX_INT_SUM_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_INT_SUM_W1S(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000020ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_INT_SUM_W1S", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_INT_SUM_W1S(a) bdk_pcm_tex_int_sum_w1s_t
#define bustype_BDK_PCM_TEX_INT_SUM_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_INT_SUM_W1S(a) "PCM_TEX_INT_SUM_W1S"
#define device_bar_BDK_PCM_TEX_INT_SUM_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_INT_SUM_W1S(a) (a)
#define arguments_BDK_PCM_TEX_INT_SUM_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_rxaddr
 *
 * PCM Receive Address Register
 */
union bdk_pcm_tex_rxaddr
{
    uint64_t u;
    struct bdk_pcm_tex_rxaddr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 49; /**< [ 48:  0](R/W/H) IOVA of the next write to the receive memory region. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 49; /**< [ 48:  0](R/W/H) IOVA of the next write to the receive memory region. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_rxaddr_s cn; */
};
typedef union bdk_pcm_tex_rxaddr bdk_pcm_tex_rxaddr_t;

static inline uint64_t BDK_PCM_TEX_RXADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_RXADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000068ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_RXADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_RXADDR(a) bdk_pcm_tex_rxaddr_t
#define bustype_BDK_PCM_TEX_RXADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_RXADDR(a) "PCM_TEX_RXADDR"
#define device_bar_BDK_PCM_TEX_RXADDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_RXADDR(a) (a)
#define arguments_BDK_PCM_TEX_RXADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_rxcnt
 *
 * PCM Receive Superframe Count Register
 */
union bdk_pcm_tex_rxcnt
{
    uint64_t u;
    struct bdk_pcm_tex_rxcnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t cnt                   : 16; /**< [ 15:  0](R/W) Number of superframes in receive memory region. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 16; /**< [ 15:  0](R/W) Number of superframes in receive memory region. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_rxcnt_s cn; */
};
typedef union bdk_pcm_tex_rxcnt bdk_pcm_tex_rxcnt_t;

static inline uint64_t BDK_PCM_TEX_RXCNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_RXCNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000060ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_RXCNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_RXCNT(a) bdk_pcm_tex_rxcnt_t
#define bustype_BDK_PCM_TEX_RXCNT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_RXCNT(a) "PCM_TEX_RXCNT"
#define device_bar_BDK_PCM_TEX_RXCNT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_RXCNT(a) (a)
#define arguments_BDK_PCM_TEX_RXCNT(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_rxmsk#
 *
 * PCM Recieve Bit Masks Register
 */
union bdk_pcm_tex_rxmskx
{
    uint64_t u;
    struct bdk_pcm_tex_rxmskx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mask                  : 64; /**< [ 63:  0](R/W) Receive mask bits.
                                                                 (1 means transmit, 0 means don't transmit):
                                                                 _ MASK\<0\> covers slots  63 to   0.
                                                                 _ MASK\<1\> covers slots 127 to  64.
                                                                 _ MASK\<2\> covers slots 191 to 128.
                                                                 _ MASK\<3\> covers slots 255 to 192.
                                                                 _ MASK\<4\> covers slots 319 to 256.
                                                                 _ MASK\<5\> covers slots 383 to 320.
                                                                 _ MASK\<6\> covers slots 447 to 384.
                                                                 _ MASK\<7\> covers slots 511 to 448. */
#else /* Word 0 - Little Endian */
        uint64_t mask                  : 64; /**< [ 63:  0](R/W) Receive mask bits.
                                                                 (1 means transmit, 0 means don't transmit):
                                                                 _ MASK\<0\> covers slots  63 to   0.
                                                                 _ MASK\<1\> covers slots 127 to  64.
                                                                 _ MASK\<2\> covers slots 191 to 128.
                                                                 _ MASK\<3\> covers slots 255 to 192.
                                                                 _ MASK\<4\> covers slots 319 to 256.
                                                                 _ MASK\<5\> covers slots 383 to 320.
                                                                 _ MASK\<6\> covers slots 447 to 384.
                                                                 _ MASK\<7\> covers slots 511 to 448. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_rxmskx_s cn; */
};
typedef union bdk_pcm_tex_rxmskx bdk_pcm_tex_rxmskx_t;

static inline uint64_t BDK_PCM_TEX_RXMSKX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_RXMSKX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=3) && (b<=7)))
        return 0x8060000000c0ll + 0x10000ll * ((a) & 0x3) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("PCM_TEX_RXMSKX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_RXMSKX(a,b) bdk_pcm_tex_rxmskx_t
#define bustype_BDK_PCM_TEX_RXMSKX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_RXMSKX(a,b) "PCM_TEX_RXMSKX"
#define device_bar_BDK_PCM_TEX_RXMSKX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_RXMSKX(a,b) (a)
#define arguments_BDK_PCM_TEX_RXMSKX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pcm_te#_rxstart
 *
 * PCM Receive Start Address Register
 */
union bdk_pcm_tex_rxstart
{
    uint64_t u;
    struct bdk_pcm_tex_rxstart_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 46; /**< [ 48:  3](R/W) Starting IOVA for the receive memory region. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t addr                  : 46; /**< [ 48:  3](R/W) Starting IOVA for the receive memory region. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_rxstart_s cn; */
};
typedef union bdk_pcm_tex_rxstart bdk_pcm_tex_rxstart_t;

static inline uint64_t BDK_PCM_TEX_RXSTART(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_RXSTART(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000058ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_RXSTART", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_RXSTART(a) bdk_pcm_tex_rxstart_t
#define bustype_BDK_PCM_TEX_RXSTART(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_RXSTART(a) "PCM_TEX_RXSTART"
#define device_bar_BDK_PCM_TEX_RXSTART(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_RXSTART(a) (a)
#define arguments_BDK_PCM_TEX_RXSTART(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_tdm_cfg
 *
 * PCM TDM Configuration Register
 */
union bdk_pcm_tex_tdm_cfg
{
    uint64_t u;
    struct bdk_pcm_tex_tdm_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t drvtim                : 16; /**< [ 63: 48](R/W) Number of  coprocessor clocks from start of bit time to stop driving last bit
                                                                 of timeslot (if not driving next timeslot). */
        uint64_t samppt                : 16; /**< [ 47: 32](R/W) Number of  coprocessor clocks from start of bit time to sample data bit. */
        uint64_t reserved_3_31         : 29;
        uint64_t lsbfirst              : 1;  /**< [  2:  2](R/W) LSB first.
                                                                 0 = Shift/receive MSB first.
                                                                 1 = Shift/receive LSB first. */
        uint64_t useclk1               : 1;  /**< [  1:  1](R/W) Use CLK1.
                                                                 0 = PCM is based on BCLK/FSYNC0.
                                                                 1 = PCM is based on BCLK/FSYNC1. */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) PCM is enabled, if clear pins are GPIOs.

                                                                 When TDM is disabled by detection of an FSYNC error all transmission and
                                                                 reception is halted.  In addition, PCMn_TX/RXADDR are updated to point to the
                                                                 position at which the error was detected. Software needs to restart the
                                                                 reinitialization sequence after error serviced. */
#else /* Word 0 - Little Endian */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) PCM is enabled, if clear pins are GPIOs.

                                                                 When TDM is disabled by detection of an FSYNC error all transmission and
                                                                 reception is halted.  In addition, PCMn_TX/RXADDR are updated to point to the
                                                                 position at which the error was detected. Software needs to restart the
                                                                 reinitialization sequence after error serviced. */
        uint64_t useclk1               : 1;  /**< [  1:  1](R/W) Use CLK1.
                                                                 0 = PCM is based on BCLK/FSYNC0.
                                                                 1 = PCM is based on BCLK/FSYNC1. */
        uint64_t lsbfirst              : 1;  /**< [  2:  2](R/W) LSB first.
                                                                 0 = Shift/receive MSB first.
                                                                 1 = Shift/receive LSB first. */
        uint64_t reserved_3_31         : 29;
        uint64_t samppt                : 16; /**< [ 47: 32](R/W) Number of  coprocessor clocks from start of bit time to sample data bit. */
        uint64_t drvtim                : 16; /**< [ 63: 48](R/W) Number of  coprocessor clocks from start of bit time to stop driving last bit
                                                                 of timeslot (if not driving next timeslot). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_tdm_cfg_s cn; */
};
typedef union bdk_pcm_tex_tdm_cfg bdk_pcm_tex_tdm_cfg_t;

static inline uint64_t BDK_PCM_TEX_TDM_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_TDM_CFG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000010ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_TDM_CFG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_TDM_CFG(a) bdk_pcm_tex_tdm_cfg_t
#define bustype_BDK_PCM_TEX_TDM_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_TDM_CFG(a) "PCM_TEX_TDM_CFG"
#define device_bar_BDK_PCM_TEX_TDM_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_TDM_CFG(a) (a)
#define arguments_BDK_PCM_TEX_TDM_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_tdm_dbg
 *
 * INTERNAL: PCM TDM Debug Information Register
 */
union bdk_pcm_tex_tdm_dbg
{
    uint64_t u;
    struct bdk_pcm_tex_tdm_dbg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t debuginfo             : 64; /**< [ 63:  0](RO/H) Miscellaneous debug information */
#else /* Word 0 - Little Endian */
        uint64_t debuginfo             : 64; /**< [ 63:  0](RO/H) Miscellaneous debug information */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_tdm_dbg_s cn; */
};
typedef union bdk_pcm_tex_tdm_dbg bdk_pcm_tex_tdm_dbg_t;

static inline uint64_t BDK_PCM_TEX_TDM_DBG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_TDM_DBG(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000030ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_TDM_DBG", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_TDM_DBG(a) bdk_pcm_tex_tdm_dbg_t
#define bustype_BDK_PCM_TEX_TDM_DBG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_TDM_DBG(a) "PCM_TEX_TDM_DBG"
#define device_bar_BDK_PCM_TEX_TDM_DBG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_TDM_DBG(a) (a)
#define arguments_BDK_PCM_TEX_TDM_DBG(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_txaddr
 *
 * PCM Transmit Address Register
 */
union bdk_pcm_tex_txaddr
{
    uint64_t u;
    struct bdk_pcm_tex_txaddr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 46; /**< [ 48:  3](R/W/H) IOVA of the next read from the transmit memory region. */
        uint64_t fram                  : 3;  /**< [  2:  0](R/W/H) Frame offset. Used to extract the correct byte from each 64-bit word read from
                                                                 the transmit memory region. */
#else /* Word 0 - Little Endian */
        uint64_t fram                  : 3;  /**< [  2:  0](R/W/H) Frame offset. Used to extract the correct byte from each 64-bit word read from
                                                                 the transmit memory region. */
        uint64_t addr                  : 46; /**< [ 48:  3](R/W/H) IOVA of the next read from the transmit memory region. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_txaddr_s cn; */
};
typedef union bdk_pcm_tex_txaddr bdk_pcm_tex_txaddr_t;

static inline uint64_t BDK_PCM_TEX_TXADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_TXADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000050ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_TXADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_TXADDR(a) bdk_pcm_tex_txaddr_t
#define bustype_BDK_PCM_TEX_TXADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_TXADDR(a) "PCM_TEX_TXADDR"
#define device_bar_BDK_PCM_TEX_TXADDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_TXADDR(a) (a)
#define arguments_BDK_PCM_TEX_TXADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_txcnt
 *
 * PCM Superframe Transmit Count Register
 */
union bdk_pcm_tex_txcnt
{
    uint64_t u;
    struct bdk_pcm_tex_txcnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t cnt                   : 16; /**< [ 15:  0](R/W) Number of superframes in transmit memory region. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 16; /**< [ 15:  0](R/W) Number of superframes in transmit memory region. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_txcnt_s cn; */
};
typedef union bdk_pcm_tex_txcnt bdk_pcm_tex_txcnt_t;

static inline uint64_t BDK_PCM_TEX_TXCNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_TXCNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000048ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_TXCNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_TXCNT(a) bdk_pcm_tex_txcnt_t
#define bustype_BDK_PCM_TEX_TXCNT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_TXCNT(a) "PCM_TEX_TXCNT"
#define device_bar_BDK_PCM_TEX_TXCNT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_TXCNT(a) (a)
#define arguments_BDK_PCM_TEX_TXCNT(a) (a),-1,-1,-1

/**
 * Register (NCB) pcm_te#_txmsk#
 *
 * PCM Transmit Bit Masks Register
 */
union bdk_pcm_tex_txmskx
{
    uint64_t u;
    struct bdk_pcm_tex_txmskx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t mask                  : 64; /**< [ 63:  0](R/W) Transmit mask bits.
                                                                 (1 means transmit, 0 means don't transmit):
                                                                 _ MASK\<0\> covers slots  63 to   0.
                                                                 _ MASK\<1\> covers slots 127 to  64.
                                                                 _ MASK\<2\> covers slots 191 to 128.
                                                                 _ MASK\<3\> covers slots 255 to 192.
                                                                 _ MASK\<4\> covers slots 319 to 256.
                                                                 _ MASK\<5\> covers slots 383 to 320.
                                                                 _ MASK\<6\> covers slots 447 to 384.
                                                                 _ MASK\<7\> covers slots 511 to 448.

                                                                 Updating this register while DMA engine is running for setup or teardown of time
                                                                 slots is not supported; dynamic changes to this register will result in
                                                                 erroneous behavior on the interface. */
#else /* Word 0 - Little Endian */
        uint64_t mask                  : 64; /**< [ 63:  0](R/W) Transmit mask bits.
                                                                 (1 means transmit, 0 means don't transmit):
                                                                 _ MASK\<0\> covers slots  63 to   0.
                                                                 _ MASK\<1\> covers slots 127 to  64.
                                                                 _ MASK\<2\> covers slots 191 to 128.
                                                                 _ MASK\<3\> covers slots 255 to 192.
                                                                 _ MASK\<4\> covers slots 319 to 256.
                                                                 _ MASK\<5\> covers slots 383 to 320.
                                                                 _ MASK\<6\> covers slots 447 to 384.
                                                                 _ MASK\<7\> covers slots 511 to 448.

                                                                 Updating this register while DMA engine is running for setup or teardown of time
                                                                 slots is not supported; dynamic changes to this register will result in
                                                                 erroneous behavior on the interface. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_txmskx_s cn; */
};
typedef union bdk_pcm_tex_txmskx bdk_pcm_tex_txmskx_t;

static inline uint64_t BDK_PCM_TEX_TXMSKX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_TXMSKX(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && ((a<=3) && (b<=7)))
        return 0x806000000080ll + 0x10000ll * ((a) & 0x3) + 8ll * ((b) & 0x7);
    __bdk_csr_fatal("PCM_TEX_TXMSKX", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_TXMSKX(a,b) bdk_pcm_tex_txmskx_t
#define bustype_BDK_PCM_TEX_TXMSKX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_TXMSKX(a,b) "PCM_TEX_TXMSKX"
#define device_bar_BDK_PCM_TEX_TXMSKX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_TXMSKX(a,b) (a)
#define arguments_BDK_PCM_TEX_TXMSKX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) pcm_te#_txstart
 *
 * PCM Transmit Start Address Register
 */
union bdk_pcm_tex_txstart
{
    uint64_t u;
    struct bdk_pcm_tex_txstart_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 46; /**< [ 48:  3](R/W) Starting IOVA for the transmit memory region. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t addr                  : 46; /**< [ 48:  3](R/W) Starting IOVA for the transmit memory region. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pcm_tex_txstart_s cn; */
};
typedef union bdk_pcm_tex_txstart bdk_pcm_tex_txstart_t;

static inline uint64_t BDK_PCM_TEX_TXSTART(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PCM_TEX_TXSTART(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN81XX) && (a<=3))
        return 0x806000000040ll + 0x10000ll * ((a) & 0x3);
    __bdk_csr_fatal("PCM_TEX_TXSTART", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_PCM_TEX_TXSTART(a) bdk_pcm_tex_txstart_t
#define bustype_BDK_PCM_TEX_TXSTART(a) BDK_CSR_TYPE_NCB
#define basename_BDK_PCM_TEX_TXSTART(a) "PCM_TEX_TXSTART"
#define device_bar_BDK_PCM_TEX_TXSTART(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PCM_TEX_TXSTART(a) (a)
#define arguments_BDK_PCM_TEX_TXSTART(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_PCM_H__ */
