/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include "bdk.h"

/* Used for all memory reads/writes related to the test */
#define READ64(address) __bdk_dram_read64(address)
#define WRITE64(address, data) __bdk_dram_write64(address, data)

#define CBx2_mask (2 * BDK_CACHE_LINE_SIZE - 1)
#define CBx4_mask (4 * BDK_CACHE_LINE_SIZE - 1)
#define CBcount   (int)(BDK_CACHE_LINE_SIZE / sizeof(uint64_t))

/**
 * Standard min(a,b) macro
 */
#define min(X, Y)                               \
        ({ typeof (X) __x = (X);                \
                typeof (Y) __y = (Y);           \
                (__x < __y) ? __x : __y; })

/**
 * Fill an memory area with the address of each 64-bit word in the area.
 * Reread to confirm the pattern.
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area (exclusive)
 * @param bursts Number of time to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_self_addr(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;

    for (int burst = 0; burst < bursts; burst++)
    {
        /* Write the pattern to memory. Each location receives the address
         * of the location.
         */
        for (uint64_t address = area; address < max_address; address+=8)
            WRITE64(address, address);
        __bdk_dram_flush_to_mem_range(area, max_address);
        BDK_DCACHE_INVALIDATE;

        /* Read by ascending address the written memory and confirm that it
         * has the expected data pattern.
         */
        for (uint64_t address = area; address < max_address; )
        {
            if (address + 256 < max_address)
                BDK_PREFETCH(address + 256, 0);
            for (int i=0; i<16; i++)
            {
                uint64_t data = READ64(address);
                if (bdk_unlikely(data != address))
                    failures += __bdk_dram_retry_failure(burst, address, data, address);
                address += 8;
            }
        }
        __bdk_dram_flush_to_mem_range(area, max_address);
        BDK_DCACHE_INVALIDATE;

        /* Read by descending address the written memory and confirm that it
         * has the expected data pattern.
         */
        uint64_t end = max_address - sizeof(uint64_t);
        for (uint64_t address = end; address >= area; )
        {
            if (address - 256 >= area)
                BDK_PREFETCH(address - 256, 0);
            for (int i=0; i<16; i++)
            {
                uint64_t data = READ64(address);
                if (bdk_unlikely(data != address))
                    failures += __bdk_dram_retry_failure(burst, address, data, address);
                address -= 8;
            }
        }
        __bdk_dram_flush_to_mem_range(area, max_address);
        BDK_DCACHE_INVALIDATE;

        /* Read from random addresses within the memory area.
         */
        uint64_t probes = (max_address - area) / 128;
        uint64_t address_ahead1 = area;
        uint64_t address_ahead2 = area;
        for (uint64_t i = 0; i < probes; i++)
        {
            /* Create a pipeline of prefetches:
               address = address read this loop
               address_ahead1 = prefetch started last loop
               address_ahead2 = prefetch started this loop */
            uint64_t address = address_ahead1;
            address_ahead1 = address_ahead2;
            address_ahead2 = bdk_rng_get_random64() % (max_address - area);
            address_ahead2 += area;
            address_ahead2 &= -8;
            BDK_PREFETCH(address_ahead2, 0);

            uint64_t data = READ64(address);
            if (bdk_unlikely(data != address))
                failures += __bdk_dram_retry_failure(burst, address, data, address);
        }
    }
    return failures;
}

/**
 * Write "pattern" and its compliment to memory and verify it was written
 * properly. Memory will be filled with DWORDs pattern, ~pattern, pattern,
 * ~pattern, ...
 *
 * @param area    Start physical address of memory
 * @param max_address
 *                End of physical memory region
 * @param pattern Pattern to write
 * @param passes  Number of time to repeat the test
 *
 * @return Number of errors, zero on success
 */
