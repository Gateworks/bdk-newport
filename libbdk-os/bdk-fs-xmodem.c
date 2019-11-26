/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* This code is an optional part of the BDK. It is only linked in
    if BDK_REQUIRE() needs it */
BDK_REQUIRE_DEFINE(FS_XMODEM);

#define SOH  0x01
#define STX  0x02
#define EOT  0x04
#define ACK  0x06
#define NAK  0x15
#define CAN  0x18
#define CTRLZ 0x1A

#define DLY_1S 1000
#define MAXRETRANS 25

typedef struct
{
    int fd;
    int is_write;
    int block_size;
    int use_crc;
    uint8_t packetno;
    uint8_t pending_ack;
    int length;
    uint8_t buffer[1024];
} xmodem_state_t;

static void dbg_printf(const char *format, ...) __attribute__ ((format(printf, 1, 2)));
static void dbg_printf(const char *format, ...)
{
#if 0 /* XMODEM debug to 2nd uart */
    static FILE *debug = NULL;
    if (debug == NULL)
    {
        char uart[32];
        sprintf(uart, "/dev/n%d.uart1", bdk_numa_master());
        debug = fopen(uart, "w");
    }
    va_list args;
    va_start(args, format);
    vfprintf(debug, format, args);
    va_end(args);
    fflush(debug);
#endif
}


static int _inbyte(xmodem_state_t *state, unsigned short timeout) // msec timeout
{
    uint64_t expires = bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) * timeout / 1000 + bdk_clock_get_count(BDK_CLOCK_TIME);
    int len;
    char c;

    do
    {
        /* Use direct read so that the readline logic in stdin doesn't
            get invoked */
        len = read(state->fd, &c, 1);
        if ((len != 1) && (bdk_clock_get_count(BDK_CLOCK_TIME) > expires))
            return -1;
    } while (len != 1);
    //dbg_printf("IN <= 0x%02x\n", 0xff & c);
    return 0xff & c;
}


static void _outbyte(xmodem_state_t *state, int c)
{
    char b = c;
    //dbg_printf("out => 0x%02x\n", 0xff & c);
    write(state->fd, &b, 1);
}

/* CRC16 implementation according to CCITT standards */

static const unsigned short crc16tab[256]= {
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

static unsigned short crc16_ccitt(const void *buf, int len)
{
    register int counter;
    register unsigned short crc = 0;
    for (counter = 0; counter < len; counter++)
        crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(char *)buf++)&0x00FF];
    return crc;
}


static void flushinput(xmodem_state_t *state)
{
    while (_inbyte(state, DLY_1S * 3 >> 1) >= 0)
        ;
}


