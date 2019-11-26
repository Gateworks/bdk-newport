/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for
higher-level functions using MDIO access to enable test modes,
loopbacks, and other diagnostic functions of the Marvell 88X32X0, 
88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdAPI.h"
#include "mtdApiRegs.h"
#include "mtdDiagnostics.h"
#include "mtdAPIInternal.h"
#include "mtdCunit.h"
#include "mtdUtils.h"

MTD_STATUS mtdGetPhyRevision
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_DEVICE_ID *phyRev,
    OUT MTD_U8 *numPorts,
    OUT MTD_U8 *thisPort
)
{
    MTD_U16 temp, tryCounter, temp2, baseType, reportedHwRev;
    MTD_U16 revision, numports,thisport, readyBit,fwNumports,fwThisport;
    MTD_BOOL registerExists, regReady, hasMacsec = MTD_FALSE, hasCopper = MTD_FALSE, isE20X0Device = MTD_FALSE;
    MTD_U8 major, minor, inc, test;

    *phyRev = MTD_REV_UNKNOWN; /* in case we have any failed ATTEMPT below, will return unknown */
    *numPorts = 0;
    *thisPort = 0;        

    /* first check base type of device, get reported rev and port info */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,3,0xD00D,&temp));
    baseType = ((temp & 0xFC00)>>6);
    reportedHwRev = (temp & 0x000F);
    numports = ((temp & 0x0380)>>7)+1;
    thisport = ((temp & 0x0070)>>4);

    /* find out if device has macsec/ptp, copper unit or is an E20X0-type device */
    if (MTD_IS_X32X0_BASE(baseType) || MTD_IS_X33X0_BASE(baseType))
    {
        ATTEMPT(mtdCheckDeviceCapabilities(devPtr,port,&hasMacsec,&hasCopper,&isE20X0Device));
    }
    else if (MTD_IS_E21X0_BASE(baseType))
    {
        hasCopper = MTD_TRUE;        
    }    

    /* check if internal processor firmware is up and running, and if so, easier to get info */    
    if (mtdGetFirmwareVersion(devPtr,port,&major,&minor,&inc,&test) == MTD_FAIL)
    {
        major = minor = inc = test = 0; /* this is expected if firmware is not loaded/running */
    }

    if (major == 0 && minor == 0 && inc == 0 && test == 0)
    {
        /* no firmware running, have to verify device revision */
        if (MTD_IS_X32X0_BASE(baseType))
        {
            /* A0 and Z2 report the same revision, need to check which is which */
            if (reportedHwRev == 1)
            {
                /* need to figure out if it's A0 or Z2 */
                /* remove internal reset */
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,3,0xD801,5,1,1));
    
                /* wait until it's ready */
                regReady = MTD_FALSE;
                tryCounter = 0;
                while(regReady == MTD_FALSE && tryCounter++ < 10)
                {
                    ATTEMPT(mtdWait(devPtr,1)); /* timeout is set to 10 ms */
                    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,3,0xD007,6,1,&readyBit));
                    if (readyBit == 1)
                    {
                        regReady = MTD_TRUE;
                    }
                }
    
                if (regReady == MTD_FALSE)
                {
                    /* timed out, can't tell for sure what rev this is */
                    *numPorts = 0;
                    *thisPort = 0;
                    *phyRev = MTD_REV_UNKNOWN;
                    return MTD_FAIL;
                }
    
                /* perform test */
                registerExists = MTD_FALSE;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,3,0x8EC6,&temp));
                ATTEMPT(mtdHwXmdioWrite(devPtr,port,3,0x8EC6,0xA5A5));
                ATTEMPT(mtdHwXmdioRead(devPtr,port,3,0x8EC6,&temp2));
    
                /* put back internal reset */
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,3,0xD801,5,1,0));
    
                if (temp == 0 && temp2 == 0xA5A5)
                {
                    registerExists = MTD_TRUE;
                }                            
    
                if (registerExists == MTD_TRUE)
                {
                    revision = 2; /* this is actually QA0 */
                }
                else
                {
                    revision = reportedHwRev; /* this is a QZ2 */
                }
                
            }
            else
            {
                /* it's not A0 or Z2, use what's reported by the hardware */
                revision = reportedHwRev;
            }
        }
        else if (MTD_IS_X33X0_BASE(baseType) || MTD_IS_E21X0_BASE(baseType))
        {        
            /* all 33X0 and 21X0 devices report correct revision */
            revision = reportedHwRev;
        }
        else
        {
            /* should not come here, all devices should belong to one of the categories above */
            *numPorts = 0;
            *thisPort = 0;
            *phyRev = MTD_REV_UNKNOWN;
            return MTD_FAIL;            
        }

        /* have to use what's reported by the hardware */
        *numPorts = (MTD_U8)numports;
        *thisPort = (MTD_U8)thisport;

        if (MTD_IS_E21X0_BASE(baseType) && (numports == 8))
        {
            /* E2180 part, port numbers need to be remapped */
            /* reported port numbers don't match MDIO port mapping */
            /* 0,1 are ok */
            if (thisport >= 4)
            {
                *thisPort = (MTD_U8)(thisport - 2); /* 4,5,6,7 -> 2,3,4,5 */
            }
            else if (thisport >= 2) /* 2,3 -> 6,7 */
            {
                *thisPort = (MTD_U8)(thisport + 4);
            }
        }
    }
    else
    {
        /* there is firmware loaded/running in internal processor */
        /* can get device revision reported by firmware */
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PHY_REV_INFO_REG,&temp));
        ATTEMPT(mtdHwGetRegFieldFromWord(temp,0,4,&revision));      
        ATTEMPT(mtdHwGetRegFieldFromWord(temp,4,3,&fwNumports));
        ATTEMPT(mtdHwGetRegFieldFromWord(temp,7,3,&fwThisport));

        if (MTD_IS_E21X0_BASE(baseType) && (fwNumports == 0))
        {
            /* On E2180, because bit field is 3 bits wide in MTD_TUNIT_PHY_REV_INFO_REG, 0->8 for number of ports */
            fwNumports = 8;

            /* E2180 part, port numbers need to be remapped */
            /* reported port numbers in hardware don't match MDIO port mapping */
            /* 0,1 are ok */
            if (thisport >= 4)
            {
                thisport = thisport - 2; /* 4,5,6,7 -> 2,3,4,5 */
            }
            else if (thisport >= 2) /* 2,3 -> 6,7 */
            {
                thisport = thisport + 4;
            }
        }
        
        if (fwNumports == numports && fwThisport == thisport)
        {
            *numPorts = (MTD_U8)numports;
            *thisPort = (MTD_U8)thisport; /* for E2180, remapping is done in firmware, so both should match after hardware remapping */
        }
        else
        {
            *phyRev = MTD_REV_UNKNOWN;
            *numPorts = 0;
            *thisPort = 0;            
            return MTD_FAIL; /* firmware and hardware are reporting different values */
        }
    }

    /* now have correct information to build up the MTD_DEVICE_ID */
    if (MTD_IS_X32X0_BASE(baseType))
    {
        temp =  MTD_X32X0_BASE;
    }
    else if (MTD_IS_X33X0_BASE(baseType))
    {
        temp = MTD_X33X0_BASE;        
    }
    else if (MTD_IS_E21X0_BASE(baseType))
    {
        temp = MTD_E21X0_BASE;
    }
    else
    {
        *phyRev = MTD_REV_UNKNOWN;
        *numPorts = 0;
        *thisPort = 0;        
        return MTD_FAIL;
    }

    if (hasMacsec)
    {
        temp |= MTD_MACSEC_CAPABLE;        
    }

    if (hasCopper)
    {
        temp |= MTD_COPPER_CAPABLE;
    }

    if (MTD_IS_X33X0_BASE(baseType) && isE20X0Device)
    {
        temp |= MTD_E20X0_DEVICE;
    }

    temp |= (revision & 0xF);

    *phyRev = (MTD_DEVICE_ID)temp;

    /* make sure we got a good one */
    if (mtdIsPhyRevisionValid(*phyRev) == MTD_OK)
    {
        return MTD_OK;
    }
    else
    {
        return MTD_FAIL; /* unknown or unsupported, if recognized but unsupported, value is still valid */
    }

    /* should never get to here */
    *phyRev = MTD_REV_UNKNOWN;
    *numPorts = 0;
    *thisPort = 0;
    return MTD_FAIL; 
}


