/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#ifdef BDK_BUILD_HOST
#include <poll.h>
#include <sys/socket.h>
#include <resolv.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#endif

static const char RPC_BEGIN = 0xa3;
static const char RPC_END = 0xa2;

// Module for supporting RPC by supplying common used building
// blocks that are slow in pure Lua.

static int string_pack(lua_State* L)
{
    /* One extra byte ofr the \0 which isn't used */
    static char hex_digits[16] = "0123456789abcdef";
    size_t input_len;
    const char *input = luaL_checklstring(L, 1, &input_len);
    luaL_Buffer output;
    luaL_buffinitsize(L, &output, input_len+2);

    luaL_addchar(&output, '"');
    while (input_len--)
    {
        int b = 0xff & *input;
        /* Escape control chars (<32), high characters (>126), double
            quote (34), and backslash (92) */
        if ((b < 32) || (b > 126) || (b == 34) || (b == 92))
        {
            luaL_addchar(&output, '\\');
            luaL_addchar(&output, hex_digits[b>>4]);
            luaL_addchar(&output, hex_digits[b&0xf]);
        }
        else
            luaL_addchar(&output, b);
        input++;
    }
    luaL_addchar(&output, '"');
    luaL_pushresult(&output);
    return 1;
}

static int string_unpack(lua_State* L)
{
    size_t loc = luaL_checkinteger(L, 1);
    size_t input_len;
    const char *input = luaL_checklstring(L, 2, &input_len);
    luaL_Buffer output;
    luaL_buffinit(L, &output);

    while (loc <= input_len)
    {
        char c = input[loc-1];
        if (c == '\\')
        {
            int i;
            int status = sscanf(input + loc, "%02x", &i);
            if (status != 1)
                return luaL_error(L, "String format error");
            luaL_addchar(&output, i);
            loc += 2;
        }
        else if (c == '"')
        {
            lua_pushnumber(L, loc + 1);
            luaL_pushresult(&output);
            return 2;
        }
        else
            luaL_addchar(&output, c);
        loc++;
    }
    return luaL_error(L, "Ran out of data processing string");
}

static int server_do_pack(lua_State* L)
{
    //local function server_do_pack(objects, ...)
    int num_args = lua_gettop(L);
    luaL_Buffer output;
    luaL_buffinit(L, &output);
    /* Note that num_args can change while the loop is running. Tables
        are inserted into the argument list */
    for (int arg=2; arg<=num_args; arg++)
    {
        switch (lua_type(L, arg))
        {
            case LUA_TNIL:
                luaL_addchar(&output, 'n');
                break;

            case LUA_TBOOLEAN:
                luaL_addchar(&output, (lua_toboolean(L, arg)) ? 't' : 'f');
                break;

            case LUA_TNUMBER:
                luaL_addchar(&output, '#');
                lua_pushvalue(L, arg);
                luaL_addvalue(&output);
                break;

            case LUA_TSTRING:
                lua_pushcfunction(L, string_pack);
                lua_pushvalue(L, arg);
                lua_call(L, 1, 1);
                luaL_addvalue(&output);
                break;

            case LUA_TTABLE:
                if (lua_getmetatable(L, arg) == 0)
                {
                    luaL_addchar(&output, '{');
                    lua_pushnil(L);  /* first key */
                    int insert_loc = arg + 1;
                    while (lua_next(L, arg) != 0)
                    {
                        luaL_checkstack(L, 3, NULL);
                        /* key, value on stack */
                        /* Copy key */
                        lua_pushvalue(L, -2);
                        /* Insert key into args list */
                        lua_insert(L, insert_loc++);
                        /* Insert value into args list */
                        lua_insert(L, insert_loc++);
                        num_args += 2;
                        /* key left on stack for next iteration */
                    }
                    /* The following special user data is used to tell the
                        code below that we need to insert the ending '}' */
                    lua_pushlightuserdata(L, server_do_pack);
                    lua_insert(L, insert_loc++);
                    num_args++;
                    break;
                }
                /* Pop the meta table off the stack */
                lua_pop(L, 1);
                /* Fall through */

            default:
            {
                /* Special marker for the end of a table */
                if (lua_touserdata(L, arg) == server_do_pack)
                {
                    luaL_addchar(&output, '}');
                    break;
                }

                /* Try and treat any other types as generic remote objects
                    All accesses to them will cause RPC calls */
                int id;
                lua_pushvalue(L, arg);
                lua_gettable(L, 1);
                if (!lua_isnil(L, -1))
                {
                    // obj_info = objects[arg] is top of the stack
                    // Get id, which is obj_info[1]
                    lua_pushinteger(L, 1);
                    lua_gettable(L, -2);
                    id = luaL_checkint(L, -1);
                    lua_pop(L, 1);
                    // Update ref count, which is obj_info[2]
                    lua_pushinteger(L, 2);
                    lua_gettable(L, -2);
                    int ref = luaL_checkint(L, -1) + 1;
                    lua_pop(L, 1);
                    lua_pushinteger(L, 2);
                    lua_pushinteger(L, ref);
                    lua_settable(L, -3);
                }
                else
                {
                    // Pop objects[arg], which was nil
                    lua_pop(L, 1);
                    // id = #objects + 1
                    id = luaL_len(L, 1) + 1;
                    // objects[id] = arg
                    lua_pushinteger(L, id);
                    lua_pushvalue(L,  arg);
                    lua_settable(L, 1);
                    // objects[arg] = {id, 1}
                    lua_pushvalue(L,  arg);
                    lua_createtable(L, 2, 0);
                    lua_pushinteger(L, 1);
                    lua_pushinteger(L, id);
                    lua_settable(L, -3);
                    lua_pushinteger(L, 2);
                    lua_pushinteger(L, 1);
                    lua_settable(L, -3);
                    lua_settable(L, 1);
                }
                luaL_addchar(&output, '@');
                lua_pushinteger(L, id);
                luaL_addvalue(&output);
                break;
            }
        }
    }
    luaL_pushresult(&output);
    return 1;
}

