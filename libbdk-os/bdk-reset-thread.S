/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#define RST_PP_RESET 0x87E006001740

    .section .text
    .global __bdk_reset_thread
__bdk_reset_thread:
    /* Switch to the exception stack so we can free our thread context */
    adr     x10, __bdk_initial_stack_end
    msr     SPSel, 0            /* Use the EL0 stack */
    mov     sp, x10             /* Update the stack */
    /* Lock the stack in case other cores try using it */
    adr     x10, __bdk_initial_stack_start
    mov     x12, 1
1:  ldxr    x11, [x10]
    cbnz    x11, 1b
    stxr    w11, x12, [x10]
    cbnz    w11, 1b

    /* Free the thread context */
    mrs     x0, TPIDR_EL3
    bl      free
    dmb     sy

    /* Make sure the write buffer is idle and the dcache is empty */
    dsb     sy
    sys     #0,c11,c0,#2, xzr

    /* Load the address of RST_PP_RESET */
    mov     x0, RST_PP_RESET >> 32
    lsl     x0, x0, 32
    mov     x1, (RST_PP_RESET & 0xffff0000)
    orr     x0, x0, x1
    mov     x1, (RST_PP_RESET & 0xffff)
    orr     x0, x0, x1
    mrs     x2, MPIDR_EL1   /* Node ID is [23:16] */
    ubfx    x1, x2, 16, 8   /* Extract node ID */
    bfi     x0, x1, 44, 2   /* Insert into IO address at [45:44] */

    /* Core ID is split into bits [15:8] and [3:0] */
    ubfx    x3, x2, 0, 4    /* low = bits [3:0] */
    ubfx    x4, x2, 8, 8    /* high = bits [15:8] */
    lsl     x4, x4, 4       /* high = high << 4 */
    orr     x3, x3, x4      /* core = high | low */

    /* Create a bitmask representing this core */
    mov     x2, 1           /* mask = 1 */
    lsl     x2, x2, x3      /* mask <<= core */

    /* Get the address to unlock the exception stack */
    adr     x3, __bdk_initial_stack_start

    ldr     x1, [x0]        /* Read current reset */
    orr     x1, x1, x2      /* add my core mask */
    str     xzr, [x3]       /* Unlock the stack */
    dmb     sy              /* Flush the write buffer */
    str     x1, [x0]        /* Write new reset */
    /* Note: there is a small race condition between the unlock of the stack
        and the write of the new reset mask. Hopefully this is small enough
        that we never hit it */

    /* Spin until we die */
1:  wfi
    b       1b