MTD_STATUS mtdGetTunitBISTStatus
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *bistStatus
)
{
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_BIST_STATUS_REG,bistStatus));    

    return MTD_OK;
}

MTD_STATUS mtdGetTunitFirmwareMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *tunitMode,
    OUT MTD_U16 *tunitState
)
{
    MTD_U16 temp;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_XG_EXT_STATUS,&temp));
    ATTEMPT(mtdHwGetRegFieldFromWord(temp,8,4,tunitMode));
    ATTEMPT(mtdHwGetRegFieldFromWord(temp,0,8,tunitState));
    
    return MTD_OK;
}


/* defines for 1.0.5:2 for 88X33x0/E20x0/E21x0 devices for speed selection */
#define SPEED_10G_1_0   (0)
#define SPEED_5G_1_0    (7)
#define SPEED_2P5G_1_0  (6)

MTD_STATUS mtdSetPMATestModes
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 speed,
    IN MTD_U16 testMode, 
    IN MTD_U16 testFrequency
)
{
    MTD_U16 freqTemp, forcedSpeed;
    MTD_BOOL isForced;

    ATTEMPT(mtdGetForcedSpeed(devPtr,port,&isForced,&forcedSpeed));

    if (isForced == MTD_TRUE)
    {
        return MTD_FAIL; /* speed bits in 1.0 cannot be set to 100M/10M to select these test modes */
    }

    /* sets speed bits 1.0.5:2 for 88X33x0/E20x0/E21x0 devices */
    switch (speed)
    {
        case MTD_SPEED_1GIG_HD:
            /* do nothing here */
            break; 

        case MTD_SPEED_2P5GIG_FD:
        case MTD_SPEED_5GIG_FD:
            if (MTD_IS_X32X0_BASE(devPtr->deviceId))
            {
                return MTD_FAIL; /* specified 5G/2.5G speed for a 32X0 device */
            }
            /* falls through on purpose */
        case MTD_SPEED_10GIG_FD:
            if (testMode == MTD_PMA_TESTMODE_OFF || speed == MTD_SPEED_10GIG_FD)
            {
                /* set 1.0 speed bits back to 10G */
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_10G_1_0));
            }
            else if (speed == MTD_SPEED_2P5GIG_FD)
            {
                /* set 1.0 speed bits to 2.5G */
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_2P5G_1_0));                
            }
            else
            {
                /* set 1.0 speed bits to 5G */
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_5G_1_0));                
            }                           
            break;

        default:
            return MTD_FAIL;
            break;
    }

    if (speed == MTD_SPEED_1GIG_HD)
    {
        testMode >>= 13; /* top 3 bits is 0-4 */

        if (testMode > 4)
        {
            return MTD_FAIL; /* other values are not allowed */
        }

        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,7,0x8000,13,3,testMode)); /* 0 = OFF, 1-4 selects test modes 1-4 */        
    }
    else
    {
        /* speed is 10G or (5G/2.5G on 88X33x0/E20x0/E21x0) */

        /* check within range */
        if (testMode & 0x1FFF)
        {
            return MTD_FAIL;
        }        
        
        if (testMode == MTD_PMA_TESTMODE_4)
        {
            freqTemp = ((testFrequency>>10)&7); /* get bits 12:10 */

            if (freqTemp == 0 || freqTemp == 3 || freqTemp == 7)
            {
                return MTD_FAIL; /* an invalid frequency was selected */
            }
            else
            {
                /* one of the good frequencies was selected */
                testMode |= (freqTemp << 10); /* with bits 12:10 */
                ATTEMPT(mtdHwXmdioWrite(devPtr,port,1,132,testMode));
            }
        }
        else /* it's off or one of the test modes besides 4 */
        {
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,1,132,testMode));
        }

    }

    return MTD_OK;
}


MTD_STATUS mtdGetPMATestMode
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *speed,
    OUT MTD_U16 *testMode,
    OUT MTD_U16 *testFrequency
)
{
    MTD_U16 valRead;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,132,&valRead));
    *testMode = valRead & 0xE000;
    *testFrequency = valRead & 0x1C00;
    *speed = MTD_ADV_NONE;

    if (*testMode == MTD_PMA_TESTMODE_OFF)
    {
        /* there's no 10G test mode on, check for 1G test mode on */
        ATTEMPT(mtdHwGetPhyRegField(devPtr,port,7,0x8000,13,3,&valRead));

        if (valRead != MTD_PMA_TESTMODE_OFF)
        {
            *testMode = valRead<<13;
            *speed = MTD_SPEED_1GIG_FD;
            *testFrequency = MTD_NO_FREQ;
        }
    }
    else
    {
        /* check if it's a 10G test mode or a 5G/2.5G */
        if (MTD_IS_X33X0_BASE(devPtr->deviceId) || MTD_IS_E21X0_BASE(devPtr->deviceId))
        {
            /* check speed bits in 1.0 */
            ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,&valRead));

            switch(valRead)
            {
                case SPEED_10G_1_0:
                    *speed = MTD_SPEED_10GIG_FD;
                    break;

                case SPEED_2P5G_1_0:
                    *speed = MTD_SPEED_2P5GIG_FD;
                    break;

                case SPEED_5G_1_0:
                    *speed = MTD_SPEED_5GIG_FD;
                    break;

                default:
                    return MTD_FAIL;
                    break;
            }
            
        }
        else
        {
            *speed = MTD_SPEED_10GIG_FD; /* for X32X0, must be a 10G test mode */
        }
    }

    return MTD_OK;
}


MTD_STATUS mtdGet10GBTSNROperatingMargin
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_S16 snr_4chan[]
)
{
    MTD_U16 readVal;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,133,&readVal));
    snr_4chan[0] = readVal ^ 0x8000; /* Channel  A, converted to 2's complement */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,134,&readVal));
    snr_4chan[1] = readVal ^ 0x8000; /* Channel  B, converted to 2's complement */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,135,&readVal));
    snr_4chan[2] = readVal ^ 0x8000; /* Channel  C, converted to 2's complement */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,136,&readVal));
    snr_4chan[3] = readVal ^ 0x8000; /* Channel  D, converted to 2's complement */
    
    return MTD_OK;
}


MTD_STATUS mtdGet10GBTSNRMinimumMargin
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_S16 snr_4chan[]
)
{
    MTD_U16 readVal;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,137,&readVal));
    snr_4chan[0] = readVal ^ 0x8000; /* Channel  A, converted to 2's complement */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,138,&readVal));
    snr_4chan[1] = readVal ^ 0x8000; /* Channel  B, converted to 2's complement */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,139,&readVal));
    snr_4chan[2] = readVal ^ 0x8000; /* Channel  C, converted to 2's complement */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,140,&readVal));
    snr_4chan[3] = readVal ^ 0x8000; /* Channel  D, converted to 2's complement */
    
    return MTD_OK;
}



/********************************Cable Diagnostics ****************************/

