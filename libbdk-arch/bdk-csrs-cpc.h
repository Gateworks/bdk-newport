#ifndef __BDK_CSRS_CPC_H__
#define __BDK_CSRS_CPC_H__
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
 * Cavium CPC.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration cpc_bar_e
 *
 * CPC Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_CPC_BAR_E_CPC_PF_BAR0 (0x86d000000000ll)
#define BDK_CPC_BAR_E_CPC_PF_BAR0_SIZE 0x100000ull

/**
 * Enumeration cpc_permit_e
 *
 * CPC Permit Enumeration
 * Enumerates the permissions for CPC access.
 */
#define BDK_CPC_PERMIT_E_MCP_DIS (1)
#define BDK_CPC_PERMIT_E_NSEC_DIS (3)
#define BDK_CPC_PERMIT_E_SCP_DIS (0)
#define BDK_CPC_PERMIT_E_SEC_DIS (2)

/**
 * Enumeration cpc_xcp_map_e
 *
 * CPC XCP Number Mapping Enumeration
 * Enumerates the XCP to MCP or SCP mapping.
 */
#define BDK_CPC_XCP_MAP_E_MCP (1)
#define BDK_CPC_XCP_MAP_E_SCP (0)

/**
 * Structure cpc_bp_test0_bp_cfg_s
 *
 * INTERNAL: CPC Backpressure Test 0 Configuration Structure
 *
 * This structure describes the layout of CPC_BP_TEST0[BP_CFG].
 */
union bdk_cpc_bp_test0_bp_cfg_s
{
    uint32_t u;
    struct bdk_cpc_bp_test0_bp_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t mcp_cr_path_out_data_fifo : 2;/**< [ 31: 30] Config for mcp_cr_path_out_data_fifo. */
        uint32_t mcp_cr_path_outstd_req_fifo : 2;/**< [ 29: 28] Config for mcp_cr_path_outstd_req_fifo. */
        uint32_t scp_cr_path_out_data_fifo : 2;/**< [ 27: 26] Config for scp_cr_path_out_data_fifo. */
        uint32_t scp_cr_path_outstd_req_fifo : 2;/**< [ 25: 24] Config for scp_cr_path_outstd_req_fifo. */
        uint32_t p_path_out_fifo       : 2;  /**< [ 23: 22] Config for p_path_out_fifo. */
        uint32_t scp_p_path_out_data_fifo : 2;/**< [ 21: 20] Config for scp_p_path_out_data_fifo. */
        uint32_t scp_p_path_outstd_req_fifo : 2;/**< [ 19: 18] Config for scp_p_path_outstd_req_fifo. */
        uint32_t mcp_p_path_out_data_fifo : 2;/**< [ 17: 16] Config for mcp_p_path_out_data_fifo. */
        uint32_t mcp_p_path_outstd_req_fifo : 2;/**< [ 15: 14] Config for mcp_p_path_outstd_req_fifo. */
        uint32_t np_path_out_fifo      : 2;  /**< [ 13: 12] Config for np_path_out_fifo. */
        uint32_t scp_np_path_out_data_fifo : 2;/**< [ 11: 10] Config for scp_np_path_out_data_fifo. */
        uint32_t scp_np_path_outstd_req_fifo : 2;/**< [  9:  8] Config for scp_np_path_outstd_req_fifo. */
        uint32_t mcp_np_path_out_data_fifo : 2;/**< [  7:  6] Config for mcp_np_path_out_data_fifo. */
        uint32_t mcp_np_path_outstd_req_fifo : 2;/**< [  5:  4] Config for mcp_np_path_outstd_req_fifo. */
        uint32_t ncbo_skid_fifo        : 2;  /**< [  3:  2] Config for ncbo_skid_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 2;  /**< [  1:  0] Config for ncb_csr_sm_req_fifo. */
        uint32_t ncbo_skid_fifo        : 2;  /**< [  3:  2] Config for ncbo_skid_fifo. */
        uint32_t mcp_np_path_outstd_req_fifo : 2;/**< [  5:  4] Config for mcp_np_path_outstd_req_fifo. */
        uint32_t mcp_np_path_out_data_fifo : 2;/**< [  7:  6] Config for mcp_np_path_out_data_fifo. */
        uint32_t scp_np_path_outstd_req_fifo : 2;/**< [  9:  8] Config for scp_np_path_outstd_req_fifo. */
        uint32_t scp_np_path_out_data_fifo : 2;/**< [ 11: 10] Config for scp_np_path_out_data_fifo. */
        uint32_t np_path_out_fifo      : 2;  /**< [ 13: 12] Config for np_path_out_fifo. */
        uint32_t mcp_p_path_outstd_req_fifo : 2;/**< [ 15: 14] Config for mcp_p_path_outstd_req_fifo. */
        uint32_t mcp_p_path_out_data_fifo : 2;/**< [ 17: 16] Config for mcp_p_path_out_data_fifo. */
        uint32_t scp_p_path_outstd_req_fifo : 2;/**< [ 19: 18] Config for scp_p_path_outstd_req_fifo. */
        uint32_t scp_p_path_out_data_fifo : 2;/**< [ 21: 20] Config for scp_p_path_out_data_fifo. */
        uint32_t p_path_out_fifo       : 2;  /**< [ 23: 22] Config for p_path_out_fifo. */
        uint32_t scp_cr_path_outstd_req_fifo : 2;/**< [ 25: 24] Config for scp_cr_path_outstd_req_fifo. */
        uint32_t scp_cr_path_out_data_fifo : 2;/**< [ 27: 26] Config for scp_cr_path_out_data_fifo. */
        uint32_t mcp_cr_path_outstd_req_fifo : 2;/**< [ 29: 28] Config for mcp_cr_path_outstd_req_fifo. */
        uint32_t mcp_cr_path_out_data_fifo : 2;/**< [ 31: 30] Config for mcp_cr_path_out_data_fifo. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_bp_test0_bp_cfg_s_s cn; */
};

/**
 * Structure cpc_bp_test0_enable_s
 *
 * INTERNAL: CPC Backpressure Test Enable Structure
 *
 * This structure describes the layout of CPC_BP_TEST0[ENABLE].
 */
