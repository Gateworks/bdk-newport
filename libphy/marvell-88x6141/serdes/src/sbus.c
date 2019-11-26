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
 ** @brief SBus functions.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#define AAPL_LOG_PRINT8 if(aapl->debug >= AVAGO_DEBUG8) aapl_log_printf
#define AAPL_LOG_PRINT9 if(aapl->debug >= AVAGO_DEBUG9) aapl_log_printf

#if AAPL_ALLOW_OFFLINE_SBUS

/** @cond INTERNAL */

uint avago_offline_sbus_fn(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,         /**< [in] SBus slice address. */
    unsigned char reg_addr, /**< [in] SBus register to read/write */
    unsigned char command,  /**< [in] 0=reset, 1=write, 2=read */
    uint *sbus_data)        /**< [in] Data to write */
{
    uint data = 0;
    uint index;
    Avago_addr_t addr_struct;
    avago_addr_to_struct(sbus_addr,&addr_struct);

    if( !aapl->offline_sbus_reg )
    {
        uint chip, reg_addr;
        int size = AAPL_MAX_CHIPS*AAPL_MAX_RINGS*256*256*sizeof(int);
        aapl->offline_sbus_reg = (int *)AAPL_MALLOC(size);
        if( aapl->offline_sbus_reg )
        {
            memset(aapl->offline_sbus_reg,0,size);
        }
        for (chip = 0; chip < AAPL_MAX_CHIPS; chip++)
        {
            uint ring;
            for (ring = 0; ring < AAPL_MAX_RINGS; ring++)
            {
                uint max_ip_address = 5;
                uint sbus = AVAGO_SBUS_CONTROLLER_ADDRESS;

                reg_addr = 0x2;
                index = ((chip * AAPL_MAX_RINGS + ring) * 256 + sbus) * 256 + reg_addr;
                if (chip == 0) aapl->offline_sbus_reg[index] = max_ip_address + 1;
                else           aapl->offline_sbus_reg[index] = 0x2 + 1;

                for (sbus = 1; sbus <= max_ip_address; sbus ++)
                {
                    reg_addr = 0xff;
                    index = ((chip * AAPL_MAX_RINGS + ring) * 256 + sbus) * 256 + reg_addr;
                    aapl->offline_sbus_reg[index] = AVAGO_SERDES;
                }

                sbus = AVAGO_SBUS_CONTROLLER_ADDRESS;
                reg_addr = 0xff;
                index = ((chip * AAPL_MAX_RINGS + ring) * 256 + sbus) * 256 + reg_addr;
                aapl->offline_sbus_reg[index] = AVAGO_SBUS_CONTROLLER;

                sbus = AVAGO_SBUS_CONTROLLER_ADDRESS;
                reg_addr = 0xfe;
                index = ((chip * AAPL_MAX_RINGS + ring) * 256 + sbus) * 256 + reg_addr;
                aapl->offline_sbus_reg[index] = 0xbe;

                sbus = AVAGO_SBUS_MASTER_ADDRESS;
                reg_addr = 0xff;
                index = ((chip * AAPL_MAX_RINGS + ring) * 256 + sbus) * 256 + reg_addr;
                aapl->offline_sbus_reg[index] = AVAGO_SPICO;
            }
        }
    }

    index = ((addr_struct.chip * AAPL_MAX_RINGS + addr_struct.ring) * 256 + addr_struct.sbus) * 256 + reg_addr;

    aapl_log_printf(aapl, AVAGO_DEBUG9, 0,0,"OFFLINE: index=%x, %s, %x, %x, %x\n", index, aapl_addr_to_str(sbus_addr), reg_addr, command, *sbus_data);


    if      (command == 0x01) data = aapl->offline_sbus_reg[index] = *sbus_data;
    else if (command == 0x02) data = aapl->offline_sbus_reg[index];


    *sbus_data = data;
    return TRUE;
}

/** @brief Opens communcation for the offline sbus communication method. */
int avago_offline_open_fn(
    Aapl_t *aapl) /**< [in] Pointer to Aapl_t structure. */
{
    (void)aapl;
    return 0;
}
/** @brief Closes communcation for the offline sbus communication method. */
int avago_offline_close_fn(
    Aapl_t *aapl) /**< [in] Pointer to Aapl_t structure. */
{
    (void)aapl;
    return 0;
}

