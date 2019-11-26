/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

#define GPR_OFFSET(reg) 16 + reg * 8

    /* X0 is the new context, TPIDR_EL3 is the old one. TPIDR_EL3
        can be zero. If X1 is non zero the old context is freed */
    .section .text
    .global __bdk_thread_switch
__bdk_thread_switch:
    stp     x10, xzr, [sp,-16]
    mrs     x10, TPIDR_EL3          /* Get the current context */
    cbz     x10, skip_save          /* Skip save if current context is zero */

    stp     x0, x1,[x10, GPR_OFFSET(0)]
    stp     x2, x3,[x10, GPR_OFFSET(2)]
    ldp     x2, xzr, [sp, -16]              /* Put x10 in x2 so we can save it later */
    stp     x4, x5,[x10, GPR_OFFSET(4)]
    stp     x6, x7,[x10, GPR_OFFSET(6)]
    stp     x8, x9,[x10, GPR_OFFSET(8)]
    stp     x2, x11,[x10, GPR_OFFSET(10)]   /* x2 is really x10 */
    mov     x11, sp                         /* sp is now in x11 */
    stp     x12, x13,[x10, GPR_OFFSET(12)]
    stp     x14, x15,[x10, GPR_OFFSET(14)]
    stp     x16, x17,[x10, GPR_OFFSET(16)]
    stp     x18, x19,[x10, GPR_OFFSET(18)]
    stp     x20, x21,[x10, GPR_OFFSET(20)]
    stp     x22, x23,[x10, GPR_OFFSET(22)]
    stp     x24, x25,[x10, GPR_OFFSET(24)]
    stp     x26, x27,[x10, GPR_OFFSET(26)]
    stp     x28, x29,[x10, GPR_OFFSET(28)]
    stp     x30, x11,[x10, GPR_OFFSET(30)]  /* SP is last */
    /* No need to save FP registers due to calling convention */

skip_save:
    /* Switch to the new thread stack so we can call C functions */
    ldr     x11, [x0, GPR_OFFSET(31)]   /* SP is last of GPR */
    mov     sp, x11
    msr     TPIDR_EL3, x0               /* Store new context */

    /* Store the old context and the don't free to the stack so we can
        restore registers */
    stp     x10, x1, [sp, -16]!

    /* Restore our thread context */
    ldp     x2, x3,[x0, GPR_OFFSET(2)]
    ldp     x4, x5,[x0, GPR_OFFSET(4)]
    ldp     x6, x7,[x0, GPR_OFFSET(6)]
    ldp     x8, x9,[x0, GPR_OFFSET(8)]
    ldp     x10, x11,[x0, GPR_OFFSET(10)]
    ldp     x12, x13,[x0, GPR_OFFSET(12)]
    ldp     x14, x15,[x0, GPR_OFFSET(14)]
    ldp     x16, x17,[x0, GPR_OFFSET(16)]
    ldp     x18, x19,[x0, GPR_OFFSET(18)]
    ldp     x20, x21,[x0, GPR_OFFSET(20)]
    ldp     x22, x23,[x0, GPR_OFFSET(22)]
    ldp     x24, x25,[x0, GPR_OFFSET(24)]
    ldp     x26, x27,[x0, GPR_OFFSET(26)]
    ldp     x28, x29,[x0, GPR_OFFSET(28)]
    ldp     x30, xzr,[x0, GPR_OFFSET(30)]   /* SP was restored above */
    ldp     x0, x1,[x0, GPR_OFFSET(0)]

    /* Thread switch is done and all registers restored */

    /* Call switch complete */
    stp     x0, x1, [sp, -16]!
    stp     x2, x3, [sp, -16]!
    stp     x4, x5, [sp, -16]!
    stp     x6, x7, [sp, -16]!
    stp     x8, x9, [sp, -16]!
    stp     x10, x11, [sp, -16]!
    stp     x12, x13, [sp, -16]!
    stp     x14, x15, [sp, -16]!
    stp     x16, x17, [sp, -16]!
    stp     x18, x19, [sp, -16]!
    stp     x20, x21, [sp, -16]!
    stp     x22, x23, [sp, -16]!
    stp     x24, x25, [sp, -16]!
    stp     x26, x27, [sp, -16]!
    stp     x28, x29, [sp, -16]!
    stp     x30, xzr, [sp, -16]!
    ldp     x0, x1, [sp, 16 * 16]
    bl      __bdk_thread_switch_complete
    ldp     x30, xzr, [sp], 16
    ldp     x28, x29, [sp], 16
    ldp     x26, x27, [sp], 16
    ldp     x24, x25, [sp], 16
    ldp     x22, x23, [sp], 16
    ldp     x20, x21, [sp], 16
    ldp     x18, x19, [sp], 16
    ldp     x16, x17, [sp], 16
    ldp     x14, x15, [sp], 16
    ldp     x12, x13, [sp], 16
    ldp     x10, x11, [sp], 16
    ldp     x8, x9, [sp], 16
    ldp     x6, x7, [sp], 16
    ldp     x4, x5, [sp], 16
    ldp     x2, x3, [sp], 16
    ldp     x0, x1, [sp], 32 /* Also removes old context and flag from stack */
    ret


