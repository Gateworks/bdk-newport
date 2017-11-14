#ifndef __BDK_CSRS_PBUS_H__
#define __BDK_CSRS_PBUS_H__
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
 * Cavium PBUS.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration pbus_bar_e
 *
 * PBUS Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_PBUS_BAR_E_PBUS_PF_BAR0_CN8 (0x87e001000000ll)
#define BDK_PBUS_BAR_E_PBUS_PF_BAR0_CN8_SIZE 0x800000ull
#define BDK_PBUS_BAR_E_PBUS_PF_BAR0_CN9 (0x87e001000000ll)
#define BDK_PBUS_BAR_E_PBUS_PF_BAR0_CN9_SIZE 0x100000ull
#define BDK_PBUS_BAR_E_PBUS_PF_BAR2 (0x800000000000ll)
#define BDK_PBUS_BAR_E_PBUS_PF_BAR2_SIZE 0x100000000ull
#define BDK_PBUS_BAR_E_PBUS_PF_BAR4 (0x87e001f00000ll)
#define BDK_PBUS_BAR_E_PBUS_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration pbus_int_vec_e
 *
 * PBUS MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_PBUS_INT_VEC_E_ADR_ERR (0)
#define BDK_PBUS_INT_VEC_E_DMA_DONEX(a) (2 + (a))
#define BDK_PBUS_INT_VEC_E_NCB_FLT (4)
#define BDK_PBUS_INT_VEC_E_NCB_RAS (5)
#define BDK_PBUS_INT_VEC_E_WAIT_ERR (1)

/**
 * Register (RSL) pbus_debug
 *
 * PBUS Debug Register
 */
union bdk_pbus_debug
{
    uint64_t u;
    struct bdk_pbus_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_21_63        : 43;
        uint64_t bus_sm                : 5;  /**< [ 20: 16](RO) Pbus state.
                                                                 For diagnostic use only. */
        uint64_t dma_sm                : 4;  /**< [ 15: 12](RO) DMA state.
                                                                 For diagnostic use only. */
        uint64_t reserved_11           : 1;
        uint64_t ncb_sm                : 3;  /**< [ 10:  8](RO) Data transfer state.
                                                                 For diagnostic use only. */
        uint64_t reserved_1_7          : 7;
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force PBUS related conditional clocks to always be on.
                                                                 For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force PBUS related conditional clocks to always be on.
                                                                 For diagnostic use only. */
        uint64_t reserved_1_7          : 7;
        uint64_t ncb_sm                : 3;  /**< [ 10:  8](RO) Data transfer state.
                                                                 For diagnostic use only. */
        uint64_t reserved_11           : 1;
        uint64_t dma_sm                : 4;  /**< [ 15: 12](RO) DMA state.
                                                                 For diagnostic use only. */
        uint64_t bus_sm                : 5;  /**< [ 20: 16](RO) Pbus state.
                                                                 For diagnostic use only. */
        uint64_t reserved_21_63        : 43;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pbus_debug_s cn; */
};
typedef union bdk_pbus_debug bdk_pbus_debug_t;

#define BDK_PBUS_DEBUG BDK_PBUS_DEBUG_FUNC()
static inline uint64_t BDK_PBUS_DEBUG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_DEBUG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0010001f0ll;
    __bdk_csr_fatal("PBUS_DEBUG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PBUS_DEBUG bdk_pbus_debug_t
#define bustype_BDK_PBUS_DEBUG BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_DEBUG "PBUS_DEBUG"
#define device_bar_BDK_PBUS_DEBUG 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_DEBUG 0
#define arguments_BDK_PBUS_DEBUG -1,-1,-1,-1

/**
 * Register (RSL) pbus_dma_adr#
 *
 * PBUS DMA Engine Address Registers
 * This register sets each DMA engine address.
 */
union bdk_pbus_dma_adrx
{
    uint64_t u;
    struct bdk_pbus_dma_adrx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t adr                   : 53; /**< [ 52:  0](R/W/H) DMA engine 0-1 IOVA. This value must be aligned to the bus width (i.e. 16-bit aligned
                                                                 if WIDTH=0, 32-bit aligned if WIDTH=1). */
#else /* Word 0 - Little Endian */
        uint64_t adr                   : 53; /**< [ 52:  0](R/W/H) DMA engine 0-1 IOVA. This value must be aligned to the bus width (i.e. 16-bit aligned
                                                                 if WIDTH=0, 32-bit aligned if WIDTH=1). */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_pbus_dma_adrx_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t adr                   : 49; /**< [ 48:  0](R/W/H) DMA engine 0-1 IOVA. This value must be aligned to the bus width (i.e. 16-bit aligned
                                                                 if WIDTH=0, 32-bit aligned if WIDTH=1). */
#else /* Word 0 - Little Endian */
        uint64_t adr                   : 49; /**< [ 48:  0](R/W/H) DMA engine 0-1 IOVA. This value must be aligned to the bus width (i.e. 16-bit aligned
                                                                 if WIDTH=0, 32-bit aligned if WIDTH=1). */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_pbus_dma_adrx_s cn9; */
};
typedef union bdk_pbus_dma_adrx bdk_pbus_dma_adrx_t;

static inline uint64_t BDK_PBUS_DMA_ADRX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_DMA_ADRX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=1))
        return 0x87e001000110ll + 8ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x87e001000110ll + 8ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e001000110ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("PBUS_DMA_ADRX", 1, a, 0, 0, 0);
}

#define typedef_BDK_PBUS_DMA_ADRX(a) bdk_pbus_dma_adrx_t
#define bustype_BDK_PBUS_DMA_ADRX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_DMA_ADRX(a) "PBUS_DMA_ADRX"
#define device_bar_BDK_PBUS_DMA_ADRX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_DMA_ADRX(a) (a)
#define arguments_BDK_PBUS_DMA_ADRX(a) (a),-1,-1,-1

/**
 * Register (RSL) pbus_dma_cfg#
 *
 * PBUS DMA Engine Configuration Registers
 * This register configures each DMA engine.
 *
 * Care must be taken to ensure that the DMA duration not exceed the processor timeout of 2^29
 * core clocks or the RML timeout specified in MRML_INT_LOCAL_TO if
 * accesses to the PBUS occur while DMA operations are in progress.
 * The DMA operation duration in coprocessor clock cycles as:
 *   _ PBUS_DMA_CFG()[SIZE] * PBUS_DMA_TIM()[TIM_MULT] * cycle_time.
 *
 * Where:
 *
 *   _ cycle_time = PBUS_DMA_TIM()[RD_DLY] + PBUS_DMA_TIM()[PAUSE]
 *                  + PBUS_DMA_TIM()[DMACK_H] + PBUS_DMA_TIM()[WE_N]
 *                  + PBUS_DMA_TIM()[WE_A] + PBUS_DMA_TIM()[OE_N]
 *                  + PBUS_DMA_TIM()[OE_A] + PBUS_DMA_TIM()[DMACK_S].
 *
 * Coprocessor clock cycles can be converted to core clock cycles by multiplying the value
 * by the clock ratio RST_BOOT[C_MUL] / RST_BOOT[PNR_MUL].
 */