/** @endcond */

#endif


/** @brief   Execute an sbus command.
 ** @details Lowest level SBus function.  Allows the user to fully specify
 **          all fields in the sbus command.  Generally, one should use
 **          sbus_rd, sbus_wr and sbus_rmw instead of sbus.
 ** @return  For reads, returns read data.
 **          For writes and reset, returns 0.
 **/
uint avago_sbus(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,         /**< [in] SBus slice address. */
    unsigned char reg_addr, /**< [in] SBus register to read/write */
    unsigned char command,  /**< [in] 0=reset, 1=write, 2=read */
    uint sbus_data,         /**< [in] Data to write */
    int recv_data_back)     /**< [in] Allows AACS protocol optimization. */
{
    Avago_addr_t addr_struct;

    if (aapl_reconnect(aapl, __func__) < 0) return -1;

    sbus_addr &= 0xffff;
    avago_addr_to_struct(sbus_addr,&addr_struct);
    sbus_data &= 0xffffffff;

    if( addr_struct.chip == AVAGO_BROADCAST )
    {
        uint data = 0;
        Avago_addr_t a_struct = addr_struct;
        for( a_struct.chip = 0; a_struct.chip < aapl->chips; a_struct.chip++ )
            data = avago_sbus(aapl, avago_struct_to_addr(&a_struct), reg_addr, command, sbus_data, recv_data_back);
        return data;
    }
    if( addr_struct.ring == AVAGO_BROADCAST )
    {
        uint data = 0;
        Avago_addr_t a_struct = addr_struct;
        for( a_struct.ring = 0; a_struct.ring < AAPL_MAX_RINGS; a_struct.ring++ )
        {
            if( aapl->max_sbus_addr[a_struct.chip][a_struct.ring] != 0 )
                data = avago_sbus(aapl, avago_struct_to_addr(&a_struct), reg_addr, command, sbus_data, recv_data_back);
        }
        return data;
    }

    {
    char sbus_cmd[AAPL_SBUS_CMD_LOG_BUF_SIZE+1];
    AAPL_SBUS_LOCK;

    snprintf(sbus_cmd, AAPL_SBUS_CMD_LOG_BUF_SIZE, "sbus %x%x%02x %02x %02x 0x%08x",
        addr_struct.chip, addr_struct.ring, addr_struct.sbus & 0xff, reg_addr, command, sbus_data);

    if( !aapl->max_sbus_addr[addr_struct.chip][addr_struct.ring] )
    {
        aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__,
            "SBus command (%s) destined for SBus address %s sent to ring %d which may not exist.\n",
            sbus_cmd, aapl_addr_to_str(sbus_addr), addr_struct.ring);
    }

    if (sbus_addr == 0xfe && reg_addr == 0x00 && (command & 0x3) == 1 && sbus_data == 0x81) recv_data_back = 1;
#if AAPL_ALLOW_THREADED_SBUS
    if (!aapl->debug)
    {
        if (!aapl->sbus_thread) pthread_create(&aapl->sbus_thread, NULL, &aapl_sbus_thread_worker, (void *)aapl);
        while (aapl->sbus_execute) {}
        aapl->sbus_sa = sbus_addr;
        aapl->sbus_da = reg_addr;
        aapl->sbus_cmd = command;
        aapl->sbus_data = sbus_data;
        aapl->sbus_recv_data_back = recv_data_back;
        __sync_synchronize();
        aapl->sbus_execute = 1;

        if (recv_data_back)
        {
            while (aapl->sbus_execute) { }
            sbus_data = aapl->sbus_data;
        }
    }
    else
#endif
    {
        uint rc = 0;
        if (aapl->sbus_fn)        rc = aapl->sbus_fn(aapl, sbus_addr, reg_addr, command, &sbus_data);
        else if (aapl->sbus_fn_2) rc = aapl->sbus_fn_2(aapl, sbus_addr, reg_addr, command, &sbus_data, recv_data_back);
        else aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "SBus function function not registered.\n");

        if (!rc) aapl_fail(aapl, __func__, __LINE__, "SBus function (0x%lx) failed.\n", (fn_cast_t)aapl->sbus_fn);
    }

    if( recv_data_back <= 1 )
        AAPL_LOG_PRINT8(aapl, AVAGO_DEBUG8, __func__, __LINE__, "%s -> 0x%08x\n", sbus_cmd, sbus_data);
    aapl->sbus_commands++;
    AAPL_SBUS_UNLOCK;
    return sbus_data;
    }
}

