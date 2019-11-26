/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "libbdk-arch/bdk-csrs-pbus.h"

#define MAX_NUM_FLASH_CHIPS 8   /* Maximum number of flash chips */
#define MAX_NUM_REGIONS     8   /* Maximum number of block regions per chip */
#define DEBUG 0

#define CFI_CMDSET_NONE             0
#define CFI_CMDSET_INTEL_EXTENDED   1
#define CFI_CMDSET_AMD_STANDARD     2
#define CFI_CMDSET_INTEL_STANDARD   3
#define CFI_CMDSET_AMD_EXTENDED     4
#define CFI_CMDSET_MITSU_STANDARD   256
#define CFI_CMDSET_MITSU_EXTENDED   257
#define CFI_CMDSET_SST              258

typedef struct
{
    bdk_node_t          node;
    uint64_t            base_addr;      /**< Physical address to start of flash */
    int                 bus_16bit;      /**< Bootbus is 16bits wide */
    int                 chip_16bit;     /**< Chip supports 16 bit operation */
    uint16_t            vendor;         /**< Vendor ID of Chip */
    int                 size;           /**< Size of the chip in bytes */
    uint64_t            erase_timeout;  /**< Erase timeout in cycles */
    uint64_t            write_timeout;  /**< Write timeout in cycles */
    int                 num_regions;    /**< Number of block regions */
    bdk_pbus_flash_region_t region[MAX_NUM_REGIONS];
} bdk_pbus_flash_t;

static bdk_pbus_flash_t flash_info[MAX_NUM_FLASH_CHIPS];
static bdk_spinlock_t flash_lock;


/**
 * @INTERNAL
 * Read a byte from flash
 *
 * @param flash  Flash to access
 * @param offset Offset into the chip
 *
 * @return Value read
 */
static uint8_t __bdk_pbus_flash_read8(const bdk_pbus_flash_t *flash, int offset)
{
    uint64_t address = flash->base_addr + offset;
    uint8_t data = bdk_read64_uint8(address);
#if DEBUG
    printf("bdk-pbus-flash: read8[0x%08lx] 0x%02x\n", address, data);
#endif
    return data;
}

/**
 * @INTERNAL
 * Read 16 bits from flash
 *
 * @param flash  Flash to access
 * @param offset Offset into the chip
 * @return Value read
 */
static uint16_t __bdk_pbus_flash_read16(const bdk_pbus_flash_t *flash, int offset)
{
    uint64_t address = flash->base_addr + offset;
    uint16_t data = bdk_read64_uint16(address);
#if DEBUG
    printf("bdk-pbus-flash: read16[0x%08lx] 0x%04x\n", address, data);
#endif
    return data;
}


/**
 * @INTERNAL
 * Write a byte to flash
 *
 * @param flash  Flash to access
 * @param offset Offset into the chip
 * @param data   Value to write
 */
static void __bdk_pbus_flash_write8(const bdk_pbus_flash_t *flash, int offset, uint8_t data)
{
    uint64_t address = flash->base_addr + offset;
#if DEBUG
    printf("bdk-pbus-flash: write8[0x%08lx] 0x%02x\n", address, data);
#endif
    bdk_write64_uint8(address, data);
}


/**
 * @INTERNAL
 * Write 16 bits to flash
 *
 * @param flash  Flash to access
 * @param offset Offset into the chip
 * @param data   Value to write
 */
static void __bdk_pbus_flash_write16(const bdk_pbus_flash_t *flash, int offset, uint16_t data)
{
    uint64_t address = flash->base_addr + offset;
#if DEBUG
    printf("bdk-pbus-flash: write16[0x%08lx] 0x%04x\n", address, data);
#endif
    bdk_write64_uint16(address, data);
}


/**
 * @INTERNAL
 * Read a byte from flash (for commands)
 *
 * @param chip_id Chip to read from
 * @param offset  Offset into the chip
 * @return Value read
 */
static uint8_t __bdk_pbus_flash_read_cmd(const bdk_pbus_flash_t *flash, int offset)
{
    if (flash->chip_16bit)
        offset<<=1;
    if (flash->bus_16bit)
        return __bdk_pbus_flash_read16(flash, offset) & 0xff;
    else
        return __bdk_pbus_flash_read8(flash, offset);
}


/**
 * @INTERNAL
 * Read 16bits from flash (for commands)
 *
 * @param chip_id Chip to read from
 * @param offset  Offset into the chip
 * @return Value read
 */
