/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions and global data defines/data for
higher-level functions to call Host's semaphore functions that
were initialized with mtdLoadDriver().
********************************************************************/
#include "mtdApiTypes.h"
#include "mtdSemaphore.h"

/*******************************************************************************
* mtdSemCreate
*
* DESCRIPTION:
*       Create semaphore.
*
* INPUTS:
*        state - beginning state of the semaphore, either MTD_SEM_EMPTY or MTD_SEM_FULL
*
* OUTPUTS:
*       None
*
* RETURNS:
*       MTD_SEM if success. Otherwise, NULL
*
* COMMENTS:
*       None
*
*******************************************************************************/
MTD_SEM mtdSemCreate
(
    IN MTD_DEV    *dev,
    IN MTD_SEM_BEGIN_STATE  state
)
{
    if(dev->semCreate)
        return dev->semCreate(state);

    return 1; /* should return any value other than 0 to let it keep going */
}

/*******************************************************************************
* mtdSemDelete
*
* DESCRIPTION:
*       Delete semaphore.
*
* INPUTS:
*       smid - semaphore Id
*
* OUTPUTS:
*       None
*
* RETURNS:
*       MTD_OK   - on success
*       MTD_FAIL - on error
*
* COMMENTS:
*       None
*
*******************************************************************************/
MTD_STATUS mtdSemDelete
(
    IN MTD_DEV  *dev,
    IN MTD_SEM  smid
)
{
    if((dev->semDelete) && (smid))
        if (dev->semDelete(smid))
          return MTD_FAIL;

    return MTD_OK;
}


/*******************************************************************************
* mtdSemTake
*
* DESCRIPTION:
*       Wait for semaphore.
*
* INPUTS:
*       smid    - semaphore Id
*       timeOut - time out in miliseconds or 0 to wait forever
*
* OUTPUTS:
*       None
* RETURNS:
*       MTD_OK   - on success
*       MTD_FAIL - on error
*       OS_TIMEOUT - on time out
*
* COMMENTS:
*       None
*
*******************************************************************************/
MTD_STATUS mtdSemTake
(
    IN MTD_DEV  *dev,
    IN MTD_SEM  smid, 
    IN MTD_U32  timeOut
)
{
    if(dev->semTake)
      if (dev->semTake(smid, timeOut))
        return MTD_FAIL;

    return MTD_OK;

}

/*******************************************************************************
* mtdSemGive
*
* DESCRIPTION:
*       release the semaphore which was taken previously.
*
* INPUTS:
*       smid    - semaphore Id
*
* OUTPUTS:
*       None
*
* RETURNS:
*       MTD_OK   - on success
*       MTD_FAIL - on error
*
* COMMENTS:
*       None
*
*******************************************************************************/
MTD_STATUS mtdSemGive
(
    IN MTD_DEV    *dev,
    IN MTD_SEM    smid
)
{
    if(dev->semGive)
        if (dev->semGive(smid))
          return MTD_FAIL;

    return MTD_OK;
}

