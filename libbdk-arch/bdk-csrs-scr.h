#ifndef __BDK_CSRS_SCR_H__
#define __BDK_CSRS_SCR_H__
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
 * OcteonTX SCR.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration scr_cmp_type_e
 *
 * ROM Script Comparison Type Enumeration
 * This enumerates SCR_CMP_AND_EXIT_S[CMP_TYPE] and
 * SCR_CMP_AND_SPIN_S[CMP_TYPE].
 */
#define BDK_SCR_CMP_TYPE_E_EQ (0)
#define BDK_SCR_CMP_TYPE_E_GE (4)
#define BDK_SCR_CMP_TYPE_E_GT (5)
#define BDK_SCR_CMP_TYPE_E_LE (1)
#define BDK_SCR_CMP_TYPE_E_LT (2)
#define BDK_SCR_CMP_TYPE_E_NE (3)

/**
 * Structure scr_cmp_and_exit_s
 *
 * ROM Script Compare and Exit Opcode Structure
 * This opcode will do a read of the address from the most recent
 * SCR_SETUP_CMP_S[ADDR], logical-and with the mask [MASK], compare
 * that result with data from the most recent SCR_SETUP_CMP_S[CMP_DATA],
 * and exit the script if the results match.
 */
union bdk_scr_cmp_and_exit_s
{
    uint64_t u[2];
    struct bdk_scr_cmp_and_exit_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t rsl64                 : 1;  /**< [ 55: 55] The RSL bus size.
                                                                 0 = 32-bits.
                                                                 1 = 64-bits. */
        uint64_t cmp_type              : 3;  /**< [ 54: 52] Comparison type. Enumerated by SCR_CMP_TYPE_E. */
        uint64_t reserved_0_51         : 52;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_51         : 52;
        uint64_t cmp_type              : 3;  /**< [ 54: 52] Comparison type. Enumerated by SCR_CMP_TYPE_E. */
        uint64_t rsl64                 : 1;  /**< [ 55: 55] The RSL bus size.
                                                                 0 = 32-bits.
                                                                 1 = 64-bits. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t mask                  : 64; /**< [127: 64] Mask for the compare.  A zero in a bit position means to ignore the corresponding bit. */
#else /* Word 1 - Little Endian */
        uint64_t mask                  : 64; /**< [127: 64] Mask for the compare.  A zero in a bit position means to ignore the corresponding bit. */
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_cmp_and_exit_s_s cn; */
};

/**
 * Structure scr_cmp_and_jump_s
 *
 * INTERNAL: ROM Script Jump Opcode Structure
 *
 * This opcode will do a read of the address from the most recent
 * SCR_SETUP_CMP_S[ADDR], logical-and
 * with the mask [MASK], compare that result with data from the
 * most recent SCR_SETUP_CMP_S[CMP_DATA] using [CMP_TYPE] comparison,  and
 * jump to [JUMP_TRUE] or [JUMP_FALSE].
 */
union bdk_scr_cmp_and_jump_s
{
    uint64_t u[2];
    struct bdk_scr_cmp_and_jump_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t rsl64                 : 1;  /**< [ 55: 55] The RSL bus size.
                                                                 0 = 32-bits.
                                                                 1 = 64-bits. */
        uint64_t cmp_type              : 3;  /**< [ 54: 52] Comparison type. Enumerated by SCR_CMP_TYPE_E. */
        uint64_t reserved_48_51        : 4;
        uint64_t jump_false            : 24; /**< [ 47: 24] Absolute jump pointer used when the condition is false. */
        uint64_t jump_true             : 24; /**< [ 23:  0] Absolute jump pointer used when the condition is true. */
#else /* Word 0 - Little Endian */
        uint64_t jump_true             : 24; /**< [ 23:  0] Absolute jump pointer used when the condition is true. */
        uint64_t jump_false            : 24; /**< [ 47: 24] Absolute jump pointer used when the condition is false. */
        uint64_t reserved_48_51        : 4;
        uint64_t cmp_type              : 3;  /**< [ 54: 52] Comparison type. Enumerated by SCR_CMP_TYPE_E. */
        uint64_t rsl64                 : 1;  /**< [ 55: 55] The RSL bus size.
                                                                 0 = 32-bits.
                                                                 1 = 64-bits. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t mask                  : 64; /**< [127: 64] Mask for the compare data. A zero in a bit position means to ignore the corresponding bit. */
#else /* Word 1 - Little Endian */
        uint64_t mask                  : 64; /**< [127: 64] Mask for the compare data. A zero in a bit position means to ignore the corresponding bit. */
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_cmp_and_jump_s_s cn; */
};