#if AAPL_ALLOW_THREADED_SBUS
void *aapl_sbus_thread_worker(void *aapl_in)
{
    Aapl_t *aapl = (Aapl_t *) aapl_in;
    uint data;
    while (1)
    {
        if (aapl->sbus_execute)
        {
            uint rc = 0;
            aapl->sbus_execute ++;
            data = aapl->sbus_data;
            if (aapl->sbus_fn)        rc = aapl->sbus_fn(aapl, aapl->sbus_sa, aapl->sbus_da, aapl->sbus_cmd, &data);
            else if (aapl->sbus_fn_2) rc = aapl->sbus_fn_2(aapl, aapl->sbus_sa, aapl->sbus_da, aapl->sbus_cmd, &data, aapl->sbus_recv_data_back);
            else aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "SBus function function not registered.\n");

            AAPL_LOG_PRINT8(aapl, AVAGO_DEBUG8, __func__, __LINE__, "%s -> 0x%08x\n", aapl->sbus_cmd, data);
            aapl->sbus_commands++;

            aapl->sbus_data = data;
            if (!rc) aapl_fail(aapl, __func__, __LINE__, "SBus function (0x%lx) failed.\n", (fn_cast_t)aapl->sbus_fn);
            aapl->sbus_execute = 0;
        }
        else if (aapl->destroy_thread) break;
        else if (aapl->debug) {aapl->sbus_thread = 0; break;}
    }
    return NULL;
}
#endif


/** @brief  SBus read operation
 ** @return Returns the result of the read operation.
 **/
uint avago_sbus_rd(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,         /**< [in] SBus slice address. */
    unsigned char reg_addr) /**< [in] Register to read */
{
    if (aapl->aacs == 1)
    {
        uint data;
        AAPL_SUPPRESS_ERRORS_PUSH(aapl);
        data = avago_sbus(aapl, sbus_addr, reg_addr, 0x02, 0x00000000, /* recv_data_back */ 1);
        AAPL_SUPPRESS_ERRORS_POP(aapl);
        if ((strstr(aapl->data_char, "WARNING") || strstr(aapl->data_char, "ERROR")))
        {
            aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "SBus read failure reading from SBus: %s addr: 0x%02x (%s). Attempting a second sbus read...\n", aapl_addr_to_str(sbus_addr), reg_addr, aapl->data_char);
            data = avago_sbus(aapl, sbus_addr, reg_addr, 0x02, 0x00000000, /* recv_data_back */ 1);
        }
        return data;
    }
    else
        return avago_sbus(aapl, sbus_addr, reg_addr, 0x02, 0x00000000, /* recv_data_back */ 1);
}

/** @brief  Reads multiple registers from a single SBus device.
 ** @return Returns 0 and places the results of the read operations in sbus_data[].
 **/
uint avago_sbus_rd_array(
    Aapl_t *aapl,                   /**< [in] Pointer to Aapl_t structure. */
    uint addr,                      /**< [in] SBus slice address. */
    uint count,                     /**< [in] Number of registers to read. */
    const unsigned char *reg_addr,  /**< [in] Register addresses to read. */
    uint sbus_data[])               /**< [out] Array into which to place register values. */
{
    uint i;
    if( (uint)aapl->max_cmds_buffered < count+aapl->cmds_buffered )
    {
        for( i = 0; i < count; i++ )
            sbus_data[i] = avago_sbus_rd(aapl, addr, reg_addr[i]);
        return 0;
    }

    for( i = 0; i < count-1; i++ )
        sbus_data[i] = avago_sbus(aapl, addr, reg_addr[i], 0x02, 0x00000000, /* recv_data_back */ 2);
    sbus_data[i] = avago_sbus(aapl, addr, reg_addr[i], 0x02, 0x00000000, /* recv_data_back */ 3);

#if AAPL_ALLOW_AACS
    if( aapl->sbus_fn_2 == &aapl_aacs_sbus_fn )
    {
        char *ptr = aapl->data_char;
        while( *ptr == ';' )
            ptr++;
        for( i = 0; i < count; i++ )
        {
            sbus_data[i] = aapl_strtol(ptr, &ptr, 2);
            ptr++;
            AAPL_LOG_PRINT8(aapl, AVAGO_DEBUG8, __func__, __LINE__, "sbus %04x %2x 02 0x00000000 -> 0x%08x\n", addr, reg_addr[i], sbus_data[i]);
        }
    }
#endif
    return 0;
}

