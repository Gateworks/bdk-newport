/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains sample functions code for the Marvell 88X32X0, 
88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#include <stdio.h>
#include <stdlib.h>

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
#include "mtdSample.h"
#include "mtdIntr.h"

/******************************************************************************
MTD_STATUS mtdSampleInitDrv
(
    INOUT MTD_DEV_PTR devPtr,
    IN MTD_VOID *pHostContext  
)

 Inputs:
    devPtr - allocated memory for the device structure
    pHostContext - optional host context

 Outputs:
    devPtr - returns an initialized device structure

 Returns:
    Returns MTD_OK or MTD_FAIL if driver initialization fails
    
 Description:
    Sample function to show the calling of the mtdLoadDriver driver initialization
    and passing in the parameters. The valid read/write MDIO function pointers must 
    be passed in or the mtdHwXmdioRead/mtdHwXmdioWrite required changes.

 Side effects:
    None

 Notes/Warnings:
    The device pointer devPtr must be allocated with the appropriate memory size and
    must not be freed until the driver unload.

    The host context pHostContext is an optional data that is provided for host to 
    keep track of any host necessary info.

    The semaphore features are currently not supported. 

*******************************************************************************/
MTD_STATUS mtdSampleInitDrv
(
    INOUT MTD_DEV_PTR devPtr,
    IN MTD_VOID *pHostContext  /* optional host context */
)
{
    MTD_STATUS status = MTD_FAIL;
    MTD_BOOL macsecIndirectAccess; 

    /* if readMdio and writeMdio function pointers are NULL, the mtdHwXmdioRead  
       and mtdHwXmdioWrite in mtdHwCntl.c must handle the MDIO read/write */
    FMTD_READ_MDIO readMdio = NULL;   /* pointer to host's function to do MDIO read */  
    FMTD_WRITE_MDIO writeMdio = NULL; /* pointer to host's function to do MDIO write */  

    /* Semaphore is work-in-progress. Set all 4 semaphore pointers to NULL */
    FMTD_SEM_CREATE semCreate = NULL;     
    FMTD_SEM_DELETE semDelete = NULL;    
    FMTD_SEM_TAKE semTake = NULL;     
    FMTD_SEM_GIVE semGive = NULL;     

    MTD_U16 anyPort = 0; /* port address of any MDIO port for this device */

    if (!devPtr)
    {
        MTD_DBG_INFO("mtdSampleInitDrv: Error - NULL devPtr pointer\n");
        return status;
    }

    /* For Macsec/PTP, pass macsecIndirectAccess as MTD_TRUE for all 88X32X0 devices */
    /* MTD_TRUE - to access MACSec through T-unit processor
       MTD_FALSE - to do direct register access */
    macsecIndirectAccess = MTD_TRUE;

    devPtr->appData = pHostContext; /* to allow host to pass some data all the way through call stack if desired */
    
    devPtr->devEnabled = MTD_FALSE; /* will be set to MTD_TRUE by mtdLoadDriver() if successful */

    status = mtdLoadDriver(readMdio, writeMdio, macsecIndirectAccess, semCreate, 
                           semDelete, semTake, semGive, anyPort, devPtr);

    return status;
}


#define MTD_SAMPLE_MAX_LOGICAL_PORTS 69 /* assumes logical ports are numbers 1...68, there is no logical port 0 */

MTD_DEV mtdDevStructures[MTD_SAMPLE_MAX_LOGICAL_PORTS]; /* assumes first entry not used */

typedef struct
{
    int mdioBus; /* MDIO Bus Number/Id to Host */
    int mdioPortAddress; /* MDIO Address To Port */
} MTD_MDIO_BUS_MAP_STRUCT;

/******************************************************************************
  Diagram for the MDIO Address and Logical Port mapping for the sample function 
  mtdSampleSystemInitDrv():

      MDIO Bus #1              PHY Port            Logical Port
       to Host               MDIO Address   (Front Panel/CLI Marking)
         |
         |         |-------|<------0------>             1
         |<------->| X3240 |<------1------>             3
         |         |       |<------2------>             2
         |         |-------|<------3------>             4
         |
         |         |-------|<------4------>             5
         |<------->| X3240 |<------5------>             7
         |         |       |<------6------>             6
         |         |-------|<------7------>             8
         |
         |            ...         ...
         |
         |         |-------|<-----28------>            29
         |<------->| X3240 |<-----29------>            31
                   |       |<-----30------>            30
                   |-------|<-----31------>            32

      MDIO Bus #2              PHY Port     
       to Host               MDIO Address   
         |     
         |         |-------|<------0------>            33
         |<------->| X3240 |<------1------>            35
         |         |       |<------2------>            34
         |         |-------|<------3------>            36
         |
         |         |-------|<------4------>            37
         |<------->| X3240 |<------5------>            39
         |         |       |<------6------>            38
         |         |-------|<------7------>            40
         |
         |            ...         ...
         |
         |         |-------|<------28----->            61
         |<------->| X3240 |<------29----->            63
                   |       |<------30----->            62
                   |-------|<------31----->            64

      MDIO Bus #3              PHY Port     
       to Host               MDIO Address   
         |    
         |         |-------|<------0------>            65
         |<------->| X3220 |
         |         |       |<------1------>            66
         |         |-------|
         |
         |         |-------|<------2------>            67
         |<------->| X3220 |
                   |       |<------3------>            68
                   |-------|

*******************************************************************************/
/* Indexed by Logical Port Number */
MTD_MDIO_BUS_MAP_STRUCT mtdMDIOPortMap[MTD_SAMPLE_MAX_LOGICAL_PORTS] =
{
    {0,0}, /* logical port 0 not used */
    {1,0}, /* logical port 1 is on bus 1 mdio 0 */ /* first X3240 */
    {1,2}, /* logical port 2 is on bus 1 mdio 2 */
    {1,1}, /* logical port 3 is on bus 1 mdio 1 */
    {1,3}, /* logical port 4 is on bus 1 mdio 3 */
    {1,4}, /* logical port 5 is on bus 1 mdio 4 */ /* second X3240 */
    {1,6}, /* logical port 6 is on bus 1 mdio 6 */
    {1,5}, /* logical port 7 is on bus 1 mdio 5 */
    {1,7}, /* logical port 8 is on bus 1 mdio 7 */
        
/* and so on, for brevity middle ones excluded  */ 
    
    {1,28}, /* logical port 29 is on bus 1 mdio 28 */ /* last X3240 */
    {1,30}, /* logical port 30 is on bus 1 mdio 30 */
    {1,29}, /* logical port 31 is on bus 1 mdio 29 */
    {1,31}, /* logical port 32 is on bus 1 mdio 31 */
        
    {2,0}, /* logical port 33 is on bus 2 mdio 0 */ /* first X3240 */
    {2,2}, /* logical port 34 is on bus 2 mdio 2 */
    {2,1}, /* logical port 35 is on bus 2 mdio 1 */
    {2,3}, /* logical port 36 is on bus 2 mdio 3 */
    {2,4}, /* logical port 37 is on bus 2 mdio 4 */ /* second X3240 */
    {2,6}, /* logical port 38 is on bus 2 mdio 6 */
    {2,5}, /* logical port 39 is on bus 2 mdio 5 */
    {2,7}, /* logical port 40 is on bus 2 mdio 7 */
        
/* and so on, for brevity middles ones excluded  */ 
    
    {2,28}, /* logical port 61 is on bus 2 mdio 28 */ /* last X3240 */
    {2,30}, /* logical port 62 is on bus 2 mdio 30 */
    {2,29}, /* logical port 63 is on bus 2 mdio 29 */
    {2,31}, /* logical port 64 is on bus 2 mdio 31 */
        
    {3,0}, /* logical port 65 is on bus 3 mdio 28 */ /* first X3220 */
    {3,1}, /* logical port 66 is on bus 3 mdio 30 */
    {3,2}, /* logical port 67 is on bus 3 mdio 29 */ /* first X3220 */
    {3,3}, /* logical port 68 is on bus 3 mdio 31 */
};


