/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
#include <bdk.h>
#include "bdk-sfp.h"

BDK_REQUIRE_DEFINE(DRIVER_NETPORT_SFP28);

#define MAX_ROM_SIZE 256

typedef struct
{
    char rom[2][MAX_ROM_SIZE]; /* Contents of the SFP EEPROM. See comments on rom_info_t for format */
    bool module_present;    /* True if there was a module the last time we checked */
    bool allow_link;        /* True if networking is allowing a link */
    bool force_unplug;      /* Override for module presence detect */
    int asim_rom;           /* Index of which ROM to use with Asim */
    bdk_device_t *twsi;     /* TWSI device connected to this SFP */
    bdk_device_t *tx_fault; /* GPIO device for TX_FAULT */
    bdk_device_t *tx_dis;   /* GPIO device for TX_DIS */
    bdk_device_t *mod_pres; /* GPIO device for PRES */
    bdk_device_t *rs0;      /* GPIO device for RS0 */
    bdk_device_t *rs1;      /* GPIO device for RS1 */
    bdk_device_t *rx_los;   /* GPIO device for RX_LOS */
    int tx_fault_pin;       /* GPIO pin for TX_FAULT (input) */
    int tx_dis_pin;         /* GPIO pin for TX_DIS (output) */
    int mod_pres_pin;       /* GPIO pin for PRES (input) */
    int rs0_pin;            /* GPIO pin for RS0 (output) */
    int rs1_pin;            /* GPIO pin for RS1 (output) */
    int rx_los_pin;         /* GPIO pin for RX_LOS (input) */
} sfp_state_t;

typedef struct
{
    const char *name;       /* Friendly name for SFP module */
    /* ROM data read from EEPROM. The first index is 256 bytes from address
       0x50 page 0. The second index is 128 bytes from address 0x51,
       followed by 128 bytes from page 1 */
    const char rom[2][MAX_ROM_SIZE];
} rom_info_t;

static rom_info_t ROM_TABLE[] = {
    {
        .name = "dac-25g-3meter",
        .rom = {
            {   /* 0x50 page 0 */
                0x03, 0x04, 0x23, 0x01, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x06, 0xff, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x03, 0x00, 0x41, 0x6d, 0x70, 0x68, 0x65, 0x6e, 0x6f, 0x6c, 0x20, 0x20, 0x20, 0x20,
                0x20, 0x20, 0x20, 0x20, 0x0b, 0x78, 0xa7, 0x14, 0x4e, 0x44, 0x43, 0x43, 0x47, 0x46, 0x2d, 0x43,
                0x31, 0x30, 0x33, 0x20, 0x20, 0x20, 0x20, 0x20, 0x41, 0x20, 0x20, 0x20, 0x03, 0x00, 0x00, 0x16,
                0x00, 0x00, 0x67, 0x00, 0x41, 0x50, 0x46, 0x31, 0x37, 0x31, 0x32, 0x31, 0x30, 0x33, 0x34, 0x32,
                0x41, 0x37, 0x20, 0x20, 0x31, 0x37, 0x30, 0x33, 0x32, 0x32, 0x20, 0x20, 0x00, 0x00, 0x08, 0x32,
            },
            {   /* 0x51 page 0, then page 1 */
                0,
            },
        }
    },
    {
        .name = "dac-25g-1meter",
        .rom = {
        {   /* 0x50 page 0 */
                0x03, 0x04, 0x23, 0x01, 0x00, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x06, 0xff, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x01, 0x00, 0x41, 0x6d, 0x70, 0x68, 0x65, 0x6e, 0x6f, 0x6c, 0x20, 0x20, 0x20, 0x20,
                0x20, 0x20, 0x20, 0x20, 0x0d, 0x78, 0xa7, 0x14, 0x4e, 0x44, 0x43, 0x43, 0x47, 0x46, 0x2d, 0x30,
                0x30, 0x30, 0x36, 0x20, 0x20, 0x20, 0x20, 0x20, 0x41, 0x20, 0x20, 0x20, 0x03, 0x00, 0x00, 0x05,
                0x00, 0x00, 0x67, 0x00, 0x41, 0x50, 0x46, 0x31, 0x37, 0x31, 0x39, 0x30, 0x30, 0x36, 0x30, 0x4a,
                0x4e, 0x36, 0x20, 0x20, 0x31, 0x37, 0x30, 0x35, 0x31, 0x34, 0x20, 0x20, 0x00, 0x00, 0x00, 0x56,
            },
            {   /* 0x51 page 0, then page 1 */
                0,
            },
        }
    },
    {
        .name = "optical-25g-1meter",
        .rom = {
        {   /* 0x50 page 0 */
                0x03, 0x04, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x01, 0x00, 0x46, 0x49, 0x4e, 0x49, 0x53, 0x41, 0x52, 0x20, 0x43, 0x4f, 0x52, 0x50,
                0x20, 0x20, 0x20, 0x20, 0x01, 0x00, 0x90, 0x65, 0x46, 0x43, 0x43, 0x47, 0x31, 0x32, 0x35, 0x53,
                0x44, 0x31, 0x43, 0x30, 0x31, 0x20, 0x20, 0x20, 0x41, 0x30, 0x30, 0x20, 0x04, 0x00, 0x00, 0x3f,
                0x00, 0x1a, 0x00, 0x00, 0x57, 0x58, 0x43, 0x30, 0x51, 0x47, 0x48, 0x20, 0x20, 0x20, 0x20, 0x20,
                0x20, 0x20, 0x20, 0x20, 0x31, 0x37, 0x30, 0x34, 0x30, 0x37, 0x20, 0x20, 0x68, 0x00, 0x08, 0x1f,
            },
            {   /* 0x51 page 0, then page 1 */
                0,
            },
        }
    },
};