static uint32_t test_mem_pattern(uint64_t area, uint64_t max_address, uint64_t pattern,
    int passes)
{
    int failures = 0;

    for (int pass = 0; pass < passes; pass++)
    {
        if (pass & 0x1)
            pattern = ~pattern;

        for (uint64_t address = area; address < max_address; address += 8)
            WRITE64(address, pattern);
        __bdk_dram_flush_to_mem_range(area, max_address);
        BDK_DCACHE_INVALIDATE;

        /* Read the written memory and confirm that it has the expected
         * data pattern.
         */
        uint64_t address = area;
        while (address < max_address)
        {
            if (address + 256 < max_address)
                BDK_PREFETCH(address + 256, 0);
            for (int i=0; i<16; i++)
            {
                uint64_t data = READ64(address);
                if (bdk_unlikely(data != pattern))
                    failures += __bdk_dram_retry_failure(pass, address, data, pattern);
                address += 8;
            }
        }
    }
    return failures;
}

/**
 * Walking zero written to memory, left shift
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area
 * @param bursts Number of time to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_leftwalk0(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    for (int burst = 0; burst < bursts; burst++)
    {
        for (uint64_t pattern = 1; pattern != 0; pattern = pattern << 1)
            failures += test_mem_pattern(area, max_address, ~pattern, 1);
    }
    return failures;
}

/**
 * Walking one written to memory, left shift
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area
 * @param bursts Number of time to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_leftwalk1(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    for (int burst = 0; burst < bursts; burst++)
    {
        for (uint64_t pattern = 1; pattern != 0; pattern = pattern << 1)
            failures += test_mem_pattern(area, max_address, pattern, 1);
    }
    return failures;
}

/**
 * Walking zero written to memory, right shift
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area
 * @param bursts Number of time to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_rightwalk0(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    for (int burst = 0; burst < bursts; burst++)
    {
        for (uint64_t pattern = 1ull << 63; pattern != 0; pattern = pattern >> 1)
            failures += test_mem_pattern(area, max_address, ~pattern, 1);
    }
    return failures;
}

/**
 * Walking one written to memory, right shift
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area
 * @param bursts Number of time to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_rightwalk1(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    for (int burst = 0; burst < bursts; burst++)
    {
        for (uint64_t pattern = 1ull<<63; pattern != 0; pattern = pattern >> 1)
            failures += test_mem_pattern(area, max_address, pattern, 1);
    }
    return failures;
}

/**
 * Apply the March C- testing algorithm to the given memory area.
 * 1) Write "pattern" to memory.
 * 2) Verify "pattern" and write "~pattern".
 * 3) Verify "~pattern" and write "pattern".
 * 4) Verify "pattern" and write "~pattern".
 * 5) Verify "~pattern" and write "pattern".
 * 6) Verify "pattern".
 *
 * @param area    Start of the physical memory area
 * @param max_address
 *                End of the physical memory area
 * @param pattern
 *
 * @return Number of errors, zero on success
 */
