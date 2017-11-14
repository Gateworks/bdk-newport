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
#include <malloc.h>
#include "libbdk-arch/bdk-csrs-rgx.h"
#include "libbdk-arch/bdk-csrs-xcv.h"

/* This file implements interfaces connected to the RGX block introduced
    for CN81XX */

#define MAX_MTU 9212

typedef struct
{
    int         port;           /* Which physical port this handle connects to */
    int         num_port;       /* Number of physical ports on this interface */
} rgx_priv_t;

/**
 * Create the private structure needed by RGX
 *
 * @param node      Node this RGX is on
 * @param interface Which RGX
 * @param index     Which channel on the RGX. This is an
 *                  encoding of port and channel.
 *
 * @return The private structure
 */
static void create_priv(bdk_node_t node, int interface, int index, rgx_priv_t *priv)
{
    memset(priv, 0, sizeof(*priv));
    priv->num_port = 1;
    priv->port = index;
}

static int if_num_interfaces(bdk_node_t node)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
        return 1;
    else
        return 0;
}

static int if_num_ports(bdk_node_t node, int interface)
{
    rgx_priv_t priv;
    create_priv(node, interface, 0, &priv);
    return priv.num_port;
}

/**
 * Perform initialization of the RGX required before use. This
 * should only be called once for each RGX. Before this is
 * called, the mode of the SERDES must be set by
 * bdk_qlm_set_mode().
 *
 * @param interface Which RGX to setup. This will have index=0
 *
 * @return Zero on success, negative on failure
 */
static int rgx_setup_one_time(bdk_if_handle_t handle)
{
    const rgx_priv_t *priv = (rgx_priv_t *)handle->priv;

    /* Set LMAC type as the hardware default is wrong */
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMRX_CONFIG(handle->interface, handle->index),
        c.s.lmac_type = 5);

    /* Strip FCS */
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMR_GLOBAL_CONFIG(handle->interface),
        c.s.fcs_strip = 1);

    /* First warn if BIST failed */
    uint64_t bist = BDK_CSR_READ(handle->node, BDK_RGXX_CMR_BIST_STATUS(handle->interface));
    if (bist)
        bdk_warn("RGX%d failed BIST\n", handle->interface);

    /* Set the PKND */
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMRX_RX_ID_MAP(handle->interface, handle->index),
        c.s.pknd = handle->pknd);

    /* Set the number of LMACs we will use */
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMR_TX_LMACS(handle->interface),
        c.s.lmacs = priv->num_port);
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMR_RX_LMACS(handle->interface),
        c.s.lmacs = priv->num_port);

    /* Set the backpressure AND mask. Each interface gets 16 channels in this
       mask. When there is only 1 port, all 64 channels are available but
       the upper channels are used for anything. That's why this code only uses
       16 channels per interface */
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMR_CHAN_MSK_AND(handle->interface),
        c.s.msk_and |= ((1ull <<1/*num_channels*/) - 1ull) << (handle->index * 16));

    /* Disable all MAC filtering */
    for (int i = 0; i < 32; i++)
        BDK_CSR_WRITE(handle->node, BDK_RGXX_CMR_RX_DMACX_CAM(handle->interface, i), 0);
    /* Disable MAC steering */
    for (int i = 0; i < 8; i++)
        BDK_CSR_WRITE(handle->node, BDK_RGXX_CMR_RX_STEERINGX(handle->interface, i), 0);

    return 0;
}

static int if_probe(bdk_if_handle_t handle)
{
    /* Don't show ports that have zero in RGXX_CMRX_RX_DMAC_CTL. These are
       not on the board and hidden by the bootstub */
    if (BDK_CSR_READ(handle->node, BDK_RGXX_CMRX_RX_DMAC_CTL(handle->interface, handle->index)) == 0)
        return -1;

    rgx_priv_t *priv = (rgx_priv_t *)handle->priv;
    create_priv(handle->node, handle->interface, handle->index, priv);

    /* Change name to be something that might be meaningful to the user */
    const char *name_format;
    if (bdk_numa_is_only_one())
    {
        name_format = "RGMII%d.%d";
        snprintf(handle->name, sizeof(handle->name), name_format, handle->interface, priv->port);
    }
    else
    {
        name_format = "N%d.RGMII%d.%d";
        snprintf(handle->name, sizeof(handle->name), name_format, handle->node, handle->interface, priv->port);
    }
    handle->name[sizeof(handle->name)-1] = 0;

    handle->flags |= BDK_IF_FLAGS_HAS_FCS;
    return 0;
}