union bdk_cpc_bp_test0_enable_s
{
    uint32_t u;
    struct bdk_cpc_bp_test0_enable_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t mcp_cr_path_out_data_fifo : 1;/**< [ 15: 15] ENABLE for mcp_cr_path_out_data_fifo. */
        uint32_t mcp_cr_path_outstd_req_fifo : 1;/**< [ 14: 14] ENABLE for mcp_cr_path_outstd_req_fifo. */
        uint32_t scp_cr_path_out_data_fifo : 1;/**< [ 13: 13] ENABLE for scp_cr_path_out_data_fifo. */
        uint32_t scp_cr_path_outstd_req_fifo : 1;/**< [ 12: 12] ENABLE for scp_cr_path_outstd_req_fifo. */
        uint32_t p_path_out_fifo       : 1;  /**< [ 11: 11] ENABLE for p_path_out_fifo. */
        uint32_t scp_p_path_out_data_fifo : 1;/**< [ 10: 10] ENABLE for scp_p_path_out_data_fifo. */
        uint32_t scp_p_path_outstd_req_fifo : 1;/**< [  9:  9] ENABLE for scp_p_path_outstd_req_fifo. */
        uint32_t mcp_p_path_out_data_fifo : 1;/**< [  8:  8] ENABLE for mcp_p_path_out_data_fifo. */
        uint32_t mcp_p_path_outstd_req_fifo : 1;/**< [  7:  7] ENABLE for mcp_p_path_outstd_req_fifo. */
        uint32_t np_path_out_fifo      : 1;  /**< [  6:  6] ENABLE for np_path_out_fifo. */
        uint32_t scp_np_path_out_data_fifo : 1;/**< [  5:  5] ENABLE for scp_np_path_out_data_fifo. */
        uint32_t scp_np_path_outstd_req_fifo : 1;/**< [  4:  4] ENABLE for scp_np_path_outstd_req_fifo. */
        uint32_t mcp_np_path_out_data_fifo : 1;/**< [  3:  3] ENABLE for mcp_np_path_out_data_fifo. */
        uint32_t mcp_np_path_outstd_req_fifo : 1;/**< [  2:  2] ENABLE for mcp_np_path_outstd_req_fifo. */
        uint32_t ncbo_skid_fifo        : 1;  /**< [  1:  1] ENABLE for ncbo_skid_fifo. */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t ncb_csr_sm_req_fifo   : 1;  /**< [  0:  0] ENABLE for ncb_csr_sm_req_fifo. */
        uint32_t ncbo_skid_fifo        : 1;  /**< [  1:  1] ENABLE for ncbo_skid_fifo. */
        uint32_t mcp_np_path_outstd_req_fifo : 1;/**< [  2:  2] ENABLE for mcp_np_path_outstd_req_fifo. */
        uint32_t mcp_np_path_out_data_fifo : 1;/**< [  3:  3] ENABLE for mcp_np_path_out_data_fifo. */
        uint32_t scp_np_path_outstd_req_fifo : 1;/**< [  4:  4] ENABLE for scp_np_path_outstd_req_fifo. */
        uint32_t scp_np_path_out_data_fifo : 1;/**< [  5:  5] ENABLE for scp_np_path_out_data_fifo. */
        uint32_t np_path_out_fifo      : 1;  /**< [  6:  6] ENABLE for np_path_out_fifo. */
        uint32_t mcp_p_path_outstd_req_fifo : 1;/**< [  7:  7] ENABLE for mcp_p_path_outstd_req_fifo. */
        uint32_t mcp_p_path_out_data_fifo : 1;/**< [  8:  8] ENABLE for mcp_p_path_out_data_fifo. */
        uint32_t scp_p_path_outstd_req_fifo : 1;/**< [  9:  9] ENABLE for scp_p_path_outstd_req_fifo. */
        uint32_t scp_p_path_out_data_fifo : 1;/**< [ 10: 10] ENABLE for scp_p_path_out_data_fifo. */
        uint32_t p_path_out_fifo       : 1;  /**< [ 11: 11] ENABLE for p_path_out_fifo. */
        uint32_t scp_cr_path_outstd_req_fifo : 1;/**< [ 12: 12] ENABLE for scp_cr_path_outstd_req_fifo. */
        uint32_t scp_cr_path_out_data_fifo : 1;/**< [ 13: 13] ENABLE for scp_cr_path_out_data_fifo. */
        uint32_t mcp_cr_path_outstd_req_fifo : 1;/**< [ 14: 14] ENABLE for mcp_cr_path_outstd_req_fifo. */
        uint32_t mcp_cr_path_out_data_fifo : 1;/**< [ 15: 15] ENABLE for mcp_cr_path_out_data_fifo. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_bp_test0_enable_s_s cn; */
};

/**
 * Structure cpc_bp_test1_bp_cfg_s
 *
 * INTERNAL: CPC Backpressure Test 1 Configuration Structure
 *
 * This structure describes the layout of CPC_BP_TEST1[BP_CFG].
 */
union bdk_cpc_bp_test1_bp_cfg_s
{
    uint32_t u;
    struct bdk_cpc_bp_test1_bp_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_18_31        : 14;
        uint32_t gnt_order_fifo        : 2;  /**< [ 17: 16] Config for gnt_out_fifo. */
        uint32_t gib_out_data_fifo     : 2;  /**< [ 15: 14] Config for gib_out_data_fifo. */
        uint32_t cr_req_fif_arb_out_fifo : 2;/**< [ 13: 12] Config for cr_req_fif_arb_out_fifo. */
        uint32_t error_cr_path_out_fifo : 2; /**< [ 11: 10] Config for error_cr_path_out_fifo. */
        uint32_t error_cr_path_out_data_fifo : 2;/**< [  9:  8] Config for error_cr_path_out_data_fifo. */
        uint32_t error_cr_path_outstd_req_fifo : 2;/**< [  7:  6] Config for error_cr_path_outstd_req_fifo. */
        uint32_t cr_path_out_fifo      : 2;  /**< [  5:  4] Config for cr_path_out_fifo. */
        uint32_t cpc_cr_path_out_data_fifo : 2;/**< [  3:  2] Config for cpc_cr_path_out_data_fifo. */
        uint32_t cpc_cr_path_outstd_req_fifo : 2;/**< [  1:  0] Config for cpc_cr_path_outstd_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t cpc_cr_path_outstd_req_fifo : 2;/**< [  1:  0] Config for cpc_cr_path_outstd_req_fifo. */
        uint32_t cpc_cr_path_out_data_fifo : 2;/**< [  3:  2] Config for cpc_cr_path_out_data_fifo. */
        uint32_t cr_path_out_fifo      : 2;  /**< [  5:  4] Config for cr_path_out_fifo. */
        uint32_t error_cr_path_outstd_req_fifo : 2;/**< [  7:  6] Config for error_cr_path_outstd_req_fifo. */
        uint32_t error_cr_path_out_data_fifo : 2;/**< [  9:  8] Config for error_cr_path_out_data_fifo. */
        uint32_t error_cr_path_out_fifo : 2; /**< [ 11: 10] Config for error_cr_path_out_fifo. */
        uint32_t cr_req_fif_arb_out_fifo : 2;/**< [ 13: 12] Config for cr_req_fif_arb_out_fifo. */
        uint32_t gib_out_data_fifo     : 2;  /**< [ 15: 14] Config for gib_out_data_fifo. */
        uint32_t gnt_order_fifo        : 2;  /**< [ 17: 16] Config for gnt_out_fifo. */
        uint32_t reserved_18_31        : 14;
#endif /* Word 0 - End */
    } s;
    struct bdk_cpc_bp_test1_bp_cfg_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_24_31        : 8;
        uint32_t reserved_18_23        : 6;
        uint32_t gnt_order_fifo        : 2;  /**< [ 17: 16] Config for gnt_out_fifo. */
        uint32_t gib_out_data_fifo     : 2;  /**< [ 15: 14] Config for gib_out_data_fifo. */
        uint32_t cr_req_fif_arb_out_fifo : 2;/**< [ 13: 12] Config for cr_req_fif_arb_out_fifo. */
        uint32_t error_cr_path_out_fifo : 2; /**< [ 11: 10] Config for error_cr_path_out_fifo. */
        uint32_t error_cr_path_out_data_fifo : 2;/**< [  9:  8] Config for error_cr_path_out_data_fifo. */
        uint32_t error_cr_path_outstd_req_fifo : 2;/**< [  7:  6] Config for error_cr_path_outstd_req_fifo. */
        uint32_t cr_path_out_fifo      : 2;  /**< [  5:  4] Config for cr_path_out_fifo. */
        uint32_t cpc_cr_path_out_data_fifo : 2;/**< [  3:  2] Config for cpc_cr_path_out_data_fifo. */
        uint32_t cpc_cr_path_outstd_req_fifo : 2;/**< [  1:  0] Config for cpc_cr_path_outstd_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t cpc_cr_path_outstd_req_fifo : 2;/**< [  1:  0] Config for cpc_cr_path_outstd_req_fifo. */
        uint32_t cpc_cr_path_out_data_fifo : 2;/**< [  3:  2] Config for cpc_cr_path_out_data_fifo. */
        uint32_t cr_path_out_fifo      : 2;  /**< [  5:  4] Config for cr_path_out_fifo. */
        uint32_t error_cr_path_outstd_req_fifo : 2;/**< [  7:  6] Config for error_cr_path_outstd_req_fifo. */
        uint32_t error_cr_path_out_data_fifo : 2;/**< [  9:  8] Config for error_cr_path_out_data_fifo. */
        uint32_t error_cr_path_out_fifo : 2; /**< [ 11: 10] Config for error_cr_path_out_fifo. */
        uint32_t cr_req_fif_arb_out_fifo : 2;/**< [ 13: 12] Config for cr_req_fif_arb_out_fifo. */
        uint32_t gib_out_data_fifo     : 2;  /**< [ 15: 14] Config for gib_out_data_fifo. */
        uint32_t gnt_order_fifo        : 2;  /**< [ 17: 16] Config for gnt_out_fifo. */
        uint32_t reserved_18_23        : 6;
        uint32_t reserved_24_31        : 8;
