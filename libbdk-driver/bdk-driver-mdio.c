/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pccpf.h"
#include "libbdk-arch/bdk-csrs-smi.h"

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(MDIO);

/* To maintain backwards compatibility for the old MDIO API we need
   to lookup the MDIO device on the ECAM bus by ID. This defines
   the ID */
#define MDIO_DEVID BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_SMI)

#define BDK_MDIO_TIMEOUT   100000 /* 100 millisec */

/* Operating request encodings. */
#define MDIO_CLAUSE_22_WRITE    0
#define MDIO_CLAUSE_22_READ     1

#define MDIO_CLAUSE_45_ADDRESS  0
#define MDIO_CLAUSE_45_WRITE    1
#define MDIO_CLAUSE_45_READ_INC 2
#define MDIO_CLAUSE_45_READ     3

/**
 * The EBB9XXX boards installed muxes in the SMI/MDIO bus for modules.
 * Rather than using a standard TWSI part, they used the CPLD with a
 * custom register layout. As a hack to support this, MDIO bus numbers
 * 16+ are used as special keys to select these muxes. PHYs must be
 * accessed by knowing which CPLD select to enable for which module
 * connector. Yep, this is awful for software.
 *
 * @param device MDIO device
 * @param bus_id Original MDIO bus number
 *
 * @return New bus number for MDIO access
 */
static int ebb9x_mdio_switch(const bdk_device_t *device, int bus_id)
{
    static int require_mdio_switch = -1;
    if (require_mdio_switch == -1)
    {
        const char *board = bdk_config_get_str(BDK_CONFIG_BOARD_MODEL);
        require_mdio_switch = (strncasecmp(board, "EBB9", 4) == 0);
    }
    if (!require_mdio_switch)
        return bus_id;

    int twsi_bus = 0;           /* CPLD is on TWSI bus 0 */
    int twsi_address = 0x6c;    /* CPLD TWSI address is 0x6c */
    int twsi_reg = 0x28;        /* CPLD register to control MDIO, 8 bits */

    /* Bus 16-23 use MDIO 0 and selects 0-7. Bus 24-31 use MDIO 1 and selects 0-7 */
    int mdio_bus = (bus_id >= 16) ? (bus_id - 16) >> 3 : bus_id;
    /* Bits are active low */
    int mdio_select = (bus_id >= 16) ? ~(1 << (bus_id & 0x7)) : 0x00;

    /* Get the TWSI device */
    bdk_device_t *twsi_dev = bdk_device_lookup(device->node, BDK_DEVICE_DEVID(BDK_PCC_DEV_IDL_E_MIO_TWS), twsi_bus);
    /* Write the CPLD register */
    bdk_device_twsi_write_ia(twsi_dev, twsi_address, twsi_reg, 1, 1, mdio_select);
    return mdio_bus;
}

/**
 * Helper function to put MDIO interface into clause 45 mode
 *
 * @param bus_id
 */
static void __bdk_mdio_set_clause45_mode(const bdk_device_t *device, int bus_id)
{
    bdk_smi_x_clk_t smi_clk;
    /* Put bus into clause 45 mode */
    smi_clk.u = BDK_BAR_READ(device, BDK_SMI_X_CLK(bus_id));
    if (smi_clk.s.mode != 1)
    {
        smi_clk.s.mode = 1;
        smi_clk.s.preamble = 1;
        BDK_BAR_WRITE(device, BDK_SMI_X_CLK(bus_id), smi_clk.u);
    }
}

/**
 * Helper function to put MDIO interface into clause 22 mode
 *
 * @param bus_id
 */
static void __bdk_mdio_set_clause22_mode(const bdk_device_t *device, int bus_id)
{
    bdk_smi_x_clk_t smi_clk;
    /* Put bus into clause 22 mode */
    smi_clk.u = BDK_BAR_READ(device, BDK_SMI_X_CLK(bus_id));
    if (smi_clk.s.mode != 0)
    {
        smi_clk.s.mode = 0;
        BDK_BAR_WRITE(device, BDK_SMI_X_CLK(bus_id), smi_clk.u);
    }
}