static uint16_t __bdk_pbus_flash_read_cmd16(const bdk_pbus_flash_t *flash, int offset)
{
    uint16_t v;
    if ((offset&1) == 0)
    {
        if (flash->chip_16bit)
            offset<<=1;
        v = __bdk_pbus_flash_read16(flash, offset);
    }
    else
    {
        v = __bdk_pbus_flash_read_cmd(flash, offset);
        v |= __bdk_pbus_flash_read_cmd(flash, offset + 1)<<8;
    }
    return v;
}


/**
 * @INTERNAL
 * Write a byte to flash (for commands)
 *
 * @param chip_id Chip to write to
 * @param offset  Offset into the chip
 * @param data    Value to write
 */
static void __bdk_pbus_flash_write_cmd(const bdk_pbus_flash_t *flash, int offset, uint8_t data)
{
    if (flash->chip_16bit)
        offset<<=1;
    if (flash->bus_16bit)
    {
        uint16_t d = data;
        d |= (uint16_t)data<<8;
        __bdk_pbus_flash_write16(flash, offset, d);
    }
    else
        __bdk_pbus_flash_write8(flash, offset, data);
}


/**
 * @INTERNAL
 * Query a address and see if a CFI flash chip is there.
 *
 * @param chip_id  Chip ID data to fill in if the chip is there
 * @param base_addr Physical address to the start address to query
 * @return Zero on success, Negative on failure
 */
static int __bdk_pbus_flash_queury_cfi(bdk_node_t node, int chip_id, uint64_t base_addr)
{
    int region;
    bdk_pbus_flash_t *flash = flash_info + chip_id;
    BDK_CSR_INIT(pbus_regx_cfg, node, BDK_PBUS_REGX_CFG(chip_id));

    /* Set the minimum needed for the read and write primitives to work */
    flash->node = node;
    flash->base_addr = base_addr;
    flash->bus_16bit = pbus_regx_cfg.s.d_width;
    flash->chip_16bit = 1;   /* FIXME: Currently assumes the chip is 16bits */

    /* Read a single byte from flash to put the flash in normal mode */
    __bdk_pbus_flash_read8(flash, 0);

    /* Put flash in CFI query mode */
    __bdk_pbus_flash_write_cmd(flash, 0x00, 0xf0); /* Reset the flash chip - AMD */
    __bdk_pbus_flash_write_cmd(flash, 0x00, 0xff); /* Reset the flash chip - Intel */
    __bdk_pbus_flash_write_cmd(flash, 0x55, 0x98);

    /* Make sure we get the QRY response we should */
    if ((__bdk_pbus_flash_read_cmd(flash, 0x10) != 'Q') ||
        (__bdk_pbus_flash_read_cmd(flash, 0x11) != 'R') ||
        (__bdk_pbus_flash_read_cmd(flash, 0x12) != 'Y'))
    {
        flash->base_addr = 0;
        printf("NOR Flash %d:CFI Query failed\n", chip_id);
        return -1;
    }

    /* Read the 16bit vendor ID */
    flash->vendor = __bdk_pbus_flash_read_cmd16(flash, 0x13);

    /* Read the location of the Primary Algorithm extended Query table */
    int p = __bdk_pbus_flash_read_cmd16(flash, 0x15);

    /* Read the write timeout. The timeout is microseconds(us) is 2^0x1f
        typically. The worst case is this value time 2^0x23 */
    flash->write_timeout = 1ull << (__bdk_pbus_flash_read_cmd(flash, 0x1f) +
                                    __bdk_pbus_flash_read_cmd(flash, 0x23));

    /* Read the erase timeout. The timeout is milliseconds(ms) is 2^0x21
        typically. The worst case is this value time 2^0x25 */
    flash->erase_timeout = 1ull << (__bdk_pbus_flash_read_cmd(flash, 0x21) +
                                    __bdk_pbus_flash_read_cmd(flash, 0x25));

    /* Get the flash size. This is 2^0x27 */
    flash->size = 1<<__bdk_pbus_flash_read_cmd(flash, 0x27);

    /* Get the number of different sized block regions from 0x2c */
    flash->num_regions = __bdk_pbus_flash_read_cmd(flash, 0x2c);

    /* Read the top/bottom flag to determine if the regions are reversed */
    int order_reversed = __bdk_pbus_flash_read_cmd(flash, p + 0xf);
    order_reversed &= 1;

    int start_offset = (order_reversed) ? flash->size : 0;
    /* Loop through all regions get information about each */
    for (region=0; region<flash->num_regions; region++)
    {
        bdk_pbus_flash_region_t *rgn_ptr = flash->region + region;
        if (order_reversed)
            rgn_ptr = flash->region + flash->num_regions - region - 1;

        /* The number of blocks in each region is a 16 bit little endian
            endian field. It is encoded at 0x2d + region*4 as (blocks-1) */
        uint16_t blocks = __bdk_pbus_flash_read_cmd16(flash, 0x2d + region*4);
        rgn_ptr->num_blocks =  1u + blocks;

        /* The size of each block is a 16 bit little endian endian field. It
            is encoded at 0x2d + region*4 + 2 as (size/256). Zero is a special
            case representing 128 */
        uint16_t size = __bdk_pbus_flash_read_cmd16(flash, 0x2f + region*4);
        if (size == 0)
            rgn_ptr->block_size = 128;
        else
            rgn_ptr->block_size = 256u * size;

        if (order_reversed)
        {
            start_offset -= rgn_ptr->block_size * rgn_ptr->num_blocks;
            rgn_ptr->start_offset = start_offset;
        }
        else
        {
            rgn_ptr->start_offset = start_offset;
            start_offset += rgn_ptr->block_size * rgn_ptr->num_blocks;
        }
    }

    /* Take the chip out of CFI query mode */
    switch (flash->vendor)
    {
        case CFI_CMDSET_AMD_STANDARD:
            __bdk_pbus_flash_write_cmd(flash, 0x00, 0xf0);
            break;
        case CFI_CMDSET_INTEL_STANDARD:
        case CFI_CMDSET_INTEL_EXTENDED:
            __bdk_pbus_flash_write_cmd(flash, 0x00, 0xff);
            break;
    }

    /* Convert the timeouts to cycles */
    flash->write_timeout *= bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000000;
    flash->erase_timeout *= bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME) / 1000;

    /* Print the information about the chip */
    printf(
           "NOR Flash %d:Base address:  0x%lx\n"
           "            Vendor:        0x%04x\n"
           "            16 bit:        %s\n"
           "            Size:          %d bytes\n"
           "            Num regions:   %d\n"
           "            Erase timeout: %llu cycles\n"
           "            Write timeout: %llu cycles\n",
           chip_id,
           flash->base_addr,
           (unsigned int)flash->vendor,
           (flash->chip_16bit) ? "yes" : "no",
           flash->size,
           flash->num_regions,
           (unsigned long long)flash->erase_timeout,
           (unsigned long long)flash->write_timeout);

    for (region=0; region<flash->num_regions; region++)
    {
        printf("            Region %d: offset 0x%x, %d blocks, %d bytes/block\n",
               region,
               flash->region[region].start_offset,
               flash->region[region].num_blocks,
               flash->region[region].block_size);
    }

    return 0;
}


