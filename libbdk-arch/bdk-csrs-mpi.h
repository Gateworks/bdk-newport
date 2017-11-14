#ifndef __BDK_CSRS_MPI_H__
#define __BDK_CSRS_MPI_H__
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
 * Cavium MPI.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration mpi_bar_e
 *
 * MPI/SPI Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_MPI_BAR_E_MPIX_PF_BAR0(a) (0x804000000000ll + 0x1000000000ll * (a))
#define BDK_MPI_BAR_E_MPIX_PF_BAR0_SIZE 0x10000ull
#define BDK_MPI_BAR_E_MPIX_PF_BAR4(a) (0x804000f00000ll + 0x1000000000ll * (a))
#define BDK_MPI_BAR_E_MPIX_PF_BAR4_SIZE 0x100000ull
#define BDK_MPI_BAR_E_MPI_PF_BAR0 (0x804000000000ll)
#define BDK_MPI_BAR_E_MPI_PF_BAR0_SIZE 0x800000ull
#define BDK_MPI_BAR_E_MPI_PF_BAR4 (0x804000f00000ll)
#define BDK_MPI_BAR_E_MPI_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration mpi_int_vec_e
 *
 * MPI/SPI MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_MPI_INT_VEC_E_ESPI_INTSX(a) (1 + (a))
#define BDK_MPI_INT_VEC_E_INTS (0)

/**
 * Enumeration mpi_iomode_e
 *
 * MPI IOMODE Enumeration
 * Enumerates the IO mode in MPI()_CFG[IOMODE].
 */
#define BDK_MPI_IOMODE_E_X1_BIDIR (1)
#define BDK_MPI_IOMODE_E_X1_UNIDIR (0)
#define BDK_MPI_IOMODE_E_X2_BIDIR (2)
#define BDK_MPI_IOMODE_E_X4_BIDIR (3)

/**
 * Structure mpi_bp_test0_bp_cfg_s
 *
 * INTERNAL: MPI Backpressure Test 0 Configuration Structure
 *
 * MPI()_BP_TEST0[BP_CFG] field structure for bit connections to fifos.
 */
union bdk_mpi_bp_test0_bp_cfg_s
{
    uint32_t u;
    struct bdk_mpi_bp_test0_bp_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t in_req_fifo           : 2;  /**< [  7:  6] Config for in_req_fifo. */
        uint32_t req_arb_fifo          : 2;  /**< [  5:  4] Config for req_arb_fifo. */
        uint32_t gnt_order_fifo        : 2;  /**< [  3:  2] Config for gnt_order_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
        uint32_t gnt_order_fifo        : 2;  /**< [  3:  2] Config for gnt_order_fifo. */
        uint32_t req_arb_fifo          : 2;  /**< [  5:  4] Config for req_arb_fifo. */
        uint32_t in_req_fifo           : 2;  /**< [  7:  6] Config for in_req_fifo. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    struct bdk_mpi_bp_test0_bp_cfg_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t reserved_8_13         : 6;
        uint32_t in_req_fifo           : 2;  /**< [  7:  6] Config for in_req_fifo. */
        uint32_t req_arb_fifo          : 2;  /**< [  5:  4] Config for req_arb_fifo. */
        uint32_t gnt_order_fifo        : 2;  /**< [  3:  2] Config for gnt_order_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
        uint32_t gnt_order_fifo        : 2;  /**< [  3:  2] Config for gnt_order_fifo. */
        uint32_t req_arb_fifo          : 2;  /**< [  5:  4] Config for req_arb_fifo. */
        uint32_t in_req_fifo           : 2;  /**< [  7:  6] Config for in_req_fifo. */
        uint32_t reserved_8_13         : 6;
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } cn;
};

/**
 * Structure mpi_bp_test0_enable_s
 *
 * INTERNAL: MPI Backpressure Test 0 Enable Structure
 *
 * MPI()_BP_TEST0[ENABLE] field structure for bit connections to fifos.
 */
union bdk_mpi_bp_test0_enable_s
{
    uint32_t u;
    struct bdk_mpi_bp_test0_enable_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t in_req_fifo           : 1;  /**< [  3:  3] ENABLE for in_req_fifo. */
        uint32_t req_arb_fifo          : 1;  /**< [  2:  2] ENABLE for req_arb_fifo. */
        uint32_t gnt_order_fifo        : 1;  /**< [  1:  1] ENABLE for gnt_order_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
        uint32_t gnt_order_fifo        : 1;  /**< [  1:  1] ENABLE for gnt_order_fifo. */
        uint32_t req_arb_fifo          : 1;  /**< [  2:  2] ENABLE for req_arb_fifo. */
        uint32_t in_req_fifo           : 1;  /**< [  3:  3] ENABLE for in_req_fifo. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    struct bdk_mpi_bp_test0_enable_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_7_31         : 25;
        uint32_t reserved_4_6          : 3;
        uint32_t in_req_fifo           : 1;  /**< [  3:  3] ENABLE for in_req_fifo. */
        uint32_t req_arb_fifo          : 1;  /**< [  2:  2] ENABLE for req_arb_fifo. */
        uint32_t gnt_order_fifo        : 1;  /**< [  1:  1] ENABLE for gnt_order_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
        uint32_t gnt_order_fifo        : 1;  /**< [  1:  1] ENABLE for gnt_order_fifo. */
        uint32_t req_arb_fifo          : 1;  /**< [  2:  2] ENABLE for req_arb_fifo. */
        uint32_t in_req_fifo           : 1;  /**< [  3:  3] ENABLE for in_req_fifo. */
        uint32_t reserved_4_6          : 3;
        uint32_t reserved_7_31         : 25;
#endif /* Word 0 - End */
    } cn;
};

/**
 * Register (NCB) mpi#_bp_test0
 *
 * INTERNAL: MPI Backpressure Test Register
 */
union bdk_mpix_bp_test0
{
    uint64_t u;
    struct bdk_mpix_bp_test0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 7;  /**< [ 63: 57](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 Refer to MPI_BP_TEST0_ENABLE_S for field bit descriptions and layout. */
        uint64_t reserved_48_56        : 9;
        uint64_t bp_cfg                : 14; /**< [ 47: 34](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 Refer to MPI_BP_TEST0_BP_CFG_S for field bit descriptions and layout. */
        uint64_t reserved_12_33        : 22;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_33        : 22;
        uint64_t bp_cfg                : 14; /**< [ 47: 34](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 Refer to MPI_BP_TEST0_BP_CFG_S for field bit descriptions and layout. */
        uint64_t reserved_48_56        : 9;
        uint64_t enable                : 7;  /**< [ 63: 57](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 Refer to MPI_BP_TEST0_ENABLE_S for field bit descriptions and layout. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_bp_test0_s cn; */
};
typedef union bdk_mpix_bp_test0 bdk_mpix_bp_test0_t;

static inline uint64_t BDK_MPIX_BP_TEST0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_BP_TEST0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x80400000e000ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_BP_TEST0", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_BP_TEST0(a) bdk_mpix_bp_test0_t
#define bustype_BDK_MPIX_BP_TEST0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_BP_TEST0(a) "MPIX_BP_TEST0"
#define device_bar_BDK_MPIX_BP_TEST0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_BP_TEST0(a) (a)
#define arguments_BDK_MPIX_BP_TEST0(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_cfg
 *
 * MPI/SPI Configuration Register
 * This register provides configuration for the MPI/SPI interface. Writes to the csr
 * will be unpredictable if done while MPI()_STS[BUSY] is asserted.
 */
