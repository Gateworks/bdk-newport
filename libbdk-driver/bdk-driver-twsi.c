/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-mio_tws.h"

#define RECOVERY_UDELAY  5
#define RECOVERY_CLK_CNT 9
#define ARBLOST_UDELAY   5000 /* 5ms */

BDK_REQUIRE_DEFINE(DRIVER_TWSI);

/**
 * The TWSI probe function
 *
 * @param device TWSI to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    bdk_device_rename(device, "N%d.TWSI%d", device->node, device->instance);
    return 0;
}

/**
 * TWSI init() function
 *
 * @param device TWSI to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    const int TWSI_BUS_FREQ = 100000;   /* 100 KHz */
    /* CN8XXX uses SCK, CN9XXX uses 100Mhz main reference */
    const int io_clock_hz = bdk_clock_get_rate(device->node,
        bdk_is_model(OCTEONTX_CN8XXX) ? BDK_CLOCK_SCLK : BDK_CLOCK_MAIN_REF);

    int tclk;

    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        const int TWSI_THP = 0x18;
        tclk = io_clock_hz / (2 * (TWSI_THP + 1));
    }
    else
    {
        const int TWSI_THP = 0x3;
        tclk = io_clock_hz / (TWSI_THP + 2);
    }

    int N_divider;
    int M_divider;

    /* Set the TWSI clock to a conservative TWSI_BUS_FREQ */
    for (N_divider = 0; N_divider < 8; N_divider++)
    {
        int fsamp = tclk / (1 << N_divider);
        M_divider = fsamp / TWSI_BUS_FREQ / 10 - 1;
        if (M_divider < 16)
            break;
    }

    BDK_TRACE(DEVICE, "%s: Setting clock TCLK=%d, M=%d, N=%d\n", device->name, tclk, M_divider, N_divider);

    BDK_CSR_DEFINE(sw_twsi, BDK_MIO_TWSX_SW_TWSI(bus));
    sw_twsi.u = 0;
    sw_twsi.s.v = 1;       /* Clear valid bit */
    sw_twsi.s.op = 0x6;    /* See EOP field */
    sw_twsi.s.r = 0;       /* Select CLKCTL when R = 0 */
    sw_twsi.s.eop_ia = 3;  /* R=0 selects CLKCTL, R=1 selects STAT */
    sw_twsi.s.data = ((M_divider & 0xf) << 3) | ((N_divider & 0x7) << 0);

    /* Only init non-slave ports */
    BDK_CSR_INIT(state, device->node, BDK_MIO_TWSX_SW_TWSI(device->instance));
    if (!state.s.slonly)
        BDK_CSR_WRITE(device->node, BDK_MIO_TWSX_SW_TWSI(device->instance), sw_twsi.u);

    /* Allow longer transactions on CN9XXX */
    if (!bdk_is_model(OCTEONTX_CN8XXX))
    {
        BDK_CSR_MODIFY(c, device->node, BDK_MIO_TWSX_ACCESS_WDOG(device->instance),
            c.s.wdog_cnt = 0x100000);
    }
    return 0;
}

/**
 * Do a twsi bus recovery in the case when the last transaction
 * on the bus has been left unfinished.
 *
 * @param device Device to access
 */
static void recover_bus(bdk_device_t *device)
{
    /* read TWSX_INT */
    BDK_CSR_INIT(twsx_int, device->node, BDK_MIO_TWSX_INT(device->instance));

    for (int i = 0; i < RECOVERY_CLK_CNT * 2; i++)
    {
	if (!twsx_int.s.scl_ovr)
	{
	    /* SCL shouldn't be low here */
	    if (!twsx_int.s.scl)
	    {
		bdk_error("%s: SCL is stuck low\n", device->name);
		return;
	    }

	    /* Break if SDA is high */
	    if (twsx_int.s.sda)
		break;
	}

	twsx_int.s.scl_ovr = !twsx_int.s.scl_ovr;
	BDK_CSR_WRITE(device->node, BDK_MIO_TWSX_INT(device->instance), twsx_int.u);
	bdk_wait_usec(RECOVERY_UDELAY);
    }

    /*
     * Generate STOP condition using the register overrides
     * in order to move the higher level controller out of
     * the bad state. This is a workaround for the TWSI hardware.
     */
    twsx_int.s.scl_ovr = 1;
    twsx_int.s.sda_ovr = 1;
    BDK_CSR_WRITE(device->node, BDK_MIO_TWSX_INT(device->instance), twsx_int.u);
    bdk_wait_usec(RECOVERY_UDELAY);
    twsx_int.s.scl_ovr = 0;
    BDK_CSR_WRITE(device->node, BDK_MIO_TWSX_INT(device->instance), twsx_int.u);
    bdk_wait_usec(RECOVERY_UDELAY);
    twsx_int.s.sda_ovr = 0;
    BDK_CSR_WRITE(device->node, BDK_MIO_TWSX_INT(device->instance), twsx_int.u);
}

