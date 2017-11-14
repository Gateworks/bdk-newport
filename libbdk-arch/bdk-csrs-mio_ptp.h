#ifndef __BDK_CSRS_MIO_PTP_H__
#define __BDK_CSRS_MIO_PTP_H__
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
 * Cavium MIO_PTP.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration mio_ptp_bar_e
 *
 * PTP Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_MIO_PTP_BAR_E_MIO_PTP_PF_BAR0_CN8 (0x807000000000ll)
#define BDK_MIO_PTP_BAR_E_MIO_PTP_PF_BAR0_CN8_SIZE 0x100000ull
#define BDK_MIO_PTP_BAR_E_MIO_PTP_PF_BAR0_CN9 (0x807000000000ll)
#define BDK_MIO_PTP_BAR_E_MIO_PTP_PF_BAR0_CN9_SIZE 0x10000ull
#define BDK_MIO_PTP_BAR_E_MIO_PTP_PF_BAR4 (0x807000f00000ll)
#define BDK_MIO_PTP_BAR_E_MIO_PTP_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration mio_ptp_bp_test_e
 *
 * INTERNAL: PTP BP_TEST Enumeration
 *
 * Enumerates the different bp_test devices.
 */
#define BDK_MIO_PTP_BP_TEST_E_GNT_ORDER_FIFO (0x21)
#define BDK_MIO_PTP_BP_TEST_E_IN_REQ_FIFO (0x23)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_AVS0_CR_PATH_OUTSTD_REQ_FIFO (0x13)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_AVS0_CR_PATH_OUT_DATA_FIFO (0x14)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_CR_PATH_OUT_FIFO (0x1a)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_CR_REQ_FIF_ARB_OUT_FIFO (0x1e)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_EMMC_NP_PATH_OUTSTD_REQ_FIFO (1)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_EMMC_NP_PATH_OUT_DATA_FIFO (2)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_EMMC_P_PATH_OUTSTD_REQ_FIFO (3)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_EMMC_P_PATH_OUT_DATA_FIFO (4)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_ERROR_CR_PATH_OUTSTD_REQ_FIFO (0x1b)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_ERROR_CR_PATH_OUT_DATA_FIFO (0x1c)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_ERROR_CR_PATH_OUT_FIFO (0x1d)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_GNT_ORDER_FIFO (0x1f)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_GPIO_CR_PATH_OUTSTD_REQ_FIFO (0xd)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_GPIO_CR_PATH_OUT_DATA_FIFO (0xe)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_MPI0_CR_PATH_OUTSTD_REQ_FIFO (0xf)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_MPI0_CR_PATH_OUT_DATA_FIFO (0x10)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_MPI1_CR_PATH_OUTSTD_REQ_FIFO (0x11)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_MPI1_CR_PATH_OUT_DATA_FIFO (0x12)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_NCBO_SKID_FIFO (0x17)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_NDF_CR_PATH_OUTSTD_REQ_FIFO (0x15)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_NDF_CR_PATH_OUT_DATA_FIFO (0x16)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_NP_PATH_OUT_FIFO (0x18)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_PBUS_CR_PATH_OUTSTD_REQ_FIFO (9)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_PBUS_CR_PATH_OUT_DATA_FIFO (0xa)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_PBUS_NP_PATH_OUTSTD_REQ_FIFO (5)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_PBUS_NP_PATH_OUT_DATA_FIFO (6)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_PBUS_P_PATH_OUTSTD_REQ_FIFO (7)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_PBUS_P_PATH_OUT_DATA_FIFO (8)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_PTP_CR_PATH_OUTSTD_REQ_FIFO (0xb)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_PTP_CR_PATH_OUT_DATA_FIFO (0xc)
#define BDK_MIO_PTP_BP_TEST_E_MIO_NCB_P_PATH_OUT_FIFO (0x19)
#define BDK_MIO_PTP_BP_TEST_E_NCB_CSR_SM_REQ_FIFO (0x20)
#define BDK_MIO_PTP_BP_TEST_E_NONE (0)
#define BDK_MIO_PTP_BP_TEST_E_REQ_ARB_FIFO (0x22)

/**
 * Enumeration mio_ptp_ext_sel_e
 *
 * PTP External Sources Select Enumeration
 * Enumerates the different external signal sources for PTP.
 * Internal:
 * Note that CCPI reference clocks cannot be selected.
 */
#define BDK_MIO_PTP_EXT_SEL_E_BTS_REF_CLK (1)
#define BDK_MIO_PTP_EXT_SEL_E_GPIO (0)
#define BDK_MIO_PTP_EXT_SEL_E_GPIOX(a) (0 + (a))
#define BDK_MIO_PTP_EXT_SEL_E_QLM_REFX(a) (0x38 + (a))

/**
 * Enumeration mio_ptp_int_vec_e
 *
 * PTP MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_MIO_PTP_INT_VEC_E_DPLL_INT (1)
#define BDK_MIO_PTP_INT_VEC_E_EVT_INT (0)

/**
 * Register (NCB) mio_ptp_bp_test_indir
 *
 * INTERNAL: MIO/PTP Backpressure Test Register
 */
union bdk_mio_ptp_bp_test_indir
{
    uint64_t u;
    struct bdk_mio_ptp_bp_test_indir_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](WO) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure. */
        uint64_t bp_cfg                : 2;  /**< [ 62: 61](WO) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time. */
        uint64_t reserved_30_60        : 31;
        uint64_t device                : 6;  /**< [ 29: 24](WO) Selects test device. Enumerated by MIO_PTP_BP_TEST_E. */
        uint64_t reserved_12_23        : 12;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](WO) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](WO) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_23        : 12;
        uint64_t device                : 6;  /**< [ 29: 24](WO) Selects test device. Enumerated by MIO_PTP_BP_TEST_E. */
        uint64_t reserved_30_60        : 31;
        uint64_t bp_cfg                : 2;  /**< [ 62: 61](WO) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time. */
        uint64_t enable                : 1;  /**< [ 63: 63](WO) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_bp_test_indir_s cn; */
};
typedef union bdk_mio_ptp_bp_test_indir bdk_mio_ptp_bp_test_indir_t;