static int newproxy(lua_State* L)
{
    luaL_checkany(L, 1);
    lua_newuserdata(L, 0);
    if (lua_isboolean(L, 1))
    {
        if (lua_toboolean(L, 1))
        {
            lua_newtable(L);
            lua_setmetatable(L, -2);
        }
    }
    else
    {
        lua_getmetatable(L, 1);
        lua_setmetatable(L, -2);
    }
    return 1;
}

static uint8_t calc_checksum(const char *buffer, size_t length)
{
    uint8_t checksum = 0;
    while (length--)
        checksum += *buffer++;
    return checksum;
}

static int do_connect(lua_State* L)
{
    const char *filename = luaL_checkstring(L, 1);
#ifdef BDK_BUILD_HOST
    const char *ptr = strchr(filename, ':');
    if (ptr)
    {
        char name[ptr - filename + 1];
        int port = atoi(ptr + 1);
        strncpy(name, filename, ptr - filename);
        name[ptr - filename] = 0;

        struct hostent *host_info = gethostbyname(name);
        if (!host_info)
            return luaL_error(L, "Hostname lookup failed\n");

        /* Set up socket structure */
        struct sockaddr_in ejtag_addr;
        memset(&ejtag_addr, 0, sizeof(ejtag_addr));
        ejtag_addr.sin_family = AF_INET;
        ejtag_addr.sin_addr.s_addr = ((struct in_addr *)(host_info->h_addr))->s_addr;
        ejtag_addr.sin_port = htons(port);

        int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_fd == -1)
            return luaL_error(L, strerror(errno));

        int i=1;
        setsockopt(sock_fd, IPPROTO_TCP, TCP_NODELAY, &i, 4);
        int status = connect(sock_fd, (struct sockaddr *)&ejtag_addr, sizeof(ejtag_addr));
        if (status == -1)
        {
            close(sock_fd);
            return luaL_error(L, strerror(errno));
        }
        lua_pushinteger(L, sock_fd);
        return 1;
    }
#endif
    int fd = open(filename, O_RDWR);
    if (fd<0)
        return luaL_error(L, strerror(errno));
    lua_pushinteger(L, fd);
    return 1;
}

