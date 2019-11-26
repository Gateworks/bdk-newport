/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdAPI.h"
#include "mtdFwDownload.h"
#include "mtdInitialization.h"
#include "mtdDiagnostics.h"
#include "mtdCunit.h"
#include "mtdHunit.h"
#include "mtdHXunit.h"
#include "mtdXunit.h"
#include "mtdApiRegs.h"
#include "mtdIntr.h"
#include "Hwfw_88X33x0.h"

BDK_REQUIRE_DEFINE(DRIVER_NETPHY_88X3310P);
BDK_REQUIRE_DEFINE(DRIVER_NETPHY_88X3340P);

#define UNUSED(x) ((void) x)
/*at this level, 0 is success, negative is fail*/
#define TRY(func) {if((func) != MTD_OK) \
                            {bdk_error("FAILED at %s:%u\n",__FUNCTION__,__LINE__); \
                            return -1;}}


typedef struct _mdio_info
{
    int bus_id;
    int bus_port;
    int node;
} mdio_info;

typedef struct 
{
    bdk_device_t * p_device;
    MTD_DEV mv_phy;
    mdio_info bus_info;
    MTD_BOOL x_hostside; //x unit is used as host if
    bdk_if_link_t phy_status;
} phy_priv_t;

typedef struct
{
    mdio_info bus_info;
    void * prev;
} port_3340p;

static port_3340p * exist_3340p_ports = NULL;

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    device->priv.phy.smi = bdk_driver_extract_int(config_str, "smi", 0, 2);
    device->priv.phy.address = bdk_driver_extract_int(config_str, "addr", 0, 31);
    int qlm = bdk_driver_extract_int(config_str, "qlm", 0, bdk_qlm_get_num(device->node) - 1);
    int qlm_lane = bdk_driver_extract_int(config_str, "qlm_lane", 0, bdk_qlm_get_lanes(device->node, qlm));
    BDK_TRACE(DEVICE, "%s: 88X3310P PHY on SMI=%d, ADDR=%d QLM=%d, QLM_LANE=%d\n",
        device->name, device->priv.phy.smi, device->priv.phy.address, qlm, qlm_lane);

    bdk_netphy_register(device, 0, device->node, qlm, qlm_lane);
}

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add_3340p(bdk_device_t *device, const char *config_str)
{
    device->priv.phy.smi = bdk_driver_extract_int(config_str, "smi", 0, 2);
    device->priv.phy.address = bdk_driver_extract_int(config_str, "addr", 0, 31);
    int qlm = bdk_driver_extract_int(config_str, "qlm", 0, bdk_qlm_get_num(device->node) - 1);
    int qlm_lane = bdk_driver_extract_int(config_str, "qlm_lane", 0, bdk_qlm_get_lanes(device->node, qlm));
    BDK_TRACE(DEVICE, "%s: 88X3340P PHY on SMI=%d, ADDR=%d QLM=%d, QLM_LANE=%d\n",
        device->name, device->priv.phy.smi, device->priv.phy.address, qlm, qlm_lane);

    bdk_netphy_register(device, 0, device->node, qlm, qlm_lane);

    port_3340p * this_port = calloc(1,sizeof(port_3340p));
    this_port->bus_info.bus_id = device->priv.phy.smi;
    this_port->bus_info.bus_port = device->priv.phy.address;
    this_port->bus_info.node = device->node;
    this_port->prev = (void *)exist_3340p_ports;
    exist_3340p_ports = this_port;
}


static MTD_STATUS _mv_read_mdio(const MTD_DEV_PTR devPtr, MTD_U16 port, MTD_U16 mmd, MTD_U16 reg, MTD_U16 * p_data)
{
    mdio_info * p_bus_info = (mdio_info *)devPtr->appData;
    int data;

    data = bdk_mdio_45_read(p_bus_info->node, p_bus_info->bus_id, p_bus_info->bus_port+port, mmd, reg);
    if (data == -1)
    {
        *p_data = 0;
        return MTD_FAIL;
    }
    else
    {
        *p_data = data;
        return MTD_OK;
    }
}