/**
 * Initialize the flash access library
 */
void bdk_pbus_flash_initialize(bdk_node_t node)
{
    int boot_region;
    int num_flash = 0;

    memset(flash_info, 0, sizeof(flash_info));

    /* Loop through each boot bus chip select region */
    for (boot_region=0; boot_region<MAX_NUM_FLASH_CHIPS; boot_region++)
    {
        bdk_pbus_regx_cfg_t region_cfg;
        region_cfg.u = BDK_CSR_READ(node, BDK_PBUS_REGX_CFG(boot_region));
        /* Only try chip select regions that are enabled */
        if (region_cfg.s.en)
        {
            uint64_t base_addr = (1ull<<47) + ((uint64_t)region_cfg.s.base<<16);
            if (__bdk_pbus_flash_queury_cfi(node, boot_region, base_addr) == 0)
            {
                /* Valid CFI flash chip found */
                num_flash++;
            }
        }
    }

    if (num_flash == 0)
        bdk_warn("bdk-pbus-flash: No CFI NOR flash found\n");
}


/**
 * Return a pointer to the flash chip
 *
 * @param chip_id Chip ID to return
 * @return Zero if the chip doesn't exist
 */
uint64_t bdk_pbus_flash_get_base(int chip_id)
{
    return flash_info[chip_id].base_addr;
}


/**
 * Return the number of erasable regions on the chip
 *
 * @param chip_id Chip to return info for
 * @return Number of regions
 */
int bdk_pbus_flash_get_num_regions(int chip_id)
{
    return flash_info[chip_id].num_regions;
}


/**
 * Return information about a flash chips region
 *
 * @param chip_id Chip to get info for
 * @param region  Region to get info for
 * @return Region information
 */
