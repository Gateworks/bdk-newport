#ifndef __BDK_RLOCK_H__
#define __BDK_RLOCK_H__
/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Recursuve lock for use by libc and others
 *
 * @defgroup lock Lock related functions
 * @{
 */

typedef struct __attribute__ ((aligned (16))) /* So lock is always in 1 cache line */
{
    void *owner;
    unsigned int count;
} bdk_rlock_t;

void bdk_rlock_init(bdk_rlock_t *lock);
void bdk_rlock_lock(bdk_rlock_t *lock);
int bdk_rlock_try_lock(bdk_rlock_t *lock);
void bdk_rlock_unlock(bdk_rlock_t *lock);

/** @} */
#endif /* __BDK_RLOCK_H__ */
