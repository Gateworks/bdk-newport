#ifndef __BDK_CSRS_NDF_H__
#define __BDK_CSRS_NDF_H__
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
 * OcteonTX NDF.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration ndf_bar_e
 *
 * NAND Flash Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_NDF_BAR_E_NDF_PF_BAR0_CN8 (0x808000000000ll)
#define BDK_NDF_BAR_E_NDF_PF_BAR0_CN8_SIZE 0x100000ull
#define BDK_NDF_BAR_E_NDF_PF_BAR0_CN9 (0x808000000000ll)
#define BDK_NDF_BAR_E_NDF_PF_BAR0_CN9_SIZE 0x10000ull
#define BDK_NDF_BAR_E_NDF_PF_BAR4 (0x808000f00000ll)
#define BDK_NDF_BAR_E_NDF_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration ndf_int_vec_e
 *
 * NAND Flash MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_NDF_INT_VEC_E_INTR (0)
#define BDK_NDF_INT_VEC_E_NCB_RAS (1)

/**
 * Register (NCB) ndf_bt_pg_info
 *
 * INTERNAL: NAND Flash Page Information Register
 *
 * This register provides the page size and the number of column-plus-row address-cycle
 * information. Software writes to this register during a boot operation from a NAND flash
 * device.
 *
 * Additionally, software also writes the multiplier value for timing parameters that is used
 * during the boot process, in the SET_TM_PARAM command. The multiplier value is used only by the
 * boot-load state machine during boot operations. Boot DMA operations do not use this value.
 *
 * Sixty-four-bit operations must be used to access this register.
 */
union bdk_ndf_bt_pg_info
{
    uint64_t u;
    struct bdk_ndf_bt_pg_info_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_11_63        : 53;
        uint64_t t_mult                : 4;  /**< [ 10:  7](R/W) The boot-time TIM_MULT field of the SET_TM_PARAM command. */
        uint64_t adr_cyc               : 4;  /**< [  6:  3](R/W) Number of column-address cycles. Legal values are 0x3 - 0x8. Values written to this field
                                                                 smaller than 0x3 are converted to 0x3; values larger than 0x8 are converted to 0x8. */
        uint64_t size                  : 3;  /**< [  2:  0](R/W) Number of bytes per page in the NAND flash device = 2^SIZE+1 * 256.
                                                                 0x0 = 512 bytes/page.
                                                                 0x1 = 1 KB/page.
                                                                 0x2 = 2 KB/page.
                                                                 0x3 = 4 KB/page.
                                                                 0x4 = 8 KB/page.
                                                                 0x5 = 16 KB/page.
                                                                 0x6 = 32 KB/page.
                                                                 0x7 = 64 KB/page. */
#else /* Word 0 - Little Endian */
        uint64_t size                  : 3;  /**< [  2:  0](R/W) Number of bytes per page in the NAND flash device = 2^SIZE+1 * 256.
                                                                 0x0 = 512 bytes/page.
                                                                 0x1 = 1 KB/page.
                                                                 0x2 = 2 KB/page.
                                                                 0x3 = 4 KB/page.
                                                                 0x4 = 8 KB/page.
                                                                 0x5 = 16 KB/page.
                                                                 0x6 = 32 KB/page.
                                                                 0x7 = 64 KB/page. */
        uint64_t adr_cyc               : 4;  /**< [  6:  3](R/W) Number of column-address cycles. Legal values are 0x3 - 0x8. Values written to this field
                                                                 smaller than 0x3 are converted to 0x3; values larger than 0x8 are converted to 0x8. */
        uint64_t t_mult                : 4;  /**< [ 10:  7](R/W) The boot-time TIM_MULT field of the SET_TM_PARAM command. */
        uint64_t reserved_11_63        : 53;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_bt_pg_info_s cn; */
};
typedef union bdk_ndf_bt_pg_info bdk_ndf_bt_pg_info_t;

#define BDK_NDF_BT_PG_INFO BDK_NDF_BT_PG_INFO_FUNC()
static inline uint64_t BDK_NDF_BT_PG_INFO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_BT_PG_INFO_FUNC(void)
{
    return 0x808000000018ll;
}

#define typedef_BDK_NDF_BT_PG_INFO bdk_ndf_bt_pg_info_t
#define bustype_BDK_NDF_BT_PG_INFO BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_BT_PG_INFO "NDF_BT_PG_INFO"
#define device_bar_BDK_NDF_BT_PG_INFO 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_BT_PG_INFO 0
#define arguments_BDK_NDF_BT_PG_INFO -1,-1,-1,-1

/**
 * Register (NCB) ndf_cmd
 *
 * NAND Flash Command Register
 * When software reads this register, NDF_MISC[RD_VAL] is cleared to 0. Software must always
 * write all eight bytes whenever it writes this register. If there are fewer than eight bytes
 * left in the command sequence that software wants the NAND flash controller to execute, it must
 * insert idle (WAIT) commands to make up eight bytes. Software must also ensure that there is
 * enough space in the NDF_CMD queue to accept these eight bytes by first reading
 * NDF_MISC[FR_BYT].
 *
 * Sixty-four-bit operations must be used to access this register.
 */
union bdk_ndf_cmd
{
    uint64_t u;
    struct bdk_ndf_cmd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t nf_cmd                : 64; /**< [ 63:  0](R/W) Eight NAND flash memory command bytes. */
#else /* Word 0 - Little Endian */
        uint64_t nf_cmd                : 64; /**< [ 63:  0](R/W) Eight NAND flash memory command bytes. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_cmd_s cn; */
};
typedef union bdk_ndf_cmd bdk_ndf_cmd_t;

#define BDK_NDF_CMD BDK_NDF_CMD_FUNC()
static inline uint64_t BDK_NDF_CMD_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_CMD_FUNC(void)
{
    return 0x808000000000ll;
}

#define typedef_BDK_NDF_CMD bdk_ndf_cmd_t
#define bustype_BDK_NDF_CMD BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_CMD "NDF_CMD"
#define device_bar_BDK_NDF_CMD 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_CMD 0
#define arguments_BDK_NDF_CMD -1,-1,-1,-1

/**
 * Register (NCB) ndf_debug
 *
 * NDF Debug Register
 */
union bdk_ndf_debug
{
    uint64_t u;
    struct bdk_ndf_debug_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force NDF related conditional clocks to always be on.
                                                                 For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clk_on                : 1;  /**< [  0:  0](R/W) Force NDF related conditional clocks to always be on.
                                                                 For diagnostic use only. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_debug_s cn; */
};
typedef union bdk_ndf_debug bdk_ndf_debug_t;