static void xmodemReceive(xmodem_state_t *state)
{
    int retry = 0;
    dbg_printf("xmodemReceive looking for block number %d\n", 0xff & state->packetno);

    if (state->pending_ack)
    {
        state->pending_ack = 0;
        dbg_printf("xmodemReceive ACK\n");
        _outbyte(state, ACK);
    }

    state->use_crc = 1;

start:
    /* When we first start a file we need to send a 'C' or a NAK to get
        things started */
    if (state->block_size == 0)
        _outbyte(state, 'C');

    dbg_printf("xmodemReceive looking for start marker\n");
    int c = _inbyte(state, 10 * DLY_1S);
    if (c<0)
    {
        retry++;
        goto start;
    }

    switch (c)
    {
        case SOH:
            dbg_printf("xmodemReceive using 128\n");
            state->block_size = 128;
            break;

        case STX:
            dbg_printf("xmodemReceive using 1024\n");
            state->block_size = 1024;
            break;

        case EOT:
            dbg_printf("xmodemReceive transfer complete\n");
            _outbyte(state, ACK);
            return;

        case CAN:
            dbg_printf("xmodemReceive cancel\n");
            _outbyte(state, CAN);
            return;

        default:
            dbg_printf("xmodemReceive error 0x%02x\n", c);
            goto retry;
    }

    c = _inbyte(state, DLY_1S);
    if (c<0)
        goto retry;

    if (c != state->packetno)
        goto retry;
    dbg_printf("xmodemReceive got packet number\n");

    c = _inbyte(state, DLY_1S);
    if (c != (0xff & ~state->packetno))
        goto retry;
    dbg_printf("xmodemReceive got ~packet number\n");

    state->length = 0;
    do
    {
        c = _inbyte(state, DLY_1S);
        if (c == -1)
        {
            if (state->use_crc)
            {
                state->length -= 2;
                uint16_t crc = state->buffer[state->length] << 8;
                crc |= state->buffer[state->length+1];
                uint16_t correct_crc = crc16_ccitt(state->buffer, state->block_size);
                dbg_printf("short correct_crc 0x%04x ", 0xffff & correct_crc);
                dbg_printf("crc 0x%04x\n", 0xffff & crc);
                if (crc != correct_crc)
                    goto retry;
                else
                    goto done;
            }
            else
            {
                state->length--;
                uint8_t correct_csum = 0;
                for (int i=0; i<state->block_size; i++)
                    correct_csum += state->buffer[i];
                dbg_printf("short correct_csum 0x%02x ", 0xff & correct_csum);
                dbg_printf("csum 0x%02x\n", state->buffer[state->length]);
                if (state->buffer[state->length] != correct_csum)
                    goto retry;
                else
                    goto done;
            }
            goto retry;
        }
        state->buffer[state->length++] = c;
    } while (state->length < state->block_size);
    dbg_printf("xmodemReceive got data\n");

    if (state->use_crc)
    {
        dbg_printf("xmodemReceive Reading CRC\n");
        c = _inbyte(state, DLY_1S);
        if (c == -1)
            goto retry;
        uint16_t crc = c << 8;
        c = _inbyte(state, DLY_1S);
        if (c == -1)
            goto retry;
        crc |= c;

        uint16_t correct_crc = crc16_ccitt(state->buffer, state->block_size);
        dbg_printf("correct_crc 0x%04x ", 0xffff & correct_crc);
        dbg_printf("crc 0x%04x\n", 0xffff & crc);

        if (crc != correct_crc)
            goto retry;
    }
    else
    {
        dbg_printf("xmodemReceive Reading CSUM\n");
        c = _inbyte(state, DLY_1S);
        if (c == -1)
            goto retry;

        uint8_t correct_csum = 0;
        for (int i=0; i<state->block_size; i++)
            correct_csum += state->buffer[i];
        dbg_printf("correct_csum 0x%02x ", 0xff & correct_csum);
        dbg_printf("csum 0x%02x\n", c);
        if (c != correct_csum)
            goto retry;
    }
done:
    state->pending_ack = 1;
    state->packetno++;
    return;

retry:
    if (c != -1)
    {
        dbg_printf("xmodemReceive flush\n");
        flushinput(state);
    }
    retry++;
    state->length = 0;
    memset(state->buffer, 0, sizeof(state->buffer));
    dbg_printf("xmodemReceive retry NAK\n");
    _outbyte(state, NAK);
    goto start;
}

static void xmodemTransmit(xmodem_state_t *state)
{
    if (state->block_size == 0)
        flushinput(state);

    while (state->block_size == 0)
    {
        dbg_printf("xmodemTransmit waiting for initial char\n");
        int c = _inbyte(state, DLY_1S);
        switch (c)
        {
            case 'C':
                dbg_printf("xmodemTransmit using 1024 byte blocks with CRC\n");
                state->block_size = 1024;
                state->use_crc = 1;
                break;
            case NAK:
                dbg_printf("xmodemTransmit using 128 byte blocks with CSUM\n");
                state->block_size = 128;
                state->use_crc = 0;
                break;
            case CAN:
                return;
        }
    }

retry:
    ;
    int length = state->length;
    if (length > state->block_size)
        length = state->block_size;

    if (length == 0)
    {
        dbg_printf("xmodemTransmit Ending transfer\n");
        _outbyte(state, EOT);
        dbg_printf("xmodemTransmit Waiting for EOT ACK\n");
        int c = _inbyte(state, DLY_1S*3);
        switch (c)
        {
            case ACK:
                dbg_printf("xmodemTransmit Transfer complete\n");
                return;
            case CAN:
                dbg_printf("xmodemTransmit Cancel\n");
                return;
            case NAK:
                dbg_printf("xmodemTransmit NAK Retry\n");
                goto retry;
            case -1:
                dbg_printf("xmodemTransmit Timeout Retry\n");
                goto retry;
            default:
                flushinput(state);
                dbg_printf("xmodemTransmit Error Retry\n");
                goto retry;
        }
    }

    dbg_printf("xmodemTransmit Starting packet %d of %d bytes\n", 0xff & state->packetno, length);
    /* Send start character */
    _outbyte(state, (state->block_size == 1024) ? STX : SOH);

    /* Send packetno */
    _outbyte(state, state->packetno);
    _outbyte(state, ~state->packetno);

    /* Send data */
    uint8_t csum = 0;
    for (int i=0; i<length; i++)
    {
        _outbyte(state, state->buffer[i]);
        csum += state->buffer[i];
    }
    for (int i=length; i<state->block_size; i++)
    {
        _outbyte(state, CTRLZ);
        csum += CTRLZ;
    }

    if (state->use_crc)
    {
        /* Send CRC */
        if (length < state->block_size)
            memset(state->buffer + length, CTRLZ, state->block_size - length);
        uint16_t crc = crc16_ccitt(state->buffer, state->block_size);
        _outbyte(state, 0xff & (crc >> 8));
        _outbyte(state, crc & 0xff);
    }
    else
    {
        /* Send CSUM */
        _outbyte(state, csum);
    }

    /* Read ACK */
    dbg_printf("xmodemTransmit Waiting for ACK\n");
    int c = _inbyte(state, DLY_1S);
    switch (c)
    {
        case ACK:
            state->length -= length;
            state->packetno++;
            dbg_printf("xmodemTransmit Block complete\n");
            if (state->length)
            {
                memcpy(state->buffer, state->buffer + length, state->length);
                goto retry;
            }
            return;
        case CAN:
            dbg_printf("xmodemTransmit Cancel\n");
            return;
        case NAK:
        case 'C':
            dbg_printf("xmodemTransmit NAK Retry\n");
            goto retry;
        case -1:
            dbg_printf("xmodemTransmit Timeout Retry\n");
            goto retry;
        default:
            flushinput(state);
            dbg_printf("xmodemTransmit Error Retry\n");
            goto retry;
    }
}