static int send_message(lua_State* L)
{
    size_t input_len;
    int fd = luaL_checkinteger(L, 1);
    const char *input = luaL_checklstring(L, 2, &input_len);

    if (fd == -1)
    {
        fflush(stdout);
        fd = 1; /* Use stdout */
    }

    uint8_t checksum = calc_checksum(input, input_len);
    char csum[4];
    snprintf(csum, sizeof(csum), "%c%02x", RPC_BEGIN, checksum);
    size_t count = write(fd, csum, 3);
    count += write(fd, input, input_len);
    count += write(fd, &RPC_END, 1);
    if (count != input_len + 4)
        return luaL_error(L, "Write failure");
    return 0;
}

static int receive_message(lua_State* L)
{
    const int TIMEOUT = 5000; /* 1sec */
    enum
    {
        LOOKING_FOR_BEGIN,
        READING_CSUM,
        LOOKING_FOR_END,
    } state = LOOKING_FOR_BEGIN;

#ifdef BDK_BUILD_HOST
    int fd = luaL_checkinteger(L, 1);
    if (fd == -1)
        fd = 0; /* Use stdin */
#else
    if (lua_toboolean(L, 2))
        state = READING_CSUM;
#endif

    luaL_Buffer out_buffer;
    luaL_buffinit(L, &out_buffer);

    uint8_t good_csum = 0;
    size_t index = 0;
retry:
    while (1)
    {
        fflush(stdout);
        char c;
#ifdef BDK_BUILD_HOST
        struct pollfd fds;
        fds.fd = fd;
        fds.events = POLLIN;
        fds.revents = 0;
        int status = poll(&fds, 1, TIMEOUT);
        if (status < 0)
            return luaL_error(L, strerror(errno));
        else if (status == 0)
            return luaL_error(L, "Timeout on read");
        else if (status != 1)
            return luaL_error(L, "Unexpected result from poll()");
        if (read(fd, &c, 1) != 1)
            return luaL_error(L, strerror(errno));
#else
        int status = bdk_readline_getkey(TIMEOUT * 1000);
        if (status < 0)
            return luaL_error(L, "Timeout on read");
        c = status;
#endif

        switch (state)
        {
            case LOOKING_FOR_BEGIN:
                if (c == RPC_BEGIN)
                {
                    state = READING_CSUM;
                    index = 0;
                }
                else
                {
                    /* Spurious data */
#ifdef BDK_BUILD_HOST
                    fputc(c, stdout);
#else
                    if (c == '\r')
                        printf("BDK waiting for remote connection\n");
#endif
                }
                break;
            case READING_CSUM:
                if (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f')))
                {
                    good_csum <<= 4;
                    good_csum |= ((c >= '0') && (c <= '9')) ? (c - '0') : (c - 'a' + 10);
                    index++;
                    if (index >= 2)
                    {
                        state = LOOKING_FOR_END;
                        index = 0;
                    }
                }
                else
                {
                    /* Corrupt data */
                    state = LOOKING_FOR_BEGIN;
                    index = 0;
#ifdef BDK_BUILD_HOST
                    fputc(c, stdout);
#endif
                }
                break;
            case LOOKING_FOR_END:
                if (c == RPC_END)
                {
                    /* Done */
                    index = 0;
                    goto done;
                }
                else
                {
                    /* Data we will need */
                    luaL_addchar(&out_buffer, c);
                }
                break;
        }
    }
done:
    /* Check the csum */
    if (good_csum != calc_checksum(out_buffer.b, out_buffer.n))
    {
        state = LOOKING_FOR_BEGIN;
        out_buffer.n = 0;
        goto retry;
    }

    luaL_pushresult(&out_buffer);
    return 1;
}

LUALIB_API int luaopen_rpc_support(lua_State *L)
{
    lua_newtable(L);
    lua_pushcfunction(L, string_pack);
    lua_setfield(L, -2, "string_pack");
    lua_pushcfunction(L, string_unpack);
    lua_setfield(L, -2, "string_unpack");
    lua_pushcfunction(L, server_do_pack);
    lua_setfield(L, -2, "server_do_pack");
    lua_pushcfunction(L, newproxy);
    lua_setfield(L, -2, "newproxy");
    lua_pushcfunction(L, do_connect);
    lua_setfield(L, -2, "connect");
    lua_pushcfunction(L, send_message);
    lua_setfield(L, -2, "send_message");
    lua_pushcfunction(L, receive_message);
    lua_setfield(L, -2, "receive_message");
    return 1;
}

