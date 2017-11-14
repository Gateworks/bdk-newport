#ifndef __BDK_CSRS_XCP_H__
#define __BDK_CSRS_XCP_H__
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
 * Cavium XCP.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration xcp_addr_prt_e
 *
 * XCP Address Partition Enumeration
 * Enumerates the partitions in MIPS address space, as recorded in XCP()_PRECISE_BUS_ERR_STATUS[PART].
 */
#define BDK_XCP_ADDR_PRT_E_CSR_CPC (3)
#define BDK_XCP_ADDR_PRT_E_CSR_PSBM (4)
#define BDK_XCP_ADDR_PRT_E_CSR_XCP (2)
#define BDK_XCP_ADDR_PRT_E_MEM (1)
#define BDK_XCP_ADDR_PRT_E_NCB (5)
#define BDK_XCP_ADDR_PRT_E_NONE (0)
#define BDK_XCP_ADDR_PRT_E_RML (6)

/**
 * Enumeration xcp_bar_e
 *
 * XCP Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_XCP_BAR_E_XCPX_PF_BAR0(a) (0x82c000000000ll + 0x1000000000ll * (a))
#define BDK_XCP_BAR_E_XCPX_PF_BAR0_SIZE 0x100000ull
#define BDK_XCP_BAR_E_XCPX_PF_BAR4(a) (0x82c000100000ll + 0x1000000000ll * (a))
#define BDK_XCP_BAR_E_XCPX_PF_BAR4_SIZE 0x100000ull

/**
 * Enumeration xcp_dintf_err_type_e
 *
 * XCP Data Interface Precise Error Enumeration
 * Enumerates the precise error types, as recorded in XCP()_PRECISE_BUS_ERR_STATUS[ERR_TYPE].
 */
#define BDK_XCP_DINTF_ERR_TYPE_E_ACCESS_ERR (3)
#define BDK_XCP_DINTF_ERR_TYPE_E_ERR_NCB_CORE_RESET (7)
#define BDK_XCP_DINTF_ERR_TYPE_E_INV_ADDR (2)
#define BDK_XCP_DINTF_ERR_TYPE_E_NO_ERR (0)
#define BDK_XCP_DINTF_ERR_TYPE_E_RD_ERR_NCB_BUS_FLT (4)
#define BDK_XCP_DINTF_ERR_TYPE_E_RD_ERR_NCB_BUS_PSN (5)
#define BDK_XCP_DINTF_ERR_TYPE_E_RD_ERR_NCB_TIMEOUT (6)
#define BDK_XCP_DINTF_ERR_TYPE_E_UMPD_ADDR (1)

/**
 * Enumeration xcp_int_vec_e
 *
 * XCP MSI-X Vector Enumeration
 * Enumerates the MSI-X interrupt vectors.
 */
#define BDK_XCP_INT_VEC_E_XCP_DEV_MBOXX(a) (0 + (a))

/**
 * Enumeration xcp_mbox_dev_e
 *
 * XCP Mailbox Device ID Enumeration
 * Enumerates the device ID for MBOX registers.
 */
#define BDK_XCP_MBOX_DEV_E_AP_NONSECURE0 (2)
#define BDK_XCP_MBOX_DEV_E_AP_NONSECURE1 (3)
#define BDK_XCP_MBOX_DEV_E_AP_SECURE0 (0)
#define BDK_XCP_MBOX_DEV_E_AP_SECURE1 (1)
#define BDK_XCP_MBOX_DEV_E_MCP_LOCAL (5)
#define BDK_XCP_MBOX_DEV_E_MCP_REMOTE (7)
#define BDK_XCP_MBOX_DEV_E_SCP_LOCAL (4)
#define BDK_XCP_MBOX_DEV_E_SCP_REMOTE (6)

/**
 * Enumeration xcp_mips_vec_int_e
 *
 * XCP MIPS Vectored Interrupt Enumeration
 * Enumerates the 8-bit vectored maskable interrupt input to the MIPS core.
 */
#define BDK_XCP_MIPS_VEC_INT_E_BUS_ERR (7)
#define BDK_XCP_MIPS_VEC_INT_E_GIB0 (1)
#define BDK_XCP_MIPS_VEC_INT_E_GIB1 (2)
#define BDK_XCP_MIPS_VEC_INT_E_GIB2 (3)
#define BDK_XCP_MIPS_VEC_INT_E_MBOX (0)
#define BDK_XCP_MIPS_VEC_INT_E_RESERVED (4)
#define BDK_XCP_MIPS_VEC_INT_E_TIMER (5)
#define BDK_XCP_MIPS_VEC_INT_E_WDOG (6)

/**
 * Structure xcp_bp_test0_bp_cfg_s
 *
 * INTERNAL: XCP Backpressure Test 0 Configuration Structure
 *
 * XCP()_BP_TEST0[BP_CFG] field structure for bit connections to fifos.
 */
union bdk_xcp_bp_test0_bp_cfg_s
{
    uint32_t u;
    struct bdk_xcp_bp_test0_bp_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t xcp_ncb_r_dctl_tx_fifo : 2; /**< [  3:  2] Config for xcp_ncb_r_dctl_tx_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
        uint32_t xcp_ncb_r_dctl_tx_fifo : 2; /**< [  3:  2] Config for xcp_ncb_r_dctl_tx_fifo. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    struct bdk_xcp_bp_test0_bp_cfg_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_14_31        : 18;
        uint32_t reserved_4_13         : 10;
        uint32_t xcp_ncb_r_dctl_tx_fifo : 2; /**< [  3:  2] Config for xcp_ncb_r_dctl_tx_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
        uint32_t xcp_ncb_r_dctl_tx_fifo : 2; /**< [  3:  2] Config for xcp_ncb_r_dctl_tx_fifo. */
        uint32_t reserved_4_13         : 10;
        uint32_t reserved_14_31        : 18;
#endif /* Word 0 - End */
    } cn;
};

/**
 * Structure xcp_bp_test0_enable_s
 *
 * INTERNAL: XCP Backpressure Test 0 Enable Structure
 *
 * XCP()_BP_TEST0[ENABLE] field structure for bit connections to fifos.
 */
union bdk_xcp_bp_test0_enable_s
{
    uint32_t u;
    struct bdk_xcp_bp_test0_enable_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_2_31         : 30;
        uint32_t xcp_ncb_r_dctl_tx_fifo : 1; /**< [  1:  1] ENABLE for xcp_ncb_r_dctl_tx_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
        uint32_t xcp_ncb_r_dctl_tx_fifo : 1; /**< [  1:  1] ENABLE for xcp_ncb_r_dctl_tx_fifo. */
        uint32_t reserved_2_31         : 30;
#endif /* Word 0 - End */
    } s;
    struct bdk_xcp_bp_test0_enable_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_7_31         : 25;
        uint32_t reserved_2_6          : 5;
        uint32_t xcp_ncb_r_dctl_tx_fifo : 1; /**< [  1:  1] ENABLE for xcp_ncb_r_dctl_tx_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
        uint32_t xcp_ncb_r_dctl_tx_fifo : 1; /**< [  1:  1] ENABLE for xcp_ncb_r_dctl_tx_fifo. */
        uint32_t reserved_2_6          : 5;
        uint32_t reserved_7_31         : 25;
#endif /* Word 0 - End */
    } cn;
};

/**
 * Register (NCB32b) xcp#_accum_empty
 *
 * XCP Write Accumulator Empty Register
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_accum_empty
{
    uint32_t u;
    struct bdk_xcpx_accum_empty_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t empty                 : 1;  /**< [  0:  0](WO/H) Writing a one will cause any write data that is buffered in the write accumulator
                                                                 to be flushed to the downstream logic, preventing subsequent writes from merging
                                                                 with any writes accumulated before this register was written. */
#else /* Word 0 - Little Endian */
        uint32_t empty                 : 1;  /**< [  0:  0](WO/H) Writing a one will cause any write data that is buffered in the write accumulator
                                                                 to be flushed to the downstream logic, preventing subsequent writes from merging
                                                                 with any writes accumulated before this register was written. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_accum_empty_s cn; */
};
typedef union bdk_xcpx_accum_empty bdk_xcpx_accum_empty_t;

