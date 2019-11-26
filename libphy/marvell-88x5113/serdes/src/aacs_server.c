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
 ** @brief Implementation of AACS Server functionality.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#if AAPL_ENABLE_MAIN || AAPL_ENABLE_AACS_SERVER

#ifndef __MINGW32__
#include <arpa/inet.h>
#endif

#define EQCN(str1,str2,len) (! aapl_strncasecmp(str1, str2, len))
#define EOS               '\0'
#define ISNUL(cp)         (*(cp) == EOS)
#define ISEOL(cp)         ((*(cp) == '#') || ISNUL(cp))
#define ISTERM(cp)        (isspace(*(cp)) || ISEOL(cp))
#define SKIPSPACE(cp)     while (isspace(*(cp))) ++(cp)
#define ISCMD(cp,cmd,len) (EQCN(cp, cmd, len) && ISTERM((cp) + len))


#define RES_CLOSE "(close)"
#define RES_EXIT  "(exit)"


#if AAPL_ENABLE_DIAG
#define RES_HELP  "Valid commands are: sbus, jtag, i2c, set_debug, chips, chipnum, version, status, send, help, close, exit, spico_int, commands, sleep, tck_delay, diag, sbus_reset. Command batching supported."
#else
#define RES_HELP  "Valid commands are: sbus, jtag, i2c, set_debug, chips, chipnum, version, status, send, help, close, exit, spico_int, commands, sleep, tck_delay, sbus_reset. Command batching supported."
#endif

/** @details     Parse a hex number and return the equivalent binary number,
 **              with *endp modified to the first char after the token.
 ** @param cp    String that should be all hex digits.
 ** @param endp  Pointer to string to return.
 ** @param min   Minimum token length in chars (must be >= 1).
 ** @param max   Maximum token length in chars.
 ** @return uint Binary equivalent, or 0 for any error, with *endp set to the
 **              original cp (as a failure flag).
 **/

static uint aapl_num_from_hex(const char *cp, const char **endp, int min, int max)
{
    uint result = 0;
    const char * start = *endp = cp;

    while (isxdigit(*cp))
    {
        if (cp - start >= max) return(0);
        result = (result << 4) | (uint)(isdigit(*cp) ? (*cp - '0') : (10 + tolower(*cp) - 'a'));
        ++cp;
    }
    if ((cp - start < min) || (! ISTERM(cp))) return(0);
    *endp = cp;
    return(result);
}

/** @details     Parse an ASCII binary number possibly containing 'x'/'X'
 **              digits, and return the equivalent binary number, with *endp
 **              modified to the first char after the token.
 ** @param cp    String that should be all '0'/'1'/'x'/'X' digits.
 ** @param endp  Pointer to string to return.
 ** @param min   Minimum token length in chars (must be >= 1).
 ** @param max   Maximum token length in chars.
 ** @param maskp Pointer to a 32-bit mask value to set, default = all 1s, but
 **              returns 0s for 'x'/'X' meaning bits not to be changed
 **              (read/modify/write).
 ** @return uint Binary equivalent, or 0 for any error, with *endp set to the
 **              original cp (as a failure flag); and with *maskp (always)
 **              modified to reflect the data value.  In case of an empty
 **              string (following a data value consisting of just "z"),
 **              assuming min >= 1, returns 0 with an apparent error, but with
 **              mask = 0, and the caller can proceed from there.
 **/

static uint aapl_num_from_bin(const char *cp, const char **endp, int min, int max, uint *maskp)
{
    uint result = 0;
    uint mask   = 0;
    const char * start = *endp = cp;

    while ((*cp == '0') || (*cp == '1') || (*cp == 'x') || (*cp == 'X'))
    {
        if (cp - start >= max) return(0);

        if ((*cp == '0') || (*cp == '1'))
        {
            result = (result << 1) | (uint)(*cp - '0');
            mask = (mask << 1) | 1;
        }
        else
        {
            result <<= 1;
            mask <<= 1;
        }
        ++cp;
    }
    *maskp = mask;

    if ((cp - start < min) || (! ISTERM(cp))) return(0);
    *endp = cp;
    return(result);
}



#define FAILRET(rc,fd1,fd2) {if ((fd1) >= 0) close(fd1); if ((fd2) >= 0) close(fd2); return rc;}




static void cmd_error(Aapl_t *aapl, char *result, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsprintf(result, fmt, ap);

    aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "%s\n", result);

    memmove(result+19, result, strlen(result)+1);
    memcpy(result, "AACS server ERROR: ", 19);
    va_end(ap);
}




static BOOL sbus_parse_da_cmd(Aapl_t *aapl, const char * cmd, const char ** cpp, uint * valp, const int argnum, const char * valname, char * result)
{
    const char * cp2;
    uint val = aapl_num_from_hex(*cpp, &cp2, 2, 2);

    if (cp2 == *cpp)
    {
        cmd_error(aapl, result, "Invalid \"sbus\" command ignored: Arg %d = <%s> must be 2 hex digits. Got: \"%s\".", argnum, valname, cmd);
        return(FALSE);
    }
    SKIPSPACE(cp2);
    *cpp  = cp2;
    *valp = val;
    return(TRUE);
}


static int sbus_parse_data(Aapl_t *aapl, const char * cmd, const char ** cpp, uint * datap, uint * maskp, char * result)
{
    const char * cp = *cpp;
    const char * cp2;
    int  reslen;
    uint data = 0;




    if ((*cp == 'z') || (*cp == 'Z'))
    {
        data = aapl_num_from_bin(++cp, &cp2, 1, 31, maskp);

        if (cp == cp2)
        {
            if (! ISTERM(cp + 1))
            {
                cmd_error(aapl, result, "Invalid \"sbus\" command ignored. Arg 4 = <data> 'z' prefix must be followed by 0-31 '0'/'1'/'x'/'X' chars, but got: \"%s\".", cmd);
                return(0);
            }
        }

        reslen = 32;
    }


    else
    {
        int len;
        *maskp = 0xffffffff;

        for (cp2 = cp; isxdigit(*cp2) || (*cp2 == 'x') || (*cp2 == 'X'); ++cp2)
        /* null */;

        len = cp2 - cp;

        if      ( len ==  2) data = aapl_num_from_hex(cp, &cp2,  2,  2);
        else if ( len ==  8) data = aapl_num_from_bin(cp, &cp2,  8,  8, maskp);
        else if ((len == 10) && EQCN(cp, "0x", 2))
                   {cp += 2; data = aapl_num_from_hex(cp, &cp2,  8,  8);}
        else if ( len == 32) data = aapl_num_from_bin(cp, &cp2, 32, 32, maskp);
        else cp2 = cp;

        if (cp == cp2)
        {
            cmd_error(aapl, result, "Invalid \"sbus\" command ignored. Arg 4 = <data> must be 2-hex, 8-bin, 0x-8-hex, 32-bin, or \"z\" prefix variable-length, but got: \"%s\".", cmd);
            return(0);
        }
        reslen = ((len <= 8) ? 8 : 32);
    }
    *cpp   = cp2;
    *datap = data;
    return(reslen);

}