#define BDK_NDF_DEBUG BDK_NDF_DEBUG_FUNC()
static inline uint64_t BDK_NDF_DEBUG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_DEBUG_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x8080000000f8ll;
    __bdk_csr_fatal("NDF_DEBUG", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDF_DEBUG bdk_ndf_debug_t
#define bustype_BDK_NDF_DEBUG BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_DEBUG "NDF_DEBUG"
#define device_bar_BDK_NDF_DEBUG 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_DEBUG 0
#define arguments_BDK_NDF_DEBUG -1,-1,-1,-1

/**
 * Register (NCB) ndf_dma_adr
 *
 * NAND Flash DMA Address Register
 * Sixty-four-bit operations must be used to access this register.
 */
union bdk_ndf_dma_adr
{
    uint64_t u;
    struct bdk_ndf_dma_adr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t adr                   : 50; /**< [ 52:  3](R/W/H) DMA engine IOVA. 64-bit aligned. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t adr                   : 50; /**< [ 52:  3](R/W/H) DMA engine IOVA. 64-bit aligned. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_ndf_dma_adr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t adr                   : 46; /**< [ 48:  3](R/W/H) DMA engine IOVA. 64-bit aligned. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t adr                   : 46; /**< [ 48:  3](R/W/H) DMA engine IOVA. 64-bit aligned. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ndf_dma_adr_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t adr                   : 50; /**< [ 52:  3](R/W/H) DMA engine IOVA. 128-bit aligned. Addr\<3\> must be 0. */
        uint64_t reserved_0_2          : 3;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_2          : 3;
        uint64_t adr                   : 50; /**< [ 52:  3](R/W/H) DMA engine IOVA. 128-bit aligned. Addr\<3\> must be 0. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ndf_dma_adr bdk_ndf_dma_adr_t;

#define BDK_NDF_DMA_ADR BDK_NDF_DMA_ADR_FUNC()
static inline uint64_t BDK_NDF_DMA_ADR_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_DMA_ADR_FUNC(void)
{
    return 0x808000000058ll;
}

#define typedef_BDK_NDF_DMA_ADR bdk_ndf_dma_adr_t
#define bustype_BDK_NDF_DMA_ADR BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_DMA_ADR "NDF_DMA_ADR"
#define device_bar_BDK_NDF_DMA_ADR 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_DMA_ADR 0
#define arguments_BDK_NDF_DMA_ADR -1,-1,-1,-1

/**
 * Register (NCB) ndf_dma_cfg
 *
 * NAND Flash DMA Configuration Register
 * Sixty-four-bit operations must be used to access this register.
 */
union bdk_ndf_dma_cfg
{
    uint64_t u;
    struct bdk_ndf_dma_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t en                    : 1;  /**< [ 63: 63](R/W/H) DMA engine enable.  This bit is cleared at the termination of the DMA. */
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W) DMA engine R/W bit: 0 = read, 1 = write. */
        uint64_t clr                   : 1;  /**< [ 61: 61](R/W) DMA engine clear EN. When set to 1, DMA is terminated and EN is cleared and the
                                                                 NDF_INT[DMA_DONE] interrupt occurs when either the [SIZE] is exhausted (normal
                                                                 termination) or the NDF BUS_REL is issued. */
        uint64_t reserved_60           : 1;
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W) DMA engine 32-bit swap enable.  See [CMD_BE]. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W) DMA engine 16-bit swap enable.  See [CMD_BE]. */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W) DMA engine 8-bit swap enable.  See [CMD_BE]. */
        uint64_t cmd_be                : 1;  /**< [ 56: 56](R/W) DMA engine command-queue endian mode: 0 = little-endian, 1 = big-endian.
                                                                 Using 0..7 to identify bytes:
                                                                 \<pre\>
                                                                 [SWAP32] [SWAP16] [SWAP8] [CMD_BE]  Result
                                                                    0        0        0      0       7 6 5 4 3 2 1 0
                                                                    0        0        1      0       6 7 4 5 2 3 0 1
                                                                    0        1        0      0       5 4 7 6 1 0 3 2
                                                                    1        0        0      0       3 2 1 0 7 6 5 4
                                                                    0        0        0      1       0 1 2 3 4 5 6 7
                                                                    0        0        1      1       1 0 3 2 5 4 7 6
                                                                    0        1        0      1       2 3 0 1 6 7 4 5
                                                                    1        0        0      1       4 5 6 7 0 1 2 3
                                                                 \</pre\> */
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine size. Specified in the number of 64-bit transfers (encoded in -1 notation). */
        uint64_t reserved_0_35         : 36;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_35         : 36;
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine size. Specified in the number of 64-bit transfers (encoded in -1 notation). */
        uint64_t cmd_be                : 1;  /**< [ 56: 56](R/W) DMA engine command-queue endian mode: 0 = little-endian, 1 = big-endian.
                                                                 Using 0..7 to identify bytes:
                                                                 \<pre\>
                                                                 [SWAP32] [SWAP16] [SWAP8] [CMD_BE]  Result
                                                                    0        0        0      0       7 6 5 4 3 2 1 0
                                                                    0        0        1      0       6 7 4 5 2 3 0 1
                                                                    0        1        0      0       5 4 7 6 1 0 3 2
                                                                    1        0        0      0       3 2 1 0 7 6 5 4
                                                                    0        0        0      1       0 1 2 3 4 5 6 7
                                                                    0        0        1      1       1 0 3 2 5 4 7 6
                                                                    0        1        0      1       2 3 0 1 6 7 4 5
                                                                    1        0        0      1       4 5 6 7 0 1 2 3
                                                                 \</pre\> */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W) DMA engine 8-bit swap enable.  See [CMD_BE]. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W) DMA engine 16-bit swap enable.  See [CMD_BE]. */
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W) DMA engine 32-bit swap enable.  See [CMD_BE]. */
        uint64_t reserved_60           : 1;
        uint64_t clr                   : 1;  /**< [ 61: 61](R/W) DMA engine clear EN. When set to 1, DMA is terminated and EN is cleared and the
                                                                 NDF_INT[DMA_DONE] interrupt occurs when either the [SIZE] is exhausted (normal
                                                                 termination) or the NDF BUS_REL is issued. */
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W) DMA engine R/W bit: 0 = read, 1 = write. */
        uint64_t en                    : 1;  /**< [ 63: 63](R/W/H) DMA engine enable.  This bit is cleared at the termination of the DMA. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_dma_cfg_s cn8; */
    struct bdk_ndf_dma_cfg_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t en                    : 1;  /**< [ 63: 63](R/W/H) DMA engine enable.  This bit is cleared at the termination of the DMA.
                                                                 It should also be cleared and the DMA cleaned up if core domain reset asserts. */
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W) DMA engine R/W bit: 0 = read, 1 = write. */
        uint64_t clr                   : 1;  /**< [ 61: 61](R/W) DMA engine clear EN. When set to 1, DMA is terminated and EN is cleared and the
                                                                 NDF_INT[DMA_DONE] interrupt occurs when either the [SIZE] is exhausted (normal
                                                                 termination) or the NDF BUS_REL is issued. */
        uint64_t reserved_60           : 1;
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W) DMA engine 32-bit swap enable.  See [CMD_BE]. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W) DMA engine 16-bit swap enable.  See [CMD_BE]. */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W) DMA engine 8-bit swap enable.  See [CMD_BE]. */
        uint64_t cmd_be                : 1;  /**< [ 56: 56](R/W) DMA engine command-queue endian mode: 0 = little-endian, 1 = big-endian.
                                                                 Using 0..7 to identify bytes:
                                                                 \<pre\>
                                                                 [SWAP32] [SWAP16] [SWAP8] [CMD_BE]  Result
                                                                    0        0        0      0       7 6 5 4 3 2 1 0
                                                                    0        0        1      0       6 7 4 5 2 3 0 1
                                                                    0        1        0      0       5 4 7 6 1 0 3 2
                                                                    1        0        0      0       3 2 1 0 7 6 5 4
                                                                    0        0        0      1       0 1 2 3 4 5 6 7
                                                                    0        0        1      1       1 0 3 2 5 4 7 6
                                                                    0        1        0      1       2 3 0 1 6 7 4 5
                                                                    1        0        0      1       4 5 6 7 0 1 2 3
                                                                 \</pre\> */
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine size. Specified in the number of 64-bit transfers (encoded in -1 notation). */
        uint64_t reserved_0_35         : 36;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_35         : 36;
        uint64_t size                  : 20; /**< [ 55: 36](R/W/H) DMA engine size. Specified in the number of 64-bit transfers (encoded in -1 notation). */
        uint64_t cmd_be                : 1;  /**< [ 56: 56](R/W) DMA engine command-queue endian mode: 0 = little-endian, 1 = big-endian.
                                                                 Using 0..7 to identify bytes:
                                                                 \<pre\>
                                                                 [SWAP32] [SWAP16] [SWAP8] [CMD_BE]  Result
                                                                    0        0        0      0       7 6 5 4 3 2 1 0
                                                                    0        0        1      0       6 7 4 5 2 3 0 1
                                                                    0        1        0      0       5 4 7 6 1 0 3 2
                                                                    1        0        0      0       3 2 1 0 7 6 5 4
                                                                    0        0        0      1       0 1 2 3 4 5 6 7
                                                                    0        0        1      1       1 0 3 2 5 4 7 6
                                                                    0        1        0      1       2 3 0 1 6 7 4 5
                                                                    1        0        0      1       4 5 6 7 0 1 2 3
                                                                 \</pre\> */
        uint64_t swap8                 : 1;  /**< [ 57: 57](R/W) DMA engine 8-bit swap enable.  See [CMD_BE]. */
        uint64_t swap16                : 1;  /**< [ 58: 58](R/W) DMA engine 16-bit swap enable.  See [CMD_BE]. */
        uint64_t swap32                : 1;  /**< [ 59: 59](R/W) DMA engine 32-bit swap enable.  See [CMD_BE]. */
        uint64_t reserved_60           : 1;
        uint64_t clr                   : 1;  /**< [ 61: 61](R/W) DMA engine clear EN. When set to 1, DMA is terminated and EN is cleared and the
                                                                 NDF_INT[DMA_DONE] interrupt occurs when either the [SIZE] is exhausted (normal
                                                                 termination) or the NDF BUS_REL is issued. */
        uint64_t rw                    : 1;  /**< [ 62: 62](R/W) DMA engine R/W bit: 0 = read, 1 = write. */
        uint64_t en                    : 1;  /**< [ 63: 63](R/W/H) DMA engine enable.  This bit is cleared at the termination of the DMA.
                                                                 It should also be cleared and the DMA cleaned up if core domain reset asserts. */
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ndf_dma_cfg bdk_ndf_dma_cfg_t;

