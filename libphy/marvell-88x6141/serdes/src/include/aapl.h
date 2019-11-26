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


/** @file
 ** @brief   Customer level configuration file.
 ** @details aapl.h is the only file we expect customers to configure.
 ** @details aapl.h consists mostly of defines taking a value of 0 or 1.
 **          To disable functionality, set the define value to 0.  Do not
 **          comment or remove the define as that will cause compile failures.
 ** @details aapl.h must be included to access AAPL functions.  Typically,
 **          it's the only AAPL header a library user needs to include.
 **/

#ifndef AAPL_H_
#define AAPL_H_

#ifndef AVAGO_FIRMWARE_PATH
/** @brief This optional define provides a shortcut for accessing firmware
 **        by [fw_rev] and [build_id] rather than only by full path.
 **
 ** It points to a directory tree organized as follows:
 **
 **  #AVAGO_FIRMWARE_PATH/serdes/[fw_rev]/serdes.[fw_rev]_[build_id].rom
 **
 **  #AVAGO_FIRMWARE_PATH/serdes/[fw_rev]/serdes.[fw_rev]_[build_id].swap
 **
 **  #AVAGO_FIRMWARE_PATH/sbus_master/[fw_rev]/sbus_master.[fw_rev]_[build_id].rom
 **/
#define AVAGO_FIRMWARE_PATH "/firmware/"
#endif

/* The AAPL_ALLOW_* defines enable/disable code sections of AAPL.
 * To remove an unneeded code section from AAPL, set the define
 *      value to 0. Do not comment or remove a define as that may
 *      cause compile failures.
 */

#define AAPL_ALLOW_AACS                0  /**< Set to 0 to remove the AACS (via TCP) communication functions. */
#define AAPL_ALLOW_MDIO                0  /**< Set to 0 to remove the MDIO communication functions. */
#define AAPL_ALLOW_GPIO_MDIO           0  /**< Set to 0 to remove the built-in GPIO based MDIO communication functions. */
#define AAPL_ALLOW_I2C                 0  /**< Set to 0 to remove the I2C communication functions.. */
#define AAPL_ALLOW_SYSTEM_I2C          0  /**< Set to 0 to remove the built-in system I2C communication functions (ie, /dev/i2c) */
#define AAPL_ALLOW_OFFLINE_SBUS        1  /**< Set to 0 to remove the built-in offline communication functions.. */
#define AAPL_ALLOW_JTAG                0  /**< Set to 0 to remove the JTAG communication functions. */
#define AAPL_ALLOW_GPIO_JTAG           0  /**< Set to 0 to remove the built-in GPIO based JTAG communication functions. */
#define AAPL_ALLOW_THREAD_SUPPORT      0  /**< Set to 1 to enable mutex locking for certain functions to help make AAPL more thread safe */
#define AAPL_ALLOW_ANSI_COLORS         1  /**< Set to 1 to enable ANSI color codes in log messages */
#define AAPL_ALLOW_SIGNALS             1  /**< Set to 1 to enable AAPL to trap SIGINT system signals */

/* Set value to 0 to disable corresponding feature support: */
#define AAPL_ENABLE_DIAG               1  /**< Enable diagnostics. */
#define AAPL_ENABLE_FILE_IO            1  /**< Enable use of file IO and the FILE type. */
#define AAPL_ENABLE_C_LINKING          1  /**< Set to 0 if library and callers all are C++ compiled. */
#define AAPL_ENABLE_AACS_SERVER        0  /**< Enable the AACS server. */

#define AAPL_ENABLE_EYE_MEASUREMENT    1  /**< Enable eye measurement support. */
#define AAPL_ENABLE_SERDES_AUTO_NEG    1 /**< Enable SerDes Auto-negotiation */
#define AAPL_ENABLE_SERDES_HAL         1  /**< Enable SerDes HAL support */
#define AAPL_ENABLE_FEC                1  /**< Enable SerDes FEC support */


#define AAPL_ENABLE_AVSP_5410          0  /**< Enable AVSP 5410 support. */
#define AAPL_ENABLE_AVSP               0  /**< Enable AVSP 5410 support. */

#if AAPL_ENABLE_AACS_SERVER && !AAPL_ALLOW_AACS
#error "AAPL_ENABLE_AACS_SERVER requires AAPL_ALLOW_AACS to also be enabled."
#endif


/** @brief   Defines the available communication methods.
 ** @details AAPL supports several methods for communicating with Avago IP.
 **          The communication_method member of the aapl structure defines
 **          which is used by the library, and can be changed at run time.
 **
 **          The default value compiled into the library is configured using
 **          the AAPL_DEFAULT_COMM_METHOD define in the aapl.h header file.
 **
 **          Note also that several AAPL_ALLOW_* defines configure which
 **          methods are compiled into the library.
 **/
