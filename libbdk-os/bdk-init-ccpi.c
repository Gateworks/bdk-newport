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
#include <stdio.h>
#include <unistd.h>
#include "libbdk-arch/bdk-csrs-l2c.h"
#include "libbdk-arch/bdk-csrs-ocx.h"
#include "libbdk-arch/bdk-csrs-smmu.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(CCPI);

/* The functions in this file work with CCPI at the lane and link level. These
   initialize CCPI into a working link, but do not actually transition to
   multi-node. Only after these functions have brought CCPI into a work state
   can the node functions in bdk-init.c start using the other nodes */

#define MAX_LINKS 3
typedef struct
{
    bdk_ocx_com_node_t      node;                    /* Node ID at end of link */
    bdk_ocx_com_linkx_ctl_t ctl[MAX_LINKS];          /* Remote node link info */
    uint64_t                unique_value[MAX_LINKS]; /* Unique values received over links */
} lk_info_t;

/**
 * During OCX link enumeration, we need to write unique values to
 * OCX_TLKX_LNK_DATA so that we can determine which links connects
 * to which node. This function creates these unique values. When
 * making values for the local node, use local_link as -1.
 *
 * @param local_link The node where we write the value is connected to "local_link". If we're
 *                   working on the local node, use -1.
 * @param remote_link
 *                   Which link on the remote node is this value for (0-3)
 *
 * @return Unique value that can be sent using OCX_TLKX_LNK_DATA, then received with
 *         OCX_RLKX_LNK_DATA.
 */
static inline uint64_t ocx_unique_key(int local_link, int remote_link)
{
    uint64_t result = 0xabcdull << 32;
    result |= (local_link & 0xff) << 16;
    result |= remote_link & 0xff;
    return result;
}

/**
 * Return if the link at the suplied index points to a node that we've already
 * discovered. This happens if two links connect to the same node for more
 * bandwidth.
 *
 * @param unique_value
 *               Conenction data for finding nodes
 * @param index  Index into unique_value that we are seeing if its a duplicate
 *
 * @return Index of the duplicate or -1 if its not a duplicate
 */
static int ocx_duplicate_node(lk_info_t *lk_info, int index)
{
    for (int link = 0; link < index; link++)
    {
        if ((lk_info[link].unique_value[0] == lk_info[index].unique_value[0]) &&
            (lk_info[link].unique_value[1] == lk_info[index].unique_value[1]) &&
            (lk_info[link].unique_value[2] == lk_info[index].unique_value[2]))
            return link;
    }
    return -1;
}

/**
 * This function reads CSRs for a remote node before OCX is completely
 * setup. It should be used during node bringup, but not after L2 is aware of
 * the other nodes.
 *
 * @param node    Node ID to read from
 * @param address CSR address to read
 *
 * @return Value read
 */
static uint64_t ocx_pp_read(bdk_node_t node, uint64_t address)
{
    #define OCX_PP_TIMEOUT 0xffffffffffffffffull
    address = bdk_numa_get_address(node, address);

    if (node == bdk_numa_local())
    {
        return bdk_read64_uint64(address);
    }
    else
    {
        BDK_CSR_DEFINE(pp_cmd, BDK_OCX_PP_CMD);
        pp_cmd.u = 0;
        pp_cmd.s.ld_cmd = 3; /* 8 byte load */
        pp_cmd.s.ld_op = 1;
        pp_cmd.s.addr = address;
        BDK_CSR_WRITE(bdk_numa_local(), BDK_OCX_PP_RD_DATA, OCX_PP_TIMEOUT);
        BDK_CSR_WRITE(bdk_numa_local(), BDK_OCX_PP_CMD, pp_cmd.u);

        /* Wait for 1ms for read ot complete */
        if (BDK_CSR_WAIT_FOR_FIELD(bdk_numa_local(), BDK_OCX_PP_RD_DATA, data, !=, OCX_PP_TIMEOUT, 1000))
            return OCX_PP_TIMEOUT;
        return BDK_CSR_READ(bdk_numa_local(), BDK_OCX_PP_RD_DATA);
    }
}