static BOOL check_term(Aapl_t *aapl, const char * cmd, const char * cp, char * result)
{
    if (!cp || ISTERM(cp)) return(TRUE);

    cmd_error(aapl, result, "Unexpected extra word(s) on command line, ignored. Got: \"%s\".", cmd);
    return(FALSE);
}


static void sbus_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result, int * chip_nump, int * ring_nump)
{
    const char * cp2;
    uint new_chip = 0x10;
    uint new_ring = 0x10;
    uint sa;
    uint data_out;
    uint da, scmd, data, mask = 0xffffffff;
    int errors, warnings, rc;

    int reslen;

    SKIPSPACE(cp);

    if (ISEOL(cp))
    {
        cmd_error(aapl, result, "Invalid \"sbus\" command ignored. Must be: \"sbus <sa> <da> <cmd> <data> [# <comment>]\".");
        return;
    }


    sa = aapl_num_from_hex(cp, &cp2, 2, 4);

    if (cp2 == cp)
    {
        cmd_error(aapl, result, "Invalid \"sbus\" command ignored: Arg 1 = <sa> must be 2-4 hex digits. Got: \"%s\".", cmd);
        return;
    }
    if (cp2 - cp == 4) new_chip = (sa & 0xf000) >> 12;
    if (cp2 - cp >= 3) new_ring = (sa & 0x0f00) >>  8;
    cp = cp2; SKIPSPACE(cp);


    if (! (sbus_parse_da_cmd(aapl, cmd, &cp, &da,   2, "da",  result)
        && sbus_parse_da_cmd(aapl, cmd, &cp, &scmd, 3, "cmd", result)
        && ((reslen = sbus_parse_data(aapl, cmd, &cp, &data, &mask, result)))))
    {return;}


    if (! check_term(aapl, cmd, cp, result)) return;
    if (new_chip < 0x10) *chip_nump = new_chip;
    if (new_ring < 0x10) *ring_nump = new_ring;


    sa |= (*chip_nump << 12) | (*ring_nump << 8);

    rc = aapl->return_code;
    errors = aapl->errors;
    warnings = aapl->warnings;

    data_out = ((scmd == 1 && mask != 0xffffffff) ? avago_sbus_rmw(aapl, sa, da, data, mask) :
                (scmd == 1)                       ? avago_sbus_wr( aapl, sa, da, data) :
                (scmd == 2)                       ? avago_sbus_rd( aapl, sa, da) :
                                                    avago_sbus(    aapl, sa, da, scmd, data, /* recv_data_back = */ 1));

    aapl_hex_2_bin(result, data_out, /* underscore_en = */ 0, /* bits */ 32);
    if (reslen == 8) strcpy(result, result + 24);


    if (rc != aapl->return_code || errors != aapl->errors || warnings != aapl->warnings)
    {
        char result_buf[128];
        strncpy(result_buf, result, 127);
        cmd_error(aapl, result, "Command failed: \"%s\" => \"%s\" result => %s %s", cmd, aapl->data_char, "\x1\x1\x1", result_buf);
    }
}


#if AAPL_ALLOW_I2C || AAPL_ALLOW_SYSTEM_I2C
static void i2c_command(Aapl_t *aapl, const char *cmd, const char *cp, char *result)
{
    typedef enum { cmd_read = 0, cmd_write, cmd_writeread} i2c_cmd_t;
    unsigned int i2c_address;
    const char *cp2;
    unsigned char buffer[256];
    i2c_cmd_t command;
    int num_bytes_r = 0, num_bytes = 0;

    SKIPSPACE(cp);
    if( *cp == '\0' )
    {
BadI2cCommand:
        sprintf(result, "ERROR: Invalid \"i2c\" command ignored. Must be: "
        "\"i2c r <addr> <num_bytes> [# <comments>]\", "
        "\"i2c w <addr> <byte>[ <byte>...] [# <comments>]\", or "
        "\"i2c wr <addr> <num_bytes> <byte>[ <byte>...] [# <comments>]\". "
        "Got: \"%s\".", cmd);
        return;
    }

    if(      (cp[0] == 'r' || cp[0] == 'R') && isspace(cp[1]) )
        command = cmd_read;
    else if( (cp[1] == 'r' || cp[1] == 'R') &&
             (cp[0] == 'w' || cp[0] == 'W') && isspace(cp[2]) )
    {
        cp++;
        command = cmd_writeread;
    }
    else if( (cp[0] == 'w' || cp[0] == 'W') && (isspace(cp[1]) || cp[1]=='\0') )
        command = cmd_write;
    else
    {
        sprintf(result, "ERROR: Invalid \"i2c\" command ignored. Arg 1 must be \"r\", \"w\", or \"wr\".  Got \"%s\".", cmd);
        return;
    }
    cp++; SKIPSPACE(cp);

    i2c_address = aapl_num_from_hex(cp, &cp2, 1, 2);
    if( cp2 == cp || i2c_address > 0x7f )
    {
        sprintf(result, "ERROR: Invalid \"i2c\" command ignored. Arg 2 must be a hex I2C address in the range 00..7f. Got: \"%s\".", cmd);
        return;
    }
    cp = cp2; SKIPSPACE(cp);

    if( *cp == '\0' )
        goto BadI2cCommand;

    if( command == cmd_read || command == cmd_writeread )
    {
        num_bytes_r = (int) aapl_strtol(cp, (char **)&cp2, 10);
        if( cp2 == cp || !(isspace(*cp2) || *cp2 == '\0') || num_bytes_r < 0 || num_bytes_r > (int)sizeof(buffer) )
        {
            sprintf(result, "ERROR: Invalid \"i2c %s\" command ignored. Arg 3 must be a number of bytes in the range 1..%d. Got: \"%s\".",
                            command==cmd_read ? "r" : "wr", (int)sizeof(buffer), cmd);
            return;
        }
        cp = cp2; SKIPSPACE(cp);
    }

    if( command == cmd_write || command == cmd_writeread )
    {
        while( *cp )
        {
            int value;
            if( num_bytes >= (int)sizeof(buffer) )
            {
                sprintf(result, "ERROR: Invalid \"i2c %s\" command ignored, too many bytes specified, limit is %d. Got: \"%s\".",
                                command==cmd_write ? "w" : "wr", (int)sizeof(buffer), cmd);
                return;
            }
            value = aapl_num_from_hex(cp, &cp2, 1, 2);
            if( cp2 == cp || value > 0xff )
            {
                sprintf(result, "ERROR: Invalid \"i2c %s\" command ignored. Arg %d must be a hex byte value in the range 00..ff. Got: \"%s\".",
                                command==cmd_write ? "w" : "wr", 3 + num_bytes, cmd);
                return;
            }
            cp = cp2; SKIPSPACE(cp);
            buffer[num_bytes++] = value;
        }
        if( num_bytes == 0 )
        {
            sprintf(result, "ERROR: Invalid \"i2c %s\" command ignored. "
                            "Must specify one or more bytes to send. "
                            "Invoke with no arguments for a usage summary.",
                                command==cmd_write ? "w" : "wr");
            return;
        }
    }

    if( command == cmd_write || command == cmd_writeread )
    {
        if( avago_i2c_write(aapl, i2c_address, num_bytes, buffer) < 0 )
        {
            sprintf(result, "ERROR: i2c command \"%s\" failed.", cmd);
            return;
        }
        if( command == cmd_write )
            sprintf(result, "Address 0x%02x, bytes written: %d.", i2c_address, num_bytes);
    }
    if( command == cmd_read || command == cmd_writeread )
    {
        int i;
        char *ptr = result;
        if( avago_i2c_read(aapl, i2c_address, num_bytes_r, buffer) < 0 )
        {
            sprintf(result, "ERROR: i2c command \"%s\" failed.", cmd);
            return;
        }
        for( i = 0; i < num_bytes_r; i++ )
            ptr += sprintf(ptr, "%02x ", buffer[i]);
        ptr[-1] = '\0';
    }
}
#endif

