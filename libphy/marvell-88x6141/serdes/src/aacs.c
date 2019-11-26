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
 ** @brief AACS functions.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

#if AAPL_ALLOW_AACS

#define AAPL_LOG_PRINT8 if(aapl->debug >= AVAGO_DEBUG8) aapl_log_printf
#define AAPL_LOG_PRINT9 if(aapl->debug >= AVAGO_DEBUG9) aapl_log_printf

#define AAPL_CMD_LOG_BUF_SIZE ((AAPL_MAX_CMDS_BUFFERED * AAPL_SBUS_CMD_LOG_BUF_SIZE) + 128)

/** @cond INTERNAL */

const char *aapl_tcp_strerr()
{
    # ifdef WIN32
        static char error[20];
        snprintf(error, 19, "%d", WSAGetLastError());
        return error;
    #else
        return strerror(errno);
    # endif
}


void aapl_check_capabilities(
    Aapl_t *aapl)           /**< [in] Pointer to Aapl_t structure. */
{
    int no_cmd_buff = 0;
    BOOL verilog;

    int set_capabilities = !aapl->capabilities;
    aapl->prior_connection = 1;

    avago_aacs_send_command(aapl, "version");
    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "AAPL socket %d connected to %s:%d (%s).\n", aapl->socket, aapl->aacs_server, aapl->tcp_port, aapl->data_char);


    verilog = 0 != strstr(aapl->data_char, "Verilog");

    no_cmd_buff = strstr(aapl->data_char, "AAPL AACS server") || strstr(aapl->data_char, "aacs_server.pl");

    if (strstr(aapl->data_char, "ATS"))
    {
        int queries = 2;
        char buf[10];
        #if AAPL_ENABLE_DIAG
        queries += 1;
        #endif
        snprintf(buf, 9, "%d", queries);
        avago_aacs_send_command(aapl, buf);
    }
    else if (aapl->capabilities) return;

    avago_aacs_send_command(aapl, "help");
    if (set_capabilities && strstr(aapl->data_char, "spico_int"))  aapl->capabilities |= AACS_SERVER_SPICO_INT;
    if (set_capabilities && strstr(aapl->data_char, "sbus_reset")) aapl->capabilities |= AACS_SERVER_SBUS_RESET;
    if (set_capabilities && verilog)                               aapl->capabilities |= AACS_SERVER_NO_CRC;

    if (no_cmd_buff && !strstr(aapl->data_char, "batching supported"))
    {
        aapl->max_cmds_buffered = 0;
        aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Command buffering disabled for aacs_server.pl, and older AAPL AACS servers.\n");
    }
    else
    {
        if (!strstr(aapl->data_char, "ATS"))
        {
            int x = aapl->max_cmds_buffered;
            avago_aacs_send_command(aapl, "status");
            if (strstr(aapl->data_char, "AACS Server buf size: "))
                x = aapl_strtol(strstr(aapl->data_char, "AACS Server buf size: ") + strlen("AACS Server buf size: "), 0, 10) * 3 / 4;
            if (aapl->max_cmds_buffered > x) aapl->max_cmds_buffered = x;
        }
        aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Command buffering set to %d.\n", aapl->max_cmds_buffered);
    }

#if AAPL_ENABLE_DIAG
    if (strstr(aapl->data_char,"diag"))
    {
        avago_aacs_send_command_options(aapl, "diag size", 1, 10);
        aapl_log_printf(aapl, AVAGO_DEBUG3, __func__, __LINE__, "Remote diag size: %d. Local: %d\n", aapl->data, sizeof(Avago_diag_config_t));
        if (set_capabilities && aapl->data == sizeof(Avago_diag_config_t))
            aapl->capabilities |= AACS_SERVER_DIAG;
    }
#endif

    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "AAPL capabilities set to: 0x%08x.\n", aapl->capabilities);
}

/** @brief   Closes an AACS connection.
 ** @details Sets aapl->socket to -1 on success.
 ** @return Returns 0.
 **/
int avago_aacs_close_fn(Aapl_t *aapl)
{
    if( aapl->socket >= 0 )
    {
        int ret = closesocket(aapl->socket);
        if( ret < 0 )
            aapl_log_printf(aapl, AVAGO_WARNING, __func__, __LINE__, "close() failed: %s on socket %d.\n", aapl_tcp_strerr(), aapl->socket);
        aapl->socket = -1;
#       ifdef WIN32
        WSACleanup();
#       endif
    }
    return 0;
}