#define BDK_NDF_DMA_CFG BDK_NDF_DMA_CFG_FUNC()
static inline uint64_t BDK_NDF_DMA_CFG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_DMA_CFG_FUNC(void)
{
    return 0x808000000050ll;
}

#define typedef_BDK_NDF_DMA_CFG bdk_ndf_dma_cfg_t
#define bustype_BDK_NDF_DMA_CFG BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_DMA_CFG "NDF_DMA_CFG"
#define device_bar_BDK_NDF_DMA_CFG 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_DMA_CFG 0
#define arguments_BDK_NDF_DMA_CFG -1,-1,-1,-1

/**
 * Register (NCB) ndf_drbell
 *
 * NAND Flash Doorbell Register
 * This register is designed to control the execution of the NAND flash commands. The NDF
 * command-execution unit must arbitrate for the pbus before it can enable a NAND flash
 * device connected to the CNXXXX, which it then does by asserting the device's chip-enable
 * signal. Therefore software must first load the NDF_CMD queue, with a full sequence of commands
 * to perform a NAND flash device task.
 *
 * This command sequence starts with a BUS_ACQ command, and the last command in the sequence must
 * be a BUS_REL command. The execution unit starts execution of the sequence only if the
 * NDF_DRBELL[CNT] is nonzero when it fetches the BUS_ACQ command.
 *
 * Software can load multiple such sequences, each starting with a CHIP_EN command and
 * ending with a CHIP_DIS command, and then write a data value to this register to
 * increment [CNT] by the number of the command sequences loaded to the NDF_CMD queue.
 *
 * Software register-write operations increment [CNT] by the signed 8-bit value being written.
 * Software register-read operations return the current [CNT] value.
 *
 * Hardware can also modifies the value of [CNT]. Every time hardware executes a BUS_ACQ command
 * to
 * arbitrate and win the pbus, it decrements [CNT] by 1. If [CNT] is already 0 or negative, the
 * hardware command-execution unit stalls when it fetches the new BUS_ACQ command from the
 * NDF_CMD queue. Only when the software writes to this register with a nonzero data value can
 * the execution unit come out of the stalled condition, and resume execution.
 *
 * Sixty-four-bit operations must be used to access this register.
 */
union bdk_ndf_drbell
{
    uint64_t u;
    struct bdk_ndf_drbell_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t cnt                   : 8;  /**< [  7:  0](R/W/H) Doorbell count, in 2s-complement format. */
#else /* Word 0 - Little Endian */
        uint64_t cnt                   : 8;  /**< [  7:  0](R/W/H) Doorbell count, in 2s-complement format. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_drbell_s cn; */
};
typedef union bdk_ndf_drbell bdk_ndf_drbell_t;

#define BDK_NDF_DRBELL BDK_NDF_DRBELL_FUNC()
static inline uint64_t BDK_NDF_DRBELL_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_DRBELL_FUNC(void)
{
    return 0x808000000030ll;
}

#define typedef_BDK_NDF_DRBELL bdk_ndf_drbell_t
#define bustype_BDK_NDF_DRBELL BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_DRBELL "NDF_DRBELL"
#define device_bar_BDK_NDF_DRBELL 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_DRBELL 0
#define arguments_BDK_NDF_DRBELL -1,-1,-1,-1

/**
 * Register (NCB) ndf_ecc_cnt
 *
 * NAND Flash ECC Count Register
 * Sixty-four-bit operations must be used to access this register.
 */
union bdk_ndf_ecc_cnt
{
    uint64_t u;
    struct bdk_ndf_ecc_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t xor_ecc               : 24; /**< [ 31:  8](RO/H) Result of XOR operation of ECC read bytes and ECC generated bytes. The value pertains to
                                                                 the last single-bit ECC error.

                                                                 _ [XOR_ECC] = {ECC_gen_byt258, ECC_gen_byt257, ECC_gen_byt256} ^
                                                                   {ECC_258, ECC_257, ECC_256}

                                                                 ECC_258, ECC_257 and ECC_256 are bytes stored in the NAND flash device and read out during
                                                                 boot.

                                                                 ECC_gen_byt258, ECC_gen_byt257, ECC_gen_byt256 are generated from data read out from the
                                                                 NAND flash device. */
        uint64_t ecc_err               : 8;  /**< [  7:  0](RO/H) ECC error count. The number of single-bit errors fixed. */
#else /* Word 0 - Little Endian */
        uint64_t ecc_err               : 8;  /**< [  7:  0](RO/H) ECC error count. The number of single-bit errors fixed. */
        uint64_t xor_ecc               : 24; /**< [ 31:  8](RO/H) Result of XOR operation of ECC read bytes and ECC generated bytes. The value pertains to
                                                                 the last single-bit ECC error.

                                                                 _ [XOR_ECC] = {ECC_gen_byt258, ECC_gen_byt257, ECC_gen_byt256} ^
                                                                   {ECC_258, ECC_257, ECC_256}

                                                                 ECC_258, ECC_257 and ECC_256 are bytes stored in the NAND flash device and read out during
                                                                 boot.

                                                                 ECC_gen_byt258, ECC_gen_byt257, ECC_gen_byt256 are generated from data read out from the
                                                                 NAND flash device. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_ecc_cnt_s cn; */
};
typedef union bdk_ndf_ecc_cnt bdk_ndf_ecc_cnt_t;

#define BDK_NDF_ECC_CNT BDK_NDF_ECC_CNT_FUNC()
static inline uint64_t BDK_NDF_ECC_CNT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_ECC_CNT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
        return 0x808000000010ll;
    __bdk_csr_fatal("NDF_ECC_CNT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDF_ECC_CNT bdk_ndf_ecc_cnt_t
#define bustype_BDK_NDF_ECC_CNT BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_ECC_CNT "NDF_ECC_CNT"
#define device_bar_BDK_NDF_ECC_CNT 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_ECC_CNT 0
#define arguments_BDK_NDF_ECC_CNT -1,-1,-1,-1

/**
 * Register (NCB) ndf_eco
 *
 * INTERNAL: NAND Flash ECO Register
 */
union bdk_ndf_eco
{
    uint64_t u;
    struct bdk_ndf_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) ECO flops. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_eco_s cn; */
};
typedef union bdk_ndf_eco bdk_ndf_eco_t;

