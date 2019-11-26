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
 ** @brief AAPL i2c implementation.
 ** @details This file contains AAPL i2c related function implementations.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"


#if AAPL_ALLOW_I2C || AAPL_ALLOW_SYSTEM_I2C

#define AAPL_LOG_PRINT8 if(aapl->debug >= AVAGO_DEBUG8) aapl_log_printf

/**
 ** @name TWI commands
 **/
#define NOP                 0x00
#define WRITE_SBUS_DEVICE   0x01
#define READ_SBUS_DEVICE    0x02
#define RESET_SBUS_DEVICE   0x03
#define CORE_SBUS_RESET     0x04
#define TWI_REGISTER_0      0x80
/** @} */

/**
 ** @name TWI slave device registers
 **/
#define SBUS_DATA_REG_ADDR  0x00
#define SBUS_DEVICE_ADDR    0x01
#define SBUS_DATA_OUT_0     0x02
#define SBUS_DATA_OUT_1     0x03
#define SBUS_DATA_OUT_2     0x04
#define SBUS_DATA_OUT_3     0x05
#define SBUS_STATUS         0x06
#define SBUS_GP_OUT_0       0x07
#define SBUS_GP_OUT_1       0x08
#define SBUS_GP_OUT_2       0x09
#define SBUS_GP_OUT_3       0x0a
#define SBUS_DATA_IN_0      0x0b
#define SBUS_DATA_IN_1      0x0c
#define SBUS_DATA_IN_2      0x0d
#define SBUS_DATA_IN_3      0x0e
/** @} */

/**
 ** @name Utility macros/defines
 **/
#define OFFSET_BYTE(d,o)        ((d>>(o*8))&0xFF)
#define TO_UPPER(x)             ((x>96) && (x<123) ? (x-32) : x)
#define HEX_TO_NUM(x)           ((x>47) && (x<58) ? (x-48) : (TO_UPPER(x)-55))
#define I2C_SBUS_HEADER_LEN     3
/** @} */

/**
 ** @brief   Read <i>length</i> number of bytes from a specified I2C device.
 ** @details Read a variable number of bytes from an I2C device, blocking until
 ** the requested number of bytes are read from the device.
 **
 ** @return  The number of bytes read (> 0) on success, -1 on failure.
 **/
int avago_i2c_read(
    Aapl_t *aapl,             /**< [in/out] Pointer to AAPL structure. */
    unsigned int dev_addr,    /**< [in] I2C address to read from. */
    unsigned int length,      /**< [in] Number of bytes to read into buffer. */
    unsigned char *buffer)    /**< [out] Pointer to the buffer to store bytes read. */
{
    int read_len;
    if (!aapl->i2c_read_fn)
    {
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "I2C read function function not registered.\n");
        return 0;
    }
    read_len = aapl->i2c_read_fn(aapl, dev_addr, length, buffer);
    if(read_len != (int)length)
        return aapl_fail(aapl,__func__,__LINE__,"i2c read(dev_addr=0x%x,length=%u) failed: returned %d (%s).\n",
            dev_addr, length, read_len, strerror(errno));

    if( aapl->debug >= AVAGO_DEBUG8 )
    {
        int i;
        char data_str[64] = "";
        char *ptr = data_str;
        ptr += sprintf(ptr, "%02x", buffer[0]);
        for( i = 1; i < read_len && ptr <= data_str + sizeof(data_str) - 8; i++ )
            ptr += sprintf(ptr, " %02x", buffer[i]);
        if( i < read_len )
            sprintf(ptr," ...");
        aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "i2c read of %d bytes from 0x%x --> %s\n", length, dev_addr, data_str);
    }
    return read_len;
}

/** @brief   Write <i>length</i> number of bytes to a specified I2C device.
 ** @details Writes variable number of bytes to an I2C device. Will block until
 ** the requested number of bytes are written to the device.
 **
 ** @return  length (>= 0) on success, -1 on failure.
 **/
