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


/** Doxygen File Header
 ** @file
 ** @brief MDIO related functions.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#if AAPL_ALLOW_MDIO || AAPL_ALLOW_GPIO_MDIO

#define REG_SBUS_CMD         32768
#define REG_SBUS_SA          32769
#define REG_SBUS_DA          32770
#define REG_SBUS_DATA_IN_LO  32771
#define REG_SBUS_DATA_IN_HI  32772
#define REG_SBUS_EXEC        32773
#define REG_SBUS_RESULT      32774
#define REG_SBUS_DATA_OUT_LO 32775
#define REG_SBUS_DATA_OUT_HI 32776


#if AAPL_ALLOW_AACS

/** @cond INTERNAL */

/** @brief Execute an MDIO command using AACS.
 **
 ** @return  0 on success, aapl->return_code (< 0) on failure.
 **/
uint avago_aacs_mdio_fn(
    Aapl_t *aapl,
    Avago_mdio_cmd_t mdio_cmd,
    uint port_addr,
    uint dev_addr,
    uint reg_addr,
    uint data)
{
    uint recv_data_back = FALSE;
    char commandstr[64];
    (void) reg_addr;

    switch( mdio_cmd )
    {
    case AVAGO_MDIO_ADDR: snprintf(commandstr, 64, "mdio a %u %u 0x%x", port_addr, dev_addr, data); break;
    case AVAGO_MDIO_WRITE:snprintf(commandstr, 64, "mdio w %u %u 0x%x", port_addr, dev_addr, data); break;
    case AVAGO_MDIO_READ: snprintf(commandstr, 64, "mdio r %u %u",      port_addr, dev_addr);
                          recv_data_back = TRUE;
                          break;
    case AVAGO_MDIO_WAIT: snprintf(commandstr, 64, "mdio wait %u %u",   port_addr, dev_addr);
                          recv_data_back = TRUE;
                          break;
    }

    avago_aacs_send_command_options(aapl, commandstr, recv_data_back, /* strtol = */ 16);
    return aapl->data;
}
/** @endcond */

#endif

/** @brief   Execute an MDIO command.
 **
 ** @return  0 on success, aapl->return_code (< 0) on failure.
 **/
uint avago_mdio(
    Aapl_t *aapl,               /**< [in] Pointer to AAPL structure */
    Avago_mdio_cmd_t mdio_cmd,  /**< [in] Command type */
    uint port_addr,             /**< [in] Physical port address (aka SBus address) */
    uint dev_addr,              /**< [in] Register address */
    uint data)                  /**< [in] Data to write, ignored for read. */
{
    if( mdio_cmd == AVAGO_MDIO_ADDR )
        aapl->last_mdio_addr[port_addr] = data;

    if( port_addr == AVAGO_BROADCAST )
    {
        uint rc = 0, chip;
        for( chip = 0; chip < aapl->chips; chip ++ )
            rc = avago_mdio(aapl, mdio_cmd, chip, dev_addr, data);
        return rc;
    }

    return aapl->mdio_fn(aapl, mdio_cmd, port_addr + aapl->mdio_base_port_addr, dev_addr, aapl->last_mdio_addr[port_addr], data);
}

/** @brief  Execute an MDIO write operation.
 **
 ** @return Returns 0 on success, aapl->return_code (< 0) on error.
 **/
uint avago_mdio_wr(
    Aapl_t *aapl,       /**< [in] Pointer to AAPL structure */
    uint port_addr,     /**< [in] Physical port address */
    uint dev_addr,      /**< [in] Register address */
    uint reg_addr,      /**< [in] Address to which to write. */
    uint data)          /**< [in] Data to write */
{
           avago_mdio(aapl, AVAGO_MDIO_ADDR, port_addr, dev_addr, reg_addr);
    return avago_mdio(aapl, AVAGO_MDIO_WRITE, port_addr, dev_addr, data);
}

/** @brief   Execute an MDIO read operation.
 ** @return  Return 32 bit data from reg_addr on port_addr.
 **          Sets aapl->return_code and logs an error on failure.
 **/