#define BDK_MIO_PTP_BP_TEST_INDIR BDK_MIO_PTP_BP_TEST_INDIR_FUNC()
static inline uint64_t BDK_MIO_PTP_BP_TEST_INDIR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_BP_TEST_INDIR_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80700000e000ll;
    __bdk_csr_fatal("MIO_PTP_BP_TEST_INDIR", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_PTP_BP_TEST_INDIR bdk_mio_ptp_bp_test_indir_t
#define bustype_BDK_MIO_PTP_BP_TEST_INDIR BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_BP_TEST_INDIR "MIO_PTP_BP_TEST_INDIR"
#define device_bar_BDK_MIO_PTP_BP_TEST_INDIR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_BP_TEST_INDIR 0
#define arguments_BDK_MIO_PTP_BP_TEST_INDIR -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_ckout_hi_incr
 *
 * PTP Clock Out High Increment Register
 * This register contains the PTP CKOUT threshold increment on pre-inverted PTP_CKOUT rising
 * edge. See MIO_PTP_CKOUT_THRESH_HI for details.
 */
union bdk_mio_ptp_ckout_hi_incr
{
    uint64_t u;
    struct bdk_mio_ptp_ckout_hi_incr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_ckout_hi_incr_s cn; */
};
typedef union bdk_mio_ptp_ckout_hi_incr bdk_mio_ptp_ckout_hi_incr_t;

#define BDK_MIO_PTP_CKOUT_HI_INCR BDK_MIO_PTP_CKOUT_HI_INCR_FUNC()
static inline uint64_t BDK_MIO_PTP_CKOUT_HI_INCR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_CKOUT_HI_INCR_FUNC(void)
{
    return 0x807000000f40ll;
}

#define typedef_BDK_MIO_PTP_CKOUT_HI_INCR bdk_mio_ptp_ckout_hi_incr_t
#define bustype_BDK_MIO_PTP_CKOUT_HI_INCR BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_CKOUT_HI_INCR "MIO_PTP_CKOUT_HI_INCR"
#define device_bar_BDK_MIO_PTP_CKOUT_HI_INCR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_CKOUT_HI_INCR 0
#define arguments_BDK_MIO_PTP_CKOUT_HI_INCR -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_ckout_lo_incr
 *
 * PTP Clock Out Low Increment Register
 * This register contains the PTP CKOUT threshold increment on pre-inverted PTP_CKOUT falling
 * edge. See MIO_PTP_CKOUT_THRESH_HI for details.
 */
union bdk_mio_ptp_ckout_lo_incr
{
    uint64_t u;
    struct bdk_mio_ptp_ckout_lo_incr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_ckout_lo_incr_s cn; */
};
typedef union bdk_mio_ptp_ckout_lo_incr bdk_mio_ptp_ckout_lo_incr_t;

#define BDK_MIO_PTP_CKOUT_LO_INCR BDK_MIO_PTP_CKOUT_LO_INCR_FUNC()
static inline uint64_t BDK_MIO_PTP_CKOUT_LO_INCR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_CKOUT_LO_INCR_FUNC(void)
{
    return 0x807000000f48ll;
}

#define typedef_BDK_MIO_PTP_CKOUT_LO_INCR bdk_mio_ptp_ckout_lo_incr_t
#define bustype_BDK_MIO_PTP_CKOUT_LO_INCR BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_CKOUT_LO_INCR "MIO_PTP_CKOUT_LO_INCR"
#define device_bar_BDK_MIO_PTP_CKOUT_LO_INCR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_CKOUT_LO_INCR 0
#define arguments_BDK_MIO_PTP_CKOUT_LO_INCR -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_ckout_thresh_hi
 *
 * PTP Clock Out High Register
 * This register contains the high bytes of the PTP CKOUT threshold.
 * Writes to MIO_PTP_CKOUT_THRESH_HI also clear MIO_PTP_CKOUT_THRESH_LO; in order to update all
 * 96 bits, writes MIO_PTP_CKOUT_THRESH_HI followed by MIO_PTP_CKOUT_THRESH_LO.
 * This threshold {MIO_PTP_CKOUT_THRESH_HI,  MIO_PTP_CKOUT_THRESH_LO} is a rolling threshold that
 * will be updated by hardware:
 *   When current PTP_CKOUT before inversion (defined by MIO_PTP_CLOCK_CFG[CKOUT_INV]) is zero,
 *   and {MIO_PTP_CLOCK_HI/LO} \>= {MIO_PTP_CKOUT_THRESH_HI/LO}, the pre-inverted PTP_CKOUT will
 *   update to one, and {MIO_PTP_CKOUT_THRESH_HI/LO} will increment by MIO_PTP_CKOUT_HI_INCR.
 *   When current PTP_CKOUT before inversion (defined by MIO_PTP_CLOCK_CFG[CKOUT_INV]) is one,
 *   and {MIO_PTP_CLOCK_HI/LO} \>= {MIO_PTP_CKOUT_THRESH_HI/LO}, the pre-inverted PTP_CKOUT will
 *   update to zero, and {MIO_PTP_CKOUT_THRESH_HI/LO} will increment by MIO_PTP_CKOUT_LO_INCR.
 */
union bdk_mio_ptp_ckout_thresh_hi
{
    uint64_t u;
    struct bdk_mio_ptp_ckout_thresh_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_ckout_thresh_hi_s cn; */
};
typedef union bdk_mio_ptp_ckout_thresh_hi bdk_mio_ptp_ckout_thresh_hi_t;

#define BDK_MIO_PTP_CKOUT_THRESH_HI BDK_MIO_PTP_CKOUT_THRESH_HI_FUNC()
static inline uint64_t BDK_MIO_PTP_CKOUT_THRESH_HI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_CKOUT_THRESH_HI_FUNC(void)
{
    return 0x807000000f38ll;
}

#define typedef_BDK_MIO_PTP_CKOUT_THRESH_HI bdk_mio_ptp_ckout_thresh_hi_t
#define bustype_BDK_MIO_PTP_CKOUT_THRESH_HI BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_CKOUT_THRESH_HI "MIO_PTP_CKOUT_THRESH_HI"
#define device_bar_BDK_MIO_PTP_CKOUT_THRESH_HI 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_CKOUT_THRESH_HI 0
#define arguments_BDK_MIO_PTP_CKOUT_THRESH_HI -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_ckout_thresh_lo
 *
 * PTP Clock Out Low Register
 * This register contains the low bytes of the PTP CKOUT threshold,
 * See MIO_PTP_CKOUT_THRESH_HI for details.
 */
union bdk_mio_ptp_ckout_thresh_lo
{
    uint64_t u;
    struct bdk_mio_ptp_ckout_thresh_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W/H) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W/H) Fractions of nanoseconds. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_ckout_thresh_lo_s cn; */
};
typedef union bdk_mio_ptp_ckout_thresh_lo bdk_mio_ptp_ckout_thresh_lo_t;

#define BDK_MIO_PTP_CKOUT_THRESH_LO BDK_MIO_PTP_CKOUT_THRESH_LO_FUNC()
static inline uint64_t BDK_MIO_PTP_CKOUT_THRESH_LO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_CKOUT_THRESH_LO_FUNC(void)
{
    return 0x807000000f30ll;
}

#define typedef_BDK_MIO_PTP_CKOUT_THRESH_LO bdk_mio_ptp_ckout_thresh_lo_t
#define bustype_BDK_MIO_PTP_CKOUT_THRESH_LO BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_CKOUT_THRESH_LO "MIO_PTP_CKOUT_THRESH_LO"
#define device_bar_BDK_MIO_PTP_CKOUT_THRESH_LO 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_CKOUT_THRESH_LO 0
#define arguments_BDK_MIO_PTP_CKOUT_THRESH_LO -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_clken
 *
 * MIO Clock Enable Register
 * This register controls conditional clocks.
 */
union bdk_mio_ptp_clken
{
    uint64_t u;
    struct bdk_mio_ptp_clken_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t ptp_clken             : 1;  /**< [  1:  1](R/W) Force the PTP core conditional clocking to be always on. For diagnostic use only. */
        uint64_t mio_ncb_clken         : 1;  /**< [  0:  0](R/W) Force the NCB interface conditional clocking to be always on, across all of MIO.
                                                                 For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t mio_ncb_clken         : 1;  /**< [  0:  0](R/W) Force the NCB interface conditional clocking to be always on, across all of MIO.
                                                                 For diagnostic use only. */
        uint64_t ptp_clken             : 1;  /**< [  1:  1](R/W) Force the PTP core conditional clocking to be always on. For diagnostic use only. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_clken_s cn; */
};
typedef union bdk_mio_ptp_clken bdk_mio_ptp_clken_t;

