/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-ap.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"
#include "libbdk-arch/bdk-csrs-fus.h"
#include "libbdk-arch/bdk-csrs-fusf.h"
#include "libbdk-arch/bdk-csrs-gpio.h"

/*
    Format of a SKU
    CN8890-2000BG2601-AAP-G
    CN8890-2000BG2601-AAP-PR-Y-G
    CN XX XX X - XXX BG XXX - XX (- XX) (- X) - G
    |  |  |  |   |   |  |     |     |      |    ^ RoHS Option, G=RoHS 6/6
    |  |  |  |   |   |  |     |     |      ^ Product Revision, blank for pass 1, Y=pass 2, W=pass 3, V=pass 4
    |  |  |  |   |   |  |     |     ^ Product Phase, blank=production, PR=Prototype, ES=Engineering Sample
    |  |  |  |   |   |  |     ^ Marketing Segment Option (SC, SNT, etc)
    |  |  |  |   |   |  ^ Number of balls on the package
    |  |  |  |   |   ^ Ball Grid Array
    |  |  |  |   ^ Frequency in Mhz, 3 or 4 digits (300 - 2000)
    |  |  |  ^ Optional Customer Code, blank or A-Z, never supported
    |  |  ^ Number of cores, see table below
    |  ^ Processor family, plus or minus for L2 sizes and such (88, 86, 83, 81, 80)
    ^ Cavium Prefix, sometimes changed for customer specific parts

    Table of Core to Model encoding
        >= 48 shows xx90
        >= 44 shows xx88
        >= 42 shows xx85
        >= 32 shows xx80
        >= 24 shows xx70
        >= 20 shows xx65
        >= 16 shows xx60
        = 15 shows xx58
        = 14 shows xx55
        = 13 shows xx52
        = 12 shows xx50
        = 11 shows xx48
        = 10 shows xx45
        = 9 shows xx42
        = 8 shows xx40
        = 7 shows xx38
        = 6 shows xx34
        = 5 shows xx32
        = 4 shows xx30
        = 3 shows xx25
        = 2 shows xx20
        = 1 shows xx10
    Special Check: t81 in 555 pin package ends with 1 instead of 0. See
    fixup later in code.
*/

/* Definition of each SKU table entry for the different dies */
typedef struct
{
    uint8_t     fuse_index; /* Index programmed into PNAME fuses to match this entry. Must never change once fused parts ship */
    const char  prefix[4];  /* Prefix before model number, usually "CN". Third letter is customer code shown after the model */
    uint8_t     model_base; /* First two digits of the model number */
    uint16_t    num_balls;  /* Number of balls on package, included in SKU */
    const char  segment[4]; /* Market segment SKU is for, 2-3 character string */
    uint16_t    fuses[12];  /* List of fuses required for operation of this SKU */
} model_sku_info_t;

/* In the model_sku_info_t.fuses[] array, we use a special value
   FUSES_CHECK_FUSF to represent that we need to check FUSF_CTL bit
   6, checking for trusted boot */
#define FUSES_CHECK_FUSF 0xffff

