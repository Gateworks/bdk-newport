/***********************license start***********************************
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
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-tns.h"

#include <stdio.h>
#include <malloc.h>

/* This code is an optional part of the BDK.  It is only linked in
   if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(TNS);

/* Constants to define the number of various interfaces */
#define TNS_MAX_LMACS   8
#define TNS_MIN_LMAC    0
#define TNS_MAX_NICS    2
#define TNS_MIN_NIC     8

#define TNS_MAX_LOGICAL_PORTS   256

#define TNS_MAX_NIC_PLUT_ENTRIES    256
#define TNS_MAX_LMAC_PLUT_ENTRIES   8
#define TNS_MAX_FWD_PLUT_ENTRIES    TNS_MAX_NIC_PLUT_ENTRIES

#define TNS_NIC_PLUT_ILLEGAL    0xff
#define TNS_LMAC_PLUT_ILLEGAL   TNS_NIC_PLUT_ILLEGAL
#define TNS_LB_PLUT_ILLEGAL     TNS_NIC_PLUT_ILLEGAL
#define TNS_FWD_PLUT_ILLEGAL    0xf

/* This caches the TNS enable bit */
static int tns_enabled = 0;

/**
 * Verify that BIST0-BIST11 contain no boot initialization errors.
 * If any are found log a message and dump the register contents.
 *
 * @param bdk_node_t node
 *
 * @return
 */
static void bdk_tns_check_bist(bdk_node_t node)
{
    bdk_tns_bist_status_t bist_status;
    bdk_tns_bist_status1_t bist_status1;
    bdk_tns_bist_status2_t bist_status2;
    bdk_tns_bist_status3_t bist_status3;
    bdk_tns_bist_status4_t bist_status4;
    bdk_tns_bist_status5_t bist_status5;
    bdk_tns_bist_status6_t bist_status6;
    bdk_tns_bist_status7_t bist_status7;
    bdk_tns_bist_status8_t bist_status8;
    bdk_tns_bist_status9_t bist_status9;
    bdk_tns_bist_status10_t bist_status10;
    bdk_tns_bist_status11_t bist_status11;

#define BDK_TNS_REG_NAME(r) basename_##r
    /* BIST 0 */
    bist_status.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS);
    if (bist_status.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST0 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS), bist_status.u);
    }
    /* BIST 1 */
    bist_status1.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS1);
    if (bist_status1.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST1 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS1), bist_status1.u);
    }
    /* BIST 2 */
    bist_status2.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS2);
    if (bist_status2.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST2 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS2), bist_status2.u);
    }
    /* BIST 3 */
    bist_status3.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS3);
    if (bist_status3.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST3 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS3), bist_status3.u);
    }
    /* BIST 4 */
    bist_status4.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS4);
    if (bist_status4.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST4 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS4), bist_status4.u);
    }
    /* BIST 5 */
    bist_status5.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS5);
    if (bist_status5.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST5 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS5), bist_status5.u);
    }
    /* BIST 6 */
    bist_status6.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS6);
    if (bist_status6.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST6 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS6), bist_status6.u);
    }
    /* BIST 7 */
    bist_status7.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS7);
    if (bist_status7.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST7 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS7), bist_status7.u);
    }
    /* BIST 8 */
    bist_status8.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS8);
    if (bist_status8.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST8 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS8), bist_status8.u);
    }
    /* BIST 9 */
    bist_status9.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS9);
    if (bist_status9.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST9 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS9), bist_status9.u);
    }
    /* BIST 10 */
    bist_status10.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS10);
    if (bist_status10.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST10 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS10), bist_status10.u);
    }
    /* BIST 11 */
    bist_status11.u = BDK_CSR_READ(node, BDK_TNS_BIST_STATUS11);
    if (bist_status11.u != 0ULL)
    {
        bdk_warn("bdk_tns_check_bist: BIST11 failures\n");
        bdk_csr_decode(BDK_TNS_REG_NAME(BDK_TNS_BIST_STATUS11), bist_status11.u);
    }
#undef BDK_TNS_REG_NAME
}

/**
 * Debug Control of TDMA functionality.  Allows the setting of the token
 * levels in the drop request, p2x, x2p and loopback FIFOs at which
 * backpressure is asserted.  Also enables the cut-thru packet transmission
 * to each physical port.
 *
 * @param bdk_node_t node
 * @param uint8_t x2p_thresh
 * @param uint8_t p2x_thresh
 * @param uint8_t lb_thresh
 * @param uint8_t drop_req_thresh
 * @param uint8_t lb_credits
 * @param uint8_t nic_on
 * @param uint8_t lmac_on
 * @param uint8_t lb_on
 *
 * @return Zero on success, negative on failure
 */
