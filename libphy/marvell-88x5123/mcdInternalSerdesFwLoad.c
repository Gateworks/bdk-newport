/*******************************************************************************
*              (c), Copyright 2001, Marvell International Ltd.                 *
* THIS CODE CONTAINS CONFIDENTIAL INFORMATION OF MARVELL SEMICONDUCTOR, INC.   *
* NO RIGHTS ARE GRANTED HEREIN UNDER ANY PATENT, MASK WORK RIGHT OR COPYRIGHT  *
* OF MARVELL OR ANY THIRD PARTY. MARVELL RESERVES THE RIGHT AT ITS SOLE        *
* DISCRETION TO REQUEST THAT THIS CODE BE IMMEDIATELY RETURNED TO MARVELL.     *
* THIS CODE IS PROVIDED "AS IS". MARVELL MAKES NO WARRANTIES, EXPRESSED,       *
* IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY, COMPLETENESS OR PERFORMANCE.   *
*******************************************************************************/

/********************************************************************
This file contains updated copies of functions from Avago library.
********************************************************************/
#define AAPL_ENABLE_INTERNAL_FUNCTIONS
#include "mcdInternalSerdesFwLoad.h"
#include "mcdUtils.h"

#ifndef ASIC_SIMULATION

#define COPY_3IDX_MAC(_src, _dst, _chip, _ring, _sbus, _field) \
    _dst->_field[_chip][_ring][_sbus] = _src->_field[_chip][_ring][_sbus];

#define COPY_2IDX_MAC(_src, _dst, _chip, _ring, _field) \
    _dst->_field[_chip][_ring] = _src->_field[_chip][_ring];

void mcd_copy_aapl_ip_types_db(Aapl_t *src_aapl, Aapl_t *dst_aapl, int refresh_source)
{
    unsigned short chip, ring, sbus;
    Avago_addr_t   addr_struct;
    uint           addr;

    for (chip = 0; (chip < AAPL_MAX_CHIPS); chip++)
    {
        addr_struct.chip = chip;
        for (ring = 0; (ring < AAPL_MAX_RINGS); ring++)
        {
            addr_struct.ring = ring;
            for (sbus = 0; (sbus < 256); sbus++)
            {
                addr_struct.sbus = sbus;
                addr = avago_struct_to_addr(&addr_struct);
                if (refresh_source)
                {
                    /* spico_running field erased by aapl_get_ip_type */
                    COPY_3IDX_MAC(src_aapl, dst_aapl, chip, ring, sbus, spico_running);
                    aapl_get_ip_type(src_aapl, addr);
                    aapl_get_ip_rev(src_aapl, addr);
                }
                COPY_3IDX_MAC(src_aapl, dst_aapl, chip, ring, sbus, ip_rev);
                COPY_3IDX_MAC(src_aapl, dst_aapl, chip, ring, sbus, firm_rev);
                COPY_3IDX_MAC(src_aapl, dst_aapl, chip, ring, sbus, firm_build);
                COPY_3IDX_MAC(src_aapl, dst_aapl, chip, ring, sbus, ip_type);
                COPY_3IDX_MAC(src_aapl, dst_aapl, chip, ring, sbus, lsb_rev);
                if (! refresh_source)
                {
                    aapl_get_ip_type(dst_aapl, addr);
                    aapl_get_ip_rev(dst_aapl, addr);
                    /* spico_running field erased by aapl_get_ip_type */
                    COPY_3IDX_MAC(src_aapl, dst_aapl, chip, ring, sbus, spico_running);
                }
            }
            COPY_2IDX_MAC(src_aapl, dst_aapl, chip, ring, max_sbus_addr);
        }
    }
}

void mcd_avago_spico_upload_reset(
    Aapl_t *aapl,       /**< Pointer to Aapl_t structure */
    uint sbus_addr_in,  /**< Sbus address */
    BOOL ram_bist)      /**< If TRUE, perform spico_ram_bist prior to upload */
{
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;
    avago_addr_to_struct(sbus_addr_in, &addr_struct);

    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next);
         st;
         st = aapl_broadcast_next(aapl,&next,&start,&stop) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);
        if( !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 3, AVAGO_SPICO, AVAGO_SERDES, AVAGO_M4) )
            continue;

        if( start.sbus != stop.sbus && (avago_sbus_rd(aapl, sbus_addr, 0xfd) & 0x1) == 0x1 )
        {
            aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "Skipping reset of SBus address %s because an upload was requested to %s and the ignore broadcast bit on this serdes was set.\n", aapl_addr_to_str(sbus_addr), aapl_addr_to_str(sbus_addr_in));
            continue;
        }
        MCD_DBG_CRITIC_INFO(
            "mcd_avago_spico_upload_reset SBus %s\n",
            aapl_addr_to_str(sbus_addr));
        avago_sbus_reset(aapl, sbus_addr, 0);
        if( ram_bist )
            avago_spico_ram_bist(aapl, sbus_addr);
    }
}