/**
 * This function writes CSRs for a remote node before OCX is completely
 * setup. It should be used during node bringup, but not after L2 is aware of
 * the other nodes.
 *
 * @param node    Node ID to write to
 * @param address CSR address to write
 * @param data    Data to write
 */
static void ocx_pp_write(bdk_node_t node, uint64_t address, uint64_t data)
{
    address = bdk_numa_get_address(node, address);

    if (node == bdk_numa_local())
    {
        bdk_write64_uint64(address, data);
    }
    else
    {
        BDK_CSR_DEFINE(pp_cmd, BDK_OCX_PP_CMD);
        pp_cmd.u = 0;
        pp_cmd.s.wr_mask = 0xff;
        pp_cmd.s.addr = address;
        BDK_CSR_WRITE(bdk_numa_local(), BDK_OCX_PP_WR_DATA, data);
        BDK_CSR_WRITE(bdk_numa_local(), BDK_OCX_PP_CMD, pp_cmd.u);
    }
}

/**
 * The oct_init() function needs to check the status of a CCPI link quite often.
 * For a link to be good it must be valid, up, and not dropping data.
 *
 * @param linkx_ctl Status of link to check
 *
 * @return Non zero if link is good
 */
static inline int is_ccpi_link_good(bdk_ocx_com_linkx_ctl_t linkx_ctl)
{
    return linkx_ctl.s.valid && linkx_ctl.s.up && !linkx_ctl.s.drop;
}

/**
 * Workaround various errata with CCPI. Call before attempting to bringup an active
 * multi-node system. The CCPI links may be active before this call, but they
 * should be idle.
 *
 * @param node   Node to configure
 * @param gbaud  Baud rate of the CCPI link. This can't be read from the hardware because we
 *               might be in software mode, where the QLMs are not up yet.
 */
static void ccpi_errata(bdk_node_t node, uint64_t gbaud)
{
    const uint64_t rclk = bdk_clock_get_rate(node, BDK_CLOCK_RCLK);
    const uint64_t baud = gbaud * 1000000;

    for (int link = 0; link < MAX_LINKS; link++)
    {
        /* Errata: (OCX-22153) OCX data rate issues with slower rclks */
        /* TX_DAT_RATE=roundup((67*RCLK / GBAUD)*32) */
        uint64_t data_rate = 67 * rclk;
        data_rate *= 32;
        data_rate += baud - 1;
        data_rate /= baud;
        BDK_CSR_MODIFY(c, node, BDK_OCX_LNKX_CFG(link),
            c.s.data_rate = data_rate);

        if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_X))
        {
            /* Errata (OCX-22951) OCX AUTO_CLR of DROP fails to work on error */
            BDK_CSR_MODIFY(c, node, BDK_OCX_COM_LINKX_CTL(link),
                c.s.auto_clr = 0;
                c.s.drop = 0);
        }
    }

    /* Errata:(SMMU-22267) SMMU not propagating Global Sync completion. Write
       even on non pass 1.0 chips as the boot ROM is writing to this register */
    int force = CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS1_0);
    for (int smmu = 0; smmu < 4; smmu++)
        BDK_CSR_MODIFY(c, node, BDK_SMMUX_DIAG_CTL(smmu),
            c.s.force_clks_active = force);
}

/**
 * Report the OCI/CCPI lane status for all lanes
 *
 * @param node   Node to report for
 * @param show_message
 *               True if status should be displayed to the user
 *
 * @return Number of good lanes (0-24)
 */
static int ccpi_report_lane(bdk_node_t node, int show_message)
{
    int num_good = 0;
    if (show_message)
        printf("N%d.CCPI Lanes([] is good):", node);
    for (int lane=0; lane<24; lane++)
    {
        int ocx_qlm = lane / 4;
        BDK_CSR_INIT(ocx_qlmx_cfg, node, BDK_OCX_QLMX_CFG(ocx_qlm));
        int good = (ocx_qlmx_cfg.s.ser_lane_ready & (1 << (lane & 3))) != 0;
        num_good += good;
        if (show_message)
        {
            if (good)
                printf("[%d]", lane);
            else
                printf(" %d", lane);
        }
    }
    if (show_message)
        printf("\n");
    return num_good;
}