MTD_STATUS mtdRun_CableDiagnostics
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    IN MTD_BOOL breakLink,
    IN MTD_BOOL disableInterPairShort
)
{
    MTD_U16 regVal;
    
    /* check if test is already running */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,0xC00D,&regVal));

    if ((regVal & (1<<15)) && (regVal & (1<<11)))
    {
        return MTD_FAIL; /* test is running */
    }

    /* test isn't running, write the request */
    regVal = (1<<15);
    if (disableInterPairShort)
    {
        regVal |= (1<<13);
    }
    if (breakLink)
    {
        regVal |= (1<<12);
    }

    ATTEMPT(mtdHwXmdioWrite(devPtr,port,1,0xC00D,regVal));    
    
    return MTD_OK;
}

MTD_STATUS mtdGet_CableDiagnostics_Status
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *testDone
)
{
    MTD_U16 regVal;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,0xC00D,&regVal));

    if (regVal & (1<<11))
    {
        *testDone = MTD_FALSE;
    }
    else
    {
        *testDone = MTD_TRUE;
    }

    return MTD_OK;
}

MTD_STATUS mtdGet_CableDiagnostics_Results
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port, 
    MTD_U8 terminationCode[],
    MTD_U8 length[]
)
{
    MTD_U16 regVal,i,mask,regVal2;
    
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,0xC00D,&regVal));    
    
    if (regVal & (1<<11))
    {
        return MTD_FAIL; /* run, but not finished */
    }

    /* finished, so get results */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,0xC00E,&regVal));

    for(i=0,mask=0x000F; i<4; i++)
    {
        terminationCode[i] = (MTD_U8)((regVal & mask)>>(4*i));
        mask <<= 4;
    }

    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,0xC00F,&regVal));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,0xC010,&regVal2));
    for(i=0,mask=0x00FF; i<2; i++)
    {
        length[i] = (MTD_U8)((regVal & mask)>>(8*i));
        length[i+2] = (MTD_U8)((regVal2 & mask)>>(8*i)); 
        mask <<= 8;
    }

    /* return PHY to normal operating mode */
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,1,0xC00D,0));        
    
    return MTD_OK;
}


/********************* Echo Tests ***********************************/
MTD_STATUS mtdStart10GEchoTest
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)
{    
    return (mtdStartEchoTest(devPtr,port,MTD_SPEED_10GIG_FD));
}

MTD_STATUS mtdIs10GEchoTestDone
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *testDone
)
{
    return (mtdIsEchoTestDone(devPtr,port,testDone));   
}

MTD_STATUS mtdGet10GEchoTestResults
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 results[]
)
{
    return (mtdGetEchoTestResults(devPtr,port,results));
}

MTD_STATUS mtdStartEchoTest
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 speed
)
{
    MTD_U16 regVal1, regVal2;

    /* qualify speed parameter and set speed selection */
    switch (speed)
    {
        case MTD_SPEED_2P5GIG_FD:
        case MTD_SPEED_5GIG_FD:
            if (MTD_IS_X32X0_BASE(devPtr->deviceId))
            {
                return MTD_FAIL; /* specified 5G/2.5G speed for a 32X0 device */
            }
            /* falls through on purpose */
        case MTD_SPEED_10GIG_FD:
            if (speed == MTD_SPEED_10GIG_FD)
            {
                if (MTD_IS_X33X0_BASE(devPtr->deviceId) && !MTD_IS_E20X0_DEVICE(devPtr->deviceId) && !MTD_IS_E21X0_BASE(devPtr->deviceId))
                {
                    /* set 1.0 speed bits to 10G */
                    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_10G_1_0));
                }
                else
                {
                    if (MTD_IS_E20X0_DEVICE(devPtr->deviceId) || MTD_IS_E21X0_BASE(devPtr->deviceId))
                    {
                        return MTD_FAIL; /* specified 10G speed for devices that don't have it */
                    }
                }
                /* do nothing on X32X0, which have only 10G, no need to change speed bits */
            }
            else if (speed == MTD_SPEED_2P5GIG_FD)
            {
                /* set 1.0 speed bits to 2.5G */
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_2P5G_1_0));                
            }
            else
            {
                /* set 1.0 speed bits to 5G */
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_5G_1_0));                
            }                           
            break;

        default:
            return MTD_FAIL; /* bad speed parameter */
            break;
    }
        
    /* check if a test was already requested and is still in progress */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,0xC00B,&regVal1));
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,0xC00C,&regVal2));

    if ((regVal1 & (1<<2)) &&
        (!(regVal2 & (1<<14))))
    {
        return MTD_FAIL; /* test requested and in progress still, can't request another */
    }

    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,1,0xC00B,2,1,1));    
    
    return MTD_OK;
}

MTD_STATUS mtdIsEchoTestDone
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *testDone
)
{
    MTD_U16 regVal;
    
    /* check if test was even requested, and if not return MTD_FAIL */
    ATTEMPT(mtdHwXmdioRead(devPtr,port,1,0xC00B,&regVal));

    if (!(regVal & (1<<2)))
    {
        return MTD_FAIL;
    }

    ATTEMPT(mtdGetTunitBISTStatus(devPtr,port,&regVal));
    
    if (regVal & MTD_BIST_ECHO_TEST_DONE)
    {
        *testDone = MTD_TRUE;
    }
    else
    {
        *testDone = MTD_FALSE;
    }

    return MTD_OK;    
}

MTD_STATUS mtdGetEchoTestResults
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 results[]
)
{
    MTD_BOOL done;
    MTD_U16 i;
    
    /* make sure it was requested and is done */
    ATTEMPT(mtdIs10GEchoTestDone(devPtr,port,&done));

    if (!done)
    {
        return MTD_FAIL;
    }

    /* read the results */
    for (i=0xC013; i < 0xC027; i++)
    {
        ATTEMPT(mtdHwXmdioRead(devPtr,port,1,i,&results[i-0xC013]));
    }

    if (MTD_IS_X33X0_BASE(devPtr->deviceId))
    {
        /* set 1.0 speed bits back to 10G */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_10G_1_0)); 
    }

    /* take it out of the echo test mode */
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,1,0xC00B,2,1,0));

    return MTD_OK;
}



MTD_STATUS mtdGetAmbientNoise
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 noiseResults[]
)
{
    MTD_BOOL testDone = MTD_FALSE;
    MTD_U16 results[20],i,speed_bits;
    
    /* force off transmitter */
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,1,9,0,1,1));

    ATTEMPT(mtdGetSpeedsAvailable(devPtr,port,&speed_bits));
    if (speed_bits & MTD_SPEED_10GIG_FD)
    {
        ATTEMPT(mtdStartEchoTest(devPtr,port,MTD_SPEED_10GIG_FD));
    }
    else if (speed_bits & MTD_SPEED_5GIG_FD)
    {
        ATTEMPT(mtdStartEchoTest(devPtr,port,MTD_SPEED_5GIG_FD));
    }
    else if (speed_bits & MTD_SPEED_2P5GIG_FD)
    {
        ATTEMPT(mtdStartEchoTest(devPtr,port,MTD_SPEED_2P5GIG_FD));
    }
    else
    {
        return MTD_FAIL;
    }

    while(testDone == MTD_FALSE)
    {
        ATTEMPT(mtdIs10GEchoTestDone(devPtr,port,&testDone));
        ATTEMPT(mtdWait(devPtr,500)); /* better not to poll constantly */
    }

    /* read results and return PHY to normal operation */
    ATTEMPT(mtdGetEchoTestResults(devPtr,port,results));
    for(i=0; i < 4; i++)
    {
        noiseResults[i] = results[i+16];
    }    
    
    /* allow transmitter to be turned back on */
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,1,9,0,1,0));
    
    return MTD_OK;
}

/***** BER COUNTER *****/
MTD_STATUS mtdReadBERCount
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *count
)
{
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,3,33,8,6,count));

    return MTD_OK;
}

MTD_STATUS mtdIsLPInfoValid
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *validFlag
)
{
    MTD_U16 regVal;
    
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,1,129,0,1,&regVal));

    if (regVal)
    {
        *validFlag = MTD_TRUE;
    }
    else
    {
        *validFlag = MTD_FALSE;
    }
    
    return MTD_OK;
}