/**
 * @INTERNAL
 * Function to read SMIX_RD_DAT and check for timeouts. This
 * code sequence is done fairly often, so put in in one spot.
 *
 * @param bus_id SMI/MDIO bus to read
 *
 * @return Value of SMIX_RD_DAT. pending will be set on
 *         a timeout.
 */
static bdk_smi_x_rd_dat_t __bdk_mdio_read_rd_dat(const bdk_device_t *device, int bus_id)
{
    bdk_smi_x_rd_dat_t smi_rd;
    uint64_t done = bdk_clock_get_count(BDK_CLOCK_TIME) + (uint64_t)BDK_MDIO_TIMEOUT *
                       bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;
    do
    {
        bdk_wait(1000);
        smi_rd.u = BDK_BAR_READ(device, BDK_SMI_X_RD_DAT(bus_id));
    } while (smi_rd.s.pending && (bdk_clock_get_count(BDK_CLOCK_TIME) < done));
    return smi_rd;
}


/**
 * Perform an MII read. This function is used to read PHY
 * registers controlling auto negotiation.
 *
 * @param bus_id   MDIO bus number. Zero on most chips, but some chips (ex CN56XX)
 *                 support multiple buses.
 * @param phy_id   The MII phy id
 * @param location Register location to read
 *
 * @return Result from the read or -1 on failure
 */
int bdk_mdio_read(bdk_node_t node, int bus_id, int phy_id, int location)
{
    const bdk_device_t *device = bdk_device_lookup(node, MDIO_DEVID, 0);
    if (!device)
    {
        bdk_error("MDIO: ECAM device not found\n");
        return -1;
    }

    /* Special hack for EBB9XXX */
    bus_id = ebb9x_mdio_switch(device, bus_id);

    bdk_smi_x_cmd_t smi_cmd;
    bdk_smi_x_rd_dat_t smi_rd;

    __bdk_mdio_set_clause22_mode(device, bus_id);

    smi_cmd.u = 0;
    smi_cmd.s.phy_op = MDIO_CLAUSE_22_READ;
    smi_cmd.s.phy_adr = phy_id;
    smi_cmd.s.reg_adr = location;
    BDK_BAR_WRITE(device, BDK_SMI_X_CMD(bus_id), smi_cmd.u);

    smi_rd = __bdk_mdio_read_rd_dat(device, bus_id);

    /* Special hack for EBB9XXX */
    ebb9x_mdio_switch(device, 0);

    if (smi_rd.s.val)
        return smi_rd.s.dat;
    else
        return -1;
}


/**
 * Perform an MII write. This function is used to write PHY
 * registers controlling auto negotiation.
 *
 * @param bus_id   MDIO bus number. Zero on most chips, but some chips (ex CN56XX)
 *                 support multiple buses.
 * @param phy_id   The MII phy id
 * @param location Register location to write
 * @param val      Value to write
 *
 * @return -1 on error
 *         0 on success
 */
int bdk_mdio_write(bdk_node_t node, int bus_id, int phy_id, int location, int val)
{
    const bdk_device_t *device = bdk_device_lookup(node, MDIO_DEVID, 0);
    if (!device)
    {
        bdk_error("MDIO: ECAM device not found\n");
        return -1;
    }

    /* Special hack for EBB9XXX */
    bus_id = ebb9x_mdio_switch(device, bus_id);

    bdk_smi_x_cmd_t smi_cmd;
    bdk_smi_x_wr_dat_t smi_wr;

    __bdk_mdio_set_clause22_mode(device, bus_id);

    smi_wr.u = 0;
    smi_wr.s.dat = val;
    BDK_BAR_WRITE(device, BDK_SMI_X_WR_DAT(bus_id), smi_wr.u);

    smi_cmd.u = 0;
    smi_cmd.s.phy_op = MDIO_CLAUSE_22_WRITE;
    smi_cmd.s.phy_adr = phy_id;
    smi_cmd.s.reg_adr = location;
    BDK_BAR_WRITE(device, BDK_SMI_X_CMD(bus_id), smi_cmd.u);

    if (BDK_BAR_WAIT_FOR_FIELD(device, BDK_SMI_X_WR_DAT(bus_id), pending, ==, 0, BDK_MDIO_TIMEOUT))
    {
        /* Special hack for EBB9XXX */
        ebb9x_mdio_switch(device, 0);
        return -1;
    }

    /* Special hack for EBB9XXX */
    ebb9x_mdio_switch(device, 0);

    return 0;
}