static inline uint64_t BDK_XCPX_ACCUM_EMPTY(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_ACCUM_EMPTY(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000a00ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_ACCUM_EMPTY", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_ACCUM_EMPTY(a) bdk_xcpx_accum_empty_t
#define bustype_BDK_XCPX_ACCUM_EMPTY(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_ACCUM_EMPTY(a) "XCPX_ACCUM_EMPTY"
#define device_bar_BDK_XCPX_ACCUM_EMPTY(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_ACCUM_EMPTY(a) (a)
#define arguments_BDK_XCPX_ACCUM_EMPTY(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_boot_jump
 *
 * XCP Boot Jump Register
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_xcpx_boot_jump
{
    uint32_t u;
    struct bdk_xcpx_boot_jump_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t addr                  : 32; /**< [ 31:  0](R/W) The XCP ROM firmware reads this register immediately after reset and jumps to
                                                                 this address if nonzero. */
#else /* Word 0 - Little Endian */
        uint32_t addr                  : 32; /**< [ 31:  0](R/W) The XCP ROM firmware reads this register immediately after reset and jumps to
                                                                 this address if nonzero. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_boot_jump_s cn; */
};
typedef union bdk_xcpx_boot_jump bdk_xcpx_boot_jump_t;

static inline uint64_t BDK_XCPX_BOOT_JUMP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_BOOT_JUMP(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000130ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_BOOT_JUMP", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_BOOT_JUMP(a) bdk_xcpx_boot_jump_t
#define bustype_BDK_XCPX_BOOT_JUMP(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_BOOT_JUMP(a) "XCPX_BOOT_JUMP"
#define device_bar_BDK_XCPX_BOOT_JUMP(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_BOOT_JUMP(a) (a)
#define arguments_BDK_XCPX_BOOT_JUMP(a) (a),-1,-1,-1

/**
 * Register (NCB) xcp#_bp_test0
 *
 * INTERNAL: XCP Backpressure Test Register
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_bp_test0
{
    uint64_t u;
    struct bdk_xcpx_bp_test0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 7;  /**< [ 63: 57](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 Refer to XCP_BP_TEST0_ENABLE_S for field bit descriptions and layout. */
        uint64_t reserved_48_56        : 9;
        uint64_t bp_cfg                : 14; /**< [ 47: 34](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 Refer to XCP_BP_TEST0_BP_CFG_S for field bit descriptions and layout. */
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
                                                                 Refer to XCP_BP_TEST0_BP_CFG_S for field bit descriptions and layout. */
        uint64_t reserved_48_56        : 9;
        uint64_t enable                : 7;  /**< [ 63: 57](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 Refer to XCP_BP_TEST0_ENABLE_S for field bit descriptions and layout. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_bp_test0_s cn; */
};
typedef union bdk_xcpx_bp_test0 bdk_xcpx_bp_test0_t;

static inline uint64_t BDK_XCPX_BP_TEST0(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_BP_TEST0(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c00000e000ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_BP_TEST0", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_BP_TEST0(a) bdk_xcpx_bp_test0_t
#define bustype_BDK_XCPX_BP_TEST0(a) BDK_CSR_TYPE_NCB
#define basename_BDK_XCPX_BP_TEST0(a) "XCPX_BP_TEST0"
#define device_bar_BDK_XCPX_BP_TEST0(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_BP_TEST0(a) (a)
#define arguments_BDK_XCPX_BP_TEST0(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_bus_err_lint
 *
 * XCP Bus error Interrupt Register
 * This register contains imprecise NCB bus error interrupt for XCP.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_bus_err_lint
{
    uint32_t u;
    struct bdk_xcpx_bus_err_lint_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t core_rst_int          : 1;  /**< [  9:  9](R/W1C/H) Write timeout. */
        uint32_t reserved_8            : 1;
        uint32_t wr_to_int             : 1;  /**< [  7:  7](R/W1C/H) Write timeout. */
        uint32_t wr_flt_int            : 1;  /**< [  6:  6](R/W1C/H) Write fault. */
        uint32_t wr_psn_int            : 1;  /**< [  5:  5](R/W1C/H) Write poison. Write poison is typically deferred, and thus this interrupt is typically ignored. */
        uint32_t reserved_3_4          : 2;
        uint32_t rd_to_int             : 1;  /**< [  2:  2](R/W1C/H) Read timeout. */
        uint32_t rd_flt_int            : 1;  /**< [  1:  1](R/W1C/H) Read fault. */
        uint32_t rd_psn_int            : 1;  /**< [  0:  0](R/W1C/H) Read poison. */
#else /* Word 0 - Little Endian */
        uint32_t rd_psn_int            : 1;  /**< [  0:  0](R/W1C/H) Read poison. */
        uint32_t rd_flt_int            : 1;  /**< [  1:  1](R/W1C/H) Read fault. */
        uint32_t rd_to_int             : 1;  /**< [  2:  2](R/W1C/H) Read timeout. */
        uint32_t reserved_3_4          : 2;
        uint32_t wr_psn_int            : 1;  /**< [  5:  5](R/W1C/H) Write poison. Write poison is typically deferred, and thus this interrupt is typically ignored. */
        uint32_t wr_flt_int            : 1;  /**< [  6:  6](R/W1C/H) Write fault. */
        uint32_t wr_to_int             : 1;  /**< [  7:  7](R/W1C/H) Write timeout. */
        uint32_t reserved_8            : 1;
        uint32_t core_rst_int          : 1;  /**< [  9:  9](R/W1C/H) Write timeout. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_bus_err_lint_s cn; */
};
typedef union bdk_xcpx_bus_err_lint bdk_xcpx_bus_err_lint_t;

static inline uint64_t BDK_XCPX_BUS_ERR_LINT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_BUS_ERR_LINT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000001c00ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_BUS_ERR_LINT", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_BUS_ERR_LINT(a) bdk_xcpx_bus_err_lint_t
#define bustype_BDK_XCPX_BUS_ERR_LINT(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_BUS_ERR_LINT(a) "XCPX_BUS_ERR_LINT"
#define device_bar_BDK_XCPX_BUS_ERR_LINT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_BUS_ERR_LINT(a) (a)
#define arguments_BDK_XCPX_BUS_ERR_LINT(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_bus_err_lint_ena_w1c
 *
 * XCP NCB bus error Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_xcpx_bus_err_lint_ena_w1c
{
    uint32_t u;
    struct bdk_xcpx_bus_err_lint_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t core_rst_int          : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[CORE_RST_INT]. */
        uint32_t reserved_8            : 1;
        uint32_t wr_to_int             : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[WR_TO_INT]. */
        uint32_t wr_flt_int            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[WR_FLT_INT]. */
        uint32_t wr_psn_int            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[WR_PSN_INT]. */
        uint32_t reserved_3_4          : 2;
        uint32_t rd_to_int             : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[RD_TO_INT]. */
        uint32_t rd_flt_int            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[RD_FLT_INT]. */
        uint32_t rd_psn_int            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[RD_PSN_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t rd_psn_int            : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[RD_PSN_INT]. */
        uint32_t rd_flt_int            : 1;  /**< [  1:  1](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[RD_FLT_INT]. */
        uint32_t rd_to_int             : 1;  /**< [  2:  2](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[RD_TO_INT]. */
        uint32_t reserved_3_4          : 2;
        uint32_t wr_psn_int            : 1;  /**< [  5:  5](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[WR_PSN_INT]. */
        uint32_t wr_flt_int            : 1;  /**< [  6:  6](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[WR_FLT_INT]. */
        uint32_t wr_to_int             : 1;  /**< [  7:  7](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[WR_TO_INT]. */
        uint32_t reserved_8            : 1;
        uint32_t core_rst_int          : 1;  /**< [  9:  9](R/W1C/H) Reads or clears enable for XCP(0..1)_BUS_ERR_LINT[CORE_RST_INT]. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_bus_err_lint_ena_w1c_s cn; */
};
typedef union bdk_xcpx_bus_err_lint_ena_w1c bdk_xcpx_bus_err_lint_ena_w1c_t;

static inline uint64_t BDK_XCPX_BUS_ERR_LINT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_BUS_ERR_LINT_ENA_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000001cc0ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_BUS_ERR_LINT_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_BUS_ERR_LINT_ENA_W1C(a) bdk_xcpx_bus_err_lint_ena_w1c_t
#define bustype_BDK_XCPX_BUS_ERR_LINT_ENA_W1C(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_BUS_ERR_LINT_ENA_W1C(a) "XCPX_BUS_ERR_LINT_ENA_W1C"
#define device_bar_BDK_XCPX_BUS_ERR_LINT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_BUS_ERR_LINT_ENA_W1C(a) (a)
#define arguments_BDK_XCPX_BUS_ERR_LINT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_bus_err_lint_ena_w1s
 *
 * XCP NCB bus error Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_xcpx_bus_err_lint_ena_w1s
{
    uint32_t u;
    struct bdk_xcpx_bus_err_lint_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t core_rst_int          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[CORE_RST_INT]. */
        uint32_t reserved_8            : 1;
        uint32_t wr_to_int             : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[WR_TO_INT]. */
        uint32_t wr_flt_int            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[WR_FLT_INT]. */
        uint32_t wr_psn_int            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[WR_PSN_INT]. */
        uint32_t reserved_3_4          : 2;
        uint32_t rd_to_int             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[RD_TO_INT]. */
        uint32_t rd_flt_int            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[RD_FLT_INT]. */
        uint32_t rd_psn_int            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[RD_PSN_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t rd_psn_int            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[RD_PSN_INT]. */
        uint32_t rd_flt_int            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[RD_FLT_INT]. */
        uint32_t rd_to_int             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[RD_TO_INT]. */
        uint32_t reserved_3_4          : 2;
        uint32_t wr_psn_int            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[WR_PSN_INT]. */
        uint32_t wr_flt_int            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[WR_FLT_INT]. */
        uint32_t wr_to_int             : 1;  /**< [  7:  7](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[WR_TO_INT]. */
        uint32_t reserved_8            : 1;
        uint32_t core_rst_int          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets enable for XCP(0..1)_BUS_ERR_LINT[CORE_RST_INT]. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_bus_err_lint_ena_w1s_s cn; */
};
typedef union bdk_xcpx_bus_err_lint_ena_w1s bdk_xcpx_bus_err_lint_ena_w1s_t;

static inline uint64_t BDK_XCPX_BUS_ERR_LINT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_BUS_ERR_LINT_ENA_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000001ce0ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_BUS_ERR_LINT_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_BUS_ERR_LINT_ENA_W1S(a) bdk_xcpx_bus_err_lint_ena_w1s_t
#define bustype_BDK_XCPX_BUS_ERR_LINT_ENA_W1S(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_BUS_ERR_LINT_ENA_W1S(a) "XCPX_BUS_ERR_LINT_ENA_W1S"
#define device_bar_BDK_XCPX_BUS_ERR_LINT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_BUS_ERR_LINT_ENA_W1S(a) (a)
#define arguments_BDK_XCPX_BUS_ERR_LINT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_bus_err_lint_w1s
 *
 * XCP NCB bus error Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_xcpx_bus_err_lint_w1s
{
    uint32_t u;
    struct bdk_xcpx_bus_err_lint_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_10_31        : 22;
        uint32_t core_rst_int          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[CORE_RST_INT]. */
        uint32_t reserved_8            : 1;
        uint32_t wr_to_int             : 1;  /**< [  7:  7](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[WR_TO_INT]. */
        uint32_t wr_flt_int            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[WR_FLT_INT]. */
        uint32_t wr_psn_int            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[WR_PSN_INT]. */
        uint32_t reserved_3_4          : 2;
        uint32_t rd_to_int             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[RD_TO_INT]. */
        uint32_t rd_flt_int            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[RD_FLT_INT]. */
        uint32_t rd_psn_int            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[RD_PSN_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t rd_psn_int            : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[RD_PSN_INT]. */
        uint32_t rd_flt_int            : 1;  /**< [  1:  1](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[RD_FLT_INT]. */
        uint32_t rd_to_int             : 1;  /**< [  2:  2](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[RD_TO_INT]. */
        uint32_t reserved_3_4          : 2;
        uint32_t wr_psn_int            : 1;  /**< [  5:  5](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[WR_PSN_INT]. */
        uint32_t wr_flt_int            : 1;  /**< [  6:  6](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[WR_FLT_INT]. */
        uint32_t wr_to_int             : 1;  /**< [  7:  7](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[WR_TO_INT]. */
        uint32_t reserved_8            : 1;
        uint32_t core_rst_int          : 1;  /**< [  9:  9](R/W1S/H) Reads or sets XCP(0..1)_BUS_ERR_LINT[CORE_RST_INT]. */
        uint32_t reserved_10_31        : 22;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_bus_err_lint_w1s_s cn; */
};
typedef union bdk_xcpx_bus_err_lint_w1s bdk_xcpx_bus_err_lint_w1s_t;

static inline uint64_t BDK_XCPX_BUS_ERR_LINT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_BUS_ERR_LINT_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000001c80ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_BUS_ERR_LINT_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_BUS_ERR_LINT_W1S(a) bdk_xcpx_bus_err_lint_w1s_t
#define bustype_BDK_XCPX_BUS_ERR_LINT_W1S(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_BUS_ERR_LINT_W1S(a) "XCPX_BUS_ERR_LINT_W1S"
#define device_bar_BDK_XCPX_BUS_ERR_LINT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_BUS_ERR_LINT_W1S(a) (a)
#define arguments_BDK_XCPX_BUS_ERR_LINT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cfg
 *
 * XCP Configuration Register
 * This register contains the configuration bits for XCP.
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 * Software must do a flush then sync before changing values in this register.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_cfg
{
    uint32_t u;
    struct bdk_xcpx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t ld_type               : 1;  /**< [  7:  7](R/W) Load type for stores out of XCP to IOB via NCBI.
                                                                 0 = LDD (allocates in LLC).
                                                                 1 = LDT (noallocate in LLC). */
        uint32_t st_type               : 1;  /**< [  6:  6](R/W) Store type for stores out of XCP to IOB via NCBI.
                                                                 0 = STP (allocate in LLC).
                                                                 1 = STT (noallocate in LLC). */
        uint32_t node_id               : 2;  /**< [  5:  4](RO/H) Dode ID associated with the chip. */
        uint32_t prefetch_dis          : 1;  /**< [  3:  3](R/W) Disable instruction prefetching.  For diagnostic use only.
                                                                 To disable prefecthing XCP needs to be in reset. */
        uint32_t accum_dis             : 1;  /**< [  2:  2](R/W) Accumulation disable.

                                                                 0 = Window will accumulate writes.  When multiple writes are accumulated then
                                                                 sent out this may result in "holes" in the byte enables within a cache line. Not
                                                                 all I/O devices can handle this, for example PEM will ignore the hole and write
                                                                 all intermediate bytes (which were not marked as supposed to be written.) Thus
                                                                 [ACCUM_DIS] should be one for I/O devices, or MIPS SYNC operations must be used
                                                                 to flush between non-mergable stores.

                                                                 1 = Writes are not accumulated, every individual write is sent to NCB.

                                                                 Ignored and acts as if set when XCP()_WIN()_CFG[RSL_NCB_N] = 1 (RSL).

                                                                 Software must do a sync before setting [ACCUM_DIS] or write data may be dropped. */
        uint32_t sync_inv_rdc          : 1;  /**< [  1:  1](R/W) If set, invalidate all windows read caches on a sync operation. */
        uint32_t ro_dis                : 1;  /**< [  0:  0](R/W) Disable for XCP NCB relaxed ordering (ro) bit on NCBI transactions. */
#else /* Word 0 - Little Endian */
        uint32_t ro_dis                : 1;  /**< [  0:  0](R/W) Disable for XCP NCB relaxed ordering (ro) bit on NCBI transactions. */
        uint32_t sync_inv_rdc          : 1;  /**< [  1:  1](R/W) If set, invalidate all windows read caches on a sync operation. */
        uint32_t accum_dis             : 1;  /**< [  2:  2](R/W) Accumulation disable.

                                                                 0 = Window will accumulate writes.  When multiple writes are accumulated then
                                                                 sent out this may result in "holes" in the byte enables within a cache line. Not
                                                                 all I/O devices can handle this, for example PEM will ignore the hole and write
                                                                 all intermediate bytes (which were not marked as supposed to be written.) Thus
                                                                 [ACCUM_DIS] should be one for I/O devices, or MIPS SYNC operations must be used
                                                                 to flush between non-mergable stores.

                                                                 1 = Writes are not accumulated, every individual write is sent to NCB.

                                                                 Ignored and acts as if set when XCP()_WIN()_CFG[RSL_NCB_N] = 1 (RSL).

                                                                 Software must do a sync before setting [ACCUM_DIS] or write data may be dropped. */
        uint32_t prefetch_dis          : 1;  /**< [  3:  3](R/W) Disable instruction prefetching.  For diagnostic use only.
                                                                 To disable prefecthing XCP needs to be in reset. */
        uint32_t node_id               : 2;  /**< [  5:  4](RO/H) Dode ID associated with the chip. */
        uint32_t st_type               : 1;  /**< [  6:  6](R/W) Store type for stores out of XCP to IOB via NCBI.
                                                                 0 = STP (allocate in LLC).
                                                                 1 = STT (noallocate in LLC). */
        uint32_t ld_type               : 1;  /**< [  7:  7](R/W) Load type for stores out of XCP to IOB via NCBI.
                                                                 0 = LDD (allocates in LLC).
                                                                 1 = LDT (noallocate in LLC). */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cfg_s cn; */
};
typedef union bdk_xcpx_cfg bdk_xcpx_cfg_t;

static inline uint64_t BDK_XCPX_CFG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CFG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000200ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CFG", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CFG(a) bdk_xcpx_cfg_t
#define bustype_BDK_XCPX_CFG(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CFG(a) "XCPX_CFG"
#define device_bar_BDK_XCPX_CFG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CFG(a) (a)
#define arguments_BDK_XCPX_CFG(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_clken
 *
 * XCP Clock Enable Register
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_clken
{
    uint32_t u;
    struct bdk_xcpx_clken_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t clken                 : 1;  /**< [  0:  0](R/W) Force the conditional clocking within XCP to be always on. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint32_t clken                 : 1;  /**< [  0:  0](R/W) Force the conditional clocking within XCP to be always on. For diagnostic use only. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_clken_s cn; */
};
typedef union bdk_xcpx_clken bdk_xcpx_clken_t;

static inline uint64_t BDK_XCPX_CLKEN(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CLKEN(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000010ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CLKEN", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CLKEN(a) bdk_xcpx_clken_t
#define bustype_BDK_XCPX_CLKEN(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CLKEN(a) "XCPX_CLKEN"
#define device_bar_BDK_XCPX_CLKEN(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CLKEN(a) (a)
#define arguments_BDK_XCPX_CLKEN(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cold_data
 *
 * XCP Cold Reset Data Register
 * Opaque data preserved through XCP and warm resets. Reset on cold reset.  This register is not
 * reset on trusted-mode changes, so must not contain keys/secrets.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on cold reset.
 */
union bdk_xcpx_cold_data
{
    uint32_t u;
    struct bdk_xcpx_cold_data_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t force_secondary       : 1;  /**< [ 31: 31](R/W) Force SCP_BL0 code to only attempt boots from the secondary boot device. SCP_BL1
                                                                 code may set this if an AP or MCP cannot be loaded from the primary, so that a
                                                                 reboot will load all of SCP_BL1, MCP_BL1, and AP_BL1 from the secondary devices
                                                                 so all the images match. */
        uint32_t data                  : 31; /**< [ 30:  0](R/W) Opaque data preserved through XCP and warm resets.   This register is not reset on trusted-mode
                                                                 changes, so must not contain keys/secrets. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 31; /**< [ 30:  0](R/W) Opaque data preserved through XCP and warm resets.   This register is not reset on trusted-mode
                                                                 changes, so must not contain keys/secrets. */
        uint32_t force_secondary       : 1;  /**< [ 31: 31](R/W) Force SCP_BL0 code to only attempt boots from the secondary boot device. SCP_BL1
                                                                 code may set this if an AP or MCP cannot be loaded from the primary, so that a
                                                                 reboot will load all of SCP_BL1, MCP_BL1, and AP_BL1 from the secondary devices
                                                                 so all the images match. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cold_data_s cn; */
};
typedef union bdk_xcpx_cold_data bdk_xcpx_cold_data_t;

static inline uint64_t BDK_XCPX_COLD_DATA(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_COLD_DATA(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c0000da000ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_COLD_DATA", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_COLD_DATA(a) bdk_xcpx_cold_data_t
#define bustype_BDK_XCPX_COLD_DATA(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_COLD_DATA(a) "XCPX_COLD_DATA"
#define device_bar_BDK_XCPX_COLD_DATA(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_COLD_DATA(a) (a)
#define arguments_BDK_XCPX_COLD_DATA(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cold_sticky_w1s
 *
 * XCP Cold Reset sticky W1S Register
 * Opaque data preserved through XCP and warm resets. Writes of one stay as one until next cold
 * reset; cannot write zeros.  This register is not reset on trusted-mode changes, so must not
 * contain keys/secrets.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on cold reset.
 */
union bdk_xcpx_cold_sticky_w1s
{
    uint32_t u;
    struct bdk_xcpx_cold_sticky_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t boot_sec              : 1;  /**< [ 31: 31](R/W1S/H) BL1 has booted in secure mode since last cold reset.  If both [BOOT_SEC] and [BOOT_NSEC]
                                                                 are set, then these bits are not trustworthy. */
        uint32_t boot_nsec             : 1;  /**< [ 30: 30](R/W1S/H) BL1 has booted in nonsecure mode since last cold reset.  If both [BOOT_SEC] and
                                                                 [BOOT_NSEC] are set, then these bits are not trustworthy. */
        uint32_t boot_rsvd             : 2;  /**< [ 29: 28](R/W1S/H) Reserved. */
        uint32_t data                  : 23; /**< [ 27:  5](R/W1S/H) Data. Opaque data preserved through XCP and warm resets. Writes of one stay as one until
                                                                 next cold reset; cannot write zeros.  This register is not reset on trusted-mode
                                                                 changes, so must not contain keys/secrets. */
        uint32_t bl1_sz_inv            : 5;  /**< [  4:  0](R/W1S/H) BL1 size (inverted). Indicates the number of regions used by MCP code.
                                                                 0x00 = BL1 can be as big as cpc_ram_size - 16KB. (First boot.)
                                                                 0x01 = BL1 can be as big a cpc_ram_size - 32KB.
                                                                 0x1E = BL1 can be as big as cpc_ram_size - 496KB.
                                                                 0x1F = BL1 can be as big as cpc_ram_size - 512KB. */
#else /* Word 0 - Little Endian */
        uint32_t bl1_sz_inv            : 5;  /**< [  4:  0](R/W1S/H) BL1 size (inverted). Indicates the number of regions used by MCP code.
                                                                 0x00 = BL1 can be as big as cpc_ram_size - 16KB. (First boot.)
                                                                 0x01 = BL1 can be as big a cpc_ram_size - 32KB.
                                                                 0x1E = BL1 can be as big as cpc_ram_size - 496KB.
                                                                 0x1F = BL1 can be as big as cpc_ram_size - 512KB. */
        uint32_t data                  : 23; /**< [ 27:  5](R/W1S/H) Data. Opaque data preserved through XCP and warm resets. Writes of one stay as one until
                                                                 next cold reset; cannot write zeros.  This register is not reset on trusted-mode
                                                                 changes, so must not contain keys/secrets. */
        uint32_t boot_rsvd             : 2;  /**< [ 29: 28](R/W1S/H) Reserved. */
        uint32_t boot_nsec             : 1;  /**< [ 30: 30](R/W1S/H) BL1 has booted in nonsecure mode since last cold reset.  If both [BOOT_SEC] and
                                                                 [BOOT_NSEC] are set, then these bits are not trustworthy. */
        uint32_t boot_sec              : 1;  /**< [ 31: 31](R/W1S/H) BL1 has booted in secure mode since last cold reset.  If both [BOOT_SEC] and [BOOT_NSEC]
                                                                 are set, then these bits are not trustworthy. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cold_sticky_w1s_s cn; */
};
typedef union bdk_xcpx_cold_sticky_w1s bdk_xcpx_cold_sticky_w1s_t;

static inline uint64_t BDK_XCPX_COLD_STICKY_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_COLD_STICKY_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c0000da040ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_COLD_STICKY_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_COLD_STICKY_W1S(a) bdk_xcpx_cold_sticky_w1s_t
#define bustype_BDK_XCPX_COLD_STICKY_W1S(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_COLD_STICKY_W1S(a) "XCPX_COLD_STICKY_W1S"
#define device_bar_BDK_XCPX_COLD_STICKY_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_COLD_STICKY_W1S(a) (a)
#define arguments_BDK_XCPX_COLD_STICKY_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_const
 *
 * XCP Constants Register
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_const
{
    uint32_t u;
    struct bdk_xcpx_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_8_31         : 24;
        uint32_t wins                  : 8;  /**< [  7:  0](RO) Number of windows supported. */
#else /* Word 0 - Little Endian */
        uint32_t wins                  : 8;  /**< [  7:  0](RO) Number of windows supported. */
        uint32_t reserved_8_31         : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_const_s cn; */
};
typedef union bdk_xcpx_const bdk_xcpx_const_t;

static inline uint64_t BDK_XCPX_CONST(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CONST(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000000ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CONST", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CONST(a) bdk_xcpx_const_t
#define bustype_BDK_XCPX_CONST(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CONST(a) "XCPX_CONST"
#define device_bar_BDK_XCPX_CONST(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CONST(a) (a)
#define arguments_BDK_XCPX_CONST(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cwd_lint
 *
 * XCP Per-core Watchdog Interrupt Register
 * Generic timer per XCP watchdog interrupts.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_cwd_lint
{
    uint32_t u;
    struct bdk_xcpx_cwd_lint_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1C/H) XCP watchdog interrupt. */
#else /* Word 0 - Little Endian */
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1C/H) XCP watchdog interrupt. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cwd_lint_s cn; */
};
typedef union bdk_xcpx_cwd_lint bdk_xcpx_cwd_lint_t;

static inline uint64_t BDK_XCPX_CWD_LINT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CWD_LINT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000040200ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CWD_LINT", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CWD_LINT(a) bdk_xcpx_cwd_lint_t
#define bustype_BDK_XCPX_CWD_LINT(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CWD_LINT(a) "XCPX_CWD_LINT"
#define device_bar_BDK_XCPX_CWD_LINT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CWD_LINT(a) (a)
#define arguments_BDK_XCPX_CWD_LINT(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cwd_lint_ena_w1c
 *
 * XCP Per-core Watchdog Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_xcpx_cwd_lint_ena_w1c
{
    uint32_t u;
    struct bdk_xcpx_cwd_lint_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_CWD_LINT[WDOG_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_CWD_LINT[WDOG_INT]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cwd_lint_ena_w1c_s cn; */
};
typedef union bdk_xcpx_cwd_lint_ena_w1c bdk_xcpx_cwd_lint_ena_w1c_t;

static inline uint64_t BDK_XCPX_CWD_LINT_ENA_W1C(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CWD_LINT_ENA_W1C(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000040210ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CWD_LINT_ENA_W1C", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CWD_LINT_ENA_W1C(a) bdk_xcpx_cwd_lint_ena_w1c_t
#define bustype_BDK_XCPX_CWD_LINT_ENA_W1C(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CWD_LINT_ENA_W1C(a) "XCPX_CWD_LINT_ENA_W1C"
#define device_bar_BDK_XCPX_CWD_LINT_ENA_W1C(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CWD_LINT_ENA_W1C(a) (a)
#define arguments_BDK_XCPX_CWD_LINT_ENA_W1C(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cwd_lint_ena_w1s
 *
 * XCP Per-core Watchdog Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_xcpx_cwd_lint_ena_w1s
{
    uint32_t u;
    struct bdk_xcpx_cwd_lint_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_CWD_LINT[WDOG_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_CWD_LINT[WDOG_INT]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cwd_lint_ena_w1s_s cn; */
};
typedef union bdk_xcpx_cwd_lint_ena_w1s bdk_xcpx_cwd_lint_ena_w1s_t;

static inline uint64_t BDK_XCPX_CWD_LINT_ENA_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CWD_LINT_ENA_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000040218ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CWD_LINT_ENA_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CWD_LINT_ENA_W1S(a) bdk_xcpx_cwd_lint_ena_w1s_t
#define bustype_BDK_XCPX_CWD_LINT_ENA_W1S(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CWD_LINT_ENA_W1S(a) "XCPX_CWD_LINT_ENA_W1S"
#define device_bar_BDK_XCPX_CWD_LINT_ENA_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CWD_LINT_ENA_W1S(a) (a)
#define arguments_BDK_XCPX_CWD_LINT_ENA_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cwd_lint_w1s
 *
 * XCP Per-core Watchdog Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_xcpx_cwd_lint_w1s
{
    uint32_t u;
    struct bdk_xcpx_cwd_lint_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_CWD_LINT[WDOG_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_CWD_LINT[WDOG_INT]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cwd_lint_w1s_s cn; */
};
typedef union bdk_xcpx_cwd_lint_w1s bdk_xcpx_cwd_lint_w1s_t;

static inline uint64_t BDK_XCPX_CWD_LINT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CWD_LINT_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000040208ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CWD_LINT_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CWD_LINT_W1S(a) bdk_xcpx_cwd_lint_w1s_t
#define bustype_BDK_XCPX_CWD_LINT_W1S(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CWD_LINT_W1S(a) "XCPX_CWD_LINT_W1S"
#define device_bar_BDK_XCPX_CWD_LINT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CWD_LINT_W1S(a) (a)
#define arguments_BDK_XCPX_CWD_LINT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cwd_nm_lint
 *
 * XCP Per-core Watchdog non-maskable Interrupt Register
 * Generic timer per XCP watchdog non-maskable interrupts.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_cwd_nm_lint
{
    uint32_t u;
    struct bdk_xcpx_cwd_nm_lint_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1C/H) XCP watchdog non-maskable interrupt. */
#else /* Word 0 - Little Endian */
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1C/H) XCP watchdog non-maskable interrupt. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cwd_nm_lint_s cn; */
};
typedef union bdk_xcpx_cwd_nm_lint bdk_xcpx_cwd_nm_lint_t;

static inline uint64_t BDK_XCPX_CWD_NM_LINT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CWD_NM_LINT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000041200ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CWD_NM_LINT", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CWD_NM_LINT(a) bdk_xcpx_cwd_nm_lint_t
#define bustype_BDK_XCPX_CWD_NM_LINT(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CWD_NM_LINT(a) "XCPX_CWD_NM_LINT"
#define device_bar_BDK_XCPX_CWD_NM_LINT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CWD_NM_LINT(a) (a)
#define arguments_BDK_XCPX_CWD_NM_LINT(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cwd_nm_lint_w1s
 *
 * XCP Per-core Watchdog non-maskable Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_xcpx_cwd_nm_lint_w1s
{
    uint32_t u;
    struct bdk_xcpx_cwd_nm_lint_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_CWD_NM_LINT[WDOG_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t wdog_int              : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_CWD_NM_LINT[WDOG_INT]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cwd_nm_lint_w1s_s cn; */
};
typedef union bdk_xcpx_cwd_nm_lint_w1s bdk_xcpx_cwd_nm_lint_w1s_t;

static inline uint64_t BDK_XCPX_CWD_NM_LINT_W1S(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CWD_NM_LINT_W1S(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000041208ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CWD_NM_LINT_W1S", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CWD_NM_LINT_W1S(a) bdk_xcpx_cwd_nm_lint_w1s_t
#define bustype_BDK_XCPX_CWD_NM_LINT_W1S(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CWD_NM_LINT_W1S(a) "XCPX_CWD_NM_LINT_W1S"
#define device_bar_BDK_XCPX_CWD_NM_LINT_W1S(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CWD_NM_LINT_W1S(a) (a)
#define arguments_BDK_XCPX_CWD_NM_LINT_W1S(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cwd_poke
 *
 * XCP Per-XCP Watchdog Poke Registers
 * Per-core watchdog poke. Writing any value to this register does the following:
 * * Clears any pending interrupt generated by the associated watchdog.
 * * Resets XCP()_CWD_WDOG[STATE] to 0x0.
 * * Sets XCP()_CWD_WDOG[CNT] to (XCP()_CWD_WDOG[LEN] \<\< 8)..
 *
 * Reading this register returns the associated XCP()_CWD_WDOG register.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_cwd_poke
{
    uint32_t u;
    struct bdk_xcpx_cwd_poke_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t ign                   : 32; /**< [ 31:  0](WO/H) Write will cause a poke to XCP()_CWD_WDOG. See XCP()_CWD_WDOG. */
#else /* Word 0 - Little Endian */
        uint32_t ign                   : 32; /**< [ 31:  0](WO/H) Write will cause a poke to XCP()_CWD_WDOG. See XCP()_CWD_WDOG. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cwd_poke_s cn; */
};
typedef union bdk_xcpx_cwd_poke bdk_xcpx_cwd_poke_t;

static inline uint64_t BDK_XCPX_CWD_POKE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CWD_POKE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c00000ee00ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CWD_POKE", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CWD_POKE(a) bdk_xcpx_cwd_poke_t
#define bustype_BDK_XCPX_CWD_POKE(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CWD_POKE(a) "XCPX_CWD_POKE"
#define device_bar_BDK_XCPX_CWD_POKE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CWD_POKE(a) (a)
#define arguments_BDK_XCPX_CWD_POKE(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_cwd_wdog
 *
 * XCP Per-XCP Watchdog Registers
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_cwd_wdog
{
    uint32_t u;
    struct bdk_xcpx_cwd_wdog_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t gstop                 : 1;  /**< [ 31: 31](R/W) Global-stop enable. */
        uint32_t dstop                 : 1;  /**< [ 30: 30](R/W) Debug-stop enable. */
        uint32_t cnt                   : 17; /**< [ 29: 13](R/W/H) Number of 10,240 us intervals until next watchdog expiration. Set on write to
                                                                 associated XCP()_CWD_POKE.

                                                                 Typically on each write to XCP()_CWD_WDOG, [CNT] should be set to [LEN] * 0x100. */
        uint32_t len                   : 9;  /**< [ 12:  4](R/W) Watchdog time-expiration length. The most-significant nine bits of a 17-bit value to be
                                                                 decremented every 10,240 us. */
        uint32_t state                 : 2;  /**< [  3:  2](R/W/H) Watchdog state. The number of watchdog time expirations since last core poke. Cleared on
                                                                 write to associated XCP()_CWD_POKE. */
        uint32_t mode                  : 2;  /**< [  1:  0](R/W) Watchdog mode:
                                                                 0x0 = Off.
                                                                 0x1 = (Maskable) Interrupt only.
                                                                 0x2 = (Maskable) Interrupt + NMI.
                                                                 0x3 = (Maskable) Interrupt + NMI + soft reset. */
#else /* Word 0 - Little Endian */
        uint32_t mode                  : 2;  /**< [  1:  0](R/W) Watchdog mode:
                                                                 0x0 = Off.
                                                                 0x1 = (Maskable) Interrupt only.
                                                                 0x2 = (Maskable) Interrupt + NMI.
                                                                 0x3 = (Maskable) Interrupt + NMI + soft reset. */
        uint32_t state                 : 2;  /**< [  3:  2](R/W/H) Watchdog state. The number of watchdog time expirations since last core poke. Cleared on
                                                                 write to associated XCP()_CWD_POKE. */
        uint32_t len                   : 9;  /**< [ 12:  4](R/W) Watchdog time-expiration length. The most-significant nine bits of a 17-bit value to be
                                                                 decremented every 10,240 us. */
        uint32_t cnt                   : 17; /**< [ 29: 13](R/W/H) Number of 10,240 us intervals until next watchdog expiration. Set on write to
                                                                 associated XCP()_CWD_POKE.

                                                                 Typically on each write to XCP()_CWD_WDOG, [CNT] should be set to [LEN] * 0x100. */
        uint32_t dstop                 : 1;  /**< [ 30: 30](R/W) Debug-stop enable. */
        uint32_t gstop                 : 1;  /**< [ 31: 31](R/W) Global-stop enable. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_cwd_wdog_s cn; */
};
typedef union bdk_xcpx_cwd_wdog bdk_xcpx_cwd_wdog_t;

static inline uint64_t BDK_XCPX_CWD_WDOG(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_CWD_WDOG(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c00000ee80ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_CWD_WDOG", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_CWD_WDOG(a) bdk_xcpx_cwd_wdog_t
#define bustype_BDK_XCPX_CWD_WDOG(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_CWD_WDOG(a) "XCPX_CWD_WDOG"
#define device_bar_BDK_XCPX_CWD_WDOG(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_CWD_WDOG(a) (a)
#define arguments_BDK_XCPX_CWD_WDOG(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_dev#_xcp_mbox
 *
 * XCP DEV-to-XCP Mailbox Data Registers
 * This register is the mailbox register for other devices to interrupt XCP
 * See XCP_MBOX_DEV_E for device enumeration.
 *
 * This register is only accessible to device driving this mailbox reg and the requestor(s)
 * permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_devx_xcp_mbox
{
    uint32_t u;
    struct bdk_xcpx_devx_xcp_mbox_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) Communication data from devices to XCP. When written sets XCP()_DEV()_XCP_MBOX_LINT[INTR]. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) Communication data from devices to XCP. When written sets XCP()_DEV()_XCP_MBOX_LINT[INTR]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_devx_xcp_mbox_s cn; */
};
typedef union bdk_xcpx_devx_xcp_mbox bdk_xcpx_devx_xcp_mbox_t;

static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=7)))
        return 0x82c0000e1000ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x7);
    __bdk_csr_fatal("XCPX_DEVX_XCP_MBOX", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_DEVX_XCP_MBOX(a,b) bdk_xcpx_devx_xcp_mbox_t
#define bustype_BDK_XCPX_DEVX_XCP_MBOX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_DEVX_XCP_MBOX(a,b) "XCPX_DEVX_XCP_MBOX"
#define device_bar_BDK_XCPX_DEVX_XCP_MBOX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_DEVX_XCP_MBOX(a,b) (a)
#define arguments_BDK_XCPX_DEVX_XCP_MBOX(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_dev#_xcp_mbox_lint
 *
 * XCP DEV-to-XCP Mailbox Interrupt Register
 * This register contains mailbox interrupt for Devs to XCP core transactions.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_devx_xcp_mbox_lint
{
    uint32_t u;
    struct bdk_xcpx_devx_xcp_mbox_lint_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t intr                  : 1;  /**< [  0:  0](R/W1C/H) Mailbox interrupt. Set when XCP()_DEV()_XCP_MBOX is written. */
#else /* Word 0 - Little Endian */
        uint32_t intr                  : 1;  /**< [  0:  0](R/W1C/H) Mailbox interrupt. Set when XCP()_DEV()_XCP_MBOX is written. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_devx_xcp_mbox_lint_s cn; */
};
typedef union bdk_xcpx_devx_xcp_mbox_lint bdk_xcpx_devx_xcp_mbox_lint_t;

static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX_LINT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX_LINT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=7)))
        return 0x82c0000e1c00ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x7);
    __bdk_csr_fatal("XCPX_DEVX_XCP_MBOX_LINT", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_DEVX_XCP_MBOX_LINT(a,b) bdk_xcpx_devx_xcp_mbox_lint_t
#define bustype_BDK_XCPX_DEVX_XCP_MBOX_LINT(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_DEVX_XCP_MBOX_LINT(a,b) "XCPX_DEVX_XCP_MBOX_LINT"
#define device_bar_BDK_XCPX_DEVX_XCP_MBOX_LINT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_DEVX_XCP_MBOX_LINT(a,b) (a)
#define arguments_BDK_XCPX_DEVX_XCP_MBOX_LINT(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_dev#_xcp_mbox_lint_ena_w1c
 *
 * XCP DEV-to-XCP Mailbox Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_xcpx_devx_xcp_mbox_lint_ena_w1c
{
    uint32_t u;
    struct bdk_xcpx_devx_xcp_mbox_lint_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t intr                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_DEV(0..7)_XCP_MBOX_LINT[INTR]. */
#else /* Word 0 - Little Endian */
        uint32_t intr                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_DEV(0..7)_XCP_MBOX_LINT[INTR]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_devx_xcp_mbox_lint_ena_w1c_s cn; */
};
typedef union bdk_xcpx_devx_xcp_mbox_lint_ena_w1c bdk_xcpx_devx_xcp_mbox_lint_ena_w1c_t;

static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=7)))
        return 0x82c0000e1d80ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x7);
    __bdk_csr_fatal("XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C(a,b) bdk_xcpx_devx_xcp_mbox_lint_ena_w1c_t
#define bustype_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C(a,b) "XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C"
#define device_bar_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C(a,b) (a)
#define arguments_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_dev#_xcp_mbox_lint_ena_w1s
 *
 * XCP DEV-to-XCP Mailbox Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_xcpx_devx_xcp_mbox_lint_ena_w1s
{
    uint32_t u;
    struct bdk_xcpx_devx_xcp_mbox_lint_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t intr                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_DEV(0..7)_XCP_MBOX_LINT[INTR]. */
#else /* Word 0 - Little Endian */
        uint32_t intr                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_DEV(0..7)_XCP_MBOX_LINT[INTR]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_devx_xcp_mbox_lint_ena_w1s_s cn; */
};
typedef union bdk_xcpx_devx_xcp_mbox_lint_ena_w1s bdk_xcpx_devx_xcp_mbox_lint_ena_w1s_t;

static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=7)))
        return 0x82c0000e1c80ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x7);
    __bdk_csr_fatal("XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S(a,b) bdk_xcpx_devx_xcp_mbox_lint_ena_w1s_t
#define bustype_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S(a,b) "XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S"
#define device_bar_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S(a,b) (a)
#define arguments_BDK_XCPX_DEVX_XCP_MBOX_LINT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_dev#_xcp_mbox_lint_w1s
 *
 * XCP AP-to-XCP Mailbox Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_xcpx_devx_xcp_mbox_lint_w1s
{
    uint32_t u;
    struct bdk_xcpx_devx_xcp_mbox_lint_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t intr                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_DEV(0..7)_XCP_MBOX_LINT[INTR]. */
#else /* Word 0 - Little Endian */
        uint32_t intr                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_DEV(0..7)_XCP_MBOX_LINT[INTR]. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_devx_xcp_mbox_lint_w1s_s cn; */
};
typedef union bdk_xcpx_devx_xcp_mbox_lint_w1s bdk_xcpx_devx_xcp_mbox_lint_w1s_t;

static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX_LINT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_DEVX_XCP_MBOX_LINT_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=7)))
        return 0x82c0000e1d00ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x7);
    __bdk_csr_fatal("XCPX_DEVX_XCP_MBOX_LINT_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_DEVX_XCP_MBOX_LINT_W1S(a,b) bdk_xcpx_devx_xcp_mbox_lint_w1s_t
#define bustype_BDK_XCPX_DEVX_XCP_MBOX_LINT_W1S(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_DEVX_XCP_MBOX_LINT_W1S(a,b) "XCPX_DEVX_XCP_MBOX_LINT_W1S"
#define device_bar_BDK_XCPX_DEVX_XCP_MBOX_LINT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_DEVX_XCP_MBOX_LINT_W1S(a,b) (a)
#define arguments_BDK_XCPX_DEVX_XCP_MBOX_LINT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_eco
 *
 * INTERNAL: XCP ECO Register
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_eco
{
    uint32_t u;
    struct bdk_xcpx_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint32_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_eco_s cn; */
};
typedef union bdk_xcpx_eco bdk_xcpx_eco_t;

static inline uint64_t BDK_XCPX_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_ECO(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000100ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_ECO", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_ECO(a) bdk_xcpx_eco_t
#define bustype_BDK_XCPX_ECO(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_ECO(a) "XCPX_ECO"
#define device_bar_BDK_XCPX_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_ECO(a) (a)
#define arguments_BDK_XCPX_ECO(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_gib#_lint
 *
 * XCP GIB Interrupt Register
 * This register contains GIB interrupt for XCP.
 *
 * This register and XCP()_GIB()_LINT_W1S are only accessible to the requestor(s)
 * permitted with CPC_XCP()_PERMIT, or by a MSI-X/GIB interrupt message write.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_gibx_lint
{
    uint32_t u;
    struct bdk_xcpx_gibx_lint_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t gib_int               : 32; /**< [ 31:  0](R/W1C/H) MSI-X interrupt bits. Devices may program their MSI-X vector addresses to this
                                                                 physical address, and MSI-X vector data to have a single bit set in \<31:0\>. This
                                                                 will allow that device to set one of these bits, causing an interrupt to be
                                                                 signalled to the XCP (if appropriately enabled with XCP()_GIB()_LINT_ENA_W1C). */
#else /* Word 0 - Little Endian */
        uint32_t gib_int               : 32; /**< [ 31:  0](R/W1C/H) MSI-X interrupt bits. Devices may program their MSI-X vector addresses to this
                                                                 physical address, and MSI-X vector data to have a single bit set in \<31:0\>. This
                                                                 will allow that device to set one of these bits, causing an interrupt to be
                                                                 signalled to the XCP (if appropriately enabled with XCP()_GIB()_LINT_ENA_W1C). */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_gibx_lint_s cn; */
};
typedef union bdk_xcpx_gibx_lint bdk_xcpx_gibx_lint_t;

static inline uint64_t BDK_XCPX_GIBX_LINT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_GIBX_LINT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=2)))
        return 0x82c000000c00ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_GIBX_LINT", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_GIBX_LINT(a,b) bdk_xcpx_gibx_lint_t