int mcd_avago_spico_upload_check_crc(
    Aapl_t *aapl,       /**< Pointer to Aapl_t structure */
    uint sbus_addr_in,  /**< Sbus address */
    int words)          /**< Length of ROM image */
{
    int return_code = aapl->return_code;
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;

    avago_addr_to_struct(sbus_addr_in, &addr_struct);

    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next);
         st;
         st = aapl_broadcast_next(aapl,&next,&start,&stop) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);
        if( !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 3, AVAGO_SPICO, AVAGO_SERDES, AVAGO_M4) )
            continue;

        MCD_DBG_CRITIC_INFO(
            "mcd_avago_spico_upload_check_crc begin - sbus_addr 0x%X \n", sbus_addr);

        if( start.sbus != stop.sbus && (avago_sbus_rd(aapl, sbus_addr, 0xfd) & 0x1) == 0x1 )
        {
            MCD_DBG_CRITIC_INFO(
                "Skipping CRC check of SBus address %s because an upload was requested to %s and the ignore broadcast bit on this serdes was set.\n",
                aapl_addr_to_str(sbus_addr), aapl_addr_to_str(sbus_addr_in));
            continue;
        }
        if (avago_spico_crc(aapl, sbus_addr))
        {
            aapl_set_ip_type(aapl, sbus_addr);
        }
        MCD_DBG_CRITIC_INFO(
            "mcd_avago_spico_upload_check_crc CHK_CRC - sbus_addr 0x%X, rc %d \n",
            sbus_addr, aapl->return_code);
        if( aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SPICO) )
        {
            int end_addr = avago_spico_int(aapl, sbus_addr, 0x1C, 0);
            MCD_DBG_CRITIC_INFO(
                "mcd_avago_spico_upload_check_crc SPICO int 0x1C - sbus_addr 0x%X \n", sbus_addr);
            if( end_addr < words )
            {
                int crc = avago_spico_int(aapl, sbus_addr, 0x1A, 0);
                MCD_DBG_CRITIC_INFO(
                    "mcd_avago_spico_upload_check_crc SPICO int 0x1A - sbus_addr 0x%X src 0x%X \n",
                    sbus_addr, crc);
                if( crc )
                    aapl_log_printf(aapl, AVAGO_DEBUG2, __func__, __LINE__, "SBus %s, SDI CRC passed.\n", aapl_addr_to_str(sbus_addr));
                else
                    aapl_fail(aapl, __func__, __LINE__, "SBus %s, SDI CRC failed. CRC interrupt returned 0x%04x\n", aapl_addr_to_str(sbus_addr), crc);
            }
        }
    }
    return return_code == aapl->return_code ? 0 : -1;
}

/* This function should do exactly the same as original avago_spico_upload */
/* coded just to check it                                                  */
/** @brief   Upload SPICO machine code and check CRC. */
/**          Works for broadcast and individual addresses. */
/** @return  On success, returns 0. */
/** @return  On error, decrements aapl->return_code and returns -1. */
int mcd_avago_spico_upload(
    Aapl_t *aapl,       /**< Pointer to Aapl_t structure */
    uint sbus_addr_in,  /**< Sbus address */
    BOOL ram_bist,      /**< If TRUE, perform spico_ram_bist prior to upload */
    int words,          /**< Length of ROM image */
    const short *rom)   /**< Avago-supplied ROM image */
{
    if( !aapl_check_ip_type(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 6, AVAGO_SPICO, AVAGO_SERDES, AVAGO_SERDES_BROADCAST, AVAGO_SPICO_BROADCAST, AVAGO_M4, AVAGO_SERDES_M4_BROADCAST) ||
        !aapl_check_process(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 2, AVAGO_PROCESS_F, AVAGO_PROCESS_B) )
        return 0;
    mcd_avago_spico_upload_reset(aapl, sbus_addr_in, ram_bist);

    aapl_log_printf(
        aapl, AVAGO_DEBUG1, __func__, __LINE__,
        "Uploading %d bytes of SPICO machine code to SBus address %s.\n",
        words, aapl_addr_to_str(sbus_addr_in));
    spico_upload_image(aapl, sbus_addr_in, words, rom);

    return mcd_avago_spico_upload_check_crc(aapl, sbus_addr_in, words);
}

/* SWAP IMAGE */

