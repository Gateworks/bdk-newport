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
 ** @brief Internal library functions.
 **/

#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "aapl.h"

/** @defgroup Address IP Addressing Functions
 ** @{
 **/

/** @brief  Initializes an Avago_addr_t structure to default values.
 ** @return void
 **/
void avago_addr_init(Avago_addr_t *addr_struct)
{
    addr_struct->chip = 0;
    addr_struct->ring = 0;
    addr_struct->sbus = 0;
    addr_struct->lane = AVAGO_ADDR_IGNORE_LANE;
    addr_struct->next_addr = 0;
}

#define AVAGO_ADDR_INVALID_LANE (0xbad)

/** @brief  Converts an address integer into an address structure.
 ** @return On success, returns TRUE.
 ** @return Returns FALSE if addr is not a recognized value.
 **/
BOOL avago_addr_to_struct(
    uint addr,                  /**< [in]  Address value. */
    Avago_addr_t *addr_struct)  /**< [out] Hardware address structure. */
{
    int lane_field = (addr >> 16) & 0x0f;
    avago_addr_init(addr_struct);
    addr_struct->chip = (addr >> 12) & 0x0f;
    addr_struct->ring = (addr >>  8) & 0x0f;
    addr_struct->sbus =  addr        & 0xff;
    addr_struct->lane = (addr >> 16) & 0x0f;
    if( addr_struct->chip == 0x0f ) addr_struct->chip = AVAGO_ADDR_BROADCAST;
    if( addr_struct->ring == 0x0f ) addr_struct->ring = AVAGO_ADDR_BROADCAST;
    if( addr_struct->sbus == 0xff ) addr_struct->sbus = AVAGO_ADDR_BROADCAST;
    if(      lane_field >  7 ) addr_struct->lane = lane_field - 8;
    else if( lane_field == 0 ) addr_struct->lane = AVAGO_ADDR_IGNORE_LANE;
    else if( lane_field == 1 ) addr_struct->lane = AVAGO_ADDR_QUAD_LOW;
    else if( lane_field == 2 ) addr_struct->lane = AVAGO_ADDR_QUAD_HIGH;
    else if( lane_field == 3 ) addr_struct->lane = AVAGO_ADDR_QUAD_ALL;
    else if( lane_field == 4 ) addr_struct->lane = AVAGO_ADDR_BROADCAST;
    else                       addr_struct->lane = AVAGO_ADDR_INVALID_LANE;
    return (addr & 0xfff00000) == 0;
}

/** @brief  Converts hardware address structure into an address integer.
 ** @return The address value representation of the hardware address.
 **/
uint avago_struct_to_addr(
    Avago_addr_t *addr_struct)  /**< [in] Hardware address structure. */
{
    uint addr, lane;
    switch( addr_struct->lane )
    {
    case AVAGO_ADDR_IGNORE_LANE: lane = 0; break;
    case AVAGO_ADDR_QUAD_LOW:    lane = 1; break;
    case AVAGO_ADDR_QUAD_HIGH:   lane = 2; break;
    case AVAGO_ADDR_QUAD_ALL:    lane = 3; break;
    case AVAGO_ADDR_BROADCAST:   lane = 4; break;
    case 0: case 1: case 2: case 3:
    case 4: case 5: case 6: case 7: lane = 8 + addr_struct->lane; break;
    default: lane = 7;
    }
    addr = (addr_struct->chip & 0x0f) << 12 |
           (addr_struct->ring & 0x0f) <<  8 |
           (addr_struct->sbus & 0xff) <<  0 |
           (             lane       ) << 16;
    return addr;
}

/** @brief  Combines the chip, ring and sbus values into an address integer.
 ** @return The address integer.
 **/
uint avago_make_addr3(
    int chip,           /**< Chip number, range [0..15]. */
    int ring,           /**< Ring number, range [0..15]. */
    int sbus)           /**< SerDes number, range [0..255]. */
{
    Avago_addr_t addr_struct;
    avago_addr_init(&addr_struct);
    addr_struct.chip = chip;
    addr_struct.ring = ring;
    addr_struct.sbus = sbus;
    return avago_struct_to_addr(&addr_struct);
}

/** @brief  Combines the chip, ring and sbus values into an address integer.
 ** @return The address integer.
 **/