#define BDK_NDF_ECO BDK_NDF_ECO_FUNC()
static inline uint64_t BDK_NDF_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_ECO_FUNC(void)
{
    return 0x808000000078ll;
}

#define typedef_BDK_NDF_ECO bdk_ndf_eco_t
#define bustype_BDK_NDF_ECO BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_ECO "NDF_ECO"
#define device_bar_BDK_NDF_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_ECO 0
#define arguments_BDK_NDF_ECO -1,-1,-1,-1

/**
 * Register (NCB) ndf_int
 *
 * NAND Flash Interrupt Register
 * This register contains the bits that can trigger an error interrupt. Sixty-four-bit operations
 * must be used to access this register.
 */
union bdk_ndf_int
{
    uint64_t u;
    struct bdk_ndf_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1C/H) NCB write failure.  Read Data from NDF device failed to reach memory.
                                                                 NDF_DMA_CFG may need clearing.  This is generally a fatal error that requires
                                                                 the core domain to be reset. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1C/H) Fault received on NCB read request. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) DMA engine request completion interrupt. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) NDF_CMD write when FIFO is full. Generally a fatal error. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1C/H) Multibit ECC error detected. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1C/H) Single-bit ECC error detected and fixed. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) One of the state machines is in a bad state, */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Watchdog timer expired during command execution. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) NDF_CMD queue is full. FULL status is updated when the NDF_CMD queue becomes full as a
                                                                 result of software writing a new command to it. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) NDF_CMD queue is empty. EMPTY status is updated when the NDF_CMD queue becomes empty as a
                                                                 result of command execution unit fetching the last instruction out of the NDF_CMD queue. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) NDF_CMD queue is empty. EMPTY status is updated when the NDF_CMD queue becomes empty as a
                                                                 result of command execution unit fetching the last instruction out of the NDF_CMD queue. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) NDF_CMD queue is full. FULL status is updated when the NDF_CMD queue becomes full as a
                                                                 result of software writing a new command to it. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Watchdog timer expired during command execution. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) One of the state machines is in a bad state, */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1C/H) Single-bit ECC error detected and fixed. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1C/H) Multibit ECC error detected. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) NDF_CMD write when FIFO is full. Generally a fatal error. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) DMA engine request completion interrupt. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1C/H) Fault received on NCB read request. */
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1C/H) NCB write failure.  Read Data from NDF device failed to reach memory.
                                                                 NDF_DMA_CFG may need clearing.  This is generally a fatal error that requires
                                                                 the core domain to be reset. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    struct bdk_ndf_int_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) DMA engine request completion interrupt. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) NDF_CMD write when FIFO is full. Generally a fatal error. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1C/H) Multibit ECC error detected. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1C/H) Single-bit ECC error detected and fixed. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) One of the state machines is in a bad state, */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Watchdog timer expired during command execution. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) NDF_CMD queue is full. FULL status is updated when the NDF_CMD queue becomes full as a
                                                                 result of software writing a new command to it. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) NDF_CMD queue is empty. EMPTY status is updated when the NDF_CMD queue becomes empty as a
                                                                 result of command execution unit fetching the last instruction out of the NDF_CMD queue. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) NDF_CMD queue is empty. EMPTY status is updated when the NDF_CMD queue becomes empty as a
                                                                 result of command execution unit fetching the last instruction out of the NDF_CMD queue. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) NDF_CMD queue is full. FULL status is updated when the NDF_CMD queue becomes full as a
                                                                 result of software writing a new command to it. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Watchdog timer expired during command execution. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) One of the state machines is in a bad state, */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1C/H) Single-bit ECC error detected and fixed. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1C/H) Multibit ECC error detected. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) NDF_CMD write when FIFO is full. Generally a fatal error. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) DMA engine request completion interrupt. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ndf_int_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1C/H) NCB write failure.  Read Data from NDF device failed to reach memory.
                                                                 NDF_DMA_CFG may need clearing.  This is generally a fatal error that requires
                                                                 the core domain to be reset. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1C/H) Fault received on NCB read request. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) DMA engine request completion interrupt. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) NDF_CMD write when FIFO is full. Generally a fatal error. */
        uint64_t reserved_4_5          : 2;
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) One of the state machines is in a bad state, */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Watchdog timer expired during command execution. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) NDF_CMD queue is full. FULL status is updated when the NDF_CMD queue becomes full as a
                                                                 result of software writing a new command to it. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) NDF_CMD queue is empty. EMPTY status is updated when the NDF_CMD queue becomes empty as a
                                                                 result of command execution unit fetching the last instruction out of the NDF_CMD queue. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) NDF_CMD queue is empty. EMPTY status is updated when the NDF_CMD queue becomes empty as a
                                                                 result of command execution unit fetching the last instruction out of the NDF_CMD queue. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) NDF_CMD queue is full. FULL status is updated when the NDF_CMD queue becomes full as a
                                                                 result of software writing a new command to it. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Watchdog timer expired during command execution. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) One of the state machines is in a bad state, */
        uint64_t reserved_4_5          : 2;
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) NDF_CMD write when FIFO is full. Generally a fatal error. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) DMA engine request completion interrupt. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1C/H) Fault received on NCB read request. */
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1C/H) NCB write failure.  Read Data from NDF device failed to reach memory.
                                                                 NDF_DMA_CFG may need clearing.  This is generally a fatal error that requires
                                                                 the core domain to be reset. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ndf_int bdk_ndf_int_t;

#define BDK_NDF_INT BDK_NDF_INT_FUNC()
static inline uint64_t BDK_NDF_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_INT_FUNC(void)
{
    return 0x808000000040ll;
}

#define typedef_BDK_NDF_INT bdk_ndf_int_t
#define bustype_BDK_NDF_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_INT "NDF_INT"
#define device_bar_BDK_NDF_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_INT 0
#define arguments_BDK_NDF_INT -1,-1,-1,-1

/**
 * Register (NCB) ndf_int_ena_w1c
 *
 * NAND Flash Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_ndf_int_ena_w1c
{
    uint64_t u;
    struct bdk_ndf_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for NDF_INT[NCB_OVERFLOW]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NDF_INT[NCB_FLT]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NDF_INT[DMA_DONE]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NDF_INT[OVRF]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NDF_INT[ECC_MULT]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NDF_INT[ECC_1BIT]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NDF_INT[SM_BAD]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NDF_INT[WDOG]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NDF_INT[FULL]. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NDF_INT[EMPTY]. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NDF_INT[EMPTY]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NDF_INT[FULL]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NDF_INT[WDOG]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NDF_INT[SM_BAD]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NDF_INT[ECC_1BIT]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NDF_INT[ECC_MULT]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NDF_INT[OVRF]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NDF_INT[DMA_DONE]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NDF_INT[NCB_FLT]. */
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for NDF_INT[NCB_OVERFLOW]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    struct bdk_ndf_int_ena_w1c_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NDF_INT[DMA_DONE]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NDF_INT[OVRF]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NDF_INT[ECC_MULT]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NDF_INT[ECC_1BIT]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NDF_INT[SM_BAD]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NDF_INT[WDOG]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NDF_INT[FULL]. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NDF_INT[EMPTY]. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NDF_INT[EMPTY]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NDF_INT[FULL]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NDF_INT[WDOG]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NDF_INT[SM_BAD]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1C/H) Reads or clears enable for NDF_INT[ECC_1BIT]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for NDF_INT[ECC_MULT]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NDF_INT[OVRF]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NDF_INT[DMA_DONE]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ndf_int_ena_w1c_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for NDF_INT[NCB_OVERFLOW]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NDF_INT[NCB_FLT]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NDF_INT[DMA_DONE]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NDF_INT[OVRF]. */
        uint64_t reserved_4_5          : 2;
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NDF_INT[SM_BAD]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NDF_INT[WDOG]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NDF_INT[FULL]. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NDF_INT[EMPTY]. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NDF_INT[EMPTY]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for NDF_INT[FULL]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for NDF_INT[WDOG]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1C/H) Reads or clears enable for NDF_INT[SM_BAD]. */
        uint64_t reserved_4_5          : 2;
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for NDF_INT[OVRF]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for NDF_INT[DMA_DONE]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1C/H) Reads or clears enable for NDF_INT[NCB_FLT]. */
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for NDF_INT[NCB_OVERFLOW]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ndf_int_ena_w1c bdk_ndf_int_ena_w1c_t;

