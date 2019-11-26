/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-cpc.h"
#include "libbdk-arch/bdk-csrs-gti.h"
#include "libbdk-arch/bdk-csrs-mio_emm.h"
#include "libbdk-arch/bdk-csrs-mrml.h"
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-xcp.h"

BDK_REQUIRE_DEFINE(DRIVER_XCP);

typedef union
{
    uint32_t u;
    struct
    {
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32_t rsvd_mbz : 30;     /* Must be zero */
        uint32_t channel_error : 1; /* Channel error? */
        uint32_t channel_free : 1;  /* Set if channel is free */
#else
        uint32_t channel_free : 1;  /* Set if channel is free */
        uint32_t channel_error : 1; /* Channel error? */
        uint32_t rsvd_mbz : 30;     /* Must be zero */
#endif
    } s;
} scmi_chan_status_t;

typedef union
{
    uint32_t u;
    struct
    {
#if __BYTE_ORDER == __BIG_ENDIAN
        uint32_t reserved : 4;      /* Reserved by SCMI, must be zero */
        uint32_t token : 10;        /* SCMI Token */
        uint32_t protocol_id : 8;   /* SCMI Protocol ID */
        uint32_t message_type : 2;  /* SCMI Message Type */
        uint32_t message_id : 8;    /* SCMI Message ID */
#else
        uint32_t message_id : 8;    /* SCMI Message ID */
        uint32_t message_type : 2;  /* SCMI Message Type */
        uint32_t protocol_id : 8;   /* SCMI Protocol ID */
        uint32_t token : 10;        /* SCMI Token */
        uint32_t reserved : 4;      /* Reserved by SCMI, must be zero */
#endif
    } s;
} scmi_header_t;

typedef union
{
    uint32_t u[16]; /* Room for 7 word header and 9 words of payload. Can be resized */
    struct
    {
        uint32_t rsvd1_mbz;         /* 0x00: Must be zero */
        scmi_chan_status_t status;  /* 0x04: Channel status */
        uint64_t rsvd2_mbz;         /* 0x08: Must be zero */
        uint32_t flags;             /* 0x10: Flags, unused by BDK */
        uint32_t length;            /* 0x14: Length */
        scmi_header_t header;       /* 0x18: Message header */
        uint32_t payload[0];        /* 0x1c: SCMI Message payload */
    } s;
} scmi_mailbox_t;

/**
 * The XCP probe function
 *
 * @param device XCP to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    /* Change the device name */
    if (device->instance == BDK_CPC_XCP_MAP_E_SCP)
        bdk_device_rename(device, "N%d.SCP", device->node);
    else if (device->instance == BDK_CPC_XCP_MAP_E_MCP)
        bdk_device_rename(device, "N%d.MCP", device->node);
    else
        bdk_device_rename(device, "N%d.XCP%d", device->node, device->instance);
    return 0;
}

/**
 * Called after the DVFS message to correct for SCLK changing
 *
 * @param node   Node SCLK changed on
 */