uint avago_make_addr4(
    int chip,           /**< Chip number, range [0..15]. */
    int ring,           /**< Ring number, range [0..15]. */
    int sbus,           /**< SerDes number, range [0..255]. */
    int lane)           /**< SerDes lane number, range [0..7,AVAGO_ADDR_QUAD_LOW,AVAGO_ADDR_QUAD_HIGH,AVAGO_ADDR_QUAD_ALL,AVAGO_ADDR_BROADCAST,AVAGO_ADDR_IGNORE_LANE]. */
{
    Avago_addr_t addr_struct;
    avago_addr_init(&addr_struct);
    addr_struct.chip = chip;
    addr_struct.ring = ring;
    addr_struct.sbus = sbus;
    addr_struct.lane = lane;
    return avago_struct_to_addr(&addr_struct);
}

/** @brief  Sets the sbus portion of an input address to the new value,
 **         and sets the lane to be ignored.
 ** @return The input address modified to reference the given sbus.
 **/
uint avago_make_sbus_addr(
    uint addr,  /**< [in] Chip/ring/sbus address. */
    int sbus)   /**< [in] New sbus address. */
{
    Avago_addr_t addr_struct;
    avago_addr_to_struct(addr,&addr_struct);
    addr_struct.sbus = sbus;
    addr_struct.lane = AVAGO_ADDR_IGNORE_LANE;
    return avago_struct_to_addr(&addr_struct);
}

/** @brief  Modifies the addr_struct passed in to be all broadcast addresses (chip, ring, SBus, etc)
 ** @return The address integer, and modifies the addr_struct passed in.
 **/
uint avago_addr_init_broadcast(Avago_addr_t *addr_struct)
{
    avago_addr_init(addr_struct);
    addr_struct->chip = AVAGO_ADDR_BROADCAST;
    addr_struct->ring = AVAGO_ADDR_BROADCAST;
    addr_struct->sbus = AVAGO_ADDR_BROADCAST;
    addr_struct->lane = AVAGO_ADDR_BROADCAST;
    return avago_struct_to_addr(addr_struct);
}


/** @brief  Returns the SBus Master address for the addressed chip and ring.
 ** @return The SBus Master address corresponding to given input address.
 **/
uint avago_make_sbus_master_addr(
    uint addr)  /**< [in] Chip/ring address. */
{
    return avago_make_sbus_addr(addr, AVAGO_SBUS_MASTER_ADDRESS);
}

/** @brief  Returns the SBus Controller address for the addressed chip and ring.
 ** @return The SBus Controller address corresponding to given input address.
 **/
uint avago_make_sbus_controller_addr(
    uint addr)  /**< [in] Chip/ring address. */
{
    return avago_make_sbus_addr(addr, AVAGO_SBUS_CONTROLLER_ADDRESS);
}

/** @brief  Returns the SerDes Broadcast address for the addressed chip and ring.
 ** @return The SerDes Broadcast address for the addressed chip and ring.
 **/
uint avago_make_serdes_broadcast_addr(
    uint addr)  /**< [in] Chip/ring address. */
{
    return avago_make_sbus_addr(addr, AVAGO_SERDES_BROADCAST_ADDRESS);
}

/** @brief  Modifies the lane portion of an input address.
 ** @return The input address modified to reference the given lane.
 **/
uint avago_make_sbus_lane_addr(
    uint addr,  /**< [in] Chip/ring/sbus address. */
    int lane)   /**< [in] New lane address. */
{
    Avago_addr_t addr_struct;
    avago_addr_to_struct(addr,&addr_struct);
    addr_struct.lane = lane;
    return avago_struct_to_addr(&addr_struct);
}

static const int AAPL_BROADCAST_FIRST = 0x8000;

/** @cond INTERNAL */

/** @brief   Begins traversal of addresses selected by sbus_addr.
 ** @details start, stop and first are updated based on any
 **          chip, ring or sbus broadcast addresses.
 **          start and stop should be passed unchanged to aapl_broadcast_next(),
 **          and first should be passed as the addr field.
 **          Flags can be the logical OR of several values:
 **           + AAPL_BROADCAST_IGNORE_LANE - causes all returned lane values to be AVAGO_ADDR_IGNORE_LANE.
 **             Use when lanes are not applicable.
 **           + AAPL_BROADCAST_NO_ITER_LANE - causes addr lane value to be passed through unchanged.
 **             Use to send broadcast requests rather than iterate over the lane range.
 **           + AAPL_BROADCAST_LANE - lane value AVAGO_ADDR_IGNORE_LANE is treated as AVAGO_ADDR_BROADCAST.
 **              Other values of lane are passed through unchanged.
 **              Use to address all SerDes even when broadcast wasn't requested.
 **           + AAPL_BROADCAST_NO_ITER_SBUS - causes addr sbus value to be passed through unchanged.
 **             Use to send broadcast requests rather than iterate over the sbus range.
 ** @return  Returns TRUE and first is initialized to the first address.
 **/