static MTD_STATUS _mv_write_mdio(MTD_DEV_PTR devPtr, MTD_U16 port, MTD_U16 mmd, MTD_U16 reg, MTD_U16 data)
{
    mdio_info * p_bus_info = (mdio_info *)devPtr->appData;

    if (bdk_mdio_45_write(p_bus_info->node, p_bus_info->bus_id, p_bus_info->bus_port+port, mmd, reg, data) == -1) 
    {
        return MTD_FAIL;
    }
    else
    {
        return MTD_OK;
    }
}


static int _init_dev(phy_priv_t * phy_priv)
{
    MTD_DEV_PTR devPtr = &phy_priv->mv_phy;
    mdio_info *p_bus_info = &phy_priv->bus_info;
    MTD_STATUS status = MTD_FAIL;
    MTD_BOOL macsecIndirectAccess; 

    /* if readMdio and writeMdio function pointers are NULL, the mtdHwXmdioRead  
       and mtdHwXmdioWrite in mtdHwCntl.c must handle the MDIO read/write */
    FMTD_READ_MDIO readMdio = _mv_read_mdio;   /* pointer to host's function to do MDIO read */  
    FMTD_WRITE_MDIO writeMdio = _mv_write_mdio; /* pointer to host's function to do MDIO write */  

    /* Semaphore is work-in-progress. Set all 4 semaphore pointers to NULL */
    FMTD_SEM_CREATE semCreate = NULL;     
    FMTD_SEM_DELETE semDelete = NULL;    
    FMTD_SEM_TAKE semTake = NULL;     
    FMTD_SEM_GIVE semGive = NULL;     

    MTD_U16 anyPort = 0; /* port address of any MDIO port for this device */

    devPtr->appData = (void*)p_bus_info;

    /* For Macsec/PTP, pass macsecIndirectAccess as MTD_TRUE for all 88X32X0 devices */
    /* MTD_TRUE - to access MACSec through T-unit processor
       MTD_FALSE - to do direct register access */
    macsecIndirectAccess = MTD_FALSE;

    if (!devPtr || !devPtr->appData) 
    {
        bdk_error("%s: handle or devPtr or appData is NULL\n",__FUNCTION__);
        return MTD_FAIL;
    }

    devPtr->devEnabled = MTD_FALSE; /* will be set to MTD_TRUE by mtdLoadDriver() if successful */

    status = mtdLoadDriver(readMdio, writeMdio, macsecIndirectAccess, semCreate, 
                           semDelete, semTake, semGive, anyPort, devPtr);

    return status;
}

static int _load_ram_img(MTD_DEV_PTR mv_phy, int is_multi_port)
{
    MTD_U16 error_code;
    char * chip_type = NULL;
    MTD_U8 major;
    MTD_U8 minor;
    MTD_U8 inc;
    MTD_U8 test;
    MTD_STATUS status = MTD_FAIL;

  
    if(is_multi_port)
        chip_type = "88X3340p";
    else
        chip_type = "88X3310p";
 
    printf("Load firmware for Marvell PHY %s\n", chip_type);

    if (is_multi_port == 0)
    {
        status = mtdUpdateRamImage(mv_phy, 0, _33x0_fw, FW_SIZE, &error_code);
    }
    else
    {
        MTD_U16 ports[4]={0,1,2,3};
        MTD_U16 error_ports[4]={0};
        status=mtdParallelUpdateRamImage(mv_phy, ports, _33x0_fw, FW_SIZE, 4, error_ports, &error_code);
    }

    if (status == MTD_OK) {
        /* if the mtdUpdateRamImage() is successful, calls the mtdGetFirmwareVersion()
           to check and verify the updated version number */
            mtdWait(mv_phy, 1000);
            mtdGetFirmwareVersion(mv_phy, 0, &major, &minor, &inc, &test);
            BDK_TRACE(DEVICE,"RAM image of %s loaded successful\n", chip_type);
            BDK_TRACE(DEVICE,"Firmware version: %d.%d.%d.%d\n", major, minor, inc, test);
    }
    else
        bdk_error("FAIL when loading RAM image of %s, error code: %d \n", chip_type, error_code);
    
    return status; 

}

static MTD_STATUS _set_led(MTD_DEV_PTR mv_phy)
{
    _mv_write_mdio(mv_phy, 0, 31, 0xf020, 0x0050);
    _mv_write_mdio(mv_phy, 0, 31, 0xf021, 0x00b0);
    _mv_write_mdio(mv_phy, 0, 31, 0xf022, 0x0128);
    _mv_write_mdio(mv_phy, 0, 31, 0xf023, 0x0131);
    return MTD_OK;
}


