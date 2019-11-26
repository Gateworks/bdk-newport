/***********************license start***********************************
* Copyright (C) 2019 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-cpc.h"

/*Temperature sensor GPIO access control pin*/
#define GPIO_TEMP_SWITCH_DEVICE 27
/*External 12V presence detector pin*/
#define GPIO_EXT_12V_PRESENCE   7
/*Maximum RCLK in MHz for the card when both ext and pci power present*/
#define MAX_RCLK_PCI_EXT_POWER  2200
/*Power cap in watts when both PCI and external power supply present*/
#define POWER_CAP_PCI_EXT       120

/*Temperature sensor TWSI 1 address*/
#define TWSI_1_TEMP_SENSOR_ADDR 0x4C

/*SA56004X device register address*/
#define TEMP_SENSOR_REM_CRIT_WR_ADDR 0x19
#define TEMP_SENSOR_REM_WARN_WR_ADDR 0x0D
#define TEMP_SENSOR_LOC_CRIT_WR_ADDR 0x20
#define TEMP_SENSOR_LOC_WARN_WR_ADDR 0x0B
#define TEMP_SENSOR_CONFIG_RD_ADDR 0x03
#define TEMP_SENSOR_CONFIG_WR_ADDR 0x09
#define TEMP_SENSOR_CONV_WR_ADDR 0x0A
#define TEMP_SENSOR_ALERT_MODE_RW_ADDR 0xBF

/*warning and critical temperature*/
#define TEMP_WARNING_CELSIUS 0x55
#define TEMP_CRITICAL_CELSIUS 0x5F

/* Conversion rate Hz 1.0 */
#define TEMP_CONVERSION_RATE 0x4

#define TEMP_ALERT_MODE_INTERRUPT  0
#define TEMP_ALERT_MODE_COMPARATOR 1