/***************************************************/
/* SKU table for t83 */
/* From "Thunder Part Number fuse overview Rev 16.xlsx" */
/***************************************************/
static const model_sku_info_t t83_sku_info[] =
{
    /* Index zero reserved for no fuses programmed */
    { 0x01, "CN", 83, 1676, "SCP", /* 24, 20, 16, 12, 8 cores */
        { /* List of fuses for this SKU */
            0 /* End of fuse list marker */
        }
    },
    { 0x02, "CN", 83, 1676, "CP", /* 24, 20, 16, 12, 8 cores */
        { /* List of fuses for this SKU */
            /* Disable all Nitrox cores, CPT0 and CPT1 */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(0), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(1), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(2), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(3), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(4), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(5), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(6), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(7), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(8), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(9), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(10), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(11), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(12), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(13), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(14), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(15), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(16), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(17), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(18), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(19), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(20), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(21), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(22), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(23), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(24), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(25), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(26), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(27), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(28), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(29), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(30), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(31), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(32), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(33), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(34), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(35), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(36), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(37), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(38), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(39), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(40), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(41), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(42), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(43), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(44), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(45), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(46), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(47), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(0), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(1), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(2), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(3), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(4), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(5), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(6), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(7), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(8), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(9), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(10), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(11), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(12), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(13), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(14), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(15), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(16), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(17), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(18), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(19), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(20), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(21), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(22), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(23), /* Nitrox */
            0 /* End of fuse list marker */
        }
    },
    { 0x03, "CN", 83, 1676, "AUS", /* 24, 20, 16, 12, 8 cores */
        { /* List of fuses for this SKU */
            FUSES_CHECK_FUSF, /* Trusted boot */
            0 /* End of fuse list marker */
        }
    },
    { 0x04, "CN", 82, 1676, "SCP", /* 12, 8 cores */
        { /* List of fuses for this SKU */
            BDK_MIO_FUS_FUSE_NUM_E_L2C_CRIPX(1),/* L2C is half size */
            BDK_MIO_FUS_FUSE_NUM_E_LMC_DIS, /* Disable upper LMC */
            /* Disable Nitrox cores CPT0[24-47] and CPT1[12-23] */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(24), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(25), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(26), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(27), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(28), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(29), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(30), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(31), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(32), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(33), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(34), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(35), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(36), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(37), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(38), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(39), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(40), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(41), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(42), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(43), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(44), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(45), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(46), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(47), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(12), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(13), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(14), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(15), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(16), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(17), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(18), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(19), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(20), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(21), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(22), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(23), /* Nitrox */
            0 /* End of fuse list marker */
        }
    },
    { 0x05, "CN", 82, 1676, "CP", /* 12, 8 cores */
        { /* List of fuses for this SKU */
            BDK_MIO_FUS_FUSE_NUM_E_L2C_CRIPX(1),/* L2C is half size */
            BDK_MIO_FUS_FUSE_NUM_E_LMC_DIS, /* Disable upper LMC */
            /* Disable all Nitrox cores, CPT0 and CPT1 */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(0), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(1), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(2), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(3), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(4), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(5), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(6), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(7), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(8), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(9), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(10), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(11), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(12), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(13), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(14), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(15), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(16), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(17), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(18), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(19), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(20), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(21), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(22), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(23), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(24), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(25), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(26), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(27), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(28), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(29), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(30), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(31), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(32), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(33), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(34), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(35), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(36), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(37), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(38), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(39), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(40), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(41), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(42), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(43), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(44), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(45), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(46), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT0_ENG_DISX(47), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(0), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(1), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(2), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(3), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(4), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(5), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(6), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(7), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(8), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(9), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(10), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(11), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(12), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(13), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(14), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(15), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(16), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(17), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(18), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(19), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(20), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(21), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(22), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT1_ENG_DISX(23), /* Nitrox */
            0 /* End of fuse list marker */
        }
    },
    {} /* End of SKU list marker */
};