#define BDK_MIO_PTP_CLKEN BDK_MIO_PTP_CLKEN_FUNC()
static inline uint64_t BDK_MIO_PTP_CLKEN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_CLKEN_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x807000002080ll;
    __bdk_csr_fatal("MIO_PTP_CLKEN", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_PTP_CLKEN bdk_mio_ptp_clken_t
#define bustype_BDK_MIO_PTP_CLKEN BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_CLKEN "MIO_PTP_CLKEN"
#define device_bar_BDK_MIO_PTP_CLKEN 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_CLKEN 0
#define arguments_BDK_MIO_PTP_CLKEN -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_clock_cfg
 *
 * PTP Clock Configuration Register
 * This register configures the timestamp architecture.
 */
union bdk_mio_ptp_clock_cfg
{
    uint64_t u;
    struct bdk_mio_ptp_clock_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t sysck                 : 1;  /**< [ 42: 42](RO/H) PTP SYSCK; reflects ptp__sysck. */
        uint64_t ckout                 : 1;  /**< [ 41: 41](RO/H) PTP CKOUT; reflects ptp__ckout after [CKOUT_INV] inverter. */
        uint64_t pps                   : 1;  /**< [ 40: 40](RO/H) PTP PPS output; reflects ptp__pps after [PPS_INV] inverter. */
        uint64_t ext_clk_edge          : 2;  /**< [ 39: 38](R/W) External clock input edge:
                                                                 0x0 = Rising edge.
                                                                 0x1 = Falling edge.
                                                                 0x2 = Both rising and falling edge.
                                                                 0x3 = Reserved. */
        uint64_t reserved_34_37        : 4;
        uint64_t refclk_src            : 1;  /**< [ 33: 33](R/W) Internal reference clock source used to generate PTP clock.
                                                                   0 = Use the coprocessor-clock to generates PTP clock.  To provide sufficient
                                                                   resolution the coprocessor clock is typically required, however if the
                                                                   frequency of the coprocessor-clock is changed, this may result in time drift
                                                                   which must be recompensated by software, perhaps by redoing the IEEE 1588
                                                                   synchronization.
                                                                   1 = Use 100 MHz input reference clock to generate the PTP clock. */
        uint64_t sysck_en              : 1;  /**< [ 32: 32](R/W) Enable PTP SYSCK. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t pps_inv               : 1;  /**< [ 31: 31](R/W) Invert PTP PPS.
                                                                 0 = Don't invert.
                                                                 1 = Invert. */
        uint64_t pps_en                : 1;  /**< [ 30: 30](R/W) Enable PTP PPS. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t reserved_26_29        : 4;
        uint64_t ckout_inv             : 1;  /**< [ 25: 25](R/W) Invert PTP CKOUT.
                                                                 0 = Don't invert.
                                                                 1 = Invert. */
        uint64_t ckout_en              : 1;  /**< [ 24: 24](R/W) Enable PTP CKOUT. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t evcnt_in              : 6;  /**< [ 23: 18](R/W) Source for event counter input:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t evcnt_edge            : 1;  /**< [ 17: 17](R/W) Event counter input edge: 0 = falling edge, 1 = rising edge. */
        uint64_t evcnt_en              : 1;  /**< [ 16: 16](R/W) Enable event counter. */
        uint64_t tstmp_in              : 6;  /**< [ 15: 10](R/W) Source for timestamp input:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t tstmp_edge            : 1;  /**< [  9:  9](R/W) External timestamp input edge: 0 = falling edge, 1 = rising edge. */
        uint64_t tstmp_en              : 1;  /**< [  8:  8](R/W) Enable external timestamp. */
        uint64_t ext_clk_in            : 6;  /**< [  7:  2](R/W) Source for external clock when [EXT_CLK_EN] is set:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t ext_clk_en            : 1;  /**< [  1:  1](R/W) Use external clock for PTP clock. */
        uint64_t ptp_en                : 1;  /**< [  0:  0](R/W) Enable PTP module. */
#else /* Word 0 - Little Endian */
        uint64_t ptp_en                : 1;  /**< [  0:  0](R/W) Enable PTP module. */
        uint64_t ext_clk_en            : 1;  /**< [  1:  1](R/W) Use external clock for PTP clock. */
        uint64_t ext_clk_in            : 6;  /**< [  7:  2](R/W) Source for external clock when [EXT_CLK_EN] is set:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t tstmp_en              : 1;  /**< [  8:  8](R/W) Enable external timestamp. */
        uint64_t tstmp_edge            : 1;  /**< [  9:  9](R/W) External timestamp input edge: 0 = falling edge, 1 = rising edge. */
        uint64_t tstmp_in              : 6;  /**< [ 15: 10](R/W) Source for timestamp input:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t evcnt_en              : 1;  /**< [ 16: 16](R/W) Enable event counter. */
        uint64_t evcnt_edge            : 1;  /**< [ 17: 17](R/W) Event counter input edge: 0 = falling edge, 1 = rising edge. */
        uint64_t evcnt_in              : 6;  /**< [ 23: 18](R/W) Source for event counter input:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t ckout_en              : 1;  /**< [ 24: 24](R/W) Enable PTP CKOUT. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t ckout_inv             : 1;  /**< [ 25: 25](R/W) Invert PTP CKOUT.
                                                                 0 = Don't invert.
                                                                 1 = Invert. */
        uint64_t reserved_26_29        : 4;
        uint64_t pps_en                : 1;  /**< [ 30: 30](R/W) Enable PTP PPS. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t pps_inv               : 1;  /**< [ 31: 31](R/W) Invert PTP PPS.
                                                                 0 = Don't invert.
                                                                 1 = Invert. */
        uint64_t sysck_en              : 1;  /**< [ 32: 32](R/W) Enable PTP SYSCK. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t refclk_src            : 1;  /**< [ 33: 33](R/W) Internal reference clock source used to generate PTP clock.
                                                                   0 = Use the coprocessor-clock to generates PTP clock.  To provide sufficient
                                                                   resolution the coprocessor clock is typically required, however if the
                                                                   frequency of the coprocessor-clock is changed, this may result in time drift
                                                                   which must be recompensated by software, perhaps by redoing the IEEE 1588
                                                                   synchronization.
                                                                   1 = Use 100 MHz input reference clock to generate the PTP clock. */
        uint64_t reserved_34_37        : 4;
        uint64_t ext_clk_edge          : 2;  /**< [ 39: 38](R/W) External clock input edge:
                                                                 0x0 = Rising edge.
                                                                 0x1 = Falling edge.
                                                                 0x2 = Both rising and falling edge.
                                                                 0x3 = Reserved. */
        uint64_t pps                   : 1;  /**< [ 40: 40](RO/H) PTP PPS output; reflects ptp__pps after [PPS_INV] inverter. */
        uint64_t ckout                 : 1;  /**< [ 41: 41](RO/H) PTP CKOUT; reflects ptp__ckout after [CKOUT_INV] inverter. */
        uint64_t sysck                 : 1;  /**< [ 42: 42](RO/H) PTP SYSCK; reflects ptp__sysck. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_ptp_clock_cfg_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_42_63        : 22;
        uint64_t ckout                 : 1;  /**< [ 41: 41](RO/H) PTP CKOUT; reflects ptp__ckout after [CKOUT_INV] inverter. */
        uint64_t pps                   : 1;  /**< [ 40: 40](RO/H) PTP PPS output; reflects ptp__pps after [PPS_INV] inverter. */
        uint64_t ext_clk_edge          : 2;  /**< [ 39: 38](R/W) External clock input edge:
                                                                 0x0 = Rising edge.
                                                                 0x1 = Falling edge.
                                                                 0x2 = Both rising and falling edge.
                                                                 0x3 = Reserved. */
        uint64_t reserved_32_37        : 6;
        uint64_t pps_inv               : 1;  /**< [ 31: 31](R/W) Invert PTP PPS.
                                                                 0 = Don't invert.
                                                                 1 = Invert. */
        uint64_t pps_en                : 1;  /**< [ 30: 30](R/W) Enable PTP PPS. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t reserved_26_29        : 4;
        uint64_t ckout_inv             : 1;  /**< [ 25: 25](R/W) Invert PTP CKOUT.
                                                                 0 = Don't invert.
                                                                 1 = Invert. */
        uint64_t ckout_en              : 1;  /**< [ 24: 24](R/W) Enable PTP CKOUT. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t evcnt_in              : 6;  /**< [ 23: 18](R/W) Source for event counter input:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t evcnt_edge            : 1;  /**< [ 17: 17](R/W) Event counter input edge: 0 = falling edge, 1 = rising edge. */
        uint64_t evcnt_en              : 1;  /**< [ 16: 16](R/W) Enable event counter. */
        uint64_t tstmp_in              : 6;  /**< [ 15: 10](R/W) Source for timestamp input:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t tstmp_edge            : 1;  /**< [  9:  9](R/W) External timestamp input edge: 0 = falling edge, 1 = rising edge. */
        uint64_t tstmp_en              : 1;  /**< [  8:  8](R/W) Enable external timestamp. */
        uint64_t ext_clk_in            : 6;  /**< [  7:  2](R/W) Source for external clock when [EXT_CLK_EN] is set:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t ext_clk_en            : 1;  /**< [  1:  1](R/W) Use external clock for PTP clock. */
        uint64_t ptp_en                : 1;  /**< [  0:  0](R/W) Enable PTP module. */
#else /* Word 0 - Little Endian */
        uint64_t ptp_en                : 1;  /**< [  0:  0](R/W) Enable PTP module. */
        uint64_t ext_clk_en            : 1;  /**< [  1:  1](R/W) Use external clock for PTP clock. */
        uint64_t ext_clk_in            : 6;  /**< [  7:  2](R/W) Source for external clock when [EXT_CLK_EN] is set:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t tstmp_en              : 1;  /**< [  8:  8](R/W) Enable external timestamp. */
        uint64_t tstmp_edge            : 1;  /**< [  9:  9](R/W) External timestamp input edge: 0 = falling edge, 1 = rising edge. */
        uint64_t tstmp_in              : 6;  /**< [ 15: 10](R/W) Source for timestamp input:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t evcnt_en              : 1;  /**< [ 16: 16](R/W) Enable event counter. */
        uint64_t evcnt_edge            : 1;  /**< [ 17: 17](R/W) Event counter input edge: 0 = falling edge, 1 = rising edge. */
        uint64_t evcnt_in              : 6;  /**< [ 23: 18](R/W) Source for event counter input:
                                                                 Enumerated by MIO_PTP_EXT_SEL_E. */
        uint64_t ckout_en              : 1;  /**< [ 24: 24](R/W) Enable PTP CKOUT. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t ckout_inv             : 1;  /**< [ 25: 25](R/W) Invert PTP CKOUT.
                                                                 0 = Don't invert.
                                                                 1 = Invert. */
        uint64_t reserved_26_29        : 4;
        uint64_t pps_en                : 1;  /**< [ 30: 30](R/W) Enable PTP PPS. (For output pin selection see GPIO_BIT_CFG().) */
        uint64_t pps_inv               : 1;  /**< [ 31: 31](R/W) Invert PTP PPS.
                                                                 0 = Don't invert.
                                                                 1 = Invert. */
        uint64_t reserved_32_37        : 6;
        uint64_t ext_clk_edge          : 2;  /**< [ 39: 38](R/W) External clock input edge:
                                                                 0x0 = Rising edge.
                                                                 0x1 = Falling edge.
                                                                 0x2 = Both rising and falling edge.
                                                                 0x3 = Reserved. */
        uint64_t pps                   : 1;  /**< [ 40: 40](RO/H) PTP PPS output; reflects ptp__pps after [PPS_INV] inverter. */
        uint64_t ckout                 : 1;  /**< [ 41: 41](RO/H) PTP CKOUT; reflects ptp__ckout after [CKOUT_INV] inverter. */
        uint64_t reserved_42_63        : 22;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_ptp_clock_cfg_s cn9; */
};
typedef union bdk_mio_ptp_clock_cfg bdk_mio_ptp_clock_cfg_t;

#define BDK_MIO_PTP_CLOCK_CFG BDK_MIO_PTP_CLOCK_CFG_FUNC()
static inline uint64_t BDK_MIO_PTP_CLOCK_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_CLOCK_CFG_FUNC(void)
{
    return 0x807000000f00ll;
}

#define typedef_BDK_MIO_PTP_CLOCK_CFG bdk_mio_ptp_clock_cfg_t
#define bustype_BDK_MIO_PTP_CLOCK_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_CLOCK_CFG "MIO_PTP_CLOCK_CFG"
#define device_bar_BDK_MIO_PTP_CLOCK_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_CLOCK_CFG 0
#define arguments_BDK_MIO_PTP_CLOCK_CFG -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_clock_comp
 *
 * PTP Clock Compensator Register
 * This register provides the amount to increment the PTP clock {MIO_PTP_CLOCK_HI,
 * MIO_PTP_CLOCK_LO}
 * on PTP events defined by MIO_PTP_CLOCK_CFG.
 * MIO_PTP_CLOCK_CFG[PTP_EN] needs to be enabled before writing this register.
 */
union bdk_mio_ptp_clock_comp
{
    uint64_t u;
    struct bdk_mio_ptp_clock_comp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Compensation value in nanoseconds. */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Compensation value in nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_clock_comp_s cn; */
};
typedef union bdk_mio_ptp_clock_comp bdk_mio_ptp_clock_comp_t;

#define BDK_MIO_PTP_CLOCK_COMP BDK_MIO_PTP_CLOCK_COMP_FUNC()
static inline uint64_t BDK_MIO_PTP_CLOCK_COMP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_CLOCK_COMP_FUNC(void)
{
    return 0x807000000f18ll;
}

#define typedef_BDK_MIO_PTP_CLOCK_COMP bdk_mio_ptp_clock_comp_t
#define bustype_BDK_MIO_PTP_CLOCK_COMP BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_CLOCK_COMP "MIO_PTP_CLOCK_COMP"
#define device_bar_BDK_MIO_PTP_CLOCK_COMP 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_CLOCK_COMP 0
#define arguments_BDK_MIO_PTP_CLOCK_COMP -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_clock_hi
 *
 * PTP Clock High Register
 * This register provides bits \<95:32\> of the PTP clock. Writes to MIO_PTP_CLOCK_HI also clear
 * MIO_PTP_CLOCK_LO. To update all 96 bits, write MIO_PTP_CLOCK_HI followed by MIO_PTP_CLOCK_LO.
 * MIO_PTP_CLOCK_CFG[PTP_EN] needs to be enabled before writing this register.
 */
union bdk_mio_ptp_clock_hi
{
    uint64_t u;
    struct bdk_mio_ptp_clock_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Clock value in nanoseconds. Bits\<95:32\> of the PTP clock. */
#else /* Word 0 - Little Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Clock value in nanoseconds. Bits\<95:32\> of the PTP clock. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_clock_hi_s cn; */
};
typedef union bdk_mio_ptp_clock_hi bdk_mio_ptp_clock_hi_t;

#define BDK_MIO_PTP_CLOCK_HI BDK_MIO_PTP_CLOCK_HI_FUNC()
static inline uint64_t BDK_MIO_PTP_CLOCK_HI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_CLOCK_HI_FUNC(void)
{
    return 0x807000000f10ll;
}

#define typedef_BDK_MIO_PTP_CLOCK_HI bdk_mio_ptp_clock_hi_t
#define bustype_BDK_MIO_PTP_CLOCK_HI BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_CLOCK_HI "MIO_PTP_CLOCK_HI"
#define device_bar_BDK_MIO_PTP_CLOCK_HI 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_CLOCK_HI 0
#define arguments_BDK_MIO_PTP_CLOCK_HI -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_clock_lo
 *
 * PTP Clock Low Register
 * This register provides bits \<31:0\> of the PTP clock.  MIO_PTP_CLOCK_CFG[PTP_EN] needs to be
 * enabled before writing this register.
 */
union bdk_mio_ptp_clock_lo
{
    uint64_t u;
    struct bdk_mio_ptp_clock_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W/H) Fractions of nanoseconds. Bits\<31:0\> of the PTP clock. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W/H) Fractions of nanoseconds. Bits\<31:0\> of the PTP clock. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_clock_lo_s cn; */
};
typedef union bdk_mio_ptp_clock_lo bdk_mio_ptp_clock_lo_t;