/**
 * Add a new device based on a bdk-config device string
 *
 * @param device     Device being added
 * @param config_str String from DEVICE in the bdk-config device tree
 */
static void add(bdk_device_t *device, const char *config_str)
{
    sfp_state_t *sfp_state = calloc(1, sizeof(sfp_state_t));

    sfp_state->twsi = bdk_driver_extract_device(config_str, "twsi");
    sfp_state->tx_fault = bdk_driver_extract_device_arg(config_str, "tx_fault", &sfp_state->tx_fault_pin);
    sfp_state->tx_dis = bdk_driver_extract_device_arg(config_str, "tx_dis", &sfp_state->tx_dis_pin);
    sfp_state->mod_pres = bdk_driver_extract_device_arg(config_str, "pres", &sfp_state->mod_pres_pin);
    sfp_state->rs0 = bdk_driver_extract_device_arg(config_str, "rs0", &sfp_state->rs0_pin);
    sfp_state->rs1 = bdk_driver_extract_device_arg(config_str, "rs1", &sfp_state->rs1_pin);
    sfp_state->rx_los = bdk_driver_extract_device_arg(config_str, "rx_los", &sfp_state->rx_los_pin);

    device->priv.state = (uint64_t)sfp_state;

    BDK_TRACE(DEVICE, "%s: SFP connected to TWSI=%s,\n"
                   "    TX_FAULT=%s(%d), TX_DIS=%s(%d), MOD_PRES=%s(%d),\n"
                   "    RS0=%s(%d), RS1=%s(%d), RX_LOS=%s(%d)\n",
        device->name, sfp_state->twsi->name,
        sfp_state->tx_fault->name, sfp_state->tx_fault_pin,
        sfp_state->tx_dis->name, sfp_state->tx_dis_pin,
        sfp_state->mod_pres->name, sfp_state->mod_pres_pin,
        sfp_state->rs0->name, sfp_state->rs0_pin,
        sfp_state->rs1->name, sfp_state->rs1_pin,
        sfp_state->rx_los->name, sfp_state->rx_los_pin);
}

/**
 * Initialize the device, nothing needed
 *
 * @param device to initialize
 *
 * @return Zero on success, negative on failure
 */
static int init(bdk_device_t *device)
{
    return 0;
}

/**
 * Internal function for reading the state of SFP GPIOs
 *
 * @param device    GPIO device
 * @param gpio      GPIO pin number
 * @param def_value Value to return if the GPIO device is NULL
 *
 * @return State of the GPIO
 */
static int gpio_read(bdk_device_t *device, int gpio, int def_value)
{
    if (!device)
        return def_value;

    int group = gpio / 64;
    int pin = gpio & 63;

    uint64_t gpios = bdk_device_gpio_readstate(device, group);
    return (gpios >> pin) & 1;
}

/**
 * Internal function for controlling SFP output GPIOs. Does
 * nothing if the GPIO device is NULL
 *
 * @param device GPIO device
 * @param gpio   Pin to change
 * @param value  Value to set
 */