const bdk_pbus_flash_region_t *bdk_pbus_flash_get_region_info(int chip_id, int region)
{
    return flash_info[chip_id].region + region;
}


/**
 * Erase a block on the flash chip
 *
 * @param chip_id Chip to erase a block on
 * @param region  Region to erase a block in
 * @param block   Block number to erase
 * @return Zero on success. Negative on failure
 */
int bdk_pbus_flash_erase_block(int chip_id, int region, int block)
{
    const bdk_pbus_flash_t *flash = flash_info + chip_id;
    bdk_spinlock_lock(&flash_lock);
#if DEBUG
    printf("bdk-pbus-flash: Erasing chip %d, region %d, block %d\n",
           chip_id, region, block);
#endif

    int offset = flash->region[region].start_offset +
                block * flash->region[region].block_size;

    switch (flash->vendor)
    {
        case CFI_CMDSET_AMD_STANDARD:
        {
            /* Send the erase sector command sequence */
            __bdk_pbus_flash_write_cmd(flash, 0x00, 0xf0); /* Reset the flash chip */
            __bdk_pbus_flash_write_cmd(flash, 0x555, 0xaa); /* Unlock start */
            __bdk_pbus_flash_write_cmd(flash, 0x2aa, 0x55); /* Unlock ack */
            __bdk_pbus_flash_write_cmd(flash, 0x555, 0x80); /* Erase start */
            __bdk_pbus_flash_write_cmd(flash, 0x555, 0xaa); /* Unlock start */
            __bdk_pbus_flash_write_cmd(flash, 0x2aa, 0x55); /* Unlock ack */
            if (flash->bus_16bit)
                __bdk_pbus_flash_write16(flash, offset, 0x3030); /* Erase sector */
            else
                __bdk_pbus_flash_write8(flash, offset, 0x30); /* Erase sector */

            /* Loop checking status */
            uint8_t status = __bdk_pbus_flash_read8(flash, offset);
            uint64_t end_cycle = bdk_clock_get_count(BDK_CLOCK_TIME) + bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
            while (status != 0xff)
            {
                if (bdk_clock_get_count(BDK_CLOCK_TIME) > end_cycle)
                {
                    bdk_error("bdk-pbus-flash: Timeout erasing block\n");
                    bdk_spinlock_unlock(&flash_lock);
                    return -1;
                }
                bdk_thread_yield();
                status = __bdk_pbus_flash_read8(flash, offset);
            }

            __bdk_pbus_flash_write_cmd(flash, 0x00, 0xf0); /* Reset the flash chip */
            bdk_spinlock_unlock(&flash_lock);
            return 0;
        }
        case CFI_CMDSET_INTEL_STANDARD:
        case CFI_CMDSET_INTEL_EXTENDED:
        {
            /* Send the erase sector command sequence */
            __bdk_pbus_flash_write_cmd(flash, 0x00, 0xff); /* Reset the flash chip */
            __bdk_pbus_flash_write8(flash, offset, 0x20);
            __bdk_pbus_flash_write8(flash, offset, 0xd0);

            /* Loop checking status */
            uint8_t status = __bdk_pbus_flash_read8(flash, offset);
            uint64_t start_cycle = bdk_clock_get_count(BDK_CLOCK_TIME);
            while ((status & 0x80) == 0)
            {
                if (bdk_clock_get_count(BDK_CLOCK_TIME) > start_cycle + flash->erase_timeout)
                {
                    bdk_error("bdk-pbus-flash: Timeout erasing block\n");
                    bdk_spinlock_unlock(&flash_lock);
                    return -1;
                }
                bdk_thread_yield();
                status = __bdk_pbus_flash_read8(flash, offset);
            }

            /* Check the final status */
            if (status & 0x7f)
            {
                bdk_error("bdk-pbus-flash: Hardware failure erasing block\n");
                bdk_spinlock_unlock(&flash_lock);
                return -1;
            }

            __bdk_pbus_flash_write_cmd(flash, 0x00, 0xff); /* Reset the flash chip */
            bdk_spinlock_unlock(&flash_lock);
            return 0;
        }
    }

    bdk_error("bdk-pbus-flash: Unsupported flash vendor\n");
    bdk_spinlock_unlock(&flash_lock);
    return -1;
}

/**
 * Write data to flash. The block must have already been erased. You can call
 * this multiple times on the same block to piecemeal write it.
 *
 * @param chip_id Which flash to write
 * @param offset  Offset into device to start write
 * @param data    Data to write
 * @param len     Length of the data
 *
 * @return Zero on success. Negative on failure
 */