/**
 * After all links are up, this function figures out where they connect and assign
 * node numbers. After this function completes, everything is setup for multi-node
 * operation, but multi-node is still disabled.
 *
 * @param node   Node to setup, expected to be the local node. Only runs on the master node
 *
 * @return Zero on success, negative on failure
 */
static int ccpi_setup_nodes(bdk_node_t node)
{
    uint64_t node_exists = 1ull << node;

    /* Index MAX_LINKS is used for the local node */
    const int LOCAL_NODE = MAX_LINKS;
    lk_info_t lk_info[MAX_LINKS + 1];
    memset(lk_info, 0, sizeof(lk_info));

    for (int link=0; link<3; link++)
    {
        /* Make sure each link has a unique node ID */
        BDK_CSR_INIT(ocx_com_linkx_ctl, node, BDK_OCX_COM_LINKX_CTL(link));
        ocx_com_linkx_ctl.s.id = (node + link + 1) & 3;
        BDK_CSR_WRITE(node, BDK_OCX_COM_LINKX_CTL(link), ocx_com_linkx_ctl.u);
        lk_info[LOCAL_NODE].ctl[link] = ocx_com_linkx_ctl;
        if (is_ccpi_link_good(ocx_com_linkx_ctl))
            BDK_TRACE(CCPI, "N%d: Link %d is up,   temp node ID is %d\n", node, link, ocx_com_linkx_ctl.s.id);
        else
            BDK_TRACE(CCPI, "N%d: Link %d is down, temp node ID is %d\n", node, link, ocx_com_linkx_ctl.s.id);
    }

    /* Only one node should be up (the one I'm on). Set its ID to be fixed. As
       part of booting the BDK we've already added it to both the exists and
       running node masks */
    BDK_CSR_INIT(ocx_com_node, node, BDK_OCX_COM_NODE);
    if (ocx_com_node.s.fixed)
    {
        BDK_TRACE(CCPI, "Current node ID %d is already marked fixed\n", node);
    }
    else
    {
        BDK_TRACE(CCPI, "Marking the current node ID %d as fixed\n", node);
        BDK_CSR_MODIFY(c, node, BDK_OCX_COM_NODE,
            c.s.fixed = 1);
    }

    /* Write a unique value to OCX_TLKX_LNK_DATA for every possible link. This
        allows us to later figure out which link goes where. Also mark all
        link as unrecoverable so its state can't change later */
    BDK_TRACE(CCPI, "Loop through local links sending unique values over OCX_TLKX_LNK_DATA\n");
    for (int link = 0; link < MAX_LINKS; link++)
    {
        /* Skip invalid links */
        if (!is_ccpi_link_good(lk_info[LOCAL_NODE].ctl[link]))
        {
            BDK_TRACE(CCPI, "    Local link %d: Down, skipping\n", link);
            continue;
        }
        /* Write a unique value so we can see where this link connects to */
        uint64_t local_unique = ocx_unique_key(-1, link);
        BDK_CSR_WRITE(node, BDK_OCX_TLKX_LNK_DATA(link), local_unique);
        BDK_TRACE(CCPI, "    Local link %d: Write link data 0x%lx\n", link, local_unique);
        const int rid = lk_info[LOCAL_NODE].ctl[link].s.id;
        /* Loop through possible remote links */
        for (int rlink = 0; rlink < MAX_LINKS; rlink++)
        {
            bdk_ocx_com_linkx_ctl_t *lnk = &lk_info[link].ctl[rlink];
            /* Read the links state and make sure it doesn't auto recover from
               errors*/
            lnk->u = ocx_pp_read(rid, BDK_OCX_COM_LINKX_CTL(rlink));
            if (lnk->u == OCX_PP_TIMEOUT)
            {
                BDK_TRACE(CCPI, "        Remote link %d: Timeout, skipping\n", rlink);
                continue;
            }
            lnk->s.auto_clr = 0;
            ocx_pp_write(rid, BDK_OCX_COM_LINKX_CTL(rlink), lnk->u);
            /* Skip invalid links */
            if (!is_ccpi_link_good(*lnk))
            {
                BDK_TRACE(CCPI, "        Remote link %d: Down, skipping\n", rlink);
                continue;
            }
            /* Write a unique value so we can see where the remote link
               connects to */
            uint64_t remote_unique = ocx_unique_key(link, rlink);
            BDK_TRACE(CCPI, "        Remote link %d: Write link data 0x%lx\n", rlink, remote_unique);
            ocx_pp_write(rid, BDK_OCX_TLKX_LNK_DATA(rlink), remote_unique);
        }
    }

    BDK_TRACE(CCPI, "Reading link data for all links\n");
    for (int link = 0; link < MAX_LINKS; link++)
    {
        if (!is_ccpi_link_good(lk_info[LOCAL_NODE].ctl[link]))
            continue;
        lk_info[LOCAL_NODE].unique_value[link] = BDK_CSR_READ(node, BDK_OCX_RLKX_LNK_DATA(link));
        BDK_TRACE(CCPI, "    Local link %d: Read link data 0x%lx\n", link, lk_info[LOCAL_NODE].unique_value[link]);
        const int rid = lk_info[LOCAL_NODE].ctl[link].s.id;
        for (int rlink = 0; rlink < MAX_LINKS; rlink++)
        {
            lk_info[link].unique_value[rlink] = ocx_pp_read(rid, BDK_OCX_RLKX_LNK_DATA(rlink));
            BDK_TRACE(CCPI, "        Remote link %d: Read link data 0x%lx\n", rlink, lk_info[link].unique_value[rlink]);
            if (lk_info[link].unique_value[rlink] == OCX_PP_TIMEOUT)
            {
                BDK_TRACE(CCPI, "            Invalid link data, marking link invalid\n");
                lk_info[LOCAL_NODE].ctl[link].s.valid = 0;
                continue;
            }
        }
        lk_info[link].node.u = ocx_pp_read(rid, BDK_OCX_COM_NODE);
    }

    BDK_TRACE(CCPI, "Finding fixed node IDs\n");
    /* Loop through once reserving all fixed node IDs */
    for (int link = 0; link < MAX_LINKS; link++)
    {
        if (!is_ccpi_link_good(lk_info[LOCAL_NODE].ctl[link]))
            continue;
        if (ocx_duplicate_node(lk_info, link) != -1)
        {
            BDK_TRACE(CCPI, "    Local link %d: Duplicate node, skipping\n", link);
            continue;
        }
        if (lk_info[link].node.s.fixed)
        {
            int rid = lk_info[link].node.s.id;
            /* Mark fixed nodes as existing so we don't reuse their node ID */
            if (node_exists & (1ull << rid))
            {
                bdk_error("Fixed ID %d conflicts with existing node, not starting OCI\n", rid);
                return -1;
            }
            node_exists |= 1ull << rid;
            BDK_TRACE(CCPI, "    Local link %d: Fixed node ID %d\n", link, rid);
        }
    }

    BDK_TRACE(CCPI, "Assigning node IDs\n");
    /* Loop through again finding node IDs for unassigned nodes */
    for (int link = 0; link < MAX_LINKS; link++)
    {
        if (!is_ccpi_link_good(lk_info[LOCAL_NODE].ctl[link]))
            continue;
        int dup = ocx_duplicate_node(lk_info, link);
        if (dup != -1)
        {
            BDK_TRACE(CCPI, "    Local link %d: Duplicate node, skipping\n", link);
            lk_info[link].node = lk_info[dup].node;
            continue;
        }
        if (!lk_info[link].node.s.fixed)
        {
            /* Find a clear exists bit */
            bdk_node_t node;
            for (node = 0; node < BDK_NUMA_MAX_NODES; node++)
            {
                if (!(node_exists & (1ull << node)))
                    break;
            }
            if (node >= BDK_NUMA_MAX_NODES)
                bdk_fatal("Somehow we found more nodes than we support. Skipping new node");
            node_exists |= 1ull << node;
            lk_info[link].node.s.fixed = 1;
            lk_info[link].node.s.id = node;
            BDK_TRACE(CCPI, "    Local link %d: Assigned node ID %d\n", link, node);
        }
    }

    /* Find an unused node number. This will be used for links that are down */
    bdk_node_t unused_node;
    for (unused_node = 0; unused_node < BDK_NUMA_MAX_NODES; unused_node++)
    {
        if (!(node_exists & (1ull << unused_node)))
            break;
    }

    BDK_TRACE(CCPI, "Determining which node each link connects to\n");
    for (int link = 0; link < MAX_LINKS; link++)
    {
        if (!is_ccpi_link_good(lk_info[LOCAL_NODE].ctl[link]))
        {
            lk_info[link].node.s.id = unused_node;
            continue;
        }
        BDK_TRACE(CCPI, "    Local link %d: Searching remote links\n", link);
        for (int rlink = 0; rlink < MAX_LINKS; rlink++)
        {
            if (!is_ccpi_link_good(lk_info[link].ctl[rlink]))
            {
                lk_info[link].ctl[rlink].s.id = unused_node;
                continue;
            }
            uint64_t search = lk_info[link].unique_value[rlink] & 0x0fffffffffffffffull;
            //BDK_TRACE(CCPI, "        Remote link %d: Looking for 0x%lx\n", rlink, search);
            int found = 0;
            for (int ll = -1; ll < MAX_LINKS; ll++)
            {
                for (int rl = 0; rl < MAX_LINKS; rl++)
                {
                    uint64_t runique = ocx_unique_key(ll, rl);
                    //BDK_TRACE(CCPI, "        Checking [%d][%d] 0x%lx\n", ll, rl, runique);
                    if (search == runique)
                    {
                        int node2 = (ll==-1) ? node : lk_info[ll].node.s.id;
                        BDK_TRACE(CCPI, "        Node ID %d, link %d => Node ID %d, link %d\n",
                            lk_info[link].node.s.id, rlink, node2, rl);
                        lk_info[link].ctl[rlink].s.id = node2;
                        found = 1;
                    }
                }
            }
            if (!found)
            {
                BDK_TRACE(CCPI, "        Node ID %d, link %d => Unknown\n",
                    lk_info[link].node.s.id, rlink);
            }
        }
    }

    BDK_TRACE(CCPI, "Programming remote links and node IDs\n");
    for (int link = 0; link < MAX_LINKS; link++)
    {
        if (!is_ccpi_link_good(lk_info[LOCAL_NODE].ctl[link]))
            continue;
        if (ocx_duplicate_node(lk_info, link) != -1)
        {
            BDK_TRACE(CCPI, "    Local link %d: Duplicate node, skipping\n", link);
            continue;
        }
        BDK_TRACE(CCPI, "    Local link %d: Assign node ID %d\n", link, lk_info[link].node.s.id);
        const int rid = lk_info[LOCAL_NODE].ctl[link].s.id;
        ocx_pp_write(rid, BDK_OCX_COM_NODE, lk_info[link].node.u);
        for (int rlink = 0; rlink < MAX_LINKS; rlink++)
        {
            if (!is_ccpi_link_good(lk_info[link].ctl[rlink]))
                BDK_TRACE(CCPI, "        Remote link %d: Down\n", rlink);
            else
                BDK_TRACE(CCPI, "        Remote link %d: Connects to node ID %d\n", rlink, lk_info[link].ctl[rlink].s.id);
            ocx_pp_write(rid, BDK_OCX_COM_LINKX_CTL(rlink), lk_info[link].ctl[rlink].u);
        }
    }

    BDK_TRACE(CCPI, "Programming local links\n");
    for (int link = 0; link < MAX_LINKS; link++)
    {
        if (!is_ccpi_link_good(lk_info[LOCAL_NODE].ctl[link]))
            BDK_TRACE(CCPI, "    Local link %d: Down\n", link);
        else
        {
            BDK_TRACE(CCPI, "    Local link %d: Connects to node ID %d\n", link, lk_info[link].node.s.id);
            bdk_numa_set_exists(lk_info[link].node.s.id);
        }
        BDK_CSR_MODIFY(c, node, BDK_OCX_COM_LINKX_CTL(link),
            c.s.id = lk_info[link].node.s.id);
    }

    BDK_TRACE(CCPI, "Checking the PP_CMD still works\n");
    int failures = 0;
    for (int link = 0; link < MAX_LINKS; link++)
    {
        BDK_CSR_INIT(local_link_ctl, node, BDK_OCX_COM_LINKX_CTL(link));
        if (!is_ccpi_link_good(local_link_ctl))
            continue;
        BDK_TRACE(CCPI, "    Local link %d: Checking\n", link);
        if (local_link_ctl.s.id != lk_info[link].node.s.id)
        {
            BDK_TRACE(CCPI, "        Failed: Local link ID doesn't match expect node ID\n");
            failures++;
        }
        bdk_ocx_com_node_t com_node;
        com_node.u = ocx_pp_read(local_link_ctl.s.id, BDK_OCX_COM_NODE);
        if (com_node.s.fixed &&
            (com_node.s.id == lk_info[link].node.s.id) &&
            local_link_ctl.s.id == lk_info[link].node.s.id)
        {
            BDK_TRACE(CCPI, "        Passed\n");
        }
        else
        {
            BDK_TRACE(CCPI, "        Failed\n");
            failures++;
        }
    }
    return (failures) ? -1 : 0;
}

