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


/** Doxygen File Header
 ** @file
 ** @brief Logging and core type--string conversion functions.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

/** @defgroup Logging Logging Functions and Types
 ** @{
 **/

/** @brief   Gets a pointer to the contents of the memory log.
 ** @details The memory log pointer is the aapl->log variable.
 **          Any aapl function may invalidate this pointer
 **          so it should be used immediately.
 **          aapl_log_clear() will invalidate this value.
 ** @return  A pointer to the memory log.
 **/
const char *aapl_log_get(
    Aapl_t *aapl)           /**< AAPL structure pointer. */
{
    return aapl->log;
}

/** @brief Clears AAPL's memory log. */
void aapl_log_clear(
    Aapl_t *aapl)           /**< AAPL structure pointer. */
{
    aapl->errors = 0;
    aapl->warnings = 0;
    aapl->last_log = aapl->log;
    aapl->last_err = aapl->log;
    aapl->log_end = aapl->log;
    if( aapl->log )
        aapl->log[0] = '\0';
}

/** @brief   Sets the file path to redirect log messages.
 ** @details aapl->logging_file_path holds the location of the
 **          file in which log messages are redirected.
 **          This feature allows to redirect log to a file
 **          at runtime. To stop redirecting user should call
 **          aapl_stop_file_logging().
 **/
void aapl_start_file_logging(
    Aapl_t *aapl, /**< AAPL structure pointer. */
    const char* filepath)  /**< location of file which contains log */
{
    aapl->logging_file_path = aapl_strdup(filepath);
}

/** @brief Stops logging messages to file. */
void aapl_stop_file_logging(
    Aapl_t *aapl)           /**< AAPL structure pointer. */
{
    if(aapl->logging_file_path)
       AAPL_FREE(aapl->logging_file_path);
    aapl->logging_file_path = NULL;
}

static void aapl_log_vprintf(
    Aapl_t *aapl,
    Aapl_log_type_t log_sel,
    const char *caller,
    int line,
    const char *fmt,
    va_list ap)
{
    char buf[AAPL_LOG_PRINTF_BUF_SIZE];

    int size = vsnprintf(buf, AAPL_LOG_PRINTF_BUF_SIZE, fmt, ap);
    aapl_log_add(aapl, log_sel, buf, caller, line);

    if( size >= (AAPL_LOG_PRINTF_BUF_SIZE - 1) )
    {
        aapl_log_printf(aapl, AVAGO_WARNING, 0, 0, "\n");
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "Output truncated.  Call to aapl_log_printf from %s:%d (log_sel: %s) reached max buffer size (AAPL_LOG_PRINTF_BUF_SIZE=%d). This size may be increased by editing the aapl.h file.\n", caller, line, aapl_log_type_to_str(log_sel), AAPL_LOG_PRINTF_BUF_SIZE);
    }
}

/** @brief Prints the specified message and marks an error.
 **
 ** @return aapl_fail() always returns -1 to indicate an error.
 **/
int aapl_fail(
    Aapl_t *aapl,           /**< AAPL structure pointer. */
    const char *caller,     /**< Caller function, usually __func__ */
    int line,               /**< Caller line number, usually __LINE__ */
    const char *fmt,        /**< Format control string (printf format) */
    ...)                    /**< Format string parameters. */
{
    va_list ap;
    va_start(ap, fmt);
    aapl_log_vprintf(aapl, AVAGO_ERR, caller, line, fmt, ap);
    va_end(ap);

    if( aapl->return_code > 0 )
        aapl->return_code = 0;

    aapl->return_code -= 1;

    return -1;
}

static int check_debug_level(
    Aapl_t *aapl,
    Aapl_log_type_t log_sel)
{
    if( (int) log_sel > (int) (aapl->debug & 0xf) && log_sel < AVAGO_MEM_LOG )
        return 1;
    return 0;
}

/** @brief  Prints message to the specified log.
 ** @details If log_sel is one of the AVAGO_DEBUGn values,
 **  logging only occurs if the aapl->debug field is greater than or equal
 **  to the log_sel value.
 ** @return void
 **/
#ifdef MYD_DEBUG
void aapl_log_printf(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    Aapl_log_type_t log_sel,    /**< [in] Type of message logging. */
    const char *caller,         /**< [in] Caller's __func__ value, or 0. */
    int line,                   /**< [in] Caller's __LINE__ value, or 0. */
    const char *fmt,            /**< [in] printf format string. */
    ...)                        /**< [in] printf arguments. */
{
    va_list ap;
    if( check_debug_level(aapl, log_sel) )
        return;

    va_start(ap, fmt);
    aapl_log_vprintf(aapl, log_sel, caller, line, fmt, ap);
    va_end(ap);
}
#endif
#if !defined __STDC_VERSION__ && !defined __cplusplus
# define USE_VARIABLE_LENGTH_ARRAY 0
#else
# define USE_VARIABLE_LENGTH_ARRAY 1
#endif

/** @brief Add new txt to AAPL's log
 ** @details DEBUG* messages will be sent to AAPL_STREAM (stdout by default, see aapl.h)
 **          and will also be added to the AAPL log if Aapl_t::enable_debug_logging is TRUE.
 **
 ** Condition,                     Action:
 ** When caller == 0 && line == 0, print "string"
 ** When caller == 0 && line >= 1, print "LABEL string"
 ** When caller != 0 && line == 0, print "LABEL function [time_stamp] string"
 ** When caller != 0             , print "LABEL function:line [time_stamp] string"
 ** @return void
 **/