/**
 * Network Port API function to initialize a port
 *
 * @param device Device to access
 * @param phy    PHY handle
 *
 * @return Zero on success, negative on failure
 */
static int phy_init(bdk_device_t *device, bdk_netphy_t phy)
{
    if (device->priv.phy.priv == NULL)
    {
        printf("%s: initializing 88X3310P ...\n", device->name);
        phy_priv_t *priv = calloc(1, sizeof(phy_priv_t));
        priv->p_device = device;
        priv->bus_info.bus_id = device->priv.phy.smi;
        priv->bus_info.bus_port = device->priv.phy.address;
        priv->bus_info.node = device->node;
        priv->x_hostside = MTD_FALSE;
        priv->phy_status.u64 = 0;
        device->priv.phy.priv = (void *)priv;

        TRY(_init_dev(priv));

        MTD_BOOL wait_for_fw = MTD_FALSE;
        TRY(mtdIsPhyInMdioDownloadMode(&priv->mv_phy,0,&wait_for_fw));
        if(wait_for_fw == MTD_TRUE)
        {
           //  mtdChipHardwareReset(&priv->mv_phy,0);
           //  mtdWait(&priv->mv_phy, 2000);
            TRY(_load_ram_img(&priv->mv_phy, 0));
        }
        else
        {
            MTD_U8 major;
            MTD_U8 minor;
            MTD_U8 inc;
            MTD_U8 test;
            MTD_BOOL update_fw = MTD_FALSE;
            mtdGetFirmwareVersion(&priv->mv_phy, 0, &major, &minor, &inc, &test);
            update_fw = V_MAJ>major ? MTD_TRUE : V_MIN>minor ? MTD_TRUE : V_INC>inc ? MTD_TRUE : MTD_FALSE;
            if (update_fw == MTD_TRUE)
            {
               TRY(_load_ram_img(&priv->mv_phy, 0));
            }
        }
        TRY(_set_led(&priv->mv_phy));
    }
    return 0;
}

/**
 * Network Port API function to initialize a port
 *
 * @param device Device to access
 * @param phy    PHY handle
 *
 * @return Zero on success, negative on failure
 */
static int phy_init_3340p(bdk_device_t *device, bdk_netphy_t phy)
{
    if (device->priv.phy.priv == NULL)
    {
        printf("%s: initializing a port of 88X3340P ...\n", device->name);
        phy_priv_t *priv = calloc(1, sizeof(phy_priv_t));
        priv->p_device = device;
        priv->bus_info.bus_id = device->priv.phy.smi;
        priv->bus_info.bus_port = device->priv.phy.address;
        priv->bus_info.node = device->node;
        priv->x_hostside = MTD_FALSE;
        priv->phy_status.u64 = 0;
        device->priv.phy.priv = (void *)priv;

        TRY(_init_dev(priv));

        MTD_BOOL new_chip = MTD_TRUE;
        if (exist_3340p_ports->prev == NULL)
        {
            new_chip = MTD_TRUE;
        }
        else
        {
            port_3340p * port = (port_3340p *)exist_3340p_ports->prev;
            while (port != NULL)
            {
                if (exist_3340p_ports->bus_info.node == port->bus_info.node
                    && exist_3340p_ports->bus_info.bus_id == port->bus_info.bus_id
                    && exist_3340p_ports->bus_info.bus_port >> 2 == port->bus_info.bus_port >> 2)
                {
                    new_chip = MTD_FALSE;
                    break;
                }
                port=(port_3340p *)port->prev;
                
            }
        }
        if (new_chip == MTD_TRUE)
        {
            MTD_BOOL wait_for_fw = MTD_FALSE;
            TRY(mtdIsPhyInMdioDownloadMode(&priv->mv_phy,0,&wait_for_fw));
            if(wait_for_fw == MTD_TRUE)
            {
              //  mtdChipHardwareReset(&priv->mv_phy,0);
              //  mtdWait(&priv->mv_phy, 2000);
                TRY(_load_ram_img(&priv->mv_phy, 1));
            }
            else
            {
                MTD_U8 major;
                MTD_U8 minor;
                MTD_U8 inc;
                MTD_U8 test;
                MTD_BOOL update_fw = MTD_FALSE;

                mtdGetFirmwareVersion(&priv->mv_phy, 0, &major, &minor, &inc, &test);
                update_fw = V_MAJ>major ? MTD_TRUE : V_MIN>minor ? MTD_TRUE : V_INC>inc ? MTD_TRUE : MTD_FALSE;
                if (update_fw == MTD_TRUE)
                {
                    TRY(_load_ram_img(&priv->mv_phy, 1));
                }
                
            }
        }
        TRY(_set_led(&priv->mv_phy));
    }
    return 0;
}