static int bdk_tns_config_sched_and_cutthru(bdk_node_t node, uint8_t x2p_thresh, uint8_t p2x_thresh, uint8_t lb_thresh,
                                            uint8_t drop_req_thresh, uint8_t lb_credits, uint8_t nic_on, uint8_t lmac_on,
                                            uint8_t lb_on)
{
    bdk_tns_tdma_nb_dbg_config1_t tdma_nb_dbg_config1;

    /* Enable Scheduling thresholds */
    tdma_nb_dbg_config1.u = 0ULL;

    /*
     * Both NIC interfaces have a FIFO for receiving tokens from the TxQ HW block.
     * Each FIFO can store 8 tokens, set the number of tokens at which the port
     * available signal to TxQ is de-asserted. (NB: This includes inflight tokens).
     */
    if (x2p_thresh > 8)
    {
        bdk_warn("bdk_tns_config_sched_and_cutthru: X2P FIFO size exceeded!\n");
        return -1;
    }
    else
    {
        tdma_nb_dbg_config1.s.x2p_tkn_sch_thresh = x2p_thresh;
    }

    /*
     * The internal loopback has a FIFO for receiving tokens from the TxQ HW block.
     * The FIFO can store 8 tokens, set the number of tokens at which the port
     * available signal to TxQ is de-asserted. (NB: Include inflight tokens).
     */
    if (lb_thresh > 8)
    {
        bdk_warn("bdk_tns_config_sched_and_cutthru: Loopback FIFO size exceeded!\n");
        return -1;
    }
    else
    {
        tdma_nb_dbg_config1.s.lb_tkn_sch_thresh = lb_thresh;
    }

    /*
     * Each BGx ports has a FIFO for receiving tokens from the ports's per-
     * priority Token FIFOs.  The FIFO can store 8 tokens, set the number of
     * tokens at which the FIFO will stop pulling tokens from the per-
     * priority Token FIFOs.
     */
    if (p2x_thresh > 8)
    {
        bdk_warn("bdk_tns_config_sched_and_cutthru: P2X FIFO size exceeded!\n");
        return -1;
    }
    else
    {
        tdma_nb_dbg_config1.s.p2x_tkn_sch_thresh = p2x_thresh;
    }

    /*
     * Requests to drop packets from the TxQ.  Arriving requests can take one
     * of two paths:
     *
     *   1) If the packet is a single-copy packet, the packet is pushed to a
     *      16-entry FIFO in the Link List walker logic.
     *   2) If the packet is a multiple-copy packet, the packet is pushed to
     *      a 16-entry FIFO in the Page Reference Count logic.
     * Set the level at which either of these FIFOs will assert flow control
     * to TxQ to prevent additional dropped messages from arriving.
     */
    if (drop_req_thresh > 16)
    {
        bdk_warn("bdk_tns_config_sched_and_cutthru: TxQ Drop Request FIFO size exceeded!\n");
        return -1;
    }
    else
    {
        tdma_nb_dbg_config1.s.txq_drop_req_thresh = drop_req_thresh;
    }

    /*
     * The flow of data from TDMA to RDMA along the internal loopback path is
     * metered by credits.  Each credit represents the transfer of a 32-byte
     * flit.  A maximum of 16 credits is allowed.  A minimum of 2 credits is
     * required for proper operation.
     */
    if ((lb_credits > 16) || (lb_credits < 2))
    {
        bdk_warn("bdk_tns_config_sched_and_cutthru: Loopback credits must 2 <= c <= 16\n");
        return -1;
    }
    else
    {
        tdma_nb_dbg_config1.s.lb_init_cdts = lb_credits;
    }
    /* Enable cut-thru towards NIC and LMAC */
    tdma_nb_dbg_config1.s.nic_cutthru_en = !!nic_on;
    tdma_nb_dbg_config1.s.lmac_cutthru_en = !!lmac_on;
    tdma_nb_dbg_config1.s.lb_cutthru_en = !!lb_on;

    BDK_CSR_WRITE(node, BDK_TNS_TDMA_NB_DBG_CONFIG1, tdma_nb_dbg_config1.u);
    /* bdk_wait_usec(10) */

    return 0;
}

/**
 * Designate the number of bytes which are considered part of the packet
 * header and will be extracted for processing by TNS.  Bytes received
 * after the header are considered part of the packet body.  Timestamp
 * bytes received from LMAC (if enabled) are not counted against the
 * header size.  Size are enumberated by TNS_RDMA_HDR_SZ_E.
 *
 * @param bdk_node_t node
 * @param tns_rdma_hdr_sz_e size
 *
 * @return Zero on success, negative on failure.
 */