static void mdio_command(Aapl_t *aapl, const char *cmd, const char *cp, char *result)
{
    (void)aapl;
    (void)cmd;
    (void)cp;
    sprintf(result, "ERROR: The mdio command is not implemented.\n");
}


static void jtag_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result, int * chip_nump)
{
    char *tdo, *cp2;
    int opcode, bits;

    SKIPSPACE(cp);

    bits = aapl_strtol(cp, &cp2, 10);
    if (ISNUL(cp2)) goto BadJtagCmd;
    opcode = aapl_strtol(cp2, &cp2, 16);
    if (ISNUL(cp2)) goto BadJtagCmd;

    if (bits == 32 && opcode == 0x2b6)
        aapl_hex_2_bin(result, aapl->jtag_idcode[*chip_nump], 0, 32);
    else
    {
        char *buf;
        int length;
        SKIPSPACE(cp2);
        length = strlen(cp2);
        buf = (char *) aapl_malloc(aapl, bits+1, __func__);
        memset(buf+length, '0', bits+1-length);
        memcpy(buf, cp2, length);
        tdo = avago_jtag(aapl, opcode, bits, buf);
        if (tdo) snprintf(result, AACS_SERVER_BUFFERS, "%s", tdo);
        else result[0] = 0;
        if (buf) aapl_free(aapl, buf, __func__);
    }
    return;

    BadJtagCmd:
    cmd_error(aapl, result, "Unsupported \"jtag\" command ignored. Format should be \"jtag <bits> <opcode> <ascii binary data>\". Got: \"%s\".", cmd);
}

#if AAPL_ALLOW_JTAG || AAPL_ALLOW_AACS
/** Private function used by avago_jtag_scan and avago_jtag_rd
 ** Copied from aapl_core.c. aapl_core.c wants this function to be static for performance.
 **/
static AAPL_INLINE char avago_bit_banged_jtag(Aapl_t *aapl, int cycles, int tms, int tdi, int trst_l, BOOL get_tdo)
{
    if (aapl->aacs)
    {
        char buf[64];

        snprintf(buf, 63, "jtag_cycle %d %d %d %d", cycles, tms, tdi, trst_l);
        avago_aacs_send_command(aapl, buf);
        return aapl->data_char[0];
    }
    else
    {
        if (!aapl->bit_banged_jtag_fn)
        {
            aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "Bit banged JTAG function function not registered.\n");
            return 0x30;
        }
        while (cycles > 1)
        {
            aapl->bit_banged_jtag_fn(aapl, tms, tdi, trst_l, 0);
            cycles--;
        }
        return aapl->bit_banged_jtag_fn(aapl, tms, tdi, trst_l, get_tdo) + 0x30;
    }
}
#endif

#if AAPL_ALLOW_JTAG || AAPL_ALLOW_AACS
static void jtag_cycle_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result)
{
    char *cp2;
    uint cycles, tms, tdi, trst_l;

    cycles = aapl_strtol(cp, &cp2, 10);
    if (ISNUL(cp2)) goto jtag_cycle_error;
    tms = aapl_strtol(cp2, &cp2, 10);
    if (ISNUL(cp2)) goto jtag_cycle_error;
    tdi = aapl_strtol(cp2, &cp2, 10);
    if (ISNUL(cp2)) goto jtag_cycle_error;
    trst_l = aapl_strtol(cp2, &cp2, 10);

    result[0] = 0;
    result[1] = 0;
    if (!check_term(aapl, cmd, cp2, result))
    {
        jtag_cycle_error:
        cmd_error(aapl, result, "Invalid command ignored. Command must be of format: jtag_cycle <cycles> <tms> <tdi> <trst_l>. Got: \"%s\".", cmd);
    }
    else
    {
        memset(aapl->prev_opcode, 0, sizeof(aapl->prev_opcode));
        result[0] = avago_bit_banged_jtag(aapl, cycles, tms, tdi, trst_l, 1);
    }
}
#endif