/******************************************************************************
MTD_STATUS mtdSampleSystemInitDrv
(
    void
)

 Inputs:
    None

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL if system initialization failed.
    
 Description:
    This sample shows how to initialize a more complicated system with
    multiple MDIO buses and multiple chip types.

    It assumes the system configuration is as follows:

    MDIO Bus #1 has 8 x X3240 devices
    MDIO Bus #2 has 8 x X3240 devices
    MDIO Bus #3 has 2 x X3220 devices

    Please see the logical-to-physical mapping table for how the
    buses and MDIO addresses are mapped from logical to physical.

    Please see the above diagram for the MDIO Address and 
    Logical Port mapping of this system.
    
 Side effects:
    None

 Notes/Warnings:
    To save memory, you could have one mtdLoadDriver() call and one MTD_DEV
    structure per MDIO bus instead of per port, as long as all the devices
    on that bus are of the same PHY type. 

    This example is one way to do this using the appData field in the MTD_DEV
    structure to pass the MDIO bus number to the lower level MDIO read/write
    functions. Another way might be to initialize the MTD_DEV structure with
    pointers to different MDIO read/write functions for different buses. You
    might also have the appData field be a data structure with a callback
    to do the conversion, and the lower level read/write function could do
    the conversion instead of the caller.

*******************************************************************************/
MTD_STATUS mtdSampleSystemInitDrv
(
    void
)
{
    MTD_U32 logicalPort;
    MTD_STATUS status;

    /* initialize all the fields for single Dev that will be the same for each port */
    /* if you'll use your own mdio read/write functions, initialize them here */

    for (logicalPort = 1; logicalPort < MTD_SAMPLE_MAX_LOGICAL_PORTS; logicalPort++)
    {
        mtdDevStructures[logicalPort].appData = (MTD_PVOID)logicalPort;   
        
        status = mtdLoadDriver(NULL, NULL, MTD_TRUE, NULL, NULL, NULL, NULL,
                               mtdMDIOPortMap[logicalPort].mdioPortAddress, &mtdDevStructures[logicalPort]);

        if (status == MTD_FAIL)
        {
            return MTD_FAIL;
        }
        
    }

    /* This assumes that the low-level MDIO read/write function called in 
       mtdHwXmdioRead/mtdHwXmdioWrite will be modified to grab the appData to 
       read from/write to the correct MDIO bus */
    
    /* After this initialization you can access any PHY port */
    /* using just the MDIO port number and passing the MTD_DEV structure. */

    /* For example, to do a chip reset on the first chip (can use logicalPorts 1..4): */
    /* status = mtdChipHardwareReset(&mtdDevStructures[logicalPort], mtdMDIOPortMap[logicalPort].mdioPortAddress); */

    return MTD_TRUE;
}



/******************************************************************************
MTD_STATUS mtdSampleEnableSpeed
(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port
)

 Inputs:
    devPtr - allocated memory for the device structure
    port - MDIO port address of the near-end port, 0-31

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL if enable speed test fails or no link-up
    
 Description:
    This sample test shows how to enable the 1G speed mode and test the 
    link status. 
    
 Side effects:
    None

 Notes/Warnings:
    The far-end port must support 1G speed mode.

*******************************************************************************/
MTD_STATUS mtdSampleEnableSpeed
(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 port
)
{    
    MTD_U16 portSpeed;
    MTD_BOOL portLinkUp;
    MTD_U16 speed_to_try = MTD_SPEED_1GIG_FD; /* enable a single speed, | multiple together to enable multiple speeds */
    MTD_U16 speeds_enabled;
    MTD_U16 timeCount = 0;

    /* enable 1G speed on port with mtdAutonegRestart*/
    ATTEMPT(mtdEnableSpeeds(devPtr, port, speed_to_try, MTD_TRUE)); 

    MTD_DBG_INFO("mtdSampleEnableSpeed: Testing speed :0x%x\n\n", speed_to_try);

    ATTEMPT(mtdGetSpeedsEnabled(devPtr, port, &speeds_enabled)); /* read back speed enabled */
    if (speeds_enabled != speed_to_try)
    {
        MTD_DBG_ERROR("Get Enable Speed failed\n");
        return MTD_FAIL;
    }

    /* Poll mtdIsBaseTUp() for linkup every 0.5 second for up to 10 seconds */
    do
    {
        timeCount++;
        ATTEMPT(mtdWait(devPtr, 500)); 
        ATTEMPT(mtdIsBaseTUp(devPtr, port, &portSpeed, &portLinkUp));
    } while ((portLinkUp == MTD_FALSE) && (timeCount < 20));

    if (portSpeed != speed_to_try || portLinkUp != MTD_TRUE)
    {
        MTD_DBG_ERROR("Enable Speed Test failed\n");
        return MTD_FAIL;
    }

    MTD_DBG_INFO("Enable Speed Test completed successfully\n");
    MTD_DBG_INFO("Speed set to: 0x%X\n", portSpeed);
    MTD_DBG_INFO("Link up in %d seconds\n", timeCount/2);

    return MTD_OK;
}