/***************************************************/
/* SKU table for t81 */
/* From "Thunder Part Number fuse overview Rev 16.xlsx" */
/***************************************************/
static const model_sku_info_t t81_sku_info[] =
{
    /* Index zero reserved for no fuses programmed */
    { 0x01, "CN", 81, 676, "SCP", /* 4, 2 cores */
        { /* List of fuses for this SKU */
            /* No fuses */
            0 /* End of fuse list marker */
        }
    },
    { 0x02, "CN", 81, 676, "CP", /* 4, 2 cores */
        { /* List of fuses for this SKU */
            BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(1), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(2), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(3), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(4), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(5), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(6), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(7), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(8), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(9), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(10), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(11), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(12), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(13), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(14), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(15), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(16), /* Nitrox */
            0 /* End of fuse list marker */
        }
    },
    { 0x07, "CN", 81, 676, "AUS", /* 4, 2 cores */
        { /* List of fuses for this SKU */
            FUSES_CHECK_FUSF, /* Trusted boot */
            0 /* End of fuse list marker */
        }
    },
    { 0x08, "CN", 81, 676, "AUC", /* 4, 2 cores */
        { /* List of fuses for this SKU */
            FUSES_CHECK_FUSF, /* Trusted boot */
            BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(1), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(2), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(3), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(4), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(5), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(6), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(7), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(8), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(9), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(10), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(11), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(12), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(13), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(14), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(15), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(16), /* Nitrox */
            0 /* End of fuse list marker */
        }
    },
    { 0x03, "CN", 80, 676, "SCP", /* 4, 2 cores */
        { /* List of fuses for this SKU */
            /* Note that CHIP_ID(7) is suppose to be blown, but a few chips
               have incorrect fuses. We allow CN80XX SKUs with or without
               CHIP_ID(7) */
            //BDK_MIO_FUS_FUSE_NUM_E_CHIP_IDX(7),     /* Alternate package fuse 2? */
            BDK_MIO_FUS_FUSE_NUM_E_L2C_CRIPX(1),    /* L2C is half size */
            BDK_MIO_FUS_FUSE_NUM_E_LMC_HALF,        /* LMC is half width */
            0 /* End of fuse list marker */
        }
    },
    { 0x04, "CN", 80, 676, "CP", /* 4, 2 cores */
        { /* List of fuses for this SKU */
            /* Note that CHIP_ID(7) is suppose to be blown, but a few chips
               have incorrect fuses. We allow CN80XX SKUs with or without
               CHIP_ID(7) */
            //BDK_MIO_FUS_FUSE_NUM_E_CHIP_IDX(7),     /* Alternate package fuse 2? */
            BDK_MIO_FUS_FUSE_NUM_E_L2C_CRIPX(1),    /* L2C is half size */
            BDK_MIO_FUS_FUSE_NUM_E_LMC_HALF,        /* LMC is half width */
            BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(1), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(2), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(3), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(4), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(5), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(6), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(7), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(8), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(9), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(10), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(11), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(12), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(13), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(14), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(15), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(16), /* Nitrox */
            0 /* End of fuse list marker */
        }
    },
    { 0x05, "CN", 80, 555, "SCP", /* 4, 2 cores */
        { /* List of fuses for this SKU */
            BDK_MIO_FUS_FUSE_NUM_E_CHIP_IDX(6),     /* Alternate package fuse */
            BDK_MIO_FUS_FUSE_NUM_E_L2C_CRIPX(1),    /* L2C is half size */
            BDK_MIO_FUS_FUSE_NUM_E_LMC_HALF,        /* LMC is half width */
            0 /* End of fuse list marker */
        }
    },
    { 0x06, "CN", 80, 555, "CP", /* 4, 2 cores */
        { /* List of fuses for this SKU */
            BDK_MIO_FUS_FUSE_NUM_E_CHIP_IDX(6),     /* Alternate package fuse */
            BDK_MIO_FUS_FUSE_NUM_E_L2C_CRIPX(1),    /* L2C is half size */
            BDK_MIO_FUS_FUSE_NUM_E_LMC_HALF,        /* LMC is half width */
            BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(1), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(2), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(3), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(4), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(5), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(6), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(7), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(8), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(9), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(10), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(11), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(12), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(13), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(14), /* Nitrox */
            //BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(15), /* Nitrox */
            BDK_MIO_FUS_FUSE_NUM_E_CPT_ENG_DISX(16), /* Nitrox */
            0 /* End of fuse list marker */
        }
    },
    { 0x07, "CN", 80, 555, "AUS", /* 4 cores */
        { /* List of fuses for this SKU */
            FUSES_CHECK_FUSF, /* Trusted boot */
            BDK_MIO_FUS_FUSE_NUM_E_CHIP_IDX(6),     /* Alternate package fuse */
            BDK_MIO_FUS_FUSE_NUM_E_L2C_CRIPX(1),    /* L2C is half size */
            BDK_MIO_FUS_FUSE_NUM_E_LMC_HALF,        /* LMC is half width */
            0 /* End of fuse list marker */
        }
    },
    { 0x08, "CN", 80, 676, "AUS", /* 4 cores */
        { /* List of fuses for this SKU */
            FUSES_CHECK_FUSF, /* Trusted boot */
            BDK_MIO_FUS_FUSE_NUM_E_L2C_CRIPX(1),    /* L2C is half size */
            BDK_MIO_FUS_FUSE_NUM_E_LMC_HALF,        /* LMC is half width */
            0 /* End of fuse list marker */
        }
    },
    {} /* End of SKU list marker */
};