#endif /* Word 0 - End */
    } cn;
};

/**
 * Structure cpc_bp_test1_enable_s
 *
 * INTERNAL: CPC Backpressure Test 1 Enable Structure
 *
 * This structure describes the layout of CPC_BP_TEST1[ENABLE].
 */
union bdk_cpc_bp_test1_enable_s
{
    uint32_t u;
    struct bdk_cpc_bp_test1_enable_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t gnt_order_fifo        : 1;  /**< [  8:  8] ENABLE for gnt_out_fifo. */
        uint32_t gib_out_data_fifo     : 1;  /**< [  7:  7] ENABLE for gib_out_data_fifo. */
        uint32_t cr_req_fif_arb_out_fifo : 1;/**< [  6:  6] ENABLE for cr_req_fif_arb_out_fifo. */
        uint32_t error_cr_path_out_fifo : 1; /**< [  5:  5] ENABLE for error_cr_path_out_fifo. */
        uint32_t error_cr_path_out_data_fifo : 1;/**< [  4:  4] ENABLE for error_cr_path_out_data_fifo. */
        uint32_t error_cr_path_outstd_req_fifo : 1;/**< [  3:  3] ENABLE for error_cr_path_outstd_req_fifo. */
        uint32_t cr_path_out_fifo      : 1;  /**< [  2:  2] ENABLE for cr_path_out_fifo. */
        uint32_t cpc_cr_path_out_data_fifo : 1;/**< [  1:  1] ENABLE for cpc_cr_path_out_data_fifo. */
        uint32_t cpc_cr_path_outstd_req_fifo : 1;/**< [  0:  0] ENABLE for cpc_cr_path_outstd_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t cpc_cr_path_outstd_req_fifo : 1;/**< [  0:  0] ENABLE for cpc_cr_path_outstd_req_fifo. */
        uint32_t cpc_cr_path_out_data_fifo : 1;/**< [  1:  1] ENABLE for cpc_cr_path_out_data_fifo. */
        uint32_t cr_path_out_fifo      : 1;  /**< [  2:  2] ENABLE for cr_path_out_fifo. */
        uint32_t error_cr_path_outstd_req_fifo : 1;/**< [  3:  3] ENABLE for error_cr_path_outstd_req_fifo. */
        uint32_t error_cr_path_out_data_fifo : 1;/**< [  4:  4] ENABLE for error_cr_path_out_data_fifo. */
        uint32_t error_cr_path_out_fifo : 1; /**< [  5:  5] ENABLE for error_cr_path_out_fifo. */
        uint32_t cr_req_fif_arb_out_fifo : 1;/**< [  6:  6] ENABLE for cr_req_fif_arb_out_fifo. */
        uint32_t gib_out_data_fifo     : 1;  /**< [  7:  7] ENABLE for gib_out_data_fifo. */
        uint32_t gnt_order_fifo        : 1;  /**< [  8:  8] ENABLE for gnt_out_fifo. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    struct bdk_cpc_bp_test1_enable_s_cn
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_12_31        : 20;
        uint32_t reserved_9_11         : 3;
        uint32_t gnt_order_fifo        : 1;  /**< [  8:  8] ENABLE for gnt_out_fifo. */
        uint32_t gib_out_data_fifo     : 1;  /**< [  7:  7] ENABLE for gib_out_data_fifo. */
        uint32_t cr_req_fif_arb_out_fifo : 1;/**< [  6:  6] ENABLE for cr_req_fif_arb_out_fifo. */
        uint32_t error_cr_path_out_fifo : 1; /**< [  5:  5] ENABLE for error_cr_path_out_fifo. */
        uint32_t error_cr_path_out_data_fifo : 1;/**< [  4:  4] ENABLE for error_cr_path_out_data_fifo. */
        uint32_t error_cr_path_outstd_req_fifo : 1;/**< [  3:  3] ENABLE for error_cr_path_outstd_req_fifo. */
        uint32_t cr_path_out_fifo      : 1;  /**< [  2:  2] ENABLE for cr_path_out_fifo. */
        uint32_t cpc_cr_path_out_data_fifo : 1;/**< [  1:  1] ENABLE for cpc_cr_path_out_data_fifo. */
        uint32_t cpc_cr_path_outstd_req_fifo : 1;/**< [  0:  0] ENABLE for cpc_cr_path_outstd_req_fifo. */
#else /* Word 0 - Little Endian */
        uint32_t cpc_cr_path_outstd_req_fifo : 1;/**< [  0:  0] ENABLE for cpc_cr_path_outstd_req_fifo. */
        uint32_t cpc_cr_path_out_data_fifo : 1;/**< [  1:  1] ENABLE for cpc_cr_path_out_data_fifo. */
        uint32_t cr_path_out_fifo      : 1;  /**< [  2:  2] ENABLE for cr_path_out_fifo. */
        uint32_t error_cr_path_outstd_req_fifo : 1;/**< [  3:  3] ENABLE for error_cr_path_outstd_req_fifo. */
        uint32_t error_cr_path_out_data_fifo : 1;/**< [  4:  4] ENABLE for error_cr_path_out_data_fifo. */
        uint32_t error_cr_path_out_fifo : 1; /**< [  5:  5] ENABLE for error_cr_path_out_fifo. */
        uint32_t cr_req_fif_arb_out_fifo : 1;/**< [  6:  6] ENABLE for cr_req_fif_arb_out_fifo. */
        uint32_t gib_out_data_fifo     : 1;  /**< [  7:  7] ENABLE for gib_out_data_fifo. */
        uint32_t gnt_order_fifo        : 1;  /**< [  8:  8] ENABLE for gnt_out_fifo. */
        uint32_t reserved_9_11         : 3;
        uint32_t reserved_12_31        : 20;
#endif /* Word 0 - End */
    } cn;
};

/**
 * Structure cpc_bp_test2_bp_cfg_s
 *
 * INTERNAL: CPC Backpressure Test 2 Configuration Structure
 *
 * This structure describes the layout of CPC_BP_TEST2[BP_CFG].
 */
union bdk_cpc_bp_test2_bp_cfg_s
{
    uint32_t u;
    struct bdk_cpc_bp_test2_bp_cfg_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_12_31        : 20;
        uint32_t cpc_ram_rowx_arb      : 12; /**< [ 11:  0] Config for cpc_ram_rowx_arb. */
#else /* Word 0 - Little Endian */
        uint32_t cpc_ram_rowx_arb      : 12; /**< [ 11:  0] Config for cpc_ram_rowx_arb. */
        uint32_t reserved_12_31        : 20;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_bp_test2_bp_cfg_s_s cn; */
};