/******************************************************************************
MTD_STATUS mtdSampleForceSpeed
(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 nearEndPort,
    IN MTD_U16 farEndPort
)

 Inputs:
    devPtr - allocated memory for the device structure
    nearEndPort - MDIO port address of the near-end port, 0-31
    farEndPort - MDIO port address of the far-end port, 0-31

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL if force speed fails
    
 Description:
    This sample shows how to force the T-unit to one of the supported speeds. The 
    near-end and far-end ports used in this sample helps to show the linkup status 
    between 2 ports after the force speed is configured. 

    This sample forces both the near-end and far-end ports speed to 100BT speed,
    MTD_SPEED_100M_FD_AN_DIS. After the force speed is completed, it shows how to 
    test the link status.  Lastly it undoes the forced speed and tests the link 
    status.

    "Forced" means that auto-negotiation is disabled and only that speed attempts
    to train. It is only supported for speeds at 100BT and 10BT.
    
 Side effects:
    None

 Notes/Warnings:
    This sample test requires an MDIO connection between the nearEndPort and 
    farEndPort. 

*******************************************************************************/
MTD_STATUS mtdSampleForceSpeed
(
    IN MTD_DEV_PTR devPtr, 
    IN MTD_U16 nearEndPort,
    IN MTD_U16 farEndPort
)
{
    MTD_U16 speed_to_try = MTD_SPEED_100M_FD_AN_DIS; /* may select only one of these speeds */
    MTD_BOOL nearEndPortLinkUp, farEndPortLinkUp;
    MTD_U16 nearEndPortSpeed,farEndPortSpeed;
    MTD_BOOL nearEndPortIsForced,farEndPortIsForced;
    MTD_U16 timeCount = 0;

    /* Force both sides to this speed, and AN disabled */
    ATTEMPT(mtdForceSpeed(devPtr,nearEndPort,speed_to_try)); 
    ATTEMPT(mtdForceSpeed(devPtr,farEndPort,speed_to_try));

    /* Make sure both sides are set to that speed */
    ATTEMPT(mtdGetForcedSpeed(devPtr,nearEndPort,&nearEndPortIsForced,&nearEndPortSpeed));
    ATTEMPT(mtdGetForcedSpeed(devPtr,farEndPort,&farEndPortIsForced,&farEndPortSpeed));

    if (nearEndPortIsForced == MTD_FALSE || farEndPortIsForced == MTD_FALSE)
    {
        MTD_DBG_ERROR("Get Force speed status failed\n");
        return MTD_FAIL;
    }

    if (nearEndPortSpeed != speed_to_try || farEndPortSpeed != speed_to_try)
    {
        MTD_DBG_ERROR("Get Force speed mode failed\n");
        return MTD_FAIL;
    }

    /* Poll mtdIsBaseTUp() for linkup every 0.5 second for up to 10 seconds */
    do
    {
        timeCount++;
        ATTEMPT(mtdWait(devPtr,500)); 
        ATTEMPT(mtdIsBaseTUp(devPtr,nearEndPort,&nearEndPortSpeed,&nearEndPortLinkUp));
        ATTEMPT(mtdIsBaseTUp(devPtr,farEndPort,&farEndPortSpeed,&farEndPortLinkUp));
    } while ((nearEndPortLinkUp == MTD_FALSE || farEndPortLinkUp == MTD_FALSE) && timeCount < 20);

    if (nearEndPortSpeed != speed_to_try || farEndPortSpeed != speed_to_try ||
        nearEndPortLinkUp != MTD_TRUE || farEndPortLinkUp != MTD_TRUE)
    {
        MTD_DBG_ERROR("Force speed failed\n");
        return MTD_FAIL;
    }

    MTD_DBG_INFO("Force speed set to: 0x%X\n", nearEndPortSpeed);
    MTD_DBG_INFO("Force speed link up in %d seconds\n", timeCount/2);

    /* Undo the forced speed */
    ATTEMPT(mtdUndoForcedSpeed(devPtr,nearEndPort,MTD_FALSE)); /* Calls mtdAutonegEnable() */
    ATTEMPT(mtdUndoForcedSpeed(devPtr,farEndPort,MTD_FALSE)); /* Calls mtdAutonegEnable() */

    /* NOTE: use MTD_SPEED_ALL_33X0 to include 5G/2.5G speeds for 88X33X0 parts */
    /* use MTD_SPEED_ALL_21X0_20X0 to advertise 5G and below only */
    /* this sample will enable 10G, which is not available on E20X0 and E21X0 parts */
    /* and does not enable 5G/2.5G, so if you run this sample on a E20X0/E21X0 part, 1G will come up */
    /* and speed resolution test below will fail. */
    ATTEMPT(mtdEnableSpeeds(devPtr,nearEndPort,MTD_SPEED_ALL_32X0,MTD_TRUE)); /* Uses mtdAutonegRestart() */
    ATTEMPT(mtdEnableSpeeds(devPtr,farEndPort,MTD_SPEED_ALL_32X0,MTD_TRUE)); /* Uses mtdAutonegRestart() */
    
    /* Poll mtdIsBaseTUp() for linkup every 0.5 second for up to 10 seconds */
    do
    {
        timeCount++;
        ATTEMPT(mtdWait(devPtr,500)); 
        ATTEMPT(mtdIsBaseTUp(devPtr,nearEndPort,&nearEndPortSpeed,&nearEndPortLinkUp));
        ATTEMPT(mtdIsBaseTUp(devPtr,farEndPort,&farEndPortSpeed,&farEndPortLinkUp));
    } while ((nearEndPortLinkUp == MTD_FALSE || farEndPortLinkUp == MTD_FALSE) && timeCount < 20);

    if (nearEndPortSpeed != MTD_SPEED_10GIG_FD || farEndPortSpeed != MTD_SPEED_10GIG_FD ||
        nearEndPortLinkUp != MTD_TRUE || farEndPortLinkUp != MTD_TRUE)
    {
        MTD_DBG_ERROR("Undo Force speed failed\n");
        return MTD_FAIL;
    }

    MTD_DBG_INFO("Undo Force speed set to: 0x%X\n", nearEndPortSpeed);
    MTD_DBG_INFO("Undo Force speed link up in %d seconds\n", timeCount/2);

    MTD_DBG_INFO("Force speed Test completed successfully\n");

    return MTD_OK;
}

/* Rename these files to match the image filenames */
#define MTD_SLAVE_IMAGE_FILE     "x3240flashdlslave_0_6_5_0_9501.bin" /* this is the helper program for flash download */