static void gpio_write(bdk_device_t *device, int gpio, int value)
{
    if (!device)
        return;

    int group = gpio / 64;
    int pin = gpio & 63;

    if (value)
        bdk_device_gpio_set1(device, group, 1ull << pin);
    else
        bdk_device_gpio_set0(device, group, 1ull << pin);
}

/**
 * Read the SFP ROM information over TWSI
 *
 * @param sfp_state SFP port state to update
 */
static void rom_read(bdk_device_t *device, sfp_state_t *sfp_state)
{
    uint8_t csum;

    if (bdk_is_platform(BDK_PLATFORM_ASIM))
    {
        memcpy(sfp_state->rom, ROM_TABLE[sfp_state->asim_rom].rom, sizeof(sfp_state->rom));
        goto skip;
    }

    const int twsi_addr = 0x50; /* From SFP spec */
    const int twsi_ia_width = 1; /* One address byte for EEPROM */

    /* Loop through EEPROM page 0 at 0x50, then page0-1 at 0x51 */
    for (int r = 0; r < 2; r++)
    {
        for (int addr = 0; addr < MAX_ROM_SIZE; addr += 4)
        {
            int64_t data = bdk_device_twsi_read_ia(sfp_state->twsi, twsi_addr + r, addr, 4, twsi_ia_width);
            if (data < 0)
                goto skip;
            sfp_state->rom[r][addr + 0] = bdk_extract(data, 24, 8);
            sfp_state->rom[r][addr + 1] = bdk_extract(data, 16, 8);
            sfp_state->rom[r][addr + 2] = bdk_extract(data, 8, 8);
            sfp_state->rom[r][addr + 3] = bdk_extract(data, 0, 8);
        }
    }
skip:
    /* Check base checksum */
    csum = 0;
    for (int i = 0; i < 63; i++)
        csum += sfp_state->rom[0][i];
    if (csum != sfp_state->rom[0][63])
        bdk_error("%s: SFP base checksum incorrect\n", device->name);
    else
        BDK_TRACE(BGX, "%s: SFP base checksum correct\n", device->name);

    /* Check extended checksum */
    csum = 0;
    for (int i = 64; i < 95; i++)
        csum += sfp_state->rom[0][i];
    if (csum != sfp_state->rom[0][95])
        bdk_error("%s: SFP extended checksum incorrect\n", device->name);
    else
        BDK_TRACE(BGX, "%s: SFP extended checksum correct\n", device->name);
}

/**
 * Process the ROM and set SFP state accordingly
 *
 * @param device  SFP device
 * @param state   State returned to network driver
 * @param verbose Show information and errors
 */
