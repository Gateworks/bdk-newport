/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-ap.h"
#include "libbdk-arch/bdk-csrs-fus.h"
#include "libbdk-arch/bdk-csrs-gic.h"
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-gser.h"
#include "libbdk-arch/bdk-csrs-mio_fus.h"

/**
 * Display information about strapping and other hard configuration items for
 * the specified node
 *
 * @param node   Node to display
 */
void bdk_boot_info_strapping(bdk_node_t node)
{
    BDK_CSR_INIT(gicd_iidr, node, BDK_GICD_IIDR);

    BDK_CSR_INIT(gpio_strap, node, BDK_GPIO_STRAP);
    char boot_method_str[32];
    const char *vrm_label;
    int vrm_disable;
    int trust_mode = bdk_extract(gpio_strap.u, BDK_GPIO_STRAP_PIN_E_TRUSTED_MODE, 1);

    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        vrm_label = "VRM";
        vrm_disable = bdk_extract(gpio_strap.u, 9, 1);
        int boot_method = bdk_extract(gpio_strap.u, 0, 4);
        switch ( boot_method )
        {
            case BDK_RST_BOOT_METHOD_E_CCPI0:
                strcpy(boot_method_str, "CCPI0");
                break;
            case BDK_RST_BOOT_METHOD_E_CCPI1:
                strcpy(boot_method_str, "CCPI1");
                break;
            case BDK_RST_BOOT_METHOD_E_CCPI2:
                strcpy(boot_method_str, "CCPI2");
                break;
            case BDK_RST_BOOT_METHOD_E_EMMC_LS:
                strcpy(boot_method_str, "EMMC_LS");
                break;
            case BDK_RST_BOOT_METHOD_E_EMMC_SS:
                strcpy(boot_method_str, "EMMC_SS");
                break;
            case BDK_RST_BOOT_METHOD_E_PCIE0:
                strcpy(boot_method_str, "PCIE0");
                break;
            case BDK_RST_BOOT_METHOD_E_PCIE2:
                strcpy(boot_method_str, "PCIE2");
                break;
            case BDK_RST_BOOT_METHOD_E_REMOTE_CN8:
                strcpy(boot_method_str, "REMOTE");
                break;
            case BDK_RST_BOOT_METHOD_E_SPI24:
                strcpy(boot_method_str, "SPI24");
                break;
            case BDK_RST_BOOT_METHOD_E_SPI32:
                strcpy(boot_method_str, "SPI32");
                break;
            default:
                strcpy(boot_method_str, "UNKNOWN");
                break;
        }
        bdk_config_set_str(boot_method_str, BDK_CONFIG_BOOT_DEVICE, node);
    }
    else
    {
        vrm_label = "AVS";
        vrm_disable = bdk_extract(gpio_strap.u, BDK_GPIO_STRAP_PIN_E_AVS_DISABLE, 1);
        boot_method_str[0] = 0;
        int boot_method = bdk_extract(gpio_strap.u, BDK_GPIO_STRAP_PIN_E_BOOT_METHOD0, 3);
        for (int loop = 0; loop < 2; loop++)
        {
            if (loop != 0)
                strcat(boot_method_str, ",");
            switch (boot_method)
            {
                case BDK_RST_BOOT_METHOD_E_EMMC_CS0:
                    strcat(boot_method_str, "EMMC_CS0");
                    break;
                case BDK_RST_BOOT_METHOD_E_EMMC_CS1:
                    strcat(boot_method_str, "EMMC_CS1");
                    break;
                case BDK_RST_BOOT_METHOD_E_SPI0_CS0:
                    strcat(boot_method_str, "SPI0_CS0");
                    break;
                case BDK_RST_BOOT_METHOD_E_SPI0_CS1:
                    strcat(boot_method_str, "SPI0_CS1");
                    break;
                case BDK_RST_BOOT_METHOD_E_SPI1_CS0:
                    strcat(boot_method_str, "SPI1_CS0");
                    break;
                case BDK_RST_BOOT_METHOD_E_SPI1_CS1:
                    strcat(boot_method_str, "SPI1_CS1");
                    break;
                case BDK_RST_BOOT_METHOD_E_REMOTE_CN9:
                    strcat(boot_method_str, "REMOTE");
                    break;
                default:
                    strcat(boot_method_str, "UNKNOWN");
                    break;
            }
            boot_method = bdk_extract(gpio_strap.u, BDK_GPIO_STRAP_PIN_E_BOOT_METHOD3, 1);
            boot_method |= bdk_extract(gpio_strap.u, BDK_GPIO_STRAP_PIN_E_BOOT_METHOD4, 2) << 1;
        }
        BDK_CSR_INIT(rst_boot_status, node, BDK_RST_BOOT_STATUS);
        const char *boot_device = "UNKNOWN";
        /* Check if SCP ran and filled the boot status */
        if (rst_boot_status.u == 0)
        {
            /* Fake boot status that matches emulator  */
            union bdk_rst_boot_stat_s stat;
            stat.u = 0;
            stat.s.trusted = 0;
            stat.s.primary = 1;
            stat.s.scr_done = 0;
            stat.s.boot_method = bdk_is_platform(BDK_PLATFORM_ASIM) ? BDK_RST_BOOT_METHOD_E_SPI0_CS0 : BDK_RST_BOOT_METHOD_E_EMMC_CS0;
            stat.s.fail = BDK_RST_BOOT_FAIL_E_GOOD_CN9;
            rst_boot_status.s.stat0 = stat.u;
        }
        for (int index = 0; index < 4; index++)
        {
            union bdk_rst_boot_stat_s stat;
            stat.u = bdk_extract(rst_boot_status.u, index * 16, 16);
            if (stat.s.fail == BDK_RST_BOOT_FAIL_E_GOOD_CN9)
            {
                switch (stat.s.boot_method)
                {
                    case BDK_RST_BOOT_METHOD_E_EMMC_CS0:
                        boot_device = "EMMC_CS0";
                        break;
                    case BDK_RST_BOOT_METHOD_E_EMMC_CS1:
                        boot_device = "EMMC_CS1";
                        break;
                    case BDK_RST_BOOT_METHOD_E_SPI0_CS0:
                        boot_device = "SPI0_CS0";
                        break;
                    case BDK_RST_BOOT_METHOD_E_SPI0_CS1:
                        boot_device = "SPI0_CS1";
                        break;
                    case BDK_RST_BOOT_METHOD_E_SPI1_CS0:
                        boot_device = "SPI1_CS0";
                        break;
                    case BDK_RST_BOOT_METHOD_E_SPI1_CS1:
                        boot_device = "SPI1_CS1";
                        break;
                    case BDK_RST_BOOT_METHOD_E_REMOTE_CN9:
                        boot_device = "REMOTE";
                        break;
                }
                strcat(boot_method_str, ", using ");
                strcat(boot_method_str, boot_device);
                break;
            }
        }
        bdk_config_set_str(boot_device, BDK_CONFIG_BOOT_DEVICE, node);
    }

    int alt_pkg;
    int major_pass;
    int minor_pass;
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        /* Read the Pass information for fuses so we can read a different node.
           Note that pass info in MIO_FUS_DAT2[CHIP_ID] is encoded as
                bit[7] = Unused, zero
                bit[6] = Alternate package
                bit[5..3] = Major pass
                bit[2..0] = Minor pass */
        BDK_CSR_INIT(mio_fus_dat2, node, BDK_MIO_FUS_DAT2);
        alt_pkg = (mio_fus_dat2.s.chip_id >> 6) & 1;
        major_pass = ((mio_fus_dat2.s.chip_id >> 3) & 7) + 1;
        minor_pass = mio_fus_dat2.s.chip_id & 7;
    }
    else
    {
        /* FIXME: We don't support getting the pass for other node on CN9XXX */
        bdk_ap_midr_el1_t midr_el1;
        BDK_MRS(MIDR_EL1, midr_el1.u);
        alt_pkg = midr_el1.s.variant >> 3;
        major_pass = (midr_el1.s.variant & 7) + 1;
        minor_pass = midr_el1.s.revision;
    }
    const char *package_str = (alt_pkg) ? " (alt pkg)" : "";

    extern uint64_t __bdk_init_reg_pc; /* The contents of PC when this image started */
    const char *secure_image = "";
    if (node == bdk_numa_master())
    {
        if (__bdk_init_reg_pc == 0x150000)
            secure_image = ", Secure Boot";
        else if (__bdk_init_reg_pc == 0x120000)
            secure_image = ", Non-secure Boot";
    }

    /* Production builds shouldn't display chip pass details */
    if (BDK_DISPLAY_PASS)
        printf("Chip:  0x%x Pass %d.%d%s\n", gicd_iidr.s.productid, major_pass,
            minor_pass, package_str);

    printf(
        "SKU:   %s\n"
        "L2:    %d KB\n"
        "Boot:  %s\n"
        "%s:   %s\n"
        "Trust: %s%s\n",
        bdk_model_get_sku(node),
        bdk_l2c_get_cache_size_bytes(node) >> 10,
        boot_method_str,
        vrm_label, (vrm_disable) ? "Disabled" : "Enabled",
        (trust_mode) ? "Enabled" : "Disabled", secure_image);
}