static void chips_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result)
{
    if (check_term(aapl, cmd, cp, result))
        sprintf(result, "%d", aapl->chips);
}


static void chipnum_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result, int * chip_nump)
{
    const char *cp2;
    uint num;

    SKIPSPACE(cp);
    if (ISEOL(cp)) {sprintf(result, "%d", *chip_nump); return;}

    cp2 = cp;
    num = aapl_num_from_hex(cp, &cp2, 1, 1);

    if (cp2 == cp)
        cmd_error(aapl, result, "Invalid \"chipnum\" command ignored: Parameter must be a single hex digit. Got: \"%s\".", cmd);
    else if (num >= aapl->chips)
        cmd_error(aapl, result, "Invalid \"chipnum\" command ignored: Max chip number is 0x%x. Got: \"%s\".", aapl->chips - 1, cmd);
    else {*chip_nump = num; result[0] = *cp; result[1] = '\0';}
}

static void set_uint(Aapl_t * aapl, const char * cmd, const char * cp, uint * ptr, char * result)
{
    const char *cp2;
    uint num;

    SKIPSPACE(cp);
    if (ISEOL(cp)) {snprintf(result, AACS_SERVER_BUFFERS, "%d", *ptr); return;}

    cp2 = cp;
    num = aapl_num_from_hex(cp, &cp2, 1, 1);

    if (cp2 == cp)
        cmd_error(aapl, result, "Invalid command ignored: Parameter must be a single integer. Got: \"%s\".", cmd);
    else
    {
        *ptr = num;
        snprintf(result, AACS_SERVER_BUFFERS, "%d", *ptr);
    }
}

static void sbus_reset_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result)
{
    uint addr;

    SKIPSPACE(cp);
    SKIPSPACE(cp);
    if (ISEOL(cp)) goto sbus_reset_error;

    if (!aapl_str_to_addr(cp, 0, &addr)) goto sbus_reset_error;
    cp = strchr(cp, ' ');

    if (!check_term(aapl, cmd, cp, result))
    {
        sbus_reset_error:
        cmd_error(aapl, result, "Invalid \"sbus_reset\" command ignored: Parameter must be a valid address. Got: \"%s\".", cmd);
    }
    else
    {
        avago_sbus_reset(aapl, addr, 1);
        snprintf(result, AACS_SERVER_BUFFERS, "Hard SBus reset executed to address %s.", aapl_addr_to_str(addr));
    }
}
static void sleep_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result)
{
    char *cp2 = 0;
    int num;

    SKIPSPACE(cp);

    num = aapl_strtol(cp, &cp2, 10);
    num *= 1000;
    if( *cp2 == '.' )
    {
        char *cp3 = ++cp2;
        int num2 = aapl_strtol(cp3, &cp2, 10);
        int len = cp2-cp3;
        for( ; len > 3; len-- ) num2 = (num2 + 5) / 10;
        for( ; len < 3; len++ ) num2 *= 10;
        num += num2;
    }
    if( *cp2 != '\0' || num < 0 || *cp == '-' )
        cmd_error(aapl, result, "Invalid \"sleep\" command ignored: Parameter must be a (non-negative) number of seconds (int or decimal). Got: \"%s\".", cmd);
    else
    {
#if AAPL_ALLOW_AACS
        avago_aacs_flush(aapl);
#endif
        ms_sleep(num);
        snprintf(result, AACS_SERVER_BUFFERS, "Slept %d.%03d seconds.",num/1000,num%1000);
    }
}

static void sbus_mode_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result)
{
    const char *cp2;
    Aapl_comm_method_t comm_method;
    (void)cmd;

    SKIPSPACE(cp);
    if (ISEOL(cp)) {snprintf(result, AACS_SERVER_BUFFERS, "%s", aapl_comm_method_to_str(aapl->communication_method)); return;}

    cp2 = cp;

    if( aapl_str_to_comm_method(cp2,&comm_method) )
    {
        aapl->communication_method = comm_method;
        snprintf(result, AACS_SERVER_BUFFERS, "sbus_mode set to %s.", cp2);
    }
    else snprintf(result, AACS_SERVER_BUFFERS, "sbus_mode option must be {AACS}_{I2C|MDIO|SBUS|JTAG|BB_JTAG}|SYSTEM_{I2C|MDIO}|GPIO_MDIO|OFFLINE\n");
}

#if AAPL_ENABLE_DIAG
static void diag_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result)
{
    char *cp2;
    uint addr;

    SKIPSPACE(cp);
    if (ISEOL(cp)) goto diag_cmd_error;

    if (EQCN(cp, "size", 4))
    {
        cp += 4;
        if (!check_term(aapl, cmd, cp, result)) goto diag_cmd_error;
        snprintf(result, AACS_SERVER_BUFFERS, "%u", (uint)sizeof(Avago_diag_config_t));
        return;
    }

    aapl_str_to_addr(cp, 0, &addr);
    cp = strchr(cp, ' ');

    if (!check_term(aapl, cmd, cp, result))
    {
        diag_cmd_error:
        cmd_error(aapl, result, "Invalid \"diag\" command ignored. Should be: diag [size | <addr>]. Got: \"%s\".", cmd);
        return;
    }

    aapl_log_clear(aapl);

    {
        size_t index;
        Avago_diag_config_t *config  = avago_diag_config_construct(aapl);

        for (index = 0; index < sizeof(Avago_diag_config_t) - 8; index++)
        {
            int num;
            if (!cp) break;
            num = aapl_strtoul(cp, &cp2, 0);
            if (cp != cp2) *((char *)config + index) = num;
            cp = cp2;
        }

        avago_diag(aapl, addr, config);
        avago_diag_config_destruct(aapl, config);
    }

    aapl_str_rep(aapl->log, 0xa, 0x2);
    aapl->aacs_server_buffer = (char *) aapl_realloc(aapl, aapl->aacs_server_buffer, strlen(aapl->log) + AACS_SERVER_BUFFERS, __func__);
    snprintf(aapl->aacs_server_buffer, strlen(aapl->log) + AACS_SERVER_BUFFERS, "%c%c%s", 0x1, 0x1, aapl->log);
}
#endif

