/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains functions for initializing the driver and setting 
up the user-provide MDIO access functions for the Marvell 88X32X0, 
88X33X0, 88E20X0 and 88E21X0 ethernet PHYs.
********************************************************************/
#ifndef MTDINITIALIZATION_H
#define MTDINITIALIZATION_H

#if C_LINKAGE
#ifdef __cplusplus
extern "C" {
#endif
#endif

/*******************************************************************************
  mtdLoadDriver

  DESCRIPTION:
        Marvell 88X32X0, 88X33X0, 88E20X0 and 88E21X0 Driver Initialization Routine. 
        This is the first routine that needs be called by system software. 
        It takes parameters from system software, and retures a pointer (*dev) 
        to a data structure which includes infomation related to this Marvell Phy
        device. This pointer (*dev) is then used for all the API functions. 
        The following is the job performed by this routine:
            1. store MDIO read/write function into the given MTD_DEV structure
            2. run any device specific initialization routine
            3. create semaphore if required
            4. Initialize the deviceId
            

  INPUTS:
    readMdio - pointer to host's function to do MDIO read
    writeMdio - point to host's function to do MDIO write
    macsecIndirectAccess - MTD_TRUE to access MacSec through T-unit processor
                           MTD_FALSE to do direct register access
                           This parameter is don't care for any non-MacSec
                           devices, pass either one. It's not used if
                           no MacSec functions are called.
    semCreate - pointer to host's function to create a semaphore, NULL
                if not used
    semDelete - pointer to host's function to create a semaphore, NULL
                if not used    
    semTake - pointer to host's function to take a semaphore, NULL
              if not used    
    semGive - pointer to host's function to give a semaphore, NULL
              if not used
    anyPort - port address of any port for this device 

  OUTPUTS:
        dev  - pointer to holds device information to be used for each API call.

  RETURNS:
        MTD_OK               - on success
        MTD_FAIL             - on error

  COMMENTS:
        mtdUnloadDriver is also provided to do driver cleanup.

        An MTD_DEV is required for each type of PHY device in the system. For
        example, if there are 16 ports of X3240 and 4 ports of X3220, 
        two MTD_DEV are required, and one call to mtdLoadDriver() must
        be made with one of the X3240 ports, and one with one of the X3220
        ports.

        Host may either pass pointers to ther MDIO read/write functions here
        for run-time calling of their MDIO read/write, or for a compile-time
        solution, programmers may modify mtdHwXmdioRead() and mtdHwXmdioWrite()
        in mtdHwCntl.c directly to call their functions and pass NULL here.

        Depending on MTD_CLAUSE_22_MDIO compile switch, readMdio() and
        writeMdio() prototypes are different.
*******************************************************************************/
MTD_STATUS mtdLoadDriver
(
    IN FMTD_READ_MDIO     readMdio,    
    IN FMTD_WRITE_MDIO    writeMdio,   
    IN MTD_BOOL           macsecIndirectAccess, 
    IN FMTD_SEM_CREATE    semCreate,     
    IN FMTD_SEM_DELETE    semDelete,    
    IN FMTD_SEM_TAKE      semTake,    
    IN FMTD_SEM_GIVE      semGive,
    IN MTD_U16            anyPort,
    OUT MTD_DEV           *dev
);

/*******************************************************************************
* mtdUnloadDriver
*
* DESCRIPTION:
*       This function frees semaphore created by Marvell X2*** Driver,
*       disables Device interrupt, and clears MTD_DEV structure.
*
* INPUTS:
*       None.
*
* OUTPUTS:
*       None.
*
* RETURNS:
*       MTD_OK           - on success
*       MTD_FAIL         - on error
*
* COMMENTS:
*       1.  This function should be called only after successful execution of
*           mtdLoadDriver().
*
*******************************************************************************/
MTD_STATUS mtdUnloadDriver
(
    IN MTD_DEV* dev
);

#if C_LINKAGE
#ifdef __cplusplus
}
#endif
#endif

#endif /* MTDINITIALIZATION_H */