/**
 * After CCPI link is up and the connections are functional, we need to setup
 * all remote hardware on the secondary nodes. This function does that. It
 * is safe to call on all nodes, including the master.
 *
 * @param node   Node to configure
 */
static void ccpi_setup_node_hardware(bdk_node_t node)
{
    /* Enable secure access to all of memory */
    BDK_CSR_WRITE(node, BDK_L2C_ASC_REGIONX_START(0), 0);
    BDK_CSR_WRITE(node, BDK_L2C_ASC_REGIONX_END(0), -1);
    BDK_CSR_WRITE(node, BDK_L2C_ASC_REGIONX_ATTR(0), 2);

    /* Update way partition to allow core 0 to write to L2 */
    BDK_CSR_WRITE(node, BDK_L2C_WPAR_PPX(0), 0);
    BDK_CSR_READ(node, BDK_L2C_WPAR_PPX(0));
    __bdk_init_node(node);
}

/**
 * Brings the CCPI lanes and links into an operational state without enabling
 * multi-node operation. Calling this function when the CCPI links are already
 * up does nothing. This function must return zero before you can go multi-node
 * by calling bdk_init_ccpi_multinode().
 *
 * @param gbaud  Baud rate to run links at. This is only used if the QLMs are in software init
 *               mode. If they are strapped for hardware init, the strapping speed is used.
 *
 * @return Zero on success, negative on failure. Zero means all CCPI links are functional.
 */
