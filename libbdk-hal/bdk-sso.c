/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

/* Channels is 12 bits in WQE. This contains pointers to 1024 element arrays
   for each node. They are not allocated until a network interface is required
   for the node to save space */
bdk_if_handle_t *bdk_sso_map[BDK_NUMA_MAX_NODES] = { NULL, };
void (*bdk_sso_process_work)(void);

/**
 * Initialize the SSO
 *
 * @return Zero on success, negative on failure
 */
int bdk_sso_init(bdk_node_t node)
{
    if (bdk_is_model(OCTEONTX_CN83XX))
    {
        extern int bdk_sso_init_cn83xx(bdk_node_t node);
        return bdk_sso_init_cn83xx(node);
    }
    else if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        extern int bdk_sso_init_cn9xxx(bdk_node_t node);
        return bdk_sso_init_cn9xxx(node);
    }
    return 0;
}

/**
 * Register a bdk-if handle with the SSO code so the SSO can be used to receive
 * traffic from it.
 *
 * @param handle Handle to register
 */
void bdk_sso_register_handle(bdk_if_handle_t handle)
{
    if (bdk_sso_map[handle->node] == NULL)
    {
        /* Channels is 12 bits in WQE */
        bdk_sso_map[handle->node] = calloc(0x1000, sizeof(bdk_if_handle_t));
        if (bdk_sso_map[handle->node] == NULL)
        {
            bdk_error("N%d.SSO: Failed to allocate channel mapping table\n", handle->node);
            return;
        }
    }
    bdk_sso_map[handle->node][handle->pki_channel] = handle;
}