typedef enum
{
    AVAGO_SBUS,             /**< Send SBus commands via the registered SBus function. AACS supported. */

    AVAGO_MDIO,             /**< Send SBus commands via the registered MDIO function. AACS supported. */
    AVAGO_GPIO_MDIO,        /**< Send SBus commands via the registered GPIO MDIO function. */

    AVAGO_I2C,              /**< Send SBus commands via the registered I2C function. AACS supported. */
    AVAGO_SYSTEM_I2C,       /**< Send SBus commands via registered system calls. */

    AVAGO_JTAG,             /**< Send SBus commands via the registered JTAG function. AACS supported. */
    AVAGO_BB_JTAG,          /**< Send SBus commands via the registered bit-banged JTAG function. AACS supported. */
    AVAGO_BB_GPIO_JTAG,     /**< Send SBus commands via the registered bit banged MDIO function. */

    AVAGO_OFFLINE           /**< Emulate SBus commands internally */

} Aapl_comm_method_t;

/** @brief Set the default AAPL communication_method value.
 ** @details The AAPL communication method actually used to communicate with
 **          devices is controlled by Aapl_t::communication_method (of type
 **          Aapl_comm_method_t).  This
 **          define simply sets the compiled in default value for this field.
 ** @details Note: The AAPL_ALLOW_* defines determine if the code for
 **          specific communication methods is compiled into the library.
 **/
#define AAPL_DEFAULT_COMM_METHOD         AVAGO_SBUS

/** @brief The default value for Aapl_t::i2c_base_addr.
 ** The base I2C address for Avago devices is usually 0x40.
 ** Normally, this is set to the address of the first Avago device.
 **/
#define AAPL_DEFAULT_I2C_BASE_ADDR       0x40

/** @brief The I2C device to communicate with for the SYSTEM_I2C communication method */
#define AAPL_SYSTEM_I2C_DEVICE "/dev/i2c-1"

/** @brief The default value for Aapl_t::mdio_base_port_addr.
 ** Normally, this is set to the address of the first Avago device.
 **/
#define AAPL_DEFAULT_MDIO_BASE_PORT_ADDR    0


/* AAPL_PROCESS_ID_OVERRIDE allows the user to override the process ID.
 * If AAPL is not using AACS to communicate with the device, you should
 * specify this here, otherwise AAPL will assume the process type
 * AVAGO_PROCESS_F and issue a warning. (AACS can auto determine the process type,
 * whereas other communication methods can not.)
 */

#define AAPL_PROCESS_ID_OVERRIDE AVAGO_PROCESS_B 

/** @brief Allows the user to override the number of devices with which
 **        AAPL will communicate.  The value 0 indicates that AAPL should
 **        auto-discover this value, if possible.
 **
 ** If AAPL is not using AACS to communicate with the device, you should
 ** specify this here, otherwise AAPL will assume one device
 ** and issue a warning.
 **/

#define AAPL_NUMBER_OF_CHIPS_OVERRIDE 1


/** @brief Allows the user to override the number of SBus rings with which
 **        AAPL will communicate.  The value 0 indicates that AAPL should
 **        auto-discover this value, if possible.
 **
 ** If AAPL is not using AACS to communicate with the device, you should
 ** specify this here, otherwise AAPL will assume one SBus ring.
 **/

#define AAPL_NUMBER_OF_RINGS_OVERRIDE 1


/* The AAPL_CHIP_ID_HEX_OVERRIDEn defines JTAG IDCODES for devices AAPL will be
 * communicating with. If AAPL is using an AVAGO_AACS_* communication method
 * these IDCODES will be auto-discovered.
 * If you are not using an AVAGO_AACS_* communication method you should define
 * AAPL_CHIP_ID_HEX_OVERRIDE0 through AAPL_CHIP_ID_HEX_OVERRIDEn, where n is
 * the number of devices AAPL will be communicating with.
 * You must always start at AAPL_CHIP_ID_HEX_OVERRIDE0.
 * WARNING: The values below are examples, and are not valid IDCODEs.
 *   The user should contact Avago if they do not know the proper
 *   IDCODE value to use here.
 *#define AAPL_CHIP_ID_HEX_OVERRIDE0 0xaaaaaaaa
 *#define AAPL_CHIP_ID_HEX_OVERRIDE1 0xaaaaaaaa
 *...
 *#define AAPL_CHIP_ID_HEX_OVERRIDE14 0xaaaaaaaa
 *
 * Id codes can also be entered as binary strings, using the following defines:
 *
 *#define AAPL_CHIP_ID_OVERRIDE0  "10101010101010101010101010101010"
 *#define AAPL_CHIP_ID_OVERRIDE1  "10101010101010101010101010101010"
 *....
 *#define AAPL_CHIP_ID_OVERRIDE14 "10101010101010101010101010101010"
 *
 * If both are given, the hex values will be used.
 */