static int bdk_tns_config_header_size(bdk_node_t node, uint8_t size)
{
    bdk_tns_rdma_nb_hdr_sz_cfg_t rdma_nb_hdr_sz_cfg;

    if (size > BDK_TNS_RDMA_HDR_SZ_E_BYTES_256)
    {
        bdk_warn("bdk_tns_config_header_size: Illegal Header size was specified\n");
        return -1;
    }

    rdma_nb_hdr_sz_cfg.u = 0ULL;
    rdma_nb_hdr_sz_cfg.s.lmac0 = size;
    rdma_nb_hdr_sz_cfg.s.lmac1 = size;
    rdma_nb_hdr_sz_cfg.s.lmac2 = size;
    rdma_nb_hdr_sz_cfg.s.lmac3 = size;
    rdma_nb_hdr_sz_cfg.s.lmac4 = size;
    rdma_nb_hdr_sz_cfg.s.lmac5 = size;
    rdma_nb_hdr_sz_cfg.s.lmac6 = size;
    rdma_nb_hdr_sz_cfg.s.lmac7 = size;
    rdma_nb_hdr_sz_cfg.s.nici0 = size;
    rdma_nb_hdr_sz_cfg.s.nici1 = size;
    rdma_nb_hdr_sz_cfg.s.lb = size;
    BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_HDR_SZ_CFG, rdma_nb_hdr_sz_cfg.u);
    /* bdk_wait_usec(10) */

    return 0;
}

/**
 * Initialize the DataPath Port Lookup tables.  Set each entry of these
 * tables to all ones.  Currently all ones are illegal ports for TNS.
 *
 * @param bdk_node_t node
 *
 * @return Nothing
 */
static void bdk_tns_init_pluts(bdk_node_t node)
{
    int i;
    bdk_tns_rdma_nb_lmac_plutx_t lmac_plut;
    bdk_tns_rdma_nb_nic_plutx_t nic_plut;
    bdk_tns_rdma_nb_loopback_plut_t lb_plut;
    bdk_tns_rdma_nb_lp_plutx_t fwd_plut;

    /* Initialize the LMAC PLUT Table */
    for (i = 0; i < TNS_MAX_LMAC_PLUT_ENTRIES; i++)
    {
        lmac_plut.u = 0ULL;
        lmac_plut.s.logical_port = TNS_LMAC_PLUT_ILLEGAL;
        BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_LMAC_PLUTX(i), lmac_plut.u);
        /* bdk_wait_usec(10) */
    }

    /* Initialize the NIC PLUT Table */
    for (i = 0; i < TNS_MAX_NIC_PLUT_ENTRIES; i++)
    {
        nic_plut.u = 0ULL;
        nic_plut.s.logical_port = TNS_NIC_PLUT_ILLEGAL;
        BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_NIC_PLUTX(i), nic_plut.u);
        /* bdk_wait_usec(10) */
    }

    /* Initialize the Forwarding PLUT Table */

    for (i = 0; i < TNS_MAX_FWD_PLUT_ENTRIES; i++)
    {
        fwd_plut.u = 0ULL;
        fwd_plut.s.physical_port = TNS_FWD_PLUT_ILLEGAL;
        BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_LP_PLUTX(i), fwd_plut.u);
        /* bdk_wait_usec(10) */
    }

    /* Initialize the Loopback PLUT Table */
    lb_plut.u = 0ULL;
    lb_plut.s.logical_port = TNS_LB_PLUT_ILLEGAL;
    BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_LOOPBACK_PLUT, lb_plut.u);
    /* bdk_wait_usec(10) */
}

/**
 * Initialize the TNS block to handle packet processing (NON-BYPASS) mode.
 * TNS at power-up will be in BYPASS mode where packets from the vNIC pipes
 * to the BGx ports will be direct.  This is normally called automatically
 * in bdk-init-main.c.
 *
 * @param node Node to initialize
 *
 * @return Zero on success, negative on failure
 */
