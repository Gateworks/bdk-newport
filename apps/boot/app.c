/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <ctype.h>
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-gti.h"
#include "libbdk-arch/bdk-csrs-ap.h"

/* This variable gets set to non-zero if any configuration error is detected
   such that we can't proceed through the normal boot path */
static int is_misconfigured = 0;

/* Filename of the next stage, default is init.bin.lzma */
static const char *next_stage = NULL;

/**
 * This function is not defined by the BDK libraries. It must be
 * defined by all BDK applications. It should be empty except for
 * containing BDK_REQUIRE() lines. The bdk-init code has a strong
 * reference to bdk_requires_depends() which then contains strong
 * references to all needed components.
 */
void __bdk_require_depends(void)
{
    BDK_REQUIRE(FS_BOOT);
    BDK_REQUIRE(FS_FATFS);
    BDK_REQUIRE(FS_MMC);
    BDK_REQUIRE(FS_MPI);
    BDK_REQUIRE(MPI);
}

void boot_menu(void)
{
    bdk_menu_t menu;
    while (1)
    {
        bdk_menu_init(&menu, "Boot Options");
        if (!is_misconfigured) // Hidden if no board configuration
            bdk_menu_item(&menu, 'N', "Boot Normally", NULL, NULL);
        if (!is_misconfigured && next_stage) // Hidden if no custom next stage is configured
            bdk_menu_item(&menu, 'I', "Boot Normally (ignoring custom boot stages)", NULL, NULL);
        bdk_menu_item(&menu, 'S', "Enter Setup", NULL, NULL);
        if (!is_misconfigured) // Hidden if no board configuration
            bdk_menu_item(&menu, 'D', "Enter Diagnostics", NULL, NULL);
        if (!bdk_is_model(OCTEONTX_CN81XX))
            bdk_menu_item(&menu, 'E', "Enter Diagnostics, skipping Setup", NULL, NULL);
        bdk_menu_item(&menu, 'W', "Burn boot flash using Xmodem", NULL, NULL);
        bdk_menu_item(&menu, 'U', "Change baud rate and flow control", NULL, NULL);
        bdk_menu_item(&menu, 'R', "Reboot", NULL, NULL);

        int key = bdk_menu_display(&menu);

        switch (key)
        {
            case 'N': /* Boot normally */
                bdk_image_boot(next_stage ? next_stage : "/fatfs/init.bin", 0);
                break;
            case 'I': /* Force-boot init.bin.lzma (skip any custom stage) */
                bdk_image_boot("/fatfs/init.bin", 0);
                break;
            case 'S': /* Enter Setup */
                bdk_image_boot("/fatfs/setup.bin.lzma", 0);
                break;
            case 'D': /* Boot diagnostics */
                bdk_config_set_int(1, BDK_CONFIG_BOOT_PATH_OPTION);
                bdk_image_boot("/fatfs/init.bin", 0);
                break;
            case 'E': /* Enter diagnostics directly */
                if (bdk_is_model(OCTEONTX_CN81XX))
                    bdk_error("Invalid choice\n");
                else
                    bdk_image_boot("/fatfs/diagnostics.bin.lzma", 0);
                break;
            case 'W': /* Xmodem to ram flash */
            {
                bdk_xmodem_upload("/boot", 0);
                break;
            }
            case 'U': /* Change baud rate */
            {
                bdk_menu_init(&menu, "Baudrate");
                bdk_menu_item(&menu, 'A', "9600", NULL, NULL);
                bdk_menu_item(&menu, 'B', "19200", NULL, NULL);
                bdk_menu_item(&menu, 'C', "38400", NULL, NULL);
                bdk_menu_item(&menu, 'D', "57600", NULL, NULL);
                bdk_menu_item(&menu, 'E', "115200", NULL, NULL);
                bdk_menu_item(&menu, 'F', "230400", NULL, NULL);
                bdk_menu_item(&menu, 'G', "460800", NULL, NULL);
                bdk_menu_item(&menu, 'H', "921600", NULL, NULL);
                key = bdk_menu_display(&menu);
                int baudrate = 0;
                if ((key >= 'A') && (key <= 'H'))
                {
                    const int baud[] = {9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600};
                    baudrate = baud[key - 'A'];
                }
                else
                    break;
                printf("Use hardware flow control(y/n) [n]: ");
                key = bdk_readline_getkey(-1);
                int use_flow = (key == 'y') || (key == 'Y');
                printf("\nChanging baudrate to %d\n", baudrate);
                fflush(NULL);
                bdk_wait_usec(500000);
                bdk_set_baudrate(bdk_numa_local(), 0, baudrate, use_flow);
                printf("Baudrate is now %d\n", baudrate);
                break;
            }
            case 'R': /* Reboot */
                printf("Rebooting\n");
                bdk_reset_chip(bdk_numa_master());
                break;
            default:
                bdk_error("Invalid choice\n");
                break;
        }
    }
}