static void rom_parse(bdk_device_t *device, bdk_device_netport_state_t *state, bool verbose)
{
    sfp_state_t *sfp_state = (sfp_state_t *)device->priv.state;
    const bdk_spd_rom_t *rom = (bdk_spd_rom_t *)sfp_state->rom[0];

    /* Byte 0: Identifier, should be 0x03 for SFP/SFP+/SFP28 */
    if (rom->base.id != 0x03)
    {
        if (verbose)
            BDK_TRACE(BGX, "%s: SFP/SFP+ not detected (id=0x%x)\n", device->name, rom->base.id);
        state->flags |= BDK_DEVICE_NETPORT_FLAG_MISSING;
        state->max_speed = 0;
        return;
    }
    /* Byte 1: Extended Identifier, should be 0x04 */
    if (rom->base.ext_id != 0x04)
    {
        if (verbose)
            BDK_TRACE(BGX, "%s: SFP/SFP+ incorrect extended identifier 0x%x\n", device->name, rom->base.ext_id);
        state->flags |= BDK_DEVICE_NETPORT_FLAG_MISSING;
        state->max_speed = 0;
        return;
    }

    state->max_speed = 100 * rom->base.bitrate;

    if (verbose)
    {
        printf("%s:\n"
            "    Vendor: %16.16s OUI:  %02x:%02x:%02x\n"
            "    Part:   %16.16s Rev:  %4.4s\n"
            "    Serial: %16.16s Date: 20%2.2s-%2.2s-%2.2s Lot: %2.2s\n",
            device->name, rom->base.vendor_name, rom->base.vendor_oui[0],
            rom->base.vendor_oui[1], rom->base.vendor_oui[2], rom->base.vendor_pn,
            rom->base.vendor_rev, rom->ext.vendir_sn, rom->ext.date_code,
            rom->ext.date_code + 2, rom->ext.date_code + 4, rom->ext.date_code + 6);
        if (rom->base.bitrate)
            printf("    Nominal signalling rate: %d MBd\n", state->max_speed);
        if (rom->base.smf_1000m)
            printf("    SMF Length: %dm\n", 1000 * rom->base.smf_1000m);
        if (rom->base.smf_100m)
            printf("    SMF Length: %dm\n", 100 * rom->base.smf_100m);
        if (rom->base.om1_10m)
            printf("    OM1 Length: %dm\n", 10 * rom->base.om1_10m);
        if (rom->base.om2_10m)
            printf("    OM2 Length: %dm\n", 10 * rom->base.om2_10m);
        if (rom->base.om3_10m)
            printf("    OM3 Length: %dm\n", 10 * rom->base.om3_10m);
        if (rom->base.dac_1m)
            printf("    DAC Length: %dm\n", rom->base.dac_1m);
        const char *TRANSCEIVER_CODES[] = {
            /* 10G Ethernet Compliance Codes */
            "10G Base-ER", /* Byte 3 Bit 7 */
            "10G Base-LRM", /* Byte 3 Bit 6 */
            "10G Base-LR", /* Byte 3 Bit 5 */
            "10G Base-SR", /* Byte 3 Bit 4 */
            /* Infiniband Compliance Codes */
            "1X SX", /* Byte 3 Bit 3 */
            "1X LX", /* Byte 3 Bit 2 */
            "1X Copper Active", /* Byte 3 Bit 1 */
            "1X Copper Passive", /* Byte 3 Bit 0 */
            /* ESCON Compliance Codes */
            "ESCON MMF, 1310nm LED", /* Byte 4 Bit 7 */
            "ESCON SMF, 1310nm Laser", /* Byte 4 Bit 6 */
            /* SONET Compliance Codes */
            "OC-192, short reach2", /* Byte 4 Bit 5 */
            "SONET reach specifier bit 1", /* Byte 4 Bit 4 */
            "SONET reach specifier bit 2", /* Byte 4 Bit 3 */
            "OC-48, long reach", /* Byte 4 Bit 2 */
            "OC-48, intermediate reach", /* Byte 4 Bit 1 */
            "OC-48, short reach", /* Byte 4 Bit 0 */
            "Unallocated (byte 5, bit 7)", /* Byte 5 Bit 7 */
            "OC-12, single mode, long reach", /* Byte 5 Bit 6 */
            "OC-12, single mode, inter. reach", /* Byte 5 Bit 5 */
            "OC-12, short reach", /* Byte 5 Bit 4 */
            "Unallocated (byte 5, bit 3)", /* Byte 5 Bit 3 */
            "OC-3, single mode, long reach", /* Byte 5 Bit 2 */
            "OC-3, single mode, inter. reach", /* Byte 5 Bit 1 */
            "OC-3, short reach", /* Byte 5 Bit 0 */
            /* Ethernet Compliance Codes */
            "BASE-PX", /* Byte 6 Bit 7 */
            "BASE-BX10", /* Byte 6 Bit 6 */
            "100BASE-FX", /* Byte 6 Bit 5 */
            "100BASE-LX/LX10", /* Byte 6 Bit 4 */
            "1000BASE-T", /* Byte 6 Bit 3 */
            "1000BASE-CX", /* Byte 6 Bit 2 */
            "1000BASE-LX", /* Byte 6 Bit 1 */
            "1000BASE-SX", /* Byte 6 Bit 0 */
            /* Fibre Channel Link Length */
            "very long distance (V)", /* Byte 7 Bit 7 */
            "short distance (S)", /* Byte 7 Bit 6 */
            "intermediate distance (I)", /* Byte 7 Bit 5 */
            "long distance (L)", /* Byte 7 Bit 4 */
            "medium distance (M)", /* Byte 7 Bit 3 */
            /* Fibre Channel Technology */
            "Shortwave laser, linear Rx (SA)", /* Byte 7 Bit 2 */
            "Longwave laser (LC)", /* Byte 7 Bit 1 */
            "Electrical inter-enclosure (EL)", /* Byte 7 Bit 0 */
            "Electrical intra-enclosure (EL)", /* Byte 8 Bit 7 */
            "Shortwave laser w/o OFC (SN) 7", /* Byte 8 Bit 6 */
            "Shortwave laser with OFC4 (SL)", /* Byte 8 Bit 5 */
            "Longwave laser (LL)5", /* Byte 8 Bit 4 */
            /* SFP+ Cable Technology */
            "Active Cable", /* Byte 8 Bit 3 */
            "Passive Cable", /* Byte 8 Bit 2 */
            "Unallocated (byte 8, bit 1)", /* Byte 8 Bit 1 */
            "Unallocated (byte 8, bit 0)", /* Byte 8 Bit 0 */
            /* Fibre Channel Transmission Media */
            "Twin Axial Pair (TW)", /* Byte 9 Bit 7 */
            "Twisted Pair (TP)", /* Byte 9 Bit 6 */
            "Miniature Coax (MI)", /* Byte 9 Bit 5 */
            "Video Coax (TV)", /* Byte 9 Bit 4 */
            "Multimode, 62.5um (M6)", /* Byte 9 Bit 3 */
            "Multimode, 50um (M5, M5E)", /* Byte 9 Bit 2 */
            "Unallocated (byte 9, bit 1)", /* Byte 9 Bit 1 */
            "Single Mode (SM)", /* Byte 9 Bit 0 */
            /* Fibre Channel Speed */
            "1200 MBytes/sec", /* Byte 10 Bit 7 */
            "800 MBytes/sec", /* Byte 10 Bit 6 */
            "1600 MBytes/sec", /* Byte 10 Bit 5 */
            "400 MBytes/sec", /* Byte 10 Bit 4 */
            "Unallocated (byte 10, bit 3)", /* Byte 10 Bit 3 */
            "200 MBytes/sec", /* Byte 10 Bit 2 */
            "Unallocated (byte 10, bit 1)", /* Byte 10 Bit 1 */
            "100 MBytes/sec", /* Byte 10 Bit 0 */
        };
        for (int byte = 0; byte < (int)sizeof(rom->base.transceiver1); byte++)
        {
            for (int bit = 7; bit >= 0; bit--)
            {
                int flag = (rom->base.transceiver1[byte] >> bit) & 1;
                if (flag)
                    printf("    %s\n", TRANSCEIVER_CODES[byte * 8 + (7 - bit)]);
            }
        }
    }
}

