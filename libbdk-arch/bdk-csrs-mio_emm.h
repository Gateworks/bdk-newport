#ifndef __BDK_CSRS_MIO_EMM_H__
#define __BDK_CSRS_MIO_EMM_H__
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
 * OcteonTX MIO_EMM.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration mio_emm_bar_e
 *
 * eMMC Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_MIO_EMM_BAR_E_MIO_EMM_PF_BAR0_CN8 (0x87e009000000ll)
#define BDK_MIO_EMM_BAR_E_MIO_EMM_PF_BAR0_CN8_SIZE 0x800000ull
#define BDK_MIO_EMM_BAR_E_MIO_EMM_PF_BAR0_CN9 (0x87e009000000ll)
#define BDK_MIO_EMM_BAR_E_MIO_EMM_PF_BAR0_CN9_SIZE 0x10000ull
#define BDK_MIO_EMM_BAR_E_MIO_EMM_PF_BAR4 (0x87e009f00000ll)
#define BDK_MIO_EMM_BAR_E_MIO_EMM_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration mio_emm_int_vec_e
 *
 * eMMC MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_MIO_EMM_INT_VEC_E_DMA_INT_DONE (8)
#define BDK_MIO_EMM_INT_VEC_E_DMA_INT_FIFO (7)
#define BDK_MIO_EMM_INT_VEC_E_EMM_BUF_DONE (0)
#define BDK_MIO_EMM_INT_VEC_E_EMM_CMD_DONE (1)
#define BDK_MIO_EMM_INT_VEC_E_EMM_CMD_ERR (3)
#define BDK_MIO_EMM_INT_VEC_E_EMM_DMA_DONE (2)
#define BDK_MIO_EMM_INT_VEC_E_EMM_DMA_ERR (4)
#define BDK_MIO_EMM_INT_VEC_E_EMM_SWITCH_DONE (5)
#define BDK_MIO_EMM_INT_VEC_E_EMM_SWITCH_ERR (6)
#define BDK_MIO_EMM_INT_VEC_E_NCB_FLT (9)
#define BDK_MIO_EMM_INT_VEC_E_NCB_RAS (0xa)

/**
 * Register (RSL) mio_emm_access_wdog
 *
 * eMMC Access Watchdog Register
 */
union bdk_mio_emm_access_wdog
{
    uint64_t u;
    struct bdk_mio_emm_access_wdog_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t clk_cnt               : 32; /**< [ 31:  0](R/W) Number of coprocessor-clock cycles to allow for a store operation to the device
                                                                 to complete before hardware will halt the operation.
                                                                 Hardware will inject an error on the next 512-byte block boundary.   The pending DMA
                                                                 operation can be resumed or terminated. A value of zero disables timer. */
#else /* Word 0 - Little Endian */
        uint64_t clk_cnt               : 32; /**< [ 31:  0](R/W) Number of coprocessor-clock cycles to allow for a store operation to the device
                                                                 to complete before hardware will halt the operation.
                                                                 Hardware will inject an error on the next 512-byte block boundary.   The pending DMA
                                                                 operation can be resumed or terminated. A value of zero disables timer. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_access_wdog_s cn; */
};
typedef union bdk_mio_emm_access_wdog bdk_mio_emm_access_wdog_t;

#define BDK_MIO_EMM_ACCESS_WDOG BDK_MIO_EMM_ACCESS_WDOG_FUNC()
static inline uint64_t BDK_MIO_EMM_ACCESS_WDOG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_ACCESS_WDOG_FUNC(void)
{
    return 0x87e0090020f0ll;
}

#define typedef_BDK_MIO_EMM_ACCESS_WDOG bdk_mio_emm_access_wdog_t
#define bustype_BDK_MIO_EMM_ACCESS_WDOG BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_ACCESS_WDOG "MIO_EMM_ACCESS_WDOG"
#define device_bar_BDK_MIO_EMM_ACCESS_WDOG 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_ACCESS_WDOG 0
#define arguments_BDK_MIO_EMM_ACCESS_WDOG -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_buf_dat
 *
 * eMMC Data Buffer Access Register
 */
union bdk_mio_emm_buf_dat
{
    uint64_t u;
    struct bdk_mio_emm_buf_dat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W/H) Direct access to the 1 KB data buffer memory. Address specified by MIO_EMM_BUF_IDX. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W/H) Direct access to the 1 KB data buffer memory. Address specified by MIO_EMM_BUF_IDX. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_buf_dat_s cn8; */
    struct bdk_mio_emm_buf_dat_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W/H) Direct access to the 1 KB data buffer memory. Address specified by
                                                                 MIO_EMM_BUF_IDX. Data is returned in MIO_EMM_BUF_DAT using a big-endian
                                                                 ordering. The first byte read from the buffer will be returned in bits \<63:56\>,
                                                                 the second byte in bits \<55:48\> continuing through the eighth byte which is
                                                                 stored in bits \<7:0\>. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W/H) Direct access to the 1 KB data buffer memory. Address specified by
                                                                 MIO_EMM_BUF_IDX. Data is returned in MIO_EMM_BUF_DAT using a big-endian
                                                                 ordering. The first byte read from the buffer will be returned in bits \<63:56\>,
                                                                 the second byte in bits \<55:48\> continuing through the eighth byte which is
                                                                 stored in bits \<7:0\>. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_mio_emm_buf_dat bdk_mio_emm_buf_dat_t;

#define BDK_MIO_EMM_BUF_DAT BDK_MIO_EMM_BUF_DAT_FUNC()
static inline uint64_t BDK_MIO_EMM_BUF_DAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_BUF_DAT_FUNC(void)
{
    return 0x87e0090020e8ll;
}

#define typedef_BDK_MIO_EMM_BUF_DAT bdk_mio_emm_buf_dat_t
#define bustype_BDK_MIO_EMM_BUF_DAT BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_BUF_DAT "MIO_EMM_BUF_DAT"
#define device_bar_BDK_MIO_EMM_BUF_DAT 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_BUF_DAT 0
#define arguments_BDK_MIO_EMM_BUF_DAT -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_buf_idx
 *
 * eMMC Data Buffer Address Register
 */
union bdk_mio_emm_buf_idx
{
    uint64_t u;
    struct bdk_mio_emm_buf_idx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t inc                   : 1;  /**< [ 16: 16](R/W) Automatically advance [BUF_NUM]/[OFFSET] after each access to
                                                                 MIO_EMM_BUF_DAT. Wraps after the last offset of the last data buffer. */
        uint64_t reserved_7_15         : 9;
        uint64_t buf_num               : 1;  /**< [  6:  6](R/W/H) Specify the data buffer for the next access to MIO_EMM_BUF_DAT. */
        uint64_t offset                : 6;  /**< [  5:  0](R/W/H) Specify the 8B data buffer offset for the next access to MIO_EMM_BUF_DAT. */
#else /* Word 0 - Little Endian */
        uint64_t offset                : 6;  /**< [  5:  0](R/W/H) Specify the 8B data buffer offset for the next access to MIO_EMM_BUF_DAT. */
        uint64_t buf_num               : 1;  /**< [  6:  6](R/W/H) Specify the data buffer for the next access to MIO_EMM_BUF_DAT. */
        uint64_t reserved_7_15         : 9;
        uint64_t inc                   : 1;  /**< [ 16: 16](R/W) Automatically advance [BUF_NUM]/[OFFSET] after each access to
                                                                 MIO_EMM_BUF_DAT. Wraps after the last offset of the last data buffer. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_buf_idx_s cn; */
};
typedef union bdk_mio_emm_buf_idx bdk_mio_emm_buf_idx_t;

#define BDK_MIO_EMM_BUF_IDX BDK_MIO_EMM_BUF_IDX_FUNC()
static inline uint64_t BDK_MIO_EMM_BUF_IDX_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_BUF_IDX_FUNC(void)
{
    return 0x87e0090020e0ll;
}

#define typedef_BDK_MIO_EMM_BUF_IDX bdk_mio_emm_buf_idx_t
#define bustype_BDK_MIO_EMM_BUF_IDX BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_BUF_IDX "MIO_EMM_BUF_IDX"
#define device_bar_BDK_MIO_EMM_BUF_IDX 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_BUF_IDX 0
#define arguments_BDK_MIO_EMM_BUF_IDX -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_calb
 *
 * eMMC Calbration Register
 * This register initiates delay line characterization.
 */
union bdk_mio_emm_calb
{
    uint64_t u;
    struct bdk_mio_emm_calb_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t start                 : 1;  /**< [  0:  0](R/W/H) Start calibration. Writes to this register send a pattern through the
                                                                 internal delay lines and is used to estimate delay.  Setting START
                                                                 will begin the process.  Calbration is complete when MIO_EMM_TAP
                                                                 has a non-zero value.  This step is typically preformed when the
                                                                 device is at operating temperature and voltage.  Clearing the START
                                                                 will clear the MIO_EMM_TAP register and allow a new calbration to
                                                                 occur.  This field should not be set unless MIO_EMM_CFG[BUS_ENA] is
                                                                 zero. */
#else /* Word 0 - Little Endian */
        uint64_t start                 : 1;  /**< [  0:  0](R/W/H) Start calibration. Writes to this register send a pattern through the
                                                                 internal delay lines and is used to estimate delay.  Setting START
                                                                 will begin the process.  Calbration is complete when MIO_EMM_TAP
                                                                 has a non-zero value.  This step is typically preformed when the
                                                                 device is at operating temperature and voltage.  Clearing the START
                                                                 will clear the MIO_EMM_TAP register and allow a new calbration to
                                                                 occur.  This field should not be set unless MIO_EMM_CFG[BUS_ENA] is
                                                                 zero. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_calb_s cn9; */
    /* struct bdk_mio_emm_calb_s cn96xxp1; */
    struct bdk_mio_emm_calb_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t start                 : 1;  /**< [  0:  0](R/W/H) Start calibration. Writes to this register send a pattern through the
                                                                 internal delay lines and is used to estimate delay.  Setting START
                                                                 will begin the process.  Calibration is complete when MIO_EMM_TAP
                                                                 has a non-zero value.  This step is typically preformed when the
                                                                 device is at operating temperature and voltage.  Clearing the START
                                                                 will clear the MIO_EMM_TAP register and allow a new calibration to
                                                                 occur.  This field should not be set unless MIO_EMM_CFG[BUS_ENA] is
                                                                 zero. */
#else /* Word 0 - Little Endian */
        uint64_t start                 : 1;  /**< [  0:  0](R/W/H) Start calibration. Writes to this register send a pattern through the
                                                                 internal delay lines and is used to estimate delay.  Setting START
                                                                 will begin the process.  Calibration is complete when MIO_EMM_TAP
                                                                 has a non-zero value.  This step is typically preformed when the
                                                                 device is at operating temperature and voltage.  Clearing the START
                                                                 will clear the MIO_EMM_TAP register and allow a new calibration to
                                                                 occur.  This field should not be set unless MIO_EMM_CFG[BUS_ENA] is
                                                                 zero. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mio_emm_calb_cn96xxp3 cn98xx; */
    /* struct bdk_mio_emm_calb_cn96xxp3 cnf95xx; */
    /* struct bdk_mio_emm_calb_cn96xxp3 loki; */
};
typedef union bdk_mio_emm_calb bdk_mio_emm_calb_t;