/**
 * Structure scr_cmp_and_spin_s
 *
 * ROM Script Compare and Spin Opcode Structure
 * This opcode will do a read of the address from the most recent
 * SCR_SETUP_CMP_S[ADDR], logical-and
 * with the mask [MASK], compare that result with data from the
 * most recent SCR_SETUP_CMP_S[CMP_DATA], and
 * spin as long as the result does not match.
 */
union bdk_scr_cmp_and_spin_s
{
    uint64_t u[2];
    struct bdk_scr_cmp_and_spin_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t rsl64                 : 1;  /**< [ 55: 55] The RSL bus operation size:
                                                                   0 = 32-bits.
                                                                   1 = 64-bits. */
        uint64_t cmp_type              : 3;  /**< [ 54: 52] Comparison type. Enumerated by SCR_CMP_TYPE_E. */
        uint64_t reserved_32_51        : 20;
        uint64_t time_out              : 32; /**< [ 31:  0] Timeout in 10 ns ticks. Bit 31 must be clear. The timeout counter starts at the
                                                                 operation's first read being issued, and once timed out, any read in progress
                                                                 will complete and be tested, but no further poll reads will be issued and the
                                                                 operation will move to the next. A value of 0x0 indicates to never give up
                                                                 spinning. A value of 0x1 indicate to issue a single read (this falls out of the
                                                                 definition above, as all reads take more than 10 ns.) */
#else /* Word 0 - Little Endian */
        uint64_t time_out              : 32; /**< [ 31:  0] Timeout in 10 ns ticks. Bit 31 must be clear. The timeout counter starts at the
                                                                 operation's first read being issued, and once timed out, any read in progress
                                                                 will complete and be tested, but no further poll reads will be issued and the
                                                                 operation will move to the next. A value of 0x0 indicates to never give up
                                                                 spinning. A value of 0x1 indicate to issue a single read (this falls out of the
                                                                 definition above, as all reads take more than 10 ns.) */
        uint64_t reserved_32_51        : 20;
        uint64_t cmp_type              : 3;  /**< [ 54: 52] Comparison type. Enumerated by SCR_CMP_TYPE_E. */
        uint64_t rsl64                 : 1;  /**< [ 55: 55] The RSL bus operation size:
                                                                   0 = 32-bits.
                                                                   1 = 64-bits. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t mask                  : 64; /**< [127: 64] Mask for the compare data. A zero in a bit position means to ignore the corresponding bit. */
#else /* Word 1 - Little Endian */
        uint64_t mask                  : 64; /**< [127: 64] Mask for the compare data. A zero in a bit position means to ignore the corresponding bit. */
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_cmp_and_spin_s_s cn; */
};

/**
 * Structure scr_dma_check_s
 *
 * ROM Script DMA Checksum Opcode Structure
 * This opcode exits for the script if the supplied checksum doesn't match the checksum
 * accumulated during the previous SCR_DMA_S transfer.
 */
union bdk_scr_dma_check_s
{
    uint64_t u[2];
    struct bdk_scr_dma_check_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t reserved_32_55        : 24;
        uint64_t checksum              : 32; /**< [ 31:  0] Checksum to be compared with that accumulated during the transfer. Uses the same
                                                                 algorithm as the ROM script checksum. */
#else /* Word 0 - Little Endian */
        uint64_t checksum              : 32; /**< [ 31:  0] Checksum to be compared with that accumulated during the transfer. Uses the same
                                                                 algorithm as the ROM script checksum. */
        uint64_t reserved_32_55        : 24;
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_64_127       : 64;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_127       : 64;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_dma_check_s_s cn; */
};

/**
 * Structure scr_dma_s
 *
 * ROM Script DMA Opcode Structure
 * This opcode copies [COUNT] 64-bit words from the flash to the [DEST_ADDR].
 */
union bdk_scr_dma_s
{
    uint64_t u[2];
    struct bdk_scr_dma_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t dest_addr             : 56; /**< [ 55:  0] Destination Address. \<2:0\> must be zero. See rules in SCR_WRITE32_S[ADDR]. */
#else /* Word 0 - Little Endian */
        uint64_t dest_addr             : 56; /**< [ 55:  0] Destination Address. \<2:0\> must be zero. See rules in SCR_WRITE32_S[ADDR]. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_120_127      : 8;
        uint64_t src_addr              : 24; /**< [119: 96] Source Address in flash.  \<2:0\> must be zero. */
        uint64_t reserved_80_95        : 16;
        uint64_t count                 : 16; /**< [ 79: 64] Number of 64-bit words to copy. */
#else /* Word 1 - Little Endian */
        uint64_t count                 : 16; /**< [ 79: 64] Number of 64-bit words to copy. */
        uint64_t reserved_80_95        : 16;
        uint64_t src_addr              : 24; /**< [119: 96] Source Address in flash.  \<2:0\> must be zero. */
        uint64_t reserved_120_127      : 8;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_dma_s_s cn; */
};