/***** PBO - NEAR END and FAR END *****/
MTD_STATUS mtdReadNearEndPBO
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *pboValue
)
{
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,1,131,10,3,pboValue));
    
    return MTD_OK;
}

MTD_STATUS mtdReadFarEndPBO
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *pboValue
)
{
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,1,131,13,3,pboValue));
    
    return MTD_OK;
}



MTD_STATUS mtdGetSerdesEyeStatistics
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 curSelLane,
    OUT MTD_U32 eyeDataUp[][MTD_EYEDIAGRAM_NCOLS],
    OUT MTD_U32 eyeDataDn[][MTD_EYEDIAGRAM_NCOLS],
    OUT MTD_U16 *eyeArea,
    OUT MTD_U16 *eyeWidth,
    OUT MTD_U16 *eyeHeight
)
{
    MTD_U16 DFEdata = 0; //reg for calculate h0
    MTD_U16 reg_8xBE = 0; //register value for center phase location

    MTD_U16 regComm_00 = 0, regLane_00 = 0;
    MTD_U16 tmp, tmpAddr;
    MTD_U16 spdSet, cnt;
    MTD_U16 eyeXmax, eyeXmin, eyeZmax, eyeZmin;
    MTD_U16 i, j;

#if 0 // uncomment this if we need to plot eye diagram
    MTD_U16 n, idx=0;
    MTD_U32 raw_topHalf_2eye[(MTD_EYEDIAGRAM_NROWS + 1) / 2][MTD_EYEDIAGRAM_NCOLS] = {0};
    MTD_U32 raw_bottomHalf_2eye[(MTD_EYEDIAGRAM_NROWS + 1) / 2][MTD_EYEDIAGRAM_NCOLS] = {0};
    MTD_U32 measEye[MTD_EYEDIAGRAM_NQ] = {0}, pMyXData[MTD_EYEDIAGRAM_NQ] = {0}, pMyYData[MTD_EYEDIAGRAM_NQ] = {0}, pMyZData[MTD_EYEDIAGRAM_NQ] = {0} ;
#endif

    *eyeArea = *eyeWidth = *eyeHeight = 0;

    tmpAddr = 0x8000 + curSelLane*MTD_XFI_LANEOFFSET;

    //track register 0x80BE, best VEO location
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0xBE, &tmp));
    reg_8xBE = tmp & 0x7f;

    //calculate h0
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x84,&tmp));
    DFEdata = ((tmp & 0x7F00) >> 8); //[14:8]

    //0. read reg $V.$CL00.1:0($CL=90)and $V.$PL00.3:0($PL=80)
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,0x9000,&tmp));
    regComm_00 = tmp & 0x3; //get last 2 bits
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x00,&tmp));
    regLane_00 = tmp & 0xF; //get last 4 bits
    if (regLane_00 > 10) //0xA
    {
        //out << "\nOP_Freq[3:0] is > 0xA; not in the table range, measurement aborted.";
        return MTD_FAIL;
    }

    //set reg$PL15.11:4
    //eye monitor speed  setting 0: $V.$PL15.11:4 = 0x0;
    //eye monitor speed  setting 1: $V.$PL15.11:4 = 0x1;
    //eye monitor speed  setting 2: $V.$PL15.11:4 = 0x16;
    //eye monitor speed  setting 3: $V.$PL15.11:4 = 0x27;
    spdSet = 0; //spdSet = Comm_Lane_freq[regComm_00, regLane_00];
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x15,&tmp));
    //speed set
    if (spdSet == 0)
    {
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x15,((tmp & 0xF00F) | 0x0)));
    }
    else if (spdSet == 1)
    {
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x15,((tmp & 0xF00F) | 0x0)));
    }
    else if (spdSet == 2)
    {
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x15,((tmp & 0xF00F) | 0x150)));
    }
    else if (spdSet == 3)
    {
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x15,((tmp & 0xF00F) | 0x260)));
    }

    //!!! need set phase to zero
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,&tmp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,(tmp & 0xFFC0)));


    //1. enable eye monitor
    //addr: phy, dev, reg
    //$V.$PL10.15 = 0x1
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x10,&tmp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x10,(tmp | 0x8000)));
    mtdWait(devPtr,1000);
    cnt = 0;
    while (1)
    {
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x10,&tmp));
        if ((tmp & 0x8000) == 0x8000)
            break;
        mtdWait(devPtr,1000);
        cnt++;
        if (cnt > 4)
        {
            //out << "\nEM enable failed. Measurement aborted.";
            //out << "\nPlease check if the selected lane is up.\n";
            return MTD_FAIL;;
        }
    }
    //2. write sample count for calibration
    //Valid setting is 10 to 29
    //5'd10 = 1024 matched samples for each pattern
    //...
    //5'd20 = 1 million matched samples for each pattern
    //...
    //$V.$PL10.13:9 = 0x14 (20 in decimal) - 5bit used for the # of samples
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x10,&tmp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x10,((tmp & 0xC1FF) | 0x2800)));
    //3. write eye amplitude $V.$PL11.10:6 = 0x19
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,&tmp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,((tmp & 0xF83F) | 0x0640)));
    //X3240 no calibration for now



    //-------------------- eye monitor measure -----------------------
    //1. set compare sample number
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x10,&tmp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x10,((tmp & 0xC1FF) | (MTD_EYE_SAMPLE_NUM << 9))));

    //2. first write top half $V.$PL11.11 = 0x1
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,&tmp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,(tmp & 0x8000)));
    //top half --- loop on amplitude & phase, and measure the eye
    //Measure top half of the first eye and bottom half of the 2nd eye
    //assume first eye is even, second is odd
    ATTEMPT(mtdDoMeasHalfEye(devPtr,port, curSelLane, reg_8xBE, eyeDataUp));

    //3. write bottom half $V.$PL11.11 = 0x0
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,&tmp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,(tmp & 0xF7FF)));
    //bottom half
    //Measure bottom half of the first eye and top half of the 2nd eye
    ATTEMPT(mtdDoMeasHalfEye(devPtr,port, curSelLane, reg_8xBE, eyeDataDn));

    //4. write back eye amplitude $V.$PL11.10:6 = 0x19
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,&tmp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x11,((tmp & 0xF83F) | 0x640)));

    //5. disable eye monitor $V.$PL10.15 = 0x0
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_XFI_DSP,tmpAddr+0x10,&tmp));
    ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_XFI_DSP,tmpAddr+0x10,(tmp & 0x7FFF)));

    //6. post processing of eye data to get eye statistics
    (*eyeArea) = 0;
    eyeXmin = MTD_EYEDIAGRAM_NCOLS/2; // for eye width
    eyeXmax = 0;
    eyeZmin = MTD_EYEDIAGRAM_NROWS; // for eye height
    eyeZmax = 0;
    for (i = 0; i < (MTD_EYEDIAGRAM_NROWS + 1) / 2; i++) // through all amplitudes 0-25
    {
        for (j = 0; j < 64; j++)  // through 64 phases (first eye)
        {
            if (eyeDataUp[i][j] == 0)
            {
                if (j < eyeXmin)
                {
                    eyeXmin = j;
                }
                else if (j > eyeXmax)
                {
                    eyeXmax = j;
                }
                if (i < eyeZmin)
                {
                    eyeZmin = i;
                }
                else if (i > eyeZmax)
                {
                    eyeZmax = i;
                }
                (*eyeArea)++;
            }
            if ((eyeDataDn[i][j] == 0) && (i < (MTD_EYEDIAGRAM_NROWS-1)/2))
            {
                if (j < eyeXmin)
                {
                    eyeXmin = j;
                }
                else if (j > eyeXmax)
                {
                    eyeXmax = j;
                }
                tmp = (MTD_EYEDIAGRAM_NROWS-1)-i;
                if (tmp < eyeZmin)
                {
                    eyeZmin = tmp;
                }
                else if (tmp > eyeZmax)
                {
                    eyeZmax = tmp;
                }
                (*eyeArea)++;
            }

        }
        for (j = 0; j < 64; j++)  // through 64 phases (second eye)
        {
            if (eyeDataDn[i][j+64] == 0)
            {
                (*eyeArea)++;
            }
            if ((eyeDataUp[i][j+64] == 0) && (i < (MTD_EYEDIAGRAM_NROWS-1)/2))
            {
                (*eyeArea)++;
            }
        }
    }

    if (*eyeArea > 0)
    {
        *eyeWidth = eyeXmax - eyeXmin;
        *eyeHeight = ((eyeZmax - eyeZmin)*((DFEdata*250/64)-249))/32;
    }