union bdk_mpix_cfg
{
    uint64_t u;
    struct bdk_mpix_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_50_63        : 14;
        uint64_t tb100_en              : 1;  /**< [ 49: 49](R/W) SPI 100 MHz clock enable. See [CLKDIV].
                                                                 0 = Use system clock as base frequency. This provides higher granularity, but
                                                                 may require changing [CLKDIV] if the system clock frequency is changed.
                                                                 1 = Use 100 MHz clock as base frequency. This is the reset value to enable the
                                                                 boot process to be frequency agnostic. */
        uint64_t reserved_48           : 1;
        uint64_t cs_espi_en            : 4;  /**< [ 47: 44](R/W) Enable ESPI mode per each slave.  Each bit corresponds to each of the four possible CS's
                                                                 on this MPI.
                                                                 If the bit is 0:
                                                                 * CRC hardware is disabled.
                                                                 * The turn around time is default for SPI.
                                                                 * No special parsing in hardware.

                                                                 If the bit is 1:
                                                                 * CRC hardware is enabled. Hardware will automatically calculate CRC for one
                                                                 transaction and then apply it to the end of the transmission. On a read it will apply to
                                                                 end of transaction and then check the CRC on response and if there is an error the
                                                                 MPI()_STS[CRC_ERR] bit will be set.
                                                                 * The turn around time (TAR in the ESPI spec) is set to two cycles.
                                                                 * Parsing for special state is enabled.

                                                                 Internal:
                                                                 Regarding CRCs: On a write, It would actually internally increase the tx_count and
                                                                 total_count by 1.  On a read (tx count != total_count) it would add 1 to tx_count and 2
                                                                 to total_count) so it would get the recieve CRC as well. */
        uint64_t reserved_36_43        : 8;
        uint64_t iomode                : 2;  /**< [ 35: 34](R/W) I/O bus configuration mode.
                                                                 Used when [LEGACY_DIS] is set.
                                                                 Enumerated by MPI_IOMODE_E. */
        uint64_t reserved_32_33        : 2;
        uint64_t legacy_dis            : 1;  /**< [ 31: 31](R/W) Disable legacy mode.
                                                                 0 = Simple SPI/MPI support backward compatible with CN8XXX-series chips.
                                                                 1 = New interface that allows support for ESPI. */
        uint64_t reserved_29_30        : 2;
        uint64_t clkdiv                : 13; /**< [ 28: 16](R/W) Clock divisor. Value 0x0 disables the SPI clock.

                                                                 _ SPI clock = base clock / (2 * [CLKDIV])

                                                                 where base clock is coprocessor clock or 100 MHz based on [TB100_EN]. */
        uint64_t csena3                : 1;  /**< [ 15: 15](R/W) Must be one. */
        uint64_t csena2                : 1;  /**< [ 14: 14](R/W) Must be one. */
        uint64_t csena1                : 1;  /**< [ 13: 13](R/W) Must be one. */
        uint64_t csena0                : 1;  /**< [ 12: 12](R/W) Must be one. */
        uint64_t cslate                : 1;  /**< [ 11: 11](R/W) SPI_CSn_L late.
                                                                 0 = SPI_CSn_L asserts 1/2 SPI_CK cycle before the transaction.
                                                                 1 = SPI_CSn_L asserts coincident with the transaction. */
        uint64_t tritx                 : 1;  /**< [ 10: 10](R/W) This works for [LEGACY_DIS] = 0 only on IO pin 0 (formerly SPI_DO).
                                                                 This works for [LEGACY_DIS] = 1 on all IO pins.
                                                                 Tristate TX. Used only when WIREOR = 1
                                                                 0 = SPI_DO pin is driven when slave is not expected to be driving.
                                                                 1 = SPI_DO pin is tristated when not transmitting. Setting this for eSPI means
                                                                 TX phase plus first cycle of TAR phase is to follow ESPI standard. */
        uint64_t idleclks              : 2;  /**< [  9:  8](R/W) Idle clocks. When set, guarantees idle SPI_CK cycles between commands. If TX only
                                                                 transaction, this doesn't do anything. */
        uint64_t cshi                  : 1;  /**< [  7:  7](R/W) SPI_CSn_L high: 1 = SPI_CSn_L is asserted high, 0 = SPI_CSn_L is asserted low. */
        uint64_t reserved_6            : 1;
        uint64_t cs_sticky             : 1;  /**< [  5:  5](R/W) Configuration chip select is sticky.
                                                                 0 = On a write to MPI()_CFG, chip selects will deassert.
                                                                 1 = On a write to MPI()_CFG, chip selects will retain their previous
                                                                 values (but see also MPI()_TX[LEAVECS]). */
        uint64_t lsbfirst              : 1;  /**< [  4:  4](R/W) This bit should only be used when [LEGACY_DIS] is 0. Do not use this with ESPI, it could
                                                                 screw up the protocol.
                                                                 Shift LSB first: 0 = shift MSB first, 1 = shift LSB first. */
        uint64_t wireor                : 1;  /**< [  3:  3](R/W) Only used when [LEGACY_DIS] = 0, otherwise see MPI_IOMODE_E.
                                                                 Wire-OR DO and DI.
                                                                 0 = SPI_DO and SPI_DI are separate wires (SPI). SPI_DO pin is always driven.
                                                                 1 = SPI_DO/DI is all from SPI_DO pin (MPI). SPI_DO pin is tristated when not transmitting.
                                                                 If [WIREOR] = 1, SPI_DI pin is not used by the MPI/SPI engine. */
        uint64_t clk_cont              : 1;  /**< [  2:  2](R/W) Clock control. Only used when ESPI mode is disabled.
                                                                 0 = Clock idles to value given by IDLELO after completion of MPI/SPI transaction.
                                                                 1 = Clock never idles, requires SPI_CSn_L deassertion/assertion between commands. */
        uint64_t idlelo                : 1;  /**< [  1:  1](R/W) Clock idle low/clock invert. Only used when ESPI is disabled, as the ESPI
                                                                 standard requires driving clock always negedge, sampling on posedge, and the
                                                                 clock always starts at 0.
                                                                 0 = SPI_CK idles high, first transition is high-to-low.
                                                                 1 = SPI_CK idles low, first transition is low-to-high. */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) MPI/SPI enable.
                                                                 0 = Pins are tristated.
                                                                 1 = Pins are driven. */
#else /* Word 0 - Little Endian */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) MPI/SPI enable.
                                                                 0 = Pins are tristated.
                                                                 1 = Pins are driven. */
        uint64_t idlelo                : 1;  /**< [  1:  1](R/W) Clock idle low/clock invert. Only used when ESPI is disabled, as the ESPI
                                                                 standard requires driving clock always negedge, sampling on posedge, and the
                                                                 clock always starts at 0.
                                                                 0 = SPI_CK idles high, first transition is high-to-low.
                                                                 1 = SPI_CK idles low, first transition is low-to-high. */
        uint64_t clk_cont              : 1;  /**< [  2:  2](R/W) Clock control. Only used when ESPI mode is disabled.
                                                                 0 = Clock idles to value given by IDLELO after completion of MPI/SPI transaction.
                                                                 1 = Clock never idles, requires SPI_CSn_L deassertion/assertion between commands. */
        uint64_t wireor                : 1;  /**< [  3:  3](R/W) Only used when [LEGACY_DIS] = 0, otherwise see MPI_IOMODE_E.
                                                                 Wire-OR DO and DI.
                                                                 0 = SPI_DO and SPI_DI are separate wires (SPI). SPI_DO pin is always driven.
                                                                 1 = SPI_DO/DI is all from SPI_DO pin (MPI). SPI_DO pin is tristated when not transmitting.
                                                                 If [WIREOR] = 1, SPI_DI pin is not used by the MPI/SPI engine. */
        uint64_t lsbfirst              : 1;  /**< [  4:  4](R/W) This bit should only be used when [LEGACY_DIS] is 0. Do not use this with ESPI, it could
                                                                 screw up the protocol.
                                                                 Shift LSB first: 0 = shift MSB first, 1 = shift LSB first. */
        uint64_t cs_sticky             : 1;  /**< [  5:  5](R/W) Configuration chip select is sticky.
                                                                 0 = On a write to MPI()_CFG, chip selects will deassert.
                                                                 1 = On a write to MPI()_CFG, chip selects will retain their previous
                                                                 values (but see also MPI()_TX[LEAVECS]). */
        uint64_t reserved_6            : 1;
        uint64_t cshi                  : 1;  /**< [  7:  7](R/W) SPI_CSn_L high: 1 = SPI_CSn_L is asserted high, 0 = SPI_CSn_L is asserted low. */
        uint64_t idleclks              : 2;  /**< [  9:  8](R/W) Idle clocks. When set, guarantees idle SPI_CK cycles between commands. If TX only
                                                                 transaction, this doesn't do anything. */
        uint64_t tritx                 : 1;  /**< [ 10: 10](R/W) This works for [LEGACY_DIS] = 0 only on IO pin 0 (formerly SPI_DO).
                                                                 This works for [LEGACY_DIS] = 1 on all IO pins.
                                                                 Tristate TX. Used only when WIREOR = 1
                                                                 0 = SPI_DO pin is driven when slave is not expected to be driving.
                                                                 1 = SPI_DO pin is tristated when not transmitting. Setting this for eSPI means
                                                                 TX phase plus first cycle of TAR phase is to follow ESPI standard. */
        uint64_t cslate                : 1;  /**< [ 11: 11](R/W) SPI_CSn_L late.
                                                                 0 = SPI_CSn_L asserts 1/2 SPI_CK cycle before the transaction.
                                                                 1 = SPI_CSn_L asserts coincident with the transaction. */
        uint64_t csena0                : 1;  /**< [ 12: 12](R/W) Must be one. */
        uint64_t csena1                : 1;  /**< [ 13: 13](R/W) Must be one. */
        uint64_t csena2                : 1;  /**< [ 14: 14](R/W) Must be one. */
        uint64_t csena3                : 1;  /**< [ 15: 15](R/W) Must be one. */
        uint64_t clkdiv                : 13; /**< [ 28: 16](R/W) Clock divisor. Value 0x0 disables the SPI clock.

                                                                 _ SPI clock = base clock / (2 * [CLKDIV])

                                                                 where base clock is coprocessor clock or 100 MHz based on [TB100_EN]. */
        uint64_t reserved_29_30        : 2;
        uint64_t legacy_dis            : 1;  /**< [ 31: 31](R/W) Disable legacy mode.
                                                                 0 = Simple SPI/MPI support backward compatible with CN8XXX-series chips.
                                                                 1 = New interface that allows support for ESPI. */
        uint64_t reserved_32_33        : 2;
        uint64_t iomode                : 2;  /**< [ 35: 34](R/W) I/O bus configuration mode.
                                                                 Used when [LEGACY_DIS] is set.
                                                                 Enumerated by MPI_IOMODE_E. */
        uint64_t reserved_36_43        : 8;
        uint64_t cs_espi_en            : 4;  /**< [ 47: 44](R/W) Enable ESPI mode per each slave.  Each bit corresponds to each of the four possible CS's
                                                                 on this MPI.
                                                                 If the bit is 0:
                                                                 * CRC hardware is disabled.
                                                                 * The turn around time is default for SPI.
                                                                 * No special parsing in hardware.

                                                                 If the bit is 1:
                                                                 * CRC hardware is enabled. Hardware will automatically calculate CRC for one
                                                                 transaction and then apply it to the end of the transmission. On a read it will apply to
                                                                 end of transaction and then check the CRC on response and if there is an error the
                                                                 MPI()_STS[CRC_ERR] bit will be set.
                                                                 * The turn around time (TAR in the ESPI spec) is set to two cycles.
                                                                 * Parsing for special state is enabled.

                                                                 Internal:
                                                                 Regarding CRCs: On a write, It would actually internally increase the tx_count and
                                                                 total_count by 1.  On a read (tx count != total_count) it would add 1 to tx_count and 2
                                                                 to total_count) so it would get the recieve CRC as well. */
        uint64_t reserved_48           : 1;
        uint64_t tb100_en              : 1;  /**< [ 49: 49](R/W) SPI 100 MHz clock enable. See [CLKDIV].
                                                                 0 = Use system clock as base frequency. This provides higher granularity, but
                                                                 may require changing [CLKDIV] if the system clock frequency is changed.
                                                                 1 = Use 100 MHz clock as base frequency. This is the reset value to enable the
                                                                 boot process to be frequency agnostic. */
        uint64_t reserved_50_63        : 14;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_cfg_s cn; */
};
typedef union bdk_mpix_cfg bdk_mpix_cfg_t;