/**
 * Structure cpc_bp_test2_enable_s
 *
 * INTERNAL: CPC Backpressure Test 2 Enable Structure
 *
 * This structure describes the layout of CPC_BP_TEST2[ENABLE].
 */
union bdk_cpc_bp_test2_enable_s
{
    uint32_t u;
    struct bdk_cpc_bp_test2_enable_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_6_31         : 26;
        uint32_t cpc_ram_rowx_arb      : 6;  /**< [  5:  0] ENABLE for cpc_ram_rowx_arb. */
#else /* Word 0 - Little Endian */
        uint32_t cpc_ram_rowx_arb      : 6;  /**< [  5:  0] ENABLE for cpc_ram_rowx_arb. */
        uint32_t reserved_6_31         : 26;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_bp_test2_enable_s_s cn; */
};

/**
 * Register (NCB32b) cpc_boot_owner#
 *
 * CPC Boot Owner Registers
 * These registers control an external arbiter for the boot device (SPI/eMMC)
 * across multiple external devices. There is a register for each requester:
 * _ \<0\> - SCP          - reset on SCP reset
 * _ \<1\> - MCP          - reset on MCP reset
 * _ \<2\> - AP Secure    - reset on core reset
 * _ \<3\> - AP Nonsecure - reset on core reset
 *
 * These register is only writable to the corresponding requestor(s) permitted with CPC_PERMIT.
 */
union bdk_cpc_boot_ownerx
{
    uint32_t u;
    struct bdk_cpc_boot_ownerx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_9_31         : 23;
        uint32_t boot_wait             : 1;  /**< [  8:  8](RO/H) Boot device wait. State of the BOOT_WAIT pseduo-input; see
                                                                 GPIO_PIN_SEL_E::BOOT_WAIT. */
        uint32_t reserved_1_7          : 7;
        uint32_t boot_req              : 1;  /**< [  0:  0](R/W) Owner is requesting or using SPI/eMMC. */
#else /* Word 0 - Little Endian */
        uint32_t boot_req              : 1;  /**< [  0:  0](R/W) Owner is requesting or using SPI/eMMC. */
        uint32_t reserved_1_7          : 7;
        uint32_t boot_wait             : 1;  /**< [  8:  8](RO/H) Boot device wait. State of the BOOT_WAIT pseduo-input; see
                                                                 GPIO_PIN_SEL_E::BOOT_WAIT. */
        uint32_t reserved_9_31         : 23;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_boot_ownerx_s cn; */
};
typedef union bdk_cpc_boot_ownerx bdk_cpc_boot_ownerx_t;

static inline uint64_t BDK_CPC_BOOT_OWNERX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_BOOT_OWNERX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=3))
        return 0x86d000000160ll + 8ll * ((a) & 0x3);
    __bdk_csr_fatal("CPC_BOOT_OWNERX", 1, a, 0, 0, 0);
}

#define typedef_BDK_CPC_BOOT_OWNERX(a) bdk_cpc_boot_ownerx_t
#define bustype_BDK_CPC_BOOT_OWNERX(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_BOOT_OWNERX(a) "CPC_BOOT_OWNERX"
#define device_bar_BDK_CPC_BOOT_OWNERX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_BOOT_OWNERX(a) (a)
#define arguments_BDK_CPC_BOOT_OWNERX(a) (a),-1,-1,-1

/**
 * Register (NCB32b) cpc_boot_rom_limit
 *
 * CPC Boot ROM Limit Register
 * This register contains the address limit in the internal bootrom that MCP and APs can
 * access.
 *
 * This register is only writable to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_boot_rom_limit
{
    uint32_t u;
    struct bdk_cpc_boot_rom_limit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t addr                  : 14; /**< [ 15:  2](R/W) End of ROM address. This field specifies the first invalid address in ROM_MEM();
                                                                 access to a ROM_MEM() address at or above this address will return a "br -1"
                                                                 (branch-to-self) instruction opcode. Writes to this register which attempt to
                                                                 set an [ADDR] greater than the previous [ADDR] setting are ignored.
                                                                 Address is word aligned. */
        uint32_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_1          : 2;
        uint32_t addr                  : 14; /**< [ 15:  2](R/W) End of ROM address. This field specifies the first invalid address in ROM_MEM();
                                                                 access to a ROM_MEM() address at or above this address will return a "br -1"
                                                                 (branch-to-self) instruction opcode. Writes to this register which attempt to
                                                                 set an [ADDR] greater than the previous [ADDR] setting are ignored.
                                                                 Address is word aligned. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_boot_rom_limit_s cn; */
};
typedef union bdk_cpc_boot_rom_limit bdk_cpc_boot_rom_limit_t;

#define BDK_CPC_BOOT_ROM_LIMIT BDK_CPC_BOOT_ROM_LIMIT_FUNC()
static inline uint64_t BDK_CPC_BOOT_ROM_LIMIT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_BOOT_ROM_LIMIT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000158ll;
    __bdk_csr_fatal("CPC_BOOT_ROM_LIMIT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_BOOT_ROM_LIMIT bdk_cpc_boot_rom_limit_t
#define bustype_BDK_CPC_BOOT_ROM_LIMIT BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_BOOT_ROM_LIMIT "CPC_BOOT_ROM_LIMIT"
#define device_bar_BDK_CPC_BOOT_ROM_LIMIT 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_BOOT_ROM_LIMIT 0
#define arguments_BDK_CPC_BOOT_ROM_LIMIT -1,-1,-1,-1

/**
 * Register (NCB) cpc_bp_test0
 *
 * INTERNAL: CPC Backpressure Test Register
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register can only be accessed using RSL/NCB, not the MCP/SCP cores.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_bp_test0
{
    uint64_t u;
    struct bdk_cpc_bp_test0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 16; /**< [ 63: 48](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 See CPC_BP_TEST0_ENABLE_S for field descriptions. */
        uint64_t bp_cfg                : 32; /**< [ 47: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 See CPC_BP_TEST0_BP_CFG_S for field descriptions. */
        uint64_t reserved_12_15        : 4;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_15        : 4;
        uint64_t bp_cfg                : 32; /**< [ 47: 16](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 See CPC_BP_TEST0_BP_CFG_S for field descriptions. */
        uint64_t enable                : 16; /**< [ 63: 48](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 See CPC_BP_TEST0_ENABLE_S for field descriptions. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_bp_test0_s cn; */
};
typedef union bdk_cpc_bp_test0 bdk_cpc_bp_test0_t;

