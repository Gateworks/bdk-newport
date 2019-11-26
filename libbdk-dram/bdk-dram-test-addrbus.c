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
 * Address bus test. This test writes a single value to each power of two in the
 * area, looking for false aliases that would be created by address lines being
 * shorted or tied together.
 *
 * @param area
 * @param max_address
 * @param bursts
 *
 * @return
 */
int __bdk_dram_test_mem_address_bus(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;

    /* Clear our work area. Checking for aliases later could get false
       positives if it matched stale data */
    void *ptr = (area) ? bdk_phys_to_ptr(area) : NULL;
    bdk_zero_memory(ptr, max_address - area);
    __bdk_dram_flush_to_mem_range(area, max_address);

    /* Each time we write, we'll write this pattern xored the address it is
       written too */
    uint64_t pattern = 0x0fedcba987654321;

    /* Walk through the region incrementing our offset by a power of two. The
       first few writes will be to the same cache line (offset 0x8, 0x10, 0x20,
       and 0x40. Offset 0x80 and beyond will be to different cache lines */
    uint64_t offset = 0x8;
    while (area + offset < max_address)
    {
        uint64_t address = area + offset;
        /* Write one location with pattern xor address */
        uint64_t p = pattern ^ address;
        WRITE64(address, p);
        __bdk_dram_flush_to_mem(address);
        offset <<= 1;
    }

    /* Read all of the area to make sure no other locations were written */
    uint64_t a = area;
    offset = 0x8;
    uint64_t next_write = area + offset;
    while (a < max_address)
    {
        if (a + 256 < max_address)
            BDK_PREFETCH(a + 256, 0);
        for (int i=0; i<16; i++)
        {
            uint64_t data = READ64(a);
            uint64_t correct;
            if (a == next_write)
            {
                correct = pattern ^ next_write;
                offset <<= 1;
                next_write = area + offset;
            }
            else
                correct = 0;
            if (bdk_unlikely(data != correct))
            {
                failures++;
                __bdk_dram_report_error(a, data, correct, 0, -1);
            }
            a += 8;
        }
    }

    return failures;
}

