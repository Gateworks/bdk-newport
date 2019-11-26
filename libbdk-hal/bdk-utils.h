/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include "libbdk-arch/bdk-csrs-rst.h"

/**
 * @file
 * Small utility functions and macros to ease programming.
 *
 * <hr>$Revision: 38306 $<hr>
 *
 * @addtogroup hal
 * @{
 */

/*
 * The macros bdk_likely and bdk_unlikely use the
 * __builtin_expect GCC operation to control branch
 * probabilities for a conditional. For example, an "if"
 * statement in the code that will almost always be
 * executed should be written as "if (bdk_likely(...))".
 * If the "else" section of an if statement is more
 * probable, use "if (bdk_unlikey(...))".
 */
#define bdk_likely(x)      __builtin_expect(!!(x), 1)
#define bdk_unlikely(x)    __builtin_expect(!!(x), 0)

#define BDK_DISPLAY_PASS       1    /* Control the display of the detail chip pass info */
#define BDK_CACHE_LINE_SIZE    (128)   // In bytes
#define BDK_CACHE_LINE_MASK    (BDK_CACHE_LINE_SIZE - 1)   // In bytes
#define BDK_CACHE_LINE_ALIGNED __attribute__ ((aligned (BDK_CACHE_LINE_SIZE)))

/**
 * Builds a bit mask given the required size in bits.
 *
 * @param bits   Number of bits in the mask
 * @return The mask
 */
static inline uint64_t bdk_build_mask(uint64_t bits) __attribute__((always_inline));
static inline uint64_t bdk_build_mask(uint64_t bits)
{
    if (bits == 64)
        return -1;
    else
        return ~((~0x0ull) << bits);
}

/**
 * Extract bits out of a number
 *
 * @param input  Number to extract from
 * @param lsb    Starting bit, least significant (0-63)
 * @param width  Width in bits (1-64)
 *
 * @return Extracted number
 */
static inline uint64_t bdk_extract(uint64_t input, int lsb, int width) __attribute__((always_inline));
static inline uint64_t bdk_extract(uint64_t input, int lsb, int width)
{
    uint64_t result = input >> lsb;
    result &= bdk_build_mask(width);
    return result;
}

/**
 * Extract signed bits out of a number
 *
 * @param input  Number to extract from
 * @param lsb    Starting bit, least significant (0-63)
 * @param width  Width in bits (1-64)
 *
 * @return Extracted number
 */
static inline int64_t bdk_extracts(uint64_t input, int lsb, int width)
{
    int64_t result = input >> lsb;
    result <<= 64 - width;
    result >>= 64 - width;
    return result;
}

/**
 * Extract a signed magnitude value. Signed magnitude is a value where the MSB
 * is treated as a sign bit, not like the normal twos compliment
 *
 * @param v      Value to extract from
 * @param lsb    LSB of number
 * @param msb    MSB, which is the signed bit
 *
 * @return Extracted number
 */
static inline int64_t bdk_extract_smag(uint64_t v, int lsb, int msb) __attribute__((always_inline));
static inline int64_t bdk_extract_smag(uint64_t v, int lsb, int msb)
{
    int64_t r = bdk_extract(v, lsb, msb - lsb);
    if (v & (1ull << msb))
        r = -r;
    return r;
}

/**
 * Insert bits into a number
 *
 * @param original Original data, before insert
 * @param input    Data to insert
 * @param lsb    Starting bit, least significant (0-63)
 * @param width  Width in bits (1-64)
 *
 * @return Number with inserted bits
 */
static inline uint64_t bdk_insert(uint64_t original, uint64_t input, int lsb, int width) __attribute__((always_inline));
static inline uint64_t bdk_insert(uint64_t original, uint64_t input, int lsb, int width)
{
    uint64_t mask = bdk_build_mask(width);
    uint64_t result = original & ~(mask << lsb);
    result |= (input & mask) << lsb;
    return result;
}

/**
 * Return the number of cores available in the chip
 *
 * @return
 */
static inline int bdk_get_num_cores(bdk_node_t node)
{
    uint64_t available = BDK_CSR_READ(node, BDK_RST_PP_AVAILABLE);
    return bdk_dpop(available);
}

/**
 * Zero a block of memory
 *
 * @param start
 * @param length
 */
static inline void bdk_zero_memory(void *start, uint64_t length) __attribute__((always_inline));
static inline void bdk_zero_memory(void *start, uint64_t length)
{
    if (((long)start & BDK_CACHE_LINE_MASK) || (length & BDK_CACHE_LINE_MASK))
    {
        /* Use slwo memset for unaligned memory */
        memset(start, 0, length);
    }
    else
    {
        void *end = start + length;
        while (start<end)
        {
            asm volatile ("dc zva,%0" : : "r"(start));
            start += BDK_CACHE_LINE_SIZE;
        }
    }
}

/** @} */