/**
 * Structure scr_exit_s
 *
 * ROM Script Exit Opcode Structure
 * This opcode causes the script to exit.
 */
union bdk_scr_exit_s
{
    uint64_t u[2];
    struct bdk_scr_exit_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t reserved_0_55         : 56;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_55         : 56;
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_64_127       : 64;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_127       : 64;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_exit_s_s cn; */
};

/**
 * Structure scr_generic_s
 *
 * ROM Script Generic Opcode Structure
 * This is the generic format of a non-specific opcode.
 */
union bdk_scr_generic_s
{
    uint64_t u[2];
    struct bdk_scr_generic_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t reserved_0_55         : 56;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_55         : 56;
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_64_127       : 64;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_127       : 64;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_generic_s_s cn; */
};

/**
 * Structure scr_move64_s
 *
 * ROM Script 64-bit CSR-to-CSR Move Opcode Structure
 * This opcode copies a 64-bit value from [SRC_ADDR] to [DEST_ADDR].
 */
union bdk_scr_move64_s
{
    uint64_t u[2];
    struct bdk_scr_move64_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t src_addr              : 56; /**< [ 55:  0] Address. \<2:0\> must be zero. See rules in SCR_WRITE32_S[ADDR]. */
#else /* Word 0 - Little Endian */
        uint64_t src_addr              : 56; /**< [ 55:  0] Address. \<2:0\> must be zero. See rules in SCR_WRITE32_S[ADDR]. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_120_127      : 8;
        uint64_t dest_addr             : 56; /**< [119: 64] Address. \<2:0\> must be zero. See rules in SCR_WRITE32_S[ADDR]. */
#else /* Word 1 - Little Endian */
        uint64_t dest_addr             : 56; /**< [119: 64] Address. \<2:0\> must be zero. See rules in SCR_WRITE32_S[ADDR]. */
        uint64_t reserved_120_127      : 8;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_move64_s_s cn; */
};

/**
 * Structure scr_noop_s
 *
 * ROM Script No-Operation Opcode Structure
 * This opcode performs no operation.
 */
union bdk_scr_noop_s
{
    uint64_t u[2];
    struct bdk_scr_noop_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t reserved_0_55         : 56;
#else /* Word 0 - Little Endian */
        uint64_t reserved_0_55         : 56;
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_64_127       : 64;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_127       : 64;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_noop_s_s cn; */
};

/**
 * Structure scr_setup_cmp_s
 *
 * ROM Script Set Compare Source Opcode Structure
 * This opcode loads a 64-bit compare data [CMP_DATA] and [ADDR] for use by
 * subsequent SCR_CMP_AND_SPIN_S, and SCR_CMP_AND_EXIT_S opcodes.
 */
union bdk_scr_setup_cmp_s
{
    uint64_t u[2];
    struct bdk_scr_setup_cmp_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. See rules in SCR_WRITE32_S[ADDR]. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. See rules in SCR_WRITE32_S[ADDR]. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t cmp_data              : 64; /**< [127: 64] Compare data. */
#else /* Word 1 - Little Endian */
        uint64_t cmp_data              : 64; /**< [127: 64] Compare data. */
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_setup_cmp_s_s cn; */
};

/**
 * Structure scr_wait_s
 *
 * ROM Script Wait Opcode Structure
 * This opcode waits for [COUNT] number of 10 ns clock periods.
 */
union bdk_scr_wait_s
{
    uint64_t u[2];
    struct bdk_scr_wait_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t reserved_31_55        : 25;
        uint64_t count                 : 31; /**< [ 30:  0] Count. Number of 10 ns clock periods to wait. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 31; /**< [ 30:  0] Count. Number of 10 ns clock periods to wait. */
        uint64_t reserved_31_55        : 25;
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_64_127       : 64;
#else /* Word 1 - Little Endian */
        uint64_t reserved_64_127       : 64;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_wait_s_s cn; */
};

/**
 * Structure scr_write32_s
 *
 * ROM Script 32-bit Write Opcode Structure
 * This opcode writes a 32-bit value [DATA] to the address [ADDR].
 */