/** @brief   Opens an AACS connection.
 ** @details Sets the aapl->socket variable to non-negative on success, and -1 on failure.
 ** @return  On success, returns 1.  On failure, decrements aapl->return_code and returns 0.
 **/
int avago_aacs_open_fn(Aapl_t *aapl)
{
    struct sockaddr_in serv_addr;
    struct hostent *server = NULL;
    int retries = 0;

# ifdef WIN32
    WSADATA wsaData;
    WORD vers_req = MAKEWORD(2,2);
    if( 0 != WSAStartup(vers_req,&wsaData) )
    {
        aapl_fail(aapl, __func__, __LINE__, "WSAStartup failed, WSAGetLastError(): %s\n", aapl_tcp_strerr());
        aapl->socket = -1;
        return 0;
    }
# endif

    aapl->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( aapl->socket < 0 )
    {
        aapl_fail(aapl, __func__, __LINE__, "socketfd == -1, errno: %s\n", aapl_tcp_strerr());
#       ifdef WIN32
        WSACleanup();
#       endif
        return 0;
    }

    if (aapl->aacs_server) server = gethostbyname(aapl->aacs_server);
    if( server == NULL )
    {
        if (aapl->aacs_server) aapl_fail(aapl, __func__, __LINE__, "aacs_server (%s) could not be found (%s).\n", aapl->aacs_server, aapl_tcp_strerr());
        else                   aapl_fail(aapl, __func__, __LINE__, "aacs_server not specified.\n");
        aapl_close_connection2(aapl);
        return 1;
    }
    serv_addr.sin_family = AF_INET;
    memmove((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr_list[0], server->h_length);

    serv_addr.sin_port = htons(aapl->tcp_port);

    {
        int rc = 1;
        setsockopt(aapl->socket, SOL_SOCKET, SO_KEEPALIVE, (char *) &rc, sizeof(rc));
    }

    while( connect(aapl->socket,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0 )
    {
        #ifdef WIN32
        errno = WSAGetLastError();
        if( errno == WSAECONNREFUSED || errno == WSAEBADF || errno == WSAENETUNREACH || errno ==WSAEHOSTUNREACH)
        #else
        if( errno == ECONNREFUSED || errno == EBADF || errno == ENETUNREACH || errno == EHOSTUNREACH || errno == EINVAL || errno == EADDRNOTAVAIL || errno == ETIMEDOUT )
        #endif
        {
            aapl_fail(aapl, __func__, __LINE__, "Connection attempt %d failed when connecting to the AACS Server at %s:%d (%s). %s is now returning.\n", retries, aapl->aacs_server, aapl->tcp_port, aapl_tcp_strerr(), __func__);
            aapl_close_connection2(aapl);
            return 0;
        }
        retries ++;
        if (retries > 10 || aapl->debug) aapl_log_printf(aapl, AVAGO_INFO, __func__, __LINE__, "Connection attempt %d failed when connecting to the AACS Server at %s:%d (%s)\n", retries, aapl->aacs_server, aapl->tcp_port, aapl_tcp_strerr());
        ms_sleep(10);
        aapl_sigint_check(aapl);
    }

    if (!aapl->prior_connection)
        aapl_check_capabilities(aapl);
    else aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "AAPL reconnected to %s:%d (socket #%d).\n", aapl->aacs_server, aapl->tcp_port, aapl->socket);
    return 1;
}


int aapl_send(Aapl_t *aapl, char * data, int len, int tcp_port)
{
    int send_len = 0;
    #ifdef MSG_NOSIGNAL
    if ((send_len = send(aapl->socket, (void *) data, len, MSG_NOSIGNAL)) < 0)
    #else
    if ((send_len = send(aapl->socket, (char *) data, len, 0)) < 0)
    #endif
    {
        aapl_fail(aapl, __func__, __LINE__, "Cannot send() %u bytes to command client on TCP port %d: %d.\n", strlen(data), tcp_port, data);
        return -1;
    }
    return send_len;
}

int aapl_recv(Aapl_t *aapl)
{
    int bytes_recv;
    bytes_recv = recv(aapl->socket, aapl->data_char, aapl->data_char_size-1, 0);

    if (bytes_recv <= 0) return 0;

    while (aapl->data_char[bytes_recv-1] != 0x0a)
    {
        int last_bytes_recv;
        if (bytes_recv >= (aapl->data_char_size - 10))
        {
            char * ptr = (char *) aapl_realloc(aapl, aapl->data_char, aapl->data_char_size * 2, __func__);
            if (ptr)
            {
                aapl->data_char = ptr;
                aapl->data_char_size *= 2;
                AAPL_LOG_PRINT8(aapl, AVAGO_DEBUG8, __func__, __LINE__,
                    "Allocating %d additional bytes to data_char buffer. Size is now %d bytes.\n", aapl->data_char_size/2, aapl->data_char_size);
            }
            else
            {
                aapl_fail(aapl, __func__, __LINE__, "Realloc failed after recv() of %d bytes. Your data has been corrupted.\n", bytes_recv);
                aapl->data_char[bytes_recv-1] = 0x0a;
                aapl->data_char[bytes_recv] = 0x00;
                return -1;
            }
        }
        last_bytes_recv = recv(aapl->socket, aapl->data_char+bytes_recv, aapl->data_char_size-1-bytes_recv, 0);
        if (last_bytes_recv > 0) bytes_recv += last_bytes_recv;
        else return -1;
    }
    aapl->data_char[bytes_recv] = 0;
    return bytes_recv;
}

/** @endcond */

uint aapl_aacs_sbus_fn(Aapl_t *aapl, uint addr, unsigned char reg_addr, unsigned char command, uint *sbus_data, uint recv_data_back)
{
    Avago_addr_t addr_struct;
    char sbus_cmd[AAPL_SBUS_CMD_LOG_BUF_SIZE+1];
    avago_addr_to_struct(addr,&addr_struct);

    snprintf(sbus_cmd, AAPL_SBUS_CMD_LOG_BUF_SIZE, "sbus %x%x%02x %02x %02x 0x%08x",
        addr_struct.chip, addr_struct.ring, addr_struct.sbus & 0xff, reg_addr, command, *sbus_data);

    avago_aacs_send_command_options(aapl, sbus_cmd, recv_data_back, /* strtol = */ 2);
    *sbus_data = (uint) aapl->data;
    return TRUE;
}
#endif


/** @brief Forces any buffered AACS commands to be flushed */
void avago_aacs_flush(
    Aapl_t *aapl)
{
    avago_aacs_send_command(aapl, "");
}


/** @brief Sends a command via AACS to the connected AACS server
 **        and returns the results.
 ** @details The "command" must be a C string (with no newline).
 ** @return  Saves the results from the command sent to the aacs_server in
 **         aapl->data_char and then returns that data.  In addition,
 **         aapl->data is set to the length of the returned string.
 **/
const char *avago_aacs_send_command(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    const char *command)    /**< [in] The AACS command to send. */
{
    return avago_aacs_send_command_options(aapl, command, /* recv_data_back */ 1, /* strtol */ 0);
}

/** @brief Sends a command via AACS to the connected AACS server
 **        and returns an integer result
 ** @details The "command" must be a C string (with no newline).
 ** @return  Saves the results from the command sent to the aacs_server in
 **         aapl->data_char and returns strtol(aapl->data_char,16).
 **         The returned integer is also stored in aapl->data.
 **/
int avago_aacs_send_command_int(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    const char *command)    /**< [in] The AACS command to send. */
{
    avago_aacs_send_command_options(aapl, command, /* recv_data_back */ 1, /* strtol */ 16);
    return aapl->data;
}

/** @brief Sends a command via AACS to the aacs_server pointed to by aapl
 **        and return the results.
 ** @details The "command" must be a C string (with no newline).
 ** @return  Saves the results from the command sent to the aacs_server in
 **         aapl->data_char and returns strtol(aapl->data_char, 16).
 **         The returned integer is also stored in aapl->data.
 **         If recv_data_back is 0 or 2, this value will be 0.
 **/
int avago_aacs_send_command_options_int(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    const char *command,    /**< [in] The AACS command to send. */
    int recv_data_back)     /**< [in] If 0, queue command, return value not wanted. */
                            /**<      If 1, send commands, read and return last result. */
                            /**<      If 2, queue command, return value wanted later. */
                            /**<      If 3, send commands, return all results. */
{
    avago_aacs_send_command_options(aapl, command, recv_data_back, 16);
    return aapl->data;
}

/** @brief Sends a command via AACS to the aacs_server pointed to by aapl
 **        and return the results.
 ** @details The "command" must be a C string (with no newline).
 ** @return The results of the command sent to the aacs_server is saved in
 **         aapl->data_char and also returned.
 **         If recv_data_back is 0 or 2, this value will be "0".
 **         In addition, aapl->data is set to the length of this string
 **         unless strtol is non-zero and recv_data_back is 1, in which
 **         case it is set to the decoded value of the returned string.
 **/
const char *avago_aacs_send_command_options(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    const char *command,    /**< [in] The AACS command to send. */
    int recv_data_back,     /**< [in] If 0, queue command, return value not wanted. */
                            /**<      If 1, send commands, read and return last result. */
                            /**<      If 2, queue command, return value wanted later. */
                            /**<      If 3, send commands, return all results. */
    int strtol)             /**< [in] If non-zero, interpret return string as */
                            /**<      base strtol (2..16) and store the result */
                            /**<      in aapl->data as a long value. */
{
#if AAPL_ALLOW_OFFLINE_SBUS
    if (aapl->communication_method == AVAGO_OFFLINE)
    {
        aapl->data = 0;
        aapl_log_printf(aapl, AVAGO_DATA_CHAR, 0, 0, "");

        if (0==strcmp("jtag 32 02b6 0", command))
            aapl_log_printf(aapl, AVAGO_DATA_CHAR, 0, 0, "00000000000000000000000000000000");
        else if (0==strcmp("status", command))
            aapl_log_printf(aapl, AVAGO_DATA_CHAR, 0, 0, "Version:    AAPL AACS Server %s;Current chip:         0 (of 0..%d);", AAPL_VERSION, aapl->chips-1);

        return aapl->data_char;
    }
#endif

#if AAPL_ALLOW_AACS
    if (aapl_is_aacs_communication_method(aapl))
    {
        size_t cmd_len = strlen(command);
        int bytes_sent = 0;
        int flags = 0;
        BOOL error_occurred = FALSE;
        AAPL_AACS_LOCK;

        #ifdef MSG_NOSIGNAL
        flags = MSG_NOSIGNAL;
        #endif

        if (!aapl->buf_cmd) aapl->buf_cmd = (char *)aapl_malloc(aapl, AAPL_CMD_LOG_BUF_SIZE, __func__);
        if (!aapl->buf_cmd_end) aapl->buf_cmd_end = aapl->buf_cmd;

#       define APPEND(end, cmd, len) { strcpy(end, cmd); end += len; }
#       define APPEND_CMD(cmd,len) APPEND(aapl->buf_cmd_end,cmd,len)
#       define RESET_CMD()  (aapl->buf_cmd_end = aapl->buf_cmd)
#       define LENGTH_CMD() (aapl->buf_cmd_end - aapl->buf_cmd)

        if (aapl_reconnect(aapl, command) < 0)
        {
            AAPL_AACS_UNLOCK;
            return aapl->data_char;
        }

        if (aapl->cmds_buffered == 0) RESET_CMD();
        else                          APPEND_CMD(";",1);

        if (recv_data_back==0)        APPEND_CMD("@",1);

        if( cmd_len > (size_t)(AAPL_CMD_LOG_BUF_SIZE - LENGTH_CMD() - 4) )
        {
            if( LENGTH_CMD() > 0 )
            {
                bytes_sent = send(aapl->socket, aapl->buf_cmd, LENGTH_CMD(), flags);
                if( bytes_sent <= 0 )
                {
                    aapl->socket = -1;
                    aapl_fail(aapl, __func__, __LINE__, "send() failed: %s.\n", aapl_tcp_strerr());
                }
            }
            RESET_CMD();
        }

        if (cmd_len == 0 && aapl->cmds_buffered > 0)
        {
            aapl_log_printf(aapl, AVAGO_DEBUG9, __func__, __LINE__, "Flush requested. Sending version command to flush buffer (%d %d).\n", cmd_len, aapl->cmds_buffered);
            recv_data_back = 1;
            command = "version";
            cmd_len = strlen(command);
        }
        else if (cmd_len == 0)
        {
            aapl_log_printf(aapl, AVAGO_DEBUG9, __func__, __LINE__, "Flush requested, but buffer empty (%d %d).\n", cmd_len, aapl->cmds_buffered);
            strcpy(aapl->data_char, "");
            aapl->data = 0;
            AAPL_AACS_UNLOCK;
            return aapl->data_char;
        }

        if( cmd_len > (AAPL_CMD_LOG_BUF_SIZE - 4))
        {
            bytes_sent = send(aapl->socket, command, cmd_len, flags);
            if( bytes_sent <= 0 )
            {
                aapl->socket = -1;
                aapl_fail(aapl, __func__, __LINE__, "send() failed: %s.\n", aapl_tcp_strerr());
            }
        }
        else
            APPEND_CMD(command,cmd_len);
        aapl->cmds_buffered += 1;


        if ((recv_data_back==0 || recv_data_back==2)
            && aapl->cmds_buffered < aapl->max_cmds_buffered
            && (uint)LENGTH_CMD() < (AAPL_CMD_LOG_BUF_SIZE-32) )
        {
            strcpy(aapl->data_char, "0");
            aapl->data = 1;
        }
        else
        {
            int bytes_recv;
            int retry = 0;
            APPEND_CMD("\n",1);
            while (1)
            {
                bytes_sent = 0;
                bytes_recv = 0;

                if( aapl->cmds_buffered > 1 )
                    AAPL_LOG_PRINT9(aapl, AVAGO_DEBUG9, __func__, __LINE__, "Sending %d batched commands (%d bytes) %s", aapl->cmds_buffered, (int) LENGTH_CMD(), aapl->buf_cmd);

                bytes_sent = send(aapl->socket, aapl->buf_cmd, LENGTH_CMD(), flags);
                if( bytes_sent == LENGTH_CMD() )
                    bytes_recv = aapl_recv(aapl);

                if (bytes_recv <= 0 || bytes_sent <= 0)
                {
                    if (retry == 0 && !aapl->disable_reconnect)
                    {
                        retry ++;
                        aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "%d bytes sent and %d bytes recv -- most likely due to remote socket closure (%s). Will retry once. Command sent: %s\n", bytes_sent, bytes_recv, aapl_tcp_strerr(), aapl->buf_cmd);
                        aapl_close_connection2(aapl);
                        aapl_reconnect(aapl, aapl->buf_cmd);
                        continue;
                    }
                    else aapl_close_connection2(aapl);
                    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "%d bytes sent and %d bytes recv on try %d (%s). Returning.\n", bytes_recv, bytes_sent, retry, aapl_tcp_strerr());
                    aapl->cmds_buffered = 0;
                    aapl->data_char[0] = 0x0a;
                    aapl->data_char[1] = 0x00;
                    AAPL_AACS_UNLOCK;
                    return aapl->data_char;
                }
                else
                {
                    if (aapl->cmds_buffered > 1) AAPL_LOG_PRINT9(aapl, AVAGO_DEBUG9, __func__, __LINE__, "Result from %d batched commands (%d bytes): %s", aapl->cmds_buffered, bytes_recv, aapl->data_char);
                    break;
                }
            }

            if (bytes_recv) bytes_recv -= 1;
            aapl->data_char[bytes_recv] = 0x00;

            if (!aapl->suppress_errors && (strstr(aapl->data_char, "WARNING") || strstr(aapl->data_char, "ERROR")))
            {
                aapl_fail(aapl, __func__, __LINE__, "Received error or warning from AACS Server: %s -> %s\n", command, aapl->data_char);
                error_occurred = TRUE;
            }

            if (aapl->cmds_buffered > 1 && recv_data_back == 1)
            {
                char *lastreply = strrchr(aapl->data_char,';');
                if( lastreply )
                {
                    lastreply++;
                    bytes_recv = strlen(lastreply);
                    memmove(aapl->data_char,lastreply,bytes_recv+1);
                }
                else
                {
                    aapl_fail(aapl, __func__, __LINE__, "Received unexpected returned data for a buffered command from remote AACS Server. Sent %d commands: %s -> %s\n",
                        aapl->cmds_buffered, aapl->buf_cmd, aapl->data_char);
                }
            }
            aapl->cmds_buffered = 0;
            aapl->data = bytes_recv;
        }

        if( strtol && recv_data_back == 1 )
        {
            char *result_ptr = 0;
            if( error_occurred )
            {
                result_ptr = strstr(aapl->data_char, "\x1\x1\x1");
                if (result_ptr) result_ptr += 4;
            }
            if (!result_ptr) result_ptr = aapl->data_char;
            aapl->data = aapl_strtoul(result_ptr, NULL, strtol);
        }

        if( aapl->debug >= 5 )
        {
            if( strtol && recv_data_back != 3 )
                aapl_log_printf(aapl, AVAGO_DEBUG9, __func__, __LINE__, "%s -> 0x%08x (%s)\n", command, aapl->data, aapl->data_char);
            else
                aapl_log_printf(aapl, AVAGO_DEBUG9, __func__, __LINE__, "%s -> %s\n", command, aapl->data_char);
        }

        if (aapl->data_char[0] == 0x1 && aapl->data_char[1] == 0x1) aapl_str_rep(aapl->data_char, 0x2, 0xa);
        AAPL_AACS_UNLOCK;
        aapl_sigint_check(aapl);
        return aapl->data_char;
    }

#endif

    (void)aapl;
    (void)command;
    (void)recv_data_back;
    (void)strtol;
    return "";
}

