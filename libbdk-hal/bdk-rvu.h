/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Interface to the hardware RVU.
 *
 * @addtogroup hal
 * @{
 */

#define BDK_RVU_PF 0    /* The BDK uses a hard coded PF number for accessing RVU devices */

/**
 * Allocate a block of MSIX vectors inside RVU
 *
 * @param node       Node to allocate for
 * @param msix_count Number to allocate
 *
 * @return Starting offset of MSIX vectors. On failure this function calls bdk_fatal(), so
 *         no error checking is needed on the return value.
 */
static inline int bdk_rvu_alloc_msix(bdk_node_t node, int msix_count)
{
    return 0; /* FIXME: Implement MSIX allocation for RVU */
}


/** @} */