static inline uint64_t BDK_MPIX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001000ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_CFG(a) bdk_mpix_cfg_t
#define bustype_BDK_MPIX_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_CFG(a) "MPIX_CFG"
#define device_bar_BDK_MPIX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_CFG(a) (a)
#define arguments_BDK_MPIX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_clken
 *
 * MPI Clock Enable Register
 * This register is to force conditional clock enable.
 */
union bdk_mpix_clken
{
    uint64_t u;
    struct bdk_mpix_clken_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t clken                 : 1;  /**< [  0:  0](R/W) Force the conditional clocking within MPI to be always on. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clken                 : 1;  /**< [  0:  0](R/W) Force the conditional clocking within MPI to be always on. For diagnostic use only. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_clken_s cn; */
};
typedef union bdk_mpix_clken bdk_mpix_clken_t;

static inline uint64_t BDK_MPIX_CLKEN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_CLKEN(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000002080ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_CLKEN", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_CLKEN(a) bdk_mpix_clken_t
#define bustype_BDK_MPIX_CLKEN(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_CLKEN(a) "MPIX_CLKEN"
#define device_bar_BDK_MPIX_CLKEN(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_CLKEN(a) (a)
#define arguments_BDK_MPIX_CLKEN(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_csclk_active_pc
 *
 * MPI Conditional Coprocessor Clock Counter Register
 * This register counts conditional clocks for power management.
 *
 * This register is reset on chip reset.
 */
union bdk_mpix_csclk_active_pc
{
    uint64_t u;
    struct bdk_mpix_csclk_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_csclk_active_pc_s cn; */
};
typedef union bdk_mpix_csclk_active_pc bdk_mpix_csclk_active_pc_t;

static inline uint64_t BDK_MPIX_CSCLK_ACTIVE_PC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_CSCLK_ACTIVE_PC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x8040000010e8ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_CSCLK_ACTIVE_PC", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_CSCLK_ACTIVE_PC(a) bdk_mpix_csclk_active_pc_t
#define bustype_BDK_MPIX_CSCLK_ACTIVE_PC(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_CSCLK_ACTIVE_PC(a) "MPIX_CSCLK_ACTIVE_PC"
#define device_bar_BDK_MPIX_CSCLK_ACTIVE_PC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_CSCLK_ACTIVE_PC(a) (a)
#define arguments_BDK_MPIX_CSCLK_ACTIVE_PC(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_cya_cfg
 *
 * MPI/SPI Internal Configuration Register
 * This register provides configuration for the overwrite MPI/SPI interface. Writes to the csr
 * will be unpredictable if done while MPI()_STS[BUSY] is asserted.
 */
union bdk_mpix_cya_cfg
{
    uint64_t u;
    struct bdk_mpix_cya_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t delay_spiclk          : 2;  /**< [  7:  6](R/W) Delay the SPICLK between 0 and 3 half-cycles. Default is zero delay. */
        uint64_t reserved_3_5          : 3;
        uint64_t drv_edge              : 1;  /**< [  2:  2](R/W) Data drive clock edge. Set means negedge, clear means posedge. */
        uint64_t ck_idle_lvl           : 1;  /**< [  1:  1](R/W) Clocks IDLE level. */
        uint64_t force_this_cfg        : 1;  /**< [  0:  0](R/W) Force configuration.
                                                                 0 = Use normal CSRs for configuration.
                                                                 1 = Force an override of the configuration to use this reigsters other bits. */
#else /* Word 0 - Little Endian */
        uint64_t force_this_cfg        : 1;  /**< [  0:  0](R/W) Force configuration.
                                                                 0 = Use normal CSRs for configuration.
                                                                 1 = Force an override of the configuration to use this reigsters other bits. */
        uint64_t ck_idle_lvl           : 1;  /**< [  1:  1](R/W) Clocks IDLE level. */
        uint64_t drv_edge              : 1;  /**< [  2:  2](R/W) Data drive clock edge. Set means negedge, clear means posedge. */
        uint64_t reserved_3_5          : 3;
        uint64_t delay_spiclk          : 2;  /**< [  7:  6](R/W) Delay the SPICLK between 0 and 3 half-cycles. Default is zero delay. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_cya_cfg_s cn; */
};
typedef union bdk_mpix_cya_cfg bdk_mpix_cya_cfg_t;

static inline uint64_t BDK_MPIX_CYA_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_CYA_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000002000ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_CYA_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_CYA_CFG(a) bdk_mpix_cya_cfg_t
#define bustype_BDK_MPIX_CYA_CFG(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_CYA_CFG(a) "MPIX_CYA_CFG"
#define device_bar_BDK_MPIX_CYA_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_CYA_CFG(a) (a)
#define arguments_BDK_MPIX_CYA_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_dat#
 *
 * MPI/SPI Legacy Data Registers
 * This register is only for MPI()_CFG[LEGACY_DIS]=0, otherwise see MPI()_WIDE_BUF().
 * Set this register for data transmission less than or equal to 8 bytes. Writes to
 * the csr will be unpredictable if done while MPI()_STS[BUSY] is asserted.
 */
union bdk_mpix_datx
{
    uint64_t u;
    struct bdk_mpix_datx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t data                  : 8;  /**< [  7:  0](R/W/H) Data to transmit/receive. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 8;  /**< [  7:  0](R/W/H) Data to transmit/receive. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_datx_s cn; */
};
typedef union bdk_mpix_datx bdk_mpix_datx_t;

static inline uint64_t BDK_MPIX_DATX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_DATX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=8)))
        return 0x804000001080ll + 0x1000000000ll * ((a) & 0x1) + 8ll * ((b) & 0xf);
    __bdk_csr_fatal("MPIX_DATX", 2, a, b, 0, 0);
}

#define typedef_BDK_MPIX_DATX(a,b) bdk_mpix_datx_t
#define bustype_BDK_MPIX_DATX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_DATX(a,b) "MPIX_DATX"
#define device_bar_BDK_MPIX_DATX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_DATX(a,b) (a)
#define arguments_BDK_MPIX_DATX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) mpi#_espi_rint_ena_w1c
 *
 * MPI ESPI Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_mpix_espi_rint_ena_w1c
{
    uint64_t u;
    struct bdk_mpix_espi_rint_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t espi_intr             : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for MPI(0..1)_ESPI_RINT_W1C[ESPI_INTR]. */
#else /* Word 0 - Little Endian */
        uint64_t espi_intr             : 64; /**< [ 63:  0](R/W1C/H) Reads or clears enable for MPI(0..1)_ESPI_RINT_W1C[ESPI_INTR]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_espi_rint_ena_w1c_s cn; */
};
typedef union bdk_mpix_espi_rint_ena_w1c bdk_mpix_espi_rint_ena_w1c_t;