#define BDK_MIO_PTP_CLOCK_LO BDK_MIO_PTP_CLOCK_LO_FUNC()
static inline uint64_t BDK_MIO_PTP_CLOCK_LO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_CLOCK_LO_FUNC(void)
{
    return 0x807000000f08ll;
}

#define typedef_BDK_MIO_PTP_CLOCK_LO bdk_mio_ptp_clock_lo_t
#define bustype_BDK_MIO_PTP_CLOCK_LO BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_CLOCK_LO "MIO_PTP_CLOCK_LO"
#define device_bar_BDK_MIO_PTP_CLOCK_LO 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_CLOCK_LO 0
#define arguments_BDK_MIO_PTP_CLOCK_LO -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_dpll_err_int
 *
 * PTP Digital PLL Error Interrupt Register
 * This register contains the digital PLL error event.
 */
union bdk_mio_ptp_dpll_err_int
{
    uint64_t u;
    struct bdk_mio_ptp_dpll_err_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t n_sclk                : 32; /**< [ 63: 32](RO/H) Latest number of coprocessor clocks in one external reference signal compensation period
                                                                 (MIO_PTP_CLOCK_COMP). */
        uint64_t reserved_0_31         : 32;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_31         : 32;
        uint64_t n_sclk                : 32; /**< [ 63: 32](RO/H) Latest number of coprocessor clocks in one external reference signal compensation period
                                                                 (MIO_PTP_CLOCK_COMP). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_dpll_err_int_s cn; */
};
typedef union bdk_mio_ptp_dpll_err_int bdk_mio_ptp_dpll_err_int_t;