#define bustype_BDK_XCPX_GIBX_LINT(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_GIBX_LINT(a,b) "XCPX_GIBX_LINT"
#define device_bar_BDK_XCPX_GIBX_LINT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_GIBX_LINT(a,b) (a)
#define arguments_BDK_XCPX_GIBX_LINT(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_gib#_lint_devid
 *
 * XCP GIB Interrupt Device ID Register
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_gibx_lint_devid
{
    uint32_t u;
    struct bdk_xcpx_gibx_lint_devid_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t valid                 : 1;  /**< [ 31: 31](R/W1C/H) Valid.  When a device sends an interrupt that writes to XCP()_GIB()_LINT_W1S (but not
                                                                 XCP()_GIB()_LINT or other registers), [VALID] is set and if [VALID] was previously clear,
                                                                 the device ID is recorded in [DEVID]. */
        uint32_t ovfl                  : 1;  /**< [ 30: 30](R/W1C/H) Overflow.  If [VALID] was previously set and a device sends a later message to
                                                                 XCP()_GIB()_LINT_W1S, and that message's device ID does not match [DEVID], then [OVFL] is
                                                                 set. This indicates that multiple devices have sent interrupts and software may need to
                                                                 poll multiple devices to determine which originated the interrupt. */
        uint32_t reserved_22_29        : 8;
        uint32_t devid                 : 22; /**< [ 21:  0](RO/H) Device ID.  The interrupt device ID that first wrote to XCP()_GIB()_LINT_W1S and caused
                                                                 [VALID] to become one. Unpredictable unless [VALID] is set. */
#else /* Word 0 - Little Endian */
        uint32_t devid                 : 22; /**< [ 21:  0](RO/H) Device ID.  The interrupt device ID that first wrote to XCP()_GIB()_LINT_W1S and caused
                                                                 [VALID] to become one. Unpredictable unless [VALID] is set. */
        uint32_t reserved_22_29        : 8;
        uint32_t ovfl                  : 1;  /**< [ 30: 30](R/W1C/H) Overflow.  If [VALID] was previously set and a device sends a later message to
                                                                 XCP()_GIB()_LINT_W1S, and that message's device ID does not match [DEVID], then [OVFL] is
                                                                 set. This indicates that multiple devices have sent interrupts and software may need to
                                                                 poll multiple devices to determine which originated the interrupt. */
        uint32_t valid                 : 1;  /**< [ 31: 31](R/W1C/H) Valid.  When a device sends an interrupt that writes to XCP()_GIB()_LINT_W1S (but not
                                                                 XCP()_GIB()_LINT or other registers), [VALID] is set and if [VALID] was previously clear,
                                                                 the device ID is recorded in [DEVID]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_gibx_lint_devid_s cn; */
};
typedef union bdk_xcpx_gibx_lint_devid bdk_xcpx_gibx_lint_devid_t;