/**
 * Main entry point
 *
 * @return exit code
 */
int main(int argc, const char **argv)
{
    bdk_node_t node = bdk_numa_local();

#if 0 // NEWPORT
    if (bdk_is_model(OCTEONTX_CN9XXX) && bdk_is_platform(BDK_PLATFORM_HW))
    {
        /* The following code programs clocks, ignoring the SCP. This should be
           removed once the SCP clock control is debugged.  It is here
           for compatibility as we skipped lots of board before enabling
           SCP clock management */
        BDK_CSR_INIT(gpio_strap, node, BDK_GPIO_STRAP);
        int avs_disable = bdk_extract(gpio_strap.u, BDK_GPIO_STRAP_PIN_E_AVS_DISABLE, 1);
        if (avs_disable)
        {
            /* Program SCLK */
            int sclock = bdk_config_get_int(BDK_CONFIG_SCLK_FREQ, node);
            bdk_wait_usec(1000);
            BDK_CSR_MODIFY(c, node, BDK_RST_PNR_PLL,
                c.s.pd_switch = 1;
                c.s.dly_switch = 2000;
                c.s.nxt_mul = sclock / 50;
                c.s.nxt_pgm = 1);
            bdk_wait_usec(1000);
            /* Update GTI for the new SCLK */
            BDK_CSR_MODIFY(c, node, BDK_GTI_CC_CNTCR,
                c.s.en = 0);
            uint64_t sclk = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);
            uint64_t inc = (BDK_GTI_RATE << 32) / sclk;
            BDK_CSR_WRITE(node, BDK_GTI_CC_CNTRATE, inc);
            BDK_CSR_MODIFY(c, node, BDK_GTI_CC_CNTCR,
                c.s.en = 1);
            /* Program CPTCLK for CN96XX, CN98XX */
            if (bdk_is_model(OCTEONTX_CN96XX) || bdk_is_model(OCTEONTX_CN98XX))
            {
                int cclock = bdk_config_get_int(BDK_CONFIG_CPTCLK_FREQ, node);
                BDK_CSR_MODIFY(c, node, BDK_RST_CPT_PLL,
                    c.s.pd_switch = 1;
                    c.s.dly_switch = 2000;
                    c.s.nxt_mul = cclock / 50;
                    c.s.nxt_pgm = 1);
                if (bdk_is_model(OCTEONTX_CN98XX))
                {
                    BDK_CSR_MODIFY(c, node, BDK_RST_CPT1_PLL,
                        c.s.pd_switch = 1;
                        c.s.dly_switch = 2000;
                        c.s.nxt_mul = cclock / 50;
                        c.s.nxt_pgm = 1);
                }
                bdk_wait_usec(1000);
            }
            /* Program BPHYCLK and DSPCLK for CNF95XX or LOKI */
            if (bdk_is_model(OCTEONTX_CNF95XX) || bdk_is_model(OCTEONTX_LOKI))
            {
                int bphyclock = bdk_config_get_int(BDK_CONFIG_BCLK_FREQ_MAX, node);
                BDK_CSR_MODIFY(c, node, BDK_RST_BPHY_PLL,
                    c.s.pd_switch = 1;
                    c.s.dly_switch = 2000;
                    c.s.nxt_mul = bphyclock / 50;
                    c.s.nxt_pgm = 1);
                bdk_wait_usec(1000);
                int dspclock = bdk_config_get_int(BDK_CONFIG_DSPCLK_FREQ_MAX, node);
                BDK_CSR_MODIFY(c, node, BDK_RST_DSP_PLL,
                    c.s.pd_switch = 1;
                    c.s.dly_switch = 2000;
                    c.s.nxt_mul = dspclock / 50;
                    c.s.nxt_pgm = 1);
                bdk_wait_usec(1000);
            }
            /* Program RCLK */
            int rclock = bdk_config_get_int(BDK_CONFIG_RCLK_FREQ_MAX, node);
            BDK_CSR_MODIFY(c, node, BDK_RST_CORE_PLL,
                c.s.dly_switch = 2000;
                c.s.nxt_mul = rclock / 50;
                c.s.nxt_pgm = 1);
            bdk_wait_usec(1000);
        }
    }

    const char *board = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
    /* Get the address of the version field in our header */
    uint64_t version_offset = offsetof(bdk_image_header_t, version);
    uint64_t version_pa = bdk_numa_get_address(node, version_offset);
    const char *version = bdk_phys_to_ptr(version_pa);

    printf(
        "==================\n"
        "OcteonTX Boot Stub\n"
        "==================\n"
        "Firmware Version: %s\n"
        "BDK Version: %s\n"
        "\n"
        "Board Model:    %s\n"
        "Board Revision: %s\n"
        "Board Serial:   %s\n"
        "\n",
        version,
        bdk_version_string(),
        board,
        bdk_config_get_str(BDK_CONFIG_BOARD_REVISION),
        bdk_config_get_str(BDK_CONFIG_BOARD_SERIAL));
    bdk_boot_info_strapping(bdk_numa_master());

    /* Check if the next boot stage is configured. */
    next_stage = bdk_config_get_str(BDK_CONFIG_BOOT_NEXT_STAGE, "BOOT");

    /* If no DRAM config goto the boot menu. First check for SPD addresses */
    int spd_addr = bdk_config_get_int(BDK_CONFIG_DDR_SPD_ADDR, 0 /* DIMM */, 0 /* LMC */, bdk_numa_master());
    if ((spd_addr == 0) && !bdk_is_platform(BDK_PLATFORM_ASIM) && !bdk_is_platform(BDK_PLATFORM_EMULATOR))
    {
        /* Not found, try SPD data */
        int spd_size = 0;
        const void *spd_data = bdk_config_get_blob(&spd_size, BDK_CONFIG_DDR_SPD_DATA, 0 /* DIMM */, 0 /* LMC */, bdk_numa_master());
        if ((spd_data == NULL) || (spd_size == 0))
        {
            /* No dram config found, jump to the boot menu */
            is_misconfigured = 1;
            goto menu;
        }

    }
