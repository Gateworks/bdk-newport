/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * Functions for determining which chip you are running on.
 *
 * <hr>$Revision: 49448 $<hr>
 * @addtogroup chips
 * @{
 */


/* Flag bits in top byte. The top byte of MIDR_EL1 is defined
   as ox43, the Cavium implementer code. In this number, bits
   7,5,4 are defined as zero. We use these bits to signal
   that revision numbers should be ignored. It isn't ideal
   that these are in the middle of an already defined field,
   but this keeps the model numbers as 32 bits */
#define __OM_IGNORE_REVISION        0x80000000
#define __OM_IGNORE_MINOR_REVISION  0x20000000
#define __OM_IGNORE_MODEL           0x10000000

/* Variant, or major pass numbers are stored in bits [23:20] */
#define __OM_PASS_SHIFT             20
#define __OM_PASS_MASK              (0xf << __OM_PASS_SHIFT)

/* Architecture, bits [19:16] are always 0xf */
#define __OM_ARCH_SHIFT             16
#define __OM_ARCH_MASK              (0xf << __OM_ARCH_SHIFT)

/* Partnum is divied into two fields for our chips. Bits [15:8] are the
   processor family. Bits [7:4] are the processor ID */
#define __OM_PARTNUM_SHIFT          4
#define __OM_PARTNUM_MASK           (0xfff << __OM_PARTNUM_SHIFT)
#define __OM_FAMILY_MASK            (0xff0 << __OM_PARTNUM_SHIFT)

/* Minor pass numbers are stored in bits [3:0] */
#define __OM_MINOR_MASK             0xf

/* This define covers the fixed bits that never change across chips. Bits
   [31:24] are the implemntor code (0x43), bits [23:16] are the architecture
   (0xf) */
#define __OM_BASE                   0x430f0000

/* Build a full MIDR_EL1 value from the part number, major, and minor pass
   numbers. Generally people refer to the first chip as pass 1.0, so major needs
   one subtracted */
#define __OM_BUILD(partnum, major, minor)  (__OM_BASE | ((partnum) << __OM_PARTNUM_SHIFT) | ((major - 1) << __OM_PASS_SHIFT) | (minor))

/* Per chip definitions */
#define OCTEONTX_CN83XX_PASS1_0   __OM_BUILD(0xa3, 1, 0)
#define OCTEONTX_CN83XX           (OCTEONTX_CN83XX_PASS1_0 | __OM_IGNORE_REVISION)
#define OCTEONTX_CN83XX_PASS1_X   (OCTEONTX_CN83XX_PASS1_0 | __OM_IGNORE_MINOR_REVISION)

#define OCTEONTX_CN81XX_PASS1_0   __OM_BUILD(0xa2, 1, 0)
#define OCTEONTX_CN81XX           (OCTEONTX_CN81XX_PASS1_0 | __OM_IGNORE_REVISION)
#define OCTEONTX_CN81XX_PASS1_X   (OCTEONTX_CN81XX_PASS1_0 | __OM_IGNORE_MINOR_REVISION)

#define OCTEONTX_CN98XX_PASS1_0   __OM_BUILD(0xb1, 1, 0)
#define OCTEONTX_CN98XX           (OCTEONTX_CN98XX_PASS1_0 | __OM_IGNORE_REVISION)
#define OCTEONTX_CN98XX_PASS1_X   (OCTEONTX_CN98XX_PASS1_0 | __OM_IGNORE_MINOR_REVISION)

#define OCTEONTX_CN96XX_PASS1_0   __OM_BUILD(0xb2, 1, 0) /* Called A0 */
#define OCTEONTX_CN96XX_PASS1_1   __OM_BUILD(0xb2, 1, 1) /* Called A1 and sometimes B0 by mistake */
#define OCTEONTX_CN96XX_PASS3_0   __OM_BUILD(0xb2, 3, 0) /* Called C0 */
#define OCTEONTX_CN96XX           (OCTEONTX_CN96XX_PASS1_0 | __OM_IGNORE_REVISION)
#define OCTEONTX_CN96XX_PASS1_X   (OCTEONTX_CN96XX_PASS1_0 | __OM_IGNORE_MINOR_REVISION)
#define OCTEONTX_CN96XX_PASS3_X   (OCTEONTX_CN96XX_PASS3_0 | __OM_IGNORE_MINOR_REVISION)

#define OCTEONTX_CNF95XX_PASS1_0  __OM_BUILD(0xb3, 1, 0) /* Called A0 */
#define OCTEONTX_CNF95XX_PASS2_0  __OM_BUILD(0xb3, 2, 0) /* Called B0 */
#define OCTEONTX_CNF95XX          (OCTEONTX_CNF95XX_PASS1_0 | __OM_IGNORE_REVISION)
#define OCTEONTX_CNF95XX_PASS1_X  (OCTEONTX_CNF95XX_PASS1_0 | __OM_IGNORE_MINOR_REVISION)
#define OCTEONTX_CNF95XX_PASS2_X  (OCTEONTX_CNF95XX_PASS2_0 | __OM_IGNORE_MINOR_REVISION)

#define OCTEONTX_LOKI_PASS1_0     __OM_BUILD(0xb4, 1, 0) /* Called A0 */
#define OCTEONTX_LOKI             (OCTEONTX_LOKI_PASS1_0 | __OM_IGNORE_REVISION)
#define OCTEONTX_LOKI_PASS1_X     (OCTEONTX_LOKI_PASS1_0 | __OM_IGNORE_MINOR_REVISION)

/* These match entire families of chips */
#define OCTEONTX_CN8XXX           (OCTEONTX_CN83XX_PASS1_0 | __OM_IGNORE_MODEL)
#define OCTEONTX_CN9XXX           (OCTEONTX_CN96XX_PASS1_0 | __OM_IGNORE_MODEL)

/* CN96XX part number is reused in a number of different chips, which are
   handled in the BDK as alternate packages. These constants represent the
   possible alternate package codes */
/* These are for CN96XX pass Ax and Bx */
#define OCTEONTX_ALT_CN96XX          0 /* (A) 50mm pkg, 3 DDR, default */
#define OCTEONTX_ALT_CN93XX          1 /* (B) 42.5mm pkg, 2 DDR, 4 lanes ethernet */
#define OCTEONTX_ALT_CN93XXC         2 /* (C) 42.5mm pkg, 2 DDR, 8 lanes ethernet */
#define OCTEONTX_ALT_CN95XXE         3 /* (D) 45mm pkg, 2 DDR, CN95XXE */
#define OCTEONTX_ALT_CN96XXH         7 /* (H) 50mm pkg, Cx compatible for pass A */
/* These are for CN96XX pass Cx */
#define OCTEONTX_ALT_CN93XXJ         (8+1) /* (J) 42.5mm pkg, 2 DDR, 4 lanes ethernet */
#define OCTEONTX_ALT_CN96XXM         (8+4) /* (M) 50mm pkg, Ax compatible */
#define OCTEONTX_ALT_CN96XXP         (8+7) /* (P) 50mm pkg, 3 DDR, TBD */

static inline uint64_t bdk_get_model() __attribute__ ((pure, always_inline));
static inline uint64_t bdk_get_model()
{
#ifdef BDK_REMOTE_GET_MODEL
    return BDK_REMOTE_GET_MODEL;
#elif defined(BDK_BUILD_HOST)
    extern uint32_t thunder_remote_get_model(void) __attribute__ ((pure));
    return thunder_remote_get_model();
#else
    uint64_t result;
    asm ("mrs %[rd],MIDR_EL1" : [rd] "=r" (result));
    return result;
#endif
}

/**
 * Return non-zero if the chip matech the passed model.
 *
 * @param arg_model One of the OCTEONTX_* constants for chip models and
 *                  passes
 *
 * @return Non-zero if match
 */
static inline int bdk_is_model(uint32_t arg_model) __attribute__ ((pure, always_inline));
static inline int bdk_is_model(uint32_t arg_model)
{
    /* Note that the model matching here is unaffected by
       MIO_FUS_FUSE_NUM_E::CHIP_IDX bits 6-7, which are the alternate package
       fuses. These bits don't affect MIDR_EL1, so:
            CN80XX will match CN81XX (CHIP_IDX 6 is set for 676 ball package)
            CN80XX will match CN81XX (CHIP_IDX 7 is set for 555 ball package)
       Alternate package parts are detected using MIO_FUS_DAT2[chip_id],
       specifically the upper two bits */

    uint32_t my_model = bdk_get_model();
    uint32_t mask;

    if (arg_model & __OM_IGNORE_MODEL)
        mask = __OM_FAMILY_MASK; /* Matches chip generation (CN8XXX, CN9XXX) */
    else if (arg_model & __OM_IGNORE_REVISION)
        mask = __OM_PARTNUM_MASK; /* Matches chip model (CN81XX, CN83XX) */
    else if (arg_model & __OM_IGNORE_MINOR_REVISION)
        mask = __OM_PARTNUM_MASK | __OM_PASS_MASK; /* Matches chip model and major version */
    else
        mask = __OM_PARTNUM_MASK | __OM_PASS_MASK | __OM_MINOR_MASK; /* Matches chip model, major version, and minor version */

    return ((arg_model & mask) == (my_model & mask));
}

/**
 * Return non-zero if the die is in an alternate package. The
 * normal is_model() checks will treat alternate package parts
 * as all the same, where this function can be used to detect
 * them. The return value is the upper two bits of
 * MIO_FUS_DAT2[chip_id]. Most alternate packages use bit 6,
 * which will return 1 here. Parts with a second alternative
 * will use bit 7, which will return 2.
 *
 * @param arg_model One of the OCTEONTX_* constants for chip models and
 *                  passes
 *
 * @return Non-zero if an alternate package
 *         0 = Normal package
 *         1 = Alternate package 1 (CN86XX, CN80XX with 555 balls)
 *         2 = Alternate package 2 (CN80XX with 676 balls)
 *         3 = Alternate package 3 (Currently unused)
 */
extern int bdk_is_altpkg(uint32_t arg_model);

#define BDK_MODEL_MAX_SKU 32 /* Maximum length of SKU is 31 plus zero terminator */

/**
 * Return the SKU string for a chip
 *
 * @param node   Node to get SKU for
 *
 * @return Chip's SKU
 */
extern const char* bdk_model_get_sku(int node);

/** @} */