union bdk_scr_write32_s
{
    uint64_t u[2];
    struct bdk_scr_write32_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. The address must be to a permitted address, or the write will be
                                                                 silently dropped and reads will return zeros. The permitted registers are:
                                                                   * GPIO:
                                                                     o GPIO_BIT_CFG().
                                                                     o GPIO_BLINK_CFG.
                                                                     o GPIO_BLINK_FREQ.
                                                                     o GPIO_CLK_GEN().
                                                                     o GPIO_IO_CTL.
                                                                     o GPIO_CONST.
                                                                     o GPIO_PSPI_CTL.
                                                                     o GPIO_MISC_STRAP.
                                                                     o GPIO_RX_DAT, GPIO_RX1_DAT.
                                                                     o GPIO_STRAP, GPIO_STRAP1.
                                                                     o GPIO_TX_CLR, GPIO_TX1_CLR.
                                                                     o GPIO_TX_SET, GPIO_TX1_SET.
                                                                   * GSERN()_*.
                                                                   \<page\>
                                                                   * PEM():
                                                                     o PEM()_CFG.
                                                                     o PEM()_CFG_RD (legacy).
                                                                     o PEM()_CFG_WR (legacy).
                                                                     o PEM()_CLK_EN.
                                                                     o PEM()_CTL_STATUS.
                                                                     o PEM()_CTL_STATUS2.
                                                                     o PEM()_DBG_INFO.
                                                                     o PEM()_DIAG_STATUS.
                                                                     o PEM()_DIS_PORT.
                                                                     o PEM()_EBI_TLP_CREDITS.
                                                                     o PEM()_EBUS_CTL.
                                                                     o PEM()_LTR_VAL().
                                                                     o PEM()_MAC_LANE()_EQ.
                                                                     o PEM()_NCBI_TLP_CREDITS.
                                                                     o PEM()_ON.
                                                                     o PEM()_PF()_CS()_PFCFG().
                                                                     o PEM()_PF()_CTL_STATUS.
                                                                     o PEM()_PF()_VF()_VFCFG().
                                                                     o PEM()_STRAP.
                                                                     o PEM()_CFG_TBL().
                                                                     o PEM()_CFG_TBL_SIZE.
                                                                   \<page\>
                                                                   * PCIEPVF_* config space via PEM()_PF()_VF()_VFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIEP_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIRC_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * RST:
                                                                     o RST_CONST.
                                                                     o RST_CTL().
                                                                     o RST_OUT_CTL.
                                                                     o RST_REFC_CTL.
                                                                     o RST_SOFT_PRST().

                                                                 Accesses are always nonsecure. The normal permission registers
                                                                 MRML_RSL()_PERMIT, MRML_NCB()_PERMIT, GPIO_PERMIT, etc. still apply, and must be
                                                                 appropriately permissive for the script access to the corresponding device to
                                                                 succeed.

                                                                 Internal:
                                                                 This list corresponds to rom.c's script_access_allowed().  Verification has a
                                                                 similar vkit function to insure PEM subsystem configuration writes are allowed
                                                                 by this function (to insure it doesn't omit an important register needed for
                                                                 configuration.)

                                                                 The description of each register listed above contains a cross reference to this
                                                                 text.

                                                                 This list must never contain registers that could enable a memory write to an
                                                                 arbitrary address, e.g. no MSI-X registers. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. The address must be to a permitted address, or the write will be
                                                                 silently dropped and reads will return zeros. The permitted registers are:
                                                                   * GPIO:
                                                                     o GPIO_BIT_CFG().
                                                                     o GPIO_BLINK_CFG.
                                                                     o GPIO_BLINK_FREQ.
                                                                     o GPIO_CLK_GEN().
                                                                     o GPIO_IO_CTL.
                                                                     o GPIO_CONST.
                                                                     o GPIO_PSPI_CTL.
                                                                     o GPIO_MISC_STRAP.
                                                                     o GPIO_RX_DAT, GPIO_RX1_DAT.
                                                                     o GPIO_STRAP, GPIO_STRAP1.
                                                                     o GPIO_TX_CLR, GPIO_TX1_CLR.
                                                                     o GPIO_TX_SET, GPIO_TX1_SET.
                                                                   * GSERN()_*.
                                                                   \<page\>
                                                                   * PEM():
                                                                     o PEM()_CFG.
                                                                     o PEM()_CFG_RD (legacy).
                                                                     o PEM()_CFG_WR (legacy).
                                                                     o PEM()_CLK_EN.
                                                                     o PEM()_CTL_STATUS.
                                                                     o PEM()_CTL_STATUS2.
                                                                     o PEM()_DBG_INFO.
                                                                     o PEM()_DIAG_STATUS.
                                                                     o PEM()_DIS_PORT.
                                                                     o PEM()_EBI_TLP_CREDITS.
                                                                     o PEM()_EBUS_CTL.
                                                                     o PEM()_LTR_VAL().
                                                                     o PEM()_MAC_LANE()_EQ.
                                                                     o PEM()_NCBI_TLP_CREDITS.
                                                                     o PEM()_ON.
                                                                     o PEM()_PF()_CS()_PFCFG().
                                                                     o PEM()_PF()_CTL_STATUS.
                                                                     o PEM()_PF()_VF()_VFCFG().
                                                                     o PEM()_STRAP.
                                                                     o PEM()_CFG_TBL().
                                                                     o PEM()_CFG_TBL_SIZE.
                                                                   \<page\>
                                                                   * PCIEPVF_* config space via PEM()_PF()_VF()_VFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIEP_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIRC_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * RST:
                                                                     o RST_CONST.
                                                                     o RST_CTL().
                                                                     o RST_OUT_CTL.
                                                                     o RST_REFC_CTL.
                                                                     o RST_SOFT_PRST().

