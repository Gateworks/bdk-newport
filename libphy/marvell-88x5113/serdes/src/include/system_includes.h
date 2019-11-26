/* AAPL CORE Revision: 2.4.0
 *
 * Copyright (c) 2014-2016 Avago Technologies. All rights reserved.
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


/* System level header file for AAPL */

/** Doxygen File Header
 ** @file
 ** @brief System level declarations.
 **/

#ifndef AVAGO_SYSTEM_INCLUDES_H_
#define AVAGO_SYSTEM_INCLUDES_H_

#ifndef _POSIX_C_SOURCE
#    define _POSIX_C_SOURCE 200112L
#endif

#ifdef HAVE_CONFIG_H
#   include <config.h>
#else
#   define STDC_HEADERS 1
#endif

#define AAPL_COPYRIGHT "Copyright (c) 2013-2016 Avago Technologies. All rights reserved."
#undef AAPL_VERSION
#ifndef AAPL_VERSION_OVERRIDE
#  define AAPL_VERSION "2.4.0"
#else
#  define AAPL_VERSION AAPL_VERSION_OVERRIDE
#endif

#if !(defined HAVE_READLINE_READLINE_H && defined(HAVE_NCURSES_H))
#   undef AAPL_ENABLE_CONSOLE
#   define AAPL_ENABLE_CONSOLE 0
#endif

#if !(defined HAVE_FCNTL_H && defined(HAVE_SYS_MMAN_H))
#   undef AAPL_ALLOW_GPIO_JTAG
#   define AAPL_ALLOW_GPIO_JTAG 0
#else
#   include <fcntl.h>
#   include <sys/mman.h>
#endif

#ifdef __STDC_VERSION__
#   define AAPL_INLINE inline
#else
#   define AAPL_INLINE
#endif

#ifdef _MSC_VER
/* If Microsoft C: */
#  define __func__ __FUNCTION__
#  define snprintf sprintf_s
#endif

/*#ifdef WIN32
 * #define DECL "C" __declspec(dllexport)
 * #include <winsock2.h>
 * #include <windows.h>
 * BOOL APIENTRY DllMain2( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpAVAGO_RESERVED) { return TRUE; }
 */
#if (defined __MINGW32__ || defined _WIN32) && !(defined WIN32)
#    define WIN32
#endif

#if defined __MINGW32__ || defined WIN32
#    include <winsock2.h>
#    include <windows.h>
#    include <io.h>
#    include <ws2tcpip.h>
#    ifndef sleep
#        define sleep(a) Sleep(a * 1000)
#    endif
#else
#   define closesocket(x) close(x)
#   if AAPL_ALLOW_AACS
#        include <sys/socket.h>
#        include <netinet/in.h>
#        include <netdb.h>
#   endif
#endif

#if defined(__cplusplus) && AAPL_ENABLE_C_LINKING
#   define EXT extern "C"
#else
#   define EXT extern
#endif

#if !defined(HAVE_PTHREAD_H)
#   undef AAPL_ALLOW_THREADS
#   define AAPL_ALLOW_THREADS 0
#else
#   if AAPL_ALLOW_THREADS
#      include <pthread.h>
#   endif
#endif

#ifdef KERNEL_INCLUDES
#   include <linux/mm.h>
#   include <linux/slab.h>
#   include <linux/ctype.h>
#   include <linux/rtc.h>
#   include <linux/delay.h>
#else
#   if STDC_HEADERS
#       include <ctype.h>
#       include <stdio.h>
#       include <stdarg.h>
#       include <errno.h>
#       include <time.h>
#       include <math.h>
#       include <stdlib.h>
#       include <string.h>
#   else
#     if HAVE_STDLIB_H
#       include <stdlib.h>
#     endif
#     if HAVE_STRING_H
#       include <string.h>
#     endif
#   endif
#   if HAVE_UNISTD_H && !defined __MINGW32__
#       include <unistd.h>
#   endif
#   if defined HAVE_SYS_TYPES_H && HAVE_SYS_TYPES_H
#       include <sys/types.h>
#   endif
#   if defined HAVE_STDTYPES_H && HAVE_STDTYPES_H
#       include <inttypes.h>
#   endif
#   if defined HAVE_STDINT_H && HAVE_STDINT_H
#       include <stdint.h>
#   endif
#endif

#if !(defined(HAVE_FCNTL_H) && defined(HAVE_LINUX_I2C_DEV_H) && defined(HAVE_SYS_IOCTL_H))
#    undef AAPL_ALLOW_SYSTEM_I2C
#    define AAPL_ALLOW_SYSTEM_I2C 0
#endif

#if AAPL_ALLOW_SYSTEM_I2C
#    include <linux/i2c-dev.h>
#    include <fcntl.h>
#    include <sys/ioctl.h>
#endif

#ifdef HAVE_BCM2835_H
/* Include libraries specific to GPIO initialization
 * As of March 2014, the bcm2835 library can be found here:
 *     http
 */
#    include <bcm2835.h>
#else
#    undef AAPL_ALLOW_GPIO_MDIO
#    define AAPL_ALLOW_GPIO_MDIO 0
#endif


#endif