int bdk_tns_initialize(bdk_node_t node)
{
    /* TNS is only allowed on CN88XX with the normal package (not CN86XX) */
    if (!CAVIUM_IS_MODEL(CAVIUM_CN88XX) || cavium_is_altpkg(CAVIUM_CN88XX))
        return -1;
    int i;

    /* Receive DMA registers (BYPASS MODE) */
    bdk_tns_rdma_config_t rdma_config;
    bdk_tns_rdma_hdr_ts_cfg_t rdma_hdr_ts_cfg;

    /* Receive DMA registers (NON-BYPASS MODE) */
    bdk_tns_rdma_nb_path_enable_t rdma_nb_path_enable;
    bdk_tns_rdma_nb_config_t rdma_nb_config;
    bdk_tns_rdma_nb_lmacx_rpkt_sz_t rdma_lmac_rpkt_sz;
    bdk_tns_rdma_nb_nicix_rpkt_sz_t rdma_nb_nic_rpkt_sz;
    bdk_tns_rdma_nb_dbg_config_t rdma_nb_dbg_config;

    /* Transmit DMA registers (BYPASS MODE) */
    bdk_tns_tdma_cap_t tdma_cap;
    bdk_tns_tdma_config_t tdma_config;
    bdk_tns_tdma_reset_ctl_t tdma_reset_ctl;
    bdk_tns_tdma_lmacx_config_t tdma_lmac_cfg;

    /* Transmit DMA registers (NON-BYPASS MODE) */
    bdk_tns_tdma_nb_config1_t tdma_nb_config1;
    bdk_tns_tdma_nb_status_t tdma_nb_status;

    /* Only valid for the HW or HW emulator, ASIM doesn't support TNS */
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        tns_enabled = 0;
        return -1;
    }

    /* Check if TNS is available */
    tdma_cap.u = BDK_CSR_READ(node, BDK_TNS_TDMA_CAP);
    if (!tdma_cap.s.switch_capable)
    {
        bdk_warn("TNS is not available!\n");
        return -1; /* TNS is not available */
    }
    else
    {
        tns_enabled = tdma_cap.s.switch_capable;
    }

    /* TNS non-bypass initialization - Taken from Section 6.2.1.2 TNS Data Path RTL
       Block Technical Specification. */

    /* 1. Verify no BIST errors */
    bdk_tns_check_bist(node);

    /* (not documented) Disable backpressure */
    rdma_config.u = 0ULL;
    BDK_CSR_WRITE(node, BDK_TNS_RDMA_CONFIG, rdma_config.u);
    bdk_wait_usec(10);

    /* (Mentioned in 6.2.1) Configure each LMAC with 512 credits in BYPASS mode */
    for (i = TNS_MIN_LMAC; i < (TNS_MIN_LMAC + TNS_MAX_LMACS); i++) {
        tdma_lmac_cfg.u = 0ULL;
        tdma_lmac_cfg.s.fifo_cdts = 0x200;
        BDK_CSR_WRITE(node, BDK_TNS_TDMA_LMACX_CONFIG(i), tdma_lmac_cfg.u);
        bdk_wait_usec(10);
    }

    /* 2. Enable the TNS Clocks and BYPASS mode */
    tdma_config.u = BDK_CSR_READ(node, BDK_TNS_TDMA_CONFIG);
    tdma_config.s.bypass0_ena = 1;
    tdma_config.s.bypass1_ena = 1;
    tdma_config.s.clk_2x_ena = 1;
    tdma_config.s.clk_ena = 1;
    BDK_CSR_WRITE(node, BDK_TNS_TDMA_CONFIG, tdma_config.u);

    /* 3. Enable CSR access (this allows us to talk to the rest of the TNS HW) */
    tdma_config.u = BDK_CSR_READ(node, BDK_TNS_TDMA_CONFIG);
    tdma_config.s.csr_access_ena = 1;
    BDK_CSR_WRITE(node, BDK_TNS_TDMA_CONFIG, tdma_config.u);

    /* 4. Clear TNS_TDMA_RESET_CTL */
    tdma_reset_ctl.u = 0ULL;
    BDK_CSR_WRITE(node, BDK_TNS_TDMA_RESET_CTL, tdma_reset_ctl.u);

    /* 5. Assume no timestamps at this time for packets arriving from LMAC */
    rdma_hdr_ts_cfg.u = 0ULL;
    BDK_CSR_WRITE(node, BDK_TNS_RDMA_HDR_TS_CFG, rdma_hdr_ts_cfg.u);

    /* 6 Configure PM_DEPTH, NICI1_PKND, NICI0_PKND, TXQ QMAP, TXQ EQ
         PM_DEPTH = 0 (Use all of packet memory)
         NICI1_PKND = 0
         NICI0_PKND = 0
         TXQ QMAP = 0xffff (all available ports)
         TXQ EQ = 0xffff (all available ports) */
    tdma_nb_config1.u = 0ULL;
    tdma_nb_config1.s.txq_eq_link_up = 0xffff;
    tdma_nb_config1.s.txq_qmap_link_up = 0xffff;
    BDK_CSR_WRITE(node, BDK_TNS_TDMA_NB_CONFIG1, tdma_nb_config1.u);
    bdk_wait_usec(10);

    /* 7. Enable backpressure on all ports for NON-BYPASS mode and
          disable LMACs, NICs and Loopback */
    rdma_nb_path_enable.u = 0ULL;
    rdma_nb_path_enable.s.bgx0_bp = 1;
    rdma_nb_path_enable.s.bgx1_bp = 1;
    rdma_nb_path_enable.s.nici0_bp = 1;
    rdma_nb_path_enable.s.nici1_bp = 1;
    BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_PATH_ENABLE, rdma_nb_path_enable.u);
    bdk_wait_usec(10);

    /* 8. Run auto-initialization */
    tdma_nb_config1.u = BDK_CSR_READ(node, BDK_TNS_TDMA_NB_CONFIG1);
    tdma_nb_config1.s.auto_init = 1;
    BDK_CSR_WRITE(node, BDK_TNS_TDMA_NB_CONFIG1, tdma_nb_config1.u);

    /* 9. Wait for auto-initialization to complete */
    tdma_nb_status.u = BDK_CSR_READ(node, BDK_TNS_TDMA_NB_STATUS);
    while(tdma_nb_status.s.init_done != 1)
    {
        bdk_wait_usec(10);
        tdma_nb_status.u = BDK_CSR_READ(node, BDK_TNS_TDMA_NB_STATUS);
        /* TODO - Add a limit and fail if passed */
    }

    /* 10. Enable DataPath to receive packets from the physical ports */
    rdma_nb_path_enable.u = BDK_CSR_READ(node, BDK_TNS_RDMA_NB_PATH_ENABLE);
    rdma_nb_path_enable.s.lmac = 0xff;
    rdma_nb_path_enable.s.nici0 = 1;
    rdma_nb_path_enable.s.nici1 = 1;
    rdma_nb_path_enable.s.loopback = 1;
    BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_PATH_ENABLE, rdma_nb_path_enable.u);
    bdk_wait_usec(10);

    /* 11. Enable TNS switch for receiving packets */
    rdma_nb_config.u = 0ULL;
    rdma_nb_config.s.master_en = 1;
    BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_CONFIG, rdma_nb_config.u);
    bdk_wait_usec(10);

    /* 12. Enable TNS switch for sending packets allows packets to be stored in packet memory */
    tdma_nb_config1.u = BDK_CSR_READ(node, BDK_TNS_TDMA_NB_CONFIG1);
    tdma_nb_config1.s.master_en = 1;
    BDK_CSR_WRITE(node, BDK_TNS_TDMA_NB_CONFIG1, tdma_nb_config1.u);
    bdk_wait_usec(10);

    /* 13-14 are done outside of TNS setup */

    /* 15-18. Initialize the PLUT table entries to all-ones */
    bdk_tns_init_pluts(node);

    /* 19. Set the number of bytes which are considered part of the the packet
           header and will be extracted and passed on to the SDE for processing. */
    if (bdk_tns_config_header_size(node, BDK_TNS_RDMA_HDR_SZ_E_BYTES_64) < 0)
    {
        return -1;
    }

    /* 20. Clear (Disable) runt packet filtering for packets from LMAC */
    for (i = TNS_MIN_LMAC; i < (TNS_MIN_LMAC + TNS_MAX_LMACS); i++)
    {
        rdma_lmac_rpkt_sz.u = 0ULL;
        BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_LMACX_RPKT_SZ(i), rdma_lmac_rpkt_sz.u);
    }
    bdk_wait_usec(10);

    /* 21. Clear (Disable) runt packet filtering for packets from NIC */
    for (i = TNS_MIN_NIC; i < (TNS_MIN_NIC + TNS_MAX_NICS); i++)
    {
        rdma_nb_nic_rpkt_sz.u = 0ULL;
        BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_NICIX_RPKT_SZ((i-TNS_MIN_NIC)), rdma_nb_nic_rpkt_sz.u);
    }
    bdk_wait_usec(10);

    /* Set scheduling thresholds */
    if (bdk_tns_config_sched_and_cutthru(node, 0x04, 0x05, 0x04, 0x0c, 0x10, 1, 1, 0) < 0)
    {
        return -1;
    }

    /* Enable SDE receipt of packet errors for a single-page packet */
    rdma_nb_dbg_config.u = 0ULL;
    rdma_nb_dbg_config.s.body_ptr_error_value = 0x3ff; /* Must match SDE value */

    /* Set the level at which the SDMA will assert backpressure to the SDE */
    rdma_nb_dbg_config.s.sdma_fifo_bp = 0x08;
    BDK_CSR_WRITE(node, BDK_TNS_RDMA_NB_DBG_CONFIG, rdma_nb_dbg_config.u);
    bdk_wait_usec(10);

    /* Enable backpressure to physical ports */
    rdma_config.u = 0ULL;