static inline uint64_t BDK_XCPX_GIBX_LINT_DEVID(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_GIBX_LINT_DEVID(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=2)))
        return 0x82c000000dc0ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_GIBX_LINT_DEVID", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_GIBX_LINT_DEVID(a,b) bdk_xcpx_gibx_lint_devid_t
#define bustype_BDK_XCPX_GIBX_LINT_DEVID(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_GIBX_LINT_DEVID(a,b) "XCPX_GIBX_LINT_DEVID"
#define device_bar_BDK_XCPX_GIBX_LINT_DEVID(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_GIBX_LINT_DEVID(a,b) (a)
#define arguments_BDK_XCPX_GIBX_LINT_DEVID(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_gib#_lint_ena_w1c
 *
 * XCP GIB Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_xcpx_gibx_lint_ena_w1c
{
    uint32_t u;
    struct bdk_xcpx_gibx_lint_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t gib_int               : 32; /**< [ 31:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_GIB(0..2)_LINT[GIB_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t gib_int               : 32; /**< [ 31:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_GIB(0..2)_LINT[GIB_INT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_gibx_lint_ena_w1c_s cn; */
};
typedef union bdk_xcpx_gibx_lint_ena_w1c bdk_xcpx_gibx_lint_ena_w1c_t;

static inline uint64_t BDK_XCPX_GIBX_LINT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_GIBX_LINT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=2)))
        return 0x82c000000cc0ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_GIBX_LINT_ENA_W1C", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_GIBX_LINT_ENA_W1C(a,b) bdk_xcpx_gibx_lint_ena_w1c_t
