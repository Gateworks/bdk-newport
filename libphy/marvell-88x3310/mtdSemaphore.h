/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions prototypes and global defines/data for
multi-threaded support of MTD. It provides entry point for 
creating, deleting, taking, and giving semaphores. Host may implement
their own function and pass in pointers when performing mtdLoadDriver()
or change the implementation in mtdSemaphore.c and pass in pointers
to those functions when calling mtdLoadDriver().
********************************************************************/
#ifndef MTD_SEMAPHORE_H
#define MTD_SEMAPHORE_H
#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif


/***** Semaphore Definitions ***********************************/

#define OS_WAIT_FOREVER             0

#define OS_MAX_TASKS                30
#define OS_MAX_TASK_NAME_LENGTH     10

#define OS_MAX_QUEUES               30
#define OS_MAX_QUEUE_NAME_LENGTH    10

#define OS_MAX_EVENTS               10

#define OS_MAX_SEMAPHORES           50

#define OS_EOF                      (-1)

#define MTD_API_FAIL_SEM_CREATE            0x18<<24/*semCreate Failed. */
#define MTD_API_FAIL_SEM_DELETE            0x19<<24/*semDelete Failed. */

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
);

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
);


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
);

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
);

#if C_LINKAGE
#if defined __cplusplus 
}
#endif 
#endif

#endif /* defined MTD_SEMAPHORE_H */