/**
 * Given a core count, return the last two digits of a model number
 *
 * @param cores  Number of cores
 *
 * @return Two digit model number
 */
static int model_digits_for_cores(int cores)
{
    /* If the number of cores is between two model levels, use the lower
       level. This assumes that a model guarantees a minimum number of
       cores. This should never happen, but you never know */
    switch (cores)
    {
        case  1: return 10; /* CNxx10 = 1 core */
        case  2: return 20; /* CNxx20 = 2 cores */
        case  3: return 25; /* CNxx25 = 3 cores */
        case  4: return 30; /* CNxx30 = 4 cores */
        case  5: return 32; /* CNxx32 = 5 cores */
        case  6: return 34; /* CNxx34 = 6 cores */
        case  7: return 38; /* CNxx38 = 7 cores */
        case  8: return 40; /* CNxx40 = 8 cores */
        case  9: return 42; /* CNxx42 = 9 cores */
        case 10: return 45; /* CNxx45 = 10 cores */
        case 11: return 48; /* CNxx48 = 11 cores */
        case 12: return 50; /* CNxx50 = 12 cores */
        case 13: return 52; /* CNxx52 = 13 cores */
        case 14: return 55; /* CNxx55 = 14 cores */
        case 15: return 58; /* CNxx58 = 15 cores */
        case 16 ... 19: return 60; /* CNxx60 = 16 cores */
        case 20 ... 23: return 65; /* CNxx65 = 20 cores */
        case 24 ... 31: return 70; /* CNxx70 = 24 cores */
        case 32 ... 39: return 80; /* CNxx80 = 32 cores */
        case 40 ... 43: return 85; /* CNxx85 = 40 cores */
        case 44 ... 47: return 88; /* CNxx88 = 44 cores */
        default: return 90; /* CNxx90 = 48 cores */
    }
}

/**
 * Return the SKU string for a CN8XXX chip
 *
 * @param node     Node to get SKU for
 * @param chip_sku String to fill with the SKU
 */
