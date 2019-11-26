/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * Functions for displaying output in libdram. Internal use only.
 */

typedef enum {
    // low 4 bits are verbosity level
    VBL_OFF       =   0, // use this only to init dram_verbosity
    VBL_ALL       =   0, // use this only in VBL_PR() to get printf equiv
    VBL_NORM      =   1,
    VBL_FAE       =   2,
    VBL_TME       =   3,
    VBL_DEV       =   4,
    VBL_DEV2      =   5,
    VBL_DEV3      =   6,
    VBL_DEV4      =   7,
    VBL_NONE      =  15, // use this only in VBL_PR() to get no printing
    // upper 4 bits are special verbosities
    VBL_SEQ       =  16,
    VBL_CSRS      =  32,
    VBL_SPECIAL   =  48,
    // force at least 8 bits for enum
    VBL_LAST      = 255
} dram_verbosity_t;

extern dram_verbosity_t dram_verbosity;

#if 0
#define DEBUG_DEBUG_PRINT 1
#endif

// "level" should be 1-7, or only one of the special bits
// let the compiler optimize the test for verbosity
#define is_verbosity_level(level)   (((level) != 0) && ((int)(dram_verbosity & 0x0f) >= (level)))
#define is_verbosity_special(level) (((int)(dram_verbosity & 0xf0) & (level)) != 0)
#define dram_is_verbose(level)      (((level) & VBL_SPECIAL) ? is_verbosity_special(level) : is_verbosity_level(level))

#define VB_PRT(level, format, ...)         \
    do {                                    \
        if (dram_is_verbose(level))         \
            printf(format, ##__VA_ARGS__);  \
    } while (0)

#define ddr_print(format, ...) VB_PRT(VBL_NORM, format, ##__VA_ARGS__)

#define error_print(format, ...) printf(format, ##__VA_ARGS__)

#ifdef DEBUG_DEBUG_PRINT
    #define debug_print(format, ...) printf(format, ##__VA_ARGS__)
#else
    #define debug_print(format, ...) do {} while (0)
#endif
