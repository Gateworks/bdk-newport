/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

    .global _start
    .global __bdk_start
    .global __bdk_start_cores
    .global __bdk_initial_stack_start
    .global __bdk_initial_stack_end

    .section .init
_start:
    b   __bdk_start
    .word   0
    # BDK image heade for Thunder is
    #   Offset  Size    Description
    #   0x00    4       Raw instruction for skipping header (above)
    #   0x04    4       Length of the image, includes header
    #   0x08    8       Magic string "OCTEONTX"
    #   0x10    4       CRC32 of image + header. These bytes are zero when calculating the CRC
    #   0x14    4       Zero, reserved for future use
    #   0x18    64      ASCII Image name. Must always end in zero
    #   0x58    32      ASCII Version. Must always end in zero
    #   0x78    136     Zero, reserved for future use
    #   0x100   -       Beginning of image. Header is always 256 bytes.

    #
    # This is our entry point. The processor starts fetching instructions here,
    # 256 bytes into the image. Everything before this is header data
    #
.org 0x100
__bdk_start:
    ic      ialluis
    fmov    d30, x0 /* Save X0 in FPR for use later */
    fmov    d31, x1 /* Save X1 in FPR for use later */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    /* Change the core to big endian mode for EL3 */
    mrs     x0, SCTLR_EL3
    mov     x1, 1<<25       /* Set SCTLR_EL3[ee]=1 */
    orr     x0, x0, x1
    msr     SCTLR_EL3, x0
    #define ENDIAN_CONVERT64(reg) rev reg, reg
    #define ENDIAN_CONVERT32(reg) rev reg, reg
    #define ENDIAN_CONVERT16(reg) rev16 reg, reg
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    /* Nothing needed, default is little endian */
    #define ENDIAN_CONVERT64(reg)
    #define ENDIAN_CONVERT32(reg)
    #define ENDIAN_CONVERT16(reg)
#else
    #error Unknown endianness
#endif

    mrs     x0, MIDR_EL1
    ubfx    x0, x0, 4, 12       /* Bits 15:4 are the part number */
    cmp     x0, 0xb0
    b.ge    thunder2_cache_setup

thunder1_cache_setup:
    # Setup L2 to allow secure access to all of the address space
    #define L2C_ASC_REGIONX 0x87E080800000
    #define REGIONX_START   0x1000
    #define REGIONX_END     0x1008
    #define REGIONX_ATTR    0x1010
    mov     x0, L2C_ASC_REGIONX >> 32
    lsl     x0, x0, 32
    mov     x1, (L2C_ASC_REGIONX & 0xffffffff)
    orr     x0, x0, x1
    str     xzr, [x0, REGIONX_START]    /* Start of zero */
    mov     x1, 0x3fffff00000           /* End of max address */
    ENDIAN_CONVERT64(x1)
    str     x1, [x0, REGIONX_END]
    mov     x1, 2                       /* Secure only access */
    ENDIAN_CONVERT64(x1)
    str     x1, [x0, REGIONX_ATTR]
    /* Update way partition to allow core 0 to write to L2 */
    #define L2C_WPAR_PP0_OFFSET 0x40000
    mov     x1, L2C_WPAR_PP0_OFFSET
    str     xzr, [x0, x1]
    ldr     xzr, [x0, x1]       /* Read back to make sure done */
    b       cache_setup_done
    #undef L2C_ASC_REGIONX
    #undef REGIONX_START
    #undef REGIONX_END
    #undef REGIONX_ATTR
    #undef L2C_WPAR_PP0_OFFSET

thunder2_cache_setup:
    # Setup CCS to allow secure access to all of the address space
    #define CCS_ASC_REGIONX 0x87E087100000
    #define CCS_TAD_CTL     0x0018
    # Load the address of CCS_ASC_REGIONX in x0
    mov     x0, CCS_ASC_REGIONX >> 32
    lsl     x0, x0, 32
    mov     x1, (CCS_ASC_REGIONX & 0xffffffff)
    orr     x0, x0, x1
    # Clear CCS_TAD_CTL[frcnalc], bit 45
    ldr     x1, [x0, CCS_TAD_CTL]
    ENDIAN_CONVERT64(x1)
    mov     x2, ~(1<<45)
    and     x1, x1, x2
    ENDIAN_CONVERT64(x1)
    str     x1, [x0, CCS_TAD_CTL]
    # Make sure the CCS updates are complete
    ldr     xzr, [x0, CCS_TAD_CTL]
    b       cache_setup_done
    #undef CCS_ASC_REGIONX
    #undef REGIONX_START
    #undef REGIONX_END
    #undef REGIONX_ATTR
    #undef CCS_TAD_CTL