#define BDK_CPC_BP_TEST0 BDK_CPC_BP_TEST0_FUNC()
static inline uint64_t BDK_CPC_BP_TEST0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_BP_TEST0_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000180ll;
    __bdk_csr_fatal("CPC_BP_TEST0", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_BP_TEST0 bdk_cpc_bp_test0_t
#define bustype_BDK_CPC_BP_TEST0 BDK_CSR_TYPE_NCB
#define basename_BDK_CPC_BP_TEST0 "CPC_BP_TEST0"
#define device_bar_BDK_CPC_BP_TEST0 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_BP_TEST0 0
#define arguments_BDK_CPC_BP_TEST0 -1,-1,-1,-1

/**
 * Register (NCB) cpc_bp_test1
 *
 * INTERNAL: CPC Backpressure Test Register
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register can only be accessed using RSL/NCB, not the MCP/SCP cores.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_bp_test1
{
    uint64_t u;
    struct bdk_cpc_bp_test1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t enable                : 12; /**< [ 63: 52](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 See CPC_BP_TEST1_ENABLE_S for field descriptions. */
        uint64_t reserved_48_51        : 4;
        uint64_t bp_cfg                : 24; /**< [ 47: 24](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 See CPC_BP_TEST1_BP_CFG_S for field descriptions. */
        uint64_t reserved_12_23        : 12;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_23        : 12;
        uint64_t bp_cfg                : 24; /**< [ 47: 24](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 See CPC_BP_TEST1_BP_CFG_S for field descriptions. */
        uint64_t reserved_48_51        : 4;
        uint64_t enable                : 12; /**< [ 63: 52](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 See CPC_BP_TEST1_ENABLE_S for field descriptions. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_bp_test1_s cn; */
};
typedef union bdk_cpc_bp_test1 bdk_cpc_bp_test1_t;

#define BDK_CPC_BP_TEST1 BDK_CPC_BP_TEST1_FUNC()
static inline uint64_t BDK_CPC_BP_TEST1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_BP_TEST1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000188ll;
    __bdk_csr_fatal("CPC_BP_TEST1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_BP_TEST1 bdk_cpc_bp_test1_t
#define bustype_BDK_CPC_BP_TEST1 BDK_CSR_TYPE_NCB
#define basename_BDK_CPC_BP_TEST1 "CPC_BP_TEST1"
#define device_bar_BDK_CPC_BP_TEST1 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_BP_TEST1 0
#define arguments_BDK_CPC_BP_TEST1 -1,-1,-1,-1

/**
 * Register (NCB) cpc_bp_test2
 *
 * INTERNAL: CPC Backpressure Test Register
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register can only be accessed using RSL/NCB, not the MCP/SCP cores.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_bp_test2
{
    uint64_t u;
    struct bdk_cpc_bp_test2_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_58_63        : 6;
        uint64_t enable                : 6;  /**< [ 57: 52](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 See CPC_BP_TEST2_ENABLE_S for field descriptions. */
        uint64_t reserved_36_51        : 16;
        uint64_t bp_cfg                : 12; /**< [ 35: 24](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 See CPC_BP_TEST2_BP_CFG_S for field descriptions. */
        uint64_t reserved_12_23        : 12;
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
#else /* Word 0 - Little Endian */
        uint64_t lfsr_freq             : 12; /**< [ 11:  0](R/W) Test LFSR update frequency in coprocessor-clocks minus one. */
        uint64_t reserved_12_23        : 12;
        uint64_t bp_cfg                : 12; /**< [ 35: 24](R/W) Backpressure weight. For diagnostic use only.
                                                                 Internal:
                                                                 There are 2 backpressure configuration bits per enable, with the two bits
                                                                 defined as 0x0=100% of the time, 0x1=75% of the time, 0x2=50% of the time,
                                                                 0x3=25% of the time.
                                                                 See CPC_BP_TEST2_BP_CFG_S for field descriptions. */
        uint64_t reserved_36_51        : 16;
        uint64_t enable                : 6;  /**< [ 57: 52](R/W) Enable test mode. For diagnostic use only.
                                                                 Internal:
                                                                 Once a bit is set, random backpressure is generated
                                                                 at the corresponding point to allow for more frequent backpressure.
                                                                 See CPC_BP_TEST2_ENABLE_S for field descriptions. */
        uint64_t reserved_58_63        : 6;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_bp_test2_s cn; */
};
typedef union bdk_cpc_bp_test2 bdk_cpc_bp_test2_t;

#define BDK_CPC_BP_TEST2 BDK_CPC_BP_TEST2_FUNC()
static inline uint64_t BDK_CPC_BP_TEST2_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_BP_TEST2_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000190ll;
    __bdk_csr_fatal("CPC_BP_TEST2", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_BP_TEST2 bdk_cpc_bp_test2_t
#define bustype_BDK_CPC_BP_TEST2 BDK_CSR_TYPE_NCB
#define basename_BDK_CPC_BP_TEST2 "CPC_BP_TEST2"
#define device_bar_BDK_CPC_BP_TEST2 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_BP_TEST2 0
#define arguments_BDK_CPC_BP_TEST2 -1,-1,-1,-1

/**
 * Register (NCB32b) cpc_clken
 *
 * CPC Clock Enable Register
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_clken
{
    uint32_t u;
    struct bdk_cpc_clken_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_1_31         : 31;
        uint32_t clken                 : 1;  /**< [  0:  0](R/W) Force the conditional clocking within CPC to be always on. For diagnostic use only. */
#else /* Word 0 - Little Endian */
        uint32_t clken                 : 1;  /**< [  0:  0](R/W) Force the conditional clocking within CPC to be always on. For diagnostic use only. */
        uint32_t reserved_1_31         : 31;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_clken_s cn; */
};
typedef union bdk_cpc_clken bdk_cpc_clken_t;

