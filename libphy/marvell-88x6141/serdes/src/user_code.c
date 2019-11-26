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
 ** @brief Function registration documentation
 **/

#include "aapl.h"

/** @brief  Registers user supplied functions.
 ** @details Provides a single function from which user function registration
 **          can be performed.  Used only by AAPL CLI functions to provide
 **          a single location for user configuration without needing
 **          to change every CLI main function.
 **/
void aapl_register_user_supplied_functions(Aapl_t *aapl)
{
    (void) aapl;



}

#if 0

Starting with AAPL 2.2, AAPL provides hooks to register user-written functions
for communicating with the hardware.  The previous user_supplied_*_functions
are no longer supported, though it should be straightforward to adapt the
existing functions to the new scheme.  Code previously provided in user_code.c
is now replaced with this documentation.

Registering user functions means that the user functions no longer need to be
compiled into AAPL, just callable from AAPL.  This greatly simplifies building
and should greatly simplify integration of new versions of AAPL into customer
environments.

If no user functions are registered, AAPL continues to provide several built-in
communication methods.  Information on registering user functions and using
built-in methods is shown below.


USING BUILT-IN COMMUNICATION METHODS
====================================
The following communication methods are built-into AAPL:
    1. AACS -- Uses the AACS TCP protocol to send commands to a remote server
           via TCP/IP.
    2. AVAGO_SYSTEM_I2C -- Uses system calls to /dev/i2c to send I2C commands
    3. AVAGO_GPIO_MDIO -- Uses system calls on a Raspberry PI to send MDIO
           commands via bit-banged GPIO
    4. AVAGO_JTAG -- Uses the AACS TCP protocol to send
           JTAG commands via TCP/IP to a remote server
    5. AVAGO_OFFLINE -- Uses a built-in server to emulate a device in software
    6. AVAGO_BB_GPIO_JTAG -- Uses /dev/mem to implement a bit-banged GPIO JTAG
           interface for the Raspberry Pi 2

To use these methods, configure AAPL in the following way:
    Aapl_t *aapl = aapl_construct();
    aapl->communication_mode = <MODE>;
    aapl_connect(aapl,server,port);
    ... code here ...
    aapl_destruct(aapl);


CONVERTING FROM USER SUPPLIED FUNCTIONS IN AAPL 2.0 - 2.1
=========================================================
If you supplied functions in user_code.c in AAPL 2.0.x and 2.1.x, it should be
straightforward to upgrade to AAPL 2.2 and later.

If you were supplying code that was called from user_supplied_sbus_function() in
user_code.c, and followed the example prototype, which is:
    command_succeeded = customer_sbus_function(addr, reg_addr, command, &sbus_data);
then all you need to do in AAPL 2.2 and later is

1. Update your function to include Aapl_t * as the first parameter. If you do not
   need anything from the struct, you can make this input a void * and ignore it.
2. Call the registration function (as shown in the section below) with the name
   of the function.

Your code to use AAPL would then be:

        Aapl_t *aapl = aapl_construct();

        aapl_register_sbus_fn(aapl, &customer_sbus_function, &my_open, &my_close);


        aapl_connect(aapl,0,0);
        aapl_get_ip_info(aapl, reset);
        ... code here ...
        aapl_destruct(aapl);



USING USER SUPPLIED COMMUNICATION METHODS
=========================================
The following modes are supported via user registered functions. When calling
the user registration functions, the aapl->communication mode is set
automatically.

After one of the following registration functions are called, all
communications with the device will be done using that communication method.
Only one of these should be called.

    1. AVAGO_SBUS       -- aapl_register_sbus_fn()
    2. AVAGO_MDIO       -- aapl_register_mdio_fn()
    3. AVAGO_I2C        -- aapl_register_i2c_fn()
    4. AVAGO_JTAG       -- aapl_register_jtag_fn()
    5. AVAGO_BB_JTAG    -- aapl_register_bit_banged_jtag_fn()

See the prototypes for these functions in include/aapl_core.h to see what
function types AAPL is expecting for each of these registration functions.

The following registration function is optional, and allows SPICO interrupts to
be sent directly to a SerDes. If you have implemented a core interface to send
SerDes interrupts directly to a SerDes, register that function here.
If this function is not registered, SBus commands will be used to send
interrupts to SerDes, using the communication method registered above.

    aapl_register_spico_int_fn()

The following registration function is also optional, and allows the user
to register a function which returns the JTAG IDCODE for a specific device.

    aapl_register_jtag_idcode_fn()

To configure and use AAPL with a user supplied function, do the following:

    Aapl_t *aapl = aapl_construct();






    aapl_register_*_fn(aapl,...);

    aapl_register_spico_int_fn(aapl, &my_interrupt_fn);

    aapl_connect(aapl,0,0);
    ... code here ...
    aapl_destruct(aapl);


LOW LEVEL DETAILS
=================

FYI: This is mostly internal documentation here -- the user should generally not
need to know this level of detail.

Here is the calling stack for various AAPL functions. Functions with the "aapl->"
prefix indicate that a registered function is called.  Functions below that are
then the possible built-in functions that may be registered depending on what
registration function was called.

avago_spico_int()
    aapl->serdes_int_fn()

avago_sbus_rd()
avago_sbus_wr()
avago_sbus()
    aapl->sbus_fn()
        avago_aacs_sbus_fn()
        avago_i2c_sbus_fn()
        avago_mdio_sbus_fn()
        avago_jtag_sbus_fn()

avago_aacs_sbus_fn()
avago_i2c_sbus_fn()
    avago_i2c_read()
        aapl->i2c_read()
    avago_i2c_write
        aapl->i2c_write()
avago_mdio_sbus_fn()
    avago_mdio()
        aapl->mdio_fn()
avago_jtag_sbus_fn()
    avago_jtag()
        aapl->jtag_fn()

#endif
