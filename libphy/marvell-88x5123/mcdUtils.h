/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

/********************************************************************
This file contains common utility functions use across the Marvell
X5121/X5111/X2381 API driver (MCD).
********************************************************************/
#ifndef MCD_UTILS_H
#define MCD_UTILS_H

#if DB_TEST_ENVIRONMENT
#include "stdio.h"
#include "stdarg.h"
#elif defined(MCD_DEBUG)
#include "stdio.h"
#include "stdarg.h"
#endif

#define C_LINKAGE 1 /* set to 1 if C compile/linkage on C files is desired with C++ */

#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#ifdef MCD_DEBUG

typedef enum
{
    MCD_DBG_OFF_LVL,
    MCD_DBG_ERR_LVL,
    MCD_DBG_INF_LVL,
    MCD_DBG_ALL_LVL
} MCD_DBG_LEVEL;

typedef int (*MCD_DBG_LOG) (const char *msg);


/**
* @internal mcdDebugLevelSet function
* @endinternal
*
* @brief   Set a debug level
*
* @param[in] debugLevel               - new debug level
*                                       None
*/
MCD_VOID mcdDebugLevelSet
(
    IN MCD_DBG_LEVEL debugLevel
);

/**
* @internal mcdSampleDebugLevelGet function
* @endinternal
*
* @brief   Get a debug level
*
* @param[in] None
*                                       None
*/
MCD_DBG_LEVEL mcdDebugLevelGet
(
    void
);


/*******************************************************************************
 void mcdDbgPrint
 (
     FILE *stream,
     MCD_DBG_LEVEL debug_level,
     char* format,
     ...
 );

 Inputs:
       debug_level - allows control of how much is printed
               MCD_DBG_OFF_LVL  - prints nothing
               MCD_DBG_ERR_LVL - for error messages
               MCD_DBG_ALL_LVL - for informational messages

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
       Set global mcd_debug_level to MCD_DBG_OFF_LVL to turn off all printing, or
       MCD_DBG_ERR_LVL to print only errors, or MCD_DBG_ALL_LVL for both errors
       and informational messages. This can be done during run time or
       the global default can be changed at compile time to change the
       run-time behavior.

       Undefine MCD_DEBUG to remove all printing code (may need some modifications
       on some compilers).

*******************************************************************************/
void mcdDbgPrint
(
    FILE *stream,
    MCD_DBG_LEVEL debug_level,
    char* format,
    ...
);

/*******************************************************************************
 void mcdDbgSetLoggerFn
 (
     MCD_DBG_LOG logger
 );

 Inputs:
       Should be registered from application
       MCD_DBG_LOG logger

 Outputs:
       None

 Returns:
       None

 Description:
       This function may be register by application in order to dump
       debug logs to application layer.

 Side effects:
       None

 Notes/Warnings:
       None

*******************************************************************************/
void mcdDbgSetLoggerFn
(
    MCD_DBG_LOG logger
);

#ifndef MV_HWS_REDUCED_BUILD_EXT_CM3
#define MCD_DBG_ERROR(...)       mcdDbgPrint(stderr, MCD_DBG_ERR_LVL, __VA_ARGS__) /* macro for error messages */
#define MCD_SHOW(...)            mcdDbgPrint(stderr, MCD_DBG_ERR_LVL, __VA_ARGS__) /* macro for show messages */
#define MCD_DBG_INFO(...)        mcdDbgPrint(stdout, MCD_DBG_ALL_LVL, __VA_ARGS__) /* macro for informational messages */
#define MCD_DBG_CRITIC_INFO(...) mcdDbgPrint(stdout, MCD_DBG_INF_LVL, __VA_ARGS__) /* macro for informational messages */
#else
#include <printf.h>

#define MCD_DBG_ERROR       printf
#define MCD_DBG_INFO(...)
#define MCD_DBG_CRITIC_INFO printf
#endif

extern MCD_DBG_LEVEL mcd_debug_level;

#else /* MCD_DEBUG not defined */

#define MCD_DBG_ERROR(...)
#define MCD_DBG_INFO(...) do {} while(0)
#define MCD_DBG_CRITIC_INFO(...)
#define MCD_SHOW(...) printf(__VA_ARGS__) /* macro for show messages */

#endif


#define MCD_CHECK_RET_CODE_WITH_ACTION(ptr, action) \
{ \
    if(ptr->return_code < 0) \
    { \
        MCD_DBG_INFO("%s failed (return code %d)\n", __func__,ptr->return_code); \
        mcdWrapperGetReturnCode(ptr);\
        action; \
        return MCD_FAIL; \
    } \
}

#define MCD_CHECK_RET_CODE(ptr) \
{ \
    if(ptr->return_code < 0) \
    { \
        MCD_DBG_ERROR("%s failed (return code %d)\n", __func__, ptr->return_code); \
        mcdWrapperGetReturnCode(ptr);\
        return MCD_FAIL; \
    } \
}
#define MCD_CHECK_RET_CODE1(ptr,num) \
{ \
    if(ptr->return_code < 0) \
    { \
        MCD_DBG_ERROR("%s failed (return code %d serdes %d )\n", __func__, ptr->return_code,num); \
        mcdWrapperGetReturnCode(ptr);\
        return MCD_FAIL; \
    } \
}


/**
* @internal mcdDbgPrintAllRegisters function
* @endinternal
*
* @brief   Prints all registers.
*
* @param[in] pDev                   device number
*
* @note should set debug level to MCD_DBG_ALL_LVL before calling this function in order to see the printout
*
*/
MCD_STATUS mcdDbgPrintAllRegisters(
    IN  MCD_DEV_PTR pDev
);



/*******************************************************************************
 MCD_PVOID mcdMemSet
 (
     IN MCD_PVOID pStart,
     IN MCD_16 symbol,
     IN MCD_U32 size
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
MCD_PVOID mcdMemSet
(
    IN MCD_PVOID pStart,
    IN MCD_16 symbol,
    IN MCD_U32 size
);


/*******************************************************************************
 MCD_PVOID mcdMemCpy
 (
     IN MCD_PVOID pDestination,
     IN const MCD_PVOID pSource,
     IN MCD_U32 size
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
MCD_PVOID mcdMemCpy
(
    IN MCD_PVOID pDestination,
    IN const MCD_PVOID pSource,
    IN MCD_U32 size
);


/*******************************************************************************
 mcdStrlen

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
MCD_U32 mcdStrlen
(
    IN const MCD_PVOID pSource
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MCD_UTILS_H */