#define BDK_CPC_CLKEN BDK_CPC_CLKEN_FUNC()
static inline uint64_t BDK_CPC_CLKEN_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_CLKEN_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000118ll;
    __bdk_csr_fatal("CPC_CLKEN", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_CLKEN bdk_cpc_clken_t
#define bustype_BDK_CPC_CLKEN BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_CLKEN "CPC_CLKEN"
#define device_bar_BDK_CPC_CLKEN 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_CLKEN 0
#define arguments_BDK_CPC_CLKEN -1,-1,-1,-1

/**
 * Register (NCB32b) cpc_const
 *
 * CPC Constants Register
 * This register is reset on chip reset.
 */
union bdk_cpc_const
{
    uint32_t u;
    struct bdk_cpc_const_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t mem_regions           : 8;  /**< [ 15:  8](RO) Indicates number of 16KB memory regions in the CPC RAM.
                                                                 Internal:
                                                                 Needs to change if RAM size changes. */
        uint32_t cores                 : 8;  /**< [  7:  0](RO) Indicates number of XCP cores within CPC. For function of each core see CPC_XCP_MAP_E. */
#else /* Word 0 - Little Endian */
        uint32_t cores                 : 8;  /**< [  7:  0](RO) Indicates number of XCP cores within CPC. For function of each core see CPC_XCP_MAP_E. */
        uint32_t mem_regions           : 8;  /**< [ 15:  8](RO) Indicates number of 16KB memory regions in the CPC RAM.
                                                                 Internal:
                                                                 Needs to change if RAM size changes. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_const_s cn; */
};
typedef union bdk_cpc_const bdk_cpc_const_t;

#define BDK_CPC_CONST BDK_CPC_CONST_FUNC()
static inline uint64_t BDK_CPC_CONST_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_CONST_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000000ll;
    __bdk_csr_fatal("CPC_CONST", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_CONST bdk_cpc_const_t
#define bustype_BDK_CPC_CONST BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_CONST "CPC_CONST"
#define device_bar_BDK_CPC_CONST 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_CONST 0
#define arguments_BDK_CPC_CONST -1,-1,-1,-1

/**
 * Register (NCB) cpc_csclk_active_pc
 *
 * CPC Conditional Coprocessor Clock Counter Register
 * This register counts conditional clocks for power management.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_csclk_active_pc
{
    uint64_t u;
    struct bdk_cpc_csclk_active_pc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#else /* Word 0 - Little Endian */
        uint64_t count                 : 64; /**< [ 63:  0](R/W/H) Count of conditional coprocessor-clock cycles since reset. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_csclk_active_pc_s cn; */
};
typedef union bdk_cpc_csclk_active_pc bdk_cpc_csclk_active_pc_t;

#define BDK_CPC_CSCLK_ACTIVE_PC BDK_CPC_CSCLK_ACTIVE_PC_FUNC()
static inline uint64_t BDK_CPC_CSCLK_ACTIVE_PC_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_CSCLK_ACTIVE_PC_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000010ll;
    __bdk_csr_fatal("CPC_CSCLK_ACTIVE_PC", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_CSCLK_ACTIVE_PC bdk_cpc_csclk_active_pc_t
#define bustype_BDK_CPC_CSCLK_ACTIVE_PC BDK_CSR_TYPE_NCB
#define basename_BDK_CPC_CSCLK_ACTIVE_PC "CPC_CSCLK_ACTIVE_PC"
#define device_bar_BDK_CPC_CSCLK_ACTIVE_PC 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_CSCLK_ACTIVE_PC 0
#define arguments_BDK_CPC_CSCLK_ACTIVE_PC -1,-1,-1,-1

/**
 * Register (NCB32b) cpc_eco
 *
 * INTERNAL: CPC ECO Register
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_eco
{
    uint32_t u;
    struct bdk_cpc_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint32_t eco_rw                : 32; /**< [ 31:  0](R/W) Reserved for ECO usage. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_eco_s cn; */
};
typedef union bdk_cpc_eco bdk_cpc_eco_t;

#define BDK_CPC_ECO BDK_CPC_ECO_FUNC()
static inline uint64_t BDK_CPC_ECO_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_ECO_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000100ll;
    __bdk_csr_fatal("CPC_ECO", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_ECO bdk_cpc_eco_t
#define bustype_BDK_CPC_ECO BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_ECO "CPC_ECO"
#define device_bar_BDK_CPC_ECO 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_ECO 0
#define arguments_BDK_CPC_ECO -1,-1,-1,-1

/**
 * Register (NCB32b) cpc_gib_loop_req
 *
 * INTERNAL: CPC GIA/GIB Loopback Request Register
 *
 * This register is used for full chip diagnostics.
 *
 * Software loads a GIB device ID (as enumerated by PCC_DEV_CON_E) into [STREAM], then sets [GO].
 * CPC will send the stream ID over the GIA bus. If/when it hits a GIB slave device that can send
 * the specified stream ID, that slave will respond on the GIB bus, and the response information
 * is
 * loaded into CPC_GIB_LOOP_RESP0 and CPC_GIB_LOOP_RESP1, and CPC_GIB_LOOP_RESP0[RESP_DONE] is
 * set.
 *
 * If no devices decode the given [STREAM], CPC_GIB_LOOP_RESP0[RESP_DONE] is never
 * set. Software must time out this case itself.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_gib_loop_req
{
    uint32_t u;
    struct bdk_cpc_gib_loop_req_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t go                    : 1;  /**< [ 31: 31](WO) Write one to initiate a GIA-to-GIB request. Must not initiate another request
                                                                 until CPC_GIB_LOOP_RESP0[RESP_DONE] is set, or 1 msec has passed. */
        uint32_t reserved_22_30        : 9;
        uint32_t stream                : 22; /**< [ 21:  0](R/W) The stream ID to request on GIA.  Enumerated by PCC_DEV_CON_E. */
#else /* Word 0 - Little Endian */
        uint32_t stream                : 22; /**< [ 21:  0](R/W) The stream ID to request on GIA.  Enumerated by PCC_DEV_CON_E. */
        uint32_t reserved_22_30        : 9;
        uint32_t go                    : 1;  /**< [ 31: 31](WO) Write one to initiate a GIA-to-GIB request. Must not initiate another request
                                                                 until CPC_GIB_LOOP_RESP0[RESP_DONE] is set, or 1 msec has passed. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_gib_loop_req_s cn; */
};
typedef union bdk_cpc_gib_loop_req bdk_cpc_gib_loop_req_t;

#define BDK_CPC_GIB_LOOP_REQ BDK_CPC_GIB_LOOP_REQ_FUNC()
static inline uint64_t BDK_CPC_GIB_LOOP_REQ_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_GIB_LOOP_REQ_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000030ll;
    __bdk_csr_fatal("CPC_GIB_LOOP_REQ", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_GIB_LOOP_REQ bdk_cpc_gib_loop_req_t
#define bustype_BDK_CPC_GIB_LOOP_REQ BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_GIB_LOOP_REQ "CPC_GIB_LOOP_REQ"
#define device_bar_BDK_CPC_GIB_LOOP_REQ 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_GIB_LOOP_REQ 0
#define arguments_BDK_CPC_GIB_LOOP_REQ -1,-1,-1,-1

/**
 * Register (NCB) cpc_gib_loop_resp0
 *
 * INTERNAL: CPC GIA/GIB Loopback Response 0 Register
 *
 * See CPC_GIB_LOOP_REQ.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_gib_loop_resp0
{
    uint64_t u;
    struct bdk_cpc_gib_loop_resp0_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_53_63        : 11;
        uint64_t addr                  : 51; /**< [ 52:  2](RO/H) GIB message address \<52:2\>. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with
                                                                 one, and is clear. */
        uint64_t reserved_1            : 1;
        uint64_t resp_done             : 1;  /**< [  0:  0](R/W1C/H) Response is done bit. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and is clear. */
#else /* Word 0 - Little Endian */
        uint64_t resp_done             : 1;  /**< [  0:  0](R/W1C/H) Response is done bit. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and is clear. */
        uint64_t reserved_1            : 1;
        uint64_t addr                  : 51; /**< [ 52:  2](RO/H) GIB message address \<52:2\>. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with
                                                                 one, and is clear. */
        uint64_t reserved_53_63        : 11;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_gib_loop_resp0_s cn; */
};
typedef union bdk_cpc_gib_loop_resp0 bdk_cpc_gib_loop_resp0_t;

#define BDK_CPC_GIB_LOOP_RESP0 BDK_CPC_GIB_LOOP_RESP0_FUNC()
static inline uint64_t BDK_CPC_GIB_LOOP_RESP0_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_GIB_LOOP_RESP0_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000020ll;
    __bdk_csr_fatal("CPC_GIB_LOOP_RESP0", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_GIB_LOOP_RESP0 bdk_cpc_gib_loop_resp0_t
#define bustype_BDK_CPC_GIB_LOOP_RESP0 BDK_CSR_TYPE_NCB
#define basename_BDK_CPC_GIB_LOOP_RESP0 "CPC_GIB_LOOP_RESP0"
#define device_bar_BDK_CPC_GIB_LOOP_RESP0 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_GIB_LOOP_RESP0 0
#define arguments_BDK_CPC_GIB_LOOP_RESP0 -1,-1,-1,-1

/**
 * Register (NCB) cpc_gib_loop_resp1
 *
 * INTERNAL: CPC GIA/GIB Loopback Response 1 Register
 *
 * See CPC_GIB_LOOP_REQ.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_gib_loop_resp1
{
    uint64_t u;
    struct bdk_cpc_gib_loop_resp1_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t stream                : 22; /**< [ 63: 42](RO/H) GIB response's stream ID. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and is clear. */
        uint64_t phys                  : 1;  /**< [ 41: 41](RO/H) GIB response's physical bit. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and
                                                                 is clear. */
        uint64_t node_rsvd             : 2;  /**< [ 40: 39](RO/H) Reserved. */
        uint64_t secure                : 1;  /**< [ 38: 38](RO/H) GIB response's secure bit. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and is clear. */
        uint64_t reserved_32_37        : 6;
        uint64_t data                  : 32; /**< [ 31:  0](RO/H) GIB response's MSI-X data. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and is clear. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](RO/H) GIB response's MSI-X data. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and is clear. */
        uint64_t reserved_32_37        : 6;
        uint64_t secure                : 1;  /**< [ 38: 38](RO/H) GIB response's secure bit. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and is clear. */
        uint64_t node_rsvd             : 2;  /**< [ 40: 39](RO/H) Reserved. */
        uint64_t phys                  : 1;  /**< [ 41: 41](RO/H) GIB response's physical bit. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and
                                                                 is clear. */
        uint64_t stream                : 22; /**< [ 63: 42](RO/H) GIB response's stream ID. CPC clears when CPC_GIB_LOOP_REQ[GO] is written with one, and is clear. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_gib_loop_resp1_s cn; */
};
typedef union bdk_cpc_gib_loop_resp1 bdk_cpc_gib_loop_resp1_t;

#define BDK_CPC_GIB_LOOP_RESP1 BDK_CPC_GIB_LOOP_RESP1_FUNC()
static inline uint64_t BDK_CPC_GIB_LOOP_RESP1_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_GIB_LOOP_RESP1_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000028ll;
    __bdk_csr_fatal("CPC_GIB_LOOP_RESP1", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_GIB_LOOP_RESP1 bdk_cpc_gib_loop_resp1_t
#define bustype_BDK_CPC_GIB_LOOP_RESP1 BDK_CSR_TYPE_NCB
#define basename_BDK_CPC_GIB_LOOP_RESP1 "CPC_GIB_LOOP_RESP1"
#define device_bar_BDK_CPC_GIB_LOOP_RESP1 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_GIB_LOOP_RESP1 0
#define arguments_BDK_CPC_GIB_LOOP_RESP1 -1,-1,-1,-1

/**
 * Register (NCB32b) cpc_permit
 *
 * CPC Register Permit Registers
 * This register is used to control CPC register permissions.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_permit
{
    uint32_t u;
    struct bdk_cpc_permit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t permitdis             : 4;  /**< [  3:  0](R/W) Access permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access.
                                                                 _ \<2\> if set disallows non-MCP/SCP (e.g. AP, NCSI, JTAG) secure access.
                                                                 _ \<3\> if set disallows non-MCP/SCP (e.g. AP, NCSI, JTAG) nonsecure access. */
#else /* Word 0 - Little Endian */
        uint32_t permitdis             : 4;  /**< [  3:  0](R/W) Access permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access.
                                                                 _ \<2\> if set disallows non-MCP/SCP (e.g. AP, NCSI, JTAG) secure access.
                                                                 _ \<3\> if set disallows non-MCP/SCP (e.g. AP, NCSI, JTAG) nonsecure access. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_permit_s cn; */
};
typedef union bdk_cpc_permit bdk_cpc_permit_t;

#define BDK_CPC_PERMIT BDK_CPC_PERMIT_FUNC()
static inline uint64_t BDK_CPC_PERMIT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_PERMIT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000120ll;
    __bdk_csr_fatal("CPC_PERMIT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_PERMIT bdk_cpc_permit_t
#define bustype_BDK_CPC_PERMIT BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_PERMIT "CPC_PERMIT"
#define device_bar_BDK_CPC_PERMIT 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_PERMIT 0
#define arguments_BDK_CPC_PERMIT -1,-1,-1,-1

/**
 * Register (NCB) cpc_ram_mem#
 *
 * CPC RAM Memory Registers
 * These registers access the CPC RAM memory space. The size of the RAM is discoverable
 * with CPC_CONST[MEM_REGIONS].
 *
 * This register is only accessible to the requestor(s) permitted with CPC_RAM_PERMIT().
 *
 * This register is reset on chip reset.
 *
 * Internal:
 * If size changes, must also update CPC_CONST[MEM_REGIONS] and CPC_RAM_PERMIT().
 */
union bdk_cpc_ram_memx
{
    uint64_t u;
    struct bdk_cpc_ram_memx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W) RAM data. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](R/W) RAM data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_ram_memx_s cn; */
};
typedef union bdk_cpc_ram_memx bdk_cpc_ram_memx_t;