static void spico_int_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result)
{
    char *cp2;
    uint interrupt, param, addr;

    SKIPSPACE(cp);
    if (ISEOL(cp)) goto spico_int_error;

    aapl_str_to_addr(cp, 0, &addr);
    cp = strchr(cp, ' ');

    if (!cp) goto spico_int_error;
    SKIPSPACE(cp);
    if (ISEOL(cp)) goto spico_int_error;
    interrupt = aapl_strtoul(cp, &cp2, 0);

    cp = cp2;
    SKIPSPACE(cp);
    if (ISEOL(cp)) goto spico_int_error;
    param  = aapl_strtoul(cp, &cp2, 0);

    cp = cp2;
    if (!check_term(aapl, cmd, cp, result))
    {
        spico_int_error:
        cmd_error(aapl, result, "Invalid \"spico_int\" command ignored. Should be: spico_int <addr> <int> <param>. Got: \"%s\".", cmd);
        return;
    }
    snprintf(result, AACS_SERVER_BUFFERS, "%x", avago_spico_int(aapl, addr, interrupt, param));
}


static void version_command(Aapl_t *aapl, const char * cmd, const char * cp, char * result)
{
    if (check_term(aapl, cmd, cp, result))
        snprintf(result, AACS_SERVER_BUFFERS, "AAPL AACS server %s", AAPL_VERSION);
}


static void status_command(Aapl_t *aapl, const char * cmd, const char * cp, char * result)
{
    if (check_term(aapl, cmd, cp, result))
    {
        char *result_end = result;
        int size = AACS_SERVER_BUFFERS;
        uint chip = 0;

        aapl_buf_add(aapl, &result, &result_end, &size, "Version:              AAPL AACS Server %s;", AAPL_VERSION);
        aapl_buf_add(aapl, &result, &result_end, &size, "Current chip:         %d (of 0..%d);", aapl->curr_chip, aapl->chips-1);
        for (chip = 0; chip <= aapl->chips - 1; chip++)
        {
            aapl_buf_add(aapl, &result, &result_end, &size, "Chip %d:              %08x ", aapl->jtag_idcode[chip], aapl->chip_name[chip]);
            if (aapl->chip_name[chip]) aapl_buf_add(aapl, &result, &result_end, &size, "(%s);", aapl->chip_name[chip]);
            else                       aapl_buf_add(aapl, &result, &result_end, &size, ";");
        }
        aapl_buf_add(aapl, &result, &result_end, &size, "SBus rings:           %d;", aapl->sbus_rings);
        aapl_buf_add(aapl, &result, &result_end, &size, "TAP generation:       %d;", avago_get_tap_gen(aapl));
        aapl_buf_add(aapl, &result, &result_end, &size, "Communication method: %s;", aapl_comm_method_to_str(aapl->communication_method));
        aapl_buf_add(aapl, &result, &result_end, &size, "Debug level:          %d;", aapl->debug);
        aapl_buf_add(aapl, &result, &result_end, &size, "Verbose level:        %d;", aapl->verbose);
        aapl_buf_add(aapl, &result, &result_end, &size, "Suppress errors:      %d;", aapl->suppress_errors);
        aapl_buf_add(aapl, &result, &result_end, &size, "Upgrade warnings:     %d;", aapl->upgrade_warnings);
        aapl_buf_add(aapl, &result, &result_end, &size, "Serdes int timeout    %d;", aapl->serdes_int_timeout);
        aapl_buf_add(aapl, &result, &result_end, &size, "TCK delay:            %d;", aapl->tck_delay);
        aapl_buf_add(aapl, &result, &result_end, &size, "Error count:          %d;", aapl->errors);
        aapl_buf_add(aapl, &result, &result_end, &size, "Warning count:        %d;", aapl->warnings);
        aapl_buf_add(aapl, &result, &result_end, &size, "Max commands buffered:%d;", aapl->max_cmds_buffered);
        aapl_buf_add(aapl, &result, &result_end, &size, "Capabilities:         %d;", aapl->capabilities);
        aapl_buf_add(aapl, &result, &result_end, &size, "Commands:             %d (sbus %d);", aapl->commands, aapl->sbus_commands);
        aapl_buf_add(aapl, &result, &result_end, &size, "Data_char size:       %d;", aapl->data_char_size);
        aapl_buf_add(aapl, &result, &result_end, &size, "Log size:             %d;", aapl->log_size);
        if (aapl->aacs_server) aapl_buf_add(aapl, &result, &result_end, &size, "AACS server:          %s:%d;", aapl->aacs_server, aapl->tcp_port);
    }
}

static void null_command(Aapl_t *aapl, const char * cmd, const char * cp, char * result)
{
    (void)aapl;
    (void)cmd;
    (void)cp;
    if (cp[0] == '#') result[0] = 0;
    else              snprintf(result, AACS_SERVER_BUFFERS, "Unimplemented command.");
}


#if AAPL_ALLOW_AACS

static void my_send_command(Aapl_t * aapl, const char * cmd, const char * cp, char * result)
{
      (void)cmd;
      SKIPSPACE(cp);


      if (ISNUL(cp)) {result[0] = '\0'; return;}

      strncpy(result, avago_aacs_send_command(aapl, cp), AACS_SERVER_BUFFERS);
      result[AACS_SERVER_BUFFERS - 1] = '\0';
}
#endif


static void help_command(Aapl_t *aapl, const char * cmd, const char * cp, char * result)
{
    if (check_term(aapl, cmd, cp, result)) strcpy(result, RES_HELP);
}

static void commands_command(Aapl_t *aapl, const char * cmd, const char * cp, char * result)
{
    if (check_term(aapl, cmd, cp, result))
        snprintf(result, AACS_SERVER_BUFFERS, "%d (sbus %d)", aapl->commands, aapl->sbus_commands);
}


static void close_command(Aapl_t *aapl, const char * cmd, const char * cp, char * result)
{
    if (check_term(aapl, cmd, cp, result)) strcpy(result, RES_CLOSE);
}


static void exit_command(Aapl_t *aapl, const char * cmd, const char * cp, char * result)
{
    if (check_term(aapl, cmd, cp, result))
        strcpy(result, RES_EXIT);
}




