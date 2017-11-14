#ifndef __BDK_CSRS_AVS_H__
#define __BDK_CSRS_AVS_H__
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
 * Cavium AVS.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration avs_bar_e
 *
 * AVS Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_AVS_BAR_E_AVS_PF_BAR0 (0x80a000000000ll)
#define BDK_AVS_BAR_E_AVS_PF_BAR0_SIZE 0x10000ull
#define BDK_AVS_BAR_E_AVS_PF_BAR4 (0x80a000f00000ll)
#define BDK_AVS_BAR_E_AVS_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration avs_bus_status_e
 *
 * AVS AVSBus Status Enumeration
 * Bit positions of the data fields used in a read or write of the \<AVSBus_Status\>.
 * Note this is different than the format used by the \<StatusResp\>.
 */
#define BDK_AVS_BUS_STATUS_E_IOUT_OC_WARNING (0xe)
#define BDK_AVS_BUS_STATUS_E_IOUT_OT_WARNING (0xc)
#define BDK_AVS_BUS_STATUS_E_POUT_OP_WARNING (0xb)
#define BDK_AVS_BUS_STATUS_E_VDONE (0xf)
#define BDK_AVS_BUS_STATUS_E_VOUT_UV_WARNING (0xd)

/**
 * Enumeration avs_cmd_e
 *
 * AVS Command Enumeration
 * Enumerates the master frame Cmd field to send on next AVS_STS[START].
 */
#define BDK_AVS_CMD_E_READ (3)
#define BDK_AVS_CMD_E_WRITE_AND_COMMIT (0)
#define BDK_AVS_CMD_E_WRITE_AND_HOLD (1)

/**
 * Enumeration avs_cmddatatype_e
 *
 * AVS Command Group Enumeration
 * Enumerates the type of data to which the Cmd applies for CmdGroup=STD.
 */
#define BDK_AVS_CMDDATATYPE_E_AVSBUS_STATUS (0xe)
#define BDK_AVS_CMDDATATYPE_E_AVSBUS_VERSION (0xf)
#define BDK_AVS_CMDDATATYPE_E_RAIL_CURRENT (2)
#define BDK_AVS_CMDDATATYPE_E_RAIL_POWER_MODE (5)
#define BDK_AVS_CMDDATATYPE_E_RAIL_TEMPERATURE (3)
#define BDK_AVS_CMDDATATYPE_E_RESET_RAIL_VOLTAGE_TO_DEFAULT (4)
#define BDK_AVS_CMDDATATYPE_E_TARGET_RAIL_VOLTAGE (0)
#define BDK_AVS_CMDDATATYPE_E_TARGET_RAIL_VOUT_TRANSITION_RATE (1)

/**
 * Enumeration avs_cmdgroup_e
 *
 * AVS Command Group Enumeration
 * Enumerates the master frame CmdGroup to send on next AVS_STS[START].
 */
#define BDK_AVS_CMDGROUP_E_MFG_SPECIFIC (1)
#define BDK_AVS_CMDGROUP_E_STD (0)

/**
 * Enumeration avs_int_vec_e
 *
 * AVS MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_AVS_INT_VEC_E_INTS (0)

/**
 * Enumeration avs_slaveack_e
 *
 * AVS SlaveAck Enumeration
 * Received response frame's SlaveACK field.
 */
#define BDK_AVS_SLAVEACK_E_ACTION_TAKEN (0)
#define BDK_AVS_SLAVEACK_E_BAD_CRC (2)
#define BDK_AVS_SLAVEACK_E_GOOD_CMD_NO_ACTION (1)
#define BDK_AVS_SLAVEACK_E_GOOD_CRC_BAD_CMD (3)

/**
 * Enumeration avs_statusresp_e
 *
 * AVS Status Response Bit Number Enumeration
 * Enumerates the bit positions of the bits in AVS_SDATA[STATUSRESP] received after
 * every transaction.
 * Note this is different than the data returned by an AVSBus_Status read.
 */