#if 0 //uncomment this part to get x/y/z values for eye diagram plot
    // prepare for eye diagram plot
    for (i = 0; i < (MTD_EYEDIAGRAM_NROWS + 1) / 2; i++) // through all amplitudes 0-25
    {
        for (j = 0; j < 64; j++)  // through 64 phases (first eye)
        {
            raw_topHalf_2eye[i][j] = eyeDataUp[i][j];
            raw_bottomHalf_2eye[i][j] = eyeDataDn[i][j];
        }
        for (j = 0; j < 64; j++)  // through 64 phases (second eye)
        {
            raw_topHalf_2eye[i][j + 64] = eyeDataDn[i][j + 64];
            raw_bottomHalf_2eye[i][j + 64] = eyeDataUp[i][j + 64];
        }
    }
    for (i = 0; i < (MTD_EYEDIAGRAM_NROWS + 1) / 2; i++)
    {
        for (j = 0; j < MTD_EYEDIAGRAM_NCOLS; j++)
        {
            measEye[idx] = raw_topHalf_2eye[i][j];
            idx++;
        }
    }
    for (i = 1; i < (MTD_EYEDIAGRAM_NROWS + 1) / 2; i++)
    {
        for (j = 0; j < MTD_EYEDIAGRAM_NCOLS; j++)
        {
            measEye[idx] = raw_bottomHalf_2eye[(MTD_EYEDIAGRAM_NROWS-1)/2-i][j];
            idx++;
        }
    }
    (*eyeArea) = 0;
    eyeXmin = MTD_EYEDIAGRAM_NCOLS/2;
    eyeXmax = 0;
    eyeZmin = MTD_EYEDIAGRAM_NROWS;
    eyeZmax = 0;
    for (i = 0; i < MTD_EYEDIAGRAM_NROWS; i++)
    {
        for (j = 0; j < MTD_EYEDIAGRAM_NCOLS; j++)
        {
            n = (i * MTD_EYEDIAGRAM_NCOLS) + j;
            pMyXData[n] = j;
            pMyZData[n] = i;
            pMyYData[n] = measEye[n];
            if (measEye[n] == 0)
            {
                if (j < MTD_EYEDIAGRAM_NCOLS/2) // for eyeWidth
                {
                    if (j < eyeXmin)
                    {
                        eyeXmin = j;
                    }
                    else if (j > eyeXmax)
                    {
                        eyeXmax = j;
                    }
                }
                if (i < eyeZmin)
                {
                    eyeZmin = i;
                }
                else if (i > eyeZmax)
                {
                    eyeZmax = i;
                }
                (*eyeArea)++;
            }
        }
    }
    *eyeWidth = eyeXmax - eyeXmin;
    *eyeHeight = ((eyeZmax - eyeZmin - ((MTD_EYEDIAGRAM_NROWS-1)/2))*(DFEdata*250/64-249))/32;
#endif

    return MTD_OK;
}


MTD_STATUS mtdSerdesEyePlotChart
(
    IN MTD_DEV_PTR pDev,
    IN MTD_U32 raw_topHalf_2eye[][MTD_EYEDIAGRAM_NCOLS], 
    IN MTD_U32 raw_bottomHalf_2eye[][MTD_EYEDIAGRAM_NCOLS]
)
{
    MTD_STATUS status = MTD_OK;
    MTD_32  i, j;
    MTD_U16 eyeTimeline, eyeMidTimeline;
    MTD_U8 point;
    static double float_topHalf_2eye[(MTD_EYEDIAGRAM_NROWS + 1) / 2][MTD_EYEDIAGRAM_NCOLS];  
    static double float_bottomHalf_2eye[(MTD_EYEDIAGRAM_NROWS + 1) / 2][MTD_EYEDIAGRAM_NCOLS];

    /* Clear buffers */
    for (i = 0; i < ((MTD_EYEDIAGRAM_NROWS + 1) / 2); i++) 
    {
        for (j = 0; j < MTD_EYEDIAGRAM_NCOLS; j++)  
        {
            float_topHalf_2eye[i][j] = 0.0;
            float_bottomHalf_2eye[i][j] = 0.0;
        }
    }

    for (i = 0; i < ((MTD_EYEDIAGRAM_NROWS + 1) / 2); i++) // through all amplitudes
    {
        for (j = 0; j < MTD_EYEDIAGRAM_NCOLS; j++)  // through 64 phases (64 columns) * 2
        {
            float_topHalf_2eye[25 - i][j] = 1.0*raw_topHalf_2eye[25 - i][j];
            float_topHalf_2eye[25 - i][j] = float_topHalf_2eye[25 - i][j] / (1 << MTD_EYE_SAMPLE_NUM);
        }
    }

    for (i = 1; i < ((MTD_EYEDIAGRAM_NROWS + 1) / 2); i++) // through all amplitudes
    {
        for (j = 0; j < MTD_EYEDIAGRAM_NCOLS; j++)  // through 64 phases (64 columns) * 2
        {
            float_bottomHalf_2eye[25 - i][j] = 1.0*raw_bottomHalf_2eye[25 - i][j];
            float_bottomHalf_2eye[25 - i][j] = float_bottomHalf_2eye[25 - i][j] / (1 << MTD_EYE_SAMPLE_NUM);
        }
    }
    
    eyeTimeline = MTD_EYEDIAGRAM_NCOLS;  
    eyeMidTimeline = MTD_EYEDIAGRAM_NCOLS/4; 

    for (i = 0; i < ((MTD_EYEDIAGRAM_NROWS + 1) / 2); i++) // through all amplitudes 
    {
        for (j = 0; j < eyeTimeline; j++)  // through 64 phases(64 columns) * 2
        {
            point = (MTD_U8)(float_topHalf_2eye[i][j]*10);
            if (j == eyeTimeline-1) 
            {
                MTD_DBG_INFO("\n"); 
            }

            if (float_topHalf_2eye[i][j] == 0)
            {
                if ((j == (MTD_EYEDIAGRAM_NCOLS/4)-1) || j == ((MTD_EYEDIAGRAM_NCOLS/4)*3))
                {
                    MTD_DBG_INFO("|");
                }
                else
                {
                    if (i+1 == ((MTD_EYEDIAGRAM_NROWS + 1) / 2))
                    {
                        MTD_DBG_INFO("_");
                    }
                    else 
                        MTD_DBG_INFO(" ");
                }
            }
            else
            {
                MTD_DBG_INFO("%x", point);
            }
        }
    }

    for (i = 1; i < ((MTD_EYEDIAGRAM_NROWS + 1) / 2); i++) // through all amplitudes
    {
        for (j = 0; j < eyeTimeline; j++)  // through 64 phases (64 columns) * 2
        {
            point = (MTD_U8)(float_bottomHalf_2eye[25 - i][j]*10);
            if (j == eyeTimeline-1) 
            {
                MTD_DBG_INFO("\n"); 
            }

            if (float_bottomHalf_2eye[25 - i][j] == 0)
            {
               if ((j == (MTD_EYEDIAGRAM_NCOLS/4)-1) || j == ((MTD_EYEDIAGRAM_NCOLS/4)*3))
                {
                    MTD_DBG_INFO("|");
                }
                else
                {
                    MTD_DBG_INFO(" ");
                }
            }
            else
            {
                MTD_DBG_INFO("%x", point);
            }
        }
    }

    return status;
}