/* #define MTD_APP_IMAGE_FILE       "x3240fw_0_3_12_0_8433.hdr" */
#define MTD_APP_IMAGE_FILE       "x3310fw_0_2_3_3_8502.hdr" /* this is the PHY application code */

/******************************************************************************
MTD_STATUS mtdSampleUpdateRamImage
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)

 Inputs:
    devPtr - allocated memory for the device structure
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL if RAM update fails
    
 Description:
    This sample test shows how the application code is downloaded to RAM via MDIO
    when the PHY isn't equipped with flash or flash is being bypassed. 

    It shows the operations to open and read the binary file, gets the image data size 
    and loads the binary data to be downloaded into the RAM buffer. 

    The mtdUpdateRamImage() is called with the above inputs. After the 
    mtdUpdateRamImage() call is completed, it checks the firmware version.

    Using this method, each port must be downloaded one-at-a-time. You can download
    multiple ports at once using MDIO broadcast to all devices on the same MDIO
    bus by using the function mtdParallelUpdateRamImage().
    
 Side effects:
    None

 Notes/Warnings:
    Make sure the file is opened in "rb"(read+binary) mode.

*******************************************************************************/
MTD_STATUS mtdSampleUpdateRamImage
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)
{
    MTD_STATUS status = MTD_FAIL;
    MTD_U16 errorCode;
    MTD_U8 *appData = NULL;
    MTD_U32 appSize = 0;
    FILE *file;

    /* Make sure the file is opened in "rb"(read+binary) mode */ 
    file = fopen(MTD_APP_IMAGE_FILE, "rb");
    fseek(file, 0, SEEK_END);

    /* get the application code image size needed for the mtdUpdateRamImage() */
    appSize = (MTD_U32)ftell(file);
    rewind(file);

    if( appSize == 0 )
    {
        fclose(file);
        MTD_DBG_ERROR("File is empty\n");
        return status;
    }

    appData = (MTD_U8*)malloc(appSize + 1);
    if (appData == NULL)
    {
        MTD_DBG_ERROR("Failed to allocate memory\n");
        return status;
    }

    fread(appData, appSize, 1, file);
    fclose(file);
    appData[appSize] = 0;

    status = mtdUpdateRamImage(devPtr, port, appData, appSize, &errorCode);

    if (status == MTD_OK)
    {
        MTD_U8 major;
        MTD_U8 minor;
        MTD_U8 inc;
        MTD_U8 test;

        /* if the mtdUpdateRamImage() is successful, calls the mtdGetFirmwareVersion()
           to check and verify the updated version number */
        mtdWait(devPtr, 1000);
        mtdGetFirmwareVersion(devPtr, port, &major, &minor, &inc, &test);
        MTD_DBG_INFO("RAM image loaded successful\n");
        MTD_DBG_INFO("Firmware version: %d.%d.%d.%d\n", major, minor, inc, test);
    }
    else
    {
        MTD_DBG_ERROR("mtdSampleUpdateRamImage: Failed with error code: 0x%x\n", errorCode);
    }

    if (appData)
    {
        free(appData);
    }

    return status;
}

/******************************************************************************
MTD_STATUS mtdSampleUpdateFlashImage
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)

 Inputs:
    devPtr - allocated memory for the device structure
    port - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL if Flash update fails
    
 Description:
    This sample test shows how to download a new application image to the flash.

    Depending on the part, there may be one flash per 1 port, 2 ports, or 4 ports. 
    Only the first port on each device needs to be downloaded. All ports on the
    same device share the same image on the flash.

    The flash download program uses a small "helper" program that is downloaded
    to the PHYs RAM first. That helper program interacts with the host to
    take the image being downloaded and program it into the flash via the SPI.

    This sample shows the operations to open and read the binary application code image
    to be loaded to flash and the binary helper program, gets the both
    images data sizes and loads both into its seperate buffers. 

    The mtdUpdateFlashImage() is called with the above inputs. After the 
    mtdUpdateFlashImage() call is completed, it takes the PHY out of download mode, 
    resets the PHY, then verifies new image is running.

    Each device (one port per device that is sharing the same flash) must be
    downloaded with one call to mtdUpdateFlashImage(). Multiple
    devices can be broadcast downloaded over the same MDIO bus by using the
    function mtdParallelUpdateFlashImage().

 Side effects:
    None

 Notes/Warnings:
    Make sure the files are opened in "rb"(read+binary) mode

*******************************************************************************/
MTD_STATUS mtdSampleUpdateFlashImage
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)
{
    MTD_STATUS status = MTD_FAIL;
    MTD_U16 errorCode;
    MTD_U8 *appData = NULL;
    MTD_U8 *slaveData = NULL;
    MTD_U32 appSize = 0;
    MTD_U32 slaveSize = 0;
    FILE *appFile, *slaveFile;

    /* Make sure the application code image file is opened in "rb"(read+binary) mode */ 
    appFile = fopen(MTD_APP_IMAGE_FILE, "rb");
    fseek(appFile, 0, SEEK_END);

    /* get the application code image size needed for the mtdUpdateFlashImage() */
    appSize = (MTD_U32)ftell(appFile);
    rewind(appFile);

    if( appSize == 0 )
    {
        fclose(appFile);
        MTD_DBG_ERROR("Incorrect application code size\n");
        return status;
    }

    /* Make sure the helper program file is opened in "rb"(read+binary) mode */ 
    slaveFile = fopen(MTD_SLAVE_IMAGE_FILE, "rb");
    fseek(slaveFile, 0, SEEK_END);

    /* get the flash size needed for the mtdUpdateFlashImage() */
    slaveSize = (MTD_U32)ftell(slaveFile);
    rewind(slaveFile);

    if( slaveSize == 0 )
    {
        fclose(slaveFile);
        MTD_DBG_ERROR("Incorrect slave size\n");
        return status;
    }

    appData = (MTD_U8*)malloc(appSize + 1);
    if (appData == NULL)
    {
        MTD_DBG_ERROR("Failed to allocate memory for application code image\n");
        return status;
    }

    slaveData = (MTD_U8*)malloc(slaveSize + 1);
    if (slaveData == NULL)
    {
        MTD_DBG_ERROR("Failed to allocate memory for slave helper program image\n");
        return status;
    }

    fread(appData, appSize, 1, appFile);
    fclose(appFile);
    appData[appSize] = 0;

    fread(slaveData, slaveSize, 1, slaveFile);
    fclose(slaveFile);
    slaveData[slaveSize] = 0;

    status = mtdUpdateFlashImage(devPtr, port, appData, appSize, slaveData, slaveSize, &errorCode);

    if (status == MTD_OK)
    {
        MTD_U8 major;
        MTD_U8 minor;
        MTD_U8 inc;
        MTD_U8 test;

        /* if the mtdUpdateFlashImage() is successful, calls the mtdGetFirmwareVersion()
           to check and verify the updated version number */
        mtdRemovePhyMdioDownloadMode(devPtr, port); /* takes PHY out of download mode and does a hardware */
                                                   /* reset on the T unit to reload the new image from flash */
        mtdWait(devPtr, 1000);
        mtdGetFirmwareVersion(devPtr, port, &major, &minor, &inc, &test);
        MTD_DBG_INFO("Application code image loaded successful to flash\n");
        MTD_DBG_INFO("Firmware version: %d.%d.%d.%d\n", major, minor, inc, test);
    }
    else
    {
        MTD_DBG_ERROR("mtdSampleUpdateFlashImage: Failed with error code: 0x%x\n", errorCode);
    }

    if (appData)
    {
        free(appData);
    }

    if (slaveData)
    {
        free(slaveData);
    }

    return status;
}


