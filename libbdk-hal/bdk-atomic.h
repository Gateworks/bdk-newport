/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * This file provides atomic operations
 *
 * @addtogroup hal
 * @{
 */

/**
 * Atomically adds a signed value to a 32 bit (aligned) memory location.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.  (This should NOT be used for reference counting -
 * use the standard version instead.)
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 */
static inline void bdk_atomic_add32_nosync(int32_t *ptr, int32_t incr)
{
    /* Atomic add with no ordering */
    asm volatile ("ldadd %w[i], wzr, [%[b]]"
                  : [r] "+m" (*ptr)
                  : [i] "r" (incr), [b] "r" (ptr)
                  : "memory");
}

/**
 * Atomically adds a signed value to a 32 bit (aligned) memory location.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 */
static inline void bdk_atomic_add32(int32_t *ptr, int32_t incr)
{
    /* Atomic add with acquire and release */
    asm volatile ("ldaddal %w[i], wzr, [%[b]]"
                  : "+m" (*ptr)
                  : [i] "r" (incr), [b] "r" (ptr)
                  : "memory");
}

/**
 * Atomically sets a 32 bit (aligned) memory location to a value
 *
 * @param ptr    address of memory to set
 * @param value  value to set memory location to.
 */
static inline void bdk_atomic_set32(int32_t *ptr, int32_t value)
{
    /* Implies a release */
    asm volatile ("stlr %w[v], [%[b]]"
                  : "+m" (*ptr)
                  : [v] "r" (value), [b] "r" (ptr)
                  : "memory");
}

/**
 * Returns the current value of a 32 bit (aligned) memory
 * location.
 *
 * @param ptr    Address of memory to get
 * @return Value of the memory
 */
static inline int32_t bdk_atomic_get32(int32_t *ptr)
{
    return *(volatile int32_t *)ptr;
}

/**
 * Atomically adds a signed value to a 64 bit (aligned) memory location.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.  (This should NOT be used for reference counting -
 * use the standard version instead.)
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 */
static inline void bdk_atomic_add64_nosync(int64_t *ptr, int64_t incr)
{
    /* Atomic add with no ordering */
    asm volatile ("ldadd %x[i], xzr, [%[b]]"
                  : [r] "+m" (*ptr)
                  : [i] "r" (incr), [b] "r" (ptr)
                  : "memory");
}

/**
 * Atomically adds a signed value to a 64 bit (aligned) memory location.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 */
static inline void bdk_atomic_add64(int64_t *ptr, int64_t incr)
{
    /* Atomic add with acquire and release */
    asm volatile ("ldaddal %x[i], xzr, [%[b]]"
                  : [r] "+m" (*ptr)
                  : [i] "r" (incr), [b] "r" (ptr)
                  : "memory");
}

/**
 * Atomically sets a 64 bit (aligned) memory location to a value
 *
 * @param ptr    address of memory to set
 * @param value  value to set memory location to.
 */
static inline void bdk_atomic_set64(int64_t *ptr, int64_t value)
{
    /* Implies a release */
    asm volatile ("stlr %x[v], [%[b]]"
                  : "+m" (*ptr)
                  : [v] "r" (value), [b] "r" (ptr)
                  : "memory");
}

/**
 * Returns the current value of a 64 bit (aligned) memory
 * location.
 *
 * @param ptr    Address of memory to get
 * @return Value of the memory
 */
static inline int64_t bdk_atomic_get64(int64_t *ptr)
{
    return *(volatile int64_t *)ptr;
}

/**
 * Atomically compares the old value with the value at ptr, and if they match,
 * stores new_val to ptr.
 * If *ptr and old don't match, function returns failure immediately.
 * If *ptr and old match, function spins until *ptr updated to new atomically, or
 *  until *ptr and old no longer match
 *
 * Does no memory synchronization.
 *
 * @return 1 on success (match and store)
 *         0 on no match
 */
static inline int bdk_atomic_compare_and_store32_nosync(uint32_t *ptr, uint32_t old_val, uint32_t new_val) __attribute__((always_inline));
static inline int bdk_atomic_compare_and_store32_nosync(uint32_t *ptr, uint32_t old_val, uint32_t new_val)
{
    uint32_t val = old_val;

    asm volatile ("cas %w[o], %w[n], [%[b]]"
                  : [mem] "+m" (*ptr), [o] "+r" (val)
                  : [b] "r" (ptr), [n] "r" (new_val)
                  : );
    return old_val == val;
}

/**
 * Atomically compares the old value with the value at ptr, and if they match,
 * stores new_val to ptr.
 * If *ptr and old don't match, function returns failure immediately.
 * If *ptr and old match, function spins until *ptr updated to new atomically, or
 *  until *ptr and old no longer match
 *
 * Does memory synchronization that is required to use this as a locking primitive.
 *
 * @return 1 on success (match and store)
 *         0 on no match
 */
static inline int bdk_atomic_compare_and_store32(uint32_t *ptr, uint32_t old_val, uint32_t new_val) __attribute__((always_inline));
static inline int bdk_atomic_compare_and_store32(uint32_t *ptr, uint32_t old_val, uint32_t new_val)
{
    uint32_t val = old_val;

    asm volatile ("casal %w[o], %w[n], [%[b]]"
                  : [mem] "+m" (*ptr), [o] "+r" (val)
                  : [b] "r" (ptr), [n] "r" (new_val)
                  : );
    return old_val == val;
}

/**
 * Atomically compares the old value with the value at ptr, and if they match,
 * stores new_val to ptr.
 * If *ptr and old don't match, function returns failure immediately.
 * If *ptr and old match, function spins until *ptr updated to new atomically, or
 *  until *ptr and old no longer match
 *
 * Does no memory synchronization.
 *
 * @return 1 on success (match and store)
 *         0 on no match
 */
static inline int bdk_atomic_compare_and_store64_nosync(uint64_t *ptr, uint64_t old_val, uint64_t new_val) __attribute__((always_inline));
static inline int bdk_atomic_compare_and_store64_nosync(uint64_t *ptr, uint64_t old_val, uint64_t new_val)
{
    uint32_t val = old_val;

    asm volatile ("cas %x[o], %x[n], [%[b]]"
                  : [mem] "+m" (*ptr), [o] "+r" (val)
                  : [b] "r" (ptr), [n] "r" (new_val)
                  : );
    return old_val == val;
}

/**
 * Atomically compares the old value with the value at ptr, and if they match,
 * stores new_val to ptr.
 * If *ptr and old don't match, function returns failure immediately.
 * If *ptr and old match, function spins until *ptr updated to new atomically, or
 *  until *ptr and old no longer match
 *
 * Does memory synchronization that is required to use this as a locking primitive.
 *
 * @return 1 on success (match and store)
 *         0 on no match
 */
static inline int bdk_atomic_compare_and_store64(uint64_t *ptr, uint64_t old_val, uint64_t new_val) __attribute__((always_inline));
static inline int bdk_atomic_compare_and_store64(uint64_t *ptr, uint64_t old_val, uint64_t new_val)
{
    uint32_t val = old_val;

    asm volatile ("casal %x[o], %x[n], [%[b]]"
                  : [mem] "+m" (*ptr), [o] "+r" (val)
                  : [b] "r" (ptr), [n] "r" (new_val)
                  : );
    return old_val == val;
}

/**
 * Atomically adds a signed value to a 64 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.  (This should NOT be used for reference counting -
 * use the standard version instead.)
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location before increment
 */
static inline int64_t bdk_atomic_fetch_and_add64_nosync(int64_t *ptr, int64_t incr)
{
    int64_t result;
    /* Atomic add with no ordering */
    asm volatile ("ldadd %x[i], %x[r], [%[b]]"
                  : [r] "=r" (result), "+m" (*ptr)
                  : [i] "r" (incr), [b] "r" (ptr)
                  : "memory");
    return result;
}

/**
 * Atomically adds a signed value to a 64 bit (aligned) memory location,
 * and returns previous value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location before increment
 */
static inline int64_t bdk_atomic_fetch_and_add64(int64_t *ptr, int64_t incr)
{
    int64_t result;
    /* Atomic add with acquire/release */
    asm volatile ("ldaddal %x[i], %x[r], [%[b]]"
                  : [r] "=r" (result), "+m" (*ptr)
                  : [i] "r" (incr), [b] "r" (ptr)
                  : "memory");
    return result;
}

/**
 * Atomically adds a signed value to a 32 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.  (This should NOT be used for reference counting -
 * use the standard version instead.)
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location before increment
 */
static inline int32_t bdk_atomic_fetch_and_add32_nosync(int32_t *ptr, int32_t incr)
{
    int32_t result;
    /* Atomic add with no ordering */
    asm volatile ("ldadd %w[i], %w[r], [%[b]]"
                  : [r] "=r" (result), "+m" (*ptr)
                  : [i] "r" (incr), [b] "r" (ptr)
                  : "memory");
    return result;
}

/**
 * Atomically adds a signed value to a 32 bit (aligned) memory location,
 * and returns previous value.
 *
 * Memory access ordering is enforced before/after the atomic operation,
 * so no additional 'sync' instructions are required.
 *
 * @param ptr    address in memory to add incr to
 * @param incr   amount to increment memory location by (signed)
 *
 * @return Value of memory location before increment
 */
static inline int32_t bdk_atomic_fetch_and_add32(int32_t *ptr, int32_t incr)
{
    int32_t result;
    /* Atomic add with acquire/release */
    asm volatile ("ldaddal %w[i], %w[r], [%[b]]"
                  : [r] "=r" (result), "+m" (*ptr)
                  : [i] "r" (incr), [b] "r" (ptr)
                  : "memory");
    return result;
}

/**
 * Atomically set bits in a 64 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.
 *
 * @param ptr    address in memory
 * @param mask   mask of bits to set
 *
 * @return Value of memory location before setting bits
 */
static inline uint64_t bdk_atomic_fetch_and_bset64_nosync(uint64_t *ptr, uint64_t mask)
{
    uint64_t result;
    /* Atomic or with no ordering */
    asm volatile ("ldset %x[i], %x[r], [%[b]]"
                  : [r] "=r" (result), "+m" (*ptr)
                  : [i] "r" (mask), [b] "r" (ptr)
                  : "memory");
    return result;
}

/**
 * Atomically set bits in a 32 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.
 *
 * @param ptr    address in memory
 * @param mask   mask of bits to set
 *
 * @return Value of memory location before setting bits
 */
static inline uint32_t bdk_atomic_fetch_and_bset32_nosync(uint32_t *ptr, uint32_t mask)
{
    uint32_t result;
    /* Atomic or with no ordering */
    asm volatile ("ldset %w[i], %w[r], [%[b]]"
                  : [r] "=r" (result), "+m" (*ptr)
                  : [i] "r" (mask), [b] "r" (ptr)
                  : "memory");
    return result;
}

/**
 * Atomically clear bits in a 64 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.
 *
 * @param ptr    address in memory
 * @param mask   mask of bits to clear
 *
 * @return Value of memory location before clearing bits
 */
static inline uint64_t bdk_atomic_fetch_and_bclr64_nosync(uint64_t *ptr, uint64_t mask)
{
    uint64_t result;
    /* Atomic and with no ordering */
    asm volatile ("ldclr %x[i], %x[r], [%[b]]"
                  : [r] "=r" (result), "+m" (*ptr)
                  : [i] "r" (mask), [b] "r" (ptr)
                  : "memory");
    return result;
}

/**
 * Atomically clear bits in a 32 bit (aligned) memory location,
 * and returns previous value.
 *
 * This version does not perform 'sync' operations to enforce memory
 * operations.  This should only be used when there are no memory operation
 * ordering constraints.
 *
 * @param ptr    address in memory
 * @param mask   mask of bits to clear
 *
 * @return Value of memory location before clearing bits
 */
static inline uint32_t bdk_atomic_fetch_and_bclr32_nosync(uint32_t *ptr, uint32_t mask)
{
    uint32_t result;
    /* Atomic and with no ordering */
    asm volatile ("ldclr %w[i], %w[r], [%[b]]"
                  : [r] "=r" (result), "+m" (*ptr)
                  : [i] "r" (mask), [b] "r" (ptr)
                  : "memory");
    return result;
}

/** @} */