void mcd_avago_spico_upload_swap_image_start(
    Aapl_t *aapl,       /**< [in] Pointer to AAPL structure */
    uint sbus_addr_in)  /**< [in] SBus address of SerDes */
{
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;

    avago_addr_to_struct(avago_make_sbus_master_addr(sbus_addr_in), &addr_struct);

    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next);
         st;
         st = aapl_broadcast_next(aapl,&next,&start,&stop) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);

        if( !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SPICO) )
            continue;

        avago_firmware_get_rev(aapl, sbus_addr);
        if( !aapl_get_spico_running_flag(aapl,sbus_addr) )
        {
            MCD_DBG_CRITIC_INFO(
                "upload_swap_image_start - can not be uploaded: address %s is not running.\n",
                aapl_addr_to_str(sbus_addr));
            continue;
        }
        avago_sbus_rmw(aapl, sbus_addr, 7, 0, 2);

        if( aapl_get_ip_rev(aapl, avago_make_sbus_controller_addr(sbus_addr)) >= 0x00be )
        {
            int base_addr = avago_spico_int(aapl, sbus_addr, 0x1C, 0);
            avago_sbus_wr( aapl, sbus_addr, 0x05, 0x01);
            avago_sbus_rmw(aapl, sbus_addr, 0x01, 0x0200, 0x0200);
            avago_sbus_wr(aapl, sbus_addr, 0x03, 0x00000000 | base_addr);
            avago_sbus_wr(aapl, sbus_addr, 0x03, 0x80000000 | base_addr);
            MCD_DBG_CRITIC_INFO(
                "upload_swap_image_start - init sequence1.\n",
                aapl_addr_to_str(sbus_addr));
        }
        else
        {
            avago_sbus_wr( aapl, sbus_addr, 0x05, 0x01);
            avago_sbus_rmw(aapl, sbus_addr, 0x01, 0x0C00, 0x0C00);
            MCD_DBG_CRITIC_INFO(
                "upload_swap_image_start - init sequence2.\n",
                aapl_addr_to_str(sbus_addr));
        }
    }
}

int mcd_avago_spico_upload_swap_image_check_crc(
    Aapl_t *aapl,       /**< [in] Pointer to AAPL structure */
    uint sbus_addr_in)  /**< [in] SBus address of SerDes */
{
    int crc = 0;
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;

    avago_addr_to_struct(avago_make_sbus_master_addr(sbus_addr_in), &addr_struct);

    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next);
         st;
         st = aapl_broadcast_next(aapl,&next,&start,&stop) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);

        if( !aapl_check_ip_type(aapl, sbus_addr, __func__, __LINE__, FALSE, 1, AVAGO_SPICO) )
            continue;

        MCD_DBG_CRITIC_INFO(
            "Swap image check CRC begin address %s..\n",
            aapl_addr_to_str(sbus_addr));

        if( !aapl_get_spico_running_flag(aapl,sbus_addr) )
        {
            continue;
        }
        /* cannot be called before writing 0 to reg 0x5 */
        /* avago_firmware_get_rev(aapl, sbus_addr);     */
        /* using derived running flag                    */


        if( aapl_get_ip_rev(aapl, avago_make_sbus_controller_addr(sbus_addr)) >= 0x00be )
        {
            avago_sbus_wr(aapl, sbus_addr, 0x03, 0x00000000);
            avago_sbus_rmw(aapl, sbus_addr, 0x01, 0x0000, 0x0200);
            avago_sbus_wr( aapl, sbus_addr, 0x05, 0x00);
            crc = avago_spico_int(aapl, sbus_addr, 0x1A, 0);
            MCD_DBG_CRITIC_INFO(
                "Swap image check CRC address %s. sequence1, crc %d\n",
                aapl_addr_to_str(sbus_addr), crc);
        }
        else
        {
            avago_sbus_rmw(aapl, sbus_addr, 0x01, 0x0000, 0x0C00);
            avago_sbus_wr( aapl, sbus_addr, 0x05, 0x00);
            crc = avago_spico_int(aapl, sbus_addr, 0x04, 0);
            MCD_DBG_CRITIC_INFO(
                "Swap image check CRC address %s. sequence2, crc %d\n",
                aapl_addr_to_str(sbus_addr), crc);
        }
        if( crc == 1 )
        {
            aapl_log_printf(aapl, AVAGO_DEBUG2, __func__,__LINE__,"SBus %s, Swap CRC passed\n", aapl_addr_to_str(sbus_addr));
        }
        else
        {
            aapl_fail(aapl, __func__, __LINE__, "SBus %s, Swap CRC failed, interrupt returned %d\n", aapl_addr_to_str(sbus_addr), crc);
            crc = 0;
        }
        avago_firmware_get_rev(aapl, sbus_addr);
    }
    return ((crc != 0) ? 0/*OK*/ : 1/*fail*/);
}