#define BDK_NDF_INT_ENA_W1C BDK_NDF_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_NDF_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_INT_ENA_W1C_FUNC(void)
{
    return 0x808000000060ll;
}

#define typedef_BDK_NDF_INT_ENA_W1C bdk_ndf_int_ena_w1c_t
#define bustype_BDK_NDF_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_INT_ENA_W1C "NDF_INT_ENA_W1C"
#define device_bar_BDK_NDF_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_INT_ENA_W1C 0
#define arguments_BDK_NDF_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) ndf_int_ena_w1s
 *
 * NAND Flash Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_ndf_int_ena_w1s
{
    uint64_t u;
    struct bdk_ndf_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for NDF_INT[NCB_OVERFLOW]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NDF_INT[NCB_FLT]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NDF_INT[DMA_DONE]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NDF_INT[OVRF]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NDF_INT[ECC_MULT]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NDF_INT[ECC_1BIT]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NDF_INT[SM_BAD]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NDF_INT[WDOG]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NDF_INT[FULL]. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NDF_INT[EMPTY]. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NDF_INT[EMPTY]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NDF_INT[FULL]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NDF_INT[WDOG]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NDF_INT[SM_BAD]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NDF_INT[ECC_1BIT]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NDF_INT[ECC_MULT]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NDF_INT[OVRF]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NDF_INT[DMA_DONE]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NDF_INT[NCB_FLT]. */
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for NDF_INT[NCB_OVERFLOW]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    struct bdk_ndf_int_ena_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NDF_INT[DMA_DONE]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NDF_INT[OVRF]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NDF_INT[ECC_MULT]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NDF_INT[ECC_1BIT]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NDF_INT[SM_BAD]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NDF_INT[WDOG]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NDF_INT[FULL]. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NDF_INT[EMPTY]. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NDF_INT[EMPTY]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NDF_INT[FULL]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NDF_INT[WDOG]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NDF_INT[SM_BAD]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets enable for NDF_INT[ECC_1BIT]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for NDF_INT[ECC_MULT]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NDF_INT[OVRF]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NDF_INT[DMA_DONE]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ndf_int_ena_w1s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for NDF_INT[NCB_OVERFLOW]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NDF_INT[NCB_FLT]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NDF_INT[DMA_DONE]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NDF_INT[OVRF]. */
        uint64_t reserved_4_5          : 2;
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NDF_INT[SM_BAD]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NDF_INT[WDOG]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NDF_INT[FULL]. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NDF_INT[EMPTY]. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NDF_INT[EMPTY]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for NDF_INT[FULL]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for NDF_INT[WDOG]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets enable for NDF_INT[SM_BAD]. */
        uint64_t reserved_4_5          : 2;
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for NDF_INT[OVRF]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for NDF_INT[DMA_DONE]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets enable for NDF_INT[NCB_FLT]. */
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for NDF_INT[NCB_OVERFLOW]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ndf_int_ena_w1s bdk_ndf_int_ena_w1s_t;

#define BDK_NDF_INT_ENA_W1S BDK_NDF_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_NDF_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_INT_ENA_W1S_FUNC(void)
{
    return 0x808000000068ll;
}

#define typedef_BDK_NDF_INT_ENA_W1S bdk_ndf_int_ena_w1s_t
#define bustype_BDK_NDF_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_INT_ENA_W1S "NDF_INT_ENA_W1S"
#define device_bar_BDK_NDF_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_INT_ENA_W1S 0
#define arguments_BDK_NDF_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) ndf_int_w1s
 *
 * NAND Flash Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_ndf_int_w1s
{
    uint64_t u;
    struct bdk_ndf_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets NDF_INT[NCB_OVERFLOW]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NDF_INT[NCB_FLT]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NDF_INT[DMA_DONE]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NDF_INT[OVRF]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NDF_INT[ECC_MULT]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NDF_INT[ECC_1BIT]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NDF_INT[SM_BAD]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NDF_INT[WDOG]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NDF_INT[FULL]. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NDF_INT[EMPTY]. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NDF_INT[EMPTY]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NDF_INT[FULL]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NDF_INT[WDOG]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NDF_INT[SM_BAD]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NDF_INT[ECC_1BIT]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NDF_INT[ECC_MULT]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NDF_INT[OVRF]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NDF_INT[DMA_DONE]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NDF_INT[NCB_FLT]. */
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets NDF_INT[NCB_OVERFLOW]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    struct bdk_ndf_int_w1s_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NDF_INT[DMA_DONE]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NDF_INT[OVRF]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NDF_INT[ECC_MULT]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NDF_INT[ECC_1BIT]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NDF_INT[SM_BAD]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NDF_INT[WDOG]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NDF_INT[FULL]. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NDF_INT[EMPTY]. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NDF_INT[EMPTY]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NDF_INT[FULL]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NDF_INT[WDOG]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NDF_INT[SM_BAD]. */
        uint64_t ecc_1bit              : 1;  /**< [  4:  4](R/W1S/H) Reads or sets NDF_INT[ECC_1BIT]. */
        uint64_t ecc_mult              : 1;  /**< [  5:  5](R/W1S/H) Reads or sets NDF_INT[ECC_MULT]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NDF_INT[OVRF]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NDF_INT[DMA_DONE]. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } cn8;
    struct bdk_ndf_int_w1s_cn9
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets NDF_INT[NCB_OVERFLOW]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NDF_INT[NCB_FLT]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NDF_INT[DMA_DONE]. */
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NDF_INT[OVRF]. */
        uint64_t reserved_4_5          : 2;
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NDF_INT[SM_BAD]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NDF_INT[WDOG]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NDF_INT[FULL]. */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NDF_INT[EMPTY]. */
#else /* Word 0 - Little Endian */
        uint64_t empty                 : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NDF_INT[EMPTY]. */
        uint64_t full                  : 1;  /**< [  1:  1](R/W1S/H) Reads or sets NDF_INT[FULL]. */
        uint64_t wdog                  : 1;  /**< [  2:  2](R/W1S/H) Reads or sets NDF_INT[WDOG]. */
        uint64_t sm_bad                : 1;  /**< [  3:  3](R/W1S/H) Reads or sets NDF_INT[SM_BAD]. */
        uint64_t reserved_4_5          : 2;
        uint64_t ovrf                  : 1;  /**< [  6:  6](R/W1S/H) Reads or sets NDF_INT[OVRF]. */
        uint64_t dma_done              : 1;  /**< [  7:  7](R/W1S/H) Reads or sets NDF_INT[DMA_DONE]. */
        uint64_t ncb_flt               : 1;  /**< [  8:  8](R/W1S/H) Reads or sets NDF_INT[NCB_FLT]. */
        uint64_t ncb_overflow          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets NDF_INT[NCB_OVERFLOW]. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } cn9;
};
typedef union bdk_ndf_int_w1s bdk_ndf_int_w1s_t;

#define BDK_NDF_INT_W1S BDK_NDF_INT_W1S_FUNC()
static inline uint64_t BDK_NDF_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_INT_W1S_FUNC(void)
{
    return 0x808000000048ll;
}

#define typedef_BDK_NDF_INT_W1S bdk_ndf_int_w1s_t
#define bustype_BDK_NDF_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_INT_W1S "NDF_INT_W1S"
#define device_bar_BDK_NDF_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_INT_W1S 0
#define arguments_BDK_NDF_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) ndf_misc
 *
 * NAND Flash Miscellaneous Register
 * Sixty-four-bit operations must be used to access this register.
 */