/**
 * Perform an IEEE 802.3 clause 45 MII read. This function is used to read PHY
 * registers controlling auto negotiation.
 *
 * @param bus_id   MDIO bus number. Zero on most chips, but some chips (ex CN56XX)
 *                 support multiple buses.
 * @param phy_id   The MII phy id
 * @param device   MDIO Manageable Device (MMD) id
 * @param location Register location to read
 *
 * @return Result from the read or -1 on failure
 */

int bdk_mdio_45_read(bdk_node_t node, int bus_id, int phy_id, int device, int location)
{
    const bdk_device_t *ecam_device = bdk_device_lookup(node, MDIO_DEVID, 0);
    if (!ecam_device)
    {
        bdk_error("MDIO: ECAM device not found\n");
        return -1;
    }

    /* Special hack for EBB9XXX */
    bus_id = ebb9x_mdio_switch(ecam_device, bus_id);

    bdk_smi_x_cmd_t smi_cmd;
    bdk_smi_x_rd_dat_t smi_rd;
    bdk_smi_x_wr_dat_t smi_wr;

    __bdk_mdio_set_clause45_mode(ecam_device, bus_id);

    smi_wr.u = 0;
    smi_wr.s.dat = location;
    BDK_BAR_WRITE(ecam_device, BDK_SMI_X_WR_DAT(bus_id), smi_wr.u);

    smi_cmd.u = 0;
    smi_cmd.s.phy_op = MDIO_CLAUSE_45_ADDRESS;
    smi_cmd.s.phy_adr = phy_id;
    smi_cmd.s.reg_adr = device;
    BDK_BAR_WRITE(ecam_device, BDK_SMI_X_CMD(bus_id), smi_cmd.u);

    if (BDK_BAR_WAIT_FOR_FIELD(ecam_device, BDK_SMI_X_WR_DAT(bus_id), pending, ==, 0, BDK_MDIO_TIMEOUT))
    {
        /* Special hack for EBB9XXX */
        ebb9x_mdio_switch(ecam_device, 0);
        bdk_error("bdk_mdio_45_read: bus_id %d phy_id %2d device %2d register %2d   TIME OUT(address)\n", bus_id, phy_id, device, location);
        return -1;
    }

    smi_cmd.u = 0;
    smi_cmd.s.phy_op = MDIO_CLAUSE_45_READ;
    smi_cmd.s.phy_adr = phy_id;
    smi_cmd.s.reg_adr = device;
    BDK_BAR_WRITE(ecam_device, BDK_SMI_X_CMD(bus_id), smi_cmd.u);

    smi_rd = __bdk_mdio_read_rd_dat(ecam_device, bus_id);

    /* Special hack for EBB9XXX */
    ebb9x_mdio_switch(ecam_device, 0);

    if (smi_rd.s.pending)
    {
        bdk_error("bdk_mdio_45_read: bus_id %d phy_id %2d device %2d register %2d   TIME OUT(data)\n", bus_id, phy_id, device, location);
        return -1;
    }

    if (smi_rd.s.val)
        return smi_rd.s.dat;
    else
    {
        bdk_error("bdk_mdio_45_read: bus_id %d phy_id %2d device %2d register %2d   INVALID READ\n", bus_id, phy_id, device, location);
        return -1;
    }
}

/**
 * Perform an IEEE 802.3 clause 45 MII write. This function is used to write PHY
 * registers controlling auto negotiation.
 *
 * @param bus_id   MDIO bus number. Zero on most chips, but some chips (ex CN56XX)
 *                 support multiple buses.
 * @param phy_id   The MII phy id
 * @param device   MDIO Manageable Device (MMD) id
 * @param location Register location to write
 * @param val      Value to write
 *
 * @return -1 on error
 *         0 on success
 */