int __bdk_init_ccpi_links(uint64_t gbaud)
{
    bdk_node_t node = bdk_numa_local();

    if (bdk_is_platform(BDK_PLATFORM_EMULATOR))
        return -1; /* Emulator doesn't seem to have CCPI registers */

    /* Use the link reset control to determine if we've already done CCPI
       setup */
    BDK_CSR_INIT(rst_ocx, node, BDK_RST_OCX);
    if (rst_ocx.s.rst_link == 0)
    {
        BDK_TRACE(CCPI, "N%d: Applying CCPI errata fixes\n", node);
        ccpi_errata(node, gbaud);
        printf("Starting CCPI links\n");
        /* Bringup the  lanes and links */
        if (__bdk_init_ccpi_connection(1, gbaud, (1ull << BDK_TRACE_ENABLE_CCPI) & bdk_trace_enables))
            return -1;
        /* Give the other node time to put the core back in reset */
        bdk_wait_usec(1000000);
    }

    if (node == 0)
    {
        BDK_CSR_INIT(l2c_oci_ctl, node, BDK_L2C_OCI_CTL);
        if (l2c_oci_ctl.s.enaoci)
            return 0;

        /* Do node assignments */
        if (ccpi_setup_nodes(node))
            return -1;

        for (bdk_node_t node = 0; node < BDK_NUMA_MAX_NODES; node++)
        {
            if (bdk_numa_exists(node))
            {
                /* Split across two links as HW currently only support 2 node */
                BDK_CSR_DEFINE(dual_sort, BDK_OCX_COM_DUAL_SORT);
                dual_sort.u = ocx_pp_read(node, BDK_OCX_COM_DUAL_SORT);
                dual_sort.s.sort = 2;
                ocx_pp_write(node, BDK_OCX_COM_DUAL_SORT, dual_sort.u);

                BDK_TRACE(CCPI, "N%d: Clearing lane errors\n", node);
                /* Enable the OCX lane counters across all lanes and clear existing errors */
                for (int lane=0; lane<24; lane++)
                {
                    ocx_pp_write(node, BDK_OCX_LNEX_INT(lane), ocx_pp_read(node, BDK_OCX_LNEX_INT(lane)));
                    BDK_CSR_DEFINE(ocx_lnex_cfg, BDK_OCX_LNEX_CFG(lane));
                    ocx_lnex_cfg.u = ocx_pp_read(node, BDK_OCX_LNEX_CFG(lane));
                    ocx_lnex_cfg.s.rx_stat_wrap_dis = 1;
                    ocx_lnex_cfg.s.rx_stat_ena = 1;
                    ocx_lnex_cfg.s.rx_stat_rdclr = 1; /* Clear on read, see below */
                    ocx_pp_write(node, BDK_OCX_LNEX_CFG(lane), ocx_lnex_cfg.u);
                    /* Make sure the update is complete */
                    ocx_pp_read(node, BDK_OCX_LNEX_CFG(lane));
                    /* Read to clear the lane statistics counters. This way
                       any errors that occurred during init aren't mistakenly
                       seen later */
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT00(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT01(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT02(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT03(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT04(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT05(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT06(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT07(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT08(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT09(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT10(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT11(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT12(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT13(lane));
                    ocx_pp_read(node, BDK_OCX_LNEX_STAT14(lane));
                    /* Disable the clear on read now that we've cleared errors */
                    ocx_lnex_cfg.s.rx_stat_rdclr = 0;
                    ocx_pp_write(node, BDK_OCX_LNEX_CFG(lane), ocx_lnex_cfg.u);
                }

                BDK_TRACE(CCPI, "N%d: Clearing link errors\n", node);
                for (int link = 0; link < MAX_LINKS; link++)
                {
                    ocx_pp_write(node, BDK_OCX_TLKX_STAT_ERR_CNT(link), 0);
                    ocx_pp_write(node, BDK_OCX_TLKX_STAT_RETRY_CNT(link), 0);
                    ocx_pp_write(node, BDK_OCX_RLKX_BLK_ERR(link), 0xffff0000);
                    ocx_pp_write(node, BDK_OCX_COM_LINKX_INT(link), ocx_pp_read(node, BDK_OCX_COM_LINKX_INT(link)));
                }
                ocx_pp_write(node, BDK_OCX_COM_INT, ocx_pp_read(node, BDK_OCX_COM_INT));
            }
        }
    }
    return 0;
}

/**
 * Once CCPI links are operational, this function transitions the system to a
 * multi-node setup. Note that this function only performs the low level CCPI
 * details, not BDK software setup on the other nodes. Call bdk_init_nodes()
 * for high level access to multi-node.
 *
 * @return Zero on success, negative on failure
 */
int __bdk_init_ccpi_multinode(void)
{
    bdk_node_t my_node = bdk_numa_local();
    uint64_t node_exists = bdk_numa_get_exists_mask();

    /* This can only be run on the main node */
    if (my_node != bdk_numa_master())
        return -1;

    /* Tell local L2 that CCPI is good */
    BDK_TRACE(CCPI, "Configuring L2 for CCPI on all nodes (exists = 0x%lx)\n", node_exists);
    for (bdk_node_t node = 0; node < BDK_NUMA_MAX_NODES; node++)
    {
        if (node == my_node)
        {
            BDK_CSR_MODIFY(l2c_oci_ctl, node, BDK_L2C_OCI_CTL,
                /* Errata (L2C-27380) L2C_OCI_CTL[LOCK_LOCAL_*,CAS_FDX] must be set */
                if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X))
                {
                    l2c_oci_ctl.s.lock_local_cas = 1;
                    l2c_oci_ctl.s.lock_local_stc = 1;
                    l2c_oci_ctl.s.lock_local_pp = 1;
                    l2c_oci_ctl.s.lock_local_iob = 1;
                    l2c_oci_ctl.s.cas_fdx = 1;
                }
                l2c_oci_ctl.s.iofrcl = 0;
                l2c_oci_ctl.s.enaoci = node_exists);
        }
        else if (node_exists & (1ull << node))
        {
            bdk_l2c_oci_ctl_t l2c_oci_ctl;
            l2c_oci_ctl.u = ocx_pp_read(node, BDK_L2C_OCI_CTL);
            /* Errata (L2C-27380) L2C_OCI_CTL[LOCK_LOCAL_*,CAS_FDX] must be set */
            if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X))
            {
                l2c_oci_ctl.s.lock_local_cas = 1;
                l2c_oci_ctl.s.lock_local_stc = 1;
                l2c_oci_ctl.s.lock_local_pp = 1;
                l2c_oci_ctl.s.lock_local_iob = 1;
                l2c_oci_ctl.s.cas_fdx = 1;
            }
            l2c_oci_ctl.s.iofrcl = 0;
            l2c_oci_ctl.s.enaoci = node_exists;
            ocx_pp_write(node, BDK_L2C_OCI_CTL, l2c_oci_ctl.u);
            // FIXME: Disable partial writes on pass 2 until it is debugged
            if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X))
            {
                bdk_l2c_ctl_t l2c_ctl;
                l2c_ctl.u = ocx_pp_read(node, BDK_L2C_CTL);
                l2c_ctl.s.dissblkdty = 1;
                ocx_pp_write(node, BDK_L2C_CTL, l2c_ctl.u);
            }
        }
    }
    BDK_TRACE(CCPI, "CCPI is functional\n");

    /* Report CCPI lanes so output matches old style */
    for (bdk_node_t node = 0; node < BDK_NUMA_MAX_NODES; node++)
    {
        if (bdk_numa_exists(node))
            ccpi_report_lane(node, 1);
    }

    /* Make sure all cores on remote nodes are in reset. The L2 will
       have invalid aliases for memory if we changed the node ID while
       a core was running */
    for (bdk_node_t node=0; node<BDK_NUMA_MAX_NODES; node++)
    {
        if (bdk_numa_exists(node) && (node != my_node))
        {
            BDK_CSR_INIT(rst_pp_available, node, BDK_RST_PP_AVAILABLE);
            BDK_CSR_INIT(rst_pp_reset, node, BDK_RST_PP_RESET);
            if (rst_pp_available.u & ~rst_pp_reset.u)
            {
                bdk_warn("*****************************************************\n");
                bdk_warn("Cores booted on remote node %d before OCI setup. L2\n", node);
                bdk_warn("aliases will make software unstable. Configure remote\n");
                bdk_warn("nodes for remote boot using GPIO_STRAP<3:0>=REMOTE.\n");
                bdk_warn("*****************************************************\n");
            }
            ccpi_setup_node_hardware(node);
        }
    }
    return 0;
}
