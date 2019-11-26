#ifndef __BDK_CSRS_DRO_H__
#define __BDK_CSRS_DRO_H__
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
 * OcteonTX DRO.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration dro_blocks_e
 *
 * INTERNAL: DRO Block Placement Enumeration
 *
 * Enumerates the DRO block identifier (CSR addresses \<23:16\>) to their physical placement.
 * Value 0xFF indicates broadcast, i.e., select all blocks.
 *
 * Internal:
 * This enum width is MDC_BAR_E::MDC_PF_BAR2's pcc_bar_size_bits minus 16, e.g. 24-16=8.
 * For P1, further limited to 4 bits.
 */
#define BDK_DRO_BLOCKS_E_DCPX_CN96XX(a) (0xc + (a))
#define BDK_DRO_BLOCKS_E_DCPX_CN98XX(a) (0x12 + (a))
#define BDK_DRO_BLOCKS_E_DCPX_CNF95XX(a) (9 + (a))
#define BDK_DRO_BLOCKS_E_DCPX_LOKI(a) (9 + (a))
#define BDK_DRO_BLOCKS_E_ROCX_CN96XX(a) (0xa + (a))
#define BDK_DRO_BLOCKS_E_ROCX_CN98XX(a) (0x10 + (a))
#define BDK_DRO_BLOCKS_E_ROCX_CNF95XX(a) (8 + (a))
#define BDK_DRO_BLOCKS_E_ROCX_LOKI(a) (8 + (a))
#define BDK_DRO_BLOCKS_E_TSNX(a) (0 + (a))
#define BDK_DRO_BLOCKS_E_TSN10 (0xe)

/**
 * Register (RSL) dro_blk#_broadcast_ack_ret
 *
 * INTERNAL: DRO Block Broadcast Ack Return Register
 *
 * This register determines which DRO will return the ack back to RSL during a broadcast.
 */
union bdk_dro_blkx_broadcast_ack_ret
{
    uint64_t u;
    struct bdk_dro_blkx_broadcast_ack_ret_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t ack_ret               : 8;  /**< [  7:  0](R/W) Block number which will return RSL acknowledge during a broadcast. Must refer to
                                                                 the block which is physically furthest from MRML (typically DCP). Enumerated by
                                                                 DRO_BLOCKS_E. */
#else /* Word 0 - Little Endian */
        uint64_t ack_ret               : 8;  /**< [  7:  0](R/W) Block number which will return RSL acknowledge during a broadcast. Must refer to
                                                                 the block which is physically furthest from MRML (typically DCP). Enumerated by
                                                                 DRO_BLOCKS_E. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_broadcast_ack_ret_s cn; */
};
typedef union bdk_dro_blkx_broadcast_ack_ret bdk_dro_blkx_broadcast_ack_ret_t;

