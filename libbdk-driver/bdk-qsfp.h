/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/

/**
 * @file
 *
 * The data structures in this file represent the EEPROM data in a
 * QSFP28 module. QSFP28 follows spec SFF-8636 revision 11.0.
 *
 * @defgroup driver ECAM Attached Drivers
 * @addtogroup driver
 * @{
 */

typedef struct
{
    uint8_t id;                 /* 0 Identifier (See SFF-8024 Transceiver Management) Read-Only */
    uint8_t status[2];          /* 1-2 Status Read-Only */
    uint8_t intr[19];           /* 3-21 Interrupt Flags Read-Only */
    uint8_t free_mon[12];       /* 22-33 Free Side Device Monitors Read-Only */
    uint8_t channel_mon[48];    /* 34-81 Channel Monitors Read-Only */
    uint8_t reserved82[4];      /* 82-85 Reserved Read-Only */
    uint8_t control[13];        /* 86-98 Control Read/Write */
    uint8_t reserved99;         /* 99 Reserved */
    uint8_t free_mask[5];       /* 100-104 Free Side Device and Channel Masks Read/Write */
    uint8_t vendor_spec[2];     /* 105-106 Vendor Specific Read/Write */
    uint8_t reserved107;        /* 107 Reserved Read/Write */
    uint8_t free_prop[3];       /* 108-110 Free Side Device Properties Read-Only */
    uint8_t pcie[2];            /* 111-112 Assigned for use by PCI Express Read/Write */
    uint8_t free_prop2;         /* 113 Free Side Device Properties Read-Only */
    uint8_t reserved114[5];     /* 114-118 Reserved Read/Write */
    uint8_t password_change[4]; /* 119-122 Password Change Entry Area Write-Only */
    uint8_t password[4];        /* 123-126 Password Entry Area Write-Only */
    uint8_t page_sel;           /* 127 Page Select Byte Read/Write */
} bdk_qspd_main_t;

typedef struct
{
    uint8_t id;                 /* 128 1 Identifier Identifier Type of free side device */
    uint8_t ext_id;             /* 129 1 Ext. Identifier Extended Identifier of free side device. Includes power classes, CLEI codes, CDR capability */
    uint8_t connector;          /* 130 1 Connector Type Code for media connector type */
    uint8_t spec_code[8];       /* 131-138 8 Specification Compliance Code for electronic or optical compatibility */
    uint8_t encoding;           /* 139 1 Encoding Code for serial encoding algorithm */
    uint8_t bit_rate;           /* 140 1 BR, nominal Nominal bit rate, units of 100 Mbps. For BR > 25.4G, set this to FFh and use Byte 222 */
    uint8_t ext_rate_sel;       /* 141 1 Extended Rate Select Compliance Tags for extended rate select compliance */
    uint8_t smf_1000m;          /* 142 1 Length (SMF) Link length supported for SMF fiber in km */
    uint8_t om3_2m;             /* 143 1 Length (OM3 50 um) Link length supported for EBW 50/125 um fiber (OM3), units of 2 m */
    uint8_t om2_1m;             /* 144 1 Length (OM2 50 um) Link length supported for 50/125 um fiber (OM2), units of 1 m */
    uint8_t om1_1m;             /* 145 1 Length (OM1 62.5 um) Link length supported for 62.5/125 um fiber (OM1), units of 1 m */
    uint8_t length_1m_2m;       /* 146 1 Length (passive copper or active cable or OM4 50 um) Length of passive or active cable assembly (units of 1 m) or link length supported for OM4 50/125 um fiber (units of 2 m) as indicated by Byte 147. */
    uint8_t technology;         /* 147 1 Device technology Device technology */
    char    vendor[16];         /* 148-163 16 Vendor name Free side device vendor name (ASCII) */
    uint8_t ext_mode_code;      /* 164 1 Extended Module Extended Module codes for InfiniBand */
    uint8_t vendor_oui[3];      /* 165-167 3 Vendor OUI Free side device vendor IEEE company ID */
    char    vendor_pn[16];      /* 168-183 16 Vendor PN Part number provided by free side device vendor(ASCII) */
    char    vendor_rev[2];      /* 184-185 2 Vendor rev Revision level for part number provided by vendor(ASCII) */
    uint8_t wave_or_attn[2];    /* 186-187 2 Wavelength or Copper Cable Attenuation Nominal laser wavelength (wavelength=value/20 in nm) or copper cable attenuation in dB at 2.5 GHz (Byte 186) and 5.0 GHz (Byte 187) */
    uint8_t wavet_or_attng[2];  /* 188-189 2 Wavelength tolerance or Copper Cable Attenuation Guaranteed range of laser wavelength(+/- value) from nominal wavelength.(wavelength Tol.=value/200 in nm) or copper cable attenuation in dB at 7.0 GHz (Byte 188) and 12GHz (Byte 189) */
    uint8_t max_temp;           /* 190 1 Max case temp. Maximum case temperature in degrees C */
    uint8_t cc_base;            /* 191 1 CC_BASE Check code for base ID fields (Bytes 128-190) */
    uint8_t link_codes;         /* 192 1 Link codes Extended Specification Compliance Codes */
    uint8_t options_rate[3];    /* 193-195 3 Options Rate Select, TX Disable, TX Fault, LOS, Warning indicators for: Temperature, VCC, RX power, TX Bias, TX EQ, Adaptive TX EQ, RX EMPH, CDR Bypass, CDR LOL Flag. */
    char    vendor_sn[16];      /* 196-211 16 Vendor SN Serial number provided by vendor (ASCII) */
    char    date_code[8];       /* 212-219 8 Date Code Vendor's manufacturing date code */
    uint8_t diagnostic;         /* 220 1 Diagnostic Monitoring Type Indicates which type of diagnostic monitoring is implemented (if any) in the free side device. Bit 1,0 Reserved. */
    uint8_t enh_options;        /* 221 1 Enhanced Options Indicates which optional enhanced features are implemented in the free side device. */
    uint8_t bit_rate_chan;      /* 222 1 BR, nominal Nominal bit rate per channel, units of 250 Mbps. Complements Byte 140. */
    uint8_t cc_ext;             /* 223 1 CC_EXT Check code for the Extended ID Fields (Bytes 192-222) */
    uint8_t vendor_spec[32];    /* 224-255 32 Vendor Specific Vendor Specific EEPROM */
} bdk_qspd_page0_t;

