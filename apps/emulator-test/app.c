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
    BDK_REQUIRE(FS_BOOT);
    BDK_REQUIRE(FS_FATFS);
    BDK_REQUIRE(FS_MMC);
    BDK_REQUIRE(FS_MPI);
    BDK_REQUIRE(MPI);
    BDK_REQUIRE(ERROR_DECODE);
    BDK_REQUIRE(ECAM);
    BDK_REQUIRE(DRIVER);
    BDK_REQUIRE(DRIVER_MCC);
    BDK_REQUIRE(DRIVER_PBUS);
    BDK_REQUIRE(DRIVER_PCIEEP);
    BDK_REQUIRE(DRIVER_PCIERC);
    BDK_REQUIRE(DRIVER_SMMU);
    BDK_REQUIRE(DRIVER_UAA);
    BDK_REQUIRE(DRIVER_IOBN5);
}

/**
 * Main entry point
 *
 * @return exit code
 */
int main(int argc, const char **argv)
{
    bdk_node_t node = bdk_numa_local();

    printf("Platform set to emulator: %s\n",
        bdk_is_platform(BDK_PLATFORM_EMULATOR) ? "PASS" : "FAIL");

    printf("Enabling all tracing\n");
    bdk_trace_enables = -1;

    printf("Starting cores\n");
    bdk_init_cores(node, 0);
    printf("Alive cores: %d\n", bdk_get_num_running_cores(node));

    printf("Starting power burn on all cores for 10ms\n");
    if (bdk_power_burn(node, BDK_POWER_BURN_FULL))
        bdk_error("Power burn start failed\n");
    bdk_wait_usec(10000);
    if (bdk_power_burn(node, BDK_POWER_BURN_NONE))
        bdk_error("Power burn stop failed\n");
    else
        printf("Power burn complete\n");

    printf("Starting DRAM test of 1MB\n");
    int errors = bdk_dram_test(4 /* random xor */, 64<<20, 1<<20, 0);
    printf("Reported %d errors: %s\n",
        errors, (errors == 0) ? "PASS" : "FAIL");

    printf("Quick tests complete, starting longer test\n");

    int test_size = bdk_l2c_get_cache_size_bytes(node) + (2 << 20);
    printf("Starting DRAM test of %dMB at offset 64MB\n", test_size >> 20);
    errors = bdk_dram_test(4 /* random xor */, 64<<20, test_size, 0);
    printf("Reported %d errors: %s\n",
        errors, (errors == 0) ? "PASS" : "FAIL");

    uint64_t mem_size = bdk_dram_get_size_mbytes(node);
    if (mem_size > 4096)
        mem_size = 4096;
    for (uint64_t mb = 512; mb <= mem_size; mb += 512)
    {
        printf("Starting DRAM test of %dMB at offset %luMB\n", test_size >> 20, mb - (test_size >> 20));
        errors = bdk_dram_test(4 /* random xor */, (mb << 20) - test_size, test_size, 0);
        printf("Reported %d errors: %s\n",
            errors, (errors == 0) ? "PASS" : "FAIL");
    }

    printf("All tests complete\n");
    return 0;
}

