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
#include <fcntl.h>
#include <unistd.h>
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-mpi.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(FS_BOOT);

/* "/boot" is a trivial filessytem to pass all operations to the boot
   device. Its purpose is to abstract the name of the boot device from
   the various open calls that want to access it */

static char boot_dev_name[64];

static int boot_stat(const char *name, struct stat *st)
{
    return stat(boot_dev_name, st);
}

static void *boot_open(const char *name, int flags)
{
    int handle = open(boot_dev_name, flags);
    if (handle < 0)
        return NULL;
    else
        return (void*)(long)handle;
}

static int boot_close(__bdk_fs_file_t *handle)
{
    return close((long)handle->fs_state);
}

static int boot_read(__bdk_fs_file_t *handle, void *buffer, int length)
{
    lseek((long)handle->fs_state, handle->location, SEEK_SET);
    return read((long)handle->fs_state, buffer, length);
}

static int boot_write(__bdk_fs_file_t *handle, const void *buffer, int length)
{
    lseek((long)handle->fs_state, handle->location, SEEK_SET);
    return write((long)handle->fs_state, buffer, length);
}

static const __bdk_fs_ops_t bdk_fs_boot_ops =
{
    .stat = boot_stat,
    .open = boot_open,
    .close = boot_close,
    .read = boot_read,
    .write = boot_write,
    .list = NULL,
};

int __bdk_fs_boot_init(void)
{
    bdk_node_t node = bdk_numa_master();

    if (CAVIUM_IS_MODEL(CAVIUM_CN8XXX))
    {
        /* Determine how we booted */
        BDK_CSR_INIT(gpio_strap, node, BDK_GPIO_STRAP);
        int boot_method = bdk_extract(gpio_strap.u, 0, 4);

        switch (boot_method)
        {
            case BDK_RST_BOOT_METHOD_E_EMMC_LS:
            case BDK_RST_BOOT_METHOD_E_EMMC_SS:
                snprintf(boot_dev_name, sizeof(boot_dev_name), "/dev/n%d.mmc0", node);
                break;

            case BDK_RST_BOOT_METHOD_E_SPI24:
            case BDK_RST_BOOT_METHOD_E_SPI32:
            {
                BDK_CSR_DEFINE(mpi_cfg, BDK_MPIX_CFG(0));
                mpi_cfg.u = BDK_CSR_READ(bdk_numa_master(), BDK_MPI_CFG);
                int chip_select = 0;
                int address_width;
                int active_high = mpi_cfg.s.cshi;
                int idle_mode = (mpi_cfg.s.idleclks) ? 'r' : (mpi_cfg.s.idlelo) ? 'l' : 'h';
                int is_msb = !mpi_cfg.s.lsbfirst;
                int freq_mhz = bdk_clock_get_rate(node, BDK_CLOCK_SCLK) / (2 * mpi_cfg.s.clkdiv) / 1000000;

                if (boot_method == BDK_RST_BOOT_METHOD_E_SPI24)
                    address_width = 24;
                else
                    address_width = 32;

                snprintf(boot_dev_name, sizeof(boot_dev_name),
                    "/dev/n%d.mpi%d/cs-%c,2wire,idle-%c,%csb,%dbit,%d",
                    node, chip_select, (active_high) ? 'h' : 'l', idle_mode,
                    (is_msb) ? 'm' : 'l', address_width, freq_mhz);
                break;
            }

            default:
                snprintf(boot_dev_name, sizeof(boot_dev_name), "/dev/n%d.mem0", node);
                break;
        }
    }
    else
    {
        /* Determine how we booted */
        BDK_CSR_INIT(gpio_strap, node, BDK_GPIO_STRAP);
        int boot_method = bdk_extract(gpio_strap.u, BDK_GPIO_STRAP_PIN_E_BOOT_METHOD0, 4);

        switch (boot_method)
        {
            case BDK_RST_BOOT_METHOD_E_EMMC_CS0:
                snprintf(boot_dev_name, sizeof(boot_dev_name), "/dev/n%d.mmc0", node);
                break;
            case BDK_RST_BOOT_METHOD_E_EMMC_CS1:
                snprintf(boot_dev_name, sizeof(boot_dev_name), "/dev/n%d.mmc1", node);
                break;

            case BDK_RST_BOOT_METHOD_E_SPI0_CS0:
            case BDK_RST_BOOT_METHOD_E_SPI0_CS1:
            case BDK_RST_BOOT_METHOD_E_SPI1_CS0:
            case BDK_RST_BOOT_METHOD_E_SPI1_CS1:
            {
                int spi = (boot_method - BDK_RST_BOOT_METHOD_E_SPI0_CS0) >> 1;
                int chip_select = (boot_method - BDK_RST_BOOT_METHOD_E_SPI0_CS0) & 1;
                BDK_CSR_DEFINE(mpi_cfg, BDK_MPIX_CFG(spi));
                mpi_cfg.u = BDK_CSR_READ(bdk_numa_master(), BDK_MPIX_CFG(spi));
                mpi_cfg.s.clkdiv = 10;
                int address_width;
                int active_high = mpi_cfg.s.cshi;
                int idle_mode = (mpi_cfg.s.idleclks) ? 'r' : (mpi_cfg.s.idlelo) ? 'l' : 'h';
                int is_msb = !mpi_cfg.s.lsbfirst;
                int freq_mhz = bdk_clock_get_rate(node, BDK_CLOCK_SCLK) / (2 * mpi_cfg.s.clkdiv) / 1000000;
                address_width = 24;

                snprintf(boot_dev_name, sizeof(boot_dev_name),
                    "/dev/n%d.mpi%d/cs-%c,2wire,idle-%c,%csb,%dbit,%d",
                    node, chip_select, (active_high) ? 'h' : 'l', idle_mode,
                    (is_msb) ? 'm' : 'l', address_width, freq_mhz);
                break;
            }

            default:
                snprintf(boot_dev_name, sizeof(boot_dev_name), "/dev/n%d.mem0", node);
                break;
        }
    }
    return bdk_fs_register("/boot", &bdk_fs_boot_ops);
}