typedef struct
{
    uint8_t cc_apps;            /* 128 7-0 CC_APPS Check code for the AST: the
                                    check code shall be the low order bits of
                                    the sum of the contents of all the bytes
                                    from 129 to 255, inclusive. */
    uint8_t ast_len;            /* 129 AST Table Length, TL (length - 1) A 6 bit
                                    binary number. TL, specifies the offset of
                                    the last application table entry defined in
                                    Bytes 130-255. TL is valid between 0 (1
                                    entry) and 62 (for a total of 63 entries) */
    uint8_t ast_tbl[63][2];     /* 130,131 Application Codes */
} bdk_qspd_page1_t;

typedef struct
{
    uint8_t rw[128];            /* User read/write EEPROM */
} bdk_qspd_page2_t;

typedef struct
{
    uint8_t threshhold[48];     /* 128-175 48 Thresholds Read-Only */
    uint8_t channel_thresh[48]; /* 176-223 48 Channel Thresholds Read-Only */
    uint8_t mag_id;             /* 224 1 Tx EQ & Rx Emphasis Magnitude ID Read-Only */
    uint8_t rx_amp_indicators;  /* 225 1 RX output amplitude support indicators Read-Only */
    uint8_t optional[16];       /* 226-241 16 Optional Channel Controls Read/Write */
    uint8_t channel_mon[12];    /* 242-253 12 Channel Monitor Masks Read/Write */
    uint8_t reserved[2];        /* 254-255 2 Reserved Read/Write */
} bdk_qspd_page3_t;

_Static_assert(sizeof(bdk_qspd_main_t) == 128, "QSFP main rom structure define incorrect");
_Static_assert(sizeof(bdk_qspd_page0_t) == 128, "QSFP page 0 structure define incorrect");
_Static_assert(sizeof(bdk_qspd_page1_t) == 128, "QSFP page 1 structure define incorrect");
_Static_assert(sizeof(bdk_qspd_page2_t) == 128, "QSFP page 2 structure define incorrect");
_Static_assert(sizeof(bdk_qspd_page3_t) == 128, "QSFP page 3 structure define incorrect");

/** @} */