int bdk_pbus_flash_write(int chip_id, int offset, const void *data, int len)
{
    const bdk_pbus_flash_t *flash = flash_info + chip_id;
    bdk_spinlock_lock(&flash_lock);
#if DEBUG
    printf("bdk-pbus-flash: Writing chip %d, offset %d, len %d\n",
           chip_id, offset, len);
#endif
    const uint8_t *ptr = (const uint8_t *)data;

    switch (flash->vendor)
    {
        case CFI_CMDSET_AMD_STANDARD:
        {
            /* Loop through one byte at a time */
            while (len>0)
            {
                uint16_t data;
                /* Send the program sequence */
                __bdk_pbus_flash_write_cmd(flash, 0x00, 0xf0); /* Reset the flash chip */
                __bdk_pbus_flash_write_cmd(flash, 0x555, 0xaa); /* Unlock start */
                __bdk_pbus_flash_write_cmd(flash, 0x2aa, 0x55); /* Unlock ack */
                __bdk_pbus_flash_write_cmd(flash, 0x555, 0xa0); /* Write */
                if (flash->bus_16bit)
                {
                    data = *(uint16_t*)ptr;
                    __bdk_pbus_flash_write16(flash, offset, *(uint16_t*)ptr);
                }
                else
                {
                    data = *ptr;
                    __bdk_pbus_flash_write8(flash, offset, *ptr);
                }
                /* Loop polling for status */
                uint64_t end_cycle = bdk_clock_get_count(BDK_CLOCK_TIME) + bdk_clock_get_rate(bdk_numa_local(), BDK_CLOCK_TIME);
                uint16_t status = ~data;
                while (status != data)
                {
                    if (bdk_clock_get_count(BDK_CLOCK_TIME) > end_cycle)
                    {
                        bdk_error("bdk-pbus-flash: Timeout writing block\n");
                        bdk_spinlock_unlock(&flash_lock);
                        return -1;
                    }
                    bdk_thread_yield();
                    if (flash->bus_16bit)
                        status = __bdk_pbus_flash_read16(flash, offset);
                    else
                        status = __bdk_pbus_flash_read8(flash, offset);
                }

                /* Increment to the next byte */
                if (flash->bus_16bit)
                {
                    ptr+=2;
                    offset+=2;
                    len-=2;
                }
                else
                {
                    ptr++;
                    offset++;
                    len--;
                }
            }

            __bdk_pbus_flash_write_cmd(flash, 0x00, 0xf0); /* Reset the flash chip */
            bdk_spinlock_unlock(&flash_lock);
            return 0;
        }
        case CFI_CMDSET_INTEL_STANDARD:
        case CFI_CMDSET_INTEL_EXTENDED:
        {
            /* Loop through one byte at a time */
            while (len--)
            {
                /* Send the program sequence */
                __bdk_pbus_flash_write_cmd(flash, 0x00, 0xff); /* Reset the flash chip */
                __bdk_pbus_flash_write8(flash, offset, 0x40);
                __bdk_pbus_flash_write8(flash, offset, *ptr);

                /* Loop polling for status */
                uint8_t status = __bdk_pbus_flash_read8(flash, offset);
                uint64_t start_cycle = bdk_clock_get_count(BDK_CLOCK_TIME);
                while ((status & 0x80) == 0)
                {
                    if (bdk_clock_get_count(BDK_CLOCK_TIME) > start_cycle + flash->write_timeout)
                    {
                        bdk_error("bdk-pbus-flash: Timeout writing block\n");
                        bdk_spinlock_unlock(&flash_lock);
                        return -1;
                    }
                    bdk_thread_yield();
                    status = __bdk_pbus_flash_read8(flash, offset);
                }

                /* Check the final status */
                if (status & 0x7f)
                {
                    bdk_error("bdk-pbus-flash: Hardware failure erasing block\n");
                    bdk_spinlock_unlock(&flash_lock);
                    return -1;
                }

                /* Increment to the next byte */
                ptr++;
                offset++;
            }

            __bdk_pbus_flash_write_cmd(flash, 0x00, 0xff); /* Reset the flash chip */
            bdk_spinlock_unlock(&flash_lock);
            return 0;
        }
    }

    bdk_error("bdk-pbus-flash: Unsupported flash vendor\n");
    bdk_spinlock_unlock(&flash_lock);
    return -1;
}