/**
 * Read the manufacturing information fuses
 *
 * @param node   Node to read
 * @param mfg0   first 64bit if fuses
 * @param mfg1   second 64bits of fuses
 */
static void read_mfg(bdk_node_t node, uint64_t *mfg0, uint64_t *mfg1)
{
    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        /* This fuse read will load all 128 fuses into MIO_FUS_BNK_DATX */
        bdk_fuse_read(node, BDK_MIO_FUS_FUSE_NUM_E_MFG0X(0));
        /* Get MFG0 and MFG0 from MIO_FUS_BNK_DATX */
        *mfg0 = BDK_CSR_READ(node, BDK_MIO_FUS_BNK_DATX(0));
        *mfg1 = BDK_CSR_READ(node, BDK_MIO_FUS_BNK_DATX(1));
    }
    else
    {
        *mfg0 = bdk_fuse_read_range(node, BDK_FUS_FUSE_NUM_E_MFG_INFOX(0), 64);
        *mfg1 = bdk_fuse_read_range(node, BDK_FUS_FUSE_NUM_E_MFG_INFOX(1), 64);
    }
}

/**
 * Return a string containing information about the chip's manufacture wafer
 *
 * @param node   Node to query
 *
 * @return Static string, reused on each call
 */
const char *bdk_boot_info_wafer(bdk_node_t node)
{
    #define DECODE_LOTID_CHAR(x)    (x < 10 ? '0' + x : x < 36 ? 'A' + x - 10 : ' ')
    static char buffer[64];

    uint64_t mfg0;
    uint64_t mfg1;
    read_mfg(node, &mfg0, &mfg1);
    /* If either MFG area is programed, assume they are valid */
    if (mfg0 || (mfg1 & bdk_build_mask(26)))
    {
        /* Extract the mother lot ID */
        int c9 = bdk_extract(mfg0, 0, 6);
        int c8 = bdk_extract(mfg0, 6, 6);
        int c7 = bdk_extract(mfg0, 12, 6);
        int c6 = bdk_extract(mfg0, 18, 6);
        int c5 = bdk_extract(mfg0, 24, 6);
        int c4 = bdk_extract(mfg0, 30, 6);
        int c3 = bdk_extract(mfg0, 36, 6);
        int c2 = bdk_extract(mfg0, 42, 6);
        int c1 = bdk_extract(mfg0, 48, 6);
        /* Extract wafer, X, and Y data */
        int y = bdk_extract(mfg1, 0, 10);
        int x = bdk_extract(mfg1, 10, 10);
        int wafer_id = bdk_extract(mfg1, 20, 6);
        snprintf(buffer, sizeof(buffer), "Lot ID: %c%c%c%c%c%c%c.%c%c, Wafer ID: %2d, X-loc: %2d, Y-loc: %2d",
            DECODE_LOTID_CHAR(c1), DECODE_LOTID_CHAR(c2), DECODE_LOTID_CHAR(c3),
            DECODE_LOTID_CHAR(c4), DECODE_LOTID_CHAR(c5), DECODE_LOTID_CHAR(c6),
            DECODE_LOTID_CHAR(c7), DECODE_LOTID_CHAR(c8), DECODE_LOTID_CHAR(c9),
            wafer_id, x, y);
    }
    else
    {
        /* Nothing programmed in the fuses */
        snprintf(buffer, sizeof(buffer), "Lot id: Not available");
    }

    return buffer;
}