static MTD_STATUS _enable_rate_match(MTD_DEV_PTR mv_phy)
{
    MTD_U16 regValue = 0;

    mtdHwXmdioRead(mv_phy, 0, MTD_CUNIT_MODE_CONFIG, &regValue);
    mtdHwSetRegFieldToWord(regValue,0x3,12,2,&regValue);
    mtdHwXmdioWrite(mv_phy,0,MTD_CUNIT_MODE_CONFIG,regValue);
    //_mv_write_mdio(&phy_priv->mv_phy, 0, 31, 0xf000, 0x30ca);
    _mv_write_mdio(mv_phy, 0, 31, 0x8c04, 0x1c00);
    _mv_write_mdio(mv_phy, 0, 31, 0x8c05, 0x0000);
    _mv_write_mdio(mv_phy, 0, 31, 0x8c00, 0x1383);

    _mv_write_mdio(mv_phy, 0, 31, 0x8c02, 0x1fff);
    _mv_write_mdio(mv_phy, 0, 31, 0x8c03, 0x0000);

    _mv_write_mdio(mv_phy, 0, 31, 0x8e02, 0x1fff);
    _mv_write_mdio(mv_phy, 0, 31, 0x8e03, 0x0000);

    _mv_write_mdio(mv_phy, 0, 31, 0x8c01, 0x0000);
    _mv_write_mdio(mv_phy, 0, 31, 0x8000, 0x0f3f);
    _mv_write_mdio(mv_phy, 0, 31, 0x8001, 0x7dd0);
    _mv_write_mdio(mv_phy, 0, 31, 0x800e, 0x1b0a);
    _mv_write_mdio(mv_phy, 0, 31, 0x800f, 0x0000);
    _mv_write_mdio(mv_phy, 0, 31, 0x80a2, 0x0001);
    _mv_write_mdio(mv_phy, 0, 31, 0x80a3, 0x0000);
    return MTD_OK;
}

static MTD_STATUS _set_fiber_speed(MTD_DEV_PTR mv_phy, MTD_UINT speed)
{
    MTD_U16 regValue = 0;

    TRY(mtdHwXmdioRead(mv_phy, 0, MTD_CUNIT_PORT_CTRL, &regValue));
    TRY(mtdHwSetRegFieldToWord(regValue,speed,3,3,&regValue));
    TRY(mtdHwXmdioWrite(mv_phy,0,MTD_CUNIT_PORT_CTRL,regValue));
    TRY(mtdCunitSwReset(mv_phy, 0));
    return MTD_OK;
}


/**
 * Setup PHY auto-neg settings
 *
 * @param device     Device to access
 * @param phy        PHY handle
 * @param num_modes  Number of QLM modes/speeds in the following arrays
 * @param qlm_modes  Array of QLM modes to support
 * @param qlm_speeds Array of QLM speeds to support
 *
 * @return Zero on success, negative on failure
 */