char *avago_aacs_process_cmd(
    Aapl_t *aapl,       /**< [in] */
    const char *cmd,    /**< [in] */
    int *chip_nump,     /**< [in/out] */
    int *ring_nump)     /**< [in/out] */
{
    const char *cp = cmd;
    int x = 0;
    int y = 0;
    if (!chip_nump) chip_nump = &x;
    if (!ring_nump) ring_nump = &y;

    if (!aapl->aacs_server_buffer) aapl->aacs_server_buffer = (char *) aapl_malloc(aapl, AACS_SERVER_BUFFERS, __func__);
    SKIPSPACE(cp);

    if (strchr(cmd, ';'))
    {
        char next_cmd[AACS_SERVER_BUFFERS];
        int result_index = 0;
        char result_buf[AACS_SERVER_BUFFERS];

        const char * index;
        const char * remaining_cmd;
        int first_cmd = 0;

        remaining_cmd = cmd;
        do
        {
            const char *result;
            index = strchr(remaining_cmd, ';');
            if (index) strncpy(next_cmd, remaining_cmd, index - remaining_cmd);
            else       strncpy(next_cmd, remaining_cmd, strlen(remaining_cmd)+1);
            if (index) next_cmd[index-remaining_cmd] = 0;
            remaining_cmd = index + 1;

            result = avago_aacs_process_cmd(aapl, next_cmd, chip_nump, ring_nump);

            if (!first_cmd++) result_index += snprintf(result_buf + result_index, AACS_SERVER_BUFFERS, "%s", result);
            else              result_index += snprintf(result_buf + result_index, AACS_SERVER_BUFFERS, ";%s", result);
        } while (index);

        strncpy(aapl->aacs_server_buffer, result_buf, AACS_SERVER_BUFFERS);
        return aapl->aacs_server_buffer;
    }

    aapl->commands++;

    if (cp[0] == '@') cp++;

    if      (ISCMD(cp, "sbus",        4)) sbus_command(       aapl, cmd, cp + 4, aapl->aacs_server_buffer, chip_nump, ring_nump);
    else if (cp[0] == '#'               ) null_command(       aapl, cmd, cp    , aapl->aacs_server_buffer);
#if AAPL_ALLOW_JTAG || AAPL_ALLOW_AACS
    else if (ISCMD(cp, "jtag_cycle", 10)) jtag_cycle_command( aapl, cmd, cp +10, aapl->aacs_server_buffer);
#endif
    else if (ISCMD(cp, "jtag",        4)) jtag_command(       aapl, cmd, cp + 4, aapl->aacs_server_buffer, chip_nump);
    else if (ISCMD(cp, "chip",        4)) jtag_command(       aapl, cmd, "32 02b6 0", aapl->aacs_server_buffer, chip_nump);
    else if (ISCMD(cp, "chips",       5)) chips_command(      aapl, cmd, cp + 5, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "chipnum",     7)) chipnum_command(    aapl, cmd, cp + 7, aapl->aacs_server_buffer, chip_nump);
    else if (ISCMD(cp, "version",     7)) version_command(    aapl, cmd, cp + 7, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "status",      6)) status_command (    aapl, cmd, cp + 6, aapl->aacs_server_buffer);
#if AAPL_ALLOW_I2C || AAPL_ALLOW_SYSTEM_I2C
    else if (ISCMD(cp, "i2c",         3)) i2c_command(        aapl, cmd, cp + 3, aapl->aacs_server_buffer);
#endif
    else if (ISCMD(cp, "mdio",        4)) mdio_command(       aapl, cmd, cp + 4, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "sbus_mode",   9)) sbus_mode_command(  aapl, cmd, cp + 9, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "spico_int",   9)) spico_int_command(  aapl, cmd, cp + 9, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "sleep",       5)) sleep_command(      aapl, cmd, cp + 5, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "sbus_reset", 10)) sbus_reset_command( aapl, cmd, cp +10, aapl->aacs_server_buffer);
#if AAPL_ENABLE_DIAG
    else if (ISCMD(cp, "diag",        4)) diag_command(       aapl, cmd, cp + 4, aapl->aacs_server_buffer);
#endif
#if AAPL_ALLOW_AACS
    else if (ISCMD(cp, "send",        4)) my_send_command(    aapl, cmd, cp + 4, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "reset",       5)) my_send_command(    aapl, cmd, cp    , aapl->aacs_server_buffer);
    else if (ISCMD(cp, "set_sbus",    8)) my_send_command(    aapl, cmd, cp    , aapl->aacs_server_buffer);
#else
    else if (ISCMD(cp, "send",        4)) null_command(       aapl, cmd, cp + 4, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "reset",       5)) null_command(       aapl, cmd, cp    , aapl->aacs_server_buffer);
    else if (ISCMD(cp, "set_sbus",    8)) null_command(       aapl, cmd, cp    , aapl->aacs_server_buffer);
#endif
    else if (ISCMD(cp, "null",        4)) null_command(       aapl, cmd, cp + 4, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "help",        4)) help_command(       aapl, cmd, cp + 4, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "set_debug",   9)) set_uint(           aapl, cmd, cp + 9, &aapl->debug,      aapl->aacs_server_buffer);
    else if (ISCMD(cp, "tck_delay",   9)) set_uint(           aapl, cmd, cp + 9, &aapl->tck_delay,  aapl->aacs_server_buffer);
    else if (ISCMD(cp, "close",       5)) close_command(      aapl, cmd, cp + 5, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "exit",        4)) exit_command(       aapl, cmd, cp + 4, aapl->aacs_server_buffer);
    else if (ISCMD(cp, "commands",    8)) commands_command(   aapl, cmd, cp + 8, aapl->aacs_server_buffer);
    else if (ISNUL(cp)) aapl->aacs_server_buffer[0] = '\0';
    else if ((cp[0] >= '0' && cp[0] <= '9') || (cp[0] >= 'a' && cp[0] <= 'f') || (cp[0] >= 'A' && cp[0] <= 'F'))
    {
        const char *cp2;
        aapl_num_from_hex(cp, &cp2, 2, 4);
        if (cp2 != cp)                    sbus_command(       aapl, cmd, cp + 0, aapl->aacs_server_buffer, chip_nump, ring_nump);
        else cmd_error(aapl, aapl->aacs_server_buffer, "Unrecognized command ignored: \"%s\".", cmd);
    }
    else cmd_error(aapl, aapl->aacs_server_buffer, "Unrecognized command ignored: \"%s\".", cmd);

    aapl->curr_chip = *chip_nump;

    if (cmd[0] == '@') aapl->aacs_server_buffer[0] = 0;

    return aapl->aacs_server_buffer;
}

#endif

#if AAPL_ENABLE_AACS_SERVER

