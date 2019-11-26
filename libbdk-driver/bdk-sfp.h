/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * The data structures in this file represent the EEPROM data in a SFP28
 * module. SFP28 follows spec SFF-8472 revision 11.0.
 *
 * @defgroup driver ECAM Attached Drivers
 * @addtogroup driver
 * @{
 */

typedef struct
{
    uint8_t id;             /* 0 1 Identifier Type of transceiver (see Table 3.2) */
    uint8_t ext_id;         /* 1 1 Ext. Identifier Extended identifier of type of transceiver (see Table 3.3) */
    uint8_t connector;      /* 2 1 Connector Code for connector type (see Table 3.4) */
    uint8_t transceiver1[8];/* 3-10 8 Transceiver Code for electronic or optical compatibility (see Table 3.5) (bit fields) */
    uint8_t encoding;       /* 11 1 Encoding Code for high speed serial encoding algorithm (see Table 3.6) */
    uint8_t bitrate;        /* 12 1 BR, Nominal Nominal signalling rate, units of 100MBd. */
    uint8_t rate_id;        /* 13 1 Rate Identifier Type of rate select functionality (see Table 3.6a) */
    uint8_t smf_1000m;      /* 14 1 Length(SMF,km) Link length supported for single mode fiber, units of km */
    uint8_t smf_100m;       /* 15 1 Length (SMF) Link length supported for single mode fiber, units of 100 m */
    uint8_t om2_10m;        /* 16 1 Length (50um) Link length supported for 50 um OM2 fiber, units of 10 m */
    uint8_t om1_10m;        /* 17 1 Length (62.5um) Link length supported for 62.5 um OM1 fiber, units of 10 m */
    uint8_t dac_1m;         /* 18 1 Length (cable) Link length supported for copper or direct attach cable, units of m */
    uint8_t om3_10m;        /* 19 1 Length (OM3) Link length supported for 50 um OM3 fiber, units of 10 m */
    char    vendor_name[16];/* 20-35 16 Vendor name SFP vendor name (ASCII) */
    uint8_t transceiver2;   /* 36 1 Transceiver Code for electronic or optical compatibility (see Table 3.5) (bit fields) */
    uint8_t vendor_oui[3];  /* 37-39 3 Vendor OUI SFP vendor IEEE company ID */
    char    vendor_pn[16];  /* 40-55 16 Vendor PN Part number provided by SFP vendor (ASCII) */
    char    vendor_rev[4];  /* 56-59 4 Vendor rev Revision level for part number provided by vendor (ASCII) */
    uint8_t wavelen[2];     /* 60-61 2 Wavelength Laser wavelength (Passive/Active Cable Specification Compliance) (bit fields) */
    uint8_t unalloc;        /* 62 1 Unallocated */
    uint8_t checksum;       /* 63 1 CC_BASE Check code for Base ID Fields (addresses 0 to 62) */
} bdk_spd_base_t;

typedef struct
{
    uint8_t options[2];     /* 64-65 2 Options - Indicates which optional transceiver signals are implemented (see Table 3.7) (bit fields) */
    uint8_t br_max;         /* 66 1 BR max - Upper bit rate margin, units of % */
    uint8_t br_min;         /* 67 1 BR min - Lower bit rate margin, units of % */
    char    vendir_sn[16];  /* 68-83 16 Vendor SN - Serial number provided by vendor (ASCII) */
    char    date_code[8];   /* 84-91 8 Date code - Vendor’s manufacturing date code (see Table 3.8) (ASCII encoded) */
    uint8_t diagnostic;     /* 92 1 Diagnostic Monitoring Type - Indicates which type of diagnostic monitoring is implemented (if any) in the transceiver (see Table 3.9) (bit fields) */
    uint8_t enhanced;       /* 93 1 Enhanced Options - Indicates which optional enhanced features are implemented (if any) in the transceiver (see Table 3.10) (bit fields) */
    uint8_t sff8427;        /* 94 1 SFF-8472 Compliance - Indicates which revision of SFF-8472 the transceiver complies with. (see Table 3.12) */
    uint8_t checksum;       /* 95 1 CC_EXT Check code for the Extended ID Fields (addresses 64 to 94) */
} bdk_spd_extended_t;

typedef struct
{
    uint8_t vendor[32];     /* 96-127 32 Vendor Specific - Vendor Specific EEPROM */
    uint8_t sff8079[128];   /* 128-255 128 Reserved - Reserved for SFF-8079 */
} bdk_spd_vendor_t;

typedef struct
{
    bdk_spd_base_t      base;
    bdk_spd_extended_t  ext;
    bdk_spd_vendor_t    vendor;
} bdk_spd_rom_t;

/** @} */