static void update_sclk(bdk_node_t node, uint64_t old_sclk_rate)
{
    uint64_t sclk = bdk_clock_get_rate(node, BDK_CLOCK_SCLK);

    /* Update GTI for the new SCLK */
    BDK_TRACE(INIT, "Updating GTI for new SCLK rate\n");
    BDK_CSR_MODIFY(c, node, BDK_GTI_CC_CNTCR,
        c.s.en = 0);
    uint64_t inc = (BDK_GTI_RATE << 32) / sclk;
    BDK_CSR_WRITE(node, BDK_GTI_CC_CNTRATE, inc);
    BDK_CSR_MODIFY(c, node, BDK_GTI_CC_CNTCR,
        c.s.en = 1);

    /* CN96XX HRM says this register must be enabled before scan, but
       doesn't say why */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        BDK_TRACE(INIT, "Updating MRML timeout for new SCLK rate\n");
        /* Program MRML_CMD_TO[tovalue] to be 100SCLK + 100RCLK in SCLK cycles */
        BDK_CSR_MODIFY(c, node, BDK_MRML_CMD_TO,
            c.s.tovalue = 100ull + 100ull * sclk / bdk_clock_get_rate(node, BDK_CLOCK_RCLK));
    }

    BDK_CSR_INIT(emm_cfg, node, BDK_MIO_EMM_CFG);
    if (!bdk_is_platform(BDK_PLATFORM_ASIM) && emm_cfg.s.bus_ena)
    {
        /* Change the EMMC clock */
        BDK_TRACE(INIT, "Updating eMMC clock for new SCLK rate\n");
        BDK_CSR_INIT(mode_reg_orig, node, BDK_MIO_EMM_MODEX(0));
        BDK_CSR_DEFINE(emm_switch, BDK_MIO_EMM_SWITCH);
        emm_switch.u = 0;
        emm_switch.s.bus_id = 0;
        emm_switch.s.switch_exe = 0;
        emm_switch.s.hs400_timing = mode_reg_orig.s.hs400_timing;
        emm_switch.s.hs200_timing = mode_reg_orig.s.hs200_timing;
        emm_switch.s.hs_timing = mode_reg_orig.s.hs_timing;
        emm_switch.s.bus_width = mode_reg_orig.s.bus_width;
        emm_switch.s.power_class = mode_reg_orig.s.power_class;
        emm_switch.s.clk_hi = sclk * mode_reg_orig.s.clk_hi / old_sclk_rate;
        emm_switch.s.clk_lo = sclk * mode_reg_orig.s.clk_lo / old_sclk_rate;
        BDK_CSR_WRITE(node, BDK_MIO_EMM_SWITCH, emm_switch.u);
        bdk_wait_usec(2000);

        /* Verify eMMC update */
        BDK_CSR_INIT(mode_reg_update, node, BDK_MIO_EMM_MODEX(0));
        if ((emm_switch.s.clk_hi != mode_reg_update.s.clk_hi) ||
            (emm_switch.s.clk_lo != mode_reg_update.s.clk_lo))
        {
            bdk_error("eMMC clock failed to update for new SCLK rate\n");
        }

        BDK_TRACE(INIT, "Updating eMMC watchdog for new SCLK rate\n");
        uint64_t wdog_value = BDK_CSR_READ(node, BDK_MIO_EMM_WDOG);
        wdog_value = wdog_value * sclk / old_sclk_rate;
        BDK_CSR_WRITE(node, BDK_MIO_EMM_WDOG, wdog_value);
    }
}

/**
 * Called to setup the SCP
 *
 * @param device SCP instance
 *
 * @return Zero on success, negative on failure
 */