union bdk_ndf_misc
{
    uint64_t u;
    struct bdk_ndf_misc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t mb_dis                : 1;  /**< [ 27: 27](R/W) Set to disable multi-bit error hangs. Allows loads and DMAs to proceed as if no
                                                                 multi-bit errors occurred. Hardware fixes single bit errors as usual. */
        uint64_t nbr_hwm               : 3;  /**< [ 26: 24](R/W) High watermark for NBR FIFO or load/store operations. Specifies the high
                                                                 watermark for the NCB outbound load/store commands receive FIFO. [NBR_HWM]+1 is used
                                                                 as the high watermark.  So a value of 0 allows 1 entry in the FIFO at a time.  The
                                                                 FIFO size is 8 entries. */
        uint64_t wait_cnt              : 6;  /**< [ 23: 18](R/W) Wait input filter count. Represents the number of coprocessor-clock cycles for glitch
                                                                 filtering of PBUS_WAIT from the NAND flash device. */
        uint64_t fr_byt                : 11; /**< [ 17:  7](RO/H) Unfilled NDF_CMD queue bytes. Specifies the number of unfilled bytes in the
                                                                 NDF_CMD queue. Bytes become unfilled as commands complete execution and exit. (FIFO is 256
                                                                 bytes when [BT_DIS] = 0 and 1536 bytes when [BT_DIS] = 1.) */
        uint64_t rd_done               : 1;  /**< [  6:  6](R/W1C/H) Read done. This bit is set to 1 by hardware when it reads the last eight bytes out of the
                                                                 NDF_CMD queue in response to [RD_CMD] being set to 1 by software. */
        uint64_t rd_val                : 1;  /**< [  5:  5](RO/H) This read-only bit is set to 1 by hardware when it reads the next eight bytes
                                                                 from NDF_CMD queue in response to [RD_CMD] being set to 1. A software read of
                                                                 NDF_CMD clears this bit to 0. */
        uint64_t rd_cmd                : 1;  /**< [  4:  4](R/W) Read command. When set to 1, the hardware reads the contents of the NDF_CMD queue eight
                                                                 bytes at a time and places the data into NDF_CMD. Software should first read [RD_VAL] to see
                                                                 if the next eight bytes from the NDF_CMD queue are available in NDF_CMD.

                                                                 All NDF_CMD queue read operations start and end on an eight-byte boundary. A
                                                                 [RD_CMD] command in the middle of command execution causes the execution to freeze
                                                                 until [RD_DONE] is set to 1.

                                                                 This bit is cleared on any NDF_CMD software write command. */
        uint64_t bt_dma                : 1;  /**< [  3:  3](R/W) Boot-time DMA enable. Reserved.
                                                                 Internal:
                                                                 When set to 1, boot-time DMA is enabled. This indicates to the NAND
                                                                 flash boot-control state machine that boot DMA read operations can begin. Software should
                                                                 set this bit to 1 after loading the NDF_CMD queue. Hardware sets the bit to 0 when boot
                                                                 DMA command execution is complete. If chip-enable 0 is not a NAND flash device, this bit
                                                                 is permanently 0 with software write operations ignored.
                                                                 When [BT_DIS] = 1, this bit is 0. */
        uint64_t bt_dis                : 1;  /**< [  2:  2](R/W) Boot disable. Typically set to 1.
                                                                 Internal:
                                                                 When the boot operation is over, software must set this field to 1, which
                                                                 causes the boot-control state machines to sleep.
                                                                 This bit indicates to the NAND flash boot-control state machine that boot operation has
                                                                 ended. When this bit changes from 0 -\> 1, the NDF_CMD queue is emptied as a side effect.
                                                                 This bit must never be set when booting from NAND flash and region zero is enabled. */
        uint64_t ex_dis                : 1;  /**< [  1:  1](R/W) Execution disable. When set to 1, this bit stops command execution after completing the
                                                                 execution of all commands currently in the NDF_CMD queue. Once command execution has
                                                                 stopped and then new commands are loaded into the NDF_CMD queue, command execution does
                                                                 not resume while this bit is 1.

                                                                 When this bit is set to 0, execution resumes if the NDF_CMD queue is not empty. */
        uint64_t rst_ff                : 1;  /**< [  0:  0](R/W) Reset FIFO.
                                                                 0 = Normal operation.
                                                                 1 = Reset NDF_CMD queue to empty it; any command in flight is not aborted before
                                                                 resetting. The FIFO comes up empty at the end of power on reset. */
#else /* Word 0 - Little Endian */
        uint64_t rst_ff                : 1;  /**< [  0:  0](R/W) Reset FIFO.
                                                                 0 = Normal operation.
                                                                 1 = Reset NDF_CMD queue to empty it; any command in flight is not aborted before
                                                                 resetting. The FIFO comes up empty at the end of power on reset. */
        uint64_t ex_dis                : 1;  /**< [  1:  1](R/W) Execution disable. When set to 1, this bit stops command execution after completing the
                                                                 execution of all commands currently in the NDF_CMD queue. Once command execution has
                                                                 stopped and then new commands are loaded into the NDF_CMD queue, command execution does
                                                                 not resume while this bit is 1.

                                                                 When this bit is set to 0, execution resumes if the NDF_CMD queue is not empty. */
        uint64_t bt_dis                : 1;  /**< [  2:  2](R/W) Boot disable. Typically set to 1.
                                                                 Internal:
                                                                 When the boot operation is over, software must set this field to 1, which
                                                                 causes the boot-control state machines to sleep.
                                                                 This bit indicates to the NAND flash boot-control state machine that boot operation has
                                                                 ended. When this bit changes from 0 -\> 1, the NDF_CMD queue is emptied as a side effect.
                                                                 This bit must never be set when booting from NAND flash and region zero is enabled. */
        uint64_t bt_dma                : 1;  /**< [  3:  3](R/W) Boot-time DMA enable. Reserved.
                                                                 Internal:
                                                                 When set to 1, boot-time DMA is enabled. This indicates to the NAND
                                                                 flash boot-control state machine that boot DMA read operations can begin. Software should
                                                                 set this bit to 1 after loading the NDF_CMD queue. Hardware sets the bit to 0 when boot
                                                                 DMA command execution is complete. If chip-enable 0 is not a NAND flash device, this bit
                                                                 is permanently 0 with software write operations ignored.
                                                                 When [BT_DIS] = 1, this bit is 0. */
        uint64_t rd_cmd                : 1;  /**< [  4:  4](R/W) Read command. When set to 1, the hardware reads the contents of the NDF_CMD queue eight
                                                                 bytes at a time and places the data into NDF_CMD. Software should first read [RD_VAL] to see
                                                                 if the next eight bytes from the NDF_CMD queue are available in NDF_CMD.

                                                                 All NDF_CMD queue read operations start and end on an eight-byte boundary. A
                                                                 [RD_CMD] command in the middle of command execution causes the execution to freeze
                                                                 until [RD_DONE] is set to 1.

                                                                 This bit is cleared on any NDF_CMD software write command. */
        uint64_t rd_val                : 1;  /**< [  5:  5](RO/H) This read-only bit is set to 1 by hardware when it reads the next eight bytes
                                                                 from NDF_CMD queue in response to [RD_CMD] being set to 1. A software read of
                                                                 NDF_CMD clears this bit to 0. */
        uint64_t rd_done               : 1;  /**< [  6:  6](R/W1C/H) Read done. This bit is set to 1 by hardware when it reads the last eight bytes out of the
                                                                 NDF_CMD queue in response to [RD_CMD] being set to 1 by software. */
        uint64_t fr_byt                : 11; /**< [ 17:  7](RO/H) Unfilled NDF_CMD queue bytes. Specifies the number of unfilled bytes in the
                                                                 NDF_CMD queue. Bytes become unfilled as commands complete execution and exit. (FIFO is 256
                                                                 bytes when [BT_DIS] = 0 and 1536 bytes when [BT_DIS] = 1.) */
        uint64_t wait_cnt              : 6;  /**< [ 23: 18](R/W) Wait input filter count. Represents the number of coprocessor-clock cycles for glitch
                                                                 filtering of PBUS_WAIT from the NAND flash device. */
        uint64_t nbr_hwm               : 3;  /**< [ 26: 24](R/W) High watermark for NBR FIFO or load/store operations. Specifies the high
                                                                 watermark for the NCB outbound load/store commands receive FIFO. [NBR_HWM]+1 is used
                                                                 as the high watermark.  So a value of 0 allows 1 entry in the FIFO at a time.  The
                                                                 FIFO size is 8 entries. */
        uint64_t mb_dis                : 1;  /**< [ 27: 27](R/W) Set to disable multi-bit error hangs. Allows loads and DMAs to proceed as if no
                                                                 multi-bit errors occurred. Hardware fixes single bit errors as usual. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_misc_s cn; */
};
typedef union bdk_ndf_misc bdk_ndf_misc_t;