void aapl_log_add(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    Aapl_log_type_t log_sel,    /**< [in] Type of message logging. */
    const char *string,         /**< [in] String to add to the log. */
    const char *caller,         /**< [in] Caller's __func__ value, or 0. */
    int line)                   /**< [in] Caller's __LINE__ value, or 0. */
{
    BOOL is_data_char_log = (log_sel == AVAGO_DATA_CHAR || log_sel == AVAGO_DATA_CHAR_ADD);
    char **log      = is_data_char_log ? &aapl->data_char      : &aapl->log;
    char **log_end  = is_data_char_log ? &aapl->data_char_end  : &aapl->log_end;
    size_t new_item_length, temp_size;

    if (aapl->suppress_errors && (log_sel == AVAGO_WARNING || log_sel == AVAGO_ERR)) log_sel = AVAGO_DEBUG1;
    if (aapl->upgrade_warnings && log_sel == AVAGO_WARNING)
    {
        log_sel = AVAGO_ERR;
        aapl->return_code -= 1;
    }
    if      (log_sel == AVAGO_WARNING) aapl->warnings++;
    else if (log_sel == AVAGO_ERR) aapl->errors++;

    if( check_debug_level(aapl, log_sel) )
        return;

    if( !caller ) caller = "";
    if( !string ) string = "";


    new_item_length = strlen(string);
    temp_size = new_item_length + 64;

    if( *caller )
        temp_size += strlen(caller);

    {
    const char *buf_begin;
#if USE_VARIABLE_LENGTH_ARRAY
    char buf[temp_size];
#else
    char *buf = 0;
#endif

    if( new_item_length > 64 * 1024 )
    {
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "Call to aapl_log_add from %s:%d (log_sel: %d) exceeds recommended max size (%d > %d).\n", caller, line, log_sel, new_item_length, 64 * 1024);
    }

    if( is_data_char_log || (line == 0 && *caller == '\0') )
    {
        if( log_sel == AVAGO_DATA_CHAR )
            *log_end = *log;

        buf_begin = string;
    }
    else
    {
        const char *log_type = aapl_log_type_to_str(log_sel);
        char *buf_end;
#if !USE_VARIABLE_LENGTH_ARRAY
        buf = (char *)aapl_malloc(aapl, temp_size, __func__);
#endif
        buf_begin = buf_end = buf;

        if( *caller )
        {
            buf_end += sprintf(buf_end, "%s (%s:%d", log_type, caller, line);

# ifdef AAPL_LOG_TIME_STAMPS
            if( aapl->log_time_stamps )
                buf_end += aapl_local_strftime(buf_end, 10, " %H:%M:%S");
# endif
            buf_end += sprintf(buf_end, "): ");
        }
        else
            buf_end += sprintf(buf_end, "%s: ", log_type);

        memcpy(buf_end, string, new_item_length);
        buf_end += new_item_length;
        buf_end[0] = '\0';
        new_item_length = buf_end - buf_begin;
    }


#if defined(AAPL_STREAM) || defined(AAPL_STREAM_ERR)
    if( !is_data_char_log )
    {
        const char *color = "";
        #define AAPL_RED         "\x1B[31m"
        #define AAPL_GRN         "\x1B[32m"
        #define AAPL_YEL         "\x1B[33m"
        #define AAPL_BLU         "\x1B[34m"
        #define AAPL_MAG         "\x1B[35m"
        #define AAPL_CYN         "\x1B[36m"
        #define AAPL_WHT         "\x1B[37m"
        #define AAPL_COLOR_RESET "\x1B[0m"

        if (aapl->ansi_colors)
        {
            if      (log_sel == AVAGO_ERR)     color = AAPL_RED;
            else if (log_sel == AVAGO_WARNING) color = AAPL_YEL;
        }
# ifdef AAPL_STREAM
        if( (log_sel == AVAGO_INFO || (uint)log_sel < AVAGO_MEM_LOG) && aapl->enable_stream_logging )
        {
            if ( aapl->logging_file_path != NULL )
            {
                FILE *file = fopen(aapl->logging_file_path, "ab");
                if( file == 0 )
                {
                    aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "Cannot open %s \n", aapl->logging_file_path);
                    return;
                }

                fwrite(buf_begin, 1, new_item_length, file);
                fclose(file);
            }
            else
            {
                int tty = 0;
#if AAPL_ALLOW_ANSI_COLORS
                if (aapl->ansi_colors == 2) tty = 1;
#ifdef WIN32
                else tty = _isatty(_fileno(AAPL_STREAM_ERR));
#else
                else tty = isatty(fileno(AAPL_STREAM_ERR));
#endif
#endif

                if (*color && tty) fwrite(color, 1, strlen(color), AAPL_STREAM);
                fwrite(buf_begin, 1, new_item_length, AAPL_STREAM);
                if (*color && tty) fwrite(AAPL_COLOR_RESET, 1, strlen(AAPL_COLOR_RESET), AAPL_STREAM);
            }
        }
# endif
# ifdef AAPL_STREAM_ERR
        if( (log_sel == AVAGO_ERR || log_sel == AVAGO_WARNING) && aapl->enable_stream_err_logging )
        {
            int tty = 0;
#if AAPL_ALLOW_ANSI_COLORS
            if (aapl->ansi_colors == 2) tty = 1;
#ifdef WIN32
            else tty = _isatty(_fileno(AAPL_STREAM_ERR));
#else
            else tty = isatty(fileno(AAPL_STREAM_ERR));
#endif
#endif
            if (*color && tty) fwrite(color, 1, strlen(color), AAPL_STREAM_ERR);
            fwrite(buf_begin, 1, new_item_length, AAPL_STREAM_ERR);
            if (*color && tty) fwrite(AAPL_COLOR_RESET, 1, strlen(AAPL_COLOR_RESET), AAPL_STREAM_ERR);
        }
# endif
    }
#endif
    MYD_DBG_INFO((char *)buf_begin); /* add logging to MYD */

    if(is_data_char_log)
        aapl_built_in_logging_fn(aapl, log_sel, buf_begin, new_item_length);
    else if(aapl->log_fn && (aapl->enable_debug_logging || (uint)log_sel >= AVAGO_MEM_LOG))
        aapl->log_fn(aapl, log_sel, buf_begin, new_item_length);

