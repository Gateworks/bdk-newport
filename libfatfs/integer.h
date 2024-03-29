/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _FF_INTEGER
#define _FF_INTEGER

#include <stdint.h>

/* Definitions for ThunderX CN88XX architecture (AARCH64) */

/* This type MUST be 8 bit */
typedef uint8_t			BYTE;

/* These types MUST be 16 bit */
typedef int16_t			SHORT;
typedef uint16_t		WORD;
typedef uint16_t		WCHAR;

/* These types MUST be 16 bit or 32 bit */
typedef int32_t			INT;
typedef uint32_t		UINT;

/* These types MUST be 32 bit */
typedef int32_t			LONG;
typedef uint32_t		DWORD;

#endif