static int phy_setup_an(bdk_device_t *device, bdk_netphy_t phy, int num_modes, bdk_qlm_modes_t qlm_modes[], int qlm_speeds[], bdk_netphy_flags_t flags)
{
    phy_priv_t *priv = device->priv.phy.priv;
    MTD_U16 allowed_speed_c = 0; //speed of copper port
    MTD_U16 allowed_speed_x = 0; //speed of fiber port when used as line side
    MTD_BOOL is_x_hostside = MTD_FALSE; // fiber port is used as host side
    MTD_BOOL an_on = MTD_FALSE;
    MTD_BOOL rate_match_on = MTD_FALSE;
    MTD_U16 media_sel = MTD_MS_CU_ONLY;
#if 1
    if (num_modes != 1)
    {
        bdk_error("%s: 88x5123 PHy driver doesn't support AN yet\n", device->name);
        return -1;
    }

    switch (qlm_speeds[0])
    {
    case 10312:
        if ((qlm_modes[0] == BDK_QLM_MODE_XFI)
            || (qlm_modes[0] == BDK_QLM_MODE_USXGMII_1X1))
        {
            allowed_speed_c = MTD_SPEED_ALL_33X0;
            allowed_speed_x = MTD_FT_10GBASER;
            an_on = MTD_TRUE;
            rate_match_on = MTD_TRUE;
            is_x_hostside = MTD_FALSE;
        }
        else if (qlm_modes[0] == BDK_QLM_MODE_10G_KR)
        {
            allowed_speed_c = MTD_SPEED_ALL_33X0;
            allowed_speed_x = MTD_FT_10GBASER;
            an_on = MTD_TRUE;
            rate_match_on = MTD_TRUE;
            is_x_hostside = MTD_FALSE;
        }
        else
        {
            bdk_error("%s: 88x3310 doesn't support current host mode\n", device->name);
            return -1;
        }
        break;
    case 6250: //need test
        if (qlm_modes[0] == BDK_QLM_MODE_RXAUI)
        {
            allowed_speed_c = MTD_SPEED_ALL_33X0;
            an_on = MTD_TRUE;
            rate_match_on = MTD_TRUE;
            is_x_hostside = MTD_TRUE;
        }
        else
        {
            bdk_error("%s: 88x3310 doesn't support current host mode\n", device->name);
            return -1;
        }
        break;
    case 5156: //5.15625G: half of 10Gbasex or 10G-SXGMII
        if (qlm_modes[0] == BDK_QLM_MODE_USXGMII_1X1)
        {
            allowed_speed_c = (MTD_SPEED_10M_HD |
                               MTD_SPEED_10M_FD |
                               MTD_SPEED_100M_HD |
                               MTD_SPEED_100M_FD |
                               MTD_SPEED_1GIG_HD |
                               MTD_SPEED_1GIG_FD |
                               MTD_SPEED_2P5GIG_FD |
                               MTD_SPEED_5GIG_FD);
            allowed_speed_x = MTD_FT_5GBASER;
            an_on = MTD_TRUE;
            rate_match_on = MTD_TRUE;
            is_x_hostside = MTD_FALSE;
        }
        else if(qlm_modes[0] == BDK_QLM_MODE_10G_KR)
        {
            allowed_speed_c = (MTD_SPEED_10M_HD |
                               MTD_SPEED_10M_FD |
                               MTD_SPEED_100M_HD |
                               MTD_SPEED_100M_FD |
                               MTD_SPEED_1GIG_HD |
                               MTD_SPEED_1GIG_FD |
                               MTD_SPEED_2P5GIG_FD |
                               MTD_SPEED_5GIG_FD);
            allowed_speed_x = MTD_FT_5GBASER;
            an_on = MTD_TRUE;
            rate_match_on = MTD_TRUE;
            is_x_hostside = MTD_FALSE;
        }
        else
        {
            bdk_error("%s: 88x3310 doesn't support current host mode\n", device->name);
            return -1;
        }
        break;
    case 3125:
        if (qlm_modes[0] == BDK_QLM_MODE_XAUI) //10G
        {
            allowed_speed_c = MTD_SPEED_ALL_33X0;
            an_on = MTD_TRUE;
            rate_match_on = MTD_TRUE;
            is_x_hostside = MTD_TRUE;
        }
        else if(qlm_modes[0] == BDK_QLM_MODE_SGMII) //2.5G
        {
            allowed_speed_c = (MTD_SPEED_10M_HD |
                                MTD_SPEED_10M_FD |
                                MTD_SPEED_100M_HD |
                                MTD_SPEED_100M_FD |
                                MTD_SPEED_1GIG_HD |
                                MTD_SPEED_1GIG_FD |
                                MTD_SPEED_2P5GIG_FD);
            allowed_speed_x = MTD_FT_2500BASEX;
            an_on = MTD_TRUE;
            rate_match_on = MTD_TRUE;
            is_x_hostside = MTD_FALSE;
        }
        else
        {
            bdk_error("%s: 88x3310 doesn't support current host mode\n", device->name);
            return -1;
        }
        break;
    case 2500:
        if (qlm_modes[0] == BDK_QLM_MODE_SGMII)
        {
            allowed_speed_c = MTD_SPEED_10M_HD |
                                MTD_SPEED_10M_FD |
                                MTD_SPEED_100M_HD |
                                MTD_SPEED_100M_FD |
                                MTD_SPEED_1GIG_HD |
                                MTD_SPEED_1GIG_FD;
            allowed_speed_x = MTD_FT_1000BASEX;
            an_on = MTD_TRUE;
            rate_match_on = MTD_TRUE;
            is_x_hostside = MTD_FALSE;
        }
        else
        {
            bdk_error("%s: 88x3310 doesn't support current host mode\n", device->name);
            return -1;
        }
        break;
    case 1250:
        if (qlm_modes[0] == BDK_QLM_MODE_SGMII)
        {
            allowed_speed_c = MTD_SPEED_10M_HD |
                                MTD_SPEED_10M_FD |
                                MTD_SPEED_100M_HD |
                                MTD_SPEED_100M_FD |
                                MTD_SPEED_1GIG_HD |
                                MTD_SPEED_1GIG_FD;
            allowed_speed_x = MTD_FT_1000BASEX;
            an_on = MTD_TRUE;
            rate_match_on = MTD_TRUE;
            is_x_hostside = MTD_FALSE;
        }
        else
        {
            bdk_error("%s: 88x3310 doesn't support current host mode\n", device->name);
            return -1;
        }
        break;
    case 2578: //2.578125G: quator of 10G-SXGMII
    default:
        bdk_error("%s: 88x3310 doesn't support current host mode\n", device->name);
        return -1;
    }
    /*get media sel mode*/
    MTD_U16 temp;
    TRY(mtdHwXmdioRead(&priv->mv_phy, 0, MTD_CUNIT_MODE_CONFIG, &temp));
    TRY(mtdHwGetRegFieldFromWord(temp,0,3,&media_sel));
    MTD_BOOL is_copper_enable = media_sel != MTD_MS_FBR_ONLY;
    MTD_BOOL is_fiber_enable = media_sel != MTD_MS_FBR_ONLY;
    if (is_copper_enable) 
    {
        /*turn on/off rate match*/
        if (rate_match_on) {
            TRY(_enable_rate_match(&priv->mv_phy));
        }
        /*set allowed speeds and restart copper port*/
        TRY(mtdEnableSpeeds(&priv->mv_phy,0,allowed_speed_c, MTD_TRUE));
        BDK_TRACE(DEVICE,"%s: set allowed copper speed to %x, rate match is %d\n", priv->p_device->name, allowed_speed_c,rate_match_on);
    }
    
    if (is_fiber_enable) 
    {
        if (!is_x_hostside)
        {
            /*set allowed speeds for fiber port*/
            TRY(_set_fiber_speed(&priv->mv_phy, allowed_speed_x));
        }
        BDK_TRACE(DEVICE,"%s: set allowed fiber speed to %x\n", priv->p_device->name, allowed_speed_x);
       
    }

    priv->x_hostside = is_x_hostside;
    
#endif    
    return 0;
}

