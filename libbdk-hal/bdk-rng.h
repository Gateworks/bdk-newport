/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Function and structure definitions for random number generator hardware
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup hal
 * @{
 */

/**
 * Reads 8 bits of random data from Random number generator
 *
 * @return random data
 */
extern uint8_t bdk_rng_get_random8(void);

/**
 * Reads 16 bits of random data from Random number generator
 *
 * @return random data
 */
extern uint16_t bdk_rng_get_random16(void);

/**
 * Reads 32 bits of random data from Random number generator
 *
 * @return random data
 */
extern uint32_t bdk_rng_get_random32(void);

/**
 * Reads 64 bits of random data from Random number generator
 *
 * @return random data
 */
extern uint64_t bdk_rng_get_random64(void);

/** @} */
