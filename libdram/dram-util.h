/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * Small utility functions for use by libdram internally. These
 * are not meant for users of the libdram API.
 */

/**
 * Standard min(a,b) macro
 */
#define min(X, Y)				\
	({ typeof (X) __x = (X);		\
		typeof (Y) __y = (Y);		\
		(__x < __y) ? __x : __y; })

/**
 * Standard max(a,b) macro
 */
#define max(X, Y)				\
	({ typeof (X) __x = (X); typeof(Y) __y = (Y);	\
		(__x > __y) ? __x : __y; })

/**
 * Absolute value of an integer
 *
 * @param v
 *
 * @return
 */
static inline int64_t _abs(int64_t v)
{
    return (v < 0) ? -v : v;
}

/**
 * Sign of an integer
 *
 * @param v
 *
 * @return
 */
static inline int64_t _sign(int64_t v)
{
    return v < 0;
}

/**
 * Divide and round results up to the next higher integer.
 *
 * @param dividend
 * @param divisor
 *
 * @return
 */
static inline uint64_t divide_roundup(uint64_t dividend, uint64_t divisor)
{
    return (dividend + divisor - 1) / divisor;
}