static int test_mem_march_c(uint64_t area, uint64_t max_address, uint64_t pattern)
{
    int failures = 0;

    /* Pass 1 ascending addresses, fill memory with pattern. */
    BDK_TRACE(DRAM_TEST, "    [0x%016lx:0x%016lx] Phase1, address incrementing, pattern 0x%016lx\n", area, max_address-1, pattern);
    for (uint64_t address = area; address < max_address; address += 8)
        WRITE64(address, pattern);

    __bdk_dram_flush_to_mem_range(area, max_address);
    BDK_DCACHE_INVALIDATE;

    /* Pass 2: ascending addresses, read pattern and write ~pattern */
    BDK_TRACE(DRAM_TEST, "    [0x%016lx:0x%016lx] Phase2, address incrementing, pattern 0x%016lx\n", area, max_address-1, ~pattern);
    for (uint64_t address = area; address < max_address; address += 8)
    {
        uint64_t data = READ64(address);
        if (bdk_unlikely(data != pattern))
            failures += __bdk_dram_retry_failure(1, address, data, pattern);
        WRITE64(address, ~pattern);
    }

    __bdk_dram_flush_to_mem_range(area, max_address);
    BDK_DCACHE_INVALIDATE;

    /* Pass 3: ascending addresses, read ~pattern and write pattern. */
    BDK_TRACE(DRAM_TEST, "    [0x%016lx:0x%016lx] Phase3, address incrementing, pattern 0x%016lx\n", area, max_address-1, pattern);
    for (uint64_t address = area; address < max_address; address += 8)
    {
        uint64_t data = READ64(address);
        if (bdk_unlikely(data != ~pattern))
            failures += __bdk_dram_retry_failure(1, address, data, ~pattern);
        WRITE64(address, pattern);
    }

    __bdk_dram_flush_to_mem_range(area, max_address);
    BDK_DCACHE_INVALIDATE;

    /* Pass 4: descending addresses, read pattern and write ~pattern. */
    BDK_TRACE(DRAM_TEST, "    [0x%016lx:0x%016lx] Phase4, address decrementing, pattern 0x%016lx\n", area, max_address-1, ~pattern);
    uint64_t end = max_address - sizeof(uint64_t);
    for (uint64_t address = end; address >= area; address -= 8)
    {
        uint64_t data = READ64(address);
        if (bdk_unlikely(data != pattern))
            failures += __bdk_dram_retry_failure(1, address, data, pattern);
        WRITE64(address, ~pattern);
    }

    __bdk_dram_flush_to_mem_range(area, max_address);
    BDK_DCACHE_INVALIDATE;

    /* Pass 5: descending addresses, read ~pattern and write pattern. */
    BDK_TRACE(DRAM_TEST, "    [0x%016lx:0x%016lx] Phase5, address decrementing, pattern 0x%016lx\n", area, max_address-1, pattern);
    for (uint64_t address = end; address >= area; address -= 8)
    {
        uint64_t data = READ64(address);
        if (bdk_unlikely(data != ~pattern))
            failures += __bdk_dram_retry_failure(1, address, data, ~pattern);
        WRITE64(address, pattern);
    }

    __bdk_dram_flush_to_mem_range(area, max_address);
    BDK_DCACHE_INVALIDATE;

    /* Pass 6: ascending addresses, read pattern. */
    BDK_TRACE(DRAM_TEST, "    [0x%016lx:0x%016lx] Phase6, address incrementing\n", area, max_address-1);
    for (uint64_t address = area; address < max_address; address += 8)
    {
        uint64_t data = READ64(address);
        if (bdk_unlikely(data != pattern))
            failures += __bdk_dram_retry_failure(1, address, data, pattern);
    }

    return failures;
}

