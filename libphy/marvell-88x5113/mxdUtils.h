/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains common utility functions use across the Marvell
X5113 API driver (MXD).
********************************************************************/
#ifndef MXD_UTILS_H
#define MXD_UTILS_H

#ifdef MXD_DEBUG
#include "stdio.h"
#include "stdarg.h"
#endif
                                   
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#ifdef MXD_DEBUG

typedef enum 
{
    MXD_DBG_OFF_LVL,
    MXD_DBG_ERR_LVL,
    MXD_DBG_INF_LVL,
    MXD_DBG_ALL_LVL
} MXD_DBG_LEVEL;

/*******************************************************************************
 void mxdDbgPrint
 (
     FILE *stream, 
     MXD_DBG_LEVEL debug_level, 
     char* format, 
     ...
 );

 Inputs:
       debug_level - allows control of how much is printed
               MXD_DBG_OFF_LVL  - prints nothing
               MXD_DBG_ERR_LVL - for error messages
               MXD_DBG_ALL_LVL - for informational messages

 Outputs:
       None

 Returns:
       None

 Description:
       This function tests for the debug message level and prints out the 
       string with the given arguments.  

 Side effects:
    None

 Notes/Warnings:
       Set global mxd_debug_level to MXD_DBG_OFF_LVL to turn off all printing, or
       MXD_DBG_ERR_LVL to print only errors, or MXD_DBG_ALL_LVL for both errors
       and informational messages. This can be done during run time or
       the global default can be changed at compile time to change the
       run-time behavior.

       Undefine MXD_DEBUG to remove all printing code (may need some modifications
       on some compilers).

*******************************************************************************/
void mxdDbgPrint
(
    FILE *stream, 
    MXD_DBG_LEVEL debug_level, 
    char* format, 
    ...
);

#define MXD_DBG_ERROR(...)       mxdDbgPrint(stderr, MXD_DBG_ERR_LVL, __VA_ARGS__) /* macro for error messages */
#define MXD_DBG_INFO(...)        mxdDbgPrint(stdout, MXD_DBG_ALL_LVL, __VA_ARGS__) /* macro for informational messages */
#define MXD_DBG_CRITIC_INFO(...) mxdDbgPrint(stdout, MXD_DBG_INF_LVL, __VA_ARGS__) /* macro for informational messages */

extern MXD_DBG_LEVEL mxd_debug_level;

#else /* MXD_DEBUG not defined */

#define MXD_DBG_ERROR(...)
#define MXD_DBG_INFO(...)
#define MXD_DBG_CRITIC_INFO(...)

#endif



/*******************************************************************************
 MXD_PVOID mxdMemSet
 (
     IN MXD_PVOID pStart,
     IN MXD_16 symbol,
     IN MXD_U32 size
 );

 Inputs:
       pStart  - start address of memory block for setting
       symbol - character to store, converted to an unsigned char
       size   - size of block to be set

 Outputs:
       None

 Returns:
       Pointer to set memory block

 Description:
       Set a block of memory

 Side effects:
    None

 Notes/Warnings:
       None

*******************************************************************************/
MXD_PVOID mxdMemSet
(
    IN MXD_PVOID pStart,
    IN MXD_16 symbol,
    IN MXD_U32 size
);


/*******************************************************************************
 MXD_PVOID mxdMemCpy
 (
     IN MXD_PVOID pDestination,
     IN const MXD_PVOID pSource,
     IN MXD_U32 size
 );
 
 Inputs:
       pDestination - destination of copy
       pSource      - source of copy
       size        - size of memory to copy

 Outputs:
       None

 Returns:
       Pointer to destination

 Description:
       Copies 'size' characters from the object pointed to by 'source' into
       the object pointed to by 'destination'. If copying takes place between
       objects that overlap, the behavior is undefined.

 Side effects:
    None

 Notes/Warnings:
       None

*******************************************************************************/
MXD_PVOID mxdMemCpy
(
    IN MXD_PVOID pDestination,
    IN const MXD_PVOID pSource,
    IN MXD_U32 size
);


/*******************************************************************************
 mxdStrlen

 Description:
       Determine the length of a string
 Inputs:
       pSource  - string

 Outputs:
       None

 Returns:
       size    - number of characters in string, not including EOS.

 Side effects:
    None

 Notes/Warnings:
       None

*******************************************************************************/
MXD_U32 mxdStrlen
(
    IN const MXD_PVOID pSource
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MXD_UTILS_H */