#if !USE_VARIABLE_LENGTH_ARRAY
    if( buf ) aapl_free(aapl, buf, __func__);
#endif
    }
}

/** @cond INTERNAL */

/** @brief   Printf append to a dynamically growing buffer.
 ** @details (*buf) must be initialized to a NULL pointer, and
 **          released by calling aapl_free().
 ** @return  void
 **/
void aapl_buf_add(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    char **buf,         /**< [in,out] Pointer to buffer pointer. */
    char **buf_end,     /**< [in,out] Pointer into *buf of where to append. */
    int *size,          /**< [in,out] Pointer to current size of *buf. */
    const char *fmt,    /**< [in] printf format string. */
    ...)                /**< [in] printf format parameters. */
{
    const int min_space = AAPL_LOG_PRINTF_BUF_SIZE;
    const int grow_size = min_space + AAPL_LOG_BUF_SIZE;
    int space_used;
    va_list ap;
    if (!*buf)
    {
        *size = space_used = 0;
        *buf_end = *buf;
    }
    else
        space_used = *buf_end - *buf;

    if ((*size - space_used) < min_space)
    {
        int new_size = space_used + grow_size + 1;
        aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__,
            "Allocating %d additional bytes to user supplied buffer. Size is now %d bytes.\n", new_size - *size, new_size);
        *buf = (char *) aapl_realloc(aapl, *buf, new_size, __func__);
        *size = new_size;
        *buf_end = *buf + space_used;
    }
    va_start(ap, fmt);
    *buf_end += vsnprintf(*buf_end, min_space, fmt, ap);
    va_end(ap);
}

/** @endcond */

/** @} */


/** @defgroup Conversions Type to String and String to Type Conversion Functions
 ** @{
 **/

/** @cond INTERNAL */

/*////////////////////////////////////////////////////////////////////// */


int name_to_index(Aapl_conv_table_t tbl[], const char *name, uint skip_prefix)
{
    int i;
    for( i = 0; tbl[i].name; i++ )
        if( 0==aapl_strcasecmp(name,tbl[i].name) )
            return i;
    if( skip_prefix > 0 )
    {
        for( i = 0; tbl[i].name; i++ )
        {
            if( strlen(tbl[i].name) > skip_prefix &&
                0==aapl_strcasecmp(name,tbl[i].name+skip_prefix) )
                return i;
        }
    }
    return -1;
}

int value_to_index(Aapl_conv_table_t tbl[], int value)
{
    int i;
    for( i = 0; tbl[i].name; i++ )
        if( value == tbl[i].value )
            return i;
    return -1;
}

/** @endcond */


static Aapl_conv_table_t comm_method_table[] =
{
    { "SBUS",                      AVAGO_SBUS                 },
    { "AACS_SBUS",                 AVAGO_SBUS                 },
    { "MDIO",                      AVAGO_MDIO                 },
    { "AACS_MDIO",                 AVAGO_MDIO                 },
    { "I2C",                       AVAGO_I2C                  },
    { "AACS_I2C",                  AVAGO_I2C                  },
    { "SYSTEM_I2C",                AVAGO_SYSTEM_I2C           },
    { "AACS_JTAG",                 AVAGO_JTAG                 },
    { "JTAG",                      AVAGO_JTAG                 },
    { "AACS_BB_JTAG",              AVAGO_BB_JTAG              },
    { "BB_JTAG",                   AVAGO_BB_JTAG              },
    { "BB_GPIO_JTAG",              AVAGO_BB_GPIO_JTAG         },
    { "GPIO_MDIO",                 AVAGO_GPIO_MDIO            },
    { "OFFLINE",                   AVAGO_OFFLINE              },
    { 0,                           0 }
};
/** @brief  Converts an Aapl_comm_method_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_comm_method().
 **/