static int scp_init(bdk_device_t *device)
{
    uint64_t old_sclk_rate = bdk_clock_get_rate(device->node, BDK_CLOCK_SCLK);

    /* Build a DVFS payload for telling the SCP how to control the
       chip */
    BDK_TRACE(INIT, "%s: Building DVFS payload\n", device->name);
    union bdk_cpc_dvfs_config_s dvfs;
    memset(&dvfs, 0, sizeof(dvfs));
    dvfs.s.vrm_temp_high =              bdk_config_get_int(BDK_CONFIG_VRM_TEMP_HIGH, device->node);
    dvfs.s.rclk_freq_max =              bdk_config_get_int(BDK_CONFIG_RCLK_FREQ_MAX, device->node);
    dvfs.s.rclk_freq_min =              bdk_config_get_int(BDK_CONFIG_RCLK_FREQ_MIN, device->node);
    dvfs.s.dvfs_config_version =        0x9300;
    dvfs.s.cptclk_freq =                bdk_config_get_int(BDK_CONFIG_CPTCLK_FREQ, device->node);
    dvfs.s.vdd_core_tolerance =         bdk_config_get_int(BDK_CONFIG_VDD_CORE_TOLERANCE, device->node);
    dvfs.s.vdd_sys_tolerance =          bdk_config_get_int(BDK_CONFIG_VDD_SYS_TOLERANCE, device->node);
    dvfs.s.vrm_temp_trip =              bdk_config_get_int(BDK_CONFIG_VRM_TEMP_TRIP, device->node);
    dvfs.s.dvfs_power_budget =          bdk_config_get_int(BDK_CONFIG_DVFS_POWER_BUDGET, device->node);
    dvfs.s.dvfs_power_control_mode =    bdk_config_get_int(BDK_CONFIG_DVFS_POWER_CONTROL_MODE, device->node);
    dvfs.s.dvfs_thermal_hot =           bdk_config_get_int(BDK_CONFIG_DVFS_THERMAL_HOT, device->node);
    dvfs.s.sclk_freq =                  bdk_config_get_int(BDK_CONFIG_SCLK_FREQ, device->node);
    dvfs.s.failsafe_timeout =           bdk_config_get_int(BDK_CONFIG_SCP_FAILSAFE_TIMEOUT, device->node);
    dvfs.s.scp_uart_num =               bdk_config_get_int(BDK_CONFIG_SCP_UART_NUM, device->node);
    dvfs.s.mcp_disable =                bdk_config_get_int(BDK_CONFIG_SCP_MCP_DISABLE, device->node);
    dvfs.s.force_secondary_boot =       bdk_config_get_int(BDK_CONFIG_SCP_FORCE_SECONDARY_BOOT, device->node);
    dvfs.s.wakeup_mode =                bdk_config_get_int(BDK_CONFIG_SCP_WAKEUP_MODE, device->node);
    dvfs.s.dvfs_thermal_hot_backoff =   bdk_config_get_int(BDK_CONFIG_DVFS_THERMAL_HOT_BACKOFF, device->node);
    dvfs.s.active_threshold =           bdk_config_get_int(BDK_CONFIG_SCP_ACTIVE_THRESHOLD, device->node);
    dvfs.s.bclk_freq_max =              bdk_config_get_int(BDK_CONFIG_BCLK_FREQ_MAX, device->node);
    dvfs.s.bclk_freq_min =              bdk_config_get_int(BDK_CONFIG_BCLK_FREQ_MIN, device->node);
    dvfs.s.dspclk_freq_max =            bdk_config_get_int(BDK_CONFIG_DSPCLK_FREQ_MAX, device->node);
    dvfs.s.dspclk_freq_min =            bdk_config_get_int(BDK_CONFIG_DSPCLK_FREQ_MIN, device->node);
    dvfs.s.vdd_core_ripple =            bdk_config_get_int(BDK_CONFIG_VDD_CORE_RIPPLE, device->node);
    dvfs.s.vdd_sys_ripple =             bdk_config_get_int(BDK_CONFIG_VDD_SYS_RIPPLE, device->node);
    dvfs.s.vdd_core_compensation =      bdk_config_get_int(BDK_CONFIG_VDD_CORE_COMPENSATION, device->node) * 10; /* Convert percent to 1000 scale */
    dvfs.s.vdd_sys_compensation =       bdk_config_get_int(BDK_CONFIG_VDD_SYS_COMPENSATION, device->node) * 10; /* Convert percent to 1000 scale */

    /* Package the DVFS payload as a SCMI message  */
    BDK_TRACE(INIT, "%s: Building SCMI message for DVFS payload\n", device->name);
    volatile scmi_mailbox_t *mailbox = bdk_phys_to_ptr(bdk_numa_get_address(device->node, BDK_CPC_RAM_MEMX(0x58000 / 8)));
    mailbox->s.rsvd1_mbz = 0;
    mailbox->s.status.u = 0;
    mailbox->s.rsvd2_mbz = 0;
    mailbox->s.flags = 0;       /* No flags */
    mailbox->s.length = bdk_cpu_to_le32(sizeof(dvfs));
    scmi_header_t header;
    header.u = 0;
    header.s.token = 0; /* Unused */
    header.s.protocol_id = 0xb0; /* Cavium implementation defined */
    header.s.message_type = 0x00; /* Command message */
    header.s.message_id = 0x03; /* CPC_DVFS_CONFIG_S */
    mailbox->s.header.u = bdk_cpu_to_le32(header.u);
#if __BYTE_ORDER == __BIG_ENDIAN
    uint32_t *ptr = (uint32_t *)&dvfs;
    for (unsigned int i = 0; i < sizeof(dvfs) / 4; i+=2)
    {
        mailbox->s.payload[i+1] = bdk_cpu_to_le32(*ptr++);
        mailbox->s.payload[i] = bdk_cpu_to_le32(*ptr++);
    }
#else
    uint32_t *ptr = (uint32_t *)&dvfs;
    for (unsigned int i = 0; i < sizeof(dvfs) / 4; i++)
        mailbox->s.payload[i] = bdk_cpu_to_le32(*ptr++);
#endif
    BDK_WMB;

    BDK_TRACE(INIT, "%s: Sending SCMI message\n", device->name);
    /* Write SCMI message doorbell AP secure to SCP  */
    BDK_CSR_WRITE(device->node, BDK_XCPX_DEVX_XCP_MBOX(device->instance, BDK_XCP_MBOX_DEV_E_AP_SECURE0), 1);

    BDK_TRACE(INIT, "%s: Waiting for SCMI message ACK\n", device->name);
    uint64_t timeout = bdk_clock_get_count(BDK_CLOCK_TIME) + bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
    if (bdk_is_platform(BDK_PLATFORM_EMULATOR)) /* Shorten to 1ms */
        timeout += bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000;
    else
        timeout += bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
    scmi_chan_status_t status;
    status.u = bdk_le32_to_cpu(mailbox->s.status.u);
    while (!status.s.channel_free)
    {
        if (bdk_clock_get_count(BDK_CLOCK_TIME) > timeout)
        {
            bdk_error("%s: Timeout waiting for SCMI message for response\n", device->name);
            return -1;
        }
        bdk_wait_usec(1);
        status.u = bdk_le32_to_cpu(mailbox->s.status.u);
    }

    /* Check channel_status is free, no error, and reserved is zero */
    if (!status.s.channel_free || status.s.channel_error || status.s.rsvd_mbz)
    {
        bdk_error("%s: SCMI DVFS channel status incorrect 0x%x\n", device->name, status.u);
        return -1;
    }
    /* Check response length, expect 8 byte status */
    if (bdk_le32_to_cpu(mailbox->s.length) != 8)
    {
        bdk_error("%s: SCMI DVFS response length incorrect, %d instead of 8\n", device->name, mailbox->s.length);
        return -1;
    }

    /* Check status */
    if (bdk_le32_to_cpu(mailbox->s.payload[0]) != 0)
    {
        bdk_error("%s: SCMI DVFS response status incorrect, 0x%x instead of 0\n", device->name, mailbox->s.payload[0]);
        return -1;
    }

    BDK_TRACE(INIT, "%s: SCMI message complete\n", device->name);

    update_sclk(device->node, old_sclk_rate);

    /* Wait for SCP to signal power programming is correct */
    timeout = bdk_config_get_int(BDK_CONFIG_SCP_FAIL_TIMEOUT, device->node) * 1000000;
    if (BDK_CSR_WAIT_FOR_FIELD(device->node, BDK_RST_COLD_DATAX(2), data & 4, ==, 0, timeout))
    {
        if (!bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            bdk_error("%s: VRM problem detected - check AVS bus enable\n", device->name);
            switch (bdk_config_get_int(BDK_CONFIG_SCP_FAIL_ACTION, device->node))
            {
                case 1: /* Reboot the system */
                    printf("Rebooting per SCP fail action\n");
                    bdk_reset_chip(device->node);
                    break;
                case 2: /* Halt forever*/
                    printf("Hanging per SCP fail action\n");
                    __bdk_die();
                    break;
                default: /* Continue */
                    printf("Continuing per SCP fail action\n");
                    break;
            }
        }
    }

    return 0;
}