void mcd_avago_spico_upload_swap_image_load(
    Aapl_t *aapl,       /**< [in] Pointer to AAPL structure */
    uint sbus_addr_in,  /**< [in] SBus address of SerDes */
    int words,          /**< [in] Number of elements in rom */
    const short *rom)   /**< [in] Swap image to upload */
{
    BOOL st;
    Avago_addr_t addr_struct, start, stop, next;

    if( !aapl_check_ip_type(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 4, AVAGO_SPICO, AVAGO_SERDES, AVAGO_SERDES_BROADCAST, AVAGO_M4) ||
        !aapl_check_process(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 2, AVAGO_PROCESS_B, AVAGO_PROCESS_F))
        return;

    avago_addr_to_struct(avago_make_sbus_master_addr(sbus_addr_in), &addr_struct);

    for( st = aapl_broadcast_first(aapl, &addr_struct, &start, &stop, &next);
         st;
         st = aapl_broadcast_next(aapl,&next,&start,&stop) )
    {
        uint sbus_addr = avago_struct_to_addr(&next);

        MCD_DBG_CRITIC_INFO("Check before Upload Swap Image sbus_addr: 0x%X \n", sbus_addr);

        if( !aapl_get_spico_running_flag(aapl,sbus_addr) )
        {
            MCD_DBG_CRITIC_INFO(
                "Swap image can not be uploaded because the SPICO at address %s is not running.\n",
                aapl_addr_to_str(sbus_addr));
            continue;
        }
        MCD_DBG_CRITIC_INFO(
            "SBus %s, Uploading %d bytes of SerDes swap machine code.\n",
            aapl_addr_to_str(sbus_addr), words);

        if( aapl_get_ip_rev(aapl, avago_make_sbus_controller_addr(sbus_addr)) >= 0x00be )
        {
            MCD_DBG_CRITIC_INFO(
                "SBus %s, Loading Swap Image to production SBM \n",
                aapl_addr_to_str(sbus_addr));

            spico_burst_upload(aapl, sbus_addr, 0x14, words, rom);
        }
        else
        {
            int base_addr = 0x400;
            int word;
            MCD_DBG_CRITIC_INFO(
                "SBus %s, Loading Swap Image to test chip SBM, base_addr=0x%x \n",
                aapl_addr_to_str(sbus_addr), base_addr);
            for( word=0; word < words; word++ )
                avago_sbus_wr(aapl, sbus_addr, 0x04, 0x8000 | (rom[word] << 16) | (base_addr+word));
        }
    }
}

/* This function should do exactly the same as original avago_spico_upload_swap_image */
/* coded just to check it                                                             */
/** @brief   Internal function that uploads SWAP image into SBM. */
/** @return  Returns 1 on success, 0 on failure. */
int mcd_avago_spico_upload_swap_image(
    Aapl_t *aapl,       /**< [in] Pointer to AAPL structure */
    uint sbus_addr_in,  /**< [in] SBus address of SerDes */
    int words,          /**< [in] Number of elements in rom */
    const short *rom)   /**< [in] Swap image to upload */
{
    if( !aapl_check_ip_type(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 4, AVAGO_SPICO, AVAGO_SERDES, AVAGO_SERDES_BROADCAST, AVAGO_M4) ||
        !aapl_check_process(aapl, sbus_addr_in, __func__, __LINE__, TRUE, 2, AVAGO_PROCESS_B, AVAGO_PROCESS_F))
        return 0;
    mcd_avago_spico_upload_swap_image_start(aapl, sbus_addr_in);

    mcd_avago_spico_upload_swap_image_load(aapl, sbus_addr_in, words, rom);

    return mcd_avago_spico_upload_swap_image_check_crc(aapl, sbus_addr_in);
}

/* ADDED Broadcast Functions */