static int get_phy_address(bdk_if_handle_t handle)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX))
        return bdk_config_get_int(BDK_CONFIG_PHY_ADDRESS, handle->node, handle->interface + 2, handle->index);
    else
        return -1;
}

static int sgmii_link(bdk_if_handle_t handle)
{
    const int rgx_block = handle->interface;
    const int rgx_index = handle->index;
    int phy_address = get_phy_address(handle);

    int forced_speed_mbps = 0;  /* Default to no forced speed, use autonegotiation */
    /* Check for special PHY address values that indicate a forced speed, and no MDIO
       connection to the PHY.  In these cases we will also force the RGMII speed, and not
       do RGMII autonegotiation. Only 1000/100 Mbits/second are supported.*/
    if (phy_address == 0x1000)
        forced_speed_mbps = 1000;
    else if (phy_address == 0x1001)
        forced_speed_mbps = 100;
    else if ((phy_address & BDK_IF_PHY_TYPE_MASK) == BDK_IF_PHY_TWSI)
        forced_speed_mbps = 1000;

    /* Take PCS through a reset sequence.
        PCS*_MR*_CONTROL_REG[PWR_DN] should be cleared to zero.
        Write PCS*_MR*_CONTROL_REG[RESET]=1 (while not changing the value of
            the other PCS*_MR*_CONTROL_REG bits).
        Read PCS*_MR*_CONTROL_REG[RESET] until it changes value to zero. */
    if (!bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_GMP_PCS_MRX_CONTROL(rgx_block, rgx_index),
            c.s.reset = 1);
        if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_RGXX_GMP_PCS_MRX_CONTROL(rgx_block, rgx_index), reset, ==, 0, 10000))
        {
            bdk_error("%s: Timeout waiting for reset finish\n", handle->name);
            return -1;
        }
    }

    if (!forced_speed_mbps)
    {
        /* Write PCS*_MR*_CONTROL_REG[RST_AN]=1 to ensure a fresh rgmii negotiation starts. */
        BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_GMP_PCS_MRX_CONTROL(rgx_block, rgx_index),
            c.s.rst_an = 1;
            c.s.an_en = 0;
            c.s.pwr_dn = 0);
    }
    else
    {
        /* A forced interface speed was selected, so configure this for the rGMII link as well,
           and don't do RGMII autonegotiation. */
        BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_GMP_PCS_MRX_CONTROL(rgx_block, rgx_index),
                       c.s.spdmsb = (forced_speed_mbps == 1000);
                       c.s.spdlsb = (forced_speed_mbps != 1000);
                       c.s.an_en = 0;
                       c.s.pwr_dn = 0);
    }

    /* Write PCS*_LINK*_TIMER_COUNT_REG[COUNT] with the appropriate
        value. RGMII specifies a 1.6ms interval, 10ms for everybody else. */
    BDK_CSR_INIT(pcs_miscx_ctl, handle->node, BDK_RGXX_GMP_PCS_MISCX_CTL(rgx_block, rgx_index));
    BDK_CSR_INIT(pcs_linkx_timer, handle->node, BDK_RGXX_GMP_PCS_LINKX_TIMER(rgx_block, rgx_index));
    const uint64_t clock_mhz = bdk_clock_get_rate(handle->node, BDK_CLOCK_SCLK) / 1000000;
    if (pcs_miscx_ctl.s.mode)
    {
        /* 1000BASE-X */
        pcs_linkx_timer.s.count = (10000ull * clock_mhz) >> 10;
    }
    else
    {
        /* RGMII */
        pcs_linkx_timer.s.count = (1600ull * clock_mhz) >> 10;
    }
    BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_PCS_LINKX_TIMER(rgx_block, rgx_index), pcs_linkx_timer.u);

    /* Write the advertisement register to be used as the
        tx_Config_Reg<D15:D0> of the autonegotiation.
        In 1000BASE-X mode, tx_Config_Reg<D15:D0> is PCS*_AN*_ADV_REG.
        In SGMII PHY mode, tx_Config_Reg<D15:D0> is PCS*_SGM*_AN_ADV_REG.
        In SGMII MAC mode, tx_Config_Reg<D15:D0> is the fixed value 0x4001, so
        this step can be skipped. */
    if (pcs_miscx_ctl.s.mode)
    {
        /* 1000BASE-X */
        BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_GMP_PCS_ANX_ADV(rgx_block, rgx_index),
            c.s.rem_flt = 0;
            c.s.pause = 3;
            c.s.hfd = 1;
            c.s.fd = 1);
    }
    else
    {
        int phy_address = get_phy_address(handle);
        if ((phy_address == -1) && !pcs_miscx_ctl.s.mac_phy)
        {
            bdk_warn("%s: Forcing PHY mode as PHY address is not set\n", handle->name);
            pcs_miscx_ctl.s.mac_phy = 1;
            BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_PCS_MISCX_CTL(rgx_block, rgx_index), pcs_miscx_ctl.u);
        }

        if (pcs_miscx_ctl.s.mac_phy)
        {
            /* PHY Mode */
            BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_GMP_PCS_SGMX_AN_ADV(rgx_block, rgx_index),
                c.s.dup = 1;
                c.s.speed= 2);
        }
        else
        {
            /* MAC Mode - Nothing to do */
        }
    }
    return 0;
}