#define AAPL_CHIP_ID_OVERRIDE0  "00000000000000000000000000000001"

/** Maximum number of devices AAPL supports.
 ** Reducing this value to that actually used will reduce the memory footprint of the Aapl_t struct.
 ** Valid range: [1-15].
 **/
#define AAPL_MAX_CHIPS 1

/** Maximum number of SBus rings AAPL supports.
 ** Reducing this value to that actually used will reduce the memory footprint of the Aapl_t struct.
 ** Valid range: [1-15].
 **/
#define AAPL_MAX_RINGS 1

/** Maximum number of AACS commands to queue before send.
 ** Setting this to 0 disables command buffering.
 **/
#define AAPL_MAX_CMDS_BUFFERED      0

#define AAPL_SERDES_INT_TIMEOUT        500  /**< Maximum number of SBus reads to check for completion of SPICO interrupt command */
#define AAPL_SBUS_MDIO_TIMEOUT         100  /**< Maximum number of reads of the SBUS_RESULT register in sbus-over-mdio mode */
#define AAPL_SERDES_INIT_RDY_TIMEOUT    20  /**< Maximum milliseconds for pll calibration */
#define AAPL_SPICO_UPLOAD_WAIT_TIMEOUT 500  /**< Maximum milliseconds to wait for AAPL to wait for external SPICO upload to complete */
#define AAPL_I2C_HARD_RESET_TIMEOUT    100  /**< Maximum number of commands to send after a hard I2C reset to wait for bus to come back up */

/*
 * AAPL Logging defines:
 *
 * The following table describes when and where messages get logged when using AAPL.
 *
 * NOTE: If you are integrating AAPL into your your codebase and do not want AAPL to
 *       save log messages on its own or send any output to a console, do the following:
 *
 *          1. Comment out the define for AAPL_STREAM below. This prevents AAPL from
 *             sending messages to stdout (this could alternatively could be done at
 *             runtime by setting Aapl_t::enable_stream_logging to 0).
 *
 *          2. Comment out the define for AAPL_STREAM_ERR below. This prevents AAPL
 *             from sending messages to stderr (this could alternatively could be done at
 *             runtime by setting Aapl_t::enable_stream_err_logging to 0).
 *
 *          3. Register your own logging function using aapl_register_logging_fn().
 *             Once that is done, AAPL will always call that function for ALL messages,
 *             including debug messages, warnings, and errors.
 *
 *                     AAPL_STREAM           AAPL_STREAM_ERR                      Registered
 *                                                                              logging function *
 *                     ------------          ----------------                   ------------------
 *
 *   AVAGO_DEBUGn   (#ifdef AAPL_STREAM &&        never                       (Aapl_t::enable_debug_logging
 *                  Aapl_t::enable_stream_logging                                  && n <= Aapl_t::debug)
 *                  && n <= Aapl_t::debug)
 *
 *   AVAGO_INFO     (#ifdef AAPL_STREAM &&        never                         always written
 *                  Aapl_t::enable_stream_logging)
 *
 *   AVAGO_WARNING         never           (#ifdef AAPL_STREAM_ERR &&           always written
 *                                          Aapl_t::enable_stream_err_logging)
 *   AVAGO_ERR             never           (#ifdef AAPL_STREAM_ERR &&           always written
 *                                          Aapl_t::enable_stream_err_logging)
 *
 *   AVAGO_MEM_LOG**       never                  never                         always written
 *
 *
 *   * Will be Aapl_t::log unless the user has registered a logging function by calling
 *     aapl_register_logging_fn(). If it has been called, then all writes that would have
 *     gone to Aapl_t::log will instead be sent to the registered logging function.
 *
 *  ** AVAGO_MEM_LOG is an internal logging method to send lines without a newline to the log.
 */

/** Sets the stdio stream to write debug and info messages.
 ** @see aapl_log_printf().
 **
 ** Comment out, or set Aapl_t::enable_stream_logging member of aapl to false,
 **   to suppress this type of output.
 **
 ** @see AAPL_STREAM_ERR
 **/
#define AAPL_STREAM stdout

/** Sets the stdio stream to write warning and error messages.
 ** @see aapl_log_printf().
 **
 ** Comment out, or set Aapl_t::enable_stream_err_logging member of aapl to false,
 **   to suppress this type of output.
 **
 ** @see AAPL_STREAM
 **/
#define AAPL_STREAM_ERR stderr

/** @brief Default value for Aapl_t::enable_debug_logging.
 ** This value also can be changed at run time.
 **/
#define AAPL_DEFAULT_ENABLE_DEBUG_LOGGING        1

/** @brief Default value for Aapl_t::enable_stream_logging.
 ** This value also can be changed at run time.
 **/
#define AAPL_DEFAULT_ENABLE_STREAM_LOGGING       1

