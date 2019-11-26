/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************************
* mxdUtils.c
*
* DESCRIPTION:
*       Collection of Utility functions
*
* DEPENDENCIES:
*       None
*
* FILE REVISION NUMBER:
*       $Revision: 1 $
*******************************************************************************/

#include "mxdApiTypes.h"
#include "mxdUtils.h"
#include "mxdHwCntl.h"

#ifdef MXD_DEBUG 
#include "stdarg.h"
#include "stdio.h"

MXD_DBG_LEVEL mxd_debug_level = MXD_DBG_ALL_LVL; /* Set default debug level */

/*******************************************************************************
* mxdDbgPrint
*
* DESCRIPTION:
*       .
*
* INPUTS:
*       debug_level - allows control of how much is printed
*               MXD_DBG_OFF_LVL  - prints nothing
*               MXD_DBG_ERR_LVL - for error messages
*               MXD_DBG_ALL_LVL - for informational messages
*
* OUTPUTS:
*       None
*
* RETURNS:
*       None
*
* COMMENTS:
*       Set global mxd_debug_level to MXD_DBG_OFF_LVL to turn off all printing, or
*       MXD_DBG_ERR_LVL to print only errors, or MXD_DBG_ALL_LVL for both errors
*       and informational messages. This can be done during run time or
*       the global default can be changed at compile time to change the
*       run-time behavior.
*
*       Undefine MXD_DEBUG to remove all printing code (may need some modifications
*       on some compilers).
*
*******************************************************************************/
MXD_VOID mxdDbgPrint(FILE *stream, MXD_DBG_LEVEL debug_level, char* format, ...)
{
    va_list argP;
    MXD_8 dbgStr[MXD_DBG_BUFSIZE] = ""; 
    MXD_U32 size;

    if (debug_level)
    {
        if (debug_level <= mxd_debug_level)
        {
            va_start(argP, format);

            size = mxdStrlen(format);
            if (size > MXD_DBG_BUFSIZE)
            {
                MXD_DBG_ERROR("mxdDbgPrint: **ERROR** - log size larger than buffer. Increase MXD_DBG_BUFSIZE size > %u\n", 
                               size);
                va_end(argP);
                return;
            }

            vsprintf(dbgStr, format, argP);

#ifdef MXD_PY_DEBUG
            tstApiDbgWrite(dbgStr);
#else
            fprintf(stream, "%s", dbgStr);
#endif

#ifdef MXD_SDEBUG
            MXD_DBG_MPRINT(dbgStr);
#endif
            va_end(argP);
        }
    }
}
#else 

/* All printing code removed */

#endif /* DEBUG_MXD */


/*******************************************************************************
* mxdMemSet
*
* DESCRIPTION:
*       Set a block of memory
*
* INPUTS:
*       start  - start address of memory block for setting
*       simbol - character to store, converted to an unsigned char
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
MXD_PVOID mxdMemSet
(
    IN MXD_PVOID start,
    IN MXD_16   symbol,
    IN MXD_U32 size
)
{
    MXD_U32 i;
    MXD_8* buf;
    
    buf = (MXD_8*)start;
        
    for(i=0; i<size; i++)
    {
        *buf++ = (MXD_8)symbol;
    }

    return start;
}

/*******************************************************************************
* mxdMemCpy
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
MXD_PVOID mxdMemCpy
(
    IN MXD_PVOID pDestination,
    IN const MXD_PVOID pSource,
    IN MXD_U32 size
)
{
    MXD_U32 i;
    MXD_8* buf;
    MXD_8* src;
    
    buf = (MXD_8*)pDestination;
    src = (MXD_8*)pSource;
        
    for(i=0; i<size; i++)
    {
        *buf++ = *src++;
    }

    return pDestination;
}

/*******************************************************************************
* mxdMemCmp
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
MXD_16 mxdMemCmp
(
    IN MXD_8 src1[],
    IN MXD_8 src2[],
    IN MXD_U32 size
)
{
    MXD_U32 i;
    MXD_16 value;

    for(i=0; i<size; i++)
    {
        if((value = (MXD_16)(src1[i] - src2[i])) != 0)
        {
            return value; 
        }
    }

    return 0;
}

/*******************************************************************************
* mxdStrlen
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
MXD_U32 mxdStrlen
(
    IN const MXD_PVOID pSource
)
{
    MXD_U32 i = 0;
    MXD_8* src;
    
    src = (MXD_8*)pSource;
        
    while(*src++) i++;

    return i;
}