BOOL aapl_broadcast_first(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr,     /**< [in] SBus slice (broadcast) address. */
    Avago_addr_t *start,    /**< [out] Start of hardware address range. */
    Avago_addr_t *stop,     /**< [out] End of hardware address range. */
    Avago_addr_t *first,    /**< [out] First hardware address. */
    uint flags)             /**< [in] Flags to control iteration. */
{
    BOOL is_broadcast_sbus = addr->sbus > AVAGO_MAX_RING_ADDRESS && addr->sbus != AVAGO_SPICO_BROADCAST && addr->sbus != AVAGO_SBUS_CONTROLLER_ADDRESS;
    BOOL iter_on_sbus = !(flags & AAPL_BROADCAST_NO_ITER_SBUS) && is_broadcast_sbus;
    avago_addr_init(first);
    avago_addr_init(stop);
    avago_addr_init(start);
    start->next_addr = addr->next_addr;
    first->chip = start->chip = addr->chip != AVAGO_BROADCAST ? addr->chip : 0;
    first->ring = start->ring = addr->ring != AVAGO_BROADCAST ? addr->ring : 0;
    first->sbus = start->sbus = iter_on_sbus ? 1 : addr->sbus;
    stop->chip  = addr->chip != AVAGO_BROADCAST ? addr->chip : (aapl->chips > 0) ? (aapl->chips - 1) : 0;
    stop->ring  = addr->ring != AVAGO_BROADCAST ? addr->ring : (aapl->sbus_rings > 0) ? aapl->sbus_rings - 1 : 0;
    if( is_broadcast_sbus )
    {
        uint c, r;
        stop->sbus = 0;
        for( c = start->chip; c <= stop->chip; c++ )
        for( r = start->ring; r <= stop->ring; r++ )
        {
            if( stop->sbus < aapl->max_sbus_addr[c][r] + 2U )
                stop->sbus = aapl->max_sbus_addr[c][r] + 2U;
        }
    }
    else
        stop->sbus = addr->sbus;
    first->lane = start->lane = stop->lane = addr->lane;
    if( flags & AAPL_BROADCAST_IGNORE_LANE )
    {
        first->lane = start->lane = stop->lane = AVAGO_ADDR_IGNORE_LANE;
    }
    else if( !(flags & AAPL_BROADCAST_NO_ITER_LANE) )
    {
        if( addr->lane == AVAGO_ADDR_BROADCAST || addr->lane == AVAGO_ADDR_QUAD_ALL ||
            ((flags & AAPL_BROADCAST_LANE) && addr->lane == AVAGO_ADDR_IGNORE_LANE)
            )
        {
            first->lane = start->lane = 0;
            stop->lane = 7;
        }
        else if( addr->lane == AVAGO_ADDR_QUAD_HIGH )
        {
            first->lane = start->lane = 4;
            stop->lane = 7;
        }
        else if( addr->lane == AVAGO_ADDR_QUAD_LOW )
        {
            first->lane = start->lane = 0;
            stop->lane = 3;
        }
    }
    else if( (flags & AAPL_BROADCAST_LANE) && (addr->lane == AVAGO_ADDR_IGNORE_LANE) )
    {
        first->lane = start->lane = stop->lane = AVAGO_ADDR_QUAD_ALL;
    }

    return aapl_broadcast_next(aapl, first, start, stop, flags | AAPL_BROADCAST_FIRST);
}

BOOL aapl_is_octal_p1(Aapl_t *aapl, uint addr)
{
    uint ip_rev = aapl_get_ip_rev(aapl, addr);
    return ip_rev == 0xe8 || ip_rev == 0xc3
        || ip_rev == 0xea || ip_rev == 0xf3
        || ip_rev == 0xe9 || ip_rev == 0xee
        || ip_rev == 0xf7 || ip_rev == 0xf8
        || ip_rev == 0xf9;
}

static BOOL is_octal_p1(Aapl_t *aapl, Avago_addr_t *addr)
{
    uint sbus_addr = avago_struct_to_addr(addr) & 0xffff;
    return aapl_is_octal_p1(aapl, sbus_addr);
}