/******************************************************************************
MTD_STATUS mtdSampleCopperToFiberMode1G
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 nearEndPort,
    IN MTD_U16 farEndPort
)

 Inputs:
    devPtr - allocated memory for the device structure
    nearEndPort - MDIO port address, 0-31
    farEndPort - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL if changing Copper to Fiber mode fails
    
 Description:
    This sample shows how to switch from the Copper mode to the Fiber mode. The 
    near-end and far-end ports used in this sample helps to show the linkup status 
    between 2 ports after switching from the Copper to the Fiber mode. 

    This test sets the H unit to SGMII, the X unit to 1000BX and the C Unit to fiber 
    only mode. After the modes are set, it checks the AN complete and link status.

 Side effects:
    None

 Notes/Warnings:
    This test requires an MDIO connection to both near end and far end ports.

*******************************************************************************/
MTD_STATUS mtdSampleCopperToFiberMode1G
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 nearEndPort,
    IN MTD_U16 farEndPort
)
{
    MTD_BOOL an_complete;  /* AutoNeg completion status */
    MTD_BOOL remote_fault;
    MTD_BOOL ls_latched;
    MTD_BOOL ls_current;
    
    /* Configure both H units for fiber only 1000BASE-X mode */
    ATTEMPT(mtdSetCunitTopConfig(devPtr, nearEndPort, MTD_F2R_OFF, MTD_MS_FBR_ONLY,
                                 MTD_FT_1000BASEX, MTD_FALSE, MTD_FALSE, MTD_TRUE, MTD_FALSE));

    ATTEMPT(mtdSetCunitTopConfig(devPtr, farEndPort, MTD_F2R_OFF, MTD_MS_FBR_ONLY, 
                                 MTD_FT_1000BASEX, MTD_FALSE, MTD_FALSE, MTD_TRUE, MTD_FALSE));
    
    ATTEMPT(mtdSetMacInterfaceControl(devPtr, nearEndPort, MTD_MAC_TYPE_XFI_SGMII_AN_EN, MTD_TRUE,
                                      MTD_MAC_SNOOP_OFF, 0, MTD_MAC_SPEED_10_GBPS, 
                                      MTD_MAX_MAC_SPEED_LEAVE_UNCHANGED, MTD_TRUE,MTD_TRUE));

    ATTEMPT(mtdSetMacInterfaceControl(devPtr, farEndPort, MTD_MAC_TYPE_XFI_SGMII_AN_EN, MTD_TRUE, 
                                      MTD_MAC_SNOOP_OFF, 0, MTD_MAC_SPEED_10_GBPS, 
                                      MTD_MAX_MAC_SPEED_LEAVE_UNCHANGED, MTD_TRUE, MTD_TRUE));

    /* Configure the BASE-X in both directions, and make one a little different to check status
       Make the fault different in one direction and the pause different in one direction, everything else the same */
    ATTEMPT(mtdSet1000BXAutoneg_Advertisement(devPtr,nearEndPort,MTD_1000BX_REMOTE_FAULT_LF,MTD_SYM_PAUSE,MTD_TRUE));
    ATTEMPT(mtdSet1000BXAutoneg_Advertisement(devPtr,farEndPort,MTD_1000BX_REMOTE_FAULT_NONE,MTD_ASYM_PAUSE,MTD_TRUE));
    
    ATTEMPT(mtdSet1000BXSGMIIControl(devPtr,nearEndPort,MTD_X_UNIT,MTD_FALSE,MTD_SGMII_SPEED_1G,MTD_TRUE,MTD_FALSE,MTD_TRUE,MTD_TRUE));
    ATTEMPT(mtdSet1000BXSGMIIControl(devPtr,farEndPort,MTD_X_UNIT,MTD_FALSE,MTD_SGMII_SPEED_1G,MTD_TRUE,MTD_FALSE,MTD_TRUE,MTD_TRUE));

    mtdWait(devPtr,1000);

    ATTEMPT(mtdGet1000BXSGMIIStatus(devPtr,nearEndPort,MTD_X_UNIT,&an_complete,&remote_fault,&ls_latched,&ls_current));

    if (an_complete == MTD_FALSE || remote_fault == MTD_TRUE || ls_latched == MTD_TRUE || ls_current == MTD_FALSE)
    {
        MTD_DBG_ERROR("CopperToFiberMode: X unit failed Port:%u an_complete:%u remote_fault:%u ls_latched:%u, ls_current:%u\n",
                     nearEndPort, an_complete, remote_fault, ls_latched, ls_current);
        return MTD_FAIL;
    }

    ATTEMPT(mtdGet1000BXSGMIIStatus(devPtr,farEndPort,MTD_X_UNIT,&an_complete,&remote_fault,&ls_latched,&ls_current));

    if (an_complete == MTD_FALSE || remote_fault == MTD_FALSE || ls_latched == MTD_TRUE || ls_current == MTD_FALSE)
    {
        MTD_DBG_ERROR("CopperToFiberMode: X unit failed Port:%u an_complete:%u remote_fault:%u ls_latched:%u, ls_current:%u\n",
                     farEndPort, an_complete, remote_fault, ls_latched, ls_current);
        return MTD_FAIL;
    }

    MTD_DBG_INFO("Copper mode to Fiber 1G mode changed completed successfully.\n");

    return MTD_OK;
}