                                                                 Accesses are always nonsecure. The normal permission registers
                                                                 MRML_RSL()_PERMIT, MRML_NCB()_PERMIT, GPIO_PERMIT, etc. still apply, and must be
                                                                 appropriately permissive for the script access to the corresponding device to
                                                                 succeed.

                                                                 Internal:
                                                                 This list corresponds to rom.c's script_access_allowed().  Verification has a
                                                                 similar vkit function to insure PEM subsystem configuration writes are allowed
                                                                 by this function (to insure it doesn't omit an important register needed for
                                                                 configuration.)

                                                                 The description of each register listed above contains a cross reference to this
                                                                 text.

                                                                 This list must never contain registers that could enable a memory write to an
                                                                 arbitrary address, e.g. no MSI-X registers. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_96_127       : 32;
        uint64_t data                  : 32; /**< [ 95: 64] Write data. */
#else /* Word 1 - Little Endian */
        uint64_t data                  : 32; /**< [ 95: 64] Write data. */
        uint64_t reserved_96_127       : 32;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_write32_s_s cn9; */
    /* struct bdk_scr_write32_s_s cn96xxp1; */
    struct bdk_scr_write32_s_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. The address must be to a permitted address, or the write will be
                                                                 silently dropped and reads will return zeros. The permitted registers are:
                                                                   * GPIO:
                                                                     o GPIO_BIT_CFG().
                                                                     o GPIO_BLINK_CFG.
                                                                     o GPIO_BLINK_FREQ.
                                                                     o GPIO_CLK_GEN().
                                                                     o GPIO_IO_CTL.
                                                                     o GPIO_CONST.
                                                                     o GPIO_PSPI_CTL.
                                                                     o GPIO_MISC_STRAP.
                                                                     o GPIO_RX_DAT, GPIO_RX1_DAT.
                                                                     o GPIO_STRAP, GPIO_STRAP1.
                                                                     o GPIO_TX_CLR, GPIO_TX1_CLR.
                                                                     o GPIO_TX_SET, GPIO_TX1_SET.
                                                                   * GSERN()_*.
                                                                   * GSERP()_*.
                                                                   \<page\>
                                                                   * PEM():
                                                                     o PEM()_CFG.
                                                                     o PEM()_CFG_RD (legacy).
                                                                     o PEM()_CFG_WR (legacy).
                                                                     o PEM()_CLK_EN.
                                                                     o PEM()_CTL_STATUS.
                                                                     o PEM()_CTL_STATUS2.
                                                                     o PEM()_DBG_INFO.
                                                                     o PEM()_DIAG_STATUS.
                                                                     o PEM()_DIS_PORT.
                                                                     o PEM()_EBI_TLP_CREDITS.
                                                                     o PEM()_EBUS_CTL.
                                                                     o PEM()_LTR_VAL().
                                                                     o PEM()_MAC_LANE()_EQ.
                                                                     o PEM()_NCBI_TLP_CREDITS.
                                                                     o PEM()_ON.
                                                                     o PEM()_PF()_CS()_PFCFG().
                                                                     o PEM()_PF()_CTL_STATUS.
                                                                     o PEM()_PF()_VF()_VFCFG().
                                                                     o PEM()_STRAP.
                                                                     o PEM()_CFG_TBL().
                                                                     o PEM()_CFG_TBL_SIZE.
                                                                     o PEM()_S_RST_CTL.
                                                                     o PEM()_RST_SOFT_PERST.
                                                                     o PEM()_RST_MAC.
                                                                   \<page\>
                                                                   * PCIEPVF_* config space via PEM()_PF()_VF()_VFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIEP_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIRC_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * RST:
                                                                     o RST_CONST.
                                                                     o RST_OUT_CTL.
                                                                     o RST_REFC_CTL.
                                                                   * TSN:
                                                                     o TSN()_TS_TEMP_NOFF_MC.
                                                                     o TSN()_TS_TEMP_CONV_RESULT.
                                                                     o TSN()_FUSE_BYPASS.
                                                                   \<page\>

                                                                 Accesses are always nonsecure. The normal permission registers
                                                                 MRML_RSL()_PERMIT, MRML_NCB()_PERMIT, GPIO_PERMIT, etc. still apply, and must be
                                                                 appropriately permissive for the script access to the corresponding device to
                                                                 succeed.

                                                                 Internal:
                                                                 This list corresponds to rom.c's script_access_allowed().  Verification has a
                                                                 similar vkit function to insure PEM subsystem configuration writes are allowed
                                                                 by this function (to insure it doesn't omit an important register needed for
                                                                 configuration.)