#define bustype_BDK_XCPX_GIBX_LINT_ENA_W1C(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_GIBX_LINT_ENA_W1C(a,b) "XCPX_GIBX_LINT_ENA_W1C"
#define device_bar_BDK_XCPX_GIBX_LINT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_GIBX_LINT_ENA_W1C(a,b) (a)
#define arguments_BDK_XCPX_GIBX_LINT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_gib#_lint_ena_w1s
 *
 * XCP GIB Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_xcpx_gibx_lint_ena_w1s
{
    uint32_t u;
    struct bdk_xcpx_gibx_lint_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t gib_int               : 32; /**< [ 31:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_GIB(0..2)_LINT[GIB_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t gib_int               : 32; /**< [ 31:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_GIB(0..2)_LINT[GIB_INT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_gibx_lint_ena_w1s_s cn; */
};
typedef union bdk_xcpx_gibx_lint_ena_w1s bdk_xcpx_gibx_lint_ena_w1s_t;

static inline uint64_t BDK_XCPX_GIBX_LINT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_GIBX_LINT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=2)))
        return 0x82c000000c40ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_GIBX_LINT_ENA_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_GIBX_LINT_ENA_W1S(a,b) bdk_xcpx_gibx_lint_ena_w1s_t
#define bustype_BDK_XCPX_GIBX_LINT_ENA_W1S(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_GIBX_LINT_ENA_W1S(a,b) "XCPX_GIBX_LINT_ENA_W1S"
#define device_bar_BDK_XCPX_GIBX_LINT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_GIBX_LINT_ENA_W1S(a,b) (a)
#define arguments_BDK_XCPX_GIBX_LINT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_gib#_lint_w1s
 *
 * XCP GIB Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_xcpx_gibx_lint_w1s
{
    uint32_t u;
    struct bdk_xcpx_gibx_lint_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t gib_int               : 32; /**< [ 31:  0](R/W1S/H) Reads or sets XCP(0..1)_GIB(0..2)_LINT[GIB_INT]. */
#else /* Word 0 - Little Endian */
        uint32_t gib_int               : 32; /**< [ 31:  0](R/W1S/H) Reads or sets XCP(0..1)_GIB(0..2)_LINT[GIB_INT]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_gibx_lint_w1s_s cn; */
};
typedef union bdk_xcpx_gibx_lint_w1s bdk_xcpx_gibx_lint_w1s_t;