/**
 * Use test_mem_march_c() with a all ones pattern
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area
 * @param bursts Number of time to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_solid(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    for (int burst = 0; burst < bursts; burst++)
        failures += test_mem_march_c(area, max_address, -1);
    return failures;
}

/**
 * Use test_mem_march_c() with a 0x55 pattern
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area
 * @param bursts Number of time to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_checkerboard(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    for (int burst = 0; burst < bursts; burst++)
        failures += test_mem_march_c(area, max_address, 0x5555555555555555L);
    return failures;
}

/**
 * Write a pseudo random pattern to memory and verify it
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area
 * @param bursts Number of time to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_random(uint64_t area, uint64_t max_address, int bursts)
{
    /* This constant is used to increment the pattern after every DWORD. This
       makes only the first DWORD truly random, but saves us processing
       power generating the random values */
    const uint64_t INC = 0x1010101010101010ULL;

    int burst, failures = 0;

    uint64_t *area1, *area2, *area3, *area4;
    uint64_t *address1, *address2, *address3, *address4;
    uint64_t extent, offset;
    uint64_t data;

    uint64_t init_pattern;
    uint64_t pattern1, pattern2;

    // make the base of the area on a 4x cache block boundary
    area = (area + CBx4_mask) & ~CBx4_mask; // round up
    max_address = max_address & ~CBx4_mask; // round dn

    extent = (max_address - area);
    offset = extent / 4;

    area1 = (uint64_t *) area;
    area2 = (uint64_t *) (area + (1 * offset));
    area3 = (uint64_t *) (area + (2 * offset));
    area4 = (uint64_t *) (area + (3 * offset));

    for (burst = 0; burst < bursts; burst++)
    {
        init_pattern = bdk_rng_get_random64();

        pattern1 = init_pattern;
        pattern2 = pattern1 + INC;
        address1 = area1;
        address2 = area2;
        address3 = area3;
        address4 = area4;

        /* Write the pattern to memory. Each location receives the random pattern
         * and a number of increments.
         */
        while (address1 < area2) {
            *address1 = pattern1;
            *(address1 + 1) = pattern2;
            address1 += 2;
            *address2 = pattern1;
            *(address2 + 1) = pattern2;
            address2 += 2;
            *address3 = pattern1;
            *(address3 + 1) = pattern2;
            address3 += 2;
            *address4 = pattern1;
            *(address4 + 1) = pattern2;
            address4 += 2;
            pattern1 = pattern2 + INC;
            pattern2 = pattern1 + INC;
        }

        __bdk_dram_flush_to_mem_range(area, max_address);
        BDK_DCACHE_INVALIDATE;

        /* Read the written memory and confirm that it has the expected
         * data pattern.
         */
        pattern1 = init_pattern;
        address1 = area1;
        address2 = area2;
        address3 = area3;
        address4 = area4;

        while (address1 < area2) {
            data = *address1;
            if (bdk_unlikely(data != pattern1))
                failures += __bdk_dram_retry_failure(burst, (uint64_t)address1, data, pattern1);
            data = *address2;
            if (bdk_unlikely(data != pattern1))
                failures += __bdk_dram_retry_failure(burst, (uint64_t)address2, data, pattern1);
            data = *address3;
            if (bdk_unlikely(data != pattern1))
                failures += __bdk_dram_retry_failure(burst, (uint64_t)address3, data, pattern1);
            data = *address4;
            if (bdk_unlikely(data != pattern1))
                failures += __bdk_dram_retry_failure(burst, (uint64_t)address4, data, pattern1);

            address1 += 1;
            address2 += 1;
            address3 += 1;
            address4 += 1;
            pattern1 += INC;
        }
    }
    return failures;
}

#if !USE_PREDICTION_CODE_VERSIONS
/**
 * test_mem_xor
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area
 * @param bursts Number of time to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_xor(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;

    uint64_t extent = max_address - area;
    uint64_t count = (extent / sizeof(uint64_t)) / 2;

    /* Fill both halves of the memory area with identical randomized data.
     */
    uint64_t address1 = area;
    uint64_t address2 = area + count * sizeof(uint64_t);

    uint64_t pattern = bdk_rng_get_random64();

    for (uint64_t j = 0; j < count; j++)
    {
        uint64_t p = pattern * address1;
        WRITE64(address1, p);
        WRITE64(address2, p);
        address1 += 8;
        address2 += 8;
    }
    __bdk_dram_flush_to_mem_range(area, max_address);
    BDK_DCACHE_INVALIDATE;

    /* Make a series of passes over the memory areas. */
    for (int burst = 0; burst < bursts; burst++)
    {
        /* XOR the data with a random value, applying the change to both
         * memory areas.
         */
        address1 = area;
        address2 = area + count * sizeof(uint64_t);

        pattern = bdk_rng_get_random64();

        for (uint64_t j = 0; j < count; j++)
        {
            if ((address1 & BDK_CACHE_LINE_MASK) == 0)
                BDK_PREFETCH(address1, BDK_CACHE_LINE_SIZE);
            if ((address2 & BDK_CACHE_LINE_MASK) == 0)
                BDK_PREFETCH(address2, BDK_CACHE_LINE_SIZE);
            WRITE64(address1, READ64(address1) ^ pattern);
            WRITE64(address2, READ64(address2) ^ pattern);
            address1 += 8;
            address2 += 8;
        }

        __bdk_dram_flush_to_mem_range(area, max_address);
        BDK_DCACHE_INVALIDATE;

        /* Look for differences in the areas. If there is a mismatch, reset
         * both memory locations with the same pattern. Failing to do so
         * means that on all subsequent passes the pair of locations remain
         * out of sync giving spurious errors.
         */
        address1 = area;
        address2 = area + count * sizeof(uint64_t);
        for (uint64_t j = 0; j < count; j++)
        {
            if ((address1 & BDK_CACHE_LINE_MASK) == 0)
                BDK_PREFETCH(address1, BDK_CACHE_LINE_SIZE);
            if ((address2 & BDK_CACHE_LINE_MASK) == 0)
                BDK_PREFETCH(address2, BDK_CACHE_LINE_SIZE);
            uint64_t d1 = READ64(address1);
            uint64_t d2 = READ64(address2);
            if (bdk_unlikely(d1 != d2))
            {
		failures += __bdk_dram_retry_failure2(burst, address1, d1, address2, d2);

                // Synchronize the two areas, adjusting for the error.
                WRITE64(address1, d2);
                WRITE64(address2, d2);
            }
            address1 += 8;
            address2 += 8;
        }
    }
    return failures;
}