/** @brief   Starts an AACS Server and listens for requests.
 ** @details Starts (and restarts after closure) an AACS server that accepts one TCP/IP
 ** connection on tcp_port, receives zero or more AACS commands, forwards them
 ** to avago_sbus_wr(), etc, and returns response text to the command client.
 **
 ** The caller must first:
 **
 ** - Open a lower-level (back end) connection or whatever else is required for
 **   avago_sbus_wr(), etc to function, such as by using aapl_connect() (but not
 **   necessarily this function in the end user context).
 **
 ** - Start a process or thread that's taken over by this function, which only
 **   returns upon "exit" or internal error.
 **
 ** Note:  Unlike the HW server (HS1, etc), this process does not support
 ** command batching.  It expects just one command => response at a time.
 **
 ** @return Returns FALSE for internal error logged, or TRUE for client "exit" command.
 ** Does not return for client command anomalies or "close" commands.
 **/
int avago_aacs_server_options(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    int tcp_port,       /**< [in] Port of remote to connect to. */
    const char *ats_server_host,
    uint ats_server_host_port)
{
    int chip_num = 0;
    int ring_num = 0;
    int error_or_exit = 0;
    int return_status = 0;
    int rc = 1, rc_ts = 1;
    int fd_socket, fd_socket_ts;
    int return_code = 0;
    Aapl_t * aapl_ats_server_host = NULL;

    struct sockaddr_in client_IPaddr, client_IPaddr_ts;
    struct sockaddr_in sai, sai_ts;
    Aapl_t *aapl_server = aapl_construct();

    socklen_t          addr_len = sizeof(client_IPaddr);
    socklen_t          addr_len_ts = sizeof(client_IPaddr_ts);

    # ifdef WIN32
        WSADATA wsaData;
        WORD vers_req = MAKEWORD(2,2);
        WSAStartup(vers_req,&wsaData);
    # endif


    fd_socket = socket(PF_INET, SOCK_STREAM, 0);
    fd_socket_ts = socket(PF_INET, SOCK_STREAM, 0);
    if( fd_socket < 0 || fd_socket_ts < 0 )
    {
        aapl_fail(aapl, __func__, __LINE__, "Cannot create PF_INET socket: %s.\n", aapl_tcp_strerr());
        return 0;
    }

    rc = setsockopt(fd_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &rc, sizeof(rc));
    rc_ts = setsockopt(fd_socket_ts, SOL_SOCKET, SO_REUSEADDR, (char *) &rc_ts, sizeof(rc_ts));

    rc = rc_ts = 1;
    rc = setsockopt(fd_socket, SOL_SOCKET, SO_KEEPALIVE, (char *) &rc, sizeof(rc));
    rc_ts = setsockopt(fd_socket_ts, SOL_SOCKET, SO_KEEPALIVE, (char *) &rc_ts, sizeof(rc_ts));

    if( rc < 0 || rc_ts < 0 )
    {
        aapl_fail(aapl, __func__, __LINE__, "Cannot setsockopt(SO_REUSEADDR) on socket %d: %s.\n", fd_socket, aapl_tcp_strerr());
        goto cleanup_and_exit;
    }

    if (ats_server_host)
    {
        aapl_log_printf(aapl, AVAGO_INFO, __func__, 0, "Attempting to connect to remote AACS ATS server: %s:%d.\n", ats_server_host, ats_server_host_port);
        aapl_ats_server_host = aapl_construct();
        aapl_ats_server_host->debug = aapl->debug;
        aapl_ats_server_host->disable_reconnect = 1;
    }
    else
    {
        sai.sin_family      = AF_INET;
        sai.sin_addr.s_addr = INADDR_ANY;
        sai.sin_port        = htons(tcp_port);

        if ((rc = bind(fd_socket, (struct sockaddr *) &sai, sizeof (sai))) < 0)
        {
            aapl_fail(aapl, __func__, __LINE__, "Cannot bind() AF_INET socket for clients on port %d: %s.\n", tcp_port, aapl_tcp_strerr());
            goto cleanup_and_exit;
        }

        if ((rc = listen(fd_socket, /* backlog = */ 1)) < 0)
        {
            aapl_fail(aapl, __func__, __LINE__, "Cannot listen() for command client on port %d: %s.\n", tcp_port, aapl_tcp_strerr());
            goto cleanup_and_exit;
        }

        if (!ats_server_host && ats_server_host_port)
        {
            int queries;
            char buffer[128];
            sai_ts.sin_family      = AF_INET;
            sai_ts.sin_addr.s_addr = INADDR_ANY;
            sai_ts.sin_port        = htons(ats_server_host_port);

            if ((rc = bind(fd_socket_ts, (struct sockaddr *) &sai_ts, sizeof (sai_ts))) < 0)
            {
                aapl_fail(aapl, __func__, __LINE__, "Cannot bind() AF_INET socket for clients on port %d: %s.\n", ats_server_host_port, aapl_tcp_strerr());
                goto cleanup_and_exit;
            }

            if ((rc = listen(fd_socket_ts, /* backlog = */ 1)) < 0)
            {
                aapl_fail(aapl, __func__, __LINE__, "Cannot listen() for command client on port %d: %s.\n", ats_server_host_port, aapl_tcp_strerr());
                goto cleanup_and_exit;
            }
            aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "AAPL ATS server version %s is now listening for TCP connections on port %d...\n", AAPL_VERSION, ats_server_host_port);

            aapl->socket = accept(fd_socket_ts, (struct sockaddr *) &client_IPaddr_ts, &addr_len_ts);
            aapl->disable_reconnect = 1;

            aapl->aacs_server = (char *) aapl_realloc(aapl, aapl->aacs_server, 32, __func__);
            strncpy(aapl->aacs_server, "(remote AAPL ATS server)", 32);
            aapl->tcp_port = 0;
            strncpy(aapl->data_char, "", 3);

            aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "AAPL ATS server is now connected on port %d.\n", ats_server_host_port);

            snprintf(buffer, 128, "AAPL AACS server %s in ATS mode", AAPL_VERSION);
            avago_aacs_send_command(aapl, buffer);
            avago_aacs_send_command_options(aapl, "ok", 1, 10);
            queries = aapl->data;
            strncpy(buffer, RES_HELP, 128);
            if (queries >= 2) avago_aacs_send_command(aapl, buffer);
            if (queries >= 3) avago_aacs_send_command(aapl, "0");

            aapl_check_capabilities(aapl);
            aapl_get_ip_info(aapl, 0);
            aapl_close_connection(aapl);
        }
        aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "AAPL AACS server version %s is now listening for TCP connections on port %d...\n", AAPL_VERSION, tcp_port);
    }


    while( !error_or_exit )
    {
        int fd_conn;

        if (ats_server_host)
        {
            aapl_connect(aapl_ats_server_host, ats_server_host, ats_server_host_port);
            fd_conn = aapl_ats_server_host->socket;
            if( fd_conn < 0 ) aapl_fail(aapl, __func__, __LINE__, "Cannot connect to remote ATS server %s:%d.\n", ats_server_host, ats_server_host_port, aapl_tcp_strerr());
        }
        else
        {
            fd_conn = accept(fd_socket, (struct sockaddr *) &client_IPaddr, &addr_len);
            if( fd_conn < 0 ) aapl_fail(aapl, __func__, __LINE__, "Cannot accept() for command client on port %d: %s.\n", tcp_port, aapl_tcp_strerr());
        }

        if( fd_conn < 0 )
        {
            error_or_exit = 1;
            break;
        }

        if (ats_server_host) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Connection to remote AACS ATS server %s:%d (socket %d) successful.\n", ats_server_host, ats_server_host_port, fd_conn);
        else                 aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Connection accepted from %s:%d (socket %d).\n", inet_ntoa(client_IPaddr.sin_addr), tcp_port, fd_conn);

        if (!(ats_server_host || ats_server_host_port))
        {
            return_code = aapl->return_code;
            aapl_connect(aapl, 0, 0);
            if( return_code != aapl->return_code )
            {
                aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "aapl_connect failed.\n");
                break;
            }
        }

