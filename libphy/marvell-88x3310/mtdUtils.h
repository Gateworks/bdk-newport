/*******************************************************************************
Copyright (C) 2014 - 2018, Marvell International Ltd. and its affiliates
If you received this File from Marvell and you have entered into a commercial
license agreement (a "Commercial License") with Marvell, the File is licensed
to you under the terms of the applicable Commercial License.
*******************************************************************************/

/********************************************************************
This file contains utility functions prototypes.
********************************************************************/
#ifndef MTD_UTIL_H
#define MTD_UTIL_H
#if C_LINKAGE
#if defined __cplusplus 
    extern "C" { 
#endif 
#endif

/*******************************************************************************
* mtdMemSet
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
MTD_PVOID mtdMemSet
(
    IN MTD_PVOID start,
    IN int  symbol,
    IN MTD_U32 size
);

/*******************************************************************************
* mtdMemCpy
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
MTD_PVOID mtdMemCpy
(
    IN MTD_PVOID destination,
    IN const MTD_PVOID source,
    IN MTD_U32  size
);

/*******************************************************************************
* mtdMemCmp
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
int mtdMemCmp
(
    IN MTD_8 src1[],
    IN MTD_8 src2[],
    IN MTD_U32 size
);

/*******************************************************************************
* mtdStrlen
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
MTD_U32 mtdStrlen
(
    IN const MTD_PVOID source
);

/*******************************************************************************
* mtdIsZero
*
* DESCRIPTION:
*       Compares given memories.
*
* INPUTS:
*       ptr - source
*       bytes - size of memory to compare
*
* OUTPUTS:
*       None
*
* RETURNS:
*       MTD_TRUE if all zeros, otherwise returns MTD_FALSE
*
* COMMENTS:
*       None
*
*******************************************************************************/
MTD_BOOL mtdIsZero(
    IN MTD_PVOID ptr, 
    IN MTD_U16 bytes 
);


#if C_LINKAGE
#if defined __cplusplus 
}
#endif 
#endif

#endif /* defined MTD_UTIL_H */


