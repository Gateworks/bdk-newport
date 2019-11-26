/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-nix.h"
#include "libbdk-arch/bdk-csrs-rvu.h"
#include "libbdk-arch/bdk-csrs-sso.h"
#include "libbdk-arch/bdk-csrs-ssow.h"

/**
 * Function called during bdk_thread_yield() to process work while we're idle
 */
static void bdk_sso_process_work_cn9xxx(void)
{
    bdk_node_t node = bdk_numa_local();
    /* Build pointers to the SSOW HWS0 */
    /* SSOW is in RVU BAR2 address range. We need to insert the
       core number into the LF_SLOT. RVU sucks */
    uint64_t gws_tag_rvu_slot = bdk_numa_get_address(node, BDK_SSOW_LF_GWS_TAG);
    uint64_t gws_wqp_rvu_slot = bdk_numa_get_address(node, BDK_SSOW_LF_GWS_WQP);
    uint64_t getwork_rvu_slot = bdk_numa_get_address(node, BDK_SSOW_LF_GWS_OP_GET_WORK);

    while (true)
    {
        /* Select the HWS for this core. Core might change between
           loops due to calls inside this loop */
        int hws = bdk_get_core_num();
        gws_tag_rvu_slot = bdk_insert(gws_tag_rvu_slot, hws, 12, 8);
        gws_wqp_rvu_slot = bdk_insert(gws_wqp_rvu_slot, hws, 12, 8);
        getwork_rvu_slot = bdk_insert(getwork_rvu_slot, hws, 12, 8);

        /* Build volatile pointers to each HWS item */
        volatile bdk_ssow_lf_gws_tag_t *gws_tag_ptr = bdk_phys_to_ptr(gws_tag_rvu_slot);
        volatile bdk_ssow_lf_gws_wqp_t *gws_wqp_ptr = bdk_phys_to_ptr(gws_wqp_rvu_slot);
        volatile bdk_ssow_lf_gws_op_get_work_t *getwork_ptr = bdk_phys_to_ptr(getwork_rvu_slot);

        /* Check if work is pending */
        bdk_ssow_lf_gws_tag_t gws_tag = { .u = bdk_le64_to_cpu(gws_tag_ptr->u) };
        bdk_ssow_lf_gws_wqp_t gws_wqp = { .u = bdk_le64_to_cpu(gws_wqp_ptr->u) };
        if (gws_tag.s.pend_get_work)
            break;
        uint64_t work_address = gws_wqp.s.wqp;
        /* GET_WORK complete, ask for more */
        bdk_ssow_lf_gws_op_get_work_t get_work;
        get_work.u = 0;
        get_work.s.waitw = 1;
        getwork_ptr->u = bdk_cpu_to_le64(get_work.u);
        //BDK_TRACE(SSO, "Asking for more work\n");
        /* Check if we have anything */
        if (!work_address)
            break;
        BDK_TRACE(SSO, "Received work 0x%lx\n", work_address);
        const void *work = bdk_phys_to_ptr(work_address);
        union bdk_nix_wqe_hdr_s wqe = *(union bdk_nix_wqe_hdr_s *)work;
        const union bdk_nix_rx_parse_s *rx_parse = work + sizeof(union bdk_nix_wqe_hdr_s);
        int channel = rx_parse->s.chan;

#if __BYTE_ORDER == __BIG_ENDIAN
        wqe.u = bdk_le64_to_cpu(wqe.u);
        channel = bdk_le64_to_cpu(rx_parse->u[0]) & 0xfff;
#endif

        if (bdk_unlikely(!bdk_sso_map[wqe.s.node][channel]))
            bdk_error("Unable to find IF for packet to port %d\n", channel);

        BDK_TRACE(SSO, "Calling receive for wqe %p, channel 0x%x, rx_parse %p\n", work, channel, rx_parse);
        __bdk_nix_process_complete_rx(bdk_sso_map[wqe.s.node][channel], rx_parse);
    }
}

/**
 * Initialize the SSO
 *
 * @return Zero on success, negative on failure
 */