#if 0 /* These bitfields are 2 bits each. */
    rdma_config.s.nici_bp_enable = 1;
    rdma_config.s.lmac_bp_enable = 1;
#else
    rdma_config.s.nici_bp_enable = 3;
    rdma_config.s.lmac_bp_enable = 3;
#endif
    BDK_CSR_WRITE(node, BDK_TNS_RDMA_CONFIG, rdma_config.u);
    bdk_wait_usec(10);

    /* 31. Disable Bypass, this effectively puts TNS into the traffic path */
#if 0 /* Skip this for now.  Have the user do it manually in traffic-gen later. */
    tdma_config.u = BDK_CSR_READ(node, BDK_TNS_TDMA_CONFIG);
    tdma_config.s.bypass0_ena = 0;
    tdma_config.s.bypass1_ena = 0;
    BDK_CSR_WRITE(node, BDK_TNS_TDMA_CONFIG, tdma_config.u);
    bdk_wait_usec(10);
#endif

    return 0;
}

/**
 * Disable TNS from processing packets.  After this, TNS must be fully
 * initialized.  The NIC and BGX blocks must already be stopped before
 * calling this function.
 *
 * Nota Bene: In CN88XX_PASS_1 there is a bug that prevents TNS DataPath
 *            from draining packets.  So ensure that NIC and BGX have
 *            also drained their packet queues.
 *
 * @param node
 *
 * @return Zero on success, negative on failure
 */