union bdk_pbus_dma_cfgx
{
    uint64_t u;
    struct bdk_pbus_dma_cfgx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t en                    : 1;  /**< [ 63: 63](R/W/H) DMA engine enable. */
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W) DMA engine R/W bit (0 = read, 1 = write). */
        uint64_t clr                   : 1;  /**< [ 61: 61](R/W) DMA engine clear operation on device terminated burst. */
        uint64_t reserved_60           : 1;
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W) DMA engine 32-bit swap. See [BIG]. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W) DMA engine 16-bit swap. See [BIG]. */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W) DMA engine 8-bit swap. See [BIG]. */
        uint64_t big                   : 1;  /**< [ 56: 56](R/W) DMA engine big endian mode (1 = big, 0 = little).
                                                                 Using 0..7 to identify bytes:
                                                                 \<pre\>
                                                                 [SWAP32] [SWAP16] [SWAP8] [BIG]     Result
                                                                    0        0        0      0       7 6 5 4 3 2 1 0
                                                                    0        0        1      0       6 7 4 5 2 3 0 1
                                                                    0        1        0      0       5 4 7 6 1 0 3 2
                                                                    1        0        0      0       3 2 1 0 7 6 5 4
                                                                    0        0        0      1       0 1 2 3 4 5 6 7
                                                                    0        0        1      1       1 0 3 2 5 4 7 6
                                                                    0        1        0      1       2 3 0 1 6 7 4 5
                                                                    1        0        0      1       4 5 6 7 0 1 2 3
                                                                 \</pre\> */
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine 0-1 size. [SIZE] is specified in number of bus transfers, where one transfer is
                                                                 equal to the following number of bytes, dependent on PBUS_DMA_TIM()[WIDTH] and
                                                                 PBUS_DMA_TIM()[DDR]:
                                                                 _ If WIDTH=0, DDR=0, then transfer is 2 bytes.
                                                                 _ If WIDTH=0, DDR=1, then transfer is 4 bytes.
                                                                 _ If WIDTH=1, DDR=0, then transfer is 4 bytes.
                                                                 _ If WIDTH=1, DDR=1, then transfer is 8 bytes. */
        uint64_t reserved_0_35         : 36;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_35         : 36;
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine 0-1 size. [SIZE] is specified in number of bus transfers, where one transfer is
                                                                 equal to the following number of bytes, dependent on PBUS_DMA_TIM()[WIDTH] and
                                                                 PBUS_DMA_TIM()[DDR]:
                                                                 _ If WIDTH=0, DDR=0, then transfer is 2 bytes.
                                                                 _ If WIDTH=0, DDR=1, then transfer is 4 bytes.
                                                                 _ If WIDTH=1, DDR=0, then transfer is 4 bytes.
                                                                 _ If WIDTH=1, DDR=1, then transfer is 8 bytes. */
        uint64_t big                   : 1;  /**< [ 56: 56](R/W) DMA engine big endian mode (1 = big, 0 = little).
                                                                 Using 0..7 to identify bytes:
                                                                 \<pre\>
                                                                 [SWAP32] [SWAP16] [SWAP8] [BIG]     Result
                                                                    0        0        0      0       7 6 5 4 3 2 1 0
                                                                    0        0        1      0       6 7 4 5 2 3 0 1
                                                                    0        1        0      0       5 4 7 6 1 0 3 2
                                                                    1        0        0      0       3 2 1 0 7 6 5 4
                                                                    0        0        0      1       0 1 2 3 4 5 6 7
                                                                    0        0        1      1       1 0 3 2 5 4 7 6
                                                                    0        1        0      1       2 3 0 1 6 7 4 5
                                                                    1        0        0      1       4 5 6 7 0 1 2 3
                                                                 \</pre\> */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W) DMA engine 8-bit swap. See [BIG]. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W) DMA engine 16-bit swap. See [BIG]. */
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W) DMA engine 32-bit swap. See [BIG]. */
        uint64_t reserved_60           : 1;
        uint64_t clr                   : 1;  /**< [ 61: 61](R/W) DMA engine clear operation on device terminated burst. */
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W) DMA engine R/W bit (0 = read, 1 = write). */
        uint64_t en                    : 1;  /**< [ 63: 63](R/W/H) DMA engine enable. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pbus_dma_cfgx_s cn; */
};
typedef union bdk_pbus_dma_cfgx bdk_pbus_dma_cfgx_t;

static inline uint64_t BDK_PBUS_DMA_CFGX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_DMA_CFGX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=1))
        return 0x87e001000100ll + 8ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x87e001000100ll + 8ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e001000100ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("PBUS_DMA_CFGX", 1, a, 0, 0, 0);
}

#define typedef_BDK_PBUS_DMA_CFGX(a) bdk_pbus_dma_cfgx_t
#define bustype_BDK_PBUS_DMA_CFGX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_DMA_CFGX(a) "PBUS_DMA_CFGX"
#define device_bar_BDK_PBUS_DMA_CFGX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_DMA_CFGX(a) (a)
#define arguments_BDK_PBUS_DMA_CFGX(a) (a),-1,-1,-1

/**
 * Register (RSL) pbus_dma_tim#
 *
 * PBUS DMA Engine Timing Registers
 * This register sets each DMA engine's timing.
 */