#define BDK_MIO_EMM_CALB BDK_MIO_EMM_CALB_FUNC()
static inline uint64_t BDK_MIO_EMM_CALB_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_CALB_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e0090020c0ll;
    __bdk_csr_fatal("MIO_EMM_CALB", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_CALB bdk_mio_emm_calb_t
#define bustype_BDK_MIO_EMM_CALB BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_CALB "MIO_EMM_CALB"
#define device_bar_BDK_MIO_EMM_CALB 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_CALB 0
#define arguments_BDK_MIO_EMM_CALB -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_cfg
 *
 * eMMC Configuration Register
 */
union bdk_mio_emm_cfg
{
    uint64_t u;
    struct bdk_mio_emm_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t bus_ena               : 4;  /**< [  3:  0](R/W) eMMC bus enable mask.

                                                                 Setting bits 0..2 enables the corresponding EMMC_CMD[x] bit and allows that bus to operate.
                                                                 Bit 3 of [BUS_ENA] is reserved.

                                                                 Clearing all bits of this field will reset the other MIO_EMM_* registers
                                                                 and disable the EMMC_CLK.
                                                                 To ensure a proper reset, [BUS_ENA] should be cleared for a minimum of 2
                                                                 EMMC_CLK periods.  This period be determined by waiting twice the number of
                                                                 coprocessor clock cycles specified in MIO_EMM_MODE()[CLK_HI] and
                                                                 MIO_EMM_MODE()[CLK_LO].

                                                                 Setting one or more bits enables EMMC_CLK operation. */
#else /* Word 0 - Little Endian */
        uint64_t bus_ena               : 4;  /**< [  3:  0](R/W) eMMC bus enable mask.

                                                                 Setting bits 0..2 enables the corresponding EMMC_CMD[x] bit and allows that bus to operate.
                                                                 Bit 3 of [BUS_ENA] is reserved.

                                                                 Clearing all bits of this field will reset the other MIO_EMM_* registers
                                                                 and disable the EMMC_CLK.
                                                                 To ensure a proper reset, [BUS_ENA] should be cleared for a minimum of 2
                                                                 EMMC_CLK periods.  This period be determined by waiting twice the number of
                                                                 coprocessor clock cycles specified in MIO_EMM_MODE()[CLK_HI] and
                                                                 MIO_EMM_MODE()[CLK_LO].

                                                                 Setting one or more bits enables EMMC_CLK operation. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_cfg_s cn; */
};
typedef union bdk_mio_emm_cfg bdk_mio_emm_cfg_t;

#define BDK_MIO_EMM_CFG BDK_MIO_EMM_CFG_FUNC()
static inline uint64_t BDK_MIO_EMM_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_CFG_FUNC(void)
{
    return 0x87e009002000ll;
}

#define typedef_BDK_MIO_EMM_CFG bdk_mio_emm_cfg_t
#define bustype_BDK_MIO_EMM_CFG BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_CFG "MIO_EMM_CFG"
#define device_bar_BDK_MIO_EMM_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_CFG 0
#define arguments_BDK_MIO_EMM_CFG -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_cmd
 *
 * eMMC Command Register
 */
union bdk_mio_emm_cmd
{
    uint64_t u;
    struct bdk_mio_emm_cmd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t skip_busy             : 1;  /**< [ 62: 62](R/W) Controls when command is completed.
                                                                 0 = Command doesn't complete until card has dropped the BUSY signal.
                                                                 1 = Complete command regardless of the BUSY signal. Status of signal can be read in
                                                                 MIO_EMM_RSP_STS[RSP_BUSYBIT]. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W) Specify the eMMC bus. */
        uint64_t cmd_val               : 1;  /**< [ 59: 59](R/W/H) Request valid. Software writes this bit to a 1. Hardware clears it when the operation completes. */
        uint64_t reserved_56_58        : 3;
        uint64_t dbuf                  : 1;  /**< [ 55: 55](R/W) Specify the data buffer to be used for a block transfer. */
        uint64_t offset                : 6;  /**< [ 54: 49](R/W/H) Debug only. Specify the number of 8-byte transfers used in the command. Value is
                                                                 64-OFFSET. The block transfer still starts at the first byte in the 512 B data buffer.
                                                                 Software must ensure CMD16 has updated the card block length. */
        uint64_t reserved_43_48        : 6;
        uint64_t ctype_xor             : 2;  /**< [ 42: 41](R/W) Command type override; typically zero. Value is XOR'd with the default command type. See
                                                                 Command and Response Types for command types per command index. Types are:
                                                                 0x0 = No data.
                                                                 0x1 = Read data into Dbuf.
                                                                 0x2 = Write data from Dbuf.
                                                                 0x3 = Reserved. */
        uint64_t rtype_xor             : 3;  /**< [ 40: 38](R/W) Response type override; typically zero. Value is XOR'd with default response type. See
                                                                 Command and Response Types for response types per command index. Types are:
                                                                 0x0 = No Response.
                                                                 0x1 = R1, 48 bits.
                                                                 0x2 = R2, 136 bits.
                                                                 0x3 = R3, 48 bits.
                                                                 0x4 = R4, 48 bits.
                                                                 0x5 = R5, 48 bits.
                                                                 0x6, 0x7 = Reserved. */
        uint64_t cmd_idx               : 6;  /**< [ 37: 32](R/W/H) eMMC command. */
        uint64_t arg                   : 32; /**< [ 31:  0](R/W/H) eMMC command argument. */
#else /* Word 0 - Little Endian */
        uint64_t arg                   : 32; /**< [ 31:  0](R/W/H) eMMC command argument. */
        uint64_t cmd_idx               : 6;  /**< [ 37: 32](R/W/H) eMMC command. */
        uint64_t rtype_xor             : 3;  /**< [ 40: 38](R/W) Response type override; typically zero. Value is XOR'd with default response type. See
                                                                 Command and Response Types for response types per command index. Types are:
                                                                 0x0 = No Response.
                                                                 0x1 = R1, 48 bits.
                                                                 0x2 = R2, 136 bits.
                                                                 0x3 = R3, 48 bits.
                                                                 0x4 = R4, 48 bits.
                                                                 0x5 = R5, 48 bits.
                                                                 0x6, 0x7 = Reserved. */
        uint64_t ctype_xor             : 2;  /**< [ 42: 41](R/W) Command type override; typically zero. Value is XOR'd with the default command type. See
                                                                 Command and Response Types for command types per command index. Types are:
                                                                 0x0 = No data.
                                                                 0x1 = Read data into Dbuf.
                                                                 0x2 = Write data from Dbuf.
                                                                 0x3 = Reserved. */
        uint64_t reserved_43_48        : 6;
        uint64_t offset                : 6;  /**< [ 54: 49](R/W/H) Debug only. Specify the number of 8-byte transfers used in the command. Value is
                                                                 64-OFFSET. The block transfer still starts at the first byte in the 512 B data buffer.
                                                                 Software must ensure CMD16 has updated the card block length. */
        uint64_t dbuf                  : 1;  /**< [ 55: 55](R/W) Specify the data buffer to be used for a block transfer. */
        uint64_t reserved_56_58        : 3;
        uint64_t cmd_val               : 1;  /**< [ 59: 59](R/W/H) Request valid. Software writes this bit to a 1. Hardware clears it when the operation completes. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W) Specify the eMMC bus. */
        uint64_t skip_busy             : 1;  /**< [ 62: 62](R/W) Controls when command is completed.
                                                                 0 = Command doesn't complete until card has dropped the BUSY signal.
                                                                 1 = Complete command regardless of the BUSY signal. Status of signal can be read in
                                                                 MIO_EMM_RSP_STS[RSP_BUSYBIT]. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_cmd_s cn; */
};
typedef union bdk_mio_emm_cmd bdk_mio_emm_cmd_t;

#define BDK_MIO_EMM_CMD BDK_MIO_EMM_CMD_FUNC()
static inline uint64_t BDK_MIO_EMM_CMD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_CMD_FUNC(void)
{
    return 0x87e009002058ll;
}

#define typedef_BDK_MIO_EMM_CMD bdk_mio_emm_cmd_t
#define bustype_BDK_MIO_EMM_CMD BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_CMD "MIO_EMM_CMD"
#define device_bar_BDK_MIO_EMM_CMD 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_CMD 0
#define arguments_BDK_MIO_EMM_CMD -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_comp
 *
 * eMMC Compensation Register
 */
union bdk_mio_emm_comp
{
    uint64_t u;
    struct bdk_mio_emm_comp_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t pctl                  : 3;  /**< [ 10:  8](R/W) eMMC bus driver PCTL. Typical values:
                                                                 0x4 = 60 ohm.
                                                                 0x6 = 40 ohm.
                                                                 0x7 = 30 ohm. */
        uint64_t reserved_3_7          : 5;
        uint64_t nctl                  : 3;  /**< [  2:  0](R/W) eMMC bus driver NCTL. Typical values:
                                                                 0x4 = 60 ohm.
                                                                 0x6 = 40 ohm.
                                                                 0x7 = 30 ohm. */
#else /* Word 0 - Little Endian */
        uint64_t nctl                  : 3;  /**< [  2:  0](R/W) eMMC bus driver NCTL. Typical values:
                                                                 0x4 = 60 ohm.
                                                                 0x6 = 40 ohm.
                                                                 0x7 = 30 ohm. */
        uint64_t reserved_3_7          : 5;
        uint64_t pctl                  : 3;  /**< [ 10:  8](R/W) eMMC bus driver PCTL. Typical values:
                                                                 0x4 = 60 ohm.
                                                                 0x6 = 40 ohm.
                                                                 0x7 = 30 ohm. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_comp_s cn; */
};
typedef union bdk_mio_emm_comp bdk_mio_emm_comp_t;

#define BDK_MIO_EMM_COMP BDK_MIO_EMM_COMP_FUNC()
static inline uint64_t BDK_MIO_EMM_COMP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_COMP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x87e009002040ll;
    __bdk_csr_fatal("MIO_EMM_COMP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_COMP bdk_mio_emm_comp_t
#define bustype_BDK_MIO_EMM_COMP BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_COMP "MIO_EMM_COMP"
#define device_bar_BDK_MIO_EMM_COMP 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_COMP 0
#define arguments_BDK_MIO_EMM_COMP -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_debug
 *
 * eMMC Debug Register
 */
union bdk_mio_emm_debug
{
    uint64_t u;
    struct bdk_mio_emm_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t rdsync_rst            : 1;  /**< [ 21: 21](R/W) eMMC Read Synchronizer logic reset.
                                                                 Must set/cleared only when [EMMC_CLK_DISABLE] is set.
                                                                 For diagnostic use only. */
        uint64_t emmc_clk_disable      : 1;  /**< [ 20: 20](R/W) Disable eMMC clock.
                                                                 Required when MIO_EMM_TIMING[*_IN_TAP] changes. */
        uint64_t dma_sm                : 4;  /**< [ 19: 16](RO) DMA state.
                                                                 For diagnostic use only. */
        uint64_t data_sm               : 4;  /**< [ 15: 12](RO) Data transfer state.
                                                                 For diagnostic use only. */
        uint64_t cmd_sm                : 4;  /**< [ 11:  8](RO) Command state.
                                                                 For diagnostic use only. */
        uint64_t reserved_1_7          : 7;
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force eMMC related conditional clocks to always be on.
                                                                 For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force eMMC related conditional clocks to always be on.
                                                                 For diagnostic use only. */
        uint64_t reserved_1_7          : 7;
        uint64_t cmd_sm                : 4;  /**< [ 11:  8](RO) Command state.
                                                                 For diagnostic use only. */
        uint64_t data_sm               : 4;  /**< [ 15: 12](RO) Data transfer state.
                                                                 For diagnostic use only. */
        uint64_t dma_sm                : 4;  /**< [ 19: 16](RO) DMA state.
                                                                 For diagnostic use only. */
        uint64_t emmc_clk_disable      : 1;  /**< [ 20: 20](R/W) Disable eMMC clock.
                                                                 Required when MIO_EMM_TIMING[*_IN_TAP] changes. */
        uint64_t rdsync_rst            : 1;  /**< [ 21: 21](R/W) eMMC Read Synchronizer logic reset.
                                                                 Must set/cleared only when [EMMC_CLK_DISABLE] is set.
                                                                 For diagnostic use only. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_debug_s cn9; */
    struct bdk_mio_emm_debug_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t dma_sm                : 4;  /**< [ 19: 16](RO) DMA state.
                                                                 For diagnostic use only. */
        uint64_t data_sm               : 4;  /**< [ 15: 12](RO) Data transfer state.
                                                                 For diagnostic use only. */
        uint64_t cmd_sm                : 4;  /**< [ 11:  8](RO) Command state.
                                                                 For diagnostic use only. */
        uint64_t reserved_1_7          : 7;
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force eMMC related conditional clocks to always be on.
                                                                 For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force eMMC related conditional clocks to always be on.
                                                                 For diagnostic use only. */
        uint64_t reserved_1_7          : 7;
        uint64_t cmd_sm                : 4;  /**< [ 11:  8](RO) Command state.
                                                                 For diagnostic use only. */
        uint64_t data_sm               : 4;  /**< [ 15: 12](RO) Data transfer state.
                                                                 For diagnostic use only. */
        uint64_t dma_sm                : 4;  /**< [ 19: 16](RO) DMA state.
                                                                 For diagnostic use only. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } cn96xxp1;
    /* struct bdk_mio_emm_debug_s cn96xxp3; */
    /* struct bdk_mio_emm_debug_s cn98xx; */
    /* struct bdk_mio_emm_debug_cn96xxp1 cnf95xx; */
    /* struct bdk_mio_emm_debug_s loki; */
};
typedef union bdk_mio_emm_debug bdk_mio_emm_debug_t;

#define BDK_MIO_EMM_DEBUG BDK_MIO_EMM_DEBUG_FUNC()
static inline uint64_t BDK_MIO_EMM_DEBUG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DEBUG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e0090020f8ll;
    __bdk_csr_fatal("MIO_EMM_DEBUG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_DEBUG bdk_mio_emm_debug_t
#define bustype_BDK_MIO_EMM_DEBUG BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DEBUG "MIO_EMM_DEBUG"
#define device_bar_BDK_MIO_EMM_DEBUG 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DEBUG 0
#define arguments_BDK_MIO_EMM_DEBUG -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma
 *
 * eMMC External DMA Configuration Register
 */
union bdk_mio_emm_dma
{
    uint64_t u;
    struct bdk_mio_emm_dma_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t extra_args            : 1;  /**< [ 63: 63](R/W) Extra arguments.  Setting this bit enables the use of
                                                                 MIO_EMM_DMA_ARG to provide additional arguments for the
                                                                 DMA operations.  Clearing this bit forces all the listed arguments
                                                                 to be zero.  See MIO_EMM_DMA_ARG for more details. */
        uint64_t skip_busy             : 1;  /**< [ 62: 62](R/W) Controls when DMA is completed.
                                                                 0 = DMA doesn't complete until card has dropped the BUSY signal.
                                                                 1 = Complete DMA after last transfer regardless of the BUSY signal. Status of signal can
                                                                 be read in MIO_EMM_RSP_STS[RSP_BUSYBIT]. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W) Specify the eMMC bus. */
        uint64_t dma_val               : 1;  /**< [ 59: 59](R/W/H) Software writes this bit to a 1 to indicate that hardware should perform the DMA transfer.
                                                                 Hardware clears this bit when the DMA operation completes or is terminated. */
        uint64_t sector                : 1;  /**< [ 58: 58](R/W/H) Specify CARD_ADDR and eMMC are using sector (512 B) addressing. */
        uint64_t dat_null              : 1;  /**< [ 57: 57](R/W) Do not perform any eMMC commands. A DMA read returns all 0s. A DMA write tosses the data.
                                                                 In the case of a failure, this can be used to unwind the DMA engine. */
        uint64_t thres                 : 6;  /**< [ 56: 51](R/W) Number of 8-byte blocks of data that must exist in the DBUF before starting the 512-byte
                                                                 block transfer. Zero indicates to wait for the entire block. */
        uint64_t rel_wr                : 1;  /**< [ 50: 50](R/W) Set the reliable write parameter when performing CMD23 (SET_BLOCK_COUNT) for a multiple block. */
        uint64_t rw                    : 1;  /**< [ 49: 49](R/W) Read/write bit (0 = read, 1 = write). */
        uint64_t multi                 : 1;  /**< [ 48: 48](R/W) Perform operation using a multiple-block command instead of a series of single-block commands. */
        uint64_t block_cnt             : 16; /**< [ 47: 32](R/W/H) Number of blocks to read/write. Hardware decrements the block count after each successful
                                                                 block transfer. */
        uint64_t card_addr             : 32; /**< [ 31:  0](R/W/H) Data address for media \<= 2 GB is a 32-bit byte address, and data address for media \> 2 GB
                                                                 is a 32-bit sector (512 B) address. Hardware advances the card address after each
                                                                 successful block transfer by 512 for byte addressing and by 1 for sector addressing. */
#else /* Word 0 - Little Endian */
        uint64_t card_addr             : 32; /**< [ 31:  0](R/W/H) Data address for media \<= 2 GB is a 32-bit byte address, and data address for media \> 2 GB
                                                                 is a 32-bit sector (512 B) address. Hardware advances the card address after each
                                                                 successful block transfer by 512 for byte addressing and by 1 for sector addressing. */
        uint64_t block_cnt             : 16; /**< [ 47: 32](R/W/H) Number of blocks to read/write. Hardware decrements the block count after each successful
                                                                 block transfer. */
        uint64_t multi                 : 1;  /**< [ 48: 48](R/W) Perform operation using a multiple-block command instead of a series of single-block commands. */
        uint64_t rw                    : 1;  /**< [ 49: 49](R/W) Read/write bit (0 = read, 1 = write). */
        uint64_t rel_wr                : 1;  /**< [ 50: 50](R/W) Set the reliable write parameter when performing CMD23 (SET_BLOCK_COUNT) for a multiple block. */
        uint64_t thres                 : 6;  /**< [ 56: 51](R/W) Number of 8-byte blocks of data that must exist in the DBUF before starting the 512-byte
                                                                 block transfer. Zero indicates to wait for the entire block. */
        uint64_t dat_null              : 1;  /**< [ 57: 57](R/W) Do not perform any eMMC commands. A DMA read returns all 0s. A DMA write tosses the data.
                                                                 In the case of a failure, this can be used to unwind the DMA engine. */
        uint64_t sector                : 1;  /**< [ 58: 58](R/W/H) Specify CARD_ADDR and eMMC are using sector (512 B) addressing. */
        uint64_t dma_val               : 1;  /**< [ 59: 59](R/W/H) Software writes this bit to a 1 to indicate that hardware should perform the DMA transfer.
                                                                 Hardware clears this bit when the DMA operation completes or is terminated. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W) Specify the eMMC bus. */
        uint64_t skip_busy             : 1;  /**< [ 62: 62](R/W) Controls when DMA is completed.
                                                                 0 = DMA doesn't complete until card has dropped the BUSY signal.
                                                                 1 = Complete DMA after last transfer regardless of the BUSY signal. Status of signal can
                                                                 be read in MIO_EMM_RSP_STS[RSP_BUSYBIT]. */
        uint64_t extra_args            : 1;  /**< [ 63: 63](R/W) Extra arguments.  Setting this bit enables the use of
                                                                 MIO_EMM_DMA_ARG to provide additional arguments for the
                                                                 DMA operations.  Clearing this bit forces all the listed arguments
                                                                 to be zero.  See MIO_EMM_DMA_ARG for more details. */
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_dma_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t skip_busy             : 1;  /**< [ 62: 62](R/W) Controls when DMA is completed.
                                                                 0 = DMA doesn't complete until card has dropped the BUSY signal.
                                                                 1 = Complete DMA after last transfer regardless of the BUSY signal. Status of signal can
                                                                 be read in MIO_EMM_RSP_STS[RSP_BUSYBIT]. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W) Specify the eMMC bus. */
        uint64_t dma_val               : 1;  /**< [ 59: 59](R/W/H) Software writes this bit to a 1 to indicate that hardware should perform the DMA transfer.
                                                                 Hardware clears this bit when the DMA operation completes or is terminated. */
        uint64_t sector                : 1;  /**< [ 58: 58](R/W/H) Specify CARD_ADDR and eMMC are using sector (512 B) addressing. */
        uint64_t dat_null              : 1;  /**< [ 57: 57](R/W) Do not perform any eMMC commands. A DMA read returns all 0s. A DMA write tosses the data.
                                                                 In the case of a failure, this can be used to unwind the DMA engine. */
        uint64_t thres                 : 6;  /**< [ 56: 51](R/W) Number of 8-byte blocks of data that must exist in the DBUF before starting the 512-byte
                                                                 block transfer. Zero indicates to wait for the entire block. */
        uint64_t rel_wr                : 1;  /**< [ 50: 50](R/W) Set the reliable write parameter when performing CMD23 (SET_BLOCK_COUNT) for a multiple block. */
        uint64_t rw                    : 1;  /**< [ 49: 49](R/W) Read/write bit (0 = read, 1 = write). */
        uint64_t multi                 : 1;  /**< [ 48: 48](R/W) Perform operation using a multiple-block command instead of a series of single-block commands. */
        uint64_t block_cnt             : 16; /**< [ 47: 32](R/W/H) Number of blocks to read/write. Hardware decrements the block count after each successful
                                                                 block transfer. */
        uint64_t card_addr             : 32; /**< [ 31:  0](R/W/H) Data address for media \<= 2 GB is a 32-bit byte address, and data address for media \> 2 GB
                                                                 is a 32-bit sector (512 B) address. Hardware advances the card address after each
                                                                 successful block transfer by 512 for byte addressing and by 1 for sector addressing. */
#else /* Word 0 - Little Endian */
        uint64_t card_addr             : 32; /**< [ 31:  0](R/W/H) Data address for media \<= 2 GB is a 32-bit byte address, and data address for media \> 2 GB
                                                                 is a 32-bit sector (512 B) address. Hardware advances the card address after each
                                                                 successful block transfer by 512 for byte addressing and by 1 for sector addressing. */
        uint64_t block_cnt             : 16; /**< [ 47: 32](R/W/H) Number of blocks to read/write. Hardware decrements the block count after each successful
                                                                 block transfer. */
        uint64_t multi                 : 1;  /**< [ 48: 48](R/W) Perform operation using a multiple-block command instead of a series of single-block commands. */
        uint64_t rw                    : 1;  /**< [ 49: 49](R/W) Read/write bit (0 = read, 1 = write). */
        uint64_t rel_wr                : 1;  /**< [ 50: 50](R/W) Set the reliable write parameter when performing CMD23 (SET_BLOCK_COUNT) for a multiple block. */
        uint64_t thres                 : 6;  /**< [ 56: 51](R/W) Number of 8-byte blocks of data that must exist in the DBUF before starting the 512-byte
                                                                 block transfer. Zero indicates to wait for the entire block. */
        uint64_t dat_null              : 1;  /**< [ 57: 57](R/W) Do not perform any eMMC commands. A DMA read returns all 0s. A DMA write tosses the data.
                                                                 In the case of a failure, this can be used to unwind the DMA engine. */
        uint64_t sector                : 1;  /**< [ 58: 58](R/W/H) Specify CARD_ADDR and eMMC are using sector (512 B) addressing. */
        uint64_t dma_val               : 1;  /**< [ 59: 59](R/W/H) Software writes this bit to a 1 to indicate that hardware should perform the DMA transfer.
                                                                 Hardware clears this bit when the DMA operation completes or is terminated. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W) Specify the eMMC bus. */
        uint64_t skip_busy             : 1;  /**< [ 62: 62](R/W) Controls when DMA is completed.
                                                                 0 = DMA doesn't complete until card has dropped the BUSY signal.
                                                                 1 = Complete DMA after last transfer regardless of the BUSY signal. Status of signal can
                                                                 be read in MIO_EMM_RSP_STS[RSP_BUSYBIT]. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_mio_emm_dma_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t extra_args            : 1;  /**< [ 63: 63](R/W) Extra arguments.  Setting this bit enables the use of
                                                                 MIO_EMM_DMA_ARG to provide additional arguments for the
                                                                 DMA operations.  Clearing this bit forces all the listed arguments
                                                                 to be zero.  See MIO_EMM_DMA_ARG for more details. */
        uint64_t skip_busy             : 1;  /**< [ 62: 62](R/W) Controls when DMA is completed.
                                                                 0 = DMA doesn't complete until card has dropped the BUSY signal.
                                                                 1 = Complete DMA after last transfer regardless of the BUSY signal. Status of signal can
                                                                 be read in MIO_EMM_RSP_STS[RSP_BUSYBIT]. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W) Specify the eMMC bus. */
        uint64_t dma_val               : 1;  /**< [ 59: 59](R/W/H) Software writes this bit to a 1 to indicate that hardware should perform the DMA transfer.
                                                                 Hardware clears this bit when the DMA operation completes or is terminated. */
        uint64_t sector                : 1;  /**< [ 58: 58](R/W/H) Specify CARD_ADDR and eMMC are using sector (512 B) addressing. */
        uint64_t dat_null              : 1;  /**< [ 57: 57](R/W) Do not perform any eMMC commands. A DMA read returns all 0s. A DMA write tosses the data.
                                                                 In the case of a failure, this can be used to unwind the DMA engine. */
        uint64_t thres                 : 6;  /**< [ 56: 51](R/W) Number of 8-byte blocks of data that must exist in the DBUF before starting the 512-byte
                                                                 block transfer. Zero indicates to wait for the entire block. */
        uint64_t reserved_50           : 1;
        uint64_t rw                    : 1;  /**< [ 49: 49](R/W) Read/write bit (0 = read, 1 = write). */
        uint64_t multi                 : 1;  /**< [ 48: 48](R/W) Perform operation using a multiple-block command instead of a series of single-block commands. */
        uint64_t block_cnt             : 16; /**< [ 47: 32](R/W/H) Number of blocks to read/write. Hardware decrements the block count after each successful
                                                                 block transfer. */
        uint64_t card_addr             : 32; /**< [ 31:  0](R/W/H) Data address for media \<= 2 GB is a 32-bit byte address, and data address for media \> 2 GB
                                                                 is a 32-bit sector (512 B) address. Hardware advances the card address after each
                                                                 successful block transfer by 512 for byte addressing and by 1 for sector addressing. */
#else /* Word 0 - Little Endian */
        uint64_t card_addr             : 32; /**< [ 31:  0](R/W/H) Data address for media \<= 2 GB is a 32-bit byte address, and data address for media \> 2 GB
                                                                 is a 32-bit sector (512 B) address. Hardware advances the card address after each
                                                                 successful block transfer by 512 for byte addressing and by 1 for sector addressing. */
        uint64_t block_cnt             : 16; /**< [ 47: 32](R/W/H) Number of blocks to read/write. Hardware decrements the block count after each successful
                                                                 block transfer. */
        uint64_t multi                 : 1;  /**< [ 48: 48](R/W) Perform operation using a multiple-block command instead of a series of single-block commands. */
        uint64_t rw                    : 1;  /**< [ 49: 49](R/W) Read/write bit (0 = read, 1 = write). */
        uint64_t reserved_50           : 1;
        uint64_t thres                 : 6;  /**< [ 56: 51](R/W) Number of 8-byte blocks of data that must exist in the DBUF before starting the 512-byte
                                                                 block transfer. Zero indicates to wait for the entire block. */
        uint64_t dat_null              : 1;  /**< [ 57: 57](R/W) Do not perform any eMMC commands. A DMA read returns all 0s. A DMA write tosses the data.
                                                                 In the case of a failure, this can be used to unwind the DMA engine. */
        uint64_t sector                : 1;  /**< [ 58: 58](R/W/H) Specify CARD_ADDR and eMMC are using sector (512 B) addressing. */
        uint64_t dma_val               : 1;  /**< [ 59: 59](R/W/H) Software writes this bit to a 1 to indicate that hardware should perform the DMA transfer.
                                                                 Hardware clears this bit when the DMA operation completes or is terminated. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W) Specify the eMMC bus. */
        uint64_t skip_busy             : 1;  /**< [ 62: 62](R/W) Controls when DMA is completed.
                                                                 0 = DMA doesn't complete until card has dropped the BUSY signal.
                                                                 1 = Complete DMA after last transfer regardless of the BUSY signal. Status of signal can
                                                                 be read in MIO_EMM_RSP_STS[RSP_BUSYBIT]. */
        uint64_t extra_args            : 1;  /**< [ 63: 63](R/W) Extra arguments.  Setting this bit enables the use of
                                                                 MIO_EMM_DMA_ARG to provide additional arguments for the
                                                                 DMA operations.  Clearing this bit forces all the listed arguments
                                                                 to be zero.  See MIO_EMM_DMA_ARG for more details. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_mio_emm_dma bdk_mio_emm_dma_t;

#define BDK_MIO_EMM_DMA BDK_MIO_EMM_DMA_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_FUNC(void)
{
    return 0x87e009002050ll;
}

#define typedef_BDK_MIO_EMM_DMA bdk_mio_emm_dma_t
#define bustype_BDK_MIO_EMM_DMA BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA "MIO_EMM_DMA"
#define device_bar_BDK_MIO_EMM_DMA 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA 0
#define arguments_BDK_MIO_EMM_DMA -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_adr
 *
 * eMMC DMA Address Register
 * This register sets the address for eMMC/SD flash transfers to/from memory. Sixty-four-bit
 * operations must be used to access this register. This register is updated by the DMA
 * hardware and can be reloaded by the values placed in the MIO_EMM_DMA_FIFO_ADR.
 */
union bdk_mio_emm_dma_adr
{
    uint64_t u;
    struct bdk_mio_emm_dma_adr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t adr                   : 53; /**< [ 52:  0](R/W/H) DMA engine IOVA. Must be 64-bit aligned. */
#else /* Word 0 - Little Endian */
        uint64_t adr                   : 53; /**< [ 52:  0](R/W/H) DMA engine IOVA. Must be 64-bit aligned. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_dma_adr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t adr                   : 49; /**< [ 48:  0](R/W/H) DMA engine IOVA. Must be 64-bit aligned. */
#else /* Word 0 - Little Endian */
        uint64_t adr                   : 49; /**< [ 48:  0](R/W/H) DMA engine IOVA. Must be 64-bit aligned. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_emm_dma_adr_s cn9; */
};
typedef union bdk_mio_emm_dma_adr bdk_mio_emm_dma_adr_t;

#define BDK_MIO_EMM_DMA_ADR BDK_MIO_EMM_DMA_ADR_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_ADR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_ADR_FUNC(void)
{
    return 0x87e009000188ll;
}

#define typedef_BDK_MIO_EMM_DMA_ADR bdk_mio_emm_dma_adr_t
#define bustype_BDK_MIO_EMM_DMA_ADR BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_ADR "MIO_EMM_DMA_ADR"
#define device_bar_BDK_MIO_EMM_DMA_ADR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_ADR 0
#define arguments_BDK_MIO_EMM_DMA_ADR -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_arg
 *
 * eMMC External DMA Extra Arguments Register
 */
union bdk_mio_emm_dma_arg
{
    uint64_t u;
    struct bdk_mio_emm_dma_arg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t alt_cmd_arg           : 32; /**< [ 63: 32](R/W) Alternate command arguments. When nonzero this field is used at the 24-bit
                                                                 argument for the DMA command instead of the address. This feature is typically
                                                                 used in conjunction with [ALT_CMD]. */
        uint64_t reserved_23_31        : 9;
        uint64_t skip_blk_cmd          : 1;  /**< [ 22: 22](R/W) When set DMA will ignore issuing CMD23 (Set Block Count) command and instead
                                                                 issue a stop command when the number of blocks have expired. This flag would
                                                                 typically be set with SD devices and with an alternate command that does not use
                                                                 CMD23 to set the number of blocks.  This field is ignored if MIO_EMM_DMA[MULTI]
                                                                 is clear since that feature already skips CMD23 and issues multiple commands. */
        uint64_t alt_cmd               : 6;  /**< [ 21: 16](R/W) Alternate command.  When non-zero this fields supplies the command used for the DMA
                                                                 Transfer.  Typically this would be CMD18 in the case of Corresponds to bit 31 of
                                                                 CMD23 (SET_BLOCK_COUNT)
                                                                 for a multiple block. */
        uint64_t rel_wr                : 1;  /**< [ 15: 15](R/W) Reliable write.  Corresponds to bit 31 of CMD23 (SET_BLOCK_COUNT)
                                                                 for a multiple block. */
        uint64_t pack_cmd              : 1;  /**< [ 14: 14](R/W) Packed command enable.
                                                                 Corresponds to bit 30 of CMD23 (SET_BLOCK_COUNT).
                                                                 0 = Normal DMA command.
                                                                 1 = Sets the packed command argument (bit 30) in the
                                                                 SET_BLOCK_COUNT (CMD23) used to start the DMA.  The
                                                                 MULTI field should also be set for both read and write
                                                                 transfers.

                                                                 In the case of a write using packed commands, the DMA
                                                                 header occupies the first block to be transfered and
                                                                 should be added to the BLOCK_COUNT of all the packed
                                                                 write transfers.

                                                                 In the case of a read using packed commands, a write
                                                                 DMA is performed with this bit set and the BLOCK_COUNT is set
                                                                 to a single block to transfer the DMA header.  Then a
                                                                 non-packed read DMA with a BLOCK_COUNT of all the packed
                                                                 read transfers should be executed. */
        uint64_t tag_req               : 1;  /**< [ 13: 13](R/W) Tag request.
                                                                 Corresponds to bit 29 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t context_id            : 4;  /**< [ 12:  9](R/W) Context ID.
                                                                 Corresponds to bits 28:25 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t force_pgm             : 1;  /**< [  8:  8](R/W) Forced programming.
                                                                 Corresponds to bit 24 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t cmd23_args            : 8;  /**< [  7:  0](R/W) CMD23 arguments 23:16.
                                                                 Corresponds to bits 23:16 of CMD23 (SET_BLOCK_COUNT). */
#else /* Word 0 - Little Endian */
        uint64_t cmd23_args            : 8;  /**< [  7:  0](R/W) CMD23 arguments 23:16.
                                                                 Corresponds to bits 23:16 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t force_pgm             : 1;  /**< [  8:  8](R/W) Forced programming.
                                                                 Corresponds to bit 24 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t context_id            : 4;  /**< [ 12:  9](R/W) Context ID.
                                                                 Corresponds to bits 28:25 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t tag_req               : 1;  /**< [ 13: 13](R/W) Tag request.
                                                                 Corresponds to bit 29 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t pack_cmd              : 1;  /**< [ 14: 14](R/W) Packed command enable.
                                                                 Corresponds to bit 30 of CMD23 (SET_BLOCK_COUNT).
                                                                 0 = Normal DMA command.
                                                                 1 = Sets the packed command argument (bit 30) in the
                                                                 SET_BLOCK_COUNT (CMD23) used to start the DMA.  The
                                                                 MULTI field should also be set for both read and write
                                                                 transfers.

                                                                 In the case of a write using packed commands, the DMA
                                                                 header occupies the first block to be transfered and
                                                                 should be added to the BLOCK_COUNT of all the packed
                                                                 write transfers.

                                                                 In the case of a read using packed commands, a write
                                                                 DMA is performed with this bit set and the BLOCK_COUNT is set
                                                                 to a single block to transfer the DMA header.  Then a
                                                                 non-packed read DMA with a BLOCK_COUNT of all the packed
                                                                 read transfers should be executed. */
        uint64_t rel_wr                : 1;  /**< [ 15: 15](R/W) Reliable write.  Corresponds to bit 31 of CMD23 (SET_BLOCK_COUNT)
                                                                 for a multiple block. */
        uint64_t alt_cmd               : 6;  /**< [ 21: 16](R/W) Alternate command.  When non-zero this fields supplies the command used for the DMA
                                                                 Transfer.  Typically this would be CMD18 in the case of Corresponds to bit 31 of
                                                                 CMD23 (SET_BLOCK_COUNT)
                                                                 for a multiple block. */
        uint64_t skip_blk_cmd          : 1;  /**< [ 22: 22](R/W) When set DMA will ignore issuing CMD23 (Set Block Count) command and instead
                                                                 issue a stop command when the number of blocks have expired. This flag would
                                                                 typically be set with SD devices and with an alternate command that does not use
                                                                 CMD23 to set the number of blocks.  This field is ignored if MIO_EMM_DMA[MULTI]
                                                                 is clear since that feature already skips CMD23 and issues multiple commands. */
        uint64_t reserved_23_31        : 9;
        uint64_t alt_cmd_arg           : 32; /**< [ 63: 32](R/W) Alternate command arguments. When nonzero this field is used at the 24-bit
                                                                 argument for the DMA command instead of the address. This feature is typically
                                                                 used in conjunction with [ALT_CMD]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_dma_arg_s cn9; */
    /* struct bdk_mio_emm_dma_arg_s cn96xxp1; */
    struct bdk_mio_emm_dma_arg_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t alt_cmd_arg           : 32; /**< [ 63: 32](R/W) Alternate command arguments. When nonzero this field is used at the 24-bit
                                                                 argument for the DMA command instead of the address. This feature is typically
                                                                 used in conjunction with [ALT_CMD]. */
        uint64_t reserved_23_31        : 9;
        uint64_t skip_blk_cmd          : 1;  /**< [ 22: 22](R/W) When set DMA will ignore issuing CMD23 (Set Block Count) command and instead
                                                                 issue a stop command when the number of blocks have expired. This flag would
                                                                 typically be set with SD devices and with an alternate command that does not use
                                                                 CMD23 to set the number of blocks.  This field is ignored if MIO_EMM_DMA[MULTI]
                                                                 is clear since that feature already skips CMD23 and issues multiple commands. */
        uint64_t alt_cmd               : 6;  /**< [ 21: 16](R/W) Alternate command.  When non-zero this fields supplies the command used for the DMA
                                                                 Transfer.  Typically this would be CMD17/CMD18 in the case of a read operation or a
                                                                 CMD24/CMD25 in the case of a write operation. */
        uint64_t rel_wr                : 1;  /**< [ 15: 15](R/W) Reliable write.  Corresponds to bit 31 of CMD23 (SET_BLOCK_COUNT)
                                                                 for a multiple block. */
        uint64_t pack_cmd              : 1;  /**< [ 14: 14](R/W) Packed command enable.
                                                                 Corresponds to bit 30 of CMD23 (SET_BLOCK_COUNT).
                                                                 0 = Normal DMA command.
                                                                 1 = Sets the packed command argument (bit 30) in the
                                                                 SET_BLOCK_COUNT (CMD23) used to start the DMA.  The
                                                                 MULTI field should also be set for both read and write
                                                                 transfers.

                                                                 In the case of a write using packed commands, the DMA
                                                                 header occupies the first block to be transfered and
                                                                 should be added to the BLOCK_COUNT of all the packed
                                                                 write transfers.

                                                                 In the case of a read using packed commands, a write
                                                                 DMA is performed with this bit set and the BLOCK_COUNT is set
                                                                 to a single block to transfer the DMA header.  Then a
                                                                 non-packed read DMA with a BLOCK_COUNT of all the packed
                                                                 read transfers should be executed. */
        uint64_t tag_req               : 1;  /**< [ 13: 13](R/W) Tag request.
                                                                 Corresponds to bit 29 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t context_id            : 4;  /**< [ 12:  9](R/W) Context ID.
                                                                 Corresponds to bits 28:25 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t force_pgm             : 1;  /**< [  8:  8](R/W) Forced programming.
                                                                 Corresponds to bit 24 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t cmd23_args            : 8;  /**< [  7:  0](R/W) CMD23 arguments 23:16.
                                                                 Corresponds to bits 23:16 of CMD23 (SET_BLOCK_COUNT). */
#else /* Word 0 - Little Endian */
        uint64_t cmd23_args            : 8;  /**< [  7:  0](R/W) CMD23 arguments 23:16.
                                                                 Corresponds to bits 23:16 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t force_pgm             : 1;  /**< [  8:  8](R/W) Forced programming.
                                                                 Corresponds to bit 24 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t context_id            : 4;  /**< [ 12:  9](R/W) Context ID.
                                                                 Corresponds to bits 28:25 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t tag_req               : 1;  /**< [ 13: 13](R/W) Tag request.
                                                                 Corresponds to bit 29 of CMD23 (SET_BLOCK_COUNT). */
        uint64_t pack_cmd              : 1;  /**< [ 14: 14](R/W) Packed command enable.
                                                                 Corresponds to bit 30 of CMD23 (SET_BLOCK_COUNT).
                                                                 0 = Normal DMA command.
                                                                 1 = Sets the packed command argument (bit 30) in the
                                                                 SET_BLOCK_COUNT (CMD23) used to start the DMA.  The
                                                                 MULTI field should also be set for both read and write
                                                                 transfers.

                                                                 In the case of a write using packed commands, the DMA
                                                                 header occupies the first block to be transfered and
                                                                 should be added to the BLOCK_COUNT of all the packed
                                                                 write transfers.

                                                                 In the case of a read using packed commands, a write
                                                                 DMA is performed with this bit set and the BLOCK_COUNT is set
                                                                 to a single block to transfer the DMA header.  Then a
                                                                 non-packed read DMA with a BLOCK_COUNT of all the packed
                                                                 read transfers should be executed. */
        uint64_t rel_wr                : 1;  /**< [ 15: 15](R/W) Reliable write.  Corresponds to bit 31 of CMD23 (SET_BLOCK_COUNT)
                                                                 for a multiple block. */
        uint64_t alt_cmd               : 6;  /**< [ 21: 16](R/W) Alternate command.  When non-zero this fields supplies the command used for the DMA
                                                                 Transfer.  Typically this would be CMD17/CMD18 in the case of a read operation or a
                                                                 CMD24/CMD25 in the case of a write operation. */
        uint64_t skip_blk_cmd          : 1;  /**< [ 22: 22](R/W) When set DMA will ignore issuing CMD23 (Set Block Count) command and instead
                                                                 issue a stop command when the number of blocks have expired. This flag would
                                                                 typically be set with SD devices and with an alternate command that does not use
                                                                 CMD23 to set the number of blocks.  This field is ignored if MIO_EMM_DMA[MULTI]
                                                                 is clear since that feature already skips CMD23 and issues multiple commands. */
        uint64_t reserved_23_31        : 9;
        uint64_t alt_cmd_arg           : 32; /**< [ 63: 32](R/W) Alternate command arguments. When nonzero this field is used at the 24-bit
                                                                 argument for the DMA command instead of the address. This feature is typically
                                                                 used in conjunction with [ALT_CMD]. */
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mio_emm_dma_arg_cn96xxp3 cn98xx; */
    /* struct bdk_mio_emm_dma_arg_s cnf95xx; */
    /* struct bdk_mio_emm_dma_arg_cn96xxp3 loki; */
};
typedef union bdk_mio_emm_dma_arg bdk_mio_emm_dma_arg_t;

#define BDK_MIO_EMM_DMA_ARG BDK_MIO_EMM_DMA_ARG_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_ARG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_ARG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e009002090ll;
    __bdk_csr_fatal("MIO_EMM_DMA_ARG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_DMA_ARG bdk_mio_emm_dma_arg_t
#define bustype_BDK_MIO_EMM_DMA_ARG BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_ARG "MIO_EMM_DMA_ARG"
#define device_bar_BDK_MIO_EMM_DMA_ARG 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_ARG 0
#define arguments_BDK_MIO_EMM_DMA_ARG -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_cfg
 *
 * eMMC DMA Configuration Register
 * This register controls the internal DMA engine used with the eMMC/SD flash controller. Sixty-
 * four-bit operations must be used to access this register. This register is updated by the
 * hardware DMA engine and can also be reloaded by writes to the MIO_EMM_DMA_FIFO_CMD register.
 */
union bdk_mio_emm_dma_cfg
{
    uint64_t u;
    struct bdk_mio_emm_dma_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t en                    : 1;  /**< [ 63: 63](R/W/H) DMA engine enable. */
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W/H) DMA engine R/W bit: 0 = read, 1 = write. */
        uint64_t clr                   : 1;  /**< [ 61: 61](R/W/H) DMA engine abort. When set to 1, DMA is aborted and [EN] is cleared on completion. */
        uint64_t reserved_60           : 1;
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W/H) DMA engine 32-bit swap. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W/H) DMA engine enable 16-bit swap. */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W/H) DMA engine enable 8-bit swap. */
        uint64_t endian                : 1;  /**< [ 56: 56](R/W/H) DMA engine endian mode: 0 = big-endian, 1 = little-endian. */
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine size. Specified in the number of 64-bit transfers (encoded in -1 notation). For
                                                                 example, to transfer 512 bytes, SIZE = 64 - 1 = 63. */
        uint64_t reserved_0_35         : 36;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_35         : 36;
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine size. Specified in the number of 64-bit transfers (encoded in -1 notation). For
                                                                 example, to transfer 512 bytes, SIZE = 64 - 1 = 63. */
        uint64_t endian                : 1;  /**< [ 56: 56](R/W/H) DMA engine endian mode: 0 = big-endian, 1 = little-endian. */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W/H) DMA engine enable 8-bit swap. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W/H) DMA engine enable 16-bit swap. */
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W/H) DMA engine 32-bit swap. */
        uint64_t reserved_60           : 1;
        uint64_t clr                   : 1;  /**< [ 61: 61](R/W/H) DMA engine abort. When set to 1, DMA is aborted and [EN] is cleared on completion. */
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W/H) DMA engine R/W bit: 0 = read, 1 = write. */
        uint64_t en                    : 1;  /**< [ 63: 63](R/W/H) DMA engine enable. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_dma_cfg_s cn; */
};
typedef union bdk_mio_emm_dma_cfg bdk_mio_emm_dma_cfg_t;