/**
 * XCP init() function
 *
 * @param device XCP to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    BDK_TRACE(INIT, "%s: Init\n", device->name);
    return 0;
}

/**
 * Tell SCP to start DVFS and program the clocks. Note that this function
 * is called on all chips, even those without a SCP.
 *
 * @return Zero on success, negative on failure
 */
int bdK_scp_init_dvfs(void)
{
    bdk_device_t *device = bdk_device_lookup(bdk_numa_local(),
        BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_XCP), BDK_CPC_XCP_MAP_E_SCP);

    if (device)
    {
        /* Check for RST_BOOT_STATUS being zero, meaning the SCP never
           filled in boot info. Take this as a hint that we aren't
           running the SCP and skip initialization */
        BDK_CSR_INIT(rst_boot_status, device->node, BDK_RST_BOOT_STATUS);
        if (!rst_boot_status.u)
            BDK_TRACE(INIT, "SCP didn't fill RST_BOOT_STATUS, skipping DVFS\n");
        else
            scp_init(device);
    }

    uint64_t rclk = bdk_clock_get_rate(device->node, BDK_CLOCK_RCLK);
    uint64_t sclk = bdk_clock_get_rate(device->node, BDK_CLOCK_SCLK);
    printf("RCLK:     %lu Mhz\n", rclk / 1000000);
    printf("SCLK:     %lu Mhz\n", sclk / 1000000);

    /* CPTCLK for CN96XX, CN98XX */
    if (bdk_is_model(OCTEONTX_CN96XX) || bdk_is_model(OCTEONTX_CN98XX))
    {
        BDK_CSR_INIT(pll, device->node, BDK_RST_CPT_PLL);
        printf("CPT-CLK:  %u Mhz\n", 50 * pll.s.cur_mul);
    }
    if (bdk_is_model(OCTEONTX_CN98XX))
    {
        BDK_CSR_INIT(pll, device->node, BDK_RST_CPT1_PLL);
        printf("CPT1-CLK: %u Mhz\n", 50 * pll.s.cur_mul);
    }

    /* BPHYCLK and DSPCLK for CNF95XX or LOKI */
    if (bdk_is_model(OCTEONTX_CNF95XX) || bdk_is_model(OCTEONTX_LOKI))
    {
        BDK_CSR_INIT(bphy, device->node, BDK_RST_BPHY_PLL);
        BDK_CSR_INIT(dsp, device->node, BDK_RST_DSP_PLL);
        printf("BPHY-CLK: %u Mhz\n", 50 * bphy.s.cur_mul);
        printf("DSP-CLK:  %u Mhz\n", 50 * dsp.s.cur_mul);
    }
    printf("\n");

    return 0;
}

bdk_driver_t __bdk_driver_xcp = {
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_XCP),
    .name = "XCP",
    .probe = probe,
    .init = init,
};
