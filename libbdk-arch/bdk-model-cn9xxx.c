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

/* Format of a SKU
    CN9760EX-2000xyA-SCP-A0-G
    CN XX XX (XX) - #### xyX - XXX - XX - G
    |  |  |  |      |    |||   |     ||   ^ RoHS Option, G=RoHS 6/6
    |  |  |  |      |    |||   |     |^ Product Minor Revision, '0', '1', etc.
    |  |  |  |      |    |||   |     ^ Product Major Revision, 'A', 'B', etc.
    |  |  |  |      |    |||   ^ Marketing Segment Option ("CP", "SCP", etc)
    |  |  |  |      |    ||^ Package letter code, GPIO_PKG_VER[PKG_VER] + 'A'
    |  |  |  |      |    |^ SCLK speed variations, shown as "y" for wildcard
    |  |  |  |      |    ^ Power letter code, shown as "x" for wildcard
    |  |  |  |      ^ Frequency in Mhz, 3 or 4 digits (500 - 3000)
    |  |  |  ^ Optional 2 character product suffix
    |  |  ^ Number of cores, see model_digits_for_cores()
    |  ^ Processor family, plus or minus for L2 sizes and such (96, 95, 93, 92)
    ^ Cavium Prefix (CN, CNF), sometimes changed for customer specific parts */

/* Definition of each SKU table entry for the different dies */
typedef struct
{
    const char      prefix[4];  /* Prefix before model number, usually "CN" */
    const uint8_t   model_base; /* First two digits of the model number */
    const char      segment[4]; /* Market segment SKU is for, 2-3 character string */
    const uint16_t  fuses[12];  /* List of fuses required for operation of this SKU */
} model_sku_info_t;

/* In the model_sku_info_t.fuses[] array, we use a special value
   FUSES_CHECK_FUSF to represent that we need to check FUSF_CTL bit
   6, checking for trusted boot */
#define FUSES_CHECK_FUSF 0xffff

/***************************************************/
/* SKU table for t96/t93 */
/***************************************************/
static const model_sku_info_t t96_sku_info[] =
{
    /* Index zero reserved for no fuses programmed */
    { "CN", 96, "SCP", /* 24, 18 cores */
        { /* List of fuses for this SKU */
            /* No fuses */
            0 /* End of fuse list marker */
        }
    },
    { "CN", 96, "CP", /* 24, 18 cores */
        { /* List of fuses for this SKU */
            BDK_FUS_FUSE_NUM_E_CPT0_NOCRYPTOX(0),
            0 /* End of fuse list marker */
        }
    },
    { "CN", 96, "AUS", /* 24, 18 cores */
        { /* List of fuses for this SKU */
            FUSES_CHECK_FUSF, /* Trusted boot */
            0 /* End of fuse list marker */
        }
    },
    { "CN", 93, "SCP", /* 18, 12 cores */
        { /* List of fuses for this SKU */
            BDK_FUS_FUSE_NUM_E_LLC_CRIPPLEX(0),
            0 /* End of fuse list marker */
        }
    },
    { "CN", 93, "CP", /* 18, 12 cores */
        { /* List of fuses for this SKU */
            BDK_FUS_FUSE_NUM_E_LLC_CRIPPLEX(0),
            BDK_FUS_FUSE_NUM_E_CPT0_NOCRYPTOX(0),
            0 /* End of fuse list marker */
        }
    },
    { "CN", 93, "AUS", /* 18, 12 cores */
        { /* List of fuses for this SKU */
            BDK_FUS_FUSE_NUM_E_LLC_CRIPPLEX(0),
            FUSES_CHECK_FUSF, /* Trusted boot */
            0 /* End of fuse list marker */
        }
    },
    { "CN", 92, "SCP", /* 12 cores */
        { /* List of fuses for this SKU */
            BDK_FUS_FUSE_NUM_E_LLC_CRIPPLEX(1),
            0 /* End of fuse list marker */
        }
    },
    { "CN", 92, "CP", /* 12 cores */
        { /* List of fuses for this SKU */
            BDK_FUS_FUSE_NUM_E_LLC_CRIPPLEX(1),
            BDK_FUS_FUSE_NUM_E_CPT0_NOCRYPTOX(0),
            0 /* End of fuse list marker */
        }
    },
    { "CN", 92, "AUS", /* 12 cores */
        { /* List of fuses for this SKU */
            BDK_FUS_FUSE_NUM_E_LLC_CRIPPLEX(1),
            FUSES_CHECK_FUSF, /* Trusted boot */
            0 /* End of fuse list marker */
        }
    },
    { "CN", 95, "ENG", /* 6 cores */
        { /* List of fuses for this SKU */
            /* No fuses */
            0 /* End of fuse list marker */
        }
    },
    {} /* End of SKU list marker */
};

