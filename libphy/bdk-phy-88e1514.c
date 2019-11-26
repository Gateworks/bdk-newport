/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>

BDK_REQUIRE_DEFINE(DRIVER_NETPHY_88E1514);

/**
 * All SMI/MDIO accesses in this driver use this wrapper
 *
 * @param device
 * @param location
 *
 * @return
 */
static int mdio_read(bdk_device_t *device, int location)
{
    bdk_node_t node = device->node;
    int mdio_bus = device->priv.phy.smi;
    int phy_addr = device->priv.phy.address;
    return bdk_mdio_read(node, mdio_bus, phy_addr, location);
}

/**
 * All SMI/MDIO accesses in this driver use this wrapper
 *
 * @param device
 * @param location
 *
 * @return
 */
static int mdio_write(bdk_device_t *device, int location, int val)
{
    bdk_node_t node = device->node;
    int mdio_bus = device->priv.phy.smi;
    int phy_addr = device->priv.phy.address;
    return bdk_mdio_write(node, mdio_bus, phy_addr, location, val);
}

static void add(bdk_device_t *device, const char *config_str)
{
    device->priv.phy.smi = bdk_driver_extract_int(config_str, "smi", 0, 2);
    device->priv.phy.address = bdk_driver_extract_int(config_str, "addr", 0, 31);
    int qlm = bdk_driver_extract_int(config_str, "qlm", 0, bdk_qlm_get_num(device->node) - 1);
    int qlm_lane = bdk_driver_extract_int(config_str, "qlm_lane", 0, bdk_qlm_get_lanes(device->node, qlm));
    BDK_TRACE(DEVICE, "%s: 88E1514 PHY on SMI=%d, ADDR=%d QLM=%d, QLM_LANE=%d\n",
        device->name, device->priv.phy.smi, device->priv.phy.address, qlm, qlm_lane);

    bdk_netphy_register(device, 0, device->node, qlm, qlm_lane);
}

static bdk_if_link_t phy_get_speed(bdk_device_t *device, bdk_netphy_t phy)
{
    bdk_if_link_t result;
    result.u64 = 0;

    /* This code assumes we are using a Marvell Gigabit PHY. All the
        speed information can be read from register 17 in one go. Somebody
        using a different PHY will need to handle it above in the board
        specific area */
    int phy_status = mdio_read(device, 17);
    if (phy_status < 0)
        return result;

    /* If the resolve bit 11 isn't set, see if autoneg is turned off
        (bit 12, reg 0). The resolve bit doesn't get set properly when
        autoneg is off, so force it */
    if ((phy_status & (1<<11)) == 0)
    {
        bdk_mdio_phy_reg_control_t control;
        int phy_c = mdio_read(device, BDK_MDIO_PHY_REG_CONTROL);
        if (phy_c < 0)
            return result;
        control.u16 = phy_c;
        if (control.s.autoneg_enable == 0)
            phy_status |= 1<<11;
    }

    /* Only return a link if the PHY has finished auto negotiation
        and set the resolved bit (bit 11) */
    if (phy_status & (1<<11))
    {
        result.s.up = 1;
        result.s.full_duplex = ((phy_status>>13)&1);
        switch ((phy_status>>14)&3)
        {
            case 0: /* 10 Mbps */
                result.s.speed = 10;
                break;
            case 1: /* 100 Mbps */
                result.s.speed = 100;
                break;
            case 2: /* 1 Gbps */
                result.s.speed = 1000;
                break;
            case 3: /* Illegal */
                result.u64 = 0;
                break;
        }
    }
    return result;
}

static int phy_init(bdk_device_t *device, bdk_netphy_t phy)
{
    /* Check if the PHY is 88e1514 PHY we expect */
    int phy_status = mdio_read(device, BDK_MDIO_PHY_REG_ID1);
    if (phy_status != 0x0141)
    {
        bdk_error("%s: Not a 88E1514 PHY\n", device->name);
        return -1;
    }
    phy_status = mdio_read(device, BDK_MDIO_PHY_REG_ID2);
    if ((phy_status & 0xfff0) != 0x0dd0)
    {
        bdk_error("%s: Not a 88E1514 PHY\n", device->name);
        return -1;
    }

    BDK_TRACE(DEVICE, "%s: Programming 88E1514 PHY\n",device->name);

    /* EEE initialization */
    mdio_write(device, 22, 0x00ff);
    mdio_write(device, 17, 0x214B);
    mdio_write(device, 16, 0x2144);
    mdio_write(device, 17, 0x0C28);
    mdio_write(device, 16, 0x2146);
    mdio_write(device, 17, 0xB233);
    mdio_write(device, 16, 0x214D);
    mdio_write(device, 17, 0xCC0C);
    mdio_write(device, 16, 0x2159);
    mdio_write(device, 22, 0x0000);

    /* SGMII-to-Copper mode initialization */
    /* Select page 18 */
    mdio_write(device, 22, 18);

    /* In reg 20, write MODE[2:0] = 0x1 (SGMII to Copper) */
    int status = mdio_read(device, 20);
    status &= -7; /* Clear Mode[2:0] */
    status |= 1; /* Mode[2:0} = SGMII */
    mdio_write(device, 20, status);

    /* PHY reset is necessary after changing MODE[2:0] */
    status |= 0x8000;
    mdio_write(device, 20, status);

    bdk_wait_usec(100);

    /* Reset page selection */
    mdio_write(device, 22, 0);

    return 0;
}

static int phy_loopback(bdk_device_t *device, bdk_netphy_t phy, bool host_side, bool line_side)
{
    /* MAC loopback, host side */
    if (host_side)
    {
        int reg = mdio_read(device, 0);
        reg = bdk_insert(reg, 1, 14, 1);
        mdio_write(device, 0, reg);
    }

    /* Far end loopback, line side */
    if (line_side)
    {
        mdio_write(device, 22, 2); /* Select page 2 */
        int reg = mdio_read(device, 21);
        reg = bdk_insert(reg, 1, 14, 1);
        mdio_write(device, 21, reg);
        mdio_write(device, 22, 0); /* Select page 0 */
    }
    return 0;
}

bdk_driver_t __bdk_driver_netphy_88e1514 = {
    .name = "PHY-88E1514",
    .api = BDK_DEVICE_API_NETPHY,
    .add = add,
    .funcs.netphy.init = phy_init,
    .funcs.netphy.loopback = phy_loopback,
    .funcs.netphy.get_speed = phy_get_speed,
};
