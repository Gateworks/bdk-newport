/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Utility functions for endian swapping
 *
 * <hr>$Revision: 32636 $<hr>
 *
 * @addtogroup hal
 * @{
 */

/**
 * Byte swap a 16 bit number
 *
 * @param x      16 bit number
 * @return Byte swapped result
 */
static inline uint16_t bdk_swap16(uint16_t x)
{
    return ((uint16_t)((((uint16_t)(x) & (uint16_t)0x00ffU) << 8) |
                       (((uint16_t)(x) & (uint16_t)0xff00U) >> 8) ));
}


/**
 * Byte swap a 32 bit number
 *
 * @param x      32 bit number
 * @return Byte swapped result
 */
static inline uint32_t bdk_swap32(uint32_t x)
{
#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3))
    return __builtin_bswap32(x);
#else
     x = ((x<<8)&0xFF00FF00) | ((x>>8)&0x00FF00FF);
     x = (x>>16) | (x<<16);
     return x;
#endif
}


/**
 * Byte swap a 64 bit number
 *
 * @param x      64 bit number
 * @return Byte swapped result
 */
static inline uint64_t bdk_swap64(uint64_t x)
{
#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3))
    return __builtin_bswap64(x);
#else
     x = ((x<< 8)&0xFF00FF00FF00FF00ULL) | ((x>> 8)&0x00FF00FF00FF00FFULL);
     x = ((x<<16)&0xFFFF0000FFFF0000ULL) | ((x>>16)&0x0000FFFF0000FFFFULL);
     return (x>>32) | (x<<32);
#endif
}


#if __BYTE_ORDER == __BIG_ENDIAN

#define bdk_cpu_to_le16(x) bdk_swap16(x)
#define bdk_cpu_to_le32(x) bdk_swap32(x)
#define bdk_cpu_to_le64(x) bdk_swap64(x)

#define bdk_cpu_to_be16(x) (x)
#define bdk_cpu_to_be32(x) (x)
#define bdk_cpu_to_be64(x) (x)

#else

#define bdk_cpu_to_le16(x) (x)
#define bdk_cpu_to_le32(x) (x)
#define bdk_cpu_to_le64(x) (x)

#define bdk_cpu_to_be16(x) bdk_swap16(x)
#define bdk_cpu_to_be32(x) bdk_swap32(x)
#define bdk_cpu_to_be64(x) bdk_swap64(x)

#endif

#define bdk_le16_to_cpu(x) bdk_cpu_to_le16(x)
#define bdk_le32_to_cpu(x) bdk_cpu_to_le32(x)
#define bdk_le64_to_cpu(x) bdk_cpu_to_le64(x)

#define bdk_be16_to_cpu(x) bdk_cpu_to_be16(x)
#define bdk_be32_to_cpu(x) bdk_cpu_to_be32(x)
#define bdk_be64_to_cpu(x) bdk_cpu_to_be64(x)

/** @} */