MTD_STATUS mtdTunitConfigurePktGeneratorChecker
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  speed,
    IN MTD_BOOL readToClear,
    IN MTD_U16  pktPatternControl,
    IN MTD_BOOL generateCRCoff,
    IN MTD_U32  initialPayload,
    IN MTD_U16  frameLengthControl,
    IN MTD_U16  numPktsToSend,
    IN MTD_BOOL randomIPG,
    IN MTD_U16  ipgDuration,
    IN MTD_BOOL clearInitCounters
)
{
    if (pktPatternControl > MTD_PKT_RANDOM_WORD || pktPatternControl == 1)
    {
        MTD_DBG_ERROR("mtdTunitConfigurePktGeneratorChecker: incorrect pktPatternControl: %u\n", pktPatternControl);
        return MTD_FAIL;
    }

    if (frameLengthControl == 6 || frameLengthControl == 7)
    {
        MTD_DBG_ERROR("mtdTunitConfigurePktGeneratorChecker: incorrect frameLengthControl: %u\n", frameLengthControl);
        return MTD_FAIL;
    }
    
    if ((speed == MTD_SPEED_MISMATCH) || (speed == MTD_ADV_NONE))
    {
        MTD_DBG_ERROR("mtdTunitConfigurePktGeneratorChecker: incorrect speed: %u\n", speed);
        return MTD_FAIL;
    }

    if ((speed == MTD_SPEED_10GIG_FD) || (speed == MTD_SPEED_2P5GIG_FD) || (speed == MTD_SPEED_5GIG_FD))
    {
        if (clearInitCounters)
        {
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTGEN_BURST,0));
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,0x0103));
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,0x0163));
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,0x0103));
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,0x0100));

            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,0x0103));
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,0x010B));
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,0x0103));
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,0x0100));
        }

        /* default generator/checker mux control */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_TEST_CTRL,3,3, (MTD_PACKETGEN_TO_LINE|MTD_CHECKER_FROM_LINE)));
        /* Disable Packet Generator */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,0,2,0x0));  
        /* Disable Packet Ckecker */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,0,2,0x0)); 

        /* Generator counters ReadToClear */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,4,1,MTD_GET_BOOL_AS_BIT(readToClear)));  
        /* Ckecker counters ReadToClear   */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,2,1,MTD_GET_BOOL_AS_BIT(readToClear)));  
 
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL1,4,4,pktPatternControl));
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL1,3,1,MTD_GET_BOOL_AS_BIT(generateCRCoff)));
        /* load up initial payload */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTGEN_INIT0,(MTD_U16)initialPayload));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTGEN_INIT1,(MTD_U16)(initialPayload>>16)));

        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTGEN_LENGTH,frameLengthControl));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_10G_PKTGEN_BURST,numPktsToSend));

        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_IPG,15,1,MTD_GET_BOOL_AS_BIT(randomIPG)));
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_IPG,0,15,ipgDuration));
    }
    else
    {
        if (clearInitCounters)
        {
            /* clear both generator and checker counters */
            ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_PKTGEN_BURST,0));
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PKTGEN_CTRL,1,2,0x3));
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PKTGEN_CTRL,0,1,1));
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PKTGEN_CTRL,1,2,0));
        }

        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PKTGEN_CTRL,4,4,pktPatternControl));
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PKTGEN_CTRL,3,1,MTD_GET_BOOL_AS_BIT(generateCRCoff)));
        /* load up initial payload */
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_PKTGEN_INIT0,(MTD_U16)initialPayload));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_PKTGEN_INIT1,(MTD_U16)(initialPayload>>16)));

        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_PKTGEN_LENGTH,frameLengthControl));
        ATTEMPT(mtdHwXmdioWrite(devPtr,port,MTD_TUNIT_PKTGEN_BURST,numPktsToSend));

        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PKTGEN_IPG,15,1,MTD_GET_BOOL_AS_BIT(randomIPG)));
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PKTGEN_IPG,0,15,ipgDuration));
    }

    return MTD_OK;
}

MTD_STATUS mtdTunit10GPktGenMuxSelect
(
     IN MTD_DEV_PTR devPtr,
     IN MTD_U16  port,
     IN MTD_U16  generatorControl,
     IN MTD_U16  checkerControl
)
{
     /* generator/checker mux control */
     ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_TEST_CTRL,3,3,(generatorControl|checkerControl)));

     return MTD_OK;
}

MTD_STATUS mtdTunitEnablePktGeneratorChecker
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 speed,
    IN MTD_BOOL enableGenerator,
    IN MTD_BOOL enableChecker
)
{
    MTD_U16 temp=0;

    if ((speed == MTD_SPEED_MISMATCH) || (speed == MTD_ADV_NONE))
    {
        MTD_DBG_ERROR("mtdTunitEnablePktGeneratorChecker: incorrect speed: %u\n", speed);
        return MTD_FAIL;
    }
    
    if ((speed == MTD_SPEED_10GIG_FD) || (speed == MTD_SPEED_2P5GIG_FD) || (speed == MTD_SPEED_5GIG_FD))
    {
        if (enableGenerator)
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,0,2,0x3));
        }
        else
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,0,2,0x0));
        }

        if (enableChecker)
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,0,2,0x3));
        }
        else
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,0,2,0x0));
        }
    }
    else
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_TEST_CTRL,3,3,(MTD_PACKETGEN_TO_LINE|MTD_CHECKER_FROM_LINE)));

        temp = ((MTD_GET_BOOL_AS_BIT(enableGenerator))<<1) | (MTD_GET_BOOL_AS_BIT(enableChecker));  
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PKTGEN_CTRL,1,2,temp));
    }

    return MTD_OK;
}

MTD_STATUS mtdTunitPktGeneratorCounterReset
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 speed
)
{
    MTD_U16 temp,temp1;

    if ((speed == MTD_SPEED_MISMATCH) || (speed == MTD_ADV_NONE))
    {
        MTD_DBG_ERROR("mtdTunitPktGeneratorCounterReset: incorrect speed: %u\n", speed);
        return MTD_FAIL;
    }
     
    if ((speed == MTD_SPEED_10GIG_FD) || (speed == MTD_SPEED_2P5GIG_FD) || (speed == MTD_SPEED_5GIG_FD))
    {
        /* save Read Clear Mode */
        ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,4,1,&temp));
        ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,2,1,&temp1));

        /* Clear genertor counters */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,4,3,0x6));
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,4,3,0x0));
        /* clear checker counters */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,2,2,0x2));
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,2,2,0x0));
        /* restore Read Clear Mode */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTGEN_CTRL,4,1,temp));
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_10G_PKTCHK_CNTL,2,1,temp1));
    }
    else
    {
        /* clear both generator and checker counters */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PKTGEN_CTRL,0,1,1));
    }

    return MTD_OK;
}