uint avago_mdio_rd(
    Aapl_t *aapl,       /**< [in] Pointer to AAPL structure */
    uint port_addr,     /**< [in] Physical port address */
    uint dev_addr,      /**< [in] Register address */
    uint reg_addr)      /**< [in] Address from which to read. */
{
           avago_mdio(aapl, AVAGO_MDIO_ADDR, port_addr, dev_addr, reg_addr);
    return avago_mdio(aapl, AVAGO_MDIO_READ, port_addr, dev_addr, 0);
}

/** @cond INTERNAL */

/** @brief   Execute an sbus reset(00), write(01) or read(10) command
 **          via the remote MDIO core interface.
 ** @return  Return 0 on write or reset, 32 bit data on read.
 **          Sets aapl->return_code and logs an error on failure.
 **/
uint avago_mdio_sbus_fn(
    Aapl_t *aapl,               /**< [in] Pointer to AAPL structure */
    uint sbus_addr,             /**< [in] SBus address of SerDes */
    unsigned char reg_addr,     /**< [in] SBus data register address */
    unsigned char command,      /**< [in] SBus command */
    uint *sbus_data)            /**< [in] 32 bit SBus data (if write command) */
{
/*//////////////////////////////////////////////////////////////////////
 * //////////////////////////////////////////////////////////////////////
 */

    int try_count = 0;
    int count = 0;
    int result = 0;
    int limit = aapl->sbus_mdio_timeout;
    uint rc = TRUE;
    Avago_addr_t addr_struct;
    sbus_addr &= 0xffff;
    avago_addr_to_struct(sbus_addr,&addr_struct);

    avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_SA, sbus_addr);
    avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_DA, reg_addr);
    avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_CMD, command | 0x20);

    if (command == 0x01)
    {
        avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_DATA_IN_LO,  (*sbus_data & 0x0000ffff));
        avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_DATA_IN_HI, ((*sbus_data & 0xffff0000) >> 16));
    }

    do
    {
        int prev_result = 0;
        count = 0;

        avago_mdio(aapl, AVAGO_MDIO_ADDR, addr_struct.chip, AVSP_DEVAD, REG_SBUS_RESULT);
        do
        {
            result = avago_mdio(aapl, AVAGO_MDIO_READ, addr_struct.chip, AVSP_DEVAD, 0);
        } while ( (result & 1) == 1 && (++count <= limit));

        prev_result = result & 0x02;

        avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_EXEC, 0x3);

        avago_mdio(aapl, AVAGO_MDIO_ADDR, addr_struct.chip, AVSP_DEVAD, REG_SBUS_RESULT);
        do
        {
            result = avago_mdio(aapl, AVAGO_MDIO_READ, addr_struct.chip, AVSP_DEVAD, 0);
        } while ( (result & 1) == 0 && (++count <= limit));

        if (command == 0x01 || command == 0x00)
        {
            avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_EXEC, 0x2);
            return rc;
        }

        while( count <= limit )
        {
            while( ((result & 2) == prev_result) && (++count <= limit) )
            {
                result = avago_mdio(aapl, AVAGO_MDIO_READ, addr_struct.chip, AVSP_DEVAD, 0);
            }
            if( (result & 0x1c) == 0x10 )
                break;

            aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "MDIO read did not receive a read complete result: 0x%x\n",result);
            prev_result = result & 2;
        }

        avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_EXEC, 0x2);

    } while( count > limit && ++try_count == 1 );

    if (count > limit)
    {
        aapl_fail(aapl, __func__, __LINE__, "SBus %s, MDIO response timed out after %d loops when reading address 0x%x, result = 0x%x.\n", aapl_addr_to_str(sbus_addr), count, reg_addr, result);
        rc = FALSE;
    }
    else
    {
        *sbus_data  =  avago_mdio_rd(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_DATA_OUT_LO) & 0xffff;
        *sbus_data |= (avago_mdio_rd(aapl, addr_struct.chip, AVSP_DEVAD, REG_SBUS_DATA_OUT_HI) & 0xffff) << 16;
    }
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "MDIO loop retries/count/limit = %d/%d/%d\n", try_count, count, limit);

    return rc;
}

/** @endcond */

#endif