/**
 * Do a twsi read from a 7 bit device address using an (optional)
 * internal address. Up to 4 bytes can be read at a time.
 *
 * @param device    Device to access
 * @param dev_addr  Device address (7 bit)
 * @param internal_addr
 *                  Internal address.  Can be 0, 1 or 2 bytes in width
 * @param num_bytes Number of data bytes to read (1-4)
 * @param ia_width_bytes
 *                  Internal address size in bytes (0, 1, or 2)
 *
 * @return Read data, or -1 on failure
 */
static int64_t read_ia(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes)
{
    bdk_mio_twsx_sw_twsi_t sw_twsi_val;
    bdk_mio_twsx_sw_twsi_ext_t twsi_ext;
    int retry_limit = 5;

    if (num_bytes < 1 || num_bytes > 4 || ia_width_bytes < 0 || ia_width_bytes > 2)
        return -1;
retry:
    twsi_ext.u = 0;
    sw_twsi_val.u = 0;
    sw_twsi_val.s.v = 1;
    sw_twsi_val.s.r = 1;
    sw_twsi_val.s.sovr = 1;
    sw_twsi_val.s.size = num_bytes - 1;
    sw_twsi_val.s.addr = dev_addr;

    if (ia_width_bytes > 0)
    {
        sw_twsi_val.s.op = 1;
        sw_twsi_val.s.ia = (internal_addr >> 3) & 0x1f;
        sw_twsi_val.s.eop_ia = internal_addr & 0x7;
        if (ia_width_bytes == 2)
        {
            sw_twsi_val.s.eia = 1;
            twsi_ext.s.ia = internal_addr >> 8;
            BDK_CSR_WRITE(device->node, BDK_MIO_TWSX_SW_TWSI_EXT(device->instance), twsi_ext.u);
        }
    }

    BDK_CSR_WRITE(device->node, BDK_MIO_TWSX_SW_TWSI(device->instance), sw_twsi_val.u);
    if (BDK_CSR_WAIT_FOR_FIELD(device->node, BDK_MIO_TWSX_SW_TWSI(device->instance), v, ==, 0, 10000))
    {
        if (!bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            bdk_warn("%s: Timeout waiting for read to complete...start recovering process\n",
                     device->name);
            /* perform bus recovery */
            recover_bus(device);
            if (retry_limit-- > 0)
                goto retry;
        }
        bdk_error("%s: Timeout waiting for operation to complete\n", device->name);
        return -1;
    }
    sw_twsi_val.u = BDK_CSR_READ(device->node, BDK_MIO_TWSX_SW_TWSI(device->instance));
    if (!sw_twsi_val.s.r)
    {
        /* Check the reason for the failure.  We may need to retry to handle multi-master
        ** configurations.
        ** Lost arbitration : 0x38, 0x68, 0xB0, 0x78
        ** Core busy as slave: 0x80, 0x88, 0xA0, 0xA8, 0xB8, 0xC0, 0xC8
        */
        if (sw_twsi_val.s.data == 0x38
            || sw_twsi_val.s.data == 0x68
            || sw_twsi_val.s.data == 0xB0
            || sw_twsi_val.s.data == 0x78
            || sw_twsi_val.s.data == 0x80
            || sw_twsi_val.s.data == 0x88
            || sw_twsi_val.s.data == 0xA0
            || sw_twsi_val.s.data == 0xA8
            || sw_twsi_val.s.data == 0xB8
            || sw_twsi_val.s.data == 0xC8)
        {
            /*
             * One of the arbitration lost conditions is recognized.
             * The TWSI hardware has switched to the slave mode and
             * expects the STOP condition on the bus.
             * Make a delay before next retry.
             */
            bdk_wait_usec(ARBLOST_UDELAY);
            if (retry_limit-- > 0)
                goto retry;
        }
        /* For all other errors, return an error code */
        return -1;
    }

    return (sw_twsi_val.s.data & (0xFFFFFFFF >> (32 - num_bytes*8)));
}

