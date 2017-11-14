/** @file cs_rtos.h
 ****************************************************************************
 *
 * @brief
 *    This contains all the RTOS(like system calls) and environment      *
 *    related macro's and stub utilities which should be modified or     *
 *    filled in as suited to the customer environment. It is important   *
 *    that this customization or porting of the driver is done BEFORE    *
 *    making any attempt to compile or use the driver.                   *
 *
 ****************************************************************************
 * @author
 *    Copyright (c) 2011-2015, Inphi Corporation
 *    All rights reserved.
 *    
 *    Redistribution and use in source and binary forms, with or without modification, 
 *    are permitted provided that the following conditions are met:
 *    
 *    1.	Redistributions of source code must retain the above copyright notice, 
 *       this list of conditions and the following disclaimer.
 *    
 *    2.	Redistributions in binary form must reproduce the above copyright notice, 
 *       this list of conditions and the following disclaimer in the documentation and/or 
 *       other materials provided with the distribution.
 *    
 *    3.	Neither the name of Inphi Corporation nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software without 
 *       specific prior written permission.
 *    
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 *    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 *    OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 *    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 *    OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 *    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *    API Version Number: 3.7.8
 ****************************************************************************/
#ifndef __CS_RTOS_H__
#define __CS_RTOS_H__

#include "cs_types.h"
#include "cs_config.h"


/**********************************************************
 *         Input/Output Routines                          *
 **********************************************************/
#ifdef CS_DONT_USE_STDLIB
#    define CS_FPRINTF(x)
#    define CS_FLUSH()
#    define CS_PRINTF(x)
#    define CS_SNPRINTF(x)

#    define CS_TRACE(x)
#else
#    include <stdio.h>
#    define CS_PRINTF(x)  printf x
#    define CS_FPRINTF(x) fprintf x
#    define CS_FLUSH()  fflush(stdout)
#ifndef __APPLE__
int snprintf(char* s, size_t n, const char* format, ...);
#endif /* __APPLE__ */
#    define CS_SNPRINTF(x) snprintf x

/* Like printf but prints to CS_TRACE_STREAM instead of stdout */
void CS_TRACE_FUNCTION(const char *fmt, ...);

/* Based on http://stackoverflow.com/a/1644898
 * Make the compiler test validity of the printf calls even if
 * debug output is turned off
 */
#    define CS_TRACE(x) \
        do { if (CS_HAS_DEBUG_STATUS_DUMPS) { \
            CS_TRACE_FUNCTION("%s:%d:%s(): ", __FILE__, __LINE__, __func__); \
            CS_TRACE_FUNCTION x; \
            fflush(CS_TRACE_STREAM); \
            } \
        } while (0)


#endif /* CS_DONT_USE_STDLIB */


/**********************************************************
 *         Math utilities                                 *
 **********************************************************/
unsigned int CS_ABS(int value);


/**********************************************************
 *         Timer delay utilities                          *
 **********************************************************/
void CS_UDELAY(int usecs);
void CS_MDELAY(int msecs);


/**********************************************************
 *         Memory Handling                                *
 **********************************************************/
void *CS_MEMSET(void *p, int c, int n);
void *CS_MEMCPY(void *p, const void* src, int n);
int CS_STRLEN(const char *s);
char *CS_STRCAT(char *dest, const char *source);
char *CS_STRNCPY(char *dest, const char *source, int count);


/**********************************************************
 *         Endianess Handling                             *
 **********************************************************/
/* Make sure endianess is defined */
#ifdef CS_BIG_ENDIAN
#  ifdef CS_LITTLE_ENDIAN
#    error "CS_BIG_ENDIAN and CS_LITTLE_ENDIAN are both defined."
#  endif
#else
#  ifndef CS_LITTLE_ENDIAN
#    error "Either CS_BIG_ENDIAN or CS_LITTLE_ENDIAN must be defined."
#  endif
#endif

/* Function used to verify endianess */
cs_status CS_VERIFY_ENDIANESS();


/**********************************************************
 *         Other utilities                                *
 **********************************************************/

/* bit masks */
#define CS_BIT0  0x0001
#define CS_BIT1  0x0002
#define CS_BIT2  0x0004
#define CS_BIT3  0x0008
#define CS_BIT4  0x0010
#define CS_BIT5  0x0020
#define CS_BIT6  0x0040
#define CS_BIT7  0x0080

#define CS_BIT8  0x0100
#define CS_BIT9  0x0200
#define CS_BIT10 0x0400
#define CS_BIT11 0x0800
#define CS_BIT12 0x1000
#define CS_BIT13 0x2000
#define CS_BIT14 0x4000
#define CS_BIT15 0x8000

/* bit masks for MSB registers */
#define CS_MSB_BIT16 0x0001
#define CS_MSB_BIT17 0x0002
#define CS_MSB_BIT18 0x0004
#define CS_MSB_BIT19 0x0008
#define CS_MSB_BIT20 0x0010
#define CS_MSB_BIT21 0x0020
#define CS_MSB_BIT22 0x0040
#define CS_MSB_BIT23 0x0080

#define CS_MSB_BIT24 0x0100
#define CS_MSB_BIT25 0x0200
#define CS_MSB_BIT26 0x0400
#define CS_MSB_BIT27 0x0800
#define CS_MSB_BIT28 0x1000
#define CS_MSB_BIT29 0x2000
#define CS_MSB_BIT30 0x4000
#define CS_MSB_BIT31 0x8000


/** Use this macro when assigning to a cs_boolean, 
 * since the cs_boolean is really an unsigned char
 * 
 * @example
 * valid == TRUE iff bit3 OR bit5 is set in reg_val:
 * cs_boolean valid = CS_IF_SET(reg_val,CS_BIT3|CS_BIT5);
 */
#define CS_IF_SET(val,mask) ( ((val) & (mask)) != 0 )

/** True iff all bits in mask are set */
#define CS_IF_ALL_SET(val,mask) ( ((val) & (mask)) == mask )

/** True iff all bits in mask are cleared */
#define CS_IF_CLR(val,mask) ( ((val) & (mask)) == 0 )

/** Set mask bits in val */
#define CS_SET(val,mask) ( ((val) | (mask)) )

/** Clear mask bits in val */
#define CS_CLR(val,mask) ( ((val) & ~(mask)) )

/** Toggle mask bits in val */
#define CS_TOGGLE(val,mask) ( ((val) ^ (mask)) )


#endif /* __CS_RTOS_H__ */

