/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains common utility functions use across the Marvell
X7120/X6181/X6141 PHYs API driver (MYD).
********************************************************************/
#ifndef MYD_UTILS_H
#define MYD_UTILS_H

#ifdef MYD_DEBUG
#include "stdio.h"
#include "stdarg.h"
#endif
                                   
#if C_LINKAGE
#if defined __cplusplus
    extern "C" {
#endif
#endif

#ifdef MYD_DEBUG
typedef enum 
{
    MYD_DBG_OFF_LVL,
    MYD_DBG_ERR_LVL,
    MYD_DBG_INF_LVL,
    MYD_DBG_ALL_LVL
} MYD_DBG_LEVEL;

/*******************************************************************************
 void mydDbgPrint
 (
     FILE *stream, 
     MYD_DBG_LEVEL debug_level, 
     char* format, 
     ...
 );

 Inputs:
       debug_level - allows control of how much is printed
               MYD_DBG_OFF_LVL  - prints nothing
               MYD_DBG_ERR_LVL - for error messages
               MYD_DBG_ALL_LVL - for informational messages

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
       Set global myd_debug_level to MYD_DBG_OFF_LVL to turn off all printing, or
       MYD_DBG_ERR_LVL to print only errors, or MYD_DBG_ALL_LVL for both errors
       and informational messages. This can be done during run time or
       the global default can be changed at compile time to change the
       run-time behavior.

       Undefined MYD_DEBUG to remove all printing code (may need some modifications
       on some compilers).

*******************************************************************************/
void mydDbgPrint
(
    FILE *stream, 
    MYD_DBG_LEVEL debug_level, 
    char* format, 
    ...
);

#define MYD_DBG_ERROR(...)       mydDbgPrint(stderr, MYD_DBG_ERR_LVL, __VA_ARGS__) /* macro for error messages */
#define MYD_DBG_INFO(...)        mydDbgPrint(stdout, MYD_DBG_ALL_LVL, __VA_ARGS__) /* macro for informational messages */
#define MYD_DBG_CRITIC_INFO(...) mydDbgPrint(stdout, MYD_DBG_INF_LVL, __VA_ARGS__) /* macro for informational messages */

extern MYD_DBG_LEVEL myd_debug_level;

#else /* MYD_DEBUG not defined */

#define MYD_DBG_ERROR(...)
#define MYD_DBG_INFO(...)
#define MYD_DBG_CRITIC_INFO(...)

#endif



/*******************************************************************************
 MYD_PVOID mydMemSet
 (
     IN MYD_PVOID start,
     IN MYD_16   symbol,
     IN MYD_U32 size
 );

 Inputs:
       start  - start address of memory block for setting
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
MYD_PVOID mydMemSet
(
    IN MYD_PVOID start,
    IN MYD_16   symbol,
    IN MYD_U32 size
);


/*******************************************************************************
 MYD_PVOID mydMemCpy
 (
     IN MYD_PVOID pDestination,
     IN const MYD_PVOID pSource,
     IN MYD_U32 size
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
MYD_PVOID mydMemCpy
(
    IN MYD_PVOID pDestination,
    IN const MYD_PVOID pSource,
    IN MYD_U32 size
);

/*******************************************************************************
 mydStrlen

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
MYD_U32 mydStrlen
(
    IN const MYD_PVOID pSource
);


#if C_LINKAGE
#if defined __cplusplus
}
#endif
#endif

#endif /* defined MYD_UTILS_H */

