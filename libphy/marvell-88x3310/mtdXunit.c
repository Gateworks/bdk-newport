/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data for
higher-level functions for controlling and getting status from 
the Fiber Unit (X Unit) of the Marvell 88X32X0, 88X33X0, 88E20X0 
and 88E21X0 ethernet PHYs.
********************************************************************/
#include "mtdApiTypes.h"
#include "mtdHwCntl.h"
#include "mtdAPI.h"
#include "mtdApiRegs.h"
#include "mtdXunit.h"

/******************************************************************************
 1000BX/SGMII functions
******************************************************************************/

MTD_STATUS mtdSet1000BXAutoneg_Advertisement
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    IN MTD_U16 remote_fault,
    IN MTD_U16 pause,
    IN MTD_BOOL restart_an    
)
{
    if (remote_fault > MTD_1000BX_REMOTE_FAULT_ANERR ||
        pause > MTD_SYM_ASYM_PAUSE)
    {
        return MTD_FAIL;
    }
    
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_1000X_SGMII_AN_ADV,12,2,remote_fault));
    
    ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_1000X_SGMII_AN_ADV,7,2,pause));

    if (restart_an == MTD_TRUE)
    {
        ATTEMPT(mtdHwSetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_1000X_SGMII_CONTROL,9,1,1)); /* bit self clears */
    }
    
    return MTD_OK;
}

MTD_STATUS mtdGet1000BXAutoneg_Advertisement
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_U16 *remote_fault,
    OUT MTD_U16 *pause
)
{
    
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_1000X_SGMII_AN_ADV,12,2,remote_fault));
    
    ATTEMPT(mtdHwGetPhyRegField(devPtr,port,MTD_X_UNIT,MTD_1000X_SGMII_AN_ADV,7,2,pause));

    return MTD_OK;
}

MTD_STATUS mtdGet1000BXLinkPartner_Ability
(
    IN MTD_DEV_PTR devPtr,
    IN MTD_U16 port,
    OUT MTD_BOOL *ack,
    OUT MTD_U16 *remote_fault,
    OUT MTD_U16 *pause,
    OUT MTD_BOOL *half_duplex,
    OUT MTD_BOOL *full_duplex
)
{
    MTD_U16 temp,temp2;

    ATTEMPT(mtdHwXmdioRead(devPtr,port,MTD_X_UNIT,MTD_1000X_SGMII_LP_ABL,&temp));

    ATTEMPT(mtdHwGetRegFieldFromWord(temp,14,1,&temp2));
    MTD_CONVERT_UINT_TO_BOOL(temp2,*ack);

    ATTEMPT(mtdHwGetRegFieldFromWord(temp,12,2,remote_fault));
    ATTEMPT(mtdHwGetRegFieldFromWord(temp,7,2,pause));
    
    ATTEMPT(mtdHwGetRegFieldFromWord(temp,6,1,&temp2));
    MTD_CONVERT_UINT_TO_BOOL(temp2,*half_duplex);
    
    ATTEMPT(mtdHwGetRegFieldFromWord(temp,5,1,&temp2));
    MTD_CONVERT_UINT_TO_BOOL(temp2,*full_duplex);
        
    return MTD_OK;
}