int mcd_avago_spico_upload_broacast(
    mcd_avago_drop_shadow_function drop_shadow_func,
    uint aapl_amount,              /* *<amount of Pointers to Aapl_t structure */
    Aapl_t_ptr aapl_ptr_arr[],     /**< array of Pointers to Aapl_t structure  */
    Aapl_t_ptr aapl_broadcast_ptr, /**< Pointer to broadcast Aapl_t structure  */
    uint sbus_addr_in,             /**< Sbus address */
    BOOL ram_bist,                 /**< If TRUE, perform spico_ram_bist prior to upload */
    int words,                     /**< Length of ROM image */
    const short *rom)              /**< Avago-supplied ROM image */
{
    uint aapl_index;
    int  rc, totalRc;

    for (aapl_index = 0; (aapl_index < aapl_amount); aapl_index++)
    {
        mcd_avago_spico_upload_reset(aapl_ptr_arr[aapl_index], sbus_addr_in, ram_bist);
        if (aapl_ptr_arr[aapl_index]->return_code != 0)
        {
            MCD_DBG_CRITIC_INFO("mcd_avago_spico_upload_reset failed\n");
        }
    }
    mcd_copy_aapl_ip_types_db(aapl_ptr_arr[0], aapl_broadcast_ptr, 1);
    drop_shadow_func(aapl_broadcast_ptr);

    aapl_log_printf(
        aapl_ptr_arr[0], AVAGO_DEBUG1, __func__, __LINE__,
        "Uploading %d bytes of SPICO machine code to SBus address %s.\n",
        words, aapl_addr_to_str(sbus_addr_in));
    spico_upload_image(aapl_broadcast_ptr, sbus_addr_in, words, rom);
    if (aapl_broadcast_ptr->return_code != 0)
    {
        MCD_DBG_CRITIC_INFO("spico_upload_image to broadcast failed\n");
    }
    for (aapl_index = 0; (aapl_index < aapl_amount); aapl_index++)
    {
        drop_shadow_func(aapl_ptr_arr[aapl_index]);
        mcd_copy_aapl_ip_types_db(aapl_broadcast_ptr, aapl_ptr_arr[aapl_index], 0);
    }

    totalRc = 0;
    for (aapl_index = 0; (aapl_index < aapl_amount); aapl_index++)
    {
        rc = mcd_avago_spico_upload_check_crc(aapl_ptr_arr[aapl_index], sbus_addr_in, words);
        if ((totalRc == 0) && (rc != 0)) totalRc = rc;
        if (aapl_ptr_arr[aapl_index]->return_code != 0)
        {
            MCD_DBG_CRITIC_INFO("mcd_avago_spico_upload_check_crc failed\n");
        }
    }
    return totalRc;
}

int mcd_avago_spico_upload_swap_image_broadcast(
    mcd_avago_drop_shadow_function drop_shadow_func,
    uint aapl_amount,              /**< amount of Pointers to Aapl_t structure */
    Aapl_t_ptr aapl_ptr_arr[],     /**< array of Pointers to Aapl_t structure  */
    Aapl_t_ptr aapl_broadcast_ptr, /**< Pointer to broadcast Aapl_t structure  */
    uint sbus_addr_in,             /**< [in] SBus address of SerDes */
    int words,                     /**< [in] Number of elements in rom */
    const short *rom)              /**< [in] Swap image to upload */
{
    uint aapl_index;
    int  rc, totalRc;

    for (aapl_index = 0; (aapl_index < aapl_amount); aapl_index++)
    {
        mcd_avago_spico_upload_swap_image_start(aapl_ptr_arr[aapl_index], sbus_addr_in);
        if (aapl_ptr_arr[aapl_index]->return_code != 0)
        {
            MCD_DBG_CRITIC_INFO("mcd_avago_spico_upload_swap_image_start failed\n");
        }
    }
    mcd_copy_aapl_ip_types_db(aapl_ptr_arr[0], aapl_broadcast_ptr, 1);
    drop_shadow_func(aapl_broadcast_ptr);

    mcd_avago_spico_upload_swap_image_load(aapl_broadcast_ptr, sbus_addr_in, words, rom);
    if (aapl_broadcast_ptr->return_code != 0)
    {
        MCD_DBG_CRITIC_INFO("mcd_avago_spico_upload_swap_image_load failed\n");
    }
    for (aapl_index = 0; (aapl_index < aapl_amount); aapl_index++)
    {
        drop_shadow_func(aapl_ptr_arr[aapl_index]);
        mcd_copy_aapl_ip_types_db(aapl_broadcast_ptr, aapl_ptr_arr[aapl_index], 0);
    }

    totalRc = 0;
    for (aapl_index = 0; (aapl_index < aapl_amount); aapl_index++)
    {
        rc = mcd_avago_spico_upload_swap_image_check_crc(aapl_ptr_arr[aapl_index], sbus_addr_in);
        if ((totalRc == 0) && (rc != 0)) totalRc = rc;
        if (aapl_ptr_arr[aapl_index]->return_code != 0)
        {
            MCD_DBG_CRITIC_INFO("mcd_avago_spico_upload_swap_image_check_crc failed\n");
        }
    }
    return totalRc;
}


#endif /*ASIC_SIMULATION*/