/** @brief  SBus write operation
 ** @return Returns the result of the avago_sbus() write function, which should generally be ignored.
 **/
uint avago_sbus_wr(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,         /**< [in] SBus slice address. */
    unsigned char reg_addr, /**< [in] Register to update */
    uint sbus_data)         /**< [in] Data to write */
{
    return avago_sbus(aapl, sbus_addr, reg_addr, 0x01, sbus_data, 0);
}

/** @brief  SBus write operation with flush
 ** @return Returns the result of the avago_sbus() write function, which should generally be ignored.
 **/
uint avago_sbus_wr_flush(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,         /**< [in] SBus slice address. */
    unsigned char reg_addr, /**< [in] Register to update */
    uint sbus_data)         /**< [in] Data to write */
{
    return avago_sbus(aapl, sbus_addr, reg_addr, 0x01, sbus_data, 1);
}

/** @brief  Modify some bits in an existing SBus register
 ** @return Returns the initial value of the SBus register before it was modified.
 **/
uint avago_sbus_rmw(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,         /**< [in] SBus slice address. */
    unsigned char reg_addr, /**< [in] Register to update */
    uint sbus_data,         /**< [in] Data to write */
    uint mask)              /**< [in] Bits in existing data to modify */
{


    uint initial_value = avago_sbus_rd(aapl, sbus_addr, reg_addr);
    avago_sbus_wr(aapl, sbus_addr, reg_addr, (sbus_data & mask) | (initial_value & ~mask));
    return initial_value;
}

#if AAPL_ALLOW_JTAG || AAPL_ALLOW_AACS
/** @cond INTERNAL */
static uint get_sbus_reset_bit(int tap_gen)
{
    if      (tap_gen == 1) return 46;
    else if (tap_gen == 2) return 46;
    else if (tap_gen == 3) return 47;
    else /*if (tap_gen == 4)*/ return 46;
}

static uint get_sbus_core_sbus_override(int tap_gen)
{
    if      (tap_gen == 1) return 47;
    else if (tap_gen == 2) return 48;
    else if (tap_gen == 3) return 49;
    else /*if (tap_gen == 4)*/ return 48;
}

static void send_read_to_all_rings(
    Aapl_t *aapl,
    uint sbus_addr_in      /**< [in] SBus slice address. */
)
{
    uint ring;
    for (ring = 0; ring < aapl->sbus_rings; ring++)
    {
        Avago_addr_t addr_struct;
        avago_addr_to_struct(avago_make_sbus_master_addr(sbus_addr_in), &addr_struct);
        addr_struct.ring = ring;
        avago_sbus_rd(aapl, avago_struct_to_addr(&addr_struct), 0x2);
    }
}

/** @brief Internal function to set SBus reset override signals */
void aapl_set_sbus_tap_reset_sel(Aapl_t *aapl, uint chip, uint override)
{
    if(!aapl->aacs && !aapl_is_jtag_communication_method(aapl)) return;

    aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "HS1 reset override set to: %d.\n", override);

    AAPL_SUPPRESS_ERRORS_PUSH(aapl);
    if (aapl_is_jtag_communication_method(aapl))
    {
        aapl->sbus_reg[126-48-1] = '1';
        avago_sbus_rd(aapl, avago_make_addr3(chip, 0, 0xfe), 0x2);
    }
    else
    {
        uint tap_gen = avago_get_tap_gen(aapl);
        char hs1_mode[64];
        char set_sbus[32];
        uint sbus_bit = 49;
        Aapl_comm_method_t comm_method;

        snprintf (hs1_mode, 64, "sbus_mode %s", avago_aacs_send_command(aapl, "sbus_mode"));
        {
            char *ptr = strstr(hs1_mode," I2C");
            if( ptr ) *ptr = '\0';
        }
        comm_method = aapl->communication_method;
        aapl->communication_method = AVAGO_SBUS;
        avago_aacs_send_command(aapl, "sbus_mode jtag");

        sbus_bit = get_sbus_core_sbus_override(tap_gen);
        snprintf(set_sbus, 32, "set_sbus %u %d", sbus_bit, override);
        avago_aacs_send_command(aapl, set_sbus);

        sbus_bit = get_sbus_reset_bit(tap_gen);
        snprintf(set_sbus, 32, "set_sbus %u %d", sbus_bit, 0);
        avago_aacs_send_command(aapl, set_sbus);

        avago_sbus_rd(aapl, avago_make_addr3(chip, 0, 0xfe), 0x2);

        avago_aacs_send_command(aapl, hs1_mode);
        aapl->communication_method = comm_method;
    }
    AAPL_SUPPRESS_ERRORS_POP(aapl);
}
/** @endcond */
#endif