#define BDK_NDF_MISC BDK_NDF_MISC_FUNC()
static inline uint64_t BDK_NDF_MISC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_MISC_FUNC(void)
{
    return 0x808000000008ll;
}

#define typedef_BDK_NDF_MISC bdk_ndf_misc_t
#define bustype_BDK_NDF_MISC BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_MISC "NDF_MISC"
#define device_bar_BDK_NDF_MISC 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_MISC 0
#define arguments_BDK_NDF_MISC -1,-1,-1,-1

/**
 * Register (NCB) ndf_msix_pba#
 *
 * NAND Flash MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the NDF_INT_VEC_E enumeration.
 */
union bdk_ndf_msix_pbax
{
    uint64_t u;
    struct bdk_ndf_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated NDF_MSIX_VEC()_CTL, enumerated by
                                                                 NDF_INT_VEC_E. Bits that have no associated NDF_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated NDF_MSIX_VEC()_CTL, enumerated by
                                                                 NDF_INT_VEC_E. Bits that have no associated NDF_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_msix_pbax_s cn; */
};
typedef union bdk_ndf_msix_pbax bdk_ndf_msix_pbax_t;

static inline uint64_t BDK_NDF_MSIX_PBAX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_MSIX_PBAX(unsigned long a)
{
    if (a==0)
        return 0x808000ff0000ll + 8ll * ((a) & 0x0);
    __bdk_csr_fatal("NDF_MSIX_PBAX", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDF_MSIX_PBAX(a) bdk_ndf_msix_pbax_t
#define bustype_BDK_NDF_MSIX_PBAX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_MSIX_PBAX(a) "NDF_MSIX_PBAX"
#define device_bar_BDK_NDF_MSIX_PBAX(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_NDF_MSIX_PBAX(a) (a)
#define arguments_BDK_NDF_MSIX_PBAX(a) (a),-1,-1,-1

/**
 * Register (NCB) ndf_msix_vec#_addr
 *
 * NAND Flash MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the NDF_INT_VEC_E enumeration.
 */
union bdk_ndf_msix_vecx_addr
{
    uint64_t u;
    struct bdk_ndf_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NDF_MSIX_VEC()_ADDR, NDF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NDF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NDF_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NDF_MSIX_VEC()_ADDR, NDF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NDF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NDF_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    struct bdk_ndf_msix_vecx_addr_cn8
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_49_63        : 15;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NDF_MSIX_VEC()_ADDR, NDF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NDF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NDF_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's NDF_MSIX_VEC()_ADDR, NDF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NDF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_NDF_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 47; /**< [ 48:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_49_63        : 15;
#endif /* Word 0 - End */
    } cn8;
    /* struct bdk_ndf_msix_vecx_addr_s cn9; */
    /* struct bdk_ndf_msix_vecx_addr_s cn96xxp1; */
    struct bdk_ndf_msix_vecx_addr_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 The vector's IOVA is sent to the SMMU as nonsecure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1).

                                                                 1 = This vector's NDF_MSIX_VEC()_ADDR, NDF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NDF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_NDF_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set.

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

                                                                 1 = This vector's NDF_MSIX_VEC()_ADDR, NDF_MSIX_VEC()_CTL, and corresponding
                                                                 bit of NDF_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.
                                                                 The vector's IOVA is sent to the SMMU as secure (though this only affects
                                                                 physical addresses if PCCPF_XXX_VSEC_SCTL[MSIX_PHYS]=1 or
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC_PHYS]=1).

                                                                 If PCCPF_NDF_VSEC_SCTL[MSIX_SEC] (for documentation, see
                                                                 PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is set, all vectors are secure and function as if
                                                                 [SECVEC] was set.

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
    /* struct bdk_ndf_msix_vecx_addr_cn96xxp3 cn98xx; */
    /* struct bdk_ndf_msix_vecx_addr_cn96xxp3 cnf95xx; */
    /* struct bdk_ndf_msix_vecx_addr_cn96xxp3 loki; */
};
typedef union bdk_ndf_msix_vecx_addr bdk_ndf_msix_vecx_addr_t;

static inline uint64_t BDK_NDF_MSIX_VECX_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_MSIX_VECX_ADDR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x808000f00000ll + 0x10ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=1))
        return 0x808000f00000ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("NDF_MSIX_VECX_ADDR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDF_MSIX_VECX_ADDR(a) bdk_ndf_msix_vecx_addr_t
#define bustype_BDK_NDF_MSIX_VECX_ADDR(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_MSIX_VECX_ADDR(a) "NDF_MSIX_VECX_ADDR"
#define device_bar_BDK_NDF_MSIX_VECX_ADDR(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_NDF_MSIX_VECX_ADDR(a) (a)
#define arguments_BDK_NDF_MSIX_VECX_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB) ndf_msix_vec#_ctl
 *
 * NAND Flash MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the NDF_INT_VEC_E enumeration.
 */
union bdk_ndf_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_ndf_msix_vecx_ctl_s
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
    struct bdk_ndf_msix_vecx_ctl_cn8
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
    /* struct bdk_ndf_msix_vecx_ctl_s cn9; */
};
typedef union bdk_ndf_msix_vecx_ctl bdk_ndf_msix_vecx_ctl_t;