union bdk_pbus_dma_timx
{
    uint64_t u;
    struct bdk_pbus_dma_timx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t tim_mult              : 2;  /**< [ 61: 60](R/W) Timing multiplier. This field specifies the timing multiplier for an engine. The timing
                                                                 multiplier applies to all timing parameters, except for [DMARQ] and [RD_DLY], which simply
                                                                 count coprocessor-clock cycles. [TIM_MULT] is encoded as follows:
                                                                   0x0 = 4x multiplier.
                                                                   0x1 = 1x multiplier.
                                                                   0x2 = 2x multiplier.
                                                                   0x3 = 8x multiplier. */
        uint64_t rd_dly                : 3;  /**< [ 59: 57](R/W) Read sample delay. This field specifies the read sample delay in coprocessor-clock cycles
                                                                 for an engine. For read operations, the data bus is normally sampled on the same
                                                                 coprocessor-clock edge that drives PBUS_OE inactive (and also active in DDR mode). This
                                                                 parameter can delay that sampling edge by up to seven coprocessor-clock cycles.
                                                                 The number of coprocessor-clock cycles counted by the [OE_A] and [DMACK_H] +
                                                                 [PAUSE] timing parameters must be greater than [RD_DLY]. */
        uint64_t ddr                   : 1;  /**< [ 56: 56](R/W) DDR mode. If one, then [WE_N] must be less than [WE_A]. */
        uint64_t width                 : 1;  /**< [ 55: 55](R/W) DMA bus width (0 = 16 bits, 1 = 32 bits). */
        uint64_t reserved_48_54        : 7;
        uint64_t pause                 : 6;  /**< [ 47: 42](R/W) Pause count. */
        uint64_t dmack_h               : 6;  /**< [ 41: 36](R/W) DMA acknowledgment hold count. */
        uint64_t we_n                  : 6;  /**< [ 35: 30](R/W) Write enable negated count. */
        uint64_t we_a                  : 6;  /**< [ 29: 24](R/W) Write enable asserted count. */
        uint64_t oe_n                  : 6;  /**< [ 23: 18](R/W) Output enable negated count. */
        uint64_t oe_a                  : 6;  /**< [ 17: 12](R/W) Output enable asserted count. */
        uint64_t dmack_s               : 6;  /**< [ 11:  6](R/W) DMA acknowledgment setup count. */
        uint64_t dmarq                 : 6;  /**< [  5:  0](R/W) DMA request glitch filter count. Number of coprocessor clocks
                                                                 the DMA request must be active before request is recognized.
                                                                 (Must be nonzero.) */
#else /* Word 0 - Little Endian */
        uint64_t dmarq                 : 6;  /**< [  5:  0](R/W) DMA request glitch filter count. Number of coprocessor clocks
                                                                 the DMA request must be active before request is recognized.
                                                                 (Must be nonzero.) */
        uint64_t dmack_s               : 6;  /**< [ 11:  6](R/W) DMA acknowledgment setup count. */
        uint64_t oe_a                  : 6;  /**< [ 17: 12](R/W) Output enable asserted count. */
        uint64_t oe_n                  : 6;  /**< [ 23: 18](R/W) Output enable negated count. */
        uint64_t we_a                  : 6;  /**< [ 29: 24](R/W) Write enable asserted count. */
        uint64_t we_n                  : 6;  /**< [ 35: 30](R/W) Write enable negated count. */
        uint64_t dmack_h               : 6;  /**< [ 41: 36](R/W) DMA acknowledgment hold count. */
        uint64_t pause                 : 6;  /**< [ 47: 42](R/W) Pause count. */
        uint64_t reserved_48_54        : 7;
        uint64_t width                 : 1;  /**< [ 55: 55](R/W) DMA bus width (0 = 16 bits, 1 = 32 bits). */
        uint64_t ddr                   : 1;  /**< [ 56: 56](R/W) DDR mode. If one, then [WE_N] must be less than [WE_A]. */
        uint64_t rd_dly                : 3;  /**< [ 59: 57](R/W) Read sample delay. This field specifies the read sample delay in coprocessor-clock cycles
                                                                 for an engine. For read operations, the data bus is normally sampled on the same
                                                                 coprocessor-clock edge that drives PBUS_OE inactive (and also active in DDR mode). This
                                                                 parameter can delay that sampling edge by up to seven coprocessor-clock cycles.
                                                                 The number of coprocessor-clock cycles counted by the [OE_A] and [DMACK_H] +
                                                                 [PAUSE] timing parameters must be greater than [RD_DLY]. */
        uint64_t tim_mult              : 2;  /**< [ 61: 60](R/W) Timing multiplier. This field specifies the timing multiplier for an engine. The timing
                                                                 multiplier applies to all timing parameters, except for [DMARQ] and [RD_DLY], which simply
                                                                 count coprocessor-clock cycles. [TIM_MULT] is encoded as follows:
                                                                   0x0 = 4x multiplier.
                                                                   0x1 = 1x multiplier.
                                                                   0x2 = 2x multiplier.
                                                                   0x3 = 8x multiplier. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pbus_dma_timx_s cn; */
};
typedef union bdk_pbus_dma_timx bdk_pbus_dma_timx_t;

static inline uint64_t BDK_PBUS_DMA_TIMX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_DMA_TIMX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=1))
        return 0x87e001000120ll + 8ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=1))
        return 0x87e001000120ll + 8ll * ((a) & 0x1);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x87e001000120ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("PBUS_DMA_TIMX", 1, a, 0, 0, 0);
}

#define typedef_BDK_PBUS_DMA_TIMX(a) bdk_pbus_dma_timx_t
#define bustype_BDK_PBUS_DMA_TIMX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_DMA_TIMX(a) "PBUS_DMA_TIMX"
#define device_bar_BDK_PBUS_DMA_TIMX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_DMA_TIMX(a) (a)
#define arguments_BDK_PBUS_DMA_TIMX(a) (a),-1,-1,-1

/**
 * Register (RSL) pbus_eco
 *
 * INTERNAL: PBUS ECO Register
 */
union bdk_pbus_eco
{
    uint64_t u;
    struct bdk_pbus_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pbus_eco_s cn; */
};
typedef union bdk_pbus_eco bdk_pbus_eco_t;

#define BDK_PBUS_ECO BDK_PBUS_ECO_FUNC()
static inline uint64_t BDK_PBUS_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_ECO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
        return 0x87e0010001f8ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
        return 0x87e0010001f8ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0010001f8ll;
    __bdk_csr_fatal("PBUS_ECO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PBUS_ECO bdk_pbus_eco_t
#define bustype_BDK_PBUS_ECO BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_ECO "PBUS_ECO"
#define device_bar_BDK_PBUS_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_ECO 0
#define arguments_BDK_PBUS_ECO -1,-1,-1,-1

/**
 * Register (RSL) pbus_int
 *
 * PBUS Interupt Register
 * This register contains the PBUS DMA and error interrupts.
 */
union bdk_pbus_int
{
    uint64_t u;
    struct bdk_pbus_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1C/H) Poisoned read data received on NCB read request.
                                                                 This error will typically be handled by the SCP. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1C/H) Fault received on NCB read request. */
        uint64_t reserved_6            : 1;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1C/H) DMA engine n request completion interrupt. */
        uint64_t reserved_2_3          : 2;
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1C/H) Wait mode error. This bit is set when wait mode is enabled
                                                                 and the external wait signal is not deasserted after 32K
                                                                 coprocessor-clock cycles. */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1C/H) Address decode error. This bit is set when a PBUS access
                                                                 does not hit in any of the eight remote regions. */
#else /* Word 0 - Little Endian */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1C/H) Address decode error. This bit is set when a PBUS access
                                                                 does not hit in any of the eight remote regions. */
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1C/H) Wait mode error. This bit is set when wait mode is enabled
                                                                 and the external wait signal is not deasserted after 32K
                                                                 coprocessor-clock cycles. */
        uint64_t reserved_2_3          : 2;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1C/H) DMA engine n request completion interrupt. */
        uint64_t reserved_6            : 1;
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1C/H) Fault received on NCB read request. */
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1C/H) Poisoned read data received on NCB read request.
                                                                 This error will typically be handled by the SCP. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    struct bdk_pbus_int_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1C/H) DMA engine n request completion interrupt. */
        uint64_t reserved_2_3          : 2;
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1C/H) Wait mode error. This bit is set when wait mode is enabled
                                                                 and the external wait signal is not deasserted after 32K
                                                                 coprocessor-clock cycles. */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1C/H) Address decode error. This bit is set when a PBUS access
                                                                 does not hit in any of the eight remote regions. */
#else /* Word 0 - Little Endian */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1C/H) Address decode error. This bit is set when a PBUS access
                                                                 does not hit in any of the eight remote regions. */
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1C/H) Wait mode error. This bit is set when wait mode is enabled
                                                                 and the external wait signal is not deasserted after 32K
                                                                 coprocessor-clock cycles. */
        uint64_t reserved_2_3          : 2;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1C/H) DMA engine n request completion interrupt. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_pbus_int_s cn9; */
};
typedef union bdk_pbus_int bdk_pbus_int_t;