#define BDK_MIO_EMM_DMA_CFG BDK_MIO_EMM_DMA_CFG_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_CFG_FUNC(void)
{
    return 0x87e009000180ll;
}

#define typedef_BDK_MIO_EMM_DMA_CFG bdk_mio_emm_dma_cfg_t
#define bustype_BDK_MIO_EMM_DMA_CFG BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_CFG "MIO_EMM_DMA_CFG"
#define device_bar_BDK_MIO_EMM_DMA_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_CFG 0
#define arguments_BDK_MIO_EMM_DMA_CFG -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_fifo_adr
 *
 * eMMC Internal DMA FIFO Address Register
 * This register specifies the internal address that is loaded into the eMMC internal DMA FIFO.
 * The FIFO is used to queue up operations for the MIO_EMM_DMA_CFG/MIO_EMM_DMA_ADR when the DMA
 * completes successfully.
 */
union bdk_mio_emm_dma_fifo_adr
{
    uint64_t u;
    struct bdk_mio_emm_dma_fifo_adr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t adr                   : 50; /**< [ 52:  3](R/W) DMA engine IOVA. Must be 64-bit aligned. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t adr                   : 50; /**< [ 52:  3](R/W) DMA engine IOVA. Must be 64-bit aligned. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_dma_fifo_adr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t adr                   : 46; /**< [ 48:  3](R/W) DMA engine IOVA. Must be 64-bit aligned. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t adr                   : 46; /**< [ 48:  3](R/W) DMA engine IOVA. Must be 64-bit aligned. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_emm_dma_fifo_adr_s cn9; */
};
typedef union bdk_mio_emm_dma_fifo_adr bdk_mio_emm_dma_fifo_adr_t;

#define BDK_MIO_EMM_DMA_FIFO_ADR BDK_MIO_EMM_DMA_FIFO_ADR_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_FIFO_ADR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_FIFO_ADR_FUNC(void)
{
    return 0x87e009000170ll;
}

