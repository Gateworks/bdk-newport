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
    .section .text
    .global __bdk_exception2
__bdk_exception2:
    #define GPR_OFFSET(reg) reg * 8
    #define FPR_OFFSET(reg) GPR_OFFSET(32) + reg * 16
    sub     sp, sp, FPR_OFFSET(32)
    stp     x0, x1, [sp, GPR_OFFSET(0)]
    stp     x2, x3, [sp, GPR_OFFSET(2)]
    stp     x4, x5, [sp, GPR_OFFSET(4)]
    stp     x6, x7, [sp, GPR_OFFSET(6)]
    stp     x8, x9, [sp, GPR_OFFSET(8)]
    stp     x10, x11, [sp, GPR_OFFSET(10)]
    stp     x12, x13, [sp, GPR_OFFSET(12)]
    stp     x14, x15, [sp, GPR_OFFSET(14)]
    stp     x16, x17, [sp, GPR_OFFSET(16)]
    stp     x18, x19, [sp, GPR_OFFSET(18)]
    stp     x20, x21, [sp, GPR_OFFSET(20)]
    stp     x22, x23, [sp, GPR_OFFSET(22)]
    stp     x24, x25, [sp, GPR_OFFSET(24)]
    stp     x26, x27, [sp, GPR_OFFSET(26)]
    stp     x28, x29, [sp, GPR_OFFSET(28)]
    mrs     x0, SP_EL0
    stp     x30, x0, [sp, GPR_OFFSET(30)]
    stp     q0, q1, [sp, FPR_OFFSET(0)]
    stp     q2, q3, [sp, FPR_OFFSET(2)]
    stp     q4, q5, [sp, FPR_OFFSET(4)]
    stp     q6, q7, [sp, FPR_OFFSET(6)]
    stp     q8, q9, [sp, FPR_OFFSET(8)]
    stp     q10, q11, [sp, FPR_OFFSET(10)]
    stp     q12, q13, [sp, FPR_OFFSET(12)]
    stp     q14, q15, [sp, FPR_OFFSET(14)]
    stp     q16, q17, [sp, FPR_OFFSET(16)]
    stp     q18, q19, [sp, FPR_OFFSET(18)]
    stp     q20, q21, [sp, FPR_OFFSET(20)]
    stp     q22, q23, [sp, FPR_OFFSET(22)]
    stp     q24, q25, [sp, FPR_OFFSET(24)]
    stp     q26, q27, [sp, FPR_OFFSET(26)]
    stp     q28, q29, [sp, FPR_OFFSET(28)]
    stp     q30, q31, [sp, FPR_OFFSET(30)]
    mov     x0, sp /* Pass registers as arguments for handler */
    bl      __bdk_exception_handler
    /* Should never get here */
    eret

    .global __bdk_init_exception_stack
__bdk_init_exception_stack:
    msr SPSel, 1
    mov sp, x0
    msr SPSel, 0
    ret

