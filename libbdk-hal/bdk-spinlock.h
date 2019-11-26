/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Implementation of spinlocks.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @addtogroup hal
 * @{
 */

/**
 * Spinlocks
 */
typedef union
{
    uint64_t combined;
    struct
    {
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32_t ticket;
        uint32_t serving;
#else
        uint32_t serving;
        uint32_t ticket;
#endif
    } s;
} bdk_spinlock_t;

/**
 * Initialize a spinlock
 *
 * @param lock   Lock to initialize
 */
static inline void bdk_spinlock_init(bdk_spinlock_t *lock)
{
    asm volatile ("str xzr, [%[b]]"
                  : "+m" (lock->combined)
                  : [b] "r" (&lock->combined)
                  : "memory");
}

/**
 * Releases lock
 *
 * @param lock   pointer to lock structure
 */
static inline void bdk_spinlock_unlock(bdk_spinlock_t *lock) __attribute__ ((always_inline));
static inline void bdk_spinlock_unlock(bdk_spinlock_t *lock)
{
    /* Implies a release */
    asm volatile ("stlr %w[v], [%[b]]"
                  : "+m" (lock->s.serving)
                  : [v] "r" (lock->s.serving + 1), [b] "r" (&lock->s.serving)
                  : "memory");
}

/**
 * Gets lock, spins until lock is taken
 *
 * @param lock   pointer to lock structure
 */
static inline void bdk_spinlock_lock(bdk_spinlock_t *lock) __attribute__ ((always_inline));
static inline void bdk_spinlock_lock(bdk_spinlock_t *lock)
{
    uint64_t combined;
    uint32_t ticket;
    uint32_t serving;

    asm volatile (
        "mov %x[serving], 1<<32                     \n"
        "ldadda %x[serving], %x[combined], [%[ptr]] \n"
        "and %x[serving], %x[combined], 0xffffffff  \n"
        "lsr %x[ticket], %x[combined], 32           \n"
        "cmp %x[ticket], %x[serving]                \n"
        "b.eq 1f                                    \n"
        "sevl                                       \n"
     "2: wfe                                        \n"
        "ldxr %w[serving], [%[ptr2]]                \n"
        "cmp %x[ticket], %x[serving]                \n"
        "b.ne 2b                                    \n"
     "1:                                            \n"
        : [serving] "=&r" (serving), [ticket] "=&r" (ticket), [combined] "=&r" (combined), "+m" (lock->combined)
        : [ptr] "r" (&lock->combined), [ptr2] "r" (&lock->s.serving)
        : "memory"
    );
}

/**
 * Tries to get the lock, failing if we can't get it immediately
 *
 * @param lock   pointer to lock structure
 */
static inline int bdk_spinlock_trylock(bdk_spinlock_t *lock) __attribute__ ((always_inline));
static inline int bdk_spinlock_trylock(bdk_spinlock_t *lock)
{
    uint64_t combined = *(volatile uint64_t *)&lock->combined;
    uint32_t ticket = combined >> 32;
    uint32_t serving = (uint32_t)combined;
    if (ticket != serving)
        return -1;
    uint64_t new_combined = combined + (1ull << 32);
    bool success = bdk_atomic_compare_and_store64(&lock->combined, combined, new_combined);
    return success ? 0 : -1;
}

/** @} */