int avago_i2c_write(
    Aapl_t *aapl,            /**< [in/out] Pointer to AAPL structure. */
    unsigned int dev_addr,   /**< [in] I2C address to write to. */
    unsigned int length,     /**< [in] Number of bytes to write from buffer. */
    unsigned char *buffer)   /**< [in] Pointer to the buffer containing bytes to be written */
                             /**<      to the device. */
{
    int write_len;
    if (!aapl->i2c_write_fn)
    {
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "I2C write function function not registered.\n");
        return 0;
    }
    write_len = aapl->i2c_write_fn(aapl, dev_addr, length, buffer);

    if( write_len != (int)length || aapl->debug >= AVAGO_DEBUG8 )
    {
        unsigned int alloc_len = length * 3 + 10;
        char buf[500];
        char *commandstr = (alloc_len <= sizeof(buf)) ? buf : (char *)aapl_malloc(aapl, alloc_len, __func__);
        char *ptr = commandstr;
        unsigned int i;

        ptr += snprintf(ptr, alloc_len, "i2c w %x", dev_addr);
        for( i = 0; i < length; i++ )
            ptr += snprintf(ptr, alloc_len - (ptr - commandstr), " %02x", buffer[i]);
        if (write_len != (int)length)
        {
            aapl_fail(aapl,__func__,__LINE__,"i2c write failed (%s): %u bytes to addr 0x%x. Data: %s -> %d\n",
                        strerror(errno), length, dev_addr, commandstr, write_len);
        }
        aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "i2c write of %d bytes to addr 0x%x. Data: %s -> %d\n", length, dev_addr, commandstr, write_len);
        if( buf != commandstr )
            aapl_free(aapl, commandstr, __func__);
    }

    return write_len;
}


#if AAPL_ALLOW_AACS

/** @cond INTERNAL */


int avago_aacs_i2c_read_fn(
    Aapl_t *aapl,             /**< [in/out] Pointer to AAPL structure. */
    unsigned int dev_addr,    /**< [in] I2C address to read from. */
    unsigned int length,      /**< [in] Number of bytes to read into buffer. */
    unsigned char *buffer)    /**< [out] Pointer to the buffer to store bytes read. */
{
    char commandstr[64];

    snprintf(commandstr, 64, "i2c r %x %x",  dev_addr, length);

    avago_aacs_send_command_options(aapl, commandstr, /* recv_data_back */ 1, /* strtol = */ 0);

    if( aapl->data > 0 )
    {
        char *pData = aapl->data_char;
        unsigned int i = 0;
        while (*pData != '\0' && i < length)
        {
            buffer[i++] = (HEX_TO_NUM(pData[0])<<4) | HEX_TO_NUM(pData[1]);
            pData += 2;
            while( *pData == ' ' )
                pData++;
        }
    }
    aapl->data = (aapl->data + 1) / 3;

    AAPL_LOG_PRINT8(aapl, AVAGO_DEBUG8, __func__, __LINE__, "%s -> 0x%08x\n", commandstr, aapl->data);
    return aapl->data;
}

int avago_aacs_i2c_write_fn(
    Aapl_t *aapl,            /**< [in/out] Pointer to AAPL structure. */
    unsigned int dev_addr,   /**< [in] I2C address to write to. */
    unsigned int length,     /**< [in] Number of bytes to write from buffer. */
    unsigned char *buffer)   /**< [in] Pointer to the buffer containing bytes to be written */
                             /**<      to the device. */
{
    int write_len = -1;
    unsigned int alloc_len = length * 3 + 10;
    char buf[500];
    char *commandstr = (alloc_len <= sizeof(buf)) ? buf : (char *)aapl_malloc(aapl, alloc_len, __func__);
    char *ptr = commandstr;
    const char *ptr1;
    const char *result;
    unsigned int i;

    ptr += snprintf(ptr, alloc_len, "i2c w %x", dev_addr);
    for( i = 0; i < length; i++ )
        ptr += snprintf(ptr, alloc_len - (ptr - commandstr), " %02x", buffer[i]);

    result = avago_aacs_send_command_options(aapl, commandstr, /* recv_data_back */ 1, /* strtol = */ 0);
    if( 0 == strncmp(result, "Address 0x", 10) && 0 != (ptr1 = strrchr(result,':')) )
        write_len = aapl_strtol(ptr1+1,0,0);

    if( buf != commandstr ) aapl_free(aapl, commandstr, __func__);

    return write_len;
}