/******************************************************************************
MTD_STATUS mtdSampleCopperToFiberMode10G
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 nearEndPort,
    IN MTD_U16 farEndPort
)

 Inputs:
    devPtr - allocated memory for the device structure
    nearEndPort - MDIO port address, 0-31
    farEndPort - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL if changing Copper to Fiber mode fails
    
 Description:
    This sample shows how to switch from the Copper mode to the Fiber mode. The 
    near-end and far-end ports used in this sample helps to show the linkup status 
    between 2 ports after switching from the Copper to the Fiber mode. 

    This test changes the mode to 10GBASE-R (XFI) on both near-end and far-end ports
    and checks the link status on both X and H unit.
    
 Side effects:
    None

 Notes/Warnings:
    This test requires an MDIO connection to both near end and far end ports.

    This test is reading the link's current, real-time status. To get the latched
    link status, call mtdGet10GBRStatus1() (to check if the link dropped since
    the last call, for example.)
 
*******************************************************************************/
MTD_STATUS mtdSampleCopperToFiberMode10G
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 nearEndPort,
    IN MTD_U16 farEndPort
)
{
    MTD_BOOL ls_current;
    MTD_BOOL high_ber;
    MTD_BOOL block_lock;

    /* Test Fiber Only Mode with 10GBR on both sides */
    ATTEMPT(mtdSetCunitTopConfig(devPtr, nearEndPort, MTD_F2R_OFF, MTD_MS_FBR_ONLY,
                                 MTD_FT_10GBASER, MTD_FALSE, MTD_FALSE, MTD_FALSE, MTD_FALSE));

    ATTEMPT(mtdSetCunitTopConfig(devPtr, farEndPort, MTD_F2R_OFF, MTD_MS_FBR_ONLY, 
                                 MTD_FT_10GBASER, MTD_FALSE, MTD_FALSE, MTD_FALSE, MTD_FALSE));
    
    ATTEMPT(mtdSetMacInterfaceControl(devPtr, nearEndPort, MTD_MAC_TYPE_XFI_SGMII_AN_EN,
                                      MTD_TRUE, MTD_MAC_SNOOP_OFF, 0, MTD_MAC_SPEED_10_GBPS,
                                      MTD_MAX_MAC_SPEED_LEAVE_UNCHANGED, MTD_TRUE, MTD_TRUE));

    ATTEMPT(mtdSetMacInterfaceControl(devPtr, farEndPort, MTD_MAC_TYPE_XFI_SGMII_AN_EN,
                                      MTD_TRUE, MTD_MAC_SNOOP_OFF, 0, MTD_MAC_SPEED_10_GBPS,
                                      MTD_MAX_MAC_SPEED_LEAVE_UNCHANGED, MTD_TRUE, MTD_TRUE));

    /* optional, does a soft reset on the 10GBASE-R block  */
    ATTEMPT(mtdSet10GBRControl(devPtr, nearEndPort, MTD_X_UNIT, MTD_FALSE, MTD_FALSE, MTD_TRUE));
    ATTEMPT(mtdSet10GBRControl(devPtr, nearEndPort, MTD_H_UNIT, MTD_FALSE, MTD_FALSE, MTD_TRUE));
   
    ATTEMPT(mtdSet10GBRControl(devPtr, farEndPort, MTD_X_UNIT, MTD_FALSE, MTD_FALSE, MTD_TRUE));
    ATTEMPT(mtdSet10GBRControl(devPtr, farEndPort, MTD_H_UNIT, MTD_FALSE, MTD_FALSE, MTD_TRUE));


    mtdWait(devPtr, 1000); /* wait for both to come up */

    ATTEMPT(mtdGet10GBRReceiveStatus(devPtr,nearEndPort,MTD_H_UNIT,&ls_current,&high_ber,&block_lock));

    if (ls_current == MTD_FALSE || high_ber == MTD_TRUE || block_lock == MTD_FALSE)
    {
        MTD_DBG_ERROR("CopperToFiberMode: H unit failed Port:%u ls_current:%u high_ber:%u block_lock:%u\n",
                      nearEndPort, ls_current, high_ber, block_lock);
        return MTD_FAIL;
    }

    ATTEMPT(mtdGet10GBRReceiveStatus(devPtr,nearEndPort,MTD_X_UNIT,&ls_current,&high_ber,&block_lock));

    if (ls_current == MTD_FALSE || high_ber == MTD_TRUE || block_lock == MTD_FALSE)
    {
        MTD_DBG_ERROR("CopperToFiberMode: X unit failed Port:%u ls_current:%u high_ber:%u block_lock:%u\n",
                      nearEndPort, ls_current, high_ber, block_lock);
        return MTD_FAIL;
    }

    ATTEMPT(mtdGet10GBRReceiveStatus(devPtr,farEndPort,MTD_H_UNIT,&ls_current,&high_ber,&block_lock));

    if (ls_current == MTD_FALSE || high_ber == MTD_TRUE || block_lock == MTD_FALSE)
    {
        MTD_DBG_ERROR("CopperToFiberMode: H unit failed Port:%u ls_current:%u high_ber:%u block_lock:%u\n",
                      farEndPort, ls_current, high_ber, block_lock);
        return MTD_FAIL;
    }

    ATTEMPT(mtdGet10GBRReceiveStatus(devPtr,farEndPort,MTD_X_UNIT,&ls_current,&high_ber,&block_lock));

    if (ls_current == MTD_FALSE || high_ber == MTD_TRUE || block_lock == MTD_FALSE)
    {
        MTD_DBG_ERROR("CopperToFiberMode: X unit failed Port:%u ls_current:%u high_ber:%u block_lock:%u\n",
                     farEndPort, ls_current, high_ber, block_lock);
        return MTD_FAIL;
    }

    MTD_DBG_INFO("Copper mode to Fiber 10G mode changed completed successfully.\n");

    return MTD_OK;
}