                                                                 The description of each register listed above contains a cross reference to this
                                                                 text.

                                                                 This list must never contain registers that could enable a memory write to an
                                                                 arbitrary address, e.g. no MSI-X registers. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. The address must be to a permitted address, or the write will be
                                                                 silently dropped and reads will return zeros. The permitted registers are:
                                                                   * GPIO:
                                                                     o GPIO_BIT_CFG().
                                                                     o GPIO_BLINK_CFG.
                                                                     o GPIO_BLINK_FREQ.
                                                                     o GPIO_CLK_GEN().
                                                                     o GPIO_IO_CTL.
                                                                     o GPIO_CONST.
                                                                     o GPIO_PSPI_CTL.
                                                                     o GPIO_MISC_STRAP.
                                                                     o GPIO_RX_DAT, GPIO_RX1_DAT.
                                                                     o GPIO_STRAP, GPIO_STRAP1.
                                                                     o GPIO_TX_CLR, GPIO_TX1_CLR.
                                                                     o GPIO_TX_SET, GPIO_TX1_SET.
                                                                   * GSERN()_*.
                                                                   * GSERP()_*.
                                                                   \<page\>
                                                                   * PEM():
                                                                     o PEM()_CFG.
                                                                     o PEM()_CFG_RD (legacy).
                                                                     o PEM()_CFG_WR (legacy).
                                                                     o PEM()_CLK_EN.
                                                                     o PEM()_CTL_STATUS.
                                                                     o PEM()_CTL_STATUS2.
                                                                     o PEM()_DBG_INFO.
                                                                     o PEM()_DIAG_STATUS.
                                                                     o PEM()_DIS_PORT.
                                                                     o PEM()_EBI_TLP_CREDITS.
                                                                     o PEM()_EBUS_CTL.
                                                                     o PEM()_LTR_VAL().
                                                                     o PEM()_MAC_LANE()_EQ.
                                                                     o PEM()_NCBI_TLP_CREDITS.
                                                                     o PEM()_ON.
                                                                     o PEM()_PF()_CS()_PFCFG().
                                                                     o PEM()_PF()_CTL_STATUS.
                                                                     o PEM()_PF()_VF()_VFCFG().
                                                                     o PEM()_STRAP.
                                                                     o PEM()_CFG_TBL().
                                                                     o PEM()_CFG_TBL_SIZE.
                                                                     o PEM()_S_RST_CTL.
                                                                     o PEM()_RST_SOFT_PERST.
                                                                     o PEM()_RST_MAC.
                                                                   \<page\>
                                                                   * PCIEPVF_* config space via PEM()_PF()_VF()_VFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIEP_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIRC_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * RST:
                                                                     o RST_CONST.
                                                                     o RST_OUT_CTL.
                                                                     o RST_REFC_CTL.
                                                                   * TSN:
                                                                     o TSN()_TS_TEMP_NOFF_MC.
                                                                     o TSN()_TS_TEMP_CONV_RESULT.
                                                                     o TSN()_FUSE_BYPASS.
                                                                   \<page\>

                                                                 Accesses are always nonsecure. The normal permission registers
                                                                 MRML_RSL()_PERMIT, MRML_NCB()_PERMIT, GPIO_PERMIT, etc. still apply, and must be
                                                                 appropriately permissive for the script access to the corresponding device to
                                                                 succeed.

                                                                 Internal:
                                                                 This list corresponds to rom.c's script_access_allowed().  Verification has a
                                                                 similar vkit function to insure PEM subsystem configuration writes are allowed
                                                                 by this function (to insure it doesn't omit an important register needed for
                                                                 configuration.)

                                                                 The description of each register listed above contains a cross reference to this
                                                                 text.

