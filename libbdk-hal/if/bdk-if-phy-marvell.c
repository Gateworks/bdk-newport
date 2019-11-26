/***********************license start***********************************
 * * Copyright (C) 2018 Marvell International Ltd.
 * * SPDX-License-Identifier: BSD-3-Clause
 * * https://spdx.org/licenses
 * ***********************license end**************************************/

#include <bdk.h>

static bool LOOP_INTERNAL = false;
static bool LOOP_EXTERNAL = false;


/**
 * Setup marvell PHYs
 * This function sets up one port in a marvell 88E1512 in SGMII mode
 */
static void setup_marvell_phy(bdk_node_t node, int mdio_bus, int mdio_addr)
{

 int phy_status = 0;
 
	   BDK_TRACE(DEVICE, "%s In SGMII mode for Marvell PHY 88E1512\n", __FUNCTION__);
	  /* Switch to Page 18 */
  	  phy_status = bdk_mdio_write(node, mdio_bus, mdio_addr, 22, 18);
          if (phy_status < 0)
               	return;
			
	  phy_status = bdk_mdio_read(node, mdio_bus, mdio_addr, 22);
          if (phy_status < 0)
               	return;
		    
	  /* Change the Phy System mode from RGMII(default hw reset mode) to SGMII */
          phy_status = bdk_mdio_write(node, mdio_bus, mdio_addr, 20, 1);
          if (phy_status < 0)
        	return;
	    
	  /* Requires a Software reset */
	  phy_status = bdk_mdio_write(node, mdio_bus, mdio_addr, 20, 0x8001);
          if (phy_status < 0)
        	return;

	  phy_status = bdk_mdio_read(node, mdio_bus, mdio_addr, 20);
          if (phy_status < 0)
               	return;
		    
	  /* Change the Page back to 0 */
  	  phy_status = bdk_mdio_write(node, mdio_bus, mdio_addr, 22, 0);
          if (phy_status < 0)
               	return;
			
	  phy_status = bdk_mdio_read(node, mdio_bus, mdio_addr, 22);
          if (phy_status < 0)
               	return;
      
      phy_status = bdk_mdio_read(node, mdio_bus, mdio_addr, 17);
      if (phy_status < 0)
           return;
}


void bdk_if_phy_marvell_setup(bdk_node_t node, int qlm, int mdio_bus, int phy_addr)
{

    BDK_TRACE(DEVICE,"In %s\n",__FUNCTION__);

    /* Check that the GSER mode is SGMII */
    /* Switch the marvell PHY to the correct mode */
    bdk_qlm_modes_t qlm_mode = bdk_qlm_get_mode(node, qlm, 0);
    
    BDK_TRACE(DEVICE,"%s: QLM:%d QLM_MODE:%d\n",__FUNCTION__, qlm, qlm_mode);
    
    if (qlm_mode != BDK_QLM_MODE_SGMII)
	return;

    BDK_TRACE(DEVICE,"%s: Detected Marvell Phy in SGMII mode\n", __FUNCTION__);    
    for (int port = 0; port < 2; port++)
    {
        setup_marvell_phy(node, mdio_bus, phy_addr + port);
    }
    return;

}