static inline uint64_t BDK_CPC_RAM_MEMX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_RAM_MEMX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=49151))
        return 0x86d000080000ll + 8ll * ((a) & 0xffff);
    __bdk_csr_fatal("CPC_RAM_MEMX", 1, a, 0, 0, 0);
}

#define typedef_BDK_CPC_RAM_MEMX(a) bdk_cpc_ram_memx_t
#define bustype_BDK_CPC_RAM_MEMX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CPC_RAM_MEMX(a) "CPC_RAM_MEMX"
#define device_bar_BDK_CPC_RAM_MEMX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_RAM_MEMX(a) (a)
#define arguments_BDK_CPC_RAM_MEMX(a) (a),-1,-1,-1

/**
 * Register (NCB32b) cpc_ram_permit#
 *
 * CPC RAM Permit Registers
 * These registers are used to control the read permissions of RAM space access permissions of
 * the MIPS and AP cores
 * The RAM is split into 24 secure regions.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_ram_permitx
{
    uint32_t u;
    struct bdk_cpc_ram_permitx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t exedis                : 2;  /**< [ 31: 30](R/W) Execute permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access. */
        uint32_t reserved_20_29        : 10;
        uint32_t wrdis                 : 4;  /**< [ 19: 16](R/W) Write permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access.
                                                                 _ \<2\> if set disallows non-MCP/SCP (e.g. AP) secure access.
                                                                 _ \<3\> if set disallows non-MCP/SCP (e.g. AP) nonsecure access. */
        uint32_t reserved_4_15         : 12;
        uint32_t rddis                 : 4;  /**< [  3:  0](R/W) Read permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access.
                                                                 _ \<2\> if set disallows non-MCP/SCP (e.g. AP) secure access.
                                                                 _ \<3\> if set disallows non-MCP/SCP (e.g. AP) nonsecure access. */
#else /* Word 0 - Little Endian */
        uint32_t rddis                 : 4;  /**< [  3:  0](R/W) Read permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access.
                                                                 _ \<2\> if set disallows non-MCP/SCP (e.g. AP) secure access.
                                                                 _ \<3\> if set disallows non-MCP/SCP (e.g. AP) nonsecure access. */
        uint32_t reserved_4_15         : 12;
        uint32_t wrdis                 : 4;  /**< [ 19: 16](R/W) Write permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access.
                                                                 _ \<2\> if set disallows non-MCP/SCP (e.g. AP) secure access.
                                                                 _ \<3\> if set disallows non-MCP/SCP (e.g. AP) nonsecure access. */
        uint32_t reserved_20_29        : 10;
        uint32_t exedis                : 2;  /**< [ 31: 30](R/W) Execute permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_ram_permitx_s cn; */
};
typedef union bdk_cpc_ram_permitx bdk_cpc_ram_permitx_t;

static inline uint64_t BDK_CPC_RAM_PERMITX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_RAM_PERMITX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=23))
        return 0x86d000008000ll + 8ll * ((a) & 0x1f);
    __bdk_csr_fatal("CPC_RAM_PERMITX", 1, a, 0, 0, 0);
}

#define typedef_BDK_CPC_RAM_PERMITX(a) bdk_cpc_ram_permitx_t
#define bustype_BDK_CPC_RAM_PERMITX(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_RAM_PERMITX(a) "CPC_RAM_PERMITX"
#define device_bar_BDK_CPC_RAM_PERMITX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_RAM_PERMITX(a) (a)
#define arguments_BDK_CPC_RAM_PERMITX(a) (a),-1,-1,-1