/**
 * Write 1-8 bytes to a TWSI device using an internal address.
 *
 * @param device    Device to access
 * @param dev_addr  TWSI device address (7 bit only)
 * @param internal_addr
 *                  TWSI internal address (0, 8, or 16 bits)
 * @param num_bytes Number of bytes to write (1-8)
 * @param ia_width_bytes
 *                  internal address width, in bytes (0, 1, 2)
 * @param data      Data to write.  Data is written MSB first on the twsi bus, and
 *                  only the lower num_bytes bytes of the argument are valid.  (If
 *                  a 2 byte write is done, only the low 2 bytes of the argument is
 *                  used.
 *
 * @return Zero on success, -1 on error
 */
static int write_ia(bdk_device_t *device, uint8_t dev_addr, uint16_t internal_addr, int num_bytes, int ia_width_bytes, uint64_t data)
{
    bdk_mio_twsx_sw_twsi_t sw_twsi_val;
    bdk_mio_twsx_sw_twsi_ext_t twsi_ext;
    int retry_limit = 5;
    int to;

    if (num_bytes < 1 || num_bytes > 8 || ia_width_bytes < 0 || ia_width_bytes > 2)
        return -1;

retry:
    twsi_ext.u = 0;
    sw_twsi_val.u = 0;
    sw_twsi_val.s.v = 1;
    sw_twsi_val.s.sovr = 1;
    sw_twsi_val.s.size = num_bytes - 1;
    sw_twsi_val.s.addr = dev_addr;
    sw_twsi_val.s.data = 0xFFFFFFFF & data;

    if (ia_width_bytes > 0)
    {
        sw_twsi_val.s.op = 1;
        sw_twsi_val.s.ia = (internal_addr >> 3) & 0x1f;
        sw_twsi_val.s.eop_ia = internal_addr & 0x7;
    }
    if (ia_width_bytes == 2)
    {
        sw_twsi_val.s.eia = 1;
        twsi_ext.s.ia = internal_addr >> 8;
    }
    if (num_bytes > 4)
        twsi_ext.s.data = data >> 32;

    BDK_CSR_WRITE(device->node, BDK_MIO_TWSX_SW_TWSI_EXT(device->instance), twsi_ext.u);
    BDK_CSR_WRITE(device->node, BDK_MIO_TWSX_SW_TWSI(device->instance), sw_twsi_val.u);
    if (BDK_CSR_WAIT_FOR_FIELD(device->node, BDK_MIO_TWSX_SW_TWSI(device->instance), v, ==, 0, 10000))
    {
        if (!bdk_is_platform(BDK_PLATFORM_ASIM))
        {
            bdk_warn("%s: Timeout waiting for write to complete...start recovering process\n",
                     device->name);
            /* perform bus recovery */
            recover_bus(device);
            if (retry_limit-- > 0)
                goto retry;
        }
        // After retry but still not success, report error and return
        bdk_error("%s: Timeout waiting for operation to complete\n", device->name);
        return -1;
    }

    /* Poll until reads succeed, or polling times out */
    to = 100;
    while (to-- > 0)
    {
        if (read_ia(device, dev_addr, 0, 1, 0) >= 0)
            break;
    }
    if (to <= 0)
        return -1;

    return 0;
}

bdk_driver_t __bdk_driver_twsi = {
    .api = BDK_DEVICE_API_TWSI,
    .id = BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_MIO_TWS),
    .name = "TWSI",
    .probe = probe,
    .init = init,
    .funcs.twsi.read_ia = read_ia,
    .funcs.twsi.write_ia = write_ia,
};