/**
 * Network Port API function to initialize a port
 *
 * @param device Device to access
 */
static void netport_init(bdk_device_t *device)
{
    sfp_state_t *sfp_state = (sfp_state_t *)device->priv.state;

    BDK_TRACE(BGX, "%s: Initializing SFP GPIOs\n", device->name);

    /* Setup GPIOs for SFP. Start with port disabled */
    if (sfp_state->tx_fault)
        bdk_device_gpio_setup(sfp_state->tx_fault, sfp_state->tx_fault_pin, false, 0, true, false);
    if (sfp_state->tx_dis)
        bdk_device_gpio_setup(sfp_state->tx_dis, sfp_state->tx_dis_pin, true, 1, true, false);
    if (sfp_state->mod_pres)
        bdk_device_gpio_setup(sfp_state->mod_pres, sfp_state->mod_pres_pin, false, 0, true, false);
    if (sfp_state->rs0)
        bdk_device_gpio_setup(sfp_state->rs0, sfp_state->rs0_pin, true, 1, true, false);
    if (sfp_state->rs1)
        bdk_device_gpio_setup(sfp_state->rs1, sfp_state->rs1_pin, true, 1, true, false);
    if (sfp_state->rx_los)
        bdk_device_gpio_setup(sfp_state->rx_los, sfp_state->rx_los_pin, false, 0, true, false);
}

/**
 * Network Port API function to set the state of a port
 *
 * @param device     Device to access
 * @param mode       QLM mode of the network port connected to the network port
 * @param baud_mhz   QLM rate in MHz
 * @param allow_link True if a link is allowed on the port
 * @param link_up    True if the current link is up, ready to move data
 */
static void netport_set(bdk_device_t *device, bdk_qlm_modes_t mode, int baud_mhz, bool allow_link, bool link_up)
{
    sfp_state_t *sfp_state = (sfp_state_t *)device->priv.state;
    if (!allow_link && sfp_state->allow_link)
    {
        BDK_TRACE(BGX, "%s: Setting TX disabled\n", device->name);
        gpio_write(sfp_state->tx_dis, sfp_state->tx_dis_pin, 1);
    }
    sfp_state->allow_link = allow_link;
}