static inline uint64_t BDK_MPIX_ESPI_RINT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_ESPI_RINT_ENA_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001148ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_ESPI_RINT_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_ESPI_RINT_ENA_W1C(a) bdk_mpix_espi_rint_ena_w1c_t
#define bustype_BDK_MPIX_ESPI_RINT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_ESPI_RINT_ENA_W1C(a) "MPIX_ESPI_RINT_ENA_W1C"
#define device_bar_BDK_MPIX_ESPI_RINT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_ESPI_RINT_ENA_W1C(a) (a)
#define arguments_BDK_MPIX_ESPI_RINT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_espi_rint_ena_w1s
 *
 * MPI ESPI Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_mpix_espi_rint_ena_w1s
{
    uint64_t u;
    struct bdk_mpix_espi_rint_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t espi_intr             : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for MPI(0..1)_ESPI_RINT_W1C[ESPI_INTR]. */
#else /* Word 0 - Little Endian */
        uint64_t espi_intr             : 64; /**< [ 63:  0](R/W1S/H) Reads or sets enable for MPI(0..1)_ESPI_RINT_W1C[ESPI_INTR]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_espi_rint_ena_w1s_s cn; */
};
typedef union bdk_mpix_espi_rint_ena_w1s bdk_mpix_espi_rint_ena_w1s_t;

static inline uint64_t BDK_MPIX_ESPI_RINT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_ESPI_RINT_ENA_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001150ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_ESPI_RINT_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_ESPI_RINT_ENA_W1S(a) bdk_mpix_espi_rint_ena_w1s_t
#define bustype_BDK_MPIX_ESPI_RINT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_ESPI_RINT_ENA_W1S(a) "MPIX_ESPI_RINT_ENA_W1S"
#define device_bar_BDK_MPIX_ESPI_RINT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_ESPI_RINT_ENA_W1S(a) (a)
#define arguments_BDK_MPIX_ESPI_RINT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_espi_rint_w1c
 *
 * MPI ESPI Interrupt Clear Register
 */
union bdk_mpix_espi_rint_w1c
{
    uint64_t u;
    struct bdk_mpix_espi_rint_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t espi_intr             : 64; /**< [ 63:  0](R/W1C/H) Interrupts for MPI_INT_VEC_E::ESPI_INTS(0..63). Physical interrupt sets for a set a
                                                                 virtual wire interrupts in ESPI mode. Software does virtual to physical mapping. */
#else /* Word 0 - Little Endian */
        uint64_t espi_intr             : 64; /**< [ 63:  0](R/W1C/H) Interrupts for MPI_INT_VEC_E::ESPI_INTS(0..63). Physical interrupt sets for a set a
                                                                 virtual wire interrupts in ESPI mode. Software does virtual to physical mapping. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_espi_rint_w1c_s cn; */
};
typedef union bdk_mpix_espi_rint_w1c bdk_mpix_espi_rint_w1c_t;

static inline uint64_t BDK_MPIX_ESPI_RINT_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_ESPI_RINT_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001138ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_ESPI_RINT_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_ESPI_RINT_W1C(a) bdk_mpix_espi_rint_w1c_t
#define bustype_BDK_MPIX_ESPI_RINT_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_ESPI_RINT_W1C(a) "MPIX_ESPI_RINT_W1C"
#define device_bar_BDK_MPIX_ESPI_RINT_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_ESPI_RINT_W1C(a) (a)
#define arguments_BDK_MPIX_ESPI_RINT_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_espi_rint_w1s
 *
 * MPI ESPI Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_mpix_espi_rint_w1s
{
    uint64_t u;
    struct bdk_mpix_espi_rint_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t espi_intr             : 64; /**< [ 63:  0](R/W1S/H) Reads or sets MPI(0..1)_ESPI_RINT_W1C[ESPI_INTR]. */
#else /* Word 0 - Little Endian */
        uint64_t espi_intr             : 64; /**< [ 63:  0](R/W1S/H) Reads or sets MPI(0..1)_ESPI_RINT_W1C[ESPI_INTR]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_espi_rint_w1s_s cn; */
};
typedef union bdk_mpix_espi_rint_w1s bdk_mpix_espi_rint_w1s_t;

static inline uint64_t BDK_MPIX_ESPI_RINT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_ESPI_RINT_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001140ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_ESPI_RINT_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_ESPI_RINT_W1S(a) bdk_mpix_espi_rint_w1s_t
#define bustype_BDK_MPIX_ESPI_RINT_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_ESPI_RINT_W1S(a) "MPIX_ESPI_RINT_W1S"
#define device_bar_BDK_MPIX_ESPI_RINT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_ESPI_RINT_W1S(a) (a)
#define arguments_BDK_MPIX_ESPI_RINT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_int_ena_w1c
 *
 * MPI/SPI Interrupt Enable Clear Register
 * This register clears interrupt enables.
 */
union bdk_mpix_int_ena_w1c
{
    uint64_t u;
    struct bdk_mpix_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1C) Reads or clears MPI()_INT_ENA_W1S[MPI_INTR]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1C) Reads or clears MPI()_INT_ENA_W1S[MPI_INTR]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_int_ena_w1c_s cn; */
};
typedef union bdk_mpix_int_ena_w1c bdk_mpix_int_ena_w1c_t;

static inline uint64_t BDK_MPIX_INT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_INT_ENA_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001030ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_INT_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_INT_ENA_W1C(a) bdk_mpix_int_ena_w1c_t
#define bustype_BDK_MPIX_INT_ENA_W1C(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_INT_ENA_W1C(a) "MPIX_INT_ENA_W1C"
#define device_bar_BDK_MPIX_INT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_INT_ENA_W1C(a) (a)
#define arguments_BDK_MPIX_INT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_int_ena_w1s
 *
 * MPI/SPI Interrupt Enable Set Register
 * This register sets interrupt enables.
 */
union bdk_mpix_int_ena_w1s
{
    uint64_t u;
    struct bdk_mpix_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1S) Enables reporting of MPI()_STS[MPI_INTR]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1S) Enables reporting of MPI()_STS[MPI_INTR]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_int_ena_w1s_s cn; */
};
typedef union bdk_mpix_int_ena_w1s bdk_mpix_int_ena_w1s_t;

static inline uint64_t BDK_MPIX_INT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_INT_ENA_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001038ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_INT_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_INT_ENA_W1S(a) bdk_mpix_int_ena_w1s_t
#define bustype_BDK_MPIX_INT_ENA_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_INT_ENA_W1S(a) "MPIX_INT_ENA_W1S"
#define device_bar_BDK_MPIX_INT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_INT_ENA_W1S(a) (a)
#define arguments_BDK_MPIX_INT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_io_ctl
 *
 * MPI/SPI I/O Control Register
 * This register controls the MPI0 IO drive strength and slew rates. MPI1 outputs are
 * controlled by GPIO_IO_CTL[DRIVE2] and GPIO_IO_CTL[SLEW2].
 */
union bdk_mpix_io_ctl
{
    uint64_t u;
    struct bdk_mpix_io_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t drive                 : 2;  /**< [  3:  2](R/W) MPI/SPI bus pin output drive strength.
                                                                 0x0 = 2 mA.
                                                                 0x1 = 4 mA.
                                                                 0x2 = 8 mA.
                                                                 0x3 = 16 mA. */
        uint64_t reserved_1            : 1;
        uint64_t slew                  : 1;  /**< [  0:  0](R/W) MPI/SPI bus pins output slew rate control.
                                                                 0 = Low slew rate.
                                                                 1 = High slew rate. */
#else /* Word 0 - Little Endian */
        uint64_t slew                  : 1;  /**< [  0:  0](R/W) MPI/SPI bus pins output slew rate control.
                                                                 0 = Low slew rate.
                                                                 1 = High slew rate. */
        uint64_t reserved_1            : 1;
        uint64_t drive                 : 2;  /**< [  3:  2](R/W) MPI/SPI bus pin output drive strength.
                                                                 0x0 = 2 mA.
                                                                 0x1 = 4 mA.
                                                                 0x2 = 8 mA.
                                                                 0x3 = 16 mA. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_io_ctl_s cn; */
};
typedef union bdk_mpix_io_ctl bdk_mpix_io_ctl_t;

static inline uint64_t BDK_MPIX_IO_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_IO_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001048ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_IO_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_IO_CTL(a) bdk_mpix_io_ctl_t
#define bustype_BDK_MPIX_IO_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_IO_CTL(a) "MPIX_IO_CTL"
#define device_bar_BDK_MPIX_IO_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_IO_CTL(a) (a)
#define arguments_BDK_MPIX_IO_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_msix_pba#
 *
 * MPI/SPI MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the MPI_INT_VEC_E enumeration.
 */
union bdk_mpix_msix_pbax
{
    uint64_t u;
    struct bdk_mpix_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MPI()_MSIX_VEC()_CTL, enumerated by MPI_INT_VEC_E. Bits
                                                                 that have no associated MPI_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MPI()_MSIX_VEC()_CTL, enumerated by MPI_INT_VEC_E. Bits
                                                                 that have no associated MPI_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_msix_pbax_s cn; */
};
typedef union bdk_mpix_msix_pbax bdk_mpix_msix_pbax_t;

