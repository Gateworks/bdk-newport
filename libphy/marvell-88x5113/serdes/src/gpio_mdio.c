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
 ** @brief Raspberry PI GPIO example
 **/

#include "aapl.h"

#if AAPL_ALLOW_GPIO_MDIO
typedef enum {mw_data, mw_addr} mw_t;
static char MDIO_data = '?';

void aapl_gpio_mdio_write(Aapl_t *aapl, const mw_t type, const int prtad, const int devad, const int data);
void aapl_gpio_mdio_read(Aapl_t *aapl, const int prtad, const int devad, unsigned int * datap);
void aapl_gpio_mdio_start(Aapl_t *aapl, const int op, const int prtad, const int devad);
void aapl_gpio_mdio_send_bit(Aapl_t *aapl, const int out);
int aapl_gpio_mdio_get_bit(Aapl_t *aapl);
int aapl_gpio_gpio_init(void);

int avago_gpio_mdio_open_fn(Aapl_t *aapl)
{
    static BOOL initialized = FALSE;
    if( !initialized && aapl_gpio_gpio_init() < 0)
        return aapl_fail(aapl,__func__,__LINE__,"Failed to Initialize GPIO\n");
    initialized = TRUE;
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "open status = 0\n");
    return 0;
}

int avago_gpio_mdio_close_fn(Aapl_t *aapl)
{
    int rc = 0;
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "close status = %d\n", rc);
    return rc;
}

uint avago_gpio_mdio_fn(
    Aapl_t *aapl,
    Avago_mdio_cmd_t mdio_cmd,
    unsigned int port_addr,
    unsigned int dev_addr,
    unsigned int reg_addr,
    unsigned int data)
{

    aapl_log_printf(aapl, AVAGO_DEBUG6, __func__, __LINE__, "MDIO_cmd = %d; Port Addr = %d; Dev Addr = %d; Register Addr = %d; Data = %d\n", mdio_cmd, port_addr, dev_addr, reg_addr, data);

    switch (mdio_cmd)
    {
    case AVAGO_MDIO_ADDR:
        aapl_gpio_mdio_write(aapl, mw_addr, port_addr, dev_addr, reg_addr);
        break;
    case AVAGO_MDIO_WRITE:
        aapl_gpio_mdio_write(aapl, mw_data, port_addr, dev_addr, data);
        break;
    case AVAGO_MDIO_READ:
        aapl_gpio_mdio_read(aapl, port_addr, dev_addr, &data);
        break;
    default:
        aapl_fail(aapl, __func__, __LINE__, "Unrecognized mdio command %d\n", mdio_cmd);
    }

    return data;

}

void aapl_gpio_mdio_write(Aapl_t *aapl, const mw_t type, const int prtad, const int devad, const int data)
{
    int at;
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Type = %d; Port Addr = %d; Dev Addr = %d; Data = %d\n", type, prtad, devad, data);

    aapl_gpio_mdio_start(aapl, /* op = */ (type == mw_data) ? 1 : 0, prtad, devad);
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Write TA state: send 10\n");
    aapl_gpio_mdio_send_bit(aapl, 1); aapl_gpio_mdio_send_bit(aapl, 0);
    aapl_log_printf(aapl, AVAGO_DEBUG6, __func__, __LINE__, "Send the data, data = %d\n", data);
    for (at = 15; at >= 0; --at)
    {
        aapl_gpio_mdio_send_bit(aapl, (data >> at) & 1);
    }

    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Set MDIO port to high Z\n");
    GPIO_SET_DIR(MDIO_port, PORT_DIR_INPUT); MDIO_data = ('Z');
#ifdef MDIO_EXTRA_CYCLES
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Send two additional clock cycles\n");
    MDC_CYCLE; MDC_CYCLE;
#endif
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Set Clock port to high Z\n");
    GPIO_SET_DIR(MDC_port,  PORT_DIR_INPUT);

}