/**
 * Network Port API function to get the state of a network port
 *
 * @param device Device to access
 * @param state
 */
static void netport_get(bdk_device_t *device, bdk_device_netport_state_t *state)
{
    sfp_state_t *sfp_state = (sfp_state_t *)device->priv.state;

    state->max_speed = 100000;
    state->flags = 0;

    if (sfp_state->force_unplug || gpio_read(sfp_state->mod_pres, sfp_state->mod_pres_pin, 1))
    {
        BDK_TRACE(BGX, "%s: Module is missing\n", device->name);
        state->flags |= BDK_DEVICE_NETPORT_FLAG_MISSING;
    }
    else
    {
        if (gpio_read(sfp_state->rx_los, sfp_state->rx_los_pin, 1))
        {
            BDK_TRACE(BGX, "%s: RX loss of signal\n", device->name);
            state->flags |= BDK_DEVICE_NETPORT_FLAG_RX_ERROR;
        }

        if (gpio_read(sfp_state->tx_fault, sfp_state->tx_fault_pin, 1))
        {
            bdk_error("%s: TX fault, disabling output\n", device->name);
            gpio_write(sfp_state->tx_dis, sfp_state->tx_dis_pin, 1);
        }
    }

    if ((state->flags & BDK_DEVICE_NETPORT_FLAG_MISSING) && sfp_state->module_present)
    {
        BDK_TRACE(BGX, "%s: Recording module removal\n", device->name);
        memset(sfp_state->rom, 0, sizeof(sfp_state->rom));
        sfp_state->module_present = false;
        BDK_TRACE(BGX, "%s: Setting TX disabled\n", device->name);
        gpio_write(sfp_state->tx_dis, sfp_state->tx_dis_pin, 1);
    }

    if (!(state->flags & BDK_DEVICE_NETPORT_FLAG_MISSING) && !sfp_state->module_present)
    {
        BDK_TRACE(BGX, "%s: Recording module insert\n", device->name);
        sfp_state->module_present = true;
        rom_read(device, sfp_state);
        rom_parse(device, state, true);
        if (sfp_state->allow_link && !(state->flags & BDK_DEVICE_NETPORT_FLAG_MISSING))
        {
            BDK_TRACE(BGX, "%s: Setting TX enabled\n", device->name);
            gpio_write(sfp_state->tx_dis, sfp_state->tx_dis_pin, 0);
        }
    }
    else
        rom_parse(device, state, false);
}

/**
 * Network port API to force an unplug, regardless if the cable is still connected
 *
 * @param device Device to unplug
 */
static void netport_unplug(bdk_device_t *device)
{
    sfp_state_t *sfp_state = (sfp_state_t *)device->priv.state;
    if (!sfp_state->force_unplug)
    {
        BDK_TRACE(BGX, "%s: Forced unplug\n", device->name);
        sfp_state->force_unplug = true;
    }
}

/**
 * Network port API to undo a force unplug. For some ports the string
 * argument can be used to control what is plugged in. For example, this
 * selects which emulated ROM is used for SFPs in Asim.
 *
 * @param device Device to plug
 * @param param  Parameter for plug
 */
static void netport_plug(bdk_device_t *device, const char *param)
{
    sfp_state_t *sfp_state = (sfp_state_t *)device->priv.state;
    if (!sfp_state->force_unplug)
    {
        bdk_error("%s: Perform unplug first\n", device->name);
        return;
    }

    BDK_TRACE(BGX, "%s: Forced plug %s\n", device->name, param);

    for (int i = 0; i < (int)(sizeof(ROM_TABLE) / sizeof(ROM_TABLE[0])); i++)
    {
        if (strcmp(param, ROM_TABLE[i].name) == 0)
        {
            BDK_TRACE(BGX, "%s: Setting ROM index %d, %s\n", device->name, i, ROM_TABLE[i].name);
            sfp_state->asim_rom = i;
            break;
        }
    }
    sfp_state->force_unplug = false;
}

bdk_driver_t __bdk_driver_netport_sfp28 = {
    .name = "NETPORT-SFP28",
    .add = add,
    .init = init,
    .api = BDK_DEVICE_API_NETPORT,
    .funcs.netport.init = netport_init,
    .funcs.netport.set = netport_set,
    .funcs.netport.get = netport_get,
    .funcs.netport.unplug = netport_unplug,
    .funcs.netport.plug = netport_plug,
};
