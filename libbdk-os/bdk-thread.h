/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for controlling threads.
 *
 * <hr>$Revision: 49448 $<hr>
 *
 * @defgroup thread Threading library
 * @{
 */

/* Use a larger stack size for main() as it tends to do lots of
    extra stuff. For example, DDR init requires a bigger stack */
#define BDK_THREAD_MAIN_STACK_SIZE 16384
#define BDK_THREAD_DEFAULT_STACK_SIZE 8192

typedef void (*bdk_thread_func_t)(int arg, void *arg1);

extern int bdk_thread_initialize(void);
extern void bdk_thread_yield(void);
extern int bdk_thread_create(bdk_node_t node, uint64_t coremask, bdk_thread_func_t func, int arg0, void *arg1, int stack_size);
extern void bdk_thread_destroy(void) __attribute__ ((noreturn));
extern void bdk_thread_first(bdk_thread_func_t func, int arg0, void *arg1, int stack_size) __attribute__ ((noreturn));

/**
 * Number of the Core on which the program is currently running.
 *
 * @return Number of cores
 */
static inline int bdk_get_core_num(void) __attribute__ ((always_inline));
static inline int bdk_get_core_num(void)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        int mpidr_el1;
        BDK_MRS(MPIDR_EL1, mpidr_el1);
        /* Core is 4 bits from AFF0 and rest from AFF1 */
        int core_num;
        core_num = mpidr_el1 & 0xf;
        core_num |= (mpidr_el1 & 0xff00) >> 4;
        return core_num;
    }
    else
    {
        uint64_t cvm_pn_el1;
        BDK_MRS(s3_0_c11_c4_2, cvm_pn_el1);
        return cvm_pn_el1 & 0xffff;
    }
}

/**
 * Return a mask representing this core in a 64bit bitmask
 *
 * @return
 */
static inline uint64_t bdk_core_to_mask(void) __attribute__ ((always_inline));
static inline uint64_t bdk_core_to_mask(void)
{
    return 1ull << bdk_get_core_num();
}

static inline int bdk_is_boot_core(void)
{
    const int master = 0x80000000 | (bdk_numa_master() << 16);
    int mpidr_el1;
    BDK_MRS_NV(MPIDR_EL1, mpidr_el1);
    return mpidr_el1 == master;
}


static inline void *bdk_thread_get_id(void) __attribute__ ((always_inline));
static inline void *bdk_thread_get_id(void)
{
    uint64_t current;
    BDK_MRS_NV(TPIDR_EL3, current);
    /* If we haven't started threading yet use the core number. Add one
        so the thread id is never zero */
    if (!current)
        current = bdk_get_core_num() + 1;
    return (void*)current;
}

/** @} */
