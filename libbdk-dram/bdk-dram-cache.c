/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

/**
 * Return the highest address initialized by the BDK when running out of
 * cache. The space below this address may contain valid date before DRAM
 * is setup. Space at and after this address is unused before DRAM, and must
 * be zeroed before use.
 *
 * @return Size of the BDK cached area in bytes
 */
uint64_t bdk_dram_get_top_of_cache(void)
{
    uint64_t top_of_cache = bdk_l2c_get_cache_size_bytes(bdk_numa_master());
    if (top_of_cache >= (4 << 20))
        top_of_cache = top_of_cache * 3 / 4;
    if (top_of_cache >= (16 << 20))
        top_of_cache = 16 << 20;
    return top_of_cache;
}
