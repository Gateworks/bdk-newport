/** @file cs_types.h
 ****************************************************************************
 *
 * @brief
 *    This module contains common data types and defines used by
 *    the driver.
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
#ifndef __CS_TYPES_H__
#define __CS_TYPES_H__

/*
 * Basic data types
 */
typedef  unsigned long long     cs_uint64 ;
typedef  long long              cs_int64  ;
typedef  unsigned int           cs_uint32 ;
typedef  int                    cs_int32  ;
typedef  unsigned short         cs_uint16 ;
typedef  short                  cs_int16  ;
typedef  unsigned char          cs_uint8  ;
typedef  signed char            cs_int8   ;
typedef  cs_uint8               cs_boolean;
typedef  cs_int32               cs_status ;

typedef char                    cs_char8;


#ifndef  CS_UNION
#define  CS_UNION               union
#endif

#ifndef __LINE__
#   define __LINE__ 0
#endif
#ifndef __FILE__
#   define __FILE__ "<unknown>"
#endif

#if defined(WIN32) || defined(WIN64)
#  ifndef __func__
     /* MSVC doesn't set __func__ */
#    define __func__ __FUNCTION__
#  endif
#endif

/* From GCC man ch 6.47 */
#if __STDC_VERSION__ < 199901L /* pre-C99 (ansi/C89) */
#  if __GNUC__ >= 2
#     ifndef __func__
#        define __func__ __FUNCTION__
#     endif
#  endif
#endif

/* fallback define */
#ifndef __func__
#   define __func__ "<unknown>"
#endif

#ifdef CS_DONT_USE_INLINE
#  define CS_INLINE
#else
#  define CS_INLINE static __inline__
#endif

/*
 * MAC address struct
 */
typedef struct {
  cs_uint8      byte5 ;
  cs_uint8      byte4 ;
  cs_uint8      byte3 ;
  cs_uint8      byte2 ;
  cs_uint8      byte1 ;
  cs_uint8      byte0 ;
} cs_mac ;

/*
 * Register data type
 */
typedef  cs_uint16      cs_reg;

typedef enum {
  CS_RESET_DEASSERT    = 0,
  CS_RESET_ASSERT      = 1,
  CS_RESET_TOGGLE      = 2
} cs_reset_action_t ;

typedef enum {
  CS_TX       = 0,
  CS_RX,
  CS_TX_AND_RX,
  CS_RX_AND_TX = CS_TX_AND_RX
} cs_dir_t ;

/*
 * Other defines
 */
#define CS_OK           0
#define CS_ERROR        -1

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#ifndef NULL
#define NULL            0
#endif

#endif /* __CS_TYPES_H__ */