                                                                 This list must never contain registers that could enable a memory write to an
                                                                 arbitrary address, e.g. no MSI-X registers. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_96_127       : 32;
        uint64_t data                  : 32; /**< [ 95: 64] Write data. */
#else /* Word 1 - Little Endian */
        uint64_t data                  : 32; /**< [ 95: 64] Write data. */
        uint64_t reserved_96_127       : 32;
#endif /* Word 1 - End */
    } cn96xxp3;
    /* struct bdk_scr_write32_s_cn96xxp3 cn98xx; */
    /* struct bdk_scr_write32_s_s cnf95xxp1; */
    struct bdk_scr_write32_s_cnf95xxp2
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. The address must be to a permitted address, or the write will be
                                                                 silently dropped and reads will return zeros. The permitted registers are:
                                                                   * GPIO:
                                                                     o GPIO_BIT_CFG().
                                                                     o GPIO_BLINK_CFG.
                                                                     o GPIO_BLINK_FREQ.
                                                                     o GPIO_CLK_GEN().
                                                                     o GPIO_IO_CTL.
                                                                     o GPIO_CONST.
                                                                     o GPIO_PSPI_CTL.
                                                                     o GPIO_MISC_STRAP.
                                                                     o GPIO_RX_DAT, GPIO_RX1_DAT.
                                                                     o GPIO_STRAP, GPIO_STRAP1.
                                                                     o GPIO_TX_CLR, GPIO_TX1_CLR.
                                                                     o GPIO_TX_SET, GPIO_TX1_SET.
                                                                   * GSERN()_*.
                                                                   * GSERP()_*.
                                                                   \<page\>
                                                                   * PEM():
                                                                     o PEM()_CFG.
                                                                     o PEM()_CFG_RD (legacy).
                                                                     o PEM()_CFG_WR (legacy).
                                                                     o PEM()_CLK_EN.
                                                                     o PEM()_CTL_STATUS.
                                                                     o PEM()_CTL_STATUS2.
                                                                     o PEM()_DBG_INFO.
                                                                     o PEM()_DIAG_STATUS.
                                                                     o PEM()_DIS_PORT.
                                                                     o PEM()_EBI_TLP_CREDITS.
                                                                     o PEM()_EBUS_CTL.
                                                                     o PEM()_LTR_VAL().
                                                                     o PEM()_MAC_LANE()_EQ.
                                                                     o PEM()_NCBI_TLP_CREDITS.
                                                                     o PEM()_ON.
                                                                     o PEM()_PF()_CS()_PFCFG().
                                                                     o PEM()_PF()_CTL_STATUS.
                                                                     o PEM()_PF()_VF()_VFCFG().
                                                                     o PEM()_STRAP.
                                                                     o PEM()_CFG_TBL().
                                                                     o PEM()_CFG_TBL_SIZE.
                                                                   \<page\>
                                                                   * PCIEPVF_* config space via PEM()_PF()_VF()_VFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIEP_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIRC_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * RST:
                                                                     o RST_CONST.
                                                                     o RST_CTL().
                                                                     o RST_OUT_CTL.
                                                                     o RST_REFC_CTL.
                                                                     o RST_SOFT_PRST().
                                                                   * TSN:
                                                                     o TSN()_TS_TEMP_NOFF_MC.
                                                                     o TSN()_TS_TEMP_CONV_RESULT.
                                                                     o TSN()_FUSE_BYPASS.
                                                                   \<page\>

                                                                 Accesses are always nonsecure. The normal permission registers
                                                                 MRML_RSL()_PERMIT, MRML_NCB()_PERMIT, GPIO_PERMIT, etc. still apply, and must be
                                                                 appropriately permissive for the script access to the corresponding device to
                                                                 succeed.

                                                                 Internal:
                                                                 This list corresponds to rom.c's script_access_allowed().  Verification has a
                                                                 similar vkit function to insure PEM subsystem configuration writes are allowed
                                                                 by this function (to insure it doesn't omit an important register needed for
                                                                 configuration.)

                                                                 The description of each register listed above contains a cross reference to this
                                                                 text.

                                                                 This list must never contain registers that could enable a memory write to an
                                                                 arbitrary address, e.g. no MSI-X registers. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. The address must be to a permitted address, or the write will be
                                                                 silently dropped and reads will return zeros. The permitted registers are:
                                                                   * GPIO:
                                                                     o GPIO_BIT_CFG().
                                                                     o GPIO_BLINK_CFG.
                                                                     o GPIO_BLINK_FREQ.
                                                                     o GPIO_CLK_GEN().
                                                                     o GPIO_IO_CTL.
                                                                     o GPIO_CONST.
                                                                     o GPIO_PSPI_CTL.
                                                                     o GPIO_MISC_STRAP.
                                                                     o GPIO_RX_DAT, GPIO_RX1_DAT.
                                                                     o GPIO_STRAP, GPIO_STRAP1.
                                                                     o GPIO_TX_CLR, GPIO_TX1_CLR.
                                                                     o GPIO_TX_SET, GPIO_TX1_SET.
                                                                   * GSERN()_*.
                                                                   * GSERP()_*.
                                                                   \<page\>
                                                                   * PEM():
                                                                     o PEM()_CFG.
                                                                     o PEM()_CFG_RD (legacy).
                                                                     o PEM()_CFG_WR (legacy).
                                                                     o PEM()_CLK_EN.
                                                                     o PEM()_CTL_STATUS.
                                                                     o PEM()_CTL_STATUS2.
                                                                     o PEM()_DBG_INFO.
                                                                     o PEM()_DIAG_STATUS.
                                                                     o PEM()_DIS_PORT.
                                                                     o PEM()_EBI_TLP_CREDITS.
                                                                     o PEM()_EBUS_CTL.
                                                                     o PEM()_LTR_VAL().
                                                                     o PEM()_MAC_LANE()_EQ.
                                                                     o PEM()_NCBI_TLP_CREDITS.
                                                                     o PEM()_ON.
                                                                     o PEM()_PF()_CS()_PFCFG().
                                                                     o PEM()_PF()_CTL_STATUS.
                                                                     o PEM()_PF()_VF()_VFCFG().
                                                                     o PEM()_STRAP.
                                                                     o PEM()_CFG_TBL().
                                                                     o PEM()_CFG_TBL_SIZE.
                                                                   \<page\>
                                                                   * PCIEPVF_* config space via PEM()_PF()_VF()_VFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIEP_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * PCIRC_* config space via PEM()_PF()_CS()_PFCFG() (or legacy PEM()_CFG_WR
                                                                     and PEM()_CFG_RD).
                                                                   * RST:
                                                                     o RST_CONST.
                                                                     o RST_CTL().
                                                                     o RST_OUT_CTL.
                                                                     o RST_REFC_CTL.
                                                                     o RST_SOFT_PRST().
                                                                   * TSN:
                                                                     o TSN()_TS_TEMP_NOFF_MC.
                                                                     o TSN()_TS_TEMP_CONV_RESULT.
                                                                     o TSN()_FUSE_BYPASS.
                                                                   \<page\>

                                                                 Accesses are always nonsecure. The normal permission registers
                                                                 MRML_RSL()_PERMIT, MRML_NCB()_PERMIT, GPIO_PERMIT, etc. still apply, and must be
                                                                 appropriately permissive for the script access to the corresponding device to
                                                                 succeed.

                                                                 Internal:
                                                                 This list corresponds to rom.c's script_access_allowed().  Verification has a
                                                                 similar vkit function to insure PEM subsystem configuration writes are allowed
                                                                 by this function (to insure it doesn't omit an important register needed for
                                                                 configuration.)

                                                                 The description of each register listed above contains a cross reference to this
                                                                 text.

                                                                 This list must never contain registers that could enable a memory write to an
                                                                 arbitrary address, e.g. no MSI-X registers. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_96_127       : 32;
        uint64_t data                  : 32; /**< [ 95: 64] Write data. */