static void *xmodem_open(const char *name, int flags)
{
    if ((flags&3) == O_RDONLY)
    {
        printf("Waiting for file through XMODEM\n");
        printf("Send ^X to abort\n");
    }
    else if ((flags&3) == O_WRONLY)
    {
        printf("Sending file using XMODEM\n");
        printf("Send ^X to abort\n");
    }
    else
    {
        bdk_error("Can't open XMODEM as read+write\n");
        return NULL;
    }

    xmodem_state_t *state = calloc(1, sizeof(xmodem_state_t));
    if (state)
    {
        char uart[32];
        sprintf(uart, "/dev/n%d.uart0", bdk_numa_master());
        state->fd = open(uart, O_RDWR | O_NOCTTY);
        state->packetno = 1;
        state->is_write = ((flags&3) == O_WRONLY);
    }
    fflush(NULL);
    return state;
}


static int xmodem_close(__bdk_fs_file_t *handle)
{
    xmodem_state_t *state = handle->fs_state;

    if (!state)
        return 0;

    if (state->is_write)
    {
        if (state->length)
        {
            dbg_printf("xmodem_close writing last bytes\n");
            xmodemTransmit(state);
        }
        dbg_printf("xmodem_close finishing file\n");
        xmodemTransmit(state);
    }

    flushinput(state);
    printf("\n");
    fflush(NULL);

    int length = state->length;
    close(state->fd);
    free(state);
    handle->fs_state = NULL;

    return (length) ? -1 : 0;
}


static int xmodem_read(__bdk_fs_file_t *handle, void *buffer, int length)
{
    int bytes_read = 0;
    xmodem_state_t *state = handle->fs_state;

    if (!state)
        return 0;
    if (state->is_write)
        return -1;

    while (length)
    {
        if (state->length)
        {
            int bytes = state->length;
            if (bytes > length)
                bytes = length;
            memcpy(buffer, state->buffer, bytes);
            state->length -= bytes;
            if (state->length)
                memcpy(state->buffer, state->buffer + bytes, state->length);
            buffer += bytes;
            length -= bytes;
            bytes_read += bytes;
            if (length == 0)
                break;
        }
        if (state->length == 0)
            xmodemReceive(state);
        if (state->length == 0)
        {
            close(state->fd);
            free(state);
            handle->fs_state = NULL;
            break;
        }
    }

    return bytes_read;
}


static int xmodem_write(__bdk_fs_file_t *handle, const void *buffer, int length)
{
    xmodem_state_t *state = handle->fs_state;
    int block_size = sizeof(state->buffer);
    const void *ptr = buffer;
    int bytes_written = 0;

    if (!state)
        return -1;
    if (!state->is_write)
        return -1;

    while (length)
    {
        int needed_bytes = block_size - state->length;
        if (needed_bytes > length)
            needed_bytes = length;
        memcpy(state->buffer + state->length, ptr, needed_bytes);
        state->length += needed_bytes;
        ptr += needed_bytes;
        bytes_written += needed_bytes;
        length -= needed_bytes;

        if (state->length == block_size)
        {
            xmodemTransmit(state);
            if (state->length != 0)
            {
                close(state->fd);
                free(state);
                handle->fs_state = NULL;
                break;
            }
        }
    }

    return bytes_written;
}

static const __bdk_fs_ops_t bdk_fs_xmodem_ops =
{
    .open = xmodem_open,
    .close = xmodem_close,
    .read = xmodem_read,
    .write = xmodem_write,
    .list = NULL,
};

int __bdk_fs_xmodem_init(void)
{
    return bdk_fs_register("/xmodem", &bdk_fs_xmodem_ops);
}