/**
 * test_mem_rows
 *
 * Write a pattern of alternating 64-bit words of all one bits and then all 0
 * bits. This pattern generates the maximum amount of simultaneous switching
 * activity on the memory channels. Each pass flips the pattern with words
 * going from all ones to all zeros and vice versa.
 *
 * @param area   Start of the physical memory area
 * @param max_address
 *               End of the physical memory area
 * @param bursts Number of times to repeat the test over the entire area
 *
 * @return Number of errors, zero on success
 */
int __bdk_dram_test_mem_rows(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    uint64_t pattern = 0x0;
    uint64_t extent = (max_address - area);
    uint64_t count  = (extent / 2) / sizeof(uint64_t); // in terms of 64bit words

    /* Fill both halves of the memory area with identical data pattern. Odd
     * address 64-bit words get the pattern, while even address words get the
     * inverted pattern.
     */
    uint64_t address1 = area;
    uint64_t address2 = area + count * sizeof(uint64_t);

    for (uint64_t j = 0; j < (count / 2); j++)
    {
        WRITE64(address1, pattern);
        WRITE64(address2, pattern);
        address1 += 8;
        address2 += 8;
        WRITE64(address1, ~pattern);
        WRITE64(address2, ~pattern);
        address1 += 8;
        address2 += 8;
    }
    __bdk_dram_flush_to_mem_range(area, max_address);
    BDK_DCACHE_INVALIDATE;

    /* Make a series of passes over the memory areas. */
    for (int burst = 0; burst < bursts; burst++)
    {
        /* Invert the data, applying the change to both memory areas. Thus on
	 * alternate passes, the data flips from 0 to 1 and vice versa.
         */
        address1 = area;
        address2 = area + count * sizeof(uint64_t);
        for (uint64_t j = 0; j < count; j++)
        {
            WRITE64(address1, ~READ64(address1));
            WRITE64(address2, ~READ64(address2));
            address1 += 8;
            address2 += 8;
        }
        __bdk_dram_flush_to_mem_range(area, max_address);
        BDK_DCACHE_INVALIDATE;

        /* Look for differences in the areas. If there is a mismatch, reset
         * both memory locations with the same pattern. Failing to do so
         * means that on all subsequent passes the pair of locations remain
         * out of sync giving spurious errors.
         */
        address1 = area;
        address2 = area + count * sizeof(uint64_t);
        for (uint64_t j = 0; j < count; j++)
        {
            uint64_t d1 = READ64(address1);
            uint64_t d2 = READ64(address2);
            if (bdk_unlikely(d1 != d2))
            {
		failures += __bdk_dram_retry_failure2(burst, address1, d1, address2, d2);

                // Synchronize the two areas, adjusting for the error.
                WRITE64(address1, d2);
                WRITE64(address2, d2);
            }
            address1 += 8;
            address2 += 8;
        }
    }
    return failures;
}
#endif /* !USE_PREDICTION_CODE_VERSIONS */