/**
 * @INTERNAL
 * Configure an RGMII link to the specified speed after the
 * SERTES link is up.
 *
 * @param interface Interface to init
 * @param index     Index of prot on the interface
 * @param link_info Link state to configure
 *
 * @return Zero on success, negative on failure
 */
static int sgmii_speed(bdk_if_handle_t handle, bdk_if_link_t link_info)
{
    const int rgx_block = handle->interface;
    const int rgx_index = handle->index;
    int is_enabled;

    /* Disable GMX before we make any changes. Remember the enable state */
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMRX_CONFIG(rgx_block, rgx_index),
        is_enabled = c.s.data_pkt_tx_en;
        c.s.data_pkt_tx_en = 0;
        c.s.data_pkt_rx_en = 0);

    /* Wait for GMX to be idle */
    if (BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_RGXX_GMP_GMI_PRTX_CFG(rgx_block, rgx_index), rx_idle, ==, 1, 10000) ||
        BDK_CSR_WAIT_FOR_FIELD(handle->node, BDK_RGXX_GMP_GMI_PRTX_CFG(rgx_block, rgx_index), tx_idle, ==, 1, 10000))
    {
        bdk_error("%s: Timeout waiting for idle\n", handle->name);
        return -1;
    }

    /* Read GMX CFG again to make sure the disable completed */
    BDK_CSR_INIT(prtx_cfg, handle->node, BDK_RGXX_GMP_GMI_PRTX_CFG(rgx_block, rgx_index));

    /* Get the misc control for PCS. We will need to set the duplication amount */
    BDK_CSR_INIT(pcsx_miscx_ctl_reg, handle->node, BDK_RGXX_GMP_PCS_MISCX_CTL(rgx_block, rgx_index));

    /* Only change the duplex setting if the link is up */
    if (link_info.s.up)
        prtx_cfg.s.duplex = link_info.s.full_duplex;

    /* Do speed based setting for GMX */
    switch (link_info.s.speed)
    {
        case 10:
            prtx_cfg.s.speed = 0;
            prtx_cfg.s.speed_msb = 1;
            prtx_cfg.s.slottime = 0;
            pcsx_miscx_ctl_reg.s.samp_pt = 25; /* Setting from GMX-603 */
            BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_GMI_TXX_SLOT(rgx_block, rgx_index), 64);
            BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_GMI_TXX_BURST(rgx_block, rgx_index), 0);
            break;
        case 100:
            prtx_cfg.s.speed = 0;
            prtx_cfg.s.speed_msb = 0;
            prtx_cfg.s.slottime = 0;
            pcsx_miscx_ctl_reg.s.samp_pt = 0x5;
            BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_GMI_TXX_SLOT(rgx_block, rgx_index), 64);
            BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_GMI_TXX_BURST(rgx_block, rgx_index), 0);
            break;
        case 1000:
            prtx_cfg.s.speed = 1;
            prtx_cfg.s.speed_msb = 0;
            prtx_cfg.s.slottime = 1;
            pcsx_miscx_ctl_reg.s.samp_pt = 1;
            BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_GMI_TXX_SLOT(rgx_block, rgx_index), 512);
	    if (prtx_cfg.s.duplex)
                BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_GMI_TXX_BURST(rgx_block, rgx_index), 0); // full duplex
	    else
                BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_GMI_TXX_BURST(rgx_block, rgx_index), 8192); // half duplex
            break;
        default:
            break;
    }

    /* Write the new misc control for PCS */
    BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_PCS_MISCX_CTL(rgx_block, rgx_index), pcsx_miscx_ctl_reg.u);

    /* Write the new GMX settings with the port still disabled */
    BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_GMI_PRTX_CFG(rgx_block, rgx_index), prtx_cfg.u);

    /* Restore the enabled / disabled state */
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMRX_CONFIG(rgx_block, rgx_index),
        c.s.data_pkt_tx_en = is_enabled;
        c.s.data_pkt_rx_en = link_info.s.up && is_enabled);
    return 0;
}

