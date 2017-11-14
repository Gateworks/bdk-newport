#ifndef __CS_CONFIG_H__
#define __CS_CONFIG_H__
/** @file cs_config.h
 ****************************************************************************
 *
 * @brief
 *    This module allows individual features in the API to be compiled
 *    in or out to manage code space.
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
 ***************************************************************************/

//#define CS_BIG_ENDIAN  //Normally part of the Makefile
#define CS_LITTLE_ENDIAN  //Normally part of the Makefile

/* Set to enable compile in debug features such as register dump */
#define CS_HAS_DEBUG_LOOPBACKS      1
#define CS_HAS_DEBUG_PRBS           1
#define CS_HAS_DEBUG_REGISTER_DUMPS 1
#define CS_HAS_DEBUG_STATUS_DUMPS   1

/* Set to define where the CS_TRACE output goes (stderr or stdout)
 * This is ignored if CS_DONT_USE_STDLIB is defined */
#define CS_TRACE_STREAM stdout

/* Set to allow the use of floating-point math */
#define CS_HAS_FLOATING_POINT 

/* Set to include the Interrupt handling code */
/* #define CS_HAS_INTERRUPTS  */

/* Set to not use stdlib */
/* #define CS_DONT_USE_STDLIB */

/* Set to not use inlining */
/* #define CS_DONT_USE_INLINE */

/* Set to include filesystem  */
#define CS_HAS_FILESYSTEM

/* Set to not load the ucode automatically (dangerous) */
/* #define CS_SKIP_UCODE_DOWNLOAD 1 */

/* Set to enable experimental maddr masking (dangerous) */
/* #define CS_MULTI_CHIP_UCODE_PRGM */

#endif /* __CS_CONFIG_H__ */
