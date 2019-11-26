/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
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

/**
 * Perform a crc32 on the supplied data
 *
 * @param ptr    Data to CRC (x0)
 * @param len    Length of the data (x1)
 * @param iv     Starting IV (w2)
 *
 * @return Result, can be used in IV to continue later. (w0)
 */
    .section .text
    .global bdk_crc32
bdk_crc32:
    mov     x10, x0             /* Move pointer to x10 */
    mov     x11, x1             /* Move Length left to x11 */
    mvn     w0, w2              /* CRC starts with ~iv */
    cmp     x11, 128
    b.lt    crc_skip128
crc_128b:
    prfum   pldl1keep,[x10,128] /* Assume large, prefetch next cache line */
    ldp     x12,x13,[x10, 16 * 0]
    ENDIAN_CONVERT64(x12)
    ENDIAN_CONVERT64(x13)
    ldp     x14,x15,[x10, 16 * 1]
    ENDIAN_CONVERT64(x14)
    ENDIAN_CONVERT64(x15)
    ldp     x16,x17,[x10, 16 * 2]
    ENDIAN_CONVERT64(x16)
    ENDIAN_CONVERT64(x17)
    crc32x  w0, w0, x12
    crc32x  w0, w0, x13
    ldp     x12,x13,[x10, 16 * 3]
    ENDIAN_CONVERT64(x12)
    ENDIAN_CONVERT64(x13)
    crc32x  w0, w0, x14
    crc32x  w0, w0, x15
    ldp     x14,x15,[x10, 16 * 4]
    ENDIAN_CONVERT64(x14)
    ENDIAN_CONVERT64(x15)
    crc32x  w0, w0, x16
    crc32x  w0, w0, x17
    ldp     x16,x17,[x10, 16 * 5]
    ENDIAN_CONVERT64(x16)
    ENDIAN_CONVERT64(x17)
    crc32x  w0, w0, x12
    crc32x  w0, w0, x13
    ldp     x12,x13,[x10, 16 * 6]
    ENDIAN_CONVERT64(x12)
    ENDIAN_CONVERT64(x13)
    crc32x  w0, w0, x14
    crc32x  w0, w0, x15
    ldp     x14,x15,[x10, 16 * 7]
    ENDIAN_CONVERT64(x14)
    ENDIAN_CONVERT64(x15)
    add     x10, x10, 128       /* Increment our pointer */
    crc32x  w0, w0, x16
    sub     x11, x11, 128       /* Shrink length by 128 bytes */
    crc32x  w0, w0, x17
    cmp     x11, 128            /* Less than 128 bytes left? */
    crc32x  w0, w0, x12
    crc32x  w0, w0, x13
    crc32x  w0, w0, x14
    crc32x  w0, w0, x15
    b.ge    crc_128b
crc_skip128:
    cmp     x11, 16             /* Less than 16 bytes left? */
    b.lt    crc_skip16
1:  ldp     x12,x13,[x10],16
    ENDIAN_CONVERT64(x12)
    ENDIAN_CONVERT64(x13)
    sub     x11, x11, 16        /* Shrink length by 16 bytes */
    crc32x  w0, w0, x12
    cmp     x11, 16             /* Less than 16 bytes left? */
    crc32x  w0, w0, x13
    b.ge    1b
crc_skip16:
    cmp     x11, 8              /* Less than 8 bytes left? */
    b.lt    crc_skip8
    ldr     x12,[x10],8
    ENDIAN_CONVERT64(x12)
    sub     x11, x11, 8         /* Shrink length by 8 bytes */
    crc32x  w0, w0, x12
crc_skip8:
    cmp     x11, 4              /* Less than 4 bytes left? */
    b.lt    crc_skip4
    ldr     w12,[x10],4
    ENDIAN_CONVERT32(w12)
    sub     x11, x11, 4         /* Shrink length by 4 bytes */
    crc32w  w0, w0, w12
crc_skip4:
    cmp     x11, 2              /* Less than 2 bytes left? */
    b.lt    crc_skip2
    ldrh    w12,[x10],2
    ENDIAN_CONVERT16(w12)
    sub     x11, x11, 2         /* Shrink length by 2 bytes */
    crc32h  w0, w0, w12
crc_skip2:
    cbz     x11, crc_done       /* Do we have one byte left? */
    ldrb    w12,[x10]
    crc32b  w0, w0, w12
crc_done:
    mvn     w0, w0              /* CRC must be inverted */
    ret