#define BDK_AVS_STATUSRESP_E_AVSBUS_CONTROL (2)
#define BDK_AVS_STATUSRESP_E_STATUS_ALERT (3)
#define BDK_AVS_STATUSRESP_E_VDONE (4)

/**
 * Register (NCB) avs_cfg
 *
 * AVS Configuration Register
 * This register provides configuration for the AVS interface.
 */
union bdk_avs_cfg
{
    uint64_t u;
    struct bdk_avs_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t clkdiv                : 13; /**< [ 28: 16](R/W) Clock divisor. Value 0x0 disables the AVS_CLK pin.
                                                                 AVS_CLK = 100 MHz reference clock / (2 * [CLKDIV]).

                                                                 Or, restated,
                                                                 [CLKDIV]  = 100 MHz reference clock / (2 * AVS_CLK). */
        uint64_t reserved_1_15         : 15;
        uint64_t enable                : 1;  /**< [  0:  0](R/W) AVS enable.
                                                                 0 = Pins are tristated.
                                                                 1 = Pins are driven. */
#else /* Word 0 - Little Endian */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) AVS enable.
                                                                 0 = Pins are tristated.
                                                                 1 = Pins are driven. */
        uint64_t reserved_1_15         : 15;
        uint64_t clkdiv                : 13; /**< [ 28: 16](R/W) Clock divisor. Value 0x0 disables the AVS_CLK pin.
                                                                 AVS_CLK = 100 MHz reference clock / (2 * [CLKDIV]).

                                                                 Or, restated,
                                                                 [CLKDIV]  = 100 MHz reference clock / (2 * AVS_CLK). */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_cfg_s cn; */
};
typedef union bdk_avs_cfg bdk_avs_cfg_t;