/** @brief Default value for Aapl_t::enable_stream_err_logging.
 ** This value also can be changed at run time.
 **/
#define AAPL_DEFAULT_ENABLE_STREAM_ERR_LOGGING   1

/** Default for Aapl_t::log_time_stamps.
 ** If defined, this value also can be changed at run time.
 **
 ** Comment out the define to remove time stamp logging from the compile.
 ** Set to 0 to compile in with a disabled default.
 ** Set to 1 to compile in with an enabled default.
 **/
#define AAPL_LOG_TIME_STAMPS 1


/** Only used when calling the aacs_server() function */
#define AACS_SERVER_BUFFERS 4096


/** Buffer used by aapl_log_printf().
 ** If too small, output will be truncated.
 **/
#define AAPL_LOG_PRINTF_BUF_SIZE 4096

/** Used by AAPL for the log, data_char, and debug buffers.
 ** Also used by recv. This number should always be >= the max size
 ** the AACS server will return.
 **
 ** AAPL's AACS server can return up to AAPL_MAX_CMDS_BUFFERED * AAPL_SBUS_CMD_LOG_BUF_SIZE.
 **/
#define AAPL_LOG_BUF_SIZE 1024

/*
 * Portability defines:
 */

#define HAVE_UINT 0  /**< Set to 1 if your system headers already have the uint typedef. */

/* Add additional defines here to replace any library
 * functions your build environment doesn't support.
 */

/*#define strtoul(a,b,c) simple_strtol(a,b,c) */

#ifdef KERNEL_INCLUDES
#include "system_includes.h"

#define MS_SLEEP(milliseconds) udelay(milliseconds*1000)

#define AAPL_EXIT(val)       {}

#define AAPL_MALLOC(sz)      kmalloc(sz, GFP_KERNEL)         /**< AAPL uses this for malloc. */
#define AAPL_REALLOC(ptr,sz) krealloc(ptr,sz, GFP_KERNEL)    /**< AAPL uses this for realloc. */
#define AAPL_FREE(ptr)       kfree(ptr)                      /**< AAPL uses this for free. */

static inline unsigned long aapl_strtoul(char *nptr, char **endptr, int base) {unsigned long val; if(kstrtoul(nptr, base, &val)) {*endptr = nptr; return 0;} else {return val;}}
static inline long aapl_strtol(char *nptr, char **endptr, int base) {long val; if(kstrtol(nptr, base, &val)) {*endptr = nptr; return 0;} else {return val;}}

#else

/* Uncomment and edit if the default ms_sleep doesn't work for you.
 *#define MS_SLEEP(milliseconds) udelay(milliseconds*1000)
 */

#define AAPL_EXIT(val)       exit(val)          /**< AAPL uses this for exit. */

/* All malloc/realloc/free calls make use of these macros: */
#define AAPL_MALLOC(sz)      malloc(sz)         /**< AAPL uses this for malloc. */
#define AAPL_REALLOC(ptr,sz) realloc(ptr,sz)    /**< AAPL uses this for realloc. */
#define AAPL_FREE(ptr)       free(ptr)          /**< AAPL uses this for free. */

#define aapl_strtoul(nptr,endptr,base) strtoul(nptr,endptr,base)
#define aapl_strtol( nptr,endptr,base) strtol( nptr,endptr,base)

#endif

#if 0
/* Use this code to replace the aapl_{malloc/realloc/free} error
 *   tracing calls with straight malloc versions.
 */
# define aapl_malloc(a,sz,c)      AAPL_MALLOC(sz)
# define aapl_realloc(a,ptr,sz,c) AAPL_REALLOC(ptr,sz)
# define aapl_free(a,ptr,c)       AAPL_FREE(ptr)
#endif


/* Note:  BOOL is a macro, not a typedef "bool" with "false" and "true" values,
 * to avoid reserved word conflicts for C++ compilations.
 * FALSE must have the value 0; if compiling using C++ it may also be false.
 * TRUE must have the value 1; if compiling using C++ it may also be true.
 */
#if !defined BOOL && !defined __MINGW32__ && !defined _MSC_VER
#define BOOL int
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#include "../../../mydApiTypes.h"
#include "../../../mydUtils.h"

/* AAPL required files: */
#include "system_includes.h"
#include "aapl_library.h"
#include "aapl_core.h"
#include "sbus.h"
#include "mdio.h"
#include "gpio_mdio.h"
#include "i2c.h"
#include "serdes_core.h"
#include "spico.h"
#include "pmd.h"
#include "logging.h"
#include "diag_core.h"

#include "sensor.h"
#include "sbm.h"
#include "pmro.h"
#include "aacs_server.h"
#include "serdes_dfe.h"

#include "eye.h"
#include "meas.h"
#include "eye_math.h"
#include "avsp.h"

#endif