/**
 * Get the currently line speed both from copper and fiber port
 * @param device Device to access
 * @param phy    PHY handle
 *
 * @return PHY link status
 */
static bdk_if_link_t phy_get_speed(bdk_device_t *device, bdk_netphy_t phy)
{
    phy_priv_t * priv = (phy_priv_t *)device->priv.phy.priv;
    MTD_DEV *p_mv_phy = &priv->mv_phy;
    bdk_if_link_t result;
    result.u64=0;

    MTD_U16 media_sel=0;
    MTD_U16 fiber_type=0;
    MTD_BOOL h_link_up = MTD_FALSE;
    MTD_BOOL x_link_up = MTD_FALSE;
    MTD_BOOL t_link_up = MTD_FALSE;
    MTD_U16 tmp_speed = 0;  //returned from mtd api, macro definition
    MTD_U16 t_speed = 0;
    MTD_U16 x_speed = 0;
    MTD_U16 full_duplex = 1;
    MTD_BOOL final_link_up = MTD_FALSE;
    MTD_UINT final_speed = 0;
    
    mtdGetCunitTopConfig(p_mv_phy,0,NULL,&media_sel,&fiber_type,NULL,NULL);
    mtdGet10GBRStatus1(p_mv_phy, 0, MTD_H_UNIT, NULL, NULL, NULL, NULL, NULL, NULL,&h_link_up);
    mtdIsBaseTUp(p_mv_phy,0,&t_speed,&t_link_up);
    
    switch (fiber_type)
    {
    case MTD_FT_1000BASEX:
        {
            MTD_U16 val=0;
            MTD_U16 link_up;
            MTD_U16 an_done;
            mtdGetBaseXrealTimeStatus(p_mv_phy,0,MTD_X_UNIT,&val);
            mtdHwGetRegFieldFromWord(val,11,1,&an_done);
            mtdHwGetRegFieldFromWord(val,10,1,&link_up);
            if (x_link_up==link_up&&an_done)
            {
                mtdHwGetRegFieldFromWord(val,14,2,&x_speed);
            }
            break;
        }
    case MTD_FT_10GBASER:
        {
            mtdGet10GBRStatus1(p_mv_phy, 0, MTD_X_UNIT, NULL, NULL, NULL, NULL, NULL, NULL,&x_link_up);
            x_speed = x_link_up ? MTD_SPEED_10GIG_FD : 0;
            break;
        }
    default:
        bdk_warn("%s: fiber type %d is not supported\n",__FUNCTION__, fiber_type);
    }

    if (h_link_up && x_link_up)
    {
        tmp_speed = x_speed;
    }
    else if (h_link_up && t_link_up) 
    {
        tmp_speed = t_speed;
    }
    else
    {
        tmp_speed = MTD_ADV_NONE;
    }

    switch (tmp_speed)
    {
    case MTD_SPEED_10M_HD:
        {
            final_speed = 10;
            full_duplex = 0;
            break;
        }
    case MTD_SPEED_10M_FD:
        {
            final_speed = 10;
            full_duplex = 1;
            break;
        }
    case MTD_SPEED_100M_HD:
        {
            final_speed = 100;
            full_duplex = 0;
            break;
        }
    case MTD_SPEED_100M_FD:
        {
            final_speed = 100;
            full_duplex = 1;
            break;
        }
    case MTD_SPEED_1GIG_HD:
        {
            final_speed = 1000;
            full_duplex = 0;
            break;
        }
    case MTD_SPEED_1GIG_FD:
        {
            final_speed = 1000;
            full_duplex = 1;
            break;
        }
    case MTD_SPEED_10GIG_FD:
        {
            final_speed = 10000;
            full_duplex = 1;
            break;
        }
    case MTD_SPEED_2P5GIG_FD:
        {
            final_speed = 2500;
            full_duplex = 1;
            break;
        }
    case MTD_SPEED_5GIG_FD:
        {
            final_speed = 5000;
            full_duplex = 1;
            break;
        }
    default:
        final_speed = 0;
        full_duplex = 0;
    }

    final_link_up = h_link_up && (x_link_up || t_link_up);

    result.s.full_duplex = full_duplex;
    result.s.up = final_link_up;
    result.s.speed = final_speed;
    result.s.lanes = 1;
    BDK_TRACE(DEVICE,"%s, current speed is %d, from %s\n", device->name, final_speed, x_link_up ? " fiber" : "copper");
    
    priv->phy_status = result;
  
    return result; 
}