/** @brief   Performs an sbus reset action.
 ** @details NOTE: When 0xff is used as the input address, all IP types are reset (not just SerDes)
 **
 ** @return  void
 **/
void avago_sbus_reset(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr_in,      /**< [in] SBus slice address. */
    int hard)
{
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;

    if( hard )
    {
        aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Hard SBus reset called to address 0x%x\n", sbus_addr_in);

#if AAPL_ALLOW_JTAG || AAPL_ALLOW_AACS
        if (aapl_is_jtag_communication_method(aapl))
        {
            uint tap_gen = avago_get_tap_gen(aapl);
            uint sbus_bit = get_sbus_reset_bit(tap_gen);
            AAPL_SUPPRESS_ERRORS_PUSH(aapl);
            aapl->sbus_reg[126-sbus_bit-1] = '1';
            send_read_to_all_rings(aapl, sbus_addr_in);
            aapl->sbus_reg[126-sbus_bit-1] = '0';
            send_read_to_all_rings(aapl, sbus_addr_in);
            AAPL_SUPPRESS_ERRORS_POP(aapl);
        }
#endif

#if AAPL_ALLOW_AACS
        if (aapl->capabilities & AACS_SERVER_SBUS_RESET)
        {
            char cmd[64];
            snprintf(cmd, 63, "sbus_reset 0x%x", sbus_addr_in);
            avago_aacs_send_command(aapl, cmd);
        }
        else if(aapl_is_aacs_communication_method(aapl))
        {
            AAPL_SUPPRESS_ERRORS_PUSH(aapl);
            Aapl_comm_method_t comm_method;
            char hs1_mode[64];
            char set_sbus[32];
            uint tap_gen = avago_get_tap_gen(aapl);
            uint sbus_bit = get_sbus_reset_bit(tap_gen);

            snprintf (hs1_mode, 64, "sbus_mode %s", avago_aacs_send_command(aapl, "sbus_mode"));
            {
                char *ptr = strstr(hs1_mode," I2C");
                if( ptr )
                    *ptr = '\0';
            }
            comm_method = aapl->communication_method;
            aapl->communication_method = AVAGO_SBUS;
            avago_aacs_send_command(aapl, "sbus_mode jtag");

            snprintf(set_sbus, 32, "set_sbus %u %d", sbus_bit, 1);
            avago_aacs_send_command(aapl, set_sbus);
            send_read_to_all_rings(aapl, sbus_addr_in);

            snprintf(set_sbus, 32, "set_sbus %u %d", sbus_bit, 0);
            avago_aacs_send_command(aapl, set_sbus);
            send_read_to_all_rings(aapl, sbus_addr_in);

            avago_aacs_send_command(aapl, hs1_mode);
            aapl->communication_method = comm_method;
            AAPL_SUPPRESS_ERRORS_POP(aapl);
        }
#endif

#if AAPL_ALLOW_MDIO || AAPL_ALLOW_GPIO_MDIO
        if(aapl_is_mdio_communication_method(aapl))
        {
            int prev_timeout;
            uint reset_val;

            avago_addr_to_struct(sbus_addr_in, &addr_struct);

            reset_val = avago_mdio_rd(aapl, addr_struct.chip, AVSP_DEVAD, AVAGO_MDIO_REG_RESET);

            aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Initial MDIO reset reg: 0x%0x\n", reset_val);

            reset_val &= 0x1;
            reset_val |= (reset_val << 1);

            reset_val ^= 3;

            prev_timeout = aapl->sbus_mdio_timeout;
            avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, AVAGO_MDIO_REG_RESET, 0x0100 | reset_val);
            avago_mdio_wr(aapl, addr_struct.chip, AVSP_DEVAD, AVAGO_MDIO_REG_RESET, 0x0100 | (reset_val ^ 3));
            aapl->sbus_mdio_timeout = 10000;

            AAPL_SUPPRESS_ERRORS_PUSH(aapl);
            avago_sbus_rd(aapl, avago_make_sbus_controller_addr(sbus_addr_in), 0xfe);
            AAPL_SUPPRESS_ERRORS_POP(aapl);
            aapl->sbus_mdio_timeout = prev_timeout;

            aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Final MDIO reset reg: 0x%0x\n", 0x0100 | (reset_val ^ 3));
        }
        else
#endif
#if AAPL_ALLOW_I2C || AAPL_ALLOW_SYSTEM_I2C
        if(aapl_is_i2c_communication_method(aapl))
        {
            aapl->sbus_fn(aapl, sbus_addr_in, 0, 3, 0);
        }
        else
#endif
        if (!aapl_is_aacs_communication_method(aapl) && !aapl_is_jtag_communication_method(aapl))
        {
            aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "Hard reset not implemented, using soft SBus reset instead.\n");
            hard = 0;
        }
    }

    if (hard) sbus_addr_in = avago_make_serdes_broadcast_addr(sbus_addr_in);

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "SBus %s, Soft SBus reset called\n", aapl_addr_to_str(sbus_addr_in));

    avago_addr_to_struct(sbus_addr_in, &addr_struct);
    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next, AAPL_BROADCAST_IGNORE_LANE);
         st;
         st = aapl_broadcast_next(aapl, &next, &start, &stop, AAPL_BROADCAST_IGNORE_LANE) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);

        if( aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_UNKNOWN_IP) )
            continue;

        if (!hard)
        {
            if (aapl_check_process(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_PROCESS_B) && aapl_get_ip_type(aapl, sbus_addr) == AVAGO_SERDES)
                avago_sbus_wr(aapl, sbus_addr, 0xff, 0x0);
            avago_sbus(aapl, sbus_addr, 0x00, 0x00, 0x00, 1);
        }

        if( aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SERDES) &&
            aapl_check_process(aapl, sbus_addr, __func__, __LINE__, FALSE, 3, AVAGO_PROCESS_E, AVAGO_PROCESS_B, AVAGO_PROCESS_F) )
        {
            avago_sbus_wr(aapl, sbus_addr, 0x01, 0x20000000);
        }
    }
    if (sbus_addr_in == AVAGO_BROADCAST && !hard)
    {
        avago_sbus(aapl, avago_make_sbus_master_addr(sbus_addr_in), 0x00, 0x00, 0x00, 1);
        avago_sbus(aapl, avago_make_sbus_controller_addr(sbus_addr_in), 0x00, 0x00, 0x00, 1);
    }
}