/** @brief   Continues traversal of addresses between start and stop.
 ** @details addr must contain the previous address on input and is updated to the next address on output.
 ** @return  Updates addr and returns TRUE while traversing the selected addresses.
 ** @return  Returns FALSE when all addresses have been traversed.
 **/
BOOL aapl_broadcast_next(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr,     /**< [in,out] Previous/next hardware address. */
    Avago_addr_t *start,    /**< [in] Start of hardware address range. */
    Avago_addr_t *stop,     /**< [in] End of hardware address range. */
    uint flags)             /**< [in] Flags to control iteration. */
{
    aapl_log_printf(aapl,AVAGO_DEBUG9,__func__,__LINE__,"Broadcast_next(addr=%s,start=%s,stop=%s,flags=0x%x,next=%x)\n",aapl_addr_to_str(avago_struct_to_addr(addr)),aapl_addr_to_str(avago_struct_to_addr(start)),aapl_addr_to_str(avago_struct_to_addr(stop)),flags,start->next_addr);
    if( !(flags & AAPL_BROADCAST_FIRST) && ((addr->lane == AVAGO_ADDR_IGNORE_LANE) || (++(addr->lane) > stop->lane) || (addr->lane > 3 && addr->lane < 8 && !is_octal_p1(aapl, addr))) )
    {
        addr->lane = start->lane;
        if( ++(addr->sbus) > stop->sbus )
        {
            addr->sbus = start->sbus;
            if( ++(addr->ring) > stop->ring )
            {
                addr->ring = start->ring;
                if( ++(addr->chip) > stop->chip )
                {
                    if( !start->next_addr )
                    {
                        aapl_log_printf(aapl,AVAGO_DEBUG8,__func__,__LINE__,"Broadcast_next returning FALSE.\n");
                        return FALSE;
                    }
                    return aapl_broadcast_first(aapl, start->next_addr, start, stop, addr, flags);
                }
            }
        }
    }

    if( addr->lane != AVAGO_ADDR_IGNORE_LANE )
    {
        uint sbus_addr = avago_struct_to_addr(addr);
        Avago_ip_type_t ip_type = aapl_get_ip_type(aapl, sbus_addr);
        if( ip_type != AVAGO_P1 )
            addr->lane = AVAGO_ADDR_IGNORE_LANE;
    }
    aapl_log_printf(aapl,AVAGO_DEBUG9,__func__,__LINE__,"Broadcast_next returning %s\n",aapl_addr_to_str(avago_struct_to_addr(addr)));
    return TRUE;
}

/** @brief   Checks if the selected address matches a SerDes device.
 ** @details Checks if addr_struct is a D6, M4 or P1 SerDes broadcast address
 **              and addr references an instance of the broadcast type
 **              and the SerDes is not ignoring broadcasts;
 **          OR if addr_struct is not a SerDes broadcast
 **              and addr references any SerDes type.
 ** @return  Returns TRUE if addr references a matching SerDes device.
 **          The ignore flag is set if broadcast type and ignore bit is set.
 **/
BOOL aapl_addr_selects_fw_device(
    Aapl_t *aapl,               /**< [in] Pointer to Aapl_t structure. */
    Avago_addr_t *addr_struct,  /**< [in] Original address struct. */
    uint sbus_addr,             /**< [in] Device address. */
    BOOL *ignore)               /**< [out] If addr selected by broadcast, returns SerDes broadcast ignore bit. */
{
    if( !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 4, AVAGO_SERDES, AVAGO_SPICO, AVAGO_M4, AVAGO_P1) )
        return FALSE;

    if( (addr_struct->sbus == AVAGO_SERDES_D6_BROADCAST && aapl_get_ip_type(aapl, sbus_addr) != AVAGO_SERDES) ||
        (addr_struct->sbus == AVAGO_SPICO_BROADCAST     && aapl_get_ip_type(aapl, sbus_addr) != AVAGO_SPICO) ||
        (addr_struct->sbus == AVAGO_SERDES_M4_BROADCAST && aapl_get_ip_type(aapl, sbus_addr) != AVAGO_M4) ||
        (addr_struct->sbus == AVAGO_SERDES_P1_BROADCAST && aapl_get_ip_type(aapl, sbus_addr) != AVAGO_P1) )
        return FALSE;

    if( addr_struct->sbus > AVAGO_MAX_RING_ADDRESS &&
        addr_struct->sbus != AVAGO_SBUS_MASTER_ADDRESS )
    {
        BOOL ig = avago_sbus_rd(aapl, sbus_addr, 0xfd) & 0x1;
        if( ignore ) *ignore = ig;
        return !ig;
    }
    return TRUE;
}
/** @endcond */

