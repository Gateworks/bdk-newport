/* AAPL CORE Revision: 2.6.2
 *
 * Copyright (c) 2014-2017 Avago Technologies. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Internal library header file for AAPL (ASIC and ASSP Programming Layer). */

/** Doxygen File Header
 ** @file
 ** @brief Declarations for library functions.
 **/

#ifndef AAPL_LIBRARY_H_
#define AAPL_LIBRARY_H_

/* Typedefs:
 */
#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#if ! HAVE_UINT
typedef unsigned int uint;
#endif

/* Define type for eye gather counts: */
#if defined __STDC_VERSION && __STDC_VERSION__ > 199409L
  typedef long long bigint;
#elif defined __MINGW_EXTENSION
  typedef __int64 bigint;
#elif defined _STDINT_H
  typedef int64_t bigint;
#else
  typedef long long bigint;
#endif

#if defined X86_64
typedef bigint   fn_cast_t;
#else
typedef long int fn_cast_t;
#endif


/* Determine number of elements in a static array: */
#define AAPL_ARRAY_LENGTH(a)   (int)(sizeof(a) / sizeof((a)[0]))
#define AAPL_BITS_SET(var,width,shift,value) var = ((var & ~(((1<<width)-1)<<(shift))) | ((value)<<(shift)))
#define AAPL_BITS_GET(var,width,shift) ((var >> (shift)) & ((1<<width)-1))

/* Specify how to declare a 64 bit constant: */
#ifdef __INT64_C
#   define AAPL_CONST_INT64(x) __INT64_C(x)
#elif defined(__GNUC__) && !defined(__STDC_VERSION__)
#   define AAPL_CONST_INT64(x) ((bigint)x)
#elif defined(__GNUC__) && defined(WIN32)
#   define AAPL_CONST_INT64(x) (x ## LL)
#elif defined(WIN32)
#   define AAPL_CONST_INT64(x) (x ## i64)
#else
#   define AAPL_CONST_INT64(x) (x)
#endif

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS

EXT void  ms_sleep(uint msec);

/* Converts data to a 32 character ASCII encoded binary str with optional underscores every 8 bits */
EXT char *aapl_hex_2_bin(char *str, uint data, int underscore_en, int bits);

/* Portability utility functions: */
EXT int   aapl_strcasecmp(const char *s1, const char *s2);
EXT int   aapl_strncasecmp(const char *s1, const char *s2, size_t len);
EXT char *aapl_strdup(const char *string);
EXT void  aapl_str_rep(char *str, char search, char replace);
EXT char *aapl_strtok_r(char *str, const char *delim, char **saveptr);
EXT size_t aapl_local_strftime(char *buf, size_t max, const char *format);

#endif

#endif