int bdk_sso_init_cn9xxx(bdk_node_t node)
{
    BDK_TRACE(SSO, "N%d: Starting SSO Init\n", node);
    /* Get SSO constants */
    BDK_CSR_INIT(sso_const, node, BDK_SSO_AF_CONST);
    BDK_CSR_INIT(sso_const1, node, BDK_SSO_AF_CONST1);

    /* Hardcode RVU selection to PF0 */
    union bdk_rvu_pf_func_s rvu_pf_func;
    rvu_pf_func.u = 0;
    rvu_pf_func.s.pf = 0;
    rvu_pf_func.s.func = 0;

    BDK_TRACE(SSO, "N%d: Setting up RVU for each group\n", node);
    /* Assign and enable the RVU access to SSO */
    for (int grp = 0; grp < sso_const.s.grp; grp++)
    {
        BDK_CSR_MODIFY(c, node, BDK_SSO_PRIV_LFX_HWGRP_CFG(grp),
            c.s.ena = 1;        /* Enable the SSOW LF */
            c.s.pf_func = rvu_pf_func.u; /* Which RVU to use */
            c.s.slot = grp);
    }

    BDK_TRACE(SSO, "N%d: 1:1 map SSOW to RVU\n", node);
    /* Assign and enable the RVU access to all SSOW */
    for (int hws = 0; hws < sso_const.s.hws; hws++)
    {
        BDK_CSR_MODIFY(c, node, BDK_SSOW_PRIV_LFX_HWS_CFG(hws),
            c.s.ena = 1;        /* Enable the SSOW LF */
            c.s.pf_func = rvu_pf_func.u; /* Which RVU to use */
            c.s.slot = hws);
    }

    /* Setup an FPA pool to store the SSO XAQ queues */
    /* Need three per group (1 XAQ, 2 prefetch), one per hardware work
       slot (HWS), plus some for memory spillage */
    const int MEM_SPILL = 1024; /* Number of WQE that can spill to DRAM */
    int num_blocks = sso_const.s.grp * 3;
    num_blocks += sso_const.s.hws;
    num_blocks += (MEM_SPILL + sso_const1.s.xae_waes-1) / sso_const1.s.xae_waes;
    BDK_TRACE(SSO, "N%d: Fill SSO pool\n", node);
    if (bdk_fpa_fill_pool(node, BDK_FPA_SSO_POOL, num_blocks))
        return -1;
    const int aura = BDK_FPA_SSO_POOL; /* Use 1:1 mapping aura */

    BDK_TRACE(SSO, "N%d: Setup XAQ\n", node);
    /* Set the NPA PF_FUNC to use for XAQ */
    for (int xaq = 0; xaq < sso_const.s.grp; xaq++)
    {
        BDK_CSR_MODIFY(c, node, BDK_SSO_AF_XAQX_GMCTL(xaq),
            c.s.pf_func = rvu_pf_func.u);
    }

    BDK_TRACE(SSO, "N%d: Setup group/qos queues\n", node);
    /* Initialize the group/qos queues */
    for (int grp = 0; grp < sso_const.s.grp; grp++)
    {
        /* Set the aura number */
        BDK_CSR_MODIFY(c, node, BDK_SSO_AF_HWGRPX_XAQ_AURA(grp),
            c.s.aura = aura);
        /* Setup how the SSO accesses memory */
        BDK_CSR_MODIFY(c, node, BDK_SSO_AF_HWGRPX_AW_CFG(grp),
            c.s.stt = 0; /* Store to LLC */
            c.s.ldt = 0; /* Load into LLC */
            c.s.ldwb = BDK_USE_DWB;
            c.s.rwen = 1);
    }

    /* Enable this LF to queue work */
    BDK_CSR_MODIFY(c, node, BDK_SSO_LF_GGRP_QCTL,
        c.s.ena = 1);

    BDK_TRACE(SSO, "N%d: Enable all HWS (Hardware Work Slots)\n", node);
    /* Enable all HWS (Hardware Work Slots) */
    for (int hws = 0; hws < sso_const.s.hws; hws++)
    {
        BDK_CSR_MODIFY(c, node, BDK_SSO_AF_HWSX_GMCTL(hws),
            c.s.alloc_we_ena = 1;
            c.s.gw_indx_ena = 1);
        /* Setup the group mask for hardware work slots (HWS) */
        for (int group_set = 0; group_set < 2; group_set++)
        {
            for (int bank = 0; bank < 4; bank++)
                BDK_CSR_WRITE(node, BDK_SSO_AF_HWSX_SX_GRPMSKX(hws, group_set, bank), -1);
        }
    }

    /* Set no-work timer, units of 1024 SCLK
       0=1024 2=2048 3=3072 ... */
    BDK_CSR_MODIFY(c, node, BDK_SSOW_LF_GWS_NW_TIM,
        c.s.nw_tim = 10);

    BDK_TRACE(SSO, "N%d: SSO Init complete\n", node);
    BDK_WMB;
    bdk_sso_process_work = bdk_sso_process_work_cn9xxx;
    BDK_WMB;
    return 0;
}