int bdk_mdio_45_write(bdk_node_t node, int bus_id, int phy_id, int device, int location,
                                     int val)
{
    const bdk_device_t *ecam_device = bdk_device_lookup(node, MDIO_DEVID, 0);
    if (!ecam_device)
    {
        bdk_error("MDIO: ECAM device not found\n");
        return -1;
    }

    /* Special hack for EBB9XXX */
    bus_id = ebb9x_mdio_switch(ecam_device, bus_id);

    bdk_smi_x_cmd_t smi_cmd;
    bdk_smi_x_wr_dat_t smi_wr;

    __bdk_mdio_set_clause45_mode(ecam_device, bus_id);

    smi_wr.u = 0;
    smi_wr.s.dat = location;
    BDK_BAR_WRITE(ecam_device, BDK_SMI_X_WR_DAT(bus_id), smi_wr.u);

    smi_cmd.u = 0;
    smi_cmd.s.phy_op = MDIO_CLAUSE_45_ADDRESS;
    smi_cmd.s.phy_adr = phy_id;
    smi_cmd.s.reg_adr = device;
    BDK_BAR_WRITE(ecam_device, BDK_SMI_X_CMD(bus_id), smi_cmd.u);

    if (BDK_BAR_WAIT_FOR_FIELD(ecam_device, BDK_SMI_X_WR_DAT(bus_id), pending, ==, 0, BDK_MDIO_TIMEOUT))
    {
        /* Special hack for EBB9XXX */
        ebb9x_mdio_switch(ecam_device, 0);
        return -1;
    }

    smi_wr.u = 0;
    smi_wr.s.dat = val;
    BDK_BAR_WRITE(ecam_device, BDK_SMI_X_WR_DAT(bus_id), smi_wr.u);

    smi_cmd.u = 0;
    smi_cmd.s.phy_op = MDIO_CLAUSE_45_WRITE;
    smi_cmd.s.phy_adr = phy_id;
    smi_cmd.s.reg_adr = device;
    BDK_BAR_WRITE(ecam_device, BDK_SMI_X_CMD(bus_id), smi_cmd.u);

    if (BDK_BAR_WAIT_FOR_FIELD(ecam_device, BDK_SMI_X_WR_DAT(bus_id), pending, ==, 0, BDK_MDIO_TIMEOUT))
    {
        /* Special hack for EBB9XXX */
        ebb9x_mdio_switch(ecam_device, 0);
        return -1;
    }

    /* Special hack for EBB9XXX */
    ebb9x_mdio_switch(ecam_device, 0);
    return 0;
}


/**
 * The MDIO probe function
 *
 * @param device MDIO/SMI to probe
 *
 * @return Zero on success, negative on failure
 */
static int probe(bdk_device_t *device)
{
    /* Change the device name */
    bdk_device_rename(device, "N%d.MDIO", device->node);
    return 0;
}

/**
 * MDIO init() function
 *
 * @param device MDIO/SMI to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    if (bdk_is_platform(BDK_PLATFORM_ASIM))
        return 0;

    if (bdk_is_model(OCTEONTX_CN8XXX))
    {
        /* Change drive strength bits to fix issues when a QLM cable
           is connected, creating a long spur path */
        BDK_CSR_MODIFY(c, device->node, BDK_SMI_DRV_CTL,
            c.s.pctl = 7; /* 30 ohm */
            c.s.nctl = 7); /* 30 ohm */
    }

    for (int i = 0; i < 2; i++)
    {
        if (bdk_is_model(OCTEONTX_CN9XXX))
        {
            /* Needed for CN96XX to make SMI/MDIO work */
            BDK_CSR_MODIFY(c, device->node, BDK_SMI_X_CLK(i),
                c.s.sample_hi = 1;
                c.s.sample = 8;
                c.s.sample_mode = 1);
        }
        BDK_BAR_MODIFY(c, device, BDK_SMI_X_EN(i), c.s.en = 1);
    }

    return 0;
}

bdk_driver_t __bdk_driver_mdio = {
    .id = MDIO_DEVID,
    .name = "MDIO",
    .probe = probe,
    .init = init,
};