const char *aapl_comm_method_to_str(Aapl_comm_method_t value)
{
    Aapl_conv_table_t *table = comm_method_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Aapl_comm_method_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_comm_method_to_str().
 **/
BOOL aapl_str_to_comm_method(const char *name, Aapl_comm_method_t *out)
{
    Aapl_conv_table_t *table = comm_method_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Aapl_comm_method_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t log_type_table[] =
{
    { "DEBUG0",         AVAGO_DEBUG0          },
    { "DEBUG1",         AVAGO_DEBUG1          },
    { "DEBUG2",         AVAGO_DEBUG2          },
    { "DEBUG3",         AVAGO_DEBUG3          },
    { "DEBUG4",         AVAGO_DEBUG4          },
    { "DEBUG5",         AVAGO_DEBUG5          },
    { "DEBUG6",         AVAGO_DEBUG6          },
    { "DEBUG7",         AVAGO_DEBUG7          },
    { "DEBUG8",         AVAGO_DEBUG8          },
    { "DEBUG9",         AVAGO_DEBUG9          },
    { "MEM_LOG",        AVAGO_MEM_LOG         },
    { "DATA_CHAR",      AVAGO_DATA_CHAR       },
    { "DATA_CHAR_ADD",  AVAGO_DATA_CHAR_ADD   },
    { "ERROR",          AVAGO_ERR             },
    { "WARNING",        AVAGO_WARNING         },
    { "INFO",           AVAGO_INFO            },
    { 0,                0 }
};
/** @brief  Converts an Aapl_log_type_t value into a string.
 ** @return Returns a string representing the type.
 **/
const char *aapl_log_type_to_str(Aapl_log_type_t value)
{
    Aapl_conv_table_t *table = log_type_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "INVALID";
}

static Aapl_conv_table_t spico_clk_table[] =
{
    { "REFCLK",                   AVAGO_SERDES_SPICO_REFCLK                },
    { "CORE_CLK",                 AVAGO_SERDES_SPICO_PCIE_CORE_CLK         },
    { "PCIE_CORE_CLK",            AVAGO_SERDES_SPICO_PCIE_CORE_CLK         },
    { "TX_F10",                   AVAGO_SERDES_SPICO_TX_F10_CLK_FIXED      },
    { "TX_F40",                   AVAGO_SERDES_SPICO_TX_F40_CLK_FIXED      },
    { "REFCLK_DIV2",              AVAGO_SERDES_SPICO_REFCLK_DIV2           },
    { "CORE_CLK_DIV2",            AVAGO_SERDES_SPICO_PCIE_CORE_CLK_DIV2    },
    { "PCIE_CORE_CLK_DIV2",       AVAGO_SERDES_SPICO_PCIE_CORE_CLK_DIV2    },
    { "TX_F10_DIV2",              AVAGO_SERDES_SPICO_TX_F10_CLK_FIXED_DIV2 },
    { "TX_F40_DIV2",              AVAGO_SERDES_SPICO_TX_F40_CLK_FIXED_DIV2 },
    { "TX_F20",                   AVAGO_SERDES_SPICO_TX_F20_CLK_FIXED      },
    { "TX_F80",                   AVAGO_SERDES_SPICO_TX_F80_CLK_FIXED      },
    { 0,                0 }
};
/** @brief  Converts an Avago_serdes_spico_clk_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_spico_clk().
 **/
const char *aapl_spico_clk_to_str(Avago_serdes_spico_clk_t value)
{
    Aapl_conv_table_t *table = spico_clk_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_spico_clk_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_spico_clk_to_str().
 **/
BOOL aapl_str_to_spico_clk(const char *name, Avago_serdes_spico_clk_t *out)
{
    Aapl_conv_table_t *table = spico_clk_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_spico_clk_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t pll_clk_table[] =
{
    { "REFCLK",             AVAGO_SERDES_TX_PLL_REFCLK             },
    { "RX_DIVX",            AVAGO_SERDES_TX_PLL_RX_DIVX            },
    { "OFF",                AVAGO_SERDES_TX_PLL_OFF                },
    { "PCIE_CORE_CLK",      AVAGO_SERDES_TX_PLL_PCIE_CORE_CLK      },
    { "PCIE_CORE_CLK_DIV2", AVAGO_SERDES_TX_PLL_PCIE_CORE_CLK_DIV2 },
    { 0,                0 }
};
/** @brief  Converts an Avago_serdes_tx_pll_clk_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_pll_clk().
 **/
const char *aapl_pll_clk_to_str(Avago_serdes_tx_pll_clk_t value)
{
    Aapl_conv_table_t *table = pll_clk_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_tx_pll_clk_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_pll_clk_to_str().
 **/
BOOL aapl_str_to_pll_clk(const char *name, Avago_serdes_tx_pll_clk_t *out)
{
    Aapl_conv_table_t *table = pll_clk_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_tx_pll_clk_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t process_id_table[] =
{
    { "PROCESS_A", AVAGO_PROCESS_A },
    { "PROCESS_B", AVAGO_PROCESS_B },
    { "PROCESS_D", AVAGO_PROCESS_D },
    { "PROCESS_E" ,AVAGO_PROCESS_E  },
    { "PROCESS_F", AVAGO_PROCESS_F },
    { "PROCESS_H", AVAGO_PROCESS_H },
    { 0,         0 }
};
/** @brief  Converts an Avago_process_id_t value into a string.
 ** @return Returns a string representing the type.
 **/
const char *aapl_process_id_to_str(Avago_process_id_t value)
{
    Aapl_conv_table_t *table = process_id_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "UNKNOWN_PROCESS";
}

static Aapl_conv_table_t dma_type_table[] =
{
    { "ESB",            AVAGO_ESB           },
    { "ESB_DIRECT",     AVAGO_ESB_DIRECT    },
    { "LSB",            AVAGO_LSB           },
    { "LSB_DIRECT",     AVAGO_LSB_DIRECT    },
    { "DMEM",           AVAGO_DMEM          },
    { "DMEM_PREHALTED", AVAGO_DMEM_PREHALTED},
    { "IMEM",           AVAGO_IMEM          },
    { "BIG_REG_16",     AVAGO_BIG_REG_16    },
    { "BIG_REG_32",     AVAGO_BIG_REG_32    },
    { 0,            0 }
};
/** @brief  Converts an Avago_serdes_mem_type_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_mem_type().
 **/
const char *aapl_mem_type_to_str(Avago_serdes_mem_type_t value)
{
    Aapl_conv_table_t *table = dma_type_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_mem_type_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_mem_type_to_str().
 **/
BOOL aapl_str_to_mem_type(const char *name, Avago_serdes_mem_type_t *out)
{
    Aapl_conv_table_t *table = dma_type_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_mem_type_t)table[index].value;
    return index >= 0;
}

/** @brief   Convert bigint to a string for displaying.
 ** @details Abstract platform dependencies for converting from a bigint
 **          to a string.
 ** @return  The string representation of bigint.
 **/
const char *aapl_bigint_to_str(
    bigint value)    /**< the bigint value to convert */
{
    static char buf[4][24];
    static int which = 0;
    which = (which + 1) % 4;
#ifdef PRId64
    sprintf(buf[which],"%" PRId64,value);
#else
    if( sizeof(bigint) == sizeof(long int) )
        sprintf(buf[which],"%ld",(long int)value);
    else
    #if defined WIN32
        sprintf(buf[which],"%I64d",value);
    #else
        sprintf(buf[which],"%lld",(long long int)value);
    #endif
#endif
    return buf[which];
}

/** @brief  Converts a boolean value into a string.
 ** @return Returns either "TRUE" or "FALSE".
 ** @see    aapl_enable_to_str(), aapl_onoff_to_str().
 **/
const char *aapl_bool_to_str(int value)
{
    return value ? "TRUE" : "FALSE";
}

/** @brief  Converts a boolean value into a string.
 ** @return Returns either "ON" or "OFF".
 ** @see    aapl_bool_to_str(), aapl_enable_to_str().
 **/
const char *aapl_onoff_to_str(int value)
{
    return value ? "ON" : "OFF";
}

/** @brief  Converts a boolean value into a string.
 ** @return Returns either "enabled" or "disabled".
 ** @see    aapl_bool_to_str(), aapl_onoff_to_str().
 **/
const char *aapl_enable_to_str(int value)
{
    return value ? "enabled" : "disabled";
}

static Aapl_conv_table_t data_sel_table[] =
{
    { "LOOPBACK", AVAGO_SERDES_TX_DATA_SEL_LOOPBACK },
    { "CORE",     AVAGO_SERDES_TX_DATA_SEL_CORE     },
    { "PRBS7",    AVAGO_SERDES_TX_DATA_SEL_PRBS7    },
    { "PRBS9",    AVAGO_SERDES_TX_DATA_SEL_PRBS9    },
    { "PRBS11",   AVAGO_SERDES_TX_DATA_SEL_PRBS11   },
    { "PRBS13",   AVAGO_SERDES_TX_DATA_SEL_PRBS13   },
    { "PRBS15",   AVAGO_SERDES_TX_DATA_SEL_PRBS15   },
    { "PRBS23",   AVAGO_SERDES_TX_DATA_SEL_PRBS23   },
    { "PRBS31",   AVAGO_SERDES_TX_DATA_SEL_PRBS31   },
    { "USER",     AVAGO_SERDES_TX_DATA_SEL_USER     },
    { "PMD",      AVAGO_SERDES_TX_DATA_SEL_PMD      },
    { "AN",       AVAGO_SERDES_TX_DATA_SEL_AN       },
    { 0,          0 }
};
/** @brief  Converts an Avago_serdes_tx_data_sel_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_data_sel().
 **/
const char *aapl_data_sel_to_str(Avago_serdes_tx_data_sel_t value)
{
    Aapl_conv_table_t *table = data_sel_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_tx_data_sel_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_data_sel_to_str().
 **/
BOOL aapl_str_to_data_sel(const char *name, Avago_serdes_tx_data_sel_t *out)
{
    Aapl_conv_table_t *table = data_sel_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_tx_data_sel_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t cmp_data_table[] =
{
    { "PRBS7",      AVAGO_SERDES_RX_CMP_DATA_PRBS7     },
    { "PRBS9",      AVAGO_SERDES_RX_CMP_DATA_PRBS9     },
    { "PRBS11",     AVAGO_SERDES_RX_CMP_DATA_PRBS11    },
    { "PRBS13",     AVAGO_SERDES_RX_CMP_DATA_PRBS13    },
    { "PRBS15",     AVAGO_SERDES_RX_CMP_DATA_PRBS15    },
    { "PRBS23",     AVAGO_SERDES_RX_CMP_DATA_PRBS23    },
    { "PRBS31",     AVAGO_SERDES_RX_CMP_DATA_PRBS31    },
    { "OFF",        AVAGO_SERDES_RX_CMP_DATA_OFF       },
    { "SELF_SEED",  AVAGO_SERDES_RX_CMP_DATA_SELF_SEED },
    { 0,            0 }
};
/** @brief  Converts an Avago_serdes_rx_cmp_data_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_cmp_data().
 **/
const char *aapl_cmp_data_to_str(Avago_serdes_rx_cmp_data_t value)
{
    Aapl_conv_table_t *table = cmp_data_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_rx_cmp_data_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_cmp_data_to_str().
 **/
BOOL aapl_str_to_cmp_data(const char *name, Avago_serdes_rx_cmp_data_t *out)
{
    Aapl_conv_table_t *table = cmp_data_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_rx_cmp_data_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t mode_table[] =
{
    { "OFF",         AVAGO_SERDES_RX_CMP_MODE_OFF         },
    { "XOR",         AVAGO_SERDES_RX_CMP_MODE_XOR         },
    { "TEST_PATGEN", AVAGO_SERDES_RX_CMP_MODE_TEST_PATGEN },
    { "MAIN_PATGEN", AVAGO_SERDES_RX_CMP_MODE_MAIN_PATGEN },
    { 0,             0 }
};
/** @brief  Converts an Avago_serdes_rx_cmp_mode_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_cmp_mode().
 **/
const char *aapl_cmp_mode_to_str(Avago_serdes_rx_cmp_mode_t value)
{
    static char buf[16];
    Aapl_conv_table_t *table = mode_table;
    int index = value_to_index(table,value);
    if( index >= 0 )
        return table[index].name;
    snprintf(buf,sizeof(buf),"0x%04x",value);
    return buf;
}
/** @brief  Converts a string into an Avago_serdes_rx_cmp_mode_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_cmp_mode_to_str().
 **/
BOOL aapl_str_to_cmp_mode(const char *name, Avago_serdes_rx_cmp_mode_t *out)
{
    Aapl_conv_table_t *table = mode_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_rx_cmp_mode_t)table[index].value;
    else
    {
        char *endptr = 0;
        Avago_serdes_rx_cmp_mode_t value = (Avago_serdes_rx_cmp_mode_t)aapl_strtol(name,&endptr,16);
        if( endptr && *endptr == '\0' )
        {
            *out = value;
            return TRUE;
        }
    }
    return index >= 0;
}

static Aapl_conv_table_t term_table[] =
{
    { "AVDD",  AVAGO_SERDES_RX_TERM_AVDD  },
    { "FLOAT", AVAGO_SERDES_RX_TERM_FLOAT },
    { "AGND",  AVAGO_SERDES_RX_TERM_AGND  },
    { 0,       0 }
};
/** @brief  Converts an Avago_serdes_rx_term_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_term().
 **/
const char *aapl_term_to_str(Avago_serdes_rx_term_t value)
{
    Aapl_conv_table_t *table = term_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_rx_term_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_term_to_str().
 **/
BOOL aapl_str_to_term(const char *name, Avago_serdes_rx_term_t *out)
{
    Aapl_conv_table_t *table = term_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_rx_term_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t line_encoding_table[] =
{
    { "NRZ",  AVAGO_SERDES_PAM2 },
    { "PAM4", AVAGO_SERDES_PAM4 },
    { "PAM2", AVAGO_SERDES_PAM2 },
    { 0,      0 }
};
/** @brief  Converts an Avago_serdes_line_encoding_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_line_encoding().
 **/
const char *aapl_line_encoding_to_str(Avago_serdes_line_encoding_t value)
{
    Aapl_conv_table_t *table = line_encoding_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_line_encoding_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_line_encoding_to_str().
 **/
BOOL aapl_str_to_line_encoding(const char *name, Avago_serdes_line_encoding_t *out)
{
    Aapl_conv_table_t *table = line_encoding_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_line_encoding_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t dfe_tune_mode_table[] =
{
    { "ICAL",           AVAGO_DFE_ICAL           },
    { "PCAL",           AVAGO_DFE_PCAL           },
    { "ICAL_ONLY",      AVAGO_DFE_ICAL_ONLY      },
    { "START_ADAPTIVE", AVAGO_DFE_START_ADAPTIVE },
    { "STOP_ADAPTIVE",  AVAGO_DFE_STOP_ADAPTIVE  },
    { "ENABLE_RR",      AVAGO_DFE_ENABLE_RR      },
    { "DISABLE_RR",     AVAGO_DFE_DISABLE_RR     },
    { 0,                0 }
};
/** @brief  Converts an Avago_serdes_dfe_tune_mode_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_dfe_tune_mode().
 **/
const char *aapl_dfe_tune_mode_to_str(Avago_serdes_dfe_tune_mode_t value)
{
    Aapl_conv_table_t *table = dfe_tune_mode_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_dfe_tune_mode_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_dfe_tune_mode_to_str().
 **/
BOOL aapl_str_to_dfe_tune_mode(const char *name, Avago_serdes_dfe_tune_mode_t *out)
{
    Aapl_conv_table_t *table = dfe_tune_mode_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_dfe_tune_mode_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t ip_type_table[] =
{
    { "Unused",              AVAGO_UNKNOWN_IP           },
    { "SerDes",              AVAGO_SERDES               },
    { "SBus Controller",     AVAGO_SBUS_CONTROLLER      },
    { "SBus Master SPICO",   AVAGO_SPICO                },
    { "QPI",                 AVAGO_QPI                  },
    { "SerDes Blackhawk",    AVAGO_BLACKHAWK            },
    { "PCS64B66B",           AVAGO_PCS64B66B            },
    { "Auto Negotiation",    AVAGO_AUTO_NEGOTIATION     },
    { "PCS64B66B FEC",       AVAGO_PCS64B66B_FEC        },
    { "PCIe PCS",            AVAGO_PCIE_PCS             },
    { "Core PLL",            AVAGO_CORE_PLL             },
    { "PMRO",                AVAGO_PMRO                 },
    { "DDR address",         AVAGO_DDR_ADDRESS          },
    { "DDR data",            AVAGO_DDR_DATA             },
    { "DDR train",           AVAGO_DDR_TRAIN            },
    { "DDR CTC",             AVAGO_DDR_CTC              },
    { "DDR STOP",            AVAGO_DDR_STOP             },
    { "Thermal Sensor",      AVAGO_THERMAL_SENSOR       },
    { "RMON",                AVAGO_RMON                 },
    { "Link Emulator",       AVAGO_LINK_EMULATOR        },
    { "AVSP Control Logic",  AVAGO_AVSP_CONTROL_LOGIC   },
    { "SerDes M4",           AVAGO_M4                   },
    { "SerDes P1",           AVAGO_P1                   },
    { "MLD",                 AVAGO_MLD                  },
    { "RS FEC Bridge",       AVAGO_RSFEC_BRIDGE         },
    { "Crosspoint",          AVAGO_CROSSPOINT           },
    { "MAX",                 AVAGO_MAX                  },
    { "Thermal Sensor",      AVAGO_SBUS2APB             },

    { "SAPPH GearBox",       AVAGO_SAPPH_GBX            },
    { "SAPPH GearBox Top",   AVAGO_SAPPH_GBX_TOP        },
    { "RSFEC 528",           AVAGO_OPAL_RSFEC528        },
    { "RSFEC 528 544",       AVAGO_OPAL_RSFEC528_544    },
    { "Host Aligner",        AVAGO_OPAL_HOST_ALIGNER    },
    { "Mod Aligner",         AVAGO_OPAL_MOD_ALIGNER     },
    { "Control Logic",       AVAGO_OPAL_CONTROL         },
    { "OSC/SSC PLL",         AVAGO_OSC_SSC_PLL          },
    { "Garnet 25GE Logic",   AVAGO_GARNET_25GE_INTERFACE},
    { "SGMII PCS",           AVAGO_SGMII                },
    { "Avago PHY Controller",AVAGO_APC                  },
    { "MLD RX2",             AVAGO_MLD_RX2              },

    { "Link Emulator",       AVAGO_LINK_EMULATOR_2      },
    { "Super Link Em Packet",AVAGO_SLE_PKT              },
    { "Super Link Emulator", AVAGO_SLE                  },
    { "Padframe Control",    AVAGO_PAD_CONTROL          },

    { "RAM PMRO",            AVAGO_RAM_PMRO             },
    { "Pandora LSB",         AVAGO_PANDORA_LSB          },

    { "SerDes Broadcast",    AVAGO_SERDES_BROADCAST     },
    { 0,                     0 }
};
/** @brief  Converts an Avago_ip_type_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_ip_type().
 **/
const char *aapl_ip_type_to_str(Avago_ip_type_t value)
{
    static char buf[32];
    Aapl_conv_table_t *table = ip_type_table;
    int index = value_to_index(table,value);
    if( index >= 0 )
        return table[index].name;

    snprintf(buf,sizeof(buf),"AVAGO_UNKNOWN_IP (0x%x)",value);
    return buf;
}
/** @brief  Converts a string into an Avago_ip_type_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_ip_type_to_str().
 **/
BOOL aapl_str_to_ip_type(const char *name, Avago_ip_type_t *out)
{
    Aapl_conv_table_t *table = ip_type_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_ip_type_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t clock_table[] =
{
    { "PD",   AVAGO_SERDES_RX_CLOCK_OFF },
    { "iclk", AVAGO_SERDES_RX_CLOCK_I   },
    { "qclk", AVAGO_SERDES_RX_CLOCK_Q   },
    { "rclk", AVAGO_SERDES_RX_CLOCK_R   },
    { 0,      0 }
};
/** @brief  Converts an Avago_serdes_rx_clock_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_rx_clock().
 **/
const char *aapl_rx_clock_to_str(Avago_serdes_rx_clock_t value)
{
    Aapl_conv_table_t *table = clock_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_rx_clock_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_rx_clock_to_str().
 **/
BOOL aapl_str_to_rx_clock(const char *name, Avago_serdes_rx_clock_t *out)
{
    Aapl_conv_table_t *table = clock_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_rx_clock_t)table[index].value;
    return index >= 0;
}

static Aapl_conv_table_t clock_cdc_table[] =
{
    { "DATA",  AVAGO_SERDES_RX_CDC_DATA     },
    { "EDGE",  AVAGO_SERDES_RX_CDC_EDGE     },
    { "~DATA", AVAGO_SERDES_RX_CDC_INV_DATA },
    { "~EDGE", AVAGO_SERDES_RX_CDC_INV_EDGE },
    { "iclk",  AVAGO_SERDES_RX_CDC_ICLK     },
    { "qclk",  AVAGO_SERDES_RX_CDC_QCLK     },
    { "rclk",  AVAGO_SERDES_RX_CDC_RCLK     },
    { "PD",    AVAGO_SERDES_RX_CDC_OFF      },
    { "~iclk", AVAGO_SERDES_RX_CDC_INV_ICLK },
    { "~qclk", AVAGO_SERDES_RX_CDC_INV_QCLK },
    { "~rclk", AVAGO_SERDES_RX_CDC_INV_RCLK },
    { 0,       0 }
};
/** @brief  Converts an Avago_serdes_rx_clock_cdc_t value into a string.
 ** @return Returns a string representing the type.
 ** @see    aapl_str_to_rx_clock_cdc().
 **/
const char *aapl_rx_clock_cdc_to_str(Avago_serdes_rx_clock_cdc_t value)
{
    Aapl_conv_table_t *table = clock_cdc_table;
    int index = value_to_index(table,value);
    return index >= 0 ? table[index].name : "unknown";
}
/** @brief  Converts a string into an Avago_serdes_rx_clock_cdc_t value.
 ** @return Returns TRUE and updates *out if a recognized type string.
 ** @return Returns FALSE if an unrecognized type.
 ** @see    aapl_rx_clock_cdc_to_str().
 **/
BOOL aapl_str_to_rx_clock_cdc(const char *name, Avago_serdes_rx_clock_cdc_t *out)
{
    Aapl_conv_table_t *table = clock_cdc_table;
    int index = name_to_index(table,name,0);
    if( index >= 0 )
        *out = (Avago_serdes_rx_clock_cdc_t)table[index].value;
    return index >= 0;
}

/** @brief  Converts an address number into a printable string.
 ** @return A printable string is returned.
 **/
const char *aapl_addr_to_str(
    uint addr)                  /**< [in] Address number. */
{
#   define NUM_BUFS (5)
    static int which = 0;
    static char num_bufs[NUM_BUFS][20];

    char *buf = num_bufs[which = (which + 1) % NUM_BUFS];
    char *ptr = buf;
    char *end = buf + sizeof(num_bufs[0]);

    Avago_addr_t addr_struct;

    avago_addr_to_struct(addr,&addr_struct);

    if( addr_struct.chip > 0 )
    {
        if( addr_struct.chip == AVAGO_ADDR_BROADCAST )
            ptr += snprintf(ptr,end-ptr,"*:");
        else
            ptr += snprintf(ptr,end-ptr,"%x:",addr_struct.chip);
    }

    if( addr_struct.ring > 0 )
    {
        if( addr_struct.ring == AVAGO_ADDR_BROADCAST )
            ptr += snprintf(ptr,end-ptr,"*");
        else
            ptr += snprintf(ptr,end-ptr,"%x",addr_struct.ring);
    }

    ptr += snprintf(ptr,end-ptr,":%x", addr_struct.sbus);

    if( addr_struct.lane < 8 )
        ptr += snprintf(ptr,end-ptr,".%x", addr_struct.lane);
    else if( addr_struct.lane == AVAGO_ADDR_QUAD_ALL )
        ptr += snprintf(ptr,end-ptr,".*");
    else if( addr_struct.lane == AVAGO_ADDR_QUAD_LOW )
        ptr += snprintf(ptr,end-ptr,".L");
    else if( addr_struct.lane == AVAGO_ADDR_QUAD_HIGH )
        ptr += snprintf(ptr,end-ptr,".H");

    return buf;
}

/** @brief  Converts a string representation of an address into a number.
 ** @return Returns TRUE on successful parsing, FALSE otherwise.
 ** @return If parsing fails, *addr is set to 0.
 **/
BOOL aapl_str_to_addr(
    const char *str,    /**< [in]  String representation of address. */
    char **endptr,      /**< [out] Pointer to the end of the processed string. */
    uint *addr)         /**< [out] Address number. */
{
#if 1
    char *ptr = 0;
    Avago_addr_t addr_struct;
    avago_addr_init(&addr_struct);
    while (str[0] == ' ') str++;
    if( 0 == strchr(str,':') )
    {
        addr_struct.sbus = aapl_strtol(str,&ptr,0);
        if( addr_struct.sbus & ~0x00ff )
            return (*addr = 0), FALSE;
    }
    else
        addr_struct.sbus = aapl_strtol(str,&ptr,16);
    if( str == ptr && *ptr == '*' )
    {
        ptr++;
        addr_struct.sbus = AVAGO_ADDR_BROADCAST;
    }
    if( *ptr == ':' )
    {
        ptr++;
        addr_struct.ring = addr_struct.sbus;
        if( *ptr == '*' )
        {
            ptr++;
            addr_struct.sbus = AVAGO_ADDR_BROADCAST;
        }
        else
            addr_struct.sbus = aapl_strtol(ptr,&ptr,16);
        if( *ptr == ':' )
        {
            ptr++;
            addr_struct.chip = addr_struct.ring;
            addr_struct.ring = addr_struct.sbus;
            if( *ptr == '*' )
            {
                ptr++;
                addr_struct.sbus = AVAGO_ADDR_BROADCAST;
            }
            else
                addr_struct.sbus = aapl_strtol(ptr,&ptr,16);
        }
    }
    if( *ptr == '.' )
    {
        ptr++;
        if(      *ptr == '*'                ) addr_struct.lane = AVAGO_ADDR_QUAD_ALL;
        else if( *ptr == 'l' || *ptr == 'L' ) addr_struct.lane = AVAGO_ADDR_QUAD_LOW;
        else if( *ptr == 'h' || *ptr == 'H' ) addr_struct.lane = AVAGO_ADDR_QUAD_HIGH;
        else if( *ptr >= '0' && *ptr <= '7' ) addr_struct.lane = *ptr - '0';
        else                                  addr_struct.lane = AVAGO_ADDR_IGNORE_LANE;
        ptr++;
    }
    *addr = avago_struct_to_addr(&addr_struct);
    if (endptr) *endptr = ptr;
    return ptr > str;
#else
    char *ptr;
    *addr = aapl_strtol(str,&ptr,0);
    return ptr > str;
#endif
}


void aapl_register_logging_fn(Aapl_t *aapl,
    void (* log_fn)(Aapl_t *, Aapl_log_type_t log_sel, const char * buf, size_t new_item_length),
    int  (* log_open_fn)(Aapl_t *),
    int  (* log_close_fn)(Aapl_t *)
)
{
    aapl_log_printf(aapl, AVAGO_DEBUG6, __func__, __LINE__, "Called %s() registration function.\n", __func__);
    aapl->log_fn = log_fn;
    aapl->log_open_fn = log_open_fn;
    aapl->log_close_fn = log_close_fn;
}


void aapl_built_in_logging_fn(Aapl_t *aapl, Aapl_log_type_t log_sel, const char * buf, size_t new_item_length)
{
    BOOL is_data_char_log = (log_sel == AVAGO_DATA_CHAR || log_sel == AVAGO_DATA_CHAR_ADD);
    char **log      = is_data_char_log ? &aapl->data_char      : &aapl->log;
    char **log_end  = is_data_char_log ? &aapl->data_char_end  : &aapl->log_end;
    int   *log_size = is_data_char_log ? &aapl->data_char_size : &aapl->log_size;

    int current_log_len = *log_end - *log;
    int min_buffer_size = new_item_length + current_log_len + 1;
    int allocated = 0, wasted = 0;

    if( min_buffer_size > *log_size )
    {
        int new_buffer_size = min_buffer_size + current_log_len * 2;
        *log = (char *) aapl_realloc(aapl, *log, new_buffer_size, __func__);
        if( !*log ) { *log_size = 0; return; }
        *log_end = *log + current_log_len;
        *log_size = new_buffer_size;
        allocated = 1;
    }
    else if( (*log_size - min_buffer_size) > (current_log_len * 2 + min_buffer_size + AAPL_LOG_BUF_SIZE) )
    {
        *log = (char *) aapl_realloc(aapl, *log, min_buffer_size + AAPL_LOG_BUF_SIZE, __func__);
        if( !*log ) return;
        *log_end = *log + current_log_len;
        *log_size = min_buffer_size + AAPL_LOG_BUF_SIZE;
        wasted = 1;
    }

    aapl->last_log = *log_end;
    if (log_sel == AVAGO_WARNING || log_sel == AVAGO_ERR) aapl->last_err = *log_end;

    memcpy(*log_end, buf, new_item_length);
    *log_end += new_item_length;
    (*log_end)[0] = '\0';

    if (allocated)
    {
        if (is_data_char_log)
            aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Allocating %d additional bytes to data_char log. Size is now %d bytes.\n", *log_size - current_log_len, *log_size);
        else
            aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Allocating %d additional bytes to AAPL log. Size is now %d bytes.\n", *log_size - current_log_len, *log_size);
    }
    else if (wasted)
    {
        if (is_data_char_log)
            aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Wasted %d bytes in data_char log. Buffer resized to %d bytes.\n", *log_size - min_buffer_size, min_buffer_size + AAPL_LOG_BUF_SIZE);
        else
            aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Wasted %d bytes in AAPL log. Buffer resized to %d bytes.\n", *log_size - min_buffer_size, min_buffer_size + AAPL_LOG_BUF_SIZE);
    }
}
/** @} */