#define typedef_BDK_MIO_EMM_DMA_FIFO_ADR bdk_mio_emm_dma_fifo_adr_t
#define bustype_BDK_MIO_EMM_DMA_FIFO_ADR BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_FIFO_ADR "MIO_EMM_DMA_FIFO_ADR"
#define device_bar_BDK_MIO_EMM_DMA_FIFO_ADR 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_FIFO_ADR 0
#define arguments_BDK_MIO_EMM_DMA_FIFO_ADR -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_fifo_cfg
 *
 * eMMC Internal DMA FIFO Configuration Register
 * This register controls DMA FIFO operations.
 */
union bdk_mio_emm_dma_fifo_cfg
{
    uint64_t u;
    struct bdk_mio_emm_dma_fifo_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_17_63        : 47;
        uint64_t clr                   : 1;  /**< [ 16: 16](R/W) DMA FIFO clear. When set, erases all commands in the DMA FIFO. Must be zero for normal operation. */
        uint64_t reserved_13_15        : 3;
        uint64_t int_lvl               : 5;  /**< [ 12:  8](R/W) Interrupt threshold indicating the number of entries remaining in the
                                                                 DMA FIFO.  An interrupt occurs if the FIFO is read at the level specified.
                                                                 A value of 0 disables the interrupt.  A value of 17 or greater causes an
                                                                 interrupt only if the FIFO is overflowed.
                                                                 See MIO_EMM_DMA_INT[FIFO]. */
        uint64_t reserved_5_7          : 3;
        uint64_t count                 : 5;  /**< [  4:  0](RO/H) Number of entries in the DMA FIFO. This count is incremented by writes to
                                                                 MIO_EMM_DMA_FIFO_CMD and decremented each time the internal DMA engine completes
                                                                 the previous command successfully.

                                                                 Up to 16 entries can be placed in the FIFO. Entries written to a full FIFO will
                                                                 potentially corrupt existing entries.  Care must be taken by software to ensure
                                                                 that this condition does not occur. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 5;  /**< [  4:  0](RO/H) Number of entries in the DMA FIFO. This count is incremented by writes to
                                                                 MIO_EMM_DMA_FIFO_CMD and decremented each time the internal DMA engine completes
                                                                 the previous command successfully.

                                                                 Up to 16 entries can be placed in the FIFO. Entries written to a full FIFO will
                                                                 potentially corrupt existing entries.  Care must be taken by software to ensure
                                                                 that this condition does not occur. */
        uint64_t reserved_5_7          : 3;
        uint64_t int_lvl               : 5;  /**< [ 12:  8](R/W) Interrupt threshold indicating the number of entries remaining in the
                                                                 DMA FIFO.  An interrupt occurs if the FIFO is read at the level specified.
                                                                 A value of 0 disables the interrupt.  A value of 17 or greater causes an
                                                                 interrupt only if the FIFO is overflowed.
                                                                 See MIO_EMM_DMA_INT[FIFO]. */
        uint64_t reserved_13_15        : 3;
        uint64_t clr                   : 1;  /**< [ 16: 16](R/W) DMA FIFO clear. When set, erases all commands in the DMA FIFO. Must be zero for normal operation. */
        uint64_t reserved_17_63        : 47;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_dma_fifo_cfg_s cn; */
};
typedef union bdk_mio_emm_dma_fifo_cfg bdk_mio_emm_dma_fifo_cfg_t;

#define BDK_MIO_EMM_DMA_FIFO_CFG BDK_MIO_EMM_DMA_FIFO_CFG_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_FIFO_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_FIFO_CFG_FUNC(void)
{
    return 0x87e009000160ll;
}

#define typedef_BDK_MIO_EMM_DMA_FIFO_CFG bdk_mio_emm_dma_fifo_cfg_t
#define bustype_BDK_MIO_EMM_DMA_FIFO_CFG BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_FIFO_CFG "MIO_EMM_DMA_FIFO_CFG"
#define device_bar_BDK_MIO_EMM_DMA_FIFO_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_FIFO_CFG 0
#define arguments_BDK_MIO_EMM_DMA_FIFO_CFG -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_fifo_cmd
 *
 * eMMC Internal DMA FIFO Command Register
 * This register specifies a command that is loaded into the eMMC internal DMA FIFO.  The FIFO is
 * used to queue up operations for the MIO_EMM_DMA_CFG/MIO_EMM_DMA_ADR when the DMA completes
 * successfully. Writes to this register store both the MIO_EMM_DMA_FIFO_CMD and the
 * MIO_EMM_DMA_FIFO_ADR contents into the FIFO and increment the MIO_EMM_DMA_FIFO_CFG[COUNT]
 * field.
 *
 * Note: This register has a similar format to MIO_EMM_DMA_CFG with the exception
 * that the EN and CLR fields are absent. These are supported in MIO_EMM_DMA_FIFO_CFG.
 */
union bdk_mio_emm_dma_fifo_cmd
{
    uint64_t u;
    struct bdk_mio_emm_dma_fifo_cmd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W) DMA engine R/W bit: 0 = read, 1 = write. */
        uint64_t reserved_61           : 1;
        uint64_t intdis                : 1;  /**< [ 60: 60](R/W) DMA command interrupt disable. When set, the DMA command being submitted will
                                                                 not generate a MIO_EMM_DMA_INT[DONE] interrupt when it completes. When cleared
                                                                 the command will generate the interrupt.

                                                                 For example, this field can be set for all the DMA commands submitted to the DMA
                                                                 FIFO in the case of a write to the eMMC device because the MIO_EMM_INT[DMA_DONE]
                                                                 interrupt would signify the end of the operation. It could be cleared on the last
                                                                 DMA command being submitted to the DMA FIFO and the MIO_EMM_DMA_INT[DONE] would
                                                                 occur when the read data from the eMMC device was available in local memory. */
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W) DMA engine 32-bit swap enable.  See [ENDIAN]. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W) DMA engine 16-bit swap enable.  See [ENDIAN]. */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W) DMA engine 8-bit swap enable.  See [ENDIAN]. */
        uint64_t endian                : 1;  /**< [ 56: 56](R/W) DMA engine endian mode: 0 = little-endian, 1 = big-endian.
                                                                 Using 0..7 to identify bytes.
                                                                 \<pre\>
                                                                 [SWAP32] [SWAP16] [SWAP8] [ENDIAN]  Result
                                                                    0        0        0      0       7 6 5 4 3 2 1 0
                                                                    0        0        1      0       6 7 4 5 2 3 0 1
                                                                    0        1        0      0       5 4 7 6 1 0 3 2
                                                                    1        0        0      0       3 2 1 0 7 6 5 4
                                                                    0        0        0      1       0 1 2 3 4 5 6 7
                                                                    0        0        1      1       1 0 3 2 5 4 7 6
                                                                    0        1        0      1       2 3 0 1 6 7 4 5
                                                                    1        0        0      1       4 5 6 7 0 1 2 3
                                                                 \</pre\> */
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine size. Specified in the number of 64-bit transfers (encoded in -1 notation). For
                                                                 example, to transfer 512 bytes, SIZE = 64 - 1 = 63. */
        uint64_t reserved_0_35         : 36;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_35         : 36;
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine size. Specified in the number of 64-bit transfers (encoded in -1 notation). For
                                                                 example, to transfer 512 bytes, SIZE = 64 - 1 = 63. */
        uint64_t endian                : 1;  /**< [ 56: 56](R/W) DMA engine endian mode: 0 = little-endian, 1 = big-endian.
                                                                 Using 0..7 to identify bytes.
                                                                 \<pre\>
                                                                 [SWAP32] [SWAP16] [SWAP8] [ENDIAN]  Result
                                                                    0        0        0      0       7 6 5 4 3 2 1 0
                                                                    0        0        1      0       6 7 4 5 2 3 0 1
                                                                    0        1        0      0       5 4 7 6 1 0 3 2
                                                                    1        0        0      0       3 2 1 0 7 6 5 4
                                                                    0        0        0      1       0 1 2 3 4 5 6 7
                                                                    0        0        1      1       1 0 3 2 5 4 7 6
                                                                    0        1        0      1       2 3 0 1 6 7 4 5
                                                                    1        0        0      1       4 5 6 7 0 1 2 3
                                                                 \</pre\> */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W) DMA engine 8-bit swap enable.  See [ENDIAN]. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W) DMA engine 16-bit swap enable.  See [ENDIAN]. */
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W) DMA engine 32-bit swap enable.  See [ENDIAN]. */
        uint64_t intdis                : 1;  /**< [ 60: 60](R/W) DMA command interrupt disable. When set, the DMA command being submitted will
                                                                 not generate a MIO_EMM_DMA_INT[DONE] interrupt when it completes. When cleared
                                                                 the command will generate the interrupt.

                                                                 For example, this field can be set for all the DMA commands submitted to the DMA
                                                                 FIFO in the case of a write to the eMMC device because the MIO_EMM_INT[DMA_DONE]
                                                                 interrupt would signify the end of the operation. It could be cleared on the last
                                                                 DMA command being submitted to the DMA FIFO and the MIO_EMM_DMA_INT[DONE] would
                                                                 occur when the read data from the eMMC device was available in local memory. */
        uint64_t reserved_61           : 1;
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W) DMA engine R/W bit: 0 = read, 1 = write. */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_dma_fifo_cmd_s cn; */
};
typedef union bdk_mio_emm_dma_fifo_cmd bdk_mio_emm_dma_fifo_cmd_t;

#define BDK_MIO_EMM_DMA_FIFO_CMD BDK_MIO_EMM_DMA_FIFO_CMD_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_FIFO_CMD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_FIFO_CMD_FUNC(void)
{
    return 0x87e009000178ll;
}

#define typedef_BDK_MIO_EMM_DMA_FIFO_CMD bdk_mio_emm_dma_fifo_cmd_t
#define bustype_BDK_MIO_EMM_DMA_FIFO_CMD BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_FIFO_CMD "MIO_EMM_DMA_FIFO_CMD"
#define device_bar_BDK_MIO_EMM_DMA_FIFO_CMD 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_FIFO_CMD 0
#define arguments_BDK_MIO_EMM_DMA_FIFO_CMD -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_int
 *
 * eMMC DMA Interrupt Register
 * Sixty-four-bit operations must be used to access this register.
 */
union bdk_mio_emm_dma_int
{
    uint64_t u;
    struct bdk_mio_emm_dma_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t fifo                  : 1;  /**< [  1:  1](R/W1C/H) Internal DMA FIFO has dropped to level specified by MIO_EMM_DMA_FIFO_CFG[INT_LVL]. */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Internal DMA engine request completion interrupt. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Internal DMA engine request completion interrupt. */
        uint64_t fifo                  : 1;  /**< [  1:  1](R/W1C/H) Internal DMA FIFO has dropped to level specified by MIO_EMM_DMA_FIFO_CFG[INT_LVL]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_dma_int_s cn; */
};
typedef union bdk_mio_emm_dma_int bdk_mio_emm_dma_int_t;

#define BDK_MIO_EMM_DMA_INT BDK_MIO_EMM_DMA_INT_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_INT_FUNC(void)
{
    return 0x87e009000190ll;
}

#define typedef_BDK_MIO_EMM_DMA_INT bdk_mio_emm_dma_int_t
#define bustype_BDK_MIO_EMM_DMA_INT BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_INT "MIO_EMM_DMA_INT"
#define device_bar_BDK_MIO_EMM_DMA_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_INT 0
#define arguments_BDK_MIO_EMM_DMA_INT -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_int_ena_w1c
 *
 * eMMC DMA Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_mio_emm_dma_int_ena_w1c
{
    uint64_t u;
    struct bdk_mio_emm_dma_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t fifo                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MIO_EMM_DMA_INT[FIFO]. */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MIO_EMM_DMA_INT[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MIO_EMM_DMA_INT[DONE]. */
        uint64_t fifo                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MIO_EMM_DMA_INT[FIFO]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_dma_int_ena_w1c_s cn; */
};
typedef union bdk_mio_emm_dma_int_ena_w1c bdk_mio_emm_dma_int_ena_w1c_t;

#define BDK_MIO_EMM_DMA_INT_ENA_W1C BDK_MIO_EMM_DMA_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_INT_ENA_W1C_FUNC(void)
{
    return 0x87e0090001a8ll;
}

#define typedef_BDK_MIO_EMM_DMA_INT_ENA_W1C bdk_mio_emm_dma_int_ena_w1c_t
#define bustype_BDK_MIO_EMM_DMA_INT_ENA_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_INT_ENA_W1C "MIO_EMM_DMA_INT_ENA_W1C"
#define device_bar_BDK_MIO_EMM_DMA_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_INT_ENA_W1C 0
#define arguments_BDK_MIO_EMM_DMA_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_int_ena_w1s
 *
 * eMMC DMA Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_mio_emm_dma_int_ena_w1s
{
    uint64_t u;
    struct bdk_mio_emm_dma_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t fifo                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MIO_EMM_DMA_INT[FIFO]. */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MIO_EMM_DMA_INT[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MIO_EMM_DMA_INT[DONE]. */
        uint64_t fifo                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MIO_EMM_DMA_INT[FIFO]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_dma_int_ena_w1s_s cn; */
};
typedef union bdk_mio_emm_dma_int_ena_w1s bdk_mio_emm_dma_int_ena_w1s_t;

#define BDK_MIO_EMM_DMA_INT_ENA_W1S BDK_MIO_EMM_DMA_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_INT_ENA_W1S_FUNC(void)
{
    return 0x87e0090001a0ll;
}

#define typedef_BDK_MIO_EMM_DMA_INT_ENA_W1S bdk_mio_emm_dma_int_ena_w1s_t
#define bustype_BDK_MIO_EMM_DMA_INT_ENA_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_INT_ENA_W1S "MIO_EMM_DMA_INT_ENA_W1S"
#define device_bar_BDK_MIO_EMM_DMA_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_INT_ENA_W1S 0
#define arguments_BDK_MIO_EMM_DMA_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_dma_int_w1s
 *
 * eMMC DMA Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_mio_emm_dma_int_w1s
{
    uint64_t u;
    struct bdk_mio_emm_dma_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t fifo                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MIO_EMM_DMA_INT[FIFO]. */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MIO_EMM_DMA_INT[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MIO_EMM_DMA_INT[DONE]. */
        uint64_t fifo                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MIO_EMM_DMA_INT[FIFO]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_dma_int_w1s_s cn; */
};
typedef union bdk_mio_emm_dma_int_w1s bdk_mio_emm_dma_int_w1s_t;

#define BDK_MIO_EMM_DMA_INT_W1S BDK_MIO_EMM_DMA_INT_W1S_FUNC()
static inline uint64_t BDK_MIO_EMM_DMA_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_DMA_INT_W1S_FUNC(void)
{
    return 0x87e009000198ll;
}

#define typedef_BDK_MIO_EMM_DMA_INT_W1S bdk_mio_emm_dma_int_w1s_t
#define bustype_BDK_MIO_EMM_DMA_INT_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_DMA_INT_W1S "MIO_EMM_DMA_INT_W1S"
#define device_bar_BDK_MIO_EMM_DMA_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_DMA_INT_W1S 0
#define arguments_BDK_MIO_EMM_DMA_INT_W1S -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_int
 *
 * eMMC Interrupt Register
 */
union bdk_mio_emm_int
{
    uint64_t u;
    struct bdk_mio_emm_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1C/H) Poisoned read data received on NCB read request.
                                                                 This error will typically be handled by the SCP. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1C/H) Fault received on NCB read request. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1C/H) Switch operation encountered an error. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1C/H) Switch operation completed successfully. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1C/H) External DMA transfer encountered an error. See MIO_EMM_RSP_STS. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1C/H) Operation specified by MIO_EMM_CMD encountered an error. See MIO_EMM_RSP_STS. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1C/H) External DMA transfer completed successfully. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1C/H) Operation specified by MIO_EMM_CMD completed successfully. */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1C/H) The next 512B block transfer of a multiblock transfer has completed. */
#else /* Word 0 - Little Endian */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1C/H) The next 512B block transfer of a multiblock transfer has completed. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1C/H) Operation specified by MIO_EMM_CMD completed successfully. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1C/H) External DMA transfer completed successfully. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1C/H) Operation specified by MIO_EMM_CMD encountered an error. See MIO_EMM_RSP_STS. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1C/H) External DMA transfer encountered an error. See MIO_EMM_RSP_STS. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1C/H) Switch operation completed successfully. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1C/H) Switch operation encountered an error. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1C/H) Fault received on NCB read request. */
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1C/H) Poisoned read data received on NCB read request.
                                                                 This error will typically be handled by the SCP. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_int_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1C/H) Switch operation encountered an error. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1C/H) Switch operation completed successfully. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1C/H) External DMA transfer encountered an error. See MIO_EMM_RSP_STS. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1C/H) Operation specified by MIO_EMM_CMD encountered an error. See MIO_EMM_RSP_STS. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1C/H) External DMA transfer completed successfully. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1C/H) Operation specified by MIO_EMM_CMD completed successfully. */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1C/H) The next 512B block transfer of a multiblock transfer has completed. */
#else /* Word 0 - Little Endian */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1C/H) The next 512B block transfer of a multiblock transfer has completed. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1C/H) Operation specified by MIO_EMM_CMD completed successfully. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1C/H) External DMA transfer completed successfully. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1C/H) Operation specified by MIO_EMM_CMD encountered an error. See MIO_EMM_RSP_STS. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1C/H) External DMA transfer encountered an error. See MIO_EMM_RSP_STS. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1C/H) Switch operation completed successfully. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1C/H) Switch operation encountered an error. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_emm_int_s cn9; */
};
typedef union bdk_mio_emm_int bdk_mio_emm_int_t;

#define BDK_MIO_EMM_INT BDK_MIO_EMM_INT_FUNC()
static inline uint64_t BDK_MIO_EMM_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_INT_FUNC(void)
{
    return 0x87e009002078ll;
}