/** @} */

/** @cond INTERNAL */

/** @details          Sleeps until a number of milliseconds has elapsed.
 ** @return           Void
 **/
void ms_sleep(
    uint ms_delay)  /**< [in] The number of milliseconds to wait before returning. */
{
#ifdef MS_SLEEP

    MS_SLEEP(ms_delay);

#elif defined __MINGW32__ || defined WIN32

    Sleep(ms_delay);

#elif defined __CYGWIN__

    usleep(ms_delay * 1000);

#elif defined unix

    extern int usleep(unsigned int);
    usleep(ms_delay * 1000);

#elif 0

    struct timespec req, rem;
    req.tv_sec = ms_delay / 1000;
    req.tv_nsec = (ms_delay % 1000) * 1000000;
    while( nanosleep(&req,&rem) != 0 && errno == EINTR )
    {
        req = rem;
    }

#else

    clock_t end = clock() + (ms_delay * CLOCKS_PER_SEC / 1000);

    while( clock() < end )
        continue;

#endif
}
/** @endcond */

#ifndef aapl_malloc
/** @details Wrapper around malloc() with standardized error handling.
 **          Note:  Use aapl_free() to delete the memory, but remember
 **          to clear the pointer to it afterward, if the pointer is reused.
 ** @return  Pointer to resulting memory (which is not initialized).
 ** @return  On error, decrements aapl->return_code and returns NULL.
 **/
void *aapl_malloc(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    size_t bytes,           /**< [in] Size to allocate. */
    const char *description)/**< [in] Description of object for error reporting. */
{
    void *memp = AAPL_MALLOC(bytes);
    if( !memp ) aapl_fail(aapl, __func__, __LINE__, "Cannot malloc() %u bytes for %s.\n", bytes, description);
    return memp;
}
/** @details Wrapper around realloc() with standardized error handling.
 **          Note:  Use aapl_free() to delete the memory, but remember
 **          to clear the pointer to it afterward, if the pointer is reused.
 ** @return  Pointer to resulting memory (which is not initialized) beyond the
 **          original allocation.
 ** @return  On error, decrements aapl->return_code and returns NULL.
 **/
void *aapl_realloc(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    void *ptr,              /**< [in] Pointer to memory reallocate to new bytes. */
    size_t bytes,           /**< [in] Size of new space. */
    const char *description)/**< [in] Description of object for error reporting. */
{
    void *memp = AAPL_REALLOC(ptr,bytes);
    if( !memp ) aapl_fail(aapl, __func__, __LINE__, "Cannot realloc() %u bytes for %s.\n", bytes, description);
    return memp;
}

/** @details Wrapper around free() for abstraction and NULL ptr release checking.
 ** @return  void. On error, decrements aapl->return_code.
 **/
void aapl_free(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    void *ptr,              /**< [in] Pointer to memory to free. */
    const char *description)/**< [in] Description of object for error reporting. */
{
    if( ptr )
        AAPL_FREE(ptr);
    else if( description )
        aapl_fail(aapl, __func__, __LINE__, "Free NULL ptr for %s\n", description);
    else
        aapl_fail(aapl, __func__, __LINE__, "Free NULL ptr for unknown.\n");
}
#endif

/** @cond INTERNAL */

/** @details Provide function where it is missing
 ** @return  Same as strncmp, except comparisons are case insensitive.
 **/
int aapl_strncasecmp(const char *s1, const char *s2, size_t n)
{
    int left = 0, right = 0;
    size_t i;
    for( i = 0; i < n; i++ )
    {
        left = *s1++;
        right = *s2++;
        if( !left || !right )
            break;
        if( left == right )
            continue;

        left = tolower(left);
        right = tolower(right);
        if( left != right )
            break;
    }
    return left - right;
}

/** @details Provide function where it is missing
 ** @return  Same as strcmp, except comparisons are case insensitive.
 **/
int aapl_strcasecmp(const char *s1, const char *s2)
{
    int left = 0, right = 0;
    for(;;)
    {
        left = *s1++;
        right = *s2++;
        if (!left || !right)
            break;
        if (left == right)
            continue;

        left = tolower(left);
        right = tolower(right);
        if (left != right)
            break;
    }
    return left - right;
}