static inline uint64_t BDK_MPIX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=1)))
        return 0x804000ff0000ll + 0x1000000000ll * ((a) & 0x1) + 8ll * ((b) & 0x1);
    __bdk_csr_fatal("MPIX_MSIX_PBAX", 2, a, b, 0, 0);
}

#define typedef_BDK_MPIX_MSIX_PBAX(a,b) bdk_mpix_msix_pbax_t
#define bustype_BDK_MPIX_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_MSIX_PBAX(a,b) "MPIX_MSIX_PBAX"
#define device_bar_BDK_MPIX_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_MPIX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_MPIX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) mpi#_msix_vec#_addr
 *
 * MPI/SPI MSI-X Vector Table Address Registers
 * This register is the MSI-X vector table, indexed by the MPI_INT_VEC_E enumeration.
 */
union bdk_mpix_msix_vecx_addr
{
    uint64_t u;
    struct bdk_mpix_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MPI()_MSIX_VEC()_ADDR, MPI()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MPI()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MPI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MPI()_MSIX_VEC()_ADDR, MPI()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MPI()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MPI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_msix_vecx_addr_s cn; */
};
typedef union bdk_mpix_msix_vecx_addr bdk_mpix_msix_vecx_addr_t;

static inline uint64_t BDK_MPIX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=64)))
        return 0x804000f00000ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x7f);
    __bdk_csr_fatal("MPIX_MSIX_VECX_ADDR", 2, a, b, 0, 0);
}

#define typedef_BDK_MPIX_MSIX_VECX_ADDR(a,b) bdk_mpix_msix_vecx_addr_t
#define bustype_BDK_MPIX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_MSIX_VECX_ADDR(a,b) "MPIX_MSIX_VECX_ADDR"
#define device_bar_BDK_MPIX_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_MPIX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_MPIX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) mpi#_msix_vec#_ctl
 *
 * MPI/SPI MSI-X Vector Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the MPI_INT_VEC_E enumeration.
 */
union bdk_mpix_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_mpix_msix_vecx_ctl_s
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
    /* struct bdk_mpix_msix_vecx_ctl_s cn; */
};
typedef union bdk_mpix_msix_vecx_ctl bdk_mpix_msix_vecx_ctl_t;

static inline uint64_t BDK_MPIX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=64)))
        return 0x804000f00008ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x7f);
    __bdk_csr_fatal("MPIX_MSIX_VECX_CTL", 2, a, b, 0, 0);
}

#define typedef_BDK_MPIX_MSIX_VECX_CTL(a,b) bdk_mpix_msix_vecx_ctl_t
#define bustype_BDK_MPIX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_MSIX_VECX_CTL(a,b) "MPIX_MSIX_VECX_CTL"
#define device_bar_BDK_MPIX_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_MPIX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_MPIX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB) mpi#_sts
 *
 * MPI/SPI STS Register
 */
union bdk_mpix_sts
{
    uint64_t u;
    struct bdk_mpix_sts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t crc                   : 8;  /**< [ 39: 32](R/W1C/H) MPI CRC value received. */
        uint64_t reserved_27_31        : 5;
        uint64_t crc_err               : 1;  /**< [ 26: 26](R/W1C/H) MPI CRC error on receive. Software should read this indication to tell if the
                                                                 receive data was error free. */
        uint64_t reserved_19_25        : 7;
        uint64_t rxnum                 : 11; /**< [ 18:  8](RO/H) Actual number of bytes received for the transaction. */
        uint64_t reserved_2_7          : 6;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1C/H) MPI interrupt on transaction done.  This interrupt should be cleared
                                                                 before any new SPI/MPI transaction is requested. */
        uint64_t busy                  : 1;  /**< [  0:  0](RO/H) Busy.
                                                                 0 = No MPI/SPI transaction in progress.
                                                                 1 = MPI/SPI engine is processing a transaction. */
#else /* Word 0 - Little Endian */
        uint64_t busy                  : 1;  /**< [  0:  0](RO/H) Busy.
                                                                 0 = No MPI/SPI transaction in progress.
                                                                 1 = MPI/SPI engine is processing a transaction. */
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1C/H) MPI interrupt on transaction done.  This interrupt should be cleared
                                                                 before any new SPI/MPI transaction is requested. */
        uint64_t reserved_2_7          : 6;
        uint64_t rxnum                 : 11; /**< [ 18:  8](RO/H) Actual number of bytes received for the transaction. */
        uint64_t reserved_19_25        : 7;
        uint64_t crc_err               : 1;  /**< [ 26: 26](R/W1C/H) MPI CRC error on receive. Software should read this indication to tell if the
                                                                 receive data was error free. */
        uint64_t reserved_27_31        : 5;
        uint64_t crc                   : 8;  /**< [ 39: 32](R/W1C/H) MPI CRC value received. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_sts_s cn; */
};
typedef union bdk_mpix_sts bdk_mpix_sts_t;

static inline uint64_t BDK_MPIX_STS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_STS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001008ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_STS", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_STS(a) bdk_mpix_sts_t
#define bustype_BDK_MPIX_STS(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_STS(a) "MPIX_STS"
#define device_bar_BDK_MPIX_STS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_STS(a) (a)
#define arguments_BDK_MPIX_STS(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_sts_w1s
 *
 * MPI/SPI Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_mpix_sts_w1s
{
    uint64_t u;
    struct bdk_mpix_sts_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MPI()_STS[MPI_INTR]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MPI()_STS[MPI_INTR]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_sts_w1s_s cn; */
};
typedef union bdk_mpix_sts_w1s bdk_mpix_sts_w1s_t;

static inline uint64_t BDK_MPIX_STS_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_STS_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001020ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_STS_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_STS_W1S(a) bdk_mpix_sts_w1s_t
#define bustype_BDK_MPIX_STS_W1S(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_STS_W1S(a) "MPIX_STS_W1S"
#define device_bar_BDK_MPIX_STS_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_STS_W1S(a) (a)
#define arguments_BDK_MPIX_STS_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_tx
 *
 * LEGACY MPI/SPI Transmit Register
 * This register is the legacy register, and must only be used when MPI()_CFG[LEGACY_DIS]=0.
 * This register shadows the value of MPI()_XMIT.
 * Writes to the csr will be unpredictable if done while MPI()_STS[BUSY] is asserted.
 */
union bdk_mpix_tx
{
    uint64_t u;
    struct bdk_mpix_tx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t csid                  : 2;  /**< [ 21: 20](WO) Which CS to assert for this transaction. */
        uint64_t reserved_17_19        : 3;
        uint64_t leavecs               : 1;  /**< [ 16: 16](WO) Leave SPI_CSn_L asserted.
                                                                 0 = Deassert SPI_CSn_L after the transaction is done.
                                                                 1 = Leave SPI_CSn_L asserted after the transaction is done, but may
                                                                 deassert when MPI()_CFG is written (see MPI()_CFG[CS_STICKY]. */
        uint64_t reserved_13_15        : 3;
        uint64_t txnum                 : 5;  /**< [ 12:  8](WO) Number of bytes to transmit. */
        uint64_t reserved_5_7          : 3;
        uint64_t totnum                : 5;  /**< [  4:  0](WO) Total number of bytes to shift (transmit and receive). */
#else /* Word 0 - Little Endian */
        uint64_t totnum                : 5;  /**< [  4:  0](WO) Total number of bytes to shift (transmit and receive). */
        uint64_t reserved_5_7          : 3;
        uint64_t txnum                 : 5;  /**< [ 12:  8](WO) Number of bytes to transmit. */
        uint64_t reserved_13_15        : 3;
        uint64_t leavecs               : 1;  /**< [ 16: 16](WO) Leave SPI_CSn_L asserted.
                                                                 0 = Deassert SPI_CSn_L after the transaction is done.
                                                                 1 = Leave SPI_CSn_L asserted after the transaction is done, but may
                                                                 deassert when MPI()_CFG is written (see MPI()_CFG[CS_STICKY]. */
        uint64_t reserved_17_19        : 3;
        uint64_t csid                  : 2;  /**< [ 21: 20](WO) Which CS to assert for this transaction. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_tx_s cn; */
};
typedef union bdk_mpix_tx bdk_mpix_tx_t;

static inline uint64_t BDK_MPIX_TX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_TX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001010ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_TX", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_TX(a) bdk_mpix_tx_t
#define bustype_BDK_MPIX_TX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_TX(a) "MPIX_TX"
#define device_bar_BDK_MPIX_TX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_TX(a) (a)
#define arguments_BDK_MPIX_TX(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_wide_buf#
 *
 * MPI/SPI Wide Data Register
 * This register is for both legacy and nonlegacy modes to recieve and transmit up
 * to 1K bytes of data buffer plus command header (max 16 bytes). Writes to the
 * csr will be unpredictable if done while MPI()_STS[BUSY] is asserted.
 */
union bdk_mpix_wide_bufx
{
    uint64_t u;
    struct bdk_mpix_wide_bufx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Data to transmit/receive. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Data to transmit/receive. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_wide_bufx_s cn; */
};
typedef union bdk_mpix_wide_bufx bdk_mpix_wide_bufx_t;