#define typedef_BDK_MIO_EMM_INT bdk_mio_emm_int_t
#define bustype_BDK_MIO_EMM_INT BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_INT "MIO_EMM_INT"
#define device_bar_BDK_MIO_EMM_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_INT 0
#define arguments_BDK_MIO_EMM_INT -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_int_ena_w1c
 *
 * eMMC Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_mio_emm_int_ena_w1c
{
    uint64_t u;
    struct bdk_mio_emm_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for MIO_EMM_INT[NCB_RAS]. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for MIO_EMM_INT[NCB_FLT]. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MIO_EMM_INT[DMA_ERR]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MIO_EMM_INT[CMD_DONE]. */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MIO_EMM_INT[BUF_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MIO_EMM_INT[BUF_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MIO_EMM_INT[CMD_DONE]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MIO_EMM_INT[DMA_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for MIO_EMM_INT[NCB_FLT]. */
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for MIO_EMM_INT[NCB_RAS]. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_int_ena_w1c_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MIO_EMM_INT[DMA_ERR]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MIO_EMM_INT[CMD_DONE]. */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MIO_EMM_INT[BUF_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for MIO_EMM_INT[BUF_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for MIO_EMM_INT[CMD_DONE]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for MIO_EMM_INT[DMA_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_emm_int_ena_w1c_s cn9; */
};
typedef union bdk_mio_emm_int_ena_w1c bdk_mio_emm_int_ena_w1c_t;

#define BDK_MIO_EMM_INT_ENA_W1C BDK_MIO_EMM_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_MIO_EMM_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_INT_ENA_W1C_FUNC(void)
{
    return 0x87e0090020b8ll;
}

#define typedef_BDK_MIO_EMM_INT_ENA_W1C bdk_mio_emm_int_ena_w1c_t
#define bustype_BDK_MIO_EMM_INT_ENA_W1C BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_INT_ENA_W1C "MIO_EMM_INT_ENA_W1C"
#define device_bar_BDK_MIO_EMM_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_INT_ENA_W1C 0
#define arguments_BDK_MIO_EMM_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_int_ena_w1s
 *
 * eMMC Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_mio_emm_int_ena_w1s
{
    uint64_t u;
    struct bdk_mio_emm_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for MIO_EMM_INT[NCB_RAS]. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for MIO_EMM_INT[NCB_FLT]. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MIO_EMM_INT[DMA_ERR]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MIO_EMM_INT[CMD_DONE]. */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MIO_EMM_INT[BUF_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MIO_EMM_INT[BUF_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MIO_EMM_INT[CMD_DONE]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MIO_EMM_INT[DMA_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for MIO_EMM_INT[NCB_FLT]. */
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for MIO_EMM_INT[NCB_RAS]. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_int_ena_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MIO_EMM_INT[DMA_ERR]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MIO_EMM_INT[CMD_DONE]. */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MIO_EMM_INT[BUF_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for MIO_EMM_INT[BUF_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for MIO_EMM_INT[CMD_DONE]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for MIO_EMM_INT[DMA_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_emm_int_ena_w1s_s cn9; */
};
typedef union bdk_mio_emm_int_ena_w1s bdk_mio_emm_int_ena_w1s_t;

#define BDK_MIO_EMM_INT_ENA_W1S BDK_MIO_EMM_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_MIO_EMM_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_INT_ENA_W1S_FUNC(void)
{
    return 0x87e0090020b0ll;
}

#define typedef_BDK_MIO_EMM_INT_ENA_W1S bdk_mio_emm_int_ena_w1s_t
#define bustype_BDK_MIO_EMM_INT_ENA_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_INT_ENA_W1S "MIO_EMM_INT_ENA_W1S"
#define device_bar_BDK_MIO_EMM_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_INT_ENA_W1S 0
#define arguments_BDK_MIO_EMM_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_int_w1s
 *
 * eMMC Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_mio_emm_int_w1s
{
    uint64_t u;
    struct bdk_mio_emm_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets MIO_EMM_INT[NCB_RAS]. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1S/H) Reads or sets MIO_EMM_INT[NCB_FLT]. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MIO_EMM_INT[DMA_ERR]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MIO_EMM_INT[CMD_DONE]. */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MIO_EMM_INT[BUF_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MIO_EMM_INT[BUF_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MIO_EMM_INT[CMD_DONE]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MIO_EMM_INT[DMA_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t ncb_flt               : 1;  /**< [  7:  7](R/W1S/H) Reads or sets MIO_EMM_INT[NCB_FLT]. */
        uint64_t ncb_ras               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets MIO_EMM_INT[NCB_RAS]. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_int_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_7_63         : 57;
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MIO_EMM_INT[DMA_ERR]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MIO_EMM_INT[CMD_DONE]. */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MIO_EMM_INT[BUF_DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t buf_done              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets MIO_EMM_INT[BUF_DONE]. */
        uint64_t cmd_done              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MIO_EMM_INT[CMD_DONE]. */
        uint64_t dma_done              : 1;  /**< [  2:  2](R/W1S/H) Reads or sets MIO_EMM_INT[DMA_DONE]. */
        uint64_t cmd_err               : 1;  /**< [  3:  3](R/W1S/H) Reads or sets MIO_EMM_INT[CMD_ERR]. */
        uint64_t dma_err               : 1;  /**< [  4:  4](R/W1S/H) Reads or sets MIO_EMM_INT[DMA_ERR]. */
        uint64_t switch_done           : 1;  /**< [  5:  5](R/W1S/H) Reads or sets MIO_EMM_INT[SWITCH_DONE]. */
        uint64_t switch_err            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets MIO_EMM_INT[SWITCH_ERR]. */
        uint64_t reserved_7_63         : 57;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_emm_int_w1s_s cn9; */
};
typedef union bdk_mio_emm_int_w1s bdk_mio_emm_int_w1s_t;

#define BDK_MIO_EMM_INT_W1S BDK_MIO_EMM_INT_W1S_FUNC()
static inline uint64_t BDK_MIO_EMM_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_INT_W1S_FUNC(void)
{
    return 0x87e009002080ll;
}

#define typedef_BDK_MIO_EMM_INT_W1S bdk_mio_emm_int_w1s_t
#define bustype_BDK_MIO_EMM_INT_W1S BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_INT_W1S "MIO_EMM_INT_W1S"
#define device_bar_BDK_MIO_EMM_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_INT_W1S 0
#define arguments_BDK_MIO_EMM_INT_W1S -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_io_ctl
 *
 * eMMC I/O Control Register
 */
union bdk_mio_emm_io_ctl
{
    uint64_t u;
    struct bdk_mio_emm_io_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t drive                 : 2;  /**< [  3:  2](R/W) eMMC bus pin output drive strength.
                                                                 0x0 = 2 mA.
                                                                 0x1 = 4 mA.
                                                                 0x2 = 8 mA.
                                                                 0x3 = 16 mA. */
        uint64_t reserved_1            : 1;
        uint64_t slew                  : 1;  /**< [  0:  0](R/W) eMMC bus pins output slew rate control.
                                                                 0 = Low slew rate.
                                                                 1 = High slew rate. */
#else /* Word 0 - Little Endian */
        uint64_t slew                  : 1;  /**< [  0:  0](R/W) eMMC bus pins output slew rate control.
                                                                 0 = Low slew rate.
                                                                 1 = High slew rate. */
        uint64_t reserved_1            : 1;
        uint64_t drive                 : 2;  /**< [  3:  2](R/W) eMMC bus pin output drive strength.
                                                                 0x0 = 2 mA.
                                                                 0x1 = 4 mA.
                                                                 0x2 = 8 mA.
                                                                 0x3 = 16 mA. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_io_ctl_s cn; */
};
typedef union bdk_mio_emm_io_ctl bdk_mio_emm_io_ctl_t;

#define BDK_MIO_EMM_IO_CTL BDK_MIO_EMM_IO_CTL_FUNC()
static inline uint64_t BDK_MIO_EMM_IO_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_IO_CTL_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e009002040ll;
    __bdk_csr_fatal("MIO_EMM_IO_CTL", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_IO_CTL bdk_mio_emm_io_ctl_t
#define bustype_BDK_MIO_EMM_IO_CTL BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_IO_CTL "MIO_EMM_IO_CTL"
#define device_bar_BDK_MIO_EMM_IO_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_IO_CTL 0
#define arguments_BDK_MIO_EMM_IO_CTL -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_mode#
 *
 * eMMC Operating Mode Register
 */
union bdk_mio_emm_modex
{
    uint64_t u;
    struct bdk_mio_emm_modex_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](RO/H) Current high-speed 400 timing mode.
                                                                 Required when CLK frequency is higher than 200 MHz.
                                                                 EMMC_VDD of 1.8V required.
                                                                 Bus width of 8-bit data bus (dual data rate) required. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](RO/H) Current high-speed 200 timing mode.
                                                                 Required when CLK frequency is higher than 50 MHz.
                                                                 EMMC_VDD of 1.8V required.
                                                                 Bus width of 4-bit or 8-bit data bus (single data rate) required. */
        uint64_t hs_timing             : 1;  /**< [ 48: 48](RO/H) Current high-speed timing mode.
                                                                 Required when CLK frequency is higher than 20 MHz. */
        uint64_t reserved_43_47        : 5;
        uint64_t bus_width             : 3;  /**< [ 42: 40](RO/H) Current card bus width mode. Out of reset, the card is in 1-bit data bus mode.
                                                                 0x0 = 1-bit data bus (power on).
                                                                 0x1 = 4-bit data bus.
                                                                 0x2 = 8-bit data bus.
                                                                 0x3 = Reserved.
                                                                 0x4 = Reserved.
                                                                 0x5 = 4-bit data bus (dual data rate).
                                                                 0x6 = 8-bit data bus (dual data rate).
                                                                 0x7 = Reserved.
                                                                 0x8 = Reserved. */
        uint64_t reserved_37_39        : 3;
        uint64_t clk_swap              : 1;  /**< [ 36: 36](RO/H) Data clock edge swap. When one, the logic swaps the data capture edge between the
                                                                 positive and negative edges of the eMMC clock. */
        uint64_t power_class           : 4;  /**< [ 35: 32](RO/H) Out of reset, the card power class is 0, which is the minimum current consumption class
                                                                 for the card. EXT_CSD bytes [203:200] and [239:238] contain the power class for different
                                                                 BUS_WITDH and CLK frequencies. Software should write this field with the 4-bit field from
                                                                 the EXT_CSD bytes corresponding to the selected operating mode. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin high. */
        uint64_t clk_lo                : 16; /**< [ 15:  0](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin low. */
#else /* Word 0 - Little Endian */
        uint64_t clk_lo                : 16; /**< [ 15:  0](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin low. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin high. */
        uint64_t power_class           : 4;  /**< [ 35: 32](RO/H) Out of reset, the card power class is 0, which is the minimum current consumption class
                                                                 for the card. EXT_CSD bytes [203:200] and [239:238] contain the power class for different
                                                                 BUS_WITDH and CLK frequencies. Software should write this field with the 4-bit field from
                                                                 the EXT_CSD bytes corresponding to the selected operating mode. */
        uint64_t clk_swap              : 1;  /**< [ 36: 36](RO/H) Data clock edge swap. When one, the logic swaps the data capture edge between the
                                                                 positive and negative edges of the eMMC clock. */
        uint64_t reserved_37_39        : 3;
        uint64_t bus_width             : 3;  /**< [ 42: 40](RO/H) Current card bus width mode. Out of reset, the card is in 1-bit data bus mode.
                                                                 0x0 = 1-bit data bus (power on).
                                                                 0x1 = 4-bit data bus.
                                                                 0x2 = 8-bit data bus.
                                                                 0x3 = Reserved.
                                                                 0x4 = Reserved.
                                                                 0x5 = 4-bit data bus (dual data rate).
                                                                 0x6 = 8-bit data bus (dual data rate).
                                                                 0x7 = Reserved.
                                                                 0x8 = Reserved. */
        uint64_t reserved_43_47        : 5;
        uint64_t hs_timing             : 1;  /**< [ 48: 48](RO/H) Current high-speed timing mode.
                                                                 Required when CLK frequency is higher than 20 MHz. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](RO/H) Current high-speed 200 timing mode.
                                                                 Required when CLK frequency is higher than 50 MHz.
                                                                 EMMC_VDD of 1.8V required.
                                                                 Bus width of 4-bit or 8-bit data bus (single data rate) required. */
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](RO/H) Current high-speed 400 timing mode.
                                                                 Required when CLK frequency is higher than 200 MHz.
                                                                 EMMC_VDD of 1.8V required.
                                                                 Bus width of 8-bit data bus (dual data rate) required. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_modex_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t hs_timing             : 1;  /**< [ 48: 48](RO/H) Current high-speed timing mode.
                                                                 Required when CLK frequency is higher than 20 MHz. */
        uint64_t reserved_43_47        : 5;
        uint64_t bus_width             : 3;  /**< [ 42: 40](RO/H) Current card bus width mode. Out of reset, the card is in 1-bit data bus mode.
                                                                 0x0 = 1-bit data bus (power on).
                                                                 0x1 = 4-bit data bus.
                                                                 0x2 = 8-bit data bus.
                                                                 0x3 = Reserved.
                                                                 0x4 = Reserved.
                                                                 0x5 = 4-bit data bus (dual data rate).
                                                                 0x6 = 8-bit data bus (dual data rate).
                                                                 0x7 = Reserved.
                                                                 0x8 = Reserved. */
        uint64_t reserved_36_39        : 4;
        uint64_t power_class           : 4;  /**< [ 35: 32](RO/H) Out of reset, the card power class is 0, which is the minimum current consumption class
                                                                 for the card. EXT_CSD bytes [203:200] and [239:238] contain the power class for different
                                                                 BUS_WITDH and CLK frequencies. Software should write this field with the 4-bit field from
                                                                 the EXT_CSD bytes corresponding to the selected operating mode. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin high. */
        uint64_t clk_lo                : 16; /**< [ 15:  0](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin low. */
#else /* Word 0 - Little Endian */
        uint64_t clk_lo                : 16; /**< [ 15:  0](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin low. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin high. */
        uint64_t power_class           : 4;  /**< [ 35: 32](RO/H) Out of reset, the card power class is 0, which is the minimum current consumption class
                                                                 for the card. EXT_CSD bytes [203:200] and [239:238] contain the power class for different
                                                                 BUS_WITDH and CLK frequencies. Software should write this field with the 4-bit field from
                                                                 the EXT_CSD bytes corresponding to the selected operating mode. */
        uint64_t reserved_36_39        : 4;
        uint64_t bus_width             : 3;  /**< [ 42: 40](RO/H) Current card bus width mode. Out of reset, the card is in 1-bit data bus mode.
                                                                 0x0 = 1-bit data bus (power on).
                                                                 0x1 = 4-bit data bus.
                                                                 0x2 = 8-bit data bus.
                                                                 0x3 = Reserved.
                                                                 0x4 = Reserved.
                                                                 0x5 = 4-bit data bus (dual data rate).
                                                                 0x6 = 8-bit data bus (dual data rate).
                                                                 0x7 = Reserved.
                                                                 0x8 = Reserved. */
        uint64_t reserved_43_47        : 5;
        uint64_t hs_timing             : 1;  /**< [ 48: 48](RO/H) Current high-speed timing mode.
                                                                 Required when CLK frequency is higher than 20 MHz. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_emm_modex_s cn9; */
    struct bdk_mio_emm_modex_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_51_63        : 13;
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](RO/H) Current high-speed 400 timing mode.
                                                                 Required when CLK frequency is higher than 200 MHz.
                                                                 EMMC_VDD of 1.8V required.
                                                                 Bus width of 8-bit data bus (dual data rate) required. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](RO/H) Current high-speed 200 timing mode.
                                                                 Required when CLK frequency is higher than 50 MHz.
                                                                 EMMC_VDD of 1.8V required.
                                                                 Bus width of 4-bit or 8-bit data bus (single data rate) required. */
        uint64_t hs_timing             : 1;  /**< [ 48: 48](RO/H) Current high-speed timing mode.
                                                                 Required when CLK frequency is higher than 20 MHz. */
        uint64_t reserved_43_47        : 5;
        uint64_t bus_width             : 3;  /**< [ 42: 40](RO/H) Current card bus width mode. Out of reset, the card is in 1-bit data bus mode.
                                                                 0x0 = 1-bit data bus (power on).
                                                                 0x1 = 4-bit data bus.
                                                                 0x2 = 8-bit data bus.
                                                                 0x3 = Reserved.
                                                                 0x4 = Reserved.
                                                                 0x5 = 4-bit data bus (dual data rate).
                                                                 0x6 = 8-bit data bus (dual data rate).
                                                                 0x7 = Reserved.
                                                                 0x8 = Reserved. */
        uint64_t reserved_36_39        : 4;
        uint64_t power_class           : 4;  /**< [ 35: 32](RO/H) Out of reset, the card power class is 0, which is the minimum current consumption class
                                                                 for the card. EXT_CSD bytes [203:200] and [239:238] contain the power class for different
                                                                 BUS_WITDH and CLK frequencies. Software should write this field with the 4-bit field from
                                                                 the EXT_CSD bytes corresponding to the selected operating mode. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin high. */
        uint64_t clk_lo                : 16; /**< [ 15:  0](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin low. */
#else /* Word 0 - Little Endian */
        uint64_t clk_lo                : 16; /**< [ 15:  0](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin low. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](RO/H) Current number of coprocessor-clocks to hold the eMMC CLK pin high. */
        uint64_t power_class           : 4;  /**< [ 35: 32](RO/H) Out of reset, the card power class is 0, which is the minimum current consumption class
                                                                 for the card. EXT_CSD bytes [203:200] and [239:238] contain the power class for different
                                                                 BUS_WITDH and CLK frequencies. Software should write this field with the 4-bit field from
                                                                 the EXT_CSD bytes corresponding to the selected operating mode. */
        uint64_t reserved_36_39        : 4;
        uint64_t bus_width             : 3;  /**< [ 42: 40](RO/H) Current card bus width mode. Out of reset, the card is in 1-bit data bus mode.
                                                                 0x0 = 1-bit data bus (power on).
                                                                 0x1 = 4-bit data bus.
                                                                 0x2 = 8-bit data bus.
                                                                 0x3 = Reserved.
                                                                 0x4 = Reserved.
                                                                 0x5 = 4-bit data bus (dual data rate).
                                                                 0x6 = 8-bit data bus (dual data rate).
                                                                 0x7 = Reserved.
                                                                 0x8 = Reserved. */
        uint64_t reserved_43_47        : 5;
        uint64_t hs_timing             : 1;  /**< [ 48: 48](RO/H) Current high-speed timing mode.
                                                                 Required when CLK frequency is higher than 20 MHz. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](RO/H) Current high-speed 200 timing mode.
                                                                 Required when CLK frequency is higher than 50 MHz.
                                                                 EMMC_VDD of 1.8V required.
                                                                 Bus width of 4-bit or 8-bit data bus (single data rate) required. */
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](RO/H) Current high-speed 400 timing mode.
                                                                 Required when CLK frequency is higher than 200 MHz.
                                                                 EMMC_VDD of 1.8V required.
                                                                 Bus width of 8-bit data bus (dual data rate) required. */
        uint64_t reserved_51_63        : 13;
#endif /* Word 0 - End */
    } cn96xxp1;
    /* struct bdk_mio_emm_modex_s cn96xxp3; */
    /* struct bdk_mio_emm_modex_s cn98xx; */
    /* struct bdk_mio_emm_modex_s cnf95xx; */
    /* struct bdk_mio_emm_modex_s loki; */
};
typedef union bdk_mio_emm_modex bdk_mio_emm_modex_t;

static inline uint64_t BDK_MIO_EMM_MODEX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_MODEX(unsigned long a)
{
    if (a<=3)
        return 0x87e009002008ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("MIO_EMM_MODEX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_MODEX(a) bdk_mio_emm_modex_t
#define bustype_BDK_MIO_EMM_MODEX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_MODEX(a) "MIO_EMM_MODEX"
#define device_bar_BDK_MIO_EMM_MODEX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_MODEX(a) (a)
#define arguments_BDK_MIO_EMM_MODEX(a) (a),-1,-1,-1

/**
 * Register (RSL) mio_emm_msix_pba#
 *
 * eMMC MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the MIO_EMM_INT_VEC_E
 * enumeration.
 */
union bdk_mio_emm_msix_pbax
{
    uint64_t u;
    struct bdk_mio_emm_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MIO_EMM_MSIX_VEC()_CTL, enumerated by
                                                                 MIO_EMM_INT_VEC_E. Bits that have no associated MIO_EMM_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MIO_EMM_MSIX_VEC()_CTL, enumerated by
                                                                 MIO_EMM_INT_VEC_E. Bits that have no associated MIO_EMM_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_msix_pbax_s cn; */
};
typedef union bdk_mio_emm_msix_pbax bdk_mio_emm_msix_pbax_t;

static inline uint64_t BDK_MIO_EMM_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_MSIX_PBAX(unsigned long a)
{
    if (a==0)
        return 0x87e009ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("MIO_EMM_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_MSIX_PBAX(a) bdk_mio_emm_msix_pbax_t
#define bustype_BDK_MIO_EMM_MSIX_PBAX(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_MSIX_PBAX(a) "MIO_EMM_MSIX_PBAX"
#define device_bar_BDK_MIO_EMM_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MIO_EMM_MSIX_PBAX(a) (a)
#define arguments_BDK_MIO_EMM_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (RSL) mio_emm_msix_vec#_addr
 *
 * eMMC MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the MIO_EMM_INT_VEC_E enumeration.
 */
union bdk_mio_emm_msix_vecx_addr
{
    uint64_t u;
    struct bdk_mio_emm_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MIO_EMM_MSIX_VEC()_ADDR, MIO_EMM_MSIX_VEC()_CTL, and
                                                                 corresponding bit of MIO_EMM_MSIX_PBA() are RAZ/WI and does not cause a fault when
                                                                 accessed by the nonsecure world.

                                                                 If PCCPF_MIO_EMM_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MIO_EMM_MSIX_VEC()_ADDR, MIO_EMM_MSIX_VEC()_CTL, and
                                                                 corresponding bit of MIO_EMM_MSIX_PBA() are RAZ/WI and does not cause a fault when
                                                                 accessed by the nonsecure world.

                                                                 If PCCPF_MIO_EMM_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_msix_vecx_addr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MIO_EMM_MSIX_VEC()_ADDR, MIO_EMM_MSIX_VEC()_CTL, and
                                                                 corresponding bit of MIO_EMM_MSIX_PBA() are RAZ/WI and does not cause a fault when
                                                                 accessed by the nonsecure world.

                                                                 If PCCPF_MIO_EMM_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MIO_EMM_MSIX_VEC()_ADDR, MIO_EMM_MSIX_VEC()_CTL, and
                                                                 corresponding bit of MIO_EMM_MSIX_PBA() are RAZ/WI and does not cause a fault when
                                                                 accessed by the nonsecure world.

                                                                 If PCCPF_MIO_EMM_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_emm_msix_vecx_addr_s cn9; */
    /* struct bdk_mio_emm_msix_vecx_addr_s cn96xxp1; */
    struct bdk_mio_emm_msix_vecx_addr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's MIO_EMM_MSIX_VEC()_ADDR, MIO_EMM_MSIX_VEC()_CTL, and
                                                                 corresponding bit of MIO_EMM_MSIX_PBA() are RAZ/WI and does not cause a fault when
                                                                 accessed by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_MIO_EMM_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set.

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

                                                                 1 = This vector's MIO_EMM_MSIX_VEC()_ADDR, MIO_EMM_MSIX_VEC()_CTL, and
                                                                 corresponding bit of MIO_EMM_MSIX_PBA() are RAZ/WI and does not cause a fault when
                                                                 accessed by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_MIO_EMM_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set.

                                                                 Also note the following:
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_EN]=1, all secure vectors (including secure
                                                                 VF vectors) will act as if PCCPF/PCCVF_XXX_MSIX_CAP_HDR[MSIXEN]=1,
                                                                 PCCPF/PCCVF_XXX_MSIX_CAP_HDR[FUNM]=0 and PCCPF/PCCVF_XXX_CMD[ME]=1.
                                                                 * When PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1, all secure vectors (including
                                                                 secure VF vectors) are considered physical, regardless of
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mio_emm_msix_vecx_addr_cn96xxp3 cn98xx; */
    /* struct bdk_mio_emm_msix_vecx_addr_cn96xxp3 cnf95xx; */
    /* struct bdk_mio_emm_msix_vecx_addr_cn96xxp3 loki; */
};
typedef union bdk_mio_emm_msix_vecx_addr bdk_mio_emm_msix_vecx_addr_t;

static inline uint64_t BDK_MIO_EMM_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=8))
        return 0x87e009f00000ll + 0x10ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=10))
        return 0x87e009f00000ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("MIO_EMM_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_MSIX_VECX_ADDR(a) bdk_mio_emm_msix_vecx_addr_t
#define bustype_BDK_MIO_EMM_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_MSIX_VECX_ADDR(a) "MIO_EMM_MSIX_VECX_ADDR"
#define device_bar_BDK_MIO_EMM_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MIO_EMM_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_MIO_EMM_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (RSL) mio_emm_msix_vec#_ctl
 *
 * eMMC MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the MIO_EMM_INT_VEC_E enumeration.
 */
union bdk_mio_emm_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_mio_emm_msix_vecx_ctl_s
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
    struct bdk_mio_emm_msix_vecx_ctl_cn8
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
    /* struct bdk_mio_emm_msix_vecx_ctl_s cn9; */
};
typedef union bdk_mio_emm_msix_vecx_ctl bdk_mio_emm_msix_vecx_ctl_t;

static inline uint64_t BDK_MIO_EMM_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a<=8))
        return 0x87e009f00008ll + 0x10ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=10))
        return 0x87e009f00008ll + 0x10ll * ((a) & 0xf);
    __bdk_csr_fatal("MIO_EMM_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_MSIX_VECX_CTL(a) bdk_mio_emm_msix_vecx_ctl_t
#define bustype_BDK_MIO_EMM_MSIX_VECX_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_MSIX_VECX_CTL(a) "MIO_EMM_MSIX_VECX_CTL"
#define device_bar_BDK_MIO_EMM_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MIO_EMM_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_MIO_EMM_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) mio_emm_rca
 *
 * eMMC Relative Card Address Register
 */
union bdk_mio_emm_rca
{
    uint64_t u;
    struct bdk_mio_emm_rca_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t card_rca              : 16; /**< [ 15:  0](R/W/H) Whenever software performs CMD7, hardware updates [CARD_RCA] with the relative card
                                                                 address
                                                                 from the MIO_EMM_CMD[ARG], unless the operation encounters an error. */
#else /* Word 0 - Little Endian */
        uint64_t card_rca              : 16; /**< [ 15:  0](R/W/H) Whenever software performs CMD7, hardware updates [CARD_RCA] with the relative card
                                                                 address
                                                                 from the MIO_EMM_CMD[ARG], unless the operation encounters an error. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_rca_s cn; */
};
typedef union bdk_mio_emm_rca bdk_mio_emm_rca_t;

#define BDK_MIO_EMM_RCA BDK_MIO_EMM_RCA_FUNC()
static inline uint64_t BDK_MIO_EMM_RCA_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_RCA_FUNC(void)
{
    return 0x87e0090020a0ll;
}

#define typedef_BDK_MIO_EMM_RCA bdk_mio_emm_rca_t
#define bustype_BDK_MIO_EMM_RCA BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_RCA "MIO_EMM_RCA"
#define device_bar_BDK_MIO_EMM_RCA 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_RCA 0
#define arguments_BDK_MIO_EMM_RCA -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_rsp_hi
 *
 * eMMC Response Data High Register
 */
union bdk_mio_emm_rsp_hi
{
    uint64_t u;
    struct bdk_mio_emm_rsp_hi_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](RO/H) Command response (as per JEDEC eMMC spec and SD Specifications):
                                                                 _ RSP_TYPE = 1: DAT[63:0] = 0x0.
                                                                 _ RSP_TYPE = 2: DAT[63:0] = CID[127:64] or CSD[127:64].
                                                                 _ RSP_TYPE = 3: DAT[63:0] = 0x0.
                                                                 _ RSP_TYPE = 4: DAT[63:0] = 0x0.
                                                                 _ RSP_TYPE = 5: DAT[63:0] = 0x0. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](RO/H) Command response (as per JEDEC eMMC spec and SD Specifications):
                                                                 _ RSP_TYPE = 1: DAT[63:0] = 0x0.
                                                                 _ RSP_TYPE = 2: DAT[63:0] = CID[127:64] or CSD[127:64].
                                                                 _ RSP_TYPE = 3: DAT[63:0] = 0x0.
                                                                 _ RSP_TYPE = 4: DAT[63:0] = 0x0.
                                                                 _ RSP_TYPE = 5: DAT[63:0] = 0x0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_rsp_hi_s cn; */
};
typedef union bdk_mio_emm_rsp_hi bdk_mio_emm_rsp_hi_t;

#define BDK_MIO_EMM_RSP_HI BDK_MIO_EMM_RSP_HI_FUNC()
static inline uint64_t BDK_MIO_EMM_RSP_HI_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_RSP_HI_FUNC(void)
{
    return 0x87e009002070ll;
}

#define typedef_BDK_MIO_EMM_RSP_HI bdk_mio_emm_rsp_hi_t
#define bustype_BDK_MIO_EMM_RSP_HI BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_RSP_HI "MIO_EMM_RSP_HI"
#define device_bar_BDK_MIO_EMM_RSP_HI 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_RSP_HI 0
#define arguments_BDK_MIO_EMM_RSP_HI -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_rsp_lo
 *
 * eMMC Response Data Low Register
 */
union bdk_mio_emm_rsp_lo
{
    uint64_t u;
    struct bdk_mio_emm_rsp_lo_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](RO/H) Command response (as per JEDEC eMMC spec and SD Specifications).

                                                                 \<pre\>
                                                                 RSP_TYPE = 1:
                                                                 DAT[63:46] = 0x0
                                                                 DAT[45:40] = Command index
                                                                 DAT[39: 8] = Card status
                                                                 DAT[ 7: 1] = CRC7
                                                                 DAT[    0] = End bit

                                                                 RSP_TYPE = 2:
                                                                 DAT[63: 1] = CID[63:1] or CSD[63:1] including CRC
                                                                 DAT[    0] = End bit

                                                                 RSP_TYPE = 3:
                                                                 DAT[63:46] = 0x0
                                                                 DAT[45:40] = Check bits (0x3F)
                                                                 DAT[39: 8] = OCR register
                                                                 DAT[ 7: 1] = Check bits (0x7F)
                                                                 DAT[    0] = End bit

                                                                 RSP_TYPE = 4:
                                                                 DAT[63:46] = 0x0
                                                                 DAT[45:40] = CMD39 ('10111')
                                                                 DAT[39:24] = RCA[31:16]
                                                                 DAT[   23] = Status
                                                                 DAT[22:16] = Register address
                                                                 DAT[15: 8] = Register contents
                                                                 DAT[ 7: 1] = CRC7
                                                                 DAT[    0] = End bit

                                                                 RSP_TYPE = 5:
                                                                 DAT[63:46] = 0x0
                                                                 DAT[45:40] = CMD40 ('10100')
                                                                 DAT[39:24] = RCA[31:16]
                                                                 DAT[   23] = Status
                                                                 DAT[22:16] = Register address
                                                                 DAT[15: 8] = Not defined. May be used for IRQ data
                                                                 DAT[ 7: 1] = CRC7
                                                                 DAT[    0] = End bit
                                                                 \</pre\> */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](RO/H) Command response (as per JEDEC eMMC spec and SD Specifications).

                                                                 \<pre\>
                                                                 RSP_TYPE = 1:
                                                                 DAT[63:46] = 0x0
                                                                 DAT[45:40] = Command index
                                                                 DAT[39: 8] = Card status
                                                                 DAT[ 7: 1] = CRC7
                                                                 DAT[    0] = End bit

                                                                 RSP_TYPE = 2:
                                                                 DAT[63: 1] = CID[63:1] or CSD[63:1] including CRC
                                                                 DAT[    0] = End bit

                                                                 RSP_TYPE = 3:
                                                                 DAT[63:46] = 0x0
                                                                 DAT[45:40] = Check bits (0x3F)
                                                                 DAT[39: 8] = OCR register
                                                                 DAT[ 7: 1] = Check bits (0x7F)
                                                                 DAT[    0] = End bit

                                                                 RSP_TYPE = 4:
                                                                 DAT[63:46] = 0x0
                                                                 DAT[45:40] = CMD39 ('10111')
                                                                 DAT[39:24] = RCA[31:16]
                                                                 DAT[   23] = Status
                                                                 DAT[22:16] = Register address
                                                                 DAT[15: 8] = Register contents
                                                                 DAT[ 7: 1] = CRC7
                                                                 DAT[    0] = End bit

                                                                 RSP_TYPE = 5:
                                                                 DAT[63:46] = 0x0
                                                                 DAT[45:40] = CMD40 ('10100')
                                                                 DAT[39:24] = RCA[31:16]
                                                                 DAT[   23] = Status
                                                                 DAT[22:16] = Register address
                                                                 DAT[15: 8] = Not defined. May be used for IRQ data
                                                                 DAT[ 7: 1] = CRC7
                                                                 DAT[    0] = End bit
                                                                 \</pre\> */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_rsp_lo_s cn; */
};
typedef union bdk_mio_emm_rsp_lo bdk_mio_emm_rsp_lo_t;

#define BDK_MIO_EMM_RSP_LO BDK_MIO_EMM_RSP_LO_FUNC()
static inline uint64_t BDK_MIO_EMM_RSP_LO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_RSP_LO_FUNC(void)
{
    return 0x87e009002068ll;
}

#define typedef_BDK_MIO_EMM_RSP_LO bdk_mio_emm_rsp_lo_t
#define bustype_BDK_MIO_EMM_RSP_LO BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_RSP_LO "MIO_EMM_RSP_LO"
#define device_bar_BDK_MIO_EMM_RSP_LO 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_RSP_LO 0
#define arguments_BDK_MIO_EMM_RSP_LO -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_rsp_sts
 *
 * eMMC Response Status Register
 */
union bdk_mio_emm_rsp_sts
{
    uint64_t u;
    struct bdk_mio_emm_rsp_sts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t bus_id                : 2;  /**< [ 61: 60](RO/H) eMMC bus ID to which the response status corresponds. */
        uint64_t cmd_val               : 1;  /**< [ 59: 59](RO/H) Read-only copy of MIO_EMM_CMD[CMD_VAL]. [CMD_VAL] = 1 indicates that a direct operation is
                                                                 in progress. */
        uint64_t switch_val            : 1;  /**< [ 58: 58](RO/H) Read-only copy of MIO_EMM_SWITCH[SWITCH_EXE]. [SWITCH_VAL] = 1 indicates that a switch
                                                                 operation is in progress. */
        uint64_t dma_val               : 1;  /**< [ 57: 57](RO/H) Read-only copy of MIO_EMM_DMA[DMA_VAL]. [DMA_VAL] = 1 indicates that a DMA operation is in
                                                                 progress. */
        uint64_t dma_pend              : 1;  /**< [ 56: 56](RO/H) The DMA engine has a pending transfer resulting from an error. Software can resume the
                                                                 transfer by writing MIO_EMM_DMA[DMA_VAL] = 1.

                                                                 Software can terminate the transfer by writing MIO_EMM_DMA[DMA_VAL] = 1 and
                                                                 MIO_EMM_DMA[DAT_NULL] = 1. Hardware will then clear [DMA_PEND] and perform the DMA
                                                                 operation. */
        uint64_t acc_timeout           : 1;  /**< [ 55: 55](RO/H) The store operation to the device took longer than MIO_EMM_ACCESS_WDOG[CLK_CNT]
                                                                 coprocessor-clock cycles to complete.
                                                                 Valid when [DMA_PEND] is set. */
        uint64_t reserved_29_54        : 26;
        uint64_t dbuf_err              : 1;  /**< [ 28: 28](RO/H) For [CMD_TYPE] = 1, indicates that a DMA read data arrived from the card without a free
                                                                 DBUF. For [CMD_TYPE] = 2, indicates a DBUF underflow occurred during a DMA write. See
                                                                 MIO_EMM_DMA[THRES]. */
        uint64_t reserved_24_27        : 4;
        uint64_t dbuf                  : 1;  /**< [ 23: 23](RO/H) DBUF corresponding to the most recently attempted block transfer. */
        uint64_t blk_timeout           : 1;  /**< [ 22: 22](RO/H) Timeout waiting for read data or 3-bit CRC token. */
        uint64_t blk_crc_err           : 1;  /**< [ 21: 21](RO/H) For [CMD_TYPE] = 1, indicates a card read data CRC mismatch. MIO_EMM_RSP_STS[DBUF]
                                                                 indicates
                                                                 the failing data buffer.

                                                                 For [CMD_TYPE] = 2, indicates card returned 3-bit CRC status token indicating that the
                                                                 card
                                                                 encountered a write data CRC check mismatch. MIO_EMM_RSP_STS[DBUF] indicates the failing
                                                                 data buffer. */
        uint64_t rsp_busybit           : 1;  /**< [ 20: 20](RO/H) Debug only. eMMC protocol utilizes DAT0 as a busy signal during block writes and R1b
                                                                 responses. This bit should read zero before any DMA or Command with data is executed. */
        uint64_t stp_timeout           : 1;  /**< [ 19: 19](RO/H) Stop transmission response timeout. */
        uint64_t stp_crc_err           : 1;  /**< [ 18: 18](RO/H) Stop transmission response had a CRC error. */
        uint64_t stp_bad_sts           : 1;  /**< [ 17: 17](RO/H) Stop transmission response had bad status. */
        uint64_t stp_val               : 1;  /**< [ 16: 16](RO/H) Stop transmission response valid. */
        uint64_t rsp_timeout           : 1;  /**< [ 15: 15](RO/H) Response timeout. */
        uint64_t rsp_crc_err           : 1;  /**< [ 14: 14](RO/H) Response CRC error. */
        uint64_t rsp_bad_sts           : 1;  /**< [ 13: 13](RO/H) Response bad status. */
        uint64_t rsp_val               : 1;  /**< [ 12: 12](RO/H) Response ID. See MIO_EMM_RSP_HI/MIO_EMM_RSP_LO. */
        uint64_t rsp_type              : 3;  /**< [ 11:  9](RO/H) Indicates the response type. See MIO_EMM_RSP_HI/MIO_EMM_RSP_LO. */
        uint64_t cmd_type              : 2;  /**< [  8:  7](RO/H) eMMC command type.
                                                                 0x0 = No data.
                                                                 0x1 = Read.
                                                                 0x2 = Write. */
        uint64_t cmd_idx               : 6;  /**< [  6:  1](RO/H) eMMC command index most recently attempted. */
        uint64_t cmd_done              : 1;  /**< [  0:  0](RO/H) eMMC command completed. Once the command has completed, the status is final and can be
                                                                 examined by software. */
#else /* Word 0 - Little Endian */
        uint64_t cmd_done              : 1;  /**< [  0:  0](RO/H) eMMC command completed. Once the command has completed, the status is final and can be
                                                                 examined by software. */
        uint64_t cmd_idx               : 6;  /**< [  6:  1](RO/H) eMMC command index most recently attempted. */
        uint64_t cmd_type              : 2;  /**< [  8:  7](RO/H) eMMC command type.
                                                                 0x0 = No data.
                                                                 0x1 = Read.
                                                                 0x2 = Write. */
        uint64_t rsp_type              : 3;  /**< [ 11:  9](RO/H) Indicates the response type. See MIO_EMM_RSP_HI/MIO_EMM_RSP_LO. */
        uint64_t rsp_val               : 1;  /**< [ 12: 12](RO/H) Response ID. See MIO_EMM_RSP_HI/MIO_EMM_RSP_LO. */
        uint64_t rsp_bad_sts           : 1;  /**< [ 13: 13](RO/H) Response bad status. */
        uint64_t rsp_crc_err           : 1;  /**< [ 14: 14](RO/H) Response CRC error. */
        uint64_t rsp_timeout           : 1;  /**< [ 15: 15](RO/H) Response timeout. */
        uint64_t stp_val               : 1;  /**< [ 16: 16](RO/H) Stop transmission response valid. */
        uint64_t stp_bad_sts           : 1;  /**< [ 17: 17](RO/H) Stop transmission response had bad status. */
        uint64_t stp_crc_err           : 1;  /**< [ 18: 18](RO/H) Stop transmission response had a CRC error. */
        uint64_t stp_timeout           : 1;  /**< [ 19: 19](RO/H) Stop transmission response timeout. */
        uint64_t rsp_busybit           : 1;  /**< [ 20: 20](RO/H) Debug only. eMMC protocol utilizes DAT0 as a busy signal during block writes and R1b
                                                                 responses. This bit should read zero before any DMA or Command with data is executed. */
        uint64_t blk_crc_err           : 1;  /**< [ 21: 21](RO/H) For [CMD_TYPE] = 1, indicates a card read data CRC mismatch. MIO_EMM_RSP_STS[DBUF]
                                                                 indicates
                                                                 the failing data buffer.

                                                                 For [CMD_TYPE] = 2, indicates card returned 3-bit CRC status token indicating that the
                                                                 card
                                                                 encountered a write data CRC check mismatch. MIO_EMM_RSP_STS[DBUF] indicates the failing
                                                                 data buffer. */
        uint64_t blk_timeout           : 1;  /**< [ 22: 22](RO/H) Timeout waiting for read data or 3-bit CRC token. */
        uint64_t dbuf                  : 1;  /**< [ 23: 23](RO/H) DBUF corresponding to the most recently attempted block transfer. */
        uint64_t reserved_24_27        : 4;
        uint64_t dbuf_err              : 1;  /**< [ 28: 28](RO/H) For [CMD_TYPE] = 1, indicates that a DMA read data arrived from the card without a free
                                                                 DBUF. For [CMD_TYPE] = 2, indicates a DBUF underflow occurred during a DMA write. See
                                                                 MIO_EMM_DMA[THRES]. */
        uint64_t reserved_29_54        : 26;
        uint64_t acc_timeout           : 1;  /**< [ 55: 55](RO/H) The store operation to the device took longer than MIO_EMM_ACCESS_WDOG[CLK_CNT]
                                                                 coprocessor-clock cycles to complete.
                                                                 Valid when [DMA_PEND] is set. */
        uint64_t dma_pend              : 1;  /**< [ 56: 56](RO/H) The DMA engine has a pending transfer resulting from an error. Software can resume the
                                                                 transfer by writing MIO_EMM_DMA[DMA_VAL] = 1.

                                                                 Software can terminate the transfer by writing MIO_EMM_DMA[DMA_VAL] = 1 and
                                                                 MIO_EMM_DMA[DAT_NULL] = 1. Hardware will then clear [DMA_PEND] and perform the DMA
                                                                 operation. */
        uint64_t dma_val               : 1;  /**< [ 57: 57](RO/H) Read-only copy of MIO_EMM_DMA[DMA_VAL]. [DMA_VAL] = 1 indicates that a DMA operation is in
                                                                 progress. */
        uint64_t switch_val            : 1;  /**< [ 58: 58](RO/H) Read-only copy of MIO_EMM_SWITCH[SWITCH_EXE]. [SWITCH_VAL] = 1 indicates that a switch
                                                                 operation is in progress. */
        uint64_t cmd_val               : 1;  /**< [ 59: 59](RO/H) Read-only copy of MIO_EMM_CMD[CMD_VAL]. [CMD_VAL] = 1 indicates that a direct operation is
                                                                 in progress. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](RO/H) eMMC bus ID to which the response status corresponds. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_rsp_sts_s cn; */
};
typedef union bdk_mio_emm_rsp_sts bdk_mio_emm_rsp_sts_t;

#define BDK_MIO_EMM_RSP_STS BDK_MIO_EMM_RSP_STS_FUNC()
static inline uint64_t BDK_MIO_EMM_RSP_STS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_RSP_STS_FUNC(void)
{
    return 0x87e009002060ll;
}

#define typedef_BDK_MIO_EMM_RSP_STS bdk_mio_emm_rsp_sts_t
#define bustype_BDK_MIO_EMM_RSP_STS BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_RSP_STS "MIO_EMM_RSP_STS"
#define device_bar_BDK_MIO_EMM_RSP_STS 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_RSP_STS 0
#define arguments_BDK_MIO_EMM_RSP_STS -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_sample
 *
 * eMMC Sampling Register
 */
union bdk_mio_emm_sample
{
    uint64_t u;
    struct bdk_mio_emm_sample_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_26_63        : 38;
        uint64_t cmd_cnt               : 10; /**< [ 25: 16](R/W) Number of coprocessor-clocks before the eMMC clock rising edge to sample the command pin. */
        uint64_t reserved_10_15        : 6;
        uint64_t dat_cnt               : 10; /**< [  9:  0](R/W) Number of coprocessor-clocks before the eMMC clock edge to sample the data pin. */
#else /* Word 0 - Little Endian */
        uint64_t dat_cnt               : 10; /**< [  9:  0](R/W) Number of coprocessor-clocks before the eMMC clock edge to sample the data pin. */
        uint64_t reserved_10_15        : 6;
        uint64_t cmd_cnt               : 10; /**< [ 25: 16](R/W) Number of coprocessor-clocks before the eMMC clock rising edge to sample the command pin. */
        uint64_t reserved_26_63        : 38;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_sample_s cn; */
};
typedef union bdk_mio_emm_sample bdk_mio_emm_sample_t;

#define BDK_MIO_EMM_SAMPLE BDK_MIO_EMM_SAMPLE_FUNC()
static inline uint64_t BDK_MIO_EMM_SAMPLE_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_SAMPLE_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x87e009002090ll;
    __bdk_csr_fatal("MIO_EMM_SAMPLE", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_SAMPLE bdk_mio_emm_sample_t
#define bustype_BDK_MIO_EMM_SAMPLE BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_SAMPLE "MIO_EMM_SAMPLE"
#define device_bar_BDK_MIO_EMM_SAMPLE 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_SAMPLE 0
#define arguments_BDK_MIO_EMM_SAMPLE -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_sts_mask
 *
 * eMMC Status Mask Register
 */
union bdk_mio_emm_sts_mask
{
    uint64_t u;
    struct bdk_mio_emm_sts_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t sts_msk               : 32; /**< [ 31:  0](R/W) Any bit set in [STS_MSK] causes the corresponding bit in the card status to be
                                                                 considered when computing response bad status. */
#else /* Word 0 - Little Endian */
        uint64_t sts_msk               : 32; /**< [ 31:  0](R/W) Any bit set in [STS_MSK] causes the corresponding bit in the card status to be
                                                                 considered when computing response bad status. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_sts_mask_s cn; */
};
typedef union bdk_mio_emm_sts_mask bdk_mio_emm_sts_mask_t;

#define BDK_MIO_EMM_STS_MASK BDK_MIO_EMM_STS_MASK_FUNC()
static inline uint64_t BDK_MIO_EMM_STS_MASK_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_STS_MASK_FUNC(void)
{
    return 0x87e009002098ll;
}

#define typedef_BDK_MIO_EMM_STS_MASK bdk_mio_emm_sts_mask_t
#define bustype_BDK_MIO_EMM_STS_MASK BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_STS_MASK "MIO_EMM_STS_MASK"
#define device_bar_BDK_MIO_EMM_STS_MASK 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_STS_MASK 0
#define arguments_BDK_MIO_EMM_STS_MASK -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_switch
 *
 * eMMC Operating Mode Switch Register
 * This register allows software to change eMMC related parameters associated
 * with a specific BUS_ID.  The MIO_EMM_MODE() registers contain the current
 * setting for each BUS.  This register is also used to switch the [CLK_HI] and
 * [CLK_LO] settings associated with the common EMMC_CLK.  These settings can only
 * be changed when [BUS_ID] = 0.
 */
union bdk_mio_emm_switch
{
    uint64_t u;
    struct bdk_mio_emm_switch_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W/H) Specifies the eMMC bus ID. */
        uint64_t switch_exe            : 1;  /**< [ 59: 59](R/W/H) When clear, the operating modes are updated directly without performing any
                                                                 SWITCH operations. This allows software to perform the SWITCH operations manually, then
                                                                 update the hardware.

                                                                 Software writes this bit to a 1 to indicate that hardware should perform the necessary
                                                                 SWITCH operations.

                                                                 * First, the power class switch is performed. If it fails,
                                                                 [SWITCH_ERR0] is set and the remaining SWITCH operations are not
                                                                 performed. If it succeeds, [POWER_CLASS] is updated and the HS_TIMING switch is
                                                                 performed.

                                                                 * If the HS_TIMING switch fails, [SWITCH_ERR1] is set and the remaining SWITCH operations
                                                                 are not performed. If it succeeds, [HS_TIMING] is updated and the BUS_WIDTH switch
                                                                 operation is performed.

                                                                 * If the BUS_WIDTH switch operation fails, [SWITCH_ERR2] is set. If it succeeds, the
                                                                 BUS_WITDH is updated.

                                                                 Changes to CLK_HI and CLK_LO are discarded if any MIO_EMM_INT[SWITCH_ERR] occurs. */
        uint64_t switch_err0           : 1;  /**< [ 58: 58](RO/H) Error encountered while performing POWER_CLASS switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err1           : 1;  /**< [ 57: 57](RO/H) Error encountered while performing HS_TIMING switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err2           : 1;  /**< [ 56: 56](RO/H) Error encountered while performing BUS_WIDTH switch. See MIO_EMM_RSP_STS. */
        uint64_t reserved_51_55        : 5;
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](R/W) Requested update to HS400_TIMING. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](R/W) Requested update to HS200_TIMING. */
        uint64_t hs_timing             : 1;  /**< [ 48: 48](R/W) Requested update to HS_TIMING. */
        uint64_t reserved_43_47        : 5;
        uint64_t bus_width             : 3;  /**< [ 42: 40](R/W) Requested update to BUS_WIDTH. */
        uint64_t reserved_37_39        : 3;
        uint64_t clk_swap              : 1;  /**< [ 36: 36](R/W) Data clock edge swap. When one, swap the data captured on the positive and
                                                                 negative edges of the emmc clock. It should be only used when [BUS_WIDTH]
                                                                 indicates DDR Mode and only if fixed data pattern indicates data has been
                                                                 exchanged. Outgoing command and data bits are not affected by this field. For
                                                                 diagnostic use only. */
        uint64_t power_class           : 4;  /**< [ 35: 32](R/W) Requested update to POWER_CLASS. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](R/W) Requested update to CLK_HI. */
        uint64_t clk_lo                : 16; /**< [ 15:  0](R/W) Requested update to CLK_LO. */