#if USE_PREDICTION_CODE_VERSIONS
//////////////////////////// this is the new code...

int __bdk_dram_test_mem_xor(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    int burst;

    uint64_t extent = max_address - area;
    uint64_t count  = (extent / sizeof(uint64_t)) / 2;
    uint64_t offset = count * sizeof(uint64_t);
    uint64_t area2  = area + offset;

    /* Fill both halves of the memory area with identical randomized data.
     */
    uint64_t address1 = area;
    uint64_t address2;

    uint64_t pattern1 = bdk_rng_get_random64();
    uint64_t pattern2 = 0;
    uint64_t this_pattern;

    uint64_t p;
    uint64_t d1, d2;

    // move the multiplies outside the loop
    uint64_t pbase = address1 * pattern1;
    uint64_t pincr = 8 * pattern1;
    uint64_t ppred;

    p = pbase;
    while (address1 < area2)
    {
        WRITE64(address1         , p);
        WRITE64(address1 + offset, p);
        address1 += 8;
	p += pincr;
    }
    __bdk_dram_flush_to_mem_range(area, max_address);
    BDK_DCACHE_INVALIDATE;

    /* Make a series of passes over the memory areas. */
    for (burst = 0; burst < bursts; burst++)
    {
        /* XOR the data with a random value, applying the change to both
         * memory areas.
         */
        address1 = area;

        this_pattern = bdk_rng_get_random64();
	pattern2 ^= this_pattern;

        BDK_PREFETCH(address1         , 0);
        BDK_PREFETCH(address1 + offset, 0);

        while (address1 < area2)
        {
            BDK_PREFETCH(address1         , BDK_CACHE_LINE_SIZE);
            BDK_PREFETCH(address1 + offset, BDK_CACHE_LINE_SIZE);
            address2 = min(address1 + BDK_CACHE_LINE_SIZE, area2);

            while (address1 < address2) {
                WRITE64(address1         , READ64(address1         ) ^ this_pattern);
                WRITE64(address1 + offset, READ64(address1 + offset) ^ this_pattern);
                address1 += 8;
            }
        }

        __bdk_dram_flush_to_mem_range(area, max_address);
        BDK_DCACHE_INVALIDATE;

        /* Look for differences from the expected pattern in both areas.
	 * If there is a mismatch, reset the appropriate memory location
	 * with the correct pattern. Failing to do so
         * means that on all subsequent passes the erroring locations
	 * will be out of sync, giving spurious errors.
         */
        address1 = area;
	ppred = pbase;

        BDK_PREFETCH(address1         , 0);
        BDK_PREFETCH(address1 + offset, 0);

        while (address1 < area2)
        {
            BDK_PREFETCH(address1         , BDK_CACHE_LINE_SIZE);
            BDK_PREFETCH(address1 + offset, BDK_CACHE_LINE_SIZE);
            address2 = min(address1 + BDK_CACHE_LINE_SIZE, area2);

            while (address1 < address2) {

                d1 = READ64(address1         );
                d2 = READ64(address1 + offset);

                p = ppred ^ pattern2;

                if (bdk_unlikely(d1 != p)) {
                    failures += __bdk_dram_retry_failure(burst, address1, d1, p);
                    // Synchronize the area, adjusting for the error.
                    //WRITE64(address1, p); // retries should do this
                }
                if (bdk_unlikely(d2 != p)) {
                    failures += __bdk_dram_retry_failure(burst, address1 + offset, d2, p);
                    // Synchronize the area, adjusting for the error.
                    //WRITE64(address1 + offset, p); // retries should do this
                }

                address1 += 8;
                ppred += pincr;

            } /* while (address1 < address2) */
        } /* while (address1 < area2) */
    } /* for (int burst = 0; burst < bursts; burst++) */
    return failures;
}