MTD_STATUS mtdTunitPktGeneratorGetCounter
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  speed,
    IN MTD_U16  whichCounter,
    OUT MTD_U64 *packetCount,
    OUT MTD_U64 *byteCount    
)
{
    MTD_U16 temp;
    
    *packetCount = *byteCount = 0;

    if ((speed == MTD_SPEED_MISMATCH) || (speed == MTD_ADV_NONE))
    {
        MTD_DBG_ERROR("mtdTunitPktGeneratorGetCounter: incorrect speed: %u\n", speed);
        return MTD_FAIL;
    }
     
    if ((speed == MTD_SPEED_10GIG_FD) || (speed == MTD_SPEED_2P5GIG_FD) || (speed == MTD_SPEED_5GIG_FD))
    {    
        switch (whichCounter)
        {
            case MTD_PKT_GET_TX:
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_TXPKTCTR1,&temp));
                *packetCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_TXPKTCTR2,&temp));
                *packetCount |= (((MTD_U64)(temp))<<16);
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_TXPKTCTR3,&temp));
                *packetCount |= (((MTD_U64)(temp))<<32);

                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_TXBYTCTR1,&temp));
                *byteCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_TXBYTCTR2,&temp));
                *byteCount |= (((MTD_U64)(temp))<<16);
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_TXBYTCTR1,&temp));
                *byteCount |= (((MTD_U64)(temp))<<32);            
                break;

            case MTD_PKT_GET_RX:
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_RXPKTCTR1,&temp));
                *packetCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_RXPKTCTR2,&temp));
                *packetCount |= (((MTD_U64)(temp))<<16);
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_RXPKTCTR3,&temp));
                *packetCount |= (((MTD_U64)(temp))<<32);

                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_RXBYTCTR1,&temp));
                *byteCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_RXBYTCTR2,&temp));
                *byteCount |= (((MTD_U64)(temp))<<16);
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_RXBYTCTR3,&temp));
                *byteCount |= (((MTD_U64)(temp))<<32);            
                break;

            case MTD_PKT_GET_ERR:
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_ERRCTR1,&temp));
                *packetCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_ERRCTR2,&temp));
                *packetCount |= (((MTD_U64)(temp))<<16);
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_10G_PKTGEN_ERRCTR3,&temp));
                *packetCount |= (((MTD_U64)(temp))<<32);            
                break;

            default:
                MTD_DBG_ERROR("mtdTunitPktGeneratorGetCounter: incorrect counter type:%u for >= 2.5G\n", whichCounter);
                return MTD_FAIL;
                break;            
        }
    }
    else
    {
        switch (whichCounter)
        {
            case MTD_PKT_GET_TX:
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_TXPKTCTR1,&temp));
                *packetCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_TXPKTCTR2,&temp));
                *packetCount |= (((MTD_U64)(temp))<<16);

                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_TXBYTCTR1,&temp));
                *byteCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_TXBYTCTR2,&temp));
                *byteCount |= (((MTD_U64)(temp))<<16);
                break;

            case MTD_PKT_GET_RX:
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_RXPKTCTR1,&temp));
                *packetCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_RXPKTCTR2,&temp));
                *packetCount |= (((MTD_U64)(temp))<<16);

                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_RXBYTCTR1,&temp));
                *byteCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_RXBYTCTR2,&temp));
                *byteCount |= (((MTD_U64)(temp))<<16);
                break;

            case MTD_PKT_GET_ERR:
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_ERRCTR1,&temp));
                *packetCount = temp;
                ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_PKTGEN_ERRCTR2,&temp));
                *packetCount |= (((MTD_U64)(temp))<<16);
                break;

            default:
                MTD_DBG_ERROR("mtdTunitPktGeneratorGetCounter: incorrect counter type: %u\n", whichCounter);
                return MTD_FAIL;
                break;            
        }
    }
    
    return MTD_OK;
}

MTD_STATUS mtdTunitConfigure10GLinkDropCounter
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_BOOL readToClear,
    IN MTD_BOOL rollOver,
    IN MTD_BOOL enable
)
{
    MTD_U16 temp;
    /* Link Drop counters readToClear */
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_LINK_DROP_CTRL,2,1,MTD_GET_BOOL_AS_BIT(readToClear))); 
    /* Link Drop counters rollOver */
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_LINK_DROP_CTRL,1,1,MTD_GET_BOOL_AS_BIT(rollOver))); 
    /* Link Drop counters enable */
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_LINK_DROP_CTRL,0,1,MTD_GET_BOOL_AS_BIT(enable)));
    /* clear link drop counter */
    if (readToClear)
    {
        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_LINK_DROP_CTR,&temp));
    }
    else
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_LINK_DROP_CTRL,3,1,1));
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_LINK_DROP_CTRL,3,1,0));
    }
    return MTD_OK;
}

MTD_STATUS mtdTunit10GGetLinkDropCounter
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_BOOL counterReset,
    OUT MTD_U16 *linkDropCounter        
)
{
    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_TUNIT_LINK_DROP_CTR,linkDropCounter));

    if (counterReset)
    {
        /* clear link drop counters */
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_LINK_DROP_CTRL,3,1,1));
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_LINK_DROP_CTRL,3,1,0));
    }
   
    return MTD_OK;
}

MTD_STATUS mtdSetTunitDeepMacLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  speed,
    IN MTD_BOOL enable
)
{
    MTD_U16 speedsAbility;
    
    if (!MTD_IS_X32X0_BASE(devPtr->deviceId))
    {
        if (enable == MTD_TRUE)
        {
            if (speed == MTD_SPEED_10GIG_FD)
            {
                ATTEMPT(mtdGetSpeedsAvailable(devPtr,port,&speedsAbility));
                
                if (speedsAbility & MTD_SPEED_10GIG_FD)
                {
                    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_10G_1_0));
                }
                else
                {
                    /* handles E20X0/E21X0 case */
                    MTD_DBG_ERROR("mtdSetTunitDeepMacLoopback: Unsupported speed!\n");
                    return MTD_FAIL;
                }
            }
            else if (speed == MTD_SPEED_5GIG_FD)
            {
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_5G_1_0));
            }
            else if (speed == MTD_SPEED_2P5GIG_FD)
            {
                ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_2P5G_1_0));
            }
        }
        else
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PMA_CTRL1,2,4,SPEED_10G_1_0));
        }
    }

    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PCS_CTRL1,14,1,(MTD_U16)enable));
 
    return MTD_OK;
}

MTD_STATUS mtdSetTunitShallowLineLoopback
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16  port,
    IN MTD_U16  loopbackSpeed,
    IN MTD_BOOL enable
)
{
    MTD_U16 speeds,status=MTD_OK;
    MTD_BOOL linkup;

    ATTEMPT(mtdIsBaseTUp(devPtr,port,&speeds,&linkup));

    if (linkup == MTD_TRUE)
    {
        if (speeds & (MTD_SPEED_10GIG_FD|MTD_SPEED_5GIG_FD|MTD_SPEED_2P5GIG_FD))
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_PHY_EXT_CTRL_1,11,1,(MTD_U16)enable));           
            if (loopbackSpeed != MTD_2P5G_ABOVE_LB_SPEED)
            {
                status = MTD_FAIL;
            }
        }
        else
        {
            ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_TUNIT_COPPER_SPEC_CTRL3,5,1,(MTD_U16)enable));
            if (loopbackSpeed == MTD_2P5G_ABOVE_LB_SPEED)
            {
                status = MTD_FAIL;
            }
        }
    }
    else
    {
        MTD_DBG_ERROR("mtdSetTunitShallowLineLoopback: Link down!\n");
        return MTD_FAIL;
    }

    return status;
}