#define BDK_PBUS_INT BDK_PBUS_INT_FUNC()
static inline uint64_t BDK_PBUS_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_INT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
        return 0x87e001000080ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
        return 0x87e001000080ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e001000080ll;
    __bdk_csr_fatal("PBUS_INT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PBUS_INT bdk_pbus_int_t
#define bustype_BDK_PBUS_INT BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_INT "PBUS_INT"
#define device_bar_BDK_PBUS_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_INT 0
#define arguments_BDK_PBUS_INT -1,-1,-1,-1

/**
 * Register (RSL) pbus_int_ena_w1c
 *
 * PBUS Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_pbus_int_ena_w1c
{
    uint64_t u;
    struct bdk_pbus_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for PBUS_INT[NCB_RAS]. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PBUS_INT[NCB_FLT]. */
        uint64_t reserved_6            : 1;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1C/H) Reads or clears enable for PBUS_INT[DMA_DONE]. */
        uint64_t reserved_2_3          : 2;
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PBUS_INT[WAIT_ERR]. */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PBUS_INT[ADR_ERR]. */
#else /* Word 0 - Little Endian */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PBUS_INT[ADR_ERR]. */
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PBUS_INT[WAIT_ERR]. */
        uint64_t reserved_2_3          : 2;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1C/H) Reads or clears enable for PBUS_INT[DMA_DONE]. */
        uint64_t reserved_6            : 1;
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for PBUS_INT[NCB_FLT]. */
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for PBUS_INT[NCB_RAS]. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    struct bdk_pbus_int_ena_w1c_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1C/H) Reads or clears enable for PBUS_INT[DMA_DONE]. */
        uint64_t reserved_2_3          : 2;
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PBUS_INT[WAIT_ERR]. */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PBUS_INT[ADR_ERR]. */
#else /* Word 0 - Little Endian */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for PBUS_INT[ADR_ERR]. */
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for PBUS_INT[WAIT_ERR]. */
        uint64_t reserved_2_3          : 2;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1C/H) Reads or clears enable for PBUS_INT[DMA_DONE]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_pbus_int_ena_w1c_s cn9; */
};
typedef union bdk_pbus_int_ena_w1c bdk_pbus_int_ena_w1c_t;

#define BDK_PBUS_INT_ENA_W1C BDK_PBUS_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_PBUS_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_INT_ENA_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
        return 0x87e001000090ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
        return 0x87e001000090ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e001000090ll;
    __bdk_csr_fatal("PBUS_INT_ENA_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PBUS_INT_ENA_W1C bdk_pbus_int_ena_w1c_t
#define bustype_BDK_PBUS_INT_ENA_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_INT_ENA_W1C "PBUS_INT_ENA_W1C"
#define device_bar_BDK_PBUS_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_INT_ENA_W1C 0
#define arguments_BDK_PBUS_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RSL) pbus_int_ena_w1s
 *
 * PBUS Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_pbus_int_ena_w1s
{
    uint64_t u;
    struct bdk_pbus_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for PBUS_INT[NCB_RAS]. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PBUS_INT[NCB_FLT]. */
        uint64_t reserved_6            : 1;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1S/H) Reads or sets enable for PBUS_INT[DMA_DONE]. */
        uint64_t reserved_2_3          : 2;
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PBUS_INT[WAIT_ERR]. */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PBUS_INT[ADR_ERR]. */
#else /* Word 0 - Little Endian */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PBUS_INT[ADR_ERR]. */
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PBUS_INT[WAIT_ERR]. */
        uint64_t reserved_2_3          : 2;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1S/H) Reads or sets enable for PBUS_INT[DMA_DONE]. */
        uint64_t reserved_6            : 1;
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for PBUS_INT[NCB_FLT]. */
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for PBUS_INT[NCB_RAS]. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    struct bdk_pbus_int_ena_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1S/H) Reads or sets enable for PBUS_INT[DMA_DONE]. */
        uint64_t reserved_2_3          : 2;
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PBUS_INT[WAIT_ERR]. */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PBUS_INT[ADR_ERR]. */
#else /* Word 0 - Little Endian */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for PBUS_INT[ADR_ERR]. */
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for PBUS_INT[WAIT_ERR]. */
        uint64_t reserved_2_3          : 2;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1S/H) Reads or sets enable for PBUS_INT[DMA_DONE]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_pbus_int_ena_w1s_s cn9; */
};
typedef union bdk_pbus_int_ena_w1s bdk_pbus_int_ena_w1s_t;

#define BDK_PBUS_INT_ENA_W1S BDK_PBUS_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_PBUS_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_INT_ENA_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
        return 0x87e001000098ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
        return 0x87e001000098ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e001000098ll;
    __bdk_csr_fatal("PBUS_INT_ENA_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PBUS_INT_ENA_W1S bdk_pbus_int_ena_w1s_t
#define bustype_BDK_PBUS_INT_ENA_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_INT_ENA_W1S "PBUS_INT_ENA_W1S"
#define device_bar_BDK_PBUS_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_INT_ENA_W1S 0
#define arguments_BDK_PBUS_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RSL) pbus_int_w1s
 *
 * PBUS Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_pbus_int_w1s
{
    uint64_t u;
    struct bdk_pbus_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets PBUS_INT[NCB_RAS]. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PBUS_INT[NCB_FLT]. */
        uint64_t reserved_6            : 1;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1S/H) Reads or sets PBUS_INT[DMA_DONE]. */
        uint64_t reserved_2_3          : 2;
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PBUS_INT[WAIT_ERR]. */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PBUS_INT[ADR_ERR]. */
#else /* Word 0 - Little Endian */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PBUS_INT[ADR_ERR]. */
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PBUS_INT[WAIT_ERR]. */
        uint64_t reserved_2_3          : 2;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1S/H) Reads or sets PBUS_INT[DMA_DONE]. */
        uint64_t reserved_6            : 1;
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1S/H) Reads or sets PBUS_INT[NCB_FLT]. */
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets PBUS_INT[NCB_RAS]. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    struct bdk_pbus_int_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_6_63         : 58;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1S/H) Reads or sets PBUS_INT[DMA_DONE]. */
        uint64_t reserved_2_3          : 2;
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PBUS_INT[WAIT_ERR]. */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PBUS_INT[ADR_ERR]. */
#else /* Word 0 - Little Endian */
        uint64_t adr_err               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets PBUS_INT[ADR_ERR]. */
        uint64_t wait_err              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets PBUS_INT[WAIT_ERR]. */
        uint64_t reserved_2_3          : 2;
        uint64_t dma_done              : 2;  /**< [  5:  4](R/W1S/H) Reads or sets PBUS_INT[DMA_DONE]. */
        uint64_t reserved_6_63         : 58;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_pbus_int_w1s_s cn9; */
};
typedef union bdk_pbus_int_w1s bdk_pbus_int_w1s_t;