//////////////// this is the new code...

int __bdk_dram_test_mem_rows(uint64_t area, uint64_t max_address, int bursts)
{
    int failures = 0;
    uint64_t pattern1, pattern2;
    uint64_t extent, offset;
    uint64_t *area1, *area2, *area3, *area4;
    uint64_t d1, d2, d1b, d2b, d3, d4, d3b, d4b;
    uint64_t *address1, *address2, *address3, *address4;
    int burst, count;
#if 1
    uint64_t cboffset;
#endif

    // make the base of the area on a 4x cache block boundary
    area = (area + CBx4_mask) & ~CBx4_mask; // round up
    max_address = max_address & ~CBx4_mask; // round dn

    extent = (max_address - area);
    offset = extent / 4;

    area1 = (uint64_t *) area;
    area2 = (uint64_t *) (area + (1 * offset));
    area3 = (uint64_t *) (area + (2 * offset));
    area4 = (uint64_t *) (area + (3 * offset));

    /* Fill both halves of the memory area with identical data pattern. Odd
     * address 64-bit words get the pattern, while even address words get the
     * inverted pattern.
     */
    address1 = area1;
    address2 = area2;
    address3 = area3;
    address4 = area4;

    pattern1 = 0x0;
    pattern2 = ~pattern1; // start with original pattern

#if 1
    cboffset = 0;
#endif
    while (address1 < area2)
    {
        // write a full cache block to all areas
        // try writing in pairs to get GCC to use "stp"

        for (count = 0; count < CBcount/2; count += 1) {

            *address1++ = pattern1;
            *address1++ = pattern2;

            *address2++ = pattern1;
            *address2++ = pattern2;

            *address3++ = pattern1;
            *address3++ = pattern2;

            *address4++ = pattern1;
            *address4++ = pattern2;
        }
#if 1
        __bdk_dram_flush_to_mem(((uint64_t)area1) + cboffset);
        __bdk_dram_flush_to_mem(((uint64_t)area2) + cboffset);
        __bdk_dram_flush_to_mem(((uint64_t)area3) + cboffset);
        __bdk_dram_flush_to_mem(((uint64_t)area4) + cboffset);
        cboffset += BDK_CACHE_LINE_SIZE;
#endif
    }

#if 0
    __bdk_dram_flush_to_mem_range(area, max_address);
#endif
    BDK_DCACHE_INVALIDATE;

#if 0
    // FIXME: do a READ pass also, no checking
    address1 = area1;
    address2 = area2;

    count = 0;

    while (address1 < area2)
    {
        d1  = *address1++;
        d1b = *address1++;
        d2  = *address2++;
        d2b = *address2++;

        if (d1 != d2)
            count += 1;
        if (d1b != d2b)
            count += 1;
    }
    if (count > 0)
        printf("MarchingRows: read loop had %ld compare errors\n", count);

    __bdk_dram_flush_to_mem_range(area, max_address);
    BDK_DCACHE_INVALIDATE;
#endif

    /* Make a series of passes over the memory areas. */
    for (burst = 0; burst < bursts; burst++)
    {
        /* Invert the data, applying the change to both memory areas. Thus on
	 * alternate passes, the data flips from 0 to 1 and vice versa.
         */
        address1 = area1;
        address2 = area2;
        address3 = area3;
        address4 = area4;

        BDK_PREFETCH(address1, 0);
        BDK_PREFETCH(address2, 0);
        BDK_PREFETCH(address3, 0);
        BDK_PREFETCH(address4, 0);

#if 1
        cboffset = 0;
#endif
        while (address1 < area2)
        {
            BDK_PREFETCH(address1, BDK_CACHE_LINE_SIZE);
            BDK_PREFETCH(address2, BDK_CACHE_LINE_SIZE);
            BDK_PREFETCH(address3, BDK_CACHE_LINE_SIZE);
            BDK_PREFETCH(address4, BDK_CACHE_LINE_SIZE);


            for (count = 0; count < CBcount/2; count += 1) {

                // again, write a full cache block to all areas
                // also try writing in pairs to get GCC to use "stp"

                d1  = *address1;
                d1b = *(address1 + 1);
                *address1 = ~d1;
                *(address1 + 1) = ~d1b;
                address1 += 2;

                d2  = *address2;
                d2b = *(address2 + 1);
                *address2 = ~d2;
                *(address2 + 1) = ~d2b;
                address2 += 2;

                d3  = *address3;
                d3b = *(address3 + 1);
                *address3 = ~d3;
                *(address3 + 1) = ~d3b;
                address3 += 2;

                d4  = *address4;
                d4b = *(address4 + 1);
                *address4 = ~d4;
                *(address4 + 1) = ~d4b;
                address4 += 2;
            }
#if 1
            __bdk_dram_flush_to_mem(((uint64_t)area1) + cboffset);
            __bdk_dram_flush_to_mem(((uint64_t)area2) + cboffset);
            __bdk_dram_flush_to_mem(((uint64_t)area3) + cboffset);
            __bdk_dram_flush_to_mem(((uint64_t)area4) + cboffset);
            cboffset += BDK_CACHE_LINE_SIZE;
#endif
        }

        __bdk_dram_flush_to_mem_range(area, max_address);
        BDK_DCACHE_INVALIDATE;

        /* Look for differences in the areas. If there is a mismatch, reset
         * both memory locations with the same pattern. Failing to do so
         * means that on all subsequent passes the pair of locations remain
         * out of sync giving spurious errors.
         */
        address1 = area1;
        address2 = area2;
        address3 = area3;
        address4 = area4;

	pattern1 = ~pattern1; // flip the starting pattern to match above loop

        BDK_PREFETCH(address1, 0);
        BDK_PREFETCH(address2, 0);
        BDK_PREFETCH(address3, 0);
        BDK_PREFETCH(address4, 0);

#if 1
        cboffset = 0;
#endif
        while (address1 < area2)
        {
            BDK_PREFETCH(address1, BDK_CACHE_LINE_SIZE);
            BDK_PREFETCH(address2, BDK_CACHE_LINE_SIZE);
            BDK_PREFETCH(address3, BDK_CACHE_LINE_SIZE);
            BDK_PREFETCH(address4, BDK_CACHE_LINE_SIZE);

            pattern2 = pattern1;

            for (count = 0; count < CBcount; count += 1) {

                // one slot at a time per cacheblock
                d1 = *address1;
                if (bdk_unlikely(d1 != pattern2)) {
                    failures += __bdk_dram_retry_failure(burst, (uint64_t)address1, d1, pattern2);
                }
                address1 += 1;

                d1 = *address2;
                if (bdk_unlikely(d1 != pattern2)) {
                    failures += __bdk_dram_retry_failure(burst, (uint64_t)address2, d1, pattern2);
                }
                address2 += 1;

                d1 = *address3;
                if (bdk_unlikely(d1 != pattern2)) {
                    failures += __bdk_dram_retry_failure(burst, (uint64_t)address3, d1, pattern2);
                }
                address3 += 1;

                d1 = *address4;
                if (bdk_unlikely(d1 != pattern2)) {
                    failures += __bdk_dram_retry_failure(burst, (uint64_t)address4, d1, pattern2);
                }
                address4 += 1;

                pattern2 = ~pattern2;
            }
#if 1
            __bdk_dram_flush_to_mem(((uint64_t)area1) + cboffset);
            __bdk_dram_flush_to_mem(((uint64_t)area2) + cboffset);
            __bdk_dram_flush_to_mem(((uint64_t)area3) + cboffset);
            __bdk_dram_flush_to_mem(((uint64_t)area4) + cboffset);
            cboffset += BDK_CACHE_LINE_SIZE;
#endif
        }
    }
    return failures;
}
#endif /* USE_PREDICTION_CODE_VERSIONS */