/**
 * Setup RGMII for the given link speed
 *
 * @param handle
 * @param link_info
 *
 * @return
 */
static int rgmii_speed(bdk_if_handle_t handle, bdk_if_link_t link_info)
{
    int speed = 2;
    if (link_info.s.speed == 100)
        speed = 1;
    else if (link_info.s.speed == 10)
        speed = 0;

    BDK_CSR_INIT(xcv_reset, handle->node, BDK_XCVX_RESET(handle->interface));
    BDK_CSR_INIT(xcv_ctl, handle->node, BDK_XCVX_CTL(handle->interface));
    int up = link_info.s.up;
    int do_credits = up && !xcv_reset.s.enable;
    if (up && (!xcv_reset.s.enable || (xcv_ctl.s.speed != speed)))
    {
        /* From the 73xx XCV wiki:
           http://mawiki.caveonetworks.com/wiki/73xx/XCV#Reset_and_Initiailization */

        /* enable the XCV block */
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_RESET(handle->interface),
            c.s.enable = 1);

        /* set operating mode */
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_CTL(handle->interface),
            c.s.speed = speed);

        /* configure DLL - enable or bypass */
        // TX no bypass, RX bypass
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_DLL_CTL(handle->interface),
            c.s.clkrx_set  = 0;
            c.s.clkrx_byp  = 1;
            c.s.clktx_byp  = 0);

        /* enable */
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_DLL_CTL(handle->interface),
            c.s.refclk_sel = 0);
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_RESET(handle->interface),
            c.s.dllrst = 0);
        /* Delay seems to be need so XCV_DLL_CTL[CLK_SET] works */
        bdk_wait_usec(10);

        /* configure compensation controller - enable or bypass */
        // no bypass
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_COMP_CTL(handle->interface),
            //c.s.drv_pctl = 0;
            //c.s.drv_nctl = 0;
            c.s.drv_byp = 0);

        /* enable */
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_RESET(handle->interface),
            c.s.comp = 1);

        /* setup the RXC. CLKRST must be zero for internal loopback, one otherwise */
        BDK_CSR_INIT(xcv_ctl, handle->node, BDK_XCVX_CTL(handle->interface));
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_RESET(handle->interface),
            c.s.clkrst = !xcv_ctl.s.lpbk_int);
        /* set refclk_sel=1 if external loopback */
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_DLL_CTL(handle->interface),
            c.s.refclk_sel = xcv_ctl.s.lpbk_ext);

        /* datapaths come out of reset
            - The datapath resets will disengage BGX from the RGMII interface.
            - XCV will continue to return TX credits for each tick that is
                sent on the TX data path */
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_RESET(handle->interface),
            c.s.tx_dat_rst_n = 1;
            c.s.rx_dat_rst_n = 1);
    }

    /* enable the packet flow
        - The packet resets will be only disengage on packet boundaries
        - XCV will continue to return TX credits for each tick that is
            sent on the TX datapath */
    BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_RESET(handle->interface),
        c.s.tx_pkt_rst_n = up;
        c.s.rx_pkt_rst_n = up);

    /* Full reset when link is down */
    if (!up)
    {
        /* wait 2*MTU in time */
        bdk_wait_usec(10000);
        /* reset the world */
        BDK_CSR_WRITE(handle->node, BDK_XCVX_RESET(handle->interface), 0);
    }
    /* grant PKO TX credits */
    if (do_credits)
        BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_BATCH_CRD_RET(handle->interface),
            c.s.crd_ret = 1);
    return 0;
}

