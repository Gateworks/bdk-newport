/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-hal/qlm/bdk-qlm-common.h"


/*
 * For SFF81xx board, query the GPIOs connected to DIP switches to determine the QLM setup.
 * The below table lists the DIP->QLM->GPIO mapping 
 * SW1.1 -> QLM0_SEL -> GPIO_26
 * SW1.2 -> QLM1_SEL -> GPIO_25
 * SW1.3 -> QLM2_SEL -> GPIO_31
 * SW1.4 -> QLM3_SEL -> GPIO_4
 * For V2.x boards 
 * SW3.7 -> XFI/QSGMII SEL ->GPIO_36
 * 
 * Notes:  
 *   For BGX, In cases where we have just one DLM lane used, It is recommended to use QLM 2x1 mode 
 *   (Ex: SGMII_2x1/XFI_2x1 instead of SGMII_1x1/XFI_1x1) and instead disable that 
 *   unused BGX ports. 
 *    
 *   On the SFF8104 board, the DLM1 lane1 is connected to XFI.
 *   So the configuration must be to
 *   1. Configure DLM1 as BDK_QLM_MODE_XFI
 *   2. Disable the BGX-ENABLE.N0.BGX0.P0
 */    

static void init_early(void)
{
    unsigned cfg[5] = {0};
    unsigned int qlm_config = 0;
    uint64_t gpio = 0;
    /* GPIO pins which are connected to DIP switches */
    int gpio_idx[5]={4, 31, 25, 26, 36};

    bdk_qlm_modes_t qlm_mode[4];
    int qlm_speed = 0;
    int use_ref = 0;
    bdk_qlm_mode_flags_t qlm_flags = 0;
    unsigned int node = 0, lane = 0;


    BDK_TRACE(INIT, "SFF8104: Called %s\n", __FUNCTION__);
    
    /* Configure the GPIOs to read the QLM settings */
    bdk_device_t *device = bdk_device_gpio_lookup(NULL, -1);
    for (int i = 0; i < 5; i++)
    {
        bdk_device_gpio_setup(device, gpio_idx[i], false, 0, false, false);
    }
    
    /* Read the GPIOs */
    gpio = bdk_device_gpio_readstate(device, 0);

    for (int i = 0; i < 5; i++ )
    {
        cfg[i] = !!(gpio & (1ULL<<gpio_idx[i]));
    }

    qlm_config = cfg[0] | cfg[1]<<1 | cfg[2]<<2 | cfg[3]<<3;

    switch(qlm_config)
    {
        case 0:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = BDK_QLM_MODE_DISABLED;
                qlm_mode[2] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[3] = BDK_QLM_MODE_PCIE_X2;
                break;
        case 1:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = BDK_QLM_MODE_DISABLED;
                qlm_mode[2] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[3] = BDK_QLM_MODE_SATA;
                break;

        case 2:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = BDK_QLM_MODE_DISABLED;
                qlm_mode[2] = BDK_QLM_MODE_XFI;
                qlm_mode[3] = BDK_QLM_MODE_PCIE_X2;
                break;
        case 3:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = BDK_QLM_MODE_DISABLED;
                qlm_mode[2] = BDK_QLM_MODE_XFI;
                qlm_mode[3] = BDK_QLM_MODE_SATA;
                break;
        case 4:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = cfg[4] ? BDK_QLM_MODE_XFI : BDK_QLM_MODE_QSGMII;
                qlm_mode[2] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[3] = BDK_QLM_MODE_PCIE_X2;
                break;
	case 5:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = cfg[4] ? BDK_QLM_MODE_XFI : BDK_QLM_MODE_QSGMII;
                qlm_mode[2] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[3] = BDK_QLM_MODE_SATA;
                break;
        case 6:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = cfg[4] ? BDK_QLM_MODE_XFI : BDK_QLM_MODE_QSGMII;
                qlm_mode[2] = BDK_QLM_MODE_XFI;
                qlm_mode[3] = BDK_QLM_MODE_PCIE_X2;
                break;
        case 7:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = cfg[4] ? BDK_QLM_MODE_XFI : BDK_QLM_MODE_QSGMII;
                qlm_mode[2] = BDK_QLM_MODE_XFI;
                qlm_mode[3] = BDK_QLM_MODE_SATA;
                break;
        case 8:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X4;
                qlm_mode[1] = BDK_QLM_MODE_PCIE_X4;
                qlm_mode[2] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[3] = BDK_QLM_MODE_PCIE_X2;
                break;
        case 9:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X4;
                qlm_mode[1] = BDK_QLM_MODE_PCIE_X4;
                qlm_mode[2] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[3] = BDK_QLM_MODE_SATA;
                break;
        case 10:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X4;
                qlm_mode[1] = BDK_QLM_MODE_PCIE_X4;
                qlm_mode[2] = BDK_QLM_MODE_XFI;
                qlm_mode[3] = BDK_QLM_MODE_PCIE_X2;
                break;
        case 11:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X4;
                qlm_mode[1] = BDK_QLM_MODE_PCIE_X4;
                qlm_mode[2] = BDK_QLM_MODE_XFI;
                qlm_mode[3] = BDK_QLM_MODE_SATA;
                break;
        case 12:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = cfg[4] ? BDK_QLM_MODE_XFI : BDK_QLM_MODE_QSGMII;
                qlm_mode[2] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[3] = BDK_QLM_MODE_PCIE_X2;
                break;
        case 13:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = cfg[4] ? BDK_QLM_MODE_XFI : BDK_QLM_MODE_QSGMII;
                qlm_mode[2] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[3] = BDK_QLM_MODE_SATA;
                break;
        case 14:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = cfg[4] ? BDK_QLM_MODE_XFI : BDK_QLM_MODE_QSGMII;
                qlm_mode[2] = BDK_QLM_MODE_XFI;
                qlm_mode[3] = BDK_QLM_MODE_PCIE_X2;
                break;
        case 15:
                qlm_mode[0] = BDK_QLM_MODE_PCIE_X2;
                qlm_mode[1] = cfg[4] ? BDK_QLM_MODE_XFI : BDK_QLM_MODE_QSGMII;
                qlm_mode[2] = BDK_QLM_MODE_XFI;
                qlm_mode[3] = BDK_QLM_MODE_SATA;
                break;
        default:
		bdk_fatal("Unsupported QLM configuration detected: %d\n", qlm_config);
                return;
        }

        for(int qlm = 0; qlm < 4; qlm++)
        {
            const char *qlm_mode_str = bdk_qlm_mode_tostring(qlm_mode[qlm]);

            switch(qlm_mode[qlm])
            {
            case  BDK_QLM_MODE_DISABLED:
                break;
            case BDK_QLM_MODE_XFI:
                use_ref = REF_156MHZ;
                qlm_speed = 10312;
                break;
            case BDK_QLM_MODE_SATA:
                qlm_speed = 6000;
                use_ref = REF_100MHZ;
                break;
            case BDK_QLM_MODE_PCIE_X2:
            case BDK_QLM_MODE_PCIE_X4:
                qlm_speed = 8000;
                use_ref =REF_100MHZ;
                break;
            case BDK_QLM_MODE_QSGMII:
                use_ref = REF_100MHZ;
                qlm_speed = 5000;
                break;
            default:
                bdk_fatal("Unsupported N%d.QLM%d mode: %s(%d)",
                          node, qlm,
                          qlm_mode_str ? qlm_mode_str : "???",
                          qlm_mode[qlm]);
                return;
            }

	/* If QLM1 is configured for XFI, then AQR107 is on QLM1 lane 1 
	   Set the PHY address correctly and disable other BGX ports */
	if ((1 == qlm) && (qlm_mode[qlm] == BDK_QLM_MODE_XFI))
	{
                 unsigned mdio_bus = 1;
                 unsigned mdio_addr = 0;
		 
                 int phy_cfg = 0xff<<24 | ((mdio_bus & 0xf)<<8) | (mdio_addr & 0xff);
                 bdk_config_set_int((uint32_t) phy_cfg,BDK_CONFIG_PHY_ADDRESS, node, 0, 1);

                for (int i = 0; i<4; i++) 
		{
                    if(i == 1)
                        continue;
                    bdk_config_set_int(-1,BDK_CONFIG_PHY_ADDRESS, node, 0, i);
                    bdk_config_set_int(0,BDK_CONFIG_BGX_ENABLE,node,0,i);
		 }
		
	}

            BDK_TRACE(INIT, "Setting N%d.QLM%d mode %s(%d), speed %d, lane %d, flags 0x%x\n",
                      node, qlm, qlm_mode_str, qlm_mode[qlm], qlm_speed, lane, qlm_flags);


            bdk_config_set_str(bdk_qlm_mode_to_cfg_str(qlm_mode[qlm]), BDK_CONFIG_QLM_MODE, node, qlm, lane); 
            bdk_config_set_int(qlm_speed, BDK_CONFIG_QLM_FREQ, node, qlm, 0);
	    /* DLMC_REF_CLK0 (0) = 156MHZ, DLMC_REF_CLK1 (1) = 100MHZ, DLM1_REF_CLK (2) = 156MHZ */
            bdk_config_set_int(((use_ref==REF_156MHZ)? 2: 1), BDK_CONFIG_QLM_CLK, node, qlm);
	   
	}
	return;
}

static void init_dram(void)
{
    BDK_TRACE(INIT, "SFF8104: Called %s\n", __FUNCTION__);
}

static void init_complete(void)
{
    BDK_TRACE(INIT, "SFF8104: Called %s\n", __FUNCTION__);
}

static const bdk_boot_callbacks_t sff8104 = {
    .board_name = "SFF8104",
    .init_early = init_early,
    .init_dram = init_dram,
    .init_complete = init_complete,
};

BDK_REGISTER_BOOT_CALLBACK(sff8104);