/** @endcond */

#endif


#if AAPL_ALLOW_SYSTEM_I2C

int avago_system_i2c_read_fn(
    Aapl_t *aapl,             /**< [in/out] Pointer to AAPL structure. */
    unsigned int dev_addr,    /**< [in] I2C address to read from. */
    unsigned int length,      /**< [in] Number of bytes to read into buffer. */
    unsigned char *buffer)    /**< [out] Pointer to the buffer to store bytes read. */
{
#  ifndef I2C_SLAVE
#    define I2C_SLAVE 0
#  endif
    if (aapl->socket < 0)
    {
        char buf[256];
        snprintf(buf, 256, "to send %d bytes to I2C address %x\n", length, dev_addr);
        if (aapl_reconnect(aapl, buf) < 0) return -1;
    }
    if( ioctl(aapl->socket, I2C_SLAVE, dev_addr) < 0 )
        return aapl_fail(aapl,__func__,__LINE__,"ioctl error: %s, addr 0x%x, read\n", strerror(errno), dev_addr);

    return read(aapl->socket, buffer, length);
}

int avago_system_i2c_write_fn(
    Aapl_t *aapl,            /**< [in/out] Pointer to AAPL structure. */
    unsigned int dev_addr,   /**< [in] I2C address to write to. */
    unsigned int length,     /**< [in] Number of bytes to write from buffer. */
    unsigned char *buffer)   /**< [in] Pointer to the buffer containing bytes to be written */
                             /**<      to the device. */
{
    if (aapl->socket < 0)
    {
        char buf[256];
        snprintf(buf, 256, "to send %d bytes to I2C address %x\n", length, dev_addr);
        if (aapl_reconnect(aapl, buf) < 0) return -1;
    }
    if( ioctl(aapl->socket, I2C_SLAVE, dev_addr) < 0 )
        return aapl_fail(aapl,__func__,__LINE__,"ioctl error: %s, addr 0x%x, bytes %d\n", strerror(errno), dev_addr, length);

    return write(aapl->socket, buffer, length);
}


/** @brief  Initializes i2c access.
 ** @return On success, returns 0.
 ** @return On error, decrements aapl->return_code and returns -1.
 **/
int avago_system_i2c_open_fn(Aapl_t *aapl)
{
    int rc;
    const char *device = AAPL_SYSTEM_I2C_DEVICE;
    aapl->socket = open(device, O_RDWR);
    aapl_log_printf(aapl,AVAGO_DEBUG2,__func__,__LINE__,"open(%s,O_RDWR) = %d\n",device,aapl->socket);

    if( aapl->socket < 0 )
        rc = aapl_fail(aapl,__func__,__LINE__,"Error opening file %s: %s\n",  AAPL_SYSTEM_I2C_DEVICE, strerror(errno));
    else
    {
        struct flock lockinfo;
        lockinfo.l_type = F_WRLCK;
        lockinfo.l_whence = SEEK_SET;
        lockinfo.l_start  = 0;
        lockinfo.l_len    = 0;
        if( 0 != fcntl(aapl->socket, F_SETLKW, &lockinfo) )
            aapl_log_printf(aapl,AVAGO_WARNING,__func__,__LINE__,"Lock on %s failed: %s\n", device, strerror(errno));
        rc = 0;
    }
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "open status = %d\n", rc);
    return rc;
}


/** @brief  Terminates i2c access.
 ** @return On success, returns 0.
 ** @return On error, decrements aapl->return_code and returns -1.
 **/