static inline uint64_t BDK_DRO_BLKX_BROADCAST_ACK_RET(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_BROADCAST_ACK_RET(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000040ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000040ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000040ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000040ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_BROADCAST_ACK_RET", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_BROADCAST_ACK_RET(a) bdk_dro_blkx_broadcast_ack_ret_t
#define bustype_BDK_DRO_BLKX_BROADCAST_ACK_RET(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_BROADCAST_ACK_RET(a) "DRO_BLKX_BROADCAST_ACK_RET"
#define busnum_BDK_DRO_BLKX_BROADCAST_ACK_RET(a) (a)
#define arguments_BDK_DRO_BLKX_BROADCAST_ACK_RET(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_cfg_ctl
 *
 * INTERNAL: DRO Block Configuration Control Registers
 *
 * This register is the configuartion register.
 */
union bdk_dro_blkx_cfg_ctl
{
    uint64_t u;
    struct bdk_dro_blkx_cfg_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_4_63         : 60;
        uint64_t metal_shunt           : 1;  /**< [  3:  3](R/W) When set, remove the metal serpentines in the metal dominated rings. */
        uint64_t gate_shunt            : 3;  /**< [  2:  0](R/W) 0x0 = Disabled.
                                                                 0x1 = No shunt.
                                                                 0x2 = First shunt.
                                                                 0x4 = Second shunt. */
#else /* Word 0 - Little Endian */
        uint64_t gate_shunt            : 3;  /**< [  2:  0](R/W) 0x0 = Disabled.
                                                                 0x1 = No shunt.
                                                                 0x2 = First shunt.
                                                                 0x4 = Second shunt. */
        uint64_t metal_shunt           : 1;  /**< [  3:  3](R/W) When set, remove the metal serpentines in the metal dominated rings. */
        uint64_t reserved_4_63         : 60;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_cfg_ctl_s cn; */
};
typedef union bdk_dro_blkx_cfg_ctl bdk_dro_blkx_cfg_ctl_t;

static inline uint64_t BDK_DRO_BLKX_CFG_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_CFG_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000018ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000018ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000018ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000018ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_CFG_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_CFG_CTL(a) bdk_dro_blkx_cfg_ctl_t
#define bustype_BDK_DRO_BLKX_CFG_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_CFG_CTL(a) "DRO_BLKX_CFG_CTL"
#define busnum_BDK_DRO_BLKX_CFG_CTL(a) (a)
#define arguments_BDK_DRO_BLKX_CFG_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_const
 *
 * INTERNAL: DRO Block Constants Register
 *
 * This register contains constants for software discovery. Software must use
 * DRO_BLK(0)_CONST[BLOCKS] to discover the number of blocks present (and thus number
 * of index {a}'s present in this register).
 */
union bdk_dro_blkx_const
{
    uint64_t u;
    struct bdk_dro_blkx_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_15_63        : 49;
        uint64_t blocks                : 6;  /**< [ 14:  9](RO) Number of blocks supported. */
        uint64_t rings                 : 9;  /**< [  8:  0](RO) Number of rings supported. */
#else /* Word 0 - Little Endian */
        uint64_t rings                 : 9;  /**< [  8:  0](RO) Number of rings supported. */
        uint64_t blocks                : 6;  /**< [ 14:  9](RO) Number of blocks supported. */
        uint64_t reserved_15_63        : 49;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_const_s cn; */
};
typedef union bdk_dro_blkx_const bdk_dro_blkx_const_t;

static inline uint64_t BDK_DRO_BLKX_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_CONST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000000ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000000ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000000ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000000ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_CONST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_CONST(a) bdk_dro_blkx_const_t
#define bustype_BDK_DRO_BLKX_CONST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_CONST(a) "DRO_BLKX_CONST"
#define busnum_BDK_DRO_BLKX_CONST(a) (a)
#define arguments_BDK_DRO_BLKX_CONST(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_eco
 *
 * INTERNAL: DRO Block ECO Register
 */
union bdk_dro_blkx_eco
{
    uint64_t u;
    struct bdk_dro_blkx_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_eco_s cn; */
};
typedef union bdk_dro_blkx_eco bdk_dro_blkx_eco_t;

static inline uint64_t BDK_DRO_BLKX_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_ECO(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000008ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000008ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000008ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000008ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_ECO", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_ECO(a) bdk_dro_blkx_eco_t
#define bustype_BDK_DRO_BLKX_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_ECO(a) "DRO_BLKX_ECO"
#define busnum_BDK_DRO_BLKX_ECO(a) (a)
#define arguments_BDK_DRO_BLKX_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_enable
 *
 * INTERNAL: DRO Block Enable Registers
 *
 * This register controls the start of ring oscillators.
 */
union bdk_dro_blkx_enable
{
    uint64_t u;
    struct bdk_dro_blkx_enable_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t enable                : 1;  /**< [  0:  0](R/W) 0x0 = Disabled.
                                                                 0x1 = Enable long path. */
#else /* Word 0 - Little Endian */
        uint64_t enable                : 1;  /**< [  0:  0](R/W) 0x0 = Disabled.
                                                                 0x1 = Enable long path. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_enable_s cn; */
};
typedef union bdk_dro_blkx_enable bdk_dro_blkx_enable_t;

static inline uint64_t BDK_DRO_BLKX_ENABLE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_ENABLE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000010ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000010ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000010ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000010ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_ENABLE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_ENABLE(a) bdk_dro_blkx_enable_t
#define bustype_BDK_DRO_BLKX_ENABLE(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_ENABLE(a) "DRO_BLKX_ENABLE"
#define busnum_BDK_DRO_BLKX_ENABLE(a) (a)
#define arguments_BDK_DRO_BLKX_ENABLE(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_error
 *
 * INTERNAL: DRO Block Error Registers
 *
 * This register is the error register.
 */
union bdk_dro_blkx_error
{
    uint64_t u;
    struct bdk_dro_blkx_error_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_5_63         : 59;
        uint64_t cfg_wr_er             : 1;  /**< [  4:  4](R/W1C/H) Config register write error. Set to indicate a write operation was performed on
                                                                 DRO_BLK()_CFG_CTL when enable is set. */
        uint64_t mask_wr_er            : 1;  /**< [  3:  3](R/W1C/H) Mask register write error. Set to indicate a write operation was performed on
                                                                 DRO_BLK()_RG()_MASK when enable is set. */
        uint64_t freeze_counter_rd_er  : 1;  /**< [  2:  2](R/W1C/H) Freeze counter read error. Set to indicate a read operation was performed on the
                                                                 counter when the value was not stable (enable is set and non-frozen). */
        uint64_t freeze_counter_wr_er  : 1;  /**< [  1:  1](R/W1C/H) Freeze counter write error. Set to indicate a write operation was performed on
                                                                 the counter when the value was not stable (enable is set and non-frozen). */
        uint64_t ring_counter_rd_er    : 1;  /**< [  0:  0](R/W1C/H) Ring counter read error. Set to indicate a read of the ring oscillator counter
                                                                 is done when the freeze state isn't complete. */
#else /* Word 0 - Little Endian */
        uint64_t ring_counter_rd_er    : 1;  /**< [  0:  0](R/W1C/H) Ring counter read error. Set to indicate a read of the ring oscillator counter
                                                                 is done when the freeze state isn't complete. */
        uint64_t freeze_counter_wr_er  : 1;  /**< [  1:  1](R/W1C/H) Freeze counter write error. Set to indicate a write operation was performed on
                                                                 the counter when the value was not stable (enable is set and non-frozen). */
        uint64_t freeze_counter_rd_er  : 1;  /**< [  2:  2](R/W1C/H) Freeze counter read error. Set to indicate a read operation was performed on the
                                                                 counter when the value was not stable (enable is set and non-frozen). */
        uint64_t mask_wr_er            : 1;  /**< [  3:  3](R/W1C/H) Mask register write error. Set to indicate a write operation was performed on
                                                                 DRO_BLK()_RG()_MASK when enable is set. */
        uint64_t cfg_wr_er             : 1;  /**< [  4:  4](R/W1C/H) Config register write error. Set to indicate a write operation was performed on
                                                                 DRO_BLK()_CFG_CTL when enable is set. */
        uint64_t reserved_5_63         : 59;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_error_s cn; */
};
typedef union bdk_dro_blkx_error bdk_dro_blkx_error_t;

static inline uint64_t BDK_DRO_BLKX_ERROR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_ERROR(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000020ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000020ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000020ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000020ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_ERROR", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_ERROR(a) bdk_dro_blkx_error_t
#define bustype_BDK_DRO_BLKX_ERROR(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_ERROR(a) "DRO_BLKX_ERROR"
#define busnum_BDK_DRO_BLKX_ERROR(a) (a)
#define arguments_BDK_DRO_BLKX_ERROR(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_force_clk_en
 *
 * INTERNAL: DRO Force Clock Enable Register
 *
 * This register controls the DRO.
 */
union bdk_dro_blkx_force_clk_en
{
    uint64_t u;
    struct bdk_dro_blkx_force_clk_en_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t clk_en                : 1;  /**< [  0:  0](R/W) Forces the conditional clocks on. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint64_t clk_en                : 1;  /**< [  0:  0](R/W) Forces the conditional clocks on. For diagnostic use only. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_force_clk_en_s cn; */
};
typedef union bdk_dro_blkx_force_clk_en bdk_dro_blkx_force_clk_en_t;

static inline uint64_t BDK_DRO_BLKX_FORCE_CLK_EN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_FORCE_CLK_EN(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000068ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000068ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000068ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000068ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_FORCE_CLK_EN", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_FORCE_CLK_EN(a) bdk_dro_blkx_force_clk_en_t
#define bustype_BDK_DRO_BLKX_FORCE_CLK_EN(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_FORCE_CLK_EN(a) "DRO_BLKX_FORCE_CLK_EN"
#define busnum_BDK_DRO_BLKX_FORCE_CLK_EN(a) (a)
#define arguments_BDK_DRO_BLKX_FORCE_CLK_EN(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_freeze
 *
 * INTERNAL: DRO Block Freeze Registers
 */
union bdk_dro_blkx_freeze
{
    uint64_t u;
    struct bdk_dro_blkx_freeze_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t freeze                : 16; /**< [ 15:  0](R/W/H) Number of 10 ns clocks to count before freezing counters.
                                                                 _ [FREEZE]\<0x0, ENABLE!=0x0 = RO counter running.
                                                                 _ [FREEZE]=0x0, ENABLE!=0x0 = RO counter frozen. */
#else /* Word 0 - Little Endian */
        uint64_t freeze                : 16; /**< [ 15:  0](R/W/H) Number of 10 ns clocks to count before freezing counters.
                                                                 _ [FREEZE]\<0x0, ENABLE!=0x0 = RO counter running.
                                                                 _ [FREEZE]=0x0, ENABLE!=0x0 = RO counter frozen. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_freeze_s cn9; */
    /* struct bdk_dro_blkx_freeze_s cn96xxp1; */
    struct bdk_dro_blkx_freeze_cn96xxp3
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t freeze                : 16; /**< [ 15:  0](R/W/H) Number of 10 ns clocks to count before freezing counters.
                                                                 _ [FREEZE]\<0x0, DRO_BLK()_ENABLE[ENABLE]!=0 = RO counter running.
                                                                 _ [FREEZE]=0x0, DRO_BLK()_ENABLE[ENABLE]!=0 = RO counter frozen.
                                                                 _ [FREEZE]\>=0x8000 is unpredictable. */
#else /* Word 0 - Little Endian */
        uint64_t freeze                : 16; /**< [ 15:  0](R/W/H) Number of 10 ns clocks to count before freezing counters.
                                                                 _ [FREEZE]\<0x0, DRO_BLK()_ENABLE[ENABLE]!=0 = RO counter running.
                                                                 _ [FREEZE]=0x0, DRO_BLK()_ENABLE[ENABLE]!=0 = RO counter frozen.
                                                                 _ [FREEZE]\>=0x8000 is unpredictable. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } cn96xxp3;
    /* struct bdk_dro_blkx_freeze_cn96xxp3 cn98xx; */
    /* struct bdk_dro_blkx_freeze_cn96xxp3 cnf95xx; */
    /* struct bdk_dro_blkx_freeze_cn96xxp3 loki; */
};
typedef union bdk_dro_blkx_freeze bdk_dro_blkx_freeze_t;

static inline uint64_t BDK_DRO_BLKX_FREEZE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_FREEZE(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000030ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000030ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000030ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000030ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_FREEZE", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_FREEZE(a) bdk_dro_blkx_freeze_t
#define bustype_BDK_DRO_BLKX_FREEZE(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_FREEZE(a) "DRO_BLKX_FREEZE"
#define busnum_BDK_DRO_BLKX_FREEZE(a) (a)
#define arguments_BDK_DRO_BLKX_FREEZE(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_rg#_mask
 *
 * INTERNAL: DRO Block Mask Registers
 */
union bdk_dro_blkx_rgx_mask
{
    uint64_t u;
    struct bdk_dro_blkx_rgx_mask_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t mask                  : 1;  /**< [  0:  0](R/W) DRO mask. Enable individual block or blocks and
                                                                 individual ring oscillator/oscillators within a block.
                                                                 0 = Block(s)/ring(s) disabled.
                                                                 1 = Block(s)/ring(s) enabled. */
#else /* Word 0 - Little Endian */
        uint64_t mask                  : 1;  /**< [  0:  0](R/W) DRO mask. Enable individual block or blocks and
                                                                 individual ring oscillator/oscillators within a block.
                                                                 0 = Block(s)/ring(s) disabled.
                                                                 1 = Block(s)/ring(s) enabled. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_rgx_mask_s cn; */
};
typedef union bdk_dro_blkx_rgx_mask bdk_dro_blkx_rgx_mask_t;

static inline uint64_t BDK_DRO_BLKX_RGX_MASK(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_RGX_MASK(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=13) && (b<=39)))
        return 0x87e008000028ll + 0x10000ll * ((a) & 0xf) + 0x100ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=19) && (b<=39)))
        return 0x87e008000028ll + 0x10000ll * ((a) & 0x1f) + 0x100ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=9) && (b<=39)))
        return 0x87e008000028ll + 0x10000ll * ((a) & 0xf) + 0x100ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=9) && (b<=39)))
        return 0x87e008000028ll + 0x10000ll * ((a) & 0xf) + 0x100ll * ((b) & 0x3f);
    __bdk_csr_fatal("DRO_BLKX_RGX_MASK", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_RGX_MASK(a,b) bdk_dro_blkx_rgx_mask_t
#define bustype_BDK_DRO_BLKX_RGX_MASK(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_RGX_MASK(a,b) "DRO_BLKX_RGX_MASK"
#define busnum_BDK_DRO_BLKX_RGX_MASK(a,b) (a)
#define arguments_BDK_DRO_BLKX_RGX_MASK(a,b) (a),(b),-1,-1

/**
 * Register (RSL) dro_blk#_rg#_read
 *
 * INTERNAL: DRO Block Ring Counter Registers
 */
union bdk_dro_blkx_rgx_read
{
    uint64_t u;
    struct bdk_dro_blkx_rgx_read_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_20_63        : 44;
        uint64_t count                 : 20; /**< [ 19:  0](RO/H) Count of number of ring loops completed within the freeze interval. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 20; /**< [ 19:  0](RO/H) Count of number of ring loops completed within the freeze interval. */
        uint64_t reserved_20_63        : 44;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_rgx_read_s cn; */
};
typedef union bdk_dro_blkx_rgx_read bdk_dro_blkx_rgx_read_t;

static inline uint64_t BDK_DRO_BLKX_RGX_READ(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_RGX_READ(unsigned long a, unsigned long b)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && ((a<=13) && (b<=39)))
        return 0x87e008000038ll + 0x10000ll * ((a) & 0xf) + 0x100ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_CN98XX) && ((a<=19) && (b<=39)))
        return 0x87e008000038ll + 0x10000ll * ((a) & 0x1f) + 0x100ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && ((a<=9) && (b<=39)))
        return 0x87e008000038ll + 0x10000ll * ((a) & 0xf) + 0x100ll * ((b) & 0x3f);
    if (bdk_is_model(OCTEONTX_LOKI) && ((a<=9) && (b<=39)))
        return 0x87e008000038ll + 0x10000ll * ((a) & 0xf) + 0x100ll * ((b) & 0x3f);
    __bdk_csr_fatal("DRO_BLKX_RGX_READ", 2, a, b, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_RGX_READ(a,b) bdk_dro_blkx_rgx_read_t
#define bustype_BDK_DRO_BLKX_RGX_READ(a,b) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_RGX_READ(a,b) "DRO_BLKX_RGX_READ"
#define busnum_BDK_DRO_BLKX_RGX_READ(a,b) (a)
#define arguments_BDK_DRO_BLKX_RGX_READ(a,b) (a),(b),-1,-1

/**
 * Register (RSL) dro_blk#_vdr_const
 *
 * INTERNAL: DRO Block VDR Constants Register
 *
 * This register contains info there a DRO has present or global feedback.Bit
 *     \<{a}\> corresponds to DRO BLK (\<a\>}. Bits enumerated by DRO_BLOCKS_E.
 */
union bdk_dro_blkx_vdr_const
{
    uint64_t u;
    struct bdk_dro_blkx_vdr_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t present               : 32; /**< [ 63: 32](RO) If set, that corresponding DRO BLK has a voltage droop detector present. Bit
                                                                 \<{a}\> corresponds to DRO BLK (\<a\>}. Bits enumerated by DRO_BLOCKS_E. */
        uint64_t dglobal               : 32; /**< [ 31:  0](RO) If set, that corresponding DRO BLK has a voltage droop detector with global
                                                                 feedback. Bit \<{a}\> corresponds to DRO BLK (\<a\>}. Bits enumerated by
                                                                 DRO_BLOCKS_E. */
#else /* Word 0 - Little Endian */
        uint64_t dglobal               : 32; /**< [ 31:  0](RO) If set, that corresponding DRO BLK has a voltage droop detector with global
                                                                 feedback. Bit \<{a}\> corresponds to DRO BLK (\<a\>}. Bits enumerated by
                                                                 DRO_BLOCKS_E. */
        uint64_t present               : 32; /**< [ 63: 32](RO) If set, that corresponding DRO BLK has a voltage droop detector present. Bit
                                                                 \<{a}\> corresponds to DRO BLK (\<a\>}. Bits enumerated by DRO_BLOCKS_E. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_vdr_const_s cn; */
};
typedef union bdk_dro_blkx_vdr_const bdk_dro_blkx_vdr_const_t;

static inline uint64_t BDK_DRO_BLKX_VDR_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_VDR_CONST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000070ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000070ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000070ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000070ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_VDR_CONST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_VDR_CONST(a) bdk_dro_blkx_vdr_const_t
#define bustype_BDK_DRO_BLKX_VDR_CONST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_VDR_CONST(a) "DRO_BLKX_VDR_CONST"
#define busnum_BDK_DRO_BLKX_VDR_CONST(a) (a)
#define arguments_BDK_DRO_BLKX_VDR_CONST(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_vdroop_ctl
 *
 * INTERNAL: DRO Block Voltage Droop Detector Control Register
 *
 * This register controls the voltage droop detector in the DROs if available.
 * For diagnostic use only.
 */
union bdk_dro_blkx_vdroop_ctl
{
    uint64_t u;
    struct bdk_dro_blkx_vdroop_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable voltage droop detection. */
        uint64_t reserved_4_62         : 59;
        uint64_t vref_sel              : 4;  /**< [  3:  0](R/W) Reference voltage setting. */
#else /* Word 0 - Little Endian */
        uint64_t vref_sel              : 4;  /**< [  3:  0](R/W) Reference voltage setting. */
        uint64_t reserved_4_62         : 59;
        uint64_t enable                : 1;  /**< [ 63: 63](R/W) Enable voltage droop detection. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_vdroop_ctl_s cn; */
};
typedef union bdk_dro_blkx_vdroop_ctl bdk_dro_blkx_vdroop_ctl_t;

static inline uint64_t BDK_DRO_BLKX_VDROOP_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_VDROOP_CTL(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000048ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000048ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000048ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000048ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_VDROOP_CTL", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_VDROOP_CTL(a) bdk_dro_blkx_vdroop_ctl_t
#define bustype_BDK_DRO_BLKX_VDROOP_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_VDROOP_CTL(a) "DRO_BLKX_VDROOP_CTL"
#define busnum_BDK_DRO_BLKX_VDROOP_CTL(a) (a)
#define arguments_BDK_DRO_BLKX_VDROOP_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_vdroop_local_cnt
 *
 * INTERNAL: DRO Block Voltage Droop Local Counter Register
 *
 * For diagnostic use only.
 */
union bdk_dro_blkx_vdroop_local_cnt
{
    uint64_t u;
    struct bdk_dro_blkx_vdroop_local_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_16_63        : 48;
        uint64_t count                 : 16; /**< [ 15:  0](RO/H) Voltage droop detector local counter, count of the rising edges of the droop detector. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 16; /**< [ 15:  0](RO/H) Voltage droop detector local counter, count of the rising edges of the droop detector. */
        uint64_t reserved_16_63        : 48;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_vdroop_local_cnt_s cn; */
};
typedef union bdk_dro_blkx_vdroop_local_cnt bdk_dro_blkx_vdroop_local_cnt_t;

static inline uint64_t BDK_DRO_BLKX_VDROOP_LOCAL_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_VDROOP_LOCAL_CNT(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000060ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000060ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000060ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000060ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_VDROOP_LOCAL_CNT", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_VDROOP_LOCAL_CNT(a) bdk_dro_blkx_vdroop_local_cnt_t
#define bustype_BDK_DRO_BLKX_VDROOP_LOCAL_CNT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_VDROOP_LOCAL_CNT(a) "DRO_BLKX_VDROOP_LOCAL_CNT"
#define busnum_BDK_DRO_BLKX_VDROOP_LOCAL_CNT(a) (a)
#define arguments_BDK_DRO_BLKX_VDROOP_LOCAL_CNT(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_vdroop_obs
 *
 * INTERNAL: DRO Block Voltage Droop Detector Observation Register
 *
 * This register observes the voltage droop detector in the DROs if available.
 * For diagnostic use only.
 */
union bdk_dro_blkx_vdroop_obs
{
    uint64_t u;
    struct bdk_dro_blkx_vdroop_obs_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t event_count           : 16; /**< [ 31: 16](R/W/H) Count of voltage droop events. */
        uint64_t reserved_3_15         : 13;
        uint64_t ddet                  : 1;  /**< [  2:  2](RO/H) Voltage droop detected. */
        uint64_t dglobal               : 1;  /**< [  1:  1](RO/H) Enable this voltage droop detector to participate in global droop mitigation logic. */
        uint64_t present               : 1;  /**< [  0:  0](RO/H) Voltage droop detector present. */
#else /* Word 0 - Little Endian */
        uint64_t present               : 1;  /**< [  0:  0](RO/H) Voltage droop detector present. */
        uint64_t dglobal               : 1;  /**< [  1:  1](RO/H) Enable this voltage droop detector to participate in global droop mitigation logic. */
        uint64_t ddet                  : 1;  /**< [  2:  2](RO/H) Voltage droop detected. */
        uint64_t reserved_3_15         : 13;
        uint64_t event_count           : 16; /**< [ 31: 16](R/W/H) Count of voltage droop events. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_vdroop_obs_s cn; */
};
typedef union bdk_dro_blkx_vdroop_obs bdk_dro_blkx_vdroop_obs_t;

static inline uint64_t BDK_DRO_BLKX_VDROOP_OBS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_VDROOP_OBS(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000050ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000050ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000050ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000050ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_VDROOP_OBS", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_VDROOP_OBS(a) bdk_dro_blkx_vdroop_obs_t
#define bustype_BDK_DRO_BLKX_VDROOP_OBS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_VDROOP_OBS(a) "DRO_BLKX_VDROOP_OBS"
#define busnum_BDK_DRO_BLKX_VDROOP_OBS(a) (a)
#define arguments_BDK_DRO_BLKX_VDROOP_OBS(a) (a),-1,-1,-1

/**
 * Register (RSL) dro_blk#_vdroop_rst
 *
 * INTERNAL: DRO Block Voltage Droop Detector Reset Register
 *
 * This register controls the droop detector. For diagnostic use only.
 */
union bdk_dro_blkx_vdroop_rst
{
    uint64_t u;
    struct bdk_dro_blkx_vdroop_rst_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_10_63        : 54;
        uint64_t rst                   : 10; /**< [  9:  0](R/W) Voltage droop detector reset. The value of the count down value. Once the 10 bit
                                                                 counter value reaches zero it triggers the reset of the droop detector. */
#else /* Word 0 - Little Endian */
        uint64_t rst                   : 10; /**< [  9:  0](R/W) Voltage droop detector reset. The value of the count down value. Once the 10 bit
                                                                 counter value reaches zero it triggers the reset of the droop detector. */
        uint64_t reserved_10_63        : 54;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_dro_blkx_vdroop_rst_s cn; */
};
typedef union bdk_dro_blkx_vdroop_rst bdk_dro_blkx_vdroop_rst_t;

static inline uint64_t BDK_DRO_BLKX_VDROOP_RST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_DRO_BLKX_VDROOP_RST(unsigned long a)
{
    if (bdk_is_model(OCTEONTX_CN96XX) && (a<=13))
        return 0x87e008000058ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_CN98XX) && (a<=19))
        return 0x87e008000058ll + 0x10000ll * ((a) & 0x1f);
    if (bdk_is_model(OCTEONTX_CNF95XX) && (a<=9))
        return 0x87e008000058ll + 0x10000ll * ((a) & 0xf);
    if (bdk_is_model(OCTEONTX_LOKI) && (a<=9))
        return 0x87e008000058ll + 0x10000ll * ((a) & 0xf);
    __bdk_csr_fatal("DRO_BLKX_VDROOP_RST", 1, a, 0, 0, 0, 0, 0);
}

#define typedef_BDK_DRO_BLKX_VDROOP_RST(a) bdk_dro_blkx_vdroop_rst_t
#define bustype_BDK_DRO_BLKX_VDROOP_RST(a) BDK_CSR_TYPE_RSL
#define basename_BDK_DRO_BLKX_VDROOP_RST(a) "DRO_BLKX_VDROOP_RST"
#define busnum_BDK_DRO_BLKX_VDROOP_RST(a) (a)
#define arguments_BDK_DRO_BLKX_VDROOP_RST(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_DRO_H__ */