#define BDK_PBUS_INT_W1S BDK_PBUS_INT_W1S_FUNC()
static inline uint64_t BDK_PBUS_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_INT_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
        return 0x87e001000088ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
        return 0x87e001000088ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e001000088ll;
    __bdk_csr_fatal("PBUS_INT_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PBUS_INT_W1S bdk_pbus_int_w1s_t
#define bustype_BDK_PBUS_INT_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_INT_W1S "PBUS_INT_W1S"
#define device_bar_BDK_PBUS_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_INT_W1S 0
#define arguments_BDK_PBUS_INT_W1S -1,-1,-1,-1

/**
 * Register (RSL) pbus_msix_pba#
 *
 * PBUS MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the PBUS_INT_VEC_E
 * enumeration.
 */
union bdk_pbus_msix_pbax
{
    uint64_t u;
    struct bdk_pbus_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated PBUS_MSIX_VEC()_CTL, enumerated by
                                                                 PBUS_INT_VEC_E. Bits that have no associated PBUS_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated PBUS_MSIX_VEC()_CTL, enumerated by
                                                                 PBUS_INT_VEC_E. Bits that have no associated PBUS_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pbus_msix_pbax_s cn; */
};
typedef union bdk_pbus_msix_pbax bdk_pbus_msix_pbax_t;

static inline uint64_t BDK_PBUS_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_MSIX_PBAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e001ff0000ll + 8ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e001ff0000ll + 8ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x87e001ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("PBUS_MSIX_PBAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_PBUS_MSIX_PBAX(a) bdk_pbus_msix_pbax_t
#define bustype_BDK_PBUS_MSIX_PBAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_MSIX_PBAX(a) "PBUS_MSIX_PBAX"
#define device_bar_BDK_PBUS_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_PBUS_MSIX_PBAX(a) (a)
#define arguments_BDK_PBUS_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (RSL) pbus_msix_vec#_addr
 *
 * PBUS MSI-X Vector Table Address Registers
 * This register is the MSI-X vector table, indexed by the PBUS_INT_VEC_E enumeration.
 */
union bdk_pbus_msix_vecx_addr
{
    uint64_t u;
    struct bdk_pbus_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's PBUS_MSIX_VEC()_ADDR, PBUS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of PBUS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_PBUS_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's PBUS_MSIX_VEC()_ADDR, PBUS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of PBUS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_PBUS_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_pbus_msix_vecx_addr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's PBUS_MSIX_VEC()_ADDR, PBUS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of PBUS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_PBUS_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's PBUS_MSIX_VEC()_ADDR, PBUS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of PBUS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_PBUS_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_pbus_msix_vecx_addr_s cn9; */
};
typedef union bdk_pbus_msix_vecx_addr bdk_pbus_msix_vecx_addr_t;

static inline uint64_t BDK_PBUS_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_MSIX_VECX_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87e001f00000ll + 0x10ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=3))
        return 0x87e001f00000ll + 0x10ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=5))
        return 0x87e001f00000ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("PBUS_MSIX_VECX_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_PBUS_MSIX_VECX_ADDR(a) bdk_pbus_msix_vecx_addr_t
#define bustype_BDK_PBUS_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_MSIX_VECX_ADDR(a) "PBUS_MSIX_VECX_ADDR"
#define device_bar_BDK_PBUS_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_PBUS_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_PBUS_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) pbus_msix_vec#_ctl
 *
 * PBUS MSI-X Vector Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the PBUS_INT_VEC_E enumeration.
 */
union bdk_pbus_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_pbus_msix_vecx_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_33_63        : 31;
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W) Data to use for MSI-X delivery of this vector. */
        uint64_t mask                  : 1;  /**< [ 32: 32](R/W) When set, no MSI-X interrupts will be sent to this vector. */
        uint64_t reserved_33_63        : 31;
#endif /* Word 0 - End */
    } s;
    struct bdk_pbus_msix_vecx_ctl_cn8
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
    } cn8;
    /* struct bdk_pbus_msix_vecx_ctl_s cn9; */
};
typedef union bdk_pbus_msix_vecx_ctl bdk_pbus_msix_vecx_ctl_t;

