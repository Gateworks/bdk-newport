/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains collection of utility functions for the 
Marvell X7120/X6181/X6141 Device.
********************************************************************/

#include "mydApiTypes.h"
#include "mydUtils.h"
#include "mydHwCntl.h"

#ifdef MYD_DEBUG 
#include "stdarg.h"
#include "stdio.h"

MYD_DBG_LEVEL myd_debug_level = MYD_DBG_ALL_LVL; /* Set default debug level */

/*******************************************************************************
* mydDbgPrint
*
* DESCRIPTION:
*       .
*
* INPUTS:
*       debug_level - allows control of how much is printed
*               MYD_DBG_OFF_LVL  - prints nothing
*               MYD_DBG_ERR_LVL - for error messages
*               MYD_DBG_ALL_LVL - for informational messages
*
* OUTPUTS:
*       None
*
* RETURNS:
*       None
*
* COMMENTS:
*       Set global myd_debug_level to MYD_DBG_OFF_LVL to turn off all printing, or
*       MYD_DBG_ERR_LVL to print only errors, or MYD_DBG_ALL_LVL for both errors
*       and informational messages. This can be done during run time or
*       the global default can be changed at compile time to change the
*       run-time behavior.
*
*       Undefined MYD_DEBUG to remove all printing code (may need some modifications
*       on some compilers).
*
*******************************************************************************/
MYD_VOID mydDbgPrint(FILE *stream, MYD_DBG_LEVEL debug_level, char* format, ...)
{
    va_list argP;
    MYD_8 dbgStr[MYD_DBG_BUFSIZE] = ""; 
    MYD_U32 size;

    if (debug_level)
    {
        if (debug_level <= myd_debug_level)
        {
            va_start(argP, format);

            size = mydStrlen(format);
            if (size > MYD_DBG_BUFSIZE)
            {
                MYD_DBG_ERROR("mydDbgPrint: **ERROR** - log size larger than buffer. Increase MYD_DBG_BUFSIZE size > %u\n", 
                               size);
                va_end(argP);
                return;
            }

            vsprintf(dbgStr, format, argP);

#ifdef MYD_PY_DEBUG
            tstApiDbgWrite(dbgStr);
#else
            fprintf(stream, dbgStr);
#endif

#ifdef MYD_SDEBUG
            MYD_DBG_MPRINT(dbgStr);
#endif
            va_end(argP);
        }
    }
}
#else 

/* All printing code removed */

#endif /* DEBUG_MYD */


/*******************************************************************************
* mydMemSet
*
* DESCRIPTION:
*       Set a block of memory
*
* INPUTS:
*       start  - start address of memory block for setting
*       symbol - character to store, converted to an unsigned char
*       size   - size of block to be set
*
* OUTPUTS:
*       None
*
* RETURNS:
*       Pointer to set memory block
*
* COMMENTS:
*       None
*
*******************************************************************************/
MYD_PVOID mydMemSet
(
    IN MYD_PVOID start,
    IN MYD_16   symbol,
    IN MYD_U32 size
)
{
    MYD_U32 i;
    MYD_8* buf;
    
    buf = (MYD_8*)start;
        
    for(i=0; i<size; i++)
    {
        *buf++ = (MYD_8)symbol;
    }

    return start;
}

/*******************************************************************************
* mydMemCpy
*
* DESCRIPTION:
*       Copies 'size' characters from the object pointed to by 'source' into
*       the object pointed to by 'destination'. If copying takes place between
*       objects that overlap, the behavior is undefined.
*
* INPUTS:
*       destination - destination of copy
*       source      - source of copy
*       size        - size of memory to copy
*
* OUTPUTS:
*       None
*
* RETURNS:
*       Pointer to destination
*
* COMMENTS:
*       None
*
*******************************************************************************/
MYD_PVOID mydMemCpy
(
    IN MYD_PVOID pDestination,
    IN const MYD_PVOID pSource,
    IN MYD_U32 size
)
{
    MYD_U32 i;
    MYD_8* buf;
    MYD_8* src;
    
    buf = (MYD_8*)pDestination;
    src = (MYD_8*)pSource;
        
    for(i=0; i<size; i++)
    {
        *buf++ = *src++;
    }

    return pDestination;
}

/*******************************************************************************
* mydMemCmp
*
* DESCRIPTION:
*       Compares given memories.
*
* INPUTS:
*       src1 - source 1
*       src2 - source 2
*       size - size of memory to copy
*
* OUTPUTS:
*       None
*
* RETURNS:
*       0, if equal.
*        negative number, if src1 < src2.
*        positive number, if src1 > src2.
*
* COMMENTS:
*       None
*
*******************************************************************************/
MYD_16 mydMemCmp
(
    IN MYD_8 src1[],
    IN MYD_8 src2[],
    IN MYD_U32 size
)
{
    MYD_U32 i;
    MYD_16 value;

    for(i=0; i<size; i++)
    {
        if((value = (MYD_16)(src1[i] - src2[i])) != 0)
        {
            return value; 
        }
    }

    return 0;
}

/*******************************************************************************
* mydStrlen
*
* DESCRIPTION:
*       Determine the length of a string
* INPUTS:
*       source  - string
*
* OUTPUTS:
*       None
*
* RETURNS:
*       size    - number of characters in string, not including EOS.
*
* COMMENTS:
*       None
*
*******************************************************************************/
MYD_U32 mydStrlen
(
    IN const MYD_PVOID pSource
)
{
    MYD_U32 i = 0;
    MYD_8* src;
    
    src = (MYD_8*)pSource;
        
    while(*src++) i++;

    return i;
}



