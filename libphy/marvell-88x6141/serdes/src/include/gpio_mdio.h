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
 ** @brief MDIO using a GPIO device definitions.
 ** @details Provides an example for integrating into AAPL.
 **/

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#if AAPL_ALLOW_GPIO_MDIO

/* Defines for to set the port directions and set and get the port value.
 * These settings work on a raspberry PI, board revision 2.
 * Pin assignment for JTAG and MDIO
 */
#define TCK_port  RPI_V2_GPIO_P1_26
#define TMS_port  RPI_V2_GPIO_P1_24
#define TDI_port  RPI_V2_GPIO_P1_21
#define TDO_port  RPI_V2_GPIO_P1_19
#define TRST_port RPI_V2_GPIO_P1_23
#define MDC_port  RPI_V2_GPIO_P1_07
#define MDIO_port RPI_V2_GPIO_P1_22

#define GPIO_SET_DIR(port, dir)     bcm2835_gpio_fsel(port, dir)
#define PORT_DIR_OUTPUT             BCM2835_GPIO_FSEL_OUTP
#define PORT_DIR_INPUT              BCM2835_GPIO_FSEL_INPT
#define GPIO_SET_VALUE(port, value) bcm2835_gpio_write(port, value)
#define GPIO_GET_VALUE(port)        bcm2835_gpio_lev(port)

#define MDIO_EXTRA_CYCLES
#define MDIO_DELAY 1

#define MDC_CYCLE {                                                                                         \
    int count;                                                                                              \
    int mdio_loop_cnt = MDIO_DELAY;                                                                         \
    for (count = 0; count <= mdio_loop_cnt; count++)                                                        \
    { GPIO_SET_VALUE(MDC_port, 1); }                                                                        \
    for (count = 0; count <= mdio_loop_cnt; count++)                                                        \
    {  GPIO_SET_VALUE(MDC_port, 0); }                                                                       \
}

#ifdef AAPL_ENABLE_INTERNAL_FUNCTIONS

    EXT int avago_gpio_mdio_open_fn(Aapl_t *aapl);
    EXT int avago_gpio_mdio_close_fn(Aapl_t *aapl);
    EXT uint avago_gpio_mdio_fn(Aapl_t *aapl, Avago_mdio_cmd_t mdio_cmd, unsigned int port_addr, unsigned int dev_addr, unsigned int reg_addr, unsigned int data);

#endif

#endif

#endif