static inline uint64_t BDK_PBUS_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_MSIX_VECX_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=3))
        return 0x87e001f00008ll + 0x10ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=3))
        return 0x87e001f00008ll + 0x10ll * ((a) & 0x3);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=5))
        return 0x87e001f00008ll + 0x10ll * ((a) & 0x7);
    __bdk_csr_fatal("PBUS_MSIX_VECX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_PBUS_MSIX_VECX_CTL(a) bdk_pbus_msix_vecx_ctl_t
#define bustype_BDK_PBUS_MSIX_VECX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_MSIX_VECX_CTL(a) "PBUS_MSIX_VECX_CTL"
#define device_bar_BDK_PBUS_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_PBUS_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_PBUS_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) pbus_reg#_cfg
 *
 * PBUS Region Configuration Registers
 * This register contains parameters for each bus region.
 */
union bdk_pbus_regx_cfg
{
    uint64_t u;
    struct bdk_pbus_regx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_48_63        : 16;
        uint64_t a_width               : 2;  /**< [ 47: 46](R/W) Region address bus maximum width.
                                                                  0x0 =  8 bits on PBUS_AD\<31:24\>, using PBUS_ALE\<3..0\>.
                                                                  0x1 = 16 bits on PBUS_AD\<31:16\>, using PBUS_ALE\<3.,1\>.
                                                                  0x2 = 32 bits on PBUS_AD\<31:0\>,  using PBUS_ALE\<3\>.
                                                                  0x3 = Reserved.

                                                                 Specifies how much of PBUS_AD is used at maximum for the address transfers.

                                                                 Fewer bits may be required based on the region size ([SIZE]), which may
                                                                 eliminate the need for address multiplexing.  E.g. a region of 64 KB requires
                                                                 only 16 bits of address, and will use only PBUS_AD\<15:0\> regardless of
                                                                 [A_WIDTH], allowing PBUS_AD[31:16\> to only be used for data.

                                                                 PBUS_ALE pins indicate the number of initial address cycles.  Page sizes are
                                                                 determined by number of dedicated PBUS_AD pins used for address only.

                                                                 Example 1: If [A_WIDTH] = 16-bit and [D_WIDTH] = 16-bit then the following
                                                                 cycles occur:

                                                                 \<pre\>
                                                                   Cycle 1  Address 31:16 on PBUS_AD\<31:16\>.
                                                                   Cycle 2  Address 15:0  on PBUS_AD\<31:16\> with PBUS_ALE\<3:2\> asserted.
                                                                   Cycle 3  Data    15:0  on PBUS_AD\<31:16\> with PBUS_ALE\<3:0\> asserted.
                                                                   Repeat Cycle 2-3 for N 16-bit data words until 16K boundary cross then 1-3.
                                                                 \</pre\>

                                                                 Example 2: If [A_WIDTH] = 32-bit and [D_WIDTH] = 16-bit then the following
                                                                 cycles occur:

                                                                 \<pre\>
                                                                   Cycle 1  Address 31:0  on PBUS_AD\<31:16\>.
                                                                   Cycle 2  Data    15:0  on PBUS_AD\<31:16\>.
                                                                            Address 15:0  on PBUS_AD\<15:0\> with PBUS_ALE\<3:2\> asserted.
                                                                   Repeat Cycle 2 for N 16-bit data words until 16K boundary cross then 1-2.
                                                                 \</pre\>

                                                                 Example 3: If [A_WIDTH] = 8-bit and [D_WIDTH] = 8-bit then the following cycles
                                                                 occur:

                                                                 \<pre\>
                                                                   Cycle 1  Address 31:24 on PBUS_AD\<31:24\>.
                                                                   Cycle 2  Address 23:16 on PBUS_AD\<31:24\> with PBUS_ALE\<3\> asserted.
                                                                   Cycle 3  Address 16:8  on PBUS_AD\<31:24\> with PBUS_ALE\<3:2\> asserted.
                                                                   Cycle 4  Address  7:0  on PBUS_AD\<31:24\> with PBUS_ALE\<3:1\> asserted.
                                                                   Cycle 5  Data     7:0  on PBUS_AD\<31:24\> with PBUS_ALE\<3:0\> asserted.
                                                                   Repeat Cycle 4-5 for N 16-bit data words until 256 boundary cross then 3-5.
                                                                   Repeat Cycle 4-5 for N 16-bit data words until 16K boundary cross then 2-5.
                                                                 \</pre\> */
        uint64_t reserved_45           : 1;
        uint64_t d_width               : 1;  /**< [ 44: 44](R/W) Region data bus width. Specifies how much of the bus is used for the data.
                                                                 See also [A_WIDTH].
                                                                  0 =  8 bits on PBUS_AD\<31:24\>.
                                                                  1 = 16 bits on PBUS_AD\<31:16\>. */
        uint64_t dmack                 : 2;  /**< [ 43: 42](R/W) Region DMACK. If nonzero, this field asserts the corresponding
                                                                 PBUS_DMACK\<n\> pin when an access to this region is performed.
                                                                  0x0 = Disabled.
                                                                  0x1 = PBUS_DMACK\<0\>.
                                                                  0x2 = PBUS_DMACK\<1\>.
                                                                  0x3 = Reserved.

                                                                 This is useful for CF cards in PC card memory mode that support DMA
                                                                 because the -REG and -DMACK pins are shared.

                                                                 The assertion level of PBUS_DMACK is specified by the corresponding
                                                                 GPIO_BIT_CFG()[PIN_XOR]. */
        uint64_t tim_mult              : 2;  /**< [ 41: 40](R/W) Region timing multiplier. Specifies the timing multiplier for the region. The
                                                                 timing multiplier applies to all timing parameters, except for
                                                                 PBUS_REG()_TIM[WAIT] and [RD_DLY], which are specified in coprocessor-clock
                                                                 cycles. [TIM_MULT] is encoded as follows:
                                                                   0x0 = 4x multiplier.
                                                                   0x1 = 1x multiplier.
                                                                   0x2 = 2x multiplier.
                                                                   0x3 = 8x multiplier. */
        uint64_t rd_dly                : 3;  /**< [ 39: 37](R/W) Region read sample delay. Specifies the read sample delay in coprocessor-clock
                                                                 cycles for a region. For read operations, the data bus is normally sampled on
                                                                 the same coprocessor-clock edge that drives PBUS_OE to the inactive state (or
                                                                 the coprocessor-clock edge that toggles the lower address bits in page
                                                                 mode). This parameter can delay that sampling edge by up to seven
                                                                 coprocessor-clock cycles. The number of coprocessor-clock cycles counted by the
                                                                 PBUS_REG()_TIM[PAGE] and PBUS_REG()_TIM[RD_HLD] timing parameters must be
                                                                 greater than or equal to [RD_DLY]. */
        uint64_t sam                   : 1;  /**< [ 36: 36](R/W) Region strobe AND mode. Internally combines the output-enable and write-enable
                                                                 strobes into a single strobe that is then driven onto both PBUS_OE and PBUS_WE.

                                                                 This is useful for parts that use a single strobe along with a read/write bit
                                                                 (the read/write bit can be driven from an address pin). */
        uint64_t we_ext                : 2;  /**< [ 35: 34](R/W) Region write-enable count extension. */
        uint64_t oe_ext                : 2;  /**< [ 33: 32](R/W) Region output-enable count extension. */
        uint64_t en                    : 1;  /**< [ 31: 31](R/W) Region enable. */
        uint64_t orbit                 : 1;  /**< [ 30: 30](R/W) Region ORBIT bit. When set, the hardware asserts this region's PBUS_CE(n)
                                                                 along with PBUS_CE(n-1) when there is an address hit in the previous region.
                                                                 Assertion timing in this case is based on the previous region, PBUS_REG(n-1)_TIM[CE].

                                                                 This is useful for CF cards because it allows the use of two separate
                                                                 timing configurations for common memory and attribute memory. */
        uint64_t size                  : 14; /**< [ 29: 16](R/W) Region size. Region size is specified in 64K blocks and in 'block-1' notation
                                                                 (i.e. 0x0 = one 64K block, 0x1 = two 64K blocks, etc.). */
        uint64_t base                  : 16; /**< [ 15:  0](R/W) Region base address. Specifies physical address bits \<31:16\> of the first 64K
                                                                 block of the region. */
#else /* Word 0 - Little Endian */
        uint64_t base                  : 16; /**< [ 15:  0](R/W) Region base address. Specifies physical address bits \<31:16\> of the first 64K
                                                                 block of the region. */
        uint64_t size                  : 14; /**< [ 29: 16](R/W) Region size. Region size is specified in 64K blocks and in 'block-1' notation
                                                                 (i.e. 0x0 = one 64K block, 0x1 = two 64K blocks, etc.). */
        uint64_t orbit                 : 1;  /**< [ 30: 30](R/W) Region ORBIT bit. When set, the hardware asserts this region's PBUS_CE(n)
                                                                 along with PBUS_CE(n-1) when there is an address hit in the previous region.
                                                                 Assertion timing in this case is based on the previous region, PBUS_REG(n-1)_TIM[CE].

                                                                 This is useful for CF cards because it allows the use of two separate
                                                                 timing configurations for common memory and attribute memory. */
        uint64_t en                    : 1;  /**< [ 31: 31](R/W) Region enable. */
        uint64_t oe_ext                : 2;  /**< [ 33: 32](R/W) Region output-enable count extension. */
        uint64_t we_ext                : 2;  /**< [ 35: 34](R/W) Region write-enable count extension. */
        uint64_t sam                   : 1;  /**< [ 36: 36](R/W) Region strobe AND mode. Internally combines the output-enable and write-enable
                                                                 strobes into a single strobe that is then driven onto both PBUS_OE and PBUS_WE.

                                                                 This is useful for parts that use a single strobe along with a read/write bit
                                                                 (the read/write bit can be driven from an address pin). */
        uint64_t rd_dly                : 3;  /**< [ 39: 37](R/W) Region read sample delay. Specifies the read sample delay in coprocessor-clock
                                                                 cycles for a region. For read operations, the data bus is normally sampled on
                                                                 the same coprocessor-clock edge that drives PBUS_OE to the inactive state (or
                                                                 the coprocessor-clock edge that toggles the lower address bits in page
                                                                 mode). This parameter can delay that sampling edge by up to seven
                                                                 coprocessor-clock cycles. The number of coprocessor-clock cycles counted by the
                                                                 PBUS_REG()_TIM[PAGE] and PBUS_REG()_TIM[RD_HLD] timing parameters must be
                                                                 greater than or equal to [RD_DLY]. */
        uint64_t tim_mult              : 2;  /**< [ 41: 40](R/W) Region timing multiplier. Specifies the timing multiplier for the region. The
                                                                 timing multiplier applies to all timing parameters, except for
                                                                 PBUS_REG()_TIM[WAIT] and [RD_DLY], which are specified in coprocessor-clock
                                                                 cycles. [TIM_MULT] is encoded as follows:
                                                                   0x0 = 4x multiplier.
                                                                   0x1 = 1x multiplier.
                                                                   0x2 = 2x multiplier.
                                                                   0x3 = 8x multiplier. */
        uint64_t dmack                 : 2;  /**< [ 43: 42](R/W) Region DMACK. If nonzero, this field asserts the corresponding
                                                                 PBUS_DMACK\<n\> pin when an access to this region is performed.
                                                                  0x0 = Disabled.
                                                                  0x1 = PBUS_DMACK\<0\>.
                                                                  0x2 = PBUS_DMACK\<1\>.
                                                                  0x3 = Reserved.

                                                                 This is useful for CF cards in PC card memory mode that support DMA
                                                                 because the -REG and -DMACK pins are shared.

                                                                 The assertion level of PBUS_DMACK is specified by the corresponding
                                                                 GPIO_BIT_CFG()[PIN_XOR]. */
        uint64_t d_width               : 1;  /**< [ 44: 44](R/W) Region data bus width. Specifies how much of the bus is used for the data.
                                                                 See also [A_WIDTH].
                                                                  0 =  8 bits on PBUS_AD\<31:24\>.
                                                                  1 = 16 bits on PBUS_AD\<31:16\>. */
        uint64_t reserved_45           : 1;
        uint64_t a_width               : 2;  /**< [ 47: 46](R/W) Region address bus maximum width.
                                                                  0x0 =  8 bits on PBUS_AD\<31:24\>, using PBUS_ALE\<3..0\>.
                                                                  0x1 = 16 bits on PBUS_AD\<31:16\>, using PBUS_ALE\<3.,1\>.
                                                                  0x2 = 32 bits on PBUS_AD\<31:0\>,  using PBUS_ALE\<3\>.
                                                                  0x3 = Reserved.

                                                                 Specifies how much of PBUS_AD is used at maximum for the address transfers.

                                                                 Fewer bits may be required based on the region size ([SIZE]), which may
                                                                 eliminate the need for address multiplexing.  E.g. a region of 64 KB requires
                                                                 only 16 bits of address, and will use only PBUS_AD\<15:0\> regardless of
                                                                 [A_WIDTH], allowing PBUS_AD[31:16\> to only be used for data.

                                                                 PBUS_ALE pins indicate the number of initial address cycles.  Page sizes are
                                                                 determined by number of dedicated PBUS_AD pins used for address only.

                                                                 Example 1: If [A_WIDTH] = 16-bit and [D_WIDTH] = 16-bit then the following
                                                                 cycles occur:

                                                                 \<pre\>
                                                                   Cycle 1  Address 31:16 on PBUS_AD\<31:16\>.
                                                                   Cycle 2  Address 15:0  on PBUS_AD\<31:16\> with PBUS_ALE\<3:2\> asserted.
                                                                   Cycle 3  Data    15:0  on PBUS_AD\<31:16\> with PBUS_ALE\<3:0\> asserted.
                                                                   Repeat Cycle 2-3 for N 16-bit data words until 16K boundary cross then 1-3.
                                                                 \</pre\>

                                                                 Example 2: If [A_WIDTH] = 32-bit and [D_WIDTH] = 16-bit then the following
                                                                 cycles occur:

                                                                 \<pre\>
                                                                   Cycle 1  Address 31:0  on PBUS_AD\<31:16\>.
                                                                   Cycle 2  Data    15:0  on PBUS_AD\<31:16\>.
                                                                            Address 15:0  on PBUS_AD\<15:0\> with PBUS_ALE\<3:2\> asserted.
                                                                   Repeat Cycle 2 for N 16-bit data words until 16K boundary cross then 1-2.
                                                                 \</pre\>

                                                                 Example 3: If [A_WIDTH] = 8-bit and [D_WIDTH] = 8-bit then the following cycles
                                                                 occur:

                                                                 \<pre\>
                                                                   Cycle 1  Address 31:24 on PBUS_AD\<31:24\>.
                                                                   Cycle 2  Address 23:16 on PBUS_AD\<31:24\> with PBUS_ALE\<3\> asserted.
                                                                   Cycle 3  Address 16:8  on PBUS_AD\<31:24\> with PBUS_ALE\<3:2\> asserted.
                                                                   Cycle 4  Address  7:0  on PBUS_AD\<31:24\> with PBUS_ALE\<3:1\> asserted.
                                                                   Cycle 5  Data     7:0  on PBUS_AD\<31:24\> with PBUS_ALE\<3:0\> asserted.
                                                                   Repeat Cycle 4-5 for N 16-bit data words until 256 boundary cross then 3-5.
                                                                   Repeat Cycle 4-5 for N 16-bit data words until 16K boundary cross then 2-5.
                                                                 \</pre\> */
        uint64_t reserved_48_63        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pbus_regx_cfg_s cn; */
};
typedef union bdk_pbus_regx_cfg bdk_pbus_regx_cfg_t;

static inline uint64_t BDK_PBUS_REGX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_REGX_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=7))
        return 0x87e001000000ll + 8ll * ((a) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=7))
        return 0x87e001000000ll + 8ll * ((a) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=7))
        return 0x87e001000000ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("PBUS_REGX_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_PBUS_REGX_CFG(a) bdk_pbus_regx_cfg_t
#define bustype_BDK_PBUS_REGX_CFG(a) BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_REGX_CFG(a) "PBUS_REGX_CFG"
#define device_bar_BDK_PBUS_REGX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_REGX_CFG(a) (a)
#define arguments_BDK_PBUS_REGX_CFG(a) (a),-1,-1,-1

/**
 * Register (RSL) pbus_reg#_tim
 *
 * PBUS Region Timing Registers
 * This register contains page-mode, wait-mode, and timing parameters for each region.
 */
union bdk_pbus_regx_tim
{
    uint64_t u;
    struct bdk_pbus_regx_tim_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pagem                 : 1;  /**< [ 63: 63](R/W) Region page mode enable.
                                                                 When set, the returned data from the target device can uses than one page
                                                                 (two, four and eight pages of data) to complete the operation.  If this bit is
                                                                 not set, only single accesses are used. */
        uint64_t waitm                 : 1;  /**< [ 62: 62](R/W) Region wait mode enable.
                                                                 When set, the hardware waits for the PBUS_WAIT signal to deassert for
                                                                 WAIT coprocessor clock cycles as well as
                                                                 (or [OE] expires which ever occurs last) before finishing the data cycle.
                                                                 Note that this bit should not be set with PAGEM. */
        uint64_t pages                 : 2;  /**< [ 61: 60](R/W) Region page size. Ignored unless PBUS_REG()_TIM[PAGEM] is set.
                                                                  0x0 = 8 bytes.
                                                                  0x1 = 2 bytes.
                                                                  0x2 = 4 bytes.
                                                                  0x3 = 8 bytes. */
        uint64_t ale                   : 6;  /**< [ 59: 54](R/W) Region ALE count. Must be nonzero to ensure legal transitions on
                                                                 the corresponding PBUS outputs. */
        uint64_t page                  : 6;  /**< [ 53: 48](R/W) Region page count. Must be nonzero to ensure legal transitions on
                                                                 the corresponding PBUS outputs. */
        uint64_t wait                  : 6;  /**< [ 47: 42](R/W) Region wait count, when [WAITM] is set, this count plus one,
                                                                 determines the number of coprocessor clocks to lengthen OE/WE
                                                                 after PBUS_WAIT deasserts.  The minimum OE/WE period is determined
                                                                 by [OE] and [WE] fields.  If PBUS_WAIT is asserted at least one coprocessor
                                                                 clock before the end of the minimum OE/WE period then the OE/WE cycle is
                                                                 extended until PBUS_WAIT is deasserted for WAIT+1 coprocessor clocks.
                                                                 Value must be greater than 0x1 if [WAITM] is set. */
        uint64_t pause                 : 6;  /**< [ 41: 36](R/W) Region pause count. */
        uint64_t wr_hld                : 6;  /**< [ 35: 30](R/W) Region write-hold count. */
        uint64_t rd_hld                : 6;  /**< [ 29: 24](R/W) Region read-hold count. */
        uint64_t we                    : 6;  /**< [ 23: 18](R/W) Region write-enable count. Must be nonzero to ensure legal
                                                                 transitions on the corresponding PBUS outputs. */
        uint64_t oe                    : 6;  /**< [ 17: 12](R/W) Region output-enable count. Must be nonzero to ensure legal
                                                                 transitions on the corresponding PBUS outputs. */
        uint64_t ce                    : 6;  /**< [ 11:  6](R/W) Region chip-enable count. */
        uint64_t adr                   : 6;  /**< [  5:  0](R/W) Region address count. */
#else /* Word 0 - Little Endian */
        uint64_t adr                   : 6;  /**< [  5:  0](R/W) Region address count. */
        uint64_t ce                    : 6;  /**< [ 11:  6](R/W) Region chip-enable count. */
        uint64_t oe                    : 6;  /**< [ 17: 12](R/W) Region output-enable count. Must be nonzero to ensure legal
                                                                 transitions on the corresponding PBUS outputs. */
        uint64_t we                    : 6;  /**< [ 23: 18](R/W) Region write-enable count. Must be nonzero to ensure legal
                                                                 transitions on the corresponding PBUS outputs. */
        uint64_t rd_hld                : 6;  /**< [ 29: 24](R/W) Region read-hold count. */
        uint64_t wr_hld                : 6;  /**< [ 35: 30](R/W) Region write-hold count. */
        uint64_t pause                 : 6;  /**< [ 41: 36](R/W) Region pause count. */
        uint64_t wait                  : 6;  /**< [ 47: 42](R/W) Region wait count, when [WAITM] is set, this count plus one,
                                                                 determines the number of coprocessor clocks to lengthen OE/WE
                                                                 after PBUS_WAIT deasserts.  The minimum OE/WE period is determined
                                                                 by [OE] and [WE] fields.  If PBUS_WAIT is asserted at least one coprocessor
                                                                 clock before the end of the minimum OE/WE period then the OE/WE cycle is
                                                                 extended until PBUS_WAIT is deasserted for WAIT+1 coprocessor clocks.
                                                                 Value must be greater than 0x1 if [WAITM] is set. */
        uint64_t page                  : 6;  /**< [ 53: 48](R/W) Region page count. Must be nonzero to ensure legal transitions on
                                                                 the corresponding PBUS outputs. */
        uint64_t ale                   : 6;  /**< [ 59: 54](R/W) Region ALE count. Must be nonzero to ensure legal transitions on
                                                                 the corresponding PBUS outputs. */
        uint64_t pages                 : 2;  /**< [ 61: 60](R/W) Region page size. Ignored unless PBUS_REG()_TIM[PAGEM] is set.
                                                                  0x0 = 8 bytes.
                                                                  0x1 = 2 bytes.
                                                                  0x2 = 4 bytes.
                                                                  0x3 = 8 bytes. */
        uint64_t waitm                 : 1;  /**< [ 62: 62](R/W) Region wait mode enable.
                                                                 When set, the hardware waits for the PBUS_WAIT signal to deassert for
                                                                 WAIT coprocessor clock cycles as well as
                                                                 (or [OE] expires which ever occurs last) before finishing the data cycle.
                                                                 Note that this bit should not be set with PAGEM. */
        uint64_t pagem                 : 1;  /**< [ 63: 63](R/W) Region page mode enable.
                                                                 When set, the returned data from the target device can uses than one page
                                                                 (two, four and eight pages of data) to complete the operation.  If this bit is
                                                                 not set, only single accesses are used. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pbus_regx_tim_s cn; */
};
typedef union bdk_pbus_regx_tim bdk_pbus_regx_tim_t;

static inline uint64_t BDK_PBUS_REGX_TIM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_REGX_TIM(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a<=7))
        return 0x87e001000040ll + 8ll * ((a) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a<=7))
        return 0x87e001000040ll + 8ll * ((a) & 0x7);
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=7))
        return 0x87e001000040ll + 8ll * ((a) & 0x7);
    __bdk_csr_fatal("PBUS_REGX_TIM", 1, a, 0, 0, 0);
}