/**
 * Control the PHY loopback mode
 *
 * @param device    Device to access
 * @param phy       PHY handle
 * @param host_side True if host TX should loop to host RX
 * @param line_side True if line RX should loop to line TX
 *
 * @return Zero on success, negative in failure
 */
static int phy_loopback(bdk_device_t *device, bdk_netphy_t phy, bool host_side, bool line_side)
{
    phy_priv_t *priv = device->priv.phy.priv;
    MTD_DEV_PTR p_mv_phy = &priv->mv_phy;
    if (host_side) 
    {
        TRY(mtdSetHXunitLineLoopback(p_mv_phy, 0, MTD_H_UNIT, MTD_FALSE, MTD_TRUE));
        if (priv->x_hostside == MTD_TRUE)
        {
            TRY(mtdSetHXunitLineLoopback(p_mv_phy, 0, MTD_X_UNIT, MTD_FALSE, MTD_TRUE));
        }
    }
    if (line_side) 
    {
        TRY(mtdSetTunitShallowLineLoopback(p_mv_phy,0,priv->phy_status.s.speed >= 2500?MTD_2P5G_ABOVE_LB_SPEED:MTD_1G_BELOW_LB_SPEED,MTD_TRUE));
        if (priv->x_hostside == MTD_FALSE)
        {
            TRY(mtdSetHXunitLineLoopback(p_mv_phy, 0, MTD_X_UNIT, MTD_FALSE, MTD_TRUE));
        }
    }
    return 0;
}




