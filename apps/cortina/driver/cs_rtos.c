/** @file cs_rtos.c
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
#include "cortina-bdk.h"
#include "cs_rtos.h"

/* Include any necessary library files when building the driver */
#ifndef CS_DONT_USE_STDLIB
#    include <stdlib.h>	       /* for malloc(), free(), abs() */
#    include <string.h>        /* for memcpy()                */
#    include <stdarg.h>        /* for variable args           */
#    include <stdio.h>         /* for printf variants         */
//#    if !defined(_WINDOWS) && !defined(_WIN32) && !defined(_WIN64)
//#        include <arpa/inet.h> /* for ntohs, htons            */
//#    else
//#        include <WinSock2.h>
//#    endif
#endif /* CS_DONT_USE_STDLIB */

/* ANSI C doesn't declare these methods */
int usleep(unsigned int usecs);



void CS_UDELAY(int usecs)
{
#ifdef CS_DONT_USE_STDLIB
    #error "TO DO: Cannot compile without defining CS_UDELAY() for your system in platform/cs_rtos.c"
#else
    bdk_watchdog_poke();
    bdk_wait_usec(usecs);
//    usleep(usecs);
#endif
}

void CS_MDELAY(int msecs)
{
    CS_UDELAY(msecs * 1000);
}

unsigned int CS_ABS(int value)
{
#ifdef CS_DONT_USE_STDLIB
    return (unsigned int) (value < 0 ? -value : value);
#else
    return (unsigned int) abs(value);
#endif
}

void *CS_MEMSET(void *p, int c, int n)
{
  char *pb = (char *) p;
  char *pbend = pb + n;
  while (pb != pbend) *pb++ = c;
  return p;
}


void *CS_MEMCPY(void *dst, const void *src, int n)
{
#ifdef CS_DONT_USE_STDLIB
    void *ret = dst;

    while (n--)
    {
      *(char *)dst = *(char *)src;
      dst = (char *) dst + 1;
      src = (char *) src + 1;
    }

    return ret;
#else
    return memcpy(dst, src, n);
#endif
}


int CS_STRLEN(const char *s)
{
  const char *eos = s;
  while (*eos++);
  return (int) (eos - s - 1);
}


char *CS_STRCAT(char *dest, const char *source)
{ 
  char *d = dest;
  while (*d) ++d;
  while ((*d++ = *source++) != '\0') ;
  return (dest);
}


char *CS_STRNCPY(char *dest, const char *source, int count)
{
  char *start = dest;

  while (count && (*dest++ = *source++)) count--;
  if (count) while (--count) *dest++ = '\0';
  return start;
}

#ifndef CS_DONT_USE_STDLIB
#ifndef CS_TRACE_FUNCTION
/** Don't use this function directly, use CS_TRACE((x)) instead
 * @private
 */
void CS_TRACE_FUNCTION(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(CS_TRACE_STREAM, fmt, ap);
    va_end(ap);
}
#endif
#endif

cs_status CS_VERIFY_ENDIANESS()
{
  cs_uint16 val = 0x2211 ;
  cs_uint8  low_byte = ((cs_uint8 *)&val)[0] ;

  if (low_byte == 0x22) {
#ifdef CS_BIG_ENDIAN
    return (CS_OK) ;
#else /* CS_LITTLE_ENDIAN */
    return (CS_ERROR) ;
#endif
  }
  else if (low_byte == 0x11) {
#ifdef CS_BIG_ENDIAN
    return (CS_ERROR) ;
#else /* CS_LITTLE_ENDIAN */
    return (CS_OK) ;
#endif
  }
  else {
    return (CS_ERROR) ;
  }
}

cs_status cs4224_reg_set(cs_uint32 slice, cs_uint32 addr, cs_uint16 data)
{
    int status = bdk_mdio_45_write(SLICE_TO_NODE(slice), SLICE_TO_BUS(slice), SLICE_TO_PHY(slice) | SLICE_TO_DIE(slice), 0, addr, (int)data);
//    printf("MDIO write, slice = 0x%08x, addr = 0x%08x, data = 0x%04x\n", slice, addr, data);
    if (status == -1)
    {
        bdk_warn("MDIO write failure\n");
        return CS_ERROR;
    }

    return CS_OK;
}

cs_status cs4224_reg_get(cs_uint32 slice, cs_uint32 addr, cs_uint16* data)
{
    int read_data = bdk_mdio_45_read(SLICE_TO_NODE(slice), SLICE_TO_BUS(slice), SLICE_TO_PHY(slice) | SLICE_TO_DIE(slice), 0, addr);
    *data = (cs_uint16) read_data;
//    printf("MDIO  read, slice = 0x%08x, addr = 0x%08x, data = 0x%04x\n", slice, addr, *data);
    if (read_data == -1)
    {
        bdk_warn("MDIO read failure\n");
        return CS_ERROR;
    }
    return CS_OK;
}