#else /* Word 0 - Little Endian */
        uint64_t clk_lo                : 16; /**< [ 15:  0](R/W) Requested update to CLK_LO. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](R/W) Requested update to CLK_HI. */
        uint64_t power_class           : 4;  /**< [ 35: 32](R/W) Requested update to POWER_CLASS. */
        uint64_t clk_swap              : 1;  /**< [ 36: 36](R/W) Data clock edge swap. When one, swap the data captured on the positive and
                                                                 negative edges of the emmc clock. It should be only used when [BUS_WIDTH]
                                                                 indicates DDR Mode and only if fixed data pattern indicates data has been
                                                                 exchanged. Outgoing command and data bits are not affected by this field. For
                                                                 diagnostic use only. */
        uint64_t reserved_37_39        : 3;
        uint64_t bus_width             : 3;  /**< [ 42: 40](R/W) Requested update to BUS_WIDTH. */
        uint64_t reserved_43_47        : 5;
        uint64_t hs_timing             : 1;  /**< [ 48: 48](R/W) Requested update to HS_TIMING. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](R/W) Requested update to HS200_TIMING. */
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](R/W) Requested update to HS400_TIMING. */
        uint64_t reserved_51_55        : 5;
        uint64_t switch_err2           : 1;  /**< [ 56: 56](RO/H) Error encountered while performing BUS_WIDTH switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err1           : 1;  /**< [ 57: 57](RO/H) Error encountered while performing HS_TIMING switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err0           : 1;  /**< [ 58: 58](RO/H) Error encountered while performing POWER_CLASS switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_exe            : 1;  /**< [ 59: 59](R/W/H) When clear, the operating modes are updated directly without performing any
                                                                 SWITCH operations. This allows software to perform the SWITCH operations manually, then
                                                                 update the hardware.

                                                                 Software writes this bit to a 1 to indicate that hardware should perform the necessary
                                                                 SWITCH operations.

                                                                 * First, the power class switch is performed. If it fails,
                                                                 [SWITCH_ERR0] is set and the remaining SWITCH operations are not
                                                                 performed. If it succeeds, [POWER_CLASS] is updated and the HS_TIMING switch is
                                                                 performed.

                                                                 * If the HS_TIMING switch fails, [SWITCH_ERR1] is set and the remaining SWITCH operations
                                                                 are not performed. If it succeeds, [HS_TIMING] is updated and the BUS_WIDTH switch
                                                                 operation is performed.

                                                                 * If the BUS_WIDTH switch operation fails, [SWITCH_ERR2] is set. If it succeeds, the
                                                                 BUS_WITDH is updated.

                                                                 Changes to CLK_HI and CLK_LO are discarded if any MIO_EMM_INT[SWITCH_ERR] occurs. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W/H) Specifies the eMMC bus ID. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } s;
    struct bdk_mio_emm_switch_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W/H) Specifies the eMMC bus ID. */
        uint64_t switch_exe            : 1;  /**< [ 59: 59](R/W/H) When clear, the operating modes are updated directly without performing any
                                                                 SWITCH operations. This allows software to perform the SWITCH operations manually, then
                                                                 update the hardware.

                                                                 Software writes this bit to a 1 to indicate that hardware should perform the necessary
                                                                 SWITCH operations.

                                                                 * First, the power class switch is performed. If it fails,
                                                                 [SWITCH_ERR0] is set and the remaining SWITCH operations are not
                                                                 performed. If it succeeds, [POWER_CLASS] is updated and the HS_TIMING switch is
                                                                 performed.

                                                                 * If the HS_TIMING switch fails, [SWITCH_ERR1] is set and the remaining SWITCH operations
                                                                 are not performed. If it succeeds, [HS_TIMING] is updated and the BUS_WIDTH switch
                                                                 operation is performed.

                                                                 * If the BUS_WIDTH switch operation fails, [SWITCH_ERR2] is set. If it succeeds, the
                                                                 BUS_WITDH is updated.

                                                                 Changes to CLK_HI and CLK_LO are discarded if any MIO_EMM_INT[SWITCH_ERR] occurs. */
        uint64_t switch_err0           : 1;  /**< [ 58: 58](RO/H) Error encountered while performing POWER_CLASS switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err1           : 1;  /**< [ 57: 57](RO/H) Error encountered while performing HS_TIMING switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err2           : 1;  /**< [ 56: 56](RO/H) Error encountered while performing BUS_WIDTH switch. See MIO_EMM_RSP_STS. */
        uint64_t reserved_49_55        : 7;
        uint64_t hs_timing             : 1;  /**< [ 48: 48](R/W) Requested update to HS_TIMING. */
        uint64_t reserved_43_47        : 5;
        uint64_t bus_width             : 3;  /**< [ 42: 40](R/W) Requested update to BUS_WIDTH. */
        uint64_t reserved_36_39        : 4;
        uint64_t power_class           : 4;  /**< [ 35: 32](R/W) Requested update to POWER_CLASS. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](R/W) Requested update to CLK_HI. */
        uint64_t clk_lo                : 16; /**< [ 15:  0](R/W) Requested update to CLK_LO. */