#define BDK_AVS_CFG BDK_AVS_CFG_FUNC()
static inline uint64_t BDK_AVS_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000000100ll;
    __bdk_csr_fatal("AVS_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_CFG bdk_avs_cfg_t
#define bustype_BDK_AVS_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_CFG "AVS_CFG"
#define device_bar_BDK_AVS_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_CFG 0
#define arguments_BDK_AVS_CFG -1,-1,-1,-1

/**
 * Register (NCB) avs_clken
 *
 * AVS Clock Enable Register
 * This register is to force conditional clock enable.
 */
union bdk_avs_clken
{
    uint64_t u;
    struct bdk_avs_clken_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t clken                 : 1;  /**< [  0:  0](R/W) Force the conditional clocking within AVS to be always on. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clken                 : 1;  /**< [  0:  0](R/W) Force the conditional clocking within AVS to be always on. For diagnostic use only. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_clken_s cn; */
};
typedef union bdk_avs_clken bdk_avs_clken_t;

#define BDK_AVS_CLKEN BDK_AVS_CLKEN_FUNC()
static inline uint64_t BDK_AVS_CLKEN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_CLKEN_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000002080ll;
    __bdk_csr_fatal("AVS_CLKEN", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_CLKEN bdk_avs_clken_t
#define bustype_BDK_AVS_CLKEN BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_CLKEN "AVS_CLKEN"
#define device_bar_BDK_AVS_CLKEN 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_CLKEN 0
#define arguments_BDK_AVS_CLKEN -1,-1,-1,-1

/**
 * Register (NCB) avs_const
 *
 * AVS Constants Register
 * This register contains constants for software discovery.
 */
union bdk_avs_const
{
    uint64_t u;
    struct bdk_avs_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t ver                   : 4;  /**< [  3:  0](RO) AVS version compatible with PMBus 1.3.1. */
#else /* Word 0 - Little Endian */
        uint64_t ver                   : 4;  /**< [  3:  0](RO) AVS version compatible with PMBus 1.3.1. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_const_s cn; */
};
typedef union bdk_avs_const bdk_avs_const_t;

#define BDK_AVS_CONST BDK_AVS_CONST_FUNC()
static inline uint64_t BDK_AVS_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_CONST_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000000000ll;
    __bdk_csr_fatal("AVS_CONST", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_CONST bdk_avs_const_t
#define bustype_BDK_AVS_CONST BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_CONST "AVS_CONST"
#define device_bar_BDK_AVS_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_CONST 0
#define arguments_BDK_AVS_CONST -1,-1,-1,-1

/**
 * Register (NCB) avs_eco
 *
 * INTERNAL: AVS ECO Register
 */
union bdk_avs_eco
{
    uint64_t u;
    struct bdk_avs_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_eco_s cn; */
};
typedef union bdk_avs_eco bdk_avs_eco_t;

#define BDK_AVS_ECO BDK_AVS_ECO_FUNC()
static inline uint64_t BDK_AVS_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_ECO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000000120ll;
    __bdk_csr_fatal("AVS_ECO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_ECO bdk_avs_eco_t
#define bustype_BDK_AVS_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_ECO "AVS_ECO"
#define device_bar_BDK_AVS_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_ECO 0
#define arguments_BDK_AVS_ECO -1,-1,-1,-1

/**
 * Register (NCB) avs_int_ena_w1c
 *
 * AVS Interrupt Enable Clear Register
 * This register clears interrupt enables.
 */
union bdk_avs_int_ena_w1c
{
    uint64_t u;
    struct bdk_avs_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t crc_err               : 1;  /**< [  1:  1](R/W1C) Reads or clears AVS_INT_ENA_W1S[CRC_ERR]. */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C) Reads or clears AVS_INT_ENA_W1S[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C) Reads or clears AVS_INT_ENA_W1S[DONE]. */
        uint64_t crc_err               : 1;  /**< [  1:  1](R/W1C) Reads or clears AVS_INT_ENA_W1S[CRC_ERR]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_int_ena_w1c_s cn; */
};
typedef union bdk_avs_int_ena_w1c bdk_avs_int_ena_w1c_t;

#define BDK_AVS_INT_ENA_W1C BDK_AVS_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_AVS_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_INT_ENA_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000000210ll;
    __bdk_csr_fatal("AVS_INT_ENA_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_INT_ENA_W1C bdk_avs_int_ena_w1c_t
#define bustype_BDK_AVS_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_INT_ENA_W1C "AVS_INT_ENA_W1C"
#define device_bar_BDK_AVS_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_INT_ENA_W1C 0
#define arguments_BDK_AVS_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) avs_int_ena_w1s
 *
 * AVS Interrupt Enable Set Register
 * This register sets interrupt enables.
 */
union bdk_avs_int_ena_w1s
{
    uint64_t u;
    struct bdk_avs_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t crc_err               : 1;  /**< [  1:  1](R/W1S) Enables reporting of AVS_STS[CRC_ERR]. */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S) Enables reporting of AVS_STS[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S) Enables reporting of AVS_STS[DONE]. */
        uint64_t crc_err               : 1;  /**< [  1:  1](R/W1S) Enables reporting of AVS_STS[CRC_ERR]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_int_ena_w1s_s cn; */
};
typedef union bdk_avs_int_ena_w1s bdk_avs_int_ena_w1s_t;

#define BDK_AVS_INT_ENA_W1S BDK_AVS_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_AVS_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_INT_ENA_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000000218ll;
    __bdk_csr_fatal("AVS_INT_ENA_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_INT_ENA_W1S bdk_avs_int_ena_w1s_t
#define bustype_BDK_AVS_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_INT_ENA_W1S "AVS_INT_ENA_W1S"
#define device_bar_BDK_AVS_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_INT_ENA_W1S 0
#define arguments_BDK_AVS_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) avs_io_ctl
 *
 * AVS I/O Control Register
 */
union bdk_avs_io_ctl
{
    uint64_t u;
    struct bdk_avs_io_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t drive                 : 2;  /**< [  3:  2](R/W) AVS bus pin output drive strength.
                                                                 0x0 = 2 mA.
                                                                 0x1 = 4 mA.
                                                                 0x2 = 8 mA.
                                                                 0x3 = 16 mA. */
        uint64_t reserved_1            : 1;
        uint64_t slew                  : 1;  /**< [  0:  0](R/W) AVS bus pins output slew rate control.
                                                                 0 = Low slew rate.
                                                                 1 = High slew rate. */
#else /* Word 0 - Little Endian */
        uint64_t slew                  : 1;  /**< [  0:  0](R/W) AVS bus pins output slew rate control.
                                                                 0 = Low slew rate.
                                                                 1 = High slew rate. */
        uint64_t reserved_1            : 1;
        uint64_t drive                 : 2;  /**< [  3:  2](R/W) AVS bus pin output drive strength.
                                                                 0x0 = 2 mA.
                                                                 0x1 = 4 mA.
                                                                 0x2 = 8 mA.
                                                                 0x3 = 16 mA. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_io_ctl_s cn; */
};
typedef union bdk_avs_io_ctl bdk_avs_io_ctl_t;

#define BDK_AVS_IO_CTL BDK_AVS_IO_CTL_FUNC()
static inline uint64_t BDK_AVS_IO_CTL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_IO_CTL_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000000128ll;
    __bdk_csr_fatal("AVS_IO_CTL", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_IO_CTL bdk_avs_io_ctl_t
#define bustype_BDK_AVS_IO_CTL BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_IO_CTL "AVS_IO_CTL"
#define device_bar_BDK_AVS_IO_CTL 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_IO_CTL 0
#define arguments_BDK_AVS_IO_CTL -1,-1,-1,-1

/**
 * Register (NCB) avs_mdata
 *
 * AVS Master Data Transmitting Register
 * This register contains the data to transmit on the AVS_MDATA signal.
 */
union bdk_avs_mdata
{
    uint64_t u;
    struct bdk_avs_mdata_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t startcode             : 2;  /**< [ 31: 30](R/W) Master frame StartCode field to send on next AVS_STS[START]. For compliance must be 0x1. */
        uint64_t cmd                   : 2;  /**< [ 29: 28](R/W) Master frame Cmd field to send on next AVS_STS[START].
                                                                 Determines the action that the master requires.
                                                                 Values enumerated by AVS_CMD_E */
        uint64_t cmdgroup              : 1;  /**< [ 27: 27](R/W) Master frame CmdGroup field to send on next AVS_STS[START].
                                                                 Values enumerated by AVS_CMDGROUP_E. */
        uint64_t cmddatatype           : 4;  /**< [ 26: 23](R/W) Master frame CmdDataType field to send on next AVS_STS[START].
                                                                 Values enumerated by AVS_CMDDATATYPE_E. */
        uint64_t select                : 4;  /**< [ 22: 19](R/W) Master frame Select field to send on next AVS_STS[START]. */
        uint64_t cmddata               : 16; /**< [ 18:  3](R/W) Master frame CmdData field to send on next AVS_STS[START]. Must be all-ones for reads. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t cmddata               : 16; /**< [ 18:  3](R/W) Master frame CmdData field to send on next AVS_STS[START]. Must be all-ones for reads. */
        uint64_t select                : 4;  /**< [ 22: 19](R/W) Master frame Select field to send on next AVS_STS[START]. */
        uint64_t cmddatatype           : 4;  /**< [ 26: 23](R/W) Master frame CmdDataType field to send on next AVS_STS[START].
                                                                 Values enumerated by AVS_CMDDATATYPE_E. */
        uint64_t cmdgroup              : 1;  /**< [ 27: 27](R/W) Master frame CmdGroup field to send on next AVS_STS[START].
                                                                 Values enumerated by AVS_CMDGROUP_E. */
        uint64_t cmd                   : 2;  /**< [ 29: 28](R/W) Master frame Cmd field to send on next AVS_STS[START].
                                                                 Determines the action that the master requires.
                                                                 Values enumerated by AVS_CMD_E */
        uint64_t startcode             : 2;  /**< [ 31: 30](R/W) Master frame StartCode field to send on next AVS_STS[START]. For compliance must be 0x1. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_mdata_s cn; */
};
typedef union bdk_avs_mdata bdk_avs_mdata_t;

#define BDK_AVS_MDATA BDK_AVS_MDATA_FUNC()
static inline uint64_t BDK_AVS_MDATA_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_MDATA_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000001010ll;
    __bdk_csr_fatal("AVS_MDATA", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_MDATA bdk_avs_mdata_t
#define bustype_BDK_AVS_MDATA BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_MDATA "AVS_MDATA"
#define device_bar_BDK_AVS_MDATA 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_MDATA 0
#define arguments_BDK_AVS_MDATA -1,-1,-1,-1

/**
 * Register (NCB) avs_msix_pba#
 *
 * AVS MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the AVS_INT_VEC_E enumeration.
 */
union bdk_avs_msix_pbax
{
    uint64_t u;
    struct bdk_avs_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated AVS_MSIX_VEC()_CTL, enumerated by AVS_INT_VEC_E. Bits
                                                                 that have no associated AVS_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated AVS_MSIX_VEC()_CTL, enumerated by AVS_INT_VEC_E. Bits
                                                                 that have no associated AVS_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_msix_pbax_s cn; */
};
typedef union bdk_avs_msix_pbax bdk_avs_msix_pbax_t;

static inline uint64_t BDK_AVS_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_MSIX_PBAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x80a000ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("AVS_MSIX_PBAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_AVS_MSIX_PBAX(a) bdk_avs_msix_pbax_t
#define bustype_BDK_AVS_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_MSIX_PBAX(a) "AVS_MSIX_PBAX"
#define device_bar_BDK_AVS_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_AVS_MSIX_PBAX(a) (a)
#define arguments_BDK_AVS_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) avs_msix_vec#_addr
 *
 * AVS MSI-X Vector Table Address Registers
 * This register is the MSI-X vector table, indexed by the AVS_INT_VEC_E enumeration.
 */
union bdk_avs_msix_vecx_addr
{
    uint64_t u;
    struct bdk_avs_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's AVS_MSIX_VEC()_ADDR, AVS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of AVS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_AVS_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's AVS_MSIX_VEC()_ADDR, AVS_MSIX_VEC()_CTL, and corresponding
                                                                 bit of AVS_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_AVS_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_msix_vecx_addr_s cn; */
};
typedef union bdk_avs_msix_vecx_addr bdk_avs_msix_vecx_addr_t;

static inline uint64_t BDK_AVS_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_MSIX_VECX_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x80a000f00000ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("AVS_MSIX_VECX_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_AVS_MSIX_VECX_ADDR(a) bdk_avs_msix_vecx_addr_t
#define bustype_BDK_AVS_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_MSIX_VECX_ADDR(a) "AVS_MSIX_VECX_ADDR"
#define device_bar_BDK_AVS_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_AVS_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_AVS_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) avs_msix_vec#_ctl
 *
 * AVS MSI-X Vector Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the AVS_INT_VEC_E enumeration.
 */
union bdk_avs_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_avs_msix_vecx_ctl_s
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
    /* struct bdk_avs_msix_vecx_ctl_s cn; */
};
typedef union bdk_avs_msix_vecx_ctl bdk_avs_msix_vecx_ctl_t;

static inline uint64_t BDK_AVS_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_MSIX_VECX_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a==0))
        return 0x80a000f00008ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("AVS_MSIX_VECX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_AVS_MSIX_VECX_CTL(a) bdk_avs_msix_vecx_ctl_t
#define bustype_BDK_AVS_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_MSIX_VECX_CTL(a) "AVS_MSIX_VECX_CTL"
#define device_bar_BDK_AVS_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_AVS_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_AVS_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) avs_sdata
 *
 * AVS Slave Data Received Response Register
 * This register contains the data received on the AVS_SDATA signal in response to a
 * master transaction.
 */
union bdk_avs_sdata
{
    uint64_t u;
    struct bdk_avs_sdata_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t slaveack              : 2;  /**< [ 31: 30](RO/H) Received response frame's SlaveACK field. Enumerated by AVS_SLAVEACK_E. */
        uint64_t reserved_29           : 1;
        uint64_t statusresp            : 5;  /**< [ 28: 24](RO/H) Received response frame's Status_Resp field. Bit numbers enumerated by
                                                                 AVS_STATUSRESP_E. */
        uint64_t cmddata               : 16; /**< [ 23:  8](RO/H) Received response frame's CmdData field. */
        uint64_t reserved_3_7          : 5;
        uint64_t crc                   : 3;  /**< [  2:  0](RAZ) Received response frame's CRC field. Software typically ignores this field and uses
                                                                 AVS_STS[CRC_ERR] instead. */
#else /* Word 0 - Little Endian */
        uint64_t crc                   : 3;  /**< [  2:  0](RAZ) Received response frame's CRC field. Software typically ignores this field and uses
                                                                 AVS_STS[CRC_ERR] instead. */
        uint64_t reserved_3_7          : 5;
        uint64_t cmddata               : 16; /**< [ 23:  8](RO/H) Received response frame's CmdData field. */
        uint64_t statusresp            : 5;  /**< [ 28: 24](RO/H) Received response frame's Status_Resp field. Bit numbers enumerated by
                                                                 AVS_STATUSRESP_E. */
        uint64_t reserved_29           : 1;
        uint64_t slaveack              : 2;  /**< [ 31: 30](RO/H) Received response frame's SlaveACK field. Enumerated by AVS_SLAVEACK_E. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_sdata_s cn; */
};
typedef union bdk_avs_sdata bdk_avs_sdata_t;

#define BDK_AVS_SDATA BDK_AVS_SDATA_FUNC()
static inline uint64_t BDK_AVS_SDATA_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_SDATA_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000001020ll;
    __bdk_csr_fatal("AVS_SDATA", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_SDATA bdk_avs_sdata_t
#define bustype_BDK_AVS_SDATA BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_SDATA "AVS_SDATA"
#define device_bar_BDK_AVS_SDATA 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_SDATA 0
#define arguments_BDK_AVS_SDATA -1,-1,-1,-1

/**
 * Register (NCB) avs_sstatus
 *
 * AVS Slave Data Received Status Register
 * This register contains the data received on the AVS_SDATA signal in a status
 * response.
 */
union bdk_avs_sstatus
{
    uint64_t u;
    struct bdk_avs_sstatus_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t prefix                : 2;  /**< [ 31: 30](RO/H) Received status frame's SlaveACK field. */
        uint64_t reserved_29           : 1;
        uint64_t statusresp            : 5;  /**< [ 28: 24](RO/H) Received status frame's Status_Resp field. */
        uint64_t reserved_3_23         : 21;
        uint64_t crc                   : 3;  /**< [  2:  0](RAZ) Received status frame's CRC field. Software typically ignores this field and uses
                                                                 AVS_STS[CRC_ERR] instead. */
#else /* Word 0 - Little Endian */
        uint64_t crc                   : 3;  /**< [  2:  0](RAZ) Received status frame's CRC field. Software typically ignores this field and uses
                                                                 AVS_STS[CRC_ERR] instead. */
        uint64_t reserved_3_23         : 21;
        uint64_t statusresp            : 5;  /**< [ 28: 24](RO/H) Received status frame's Status_Resp field. */
        uint64_t reserved_29           : 1;
        uint64_t prefix                : 2;  /**< [ 31: 30](RO/H) Received status frame's SlaveACK field. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_sstatus_s cn; */
};
typedef union bdk_avs_sstatus bdk_avs_sstatus_t;

#define BDK_AVS_SSTATUS BDK_AVS_SSTATUS_FUNC()
static inline uint64_t BDK_AVS_SSTATUS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_SSTATUS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000001030ll;
    __bdk_csr_fatal("AVS_SSTATUS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_SSTATUS bdk_avs_sstatus_t
#define bustype_BDK_AVS_SSTATUS BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_SSTATUS "AVS_SSTATUS"
#define device_bar_BDK_AVS_SSTATUS 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_SSTATUS 0
#define arguments_BDK_AVS_SSTATUS -1,-1,-1,-1

/**
 * Register (NCB) avs_sts
 *
 * AVS STS Register
 * This register provides status and interrupt for the AVS interface.
 */
union bdk_avs_sts
{
    uint64_t u;
    struct bdk_avs_sts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_9_63         : 55;
        uint64_t busy                  : 1;  /**< [  8:  8](RO/H) Busy.
                                                                 0 = No AVS transaction in progress.
                                                                 1 = AVS engine is processing a transaction. */
        uint64_t reserved_5_7          : 3;
        uint64_t start                 : 1;  /**< [  4:  4](R/W1/H) Write 1 to start transaction defined by AVS_MDATA[CMD].
                                                                 Read back value always zero. */
        uint64_t reserved_2_3          : 2;
        uint64_t crc_err               : 1;  /**< [  1:  1](R/W1C/H) AVS interrupt on CRC error in receiving data.
                                                                 If there is CRC error in the read frame, [CRC_ERR] interrupt is generated
                                                                 at the same time with [DONE] interrupt. */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) AVS interrupt on transaction done. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1C/H) AVS interrupt on transaction done. */
        uint64_t crc_err               : 1;  /**< [  1:  1](R/W1C/H) AVS interrupt on CRC error in receiving data.
                                                                 If there is CRC error in the read frame, [CRC_ERR] interrupt is generated
                                                                 at the same time with [DONE] interrupt. */
        uint64_t reserved_2_3          : 2;
        uint64_t start                 : 1;  /**< [  4:  4](R/W1/H) Write 1 to start transaction defined by AVS_MDATA[CMD].
                                                                 Read back value always zero. */
        uint64_t reserved_5_7          : 3;
        uint64_t busy                  : 1;  /**< [  8:  8](RO/H) Busy.
                                                                 0 = No AVS transaction in progress.
                                                                 1 = AVS engine is processing a transaction. */
        uint64_t reserved_9_63         : 55;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_sts_s cn; */
};
typedef union bdk_avs_sts bdk_avs_sts_t;

#define BDK_AVS_STS BDK_AVS_STS_FUNC()
static inline uint64_t BDK_AVS_STS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_STS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000000200ll;
    __bdk_csr_fatal("AVS_STS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_STS bdk_avs_sts_t
#define bustype_BDK_AVS_STS BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_STS "AVS_STS"
#define device_bar_BDK_AVS_STS 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_STS 0
#define arguments_BDK_AVS_STS -1,-1,-1,-1

/**
 * Register (NCB) avs_sts_w1s
 *
 * AVS Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_avs_sts_w1s
{
    uint64_t u;
    struct bdk_avs_sts_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t crc_err               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets AVS_STS[CRC_ERR]. */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets AVS_STS[DONE]. */
#else /* Word 0 - Little Endian */
        uint64_t done                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets AVS_STS[DONE]. */
        uint64_t crc_err               : 1;  /**< [  1:  1](R/W1S/H) Reads or sets AVS_STS[CRC_ERR]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_avs_sts_w1s_s cn; */
};
typedef union bdk_avs_sts_w1s bdk_avs_sts_w1s_t;

#define BDK_AVS_STS_W1S BDK_AVS_STS_W1S_FUNC()
static inline uint64_t BDK_AVS_STS_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_AVS_STS_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x80a000000208ll;
    __bdk_csr_fatal("AVS_STS_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_AVS_STS_W1S bdk_avs_sts_w1s_t
#define bustype_BDK_AVS_STS_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_AVS_STS_W1S "AVS_STS_W1S"
#define device_bar_BDK_AVS_STS_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_AVS_STS_W1S 0
#define arguments_BDK_AVS_STS_W1S -1,-1,-1,-1

#endif /* __BDK_CSRS_AVS_H__ */
