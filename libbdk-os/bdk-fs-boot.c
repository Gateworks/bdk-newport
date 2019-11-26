/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <fcntl.h>
#include <unistd.h>
#include "libbdk-arch/bdk-csrs-cpc.h"
#include "libbdk-arch/bdk-csrs-gpio.h"
#include "libbdk-arch/bdk-csrs-mpi.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(FS_BOOT);

/* "/boot" is a trivial filesystem to pass all operations to the boot
   device. Its purpose is to abstract the name of the boot device from
   the various open calls that want to access it */

static char boot_dev_name[64];

static void *boot_open(const char *name, int flags)
{
    /* Arbitrate for boot ownership */
    if (!bdk_is_model(OCTEONTX_CN8XXX))
    {
        BDK_TRACE(INIT, "Arbitrate for boot ownership\n");
        const int TIMEOUT = 10000000; /* 10 second */
        BDK_CSR_MODIFY(c, bdk_numa_master(), BDK_CPC_BOOT_OWNERX(2),
            c.s.boot_req = 1);
        if (BDK_CSR_WAIT_FOR_FIELD(bdk_numa_master(), BDK_CPC_BOOT_OWNERX(2), boot_wait, ==, 0, TIMEOUT))
            bdk_error("Timeout waitng for boot arbitration, continuing anyway\n");
        else
            BDK_TRACE(INIT, "Arbitration complete\n");
    }
    int handle = open(boot_dev_name, flags);
    if (handle < 0)
        return NULL;
    else
        return (void*)(long)handle;
}

static int boot_close(__bdk_fs_file_t *handle)
{
    int status = close((long)handle->fs_state);
    /* Release boot ownership */
    if (!bdk_is_model(OCTEONTX_CN8XXX))
    {
        BDK_TRACE(INIT, "Releasing boot device\n");
        BDK_CSR_MODIFY(c, bdk_numa_master(), BDK_CPC_BOOT_OWNERX(2),
            c.s.boot_req = 0);
    }
    return status;
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
    .open = boot_open,
    .close = boot_close,
    .read = boot_read,
    .write = boot_write,
    .list = NULL,
};

int __bdk_fs_boot_init(void)
{
    bdk_node_t node = bdk_numa_master();

    if (bdk_is_model(OCTEONTX_CN8XXX))
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
                    "/dev/n%d.mpi%d/cs%d-%c,2wire,idle-%c,%csb,%dbit,%d",
                    node, 0, chip_select, (active_high) ? 'h' : 'l', idle_mode,
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
        BDK_CSR_INIT(rst_boot_status, node, BDK_RST_BOOT_STATUS);
        for (int index = 0; index < 4; index++)
        {
            union bdk_rst_boot_stat_s stat;
            stat.u = bdk_extract(rst_boot_status.u, index * 16, 16);
            if (stat.s.fail == BDK_RST_BOOT_FAIL_E_GOOD_CN9)
            {
                switch (stat.s.boot_method)
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
                        int spi = (stat.s.boot_method - BDK_RST_BOOT_METHOD_E_SPI0_CS0) >> 1;
                        int chip_select = (stat.s.boot_method - BDK_RST_BOOT_METHOD_E_SPI0_CS0) & 1;
                        BDK_CSR_DEFINE(mpi_cfg, BDK_MPIX_CFG(spi));
                        mpi_cfg.u = BDK_CSR_READ(bdk_numa_master(), BDK_MPIX_CFG(spi));
                        mpi_cfg.s.clkdiv = 10;
                        int address_width;
                        int active_high = mpi_cfg.s.cshi;
                        int idle_mode = (mpi_cfg.s.idleclks) ? 'r' : (mpi_cfg.s.idlelo) ? 'l' : 'h';
                        int is_msb = !mpi_cfg.s.lsbfirst;
                        int freq_mhz = bdk_clock_get_rate(node, BDK_CLOCK_MAIN_REF) / (2 * mpi_cfg.s.clkdiv) / 1000000;
                        address_width = 24;

                        snprintf(boot_dev_name, sizeof(boot_dev_name),
                            "/dev/n%d.mpi%d/cs%d-%c,2wire,idle-%c,%csb,%dbit,%d",
                            node, spi, chip_select, (active_high) ? 'h' : 'l', idle_mode,
                            (is_msb) ? 'm' : 'l', address_width, freq_mhz);
                        break;
                    }

                    default:
                        snprintf(boot_dev_name, sizeof(boot_dev_name), "/dev/n%d.mem0", node);
                        break;
                }
                break;
            }
        }
        if (!boot_dev_name[0] && bdk_is_platform(BDK_PLATFORM_EMULATOR))
        {
            bdk_error("RST_BOOT_STATUS(0x%lx) not programmed correctly, assuming EMMC_CS0\n", rst_boot_status.u);
            snprintf(boot_dev_name, sizeof(boot_dev_name), "/dev/n%d.mmc0", node);
        }
        if (!boot_dev_name[0] && bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            snprintf(boot_dev_name, sizeof(boot_dev_name),
                "/dev/n%d.mpi%d/cs%d-%c,2wire,idle-%c,%csb,%dbit,%d",
                node, 0, 0, 'h', 'h', 'm', 24, 12);
            bdk_error("RST_BOOT_STATUS(0x%lx) not programmed correctly, assuming %s\n", rst_boot_status.u, boot_dev_name);
        }
    }
    BDK_TRACE(INIT, "Boot device is %s\n", boot_dev_name);
    return bdk_fs_register("/boot", &bdk_fs_boot_ops);
}