#define BDK_MIO_PTP_DPLL_ERR_INT BDK_MIO_PTP_DPLL_ERR_INT_FUNC()
static inline uint64_t BDK_MIO_PTP_DPLL_ERR_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_DPLL_ERR_INT_FUNC(void)
{
    return 0x807000000f90ll;
}

#define typedef_BDK_MIO_PTP_DPLL_ERR_INT bdk_mio_ptp_dpll_err_int_t
#define bustype_BDK_MIO_PTP_DPLL_ERR_INT BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_DPLL_ERR_INT "MIO_PTP_DPLL_ERR_INT"
#define device_bar_BDK_MIO_PTP_DPLL_ERR_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_DPLL_ERR_INT 0
#define arguments_BDK_MIO_PTP_DPLL_ERR_INT -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_dpll_err_thresh
 *
 * PTP Digital PLL Error Threshold Register
 * This register configures the digital PLL error interrupt.
 */
union bdk_mio_ptp_dpll_err_thresh
{
    uint64_t u;
    struct bdk_mio_ptp_dpll_err_thresh_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t max                   : 32; /**< [ 63: 32](R/W) Highest acceptable value of MIO_PTP_DPLL_ERR_INT[N_SCLK] without asserting
                                                                 MIO_PTP_INT[DPLL_INT] interrupt. */
        uint64_t min                   : 32; /**< [ 31:  0](R/W) Lowest acceptable value of MIO_PTP_DPLL_ERR_INT[N_SCLK] without asserting
                                                                 MIO_PTP_INT[DPLL_INT] interrupt. */
#else /* Word 0 - Little Endian */
        uint64_t min                   : 32; /**< [ 31:  0](R/W) Lowest acceptable value of MIO_PTP_DPLL_ERR_INT[N_SCLK] without asserting
                                                                 MIO_PTP_INT[DPLL_INT] interrupt. */
        uint64_t max                   : 32; /**< [ 63: 32](R/W) Highest acceptable value of MIO_PTP_DPLL_ERR_INT[N_SCLK] without asserting
                                                                 MIO_PTP_INT[DPLL_INT] interrupt. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_dpll_err_thresh_s cn; */
};
typedef union bdk_mio_ptp_dpll_err_thresh bdk_mio_ptp_dpll_err_thresh_t;

#define BDK_MIO_PTP_DPLL_ERR_THRESH BDK_MIO_PTP_DPLL_ERR_THRESH_FUNC()
static inline uint64_t BDK_MIO_PTP_DPLL_ERR_THRESH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_DPLL_ERR_THRESH_FUNC(void)
{
    return 0x807000000f88ll;
}

#define typedef_BDK_MIO_PTP_DPLL_ERR_THRESH bdk_mio_ptp_dpll_err_thresh_t
#define bustype_BDK_MIO_PTP_DPLL_ERR_THRESH BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_DPLL_ERR_THRESH "MIO_PTP_DPLL_ERR_THRESH"
#define device_bar_BDK_MIO_PTP_DPLL_ERR_THRESH 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_DPLL_ERR_THRESH 0
#define arguments_BDK_MIO_PTP_DPLL_ERR_THRESH -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_dpll_incr
 *
 * PTP Digital PLL Increment Register
 * This register contains the digital PLL increment on each coprocessor clock rising edge.
 * Zero disables the digital PLL.
 */
union bdk_mio_ptp_dpll_incr
{
    uint64_t u;
    struct bdk_mio_ptp_dpll_incr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_dpll_incr_s cn; */
};
typedef union bdk_mio_ptp_dpll_incr bdk_mio_ptp_dpll_incr_t;

#define BDK_MIO_PTP_DPLL_INCR BDK_MIO_PTP_DPLL_INCR_FUNC()
static inline uint64_t BDK_MIO_PTP_DPLL_INCR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_DPLL_INCR_FUNC(void)
{
    return 0x807000000f80ll;
}

#define typedef_BDK_MIO_PTP_DPLL_INCR bdk_mio_ptp_dpll_incr_t
#define bustype_BDK_MIO_PTP_DPLL_INCR BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_DPLL_INCR "MIO_PTP_DPLL_INCR"
#define device_bar_BDK_MIO_PTP_DPLL_INCR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_DPLL_INCR 0
#define arguments_BDK_MIO_PTP_DPLL_INCR -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_evt_cnt
 *
 * PTP Event Counter Register
 * This register contains the PTP event counter.
 */
union bdk_mio_ptp_evt_cnt
{
    uint64_t u;
    struct bdk_mio_ptp_evt_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t cntr                  : 64; /**< [ 63:  0](R/W/H) PTP event counter. Writing to this register increments this register by the
                                                                 value of the write data. The register counts down by one for every
                                                                 MIO_PTP_CLOCK_CFG[EVCNT_EDGE] edge of MIO_PTP_CLOCK_CFG[EVCNT_IN]. When this
                                                                 register equals zero, an interrupt is generated. When this register equals zero
                                                                 and PTP event is still enabled (MIO_PTP_CLOCK_CFG[EVCNT_EN]), the counter will
                                                                 roll over to negative to continue counting down whenever new event comes. */
#else /* Word 0 - Little Endian */
        uint64_t cntr                  : 64; /**< [ 63:  0](R/W/H) PTP event counter. Writing to this register increments this register by the
                                                                 value of the write data. The register counts down by one for every
                                                                 MIO_PTP_CLOCK_CFG[EVCNT_EDGE] edge of MIO_PTP_CLOCK_CFG[EVCNT_IN]. When this
                                                                 register equals zero, an interrupt is generated. When this register equals zero
                                                                 and PTP event is still enabled (MIO_PTP_CLOCK_CFG[EVCNT_EN]), the counter will
                                                                 roll over to negative to continue counting down whenever new event comes. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_evt_cnt_s cn; */
};
typedef union bdk_mio_ptp_evt_cnt bdk_mio_ptp_evt_cnt_t;

#define BDK_MIO_PTP_EVT_CNT BDK_MIO_PTP_EVT_CNT_FUNC()
static inline uint64_t BDK_MIO_PTP_EVT_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_EVT_CNT_FUNC(void)
{
    return 0x807000000f28ll;
}

#define typedef_BDK_MIO_PTP_EVT_CNT bdk_mio_ptp_evt_cnt_t
#define bustype_BDK_MIO_PTP_EVT_CNT BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_EVT_CNT "MIO_PTP_EVT_CNT"
#define device_bar_BDK_MIO_PTP_EVT_CNT 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_EVT_CNT 0
#define arguments_BDK_MIO_PTP_EVT_CNT -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_int
 *
 * PTP Interrupt Register
 * This register contains the PTP interrupts.
 */
union bdk_mio_ptp_int
{
    uint64_t u;
    struct bdk_mio_ptp_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t dpll_int              : 1;  /**< [  1:  1](R/W1C/H) Digital PLL error. */
        uint64_t evt_int               : 1;  /**< [  0:  0](R/W1C/H) PTP event observed. See MIO_PTP_EVT_CNT for details. */
#else /* Word 0 - Little Endian */
        uint64_t evt_int               : 1;  /**< [  0:  0](R/W1C/H) PTP event observed. See MIO_PTP_EVT_CNT for details. */
        uint64_t dpll_int              : 1;  /**< [  1:  1](R/W1C/H) Digital PLL error. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_int_s cn; */
};
typedef union bdk_mio_ptp_int bdk_mio_ptp_int_t;