/** @details Provide function where it is missing
 ** @details Same functionality as strdup.
 ** @return  Returns AAPL_MALLOC'd space on success.  The return value should be freed by calling AAPL_FREE(ret).
 **          Returns NULL if an allocation error occurs.
 **/
char *aapl_strdup(const char *string)
{
    char *buf = (char *)AAPL_MALLOC(strlen(string)+1);
    return buf ? strcpy(buf,string) : NULL;
}

/** @details  Replaces all occurrences of the character \b search with the character \b replace.
 **/
void aapl_str_rep(char *str, char search, char replace)
{
    char *ptr = str;
    while( 0 != (ptr = strchr(ptr, search)) )
        *ptr++ = replace;
}

/** @details Provide function where it is missing
 ** @details Same functionality as strtok_r
 ** @return  Returns pointer to first token, and updates saveptr for next call.
 **/
char *aapl_strtok_r(char *str, const char *delim, char **saveptr)
{
    int len;
    if( !str ) str = *saveptr;
    str += strspn(str,delim);
    len = strcspn(str,delim);
    *saveptr = str + len;
    if( **saveptr != 0 )
        *(*saveptr)++ = '\0';
    return len ? str : 0;
}

/** @brief Converts data to a 32 character ASCII encoded binary string with optional
 ** underscores every 8 bits.
 **
 ** @return str is returned; if bits requested is greater than 32, then NULL is returned.
 **/

char *aapl_hex_2_bin(
        char *str,              /**< Output string, also returned on success */
        uint data,              /**< Data to convert. */
        int underscore_en,      /**< Non-zero to add underscores every 8 bits. */
        int bits)               /**< Number of bits to convert. */
{
    /* Only convert if the number of bits requested to be equal to or less
       than the width of the data variable. */
    #define kBitsPerByte 8
    if ( bits <= (int)(sizeof(data) * kBitsPerByte) ) {
        char *pDest = str;
        int offset = (kBitsPerByte*(bits%kBitsPerByte) - bits);
        int i;
        if (underscore_en)
        {
            for (i = 1; i <= bits; ++i)
            {
                /* Check bit value MSB to LSB*/
                *pDest++ = ((data >> (bits - i)) & 0x1) + 0x30;

                /* Insert underscore at byte boundry when enabled. */
                if ((i != bits) && ((i+offset)%kBitsPerByte == 0)) *pDest++ = '_';
            }
        }
        else
        {
            for (i = 1; i <= bits; ++i) *pDest++ = ((data >> (bits - i)) & 0x1) + 0x30; /* Check bit value MSB to LSB*/
        }

        /* Insert end of string marker. */
        *pDest = '\0';

        return str;
    }
    return NULL;
}

/** @brief Works like strftime, but always returns local time information.
 ** @return The number of characters placed into buf, not including the
 **         terminating null byte, or 0 if the results do not fit.
 **/
#ifndef KERNEL_INCLUDES
size_t aapl_local_strftime(char *buf, size_t size_of_buf, const char *format)
{
    time_t t = time(0);
    struct tm *tm_info = localtime(&t);
    return strftime(buf, size_of_buf, format, tm_info);
}

#else

size_t aapl_local_strftime(char *buf, size_t size_of_buf, const char *format)
{
    struct timeval time;
    unsigned long local_time;
    struct tm tm_info;

    do_gettimeofday(&time);
    local_time = (u32)(time.tv_sec - (sys_tz.tz_minuteswest * 60));
    time_to_tm(local_time, 0, &tm_info);

    return snprintf(buf, size_of_buf, format, tm_info);
}

#endif

#if AAPL_ENABLE_FILE_IO
/** @details Reads the file contents into memory.
 ** @return  Allocated buffer with contents of file.  Call aapl_free() to
 **          release the buffer after use.
 **/
char *aapl_read_file(
    Aapl_t *aapl,           /**< [in] Pointer to Aapl_t structure. */
    const char *filename)   /**< [in] Name of file to read. */
{
    int size;
    char *data;
    FILE *file;
    file = fopen(filename, "r");

    if( !file )
    {
        aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Could not open file: %s\n",filename);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    aapl_log_printf(aapl, AVAGO_DEBUG1, __func__, __LINE__, "Reading %d bytes from file: %s\n", size, filename);

    data = (char *) aapl_malloc(aapl, sizeof(char) * size + 1, filename);

    if( !data ) { fclose(file); return 0; }

    fread(data, 1, size, file);
    data[size] = 0;

    fclose(file);
    return data;
}
#endif

/** @endcond */
