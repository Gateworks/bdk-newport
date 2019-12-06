/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <malloc.h>
#include <newport.h>
#include "libbdk-arch/bdk-csrs-key.h"
#include "libbdk-arch/bdk-csrs-usbh.h"

/* Address of ATF in flash */
#ifdef ATF_NONSECURE_FLASH_ADDRESS
    #define ATF_ADDRESS ATF_NONSECURE_FLASH_ADDRESS
#else
    #define ATF_ADDRESS 0x00400000
#endif

/**
 * This function is not defined by the BDK libraries. It must be
 * defined by all BDK applications. It should be empty except for
 * containing BDK_REQUIRE() lines. The bdk-init code has a strong
 * reference to bdk_requires_depends() which then contains strong
 * references to all needed components.
 */
void __bdk_require_depends(void)
{
    BDK_REQUIRE(ERROR_DECODE);
    BDK_REQUIRE(FS_BOOT);
    BDK_REQUIRE(FS_FATFS);
    BDK_REQUIRE(FS_MMC);
    BDK_REQUIRE(FS_MPI);
    BDK_REQUIRE(FS_ROM);
    BDK_REQUIRE(QLM);
    BDK_REQUIRE(MDIO);
    BDK_REQUIRE(PCIE);
    BDK_REQUIRE(RNM);
    BDK_REQUIRE(KEY_MEMORY);
    BDK_REQUIRE(MPI);
    BDK_REQUIRE(DRAM_CONFIG);
    BDK_REQUIRE(USB);
    BDK_REQUIRE(ECAM);
    BDK_REQUIRE(DRIVER);

    BDK_REQUIRE(DRIVER_GPIO);
    BDK_REQUIRE(DRIVER_GPIO_CONSOLE);
    BDK_REQUIRE(DRIVER_MCC);
    BDK_REQUIRE(DRIVER_PBUS);
    BDK_REQUIRE(DRIVER_PCIEEP);
    BDK_REQUIRE(DRIVER_PCIERC);
    BDK_REQUIRE(DRIVER_PWM_ISL6813X);
    BDK_REQUIRE(DRIVER_SMMU);
    BDK_REQUIRE(DRIVER_IOBN5);
    BDK_REQUIRE(DRIVER_TWSI);
    BDK_REQUIRE(DRIVER_TWSI_PCA9548);
    BDK_REQUIRE(DRIVER_UAA);
    BDK_REQUIRE(DRIVER_USB);
    BDK_REQUIRE(DRIVER_XCP);
}

extern const char *boot_device_volstr_for_boot_method(int boot_method);

/**
 * Main entry point
 *
 * @return exit code
 */
int main(int argc, const char **argv)
{
    bdk_node_t node = bdk_numa_local();

    /* Enable watchdog. Must be after loading the config so we know the
       watchdog timeout */
    bdk_watchdog_set(0);
#if 0 // NEWPORT
    bdk_boot_board_init_early();
    bdk_watchdog_poke();

    printf(
        "=============\n"
        "OcteonTX Init\n"
        "=============\n"
        "BDK Version: %s\n"
        "\n",
        bdk_version_string());

    bdk_watchdog_poke();

    /* We still call DVFS for all chips. Internally the function figures out
       what is needed to each chip */
    bdK_scp_init_dvfs();
    bdk_watchdog_poke();

    bdk_config_set_str(bdk_model_get_sku(node), BDK_CONFIG_CHIP_SKU, node);
    bdk_config_set_str(bdk_boot_info_serial(node), BDK_CONFIG_CHIP_SERIAL, node);
    bdk_config_set_str(bdk_boot_info_unique_id(node), BDK_CONFIG_CHIP_UNIQUE_ID, node);

    int override_for_speed = 0;
    bdk_boot_dram(bdk_numa_master(), override_for_speed); /* Initialize DRAM on node 0 */

#if BDK_SUPPORT_MULTINODE
    if (bdk_numa_exists(BDK_NODE_1))
    {
        bdk_config_set_str(bdk_model_get_sku(BDK_NODE_1), BDK_CONFIG_CHIP_SKU, BDK_NODE_1);
        bdk_config_set_str(bdk_boot_info_serial(BDK_NODE_1), BDK_CONFIG_CHIP_SERIAL, BDK_NODE_1);
        bdk_boot_info_strapping(BDK_NODE_1);
        const char *node1_version = (const char *)bdk_phys_to_ptr(
            bdk_numa_get_address(BDK_NODE_1, BDK_KEY_MEMX(0)));
        printf("BDK Version: %s\n", node1_version);
        if (strcmp(node1_version, bdk_version_string()) != 0)
            bdk_fatal("Mismatched BDK versions between nodes\n");
        bdk_boot_dram(BDK_NODE_1, override_for_speed); /* Initialize DRAM on node 1 */
    }
#endif

    bdk_watchdog_poke();
    bdk_boot_board_init_dram();
    bdk_watchdog_poke();
    bdk_boot_qlm();
    bdk_watchdog_poke();

    bdk_boot_bgx();
    if (!bdk_is_platform(BDK_PLATFORM_EMULATOR))
        bdk_boot_usb();

    bdk_watchdog_poke();

    bdk_boot_pcie();
    bdk_boot_twsi();
    bdk_boot_mdio();

    /*
     * Program the PHYs 
     * List of PHYs currently initialized in BDK 
     * VSC8514/VSC8574/Marvell88E15X
     */
    for (bdk_node_t n = BDK_NODE_0; n < BDK_NUMA_MAX_NODES; n++)
    {
        if (bdk_numa_exists(n))
        {
            bdk_if_phy_setup(n);
        }
    }
#else
    if (newport_config()) {
		printf("hang\n");
		while (1) {
			bdk_wait_usec(10000);
		}
    }

    /* disable boot watchdog */
    gsc_boot_wd_disable(node, true);
#endif // NEWPORT

    /* Poke the watchdog */
    bdk_watchdog_poke();
    bdk_boot_board_init_complete();
    bdk_watchdog_poke();

    int boot_path = bdk_config_get_int(BDK_CONFIG_BOOT_PATH_OPTION);
    int use_atf = (boot_path == 0); /* 0 = normal, 1 - diagnostics */

    /* Process the Operating system device tree */
    extern int devtree_process(int use_atf);
    int devtree_fail = devtree_process(use_atf);

    /* Poke the watchdog */
    bdk_watchdog_poke();


    /* Transfer control to next image */
    if (use_atf && !devtree_fail)
    {
        /* Check if the next boot stage is configured. */
        const char *next_stage = bdk_config_get_str(BDK_CONFIG_BOOT_NEXT_STAGE, "INIT");
        if (next_stage)
        {
            bdk_image_boot(next_stage, 0);

            printf("**********************************************************************\n");
            printf("* WARNING\n");
            printf("*\n");
            printf("* Next boot stage file is configured as:\n");
            printf("*    %s\n", next_stage);
            printf("* but loading the stage failed. Loading ATF instead.\n");
            printf("**********************************************************************\n");
        }

        /* Try to load ATF image from raw flash */
        BDK_TRACE(INIT, "Looking for ATF image\n");
        if (bdk_trust_get_level() == BDK_TRUST_LEVEL_NONE)
            bdk_image_boot("/boot", ATF_ADDRESS);
        bdk_image_boot("/fatfs/bl1.bin.lzma", 0);
        bdk_error("Unable to load image\n");
        printf("Trying diagnostics\n");
    }

    /* Load Diagnostics from FAT fs */
    BDK_TRACE(INIT, "Looking for Diagnostics image\n");
    return bdk_image_boot("/fatfs/diagnostics.bin.lzma", 0);
}