static inline uint64_t BDK_NDF_MSIX_VECX_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_MSIX_VECX_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN8XXX) && (a==0))
        return 0x808000f00008ll + 0x10ll * ((a) & 0x0);
    if (bdk_is_model(OCTEONTX_CN9XXX) && (a<=1))
        return 0x808000f00008ll + 0x10ll * ((a) & 0x1);
    __bdk_csr_fatal("NDF_MSIX_VECX_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDF_MSIX_VECX_CTL(a) bdk_ndf_msix_vecx_ctl_t
#define bustype_BDK_NDF_MSIX_VECX_CTL(a) BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_MSIX_VECX_CTL(a) "NDF_MSIX_VECX_CTL"
#define device_bar_BDK_NDF_MSIX_VECX_CTL(a) 0x4 /* PF_BAR4 */
#define busnum_BDK_NDF_MSIX_VECX_CTL(a) (a)
#define arguments_BDK_NDF_MSIX_VECX_CTL(a) (a),-1,-1,-1

/**
 * Register (NCB) ndf_ras_int
 *
 * NAND Flash Interrupt Register
 * This register contains the bits that can trigger an error interrupt. Sixty-four-bit operations
 * must be used to access this register.
 */
union bdk_ndf_ras_int
{
    uint64_t u;
    struct bdk_ndf_ras_int_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ncb_ras               : 1;  /**< [  0:  0](R/W1C/H) NCB POISON recieved. */
#else /* Word 0 - Little Endian */
        uint64_t ncb_ras               : 1;  /**< [  0:  0](R/W1C/H) NCB POISON recieved. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_ras_int_s cn; */
};
typedef union bdk_ndf_ras_int bdk_ndf_ras_int_t;

#define BDK_NDF_RAS_INT BDK_NDF_RAS_INT_FUNC()
static inline uint64_t BDK_NDF_RAS_INT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_RAS_INT_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x808000000080ll;
    __bdk_csr_fatal("NDF_RAS_INT", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDF_RAS_INT bdk_ndf_ras_int_t
#define bustype_BDK_NDF_RAS_INT BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_RAS_INT "NDF_RAS_INT"
#define device_bar_BDK_NDF_RAS_INT 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_RAS_INT 0
#define arguments_BDK_NDF_RAS_INT -1,-1,-1,-1

/**
 * Register (NCB) ndf_ras_int_ena_w1c
 *
 * NAND Flash Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_ndf_ras_int_ena_w1c
{
    uint64_t u;
    struct bdk_ndf_ras_int_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ncb_ras               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NDF_RAS_INT[NCB_RAS]. */
#else /* Word 0 - Little Endian */
        uint64_t ncb_ras               : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for NDF_RAS_INT[NCB_RAS]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_ras_int_ena_w1c_s cn; */
};
typedef union bdk_ndf_ras_int_ena_w1c bdk_ndf_ras_int_ena_w1c_t;

#define BDK_NDF_RAS_INT_ENA_W1C BDK_NDF_RAS_INT_ENA_W1C_FUNC()
static inline uint64_t BDK_NDF_RAS_INT_ENA_W1C_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_RAS_INT_ENA_W1C_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x808000000098ll;
    __bdk_csr_fatal("NDF_RAS_INT_ENA_W1C", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDF_RAS_INT_ENA_W1C bdk_ndf_ras_int_ena_w1c_t
#define bustype_BDK_NDF_RAS_INT_ENA_W1C BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_RAS_INT_ENA_W1C "NDF_RAS_INT_ENA_W1C"
#define device_bar_BDK_NDF_RAS_INT_ENA_W1C 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_RAS_INT_ENA_W1C 0
#define arguments_BDK_NDF_RAS_INT_ENA_W1C -1,-1,-1,-1

/**
 * Register (NCB) ndf_ras_int_ena_w1s
 *
 * NAND Flash Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_ndf_ras_int_ena_w1s
{
    uint64_t u;
    struct bdk_ndf_ras_int_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ncb_ras               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NDF_RAS_INT[NCB_RAS]. */
#else /* Word 0 - Little Endian */
        uint64_t ncb_ras               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for NDF_RAS_INT[NCB_RAS]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_ras_int_ena_w1s_s cn; */
};
typedef union bdk_ndf_ras_int_ena_w1s bdk_ndf_ras_int_ena_w1s_t;

#define BDK_NDF_RAS_INT_ENA_W1S BDK_NDF_RAS_INT_ENA_W1S_FUNC()
static inline uint64_t BDK_NDF_RAS_INT_ENA_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_RAS_INT_ENA_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x808000000090ll;
    __bdk_csr_fatal("NDF_RAS_INT_ENA_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDF_RAS_INT_ENA_W1S bdk_ndf_ras_int_ena_w1s_t
#define bustype_BDK_NDF_RAS_INT_ENA_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_RAS_INT_ENA_W1S "NDF_RAS_INT_ENA_W1S"
#define device_bar_BDK_NDF_RAS_INT_ENA_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_RAS_INT_ENA_W1S 0
#define arguments_BDK_NDF_RAS_INT_ENA_W1S -1,-1,-1,-1

/**
 * Register (NCB) ndf_ras_int_w1s
 *
 * NAND Flash Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_ndf_ras_int_w1s
{
    uint64_t u;
    struct bdk_ndf_ras_int_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t ncb_ras               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NDF_RAS_INT[NCB_RAS]. */
#else /* Word 0 - Little Endian */
        uint64_t ncb_ras               : 1;  /**< [  0:  0](R/W1S/H) Reads or sets NDF_RAS_INT[NCB_RAS]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_ras_int_w1s_s cn; */
};
typedef union bdk_ndf_ras_int_w1s bdk_ndf_ras_int_w1s_t;

#define BDK_NDF_RAS_INT_W1S BDK_NDF_RAS_INT_W1S_FUNC()
static inline uint64_t BDK_NDF_RAS_INT_W1S_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_RAS_INT_W1S_FUNC(void)
{
    if (bdk_is_model(OCTEONTX_CN9XXX))
        return 0x808000000088ll;
    __bdk_csr_fatal("NDF_RAS_INT_W1S", 0, 0, 0, 0, 0, 0, 0);
}

#define typedef_BDK_NDF_RAS_INT_W1S bdk_ndf_ras_int_w1s_t
#define bustype_BDK_NDF_RAS_INT_W1S BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_RAS_INT_W1S "NDF_RAS_INT_W1S"
#define device_bar_BDK_NDF_RAS_INT_W1S 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_RAS_INT_W1S 0
#define arguments_BDK_NDF_RAS_INT_W1S -1,-1,-1,-1

/**
 * Register (NCB) ndf_st_reg
 *
 * NAND Flash State Machine Register
 * This register aggregates all state machines used in NAND flash controller for debug purposes.
 */
union bdk_ndf_st_reg
{
    uint64_t u;
    struct bdk_ndf_st_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t exe_idle              : 1;  /**< [ 15: 15](RO/H) Command execution status.
                                                                 0 = Busy.
                                                                 1 = Idle (execution of command sequence is complete and NDF_CMD queue is empty). */
        uint64_t exe_sm                : 4;  /**< [ 14: 11](RO/H) Command-execution state-machine states. */
        uint64_t bt_sm                 : 4;  /**< [ 10:  7](RO/H) Load and DMA state-machine states. */
        uint64_t rd_ff_bad             : 1;  /**< [  6:  6](RO/H) The NDF_CMD-queue read-back state machine is in a 'bad' state. */
        uint64_t rd_ff                 : 2;  /**< [  5:  4](RO/H) NDF_CMD-queue read-back state machine states. */
        uint64_t main_bad              : 1;  /**< [  3:  3](RO/H) The main state machine is in a 'bad' state. */
        uint64_t main_sm               : 3;  /**< [  2:  0](RO/H) Main state machine states. */
#else /* Word 0 - Little Endian */
        uint64_t main_sm               : 3;  /**< [  2:  0](RO/H) Main state machine states. */
        uint64_t main_bad              : 1;  /**< [  3:  3](RO/H) The main state machine is in a 'bad' state. */
        uint64_t rd_ff                 : 2;  /**< [  5:  4](RO/H) NDF_CMD-queue read-back state machine states. */
        uint64_t rd_ff_bad             : 1;  /**< [  6:  6](RO/H) The NDF_CMD-queue read-back state machine is in a 'bad' state. */
        uint64_t bt_sm                 : 4;  /**< [ 10:  7](RO/H) Load and DMA state-machine states. */
        uint64_t exe_sm                : 4;  /**< [ 14: 11](RO/H) Command-execution state-machine states. */
        uint64_t exe_idle              : 1;  /**< [ 15: 15](RO/H) Command execution status.
                                                                 0 = Busy.
                                                                 1 = Idle (execution of command sequence is complete and NDF_CMD queue is empty). */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_ndf_st_reg_s cn; */
};
typedef union bdk_ndf_st_reg bdk_ndf_st_reg_t;

#define BDK_NDF_ST_REG BDK_NDF_ST_REG_FUNC()
static inline uint64_t BDK_NDF_ST_REG_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_NDF_ST_REG_FUNC(void)
{
    return 0x808000000038ll;
}

#define typedef_BDK_NDF_ST_REG bdk_ndf_st_reg_t
#define bustype_BDK_NDF_ST_REG BDK_CSR_TYPE_NCB
#define basename_BDK_NDF_ST_REG "NDF_ST_REG"
#define device_bar_BDK_NDF_ST_REG 0x0 /* PF_BAR0 */
#define busnum_BDK_NDF_ST_REG 0
#define arguments_BDK_NDF_ST_REG -1,-1,-1,-1

#endif /* __BDK_CSRS_NDF_H__ */