bdk_driver_t __bdk_driver_netphy_88x3310p = { //must in same format as defined in bdk-driver.c
    .name = "PHY-88X3310P",
    .add = add,
    .api = BDK_DEVICE_API_NETPHY,
    .funcs.netphy.init = phy_init,
    .funcs.netphy.get_speed = phy_get_speed,
    .funcs.netphy.setup_an = phy_setup_an,
    .funcs.netphy.loopback = phy_loopback,
};

bdk_driver_t __bdk_driver_netphy_88x3340p = { //must in same format as defined in bdk-driver.c
    .name = "PHY-88X3340P",
    .add = add_3340p,
    .api = BDK_DEVICE_API_NETPHY,
    .funcs.netphy.init = phy_init_3340p,
    .funcs.netphy.get_speed = phy_get_speed,
    .funcs.netphy.setup_an = phy_setup_an,
    .funcs.netphy.loopback = phy_loopback,
};


static MTD_STATUS _init_dev2(const int node, const int mdio_bus_id, const int mdio_addr, MTD_DEV_PTR devPtr)
{
    mdio_info * bus_info_p= (mdio_info *)devPtr->appData;

    MTD_STATUS status = MTD_FAIL;
    MTD_BOOL macsecIndirectAccess;

    /* if readMdio and writeMdio function pointers are NULL, the mtdHwXmdioRead
       and mtdHwXmdioWrite in mtdHwCntl.c must handle the MDIO read/write */
    FMTD_READ_MDIO readMdio = _mv_read_mdio;   /* pointer to host's function to do MDIO read */
    FMTD_WRITE_MDIO writeMdio = _mv_write_mdio; /* pointer to host's function to do MDIO write */

    /* Semaphore is work-in-progress. Set all 4 semaphore pointers to NULL */
    FMTD_SEM_CREATE semCreate = NULL;
    FMTD_SEM_DELETE semDelete = NULL;
    FMTD_SEM_TAKE semTake = NULL;
    FMTD_SEM_GIVE semGive = NULL;

    MTD_U16 anyPort = 0; /* port address of any MDIO port for this device */

    /* For Macsec/PTP, pass macsecIndirectAccess as MTD_TRUE for all 88X32X0 devices */
    /* MTD_TRUE - to access MACSec through T-unit processor
       MTD_FALSE - to do direct register access */
    macsecIndirectAccess = MTD_FALSE;

    if (!devPtr || !devPtr->appData)
    {
        bdk_error("%s: handle or devPtr or appData is NULL\n",__FUNCTION__);
        return MTD_FAIL;
    }

    bus_info_p->node = node;
    bus_info_p->bus_id = mdio_bus_id;
    bus_info_p->bus_port = mdio_addr;


    devPtr->devEnabled = MTD_FALSE; /* will be set to MTD_TRUE by mtdLoadDriver() if successful */

    status = mtdLoadDriver(readMdio, writeMdio, macsecIndirectAccess, semCreate,
                           semDelete, semTake, semGive, anyPort, devPtr);

    return status;
}

int load_88X33x0_fw(int node, int bus_id, int addr, int is_rate_match_on, int is_load_firmware, int is_multi_port)
{
    MTD_DEV mv_phy = {0};
    mdio_info  bus_info = {0};
    mv_phy.appData = (void *)&bus_info;
    TRY(_init_dev2(node, bus_id, addr ,&mv_phy));

    if (is_load_firmware)
    {
        TRY(_load_ram_img(&mv_phy, is_multi_port));
    }
    if (is_rate_match_on)
    {
        TRY(_enable_rate_match(&mv_phy));
    }
    TRY(_set_led(&mv_phy));
    return 0;
}