#define BDK_MIO_PTP_INT BDK_MIO_PTP_INT_FUNC()
static inline uint64_t BDK_MIO_PTP_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_INT_FUNC(void)
{
    return 0x807000000f70ll;
}

#define typedef_BDK_MIO_PTP_INT bdk_mio_ptp_int_t
#define bustype_BDK_MIO_PTP_INT BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_INT "MIO_PTP_INT"
#define device_bar_BDK_MIO_PTP_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_INT 0
#define arguments_BDK_MIO_PTP_INT -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_int_ena_w1c
 *
 * PTP Interrupt Enable Register
 * This register clears interrupt enable bits.
 */
union bdk_mio_ptp_int_ena_w1c
{
    uint64_t u;
    struct bdk_mio_ptp_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t dpll_int              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MIO_PTP_INT[DPLL_INT]. */
        uint64_t evt_int               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MIO_PTP_INT[EVT_INT]. */
#else /* Word 0 - Little Endian */
        uint64_t evt_int               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MIO_PTP_INT[EVT_INT]. */
        uint64_t dpll_int              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MIO_PTP_INT[DPLL_INT]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_int_ena_w1c_s cn; */
};
typedef union bdk_mio_ptp_int_ena_w1c bdk_mio_ptp_int_ena_w1c_t;

#define BDK_MIO_PTP_INT_ENA_W1C BDK_MIO_PTP_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_MIO_PTP_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_INT_ENA_W1C_FUNC(void)
{
    return 0x807000000fa0ll;
}

#define typedef_BDK_MIO_PTP_INT_ENA_W1C bdk_mio_ptp_int_ena_w1c_t
#define bustype_BDK_MIO_PTP_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_INT_ENA_W1C "MIO_PTP_INT_ENA_W1C"
#define device_bar_BDK_MIO_PTP_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_INT_ENA_W1C 0
#define arguments_BDK_MIO_PTP_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_int_ena_w1s
 *
 * PTP Interrupt Enable W1S Register
 * This register sets interrupt enable bits.
 */
union bdk_mio_ptp_int_ena_w1s
{
    uint64_t u;
    struct bdk_mio_ptp_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t dpll_int              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MIO_PTP_INT[DPLL_INT]. */
        uint64_t evt_int               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MIO_PTP_INT[EVT_INT]. */
#else /* Word 0 - Little Endian */
        uint64_t evt_int               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MIO_PTP_INT[EVT_INT]. */
        uint64_t dpll_int              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MIO_PTP_INT[DPLL_INT]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_int_ena_w1s_s cn; */
};
typedef union bdk_mio_ptp_int_ena_w1s bdk_mio_ptp_int_ena_w1s_t;

#define BDK_MIO_PTP_INT_ENA_W1S BDK_MIO_PTP_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_MIO_PTP_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_INT_ENA_W1S_FUNC(void)
{
    return 0x807000000fa8ll;
}

#define typedef_BDK_MIO_PTP_INT_ENA_W1S bdk_mio_ptp_int_ena_w1s_t
#define bustype_BDK_MIO_PTP_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_INT_ENA_W1S "MIO_PTP_INT_ENA_W1S"
#define device_bar_BDK_MIO_PTP_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_INT_ENA_W1S 0
#define arguments_BDK_MIO_PTP_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_int_w1s
 *
 * PTP Interrupt W1S Register
 * This register sets interrupt bits.
 */
union bdk_mio_ptp_int_w1s
{
    uint64_t u;
    struct bdk_mio_ptp_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t dpll_int              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MIO_PTP_INT[DPLL_INT]. */
        uint64_t evt_int               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MIO_PTP_INT[EVT_INT]. */
#else /* Word 0 - Little Endian */
        uint64_t evt_int               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MIO_PTP_INT[EVT_INT]. */
        uint64_t dpll_int              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MIO_PTP_INT[DPLL_INT]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_int_w1s_s cn; */
};
typedef union bdk_mio_ptp_int_w1s bdk_mio_ptp_int_w1s_t;

#define BDK_MIO_PTP_INT_W1S BDK_MIO_PTP_INT_W1S_FUNC()
static inline uint64_t BDK_MIO_PTP_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_INT_W1S_FUNC(void)
{
    return 0x807000000f78ll;
}

#define typedef_BDK_MIO_PTP_INT_W1S bdk_mio_ptp_int_w1s_t
#define bustype_BDK_MIO_PTP_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_INT_W1S "MIO_PTP_INT_W1S"
#define device_bar_BDK_MIO_PTP_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_INT_W1S 0
#define arguments_BDK_MIO_PTP_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_msix_pba#
 *
 * PTP MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the MIO_PTP_INT_VEC_E
 * enumeration.
 */
union bdk_mio_ptp_msix_pbax
{
    uint64_t u;
    struct bdk_mio_ptp_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO) Pending message for the associated MIO_PTP_MSIX_VEC()_CTL, enumerated by
                                                                 MIO_PTP_INT_VEC_E. Bits
                                                                 that have no associated MIO_PTP_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO) Pending message for the associated MIO_PTP_MSIX_VEC()_CTL, enumerated by
                                                                 MIO_PTP_INT_VEC_E. Bits
                                                                 that have no associated MIO_PTP_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_msix_pbax_s cn; */
};
typedef union bdk_mio_ptp_msix_pbax bdk_mio_ptp_msix_pbax_t;