/***************************************************/
/* SKU table for f95 */
/***************************************************/
static const model_sku_info_t f95_sku_info[] =
{
    /* Index zero reserved for no fuses programmed */
    { "CNF", 95, "SCP", /* 6 cores */
        { /* List of fuses for this SKU */
            /* No fuses */
            0 /* End of fuse list marker */
        }
    },
    {} /* End of SKU list marker */
};

/***************************************************/
/* SKU table for LOKI */
/***************************************************/
static const model_sku_info_t loki_sku_info[] =
{
    /* Index zero reserved for no fuses programmed */
    { "LOK", 95, "SCP", /* 6 cores */
        { /* List of fuses for this SKU */
            /* No fuses */
            0 /* End of fuse list marker */
        }
    },
    {} /* End of SKU list marker */
};

/***************************************************/
/* SKU table for CN98XX */
/***************************************************/
static const model_sku_info_t t98_sku_info[] =
{
    /* Index zero reserved for no fuses programmed */
    { "CN", 98, "SCP", /* 6 cores */
        { /* List of fuses for this SKU */
            /* No fuses */
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
        case  6: return 35; /* CNxx35 = 6 cores */
        case  7: return 38; /* CNxx38 = 7 cores */
        case  8: return 40; /* CNxx40 = 8 cores */
        case  9: return 42; /* CNxx42 = 9 cores */
        case 10: return 45; /* CNxx45 = 10 cores */
        case 11: return 48; /* CNxx48 = 11 cores */
        case 12: return 50; /* CNxx50 = 12 cores */
        case 13: return 52; /* CNxx52 = 13 cores */
        case 14: return 55; /* CNxx55 = 14 cores */
        case 15: return 58; /* CNxx58 = 15 cores */
        case 16 ... 17: return 60; /* CNxx60 = 16 cores */
        case 18 ... 23: return 65; /* CNxx65 = 20 cores */
        case 24 ... 31: return 70; /* CNxx70 = 24 cores */
        case 32 ... 39: return 80; /* CNxx80 = 32 cores */
        case 40 ... 43: return 85; /* CNxx85 = 40 cores */
        case 44 ... 47: return 88; /* CNxx88 = 44 cores */
        default: return 90; /* CNxx90 = 48 cores */
    }
}

/**
 * Return the SKU string for a CN9XXX chip
 *
 * @param node     Node to get SKU for
 * @param chip_sku String to fill with the SKU
 */
void __bdk_model_get_sku_cn9xxx(int node, char *chip_sku)
{
    /* Figure out which SKU list to use */
    const model_sku_info_t *sku_info;
    uint64_t result;
    asm ("mrs %[rd],MIDR_EL1" : [rd] "=r" (result));
    result = bdk_extract(result, 4, 12);
    switch (result)
    {
        case 0xb1:
            sku_info = t98_sku_info;
            break;
        case 0xb2:
            sku_info = t96_sku_info;
            break;
        case 0xb3:
            sku_info = f95_sku_info;
            break;
        case 0xb4:
            sku_info = loki_sku_info;
            break;
        default:
            bdk_fatal("SKU detect: Unknown die\n");
    }

    int match_index = 0;
    int match_score = -1;
    int index = 0;
    while (sku_info[index].model_base)
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

    /* Update the model number with the number of cores */
    int model = 100 * sku_info[match_index].model_base +
        model_digits_for_cores(bdk_get_num_cores(node));

    /* Decode the product suffix from fuses */
    char product_suffix[3];
    uint64_t suffix_fuse = bdk_fuse_read_range(node, BDK_FUS_FUSE_NUM_E_SKU_CUSTX(0), 10);
    if (suffix_fuse)
    {
        product_suffix[0] = 'A' + (suffix_fuse & 0x1f) - 1;
        if (suffix_fuse >> 5)
            product_suffix[1] = 'A' + (suffix_fuse >> 5) - 1;
        else
            product_suffix[1] = 0;
        product_suffix[2] = 0;
    }
    else
        product_suffix[0] = 0;

    /* Update the RCLK setting based on MIO_FUS_DAT3[core_pll_mul] */
    uint64_t core_pll_mul;
    if (bdk_is_model(OCTEONTX_CN96XX))
        core_pll_mul = bdk_fuse_read_range(node, BDK_FUS_FUSE_NUM_E_CORE_MAX_MULX_CN96XX(0), 7);
    else if (bdk_is_model(OCTEONTX_CNF95XX))
        core_pll_mul = bdk_fuse_read_range(node, BDK_FUS_FUSE_NUM_E_CORE_MAX_MULX_CNF95XX(0), 7);
    else if (bdk_is_model(OCTEONTX_LOKI))
        core_pll_mul = bdk_fuse_read_range(node, BDK_FUS_FUSE_NUM_E_CORE_MAX_MULX_LOKI(0), 7);
    else if (bdk_is_model(OCTEONTX_CN98XX))
        core_pll_mul = bdk_fuse_read_range(node, BDK_FUS_FUSE_NUM_E_CORE_MAX_MULX_CN98XX(0), 7);
    else
        bdk_fatal("%s: Needs update for this chip\n", __FUNCTION__);

    int rclk_limit = bdk_clock_get_rate(node, BDK_CLOCK_RCLK) / 1000000;
    if (core_pll_mul)
    {
        /* CORE_PLL_MUL covers bits 5:1, so we need to multiple by 2. The
           documentation doesn't mention this clearly: There is a 300Mhz
           addition to the base multiplier */
        rclk_limit = core_pll_mul * 2 * 50 + 300;
    }

    /* Get the package code */
    BDK_CSR_INIT(gpio_pkg_ver, node, BDK_GPIO_PKG_VER);
    char package_code = 'A' + gpio_pkg_ver.s.pkg_ver;
    /* 96XX pass C0 and above have extended package codes */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS3_X))
        package_code = 'I' + gpio_pkg_ver.s.pkg_ver;

    /* FIXME: We don't support getting the pass for other node on CN9XXX */
    bdk_ap_midr_el1_t midr_el1;
    BDK_MRS(MIDR_EL1, midr_el1.u);
    int major_pass = (midr_el1.s.variant & 7) + 1;
    int minor_pass = midr_el1.s.revision;

    /* CN96XX-A1 was named CN96XX-B0 by marketing. Fixup the revision
       before we build the SKU */
    if (bdk_is_model(OCTEONTX_CN96XX_PASS1_1))
    {
        major_pass = 2;
        minor_pass = 0;
    }

    /* Build the SKU string */
    snprintf(chip_sku, BDK_MODEL_MAX_SKU, "%s%d%s-%dxy%c-%s-%c%c-G",
        sku_info[match_index].prefix, model, product_suffix,
        rclk_limit, package_code, sku_info[match_index].segment,
        'A' + major_pass - 1, '0' + minor_pass);
}