static inline uint64_t BDK_MPIX_WIDE_BUFX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_WIDE_BUFX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=143)))
        return 0x804000001800ll + 0x1000000000ll * ((a) & 0x1) + 8ll * ((b) & 0xff);
    __bdk_csr_fatal("MPIX_WIDE_BUFX", 2, a, b, 0, 0);
}

#define typedef_BDK_MPIX_WIDE_BUFX(a,b) bdk_mpix_wide_bufx_t
#define bustype_BDK_MPIX_WIDE_BUFX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_WIDE_BUFX(a,b) "MPIX_WIDE_BUFX"
#define device_bar_BDK_MPIX_WIDE_BUFX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_WIDE_BUFX(a,b) (a)
#define arguments_BDK_MPIX_WIDE_BUFX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) mpi#_wide_dat
 *
 * MPI/SPI Legacy Wide Data Register
 * This register is only for MPI()_CFG[LEGACY_DIS]=0, otherwise see MPI()_WIDE_BUF().
 * Set this register for data transmission less than or equal to 8 bytes. Writes to
 * the csr will be unpredictable if done while MPI()_STS[BUSY] is asserted.
 */
union bdk_mpix_wide_dat
{
    uint64_t u;
    struct bdk_mpix_wide_dat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Data to transmit/receive. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Data to transmit/receive. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpix_wide_dat_s cn; */
};
typedef union bdk_mpix_wide_dat bdk_mpix_wide_dat_t;

static inline uint64_t BDK_MPIX_WIDE_DAT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_WIDE_DAT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001040ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_WIDE_DAT", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_WIDE_DAT(a) bdk_mpix_wide_dat_t
#define bustype_BDK_MPIX_WIDE_DAT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_WIDE_DAT(a) "MPIX_WIDE_DAT"
#define device_bar_BDK_MPIX_WIDE_DAT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_WIDE_DAT(a) (a)
#define arguments_BDK_MPIX_WIDE_DAT(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi#_xmit
 *
 * MPI/SPI Transmit Register
 * Transmit transaction register. This register is for when MPI()_CFG[LEGACY_DIS]=0.
 * Writes to the csr will be unpredictable if done while MPI()_STS[BUSY] is asserted.
 */
union bdk_mpix_xmit
{
    uint64_t u;
    struct bdk_mpix_xmit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t csid                  : 2;  /**< [ 62: 61](WO) Which CS to assert for this transaction */
        uint64_t leavecs               : 1;  /**< [ 60: 60](WO) Leave SPI_CSn_L asserted.
                                                                 0 = Deassert SPI_CSn_L after the transaction is done.
                                                                 1 = Leave SPI_CSn_L asserted after the transaction is done. */
        uint64_t reserved_31_59        : 29;
        uint64_t txnum                 : 11; /**< [ 30: 20](WO) Number of bytes to transmit. If software writes a value larger than 1152 bytes,
                                                                 hardware will overwrite the number to 1152 bytes. */
        uint64_t reserved_11_19        : 9;
        uint64_t totnum                : 11; /**< [ 10:  0](WO) Total number of bytes to shift (transmit and receive). If you are in ESPI mode,
                                                                 this setting is not guaranteed because RXNUM is up to the slave. If the response
                                                                 is short, the MPI()_STS[MPI_INTR] interrupt will notify software. If software
                                                                 writes this CSR to be larger than 1152 bytes, hardware will overwrite the number
                                                                 as 1152 bytes. */
#else /* Word 0 - Little Endian */
        uint64_t totnum                : 11; /**< [ 10:  0](WO) Total number of bytes to shift (transmit and receive). If you are in ESPI mode,
                                                                 this setting is not guaranteed because RXNUM is up to the slave. If the response
                                                                 is short, the MPI()_STS[MPI_INTR] interrupt will notify software. If software
                                                                 writes this CSR to be larger than 1152 bytes, hardware will overwrite the number
                                                                 as 1152 bytes. */
        uint64_t reserved_11_19        : 9;
        uint64_t txnum                 : 11; /**< [ 30: 20](WO) Number of bytes to transmit. If software writes a value larger than 1152 bytes,
                                                                 hardware will overwrite the number to 1152 bytes. */
        uint64_t reserved_31_59        : 29;
        uint64_t leavecs               : 1;  /**< [ 60: 60](WO) Leave SPI_CSn_L asserted.
                                                                 0 = Deassert SPI_CSn_L after the transaction is done.
                                                                 1 = Leave SPI_CSn_L asserted after the transaction is done. */
        uint64_t csid                  : 2;  /**< [ 62: 61](WO) Which CS to assert for this transaction */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } s;
    struct bdk_mpix_xmit_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_63           : 1;
        uint64_t csid                  : 2;  /**< [ 62: 61](WO) Which CS to assert for this transaction */
        uint64_t leavecs               : 1;  /**< [ 60: 60](WO) Leave SPI_CSn_L asserted.
                                                                 0 = Deassert SPI_CSn_L after the transaction is done.
                                                                 1 = Leave SPI_CSn_L asserted after the transaction is done. */
        uint64_t reserved_51_59        : 9;
        uint64_t reserved_31_50        : 20;
        uint64_t txnum                 : 11; /**< [ 30: 20](WO) Number of bytes to transmit. If software writes a value larger than 1152 bytes,
                                                                 hardware will overwrite the number to 1152 bytes. */
        uint64_t reserved_11_19        : 9;
        uint64_t totnum                : 11; /**< [ 10:  0](WO) Total number of bytes to shift (transmit and receive). If you are in ESPI mode,
                                                                 this setting is not guaranteed because RXNUM is up to the slave. If the response
                                                                 is short, the MPI()_STS[MPI_INTR] interrupt will notify software. If software
                                                                 writes this CSR to be larger than 1152 bytes, hardware will overwrite the number
                                                                 as 1152 bytes. */
#else /* Word 0 - Little Endian */
        uint64_t totnum                : 11; /**< [ 10:  0](WO) Total number of bytes to shift (transmit and receive). If you are in ESPI mode,
                                                                 this setting is not guaranteed because RXNUM is up to the slave. If the response
                                                                 is short, the MPI()_STS[MPI_INTR] interrupt will notify software. If software
                                                                 writes this CSR to be larger than 1152 bytes, hardware will overwrite the number
                                                                 as 1152 bytes. */
        uint64_t reserved_11_19        : 9;
        uint64_t txnum                 : 11; /**< [ 30: 20](WO) Number of bytes to transmit. If software writes a value larger than 1152 bytes,
                                                                 hardware will overwrite the number to 1152 bytes. */
        uint64_t reserved_31_50        : 20;
        uint64_t reserved_51_59        : 9;
        uint64_t leavecs               : 1;  /**< [ 60: 60](WO) Leave SPI_CSn_L asserted.
                                                                 0 = Deassert SPI_CSn_L after the transaction is done.
                                                                 1 = Leave SPI_CSn_L asserted after the transaction is done. */
        uint64_t csid                  : 2;  /**< [ 62: 61](WO) Which CS to assert for this transaction */
        uint64_t reserved_63           : 1;
#endif /* Word 0 - End */
    } cn;
};
typedef union bdk_mpix_xmit bdk_mpix_xmit_t;