/** @brief   Performs a read-write test to the SBus Controller or SerDes
 ** @details If sbus_addr is 0 or points to an SBus controller the test will
 **          Communicate with the SBus Controller (sbus address 0xfd),
 **          otherwise it will run on any specified SerDes SBus address.
 ** @return  TRUE if the test passes, FALSE if any errors.
 **/
BOOL avago_diag_sbus_rw_test(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint sbus_addr,     /**< [in] SBus slice address. */
    int cycles)         /**< [in] Number of write-read cycles to do. */
{
    Avago_addr_t addr_struct;
    int result = TRUE, addr, data_addr, mask, rev = 0, data2 = 0, ran, data = 0, prev = 0, x;

    avago_addr_to_struct(sbus_addr, &addr_struct);

    if (addr_struct.sbus != AVAGO_SBUS_CONTROLLER_ADDRESS &&
        (!aapl->ip_type[AAPL_3D_ARRAY_ADDR(addr_struct)] ||
         (aapl_get_ip_type(aapl, sbus_addr) != AVAGO_SERDES &&  aapl_get_ip_type(aapl, sbus_addr) != AVAGO_M4 )))
    {
        aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "%s requested on SBus address %s, which doesn't support the r/w test. Testing using SBus address %s instead.\n",
            __func__, aapl_addr_to_str(sbus_addr), aapl_addr_to_str(avago_make_sbus_controller_addr(sbus_addr)));
        sbus_addr = avago_make_sbus_controller_addr(sbus_addr);
    }

    avago_addr_to_struct(sbus_addr, &addr_struct);

    if (addr_struct.sbus == 0 || addr_struct.sbus == AVAGO_SBUS_CONTROLLER_ADDRESS)
    {
        addr = avago_make_sbus_controller_addr(sbus_addr);
        mask = 0xffffffff;
        data_addr = 0x13;
    }
    else
    {
        addr = sbus_addr;
        mask = 0xffff;
        data_addr = 0x26;
    }

    AAPL_SUPPRESS_ERRORS_PUSH(aapl);
    {
        int orig_val = avago_sbus_rd(aapl, addr, data_addr);

        ran = 0x1678ab4a;
        ran ^= (size_t) &ran;
        for( x=1; x <= cycles; x++ )
        {
            ran = (ran << 1) | (((ran >> 0) ^ (ran >> 6)) & 0x1);
            ran &= mask;
            avago_sbus_wr(aapl, addr, data_addr, ran);
            data = avago_sbus_rd(aapl, addr, data_addr) & mask;
            if (data != ran)
            {
                rev = avago_sbus_rd(aapl, addr, 0xff);
                data2 = avago_sbus_rd(aapl, addr, data_addr) & mask;
                result = FALSE;
                if (!(aapl->debug & AAPL_DEBUG_SBUS_RW_TEST)) break;

                aapl->suppress_errors -= 1;
                aapl_fail(aapl, __func__, __LINE__, "SBus read/write test failed on address %s in test loop %d. Expected 0x%08x, but got 0x%08x, re-read: 0x%08x. Previous data written was: 0x%08x. Reg 0xff: 0x%08x\n", aapl_addr_to_str(addr), x, ran, data, data2, prev, rev);
                aapl->suppress_errors += 1;
            }
            if (x % 1000 == 0) aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SBus R/W %d cycles complete on address %s.\n", x, aapl_addr_to_str(addr));
            prev = ran;
        }
        avago_sbus_wr_flush(aapl, addr, data_addr, orig_val);
    }
    AAPL_SUPPRESS_ERRORS_POP(aapl);

    if (result) aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "SBus R/W test passed on address %s after %d cycles.\n", aapl_addr_to_str(addr), cycles);
    else if (!(aapl->debug & AAPL_DEBUG_SBUS_RW_TEST)) aapl_fail(aapl, __func__, __LINE__, "SBus read/write test failed on address %s in test loop %d. Expected 0x%08x, but got 0x%08x, re-read: 0x%08x. Previous data written was: 0x%08x. Reg 0xff: 0x%08x\n", aapl_addr_to_str(addr), x, ran, data, data2, prev, rev);
    return result;
}