int bdk_tns_shutdown(bdk_node_t node)
{
    if (tns_enabled)
    {
        /* 1. Stop packet traffic from entering TNS via NIC and BGX, this must
              occur before calling this function. */
        /* 2. Drain packets from the TNS. */
        if (!CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
        {
            /* TBD */
        }

        /* 3. Disable backpressure for BGX and NIC */
        BDK_CSR_MODIFY(c, node, BDK_TNS_RDMA_NB_PATH_ENABLE,
                       c.s.nici1_bp = 0;
                       c.s.nici0_bp = 0;
                       c.s.bgx1_bp = 0;
                       c.s.bgx0_bp = 0);
        bdk_wait_usec(10);

        /* 4. Enable Bypass mode */
        BDK_CSR_MODIFY(c, node, BDK_TNS_TDMA_CONFIG,
                       c.s.bypass1_ena = 1;
                       c.s.bypass0_ena = 1);
        bdk_wait_usec(10);

        /* 5. Disable TNS from transmitting packets */
        BDK_CSR_MODIFY(c, node, BDK_TNS_TDMA_NB_CONFIG1,
                       c.s.master_en = 0);

        /* 6. Disable TNS from receiving packets */
        BDK_CSR_MODIFY(c, node, BDK_TNS_RDMA_NB_CONFIG,
                       c.s.master_en = 0);

        /* 7. Force a reset of all TNS HW blocks */
        BDK_CSR_MODIFY(c, node, BDK_TNS_TDMA_RESET_CTL,
                       c.u = 0x000000FFFFFFFFFFULL);

        /* 8. Disable CSR access */
        BDK_CSR_MODIFY(c, node, BDK_TNS_TDMA_CONFIG,
                       c.s.csr_access_ena = 0);

        /* 9. Disable CLK2 and CLK */
        BDK_CSR_MODIFY(c, node, BDK_TNS_TDMA_CONFIG,
                       c.s.clk_2x_ena = 0;
                       c.s.clk_ena = 0);
    }

    return 0;
}


typedef struct _tns_datapath_config {
    uint64_t addr;
    uint64_t data;
} tns_datapath_config_t;

#define SST_CONFIG_PLAYBACK // This uses a somewhat compressed format instead of the normal "trace" format
#ifdef SST_CONFIG_PLAYBACK
typedef union _tns_sst_config {
    uint64_t data;
    struct {
#if __BYTE_ORDER == __BIG_ENDIAN
        uint64_t powerof2stride              : 1;
        uint64_t run                         : 11;
        uint64_t reserved                    : 14;
        uint64_t req_type                    : 2;
        uint64_t word_cnt                    : 4;
        uint64_t byte_addr                   : 32;
#else
        uint64_t byte_addr                   : 32;
        uint64_t word_cnt                    : 4;
        uint64_t req_type                    : 2;
        uint64_t reserved                    : 14;
        uint64_t run                         : 11;
        uint64_t powerof2stride              : 1;
#endif
    } cmd;
    struct {
#if __BYTE_ORDER == __BIG_ENDIAN
        uint64_t do_not_copy                 : 26;
        uint64_t do_copy                     : 38;
#else
        uint64_t do_copy                     : 38;
        uint64_t do_not_copy                 : 26;
#endif
    } copy;
    struct {
#if __BYTE_ORDER == __BIG_ENDIAN
        uint64_t magic                       : 48;
        uint64_t major_version_BCD           : 8;
        uint64_t minor_version_BCD           : 8;
#else
        uint64_t minor_version_BCD           : 8;
        uint64_t major_version_BCD           : 8;
        uint64_t magic                       : 48;
#endif
    } header;
} tns_sst_config_union_t;
typedef uint64_t tns_sst_config_t;

#else
typedef struct _tns_sst_config {
    uint64_t addr;
    uint64_t data;
} tns_sst_config_t;
#endif

typedef struct _tns_profile {
    const char *name;
    const tns_sst_config_t *tns_sst_config;
    int tns_sst_config_size;
    const tns_datapath_config_t *tns_datapath_config;
    int tns_datapath_config_size;
} tns_profile_t;

#define TNS_CONFIG_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

/*
 * This array contains the TNS Datapath HW configuration in a simple run-length format.
 * The Search Engine, SDE and TxQ HW configuration is done separately.
 */
static const tns_datapath_config_t tns_datapath_config_passthru[] = {
#include "bdk-tns-datapath-config-passthru.h"
};

static const tns_datapath_config_t tns_datapath_config_bgxloopback[] = {
#include "bdk-tns-datapath-config-bgxloopback.h"
};

/*
 * This array contains the TNS Search Engine, SDE and TxQ HW configuration in
 * a packed format.  The DataPath HW configuration is done separately.
 */
static const tns_sst_config_t tns_sst_config_passthru[] = {
#include "bdk-tns-sst-config-passthru.h"
};

static const tns_sst_config_t tns_sst_config_bgxloopback[] = {
#include "bdk-tns-sst-config-bgxloopback.h"
};

static const tns_profile_t tns_profiles[] = {
    {"passthru", tns_sst_config_passthru, TNS_CONFIG_SIZE(tns_sst_config_passthru),
        tns_datapath_config_passthru, TNS_CONFIG_SIZE(tns_datapath_config_passthru)},
    {"bgxloopback", tns_sst_config_bgxloopback, TNS_CONFIG_SIZE(tns_sst_config_bgxloopback),
        tns_datapath_config_bgxloopback, TNS_CONFIG_SIZE(tns_datapath_config_bgxloopback)},
    {NULL, NULL, 0, NULL, 0} /* final entry */
};

#define TNS_WRITE_CSR(node, a, d) bdk_csr_write(node, BDK_CSR_TYPE_NCB, 0, sizeof(uint64_t), a, d)

static int tns_configure_datapath(bdk_node_t node, const tns_datapath_config_t *datapath_config, int ndatapath)
{
    int i;
    int nregs = 0;

    for (i = 0; i < ndatapath; i++)
    {
        uint64_t addr = datapath_config[i].addr & 0x000fffffffffffff;
        int remaining = (int)(datapath_config[i].addr >> 56) & 0xff;
        int increment = (int)(datapath_config[i].addr >> 52) & 0x0f;
        uint64_t data = datapath_config[i].data;

        do {
            TNS_WRITE_CSR(node, addr, data);
            bdk_wait_usec(10);
            nregs++;
//printf(" { %016llx, %016llx },\n", addr, data);
            addr += 0x10;
            data += increment;
        } while (remaining-- > 0);
    }

    printf("Updated TNS DataPath (%d registers updated from %d bytes of configuration)\n",
        nregs, ndatapath * (int)sizeof(datapath_config[0]));

    return 0;
}

#ifdef SST_CONFIG_PLAYBACK
static int tns_configure_sst(bdk_node_t node, const tns_sst_config_t *sst_config, int ntnscfg)
{
    int i;
    int niregs = 0;

    tns_sst_config_union_t header = (tns_sst_config_union_t)(sst_config[0]);

    if ((ntnscfg < 1) || (header.header.magic != 0x0000abac0000)) {
        bdk_error("Error in playback config:  could not find magic number in the header.\n");
        return -1;
    }

    /*
     * To configure SE/SDE/TxQ HW blocks inside TNS, we use the indirect
     * method (TNS_TDMA_SST_ACC_CMD) to load since many of those registers
     * exceed 64-bits in width.  This means after every TNS_TDMA_SST_ACC_CMD
     * we need to read TNS_TDMA_SST_ACC_STAT until CMD_DONE == 1.
     */
    for (i = 1; i < ntnscfg; i++)
    {
        tns_sst_config_union_t cmd = (tns_sst_config_union_t)(sst_config[i]);
        bdk_tns_tdma_sst_acc_stat_t cmdstat;
        int remaining = cmd.cmd.run;
        int word_cnt = cmd.cmd.word_cnt;
        int size = (word_cnt + 1) / 2;
        uint64_t data[16];
        uint64_t stride = word_cnt;
        uint64_t acc_cmd = cmd.copy.do_copy;

        if (word_cnt == 0) {
            word_cnt = 16;
            stride = 16;
            size = 8;
        }
        else {
            if (cmd.cmd.powerof2stride) { // make stride next power of 2
                while ((stride & (stride - 1)) != 0) stride++;
            }
        }

        stride *= 4; // convert stride from 32-bit words to bytes

        while (size > 0) { // extract (big endian) data from the config into the data array
            size--;
            data[size] = sst_config[++i];
            if (i >= ntnscfg) {
                bdk_error("Error in playback config, %d >= %d\n", i, ntnscfg);
                return -1;
            }
        }

        do {
            /* write the data */
            int w;
            /* could move this outside of the loop, but trace would be confusing and patches will need it */
            for (w = (word_cnt + 1) / 2; w >= 0; w--)
            {
                TNS_WRITE_CSR(node, BDK_TNS_TDMA_SST_ACC_WDATX(w), data[w]);
            }

            /* write the command */
            TNS_WRITE_CSR(node, BDK_TNS_TDMA_SST_ACC_CMD, acc_cmd);
            // printf("%016lx\n", acc_cmd);

            /* check for completion */
            do {
                cmdstat.u = BDK_CSR_READ(node, BDK_TNS_TDMA_SST_ACC_STAT);

                if (cmdstat.s.error)
                {
                    bdk_error("Error issuing ACC Write command: 0x%016lx\n", acc_cmd);
                    return -1;
                }
            } while (cmdstat.s.cmd_done != 1);

            /* update the address */
            acc_cmd += stride;

            niregs++;

        } while (remaining-- > 0);
    }

    printf("Wrote TNS SST (Search, SDE, and TxQ) configuration.\n");
    printf(" -- %d indirect SST registers written from %d v%x.%x config bytes.\n",
        niregs, ntnscfg * (int)sizeof(sst_config[0]),
        header.header.major_version_BCD, header.header.minor_version_BCD);

    return 0;
}
#else
static int tns_configure_sst(bdk_node_t node, const tns_sst_config_t *sst_config, int ntnscfg)
{
    uint64_t tns_sst_acc = BDK_TNS_TDMA_SST_ACC_CMD;
    int i;
    int niregs = 0;

    /*
     * To configure SE/SDE/TxQ HW blocks inside TNS, we use the indirect
     * method (TNS_TDMA_SST_ACC_CMD) to load since many of those registers
     * exceed 64-bits in width.  This means after every TNS_TDMA_SST_ACC_CMD
     * we need to read TNS_TDMA_SST_ACC_STAT until CMD_DONE == 1.
     */
    for (i = 0; i < ntnscfg; i++)
    {
        TNS_WRITE_CSR(node, sst_config[i].addr, sst_config[i].data);
        if (sst_config[i].addr == tns_sst_acc)
        {
            bdk_tns_tdma_sst_acc_stat_t cmdstat;

            do {
                cmdstat.u = BDK_CSR_READ(node, BDK_TNS_TDMA_SST_ACC_STAT);

                if (cmdstat.s.error)
                {
                    bdk_error("Error issuing ACC Write command: 0x%016lx\n", sst_config[i].data);
                    return -1;
                }
            } while (cmdstat.s.cmd_done != 1);
            niregs++;
        }
    }

    printf("Wrote TNS SST (Search, SDE, and TxQ) configuration.\n");
    printf(" -- %d indirect SST registers written from %d config bytes.\n",
        niregs, ntnscfg * (int)sizeof(sst_config[0]));

    return 0;
}
#endif

#undef TNS_WRITE_CSR

int bdk_tns_profile(bdk_node_t node, const char *name)
{
    const tns_profile_t *profile = tns_profiles;

    while (profile->name != NULL)
    {
        if (strcasecmp(profile->name, name) == 0)
        {
            break;
        }
        profile++;
    }

    if (profile->name == NULL) {
        bdk_error("Could not find profile '%s'\n", name);
        return -1;
    }

    tns_configure_datapath(node, profile->tns_datapath_config, profile->tns_datapath_config_size);
    tns_configure_sst(node, profile->tns_sst_config, profile->tns_sst_config_size);

    return 0;
}

/* later we may want to allow profile name to be passed from lua directly */
int bdk_tns_profile_passthru(bdk_node_t node)
{
    return bdk_tns_profile(node, "passthru");
}

int bdk_tns_profile_bgxloopback(bdk_node_t node)
{
    return bdk_tns_profile(node, "bgxloopback");
}
