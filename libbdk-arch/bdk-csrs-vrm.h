#ifndef __BDK_CSRS_VRM_H__
#define __BDK_CSRS_VRM_H__
/* This file is auto-generated. Do not edit */

/***********************license start***************
 * Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
 * reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.

 *   * Neither the name of Cavium Inc. nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.

 * This Software, including technical data, may be subject to U.S. export  control
 * laws, including the U.S. Export Administration Act and its  associated
 * regulations, and may be subject to export or import  regulations in other
 * countries.

 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM  NETWORKS MAKES NO PROMISES, REPRESENTATIONS OR
 * WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT TO
 * THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY REPRESENTATION OR
 * DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT DEFECTS, AND CAVIUM
 * SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES OF TITLE,
 * MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF
 * VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK ARISING OUT OF USE OR
 * PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
 ***********************license end**************************************/


/**
 * @file
 *
 * Configuration and status register (CSR) address and type definitions for
 * Cavium VRM.
 *
 * This file is auto generated. Do not edit.
 *
 */

/**
 * Enumeration vrm_bar_e
 *
 * VRM Base Address Register Enumeration
 * Enumerates the base address registers.
 */
#define BDK_VRM_BAR_E_VRMX_PF_BAR0(a) (0x87e021000000ll + 0x1000000ll * (a))
#define BDK_VRM_BAR_E_VRMX_PF_BAR0_SIZE 0x100000ull

/**
 * Enumeration vrm_type_e
 *
 * VRM Types Register Enumeration
 * Indicates type of device connected to this controller, as loaded into
 * VRM()_MISC_INFO[VRM_TYPE] and VRM()_MISC_INFO[VRM_TYPE2].
 */
#define BDK_VRM_TYPE_E_ISL6367 (1)
#define BDK_VRM_TYPE_E_PMB_LIN (0)
#define BDK_VRM_TYPE_E_PMB_VID (2)
#define BDK_VRM_TYPE_E_PMB_VID_TPS53641 (4)

/**
 * Structure vrm_tws_twsi_sw_s
 *
 * VRM TWSI Software Write Structure
 * Format for software to write data to external regulator.
 */
union bdk_vrm_tws_twsi_sw_s
{
    uint64_t u;
    struct bdk_vrm_tws_twsi_sw_s_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_52_63        : 12;
        uint64_t v                     : 1;  /**< [ 51: 51] Valid. */
        uint64_t r                     : 1;  /**< [ 50: 50] Read. */
        uint64_t size                  : 2;  /**< [ 49: 48] Size of payload. */
        uint64_t addr                  : 8;  /**< [ 47: 40] Slave address. External regulator ID. */
        uint64_t ia                    : 8;  /**< [ 39: 32] Internal CSR address of registers within external regulator. */
        uint64_t data                  : 32; /**< [ 31:  0] Data to/from external regulator, includes PEC. */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0] Data to/from external regulator, includes PEC. */
        uint64_t ia                    : 8;  /**< [ 39: 32] Internal CSR address of registers within external regulator. */
        uint64_t addr                  : 8;  /**< [ 47: 40] Slave address. External regulator ID. */
        uint64_t size                  : 2;  /**< [ 49: 48] Size of payload. */
        uint64_t r                     : 1;  /**< [ 50: 50] Read. */
        uint64_t v                     : 1;  /**< [ 51: 51] Valid. */
        uint64_t reserved_52_63        : 12;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrm_tws_twsi_sw_s_s cn; */
};

/**
 * Register (RSL) vrm#_alt_fuse
 *
 * VRM Alternative Fuse Register
 */
union bdk_vrmx_alt_fuse
{
    uint64_t u;
    struct bdk_vrmx_alt_fuse_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_40_63        : 24;
        uint64_t tran_temp             : 8;  /**< [ 39: 32](R/W) Transition temperature for V calculation. */
        uint64_t max_step              : 8;  /**< [ 31: 24](R/W) V step. */
        uint64_t slope                 : 8;  /**< [ 23: 16](R/W) Slope. */
        uint64_t v_base                : 8;  /**< [ 15:  8](R/W) Base voltage. Minimum voltage that gets written to voltage regulator. */
        uint64_t v_max                 : 8;  /**< [  7:  0](R/W) Max voltage. Maximum voltage that gets written to voltage regulator. */
#else /* Word 0 - Little Endian */
        uint64_t v_max                 : 8;  /**< [  7:  0](R/W) Max voltage. Maximum voltage that gets written to voltage regulator. */
        uint64_t v_base                : 8;  /**< [ 15:  8](R/W) Base voltage. Minimum voltage that gets written to voltage regulator. */
        uint64_t slope                 : 8;  /**< [ 23: 16](R/W) Slope. */
        uint64_t max_step              : 8;  /**< [ 31: 24](R/W) V step. */
        uint64_t tran_temp             : 8;  /**< [ 39: 32](R/W) Transition temperature for V calculation. */
        uint64_t reserved_40_63        : 24;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_alt_fuse_s cn; */
};
typedef union bdk_vrmx_alt_fuse bdk_vrmx_alt_fuse_t;