cache_setup_done:

    /* Get our base link address and store it in x7 */
    adrp    x0, bdk_fs_dev_uart0/* Pick a structure that has a pointer in it */
    ldr     x0, [x0,:lo12:bdk_fs_dev_uart0] /* Read the pointer, which should be at link address */
    and     x7, x0, 0xffffff0000000000 /* Strip off the lower bits */

    /* Check that we're running on the node we're linked for */
    mrs     x0, MPIDR_EL1
    lsr     x1, x7, 40          /* Node we are linked at [41:40] */
    ubfx    x0, x0, 16, 8       /* Bits 23:16 are the physical node ID */
    cmp     x0, x1
    b.ne    __bdk_incorrect_node

    /* Copy 128 bytes at 0x11300 into FP registers. This is to store the
        trusted boot CSIB */
    mov     x0, 0x110000
    add     x0, x0, 0x00300
    ldp     q20, q21, [x0], 32  /* Load CSIB[0:31] */
    ldp     q22, q23, [x0], 32  /* Load CSIB[32:63] */
    ldp     q24, q25, [x0], 32  /* Load CSIB[64:95] */
    ldp     q26, q27, [x0], 32  /* Load CSIB[96:127] */

    /* Relocate ourself if we aren't running at our link address */
    mov     x0, x7              /* x0 = _start location as an absolute */
    adr     x1, _start          /* x1 = _start location based on PC */
    fmov    d29, x1             /* Store our original PC to pass to C code. Useful for detecting trusted boot */
    cmp     x0, x1              /* See if we're running at the right location */
    b.eq    after_relocate      /* Skip relocate if we're already there */
    ldr     w2, [x1, 4]         /* w2 = Image length we need to copy */
    ENDIAN_CONVERT32(w2)
    b       copy_code
    /* Align on a cache line so the entire code copy is in one cache line.
        No Icache misses */
.align 7
copy_code:
    ldp     q0, q1, [x1], 32    /* Load 32 bytes */
    subs    w2, w2, 32          /* Subtract 32 from length, setting flags */
    stp     q0, q1, [x0], 32    /* Store 32 bytes */
    b.gt    copy_code           /* Repeat if length is still positive */
    dmb     sy                  /* Force writes to L2 */

    /* Load the actual location we're suppose to be at */
    adr     x0, after_relocate  /* Relative address */
    adr     x1, _start          /* Relative address */
    sub     x0, x0, x1          /* This only works if _start is suppose to be zero */
    mov     x1, x7              /* X7 is our link address */
    add     x0, x0, x1
    br      x0                  /* Branch to relocated code */

after_relocate:
    ic      ialluis             /* Clear the icache now that all code is correct */

    /* Calculate a CRC32 over the image before C corrupts global variables */
    adr     x10, _start         /* x10 = Address we're CRCing */
    ldr     w1, [x10, 4]        /* w1 = CRC left to do (Image length) */
    ENDIAN_CONVERT32(w1)
    mov     w0, -1              /* w0 is the CRC, init with -1 */
    ldp     x3, x4, [x10]       /* Load first 16 bytes, CRC them */
    ENDIAN_CONVERT64(x3)
    ENDIAN_CONVERT64(x4)
    crc32x  w0, w0, x3
    crc32x  w0, w0, x4
    crc32w  w0, w0, wzr         /* Skip the CRC in the image */
    ldr     w3, [x10, 0x14]     /* Reserved 4 bytes */
    ENDIAN_CONVERT32(w3)
    crc32w  w0, w0, w3
    ldr     x3, [x10, 0x18]     /* Next 8 bytes to get us aligned again */
    ENDIAN_CONVERT64(x3)
    crc32x  w0, w0, x3
    add     x10, x10, 32        /* We've processed 32 bytes */
    sub     w1, w1, 32