static inline uint64_t BDK_XCPX_GIBX_LINT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_GIBX_LINT_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=2)))
        return 0x82c000000c80ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_GIBX_LINT_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_GIBX_LINT_W1S(a,b) bdk_xcpx_gibx_lint_w1s_t
#define bustype_BDK_XCPX_GIBX_LINT_W1S(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_GIBX_LINT_W1S(a,b) "XCPX_GIBX_LINT_W1S"
#define device_bar_BDK_XCPX_GIBX_LINT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_GIBX_LINT_W1S(a,b) (a)
#define arguments_BDK_XCPX_GIBX_LINT_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_lint_summary
 *
 * XCP Interrupt Summary Registers
 * This register is the local interrupt summary register for the MIPS core.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_lint_summary
{
    uint32_t u;
    struct bdk_xcpx_lint_summary_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_20_31        : 12;
        uint32_t wdog_nmi              : 1;  /**< [ 19: 19](RO/H) WDOG non-maskable interrupt, XCP()_CWD_NM_LINT[WDOG_INT]. */
        uint32_t wdog_mi               : 1;  /**< [ 18: 18](RO/H) WDOG maskable interrupt, XCP()_CWD_LINT[WDOG_INT]. */
        uint32_t reserved_16_17        : 2;
        uint32_t bus_err               : 1;  /**< [ 15: 15](RO/H) Logical OR of bus error interrupt bits, XCP()_BUS_ERR_LINT. */
        uint32_t wakeup                : 1;  /**< [ 14: 14](RO/H) PSBM wakeup interrupt (SCP only, otherwise reserved). */
        uint32_t reserved_13           : 1;
        uint32_t mbox                  : 8;  /**< [ 12:  5](RO/H) Mailbox interrupt bits, XCP()_DEV()_XCP_MBOX_LINT[INTR]. */
        uint32_t reserved_3_4          : 2;
        uint32_t gib                   : 3;  /**< [  2:  0](RO/H) Logical OR of each set of 32 GIB interrupt bits XCP()_GIB()_LINT\<31:0\>. */
#else /* Word 0 - Little Endian */
        uint32_t gib                   : 3;  /**< [  2:  0](RO/H) Logical OR of each set of 32 GIB interrupt bits XCP()_GIB()_LINT\<31:0\>. */
        uint32_t reserved_3_4          : 2;
        uint32_t mbox                  : 8;  /**< [ 12:  5](RO/H) Mailbox interrupt bits, XCP()_DEV()_XCP_MBOX_LINT[INTR]. */
        uint32_t reserved_13           : 1;
        uint32_t wakeup                : 1;  /**< [ 14: 14](RO/H) PSBM wakeup interrupt (SCP only, otherwise reserved). */
        uint32_t bus_err               : 1;  /**< [ 15: 15](RO/H) Logical OR of bus error interrupt bits, XCP()_BUS_ERR_LINT. */
        uint32_t reserved_16_17        : 2;
        uint32_t wdog_mi               : 1;  /**< [ 18: 18](RO/H) WDOG maskable interrupt, XCP()_CWD_LINT[WDOG_INT]. */
        uint32_t wdog_nmi              : 1;  /**< [ 19: 19](RO/H) WDOG non-maskable interrupt, XCP()_CWD_NM_LINT[WDOG_INT]. */
        uint32_t reserved_20_31        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_lint_summary_s cn; */
};
typedef union bdk_xcpx_lint_summary bdk_xcpx_lint_summary_t;

