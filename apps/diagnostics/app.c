/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

/**
 * This function is not defined by the BDK libraries. It must be
 * defined by all BDK applications. It should be empty except for
 * containing BDK_REQUIRE() lines. The bdk-init code has a strong
 * reference to bdk_requires_depends() which then contains strong
 * references to all needed components.
 */
void __bdk_require_depends(void)
{
    BDK_REQUIRE(CSR_DB);
    BDK_REQUIRE(DRAM_CONFIG);
    BDK_REQUIRE(DRAM_TEST);
    BDK_REQUIRE(ENVIRONMENT);
    BDK_REQUIRE(ERROR_DECODE);
    BDK_REQUIRE(FS_BASE64);
    BDK_REQUIRE(FS_BOOT);
    BDK_REQUIRE(FS_FATFS);
    BDK_REQUIRE(FS_MEM);
    BDK_REQUIRE(FS_MMC);
    BDK_REQUIRE(FS_MPI);
    BDK_REQUIRE(FS_PBUS);
    BDK_REQUIRE(FS_PCIE);
    BDK_REQUIRE(FS_RAM);
    BDK_REQUIRE(FS_ROM);
    BDK_REQUIRE(FS_SATA);
    BDK_REQUIRE(FS_XMODEM);
    BDK_REQUIRE(KEY_MEMORY);
    BDK_REQUIRE(MDIO);
    BDK_REQUIRE(MPI);
    BDK_REQUIRE(PCIE);
    BDK_REQUIRE(PCIE_EEPROM);
    BDK_REQUIRE(POWER_BURN);
    BDK_REQUIRE(QLM);
    BDK_REQUIRE(QLM_MARGIN);
    BDK_REQUIRE(QLM_EYE);
    BDK_REQUIRE(RNM);
    BDK_REQUIRE(SATA);
    BDK_REQUIRE(SCR_SCRIPT);
    BDK_REQUIRE(TRAFFIC_GEN);
    BDK_REQUIRE(USB);
    BDK_REQUIRE(USB_XHCI);
    BDK_REQUIRE(ECAM);
    BDK_REQUIRE(DRIVER);

    BDK_REQUIRE(DRIVER_GPIO);
    BDK_REQUIRE(DRIVER_GPIO_CONSOLE);
    BDK_REQUIRE(DRIVER_GPIO_PCA8574);
    BDK_REQUIRE(DRIVER_GPIO_PCA9535);
    BDK_REQUIRE(DRIVER_LED_CONSOLE);
    BDK_REQUIRE(DRIVER_LED_GPIO);
    BDK_REQUIRE(DRIVER_MCC);
    BDK_REQUIRE(DRIVER_NETPHY_88E1514);
    BDK_REQUIRE(DRIVER_NETPHY_88X5113);
    BDK_REQUIRE(DRIVER_NETPHY_88X5123);
    BDK_REQUIRE(DRIVER_NETPHY_88X6141);
    BDK_REQUIRE(DRIVER_NETPHY_88X3310P);
    BDK_REQUIRE(DRIVER_NETPHY_88X3340P);
    BDK_REQUIRE(DRIVER_NETPHY_VSC8574);
    BDK_REQUIRE(DRIVER_NETPORT_CONSOLE);
    BDK_REQUIRE(DRIVER_NETPORT_SFP28);
    BDK_REQUIRE(DRIVER_NETPORT_QSFP28);
    BDK_REQUIRE(DRIVER_PBUS);
    BDK_REQUIRE(DRIVER_PCIEEP);
    BDK_REQUIRE(DRIVER_PCIERC);
    BDK_REQUIRE(DRIVER_PWM_ISL6813X);
    BDK_REQUIRE(DRIVER_SATA);
    BDK_REQUIRE(DRIVER_SMMU);
    BDK_REQUIRE(DRIVER_TWSI);
    BDK_REQUIRE(DRIVER_TWSI_PCA9548);
    BDK_REQUIRE(DRIVER_TWSI_PCA9547);
    BDK_REQUIRE(DRIVER_UAA);
    BDK_REQUIRE(DRIVER_USB);
    BDK_REQUIRE(DRIVER_IOBN5);
}

/**
 * Main entry point
 *
 * @return exit code
 */
int main(int argc, const char **argv)
{
    bdk_watchdog_disable();

    /* If we skipped init and are relying on DVFS to set the clocks, do so now */
    uint64_t rclk = bdk_clock_get_rate(bdk_numa_master(), BDK_CLOCK_RCLK);
    if (rclk == 500000000)
        bdK_scp_init_dvfs();

    /* Start Lua. It will execute init.lua */
    return bdk_lua_start();
}