#else /* Word 0 - Little Endian */
        uint64_t clk_lo                : 16; /**< [ 15:  0](R/W) Requested update to CLK_LO. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](R/W) Requested update to CLK_HI. */
        uint64_t power_class           : 4;  /**< [ 35: 32](R/W) Requested update to POWER_CLASS. */
        uint64_t reserved_36_39        : 4;
        uint64_t bus_width             : 3;  /**< [ 42: 40](R/W) Requested update to BUS_WIDTH. */
        uint64_t reserved_43_47        : 5;
        uint64_t hs_timing             : 1;  /**< [ 48: 48](R/W) Requested update to HS_TIMING. */
        uint64_t reserved_49_55        : 7;
        uint64_t switch_err2           : 1;  /**< [ 56: 56](RO/H) Error encountered while performing BUS_WIDTH switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err1           : 1;  /**< [ 57: 57](RO/H) Error encountered while performing HS_TIMING switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err0           : 1;  /**< [ 58: 58](RO/H) Error encountered while performing POWER_CLASS switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_exe            : 1;  /**< [ 59: 59](R/W/H) When clear, the operating modes are updated directly without performing any
                                                                 SWITCH operations. This allows software to perform the SWITCH operations manually, then
                                                                 update the hardware.

                                                                 Software writes this bit to a 1 to indicate that hardware should perform the necessary
                                                                 SWITCH operations.

                                                                 * First, the power class switch is performed. If it fails,
                                                                 [SWITCH_ERR0] is set and the remaining SWITCH operations are not
                                                                 performed. If it succeeds, [POWER_CLASS] is updated and the HS_TIMING switch is
                                                                 performed.

                                                                 * If the HS_TIMING switch fails, [SWITCH_ERR1] is set and the remaining SWITCH operations
                                                                 are not performed. If it succeeds, [HS_TIMING] is updated and the BUS_WIDTH switch
                                                                 operation is performed.

                                                                 * If the BUS_WIDTH switch operation fails, [SWITCH_ERR2] is set. If it succeeds, the
                                                                 BUS_WITDH is updated.

                                                                 Changes to CLK_HI and CLK_LO are discarded if any MIO_EMM_INT[SWITCH_ERR] occurs. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W/H) Specifies the eMMC bus ID. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_mio_emm_switch_s cn9; */
    struct bdk_mio_emm_switch_cn96xxp1
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W/H) Specifies the eMMC bus ID. */
        uint64_t switch_exe            : 1;  /**< [ 59: 59](R/W/H) When clear, the operating modes are updated directly without performing any
                                                                 SWITCH operations. This allows software to perform the SWITCH operations manually, then
                                                                 update the hardware.

                                                                 Software writes this bit to a 1 to indicate that hardware should perform the necessary
                                                                 SWITCH operations.

                                                                 * First, the power class switch is performed. If it fails,
                                                                 [SWITCH_ERR0] is set and the remaining SWITCH operations are not
                                                                 performed. If it succeeds, [POWER_CLASS] is updated and the HS_TIMING switch is
                                                                 performed.

                                                                 * If the HS_TIMING switch fails, [SWITCH_ERR1] is set and the remaining SWITCH operations
                                                                 are not performed. If it succeeds, [HS_TIMING] is updated and the BUS_WIDTH switch
                                                                 operation is performed.

                                                                 * If the BUS_WIDTH switch operation fails, [SWITCH_ERR2] is set. If it succeeds, the
                                                                 BUS_WITDH is updated.

                                                                 Changes to CLK_HI and CLK_LO are discarded if any MIO_EMM_INT[SWITCH_ERR] occurs. */
        uint64_t switch_err0           : 1;  /**< [ 58: 58](RO/H) Error encountered while performing POWER_CLASS switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err1           : 1;  /**< [ 57: 57](RO/H) Error encountered while performing HS_TIMING switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err2           : 1;  /**< [ 56: 56](RO/H) Error encountered while performing BUS_WIDTH switch. See MIO_EMM_RSP_STS. */
        uint64_t reserved_51_55        : 5;
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](R/W) Requested update to HS400_TIMING. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](R/W) Requested update to HS200_TIMING. */
        uint64_t hs_timing             : 1;  /**< [ 48: 48](R/W) Requested update to HS_TIMING. */
        uint64_t reserved_43_47        : 5;
        uint64_t bus_width             : 3;  /**< [ 42: 40](R/W) Requested update to BUS_WIDTH. */
        uint64_t reserved_36_39        : 4;
        uint64_t power_class           : 4;  /**< [ 35: 32](R/W) Requested update to POWER_CLASS. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](R/W) Requested update to CLK_HI. */
        uint64_t clk_lo                : 16; /**< [ 15:  0](R/W) Requested update to CLK_LO. */