void __bdk_model_get_sku_cn8xxx(int node, char *chip_sku)
{
    /* Figure out which SKU list to use */
    const model_sku_info_t *sku_info;
    uint64_t result;
    asm ("mrs %[rd],MIDR_EL1" : [rd] "=r" (result));
    result = bdk_extract(result, 4, 12);
    switch (result)
    {
        case 0xa2:
            sku_info = t81_sku_info;
            break;
        case 0xa3:
            sku_info = t83_sku_info;
            break;
        default:
            bdk_fatal("SKU detect: Unknown die\n");
    }

    int match_index = 0;
    int match_score = -1;
    int index = 0;
    while (sku_info[index].fuse_index)
    {
        int score = 0;
        int fuse_index = 0;
        /* Count the number of fuses that match. A mismatch forces the worst
           score (-1) */
        while (sku_info[index].fuses[fuse_index])
        {
            int fuse;
            /* FUSES_CHECK_FUSF is special for trusted parts */
            if (sku_info[index].fuses[fuse_index] == FUSES_CHECK_FUSF)
            {
                BDK_CSR_INIT(fusf_ctl, node, BDK_FUSF_CTL);
                fuse = (fusf_ctl.u >> 6) & 1;
            }
            else
            {
                fuse = bdk_fuse_read(node, sku_info[index].fuses[fuse_index]);
            }
            if (fuse)
            {
                /* Match, improve the score */
                score++;
            }
            else
            {
                /* Mismatch, force score bad */
                score = -1;
                break;
            }
            fuse_index++;
        }
        /* If this score is better than the last match, use this index as the
           match */
        if (score > match_score)
        {
            match_score = score;
            match_index = index;
        }
        index++;
    }

    /* Use the SKU table to determine the defaults for the SKU parts */
    const char *prefix          = sku_info[match_index].prefix;
    int         model           = 100 * sku_info[match_index].model_base;
    int         cores           = bdk_get_num_cores(node);
    const char *customer_code   = "";
    int         rclk_limit      = bdk_clock_get_rate(node, BDK_CLOCK_RCLK) / 1000000;
    const char *bg_str          = "BG"; /* Default Ball Grid array */
    int         balls           = sku_info[match_index].num_balls; /* Num package balls */
    const char *segment         = sku_info[match_index].segment; /* Market segment */
    char prod_phase[4];         /* Blank = production, PR = Prototype, ES = Engineering sample */
    char prod_rev[5];           /* Product revision */
    const char *rohs_option     = "G"; /* RoHS is always G for current parts */

    /* Update the model number with the number of cores */
    model = (model / 100) * 100 + model_digits_for_cores(cores);

    /* Update the RCLK setting based on MIO_FUS_DAT3[core_pll_mul] */
    uint64_t core_pll_mul;
    BDK_CSR_INIT(mio_fus_dat3, node, BDK_MIO_FUS_DAT3);
    core_pll_mul = mio_fus_dat3.s.core_pll_mul;

    if (core_pll_mul)
    {
        /* CORE_PLL_MUL covers bits 5:1, so we need to multiple by 2. The
           documentation doesn't mention this clearly: There is a 300Mhz
           addition to the base multiplier */
        rclk_limit = core_pll_mul * 2 * 50 + 300;
    }

    /* Hardcode production as there is no way to tell */
    prod_phase[0] = 0;

    /* Read the Pass information from fuses. Note that pass info in
       MIO_FUS_DAT2[CHIP_ID] is encoded as
            bit[7] = Unused, zero
            bit[6] = Alternate package
            bit[5..3] = Major pass
            bit[2..0] = Minor pass */
    BDK_CSR_INIT(mio_fus_dat2, node, BDK_MIO_FUS_DAT2);
    int major_pass = ((mio_fus_dat2.s.chip_id >> 3) & 7) + 1;
    int minor_pass = mio_fus_dat2.s.chip_id & 7;

    if (major_pass == 1)
    {
        /* Pass 1.x is special in that we don't show the implied 'X' */
        if (minor_pass == 0)
        {
            /* Completely blank for 1.0 */
            prod_rev[0] = 0;
        }
        else
        {
            /* If we are production and not pass 1.0, the product phase
               changes from blank to "-P". The product revision then
               follows the product phase without a '-' */
            if (prod_phase[0] == 0)
            {
                /* Change product phase to "-P" */
                prod_phase[0] = '-';
                prod_phase[1] = 'P';
                prod_phase[2] = 0;
            }
            /* No separator between phase and revision */
            prod_rev[0] = '1';
            prod_rev[1] = '0' + minor_pass;
            prod_rev[2] = 0;
        }
    }
    else
    {
        /* Pass 2.0 and above        12345678 */
        const char pass_letter[8] = "XYWVUTSR";
        prod_rev[0] = '-';
        prod_rev[1] = pass_letter[major_pass-1];
        if (minor_pass == 0)
        {
            /* Nothing after the letter code */
            prod_rev[2] = 0;
        }
        else
        {
            /* Add major and minor after the letter code */
            prod_rev[2] = '0' + major_pass;
            prod_rev[3] = '0' + minor_pass;
            prod_rev[4] = 0;
        }
    }

    /* Special check alert: The part numbers for t81 in alternate
       package 1 (555 pins) all end in "1" instead of the normal "0".
       Marketing didn't follow the CPU number standard, so we hack it
       here */
    if (bdk_is_altpkg(OCTEONTX_CN81XX) == 1)
        model++;

    /* Build the SKU string */
    snprintf(chip_sku, BDK_MODEL_MAX_SKU, "%s%d%s-%d%s%d-%s%s%s-%s",
        prefix, model, customer_code, rclk_limit, bg_str, balls, segment,
        prod_phase, prod_rev, rohs_option);
}
