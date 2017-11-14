/***********************license start***********************************
* Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
* reserved.
*
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*
*   * Neither the name of Cavium Inc. nor the names of
*     its contributors may be used to endorse or promote products
*     derived from this software without specific prior written
*     permission.
*
* This Software, including technical data, may be subject to U.S. export
* control laws, including the U.S. Export Administration Act and its
* associated regulations, and may be subject to export or import
* regulations in other countries.
*
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
* AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
* WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
* TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
* REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
* DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
* OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
* PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
* QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
* ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
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
    BDK_REQUIRE(CCPI);
    BDK_REQUIRE(CSR_DB);
    BDK_REQUIRE(DRAM_CONFIG);
    BDK_REQUIRE(DRAM_TEST);
    BDK_REQUIRE(ERROR_DECODE);
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
    BDK_REQUIRE(GPIO);
    BDK_REQUIRE(SGPIO);
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
    BDK_REQUIRE(TRAFFIC_GEN);
    BDK_REQUIRE(TWSI);
    BDK_REQUIRE(USB);
    BDK_REQUIRE(USB_XHCI);
    BDK_REQUIRE(ECAM);
    BDK_REQUIRE(DRIVER);
    BDK_REQUIRE(XFI);
    BDK_REQUIRE(EEPROM);

    BDK_REQUIRE(DRIVER_CCPI);
    BDK_REQUIRE(DRIVER_PBUS);
    BDK_REQUIRE(DRIVER_PCIEEP);
    BDK_REQUIRE(DRIVER_PCIERC);
    BDK_REQUIRE(DRIVER_SMMU);
    BDK_REQUIRE(DRIVER_UAA);
    BDK_REQUIRE(DRIVER_IOBN5);
    BDK_REQUIRE(AQR107_SUPPORT);
}

/**
 * Main entry point
 *
 * @return exit code
 */
int main(int argc, const char **argv)
{
    bdk_boot_status(BDK_BOOT_STATUS_DIAG_STARTING);
    bdk_watchdog_disable();
    bdk_boot_status(BDK_BOOT_STATUS_DIAG_COMPLETE);
    /* Start Lua. It will execute init.lua */
    return bdk_lua_start();
}