static void init_early(void)
{
    int node = bdk_numa_master();
    uint64_t cur_gpio = 0;

    bdk_device_t *gpio_device = NULL;
    gpio_device = bdk_device_gpio_lookup(NULL, -1);

    if (!gpio_device)
    {
        bdk_error("%s: Unable to get GPIO device\n",__FUNCTION__);
        return;
    }
    cur_gpio = bdk_device_gpio_readstate(gpio_device, 0);

    if(((cur_gpio >> GPIO_EXT_12V_PRESENCE) & 1))
    {
        BDK_TRACE(INIT, "CN3380_250SV_V3: External power present, Max"
            "RCLK %d MHz Power cap %d Watts\n", MAX_RCLK_PCI_EXT_POWER,
            POWER_CAP_PCI_EXT);
        bdk_config_set_int(MAX_RCLK_PCI_EXT_POWER, BDK_CONFIG_RCLK_FREQ_MAX,
            node, 0);
        /* Both pci based and external power supply present */
        bdk_config_set_int(POWER_CAP_PCI_EXT, BDK_CONFIG_DVFS_POWER_BUDGET,
            node, 0);
    }
    BDK_TRACE(INIT, "CN3380_250SV_V3: Called %s\n", __FUNCTION__);
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "CN3380_250SV_V3: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    int node = bdk_numa_master();
    bdk_device_t *gpio_device = NULL;
    int dev_addr = TWSI_1_TEMP_SENSOR_ADDR;
    int internal_addr = 0;
    int twsi_id = 1;
    int num_bytes = 1;
    int ia_width_bytes = 1;
    uint64_t data = 0;
    uint64_t *addr = NULL;

    addr = (uint64_t *)(BDK_RST_COLD_DATAX(0));
    if ( addr && (*addr))
    {
        BDK_TRACE(INIT
        ,"CN3380_250SV_V3: Called %s not a cold reset so return\n", __FUNCTION__);
        return;
    }
    else
    {
        BDK_TRACE(INIT,
        "CN3380_250SV_V3: Called %s cold reset setting up temp sensor\n", __FUNCTION__);
        (*addr) = 1;
    }

    gpio_device = bdk_device_gpio_lookup(NULL, -1);

    if (!gpio_device)
    {
        bdk_error("%s: Unable to get GPIO device\n",__FUNCTION__);
        return;
    }

    bdk_device_gpio_setup(gpio_device, GPIO_TEMP_SWITCH_DEVICE, 1, 1, 1, 0);

    bdk_device_t *twsi_device = bdk_device_lookup(node,
        BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_MIO_TWS), twsi_id);

    if (!twsi_device)
    {
        bdk_error("%s: Unable to get twsi_device\n",__FUNCTION__);
        return;
    }

    /*setting local warning temperature*/
    internal_addr = TEMP_SENSOR_LOC_WARN_WR_ADDR;
    data = (TEMP_WARNING_CELSIUS - 5);
    if (bdk_device_twsi_write_ia(twsi_device, dev_addr, internal_addr,
        num_bytes, ia_width_bytes, data) == -1)
    {
        bdk_error("%s: TWSI temp sensor 1 - setting failed\n",__FUNCTION__);
        goto skip;
    }

    /*setting local critical temperature*/
    internal_addr = TEMP_SENSOR_LOC_CRIT_WR_ADDR;
    data = TEMP_CRITICAL_CELSIUS;
    if (bdk_device_twsi_write_ia(twsi_device, dev_addr, internal_addr,
        num_bytes, ia_width_bytes, data) == -1)
    {
        bdk_error("%s: TWSI temp sensor 2 - setting failed\n",__FUNCTION__);
        goto skip;
    }

    /*setting remote warning temperature*/
    internal_addr = TEMP_SENSOR_REM_WARN_WR_ADDR;
    data = TEMP_WARNING_CELSIUS;
    if (bdk_device_twsi_write_ia(twsi_device, dev_addr, internal_addr,
        num_bytes, ia_width_bytes, data) == -1)
    {
        bdk_error("%s: TWSI temp sensor 3 - setting failed\n",__FUNCTION__);
        goto skip;
    }

    /*setting remote critical temperature*/
    internal_addr = TEMP_SENSOR_REM_CRIT_WR_ADDR;
    data = TEMP_CRITICAL_CELSIUS;
    if (bdk_device_twsi_write_ia(twsi_device, dev_addr, internal_addr,
        num_bytes, ia_width_bytes, data) == -1)
    {
        bdk_error("%s: TWSI temp sensor 4 - setting failed\n",__FUNCTION__);
        goto skip;
    }

    /*setting remote critical trigger to 3 consecutive measurements*/
    internal_addr = TEMP_SENSOR_CONFIG_RD_ADDR;
    data = 0;
    if ((signed int)(data = bdk_device_twsi_read_ia(twsi_device, dev_addr, internal_addr,
        num_bytes, ia_width_bytes)) == -1)
    {
        bdk_error("%s: TWSI temp sensor 5 - reading failed\n",__FUNCTION__);
        goto skip;
    }

    internal_addr = TEMP_SENSOR_CONFIG_WR_ADDR;
    data |= 1;
    if (bdk_device_twsi_write_ia(twsi_device, dev_addr, internal_addr,
        num_bytes, ia_width_bytes, data) == -1)
    {
        bdk_error("%s: TWSI temp sensor 6 - setting failed\n",__FUNCTION__);
        goto skip;
    }

    /*setting remote critical temperature*/
    internal_addr = TEMP_SENSOR_CONV_WR_ADDR;
    data = TEMP_CONVERSION_RATE;
    if (bdk_device_twsi_write_ia(twsi_device, dev_addr, internal_addr,
        num_bytes, ia_width_bytes, data) == -1)
    {
        bdk_error("%s: TWSI temp sensor 7 - setting failed\n",__FUNCTION__);
        goto skip;
    }

    /*setting alert mode*/
    internal_addr = TEMP_SENSOR_ALERT_MODE_RW_ADDR;
    data = TEMP_ALERT_MODE_COMPARATOR;
    if (bdk_device_twsi_write_ia(twsi_device, dev_addr, internal_addr,
        num_bytes, ia_width_bytes, data) == -1)
    {
        bdk_error("%s: TWSI temp sensor 8 - setting failed\n",__FUNCTION__);
        goto skip;
    }

skip:
    bdk_device_gpio_setup(gpio_device, GPIO_TEMP_SWITCH_DEVICE, 1, 0, 1, 0);
    return;
}

static const bdk_boot_callbacks_t cn3380_250sv_v3 = {
    .board_name = "cn3380_250sv_v3",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(cn3380_250sv_v3);