MTD_STATUS mtdGetLoopbackSetting
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16     port,
    OUT MTD_LOOPBACKS_STATUS_STRUCT *loopbackStatus
)
{
    MTD_U16 regVal,temp;

    mtdMemSet(loopbackStatus, 0, sizeof(MTD_LOOPBACKS_STATUS_STRUCT));

    /* T-unit Deep MAC Loopback */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_TUNIT_IEEE_PCS_CTRL1,14,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, loopbackStatus->tunitMacLoopback);

    /* T-unit Shallow Line loopback, Speed 10G,5G,2.5G */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_TUNIT_PHY_EXT_CTRL_1,11,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, loopbackStatus->tunitLineLoopback2P5GAbove);

    /* T-unit Shallow Line loopback, Speed 1000M,100M,10M */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_TUNIT_COPPER_SPEC_CTRL3,5,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, loopbackStatus->tunitLineLoopback1GBelow);

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_H_UNIT,MTD_SERDES_CONTROL1,&regVal));

    /* H-unit Shallow MAC Loopback */
    ATTEMPT(mtdHwGetRegFieldFromWord(regVal,12,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, loopbackStatus->hunitMacLoopback);

    /* H-unit Deep Line Pass through */
    ATTEMPT(mtdHwGetRegFieldFromWord(regVal,6,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(!temp, loopbackStatus->hunitLinePassThrough);

    /* H-unit Deep Line Loopback */
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_H_UNIT,MTD_10GBR_PCS_CONTROL,14,1,&temp));
    MTD_CONVERT_UINT_TO_BOOL(temp, loopbackStatus->hunitLineLoopback);

    if (MTD_HAS_X_UNIT(devPtr))
    {
        /* X-unit Deep MAC Loopback */
        ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_10GBR_PCS_CONTROL,14,1,&temp));
        MTD_CONVERT_UINT_TO_BOOL(temp, loopbackStatus->xunitMacLoopback);

        ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_X_UNIT,MTD_SERDES_CONTROL1,&regVal));

        /* X-unit Deep MAC Pass Through */
        ATTEMPT(mtdHwGetRegFieldFromWord(regVal,6,1,&temp));
        MTD_CONVERT_UINT_TO_BOOL(!temp, loopbackStatus->xunitMacPassThrough);

        /* X-unit Shallow Line Loopback */
        ATTEMPT(mtdHwGetRegFieldFromWord(regVal,12,1,&temp));
        MTD_CONVERT_UINT_TO_BOOL(temp, loopbackStatus->xunitLineLoopback);
    }

    return MTD_OK;
}

MTD_STATUS mtdGetTempSensorMDIOPort
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_U16 *sensorPort
)
{
    MTD_U16 deviceId, numPorts, basePort, portOffset;

    if (devPtr->numPorts == 0)
    {
        MTD_DBG_ERROR("mtdGetTempSensorMDIOPort: numPorts cannot be 0\n");
        return MTD_FAIL;
    }

    numPorts = devPtr->numPorts;
    deviceId = devPtr->deviceId;
    basePort = (port/numPorts) * numPorts;   
    portOffset = port - basePort;  /* take the relative port number from MDIO port */

    if (MTD_IS_E21X0_BASE(deviceId))
    {
        if (numPorts == 1) /* E2110 */
        {
            *sensorPort = basePort;
        }
        else if (numPorts == 4) /* E2140 */
        {
            *sensorPort = basePort + 1;
        }
        else /* E2180 */
        {
            if ((portOffset >=2) && (portOffset <=5))
            {
                *sensorPort = basePort + 3; /* 2nd DIE */
            }
            else
            {
                *sensorPort = basePort + 1; /* 1st DIE */
            }
        }
    }
    else if (MTD_IS_X32X0_BASE(deviceId))
    {
        if (numPorts == 2) /* X3220 */
        {
            *sensorPort = basePort + 1;
        }
        else /* X3240 */
        {
            *sensorPort = basePort + 3;
        }
    }
    else if (MTD_IS_X33X0_BASE(deviceId)) /* X33X0, E20X0 */
    {
        *sensorPort = port;
    }
    else
    {
        MTD_DBG_ERROR("mtdGetTempSensorMDIOPort: Device is not supported.\n");
        return MTD_FAIL;
    }

    return MTD_OK;
}

MTD_STATUS mtdEnableTemperatureSensor
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)
{
    MTD_U16 sensorPort;
    MTD_U16 e21x0SensorSetting;

    if (MTD_IS_E21X0_BASE(devPtr->deviceId))
    {
        /* some early firmware was not configuring it, check if it's configured */
        /* if not, configure it. if it's already configured, leave it alone */

        if (mtdGetTempSensorMDIOPort(devPtr, port, &sensorPort) == MTD_FAIL)
        {
            MTD_DBG_ERROR("mtdGetTempSensorMDIOPort() failed.\n");
            return MTD_FAIL;
        }

        /* Check if the sensor is configured for average mode over the period/samples in 3.8042 */ 
        ATTEMPT(mtdHwGetPhyRegField(devPtr,sensorPort,MTD_TUNIT_TEMP_SENSOR2,14,2,&e21x0SensorSetting));

        if (e21x0SensorSetting != 0x01)
        {
            /* firmware did not configure it, it's old firmware, so configure it */
            /* note: on older firmware, a T unit soft reset will clear the setting and it will have to be */
            /* re-enabled */
            if (mtdHwSetPhyRegField(devPtr,sensorPort,MTD_TUNIT_TEMP_SENSOR2,8,8,0x45) != MTD_OK)
            {
                MTD_DBG_ERROR("Enable Tunit temperature sensor failed.\n");
                return MTD_FAIL;
            }            
        } /* else it's already configured by firmware, leave it alone */
                    
        return MTD_OK; 
    }

    if (MTD_IS_X32X0_BASE(devPtr->deviceId) || MTD_IS_X33X0_BASE(devPtr->deviceId))
    {
        if (mtdGetTempSensorMDIOPort(devPtr, port, &sensorPort) == MTD_FAIL)
        {
            MTD_DBG_ERROR("mtdGetTempSensorMDIOPort() Failed.\n");
            return MTD_FAIL;
        }
       
        /* Enable Cunit temperature sensor to use 2^11 samples at a period of 2.2ms */
        if (mtdHwSetPhyRegField(devPtr,sensorPort,MTD_CUNIT_TEMP_SENSOR_CTRL_STAT,8,8,0x45) != MTD_OK)
        {
            MTD_DBG_ERROR("Enable Cunit temperature sensor failed.\n");
            return MTD_FAIL;
        }
    }
    else
    {
        MTD_DBG_ERROR("mtdEnableTemperatureSensor: device not supported.\n");
        return MTD_FAIL;
    }

    return MTD_OK;
}

MTD_STATUS mtdReadTemperature
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16   port,
    OUT MTD_S16 *temperature
)
{
    MTD_U16 sensorPort, temp;

    if (mtdGetTempSensorMDIOPort(devPtr, port, &sensorPort) == MTD_FAIL)
    {
        MTD_DBG_ERROR("mtdGetTempSensorMDIOPort() Failed.\n");
        return MTD_FAIL;
    }    

    if (MTD_IS_E21X0_BASE(devPtr->deviceId))
    {
        ATTEMPT(mtdHwXmdioRead(devPtr,sensorPort,MTD_TUNIT_TEMP_SENSOR2,&temp)); /* need to read the average temperature */
    }
    else if (MTD_IS_X32X0_BASE(devPtr->deviceId) || MTD_IS_X33X0_BASE(devPtr->deviceId))
    {
        ATTEMPT(mtdHwXmdioRead(devPtr,sensorPort,MTD_CUNIT_TEMP_SENSOR_CTRL_STAT,&temp)); /* need to read the average temperature */
    }
    else
    {
        MTD_DBG_ERROR("mtdReadTemperature: Device is not supported.\n");
        return MTD_FAIL;
    }

    *temperature = ((MTD_S16)(temp & 0xFF)) - 75;

    return MTD_OK;
}

MTD_STATUS mtdCunitSwResetLeaveCopperLinkUp
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port
)
{
    
    /* Keep copper link up during software reset d*/
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF045,0,5,0x1F));
    
    ATTEMPT(mtdCunitSwReset(devPtr,port));

    ATTEMPT(mtdWait(devPtr,100)); /* allow it to complete */
    
    /*Set 31.F045 back to default */
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,31,0xF045,0,5,0x0F));

    return MTD_OK;
}