#else /* Word 1 - Little Endian */
        uint64_t data                  : 32; /**< [ 95: 64] Write data. */
        uint64_t reserved_96_127       : 32;
#endif /* Word 1 - End */
    } cnf95xxp2;
    /* struct bdk_scr_write32_s_cn96xxp3 loki; */
};

/**
 * Structure scr_write64_s
 *
 * ROM Script 64-bit Write Opcode Structure
 * This opcode writes a 64-bit value [DATA] to the address [ADDR].
 */
union bdk_scr_write64_s
{
    uint64_t u[2];
    struct bdk_scr_write64_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. \<2:0\> must be zero. See rules in SCR_WRITE32_S[ADDR]. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. \<2:0\> must be zero. See rules in SCR_WRITE32_S[ADDR]. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t data                  : 64; /**< [127: 64] Write data. */
#else /* Word 1 - Little Endian */
        uint64_t data                  : 64; /**< [127: 64] Write data. */
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_write64_s_s cn; */
};

/**
 * Structure scr_write_temp_s
 *
 * ROM Script Write Temperature in GSERP Opcode Structure
 * This opcode writes the current GSERP temperature into the 8 bit GSERP register at
 * [ADDR]. It writes an 8-bit unsigned integer representing the Celsius temperature +
 * 40C, e.g. where value of 0 represents -40 C, 65 represents 25 C. Note that the TSN
 * requires ~4ms to initialize after the NOFF MC calibration is written, so write NOFF
 * MC first, then DMA the GSERP firmware, then use SCR_WRITE_TEMP_S.
 */
union bdk_scr_write_temp_s
{
    uint64_t u[2];
    struct bdk_scr_write_temp_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. See rules in SCR_WRITE32_S[ADDR]. */
#else /* Word 0 - Little Endian */
        uint64_t addr                  : 56; /**< [ 55:  0] Address. See rules in SCR_WRITE32_S[ADDR]. */
        uint64_t op                    : 8;  /**< [ 63: 56] Opcode. */
#endif /* Word 0 - End */
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 1 - Big Endian */
        uint64_t reserved_68_127       : 60;
        uint64_t tsn                   : 4;  /**< [ 67: 64] The TSN instance to use for the temperature.  Choose the one nearest the GSERP. */
#else /* Word 1 - Little Endian */
        uint64_t tsn                   : 4;  /**< [ 67: 64] The TSN instance to use for the temperature.  Choose the one nearest the GSERP. */
        uint64_t reserved_68_127       : 60;
#endif /* Word 1 - End */
    } s;
    /* struct bdk_scr_write_temp_s_s cn; */
};

#endif /* __BDK_CSRS_SCR_H__ */