/**
 * Register (NCB) cpc_rom_mem#
 *
 * CPC ROM Memory Registers
 * These registers access the CPC ROM memory space.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_BOOT_ROM_LIMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_rom_memx
{
    uint64_t u;
    struct bdk_cpc_rom_memx_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](RO) ROM data. */
#else /* Word 0 - Little Endian */
        uint64_t dat                   : 64; /**< [ 63:  0](RO) ROM data. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_rom_memx_s cn; */
};
typedef union bdk_cpc_rom_memx bdk_cpc_rom_memx_t;

static inline uint64_t BDK_CPC_ROM_MEMX(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_ROM_MEMX(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=4095))
        return 0x86d000010000ll + 8ll * ((a) & 0xfff);
    __bdk_csr_fatal("CPC_ROM_MEMX", 1, a, 0, 0, 0);
}

#define typedef_BDK_CPC_ROM_MEMX(a) bdk_cpc_rom_memx_t
#define bustype_BDK_CPC_ROM_MEMX(a) BDK_CSR_TYPE_NCB
#define basename_BDK_CPC_ROM_MEMX(a) "CPC_ROM_MEMX"
#define device_bar_BDK_CPC_ROM_MEMX(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_ROM_MEMX(a) (a)
#define arguments_BDK_CPC_ROM_MEMX(a) (a),-1,-1,-1

/**
 * Register (NCB32b) cpc_scp_boot_rom_limit
 *
 * CPC SCP Boot ROM Limit Register
 * This register contains the address limit in the internal bootrom that SCP can access.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset & scp_reset
 */
union bdk_cpc_scp_boot_rom_limit
{
    uint32_t u;
    struct bdk_cpc_scp_boot_rom_limit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_16_31        : 16;
        uint32_t addr                  : 14; /**< [ 15:  2](R/W) End of ROM address. This field specifies the first invalid address in ROM_MEM();
                                                                 access to a ROM_MEM() address at or above this address will return a "br -1"
                                                                 (branch-to-self) instruction opcode. Writes to this register which attempt to
                                                                 set an [ADDR] greater than the previous [ADDR] setting are ignored.
                                                                 Address is word aligned. */
        uint32_t reserved_0_1          : 2;
#else /* Word 0 - Little Endian */
        uint32_t reserved_0_1          : 2;
        uint32_t addr                  : 14; /**< [ 15:  2](R/W) End of ROM address. This field specifies the first invalid address in ROM_MEM();
                                                                 access to a ROM_MEM() address at or above this address will return a "br -1"
                                                                 (branch-to-self) instruction opcode. Writes to this register which attempt to
                                                                 set an [ADDR] greater than the previous [ADDR] setting are ignored.
                                                                 Address is word aligned. */
        uint32_t reserved_16_31        : 16;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_scp_boot_rom_limit_s cn; */
};
typedef union bdk_cpc_scp_boot_rom_limit bdk_cpc_scp_boot_rom_limit_t;

#define BDK_CPC_SCP_BOOT_ROM_LIMIT BDK_CPC_SCP_BOOT_ROM_LIMIT_FUNC()
static inline uint64_t BDK_CPC_SCP_BOOT_ROM_LIMIT_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_SCP_BOOT_ROM_LIMIT_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000150ll;
    __bdk_csr_fatal("CPC_SCP_BOOT_ROM_LIMIT", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_SCP_BOOT_ROM_LIMIT bdk_cpc_scp_boot_rom_limit_t
#define bustype_BDK_CPC_SCP_BOOT_ROM_LIMIT BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_SCP_BOOT_ROM_LIMIT "CPC_SCP_BOOT_ROM_LIMIT"
#define device_bar_BDK_CPC_SCP_BOOT_ROM_LIMIT 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_SCP_BOOT_ROM_LIMIT 0
#define arguments_BDK_CPC_SCP_BOOT_ROM_LIMIT -1,-1,-1,-1

/**
 * Register (NCB32b) cpc_timer100
 *
 * CPC Timer 100 MHz Register
 * This register contains the common 100 MHz timer register for the XCP cores.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_timer100
{
    uint32_t u;
    struct bdk_cpc_timer100_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t tmr                   : 32; /**< [ 31:  0](R/W/H) Free running count of 100 MHz clock cycles. */
#else /* Word 0 - Little Endian */
        uint32_t tmr                   : 32; /**< [ 31:  0](R/W/H) Free running count of 100 MHz clock cycles. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_timer100_s cn; */
};
typedef union bdk_cpc_timer100 bdk_cpc_timer100_t;

#define BDK_CPC_TIMER100 BDK_CPC_TIMER100_FUNC()
static inline uint64_t BDK_CPC_TIMER100_FUNC(void) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_TIMER100_FUNC(void)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX))
        return 0x86d000000110ll;
    __bdk_csr_fatal("CPC_TIMER100", 0, 0, 0, 0, 0);
}

#define typedef_BDK_CPC_TIMER100 bdk_cpc_timer100_t
#define bustype_BDK_CPC_TIMER100 BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_TIMER100 "CPC_TIMER100"
#define device_bar_BDK_CPC_TIMER100 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_TIMER100 0
#define arguments_BDK_CPC_TIMER100 -1,-1,-1,-1

/**
 * Register (NCB32b) cpc_xcp#_permit
 *
 * CPC Register Permit Registers
 * These registers are used to control the XCP register permissions.
 *
 * This register is only accessible to the requestor(s) permitted with CPC_PERMIT.
 *
 * This register is reset on chip reset.
 */
union bdk_cpc_xcpx_permit
{
    uint32_t u;
    struct bdk_cpc_xcpx_permit_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint32_t reserved_4_31         : 28;
        uint32_t permitdis             : 4;  /**< [  3:  0](R/W) Access permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access.
                                                                 _ \<2\> if set disallows non-MCP/SCP (e.g. AP) secure access.
                                                                 _ \<3\> if set disallows non-MCP/SCP (e.g. AP) nonsecure access. */
#else /* Word 0 - Little Endian */
        uint32_t permitdis             : 4;  /**< [  3:  0](R/W) Access permission of each access group.
                                                                 _ \<0\> if set disallows SCP access.
                                                                 _ \<1\> if set disallows MCP access.
                                                                 _ \<2\> if set disallows non-MCP/SCP (e.g. AP) secure access.
                                                                 _ \<3\> if set disallows non-MCP/SCP (e.g. AP) nonsecure access. */
        uint32_t reserved_4_31         : 28;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_cpc_xcpx_permit_s cn; */
};
typedef union bdk_cpc_xcpx_permit bdk_cpc_xcpx_permit_t;

static inline uint64_t BDK_CPC_XCPX_PERMIT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_CPC_XCPX_PERMIT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN9XXX) && (a<=1))
        return 0x86d000000140ll + 8ll * ((a) & 0x1);
    __bdk_csr_fatal("CPC_XCPX_PERMIT", 1, a, 0, 0, 0);
}

#define typedef_BDK_CPC_XCPX_PERMIT(a) bdk_cpc_xcpx_permit_t
#define bustype_BDK_CPC_XCPX_PERMIT(a) BDK_CSR_TYPE_NCB32b
#define basename_BDK_CPC_XCPX_PERMIT(a) "CPC_XCPX_PERMIT"
#define device_bar_BDK_CPC_XCPX_PERMIT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_CPC_XCPX_PERMIT(a) (a)
#define arguments_BDK_CPC_XCPX_PERMIT(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_CPC_H__ */
