/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include "bdk.h"

/* Used for all memory reads/writes related to the test */
#define READ64(address) __bdk_dram_read64(address)
#define WRITE64(address, data) __bdk_dram_write64(address, data)

/**
 * Fast scan test. This test is meant to find gross errors caused by read/write
 * level failing on a single rank or dimm. The idea is to scan through all of
 * memory in large steps. The large steps hit each rank multiple times, but not
 * every byte. If the whole rank has errors, his should find it quickly. This test
 * is suitable for an alive test during early boot.
 *
 * @param area   Starting physical address
 * @param max_address
 *               Ending physical address, exclusive
 * @param bursts Burst to run
 *
 * @return Number of errors
 */
int __bdk_dram_test_fast_scan(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    const uint64_t step = 0x10008; /* The 8 is so we walk through cache lines too */
    const uint64_t pattern1 = 0xaaaaaaaaaaaaaaaa;
    const uint64_t pattern2 = 0x5555555555555555;

    /* Walk through the region incrementing our offset by STEP */
    uint64_t a = area;
    while (a + 16 <= max_address)
    {
        WRITE64(a, pattern1);
        WRITE64(a+8, pattern2);
        __bdk_dram_flush_to_mem_range(a, a + 16);
        a += step;
    }

    /* Read back, checking the writes */
    a = area;
    while (a + 16 <= max_address)
    {
        /* Prefetch 3 ahead for better performance */
        uint64_t pre = a + step * 2;
        if (pre + 16 < max_address)
            BDK_PREFETCH(pre, 0);
        /* Check pattern 1 */
        uint64_t data1 = READ64(a);
        if (bdk_unlikely(data1 != pattern1))
        {
            failures++;
            __bdk_dram_report_error(a, data1, pattern1, 0, -1);
        }
        /* Check pattern 2 */
        uint64_t data2 = READ64(a+8);
        if (bdk_unlikely(data2 != pattern2))
        {
            failures++;
            __bdk_dram_report_error(a+8, data2, pattern2, 0, -1);
        }
        a += step;
    }

    return failures;
}