static inline uint64_t BDK_MPIX_XMIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPIX_XMIT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x804000001018ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("MPIX_XMIT", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPIX_XMIT(a) bdk_mpix_xmit_t
#define bustype_BDK_MPIX_XMIT(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPIX_XMIT(a) "MPIX_XMIT"
#define device_bar_BDK_MPIX_XMIT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPIX_XMIT(a) (a)
#define arguments_BDK_MPIX_XMIT(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi_cfg
 *
 * MPI/SPI Configuration Register
 * This register provides configuration for the MPI/SPI interface.
 */
union bdk_mpi_cfg
{
    uint64_t u;
    struct bdk_mpi_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_29_63        : 35;
        uint64_t clkdiv                : 13; /**< [ 28: 16](R/W) Clock divisor.
                                                                 SPI_CK = coprocessor clock / (2 * CLKDIV)
                                                                 CLKDIV = coprocessor clock / (2 * SPI_CK) */
        uint64_t csena3                : 1;  /**< [ 15: 15](R/W) Must be one. */
        uint64_t csena2                : 1;  /**< [ 14: 14](R/W) Must be one. */
        uint64_t csena1                : 1;  /**< [ 13: 13](R/W) Must be one. */
        uint64_t csena0                : 1;  /**< [ 12: 12](R/W) Must be one. */
        uint64_t cslate                : 1;  /**< [ 11: 11](R/W) SPI_CSn_L late.
                                                                 0 = SPI_CSn_L asserts 1/2 SPI_CK cycle before the transaction.
                                                                 1 = SPI_CSn_L asserts coincident with the transaction. */
        uint64_t tritx                 : 1;  /**< [ 10: 10](R/W) Tristate TX. Used only when WIREOR = 1
                                                                 0 = SPI_DO pin is driven when slave is not expected to be driving.
                                                                 1 = SPI_DO pin is tristated when not transmitting. */
        uint64_t idleclks              : 2;  /**< [  9:  8](R/W) Idle clocks. When set, guarantees idle SPI_CK cycles between commands. */
        uint64_t cshi                  : 1;  /**< [  7:  7](R/W) SPI_CSn_L high: 1 = SPI_CSn_L is asserted high, 0 = SPI_CSn_L is asserted low. */
        uint64_t reserved_5_6          : 2;
        uint64_t lsbfirst              : 1;  /**< [  4:  4](R/W) Shift LSB first: 0 = shift MSB first, 1 = shift LSB first. */
        uint64_t wireor                : 1;  /**< [  3:  3](R/W) Wire-OR DO and DI.
                                                                 0 = SPI_DO and SPI_DI are separate wires (SPI). SPI_DO pin is always driven.
                                                                 1 = SPI_DO/DI is all from SPI_DO pin (MPI). SPI_DO pin is tristated when not transmitting.
                                                                 If [WIREOR] = 1, SPI_DI pin is not used by the MPI/SPI engine. */
        uint64_t clk_cont              : 1;  /**< [  2:  2](R/W) Clock control.
                                                                 0 = Clock idles to value given by IDLELO after completion of MPI/SPI transaction.
                                                                 1 = Clock never idles, requires SPI_CSn_L deassertion/assertion between commands. */
        uint64_t idlelo                : 1;  /**< [  1:  1](R/W) Clock idle low/clock invert.
                                                                 0 = SPI_CK idles high, first transition is high-to-low.
                                                                 1 = SPI_CK idles low, first transition is low-to-high. */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) MPI/SPI enable.
                                                                 0 = Pins are tristated.
                                                                 1 = Pins are driven. */
#else /* Word 0 - Little Endian */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) MPI/SPI enable.
                                                                 0 = Pins are tristated.
                                                                 1 = Pins are driven. */
        uint64_t idlelo                : 1;  /**< [  1:  1](R/W) Clock idle low/clock invert.
                                                                 0 = SPI_CK idles high, first transition is high-to-low.
                                                                 1 = SPI_CK idles low, first transition is low-to-high. */
        uint64_t clk_cont              : 1;  /**< [  2:  2](R/W) Clock control.
                                                                 0 = Clock idles to value given by IDLELO after completion of MPI/SPI transaction.
                                                                 1 = Clock never idles, requires SPI_CSn_L deassertion/assertion between commands. */
        uint64_t wireor                : 1;  /**< [  3:  3](R/W) Wire-OR DO and DI.
                                                                 0 = SPI_DO and SPI_DI are separate wires (SPI). SPI_DO pin is always driven.
                                                                 1 = SPI_DO/DI is all from SPI_DO pin (MPI). SPI_DO pin is tristated when not transmitting.
                                                                 If [WIREOR] = 1, SPI_DI pin is not used by the MPI/SPI engine. */
        uint64_t lsbfirst              : 1;  /**< [  4:  4](R/W) Shift LSB first: 0 = shift MSB first, 1 = shift LSB first. */
        uint64_t reserved_5_6          : 2;
        uint64_t cshi                  : 1;  /**< [  7:  7](R/W) SPI_CSn_L high: 1 = SPI_CSn_L is asserted high, 0 = SPI_CSn_L is asserted low. */
        uint64_t idleclks              : 2;  /**< [  9:  8](R/W) Idle clocks. When set, guarantees idle SPI_CK cycles between commands. */
        uint64_t tritx                 : 1;  /**< [ 10: 10](R/W) Tristate TX. Used only when WIREOR = 1
                                                                 0 = SPI_DO pin is driven when slave is not expected to be driving.
                                                                 1 = SPI_DO pin is tristated when not transmitting. */
        uint64_t cslate                : 1;  /**< [ 11: 11](R/W) SPI_CSn_L late.
                                                                 0 = SPI_CSn_L asserts 1/2 SPI_CK cycle before the transaction.
                                                                 1 = SPI_CSn_L asserts coincident with the transaction. */
        uint64_t csena0                : 1;  /**< [ 12: 12](R/W) Must be one. */
        uint64_t csena1                : 1;  /**< [ 13: 13](R/W) Must be one. */
        uint64_t csena2                : 1;  /**< [ 14: 14](R/W) Must be one. */
        uint64_t csena3                : 1;  /**< [ 15: 15](R/W) Must be one. */
        uint64_t clkdiv                : 13; /**< [ 28: 16](R/W) Clock divisor.
                                                                 SPI_CK = coprocessor clock / (2 * CLKDIV)
                                                                 CLKDIV = coprocessor clock / (2 * SPI_CK) */
        uint64_t reserved_29_63        : 35;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_cfg_s cn; */
};
typedef union bdk_mpi_cfg bdk_mpi_cfg_t;

#define BDK_MPI_CFG BDK_MPI_CFG_FUNC()
static inline uint64_t BDK_MPI_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_CFG_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x804000001000ll;
    __bdk_csr_fatal("MPI_CFG", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MPI_CFG bdk_mpi_cfg_t
#define bustype_BDK_MPI_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_CFG "MPI_CFG"
#define device_bar_BDK_MPI_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_MPI_CFG 0
#define arguments_BDK_MPI_CFG -1,-1,-1,-1

/**
 * Register (NCB) mpi_dat#
 *
 * MPI/SPI Data Registers
 */
union bdk_mpi_datx
{
    uint64_t u;
    struct bdk_mpi_datx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t data                  : 8;  /**< [  7:  0](R/W/H) Data to transmit/receive. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 8;  /**< [  7:  0](R/W/H) Data to transmit/receive. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_datx_s cn; */
};
typedef union bdk_mpi_datx bdk_mpi_datx_t;

static inline uint64_t BDK_MPI_DATX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_DATX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a<=8))
        return 0x804000001080ll + 8ll * ((a) & 0xf);
    __bdk_csr_fatal("MPI_DATX", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPI_DATX(a) bdk_mpi_datx_t
#define bustype_BDK_MPI_DATX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_DATX(a) "MPI_DATX"
#define device_bar_BDK_MPI_DATX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_MPI_DATX(a) (a)
#define arguments_BDK_MPI_DATX(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi_int_ena_w1c
 *
 * MPI Interrupt Enable Clear Register
 * This register clears interrupt enables.
 */
union bdk_mpi_int_ena_w1c
{
    uint64_t u;
    struct bdk_mpi_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1C) Reads or clears MPI_INT_ENA_W1S[MPI_INTR]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1C) Reads or clears MPI_INT_ENA_W1S[MPI_INTR]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_int_ena_w1c_s cn; */
};
typedef union bdk_mpi_int_ena_w1c bdk_mpi_int_ena_w1c_t;

#define BDK_MPI_INT_ENA_W1C BDK_MPI_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_MPI_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_INT_ENA_W1C_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x804000001030ll;
    __bdk_csr_fatal("MPI_INT_ENA_W1C", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MPI_INT_ENA_W1C bdk_mpi_int_ena_w1c_t
#define bustype_BDK_MPI_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_INT_ENA_W1C "MPI_INT_ENA_W1C"
#define device_bar_BDK_MPI_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_MPI_INT_ENA_W1C 0
#define arguments_BDK_MPI_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) mpi_int_ena_w1s
 *
 * MPI Interrupt Enable Set Register
 * This register sets interrupt enables.
 */
union bdk_mpi_int_ena_w1s
{
    uint64_t u;
    struct bdk_mpi_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1S) Enables reporting of MPI_STS[MPI_INTR]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1S) Enables reporting of MPI_STS[MPI_INTR]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_int_ena_w1s_s cn; */
};
typedef union bdk_mpi_int_ena_w1s bdk_mpi_int_ena_w1s_t;

