/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
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