static inline uint64_t BDK_XCPX_LINT_SUMMARY(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_LINT_SUMMARY(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c0000e0000ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_LINT_SUMMARY", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_LINT_SUMMARY(a) bdk_xcpx_lint_summary_t
#define bustype_BDK_XCPX_LINT_SUMMARY(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_LINT_SUMMARY(a) "XCPX_LINT_SUMMARY"
#define device_bar_BDK_XCPX_LINT_SUMMARY(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_LINT_SUMMARY(a) (a)
#define arguments_BDK_XCPX_LINT_SUMMARY(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_mrml_64rd
 *
 * XCP MRML 64-bit Read Save/Restore Register
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on xcp_reset
 */
union bdk_xcpx_mrml_64rd
{
    uint32_t u;
    struct bdk_xcpx_mrml_64rd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t rd_data               : 32; /**< [ 31:  0](R/W) On a read, will return the saved upper 32-bits for the last 64-bit MRML read request.
                                                                 Writing this register will overwrite the value used by the MRML on a read to the upper
                                                                 32-bits in a 64-bit MRML window. Used to save/restore this value. */
#else /* Word 0 - Little Endian */
        uint32_t rd_data               : 32; /**< [ 31:  0](R/W) On a read, will return the saved upper 32-bits for the last 64-bit MRML read request.
                                                                 Writing this register will overwrite the value used by the MRML on a read to the upper
                                                                 32-bits in a 64-bit MRML window. Used to save/restore this value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_mrml_64rd_s cn; */
};
typedef union bdk_xcpx_mrml_64rd bdk_xcpx_mrml_64rd_t;

static inline uint64_t BDK_XCPX_MRML_64RD(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_MRML_64RD(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000110ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_MRML_64RD", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_MRML_64RD(a) bdk_xcpx_mrml_64rd_t
#define bustype_BDK_XCPX_MRML_64RD(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_MRML_64RD(a) "XCPX_MRML_64RD"
#define device_bar_BDK_XCPX_MRML_64RD(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_MRML_64RD(a) (a)
#define arguments_BDK_XCPX_MRML_64RD(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_mrml_64wr
 *
 * XCP MRML 64-bit Write Save/Restore Register
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_mrml_64wr
{
    uint32_t u;
    struct bdk_xcpx_mrml_64wr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t wr_data               : 32; /**< [ 31:  0](R/W) On a read, will return the saved value of lower 32-bits of a 64-bit write to be used by
                                                                 the MRML. Writing this register will overwrite the value used by the MRML. Used to
                                                                 save/restore this value. */
#else /* Word 0 - Little Endian */
        uint32_t wr_data               : 32; /**< [ 31:  0](R/W) On a read, will return the saved value of lower 32-bits of a 64-bit write to be used by
                                                                 the MRML. Writing this register will overwrite the value used by the MRML. Used to
                                                                 save/restore this value. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_mrml_64wr_s cn; */
};
typedef union bdk_xcpx_mrml_64wr bdk_xcpx_mrml_64wr_t;

static inline uint64_t BDK_XCPX_MRML_64WR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_MRML_64WR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000120ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_MRML_64WR", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_MRML_64WR(a) bdk_xcpx_mrml_64wr_t
#define bustype_BDK_XCPX_MRML_64WR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_MRML_64WR(a) "XCPX_MRML_64WR"
#define device_bar_BDK_XCPX_MRML_64WR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_MRML_64WR(a) (a)
#define arguments_BDK_XCPX_MRML_64WR(a) (a),-1,-1,-1

/**
 * Register (NCB) xcp#_msix_pba#
 *
 * XCP MSI-X Pending Bit Array Registers
 * This register is the MSI-X PBA table; the bit number is indexed by the XCP_INT_VEC_E enumeration.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_msix_pbax
{
    uint64_t u;
    struct bdk_xcpx_msix_pbax_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated XCP()_MSIX_VEC()_CTL, enumerated by XCP_INT_VEC_E. Bits
                                                                 that have no associated XCP_INT_VEC_E are 0. */
#else /* Word 0 - Little Endian */
        uint64_t pend                  : 64; /**< [ 63:  0](RO/H) Pending message for the associated XCP()_MSIX_VEC()_CTL, enumerated by XCP_INT_VEC_E. Bits
                                                                 that have no associated XCP_INT_VEC_E are 0. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_msix_pbax_s cn; */
};
typedef union bdk_xcpx_msix_pbax bdk_xcpx_msix_pbax_t;

static inline uint64_t BDK_XCPX_MSIX_PBAX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_MSIX_PBAX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b==0)))
        return 0x82c0001f0000ll + 0x1000000000ll * ((a) & 0x1) + 8ll * ((b) & 0x0);
    __bdk_csr_fatal("XCPX_MSIX_PBAX", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_MSIX_PBAX(a,b) bdk_xcpx_msix_pbax_t
#define bustype_BDK_XCPX_MSIX_PBAX(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_XCPX_MSIX_PBAX(a,b) "XCPX_MSIX_PBAX"
#define device_bar_BDK_XCPX_MSIX_PBAX(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_XCPX_MSIX_PBAX(a,b) (a)
#define arguments_BDK_XCPX_MSIX_PBAX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) xcp#_msix_vec#_addr
 *
 * XCP MSI-X Vector-Table Address Register
 * This register is the MSI-X vector table, indexed by the XCP_INT_VEC_E enumeration.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_msix_vecx_addr
{
    uint64_t u;
    struct bdk_xcpx_msix_vecx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_1            : 1;
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's XCP()_MSIX_VEC()_ADDR, XCP()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of XCP()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_XCP_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
#else /* Word 0 - Little Endian */
        uint64_t secvec                : 1;  /**< [  0:  0](SR/W) Secure vector.
                                                                 0 = This vector may be read or written by either secure or nonsecure states.
                                                                 1 = This vector's XCP()_MSIX_VEC()_ADDR, XCP()_MSIX_VEC()_CTL, and corresponding
                                                                 bit of XCP()_MSIX_PBA() are RAZ/WI and does not cause a fault when accessed
                                                                 by the nonsecure world.

                                                                 If PCCPF_XCP_VSEC_SCTL[MSIX_SEC] (for documentation, see PCCPF_XXX_VSEC_SCTL[MSIX_SEC]) is
                                                                 set, all vectors are secure and function as if [SECVEC] was set. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](R/W) IOVA to use for MSI-X delivery of this vector. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_msix_vecx_addr_s cn; */
};
typedef union bdk_xcpx_msix_vecx_addr bdk_xcpx_msix_vecx_addr_t;

static inline uint64_t BDK_XCPX_MSIX_VECX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_MSIX_VECX_ADDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c000100000ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_MSIX_VECX_ADDR", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_MSIX_VECX_ADDR(a,b) bdk_xcpx_msix_vecx_addr_t
#define bustype_BDK_XCPX_MSIX_VECX_ADDR(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_XCPX_MSIX_VECX_ADDR(a,b) "XCPX_MSIX_VECX_ADDR"
#define device_bar_BDK_XCPX_MSIX_VECX_ADDR(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_XCPX_MSIX_VECX_ADDR(a,b) (a)
#define arguments_BDK_XCPX_MSIX_VECX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB) xcp#_msix_vec#_ctl
 *
 * XCP MSI-X Vector-Table Control and Data Register
 * This register is the MSI-X vector table, indexed by the XCP_INT_VEC_E enumeration
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_msix_vecx_ctl
{
    uint64_t u;
    struct bdk_xcpx_msix_vecx_ctl_s
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
    /* struct bdk_xcpx_msix_vecx_ctl_s cn; */
};
typedef union bdk_xcpx_msix_vecx_ctl bdk_xcpx_msix_vecx_ctl_t;

static inline uint64_t BDK_XCPX_MSIX_VECX_CTL(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_MSIX_VECX_CTL(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c000100008ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_MSIX_VECX_CTL", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_MSIX_VECX_CTL(a,b) bdk_xcpx_msix_vecx_ctl_t
#define bustype_BDK_XCPX_MSIX_VECX_CTL(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_XCPX_MSIX_VECX_CTL(a,b) "XCPX_MSIX_VECX_CTL"
#define device_bar_BDK_XCPX_MSIX_VECX_CTL(a,b) 0x4 /* PF_BAR4 */
#define busnum_BDK_XCPX_MSIX_VECX_CTL(a,b) (a)
#define arguments_BDK_XCPX_MSIX_VECX_CTL(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_ncb_timeout
 *
 * XCP NCB Timeout Count Configuration Register
 * This register configures the NCB timeout counters.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_ncb_timeout
{
    uint32_t u;
    struct bdk_xcpx_ncb_timeout_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t cnt                   : 32; /**< [ 31:  0](R/W) Number of coprocessor-clocks to wait on responses from IOBN. Value of 0x0 disables. */
#else /* Word 0 - Little Endian */
        uint32_t cnt                   : 32; /**< [ 31:  0](R/W) Number of coprocessor-clocks to wait on responses from IOBN. Value of 0x0 disables. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_ncb_timeout_s cn; */
};
typedef union bdk_xcpx_ncb_timeout bdk_xcpx_ncb_timeout_t;

static inline uint64_t BDK_XCPX_NCB_TIMEOUT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_NCB_TIMEOUT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000220ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_NCB_TIMEOUT", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_NCB_TIMEOUT(a) bdk_xcpx_ncb_timeout_t
#define bustype_BDK_XCPX_NCB_TIMEOUT(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_NCB_TIMEOUT(a) "XCPX_NCB_TIMEOUT"
#define device_bar_BDK_XCPX_NCB_TIMEOUT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_NCB_TIMEOUT(a) (a)
#define arguments_BDK_XCPX_NCB_TIMEOUT(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_precise_bus_err_addr
 *
 * XCP Precise Bus Error Address Register
 * This register contains the address of the precise data bus interface error for XCP.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_precise_bus_err_addr
{
    uint32_t u;
    struct bdk_xcpx_precise_bus_err_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t addr                  : 32; /**< [ 31:  0](RO/H) Precise bus error address. Unpredictable unless XCP()_PRECISE_BUS_ERR_STATUS[VAL] is set. */
#else /* Word 0 - Little Endian */
        uint32_t addr                  : 32; /**< [ 31:  0](RO/H) Precise bus error address. Unpredictable unless XCP()_PRECISE_BUS_ERR_STATUS[VAL] is set. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_precise_bus_err_addr_s cn; */
};
typedef union bdk_xcpx_precise_bus_err_addr bdk_xcpx_precise_bus_err_addr_t;

static inline uint64_t BDK_XCPX_PRECISE_BUS_ERR_ADDR(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_PRECISE_BUS_ERR_ADDR(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000001d00ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_PRECISE_BUS_ERR_ADDR", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_PRECISE_BUS_ERR_ADDR(a) bdk_xcpx_precise_bus_err_addr_t
#define bustype_BDK_XCPX_PRECISE_BUS_ERR_ADDR(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_PRECISE_BUS_ERR_ADDR(a) "XCPX_PRECISE_BUS_ERR_ADDR"
#define device_bar_BDK_XCPX_PRECISE_BUS_ERR_ADDR(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_PRECISE_BUS_ERR_ADDR(a) (a)
#define arguments_BDK_XCPX_PRECISE_BUS_ERR_ADDR(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_precise_bus_err_status
 *
 * XCP Precise Bus Error Status Register
 * This register contains the state of the precise data bus interface error for XCP.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_precise_bus_err_status
{
    uint32_t u;
    struct bdk_xcpx_precise_bus_err_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_7_31         : 25;
        uint32_t val                   : 1;  /**< [  6:  6](R/W1C/H) Error valid. When set, subsequent bus errors are not recorded un
                                                                 XCP()_PRECISE_BUS_ERR_ADDR and XCP()_PRECISE_BUS_ERR_STATUS. */
        uint32_t err_type              : 3;  /**< [  5:  3](RO/H) Precise bus error type. Enumerated by XCP_DINTF_ERR_TYPE_E. */
        uint32_t part                  : 3;  /**< [  2:  0](RO/H) Partition in which the bus error occured. Enumerated by XCP_ADDR_PRT_E. */
#else /* Word 0 - Little Endian */
        uint32_t part                  : 3;  /**< [  2:  0](RO/H) Partition in which the bus error occured. Enumerated by XCP_ADDR_PRT_E. */
        uint32_t err_type              : 3;  /**< [  5:  3](RO/H) Precise bus error type. Enumerated by XCP_DINTF_ERR_TYPE_E. */
        uint32_t val                   : 1;  /**< [  6:  6](R/W1C/H) Error valid. When set, subsequent bus errors are not recorded un
                                                                 XCP()_PRECISE_BUS_ERR_ADDR and XCP()_PRECISE_BUS_ERR_STATUS. */
        uint32_t reserved_7_31         : 25;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_precise_bus_err_status_s cn; */
};
typedef union bdk_xcpx_precise_bus_err_status bdk_xcpx_precise_bus_err_status_t;

static inline uint64_t BDK_XCPX_PRECISE_BUS_ERR_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_PRECISE_BUS_ERR_STATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000001d08ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_PRECISE_BUS_ERR_STATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_PRECISE_BUS_ERR_STATUS(a) bdk_xcpx_precise_bus_err_status_t
#define bustype_BDK_XCPX_PRECISE_BUS_ERR_STATUS(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_PRECISE_BUS_ERR_STATUS(a) "XCPX_PRECISE_BUS_ERR_STATUS"
#define device_bar_BDK_XCPX_PRECISE_BUS_ERR_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_PRECISE_BUS_ERR_STATUS(a) (a)
#define arguments_BDK_XCPX_PRECISE_BUS_ERR_STATUS(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_seg#_map_reg
 *
 * XCP Segment Mapping Register
 * This register contains the segment mapping from the MIPS core addresses
 * to sections of the CPC RAM.
 * * SEG0 corresponds to kuseg.
 * * SEG1 corresponds to kseg0/kseg1.
 * * SEG2 corresponds to kseg2.
 * * SEG3 corresponds to kseg3.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_segx_map_reg
{
    uint32_t u;
    struct bdk_xcpx_segx_map_reg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_13_31        : 19;
        uint32_t size                  : 7;  /**< [ 12:  6](R/W) Size of segment in number of 16 KB blocks. */
        uint32_t base                  : 6;  /**< [  5:  0](R/W) CPC RAM base address for this segment. */
#else /* Word 0 - Little Endian */
        uint32_t base                  : 6;  /**< [  5:  0](R/W) CPC RAM base address for this segment. */
        uint32_t size                  : 7;  /**< [ 12:  6](R/W) Size of segment in number of 16 KB blocks. */
        uint32_t reserved_13_31        : 19;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_segx_map_reg_s cn; */
};
typedef union bdk_xcpx_segx_map_reg bdk_xcpx_segx_map_reg_t;

static inline uint64_t BDK_XCPX_SEGX_MAP_REG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_SEGX_MAP_REG(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c000000600ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_SEGX_MAP_REG", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_SEGX_MAP_REG(a,b) bdk_xcpx_segx_map_reg_t
#define bustype_BDK_XCPX_SEGX_MAP_REG(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_SEGX_MAP_REG(a,b) "XCPX_SEGX_MAP_REG"
#define device_bar_BDK_XCPX_SEGX_MAP_REG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_SEGX_MAP_REG(a,b) (a)
#define arguments_BDK_XCPX_SEGX_MAP_REG(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_win#_addr
 *
 * XCP Window Address Register
 * This register contains the upper address bits for the XCP core RSL/NCB access windows.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 *
 * The windows should not have overlapping address spaces if caching is enabled.
 */
union bdk_xcpx_winx_addr
{
    uint32_t u;
    struct bdk_xcpx_winx_addr_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_29_31        : 3;
        uint32_t addr                  : 29; /**< [ 28:  0](R/W) IOVA bits 52:24. If XCP()_WIN()_CFG[RSL_NCB_N] = 1 (RSL), only IOVA 47:24 are
                                                                 used (as a physical address). */
#else /* Word 0 - Little Endian */
        uint32_t addr                  : 29; /**< [ 28:  0](R/W) IOVA bits 52:24. If XCP()_WIN()_CFG[RSL_NCB_N] = 1 (RSL), only IOVA 47:24 are
                                                                 used (as a physical address). */
        uint32_t reserved_29_31        : 3;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_winx_addr_s cn; */
};
typedef union bdk_xcpx_winx_addr bdk_xcpx_winx_addr_t;

static inline uint64_t BDK_XCPX_WINX_ADDR(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_WINX_ADDR(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c000000400ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_WINX_ADDR", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_WINX_ADDR(a,b) bdk_xcpx_winx_addr_t
#define bustype_BDK_XCPX_WINX_ADDR(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_WINX_ADDR(a,b) "XCPX_WINX_ADDR"
#define device_bar_BDK_XCPX_WINX_ADDR(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_WINX_ADDR(a,b) (a)
#define arguments_BDK_XCPX_WINX_ADDR(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_win#_cfg
 *
 * XCP Window Configuration Register
 * This register contains the control bits for the XCP core RSL/NCB access windows.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_winx_cfg
{
    uint32_t u;
    struct bdk_xcpx_winx_cfg_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t b64                   : 1;  /**< [  5:  5](R/W) 64-bit window. If [RSL_NCB_N] is set, specifices if the window access size.
                                                                 0 = 32 bit.
                                                                 1 = 64 bit. */
        uint32_t rsl_ncb_n             : 1;  /**< [  4:  4](R/W) RSL or NCB window type.
                                                                 0 = NCB.  Accesses may be cached, based on [CACHEABLE] and XCP()_CFG[ACCUM_DIS].
                                                                 1 = RSL.  Accesses will never be cached. */
        uint32_t secure                : 1;  /**< [  3:  3](R/W) Secure-world transaction.
                                                                 0 = Nonsecure world for RSL or NCB transactions.
                                                                 1 = Secure world for RSL or NCB transactions. */
        uint32_t phys                  : 1;  /**< [  2:  2](R/W) Physical address.
                                                                 0 = Virtual address. NCB IOVAs will be translated by the SMMU.
                                                                 1 = Physical address. NCB IOVAs bypass SMMU translation, and IOVA \<52\> is ignored.

                                                                 Ignored and acts as if set when [RSL_NCB_N] = 1 (RSL). */
        uint32_t reserved_1            : 1;
        uint32_t cacheable             : 1;  /**< [  0:  0](R/W) Cacheable.
                                                                   0 = Not cachable.
                                                                   1 = Cachable.

                                                                 Ignored and acts as if clear when [RSL_NCB_N] = 1 (RSL). */
#else /* Word 0 - Little Endian */
        uint32_t cacheable             : 1;  /**< [  0:  0](R/W) Cacheable.
                                                                   0 = Not cachable.
                                                                   1 = Cachable.

                                                                 Ignored and acts as if clear when [RSL_NCB_N] = 1 (RSL). */
        uint32_t reserved_1            : 1;
        uint32_t phys                  : 1;  /**< [  2:  2](R/W) Physical address.
                                                                 0 = Virtual address. NCB IOVAs will be translated by the SMMU.
                                                                 1 = Physical address. NCB IOVAs bypass SMMU translation, and IOVA \<52\> is ignored.

                                                                 Ignored and acts as if set when [RSL_NCB_N] = 1 (RSL). */
        uint32_t secure                : 1;  /**< [  3:  3](R/W) Secure-world transaction.
                                                                 0 = Nonsecure world for RSL or NCB transactions.
                                                                 1 = Secure world for RSL or NCB transactions. */
        uint32_t rsl_ncb_n             : 1;  /**< [  4:  4](R/W) RSL or NCB window type.
                                                                 0 = NCB.  Accesses may be cached, based on [CACHEABLE] and XCP()_CFG[ACCUM_DIS].
                                                                 1 = RSL.  Accesses will never be cached. */
        uint32_t b64                   : 1;  /**< [  5:  5](R/W) 64-bit window. If [RSL_NCB_N] is set, specifices if the window access size.
                                                                 0 = 32 bit.
                                                                 1 = 64 bit. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_winx_cfg_s cn; */
};
typedef union bdk_xcpx_winx_cfg bdk_xcpx_winx_cfg_t;

static inline uint64_t BDK_XCPX_WINX_CFG(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_WINX_CFG(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c000000300ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_WINX_CFG", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_WINX_CFG(a,b) bdk_xcpx_winx_cfg_t
#define bustype_BDK_XCPX_WINX_CFG(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_WINX_CFG(a,b) "XCPX_WINX_CFG"
#define device_bar_BDK_XCPX_WINX_CFG(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_WINX_CFG(a,b) (a)
#define arguments_BDK_XCPX_WINX_CFG(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_win#_inv
 *
 * XCP Window Invalidate Register
 * This register contains the invalidate bits for the RSL/NCB window 0-3 for the MIPS core to
 * read/write from/to to reach Thunder memory.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_winx_inv
{
    uint32_t u;
    struct bdk_xcpx_winx_inv_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t invalidate            : 1;  /**< [  0:  0](WO/H) Writing a one will invalidate this window's read cache and flush the write cache. */
#else /* Word 0 - Little Endian */
        uint32_t invalidate            : 1;  /**< [  0:  0](WO/H) Writing a one will invalidate this window's read cache and flush the write cache. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_winx_inv_s cn; */
};
typedef union bdk_xcpx_winx_inv bdk_xcpx_winx_inv_t;

static inline uint64_t BDK_XCPX_WINX_INV(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_WINX_INV(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c000000500ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_WINX_INV", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_WINX_INV(a,b) bdk_xcpx_winx_inv_t
#define bustype_BDK_XCPX_WINX_INV(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_WINX_INV(a,b) "XCPX_WINX_INV"
#define device_bar_BDK_XCPX_WINX_INV(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_WINX_INV(a,b) (a)
#define arguments_BDK_XCPX_WINX_INV(a,b) (a),(b),-1,-1

/**
 * Register (NCB32b) xcp#_wr_accum_flsh_cnt
 *
 * XCP Write Accumulator Flush Count Configuration Register
 * This register configures the write accumulator.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_wr_accum_flsh_cnt
{
    uint32_t u;
    struct bdk_xcpx_wr_accum_flsh_cnt_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t cnt                   : 24; /**< [ 23:  0](R/W) Number of coprocessor-clocks to wait before emptying the write accumulator. */
#else /* Word 0 - Little Endian */
        uint32_t cnt                   : 24; /**< [ 23:  0](R/W) Number of coprocessor-clocks to wait before emptying the write accumulator. */
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_wr_accum_flsh_cnt_s cn; */
};
typedef union bdk_xcpx_wr_accum_flsh_cnt bdk_xcpx_wr_accum_flsh_cnt_t;

static inline uint64_t BDK_XCPX_WR_ACCUM_FLSH_CNT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_WR_ACCUM_FLSH_CNT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x82c000000210ll + 0x1000000000ll * ((a) & 0x1);
    __bdk_csr_fatal("XCPX_WR_ACCUM_FLSH_CNT", 1, a, 0, 0, 0);
}

#define typedef_BDK_XCPX_WR_ACCUM_FLSH_CNT(a) bdk_xcpx_wr_accum_flsh_cnt_t
#define bustype_BDK_XCPX_WR_ACCUM_FLSH_CNT(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_WR_ACCUM_FLSH_CNT(a) "XCPX_WR_ACCUM_FLSH_CNT"
#define device_bar_BDK_XCPX_WR_ACCUM_FLSH_CNT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_WR_ACCUM_FLSH_CNT(a) (a)
#define arguments_BDK_XCPX_WR_ACCUM_FLSH_CNT(a) (a),-1,-1,-1

/**
 * Register (NCB32b) xcp#_xcp_dev#_mbox
 *
 * XCP XCP-to-AP Mailbox Data Registers
 * This register is the mailbox register for XCP-to-AP core transactions.
 *
 * This register is only accessible to device driving this mailbox and the requestor(s) permitted
 * with CPC_XCP()_PERMIT.
 */
union bdk_xcpx_xcp_devx_mbox
{
    uint32_t u;
    struct bdk_xcpx_xcp_devx_mbox_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) Communication data from AP to XCP. When written sets XCP()_XCP_DEV()_MBOX_RINT[INTR]. */
#else /* Word 0 - Little Endian */
        uint32_t data                  : 32; /**< [ 31:  0](R/W) Communication data from AP to XCP. When written sets XCP()_XCP_DEV()_MBOX_RINT[INTR]. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_xcp_devx_mbox_s cn; */
};
typedef union bdk_xcpx_xcp_devx_mbox bdk_xcpx_xcp_devx_mbox_t;

static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c0000d1000ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_XCP_DEVX_MBOX", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_XCP_DEVX_MBOX(a,b) bdk_xcpx_xcp_devx_mbox_t
#define bustype_BDK_XCPX_XCP_DEVX_MBOX(a,b) BDK_CSR_TYPE_NCB32b
#define basename_BDK_XCPX_XCP_DEVX_MBOX(a,b) "XCPX_XCP_DEVX_MBOX"
#define device_bar_BDK_XCPX_XCP_DEVX_MBOX(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_XCP_DEVX_MBOX(a,b) (a)
#define arguments_BDK_XCPX_XCP_DEVX_MBOX(a,b) (a),(b),-1,-1

/**
 * Register (NCB) xcp#_xcp_dev#_mbox_rint
 *
 * XCP XCP-to-AP Mailbox Interrupt Register
 * This register contains mailbox interrupt for XCP-to-AP core transactions.
 *
 * This register is only accessible to device driving this mailbox and the requestor(s) permitted
 * with CPC_XCP()_PERMIT.
 *
 * This register is reset on XCP domain reset.
 */
union bdk_xcpx_xcp_devx_mbox_rint
{
    uint64_t u;
    struct bdk_xcpx_xcp_devx_mbox_rint_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t intr                  : 1;  /**< [  0:  0](R/W1C/H) Mailbox interrupt. Set when XCP()_XCP_DEV()_MBOX is written. */
#else /* Word 0 - Little Endian */
        uint64_t intr                  : 1;  /**< [  0:  0](R/W1C/H) Mailbox interrupt. Set when XCP()_XCP_DEV()_MBOX is written. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_xcp_devx_mbox_rint_s cn; */
};
typedef union bdk_xcpx_xcp_devx_mbox_rint bdk_xcpx_xcp_devx_mbox_rint_t;

static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX_RINT(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX_RINT(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c0000d1c00ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_XCP_DEVX_MBOX_RINT", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_XCP_DEVX_MBOX_RINT(a,b) bdk_xcpx_xcp_devx_mbox_rint_t
#define bustype_BDK_XCPX_XCP_DEVX_MBOX_RINT(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_XCPX_XCP_DEVX_MBOX_RINT(a,b) "XCPX_XCP_DEVX_MBOX_RINT"
#define device_bar_BDK_XCPX_XCP_DEVX_MBOX_RINT(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_XCP_DEVX_MBOX_RINT(a,b) (a)
#define arguments_BDK_XCPX_XCP_DEVX_MBOX_RINT(a,b) (a),(b),-1,-1

/**
 * Register (NCB) xcp#_xcp_dev#_mbox_rint_ena_w1c
 *
 * XCP XCP-to-AP Mailbox Interrupt Enable Clear Register
 * This register clears interrupt enable bits.
 */
union bdk_xcpx_xcp_devx_mbox_rint_ena_w1c
{
    uint64_t u;
    struct bdk_xcpx_xcp_devx_mbox_rint_ena_w1c_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t intr                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_XCP_DEV(0..3)_MBOX_RINT[INTR]. */
#else /* Word 0 - Little Endian */
        uint64_t intr                  : 1;  /**< [  0:  0](R/W1C/H) Reads or clears enable for XCP(0..1)_XCP_DEV(0..3)_MBOX_RINT[INTR]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_xcp_devx_mbox_rint_ena_w1c_s cn; */
};
typedef union bdk_xcpx_xcp_devx_mbox_rint_ena_w1c bdk_xcpx_xcp_devx_mbox_rint_ena_w1c_t;

static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c0000d1cc0ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C(a,b) bdk_xcpx_xcp_devx_mbox_rint_ena_w1c_t
#define bustype_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C(a,b) "XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C"
#define device_bar_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C(a,b) (a)
#define arguments_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1C(a,b) (a),(b),-1,-1

/**
 * Register (NCB) xcp#_xcp_dev#_mbox_rint_ena_w1s
 *
 * XCP XCP-to-AP Mailbox Interrupt Enable Set Register
 * This register sets interrupt enable bits.
 */
union bdk_xcpx_xcp_devx_mbox_rint_ena_w1s
{
    uint64_t u;
    struct bdk_xcpx_xcp_devx_mbox_rint_ena_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t intr                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_XCP_DEV(0..3)_MBOX_RINT[INTR]. */
#else /* Word 0 - Little Endian */
        uint64_t intr                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets enable for XCP(0..1)_XCP_DEV(0..3)_MBOX_RINT[INTR]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_xcp_devx_mbox_rint_ena_w1s_s cn; */
};
typedef union bdk_xcpx_xcp_devx_mbox_rint_ena_w1s bdk_xcpx_xcp_devx_mbox_rint_ena_w1s_t;

static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c0000d1c40ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S(a,b) bdk_xcpx_xcp_devx_mbox_rint_ena_w1s_t
#define bustype_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S(a,b) "XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S"
#define device_bar_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S(a,b) (a)
#define arguments_BDK_XCPX_XCP_DEVX_MBOX_RINT_ENA_W1S(a,b) (a),(b),-1,-1

/**
 * Register (NCB) xcp#_xcp_dev#_mbox_rint_w1s
 *
 * XCP XCP-to-AP Mailbox Interrupt Set Register
 * This register sets interrupt bits.
 */
union bdk_xcpx_xcp_devx_mbox_rint_w1s
{
    uint64_t u;
    struct bdk_xcpx_xcp_devx_mbox_rint_w1s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_1_63         : 63;
        uint64_t intr                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_XCP_DEV(0..3)_MBOX_RINT[INTR]. */
#else /* Word 0 - Little Endian */
        uint64_t intr                  : 1;  /**< [  0:  0](R/W1S/H) Reads or sets XCP(0..1)_XCP_DEV(0..3)_MBOX_RINT[INTR]. */
        uint64_t reserved_1_63         : 63;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_xcpx_xcp_devx_mbox_rint_w1s_s cn; */
};
typedef union bdk_xcpx_xcp_devx_mbox_rint_w1s bdk_xcpx_xcp_devx_mbox_rint_w1s_t;

static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX_RINT_W1S(unsigned long a, unsigned long b) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_XCPX_XCP_DEVX_MBOX_RINT_W1S(unsigned long a, unsigned long b)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && ((a<=1) && (b<=3)))
        return 0x82c0000d1c80ll + 0x1000000000ll * ((a) & 0x1) + 0x10ll * ((b) & 0x3);
    __bdk_csr_fatal("XCPX_XCP_DEVX_MBOX_RINT_W1S", 2, a, b, 0, 0);
}

#define typedef_BDK_XCPX_XCP_DEVX_MBOX_RINT_W1S(a,b) bdk_xcpx_xcp_devx_mbox_rint_w1s_t
#define bustype_BDK_XCPX_XCP_DEVX_MBOX_RINT_W1S(a,b) BDK_CSR_TYPE_NCB
#define basename_BDK_XCPX_XCP_DEVX_MBOX_RINT_W1S(a,b) "XCPX_XCP_DEVX_MBOX_RINT_W1S"
#define device_bar_BDK_XCPX_XCP_DEVX_MBOX_RINT_W1S(a,b) 0x0 /* PF_BAR0 */
#define busnum_BDK_XCPX_XCP_DEVX_MBOX_RINT_W1S(a,b) (a)
#define arguments_BDK_XCPX_XCP_DEVX_MBOX_RINT_W1S(a,b) (a),(b),-1,-1

#endif /* __BDK_CSRS_XCP_H__ */
