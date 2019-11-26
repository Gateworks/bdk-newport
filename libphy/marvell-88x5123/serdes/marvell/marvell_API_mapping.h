/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
********************************************************************************
*/
/**
********************************************************************************
* @file marvell_API_mapping.h
*
* @brief API mappings from POSIX to hws
*
*
* @version   1
********************************************************************************
*/

#ifndef __marvell_API_mapping_H
#define __marvell_API_mapping_H

#include <cpss/common/labServices/port/gop/common/os/hwsEnv.h>

/* redefine alloc macroces */
#undef AAPL_MALLOC
#undef AAPL_REALLOC
#undef AAPL_FREE
#undef AAPL_MEMSET
#define AAPL_MALLOC(sz)      hwsMalloc(sz)         /**< AAPL uses this for malloc. */
#define AAPL_REALLOC(ptr,sz) hwsRealloc(ptr,sz)    /**< AAPL uses this for realloc. */
#define AAPL_FREE(ptr)       hwsFree(ptr)          /**< AAPL uses this for free. */

#ifdef MV_HWS_REDUCED_BUILD_EXT_CM3
#include <stdio.h>
#include <string.h>
#define AAPL_MEMSET(ptr,sym,sz) memset(ptr,sym,sz) /**< AAPL uses this for memset. */
#else
#define AAPL_MEMSET(ptr,sym,sz) hwsMemSet(ptr,sym,sz) /**< AAPL uses this for memset. */
#endif

/* redefine stdio APIS */
#define sprintf              hwsSprintf
#define snprintf             hwsSnprintf
#define vsprintf             hwsVsprintf
#define vsnprintf            hwsVsnprintf

#ifdef CPSS_BLOB
/* redefine ctype macros */
#undef tolower
#undef isspace
#undef isdigit
#undef isxdigit

#define tolower(_c)  (((_c)>='A' && (_c)<='Z')?((_c)+('a'-'A')):(_c))
#define isspace(_c)  (((_c)==' '||(_c)=='\t'||(_c)=='\r'||(_c)=='\n')?1:0)
#define isdigit(_c)  (((_c)>='0' && (_c)<='9')?1:0)
#define isxdigit(_c)  ((((_c)>='0' && (_c)<='9')||((_c)>='a' && (_c)<='f')||((_c)>='A' && (_c)<='F'))?1:0)

#define MS_SLEEP    hwsDelayMs

/* redefine str* APIs */
#undef strcpy
#undef strlen
#undef strchr
#undef strncmp
#undef strrchr
#define strcpy      hwsStrCpy
#define strlen      hwsStrLen
#define strchr      hwsStrChr
#define strncmp     hwsStrNCmp
#define strrchr     hwsStrrChr

long hws_strtol(const char *nptr, char **endptr, int base);
unsigned long hws_strtoul(const char *nptr, char **endptr, int base);
#define strtol      hws_strtol
#define strtoul     hws_strtoul

void *hws_memmove(void *dest, void *src, unsigned len);
#define memmove     hws_memmove

#endif /*CPSS_BLOB*/

#include <mvHwsAvagoSerdes.h>

#endif /* __marvell_API_mapping_H */