int avago_system_i2c_close_fn(Aapl_t *aapl)
{
    int rc;
    if( aapl->socket >= 0 )
    {
        rc = close(aapl->socket);
        if( rc != 0 )
            aapl_log_printf(aapl,AVAGO_WARNING,__func__,__LINE__,"close(%d) failed: %s\n",aapl->socket,strerror(errno));
        aapl->socket = -1;
    }
    else
        rc = 0;
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "close status = %d\n", rc);
    return rc;
}

#endif

/** @cond INTERNAL */

/** @brief   Send sbus commands to the specific I2C device.
 ** @details The supported sbus commands are <b>reset</b>, <b>read</b> and <b>write</b>.
 ** The maximum amount of data this function reads from a device is 32 bits.
 **
 ** @return  Data received from device.
 **/
uint avago_i2c_sbus_fn(
    Aapl_t *aapl,            /**< [in/out] Pointer to AAPL structure */
    unsigned int sbus_addr,  /**< [in] Address of the sbus device */
    unsigned char reg_addr,  /**< [in] Address of the register */
    unsigned char command,   /**< [in] Type of command */
    unsigned int *sbus_data) /**< [in] Data to write for a <b>write</b> command */
{
    unsigned char buffer[8] = {0};
    unsigned int i2c_address = aapl->i2c_base_addr;
    int rc = TRUE;

    Avago_addr_t addr_struct;
    sbus_addr &= 0xffff;
    avago_addr_to_struct(sbus_addr,&addr_struct);
    i2c_address += addr_struct.chip;

    if( command == 0 )
    {
        buffer[0] = RESET_SBUS_DEVICE;
        buffer[1] = 0;
        buffer[2] = (unsigned char)addr_struct.sbus;
        buffer[3] = 0;
        buffer[4] = 0;
        buffer[5] = 0;
        buffer[6] = 0;
        avago_i2c_write(aapl, i2c_address, 7, buffer);
    }
    else if( command == 3 )
    {
        int rc_prev = aapl->return_code;
        buffer[0] = CORE_SBUS_RESET;
        buffer[1] = 0;
        buffer[2] = 0;
        buffer[3] = 0;
        buffer[4] = 0;
        buffer[5] = 0;
        buffer[6] = 0;
        avago_i2c_write(aapl, i2c_address, 7, buffer);
        AAPL_SUPPRESS_ERRORS_PUSH(aapl);
        int retry;
        for (retry = 0; retry <= AAPL_I2C_HARD_RESET_TIMEOUT; retry ++)
            if (avago_diag_sbus_rw_test(aapl, avago_make_sbus_controller_addr(sbus_addr), 2)) break;
        aapl->return_code = rc_prev;
        AAPL_SUPPRESS_ERRORS_POP(aapl);
    }
    else if( command == 1 )
    {
        buffer[0] = WRITE_SBUS_DEVICE;
        buffer[1] = reg_addr;
        buffer[2] = (unsigned char)addr_struct.sbus;
        buffer[3] = OFFSET_BYTE(*sbus_data,0);
        buffer[4] = OFFSET_BYTE(*sbus_data,1);
        buffer[5] = OFFSET_BYTE(*sbus_data,2);
        buffer[6] = OFFSET_BYTE(*sbus_data,3);
        avago_i2c_write(aapl, i2c_address, 7, buffer);
    }
    else
    {
        buffer[0] = READ_SBUS_DEVICE;
        buffer[1] = reg_addr;
        buffer[2] = (unsigned char)addr_struct.sbus;
        avago_i2c_write(aapl, i2c_address, 3, buffer);

        if( avago_i2c_read(aapl, i2c_address, 4, buffer) > 0 )
        {
            *sbus_data = (unsigned int)((buffer[3]<<24)|(buffer[2]<<16)|(buffer[1]<<8)|buffer[0]);
        }
        else
            rc = FALSE;
    }

    AAPL_LOG_PRINT8(aapl, AVAGO_DEBUG8, __func__, __LINE__, "%s %02x %02x -> 0x%08x\n", aapl_addr_to_str(sbus_addr), reg_addr, command, sbus_data?*sbus_data:0);
    return rc;
}

/** @endcond */

#endif