static inline uint64_t BDK_MIO_PTP_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_MSIX_PBAX(unsigned long a)
{
    if (a==0)
        return 0x807000ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("MIO_PTP_MSIX_PBAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_MIO_PTP_MSIX_PBAX(a) bdk_mio_ptp_msix_pbax_t
#define bustype_BDK_MIO_PTP_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_MSIX_PBAX(a) "MIO_PTP_MSIX_PBAX"
#define device_bar_BDK_MIO_PTP_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MIO_PTP_MSIX_PBAX(a) (a)
#define arguments_BDK_MIO_PTP_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) mio_ptp_msix_vec#_addr
 *
 * PTP MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the MIO_PTP_INT_VEC_E enumeration.
 */
union bdk_mio_ptp_msix_vecx_addr
{
    uint64_t u;
    struct bdk_mio_ptp_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MIO_PTP_MSIX_VEC()_ADDR, MIO_PTP_MSIX_VEC()_CTL, and
                                                                 corresponding
                                                                 bit of MIO_PTP_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 If PCCPF_MIO_PTP_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MIO_PTP_MSIX_VEC()_ADDR, MIO_PTP_MSIX_VEC()_CTL, and
                                                                 corresponding
                                                                 bit of MIO_PTP_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 If PCCPF_MIO_PTP_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_ptp_msix_vecx_addr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MIO_PTP_MSIX_VEC()_ADDR, MIO_PTP_MSIX_VEC()_CTL, and
                                                                 corresponding
                                                                 bit of MIO_PTP_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 If PCCPF_MIO_PTP_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MIO_PTP_MSIX_VEC()_ADDR, MIO_PTP_MSIX_VEC()_CTL, and
                                                                 corresponding
                                                                 bit of MIO_PTP_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 If PCCPF_MIO_PTP_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_ptp_msix_vecx_addr_s cn9; */
};
typedef union bdk_mio_ptp_msix_vecx_addr bdk_mio_ptp_msix_vecx_addr_t;

static inline uint64_t BDK_MIO_PTP_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_MSIX_VECX_ADDR(unsigned long a)
{
    if (a<=1)
        return 0x807000f00000ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("MIO_PTP_MSIX_VECX_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_MIO_PTP_MSIX_VECX_ADDR(a) bdk_mio_ptp_msix_vecx_addr_t
#define bustype_BDK_MIO_PTP_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_MSIX_VECX_ADDR(a) "MIO_PTP_MSIX_VECX_ADDR"
#define device_bar_BDK_MIO_PTP_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MIO_PTP_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_MIO_PTP_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) mio_ptp_msix_vec#_ctl
 *
 * PTP MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the MIO_PTP_INT_VEC_E enumeration.
 */
union bdk_mio_ptp_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_mio_ptp_msix_vecx_ctl_s
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
    struct bdk_mio_ptp_msix_vecx_ctl_cn8
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
    /* struct bdk_mio_ptp_msix_vecx_ctl_s cn9; */
};
typedef union bdk_mio_ptp_msix_vecx_ctl bdk_mio_ptp_msix_vecx_ctl_t;

static inline uint64_t BDK_MIO_PTP_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_MSIX_VECX_CTL(unsigned long a)
{
    if (a<=1)
        return 0x807000f00008ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("MIO_PTP_MSIX_VECX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_MIO_PTP_MSIX_VECX_CTL(a) bdk_mio_ptp_msix_vecx_ctl_t
#define bustype_BDK_MIO_PTP_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_MSIX_VECX_CTL(a) "MIO_PTP_MSIX_VECX_CTL"
#define device_bar_BDK_MIO_PTP_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MIO_PTP_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_MIO_PTP_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) mio_ptp_pps_hi_incr
 *
 * PTP PPS High Increment Register
 * This register contains the PTP PPS threshold increment on pre-inverted PTP_PPS rising edge.
 * See MIO_PTP_PPS_THRESH_HI for details.
 */
union bdk_mio_ptp_pps_hi_incr
{
    uint64_t u;
    struct bdk_mio_ptp_pps_hi_incr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_pps_hi_incr_s cn; */
};
typedef union bdk_mio_ptp_pps_hi_incr bdk_mio_ptp_pps_hi_incr_t;

#define BDK_MIO_PTP_PPS_HI_INCR BDK_MIO_PTP_PPS_HI_INCR_FUNC()
static inline uint64_t BDK_MIO_PTP_PPS_HI_INCR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_PPS_HI_INCR_FUNC(void)
{
    return 0x807000000f60ll;
}

#define typedef_BDK_MIO_PTP_PPS_HI_INCR bdk_mio_ptp_pps_hi_incr_t
#define bustype_BDK_MIO_PTP_PPS_HI_INCR BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_PPS_HI_INCR "MIO_PTP_PPS_HI_INCR"
#define device_bar_BDK_MIO_PTP_PPS_HI_INCR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_PPS_HI_INCR 0
#define arguments_BDK_MIO_PTP_PPS_HI_INCR -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_pps_lo_incr
 *
 * PTP PPS Low Increment Register
 * This register contains the PTP PPS threshold increment on pre-inverted PTP_PPS falling edge.
 * See MIO_PTP_PPS_THRESH_HI for details.
 */
union bdk_mio_ptp_pps_lo_incr
{
    uint64_t u;
    struct bdk_mio_ptp_pps_lo_incr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_pps_lo_incr_s cn; */
};
typedef union bdk_mio_ptp_pps_lo_incr bdk_mio_ptp_pps_lo_incr_t;

#define BDK_MIO_PTP_PPS_LO_INCR BDK_MIO_PTP_PPS_LO_INCR_FUNC()
static inline uint64_t BDK_MIO_PTP_PPS_LO_INCR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_PPS_LO_INCR_FUNC(void)
{
    return 0x807000000f68ll;
}

#define typedef_BDK_MIO_PTP_PPS_LO_INCR bdk_mio_ptp_pps_lo_incr_t
#define bustype_BDK_MIO_PTP_PPS_LO_INCR BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_PPS_LO_INCR "MIO_PTP_PPS_LO_INCR"
#define device_bar_BDK_MIO_PTP_PPS_LO_INCR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_PPS_LO_INCR 0
#define arguments_BDK_MIO_PTP_PPS_LO_INCR -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_pps_thresh_hi
 *
 * PTP PPS Threshold High Register
 * This register contains the high bytes of the PTP PPS threshold.
 * Writes to MIO_PTP_PPS_THRESH_HI also clear MIO_PTP_PPS_THRESH_LO; in order to update all 96
 * bits, writes MIO_PTP_PPS_THRESH_HI followed by MIO_PTP_PPS_THRESH_LO.
 * This threshold {MIO_PTP_PPS_THRESH_HI, MIO_PTP_PPS_THRESH_LO}  is a rolling threshold that
 * will be updated by hardware:
 *   When current PTP_PPS before inversion (defined by MIO_PTP_CLOCK_CFG[PPS_INV]) is zero,
 *   and {MIO_PTP_CLOCK_HI/LO} \>=  {MIO_PTP_PPS_THRESH_HI/LO}, the pre-inverted PTP_PPS will
 *   update to one, and {MIO_PTP_PPS_THRESH_HI/LO} will increment by MIO_PTP_PPS_HI_INCR.
 *   When current PTP_PPS before inversion (defined by MIO_PTP_CLOCK_CFG[PPS_INV]) is one,
 *   and {MIO_PTP_CLOCK_HI/LO} \>=  {MIO_PTP_PPS_THRESH_HI/LO}, the pre-inverted PTP_PPS will
 *   update to zero, and {MIO_PTP_PPS_THRESH_HI/LO} will increment by MIO_PTP_PPS_LO_INCR.
 */
union bdk_mio_ptp_pps_thresh_hi
{
    uint64_t u;
    struct bdk_mio_ptp_pps_thresh_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_pps_thresh_hi_s cn; */
};
typedef union bdk_mio_ptp_pps_thresh_hi bdk_mio_ptp_pps_thresh_hi_t;

#define BDK_MIO_PTP_PPS_THRESH_HI BDK_MIO_PTP_PPS_THRESH_HI_FUNC()
static inline uint64_t BDK_MIO_PTP_PPS_THRESH_HI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_PPS_THRESH_HI_FUNC(void)
{
    return 0x807000000f58ll;
}

#define typedef_BDK_MIO_PTP_PPS_THRESH_HI bdk_mio_ptp_pps_thresh_hi_t
#define bustype_BDK_MIO_PTP_PPS_THRESH_HI BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_PPS_THRESH_HI "MIO_PTP_PPS_THRESH_HI"
#define device_bar_BDK_MIO_PTP_PPS_THRESH_HI 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_PPS_THRESH_HI 0
#define arguments_BDK_MIO_PTP_PPS_THRESH_HI -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_pps_thresh_lo
 *
 * PTP PPS Low Register
 * This register contains the low bytes of the PTP PPS threshold.
 * See MIO_PTP_PPS_THRESH_HI for details.
 */
union bdk_mio_ptp_pps_thresh_lo
{
    uint64_t u;
    struct bdk_mio_ptp_pps_thresh_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W/H) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W/H) Fractions of nanoseconds. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_pps_thresh_lo_s cn; */
};
typedef union bdk_mio_ptp_pps_thresh_lo bdk_mio_ptp_pps_thresh_lo_t;

#define BDK_MIO_PTP_PPS_THRESH_LO BDK_MIO_PTP_PPS_THRESH_LO_FUNC()
static inline uint64_t BDK_MIO_PTP_PPS_THRESH_LO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_PPS_THRESH_LO_FUNC(void)
{
    return 0x807000000f50ll;
}

#define typedef_BDK_MIO_PTP_PPS_THRESH_LO bdk_mio_ptp_pps_thresh_lo_t
#define bustype_BDK_MIO_PTP_PPS_THRESH_LO BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_PPS_THRESH_LO "MIO_PTP_PPS_THRESH_LO"
#define device_bar_BDK_MIO_PTP_PPS_THRESH_LO 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_PPS_THRESH_LO 0
#define arguments_BDK_MIO_PTP_PPS_THRESH_LO -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_sysck_hi_incr
 *
 * PTP SYSCK High Increment Register
 * This register contains the PTP SYSCK threshold increment on pre-inverted PTP_SYSCK rising
 * edge.
 * See MIO_PTP_SYSCK_THRESH_HI for details.
 */
union bdk_mio_ptp_sysck_hi_incr
{
    uint64_t u;
    struct bdk_mio_ptp_sysck_hi_incr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_sysck_hi_incr_s cn; */
};
typedef union bdk_mio_ptp_sysck_hi_incr bdk_mio_ptp_sysck_hi_incr_t;

#define BDK_MIO_PTP_SYSCK_HI_INCR BDK_MIO_PTP_SYSCK_HI_INCR_FUNC()
static inline uint64_t BDK_MIO_PTP_SYSCK_HI_INCR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_SYSCK_HI_INCR_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x807000000fc0ll;
    __bdk_csr_fatal("MIO_PTP_SYSCK_HI_INCR", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_PTP_SYSCK_HI_INCR bdk_mio_ptp_sysck_hi_incr_t
#define bustype_BDK_MIO_PTP_SYSCK_HI_INCR BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_SYSCK_HI_INCR "MIO_PTP_SYSCK_HI_INCR"
#define device_bar_BDK_MIO_PTP_SYSCK_HI_INCR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_SYSCK_HI_INCR 0
#define arguments_BDK_MIO_PTP_SYSCK_HI_INCR -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_sysck_lo_incr
 *
 * PTP SYSCK Low Increment Register
 * This register contains the PTP SYSCK threshold increment on pre-inverted PTP_SYSCK falling
 * edge.
 * See MIO_PTP_SYSCK_THRESH_HI for details.
 */
union bdk_mio_ptp_sysck_lo_incr
{
    uint64_t u;
    struct bdk_mio_ptp_sysck_lo_incr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W) Fractions of nanoseconds. */
        uint64_t nanosec               : 32; /**< [ 63: 32](R/W) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_sysck_lo_incr_s cn; */
};
typedef union bdk_mio_ptp_sysck_lo_incr bdk_mio_ptp_sysck_lo_incr_t;

#define BDK_MIO_PTP_SYSCK_LO_INCR BDK_MIO_PTP_SYSCK_LO_INCR_FUNC()
static inline uint64_t BDK_MIO_PTP_SYSCK_LO_INCR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_SYSCK_LO_INCR_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x807000000fc8ll;
    __bdk_csr_fatal("MIO_PTP_SYSCK_LO_INCR", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_PTP_SYSCK_LO_INCR bdk_mio_ptp_sysck_lo_incr_t
#define bustype_BDK_MIO_PTP_SYSCK_LO_INCR BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_SYSCK_LO_INCR "MIO_PTP_SYSCK_LO_INCR"
#define device_bar_BDK_MIO_PTP_SYSCK_LO_INCR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_SYSCK_LO_INCR 0
#define arguments_BDK_MIO_PTP_SYSCK_LO_INCR -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_sysck_thresh_hi
 *
 * PTP SYSCK Threshold High Register
 * This register contains the high bytes of the PTP SYSCK threshold.
 * Writes to MIO_PTP_SYSCK_THRESH_HI also clear MIO_PTP_SYSCK_THRESH_LO; in order to update all
 * 96
 * bits, writes MIO_PTP_SYSCK_THRESH_HI followed by MIO_PTP_SYSCK_THRESH_LO.
 * This threshold {MIO_PTP_SYSCK_THRESH_HI, MIO_PTP_SYSCK_THRESH_LO}  is a rolling threshold that
 * will be updated by hardware:
 * * When current PTP_SYSCK is zero,
 *   and {MIO_PTP_CLOCK_HI/LO} \>=  {MIO_PTP_SYSCK_THRESH_HI/LO}, the pre-inverted PTP_SYSCK will
 *   update to one, and {MIO_PTP_SYSCK_THRESH_HI/LO} will increment by MIO_PTP_SYSCK_HI_INCR.
 * * When current PTP_SYSCK before inversion is one,
 *   and {MIO_PTP_CLOCK_HI/LO} \>=  {MIO_PTP_SYSCK_THRESH_HI/LO}, the pre-inverted PTP_SYSCK will
 *   update to zero, and {MIO_PTP_SYSCK_THRESH_HI/LO} will increment by MIO_PTP_SYSCK_LO_INCR.
 */
union bdk_mio_ptp_sysck_thresh_hi
{
    uint64_t u;
    struct bdk_mio_ptp_sysck_thresh_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_sysck_thresh_hi_s cn; */
};
typedef union bdk_mio_ptp_sysck_thresh_hi bdk_mio_ptp_sysck_thresh_hi_t;

#define BDK_MIO_PTP_SYSCK_THRESH_HI BDK_MIO_PTP_SYSCK_THRESH_HI_FUNC()
static inline uint64_t BDK_MIO_PTP_SYSCK_THRESH_HI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_SYSCK_THRESH_HI_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x807000000fb8ll;
    __bdk_csr_fatal("MIO_PTP_SYSCK_THRESH_HI", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_PTP_SYSCK_THRESH_HI bdk_mio_ptp_sysck_thresh_hi_t
#define bustype_BDK_MIO_PTP_SYSCK_THRESH_HI BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_SYSCK_THRESH_HI "MIO_PTP_SYSCK_THRESH_HI"
#define device_bar_BDK_MIO_PTP_SYSCK_THRESH_HI 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_SYSCK_THRESH_HI 0
#define arguments_BDK_MIO_PTP_SYSCK_THRESH_HI -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_sysck_thresh_lo
 *
 * PTP SYSCK Low Register
 * This register contains the low bytes of the PTP SYSCK threshold.
 * See MIO_PTP_SYSCK_THRESH_HI for details.
 */
union bdk_mio_ptp_sysck_thresh_lo
{
    uint64_t u;
    struct bdk_mio_ptp_sysck_thresh_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W/H) Fractions of nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t frnanosec             : 32; /**< [ 31:  0](R/W/H) Fractions of nanoseconds. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_sysck_thresh_lo_s cn; */
};
typedef union bdk_mio_ptp_sysck_thresh_lo bdk_mio_ptp_sysck_thresh_lo_t;

#define BDK_MIO_PTP_SYSCK_THRESH_LO BDK_MIO_PTP_SYSCK_THRESH_LO_FUNC()
static inline uint64_t BDK_MIO_PTP_SYSCK_THRESH_LO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_SYSCK_THRESH_LO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x807000000fb0ll;
    __bdk_csr_fatal("MIO_PTP_SYSCK_THRESH_LO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_PTP_SYSCK_THRESH_LO bdk_mio_ptp_sysck_thresh_lo_t
#define bustype_BDK_MIO_PTP_SYSCK_THRESH_LO BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_SYSCK_THRESH_LO "MIO_PTP_SYSCK_THRESH_LO"
#define device_bar_BDK_MIO_PTP_SYSCK_THRESH_LO 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_SYSCK_THRESH_LO 0
#define arguments_BDK_MIO_PTP_SYSCK_THRESH_LO -1,-1,-1,-1

/**
 * Register (NCB) mio_ptp_timestamp
 *
 * PTP Timestamp Register
 * This register contains the timestamp latched on MIO_PTP_CLOCK_CFG[TSTMP_EDGE] edge of
 * MIO_PTP_CLOCK_CFG[TSTMP_IN].
 */
union bdk_mio_ptp_timestamp
{
    uint64_t u;
    struct bdk_mio_ptp_timestamp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Timestamp in nanoseconds. */
#else /* Word 0 - Little Endian */
        uint64_t nanosec               : 64; /**< [ 63:  0](R/W/H) Timestamp in nanoseconds. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_ptp_timestamp_s cn; */
};
typedef union bdk_mio_ptp_timestamp bdk_mio_ptp_timestamp_t;

#define BDK_MIO_PTP_TIMESTAMP BDK_MIO_PTP_TIMESTAMP_FUNC()
static inline uint64_t BDK_MIO_PTP_TIMESTAMP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_PTP_TIMESTAMP_FUNC(void)
{
    return 0x807000000f20ll;
}

#define typedef_BDK_MIO_PTP_TIMESTAMP bdk_mio_ptp_timestamp_t
#define bustype_BDK_MIO_PTP_TIMESTAMP BDK_CSR_TYPE_NCB
#define basename_BDK_MIO_PTP_TIMESTAMP "MIO_PTP_TIMESTAMP"
#define device_bar_BDK_MIO_PTP_TIMESTAMP 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_PTP_TIMESTAMP 0
#define arguments_BDK_MIO_PTP_TIMESTAMP -1,-1,-1,-1

#endif /* __BDK_CSRS_MIO_PTP_H__ */