#else /* Word 0 - Little Endian */
        uint64_t clk_lo                : 16; /**< [ 15:  0](R/W) Requested update to CLK_LO. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](R/W) Requested update to CLK_HI. */
        uint64_t power_class           : 4;  /**< [ 35: 32](R/W) Requested update to POWER_CLASS. */
        uint64_t reserved_36_39        : 4;
        uint64_t bus_width             : 3;  /**< [ 42: 40](R/W) Requested update to BUS_WIDTH. */
        uint64_t reserved_43_47        : 5;
        uint64_t hs_timing             : 1;  /**< [ 48: 48](R/W) Requested update to HS_TIMING. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](R/W) Requested update to HS200_TIMING. */
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](R/W) Requested update to HS400_TIMING. */
        uint64_t reserved_51_55        : 5;
        uint64_t switch_err2           : 1;  /**< [ 56: 56](RO/H) Error encountered while performing BUS_WIDTH switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err1           : 1;  /**< [ 57: 57](RO/H) Error encountered while performing HS_TIMING switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err0           : 1;  /**< [ 58: 58](RO/H) Error encountered while performing POWER_CLASS switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_exe            : 1;  /**< [ 59: 59](R/W/H) When clear, the operating modes are updated directly without performing any
                                                                 SWITCH operations. This allows software to perform the SWITCH operations manually, then
                                                                 update the hardware.

                                                                 Software writes this bit to a 1 to indicate that hardware should perform the necessary
                                                                 SWITCH operations.

                                                                 * First, the power class switch is performed. If it fails,
                                                                 [SWITCH_ERR0] is set and the remaining SWITCH operations are not
                                                                 performed. If it succeeds, [POWER_CLASS] is updated and the HS_TIMING switch is
                                                                 performed.

                                                                 * If the HS_TIMING switch fails, [SWITCH_ERR1] is set and the remaining SWITCH operations
                                                                 are not performed. If it succeeds, [HS_TIMING] is updated and the BUS_WIDTH switch
                                                                 operation is performed.

                                                                 * If the BUS_WIDTH switch operation fails, [SWITCH_ERR2] is set. If it succeeds, the
                                                                 BUS_WITDH is updated.

                                                                 Changes to CLK_HI and CLK_LO are discarded if any MIO_EMM_INT[SWITCH_ERR] occurs. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W/H) Specifies the eMMC bus ID. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } cn96xxp1;
    struct bdk_mio_emm_switch_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_62_63        : 2;
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W/H) Specifies the eMMC bus ID. */
        uint64_t switch_exe            : 1;  /**< [ 59: 59](R/W/H) When clear, the operating modes are updated directly without performing any
                                                                 SWITCH operations. This allows software to perform the SWITCH operations manually, then
                                                                 update the hardware.

                                                                 Software writes this bit to a 1 to indicate that hardware should perform the necessary
                                                                 SWITCH operations.

                                                                 * First, the power class switch is performed. If it fails,
                                                                 [SWITCH_ERR0] is set and the remaining SWITCH operations are not
                                                                 performed. If it succeeds, [POWER_CLASS] is updated and the BUS_WIDTH switch is
                                                                 performed.

                                                                 * If the BUS_WIDTH switch operation fails, [SWITCH_ERR2] is set and the remaining
                                                                 SWITCH operations are not performed. If it succeeds, the BUS_WIDTH is updated and
                                                                 the HS_TIMING switch is preformed.

                                                                 * If the HS_TIMING switch fails, [SWITCH_ERR1] is set. If it succeeds the HS_TIMING,
                                                                 HS200_TIMING and HS400_TIMING fields are updated and any CLK updates are preformed.

                                                                 Changes to CLK_HI and CLK_LO are discarded if any MIO_EMM_INT[SWITCH_ERR] occurs. */
        uint64_t switch_err0           : 1;  /**< [ 58: 58](RO/H) Error encountered while performing POWER_CLASS switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err1           : 1;  /**< [ 57: 57](RO/H) Error encountered while performing HS_TIMING switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err2           : 1;  /**< [ 56: 56](RO/H) Error encountered while performing BUS_WIDTH switch. See MIO_EMM_RSP_STS. */
        uint64_t reserved_51_55        : 5;
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](R/W) Requested update to HS400_TIMING. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](R/W) Requested update to HS200_TIMING. */
        uint64_t hs_timing             : 1;  /**< [ 48: 48](R/W) Requested update to HS_TIMING. */
        uint64_t reserved_43_47        : 5;
        uint64_t bus_width             : 3;  /**< [ 42: 40](R/W) Requested update to BUS_WIDTH. */
        uint64_t reserved_37_39        : 3;
        uint64_t clk_swap              : 1;  /**< [ 36: 36](R/W) Data clock edge swap. When one, swap the data captured on the positive and
                                                                 negative edges of the emmc clock. It should be only used when [BUS_WIDTH]
                                                                 indicates DDR Mode and only if fixed data pattern indicates data has been
                                                                 exchanged. Outgoing command and data bits are not affected by this field. For
                                                                 diagnostic use only. */
        uint64_t power_class           : 4;  /**< [ 35: 32](R/W) Requested update to POWER_CLASS. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](R/W) Requested update to CLK_HI. */
        uint64_t clk_lo                : 16; /**< [ 15:  0](R/W) Requested update to CLK_LO. */
#else /* Word 0 - Little Endian */
        uint64_t clk_lo                : 16; /**< [ 15:  0](R/W) Requested update to CLK_LO. */
        uint64_t clk_hi                : 16; /**< [ 31: 16](R/W) Requested update to CLK_HI. */
        uint64_t power_class           : 4;  /**< [ 35: 32](R/W) Requested update to POWER_CLASS. */
        uint64_t clk_swap              : 1;  /**< [ 36: 36](R/W) Data clock edge swap. When one, swap the data captured on the positive and
                                                                 negative edges of the emmc clock. It should be only used when [BUS_WIDTH]
                                                                 indicates DDR Mode and only if fixed data pattern indicates data has been
                                                                 exchanged. Outgoing command and data bits are not affected by this field. For
                                                                 diagnostic use only. */
        uint64_t reserved_37_39        : 3;
        uint64_t bus_width             : 3;  /**< [ 42: 40](R/W) Requested update to BUS_WIDTH. */
        uint64_t reserved_43_47        : 5;
        uint64_t hs_timing             : 1;  /**< [ 48: 48](R/W) Requested update to HS_TIMING. */
        uint64_t hs200_timing          : 1;  /**< [ 49: 49](R/W) Requested update to HS200_TIMING. */
        uint64_t hs400_timing          : 1;  /**< [ 50: 50](R/W) Requested update to HS400_TIMING. */
        uint64_t reserved_51_55        : 5;
        uint64_t switch_err2           : 1;  /**< [ 56: 56](RO/H) Error encountered while performing BUS_WIDTH switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err1           : 1;  /**< [ 57: 57](RO/H) Error encountered while performing HS_TIMING switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_err0           : 1;  /**< [ 58: 58](RO/H) Error encountered while performing POWER_CLASS switch. See MIO_EMM_RSP_STS. */
        uint64_t switch_exe            : 1;  /**< [ 59: 59](R/W/H) When clear, the operating modes are updated directly without performing any
                                                                 SWITCH operations. This allows software to perform the SWITCH operations manually, then
                                                                 update the hardware.

                                                                 Software writes this bit to a 1 to indicate that hardware should perform the necessary
                                                                 SWITCH operations.

                                                                 * First, the power class switch is performed. If it fails,
                                                                 [SWITCH_ERR0] is set and the remaining SWITCH operations are not
                                                                 performed. If it succeeds, [POWER_CLASS] is updated and the BUS_WIDTH switch is
                                                                 performed.

                                                                 * If the BUS_WIDTH switch operation fails, [SWITCH_ERR2] is set and the remaining
                                                                 SWITCH operations are not performed. If it succeeds, the BUS_WIDTH is updated and
                                                                 the HS_TIMING switch is preformed.

                                                                 * If the HS_TIMING switch fails, [SWITCH_ERR1] is set. If it succeeds the HS_TIMING,
                                                                 HS200_TIMING and HS400_TIMING fields are updated and any CLK updates are preformed.

                                                                 Changes to CLK_HI and CLK_LO are discarded if any MIO_EMM_INT[SWITCH_ERR] occurs. */
        uint64_t bus_id                : 2;  /**< [ 61: 60](R/W/H) Specifies the eMMC bus ID. */
        uint64_t reserved_62_63        : 2;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_mio_emm_switch_cn96xxp3 cn98xx; */
    /* struct bdk_mio_emm_switch_cn96xxp3 cnf95xx; */
    /* struct bdk_mio_emm_switch_cn96xxp3 loki; */
};
typedef union bdk_mio_emm_switch bdk_mio_emm_switch_t;

#define BDK_MIO_EMM_SWITCH BDK_MIO_EMM_SWITCH_FUNC()
static inline uint64_t BDK_MIO_EMM_SWITCH_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_SWITCH_FUNC(void)
{
    return 0x87e009002048ll;
}

#define typedef_BDK_MIO_EMM_SWITCH bdk_mio_emm_switch_t
#define bustype_BDK_MIO_EMM_SWITCH BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_SWITCH "MIO_EMM_SWITCH"
#define device_bar_BDK_MIO_EMM_SWITCH 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_SWITCH 0
#define arguments_BDK_MIO_EMM_SWITCH -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_tap
 *
 * eMMC TAP Delay Register
 * This register indicates the delay line characteristics.
 */
union bdk_mio_emm_tap
{
    uint64_t u;
    struct bdk_mio_emm_tap_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t delay                 : 8;  /**< [  7:  0](RO) Tap estimate. The estimate in number of 100 MHz reference clocks for 512 tap
                                                                 delays. The delay value should be multiplied by 10 ns and then divided by 512
                                                                 to determine the estimated delay in fractions of a ns. The nominal value is 125
                                                                 ps per tap.

                                                                 A value of 0x0 indicates calibration has not completed.  After setting
                                                                 MIO_EMM_CALB[START], it will take approximately 3 us to complete. */
#else /* Word 0 - Little Endian */
        uint64_t delay                 : 8;  /**< [  7:  0](RO) Tap estimate. The estimate in number of 100 MHz reference clocks for 512 tap
                                                                 delays. The delay value should be multiplied by 10 ns and then divided by 512
                                                                 to determine the estimated delay in fractions of a ns. The nominal value is 125
                                                                 ps per tap.

                                                                 A value of 0x0 indicates calibration has not completed.  After setting
                                                                 MIO_EMM_CALB[START], it will take approximately 3 us to complete. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_tap_s cn; */
};
typedef union bdk_mio_emm_tap bdk_mio_emm_tap_t;

#define BDK_MIO_EMM_TAP BDK_MIO_EMM_TAP_FUNC()
static inline uint64_t BDK_MIO_EMM_TAP_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_TAP_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e0090020c8ll;
    __bdk_csr_fatal("MIO_EMM_TAP", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_TAP bdk_mio_emm_tap_t
#define bustype_BDK_MIO_EMM_TAP BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_TAP "MIO_EMM_TAP"
#define device_bar_BDK_MIO_EMM_TAP 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_TAP 0
#define arguments_BDK_MIO_EMM_TAP -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_timing
 *
 * eMMC Timing Register
 * This register determines the number of tap delays the
 * EMM_DAT, EMM_DS, and EMM_CMD lines are transmitted or
 * received in relation to EMM_CLK.
 * These values should only be changed when the eMMC bus is idle.
 */
union bdk_mio_emm_timing
{
    uint64_t u;
    struct bdk_mio_emm_timing_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_54_63        : 10;
        uint64_t cmd_in_tap            : 6;  /**< [ 53: 48](R/W) EMM_CMD sample delay. */
        uint64_t reserved_38_47        : 10;
        uint64_t cmd_out_tap           : 6;  /**< [ 37: 32](R/W) EMM_CMD hold time from rising edge of EMMC_CLK.
                                                                 _ Typically 3.0 ns at frequencies \< 26 MHz.
                                                                 _ Typically 3.0 ns at frequencies \<= 52 MHz SDR.
                                                                 _ Typically 2.5 ns at frequencies \<= 52 MHz DDR.
                                                                 _ Typically 0.8 ns at frequencies \> 52 MHz SDR.
                                                                 _ Typically 0.4 ns at frequencies \> 52 MHz DDR. */
        uint64_t reserved_22_31        : 10;
        uint64_t data_in_tap           : 6;  /**< [ 21: 16](R/W) EMM_DAT/EMM_DS sample delay. */
        uint64_t reserved_6_15         : 10;
        uint64_t data_out_tap          : 6;  /**< [  5:  0](R/W) EMM_DAT hold time from either edge of EMMC_CLK.
                                                                 Typically set to 0 for single data rate since data is output
                                                                 on falling edge of EMMC_CLK.
                                                                 For DDR:
                                                                 _ Typically 3.0 ns at frequencies \< 26 MHz.
                                                                 _ Typically 3.0 ns at frequencies \<= 52 MHz SDR.
                                                                 _ Typically 2.5 ns at frequencies \<= 52 MHz DDR.
                                                                 _ Typically 0.8 ns at frequencies \> 52 MHz SDR.
                                                                 _ Typically 0.4 ns at frequencies \> 52 MHz DDR. */
#else /* Word 0 - Little Endian */
        uint64_t data_out_tap          : 6;  /**< [  5:  0](R/W) EMM_DAT hold time from either edge of EMMC_CLK.
                                                                 Typically set to 0 for single data rate since data is output
                                                                 on falling edge of EMMC_CLK.
                                                                 For DDR:
                                                                 _ Typically 3.0 ns at frequencies \< 26 MHz.
                                                                 _ Typically 3.0 ns at frequencies \<= 52 MHz SDR.
                                                                 _ Typically 2.5 ns at frequencies \<= 52 MHz DDR.
                                                                 _ Typically 0.8 ns at frequencies \> 52 MHz SDR.
                                                                 _ Typically 0.4 ns at frequencies \> 52 MHz DDR. */
        uint64_t reserved_6_15         : 10;
        uint64_t data_in_tap           : 6;  /**< [ 21: 16](R/W) EMM_DAT/EMM_DS sample delay. */
        uint64_t reserved_22_31        : 10;
        uint64_t cmd_out_tap           : 6;  /**< [ 37: 32](R/W) EMM_CMD hold time from rising edge of EMMC_CLK.
                                                                 _ Typically 3.0 ns at frequencies \< 26 MHz.
                                                                 _ Typically 3.0 ns at frequencies \<= 52 MHz SDR.
                                                                 _ Typically 2.5 ns at frequencies \<= 52 MHz DDR.
                                                                 _ Typically 0.8 ns at frequencies \> 52 MHz SDR.
                                                                 _ Typically 0.4 ns at frequencies \> 52 MHz DDR. */
        uint64_t reserved_38_47        : 10;
        uint64_t cmd_in_tap            : 6;  /**< [ 53: 48](R/W) EMM_CMD sample delay. */
        uint64_t reserved_54_63        : 10;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_timing_s cn; */
};
typedef union bdk_mio_emm_timing bdk_mio_emm_timing_t;

#define BDK_MIO_EMM_TIMING BDK_MIO_EMM_TIMING_FUNC()
static inline uint64_t BDK_MIO_EMM_TIMING_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_TIMING_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x87e0090020d0ll;
    __bdk_csr_fatal("MIO_EMM_TIMING", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_MIO_EMM_TIMING bdk_mio_emm_timing_t
#define bustype_BDK_MIO_EMM_TIMING BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_TIMING "MIO_EMM_TIMING"
#define device_bar_BDK_MIO_EMM_TIMING 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_TIMING 0
#define arguments_BDK_MIO_EMM_TIMING -1,-1,-1,-1

/**
 * Register (RSL) mio_emm_wdog
 *
 * eMMC Watchdog Register
 */
union bdk_mio_emm_wdog
{
    uint64_t u;
    struct bdk_mio_emm_wdog_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_26_63        : 38;
        uint64_t clk_cnt               : 26; /**< [ 25:  0](R/W) Maximum number of clock cycles to wait for the card to return a response, read data, or
                                                                 the 3-bit CRC status token following write data. The following timeouts are detected:

                                                                 Expected response to a command doesn't occur causing MIO_EMM_RSP_STS[RSP_TIMEOUT].

                                                                 On a read command, expected data isn't returned causing MIO_EMM_RSP_STS[BLK_TIMEOUT].

                                                                 On a multi read command, expected data isn't returned causing
                                                                 MIO_EMM_RSP_STS[BLK_TIMEOUT].

                                                                 On a write command, expected token to a write block isn't received causing
                                                                 MIO_EMM_RSP_STS[BLK_TIMEOUT].

                                                                 If a stop command is issued by the hardware and no response is returned causing
                                                                 MIO_EMM_RSP_STS[STP_TIMEOUT].

                                                                 Issues that this timeout doesn't cover are stalls induced by the card which are
                                                                 not limited by the specifications.
                                                                 For example, when a write multi command is issued to the card and a block (not the last)
                                                                 is transferred, the card can "stall" CNXXXX by forcing EMMC_DAT\<0\> low for as long as
                                                                 it wants to free up buffer space.

                                                                 The second case is when the last block of a write or multi write is being transferred and
                                                                 the card elects to perform some background tasks. The same stall mechanism with
                                                                 EMMC_DAT\<0\> is used, but this can last for an extended time period. */
#else /* Word 0 - Little Endian */
        uint64_t clk_cnt               : 26; /**< [ 25:  0](R/W) Maximum number of clock cycles to wait for the card to return a response, read data, or
                                                                 the 3-bit CRC status token following write data. The following timeouts are detected:

                                                                 Expected response to a command doesn't occur causing MIO_EMM_RSP_STS[RSP_TIMEOUT].

                                                                 On a read command, expected data isn't returned causing MIO_EMM_RSP_STS[BLK_TIMEOUT].

                                                                 On a multi read command, expected data isn't returned causing
                                                                 MIO_EMM_RSP_STS[BLK_TIMEOUT].

                                                                 On a write command, expected token to a write block isn't received causing
                                                                 MIO_EMM_RSP_STS[BLK_TIMEOUT].

                                                                 If a stop command is issued by the hardware and no response is returned causing
                                                                 MIO_EMM_RSP_STS[STP_TIMEOUT].

                                                                 Issues that this timeout doesn't cover are stalls induced by the card which are
                                                                 not limited by the specifications.
                                                                 For example, when a write multi command is issued to the card and a block (not the last)
                                                                 is transferred, the card can "stall" CNXXXX by forcing EMMC_DAT\<0\> low for as long as
                                                                 it wants to free up buffer space.

                                                                 The second case is when the last block of a write or multi write is being transferred and
                                                                 the card elects to perform some background tasks. The same stall mechanism with
                                                                 EMMC_DAT\<0\> is used, but this can last for an extended time period. */
        uint64_t reserved_26_63        : 38;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mio_emm_wdog_s cn; */
};
typedef union bdk_mio_emm_wdog bdk_mio_emm_wdog_t;

#define BDK_MIO_EMM_WDOG BDK_MIO_EMM_WDOG_FUNC()
static inline uint64_t BDK_MIO_EMM_WDOG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MIO_EMM_WDOG_FUNC(void)
{
    return 0x87e009002088ll;
}

#define typedef_BDK_MIO_EMM_WDOG bdk_mio_emm_wdog_t
#define bustype_BDK_MIO_EMM_WDOG BDK_CSR_TYPE_RSL
#define basename_BDK_MIO_EMM_WDOG "MIO_EMM_WDOG"
#define device_bar_BDK_MIO_EMM_WDOG 0x0 /* PF_BAR0 */
#define busnum_BDK_MIO_EMM_WDOG 0
#define arguments_BDK_MIO_EMM_WDOG -1,-1,-1,-1

#endif /* __BDK_CSRS_MIO_EMM_H__ */