void aapl_gpio_mdio_read(Aapl_t *aapl, const int prtad, const int devad, unsigned int * datap)
{
    int at;
    aapl_log_printf(aapl, AVAGO_DEBUG5, __func__, __LINE__, "Port Addr = %d; Dev Addr = %d\n", prtad, devad);

    aapl_gpio_mdio_start(aapl, /* op = */ 3, prtad, devad);
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Read TA state: MDIO data = high Z for two clock cycles.\n");
    GPIO_SET_DIR(MDIO_port, PORT_DIR_INPUT); MDIO_data = ('Z');
    MDC_CYCLE; MDC_CYCLE;

    *datap = 0;
    for (at = 15; at >= 0; --at)
    {
        *datap = (*datap << 1) | aapl_gpio_mdio_get_bit(aapl);
    }
    aapl_log_printf(aapl, AVAGO_DEBUG6, __func__, __LINE__, "Read data: data = %d\n", *datap);

#ifdef MDIO_EXTRA_CYCLES
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Send two additional clock cycles\n");
    MDC_CYCLE; MDC_CYCLE;
#endif
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Set Clock port to high Z\n");
    GPIO_SET_DIR(MDC_port, PORT_DIR_INPUT);
}

void aapl_gpio_mdio_start(Aapl_t *aapl, const int op, const int prtad, const int devad)
{
    aapl_log_printf(aapl, AVAGO_DEBUG7, __func__, __LINE__, "Port Addr = %d; Dev Addr = %d\n", prtad, devad);

    GPIO_SET_VALUE(MDC_port, 0);


    GPIO_SET_DIR(MDIO_port, PORT_DIR_OUTPUT);
    GPIO_SET_DIR(MDC_port,  PORT_DIR_OUTPUT);

    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Send stop bits (2 bits): 0x00\n");
    aapl_gpio_mdio_send_bit(aapl, 0); aapl_gpio_mdio_send_bit(aapl, 0);
    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Send OP bits (2 bits): 0x%x\n", op);
    aapl_gpio_mdio_send_bit(aapl, op >> 1); aapl_gpio_mdio_send_bit(aapl, op & 1);

    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Send port address bits (5 bits): 0x%x\n", prtad);
    aapl_gpio_mdio_send_bit(aapl, (prtad >> 4) & 1);
    aapl_gpio_mdio_send_bit(aapl, (prtad >> 3) & 1);
    aapl_gpio_mdio_send_bit(aapl, (prtad >> 2) & 1);
    aapl_gpio_mdio_send_bit(aapl, (prtad >> 1) & 1);
    aapl_gpio_mdio_send_bit(aapl,  prtad       & 1);

    aapl_log_printf(aapl, AVAGO_DEBUG8, __func__, __LINE__, "Send device address bits (5 bits): 0x%x\n", devad);
    aapl_gpio_mdio_send_bit(aapl, (devad >> 4) & 1);
    aapl_gpio_mdio_send_bit(aapl, (devad >> 3) & 1);
    aapl_gpio_mdio_send_bit(aapl, (devad >> 2) & 1);
    aapl_gpio_mdio_send_bit(aapl, (devad >> 1) & 1);
    aapl_gpio_mdio_send_bit(aapl,  devad       & 1);
}

void aapl_gpio_mdio_send_bit(Aapl_t *aapl, const int out)
{
    GPIO_SET_VALUE(MDIO_port, out);
    MDIO_data = (out ? '1' : '0');
    MDC_CYCLE;
}

int aapl_gpio_mdio_get_bit(Aapl_t *aapl)
{
    int bit = GPIO_GET_VALUE(MDIO_port);
    MDC_CYCLE;
    return(bit);
}

int aapl_gpio_gpio_init()
{
    if (!bcm2835_init())
        return -1;

    GPIO_SET_DIR(MDC_port,  PORT_DIR_OUTPUT);
    GPIO_SET_DIR(MDIO_port, PORT_DIR_OUTPUT);

    return 0;
}


#endif