static int if_init(bdk_if_handle_t handle)
{
    const int rgx_block = handle->interface;
    const int rgx_index = handle->index;
    if (rgx_setup_one_time(handle))
        return -1;

    /* Configure to allow max sized frames */
    const int buffer_size = bdk_config_get_int(BDK_CONFIG_PACKET_BUFFER_SIZE);
    int max_size = buffer_size * 12; /* 12 is from nic_cqe_rx_s */
    BDK_CSR_WRITE(handle->node, BDK_RGXX_GMP_GMI_RXX_JABBER(rgx_block, rgx_index), max_size);

    /* Disable frame alignment if using preamble. This allows the link to
        reach full rate for odd length packets. For example, without this
        SGMII is slower than RGMII for 65 byte packets */
    BDK_CSR_INIT(txx_append, handle->node, BDK_RGXX_GMP_GMI_TXX_APPEND(rgx_block, rgx_index));
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_GMP_GMI_TXX_SGMII_CTL(rgx_block, rgx_index),
        c.s.align = !txx_append.s.preamble);

    int bytes_per_port;
    BDK_CSR_INIT(rgxx_const, handle->node, BDK_RGXX_CONST(handle->interface));
    bytes_per_port = rgxx_const.s.tx_fifosz;
    if (bytes_per_port == 0)
        bytes_per_port = 0x3000;
    if (bdk_nic_port_init(handle, BDK_NIC_TYPE_RGMII, bytes_per_port))
        return -1;

    return 0;
}

static int if_enable(bdk_if_handle_t handle)
{
    const rgx_priv_t *priv = (rgx_priv_t *)handle->priv;
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMRX_CONFIG(handle->interface, priv->port),
        c.s.enable = 1;
        c.s.data_pkt_tx_en = 1;
        c.s.data_pkt_rx_en = 1);
    return 0;
}

static int if_disable(bdk_if_handle_t handle)
{
    const rgx_priv_t *priv = (rgx_priv_t *)handle->priv;
    BDK_CSR_MODIFY(c, handle->node, BDK_RGXX_CMRX_CONFIG(handle->interface, priv->port),
        c.s.enable = 0;
        c.s.data_pkt_tx_en = 0;
        c.s.data_pkt_rx_en = 0);
    return 0;
}

/**
 * Get RGMII link speed
 *
 * @param handle
 *
 * @return
 */
static bdk_if_link_t if_link_get_rgmii(bdk_if_handle_t handle)
{
    BDK_CSR_INIT(xcv_ctl, handle->node, BDK_XCVX_CTL(handle->interface));
    if (xcv_ctl.s.lpbk_int)
    {
        bdk_if_link_t result;
        result.u64 = 0;
        result.s.full_duplex = 1;
        result.s.lanes = 1;
        result.s.speed = 1000;
        result.s.up = 1;
        return result;
    }
    int rgmii_phy = get_phy_address(handle);
    if (rgmii_phy == -1)
    {
        /* Use RGMII inband status */
        BDK_CSR_INIT(inbnd, handle->node, BDK_XCVX_INBND_STATUS(handle->interface));
        bdk_if_link_t result;
        result.u64 = 0;
        if (inbnd.s.link)
        {
            result.s.full_duplex = inbnd.s.duplex;
            result.s.lanes = 1;
            result.s.up = 1;
            switch (inbnd.s.speed)
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
                default: /* Invalid, force down */
                    result.u64 = 0;
                    break;
            }
        }
        return result;
    }
    else
        return __bdk_if_phy_get(handle->node, rgmii_phy);
}

/**
 * Get RGMII link speed
 *
 * @param handle
 *
 * @return
 */