#define typedef_BDK_PBUS_REGX_TIM(a) bdk_pbus_regx_tim_t
#define bustype_BDK_PBUS_REGX_TIM(a) BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_REGX_TIM(a) "PBUS_REGX_TIM"
#define device_bar_BDK_PBUS_REGX_TIM(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_REGX_TIM(a) (a)
#define arguments_BDK_PBUS_REGX_TIM(a) (a),-1,-1,-1

/**
 * Register (RSL) pbus_thr
 *
 * PBUS Threshold Register
 * This register controls read and write requests to the PBUS registers and external
 * devices.
 */
union bdk_pbus_thr
{
    uint64_t u;
    struct bdk_pbus_thr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t dma_thr               : 6;  /**< [ 21: 16](R/W) DMA threshold. When non-DMA accesses are pending, perform a DMA access after
                                                                 this value of non-DMA accesses have completed. If set to zero, only perform a
                                                                 DMA access when non-DMA accesses are not pending. */
        uint64_t reserved_14_15        : 2;
        uint64_t fif_cnt               : 6;  /**< [ 13:  8](RO/H) Current FIFO count. */
        uint64_t reserved_6_7          : 2;
        uint64_t fif_thr               : 6;  /**< [  5:  0](R/W) NCB busy threshold. Should always read 0x19 (the only legal value). */
#else /* Word 0 - Little Endian */
        uint64_t fif_thr               : 6;  /**< [  5:  0](R/W) NCB busy threshold. Should always read 0x19 (the only legal value). */
        uint64_t reserved_6_7          : 2;
        uint64_t fif_cnt               : 6;  /**< [ 13:  8](RO/H) Current FIFO count. */
        uint64_t reserved_14_15        : 2;
        uint64_t dma_thr               : 6;  /**< [ 21: 16](R/W) DMA threshold. When non-DMA accesses are pending, perform a DMA access after
                                                                 this value of non-DMA accesses have completed. If set to zero, only perform a
                                                                 DMA access when non-DMA accesses are not pending. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_pbus_thr_s cn8; */
    struct bdk_pbus_thr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t reserved_14_21        : 8;
        uint64_t fif_cnt               : 6;  /**< [ 13:  8](RO/H) Current FIFO count. */
        uint64_t reserved_0_7          : 8;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_7          : 8;
        uint64_t fif_cnt               : 6;  /**< [ 13:  8](RO/H) Current FIFO count. */
        uint64_t reserved_14_21        : 8;
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_pbus_thr bdk_pbus_thr_t;

#define BDK_PBUS_THR BDK_PBUS_THR_FUNC()
static inline uint64_t BDK_PBUS_THR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_PBUS_THR_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
        return 0x87e0010000b0ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
        return 0x87e0010000b0ll;
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x87e0010000b0ll;
    __bdk_csr_fatal("PBUS_THR", 0, 0, 0, 0, 0);
}

#define typedef_BDK_PBUS_THR bdk_pbus_thr_t
#define bustype_BDK_PBUS_THR BDK_CSR_TYPE_RSL
#define basename_BDK_PBUS_THR "PBUS_THR"
#define device_bar_BDK_PBUS_THR 0x0 /* PF_BAR0 */
#define busnum_BDK_PBUS_THR 0
#define arguments_BDK_PBUS_THR -1,-1,-1,-1

#endif /* __BDK_CSRS_PBUS_H__ */