static inline uint64_t BDK_VRMX_ALT_FUSE(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_ALT_FUSE(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000018ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000018ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000018ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_ALT_FUSE", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_ALT_FUSE(a) bdk_vrmx_alt_fuse_t
#define bustype_BDK_VRMX_ALT_FUSE(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_ALT_FUSE(a) "VRMX_ALT_FUSE"
#define device_bar_BDK_VRMX_ALT_FUSE(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_ALT_FUSE(a) (a)
#define arguments_BDK_VRMX_ALT_FUSE(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_device_status
 *
 * VRM Device Status Register
 */
union bdk_vrmx_device_status
{
    uint64_t u;
    struct bdk_vrmx_device_status_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_18_63        : 46;
        uint64_t remove_idle           : 1;  /**< [ 17: 17](R/W) When set, will remove IDLE as described below.
                                                                 Software should not set this bit, unless the reason for PEC mismatch is known. */
        uint64_t status_idle           : 1;  /**< [ 16: 16](RO/H) If set, faulty external controller operation was detected, for example in the ISL636*.
                                                                 Sixteen attempts were made to communicate with device that came back with PEC faults.
                                                                 See STATUS_CML in the PMbus documentation. */
        uint64_t status_byte           : 8;  /**< [ 15:  8](RO/H) Reads STATUS_BYTE register. See PMBus documentation. */
        uint64_t status_cml            : 8;  /**< [  7:  0](RO/H) Reads STATUS_CML register. See PMBus documentation. */
#else /* Word 0 - Little Endian */
        uint64_t status_cml            : 8;  /**< [  7:  0](RO/H) Reads STATUS_CML register. See PMBus documentation. */
        uint64_t status_byte           : 8;  /**< [ 15:  8](RO/H) Reads STATUS_BYTE register. See PMBus documentation. */
        uint64_t status_idle           : 1;  /**< [ 16: 16](RO/H) If set, faulty external controller operation was detected, for example in the ISL636*.
                                                                 Sixteen attempts were made to communicate with device that came back with PEC faults.
                                                                 See STATUS_CML in the PMbus documentation. */
        uint64_t remove_idle           : 1;  /**< [ 17: 17](R/W) When set, will remove IDLE as described below.
                                                                 Software should not set this bit, unless the reason for PEC mismatch is known. */
        uint64_t reserved_18_63        : 46;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_device_status_s cn; */
};
typedef union bdk_vrmx_device_status bdk_vrmx_device_status_t;

static inline uint64_t BDK_VRMX_DEVICE_STATUS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_DEVICE_STATUS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e0210000a8ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e0210000a8ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e0210000a8ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_DEVICE_STATUS", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_DEVICE_STATUS(a) bdk_vrmx_device_status_t
#define bustype_BDK_VRMX_DEVICE_STATUS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_DEVICE_STATUS(a) "VRMX_DEVICE_STATUS"
#define device_bar_BDK_VRMX_DEVICE_STATUS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_DEVICE_STATUS(a) (a)
#define arguments_BDK_VRMX_DEVICE_STATUS(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_eco
 *
 * INTERNAL: VRM ECO Register
 */
union bdk_vrmx_eco
{
    uint64_t u;
    struct bdk_vrmx_eco_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
#else /* Word 0 - Little Endian */
        uint64_t eco_rw                : 32; /**< [ 31:  0](R/W) Internal:
                                                                 Reserved for ECO usage. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_eco_s cn; */
};
typedef union bdk_vrmx_eco bdk_vrmx_eco_t;

static inline uint64_t BDK_VRMX_ECO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_ECO(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e0210000c8ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e0210000c8ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX_PASS2_X) && (a<=1))
        return 0x87e0210000c8ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_ECO", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_ECO(a) bdk_vrmx_eco_t
#define bustype_BDK_VRMX_ECO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_ECO(a) "VRMX_ECO"
#define device_bar_BDK_VRMX_ECO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_ECO(a) (a)
#define arguments_BDK_VRMX_ECO(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_fuse_bypass
 *
 * VRM Fuse Bypass Register
 */
union bdk_vrmx_fuse_bypass
{
    uint64_t u;
    struct bdk_vrmx_fuse_bypass_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_3_63         : 61;
        uint64_t ctl_hw_bypass         : 1;  /**< [  2:  2](R/W) If set, bypass VRM control hardware responsible for controlling external voltage
                                                                 regulator so software can send commands to the regulator. */
        uint64_t ctl_fuse_bypass       : 1;  /**< [  1:  1](R/W) If set, bypass V_MAX, V_BASE, MAX_STEP, SLOPE, TRAN_TEMP fuses which feed the PMBus VRM controller. */
        uint64_t ts_fuse_bypass        : 1;  /**< [  0:  0](R/W) If set, bypass MC and NOFF fuses which feed the temperature sensor. */
#else /* Word 0 - Little Endian */
        uint64_t ts_fuse_bypass        : 1;  /**< [  0:  0](R/W) If set, bypass MC and NOFF fuses which feed the temperature sensor. */
        uint64_t ctl_fuse_bypass       : 1;  /**< [  1:  1](R/W) If set, bypass V_MAX, V_BASE, MAX_STEP, SLOPE, TRAN_TEMP fuses which feed the PMBus VRM controller. */
        uint64_t ctl_hw_bypass         : 1;  /**< [  2:  2](R/W) If set, bypass VRM control hardware responsible for controlling external voltage
                                                                 regulator so software can send commands to the regulator. */
        uint64_t reserved_3_63         : 61;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_fuse_bypass_s cn; */
};
typedef union bdk_vrmx_fuse_bypass bdk_vrmx_fuse_bypass_t;

static inline uint64_t BDK_VRMX_FUSE_BYPASS(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_FUSE_BYPASS(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000098ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000098ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000098ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_FUSE_BYPASS", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_FUSE_BYPASS(a) bdk_vrmx_fuse_bypass_t
#define bustype_BDK_VRMX_FUSE_BYPASS(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_FUSE_BYPASS(a) "VRMX_FUSE_BYPASS"
#define device_bar_BDK_VRMX_FUSE_BYPASS(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_FUSE_BYPASS(a) (a)
#define arguments_BDK_VRMX_FUSE_BYPASS(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_misc_info
 *
 * VRM Miscellaneous Register
 */
union bdk_vrmx_misc_info
{
    uint64_t u;
    struct bdk_vrmx_misc_info_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_43_63        : 21;
        uint64_t vrm_type2             : 3;  /**< [ 42: 40](RO/H) Bits \<4..2\> of VRM type, enumerated by VRM_TYPE_E. */
        uint64_t vrm_ctl_rcv_status_error : 24;/**< [ 39: 16](RO/H) Holds the received status read from the external controller only for failing status. */
        uint64_t vrm_ctl_cur_state     : 3;  /**< [ 15: 13](RO/H) Current state of the VRM_CTL. */
        uint64_t vrm_type              : 2;  /**< [ 12: 11](RO/H) Bits \<1:0\> of VRM type indicating the type of device connected to this controller.
                                                                 Enumerated by VRM_TYPE_E. */
        uint64_t boot_seq              : 1;  /**< [ 10: 10](RO/H) Boot sequence was completed. */
        uint64_t ts_fuse_sts           : 1;  /**< [  9:  9](RO/H) Set if VRM fuses were loaded. */
        uint64_t vrm_fuse_sts          : 1;  /**< [  8:  8](RO/H) Set if VRM fuses were loaded. */
        uint64_t cmnd                  : 8;  /**< [  7:  0](RO/H) Last command send to the external voltage regulator. */
#else /* Word 0 - Little Endian */
        uint64_t cmnd                  : 8;  /**< [  7:  0](RO/H) Last command send to the external voltage regulator. */
        uint64_t vrm_fuse_sts          : 1;  /**< [  8:  8](RO/H) Set if VRM fuses were loaded. */
        uint64_t ts_fuse_sts           : 1;  /**< [  9:  9](RO/H) Set if VRM fuses were loaded. */
        uint64_t boot_seq              : 1;  /**< [ 10: 10](RO/H) Boot sequence was completed. */
        uint64_t vrm_type              : 2;  /**< [ 12: 11](RO/H) Bits \<1:0\> of VRM type indicating the type of device connected to this controller.
                                                                 Enumerated by VRM_TYPE_E. */
        uint64_t vrm_ctl_cur_state     : 3;  /**< [ 15: 13](RO/H) Current state of the VRM_CTL. */
        uint64_t vrm_ctl_rcv_status_error : 24;/**< [ 39: 16](RO/H) Holds the received status read from the external controller only for failing status. */
        uint64_t vrm_type2             : 3;  /**< [ 42: 40](RO/H) Bits \<4..2\> of VRM type, enumerated by VRM_TYPE_E. */
        uint64_t reserved_43_63        : 21;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_misc_info_s cn; */
};
typedef union bdk_vrmx_misc_info bdk_vrmx_misc_info_t;

static inline uint64_t BDK_VRMX_MISC_INFO(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_MISC_INFO(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000048ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000048ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000048ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_MISC_INFO", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_MISC_INFO(a) bdk_vrmx_misc_info_t
#define bustype_BDK_VRMX_MISC_INFO(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_MISC_INFO(a) "VRMX_MISC_INFO"
#define device_bar_BDK_VRMX_MISC_INFO(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_MISC_INFO(a) (a)
#define arguments_BDK_VRMX_MISC_INFO(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_telemetry_cmnd
 *
 * VRM Telemetry Command Register
 */
union bdk_vrmx_telemetry_cmnd
{
    uint64_t u;
    struct bdk_vrmx_telemetry_cmnd_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_2_63         : 62;
        uint64_t cmnd                  : 2;  /**< [  1:  0](R/W/H) This command will initiate a read instruction to the external voltage regulator
                                                                 into VRM_TELEMETRY_READ.
                                                                 0x0 = Do nothing.
                                                                 0x1 = Read V.
                                                                 0x2 = Read I.
                                                                 0x3 = Read V.

                                                                 Hardware clears [CMND] to indicate operation completed. */
#else /* Word 0 - Little Endian */
        uint64_t cmnd                  : 2;  /**< [  1:  0](R/W/H) This command will initiate a read instruction to the external voltage regulator
                                                                 into VRM_TELEMETRY_READ.
                                                                 0x0 = Do nothing.
                                                                 0x1 = Read V.
                                                                 0x2 = Read I.
                                                                 0x3 = Read V.

                                                                 Hardware clears [CMND] to indicate operation completed. */
        uint64_t reserved_2_63         : 62;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_telemetry_cmnd_s cn; */
};
typedef union bdk_vrmx_telemetry_cmnd bdk_vrmx_telemetry_cmnd_t;

static inline uint64_t BDK_VRMX_TELEMETRY_CMND(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_TELEMETRY_CMND(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000038ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000038ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000038ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_TELEMETRY_CMND", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_TELEMETRY_CMND(a) bdk_vrmx_telemetry_cmnd_t
#define bustype_BDK_VRMX_TELEMETRY_CMND(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_TELEMETRY_CMND(a) "VRMX_TELEMETRY_CMND"
#define device_bar_BDK_VRMX_TELEMETRY_CMND(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_TELEMETRY_CMND(a) (a)
#define arguments_BDK_VRMX_TELEMETRY_CMND(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_telemetry_read
 *
 * VRM Telemetry Read Register
 */
union bdk_vrmx_telemetry_read
{
    uint64_t u;
    struct bdk_vrmx_telemetry_read_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_32_63        : 32;
        uint64_t iout                  : 16; /**< [ 31: 16](RO) Current reading from external regulator. */
        uint64_t vout                  : 16; /**< [ 15:  0](RO) Voltage reading from external regulator. */
#else /* Word 0 - Little Endian */
        uint64_t vout                  : 16; /**< [ 15:  0](RO) Voltage reading from external regulator. */
        uint64_t iout                  : 16; /**< [ 31: 16](RO) Current reading from external regulator. */
        uint64_t reserved_32_63        : 32;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_telemetry_read_s cn; */
};
typedef union bdk_vrmx_telemetry_read bdk_vrmx_telemetry_read_t;

static inline uint64_t BDK_VRMX_TELEMETRY_READ(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_TELEMETRY_READ(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000028ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000028ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000028ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_TELEMETRY_READ", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_TELEMETRY_READ(a) bdk_vrmx_telemetry_read_t
#define bustype_BDK_VRMX_TELEMETRY_READ(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_TELEMETRY_READ(a) "VRMX_TELEMETRY_READ"
#define device_bar_BDK_VRMX_TELEMETRY_READ(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_TELEMETRY_READ(a) (a)
#define arguments_BDK_VRMX_TELEMETRY_READ(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_trip
 *
 * VRM Thermal Trip Register
 */
union bdk_vrmx_trip
{
    uint64_t u;
    struct bdk_vrmx_trip_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_8_63         : 56;
        uint64_t trip_level            : 8;  /**< [  7:  0](R/W) If temperature sensed is greater than this value RST_THERMAL_ALERT[TRIP] is set,
                                                                 and the THERMAL_TRIP_L pin asserts. */
#else /* Word 0 - Little Endian */
        uint64_t trip_level            : 8;  /**< [  7:  0](R/W) If temperature sensed is greater than this value RST_THERMAL_ALERT[TRIP] is set,
                                                                 and the THERMAL_TRIP_L pin asserts. */
        uint64_t reserved_8_63         : 56;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_trip_s cn; */
};
typedef union bdk_vrmx_trip bdk_vrmx_trip_t;

static inline uint64_t BDK_VRMX_TRIP(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_TRIP(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e0210000b8ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e0210000b8ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e0210000b8ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_TRIP", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_TRIP(a) bdk_vrmx_trip_t
#define bustype_BDK_VRMX_TRIP(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_TRIP(a) "VRMX_TRIP"
#define device_bar_BDK_VRMX_TRIP(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_TRIP(a) (a)
#define arguments_BDK_VRMX_TRIP(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_ts_temp_conv_coeff_fsm
 *
 * VRM Temp Sensor Conversion Coefficient and FSM Register
 */
union bdk_vrmx_ts_temp_conv_coeff_fsm
{
    uint64_t u;
    struct bdk_vrmx_ts_temp_conv_coeff_fsm_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_58_63        : 6;
        uint64_t t_fsm                 : 10; /**< [ 57: 48](R/W) Sets time interval for FSM update. */
        uint64_t reserved_38_47        : 10;
        uint64_t coeff_a               : 6;  /**< [ 37: 32](R/W) Coefficient A value for polynomial fit.
                                                                 _ \<37\> is a sign bit to flip the shifted results.
                                                                 _ \<36:32\> dictates the amount of right shift. */
        uint64_t reserved_25_31        : 7;
        uint64_t coeff_b               : 9;  /**< [ 24: 16](R/W) Coefficient B value for polynomial fit. It should be a positive number and between 1 and
                                                                 2.
                                                                 _ \<24\> is the integer part should always be 1.
                                                                 _ \<23:16\> form the fractional part. */
        uint64_t reserved_12_15        : 4;
        uint64_t coeff_c               : 12; /**< [ 11:  0](R/W) Coefficient C value for polynomial fit.
                                                                 A 2's complement number. */
#else /* Word 0 - Little Endian */
        uint64_t coeff_c               : 12; /**< [ 11:  0](R/W) Coefficient C value for polynomial fit.
                                                                 A 2's complement number. */
        uint64_t reserved_12_15        : 4;
        uint64_t coeff_b               : 9;  /**< [ 24: 16](R/W) Coefficient B value for polynomial fit. It should be a positive number and between 1 and
                                                                 2.
                                                                 _ \<24\> is the integer part should always be 1.
                                                                 _ \<23:16\> form the fractional part. */
        uint64_t reserved_25_31        : 7;
        uint64_t coeff_a               : 6;  /**< [ 37: 32](R/W) Coefficient A value for polynomial fit.
                                                                 _ \<37\> is a sign bit to flip the shifted results.
                                                                 _ \<36:32\> dictates the amount of right shift. */
        uint64_t reserved_38_47        : 10;
        uint64_t t_fsm                 : 10; /**< [ 57: 48](R/W) Sets time interval for FSM update. */
        uint64_t reserved_58_63        : 6;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_ts_temp_conv_coeff_fsm_s cn; */
};
typedef union bdk_vrmx_ts_temp_conv_coeff_fsm bdk_vrmx_ts_temp_conv_coeff_fsm_t;

static inline uint64_t BDK_VRMX_TS_TEMP_CONV_COEFF_FSM(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_TS_TEMP_CONV_COEFF_FSM(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000078ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000078ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000078ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_TS_TEMP_CONV_COEFF_FSM", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_TS_TEMP_CONV_COEFF_FSM(a) bdk_vrmx_ts_temp_conv_coeff_fsm_t
#define bustype_BDK_VRMX_TS_TEMP_CONV_COEFF_FSM(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_TS_TEMP_CONV_COEFF_FSM(a) "VRMX_TS_TEMP_CONV_COEFF_FSM"
#define device_bar_BDK_VRMX_TS_TEMP_CONV_COEFF_FSM(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_TS_TEMP_CONV_COEFF_FSM(a) (a)
#define arguments_BDK_VRMX_TS_TEMP_CONV_COEFF_FSM(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_ts_temp_conv_ctl
 *
 * VRM Temp Sensor Analog Alternate Conversion Register
 */
union bdk_vrmx_ts_temp_conv_ctl
{
    uint64_t u;
    struct bdk_vrmx_ts_temp_conv_ctl_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_13_63        : 51;
        uint64_t reset_sm              : 1;  /**< [ 12: 12](R/W) This will force the temperature conversion state machine into the reset state until
                                                                 [RESET_SM] is cleared. */
        uint64_t sw_access             : 1;  /**< [ 11: 11](R/W) If set, software controls inputs of analog temperature sensor. */
        uint64_t ts_switch             : 9;  /**< [ 10:  2](R/W) Alternate software access to control temperature sensor switches. */
        uint64_t ts_curr2en            : 1;  /**< [  1:  1](R/W) Controls curr2_en pin on analog temperature sensor block. */
        uint64_t strobe                : 1;  /**< [  0:  0](R/W) Controls strobe pin on analog temperature sensor block. */
#else /* Word 0 - Little Endian */
        uint64_t strobe                : 1;  /**< [  0:  0](R/W) Controls strobe pin on analog temperature sensor block. */
        uint64_t ts_curr2en            : 1;  /**< [  1:  1](R/W) Controls curr2_en pin on analog temperature sensor block. */
        uint64_t ts_switch             : 9;  /**< [ 10:  2](R/W) Alternate software access to control temperature sensor switches. */
        uint64_t sw_access             : 1;  /**< [ 11: 11](R/W) If set, software controls inputs of analog temperature sensor. */
        uint64_t reset_sm              : 1;  /**< [ 12: 12](R/W) This will force the temperature conversion state machine into the reset state until
                                                                 [RESET_SM] is cleared. */
        uint64_t reserved_13_63        : 51;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_ts_temp_conv_ctl_s cn; */
};
typedef union bdk_vrmx_ts_temp_conv_ctl bdk_vrmx_ts_temp_conv_ctl_t;

static inline uint64_t BDK_VRMX_TS_TEMP_CONV_CTL(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_TS_TEMP_CONV_CTL(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000058ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000058ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000058ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_TS_TEMP_CONV_CTL", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_TS_TEMP_CONV_CTL(a) bdk_vrmx_ts_temp_conv_ctl_t
#define bustype_BDK_VRMX_TS_TEMP_CONV_CTL(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_TS_TEMP_CONV_CTL(a) "VRMX_TS_TEMP_CONV_CTL"
#define device_bar_BDK_VRMX_TS_TEMP_CONV_CTL(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_TS_TEMP_CONV_CTL(a) (a)
#define arguments_BDK_VRMX_TS_TEMP_CONV_CTL(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_ts_temp_conv_result
 *
 * VRM Temp Sensor Result Register
 */
union bdk_vrmx_ts_temp_conv_result
{
    uint64_t u;
    struct bdk_vrmx_ts_temp_conv_result_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_24_63        : 40;
        uint64_t n_valid               : 1;  /**< [ 23: 23](RO/H) When set N_VALUE is valid. */
        uint64_t n_value               : 11; /**< [ 22: 12](RO/H) N cycle count values after calibration initiated. Qualified by [N_VALID]. */
        uint64_t temp_valid            : 1;  /**< [ 11: 11](RO/H) When set [TEMP_CORRECTED] is valid.
                                                                 This bit is pulsed on each conversion, and as such software may not be able to observe the
                                                                 cycle in which [TEMP_VALID] is set. */
        uint64_t temp_corrected        : 11; /**< [ 10:  0](RO/H) Corrected temperature read out from the temp sensor module, in degrees C with
                                                                 two bits of fraction. Twos-complement if negative temperature. Unpredictable
                                                                 unless [TEMP_VALID] is set. */
#else /* Word 0 - Little Endian */
        uint64_t temp_corrected        : 11; /**< [ 10:  0](RO/H) Corrected temperature read out from the temp sensor module, in degrees C with
                                                                 two bits of fraction. Twos-complement if negative temperature. Unpredictable
                                                                 unless [TEMP_VALID] is set. */
        uint64_t temp_valid            : 1;  /**< [ 11: 11](RO/H) When set [TEMP_CORRECTED] is valid.
                                                                 This bit is pulsed on each conversion, and as such software may not be able to observe the
                                                                 cycle in which [TEMP_VALID] is set. */
        uint64_t n_value               : 11; /**< [ 22: 12](RO/H) N cycle count values after calibration initiated. Qualified by [N_VALID]. */
        uint64_t n_valid               : 1;  /**< [ 23: 23](RO/H) When set N_VALUE is valid. */
        uint64_t reserved_24_63        : 40;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_ts_temp_conv_result_s cn; */
};
typedef union bdk_vrmx_ts_temp_conv_result bdk_vrmx_ts_temp_conv_result_t;

static inline uint64_t BDK_VRMX_TS_TEMP_CONV_RESULT(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_TS_TEMP_CONV_RESULT(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000068ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000068ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000068ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_TS_TEMP_CONV_RESULT", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_TS_TEMP_CONV_RESULT(a) bdk_vrmx_ts_temp_conv_result_t
#define bustype_BDK_VRMX_TS_TEMP_CONV_RESULT(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_TS_TEMP_CONV_RESULT(a) "VRMX_TS_TEMP_CONV_RESULT"
#define device_bar_BDK_VRMX_TS_TEMP_CONV_RESULT(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_TS_TEMP_CONV_RESULT(a) (a)
#define arguments_BDK_VRMX_TS_TEMP_CONV_RESULT(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_ts_temp_noff_mc
 *
 * VRM Temp Sensor Noff Coefficient Register
 */
union bdk_vrmx_ts_temp_noff_mc
{
    uint64_t u;
    struct bdk_vrmx_ts_temp_noff_mc_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t reserved_28_63        : 36;
        uint64_t mc                    : 12; /**< [ 27: 16](R/W) MC value, default is 3000 decimal. */
        uint64_t reserved_11_15        : 5;
        uint64_t noff                  : 11; /**< [ 10:  0](R/W) N cycle count offset, used to subtract the appropriate count from N cycle.
                                                                 It should be such that at 0 degrees C, the difference between NOFF and NCYCLE is 0. */
#else /* Word 0 - Little Endian */
        uint64_t noff                  : 11; /**< [ 10:  0](R/W) N cycle count offset, used to subtract the appropriate count from N cycle.
                                                                 It should be such that at 0 degrees C, the difference between NOFF and NCYCLE is 0. */
        uint64_t reserved_11_15        : 5;
        uint64_t mc                    : 12; /**< [ 27: 16](R/W) MC value, default is 3000 decimal. */
        uint64_t reserved_28_63        : 36;
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_ts_temp_noff_mc_s cn; */
};
typedef union bdk_vrmx_ts_temp_noff_mc bdk_vrmx_ts_temp_noff_mc_t;

static inline uint64_t BDK_VRMX_TS_TEMP_NOFF_MC(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_TS_TEMP_NOFF_MC(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000088ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000088ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000088ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_TS_TEMP_NOFF_MC", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_TS_TEMP_NOFF_MC(a) bdk_vrmx_ts_temp_noff_mc_t
#define bustype_BDK_VRMX_TS_TEMP_NOFF_MC(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_TS_TEMP_NOFF_MC(a) "VRMX_TS_TEMP_NOFF_MC"
#define device_bar_BDK_VRMX_TS_TEMP_NOFF_MC(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_TS_TEMP_NOFF_MC(a) (a)
#define arguments_BDK_VRMX_TS_TEMP_NOFF_MC(a) (a),-1,-1,-1

/**
 * Register (RSL) vrm#_tws_twsi_sw
 *
 * VRM TWSI to Software Register
 * This register allows software to write data into I2C controller directly.
 * This register is for diagnostic use only.
 */
union bdk_vrmx_tws_twsi_sw
{
    uint64_t u;
    struct bdk_vrmx_tws_twsi_sw_s
    {
#if __BYTE_ORDER == __BIG_ENDIAN /* Word 0 - Big Endian */
        uint64_t v                     : 1;  /**< [ 63: 63](RC/W/H) Valid bit.
                                                                 Set on a write operation (should always be written with a 1).
                                                                 Cleared when a TWSI master-mode operation completes.
                                                                 Cleared when a TWSI configuration register access completes.
                                                                 Cleared when the TWSI device reads the register if SLONLY = 1. */
        uint64_t sl_only               : 1;  /**< [ 62: 62](RO) Reserved. */
        uint64_t eia                   : 1;  /**< [ 61: 61](RO) Reserved. */
        uint64_t op                    : 4;  /**< [ 60: 57](RO) Reserved. */
        uint64_t r                     : 1;  /**< [ 56: 56](R/W/H) Read bit or result. If this bit is set on a CSR write when SLONLY = 0, the operation is a
                                                                 read operation (if clear, it is a write operation).
                                                                 On a CSR read, this bit returns the result indication for the most recent master-mode
                                                                 operation, 1 = success, 0 = failure. */
        uint64_t sovr                  : 1;  /**< [ 55: 55](RO) Reserved. */
        uint64_t size_b3               : 1;  /**< [ 54: 54](RO) Reserved. */
        uint64_t size                  : 2;  /**< [ 53: 52](R/W/H) Size minus one. Specifies the size in bytes of the master-mode operation.
                                                                 (0 = 1 byte, 1 = 2 bytes, 3 = 4 bytes). */
        uint64_t scr                   : 2;  /**< [ 51: 50](RO) Reserved. */
        uint64_t un_addr               : 3;  /**< [ 49: 47](RO) Reserved. */
        uint64_t addr                  : 7;  /**< [ 46: 40](R/W/H) Address field. The address of the remote device for a master-mode operation.
                                                                 Note that when mastering a 7-bit OP, ADDR\<6:0\> should not take any of the values 0x78,
                                                                 0x79, 0x7A nor 0x7B, as these 7-bit addresses are reserved to extend to 10-bit addressing. */
        uint64_t ia                    : 8;  /**< [ 39: 32](R/W/H) Internal address. Used when launching a combined master-mode operation. */
        uint64_t data                  : 32; /**< [ 31:  0](R/W/H) Data field.
                                                                 Used on a write operation when initiating a master-mode write operation (SLONLY = 0),
                                                                 or writing a TWSI configuration register (SLONLY = 0).
                                                                 The read value is updated by:

                                                                 * A write operation to this register.

                                                                 * Master-mode completion (contains error code).

                                                                 * TWSI configuration-register read (contains result). */
#else /* Word 0 - Little Endian */
        uint64_t data                  : 32; /**< [ 31:  0](R/W/H) Data field.
                                                                 Used on a write operation when initiating a master-mode write operation (SLONLY = 0),
                                                                 or writing a TWSI configuration register (SLONLY = 0).
                                                                 The read value is updated by:

                                                                 * A write operation to this register.

                                                                 * Master-mode completion (contains error code).

                                                                 * TWSI configuration-register read (contains result). */
        uint64_t ia                    : 8;  /**< [ 39: 32](R/W/H) Internal address. Used when launching a combined master-mode operation. */
        uint64_t addr                  : 7;  /**< [ 46: 40](R/W/H) Address field. The address of the remote device for a master-mode operation.
                                                                 Note that when mastering a 7-bit OP, ADDR\<6:0\> should not take any of the values 0x78,
                                                                 0x79, 0x7A nor 0x7B, as these 7-bit addresses are reserved to extend to 10-bit addressing. */
        uint64_t un_addr               : 3;  /**< [ 49: 47](RO) Reserved. */
        uint64_t scr                   : 2;  /**< [ 51: 50](RO) Reserved. */
        uint64_t size                  : 2;  /**< [ 53: 52](R/W/H) Size minus one. Specifies the size in bytes of the master-mode operation.
                                                                 (0 = 1 byte, 1 = 2 bytes, 3 = 4 bytes). */
        uint64_t size_b3               : 1;  /**< [ 54: 54](RO) Reserved. */
        uint64_t sovr                  : 1;  /**< [ 55: 55](RO) Reserved. */
        uint64_t r                     : 1;  /**< [ 56: 56](R/W/H) Read bit or result. If this bit is set on a CSR write when SLONLY = 0, the operation is a
                                                                 read operation (if clear, it is a write operation).
                                                                 On a CSR read, this bit returns the result indication for the most recent master-mode
                                                                 operation, 1 = success, 0 = failure. */
        uint64_t op                    : 4;  /**< [ 60: 57](RO) Reserved. */
        uint64_t eia                   : 1;  /**< [ 61: 61](RO) Reserved. */
        uint64_t sl_only               : 1;  /**< [ 62: 62](RO) Reserved. */
        uint64_t v                     : 1;  /**< [ 63: 63](RC/W/H) Valid bit.
                                                                 Set on a write operation (should always be written with a 1).
                                                                 Cleared when a TWSI master-mode operation completes.
                                                                 Cleared when a TWSI configuration register access completes.
                                                                 Cleared when the TWSI device reads the register if SLONLY = 1. */
#endif /* Word 0 - End */
    } s;
    /* struct bdk_vrmx_tws_twsi_sw_s cn; */
};
typedef union bdk_vrmx_tws_twsi_sw bdk_vrmx_tws_twsi_sw_t;

static inline uint64_t BDK_VRMX_TWS_TWSI_SW(unsigned long a) __attribute__ ((pure, always_inline));
static inline uint64_t BDK_VRMX_TWS_TWSI_SW(unsigned long a)
{
    if (CAVIUM_IS_MODEL(CAVIUM_CN81XX) && (a==0))
        return 0x87e021000008ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN83XX) && (a==0))
        return 0x87e021000008ll + 0x1000000ll * ((a) & 0x0);
    if (CAVIUM_IS_MODEL(CAVIUM_CN88XX) && (a<=1))
        return 0x87e021000008ll + 0x1000000ll * ((a) & 0x1);
    __bdk_csr_fatal("VRMX_TWS_TWSI_SW", 1, a, 0, 0, 0);
}

#define typedef_BDK_VRMX_TWS_TWSI_SW(a) bdk_vrmx_tws_twsi_sw_t
#define bustype_BDK_VRMX_TWS_TWSI_SW(a) BDK_CSR_TYPE_RSL
#define basename_BDK_VRMX_TWS_TWSI_SW(a) "VRMX_TWS_TWSI_SW"
#define device_bar_BDK_VRMX_TWS_TWSI_SW(a) 0x0 /* PF_BAR0 */
#define busnum_BDK_VRMX_TWS_TWSI_SW(a) (a)
#define arguments_BDK_VRMX_TWS_TWSI_SW(a) (a),-1,-1,-1

#endif /* __BDK_CSRS_VRM_H__ */