#if AAPL_ALLOW_JTAG || AAPL_ALLOW_AACS
/** @cond INTERNAL */

/** @brief   Implements an SBus command with JTAG instructions
 ** @return  SBus result
 **/
uint avago_jtag_sbus_fn(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    uint sbus_address,  /**< [in] SBus slice address. */
    unsigned char data_address,
    unsigned char command,
    uint *data)
{
    #define AVAGO_JTAG_SCAN_DATA_OUT (32+12)
    #define AVAGO_BITS_TO_SCAN 126 - AVAGO_JTAG_SCAN_DATA_OUT
    #define AVAGO_MAX_LOOPS 1000

    uint cism = 0;
    uint tap_gen = avago_get_tap_gen(aapl);
    char tdi[256];
    char *tdo = 0;
    char bin_data[33];

    int max_read_loops = AVAGO_MAX_LOOPS;
    int max_dummy_write_loops = AVAGO_MAX_LOOPS;
    int offset;
    Avago_addr_t addr_struct;
    avago_addr_to_struct(sbus_address, &addr_struct);

    if (tap_gen == 3) offset = 1;
    else              offset = 0;

    if (tap_gen != 3 && tap_gen != 4)
    {
        aapl_fail(aapl, __func__, __LINE__, "%s only supports TAP gen 3 and 4.\n", __func__);
        return FALSE;
    }

    aapl_set_chip_by_addr(aapl, sbus_address);

    memset(tdi, 0, 255);
    memcpy(tdi,    aapl->sbus_reg, 128);
    memcpy(tdi+21, aapl_hex_2_bin(bin_data, data_address, 0, 8), 8);
    memcpy(tdi+29, aapl_hex_2_bin(bin_data, sbus_address, 0, 8), 8);
    memcpy(tdi+37, aapl_hex_2_bin(bin_data, command, 0, 8),      8);
    memcpy(tdi+45, aapl_hex_2_bin(bin_data, *data, 0, 32),      32);

    tdi[78] = '1';
    tdi[81] = '1';


    if (sbus_address == 0xfe && data_address == 0x00 && (command & 0x3) == 1 && *data == 0x81) cism = 1;

    if ((command & 0x3) != 2 && cism != 1)
        avago_jtag_options(aapl, 0x180 + addr_struct.ring, AVAGO_BITS_TO_SCAN + offset, tdi, 0);
    else
    {

        if (!aapl->recv_data_valid[addr_struct.chip][addr_struct.ring])
        {
            tdo = avago_jtag_options(aapl, 0x180 + addr_struct.ring, AVAGO_BITS_TO_SCAN + offset, tdi, 1);
            aapl->recv_data_valid[addr_struct.chip][addr_struct.ring] = tdo[AVAGO_BITS_TO_SCAN-35-1];
        }
        else
            avago_jtag_options(aapl, 0x180 + addr_struct.ring, AVAGO_BITS_TO_SCAN + offset, tdi, 0);

        tdi[126-45] = 0x30;

        while (1)
        {
            tdo = avago_jtag(aapl, 0x180 + addr_struct.ring, AVAGO_BITS_TO_SCAN+offset, tdi);
            if (!cism && --max_read_loops == 0) break;
            if (tdo[AVAGO_BITS_TO_SCAN-34-1] == 0x31 && tdo[AVAGO_BITS_TO_SCAN-32-1] == 0x30 && tdo[AVAGO_BITS_TO_SCAN-35-1] != aapl->recv_data_valid[addr_struct.chip][addr_struct.ring] && !cism) break;
            else if (cism && tdo[AVAGO_BITS_TO_SCAN-34-1] == 0x31 && tdo[AVAGO_BITS_TO_SCAN-33-1] == 0x31 && tdo[AVAGO_BITS_TO_SCAN-32-1] == 0x31) break;
        }

        if (offset) tdo[AVAGO_BITS_TO_SCAN] = 0;

        if (!max_read_loops || !max_dummy_write_loops)
        {
            aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "Read and/or dummy write loops reached max for command: %02x %02x %02x %08x: read dummy: %d write dummy: %d %x%x%x\n", sbus_address, data_address, command, *data, AVAGO_MAX_LOOPS-max_read_loops, AVAGO_MAX_LOOPS-max_dummy_write_loops, tdo[AVAGO_BITS_TO_SCAN-34-1]-0x30, tdo[AVAGO_BITS_TO_SCAN-33-1]-0x30, tdo[AVAGO_BITS_TO_SCAN-32-1]-0x30);
            aapl->recv_data_valid[addr_struct.chip][addr_struct.ring] = 0;
            aapl->prev_opcode = 0;
        }

        *data = (uint) aapl_strtoul(tdo+AVAGO_BITS_TO_SCAN-32, NULL, 2);
    }
    if (aapl->recv_data_valid[addr_struct.chip][addr_struct.ring] == 0x30) aapl->recv_data_valid[addr_struct.chip][addr_struct.ring] = 0x31;
    else aapl->recv_data_valid[addr_struct.chip][addr_struct.ring] = 0x30;

    if (cism) aapl->recv_data_valid[addr_struct.chip][addr_struct.ring] = 0;

    if (aapl->debug >= 9)
    {
        AAPL_LOG_PRINT9(aapl, AVAGO_DEBUG9, __func__, __LINE__, "Bits scanned in:  %s\n", tdi);
        if ((command & 0x3) == 2) AAPL_LOG_PRINT9(aapl, AVAGO_DEBUG9, __func__, __LINE__, "Read loops: %d Dummy write loops: %d. Bits scanned out: %s\n", AVAGO_MAX_LOOPS-max_read_loops, AVAGO_MAX_LOOPS-max_dummy_write_loops, tdo?tdo:"");
    }
    return TRUE;
}

/** @endcond */
#endif