crc_loop:
    ldp     x3, x4, [x10], 16   /* Load and CRC next 16 bytes */
    ENDIAN_CONVERT64(x3)
    ENDIAN_CONVERT64(x4)
    sub     w1, w1, 16          /* Update amount left */
    crc32x  w0, w0, x3
    cmp     w1, 16
    crc32x  w0, w0, x4
    bge     crc_loop
    cmp     w1, 8
    b.lt    crc_skip8
    ldr     x3, [x10], 8
    ENDIAN_CONVERT64(x3)
    sub     w1, w1, 8
    crc32x  w0, w0, x3
crc_skip8:
    cmp     w1, 4
    b.lt    crc_skip4
    ldr     w3, [x10], 4
    ENDIAN_CONVERT32(w3)
    sub     w1, w1, 4
    crc32w  w0, w0, w3
crc_skip4:
    cmp     w1, 2
    b.lt    crc_skip2
    ldrh    w3, [x10], 2
    ENDIAN_CONVERT16(w3)
    sub     w1, w1, 2
    crc32h  w0, w0, w3
crc_skip2:
    cbz     w1, crc_done
    ldrb    w3, [x10]
    crc32b  w0, w0, w3
crc_done:
    mvn     w0, w0              /* Result must be inverted */

    /* Store the CSIB in the global __bdk_trust_csib */
    adr     x10, __bdk_trust_csib
    stp     q20, q21, [x10], 32  /* Store CSIB[0:31] */
    stp     q22, q23, [x10], 32  /* Store CSIB[32:63] */
    stp     q24, q25, [x10], 32  /* Store CSIB[64:95] */
    stp     q26, q27, [x10], 32  /* Store CSIB[96:127] */

    /* w0 contains the image CRC */
__bdk_start_cores:
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    /* Change the core to big endian mode for EL3 */
    mrs     x10, SCTLR_EL3
    mov     x11, 1<<25       /* Set SCTLR_EL3[ee]=1 */
    orr     x10, x10, x11
    msr     SCTLR_EL3, x10
#endif
    /* Initialise the stack */
    adr     x10, __bdk_initial_stack_end
    msr     SPSel, 0            /* Use the EL0 stack */
    mov     sp, x10             /* Update the stack */
    /* Lock the stack in case other cores boot */
    adr     x10, __bdk_initial_stack_start
    mov     x12, 1
    sevl
1:  wfe
2:  ldxr    x11, [x10]
    cbnz    x11, 1b
    stxr    w11, x12, [x10]
    cbnz    w11, 2b

    fmov    x1, d30 /* The original X0 is now in X1, info from previous image */
    fmov    x2, d31 /* The original X1 is now in X2, info from previous image */
    fmov    x3, d29 /* The original PC we were loaded at */
    /* Jump to C code */
    bl      __bdk_init
1:  b       1b              /* Infinite loop we should never reach */

__bdk_incorrect_node:
    /* We're on a non-zero node, infinite loop we should never reach */
1:  b       1b

    .macro exception_stub label
    .global __bdk_exception_\label
    .align 7
__bdk_exception_\label:
    b       __bdk_exception2
    .endm

.align 3
__bdk_initial_stack_start:
    .quad   0
.align 12
__bdk_initial_stack_end:

.align 11   /* Must be 2KB aligned */
    exception_stub current_el_sync_sp0
    exception_stub current_el_irq_sp0
    exception_stub current_el_fiq_sp0
    exception_stub current_el_serror_sp0
    exception_stub current_el_sync_spx
    exception_stub current_el_irq_spx
    exception_stub current_el_fiq_spx
    exception_stub current_el_serror_spx
    exception_stub lower_el_sync_sp0
    exception_stub lower_el_irq_sp0
    exception_stub lower_el_fiq_sp0
    exception_stub lower_el_serror_sp0
    exception_stub lower_el_sync_spx
    exception_stub lower_el_irq_spx
    exception_stub lower_el_fiq_spx
    exception_stub lower_el_serror_spx
.align 7