#endif // NEWPORT

    int key = -1;
    FRESULT res= FR_OK;
    FILINFO info;
    res = f_stat("diagnostics.bin.lzma", &info);
if (res == FR_OK) {
    int boot_timeout = bdk_config_get_int(BDK_CONFIG_BOOT_MENU_TIMEOUT);
    printf("\nPress 'B' within %d seconds for boot menu\n", boot_timeout);
    do
    {
        key = bdk_readline_getkey(boot_timeout * 1000000);
    } while ((key != -1) && (key != 'B') && (key != 'b'));
}

    const char *board = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
    if (!strcmp(board, "unknown"))
	next_stage = "/fatfs/setup.bin.lzma";

    if (key == -1)
    {
        if (next_stage)
        {
            bdk_image_boot(next_stage, 0);

            printf("**********************************************************************\n");
            printf("* WARNING\n");
            printf("*\n");
            printf("* Next boot stage file is configured as:\n");
            printf("*    %s\n", next_stage);
            printf("* but loading the stage failed. Loading INIT instead.\n");
            printf("**********************************************************************\n");
        }

        bdk_image_boot("/fatfs/init.bin", 0);
    }
    else if (bdk_is_model(OCTEONTX_CN9XXX))
    {
        /* SCP uses RST_COLD_DATAX(2) bit 0 as a image good flag to disable
           the failsafe timer. Set this bit on keypress so the failsafe timer
           doesn't trigger while waiting for input */
        BDK_CSR_MODIFY(c, node, BDK_RST_COLD_DATAX(2),
            c.u |= 1);
    }

menu:
    boot_menu();
    return 0;
}