/**
 * Return a string containing the chip's unique serial number
 *
 * @param node   Node to query
 *
 * @return Static string, reused on each call
 */
const char *bdk_boot_info_serial(bdk_node_t node)
{
    static char buffer[30];

    uint64_t mfg0;
    uint64_t mfg1;
    read_mfg(node, &mfg0, &mfg1);

    if (mfg0 || (mfg1 & bdk_build_mask(26)))
    {
        snprintf(buffer, sizeof(buffer), "%04lx-%04lx-%04lx-%04lx-%04lx-%04lx",
            bdk_extract(mfg1, 16, 10), /* Total of 26 bits from mfg1 */
            bdk_extract(mfg1, 0, 16),
            bdk_extract(mfg0, 48, 16), /* Total of 64 bits from mfg0 */
            bdk_extract(mfg0, 32, 16),
            bdk_extract(mfg0, 16, 16),
            bdk_extract(mfg0, 0, 16));
    }
    else
    {
        snprintf(buffer, sizeof(buffer), "Not Available");
    }

    return buffer;
}

/**
 * Return a string containing the chip's unique ID
 *
 * @param node   Node to query
 *
 * @return Static string, reused on each call
 */
const char *bdk_boot_info_unique_id(bdk_node_t node)
{
    static char buffer[21];

    uint64_t mfg0;
    uint64_t mfg1;
    read_mfg(node, &mfg0, &mfg1);

    uint64_t id_hi =
        (bdk_extract(mfg1, 10, 10) << 54) |
        (bdk_extract(mfg0, 0, 12) << 42) |
        (bdk_extract(mfg0, 12, 6) << 36) |
        (bdk_extract(mfg0, 18, 6) << 30) |
        (bdk_extract(mfg0, 24, 6) << 24) |
        (bdk_extract(mfg0, 30, 6) << 18) |
        (bdk_extract(mfg0, 36, 6) << 12) |
        (bdk_extract(mfg0, 42, 6) << 6) |
        (bdk_extract(mfg0, 48, 6) << 0);
    uint64_t id_lo = (bdk_extract(mfg1, 0, 10) << 6) | bdk_extract(mfg1, 20, 6);

    snprintf(buffer, sizeof(buffer), "%016lx%04lx", id_hi, id_lo);
    return buffer;
}