#       if 0
        return_code = aapl->return_code;
        aapl_get_ip_info(aapl, /* chip_reset */ 0);
        if( return_code != aapl_get_return_code(aapl) )
        {
            aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "aapl_get_ip_info returned a negative value.\n");
            break;
        }
#       endif


        for(;;)
        {
            char *cmd;
            int read_len = 0;
            int send_len = 0;
            char *result;
            size_t res_len;

            aapl_server->socket = fd_conn;
            read_len = aapl_recv(aapl_server);
            cmd = aapl_server->data_char;

            if (read_len < 0)
            {
                #ifdef WIN32
                if( WSAGetLastError() == WSAECONNRESET)
                #else
                if( errno == ECONNRESET )
                #endif
                     aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "could not read from socket %d on port %d (%d: %s)\n", aapl->socket, tcp_port, read_len, aapl_tcp_strerr());
                else
                {
                    aapl_fail(aapl, __func__, __LINE__, "could not read from socket %d on port %d (%d: %s).\n", aapl->socket, tcp_port, read_len, aapl_tcp_strerr());
                    error_or_exit = 1;
                }
                break;
            }

            if( 0 == read_len )
            {
                aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Server got EOF on port %d.\n", tcp_port);
                break;
            }

            if ((read_len >= 1) && (cmd[read_len - 1] == '\n')) --read_len;
            if ((read_len >= 1) && (cmd[read_len - 1] == '\r')) --read_len;
            cmd[read_len] = '\0';

            if (!ats_server_host && ats_server_host_port && aapl->socket < 0)
            {
                aapl_close_connection(aapl);
                aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "AAPL ATS server lost connection with client. Waiting for new connection on port %d...\n", ats_server_host_port); aapl->socket = accept(fd_socket_ts, (struct sockaddr *) &client_IPaddr_ts, &addr_len_ts); if (aapl_connection_status(aapl) < 0)
                {
                    aapl_close_connection(aapl);
                    aapl->socket = accept(fd_socket_ts, (struct sockaddr *) &client_IPaddr_ts, &addr_len_ts);
                }
                aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "AAPL ATS server is now connected on port %d (socket %d).\n", ats_server_host_port, aapl->socket);
                aapl_get_ip_info(aapl, 0);
            }

            result = avago_aacs_process_cmd(aapl, cmd, &chip_num, &ring_num);
            aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "%s => %s\n", cmd, result);

            res_len = strlen(result);
            result[res_len++] = '\n';

            #ifdef MSG_NOSIGNAL
            if ((send_len = send(fd_conn, (void *) result, res_len, MSG_NOSIGNAL)) < 0)
            #else
            if ((send_len = send(fd_conn, (void *) result, res_len, 0)) < 0)
            #endif
            {
                aapl_fail(aapl, __func__, __LINE__, "Cannot send() %u bytes to command client on TCP port %d: %d.\n", res_len, tcp_port, send_len);
                error_or_exit = 1;
                break;
            }

            if( 0 == strncmp(result, RES_CLOSE, 5) )
                break;
            if( 0 == strncmp(result, RES_EXIT, 4) )
            {
                error_or_exit = 1;
                return_status = 1;
                break;
            }
        }

        aapl_close_connection(aapl);
        if (ats_server_host) aapl_close_connection(aapl_ats_server_host);
        else closesocket(fd_conn);
    }

cleanup_and_exit:
    closesocket(fd_socket);
    aapl_destruct(aapl_server);
    return return_status;

}

/** @brief   Starts an AACS Server and listens for requests.
 ** @details Starts (and restarts after closure) an AACS server that accepts one TCP/IP
 ** connection on tcp_port, receives zero or more AACS commands, forwards them
 ** to avago_sbus_wr(), etc, and returns response text to the command client.
 **
 ** The caller must first:
 **
 ** - Open a lower-level (back end) connection or whatever else is required for
 **   avago_sbus_wr(), etc to function, such as by using aapl_connect() (but not
 **   necessarily this function in the end user context).
 **
 ** - Start a process or thread that's taken over by this function, which only
 **   returns upon "exit" or internal error.
 **
 ** Note:  Unlike the HW server (HS1, etc), this process does not support
 ** command batching.  It expects just one command => response at a time.
 **
 ** @return Returns FALSE for internal error logged, or TRUE for client "exit" command.
 ** Does not return for client command anomalies or "close" commands.
 **/
int avago_aacs_server(
    Aapl_t *aapl,       /**< [in] Pointer to Aapl_t structure. */
    int tcp_port)       /**< [in] Port of remote to connect to. */
{
    return avago_aacs_server_options(aapl, tcp_port, NULL, 0);
}

#endif