/******************************************************************************
MTD_STATUS mtdSampleFiberToCopperMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 nearEndPort,
    IN MTD_U16 farEndPort
)

 Inputs:
    devPtr - allocated memory for the device structure
    nearEndPort - MDIO port address, 0-31
    farEndPort - MDIO port address, 0-31

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL if changing Fiber to Copper mode fails
    
 Description:
    This sample shows how to switch from the Fiber mode to the Copper mode. The 
    near-end and far-end ports used in this sample helps to show the linkup status 
    between 2 ports after switching from the Fiber to the Copper mode. 

    This test changes the configuration to Copper mode 10GBASE-T on both near-end 
    and far-end ports. After the change, it polls every half a second up to 10 seconds
    to check the copper link status. 

 Side effects:
    None

 Notes/Warnings:
    This test requires an MDIO connection to both near end and far end ports.

    This test assumes both ends were previously set to advertise 10GBT
    or defaulted to this on reset.
    
*******************************************************************************/
MTD_STATUS mtdSampleFiberToCopperMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 nearEndPort,
    IN MTD_U16 farEndPort
)
{
    MTD_U16 baseTSpeed;
    MTD_BOOL islinkup;
    MTD_U16 timeCount = 0;

    if (!MTD_HAS_X_UNIT(devPtr))
    {
        /* no fiber interface on this PHY */
        ATTEMPT(mtdSetCunitTopConfig(devPtr, nearEndPort, MTD_F2R_OFF, MTD_MS_CU_ONLY, 
                                 MTD_FT_NONE, MTD_FALSE, MTD_FALSE, MTD_TRUE, MTD_FALSE));

        ATTEMPT(mtdSetCunitTopConfig(devPtr, farEndPort, MTD_F2R_OFF, MTD_MS_CU_ONLY,
                                 MTD_FT_NONE, MTD_FALSE, MTD_FALSE, MTD_TRUE, MTD_FALSE));
    }
    else
    {
        ATTEMPT(mtdSetCunitTopConfig(devPtr, nearEndPort, MTD_F2R_OFF, MTD_MS_CU_ONLY, 
                                 MTD_FT_10GBASER, MTD_FALSE, MTD_FALSE, MTD_TRUE, MTD_FALSE));

        ATTEMPT(mtdSetCunitTopConfig(devPtr, farEndPort, MTD_F2R_OFF, MTD_MS_CU_ONLY,
                                 MTD_FT_10GBASER, MTD_FALSE, MTD_FALSE, MTD_TRUE, MTD_FALSE));
    }

    ATTEMPT(mtdSetMacInterfaceControl(devPtr, nearEndPort, MTD_MAC_TYPE_XFI_SGMII_AN_EN, 
                                      MTD_TRUE, MTD_MAC_SNOOP_OFF, 0, MTD_MAC_SPEED_10_GBPS,
                                      MTD_MAX_MAC_SPEED_LEAVE_UNCHANGED, MTD_TRUE, MTD_TRUE));
    
    ATTEMPT(mtdSetMacInterfaceControl(devPtr, farEndPort, MTD_MAC_TYPE_XFI_SGMII_AN_EN, 
                                      MTD_TRUE, MTD_MAC_SNOOP_OFF, 0, MTD_MAC_SPEED_10_GBPS,
                                      MTD_MAX_MAC_SPEED_LEAVE_UNCHANGED, MTD_TRUE, MTD_TRUE));
    
    /* Poll mtdIsBaseTUp() for linkup every 0.5 second for up to 10 seconds */
    do
    {
        timeCount++;
        ATTEMPT(mtdWait(devPtr, 500)); 
        ATTEMPT(mtdIsBaseTUp(devPtr, nearEndPort, &baseTSpeed, &islinkup));
    } while (islinkup == MTD_FALSE && timeCount < 20);

    if (!(islinkup == MTD_TRUE && (baseTSpeed == MTD_SPEED_10GIG_FD || baseTSpeed == MTD_SPEED_5GIG_FD)))
    {
        MTD_DBG_ERROR("FiberToCopperMode: failed Port:%u islinkup:0x%X baseTSpeed:0x%X\n", 
                      nearEndPort, islinkup, baseTSpeed);
        return MTD_FAIL;
    }

    if (baseTSpeed == MTD_SPEED_10GIG_FD)
    {
        MTD_DBG_INFO("Fiber to Copper mode changed completed successfully. Link is up at 10G speed in %u seconds.\n", 
                  timeCount/2);
    }
    else
    {
        MTD_DBG_INFO("Fiber to Copper mode changed completed successfully. Link is up at 5G speed in %u seconds.\n", 
                  timeCount/2);
    }

    return MTD_OK;
}

/******************************************************************************
MTD_STATUS mtdSampleGetEye
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 lane
)

 Inputs:
    devPtr - allocated memory for the device structure
    port - MDIO port address, 0-31
    lane - eye data of the lane 

 Outputs:
    None

 Returns:
    Returns MTD_OK or MTD_FAIL if the eye diagram reading or plotting fails
    
 Description:
    Sample code to extract the eye data and plotting eye diagram by calling 
    the mtdGetSerdesEyeStatistics and mtdSerdesEyePlotChart APIs.
    The mtdSerdesEyePlotChart will plot the eye diagram to the buffer defined 
    in the mtdDbgPrint().

 Side effects:
    None

 Notes/Warnings:
    Must wait for link up before extracting eye data.


*******************************************************************************/
MTD_STATUS mtdSampleGetEye
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_U16 lane
)
{
    MTD_U16 eyeArea;
    MTD_U16 eyeWidth; 
    MTD_U16 eyeHeight;

    /* provide the arrays for the eye data */
    MTD_U32 eyeDataUp[(MTD_EYEDIAGRAM_NROWS + 1) / 2][MTD_EYEDIAGRAM_NCOLS];
    MTD_U32 eyeDataDn[(MTD_EYEDIAGRAM_NROWS + 1) / 2][MTD_EYEDIAGRAM_NCOLS];

    ATTEMPT(mtdGetSerdesEyeStatistics(devPtr, port, lane, eyeDataUp, eyeDataDn, 
                                      &eyeArea, &eyeWidth, &eyeHeight));

    ATTEMPT(mtdSerdesEyePlotChart(devPtr, eyeDataUp, eyeDataDn));


    MTD_DBG_INFO("mtdSampleGetEye: eyeArea:%u eyeWidth:%u eyeHeight:%u\n", 
                 eyeArea, eyeWidth, eyeHeight);

    return MTD_OK;
}

/******************************************************************************
MTD_STATUS mtdSampleGetChipIntrStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_INTR_STATUS interruptStatus[]
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port   - mdio address of first port on device 

 Outputs:
    interruptStatus[] - array of interrupt structures, one per port, total size 
                        determined by devPtr->numPorts. User required to allocate
                        memory at least devPtr->numPorts structures.

 Returns:
    MTD_OK or MTD_FAIL

 Description:
    Get the status of all the triggered interrupts on this device. 

    This function uses devPtr->numPorts to determine how many ports to check
    and return. Caller may use this to determine how much memory to allocate.

    Please check the interrupt definition of the corresponding unit to identify 
    the interrupt source. See the defines in mtdIntr.h for the defines for
    these interrupts.

 Side effects:
    None

 Notes/Warnings:
    No X-unit on E20X0 and E21X0 PHYs. 
    
    All individual interrupts are cleared after this API call. This function
    checks all interrupts regardless of enable/disable (mask).
******************************************************************************/
MTD_STATUS mtdSampleGetChipIntrStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_INTR_STATUS interruptStatus[]
)
{
    MTD_U16  i;
    MTD_BOOL interruptTrig;

    for (i=0; i<devPtr->numPorts; i++)
    {
        ATTEMPT(mtdGetPortIntrStatus(devPtr, (port+i), &interruptTrig, &interruptStatus[i]));
        if (interruptTrig == MTD_TRUE)
        {
             MTD_DBG_INFO("Interrupt triggered on port: %d\n", (port+i));
        }
    }

    return MTD_OK;
}

