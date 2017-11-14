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
#include "libbdk-arch/bdk-csrs-dpi.h"
#include "libbdk-arch/bdk-csrs-pcieep.h"
#include "libbdk-arch/bdk-csrs-pem.h"
#include "libbdk-arch/bdk-csrs-pki.h"

/* Packets over PCIe (SDP) */

static int if_num_interfaces(bdk_node_t node)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX))
        return 2; /* CN83XX has 2 End Point Functions (EPF) */
    else
        return 0;
}

static int if_num_ports(bdk_node_t node, int interface)
{
    /* CN83XX uses PEM 0 and 2 */
    int pcie_port = (interface) ? 2 : 0;

    /* Make sure PEM is on */
    BDK_CSR_INIT(pemx_on, node, BDK_PEMX_ON(pcie_port));
    if (!pemx_on.s.pemon || !pemx_on.s.pemoor)
        return 0;

    /* Make sure PEM is EP */
    BDK_CSR_INIT(pemx_cfg, node, BDK_PEMX_CFG(pcie_port));
    if (pemx_cfg.cn83xx.hostmd)
        return 0;

    BDK_CSR_INIT(rinfo, node, BDK_SDPX_EPFX_RINFO(0, interface));
    return rinfo.s.trs;
}

static int if_probe(bdk_if_handle_t handle)
{
    /* Set the port name */
    if (bdk_numa_is_only_one())
        snprintf(handle->name, sizeof(handle->name), "SDP%d.%d", handle->interface, handle->index);
    else
        snprintf(handle->name, sizeof(handle->name), "N%d.SDP%d.%d", handle->node, handle->interface, handle->index);
    handle->name[sizeof(handle->name)-1] = 0;

    /* SDP only supports PKI / PKO */
    handle->pko_queue = 1;
    BDK_CSR_INIT(rinfo, handle->node, BDK_SDPX_EPFX_RINFO(0, handle->interface));
    handle->pki_channel = BDK_PKI_CHAN_E_DPI_CHX(rinfo.s.srn + handle->index);

    return 0;
}

static int if_init(bdk_if_handle_t handle)
{
    /* Record the PKND for this port */
    BDK_CSR_MODIFY(c, handle->node, BDK_SDPX_GBL_CONTROL(0),
        c.s.bpkind = handle->pknd);
    return 0;
}

static int if_enable(bdk_if_handle_t handle)
{
    return 0; /* SDP is always enabled */
}

static int if_disable(bdk_if_handle_t handle)
{
    return 0; /* SDP is always enabled, no disable */
}

static bdk_if_link_t if_link_get(bdk_if_handle_t handle)
{
    bdk_if_link_t result;
    result.u64 = 0;

    /* CN83XX uses PEM 0 and 2 */
    int pcie_port = (handle->interface) ? 2 : 0;
    BDK_CSR_INIT(pcieepx_cfg032, handle->node, BDK_PCIEEPX_CFG032(pcie_port));

    result.s.lanes = pcieepx_cfg032.s.nlw;
    switch (pcieepx_cfg032.s.ls)
    {
        case 3:
            result.s.speed = 8000;
            break;
        case 2:
            result.s.speed = 5000;
            break;
        default:
            result.s.speed = 2500;
            break;
    }
    result.s.full_duplex = 1;
    result.s.up = 1;

    return result;
}

static const bdk_if_stats_t *if_get_stats(bdk_if_handle_t handle)
{
    bdk_pki_fill_rx_stats(handle);
    bdk_pko_fill_tx_stats(handle);
    return &handle->stats;
}

const __bdk_if_ops_t __bdk_if_ops_pcie = {
    .if_num_interfaces = if_num_interfaces,
    .if_num_ports = if_num_ports,
    .if_probe = if_probe,
    .if_init = if_init,
    .if_enable = if_enable,
    .if_disable = if_disable,
    .if_link_get = if_link_get,
    .if_transmit = bdk_pko_transmit,
    .if_get_queue_depth = bdk_pko_get_queue_depth,
    .if_get_stats = if_get_stats,
};