#define BDK_MPI_INT_ENA_W1S BDK_MPI_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_MPI_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_INT_ENA_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x804000001038ll;
    __bdk_csr_fatal("MPI_INT_ENA_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MPI_INT_ENA_W1S bdk_mpi_int_ena_w1s_t
#define bustype_BDK_MPI_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_INT_ENA_W1S "MPI_INT_ENA_W1S"
#define device_bar_BDK_MPI_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MPI_INT_ENA_W1S 0
#define arguments_BDK_MPI_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) mpi_msix_pba#
 *
 * MPI/SPI MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table, the bit number is indexed by the MPI_INT_VEC_E enumeration.
 */
union bdk_mpi_msix_pbax
{
    uint64_t u;
    struct bdk_mpi_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MPI_MSIX_VEC()_CTL, enumerated by MPI_INT_VEC_E. Bits
                                                                 that have no associated MPI_INT_VEC_E are zero. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated MPI_MSIX_VEC()_CTL, enumerated by MPI_INT_VEC_E. Bits
                                                                 that have no associated MPI_INT_VEC_E are zero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_msix_pbax_s cn; */
};
typedef union bdk_mpi_msix_pbax bdk_mpi_msix_pbax_t;

static inline uint64_t BDK_MPI_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_MSIX_PBAX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a==0))
        return 0x804000ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("MPI_MSIX_PBAX", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPI_MSIX_PBAX(a) bdk_mpi_msix_pbax_t
#define bustype_BDK_MPI_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_MSIX_PBAX(a) "MPI_MSIX_PBAX"
#define device_bar_BDK_MPI_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MPI_MSIX_PBAX(a) (a)
#define arguments_BDK_MPI_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi_msix_vec#_addr
 *
 * MPI/SPI MSI-X Vector Table Address Registers
 * This register is the MSI-X vector table, indexed by the MPI_INT_VEC_E enumeration.
 */
union bdk_mpi_msix_vecx_addr
{
    uint64_t u;
    struct bdk_mpi_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MPI_MSIX_VEC()_ADDR, MPI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MPI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MPI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's MPI_MSIX_VEC()_ADDR, MPI_MSIX_VEC()_CTL, and corresponding
                                                                 bit of MPI_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_MPI_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_msix_vecx_addr_s cn; */
};
typedef union bdk_mpi_msix_vecx_addr bdk_mpi_msix_vecx_addr_t;

static inline uint64_t BDK_MPI_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_MSIX_VECX_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a==0))
        return 0x804000f00000ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("MPI_MSIX_VECX_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPI_MSIX_VECX_ADDR(a) bdk_mpi_msix_vecx_addr_t
#define bustype_BDK_MPI_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_MSIX_VECX_ADDR(a) "MPI_MSIX_VECX_ADDR"
#define device_bar_BDK_MPI_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MPI_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_MPI_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi_msix_vec#_ctl
 *
 * MPI/SPI MSI-X Vector Table Control and Data Registers
 * This register is the MSI-X vector table, indexed by the MPI_INT_VEC_E enumeration.
 */
union bdk_mpi_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_mpi_msix_vecx_ctl_s
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
    /* struct bdk_mpi_msix_vecx_ctl_s cn; */
};
typedef union bdk_mpi_msix_vecx_ctl bdk_mpi_msix_vecx_ctl_t;

static inline uint64_t BDK_MPI_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_MSIX_VECX_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX) && (a==0))
        return 0x804000f00008ll + 0x10ll * ((a) & 0x0);
    __bdk_csr_fatal("MPI_MSIX_VECX_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_MPI_MSIX_VECX_CTL(a) bdk_mpi_msix_vecx_ctl_t
#define bustype_BDK_MPI_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_MSIX_VECX_CTL(a) "MPI_MSIX_VECX_CTL"
#define device_bar_BDK_MPI_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_MPI_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_MPI_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) mpi_sts
 *
 * MPI/SPI STS Register
 */
union bdk_mpi_sts
{
    uint64_t u;
    struct bdk_mpi_sts_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t rxnum                 : 5;  /**< [ 12:  8](RO/H) Actual number of bytes received for the transaction. */
        uint64_t reserved_2_7          : 6;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1C/H) MPI interrupt on transaction done.  This interrupt should be cleared
                                                                 before any new SPI/MPI transaction is requested. */
        uint64_t busy                  : 1;  /**< [  0:  0](RO/H) Busy.
                                                                 0 = No MPI/SPI transaction in progress.
                                                                 1 = MPI/SPI engine is processing a transaction. */
#else /* Word 0 - Little Endian */
        uint64_t busy                  : 1;  /**< [  0:  0](RO/H) Busy.
                                                                 0 = No MPI/SPI transaction in progress.
                                                                 1 = MPI/SPI engine is processing a transaction. */
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1C/H) MPI interrupt on transaction done.  This interrupt should be cleared
                                                                 before any new SPI/MPI transaction is requested. */
        uint64_t reserved_2_7          : 6;
        uint64_t rxnum                 : 5;  /**< [ 12:  8](RO/H) Actual number of bytes received for the transaction. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_sts_s cn; */
};
typedef union bdk_mpi_sts bdk_mpi_sts_t;

#define BDK_MPI_STS BDK_MPI_STS_FUNC()
static inline uint64_t BDK_MPI_STS_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_STS_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x804000001008ll;
    __bdk_csr_fatal("MPI_STS", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MPI_STS bdk_mpi_sts_t
#define bustype_BDK_MPI_STS BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_STS "MPI_STS"
#define device_bar_BDK_MPI_STS 0x0 /* PF_BAR0 */
#define busnum_BDK_MPI_STS 0
#define arguments_BDK_MPI_STS -1,-1,-1,-1

/**
 * Register (NCB) mpi_sts_w1s
 *
 * MPI Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_mpi_sts_w1s
{
    uint64_t u;
    struct bdk_mpi_sts_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MPI_STS[MPI_INTR]. */
        uint64_t reserved_0            : 1;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0            : 1;
        uint64_t mpi_intr              : 1;  /**< [  1:  1](R/W1S/H) Reads or sets MPI_STS[MPI_INTR]. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_sts_w1s_s cn; */
};
typedef union bdk_mpi_sts_w1s bdk_mpi_sts_w1s_t;

#define BDK_MPI_STS_W1S BDK_MPI_STS_W1S_FUNC()
static inline uint64_t BDK_MPI_STS_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_STS_W1S_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x804000001020ll;
    __bdk_csr_fatal("MPI_STS_W1S", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MPI_STS_W1S bdk_mpi_sts_w1s_t
#define bustype_BDK_MPI_STS_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_STS_W1S "MPI_STS_W1S"
#define device_bar_BDK_MPI_STS_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_MPI_STS_W1S 0
#define arguments_BDK_MPI_STS_W1S -1,-1,-1,-1

/**
 * Register (NCB) mpi_tx
 *
 * MPI/SPI Transmit Register
 */
union bdk_mpi_tx
{
    uint64_t u;
    struct bdk_mpi_tx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_22_63        : 42;
        uint64_t csid                  : 2;  /**< [ 21: 20](WO) Which CS to assert for this transaction. */
        uint64_t reserved_17_19        : 3;
        uint64_t leavecs               : 1;  /**< [ 16: 16](WO) Leave SPI_CSn_L asserted.
                                                                 0 = Deassert SPI_CSn_L after the transaction is done.
                                                                 1 = Leave SPI_CSn_L asserted after the transaction is done. */
        uint64_t reserved_13_15        : 3;
        uint64_t txnum                 : 5;  /**< [ 12:  8](WO) Number of bytes to transmit. */
        uint64_t reserved_5_7          : 3;
        uint64_t totnum                : 5;  /**< [  4:  0](WO) Total number of bytes to shift (transmit and receive). */
#else /* Word 0 - Little Endian */
        uint64_t totnum                : 5;  /**< [  4:  0](WO) Total number of bytes to shift (transmit and receive). */
        uint64_t reserved_5_7          : 3;
        uint64_t txnum                 : 5;  /**< [ 12:  8](WO) Number of bytes to transmit. */
        uint64_t reserved_13_15        : 3;
        uint64_t leavecs               : 1;  /**< [ 16: 16](WO) Leave SPI_CSn_L asserted.
                                                                 0 = Deassert SPI_CSn_L after the transaction is done.
                                                                 1 = Leave SPI_CSn_L asserted after the transaction is done. */
        uint64_t reserved_17_19        : 3;
        uint64_t csid                  : 2;  /**< [ 21: 20](WO) Which CS to assert for this transaction. */
        uint64_t reserved_22_63        : 42;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_tx_s cn; */
};
typedef union bdk_mpi_tx bdk_mpi_tx_t;

#define BDK_MPI_TX BDK_MPI_TX_FUNC()
static inline uint64_t BDK_MPI_TX_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_TX_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x804000001010ll;
    __bdk_csr_fatal("MPI_TX", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MPI_TX bdk_mpi_tx_t
#define bustype_BDK_MPI_TX BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_TX "MPI_TX"
#define device_bar_BDK_MPI_TX 0x0 /* PF_BAR0 */
#define busnum_BDK_MPI_TX 0
#define arguments_BDK_MPI_TX -1,-1,-1,-1

/**
 * Register (NCB) mpi_wide_dat
 *
 * MPI/SPI Wide Data Register
 */
union bdk_mpi_wide_dat
{
    uint64_t u;
    struct bdk_mpi_wide_dat_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Data to transmit/receive. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 64; /**< [ 63:  0](R/W/H) Data to transmit/receive. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_mpi_wide_dat_s cn; */
};
typedef union bdk_mpi_wide_dat bdk_mpi_wide_dat_t;

#define BDK_MPI_WIDE_DAT BDK_MPI_WIDE_DAT_FUNC()
static inline uint64_t BDK_MPI_WIDE_DAT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_MPI_WIDE_DAT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
        return 0x804000001040ll;
    __bdk_csr_fatal("MPI_WIDE_DAT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_MPI_WIDE_DAT bdk_mpi_wide_dat_t
#define bustype_BDK_MPI_WIDE_DAT BDK_CSR_TYPE_NCB
#define basename_BDK_MPI_WIDE_DAT "MPI_WIDE_DAT"
#define device_bar_BDK_MPI_WIDE_DAT 0x0 /* PF_BAR0 */
#define busnum_BDK_MPI_WIDE_DAT 0
#define arguments_BDK_MPI_WIDE_DAT -1,-1,-1,-1

#endif /* __BDK_CSRS_MPI_H__ */