/******************************************************************************
MTD_STATUS mtdSampleE21X0EnableSerialLED
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31 

 Outputs:
    none

 Returns:
    MTD_OK if LEDs are successfully configured
    MTD_FAIL if the device is not supported or other failure

 Description:
    This sample function applies to only 88E2110 and 88E2180 PHY devices.  It shows 
    how to enable the Serial LEDs for various activities, statuses, features, etc...  
    
    The following are some of the LED registers to configure the LEDs. Refer to the 
    datasheet for the complete details on these registers and other LED registers:
        31.0xF03A - LED Control Register is a global register. A write to 31.F03A on 
        any port will update all 8 ports on the 88E2180
        31.0xF020 - LED[0] Control
        31.0xF021 - LED[1] Control
        31.0xF022 - LED[2] Control

    This sample sets the LED1 to turn ON when port is running at 5G speed and 
    LED2 to turn ON when port is running at 2.5G speed.

 Side effects:
    None

 Notes/Warnings:
******************************************************************************/
MTD_STATUS mtdSampleE21X0EnableSerialLED
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)
{
    if (!(MTD_IS_E21X0_BASE(devPtr->deviceId)))
    {
        MTD_DBG_ERROR("mtdSampleE21X0EnableSerialLED: Device is not supported.\n");
        return MTD_FAIL;
    }

    /* if device is not a 1 or 8-port device, it's not supported */
    if (!((devPtr->numPorts == 1) || (devPtr->numPorts == 8)))
    {
        MTD_DBG_ERROR("mtdSampleE21X0EnableSerialLED: Device with port count:%d is not supported.\n", devPtr->numPorts);
        return MTD_FAIL;
    }

    /* enables all 3 LEDs for E2110 and E2180 on 31.F03A; 31.F03A is a global register; 
       A write to 31.F03A to any port will update all 8 ports */
    ATTEMPT(mtdHwXmdioWrite(devPtr, port, MTD_C_UNIT_GENERAL, CUNIT_SLED_CONTROL, 0x0112));

    if (devPtr->numPorts == 1) /* E2110 */
    {
        /* LED1 turns on when linkup on 5G, 31.F021 */
        ATTEMPT(mtdHwXmdioWrite(devPtr, port, MTD_C_UNIT_GENERAL, CUNIT_LED1_CONTROL, 0x00B0));

        /* LED2 turns on when linkup on 2.5G, 31.F022 */
        ATTEMPT(mtdHwXmdioWrite(devPtr, port, MTD_C_UNIT_GENERAL, CUNIT_LED2_CONTROL, 0x00A8));

    }
    else /* E2180 */
    {
        MTD_U16 numPorts, basePort, portIndex;

        numPorts = devPtr->numPorts;

        /* calculates the MDIO port number of the 1st(base) port */
        basePort = (port/numPorts) * numPorts;   
        for (portIndex = basePort; portIndex < devPtr->numPorts; portIndex++) 
        {
            /* LED1 turns on when linkup on 5G, 31.F021 */
            ATTEMPT(mtdHwXmdioWrite(devPtr, portIndex, MTD_C_UNIT_GENERAL, CUNIT_LED1_CONTROL, 0x00B0));

            /* LED2 turns on when linkup on 2.5G, 31.F022 */
            ATTEMPT(mtdHwXmdioWrite(devPtr, portIndex, MTD_C_UNIT_GENERAL, CUNIT_LED2_CONTROL, 0x00A8));
        }
    }

    return MTD_OK;
}


/******************************************************************************
MTD_STATUS mtdSampleE2180EnableParallelLED
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
);

 Inputs:
    devPtr - pointer to MTD_DEV initialized by mtdLoadDriver() call
    port - MDIO port address, 0-31 

 Outputs:
    none

 Returns:
    MTD_OK if LEDs are successfully configured
    MTD_FAIL if the device is not supported or other failure

 Description:
    This sample function applies to only 88E2180 PHY device.  It shows 
    how to enable the parallel LEDs on the 88E2180 for various activities, 
    statuses, features, etc...  
    
    The following are some of the LED registers to configure the LEDs. Refer to the 
    datasheet for the complete details on these registers and other LED registers:
        31.0xF015 - GPIO Interrupt Control
        31.0xF020 - LED[0] Control
        31.0xF021 - LED[1] Control

    This sample sets the parallel LEDs where LED0 turns on for copper link and blinks
    on tx/rx activity, and LED1 turns on for 5G speed (off for lower speeds).

 Side effects:
    None

 Notes/Warnings:
*******************************************************************************/
MTD_STATUS mtdSampleE2180EnableParallelLED
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)
{
    MTD_U16 numPorts, basePort, portIndex;

    if (!(MTD_IS_E21X0_BASE(devPtr->deviceId)))
    {
        MTD_DBG_ERROR("mtdSampleE2180EnableParallelLED: Device is not supported.\n");
        return MTD_FAIL;
    }

    /* if device is not a 8-port device, it's not supported */
    if (!(devPtr->numPorts == 8))
    {
        MTD_DBG_ERROR("mtdSampleE2180EnableParallelLED: Device with port count:%d is not supported.\n", devPtr->numPorts);
        return MTD_FAIL;
    }

    numPorts = devPtr->numPorts;

    /* calculates the MDIO port number of the 1st(base) port */
    basePort = (port/numPorts) * numPorts; 

    for (portIndex = basePort; portIndex < devPtr->numPorts; portIndex++) 
    {
        /* enable 2 LED mode control by GPIO, 31.F015 */
        ATTEMPT(mtdHwXmdioWrite(devPtr, portIndex, MTD_C_UNIT_GENERAL, CUNIT_GPIO_CONTROL, 0x8800));
        
        /* uses default for LED0, on for copper link, blink for tx/rx activity */

        /* LED1 turns on when linkup on 5G, 31.F021 */
        ATTEMPT(mtdHwXmdioWrite(devPtr, portIndex, MTD_C_UNIT_GENERAL, CUNIT_LED1_CONTROL, 0x00B0));
    }

    return MTD_OK;
}