static bdk_if_link_t if_link_get(bdk_if_handle_t handle)
{
    const int rgx_block = handle->interface;
    const int rgx_index = handle->index;
    bdk_if_link_t result;

    result.u64 = 0;
    int speed = 1000;

    if (bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        /* The simulator gives you a simulated 1Gbps full duplex link */
        result.s.up = 1;
        result.s.full_duplex = 1;
        result.s.speed = speed;
        return result;
    }

    BDK_CSR_INIT(xcv_ctl, handle->node, BDK_XCVX_CTL(handle->interface));
    if (xcv_ctl.s.lpbk_int)
    {
        /* Force 1Gbps full duplex link for internal loopback */
        result.s.up = 1;
        result.s.full_duplex = 1;
        result.s.speed = speed;
        return result;
    }


    BDK_CSR_INIT(gmp_pcs_miscx_ctl, handle->node, BDK_RGXX_GMP_PCS_MISCX_CTL(rgx_block, rgx_index));
    if (gmp_pcs_miscx_ctl.s.mode)
    {
        /* FIXME: 1000BASE-X */
    }
    else
    {
        if (gmp_pcs_miscx_ctl.s.mac_phy)
        {
            /* PHY Mode */
            /* Don't bother continuing if the SERTES low level link is down */
            BDK_CSR_INIT(gmp_pcs_mrx_status, handle->node, BDK_RGXX_GMP_PCS_MRX_STATUS(rgx_block, rgx_index));
            if (bdk_unlikely(gmp_pcs_mrx_status.s.lnk_st == 0))
            {
                /* Read a second time as the lnk_st bit is sticky */
                gmp_pcs_mrx_status.u = BDK_CSR_READ(handle->node, BDK_RGXX_GMP_PCS_MRX_STATUS(rgx_block, rgx_index));
                if (bdk_unlikely(gmp_pcs_mrx_status.s.lnk_st == 0))
                {
                    if (sgmii_link(handle) != 0)
                        return result;
                }
            }

            /* Read the autoneg results */
            BDK_CSR_INIT(gmp_pcs_anx_results, handle->node, BDK_RGXX_GMP_PCS_ANX_RESULTS(rgx_block, rgx_index));
            if (gmp_pcs_anx_results.s.an_cpt)
            {
                /* Auto negotiation is complete. Set status accordingly */
                result.s.full_duplex = gmp_pcs_anx_results.s.dup;
                result.s.up = gmp_pcs_anx_results.s.link_ok;
                switch (gmp_pcs_anx_results.s.spd)
                {
                    case 0:
                        result.s.speed = speed / 100;
                        break;
                    case 1:
                        result.s.speed = speed / 10;
                        break;
                    case 2:
                        result.s.speed = speed;
                        break;
                    default:
                        result.s.speed = 0;
                        result.s.up = 0;
                        break;
                }
            }
            else
            {
                /* Auto negotiation isn't complete. Return link down */
                result.s.speed = 0;
                result.s.up = 0;
            }
        }
        else /* MAC Mode */
        {
            int phy_address = get_phy_address(handle);
            result = __bdk_if_phy_get(handle->node, phy_address);
        }
    }
    return result;
}

static void if_link_set(bdk_if_handle_t handle, bdk_if_link_t link_info)
{
    int status = sgmii_link(handle);
    if (status == 0)
    {
        sgmii_speed(handle, link_info);
        rgmii_speed(handle, link_info);
    }
}

/**
 * Setup loopback
 *
 * @param handle
 * @param loopback
 *
 * @return
 */
static int if_loopback(bdk_if_handle_t handle, bdk_if_loopback_t loopback)
{
    if ((loopback & BDK_IF_LOOPBACK_INTERNAL) &&
        (loopback & BDK_IF_LOOPBACK_EXTERNAL))
    {
        bdk_error("Can't set internal and external loopback at the same time on RGMII port\n");
        return 0;
    }
    /* Set the loopback requested, reset the XCV to complete the initialization
       into the new mode.
       Reset per http://mawiki.caveonetworks.com/wiki/73xx/XCV#Reset_and_Initiailization */
    BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_RESET(handle->interface),
                   c.s.tx_pkt_rst_n = 0;
                   c.s.rx_pkt_rst_n = 0);
    /* wait 2*MTU in time */
    bdk_wait_usec(10000);
    BDK_CSR_MODIFY(c, handle->node, BDK_XCVX_CTL(handle->interface),
        c.s.lpbk_int = !!(loopback & BDK_IF_LOOPBACK_INTERNAL);
        c.s.lpbk_ext = !!(loopback & BDK_IF_LOOPBACK_EXTERNAL));
    /* reset the world */
    BDK_CSR_WRITE(handle->node, BDK_XCVX_RESET(handle->interface), 0);
    sgmii_link(handle);
    sgmii_speed(handle, if_link_get_rgmii(handle));
    rgmii_speed(handle, if_link_get_rgmii(handle));
    return 0;
}

/**
 * Get the interface RX and TX counters.
 *
 * @param handle Handle of port
 *
 * @return Statistics
 */
static const bdk_if_stats_t *if_get_stats(bdk_if_handle_t handle)
{
    bdk_nic_fill_rx_stats(handle);
    bdk_nic_fill_tx_stats(handle);
    return &handle->stats;
}

const __bdk_if_ops_t __bdk_if_ops_rgx = {
    .priv_size = sizeof(rgx_priv_t),
    .if_num_interfaces = if_num_interfaces,
    .if_num_ports = if_num_ports,
    .if_probe = if_probe,
    .if_init = if_init,
    .if_enable = if_enable,
    .if_disable = if_disable,
    .if_link_get = if_link_get,
    .if_link_set = if_link_set,
    .if_transmit = bdk_nic_transmit,
    .if_loopback = if_loopback,
    .if_get_queue_depth = bdk_nic_get_queue_depth,
    .if_get_stats = if_get_stats,
};

